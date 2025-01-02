package sec01.exam11;

public class CharExample {

	public static void main(String[] args) {
		
		char c1 = 'A';
		char c2 = 65;
		char c3 = '\u0041';
		
		System.out.println(c1);
		System.out.println(c2);
		System.out.println(c3);
		
		char c4 = '가';
		char c5 = 44032;
		char c6 = '\uAC00';
		
		
		System.out.println(c4);
		System.out.println(c5);
		System.out.println(c6);
		
	}
	
}
/*result : 
A
A
A
가
가
가*/
