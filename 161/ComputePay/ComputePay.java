
public class ComputePay {

	public static void main(String[] args) {
		// Calculate pay at work based on hours worked each day
		
		// Declare variables
		int mondayHours = 4;
		int tuesdayHours = 5;
		int wednesdayHours = 8;
		int thursdayHours = 4;
	
		int totalHours = mondayHours + tuesdayHours + wednesdayHours + thursdayHours;
		double taxRate = 0.20;
		double hourlySalary = 8.75;
		
		// Calculate and display total hours worked
		System.out.println("My total hours worked:");
		System.out.println(totalHours);
		
		// Display hourly salary
		System.out.println("My hourly salary:");
		System.out.println(hourlySalary);
		
		// Calculate and display total pay
		System.out.println("My total pay:");
		double totalPay = totalHours * hourlySalary;
		System.out.println(totalPay);
		
		// Calculate and display taxes owed
		System.out.println("My taxes owed:"); //20% tax
		System.out.println(totalPay * taxRate);
	}

}
