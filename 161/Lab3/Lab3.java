/**
 * <Name> Looper
 * 
 * <Purpose> This program accepts two numbers as input at displays the numbers 
 * 			 between the two values entered
 * 
 * @author jmshenk1
 *
 * <Date> February 18, 2020
 */

import java.util.Scanner;

public class Lab3 {
	
	/**
	 * 
	 * This method requests the first integer value and 
	 * returns it as an integer to the main method
	 * 
	 * @param firstNumber
	 * 
	 * @return
	 */
	public static int getValue(Scanner console, String number) {
		// Display prompt and request integer
		System.out.println("Please enter the " + number + " integer: ");
		int firstNumber = console.nextInt();
		return firstNumber;
	}
	
	/**
	 * 
	 * The main method calls a method twice to request two input values as integers,
	 * and the displays the integers between those values in ascending or descending order 
	 * depending on if the first value is smaller than the second value or vice-versa
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner console = new Scanner(System.in);
		
		
		// request integers
		int first = getValue(console, "first");
		int second = getValue(console, "second");
		
		// Display the integers between the two numbers entered
		System.out.print("Output: \n");
		
		// Determine if the first value is less than the second valueor not
		//and display accordingly
		if (first < second) {
			// Display numbers in ascending order
			for (int i = first; i <= second; i++) {
				System.out.println(i);
			}
		} else {
			// Display number in descending order
			for (int j = first; j >= second; j--) {
				System.out.println(j);
			}
			
		}
	}

}
