# Vani和Cl2捉迷藏

## 题目描述

Vani 和 cl2 在一片树林里捉迷藏。

这片树林里有 $N$ 座房子，$M$ 条有向道路，组成了一张有向无环图。

树林里的树非常茂密，足以遮挡视线，但是沿着道路望去，却是视野开阔。

如果从房子 $A$ 沿着路走下去能够到达 $B$，那么在 $A$ 和 $B$ 里的人是能够相互望见的。

现在 cl2 要在这 $N$ 座房子里选择 $K$ 座作为藏身点，同时 Vani 也专挑 cl2 作为藏身点的房子进去寻找，为了避免被 Vani 看见，cl2 要求这 $K$ 个藏身点的任意两个之间都没有路径相连。

为了让 Vani 更难找到自己，cl2 想知道最多能选出多少个藏身点。

## 说明/提示

- 对于 $20\%$ 的数据，$1\leq N\leq 10$，$1\leq M\leq 20$。
- 对于 $60\%$ 的数据，$1\leq N\leq 100$，$1\leq M\leq 1000$。
- 对于 $100\%$ 的数据，$1\leq N\leq 200$，$1\leq M\leq 30000$，$1\leq x,y\leq N$。

## 样例 #1

### 输入

```
4 4
1 2
3 2
3 4
4 2```

### 输出

```
2```

# 题解

## 作者：JustPureH2O (赞：10)

[更好的阅读体验](https://justpureh2o.cn/articles/1126)

题目地址：[P10938](https://www.luogu.com.cn/problem/P10938)

> Vani 和 cl2 在一片树林里捉迷藏。
>
> 这片树林里有 $N$ 座房子，$M$ 条有向道路，组成了一张有向无环图。
>
> 树林里的树非常茂密，足以遮挡视线，但是沿着道路望去，却是视野开阔。
>
> 如果从房子 $A$ 沿着路走下去能够到达 $B$，那么在 $A$ 和 $B$ 里的人是能够相互望见的。
>
> 现在 cl2 要在这 $N$ 座房子里选择 $K$ 座作为藏身点，同时 Vani 也专挑 cl2 作为藏身点的房子进去寻找，为了避免被 Vani 看见，cl2 要求这 $K$ 个藏身点的任意两个之间都没有路径相连。
>
> 为了让 Vani 更难找到自己，cl2 想知道最多能选出多少个藏身点。
>
> 对于 $100\%$ 的数据，$1\leq N\leq 200$，$1\leq M\leq 30000$，$1\leq x,y\leq N$。

乍一看好像求最大点独立集的问题，但是它只存在于无向图中，题目所给是有向图。这道题的答案是该图的最小重复路径点覆盖的路径条数。那么什么是路径点覆盖呢？

在图上选取若干条互不相交的路径，并让这些路径不重不漏覆盖到每一个点。符合上述要求且总数最小的方案就叫做原图的最小路径点覆盖，图中每个节点均只被覆盖一次。而最小重复路径点覆盖则是允许选取的路径相交，即某个点至少被覆盖一次。

在二分图中，最小路径点覆盖的路径条数等于总点数减去最大匹配数；最小路径重复点覆盖的数量则需要先求传递闭包，再计算最小路径点覆盖得出。

这启发我们可以把图转化为二分图来做，具体流程如下：

1. 原图中的点 $P$，在二分图中变为 $P$ 和 $P^\prime$。
2. 对于原图所有形如 $(P,A)$ 的边，在二分图上连 $(P,A^\prime)$；对于所有形如 $(A,P)$ 的边，在二分图上连边 $(A,P^\prime)$。

就可以把原图转化成二分图求解了。

---

接下来证明为什么答案就是原图的最小重复路径点覆盖。设答案为 $f(x)$、原图最小重复路径点覆盖数为 $k$，即证明 $f(x)=k$：

1. 证明 $f(x)\geq k$，考虑最小路径点覆盖的定义：因为 $k$ 条路径已经把所有点覆盖了，选点只能选其中某条路径的某个端点，已知有道路相连的房屋是可以互相看到的，所以不可能同时选某条路径的两个端点（最多选一个）。因此选出的 $k$ 是一定小于等于 $f(x)$ 的。
2. 证明 $f(x)\leq k$，考虑构造：将所有路径的终点 $E$ 放入一个集合 $\mathbb D$ 中，$\mathbb E$ 为“从 $E$ 出发能够到达的所有点的集合”。如果 $\forall E\in\mathbb D$，均有 $\mathbb D\cap\mathbb E=\varnothing$，意味着 $\mathbb E$ 内任意两点不互通，此时 $\mathbb E$ 为一组合法方案，大小为 $k$；反之，让当前的 $E$ 沿有向边反着走直到满足上面的情况。若当前点已经退回到它的起点，都还不满足上述情况，意味着这个起点与 $\mathbb D$ 中的所有点都互通，我们完全可以让 $E$ 作为起点，所有点也都能被覆盖到，此时的最小路径点覆盖数为 $k-1$，与原图最小路径点覆盖数为 $k$ 矛盾。故一定存在 $f(x)\leq k$。
3. 综上，$f(x)=k$ 必定成立。证毕。

此时使用匈牙利算法跑二分图最大匹配，然后就可以得出答案了。时间复杂度 $\mathcal O(nm)$，实际上会远小于此。

```cpp
#include <bits/stdc++.h>
#define N 210
#define M 30010
using namespace std;

bool g[N][N];
int match[N];
bool st[N];
int n, m;

bool hungary(int u) {
    for (int i = 1; i <= n; i++) {
        if (g[u][i] && !st[i]) {
            st[i] = true;
            if (!match[i] || hungary(match[i])) {
                match[i] = u;
                return true;
            }
        }
    }
    return false;
}

void floyd() {
    // Floyd 传递闭包
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                g[i][j] |= g[i][k] & g[k][j];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        g[a][b] = 1;
    }
    floyd();
    int res = 0;
    for (int i = 1; i <= n; i++) {
        memset(st, false, sizeof st);
        if (hungary(i)) res++;
    }
    cout << (n - res) << endl;
    return 0;
}
```

~~瓦尼瓦尼和氯气？~~

$\texttt{The End}$

---

## 作者：pangyuchen75 (赞：7)

**最小路径覆盖**：针对一个有向无环图（DAG），用最少条互不相交路径，覆盖所有点（其中互不相交是指点不重复）。

> 结论：最小路径点覆盖（最小路径覆盖）$=$ 总点数 $-$ 最大匹配。

证明：

## 1.建图

求最小路径覆盖用到拆点，一个点分成两个点，分别表示出点和入点，那么从点 $i \to j$ 的一条边就用，从左边的出点 $i$ 连到右边的入点 $j'$ 表示，于是得到的图是一个二分图，因为所有的边都是在左部和右部之间的，内部没有点。

## 2.转化

此时将原图中的每一条路径转化到新图中，因为原图中的路径互不相交，所以每一个点最多只有一个出度和入度，这就意味着在新图中，左部每一个点最多只会向右部连一条边，右部的点最多只会有一条边连入，每个点最多只会属于一条边。
- 原图中的一条路径 $\Longleftrightarrow$ 新图中的一组匹配（新图中每一个点最多只会属于一条边）。
- 原图中每一条路径的终点（没有出边） $\Longleftrightarrow$ 新图左部的非匹配点。

## 3.推导
求原图中互不相交路径数 $\Longleftrightarrow$ 求路径终点数最少 $\Longleftrightarrow$ 求左部非匹配点最少 $\Longleftrightarrow$ 求最大匹配。

拓展：

**最小路径重复点覆盖**：在最小路径覆盖问题的基础上，去掉互不相交。

> 结论：记原图 $G$，求传递闭包后的图 $G'$，则 $G$ 的最小路径重复点覆盖 $=G'$ 的最小路径覆盖。

在该题中，记最小路径重复点覆盖数为 $cnt$，该题的答案就是 $cnt$。

证明：

---

$k \le cnt$

这 $cnt$ 条路径覆盖了所有的点，所以所求的 $k$ 个点一定要从这 $cnt$ 条路径中的点选，并且每条路径上最多选一个点，所以 $k \le cnt$。

---

$k \ge cnt$

构造：将 $cnt$ 条路径的终点都放到一个集合 $E$ 中，记 $next(E)$ 返回的是从 $E$ 中的每个点出发能到的所有点的集合。

分类讨论：
- $E \cap next(E) = Ø$，此时 $E$ 内的点不能相互到达，说明 $E$ 中所有的点就是一种 $k = cnt$ 的方案。
- $E \cap next(E) \ne Ø$，对于 $E$ 中的任何一个点 $p$，让这个点反向走，直到这个点走到一个不在 $next(E-p)$ 中的点，可证当这个点走到起点时肯定不在 $next(E-p)$ 中。

---

反证法：

如果这个点走到起点，仍在 $next(E-p)$ 中，说明 $p$ 所在的路径的起点可以被其他路径到达，那么这条路径就没有存在的意义可以省去，不满足最小路径重复点覆盖。

所以此时同样可以在每一条路径中选出一个点，使得这些点之间两两不可到达，即 $k = cnt$。

## C++ 代码：

```cpp
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 205;
const int M = 3e4 + 5;

int n, m;
bool d[N][N], st[N];
int match[N];

bool find(int x) {
    for (int i = 1; i <= n; i ++ ) {
        if (d[x][i] && !st[i]) {
            st[i] = true;
            int t = match[i];

            if (!t || find(t)) {
                match[i] = x;
                return true;
            }
        }
    }

    return false;
}

void inp() {
    scanf("%d%d", &n, &m);
    
    while (m -- ) {
        int u, v;
        scanf("%d%d", &u, &v);
        d[u][v] = true;
    }
}

void work() {
    for (int k = 1; k <= n; k ++ )
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= n; j ++ )
                d[i][j] |= d[i][k] & d[k][j];
    
    int res = 0;

    for (int i = 1; i <= n; i ++ ) {
        memset(st, false, sizeof st);
        if (find(i)) res ++ ;
    }
    
    printf("%d\n", n - res);
}

int main() {
    inp();
    work();

    return 0;
}
```

## 完结散花！

---

## 作者：_jimmywang_ (赞：6)

题意：求 DAG 的**最长反链**长度。

反链的概念来源于[序理论](https://oi-wiki.org/math/order-theory/)，此处稍作简化处理。

因为偏序集可以视作一个 DAG，偏序关系即为有向边，此处为方便，将序理论中的概念迁移至 DAG 上。

定义 DAG 上两点 $u,v$ 是**可比**的，当且仅当存在一条 $u\to v$ 或 $v\to u$ 的有向路径，反之 $u,v$ 是**不可比**的。定义**链**为一个点集 $S$，使得任意两点 $u,v\in S$，$u,v$ 都是可比的；定义**反链**为一个点集 $T$，使得任意两点 $u,v\in T$，$u,v$ 都是不可比的。

简单地说，链就是一条 DAG 的路径的子集，反链就是一个点集，其中的点两两没有有向路径连接。

-------

### 做法1：最大权闭合子图

因为选了一个点，其所有的后继节点（可传递）均不能选，因此我们建立以下模型：

对原图每个点拆点 $(in_u,out_u)$，原图边 $(u,v)$ 改为 $(out_u,in_v)$，所有 $in_u$ 点权为 -1，所有 $out_u$ 点权为 1。此图最大权闭合子图即为最长反链。

这个图比较好理解，因为一个最大的闭合子图一定是由若干个 $out_u$ 作为起点发出的（否则权值和非正），这几个 $u$ 构成了一个反链。

### 做法2：Dilworth 定理

[Dilworth 定理](https://zh.wikipedia.org/wiki/%E7%8B%84%E5%B0%94%E6%B2%83%E6%96%AF%E5%AE%9A%E7%90%86)的表述：最长反链等于最小链覆盖。注意区分此处的**链**与**路径**。链是点集，不一定要求是一条路径。

证明采用归纳形式，详见 [oi-wiki](https://oi-wiki.org/math/order-theory/#dilworth-%E5%AE%9A%E7%90%86%E4%B8%8E-mirsky-%E5%AE%9A%E7%90%86)。

最小链覆盖的做法并不困难：先对原图做一遍传递闭包，此时所有的链都转化为了传递闭包后的图上的路径，此时再做最小路径覆盖的答案就是原图上最小链覆盖的答案。

---

## 作者：apple_vinegar (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P10938)

题意：给出一个有向无环图，你需要选出若干个点，使它们不能两两到达，你需要使选择的点最多。

比较熟悉的人可以一眼发现需要求的是最长反链，但其实就算不知道反链是什么也是没关系的。其实个人感性理解可以理解出就是选择尽量少的可以覆盖所有点的路径，然后每个路径上选择一点，所以相等。但这显然是没有逻辑的，我们需要证明一下。

### 最小不交链覆盖

这是什么东西呢，其实就是指在有向无环图中，用最少的不可以相交的简单路径覆盖图中的所有点。\
一下子没什么思路，但我们发现每个点能且仅能被经过 1 次，那我们考虑转化成匹配问题，也就是每个点必须且仅能连一次前继与一次后驱，把左右分开，发现变成了二分图，起初存在 $n$ 个不相连的路径，每进行一次匹配可视为合并两条路径，所以最小不交链覆盖等于 $n$ 减最大匹配数。

### 最小可交链覆盖

意思很好理解，就是把上面的定义改成可交。\
思考改变了什么，我们发现变成二分图后每次连边不一定只能按原来的连边走。因为可以重复经过，所以比如此时已有路径 $1\to 2\to 3$，我们需要 $4\to 3\to 5$，虽然 3 被占用了，但是我们仍能从 4 直接到 5，所以我们需要传递闭包维护联通性。

### 最大反链

以下是本题所用知识，最长反链指在有向无环图中，选择最多的点，使它们两两不相通。

首先容易发现最大反链长度一定小于等于最小可交链覆盖，证明是设最小可交链覆盖为 $k$，那么我选择的点数一旦超过 $k$ 则必然有两个点在同一路径上。\
再证明最大反链长度一定大于等于最小可交链覆盖。同样设最小可交链覆盖为 $k$，那这个二分图的最大独立集为 $2 \times n-(n-k)=n+k$。所以最大反链长度一定大于等于 $n+k-n=k$。\
综上，最大反链长度一定等于最小可交链覆盖。

笔者自认为这个方式比较好理解，感兴趣的可以研究更为广泛的 [Dilworth 定理](https://oi-wiki.org/math/order-theory/#dilworth-%E5%AE%9A%E7%90%86%E4%B8%8E-mirsky-%E5%AE%9A%E7%90%86)。

### Ac Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18;
int idx=1,e[N],w[N],ne[N],h[N],dep[N],s,t,now[N],vis[505][505],n,m,E;


inline int read(){
    int a=1,b=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') a=-a;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        b=(b<<1)+(b<<3)+(ch^48);
        ch=getchar();
    }
    return a*b;
}



inline void add(int a,int b,int c){
    e[++idx]=b;
    w[idx]=c;
    ne[idx]=h[a];
    h[a]=idx;
    e[++idx]=a;
    w[idx]=0;
    ne[idx]=h[b];
    h[b]=idx;
}

inline int bfs(){
    queue<int>q;
    for(int i=0;i<=n+n+2;i++){
        dep[i]=inf;
    }
    q.push(s);
    dep[s]=0;
    now[s]=h[s];
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=h[u];i;i=ne[i]){
            int v=e[i];
            if(w[i]&&dep[v]==inf){
                now[v]=h[v];
                dep[v]=dep[u]+1;
                q.push(v);
                if(v==t) return 1;
            }
        }
    }
    return 0;
}
inline int dfs(int u,int flow){
    if(u==t) return flow;
    int res=0,k;
    for(int i=now[u];i;i=ne[i]){
        int v=e[i];
        now[u]=i;
        if(w[i]&&dep[v]==dep[u]+1){
            k=dfs(v,min(flow,w[i]));
            if(!k) dep[v]=inf;
            w[i]-=k;
            w[i^1]+=k;
            res+=k;
            flow-=k;
        }
    }
    return res;
}



signed main(){
    n=read(),m=read();
    s=0,t=n*2+1;
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        vis[u][v]=1;
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                vis[i][j]|=(vis[i][k]&vis[k][j]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        add(s,i,1);
        add(i+n,t,1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(vis[i][j]) add(i,j+n,1);
        }
    }
    int ans=0;
    while(bfs()){
        ans+=dfs(s,inf);
    }
    cout<<n-ans<<endl;
    return 0;
}
```

---

## 作者：Stairs_upon_temple (赞：5)

### 闲话

基于本题已经有人写了匈牙利的题解，这里我就来写一篇关于网络流的题解。

能做这道题的人应该都能看出是裸的最小重复路径覆盖问题吧。

~~虽然最小路径覆盖原代码只会红一个点。~~

# 思路

首先网络流的难点一直都是在于建图，那么这道题该怎么建图呢？

### 引入

先想一下普通的最小路径覆盖集问题，我们的见图方式是将每个点拆为出点和入点，目的是保证每个点刚好只被所有路径经过一次。

然后将源点和入点连接，汇点和出点连接（~~废话~~）。

对于原图中的连边 $(u,v)$ 我们将 $u$ 出点连接到 $y$ 入点。

仔细考虑一下为什么这么建图，我的解释是这样的：对于最小路径覆盖我们肯定希望能用最少的路径覆盖**不重不漏**覆盖所有点，那么上面这种建图方式，可以再实际运行中像穿针引线一样**把所有这条路径上是点用 $1$ 的单位流量穿起来从起点引导到终点**，而因为过程中限流，所以就算有多条边和改点相连，最后也只会穿到一条路径上，而跑满最大流的过程最好就是将上面所有的边 $(u,v)$ 都跑上一的流量，刚好满足最大流的性质。

### 正解

最小路径覆盖和最小重复路径覆盖的区别在于，后者可以是一条边被多次覆盖，那该怎么办呢？

其实唯一区别就是将原来的建边改为将一个点和它所有能沿着当前边能到达的点都连上**有向边**。

现在考虑为什么？

因为是重复覆盖，因此可以有多条路径同起点或同终点，而原来一条路径可能会被另一条分成两条，而现在可以直接用两点表示一整条路径，故上述建图方式可行。

```cpp
/*
g++ -o2 P10938.cpp -o c -std=c++14
.\c

*/

#include<cstring>
#include<vector>
#include<cstdio>

using namespace std;
const int N=4e2+20;
const int M=5e4+100;
const int inf=0x3f3f3f3f;

inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
inline int ops(int x){return x^1;}

int tot;
int head[N];
struct edge{
    int y,f,w;
    int next;
}e[M];

int cur[N];
int dep[N];

int q[M];
int in[N];
int ou[N];

int n,m;
int s,t;

int con[N][N];
vector<int>v[N];

char *p1,*p2;
char buf[10];
// #define nc getchar
#define nc() (p1==p1 && (p2=(p1=buf)+fread(buf,1,10,stdin),p1==p2)?EOF:*p1++)

inline void read(int &x){
    int sum=0;
    char ch=nc();
    while(ch<48 || ch>57){
        ch=nc();
    }
    while(ch>=48 && ch<=57){
        sum=(sum<<3)+(sum<<1)+ch-48;
        ch=nc();
    }
    x=sum;
    return ;
}

inline void add(int x,int y,int f){
    e[tot].y=y;
    e[tot].f=f;
    e[tot].next=head[x];
    head[x]=tot++;
    return ;
}

inline void make(int x,int y,int f){
    add(x,y,f);
    add(y,x,0);
    return ;
}

inline bool bfs(int start,int to){
    int hh=0;
    int tt=1;
    memset(dep,-1,sizeof(dep));
    // for(int i=1;i<=n*2+10;i++)dep[i]=-1;
    q[hh]=start;
    cur[start]=head[start];
    dep[start]=0;
    while(hh!=tt){
        int x=q[hh++];
        if(tt==M)hh=0;
        for(int i=head[x];~i;i=e[i].next){
            int y=e[i].y;
            int f=e[i].f;
            if(!f)continue;
            if(dep[y]==-1){
                dep[y]=dep[x]+1;
                cur[y]=head[y];
                if(y==to)return true;
                q[tt++]=y;
                if(tt==M)tt=0;
            }
        }
    }
    return false;
}

inline int find(int x,int to,int limit){
    if(x==to)return limit;
    int flow=0;
    for(int i=cur[x];~i && flow<limit;i=e[i].next){
        int y=e[i].y;
        int f=e[i].f;
        cur[x]=i;
        if(!f)continue;
        if(dep[y]==dep[x]+1){
            int t=find(y,to,min(limit-flow,f));
            if(!t)dep[y]=-1;
            e[i].f-=t;
            e[ops(i)].f+=t;
            flow+=t;
        }
    }
    return flow;
}

inline void dinic(int start,int to,int &ans){
    int flow=0;
    int r=0;
    while(bfs(start,to)){
        while(flow=find(start,to,inf)){
            r+=flow;
        }
    }
    ans=r;
    return ;
}

inline void init(){
    tot=0;
    memset(head,-1,sizeof(head));
    s=0;
    t=n*2+1;
    return ;
}

inline void debug_build(){
    for(int i=0;i<tot;i+=2){
        int x=e[ops(i)].y;
        // int x=e[i].x;
        int y=e[i].y;
        int f=e[i].f;
        // int w=e[i].w;
        printf("%d -> %d :%d\n",x,y,f);
    }
    return ;
}

inline void dfs(int x,int fro){
    for(int i=0;i<v[x].size();i++){
        int y=v[x][i];
        if(con[fro][y])continue;
        con[fro][y]=1;
        // con[y][fro]=1;
        dfs(y,fro);
    }
    return ;
}

int main(){
    scanf("%d%d",&n,&m);
    init();
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        v[x].push_back(y);
    }
    for(int i=1;i<=n;i++){
        dfs(i,i);
        for(int j=1;j<=n;j++){
            if(con[i][j]){
                make(i+n,j,1);
            }
        }
    }
    for(int i=1;i<=n;i++){
        make(s,i+n,1);
        make(i,t,1);
    }
    int ans;
    // debug_build();
    dinic(s,t,ans);
    printf("%d\n",n-ans);
    return 0;
}
```

最后祝喜欢瓦尼瓦尼的 $CL$ 能早日水神满命。

---

## 作者：Wsl886 (赞：4)

#### 我的第一个题解！

### 题意
给定 DAG，问最多能选多少点，使任意两点间不连通。

### 分析

就是求 DAG 的最小路径重复点覆盖。

最小路径点覆盖（最小路径覆盖）就是总点数-最大匹配。

最小路径重复点覆盖：在最小路径覆盖问题的基础上，去掉互不相交。

最大匹配用匈牙利即可（~~我不会网络流 qwq~~）。

### 代码环节

#### 马蜂不好，大括号习惯换行，请谅解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=210,M=30010;
int n,m;
bool g[N][N],st[N];
int match[N];
bool find(int x)
{
	for(int i=1;i<=n;++i)
	{
		if(g[x][i] && !st[i])
		{
			st[i]=true;
			int t=match[i];
			if(t==0||find(t))
			{
				match[i]=x;
				return true;
			}
		}
	}
	return false;
}
int main()
{
	cin>>n>>m;
	while(m--)
	{
		int a,b;
		cin>>a>>b;
		g[a][b]=true;
	}
	// Floyd传递闭包
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=n;++j)
			{
				g[i][j] |=g[i][k] & g[k][j];
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		memset(st,0,sizeof st);
		if(find(i)) ans++;
	}
	cout<<n-ans;
}
```

---

## 作者：_OccDreamer_ (赞：2)

## 题意

最小可交路径点覆盖。

## 前置知识

最小无交路径点覆盖。

令最小无交路径点覆盖数为 $x$，二分图最大匹配数为 $y$，图总点数为 $n$。

结论是：$x = n - y$。

## 思路

考虑转化。如果一个点可以间接到达另一个点，那么在图上建一条直接连接两点的边，做最小无交路径点覆盖就相当于原先的最小可交路径点覆盖。

这个证明是很好想的，可以自行思考。

对于判断一个点是否可以间接到达另一个点，用 Floyd 做传递闭包即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;

const int N = 205;
int n, m, u, v, mch[N], dis[N][N];
bool vis[N];
vector<int> g[N];

inline bool dfs(int x) {
	for(auto u : g[x])
		if(! vis[u]) {
			vis[u] = true;
			
			if(! mch[u] || dfs(mch[u])) {
				mch[u] = x;
				
				return true;
			}
		}
	
	return false;
}

signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> n >> m;
	for(int i = 1 ; i <= m ; ++ i) {
		cin >> u >> v;
		
		dis[u][v] = true;
	}
	
	for(int k = 1 ; k <= n ; ++ k)
		for(int i = 1 ; i <= n ; ++ i)
			for(int j = 1 ; j <= n ; ++ j)
				dis[i][j] |= (dis[i][k] & dis[k][j]);
	
	for(int i = 1 ; i <= n ; ++ i)
		for(int j = 1 ; j <= n ; ++ j)
			if(dis[i][j]) g[i].pb(j);
	
	int ans = 0;
	
	for(int i = 1 ; i <= n ; ++ i) {
		memset(vis, false, sizeof vis);
		
		if(dfs(i)) ++ ans;
	}
	
	cout << n - ans;
	
	return 0;
}
```

---

## 作者：Weekoder (赞：2)

### 分析

可以观察到，本题给出了一个 DAG，并且可以看作要用“路径”覆盖整个图。由于“能互相望见”在本题中即为路径，所以这些路径是可相交的。而我们又可以发现，望，是可以一望到底的，也就是路径会本能地做到尽可能长。藏身点怎么选呢？由于所有路径都不是完全重合的，因此我们总可以在每条路径上选出一个藏身点。可见这是一个**有向无环图可相交情况下的最小路径点覆盖问题**。

upd 2025/1/22：本题更为严谨且直接的解法为：求原图的最长反链的长度。同样可以由 [Dilworth 定理](https://oi-wiki.org/math/order-theory/#dilworth-%E5%AE%9A%E7%90%86%E4%B8%8E-mirsky-%E5%AE%9A%E7%90%86) 得到上述结论。此处作为扩展，感性理解“选择藏身点”即可。

### 最小路径点覆盖问题

[P2764 最小路径覆盖问题](https://www.luogu.com.cn/problem/P2764) 是模板题。此问题定义如下：

>给定有向无环图 $G$，用最少的不相交的路径覆盖所有的点。

路径不相交，是指一个点恰好出现在一条路径上。

解决方法：我们将所有的点分为入点和出点，即对于一条有向边 $x\to y$，$x$ 是入点，$y$ 是出点。通过这种分类方法构造二分图，则最少路径数量 $=$ 原图点数 $n$ 减去二分图的最大匹配数。在此不提路径打印的方法，与本题无关。

#### 证明

由于所有路径不相交，所以路径数量应等于终点的数量。因为终点没有出边，所以当 $x$ 的出边 $out_x$ 没有参与最大匹配时，$x$ 必须是终点。由此可知，当参与最大匹配的 $out_x$ 最多时，作为路径终点的 $x$ 就最少，从而选择最少的路径。

### Plus - 最小路径可相交点覆盖问题

在原图中，从 $x$ 到 $y$ 的路径我们并不关心。由于路径可相交，只要 $x$ 能到达 $y$，我们就一定能选出一条 $x\to y$ 的路径来。于是只需要在 $x,y$ 之间直接连一条边就可以了，避免了相交的问题，于是原问题又转化为新图下的最小路径点覆盖问题。显然，$x$ 是否能到达 $y$ 能用 Floyd 传递闭包维护。

---

下面给出参考代码：


```cpp
#include <bits/stdc++.h>

#define debug(x) (cout << #x << " " << x << "\n")

using namespace std;

using ll = long long;

const int N = 205;

int T, n, m, ans, match[N];

bool vis[N], dis[N][N];

void floyd() {
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dis[i][j] |= dis[i][k] && dis[k][j];
}

bool hungary(int cur) {
	for (int nxt = 1; nxt <= n; nxt++) if (cur != nxt && dis[cur][nxt] && !vis[nxt]) {
		vis[nxt] = 1;
		if (!match[nxt] || hungary(match[nxt])) {
			match[nxt] = cur;
			return 1;
		}
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fill(dis[i] + 1, dis[i] + 1 + n, 0), dis[i][i] = 1;
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		dis[u][v] = 1;
	}
	floyd();
	fill(match + 1, match + 1 + n, 0);
	ans = 0;
	for (int i = 1; i <= n; i++) { 
		fill(vis + 1, vis + 1 + n, 0);
		ans += hungary(i);
	}
	cout << n - ans << "\n";
	return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：2)

## 题解：P10938 Vani和Cl2捉迷藏
### 分析
很容易知道若两个人能互相望见，则这是一条路径。

题面中告诉我们本题是有向无环图，并且这 $k$ 个点没有边相连。

所以，从任意一个起点（即入度为 $0$ 的点）到这个点只有一条路径。

如果选了一个藏身点，那么藏身点所在的这条路径上的其他点都不可能再成为藏身点，因此，找点的本质是找路径。

因此，题目就变成了最小路径点覆盖问题。但是，并没有说两条路径不能共点。我们可以侧翼采取如下的解决方法：若 $1\to 3$，$2\to 3$，而点 $3$ 是两条路径的交点，那么我们可以认为 $1$ 和 $2$ 之间有连边。考虑用传递闭包来实现。

这时思路就很明显了，跑一边传递闭包，对于可以互相到达的点建边后再跑匈牙利算法即可求出藏身点数。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+5;

int match[N], Out[N], n, m;
//struct node
//{
//	int x, y;
//}a[N];
vector<int> nbr[N];
bool vis[N];
bool g[N][N];
void flo()
{
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				g[i][j]|=g[i][k]&g[k][j];
			}
		}
	}
}
bool xyl(int cur)
{
	for(int nxt=1;nxt<=n;nxt++)
	{
		if(!vis[nxt]&&g[cur][nxt])
		{
			vis[nxt]=1;
			if(!match[nxt]||xyl(match[nxt]))
			{
				match[nxt]=cur;
				return 1;
			}
		}
	}
	return 0;
}
signed main()
{
	cin>>n>>m;
	while(m--)
	{
		int a, b;
		cin>>a>>b;
		g[a][b]=1;
	}
	flo();
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof vis);
		if(xyl(i))ans++;
	}
	cout<<n-ans<<"\n";
}
```

---

## 作者：lfxxx_ (赞：2)

不难发现，这个图 $G$ 是一个 DAG。

而这 $k$ 个点都没有路径相连，则从任一入度为 $0$ 的点到达这个点只有一条路径，而路径之间可以重复，于是就变成了可重边的 DAG 最小路径覆盖问题。

用 Floyd 传递闭包，变成不可重边的 DAG 最小路径覆盖问题，然后直接跑匈牙利算法即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=205;
int n,m;
int mp[N][N];
int mat[N],vis[N];
bool dfs(int u)
{
    for(int i=1;i<=n;++i)
    {
        if(!mp[u][i]||vis[i]) continue;
        vis[i]=1;
        if(!mat[i]||dfs(mat[i]))
        {
            mat[i]=u;
            return 1;
        }
    }
    return 0;
}
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        int x,y;
        cin>>x>>y;
        mp[x][y]=1;
    }
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                mp[i][j]|=(mp[i][k]&mp[k][j]);
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        memset(vis,0,sizeof vis);
        ans+=dfs(i);
    }
    cout<<n-ans;
}
```

---

## 作者：XZhuRen (赞：1)

本题正常做法是传递闭包后转化为不交路径点覆盖或者最大权闭合子图做法。

本题解给出另一种不用求传递闭包的傻子写法：

由于求最小可交路径覆盖，是相对于点的，考虑相对于边的覆盖：

拆点成边，钦定每个点 `In->Out` 的边流量至少为 $1$，原图的边无限制，上下界最小流即可。

省去了求传递闭包，可以跑 $n=10^4,m=10^5$ 以上的数据。

正确性显然。

```cpp

#include<bits/stdc++.h>
using namespace std;
const int inf=1e9+7;
const int N=5e5+5;
const int M=5e5+5;
struct edge{
	int u,v,nxt;
	int c;
};
int col[N],tc=0,m;
namespace graph1{
	edge g[M];
	int head[N],tote=0;
	void ae(int u,int v,int op){g[++tote]=(edge){u,v,head[u],op};head[u]=tote;}
	int dfn[N],low[N],tdfn=0;
	int stk[N],top=0;
	void Tarjan(int u){
		dfn[u]=low[u]=++tdfn;
		stk[++top]=u;
		for(int e=head[u],v;e;e=g[e].nxt){
			v=g[e].v;
			if(!dfn[v])Tarjan(v),low[u]=min(low[u],low[v]);
			else if(!col[v])low[u]=min(low[u],dfn[v]);
		}
		if(low[u]==dfn[u]){
			col[u]=++tc;
			while(stk[top]!=u)
				col[stk[top--]]=tc;
			top--;
		}
	}
}
int totn=0;
namespace graph2{
	edge g[M];
	int head[N],tote=1;
	void ae(int u,int v,int c){g[++tote]=(edge){u,v,head[u],c};head[u]=tote;}
	void Ae(int u,int v,int c){ae(u,v,c),ae(v,u,0);}
	int totn=0;
	int S,T;
	int dep[N],thead[N],que[N],hd=1,tl=0;
	bool bfs(){
		for(int i=1;i<=totn;i++)thead[i]=head[i],dep[i]=0;
		int u;
		dep[S]=1,que[hd=tl=1]=S;
		while(hd<=tl){
			u=que[hd++];
			for(int e=head[u],v;e;e=g[e].nxt){
				v=g[e].v;if(dep[v]||!g[e].c)continue;
				dep[v]=dep[u]+1,que[++tl]=v;
			}
		}
		return dep[T];
	}
	int dfs(int u,int F){
		if(!F||u==T)return F;
		int rf=0,tmp;
		for(int e=thead[u],v;F&&e;e=g[e].nxt){
			v=g[e].v;thead[u]=e;if(!g[e].c||dep[v]!=dep[u]+1)continue;
			tmp=dfs(v,min(F,g[e].c)),F-=tmp,rf+=tmp,g[e].c-=tmp,g[e^1].c+=tmp;
		}
		return rf;
	}
	int dinic(){
		int res=0;
		while(bfs())res+=dfs(S,inf);
		return res;
	}
	int inflow[N],outflow[N];
	int te=0;
	int s,t;
#define In(x) (x)
#define Out(x) (x+tc)
	bool V[N];
	void init(){
		totn=(tc<<1)+2;
		s=(tc<<1)+1,t=(tc<<1)+2;
		for(int c1,c2,u,v,e=1;e<=m;e++){
			u=col[graph1::g[e].u],v=col[graph1::g[e].v];
			if(u==v)V[u]=1;
		}
		for(int i=1,u,v,c1,c2;i<=tc;i++){//拆点连边
			u=In(i),v=Out(i);
			c1=0,c2=inf;
			if(V[i])c1=1;
			Ae(u,v,c2-c1);
			inflow[v]+=c1;
			outflow[u]+=c1;
			Ae(s,In(i),inf);
			Ae(Out(i),t,inf);
		}
		for(int c1,c2,u,v,e=1;e<=m;e++){
			u=col[graph1::g[e].u],v=col[graph1::g[e].v];
			if(u==v)continue;
			u=Out(u),v=In(v);
			c1=0,c2=inf;
			if(graph1::g[e].c)c1=1;
			Ae(u,v,c2-c1);
			inflow[v]+=c1;
			outflow[u]+=c1;
		}
		Ae(t,s,inf);
		te=tote;
		S=++totn,T=++totn;
		for(int u=1,dif;u<=tc*2+2;u++){
			dif=inflow[u]-outflow[u];
			if(dif>=0)Ae(S,u,dif);
			else Ae(u,T,-dif);
		}
	}
	void work(){
		dinic();
		int res=g[te].c;
		for(int e=te-1;e<=tote;e++)g[e].c=0;
		S=t,T=s;
		res-=dinic();
		printf("%d",res);
	}
}
int n;
void init(){
	int u,v,op;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		op=0;
		graph1::ae(u,v,op);
	}
	for(int i=1;i<=n;i++){
		u=v=i;
		op=1;
		graph1::ae(u,v,op);
	}
	m+=n;
	for(int i=1;i<=n;i++)
	if(!graph1::dfn[i])graph1::Tarjan(i);
}
void work(){
	graph2::init();
	graph2::work();
}
int main(){
	init();
	work();
	return 0;
}

```

---

## 作者：Gorenstein (赞：1)

如果读者对序理论有所了解，则容易发现这是求解**最长反链大小**的模板题。通常而言，求最长反链需要借助 Dilworth 定理转化为最小链分解，这也是本题解给出的方式。@[\_jimmywang\_](https://www.luogu.com.cn/user/90706) 则指出了一个最大权闭合子图的做法。



---

在下面的内容中，我将先介绍序理论的基本概念，并给出 Dilworth 定理的证明。对此已有了解的读者，可跳过此部分。

**定义 1.** $\quad$ 设 $P$ 为集合，资料 $(P,\leq)$ 被称作**偏序集**；其中 $\leq:P\times P\to\{0,1\}$ 是 $P$ 上的二元关系 (偏序)，满足

1. 反身性：$\forall x\in P,x\leq x$；
2. 传递性：$(x\leq y)\land(y\leq z)\Longrightarrow x\leq z$；
3. 反称性：$(x\leq y)\land(y\leq x)\Longrightarrow x=y$。

特别地，用 $x<y$ 表示 $x\leq y$ 且 $x\neq y$。$\blacksquare$

容易发现，在 $P=\{x_i\}_1^{|P|}$ 有限时，$\leq$ 的取值可表为一个 $|P|$ 阶方阵 $\Gamma_P=(p_{ij})_{1\leq i,j\leq|P|}$，其中 $p_{ij}=1\iff x_i\leq x_j$。以 $P$ 为邻接矩阵可得一个 DAG。换言之，对于有限的偏序集，若 $x\leq y$ 则由 $x$ 向 $y$ 连边，则总可以得到一个 DAG。

**定义 2.** $\quad$ 若偏序集 $P$ 的任意一对元素 $(x,y)\in P^2$ 皆可比（即，或者 $x\leq y$，或者 $y\leq x$），则称 $P$ 为**全序集**或**链**。若 集合 $E\subset P$ 满足 $\forall (x,y)\in E^2$，$x\leq y$ 与 $y\leq x$ 皆不满足，即 $x,y$ 不可比，则称 $E$ 是一条**反链**。称偏序集 $P$ 的最长反链的大小为 $P$ 的**宽度**。$\blacksquare$

**定义 3.** $\quad$ 设 $E\subset P$，$P$ 为偏序集。

- 称 $x\in P$ 为 $P$ 的**极大元**，若不存在 $y\in P$ 使得 $x<y$。
- 称 $x\in P$ 为 $E$ 的**上界**，若 $\forall y\in E$ 皆有 $y\leq x$。
- 称 $x\in P$ 为 $E$ 的**上确界**，若 $x$ 是其上界，且对于每个上界 $y$ 皆有 $x\leq y$。

同理可定义极小元、下界与下确界。$\blacksquare$

下面将给出的 Dilworth 定理是本题解做法的关键。

**定理 4. (Dilworth)** $\quad$ 设偏序集 $(P,\leq)$ 的宽度为 $m$，则存在划分 $X=\bigcup_1^mC_i$，其中每个 $C_i$ 皆为链。

**证明** $\quad$ 首先 $P$ 显然不能被划分为更少的链。下面对 $|P|$ 归纳。当 $|P|=1$ 时，结论显然成立。假设结论对 $<|P|$ 成立，考察 $|P|$ 的情形。

设 $C_1$ 为 $P$ 的一个极大链，考察 $P\backslash C_1$。若 $P\backslash C_1$ 宽度为 $m-1$ 则结论显然成立。

若 $P\backslash C_1$ 的宽度为 $m$，则设 $\{a_i\}_1^m$ 为它的一条反链，定义 $S^-:=\{x\in P:\exists i\text{ s.t. }x\leq a_i\},S^+:=\{x\in P:\exists i\text{ s.t. }x\geq a_i\}$。因 $(P,\leq)$ 的宽度为 $m$，可知 $S^-\cap S^+=\{a_1,\cdots,a_m\}$ 且 $P=S^-\cup S^+$。由于 $C_1$ 为极大链，$C_1$ 的最大元不能在 $S^-$ 中。由归纳假设知，$S^-$ 与 $S^+$ 皆可划分为 $m$ 个链 $S_i^-\,(i=1,\cdots,m)$ 与 $S_j^+\,(j=1,\cdots,m)$。易知 $a_i$ 为 $S_i^-$ 的最大元与 $S_i^+$ 的最小元。将 $S_i^-$ 与 $S_i^+$ 由 $a_i$ 合并，即将 $P$ 分为了 $m$ 个链。$\square$



---

下面回到本题来。容易发现，DAG 上可达性自然地构成了一个偏序，即，若将 DAG 的传递闭包中的有向边看作偏序关系，则它构成了一个偏序集。显然，本题中的“藏身点”需要是一条反链。因此本题正是让我们计算该偏序集的宽度，或者说其最长反链的大小。

运用 Dilworth 定理，则问题转化为求链分解的最小数目。容易发现这就是传递闭包图上的最小路径覆盖问题，运用 [P2764 最小路径覆盖问题](https://www.luogu.com.cn/problem/P2764) 的做法即可。

具体地，将原图每个点 $x$ 拆为 $x_1,x_2$ 二点，若满足 $x<y$ 则连边 $(x_1,y_2)$，形成一张二分图。该图的任意一个匹配中的一条匹配边 $(u_1,v_2)$ 代表传递闭包图上 $u,v$ 两点合并为一条路径。容易看出，匹配中一个点至多连一条匹配边的性质满足了一个点只能被一条路径覆盖的要求，故一个匹配对应一个路径覆盖，反之亦然。注意到一条匹配边会使路径数量减一，从而设最大匹配为 $x$，则 $n-x$ 即为最小路径覆盖，也就是最长反链的大小。

欲求一条具体的最长反链，可看 [\[CTSC2008\] 祭祀](https://www.luogu.com.cn/problem/P4298)（这题是最长反链模板的完全体）。@[\_jimmywang\_](https://www.luogu.com.cn/user/90706) 则给出了一个不依赖 Dilworth 定理的做法。

---

## 作者：Stone_Xz (赞：1)

## [传送门：P10938 Vani和Cl2捉迷藏](https://www.luogu.com.cn/problem/P10938)

## 简要题意：

> 给定一张有向无环图，现在需要选出最多的点，使得它们之间无法互相到达。

## 分析：

1. 若答案的点集中有某个点，这个点就会占掉图中一条路径，我们能不能看作是选路径而不是选点呢？

2. 从路径的起点可以一眼看到底，所以路径是天然最长的。不可能出现一条路径没有选到底的情况。是不是一定有方案使得选择每条路径上的一个点，他们两两无法到达？考虑两条路径相交的情况，如果无法选出这样的两个点，说明对于两条路径上的任意两点，都可以由其中一个到达另一个。那么我们固定其中一条路径的方向，两条路径的起点相通，起点方向一致；两条路径的终点也相通，终点方向也一致。那么这两条路径就可以合并成一条更长的路径，不符合路径最长的规则。我们就用反证法证明了两条路径相交的情况一定有方案。合并这两条路径，此时再加入其他的路径就又回到了我们刚刚讨论的两条路径的模型，是相同的。所以刚刚的讨论可以扩展到整张图。所以只要路径最长，就一定有方案使得选出的点集两两无法到达。所以可以将题意转换为选路径覆盖所有的点，且每条路径必须极长。

3. 路径最长意味着路径数最少，问题转换为路径可以相交的最小路径点覆盖问题。

4. 首先你需要掌握[P2764 最小路径覆盖问题](https://www.luogu.com.cn/problem/P2764)模板，接下来我们考虑如何处理“路径可以相交”这一区别。让我们手玩一张最简单的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mnj5329o.png)

如果路径不能相交，那么这张图的最小路径点覆盖为 $3$。但是如果可以相交，那么答案显然为 $2$。

由于我们不关心具体选的边，只关心最少的边的数量，所以 $4 \to 2 \to 5$ 这条边等价于一条 $4 \to 5$ 的边。如果我们加入这条边，那么就可以在路径不能相交的情况下选出 $1 \to 2 \to 3$ 和 $4 \to 5$（实际上是 $4 \to 2 \to 5$）这两条边。按照这样的想法，我们对原图跑一遍[传递闭包](https://www.luogu.com.cn/problem/B3611)，只要从点 $x$ 可以到达点 $y$，我们就让 $x$ 向 $y$ 建边，这样就可以找出路径可以相交的最小路径点覆盖了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 205;

int n, m, match[N], vis[N], tim, ans;

bool f[N][N];

vector<int> nbr[N];

bool haha(int cur) {
	for (auto nxt : nbr[cur]) {
		if (vis[nxt] == tim) continue;
		vis[nxt] = tim;
		if (!match[nxt] || haha(match[nxt])) {
			match[nxt] = cur;
			return true;
		}
	}
	return false;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y;
		f[x][y] = true;
	}
	for (int i = 1; i <= n; i++)
		f[i][i] = true;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				f[i][j] |= (f[i][k] && f[k][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) if (i != j && f[i][j]) {
			nbr[i].push_back(j);
		}
	for (int i = 1; i <= n; i++) {
		tim ++;
		if (haha(i)) ans ++;
	}
	cout << n - ans << "\n";
	return 0;
}
```

---

## 作者：Planetary_system (赞：0)

## 题面解释：
$n$ 个点 $m$ 条有向边 $u_i$ 和 $v_i$ 表示图中选择了 $u_i$ 就不能选择 $v_i$。

## 思路分析：
根据题意连起来的点只能取一个，即求最大点独立集。果断建二分图，求最大匹配。使用匈牙利算法即可。

关于匈牙利算法，即求二分图最大匹配的一种优质算法，好学好用，具体见 [这里](https://www.luogu.com.cn/article/nez5vwet)。简单地说，就是每次枚举边，能连则连，不能连则尝试让原先连好的边换一条连，递归下去，若当前点成功连接则说明增加了一条匹配，最终答案就是总数减去匹配数。

这样，你可以获得 `95pts` 的高分而 `WA`。（本不应有这么多分，数据有点水。）这时候反观题目，发现边具有传递性，即若 $1$ 指向 $2$ 而 $2$ 指向 $3$，$1$ 与 $3$ 同样不能共存，所以我们先跑一遍 $\text{Floyd}$ 即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=210;
int n,m,t,vis[N],mch[N],g[N][N];
bool dfs(const int u, const int tag) {
	if(vis[u]==tag)return 0;
	vis[u]=tag;
	for(int i=1; i<=n; i++)
		if(g[u][i]&&((mch[i]==0)||dfs(mch[i],tag)))
			{mch[i]=u;return 1;}
	return 0;
}
signed main() {
	scanf("%d%d",&n,&t);
	for(register int i=1,x,y; i<=t; i++)
		scanf("%d%d",&x,&y),g[x][y]=1;
	for(register int k=1; k<=n; k++)
		for(register int i=1; i<=n; i++)
			for(register int j=1; j<=n; j++)
				g[i][j]|=g[i][k]&g[k][j];
	int res=n;
	for(register int i=1; i<=n; i++)
		res-=dfs(i,i);
	printf("%d",res);
	return 0;
}
```

谢谢！

---

## 作者：Inter12 (赞：0)

## 题意简化

> 题目构造了一个有 $n$ 个点 $m$ 条边的有向无环图（DAG），求最多有多少个点互不相通（没有路径连接）。

## 题意转化

- 由“不连接”转化为“连接”

1. 我们不能只站在 Vani 的角度看，而应该多考虑猎人 Cl2 的角度。从他的角度，我们可以发现，他希望的就是尽可能少的去不同路径，也就是他会一条路径看到底，所以“选出互不相通的最多的点”就是最少的路径个数能覆盖到所有的点，再加上题目给出的图是有向无环图，所以我们要求的是**最小重复路径点覆盖**的路径数；

附：乍一看一般人的第一反应都是**最小路径点覆盖**，但是仔细读题后大多会明悟，这就是仔细读题的重要性。


### 插入：做法（最小路径点覆盖）

由于楼上大佬已经讲的很明白了，这里一笔带过：

#### 方法一：贪心（粗略证伪）

1. 按照贪心，路径越长数量越少，因此我们可以维护最长路径；

2. 然后，去除最长路径，找第二场路径，以此类推，直至选完。

证伪部分：

并非路径越长越好，因为一条长的路径可能会使得整个图分成很多块，剩下的路径反而更短。

#### 方法二：二分图

1. 将原图中的 $n$ 个点分别拆成出点 $O_i$ 数组和入点 $I_i$ 数组，其中出点只作为一条有向边的起始点，入边只作为一条有向边的终点。

2. 原图中的一条 $x \to y$ 的有向边，在新图中改为 $O_x \to I_y$；

3. 由于新旧图具有唯一转换性，因而他们是等价的。对于新图，跑二分图最大匹配，记其数量为 $cnt$ 条，再记原图总点数为 $n$ 个，那么最少路径数就是 $n - cnt$ 条。

### 升级（最小重复路径点覆盖）

- 由“不熟悉”转化为“熟悉”（由“相交”转化为“不相交”）

升级版本仅仅只是将“不相交”硬核变成了“相交”，那么，是否有什么办法，将此转化为上一做法呢？

#### 解决方法：传递闭包

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wz8i4amo.png)

按照最小路径点覆盖，我们可以划分为：$a \to b \to c$ 一条，点 $d$ 与点 $e$ 各自成一条。

按照最小重复路径点覆盖，我们可以划分为：$a \to b \to c$ 与 $d \to b \to e$ 各一条。

这该怎么办呢？

我们可以在 $d$ 点和 $e$ 点之间连上一条有向边，再按照最小路径点覆盖方法获取答案，当然，我们也可以在 $a$ 点和 $c$ 点之间连上一条有向边。

如图：（未连 $a$ 点和 $c$ 点）

![](https://cdn.luogu.com.cn/upload/image_hosting/ec1ch0js.png)

而这个过程，正是多条路径压缩成一条路径的过程，也正好符合传递闭包的要求。

那么，传递闭包，就是 Floyd 的任务了。

由于跑二分图最大匹配的匈牙利算法已经大约 $O(N^3)$ 级别了（实际上根本跑不满），再加上 $1 \leq N \leq 200$ 这个数据范围，因而 Floyd 的出现没什么影响。

## 主要代码

```cpp
cin >> n >> m;
for(int i = 1; i <= m; i++)
{
	int x, y;
	cin >> x >> y;
	dp[x][y] = 1;
}
// 传递闭包 
for(int k = 1; k <= n; k++)
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(dp[i][k] == 1 && dp[k][j] == 1)
				dp[i][j] = 1;
// 连接 
for(int i = 1; i <= n; i++)
	for(int j = 1; j <= n; j++)
		if(dp[i][j])
			nbr[i].push_back(j);
// 匈牙利 
for(int i = 1; i <= n; i++)
{
	if(hungary(i, ++tim)) // 打时间戳减少时间消耗 
		ans++;
}
cout << n - ans << endl;
```

### 小贴士

1. 定义数组大小时最好定义 `const int N` 来约束数组大小，不仅方便，还不容易出错，改动的时候也方便；

2. 匈牙利算法可以用打时间戳方式减少时间消耗；

3. 如果不需要卡常，最好使用 vector 数组存边的关系，方便快捷。

$$The \ End$$

---

## 作者：NTT__int128 (赞：0)

换一种角度考虑。

假如求出了可相交最少路径点覆盖的路径数 $k$。假如你是 Vani，若 cl2 选择的藏身点总数 $K>k$，则 cl2 选的藏身点中一定有两个是能互相看见的。

所以 $K\le k$，答案为 $k$。

考虑如何求取可相交最少路径点覆盖。

将所有间接相邻的点，加一条直接相连的边，再跑不相交的最少路径点覆盖。Floyd 预处理连通性即可。

时间复杂度：$\Theta(n^3+nm)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=205;
int n,m,x,y,to[N],mch[N],tim,vis[N],d[N][N];
vector<int>v[N];
bool hungary(int x){
	for(int y:v[x]){
		if(vis[y]==tim)continue;
		vis[y]=tim;
		if(!mch[y]||hungary(mch[y]))return mch[y]=x,to[x]=y,1;
	}
	return 0;
}
int main(){
	cin>>n>>m;
	while(m--)cin>>x>>y,d[x][y]=1;
	for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)d[i][j]|=(d[i][k]&d[k][j]);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i!=j&&d[i][j])v[i].push_back(j);
	int ans=0;
	for(int i=1;i<=n;i++)++tim,ans+=hungary(i);
	cout<<n-ans;
	return 0;
}
```

---

