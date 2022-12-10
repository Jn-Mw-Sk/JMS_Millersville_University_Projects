
public class StarFigures {

	// This method creates two lines of input composed of two rows of 5 asterisks each.
	public static void DrawLines()
	{
		System.out.println("*****");
		System.out.println("*****");
	}
	
	// This method creates an "X" out of asterisks
	public static void DrawX()
	{
		System.out.println(" * * ");
		System.out.println("  *  ");
		System.out.println(" * * ");
	}
	
	// This method creates a vertical line of 3 asterisks
	public static void DrawVertical()
	{
		System.out.println("  *  ");
		System.out.println("  *  ");
		System.out.println("  *  ");
	}
	
	// This method creates a blank line
	public static void DrawBlank()
	{
		System.out.println();
	}
	
	// The main method puts all of these together to create the image in the textbook
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		DrawLines();
		DrawX();
		DrawBlank();
		DrawLines();
		DrawX();
		DrawLines();
		DrawBlank();
		DrawVertical();
		DrawLines();
		DrawX();
	}

}
