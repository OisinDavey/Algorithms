//
// Implementation of golden section search, wherein we do ternary search except with minimising calls to f(x)
//

#include                <bits/stdc++.h>
#define MX_N            200001
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

int n;
int a[MX_N];

double f(double x){
    return -3.0*x*x - 8*x + 2;
}

double phi = 1.618033989;
double inv_phi = 0.618033989;

double calc_b(double L, double R){
    return R - (R - L) * inv_phi;
}

double calc_c(double L, double R){
    return L + (R - L) * inv_phi;
}

int main(){
    double eps = 0.0000001;
    double a = -10001.0, d = 10001.0;
    double b = calc_b(a, d);
    double c = calc_c(a, d);
    double f1 = f(b);
    double f2 = f(c);
    while((c - b) > eps){
        if(f1 < f2){
            a = b;
            b = c;
            c = calc_c(a, d);
            f1 = f2;
            f2 = f(c);
        }else{
            d = c;
            c = b;
            b = calc_b(a, d);
            f2 = f1;
            f1 = f(b);
        }
    }
    cout << fixed << setprecision(12) << b << endl;
}
