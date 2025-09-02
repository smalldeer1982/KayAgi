# [NEERC 2017] Laminar Family

## 题目描述

在研究组合优化时，Lucas 遇到了“层状集合族”的概念。对于某个集合 $\Omega$ 的子集族 $F$，如果它不包含空集，并且对于任何两个不同的集合 $A, B \in F$，要么 $A \subset B$，要么 $B \subset A$，要么 $A \cap B = \emptyset$，则称其为层状集合族。

作为一名经验丰富的题目设计者，Lucas 总是尝试将他获得的每一项新知识应用于编程竞赛题目。他的科学兴趣领域包括识别问题，这些问题通常听起来像是“给定某种奇怪的组合性质，检查给定结构是否满足它”。

Lucas 认为完美的编程竞赛题目应该包含一个仙人掌树。在尝试将层状集合和树结合成一个识别问题时，他最终提出了以下问题：给定一个有 $n$ 个顶点的无向树和一个集合族 $F = \{F_{1}, \ldots, F_{k}\}$，其中 $F_{i}$ 包含树中某两个顶点 $a_{i}$ 和 $b_{i}$ 之间简单路径上的所有顶点，检查集合族 $F$ 是否为层状集合族。注意，在这种情况下 $\Omega = V$，并且每个 $F_{i} \subseteq V$。

如你所见，Lucas 成功地将这个问题建议给了编程竞赛。现在轮到你来解决它了。

## 说明/提示

时间限制：2 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 2
1 2
2 3
2 4
1 2
4 2
```

### 输出

```
No
```

## 样例 #2

### 输入

```
6 5
1 2
2 3
3 4
5 6
5 2
2 1
6 6
1 4
3 4
4 1
```

### 输出

```
Yes
```

# 题解

## 作者：CYJian (赞：16)

## 题目大意

给定一棵 $n$ 个节点的树，给出 $m$ 条路径，试判断下面的命题是否成立：

$m$ 条路径中，任意两条路径的点集的交集为空，或者一个是另一个的子集。

$1 \leq n,m \leq 10^5$

## 吐槽

这个作业题怎么又是一个数据范围、时间复杂度和时限凑一起越看越离谱的题啊

先有一个 $10^6$ 的小常数线性复杂度题开 `10s`，这又整一个 $O(n \alpha(n))$ 的并查集题只开 $10^5$ 还开 `3s` 的...

## 题目解法

不难发现，包含关系只可能是短的路径被长的路径包含。

那么我们考虑按照路径长度从小到大一条一条路径边加入边判断。

考虑先将树上的所有边断开，每加入一条路径的时候就将这条路径上包含的边加入，用并查集维护连通块的点数。不难发现，如果加入一条路径后，这条路径所在连通块的点数与当前加入的这条路径上的点数不同时，就必然存在一条路径，与当前加入的这条路径不满足题目所给命题，此时可以判定不成立了。如果加入后点数相符合，那么当前就没有问题。

如果将所有路径都加入了还没出现问题，那么这个命题就可以确定为正确的了。

`Code`：

```cpp
const int MAXN = 100010;

int tot;
int fi[MAXN];
int ne[MAXN << 1];
int to[MAXN << 1];

inline void Link(int u, int v) {
	tot++;
	to[tot] = v;
	ne[tot] = fi[u];
	fi[u] = tot;
}

int fa[MAXN];
int dep[MAXN];
int up[MAXN][20];

inline void dfs(int x, int la) {
	dep[x] = dep[la] + 1, up[x][0] = fa[x] = la;
	for(int i = 1; i < 20; i++)
		up[x][i] = up[up[x][i - 1]][i - 1];
	for(int i = fi[x]; i; i = ne[i]) {
		int u = to[i];
		if(u == la) continue;
		dfs(u, x);
	}
}

inline int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	int k = dep[x] - dep[y];
	for(int i = 0; i < 20; i++)
		if(k & (1 << i)) x = up[x][i];
	if(x == y) return x;
	for(int i = 19; ~i; --i)
		if(up[x][i] != up[y][i])
			x = up[x][i], y = up[y][i];
	return up[x][0];
}

struct Path {
	int u, v, lca, len, id;

	inline void init(int i) {
		id = i, u = ri, v = ri, lca = LCA(u, v);
		len = dep[u] + dep[v] - dep[lca] * 2;
	}

	friend bool operator < (Path a, Path b) { return a.len < b.len; }
}a[MAXN];

struct UFS {
	int fa[MAXN];
	int sz[MAXN];

	inline void init(int n) { for(int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1; }
	inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
	inline void Merge(int u, int v) {
		u = find(u), v = find(v);
		if(u == v) return ;
		fa[u] = v, sz[v] += sz[u];
	}
}ufs;

inline void Solve(Path x) {
	int u, d = dep[x.lca];
	u = ufs.find(x.u); while(dep[u] > d) ufs.Merge(u, fa[u]), u = ufs.find(u);
	u = ufs.find(x.v); while(dep[u] > d) ufs.Merge(u, fa[u]), u = ufs.find(u);
	if(x.len != ufs.sz[ufs.find(x.lca)] - 1) puts("No"), exit(0);
}

int main() {
	int n = ri, m = ri;
	for(int i = 1; i < n; i++) {
		int u = ri, v = ri;
		Link(u, v), Link(v, u);
	} dfs(1, 0);
	for(int i = 1; i <= m; i++) a[i].init(i);
	sort(a + 1, a + 1 + m), ufs.init(n);
	for(int i = 1; i <= m; i++) Solve(a[i]);
	puts("Yes");
	return 0;
}
```

---

## 作者：Cupids_Bow (赞：2)

## 思路：树链剖分 + 哈希

### 题意

给定一棵树与若干条链，判断是否所有的链满足两个条件之一：
1. 与其他链交集为空，
2. 完全包含或被包含在其他链中

### 思路

提供一种不一样的思路，对于所有的链按长度从大到小考虑，因为长度小的链只能被包含或者与其他链相离。考虑按长度从大到小将链加入到树上，加入时查询该链所覆盖区间内是否存在相同种类及数量的其他链。这个地方考虑为每一条链随机一个大哈希值，加入链时相当于给链覆盖的每一个点异或上改链的哈希值，查询时查询区间内所有点的哈希值是否都相等，若存在不相等则说明该区间内存在不同种类或数量的其他链，则不满足条件。

关于哈希解法的正确性证明可以参考：[https://codeforces.com/blog/entry/85900](https://codeforces.com/blog/entry/85900)

### 代码如下

```cpp
#include<bits/stdc++.h>
#define size size_
using namespace std;

using ull=unsigned long long;

const int N=(int)1e5+5;
int CNT=-1;

ull Ra(){
    return (ull)rand()*(ull)rand()*(ull)rand()*(ull)rand()*(ull)rand()*(ull)rand();
}

int n,m;
int u[N*2],v[N*2],nex[N*2],first[N];
int size[N],son[N],fa[N],dep[N];
int top[N],tot,id[N],pos[N],last[N];
struct seg{
    int x;
    int y;
    int len;
    ull h;
}a[N];
struct tree{
    int l;
    int r;
    ull sum;
    int equal;
    ull lz;
}t[N<<2];

void add(int x,int y){
    CNT++;
    u[CNT]=x;
    v[CNT]=y;
    nex[CNT]=first[u[CNT]];
    first[u[CNT]]=CNT;
}

void build(int i,int l,int r){
    t[i].l=l;
    t[i].r=r;
    t[i].lz=0;
    t[i].equal=1;
    if(l==r){
        t[i].sum=1;
        return;
    }
    int mid=l+r>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    t[i].sum=t[i<<1].sum+t[i<<1|1].sum;
    return;
}

void build1(int i,int l,int r){
    t[i].l=l;
    t[i].r=r;
    t[i].lz=0;
    t[i].equal=1;
    if(l==r){
        t[i].sum=1;
        return;
    }
    int mid=l+r>>1;
    build1(i<<1,l,mid);
    build1(i<<1|1,mid+1,r);
    t[i].sum=1;
    return;
}

void pushdown(int i){
    if(t[i].lz){
        ull k=t[i].lz;
        if(t[i<<1].equal) t[i<<1].sum^=k;
        if(t[i<<1|1].equal) t[i<<1|1].sum^=k;
        t[i<<1].lz^=k;
        t[i<<1|1].lz^=k;
        t[i].lz=0;
    }
    return;
}

void add(int i,int l,int r,ull k){
    if(t[i].l>=l&&t[i].r<=r){
        if(t[i].equal) t[i].sum^=k;
        t[i].lz^=k;
        return;
    }
    pushdown(i);
    if(t[i<<1].r>=l) add(i<<1,l,r,k);
    if(t[i<<1|1].l<=r) add(i<<1|1,l,r,k);
    if(t[i<<1].equal&&t[i<<1|1].equal&&t[i<<1].sum==t[i<<1|1].sum){
        t[i].equal=1;
        t[i].sum=t[i<<1].sum;
    }
    else t[i].equal=false;
    return;
}

pair<int,ull> search(int i,int l,int r){
    if(t[i].l>=l&&t[i].r<=r) return {t[i].equal,t[i].sum};
    pushdown(i);
    if(t[i<<1].r>=l&&t[i<<1|1].l<=r){
        pair<int,ull> node1=search(i<<1,l,r);
        pair<int,ull> node2=search(i<<1|1,l,r);
        if(node1.first&&node2.first) return {node1.second==node2.second,node1.second};
        else return {0,0};
    }
    else if(t[i<<1].r>=l) return search(i<<1,l,r);
    else return search(i<<1|1,l,r);
}

ull searchdis(int i,int l,int r){
    if(t[i].l>=l&&t[i].r<=r) return t[i].sum;
    pushdown(i);
    int sum=0;
    if(t[i<<1].r>=l) sum+=searchdis(i<<1,l,r);
    if(t[i<<1|1].l<=r) sum+=searchdis(i<<1|1,l,r);
    return sum;
}

void getson(int t,int f){
    size[t]++;
    fa[t]=f;
    int k=first[t];
    while(k!=-1){
        if(v[k]!=f){
            dep[v[k]]=dep[t]+1;
            getson(v[k],t);
            size[t]+=size[v[k]];
            if(size[v[k]]>size[son[t]]) son[t]=v[k];
        }
        k=nex[k];
    }
}

void dfs(int t,int f,int tp){
    top[t]=tp;
    id[t]=++tot;
    pos[tot]=t;
    if(son[t]) dfs(son[t],t,tp);
    int k=first[t];
    while(k!=-1){
        if(v[k]!=son[t]&&v[k]!=f) dfs(v[k],t,v[k]);
        k=nex[k];
    }
    last[t]=tot;
}

void addxy(int x,int y,ull k){
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]) swap(x,y);
        add(1,id[top[y]],id[y],k);
        y=fa[top[y]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    add(1,id[x],id[y],k);
}

int equal(int x,int y){
    pair<int,ull> sum={-1,0};
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]) swap(x,y);
        pair<int,ull> node=search(1,id[top[y]],id[y]);
        if(sum.first==-1) sum=node;
        else{
            if(sum.first&&node.first) sum={sum.second==node.second,sum.second};
            else sum={0,0};
        }
        y=fa[top[y]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    pair<int,ull> node=search(1,id[x],id[y]);
    if(sum.first==-1) sum=node;
    else{
        if(sum.first&&node.first) sum={sum.second==node.second,sum.second};
        else sum={0,0};
    }
    return sum.first;
}

ull dis(int x,int y){
    ull sum=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]>dep[top[y]]) swap(x,y);
        sum+=searchdis(1,id[top[y]],id[y]);
        y=fa[top[y]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    sum+=searchdis(1,id[x],id[y]);
    return sum;
}

int main(){
    srand(time(0));
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    for(int i=1,x,y;i<n;i++){
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].h=Ra();//产生哈希值
    }
    getson(1,0);//树剖
    dfs(1,0,1);//树剖
    build(1,1,n);//树剖
    for(int i=1;i<=m;i++) a[i].len=(int)dis(a[i].x,a[i].y);//查询距离
    sort(a+1,a+1+m,[](const seg& a,const seg& b){
        return a.len>b.len;
    });//按长度排序
    build1(1,1,n);
    for(int i=1;i<=m;i++){
        if(!equal(a[i].x,a[i].y)) return printf("No"),0;//查询区间内哈希值是否相等
        addxy(a[i].x,a[i].y,a[i].h);//加入链
    }
    printf("Yes");
    return 0;
}
```


---

## 作者：Tenshi (赞：2)

排序 + 线段树 + 树剖

不得不说这道题涉及到的操作还是挺多的，我调了一个多小时呜呜。

## 分析

首先我们按照将题目所给的路径存入 `q[]` 中并按照**长度**从大到小排序，然后从左到右扫一遍 `q[]`，对于当前的路径，我们只需要看看它是否被其他路径包含即可。

具体来说我们可以对路径进行染色，然后看看当前路径是否具有同一种颜色，这个操作可以使用线段树 + 树剖来解决。

```cpp
// #pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define debug(x) cerr << #x << ": " << x << endl

#define set0(a) memset(a,0,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)

using pii = pair<int, int>;

#define x first
#define y second

inline void read(int &x) {
    int s=0;x=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=1e5+5, M=N<<1;

int n, m;

struct Edge{
	int to, next;
}e[M];

int h[N], tot;

void add(int u, int v){
	e[tot].to=v, e[tot].next=h[u], h[u]=tot++;
}

int son[N], fa[N], dep[N], sz[N];
int top[N], id[N], idx;

void dfs(int u, int father, int depth){
	fa[u]=father, dep[u]=depth, sz[u]=1;
	for(int i=h[u]; ~i; i=e[i].next){
		int go=e[i].to;
		if(go==father) continue;
		dfs(go, u, depth+1);
		sz[u]+=sz[go];
		if(sz[go]>sz[son[u]]) son[u]=go;
	}	
}

void dfs2(int u, int t){
	id[u]=++idx, top[u]=t;
	if(!son[u]) return;
	dfs2(son[u], t);
	for(int i=h[u]; ~i; i=e[i].next){
		int go=e[i].to;
		if(go==fa[u] || go==son[u]) continue;
		dfs2(go, go);
	}
}

int lca(int u, int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u, v);
		u=fa[top[u]];
	}
	return dep[u]>dep[v]? v: u;
}

int dis(int u, int v){
	return dep[u]+dep[v]-2*dep[lca(u, v)];
}

struct Msg{
	int l, r;
	bool operator < (const Msg &o)const{
		return dis(l, r)>dis(o.l, o.r);
	}
}q[N];

// ======================== segment tree op ==========================

struct Node{
	int l, r;
	int v, same;
	int tag;
	
	#define ls u<<1
	#define rs u<<1|1
}tr[N<<2];

void pushup(int u){
	if(!tr[ls].l) tr[u].same=tr[rs].same;
	else if(!tr[rs].l) tr[u].same=tr[ls].same;
	else{
		if(tr[ls].same && tr[rs].same && tr[ls].v==tr[rs].v) tr[u].same=1;
		else tr[u].same=0;
	}
	tr[u].v=max(tr[ls].v, tr[rs].v);
}

void pushdown(int u){
	if(tr[u].tag){
		auto &L=tr[ls], &R=tr[rs];
		L.same=1, L.v=tr[u].tag, L.tag=tr[u].tag;
		R.same=1, R.v=tr[u].tag, R.tag=tr[u].tag;
		tr[u].tag=0;
	}
}

void build(int u, int l, int r){
	tr[u]={l, r, 0, 1, 0};
	if(l==r) return;
	int mid=l+r>>1;
	build(ls, l, mid), build(rs, mid+1, r);
}

void upd(int u, int l, int r, int k){
	if(l<=tr[u].l && tr[u].r<=r){
		tr[u].tag=k;
		tr[u].v=k, tr[u].same=1;
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	pushdown(u);
	if(l<=mid) upd(ls, l, r, k);
	if(mid<r) upd(rs, l, r, k);
	pushup(u);
}

pii query(int u, int l, int r){
	if(l<=tr[u].l && tr[u].r<=r) return {tr[u].same, tr[u].v};
	int mid=tr[u].l+tr[u].r>>1;
	int same=1, v=-1;
	pii L={-1, -1}, R={-1, -1};
	pushdown(u);
	if(l<=mid){
		L=query(ls, l, r);
		same&=L.x;
		v=max(v, L.y);
	}
	if(mid<r){
		R=query(rs, l, r);
		same&=R.x;
		v=max(v, R.y);
	}
	if(~L.y && ~R.y && L.y!=R.y) same=0;
	return {same, v};
}

// ========================= end of seg tree =============================

bool qsame(int u, int v){
	set<int> st;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u, v);
		auto t=query(1, id[top[u]], id[u]);
		if(!t.x) return false;
		st.insert(t.y);
		u=fa[top[u]]; 
	}
	if(dep[u]<dep[v]) swap(u, v);
	auto t=query(1, id[v], id[u]);
	if(!t.x) return false;
	st.insert(t.y);
	
	return st.size()==1;
}

void assign(int u, int v, int col){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u, v);
		upd(1, id[top[u]], id[u], col);
		u=fa[top[u]]; 
	}
	if(dep[u]<dep[v]) swap(u, v);
	upd(1, id[v], id[u], col);
}

int main(){
	memset(h, -1, sizeof h);
	read(n), read(m);
	rep(i,1,n-1){
		int u, v; read(u), read(v);
		add(u, v), add(v, u); // 建树
	}
	
	dfs(1, -1, 1), dfs2(1, 1); // 树剖
	build(1, 1, n); // 建线段树
	
	rep(i,1,m){
		int u, v; read(u), read(v);
		q[i]={u, v}; // 记录所有路径
	}
	
	sort(q+1, q+1+m); // 按照路径长度从大到小排序

	bool ok=true;
	
	rep(i,1,m){
		int u=q[i].l, v=q[i].r;
		if(!qsame(u, v)){ // 如果当前路径不是同色的，ok = false
			ok=false;
			break;
		}
		assign(u, v, i); // 对路径进行染色修改
	}

	puts(ok? "Yes": "No");
	
	return 0;
}
```

---

## 作者：ix35 (赞：2)

CYJ 的做法非常 nb，我这里给一个比较无脑的头铁做法。

考虑两条路径 $S_1,S_2$，设它们的 LCA 分别为 $L_1,L_2$。

首先有个显然的命题：两条路径点相交，当且仅当其中一个的 LCA 在另一条路径上。

接下来对 $L_1,L_2$ 分类：

---

$L_1\ne L_2$：

那么我们对每条路径 $i$ 分别统计 $f(i)$ 表示 LCA 在 $S_i$ 上且不为 $L_i$ 的路径数量，以及 $g(i)$ 表示 LCA 不为 $L_i$ 且被 $S_i$ 包含的路径数量，只要 $f(i)\ne g(i)$，答案就是 `No`。

$f(i)$ 的计算是一个简单的树上差分，而 $g(i)$ 可以通过一个线段树合并求出，因为这样被包含的路径肯定是一段祖先链。

---

$L_1=L_2$：

显然只有长的路径能包含短的路径，所以将 LCA 相同的路径按照长度排序，依次检查后一个是否包含前一个即可。

---

总时间复杂度为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010;
struct Path {
	int u,v,l,dis,id;
}p[MAXN];
int n,m,x,y,eg,cnt,tot,val[MAXN],hd[MAXN],ver[2*MAXN],nx[2*MAXN],dp[MAXN];
int dep[MAXN],f[MAXN][20],dfn[MAXN],ed[MAXN],rt[MAXN],sum[MAXN*200],ch[MAXN*200][2];
vector <Path> v[MAXN];
bool cmp (Path a,Path b) {return a.dis<b.dis;}
void add_edge (int x,int y) {
	ver[++eg]=y;
	nx[eg]=hd[x];
	hd[x]=eg;
	return;
}
void modify (int &p,int l,int r,int xl,int xr,int v) {
	if (xr<l||r<xl) {return;}
	if (!p) {p=++tot;}
	if (xl<=l&&r<=xr) {
		sum[p]+=v;
		return;
	}
	int mid=(l+r)>>1;
	modify(ch[p][0],l,mid,xl,xr,v);
	modify(ch[p][1],mid+1,r,xl,xr,v);
	return;
}
int query (int p,int l,int r,int pos) {
	if (l==r) {return sum[p];}
	int mid=(l+r)>>1;
	if (pos<=mid) {return sum[p]+query(ch[p][0],l,mid,pos);}
	else {return sum[p]+query(ch[p][1],mid+1,r,pos);}
}
int merge (int x,int y) {
	if (!x||!y) {return x+y;}
	ch[x][0]=merge(ch[x][0],ch[y][0]);
	ch[x][1]=merge(ch[x][1],ch[y][1]);
	sum[x]=sum[x]+sum[y];
	return x;
}
void dfs1 (int x,int fa) {
	dep[x]=dep[fa]+1,f[x][0]=fa,dfn[x]=ed[x]=++cnt;
	for (int i=1;i<=18;i++) {f[x][i]=f[f[x][i-1]][i-1];}
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		dfs1(ver[i],x);
		ed[x]=ed[ver[i]];
	}
	return;
}
void dfs2 (int x,int fa) {
	dp[x]+=dp[fa];
	for (int i=hd[x];i;i=nx[i]) {
		if (ver[i]==fa) {continue;}
		dfs2(ver[i],x);
		rt[x]=merge(rt[x],rt[ver[i]]);
	}
	int len=v[x].size();
	for (int i=0;i<len;i++) {
		Path tmp=v[x][i];
		val[tmp.id]-=query(rt[x],1,n,dfn[tmp.u])+query(rt[x],1,n,dfn[tmp.v]);
	}
	for (int i=0;i<len;i++) {
		Path tmp=v[x][i];
		if (tmp.u==tmp.l) {modify(rt[x],1,n,dfn[tmp.v],ed[tmp.v],1);}
	}
	return;
}
int query_lca (int x,int y) {
	if (dep[x]<dep[y]) {swap(x,y);}
	for (int i=18;i>=0;i--) {
		if (dep[x]-(1<<i)>=dep[y]) {x=f[x][i];}
	}
	if (x==y) {return x;}
	for (int i=18;i>=0;i--) {
		if (f[x][i]!=f[y][i]) {x=f[x][i],y=f[y][i];}
	}
	return f[x][0];
}
int query_anc (int x,int y) {return (dfn[y]<=dfn[x]&&ed[x]<=ed[y]);}
int main () {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		add_edge(x,y),add_edge(y,x);
	}
	dfs1(1,0);
	for (int i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		if (dep[x]>dep[y]) {swap(x,y);}
		p[i].u=x,p[i].v=y,p[i].l=query_lca(x,y);
		p[i].dis=dep[x]+dep[y]-2*dep[p[i].l],p[i].id=i;
		v[p[i].l].push_back(p[i]),dp[p[i].l]++;
	}
	dfs2(1,0);
	for (int i=1;i<=m;i++) {
		val[i]+=dp[p[i].u]+dp[p[i].v]-2*dp[p[i].l];
		if (val[i]) {
			printf("No\n");
			return 0;
		}
	}
	for (int i=1;i<=n;i++) {
		sort(v[i].begin(),v[i].end(),cmp);
		int len=v[i].size();
		for (int j=1;j<len;j++) {
			if ((query_anc(v[i][j].u,v[i][j-1].u)&&query_anc(v[i][j].v,v[i][j-1].v))||
				(query_anc(v[i][j].u,v[i][j-1].v)&&query_anc(v[i][j].v,v[i][j-1].u))) {continue;}
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	return 0;
}
```


---

## 作者：myster1ous (赞：1)

## Problem Statement

给定一颗 $n$ 个节点的树，给定 $f$ 个树上的路径，判断这 $f$ 个路径是否两两之间互不相交或其一包含另一个。

## Solution

我们考虑将加入一个路径看成一个操作，每加入一个路径就判断当前是否已经不合法了，如果是直接输出 `No` 结束，否则继续加入下一个路径。

*如何判断此路径是否和已经加入的其他路径相交但不包含？*

我们定义一个点的颜色是这个点属于的路径的编号，一开始所有点的颜色都为 $0$。

如果没有加入过当前路径的子集，那么我们只需判断这条路径上是否有两个点的颜色不同（这可以 $\mathcal{O}(\log^2 n)$ 地求出），如果这条路径上的所有点的颜色都相同，那么这条路径属于以下两种情况之一：

- 这条路径属于另一个路径的子集。
- 这条路径上的所有点都没有被其他路径经过。

如果这个路径和另一条路径相交但不包含，那么这条路径上的点的颜色必然有不同，否则必然属于以上两种情况之一，所以如果颜色有不同直接输出 `No` 结束。

但是考虑如果之前已经加入的路径是当前路径的子集，那么上述算法会判断出错，因此我们可以直接按照路径的长度排序，这样可以保证在加入一个路径的时候，该路径一定没有子集已经加入（除非有两个完全相同的路径）。

所以总结一下，算法的流程如下：

- 将所有的路径按照路径长度排序，优先处理更长的序列。
- 对于每一个路径：
  - 首先判断它是否和已经加入的路径相交，这个命题等价于判断这个路径上点的颜色是否都相同。如果不相同输出 `No` 并结束。
  - 否则，我们直接将路径上的节点的颜色染为这个路径的编号。
- 加入了所有序列都没有发生矛盾，输出 `Yes`。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long

constexpr int maxn = 200010;
constexpr int inf = 1145141919810LL;

// We need to make a tree-decomposition that supports:
// -- Tree query, if all the nodes in a link was the same, returns the value
// --             else returns -1
//
// -- Tree modification, modify all the nodes in a link to the same value

// First of all, we need a segmentree that supports:
// -- Ranged query, if all the nodes in a range was the same, returns the value
// -- 				else returns -1
//
// -- Ranged modification, modify all the nodes in a range to the same value

using sametype = int; // -1 -> not the same, inf -> nothing
					  // other -> all the same to the 'other'
using tagtype = int; // inf -> no tag, other -> have tag the same to the 'other'
					  
sametype merge(sametype a, sametype b) {
	if (a == inf) return b;
	if (b == inf) return a;
	if (a == -1 || b == -1) return -1;
	return (a == b ? a : -1);
}

struct segmentree {
	// A segmentree that supports ranged query same, ranged modification to same value
	// In the question, only use this segmentree with dfn value! (in tree decomposition)
	int l, r, mid;
	segmentree *son[2];
	sametype sameval;
	tagtype settag;
	
	segmentree(int L, int R) {
		l = L, r = R, mid = (l + r) / 2;
		settag = inf;
		if (l == r) {
			son[0] = son[1] = nullptr;
			sameval = 0; // All the same to the zero
		} else {
			son[0] = new segmentree(l, mid);
			son[1] = new segmentree(mid + 1, r);
			sameval = merge(son[0]->sameval, son[1]->sameval);
		}
	}
	
	void pushdown() {
		if (settag != inf) {
			son[0]->settag = settag;
			son[0]->sameval = settag;
			son[1]->settag = settag;
			son[1]->sameval = settag;
			settag = inf;
		}
	}
	
	sametype query(int L, int R) {
		if (L > R) std::swap(L, R);
//		std::cout << "Querying [" << L << ", " << R << "] in node (" << l << ", " << r << ")" << std::endl;
		if (L <= l && r <= R){
			return sameval;
		} else {
			pushdown();
			sametype ans = inf;
			if (L <= mid) ans = merge(ans, son[0]->query(L, R));
			if (mid < R)  ans = merge(ans, son[1]->query(L, R));
			return ans;
		}
	}
	
	void modification(int L, int R, int set) {
		if (L > R) std::swap(L, R);
		if (L <= l && r <= R) {
			sameval = set, settag = set;
		} else {
			pushdown();
			if (L <= mid) son[0]->modification(L, R, set);
			if (mid < R)  son[1]->modification(L, R, set);
			sameval = merge(son[0]->sameval, son[1]->sameval);
		}
	}
};

int n, f, u, v;
std::vector<int> graph[maxn];

struct tree { // The tree decomposition
	int depth[maxn], father[maxn], size[maxn], heavy[maxn];
	int dfn[maxn], top[maxn], total;
	segmentree *seg;

	void dfsbuild(int now, int de, int fa) {
		depth[now] = de, father[now] = fa;
		size[now] = 1;
		for (auto to : graph[now])
			if (to != fa) {
				dfsbuild(to, de + 1, now);
				size[now] += size[to];
				if (!heavy[now] || size[heavy[now]] < size[to]) heavy[now] = to;
			}
	}
	
	void dfschain(int now, int chain) {
		top[now] = chain;
		dfn[now] = ++total;
		if (!heavy[now]) return;
		dfschain(heavy[now], chain);
		for (auto to : graph[now])
			if (to != father[now] && to != heavy[now])
				dfschain(to, to);
	}

	void init() {
		total = 0, seg = new segmentree(1, n);
		dfsbuild(1, 1, -1);
		dfschain(1, 1);
	}
	
	int lca(int u, int v) {
		while (top[u] != top[v]) {
			if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
			u = father[top[u]];
		}
		return (depth[u] < depth[v] ? u : v);
	}
	
	int query(int u, int v) {
//		std::cout << "Starting to query (" << u << " -> " << v << ")" << std::endl;
		sametype ans = inf;
		while (top[u] != top[v]) {
			if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
			ans = merge(ans, seg->query(dfn[top[u]], dfn[u]));
			u = father[top[u]];
		}
		if (depth[u] < depth[v]) std::swap(u, v);
		ans = merge(ans, seg->query(dfn[v], dfn[u]));
//		std::cout << "Result of querying (" << u << ", " << v << ") is " << ans << std::endl;
		return ans;
	}
	
	void modify(int u, int v, int set) {
		while (top[u] != top[v]) {
			if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
			seg->modification(dfn[top[u]], dfn[u], set);
			u = father[top[u]];
		}
		if (depth[u] < depth[v]) std::swap(u, v);
		seg->modification(dfn[v], dfn[u], set);
//		std::cout << "Modified [" << u << ", " << v << "] with " << set << std::endl;
	}
} tre;

struct path {
	int u, v, lca, length;
	path(int l=0, int r=0) { u = l, v = r; }
} p[maxn];

signed main() {
	
	std::cin >> n >> f;
	
	for (int i = 1; i < n; i++) {
		std::cin >> u >> v;
		graph[u].emplace_back(v);
		graph[v].emplace_back(u);
	}
	
	for (int i = 1; i <= f; i++) std::cin >> p[i].u >> p[i].v;
	
	tre.init();
	
	for (int i = 1; i <= f; i++) {
		p[i].lca = tre.lca(p[i].u, p[i].v);
		p[i].length = tre.depth[p[i].u] + tre.depth[p[i].v] - tre.depth[p[i].lca] - tre.depth[p[i].lca] + 1;
	}
	
	std::sort(p + 1, p + f + 1, [] (const path& a, const path& b) { return a.length > b.length; });
	// Sort it by length, we don't want short ones first.
//	std::cout << "Completed initialization!\n";
	for (int i = 1; i <= f; i++) {
		int u = p[i].u, v = p[i].v;
		sametype res = tre.query(u, v);
		if (res == -1) {
			std::cout << "No\n";
			return 0;
		} else tre.modify(u, v, i);
	}
	
	std::cout << "Yes\n";
	return 0;
}
```

---

## 作者：litjohn (赞：1)

### 思路
一个非常简单的思路：一开始将整棵树染上某种代表空的颜色，然后将所有路径按长度由长到短排序，从前往后考虑。

如果这条路径上只有一种颜色，那么它肯定被某条路径完全包含或者它经过的点上没有其他路径，合法，将它经过的点都染上代表它的颜色。反之则它与某条其他路径有交集但却不被完全包含，输出 No，结束程序。
### 实现
对树进行树剖，建出一颗支持区间赋值与区间查询颜色（如果不是同样的颜色就返回某个特殊值）的线段树，然后就是树剖板子。
### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
int n, f;
array<int, 100005> fa, depth, top, son, rev, tree_size;
vector<int> dfn(1);

struct path {
    int u, v, length;

    bool operator<(path b) const {
        return length > b.length;
    }

    path(int u, int v, int length) : u(u), v(v), length(length) {}
};

vector<path> paths;
array<vector<int>, 100005> e;

struct node {
    int assign_tag, color;

    node() : assign_tag(-2), color(-1) {}
};

array<node, 400005> seg;

inline void apply_assign(int p, int x) {
    seg[p].color = x;
    seg[p].assign_tag = x;
}

void push_down(int p) {
    if (seg[p].assign_tag != -2) {
        apply_assign(p * 2, seg[p].assign_tag);
        apply_assign(p * 2 + 1, seg[p].assign_tag);

        seg[p].assign_tag = -2;
    }
}

int query(int l, int r, int s, int t, int p) {
    if (l <= s && r >= t) {
        return seg[p].color;
    } else {
        int mid = (s + t) >> 1, left = -1, right = -1;
        push_down(p);

        if (l <= mid) {
            left = query(l, r, s, mid, p * 2);
        }

        if (r > mid) {
            right = query(l, r, mid + 1, t, p * 2 + 1);
        }

        if (l <= mid && r > mid) {
        	if (left == right) {
            	return left;
        	} else {
        		//cerr << "range: " << s << " " << t << "\n";
        		//cerr << left << " " << right << "\n";
            	return -2;
        	}
        } else {
        	if (l <= mid) {
        		return left;
        	} else {
        		return right;
        	}
        }
    }
}

void assign(int l, int r, int c, int s, int t, int p) {
    if (l <= s && r >= t) {
        apply_assign(p, c);
    } else {
        int mid = (s + t) >> 1;
        push_down(p);

        if (l <= mid) {
            assign(l, r, c, s, mid, p * 2);
        }

        if (r > mid) {
            assign(l, r, c, mid + 1, t, p * 2 + 1);
        }

        if (seg[p * 2].color == seg[p * 2 + 1].color) {
            seg[p].color = seg[p * 2].color;
        } else {
            seg[p].color = -2;
        }
    }
}

void init(int p) {
    top[p] = p;
    tree_size[p] = 1;

    for (auto i: e[p]) {
        if (i != fa[p]) {
            fa[i] = p;
            depth[i] = depth[p] + 1;
            init(i);

            tree_size[p] += tree_size[i];

            if (tree_size[i] > tree_size[son[p]]) {
                son[p] = i;
            }
        }
    }
}

void cut_tree(int p) {
    rev[p] = dfn.size();
    dfn.push_back(p);

    if (son[p]) {
        top[son[p]] = top[p];
        cut_tree(son[p]);
    }

    for (auto i: e[p]) {
        if (i != fa[p] && i != son[p]) {
            cut_tree(i);
        }
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            swap(u, v);
        }

        u = fa[top[u]];
    }

    return (depth[u] < depth[v] ? u : v);
}

void path_query(int u, int v) {
    int last_color = query(rev[u], rev[u], 1, n, 1), now_color;

    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            swap(u, v);
        }

        now_color = query(rev[top[u]], rev[u], 1, n, 1);
        if (now_color != last_color) {
            cout << "No";
            exit(0);
        }

        u = fa[top[u]];
    }

    if (depth[u] > depth[v]) {
        swap(u, v);
    }

    now_color = query(rev[u], rev[v], 1, n, 1);

    if (last_color != now_color || last_color == -2) {
        cout << "No";
        exit(0);
    }
}

void path_assign(int u, int v, int w) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            swap(u, v);
        }

        assign(rev[top[u]], rev[u], w, 1, n, 1);
        u = fa[top[u]];
    }

    if (depth[u] > depth[v]) {
        swap(u, v);
    }

    assign(rev[u], rev[v], w, 1, n, 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> f;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    init(1);
    cut_tree(1);

    for (int i = 1; i <= f; ++i) {
        int u, v, w;
        cin >> u >> v;

        w = depth[u] + depth[v] - 2 * depth[lca(u, v)];

        paths.emplace_back(u, v, w);
    }

    sort(paths.begin(), paths.end());

    int cnt = 1;
    for (auto [u, v, w]: paths) {
        path_query(u, v);
        path_assign(u, v, cnt);
        cnt++;
    }

    cout << "Yes";
    return 0;
}
```

---

## 作者：yzh_Error404 (赞：1)

难道树上题不应该先考虑树剖吗？

显然小的区间只能被比它长的区间完全覆盖。

所以可以考虑将每个区间按长度从大到小排序。

然后对于遍历到的每一个区间，询问这个区间是否只有一种颜色。

具体就是这个区间的最大值和最小值是否相等，树剖即可。

然后就没有其他的了。

代码实现：

```cpp
#include<bits/stdc++.h>
#define NO return puts("No"),0;
#define YES return puts("Yes"),0;
using namespace std;
const int MAXN=1e6+5;
const int INF=0x7f7f7f7f;
struct node
{
	int to,nxt;
}e[MAXN];
int head[MAXN],cnt;
inline void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
struct period
{
	int x,y;
}q[MAXN];
int n,f;
int fa[MAXN],siz[MAXN],dep[MAXN],hson[MAXN];
inline void dfs1(int x,int f)
{
	fa[x]=f;
	dep[x]=dep[f]+1;
	siz[x]=1;
	int maxson=-1;
	for(register int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==f)continue;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[y]>maxson)
		{
			maxson=siz[y];
			hson[x]=y;
		}
	}
}
int top[MAXN],id[MAXN],tim;
inline void dfs2(int x,int ltop)
{
	id[x]=++tim;
	top[x]=ltop;
	if(!hson[x])return;
	dfs2(hson[x],ltop);
	for(register int i=head[x];i;i=e[i].nxt)
	{
		int y=e[i].to;
		if(y==hson[x]||y==fa[x])continue;
		dfs2(y,y);
	}
}
int maxn[MAXN],minn[MAXN],dat[MAXN];
inline void pushup(int p)
{
	maxn[p]=max(maxn[p<<1],maxn[p<<1|1]);
	minn[p]=min(minn[p<<1],minn[p<<1|1]);
}
inline void addtag(int p,int k)
{
	maxn[p]=minn[p]=dat[p]=k;
}
inline void pushdown(int p)
{
	if(dat[p])
	{
		addtag(p<<1,dat[p]);
		addtag(p<<1|1,dat[p]);
		dat[p]=0;
	}
}
inline void change(int p,int l,int r,int a,int b,int k)
{
	if(r<a||l>b)return;
	if(l>=a&&r<=b)
	{
		addtag(p,k);
		return;
	}
	int mid=(l+r)>>1;
	pushdown(p);
	change(p<<1,l,mid,a,b,k);
	change(p<<1|1,mid+1,r,a,b,k);
	pushup(p);
}
inline int ask_max(int p,int l,int r,int a,int b)
{
	if(r<a||l>b)return -INF;
	if(l>=a&&r<=b)return maxn[p];
	int mid=(l+r)>>1;
	pushdown(p);
	return max(ask_max(p<<1,l,mid,a,b),ask_max(p<<1|1,mid+1,r,a,b));
}
inline int ask_min(int p,int l,int r,int a,int b)
{
	if(r<a||l>b)return INF;
	if(l>=a&&r<=b)return minn[p];
	int mid=(l+r)>>1;
	pushdown(p);
	return min(ask_min(p<<1,l,mid,a,b),ask_min(p<<1|1,mid+1,r,a,b));
}
inline void change_ran(int x,int y,int k)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		change(1,1,n,id[top[x]],id[x],k);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	change(1,1,n,id[x],id[y],k);
}
inline int ask_ran_max(int x,int y)
{
	int ans=-INF;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=max(ans,ask_max(1,1,n,id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans=max(ans,ask_max(1,1,n,id[x],id[y]));
	return ans;
}
inline int ask_ran_min(int x,int y)
{
	int ans=INF;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=min(ans,ask_min(1,1,n,id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	ans=min(ans,ask_min(1,1,n,id[x],id[y]));
	return ans;
}
inline int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
inline int dist(int x,int y)
{
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
inline bool cmp(period a,period b)
{
	return dist(a.x,a.y)>dist(b.x,b.y);
}
int main()
{
	scanf("%d%d",&n,&f);
	for(register int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(register int i=1;i<=f;i++)
		scanf("%d%d",&q[i].x,&q[i].y);
	sort(q+1,q+1+f,cmp);
	for(register int i=1;i<=f;i++)
	{
		int mx=ask_ran_max(q[i].x,q[i].y),mn=ask_ran_min(q[i].x,q[i].y);
		if(mx!=mn)NO
		change_ran(q[i].x,q[i].y,++col);
	}
	YES
}
```

---

## 作者：Richard_Whr (赞：0)

超级无敌暴力做法。

直接按题意模拟，统计“无交”，“包含”，的对数，查看是否为 $m^2$。

先统计无交，无交 = 所有 - 有交。

有交可以使用连通块容斥技巧，添加时给路径点权 $+1$，边权 $-1$。查询时询问链的点权和和边权和。

因为连通块有性质 $V=E+1$，因此这样只要有交就会贡献 $1$。

包含就简单了，直接统计被包含数量然后 $\times 2$ 就是对数。

然后就是分直链和曲链讨论一下，二维数点即可。

注意到单点的情况比较复杂，不过可以直接使用和它有交的路径数量作为包含的数量。

然后做完了，一些细节需要特判。

复杂度 $O(n \log n)$

```
#include<bits/stdc++.h>
#define int long long
#define ls tr[u].l
#define rs tr[u].r
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int N=1e5+10;
vector<int> e[N];
int dfn[N],sz[N],fa[N],son[N],dep[N],top[N],ts;
int val[N],w[N];
int n,m;
struct Road
{
	int u,v,p;
}q[N];
int tot;
map<PII,int> Map;
bool flg;
vector<int> vec[N];
struct Tree
{
	int l,r;
	int sz;
}tr[N*30];
int root[N],idx;

void dfs1(int u,int p)
{
	fa[u]=p,dep[u]=dep[p]+1,sz[u]=1;
	for(auto v:e[u])
	{
		if(v==p) continue;
		dfs1(v,u);
		if(sz[v]>sz[son[u]]) son[u]=v;
		sz[u]+=sz[v];
	}
}

void dfs2(int u,int t)
{
	top[u]=t,dfn[u]=++ts;
	if(son[u]) dfs2(son[u],t);
	for(auto v:e[u])
	{
		if(v==fa[u] || v==son[u]) continue;
		dfs2(v,v);
	}
}

int lca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	return v;
}

int find(int u,int v)
{
	while(top[u]!=top[v])
	{
		u=top[u];
		if(fa[u]==v) return u;
		u=fa[u];
	}
	return son[v];
}

void Dfs(int u)
{
	for(auto v:e[u])
	{
		if(v==fa[u]) continue;
		Dfs(v);
		val[u]+=val[v],w[u]+=w[v];
	}
}

void Dfs1(int u)
{
	for(auto v:e[u])
	{
		if(v==fa[u]) continue;
		val[v]+=val[u],w[v]+=w[u];
		Dfs1(v);
	}
}

int insert(int p,int l,int r,int x)
{
	int u=++idx;
	tr[u]=tr[p];
	tr[u].sz++;
	if(l==r) return u;
	int mid=l+r>>1;
	if(x<=mid) ls=insert(tr[p].l,l,mid,x);
	else rs=insert(tr[p].r,mid+1,r,x);
	return u;
}

int query(int L,int R,int l,int r,int ql,int qr)
{
	if(l>r || ql>qr) return 0;
	if(l>=ql && r<=qr) return tr[R].sz-tr[L].sz;
	else
	{
		int mid=l+r>>1,res=0;
		if(ql<=mid) res+=query(tr[L].l,tr[R].l,l,mid,ql,qr);
		if(qr>mid) res+=query(tr[L].r,tr[R].r,mid+1,r,ql,qr);
		return res;
	}
}

int calc(int l1,int r1,int l2,int r2)
{
	if(l1>l2) swap(l1,l2),swap(r1,r2);
	if(l1>r1 || l2>r2) return 0;
	return query(root[l1-1],root[r1],1,n,l2,r2);
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m;
	for(int i=1,a,b;i<n;i++) cin>>a>>b,e[a].push_back(b),e[b].push_back(a);
	dfs1(1,0);
	dfs2(1,1);
	
	for(int i=1,u,v,p;i<=m;i++)
	{
		cin>>u>>v;p=lca(u,v);
		if(u>v) swap(u,v);
		if(Map[{u,v}]) continue;
		Map[{u,v}]++;
		val[u]++,val[v]++,val[p]--;
		if(fa[p]) val[fa[p]]--;
		w[u]--,w[v]--,w[p]+=2;
		if(dfn[u]>dfn[v]) swap(u,v);
		vec[dfn[u]].push_back(dfn[v]);
		q[++tot]={u,v,p};
	}
	
	Dfs(1); 
	Dfs1(1);
	
	for(int i=1;i<=n;i++)
	{
		root[i]=root[i-1];
		for(auto j:vec[i]) root[i]=insert(root[i],1,n,j);
	}
	
	LL res=0;
	for(int i=1;i<=tot;i++)
	{
		int u=q[i].u,v=q[i].v,p=q[i].p,have,cnt;
		have=val[u]+val[v]-val[p]-val[fa[p]]+w[u]+w[v]-2*w[p];
		cnt=tot-have+1;
		if(u==p)
		{
			int x,y;
			if(u==v) y=have;
			else
			{
				x=find(v,u);
				y=calc(dfn[v],dfn[v]+sz[v]-1,1,dfn[x]-1)+calc(dfn[v],dfn[v]+sz[v]-1,dfn[x]+sz[x],n);
			}
			cnt+=(y-1)*2;
		}
		else
		{
			int y=calc(dfn[v],dfn[v]+sz[v]-1,dfn[u],dfn[u]+sz[u]-1);
			cnt+=(y-1)*2;
		} 
		res=(LL)res+cnt;
	}
	
	if(res==(LL)tot*tot) cout<<"Yes\n";
	else cout<<"No\n";
	
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：0)

我们考虑按路径长度递增顺序逐渐加入每一条路径。  
那么只需考虑后加入的路径把前面路径包含的情况。

一个巧妙的转化：  
先将树看成 $n$ 个孤立点，每次加入一条路径再将这条路径上的边连上。

那么：一条加入的路径和前面所有路径无交或将其包含等价于加入新边后，路径所在连通块大小等于路径长度。

否则两路径必然有交且不包含。

具体实现用并查集写一个路径压缩即可。

复杂度 $O(n\alpha(n))$。

```cpp
struct DSU
{
  ve<int>f,g;
  DSU(int n){f.assign(n,0),g.assign(n,1),sd iota(all(f),0);}
  il int F(int x){return f[x]^x?f[x]=F(f[x]):x;}
  il void _M(int u,int v){if((u=F(u))^(v=F(v))) f[u]=v,g[v]+=g[u];}
  il bool _Q(int u,int v){return F(u)==F(v);}
  il int op[](int u){return g[F(u)];}
};
il void Solve()
{
  int n,m;rd(n),rd(m);
  ve<ve<int>>G(n);
  for(int u,v,i=1;i<n;++i) rd(u),rd(v),--u,--v,G[u].pb(v),G[v].pb(u);
  ve<int>sz(n),fa(n),d(n),h(n,-1),t(n);
  sd function<void(int,int)>dfs_1=[&](int u,int p)
  {
    sz[u]=1,fa[u]=p,d[u]=d[p]+1;
    for(int v:G[u]) if(v^p) {
      dfs_1(v,u),sz[u]+=sz[v];
      if(!~h[u]||sz[v]>sz[h[u]]) h[u]=v;
    }
  };
  dfs_1(0,0);
  sd function<void(int,int)>dfs_2=[&](int u,int p)
  {
    if(~h[u]) t[h[u]]=t[u],dfs_2(h[u],u);
    for(int v:G[u]) if(v^p&&v^h[u]) dfs_2(t[v]=v,u);
  };
  dfs_2(0,0);
  auto LCA=[&](int u,int v)
  {
    for(;t[u]^t[v];u=fa[t[u]]) {
      if(d[t[u]]<d[t[v]]) sd swap(u,v);
    }
    return d[u]<d[v]?u:v;
  };
  ve<sd array<int,4>>e(m);
  for(auto&f:e) rd(f[1]),rd(f[2]),--f[1],--f[2],f[3]=LCA(f[1],f[2]),f[0]=d[f[1]]+d[f[2]]-2*d[f[3]]+1;
  sd stable_sort(all(e));
  DSU S(n);
  for(auto[len,u,v,lca]:e) {
    for(u=S.F(u);d[lca]<d[u];) {
      S._M(u,fa[u]),u=S.F(u);
    }
    for(v=S.F(v);d[lca]<d[v];) {
      S._M(v,fa[v]),v=S.F(v);
    }
    if(len!=S[u]) {
      wrt("No");
      return;
    }
  }
  wrt("Yes");
  return;
}
```

[$\color{green}{\checkmark}$](https://www.luogu.com.cn/record/148570146)

---

## 作者：ExplodingKonjac (赞：0)

### [原题链接](https://www.luogu.com.cn/problem/P6963)

~~又是充分发扬人类智慧~~

## 题目分析

看到题发现不会做，所以考虑乱搞。

想象一下：在一条链上（假设其长度为 $len$），给端点加上 $-len+1$，给其它点加上 $1$。那么整条链的和就是 $0$。我们称经过这些处理的链为关键链。

那么，如果某条链包含了一条关键链，或者与其不相交，那么该关键链对这条链的贡献就是 $0$。

由于相互包含不太好处理，所以我们先将所有 $m$ 条链按照长度从小到大处理，依次将其加入关键链中。因为只可能长度大的包含长度小的，所以现在只用考虑当前处理的链包含关键链的情况了。

假设我们已经对所有处理过的链进行了上文的操作，现在查询当前链的点权和。我们发现：

* 如果当前链与关键链都不相交或者包含，那么结果**一定**是 $0$；

* 否则，结果**不一定**是 $0$。

发现所有结果都是 $0$ 是题目所给命题成立的必要条件，但不充分，所以可以使用随机化什么的乱搞。

1. 不要每条关键链只加 $1$，可以加上一个随机数 $rand$，这样可以大大减小错误概率；

2. 可以使用多次哈希，减小错误概率（但是不用貌似也过了）。

然后动态的链上加、求和都可以用树剖做，这题就……没了。

## 代码实现

虽然代码比较长，但是大部分都是树剖板子，所以也不繁杂。

```cpp
#include <bits/stdc++.h>
using namespace std;

/*
省略100多行的快读快写代码
即下文中的qin、qout
*/

typedef long long LL;
int n,m;
struct Edge{ int to,nxt; }e[200005];
int cnt,head[100005];
inline void addEdge(int u,int v)
	{ e[++cnt]=(Edge){v,head[u]},head[u]=cnt; }
int dfn,siz[100005],dep[100005],lb[100005],top[100005],son[100005],fa[100005];
void dfs1(int u,int ffa=0)
{
	siz[u]=1,dep[u]=dep[ffa]+1,fa[u]=ffa;
	for(int i=head[u],v;v=e[i].to;i=e[i].nxt)
		if(v!=ffa)
		{
			dfs1(v,u),siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])	son[u]=v;
		}
}
void dfs2(int u,int tp)
{
	top[u]=tp,lb[u]=++dfn;
	if(son[u])	dfs2(son[u],tp);
	for(int i=head[u],v;v=e[i].to;i=e[i].nxt)
		if(v!=fa[u] && v!=son[u])
			dfs2(v,v);
}
int lca(int x,int y)
{
	int fx=top[x],fy=top[y];
	while(fx!=fy)
		if(dep[fx]>=dep[fy])
			x=fa[fx],fx=top[x];
		else
			y=fa[fy],fy=top[y];
	return dep[x]<dep[y]?x:y;
}
struct F$$k
{
	int u,v,len;
	inline bool operator <(const F$$k &b)const
		{ return len<b.len; }
}a[100005];
mt19937 mt_rnd(time(0));

struct TreeNode{ LL sum,tag;int lc,rc; }t[200005];
int tot,rt;
#define LC t[i].lc
#define RC t[i].rc
inline void addTag(int i,int x,int len)
	{ t[i].sum+=1ll*x*len,t[i].tag+=x; }
inline void pushup(int i)
	{ t[i].sum=t[LC].sum+t[RC].sum; }
inline void pushdown(int i,int l,int r)
{
	if(!t[i].tag)	return;
	int mid=(l+r)>>1;
	addTag(LC,t[i].tag,mid-l+1);
	addTag(RC,t[i].tag,r-mid);
	t[i].tag=0;
}
void build(int l,int r,int &i=rt)
{
	i=++tot;
	if(l!=r)
	{
		int mid=(l+r)>>1;
		build(l,mid,LC),build(mid+1,r,RC);
	}
}
void modify(int lq,int rq,int x,int i=rt,int l=1,int r=n)
{
	if(l>=lq && r<=rq)	addTag(i,x,r-l+1);
	else
	{
		int mid=(l+r)>>1;
		pushdown(i,l,r);
		if(mid>=lq)	modify(lq,rq,x,LC,l,mid);
		if(mid<rq)	modify(lq,rq,x,RC,mid+1,r);
		pushup(i);
	}
}
LL query(int lq,int rq,int i=rt,int l=1,int r=n)
{
	if(l>=lq && r<=rq)	return t[i].sum;
	else
	{
		LL mid=(l+r)>>1,res=0;
		pushdown(i,l,r);
		if(mid>=lq)	res+=query(lq,rq,LC,l,mid);
		if(mid<rq)	res+=query(lq,rq,RC,mid+1,r);
		return res;
	}
}
inline int treeQuery(int x,int y)
{
	int fx=top[x],fy=top[y];
	LL res=0;
	while(fx!=fy)
		if(dep[fx]>=dep[fy])
			res+=query(lb[fx],lb[x]),x=fa[fx],fx=top[x];
		else
			res+=query(lb[fy],lb[y]),y=fa[fy],fy=top[y];
	if(lb[x]<=lb[y])
		res+=query(lb[x],lb[y]);
	else
		res+=query(lb[y],lb[x]);
	return res;
}
inline void treeModify(int x,int y,int v)
{
	int fx=top[x],fy=top[y];
	while(fx!=fy)
		if(dep[fx]>=dep[fy])
			modify(lb[fx],lb[x],v),x=fa[fx],fx=top[x];
		else
			modify(lb[fy],lb[y],v),y=fa[fy],fy=top[y];
	if(lb[x]<=lb[y])
		modify(lb[x],lb[y],v);
	else
		modify(lb[y],lb[x],v);
}
inline void gao(const F$$k &zt)
{
	int u=zt.u,v=zt.v;
	LL val=mt_rnd()%100+1;
	treeModify(u,v,val);
	if(mt_rnd()&1)	swap(u,v);
	treeModify(u,u,-val*(zt.len+1));
}

int main()
{
	int u,v;
	qin>>n>>m;
	for(int i=1;i<n;i++)	qin>>u>>v,addEdge(u,v),addEdge(v,u);
	dfs1(1),dfs2(1,1);
	for(int i=1;i<=m;i++)
	{
		qin>>u>>v,a[i].u=u,a[i].v=v;
		int l=lca(u,v);
		a[i].len=dep[u]+dep[v]-2*dep[l];
	}
	sort(a+1,a+m+1);
	build(1,n);
	bool flag=true;
	for(int i=1;i<=m;i++)
	{
		u=a[i].u,v=a[i].v;
		int res1=treeQuery(u,v);
		if(res1)	{ flag=false;break; }
		gao(a[i]);
	}
	qout<<(flag?"Yes":"No");
//	return qout.flush(),0;
}
```


---

