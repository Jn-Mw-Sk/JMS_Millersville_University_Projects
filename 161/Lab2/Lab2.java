        
/*******************************************************************************
 * 
 * <Name> Lab2
 * 
 * Purpose:  This program receives a number of seconds from the user and 
 * calculates the number of day, hours, and minutes in that number of seconds
 * and display them. Finally, it displays the amount of time in that amount
 * of seconds in D:HH:MM:SS format. The program keeps requesting an integer amount
 * from the user until the user enters "0".
 * 
 * @author John Shenk
 *
 * @version 1.0 (February 11, 2018)      
 * 
 ******************************************************************************/

import java.util.Scanner; // for scanner

public class Lab2 {
	
	/**
	 * 
	 * This method displays then number of seconds the user entered
	 * @param days
	 */
	public static void displaySeconds(int seconds) {
		System.out.println("Number of seconds entered is " + seconds + " which equates to: ");
	}
	
	/**
	 * 
	 * This method calculates the number of days in the number of seconds passed
	 * and displays the result
	 * @param days
	 */
	public static void printDays(int seconds) {
		int days = seconds / 86400;
		System.out.println("\t" + days + " days");
	}
	
	/**
	 * 
	 * This method calculates the number of hours in the number of seconds passed 
	 * and displays the result
	 * @param seconds
	 */
	public static void printHours(int seconds) {
		int hours = seconds / 3600;
		System.out.println("\t" + hours + " hours");
	}
	
	/**
	 * 
	 * This method calculates the number of minutes in the number of seconds passed 
	 * and displays the result
	 * @param seconds
	 */
	public static void printMinutes(int seconds) {
		int minutes = seconds / 60;
		System.out.println("\t" + minutes + " minutes");
	}
	
	/**
	 * This method checks to see if the hour is a single integer, formats it accordingly, 
	 * and then returns it to the "printDigital" method
	 * @param hours2
	 * @return
	 */
	public static String formatHour(int hours2) {
		if (hours2 < 10) {
			String hoursFormat = "0" + hours2; 
			return hoursFormat;
					
		}
		else {
			String hoursFormat = "" + hours2 + "";
			return hoursFormat;
		}
		
	}
	/**
	 * This method checks to see if the minute(s) are a single integer, formats it accordingly, 
	 * and then returns it to the "printDigital" method
	 * @param minutes2
	 * @return
	 */
	public static String formatMinutes(int minutes2) {
		if (minutes2 < 10) {
			String minutesFormat = "0" + minutes2; 
			return minutesFormat;
					
		}
		else {
			String minutesFormat = "" + minutes2 + "";
			return minutesFormat;
		}
		
	}
	/**
	 * This method checks to see if the second(s) are a single integer, formats it accordingly, 
	 * and then returns it to the "printDigital" method
	 * @param seconds2
	 * @return
	 */
	public static String formatSeconds(int seconds2) {
		if (seconds2 < 10) {
			String secondsFormat = "0" + seconds2; 
			return secondsFormat;
					
		}
		else {
			String secondsFormat = "" + seconds2 + "";
			return secondsFormat;
		}
		
	}
	
	/**
	 * 
	 * This method prints out the number of days, hours, and 
	 * minutes in the D:HH:MM:SS format
	 * @param seconds
	 */
	public static void printDigital(int seconds) {
		int days = seconds / 86400;
		int hours = (seconds % 86400) / 3600;
		int minutes = (seconds % 3600) / 60;
		seconds = seconds % 60;
		System.out.println("\t" + days + ":" + formatHour(hours) + ":" + formatMinutes(minutes) + ":" + formatSeconds(seconds) + " days, hours, minutes, and seconds (D:HH:MM:SS:)");
	}
	
	/**
	 * 
	 * This method prints out a departing message whenever "0" is entered 
	 * @param days
	 */
	public static void printGoodBye() {
		System.out.println("0 entered. Goodbye!");
	}
	
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Scanner console = new Scanner(System.in);
		
		// obtain values
		System.out.println("Enter a number of seconds as a whole number or 0 to quit:");
		int seconds = console.nextInt();
		
		//perform calculations / display results
		while (seconds != 0) {
			displaySeconds(seconds);
			printDays(seconds);
			printHours(seconds);
			printMinutes(seconds);
			printDigital(seconds);
			
			// request another input number
			System.out.println("\n" + "Enter a number of seconds as a whole number or 0 to quit:");
			seconds = console.nextInt();
	}
		
		printGoodBye();
	}

}
