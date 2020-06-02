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
    node* l;
    node* r;

    vector<double> pos;

    int L;
    int R;

    int d;

    int id;
};

//Global Variables
node* tree[MX_N]; // The tree stored in array form
node* nodes[MX_N]; // Maintains original order of list to get IDs
bool inTopK[MX_N]; // Whether a node is in the top K nodes
int N, M, K, D;
double Radius;

double dist(node* a, node* b){
    double ans = 0.0;
    for(int i=0;i<D;++i)
        ans += (a->pos[i] - b->pos[i])*(a->pos[i] - b->pos[i]);
    ans = sqrt(ans);
    return ans;
}

int pivot (int l, int r, int d){  
    node* piv = tree[r]; // pivot  
    int i = (l - 1); // Index of smaller element  
    for (int j = l; j <= r - 1; j++){  
        if (tree[j]->pos[d % D] < piv->pos[d % D]){  
            i++; // increment index of smaller element  
            swap(tree[i], tree[j]);  
        }  
    }
    swap(tree[i + 1], tree[r]);  
    return (i + 1);  
}

node* construct(int l, int r, int d){
    if(l == r){
        tree[l]->l = NULL;
        tree[l]->r = NULL;
        tree[l]->L = l;
        tree[l]->R = l;
        tree[l]->d = d; 
        return tree[l];
    }
    int m = pivot(l, r, d);
    if(m > l)
        tree[m]->l = construct(l, m-1, d+1);
    else
        tree[m]->l = NULL;
    if(m < r)
        tree[m]->r = construct(m+1, r, d+1);
    else
        tree[m]->r = NULL;
    tree[m]->L = l;
    tree[m]->R = r;
    tree[m]->d = d;
    return tree[m];
}

node* NP(node* at, node* dest){
    int d = at->d;
    double crossDist = abs(at->pos[d % D] - dest->pos[d % D]);
    node* best = NULL;
    double distA = dist(at, dest);
    if(distA < Radius && !inTopK[at->id]){
        best = at;
        Radius = distA;
    }
    if(at->l == NULL && at->r == NULL)
        return best;
    if(dest->pos[d % D] < at->pos[d % D]){
        if(at->l != NULL){
            node* bestL = NP(at->l, dest);
            if(bestL != NULL)
                best = bestL;
        }
        if(at->r != NULL && crossDist <= Radius){
            node* bestR = NP(at->r, dest);
            if(bestR != NULL)
                best = bestR;
        }
    }else{
        if(at->r != NULL){
            node* bestR = NP(at->r, dest);
            if(bestR != NULL)
                best = bestR;
        }
        if(at->l != NULL && crossDist <= Radius){
            node* bestL = NP(at->l, dest);
            if(bestL != NULL)
                best = bestL;
        }
    }
    return best;
}

string getName(){
    string s, name = "";
    while(cin >> s){
        name += s;
        if(s[s.size()-1] == '\"')
            break;
        else
            name += " ";
    }
    return name;
}

int main(){
    cin >> N >> M >> K;
    D = 3;
    vector<double> empty(D);
    map<string, int> Name2ID;
    string ID2Name[N];
    
    for(int i=0;i<N;++i){
        tree[i] = new node;
        tree[i]->pos = empty;
        tree[i]->id = i;
        string name = getName();
        ID2Name[i] = name;
        Name2ID[name] = i;
        for(int j=0;j<D;++j)
            cin >> tree[i]->pos[j];
    }

    node* root = construct(0, N-1, 0);

    for(int i=0;i<N;++i)
        nodes[tree[i]->id] = tree[i];

    for(int i=0;i<M;++i){
        string name = getName();
        int destID = Name2ID[name];
        node* dest = nodes[destID];

        memset(inTopK, 0, sizeof(inTopK));
        inTopK[destID] = 1;
        vector<string> ans;
        Radius = INF;

        for(int j=0;j<K;++j){
            Radius = INF;
            node* best = NP(root, dest);
            inTopK[best->id] = 1;
            ans.pb(ID2Name[best->id]);
        }

        cout << name << ": ";
        for(int j=0;j<ans.size();++j){
            cout << ans[j];
            if(j < ans.size()-1)
                cout << ", ";
        }
        cout << endl;
    }
}
