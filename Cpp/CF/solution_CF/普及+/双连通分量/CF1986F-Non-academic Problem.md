# Non-academic Problem

## 题目描述

给定一个连通的无向图，其顶点用从1到n的整数编号。你的任务是最小化在这个图中存在路径的顶点对(u,v)的数量，其中1≤u<v≤n。为了达到这个目标，你可以从图中移除恰好一条边。

现在请你找到可以移除一条边后，顶点对数量最小的值！

## 说明/提示

在第一组输入数据中，我们将移除单一边 (1,2)，并且唯一的顶点对 (1,2) 将变得不可达。

在第二组输入数据中，无论我们移除哪条边，所有顶点都将保持彼此可达。

在第四组输入数据中，初始的图看起来像这样（这里需要你画出图或者想象出图的结构）：

我们将移除边(3,4)，然后唯一的可达顶点对将是 (1,2)，(1,3)，(2,3)，(4,5)，(4,6)，(5,6)。

在第六组输入数据中，初始的图看起来像这样（同样需要你画出图或者想象出图的结构）：

移除边(2,4)后，图将变成这样（这里需要你想象出移除边后的图结构）。因此，将有21对可达顶点。

## 样例 #1

### 输入

```
6
2 1
1 2
3 3
1 2
2 3
1 3
5 5
1 2
1 3
3 4
4 5
5 3
6 7
1 2
1 3
2 3
3 4
4 5
4 6
5 6
5 5
1 2
1 3
2 3
2 4
3 5
10 12
1 2
1 3
2 3
2 4
4 5
5 6
6 7
7 4
3 8
8 9
9 10
10 8```

### 输出

```
0
3
4
6
6
21```

# 题解

## 作者：Louis_lxy (赞：7)

看到这题的第一眼就是割边，因为不可能断掉一个边双连通分量中的边，这样造不成贡献。

我们直接枚举割边，设此边为 $(u,v)$。那么减少点对数量为 $\max(size_u\times(n-size_u),size_v\times(n-size_v))$。

一个技巧是，我们无需枚举每条边，我们只需要在 dfs 时判断，如果有一条边与当前节点相连那么直接更新答案 $ans=\max(ans,size_x\times(n-size_x))$。

AC 记录：https://www.luogu.com.cn/record/168220686

---

## 作者：2huk (赞：4)

> - 给定 $n$ 个点 $m$ 条边的简单无向连通图。你需要删除一条边使得图中连通的顶点对 $1 \le u \le v \le n$ 最少。求这个最小值。
> - $n, m \le 10^5$。

显然删除一个 [e-dcc](https://www.luogu.com.cn/problem/P8436) 中的点一定是不优的，因为这样不会连通的顶点对不会减少。

所以将 e-dcc 缩点，每个点的点权为其代表的 e-dcc 中的点数。因为原图连通所以形成了一颗树。我们考虑删除一条树边带来的收益。

若令这条边为 $(u, v)$，那么原本连通现在不连通的顶点对数，应该是从 $u$ 出发不通过 $v$ 能到达的节点数，与从 $v$ 出发不通过 $u$ 能到达的节点数的乘积。预处理子树和即可。

```cpp
int n, m, a, b;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;  // 时间戳
int stk[N], top, dcc_cnt, id[N];
int ans[N], sz[N];
vector<int> g[N];

void clear(int n) {
	for (int i = 1; i <= n; ++ i ) {
		dfn[i] = low[i] = id[i] = ans[i] = sz[i] = 0;
		g[i].clear();
	}
	
	timestamp = 0;
	top = 0;
	idx = 0;
	dcc_cnt = 0;
	memset(h, -1, sizeof h);
}

void tarjan(int u, int from) {
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u;
    
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
        }
        else if (i != (from ^ 1)) low[u] = min(low[u], dfn[j]);
    }
    
    if (dfn[u] == low[u]) {
        ++ dcc_cnt;
        int y;
        do {
            y = stk[top -- ];
            id[y] = dcc_cnt;
            ans[dcc_cnt] ++ ;
        } while (y != u);
    }
}

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int fa) {
	sz[u] = ans[u];
	for (int v : g[u])
		if (v != fa) {
			dfs(v, u);
			sz[u] += sz[v];
		}
}

int solve() {
    cin >> n >> m;
    clear(n);
    
    for (int i = 1; i <= m; i ++ ) {
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    
    tarjan(1, 0);
    
    if (dcc_cnt == 1) return n * (n - 1) / 2;
    
    for (int i = 1; i <= n; ++ i ) {
    	for (int _ = h[i]; ~_; _ = ne[_]) {
    		int j = e[_];
    		if (id[i] != id[j]) {
    			int x = id[i], y = id[j];
    			g[x].push_back(y);
    			g[y].push_back(x);
    		}
    	}
    }
    
    for (int i = 1; i <= dcc_cnt; ++ i ) {
    	sort(g[i].begin(), g[i].end());
    	g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
    }
    
    dfs(1, -1);
    
    int res = 0;
    for (int i = 2; i <= dcc_cnt; ++ i ) {
    	res = max(res, sz[i] * (n - sz[i]));
    }
    
    return n * (n - 1) / 2 - res;
}
```

---

## 作者：zhr2021 (赞：2)

# [CF1986F Non-academic Problem](https://www.luogu.com.cn/problem/CF1986F) 题解
简略题意：给一张联通无向图，求断开一条边后最少的联通点对

## solution
明显地，原图联通，所以若不删桥删别的边，跟不删没有区别，所以必然删桥。

删掉桥后，桥两边各成一个联通块。减少的点对数为两边联通块大小乘积，对这个值取最大值，再用总的点对数减去它就是答案。

考虑计算每个桥产生的贡献。按 tarjan 算法的方式，设当前找到一条 $u -v$ 的桥（$v$ 为儿子），我们可以计算出 $v$ 所在联通块的大小 $siz_v$，贡献即为 $siz_v\times(n-siz_v)$。$siz_v$ 的计算可以用类似树形 dp 的方法计算，也无需计算边双联通分量之类，具体见代码。
## code
[提交记录（171ms）](https://www.luogu.com.cn/record/166271962)

~~不用边双的代码就是好写很多~~
```cpp
#include<bits/stdc++.h>
#define L long long
using namespace std;
inline L read(){
	L x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<3ll)+(x<<1ll)+(ch^48ll);ch=getchar();}
	return w?-x:x;
}
const L N=1e6+10;
L T,n,m,ma;
struct edges{
	L nxt,to;
}edge[N];
L idx=1,head[N];
void addedge(L u,L v){
	edge[++idx]={head[u],v};
	head[u]=idx;
}
L low[N],dfn[N],dft,siz[N];
void tarjan(L u,L from){
	siz[u]=1;
	low[u]=dfn[u]=++dft;
	for(L i=head[u];i;i=edge[i].nxt){
		L v=edge[i].to;
		if(!dfn[v]){
			tarjan(v,i);
			siz[u]+=siz[v];
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){
				ma=max(ma,siz[v]*(n-siz[v]));
			}
		}
		else if(i!=(from^1)) low[u]=min(low[u],dfn[v]);
	}
}
int main(){
	T=read();
	while(T--){
		n=read(),m=read();
		idx=1,dft=ma=0;
		for(L i=1;i<=n;i++) low[i]=dfn[i]=head[i]=siz[i]=0;
		for(L i=1;i<=m;i++){
			L u=read(),v=read();
			addedge(u,v),addedge(v,u);
		}
		tarjan(1,0);
		printf("%lld\n",n*(n-1)/2-ma);
	}
	return 0;
}
```

---

## 作者：liugh_ (赞：2)

[CF1986F Non-academic Problem](https://www.luogu.com.cn/problem/CF1986F)

Div 3 也能出原题了么？

---

对于每组数据，给定一张 $n$ 个点 $e$ 条边的无向图，割掉一条边会导致有某些点对不连通，求这个数量的最大值。

$\sum n,\sum e\le 2\cdot 10^5$。

---

边双连通分量中的边割去后不会有点对的连通性发生变化，由此想到缩点。无向图缩点后是一棵树，可以直接重新建图并 $\text{dfs}$ 一遍，此时割掉树上的一条边会导致树分成“上下”两部分，下面是当前子树大小，上面就用总点数减去当前子树大小，这两部分相乘就是一个可行的答案，取 $\max$ 即可。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline","-fgcse","-fgcse-lm","-fipa-sra","-ftree-pre","-ftree-vrp","-fpeephole2","-ffast-math","-fsched-spec","unroll-loops","-falign-jumps","-falign-loops","-falign-labels","-fdevirtualize","-fcaller-saves","-fcrossjumping","-fthread-jumps","-funroll-loops","-freorder-blocks","-fschedule-insns","inline-functions","-ftree-tail-merge","-fschedule-insns2","-fstrict-aliasing","-falign-functions","-fcse-follow-jumps","-fsched-interblock","-fpartial-inlining","no-stack-protector","-freorder-functions","-findirect-inlining","-fhoist-adjacent-loads","-frerun-cse-after-loop","inline-small-functions","-finline-small-functions","-ftree-switch-conversion","-foptimize-sibling-calls","-fexpensive-optimizations","inline-functions-called-once","-fdelete-null-pointer-checks")
#pragma GCC target("abm","avx","avx2","f16c","fma","mmx","popcnt","sse","sse2","sse3","sse4","ssse3")
#define inline inline __attribute__((always_inline))
#define getchar() (_p==_q&&(_q=(_p=_b)+fread(_b,1,_s,stdin),_p==_q)?-1:*_p++)
using namespace std;const int _s=1<<20;char _b[_s],*_p=_b,*_q=_b;template<class T>inline void fr(T&x){x=0;char c=0;do{}while(c=getchar(),c<48||c>57);do x=x*10+c-48;while(c=getchar(),c>47&&c<58);}inline void debug(){cout<<endl;}template<class T,class...Argv>inline void debug(const T&x,const Argv&...argv){cout<<' '<<x;debug(argv...);}template<class T>inline void Debug(const string&s,const T l,const T r){cout<<' '<<s;for(T it=l;it!=r;++it)cout<<' '<<*it;cout<<endl;}template<class T>inline void Debug(const T l,const T r){for(T it=l;it!=r;++it)cout<<' '<<*it;cout<<endl;}
#define int long long

const int Maxn = 2e5 + 3;

int N, E;

struct edge {int to, pre;} eg[Maxn * 2]; int eidx = 1, ehd[Maxn];
inline void adde(int u, int v) {eg[++eidx] = {v, ehd[u]}; ehd[u] = eidx;}

list<int> g[Maxn];

int dfn[Maxn], low[Maxn], idx;
int stk[Maxn], stop;
int scc, bel[Maxn]; int cnt[Maxn];
void tarjan(int u, int lst) {
	dfn[u] = low[u] = ++idx;
	stk[++stop] = u;
	for (int e = ehd[u]; e; e = eg[e].pre) {
		int v = eg[e].to;
		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
		}
		else if (v != lst) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		scc++; while (1) {
			int t = stk[stop--];
			bel[t] = scc;
			cnt[scc]++;
			if (t == u) break;
		}
	}
}


bool vis[Maxn];
int ans;
void dfs(int u) {
	vis[u] = 1;
	for (auto v : g[u]) {
		if (vis[v]) continue;
		dfs(v);
		cnt[u] += cnt[v];
	}
	ans = max(ans, cnt[u] * (N - cnt[u]));
}

inline void clear() {
	fill(ehd, ehd + N + 1, 0); eidx = 1;
	fill(g, g + N + 1, list<int>());
	scc = 0;fill(bel, bel + N + 1, 0);
	stop = 0;
	idx = 0;
	fill(dfn, dfn + N + 1, 0);
	fill(low, low + N + 1, 0);
	fill(cnt, cnt + N + 1, 0);
	ans = 0;
	fill(vis, vis + N + 1, 0);
}

signed main() {
	// freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
	int Case; fr(Case); while (Case--) {
		clear();
		fr(N), fr(E);
		for (int i = 1; i <= E; ++i) {
			int u, v; fr(u), fr(v);
			adde(u, v), adde(v, u);
		}
		tarjan(1, 0);
		if (scc == 1) {printf("%lld\n", N * (N - 1) / 2); continue;}
		for (int u = 1; u <= N; ++u) {
			for (int e = ehd[u]; e; e = eg[e].pre) {
				int v = eg[e].to;
				if (bel[u] != bel[v]) {
					g[bel[u]].push_back(bel[v]);
				}
			}
		}
		dfs(bel[1]);
		printf("%lld\n", N * (N - 1) / 2 - ans);
	}
	return 0;
}
```

---

## 作者：yr409892525 (赞：0)

### 题解：CF1986F Non-academic Problem
很明显，只有删除桥才会减少答案。                
设当前桥的下面有 $s$ 个节点，则减少答案 $\frac{1}{2}\times s\times (n-s)$。                             

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using Pii=pair<int,int>;
const int N=1e5+5;
int q,n,m;
struct V{
    int l,d;
    vector<Pii> e;
}v[N];
int t,ans,s[N];
int S(int e,int u){
    if(!v[u].d){
		s[u]=1;
        v[u].l=v[u].d=++t;
        for(auto x:v[u].e){
            if(x.second!=e){
				bool f=!v[x.first].d;
                v[u].l=min(v[u].l,S(x.second,x.first));
				s[u]+=s[x.first]*f;
            }
        }
        if(e && v[u].d==v[u].l){
			ans=max(ans,s[u]*(n-s[u]));
        }
    }
    return v[u].l;
}
signed main(){
	for(cin>>q;q--;ans=t=0){
		cin>>n>>m;
		fill(v+1,v+n+1,v[0]);
		for(int i=1;i<=m;i++){
			int x,y;
			cin>>x>>y;
			v[x].e.emplace_back(y,i);
			v[y].e.emplace_back(x,i);
		}
		for(int i=1;i<=n;i++){
			S(0,i);
		}
		cout<<n*(n-1)/2-ans<<"\n";
	}
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

边双板子。

显然只有删除割边才能改变点对数量。

删除割边之后分为两个子图，令第子图点数为 $n$，那么对当前答案的贡献就是 $\frac{n \times (n - 1)}{2}$。

点数可以通过 dfs 直接求出，剩余 Tarjan 即可。

核心代码：

```cpp
void dfs (int u){
	vis[u] = 1;
	sz[u] = 1;
	for (auto v : g[u]){
		if (vis[v]) continue;
		dfs(v);
		sz[u] += sz[v];
	}
}
void Tarjan (int u,int lst){
	dfn[u] = low[u] = ++cnt;
	for (auto v : g[u]){
		if (v == lst) continue;
		if (!dfn[v]){
			Tarjan(v,u);
			low[u] = min(low[u],low[v]);
			if (low[v] > dfn[u]){
				int x = sz[v] * (sz[v] - 1) / 2;
				int y = (n - sz[v]) * (n - sz[v] - 1) / 2;
				ans = min(ans,x + y);
			}
		}else{
			low[u] = min(low[u],dfn[v]);
		}
	}
}
void solve(){
	cin >> n >> m;
	for (int i = 1 ; i <= n ; i++){
		g[i].clear();
		dfn[i] = low[i] = 0;
		vis[i] = 0;
	}
	for (int i = 1 ; i <= m ; i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	ans = n * (n - 1) / 2;
	dfs(1);
	Tarjan(1,0);
	cout << ans << endl;
}
```

---

## 作者：Daniel_yao (赞：0)

# Solve

考虑快速计算贡献：设将图分为大小为 $n_1,n_2$ 的两部分，显然有 $n_1+n_2=n$。则当前方案贡献为 $\min(\frac{n_1^2-n_1}{2},\frac{n_2^2-n_2}{2})$。

由于要最小化路径树，且只能删去一条边。所以最好的情况是将图尽可能分为两部分，所以满足删除条件的边就是割边。

先缩边双联通分量，然后枚举割边（缩成树后跑 dfs）。然后计算删去该割边的贡献即可，最后取最小的贡献作为答案。

总时间复杂度 $O(n)$。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)
#define inf 1e17

using namespace std;

const int N = 2e5 + 10;

struct Node {
  int v, nx, u;
} e[N], E[N]; 

int T, n, m, h[N], H[N], dfn[N], low[N], cut[N], dcc[N], Col, tot = 1, idx, Idx = 1, siz[N];

void add(int u, int v) {
  e[++tot] = (Node){v, h[u], u};
  h[u] = tot;
}

void Add(int u, int v) {
  E[++Idx] = (Node){v, H[u], u};
  H[u] = Idx;
}

void tarjan(int x, int fa) {
  dfn[x] = low[x] = ++idx;
  for (int i = h[x]; i; i = e[i].nx) {
    int y = e[i].v;
    if(!dfn[y]) {
      tarjan(y, x);
      low[x] = min(low[x], low[y]);
      if(low[y] > dfn[x]) cut[i] = cut[i ^ 1] = 1;
    } else if(y != fa) {
      low[x] = min(low[x], dfn[y]);
    }
  }
}

void dfs(int x, int cnt) {
  dcc[x] = cnt;
  siz[cnt]++;
  for (int i = h[x]; i; i = e[i].nx) {
    int y = e[i].v;
    if(dcc[y] || cut[i]) continue;
    dfs(y, cnt);
  }
}

void Dfs(int x, int fa) {
  for (int i = H[x]; i; i = E[i].nx) {
    int y = E[i].v;
    if(y == fa) continue;
    Dfs(y, x);
    siz[x] += siz[y];
  }
}

void solve() {
  int ans = inf;
  Col = idx = 0;
  Idx = tot = 1;
  memset(cut, 0, sizeof cut);
  For(i,1,n) {
    h[i] = H[i] = 0;
    dfn[i] = low[i] = dcc[i] = siz[i] = 0;
  }
  cin >> n >> m;
  For(i,1,m) {
    int u, v; cin >> u >> v;
    add(u, v), add(v, u);
  }
  tarjan(1, 1);
  For(i,1,n) {
    if(!dcc[i]) dfs(i, ++Col);
  }
  For(i,1,n) {
    for (int j = h[i]; j; j = e[j].nx) {
      int y = e[j].v;
      if(dcc[i] != dcc[y]) Add(dcc[i], dcc[y]);
    } 
  }
  Dfs(1, 0);
  For(i,1,n) {
    ans = min(ans, (n * n - n - (2 * siz[i] * (n - siz[i]))) / 2);
  }
  cout << ans << endl;
  return ;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：TTpandaS (赞：0)

只有删掉桥才能减少联通点对。

只需要统计出桥连接的两个连通块中点的数量 $x,y$，那么联通点对数量就会减少 $x \times y$ 个。

找桥就用 low 数组记录一个点即其儿子能回到的最小的 dfn。当一个点 $x$ 的儿子节点 $y$ 搜索一遍后的 $low_y$ 仍然小于 $dfn_x$，说明边 $x \to y$ 为桥。统计连通块数量只需要用搜索 $y$ 后的 dfn 值减去搜索 $y$ 前的 dfn 值即可。

---

## 作者：QWQ_123 (赞：0)

因为是删除一条边，所以考虑边双缩点，然后枚举删除哪一条割边。

由于让我们求最少联通数，那么实际上就是求最多不连通的数量。

然后我们在缩点之后的树上搜索，对于删除 $(u,fa_u)$ 这条边，那么它减少的联通的数量就是 $sz_u \times (sz_1 - sz_u)$，其中 $sz_1$ 表示整棵树的 $sz$。

然后用总数减去最大的不连通数即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int ll

const int N = 1e5 + 5;

int T = 0;
vector<int> e[N], e1[N];
int dfn[N], low[N], fa[N], ct;
bool st[N]; int cnt = 0;
int ccnt = 0;
int sz[N];
int ssz[N];
vector<pair<int, int>> cut_e, b;
int bel[N];
stack<int> stk;

void tarjan(int u) {
	stk.push(u);
	low[u] = dfn[u] = ++ct;
	for (auto v : e[u]) {
		if (!dfn[v]) {
			fa[v] = u;
			tarjan(v);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u])
				cut_e.push_back({u, v});
		}
		else if (v != fa[u])
			low[u] = min(low[u], dfn[v]);
	}

	if (low[u] == dfn[u]) {
		int tmp;
		int cnt = 0;
		vector<int> p;
		++ccnt;
		do {
			tmp = stk.top();
			stk.pop();
			bel[tmp] = ccnt;
			++cnt;
			p.push_back(tmp);
		} while(tmp != u);

		sz[ccnt] = cnt;
	}
}

void dfs(int u) {
	++cnt;
	st[u] = true;
	// cout << u << ' ' << cnt << endl;

	for (auto v : e[u]) {
		if (!st[v]) dfs(v);
	}
}

void Dfs(int u) {
	st[u] = true;
	for (auto v : e1[u]) {
		if (!st[v]) {
			Dfs(v);
			sz[u] += sz[v];
		}
	}
}

int ans;
void DP(int u) {
	ans = max(ans, sz[u] * (sz[1] - sz[u]));
	// cout << u << ' ' << e[u].size() << ' ' << sz[u] << "---\n";
	st[u] = true;
	for (auto v : e1[u]) {
		if (!st[v]) {
			DP(v);
		}
	}
}

signed main() {
	scanf("%lld", &T);
	while (T--) {
		int n, m;
		scanf("%lld%lld", &n, &m);
		for (int i = 1; i <= m; ++i) {
		   int u, v;
		   scanf("%lld%lld", &u, &v);
		   b.push_back({u, v});
		   e[u].emplace_back(v);
		   e[v].emplace_back(u);
		}

		long long res = 0;

		for (int i = 1; i <= n; ++i) st[i] = false;
		for (int i = 1; i <= n; ++i) {
			cnt = 0;
			if (!st[i]) {
				dfs(i);
				res += cnt * (cnt - 1) / 2ll;
			}
		}

		// cout << res << endl;

		ct = 0;
		tarjan(1);

		for (auto [u, v] : b) {
			e1[bel[u]].push_back(bel[v]);
			e1[bel[v]].push_back(bel[u]);
		}

		for (int i = 1; i <= n; ++i) st[i] = false;
		Dfs(1);
		for (int i = 1; i <= n; ++i) st[i] = false;
		ans = 0;
		DP(1);

		// cout << res << ' ' << ans << endl;

		printf("%lld\n", res - ans);

		ccnt = 0;
		for (int i = 1; i <= n; ++i) e[i].clear(), e1[i].clear(), low[i] = dfn[i] = sz[i] = bel[i] = 0;
		cut_e.clear();
		b.clear();
	}

	return 0;
}
```

---

## 作者：Houkiseino_Kokoro (赞：0)

### $\texttt{F. Non-academic Problem}$
#### [原题链接](https://codeforces.com/contest/1986/problem/F)
#### 题意简述
给定一张 $n$ 个节点的简单无向连通图，在这个图中删掉一条边，使得图中相互连通的节点对数最少。

#### 解法
前置知识：Tarjan / eDCC 缩点。

模板题指路：[P8436 边双连通分量](https://www.luogu.com.cn/problem/P8436)

显然为使图中连通的节点对减少，删掉的一条边必须是桥（割边）。如果图中没有桥，答案为 $\dfrac{n(n-1)}{2}$。因此用 Tarjan 算法把图缩成一棵树，以边双连通分量中节点个数作为缩点后对应的节点权值。

接下来考虑树边删除后的答案如何计算。我们随意指定一个节点为根对这棵树跑 dfs 计算每个节点的所有子树的权值与该节点本身权值之和。假设某个节点的权值为 $p$，显然，将该节点与其祖先相连的那条边删除等价于将图分成了节点数分别为 $p$ 与 $n-p$ 的两部分，故答案为 $\dfrac{p(p-1) + (n-p)(n-p-1)}{2}$。暴力枚举每一条树边删除后的答案即可。时间复杂度为 $O(n+m)$。

#### 代码

赛时代码，且板子是复制的自己封装好的代码，因此写的可能会比较臃肿 qwq。

下面是核心代码：

```cpp
void solve()
{
    long long n, m, u, v;
    std::cin >> n >> m;
    p0_templates::graph::adj_table<long long> g(n);
    for (size_t i = 1; i <= m; i++)
    {
        std::cin >> u >> v;
        g.build_edge(u, v, i);
        g.build_edge(v, u, i);
    }
    p0_templates::graph::tarjan_edcc<long long> edcc(g);
    if (edcc.get_bridge_cnt() == 0)
    {
        std::cout << n * (n - 1) / 2 << '\n';
        return;
    }
    p0_templates::graph::adj_table<long long> tree(edcc.get_edcc_cnt());
    for (size_t i = 1; i <= n; i++)
    {
        for (auto j : g.get_neighbour(i))
        {
            auto x = edcc.edcc_find(i), y = edcc.edcc_find(j);
            if (x != y)
            {
                tree.build_edge(x, y);
            }
        }
    }
    std::vector<long long> weight(edcc.get_edcc_cnt() + 1);
    std::function<long long(int, int)> dfs = [&tree, &edcc, &weight, &dfs](int x, int father) -> long long
    {
        weight[x] += edcc.get_edcc_weight(x, 0);
        if (tree.get_neighbour(x).size() == 1 && tree.get_neighbour(x).front() == father)
        {
            return weight[x];
        }

        for (auto i : tree.get_neighbour(x))
        {
            if (i == father)
            {
                continue;
            }
            weight[x] += dfs(i, x);
        }
        return weight[x];
    };
    dfs(1, 1);
    long long ans = n * (n - 1) / 2;
    for (size_t i = 1; i <= edcc.get_edcc_cnt(); i++)
    {
        ans = std::min(ans, (weight[i] * (weight[i] - 1) + (n - weight[i]) * (n - weight[i] - 1)) / 2);
    }
    std::cout << ans << '\n';
}

```

这边是自己封装的建图与 Tarjan 的板子，请不要随意抄袭 qwq。

```cpp
/*
------------------------------------------------------
Graph Theory: Adjacency Table
图论:         邻接表

以存放每个点的所有出边的形式存储一个图。
存树也用邻接表存。
使用条件：无
应用范围：无特殊需求下的存图方法，尤其适合存树

时间复杂度：1. 查询是否存在节点u到节点v的边        O(d+(u))
            2. 遍历一个点的所有出边    O(d+(u))
            3. 遍历整张图             O(n+m)
------------------------------------------------------
*/
template <typename T>
class adj_table
{
private:
    typedef struct
    {
        size_t b;
        T x;
    } edge;

    std::vector<std::vector<edge>> _graph;

    std::vector<T> _vertex_weight;

    size_t _n;

public:
    adj_table() {}
    // 新建一个有n个节点的图

    adj_table(size_t n)
    {
        _graph.resize(n + 1);
        _vertex_weight.resize(n + 1, 1);
        _vertex_weight[0] = 0;
        _n = n;
    }

    // 新建一条由节点a指向节点b，权值为x的边
    // 注：按照有向图方式存边，若建无向图，请将两个边都存一遍。边无权时无需输入权值，默认设为1。
    void build_edge(size_t a, size_t b, T x = 1)
    {
        _graph[a].push_back({b, x});
    }

    // 给节点赋点权，不赋值时点权为1
    void set_vertex_weight(size_t pos, T weight)
    {
        _vertex_weight = weight;
    }

    // 查询节点点权
    T get_vertex_weight(size_t pos)
    {
        return _vertex_weight[pos];
    }

    // 查询图的节点个数
    size_t get_vertex_count()
    {
        return _n;
    }

    // 返回节点a的邻域
    // 注：可能会返回空数组，请注意用arr.empty()方法检查一下
    std::vector<size_t> get_neighbour(size_t a)
    {
        std::vector<size_t> ans;
        for (auto i : _graph[a])
        {
            ans.push_back(i.b);
        }
        return ans;
    }

    // 返回节点a的所有出边
    // 注：可能会返回空数组，请注意用arr.empty()方法检查一下
    std::vector<edge> &get_outedge(size_t a)
    {
        return _graph[a];
    }
};

/*
------------------------------------------------------
Graph Theory: Tarjan (edge Double Connected Components, vDCC)
图论:         Tarjan算法（边双连通分量）

功能：        求一张有向图所有的桥与边双连通分量

用途：        将图上所有边双连通分量分别缩成一个点，从而将图转为树或森林。

时间复杂度：  O(n+m)

传入参数：    图g。

注：          传入的图 g **需要给每一条边编号**！！实现方法即为给每一条边赋一个独一无二的权值。
------------------------------------------------------
*/
template <typename T>
class tarjan_edcc
{
private:
    graph::adj_table<T> _graph;

    std::vector<size_t> _dfn, _low;
    std::stack<size_t> _s;

    size_t ptr = 0;

    size_t _bridge_cnt = 0;
    std::map<std::pair<size_t, size_t>, bool> _bridges;

    size_t _edcc_cnt = 0;
    std::vector<size_t> _edcc_ans;
    std::vector<T> _edcc_weight = {0};
    std::vector<std::vector<size_t>> __edcc_ans;

    void dfs(size_t u, size_t in_edge)
    {
        _dfn[u] = _low[u] = ++ptr;
        _s.push(u);

        for (auto e : _graph.get_outedge(u))
        {
            size_t v = e.b;
            if (!_dfn[v])
            {
                dfs(v, e.x);
                _low[u] = std::min(_low[u], _low[v]);
                if (_low[v] > _dfn[u])
                {
                    _bridges[{std::min(u, v), std::max(u, v)}] = true;
                    _bridge_cnt++;
                }
            }
            else if (_dfn[v] < _dfn[u] && e.x != in_edge)
            {
                _low[u] = std::min(_low[u], _dfn[v]);
            }
        }

        if (_dfn[u] == _low[u])
        {
            int y;
            _edcc_cnt++;
            _edcc_weight.push_back(0);
            do
            {
                y = _s.top();
                _s.pop();
                _edcc_ans[y] = _edcc_cnt;
                _edcc_weight.back() += _graph.get_vertex_weight(y);
            } while (y != u);
        }
    }

public:
    tarjan_edcc(graph::adj_table<T> g)
    {
        _graph = g;
        auto size = g.get_vertex_count();
        _dfn.resize(size + 1);
        _low.resize(size + 1);
        _edcc_ans.resize(size + 1);

        for (size_t i = 1; i <= size; i++)
        {
            if (!_dfn[i])
            {
                dfs(i, i);
            }
        }
    }

    // 查询节点所属边双连通分量的编号
    size_t edcc_find(size_t pos)
    {
        return _edcc_ans[pos];
    }

    // 判断两节点是否在同一个边双连通分量中
    bool edcc_check(size_t a, size_t b)
    {
        return (_edcc_ans[a] == _edcc_ans[b]);
    }

    // 返回图中边双连通分量的个数
    size_t get_edcc_cnt()
    {
        return _edcc_cnt;
    }

    // 返回节点所属边双连通分量的总权值
    // 传入参数第二项为根据图中节点下标还是边双连通分量下标返回权值，1 = 前者，0 = 后者。默认为后者。
    T get_edcc_weight(size_t x, bool by_node_index_or_edcc_index = 0)
    {
        return _edcc_weight[(by_node_index_or_edcc_index ? _edcc_ans[x] : x)];
    }

    // 返回图中所有的边双联通分量（单个分量内的所有点从下标 0 开始存储）
    std::vector<std::vector<size_t>> &pull_all_edcc()
    {
        __edcc_ans.resize(get_edcc_cnt() + 1);
        for (size_t i = 1; i <= _graph.get_vertex_count(); i++)
        {
            __edcc_ans[_edcc_ans[i]].push_back(i);
        }
        return __edcc_ans;
    }

    // 返回图中桥的个数
    size_t get_bridge_cnt()
    {
        return _bridge_cnt;
    }

    // 判断某条边是不是桥
    bool bridge_check(int u, int v)
    {
        return _bridges[{std::min(u, v), std::max(u, v)}];
    }

    // 获取图中所有的桥
    std::map<std::pair<size_t, size_t>, bool> &pull_all_bridges()
    {
        return _bridges;
    }
};

```

---

## 作者：红黑树 (赞：0)

[可能更好的阅读体验](https://rbtr.ee/CF1986F)

## [题意](https://codeforces.com/contest/1986/problem/F)
给定一个 $n$ 个点，$m$ 条边的连通无向图。您的任务是最小化此图中存在路径的顶点对 $1 \leq u < v \leq n$ 的数量。要实现此目标，您可以从图中移除一条边。

找到最小数量的顶点对！

$1 \leq n, m \leq 10^5$

## 题解
显然删除一个边双连通分量中的边没有任何用处。

于是先跑 Tarjan 缩边双连通分量，然后就会变成一棵树。

计算每个节点的子树大小，记为 $\mathsf{Size}_i$。

如果删除 $i$ 到 $i$ 父亲的边的话，此时树会被拆成两个连通块，大小分别为 $\mathsf{Size}_i$ 和 $n - \mathsf{Size}_i$，于是总的连通点对数量为

$$\mathsf{Size}_i\left(\mathsf{Size}_i - 1\right) + \left(n - \mathsf{Size}_i\right)\left(n - \mathsf{Size}_i - 1\right)$$

因此枚举每个点，求上式的最小值即可。

其实你可以在 Tarjan 过程中做上述过程，找到桥之后直接判两端大小算答案，这样代码会非常好写。

---

## 作者：hikariyo_ (赞：0)

## 题意

给定 $n$ 点 $m$ 边**无向连通图**，编号 $1\sim n$。最小化删除一条边后对于 $1\le u<v\le n$，连通的点对 $(u,v)$ 的数量。

$T$ 组测试数据，其中 $T\le 10^4,n,m\le 10^5,\sum n,\sum m\le 2\times 10^5$。

## 思路

整个图是连通的，删除边双内的边并不会影响连通性，删除桥边会变成两个连通块，一个大小为 $x$ 另一个则为 $n-x$。

对于一个大小为 $x$ 的连通块，编号最小的点有另外 $x-1$ 个点与其对应，以此类推，因此满足条件的点对数量是：

$$
\sum_{i=1}^{x-1}i=\frac{x(x-1)}{2}
$$

所以考虑将图缩点为边双，然后只枚举桥边（即树边），对于所有情况取一个最小值即可。

复杂度 $O(n+m)$，由于我缩点的时候用了 `set` 去重边，所以多一个 $\log$。可以用 `unordered_set` 去重做到线性，但是众所周知 CF 对于哈希不太友好。

## 代码

[Codeforces](https://codeforces.com/contest/1986/submission/267135486)

---

## 作者：wuzy_ (赞：0)

## 题意
给定一个连通无向图 $G$，删除任意一条边 $e$，则 $G' = G - e$，最小化 $G'$ 可相互到达的顶点对数量 $num$。

## Solution
默认读者已了解 targan 算法求割边，尚未了解该算法的读者请参考学习视频  [tarjan 割边](https://www.bilibili.com/video/BV14g411Q7ze/?spm_id_from=333.999.0.0&vd_source=868104a732698ccb20d26ff447380eda)。

显然，只有删除割边才能最小化 $num$。考虑遍历原图 $G$ 的所有割边，假如 $(x,y)$ 是 $G$ 的割边，并且在遍历图的过程中，$x$ 是 $y$ 的父节点。在遍历的过程中，我们能够求算出**以 $u$ 为起点所遍历到的子图的节点数量**，记为 $sz(u)$。那么删除割边 $(x,y)$ 后的顶点对数量为：


$$cnt = \frac{sz(y) \times (sz(y)-1)+(n-sz(y)) \times (n-sz(y)-1)}{2} $$

每当遍历到一条割边，便能求算出一个 $cnt$ ，取 $cnt$ 中的最小值作为答案。

**与此同时，假如原图中不存在割边怎么办？**

考虑额外添加顶点 $0$，且顶点 $0$ 只与顶点 $1$ 相连，那么 $(0,1)$ 构成一条割边。在使用 tarjan 函数时，初始化顶点 $0$ 为顶点 $1$ 的父节点即可。


## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100005;

vector<int>g[N];
int dfn[N], low[N], sz[N], tot, n, m;
ll ans;

// f是u的父节点
void tarjan(int u, int f) {
	sz[u] = 1;
	dfn[u] = low[u] = ++tot;
	for (auto v : g[u]) {
		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			sz[u] += sz[v];
		}
		else if (v != f) {
			low[u] = min(low[u], low[v]);
		}
	}
	if (low[u] > dfn[f]) {
		ll cur = 1ll * sz[u] * (sz[u] - 1) / 2 + 1ll * (n - sz[u]) * (n - sz[u] - 1) / 2;
		ans = min(ans, cur);
	}
}

void solve() {
	cin >> n >> m;
	tot = 0, ans = 1e18;
	for (int i = 1;i <= n;i++) {
		g[i].clear();
		dfn[i] = low[i] = sz[i] = 0;
	}

	for (int i = 1;i <= m;i++) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);g[b].push_back(a);
	}

	tarjan(1, 0);
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int t = 1;
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：yshpdyt (赞：0)

## 题意
一个连通无向图，你可以删去任意一条边，并最大化无法相互到达的点对数量。

## Sol
边双连通分量版题，没有做过先去学 [P8436 【模板】边双连通分量](https://www.luogu.com.cn/problem/P8436)。

先考虑如果图是一颗树的情况，记 $siz_x$ 表示 $x$ 及其子树的大小，答案是：
$$res=\max\limits_{i=1}^n siz_x\times(n-siz_x)$$

意思很好理解，$x$ 子树内的点相对于子树外的每个点都不可达。

树的情况解决了，考虑把图变成树。注意到只有割边对答案影响，那么边双缩点变成树（由于原图保证连通所以不会是森林），改一改每个点的大小即可。

时间复杂度 $O(n+m)$。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 2000005
using namespace std;
vector<pair<ll,ll> >v[N];
vector<ll> vt[N];
stack<ll> q;
ll dfn[N],low[N],cnt,bel[N],n,m,tot,siz[N];
bool vis[N];
bool build(ll x,ll y){
    q.pop();
    siz[tot]++;
    bel[x]=tot;
    return x==y;
}
void tarjan(ll x){
    dfn[x]=low[x]=++cnt;
    q.push(x);
    for(auto [y,id]:v[x]){
        if(vis[id])continue;
        vis[id]=1;
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }else low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        tot++;
        while(1) if(build(q.top(),x))break;
    }
}
struct edge{
    ll x,y;
}e[N];
ll nsiz[N],res;
void dfs(ll x,ll fa){
    nsiz[x]=siz[x];
    for(auto y:vt[x]){
        if(y==fa)continue;
        dfs(y,x);
        nsiz[x]+=nsiz[y];
    }
    for(auto y:vt[x])if(y!=fa)res=max(res,(n-nsiz[y])*(nsiz[y]));
}
void sol(){
    cin>>n>>m;
    while(!q.empty())q.pop();
    for(int i=1;i<=n;i++){
        v[i].clear(),vt[i].clear();
        low[i]=nsiz[i]=siz[i]=bel[i]=dfn[i]=0;
    }
    res=tot=cnt=0;
    for(int i=1,x,y;i<=m;i++){
        vis[i]=0;
        cin>>x>>y;
        e[i]={x,y};
        v[x].push_back(make_pair(y,++cnt));
        v[y].push_back(make_pair(x,cnt));
    }
    for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=m;i++){
        if(bel[e[i].x]==bel[e[i].y])continue;
        vt[bel[e[i].x]].push_back(bel[e[i].y]);
        vt[bel[e[i].y]].push_back(bel[e[i].x]);
    }
    dfs(1,0);
    cout<<n*(n-1)/2-res<<endl;
}
int main(){
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

