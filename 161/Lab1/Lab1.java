
public class Lab1 {
	
	// This method produces the letter "M" in Ascii art
	public static void drawM() {
		System.out.println("M      M");
		System.out.println("MM    MM");
		System.out.println("M M  M M");
		System.out.println("M  MM  M");
		System.out.println("M      M");
		System.out.println("M      M");
		System.out.println("M      M");
		System.out.println("M      M");
	}
	
	// This method produces the letter "I" in Ascii art
	public static void drawI() {
		System.out.println(" IIIIII ");
		System.out.println("   II   ");
		System.out.println("   II   ");
		System.out.println("   II   ");
		System.out.println("   II   ");
		System.out.println("   II   ");
		System.out.println("   II   ");
		System.out.println(" IIIIII ");
	}
	
	// This method produces the letter "S" in Ascii art
	public static void drawS() {
		System.out.println(" SSSSSS ");
		System.out.println("S      S");
		System.out.println("S       ");
		System.out.println(" SSSSSS ");
		System.out.println("       S");
		System.out.println("       S");
		System.out.println("S      S");
		System.out.println(" SSSSSS ");
	}
	
	// This method produces the letter "P" in Ascii art
	public static void drawP() {
		System.out.println("PPPPPPP ");
		System.out.println("P      P");
		System.out.println("P      P");
		System.out.println("PPPPPPP ");
		System.out.println("P       ");
		System.out.println("P       ");
		System.out.println("P       ");
		System.out.println("P       ");
	}
	
	// This method produces a blank line
	public static void drawBlankLine() {
		System.out.println();
	}
	
	// This main method produces the word "Mississippi" by calling methods for
	// producing letters in Ascii art and blank lines
	public static void main(String[] args) {
		drawM();
		drawBlankLine();
		drawI();
		drawBlankLine();
		drawS();
		drawBlankLine();
		drawS();
		drawBlankLine();
		drawI();
		drawBlankLine();
		drawS();
		drawBlankLine();
		drawS();
		drawBlankLine();
		drawI();
		drawBlankLine();
		drawP();
		drawBlankLine();
		drawP();
		drawBlankLine();
		drawI();
	}

}
