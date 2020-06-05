//
// Compute area of largest rectangle of ones in a boolean matrix in O(nm) time, using max histogram area
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

int N, M;
bool G[MX_N][MX_N];
int GH[MX_N][MX_N];
int H[MX_N];

int MaxHistogramArea(){
    stack<int> stak;
    int maxh = 0;
    for(int i=0;i<(M+2);++i){
        if(!stak.empty()){
            while(H[i] < H[stak.top()]){
                int rem = stak.top();
                stak.pop();
                maxh = max(maxh, H[rem] * (i-stak.top()-1));
            }
        }
        stak.push(i);
    }
    return maxh;
}

int MaxSubMatrixBoolean(){
    int best = 0;
    H[0] = 0;
    H[M+1] = 0;
    for(int j=0;j<M;++j){
        GH[0][j] = G[0][j];
        H[j+1] = GH[0][j];
    }
    best = max(best, MaxHistogramArea());
    for(int i=1;i<N;++i){
        for(int j=0;j<M;++j){
            GH[i][j] = (G[i][j]) ? 1 + GH[i-1][j] : 0;
            H[j+1] = GH[i][j];
        }
        best = max(best, MaxHistogramArea());
    }
    return best;
}

int maximalRectangle(vector<vector<char>>& matrix) {
    N = matrix.size();
    M = matrix[0].size();
    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            G[i][j] = (matrix[i][j] == '1') ? 1 : 0;
        }
    }
    return MaxSubMatrixBoolean();
}

int main(){
}
