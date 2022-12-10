/* This program, the "Number Wizard", takes a number of integers from the user
 * and proceeds to display the largest number, smallest number, number of 0s entered,
 * number of even numbers, number of odd numbers, the average, and the total of the 
 * integers entered
 * 
 * @author John Shenk
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
		System.out.printf("\tYour integer # ");
		System.out.printf(num + " is? ");
		num = console.nextInt();
		
		return num;
	}
	
	/**
	 * This method determines if a number is the maximum in the series entered
	 * 
	 * @param next
	 * @param maximum
	 * @return
	 */
	public static int checkIfMaximum(int next, int maximum) {
		if(next > maximum) {
			maximum = next;
		}
		return maximum;
	}
	
	/**
	 * This method determines if a number is the maximum in the series entered
	 * 
	 * @param next
	 * @param minimum
	 * @return
	 */
	public static int checkIfMinimum(int next, int minimum) {
		if(next < minimum) {
			minimum = next;
		}
		return minimum;
		
	}
	
	/**
	 * This method determines if the number entered is "o" and returns a value 
	 * accordingly
	 * 
	 * @param next
	 * @return
	 */
	public static int checkIfZero(int next) {
		int num;
		if(next == 0) {
			num = 1;
		} else {
			num = 0;
		}
		return num;
	}
	
	/**
	 * This method determines if the number entered is even and returns a value
	 * accordingly
	 * 
	 * @param next
	 * @return
	 */
	public static int checkIfEven(int next) {
		int num;
		if (next % 2 == 0) {
			num = 1;
		} else {
			num = 0;
		}
		return num;
	}
	
	/**
	 * This method determines if the number entered is even and returns a value
	 * accordingly
	 * 
	 * @param next
	 * @return
	 */
	public static int checkIfOdd(int next) {
		int num;
		if (next % 2 != 0) {
			num = 1;
		} else {
			num = 0;
		}
		return num;
	}
	
	/**
	 * This method determines the average of the numbers entered and
	 * returns the value
	 * 
	 * @param total
	 * @param num
	 * @return
	 */
	public static double calcAverage(int total, int num) {
		double average = (double)total / num;
		return average;
	}
	
	public static void displayResults(int max, int min, int zeroes, int evens, int odds, double average, int total) {
		System.out.printf("\tMaximum integer in series................." + max + "\n");
		System.out.printf("\tMinimum integer in series................." + min + "\n");
		System.out.printf("\tNumber of 0s in series...................." + zeroes + "\n");
		System.out.printf("\tNumber of even integers in series........." + evens + "\n");
		System.out.printf("\tNumber of odd integers in series.........." + odds + "\n");
		System.out.printf("\tAverage of all integers in series.........");
		System.out.printf("%.2f", average);
		System.out.printf("\n");
		System.out.printf("\tTotal of all integers in series..........." + total + "\n");
		
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
		
		// Declare variables
		int max = MIN_INT;
		int min = MAX_INT;
		int numZeroes = 0;
		int total = 0;
		int numEvens = 0;
		int numOdds = 0;
		double average;
		
		// Determine if the integer entered is less than 0 and keep prompting until the
		// user enters a number greater than 0.
		while(numIntegers <= 0) {
			
			System.out.printf("\n");
			System.out.printf("Number entered is less than or equal to 0.\n");
			System.out.printf("Please enter a number greater than 0\n\n");
			System.out.printf("How many integers are in your series? ");
			numIntegers = console.nextInt();
			
		}
		
		// Get user input for the number of times the user entered.
		for (int x = 1; x <= numIntegers; x++) {
			int nextNum = getInteger(console, x);
			
			// Check if the number is the maximum in the series.
			max = checkIfMaximum(nextNum, max);
		
			// Check if the number is the minimum in the series.
			min = checkIfMinimum(nextNum, min);
			
			// Check if the number entered is "0" and add to the "zero"
			// counter.
			numZeroes += checkIfZero(nextNum);
		
			// Check if the number entered is even and add to the "even"
			// counter
			numEvens += checkIfEven(nextNum);
		
			// Check if the number entered is odd and add to the "odd"
			// counter
			numOdds += checkIfOdd(nextNum);
			
			// Accumulate total
			total += nextNum;
				
		}
			 
		
		// Calculate average
		average = calcAverage(total, numIntegers);
		
		System.out.printf("\n");
		// Thank the user 
		System.out.printf("Thank you for your " + numIntegers +  " entries.\n");
		
		// Display results
		System.out.printf("\n" + "The \"Number Wizard\" has reviewed your series and conjured the\n" + "following:\n\n");	
		displayResults(max, min, numZeroes, numEvens, numOdds, average, total);
				
	}

}