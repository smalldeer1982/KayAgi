# 【MX-X3-T5】「RiOI-4」Countless J-Light Decomposition

## 题目背景

原题链接：<https://oier.team/problems/X3F>。

---

「如果，如果，如果真的可以是那样的话，就好了啊。」

回想起自己做出的一个个选择，泠珞有时会想，自己是否有过更好的机会。

但是既然一切已经如此了，除了前进，别无他法。

无论结果是如何，接受结果，习得教训，然后……去争取更美好的未来。

那么，现在应该做的就是，尽可能避免，之后会走到的最坏结果了吧。

「规避风险。脚踏实地。做最可能实现的选择。」

「一定是的。」

## 题目描述

给定一棵有根**带权**树，结点以 $1\sim n$ 编号。根结点编号为 $1$，边权均为正整数。

定义这棵树的**剖分**为对于每个结点，选择一些儿子（可以都选或都不选）为**重儿子**的方案。重儿子和其父亲的边称为**重边**。不是重边的边称为**轻边**。

定义一个剖分是 $\textbf{\textit{i--}}$**重的**，当且仅当对于每个结点，其重儿子数量不超过 $i$。

定义一个剖分是 $\textbf{\textit{j--}}$**轻的**，当且仅当对于每条从根（编号为 $1$ 的结点）出发的简单路径，其经过的轻边的边权和不超过 $j$。

对于 $i=0,1,\cdots,n-1$，请求出最小的 $j$，使得存在一个 $\textit{i--}$重的剖分是 $\textit{j--}$轻的。

## 说明/提示

**【样例解释 #1】**

对于样例 1，其中的树如下所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/tox3t3d4.png)

当 $i=0$ 时，只存在一种剖分，不存在任何重儿子或重边。一条从根出发经过轻边边权和最大的简单路径为 $1\textit{---}2\textit{---}4$，边权和为 $2$。

当 $i=1$ 时，可以采用如图所示的剖分，加粗结点（根除外）为重儿子。一条从根出发经过轻边边权和最大的简单路径为 $1\textit{---}2\textit{---}5$，经过轻边的边权和为 $1$。

当 $i\ge 2$ 时，可以令所有的非根结点为重儿子，因此任何从根出发经过最多轻边的简单路径只能经过 $0$ 条轻边，故轻边最大边权和为 $0$。

**【样例解释 #2】**

当 $i\ge 3$ 时，可以令所有的非根结点为重儿子，因此任何从根出发经过最多轻边的简单路径只能经过 $0$ 条轻边，故轻边最大边权和为 $0$。

当 $i=0,1,2$ 时，我有一个很简洁的解释，但是这里空白太小写不下。

**【数据范围】**

**本题开启捆绑测试。**

|子任务|分数|$n\le$|特殊性质|
|:-:|:-:|:-:|:-:|
|$1$|$10$|$10^3$||
|$2$|$18$|$4\times10^4$||
|$3$|$16$|$10^5$|$w_i\le100$|
|$4$|$21$|$10^5$|$w_i\le10^5$|
|$5$|$35$|$2\times10^5$||

对于 $100\%$ 的数据，$1\le n\le2\times10^5$，$1\le w_i\le 10^9$，保证输入是一棵树。

## 样例 #1

### 输入

```
5
1 2 1
1 3 1
2 4 1
2 5 1
```

### 输出

```
2 1 0 0 0```

## 样例 #2

### 输入

```
24
15 4 25
5 11 8
23 13 14
15 6 12
21 14 22
21 12 5
1 9 30
6 19 20
18 7 4
4 5 16
9 23 5
6 22 9
12 20 23
2 24 18
6 2 5
16 21 9
14 18 9
14 8 5
23 17 18
1 16 22
15 3 26
1 10 3
10 15 9```

### 输出

```
66 28 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ```

## 样例 #3

### 输入

```
10
4 8 407414868
3 9 875245582
10 3 548046335
2 8 163333320
7 5 320544242
5 3 504767824
6 7 431834202
9 4 639504669
9 1 968451452
```

### 输出

```
3100843302 639504669 0 0 0 0 0 0 0 0```

# 题解

## 作者：Register_int (赞：6)

鲜花：这题 idea 来自我真名的拼音首字母缩写。

首先考虑一个 $O(n^2)$ 的 dp。先枚举 $i$，然后设 $dp_u$ 为 $u$ 子树内的答案。对于 $u$ 的儿子 $v$，若定为重儿子则造成 $dp_v$ 的贡献，否则造成 $dp_v+w_{u,v}$ 的贡献。最优策略就是贪心地将 $dp_v+w_{u,v}$ 的前 $i$ 大设为重儿子，可以得到转移：

$$dp_u=\max((i+1)_{\text{th}}(\{dp_v+w_{u,v}\mid v\in\operatorname{son}(u)\}),\max_{v\in\operatorname{son}(u)}dp_v)$$

其中 $k_{\text{th}}(S)$ 表示集合 $S$ 内的第 $k$ 大。单次可用 `nth_element` 函数做到 $O(n)$。

可以发现一个事情：当 $i\ge d_u$ 时，我们可以把它的所有儿子都设为重儿子。所以这些 $u$ 本质上是没用的，只要保留所有 $d_u>i$ 的节点后建虚树，节点总数是 $O(\sum^{n-1}_i\sum_u[d_u>i])=O(\sum_ud_u)=O(n)$ 的。

但是转移复杂度还是错的啊？你先别急，我们每个节点开一个平衡树/可删对顶堆，维护其下所有 $dp_v+w_{v,u}$ 的值即可。新建虚树时暴力删除所有删掉的节点，进行 dp 时暴力加上所有有用的节点，修改次数是 $O(n)$ 的。

但是虚树是 10 级算法我不会啊？你先别急，我们可以在 $i=x-1$ 的虚树上面建 $i=x$ 的虚树，每次搜第一遍找出哪些点要用，再搜第二遍连父亲即可，时间复杂度是所有虚树的大小总和，也是 $O(n)$ 的。总复杂度带个 `priority_queue` 或者 `multiset` 的 log。

代码异常简单。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

struct heap {
	
	multiset<ll, greater<ll>> s1, s2;
	
	void insert(ll x) {
		if (s2.empty() || x >= *s2.begin()) s1.insert(x);
		else s2.insert(x);
	}
	
	void erase(ll x) {
		if (s1.find(x) != s1.end()) s1.erase(s1.find(x));
		else if (s2.find(x) != s2.end()) s2.erase(s2.find(x));
	}
	
	ll kth(int rk) {
		if (rk > s1.size() + s2.size()) return 0;
		for (; s1.size() < rk; s1.insert(*s2.begin()), s2.erase(s2.begin()));
		for (; s1.size() > rk; s2.insert(*--s1.end()), s1.erase(--s1.end()));
		return s2.empty() ? 0 : *s2.begin();
	}
	
} s[MAXN]; 

struct node {
	int v, w;
	node(int v = 0, int w = 0) : v(v), w(w) {}
}; vector<node> g[MAXN], tg[MAXN];

int k, d[MAXN]; ll dp[MAXN];

void dfs(int u, int f) {
	ll res = 0;
	for (node p : g[u]) {
		if (p.v == f) continue; dfs(p.v, u);
		res = max(res, dp[p.v]), s[u].insert(dp[p.v] + p.w);
	}
	dp[u] = max(res, s[u].kth(k));
}

int vis[MAXN], sz[MAXN];

void init(int u, int f) {
	int cnt = 0; sz[u] = vis[u] = (!f || d[u] > k);
	for (node p : g[u]) {
		if (p.v == f) continue; init(p.v, u);
		if (sz[p.v]) cnt++; sz[u] += sz[p.v];
	}
	if (!vis[u] && cnt > 1) vis[u] = 1, sz[u]++;
}

void build(int u, int f, int t, int w) {
	for (node p : g[u]) if (p.v != f) s[u].erase(dp[p.v] + p.w);
	for (node p : g[u]) if (p.v != f && !sz[p.v]) s[u].insert(p.w);
	if (vis[u]) { if (t) tg[t].emplace_back(u, w); t = u; }
	else for (node &p : g[u]) p.w = w;
	for (node p : g[u]) if (p.v != f && sz[p.v]) build(p.v, u, t, p.w);
	g[u] = tg[u], tg[u].clear();
}

int n;

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v, w; i < n; i++) {
		scanf("%d%d%d", &u, &v, &w);
		g[u].emplace_back(v, w), d[u]++;
		g[v].emplace_back(u, w), d[v]++;
	}
	for (int i = 2; i <= n; i++) d[i]--;
	dfs(1, 0), printf("%lld ", dp[1]);
	for (k = 1; k < n; k++) {
		init(1, 0), build(1, 0, 0, 0), dfs(1, 0);
		printf("%lld ", dp[1]);
	}
}
```

审核说还存在一个长剖做法，但是我不会长剖，有会的同学可以写一下谢谢喵。

赛时被骂说这题跟 TECHNOPOLIS 2085 太卡常了，一看写的不是直接搜而是 10 级算法，令人忍俊不禁。

---

## 作者：drowsylve (赞：4)

平衡树优化 dp，我找你找的好苦啊 /tt。

形式化体面：对于每个点，可以选择删掉 $k$ 条连向子树的边，求从根节点到所有叶子节点的权值和的最大值。分别回答 $k=[0,n-1]$ 时的答案。

设 $f_u$ 为 $u$ 子树中的答案，不难发现删掉 $f_v+w$ 前 $k$ 大的 $w$ 是优的，取第 $k+1$ 大就行了，容易得到

$$ f_u= \max_{v \in son_u }(f_v) $$
$$ f_u= \max (f_u,(k+1)_{th} \{f_v+w\}) $$

发现如果 $k+1 \ge son_u$ 那这个点是没有意义的，相当于所有边都能删掉，继承子节点最大的就行了。于是尝试往虚树的角度考虑，每次树的大小和点的度数有关，其实是 $O(n)$ 级别的。

现在遍历树的复杂度是对的了。这里注意虚树上 dp 的时候考虑子节点 v，应该向上跳到原树中 u 的某个儿子，使得这个儿子是 v 的祖先，我们要考虑的也应该是这个儿子到 u 的边权 w。次过程不难用倍增实现。

此外，虚树中仍然可能有已经无意义的点，对于这些点，答案直接取虚树上子节点的 $\max$ 就行了。

但是瓶颈仍然在取第 $(k+1)$ 大？对每个节点开一个平衡树先维护所有的 $w$，考虑在虚树上如果某个儿子的子树中有虚树上的点，那么替换 $w$ 为 $f_v+w$，查询排名后还原即可，操作次数与虚树上的儿子个数有关，也是 $O(n)$ 级的。

实现无其他题解的聪明优化，无 pbds，纯虚树板子和 fhq 板子，朴实无华。


```cpp
bool M1;
#include<bits/stdc++.h>
using namespace std;
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<'\n'
#define look_time cerr<<(clock()-ST)*1.0/CLOCKS_PER_SEC<<'\n'
//#define int long long
//#define double long double
#define ll long long
#define db double
#define pb push_back
#define pii pair<int,int>
#define mkp make_pair
#define fr first
#define sc second
template<typename T> void ckmin(T &x,T y){x=min(x,y);}
template<typename T> void ckmax(T &x,T y){x=max(x,y);}
mt19937 rnd(time(0));
const int N=200005;
const int inf=1e9;
const int mod=1000000007;
int n;
int rt[N],tot;
struct Fhq{
	struct node{
		int ls,rs,w,siz;
		ll v;
	}c[N*10];
	int crt(ll v){
		tot++;
		c[tot].v=v;c[tot].w=rnd();c[tot].siz=1;
		return tot;
	}
	void pu(int p){
		c[p].siz=c[c[p].ls].siz+c[c[p].rs].siz+1;
	}
	void splt(int p,ll v,int &x,int &y){
		if(!p) return x=y=0,void();
		if(c[p].v<=v) x=p,splt(c[p].rs,v,c[p].rs,y);
		else y=p,splt(c[p].ls,v,x,c[p].ls);
		pu(p);
	}
	int mge(int x,int y){
		if(!x||!y) return x+y;
		if(c[x].w>c[y].w) return c[x].rs=mge(c[x].rs,y),pu(x),x;
		else return c[y].ls=mge(x,c[y].ls),pu(y),y;
	}
	void ins(int u,ll p){
		int x,y;
		splt(rt[u],p,x,y);
		rt[u]=mge(mge(x,crt(p)),y);
	}
	void era(int u,ll p){
		int x,y,z;
		splt(rt[u],p,x,z);
		splt(x,p-1,x,y);
		y=mge(c[y].ls,c[y].rs);
		rt[u]=mge(mge(x,y),z);
	}
	ll qryk(int p,int k){
		if(k<=c[c[p].ls].siz) return qryk(c[p].ls,k);
		else if(k==c[c[p].ls].siz+1) return c[p].v;
		else return qryk(c[p].rs,k-c[c[p].ls].siz-1);
	}
}trp;
int cnte,to[N<<1],nxt[N<<1],val[N<<1],head[N];
inline void add(int u,int v,int w){
	to[++cnte]=v;
	val[cnte]=w;
	nxt[cnte]=head[u];
	head[u]=cnte;
}
int dep[N],siz[N],son[N],fa[N][21],top[N],deg[N],up[N];
void dfs1(int u,int ft){
	int hson=-1;
	siz[u]=1;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i],w=val[i];
		if(v==ft) continue;
		deg[u]++;
		fa[v][0]=u,dep[v]=dep[u]+1,up[v]=w;
		trp.ins(u,w);
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>hson) son[u]=v,hson=siz[v];
	}
}
int dfn[N];
void dfs2(int u,int tp){
	top[u]=tp;
	dfn[u]=++dfn[0];
	if(son[u]) dfs2(son[u],tp);
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa[u][0]||v==son[u]) continue;
		dfs2(v,v);
	}
}
int glca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]][0];
	}
	if(dep[u]<dep[v]) swap(u,v);
	return v;
}
int gson(int v,int u){
	for(int i=19;i>=0;i--)
		if(dep[fa[v][i]]>dep[u]) v=fa[v][i];
	return v;
}
ll f[N];
int del[N],o[N],stk[N];
vector<int> E[N];
void dfs(int u,int k){
	f[u]=0;
	for(int v:E[u]) dfs(v,k);
	if(del[u]){
		for(int v:E[u]) ckmax(f[u],f[v]);
		return;
	}
	vector<int> vec;
	for(int v:E[u]){
		int su=gson(v,u);
		vec.pb(su);
		ckmax(f[u],f[v]);
		trp.era(u,up[su]);
		trp.ins(u,f[v]+up[su]);
	}
	ckmax(f[u],trp.qryk(rt[u],deg[u]-k));
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i],su=vec[i];
		trp.ins(u,up[su]);
		trp.era(u,f[v]+up[su]);
	}
}
bool M2;
signed main(){
//	look_memory;
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;cin>>u>>v>>w;
		add(u,v,w),add(v,u,w);
	}
	dep[1]=1;
	dfs1(1,0);
	dfs2(1,1);
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
			fa[i][j]=fa[fa[i][j-1]][j-1];
	for(int i=1;i<=n;i++) o[i]=i;
	sort(o+1,o+1+n,[](int x,int y){return deg[x]<deg[y];});
	int p=1;
	for(int i=0;i<n;i++){
		while(p<=n && deg[o[p]]<=i) del[o[p]]=1,p++;
		if(p>n){cout<<"0 ";continue;}
		vector<int> pt;
		for(int j=p;j<=n;j++) pt.pb(o[j]);
		sort(pt.begin(),pt.end(),[](int x,int y){return dfn[x]<dfn[y];});
		int tp=1;
		stk[tp]=1;
		E[1].clear();
		for(int u:pt){
			if(u==1) continue;
			int lca=glca(u,stk[tp]);
			if(lca!=stk[tp]){
				while(dfn[lca]<dfn[stk[tp-1]]){
					E[stk[tp-1]].pb(stk[tp]);
					tp--;
				}
				if(lca!=stk[tp-1]){
					E[lca].clear();
					E[lca].pb(stk[tp]);
					stk[tp]=lca;
				}else{
					E[lca].pb(stk[tp]);
					tp--;
				}
			}
			E[u].clear();
			stk[++tp]=u;
		}
		for(int j=1;j<tp;j++) E[stk[j]].pb(stk[j+1]);
		dfs(1,i);
		cout<<f[1]<<" ";
	}
	return 0;
}
```

---

## 作者：yyyyxh (赞：4)

看题以为自己会了，写代码的时候发现有细节没考虑清楚，复杂度写挂了以为被卡常了，调用并查集函数还手残打错了，浪费大半个下午。NOI 之后属于越训越菜了 QwQ。

回到这个题，首先这个题当 $i$ 固定时做法是显然的，我们自底向上考虑，每次一定是 ban 掉连向当前最长链最大子树的 $i$ 条边。

发现只有当 $deg_i>x$ 时一个点才有考虑价值，而 $\sum_{x=0}^{n-1} \sum_u [deg_u>x]=\sum_u deg_u$ 是 $O(n)$ 级别的。建出虚树，然后每个点相当于删除若干个边权，加入若干个新边权，求第 $k$ 大。可以使用平衡树维护。做完了，复杂度 $O(n\log n)$。

如果我直接写虚树+平衡树，我就不用浪费这个下午了，但是我脑子一抽突然不想写十级算法。所以我们可以考虑用并查集维护当前还存在的 $deg_u>x$ 的点，再开一颗并查集，按照 dfs 序倒序遍历，每次删去在当前所有点子树的关键点，就可以实现跟虚树同样的功能且免去了常数大的递归，但是复杂度其实是带一个小 $\log n$ 或 $\alpha(n)$ 的。

平衡树也好难写，每次加入删除之后还要删除加入回去常数大飞，我们考虑用常数更小的算法。注意到题目对于一个已经准备好的数组形如删除若干个，加入若干个，然后还要回退回去。我们考虑经典的用堆维护第 $k$ 大，所以我们只需要开一个小根堆存储最大的 $k$ 个。

使用可删堆不够优美，因为还是要回退回去。我们考虑用两个堆结构拼成一个堆，把一个点下面的所有边排序一下，取后面若干个直接作为其中一个堆，由于原本存在的边只会被删，所以这里就是直接用一个指针就可以实现弹堆了。然后你就可以做到洛谷最快了。

我是在这里干些什么啊 \yun。

```cpp
#include <queue>
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>
#define fi first
#define se second
using namespace std;
int read(){ /* reading... */ }
const int N=200003;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,int> pli;
inline void chmx(ll &x,ll v){if(x<v) x=v;}
inline void chmn(ll &x,ll v){if(x>v) x=v;}
int n;
vector<pii> adj[N],tr[N],vec[N];
int dfn[N],o[N],sz[N],ps[N],num;
void dfs(int u,int fa){
	o[dfn[u]=++num]=u;
	sz[u]=1;
	for(auto [v,w]:adj[u]) if(v^fa){
		dfs(v,u);
		tr[u].emplace_back(w,v);
		vec[u].emplace_back(v,w);
		sz[u]+=sz[v];
	}
	sort(tr[u].begin(),tr[u].end());
	int tt=0;
	for(auto [w,v]:tr[u]) ps[v]=tt++;
}
int f[N],g[N];
bool del[N];
int rt(int x){
	if(f[x]==x) return x;
	return f[x]=rt(f[x]);
}
int go(int x){
	if(g[x]==x) return x;
	return g[x]=go(g[x]);
}
int stk[N],tp;
int que[N],tl;
ll dp[N],ed[N];
int main(){
	n=read();
	for(int i=1;i<n;++i){
		int u=read(),v=read(),w=read();
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
	}
	dfs(1,0);
	for(int i=n;i;--i) stk[++tp]=o[i];
	for(int i=1;i<=n+1;++i) f[i]=i;
	g[n+1]=n+1;
	int cnt=0;
	for(int x=0;x<n;++x){
		ll res=0;
		for(int i=1;i<=tp;++i){
			int u=stk[i];
			int ss=tr[u].size();
			if(ss<=x){f[dfn[u]]=dfn[u]+1;continue;}
			g[dfn[u]]=dfn[u];
			vector<pii> tmp;
			que[++tl]=u;
			int p=ss-x-1;
			ll tdp=0;
			priority_queue<ll,vector<ll>,greater<ll>> pq;
			for(auto [v,w]:vec[u]){
				ed[v]=0;bool fl=0;
				for(int t=go(rt(dfn[v]));t<dfn[v]+sz[v];t=go(t)) chmx(ed[v],dp[o[t]]+w),fl=1,g[t]=rt(t+1),chmx(tdp,dp[o[t]]);
				if(fl){
					tmp.emplace_back(v,w);
					del[v]=1;pq.emplace(ed[v]);
					if(ps[v]<p){
						if(!pq.empty()&&(p==ss||tr[u][p].fi>pq.top())) pq.pop();
						else ++p;
					}
					while(p<ss&&del[tr[u][p].se]) ++p;
				}
			}
			dp[u]=1e18;
			if(p<ss) chmn(dp[u],tr[u][p].fi);
			if(!pq.empty()) chmn(dp[u],pq.top());
			vec[u].swap(tmp);
			for(auto [v,w]:vec[u]) del[v]=0;
			chmx(dp[u],tdp);
			chmx(res,dp[u]);
		}
		tp=tl;tl=0;
		for(int i=1;i<=tp;++i) stk[i]=que[i];
		printf("%lld ",res);
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P11038)

**题目大意**

> 给定 $n$ 个点的有根带权树，对于 $k=0\sim n-1$，求出：每个节点可以选择 $\le k$ 条出边，将其边权变成 $0$，此时最小的最大深度。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

容易想到简单贪心，每次把最深的 $k$ 个儿子边权清零。

$f_u$ 表示 $u$ 子树的答案且 $v\in\mathrm{son}(u)$，那么 $f_u\gets \max f_v$ 并且用第 $k+1$ 大的 $f_v+w(u,v)$ 更新 $f_u$。

注意到如果一个点的度数 $\le k$，那么 $f_u\gets \max f_v$，这是简单的，因此我们实际上只要保留度数 $>k$ 的点，并在他们构成的虚树上 dp 即可。

容易发现一个点只会出现 $\mathrm{deg}(u)$ 次，因此总的出现次数为均摊 $\mathcal O(n)$，虚树大小之和也是均摊 $\mathcal O(n)$
。

但是对于一个度数 $\ge k$ 的点，他不在虚树上的儿子 $v$ 也是有贡献的，虽然 $f_v=0$，但我们要考虑 $w(u,v)$ 的贡献。

用平衡树维护 $u$ 的所有出边，如果 $v$ 是 $u$ 虚树上的儿子，那么在平衡树上暴力更新 $v$ 所在子树对应的权值，这部分同样是均摊 $\mathcal O(n)$ 次的，最后查询第 $k+1$ 大并还原即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define ll long long
using namespace std;
using namespace __gnu_pbds;
const int MAXN=2e5+5;
tree <array<ll,2>,null_type,greater<array<ll,2>>,rb_tree_tag,tree_order_statistics_node_update> Q[MAXN];
struct Edge { int v,w; };
vector <Edge> G[MAXN],T[MAXN];
int n,deg[MAXN],dfn[MAXN],dcnt,st[MAXN][20],val[MAXN];
int dep[MAXN],up[MAXN][20];
void dfs0(int u,int fz) {
	dep[u]=dep[fz]+1,dfn[u]=++dcnt,st[dcnt][0]=up[u][0]=fz;
	for(int k=1;k<20;++k) up[u][k]=up[up[u][k-1]][k-1];
	for(auto e:G[u]) if(e.v^fz) {
		Q[u].insert({e.w,e.v}),val[e.v]=e.w,dfs0(e.v,u),++deg[u];
	}
}
int gs(int x,int r) {
	for(int k=19;~k;--k) if(dep[up[x][k]]>dep[r]) x=up[x][k];
	return x;
}
int bit(int x) { return 1<<x; }
int cmp(int x,int y) { return dfn[x]<dfn[y]?x:y; }
int LCA(int x,int y) {
	if(x==y) return x;
	int l=min(dfn[x],dfn[y])+1,r=max(dfn[x],dfn[y]),k=__lg(r-l+1);
	return cmp(st[l][k],st[r-bit(k)+1][k]);
}
ll f[MAXN];
void dfs1(int u,int k) {
	f[u]=0;
	for(auto e:T[u]) dfs1(e.v,k),f[u]=max(f[u],f[e.v]);
	if(deg[u]<=k) return ;
	for(auto e:T[u]) Q[u].erase({val[e.w],e.w}),Q[u].insert({f[e.v]+val[e.w],e.w});
	f[u]=max(f[u],(*Q[u].find_by_order(k))[0]);
	for(auto e:T[u]) Q[u].erase({f[e.v]+val[e.w],e.w}),Q[u].insert({val[e.w],e.w});
}
void solve(vector<int>&id,int k) {
	sort(id.begin(),id.end(),[&](int x,int y){ return dfn[x]<dfn[y]; });
	for(int i=1,m=id.size();i<m;++i) id.push_back(LCA(id[i-1],id[i]));
	sort(id.begin(),id.end(),[&](int x,int y){ return dfn[x]<dfn[y]; });
	id.erase(unique(id.begin(),id.end()),id.end());
	for(int i=1,m=id.size();i<m;++i) {
		int x=LCA(id[i-1],id[i]);
		T[x].push_back({id[i],gs(id[i],x)});
	}
	dfs1(1,k);
	for(int u:id) T[u].clear();
}
vector <int> id[MAXN];
signed main() {
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;++i) {
		scanf("%d%d%d",&u,&v,&w);
		G[u].push_back({v,w}),G[v].push_back({u,w});
	}
	dfs0(1,0);
	for(int k=1;k<20;++k) for(int i=1;i+bit(k)-1<=n;++i) st[i][k]=cmp(st[i][k-1],st[i+bit(k-1)][k-1]);
	for(int i=0;i<n;++i) id[i].push_back(1);
	for(int u=2;u<=n;++u) for(int i=0;i<deg[u];++i) id[i].push_back(u);
	for(int i=0;i<n;++i) solve(id[i],i),printf("%lld ",f[1]);
	puts("");
	return 0;
}
```

---

## 作者：Jorisy (赞：0)

首先题目等价于每个节点可以选择不超过 $k$ 条边将边权清零，最小化以根为起点的路径的最大权值和。

下面为了方便记 $a_i$ 为边 $(i,\text{fa}_i)$ 的权值。

贪心地，对于节点 $i$，我们必然会将权值前 $k$ 大的儿子清零。

设 $f_i$ 为以 $i$ 为根的子树的答案，则首先有 $f_i=\max\limits_{j\in\text{son}_i}\{f_j\}$，然后还需要用第 $k+1$ 大的 $f_j+a_j$ 更新它。这些都是容易得到的。

时间复杂度 $O(n^2\log n)$，考虑优化。

很难不发现，如果 $|\text{son}_i|\le k$，则 $f_i=\max\limits_{j\in\text{son}_i}\{f_j\}$。那么这个 $i$ 就没有用了。

所以我们只要保留 $|\text{son}_i|>k$ 的节点，然后直接在虚树上用平衡树维护 dp 即可。另外注意这些节点不在虚树上的儿子 $x$ 也仍然具有儿子和父亲之间连的边的贡献 $a_x$。

每个节点会出现 $|\text{son}_i|$ 次，故总出现次数为 $O(n)$ 级别，所以时间复杂度是均摊 $O(n\log n)$ 的。

---

## 作者：ForgotMe (赞：0)

题意相当于将每个点的连出去的边最多将其中的 $i$ 条边边权变为 $0$后使从 $1$ 为起点的所有链的边权和的最大值最小。

$\mathcal{O}(n^2\log n)$ 是显然的。

设 $deg_u$ 表示点 $u$ 儿子个数。

设 $f_u$ 表示将在 $u$ 连出去的边中，其中的 $i$ 条边的边权变为 $0$ 后，以 $u$ 为起点的所有链的边权和的最大值的最小值。

转移是简单的，设 $S=\{f_v+w(u,v)|v\in son_u\}$，那么肯定是让 $S$ 中前 $i$ 大的数对应的 $w(u,v)$ 全部变为 $0$，总结一下 $f_u$ 就是 $S$ 中第 $i+1$ 大的值与 $\max_{v\in son_u}f_v$ 两者取 max 后的值。

考虑优化，注意到当 $i$ 逐渐变大时，满足 $deg_u\le i$ 的点 $u$ 连出去的边权和一定会变成 $0$，而且发现此时点 $u$ 没什么用了，相当于就是取儿子的所有 $f$ 值的 $\max$ 后上传。

考虑建出所有满足 $deg_u>i$ 的 $u$ 形成的虚树，注意到对于所有的 $i$，虚树大小的总和是 $n$，这是显然的。

此时这个虚树上由两类点组成，一类是满足 $deg_u>i$ 的点，称其为**关键点**，剩下的点称为**非关键点**。

对于非关键点来讲，其 $f$ 的转移是简单的，就是其虚树上所有儿子的 $f$ 值的 $\max$。

对于关键点来讲，首先其儿子组成包含关键点和非关键点，这些点对应 $f_v+w(u,v)$ 是好求出的，注意 $w(u,v)$ 需要通过倍增求出，因为在原树上两者可能只是祖先关系，而非父子关系。做完了吗？没有，注意到关键点在原树上可能还有一些在虚树上并未出现的儿子，这些儿子的贡献不能忽视（虽然其 $f$ 值都是 $0$，但是对应的 $w(u,v)$ 的并没有变成 $0$，也要包含在 $S$ 集合里）。

可是如果每次暴力把这些在虚树没有出现的儿子加进去，然后求 $S$ 集合的第 $i+1$ 的值，复杂度肯定爆炸了。

考虑先对每个点开一颗平衡树，将每个点连出去的边权形成的集合都丢到该点对应的平衡树里。求关键点的 $f$ 时就把在虚树上出现过的儿子对应的 $w(u,v)$ 从平衡树中删了，加入新的值，然后直接求第 $i+1$ 大即可，最后还原即可。

时间复杂度 $\mathcal{O}(n\log n)$。

实现偷了个懒，用的 pbds 中的平衡树。
```cpp
#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define LL long long
#define pp pair<LL,int>
#define mp make_pair 
#define ull unsigned long long
namespace IO{
	const int sz=1<<22;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
	//	return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
		return getchar();
	}
	template<class T> void gi(T& x){
		x=0; int f=1;char c=gc();
		if(c=='-')f=-1;
		for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
		x=x*f;
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> void pi(T x,char c='\n'){
		if(x<0)pc('-'),x=-x;
		if(x==0) pc('0'); int t=0;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
const int mod=998244353;
inline int add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
	return x-y<0?x-y+mod:x-y;
}
inline int mul(int x,int y){
	return 1ll*x*y%mod;
}
inline int qkpow(int a,int b){
	if(b<0)return 0;
	int ans=1,base=a%mod;
	while(b){
		if(b&1)ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int fac[1000005],inv[1000005],Invn[600005];
inline int binom(int n,int m){
	if(n<m||m<0)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
	inv[0]=1;
	inv[n]=qkpow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	Invn[0]=Invn[1]=1;
	for(int i=1;i<=200000;i++)Invn[i]=(LL)(mod-mod/i)*Invn[mod%i]%mod;
}
typedef tree<pp, null_type, less<pp>, rb_tree_tag, tree_order_statistics_node_update> Tree;
Tree Q[200005];
int f[400005][22],dep[200005],dew[200005];
struct node{
	int to,w;
}; 
int n,dfn[200005],cnt,son[200005],po[200005];
vector<node>G[200005];
vector<int>G2[200005]; 
int s[400005],len,len2;
LL dp[400005];
bool live[200005];
bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}
bool cmp2(int x,int y){
	return son[x]>son[y];
}
inline void dfs(int u,int ff){
	dfn[u]=++cnt;
	dep[u]=dep[ff]+1;
	for(int i=0;i<=19;i++)f[u][i+1]=f[f[u][i]][i];
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].to; 
		if(v==ff)continue;
		dew[v]=G[u][i].w;
		f[v][0]=u;
		Q[u].insert(pp(G[u][i].w,v));
		dfs(v,u);
		son[u]++;
	}
}
inline int LCA(int u,int v){
	if(u==v)return u;
	if(dep[u]<dep[v])swap(u,v);
	for(int i=20;i>=0;i--){
		if(dep[f[u][i]]>=dep[v])u=f[u][i];
		if(u==v)return u;
	} 
	for(int i=20;i>=0;i--){
		if(f[u][i]!=f[v][i]){
			u=f[u][i];
			v=f[v][i];
		}
	}
	return f[u][0];
} 
inline int queryw(int u,int v){
	for(int i=20;i>=0;i--)
		if(dep[f[v][i]]>dep[u])v=f[v][i];
	return v; 
}
inline void dfs2(int u,int K){
	for(auto v:G2[u])dfs2(v,K);
	if(!live[u]){
		for(auto v:G2[u])dp[u]=max(dp[u],dp[v]);
	}else{
		dp[u]=0;
		for(auto v:G2[u]){
			int x=queryw(u,v);
			dp[u]=max(dp[u],dp[v]);
			Q[u].erase(pp(dew[x],x));
			Q[u].insert(pp(dp[v]+dew[x],x));
		}
		dp[u]=max(dp[u],(*Q[u].find_by_order(son[u]-K-1)).first);
		for(auto v:G2[u]){
			int x=queryw(u,v);
			Q[u].erase(pp(dp[v]+dew[x],x));
			Q[u].insert(pp(dew[x],x));
		}
	}
	
}
inline void solve(int x){
	if(!len){
		pi(0,' ');
		return ;
	}
	len2=len;
	for(int i=1;i<=len2;i++)s[i]=po[i];
	sort(s+1,s+len2+1,cmp);
	int L=len2;
	for(int i=2;i<=L;i++)s[++len2]=LCA(s[i-1],s[i]);
	sort(s+1,s+len2+1,cmp);
	len2=unique(s+1,s+len2+1)-s-1;
	for(int i=1;i<=len2;i++)G2[s[i]].clear(),dp[s[i]]=0;
	for(int i=2;i<=len2;i++)G2[LCA(s[i-1],s[i])].push_back(s[i]);
	dfs2(s[1],x);
	pi(dp[s[1]],' ');
}
signed main(){
	gi(n);
	for(int i=1;i<=n;i++)live[i]=1;
	for(int i=1;i<n;i++){
		int u,v,w;
		gi(u),gi(v),gi(w);
		G[u].push_back(node{v,w});
		G[v].push_back(node{u,w});
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)po[i]=i;
	sort(po+1,po+n+1,cmp2);
	len=n;
	for(int i=0;i<n;i++){
		while(len>=1&&son[po[len]]==i)live[po[len]]=0,len--;
		solve(i);
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

题意：

给定一棵有根**带权**树，结点以 $1\sim n$ 编号。根结点编号为 $1$，边权均为正整数。

定义这棵树的**剖分**为对于每个结点，选择一些儿子（可以都选或都不选）为**重儿子**的方案。重儿子和其父亲的边称为**重边**。不是重边的边称为**轻边**。

定义一个剖分是 $i$ **重的**，当且仅当对于每个结点，其重儿子数量不超过 $i$。

定义一个剖分是 $j$ **轻的**，当且仅当对于每条从根（编号为 $1$ 的结点）出发的简单路径，其经过的轻边的边权和不超过 $j$。

对于 $i=0,1,\cdots,n-1$，请求出最小的 $j$，使得存在一个 $i$ 重的剖分是 $j$ 轻的。

$n \leq 2 \times 10^5$，$1 \leq w \leq 10^9$，$1$ 秒。

解法：

先考虑暴力，对于每个 $i$ 进行 DP，记 $f_u$ 表示在 $u$ 子树内的答案，转移直接从儿子里取 $i$ 大的转移即可。复杂度 $O(n^2 \log n)$ 或 $O(n^2)$。

进一步地，如果某个点儿子数量不超过 $i$，其 $f$ 值就是儿子的 $f$ 最大值。考虑对于每个 $i$，建立儿子个数大于 $i$ 的点的虚树，虚树总点数是 $O(\sum deg_i)=O(n)$ 量级的。转移时直接枚举儿子复杂度不对，但是使用平衡树维护每个点的所有儿子贡献即可。

---

