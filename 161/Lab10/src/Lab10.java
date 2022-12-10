/**
 * This program outputs the point of a single point, 
 * the points, area, and perimeter of a circle,
 * the points, area, and perimeter of a square,
 * and the points, area, and perimeter of a rectangle.
 * 
 * <Author> John Shenk
 * <Date> April 23, 2020
 */
public class Lab10 {

	public static void main(String[] args) {
		// Point
		Point p = new Point(15, 2);
		System.out.printf("\nCoordinates of the point are: %s\n", p.toString());
		System.out.printf("Area of the point is: %.2f\n", p.area());
		System.out.printf("Perimeter of the point is: %.2f\n\n", p.perimeter());
				
		// Circle
		Circle c = new Circle(10, 5, 3);
		System.out.printf("Points of the circle are: %s\n", c.toString());
		System.out.printf("Area of the circle is: %.2f\n", c.area());
		System.out.printf("Perimeter of the circle is: %.2f\n\n", c.perimeter());
				
		// Square
		Square s = new Square(0, 7, 6);
		System.out.printf("Points of the square are: %s\n", s.toString());
		System.out.printf("Area of the square is: %.2f\n", s.area());
		System.out.printf("Perimeter of the square is: %.2f\n\n", s.perimeter());

		// Rectangle
		Rectangle r = new Rectangle(2, 14, 12, 4);
		System.out.printf("Points of the rectangle are: %s\n", r.toString());
		System.out.printf("Area of the rectangle is: %.2f\n", r.area());
		System.out.printf("Perimeter of the rectangle is: %.2f\n\n", r.perimeter());
	}

}
