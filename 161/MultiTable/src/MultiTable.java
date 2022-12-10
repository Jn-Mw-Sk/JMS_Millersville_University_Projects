/**
 * <Name> MultiTable
 * 
 * <Purpose> This program draws a multiplication table for values 1-10 
 * using nested for loops
 * 
 * @author John Shenk
 *
 * @version 1.1 February 13, 2020
 */
public class MultiTable {

	/**
	 * This method constructs a multiplication table using nested for loops
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		// Draw column labels
		System.out.println("   #   0   1   2   3   4   5   6   7   8   9   10");
		System.out.println("#################################################");
		
		// Draw the multiplication table
		for (int i = 0; i <= 10; i++) {
			System.out.printf("%2d", i);
			System.out.printf("%2s", "#");
			for(int j = 0; j <= 10; j++) {
				
				System.out.printf("%4d", j * i);
			}
			System.out.println("");
		}
			
	}

}
