//
// Implementation of Dijksta's Algorithm, specifically for codeforces 545 E 
//

#include                <bits/stdc++.h>
#define mp              make_pair
#define MX_N            305001
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

using namespace std;

const long long INF=1e18;

///Global Variables
int N, E;
ll dist[MX_N];
bool processed[MX_N];
vector<pair<int, int> > adj[MX_N];
ll mass[MX_N];
int par[MX_N];
int s;

void Dijkstra(){
    cin >> N >> E;
    for(int i=0;i<N;++i){
        dist[i] = INF;
        par[i] = -1;
        processed[i] = false;
    }
    for(int i=0;i<E;++i){
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].pb(mp(v, i));
        adj[v].pb(mp(u, i));
        mass[i] = w;
    }
    cin >> s;
    --s;
    dist[s] = 0LL;
    priority_queue<pair<ll, int> > PQ;
    PQ.push(mp(dist[s], s));
    while(!PQ.empty()){
        pair<ll, int> at = PQ.top();
        PQ.pop();
        if(processed[at.se])
            continue;
        processed[at.se] = true;
        for(pair<int, int> to : adj[at.se]){
            if(dist[to.fi] > dist[at.se] + mass[to.se]){
                dist[to.fi] = dist[at.se] + mass[to.se];
                PQ.push(mp(-dist[to.fi], to.fi));
            }
        }
    }
}

int main(){
    FastIO;
    Dijkstra();
    for(int i=0;i<N;++i){
        if(i == s)
            continue;
        ll minw = INF;
        int best = -1;
        for(pair<int, int> to : adj[i]){
            if(dist[to.fi] + mass[to.se] == dist[i]){
                if(mass[to.se] < minw){
                    minw = mass[to.se];
                    best = to.fi;
                }
            }
        }
        par[i] = best;
    }
    vector<int> ans;
    ll c = 0LL;
    for(int i=0;i<N;++i){
        for(pair<int, int> to : adj[i]){
            if(i == par[to.fi]){
                ans.pb(to.se);
                c += mass[to.se];
            }
        }
    }
    cout << c << endl;
    for(int x : ans)
        cout << x+1 << ' ';
    cout << endl;
}
