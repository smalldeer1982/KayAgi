# [ABC341F] Breakdown

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc341/tasks/abc341_f

$ N $ 個の頂点と $ M $ 本の辺からなる単純な無向グラフが与えられます。 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結ぶ辺です。 また、$ i\ =\ 1,\ 2,\ \ldots,\ N $ について、頂点 $ i $ には正整数 $ W_i $ が割り当てられており、$ A_i $ 個のコマが置かれています。

グラフ上にコマが存在する限り、下記の操作を繰り返します。

- まず、グラフ上のコマを $ 1 $ 個選んで取り除き、そのコマが置かれていた頂点を $ x $ とおく。
- $ x $ に隣接するいくつかの頂点からなる（空でも良い）集合 $ S $ であって、$ \sum_{y\ \in\ S}\ W_y\ \lt\ W_x $ であるものを選び、$ S $ に含まれる頂点それぞれに $ 1 $ 個ずつコマを置く。

操作を行う回数としてあり得る最大値を出力してください。

なお、どのように操作を行っても、有限回の操作の後にはグラフ上にコマが存在しない状態に至ることが証明出来ます。

## 说明/提示

### 制約

- 入力される値はすべて整数
- $ 2\ \leq\ N\ \leq\ 5000 $
- $ 1\ \leq\ M\ \leq\ \min\ \lbrace\ N(N-1)/2,\ 5000\ \rbrace $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- $ u_i\ \neq\ v_i $
- $ i\ \neq\ j\ \implies\ \lbrace\ u_i,\ v_i\ \rbrace\ \neq\ \lbrace\ u_j,\ v_j\ \rbrace $
- $ 1\ \leq\ W_i\ \leq\ 5000 $
- $ 0\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

以下の説明では、各頂点にあるコマの個数を、数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ として表します。 はじめ、$ A\ =\ (1,\ 0,\ 0,\ 0,\ 0,\ 1) $ です。 下記の手順で操作を行うことを考えます。 - 頂点 $ 1 $ にあるコマを $ 1 $ 個取り除き、頂点 $ 2,\ 3 $ にコマを $ 1 $ 個ずつ置く。その結果、$ A\ =\ (0,\ 1,\ 1,\ 0,\ 0,\ 1) $ となる。 - 頂点 $ 2 $ にあるコマを $ 1 $ 個取り除く。その結果、$ A\ =\ (0,\ 0,\ 1,\ 0,\ 0,\ 1) $ となる。 - 頂点 $ 6 $ にあるコマを $ 1 $ 個取り除く。その結果、$ A\ =\ (0,\ 0,\ 1,\ 0,\ 0,\ 0) $ となる。 - 頂点 $ 3 $ にあるコマを $ 1 $ 個取り除き、頂点 $ 2 $ にコマを $ 1 $ 個置く。その結果、$ A\ =\ (0,\ 1,\ 0,\ 0,\ 0,\ 0) $ となる。 - 頂点 $ 2 $ にあるコマを $ 1 $ 個取り除く。その結果、$ A\ =\ (0,\ 0,\ 0,\ 0,\ 0,\ 0) $ となる。 上記の手順で操作を行う回数は $ 5 $ 回であり、これが操作を行う回数としてあり得る最大値です。

### Sample Explanation 2

この入力例では、はじめからグラフ上にコマが存在しません。

## 样例 #1

### 输入

```
6 6
1 2
2 3
3 1
3 4
1 5
5 6
9 2 3 1 4 4
1 0 0 0 0 1```

### 输出

```
5```

## 样例 #2

### 输入

```
2 1
1 2
1 2
0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
10 20
4 8
1 10
1 7
5 9
9 10
8 10
7 5
1 4
7 3
8 7
2 8
5 8
4 2
5 1
7 2
8 3
3 4
8 9
7 10
2 3
25 5 1 1 16 5 98 3 21 1
35 39 32 11 35 37 14 29 36 1```

### 输出

```
1380```

# 题解

## 作者：_anll_ (赞：9)

~~第一次自己订到 F，好兴奋！~~
## 题目大意
题目翻译过来挺简洁的，就不再赘述了。这里注意一个点：是顶点集的 $w$ 总和小于 $w_x$，而不是每个 $w \lt w_x$。

## 大体思路
一个简单的 dfs 套 $01$ 背包。

因为我们需要 $ \sum_{l\ \in\ S}\ w_l\ \lt\ w_x $，所以很容易想到每条边至多只能有一个可选方向。因此每个点的方案都是无后效性的，是可以预处理出来的。

问题转换成对于点 $x$ 如何找到最优的选点方式。我们令点 $x$ 的子结点 $l$ 的贡献（即最多可以通过 $l$ 传递给几个包含 $l$ 在内的点）为 $cu_l$，注意到一个点 $l$ 有两个属性，要在总 $w \lt w_x$ 的情况下满足总 $cu$ 尽可能大，联想到背包问题。把点 $l$ 看作物品， $w$ 看作重量，$cu$ 看作价值，于是一个简单的 $01$ 背包就构造好了。

剩下的步骤就很简单了。用 dfs 去遍历这个图，在过程中求出每个点的最优方案 $anu_i$，最后再用 $a_i \times anu_i$ 得到最终答案，再在 dfs 里加一些优化就可以过了。

## 代码演示
大体思路就是这样，如果有不清晰的地方还请结合代码和注释理解。
```cpp
#include<iostream>
#include<set>
#include<cstring>
#define int long long
using namespace std;
struct Edge{
    int l,nxt;
}edges[50005];
int n,m,tt=1,ans,head[5005],w[5005],a[5005],anu[5005];
set<int> so[5005];
void add_edge(int f,int l){
    tt+=1;
    edges[tt]={l,head[f]};
    head[f]=tt;
}
int dfs(int x){
    if(anu[x]) return anu[x];//已经求过该点方案
    int cu[5005],dp[5005];
    for(int i=1;i<w[x];i++) dp[i]=0;
    for(int i=head[x];i;i=edges[i].nxt){
        int l=edges[i].l;
        if(w[x]<=w[l]) continue;
        cu[l]=dfs(l);//价值:l一共可以传递给几个点
        so[x].insert(l);
    }
    for(int j:so[x])//只枚举可以有贡献的点
        for(int i=w[x]-1;i>=w[j];i--)
            dp[i]=max(dp[i],dp[i-w[j]]+cu[j]);

    anu[x]=dp[w[x]-1]+1;
    return anu[x];
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int f,l;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>f>>l;
        add_edge(f,l);
        add_edge(l,f);
    }
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        if(anu[i]) continue;
        dfs(i);
    }
    for(int i=1;i<=n;i++) ans+=anu[i]*a[i];
    cout<<ans;
    return 0;
}
```


---

## 作者：NATO (赞：2)

~~只要不读错题，相信大家一定可以一眼秒的。~~

### 解题思路：

首先，一定要注意是 $\sum_{y\in S}W_y\lt W_x$ 而不是 $y\in S,w_y<w_x$（~~否则你就会像我一样对第一个样例百思不得其解很久~~）。

先考虑建图。虽然题目中说是无向图，但我们发现当 $w_u<w_v$ 时只有 $u$ 可以 $v$ 产生贡献的，故只从 $v$ 连向 $u$，点权大小相反时同理，相等时不连边，容易发现，我们建出了一个所有边都是从大点权连向小点权的有向无环图。

根据数据范围，我们猜测时间复杂度应是 $O(n^2)$ 级别的，这种求最大执行次数看起来很像一个动态规划。

当一个棋子走到它原来所在点的儿子时显然可以像儿子点上原有的棋子一样继续走，那么从该点出发的一个棋子的操作次数即为 $1+\sum_{y\in S}dp_y$。

其中 $dp_y$ 为从 $y$ 点的出发的一个棋子的最大操作次数。

考虑如何最大化 $1+\sum_{y\in S}dp_y$。

假设我们已经求出了一个点 $x$ 的所有儿子的最大操作次数，现在求这个点的最大操作次数，我们选择 $x$ 一个儿子 $y$ 会得到 $dp_y$ 的操作次数，同时会占用 $w_y$ 的权值，每个儿子选且只能选 $1$ 次，$x$ 最大可以使用 $w_x-1$ 的权值。我们发现，这不就是一个典型的 0-1 背包吗？那么在搜索的过程中做 0-1 背包即可。

注意到我们 $w$ 与 $n$ 同阶，而有一条边就会做一次背包，故时间复杂度 $O(nm)$，可以通过本题，实现时注意不要重复做一个点的背包（检查当前点是否被访问即可）以保证复杂度正确。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
ll res;
ll head[5005],cnt;
ll a[5005],w[5005];
ll u[5005],v[5005];
ll in[5005];
ll cg[5005];
bool vis[5005];
ll mc[5005];
struct ed
{
	ll v,next;
}edge[10005];
void add(ll u,ll v)
{
	edge[++cnt].v=v;edge[cnt].next=head[u];head[u]=cnt;++in[v];
}
void dfs(ll id)
{
	if(vis[id])return;
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		dfs(v);
	}
	memset(mc,0,sizeof(mc));
	for(ll i=head[id];i;i=edge[i].next)
	{
		ll v=edge[i].v;
		for(ll j=w[id]-1;j>=w[v];--j)mc[j]=max(mc[j],mc[j-w[v]]+cg[v]);
	}
	vis[id]=1;
	cg[id]=1+mc[w[id]-1];
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=m;++i)cin>>u[i]>>v[i];
	for(ll i=1;i<=n;++i)cin>>w[i];
	for(ll i=1;i<=m;++i)
	if(w[u[i]]<w[v[i]])add(v[i],u[i]);
	else if(w[u[i]]!=w[v[i]])add(u[i],v[i]);
	for(ll i=1;i<=n;++i)cin>>a[i];
	for(ll i=1;i<=n;++i)
	if(!in[i])dfs(i);
	for(ll i=1;i<=n;++i)res+=cg[i]*a[i];
	cout<<res;
}
```


---

## 作者：Otue (赞：1)

很精妙的题。首先你要发现他给的每颗棋子其实是独立的，我们只需要计算出在每个节点放 $1$ 颗棋子的最大次数即可。将其乘上 $A_i$ 就是答案。

然后我们发现他这个转移也是有方向性的，即 $W_y<W_x$，总是大的走向小的。

再发现 $\sum W_y<W_x$，我们可以把 $W_y$ 看成体积，把选了 $y$ 之后的利润看成价值，把 $W_x-1$ 看成背包容量，这就是个背包问题。如何计算选了 $y$ 之后的利润？这不就是在 $y$ 节点上放一颗棋子的利润吗，用之前算出来的值进行转移。

如何保证之前一定算过 $y$？我们说过，他这个转移有方向性，只要将 $W$ 从小到大排序依次转移就能保证之前算过 $y$。

代码：

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 5e3 + 5;

int n, m, w[N], a[N], id[N], dp[N], cost[N], res;
vector<int> G[N];

bool cmp(int x, int y) {
	return w[x] < w[y];
}

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u); 
	}
	for (int i = 1; i <= n; i++) cin >> w[i];
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) id[i] = i;
	sort(id + 1, id + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		int u = id[i];
		memset(dp, 0, sizeof dp);
		for (auto v : G[u]) {
			if (w[v] < w[u]) {
				for (int j = w[u] - 1; j >= w[v]; j--) {
					dp[j] = max(dp[j], dp[j - w[v]] + cost[v]); // w_v为体积，cost_v为价值
				}
			}
		}
		for (int j = 0; j <= N - 5; j++) cost[u] = max(cost[u], dp[j] + 1);
	}
	for (int i = 1; i <= n; i++) res += a[i] * cost[i];
	cout << res << endl;
}
```

祝大家学习愉快！

---

## 作者：ran_qwq (赞：1)

根据 $W_i$ 重新建图，一条有向边 $(x,y)$ 有用当且仅当 $W_x>W_y$。

因为一定是从 $W_i$ 大的走到 $W_i$ 小的，所以新图是 DAG。

新图是 DAG，无后效性，再结合数据范围允许 $O(N^2)$ 做法，考虑 dp。

不同棋子显然是独立的，我们只考虑一枚棋子的情况。

设 $dp_u$ 为 $u$ 有一枚棋子的最大操作数。

则 $dp_u=\max(\sum\limits_{S\in v}dp_v[\sum\limits_{S\in v}W_v<W_u])$（$u$ 能直接到达 $v$）。

每个 $v$ 都有选和不选两种状态，这不就是个 01 背包吗？

设 $f_{u,i}$ 为 $u$ 有一颗棋子，选的 $W$ 和为 $i$ 的最大 $dp$ 之和，即 $f_{u,i}=\max\limits_v(f_{u,i-W_v}+dp_v)$。

然后 $dp_u=f_{u,W_u-1}+1$。答案就是 $\sum dp_u\times A_u$。

时间复杂度 $O(N^2)$。

```cpp
int n,m,id,X[N],Y[N],to[N<<1],ne[N<<1],head[N],w[N],a[N],in[N],vis[N];ll ans,f[N][N],dp[N];vi b;
void add(int x,int y) {to[++id]=y,ne[id]=head[x],head[x]=id;} 
void dfs(int u,int fa) {
	vis[u]=1,b.pb(u);
	for(int i=head[u];i;i=ne[i]) {
		int v=to[i];if(v==fa) continue;
		if(!vis[v]) dfs(v,u);
		for(int j=w[u]-1;j>=w[v];j--) f[u][j]=max(f[u][j],f[u][j-w[v]]+dp[v]);
	}
	dp[u]=f[u][w[u]-1]+1;
}
void QwQ() {
	n=rd(),m=rd();
	for(int i=1;i<=m;i++) X[i]=rd(),Y[i]=rd();
	for(int i=1;i<=n;i++) w[i]=rd();
	for(int i=1;i<=n;i++) a[i]=rd();
	for(int i=1;i<=m;i++) {
		if(w[X[i]]>w[Y[i]]) add(X[i],Y[i]);
		if(w[Y[i]]>w[X[i]]) add(Y[i],X[i]);
	}
	for(int i=1;i<=n;i++) if(a[i]) {
		dfs(i,0),ans+=1ll*dp[i]*a[i];
		for(int x:b) mst(f[x],0);b.clear();
	}
	wrll(ans,"");
}
```

---

## 作者：Shunpower (赞：1)

## Statement

给定一张 $n$ 个点 $m$ 条边的简单无向图，每个点 $i$ 上初始有 $a_i$ 个棋子，且有一个点权 $w_i$。

每次可以选择一个有棋子的点 $x$，移除它上面的一颗棋子，再选中一个与 $x$ 相邻的点构成的点集的子集 $S$，满足 $\sum\limits_{y\in S} w_y<w_x$，在 $S$ 中的每一个点上都放上一个棋子。特别地，可以选择空集。

可以证明在若干次操作之后图上不存在任何棋子。

求在图上没有棋子之前的最大操作次数。

$2\leq n\leq 5000,1\leq w_i\leq 5000,1\leq m\leq \min(\frac{n(n-1)}{2},5000),0\leq a_i\leq 10^9$。

## Solution

考虑每个点上棋子的移动方式都是一样的，且棋子之间互相独立。所以令 $f_i$ 表示当整个图上有且仅有 $i$ 处的一枚棋子时最多可以操作多少次能使图上没有任何棋子。显然最终答案即为 $\sum\limits_{i=1}^n f_ia_i$。

考虑如何 dp 出 $f_i$。假设我在 $i$ 处选中了点集 $S$（当然需要是合法点集，即 $S$ 中每个元素都与 $i$ 相邻，下文默认都选中合法点集），那么显然有 $f_i\gets 1+\sum\limits_{y\in S} f_y$，$1$ 是在这个点上进行的 $1$ 次操作，可以注意到在这样一步操作后 $S$ 中每个点上都会恰好有一个棋子。于是把这些点上的棋子再操作到不在图上的最大步数求和再加上那个 $1$ 就是把 $i$ 上的这一枚棋子操作到不在图上的最大步数。

考虑转移顺序可以发现，一枚位于 $x$ 的棋子可以选中并操作的点集 $S$ 满足 $\max\limits_{y\in S} w_y<w_x$，于是我们可以把所有点按照 $w$ 从小到大排序，从左到右进行转移，就能确保一个点选中的所有可能点集 $S$ 中 $S$ 的元素的 $f$ 值都已经被计算过了。

接下来考虑对于每个点如何选择一个 $\sum\limits_{y\in S} f_y$ 最大的点集 $S$。显然可以直接设 $g_i$ 表示权值和为 $i$ 的点集中 $f$ 之和的最大值，背包转移即可。由于合法的点集需要满足权值和 $<w_x$，所以背包只需要 $5000$ 的体积就够了。

枚举点，对于每一条连出去的边都要进行最多一次背包转移，于是复杂度就是 $\mathcal O(mV)$，其中 $V$ 表示权值值域也就是 $5000$，可以通过。

---

## 作者：Missa (赞：1)

如果你没有读错题，想必 20min 就够了。可惜这个人读错了两处题意浪费了 10min 导致没写完 G，这就是另一个故事了。

首先思考为什么这个过程会结束，发现有 $w_i$ 的限制。考虑 $\sum a_iw_i$，每次操作这个数值严格减小，因此操作数目的上限即为 $\sum a_iw_i$。

注意到一枚硬币只会从 $w$ 大的地方到达 $w$ 小的地方，因此按 $w$ 从大到小做背包，求出 $g_u$ 表示在 $u$ 处放置一个硬币最多能进行下去几次操作，转移时做 01 背包即可。复杂度 $O(nm)$，因为所有点一共有 $2m$ 个邻居。

```cpp
#include <bits/stdc++.h>

int main() {
  int n, m; scanf("%d %d", &n, &m);
  std::vector<std::vector<int>> e(n);
  for (int i = 0, u, v; i < m; i++) {
    scanf("%d %d", &u, &v), --u, --v;
    e[u].push_back(v), e[v].push_back(u);
  }
  int mx(1);
  std::vector<int> w(n), a(n), id(n);
  for (int &x : w) scanf("%d", &x), mx = std::max(mx, x);
  std::iota(id.begin(), id.end(), 0);
  std::sort(id.begin(), id.end(), [&](int x, int y) -> bool {
    return w[x] < w[y];
  });
  std::vector<int> g(n);
  for (int &u : id) {
    std::vector<int> f(w[u], 1);
    for (int v : e[u]) {
      int t = w[v];
      for (int i = w[u] - 1; i >= t; i--)
        f[i] = std::max(f[i], f[i - t] + g[v]);
    }
    g[u] = *std::max_element(f.begin(), f.end());
  }
  long long ans(0);
  for (int i = 0, x; i < n; i++) {
    scanf("%d", &x);
    ans += 1ll * x * g[i];
  }
  printf("%lld\n", ans);
}
```

---

## 作者：Linge_Zzzz (赞：0)

# 题意简述

不得不说读题是一个很重要的东西。

给你一个无向图，每个节点上有权值 $W_i$，上面还有 $A_i$ 个棋子。

你可以执行任意次下面这样的操作：

* 选择一个上面还有棋子的点 $u$，拿走其中的一个棋子。
* 在与点 $u$ 相连的点中选择一些点（可以不选），使得这些点的权值和**严格小于** $W_u$，然后往这些点上放上一个棋子。

可以证明，在有限次操作内，棋盘中的棋子必定会全部消失，问你操作最多能执行多少次？

# 解法

首先注意到，这个无向图可以转化成有向图，我们对每个边判断一下，如果 $u$ 能向 $v$ 传递棋子就连边，即 $W_u>W_v$。

进一步观察这个图，可以发现它是一个 DAG（有向无环图），证明如下：

> 假设这个有向图中存在一个环 $u \to x \to y \to \cdots \to u$，那么根据我们的建图，可以得出 $W_u>W_x>W_y>\cdots>W_u$。然而 $W_u$ 是不可能比自己大的，所以该假设不成立，进而说明这是一个有向无环图。

有向无环图是一种优美的图，因为我们可以对其进行 DP。

设 $val_i$ 为在 $i$ 点放 $1$ 个棋子后，这个点可以往后的操作数，答案就是 $\sum_{i=1}^n val_i\times A_i$，现在我们的任务就转变为了求出 $val_i$。

对于点 $i$，如何确定一种选择将要传递的点的方案是关键。发现它可以转化为 $0/1$ 背包模型。这个点的背包体积是 $W_i$，物品就是他相邻的点，物品 $j$ 的体积是 $W_j$，价值是 $val_j$，使用 $0/1$ 背包即可求出 $val_i$。

我们求 $val_i$ 时需要已经计算出来的 $val_j$，这就是我们使用拓扑序 DP 的原因，拓扑序可以保证在求 $val_i$ 的时候，所有的 $val_j$ 已经被求出。

值得注意的是，就算任何物品都不选，把自己身上的一个棋子消掉也有一种操作，所以对于求出的 DP 值要加 $1$。

剩下的就是代码细节了，可以参考我的代码。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e3+10,M=5010;
int n,m;
struct edge{
	int v,w,nxt;
}e[N*2];
int head[N],cnt=1;
void add(int u,int v,int w){
	e[cnt].v=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt++;
}
int w[N],a[N],d[N];
int u[N],v[N];

vector<int> f[N],g[N];

int dp[N],val[N];
void solve(int u){ // 求解点 u 的 val 值
	memset(dp,0,sizeof(dp));
	for(int i=0;i<f[u].size();i++){
		for(int j=w[u];j>w[f[u][i]];j--){
			dp[j]=max(dp[j],dp[j-w[f[u][i]]]+val[f[u][i]]);
		}
	}
	val[u]=dp[w[u]]+1;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>u[i]>>v[i];
	for(int i=1;i<=n;i++)cin>>w[i];
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++){
		if(w[v[i]]>w[u[i]])swap(u[i],v[i]);
		if(w[u[i]]==w[v[i]])continue;
		f[u[i]].push_back(v[i]);
		g[v[i]].push_back(u[i]);
		d[u[i]]++;
	}
	queue<int> q;
	for(int i=1;i<=n;i++){
		if(d[i]==0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int p=q.front();q.pop();
		solve(p);
		for(int x:g[p]){
			d[x]--;
			if(d[x]==0)q.push(x);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=val[i]*a[i];
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
给定一个共 $N$ 个点 $M$ 条边的无向图，对于点 $i$ 有值 $W_i$ 和 $A_i$ 个标记。

令 $u$ 为某一有标记的点，现可对其进行操作。首先去除点 $u$ 的一点标记，然后在与点 $u$ 直接相连的点中选择一些点构成一集合 $S$，保证 $\sum_{v\in S}W_v<W_u$，然后所有集合中的点增加一个标记。

求操作的最大次数。
# 思路
首先设有点 $u$ 与 $v$，有以下三种情况：
- $W_u>W_v$，此时 $u$ 可选择点 $v$，但 $v$ 不可选择点 $u$。
- $W_u<W_v$，此时 $v$ 可选择点 $u$，但 $u$ 不可选择点 $v$。
- $W_u=W_v$，此时 $u,v$ 相互不可选择。

于是可以知道，选择只能是单向、从大往小的，所以标记的传递也就不存在环了。

对于点 $u$ 我们设有一个权值 $con_u$，意为从 $u$ 为起点的一个标记最多可以有多少次操作。然后分析取点的过程，会发现其转变成为了一个 01 背包的问题，容量为题意中提到的 $W_u$，而可选择点 $v$ 的价值则为 $con_v$，最后跑一遍 dp 即可算出 $con_u$。

枚举时每个点跑一遍深搜，最后答案为 $\sum_{i=1}^N A_i\times con_i$。
# 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5;
vector<int> r[N];
int n,m,w[N];
long long ans,con[N];
inline long long dfs(int u){
	if(con[u])
		return con[u];
	long long f[N];
	for(int i=0;i<w[u];i++)
		f[i]=0;
	for(auto v:r[u])
		if(w[v]<w[u]){
			long long V=dfs(v);
			for(int i=w[u]-1;i>=w[v];i--)
				f[i]=max(f[i],f[i-w[v]]+V);
	}
	return con[u]=f[w[u]-1]+1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		r[u].emplace_back(v);
		r[v].emplace_back(u);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for(int i=1,a;i<=n;i++){
		scanf("%d",&a);
		ans+=1ll*dfs(i)*a;
	}
	printf("%lld",ans);
	return 0;
} 
```

---

## 作者：JuRuoOIer (赞：0)

# 题解 ABC341F Breakdown

### 背景

赛时调了一整场 E 导致人家都 AK 了我只有 ABCD。~~这样都能上分可见我有多菜~~。赛后又因为读错题（题意部分的注意）导致不会做。

### 题意

已提交翻译。

一张 $n$ 个点 $m$ 条边的无向图，每个点有权值 $w_i$，并且在上面放了 $a_i$ 个棋子。只要图上还有棋子，就进行一次如下操作：
- 选择一个有棋子的点 $x$。
- 选择一个点集 $S$（可以为空），要求其中所有结点与 $x$ 有边相连，且满足 $\sum_{y \in S}w_y<w_x$（注意：是点集中所有结点的 $w$ 之和小于 $w_x$，不是每个节点的 $w$ 小于 $w_x$）。
- 从 $x$ 上移除一个棋子，并往 $S$ 中的每个点上放一个棋子。

求最大的操作次数。

数据范围：$n,m,w_i\le 5000$，$a_i \le 10^9$，没有自环重边。

### 做法

省流：DFS 套 01 背包。

首先一个很显然的结论：棋子一定是从 $w$ 大的点往 $w$ 小的点走（要不怎么小于 $w_x$）。

注意到 $n$ 的数据范围满脸写着 $O(n^2)$（级别），且 $w$ 范围极小，又要求选择的点集中点的 $w$ 之和不能超过 $w_x$，容易想到把点看做以 $w$ 为体积，以 $ans$（它操作一次的总贡献）为价值的物品，这样 $w_x$ 就是背包容量，然后就可以对每个点跑 01 背包了。

由于每个点只会更新一次 dp 数组，而 $w$ 与 $n$ 同阶，所以复杂度大致为 $O(n^2)$。

### 代码

```cpp
#define ll long long
using namespace std;
ll n,m,u,v,w[5010],y[5010],ans[5010],tot;
//u,v 读边用；w,y 分别对应题目中 w,a；ans 为每个点操作一次的贡献。
vector<ll> a[5010];//存图
ll dfs(ll now){
	if(ans[now])return ans[now];//记忆化，算过答案就返回
	ll c,dp[5010];
	memset(dp,0,sizeof(dp));
	for(int i=0;i<a[now].size();i++){//外层枚举每一个点
		if(w[a[now][i]]<w[now]){//判断是否可能选择
			c=dfs(a[now][i]);//求出枚举的点操作一次的贡献
			for(int j=w[now]-1;j>=w[a[now][i]];j--){//滚动数组 01 背包板子，注意开成一维时的枚举顺序
				dp[j]=max(dp[j],dp[j-w[a[now][i]]]+c);
			}
		}
	}
	ans[now]=dp[w[now]-1]+1;//记录贡献并返回，注意空集也会产生贡献因此加 1
	return ans[now];
}
int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	for(int i=1;i<=n;i++){
		cin>>y[i];
	}
    //以上是读入
	for(int i=1;i<=n;i++){
		if(!ans[i])dfs(i);//计算所有点的答案
	}
	for(int i=1;i<=n;i++){
		tot+=ans[i]*y[i];//统计时注意乘上操作的次数
	}
	cout<<tot;
	return 0;
}
```

---

## 作者：MrPython (赞：0)

好一个 DP 套 DP！~~这里必须要锐评一下题面太抽象读题都花我 20 min~~

从一个点 $p$ 删除一个棋子后，你可以选择与他直接相连的一些点放上棋子，不过要求**被选择点权值的和**小于 $p$ 的权值 $w_p$。显然，如果想要选择 $p$ 的某个相邻点 $q$，一定有 $w_p>w_q$ （单个点的权值都超了肯定没法选）。凭借权值的关系，就能发现这张图实际是一张 **DAG**。

DAG 说明了无后效性，可以在图上跑 DP，单独计算某个点的最大贡献。又因为棋子之间不会互相干扰，因此只计算某点只有一个棋子时的最大贡献，最后统计时乘以当前点棋子数量即可。

如何统计某个点上有一个棋子时产生的贡献？我们发现：问题“限制选择的点的权值和不超过当前点，求总贡献最大”非常像一个 0-1 背包问题。计这个函数为 $f$。假如我们正在求解 $f(p)$，目前在考虑是否选择 $q$。如果选择了 $q$，则 $q$ 上会出现一枚棋子，产生 $f(q)$ 的贡献。因此，$w_q$ 看作物品体积，$f(q)$ 看作物品价值，可以跑背包。移除当前点本身也可产生 $1$ 的贡献，跑背包 dp 的数组记得初始化为 $1$。

使用递归的形式求贡献 $f$，搭配记忆化食用效果更佳。递归时处理好 $w_p\le w_q$ 的情况，可以不用显式建 DAG。

```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
using usi=unsigned short int;
uli f(size_t p,vector<usi> const& w,vector<ui> const& a,vector<uli>& d,vector<vector<size_t>>& mp){
    if (~d[p]) return d[p];
    d[p]=0;
    vector<uli> dp(w[p],1);
    for (size_t i:mp[p])
        for (usi j=w[p]-1;j>=w[i];--j) dp[j]=max(dp[j],dp[j-w[i]]+f(i,w,a,d,mp));
    return d[p]=dp.back();
}
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t n,m;cin>>n>>m;
    vector<vector<size_t>> mp(n);
    while (m--){
        size_t x,y;cin>>x>>y;--x,--y;
        mp[x].push_back(y),mp[y].push_back(x);
    }
    
    vector<usi> w(n);vector<ui> a(n);
    for (usi& i:w) cin>>i;
    for (ui& i:a) cin>>i;
    vector<uli> d(n,~0);
    uli ans=0;
    for (size_t i=0;i<n;++i) ans+=a[i]*f(i,w,a,d,mp);
    cout<<ans;
    return 0;
}
```

---

## 作者：newwzl (赞：0)

## 题意
给你一个无向无权图 $G=(V(G),E(G))$，每个点有两种权值，分别为 $W$ 和 $A$。每一次操作，可以选择一个点 $i$ 并先使 $A_i$ 减一，再选择几个与 $i$ 相邻的点，设为点集 $S$，满足 $\sum_{j\in{S}}^{W_j} < W_i$，使对于 $S$ 内的所有点 $j$，$A_j$ 加一。当 $A$ 数组全部是 $0$，时停止操作。问最多操作次数。
## 思路
假设有一个函数 $h(V,E,M,N)$ 表示对于图 $(V,E)$ ，当该图的 $W,A$ 数组分别为 $M,N$ 时的最多操作次数。

显然有两个结论形如下式：

`h(V,E,M,{a,0,0,…})=h(V,E,M,{1,0,0,…)*a`

`h(V,E,M,{a,0,b,…})=h(V,E,M,{a,0,0,…})+h(V,E,M,{0,0,b,…})`

于是我们就可以用动态规划求出每个顶点 $i$ 对答案的贡献 $f_i$。

不过我们现在不知道图上的转移顺序，但是为我们发现只有 $W$ 低的能向 $W$ 高的点转移，于是原图就合理地变成了有向无环图。

转移顺序有了，下一步就是转移方程。

当转移到 $f_x$ 的时候，我们可以将该过程理解为01背包，$W_x-1$ 是背包的容量，$W_y\ (y\in S)$ 是物品的大小，$f_y\ (y\in S)$ 是物品的价值。记住答案要比背包求出来的值多一。

答案就是 $\sum_{i=1}^n A_i \times f_i$。

时间：$O(NW)$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5005;
int n,m,dg[N],a[N],w[N];
int head[N],tot;
struct node{
	int next,to;
}e[N<<2];
void add(int from,int to){
	e[++tot].next=head[from];head[from]=tot;e[tot].to=to;
}
int f[N],g[N];
void bfs(){
	queue<int>q;for(int i=1;i<=n;i++)if(dg[i]==0)q.push(i);
	while(q.size()){
		int x=q.front();q.pop();
		memset(g,0,sizeof g);
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;if(w[y]>=w[x])continue;
			for(int j=w[x]-1;j>=w[y];j--)g[j]=max(g[j],g[j-w[y]]+f[y]);
		}
		f[x]=g[w[x]-1];
		f[x]++;
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;if(w[y]<=w[x])continue;
			dg[y]--;if(dg[y]==0)q.push(y);
		}
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;scanf("%lld%lld",&u,&v);add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++)scanf("%lld",&w[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int x=1;x<=n;x++){
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;if(w[y]<w[x])dg[x]++;
		}
	}
	bfs();
	int ans=0;
	for(int i=1;i<=n;i++)ans+=f[i]*a[i];
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Soul_Wanderer (赞：0)

# 题解

## [[ABC341F] Breakdown](https://www.luogu.com.cn/problem/AT_abc341_f)

## 题意

给你一个 $n$ 个点 $m$ 条边的无向图，每个点有两个值，$W_i$ 和 $A_i$。

重复下面的操作：

找一个点 $x$，如果 $A_x$ 大于零，将 $A_x$ 减一。

选择一些与 $x$ 点相邻的点构成点集 $S$（可以为空），满足 $\sum_{y \in S} W_y \lt W_x$，并将集合 $S$ 中的每个点的 $A_i$ 加一。

输出此操作的最大执行次数。

# 思路

~~场上太菜没切出来（悲。~~

有些类似于背包 DP，定义状态 $f_{x,i,j}$ 表示在点 $x$ 已经枚举了 $i$ 个点，空间限制为 $j$ 的最大执行数。（~~请感性理解~~）根据背包 DP 可知，可以将一维优化掉，为 $f_{x,j}$。

转移顺序根据 $W_i$ 从小往大连边，拓扑排序。

转移方程：$f_{x,j}=\max(f_{x,j-w_y}+f_{y,w_y-1})$。

$y$ 为与 $x$ 相邻的点且满足 $W_y \lt W_x$。

显然，答案就是 $\sum A_i \times f_{i,w_i-1}$。

具体细节见代码。

~~温馨提示：本人太蒻，题解思路过于抽象，请强行理解感性理解加极致的思考。~~

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e3+37;
int n,m;
int w[N],a[N]; 
struct n1{
	int to,next;
}e[N*N<<1];
int head[N],tot;
void add(int from,int to){
	e[++tot].to=to;
	e[tot].next=head[from];
	head[from]=tot;
}
int f[N][N];
int in[N];
queue<int >que;
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=head[i];j;j=e[j].next){
			int y=e[j].to;
			if(w[y]>w[i]) in[y]++;
		}
	}
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		if(in[i]==0){
			que.push(i);
		}
	}
	while(que.size()){
		int x=que.front();
		que.pop();
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;
			if(w[y]<w[x]){
				for(int j=w[x]-1;j>=w[y];j--){
					f[x][j]=max(f[x][j],f[x][j-w[y]]+f[y][w[y]-1]);
          	   //非常像01背包DP，只是转移顺序不一样
				}
			}
		}
		f[x][w[x]-1]++;//自己本次操作一次也算
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;
			if(w[y]>w[x]){
				in[y]--;
				if(in[y]==0){
					que.push(y);
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=a[i]*f[i][w[i]-1];
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：YangRuibin (赞：0)

# 思路构建

观察题目，注意到两点：

1. 每个点“删掉”后，总是往 $w_i$ 小的地方转移。
2. 因为要求最大步数，所以转移到的儿子节点答案之和要尽可能大。

所以想到动态规划。其中关注到的值有两种：

1. 能够转移到的节点的代价。
2. 这些节点的贡献。

这就是一个背包。定义状态 $f_{i,j}$ 表示的节点 $i$ 在“空间”为 $j$ 时的最优答案。方程就是典型的背包的方程，此处不必再写。

枚举结点的顺序是按点权 $w_i$ 从小到大排的。

# 代码
 ```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5005,M=N*N;
int n,m,head[N],tot,f[N][N],mi[N],w[N],a[N],id[N];
struct node{
	int to,next;
}edge[M];
void add(int from,int to)
{
	++tot;
	edge[tot].to=to;
	edge[tot].next=head[from];
	head[from]=tot;
}
bool cmp(const int &x,const int &y)
{
	return w[x]<w[y];
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1,x,y;i<=m;i++)
		scanf("%lld%lld",&x,&y),add(x,y),add(y,x);
	for(int i=1;i<=n;i++)scanf("%lld",w+i);
	for(int i=1;i<=n;i++)scanf("%lld",a+i),id[i]=i;
	sort(id+1,id+n+1,cmp);//按点权排序
	memset(f,-1,sizeof(f));
	for(int p=1,x;p<=n;p++)//依次背包
	{
		x=id[p];f[x][0]=1;
		for(int i=head[x];i;i=edge[i].next)
		{
			int to=edge[i].to;
			if(w[to]>w[x])continue;
			for(int j=w[x]-1;j;j--)
				if(w[to]<=j&&f[x][j-w[to]]>=0)f[x][j]=max(f[x][j],f[x][j-w[to]]+f[to][mi[to]]);
		}
		for(int i=0;i<=w[x];i++)
			if(f[x][i]>f[x][mi[x]])mi[x]=i;//mi[x]为结点x在背包中最优答案所在下标
	}
	int ans=0;
	for(int i=1;i<=n;i++)ans+=f[i][mi[i]]*a[i];
	printf("%lld",ans);
	return 0;
}
 ```


---

## 作者：rainygame (赞：0)

背包板子题，赛时看错题瞪了 40 分钟的样例……

设 $f_i$ 为在 $i$ 号结点上放一个棋子的最大移动次数，那么答案就是 $\sum\limits_{i=1}^na_i\times f_i$，考虑求出 $f_i$。

考虑给图定向，让权值小的往权值大的连，两端权值相同就不连。

这样就可以上拓扑了，对于 $u$，我们需要选择一些入结点 $v$ 来更新它，并且 $W_v$ 和不能超过 $W_u$。

发现这是一个经典的 01 背包问题，秒了。

时间复杂度 $O(nW)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 5001

int n, m;
int w[MAXN], a[MAXN];
int us[MAXN], vs[MAXN], in[MAXN];
vector<int> e[MAXN];

long long ans;
long long tms[MAXN];
long long f[MAXN][MAXN];

void toposort(){
    queue<int, list<int>> que;
    for (int i(1); i<=n; ++i){
        if (!in[i]) que.push(i);
    }

    while (!que.empty()){
        int u(que.front());
        que.pop();
        tms[u] = f[u][w[u]-1]+1;

        for (auto i: e[u]){
            for (int j(w[i]-1); j>=w[u]; --j) f[i][j] = max(f[i][j], f[i][j-w[u]]+tms[u]);
            if (!(--in[i])) que.push(i);
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i(1); i<=m; ++i) cin >> us[i] >> vs[i];
    for (int i(1); i<=n; ++i) cin >> w[i];
    for (int i(1); i<=n; ++i) cin >> a[i];
    for (int i(1); i<=m; ++i){
        if (w[us[i]] > w[vs[i]]) swap(us[i], vs[i]);
        if (w[us[i]] ^ w[vs[i]]){
            e[us[i]].push_back(vs[i]);
            ++in[vs[i]];
        }
    }
    toposort();
    for (int i(1); i<=n; ++i) ans += a[i]*tms[i];
    cout << ans;

    return 0;
}

```


---

## 作者：incra (赞：0)

### Solution
看完题目，感觉很毒瘤。

令 $c_i$ 为第 $i$ 个点增加一个棋子最多能增加的操作次数，答案显然就是 $\displaystyle\sum_{i=1}^na_ic_i$。

如何计算 $c_i$？我们发现，$c_i$ 的值只和与 $i$ 相邻的点 $j$ 满足 $w_j<w_i$ 有关，所以我们要先计算**没有** $v$ 满足 $w_v<w_u$ 的点 $u$（因为 $c_u$ 与任何东西都无关），然后计算和 $u$ 相邻的点 $p$ 满足 $w_u<w_p$ 的 $c_p$，然后计算 $p$ 相邻的点 $l$，满足 $w_p<w_l$ 的 $c_l$，以此类推。然后我们发现，执行上述过程中，对于一条边 $(i,j)$，只会从 $w_i$ 小的点走到大的点，这个图就变成了有向图，于是就可以用拓扑排序求 $c_v$。

设我们已经计算出这个有向图（按照 $w_i$ 小的点向大的点连边）某一个点 $u$ 的所有前驱节点 $v$ 的值 $c_v$，那么可以看成以 $w_v$ 为重量，$c_v$ 为价值的 01 背包问题，$c_v$ 就是重量不超过 $w_u-1$ 的物品所能得到的最大价值。

时间复杂度：拓扑排序 $O(n+m)$，01 背包会执行 $m$ 次（不是 $n^2$ 次，因为每一次 DP 会涉及到一条边的两个节点），总的时间复杂度为 $O(nm+n^2)$。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 5010;
int n,m;
vector <int> g[N];
int w[N];
LL a[N];
int in_deg[N];
LL f[N][N];
LL c[N];
int main () {
	cin >> n >> m;
	while (m--) {
		int a,b;
		cin >> a >> b;
		g[a].pb (b),g[b].pb (a);
	}
	for (int i = 1;i <= n;i++) cin >> w[i];
	for (int i = 1;i <= n;i++) {
		sort (g[i].begin (),g[i].end (),[](int x,int y) {
			return w[x] < w[y];
		});
	}
	for (int i = 1;i <= n;i++) cin >> a[i];
	for (int i = 1;i <= n;i++) {
		for (int j : g[i]) {
			if (w[i] < w[j]) in_deg[j]++;
		}
	}
	queue <int> q;
	for (int i = 1;i <= n;i++) {
		if (!in_deg[i]) q.push (i),c[i] = 1;
	}
	while (q.size ()) {
		int u = q.front ();
		q.pop ();
		for (int v : g[u]) {
			if (w[u] < w[v]) {
				for (int i = w[v];i >= w[u];i--) tomax (f[v][i],f[v][i - w[u]] + c[u]);
				if (!--in_deg[v]) {
					c[v] = f[v][w[v] - 1] + 1;
					q.push (v);
				}
			}
		}
	}
//	for (int i = 1;i <= n;i++) cout << c[i] << ' ';
//	cout << endl;
	LL ans = 0;
	for (int i = 1;i <= n;i++) ans += a[i] * c[i];
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Wei_Han (赞：0)

## 题意大意
给定一个无向图，每个点有权值 $w_i$，每个点上放了 $a_i$ 个棋子。记一次操作为，对于一个点 $x$，找到与他相邻的点的集合 $S$，且 $\sum_{y\in S}w_y<w_x$，也就是说找到与 $x$ 相邻的几个点，且 $w$ 的和不到 $w_x$。让 $a_x-1$，点集中的每个点 $a_i+1$。求出最大的操作次数。 
## Solution
会发现，每次操作都是独立的，我们就可以处理出每个点进行一次操作的总操作次数，再进行统一累加求和。

考虑如何处理一个点的次数，会发现，对于原图，可能会有许多不必要的边，从 $w$ 较小的点连到 $w$ 较大的点（无向边看做两条边），我们可以重新建图，只保留需要的边，也就是由较大点连到较小点。这样就会形成一个有向无环图了，在这个图上，一个点操作一次的操作次数也就是他的子节点的操作数总和 $+1$。

由于还有 $w$ 的限制，也就是只能选其中几个子节点，将子节点的操作数看做价值，将 $w$ 看做重量，对于每个点做背包就可以了。
## Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ;  i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i  )
#pragma GCC optimize(2)
using namespace std;
typedef long long ll;
typedef double db;
const int N=5e3+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

ll n,m,a[N],w[N];
ll head[N],tot;
int cnt[N],maxx=-1;
struct Graph{ll ver,nxt;}g[N];
inline void add(ll x,ll y){g[++tot].ver=y,g[tot].nxt=head[x];head[x]=tot;}
int dp[N],c[N],w1[N];
ll u[N],v[N],vis[N];
inline void dfs(ll x){
	int ans=0;
	cnt[x]=1;
	for(int i=head[x];i;i=g[i].nxt){
		int y=g[i].ver;
		if(!vis[y]) dfs(y);
	}
	for(int i=head[x];i;i=g[i].nxt){
		int y=g[i].ver;
		c[++ans]=cnt[y];w1[ans]=w[y];
	}
	fo(1,i,w[x]) dp[i]=0;
	fo(1,i,ans){
		Fo(w[x]-1,j,w1[i]){
			dp[j]=max(dp[j],dp[j-w1[i]]+c[i]);
		}
	}
	cnt[x]+=dp[w[x]-1];vis[x]=1;
}
int main(){
	read(n),read(m);
	fo(1,i,m) read(u[i]),read(v[i]);
	fo(1,i,n) read(w[i]),maxx=max(0ll+maxx,0ll+w[i]);
	fo(1,i,m){
		if(w[v[i]]>w[u[i]]) add(v[i],u[i]);
		else if(w[v[i]]<w[u[i]]) add(u[i],v[i]);
	}
	fo(1,i,n) if(!cnt[i]) dfs(i);
	long long sum=0;
	fo(1,i,n) read(a[i]),sum+=1ll*cnt[i]*a[i];
	wr(sum);
	return 0; 
}
``````

---

## 作者：hhce2012 (赞：0)

# 1. 前言

省流：经典的 DAG 上背包，但是将状态当作物品选取。

# 2. 关键点

关键点是“如果给这张图的每一条边按照如下规则定向：‘如果这条边 $(u, v)$ 满足 $W_u \ne W_v$，则 $W$ 大的连向 $W$ 小的，否则直接删除’，那么得到的图一定是一个 DAG”。

证明：

如果有环，那么意味着环上 $a1 > a2 > a3 > \dots > a1$，很显然矛盾，因此不会有环。

# 3. 具体思路

既然是个 DAG，考虑 dp。

但是显然是从 $W$ 小的转移到 $W$ 大的。

即使这样，我们仍然可以建反图然后 dp。

我们不确定到底选什么 $S$ 可以最优，所以得将这个东西用某种方式加进状态中。看一看题目，$\sum \limits_{y \in S} W_y < W_x$，这个式子不就是一个背包的模型吗？

所以定义状态 $dp_{i, j}$ 为当节点 $i$ 的 $W_i$ 为 $j + 1$ 并且刚好有一个棋子，操作的最大次数。

转移：

对于每一个可以通过一条边到达 $i$（反图上）的 $k$，$dp_{i, j} = \max(dp_{i, j}, dp_{i, j - W_k} + \max \limits_{0 \le a < W_k} dp_{k, a})$。

这个式子看起来会 T 飞，事实上在 $dp_{i, x}$ 求解完成后可以立马处理出 $\max \limits_{0 \le x < W_k} dp_{i, x}$ 的值。

即使这样，这个式子看起来还是会 T 飞。

可是，让我们具体分析一下：

状态 $O(NV)$，转移每一条边 $O(V)$，总共 $O(M)$ 条边，所以总时间复杂度 $O((N + M)V)$，其中 $V = \max \limits_{1 \le i \le N} W_i$。

# 4. 上代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

struct node {
  int u, v;
}arr[5050];

int n, m, dp[5050][5050], a[5050], p[5050], ind[5050], vis[5050], tdp[5050], ans;
vector<int> to[5050];
queue<int> q;

void topsort() {
  for(int i = 1; i <= n; i++) {
    if(!ind[i]) {
      q.push(i);
    }
  }
  for(; q.size(); q.pop()) {
    int i = q.front();
    for(int j = 0; j < a[i]; j++) {
      tdp[i] = max(tdp[i], dp[i][j]);
    }
    tdp[i]++;
    vis[i] = 1;
    for(auto j : to[i]) {
      for(int k = a[j] - 1; k >= a[i]; k--) {
        dp[j][k] = max(dp[j][k], dp[j][k - a[i]] + tdp[i]);
      }
      ind[j]--;
      if(!ind[j]) {
        q.push(j);
      }
    }
    ans += p[i] * tdp[i];
    //cout << i << ' ' << tdp[i] << '\n';
    for(int j = 0; j < a[i]; j++) {
      //cout << dp[i][j] << ' ';
    }
    //cout << '\n';
  }
}

signed main() {
  cin >> n >> m;
  for(int i = 1; i <= m; i++) {
    cin >> arr[i].u >> arr[i].v;
  }
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for(int i = 1; i <= n; i++) {
    cin >> p[i];
  }
  for(int i = 1; i <= m; i++) {
    if(a[arr[i].u] < a[arr[i].v]) {
      to[arr[i].u].push_back(arr[i].v);
      ind[arr[i].v]++;
    }
    if(a[arr[i].u] > a[arr[i].v]) {
      to[arr[i].v].push_back(arr[i].u);
      ind[arr[i].u]++;
    }
  }
  for(int i = 1; i <= n; i++) {
    //cout << ind[i] << ' ';
  }
  //cout << '\n';
  topsort();
  cout << ans << '\n';
  return 0;
}
```

[赛时 AC](https://atcoder.jp/contests/abc341/submissions/50387467)

[赛后 AC](https://atcoder.jp/contests/abc341/submissions/50403950)

---

