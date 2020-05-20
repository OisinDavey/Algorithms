//
// Code to generate Eertree and find the longest palindrome using it
//

#include<bits/stdc++.h>

#define MX_N 5001
#define ALPH_SIZE 26

using namespace std;

struct node{
    int start;
    int end;

    int size;

    int sufflink;
    int edge[256];
};

int maxx;

string stree;

node tree[1002];

int glit;

int curnode = 0;

void insertnode(int pos){
    while(1){
        if(pos-tree[curnode].size-1 >= 0 && stree[pos-tree[curnode].size-1] == stree[pos]){
            if(tree[curnode].edge[(int)stree[pos]] > 0){
                curnode = tree[curnode].edge[(int)stree[pos]];
                return;
            }
            ++glit;
            
            tree[glit].size = tree[curnode].size+2;
            tree[glit].start = pos-tree[glit].size+1;
            tree[glit].end = pos;
            if(tree[glit].size > tree[maxx].size)
                maxx = glit;
            
            if(tree[glit].size == 1){//Special Case
                tree[glit].sufflink = 1;
            }else{
                int at = tree[curnode].sufflink;
                int ans;
                while(1){
                    if(pos-tree[at].size-1 >= 0 && stree[pos-tree[at].size-1] == stree[pos]){
                        ans = tree[at].edge[(int)stree[pos]];
                        break;
                    }else{
                        at = tree[at].sufflink;
                    }
                }
                tree[glit].sufflink = ans;
            }
            
            tree[curnode].edge[(int)stree[pos]] = glit;
            
            curnode = glit;
            
            return;
        }else{
            curnode = tree[curnode].sufflink;
        }
    }
}

string longestPalindrome(string s){
    memset(tree,0,sizeof(tree));

    glit = 1;
    tree[0].sufflink = 0;
    tree[0].size = -1;
    tree[1].sufflink = 0;
    tree[1].size = 0;
    stree = s;

    maxx = 0;

    for(int i=0;i<stree.size();++i)
        insertnode(i);

    return stree.substr(tree[maxx].start,tree[maxx].size);
}
