# [ABC280F] Pay or Receive

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc280/tasks/abc280_f

$ 1,\ldots,N $ の番号がついた $ N $ 個の街と、$ 1,\ldots,M $ の番号がついた $ M $ 本の道路があります。

道路 $ i $ は街 $ A_i $ と $ B_i $ を結んでいます。道路を通行すると、所持している **ポイント** が次の通り増減します。

- 道路 $ i $ を使って、街 $ A_i $ から街 $ B_i $ に移動するときにはポイントが $ C_i $ 増加し、街 $ B_i $ から街 $ A_i $ に移動するときにはポイントが $ C_i $ 減少する。
 
所持しているポイントは負にもなりえます。

次の $ Q $ 個の質問に答えてください。

- 所持しているポイントが $ 0 $ である状態で街 $ X_i $ から移動を始めたとき、街 $ Y_i $ にいる状態で所持しているポイントの最大値を出力せよ。  
   ただし、街 $ X_i $ から街 $ Y_i $ に到達できないときは `nan`、街 $ Y_i $ にいる状態で所持しているポイントをいくらでも増やせるときは `inf` を代わりに出力せよ。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 10^5 $
- $ 0\leq\ M\ \leq\ 10^5 $
- $ 1\leq\ Q\ \leq\ 10^5 $
- $ 1\leq\ A_i,B_i,X_i,Y_i\ \leq\ N $
- $ 0\leq\ C_i\ \leq\ 10^9 $
- 入力は全て整数である
 
### Sample Explanation 1

$ 1 $ 番目の質問では、道路 $ 5 $ を使って街 $ 5 $ から街 $ 3 $ に移動すると、ポイントを $ -2 $ 所持している状態で街 $ 3 $ にいることができます。 これ以上ポイントを大きくすることはできないので答えは $ -2 $ になります。 $ 2 $ 番目の質問では、「道路 $ 2 $ を使って街 $ 1 $ から街 $ 2 $ に移動し、道路 $ 1 $ を使って街 $ 2 $ から街 $ 1 $ に移動する」 という行動を好きなだけ繰り返したあと、道路 $ 2 $ を使って街 $ 1 $ から街 $ 2 $ に移動することで、 街 $ 2 $ にいる状態で所持しているポイントをいくらでも増やすことができます。 $ 3 $ 番目の質問では、街 $ 3 $ から移動を始めて街 $ 1 $ へ到達することはできません。

### Sample Explanation 2

始点と終点が同じ街である道路や、始点と終点が同じ街である質問が含まれることもあります。

## 样例 #1

### 输入

```
5 5 3
1 2 1
1 2 2
3 4 1
4 5 1
3 5 2
5 3
1 2
3 1```

### 输出

```
-2
inf
nan```

## 样例 #2

### 输入

```
2 1 1
1 1 1
1 1```

### 输出

```
inf```

## 样例 #3

### 输入

```
9 7 5
3 1 4
1 5 9
2 6 5
3 5 8
9 7 9
3 2 3
8 4 6
2 6
4 3
3 8
3 2
7 9```

### 输出

```
inf
nan
nan
inf
-9```

# 题解

## 作者：CarroT1212 (赞：13)

### 题目大意

有一张 $N$ 个点 $2M$ 条边的有向图，第 $i$ 条边是一条从第 $A_i$ 个点到第 $B_i$ 个点，权值为 $C_i$ 的边，第 $i+m$ 条边是一条从第 $B_i$ 个点到第 $A_i$ 个点，权值为 $-C_i$ 的边。现给定 $Q$ 次询问，每次询问给定 $X_i,Y_i$，你需要输出从第 $X_i$ 个点到第 $Y_i$ 个点的路径上的权值最大值（可以重复经过某个点或某条边）。如果两点不连通，输出 `nan`；如果最大值为无限大，输出 `inf`。

输入格式：第一行三个整数 $N,M,Q$，接下来 $M$ 行每行三个整数 $A_i,B_i,C_i$，再接下来 $Q$ 行每行两个整数 $X_i,Y_i$，表示 $Q$ 组询问。

输出格式：共 $Q$ 行，每行一个整数或是一个字符串，表示对应询问的回答。

数据范围：$2 \le N \le 10^5$，$0 \le M \le 10^5$，$1 \le Q \le 10^5$，$1 \le A_i,B_i,X_i,Y_i \le N$，$0 \le C_i \le 10^9$。

------------

### 解法分析

赛时被 D 把心态搞崩了没去仔细想，赛后听学长讲评后发现是很有意思的一道题。

下面的分析全部建立在本题图的特殊性质条件的基础上。

显然的是只要 $X_i,Y_i$ 不在同一个连通块中，这组询问的答案就是 `nan`。

（~~然而赛时的我止步于此。~~）

同样显然的是只要 $X_i,Y_i$ 在同一个连通块中，而且这个连通块内存在正环的话，这组询问的答案就是 `inf`。

并且，只要有负环，就一定有正环，反之亦然。

那只出现什么样的环才能不存在正环或者负环呢？

边上权值之和为 $0$ 的环。

而且，显然环上任意两点之间都有两条简单路径，然后我们会发现，当环满足边权之和为 $0$ 的条件时，这两条路径的权值相同。

所以，**当一个连通块中不存在正环与负环时，块上任意两点之间不管有多少条不同路径，它们的权值都是相等的。**

信息量有点大，花点时间理解一下。

于是利用上面的结论我们可以发现一种解法：对于每个连通块，从块上任意一点搜索整个块，设这个点与第 $i$ 个点的距离为 $dis_i$。由刚刚的结论我们可以知道如果块内不存在正环的话 $dis_i$ 是唯一的，如果不唯一就说明有正环。如果询问中的 $X_i,Y_i$ 在同一连通块且块内不存在正环的话，这一组询问的答案就为 $dis_{Y_i}-dis_{X_i}$（可以理解为 $dis_{Y_i}+(-dis_{X_i})$。同样利用结论，两点之间所有路径权值相等，所以只要求出任意一条路径的权值就足够了）。

------------

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pll pair<ll,ll>
using namespace std;
const ll N=1e5+7;
ll n,m,q,coid,vis[N],dis[N],isnf[N],co[N];
vector <pll > v[N];
void dfs(ll pos) {
	co[pos]=coid; // 记连通块编号
	for (pll i:v[pos]) {
		ll x=i.first,y=i.second;
		if (!vis[x]) dis[x]=dis[pos]+y,vis[x]=1,dfs(x);
		else if (dis[x]!=dis[pos]+y) isnf[coid]=1; // 存在不相等路径，则有正环，注意这个时候还不能直接退出，你连通块编号还没记完呐
	}
}
int main() {
	scanf("%lld%lld%lld",&n,&m,&q);
	for (ll i=1,r1,r2,r3;i<=m;i++)
		scanf("%lld%lld%lld",&r1,&r2,&r3),v[r1].pb({r2,r3}),v[r2].pb({r1,-r3});
	for (ll i=1;i<=n;i++) if (!vis[i]) coid++,vis[i]=1,dfs(i); // 对每个连通块搜索
	for (ll r1,r2;q--;) {
		scanf("%lld%lld",&r1,&r2);
		if (co[r1]!=co[r2]) printf("nan\n"); // 不在同一连通块
		else if (isnf[co[r1]]) printf("inf\n"); // 有正环
		else printf("%lld\n",dis[r2]-dis[r1]);
	}
	return 0;
}
```

---

## 作者：StudyingFather (赞：4)

首先分析一下题目所给图的特殊性质：该图上的边总是成对出现，且一对方向相反的边权值互为相反数。之后会发现，这一特殊性质会大大简化后续问题的求解。

先解决第一个子问题：两点间路径存在性的判定。因为本题图上边总是成对出现，所以直接使用并查集维护连通性即可，不再赘述。

现在考虑如何判定“两点间最长路不存在”这一点。该问题显然等价于判定两点所在的连通分量内是否存在正权环。同样，利用该图的特殊性质，正权环判定可以转化为负权环判定。

直接使用常规的 Bellman-Ford 算法判定负环，并求解最长路时间复杂度是 $O(nm)$ 的，并不能满足解决问题的需要。

考虑利用该图的特殊性质简化问题。注意到，在正权环和负权环都不存在的情况下，图上即使存在环路，也只能是零权环路。从零权环路上的 $u$ 点到 $v$ 点时，两个方向的距离是相等的。推而广之，如果图上不存在正（负）权环，从 $u$ 点到 $v$ 点的任何一条路径的长度均相等！

在这一前提下，我们可以直接任意指定图上一点 $s$ 为起点跑 DFS，求出 $s$ 到图上任意一点的距离 $dis(u)$，并完成该连通分量内正（负）环的存在性判定：如果 DFS 过程中重复访问了某个点，且求出的路径长度与之前求得的长度不等，则整个图一定存在正（负）权环。

对于每一组询问 $(u,v)$，利用所有路径的等距性，可以将该路径转换为 $u \to s \to v$ 的路径，从而所求答案为 $dis(v) - dis(u)$。

```cpp
// Problem: F - Pay or Receive
// Contest: AtCoder - Denso Create Programming Contest 2022 Winter(AtCoder
// Beginner Contest 280)
// URL: https://atcoder.jp/contests/abc280/tasks/abc280_f
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
struct dsu {
  int fa[100005], siz[100005];
  void init(int n) {
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
  }
  int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    fa[v] = u, siz[u] += siz[v];
    return true;
  }
  bool together(int u, int v) { return find(u) == find(v); }
  int size(int u) { return siz[find(u)]; }
} ds;
bool vis[100005], inf[100005], inque[100005];
vector<pii> e[100005];
long long dis[100005];
int n, m, q;
void dfs(int u) {
  vis[u] = true;
  for (auto ed : e[u]) {
    int v = ed.first, w = ed.second;
    if (vis[v]) {
      if (dis[v] != dis[u] + w) inf[ds.find(u)] = true;
    } else {
      dis[v] = dis[u] + w;
      dfs(v);
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n >> m >> q;
  ds.init(n);
  for (int i = 1; i <= m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    e[u].emplace_back(v, c);
    e[v].emplace_back(u, -c);
    ds.merge(u, v);
  }
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    dfs(i);
  }
  while (q--) {
    int u, v;
    cin >> u >> v;
    if (!ds.together(u, v))
      cout << "nan" << '\n';
    else if (inf[ds.find(u)])
      cout << "inf" << '\n';
    else
      cout << dis[v] - dis[u] << '\n';
  }
  return 0;
}
```

---

## 作者：zlqwq (赞：2)

我们先特判一下：

$x$ 和 $y$ 之间是否连通，若不连通，直接输出 nan 即可。

$x$ 和 $y$ 之间若存在正环，直接输出 inf 即可。
## 思路：

对于找环，我们可以直接用 Bellman-Ford 处理，边记录一个数组 $dis$，$dis_i$ 表示 $i$ 点到源点的最短距离。

处理连通性，我们可以运用到强连通分量的思路。处理每个点所在连通分量的编号。特判两个点的值是否相同。

然后对于每次询问，输出两个点的 $dis$ 值之差即可。

## 代码：

提示：请不要直接抄袭。


```cpp
#include<iostream>
#define int long long
#define PII pair<int,int>

using namespace std;
const int N=1e6+5;
int n,m,q; 
vector<PII> ed[N];
bool vis[N];
int belong[N],idx;
bool in_circle[N];
void tarjan(int now){
	vis[now]=1;
	for(auto p:ed[now]){
		int v=p.first;
		int w=p.second;
		if(!vis[v]){
			dis[v]=dis[now]+w;
			tarjan(v);
		}
		else if(dis[v]!=dis[now]+w){
			in_circle[idx]=1;
		}
	}
}
signed main() {
	cin>>n>>m>>q;
	while(m--){
		int u,v,w;
		cin>>u>>v>>w;
		ed[u].push_back({v,w});
		ed[v].push_back({u,-w});
	}
	int u=0;
	for(int i=1;i<=n;++i){
		if(!vis[i]){
			idx++;
			belong[i]=idx;
			tarjan(i);
		}
	}
	while(q--) {
		int u,v;
		cin>>u>>v;
		if(belong[u]!=belong[v]){
			cout<<"nan\n";
		}
		else if(in_circle[belong[u]]){
			cout<<"inf\n";
		}
		else cout<<dis[v]-dis[u]<<'\n';
	}
	retur 0;
}
```

---

## 作者：PineappleSummer (赞：2)

这题几个重要结论还是好想的吧。

1. 如果 $x$ 和 $y$ 不在一个连通块内，肯定无法到达，输出 `nan`。
2. 如果 $x$ 到 $y$ 的路径上存在正环，那么可以挣得无限的分数，输出 `inf`。
3. 若 $x$ 到 $y$ 只存在边权和为 $0$ 的环，则 $x$ 到 $y$ 路径唯一，这时才输出最大得分。

对于判 `nan`，可以对每个连通块用不同颜色标记，再进行判断。

对于判 `inf`，只需 DFS 判断到这个点的多条路径长度是否相同即可。

对于距离，DFS 的时候顺便记录一个 $dis$，用 $dis$ 相减便可得到最终距离。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long LL;
typedef pair <int, int> pii;
const int N = 1e6 + 10;
int n, m, q, col, dis[N], c[N], f[N];
bool vis[N];
vector <pii> G[N];
void dfs (int u) {
    c[u] = col;
    for (auto [v, w] : G[u]) {
        if (!vis[v]) dis[v] = dis[u] + w, vis[v] = 1, dfs (v);
        else if (dis[v] != dis[u] + w) f[col] = 1;
    }
}
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n >> m >> q;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        G[u].push_back ({v, w});
        G[v].push_back ({u, -w});
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i]) col ++, vis[i] = 1, dfs (i);
    for (int u, v; q--;) {
        cin >> u >> v;
        if (c[u] != c[v]) cout << "nan\n";
        else if (f[c[u]]) cout << "inf\n";
        else cout << dis[v] - dis[u] << '\n';
    }
    return 0;
}
```

---

## 作者：N_Position (赞：1)

# AT_abc280_f
## 分析

几个显然的性质：

- 不在同一个连通块中的两个节点互相不可到达；
- 若两个点在同一个连通块中，若这个连通块存在正环，则最大距离一定为 `inf`。
- 一个连通块中，有正环一定有负环，反之亦然。

前两个性质显然，最后一个简单证明：

若有正环，则正环所对应的相反的边，每一条边的边权都相反，因此这个环一定是负环。

- 推论一：任意一个没有正环的连通块中，任意两个点之间的所有简单路径的长度都相等。

推论一证明：

若存在两条路径长度不相等，则第一条路径与第二条路径的反路径构成负环或正环，与假设矛盾。所以不存在两条起点终点相同，路径长度不同的两条路径。

- 推论二：最大路径为简单路径，如不为简单路径，则另一条存在简单路径与其等价。

推论二证明：

若最大路径不为简单路径，则路径中必定存在环，由性质三可知，这个环的长度为 $0$，则存在另一条简单路径即为最大路径。

- 推论三：任意一个没有正环的连通块中，任意两个点之间的简单路径长度即为最大路径长度。

推论三证明：

因为最大路径为简单路径，由推论一知，所有简单路径的长度均相等，得证。

综上所述，`inf` 和 `nan` 的判断较为简单，否则：

设两点为 $A$ 和 $B$，其中一条简单路径上的中间点 $C$，若我们已经知道 $dis_{C,A}$ 和 $dis_{C,B}$ 则 $dis_{A,B} = dis_{C,B} - dis_{C,A}$，有点像向量。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
vector<pair<int,int> > e[N];
int belong[N],cnt = 0;
ll dis[N];
bool is_inf[N],vis[N];
void add(int u,int v,int w){
	e[u].push_back(make_pair(v,w));
	e[v].push_back(make_pair(u,-w));
}
void dfs(int u){
	vis[u] = true;
	belong[u] = cnt;
	for(auto it:e[u]){
		int v = it.first;
		int w = it.second;
		if(!vis[v]){
			dis[v] = dis[u] + w;
			dfs(v);
		}else if(dis[v] != dis[u] + w){
			is_inf[cnt] = true;
		}
	}
}
int main(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			cnt ++;
			dfs(i);
		}
	}
	for(int i=1;i<=q;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		if(belong[x] != belong[y]){
			puts("nan");
		}else if(is_inf[belong[x]]){
			puts("inf");
		}else{
			printf("%lld\n",- dis[x] + dis[y]);
		}
	}
}
```

---

## 作者：lfxxx (赞：1)

算是比较有意思的题目。

首先不难发现，假若连通块内存在正环，一定可以跑到正无穷，假若存在负环，则一定可以倒着跑变成正环因此也是正无穷。

然后考虑在连通块内先用并查集建出一棵生成树，接着加入剩下的边，假若构成了正环或者负环那么就是正无穷，否则一个边权和为 $0$ 的环加了之后不会改变两点的距离，因此最后只要算两点在树上的距离即可。

随后发现两点最近公共祖先的贡献会被抵消，距离就是两点深度之差。

因此就有一个简单的 $O(n + m \log n + q)$ 的做法了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5+114;
int fa[maxn];
int dep[maxn];
int E[maxn],w[maxn];
int col[maxn],cl,q;
int infty[maxn];
vector< pair<int,int> >edge[maxn];
int n,m;
void dfs(int u,int father){
	col[u]=cl;
	for(pair<int,int> nxt:edge[u]){
		if(nxt.first==father) continue;
		dep[nxt.first]=dep[u]+nxt.second;
		dfs(nxt.first,u);
	}
}
int dis(int u,int v){
	return dep[u]-dep[v];
}
int found(int u){
	return fa[u]=(fa[u]==u?u:found(fa[u]));
}
pair<int,int> e[maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		int u,v,c;
		cin>>u>>v>>c;
		if(found(u)!=found(v)){
			edge[u].push_back(make_pair(v,c));
			edge[v].push_back(make_pair(u,-c));
			fa[found(u)]=found(v);
		}	
		e[i].first=u,e[i].second=v;
		w[i]=c;
	}
	for(int i=1;i<=n;i++){
		if(col[i]==0){
			cl++;
			dfs(i,0);
		}
	}
	for(int i=1;i<=m;i++){
		if(dis(e[i].second,e[i].first)!=w[i]){
			infty[col[e[i].first]]=1;
		}
	}	
	while(q--){
		int x,y;
		cin>>x>>y;
		if(col[x]!=col[y]){
			cout<<"nan\n";
		}else{
			if(infty[col[x]]==1){
				cout<<"inf\n";
			}
			else{
				cout<<-dis(x,y)<<'\n';
			}
		}
	}
}
```


---

## 作者：chrispang (赞：0)

## 题目大意

给定一张 $n$ 个点，$2m$ 条边的图。其中第 $i$ 条边是由 $A_i$ 连向 $B_i$，边权为 $C_i$ 组成的。第 $i+m$ 条边是由 $B_i$ 连向 $A_i$，边权为 $-C_i$ 组成的。

之后有 $Q$ 次询问，每次询问给定两个点 $X_i,Y_i$，问从 $X_i$ 到 $Y_i$ 的路径中，边权和最大的哪条路径边权和为多少？

对于每次询问，若 $X_i$ 到不了 $Y_i$，则输出 `nan`；若 $X_i$ 到 $Y_i$ 的路径中有路径可以做到边权和有无限大，则输出 `inf`；否则，输出最大边权和。

$n\le 10^5,m\le 10^5,Q\le 10^5$。

## 题目分析

如何判断第一种情况呢？

仔细观察一下，发现只有存在两个点不在同一个连通块中，那么它们就不能互相到达，则输出 `nan`。

判断两点是否联通可以使用 `DFS` 染色或者使用并查集，此处使用第一种方法。

---

如何判断第二种情况呢？

若 $X_i,Y_i$ 在同一个连通块中，而且这个连通块内存在正环的话，那这组询问的答案就是 `inf`。

而有了负环也一定会存在正环，所以负环与正环都不能出现。

那该怎么判断是否存在正负环呢？

我们知道，`SPFA` 可以判断正负环，可惜它的时间复杂度最高能飞到 $O(nm)$，因此不考虑这种算法。

那该怎么做呢？

我们可以反向思考，一个环，不是 $0$ 环就是正负环，因此我们只要判断是否存在 $0$ 环就可以了。

可 $0$ 环又该怎么判断呢？

~~显然~~，环上任意两点之间都有两条简单路径，然后我们会发现，当环满足边权之和为 $0$ 的条件时，这两条路径的权值相同。

所以，**当一个连通块中不存在正环与负环时，块上任意两点之间不管有多少条不同路径，它们的权值都是相等的。**

总结上面的结论，我们可以发现一种解法：对于每个连通块，从块上取任意一点搜索整个块，设这个点与第 $i$ 个点的距离为 $dis_i$。根据上述结论，若没有正环，则 $dis_i$ 是唯一的。否则 $dis_i$ 将不唯一，那就说明出现了正环。

---

如何得到最终的答案呢？

由于我们已经求出了 $dis_i$，这里可以画一张图来理解一下使用 $dis$ 数组的方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/o3hltyck.png)

从中可见 $X\to Y$ 的最大边权和为 $dis_Y- dis_X$。每次询问输出 $dis_Y- dis_X$ 即可。

## 题目代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define maxn 100010
#define endl "\n"
using namespace std;

struct edge {
    int to, w;
};

int n, m, Q, coil, isco[maxn], co[maxn], dis[maxn]; //isco表示连通块有无正环、co表示一个点属于哪个连通块，dis数组见上述讲解
bool vis[maxn]; //判断一个点是否走过
vector<edge> linker[maxn];
void add(int x, int y, int w) { linker[x].push_back({ y, w }); } //加入一条边
void dfs(int x) {
    co[x] = coil; //染色
    for (auto i:linker[x]) {
        int v = i.to, w = i.w;
        if(!vis[v]) dis[v] = dis[x] + w, vis[v] = 1, dfs(v); //如果没有走过，则更新dis数组，并且进行标记，接着往下搜
        else if(dis[v] != dis[x] + w) isco[coil] = 1; //若已经走过，且dis值不唯一，说明存在正环。
    }
}

signed main() {
    cin >> n >> m >> Q;
    for (int i = 1, A, B, C; i <= m; i++) {
        cin >> A >> B >> C;
        add(A, B, C), add(B, A, -C);
    }
    for (int i = 1; i <= n; i++) if(!vis[i]) coil++, dfs(i); //给每一个连通块染色
    while (Q--) {
        int x, y;
        cin >> x >> y;
        if (co[x] != co[y])  printf("nan\n"); //两点之间无路径
        else if(isco[co[x]]) printf("inf\n"); //连通块中有正环
        else cout << dis[y] - dis[x] << endl; //两点最大边权和
    }
    return 0;
}
```

本题解借鉴了[CarroT1212](https://www.luogu.com.cn/user/319803)大佬的[题解](https://www.luogu.com.cn/article/i1h91gs8)思路，但我只是想写一篇学习笔记，求求大家不要生气呀！

---

## 作者：cwfxlh (赞：0)

## [题面传送门](https://www.luogu.com.cn/problem/AT_abc280_f)
题意不再赘述。    
我们从题目要求的回答来分析题目：   
第一种，两点不能互相到达：因为这是个无向图，所以使用并查集来判断即可。   

第二种，可以获得无限价值：即存在正环使得价值不受限制，这种情况我们可以用 dfs 来判断。因为是无向图，所以随便选这个连通块中的一个点，使用 dfs 来跑一个最短路，如果到某个点的最短路被更新了（出现了两种不同权值的路径），那么这个连通块就存在正环。    
解释一下，如果出现了两种不同权值的路径，则可以从起点出发，选择权值较大的路径到达目标点，再用权值较小的路径的逆路径走回去，这样就会导致权值之和大于 0，即存在正环。    

第三种，要求输出路径长。在第二点中我们已经分析过了，两点间如果有不同长度的路径，必定会导致正环，所以当下两点中任意一条路径均为答案。这里我们可以挑选这样一条路径：在第二点中，预处理这个连通块时，我们选择了 $s$ 作为起点来 dfs，不妨选择从 $x$ 到 $s$ 再到 $y$ 这样一条路径，权值即为：$dist[y]-dist[x]$，输出即可。    
____
思路分析完了，那么代码的内容就出来了，读入图后跑一下并查集，再把每个连通块都跑一个 dfs，如果有正环就把这个连通块标记一下。输入时直接调用即可。
____
上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,q,k1,k2,k3,head[1000003];
struct Edge{
	long long st;
	long long ed;
	long long val;
	long long nxt;
}E[2000003];
long long totE;
void addEdge(long long X,long long Y,long long Z){
	totE++;
	E[totE].st=X;
	E[totE].ed=Y;
	E[totE].val=Z;
	E[totE].nxt=head[X];
	head[X]=totE;
	return;
}
long long dist[1000003],vis[1000003],bcj[1000003],rd[1000003],sz[1000003];
void dfs(long long now){
	for(long long i=head[now];i!=0;i=E[i].nxt){
		if(vis[E[i].ed]==0){
			dist[E[i].ed]=dist[now]+E[i].val;
			vis[E[i].ed]=1;
			dfs(E[i].ed);
		}
		else{
			if(dist[E[i].ed]!=E[i].val+dist[now]){
				rd[bcj[now]]=1;
			}
		}
		if(rd[bcj[now]])return;
	}
	return;
}
long long finf(long long now){
	if(bcj[now]!=now)bcj[now]=finf(bcj[now]);
	return bcj[now];
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&q);
	for(long long i=1;i<=n;i++)bcj[i]=i;
	for(long long i=1;i<=m;i++){
		scanf("%lld%lld%lld",&k1,&k2,&k3);
		addEdge(k1,k2,k3);
		addEdge(k2,k1,-k3);
		bcj[finf(k2)]=finf(k1);
	}
	for(long long i=1;i<=n;i++)
	{
		bcj[i]=finf(i);
		sz[bcj[i]]++;
	}
	for(long long i=1;i<=n;i++){
		if(!vis[i]){
			dfs(i);
		}
	}
	while(q--){
		scanf("%lld%lld",&k1,&k2);
		if(bcj[k1]!=bcj[k2]){
			printf("nan\n");
			continue;
		}
		if(rd[bcj[k1]]){
			printf("inf\n");
			continue;
		}
		printf("%lld\n",dist[k2]-dist[k1]);
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

### 算法分析

如果两点不在同一个连通块中，则答案是 `nan`

如果两点所在的连通块里存在非零费用的环的话，则答案是 `inf`

- 从一个点 $v$ 出发，我们可以通过 `dfs` 求出 $v$ 到每个点的费用

- 从点 $v$ 到某个点的费用不唯一当且仅当存在非零费用的环

对于其他情况，所有环的费用都是 $0$，所以在任意 $\text{dfs}$ 生成树中两点之间的距离是唯一的

### 代码
```
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)

using namespace std;
using ll = long long;

struct Edge {
    int to, cost;
    Edge() {}
    Edge(int to, int cost): to(to), cost(cost) {}
};

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<Edge>> g(n);
    rep(i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, -c);
    }

    vector<ll> po(n);
    vector<int> cid(n, -1);
    vector<bool> ok;
    int cn = 0;
    auto dfs = [&](auto& f, int v, ll np=0) -> void {
        if (cid[v] != -1) {
            if (po[v] != np) ok[cn] = false;
            return;
        }
        cid[v] = cn;
        po[v] = np;
        for (auto e : g[v]) {
            f(f, e.to, np+e.cost);
        }
    }; 

    rep(i, n) {
        if (cid[i] != -1) continue;
        ok.push_back(true);
        dfs(dfs, i);
        cn++;
    }

    rep(qi, q) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (cid[a] != cid[b]) puts("nan");
        else if (!ok[cid[a]]) puts("inf");
        else cout << po[b]-po[a] << '\n';
    }

    return 0;
}
```

---

## 作者：dapingguo8 (赞：0)

### 题意

给定一张包含 $N$ 个点和 $2M$ 条边的带权有向图，对于 $1\le i \le M$，第 $i$ 条边从 $A_i$ 连向 $B_i$，边权为 $C_i$；第 $i+M$ 条边从 $B_i$ 连向 $A_i$，边权为 $-C_i$。

$Q$ 次询问两个点 $X_i,Y_i$ 间最长路。若 $X_i,Y_i$ 不连通则输出 `nan`，若最长路长度无限则输出 `inf`。

$2\le N \le 10^5,0\le M\le 10^5,1\le Q \le 10^5$

$1\le A_i,B_i,X_i,Y_i \le N,0\le C_i \le 10^9$

#### Solution

结论：

- 若 $X_i$ 和 $Y_i$ 不在同一连通块则答案为 `nan`。

- 若 $X_i$ 至 $Y_i$ 的所有不同路径长度均相同则答案为路径长度，否则答案为 `inf`。

对于第二条的证明：

假设存在两条长度不相同的从 $X_i$ 至 $Y_i$ 的路径，长度分别为 $W_1$，$W_2$。不妨设 $W_1<W_2$，由题目性质可得必然存在一条从 $Y_i$ 至 $X_i$ ，总长度为 $-W_1$ 的路径，这样就形成了一个总长度为 $W_2-W_1>0$ 的正环，因此最长路长度无限。

引申结论为同一连通块内两个点 $X_i$ 与 $Y_i$ 间所有不同路径长度均相同当且仅当这两个点所属连通块中的任意两个点均满足该性质（若有两个点不满足该性质，则从 $X_i$ 至 $Y_i$ 必然可以经过这两个点所形成的的正环，使得 $X_i$ 与 $Y_i$ 也不满足该性质），从而连通块内每个点均可以用“势能”描述：

- 对于一个连通块，设 $x$ 为其中任意一个点，令点 $x$ 的势能为 $0$，同一连通块内其他点的势能为 $x$ 至其的距离。

逐一判断每个连通块内的点是否满足势能性质，若满足则求出每个点的势能。

回答询问时先判断两个点是否位于同一连通块，是的话再判断该连通块是否满足势能性质，若不满足则答案为 `inf`，否则答案为终点势能减去起点势能。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=3e5+5;
#define int long long
struct edge{
	int u[2*M],nxt[2*M],v[2*M],l[2*M];
	int head[M],cnt;
	void add(int x,int y,int z){
		cnt++;
		u[cnt]=x;
		v[cnt]=y;
		l[cnt]=z;
		nxt[cnt]=head[x];
		head[x]=cnt;
	}
	void init(int n,int m){
		for(int i=1;i<=n;i++){
			head[i]=0;
		}
		for(int i=1;i<=m;i++){
			u[i]=v[i]=l[i]=nxt[i]=0;
		}
		cnt=0;
	}
}e;

int n,m,q,cnt;
int p[100005],d[100005],v[100005];
//p:每个点所属连通块编号
//d:每个点的势能
//v:每个点所在连通块是(0)/否(1)满足势能性质
void bfs(int u){
	queue<int>q;
	q.push(u);
	p[u]=++cnt;
	d[u]=0;
	set<int>st;
	bool dif=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		st.insert(u);
		for(int i=e.head[u];i;i=e.nxt[i]){
			int v=e.v[i];
			if(!p[v]){
				d[v]=d[u]+e.l[i];//经过一条长度为l的边则将势能加l
				q.push(v);
				p[v]=cnt;
			}
			else if(d[v]!=d[u]+e.l[i]){//不满足势能性质
				dif=1;
			}
		}
	}
	if(dif){
		for(auto it:st)v[it]=1;//若不满足势能性质则将连通块内所有点打上标记
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		e.add(x,y,z);
		e.add(y,x,-z);
	}
	for(int i=1;i<=n;i++){
		if(!p[i]){
			bfs(i);
		}
	}
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		if(p[x]!=p[y])cout<<"nan"<<endl;//不在同一连通块
		else if(v[x])cout<<"inf"<<endl;//连通块不满足势能性质
		else cout<<d[y]-d[x]<<endl;//终点势能减去起点势能
	}
}
```



---

