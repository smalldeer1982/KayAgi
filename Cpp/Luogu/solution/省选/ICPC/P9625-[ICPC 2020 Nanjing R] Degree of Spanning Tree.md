# [ICPC 2020 Nanjing R] Degree of Spanning Tree

## 题目描述

给定一张 $n$ 个点 $m$ 条边的无向图，求一个生成树满足每个点的度数都不大于 $\frac{n}{2}$。

## 说明/提示

$2 \leq n \leq 10^5$，$n - 1\leq m \leq 2\times10^5$，$\sum n\leq5\times10^5$，$\sum m\leq10^6$。

保证图连通。

## 样例 #1

### 输入

```
2
6 9
1 2
1 3
1 4
2 3
2 4
3 4
4 5
4 6
4 6
3 4
1 3
2 3
3 3
1 2
```

### 输出

```
Yes
1 2
1 3
1 4
4 5
4 6
No
```

# 题解

## 作者：WhitD (赞：6)

## 题目大意
给定一个具有 $n$ 个顶点和 $m$ 条边的无向图，找到一个图的生成树，使得生成树中的每个顶点的度数不大于 $\frac{n}{2}$。
## 思路
对于有 $n$ 个点的生成树，其边数为 $n-1$，总度数为 $2n-2$，因此至多只有一个点的度数会大于 $\frac{n}{2}$。

我们可以先把这个图的任意一个生成树找出来，然后找到这个生成树中度数大于 $\frac{n}{2}$ 的点（要是找不到说明这个生成树已经满足条件了，直接输出就可以），将这个点设为生成树的根节点，枚举所有不在生成树上的边，先将这条边加进去，然后判断图中是否形成了包含根节点的环……

如图：蓝色边是初始生成树，红色点是根节点，黄色边是当前枚举到的边，不难看出图中的绿色边形成了一个包含根节点的环。

![](https://cdn.luogu.com.cn/upload/image_hosting/bsv6vjjw.png)

此时我们需要删除一条绿色边才能保证还是生成树，请注意我们的目的是为了减小根节点的度数，因此一定是优先删除与根节点相连的边，会有如下两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/sr10p94b.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/q5k7wpyd.png)

注意第二种情况，虽然根节点的度数小于 $\frac{n}{2}$ 了，但是橘色点的度数又大于 $\frac{n}{2}$ 了。我们发现原生成树中橘色点的度数为 $2$，而右下角的点度数为 $1$，也就是说我们在删边时需要优先删除度数大的点与根节点所连的边。

综上，我们得到了在删边时需要遵守的规则：优先删除与根节点相连的边，并且是度数大的节点与根节点相连的那条边（注意特判无解情况）。

---

## 作者：bluewindde (赞：2)

上一篇题解讲得很好，这里只做补充。

### 题意

给一张 $n$ 个点，$m$ 条边的无向图，找到一棵每个顶点度数都不大于 $\frac{n}{2}$ 的生成树。

### 解法

首先证明一个引理：一颗节点个数为 $n$ 的生成树上只有至多一个节点的度数会大于 $\frac{n}{2}$。运用反证法：对于一颗有 $n$ 个点的生成树，若存在 $2$ 个点度数大于 $\frac{n}{2}$，这 $2$ 个点的度数之和一定大于 $n$。因为整棵树的度数之和为 $2n-2$，所以其余 $n-2$ 个点的度数之和一定小于 $n-2$（当这两个点直接相连时，这个值为 $n-1$），即这 $n-2$ 个点中会存在度数为 $0$ 的点，而树上每个节点的最小度数为 $1$，产生矛盾。

随便搜一颗生成树 $T$，若 $T$ 存在一个度数大于 $\frac{n}{2}$ 的点 $u$（根据引理，这样的点最多只有一个），将点 $u$ 设为根。遍历不在树 $T$ 的边 $(x,y)$，若树 $T$ 加上这条边后形成的环内包含点 $u$，则删去点 $u$ 与相邻的、在环内的且度数最大的点 $v$ 之间的边（为了不让点 $v$ 度数不符合要求）。如果遍历完成后点 $u$ 的度数仍不符合要求，输出无解，否则输出答案。

本题坑点不少，注意处理细节。

```cpp
#include <iostream>
#include <vector>
using namespace std;

int T,n,m;

// 存两次边，适应不同情况
struct node {
    int u,v,id;
    node() {}
    node(int _u,int _v,int _id):u(_u),v(_v),id(_id) {}
} e[200005];
vector<node> vec[200005];
int deg[200005];
bool vis[200005];

int f[200005];
static inline int find(int x) {
    if(f[x]==x) return x;
    return f[x]=find(f[x]);
}

int dep[200005];
int to[200005];
static inline void dfs(int u,int fa,int t) {
    f[u]=t;
    dep[u]=dep[fa]+1;
    for(auto edge:vec[u]) {
        int v=edge.v;
        if(v==fa) continue;
        dfs(v,u,t);
    }
}

static inline void print() {
    for(int i=1;i<=m;++i) {
        if(vis[i]) {
            cout<<e[i].u<<" "<<e[i].v<<endl;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--) {
        cin>>n>>m;
        for(int i=0;i<=n;++i) {
            vec[i].clear();
            deg[i]=0;
            f[i]=i;
        }
        for(int i=1;i<=m;++i) {
            vis[i]=false;
        }
        for(int i=1;i<=m;++i) { // 一边读入一边建树 用并查集判断是否已经经过这个点
            int u,v;
            cin>>u>>v;
            e[i]=node(u,v,i);
            int uu=find(u);
            int vv=find(v);
            if(uu==vv) continue;
            vec[u].push_back(node(u,v,i));
            vec[v].push_back(node(v,u,i));
            f[vv]=uu;
            ++deg[u];
            ++deg[v];
            vis[i]=true;
        }
        int maxi=0;
        for(int i=1;i<=n;++i) {
            if(deg[i]>deg[maxi]) {
                maxi=i;
            }
        }
        if(n==3) {
            cout<<"No"<<endl;
            continue;
        }
        if(deg[maxi]<=n>>1) {
            cout<<"Yes"<<endl;
            print();
            continue;
        }
        f[maxi]=maxi; // 换根
        dep[maxi]=0;
        for(auto edge:vec[maxi]) {
            int v=edge.v;
            to[v]=edge.id;
            dfs(v,maxi,v);
        }
        for(int i=1;i<=m;++i) {
            int u=e[i].u;
            int v=e[i].v;
            if(u==maxi||v==maxi) continue;
            int uu=find(u);
            int vv=find(v);
            if(uu==vv) continue;
            if(dep[u]<dep[v]) {
                swap(u,v);
                swap(uu,vv);
            }
            if(dep[v]==1&&deg[u]>deg[v]) {
                swap(u,v);
                swap(uu,vv);
            }
            ++deg[u];
            ++deg[v];
            --deg[maxi];
            --deg[vv];
            vis[e[i].id]=true;
            vis[to[vv]]=false;
            f[vv]=uu;
            if(deg[maxi]<=n>>1) break;
        }
        if(deg[maxi]<=n>>1) {
            cout<<"Yes"<<endl;
            print();
        }
        else {
            cout<<"No"<<endl;
        }
    }
    return 0;
}
```

---

