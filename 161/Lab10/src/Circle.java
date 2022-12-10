
public class Circle {
	/** Constants **/
	private final double PI = 3.14159;
	
	public int x;
	public int y;
	
	/** Fields (aka State variables) **/
	Point origin = new Point(x, y);
	double radius;
	
	/** Constructor **/
	/**
	 * Constructs a Circle given origin's x, y and radius
	 * @param initialX - Origin point's x value
	 * @param initialY - Origin point's y value
	 * @param initialRadius - Radius of the circle
	 */
	public Circle( double initialX, double initialY, double initialRadius) {
		origin.x = initialX;
		origin.y = initialY;
		radius = initialRadius;
	}
	
	/** Methods (Behavior of the class) **/
	
	// Accessor Method: Returns the area of the Circle
	public double area() {
		return (PI * radius * radius);
	}
	
	// Accessor Method: Return perimeter (aka circumference) of the Circle
	public double perimeter() {
		return ( 2.0 * PI * radius ); 
	}
	
	// Accessor Method: Returns the points along the Circle's circumference
	public Point[] getPoints() {
		Point[] points = new Point[360];
		for (int i=0; i<points.length; i++) {
			double angle = PI * 2.0 * (double)i / 360.0;  // angle in radians
			points[i] = new Point( origin.x + radius * Math.cos(angle), origin.y + radius * Math.sin(angle));
		}
		return points;
	}
	
	// Accessor Method: Returns a String representation of this Circle
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
