package sec01.exam18;

public class ByteOperationExample {

	public static void main(String[] args) {
		
		byte result1 = 10 + 20; //Java는 컴파일 과정에서도 연산을 수행함. 컴파일러에서의 연산은 좌측의 변수타입에 맞춰 연산.
	
		
		
		byte x = 10;
		byte y = 20;
		int result = x + y; /*위와 아래의 연산되는 위치가 다름. 이 코드는 JVM에서 연산이 시작됨. 변수가 사용되면, 변환이 된다. 해당 코드에서는
							각 각 byte타입으로 명시되어 있지만, 출력하고자 하는 result의 값은 int타입으로 타입 불일치가 발생한다.*/
    
		System.out.println("result : " + result);
	}
}

// result : 30 
