//
// Solve maximum sum subarray which is less than k in M*M*N*LogN, cannot find better solution 
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
int N, M, K;
int A[MX_N];
int G[MX_N][MX_N];
int GER[MX_N][MX_N];

int maxSumSubArray(){
    set<int> sumset;
    sumset.insert(0);
    int best = -(INT_MAX);
    int sum=0;
    for(int i=0;i<N;i++){
        sum += A[i];
        auto it = sumset.upper_bound(sum-K-1);
        if(it!=sumset.end()){
            best=max(best,sum-*it);
        }
        sumset.insert(sum);
    }
    return best;
}

int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int m = matrix[0].size();
    N = max(n, m);
    M = min(n, m);
    K = k;
    if(n > m){
        for(int i=0;i<N;++i){
            for(int j=0;j<M;++j){
                G[i][j] = matrix[i][j];
            }
        }
    }else{
        for(int i=0;i<N;++i){
            for(int j=0;j<M;++j){
                G[i][j] = matrix[j][i];
            }
        }
    }
    for(int i=0;i<N;++i){
        for(int j=0;j<M;++j){
            GER[i][j+1] = G[i][j] + GER[i][j];
        }
    }
    int maxsum = -(INT_MAX);
    for(int x=0;x<=M;++x){
        for(int y=x+1;y<=M;++y){
            for(int i=0;i<N;++i){
                A[i] = GER[i][y]-GER[i][x];
            }
            maxsum = max(maxsum, maxSumSubArray());
        }
    }
    return maxsum;
}

int main(){
}
