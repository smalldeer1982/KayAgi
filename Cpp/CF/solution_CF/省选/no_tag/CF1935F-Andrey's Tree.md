# Andrey's Tree

## 题目描述

Master Andrey loves trees $ ^{\dagger} $ very much, so he has a tree consisting of $ n $ vertices.

But it's not that simple. Master Timofey decided to steal one vertex from the tree. If Timofey stole vertex $ v $ from the tree, then vertex $ v $ and all edges with one end at vertex $ v $ are removed from the tree, while the numbers of other vertices remain unchanged. To prevent Andrey from getting upset, Timofey decided to make the resulting graph a tree again. To do this, he can add edges between any vertices $ a $ and $ b $ , but when adding such an edge, he must pay $ |a - b| $ coins to the Master's Assistance Center.

Note that the resulting tree does not contain vertex $ v $ .

Timofey has not yet decided which vertex $ v $ he will remove from the tree, so he wants to know for each vertex $ 1 \leq v \leq n $ , the minimum number of coins needed to be spent to make the graph a tree again after removing vertex $ v $ , as well as which edges need to be added.

 $ ^{\dagger} $ A tree is an undirected connected graph without cycles.

## 说明/提示

In the first test case:

Consider the removal of vertex $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1935F/326dc8cb966e19a6daecb0dbccfbaeee064df065.png)The optimal solution would be to add an edge from vertex $ 5 $ to vertex $ 3 $ . Then we will spend $ |5 - 3| = 2 $ coins.

In the third test case:

Consider the removal of vertex $ 1 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1935F/36d8650d7de797c0afd20514badf62c9e0f28a87.png)The optimal solution would be:

- Add an edge from vertex $ 2 $ to vertex $ 3 $ , spending $ |2 - 3| = 1 $ coin.
- Add an edge from vertex $ 3 $ to vertex $ 4 $ , spending $ |3 - 4| = 1 $ coin.
- Add an edge from vertex $ 4 $ to vertex $ 5 $ , spending $ |4 - 5| = 1 $ coin.

Then we will spend a total of $ 1 + 1 + 1 = 3 $ coins.

Consider the removal of vertex $ 2 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1935F/e02dc00d347b25feb8bd25ab43e8edd9a285a2c9.png)No edges need to be added, as the graph will remain a tree after removing the vertex.

## 样例 #1

### 输入

```
3
5
1 3
1 4
4 5
3 2
5
4 2
4 3
3 5
5 1
5
2 1
1 5
1 4
1 3```

### 输出

```
1 1
3 4

0 0

1 1
1 2

2 1
3 5

0 0

0 0

0 0

1 1
1 2

1 1
1 2

1 1
1 2

3 3
2 3
4 5
3 4

0 0

0 0

0 0

0 0```

# 题解

## 作者：Alex_Wei (赞：8)

### [CF1935F Andrey's Tree](https://www.luogu.com.cn/problem/CF1935F)

给一个简单的线性做法。

先考虑答案下界，显然不小于 $deg_v - 1$，是否能达到该下界呢？

考虑 $v = 1$ 或 $v = n$ 的情况，此时所有编号构成连续段。对此有一个非常经典的构造：求出每个连通块的编号最大值 $mx$，若 $mx$ 不是编号最大的点，则从 $mx$ 向 $mx + 1$ 连边。这样会连出一棵有根树，根为 $mx_i$ 最大的连通块，且从每个连通块开始不断跳父亲都会跳到该连通块，因为每个非 $mx$ 最大的点都有父亲，且父亲 $mx$ 大于其 $mx$。

对于 $v\neq 1, n$ 的情况，可类似构造。具体地，若不存在 $mx_i + 1 = v$，则使用上述方法构造即可。若存在，则还需分两种情况讨论：

- 若一部分连通块构成了 $1\sim v - 1$，另一部分连通块构成了 $v + 1\sim n$，则无论如何，连接分别属于这两部分的连通块的边的权值不小于 $2$，而这样的边至少有一条，所以答案下界为 $deg_v$。使用上述方法构造，并将 $(v - 1, v)$ 改成 $(v - 1, v + 1)$ 即可。

- 若并非上述情况，则存在连通块同时含有 $[1, v - 1]$ 和 $[v + 1, n]$ 中的点。这些连通块就是沟通 $[1, v - 1]$ 和 $[v + 1, n]$ 的桥梁。我们将连通块按照 $mx$ 是否小于 $v$ 分为两部分 $L, R$。对于 $R$ 的所有连通块，从 $mx$ 向 $mx + 1$ 连边。对于 $L$，就相反地考虑，从 $mn$ 向 $mn - 1$ 连边。这样至少连出了 $deg_v - 2$ 条边，因为不能连 $(n, n + 1)$ 和 $(1, 0)$。 

  首先要证明这样不会连出环：从 $R$ 中的连通块出发，不断跳出边，最终一定能到达 $mx = n$ 的连通块；从 $L$ 中的连通块出发，要么跳到某个 $R$ 中的连通块再跳到 $mx = n$ 的连通块，要么跳到 $L$ 中 $mn = 1$ 的连通块。

  无论是从连边方式，还是从上述证明，都可以看出此时不连通（只连了 $deg_v - 2$ 条边）当且仅当 $mn = 1$ 的连通块属于 $L$。此时只需取出 $R$ 中 $mn$ 最小的连通块，然后在 $mn$ 和 $mn - 1$ 之间连边即可：容易证明此时 $mn$ 和 $mn - 1$ 不连通。

换根 DP 计算每个点的每棵子树的 $mn$ 和 $mx$，时间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1935/submission/250571517)。

---

## 作者：H_W_Y (赞：4)

首先，贪心地想，对于每一次连边，从 $i$ 连到 $i+1$ 一定是非常优秀的，于是我们尽量都是选这样的边，那么得到的结果是 $w=m$，一定是最优的。

而并不是任何时刻我们都可以得到 $w=m$ 的结果的，比如这下面两种：

![1](https://cdn.luogu.com.cn/upload/image_hosting/19p78tvf.png?x-oss-process=image)

>  红色点的答案，$w=2,m=1$，并不能做到 $w=m$。

这是为什么呢？

容易发现，假设一个点 $u$ 有 $d$ 条出边，那么把 $u$ 删除的时候，图就变成了 $d$ 个连动块，而我们希望再一次把它变成一棵树，相当于把每一个连动块看作一个点，也就是需要 $d-1$ 条边，那么 $m=d-1$ 是一定成立的。

而在连接这 $m$ 条边中，我们尽量是用 $i \to i+1$ 的边，直到不能连的时候（即所有的 $i$ 和 $i+1$ 都在同一个连动块内部），像图中这种情况，我们就需要从 $u-1$ 连到 $u+1$（它们两个一定不在同一个连动块内，可以画图理解），此时的 $w=m+1$。容易发现，这是一种合法且最优的方案。

题目中需要我们构造，那么我们现在的问题就是如何找到并用上 $i \to i+1$ 的边。

以下的分析默认在以 $u$ 为根的子树中进行，而其所有子树的答案已经计算过了。

对于每一条 $i \to i+1$ 的边，有两类：

- 从 $u$ 的子树连到 $u$ 的子树。
- 从 $u$ 的子树连到 $u$ 子树外面。

对于第一种情况，容易发现这两个点 $i,i+1$ 的 LCA 一定是 $u$，于是我们可以提前用 vector 存下 LCA 为 $u$ 的相邻点对。

对于第二种情况，这两个点 $i$ 和 $i+1$ 的 LCA 一定是在 $u$ 的祖先中，而这个祖先越早越好，因为这样它就不会那么早被淘汰（我们的 dfs 是从下到上统计的），直接用一个数组记录一下就可以了。

想到这里，大概就可以写了。

LCA 是可以预处理出来的，你怎么求都可以，笔者写得是用 dfn 序 $O(n \log n) - O(1)$ 的 LCA。

是否在连动块内的判断可以用并查集完成，实际实现的时候你可以假设 $u$ 节点的并查集就代表 $u$ 子树外面的那个连动块，这样就可以边统计答案边更新子树信息，方便以后的 dfs。

每次的构造方案主要就是上面的两种情况，如果存在这样的一条边，并且它所在的两个连动块不连通，那么就直接加入答案就可以了。

最后如果少一条边，就直接加入 $u-1$ 到 $u+1$ 的边就可以了，注意这里还需要用并查集合并一下。

感觉没有什么实现难度，由于 $i,i+1$ 这样的点对只会有 $n-1$ 对，枚举总次数是 $O(n)$ 的，所以总的时间复杂度是 $\mathcal O(n + n\log n)$，瓶颈在于求 LCA。

似乎不用任何数据结构，只要会求 LCA 和并查集就可以了。

```cpp
int T,n,dep[N],f[N];
vector<int> G[N],H[N];//H 数组记录 LCA 为 u 的 (i,i+1)，也就是第一类边
struct Answer{
  int w,m;
  vector<pii> g; 
  void init(){w=m=0,g.clear();}
}ans[N];
struct node{
  int u,v,d;//d 记录 LCA 的 dep
  node(int U=0,int V=0,int D=0){u=U,v=V,d=D;}
  bool operator <(const node &rhs)const {return d<rhs.d;}
}c[N];//c 数组维护每一个点和子树外的节点连接的最优点对，LCA 在越上面越优秀

void init(){for(int i=1;i<=n;i++) G[i].clear(),H[i].clear(),ans[i].init(),c[i]=node(0,0,n+1),f[i]=i;}
void add(int u,int v){G[u].pb(v),G[v].pb(u);}

namespace Tr{//dfn 序求 LCA
  int idx=0,dfn[N],lg[N],st[21][N];
  void dfs(int u,int fa){
  	dfn[u]=++idx,st[0][idx]=fa,dep[u]=dep[fa]+1;
  	for(auto v:G[u]) if(v!=fa) dfs(v,u);
  }
  int Min(int u,int v){return dfn[u]<dfn[v]?u:v;}
  void init(){
    idx=0,dfs(1,0);lg[1]=0;
    for(int i=2;i<=n;i++) lg[i]=lg[i/2]+1;
    for(int i=1;i<=lg[n]+1;i++)
      for(int j=1;j+(1<<i)-1<=n;j++)
        st[i][j]=Min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
  }
  int LCA(int u,int v){
    if(u==v) return u;
    u=dfn[u],v=dfn[v];
    if(u>v) swap(u,v);
    int s=lg[v-u];
    return Min(st[s][u+1],st[s][v-(1<<s)+1]);
  }
}

int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
void merge(int u,int v){//并查集
  u=find(u),v=find(v);
  if(u!=v) f[u]=v;
}

void dfs(int u,int fa){
  ans[u].m=ans[u].w=G[u].size()-1;
  for(auto v:G[u]) if(v!=fa){
  	dfs(v,u),c[u]=min(c[u],c[v]);
    if(c[v].d<dep[u]) merge(v,u),ans[u].g.pb({c[v].u,c[v].v});//可能存在的第二类边
  }
  for(auto i:H[u]) if(i!=u&&i+1!=u&&find(i)!=find(i+1)) merge(i,i+1),ans[u].g.pb({i,i+1});//连第一类边
  if((int)ans[u].g.size()<ans[u].m){//(u-1,u+1) 的边
  	++ans[u].w;ans[u].g.pb({u-1,u+1});
  	for(auto v:G[u]) if(v!=fa) merge(v,u);
  }
}

void sol(){
  cin>>n;init();
  for(int i=1,u,v;i<n;i++) cin>>u>>v,add(u,v);
  Tr::init();
  for(int i=1;i<=n;i++){//预处理出 (i,i+1) 点对
  	if(i>1) c[i]=min(c[i],node(i,i-1,dep[Tr::LCA(i,i-1)]));
  	if(i<n) c[i]=min(c[i],node(i,i+1,dep[Tr::LCA(i,i+1)])),H[Tr::LCA(i,i+1)].pb(i); 
  }
  dfs(1,0);
  for(int i=1;i<=n;i++){
  	cout<<ans[i].w<<' '<<ans[i].m<<'\n';
  	for(auto j:ans[i].g) cout<<j.fi<<' '<<j.se<<'\n';
    cout<<'\n';
  }
}

int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>T;
  while(T--) sol();
  return 0;
}
```

~~目前 CF 最短解，比较神秘。~~

---

## 作者：zhongpeilin (赞：2)

## 题目大意：
有一棵树，定义从 $a$ 向 $b$ 连一条无向边的代价为 $|a - b|$，现在对于每个 $1\le i \le n$，求出假如把 $i$ 点和与 $i$ 相连的边都删掉，要从新让他变成一棵树的最小代价。  
## 解题思路：
对于第 $i$ 个点来说，所需要加的边数一定是度数减一。  
然后我们一定是尽可能得让边的代价都为 `1`，所以要分类讨论。  
设将 $i$ 删掉后，原本与 $i$ 相连的点的集合的联通块的最大值为 $mx$ 的集合，$mn$ 为最小值的集合。  
1. 当 $i = 1$ 或 $i = n$ 时，我们就有种构造方案， 对于每个连通块 $id$，建一条 $mx_{id} \to mx_{id}+1$ 的边，由于是 $mx$，所以不会存在连完后出环的，因为如果有环说明 $mx_{id}+1$ 会主动向 $mx$ 连，于是 $mx_{id}+1$ 比 $mx_{id}$ 小，肯定无解。  
2. 当没有 $id$ 满足 $mn_{id} < i < mx_{id}$ 时，也就是说对于每个连通块一定都小于 $i$ 或都大于 $i$ 时，也是和上面同理的，因为可以将它看成两个不相交的集合，而对于左集合来说，就像 $i = n$ 时，右集合时，可以看成 $i = 1$。只不过要判断一下当 $i - 1$ 要连向 $i$ 的话，就让他连向 $i + 1$，这样一定是以最优策略合并左右集合的，而最小代价为 $i$ 的度数。  
3. 当有 $id$ 满足 $mn_{id} < i < mx_{id}$ 时，也就是说有至少一个连通块左右集合都有点，那么我们将 $mx$ 小于 $i$ 的分左集合，其他的分给右集合，那么右集合和上面一样，而左集合就是 $mn_{id} - 1 \to mn_{id}$。但我们会发现，有可能 `1` 在左集合里，会少连一条边，而 $n$ 一定在右集合，一定不会连边，这样是度数减二条边，也就是我们现在没有保证左右连通，那么我们可以找到右集合里的 $mn$ 最小值，再与他前一个位置相连。它前面的一定都是左集合的，因为 `1` 在左集合里。  

那么我们现在就只需考虑 $mn$ 和 $mx$ 了，不妨设 $g_{x}$ 存 $x$ 子树里的最小最大值，然后 $f_{x}$ 表示 $x$ 子树以外的最小最大值，那么换根即可。  
$O(n)$。
## CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
int res[200005];
int n, fmn[200005], fmx[200005], gmn[200005], gmx[200005];
vector<int> g[200005];
vector<pair<int, int> > ans[200005];

void dfs_g(int x, int fa){ //预处理 g 
	gmn[x] = gmx[x] = x;
	for(auto y : g[x]) {
		if(y == fa) continue;
		dfs_g(y, x);
		gmn[x] = min(gmn[x], gmn[y]);
		gmx[x] = max(gmx[x], gmx[y]);
	}
}

void dfs_f(int x, int fa){ //f换根，考虑到f[x]=min/max (f[fa], fa, g[x的兄弟])，所以在fa算。 
	int mn = 1e9, idmn = 0, mnn = 1e9, mx = 0, idmx = 0, mxn = 0;
	for(auto y : g[x]){
		if(y == fa) continue;
		if(gmn[y] <= mn){ //因为是 g[x的兄弟]，所以算 g 最小时要维护最小次小。 
			mnn = mn;
			mn = gmn[y];
			idmn = y; //记录最小值，这样算他的f时就用次小值 
		} else if(gmn[y] < mnn){
			mnn = gmn[y];
		}
		
		if(gmx[y] >= mx){ //因为是 g[x的兄弟]，所以算 g 最大时要维护最大次大。
			mxn = mx;
			idmx = y;
			mx = gmx[y];
		} else if(gmx[y] > mxn){
			mxn = gmx[y];
		}
	}
	for(auto y : g[x]){
		if(y == fa) continue;
		fmn[y] = min({x, fmn[x], (idmn == y ? mnn : mn)}); //更新 
		fmx[y] = max({x, fmx[x], (idmx == y ? mxn : mx)});
		dfs_f(y, x);
	}
}

void dfs(int x, int fa){
	bool flag = false;
	for(auto y : g[x]){ //判断有没有子树在两边都有。 
		if(y == fa){
			if(fmx[x] > x && fmn[x] < x) flag = 1;
		} else {
			if(gmx[y] > x && gmn[y] < x) flag = 1;
		}
	}
	if(x == 1 || x == n){  
		for(auto y : g[x]){
			if(y == fa){
				if(fmx[x] + 1 <= n && fmx[x] + 1 != x){ //mx => mx+1 
					ans[x].push_back({fmx[x], fmx[x] + 1});
				}
			} else {
				if(gmx[y] + 1 <= n && gmx[y] + 1 != x){ //注意这里是g[y]，上面是f[x] 
					ans[x].push_back({gmx[y], gmx[y] + 1});
				}
			}
		}
		res[x] = g[x].size() - 1; //代价 
	} else if(!flag){
		for(auto y : g[x]){
			if(y == fa){
				if(fmx[x] + 1 != x && fmx[x] != n){
					ans[x].push_back({fmx[x], fmx[x] + 1});
				}
			} else {
				if(gmx[y] + 1 != x && gmx[y] != n){
					ans[x].push_back({gmx[y], gmx[y] + 1});
				}
			}
		}
		ans[x].push_back({x - 1, x + 1}); //连接 
		res[x] = g[x].size(); //有一个2的边。 
	} else {
		vector<int> val;
		for(auto y : g[x]){ //左集合 
			if(y == fa){
				if(fmx[x] < x) val.push_back(fmn[x]); 
			} else {
				if(gmx[y] < x) val.push_back(gmn[y]);
			}
		}
		for(auto it : val){ //mn-1=>mn 
			if(it != 1){
				ans[x].push_back({it - 1, it});
			}
		}
		val.clear();
		int minn = 1e9;
		for(auto y : g[x]){ //右 
			if(y == fa){
				if(fmx[x] > x) {
					val.push_back(fmx[x]);
					minn = min(minn, fmn[x]); //还要维护一下最小值 
				}
			} else {
				if(gmx[y] > x) {
					val.push_back(gmx[y]);
					minn = min(minn, gmn[y]);
				}
			}
		}
		for(auto it : val){
			if(it != n){
				ans[x].push_back({it, it + 1}); //连 
			}
		}
		res[x] = g[x].size() - 1;
		if(minn != 1) { //注意有条件，当minn=1时一定有deg-1条边 
			ans[x].push_back({minn - 1, minn});
		}
	}
	for(auto y : g[x]){
		if(y == fa) continue;
		dfs(y, x);
	}
}
void solve(){
	cin >> n;
	for(int i = 1; i <= n; i++) ans[i].clear(), g[i].clear();
	for(int i = 1; i < n; i++){
		int x, y;
		cin>> x>> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs_g(1, 0);
	fmn[1] = 1e9, fmx[1] = 0; //初始化 
	dfs_f(1, 0);
	dfs(1, 0);
	
	for(int i = 1; i <= n; i++){
		cout << res[i] << " "<< g[i].size() - 1 << endl;
		for(auto it : ans[i]){
			cout << it.first << " " << it.second << endl;
		}
		cout << endl;
	}
}
int main(){
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：henrytb (赞：2)

首先考虑答案长成什么样子。

发现在绝大多数情况中，都可以仅使用长度为 $1$ 的边来使图重新连通。唯一的例外是，假设删去点 $i$，必须使用 $(i - 1, i + 1)$ 这条长度为 $2$ 的边的情况。

因此删去某个点后答案便是这个点的度数或其度数 $ - 1$。

判断方法很简单，将所有形如 $(i, i + 1)$ 的边拿出来挂在这两个点在原树上 $\mathrm{lca}$ 处，然后删掉树上的一个点 $u$ 相当于需要合并这个点的子树们以及它上方的部分。首先将子树们用刚刚储存在 $\mathrm{lca} = u$ 处的长度为 $1$ 的边尽可能合并，然后对于每个子树维护出它往上能否有一条长度为 $1$ 的边通向 $u$ 的上方部分。将这些边添加完（用并查集判断是否需要添加）之后，假如当前还是有两个连通块，说明我们被迫使用 $(u - 1, u + 1)$ 这条边。否则就没事。

实现起来很容易，`dfs` 时每次都可以继承子树的并查集信息。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 2e5 + 5;
int n, _;
vector<int> e[N];
int sum[N], cnt[N];
vector<pair<int, int>> ans[N];
int f[N][18], dep[N];
void dfs1(int u, int fa) {
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    rep(i, 1, 17) f[u][i] = f[f[u][i - 1]][i - 1];
    for (auto &v: e[u]) if (v != fa) {
        dfs1(v, u);
    }
}
inline int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    per(i, 17, 0) if (dep[f[u][i]] >= dep[v]) u = f[u][i];
    if (u == v) return u;
    per(i, 17, 0) if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    return f[u][0];
}
tuple<int, int, int, int> thst[N];
vector<pair<int, int>> lcs[N];
int ff[N];
int find(int x) { return x == ff[x] ? x : ff[x] = find(ff[x]); }
void dfs(int u, int fa) {
    int sons = 0;
    for (auto &v: e[u]) if (v != fa) {
        ++sons;
        dfs(v, u);
        thst[u] = min(thst[u], thst[v]);
    }
    for (auto &[x, y]: lcs[u]) {
        if (x == u || y == u) continue;
        int xx = find(x), yy = find(y);
        if (xx != yy) {
            ff[xx] = yy;
            ++cnt[u]; ++sum[u];
            ans[u].emplace_back(x, y);
        }
    }
    if (fa) {
        for (auto &v: e[u]) if (v != fa) {
            if (get<0>(thst[v]) < dep[u]) {
                int tfa = find(v);
                if (tfa != u) {
                    ff[tfa] = u;
                    ++cnt[u]; ++sum[u];
                    ans[u].emplace_back(get<2>(thst[v]), get<3>(thst[v]));
                }
            }
        }
        if (cnt[u] < sons) {
            ++cnt[u]; sum[u] += 2;
            ans[u].emplace_back(u - 1, u + 1);
        }
    } else {
        if (cnt[u] < sons - 1) {
            ++cnt[u]; sum[u] += 2;
            ans[u].emplace_back(u - 1, u + 1);
        }
    }
    for (auto &v: e[u]) if (v != fa) ff[v] = u;
}
int main() {
    for (scanf("%d", &_); _; --_) {
        scanf("%d", &n);
        rep(i, 1, n) e[i].clear(), ans[i].clear(), lcs[i].clear(), sum[i] = cnt[i] = 0;
        iota(ff + 1, ff + n + 1, 1);
        rep(i, 2, n) {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].emplace_back(v);
            e[v].emplace_back(u);
        }
        dfs1(1, 0);
        rep(i, 1, n) thst[i] = make_tuple(0x3f3f3f3f, 0, 0, 0);
        rep(i, 1, n - 1) {
            int lc = lca(i, i + 1);
            thst[i] = min(thst[i], make_tuple(dep[lc], lc, i, i + 1));
            thst[i + 1] = min(thst[i + 1], make_tuple(dep[lc], lc, i + 1, i));
            lcs[lc].emplace_back(i, i + 1);
        }
        dfs(1, 0);
        rep(i, 1, n) {
            printf("%d %d\n", sum[i], cnt[i]);
            for (auto &[x, y]: ans[i]) printf("%d %d\n", x, y);
            puts("");
        }
    }
    return 0;
}
```

---

## 作者：sunkuangzheng (赞：2)

$\textbf{CF1935F *3000}$

> - 给定一棵树，对于 $i \in [1,n]$ 求出以下问题的答案：
>   - 将点 $i$ 及所有 $i$ 相连的边删除后，定义一条连接 $u,v$ 的额外边的边权是 $|u-v|$，额外边不能连接 $i$。
>   - 用额外边将除点 $i$ 外的点重新连成一棵树，最小化边权和。
> - $1 \le n \le 2 \cdot 10^5$。

由于作者没有写按秩合并，以下并查集复杂度均视为 $\mathcal O(\log n)$。

假设我们在求解节点 $i$ 的答案，断开 $i$ 后考虑连通块的形态。

显然答案的下界是 $d_i-1$，$d_i$ 即节点 $i$ 的度数，能达到这个下界当且仅当每条边的权值都是 $1$。

我们先将所有边权为 $1$ 的连接两个不连通子树的边连接，容易发现 $[1,i-1]$ 和 $[i+1,n]$ 中的节点已经各自连通。那么，如果存在一条树边 $u,v$ 满足 $u \in [1,i-1],v \in [i+1,n]$，我们的答案就是 $d_i-1$。否则，我们直接连接 $i-1,i+1$，代价为 $d_i-2+1=d_i$。检验这个方法很多，这里提供复杂度较为优秀、实现简单的做法：判断是否存在一个连通块，使得 $\min < i,\max > i$。一个连通块形如一个子树，或是子树外的全部，那么 dfs 序配合 ST 表即可求 $\min,\max$，时间复杂度 $\mathcal O(n \log n)- \mathcal O(1)$。

当然这道题没有到这里结束，我们还需要给出构造，这也是本题的难点。

考虑如果直接暴力模拟上述过程，用并查集判断，复杂度将是 $\mathcal O(n^2 \log n)$，不可接受。

考虑设 $mx_u,mn_u$ 表示 $u$ 子树内的最大最小值（以 $i$ 为根），边 $(mx_u,mx_u+1)$ 和 $(mn_u-1,mn_u)$ 一定连接了**原树**上两个不同的连通块，同时连接所有上述边后整张图连通，但是我们需要去除环。如果直接判断两个点是否在一个连通块里，就需要将树边先在并查集里合并，每次暴力合并复杂度还是会炸，此时可以线段树分治套可撤销并查集维护树边的连通性，然后再判断每条边是否需要加入即可，时间复杂度 $\mathcal O(n \log^2 n)$。

但是上面的做法太麻烦，事实上，我们连一条边只需要合并边的端点所在的子树，找到每个点所在的子树可以用 dfs 序上二分或者倍增，然后合并即可。总复杂度 $\mathcal O(n \log n)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 06.03.2024 09:58:50
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,u,v,dfn[N],cnt,nfd[N],siz[N],fa[N],mx[N],mn[N]; vector<int> g[N];
struct dsu{
    int fa[N];
    void init(int n){for(int i = 1;i <= n;i ++) fa[i] = i;}
    int fd(int x){return x == fa[x] ? x : fa[x] = fd(fa[x]);}
    bool mg(int x,int y){
        int fx = fd(x),fy = fd(y); 
        if(fx != fy) return fa[fx] = fy,1;
        else return 0;
    }
}d;
struct ST{
    int st[22][N],op;
    int cmp(int x,int y){return op ? max(x,y) : min(x,y);}
    void build(int _op,int *a){
        op = _op;
        for(int i = 1;i <= n;i ++) st[0][i] = a[i];
        for(int j = 1;j <= __lg(n);j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)
            st[j][i] = cmp(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }int qry(int l,int r){
        if(l > r) return (op ? 0 : 1e9);
        int k = __lg(r - l + 1);
        return cmp(st[k][l],st[k][r-(1<<k)+1]);
    }
}A,B;
void dfs(int u,int f){
    dfn[u] = ++cnt,nfd[cnt] = u,siz[u] = 1,fa[u] = f;
    for(int v : g[u]) if(v != f) dfs(v,u),siz[u] += siz[v];
}void los(){
    cin >> n;
    for(int i = 1;i <= n;i ++) g[i].clear(); cnt = 0;
    for(int i = 1;i < n;i ++) cin >> u >> v,g[u].push_back(v),g[v].push_back(u);
    dfs(1,0),A.build(1,nfd),B.build(0,nfd);
    for(int i = 1;i <= n;i ++){
        if(g[i].size() == 1) {cout << "0 0\n";continue;} vector<int> fk,sb;
        int k = g[i].size(),ans = k - 1,fg = (i == 1 || i == n),ms = 1e9;
        auto ck = [&](int j){return mx[j] >= i && mn[j] <= i;};
        for(int j : g[i])
            if(j == fa[i]) mx[j] = max(A.qry(1,dfn[i]-1),A.qry(dfn[i]+siz[i],n)),
                           mn[j] = min(B.qry(1,dfn[i]-1),B.qry(dfn[i]+siz[i],n)),
                           fg |= ck(j),ms = dfn[i] + siz[i];
            else sb.push_back(dfn[j]),mx[j] = A.qry(dfn[j],dfn[j]+siz[j]-1),mn[j] = B.qry(dfn[j],dfn[j]+siz[j]-1),fg |= ck(j);
        if(!fg) ans ++; 
        cout << ans << " " << k - 1 << "\n"; 
        if(!fg) cout << i - 1 << " " << i + 1 << "\n";
        sort(sb.begin(),sb.end());
        auto get = [&](int x){
            if(x >= ms || x < sb.front()) return k;
            else return (int)(upper_bound(sb.begin(),sb.end(),x) - sb.begin());
        }; d.init(k);
        auto mg = [&](int x,int y){
            if(x != i && y != i && x >= 1 && y <= n) if(d.mg(get(dfn[x]),get(dfn[y]))) cout << x << " " << y << "\n";
        };
        for(int j : g[i]) mg(mn[j]-1,mn[j]),mg(mx[j],mx[j]+1);
    }
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

## 作者：fast_photon (赞：1)

## CF1935F  

### 1. 题意  
给定一棵树，对于每个顶点 $v$，问把它删掉后，剩余部分连成一棵树的最小代价，并给出最小代价的方案。在 $(i,j)$ 之间连边的代价是 $|i-j|$。  
$5\le n\le 2\times 10^5$。  

### 2. 分析  
对于一个顶点 $v$，我们设它的度数为 $d_v$。  
容易发现，答案的最小值不会小于 $d_v-1$。  
若 $v$ 没有被删除，则对于所有形如 $(i,i+1)$ 的边跑最小生成树一定能做到 $d_v-1$。  
所以可以直接对所有形如 $(i\neq v,i+1\neq v)$ 的边和 $(v-1,v+1)$ 跑最小生成树。但这样复杂度太高了，无法接受。  

通过最小生成树的思路，发现答案不会超过 $d_v$。如果两个连通块无法通过 $(i\neq v,i+1\neq v)$ 形式的边连通，则一定是 $<v$ 一个块，$>v$ 一个块。  
否则找到与 $1$（$v=1$ 时取 $2$）不连通的第一个点，则它前面一个和 $1$ 连通，故它和 $1$ 连通。从末尾再来一次，可以发现如果不连通一定是 $<v$ 一个块，$>v$ 一个块。  
同时，此时任何一个子树的编号没有跨块。否则可以取到 $d_v-1$。  

现在我们已经会了计算答案，考虑如何构造方案。  
直接枚举每个点，看它左右有没有不同子树的，并查集维护。复杂度过高，无法接受。  
考虑少枚举一些点。比如，仅仅枚举每个子树的最大最小编号的点。这样一定是对的吗？  
从 $1$（$v=1$ 时取 $2$）开始，找到第一个没有通过这样的边与之连通的。由于同一个子树的被连通了，所以这个点之前没有和它在同一个子树的。所以它是子树最小值，可以向它前一个点连边，除非 $i=v+1$。  
同理倒着来一次，利用最大值证明，这样的边可以连通 $[v+1,n]$。  

如果最小代价是 $d_v$，那么再连通 $v-1,v+1$ 即可。否则，不需要任何额外连边，因为左侧和右侧内部已经连通，而有至少一个子树连通了左侧和右侧。  

**一些技巧**  
由于这是一棵无根树，对于“每个子树”这样的表述，我们是把顶点 $v$ 当作根来看的。直接维护复杂度无法接受，可以随意钦定一个根把树“拎起来"做换根 DP。  

实现上，我钦定了 $1$ 为根。代码注释中，对于一个节点，内部子树是 1 为根它拥有的子树，外部子树是 1 为根它没有，它自己为根才有的（对于 1 不存在，对于其他点包含 1）的子树。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#define maxn 200005

using namespace std;

int n, l[maxn], r[maxn], cnt[maxn], siz[maxn], val[maxn], rep[maxn], f[maxn], ft[maxn], vst[maxn], mx1[maxn], mx2[maxn], mn1[maxn], mn2[maxn];
int iv[maxn];
int _G_T;

int hg[maxn], tg[maxn], ha[maxn], eg, eq, ea;

struct edge { //存图和答案用的，单双向链表
	int v, u, next;
} g[maxn * 2], ans[maxn * 2];

void addg(int id, int u, int v = -1) { //图，双向，v u next（结构体中）分别为边到达的点，上一条边，下一条边
	if(hg[id] != -1) g[hg[id]].u = eg;
	else tg[id] = eg;
	g[eg] = (edge){u, v, hg[id]};
	hg[id] = eg++;
}
void adda(int id, int u, int v) { //答案，单向，v u next（结构体中）分别为答案边的 u v 和删除这个点方案的下一条边。
	ans[ea] = (edge){u, v, ha[id]};
	ha[id] = ea++;
}

struct Stack { //手写栈
	int n, a[maxn];
	Stack() {
		n = 0;
	}
	bool empty() {
		return n == 0;
	}
	void push(int x) {
		a[n++] = x;
	}
	int pop() {
		return a[--n];
	}
	void clear() {
		n = 0;
	}
	int front() {
		return a[n - 1];
	}
} q, p;
inline int find(int x) { //并查集一号，用来枚举点时合并子树
	return f[x] == x ? x : f[x] = find(f[x]);
}
bool t(int x, int y) { //并查集一号的合并
	int fx = find(x), fy = find(y);
	if(fx == fy) return false;
	f[fx] = fy;
	return true;
}
inline int frep(int x) { //并查集二号，用于判定每个点所在的子树
	return rep[x] == x ? x : rep[x] = frep(rep[x]); 
}
inline void dfs(int id, int fr = 0) { //第一次 dfs 算最小值和子树内编号最大最小值
	int cnt0 = 0, cnt1 = 0;
	int deg = id == 1 ? 0 : 1;  //钦定了 1 为根，若是根没有连向父节点的度数，否则有 1
	for(int j = hg[id]; ~j; j = g[j].next) {
		int v = g[j].v;
		if(v == fr) continue;
		ft[v] = id;
		dfs(v, id);
		deg++;
		siz[id] += siz[v];
		l[id] = min(l[id], l[v]); //子树编号min
		r[id] = max(r[id], r[v]); //max
		if(r[v] < id) cnt0 += siz[v];
		if(l[v] > id) cnt1 += siz[v];
	}
	cnt[id] = deg - 1;
	val[id] = deg - 1;
	if((cnt0 == id - 1 || cnt1 == n - id) && id != 1 && id != n) { //若内部子树完全占满了 id 的一侧，则需要额外代价。
		val[id]++;
		adda(id, id - 1, id + 1);
	}
	siz[id]++;
}

void dfs1(int id, int fr = 0) {
	mn1[id] = n + 1, mn2[id] = n + 1, mx1[id] = 0, mx2[id] = 0;//换根，记录每个点子树的最小次小值
	for(int j = hg[id]; ~j; j = g[j].next) {
		int v = g[j].v;
		int l0v = l[v], r0v = r[v];
		if(v == fr) { //继承父节点的值，但是要扣掉自己这个子树，这就是最大最小值维护前两最的原因
			l0v = l[id] == mn1[fr] ? mn2[fr] : mn1[fr];
			r0v = r[id] == mx1[fr] ? mx2[fr] : mx1[fr];
			l0v = min(l0v, id);
			r0v = max(r0v, id);
		}
		if(l0v < mn1[id]) mn2[id] = mn1[id], mn1[id] = l0v;
		else if(l0v < mn2[id]) mn2[id] = l0v;
		if(r0v > mx1[id]) mx2[id] = mx1[id], mx1[id] = r0v;
		else if(r0v > mx2[id]) mx2[id] = r0v;
	}
	for(int j = hg[id]; ~j; j = g[j].next) {
		int v = g[j].v;
		if(v == fr) continue;
		dfs1(v, id);
	}
}

int rfep(int x) { //判断是内部子树还是外部子树
	int p0 = frep(x);
	if(iv[p0]) return p0;
	return 0;
}

void dfs2(int id, int fr = 0) { //方案记录
	for(int j = hg[id]; ~j; j = g[j].next) {
		int v = g[j].v;
		if(v == fr) continue;
		dfs2(v, id); //先搜儿子，这样子树的判定才能生效
		f[v] = v; //重置并查集一号
	}
	for(int j = hg[id]; ~j; j = g[j].next) {
		int v = g[j].v;
		if(v == fr) continue;
		iv[v] = 1; // 记录儿子，这样 rfep 函数才生效
	}
	f[0] = 0; //外部子树用0这个点
	for(int j = hg[id]; ~j; j = g[j].next) {
		int v = g[j].v;
		int l0, r0; 
		if(v != fr) l0 = l[v], r0 = r[v]; //内部子树
		else { //外部子树
			v = 0;
			l0 = l[id] == mn1[fr] ? mn2[fr] : mn1[fr];
			r0 = r[id] == mx1[fr] ? mx2[fr] : mx1[fr];
		}
		if(l0 > 1 && l0 <= n && l0 - 1 != id) {//边合法
			if(t(rfep(l0 - 1), v)) {//边有效
				adda(id, l0 - 1, l0);//连边
			}
		}
		if(r0 >= 1 && r0 < n && r0 + 1 != id) { 
			if(t(rfep(r0 + 1), v)) { 
				adda(id, r0 + 1, r0); 
			}
		}
	}
	for(int j = hg[id]; ~j; j = g[j].next) {
		int v = g[j].v;
		if(v == fr) continue;
		iv[v] = 0; //记录的儿子退回去
		rep[v] = id; //认祖，使 rfep 生效
	}
}

int _;

void work() {
	q.clear();
	cin >> n;
	eg = ea = 0;
	for(int i = 0; i <= n + 1; i++) {
		hg[i] = ha[i] = tg[i] = -1; //多测清空
	}
	_G_T = 0;
	for(int i = 0; i <= n + 1; i++) {
		rep[i] = i;
		siz[i] = cnt[i] = 0;
		l[i] = i, r[i] = i;
	}
	f[0] = 0;
	for(int i = 1; i < n; i++) {
		int u, v; cin >> u >> v; 
		addg(u, v); addg(v, u);
	}
	_G_T = 0;
	dfs(1); //先搜一遍
	dfs1(1);//换根DP 
	dfs2(1);//记录答案
	for(int i = 1; i <= n; i++) {
		cout << val[i] << ' ' << cnt[i] << '\n';
		int ctn = 0;
		for(int j = ha[i]; ~j; j = ans[j].next) {
			cout << ans[j].u << ' ' << ans[j].v << '\n';ctn++;
		}
		cout << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> _; 
	while(_--) work();
}
```

---

## 作者：EuphoricStar (赞：1)

赛后 15min 过题/ll。

删掉点 $u$ 后树会分成若干棵子树。给每个子树一个编号，令 $c_i$ 表示 $i$ 所在子树的编号。然后题目要求一个类似最小生成树的东西。

既然要求最小生成树，那肯定先从 $|a - b| = 1$ 选起。对于所有 $i \in [1, u - 2] \cup [u + 1, n]$，连边 $(c_i, c_{i + 1})$，那么新图上最多有两个连通块。

新图只有一个连通块就直接做完了，否则 $(c_{u - 1}, c_{u + 1})$ 一定不在同一个连通块，合并它们的代价是 $2$。这样就是最优策略。

考虑怎么快速找到全部有用的 $(c_i, c_{i + 1})$ 的边。对于一对 $(i, i + 1)$，设 $x = \text{lca}(i, i + 1)$。发现只有当 $u = x$ 时 $i, i + 1$ 才都在 $x$ 的子树中且在 $x$ 的不同儿子的子树。设 $u$ 的一个儿子 $y$ 为 $i$ 所在子树，那么 $fa_i \to y$ 路径上的所有点满足 $i$ 在它的一个儿子的子树，$i + 1$ 在它父亲的子树。反过来对于 $i + 1$ 也类似。

当 $u = x$ 时可以用 `vector` 存全部满足的 $i$；否则维护每个点 $v$ 的子树中的使得 $dep_z$ 最小的 $i$（这样就能尽可能使得 $i + 1$ 在 $v$ 父亲那棵子树）。用可撤销并查集维护连通块的合并。

总时间复杂度 $O(n \log n)$。

[code](https://codeforces.com/problemset/submission/1935/250286378)

---

## 作者：MaxBlazeResFire (赞：1)

假设我们去掉的是点 $v$，记边集 $E=\{(1,2),(2,3),\cdots (v-2,v-1),(v-1,v+1),(v+1,v+2)\cdots\}$，那么可以证明所有新连的边集是 $E$ 的子集。

考虑一种贪心的构造。先假设 $v=1$，从节点 $2$ 开始遍历节点并构造大连通块。我们发现，如果发现当前节点 $x$ 与 $x-1$ 不连通，只需要连起 $(x-1,x)$ 即可，因为连的边数是确定的，这个代价必然取到了下界。

然后考虑 $v\neq 1$。考虑刚才的这个下界还能不能取到。如果存在一个连通块，使得它里面同时出现了 $>v$ 和 $<v$ 的数，那么根据上述构造方法，一定还是可以取到下界。否则我们考虑 $v-1$ 和 $v+1$ 不在同一个连通块里，此时用上述构造方法连接 $[1,v-1]$ 的所有点和 $[v+1,n]$ 的所有点，再加上一条边 $(v-1,v+1)$ 就一定可以得到最优解，仅比下界大 $1$。

考虑对于每个 $v$ 暴力模拟上述过程是不可取的。再挖掘一步性质。我们发现，遍历到节点 $x<v$ 时，假设 $x$ 与 $x-1$ 不连通，那么一定有 $x$ 是其所属连通块的最小值，相对地当 $x>v$ 时，一定有 $x$ 是其所属连通块的最大值。因此我们发现，对于一个点 $v$，按照它分裂后，对于剩下的 $deg_v$ 个连通块，我们只保留每个联通块的最小值或最大值 $x$ 所代表的 $(x-1,x)$ 这条边或 $(x,x+1)$ 这条边，以及 $(v-1,v+1)$ 共 $O(deg_v)$ 条边，直接跑一个 `Kruskal`，复杂度均摊下来就对了。

复杂度 $O(n(\log n+\alpha(n)))$。

```cpp
#include<bits/stdc++.h>
using namespace std;

//换根 dp 一下
//倍增判是否在同一个子树里

#define MAXN 400005
vector<int> E[MAXN],son[MAXN];

const int INF = 1000000000;

int n,deg[MAXN],mn[MAXN],mx[MAXN],gmn[MAXN],gmx[MAXN],fa[19][MAXN],dep[MAXN];
int dfn[MAXN],ed[MAXN],idx,df[MAXN];

int find( int x ){ return df[x] == x ? x : df[x] = find( df[x] ); }

void dfs( int x , int Fa ){
	mn[x] = mx[x] = x,dfn[x] = ++idx;
	for( int v : E[x] ){
		if( v == Fa ) continue;
		son[x].emplace_back( v ),dep[v] = dep[x] + 1,dfs( v , x );
		fa[0][v] = x;
		mn[x] = min( mn[x] , mn[v] );
		mx[x] = max( mx[x] , mx[v] );
	}
	ed[x] = idx;
}

void dfs2( int x , int Fa ){
	for( int v : E[x] ){
		if( v == Fa ) continue;
		gmn[v] = gmx[v] = x;
	}
	int siz = (int)son[x].size();
	for( int i = 0 , pre = INF , pre2 = 0 ; i < siz ; i ++ ){
		int v = son[x][i];
		gmn[v] = min( gmn[v] , min( gmn[x] , pre ) ),pre = min( pre , mn[v] );
		gmx[v] = max( gmx[v] , max( gmx[x] , pre2 ) ),pre2 = max( pre2 , mx[v] );
	}
	for( int i = siz - 1 , pre = INF , pre2 = 0 ; i >= 0 ; i -- ){
		int v = son[x][i];
		gmn[v] = min( gmn[v] , min( gmn[x] , pre ) ),pre = min( pre , mn[v] );
		gmx[v] = max( gmx[v] , max( gmx[x] , pre2 ) ),pre2 = max( pre2 , mx[v] );
	}
	for( int v : E[x] ){
		if( v == Fa ) continue;
		dfs2( v , x );
	}
}

inline int findup( int x , int w ){
	if( !( dfn[x] >= dfn[w] && dfn[x] <= ed[w] ) ) return fa[0][w];
	for( int j = 17 ; ~j ; j -- ) if( dep[fa[j][x]] > dep[w] ) x = fa[j][x];
	return x;
}

struct node{ int u,v,w,U,V; };

inline bool cmp( node A , node B ){ return A.w < B.w; }

vector<node> Es;

inline void solve(){
	scanf("%d",&n);
	for( int i = 1 ; i < n ; i ++ ){
		int u,v; scanf("%d%d",&u,&v);
		E[u].emplace_back( v ),E[v].emplace_back( u );
		deg[u] ++,deg[v] ++;
	}
	gmn[1] = INF,dfs( 1 , 0 ),dfs2( 1 , 0 );
	for( int j = 1 ; j <= 18 ; j ++ )
		for( int i = 1 ; i <= n ; i ++ ) fa[j][i] = fa[j - 1][fa[j - 1][i]];
	//枚举被删掉的点
	for( int x = 1 ; x <= n ; x ++ ){
		Es.clear();
		//抽象一张大小为 deg[x] 的图
		map<int,int> M; int id = 0;
		for( int p : son[x] ) M[p] = ++id;
		if( x != 1 ) M[fa[0][x]] = ++id;
		for( int p : son[x] ){
			int u = mn[p],v = mn[p] - 1;
			if( v > 0 && v != x ){
				int cu = findup( u , x ),cv = findup( v , x );
				if( cu != cv ) Es.emplace_back( node{ M[cu] , M[cv] , 1 , u , v } );
			}
			u = mx[p],v = mx[p] + 1;
			if( v <= n && v != x ){
				int cu = findup( u , x ),cv = findup( v , x );
				if( cu != cv ) Es.emplace_back( node{ M[cu] , M[cv] , 1 , u , v } );
			}
		}
		if( x != 1 ){
			int u = gmn[x],v = gmn[x] - 1;
			if( v > 0 && v != x ){
				int cu = findup( u , x ),cv = findup( v , x );
				if( cu != cv ) Es.emplace_back( node{ M[cu] , M[cv] , 1 , u , v } );
			}
			u = gmx[x],v = gmx[x] + 1;
			if( v <= n && v != x ){
				int cu = findup( u , x ),cv = findup( v , x );
				if( cu != cv ) Es.emplace_back( node{ M[cu] , M[cv] , 1 , u , v } );
			}
		}
		int u = x - 1,v = x + 1;
		if( u >= 1 && v <= n ){
			int cu = findup( u , x ),cv = findup( v , x );
			if( cu != cv ) Es.emplace_back( node{ M[cu] , M[cv] , 2 , u , v } );
		}
		sort( Es.begin() , Es.end() , cmp );
		for( int i = 1 ; i <= deg[x] ; i ++ ) df[i] = i;
		int res = 0;
		vector< pair<int,int> > Ans;
		for( node N : Es ){
			int u = N.u,v = N.v,w = N.w,ansu = N.U,ansv = N.V;
			if( find( u ) == find( v ) ) continue;
			res += w,df[find( u )] = find( v );
			Ans.emplace_back( make_pair( ansu , ansv ) );
		}
		printf("%d %d\n",res,deg[x] - 1);
		for( pair<int,int> ele : Ans ) printf("%d %d\n",ele.first,ele.second);
	}
	for( int i = 1 ; i <= n ; i ++ ) E[i].clear(),son[i].clear(),deg[i] = dfn[i] = ed[i] = dep[i] = mx[i] = mn[i] = gmx[i] = gmn[i] = 0;
	for( int j = 0 ; j <= 18 ; j ++ )
		for( int i = 1 ; i <= n ; i ++ ) fa[j][i] = 0;
	idx = 0;
}

signed main(){
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：聪明的乖宝宝 (赞：0)

# 思路
## 最小代价
首先，考虑最小代价是多少，当删除一个节点的时候，之前的树会变成一个森林，现在需要建立一些边，使得这个森林变回一棵树，设与删除的节点直接相连的点又 $ x $ 个，那么我们需要建立 $ x-1 $ 条边。当我们连接两个序号相差 $ 1 $ 的节点时，代价为 $ 1 $ 这也是建立一条边的最小代价。

那么我们可以考虑尽可能多的建立代价最小的边，我们发现当节点为 $ 1 $ 或 $ n $ 时，我们可以只建立代价最小的边，
因为删除节点 $ 1 $ 得到若干个连通块，取一个连通块中最大的节点，如果这个节点不是 $ n $ 那么将这个节点和比其编号大 $ 1 $ 的节点所在的连通块相连，否则，当这个节点是 $ n $ 找到比这个节点小 $ 1 $ 的节点，如果这个节点不在这个连通块内，将两个节点相连，否则再找小 $ 1 $ 的节点，直至不在这个连通块内。重复操作直到只剩下一个连通块。若节点是 $ n $ 则类似可证。

当节点不是 $ 1 $ 或 $ n $ 时，用上述方法，我们可以证明，所有包含编号大于该节点的连通块可以连接，所有包含编号小于该节点的连通块也都可以连接，如果在将能用最小代价边连接的部分都连接好了，还没有形成一棵树，当且仅当剩余两个连通块，一个连通块包含所有序号大于该节点的节点，另一个包含所有编号小于该节点的节点，这时，假设该节点编号为 $ x $ 则我们在 $ x-1 $ 和 $ x+1 $ 这两个节点之间建立一条边得到的总代价最小。
## 实现
按照上述逻辑我们考虑尽可能第在 $ i $ 和 $ i+1 $ 这种节点之间建立边。

当我们处理点 $ x $ 的时候，我们将这些点对分为三种
1. $ lca $ 在 $ x $ 的子树里的节点，这种点对对于答案没有贡献
2. $ lca $ 是 $ x $ 的点对
3. $ lca $ 是 $ x $ 的祖先的点对

我们将以 $ x $ 的所有子结点为根节点的子树看作一个点，对于每个第二类点对，它的两个点一定分别存在于 $ x $ 相关的两个子树中，我们将这两个子树建立一条边，并记录其连接的点的序号。

然后我们在建好的图上搜索，可以搜到若干连通块，就可以得到只通过 $ x $ 下的节点可以形成的连通块。

剩余的连通块想要相连，就要通过第三类点，将 $ x $ 的子树的每一个连通块同 $ x $ 之上的节点相连，当无法相连时，说明我们需要连接一条代价为 $ 2 $ 的边。我们可以将每个节点的子树中的第三类节点存在邻接表中，向上合并时将邻接表相连，每次取出时，判断一下此时还是否是第三类点，若不是，则删除，每个第三类点最多进入邻接表一次，从邻接表中删除一次。
# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int N=200010;
int t,n;
int head[N],Next[N*2],ver[N*2],sum[N],tot;
int f[N];
int h[N][25],d[N];
int lc[N];
int hc[N],nc[N*2],vc[N*2],ec[N],p[N*2],tc;
int u[N];
int e[N];
vector<pair<int,int> >vv[N],ans[N];
vector<int>w[N];
void qk()
{
    for(int i=1;i<=n;i++)
    {
        head[i]=0;
        d[i]=0;
        lc[i]=0;
        hc[i]=0;
        ec[i]=0;
        p[i]=0;
        u[i]=0;
        e[i]=0;
        vv[i].clear();
        ans[i].clear();
        w[i].clear();
        sum[i]=0;
    }
    tot=0;
    tc=0;
}
void add(int x,int y)
{
    ver[++tot]=y;
    Next[tot]=head[x];
    head[x]=tot;
    sum[x]++;
}
void ac(int x,int y,int z)
{
    vc[++tc]=y;
    nc[tc]=hc[x];
    if(hc[x]==0)ec[x]=tc;
    hc[x]=tc;
    p[tc]=z;
}
void dfsycl(int x)
{
    for(int i=head[x];i;i=Next[i])
    {
        int y=ver[i];
        if(d[y])continue;
        d[y]=d[x]+1;
        h[y][0]=x;
        for(int j=1;j<=20;j++)h[y][j]=h[h[y][j-1]][j-1];
        dfsycl(y);
    }
}
int lca(int x,int y)
{
    if(d[x]<d[y])
    {
        x=x^y;
        y=x^y;
        x=x^y;
    }
    for(int j=20;j>=0;j--)
    {
        if(d[h[x][j]]>=d[y])x=h[x][j];
    }
    if(x==y)return x;
    for(int j=20;j>=0;j--)
    {
        if(h[x][j]!=h[y][j])x=h[x][j],y=h[y][j];
    }
    return h[x][0];
}
void ycl()
{
    d[1]=1;
    dfsycl(1);
    for(int i=1;i<n;i++)
    {
        int md=lca(i,i+1);
        lc[i]=md;
        w[md].push_back(i);
        f[i]=i;
    }
    f[n]=n;
}
int cj(int x)
{
    if(f[x]==x)return x;
    f[x]=cj(f[x]);
    return f[x];
}
void bj(int x,int y)
{
    f[cj(x)]=cj(y);
}
void Find(int x,int r)
{
    u[x]=1;
    for(int i=0;i<vv[x].size();i++)
    {
        int y=vv[x][i].first;
        if(u[y])continue;
        int z=vv[x][i].second;
        ans[r].push_back(make_pair(z,z+1));
        Find(y,r);
        if(ec[x])nc[ec[x]]=hc[y];
        else hc[x]=hc[y];
        if(ec[y])ec[x]=ec[y];
    }
}
void dfs(int x)
{
    for(int i=head[x];i;i=Next[i])
    {
        int y=ver[i];
        if(y==h[x][0])continue;
        dfs(y);
    }
    for(int j=0;j<w[x].size();j++)
    {
        int z=w[x][j];
        int u1=cj(z),u2=cj(z+1);
        if(z==x||z+1==x)continue;
        vv[u1].push_back(make_pair(u2,z));
        vv[u2].push_back(make_pair(u1,z));
    }
    for(int i=head[x];i;i=Next[i])
    {
        int y=ver[i];
        if(y==h[x][0]||u[y])continue;
        Find(y,x);
        int pre=0,flag=1;
        for(int j=hc[y];j;j=nc[j])
        {
            int z=p[j];
            if(d[lc[z]]>=d[x])
            {
                if(j==hc[y])
                {
                    hc[y]=nc[j];
                    if(j==ec[y])ec[y]=0;
                }
                else
                {
                    nc[pre]=nc[j];
                    if(ec[y]==j)ec[y]=pre;
                }
            }
            else if(x!=1)
            {
                flag=0;
                ans[x].push_back(make_pair(z,z+1));
                break;
            }
            pre=j;
        }
        if(flag&&x!=1)
        {
            sum[x]++;
            ans[x].push_back(make_pair(x-1,x+1));
        }
        if(ec[x])nc[ec[x]]=hc[y];
        else hc[x]=hc[y];
        if(ec[y])ec[x]=ec[y];
    }
    if(d[lc[x]]<d[x]&&x!=n)ac(x,x,x);
    if(x!=1&&d[lc[x-1]]<d[x])ac(x,x,x-1);
    for(int i=head[x];i;i=Next[i])
    {
        int y=ver[i];
        if(y==h[x][0])continue;
        bj(y,x);
    }
}
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}
int main()
{
    cin>>t;
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<n;i++)
        {
            int x,y;
            x=read();
            y=read();
            add(x,y);
            add(y,x);
        }
        ycl();
        dfs(1);
        for(int i=1;i<=n;i++)
        {
            write(sum[i]-1);
            putchar(' ');
            write(ans[i].size());
            putchar('\n');
            for(int j=0;j<ans[i].size();j++)
            {
                write(ans[i][j].first);
                putchar(' ');
                write(ans[i][j].second);
                putchar('\n');
            }
            putchar('\n');
        }
        if(t)qk();
    }
    return 0;
}
```

---

## 作者：鼓豆帝王 (赞：0)

题目链接：[CF1935F Andrey's Tree](https://www.luogu.com.cn/problem/CF1935F)

## 解法说明

### 单个 $v$

先考虑对于某个固定的 $v$，该如何求得答案。

现在设 $v$ 是整棵树的根，它有 $s$ 个儿子，把它们对应的子树编号为 $1\sim s$。第一步肯定是要把题目转化一下，我们可以从值域上看。值域上的每个点都属于 $s$ 个子树中的一个，或是 $v$。有一个结论：

- 假设所有编号小于 $v$ 的节点分属于 $m$ 个子树中，连 $m-1$ 条代价为 $1$ 的边，一定能使 $m$ 个子树连通。对于所有编号大于 $v$ 的节点同理。

对于第 $i$ 个子树，其中编号小于 $v$ 的节点数计为 $l_i$，编号大于 $v$ 的节点数计为 $r_i$，则：

- **若存在 $l_i\neq0$ 且 $r_i\neq0$，则连通的最小代价为 $s-1$。**  
- **反之，连通的最小代价为 $s$。**

显然，需要连的边数一定比儿子数量小 $1$。

### 多个 $v$

沿袭上述思路，我们要维护每个点的 $l_i,r_i$，我们重新定义这两个量：对于以结点 $i$ 为根的子树，其中编号小于 $i$ 的父亲的节点数计为 $l_i$，编号大于 $i$ 的父亲的节点数计为 $r_i$。

在预处理 $l_i,r_i$ 时，可以按编号从小到大的顺序遍历结点，用 dfs 序和树状数组求出子树内编号大于某数的节点数量即可，复杂度为 $O(n\log n)$（这是时间复杂度瓶颈）。

但现在研究的 $v$ 可能不是整棵树的根，我们还要维护父结点的信息，但其实只要求出以结点 $v$ 为根的子树，其中编号小于或大于 $v$ 的节点数即可。因为这和父结点的信息对于整棵树是互补的。

如此我们便求出了删去每个点的连通最小代价。

### 构造方案

这是本题相对复杂的部分，要预处理多个数组：

1. 要求出每个子树中最小和最大的结点编号，这可以按编号大小顺序遍历结点，用贪心求解。  
2. 依旧要维护每个点父亲的信息，也就是求去掉某棵子树后，剩余结点编号的最大值和最小值。以求最小值举例，要求剩余结点编号的最小值，也就是要求最大的 $k$，满足：编号为 $1\sim k$ 的结点都在以该结点为根的子树中。那么剩余结点编号的最小值就是 $k+1$。这可以从叶子节点开始向上暴力递推，在每个结点检验最大的 $k$ 是否改变，复杂度为 $O(n)$。

接下来正式开始构造。

以 $v$ 为根举例，假设所有编号大于 $v$ 的节点分属于 $m$ 个子树中，计第 $i$ 个子树的最大编号为 $a_i$。当 $a_i\neq n$ 时，连 $a_i,a_i+1$。如此操作后这 $m$ 个子树必然连通。下面分类讨论：

- 若**不存在** $l_i\neq0$ 且 $r_i\neq0$，那么另外 $s-m$ 个子树的处理方式相同，此时一定满足 $a_i<v$。当 $a_i=v-1$ 时，连 $a_i,a_i+2$；否则，连 $a_i,a_i+1$。  
- 若**存在** $l_i\neq0$ 且 $r_i\neq0$，要颠倒操作顺序，因为要额外连一条边使值域上左右两边的子树连通。对于另外 $s-m$ 个子树，计第 $i$ 个子树的最小编号为 $b_i$。当 $b_i\neq 1$ 时，连 $b_i,b_i-1$；对于上述 $m$ 个子树，计 $c=\min \limits_{i=1}^m b_i$，当 $c\neq 1$ 时，连 $c,c-1$。

注意，$v=1$ 或 $v=n$ 的情况可能需要特判。

该算法的时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。

## AC 代码

```cpp
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

const int maxN = 2e5 + 10;

int t, n;
int len = 0, to[maxN << 1], ne[maxN << 1], fi[maxN];
int cnt = 0, fa[maxN], dfn[maxN], siz[maxN];
int tsum[maxN];
int sum[maxN], sum2[maxN];
int mx[maxN], mx2[maxN], mn[maxN], mn2[maxN], mxcnt[maxN], mncnt[maxN];

void link(int u, int v) {
	to[++len] = v, ne[len] = fi[u], fi[u] = len;
}

void dfs(int p, int fp) {
	fa[p] = fp, siz[p] = 1, dfn[p] = ++cnt;
	for (int i = fi[p]; i; i = ne[i]) {
		if (to[i] == fp) continue;
		dfs(to[i], p);
		siz[p] += siz[to[i]];
	}
}

void add(int x, int k) {
	while (x <= n) {
		tsum[x] += k;
		x += x & -x;
	}
}

int getsum(int x) {
	int res = 0;
	while (x) {
		res += tsum[x];
		x -= x & -x;
	}
	return res;
}

void dfsmn(int p) {
	int mxc = 0;
	for (int i = fi[p]; i; i = ne[i]) {
		if (to[i] == fa[p]) continue;
		dfsmn(to[i]);
		mxc = max(mxc, mncnt[to[i]]);
	}
	
	if (p == 1) mxc = 1;
	int r = mxc + 1;
	while (dfn[r] >= dfn[p] && dfn[r] <= dfn[p] + siz[p] - 1) r++;
	mncnt[p] = r - 1;
	mn2[p] = r;
}

void dfsmx(int p) {
	int mnc = n + 1;
	for (int i = fi[p]; i; i = ne[i]) {
		if (to[i] == fa[p]) continue;
		dfsmx(to[i]);
		mnc = min(mnc, mxcnt[to[i]]);
	}
	
	if (p == n) mnc = n;
	int l = mnc - 1;
	while (dfn[l] >= dfn[p] && dfn[l] <= dfn[p] + siz[p] - 1) l--;
	mxcnt[p] = l + 1;
	mx2[p] = l;
}

int main(void) {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int u, v;
		for (int i = 1; i < n; i++) {
			scanf("%d%d", &u, &v);
			link(u, v), link(v, u);
		}
		dfs(1, 0);
		
		for (int i = 1; i <= n; i++) {
			int temp = getsum(dfn[i] + siz[i] - 1) - getsum(dfn[i] - 1);
			sum[i] = temp;
			for (int j = fi[i]; j; j = ne[j]) {
				if (to[j] == fa[i]) continue;
				temp = getsum(dfn[to[j]] + siz[to[j]] - 1) - getsum(dfn[to[j]] - 1);
				sum2[to[j]] = temp;
			}
			add(dfn[i], 1);
		}
		for (int i = 1; i <= n; i++) {
			for (int j = i; j; j = fa[j]) {
				if (mn[j]) break;
				mn[j] = i;
			}
		}
		for (int i = n; i >= 1; i--) {
			for (int j = i; j; j = fa[j]) {
				if (mx[j]) break;
				mx[j] = i;
			}
		}
		dfsmn(1), dfsmx(1);
		
		for (int i = 1; i <= n; i++) {
			int soncnt = 0;
			bool flag = 0;
			if (i == 1 || i == n) flag = 1;
			for (int j = fi[i]; j; j = ne[j]) {
				soncnt++;
				if (to[j] == fa[i]) {
					if (i - 1 - sum[i] != 0 && i - 1 - sum[i] != n - siz[i]) {
						flag = 1;
					}
				}
				else {
					if (sum2[to[j]] != 0 && sum2[to[j]] != siz[to[j]]) {
						flag = 1;
					}
				}
			}
			
			if (soncnt == 1) {
				printf("0 0\n");
			}
			else if (flag) {
				printf("%d %d\n", soncnt - 1, soncnt - 1);
				int mnp = n + 1;
				for (int j = fi[i]; j; j = ne[j]) {
					if (to[j] == fa[i]) {
						if (mx2[i] < i) continue;
						v = mx2[i] + 1;
						if (v <= n) printf("%d %d\n", mx2[i], v);
						mnp = min(mnp, mn2[i]);
					}
					else {
						if (mx[to[j]] < i) continue;
						v = mx[to[j]] + 1;
						if (v <= n) printf("%d %d\n", mx[to[j]], v);
						mnp = min(mnp, mn[to[j]]);
					}
				}
				v = mnp - 1;
				if (i != 1 && i != n && v >= 1) printf("%d %d\n", mnp, v);
				for (int j = fi[i]; j; j = ne[j]) {
					if (to[j] == fa[i]) {
						if (mx2[i] > i) continue;
						v = mn2[i] - 1;
						if (v >= 1) printf("%d %d\n", mn2[i], v);
					}
					else {
						if (mx[to[j]] > i) continue;
						v = mn[to[j]] - 1;
						if (v >= 1) printf("%d %d\n", mn[to[j]], v);
					}
				}
			}
			else {
				printf("%d %d\n", soncnt, soncnt - 1);
				for (int j = fi[i]; j; j = ne[j]) {
					if (to[j] == fa[i]) {
						if (mx2[i] + 1 == i) v = mx2[i] + 2;
						else v = mx2[i] + 1;
						if (v <= n) printf("%d %d\n", mx2[i], v);
					}
					else {
						if (mx[to[j]] + 1 == i) v = mx[to[j]] + 2;
						else v = mx[to[j]] + 1;
						if (v <= n) printf("%d %d\n", mx[to[j]], v);
					}
				}
			}
			putchar('\n');
		}
		
		for (int i = 1; i <= n; i++) {
			fi[i] = fa[i] = dfn[i] = siz[i] = tsum[i] = sum[i] = sum2[i] = 0;
			mx[i] = mx2[i] = mn[i] = mn2[i] = mncnt[i] = mxcnt[i] = 0;
		}
		for (int i = 1; i <= len; i++) {
			to[i] = ne[i] = 0;
		}
		len = cnt = 0;
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

设 $d_u$ 为 $u$ 的度数，显然删掉 $u$ 后树变成了 $d_u$ 个连通块，至少需要 $d_u-1$ 次合并才能变成一个连通块，所以答案下界显然是 $d_u-1$。

但是下界不一定取得到。注意到这个东西其实是求最小生成树，不妨考虑 Kruskal 的贪心过程，我们肯定先希望连接形如 $i \leftrightarrow i+1(i < n)$ 的边，这样连接所有边后，点编号在 $[1,u)$ 和 $(u,n]$ 区间内的点内部必然已经联通了。因为假如不联通，那么你可以通过一次操作 $i,i+1$ 使得其联通，然而由于 $u$ 被删了，于是这是两个区间。

有两种情况：

1. 把 $i,i+1$ 的边连完后，全部点除了 $u$ 都联通，答案就是 $d_u-1$。

2. 否则，连接 $u-1$ 和 $u+1$，答案为 $d_u$。

至此我们知道了答案是多少，但是怎么构造呢？

考虑将树视为以 $1$ 为根的有根树，考虑点 $i$ 和 $i+1$，其中 $i<n$。这两个点在 $u = \operatorname{LCA}(i,i+1)$ 的时候会需要合并，但是我们发现还有一个问题，在于合并的 $i,i+1$ 有时可能分别处于 $u$ 子树内外。

对于 $u$ 的每个儿子 $j$，其子树内某个点 $i$，如果想通过 $i \leftrightarrow i+1$ 的边合并，且 $i+1$ 在 $u$ 子树外的时候，容易发现 $i$ 必然是 $j$ 子树内 $\operatorname{LCA}(i,i+1)$ 深度最小的位置，这样才有更多的 $u$ 能被合并。

于是我们把所有可能有贡献的点对 $(i,i+1)$ 都求出来即可。合并的时候考虑可撤销并查集。

于是现在我们要求树删掉每一个点的并查集，直接无脑上线段树分治就可以做到 $O(n \log^2 n)$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
using namespace std;

const int N = 2e5 + 5;

int t, n;
vector<int> G[N];
int fa[N][21], dep[N], id[N];
int v1[N], v2[N], l1[N], l2[N];
int sz[N];

vector<pair<int, int>> ver[N];
int LG2[N];

class ST
{
public:
	int f[N][21];
	int na[N];
	void Init(int* a)
	{
		for (int i = 1; i <= n; i++) f[i][0] = i, na[i] = a[i];
		for (int j = 1; j <= LG2[n]; j++)
		{
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
			{
				if (a[f[i][j - 1]] < a[f[i + (1 << (j - 1))][j - 1]]) f[i][j] = f[i][j - 1];
				else f[i][j] = f[i + (1 << (j - 1))][j - 1];
			}
		}
	}
	int query(int l, int r)
	{
		int p = LG2[r - l + 1];
		return (na[f[l][p]] < na[f[r - (1 << p) + 1][p]] ? f[l][p] : f[r - (1 << p) + 1][p]);
	}
}s1, s2;

class Union_Find
{
public:
	int fa[N], sz[N];
	void Init()
	{
		for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
	}
	int find(int u)
	{
		return (fa[u] == u ? u : find(fa[u]));
	}
	pair<int, int> merge(int u, int v)
	{
		if ((u = find(u)) == (v = find(v))) return make_pair(-1, -1);
		if (sz[u] < sz[v]) swap(u, v);
		sz[u] += sz[v];
		fa[v] = u;
		return make_pair(u, v);
	}
	void rollback(pair<int, int> p)
	{
		if (p.first == -1) return;
		sz[p.first] -= sz[p.second];
		fa[p.second] = p.second;
	}
}uf;

int idx;
int ra[N];

void dfs(int u, int f)
{
	sz[u] = 1;
	id[u] = ++idx;
	ra[idx] = u;
	fa[u][0] = f;
	dep[u] = dep[f] + 1;
	for (auto& j : G[u]) if (j ^ f) dfs(j, u), sz[u] += sz[j];
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
	for (int i = 20; i >= 0; i--)
	{
		if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
	}
	return fa[u][0];
}

class Time_SegmentTree
{
public:
	struct Node
	{
		int l, r;
		vector<pair<int, int>> eg;
	}tr[N << 2];
	void build(int u, int l, int r)
	{
		tr[u] = { l, r };
		tr[u].eg.clear(), tr[u].eg.shrink_to_fit();
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	void update(int u, int l, int r, auto x)
	{
		if (tr[u].l >= l and tr[u].r <= r)
		{
			tr[u].eg.emplace_back(x);
			return;
		}
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) update(u << 1, l, r, x);
		if (r > mid) update(u << 1 | 1, l, r, x);
	}
	void solve(int u)
	{
		vector<pair<int, int>> rol;
		for (auto& [x, y] : tr[u].eg)
		{
			rol.emplace_back(uf.merge(x, y));
		}
		if (tr[u].l == tr[u].r)
		{
			int i = tr[u].l;
			vector<pair<int, int>> ans;
			vector<pair<int, int>> ds;
			for (auto& [u, v] : ver[i])
			{
				if (u == i || v == i) continue;
				ds.emplace_back(uf.merge(u, v));
				if (ds.back().first != -1) ans.emplace_back(make_pair(u, v));
			}
			for (auto& u : G[i])
			{
				if (u == fa[i][0]) continue;
				int l = id[u], r = id[u] + sz[u] - 1;
				int p1 = s1.query(l, r);
				if (v1[p1] != (int)1e9)
				{
					int j = ra[p1], j2 = j - 1;
					if (j == i || j2 == i) goto E;
					ds.emplace_back(uf.merge(j, j2));
					if (ds.back().first != -1) ans.emplace_back(make_pair(j, j2));
				}
			E:
				p1 = s2.query(l, r);
				if (v2[p1] != (int)1e9)
				{
					int j = ra[p1], j2 = j + 1;
					if (j != i && j2 != i)
					{
						ds.emplace_back(uf.merge(j, j2));
						if (ds.back().first != -1) ans.emplace_back(make_pair(j, j2));
					}
				}
			}
			int res = G[i].size() - 1;
			if (uf.sz[uf.find(i == 1 ? 2 : 1)] != n - 1)
			{
				ds.emplace_back(uf.merge(i - 1, i + 1));
				ans.emplace_back(make_pair(i - 1, i + 1));
				res++;
			}
			cout << res << " " << ans.size() << "\n";
			for (auto& [u, v] : ans)
			{
				cout << u << " " << v << "\n";
			}
			cout << "\n";
			reverse(ds.begin(), ds.end());
			for (auto& u : ds) uf.rollback(u);
			reverse(rol.begin(), rol.end());
			for (auto& u : rol) uf.rollback(u);
			return;
		}
		solve(u << 1);
		solve(u << 1 | 1);
		reverse(rol.begin(), rol.end());
		for (auto& u : rol) uf.rollback(u);
	}
}sgt;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	for (int i = 2; i < N; i++) LG2[i] = LG2[i >> 1] + 1;
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			G[i].clear(), G[i].shrink_to_fit();
			v1[i] = v2[i] = (int)1e9;
			l1[i] = l2[i] = 0;
			dep[i] = 0;
			ver[i].clear(), ver[i].shrink_to_fit();
			for (int j = 0; j <= 20; j++) fa[i][j] = 0;
		}
		uf.Init();
		vector<pair<int, int>> egs;
		for (int i = 1; i < n; i++)
		{
			int u, v;
			cin >> u >> v;
			egs.emplace_back((u < v ? make_pair(u, v) : make_pair(v, u)));
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		idx = 0;
		dfs(1, 0);
		for (int j = 1; j <= 20; j++)
		{
			for (int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
		}
		for (int i = 1; i <= n; i++)
		{
			// l1: i - 1
			if (i != 1)
			{
				l1[id[i]] = LCA(i, i - 1);
				v1[id[i]] = dep[l1[id[i]]];
			}
			if (i != n)
			{
				l2[id[i]] = LCA(i, i + 1);
				v2[id[i]] = dep[l2[id[i]]];
			}
		}
		for (int i = 1; i < n; i++)
		{
			ver[LCA(i, i + 1)].emplace_back(make_pair(i, i + 1));
		}
		s1.Init(v1);
		s2.Init(v2);
		//cout << "???: " << ver[1].size() << "\n";
		sgt.build(1, 1, n);
		for (auto& [u, v] : egs)
		{
			if (u != 1) sgt.update(1, 1, u - 1, make_pair(u, v));
			if (u + 1 < v) sgt.update(1, u + 1, v - 1, make_pair(u, v));
			if (v < n) sgt.update(1, v + 1, n, make_pair(u, v));
		}
		sgt.solve(1);
	}
	return 0;
}
```

---

## 作者：meyi (赞：0)

我好像把题加强了，下面那份代码貌似能处理任意图的情况（连成连通块而不是树，求最小代价），不一定要树的限制。如果有读者找到反例还请告知，谢谢。

结论：在所有连边中，最多有一条代价为 $2$ 的边（$[1,u-1]$ 和 $[u+1,n]$ 不存在任何连边时连接 $u-1$ 和 $u+1$），其余的边的代价一定是 $1$。

先处理代价为 $2$ 的边，然后证明剩下的边的边权均为 $1$：若连通块个数 $> 1$，则一定存在至少一个点 $i(i < n)$ 满足 $i$ 和 $i+1$ 在不同连通块，添加一条连接 $i$ 和 $i+1$ 的边即可。

如何找到这样的 $i$？不难发现满足条件的 $i$ 中至少有一个满足 $i$ 或 $i+1$ 是所属块的最小/最大值，使用并查集维护即可。

拓展到多组询问，只需套上线段树分治+可撤销并查集的套路。

时间复杂度 $\mathcal{O}(n\log n\alpha(n))$。

赛时代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#define ALL(v) v.begin(),v.end()
#define For(i,_) for(int i=0,i##end=_;i<i##end;++i) // [0,_)
#define FOR(i,_,__) for(int i=_,i##end=__;i<i##end;++i) // [_,__)
#define Rep(i,_) for(int i=(_)-1;i>=0;--i) // [0,_)
#define REP(i,_,__) for(int i=(__)-1,i##end=_;i>=i##end;--i) // [_,__)
typedef long long ll;
typedef unsigned long long ull;
#define V vector
#define pb push_back
#define pf push_front
#define qb pop_back
#define qf pop_front
#define eb emplace_back
typedef pair<int,int> pii;
typedef pair<ll,int> pli;
#define fi first
#define se second
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}},inf=0x3f3f3f3f,mod=1e9+7;
const ll infl=0x3f3f3f3f3f3f3f3fll;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
int init=[](){return cin.tie(nullptr)->sync_with_stdio(false),0;}();
template<class T1,class T2>
inline V<T1> pre1d(const V<T2> &v,const function<T1(T1,T2)> &f=[](const T1 &x,const T2 &y){return x+y;}){
    V<T1>ret(v.size());
    For(i,v.size())ret[i]=f((i?ret[i-1]:T1()),v[i]);
    return ret;
}
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
struct undo_dsu{
    V<int>fa,mn,mx,siz;
    V<array<int,4>>q;
    unordered_set<int,custom_hash>s;
    inline void resize(int n){
		V<int>(n).swap(fa),V<int>(n).swap(mn),V<int>(n).swap(mx),iota(ALL(fa),0),iota(ALL(mn),0),iota(ALL(mx),0),decltype(q)().swap(q),V<int>(n,1).swap(siz);
		decltype(s)().swap(s);For(i,n)s.insert(i);
	}
    inline undo_dsu(int n=0){resize(n);}
    int find(int k){return k==fa[k]?k:find(fa[k]);}
    inline bool merge(int x,int y){
		x=find(x),y=find(y);
		if(x!=y){
			if(siz[x]<siz[y])swap(x,y);
			q.pb({x,y,mn[x],mx[x]});
			fa[y]=x,ckmin(mn[x],mn[y]),ckmax(mx[x],mx[y]),siz[x]+=siz[y];
			s.erase(y);
		}
		return x!=y;
	}
	inline void undo(int k){
		while(q.size()>k){
			auto p=q.back();q.qb();
			fa[p[1]]=p[1],mn[p[0]]=p[2],mx[p[0]]=p[3],siz[p[0]]-=siz[p[1]];
			s.insert(p[1]);
		}
	}
	inline bool same(int x,int y){return find(x)==find(y);}
	inline int size(int k){return siz[find(k)];}
};
int main(){
	int t_case=1;
	scanf("%d",&t_case);
	while(t_case--){
		int n;
		scanf("%d",&n);
		V<int>cnt(n);
		V<V<pii>>evt(n<<2);
		function<void(int,int,int,int,int,int,int)>add=[&](int p,int l,int r,int ql,int qr,int x,int y){
			if(ql<=l&&r<=qr){
				evt[p].eb(x,y);
				return;
			}
			int mid=l+r>>1;
			if(ql<=mid)add(p<<1,l,mid,ql,qr,x,y);
			if(qr>mid)add(p<<1|1,mid+1,r,ql,qr,x,y);
		};
		For(i,n-1){
			int x,y;
			scanf("%d%d",&x,&y),--x,--y;
			if(x>y)swap(x,y);
			if(x)add(1,0,n-1,0,x-1,x,y);
			if(x+1<y)add(1,0,n-1,x+1,y-1,x,y),++cnt[x+1],--cnt[y];
			if(y+1<n)add(1,0,n-1,y+1,n-1,x,y);
		}
		cnt=pre1d<int>(cnt);
		undo_dsu d(n);
		function<void(int,int,int)>solve=[&](int p,int l,int r){
			int tmp=d.q.size();
			for(const pii &i:evt[p])d.merge(i.fi,i.se);
			if(l==r){
				int ans=0;
				V<pii>e;
				if(l&&l<n-1&&!cnt[l]){
					ans+=2;
					d.merge(l-1,l+1);
					e.eb(l-1,l+1);
				}
				d.s.erase(l);
				while(d.s.size()>1){
					for(int x:d.s){
						int y=d.mn[x],z=d.mx[x];
						if(y&&y-1!=l&&d.merge(x,y-1)){++ans,e.eb(y,y-1);goto skip;}
						else if(z<n-1&&z+1!=l&&d.merge(x,z+1)){++ans,e.eb(z,z+1);goto skip;}
					}
					assert(0);
					skip:;
				}
				d.s.insert(l);
				printf("%d %d\n",ans,(int)e.size());
				for(const pii &i:e)printf("%d %d\n",i.fi+1,i.se+1);
				putchar(10);
			}
			else{
				int mid=l+r>>1;
				solve(p<<1,l,mid);
				solve(p<<1|1,mid+1,r);
			}
			d.undo(tmp);
		};
		solve(1,0,n-1);
	}
	return 0;
}

```

---

## 作者：nullqtr_pwp (赞：0)

这种题怎么敢放 2F 恶心人的。

考虑对于定值 $u$ 的询问，原图被分为了 $\text{deg}_u$ 个连通块，注意到我们就是要将这些块连通起来，其实相当于有边权 $w(u,v)=|u-v|$，不难想到**最小生成树**。

记删去 $u$ 的图为 $G_u$。

对于 kruskal 算法，考虑边权从 $1\sim n-1$ 逐条加入 $G_u$，观察其何时联通，这个东西已经和本身形态没太大关联了，观察连通性即可。

注意到边权 $=1$ 的加完的时候就一定有标号在 $[1,u-1]$ 的点形成一个大连通块，$[u+1,n]$ 的点也形成一个大连通块，如果这样算完之后确实出现 $u-1,u+1$ 不联通，那么加入 $(u-1,u+1)$ 的边一定最优。

那么容易想到，如果在数轴上极长的连续段 $[l,r]$，如果满足标号是它们的在树上构成一个连通块，内部是不用连边的。也就是说，我们按照连通性分成若干连续段，$[1,2],[3,5],[6,8],[9]$ 就表示，当前的图上有连通块 $(1,2),(3,4,5),(6,7,8),(9)$。

去除 $u$ 后，就考虑相邻两个连续段中间必须连边，然后再判定 $(u-1,u+1)$ 的边是否要连。

现在将问题拓展到所有的 $u=1,2,\cdots,n$。注意到每次询问只涉及到邻域，所以每次可以暴力查询这些连通块。

图连通性这个东西不可加，套路是用**整体二分+带撤销并查集**维护图连通性。不难想到，这道题需要在刚开始跑到 $\text{solve}(l,r)$ 时，并查集就维护好 $[1,l-1]$ 以及 $[r+1,n]$ 的连通性。

由于要带撤销，不能路径压缩，时间复杂度 $O(n\log^2n)$。

[提交记录](https://codeforces.com/contest/1935/submission/249931422)

---

