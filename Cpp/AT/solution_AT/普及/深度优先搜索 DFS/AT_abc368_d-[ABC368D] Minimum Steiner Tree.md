# [ABC368D] Minimum Steiner Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc368/tasks/abc368_d

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点の木が与えられます。$ i $ 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます。

このグラフからいくつかの($ 0 $ 個でもよい)辺と頂点を削除してできる木のうち、指定された $ K $ 個の頂点、頂点 $ V_1,\ldots,V_K $ を全て含むようなものの頂点数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- $ 1\ \leq\ V_1\ <\ V_2\ <\ \ldots\ <\ V_K\ \leq\ N $
- 与えられるグラフは木である
- 入力は全て整数

### Sample Explanation 1

与えられた木は下図左の通りであり、そこからいくつかの辺と頂点を削除してできる木のうち頂点 $ 1,3,5 $ を全て含むような頂点数最小のものは下図右の通りです。 
![図](https://img.atcoder.jp/abc368/4baf6b0adb0e12dcf8a5c812ada5c17a.png)

## 样例 #1

### 输入

```
7 3
1 2
1 3
2 4
2 5
3 6
3 7
1 3 5```

### 输出

```
4```

## 样例 #2

### 输入

```
4 4
3 1
1 4
2 1
1 2 3 4```

### 输出

```
4```

## 样例 #3

### 输入

```
5 1
1 4
2 3
5 2
1 2
1```

### 输出

```
1```

# 题解

## 作者：wo_hen_la (赞：5)

**可以把保留的最少顶点数看成最多没用的顶点数**。注意到如果一个顶点的子树中不包含任意一个要保留的点，那么该点是没用的，它的子树去除后依然满足题目要求。

可以跑两遍 dfs 解决，第一遍记录每个点的子树大小和该点是否有用。第二遍时若遇到一个点是没用的，就用总点数减去它的子树大小，且不从这个点往下搜。

注意 dfs 的根应是要保留的点的任意一个。

## 代码

```cpp
int n,m,ans;
vector<int> e[N];
bool vv[N],vis[N];
int siz[N];
void dfs(int u,int fa)
{
	if(vis[u]) vv[u]=1;
	siz[u]=1;
	for(auto v:e[u]){
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		vv[u]|=vv[v];//任意儿子有用，父亲就有用
	}
}
void dfs2(int u,int fa)
{
	for(auto v:e[u]){
		if(v==fa) continue;
		if(!vv[v]){//没用的不需要往下搜
			ans-=siz[v];
			continue;
		}
		dfs2(v,u);
	}
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n>>m;ans=n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].pb(v);e[v].pb(u);
	}
	int x;
	while(m--){
		cin>>x;
		vis[x]=1;
	}
	dfs(x,0);
	dfs2(x,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：yx666 (赞：3)

# Minimum Steiner Tree 题解

$$\text{Description}$$

一棵树，树上有 $n$ 个顶点，编号为 $1$ 到 $n$。第 $i$ 条边连接顶点 $a_i$ 和 $b_i$。

考虑从这个图中删除一些边和顶点（可能为零）后可以得到一棵树。

求这样一棵树中包含所有 $k$ 指定顶点 $v_1,\ldots,v_k$ 的顶点的最小数目。

$$\text{Solution 1}$$

蒟蒻刚学会[**重链剖分**](https://www.luogu.com.cn/problem/P3384)，就用**重剖**水半篇题解。

实现：

1. 建树。

2. 重剖找到 $v_1,\ldots,v_k$ 的最近公共祖先 $rt$。

3. 以 $rt$ 为根，向下做 dfs 染色，统计答案。

时间复杂度 $\Theta(k\log n)$。

具体操作看代码。

$$\text{Code 1}$$

[AC 记录](https://www.luogu.com.cn/record/174595397)。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define N 200005

// 链式前向星
int cnt,head[N];
struct {
	int to,nxt;
}edge[N<<1];

static inline void addEdge(int from,int to){
	edge[++cnt]={to,head[from]};
	head[from]=cnt;
	return;
}

// 重链剖分
int hs[N],sz[N],fa[N],dep[N];
void dfs1(int x,int t){
	fa[x]=t;
	sz[x]=1;
	
	int mx=-1,p=-1;
	for(int i=head[x];i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==t) continue;
		
		dep[to]=dep[x]+1;
		dfs1(to,x);
		sz[x]+=sz[to];
		if(sz[to]>mx){
			mx=sz[to];
			p=to;
		}
	}
	hs[x]=p;
	return;
}

int top[N];
void dfs2(int x,int t){
	top[x]=t;
	
	if(hs[x]!=-1) dfs2(hs[x],t);
	for(int i=head[x];i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==fa[x]||to==hs[x]) continue;
		dfs2(to,to);
	}return;
}

static inline int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) // 注意是判断链顶的深度
			x^=y^=x^=y;
		x=fa[top[x]];
	}
	return dep[x]>dep[y]?x:y;		// 返回的是 dep 更小的
}
// 重剖完辣

// 统计答案
int ans=0;
bitset<N>vis,tar;		// tar_i 表示 i 是否是指定顶点；vis_i 表示 i 是否被染色
void dfs3(int x,int fa){
	if(tar[x]) vis[x]=1,++ans;
	for(int i=head[x];i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==fa) continue;
		
		dfs3(to,x);
		if(vis[to]&&!vis[x])		// 注意要判断 x 是否被染色 
			vis[x]=1,++ans;
	}return;
}
// 统计完了

int n,k;
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	// 建图
	cin>>n>>k;
	for(int x,y,i=1;i<n;++i){
		cin>>x>>y;
		addEdge(x,y);
		addEdge(y,x);
	}
	// 建完图了
	
	// 跑重剖
	dfs1(1,0);dfs2(1,0);
	int rt;	cin>>rt;
	tar[rt]=1;
	for(int x,i=1;i<k;++i){
		cin>>x;
		tar[x]=1;
		rt=LCA(rt,x);
	}
	// 跑完了
	
	// 统计答案
	dfs3(rt,0);
	cout<<ans;
	return 0;
}
```

$$\text{Solution 2}$$

一次 dfs 即可。

思路：

定义一个点的大小 $sz$ 表示以该点为根的所有子树中被染色的点的个数。

1. 将要求的点染上色。

2. 跑一遍 dfs，算出 $sz$。

3. 统计答案，答案为 $1+\sum_{i=1}^n [sz_i<k]$。

4. 时间复杂度 $\Theta(n)$。

$$\text{Code 2}$$

[你谷目前 rk 1](https://www.luogu.com.cn/record/174604358)。

```cpp
#define N 200005
int cnt=0,head[N];
struct {
	int to,nxt;
}edge[N<<1];
static inline void addEdge(int from,int to){
	edge[++cnt].to=to;
	edge[cnt].nxt=head[from];
	head[from]=cnt;
}
int sz[N];
void dfs(int x,int fa){
	for(int i=head[x];i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to!=fa){
			dfs(to,x);
			sz[x]+=sz[to];
		}
	}
}
int n,k;
signed main(){
	n=read(),k=read();
	for(int x,y,i=1;i<n;++i){
		x=read(),y=read();
		addEdge(x,y);
		addEdge(y,x);
	}
	for(int i=1;i<=k;++i) sz[read()]=1;		// 染色
	dfs(1,0);
	
	int ans=0;
	for (int i=1;i<=n;++i){
		if (sz[i]&&sz[i]<k)
			++ans;			// 统计答案
	}printf("%d",ans+1);// 不要忘了根节点 +1
	return 0;
}
```

$$\text{Afterword}$$

这里也给出一些自造样例：

**example 1**：

input：

```
6 4
2 3
4 2
1 2
1 5
2 6
3 4 6 5
```

output：

```
6
```

**example 2**：

input：

```
4 3
2 3
4 2
1 2
2 3 4
```

output：

```
3
```

---

## 作者：wuyixiang (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc368_d)

题目大意：给你一棵树和带标记的 $m$ 个节点，请用结点数最少的树形连通块将这 $m$ 个节点都包含在内。

题目分析：首先我们将任意一个打标记的结点设为根，这样我们在讨论某个结点在不在联通块时才会更方便。

这样对于任意一个结点 $x$，如果它被打上了标记，则它的祖先肯定都在路径之内。可以证明：如果它的祖先不在路径内，则它和根的路径就会中断。又它们都打了标记，所以不符合题意。

显然每个打标记的结点往上查找会超时。换种思路：对于一个结点 $y$，如果在以它为根的所有结点内有一个被打上了标记，则结点 $y$ 一定会打标记。这种搜索的好处在于：它的儿子都能以较快的速度得出答案，那么结点 $y$ 的答案就是儿子的答案之和了。因为只要访问一遍结点和边，所以复杂度为 $\mathcal{O(n + m)}$，不会超时。

代码放这里。

```cpp
#include <iostream>
#include <vector>
#define int long long
using namespace std;
vector<int>ve[200005];
int n,m,a[200005];
int dfs(int x,int fa)
{
  int ans = a[x];
  for(int i = 0;i < ve[x].size();i ++)
  {
    if(ve[x][i] == fa)continue ;
    int num = dfs(ve[x][i],x);
    ans += num;
    if(num && !a[ve[x][i]])m ++;
  }
  return ans;
}
signed main()
{
  cin >> n >> m;
  for(int i = 1,u,v;i < n;i ++)
  {
    cin >> u >> v;
    ve[u].push_back(v),ve[v].push_back(u);
  }
  int x = 0;
  for(int i = 1;i <= m;i ++)
  {
    cin >> x;
    a[x] ++;
  }
  dfs(x,0);
  cout << m;
}
```

---

## 作者：KobeBeanBryantCox (赞：2)

# AT_abc368_d [ABC368D] Minimum Steiner Tree 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc368_d)。

~~话说这个题为什么我第一眼是建虚树 awa。~~

----------------------

## 题意

给若干个关键点，在给出的树中把这些关键点抽出来组成一个新的树，求新树最少节点个数。

----------------------------

## 题解

考虑一个点什么时候被选上。

当且仅当以它为根节点的子树内有节点被选上或者它本身就是一个关键点。

用 $f$ 数组记录关键点。

设布尔类型的 $b_u$ 表示 $u$ 这个点是否被选。

即 $b_u=f_u\vee b_{v_1}\vee b_{v_2}\vee\dots\vee b_{v_k}$，其中 $v_1\sim v_k$ 为 $u$ 的儿子，$\vee$ 为或符号。

最后 $\large ans=\sum_{i=1}^n[b_i=1]$。

还要注意一点，就是整棵树的根节点必须是这些关键点的其中一个，否测可能会选到无用的点。

~~我也不知道这个算不算 DP，个人感觉不算 DP 吧。~~

-----------------------

## AC 代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
#define int long long
int in()
{
	int k=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
void out(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
const int N=2e5+10;
vector<int>e[N];
bool f[N],b[N];
int ans=0;
void dfs(int u,int fa)
{
	for(int v:e[u])
		if(v!=fa)
		{
			dfs(v,u);
			b[u]=b[u]||b[v];
		}
	if(f[u])b[u]=true;
	if(b[u])ans++;
}
signed main()
{
	int n=in(),k=in();
	for(int i=1;i<n;i++)
	{
		int u=in(),v=in();
		e[u].push_back(v),e[v].push_back(u);
	}
	int root=in();f[root]=true;
	for(int i=2;i<=k;i++)f[in()]=true;
	dfs(root,0),out(ans);
	return 0;
}
```

-----------------

## 后记

如果讲的不对，欢迎提出问题；如果讲得不清楚，欢迎提问。

---

## 作者：Walrus (赞：2)

赛后 10 秒过 D 什么实力。

## 题意

有 $n$ 个点的树，再指定 $k$ 个点，你可以删除一些点和边，求剩下的点和边**构成一棵树**且包含所有指定的 $k$ 个点的树的最小点数。

## 做法

一个比较显然的思路是暴力跑每一对点之间的路径所经过的点，由于这是一棵树，所以只有唯一路径，所以预处理出 $fa$ 数组接着选定一个指定点然后将剩余所有指定点暴力上跳，经过的点数量就是答案。

但这样显然会 T，有个小优化（比赛结束前 10 秒想到），如果上跳途中遇到已经跳过的点，说明有其他点已经经过了这条路径，由于路径唯一，所以不需要继续上跳。

时间复杂度应该是 $O(N)$，因为每个点只会被跳到一次。

```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pre(i, j, k) for(int i = j; i >= k; --i)
#define pb push_back
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, u, v, k, fa[N], dep[N];
vector<int> e[N], p;
set<int> st;

void dfs(int x, int f) {
	for(auto y : e[x]) {
		if(y == f) continue;
		fa[y] = x, dep[y] = dep[x] + 1;
		dfs(y, x);	
	}
}

void up(int x) {
	if(x == u || st.count(x)) return;//注意这个地方和下面别写反了
	st.insert(x);//结束前2秒没编译直接交结果写反了直接坐牢
	up(fa[x]);
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> k;
	rep(i, 1, n - 1) cin >> u >> v, e[u].pb(v), e[v].pb(u);
	cin >> u; st.insert(u);
	rep(i, 2, k) cin >> v, p.pb(v);
	dfs(u, 0);
	for(auto x : p) up(x);
	cout << st.size();
	return 0;
}
```

---

## 作者：linjinkun (赞：2)

其实这道题和 [P10723](https://www.luogu.com.cn/problem/P10723) 本质上是差不多的。

题目大意就是给你一棵树，问你最少需要保留多少个结点，使得这些节点包含 $V$，并且是一棵树。那么就简单了，想想这道题和 [P10723](https://www.luogu.com.cn/problem/P10723) 的题目，我们立刻可以将这道题转化成那道题：我们将要保留的点集全部染成黑色，其他的点全部都染成白色，用 [P10723](https://www.luogu.com.cn/problem/P10723) 的思路跑一遍，最后输出 $k+ans$ 就行了（$ans$ 是跑出来的答案）。原理不用我解释了，自己想想都知道为什么了吧。

这里简单介绍一下 [P10723](https://www.luogu.com.cn/problem/P10723) 的解法，找到第一个或最后一个黑点，```dfs``` 一遍，中间加上一句判断，如果当前结点是白色并且它的儿子是黑色，那么必须将当前结点染成黑色，这里给出核心代码：
```cpp
void dfs(int x,int fa)
{
	for(int i = head[x];i;i = t[i].nxt)
	{
		int v = t[i].to;
		if(v!=fa)
		{
			dfs(v,x);
			if(a[v]&&!a[x])//注：1代表黑色，0代表白色
			{
				ans++;
				a[x] = 1;
			}
		}
	}
}
```
最后给出全部代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5+5;//如果你写链式前向星，一定得把数组开两倍
struct node
{
	int to;
	int nxt;
}t[N];
int head[N];
int cnt;
int a[N];
int ans;
void dfs(int x,int fa)
{
	for(int i = head[x];i;i = t[i].nxt)
	{
		int v = t[i].to;
		if(v!=fa)
		{
			dfs(v,x);
			if(a[v]&&!a[x])
			{
				ans++;
				a[x] = 1;
			}
		}
	}
}
signed main()
{
	int n,s,k;
	scanf("%d %d",&n,&k);
	for(int i = 1;i<n;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		t[++cnt].to = y;
		t[cnt].nxt = head[x];
		head[x] = cnt;
		t[++cnt].to = x;
		t[cnt].nxt = head[y];
		head[y] = cnt;
	}
	for(int i = 1;i<=k;i++)
	{
		int x;
		scanf("%d",&x);
		a[x] = 1;
	}
	for(int i = 1;i<=n;i++)
	{
		if(a[i])
		{
			s = i;
		}
	}
	dfs(s,0);
	printf("%d",ans+k);
	return 0;
}
```

---

## 作者：Xuan_qwq (赞：1)

### 题面大意
给定一棵树和一个点集 $V$，求最小的包含这个点集的连通子图的大小。
### 思路
很容易知道这个连通子图是唯一的。树上求子图，想到树上动规。

设 $dp_u$ 表示为以 $u$ 为根的子树中含给定节点的数量。很容易可以得到转移方程：
$$dp_u=(u\in V)+\sum_{v\in son[u]}dp_v$$
答案就是 $dp$ 数组中非零元素个数。

但是这里有一个问题，就是 $V$ 中所有点的最近公共祖先到树根这一段节点对应的 $dp$ 数组是非零的，但这些节点并不包含在我们要求的连通子图中，怎么办呢？

不需要写求最近公共祖先，只需要在做 $dp$ 的时候强制以 $V$ 中的一个节点为根就可以了。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[200005];
vector<int>G[200005];
int dp[200005];
void dfs(int u,int fa){
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==fa)continue;
		dfs(v,u);
		dp[u]+=dp[v];
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=0;i<k;i++)cin>>a[i],dp[a[i]]=1;//dp初始值
	dfs(a[0],-1);//强制以V中节点为根
	int ans=0;
	for(int i=1;i<=n;i++)if(dp[i])ans++;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：AlexandreLea (赞：1)

## 题目大意

给定一棵 $n$ 个节点的树以及要求的 $k$ 个节点，求最少保留多少节点能使的所有要求的 $k$ 个节点连通。

## 题目思路

我用了一种诡异的方法来做这道题。本题我采用了递归的统计方法。

这样，我们只需要递归地统计是否有节点在子树中，且如果有的话自己这个节点也需要算入。

但是，如果我们以 $1$ 为根节点，你就死定了，这个算法会在最小的点延长出一条链来，所以我们不能以 $1$ 为根，而以某个要求的点为根。

这题就诡异的 AC 了。时间复杂度为 $O(n)$（不考虑 STL）。代码如下。

```cpp
// ABC368D - Minimum Steiner Tree
// Code by Alexandre Lea
#include <bits/stdc++.h>
using namespace std;
const int N=2'00'005;
int n,fa[N][17],dep[N],k,x;
vector<int> tr[N];
set<int> son[N],requ;
void dfs(int u,int f){
    fa[u][0]=f,dep[u]=dep[f]+1;
    for(int v:tr[u]){
        if(v==f) continue;
        son[u].insert(v);
        dfs(v,u);
    }
}
int cnt(int u){
    bool cont=0;
    int ans=0;
    for(int v:son[u]){
        int re=cnt(v);
        if(re!=0) cont=1;
        ans+=re;
    }
    ans+=(cont||requ.count(u));
    // cerr<<"c "<<u<<" = "<<ans<<endl;
    return ans;
}
int main(){
    cin>>n>>k;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        tr[u].push_back(v),tr[v].push_back(u);
    }
    for(int i=1;i<=k;++i){
        cin>>x;
        requ.insert(x);
    }
    dfs(*requ.begin(),0);
    cout<<cnt(*requ.begin())<<endl;
    return 0;
}
```

**EOF**

---

## 作者：lucasincyber (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc368_d)
## 思路 
很显然，每次删除的点一定有两个要求：

1. 不在 $v_i$ 里；
2. 度数为 $1$ （因为是无向图）

那就可以用拓扑排序解决，删除时只需判断以上两个条件是否满足。若满足，就将其删除，同时将与其相连的点的度数减 $1$。最后统计一下一共删了多少个点。

时间复杂度 $O(n)$，可以通过本题。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, k, ans;
int a[N], deg[N];
bool must[N];
vector<int> tr[N];
queue<int> q;

int main()
{
 	scanf("%d%d", &n, &k);
 	for (int i = 1, u, v; i < n; i++)
    {
    	scanf("%d%d", &u, &v);
    	tr[u].push_back(v);
    	tr[v].push_back(u);
    	deg[u]++, deg[v]++;
	}
	ans = n;
	for (int i = 1; i <= k; i++)
	{
		scanf("%d", &a[i]);
		must[a[i]] = true;
	}
	for (int i = 1; i <= n; i++)
		if (!must[i] && deg[i] == 1)
			q.push(i);
	while (q.size()) // 拓扑
	{
		int u = q.front();
		q.pop();
		ans--;
		for (auto v : tr[u])
		{
			if (!must[v]) // 判断能否删除
			{
				deg[v]--;
				if (deg[v] == 1) q.push(v);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}

```

---

## 作者：zhouzihang1 (赞：1)

# AT_abc368_d [ABC368D] Minimum Steiner Tree 题解

## 题意

给出 $n$ 个点的树，和一些关键点，从 $n$ 个点中选出最少的点，使得包含所有关键点且连通。

## 思路

树形 dp。

以下部分以 $1$ 为根。

记 $g_i$ 表示以 $i$ 为根的子树中有无关键点，若 $i$ 是关键点，则 $g_i = 1$。

记 $d_i$ 表示若 $g_i = 1$ 时选出的最少的**边**的个数，则若 $v$ 是 $u$ 的子节点，则 $d_u \leftarrow d_u  + d_v + 1$。

容易发现，答案存储在所有关键点的 LCA 处。

## AC Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int n, k, a[N], g[N], d[N], b[N];
vector<int> vc[N];
void dfs(int u, int fa) {
	if(a[u]) g[u] = 1;
	for(int v : vc[u]) {
		if(v == fa) continue;
		dfs(v, u);
		if(g[v]) {
			g[u] = 1;
			d[u] += d[v] + 1;
		}
	}
}

int f[N][22], dep[N], mx;
void init() {
	mx = log2(n) + 1;
	for(int j = 1; j <= mx; j++)
		for(int i = 1; i <= n; i++)
			f[i][j] = f[f[i][j - 1]][j - 1];
}
void dfs1(int u, int fa) {
	f[u][0] = fa;
	dep[u] = dep[fa] + 1;
	for(int v : vc[u])
		if(v != fa) dfs1(v, u);
}
int lca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = mx; i >= 0; i--)
		if(dep[f[u][i]] >= dep[v]) u = f[u][i];
	if(u == v) return u;
	for(int k = mx; k >= 0; k--)
		if(f[u][k] != f[v][k])
			u = f[u][k], v = f[v][k];
	return f[u][0];
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	for(int i = 1; i <= k; i++) scanf("%d", &b[i]), a[b[i]] = 1;
	dfs(1, 0);
	dfs1(1, 0);
	init();
	int lc = b[1];
	for(int i = 2; i <= k; i++) lc = lca(lc, b[i]);
	printf("%d\n", d[lc] + 1);
	return 0;
}
```

## 思考

我们发现所有关键点的 LCA 一定会选，所以我们可以找 LCA 处的答案，但是实际上只需要找一个一定选的点作为根求解即可，所以完全不需要处理 LCA，只需要随便找一个关键点作为根即可。

~~另外感觉 D 有原题，好像见过。~~

---

## 作者：qzmoot (赞：1)

# AT_abc368_d
## 题目大意
给你一颗树，再给你一个大小为 $k$ 的点集，要求你求出一颗大小最小的子树，包含点集里的所有点。输出最小子树的大小。
## 分析
这道题目可能有点裸，是虚树的板子。虚树的实现方法你们可以查看洛谷上的其他模板题目。我就不多赘述了。

在建完虚树后，因为虚树并不是严格意义上的子树，他中间省略了关键点之间的链，我们只用在虚树上 dfs 一遍，对于每个点之间的链的长度，就直接用深度来计算即可。
## Code
```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=2e5+5;
int n,k,s[N],dfn[N],idx,dep[N],f[N][25];
vector<int>a[N],na[N];
int st[N],top=0;
int ans;
bool cmp(int x,int y)
{
	return dfn[x]<dfn[y];
}
void dfs(int u,int fa)
{
	dfn[u]=++idx;
	dep[u]=dep[fa]+1;
	for(int i=1;(1<<i)<=dep[u];i++)
		f[u][i]=f[f[u][i-1]][i-1];
	for(auto v:a[u])
	{
		if(v==fa)
			continue;
		f[v][0]=u;
		dfs(v,u);
	}	
}
int lca(int x,int y)
{
	if(dep[x]>dep[y])
		swap(x,y);
	for(int i=20;i>=0;i--)
		if(dep[x]<=dep[y]-(1<<i))
			y=f[y][i];
	if(x==y)
		return x;
	for(int i=20;i>=0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
void dfs1(int u)
{
	ans++;//节点本身要算上 
	for(auto v:na[u])
	{
		ans+=dep[v]-dep[u]-1;//节点之间链的长度也要算上 
		dfs1(v);
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		a[u].pb(v),a[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=k;i++)
		scanf("%d",&s[i]);
	//对关键点按照dfn序排序，这样保证了建树时的顺序 
	sort(s+1,s+1+k,cmp);
	st[++top]=s[1];
	for(int i=2;i<=k;i++)
	{
		int u=s[i];
		int l=lca(u,st[top]);
		while(1)
		{
			if(dep[l]>=dep[st[top-1]])
			{
				if(l!=st[top])
				{
					na[l].pb(st[top]);
					if(l!=st[top-1])
						st[top]=l;
					else
						top--;
				}
				break;
			}
			else
			{
				na[st[top-1]].pb(st[top]);
				top--;
			}
		}
		st[++top]=u;
	}
	while(--top)
		na[st[top]].pb(st[top+1]);
	//搜索答案 
	dfs1(st[1]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

首先求出所有给定点的 LCA，则所有给定点到 LCA 路径上的所有点都需要被经过。

那么实际上就是给路径上的点全部加 $1$，最后判断有多少个点非 $0$。

这可以使用树上差分，对于每个给定的点，把该点差分值 $+1$，LCA 的父亲差分值 $-1$。

代码很好写，不放了。

---

## 作者：_HCl_ (赞：0)

简单的树形 DP，来水一篇题解。

# ABC368D 题解

**题意简述**

给定一棵树 $T$ 和一个点的集合 $S$。现在要求在 $T$ 中删除一些边和节点，产生的新图依然是一棵树且 $S$ 包含于其点集。求生成的新树最小的点数。

**思路引导**

我们可以认为是在树上给节点染色，染色的节点可以被组成新树。

很容易想到树形 DP。一个很自然的想法是，对于一个节点，如果它的儿子需要被染色，那么该节点也需要被染色。

（下面是我赛时思路，这个状态设置可能比较神经，读者可以自行思考）

设 $f_x$ 表示以 $x$ 为根的子树（除 $x$ 本身）内需要染色的节点数，可以列出方程：

$$
f_x=\sum_{y\in \text{son}_x}(f_y+1)[y\in S\ \text{or}\ f_y>0]
$$

但是这样显然是有问题的，从根节点向下的一些节点实际上是不用染的。那么我们可以在树形 DP 结束后再进行处理。模拟从根节点向下，遇到一个节点就把它删掉，直到碰到了在 $S$ 中的点或有大于 $1$ 个儿子的点（作为 LCA 不能删）退出。

（这样说可能比较抽象，建议读者画图理解）

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
int tag[N],f[N],cnt[N],son[N];
vector<int> e[N];
int n,k;
void dfs(int x,int fa){
	for(auto y:e[x]){
		if(y==fa)continue;
		dfs(y,x);
		if(tag[y]||f[y])f[x]++;
		f[x]+=f[y];
		if(tag[y]||f[y])son[x]=y,cnt[x]++;
	}
}
int main(){
	cin>>n>>k;
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=k;++i){
		int x;
		scanf("%d",&x);
		tag[x]=1;
	}
	dfs(1,0);
	int ans=f[1]+1,cur=1;
	while(1){
		if(tag[cur]||cnt[cur]!=1)break;
		ans--;
		cur=son[cur];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：stripe_python (赞：0)

所求的树包含所求点两两简单路径上的所有点。

证明：反证法，如果一个点不包含在这 $k^2$ 条简单路径上，则这个点没必要加入，故不优。

$k$ 个所求点中任意排列并顺次连接的 $k-1$ 条简单路径与之等价。

感性理解：考虑一棵三个点的树，$1$ 到 $2$ 与 $2$ 到 $3$ 的简单路径的并和 $1$ 到 $3$ 相同。更复杂的情况类似。

所以使用树上差分 / 树剖对这 $k$ 个点之间的 $k-1$ 条简单路径更新即可。注意特判 $k=1$。

本蒟蒻写了树剖，复杂度 $O(k \log^2n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int tot = 0, head[N];
struct Edge {
	int next, to;
} edge[N << 1];
inline void add_edge(int u, int v) {
	edge[++tot].next = head[u], edge[tot].to = v, head[u] = tot;
}
int n, k, u, v, a[N], b[N];
void _main() {
	cin >> n >> k;
	if (k == 1) return cout << 1, void();
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		add_edge(u, v), add_edge(v, u);
	}
	for (int i = 1; i <= k; i++) cin >> a[i];
	HPD<int> hpd(1, b);
	SegmentTree<int> sgt(b, n);
	for (int i = 1; i < k; i++) {
		hpd.update_chain(a[i], a[i + 1], [&](int l, int r) {
			sgt.update(l, r, 1);
		});
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (sgt.query(i, i) >= 1) cnt++;
	}
	cout << cnt;
} 
```

---

## 作者：LuukLuuk (赞：0)

# 题解：AT_abc368_d [ABC368D] Minimum Steiner Tree
### 题目大意
给你一颗 $n$ 个节点的树，让你求保留 $v_1,\dots,v_k$ 节点联通的情况下最多可以删去多少节点，输出此时树中剩下的节点数。

数据范围：

- $1 \le n,k \le 2 \times 10^5$

### 思路
选一个要**保留**的节点，以它为根进行深搜，深搜时根据儿子节点是否要保留的情况决定它的保留情况。

具体地，用一个数组 $vis$ 表示哪些节点将被保留，在输入时标记 $vis_{v_1},\dots,vis_{v_k}$ 为 $1$，搜索时先访问儿子节点 $x_1,\dots,x_m$，再更新当前节点 $vis_u = vis_u \vee vis_{x_1} \vee \dots \vee vis_{x_m}$，表示如果当前点及其儿子中有需要保留的，则当前点将要保留。

### 代码
```cpp
#include <vector>
#include <cstdio>
using namespace std;

vector<int> g[200010];
int vis[200010];
int n, k;
int beg;
int ans;

void dfs(int u, int fa) {
	for (int i = 0; i < g[u].size(); ++i) {
		int v = g[u][i];
		if (v == fa)	continue;
		dfs(v, u);
		vis[u] |= vis[v];//将儿子的情况传给u
	}
	if (vis[u]) ans++;//要保留的节点数加1
}

int main() {
	scanf("%d%d",  &n, &k);
	for (int i = 1, a, b; i < n; ++i) {
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for (int i = 1, x; i <= k; ++i) {
		scanf("%d", &x);
		vis[x] = 1;//标记x要保留
		if (!beg)	beg = x;//找到一个要保留的点
	}
	dfs(beg, 0);//从它开始搜索
	printf("%d", ans);
	return 0;
}

```

---

## 作者：Lame_Joke (赞：0)

- ### 大体思路

  题目要求从原树中挑一颗结点最少的包含 $V$ 数组中所有节点的子树，下面将 $V$ 数组中的结点称为关键结点。不难想到可以以 $V$ 数组中任意一个结点为根来往下搜索，因为树中两点路径唯一，所以从一个关键结点往下搜索，搜到另一个关键结点的路径是唯一的，换个关键结点为根也一样。所以我们可以普通 $DFS$，在 $DFS$ 中多设一个参数，存当前搜索的路径已经包含了多少个结点。如果搜到最后还没搜到关键结点，则不对答案产生贡献；如果搜到关键结点了，那么这条路径的结点数加入贡献，然后搜索下一条路径时从 $0$ 个结点开始。

- ### 具体实现

  ```cpp
  #include<cstdio>
  using namespace std;
  int n,k;
  int nxt[400005],hd[400005],to[400005],cnt;
  bool bz[200005],bz1[200005];
  void add(int u,int v)
  {
  	nxt[++cnt]=hd[u];
  	hd[u]=cnt;
  	to[cnt]=v;
  }
  int ans=0;
  bool dfs(int x,int cnt)
  {
  	bz[x]=1;
  	bool s=0,s1=0;                   //s是标记路径上的点
  	if(bz1[x]==1)					 //是否已加入贡献
  	{								 //用于返回
  		ans+=cnt;
  		cnt=0;
  		s=1;
  	}
  	for(int i=hd[x];i;i=nxt[i])
  	{
  		if(bz[to[i]]==1) continue;
  		s1=dfs(to[i],cnt+1);
  		if(s1==1) cnt=0,s=1;
  	}
  	if(s==1) return 1;
  	else return 0;
  }
  int main()
  {
  	scanf("%d%d",&n,&k);
  	if(k==n)
  	{
  		printf("%d",n);
  		return 0;
  	}
  	int u,v;
  	n--;
  	while(n--)
  	{
  		scanf("%d%d",&u,&v);
  		add(u,v);
  		add(v,u);
  	}
  	while(k--)
  	{
  		scanf("%d",&v);
  		bz1[v]=1;
  	}
  	dfs(v,1);
  	printf("%d",ans);
  }
  ```

---

## 作者：liruixiong0101 (赞：0)

# D - Minimum Steiner Tree
## 题意：
给定一颗 $n$ 个节点的树，再给定树上的 $k$ 个点 $x_1,x_2,\cdots x_k$，求包含这 $k$ 个点的最小生成树大小。（$1\le k\le n\le 2\times 10^5$）

## 思路：
考虑以 $x_1$ 为根，容易发现若节点 $u$ 一定要被包含，那么其父亲也一定要被包含，考虑设 $vis_i$ 表示节点 $i$ 是否被包含，然后 dfs 遍历每一个节点并回溯转移即可。

## 代码：
<https://atcoder.jp/contests/abc368/submissions/57055501>

---

## 作者：Size_OIer (赞：0)

这是一棵无根树，所以我们先考虑确定一个根。  
如果我们选择一个非标记点为根，假如这个点是可删的，但是作为一个根我们并不能删它，那就是错误的。  
因此我们只能选一个标记点为根，至于选哪一个，这并无影响。  
定根之后，我们考虑对树进行遍历，如果遍历到的点是标记点，就向上把标记传递上去；如果一个点子树中传上来标记，那么自己也打上标记并继续向上传递。  
最后统计答案，有标记的点保留，无标记的点全都删掉。  
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200000+5;
int n,k,rt;
int idx[maxn],ans;
vector<int> edge[maxn];
bool vis[maxn];
inline bool dfs(int u,int fa){
    for(int v:edge[u]){
        if(v==fa) continue;
        bool flag=dfs(v,u);
        vis[u]|=flag;
    }
    return vis[u];
}
int main(){
    memset(vis,false,sizeof(vis));
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        edge[u].push_back(v);
        edge[v].push_back(u);
        idx[u]++,idx[v]++;
    }
    rt=n;
    for(int i=1;i<=k;i++){
        int u;
        cin>>u;
        vis[u]=true;
        rt=min(rt,u);
    }
    dfs(rt,0);
    for(int i=1;i<=n;i++) if(vis[i]) ans++;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：fp0cy1tz6mn4rd_ (赞：0)

只需要简单的遍历，难度：黄。

可以直接将树看作一个无向无环图，不必考虑树根。因此只需要在 $V$ 中随便选一个顶点进行 `dfs`。

搜索时，如果**搜索到点 $p$，且 $p\in V$** 或者 
**$p$ 在往下搜索的时候遇到了点 $q$ 且 $q\in V$**，则保留这个点。

可以用 `unordered_set` 维护 $V$ 和保留的顶点集。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<unordered_set>
using namespace std;
const int N=2e5+5;
int a[N],n,k,u,v,x;
bool vis[N];
vector<int> G[N];
unordered_set<int> Q,E;
bool dfs(int x){
	bool t=false;
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i];
		if(vis[y]) continue;
		vis[y]=true;
		t=dfs(y)||t;
	}
	if(t||Q.count(x)){
		E.insert(x);
		return true;
	}
	return false;
}
signed main(){
	memset(vis,false,sizeof(vis));
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=k;i++){
		cin>>a[i];
		Q.insert(a[i]);
	}
	vis[a[1]]=true;
	dfs(a[1]);
	cout<<E.size()<<endl;
	return 0;
}
```

---

## 作者：coding_goat (赞：0)

# D

注意到当节点 $x$ 被保留，当且仅当 $x \in V$ 或其有一子节点 $y \in V$。故我们 dfs 遍历这个树，用一个数组记录当前节点及其子树需要取的节点数，对于当前的节点 $x$，需要取的节点数为其子树需要取得节点数之和，然后就是如果子树需要取节点或者 $x \in V$，节点数需要加一。

直接以 $V$ 中任意元素开始遍历，输出该元素在数组中的值即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mem(a,b) memset((a),(b),sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
using namespace std;
inline int read()
{
	int xx=0;int f=1;
	char c = getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f = -1;
		c = getchar();
	}
	while(c>='0'&&c<='9')
	{
		xx = (xx<<1)+(xx<<3)+(c^48);
		c = getchar();
	}
	return xx*f;
}
#define maxn 200050
int n,k;
vector<int>G[maxn];
bool vis[maxn];
int cnt[maxn],tmp;
void dfs(int now,int fa)
{
//	cout<<now<<' '<<fa<<'\n';
//	system("pause");
	int res=0;
	for(int i=0;i<(int)G[now].size();i++)
		if(G[now][i]!=fa)
			dfs(G[now][i],now);
	for(int i=0;i<(int)G[now].size();i++)
		if(G[now][i]!=fa)
			res+=cnt[G[now][i]];
	if(res||vis[now]) res++;
	cnt[now]=res;
	return ;
}
signed main()
{
	n=read(),k=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		pb(G[y],x);
		pb(G[x],y);
	}
	for(int i=1;i<=k;i++)
	{
		tmp=read();
		vis[tmp]=1;
	}
	dfs(tmp,-1);
	cout<<cnt[tmp];
	return 0;
}
```

---

## 作者：OIer_Hhy (赞：0)

一道水题。

其实根本就不需要什么 LCA，树链剖分，只需会暴搜即可。

我们自根向下搜索每一个节点的子节点，若子节点中没有必须保留的，且自己也不用保留，则把自己删掉；否则自己必须保留。


然而，如果你把 $1$ 作为根，那你会 WA 在这组数据上：

```cpp
6 1
1 3
4 2
4 5
4 6
3 4
3
```

![](https://cdn.luogu.com.cn/upload/image_hosting/im1nu6nr.png)![](https://cdn.luogu.com.cn/upload/image_hosting/57fz970v.png)

因为你把 $1$ 作为了根，所以你不能删掉 $1$ 号节点。

而实际上，把 $3$ 作为根，就能删掉其他所有节点，这才是最优解。

于是，我们要把 v 数组中的第一个作为根，遍历下去，找出那些可以删掉的节点，才能 AC。

最终的答案就是剩下的节点数。


code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
int n,k,a[N],b[N];
vector<int> e[N];
int ans;
bool dfs(int u,int fa){
	bool f=1;
	for(auto v:e[u]){
		if(v==fa) continue;
		if(b[v]) f=0;
		f&=dfs(v,u); 
	}
	f&=b[u]^1;
	ans+=f;
	return f;
	
}
signed main(){
	cin>>n>>k;
	for(int i=2,u,v;i<=n;i++){
		cin>>u>>v;
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	for(int i=1;i<=k;i++){
		cin>>a[i];
		b[a[i]]=1;
	}
	dfs(a[1],0);
	cout<<n-ans<<'\n';
	return 0;
}


```

---

## 作者：lcezshiyuang (赞：0)

## 题目大意
给定一颗树和一些关键点，要求在保留关键点且最后的图仍是一棵树的情况下尽多删除点。

考虑以任意关键点为根，维护 $ siz $ 数组和 $ has $ 数组，前者表示子树大小，后者表示子树中是否有关键点。那么在 $ dfs $ 时对于每一个 $ has $ 为零且父亲节点 $ has $ 为一的点将其子树大小 $ siz $ 加入贡献 $ ans $。最后输出 $ n-ans $ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,root,ans;
vector<int>e[300000];
bool key[300000];
bool has[300000];
int siz[300000];
void dfs(int u,int fa){
	 siz[u]=1;
	 if(key[u]) has[u]=1;
	 for(auto v:e[u]){
	 	if(v==fa) continue;
	 	dfs(v,u);
	 	siz[u]+=siz[v];
	 	if(has[v]) has[u]=1; 
	 }
	 
}

void dfss(int u,int fa){
	for(auto v:e[u]){
		if(v==fa) continue;
		dfss(v,u);
	}
	if(!has[u]&&has[fa]) ans+=siz[u];
}
signed main(){
cin>>n>>k;
for(int i=1;i<n;i++) {
	int u,v;
	cin>>u>>v;
	e[u].push_back(v);
	e[v].push_back(u);
}
for(int i=1;i<=k;i++){
	int u;
	cin>>u;
	key[u]=1;
	root=u;
}
dfs(root,0);
dfss(root,0);
cout<<n-ans;
	return 0;
}
```
注意求 $ has $ 数组和计算 $ ans $ 要分开，因为在 $ dfs $ 函数中不能直接调用父亲的信息——父亲节点的信息需要其子节点全部递归完毕才准确。

---

## 作者：huangrenheluogu (赞：0)

不妨以 $1$ 为根，考虑 $(x,fa_x)$ 的边有没有贡献。

记 $sz_x$ 为 $x$ 子树内关键点的数量，显然需要 $x$ 子树里和子树外都有关键点，即 $0\lt sz_x\lt k$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, k, a[N], fir[N], nxt[N << 1], son[N << 1], ans, tot;
int sz[N], u, v;
inline void add(int x, int y){
	nxt[++tot] = fir[x];
	fir[x] = tot;
	son[tot] = y;
}
inline void dfs(int x, int ff = 0){
	for(int i = fir[x]; i ; i = nxt[i]){
		if(son[i] == ff) continue ;
		dfs(son[i], x);
		sz[x] += sz[son[i]];
	}
	if(sz[x] < k && sz[x]){
		ans++;
	}
}
int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i < n; i++){
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= k; i++){
		scanf("%d", &u);
		sz[u] = 1;
	}
	dfs(1);
	ans++;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：xxseven (赞：0)

### 题意简述：

给定你一棵 $n$ 个点的无根树，一个大小为 $k$ 的点集 $v$，你需要删除树上的部分边和点使得剩下的部分还是一棵树，且包含点集内的所有点。  
输出新树的最小可能点数。

### 解题思路：

首先我们钦定 $v_1$ 为根，这个显然不劣。

然后肯定是要把点集内的点一个个加进去。由于在树上跳父亲十分方便，我们考虑将点集内的点向上跳。每加入一个节点，就将其跳到根，加入中间的所有点。

但这样的时间复杂度是平方级的，考虑到我们其实跳了许多重复的点，如果在向上跳的途中跳到一个选过的点，它到根的路径上的点一定全部被选了，因此我们直接返回即可。

由于每个点只会被标记一次，时间复杂度为 $O(n)$。下面是赛时代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+6;
vector<int> f[N];
int n,k,v[N],fa[N],used[N],ans;
void dfs(int x,int y){
	fa[x]=y;
	for(int u:f[x]){
		if(u==y) continue;
		dfs(u,x);
	}
}
void add(int x){
	if(used[x]) return;//如果跳到被标记的点，直接返回
	ans++; used[x]=1; add(fa[x]);//否则标记并向上跳
}
int main(){
	cin>>n>>k;
	for(int x,y,i=1;i<n;++i){
		cin>>x>>y;
		f[x].push_back(y); f[y].push_back(x);
	}
	for(int i=1;i<=k;++i){
		cin>>v[i];
	}
	dfs(v[1],0); //钦定v1为根
	used[v[1]]=1; ans=1;
	for(int i=2;i<=k;++i) add(v[i]);
	cout<<ans;
	return 0;
}
```

希望这篇题解能够帮到你！

---

