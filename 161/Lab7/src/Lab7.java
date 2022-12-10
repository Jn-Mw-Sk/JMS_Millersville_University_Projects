/**
 * This program calculates the scores for consecutive dives, omitting the highest and lowest scores
 * from each dive, and displays the scores. The program also displays an average for the total scores
 * and the top three scores of all of the dives.
 * 
 * The scores are read from a text file line-by-line with each line containing a dive number, 
 * a difficulty number, and 7 scores from 7 judges, ranging in score from 0-10.
 * 
 * <Author> John M. Shenk
 * 
 * <Date> April 2, 2020
 */

import java.io.*;
import java.util.Arrays;
import java.util.Scanner; 

public class Lab7 {
	public static final double MAX_NUM = Double.MAX_VALUE;
	public static final double MIN_NUM = Double.MIN_VALUE;
	
	
	// Print the introductory message
	public static void printIntro() {
		System.out.printf("Welcome to the Diver Scoring program. This program will calculate an\n");
		System.out.printf("  overall score for a diver, based on individual dives.\n");
	}
	
	/**
	 * Determines the number of lines within the text document
	 * @param fileScanner
	 * @return
	 */
	public static int getNumLines(Scanner fileScanner) {
		int lines = 0;
		while(fileScanner.hasNextLine()) {
			String line = fileScanner.nextLine();
			lines += 1;
		}
		return lines;
	}

	/**
	 * This method sorts the items in the <scores> array from largest to smallest
	 * to more easily display them in the top three scores line.
	 * @param arr
	 */
	public static void flipScores(double[] arr) {
		for(int idx = 0; idx < arr.length/2; idx++) {
			double tmp = arr[idx];
			arr[idx] = arr[arr.length-1-idx];
			arr[arr.length-1-idx] = tmp;
		}
		
		System.out.printf("\nThe top three scores are: %.2f, %.2f, and %.2f", arr[0], arr[1], arr[2]);

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
	public static void processDives(Scanner fileScanner, int lines) {
		double score;
		int num = 0;
		double average = 0.0;
		double[] scores= new double[lines];
		while(fileScanner.hasNextInt()) {
			String line = fileScanner.nextLine();
			score = calculateDiveScore(line);
			num += 1;
			System.out.printf("\nThe diver's score for dive %d is: %.2f", num, score);
			average += score; 
			scores[num - 1] = score; 
		}
		average = average / num;
		System.out.printf("\n\nThe average score for these dives is: %.2f\n", average);
		Arrays.sort(scores);
		flipScores(scores);
	}
	
	
	/**
	 * The main methods calls two functions,
	 * one to output the introductory message,
	 * one to get the number of line in the text document, and
	 * one to calculate and displays the total scores for each dive,
	 * the average of the scores for the dives, and the top three scores
	 * 
	 * @param args
	 * @throws FileNotFoundException
	 */
	public static void main(String[] args) throws FileNotFoundException  {
		Scanner input = new Scanner(new File("DiveData.txt"));
		int numLines = getNumLines(input);
		printIntro();
		Scanner input2 = new Scanner(new File("DiveData.txt"));
		processDives(input2, numLines);
	}

}
