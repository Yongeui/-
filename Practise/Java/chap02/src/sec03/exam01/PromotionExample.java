package sec03.exam01;

public class PromotionExample {

	public static void main(String[] args) {
		
		byte byteValue = 10;
		int intValue = byteValue;
		
		System.out.println("intValue: " + intValue);
		
		char charValue ='가';
		intValue = charValue;
		
		System.out.println("intValue:" + intValue);
		
		intValue = 30;
		long longValue = intValue;
		System.out.println("longValue:" + longValue);
		
		longValue = 100;
		float floatvalue = longValue;
		System.out.println("floatValue: " + floatvalue);
	
		floatvalue = 100.5f;
		double doubleValue = floatvalue;
		System.out.println("floatValue" + floatvalue);
		
		
		
	}
	
}
