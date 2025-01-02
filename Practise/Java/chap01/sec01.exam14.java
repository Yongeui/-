package sec01.exam14;

public class FloatDoubleExample {

	public static void main(String[] args) {
		
		float var1 = 3.14f;
		double var2 = 3.14;
		 
		System.out.println("Float :" + var1);
		System.out.println("Double :" + var2);
		

		float var3 = 0.1234567890123456789f;
		double var4 = 0.1234567890123456789;
		
		
		System.out.println("Float :" + var3);
		System.out.println("Double :" + var4);
		
		double var5 = 3e6;	
		float var6 = 3e6f;
		double var7 = 2e-3;
		
		System.out.println("Double :" + var5);
		System.out.println("Float :" + var6);
		System.out.println("Double :" + var7);
		
	}
	
}
/* result :
Float :3.14
Double :3.14
Float :0.12345679
Double :0.12345678901234568
Double :3000000.0
Float :3000000.0
Double :0.002 */
