
public class Square {
	/**DeclareConstants**/
	private final int NUM_OF_SIDES = 4;
	
	/** Square fields (aka State variables) **/
	public double x;
	public double y; 
	Point origin = new Point(x, y);
	double size;
	
	/** Constructor **/
	/**
	 * Square constructor
	 * @param initialX - Origin point's X value
	 * @param initialY - Origin point's Y value
	 * @param initialSize - Size of the Square
	 */
	public Square(double initialX, double initialY, double initialSize) {
		origin.x = initialX;
		origin.y = initialY;
		size = initialSize;
	}     
	
	// Accessor method: Returns the area of the square
	double area() {
		return(size * size);
	}
	
	// Accessor method: Returns the perimeter of the square
	double perimeter() {
		return(size * NUM_OF_SIDES);
	}
	
	// Accessor Method: Returns the points along the square's perimeter
		public Point[] getPoints() {
			Point[] points = new Point[4];
			points[0] = new Point(origin.x, origin.y);
			points[1] = new Point(origin.x + size, origin.y);
			points[2] = new Point(origin.x + size, origin.y - size);
			points[3] = new Point(origin.x, origin.y - size);
			return points;
		}
		
	// Accessor Method: Returns a String representation of this Square
	public String toString() {
		String ret = "[";	// Start with array bracket
		Point[] points = getPoints();  // get points of the shape
		for (int i=0; i < points.length; i++) {  // loop to add to ret string
			ret += points[i].toString();
			if (i+1 < points.length) {   // fence-post variant
				ret += ", ";
			}
		}
		ret += "]";  // Close out array bracket
		return ret; 
	}
}
