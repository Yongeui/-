package sec04.exam05;

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
		
		System.out.println("종료");
		
	}
	
}
