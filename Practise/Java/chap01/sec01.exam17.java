package sec01.exam17;

public class CastExample {

	public static void main(String[] args) {
		
		int intValue = 44032;
		char charValue = (char)intValue;
		
		System.out.println(charValue);
		
		long longValue = 500;
		intValue = (int)longValue;

		System.out.println(intValue);
		
		double doubleValue = 3.14;
		intValue = (int)doubleValue;
		
		System.out.println(intValue);
		
		
		
	}
	
}

/* result : 
가
500
3 */
