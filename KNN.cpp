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
    int L, R;
    node* l;
    node* r;

    vector<double> pos; // Will be of size D, containing points of dimensions x, y, z, w, etc

    int id;

    int p;

    int depth;
};

int calls = 0;

vector<string> names;

node* tree[MX_N];
node* nodes[MX_N];
bool inTopK[MX_N];

int M, D, K, N; // Dimensions, Number of neighbours for which to look & Number of points

node* construct(int l, int r, int depth){
    if(l == r){
        tree[l]->l = NULL;
        tree[l]->r = NULL;
        tree[l]->L = l;
        tree[l]->R = l;
        tree[l]->p = l;
        tree[l]->depth = depth; 
        return tree[l];
    }
    int m = l + (r-l)/2;
    double compos = tree[m]->pos[depth % D];
    partition(tree+l, tree+r+1, [depth, compos](node* at){ 
        return at->pos[depth % D] < compos;
    });
    auto it = partition_point(tree+l, tree+r+1, [depth, compos](node* at){ 
        return at->pos[depth % D] < compos;
    });
    m = ((it) - (tree+0));
    for(int i=m+1;i<=r;++i)
        if(tree[i]->pos[depth % D] < tree[m]->pos[depth % D])
            swap(tree[i], tree[m]);
    //cout << compos << endl;
    if(m > l)
        tree[m]->l = construct(l, m-1, depth+1);
    else
        tree[m]->l = NULL;
    if(m < r)
        tree[m]->r = construct(m+1, r, depth+1);
    else
        tree[m]->r = NULL;
    tree[m]->L = l;
    tree[m]->R = r;
    tree[m]->p = m;
    tree[m]->depth = depth;
    return tree[m];
}

double Radius = INF;
double SecondRadius = INF;

double dist(node* a, node* b){
    double ans = 0.0;
    for(int i=0;i<D;++i)
        ans += (a->pos[i] - b->pos[i])*(a->pos[i] - b->pos[i]);
    ans = sqrt(ans);
}

node* NN(node* at, node* look){
    ++calls;

    int depth = at->depth;

    double crossdist = abs(at->pos[depth % D] - look->pos[depth % D]);

    node* best = NULL;

    //Consider this

    double distA = dist(at, look);

    if(distA < Radius && !inTopK[at->id]){
        best = at;
        SecondRadius = Radius+1;
        Radius = distA;
    }

    if(at->l == NULL && at->r == NULL)
        return best;

    if(look->pos[depth % D] < at->pos[depth % D]){//Check left first
        //cout << "LEFT\n";
        if(at->l != NULL){
            node* bestB = NN(at->l, look);
            if(bestB != NULL)
                best = bestB;
        }
        if(at->r != NULL && crossdist <= Radius){
            node* bestB = NN(at->r, look);
            if(bestB != NULL)
                best = bestB;
        }
    }else{//Check right first
        //cout << "RIGHT\n";
        if(at->r != NULL){
            node* bestB = NN(at->r, look);
            if(bestB != NULL)
                best = bestB;
        }
        if(at->l != NULL && crossdist <= Radius){
            node* bestB = NN(at->l, look);
            if(bestB != NULL)
                best = bestB;
        }
    }
    return best;
}

int main(){
    cin >> N >> M >> K;

    D = 3;

    vector<double> empty(D);
    map<string, int> nameToId;

    for(int i=0;i<N;++i){
        tree[i] = new node;
        tree[i]->pos = empty;
        tree[i]->id = i;
        string s, name = "";
        while(cin >> s){
            name += s;
            if(s[s.size()-1] == '\"')
                break;
            else
                name += " ";
        }
        names.pb(name);
        nameToId[name] = i;
        for(int j=0;j<D;++j)
            cin >> tree[i]->pos[j];
    }

    node* root = construct(0, N-1, 0);

    for(int i=0;i<N;++i)
        nodes[tree[i]->id] = tree[i];

    for(int i=0;i<M;++i){
        string s, name = "";
        while(cin >> s){
            name += s;
            if(s[s.size()-1] == '\"')
                break;
            else
                name += " ";
        }
        int lookFor = nameToId[name];        

        node* look = nodes[lookFor];

        memset(inTopK, 0, sizeof(inTopK));

        inTopK[lookFor] = 1;

        vector<string> ans;

        Radius = INF;
        SecondRadius = INF;

        for(int i=0;i<K;++i){
            Radius = SecondRadius;
            node* best = NN(root, look);
            inTopK[best->id] = 1;
            ans.pb(names[best->id]);
        }

        cout << "Number of calls total: " << calls << endl;
        
        cout << name << ": ";
        for(int i=0;i<ans.size();++i){
            cout << ans[i];
            if(i < ans.size()-1)
                cout << ", ";
        }
        cout << endl;
    }
}
