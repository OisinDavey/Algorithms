//
// Handy type for fractions, when relation to integers is important, no floating point errors
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

ll gcd(ll a, ll b){
    return (a==0)?b:gcd(b%a,a);
}

ll lcm(ll a, ll b){
    return a*(b/gcd(a,b));
}

const long long INF = 1e18;

using namespace std;

struct frac{
    public:
    ll numerator;
    ll denominator;

    frac() {
        numerator = 0;
        denominator = 1;
    }

    void balance(){
        ll tmp = gcd(numerator, denominator);
        numerator /= tmp;
        denominator /= tmp;
    }

    frac(ll _a, ll _b){
        if(_b == 0){
            cout << "Cannot have negative denominator!\n";
            numerator = 0;
            denominator = 1;
        }else{
            numerator = _a;
            denominator = _b;
            balance();
        }
    }

    ll value(){
        return numerator / denominator;
    }
};

ostream& operator<<(ostream& os, const frac& a){
    os << a.numerator << '/' << a.denominator;
    return os;
}

frac operator*(const frac& a, const frac& b){
    frac res;
    res.numerator = a.numerator * b.numerator;
    res.denominator = a.denominator * b.denominator;
    res.balance();
    return res;
}

frac operator*(const ll& a, const frac& b){
    frac res(a * b.numerator, b.denominator);
    return res;
}

frac operator+(const frac& a, const frac& b){
    ll tmp = lcm(a.denominator, b.denominator);
    frac res;
    res.numerator = a.numerator * (tmp / a.denominator) + b.numerator * (tmp / b.denominator);
    res.denominator = tmp;
    res.balance();
    return res;
}

frac operator+(const ll& a, const frac& b){
    frac tmp(a, 1);
    return tmp + b;
}

frac operator-(const frac& a, const frac& b){
    ll minus = -1;
    frac tmp = minus * b;
    return a + tmp;
}

frac operator/(const frac& a, const frac& b){
    frac tmp(b.denominator, b.numerator);
    return a * tmp;
}

ll ll_value(frac a){
    return (a.numerator)/(a.denominator);
}

double double_value(frac a){
    return (double)(a.numerator)/(double)(a.denominator);
}

int main(){
    while(1){
        ll x, y;
        cin >> x >> y;
        frac a(x, y);
        cin >> x >> y;
        frac b(x, y);
        cout << a + b << endl;
        cout << a * b << endl;
        cout << a - b << endl;
        cout << a / b << endl;
        cout << ll_value(a/b) << endl;
        cout << double_value(a/b) << endl;
    }
}
