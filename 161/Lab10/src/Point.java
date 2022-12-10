
public class Point {
	
	//**Point fields (aka State Variables)**//
	public double x;
	public double y;
	
	// Constructor
    public Point(double x, double y) {
		this.x = x;
		this.y = y;
	}

	/** Methods (Behavior of the class) **/
	
	// Accessor Method: Returns the area of the Point (points have no area)
	public double area() {
		return (0.0);
	}
	
	// Accessor Method: Return perimeter of the Point (points have no perimeter)
	public double perimeter() {
		return ( 0.0 ); 
	}
	
	// Accessor Method: Returns the single point
	public Point[] getPoints() {
		Point[] points = new Point[1];   // Just one point for a Point
		points[0] = this;  // this refers to this object
		return points;
	}
	
	// Accessor Method: Returns a String representation of this Point
	public String toString() {
		return String.format("(%.2f, %.2f)", x, y);
	}
}
