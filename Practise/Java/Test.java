public class DiceGame {
public static void main(String[] args) {
System.out.println("Welcome to the Dice Game! ");
System.out.println("Match the dice numbers to earn points.\n");

int chances = 2; 
int score = 0; 
Random random = new Random();

while (chances > 0) {
int dice1 = random.nextInt(6) + 1;
int dice2 = random.nextInt(6) + 1;
System.out.println("Rolling dice:");
System.out.println("Result: [" + dice1 + "] [" + dice2 + "]");

if (dice1 == dice2) { 
score += dice1; 
chances += 3; 
System.out.println("Match! You earned " + dice1 + " points and gained 3 extra chances!");
}
else {
System.out.println("No match. Try again!");
}
chances--;
System.out.println("Remaining chances: " + chances);
System.out.println("--------------------");
}
System.out.println("Game Over! Your final score: " + score + " ");
}
}

public class Vending_Machine {
public static void main(String[] args) {
int initialMoney = 5000;

String[] menuItem = {"Cola", "Water", "Juice", "Coffee", "Snack"};
Map<String, Integer> menuPrice = new HashMap<>();
for (String item : menuItem) {
menuPrice.put(item, ((int) (Math.random() * 1000) + 1) * 10);
}
String selecteItem = menuItem[(int) (Math.random() * menuItem.length)];
int selectePrice = menuPrice.get(selecteItem);

System.out.println("Welcome to the Vending Machine!");
System.out.println("Here are today's menu prices:");
menuPrice.forEach((item, price) -> System.out.println(item + ": " + price + " won"));
System.out.println("\nInitial money: " + initialMoney + " won");

if (initialMoney >= selectePrice) {
System.out.println("\nPurchased: " + selecteItem + " (" + selectePrice + " won)");
int remainingMoney = initialMoney - selectePrice;
System.out.println("Remaining money: " + remainingMoney + " won");
System.out.println("\nChange Breakdown:");

int[] coinTypes = {500, 100, 50, 10};
for (int coin : coinTypes) {
int count = remainingMoney / coin;
remainingMoney %= coin;
System.out.println(coin + " won: " + count + " coins");
}
}else {
System.out.println("\nNot enough money to buy " + selecteItem + ". Purchase failed.");
}
System.out.println("\nThank you for using the Vending Machine!");
}
}
