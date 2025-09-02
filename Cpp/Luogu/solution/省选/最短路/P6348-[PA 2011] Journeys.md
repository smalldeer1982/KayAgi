# [PA 2011] Journeys

## 题目描述

一个星球上有 $n$ 个国家和许多双向道路，国家用 $1\sim n$ 编号。

但是道路实在太多了，不能用通常的方法表示。于是我们以如下方式表示道路：$(a,b),(c,d)$ 表示，对于任意两个国家 $x,y$，如果 $a\le x\le b,c\le y\le d$，那么在 $x,y$ 之间有一条道路。

首都位于 $P$ 号国家。你想知道 $P$ 号国家到任意一个国家最少需要经过几条道路。保证 $P$ 号国家能到任意一个国家。

## 说明/提示

对于所有测试点，保证 $1\le n\le 5\times 10^5$，$1\le m\le 10^5$，$1\le a\le b\le n$，$1\le c\le d\le n$。

## 样例 #1

### 输入

```
5 3 4
1 2 4 5
5 5 4 4
1 1 3 3```

### 输出

```
1
1
2
0
1```

# 题解

## 作者：_Diu_ (赞：30)

[题目传送门](https://www.luogu.com.cn/problem/P6348)

# 线段树优化建图

我们可以从最朴素的思路开始想起。

## 0.0 暴力建图

对于一堆道路 $(a,b),(c,d)$，两两连边。

## 1.0 连向公共边

对于一堆道路 $(a,b),(c,d)$，我们让 $(a,b)$ 连向一个虚拟点 $k$，

再从 $k$ 向 $(c,d)$ 连边。

但是这样总共要连 $2nm$ 条边，肯定会炸。

所以要想办法优化连边的边数。

## 2.0 线段树优化建图

这个时候线段树重磅出击。

- **性质 2.1** 对于一个区间的点 $(l,r)$，一个包含它的区间 $(L,R)$ 连向的点，那么 $(l,r)$ 也能连向。

- **性质 2.2** 对于一个区间的点 $(l,r)$，另一个点 $a$ 如果能到达一个包含 $(l,r)$ 区间 $(L,R)$，那么点 $a$ 也能到达 $(l,r)$。

**由此，我们便可建出两棵线段树，进树和出树。**

**同时，这也是为什么进树从父节点连向子节点，二出树从子节点连向父节点的原因。**

不把两棵树建到一块，是为了防止直接顺着线段树直接走完所有点。

而对于一个区间 $(l,r)$ 它在进树、出树本质上是一个点。

所以**经过某条边到达进树后，可以回到出树继续走下一条边**。

也就是说进树的点直接连向对应的出树的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/lbokvrg5.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/df63re4h.png)

图中绿色的边权之标上 $1$，但是最后答案要除以 $2$。

因为从 $(a,b)$ 连到 $(c,d)$ 经过两条绿边，路程算了 $2$，但其实只用算一条，所以要除以 $2$。

或者连向绿点的边和绿点连出的边任意一个标权值也可以。

## code

```cpp
#include<bits/stdc++.h>
#define ls(o) (o<<1)
#define rs(o) (o<<1|1)
//#define int long long
using namespace std;
const int N=500010,M=4200010;
int n,m,p,out,num[N];
struct edge{
    int v,w;
};
vector<edge> g[M];
void build_in(int o,int l,int r){
    if(l==r)return;
    int mid=l+r>>1;
    build_in(ls(o),l,mid);
    build_in(rs(o),mid+1,r);
    g[o].push_back({ls(o),0});
    g[o].push_back({rs(o),0});
}
void build_out(int o,int l,int r){
    g[o].push_back({o+n*4,0});
    if(l==r)return (void)(num[l]=o+n*4);
    int mid=l+r>>1;
    build_out(ls(o),l,mid);
    build_out(rs(o),mid+1,r);
    g[ls(o)+n*4].push_back({o+n*4,0});
    g[rs(o)+n*4].push_back({o+n*4,0});
}
void merge1(int o,int l,int r,int x,int y,int k){
    if(l>=x&&r<=y)return (void)(g[k].push_back({o,1}),g[o+n*4].push_back({k+1,1}));
    int mid=l+r>>1;
    if(mid>=x)merge1(ls(o),l,mid,x,y,k);
    if(mid<y)merge1(rs(o),mid+1,r,x,y,k);
}
void merge2(int o,int l,int r,int x,int y,int k){
    if(l>=x&&r<=y)return (void)(g[k+1].push_back({o,1}),g[o+n*4].push_back({k,1}));
    int mid=l+r>>1;
    if(mid>=x)merge2(ls(o),l,mid,x,y,k);
    if(mid<y)merge2(rs(o),mid+1,r,x,y,k);
}
int d[M];
bool vis[M];
deque<int> q;
void dijstra(int s){
    memset(d,127,sizeof(d));
    d[s]=0;
    q.push_front(s);
    while(!q.empty()){
        int u=q.front();
        q.pop_front();
//      if(vis[u])continue;
//      vis[u]=1;
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i].v;
//          if(vis[v])continue;
            int w=g[u][i].w;
            if(d[v]>d[u]+w){
                d[v]=d[u]+w;
                if(w==1)q.push_back(v);
                else q.push_front(v);
            }
        }
    }
}
inline char nc(){
    static char buf[1000010],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000010,stdin),p1==p2)?EOF:*p1++;
}
//#define nc getchar
inline int read(){
    register int s=0,w=0;
    static char ch=nc();
    for(;!isdigit(ch);)ch=nc();
    for(;isdigit(ch);){
        s=(s<<1)+(s<<3)+(ch^48);
        ch=nc();
    }
    return w?-s:s;
}
signed main(){
    n=read(),m=read(),p=read();
    build_in(1,1,n);
    build_out(1,1,n);
    for(register int a,b,c,d,i=1;i<=m;++i){
        a=read(),b=read(),c=read(),d=read();
        merge1(1,1,n,a,b,n*8+i*2);
        merge2(1,1,n,c,d,n*8+i*2);
    }
    dijstra(num[p]);
    for(register int i=1;i<=n;++i)printf("%d\n",d[num[i]]/2);
//  for(int i=1;i<=tot;i++){
//    printf("%lld %lld %lld %lld:\n",i,tr[i].l,tr[i].r,g[i].size());
//    for(int j=0;j<g[i].size();j++)printf("%lld %lld\n",g[i][j].v,g[i][j].w);
//  }
}
```

---

## 作者：hs_black (赞：26)


## 解题思路

当然这是一道线段树优化建图模板题，但我们有更简单更快的做法

请想象一下超级暴力 bfs 的过程，我们从 s 点开始 bfs，扫一遍找到包含 s 的区间，从而轻松找到和 s 距离为 1 的点，我们再用距离为 1 的点找到距离为 2 的点

这样显然很暴力，但可喜的是，我们有些地方还可以优化

* bfs 过程中每个点只被更新一次且只更新别人一次
* 需要快速找到包含 s 的区间，并删之

那么第一个优化我们直接用并查集就可以维护，这是经典套路不再多说

第二个优化使用线段树，将区间挂在线段树上，询问时直接把根节点到对应叶子节点上挂的区间全部扔到队列中并删除

总复杂度 $\Theta((n+m)log_n$ 温馨提示：最好不要用 vector 。目前是最优解

```cpp
const int M = 200500;
const int N = 500500;
int m, n, s;
int l1[M], r1[M], l2[M], r2[M];
bool vis[N]; int dis[N], f[N];

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

#define ls p << 1
#define rs ls | 1

struct node {
	int l, r, k;
}q[N];
int h[N<<2], ne[N<<4], to[N<<4], tot;
inline void add(int x, int y) {
	ne[++tot] = h[x], to[h[x] = tot] = y;
}

void change(int p, int l, int r, int L, int R, int k) {
	if (L <= l && r <= R) return add(p, k);
	int mid = (l + r) >> 1;
	if (L <= mid) change(ls, l, mid, L, R, k);
	if (mid < R) change(rs, mid + 1, r, L, R, k);
}

int L, R;
void update(int p, int l, int r, int x, int k) {
	if (h[p]) {
		for (int i = h[p]; i; i = ne[i]) {
			int tp = to[i];
			if (!vis[tp]) q[++R] = ((node){l2[tp], r2[tp], k}), vis[tp] = 1;
		}
		h[p] = 0;
	}
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (x <= mid) update(ls, l, mid, x, k);
	else update(rs, mid + 1, r, x, k); 
}

void bfs(int s) {
	L = 1, R = 0;
	q[++R] = ((node){s, s, 0});
	while (L <= R) {
		node x = q[L++];
		for (int i = find(x.l); i <= x.r; i = find(i + 1)) 
			update(1, 1, n, i, x.k + 1), dis[i] = x.k, f[i] = i + 1;
	}
}

int main() {
	read(n), read(m), read(s);
	for (int i = 1;i <= m; i++) {
		read(l1[i]), read(r1[i]), read(l2[i]), read(r2[i]);
		change(1, 1, n, l1[i], r1[i], i); 
		l1[i + m] = l2[i], r1[i + m] = r2[i];
		l2[i + m] = l1[i], r2[i + m] = r1[i];
		change(1, 1, n, l2[i], r2[i], i + m);
	}
	for (int i = 1;i <= n + 1; i++) f[i] = i; bfs(s);
	for (int i = 1;i <= n; i++) write(dis[i]);
	return 0;
}

```



---

## 作者：feecle6418 (赞：18)

线段树优化建图模板题。

建立一棵入树，一棵出树，对于每次连边建两个虚点，在其间连一条权为一的边；然后从出树连出来，连进去入树，边权均为 $0$。注意边是双向的，因此需要做两遍。

最短路不需要 Dijkstra，只需要 01BFS。时间复杂度 $O(n\log n)$。

核心代码：

```cpp
int n,q,S,tot,ls[4000005],rs[4000005],dis[4000005],h[4000005],cnt;
struct Edge{
	int to,next,value;
}e[8000005];
void AddEdge(int x,int y,int z){
	e[++cnt]={y,h[x],z};
	h[x]=cnt;
}
void Dijkstra() {
	memset(dis,0x3f,sizeof(dis));
	deque<int> q;
	dis[S]=0;
	q.push_back(S);
	while(!q.empty()) {
		int now=q.front();
		q.pop_front();
		for(int i=h[now]; i; i=e[i].next) {
			int y=e[i].to,v=e[i].value;
			if(dis[y]>dis[now]+v) {
				dis[y]=dis[now]+v;
				if(v)q.push_back(y);
				else q.push_front(y);
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%d\n",dis[i]);
}
void Build(int &p,int &q,int l,int r) {
	if(l==r){
		p=l,q=l;
		return ;
	}
	if(!p)p=++tot;
	if(!q)q=++tot;
	int mid=(l+r)/2;
	Build(ls[p],ls[q],l,mid),AddEdge(ls[p],p,0),AddEdge(q,ls[q],0);
	Build(rs[p],rs[q],mid+1,r),AddEdge(rs[p],p,0),AddEdge(q,rs[q],0);
}
void Add(int p,int l,int r,int x,int y,int z,int flag) {
	if(x<=l&&r<=y) {
		if(flag)AddEdge(z,p,0);
		else AddEdge(p,z,0);
		return ;
	}
	int mid=(l+r)/2;
	if(x<=mid)Add(ls[p],l,mid,x,y,z,flag);
	if(mid<y)Add(rs[p],mid+1,r,x,y,z,flag);
}
int main() {
	n=read(),q=read(),S=read(),tot=n;
	int root1=0,root2=0;
	Build(root1,root2,1,n);
	while(q--){
		int x=read(),y=read(),z=read(),w=read(),a=++tot,b=++tot;
		AddEdge(a,b,1);
		Add(root1,1,n,x,y,a,0);
		Add(root2,1,n,z,w,b,1);
		a=++tot,b=++tot;
		AddEdge(a,b,1);
		Add(root1,1,n,z,w,a,0);
		Add(root2,1,n,x,y,b,1);
	}
	Dijkstra();
}
```

---

## 作者：cymrain07 (赞：10)

![](https://i.loli.net/2021/09/04/o7qUxj13fWIntGQ.png)
首先建出两颗线段树，一颗入树，一颗出树。  
入树中连边 $(fa,son,0)$，出树中连边 $(son,fa,0)$。  
并且两棵树中对应的节点也要连权为 $0$ 的边，代表可以从该区间重新出发。  
每次连边时，新建一个虚拟节点，出树对应区间向虚拟节点连权为 $0$ 的边，虚拟节点向入树连权为 $1$ 的边。  
注意无向边要连两次。  
最后用 01-BFS 跑最短路。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 4200005
typedef pair<int, bool> pii;
vector<pii> e[N];
void add(int u, int v, bool w) { e[u].push_back({v, w}); }
int n, m, p, tot;
int num[N], dis[N];
#define rt 1, 1, n
#define lpos (pos << 1)
#define rpos (lpos | 1)
#define lson lpos, l, mid
#define rson rpos, mid + 1, r
void bld(int pos, int l, int r)
{
    add(pos + 4 * n, pos, 0);
    if (l == r)
        return num[l] = pos, void();
    add(lpos, pos, 0), add(rpos, pos, 0);
    add(pos + 4 * n, lpos + 4 * n, 0), add(pos + 4 * n, rpos + 4 * n, 0);
    int mid = (l + r) >> 1;
    bld(lson), bld(rson);
}
void Add(int pos, int l, int r, int L, int R, bool op) //0 出树 1 入树
{
    if (L <= l && r <= R)
    {
        if (op == 0)
            add(pos, 8 * n + tot, 0);
        else
            add(8 * n + tot, pos + 4 * n, 1);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid)
        Add(lson, L, R, op);
    if (R > mid)
        Add(rson, L, R, op);
}
deque<int> q;
void BFS_01()
{
    memset(dis, 0x3f, sizeof(dis));
    dis[num[p]] = 0;
    q.push_back(num[p]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        for (pii x : e[u])
        {
            int v = x.first;
            if (dis[v] > dis[u] + x.second)
            {
                dis[v] = dis[u] + x.second;
                if (x.second == 1)
                    q.push_back(v);
                else
                    q.push_front(v);
            }
        }
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &p);
    bld(rt);
    while (m--)
    {
        tot++;
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        Add(rt, a, b, 0);
        Add(rt, c, d, 1);
        tot++;
        Add(rt, a, b, 1);
        Add(rt, c, d, 0);
    }
    BFS_01();
    for (int i = 1; i <= n; i++)
    {
        if (i == p)
            printf("0\n");
        else
            printf("%d\n", dis[num[i] + 4 * n]);
    }
    return 0;
}

```

---

## 作者：Piwry (赞：6)

这里讲下强制空间限制 $O(n+m)$ 的做法

当然直接线段树建图更可做；但可惜这样的空间复杂度是 $O(m\log n)$ 的（更 naive 一些的建图甚至是 $O(m\log^2 n)$ 的 \fad）

## 解析

（下面将形如输入给出的 $(a, b, c, d)$ 的四元组称为 “一条边”；虽然它可能描述了多个结点间的连通关系X）

由于边权没有负数；考虑最短路算法的性质，一条边显然**只会被使用一次**（第一次用到这条边即是最短路）

于是我们可以考虑用完一条边就删去它。这样复杂度就和每条边的区间大小无关了

设当前点的编号为 $x$。若将每条边视为（两个）区间，此时我们需要做的就是找到**所有覆盖 $x$ 的区间**

我们可以用线段树维护。具体来说，若有一个区间 $[l, r]$，我们将其存在下标为 $l$ 的位置上（同时也一并保存边的编号什么），并取其中 $r$ 最大的区间作为该下标的 “权”（具体实现时可以排个序，然后从后往前作为该下标的 “权”）；线段树上则具体维护区间内最大的 “权” 及其信息（即来自于哪个位置什么）。每次询问时，就寻找 $[1, x]$ 中（显然只有左端点在 $[1, x]$ 内的区间才能覆盖 $x$）最大的 “权”，用掉其对应的边，然后再找；直到找到的边的 $r$ 不大于 $x$ 时结束（这时候 $x$ 无法使用这条边）

“使用” 每条边的具体实现可以暴力枚举区间中的元素，但同时用并查集将访问过的元素（已发现最短路的元素）缩起来以保障复杂度

另外由于本题的边没有边权，因此没必要写 Dijkstra 之类；用 Bfs 就行了

描述不太清楚的地方可参考代码qaq

## CODE

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using std::pair;
using std::vector;
using std::sort;
typedef pair<int, int> pad;

const int MAXN =5e5+20, MAXM =1e5+20, MAXSeg =1<<20;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return x;
}

void write(const int &x){
	if(x/10)
		write(x/10);
	putchar('0'+x%10);
}

/*------------------------------Seg------------------------------*/

struct node{
	int l, r, id;
	
	node(){}
	node(const int &L, const int &R, const int &ID):l(L), r(R), id(ID){}
	
	node operator + (const node &B) const{
		node ret(l, r, id);
		if(B.r > ret.r)
			ret =B;
		return ret;
	}
	bool operator < (const node &B) const{
		return r < B.r;
	}
}data[MAXSeg];/*以 [nl, nr] 为左端点的边中 r 最大的边*/

vector<node> v[MAXN];

int N =1;

inline void pushup(const int &x){
	data[x] =data[x<<1]+data[x<<1^1];
}

void Build(const int &n){
	while(N < n)
		N <<=1;
	for(int i =N; i < N+n; ++i)
		data[i] =v[i-N+1].back();
	for(int i =N-1; i >= 1; --i)
		pushup(i);
}

/*以 [l, r] 为左端点的边中 r 最大的边*/
node query(const int &l, const int &r, const int &nl =1, const int &nr =N, const int &x =1){
	if(l == nl && r == nr)
		return data[x];
	int mid =nl+nr>>1;
	if(r <= mid)
		return query(l, r, nl, mid, x<<1);
	else if(l >= mid+1)
		return query(l, r, mid+1, nr, x<<1^1);
	else
		return query(l, mid, nl, mid, x<<1)+query(mid+1, r, mid+1, nr, x<<1^1);
}

void del_edge(const int &pos, const int &nl =1, const int &nr =N, const int &x =1){
	if(nl == nr){
		v[pos].pop_back();
		data[x] =v[pos].back();
		return;
	}
	int mid =nl+nr>>1;
	if(pos <= mid)
		del_edge(pos, nl, mid, x<<1);
	else
		del_edge(pos, mid+1, nr, x<<1^1);
	pushup(x);
}

/*------------------------------Disjoint Set------------------------------*/

int fa[MAXN];

void Build_ds(const int &n){
	for(int i =1; i <= n+1; ++i)
		fa[i] =i;
}

int find(const int &x){
	return (fa[x] == x) ? x : fa[x] =find(fa[x]);
}

/*删除编号序列上该处的点*/
void del_pos(const int &pos){
	int x =find(pos)+1;
	fa[pos] =x;
}

/*------------------------------01Bfs------------------------------*/

struct query{
	int l1, r1, l2, r2;
}q[MAXM];

pad que[MAXN];
int head, tail;

int dist[MAXN];

#define fi first
#define se second

void Bfs(const int &s){
	que[tail++] =pad(s, 0);
	del_pos(s);
	while(head < tail){
		pad nw =que[head++];
		dist[nw.fi] =nw.se;
		while(1){
			node tmp =query(1, nw.fi);
			if(tmp.r < nw.fi)
				break;
			else if(tmp.l == q[tmp.id].l1){
				for(int to =find(q[tmp.id].l2); to <= q[tmp.id].r2; del_pos(to), to =find(to+1))
					que[tail++] =pad(to, nw.se+1);
			}
			else{
				for(int to =find(q[tmp.id].l1); to <= q[tmp.id].r1; del_pos(to), to =find(to+1))
					que[tail++] =pad(to, nw.se+1);
			}
			del_edge(tmp.l);
		}
	}
}

#undef fi
#undef se

/*------------------------------Main------------------------------*/

int main(){
	int n =read(), m =read(), s =read();
	for(int i =1; i <= m; ++i){
		int a =read(), b =read(), c =read(), d =read();
		q[i].l1 =a, q[i].r1 =b, q[i].l2 =c, q[i].r2 =d;
		v[q[i].l1].push_back(node(q[i].l1, q[i].r1, i));
		v[q[i].l2].push_back(node(q[i].l2, q[i].r2, i));
	}
	for(int i =1; i <= n; ++i)
		v[i].push_back(node(0, 0, 0)), sort(v[i].begin(), v[i].end());
	Build_ds(n), Build(n);
	Bfs(s);
	for(int i =1; i <= n; ++i)
		write(dist[i]), putchar('\n');
}
```

---

## 作者：conprour (赞：2)

# 题解
顺着线段树优化建图的板子来的。

原本想的建图方式是找到每个区间对应的入树和出树节点分别连起来，但这样单次连边复杂度是 $O(\log^2n)$，MLE+TLE 。

题解的虚点做法直接降一个 $\log n$ 已经很详细，但我实现的时候遇到一点小问题，写出来告诫一下和我有同样想法的人。

## 关于连边方向

出树/入树向虚点连边怎么连？

显然出树连向虚点，虚点连向入树这种连边方式是对的。

**如果有人连双向边请往下看：**

但是我为了图省事建了双向边，因为我觉得从入树走回出树的边不会对答案有影响，但是 WA 了。

再经过思考才发现单独一条双向边没事，但如果两条双向边连在一起，那么对应的节点就会通过双向边在树上乱走了。因此不能建双向边。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define FCC fclose(stdin),fclose(stdout)
#define mid ((l+r)>>1)
#define MP make_pair
#define pr pair<ll,int>
const int INF = 0x3f3f3f3f,N = 5e5+10;
inline ll read()
{
	ll ret=0;char ch=' ',c=getchar();
	while(!(c>='0'&&c<='9')) ch=c,c=getchar();
	while(c>='0'&&c<='9') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
	return ch=='-'?-ret:ret;
}
int n,m,s;
int head[N<<5],ecnt=-1;
inline void init_edge(){memset(head,-1,sizeof(head)),ecnt=-1;}
struct edge
{
	int nxt,to,w;
}a[N<<5];
inline void add_edge(int x,int y,int w)
{
	a[++ecnt]=(edge){head[x],y,w};
	head[x]=ecnt;
}
int ls[N<<5],rs[N<<5];
int rtin,rtout,tot;
void buildin(int &k,int l,int r)
{
	k=++tot;
	if(l==r) return add_edge(k,l,0);
	buildin(ls[k],l,mid);
	buildin(rs[k],mid+1,r);
	add_edge(k,ls[k],0);
	add_edge(k,rs[k],0);
}
void addin(int k,int l,int r,int x,int y,int v)
{
	if(x<=l&&r<=y) return add_edge(v,k,1);
	if(x<=mid) addin(ls[k],l,mid,x,y,v);
	if(y>mid) addin(rs[k],mid+1,r,x,y,v);
}
void buildout(int &k,int l,int r)
{
	k=++tot;
	if(l==r) return add_edge(l,k,0);
	buildout(ls[k],l,mid);
	buildout(rs[k],mid+1,r);
	add_edge(ls[k],k,0);
	add_edge(rs[k],k,0);
}
void addout(int k,int l,int r,int x,int y,int v)
{
	if(x<=l&&r<=y) return add_edge(k,v,1);
	if(x<=mid) addout(ls[k],l,mid,x,y,v);
	if(y>mid) addout(rs[k],mid+1,r,x,y,v);
}
void find(int k,int l,int r,int x,int y,int w,bool op)
{
	if(x<=l&&r<=y) 
	{
		if(!op) add_edge(k,tot,w);
		else add_edge(tot,k,w);
		return;
	} 
	if(x<=mid) find(ls[k],l,mid,x,y,w,op);
	if(y>mid)  find(rs[k],mid+1,r,x,y,w,op);
}
ll dis[N<<5];
bool vis[N<<5];
void dijk()
{
	priority_queue<pr,vector<pr>,greater<pr> >q;
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(MP(0ll,s));
	dis[s]=0ll;
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];~i;i=a[i].nxt)
		{
			int v=a[i].to;
		//	printf("v=%d\n",v);
			if(dis[v]>dis[u]+a[i].w)
			{
				dis[v]=dis[u]+a[i].w;
				q.push(MP(dis[v],v));
			}
		}
	}
}
int main()
{
	tot=n=read(),m=read(),s=read();
	init_edge();
	buildin(rtin,1,n);
	buildout(rtout,1,n);
	for(int i=1;i<=m;i++)
	{
		int l1=read(),r1=read(),l2=read(),r2=read();
		tot++;//建立虚点 
		find(rtout,1,n,l1,r1,0,false);
		find(rtin,1,n,l2,r2,1,true);
		tot++;
		find(rtout,1,n,l2,r2,0,false);
		find(rtin,1,n,l1,r1,1,true);
	}
	dijk();
	for(int i=1;i<=n;i++) printf("%lld\n",dis[i]);
	return 0;
}

```


---

## 作者：AIskeleton (赞：2)

[博客园查看](https://www.cnblogs.com/AIskeleton/p/16306369.html)

> [P6348 [PA2011]Journeys](https://www.luogu.com.cn/problem/P6348)

> 有 $n$ 个点，$m$ 次连边，每次在两区间 $[a,b],[c,d]$ 的每两个点之间连一条无向边。
> 求问点 $p$ 到达其余的每个点所需经过的最少路径数。

> $1\le n\le 5\times 10^5,1\le m\le 10^5$。

线段树优化建图，**区间之间连边**的模板题。

很明显直接暴力连边的时间和空间复杂度都是 $O(m\,n^2)$，所以要用到**线段树优化建图**来优化建边的复杂度。

我们可以利用“对于每一个区间，都可以将其转化为线段树上至多 $\log_2n$ 个区间”这一性质，来减少连边的数量。

先建出线段树，连边时改为向线段树上的表示相应的区间的节点连边。

线段树上的父子节点之间连边权为 0 的有向边，根据题目连边要求确定方向，此题要建两棵线段树。

- 如果是点向区间连边，就将点连向**树中父节点向子节点连边**的线段树中节点。
- 如果是区间向点连边，就从**树中子节点向父节点连边**的线段树上的相应节点向要求的节点连边。

![](https://cdn.luogu.com.cn/upload/image_hosting/o87spdle.png)

比如图中的例子就是**点 u 向区间 $[3,7]$ 之间的点连边**时的情况。

建出两棵线段树，其中一棵的每个父节点向其子节点连**边权为 0 的单向边**，另一棵则与之相反。

对于每次区间连边操作，在两棵线段树上找出对应节点并暴力连边，空间复杂度为 $O(n \log_2^2n)$，仍需优化。

考虑每次建边时引入一个虚点，在虚点和两棵线段树之间**分别连两条方向相反的权值为 1 的有向边**，空间复杂度降到 $O(n\log_2n)$，可以通过。

不直接直接只连一条无向边的原因是，如果两条连接虚点和线段树上节点的无向边**经过了同一个点**，则会让这个线段树上的节点可以通过**线段树上的路径**到达每一个节点。

建完边后以 $p$ 为起点跑一遍 01BFS 即可。
最后距离应除二，因为一条边被拆成了连向虚点从虚点连向目标点两个部分，边权算了两次。

```cpp
#include <bits/stdc++.h>
#define MID int m=(l+r)>>1;
using namespace std;
const int N = 8e6;
int rd() {
    int w = 0, v = 1;
    char c = getchar();

    while (c < '0' || c > '9') {
        if (c == '-')
            v = -1;

        c = getchar();
    }

    while (c >= '0' && c <= '9')
        w = (w << 1) + (w << 3) + (c & 15), c = getchar();

    return w * v;
}
void wr(int x) {
    if (x < 0)
        putchar('-'), x = -x;

    if (x > 9)
        wr(x / 10);

    putchar(x % 10 + '0');
}
int fir[N], c, cnt, ls[N], rs[N], n, m, p, r1, r2, xd, vis[N], d[N];
deque <int>q;
struct E {
    int v, nt, w;
} e[N];
void I(int u, int v, int w = 0) {
    e[++cnt] = (E) {
        v, fir[u], w
    };
    fir[u] = cnt;
}
void b1(int &p, int l, int r) {
    if (l == r) {
        p = l;
        return;
    }
    p = ++c;
    MID b1(ls[p], l, m);
    b1(rs[p], m + 1, r);
    I(p, ls[p]);
    I(p, rs[p]);
}
void b2(int &p, int l, int r) {
    if (l == r) {
        p = l;
        return;
    }
    p = ++c;
    MID b2(ls[p], l, m);
    b2(rs[p], m + 1, r);
    I(ls[p], p);
    I(rs[p], p);
}
void ch(int p, int l, int r, int L, int R, bool f) {
    if (l >= L && r <= R) {
        if (f) I(p, xd, 1);
        else I(xd, p, 1);
        return ;
    }MID 
    if (L <= m)
        ch(ls[p], l, m, L, R, f);
    if (R > m)
        ch(rs[p], m + 1, r, L, R, f);
    return ;
}
void dj(int p) {
    memset(d, 0x7f, sizeof(d));d[p] = 0;q.push_front(p);
    while (!q.empty()) {
        int u = q.front(), v, w;q.pop_front();
        for (int i = fir[u]; i; i = e[i].nt) {
            v = e[i].v;w = e[i].w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                if (w == 1)
                    q.push_back(v);
                else
                    q.push_front(v);
            }
        }
    }
}
signed main() {
    n = rd();m = rd();p = rd();
    c = n;b1(r1, 1, n);b2(r2, 1, n);
    xd = c + 1;
    for (int i = 1, a, b, c, d; i <= m; i++) {
        a = rd();b = rd();c = rd();d = rd();
        ch(r2, 1, n, a, b, 1);
        ch(r1, 1, n, c, d, 0);
        xd++;
        ch(r2, 1, n, c, d, 1);
        ch(r1, 1, n, a, b, 0);
        xd++;
    }dj(p);
    for (int i = 1; i <= n; i++)
        wr(d[i] / 2), putchar('\n');
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

显然线段树优化建图，但是直接任意两个点连边空间复杂度将达到难看的 $O(n \log ^ 2 n)$ 所以我们来个小改动。              

考虑在每次连边的时候建立个虚点，然后左边的树上覆盖节点向这个虚点连值为 $0$ 的边，这个点向右边树上的覆盖节点连值为 $1$ 的边空间复杂度就是可以接受的 $O((n + q) \log n)$。              

当然也有一种高论的空间 $O(n + q)$ 做法我也不会，有兴趣的同学翻一翻洛谷这道题的题解就可以翻到。               

实现最短路时用 01BFS 可以省一只 $\log$，这里用 Dijkstra 就可以过了。 

01BFS：$O((n + m) \log n) - O((n + q) \log n)$

Dijkstra：$O((n + (n + q) \log n) \log n) - O((n + q) \log n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 5e5 + 5 , Inf = 1e9;
int n,m,P,dis[Len << 4],head[Len << 4],cnt,tot,Indx[Len << 4][2],Pos[Len];
bool flag[Len << 4];
struct node
{
	int next,to,w;
}edge[Len * 105];
void add(int from,int to,int w)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	edge[cnt].w = w;
	head[from] = cnt;
}
#define ls(p) p << 1
#define rs(p) p << 1 | 1
void build(int p,int l,int r)
{	
	Indx[p][0] = ++ tot;
	Indx[p][1] = ++ tot;
	add(Indx[p][1] , Indx[p][0] , 0);
	if(l == r) 
	{
		Pos[l] = Indx[p][0];
		//printf("### %d %d\n",l,Pos[l]);
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	add(Indx[ls(p)][0] , Indx[p][0] , 0) , add(Indx[rs(p)][0] , Indx[p][0] , 0);
	add(Indx[p][1] , Indx[ls(p)][1] , 0) , add(Indx[p][1] , Indx[rs(p)][1] , 0);
}
vector<int> Left[2];
vector<int> Right[2];
void update_L(int p,int l,int r,int nl,int nr,int opt)
{
	if(nl <= l && nr >= r) 
	{
		Left[opt].push_back(Indx[p][0]);
		return;
	}
	int mid = (l + r) >> 1;
	if(nl <= mid) update_L(ls(p) , l , mid , nl , nr , opt);
	if(nr > mid) update_L(rs(p) , mid + 1 , r , nl , nr , opt);
}
void update_R(int p,int l,int r,int nl,int nr,int opt)
{
	if(nl <= l && nr >= r)
	{
		Right[opt].push_back(Indx[p][1]);
		return;
	}
	int mid = (l + r) >> 1;
	if(nl <= mid) update_R(ls(p) , l , mid , nl , nr , opt);
	if(nr > mid) update_R(rs(p) , mid + 1 , r , nl , nr , opt);
}
void ADD()
{
	++ tot;
	for(int i = 0 ; i < Left[0].size() ; i ++) add(Left[0][i] , tot , 0);
	for(int i = 0 ; i < Right[0].size() ; i ++) add(tot , Right[0][i] , 1);
	++ tot;
	for(int i = 0 ; i < Left[1].size() ; i ++) add(Left[1][i] , tot , 0);
	for(int i = 0 ; i < Right[1].size() ; i ++) add(tot , Right[1][i] , 1);
}
struct Node
{
	int x,val;
	Node(){x = val = 0;}
	Node(int X,int VAL){x = X , val = VAL;}
	bool operator < (const Node &Ano) const
	{
		return val > Ano.val;
	}
}PS;
void BFS(int s)
{
	priority_queue<Node> Q;
	for(int i = 1 ; i <= tot ; i ++) dis[i] = Inf , flag[i] = 0;
	Q.push(Node(s , 0));dis[s] = 0;
	while(!Q.empty())
	{
		PS = Q.top();Q.pop();
		if(!flag[PS.x])
		{
			flag[PS.x] |= 1;
			for(int e = head[PS.x] ; e ; e = edge[e].next)
			{
				int to = edge[e].to;
				if(dis[to] > dis[PS.x] + edge[e].w)
				{
					dis[to] = dis[PS.x] + edge[e].w;
					if(!flag[to]) Q.push(Node(to , dis[to]));
				}
			}
		}
	}
}
int main()
{
	scanf("%d %d %d",&n,&m,&P);
	build(1 , 1 , n);
	for(int i = 1 ; i <= m ; i ++)
	{
		int a,b,c,d;scanf("%d %d %d %d",&a,&b,&c,&d);
		Left[0].clear() , Right[0].clear() , Left[1].clear() , Right[1].clear();
 		update_L(1 , 1 , n , a , b , 0);
 		update_R(1 , 1 , n , c , d , 0);
 		update_L(1 , 1 , n , c , d , 1);
 		update_R(1 , 1 , n , a , b , 1);
 		ADD();
	}
	BFS(Pos[P]);
	for(int i = 1 ; i <= n ; i ++) printf("%d\n",dis[Pos[i]]);
	return 0;	
} 
```

---

