package interpreterTool;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.List;

public class GenerateAst {

	public static void main(String[] args) throws IOException{
		if(args.length != 1) {
			System.err.println("Usage: generate_ast <output directory>");
			System.exit(64);
		}
		
		String outputDir = args[0];
		defineAst(outputDir, "Expr", Arrays.asList(
				"Binary   : Expr left, Token oper, Expr right",
				"Grouping : Expr expression",
				"LiteralExpression  : Literal lit, TokenType type",
				"Unary    : Token oper, Expr right"
			    ));

	}
	
	private static void defineAst(
		String outputDir, String baseName, List<String> types)
		throws IOException{
		String path = outputDir + "/" + baseName + ".h";
		PrintWriter writer = new PrintWriter(path, "UTF-8");
		
		writer.println("#include \"Token.h\"");
		writer.println();
		
		//	Forward Declarations
		for(String type : types)
		{
			String className = type.split(":")[0].trim();
			forwardDeclaration(writer, className);
		}
		
		//	Base visitor class
	    defineVisitor(writer, baseName, types);
		
	    //	Expr class ( base visitable class)
	    writer.println("template<typename T>");
	    writer.println("class " + baseName + " {");
		
		writer.println("public:");
	    
		//	The base accept() method
		writer.print("	virtual T accept(Visitor<T> visitor)");	
		writer.println(" { T temp;  return temp; };");	// accept method to be overriden
		writer.println("};");
		writer.println();

		//	Expressions
		for(String type : types)
		{
			String className = type.split(":")[0].trim();
			String fields = type.split(":")[1].trim();
			defineType(writer, baseName, className, fields);
		}
		
		writer.close();
	
	}
	
	private static void defineType(
			PrintWriter writer, String baseName, 
			String className, String fieldList) {
		
		String inheritExpr = baseName.replace("Expr", "Expr<T>");
		writer.println("template<typename T>");
		writer.println("class " + className + " : public " + inheritExpr + " {");
				 
		writer.println("public:");
		
		//	Constructor
		String constructorList = fieldList.replace("Expr ", "Expr<T> ");
		writer.print("	" + className + "(" + constructorList + ") : ");
				
		//	Initializer list
		String[] fields = fieldList.split(", ");
		
		int counter = 0; // 	to detect if its the last field as to not add a comma
		for(String field : fields) 
		{
			String name = field.split(" ")[1];
			writer.print(name + "(" + name + ")");
			if(counter++ < fields.length - 1)
				writer.print(", ");
		}
		writer.println("	{");
		writer.println("	}");
		
		//	Visitor pattern
		writer.println();
		//writer.println("	@Override");
		writer.println("	T accept(Visitor<T> visitor) {");
		writer.println("		return visitor.visit" + className + baseName + "(*this);");
		writer.println("	}");
		
		//	Fields
		writer.println();
		for(String field : fields)
		{
			field = field.replace("Expr", "Expr<T>");
			writer.println("	const " + field + ";");
		}
		
		writer.println("};");
		writer.println();
		
	}
	
	private static void defineVisitor(PrintWriter writer, String baseName, List<String> types) {
		writer.println("template <typename T>");
		writer.println("class Visitor {");
		writer.println("public:");

		for (String type : types) {
			String typeName = type.split(":")[0].trim();
			writer.print("		virtual T visit" + typeName + baseName + "(" + typeName + "<T>" + " " + baseName.toLowerCase() + ")");
			writer.println(" { T temp;  return temp; };");//	visit expression to be overriden
		}

		writer.println("};");
		writer.println();
	}
	
	private static void forwardDeclaration(PrintWriter writer, String className) {
		writer.println("template <typename T>");
		writer.println("class " + className +";");
	    writer.println();
		
	}

}
