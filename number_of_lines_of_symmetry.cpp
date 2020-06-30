//
// ~oisín~ C++ Template
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

//Global Variables
const double eps = 0.0000001;
map<pair<int, int>, bool> is_point;

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

struct comp{
    bool operator()(point a, point b){
        return (a.x == b.x)?(a.y < b.y):(a.x < b.x);
    }
};

double ccw(point& a, point& b, point& c){// + = right turn, - = left turn
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

double dist(point& a, point& b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

point reflect_origin(point a, point b){
    double scale = a*b;
    scale /= b*b;
    scale *= 2.0;
    point temp = scale * b;
    point result = temp - a;
    return result;
}

point reflect_floating_line(point a, point b, point target){
    b = b - a;
    target = target - a;
    point temp = reflect_origin(b, target);
    point result = temp + a;
    return result;
}

bool close_to_int(double x){
    double closest = round(x);
    return (abs(closest - x) < eps);
}

bool good(point a, point b, point c){
    point ref = reflect_floating_line(a, b, c);
//    cout << endl;
//    cout << a.x << ' ' << a.y << endl;
//    cout << b.x << ' ' << b.y << endl;
//    cout << c.x << ' ' << c.y << endl;
//    cout << ref.x << ' ' << ref.y << endl;
//    cout << endl;
    if(close_to_int(ref.x) && close_to_int(ref.y)){
        if(is_point[mp(round(ref.x), round(ref.y))]){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

point center_of_mass(vector<point>& mass){
    int n = mass.size();
    point ans(0, 0);
    for(point at : mass){
        ans.x += at.x;
        ans.y += at.y;
    }
    ans.x /= (double)n;
    ans.y /= (double)n;
    return ans;
}

vector<point> hull(vector<point>& mass){
    sort(All(mass), comp());
    vector<point> Upper;
    vector<point> Lower;
    for(point at : mass){
        while(Upper.size() >= 2){
            if(ccw(Upper[Upper.size()-2], Upper[Upper.size()-1], at) > 0)
                Upper.pop_back();
            else
                break;
        }
        Upper.pb(at);
    }
    reverse(All(mass));
    for(point at : mass){
        while(Lower.size() >= 2){
            if(ccw(Lower[Lower.size()-2], Lower[Lower.size()-1], at) > 0)
                Lower.pop_back();
            else
                break;
        }
        Lower.pb(at);
    }
    vector<point> ans;
    for(int i=0;i<Upper.size()-1;++i){
        ans.pb(Upper[i]);
    }
    for(int i=0;i<Lower.size()-1;++i){
        ans.pb(Lower[i]);
    }
    return ans;
}

point mean(point& a, point& b){
    point result((a.x + b.x)/2, (a.y + b.y)/2);
    return result;
}

int main(){
    int n;
    cin >> n;
    vector<point> mass;
    for(int i=0;i<n;++i){
        double _x, _y;
        cin >> _x >> _y;
        point tmp(_x, _y);
        mass.pb(tmp);
        is_point[mp((int)_x, (int)_y)] = true;
    }
    vector<point> h = hull(mass);
    point com = center_of_mass(mass);
    vector<point> candidates;
    candidates.pb(h[0]);
    for(int i=1;i<h.size();++i){
        candidates.pb(mean(h[i], h[i-1]));
        candidates.pb(h[i]);
    }
    candidates.pb(mean(h[0], h[h.size()-1]));
    int ans = 0;
    bool hori = false;
    vector<double> lines;
    for(point candidate : candidates){
        for(point at : mass){
            if(at.x == candidate.x && at.y == candidate.y){
                continue;
            }
            if(!good(com, at, candidate)){
                goto end_of_loop;
            }
        }
        if(candidate.x == com.x){
            hori = true;
        }else{
            lines.pb((candidate.y - com.y)/(candidate.x - com.x));
        }
        end_of_loop:;
    }
    sort(All(lines));
    if(lines.size() > 0){
        ++ans;
    }
    for(int i=1;i<lines.size();++i){
        if(abs(lines[i] - lines[i-1]) > eps){
            ++ans;
        }
    }
    cout << ans + (hori == true) << endl;
}
