# [ARC143D] Bridges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc143/tasks/arc143_d

$ 1 $ 以上 $ N $ 以下の整数からなる $ 2 $ つの数列 $ A_1,\ldots,\ A_M $ および $ B_1,\ldots,B_M $ があります．

`0` と `1` からなる長さ $ M $ の文字列に対して，$ 2N $ 頂点 $ (M+N) $ 辺からなる次のような無向グラフを対応させます:

- $ i $ 番目の文字が `0` のとき，$ i $ 番目の辺は頂点 $ A_i $ と頂点 $ (B_i+N) $ を結ぶ辺である．
- $ i $ 番目の文字が `1` のとき，$ i $ 番目の辺は頂点 $ B_i $ と頂点 $ (A_i+N) $ を結ぶ辺である．
- $ (j+M) $ 番目の辺は頂点 $ j $ と頂点 $ (j+N) $ を結ぶ辺である．

ただし，$ i $, $ j $ はそれぞれ $ 1\ \leq\ i\ \leq\ M $, $ 1\ \leq\ j\ \leq\ N $ を満たす整数を動くものとします． また，頂点には $ 1 $ から $ 2N $ までの番号がついています．

対応する無向グラフに含まれる橋の個数が最小となるような，`0` と `1` からなる長さ $ M $ の文字列を $ 1 $ つ求めてください．

 橋について グラフの辺であって，その辺を除くと連結成分の個数が増えるようなものを橋と呼びます．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $

### Sample Explanation 1

`01` に対応するグラフには橋が存在しません． `00` に対応するグラフでは頂点 $ 1 $ と頂点 $ 3 $ を結ぶ辺と頂点 $ 2 $ と頂点 $ 4 $ を結ぶ辺が橋となるので， `00` は条件を満たしません．

## 样例 #1

### 输入

```
2 2
1 1
2 2```

### 输出

```
01```

## 样例 #2

### 输入

```
6 7
1 1 2 3 4 4 5
2 3 3 4 5 6 6```

### 输出

```
0100010```

# 题解

## 作者：LiveZoom (赞：6)

## Description

[link](https://www.luogu.com.cn/problem/AT_arc143_d)

## Solution

首先这个题目描述很像拆点，把每个点拆成入点和出点，每次操作就是给无向边定向。

然后考虑这样一个做法：把 $a_i$ 和 $b_i$ 连上一条双向边，然后在这个 $n$ 个点 $m$ 条边的无向图上跑 dfs，如果不是返祖边，那么就向上定向，否则向下定向。

---

证明一下这个做法的正确性。

首先如果一条边 $(u,v)$ 在无向图上是桥，那么在原图上无论怎么连也都是桥。因为在原图上，只有这条边连接了 $u$ 和 $v$ 所在的连通块，所以它在原图上也一定是桥。

然后这么跑 dfs 相当于建出了很多强连通分量，如果 $u\to v$ 和 $v\to u$ 各有一条路径，删一条边一定不会影响连通性。

所以这样跑肯定是最小的。

时间复杂度：$O(n+m)$

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 5;

int n, m;
int a[kMaxN], b[kMaxN], dir[kMaxN];
bool vis[kMaxN], vise[kMaxN];
vector<pair<int, int>> G[kMaxN];

void dfs(int u, int fa) {
  // cerr << u << ' ' << fa << '\n';
  vis[u] = 1;
  for (auto [v, p] : G[u]) {
    if (vise[p]) continue;
    vise[p] = 1;
    // cerr << u << ' ' << v << '\n';
    if (vis[v]) {
      // cerr << "黑哥\n";
      dir[p] = (u == b[p] && v == a[p]);
    } else {
      dir[p] = (u == b[p] && v == a[p]);
      dfs(v, u);
    }
  }
}

int main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> b[i];
    G[a[i]].emplace_back(b[i], i);
    G[b[i]].emplace_back(a[i], i);
  }
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) {
      dfs(i, 0);
    }
  }
  for (int i = 1; i <= m; ++i)
    cout << dir[i];
  return 0;
}
```

---

## 作者：lhyuu (赞：2)

一种可能不是很一样的想法。

题目让我们在 $(A_i,B_i+N)$ 和 $(B_i,A_i+N)$ 中选一个，不妨两个都选，最后再考虑删一条。

然后因为 $(i,i+N)$ 之间有边，可以画画图，发现操作 $i$ 会造成的影响是连出一个以 $A_i,A_i+N,B_i,B_i+N$ 为顶点的四边形。

大概是长这样的。
![](https://cdn.luogu.com.cn/upload/image_hosting/i8yyjbz5.png)

然后红色的是要考虑删掉的，一个小正方形里二选一删掉。

![](https://cdn.luogu.com.cn/upload/image_hosting/dkid401n.png)

然后发现怎么删都无济于事。每条边都可以做桥。

再一想原来可能有环。
![](https://cdn.luogu.com.cn/upload/image_hosting/agbd5rsx.png)

因为你不想要桥，所以你删边的时候最后剩余一个环。

于是这样选：

![](https://cdn.luogu.com.cn/upload/image_hosting/kmza3tpy.png)

图画的丑，勉强看看吧。奇数个点的情况本质上是一样的。

也就是轮流选。对于当前点 $A$，先选边 $(A,B+N)$，再选 $(B+N,C)...$ 以此类推。可以发现 $0,1$ 是可以整体互换的，代码非常好写。


```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define mpr make_pair
#define x first
#define y second
#define up(i, a, b) for(int i = a; i <= (int)b; ++i)
#define dn(i, a, b) for(int i = a; i >= (int)b; --i)
#define vc vector
#define pb push_back
#define itset set< int >::iterator
#define lowbit(x) (x & -x)

using namespace std;

void chkmin(int &x, int y){x = min(x, y);}
void chkmax(int &x, int y){x = max(x, y);}

const int MN = 2e5 + 5;

int n, m, a[MN], b[MN];
struct node{
	int to, op, id;
};
vc< node > v[MN];
int vis[MN], ans[MN];

void dfs(int x){
	vis[x] = 1;
	for(node w : v[x]){
		int y = w.to;
		if(!ans[w.id]) ans[w.id] = w.op + 1;
		if(vis[y]) continue;
		dfs(y);
	}
}

signed main(){
	scanf("%d%d", &n, &m);
	up(i, 1, m) scanf("%d", &a[i]);
	up(i, 1, m){
		scanf("%d", &b[i]);
		v[a[i]].pb((node){b[i], 0, i});
		v[b[i]].pb((node){a[i], 1, i});
	}
	up(i, 1, n) if(!vis[i]) dfs(i);
	up(i, 1, m) printf("%d", ans[i] - 1);
	
	return 0;
}
```

---

## 作者：住在隔壁小莘 (赞：2)

# [Atcoder ABC143](https://atcoder.jp/contests/arc143)

[更好的阅读](https://blog.xinzirui.cn/solve/Atcoder/ARC143%20D/)

## [D - Bridges](https://atcoder.jp/contests/arc143/tasks/arc143_d)

### 题面

我们有两个序列 $A_1,\ldots, A_M$ 和 $B_1,\ldots,B_M$，分别由 $1$ 和 $N$（含）之间的内格组成。

对于由 "0" 和 "1" 组成的长度为 $M$ 的字符串，请考虑以下与该字符串对应的有 $2N$ 个顶点和 $(M+N)$ 条边的无向图。

- 如果字符串的 $i$ 个字符是 "0"，那么 $i$ 条边连接顶点 $A_i$ 和顶点 $(B_i+N)$。
- 如果字符串的第 $i$ 个字符是 "1"，那么第 $i$ 条边连接顶点 $B_i$ 和顶点 $(A_i+N)$。
- 第 $(j+M)$ 条边连接顶点 $j$ 和顶点 $(j+N)$。

这里，$i$ 和 $j$ 是整数，即 $1 \leq i \leq M$ 和 $1 \leq j \leq N$，顶点的编号为 $1$  至 $2N$。

请找出一个长度为 $M$ 的字符串，由 "0" 和 "1" 组成，使得相应的无向图中的桥的数量最少。

关于桥的说明：桥是图中的一条边，删除它可以增加相连部分的数量。


#### 分析

数字 `0` 和 `1` 其实就是决定了连接 $a[i]与b[i]$ 的边是谁指向谁，也就是无向边定向。那么问题就转化成了决定无向边的方向，使得图中的桥最小。

其实这里有个地方需要注意，转化成连接 $a[i]与b[i]$ 是根据题目中的中间节点 $j+N$ 转化来的。根据例一，如果我们输出 `00`，那么这个图是这样的。
![](https://s2.loli.net/2023/10/15/SK4qchQ9jO31fHR.png)

显而易见，他是有两个桥的。

如果是 `01` 则就一个桥都没有。

![](https://s2.loli.net/2023/10/15/sRAMWuKC7PJroNV.png)

还有一个显而易见的，如果在无向图的情况下就出现了“割边”的情况，那么当它成为一个有向图那么它肯定还是割边，所以不用在意他的方向。

那么接下来思考如何给无向边定向，边双连通分量变成强联通分量，就是相当于在一棵树上多了几条返祖边，那么我们可以用 $DFS$ 序来建树，正常边向下，返祖边向上，再注意一下建的是双向边，所以两条边其实是一条边，记得判定一下就好。

#### 解法

建立双向边，跑 $DFS$,不走重复的边，不走走过的点，把答案记在边上，一条边为 `0`，另一条为 `1`，这样就结束啦。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <iomanip>
using namespace std;
const int MAXN=1e6+10;
struct edge{
	int nex,to,val,top;
}p[MAXN];
int head[MAXN],cnt=1,tot,num,dfn[MAXN],low[MAXN];//cnt从一开始，那么第一条边的序号为2，方便异或

//一开始还以为需要tarjan，写了半天发现貌似用不到……
bool vis[MAXN],vis1[MAXN];
int a[MAXN],b[MAXN],belong[MAXN],ans[MAXN];
stack<int>st;
vector<int>dis[MAXN];
void add(int from,int to,int val,int top){
	p[++cnt]=edge{head[from],to,val,top};
	head[from]=cnt;
}
void dfs2(int now,int fa){
	if(vis1[now]){
		return;
	}
	vis1[now]=true;
	for(int i=head[now];i;i=p[i].nex){
		int to=p[i].to;
		if(vis[i]){//建的双向边
			continue;
		}
		vis[i^1]=vis[i]=true;
		ans[i]=1;
		ans[i^1]=0;
		dfs2(to,now);
	}
	return ;
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	for(int i=1;i<=m;i++){
		add(a[i],b[i],i,a[i]);
		add(b[i],a[i],i,a[i]);
	}
	for(int i=1;i<=n;i++){
		if(!vis1[i]){
			dfs2(i,0);
		}
	}
	for(int i=1;i<=m;i++){
		cout<<ans[(i<<1)];
	}
}
```



---

## 作者：xuantianhao (赞：2)

# [[ARC143D] Bridges](https://www.luogu.com.cn/problem/AT_arc143_d)

题意：给定 $2n$ 个点和 $(u_1,v_1) , \cdots , (u_m,v_m)$，选择让 $u_i$ 连 $v_i+n$ 或 $v_i$ 连 $u_i+n$，以最小化图中桥的个数。

有种技巧叫拆点，把一个点拆成入点和出点，看这个形式非常像拆点，于是先想想合并。

若有 $n$ 个点，连上所有 $u_i$ 和 $v_i$，是桥的边在原图中只能是桥（路径唯一），抛出结论：可以通过构造，让其他边均不是桥。

如果现在在看一个连通块，只需要通过把边重定向以使得这一块强连通，即可。

考虑去掉那些桥后一个一个连通块处理：顺着 DFS 树走下去，遇到返祖边向上定向，否则向下定向，即得。

以前听说过拆点这个想法，但这是第一次见到，甚至连可以合并两个点都没想到，只能说是发散思维的极大不足了。确实想到了某种 $i$ 与 $i+n$ 间奇怪的对应关系，但“桥”导致往 tarjan 上想，这是复杂化了问题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e6+100;
struct node{
	int to,next;
}e[N];
int n,m,cnt=1;
int a[N],b[N],head[N],dir[N];
bool vis[N],vis1[N];
void add(int x,int y){
	e[++cnt]={y,head[x]};
	head[x]=cnt;
}
void dfs(int now,int fa){
	if(vis1[now]) return ;
	vis1[now]=1;
	for(int i=head[now];i;i=e[i].next){
		int v=e[i].to;
		if((i^1)==fa||vis[i]) continue;
		vis[i^1]=vis[i]=1;
		dir[i]=1;
		dir[i^1]=0;
		dfs(v,i);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	for(int i=1;i<=m;i++) add(a[i],b[i]),add(b[i],a[i]);
	for(int i=1;i<=n;i++) if(!vis1[i]) dfs(i,0);
	for(int i=1;i<=m;i++) cout<<dir[i<<1];
	return 0;
}
```


---

## 作者：XiaoQuQu (赞：1)

一直下定决心写这题，但是好多次还是没写，这次终于写了，发个题解纪念下。

首先考虑有哪些边最终一定会成为割边。我们将 $i,i+n$ 合并成一个点，相当于是在这个无向图中，对于给出的 $a_i,b_i$ 定向。如果一条边 $(u,v)$ 在我们的这个无向图中是割边，那么我们在原图中无论如何连接，它肯定也将会是一个割边。

对于那些在无向图中不是割边的边，我们考虑如何将他定向，使得他们形成一个强连通分量，一个非常显然的方法是，对于树边正向，对于返祖边反向，如下图。

![](https://img.zshfoj.com/d0d7c5609faac4590a49d0244f32333c17097bdce47e3f921e2f6775f19b56e8.png)

知道了这个结论，我们改如何构造答案？假设我们当前遍历到了 $(u,v)$ 这条边，然后进行分类讨论：

1. $u$ 对应 $a_i$，且 $(u,v)$ 不是返祖边：连接 $u\to v$，答案为 $0$。
2. $u$ 对应 $a_i$，且 $(u,v)$ 是返祖边：连接 $u\to v$，答案为 $0$。
3. $u$ 对应 $b_i$，且 $(u,v)$ 不是返祖边：连接 $v\to u$，答案为 $1$。
4. $u$ 对应 $b_i$，且 $(u,v)$ 是返祖边：连接 $v\to u$，答案为 $1$。

于是我们发现，答案为 $1$ 当且仅当 $u$ 对应 $b_i$，与 $(u,v)$ 是否为返祖边无关。

```cpp
const int MAXN = 2e5 + 5;
int n, m, tot, a[MAXN], b[MAXN], ans[MAXN], vis[MAXN], dfn[MAXN];
struct _node {
	int v, id;
};
vector<_node> G[MAXN];

void dfs(int x) {
	dfn[x] = ++tot;
	for (auto [u, id]:G[x]) {
		if (vis[id]) continue;
		vis[id] = true;
		ans[id] = (x != a[id]);
		if (!dfn[u]) dfs(u);
	}
}

void work() {
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) cin >> a[i];
	for (int i = 1; i <= m; ++i) cin >> b[i];
	for (int i = 1; i <= m; ++i) {
		G[a[i]].push_back({b[i], i});
		G[b[i]].push_back({a[i], i});
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= m; ++i)
		cout << ans[i];
	cout << endl;
}
```



---

## 作者：binbin_200811 (赞：0)

# [ARC143D Bridges](https://www.luogu.com.cn/problem/AT_arc143_d)

巧妙的图论题。

### 思路

分析题目，发现很像拆点。

由于拆点要设置出入点，这里我们也把 $a_i$ 设成入点，把 $a_i+n$ 设成出点，再次分析问题。

考虑我们把拆的点合并成一个点，对于 $(a_i,b_i)$ 建边，建出图 $G$。

不难发现，原图是图 $G$ 展开后的形态，且只有按照出入点的方式构造图 $G$ 才是最优解，可以考虑把此图还原原图。

我们只需要找一个点开始一个点一个点的把图 $G$ 遍历出了就 OK（记得删边，边不可以走两次）。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=4e5+5;

struct Edge
{
    int tot;
    int head[maxn];
    struct edgenode{int to,nxt,num;}edge[maxn*2];
    void add(int u,int v,int z)
    {
        tot++;
        edge[tot].to=v;
        edge[tot].nxt=head[u];
        edge[tot].num=z;
        head[u]=tot;
    }
}G;

int n,m;
int a[maxn],b[maxn],ans[maxn];

bool vis[maxn],cis[maxn];

void dfs(int u)
{
    vis[u]=1;
    for(int i=G.head[u];i;i=G.edge[i].nxt)
    {
        int v=G.edge[i].to;
        if(cis[G.edge[i].num]) continue;
        cis[G.edge[i].num]=1;
        ans[G.edge[i].num]=(a[G.edge[i].num]==u);
        if(vis[v]) continue;
        dfs(v);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    for(int i=1;i<=m;i++) G.add(a[i],b[i],i),G.add(b[i],a[i],i);
    for(int i=1;i<=n;i++)
        if(!vis[i]) dfs(i);
    for(int i=1;i<=m;i++) printf("%d",ans[i]);
}
```



---

## 作者：XYQ_102 (赞：0)

## 思路
如果一条边不是割边， 那么他应该存在于一个环上。 考虑把它当成一条有向边， 你的任务就是给这些有向边定向， 因为实际上你只是需要从一个点出发找一条能回到自己的回路。 如果找不到的话， 那么这个点肯定会被割开。

那么我们只需要把它当成一个未定向的有向图， 然后在图上找环， 并定向即可。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
#define pb push_back
#define ln '\n'
const int N = 2e5+5;
const int mod = 998244353;
inline void inc(int &a, int b){
    a+=b;
    if(a>=mod) a-=mod;
}
inline void dec(int &a, int b){
  a-=b;
  if(a<0) a+=mod;
}
int vis[N];
vector<tuple<int,int,int>>e[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int>a(m+1), b(m+1);
    vector<char>s(m+1, '?');
    for(int i=1; i<=m; i++)
    	cin >> a[i];
    for(int i=1; i<=m; i++)
    	cin >> b[i];
    for(int i=1; i<=m; i++){
    	int u = a[i], v = b[i];
    	e[u].pb({v, i, 0});
    	e[v].pb({u, i, 1});
    }
    function<void(int)> dfs = [&](int u){
		if(vis[u]) return;
		vis[u] = 1;
		for(auto [v, id, w]: e[u]){
			if(s[id] == '?')
				s[id] = '0' + w;
			dfs(v);
		}
	};
    for(int i=1; i<=n; i++)
    	dfs(i);
    for(int i=1; i<=m; i++)
    	cout << s[i];
}
```

---

