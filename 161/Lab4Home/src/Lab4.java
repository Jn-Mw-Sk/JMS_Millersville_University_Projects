/**
 * This program, the "Number Wizard", takes a number of integers from the user
 * and proceeds to display the largest number, smallest number, number of 0s entered,
 * number of even numbers, number of odd numbers, the average, and the total of the 
 * integers entered
 * 
 * @author shenk
 * 
 * <Date> March 3, 2020
 */

import java.util.Scanner;
public class Lab4 {
	public static final int MAX_INT = Integer.MAX_VALUE;
	public static final int MIN_INT = Integer.MIN_VALUE; 
	
	
	/**
	 * This method receives integer input from the user and 
	 * returns it to the main method as an integer value
	 * 
	 * @param console
	 * @param num
	 * @return
	 */
	public static int getInteger(Scanner console, int num) {
		System.out.printf("%11s", "Your integer # ");
		System.out.printf(num + " is? ");
		num = console.nextInt();
		
		return num;
	}
	
	public static int checkIfMaximum(int next, int maximum) {
		if(next > maximum) {
			maximum = next;
		}
		
	}
	
	/**
	 * The main method introduces the program and requests the number of integers
	 * the user wishes to enter. Additional methods are called to acquire input, determine if 
	 * the number is the largest or smallest, count the number of zeroes and odds and evens,
	 * calculate and display the average, and display the total of the numbers entered.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner console = new Scanner(System.in);
		
		// Introduce Program
		System.out.printf("Greetings!\n\n");
		System.out.printf("I am the \"Number Wizard\" and I will astound you with my ability to analyze an integer series.\n\n");
		
		// Get the number of integers from the user
		System.out.printf("How many integers are in your series? ");
		int numIntegers = console.nextInt();
		
		int max = MIN_INT;
		int min = MAX_INT;
		
		// Get user input for the number of times the user entered
		for (int x = 1; x <= numIntegers; x++) {
			int nextNum = getInteger(console, x);
			
			
			
			//check if the number is the minimum in the series
			if(nextNum < min) {
				min = nextNum;
			}
			
		}
		
	}

}
