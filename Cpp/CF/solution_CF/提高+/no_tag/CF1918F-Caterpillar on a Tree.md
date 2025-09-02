# Caterpillar on a Tree

## 题目描述

The caterpillar decided to visit every node of the tree. Initially, it is sitting at the root.

The tree is represented as a rooted tree with the root at the node $ 1 $ . Each crawl to a neighboring node takes $ 1 $ minute for the caterpillar.

And there is a trampoline under the tree. If the caterpillar detaches from the tree and falls onto the trampoline, it will end up at the root of the tree in $ 0 $ seconds. But the trampoline is old and can withstand no more than $ k $ caterpillar's falls.

What is the minimum time the caterpillar can take to visit all the nodes of the tree?

More formally, we need to find the minimum time required to visit all the nodes of the tree, if the caterpillar starts at the root (node $ 1 $ ) and moves using two methods.

1. Crawl along an edge to one of the neighboring nodes: takes $ 1 $ minute.
2. Teleport to the root: takes no time, no new nodes become visited.

The second method (teleportation) can be used at most $ k $ times. The caterpillar can finish the journey at any node.

## 说明/提示

The figure shows one of the ways to traverse the tree from the first test in 9 minutes.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1918F/77179a13af1b28ec2237ee92c15cdb8a4a8e0b93.png)

## 样例 #1

### 输入

```
8 1
1 1 2 2 4 3 3```

### 输出

```
9```

## 样例 #2

### 输入

```
4 0
4 4 1```

### 输出

```
4```

# 题解

## 作者：FeelGood (赞：22)

首先发现如果要直接计算答案非常困难，所以我们考虑先计算出暴力遍历整棵树需要的时间，再减去使用传送可以节约的时间。

然后我们考虑计算传送可以节约的时间。发现传送的操作只会发生再叶子节点上，因为如果当前结点的儿子还没有遍历完，我们就返回了根节点，那么我们还要走回来继续遍历，所以答案不会更优。同时，遍历结束时我们不需要返回根节点，这相当于我们可以使用 $k + 1$ 次传送操作。

因为是传送回根节点，所以我们考虑把根节点下的所有子树分离开来单独考虑。发现对于一颗子树，如果它使用了传送操作，那么它最深的叶子结点一定是使用了传送操作。于是我们在存边时，先对每一个点拥有的边，按照边连接的子树中结点的最大深度从大到小排序，保证深度大的叶子结点 dfs 序在深度小的叶子结点之前。

记 $dep_i$ 为 $i$ 号结点的深度，$lca_{i, j}$ 为 $i$ 号结点与 $j$ 号结点的最近公共祖先，$dst_i$ 为第 $i$ 个结点使用传送操作能节约的时间。

我们把子树上所有的叶子结点按照 dfs 序从小到大截取出来，这是为了后面计算每个结点能节约时间时不多计算节约的时间。

推理一下，我们可以发现对于 $1$ 号结点 $dst_i = dep_i$，对于 $i$ 号结点 $(i \ge 2)$，发现它如果使用传送技能，它能节省的时间为 $dst_i = \max \{ 0, dep_i - dep_{lca_{i - 1, i} } \times 2\}$。

这样我们可以把整棵树所有叶子结点使用传送技能节约的时间计算出来。然后我们把所有子树叶子结点的 $dst$ 一起从大到小排序，用暴力遍历的时间减 $\sum_{i = 1}^{k + 1} dst_i$，就可以得到答案了。

时间复杂度 $O(n \log n)$，可以通过。

代码如下

```cpp
#include <bits/stdc++.h>

#define ll long long
#define lll __int128

using namespace std;

namespace IO
{
	void read() {}
	template <typename T1, typename ...T2>
	void read(T1 &n, T2 &...m)
	{
		T1 op = 1;
		char c;
		while (isdigit(c = getchar()) == false)
			if (c == '-') op = -1;
		n = c ^ 48;
		while (isdigit(c = getchar()))
			n = (n << 1) + (n << 3) + (c ^ 48);
		n *= op;
		return read(m...);
	}
}

using IO::read;

namespace Solve
{
	const int MaxN = 2e5;
	
	vector<int> G[MaxN + 10];
	
	void addedge(int u, int v) { G[u].emplace_back(v); }
	
	int dep[MaxN + 10], dfn[MaxN + 10], fa[MaxN + 10], st[20][MaxN + 10], v[MaxN + 10], mxdep[MaxN + 10], tot, tim;
	
	int get(int u, int v) {return dep[u] < dep[v] ? u : v;}
	
	void dfs1(int f, int u)
	{
		fa[u] = f;
		dep[u] = dep[f] + 1;
		for (int &v : G[u])
		{
			dfs1(u, v);
			mxdep[u] = max(mxdep[u], mxdep[v]);
		}
		mxdep[u] = max(mxdep[u], dep[u]);
	}
	
	void dfs2(int u)
	{
		sort(G[u].begin(), G[u].end(), [](int a, int b) {return mxdep[a] > mxdep[b];});
		dfn[u] = ++tim;
		st[0][dfn[u]] = u;
		for (int &v : G[u])
			dfs2(v);
	}
	
	void init(int n, int rt)
	{
		dfs1(0, rt);
		dfs2(rt);
		int len = __lg(n);
		for (int i = 1; i <= len; ++i)
			for (int j = 1; j + (1 << i) - 1 <= n; ++j)
				st[i][j] = get(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
	}
	
	int getlca(int u, int v)
	{
		if (u == v) return u;
		u = dfn[u], v = dfn[v];
		if (u > v) swap(u, v);
		int len = __lg(v - u++);
		return fa[get(st[len][u], st[len][v - (1 << len) + 1])];
	}
	
	void dfs3(int f, int u)
	{
		if (G[u].empty())
			v[++tot] = u;
		for (int &v : G[u])
			dfs3(u, v);
	}
	
	int dst[MaxN + 10], cntd;
	
	void Sol()
	{
		int n, k;
		read(n, k);
		for (int i = 2; i <= n; ++i)
		{
			int f;
			read(f);
			addedge(f, i);
		}
		dep[0] = -1;
		init(n, 1);
		for (int &u : G[1])
		{
			tot = 0;
			dfs3(1, u);
			sort(v + 1, v + tot + 1, [](int a, int b) {return dfn[a] < dfn[b];});
			dst[++cntd] = dep[v[1]];
			for (int i = 2; i <= tot; ++i)
			{
				int lca = getlca(v[i - 1], v[i]);
				dst[++cntd] = max(0, dep[v[i]] - (dep[lca] << 1));
			}
		}
		sort(dst + 1, dst + cntd + 1, [](int a, int b) {return a > b;});
		int ans = (n - 1) << 1;
		k = min(k + 1, cntd);
		for (int i = 1; i <= k; ++i)
			ans -= dst[i];
		printf("%d\n", ans);
	}
}

using Solve::Sol;

int main()
{
	Sol();
	return 0;
}

```

---

## 作者：LCat90 (赞：5)

### 思路

口胡一个早读胡出来的……感觉 pyt 讲得不是很透。

为了使得操作同质化，不难首先想到：将 $k+1\rightarrow k$，这样最后一定要回到根节点。

想象一下我们在树上行走的过程，肯定是一个叶子走完了就去下一个（这样也能保证每个点都经过）。这样一定每条边经过 $2$ 次（一来一回）。所以如果没有传送门，答案就是 $2(n-1)$。

考虑传送门带来的影响。首先是使用它的位置：一定是到了叶子节点用。

又，什么时候使用？发现对于一棵子树 $x$，我们肯定是把传送门在最深的节点使用。因为使得总步数尽量少，所以我们肯定希望这个最深的点是子树中走到的最后一个，使得我们不用再向上返回，造成太多步数的浪费。

推导一下（这里假设 $dep_1=0$）：显然，访问完这个子树后我们需要至少回到根节点。设这个点为 $b_x$，那么直接返回的代价是 $dep_{b_x}-dep_{fa_x}=dep_{b_x}-dep_x+1$。

如果使用传送门，那么我们下一步肯定也是要走到父亲的（但是从根节点走），所以代价是 $dep_{fa}=dep_x-1$。

两者相减就得到：$dep_{b_x}-2\times dep_x+2$，也就是在 $x$ 节点中的 $b_x$ 处使用传送门可以使节省的代价。排序过后取前 $k$ 个就行了。

而因为我们是对每个节点都计算了 $b_x$，所以一定能保证每个叶子都被取到，并且每个叶子被取到的位置都是最优的。（注意：我们之前所说返回到父亲节点是不严谨的，但是这样做可以**保证每个叶子节点最终要回到的位置是最上面的**，也就是最优的）

----------

### 实现细节

+ 可能会出现一个叶子重复使用传送门的情况，我们只需要记录一个 vis 数组即可。

+ 注意 1 节点我们不能统计 $b_x$ 进行操作，因为它没有父亲，无法按照这种算法计算。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;
const int N = 5e5 + 5; int read();
int n, k, maxn[N], dep[N], b[N], ans;
bool vis[N]; vector <int> G[N];
struct node {
	int id, x;
	friend bool operator < (node a, node b) { return a.x > b.x; }
} a[N];
void dfs(int x, int fa) {
	maxn[x] = dep[x] = dep[fa] + 1; b[x] = x;
	for(int i = 0;i < G[x].size(); ++i) {
		int to = G[x][i];
		dfs(to, x);
		if(maxn[to] > maxn[x]) maxn[x] = maxn[to], b[x] = b[to];
	}
}
signed main() {
	cin >> n >> k; ++k; ans = 2 * (n - 1);
	for(int i = 2;i <= n; ++i) G[read()].pb(i);
	dep[0] = -1; dfs(1, 0); // dep[1] = 0 
	for(int i = 2;i <= n; ++i) a[i].id = b[i], a[i].x = maxn[i] - 2 * dep[i] + 2;
	sort(a + 1, a + n + 1); 
	for(int i = 1, cnt = 1;i <= n and cnt <= k; ++i) {
		if(a[i].x <= 0) break ;
		if(vis[a[i].id]) continue ;
		ans -= a[i].x, vis[a[i].id] = 1; ++cnt;
	}
	cout << ans; 
    return 0; 
}
int read() {
	char c; int sum = 0; while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') sum = (sum << 3) + (sum << 1) + (c ^ 48), c = getchar();
	return sum;	
}
```

---

## 作者：GI录像机 (赞：4)

更新：删除中文标点与英文之间的空格。

## 思路

显然遍历完每个叶子整个树也遍历完了，而且蹦床只会在叶子使用。

显然我们每次在遍历完一个子树后再遍历其它子树是最优的。无蹦床情况下，答案为 $2n-2-\max  dep$（选择最深的点作为终点）。

考虑叶子 $u$ 到叶子 $v$，如果不使用蹦床，$dis(u,v)=dep_u+dep_v-2dep_{lca}$，如果使用，$dis(1,v)=dep_v$。此次使用蹦床就会使答案减少 $dis(u,v)-dis(1,v)=dep_u-2dep_{lca}$。

发现 $v$ 和答案无关，所以我们只需要考虑每个叶子通过哪一个祖先转向另一个叶子。当然，我们要先遍历完以该叶子到目标祖先中间所有点为根的子树。

要使答案最小，就要使前 $k$ 大的 $dep_u-2dep_{x}$ 最大（$x$ 为 $u$ 的祖先），就要贪心地让大的 $dep_u$ 和尽量的小的 $dep_{x}$ 配对。

为什么这样贪心是对的呢？因为可选的 $dep_{x}$ 数量与非终点的叶子结点数量相同（一个 $x$ 可以选 $s_x-1$ 次，其中 $s_x$ 为儿子数），每个叶子都能和一个 $dep_{x}$ 配对，所以不用担心选了 $x$ 之后其它叶子没得选；因为这是一棵树，所以能替换 $u$ 的所有点都有一个相同的“下位替代” $t$，对于同样被选择的，可以和 $x$ 配对的两个叶子，谁去和“下位替代”配对是一样的。

也就是说，我们要将 $dep$ 更大的 $u$ 作为更大的子树的最后访问叶子。这样就能确定整个树的遍历顺序。然后将每次叶子之间的转移使用蹦床可以减少的代价放进优先队列，寻找前 $k$ 大的代价即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int fa[N], n = read(), k = read(), head[N], tot, dep[N], tmp[N], ans;
bool gg[N];
struct Edge {
	int to, nxt;
} e[N];
void add(int u, int v) {
	e[++tot].to = v;
	e[tot].nxt = head[u];
	head[u] = tot;
}
priority_queue<int>q;
void dfs(int pos) {
	dep[pos] = dep[fa[pos]] + 1;
	tmp[pos] = pos;
	for (int i = head[pos]; i; i = e[i].nxt) {
		dfs(e[i].to);
		if (dep[tmp[pos]] < dep[tmp[e[i].to]])tmp[pos] = tmp[e[i].to];
	}
}
void sfd(int pos) {
	for (int i = head[pos]; i; i = e[i].nxt) {
		sfd(e[i].to);
		if (tmp[pos] != tmp[e[i].to])q.push(-2 * dep[pos] + dep[tmp[e[i].to]]);
	}
}
signed main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	for (int i = 2; i <= n; i++) {
		fa[i] = read();
		add(fa[i], i);
	}
	dep[0] = -1;
	dfs(1);
	sfd(1);
	ans = 2 * n - 2 - dep[tmp[1]];
	while (!q.empty() && k) {
		if (q.top() <= 0)break;
		ans -= q.top();
		q.pop();
		k--;
	}
	write(ans);
	return 0;
}
```


---

## 作者：ReTF (赞：2)

提供一种和官方题解不同的贪心。

首先不强制返回根节点等价于强制返回根节点加上多跳一次。

然后跳非叶子比跳叶子劣。

发现当前确定了若干个要跳的点，现在要确定下一个时，假如覆盖之前所有跳的点到根的路径，经过之前覆盖过的边会使答案增加 $1$，经过之前没有覆盖的边会使答案增加 $-1$。直接拿线段树维护一下取最小值就行了。

假如确定了某个要跳的点，要覆盖其到根节点的路径，其祖先中没有覆盖的边至少占一半，所以可以直接暴力跳。

时间复杂度线性对数。

[Link](https://codeforces.com/contest/1918/submission/244490451)

---

## 作者：WuMin4 (赞：1)

## [CF1918F Caterpillar on a Tree](https://codeforces.com/problemset/problem/1918/F)

## 思路

当 $k=0$ 时我们可以发现答案即为 $2\times (n-1)-w$，其中 $w$ 为根节点出发到儿子节点（可以证明这样走一定是最优的）的最长链长度，因为不用返回根节点，所以不用走这一条路。

设遍历一棵树的原代价为 $2\times (n-1)$，可以发现当我们从根节点出发到儿子节点再传送到根节点（或遍历完不用传送）时，某条路第一次被走过时会使得代价减少 $1$，否则会使得代价增加 $1$。

因此我们对整棵树进行长链剖分，当我们从一条长链跨越到另一条长链时，由于之前的长链已经被走过了，所以之前走过的路径长度会使得代价增加，正在走的长链会使得代价减少。

于是我们可以预处理出所有根节点到儿子节点可以减少的代价，并取前 $k+1$ 大即可（若小于 $0$ 则不取）。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,dep[200005],mdep[200005],hvy[200005],Ans;
vector<int> t[200005],ans;
void dfs(int x,int fa){
	dep[x]=dep[fa]+1,mdep[x]=dep[x];
	for(int v:t[x]){
		if(v!=fa){
			dfs(v,x);
			if(mdep[v]>mdep[x])
				hvy[x]=v,mdep[x]=mdep[v];
		}
	}
}
void dfs2(int x,int fa,int v1,int v2){
	if(t[x].size()==1)
		ans.push_back(v2-v1);
	for(int v:t[x]){
		if(v!=fa){
			if(v==hvy[x]) dfs2(v,x,v1,v2+1);
			else dfs2(v,x,v1+v2,1);
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>k;
	for(int x,i=2;i<=n;i++)
		cin>>x,t[i].push_back(x),t[x].push_back(i);
	dfs(1,0),dfs2(1,0,0,0);
	sort(ans.begin(),ans.end());
	for(int i=ans.size()-1;i>=max(0,(int)(ans.size())-k-1)&&ans[i]>0;i--)
		Ans+=ans[i];
	cout<<2*(n-1)-Ans;
	return 0; 
}
```

---

## 作者：Register_int (赞：1)

怎么都是思维大佬，都能想出牛逼贪心，来点比较爆的做法。

发现你顶多跳 $n$ 次，所以 $m$ 先跟 $n$ 取 $\min$。先来一个树上背包，设 $dp_{u,i}$ 表示 $u$ 子树内往回跳 $i$ 次的最小步数。转移是简单的：

$$dp_{u,i}\underset{\min}{\gets}dp_{u,i-j}+dp_{v,j}+w(j)$$

其中 $w(j)$ 表示往回跳 $j$ 次时 $u\to v$ 这条边需要走的次数。没有往回跳时要往上往下各走一次，否则需要往下走往回跳的次数次，所以 $j=0$ 时 $w(j)=2$，否则 $w(j)=j$。你发现最后可以不回到根，但是没有关系，你可以给他多加一次操作。

容易发现 $w(j)$ 是下凸的，而转移是 $\min+$ 卷积，所以每个 $dp_u$ 都是下凸的。用启发式合并维护差分，问题变成你要在差分数组上加上一个 $2,-1,1,1,1,\cdots$ 的东西。可以直接拆成一个全局加标记和两个单点改，大力做即可。时间复杂度 $O(n\log^2 n)$ 或者 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int n, m, s[MAXN], a[MAXN]; vector<int> g[MAXN];

priority_queue<int, vector<int>, greater<int>> dp[MAXN]; ll ans, sum;

void dfs(int u) {
	s[u] = 1;
	if (g[u].empty()) dp[u].emplace(0);
	for (int v : g[u]) {
		dfs(v), s[u] += s[v], a[v]++;
		int x = dp[v].top(); dp[v].pop(), dp[v].emplace(x - 2);
		if (dp[u].size() < dp[v].size()) dp[u].swap(dp[v]), swap(a[u], a[v]);
		for (; !dp[v].empty(); dp[u].emplace(dp[v].top() - a[u] + a[v]), dp[v].pop());
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 2, u; i <= n; i++) scanf("%d", &u), g[u].emplace_back(i);
	dfs(1), ans = sum = s[1] - 1 << 1;
	for (int i = 1; !dp[1].empty() && i <= m + 1; i++) {
		ans = min(ans, sum += dp[1].top() + a[1]), dp[1].pop();
	}
	printf("%lld", ans);
}
```

---

## 作者：Eraine (赞：1)

编号：CF1918F

tag：贪心

分析题面，我们要让花费最小，可以转换为让每次使用传送经过的路径尽量大。很容易想到传送的起点尽量要为叶子，否则总能找到该子树的某一个叶子更优。若有多个叶子，优先贪心地选择深度更大的叶子更优。

考虑一个非根节点 $u$，在遍历的时候把 $u$ 子树遍历完再访问其他节点。若在访问 $u$ 的叶子时有两次传送到 $u$ 的祖先节点，则第二次必然经过 $(fa_u,u)$ 这条边，更劣。

再考虑一个问题，还是以 $u$ 为例，若在 $u$ 子树中有至少 $1$ 次的传送，那么必然有一次传送到 $u$ 的祖先节点，否则答案不会更优。

将每个节点所在子树预留一个传送到祖先节点的传送。在 $\text{DFS}$ 过程中把信息保留。然后将所有叶子传送的信息按照贡献从小到大排序，选择前面总和为 $k$ 的即可。


$\Theta(n\log n)$。

考场代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5;
vector<int>E[N];
int n,k,len[N],dep[N],f[N],a[N];
priority_queue<int>q;
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		dfs(v,u);
	}
	if(!E[u].size()){
		return;
	}
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		a[i]=f[v]+1;
	}
	sort(a,a+E[u].size());
	for(int i=0;i<E[u].size()-1;i++){
		q.push(a[i]-dep[u]);
	}
	if(u==1){
		q.push(a[E[u].size()-1]-dep[u]);
	}else{
		f[u]=a[E[u].size()-1];
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=2;i<=n;i++){
		int fa;
		scanf("%d",&fa);
		E[fa].push_back(i);
	}
	dep[0]=-1;
	dfs(1,0);
	int cnt=0;
	int res=n*2-2;
	while(!q.empty()){
		++cnt;
		if(cnt>k+1){
			break;
		}
		int x=q.top();
		q.pop();
		if(x<=0){
			break;
		}
		res=res-x;
	}
	printf("%d\n",res);
	return 0;
}
```

各位看官点个赞再走吧 qwq

---

## 作者：Remarks (赞：1)

感觉根本配不上这个评分。甚至不如 D。

考虑前序遍历整棵树，发现一次遍历中，定义下一个要遍历的点为 $pos$，从某一点 $x$ 跳跃到根节点节省的代价为：$\operatorname{dep}_{x}-2\times \operatorname{dep}_{\operatorname{lca}(x,pos)}$，$\operatorname{dep}_k$ 定义为从根节点直接走到 $k$ 经过的边数。我们可以直接遍历整棵树，然后计算每个点能节约的代价，排序，然后根据 $k$ 减掉。

显然我们肯定是走到一个叶子结点再传送。

因为实现遍历的顺序尚未确定，这部分也需要贪心。关注到实际上 $\operatorname{lca}(x,pos)$ 即为当前点所在的所有子树中，一定遍历完的最大的子树的根节点的父亲节点。为了方便大家理解，配图：

![](https://cdn.luogu.com.cn/upload/image_hosting/y9bep5v4.png)

所以我们发现最后遍历子树中的较深节点最优。

另外，因为不需要回到根节点，我们大可假定令其回到根节点，并令 $k+1$，让最后一次跳跃发生在最后一次节点上，答案正确且方便计算：设节约的代价为 $v$，总代价即为 $2\times n -1 -v $。

代码：https://codeforces.com/contest/1918/submission/244187486

---

## 作者：Tx_Lcy (赞：0)

## 思路

考虑如果 $k=0$ 答案就是 $2(n-1)-dep$，其中 $dep$ 表示原树最大深度。

对于 $k \neq 0$ 的情况，我们将原树长链剖分，在一条长链底端跳到根可以减少一定的代价，排序之后取前 $k+1$ 大的代价减去即可。

注意代价有可能是负的。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
int const N=2e5+10;
int n,k,mx[N],res[N],dep[N],high[N];
vector<int>a[N];
inline void dfs(int x){
	for (auto v:a[x]){
		dep[v]=dep[x]+1,dfs(v),mx[x]=max(mx[x],mx[v]+1);
		if (mx[v]>=mx[high[x]]) high[x]=v;
	}
}
inline void Dfs(int x,int tp){
	if (x^1) ++res[tp];
	if (high[x]) Dfs(high[x],tp);
	for (auto v:a[x]) if (v!=high[x]) res[v]=-dep[x],Dfs(v,v);
}
inline void solve(){
	cin>>n>>k;
	rep(i,2,n){
		int p;cin>>p;
		a[p].push_back(i);
	}
	dfs(1),Dfs(1,1);
	sort(res+1,res+n+1,greater<>());
	int ans=2*(n-1);
	rep(i,1,min(n,k+1)) ans-=max(0,res[i]);
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	// cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：TernaryTree (赞：0)

首先我们发现你如果第一次到一个结点就把这个节点记录下来，那么一定存在一种最优方式使得你记录的顺序是一个 dfs 序。感性理解就是，如果不是 dfs 序，那么你一定跳过了某个子树，你之后还要回来去那个子树，答案不会更优。

考虑 $k=0$，此时答案应为 $2n-2-\max dep_u$。并且，我们一定是到一个叶子结点再瞬移回根，否则不优。假设这个叶子是 $u$，下一个要访问的是 $v$，若直接走过去，需要 $dep_u+dep_v-2dep_{lca}$，若使用瞬移再过去，需要 $dep_v$，节省了 $dep_u-2dep_{lca}$ 步。$dep_u$ 越深越好，我们就让所有点的儿子按子树内最深叶子深度升序排序，这样得到的 dfs 序就是我们想要的。

得到 dfs 序之后直接把每个叶子开始瞬移节省的步数扔进数组里排序一下，贪心选前 $k$ 大即可。时间复杂度瓶颈在于排序，$\Theta(n\log n)$。

```cpp
void dfs1(int u, int d) {
	f[u] = dep[u] = d;
	for (int v : tr[u]) dfs1(v, d + 1), f[u] = max(f[u], f[v]);
}

void dfs2(int u) {
	q[++m] = u;
	for (int v : tr[u]) dfs2(v);
}

void fake_main() {
	n = read(), k = read();
	rep(i, 2, n) tr[p[i] = read()].push_back(i);
	dfs1(1, 0);
	rep(i, 1, n) sort(tr[i].begin(), tr[i].end(), [] (int x, int y) {
		return f[x] < f[y];
	});
	dfs2(1); 
	tot = n * 2 - 2 - dep[q[m]];
	vector<int> s;
	rep(i, 1, m - 1) if (!tr[q[i]].size()) s.push_back(max(dep[q[i]] - dep[p[q[i + 1]]] * 2, 0ll));
	sort(s.begin(), s.end(), greater<int> ());
	rep(i, 0, min(k - 1, (int) s.size() - 1)) tot -= s[i];
	cout << tot << endl;
}
```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/%5B%E9%A2%98%E8%A7%A3%5DCF1918F%20Caterpillar%20on%20a%20Tree)

# 思路

首先有一个显然结论：如果我们将所有叶子节点全部遍历过了，那么整棵树都将被遍历。

于是我们只需要考虑叶子节点之间的关系。再其次，我们发现同一棵子树内的叶子节点一定是被连续遍历的。

考虑将 $k$ 赋值为 $k + 1$，那么最终我们是需要直接返回根节点的。

显然，当我们访问完一棵子树后，我们需要返回根节点。令这个点为 $p_u$，则直接返回的代价是 $d_{p_u} - d_{fa_u} = d_{p_u} - d_u + 1$。如果只用传送门，则代价为 $d_{fa_u} = d_u - 1$。

那么两式相减，得到使用传送门能使答案变优的数量：$d_{p_u} - 2 \times d_{u} + 2$。由这个式子可以看出，我们 $p_u$ 就是 $u$ 子树内深度最深的点。

然后贪心地选择前 $k$ 大的数即可。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 2e5 + 10;
int n,k,ans;
int d[N],Max[N],p[N];
bool vis[N];
pii arr[N];
vector<int> g[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void dfs(int u,int fa){
    p[u] = u;
    Max[u] = d[u] = d[fa] + 1;
    for (auto v:g[u]){
        dfs(v,u);
        if (Max[u] < Max[v]){
            Max[u] = Max[v]; p[u] = p[v];
        }
    }
}

int main(){
    n = read(),k = read() + 1;
    d[0] = -1; ans = 2 * (n - 1);
    for (re int i = 2;i <= n;i++){
        int x; x = read();
        g[x].push_back(i);
    }
    dfs(1,0);
    for (re int i = 2;i <= n;i++) arr[i] = {Max[i] - 2 * d[i] + 2,p[i]};
    sort(arr + 1,arr + n + 1,[](const pii &a,const pii &b){
        return a > b;
    });
    for (re int i = 1;i <= n && k;i++){
        if (arr[i].fst <= 0) break;
        if (vis[arr[i].snd]) continue;
        k--;
        ans -= arr[i].fst; vis[arr[i].snd] = true;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Z1qqurat (赞：0)

一眼丁真鉴定为 F<E，我一个 rating 1500 的人居然都能切的 *2500 多少有点离谱了。持续后悔为啥不打这场，打了至少可以场切 D，F。

首先很显然地，如果 $k=0$，考虑到最后不需要回到根节点，如果要回到根就是 $2n-2$，所以就选择一个 $dep$ 最大的点作为结束位置 $t$，答案就是 $ans=2n-2-dep_t$。

考虑到可以进行传送操作，其实可以理解一下，传送操作相当于改变了一个点到它 dfs 序列中下一个点的距离。假如现在在 $u$，它要回跳到一个不在 $u$ 子树中的节点 $v$，继续 dfs，也就是说 $v$ 和 $u$ 在 dfs 序中是相邻的。假设原先从 $v$ 到 $u$ 的距离是 $dis_1$（其实就是 $u,v$ 的树上距离），那么如果使用传送就只需要走根节点 $1$ 到 $v$ 的距离 $dis_2$ 了，所以说在 $u$ 回跳时使用操作 $2$ 就能够使 $ans$ 加上 $dis_2-dis_1$。

显然，在不同的点使用操作 $2$ 是互不影响的，所以直接贪心地取出 $dis_2-dis_1$ 最小且都为负数的 $k$ 个点，对它们执行操作 $2$ 就是最优的。现在问题在于怎么求出所有可以产生合法 $dis_2-dis_1$ 的点对 $u,v$ 以及它们对应的 $dis_2-dis_1$。首先 $u,v$ 得在 dfs 序列上相邻并且 $v$ 不是 $u$ 的儿子，其次 $dis_2$ 是好求的，就是 $dep_v$（这里 $dep_1=0$），问题在于 $dis_1$，其实完全没有必要求出 lca 再求什么树上距离，$u,v$ 之间的位置关系只有两种，第一种是 $u
\in \text{subtree}(v)$，那么 $dis_1=dep_u-dep_v$，第二种就是 $u,v$ 的最近公共祖先 $l$ 就是 $v$ 的父亲，此时 $dis_1=dep_u-dep_v+2$，直接判断一下 $u$ 是否在 $\text{subtree}(v)$ 中就能算出 $dis_2$ 了。

还有一个问题，怎么保证 $dis_2-dis_1$ 都最小？这就需要注意 dfs 顺序的选择了。每次都选择**子树内最大深度最小**的节点先遍历，就能使需要回跳的 $u$ 的 $dis_2-dis_1$ 最小。

时间复杂度 $\mathcal{O}(n\log n)$，瓶颈在于对子树以及 $dis_2-dis_1$ 的排序。

[Submission.](https://codeforces.com/contest/1918/submission/246422281)

---

## 作者：Y_ATM_K (赞：0)

观察题。

设结点 $x$​ 到根的距离为 $dep(x)$​，结点 $x,y$​ 的最近公共祖先为 $lca(x,y)$​。

观察可知，问题等价于 $k+1$ 次传送，最终回到根结点。

观察可知，最优方案一定按照某个 dfs 序遍历整棵树。因为遍历完一棵子树再遍历其他子树一定最优。

观察可知，最优方案一定在叶子结点传送，因此可以把遍历路径看作按 dfs 序的叶子到叶子的路径。

观察可知，没有传送时答案是 $2 \times (n-1)$。考虑计算一次传送的贡献。假设当前遍历到叶子结点 $x$，下一个要遍历的叶子结点为 $y$，则直接走到 $y$ 的代价是 $dep(x) + dep(y) - 2 \times dep(lca(x,y))$，传送后走到 $y$ 的代价是 $dep(y)$。因此在 $x$ 处传送产生的贡献为 $2 \times dep(lca(x,y)) - dep(x)$。要求最小化传送的总贡献。

观察可知，遍历完结点 $x$ 的一棵儿子子树时，若 $x$ 子树没遍历完，传送的贡献是 $2 \times dep(x) - dep(\text{当前结点})$。

观察可知，一棵子树最深的结点一定最后被遍历。因为此时传送的贡献最小。

观察可知，一个叶子的传送贡献是固定的。设结点 $A(x)$ 为最深的满足 $A(x)$ 的子树中最深点不为 $x$ 的 $x$ 的祖先。那么结点 $x$ 的传送贡献为 $2 \times dep(A(x)) - dep(x)$。

观察可知，$A(x)$ 就是长链剖分后 $x$ 所在重链链顶的父亲。因此可以 $O(n)$ 地得到 $A$ 数组，进而得到每个叶子的传送贡献。

观察可知，贡献的值域大小是 $O(n)$ 的，因此对所有贡献计数排序取前 $k+1$ 小即可。

时空复杂度 $O(n)$。

[通过记录](https://codeforces.com/contest/1918/submission/262069582)

---

