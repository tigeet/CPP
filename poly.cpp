#include"poly.h"


        void Poly::update(map<int, double> f) {
            factors = f;
        }
        Poly::Poly() {}

        Poly::Poly(map<int, double> factors_) : factors(factors_) {}




        

        void Poly::operator=( Poly &poly) {
            factors = poly.factors;
        }

        Poly::Poly(const Poly&poly) {
            factors = poly.factors;
        }

        Poly Poly::operator+(Poly &poly2) {
            int n = max(factors.size(), poly2.factors.size());
            map<int, double> res;
            for (int i = 0; i < n; ++i) {
                res[i] = poly2.factors[i] + factors[i];
            }
            return Poly(res);
        }


        Poly Poly::operator- (Poly &poly2) {
            int n = max(factors.size(), poly2.factors.size());
            map<int, double> res;
            for (int i = 0; i < n; ++i) {
                res[i] = factors[i] - poly2.factors[i];
            }
            return Poly(res);
        }

        void Poly::operator+= (Poly &poly2) {
            int n = max(factors.size(), poly2.factors.size());
            for (int i = 0; i < n; ++i) {
                factors[i] = factors[i] + poly2.factors[i];
            }
        }

        void Poly::operator-= (Poly &poly2) {
            int n = max(factors.size(), poly2.factors.size());
            for (int i = 0; i < n; ++i) {
                factors[i] = factors[i] - poly2.factors[i];
            }
        }


        Poly Poly::operator/(double k) {
            //k == 0
            int n = factors.size();
            map<int, double> res;
            for (int i = 0; i < factors.size(); ++i) {
                res[i] = factors[i] / k;
            }
            return Poly(res);
        }


        Poly Poly::operator*( Poly &poly2) {
            map<int, double> res;
            double val = 0;
            int m = 0;
            for (int pa = 0; pa < factors.size(); ++pa) {
                for (int pb = 0; pb< poly2.factors.size(); ++pb) {
                    val = factors[pa] * poly2.factors[pb];
                    res[pa + pb] += val;
                }
            }
            return Poly(res);
        }


        void Poly::operator*=(Poly &poly2) {
            map<int, double> res;
            double val = 0;
            int m = 0;
            for (int pa = 0; pa < factors.size(); ++pa) {
                for (int pb = 0; pb< poly2.factors.size(); ++pb) {
                    if (pa + pb > m) {
                        m = pa + pb;
                    }
                    val = factors[pa] * poly2.factors[pb];
                    res[pa + pb] += val;
                }
            }
            update(res);
        }

        void Poly::operator/=(double k) {
        // k == 0
            for (int i = 0; i < factors.size(); ++i) {
                factors[i] = factors[i] / k;
            }
        }

        double Poly::operator[](int n) {
            if (n < factors.size())
                return factors[n];
            else   
                return 0;
        }

        bool Poly::operator==(Poly &poly) {
            int n = max(factors.size(), poly.factors.size());
            for (int i = 0; i < n; ++i) {
                if (factors[i] != poly.factors[i])
                    return false;
            }
            return true;
        }

        bool Poly::operator!=(Poly &poly) {
            int n = max(factors.size(), poly.factors.size());
            for (int i = 0; i < n; ++i) {
                if (factors[i] != poly.factors[i])
                    return true;
            }
            return false;
        }

std::ostream& operator<<(std::ostream& out,  Poly &p_) {
    auto poly = p_.factors;
    int p = poly.size() - 1;
    
    if (p > 0 && poly[p] < 0)
        out << "-";

        if (abs(poly[p]) != 1) 
            out << abs(poly[p]);
        else if (poly[p] == 1 && p == 0)
            out << abs(poly[p]);


        if (p > 1)
            out << "x^" << p;
        else if (p == 1)
            out << 'x';
    p -= 1;
    
    
    for (p; p > 0; --p) {
        double val = poly[p];
        if (poly[p] == 0)
            continue;
        if (poly[p] > 0)
            out << " + ";
        else   
            out << " - ";

        if (abs(poly[p]) != 1) 
            out << abs(poly[p]);
        else if (poly[p] == 1 && p == 0)
            out << abs(poly[p]);


        if (p > 1)
            out << "x^" << p;
        else if (p == 1)
            out << 'x';
    }

    if (p == 0) {
        if (poly[0] > 0)
            out << " + " << poly[0];
        else if (poly[0] < 0)
            out << " - " << abs(poly[0]);
    }
    return out;
}


std::istream& operator>>(std::istream& in, Poly &p_) {
    string str;
    in >> str;
    map<int, double> res;
    int mp = 0;
    int sign = 1;
    int l = 0, r = 0;
    while (r < str.length()) {
        if (str[r] == '+') {
            // cout << '+' << " ";
            sign = 1;
            ++r;
            ++l;
        }
        if (str[r] == '-') {
            // cout << '-' << " ";
            sign = -1;
            ++r;
            ++l;
        }
        // cout << "pos: " << l << ", " << r << "  ";
        double value = 1;
        // reading the value, default = 1;
        while (r < str.length() && str[r] != 'x' && str[r] != '+' && str[r] != '-')
            ++r;
        if (r - l) 
            value = atof(str.substr(l, r - l).c_str());
        value = value * sign;

        int power = 0;
        //reading the pow, deafult = 0;
        if (str[r] == 'x') {
            if (r + 1 < str.length() && str[r + 1] == '^') {
                l = r = r + 2;
                while (r < str.length() && str[r] != '+' && str[r] != '-')
                    ++r;
                power = atof(str.substr(l, r - l).c_str());
                l = r;
            } else {
                power = 1;
                l = r = r + 1;
            }
        } else {
            l = r;
        }
        res[power] = value;
    }
    p_.factors = res;
    return in;
}

int main() {
    // string test = "-5x^3+17x^21-1x+123";
    // 5x^4 - 3x^3 + 3;  5 -3 0 0 3
    // x^3 + 2x^2 - x;   1 2 -1 0
    // string test2 = "-51x^12";
    // map<int, double> seq1 = {3, 0, 0, -3, -5};
    // map<int, double> seq2 = {0, -1, 2, 1};
    // Poly poly1 = Poly(seq1);
    // Poly poly2 = Poly(seq2);
    // Poly poly3 = Poly(seq1);
    // poly3 = poly2;
    Poly poly4, poly5;
    cin >> poly4 >> poly5;
    poly4 *= poly5;
    cout << poly4 << "\n" << poly5;
    // cout << (poly3 == poly2) << "\n" << (poly3 == poly1) << "\n" << (poly3 != poly1) << '\n';
    // poly3 += poly2;
    // poly1 *= 2;
    // cout << poly1;

    return 0;
}