package sec04.exam01;

public class PrintfExample {

	public static void main(String[] args) {
		
		int Value = 123;
		System.out.printf("상품의 가격: %d원 \n" , Value);
		System.out.printf("상품의 가격: %6d원 \n" , Value);
		System.out.printf("상품의 가격: %-6d원 \n" , Value);
		System.out.printf("상품의 가격: %06d원 \n" , Value);
		
		double area  = 3.14159 * 10 * 10;
		System.out.printf("반지름이 %d인 원의 넓이: %10.2f\n ", 10,area);
		
		String name = "홍길동";
		String job  = "도둑";
		System.out.printf("%6d ㅣ %-10s ㅣ %10s\n", 1, name, job);
		
		
	}
	
}
