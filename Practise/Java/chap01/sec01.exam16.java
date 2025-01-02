/* 데이터 타입 간의 자동 형 변환(Promotion)을 확인하는 코드이다. 첫 라인에서 byte값을 int변수에 할당한다.
byte를 int로 형변환할때는 자동으로 이루어진다. 두 번째 라인에서는 char값을 int에 할당하는데 char를 int로 
형변환할 때 유니코드 값으로 변환된다. '가' = 유니코드 '44032', 세 번째 라인에서는 int값을 long 변수에 할당
한다 int를 long으로 형변환할 때 자동으로 형변환이 이루어짐, 네 번째 라인에서는 long값을 float변수에 할당한다.
long을 float으로 형변환 시 자동으로 형변환이 이루어지며, 소수점 이하가 있는 값을 float타입을 변환된다. 마지막
으로 float값을 double에 할당한다. */

package sec01.exam16;

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
		
		System.out.println("floatValue:" + floatvalue);
	
		floatvalue = 100.5f;
		double doubleValue = floatvalue;
		
		System.out.println("floatValue" + floatvalue);
		
		
		
	}
	
}

/* reuslt : 
intValue: 10
intValue:44032
longValue:30
floatValue:100.0
floatValue100.5 */
