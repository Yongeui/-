package sec01.exam07;

/*
 * public class VariableinitaializationExample {
 * 
 * public static void main(String[] args) {
 * 
 * int v1 = 15; int v2 = 0; // v2 변수를 if 블록 밖에서 선언하고 초기화
 * 
 * 
 * if (v1 > 10) { v2 = v1 - 10; }
 * 
 * int v3 = v1 + v2 + 5; // v2 변수를 사용하여 v3를 계산 System.out.println("v3의 값: " +
 * v3); // v3의 값 출력 } //int v3 = v1 + v2, + 5; // v2 변수를 사용할 수 없기 때문에 컴파일 에러가
 * 생김. }
 */

public class VariableinitaializationExample {

	public static void main(String[] args) {
		
		int val1 = 15;
		int val2 = 0;  // val2를 if 블록 바깥에서 초기화하여 모든 경로에서 사용 가능하게 함
		
		if(val1 > 10) {
			val2 = val1 - 10;  // val1이 10보다 클 경우, val2에 새 값을 할당
		}
		int val3 = val1 + val2 + 5;  // val2는 이제 항상 초기화된 상태이므로 안전하게 사용 가능
		
		System.out.println("val3의 값: " + val3);
	}
}

//result : val3의 값은 : 25
