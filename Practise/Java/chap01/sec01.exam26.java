package sec01.exam26;

public class QstopExample {

	public static void main(String[] args) throws Exception {
		
		int keyCode;
		
		while(true) {
			keyCode = System.in.read();
			System.out.println("KeyCode:" + keyCode);
			if (keyCode == 113) { //keycode == 113은 키보드에서 소문자q이다. while문의 루프를 종료하기 위해서는 q를 입력하면 된다.
				break;
				
			}
		}
		System.out.println("종료");		
	}	
}
/* exam25에서는 무한루프에서 탈출하지 않고 계속 실행되는 상태였는데 현재는 루프를 이용하지만 아스키코드 113(q)
를 입력하여 루프에서 탈출하여 프로그램이 종료될 수 있도록 작성하였다. */
