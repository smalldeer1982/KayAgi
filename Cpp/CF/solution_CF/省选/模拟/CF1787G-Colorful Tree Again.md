# Colorful Tree Again

## 题目描述

给定一棵有 $n$ 个节点的树，边有边权和颜色。每个点有被摧毁和不被摧毁两种状态，初始所有点都没被摧毁。

一条简单路径指图中没有重复节点的路径。简单路径的长度定义为路径上所有边的边权之和。

定义一条简单路径是好的，当且仅当路径仅有某一种颜色 $c$ 构成，且所有颜色为 $c$ 的边都在这条简单路径里，且路径上所有节点都没被摧毁。

你需要处理两种操作：

1. 摧毁一个节点；
2. 修复一个节点。

每个操作之后，你都需要输出最长的好的路径长度。若没有输出 $0$。

~~写了 3 次样例解释全被删了 QAQ~~

## 样例 #1

### 输入

```
5 4
4 1 3 4
5 2 4 4
3 1 3 2
1 2 5 1
0 4
0 3
0 2
1 3```

### 输出

```
5
5
0
3```

## 样例 #2

### 输入

```
5 5
4 1 4 4
4 5 2 2
3 1 2 4
3 2 3 1
0 3
0 4
1 3
1 4
0 1```

### 输出

```
2
0
3
6
3```

## 样例 #3

### 输入

```
6 9
3 2 2 3
2 4 4 2
3 1 5 5
6 4 3 2
5 3 1 3
0 2
0 4
0 5
0 6
1 2
1 4
1 5
0 3
1 6```

### 输出

```
5
5
5
5
5
5
5
0
7```

## 样例 #4

### 输入

```
1 2
0 1
1 1```

### 输出

```
0
0```

# 题解

## 作者：Graphcity (赞：5)

大家好，这里是更更更更简单且更更更更好写的 $O(n\log n)$ 做法。

判断一种颜色是否合法很简单，所以我们可以先去掉不合法的颜色。加入或者删除一个点的时候，我们希望能够快速更改经过它的颜色的剩余点数。

这里先提一个前置知识：bdfs 序。bdfs 序指的就是往序列中先加入根节点，然后按照 dfs 序依次加入每个点的所有儿子的顺序。这种顺序可以保证每个点的所有儿子标号连续，且整棵子树除根节点外标号连续。

注意到经过 $x$ 的颜色中，要么也经过 $fa_x$，且这种颜色只有一种；要么仅经过 $x$ 子树内的点。这提示我们 **对颜色进行重标号**。考虑从前往后按照 bdfs 序扫描点，如果一个点的父亲边颜色未被标记，则标记这个颜色。最后按照标记顺序从前往后给颜色编号。

不难发现，对于 $x$ 的邻边，它们的编号要么等于父亲边的编号，要么形成一个区间。这样，我们维护每种颜色的被删除点数量时，仅需要做区间加减操作。

对这个问题进行建模：给定 $a_{1\cdots k}$ 和 $c_{1\cdots k}$，需要区间修改 $c$ 以及查询 $\max_{c_i=0}a_i$。此外，有一个性质：$c_i\ge 0$。那么每个线段树节点维护 $(mn,k)$ 表示这个节点所代表区间的 $\min c$ 和 $c$ 取到最小值时的 $\max a$。区间修改时，仅需要打个 $tag$ 标记表示 $mn\gets mn+tag$。

代码很好写，主要码量在于判断颜色是否合法。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

struct Node{int frm,to,nxt,w,c;} Edge[Maxn*2+5];
int tot,Head[Maxn+5];
inline void Addedge(int x,int y,int w,int c)
{
    Edge[++tot]=(Node){x,y,Head[x],w,c},Head[x]=tot;
    Edge[++tot]=(Node){y,x,Head[y],w,c},Head[y]=tot;
}
int n,m,s,id[Maxn+5],pos[Maxn+5],chk[Maxn+5],tag[Maxn*4+5];
int val[Maxn+5],L[Maxn+5],R[Maxn+5]; ll sum[Maxn+5];
vector<int> col[Maxn+5];
struct Data
{
    int mn; ll w;
    inline Data() {}
    inline Data(int _mn,ll _w): mn(_mn),w(_w) {}
} t[Maxn*4+5];
inline Data operator+(Data a,Data b)
{Data c; c.mn=min(a.mn,b.mn),c.w=max(a.w*(a.mn==c.mn),b.w*(b.mn==c.mn)); return c;}
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void push_up(int p) {t[p]=t[ls(p)]+t[rs(p)];}
inline void f(int p,int k) {t[p].mn+=k,tag[p]+=k;}
inline void push_down(int p) {if(tag[p]) f(ls(p),tag[p]),f(rs(p),tag[p]),tag[p]=0;}
inline void Build(int l,int r,int p)
{
    if(l==r) {t[p]=Data(0,sum[pos[l]]); return;}
    int mid=(l+r)>>1;
    Build(l,mid,ls(p)),Build(mid+1,r,rs(p)),push_up(p);
}
inline void Modify(int nl,int nr,int l,int r,int p,int k)
{
    if(l<=nl && nr<=r) {f(p,k); return;}
    int mid=(nl+nr)>>1; push_down(p);
    if(l<=mid) Modify(nl,mid,l,r,ls(p),k);
    if(r>mid) Modify(mid+1,nr,l,r,rs(p),k);
    push_up(p);
}
inline void Duel(int c)
{
    static int deg[Maxn+5],vis[Maxn+5];
    int cnt=0,mx=0;
    for(auto id:col[c])
    {
        int x=Edge[id].frm,y=Edge[id].to;
        if(!vis[x]) vis[x]=1,cnt++; if(!vis[y]) vis[y]=1,cnt++;
        mx=max(mx,++deg[x]),mx=max(mx,++deg[y]);
    }
    if(cnt==1+col[c].size() && mx<=2) chk[c]=1;
    for(auto id:col[c])
    {
        int x=Edge[id].frm,y=Edge[id].to;
        vis[x]=0,vis[y]=0,deg[x]=0,deg[y]=0;
    }
}
inline void dfs(int x,int fa)
{
    L[x]=n+1,R[x]=0;
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to,z=Edge[i].c;
        if(y==fa) continue;
        if(chk[z] && !id[z]) id[z]=++s;
        if(z!=val[x] && id[z]) L[x]=min(L[x],id[z]),R[x]=max(R[x],id[z]);
        val[y]=z;
    }
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to,z=Edge[i].c;
        if(y==fa) continue;
        dfs(y,x);
    }
}
inline void Modify(int x,int k)
{
    if(L[x]<=R[x]) Modify(1,s,L[x],R[x],1,k);
    if(val[x]) if(L[x]>R[x] || val[x]<L[x] || val[x]>R[x])
        Modify(1,s,val[x],val[x],1,k);
}

int main()
{
    n=read(),m=read();
    For(i,1,n-1)
    {
        int a=read(),b=read(),w=read(),c=read();
        Addedge(a,b,w,c),col[c].push_back(tot),sum[c]+=w;
    }
    For(i,1,n) if(!col[i].empty()) Duel(i);
    dfs(1,0);
    For(i,1,n) if(chk[val[i]]) val[i]=id[val[i]]; else val[i]=0;
    if(!s) {For(i,1,m) printf("0\n"); return 0;}
    For(i,1,n) if(id[i]) pos[id[i]]=i;
    Build(1,s,1);
    while(m--)
    {
        int op=read(),x=read();
        Modify(x,op?-1:1);
        printf("%lld\n",t[1].mn==0?t[1].w:0ll);
    }
    return 0;
}
```



---

## 作者：Neutralized (赞：3)

CF1787G，~~在物理期末考试前的诡异自习里搞出来了~~。  

***

虽然说你对每个颜色都建虚树空间是 $O(n)$ 的，但是分开维护没有出路，这是因为一个点连出的颜色数是 $O(n)$ 的。考虑一朵菊花，反复操作菊花的根就可以使得每次要修改 $O(n)$ 棵虚树的值。  

那么考虑就放在这棵树上维护。（由于摧毁和修复是同理的所以下文只考虑摧毁）  

显然所有好路径都是树链，摧毁一个点 $u$ 会影响的路径就自然地分为两种：以 $u$ 为根的链 和 根是 $u$ 的祖先的链。  

注意到第二种至多只有一条（每个点连向父亲的颜色唯一），那么对于每条链可以简单地维护有多少点被摧毁从而判断它是否产生贡献，而不需要知道具体哪些点被摧毁。  

现在加上第一种链，对应操作就是取消所有以 $u$ 为根的链的贡献。那么如果我们把每条链都挂在它的根处，使用单点修改、求全局最大值的数据结构维护以支持对于第二种链的修改，再在外面使用另一个同样的数据结构维护所有 挂了链的未被摧毁的点，其拥有的链的最大值 的最大值，那么就做完了。  

我们可以使用平衡树或动态开点线段树，这样时间复杂度 $O((n+q) \log n)$，空间 $O(n)$ 或 $O(n \log n)$。  

实际上线段树部分只需要写 $8$ 行（。  
另外，注意找出每种颜色的链长和根时不要用链式前向星存图，使用 `vector` 将所有边按颜色排序可以做到 $O(n \log n)$。  


```cpp
const int N = 200003, oo = 2e9;
int n,q,head[N],cntr,dep[N],lca[N];
int fir[N],cnt[N],col[N],siz[N]; bool S[N]; ll len[N];
struct Node{
	int to,w,c;
	inline bool operator <(const Node &a) const{ return c==a.c?w<a.w:c<a.c; }
}; vector<Node> e[N];
#define all(x) x.begin(),x.end()

inline void DFS(int u,int fa){
	dep[u]=dep[fa]+1,sort(all(e[u]));
	(u!=1&&dep[fir[col[u]]]<dep[u])&&(fir[col[u]]=u);
	for(auto t:e[u]){
		int v=t.to; if(v==fa) continue;
		(dep[fir[t.c]]<dep[v])&&(fir[t.c]=v),col[v]=t.c,DFS(v,u);
	}
}
inline void Get(int u,int fa,int c){
	(!lca[c]||dep[lca[c]]>dep[u])&&(lca[c]=u),++siz[c];
	for(auto it = upper_bound(all(e[u]),(Node){+oo,+oo,c-1}); it!=e[u].end()&&it->c==c; ++it)
		if(it->to!=fa){ int v=it->to; len[c]+=it->w,Get(v,u,c); break; }
}
template<const int SIZ> struct SegTree{
	struct Seg{ int lc,rc; ll val; }tr[SIZ]; int tot,root[N];
	inline void Push(int u){ tr[u].val=max(tr[tr[u].lc].val,tr[tr[u].rc].val); }
	inline void Mdf(int &u,int l,int r,int x,ll d){
		if(!u) u=++tot; if(l==r){ tr[u].val=d; return; } int mid=l+r>>1;
		x<=mid?Mdf(tr[u].lc,l,mid,x,d):Mdf(tr[u].rc,mid+1,r,x,d); Push(u);
	}
}; SegTree<N*20> t; SegTree<N<<1> T;

auto Lock = [](int u){
	T.Mdf(T.root[0],1,n,u,0);
	if(u==1) return; --siz[col[u]];
	if(lca[col[u]]&&siz[col[u]]==cnt[col[u]]-1){
		int LCA = lca[col[u]];
		t.Mdf(t.root[LCA],1,n,col[u],0);
		if(S[LCA]) T.Mdf(T.root[0],1,n,LCA,t.tr[t.root[LCA]].val);
	}
};
auto Unlock = [](int u){
	T.Mdf(T.root[0],1,n,u,t.tr[t.root[u]].val);
	if(u==1) return; ++siz[col[u]];
	if(lca[col[u]]&&siz[col[u]]==cnt[col[u]]){
		int LCA = lca[col[u]];
		t.Mdf(t.root[LCA],1,n,col[u],len[col[u]]);
		if(S[LCA]) T.Mdf(T.root[0],1,n,LCA,t.tr[t.root[LCA]].val);
	}
};

main(){
	rd(n),rd(q),fill(S+1,S+n+1,1);
	for(int i=1,u,v,w,c;i<n;++i)
		rd(u),rd(v),rd(w),rd(c),e[u].push_back({v,w,c}),e[v].push_back({u,w,c}),++cnt[c];
	for(int i=1;i<=n;++i) if(cnt[i]) ++cnt[i];
	DFS(1,0);
	for(int i=1;i<=n;++i) if(fir[i]){
		Get(fir[i],0,i); if(siz[i]!=cnt[i]){ len[i]=lca[i]=-1; continue; }
		t.Mdf(t.root[lca[i]],1,n,i,len[i]);
	}
	for(int i=1;i<=n;++i) if(t.root[i])
		T.Mdf(T.root[0],1,n,i,t.tr[t.root[i]].val);
	while(q--){
		int p,x; rd(p),rd(x),S[x]^=1;
		p?Unlock(x):Lock(x); writeln(T.tr[T.root[0]].val);
	}
}
```

---

## 作者：xianggl (赞：3)

题意：

定义一条路径为好，当且仅当：

1、所有边同色。

2、所有点均没有被锁。

3、包含了这种颜色的所有边。

定义一条路径的权值为边权之和。

现给定一棵树，有多次操作，每次锁或解锁一个点，你需要求出最大的好路径的权值，若不存在输出 $0$。

题解：

先求出所有好的路径，直接把一种颜色的边抓出来，判 $deg$ 是否全部不超过 $2$，再看 $deg = 1$ 的是否恰为两个即可。

然后考虑修改一个点，我们会发现，如果说要去修改每一条好路径的状态，这个复杂度是 $O(n ^ 2)$ 的，显然不行。

于是考虑将路径挂到点上，用 ```set``` 维护，每次修改一个点就将这个点的权值赋为 $0$ 或 ```set``` 中的最大值，但是这也是 $O(n ^ 2)$ 的，因为要修改每个点的状态。

那我们思考，能不能对于一个点只维护某些经过它的路径？

注意到，一个点向上的路径最多只有一条，于是考虑对于每个点维护 $\operatorname{lca} = x$ 的所有路径。

那么修改时只需要将本身的权值设为 $0$ 或 ```set```
中的最大值，再去修改往上的路径的 $\operatorname{lca}$ 即可。

时间复杂度 $O(n \log n)$。

代码：

```
#include <bits/stdc++.h>
#define fi first
#define se second

using i64 = long long;
constexpr int N = 2e5;

std::vector<std::pair<int, int>> adj[N + 5];
int dep[N + 5], up[N + 5];

struct SegTree {
	#define ls(p) (p << 1)
	#define rs(p) (p << 1 | 1)
	#define mid (((l) + (r)) >> 1)
	std::vector<i64> mx;
	SegTree() {}
	void init(int n) {
		mx.resize(4 * n);
	}
	SegTree(int n) {
		init(n);
	}
	void change(int p, int l, int r, int k, int d) {
		if (l == r) {
			mx[p] = d;
			return ;
		}
		if (k <= mid) change(ls(p), l, mid, k, d);
		else change(rs(p), mid + 1, r, k, d);
		mx[p] = std::max(mx[ls(p)], mx[rs(p)]);
	}
};

void dfs(int u, int fa) {
	for (auto e : adj[u]) {
		int v = e.fi;
		if (v != fa) {
			dep[v] = dep[u] + 1, up[v] = e.se;
			dfs(v, u);
		}
	}
}

int main() {
	int n, m;
	std::scanf("%d %d", &n, &m);
	std::vector<std::vector<int>> s(n);
	std::vector<i64> len(n);
	for (int i = 0; i < n - 1; i++) {
		int x, y, z, c;
		std::scanf("%d %d %d %d", &x, &y, &z, &c);
		--x, --y, --c;
		adj[x].emplace_back(y, c);
		adj[y].emplace_back(x, c);
		len[c] += z;
		s[c].emplace_back(x);
		s[c].emplace_back(y);
	}
	dfs(0, -1);
	std::vector<int> deg(n), node(n, -1);
	std::vector<std::multiset<i64>> mx(n);
	SegTree t(n);
	for (int i = 0; i < n; i++) {
		int ok = 1, cnt = 0;
		for (auto x : s[i]) {
			++deg[x];
			ok &= deg[x] <= 2;
		}
		for (auto x : s[i]) cnt += deg[x] == 1;
		if (ok && cnt == 2) {
			int lca = s[i][0];
			for (auto x : s[i]) {
				if (dep[x] < dep[lca]) lca = x;
			}
			mx[lca].insert(len[i]);
			t.change(1, 0, n - 1, lca, *mx[lca].rbegin());
			node[i] = lca;
		}
		for (auto x : s[i]) --deg[x];
	}
	std::vector<int> sum(n), block(n);
	while (m--) {
		int op, x;
		std::scanf("%d %d", &op, &x);
		--x;
		if (op == 0) {
			t.change(1, 0, n - 1, x, 0);
			block[x] = 1;
			if (x && node[up[x]] != -1) {
				int c = up[x];
				++sum[c];
				if (sum[c] == 1) {
					int u = node[c];
					mx[u].erase(mx[u].find(len[c]));
					if (!block[u]) {
						t.change(1, 0, n - 1, u, mx[u].empty() | block[u] ? 0 : *mx[u].rbegin());
					}
				}
			}
		}
		else {
			t.change(1, 0, n - 1, x, mx[x].empty() ? 0 : *mx[x].rbegin());
			block[x] = 0;
			if (x && node[up[x]] != -1) {
				int c = up[x];
				--sum[c];
				if (sum[c] == 0) {
					int u = node[c];
					mx[u].insert(len[c]);
					t.change(1, 0, n - 1, u, mx[u].empty() | block[u] ? 0 : *mx[u].rbegin());
				}
			}
		}
		std::printf("%d\n", t.mx[1]);
	}
	return 0;
}

```


---

## 作者：critnos (赞：3)

大家好，这里又是更更更更更更更劣且不难写的 $O(n\sqrt{n\log n})$ 做法！

对每个点求出修改它会涉及多少条链，根号分治。

对 $\le B$ 的直接修改，对 $>B$ 的，直觉上不会有太多一条链被两个这类点影响的。实际上这很显然有 $O(\dfrac n B)$ 条，那么把这类链特殊处理一下，然后把被 $\le 1$ 个 $>B$ 的点影响的链挂在对应的点上用带删除的堆维护，取 $B=\Theta(\sqrt{\dfrac n {\log n}})$，时间复杂度是 $O(n\sqrt{n\log n})$ 的。

---

## 作者：Colinxu2020 (赞：2)

提供一个非常好写的 $O(n \log n)$ 做法，讲题的时候听到的qwq

首先考虑没有修改怎么做，直接 DFS 每一个颜色的边构成的子图，如果这个子图是一个链就加入这个颜色的边的权值和，否则什么也不做即可。

考虑怎么修改，研究一下把某一个点 block 掉会发生什么，发现受影响有两类，第一类是经过这个点父亲和自己的链，第二类是不经过这个点父亲，但是经过这个点的链。对于第一类是简单地，因为可以直接把这个链的贡献去掉，对于第二类，所有受影响的链的 LCA 一定都是这个点，于是考虑将所有链的贡献挂到 LCA 上，在每个 LCA 上开一个优先队列，那么总答案就是所有优先队列堆顶的最大值，显然这是等价的。

这样的话，对于操作 1，只需要对于父亲边所对应的链，找到他的 LCA，去掉这条链的贡献，在取消自己的贡献即可，对于操作 2 就是反过来，求 LCA 可以直接 dfs 的时候找深度最小的。为了维护堆顶最大值再额外开一个总的优先队列即可。

因为要在堆里删除元素考虑使用 `pb_ds` 的优先队列即可，复杂度为 $O(n \log n)$。

注意有很多 corner case，如果父亲边对应的链已经被删掉就不要重复删了，直接打个删除标记，如果恢复也不要直接恢复，而是判定删除标记为 $0$ 再恢复，否则只是减少一个删除标记，如果父亲所在的颜色本身不构成链也不要删除/恢复。但样例还是很强的，这几个基本样例都 hack 掉了。

参考代码：

```cpp
#include<iostream>
#include<vector>
#include<map>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;

#define ll long long
const int maxn=2e5+10;
int n,qasks,cnt[maxn],start[maxn],top[maxn],fa[maxn],dep[maxn],rmcnt[maxn]; ll len[maxn];
map<int,vector<pair<int,int>>> grp[maxn];
__gnu_pbds::priority_queue<int> q[maxn];
__gnu_pbds::priority_queue<int>::point_iterator link[maxn],link_col[maxn];

void init_dfs(int cur, int pa){
    for(auto it=grp[cur].begin();it!=grp[cur].end();it++){
        auto& vec=it->second; int col=it->first;
        for(auto x:vec)if(x.first!=pa)dep[x.first]=dep[cur]+1,fa[x.first]=col,init_dfs(x.first,cur);
    }
}
bool dfs(int cur, int col, int pa){
    bool flag=grp[cur][col].size()<=2; if(dep[cur]<dep[top[col]])top[col]=cur;
    for(auto edge:grp[cur][col])if(edge.first!=pa)cnt[col]--,len[col]+=edge.second,flag&=dfs(edge.first,col,cur);
    return flag;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>qasks;
    dep[0]=1e9;
    for(int i=1;i<n;i++){
        int u,v,w,c; cin>>u>>v>>w>>c;
        grp[u][c].push_back({v,w});
        grp[v][c].push_back({u,w});
        cnt[c]++; start[c]=u;
    }
    init_dfs(1,0);
    for(int i=1;i<=n;i++)if(start[i]){
        if(dfs(start[i], i, 0)&&!cnt[i]){
            link_col[i]=q[top[i]].push(len[i]);
        }
    }
    for(int i=1;i<=n;i++)q[i].push(0),link[i]=q[0].push(q[i].top());
    q[0].push(0);
    while(qasks--){
        int op,x; cin>>op>>x;
        if(op==0){
            q[0].erase(link[x]); link[x]=nullptr;
            if(link_col[fa[x]]!=nullptr){
                if(link[top[fa[x]]]!=nullptr)q[0].erase(link[top[fa[x]]]);
                if(!rmcnt[fa[x]])q[top[fa[x]]].erase(link_col[fa[x]]);
                rmcnt[fa[x]]++;
                if(link[top[fa[x]]]!=nullptr)link[top[fa[x]]]=q[0].push(q[top[fa[x]]].top());
            }
        }else{
            link[x]=q[0].push(q[x].top());
            if(link[top[fa[x]]]!=nullptr)q[0].erase(link[top[fa[x]]]);
            rmcnt[fa[x]]--;
            if(!rmcnt[fa[x]])link_col[fa[x]]=q[top[fa[x]]].push(len[fa[x]]);
            if(link[top[fa[x]]]!=nullptr)link[top[fa[x]]]=q[0].push(q[top[fa[x]]].top());
        }
        cout<<q[0].top()<<'\n';
    }
}
```

---

## 作者：yllcm (赞：2)

大家好，这里是更更更更劣且更更更更难写的 $\mathcal{O}(n\log^2 n)$ 做法。

首先我们把不是一条链的颜色去掉，并不妨假设每条链两端 $u,v$ 均满足 $\text{lca}(u,v)\neq u$ 且 $\text{lca}(u,v)\neq v$。如果有这种情况，可以在链顶往下连一个新节点，颜色为链的颜色，边权为 $0$。

我们直接动态 DP。设 $f_u$ 表示 $u$ 子树里面与 $(u,fa_u)$ 颜色相同的链的长度（长度要加上父亲边），$g_u$ 表示完全在 $u$ 子树内的链的答案。考虑转移：

* $f_u$ 的转移：直接找到 $u$ 子树内唯一的一条与父亲边颜色相同的边，然后直接加上 $(u,fa_u)$ 的权值，如果没有颜色相同的边就直接赋值。
* $g_u$ 的转移。
  * 链的 $\text{lca}$ 不在 $u$，直接拿儿子的 $g$ 转移。
  * 链的 $\text{lca}$ 在 $u$，对于每个儿子找到与之颜色对应的另一个儿子即可。

转移是简单的，关键在于如何将其套用到动态 DP 的模型上。动态 DP 的思想在于，将轻子树信息合并成一个关于重子树信息的映射变换，然后利用线段树快速处理映射的符合运算。此处的映射不能简单地用矩阵刻画，考虑如何刻画它。

* 关于 $f_u$ 的变换：若 $u$ 子树内没有颜色相同的边，$f_u$ 的变换是形如 $f_u\gets a_0$ 的赋值变换。否则，$f_u$ 的变换是形如 $f_u\gets f_{\text{hson}_u}+a_0$ 的加法变换。
* 关于 $g_u$ 的变换，贡献分为：
  * $\text{lca}$ 不在 $u$，变换相当于 $\text{chkmax}$：$g_u\gets \max(g_u,g_v)$。
  * $\text{lca}$ 在 $u$，且两条链和重儿子无关，变换仍然是 $\text{chkmax}$：$g_u\gets\max(g_u,f_x+f_y)$。
  * 两条链其中一条是重儿子，变换是关于 $f_{\text{hson}_u}$ 的 $\text{chkmax}$ 变换：$g_u\gets \max(g_u,f_{\text{hson}_u}+f_x)$。

简单地说，一个变换实际上是四元组 $(type,a_0,a_1,a_2)$：

* $type=0$，$f_u\gets a_0$，$g_u\gets \max(g_u,f_{\text{hson}_u}+a_1,a_2)$。
* $type=1$，$f_u\gets f_{\text{hson}_u}+a_0$，$g_u\gets \max(g_u,f_{\text{hson}_u}+a_1,a_2)$。

接下来只要处理映射的复合，关于这个，相信大家都会合并线段树的标记，类似讨论即可。如果不太熟悉可以阅读[线段树维护分治信息略解-rqy](https://_rqy.blog.uoj.ac/blog/8105)。

至此我们构建起了动态 DP 的模型，采用动态 DP 的方法维护即可。至于维护每个点的标记，拿两个 multiset 维护相同颜色的节点对的权值和即可。时间复杂度 $\mathcal{O}(n\log^2 n)$。如果使用 GBT 也许能 1log，但是我比较懒，就不写了。

[code](https://codeforc.es/problemset/submission/1787/211785144)

![](https://cdn.luogu.com.cn/upload/image_hosting/rdrou1g2.png)

我不相信能有比这还慢的做法（

---

## 作者：Nuisdete (赞：1)

首先处理出每种颜色是否合法以及路径长度等信息，我这里写了个丑陋的并查集，建议换个写法。

然后就是维护哪些颜色路径是好的。

考虑将每条颜色路径挂到两个路径端点的 $\operatorname{lca}$ 上，然后我们考虑修改一个点的状态时会影响哪些颜色路径。

1. 多条挂在这个点的颜色路径；
2. 向上穿过这个点的颜色路径（只有一条）；

这里可以使用类似点分树的维护方式，对每个点维护一个 `multiset` 存储挂在这个点的颜色路径长度，同时维护一个全局 `multiset` 存储每个点的 `multiset` 的最大值。

第一种路径直接在全局 `multiset` 修改即可，第二种路径在 $\operatorname{lca}$ 的 `multiset` 里修改一下，然后更新全局 `multiset` 也就行了。

```cpp
# include <cstdio>
# include <vector>
# include <set>
# include <map>
# include <iterator>
# include <algorithm>

const int MAXN = 2e5 + 5;

int n, m;
int col[MAXN << 1], top[MAXN << 1];

bool ava[MAXN << 1];

int dep[MAXN << 1], lth[MAXN << 1];

struct E {
	int k, dis, col;
	
	E(int K = 0, int D = 0, int C = 0) {
		k = K, dis = D, col = C;
	}
};

std::vector<E> G[MAXN << 1];

int cnt[MAXN << 1];

std::vector<int> vec[MAXN << 1];

void dfs(int u, int father) {
	for (auto [k, d, c] : G[u]) {
		++cnt[c];
		if (cnt[c] > 2) ava[c] = false;
	}
	for (auto [k, d, c] : G[u]) --cnt[c];
	bool flg = true;
	for (auto [k, d, c] : G[u]) if (k != father) {
		dep[k] = dep[u] + d;
		if (c == col[u]) flg = false;
		if (!top[c]) top[c] = u; 
		col[k] = c, dfs(k, u);
	}
	if (flg) vec[ col[u] ].push_back(u);
}

struct DSU {
	std::map<int, int> fa;
	
	int find(int x) {
		return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
	}
	
	void unite(int x, int y) {
		if (!fa[x]) fa[x] = x;
		if (!fa[y]) fa[y] = y;
		fa[find(x)] = find(y);
	}
} dsu[MAXN << 1];

std::multiset<int> mx, val[MAXN << 1];

bool die[MAXN << 1];

int num[MAXN << 1];

void distroy(int u) {
	die[u] = true;
	if (!val[u].empty()) mx.erase(mx.find(*prev(val[u].end())));
	if (u == 1 || !ava[ col[u] ]) return;
	if (!die[ top[ col[u] ] ] && !val[ top[ col[u] ] ].empty())
		mx.erase(mx.find(*prev(val[ top[ col[u] ] ].end())));
		
	if (num[ col[u] ] == n) val[ top[ col[u] ] ].erase(val[ top[ col[u] ] ].find(lth[ col[u] ]));
	--num[ col[u] ];
	if (!die[ top[ col[u] ] ] && !val[ top[ col[u] ] ].empty())
		mx.insert(*prev(val[ top[ col[u] ] ].end()));
}

void rebuild(int u) {
	die[u] = false;
	if (!val[u].empty()) mx.insert(*prev(val[u].end()));
	if (u == 1 || !ava[ col[u] ]) return;
	if (!die[ top[ col[u] ] ] && !val[ top[ col[u] ] ].empty())
		mx.erase(mx.find(*prev(val[ top[ col[u] ] ].end())));
		
	if (num[ col[u] ] == n - 1) val[ top[ col[u] ] ].insert(lth[ col[u] ]);
	++num[ col[u] ];
	if (!die[ top[ col[u] ] ] && !val[ top[ col[u] ] ].empty())
		mx.insert(*prev(val[ top[ col[u] ] ].end()));
}

int main() {
	
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; ++i) {
		int x, y, d, c;
		scanf("%d %d %d %d", &x, &y, &d, &c);
		G[x].emplace_back(y, d, c), G[y].emplace_back(x, d, c);
		dsu[c].unite(x, y);
		vec[c].push_back(x), vec[c].push_back(y);
	}
	for (int i = 1; i <= n; ++i) ava[i] = true;
	for (int i = 1; i <= n; ++i) {
		int tot = 0;
		std::sort(vec[i].begin(), vec[i].end());
		vec[i].erase(unique(vec[i].begin(), vec[i].end()), vec[i].end());
		for (int k : vec[i]) if (dsu[i].fa[k] == k) ++tot;
		if (tot > 1) ava[i] = false; std::vector<int>().swap(vec[i]);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) {
		if (vec[i].size() < 2) vec[i].push_back(top[i]);
		if (vec[i].size() == 2) {
			lth[i] = dep[ vec[i][0] ] + dep[ vec[i][1] ] - 2 * dep[ top[i] ];
			if (ava[i]) val[ top[i] ].insert(lth[i]);
		}
	}
	for (int i = 1; i <= n; ++i) {
		num[i] = n;
		if (!val[i].empty()) mx.insert(*prev(val[i].end()));
	}
	for (int i = 1; i <= m; ++i) {
		int op, x;
		scanf("%d %d", &op, &x);
		switch (op) {
			case 0 : distroy(x); break;
			case 1 : rebuild(x); break;
			default : puts(">_<");
		}
		printf("%d\n", mx.empty() ? 0 : *prev(mx.end()));
	}
	
	return 0;
}
```

---

## 作者：namelessgugugu (赞：1)

大家好啊，这里又是更劣且更难写的 $O(n \log ^ 2 n)$ 做法。

#### 题意

一颗 $n$ 个点的树，边有长度且有颜色，一条好的路径定义为一条仅包含一种颜色 $c$，且包含了所有颜色为 $c$ 的边的简单路径，同时要求路径上所有点未被摧毁。

$m$ 次操作，每次摧毁或修复一个点，修改后求所有好的路径的长度最大值。

#### 题解

首先一种颜色至多对应一条可能好的路径，这是容易求的。简单思考发现这些路径好像只能在点上相交，而且整体上由于树的限制不会呈现过于复杂的结构。考虑建一个新图，第 $i$ 个点对应原图上颜色为 $i$ 的好路径。如果一个点被颜色为 $a_1, a_2 ,\dots , a_k$ 的好路径经过，那么连接 $(a_1, a_2), (a_2, a_3), \dots, (a_{k - 1}, a_k)$，那么最后整张新图也必然是一棵树（或森林），否则可以推出原图有环。

此时考虑一个点的摧毁与修复带来了什么，相当于把 $a_1 - a_2 - a_3 - \dots - a_k$ 这条链给摧毁或修复了一次。令 $v_i$ 表示一个点被摧毁的次数，那么一条链还活着等价于 $v_i = 0$，摧毁和修复操作对应链上权值加 $1$ 或减 $1$。

注意到 $v_i \geqslant 0$，因此我们实际上是可以通过线段树直接维护这种信息的。类似扫描线求矩形面积并，在线段树节点 $x$ 中令 $mn_x$ 表示对应区间的 $v_i$ 最小值，$mx_x$ 表示在那些 $v_i$ 取最小值的地方路径长度的最大值，再开一个 $lz_x$ 用来实现区间加就可以了。

通过重链剖分把链拆成 $O(\log n)$ 段区间即可做到 $O(n \log ^ 2 n)$ 的复杂度，应用全局平衡二叉树或者 LCT 应该能做到 $O(n \log n)$，但是树剖已经够难写了所以不会有人尝试的吧。

#### 代码


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
typedef long long ll;
const int N = 200005;
int n, m;
struct edge
{
    int u, v, w, c;
} e[N];
int deg[N];
struct Edge
{
    int to, nxt;
} E[N << 1];
int head[N], tot;
inline void add(int f, int t)
{
    E[++tot] = {t, head[f]}, head[f] = tot;
    return;
}
bool vis[N];
int st[N], col[N];
ll val[N];
int fa[N], dep[N], siz[N], son[N], top[N], dfn[N], rks[N], tt;
void dfs1(int x, int from)
{
    dep[x] = dep[fa[x] = from] + 1, siz[x] = 1;
    for (int i = head[x];i;i = E[i].nxt)
    {
        int y = E[i].to;
        if(y == from)
            continue;
        dfs1(y, x), siz[x] += siz[y], son[x] = siz[son[x]] >= siz[y] ? son[x] : y;
    }
    return;
}
void dfs2(int x, int tp)
{
    rks[dfn[x] = ++tt] = x, top[x] = tp;
    if(son[x])
        dfs2(son[x], tp);
    for (int i = head[x];i;i = E[i].nxt)
    {
        int y = E[i].to;
        if(y == son[x] || y == fa[x])
            continue;
        dfs2(y, y);
    }
    return;
}
struct SgT
{
    struct node
    {
        int mn, lz;
        ll mx;
    } t[N << 2];
    inline int ls(int x)
    {
        return x << 1;
    }
    inline int rs(int x)
    {
        return x << 1 | 1;
    }
    inline void pushup(int x)
    {
        t[x].mn = std::min(t[ls(x)].mn, t[rs(x)].mn);
        if(t[ls(x)].mn == t[rs(x)].mn)
            t[x].mx = std::max(t[ls(x)].mx, t[rs(x)].mx);
        else
            t[x].mx = t[ls(x)].mn < t[rs(x)].mn ? t[ls(x)].mx : t[rs(x)].mx;
        return;
    }
    inline void modify(int x, int v)
    {
        t[x].mn += v, t[x].lz += v;
        return;
    }
    inline void pushdown(int x)
    {
        if(t[x].lz)
            modify(ls(x), t[x].lz), modify(rs(x), t[x].lz), t[x].lz = 0;
        return;
    }
    void build(int x, int l, int r)
    {
        if(l == r)
            return t[x].mn = 0, t[x].mx = val[rks[l]], void(0);
        int mid = (l + r) >> 1;
        build(ls(x), l, mid), build(rs(x), mid + 1, r), pushup(x);
        return;
    }
    void update(int x, int l, int r, int ql, int qr, int v)
    {
        if(l >= ql && r <= qr)
            return modify(x, v), void(0);
        pushdown(x);
        int mid = (l + r) >> 1;
        if(ql <= mid)
            update(ls(x), l, mid, ql, qr, v);
        if(qr > mid)
            update(rs(x), mid + 1, r, ql, qr, v);
        pushup(x);
        return;
    }
    inline ll query(void)
    {
        return t[1].mn == 0 ? t[1].mx : 0ll;
    }
} T;
inline void update(int x, int y, int v)
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        T.update(1, 1, tt, dfn[top[x]], dfn[x], v), x = fa[top[x]];
    }
    if(dep[x] < dep[y])
        std::swap(x, y);
    T.update(1, 1, tt, dfn[y], dfn[x], v);
    return;
}
int main(void)
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n;++i)
        scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].w, &e[i].c), add(e[i].u, e[i].v), add(e[i].v, e[i].u);
    std::sort(e + 1, e + n, [](edge a, edge b) -> bool
              { return a.c < b.c; });
    dfs1(1, 0);
    memset(head, 0, sizeof(head)), tot = 0;
    for (int l = 1, r; l < n; l = r) // 这是在找出好的路径
    {
        r = l;
        while(r < n && e[r].c == e[l].c)
            ++deg[e[r].u], ++deg[e[r].v], val[e[l].c] += e[r].w, ++r;
        bool flag = 1;
        std::vector<int> vec;
        for (int i = l; i < r; ++i)
        {
            if(deg[e[i].u] == 1)
                vec.push_back(e[i].u);
            if(deg[e[i].v] == 1)
                vec.push_back(e[i].v);
            if (vec.size() > 2u)
            {
                flag = 0;
                break;
            }
        }
        for (int i = l; i < r;++i)
            --deg[e[i].u], --deg[e[i].v];
        if (flag)
        {
            int rt = e[l].c, u = vec[0], v = vec[1];
            vis[rt] = 1;
            while (1)
            {
                if (dep[u] < dep[v])
                    std::swap(u, v);
                if (col[u])
                    add(rt, col[u]), add(col[u], rt), col[u] = rt;
                else
                    st[u] = col[u] = rt;
                if(u == v)
                    break;
                u = fa[u];
            }
        }
    }
    memset(fa, 0, sizeof(fa));
    memset(son, 0, sizeof(son));
    for (int i = 1; i <= n;++i)
        if(vis[i] && !fa[i])
            dfs1(i, 0), dfs2(i, i);
    if(tt == 0)
    {
        for (int i = 1; i <= m;++i)
            puts("0");
        return 0;
    }
    T.build(1, 1, tt);
    for (int i = 1, op, x; i <= m;++i)
    {
        scanf("%d%d", &op, &x);
        if(st[x])
            update(st[x], col[x], op ? -1 : 1);
        printf("%lld\n", T.query());
    }
    return 0;
}
```

说句闲话，这份巨长的代码实际上我只调了不到两分钟就一遍过了。

---

## 作者：sunkuangzheng (赞：1)

$\textbf{CF1787G}$

> - 给定一棵 $n$ 个点的树，每条边有颜色和权值，点有黑色和白色，初始时都是黑色。定义一条路径是好的，当且仅当路径上所有点都是黑色，且所有边的颜色相同（设均为 $c$），且所有颜色 $c$ 的边都要在路径上。
> - $q$ 次修改，每次翻转一个点的颜色，问好路径里边权和的最大值。
> - $1 \le n,q \le 2 \cdot 10^5$，时间限制 $2.0$ 秒。

一个显然的观察是，一个颜色最多贡献一条路径，且这个颜色的边需要构成一条链。

一个不太显然的观察是，把合法颜色路径挂在 LCA 上，把一个点 $u$ 反转颜色，只会影响 $1$ 个 LCA 不等于 $u$ 的路径，其余路径的 LCA 都是 $u$。

到这里我们就有思路了：把路径按照 LCA 的编号排序，这样每次操作影响的范围是一个点和一个区间。我们设每个颜色白点数量为 $-b_i$，则问题可以改写成：

- 区间给 $b_i$ 加减 $1$，且保证 $b_i \le 0$。
- 全局查 $b_i = 0$ 的 $i$ 里 $a_i$ 的 $\max$。

我不知道这个问题能不能线段树做，考虑分块。块内按照 $b_i$ 排序，考虑区间修改：

- 散块直接暴力改，改完后重新排序。
- 整块区间打 tag，显然区间加不影响顺序关系。

由于是全局查询，涉及的询问都是整块。

块内元素是有序的，于是在每个块里容易二分出 $\ge 0$ 的区间，其应该是一段前缀，维护块内前缀 $\max a_i$ 即可。

- 修改复杂度：$\mathcal O(B \log n + \dfrac{n}{B})$。
- 查询复杂度：$\mathcal O(\dfrac{n \log n}{B})$。

取 $B = \sqrt n$ 即可得到 $\mathcal O(q\sqrt n \log n )$。

实测过不了，我们尝试优化复杂度：

- 注意到我们的散块修改是拎出来若干位置，加减 $1$ 后再塞回去 sort。实际上我们得到了两个有序数组，将它们归并排序即可去掉修改时的 $\log$。
- 查询时我们二分 $\ge 0$ 的前缀，实际上由于 $0$ 一定是最大值，我们只需要对每个块维护最大值延续到哪里即可。这样可以去掉查询时的 $\log$。

最终复杂度 $\mathcal O(q \sqrt n)$，[可以通过](https://codeforces.com/contest/1787/submission/257019365)。

---

## 作者：_SeeleVollerei_ (赞：1)

题目中关于路径的限制特别强。容易发现有至多 $n$ 条可能合法的路径。

我们不妨考虑对每个点所在的合法路径存起来，这样看上去是一个二分图，看上去不太可做。所以考虑从原图是个树入手，看看有没有什么好的性质。

我们将所有的合法路径建一个点，原本的点都建一个点，然后每个点与所有它所在的路径对应的点连边。

然后会发现这个二分图实际上也是一个树/森林。因为如果这不是一棵树/森林，相当于有环的出现，那么原图上也一定会有个环。这就矛盾了。

对于每棵树，将一个原树上的点作为根，那么能保证每个路径只有唯一的一个父亲。我们用每个父亲搞一个支持单点修改和整体修改的数据结构去管辖它的儿子。这样，所有路径都能被唯一的点所管辖。

修改的时候，考虑对一个点管辖的儿子整体加减，对父亲的父亲单点修改即可。然后拿一个堆或者 multiset 维护每个点管辖的可用的儿子的最大值即可。

https://codeforces.com/contest/1787/submission/192148553

---

## 作者：不知名用户 (赞：0)

有一个 $n$ 个节点的树，每条边有边权和颜色。一条路径被称为“好的”当且仅当它满足以下条件：1. 所有边颜色相同 2.这条路径包含了所有颜色为该颜色的边 3. 所有节点均未摧毁。然后给你 $q$ 次操作，每次会摧毁/修复一个节点，然后你要输出最长的好的路径，若没有输出 $0$。$n,q\le2\cdot10^5$。

一种颜色的边要么构成链要么不构成链（也有可能不存在，不过不重要）。只有前者可能构成好的路径，以下提到的颜色均指这种颜色。于是有一个暴力做法：对于每个颜色，开个桶维护有多少个点被摧毁了。用 `set` 维护所有未被摧毁的颜色的边权和（以下称为全局 `set`）。对于一次修改，只用把与这个点相连的有用的边的桶的值 +1/-1，再在全局 `set` 上插入/删除。但是一个菊花不断修改花心就 TLE 了。

如果把树看成有根树，每条链就会有个链顶。如果不修改链顶就只用修改父边的颜色的桶。对于链顶需要使用另一种方法。

在链顶单独开一个 `set`，功能和全局 `set` 类似，只是把所有颜色改成以这个点为链顶的颜色。全局 `set` 存链顶 `set` 的最大值，不是原来的所有未被摧毁的最大值。在修改一个点时只用在全局 `set` 删除或插入这个点的 `set` 的最大值，同时在父边的对应颜色的链顶的 `set` 上修改（注意这个修改也会造成全局 `set` 的变化）。为了减少细节可以在所有 `set` 预先插入 $0$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
multiset<ll,greater<ll> >ans,x[N];
struct node{int x,y,z;};
vector<pair<int,int> > ed[N];
vector<int>g[N],G[N];
int dep[N], lc[N], cx, ld, lu, on[N], fc[N], ch[N];
ll cw[N];

void era(multiset<ll,greater<ll> >&S, int x){S.erase(S.find(x));}
void getdep(int x, int f){dep[x]=dep[f]+1;for(auto j:g[x])if(j!=f)getdep(j,x);}
void dfs(int x, int f)
{
	cx--;
	if(dep[x]<ld) ld = dep[x], lu = x;
	if(G[x].size()>2) cx = 1e9;
	for(auto j:G[x]) if(j!=f) dfs(j,x);
}

int main()
{
	int n, q, i;
	scanf("%d%d", &n, &q);
	for(i=1;i<n;i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		g[a].push_back(b), g[b].push_back(a);
		ed[d].emplace_back(a,b), cw[d] += c;
	}
	getdep(1,0);
	for(i=1;i<=n;i++) if((int)ed[i].size()>0)
	{
		for(auto j:ed[i])
		{
			int a = j.first, b = j.second;
			G[a].emplace_back(b), G[b].emplace_back(a);
		}
		cx = ed[i].size() + 1, ld = 1e9, dfs(ed[i][0].first,0);
		if(cx==0) lc[i] = lu;
		for(auto j:ed[i])
		{
			int a = j.first, b = j.second;
			G[a].clear(), G[b].clear();
			if(cx==0) if(dep[a]<dep[b]) fc[b] = i;else fc[a] = i;
		}
		if(lc[i]) x[lc[i]].insert(cw[i]);
	}
	ans.insert(0);
	for(i=1;i<=n;i++) x[i].insert(0), ans.insert(*x[i].begin());
	while(q--)
	{
		int p, a;scanf("%d%d", &p, &a);
		if(p==0)
		{
			if(fc[a])
			{
				if(!ch[fc[a]])
				{
					int b = lc[fc[a]];
					if(!on[b]) era(ans,*x[b].begin());
					era(x[b],cw[fc[a]]);
					if(!on[b]) ans.insert(*x[b].begin());
				}
				ch[fc[a]]++;
			}
			on[a] = 1, era(ans,*x[a].begin());
		}
		else
		{
			if(fc[a])
			{
				if(ch[fc[a]]==1)
				{
					int b = lc[fc[a]];
					if(!on[b]) era(ans,*x[b].begin());
					x[b].insert(cw[fc[a]]);
					if(!on[b]) ans.insert(*x[b].begin());
				}
				ch[fc[a]]--;
			}
			on[a] = 0, ans.insert(*x[a].begin());
		}
		printf("%d\n", *ans.begin());
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

首先，有关“好路径”的定义告诉我们，每条边至多包含在一条“好”路径中，因此不管三七二十一先预处理出所有的“好”路径。

思考这个问题棘手在哪里，因为你修改一个点时，最劣情况可能会导致 $O(n)$ 个好路径的状态发生改变。但是对于这种“邻域修改”的问题其实是有不少套路可言的。一种是将每个点的儿子分为重儿子和轻儿子两类，类似于 NOI2021 D1T1，但是这题不牵扯到路径邻域的修改，所以使用这个方法显得有点累赘。还有一种是类似于 CF487E 那样将与一个点相邻的边分为父亲边和儿子边处理。对于这道题而言，每次修改至多导致一条 LCA 不是 $x$ 的路径发生变化，这是本题的突破口。

这样思路就出来了。记 $cnt_i$ 表示颜色为 $i$ 的路径上有多少个除 LCA 之外的点在集合中，那么加入一个点的时候，设 $c$ 为其与父亲节点之间的边的颜色，那么我们先令 $cnt_c$ 加一，如果 $cnt_c$ 等于路径上点数减一就往这条路径 LCA 的集合内加入这条路径的权值，同时加入一个点时对 $x$ 集合内的最大值取 $\max$。外面再额外维护所有集合的 $\max$ 组成的集合即可做到单 $\log$。

然而刚才脑瘫了写了线段树分治，但还是过了（

```cpp
const int MAXN=2e5;
const int LOG_N=18;
int n,qu,hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],val[MAXN*2+5],col[MAXN*2+5],ec;
void adde(int u,int v,int w,int c){to[++ec]=v;val[ec]=w;col[ec]=c;nxt[ec]=hd[u];hd[u]=ec;}
map<int,int>deg[MAXN+5];
int pt[MAXN+5][2],dep[MAXN+5],fa_col[MAXN+5];ll dis[MAXN+5];
int len[MAXN+5],lc[MAXN+5],fa[MAXN+5][LOG_N+2];ll sumw[MAXN+5];
void dfs(int x,int f){
	fa[x][0]=f;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e],z=val[e],c=col[e];if(y==f)continue;
		fa_col[y]=c;dep[y]=dep[x]+1;dis[y]=dis[x]+z;dfs(y,x);
	}
}
int getlca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=LOG_N;~i;i--)if(dep[x]-(1<<i)>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=LOG_N;~i;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int cnt[MAXN+5],pre[MAXN+5];
multiset<ll>st[MAXN+5];ll mx;
struct node{int l,r;vector<int>v;}s[MAXN*4+5];
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r)return;
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
}
void insert(int k,int l,int r,int x){
	if(l>r)return;if(l<=s[k].l&&s[k].r<=r)return s[k].v.pb(x),void();
	int mid=s[k].l+s[k].r>>1;
	if(r<=mid)insert(k<<1,l,r,x);
	else if(l>mid)insert(k<<1|1,l,r,x);
	else insert(k<<1,l,mid,x),insert(k<<1|1,mid+1,r,x);
}
bool in[MAXN+5];
void ins(int x){
	in[x]=1;
	if(!st[x].empty())chkmax(mx,*st[x].rbegin());
	if(x!=1){
		int c=fa_col[x];
		if(lc[c]){
			cnt[c]++;
			if(cnt[c]==len[c]){
				if(in[lc[c]])chkmax(mx,sumw[c]);
				st[lc[c]].insert(sumw[c]);
			}
		}
	}
}
void del(int x){
	in[x]=0;
	if(x!=1){
		int c=fa_col[x];
		if(lc[c]){
			if(cnt[c]==len[c])st[lc[c]].erase(st[lc[c]].find(sumw[c]));
			cnt[c]--;
		}
	}
}
void iterate(int k){
	ll tmpmx=mx;for(int x:s[k].v)ins(x);
	if(s[k].l==s[k].r)printf("%lld\n",mx);
	else iterate(k<<1),iterate(k<<1|1);
	for(int x:s[k].v)del(x);mx=tmpmx;
}
int main(){
	scanf("%d%d",&n,&qu);
	for(int i=1,u,v,w,c;i<n;i++){
		scanf("%d%d%d%d",&u,&v,&w,&c);
		adde(u,v,w,c);adde(v,u,w,c);deg[c][u]++;deg[c][v]++;
	}
	for(int i=1;i<=n;i++){
		for(pii p:deg[i]){
			if(p.se>=3)pt[i][0]=pt[i][1]=-1;
			else if(p.se==1){
				if(!pt[i][0])pt[i][0]=p.fi;
				else if(!pt[i][1])pt[i][1]=p.fi;
				else pt[i][0]=pt[i][1]=-1;
			}
		}
	}
	dfs(1,0);
	for(int i=1;i<=LOG_N;i++)for(int j=1;j<=n;j++)
		fa[j][i]=fa[fa[j][i-1]][i-1];
	for(int i=1;i<=n;i++)if(pt[i][0]>0){
		lc[i]=getlca(pt[i][0],pt[i][1]);
		len[i]=dep[pt[i][0]]+dep[pt[i][1]]-(dep[lc[i]]<<1);
		sumw[i]=dis[pt[i][0]]+dis[pt[i][1]]-(dis[lc[i]]<<1);
	}
//	for(int i=1;i<=n;i++)printf("color %d %d %d %d %lld\n",i,pt[i][0],pt[i][1],len[i],sumw[i]);
	build(1,1,qu);
	for(int i=1;i<=n;i++)pre[i]=in[i]=1;
	for(int i=1,opt,x;i<=qu;i++){
		scanf("%d%d",&opt,&x);
		if(opt==0)insert(1,pre[x],i-1,x),in[x]=0;
		else pre[x]=i,in[x]=1;
	}
	for(int i=1;i<=n;i++)if(in[i])insert(1,pre[i],qu,i);
	memset(in,0,sizeof(in));iterate(1);
	return 0;
}
```



---

## 作者：happybob (赞：0)

首先容易发现有用的颜色必然构成一条链，先将这些链拉出来。

对于修改，暴力做法是直接将所有包含这个点的有用链修改，但这样复杂度显然不对。

考虑一个套路是，将有用链分为两类，一类是 $\operatorname{LCA}$ 为 $u$ 的，另一类是通过 $u$ 和 $u$ 父亲的链。对于第二类可以直接对这条链修改，第一类可以预先将有用链按照 $\operatorname{LCA}$ 排序，这样每次修改的是一个区间。

问题转化为，区间加减 $1$，求全局为 $0$ 的位置的点权最大值。但是注意到这个和扫描线里的线段树类似，任何时刻最小值都不会 $<0$，于是维护最小值和最小值对应的点权最大值即可。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <array>
using namespace std;

using ll = long long;

constexpr int N = 2e5 + 5;

struct Edge
{
	int to, w, c;
	Edge() = default;
	Edge(int to, int w, int c) : to(to), w(w), c(c) {}
};

array<vector<Edge>, N> G;

int n, q;

array<int, N> facol;

array<set<pair<int, int>>, N> arr;
array<array<int, 20>, N> fa;
array<int, N> dep, id;
int idx;
array<ll, N> dis;

array<vector<int>, N> col;

void dfs(int u, int f)
{
	id[u] = ++idx;
	fa[u][0] = f;
	dep[u] = dep[f] + 1;
	for (auto& [j, w, c] : G[u])
	{
		if (j == f) continue;
		dis[j] = dis[u] + w;
		facol[j] = c;
		dfs(j, u);
	}
}

inline int LCA(int u, int v)
{
	if (u == v) return u;
	if (dep[u] < dep[v]) swap(u, v);
	int k = dep[u] - dep[v], c = 0;
	while (k)
	{
		if (k & 1) u = fa[u][c];
		k >>= 1;
		c++;
	}
	if (u == v) return u;
	for (int i = 19; i >= 0; i--) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

inline ll getdis(int x, int y)
{
	return dis[x] + dis[y] - 2ll * dis[LCA(x, y)];
}

inline bool inpath(int u, int v, int z)
{
	return getdis(u, v) == getdis(u, z) + getdis(z, v);
}

struct Path
{
	int u, v, c, lc;
	ll len;
	Path() = default;
	Path(int u, int v, int c, int lc, ll len) : u(u), v(v), c(c), lc(lc), len(len) {}
};

vector<Path> vec;
array<Path, N> rc;
array<int, N> L, R;

class SegmentTree
{
public:
	struct Node
	{
		int l, r, minn;
		ll mind;
		int tag;
	};
	array<Node, N << 2> tr;
	void pushup(int u)
	{
		tr[u].minn = min(tr[u << 1].minn, tr[u << 1 | 1].minn);
		tr[u].mind = 0;
		if (tr[u].minn == tr[u << 1].minn) tr[u].mind = tr[u << 1].mind;
		if (tr[u].minn == tr[u << 1 | 1].minn) tr[u].mind = max(tr[u].mind, tr[u << 1 | 1].mind);
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, 0, vec[r].len, 0 };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		pushup(u);
	}
	void pushtag(int u, int c)
	{
		tr[u].minn += c;
		tr[u].tag += c;
	}
	void pushdown(int u)
	{
		if (tr[u].tag)
		{
			pushtag(u << 1, tr[u].tag);
			pushtag(u << 1 | 1, tr[u].tag);
			tr[u].tag = 0;
		}
	}
	void update(int u, int l, int r, int c)
	{
		if (tr[u].l >= l and tr[u].r <= r)
		{
			pushtag(u, c);
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update(u << 1, l, r, c);
		if (r > mid) update(u << 1 | 1, l, r, c);
		pushup(u);
	}
}sgt;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i < n; i++)
	{
		int u, v, w, c;
		cin >> u >> v >> w >> c;
		arr[u].emplace(v, c), arr[v].emplace(u, c);
		G[u].emplace_back(v, w, c);
		G[v].emplace_back(u, w, c);
		col[c].emplace_back(u), col[c].emplace_back(v);
	}
	dfs(1, 0);
	for (int j = 1; j < 20; j++)
	{
		for (int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
	}
	for (int i = 1; i <= n; i++)
	{
		sort(col[i].begin(), col[i].end(), [&](const int& x, const int& y) {return id[x] < id[y]; });
		col[i].erase(unique(col[i].begin(), col[i].end()), col[i].end());
	}
	for (int i = 1; i <= n; i++)
	{
		rc[i] = Path(-1, -1, -1, -1, -1);
		if (col[i].empty()) continue;
		if (col[i].size() == 1)
		{
			vec.emplace_back(col[i][0], col[i][0], i, col[i][0], 0);
		}
		else
		{
			int u = col[i][0], v = u;
			bool tag = 1;
			for (int j = 1; j < col[i].size(); j++)
			{
				int nu = col[i][j];
				if (!arr[nu].count(make_pair(u, i)) && !arr[nu].count(make_pair(v, i)))
				{
					tag = 0;
					break;
				}
				if (inpath(u, nu, v)) v = nu;
				else if (inpath(v, nu, u)) u = nu;
				else
				{
					tag = 0;
					break;
				}
			}
			if (tag)
			{
				vec.emplace_back(u, v, i, LCA(u, v), getdis(u, v));
			}
		}
	}
	sort(vec.begin(), vec.end(), [&](const auto& x, const auto& y) {return x.lc < y.lc; });
	for (int i = 0; i < vec.size(); i++)
	{
		rc[vec[i].c] = Path(vec[i].u, vec[i].v, i, i, i);
	}
	L.fill(-1), R.fill(-1);
	for (int i = 0; i < vec.size(); i++)
	{
		R[vec[i].lc] = i;
	}
	for (int i = vec.size() - 1; i >= 0; i--) L[vec[i].lc] = i;
	if (vec.size()) sgt.build(1, 0, vec.size() - 1);
	while (q--)
	{
		int op, x;
		cin >> op >> x;
		if (op == 0)
		{
			int l = L[x], r = R[x];
			if (l != -1) sgt.update(1, l, r, 1);
			if (x != 1)
			{
				int c = facol[x];
				if (rc[c].c != -1)
				{
					sgt.update(1, rc[c].lc, rc[c].lc, 1);
				}
			}
		}
		else
		{
			int l = L[x], r = R[x];
			if (l != -1) sgt.update(1, l, r, -1);
			if (x != 1)
			{
				int c = facol[x];
				if (rc[c].c != -1)
				{
					sgt.update(1, rc[c].lc, rc[c].lc, -1);
				}
			}
		}
		if (sgt.tr[1].minn != 0) cout << "0\n";
		else cout << sgt.tr[1].mind << "\n";
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

很难不发现总共最多有 $O(n)$ 种不同的简单路径，因为每种颜色对应至多一个简单路径。

考虑改变一个节点的状态会影响哪些简单路径。暴力修改显然不行。考虑将影响的简单路径分成两类，一种是向上的，一种是以这个点为两个端点 LCA 的。将第二类的链挂在这个点上，然后按顺序将每个点上的链排开，用线段树维护。这样的好处是可以每个点操作都可以区间+一个点打 tag。

总复杂度 $O(n\log n)$，线段树维护是平凡的。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
vector<pair<int,int>> vc[200005];
int ind[200005],outd[200005],f[200005][20],dep[200005],cnt;
void dfs0(int now,int fa){
	f[now][0]=fa;
	dep[now]=dep[fa]+1;
	ind[now]=++cnt;
	for(int i=1;i<=19;i++) f[now][i]=f[f[now][i-1]][i-1];
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		dfs0(v.first,now);
	}
	outd[now]=cnt;
}
int lca(int u,int v){
	if(dep[u]>dep[v]) swap(u,v);
	for(int i=19;i>=0;i--) if(dep[f[v][i]]>=dep[u]) v=f[v][i];
	if(u==v) return u;
	for(int i=19;i>=0;i--) if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	return f[u][0];
}
bool check(int i,int j,int k){
	return ind[i]<=ind[j]&&ind[j]<=ind[k]&&outd[k]<=outd[j]&&outd[j]<=outd[i];
}
pair<int,int> merge(pair<int,int> x,pair<int,int> y){
	if(x.first==-1||y.first==-1) return make_pair(-1,-1);
	if(x.first==0) return y;
	if(y.first==0) return x;
	{
		int l=lca(x.first,x.second);
		if((check(l,y.first,x.first)|check(l,y.first,x.second))&(check(l,y.second,x.first)|check(l,y.second,x.second))) return x;
	}
	{
		int l=lca(y.first,y.second);
		if((check(l,x.first,y.first)|check(l,x.first,y.second))&(check(l,x.second,y.first)|check(l,x.second,y.second))) return y;
	}
	{
		int l=lca(x.first,y.first);
		if((check(l,x.second,x.first)|check(l,x.second,y.first))&(check(l,y.second,x.first)|check(l,y.second,y.first))) return make_pair(x.first,y.first);
	}
	{
		int l=lca(x.first,y.second);
		if((check(l,x.second,x.first)|check(l,x.second,y.second))&(check(l,y.first,x.first)|check(l,y.first,y.second))) return make_pair(x.first,y.second);
	}
	{
		int l=lca(x.second,y.first);
		if((check(l,x.first,x.second)|check(l,x.first,y.first))&(check(l,y.second,x.second)|check(l,y.second,y.first))) return make_pair(x.second,y.first);
	}
	{
		int l=lca(x.second,y.second);
		if((check(l,x.first,x.second)|check(l,x.first,y.second))&(check(l,y.first,x.second)|check(l,y.first,y.second))) return make_pair(x.second,y.second);
	}
	return make_pair(-1,-1);
}
vector<pair<pair<int,int>,int>> col[200005];
bool okcol[200005];
int siz[200005],stpos[200005],edpos[200005];
vector<int> bel[200005];
int rval[200005],tot,upcol[200005],rnm[200005];
void dfs1(int now,int fa){
	stpos[now]=tot+1;
	for(auto v:bel[now]){
		tot++;
		rval[tot]=v;
		rnm[v]=tot;
	}
	edpos[now]=tot;
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		upcol[v.first]=v.second;
		dfs1(v.first,now);
	}
}
struct node{
	int maxv,maxq,lzt;
};
node merge(node x,node y){
	x.lzt=y.lzt=0;
	if(x.maxv>y.maxv) return x;
	if(x.maxv<y.maxv) return y;
	if(x.maxq>y.maxq) return x;
	return y;
}
struct sgt{
	node f[1000005];
	void pushdown(int i){
		f[i*2].maxv+=f[i].lzt;
		f[i*2+1].maxv+=f[i].lzt;
		f[i*2].lzt+=f[i].lzt;
		f[i*2+1].lzt+=f[i].lzt;
		f[i].lzt=0;
	}
	void build(int i,int l,int r){
		if(l==r){
			f[i].maxv=0;
			f[i].maxq=siz[rval[l]];
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i].lzt+=cg;
			f[i].maxv+=cg;
			// if(l==r&&l==2){
			// 	cout<<f[i].maxv<<" "<<cg<<"\n";
			// }
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	node qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		pushdown(i);
		if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		return merge(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n,q; cin>>n>>q;
	for(int i=1;i<n;i++){
		int u,v,w,c; cin>>u>>v>>w>>c;
		vc[u].push_back(make_pair(v,c)),vc[v].push_back(make_pair(u,c));
		col[c].push_back(make_pair(make_pair(u,v),w));
	}
	dfs0(1,0);
	for(int i=1;i<=n;i++){
		auto ori=make_pair(0,0);
		for(auto v:col[i]){
			ori=merge(ori,v.first);
			siz[i]+=v.second;
		}
		if(ori.first>0){
			int dist=dep[ori.first]+dep[ori.second]-2*dep[lca(ori.first,ori.second)];
			if(dist!=col[i].size()) continue;
			okcol[i]=1;
			bel[lca(ori.first,ori.second)].push_back(i);
		}
	}
	dfs1(1,0);
	if(tot==0){
		while(q--){
			cout<<0<<"\n";
		}
		return 0;
	}
	tree.build(1,1,tot);
	// cout<<upcol[2]<<" "<<rnm[upcol[2]]<<"\n";
	while(q--){
		int p,x; cin>>p>>x;
		if(p==0){
			if(stpos[x]<=edpos[x]) tree.change(1,1,tot,stpos[x],edpos[x],-1);
			if(rnm[upcol[x]]) tree.change(1,1,tot,rnm[upcol[x]],rnm[upcol[x]],-1);
		}
		else{
			if(stpos[x]<=edpos[x]) tree.change(1,1,tot,stpos[x],edpos[x],1);
			if(rnm[upcol[x]]) tree.change(1,1,tot,rnm[upcol[x]],rnm[upcol[x]],1);
		}
		auto qd=tree.qry(1,1,tot,1,tot);
		if(qd.maxv==0) cout<<qd.maxq<<"\n";
		else cout<<0<<"\n";
	}
	return 0;
}
```

---

