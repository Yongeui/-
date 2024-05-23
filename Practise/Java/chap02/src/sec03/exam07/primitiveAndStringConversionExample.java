package sec03.exam07;

public class primitiveAndStringConversionExample {

	public static void main(String[] args) {
		
		int Value1 = Integer.parseInt("10");
		double Value2  = Double.parseDouble("3.14");
		boolean Value3 = Boolean.parseBoolean("true");
		
		System.out.println("Value:1" + Value1);
		System.out.println("Value:2" + Value2);
		System.out.println("Value3:" + Value3);

		String str1 = String.valueOf(10);
		String str2 = String.valueOf(3.14);
		String str3 = String.valueOf(true);
		
		
		System.out.println("str1:" + str1);
		System.out.println("str2:" + str2);
		System.out.println("str3:" + str3);
		
	}
	
}
