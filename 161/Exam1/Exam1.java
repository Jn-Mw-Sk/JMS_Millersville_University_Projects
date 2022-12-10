/**
 * 
 * @author John Shenk
 *
 */

public class Exam1 {
	// declare constants
	public static int MINUTES_IN_AN_HOUR = 60;
	public static int SPEED = 55;
	
	
	public static void main(String[] args) {
		// Display column headings
		System.out.print("Minutes Distance\n");
		
		//declare variable
		double distance; 
		double minutes;
		
		//execute for loop
		for(int x = 5; x <= 30; x += 5){
			System.out.print(x);
			minutes = x;
			distance = Math.round(minutes/MINUTES_IN_AN_HOUR * SPEED);
			if (x <= 10) {
				System.out.printf("%10s", distance);
				System.out.println("");
			}
			else {
				System.out.printf("%10s", distance);
				System.out.println("");
			}
		
		}
		
	}

}
