#include<iostream>
#include<vector>
using namespace std;
#include<math.h>


class Vector {
    public:
        double x;
        double y;

        double length() {
            return sqrt(x*x + y*y);
        }

        Vector(double x_, double y_) : x(x_), y(y_) {}
};


class Point {
    public:
        double x;
        double y;

        Point() {}
        Point(double x_, double y_) : x(x_), y(y_) { }
        ~Point() { }
        Point(const Point& point_) : x(point_.x), y(point_.y){}

        void operator=(Point& point_) { 
            x = point_.x; 
            y = point_.y;
        }

        Vector operator-(Point p2) {
            return Vector(p2.x - x, p2.y - y);
        }

        bool operator==(Point p2)  {
            return (x == p2.x && y == p2.y);
        }

};


class Line {
    private:
        vector<Point> points;
    
    public:
        Line(vector<Point> points_) : points(points_){ }
        Line(std::initializer_list<Point> points_) : points(points_) {}
        ~Line() {}
        Line(const Line & line) {
            points.resize(0);
            for (const Point & point : line.points)
                points.push_back(point);
        }

        void loop() {
            points.push_back(points[0]);
        }

        vector<Point> get_points() const {
            return points;
        }

        friend std::ostream& operator<<(std::ostream& out,  Line &line);
};
std::ostream& operator<<(std::ostream& out,  Line &line) {   
    int i = 0;
	for ( auto point : line.points) {
        out << ++i << ": (" << point.x << ", " << point.y << ")\n";
    }
	return out;
}


class Chain : public Line {
    public:
        Chain(vector<Point> points_) :  Line(points_) { 
            loop();
        }
        Chain(std::initializer_list<Point> points_) : Line(points_) { 
            loop();
        }
        ~Chain() {}
        Chain(const Chain& chain) : Line(chain.get_points()) { }
};


class Polygon : public Chain {
    public:
        Polygon(vector<Point> points_) :  Chain(points_) { }
        Polygon(std::initializer_list<Point> points_) : Chain(points_) {}
        ~Polygon() {}
        Polygon(const Polygon & poly) : Chain(poly.get_points()) {}

        double Perimeter() {
            auto points = get_points();
            if (points.size() < 3)
                return 0;

            double perimeter = 0;
            Point p1 = points[0]; 
            for (int i = 1; i < points.size(); ++i) {
                perimeter += (points[i] - p1).length();
                p1 = points[i];
            }

            return perimeter;
        }

        double Area() {
            auto points = get_points();
            if (points.size() < 3)
                return 0;

            double area1, area2 = 0;
            for (int i = 0; i < points.size() - 1; ++i) {
                area1 += points[i].x * points[i + 1].y;
                area2 += points[i + 1].x * points[i].y;
            }
            return 0.5 * abs(area1 - area2);
        }
};


class Triangle : public Polygon {
    public:
        Triangle(vector<Point> &points_) :  Polygon(points_) { }
        Triangle(std::initializer_list<Point> points_) : Polygon(points_) { }
        ~Triangle() {}
        Triangle(const Triangle & triangle) : Polygon(triangle.get_points()) {}
};


class Trapezoid: public Polygon {
    public:
        Trapezoid(vector<Point> &points_) :  Polygon(points_) { }
        Trapezoid(std::initializer_list<Point> points_) : Polygon(points_) { }
        ~Trapezoid() {}
        Trapezoid(const Trapezoid & trapezoid) : Polygon(trapezoid.get_points()) {}
};



class RightPolygon : public Polygon {
    public:
        RightPolygon(vector<Point> &points_) :  Polygon(points_) { }
        RightPolygon(std::initializer_list<Point> points_) : Polygon(points_) { }
        ~RightPolygon() {}
        RightPolygon(const RightPolygon & rightPolygon) : Polygon(rightPolygon.get_points()) {}
};



int main() {
    Point p1 = Point(1, 0);    
    Point p2= Point(-1, 0);
    Point p3 = Point(sqrt(2) / 2, sqrt(2) / 2);
    // Triangle line{p1, p2, p3};
    Point p4{-sqrt(2) / 2, sqrt(2) / 2};
    Point p5{sqrt(2) / 2, -sqrt(2) / 2};
    Point p6{-sqrt(2) / 2, -sqrt(2) / 2};
    RightPolygon poly = RightPolygon{p1, p3, p4, p2, p6, p5};
        for (auto item : poly.get_points())
        cout << item.x << ", " << item.y << "\n";
    return 0;
}