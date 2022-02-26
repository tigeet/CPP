#include<iostream>
#include<vector>
using namespace std;
#include<math.h>


class Vector {
    public:
        double x;
        double y;

        explicit Vector(double x_, double y_);

        double length();

        bool isParallel(Vector&v2);
};


class Point {
    public:
        double x;
        double y;

        explicit Point();
        explicit Point(double x_, double y_);
        ~Point();
        Point(const Point& point_);

        void operator=(Point& point_);

        Vector operator-(Point p2);

        bool operator==(Point p2) ;

};


class Line {
    private:
        vector<Point> points;
    
    public:
        Line(vector<Point> points_);
        Line(std::initializer_list<Point> points_);
        ~Line() {}
        Line(const Line & line);
        Line();
        void loop();

        vector<Point> get_points() const;

        friend std::ostream& operator<<(std::ostream& out,  Line &line);
};
std::ostream& operator<<(std::ostream& out,  Line &line);


class Chain : public Line {
    public:
        explicit Chain();
        explicit Chain(vector<Point> points_);
        explicit Chain(std::initializer_list<Point> points_);
        ~Chain();
        Chain(const Chain& chain) ;
};


class Polygon : public Chain {
    public:
        Polygon(vector<Point> points_);
        Polygon(std::initializer_list<Point> points_);
        ~Polygon();
        Polygon(const Polygon & poly) ;
        Polygon();
        double Perimeter();
        double Area();
};


class Triangle : public Polygon {
    public:
        Triangle(vector<Point> &points_);
        Triangle(initializer_list<Point> points_);
        ~Triangle();
        Triangle(const Triangle & triangle);
};


class Trapezoid: public Polygon {
    public:
        Trapezoid(vector<Point> &points_) ;
        Trapezoid(std::initializer_list<Point> points_);
        ~Trapezoid();
        Trapezoid(const Trapezoid & trapezoid);
};



class RightPolygon : public Polygon {
    public:
        RightPolygon(vector<Point> &points_);
        RightPolygon(std::initializer_list<Point> points_) ;
        ~RightPolygon() ;
        RightPolygon(const RightPolygon & rightPolygon);
};