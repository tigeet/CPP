#include<iostream>
#include<vector>
using namespace std;
#include<math.h>

class GeometryException : public exception {
    private:
        string message;
    public:
        GeometryException(string message_) : message(message_) {}
        virtual const char* what() const throw () {
            return message.c_str();
        }
};

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
        Point() { }
        Point(double x_, double y_) {
            x = x_;
            y = y_;
        }

        ~Point() { }

        void operator=(Point p2) {
            x = p2.x;
            y = p2.y;
        }

        // double operator-(Point p2) {
        //     return sqrt( pow(p2.x - x , 2) + pow(p2.y - y , 2));
        // }

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
        vector<Point> & get_points() {
            return points;
        }

        Line(vector<Point> &points_) : points(points_){ }

        Line(std::initializer_list<Point> points_) 
        : points(points_) {}

        Line(const Line & line) {
            points.resize(0);
            for (const Point & point : line.points)
                points.push_back(point);
        }

        void add(Point &point) {
            points.push_back(point);
        }

        friend std::ostream& operator<<(std::ostream& out, const Line &line);
};

std::ostream& operator<<(std::ostream& out, const Line &line) {   
    int i = 0;
	for (const auto point : line.points) {
        out << ++i << ": (" << point.x << ", " << point.y << ")\n";
    }
	return out;
}



class Chain : public Line {
    private:
        vector<Point> points;
    public:
        Chain(vector<Point> &points_) :  Line(points_) { 
                add(points_[0]);
        }

        Chain(std::initializer_list<Point> points_) : Line(points_) {}
};


class Polygon : public Chain {
    public:
        Polygon(vector<Point> &points_) :  Chain(points_) { }

        Polygon(std::initializer_list<Point> &points_) : Chain(points_) {}
        
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

        Triangle(std::initializer_list<Point> points_) : Polygon(points_) {
            if (points_.size() != 3) 
                throw GeometryException("Cannot create a triangle without 3 vertices");
        }
};

class Trapezoid: public Polygon {
    public:
        Trapezoid(vector<Point> &points_) :  Polygon(points_) { }

        Trapezoid(std::initializer_list<Point> points_) : Polygon(points_) {}
};

class RightPolygon : public Polygon {
    public:
        RightPolygon(vector<Point> &points_) :  Polygon(points_) { }

        RightPolygon(std::initializer_list<Point> points_) : Polygon(points_) {}
};




int main() {
    Point p1{1, 0};
    Point p2{-1, 0};
    Point p3{sqrt(2) / 2, sqrt(2) / 2};
    Point p4{-sqrt(2) / 2, sqrt(2) / 2};
    Point p5{sqrt(2) / 2, -sqrt(2) / 2};
    Point p6{-sqrt(2) / 2, -sqrt(2) / 2};
    RightPolygon poly = RightPolygon{p1, p3, p4, p2, p6, p5};
    return 0;
}