//
// Given 3 points on a plane, two of which defining a line, reflect the third across the line without messy trig division 
//

#include                <bits/stdc++.h>
#define MX_N            5001
#define mp              make_pair
#define mod7            1000000007
#define modpi           314159
#define PI              3.141592653589793238
#define pb              push_back
#define FastIO          ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define All(a)          a.begin(),a.end()
#define fi              first
#define se              second
#define ll              long long int
#define ull             unsigned long long int

int kx[8]  =            {+2, +2, -2, -2, +1, +1, -1, -1};
int ky[8]  =            {+1, -1, +1, -1, +2, -2, +2, -2};
int d9x[9] =            {+1, +1, +1, +0, +0, +0, -1, -1, -1};
int d9y[9] =            {+1, +0, -1, +1, +0, -1, +1, +0, -1};
int dx4[4] =            {+0, +0, +1, -1};
int dy4[4] =            {+1, -1, +0, +0};

ll gcd(ull a, ull b){
    return (a==0)?b:gcd(b%a,a);
}

ll lcm(ull a, ull b){
    return a*(b/gcd(a,b));
}

const long long INF = 1e18;

using namespace std;

struct point{
    double x;
    double y;

    point(double _x, double _y){
        x = _x;
        y = _y;
    }
};

double operator*(point& a, point& b){
    return (a.x * b.x) + (a.y * b.y);
}

point operator+(point& a, point& b){
    point result(a.x + b.x, a.y + b.y);
    return result;
}

point operator-(point& a, point& b){
    point result(a.x - b.x, a.y - b.y);
    return result;
}

point operator*(double& a, point& b){
    point result(a * b.x, a * b.y);
    return result;
}

point reflect_origin(point& a, point& b){
    double scale = a*b;
    scale /= b*b;
    scale *= 2.0;
    point temp = scale * b;
    point result = temp - a;
    return result;
}

point reflect_floating_line(point& a, point& b, point& target){
    b = b - a;
    target = target - a;
    point temp = reflect_origin(b, target);
    point result = temp + a;
    return result;
}

int main(){
    point a(4, 5);
    point b(5, 5.2);
    point target(5.3, 8);
    point ans = reflect_floating_line(a, b, target);
    cout << ans.x << ' ' << ans.y << endl;
}
