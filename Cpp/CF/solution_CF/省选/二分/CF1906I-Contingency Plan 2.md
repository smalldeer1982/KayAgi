# Contingency Plan 2

## 题目描述

You are working as a manager in The ICPC Company. In the company building, there are $ N $ computers (numbered from $ 1 $ to $ N $ ). There are $ N - 1 $ cables, numbered from $ 1 $ to $ N - 1 $ , that connect all the computers into a single network. Cable $ i $ connects computer $ U_i $ and $ V_i $ . Each cable can be set into emergency mode, where cable $ i $ only transfers data from computer $ U_i $ to computer $ V_i $ , but not the other way around. During a disaster, it is mandatory for all cables to be in emergency mode.

Through your research, you discover a new way to determine the vulnerability of a network. You want to add zero or more new cables to the current network such that it is not vulnerable during a disaster. Your network is not vulnerable if and only if there is exactly one permutation of $ 1 $ to $ N $ such that $ u $ appears before $ v $ in the permutation for all cables that connect computer $ u $ and $ v $ . In other words, it should have exactly one topological order.

The following illustration shows examples of not vulnerable networks and vulnerable networks.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906I/ff9330023f2ecf78266212977dcfc3bc8b6c375c.png)For the not vulnerable networks, the only permutation that satisfies the requirement for the networks on the left and on the right are $ [1, 2, 3] $ and $ [3, 1, 2] $ , respectively. Meanwhile, for the vulnerable networks, there are $ 2 $ permutations that satisfy the requirement for the network on the left: $ [1, 2, 3] $ and $ [3, 1, 2] $ ; while there is no permutation that satisfies the requirement for the network on the right.

You are interested in the minimum number of new cables that should be added to the current network such that it is not vulnerable during a disaster. Furthermore, you want to know, which pairs of computers should be connected by using the minimum number of cables. If there are several ways to connect, you can connect in any way of your choice. Under the given constraints, it can be proven that there exists a way to make the network not vulnerable.

## 说明/提示

Explanation for the sample input/output #3

The following illustration shows the original network and the new network with the added cables during a disaster. The only permutation that satisfies the requirement is $ [1, 2, 3, 4, 5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906I/9707ade040aa4f162ed2448ef1274e451a9777c6.png)

## 样例 #1

### 输入

```
3
1 2
3 2```

### 输出

```
1
3 1```

## 样例 #2

### 输入

```
3
1 2
2 3```

### 输出

```
0```

## 样例 #3

### 输入

```
5
1 2
1 3
3 4
3 5```

### 输出

```
2
2 3
4 5```

# 题解

## 作者：FFTotoro (赞：3)

被大佬 @[未来姚班zyl](https://www.luogu.com.cn/user/565742) 一眼秒了。

有结论：一个 DAG 的拓扑序确定的充要条件为它具有一个**生成子图**$^{[1]}$是一条长度为 $n$ 的链。于是现在的问题就变成了如何加最少的边构造出这样的链。

> 注 $[1]$：一个图 $G=(V,E)$ 的一个生成子图 $G'=(V',E')$ 是一个满足 $V'=V\land E'\subseteq E$ 的图。也就是说，生成子图是原图中保留所有结点、并删去若干条边（可以不删）形成的子图。

解决上面的问题可以考虑经典的[最小路径覆盖问题](https://www.luogu.com.cn/problem/P2764)，因为显然我们需要找出若干条**点不相交**的路径，并将它们首尾相接形成一条长度为 $n$ 的链——需要加的边数就是路径数减 $1$ 的值。这个东西可以用匈牙利算法跑，朴素的跑不过去（会 TLE on Test \#7）；但是众所周知的匈牙利常数已经极其小了，加入一些技巧直接让 $n=10^5$ 跑进 $200\mathrm{ms}$。

现在还有一个问题，就是找出路径之后，不能使用随便的顺序将它们连在一起——因为原图是一个有向树，这么做可能会**成环**。解决这个问题的方法是简单的，只需要将所有路径缩成一个点后在原图上跑出拓扑序，按照拓扑序从小到大将路径排序，之后依次相连即可保证不出现环。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
inline vector<vector<int> > cover(int n,vector<pii> e){
  vector<vector<int> > g(n<<1);
  for(auto [u,v]:e)
    g[u+n].emplace_back(v);
  vector<int> b(n<<1,-1),v(n),p(n<<1,-1);
  function<bool(int,int)> dfs=[&](int u,int t){
    for(int i:g[u])
      if(b[i]<t)
        if(b[i]=t;p[i]<0||dfs(p[i],t))
          return p[i]=u,p[u]=i,true;
    return false;
  }; // 匈牙利算法
  iota(v.begin(),v.end(),n);
  shuffle(v.begin(),v.end(),mt19937(time(0)));
  int t=0;
  for(int i:v)dfs(i,t++);
  vector<vector<int> > r;
  for(int i=0;i<n;i++)
    if(p[i]<0){
      int u=i; vector<int> v={u};
      while(~p[u+n])v.emplace_back(u=p[u+n]);
      r.emplace_back(v);
    }
  return r;
} // 最小路径覆盖
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,c=0; cin>>n;
  vector<pii> e(n-1);
  for(auto &[u,v]:e)cin>>u>>v,u--,v--;
  auto r=cover(n,e);
  vector<int> id(n);
  for(int i=0;i<r.size();i++)
    for(int j:r[i])id[j]=i; // 缩点
  vector<vector<int> > g(r.size());
  vector<int> d(r.size()),o(r.size()),p(r.size());
  for(auto [u,v]:e)
    if(id[u]!=id[v])g[id[u]].emplace_back(id[v]),d[id[v]]++;
  queue<int> q;
  for(int i=0;i<r.size();i++)
    if(!d[i])q.emplace(i);
  while(!q.empty()){
    int u=q.front(); o[u]=c++,q.pop();
    for(int i:g[u])
      if(!--d[i])q.emplace(i);
  } // 跑出拓扑序
  iota(p.begin(),p.end(),0);
  sort(p.begin(),p.end(),[&](int x,int y){
    return o[x]<o[y];
  });
  cout<<r.size()-1<<endl;
  for(int i=1;i<p.size();i++)
    cout<<r[p[i-1]].back()+1<<' '<<r[p[i]][0]+1<<'\n';
  return 0;
}
```

---

## 作者：Register_int (赞：3)

在原图中，对于每一条链，他的拓扑序都是确定的。我们需要将原图分成数量尽可能少的链，再将这些链的头尾穿起来即可。

问题转化为求最小链覆盖的方案。先有经典结论：最小链覆盖等于点数减去最大二分图匹配数，建图先跑个 dinic。之后，对于一条从左向右连的边，如果他有流，那么说明这条边作为一条链边被选上了。所以，我们删去所有没有流的边，每个连通块即是一条链。缩完链再在原图上跑出拓扑序，按拓扑序将链首尾相连即可。时间复杂度 $O(n\sqrt n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int MAXM = 6e5 + 10;
const int inf = INT_MAX;

struct edge { int v, c, nxt; } e[MAXM << 1];

int head[MAXN], tot = 1;

inline 
void add(int u, int v, int c) {
	e[++tot] = { v, c, head[u] }, head[u] = tot;
	e[++tot] = { u, 0, head[v] }, head[v] = tot;
}

int lvl[MAXN], lst[MAXN]; queue<int> q;

inline 
bool bfs(int s, int t) {
	memset(lvl, 0xff, sizeof lvl), lvl[s] = 0, q.push(s);
	for (int u; !q.empty();) {
		u = q.front(), q.pop(), lst[u] = head[u];
		for (int i = head[u], v; i; i = e[i].nxt) {
			v = e[i].v;
			if (!e[i].c || ~lvl[v]) continue;
			lvl[v] = lvl[u] + 1, q.push(v);
		}
	}
	return ~lvl[t];
}

int dfs(int u, int t, int f) {
	if (u == t) return f; int res = 0;
	for (int &i = lst[u], v, x; i; i = e[i].nxt) {
		v = e[i].v;
		if (!e[i].c || lvl[v] != lvl[u] + 1) continue;
		x = dfs(v, t, min(f, e[i].c)), x || (lvl[v] = -1);
		e[i].c -= x, e[i ^ 1].c += x, f -= x, res += x;
		if (!f) break;
	}
	return res;
}

inline 
ll dinic(int s, int t) {
	ll res = 0;
	for (; bfs(s, t); res += dfs(s, t, inf));
	return res;
}

vector<int> g[MAXN], ans; queue<int> tq;

bool vis[MAXN]; int d[MAXN], id[MAXN], f[MAXN];

void dfs(int u, int rt) {
	id[u] = rt, f[rt] = u;
	for (int v : g[u]) dfs(v, rt);
}

int n, s, t, u[MAXN], v[MAXN];

int main() {
	scanf("%d", &n), t = n << 1 | 1;
	for (int i = 1; i < n; i++) scanf("%d%d", &u[i], &v[i]), add(u[i], v[i] + n, 1);
	for (int i = 1; i <= n; i++) add(s, i, 1), add(i + n, t, 1); dinic(s, t);
	for (int u = 1; u <= n; u++) {
		for (int i = head[u], v; i; i = e[i].nxt) {
			v = e[i].v;
			if (v && e[i ^ 1].c) g[u].push_back(v - n), vis[v - n] = 1;
		}
	}
	for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i, i);
	for (int i = 1; i <= n; i++) g[i].clear();
	for (int i = 1; i < n; i++) {
		if (id[u[i]] != id[v[i]]) g[id[u[i]]].push_back(id[v[i]]), d[id[v[i]]]++;
	}
	for (int i = 1; i <= n; i++) if (!vis[i] && !d[i]) tq.push(i);
	for (int u; !tq.empty();) {
		ans.push_back(u = tq.front()), tq.pop();
		for (int v : g[u]) if (!--d[v]) tq.push(v);
	}
	printf("%d\n", (int)ans.size() - 1);
	for (int i = 1; i < ans.size(); i++) printf("%d %d\n", f[ans[i - 1]], ans[i]);
}
```

---

## 作者：蒟蒻君HJT (赞：1)

假设我们已经确定了拓扑序从小到大依次为 $p_1,p_2\cdots p_n$，则其是唯一的的充要条件是 $\forall i\in[1,n-1]$，存在有向边 $(p_i,p_{i+1})$。

充分性显然。

必要性：$\forall i\in [1,n-1]$ 满足不存在有向边 $(p_i,p_{i+1})$，交换拓扑序中的 $p_i,p_{i+1}$ 也合法，与唯一性矛盾。

因此一个想法是在原本给的 DAG（有向树一定是 DAG）上找出一组合法的拓扑序，然后依次连 $n-1$ 条边（原来就有则不连）是一个合法的方案，但它显然不一定是加边最少的方案。自然的想法是原本给的边用的越多越好。但不一定所有边都能选上，一个合法的尽可能利用原本给的边的方案需要满足每个点至多只有一条出边被用到，且至多只有一条入边被用到。

所以想到把每个点拆成两个跑二分图匹配。左右各 $n$ 个点，对于原图上的有向边 $(u,v)$，在二分图上建边 $(u_{left},v_{right})$，用网络流跑最大匹配即可。设最大匹配为 $m$，这样就求出了最少边数 $n-1-m$。

但还有个问题是输出方案。考虑把已经选择的边挑出来，将树划分为 $n-m$ 条极长的不相交的链（$1$ 个孤立点也算）。根据我们之前的想法，链内部的点必须在拓扑序里按顺序连着放。而对应其他没有被选择的边，每条边会贡献一个链与链间的拓扑序要求，由于原图是一棵树，所以把链看成新点的话，任意两点间至多只有一条边，而且这些要求必然形成一棵树（相当于对树进行这样的缩链为点的运算是封闭的，但对 DAG 进行的话就不是封闭的，所以这道题初始给的是 DAG 的话就做不了，考虑四个点的边集为 $(1,2),(2,4),(1,3),(3,4)$ 的 DAG 缩 $(1,2),(2,3)$ 这条链后得到的图）。

对于新的要求，跑一次拓扑排序，在相邻链间连一条边即可。这条边从上一条链的链尾连向下一条链的链头。

时间复杂度 $\Theta(n\sqrt n)$。

---

## 作者：operator_ (赞：0)

# Contingency Plan 2

[题目传送门](https://www.luogu.com.cn/problem/CF1906I)

题解区全都是暴力跑匈牙利/Dinic，完全没利用到本题性质啊（怎么官解也是 flow）。来篇 $O(n)$ 的树形 dp。

结论很简单：合法当且仅当最终拓扑序中相邻两点均有连边（显然相邻的两点不可能间接有边）。因为如果存在相邻两点没有连边则可以交换他们。

于是我们就要尽量利用上本来的边，即求最小链覆盖。本题是有向树，因此可以树形 dp：设 $f_{u,0/1}$ 表示 $u$ 的父边是/否被利用上时 $u$ 子树内的最小链覆盖。转移只需要考虑 $u$ 这个点的覆盖状态即可。

dp 完后得到方案，对链进行缩点，按此时的拓扑序依次连接即可。



代码：

```cpp
//Date: 2025-01-31 11:01:59
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
#define P emplace_back
#define CLEAR(a,v) memset((a),(v),sizeof((a)))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
char buf[1<<20],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
bool MBE;
namespace SOLVER {
#define FORGRAPH for(int i=h[u],v;v=e[i].v;i=e[i].nxt)
int n,fe[100005],f[100005][2],fa[100005],S[100005],T[100005],h[100005],cnt;
int in[100005],out[100005],deg[100005];vector<int> g[100005];queue<int> q;
struct Edge{int v,nxt;} e[200005];inline void add(int u,int v) {e[++cnt]={v,h[u]},h[u]=cnt;}
void dfs(int u,int p) {
    int sum=0,Mn[2]={0x3f3f3f3f,0x3f3f3f3f};
    FORGRAPH if(v!=p) fe[v]=i&1,dfs(v,u),sum+=f[v][0],Mn[fe[v]]=min(Mn[fe[v]],f[v][1]-f[v][0]);
    if(!sum) {f[u][0]=f[u][1]=1;return;}
    f[u][0]=min({sum+Mn[0],sum+Mn[1],sum+Mn[0]+Mn[1]-1}),f[u][1]=min(sum+1,sum+Mn[fe[u]]);
}
void print(int u,int p,int k) {
    int sum=0,Mn[2]={0x3f3f3f3f,0x3f3f3f3f},f0=-1,f1=-1;if(k) fa[u]=fa[p];
    FORGRAPH if(v!=p) sum+=f[v][0],Mn[fe[v]]=min(Mn[fe[v]],f[v][1]-f[v][0]);if(!sum) return;
    if(!k) {
        if(f[u][0]==sum+Mn[0]) f0=1,f1=0;
        if(f[u][0]==sum+Mn[1]) f0=0,f1=1;
        if(f[u][0]==sum+Mn[0]+Mn[1]-1) f0=1,f1=1;
    }
    else {
        if(f[u][1]==sum+1) f0=0,f1=0;
        if(f[u][1]==sum+Mn[fe[u]]) f0=(fe[u]==0),f1=(fe[u]==1);
    }
    FORGRAPH if(v!=p) {
        if(fe[v]==0&&f0&&f[v][1]-f[v][0]==Mn[0]) {print(v,u,1),f0=0;continue;}
        if(fe[v]==1&&f1&&f[v][1]-f[v][0]==Mn[1]) {print(v,u,1),f1=0;continue;}
        print(v,u,0);
    }
}
void MAIN() {
    cin>>n;rep(i,1,n-1) {int u=rd(),v=rd();add(u,v),add(v,u);}
    rep(i,1,n) fa[i]=i;dfs(1,0);print(1,0,0);cout<<f[1][0]-1<<endl;
    for(int i=1,u,v;u=e[i+1].v,v=e[i].v;i+=2) if(fa[u]==fa[v]) out[u]++,in[v]++;else deg[fa[v]]++,g[fa[u]].P(fa[v]);
    rep(i,1,n) {if(!in[i]) S[fa[i]]=i;if(!out[i]) T[fa[i]]=i;if(fa[i]==i&&!deg[i]) q.push(i);}
    int now=0;while(q.size()) {
        int u=q.front();q.pop();if(now) printf("%d %d\n",now,S[u]);now=T[u];
        for(int v:g[u]) if(--deg[v]==0) q.push(v);
    }
}
}
bool MED;
signed main() {
    for(int tt=1;tt;tt--) SOLVER::MAIN();
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1906I)

**题目大意**

> 给定 $n$ 个点 $n-1$ 条边的弱联通 DAG，加入最少的边使得该图拓扑序唯一。
>
> 数据范围：$n\le 10^5$。

**思路分析**

可以证明拓扑序唯一当且仅当最长链长度为 $n$，否则拓扑序中无边的相邻元素并交换即可。

那么我们求出该图的最小链覆盖，然后把所有链缩点，按拓扑序连起来即可。

时间复杂度 $\mathcal O(n\sqrt n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace F {
const int MAXV=2e5+5,MAXE=6e5+5,inf=1e9;
struct Edge {
	int v,f,lst;
}	G[MAXE];
int S,T,tot=1,hd[MAXV],cur[MAXV],dep[MAXV];
void init() { tot=1,memset(hd,0,sizeof(hd)); }
void adde(int u,int v,int w) { G[++tot]={v,w,hd[u]},hd[u]=tot; }
int link(int u,int v,int w) { adde(u,v,w),adde(v,u,0); return tot; }
bool BFS() {
	memcpy(cur,hd,sizeof(cur)),memset(dep,-1,sizeof(dep));
	queue <int> Q;
	Q.push(S),dep[S]=0;
	while(!Q.empty()) {
		int u=Q.front(); Q.pop();
		for(int i=hd[u];i;i=G[i].lst) if(G[i].f&&dep[G[i].v]==-1) {
			dep[G[i].v]=dep[u]+1,Q.push(G[i].v);
		}
	}
	return ~dep[T];
}
int dfs(int u,int f) {
	if(u==T) return f;
	int r=f;
	for(int i=cur[u];i;i=G[i].lst) {
		int v=G[cur[u]=i].v;
		if(G[i].f&&dep[v]==dep[u]+1) {
			int g=dfs(v,min(r,G[i].f));
			if(!g) dep[v]=-1;
			G[i].f-=g,G[i^1].f+=g,r-=g;
		}
		if(!r) return f;
	}
	return f-r;
}
int Dinic() {
	int f=0;
	while(BFS()) f+=dfs(S,inf);
	return f;
}
}
const int MAXN=1e5+5;
vector <int> G[MAXN];
int st[MAXN],ed[MAXN],id[MAXN],nxt[MAXN],ty[MAXN],deg[MAXN];
bool vis[MAXN];
signed main() {
	int n;
	scanf("%d",&n);
	int s=F::S=2*n+1,t=F::T=2*n+2;
	for(int i=1;i<=n;++i) F::link(s,i,1),F::link(i+n,t,1);
	for(int i=1;i<n;++i) {
		scanf("%d%d",&st[i],&ed[i]);
		id[i]=F::link(st[i],ed[i]+n,1);
	}
	printf("%d\n",n-1-F::Dinic());
	for(int i=1;i<n;++i) if(F::G[id[i]].f) nxt[st[i]]=ed[i],vis[ed[i]]=true;
	for(int i=1;i<=n;++i) if(!vis[i]) for(int j=i;j;j=nxt[j]) ty[j]=i;
	for(int i=1;i<n;++i) if(ty[st[i]]!=ty[ed[i]]) {
		G[ty[st[i]]].push_back(ty[ed[i]]),++deg[ty[ed[i]]];
	}
	queue <int> Q;
	for(int i=1;i<=n;++i) if(!deg[i]&&!vis[i]) Q.push(i);
	for(int x=0;Q.size();) {
		int u=Q.front(); Q.pop();
		if(x) printf("%d %d\n",x,u);
		for(x=u;nxt[x];x=nxt[x]);
		for(int v:G[u]) if(!--deg[v]) Q.push(v);
	}
	return 0;
}
```

---

