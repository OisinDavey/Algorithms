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
const long long ALPH_SIZE = 26LL;

using namespace std;

void modulo(ll& x){
    if(x >= mod7){
        x %= mod7;
    }else if(x < 0){
        x = (mod7 + ( x % mod7 )) % mod7;
    }
}

ll binpow(ll base, int expo){
    if(expo == 0){
        return 1ll;
    }else if(expo == 1){
        return base;
    }
    ll tmp = binpow(base, expo/2);
    tmp *= tmp;
    modulo(tmp);
    if(expo % 2 == 1){
        tmp *= base;
        modulo(tmp);
    }
    return tmp;
}

ll rk_static_hash(string& s, int end_pos){
    ll ans = (ll)(s[0] - 'a');
    for(int i=1;i<end_pos;++i){
        ans *= ALPH_SIZE;
        modulo(ans);
        ans += (ll)(s[i] - 'a');
    }
    modulo(ans);
    return ans;
}

void rk_rolling_hash(string& s, int& start_pos, int& end_pos, ll& hash){
    ll k = end_pos - start_pos;
    hash -= (ll)(s[start_pos] - 'a') * binpow(ALPH_SIZE, k);
    modulo(hash);
    hash *= ALPH_SIZE;
    modulo(hash);
    hash += (ll)(s[end_pos + 1] - 'a');
    ++start_pos;
    ++end_pos;
}

int main(){
    string a;
    cin >> a;
    int T;
    cin >> T;
    while(T--){
        string b;
        cin >> b;
        vector<int> ans;
        ll b_hash = rk_static_hash(b, b.size());
        ll a_hash = rk_static_hash(a, b.size());
        int start_pos = 0;
        int end_pos = b.size()-1;
        while(end_pos < a.size()-1){
            if(a_hash == b_hash){
                ans.pb(start_pos);
            }
            rk_rolling_hash(a, start_pos, end_pos, a_hash);
        }
        if(a_hash == b_hash){
            ans.pb(start_pos);
        }
        vector<int> outp;
        for(int pos : ans){
            if(a.substr(pos, b.size()) == b){
                outp.pb(pos);
            }
        }
        if(outp.size() == 0){
            cout << "No matches\n";
        }else{
            cout << outp.size() << " matches\n";
            for(int pos : outp){
                cout << pos << ' ';
            }
            cout << endl;
        }
    }
}

