#include<iostream>
#include<vector>
#include<string>
using namespace std;


vector<double> parse(string str) {
    vector<double> res(1, 0);
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


        if (power > mp) {
            mp = power;
            res.resize(mp + 1, 0);
        }
        res[power] = value;
    }
    return res;
}



void print(vector<double> &poly) {
    int p = poly.size() - 1;
    
    if (poly[p] < 0)
        cout << "-";

        if (abs(poly[p]) != 1) 
            cout << abs(poly[p]);
        else if (poly[p] == 1 && p == 0)
            cout << abs(poly[p]);


        if (p > 1)
            cout << "x^" << p;
        else if (p == 1)
            cout << 'x';
    p -= 1;
    
    
    for (p; p >= 0; --p) {
        double val = poly[p];
        if (poly[p] == 0)
            continue;
        if (poly[p] > 0)
            cout << "+";
        else   
            cout << "-";

        if (abs(poly[p]) != 1) 
            cout << abs(poly[p]);
        else if (poly[p] == 1 && p == 0)
            cout << abs(poly[p]);


        if (p > 1)
            cout << "x^" << p;
        else if (p == 1)
            cout << 'x';
    }
}

int main() {
    string test1 = "-76-x^2";
    auto res = parse(test1);
    for (int i = 0; i < res.size(); ++i)
        cout << "pow: " << i << " value: " << res[i] << "\n";
    print(res);
    return 0;
}