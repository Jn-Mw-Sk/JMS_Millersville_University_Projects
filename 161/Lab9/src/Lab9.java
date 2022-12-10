/**
 * This program takes two zip codes from the user and, using those zip codes, 
 * finds the longitudes and latitudes for each zip code, 
 * calculates the distance between them, and then displays the distance
 * between the zip codes accompanied by the city and state the zip codes 
 * belong to.
 * 
 * <Author> John Shenk
 * <Date> April 20, 2020
 */
import java.util.Scanner;
import java.io.*;

public class Lab9 {
	public static final double RADIUS = 3956.6;
	
	/**
	 * Counts the number of lines in the text file to give dimensions to the arrays
	 * used in the program.
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
	 * Reads the file and places the objects within the text file into arrays for zip codes, 
	 * latitudes, longitudes, and cities.
	 * @param filename
	 * @param lines
	 * @param zips
	 * @param lats
	 * @param longs
	 * @param cities
	 * @throws FileNotFoundException
	 */
	public static void readFile(String filename, String[] zips, double[] lats, double[] longs, String[] cities) 
			throws FileNotFoundException {
		Scanner input = new Scanner(new File(filename));
		String line = input.nextLine();
		int x = 0;
		while(input.hasNextLine()) {
			Scanner file = new Scanner(line);
			zips[x] = file.next();
			lats[x] = file.nextDouble();
			longs[x] = file.nextDouble();
			cities[x] = file.nextLine();
			x += 1;
			line = input.nextLine();
		}
	}
	
	/**
	 * Prompt the user to enter a ZIP code with 5 digits. 
	 * The program will keep looping until the user enters a 5 digit 
	 * zip code
	 * @param console
	 * @param prompt
	 * @return
	 */
	public static String getZipCode(Scanner console, String prompt) {
		System.out.printf(prompt);
		String zipCode = console.next();
		while(zipCode.length() < 5 || zipCode.length() > 5) {
			System.out.printf("\n" + prompt);
			zipCode = console.next();
		}
		return zipCode;
	}
	
	/**
	 * Locate the zip code entered in the array of zip codes passed in
	 * @param zips
	 * @param findZip
	 * @return
	 */
	public static int findZipCode(String[] zips, String findZip) {
		int idx = 0; 
		for(int x = 0; x < zips.length - 1; x++) {
			if(findZip.equals(zips[x])){
				idx = x;
			} 
		}
		return idx;
	}
	
	/**
	 * Returns spherical distance in miles between two points
	 * @param lat1  - Latitude of first point
	 * @param long1 - Longitude of first point
	 * @param lat2 - Latitude of second point
	 * @param long2 - longitude of second point
	 * @return
	 */
	public static double calculateDistance(double lat1, double long1,
										   double lat2, double long2) {
		lat1 = Math.toRadians(lat1);
		long1 = Math.toRadians(long1);
		lat2 = Math.toRadians(lat2);
		long2 = Math.toRadians(long2);
		double theCos = Math.sin(lat1) * Math.sin(lat2) +
				        Math.cos(lat1) * Math.cos(lat2) *
				        Math.cos(long1 - long2);
		double arcLength = Math.acos(theCos);
		return arcLength * RADIUS;
	}
	
	/**
	 * Display the distance between two zip codes while also displaying the city names,
	 * state initials, and zip codes.
	 * @param distance
	 * @param zipOne
	 * @param zipTwo
	 * @param cityOne
	 * @param cityTwo
	 */
	public static void displayDistance(double distance, String zipOne, String zipTwo, 
													 String cityOne, String cityTwo) {
		String stateOne = cityOne.substring(1, 3);
		String stateTwo = cityTwo.substring(1, 3);
		
		System.out.printf("%s, %s %s is %.2f miles from %s, %s %s", 
				cityOne.substring(4), stateOne, zipOne, distance, 
				          cityTwo.substring(4), stateTwo, zipTwo);	
	}
	
	/**
	 * The main method
	 * @param args
	 * @throws FileNotFoundException
	 */
	public static void main(String[] args) 
			throws FileNotFoundException {
		Scanner console = new Scanner(System.in);
		Scanner input = new Scanner(new File("zipcodes.txt"));
		String fileName = "zipcodes.txt";
		
		int numLines = getNumLines(input);
		
		// Declare arrays
		String[] zipCodes = new String[numLines];
		double[] latitudes = new double[numLines];
		double[] longitudes = new double[numLines];
		String[] cityNames = new String[numLines];
		
		// Call readFile method to place elements into arrays
		readFile(fileName, zipCodes, latitudes, longitudes, cityNames);
		
		// Call getZipCode Method
		String firstZip = getZipCode(console, "Please enter first zip code: ");
		String secZip = getZipCode(console, "Please enter second zip code: ");
		
		// Call method to retrieve the index for each zip code
		int idxOne = findZipCode(zipCodes, firstZip);
		int idxTwo = findZipCode(zipCodes, secZip);
		
		// Calls a method to calculate the distance between the two zip codes
		// using the coordinates of each zip code
		double distance = calculateDistance(latitudes[idxOne], longitudes[idxOne], 
											 latitudes[idxTwo], longitudes[idxTwo]);
											 
		// Calls a method to display the distance between two citites
		//while also displaying the city name, state initials, and zip code.
		displayDistance(distance, firstZip, secZip,
			  cityNames[idxOne], cityNames[idxTwo]);								 
	}
	

}
