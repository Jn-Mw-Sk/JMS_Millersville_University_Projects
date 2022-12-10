
public class Rectangle {
    
	/** Rectangle fields (aka State variables) **/
	public double x;
	public double y;
	
	Point origin = new Point(x, y);
	double width;
	double height;

	/** Constructor **/
	/**
	 * Rectangle Constructor
	 * @param initialX - Origin point's X value 
	 * @param initialY - Origin point's Y value
	 * @param initialWidth - Rectangle width
	 * @param initialHeight - Rectangle height
	*/
	public Rectangle(double initialX, double initialY, double initialWidth, double initialHeight) {
		origin.x = initialX;
		origin.y = initialY;
		width = initialWidth;
		height = initialHeight;
	}              
	
	//Accessor method: Returns the area of the rectangle
	double area() {
		return(width * height);
	}
	
	//Accessor method: Returns the perimeter of the rectangle
	double perimeter() {
		return((width * 2) + (height * 2));
	}
	
	// Accessor Method: Returns the points along the rectangle's perimeter
	public Point[] getPoints() {
		Point[] points = new Point[4];
		points[0] = new Point(origin.x, origin.y);
		points[1] = new Point(origin.x + width, origin.y);
		points[2] = new Point(origin.x + width, origin.y - height);
		points[3] = new Point(origin.x, origin.y - height);
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
