/**
 * This program calculates the scores for consecutive dives, omitting the highest and lowest scores
 * from each dive, and displays the scores. The program then displays an average for the total scores.
 * 
 * The scores are read from a text file line-by-line with each line containing a dive number, 
 * a difficulty number, and 7 scores from 7 judges, ranging in score from 0-10.
 * 
 * <Author> John M. Shenk
 * 
 * <Date> March 21, 2020
 */

import java.io.*; 
import java.util.Scanner; 

public class Lab6 {
	public static final double MAX_NUM = Double.MAX_VALUE;
	public static final double MIN_NUM = Double.MIN_VALUE;
	
	
	// Print the introductory message
	public static void printIntro() {
		System.out.printf("Welcome to the Diver Scoring program. This program will calculate an\n");
		System.out.printf("  overall score for a diver, based on individual dives.\n");
	}
	
	/**
	 *  Calculate the score for one dive 
	 * @param diveLine
	 * @return
	 */
	public static double calculateDiveScore(String diveLine) {
			Scanner data = new Scanner(diveLine);
			int diveNum = data.nextInt();
			double score = 0.0;
			double difficulty = data.nextDouble();
			double max = MIN_NUM;
			double min = MAX_NUM;
			while(data.hasNextDouble()) {
				double next = data.nextDouble();
				score += next;
				max = Math.max(max, next); // Get maximum value
				min = Math.min(min, next); // Get minimum value
			}
			score = score - max - min; // Omit the largest and smallest scores from the total score
			score = (score * difficulty) * 0.6; // Calculate Score for dive
			return score;
		}
	
	/**
	 * Read each line from input file and output scores and average by calling a method
	 * 
	 * @param fileScanner
	 */
	public static void processDives(Scanner fileScanner) {
		double score;
		int num = 0;
		double average = 0.0;
		while(fileScanner.hasNextInt()) {
			String line = fileScanner.nextLine();
			score = calculateDiveScore(line);
			num += 1;
			System.out.printf("\nThe diver's score for dive %d is: %.2f", num, score);
			average += score; 
		}
		average = average / num;
		System.out.printf("\n\nThe average score for these dives is: %.2f\n", average);
	}
	
	
	/**
	 * The main methods calls two functions,
	 * one to output the introductory message and
	 * one to calculate and displays the total scores for each dive
	 * and the average of the scores for the dives.
	 * @param args
	 * @throws FileNotFoundException
	 */
	public static void main(String[] args) throws FileNotFoundException  {
		Scanner input = new Scanner(new File("DiveData.txt"));
		printIntro();
		processDives(input);
	}

}
