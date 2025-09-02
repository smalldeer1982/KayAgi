# Matching Reduction

## 题目描述

You are given a bipartite graph with $ n_1 $ vertices in the first part, $ n_2 $ vertices in the second part, and $ m $ edges. The maximum matching in this graph is the maximum possible (by size) subset of edges of this graph such that no vertex is incident to more than one chosen edge.

You have to process two types of queries to this graph:

- $ 1 $ — remove the minimum possible number of vertices from this graph so that the size of the maximum matching gets reduced exactly by $ 1 $ , and print the vertices that you have removed. Then, find any maximum matching in this graph and print the sum of indices of edges belonging to this matching;
- $ 2 $ — query of this type will be asked only after a query of type $ 1 $ . As the answer to this query, you have to print the edges forming the maximum matching you have chosen in the previous query.

Note that you should solve the problem in online mode. It means that you can't read the whole input at once. You can read each query only after writing the answer for the last query. Use functions fflush in C++ and BufferedWriter.flush in Java languages after each writing in your program.

## 说明/提示

In this problem, you may receive the verdict "Idleness Limit Exceeded" since it is in online mode. If it happens, it means that either the output format is wrong, or you don't meet some constraint of the problem. You may treat this verdict as "Wrong Answer".

For your convenience, the output for queries in the example is separated by the line ===. Don't print this line in your program, it is done only to make sure that it's easy to distinguish between answers for different queries in the statement.

## 样例 #1

### 输入

```
3 4 4 4
2 2
1 3
2 1
3 4
1
2
1
2```

### 输出

```
1
-4
3
===
2
1 2
===
1
2
2
===
1
2```

# 题解

## 作者：Alex_Wei (赞：7)

> [CF1721F Matching Reduction](https://codeforces.com/problemset/problem/1721/F) *2800

删点网络流看起来很离谱，考虑倒过来加点。探究最终态的形态，即删点使得不存在匹配，形成 **独立集**。那我们考虑最大独立集，结合最大独立集 $I$ 等于 $V$ 减去最大匹配 $M$ 的性质：

- 每删去一个点，最大匹配至多减少 $1$。
- 删去恰好 $|M|$ 个点之后，得到原图最大独立集，最大匹配为 $0$。

综合上述两点，最优方案中每次只需删去一个点即可使得匹配大小减少 $1$。

接下来考虑构造方案。每次删去原图非最大独立集的一个节点，根据 $|I| + |M| = |V|$，$|I|$ 不变，$|V|$ 减 $1$，则 $|M|$ 减 $1$，合法，这样节点的方案就搞定了。

至于具体匹配边的方案，求出非最大独立集节点与最大独立集之间的最大匹配，可知每个非最大独立集节点均与某个最大独立集节点匹配，这样容易知道删去每个点之后对应删去了哪条匹配边，时间复杂度 $\mathcal{O}(m\sqrt n)$。

进一步地，笔者看了 jiangly 的代码之后发现，其实求最大独立集时得到的最大匹配 $M$ 就是一个合法的 $V\backslash I$ 与 $I$ 之间的匹配，不需要重新求了，因为每条匹配边至少有一个端点不属于 $I$，而 $|M| = |V\backslash I|$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 4e5 + 5;
constexpr int M = 6e5 + 5;
struct flow {
  int cnt = 1, hd[N], nxt[M << 1], to[M << 1], limit[M << 1];
  void add(int u, int v, int w) {
    nxt[++cnt] = hd[u], hd[u] = cnt, to[cnt] = v, limit[cnt] = w;
    nxt[++cnt] = hd[v], hd[v] = cnt, to[cnt] = u, limit[cnt] = 0;
  }
  int dis[N], cur[N], T;
  int dfs(int id, int res) {
    if(id == T) return res;
    int flow = 0;
    for(int i = cur[id]; i && res; i = nxt[i]) {
      cur[id] = i;
      int it = to[i], c = min(limit[i], res);
      if(dis[id] + 1 == dis[it] && c) {
        int k = dfs(it, c);
        flow += k, res -= k, limit[i] -= k, limit[i ^ 1] += k;
      }
    }
    if(!flow) dis[id] = -1;
    return flow;
  }
  int maxflow(int s, int t) {
    int flow = 0;
    T = t;
    while(1) {
      queue<int> q;
      memset(dis, -1, sizeof(dis));
      memcpy(cur, hd, sizeof(cur));
      q.push(s), dis[s] = 0;
      while(!q.empty()) {
        int t = q.front();
        q.pop();
        for(int i = hd[t]; i; i = nxt[i])
          if(dis[to[i]] == -1 && limit[i])
            dis[to[i]] = dis[t] + 1, q.push(to[i]);
      }
      if(dis[t] == -1) return flow;
      flow += dfs(s, 1e9);
    }
  }
} g, h;
long long sum[N];
int n1, n2, m, q, I, IC, u[N], v[N], bel[N], L[N], R[N], eid[N];
map<pair<int, int>, int> mp;
int sgn(int id) {return id > 0;}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> n1 >> n2 >> m >> q;
  int t = n1 + n2 + 1;
  for(int i = 1; i <= m; i++) cin >> u[i] >> v[i], v[i] += n1;
  for(int i = 1; i <= n1; i++) g.add(0, i, 1);
  for(int i = 1; i <= n2; i++) g.add(n1 + i, t, 1);
  for(int i = 1; i <= m; i++) g.add(u[i], v[i], 1e9);
  int J = g.maxflow(0, t);
  for(int i = 1; i <= n1; i++) 
    if(g.dis[i] != -1) R[++I] = i, bel[i] = -I;
    else L[++IC] = i, bel[i] = IC;
  for(int i = 1; i <= n2; i++)
    if(g.dis[n1 + i] == -1) R[++I] = -i, bel[n1 + i] = -I;
    else L[++IC] = -i, bel[n1 + i] = IC;
  assert(IC == J);
  for(int i = 1; i <= IC; i++) h.add(0, i, 1);
  for(int i = 1; i <= I; i++) h.add(IC + i, t, 1);
  for(int i = 1; i <= m; i++) {
    if(sgn(bel[u[i]]) == sgn(bel[v[i]])) continue;
    u[i] = bel[u[i]], v[i] = bel[v[i]];
    if(u[i] < 0) swap(u[i], v[i]);
    mp[{u[i], IC - v[i]}] = i;
    h.add(u[i], IC - v[i], 1);
  }
  assert(h.maxflow(0, t) == J);
  for(int i = 1; i <= IC; i++)
    for(int j = h.hd[i]; j; j = h.nxt[j]) {
      int it = h.to[j];
      if(it <= IC || h.limit[j]) continue;
      assert(!eid[i]);
      eid[i] = mp[{i, it}];
      sum[i] = sum[i - 1] + eid[i];
    }
  int curflow = J;
  for(int i = 1; i <= q; i++) {
    int type;
    cin >> type;
    if(type == 1) {
      cout << "1\n";
      cout << L[curflow] << "\n";
      cout << sum[--curflow] << "\n";
    }
    else {
      cout << curflow << "\n";
      for(int j = 1; j <= curflow; j++) cout << eid[j] << " ";
      cout << "\n";
    }
    fflush(stdout);
  }
  return 0;
}
```

---

## 作者：Leasier (赞：5)

前置芝士：[二分图](https://oi-wiki.org/graph/bi-graph/)、[最大流](https://oi-wiki.org/graph/flow/max-flow/)

注意到题目中讨论的是删点而非删边，考虑将最大匹配转化为点数减去最大独立集。

为了将最大匹配减少 $1$，我们显然可以只删除一个不在最大独立集中的点。

我们已知最大独立集的补集为最小点覆盖，于是我们可以通过求最大匹配间接求出最大独立集。具体地，我们在本题中使用最大流求最大匹配，在残量网络上从 $S$ 开始 dfs 并标记访问过的点，最终左部点中未被访问的点和右部点中被访问的点在最大独立集中。

对于操作 $1$，随意选择最大独立集中的一个点删除并删除与之相连的匹配边。

对于操作 $2$，数一下还有多少条匹配边并直接输出匹配边即可。

时间复杂度为 $O(n1 + n2 + m \sqrt{n1 + n2} + q)$。

代码：
```cpp
#include <queue>
#include <cstdio>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int start;
	int end;
	int dis;
} Edge;

int cnt = 1;
int head[400007], id[200007], dis[400007], cur_edge[400007], dis_cnt[400007], candiate[400007], link[400007];
bool vis[400007], mark[200007];
Edge edge[1200007];
queue<int> q;

inline void init(int n){
	for (register int i = 0; i <= n; i++){
		dis[i] = 0x7fffffff;
		cur_edge[i] = head[i];
	}
}

inline void add_edge(int start, int end, int dis){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].start = start;
	edge[cnt].end = end;
	edge[cnt].dis = dis;
}

inline void bfs(int start){
	dis[start] = 0;
	q.push(start);
	while (!q.empty()){
		int cur = q.front(), dis_i = dis[cur] + 1;
		q.pop();
		dis_cnt[dis[cur]]++;
		for (register int i = head[cur]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (dis[x] == 0x7fffffff){
				dis[x] = dis_i;
				q.push(x);
			}
		}
	}
}

int dfs1(int u, int flow, int start, int end, int n){
	if (u == end) return flow;
	int ans = 0;
	for (register int i = cur_edge[u]; i != 0; i = edge[i].nxt){
		cur_edge[u] = i;
		if (edge[i].dis != 0){
			int x = edge[i].end;
			if (dis[u] == dis[x] + 1){
				int t = dfs1(x, min(flow - ans, edge[i].dis), start, end, n);
				edge[i].dis -= t;
				edge[i ^ 1].dis += t;
				ans += t;
				if (ans == flow) return ans;
			}
		}
	}
	cur_edge[u] = head[u];
	if (--dis_cnt[dis[u]] == 0) dis[start] = n;
	dis_cnt[++dis[u]]++;
	return ans;
}

inline int isap(int start, int end, int n){
	int ans = 0;
	bfs(end);
	while (dis[start] < n) ans += dfs1(start, 0x7fffffff, start, end, n);
	return ans;
}

void dfs2(int u){
	vis[u] = true;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		if (edge[i].dis != 0){
			int x = edge[i].end;
			if (!vis[x]) dfs2(x);
		}
	}
}

int main(){
	int n1, n2, m, q, end, candiate_cnt = 0;
	ll sum = 0;
	scanf("%d %d %d %d", &n1, &n2, &m, &q);
	end = n1 + n2 + 1;
	for (register int i = 1; i <= m; i++){
		int x, y, y_;
		scanf("%d %d", &x, &y);
		y_ = y + n1;
		add_edge(x, y_, 1);
		id[i] = cnt;
		add_edge(y_, x, 0);
	}
	for (register int i = 1; i <= n1; i++){
		add_edge(0, i, 1);
		add_edge(i, 0, 0);
	}
	for (register int i = 1; i <= n2; i++){
		int i_ = i + n1;
		add_edge(i_, end, 1);
		add_edge(end, i_, 0);
	}
	init(end);
	isap(0, end, end + 1);
	dfs2(0);
	for (register int i = 1; i <= n1; i++){
		if (!vis[i]) candiate[++candiate_cnt] = i;
	}
	for (register int i = 1; i <= n2; i++){
		int i_ = i + n1;
		if (vis[i_]) candiate[++candiate_cnt] = i_;
	}
	for (register int i = 1; i <= m; i++){
		if (edge[id[i]].dis == 0){
			sum += i;
			link[edge[id[i]].start] = link[edge[id[i]].end] = i;
			mark[i] = true;
		}
	}
	for (register int i = 1, j = 0; i <= q; i++){
		int op;
		scanf("%d", &op);
		if (op == 1){
			int u = candiate[++j];
			printf("1\n");
			if (u <= n1){
				printf("%d\n", u);
			} else {
				printf("%d\n", -(u - n1));
			}
			if (mark[link[u]]){
				mark[link[u]] = false;
				sum -= link[u];
			}
			printf("%lld\n", sum);
		} else {
			int size = 0;
			for (register int k = 1; k <= m; k++){
				if (mark[k]) size++;
			}
			printf("%d\n", size);
			for (register int k = 1; k <= m; k++){
				if (mark[k]) printf("%d ", k);
			}
			printf("\n");
		}
		fflush(stdout);
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：3)

不弱于二分图最大匹配，那跑个网络流先。

直接考虑删点使得最大匹配恰好 $-1$ 似乎有些困难，考虑利用 König 定理：二分图最小点覆盖大小等于最大匹配大小，删点使得最小点覆盖恰好 $-1$．

先求出这个最小点覆盖。可以直接套用 König 定理的构造性证明：对于每个右边每个失配点，尝试走“一条匹配，一条没匹配...”这样交替出现的路径，然后将所有走到的点都打上标记，称之为标记点。则左侧的标记点和右侧的未标记点组成了最小点覆盖。

求出最小点覆盖之后，发现任意删掉一个最小点覆盖中的点即可使得最小点覆盖恰好 $-1$：

- 设原先最小点覆盖大小为 $s$，删去点 $x$ 后，原先最小点覆盖方案中去掉 $x$ 即为一个合法的点覆盖，所以删点后最小点覆盖 $\leq s-1$；
- 删点后最小点覆盖不会 $<s-1$，否则将 $x$ 加入这个点覆盖方案，是删点前的一组合法点覆盖，其大小 $<s$，与 $s$ 是最小点覆盖大小矛盾。

所以遇到一操作直接删掉最小点覆盖中的任意一个点即可。

时间复杂度 $\mathcal{O}(m\sqrt n+q)$

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
#define flh fflush(stdout)
const int N=1000010;
const int inf=0x7fffffff;
int n1,n2,m,q;
int ent=1,tot,S,T;
int dis[N],head[N],cur[N];
int eu[N],ev[N],eid[N];
int blo[N],evis[N];
ll sum=0;
int vis[N];
struct Edge{
	int nxt,to,fl;
}e[N<<1];
inline void add(int x,int y,int z){
	e[++ent]={head[x],y,z};head[x]=ent;
	e[++ent]={head[y],x,0};head[y]=ent;
}
int bfs(){
	for(int i=1;i<=tot;i++)cur[i]=head[i],dis[i]=0;
	queue<int>q;q.push(S);dis[S]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].to,fl=e[i].fl;
			if(fl){
				if(!dis[v]){
					dis[v]=dis[x]+1;
					q.push(v);
				}
			}
		}
	}
	return dis[T]>0;
}
int dfs(int x,int mxfl){
	if(x==T)return mxfl;
	int flow=0;
	for(int i=cur[x];i&&flow<mxfl;i=e[i].nxt){
		cur[x]=i;
		int v=e[i].to;
		if(dis[v]==dis[x]+1){
			int fl=dfs(v,min(e[i].fl,mxfl-flow));
			flow+=fl;e[i].fl-=fl;e[i^1].fl+=fl;
		}
	}
	return flow;
}
int dinic(){
	int mxfl=0;
	while(bfs())mxfl+=dfs(S,inf);
	return mxfl;
}
void dfs(int x){
	if(vis[x])return ;
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt)if(!e[i].fl)dfs(e[i].to);
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n1);read(n2);read(m);read(q);
	S=n1+n2+1;tot=T=S+1;
	for(int i=1;i<=n1;i++)add(S,i,1);
	for(int i=1;i<=n2;i++)add(i+n1,T,1);
	for(int i=1;i<=m;i++){
		int x,y;read(x,y);
		eu[i]=x;ev[i]=n1+y;eid[i]=ent+1;
		add(x,n1+y,1);
	}
	dinic();
	for(int i=1;i<=m;i++){
		if(!e[eid[i]].fl){
			blo[eu[i]]=blo[ev[i]]=i;
			sum+=i;
			evis[i]=1;
		}
	}
	for(int i=n1+1;i<=n1+n2;i++)
		if(!blo[i])
			dfs(i);
	vi vec;
	for(int i=1;i<=n1;i++)if(vis[i])vec.pb(i);
	for(int i=n1+1;i<=n1+n2;i++)if(!vis[i])vec.pb(i);
	while(q--){
		int op;read(op);
		if(op==1){
			puts("1");
			int x=vec.back();vec.pop_back();
			if(x<=n1)cout << x << '\n';
			else cout << -(x-n1) << '\n';
			evis[blo[x]]=0;
			sum-=blo[x];
			cout << sum << '\n';
		}
		else{
			vi eg;
			for(int i=1;i<=m;i++)if(evis[i])eg.pb(i);
			cout << eg.size() << '\n';
			for(auto i:eg)cout << i << ' ';
			puts("");
		}
		flh;
	}
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：0)

提供一点自然的思路？

根据样例猜测每次只需要删去一个点就可以使得最大匹配减少 $1$。

显然需要先求出一个最大匹配的方案（用网络流）。如果以上结论正确，那么每一对匹配点中必须恰好删去一个点，才有可能是对的。

一个概念：二分图匹配的必须点，即在所有最大匹配方案中都要出现的点。在已经求出最大匹配的残量网络（匹配边反向的网络）中缩点，如果对于左部点 $u$，满足源点 $S$ 无法到达 $u$，则 $u$ 是必须点，这等价于 $S$ 与 $u$ 在同一个强连通分量中，原因是必然存在反向边 $(u,S)$，对于右部点是否是必须点的判定同理。

那么如果一对匹配点 $(u,v)$ 中有 $1$ 个或者 $2$ 个必须点，事情就变得非常简单了！第 $i$ 次删去第 $i$ 对匹配中任意一个必须点就可以。

有没有可能 $u$，$v$ 都不是必须点呢？这种情况下，$S$ 能到达 $u$，$v$ 能到达 $T$，说明存在 $S$ 到 $T$ 的路径，与已达到最大流（最大匹配）矛盾。

[for reference only.](https://codeforces.com/contest/1721/submission/235512472)

---

