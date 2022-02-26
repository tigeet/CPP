#include"geo.h"



Vector::Vector(double x_, double y_) : x(x_), y(y_) {}

double Vector::length() {
    return sqrt(x*x + y*y);
}

bool Vector::isParallel(Vector&v2) {
    if (x == 0.0 && v2.x == 0.0)
        return true;
    if (y == 0.0 && v2.y == 0.0)
        return true;  
    if (v2.x / x == v2.y / y)
        return true;
    return false;
}


Point::Point() {};
Point::Point(double x_, double y_) : x(x_), y(y_) { }
Point::~Point() { }
Point::Point( const Point& point_) : x(point_.x), y(point_.y){}

void Point::operator=(Point& point_) { 
    x = point_.x; 
    y = point_.y;
}

Vector Point::operator-(Point p2) {
    return Vector(p2.x - x, p2.y - y);
}

bool Point::operator==(Point p2)  {
    return (x == p2.x && y == p2.y);
}


    Line::Line() {}
    Line::Line(vector<Point> points_) : points(points_){ }
    Line::Line(std::initializer_list<Point> points_) : points(points_) {}
    Line::Line(const Line & line) {
        points.resize(0);
        for ( Point & point : line.get_points())
            points.push_back(point);
    }

    void Line::loop() {
        points.push_back(points[0]);
    }

    vector<Point> Line::get_points() const{
        vector<Point> res = points;
        return res;
    }

std::ostream& operator<<(std::ostream& out,  Line &line) { 
    int i = 0;
	for ( auto point : line.points) {
        out << ++i << ": (" << point.x << ", " << point.y << ")\n";
    }
	return out;
}

Chain::Chain() : Line() {}
Chain::Chain(vector<Point> points_) :  Line(points_) { 
    loop();
}
Chain::Chain(std::initializer_list<Point> points_) : Line(points_) { 
    loop();
}
Chain::~Chain() {}

    






        Polygon::Polygon(vector<Point> points_) :  Chain(points_) { }
        Polygon::Polygon(std::initializer_list<Point> points_) : Chain(points_) {}
        Polygon::~Polygon() {}
        Polygon::Polygon(const Polygon & poly) : Chain(poly.get_points()) {}

        double Polygon::Perimeter() {
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

        double Polygon::Area() {
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



        Triangle::Triangle(vector<Point> &points_) :  Polygon(points_) { }
        Triangle::Triangle(std::initializer_list<Point> points_) : Polygon(points_) { 
            auto points = get_points();
            if (points.size() != 4)
                throw;
            auto v1 = points[1] - points[0];
            auto v2 = points[2] - points[1];
            auto v3 = points[0] - points[2];
            if (v1.length() + v2.length() <= v3.length() ||
                v2.length() + v3.length() <= v1.length() || 
                v1.length() + v3.length() <= v2.length()) {
                throw;
            }
        }
        Triangle::~Triangle() {}
        Triangle::Triangle(const Triangle & triangle) : Polygon(triangle.get_points()) {}




        Trapezoid::Trapezoid(vector<Point> &points_) :  Polygon(points_) { }
        Trapezoid::Trapezoid(std::initializer_list<Point> points_) : Polygon(points_) { 
            auto points = get_points();
            if (points.size() != 5)
                throw;
            auto v1 = points[1] - points[0];
            auto v2 = points[2] - points[1];
            auto v3 = points[2] - points[3];
            auto v4 = points[3] - points[0];
            if (v1.isParallel(v3) == false && v2.isParallel(v4) == false) 
                throw;
        }
        
        Trapezoid::~Trapezoid() {}
        Trapezoid::Trapezoid(const Trapezoid & trapezoid) : Polygon(trapezoid.get_points()) {}


RightPolygon::RightPolygon(vector<Point> &points_) :  Polygon(points_) {  }
RightPolygon::RightPolygon(std::initializer_list<Point> points_) : Polygon(points_) {
    auto points = get_points();
    if (points.size() < 4)
        throw;
    auto side = (points[1] - points[0]).length();
    for (int i = 2; i < points.size(); ++i) {
        auto length = (points[i] - points[i - 1]).length();
        cout << length << "\n";
        if (length != side) 
            throw;
    }
}
RightPolygon::~RightPolygon() {}
RightPolygon::RightPolygon(const RightPolygon & rightPolygon) : Polygon(rightPolygon.get_points()) {}

int main() {
    Point p1 = Point(1, 0);    
    Point p2= Point(-1, 0);
    Point p3 = Point(sqrt(2) / 2, sqrt(2) / 2);
    Triangle line{p1, p2, p3};
    Point p4{-sqrt(2) / 2, sqrt(2) / 2};
    Point p5{sqrt(2) / 2, -sqrt(2) / 2};
    Point p6{-sqrt(2) / 2, -sqrt(2) / 2};
    Triangle tr = Triangle{p1, p2, p3};
    // cout << tr.Area();
    RightPolygon tp = RightPolygon{p3, p4, p6, p5}; // трапеция
    RightPolygon poly = RightPolygon{p1, p3, p4, p2, p6, p5};

    //     for (auto item : poly.get_points())
    //     cout << item.x << ", " << item.y << "\n";
    return 0;
}