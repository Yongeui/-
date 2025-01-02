package sec01.exam23;

public class PrintfExample {

	public static void main(String[] args) {
		
		int Value = 123;
		System.out.printf("상품의 가격: %d원 \n" , Value); //일반출력
		System.out.printf("상품의 가격: %6d원 \n" , Value); //가장 앞자리3칸 + 주어진값3칸 총6칸
		System.out.printf("상품의 가격: %-6d원 \n" , Value); //가장 뒷자리3칸 + 주어진값 3칸 총6칸
		System.out.printf("상품의 가격: %06d원 \n" , Value); //06d이므로 앞자리를 3칸을 0으로 채움
		
		double area  = 3.14159 * 10 * 10;
		System.out.printf("반지름이 %d인 원의 넓이: %10.2f\n ", 10,area); //%12.2f에서 10.2만큼 공간을 생성
		
		String name = "홍길동";
		String job  = "도둑";
		System.out.printf("%6d ㅣ %-10s ㅣ %10s\n", 1, name, job);
		
		
	}
	
}
/* reuslt : 
상품의 가격: 123원 
상품의 가격:    123원 
상품의 가격: 123   원 
상품의 가격: 000123원 
반지름이 10인 원의 넓이:     314.16
      1 ㅣ 홍길동        ㅣ         도둑 */
