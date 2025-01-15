package sec02.exam07;

public class CompareOperatiorExample {

	public static void main(String[] args) {
		
		int num1 = 10;
		int num2 = 10;
		boolean rseult1 = (num1 == num2);
		boolean rseult2 = (num1 != num2);
		boolean rseult3 = (num1 <= num2);
		System.out.println("result1=" + rseult1);
		System.out.println("result2=" + rseult2);
		System.out.println("result3=" + rseult3);
		
		char char1 = 'A';
		char char2 = 'B';
		boolean result4 = (char1 < char2);
		System.out.println("result4=" + result4);
	}
	
}
