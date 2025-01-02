package sec01.exam22;

public class primitiveAndStringConversionExample {

	public static void main(String[] args) {
		
		int Value1 = Integer.parseInt("10");
		double Value2  = Double.parseDouble("3.14");
		boolean Value3 = Boolean.parseBoolean("true");
		
		System.out.println("Value1:" + Value1);
		System.out.println("Value2:" + Value2);
		System.out.println("Value3:" + Value3);

		String str1 = String.valueOf(10);
		String str2 = String.valueOf(3.14);
		String str3 = String.valueOf(true);
		
		
		System.out.println("str1:" + str1);
		System.out.println("str2:" + str2);
		System.out.println("str3:" + str3);
		
	}
}
/* result :
Value1:10
Value2:3.14
Value3:true
str1:10
str2:3.14
str3:true */
