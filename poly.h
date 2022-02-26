#include<iostream>
#include<vector>
using namespace std;
#include<math.h>
#include<map>


class Poly {
    private:
        map<int, double> factors;
    public:

        void update(map<int, double> f);
        explicit Poly();

        explicit Poly(map<int, double> factors_);
        Poly(const Poly&poly);


        friend std::ostream& operator<<(std::ostream& out,  Poly &poly);
        friend std::istream& operator>>(std::istream& in, Poly &poly);
        

        void operator=( Poly &poly);

        Poly operator+(Poly &poly2);


        Poly operator- (Poly &poly2);

        void operator+= (Poly &poly2);

        void operator-= (Poly &poly2);


        Poly operator/(double k);


        Poly operator*( Poly &poly2);


        void operator*=(Poly &poly2);

        void operator/=(double k) ;

        double operator[](int n);

        bool operator==(Poly &poly);

        bool operator!=(Poly &poly);
};
std::ostream& operator<<(std::ostream& out,  Poly &p_);

std::istream& operator>>(std::istream& in, Poly &p_);

