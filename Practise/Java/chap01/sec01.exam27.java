package sec01.exam27;

import java.util.Scanner; //Scanner를 사용하기 위해선 반드시 임폴트를 포함해야한다.

public class ScannerExample {

	public static void main(String[] args) {
		
		Scanner scanner =   new Scanner(System.in);
		
		String inputData;
		
		while(true) {
			inputData = scanner.nextLine();
			System.out.println("입력된 문자열: \"" + inputData + "\"" );
			if (inputData.equals("q")) {
				break;
			}
		}
		scanner.close(); /*scanner 객체가 입력스트림을 계속 열어둔채로 프로그램이 종료
		될 수 있기 때문에 입력,출력 스트림을 사용한 후 명시적으로 닫아줘야하기 때문에 사용된다.*/
		
		System.out.println("종료");		
	}	
}
//입력된 문자열에 대해서 읽고 출력하고 입력한 문자열이 "q"라면 프로그램을 종료한다.
