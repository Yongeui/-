package sec01.exam25;

public class ContinueKeycodeReadExample {

	public static void main(String[] args) throws Exception {
		
		int keyCode;
		
		while(true) {
			keyCode = System.in.read();
			System.out.println("KeyCode:" + keyCode);
			
		}
	}
}
//루프를 통해 사용자 입력에 대한 아스키코드를 출력.
