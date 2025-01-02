/* boolean 변수 'Stop'을 flase로 초기화하고 if문에서 stop 변수의 값으 확인한다
  stop 변수가 tureㅇ면 중지합니다 라는 메시지를 출력하고 false이면 "시작합니다"
  를 출력하도록 한다. 현재 stop = false;이므로 "시작합니다"를 출력한다 */
package sec01.exma15;

public class BooleanExample {

	public static void main(String[] args) {
		
		boolean stop = false;
		
		if(stop) {
			System.out.println("중지합니다.");
			
			
		} else {
			System.out.println("시작합니다.");			
			
			
		}
		
	}
	
}
//result : 시작합니다.
