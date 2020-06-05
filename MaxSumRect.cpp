//
// O(N^3) solution to the maximum sum in a 2d rectangle, making use of Kadane's Algorithm & precomputing row sums
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

//MaxSumRect Variables
int N, M;

int MaxSumRect(){
    cin >> N >> M;
    int G[N][M];
    int GER[N][M+1];
    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            cin >> G[i][j];
        }
    }
    memset(GER, 0, sizeof(GER));
    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            GER[i][j+1] = G[i][j] + GER[i][j];
        }
    }
    int Kadane[N];
    int maxsum = -(INT_MAX/2);
    for(int x=0;x<=M;++x){
        for(int y=x+1;y<=M;++y){
            Kadane[0] = GER[0][y]-GER[0][x];
            for(int i=1;i<N;++i){
                int CUR = GER[i][y]-GER[i][x];
                Kadane[i] = max(CUR, CUR + Kadane[i-1]);
                maxsum = max(maxsum, Kadane[i]);
            }
        }
    }
    return maxsum;
}

int main(){
    cout << MaxSumRect() << endl;
}
