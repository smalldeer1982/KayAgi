# Privatization of Roads in Berland

## 题目描述

在 Berland 有 $n$ 个城市和 $m$ 条双向道路，每条道路连接两个不同的城市。

最近，Berland 政府做出了一个艰难的决定，将道路的所有权转让给私营公司。Berland 总共有 $100500$ 家私营公司，编号为 $1$ 到 $100500$。在私有化后，每条道路必须且只能属于一家公司的所有。

反垄断委员会要求，私有化后每家公司最多只能拥有两条道路。Berland 的城市规划师也提出了意见：每个城市相邻的道路，最多只能由 $k$ 家不同的公司拥有。

请帮助政府分配道路的所有权，使得上述两个条件都被满足。也就是说，每家公司最多拥有两条道路，并且每个城市相邻的道路最多属于 $k$ 家不同的公司。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3 3 2
1 2
2 3
3 1
4 5 2
1 2
1 3
1 4
2 3
2 4
4 6 2
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
1 2 3 
2 1 1 2 3 
0 0 0 0 0 0 
```

# 题解

## 作者：jianhe (赞：3)

### 前言：
数组开小了于是一直 TLE on test 16。。
### 思路：
先转化一下题意，“每个点周围边的不同颜色数 $\le k$” **等价于** “每个点周围边的相同颜色数 $\ge du_i-k$”（$du_i$ 指点 $i$ 的度数）。

但注意到到底是什么颜色并不重要，重要的是相同颜色的 **个数**。

所以也等价于 “每个点周围的边要选出 $\ge (du_i-k) \times 2$ 个来两两匹配同一颜色”。

由于 “同种颜色的边最多两条”，而且没有重边，所以这两条同种颜色的边最多有一个公共点，也就是说每条边最多为匹配中的一个点做贡献。

因此可以跑一遍网络流来求这个匹配（点匹配边）。

具体地，记 $S$ 为超级源点，$T$ 为超级汇点。那么对于第 $i$ 条边 $(x,y)$，连边 $S \overset{1}\rightarrow i$，$(x+m) \overset{1}\rightarrow T$，$(y+m) \overset{1}\rightarrow T$。

若点 $x$ 满足 $du_x>k$，还要连边 $(x+m) \overset{(du_x-k) \times 2}\rightarrow T$。

这样跑一遍最大流就能够求出匹配了。

### 代码：
```cpp
/*
 * @Author: jianhe
 * @Date: 2025-02-19 08:45:46
 * @LastEditTime: 2025-02-19 09:43:52
 */
#include<bits/stdc++.h>
using namespace std;
#define ll int
const ll N=1222;// 数组开大一点！！！
ll TT,n,m,k,ct,tot,S,T,x,y,du[N],d[N],h[N],now[N],ans[N];
vector<ll> p[N];
// ----------- 下为网络流板子 -----------
struct P{ll to,nxt,w;}e[N<<2];
void add(ll x,ll y,ll w,bool p=1){e[++ct]={y,h[x],w},h[x]=ct;if(p) add(y,x,0,0);}
bool bfs(){
    memset(d,-1,sizeof d);d[S]=0;
    queue<ll> q;q.push(S);now[S]=h[S];
    while(q.size()){
        ll x=q.front();q.pop();
        for(int i=h[x];i;i=e[i].nxt)
            if(e[i].w&&!~d[e[i].to]){
                d[e[i].to]=d[x]+1;now[e[i].to]=h[e[i].to];q.push(e[i].to);
                if(e[i].to==T) return 1;
            }
    }
    return 0;
}
ll dfs(ll x,ll f,ll ct=0){
    if(x==T) return f;
    for(int i=h[x];i&&f;i=e[i].nxt){
        now[x]=i;
        if(e[i].w&&d[e[i].to]==d[x]+1){
            ll t=dfs(e[i].to,min(e[i].w,f));
            if(!t) d[e[i].to]=-1;
            e[i].w-=t,e[i^1].w+=t,ct+=t,f-=t;
        }
    }
    return ct;
}
ll dinic(ll ct=0){while(bfs()) ct+=dfs(S,1e9);return ct;}
// ----------- 上为网络流板子 -----------
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>TT;
    while(TT--){
        cin>>n>>m>>k;T=n+m+1,ct=1,tot=0;
        for(int i=0;i<=T;i++) p[i].clear(),h[i]=du[i]=now[i]=ans[i]=0;// ans 数组也要记得清空
        for(int i=1;i<=m;i++)
            cin>>x>>y,du[x]++,du[y]++,add(S,i,1),add(i,x+m,1),add(i,y+m,1);
        for(int i=1;i<=n;i++)
            if(du[i]>k) add(i+m,T,(du[i]-k)*2),tot+=(du[i]-k)*2;
        if(dinic()!=tot){// 没满流，无解
            for(int i=1;i<=m;i++) cout<<"0 ";
            cout<<"\n";
        }else{
            tot=0;
            for(int i=2;i<=ct;i+=2)
                if(!e[i].w&&e[i^1].to!=S&&e[i].to!=T) p[e[i].to-m].push_back(e[i^1].to);
                // 找到没有连着起点、终点的边，e[i^1].to 是输入的边的编号，e[i^1].to-m 是点的编号
            for(int i=1;i<=n;i++)
                for(int j=0;j+1<p[i].size();j+=2)
                    ans[p[i][j]]=ans[p[i][j+1]]=++tot;// 对于每个点连出去的“满流”的边，两两匹配相同颜色
            for(int i=1;i<=m;i++) if(!ans[i]) ans[i]=++tot;// 剩下的边可以任意染色
            for(int i=1;i<=m;i++) cout<<ans[i]<<" ";
            cout<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：Drind (赞：2)

因为一个点的度数为 $d_i$，但是我们要求连接他的边只有 $k$ 种颜色，所以会有 $d_i-k$ **对**边颜色相同。

但是这个**对**的性质没有什么用，因为任意两两成对之后，结果都是相同的，也就是对于每个点 $i$，我们要选出 $2(d_i-k)$ **条**边，让这些边两两匹配，染成 $d_i-k$ 种颜色。我们发现一条边只能给他连接的两个点之一造成贡献（因为没有重边），所以使用二分图匹配，一个点匹配 $2(d_i-k)$ 条边。

省略网络流板子，代码如下。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;

int E[610][610];
int d[610];
vector<int> bel[1210];
int col[1210];

inline void fake_main(){
	memset(head,-1,sizeof head); cnt=-1;
	s=N-1; t=s-1;
	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		E[u][v]=E[v][u]=i;
		adde(n+i,t,1);//边作为右部点，连汇点
		d[u]++; d[v]++;
	}
	int res=0;
	for(int i=1;i<=n;i++){
		bel[i].clear();
		if(d[i]<=k) continue;
		adde(s,i,(d[i]-k)*2); res+=(d[i]-k)*2;//点作为左部点，连源点，因为要匹配 2(d[i]-k) 条边，所以流量就是 2(d[i]-k)
		for(int r=1;r<=n;r++){//左右点之间连边。
			if(i==r) continue;
			if(!E[i][r]) continue;
			adde(i,n+E[i][r],1);
		}
	}
	for(int i=1;i<=n;i++){
		d[i]=0;
		for(int j=1;j<=n;j++){
			E[i][j]=0;
		}
	}
	
	
	int tmp=dinic(); if(tmp!=res){//如果流不满则无解
		for(int i=1;i<=m;i++) cout<<"0 "; cout<<"\n";
		return;
	}
	for(int i=0;i<=cnt;i+=2){//否则构造方案
		if(edge[i].to!=t&&edge[i^1].to!=s){//这个边不连源点或者汇点，也就是左右点之间的边
			if(edge[i].flow==0){//被流过
				int u=edge[i^1].to;
				int v=edge[i].to;
				bel[u].push_back(v-n);//也就是这个边给点 u 做了贡献
			}
		}
	}
	
	res=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<bel[i].size();j+=2){
			col[bel[i][j]]=col[bel[i][j+1]]=++res;//对他做贡献的边，两两染同色
		}
	}
	for(int i=1;i<=m;i++){
		if(col[i]) cout<<col[i]<<" ";
		else cout<<++res<<" ";//其他散边随便染色
	}cout<<"\n";
	for(int i=1;i<=m;i++) col[i]=0;
}

signed main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--) fake_main();
}

```

---

## 作者：Skeleton_Huo (赞：1)

**补一个图匹配的解法。**

#### 算法流程
设点 $i$ 的度为 $deg_i$，同色邻边对数为 $a_i$，有 $deg_i - a_i \le k$，即 $deg_i - k \le a_i$。问题变为：将所有边先染成互不相同的颜色，再将一些边染成同色，使得对每个 $a_i$ 都满足限制条件。

显然，同色边只有在相邻的时候才能对某个 $a_i$ 产生贡献，且每条边只会对一个点产生贡献，所以我们可以看作将一些边的一个“资源”分配给它的一个端点，而点 $i$ 的“资源”数除以 $2$ 就是 $a_i$（这里可以看出来，这个染色的外壳对解决本题并不重要）。

接下来我们解决分配资源的问题，每个点可以匹配很多边，我们的要求是至少 $2(deg_i - k)$ 条。那么我们不妨将每个点拆成 $2(deg_i - k)$ 个点放在左部，边作为右部，相邻则连边。对该二分图跑匹配即可解决。

#### 复杂度分析
左部点数为 $\sum_{i=1}^{n}{2(deg_i - k)} = O(N)$，右部点数为 $O(N)$，用 HK 算法即可 $O(N \sqrt{N})$ 解决。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1210, inf = 0x3f3f3f3f;

int n, m, k;
int nx;
vector<int> ex[N];
vector<pair<int, int>> e[N];
int deg[N], id[N];
int col[N];
vector<int> mat[N];

int mx[N], my[N], dx[N], dy[N], mindis;

bool bfs() {
  mindis = inf;
  fill(dx + 1, dx + nx + 1, inf), fill(dy + 1, dy + m + 1, inf);
  queue<int> q;
  for (int i = 1; i <= nx; i++)
    if (!mx[i]) q.push(i), dx[i] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : ex[u]) {
      if (mx[u] == v || dy[v] != inf) continue;
      dy[v] = dx[u] + 1;
      int w = my[v];
      if (!w) mindis = min(mindis, dy[v]);
      else dx[w] = dy[v] + 1, q.push(w);
    }
  }
  return mindis != inf;
}

bool dfs(int u) {
  for (auto v : ex[u]) {
    if (mx[u] == v || dy[v] != dx[u] + 1) continue;
    if (dy[v] == mindis && !my[v]) {
      mx[u] = v, my[v] = u, dx[u] = dy[v] = inf;
      return 1;
    }
    int w = my[v];
    if (w && dfs(w)) {
      mx[u] = v, my[v] = u, dx[u] = dy[v] = inf;
      return 1;
    }
    dy[v] = inf;
  }
  dx[u] = inf;
  return 0;
}

void solve() {
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    deg[u]++, deg[v]++;
    e[u].emplace_back(make_pair(v, i));
    e[v].emplace_back(make_pair(u, i));
  }
  for (int u = 1; u <= n; u++) {
    for (int i = 1; i <= 2 * (deg[u] - k); i++) {
      id[++nx] = u;
      for (auto eg : e[u]) {
        ex[nx].emplace_back(eg.second);
      }
    }
  }
  
  int ans = 0;
  while (bfs()) {
    for (int i = 1; i <= nx; i++)
      if(!mx[i]) ans += dfs(i);
  }
  
  if (ans == nx) {
    for (int i = 1; i <= m; i++) mat[id[my[i]]].emplace_back(i);
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < (int)mat[i].size(); j += 2)
        col[mat[i][j]] = col[mat[i][j + 1]] = ++col[0];
    }
    for (int i = 1; i <= m; i++) {
      if (!col[i]) col[i] = ++col[0];
      cout << col[i] << " ";
    }
  } else for (int i = 1; i <= m; i++) cout << "0 ";
  cout << "\n";
  
  for (int i = 1; i <= nx; i++) ex[i].clear();
  for (int i = 1; i <= n; i++) e[i].clear(), mat[i].clear();
  fill(deg + 1, deg + n + 1, 0), fill(col, col + m + 1, 0);
  fill(mx + 1, mx + nx + 1, 0), fill(my + 1, my + m + 1, 0);
  nx = 0;
}

int main() {
  
  int t;
  cin >> t;
  while (t--) solve();
  
  return 0;
}
```

---

## 作者：Mophie (赞：1)

~~为啥这题是个蓝啊~~

首先每条边都要有个相同的出边，设第 $i$ 个点有 $a_i$ 对相同的边。

那么同时设第 $i$ 个点的出度为 $deg_i$，那么 $deg_i - a_i \leq k$，即 $deg_i - k \leq a_i$。

那么就有了 $a_i$ 的取值范围。

然后我们又发现，一条边只能给它的一个端点做贡献。

因为每个公司都只掌管着两条道路，因此不可能一条边同时对它的端点做贡献。

所以说就可以用网络流来做了。然后构造的时候枚举每条边，看是否流量是 $0$，是 $0$ 就相当于取这条边。

最后直接构造即可。

```cpp
/*
    长弓背负，仙女月鹫，
	梦中徐来，长夜悠悠。
	今宵共君，夜赏囃子，
	盼君速归，长夜悠悠。
	睡意袭我，眼阖梦徭，
	睡意袭我，意归襁褓。
	手扶卓揭，仙女水狃，
	盼君速归，长夜悠悠。
	今宵共君，戏于西楼，
	盼君速归，长夜悠悠。
	睡意袭我，涟锜池留，
	睡意袭我，意归海角。
					                  ——《ever17》
*/
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int sum = 0, nega = 1;
	char ch = getchar();
	while (ch > '9'||ch < '0')
	{
	    if (ch == '-') nega = -1;
		ch = getchar();
	}
	while (ch <= '9'&&ch >= '0') sum = sum * 10 + ch - '0', ch = getchar ();
	return sum * nega;
}
const int N = 1e4 + 9, M = 1e6 + 9;
int n, m, s, t;
int val[M << 1], cnt = 1, head[N], nxt[M << 1], to[M << 1], ans;
int dep[N], q[N], f, e, deg[N];
inline void addedge(int u, int v, int w)
{
	to[++cnt] = v, nxt[cnt] = head[u], head[u] = cnt, val[cnt] = w;
	to[++cnt] = u, nxt[cnt] = head[v], head[v] = cnt, val[cnt] = 0;
}
inline bool bfs()
{
	for (int i = 1; i <= t; i++) dep[i] = 0;
	f = 0, e = 1; q[1] = s; dep[s] = 1;
	while(f < e)
	{
		f++;
		int u = q[f];
		for (int i = head[u]; i; i = nxt[i])
			if(!dep[to[i]] && val[i])
			{ 
				q[++e] = to[i];
				dep[to[i]] = dep[u] + 1;
			}
	}
	if(dep[t]) return 1;
	return 0;
}
inline int dfs(int u, int flow)
{
	int tot = 0;
	if(u == t) return flow;
	for (int i = head[u]; i && flow; i = nxt[i]) 
		if(dep[to[i]] == dep[u] + 1 && val[i])
		{
			int res = dfs(to[i], min(flow, val[i]));
			val[i] -= res;
			val[(i ^ 1)] += res;
			flow -= res;
			tot += res;
		}
	if(!tot) dep[u] = 0;
	return tot;
}
int x[M], y[M], k;
int col[N];
vector<int> G[N];
inline void work()
{
	memset(head, 0, sizeof(head)); cnt = 1;
	n = read(), m = read(), k = read(); ans = 0;
	int qwqaq = 0;
	s = n + m + 1, t = n + m + 2;
	for (int i = 1; i <= n; i++) deg[i] = 0, G[i].clear();
	for (int i = 1; i <= m; i++)
	{
		x[i] = read(), y[i] = read(); deg[x[i]]++, deg[y[i]]++;
		addedge(s, i, 1); addedge(i, m + x[i], 1); addedge(i, m + y[i], 1);
	}
	for (int i = 1; i <= n; i++)
	{
		if(deg[i] > k * 2) 
		{
			for (int j = 1; j <= m; j++) printf("0 "); puts("");
			return ;
		} 
		int now = max(0ll, (deg[i] - k) * 2);
		addedge(m + i, t, now); qwqaq += now;
	}
	while(bfs()) ans += dfs(s, 1e18);
	if(qwqaq != ans)
	{
		for (int i = 1; i <= m; i++) printf("0 "); puts("");
		return ;
	}
	for (int i = 1; i <= m; i++)
	{
		if(val[i * 6 - 2] == 0) G[to[i * 6 - 2] - m].push_back(i);
		else if(val[i * 6] == 0) G[to[i * 6] - m].push_back(i);
	}
	int cnt = 0;
	for (int i = 1; i <= m; i++) col[i] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < G[i].size(); j += 2)
			col[G[i][j]] = col[G[i][j + 1]] = ++cnt;
	for (int i = 1; i <= m; i++)
		if(!col[i]) col[i] = ++cnt;
	for (int i = 1; i <= m; i++) printf("%lld ", col[i]); puts("");
	return ;
}
signed main()
{
	int T = read();
	for (int ttt = 1; ttt <= T; ttt++)
		work();
}
```


---

## 作者：happybob (赞：0)

题意：

给定一个 $n$ 个点 $m$ 条边的无向图和一个数 $k$，给每条边染色，使得同色边数至多为 $2$，且任意一个点的所有出边的不同色数 $\leq k$。如果无解报告，否则输出任意一组合法解。

解法：

首先我们可以注意到，如果某种颜色的边有两条，那么必然共用一个顶点。否则你可以把两条边颜色改成不同的。

然后考虑每个点 $u$ 的度数 $d_u$。若 $d_u \leq k$，$u$ 的出边颜色没有限制。若 $d_u > 2k$，必然无解。否则，$u$ 至少要有 $d_u-k$ 对相同颜色的出边。

考虑建立二分图，左侧是点，右侧是边。将每个 $d_u \in (k,2k]$ 的点拆成 $2\times (d_u-k)$ 个点，连向右侧所有 $u$ 的出边。注意到此时我们相当于要求一个完美匹配即可。最终没有限制的边直接随便填就行。

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
#include <map>
using namespace std;

const int N = 5e5 + 5;

int match[N];
bool vis[N];
int dis[N];

int t, n, m, k;
int idx;
vector<int> G[N];
int u[N], v[N];
int ans[N], d[N];
vector<int> ver[N];
int col;
vector<int> NG[N];
map<pair<int, int>, int> mp;
int lft;
int mind;

inline bool bfs(bool flag)
{
	mind = (int)1e9;
	for (int i = 1; i <= idx; i++) dis[i] = -1, vis[i] = 0;
	queue<int> q;
	for (int i = lft; i <= idx; i++) if (!match[i]) q.push(i), dis[i] = 0;
	while (q.size())
	{
		int u = q.front();
		q.pop();
		if (flag) cout << "queue: " << u << "\n";
		if (vis[u]) continue;
		vis[u] = 1;
		for (auto& j : NG[u])
		{
			if (j == match[u] || vis[j]) continue;
			vis[j] = 1;
			dis[j] = dis[u] + 1;
			if (dis[j] > mind) continue;
			int k = match[j];
			if (!k) mind = min(mind, dis[j]);
			else if (!vis[k])
			{
				dis[k] = dis[j] + 1;
				if (dis[k] <= mind) q.push(k);
			}
		}
	}
	return (mind != (int)1e9);
}

int dfs(int u)
{
	if (vis[u] || dis[u] > mind) return 0;
	vis[u] = 1;
	for (auto& j : NG[u])
	{
		if (vis[j] || j == match[u] || dis[j] != dis[u] + 1 || dis[j] > mind) continue;
		vis[j] = 1;
		if (!match[j])
		{
			match[u] = j, match[j] = u;
			return 1;
		}
		else if (dfs(match[j]))
		{
			match[u] = j, match[j] = u;
			return 1;
		}
	}
	return 0;
}

inline int HK()
{
	int ans = 0;
	while (bfs(0))
	{
		for (int i = 1; i <= idx; i++) vis[i] = 0;
		for (int i = lft; i <= idx; i++) if (!match[i]) ans += dfs(i);
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		mp.clear();
		cin >> n >> m >> k;
		for (int i = 1; i <= idx; i++) match[i] = vis[i] = dis[i] = 0, NG[i].clear(), NG[i].shrink_to_fit();
		idx = col = 0;
		for (int i = 1; i <= n; i++) G[i].clear(), G[i].shrink_to_fit(), d[i] = 0, ver[i].clear(), ver[i].shrink_to_fit();
		for (int i = 1; i <= m; i++)
		{
			ans[i] = 0;
			cin >> u[i] >> v[i];
			mp[make_pair(u[i], v[i])] = mp[make_pair(v[i], u[i])] = i;
			G[u[i]].emplace_back(v[i]);
			G[v[i]].emplace_back(u[i]);
			d[u[i]]++, d[v[i]]++;
		}
		idx = m;
		lft = idx + 1;
		bool f = 0;
		for (int i = 1; i <= n; i++)
		{
			if (d[i] <= k) continue;
			if (d[i] > 2 * k)
			{
				for (int j = 1; j <= m; j++) cout << "0 ";
				cout << "\n";
				f = 1;
				break;
			}
			else
			{
				int x = 2 * (d[i] - k);
				for (int j = 1; j <= x; j++)
				{
					idx++;
					ver[i].emplace_back(idx);
					for (auto& k : G[i])
					{
						NG[idx].emplace_back(mp[make_pair(i, k)]);
					}
				}
			}
		}
		if (f) continue;
		int sum = HK();
		if (sum != idx - lft + 1)
		{
			for (int j = 1; j <= m; j++) cout << "0 ";
			cout << "\n";
		}
		else
		{
			for (int i = 1; i <= n; i++)
			{
				for (int j = 0; j < ver[i].size(); j += 2)
				{
					int x = j, y = j + 1;
					int a = match[ver[i][x]], b = match[ver[i][y]];
					col++;
					ans[a] = ans[b] = col;
				}
			}
			for (int i = 1; i <= m; i++)
			{
				if (!ans[i]) ans[i] = ++col;
				cout << ans[i] << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}
```

---

