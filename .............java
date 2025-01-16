package JP2024_W_Assignment_Final;

class Employee {
    private String name;       
    private String address;   
    private int rrn;          
    protected int salary;      

    public Employee(String name, String address, int rrn, int salary) {
        this.name = name;
        this.address = address;
        this.rrn = rrn;
        this.salary = salary;
    }

    public String getName() {
        return name;
    }

    public String getAddress() {
        return address;
    }

    public int getSalary() {
        return salary;
    }

    @Override
    public String toString() {
        return "name = " + name + "\naddress = " + address + "\nSalary = " + salary;
    }
}

class Manager extends Employee {
    private int bonus; 

    public Manager(String name, String address, int rrn, int salary, int bonus) {
        super(name, address, rrn, salary); 
        this.bonus = bonus;
    }

    public void test() {
        System.out.println("name = " + getName());    
        System.out.println("address = " + getAddress());
        System.out.println("Salary = " + getSalary()); 
    }
}

public class Practice6_63P {
    public static void main(String[] args) {
        Manager manager = new Manager("Tom", "Wonju", 123456, 1000000, 50000);
        manager.test();
    }
}
===================================================================================
===================================================================================
===================================================================================
package JP2024_W_Assignment_Final;

class Bank {
 public double getInterestrate() {
     return 0.0; 
 }
}

class BadBank extends Bank {
 @Override
 public double getInterestrate() {
     return 10.0; 
 }
}

class NormalBank extends Bank {
 @Override
 public double getInterestrate() {
     return 5.0; 
 }
}

class GoodBank extends Bank {
 @Override
 public double getInterestrate() {
     return 3.0; 
 }
}

public class Practice6_64P {
 public static void main(String[] args) {
     Bank badBank = new BadBank();
     Bank normalBank = new NormalBank();
     Bank goodBank = new GoodBank();

     System.out.println("BadBank의 이자율: " + badBank.getInterestrate());
     System.out.println("NormalBank의 이자율: " + normalBank.getInterestrate());
     System.out.println("GoodBank의 이자율: " + goodBank.getInterestrate());
 }
}
===================================================================================
===================================================================================
===================================================================================
package JP2024_W_Assignment_Final;

class Shape {
 protected int x, y; 

 public Shape() {
     x = 0;
     y = 0;
     System.out.println("Shape()");
 }
}

class Rectangle extends Shape {
 protected int width, height; 

 public Rectangle() {
     width = 0;
     height = 0;
     System.out.println("Rectangle()");
 }
}

class ColoredRectangle extends Rectangle {
 private String color; 

 public ColoredRectangle() {
     color = "none";
     System.out.println("ColoredRectangle()");
 }
}

public class Practice6_65P {
 public static void main(String[] args) {
     ColoredRectangle ar = new ColoredRectangle();
 }
}
