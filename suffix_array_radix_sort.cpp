//
// ~oisín~ C++ Template
//

#include                <bits/stdc++.h>
#define MX_N            200000 
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

void radix_sort(vector<pair<pair<int, int>, int> >& a){
    int n = a.size();
    {
        vector<pair<pair<int, int>, int> > a_new(n);
        vector<int> cnt(n);
        vector<int> pos(n);
        for(auto& x : a){
            ++cnt[x.fi.se];
        }
        pos[0] = 0;
        for(int i=1;i<n;++i){
            pos[i] = pos[i-1] + cnt[i-1];
        }
        for(auto& x : a){
            a_new[pos[x.fi.se]] = x;
            ++pos[x.fi.se];
        }
        a = a_new;
    }
    {
        vector<pair<pair<int, int>, int> > a_new(n);
        vector<int> cnt(n);
        vector<int> pos(n);
        for(auto& x : a){
            ++cnt[x.fi.fi];
        }
        pos[0] = 0;
        for(int i=1;i<n;++i){
            pos[i] = pos[i-1] + cnt[i-1];
        }
        for(auto& x : a){
            a_new[pos[x.fi.fi]] = x;
            ++pos[x.fi.fi];
        }
        a = a_new;
    }
    return;
}

int main(){
    string s;
    cin >> s;
    s += "$";
    int n = s.size();
    int order[n], e_class[n];
    {
        pair<char, int> a[n];
        for(int i=0;i<n;++i){
            a[i] = mp(s[i], i);
        }
        sort(a, a+n);
        for(int i=0;i<n;++i){
            order[i] = a[i].se;
        }
        e_class[order[0]] = 0;
        int e_value = 0;
        for(int i=1;i<n;++i){
            if(a[i].fi != a[i-1].fi){
                ++e_value;
            }
            e_class[order[i]] = e_value;
        }
    }

    int k = 0;
    while((1 << k) < n){
        vector<pair<pair<int, int>, int> > a(n);
        for(int i=0;i<n;++i){
            a[i] = mp(mp(e_class[i], e_class[(i + (1 << k)) % n]), i);
        }
        radix_sort(a);
        for(int i=0;i<n;++i){
            order[i] = a[i].se;
        }
        e_class[order[0]] = 0;
        int e_value = 0;
        for(int i=1;i<n;++i){
            if(a[i].fi != a[i-1].fi){
                ++e_value;
            }
            e_class[order[i]] = e_value;
        }
        ++k;
    }

    for(int i=0;i<n;++i){
        cout << order[i] << ' ';
    }
    cout << endl;
}
