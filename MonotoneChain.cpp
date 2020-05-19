//
// Code to generate a convex hull and compute its perimeter
//

#include                <bits/stdc++.h>
#define pb              push_back
#define All(a)          a.begin(),a.end()

using namespace std;

struct point{
    double x;
    double y;
};

struct comp{
    bool operator()(point a, point b){
        return (a.x == b.x)?(a.y < b.y):(a.x < b.x);
    }
};

int ccw(point& a, point& b, point& c){// + = right turn, 0 = collinear, - = left turn
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

double dist(point a, point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double Hull(vector<point>& Poles){
    sort(All(Poles), comp());
    vector<point> Upper;
    vector<point> Lower;
    for(point at : Poles){
        while(Upper.size() >= 2){
            if(ccw(Upper[Upper.size()-2], Upper[Upper.size()-1], at) <= 0)
                Upper.pop_back();
            else
                break;
        }
        Upper.pb(at);
    }
    reverse(All(Poles));
    for(point at : Poles){
        while(Lower.size() >= 2){
            if(ccw(Lower[Lower.size()-2], Lower[Lower.size()-1], at) <= 0)
                Lower.pop_back();
            else
                break;
        }
        Lower.pb(at);
    }
    double perimeter = 0.0;
    for(int i=0;i<Upper.size()-1;++i)
        perimeter += dist(Upper[i], Upper[i+1]);
    for(int i=0;i<Lower.size()-1;++i)
        perimeter += dist(Lower[i], Lower[i+1]);
    return perimeter;
}

int main(){
    int n;
    cin >> n;
    vector<point> v(n);
    for(int i=0;i<n;++i) cin >> v[i].x >> v[i].y;
    double ans = Hull(v);
    cout << ans << endl;
}
