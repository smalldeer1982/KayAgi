# Oleg and chess

## 题目描述

**题目翻译:**

有一个 $n×n$ 的矩阵，每行每列至多能放一个棋子，另外有 $q$ 个矩形的区域不能放棋子（这些矩形区域互不相交），问最多能放多少个棋子。$n,q≤10^4$

## 样例 #1

### 输入

```
5
5
1 1 2 1
1 3 1 5
4 1 5 5
2 5 2 5
3 2 3 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
8
4
2 2 4 6
1 8 1 8
7 1 8 2
5 4 6 8
```

### 输出

```
8
```

# 题解

## 作者：Rorschachindark (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF793G)
# 题目大意
给出一个 $n\times n$ 的矩阵，要求选出一些格子，使得每行每列都存在格子。但是有 $q$ 个矩阵不能选格子。

$n,q\le 10^4$
# 思路
部分思路来自于 @Rainybunny 。在此真诚地stO stO Orz Orz （大喊“wxk牛逼！”）

首先不难看出，如果没有限制的话，就相当于每一行和每一列连一条容量为 $1$ 的边，源点向每一行连一条容量为 $1$ 的边，每一列向汇点连一条容量为 $1$ 的边，答案就是最大流。（应该很显然吧。。。）然后如果有些矩阵不能选的话，那就那些行和那些列不连边就好了。

然后我们发现 $n^2$ 的边数你直接最大流能过出题人肯定会请您喝卡布奇诺和抽烟，然后我们发现这个东西我们可以用线段树优化建图做。于是问题就来了，我们如何快速知道该连的区间。

（以下思路来自于 @Rainybunny）

我们其实可以用扫描线，我们把一个限制矩阵分成两条直线，然后按横坐标排序，维护每一列的轮廓，也就是最靠右的点，然后对于一个矩阵的左边（左面的边），我们就可以看出可以分出哪些块，如图：

![](https://i.loli.net/2020/08/06/7pL5K1DvWnaxG9u.png)

（理解大意就好了）

至于一个矩阵的右边，它的影响肯定就是影响那些列的轮廓。

虽然时间复杂度是 $\Theta(n^2)$ 的，但是并不能跑满，而且贼快。

注意：**如果您的数组很大，不要memset**，我就因为这个问题调了一个晚上。。。
# $\texttt{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define INF 0x3f3f3f3f
#define MAXM 10000005
#define MAXN 50005

int n,q,S,T,top = 1,dep[MAXN],to[MAXM],wei[MAXM],nxt[MAXM],cur[MAXN],head[MAXN];
void Add_Edge (int u,int v,int w){
	to[++ top] = v,wei[top] = w,nxt[top] = head[u],head[u] = top;
	to[++ top] = u,wei[top] = 0,nxt[top] = head[v],head[v] = top;
} 
bool BFS (){
	for (Int i = 1;i <= T;++ i) cur[i] = head[i],dep[i] = INF;
	queue <int> q;while (!q.empty()) q.pop ();dep[S] = 0,q.push (S);
	while (!q.empty()){
		int u = q.front();q.pop ();
		for (Int i = head[u];i;i = nxt[i]){
			int v = to[i],w = wei[i];
			if (dep[v] == INF && w){
				dep[v] = dep[u] + 1;
				q.push (v);
			}
		}
	}
	return dep[T] != INF;
}
int dfs (int u,int lim){
	if (u == T) return lim;
	int used = 0;
	for (Int i = cur[u];i && lim;i = nxt[i]){
		cur[u] = i;int v = to[i],w = wei[i];
		if (dep[v] == dep[u] + 1 && w){
			int del = dfs (v,min (lim,w));
			used += del,lim -= del,wei[i] -= del,wei[i ^ 1] += del;
		}
	}
	if (used == 0) dep[u] = INF;
	return used;
}
int Dinic (){
	int res = 0;
	while (BFS ()) res += dfs (S,INF);
	return res;
}
int sizt;
int id (int l,int r,int type){return type * sizt + ((l + r) | (l != r));}
void build (int l,int r,int type){
	int rt = id (l,r,type);
	if (l == r){
		if (type == 0) Add_Edge (S,rt,1);
		if (type == 1) Add_Edge (rt,T,1);
		return ;
	}
	int mid = (l + r) >> 1;
	build (l,mid,type),build (mid + 1,r,type);
	if (type == 0) Add_Edge (id (l,mid,type),rt,INF),Add_Edge (id (mid + 1,r,type),rt,INF);
	else Add_Edge (rt,id (l,mid,type),INF),Add_Edge (rt,id (mid + 1,r,type),INF);
}

#define PII pair<int,int>
#define MP make_pair

void modify (int l,int r,int type,int tl,int tr,vector<PII> &s){
	if (l >= tl && r <= tr) return s.push_back (MP (id (l,r,type),r - l + 1));
	int mid = (l + r) >> 1;
	if (tl <= mid) modify (l,mid,type,tl,tr,s);
	if (tr > mid) modify (mid + 1,r,type,tl,tr,s); 
}
void update (int tl,int tr,int ql,int qr){
	static vector <PII> A,B;A.clear(),B.clear();
	modify (1,n,0,tl,tr,A),modify (1,n,1,ql,qr,B);
	for (Int i = 0;i < A.size();++ i) for (Int j = 0;j < B.size();++ j) Add_Edge (A[i].first,B[j].first,A[i].second * B[j].second);   
}

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

struct node{
	int r1,r2,c;bool type;
	bool operator < (const node &p)const{return c != p.c ? c < p.c : type < p.type;}
}mat[MAXN];
int lef[MAXN];
void Scan (){//输入+扫描线 
	read (n,q);int tot = 0;
	for (Int i = 1,r1,r2,c1,c2;i <= q;++ i) read (r1,c1,r2,c2),mat[++ tot] = node {r1,r2,c1,0},mat[++ tot] = node {r1,r2,c2,1};
	mat[++ tot] = node {1,n,n + 1,0},mat[++ tot] = node {1,n,n + 1,1};
	sort (mat + 1,mat + tot + 1);
	sizt = id (n,n,0);
	S = sizt * 2 + 3,T = S + 1;
	build (1,n,0),build (1,n,1);
	for (Int i = 1;i <= tot;++ i){
		if (mat[i].type == 1) for (Int j = mat[i].r1;j <= mat[i].r2;++ j) lef[j] = mat[i].c;
		else{
			for (Int j = mat[i].r1,lasw = mat[i].c - 1,lash = 0;j <= mat[i].r2 + 1;++ j){
				if (j == mat[i].r2 + 1 || lef[j] ^ lasw){
					if (lasw + 1 < mat[i].c) update (lash,j - 1,lasw + 1,mat[i].c - 1);
					lasw = lef[j],lash = j;
				}
			}
		}
	} 
}

signed main(){
	Scan ();
	write (Dinic ()),putchar ('\n');
	return 0;
}
```


---

## 作者：YCS_GG (赞：5)

比较套路的题

如果没有矩阵的限制就是每行每列互相连边跑最大匹配，禁止的点不能连边，但是 $n^2$ 的边数会 T

观察连边可以发现绝大部分边都是一个点连向某一个区间，那就考虑线段树优化建图

具体的可以用扫描线的思路，把矩阵左边界的 $(y_1,y_2)$ 置为不能选，右边界再去掉限制，新建点向这一列内连边即可

注意需要先加后删

边数为 $n\log n$ 级别，网络流跑不满所以能过

```cpp
#include <array>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int N   = 1e4 + 5;
const int INF = 0x7f7f7f7f;
struct Graph {
    struct Node {
        int v, w, nxt;
    };
    std::vector<int> head;
    std::vector<Node> edge;
    Graph() {
    }
    Graph(int n) : head(n + 1, -1){};
    void resize(int n) {
        head.assign(n + 1, -1);
    }
    void add(int u, int v, int w) {
        if (head.size() < u) {
            head.reserve(u * 2);
        }
        edge.emplace_back(Node{v, w, head[u]});
        head[u] = edge.size() - 1;
    }

    void add_flow(int u, int v, int w) {
        add(u, v, w);
        add(v, u, 0);
    }
};
namespace NetworkFlow {
std::vector<int> level;
bool bfs(int S, int T, const Graph &G) {
    level.assign(G.head.size(), 0);
    level[S] = 1;
    std::queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = G.head[now]; ~i; i = G.edge[i].nxt) {
            int v = G.edge[i].v;
            if (!level[v] && G.edge[i].w) {
                level[v] = level[now] + 1;
                q.push(v);
            }
        }
    }
    return level[T];
}
std::vector<int> cur;
int dfs(int x, int T, int maxflow, Graph &G) {
    if (x == T) {
        return maxflow;
    }
    int res = 0;
    for (int i = cur[x]; ~i && res < maxflow; i = G.edge[i].nxt) {
        cur[x] = i;
        int v  = G.edge[i].v;
        if (G.edge[i].w && level[v] == level[x] + 1) {
            int x = dfs(v, T, std::min(G.edge[i].w, maxflow - res), G);
            if (x) {
                G.edge[i].w -= x;
                G.edge[i ^ 1].w += x;
                res += x;
            }
        }
    }
    if (res < maxflow) {
        level[x] = -1;
    }
    return res;
}
int MaxFlow(const int S, const int T, const Graph &G) {
    cur.resize(G.head.size());
    level.resize(G.head.size());
    Graph tmpG = G;
    int res    = 0;
    while (bfs(S, T, tmpG)) {
        cur.assign(tmpG.head.begin(), tmpG.head.end());
        int x;
        while (x = dfs(S, T, INF, tmpG)) {
            res += x;
        }
    }
    return res;
}
} // namespace NetworkFlow
int S, T;
Graph G;
array<int, N * 20> id, col;
int idcnt;
namespace SegmentTree {
using namespace NetworkFlow;
#define ls(x) (x * 2)
#define rs(x) (x * 2 + 1)
void build(int rt, int l, int r) {
    if (l == r) {
        id[rt] = l;
        G.add_flow(l, T, 1);
        col[rt] = l;
        return;
    }
    id[rt] = col[rt] = ++idcnt;
    int mid          = (l + r) / 2;
    build(ls(rt), l, mid);
    build(rs(rt), mid + 1, r);
    G.add_flow(col[rt], col[ls(rt)], INF);
    G.add_flow(col[rt], col[rs(rt)], INF);
}
void update(int rt, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) {
        if (v) {
            id[rt] = col[rt];
        } else {
            id[rt] = -1;
        }
        return;
    }
    int mid = (l + r) / 2;
    id[rt]  = ++idcnt;
    if (L <= mid) {
        update(ls(rt), l, mid, L, R, v);
    }
    if (mid < R) {
        update(rs(rt), mid + 1, r, L, R, v);
    }
    if (id[ls(rt)] != -1) {
        G.add_flow(id[rt], id[ls(rt)], INF);
    }
    if (id[rs(rt)] != -1) {
        G.add_flow(id[rt], id[rs(rt)], INF);
    }
}
#undef ls
#undef rs
} // namespace SegmentTree
int n, q;
vector<pair<int, int>> st[N], ed[N];
int main() {
    cin >> n >> q;
    G.resize(n * 80);
    S = idcnt = n + 1;
    T         = S + 1;
    for (int i = 1; i <= q; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        st[x1].emplace_back(make_pair(y1, y2));
        ed[x2 + 1].emplace_back(make_pair(y1, y2));
    }
    SegmentTree::build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        for (auto v : ed[i]) {
            SegmentTree::update(1, 1, n, v.first, v.second, 1);
        }
        for (auto v : st[i]) {
            SegmentTree::update(1, 1, n, v.first, v.second, 0);
        }
        if (id[1] != -1)
            G.add_flow(S, id[1], 1);
    }
    cout << NetworkFlow::MaxFlow(S, T, G);
    return 0;
}
// Asusetic eru quionours
```

---

## 作者：louhao088 (赞：4)

线段树优化建图网络流好题。


------------

首先我们很容易想出一个套路的网络流做法，直接把原点向横轴连边，纵轴向汇点连边，能选的点则横轴向纵轴连边。

但是这样的图是 $n^2$ 级别的很明显不能通过。


------------

考虑用线段树优化。

我们可以用动态开点线段树维护每个横轴能选的纵轴状态，具体的考虑对每个矩形用类似扫描线的方法，差分线段，从前往后在线段树上加即可，如果那个子树没有被标记就连一条由其祖先向其流量为 1 的连边。

然后我们发现我们其实只需要维护图上信息，根本不用动态开点线段树，只要对图上的点动态开点就可以了。这个用一个数组记录现在线段树上这个节点在图上代表的点即可。


------------


这样建图点数和边数都是 $n \log n$ 级别的，建完图后跑最大流即可。

由于网络流跑不满，整个程序跑的飞快，最慢的点也在 1s 左右。


------------
代码如下

```cpp
// Problem: CF793G Oleg and chess
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF793G
// Memory Limit: 250 MB
// Time Limit: 6500 ms
// 2022-02-14 11:30:23
// Author : louhao088
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
#define lowbit (x&-x)
const int maxn=1e5+5,M=34005,inf=1e9;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,s,t,tot,tag[maxn*4],id[maxn*4],lx,ly,rx,ry;
struct node{int l,r,x;};
vector<node>a[maxn];
struct Dinic
{
	int head[maxn*20],to[maxn*40],nex[maxn*40],w[maxn*40],cnt=1,dis[maxn*20],cur[maxn*20],vis[maxn*20],sum,maxflow;
	void add(int x,int y,int z){to[++cnt]=y,w[cnt]=z,nex[cnt]=head[x],head[x]=cnt;
	to[++cnt]=x,w[cnt]=0,nex[cnt]=head[y],head[y]=cnt;}
	void clear(){memset(head,0,sizeof head),memset(cur,0,sizeof cur),cnt=1,maxflow=0;memset(vis,0,sizeof vis);}
	bool bfs()
	{
		for(int i=1;i<=tot;i++)dis[i]=-1;
		queue<int>q;q.push(s);cur[s]=head[s];dis[s]=0;		
		while(!q.empty())
		{
			int x=q.front();q.pop();
			for(int i=head[x];i;i=nex[i])
				if(dis[to[i]]==-1&&w[i])
					dis[to[i]]=dis[x]+1,q.push(to[i]),cur[to[i]]=head[to[i]];
		}
		return dis[t]!=-1;
	}
	int dfs(int x,int flow)
	{
		if(x==t)return flow;
		int sum=0;
		for(int i=cur[x];i&&flow;i=nex[i])
		{
			cur[x]=i;
			if(w[i]&&dis[to[i]]==dis[x]+1)
			{
				int k=dfs(to[i],min(flow,w[i]));
				flow-=k,sum+=k;w[i]-=k,w[i^1]+=k;
			}
		}return sum;
	}
	void work()
	{
		while(bfs())maxflow+=dfs(s,inf);
	}
}G;
void pushup(int rt)
{
	id[rt]=++tot;
	if(!tag[ls])G.add(id[rt],id[ls],inf);
	if(!tag[rs])G.add(id[rt],id[rs],inf);
}
void build(int rt,int l,int r)
{
	if(l==r){id[rt]=l+n;return;}
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(rt);
}
void change(int rt,int l,int r,int L,int R,int x)
{
	if(l>R||r<L)return;
	if(l>=L&&r<=R){tag[rt]+=x;return;}
	change(ls,l,mid,L,R,x);change(rs,mid+1,r,L,R,x);
	pushup(rt);
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();tot=2*n+2,s=2*n+1,t=2*n+2;G.cnt=1;
	for(int i=1;i<=m;i++)
	{
		lx=read(),ly=read();rx=read(),ry=read();
		a[lx].pb((node){ly,ry,1}),a[rx+1].pb((node){ly,ry,-1});
	}
	for(int i=1;i<=n;i++)G.add(s,i,1),G.add(i+n,t,1);
	build(1,1,n);
	for(int i=1;i<=n;i++)
	{
		for(auto j:a[i])
			change(1,1,n,j.l,j.r,j.x);
		if(!tag[1])G.add(i,id[1],inf);
	}
	G.work();cout<<G.maxflow<<endl;
 	return 0;
}


```


---

## 作者：K8He (赞：2)

[Oleg and chess .](https://codeforces.com/problemset/problem/793/G)

不考虑数据范围，问题是一个经典的行向列连边的二分图模型。然而 $O(n^2)$ 的边数过大，需要在建图上进行一定优化。

很容易想到套路是线段树优化建图，可以利用扫描线维护出当前行仍可向哪些区间里的列连边，不能影响之前行的连边所以使用类似于主席树的方式维护。

这样做点数是 $O(n + q\log n)$ 的，边数同样是 $O(n + q\log n)$ 的，虽然主席树区间修改时点数附带巨大常数但是难以卡满所以可以通过此题。

可能是我写得比较有问题需要一定程度卡常，卡完后最后一个点跑了 6421ms/6500ms，流汗。

[CodeForces Submission .](https://codeforces.com/contest/793/submission/262100899)

---

## 作者：chlchl (赞：1)

水题，直接暴力撵（doge）。

考虑将行作为左部点，列为右部点，如果 $(x,y)$ 能放棋子，我们就 $x\rightarrow y$ 连边，这样最后跑一个二分图最大匹配就是答案了。

使用 ``bitset`` 优化空间，剩下时间问题。

这时我们直接加上一个“当前弧”优化，即可顺利通过！！！！！！

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n, q, cp[N], cur[N];
bitset<N> mp[N], vis;

bool aug(int u){
	for(int &v=cur[u];v<=n;v++){
		if(mp[u][v] || vis[v])
			continue;
		vis[v] = 1;
		if(!cp[v] || aug(cp[v])){
			cp[v] = u;
			return 1;
		}
	}
	return 0;
}

int main(){
	scanf("%d%d", &n, &q);
	for(int i=1,x,y,xx,yy;i<=q;i++){
		scanf("%d%d%d%d", &x, &y, &xx, &yy);
		for(int nx=x;nx<=xx;nx++)
			for(int ny=y;ny<=yy;ny++)
				mp[nx].set(ny);
	}
	int cnt = 0;
	for(int i=1;i<=n;i++)
		cur[i] = 1;
	for(int i=1;i<=n;i++){
		vis.reset();
		if(aug(i))
			++cnt;
	}
	printf("%d\n", cnt);
	return 0;
}
```


---

## 作者：Anoshag_Ruwan (赞：0)

NOIP 前想发题解但拖到现在的题。

首先如果不管数据范围，这就是二分图匹配的板子题，若 $(x1,y1)$ 可以放置棋子，就从 $a_{x1}$ 到 $b_{y1}$ 连边，最大匹配数即为答案。但本题中如果显式建图边数会达到喜人的 $10^8$ 级别，于是显然需要更优的方案。

换个角度，如果将题意改为若干个不相交矩形区域可以摆放棋子，则对于矩形 $(x1,x2,y1,y2)$，需要对 $x \in [x1,x2]$ 的每个 $x$ 向 $y \in [y1,y2]$ 的每个 $y$ 连边，这是线段树优化建图的标准应用场景。所以只需要将输入的补集划分为若干矩形。考虑扫描线，对于先把矩阵的横向边缘分为上缘和下缘两种，从下往上扫。将划分矩形的过程具象成“填坑”~~（奇妙比喻）~~，用 set 维护当前纵坐标下的极大连续段即“坑”的位置，线段树维护一段连续的“坑”向下达到的深度。当遇到下边缘时，直接对这一段填坑，遇到上边缘时，则对其左端点左边、右端点右边的小连续段填坑，并将其合并为一个大坑。由该过程容易发现其划分不重不漏，且矩形个数是 $O(q)$ 的，整体边数为 $O(q \log n)$，dinic 可以通过。

注意一些细节，比如同一纵坐标下要先处理下边缘再处理上边缘，以及“坑”不存在的情况，代码 $4096$ 字节~~强迫症患者狂喜~~。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define lw(x) *u.lower_bound(x)
using namespace std;
struct ltk{
	long long l1,r1;
	friend bool operator <(ltk x,ltk y){return x.r1==y.r1?x.l1>y.l1:x.r1<y.r1;}
	friend bool operator >(ltk x,ltk y){return x.r1==y.r1?x.l1<y.l1:x.r1>y.r1;}
};set<ltk>u;
struct dir{long long l,r,ht,p;}a[300011];
inline bool s1(dir x,dir y)
	{return x.ht==y.ht?x.l<y.l:x.ht<y.ht;}
struct sgtr{long long l,r,lz;}tr[800011],tr1[800011],tr2[800011];
long long m=1,hd[600011],fl,nt[2000011],b[2000011],inf=1e9,n,p,c[2000011],nw[600011],lv[600011],que[600011],s=1,t;
inline long long minn(long long x,long long y){return x<y?x:y;}
inline void addln(long long x,long long y,long long z){
	nt[++m]=hd[x],b[m]=y,hd[x]=m,c[m]=z;
	nt[++m]=hd[y],b[m]=x,hd[y]=m;}
inline long long rd(){
	long long i=0,j=1;char g=getchar();
	while(g>57||g<48)g=getchar();
	while(g>47&&g<58)i=(i<<3)+(i<<1)+g-48,g=getchar();
	return i*j;
}
inline long long dinitz(long long x,long long y){
	long long i,q=0,k;
	if(x==t||!y)return y;
	for(i=nw[x];i;i=nt[i]){nw[x]=i;
		if(lv[b[i]]==lv[x]+1&&c[i]){
			k=dinitz(b[i],minn(c[i],y));
			q+=k,y-=k,c[i]-=k,c[i^1]+=k;
			if(!y)break;}
	}if(!q)lv[x]=0;
	return q;
} 
inline long long maxxflow(){
	long long i,h,tl,ans=0;
	while(1){
		h=1,tl=2;que[h]=s;
		for(i=1;i<=t;i++)nw[i]=hd[i],lv[i]=0;lv[s]=1;
		while(h<tl){
			for(i=hd[que[h]];i;i=nt[i])
				if(!lv[b[i]]&&c[i])
					lv[b[i]]=lv[que[h]]+1,que[tl++]=b[i];h++;}
		if(!lv[t])break;ans+=dinitz(s,inf);
	}return ans;
}

inline void build(sgtr *f,long long w,long long x,long long y){
	f[w].l=x,f[w].r=y;
	if(w!=1&&fl==1)addln(w<<1,w-(w&1),inf);
	if(w!=1&&fl==2)addln(w+(w&1^1),(w<<1)+1,inf);
	if(x==y){
		if(fl==1)addln(s,w<<1,1);
		if(fl==2)addln((w<<1)+1,t,1);
		return;}
	long long mid=x+y>>1;
	build(f,w<<1,x,mid);build(f,(w<<1)+1,mid+1,y);
}
inline void pdown(long long x){
	if(tr[x].l==tr[x].r||!tr[x].lz)return;
	int k=tr[x].lz;tr[x].lz=0;
	tr[x<<1].lz=tr[(x<<1)+1].lz=k;}
inline void fz(long long w,long long x,long long y,long long z){
	if(tr[w].l>=x&&tr[w].r<=y)
		{tr[w].lz=z;pdown(w);return;}
	int mid=tr[w].l+tr[w].r>>1;pdown(w);
	if(x<=mid)fz(w<<1,x,y,z);
	if(y>mid)fz((w<<1)+1,x,y,z);
}
inline long long qry(long long w,long long x){
	if(tr[w].l==tr[w].r)return tr[w].lz;
	int mid=tr[w].l+tr[w].r>>1;pdown(w);
	return x<=mid?qry(w<<1,x):qry((w<<1)+1,x);
}
inline void add(long long w,long long x,long long y,long long z){
	int mid=tr1[w].l+tr1[w].r>>1;
	if(tr1[w].l>=x&&tr1[w].r<=y){
		if(z>0)addln(w<<1,z,inf);
		else addln(-z,(w<<1)+1,inf);
		return;
	}if(x<=mid)add(w<<1,x,y,z);
	if(y>mid)add((w<<1)+1,x,y,z);
}
inline void admtr(long long x1,long long x2,long long y1,long long y2){
	if(x2<x1||y2<y1)return;
	add(1,x1,x2,++p);add(1,y1,y2,-p);
}
int main()
{
	long long i,j,k,k1,v,m,n=rd(),q=rd();t=(n<<3)+(q<<2)+4;
	for(i=1,k=1;i<=q;i++){
		a[++k].ht=rd(),a[k].l=a[k+1].l=rd(),a[k].p=1;
		a[++k].ht=rd(),a[k-1].r=a[k].r=rd(),a[k].p=-1;
	}a[1]=(dir){1,n,n+1,1};q=(q<<1)+1; 
	sort(a+1,a+q+1,s1);
	build(tr,1,1,n);p=(n<<3)+2;
	fl=1;build(tr1,1,1,n);fl=2;build(tr2,1,1,n);
	ltk x={n+1,n+1},y={1,n};u.insert(x),u.insert(y);
	for(i=1;i<=q;i++){
		for(j=i;a[j].ht==a[i].ht;j++);v=j-1;
		for(j=i;j<=v;j++){ 
			if(a[j].p>0){
				x={a[j].l,a[j].r},y=lw(x);
				if(y.l1<a[j].l){x=(ltk){y.l1,a[j].l-1};u.insert(x);}
				if(a[j].r<y.r1){x=(ltk){a[j].r+1,y.r1};u.insert(x);}
				u.erase(y);
				admtr(qry(1,a[j].l)+1,a[j].ht-1,a[j].l,a[j].r);
				fz(1,a[j].l,a[j].r,a[j].ht);}
		}for(j=i;j<=v;j++)
			if(a[j].p<0){
				k1=a[j].r,k=a[j].l;
				x={a[j].l,a[j].r},y=lw(x);
				if(y.l1==a[j].r+1&&a[j].r!=n){
					admtr(qry(1,y.r1)+1,a[j].ht,a[j].r+1,y.r1);
					k1=y.r1,u.erase(y);
				}x=(ltk){a[j].l-1,a[j].l-1},y=lw(x);
				if(y.r1<a[j].l){
					admtr(qry(1,y.l1)+1,a[j].ht,y.l1,a[j].l-1);
					k=y.l1,u.erase(y);}
				if(k<=k1){x=(ltk){k,k1},u.insert(x);}
				y=lw(x);
				fz(1,y.l1,y.r1,a[j].ht);}i=v;
	}printf("%lld\n",maxxflow());
	return 0;
}
```


---

