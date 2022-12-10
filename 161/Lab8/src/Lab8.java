/**
 * This program reads a letter in ascii art from a text file and puts it into a
 * two-dimensional array, prints it once, flips it vertically, then prints it again.
 * 
 * <Author> John Shenk
 * 
 * <Date>April 14, 2020
 */
import java.io.*;
import java.util.Arrays;
import java.util.Scanner;
public class Lab8 {
	/**
	 * Reads an ASCII-art letter given a file Scanner and returns the letter
	 * as a two-dimensional char array.
	 * 
	 * @param file - A file scanner to read
	 * 
	 * @return char[][] - The two-dimensional ASCII letter to read
	 */
	public static char[][] readLetter(Scanner file) {
		char[][] letter = new char[7][15];
		for(int m = 0; m < 7; m++) {
			String line = file.nextLine();
			for(int n = 0; n < 15; n++) {
				letter[m][n] = line.charAt(n);
			}
		}
		return letter;
	}

	/**
	 * Prints a two-dimensional array of characters holding an
	 * ASCII-art letter to the screen.
	 * 
	 * @param letter - The two-dimensional ASCII letter to print
	 */
	public static void printLetter(char[][] letter) {
	    for(int a = 0; a < 7; a++) {
	    	for(int b = 0; b < 15; b++){
	    		System.out.print(letter[a][b]);
	    	}
	    System.out.println();
	    
	    }
	    System.out.println();
	}

	/**
	 * Vertically flips a two-dimensional array of characters holding
	 * an ASCII-art letter.
	 * 
	 * @param letter - The two-dimensional ASCII letter to flip.
	 */
	public static void flipLetter(char[][] letter) {
		char[][] tmp = new char[7][15];
		for(int q = 0; q < 7; q++) {
			for(int r = 0; r < 15; r++) {
				tmp[q][r] = letter [q][r];
			}
		}
		
		for(int q = 0; q < 7; q++) {
			for(int r = 0; r < 15; r++) {
				letter[7-1-q][15-1-r] = tmp[q][r];
			}
		}
	}
	
	/**
	 * The main method calls a method to read a text file and 
	 * place the ascii art letter in the file into a two-dimensional array,
	 * another to print it, and one to flip it vertically. The print method is
	 * called again to display the flipped letter.
	 * @param args
	 * @throws FileNotFoundException
	 */
	public static void main(String[] args) throws FileNotFoundException {
	    Scanner file = new Scanner(new File("letter.txt"));
	    char[][] letter = readLetter(file);
	    printLetter(letter);
	    flipLetter(letter);
	    printLetter(letter);
	}        
	        
}
