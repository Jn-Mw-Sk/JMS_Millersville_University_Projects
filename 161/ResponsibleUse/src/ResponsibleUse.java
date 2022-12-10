/**
 * This program presents the user with 5 questions regarding Millersville University's 
 * Policy for Responsible Use. THe program displays the user's score with a percentage 
 * based on how they answered the questions
 * 
 * @author shenk
 *
 */
import java.util.Scanner;

public class ResponsibleUse {

	//declare constants
	public static final String QUESTION_1 = "Which is NOT a purpose Millersville University makes electronic resources available to faculty, staff, and students?";
	public static final String RESPONSE_1A = "For conducting official University business.";
	public static final String RESPONSE_1B = "For academic scholarship.";
	public static final String RESPONSE_1C = "For research.";
	public static final String RESPONSE_1D = "For student access to social media sites.";
	public static final String ANSWER_1 = "d";  

	public static final String QUESTION_2 = "Which usage is NOT described in the \"Policy for Responsible Use\"?";
	public static final String RESPONSE_2A = "Electronic Mail";
	public static final String RESPONSE_2B = "Network Use";
	public static final String RESPONSE_2C = "Crypto-currency";
	public static final String RESPONSE_2D = "User Accounts";
	public static final String ANSWER_2 = "c";  
	
	public static final String QUESTION_3 = "Under which topic is improper printing of documents covered?";
	public static final String RESPONSE_3A = "Electronic Mail";
	public static final String RESPONSE_3B = "Network Use";
	public static final String RESPONSE_3C = "Webpages";
	public static final String RESPONSE_3D = "Software";
	public static final String ANSWER_3 = "b";  
	
	public static final String QUESTION_4 = "The \"Privacy and Confidentiality of Electronic Media\" portion of the policy states that?";
	public static final String RESPONSE_4A = "The University may be required to provide information stored in its system if so compelled by a court order.";
	public static final String RESPONSE_4B = "Your privacy should be presumed at all times.";
	public static final String RESPONSE_4C = "The University will routinely monitor and review the contents of your user accounts.";
	public static final String RESPONSE_4D = "The University does not abide by recent court decisions regarding privacy and \"Right to Know.\"";
	public static final String ANSWER_4 = "a";  
	
	public static final String QUESTION_5 = "Consequences of violating the policy includes?";
	public static final String RESPONSE_5A = "Loss of access to University computing systems pending disciplinary process.";
	public static final String RESPONSE_5B = "Possible prosecution under State laws or local laws.";
	public static final String RESPONSE_5C = "Loss of access to University computing resources after the disciplinary process.";
	public static final String RESPONSE_5D = "All of the above.";
	public static final String ANSWER_5 = "d";  
	
	/**
	 * 
	 *  Prompts the user with a supplied question along with supplied multiple choice responses,
	 * gets their response and if the response is correct given the supplied answer returns the
	 * appropriate points for that correct answer else 0 points are returned.
	 * 
	 * @param console
	 * @param questionNum
	 * @param question
	 * @param respA
	 * @param respB
	 * @param respC
	 * @param respD
	 * @param answer
	 * @return
	 * 
	 */
	public static int askQuestion(Scanner console, int questionNum, String question, String respA, String respB, String respC, String respD, String answer) {
		int score = 0;
		
		// Display question number and responses and a line to input an answer
		System.out.println("Question #" + questionNum + ": " + question);
		System.out.printf("%11s", "a. ");
		System.out.print(respA + "\n");
		System.out.printf("%11s", "b. ");
		System.out.print(respB + "\n");
		System.out.printf("%11s", "c. ");
		System.out.print(respC + "\n");
		System.out.printf("%11s", "d. ");
		System.out.print(respD + "\n");
		System.out.print("Please enter a, b, c, or d: ");
		String userAnswer = console.nextLine();
		
		// Determine the value of the int variable to return based on the answer
		if (userAnswer.equals(answer)) {
			score = 20;
		} else {
			score = 0;
		}
		System.out.println("");
		// Return the score value
		return score;
	}
	
	
	/**
	 * This method displays the user's score  on a scale from 0% to 100%
	 * depending on how they answered the questions
	 * 
	 * @param totalScore
	 */
	public static void printScore(int totalScore) {
		System.out.println("Your score: " + totalScore + "%");
	}
	
	
	/** 
	 * The main method calls a methods to display 5 questions with possible answers. 
	 * The main methods adds the total score based on the value the askQuestion method returns to it,
	 * and then passes the total score to a method to display the score with a "%" following
	 * @param args
	 */
	public static void main(String[] args) {
		int totalScore = 0;
		Scanner console = new Scanner(System.in);
		
		// Call methods to display questions and responses and return an int score value
		totalScore += askQuestion(console, 1, QUESTION_1, RESPONSE_1A, RESPONSE_1B, RESPONSE_1C, RESPONSE_1D, ANSWER_1);
		totalScore += askQuestion(console, 2, QUESTION_2, RESPONSE_2A, RESPONSE_2B, RESPONSE_2C, RESPONSE_2D, ANSWER_2);
		totalScore += askQuestion(console, 3, QUESTION_3, RESPONSE_3A, RESPONSE_3B, RESPONSE_3C, RESPONSE_3D, ANSWER_3);
		totalScore += askQuestion(console, 4, QUESTION_4, RESPONSE_4A, RESPONSE_4B, RESPONSE_4C, RESPONSE_4D, ANSWER_4);
		totalScore += askQuestion(console, 5, QUESTION_5, RESPONSE_5A, RESPONSE_5B, RESPONSE_5C, RESPONSE_5D, ANSWER_5);
		
		// Call a method to display the user's score based on how they answered the questions
		printScore(totalScore);
	}
}
