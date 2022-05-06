#include <iostream>
#include<vector>
#include <gtest/gtest.h>
using namespace std;


constexpr int pw(int X,int P) {
    return (P == 0) ? 1 : X * pw(X, P - 1);
}


template <int point, int p, int...>
struct poly{};

template<int point, int p>
struct poly<point,  p>{
    static const int val = 0;
};

template <int point, int p, int x, int ... other>
struct poly<point, p, x, other...>{
    static const long long val = pw(point, p) * x + poly<point, p + 1, other...> :: val;
};


template<int point, int p, int k>
std::ostream &operator<< (std::ostream& out, poly<point, p, k> pol) {
    return out << k << " = " << pol.val;
}

template <int point, int p_, int k, int ... other>
std::ostream &operator<< (std::ostream& out, poly<point, p_, k, other...> pol) {
    vector<int> Poly__ = {{other...}};
    vector<int> Poly; Poly.push_back(k);
    for (auto i: Poly__) 
        Poly.push_back(i);


    int p = Poly.size() - 1;
    
    if (p > 0 && Poly[p] < 0)
        out << "-";

        if (abs(Poly[p]) != 1) 
            out << abs(Poly[p]);
        else if (Poly[p] == 1 && p == 0)
            out << abs(Poly[p]);


        if (p > 1)
            out << "x^" << p;
        else if (p == 1)
            out << 'x';
    p -= 1;
    
    
    for (p; p > 0; --p) {
        double val = Poly[p];
        if (Poly[p] == 0)
            continue;
        if (Poly[p] > 0)
            out << " + ";
        else   
            out << " - ";

        if (abs(Poly[p]) != 1) 
            out << abs(Poly[p]);
        else if (Poly[p] == 1 && p == 0)
            out << abs(Poly[p]);


        if (p > 1)
            out << "x^" << p;
        else if (p == 1)
            out << 'x';
    }

    if (p == 0) {
        if (Poly[0] > 0)
            out << " + " << Poly[0];
        else if (Poly[0] < 0)
            out << " - " << abs(Poly[0]);
    }

    out << " = " << pol.val << "  ( x = " << point << " )";
    return out;
}



TEST(val, A) {
    auto p = poly<4, 0, -7, -18, 81, 83, -79, -16, 80, 51>();
    EXPECT_EQ(p.val, 1133185);
}

TEST(val, B) {
    auto p = poly<1, 0, 57, 68, -21, -22, -50, -40, 89>();
    EXPECT_EQ(p.val, 81);
}

TEST(val, C) {
    auto p = poly<7, 0, -13, -30, -21, -4, 71, -7>();
    EXPECT_EQ(p.val, 50198);
}

TEST(val, D) {
    auto p = poly<2, 0, 47, 6, 56, -96, -85, -38, -13>();
    EXPECT_EQ(p.val, -3893);
}

TEST(val, E) {
    auto p = poly<2, 0, 81, -15>();
    EXPECT_EQ(p.val, 51);
}

TEST(val, F) {
    auto p = poly<5, 0, -41, 42, 53, 69, -23, 61, 54, 59, 84, 29>();
    EXPECT_EQ(p.val, 95092619);
}

TEST(val, G) {
    auto p = poly<4, 0, 54, 8, -13>();
    EXPECT_EQ(p.val, -122);
}

TEST(val, H) {
    auto p = poly<0, 0, -63, 16, 78, -68, -69, -11, -31, -27>();
    EXPECT_EQ(p.val, -63);
}

TEST(val, I) {
    auto p = poly<6, 0, 55, 95, 34, -90, 3>();
    EXPECT_EQ(p.val, -13703);
}

TEST(val, J) {
    auto p = poly<4, 0, -6, -95, -4>();
    EXPECT_EQ(p.val, -450);
}

TEST(val, K) {
    auto p = poly<1, 0, -100, -74, 40, 96>();
    EXPECT_EQ(p.val, -38);
}

TEST(val, L) {
    auto p = poly<5, 0, -31, 62, 37, -49, -13, 25, 28, 54, 46, -72>();
    EXPECT_EQ(p.val, -117934921);
}

TEST(val, M) {
    auto p = poly<4, 0, -59, -88, -72, -46>();
    EXPECT_EQ(p.val, -4507);
}

TEST(val, N) {
    auto p = poly<9, 0, -20, -29, -97>();
    EXPECT_EQ(p.val, -8138);
}

TEST(val, O) {
    auto p = poly<1, 0, 100, -68, 55, 77>();
    EXPECT_EQ(p.val, 164);
}

TEST(val, P) {
    auto p = poly<8, 0, 26, 64, -87, 26, -67, -65, -33, 70>();
    EXPECT_EQ(p.val, 135753818);
}

TEST(val, Q) {
    auto p = poly<2, 0, 8>();
    EXPECT_EQ(p.val, 8);
}

TEST(val, R) {
    auto p = poly<8, 0, -96, 6, -75, 98>();
    EXPECT_EQ(p.val, 45328);
}

TEST(val, S) {
    auto p = poly<0, 0, -1, 96, 75, 59, 95, -4, 43>();
    EXPECT_EQ(p.val, -1);
}

TEST(val, T) {
    auto p = poly<2, 0, 0, -4, 49, -55>();
    EXPECT_EQ(p.val, -252);
}

TEST(val, U) {
    auto p = poly<10, 0, 25, 5, -32, -16, 84, 63, 5, -19>();
    EXPECT_EQ(p.val, -177879125);
}

TEST(val, V) {
    auto p = poly<3, 0, -80, -19, 70, 16, -1>();
    EXPECT_EQ(p.val, 844);
}

TEST(val, W) {
    auto p = poly<5, 0, 91, 44, -74, -63, -87>();
    EXPECT_EQ(p.val, -63789);
}

TEST(val, X) {
    auto p = poly<5, 0, 63, 2, 10>();
    EXPECT_EQ(p.val, 323);
}

TEST(val, Y) {
    auto p = poly<3, 0, 5, 8, 28, -20, 93, 88, -99, 38, 46, -69>();
    EXPECT_EQ(p.val, -1016728);
}

TEST(val, Z) {
    auto p = poly<7, 0, -48, 26, 62, 93, 22, -82, -28, 22, 35, -64>();
    EXPECT_EQ(p.val, -2367329320);
}




int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}