//
// ~oisín~ C++ Template
//

#include                <bits/stdc++.h>
#define MX_N            5001
#define INF             100000000
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

struct node{
    vector<node*> kids;
    int id;
    bool visited;
};

///Global Variables
int N, E;
node* G[MX_N];
node* GT[MX_N];
stack<int> stak;
vector<vector<int> > SCCs;
vector<int> curSCC;

void DFS(node* at){
    if(at->visited)
        return;
    at->visited = true;
    for(node* to : at->kids)
        DFS(to);
    stak.push(at->id);
    return;
}

void findSCC(node* at){
    if(at->visited)
        return;
    at->visited = true;
    curSCC.pb(at->id);
    for(node* to : at->kids)
        findSCC(to);
    return;
}

int main(){
    cin >> N;
    for(int i=0;i<N;++i){
        G[i] = new node;
        G[i]->id = i;
        G[i]->visited = false;
        GT[i] = new node;
        GT[i]->id = i;
        GT[i]->visited = false;
    }
    for(int i=0;i<N;++i){
        int at, to;
        string s;
        cin >> at;
        getline(cin, s);
        stringstream ss(s);
        while(ss >> to){
            G[at]->kids.pb(G[to]);
            GT[to]->kids.pb(GT[at]);
        }
    }
    for(int i=0;i<N;++i){
        DFS(G[i]);
    }
    while(!stak.empty()){
        int at = stak.top();
        stak.pop();
        if(!GT[at]->visited){
            findSCC(GT[at]);
            SCCs.pb(curSCC);
            curSCC = {};
        }
    }
    for(vector<int> SCC : SCCs){
        for(int x : SCC){
            cout << x << ' ';
        }
        cout << endl;
    }
}
