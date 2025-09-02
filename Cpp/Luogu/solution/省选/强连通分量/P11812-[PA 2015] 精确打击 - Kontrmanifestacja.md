# [PA 2015] 精确打击 / Kontrmanifestacja

## 题目背景


译自 [PA 2015](https://sio2.mimuw.edu.pl/c/pa-2015-1/p/) R5.


## 题目描述

给定一张 $n$ 个点 $m$ 条边的**有向图**。有向图无重边自环。

对于这张图的经过边数量 $\ge 1$ 的回路，求回路上点集的交。


## 说明/提示

- $2\le n\le 5\times 10^5$；
- $1\le m\le 10^6$；
- 图无重边自环。

## 样例 #1

### 输入

```
4 5
1 2
2 3
3 1
3 4
4 2```

### 输出

```
2
2 3```

## 样例 #2

### 输入

```
3 2
1 2
2 3```

### 输出

```
NIE```

# 题解

## 作者：Purslane (赞：7)

# Solution

如果整张图已经是 DAG 了，输出 `NIE`。

那么一个点在所有回路上的充要条件是，删掉他之后图是一张 DAG。不过如果你做了这样的转化，你很大概率是写不出一些正经做法的。原因在于，DAG 的结构太过复杂，没有非常优秀的处理方法。

我们可以找到一个环。显然答案只能是这个环上的节点。

如果删掉这个环之后不是 DAG，那么至少有两个无交环，答案是空集。

否则，所有可能的回路都形如：从环上的一个点出发，走外层 DAG，回到环上的另一个点。

稍微画个图：

![](https://s21.ax1x.com/2025/02/25/pE1UOxg.png)

加上环上两点 $S$ 和 $T$，存在一条路径满足，首尾分别是 $S$ 和 $T$，且中间**不经过环上任意元素**，则 $S\to T$ 在环上的路径中**除了 $S$ 和 $T$ 以外的节点都不会在回路的交上**。（注意，$S=T$ 可能发生，这代表有一个只经过 $S$ 的回路。）

如果能把所有的 $(S,T)$ 找出来，我们已经能找到一个必要条件了。

下面证明：如果一个点不会被任何一个类似的 $S \to T$ 覆盖，那么他是合法的。

这个实际上相当简单。因为此时任何一个回路，都不可能跨过该点，必须直接走过去。

假设环上的点编号是 $1$ 到 $k$。

对于 $S$ 而说，我们可以通过 DAG 上记忆化搜索求出最大的 $T$ 使得 $S \to T$ 路径存在，以及最小的 $T$ 使得 $S \to T$ 的路径存在。

如果 $T_{\max} \ge S$，显然让 $(S,T_{\max})$ 中所有元素都不合法即可。

如果 $T_{\min} \le S$，则设 $T_0$ 为 $\le S$ 且能由 $S$ 到达的最大的节点，则 $(S,k] \cup [1,T_0)$ 都不合法。

可惜我们不太好找 $T_0$。不过把整张图反过来，通过 $T_0$ 找 $S$ 即可。（注：对于 $S$ 而言，如果 $T_{\min} \le S$，我们将 $(S,k]$ 记为不合法。而 $[1,T_0)$ 这一段通过枚举 $T_0$ 判断是否有 $S$ 进行判定。）

使用前缀和维护不合法的标记。

复杂度 $O(n+m)$（如果实现不好，会在输出的时候带 $\log$，只需要把最终的排序改成桶排就可以做到严格线性了。/tuu）

挺可爱的代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int n,m,vis[MAXN],pre[MAXN],ok[MAXN];
vector<int> G[MAXN],g[MAXN];
vector<int> cir;
void dfs(int u,int rt) {
	vis[u]=1;
	for(auto v:G[u]) {
		if(v==rt) {
			int tmp=u;
			while(tmp!=rt) cir.push_back(tmp),tmp=pre[tmp];
			cir.push_back(rt);
			reverse(cir.begin(),cir.end());
			return ;
		}
		if(vis[v]) continue ;
		pre[v]=u,dfs(v,rt);
		if(!cir.empty()) return ;
	}
	return ;
}
//=====tarjan=====
int dfn[MAXN],low[MAXN],in[MAXN],tot;
int col[MAXN],cs,ccnt[MAXN];
stack<int> st;
void tarjan(int u) {
	dfn[u]=low[u]=++tot,in[u]=1,st.push(u);	
	for(auto v:G[u]) if(!ok[v]) {
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(in[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		++cs,ccnt[cs]=0;
		while(1) {
			int v=st.top();
			st.pop();
			col[v]=cs,ccnt[cs]++,in[v]=0;
			if(u==v) return ;
		}
	}
	return ;
}
//====tarjan=====
int prex[MAXN];
void del(int l,int r) {
	l=max(1,l),r=min((int)cir.size(),r);
	if(l>r) return ;
	prex[l]++,prex[r+1]--;
	return ;
}
int mx[MAXN],mn[MAXN];
void solve1(int u) {
	if(vis[u]) return ;
	vis[u]=1;
	if(ok[u]) return mx[u]=mn[u]=ok[u],void();
	mx[u]=0,mn[u]=n+1;
	for(auto v:G[u]) {
		solve1(v);
		mx[u]=max(mx[u],mx[v]);
		mn[u]=min(mn[u],mn[v]);
	}
	return ;
}
void solve2(int u) {
	if(vis[u]) return ;
	vis[u]=1;
	if(ok[u]) return mx[u]=mn[u]=ok[u],void();
	mx[u]=0,mn[u]=n+1;
	for(auto v:g[u]) {
		solve2(v);
		mx[u]=max(mx[u],mx[v]);
		mn[u]=min(mn[u],mn[v]);
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,m) {int u,v;cin>>u>>v,G[u].push_back(v),g[v].push_back(u);}
	ffor(i,1,n) if(!dfn[i]) tarjan(i);
	int rt=-1;
	ffor(i,1,n) if(ccnt[col[i]]>1) rt=i;
	if(rt==-1) return cout<<"NIE",0;
	dfs(rt,rt);
	ffor(i,0,cir.size()-1) ok[cir[i]]=i+1;
	
	tot=0,cs=0;
	ffor(i,1,n) dfn[i]=low[i]=col[i]=0;
	ffor(i,1,n) if(!ok[i]&&!dfn[i]) tarjan(i);
	ffor(i,1,n) if(!ok[i]&&ccnt[col[i]]>1) return cout<<0<<'\n',0;
	

	memset(vis,0,sizeof(vis));
	for(auto id:cir) {
		for(auto to:G[id]) {
			solve1(to);
			if(mx[to]&&mx[to]>=ok[id]) del(ok[id]+1,mx[to]-1);
			if(mn[to]!=n+1&&mn[to]<=ok[id]) del(ok[id]+1,cir.size());
		}
	}
	memset(vis,0,sizeof(vis));
	for(auto id:cir) {
		for(auto to:g[id]) {
			solve2(to);
			if(mx[to]&&mx[to]>=ok[id]) del(1,ok[id]-1);
		}
	}
	
	ffor(i,1,cir.size()) prex[i]+=prex[i-1];
	vector<int> ans;
	ffor(i,1,cir.size()) if(!prex[i]) ans.push_back(cir[i-1]);
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<'\n';
	for(auto id:ans) cout<<id<<' ';
	return 0;
}
```

---

## 作者：pp_orange (赞：5)

原问题有一个等价问题：求这张图上所有点，使得删去这个点，图是一个 DAG。这可以看做原问题的第二定义，这个定义可以帮助我们找到一些性质和写对拍暴力。

(upd 20250301:补充一个忘写的定义) 我们称，如果一个点删去后原图成为 DAG，那么这个点就是 Dagless 的。

首先对原图缩点。缩完之后若干 SCC 之间构成一张 DAG，一个平凡的结论是如果一个 SCC 的大小大于等于 2 ，那么这个 SCC 内必然存在一个环。所以如果存在 2 个及以上的大 SCC，那就意味着存在不交的环，那么无解。所以必然只有一个 SCC，并且其他点对答案不影响，可以删去，后文钦定 “原图是 SCC” 这个条件。

考虑 dfs 树。我们发现所有返边的交必然是一个链，而且最后的答案一定在这个链上。后文我们将寻找一些必要条件，寻求更好的性质。

- $jump$ ：考虑每一个链上的点可以不经过链上任意一个点，可以到达的最深的链上的点是哪个。第 $i$ 个点的答案记作 $jump_i$（或者求最浅的可以达到这个点的，这两个用处差不多）。这一步和支配树中的 sdom 有异曲同工之妙。$i \to jump_i $ 在链上中间的每一个点都一定不可能成为答案，因为根据 $jump$ 数组的定义，他可以被绕过。请注意 $jump$ 数组就是为了**否定** Dagless 的，所以被定义为最深的可达点。$jump$ 数组可以容易的在 $O(n)$ 时间求得。

- $back$：如果一个链上的点可以不经过链上的任何一个点，到达一个返边，我们称之为“可返的”，记录在 $back_i$ 中。这个数组容易求得，考虑这个数组能帮助我们干什么。找到最浅的那个 $i$ 使得 $back_i=1$，那么显然，比这个更深的点一定不可能是 Dagless 的，因为如果一个点可以经过返边，那么这个返边一定可以不经过这个点的子树再走回这个点。所以这个点之后的点都不合法。

- 有了 $jump$ 和 $back$ 数组给出的**必要条件**，**我们断言**：剩下的可选点，如果 $x$ 合法，那么比 $x$ 更深的可选点也合法。原因在于，如果一个环经过了 $x$，那么他就必须经过紧接着的比他深的可选点。证明需要如下引理。

_引理：任何一个环至少要经过一个返祖边_

证明：考虑 dfs 树的后序遍历，容易发现只有返祖边会使得后序遍历的序数变大。

那么我们有了这个引理，联系 $back$ 数组，那么对于一个“可选点” $x$ 子树内仍然有“可选点” $y$ 的情况，上面那个点必然 $back_x = 0$，那么如果一个环必然经过他，则他的后继中还是需要有链上的点，因为根据 $back$ 的定义，不经过链上的点他无法来到一个返祖边。然后根据 $jump$ 的定义，他不可能在任何时候跨过 $y$，所以这个环必然经过 $y$。

那么答案具有单调性，二分检测即可，$O(n\log n)$

### 进一步的做法

能否做到线性？答案是能。

我们直接对最深的那个 "可选点" 检测一下，如果这个点不合法则这个图不是 Dagless 的。否则我们把这个点拆成 $2$ 个点 $S,T$，$S$ 继承所有出度，$T$ 继承所有入度。那么一个环对应这个 DAG 是一个从 $S\to T$ 的路径。一个 $O(n\alpha(n))$ 的做法是直接对这个图跑支配树，就能扫出来 $S\to T$ 的必经点（显然这就是支配树的定义），另一个更为巧妙的做法是把这张图看成无向的跑割点。因为 Dagless 的一定是割点，同时割点一定是 Dagless 的，所以是充要的。复杂度 $O(n)$。

### 简要流程汇总

考虑 dfs 树。

1、求返边交。

2、每个点跑最深的可达。

3、找最早的可以到返边。

4、对最后一个判定 Dagless。

5、把最后一个拆点跑无向图割点。

丑陋的赛时代码：

```cpp
/* Code by pp_orange */
//#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define m_p(a,b) make_pair(a,b)
#define pb push_back
#define ll long long
#define ull unsigned long long
#define ld long double
#define inf 0x7FFFFFFF
#define inff 9223372036854775807
#define rep(i,l,r) for(int i=l;i<r;++i)
#define repp(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r-1;i>=l;--i)
#define pper(i,r,l) for(int i=r;i>=l;--i)
#define pii pair<int,int>
#define fi first
#define se second
#define p_q priority_queue
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
#define lb(x) ((x)&-(x))
#define lg(x) (31^__builtin_clz(x))
#define vi vector<int>
#define vii vector<pii >
#define vT vector<T>
#define mm1 mint(1)
const int mod = 998244353;
//#define int ll
const int intsz = sizeof(int);
using namespace std;
inline int rd(){
	int x(0),f(1);char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while (isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
inline void out(int X){
	if(X<0) {X=~(X-1); putchar('-');}
	if(X>9) out(X/10);
	putchar(X%10+'0');
}
ll pw(ll x,int d){
	ll t = 1;
	for(;d;d>>=1,x=x*x%mod)if(d&1)t = t*x%mod;
	return t;
}
#define MAX 500005
vector<int> v[MAX];
vector<int> iv[MAX];
int jump[MAX],back[MAX];
int deg[MAX],ideg[MAX];
bool ban[MAX];
bool cyc[MAX];
int tot,pre[MAX],pa[MAX];
bool vis[MAX];
bool instk[MAX];
// backp[MAX];
int dfn[MAX],idfn[MAX];
int dfnt;
int banpre[MAX];
bool backp[MAX];
bool ans[MAX];
void dfs(int x){
	dfn[x] = ++dfnt;
	idfn[dfnt] = x;
	instk[x] = 1;
	for(auto to : v[x]){
		if(!dfn[to]){
			pa[to] = x;
			dfs(to);
			pre[x] += pre[to];
		}else if(instk[to]){
			backp[x] = 1;
			tot++;
			pre[x]++;
			pre[pa[to]]--;
		}
	}
	instk[x] = 0;
	return ;
}
int tong[MAX];
namespace Tarjan{
	int stk[MAX],tl;
	int dfn[MAX],dfnt,low[MAX];
	void tarjan(int x){
		dfn[x] = low[x] = ++dfnt;
		stk[++tl] = x;
		rep(o,0,2){
			vector<int> &G = o==0?v[x]:iv[x];
			for(auto to : G){
				if(!dfn[to]){
					tarjan(to);
					low[x] = min(low[x],low[to]);
					if(low[to]==dfn[x]){
						tong[x]++;
						while(stk[tl]!=x){
							tong[stk[tl]]++;
							tl--;
						}
					}
				}else{
					low[x] = min(low[x],dfn[to]);
				}
			}
		}
	}
}
signed main(){
	//freopen("F.in","r",stdin);
	//freopen("F.out","w",stdout);
	int n = rd();
	int m = rd();
	repp(i,1,m){
		int x = rd();
		int y = rd();
		v[x].pb(y);
		iv[y].pb(x);
		deg[y]++;
		ideg[x]++;
	}
	queue<int> q;
	int cnt = 0;
	repp(i,1,n)if(!deg[i])q.push(i);
	while(!q.empty()){
		int x = q.front();q.pop();
		ban[x] = 1;
		cnt++;
		for(auto to : v[x])if(!--deg[to])q.push(to);
	}
	if(cnt==n){
		cout<<"NIE"<<endl;
		return 0;
	}
	repp(i,1,n){
		if(ban[i])continue ;
		if(!ideg[i])q.push(i);
	}
	while(!q.empty()){
		int x = q.front();q.pop();
		ban[x] = 1;
		for(auto to : iv[x]){
			if(ban[to])continue;
			if(!--ideg[to])q.push(to);
		}
	}
	repp(i,1,n){
		if(ban[i]){
			v[i].clear();
			iv[i].clear();
		}
		vector<int> tmp;
		for(auto to : v[i])if(!ban[to])tmp.pb(to);
		v[i] = tmp;
		tmp.clear();
		for(auto to : iv[i])if(!ban[to])tmp.pb(to);
		iv[i] = tmp;
	}
	int st = -1;
	repp(i,1,n){
		if(!ban[i]){
			st = i;
			break ;
		}
	}
	assert(st!=-1);
	dfs(st);
	repp(i,1,n)cyc[i] = (tot==pre[i]);
	// repp(i,1,n)cout<<pa[i]<<' ';cout<<endl;
	// repp(i,1,n)cout<<cyc[i]<<' ';cout<<endl;

	memset(deg,0,sizeof(deg));
	int res = 0;
	repp(i,1,n){
		if(ban[i])continue ;
		if(cyc[i])continue ;
		res++;
		for(auto to : iv[i])if(!cyc[to])deg[to]++;
	}
	// repp(i,1,n)cout<<deg[i]<<' ';cout<<endl;
	// cout<<"res = "<<res<<endl;
	assert(q.empty());
	repp(i,1,n){
		if(ban[i])continue ;
		if(cyc[i])continue ;
		if(!deg[i])q.push(i);
	}
	// cout<<q.size()<<endl;
	vector<int> ord;
	while(!q.empty()){
		int x = q.front();q.pop();
		ord.pb(x);
		res--;
		for(auto to : iv[x]){
			if(cyc[to])continue ;
			if(!--deg[to])q.push(to);
		}
	}
	if(res){
		// cout<<"here"<<endl;
		cout<<0<<endl;
		cout<<endl;
		return 0;
	}
	vector<int> cycver;
	repp(i,1,n)if(cyc[i])cycver.pb(i);
	sort(all(cycver),[&](int x,int y){return dfn[x]>dfn[y];});
	for(auto x : cycver)jump[x] = dfn[x];
	repp(i,1,n){
		if(ban[i])continue ;
		if(!cyc[i]){
			back[i] = backp[i];
		}
	}
	// cout<<"? "<<back[3]<<endl;
	for(auto x : ord){
		for(auto to : v[x]){
			back[x] |= back[to];
			jump[x] = max(jump[x],jump[to]);
		}
	}
	for(auto x : cycver){
		for(auto to : v[x]){
			if(cyc[to]){
				if(pa[to]!=x)jump[x] = max(jump[x],dfn[to]);
				continue ;
			}
			back[x] |= back[to];
			jump[x] = max(jump[x],jump[to]);
		}
		int to = idfn[jump[x]];
		if(to!=x){
			banpre[x]--;
			banpre[pa[to]]++;
		}

	}
	for(auto x : cycver)banpre[pa[x]] += banpre[x];
	vector<int> recyc = cycver;
	reverse(all(recyc));
	back[pa[recyc[0]]] = 0;
	for(auto x : recyc)back[x] |= back[pa[x]];

	// repp(i,1,n)cout<<back[i]<<',';cout<<endl;
	// repp(i,1,n)cout<<banpre[i]<<',';cout<<endl;

	int g = -1;
	for(auto x : cycver){
		if(!back[pa[x]]&&banpre[x]==0){
			g = x;
			break ;
		}
	}
	// cout<<"g = "<<g<<endl;
	assert(g!=-1);
	if(g==-1){
		cout<<0<<endl;
		cout<<endl;
		return 0;
	}
	int S = 0,T = n+1;
	for(auto to : v[g])v[S].pb(to),iv[to].pb(S);;
	for(auto to : iv[g])v[to].pb(T),iv[T].pb(to);
	repp(i,1,n){
		v[i].erase(remove(all(v[i]),g),v[i].end());
		iv[i].erase(remove(all(iv[i]),g),iv[i].end());
	}
	// cout<<"g = "<<g<<endl;
	ban[g] = 1;
	memset(deg,0,sizeof(deg));
	res = 0;
	repp(i,0,n+1){
		if(ban[i])continue ;
		res++;
		for(auto to : v[i])deg[to]++;
	}
	// repp(i,0,n+1)cout<<deg[i]<<' ';cout<<endl;
	assert(q.empty());
	repp(i,0,n+1){
		if(ban[i])continue;
		if(deg[i]==0)q.push(i);
	}
	assert(q.size()==1);
	while(!q.empty()){
		int x = q.front();q.pop();
		res--;
		for(auto to : v[x])if(!--deg[to])q.push(to);
	}
	if(res){
		cout<<0<<endl;
		cout<<endl;
		return 0;
	}
	ans[g] = 1;
	Tarjan::tarjan(0);
	assert(Tarjan::tl==1);
	repp(i,1,n){
		if(ban[i])continue ;
		assert(tong[i]==1||tong[i]==2);
		if(tong[i]==2)ans[i] = 1;
	}
	int anscnt = 0;
	repp(i,1,n)anscnt += ans[i];
	cout<<anscnt<<endl;
	repp(i,1,n)if(ans[i])cout<<i<<' ';
	cout<<endl;
	return 0;
}
/*
g++ F.cpp -o F -g -std=c++14 -Wall -Wshadow -fsanitize=undefined,address && ./F < in.in
ulimit -s unlimited
*/
```

---

