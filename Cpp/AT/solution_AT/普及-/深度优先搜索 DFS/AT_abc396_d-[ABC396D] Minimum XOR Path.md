# [ABC396D] Minimum XOR Path

## 题目描述

给定一个简单连通无向图，包含 $N$ 个顶点（编号为 $1$ 至 $N$）和 $M$ 条边（编号为 $1$ 至 $M$）。边 $i$ 连接顶点 $u_i$ 和 $v_i$，并带有标签 $w_i$。

请找出从顶点 $1$ 到顶点 $N$ 的所有简单路径（不重复经过顶点的路径）中，路径上所有边标签的总异或值的最小可能值。

关于异或（XOR）的定义：  
对于非负整数 $A$ 和 $B$，它们的异或 $A \oplus B$ 定义如下：
- $A \oplus B$ 的二进制表示中，$2^k$ 位（$k \geq 0$）的值为 $1$，当且仅当 $A$ 和 $B$ 在 $2^k$ 位上的值不同；否则为 $0$。

例如，$3 \oplus 5 = 6$（二进制表示为 $011 \oplus 101 = 110$）。  
对于 $k$ 个整数 $p_1, \dots, p_k$ 的异或，定义为 $(\cdots ((p_1 \oplus p_2) \oplus p_3) \oplus \cdots \oplus p_k)$，且其值与运算顺序无关。

## 说明/提示

### 约束条件

- $2 \leq N \leq 10$
- $N - 1 \leq M \leq \frac{N(N-1)}{2}$
- $1 \leq u_i < v_i \leq N$
- $0 \leq w_i < 2^{60}$
- 输入的图是简单连通无向图
- 输入中的所有值均为整数

### 样例解释 1

从顶点 $1$ 到顶点 $4$ 存在以下两条简单路径：  
1. 顶点 $1$ → 顶点 $2$ → 顶点 $4$  
   路径上的边标签总异或值为 $6$。  
2. 顶点 $1$ → 顶点 $3$ → 顶点 $4$  
   路径上的边标签总异或值为 $3$。  
因此，最小值为 $3$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4 4
1 2 3
2 4 5
1 3 4
3 4 7```

### 输出

```
3```

## 样例 #2

### 输入

```
4 3
1 2 1
2 3 2
3 4 4```

### 输出

```
7```

## 样例 #3

### 输入

```
7 10
1 2 726259430069220777
1 4 988687862609183408
1 5 298079271598409137
1 6 920499328385871537
1 7 763940148194103497
2 4 382710956291350101
3 4 770341659133285654
3 5 422036395078103425
3 6 472678770470637382
5 7 938201660808593198```

### 输出

```
186751192333709144```

# 题解

## 作者：FlowerAccepted (赞：1)

## 解题思路

注意到，$N \leq 10$，于是 $\cdots\kern0mm\cdots$

直接暴力搜索即可。

简单路径咋办？用 $\tt{dfs}$，开 $vis$ 数组！

每搜到一次 $N$，就更新答案。

都是这时候的人了，相信套 $\tt{dfs}$ 板子没人不会。

注意：

> 十年 $\tt{OI}$ 一场空，不开 `unsigned long long` 见甲虫！
>
> ${\tt{INF}} \geq 2^{31}$ 不 `1ll << x`，转角法老怼到头！
>
> 数组开小报 $\color{purple}{\tt{RE}}$，$\tt{Mf}$ 送你到地狱！
>
> $\tt{OJ}$ 提交忘 `include<vector>`，$\tt{shiny}$ 到头总 $\tt{nl}$！
> 
> 盼君勿忘此四条，一年到头欧气多！

## 代码呈现

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef unsigned long long ll;
typedef pair<int, ll> pii;
const int MAXN = 12;
vector<pii> G[MAXN]; // 邻接表存图
bool vis[MAXN];
ll ans = 1ll << 62;

void add(int u, int v, ll w) { // 简简单单封装一下
    G[u].push_back({v, w});
    G[v].push_back({u, w});
}

void dfs(int x, ll xr, int n) {
    if (x == n) {
        ans = min(xr, ans);
        return;
    }
    vis[x] = 1; // 防止重复
    for (auto i : G[x]) {
        if (!vis[i.first]) {
            dfs(i.first, xr ^ i.second, n);
        }
    }
    vis[x] = 0;
}

int main() {
    int n, m, u, v;
    ll w;
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        cin >> u >> v >> w;
        add(u, v, w);
    }
    dfs(1, 0, n);
    cout << ans;
    return 0;
}

```

## 复杂度分析

由于每个点度数不一，所以复杂度最高能达到 $O(N!)$，但是能过。

---

## 作者：DHT666 (赞：1)

## 题意
给一张无向图，求所有从 $1$ 到 $n$ 的简单路径中，经过的路径长度最小异或。

$1 \le n \le 10$。

## 思路
数据范围很小，直接暴力搜索即可。

时间复杂度应该是 $O(n!)$。

## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;

const LL N = 20, M = 210; // 双向边

LL n, m;
LL e[M], ne[M], l[M], h[N], idx;
bool vis[N];
LL res = (1ll << 63) - 1; // 最大值设够

void add(LL x, LL y, LL z) {
    e[++idx] = y;
    l[idx] = z;
    ne[idx] = h[x];
    h[x] = idx;
}

void dfs(LL u, LL s) {
    vis[u] = 1;
    if(u == n) res = min(res, s); // 统计答案
    for(LL i = h[u]; i; i = ne[i]) {
        LL v = e[i];
        if(!vis[v]) { // 简单路径就是不存在环
            dfs(v, s ^ l[i]);
        }
    }
    vis[u] = 0;
}

int main() {
    cin >> n >> m;
    for(LL i = 1; i <= m; i++) {
        LL x, y, z;
        cin >> x >> y >> z;
        add(x, y, z), add(y, x, z);
    }

    dfs(1, 0);

    cout << res << endl;

    return 0;
}
```

---

## 作者：cjx_AK (赞：1)

### 题目
题目说给你一个无向图，求点 $1$ 到点 $n$ 的最小异或和。

### 思路
考虑到数据范围较小，$n\leqslant10$，我们可以用搜索。
先从 $1$ 号点出发，遍历他连接的点，一直这么搜索，直到搜到 $n$ 号点，更新答案，结束这个分支。注意记得初始化一号点已访问，不然这个点可能会走多次。  

看懂就点个赞吧！

code：

```
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;//w很大
ll n,m,ans=ULONG_LONG_MAX,vis[2000001];
struct node{
	ll v,w;
};
vector<node>ed[200002];
void dfs(ll u,ll dis){
	if(u==n){
		ans=min(ans,dis);//更新
		return;
	}
	for(int i=0;i<ed[u].size();i++){
		if(!vis[ed[u][i].v]){//如果没搜到
			vis[ed[u][i].v]=1;
			dfs(ed[u][i].v,dis^ed[u][i].w);//去搜索
			vis[ed[u][i].v]=0;//搜过变回原来样
	}
	}
}
void solve(){
	cin>>n>>m;
	for(ll i=1;i<=m;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		ed[u].push_back({v,w});
		ed[v].push_back({u,w});
		//存图
	}
	vis[1]=1;//注意初始化，我WA了一发
	dfs(1,0);//带的答案初始为0，现在节点是1
	cout<<ans<<endl;//输出答案
}
signed main(){
	solve();
	return 0;
}
```

---

## 作者：Tomwsc (赞：1)

# AT_abc396_d [ABC396D] Minimum XOR Path 题解

## 题意

给定一张无向带权图，求从 $1$ 号节点到 $n$ 号节点所需要经过的路的最小异或值。

## 思路

注意到 $n\le 10$，于是果断爆搜，接着便是深搜板子了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define PIII pair<int , pair<int , int>>
#define inf (1ll << 62)
#define regint register int
using namespace std;
const int MAXN = 15 , MAXM = 1e4 + 10;
int n , m , ans = inf;
bool flag[MAXN];
vector<pair<int , int>>G[MAXN];

void dfs(int u , int cnt) {
	if(u == n) {
		ans = min(ans , cnt);
		return;
	}
	for(auto [v , w] : G[u])
		if(!flag[v] && u != 1) {
			flag[v] = true;
			dfs(v , cnt ^ w);
			flag[v] = false;
		} else if(u == 1 && !flag[v]) {
			flag[v] = true;
			dfs(v , w);
			flag[v] = false;
		}
	return;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	while(m --) {
		int u , v , w;
		cin >> u >> v >> w;
		G[u].push_back(make_pair(v , w));
		G[v].push_back(make_pair(u , w));
	}
	dfs(1 , 0);
	cout << ans;
	return 0;
}
```

---

## 作者：LionBlaze (赞：0)

抽象的题目。

考虑爆搜。剪枝都不用。

但是我们觉得 DFS 太简单了，所以打算写个 BFS 版本的爆搜。

同样是遍历解答树，只是使用 BFS 序遍历。

注意这里不能用类似 DFS 记忆化的东西，因为就算 $x<y$，也不一定满足 $x \operatorname{xor} z < y \operatorname{xor} z$。

代码：

```cpp
// 草，C 都能写炸
// 不管了，先写 D
// 爆搜显然吧，希望不会掉分。
#include <queue>
#include <tuple>
#include <cstdio>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

unsigned long long dist[10005][15];
bool vis[10005][15];
vector<pair<int, unsigned long long>> web[15];

int main()
{
	memset(dist, 0x3f, sizeof dist);
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		unsigned long long w;
		scanf("%d%d%llu", &u, &v, &w);
		web[u].push_back({ v, w });
		web[v].push_back({ u, w });
	}
	// 如何 DP？
	// 显然 BFS
	// 类似 SPFA……
	queue<tuple<int, int, unsigned long long>> q;
	q.push({ 1, 1, 0 });
	dist[1][1] = 0;
	unsigned long long maxn = 0xffffffffffffffff;
	while (!q.empty())
	{
		tuple<int, int, unsigned long long> uk = q.front();
		q.pop();
		pair<int, int> u = { get<0>(uk), get<1>(uk) };
		unsigned long long w = get<2>(uk);
		if (u.second == n && w < maxn) maxn = w;
		for (pair<int, unsigned long long> vk : web[u.second])
		{
			if (u.first & (1 << (vk.first - 1))) continue;
			tuple<int, int, unsigned long long> v = { u.first | (1 << (vk.first - 1)), vk.first, w ^ vk.second };
			q.push(v);
		}
	}
	printf("%llu\n", maxn);
	return 0;
}
```

---

## 作者：FXLIR (赞：0)

### 思路
有点板。

观察到 $n \leq 10$，于是考虑直接暴力。

通过 dfs 枚举每一条从 $1$ 到 $n$ 的边及路上边权的异或值，再用一个变量 $ans$ 维护最终答案即可。

注意 $ans$ 的初始值一定要 $ \geq 2^{60}-1 $，否则会被卡。

剩下的根据代码自行理解吧。
### 代码
```
#include<cstdio>
#include<iostream>
#define int long long
using namespace std;
const int N=15,INF=1152921504606846976/*即 2 的 60 次方*/;
bool vis[N],is[N][N];
int n,m,u,v,w,a[N][N],ans=INF;
void dfs(int now,int x){
	if(now==n){
		ans=min(ans,x);
		return;
	}
	vis[now]=1;
	for(int i=1;i<=n;i++){
		if(is[now][i]&&vis[i]==0){
			dfs(i,(x^a[now][i]));
		}
	}
	vis[now]=0;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;
		a[u][v]=a[v][u]=w,is[v][u]=is[u][v]=1;
	}
	vis[1]=1;
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：yyycj (赞：0)

## [题目传送门](https://atcoder.jp/contests/abc396/tasks/abc396_d)

## 题目简述
一个简单无向图有 $n$ 个顶点和 $m$ 条边。边 $i$ 连接顶点 $u_{i}$ 和 $v_{i}$，权值为 $w_{i}$。求顶点 $1$ 到 顶点 $N$ 的所有简单路径中，路径上的边的最小异或和。

## 主要思路
一道比较板的 `dfs` 题，由于 $N \le 10$，所以也不需要进行优化。边可以用邻接表记录，从顶点 $1$ 开始依次遍历每条路径即可。注意：标记走过的顶点时，顶点 $1$ 在 `dfs` 前要标记。

由于 $w_{i} < 2^{60}$，所以十年 OI 一场空，_____________________。

## AC Code
```cpp
#include<set>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;
typedef long double db;
const int INT_INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
// ----------------------------

// ----------------------------
int n;
bool vis[20];
ll ans = LL_INF;
set<pair<int, ll> > st[11];
// ----------------------------
void dfs(int u, ll sum) {
	if (u == n) {
		ans = min(ans, sum);
		return;
	}
	for (auto i : st[u]) {
		if (!vis[i.first]) {
			vis[i.first] = true;
			dfs(i.first, sum ^ i.second);
			vis[i.first] = false;
		}
	}
}

int main() {
	int m, u, v; ll w; cin >> n >> m;
	for (int _ = 1; _ <= m; _++) {
		cin >> u >> v >> w;
		st[u].insert(make_pair(v, w));
		st[v].insert(make_pair(u, w));
	}
	// ----------------------------
	vis[1] = true;
	dfs(1, 0);
	// ----------------------------
	cout << ans;
	return 0;
}
```

---

## 作者：shiyuting123 (赞：0)

# [题解 AT_abc396_d](https://www.luogu.com.cn/problem/AT_abc396_d)

## 题意

给你一张图，求出从 $1$ 到 $n$ 的异或值最小的不能走到同一个节点的路径。

注意 $2\leq N\leq 10$。

## 做法

首先我们注意到数据范围只有 $10$ ，首先的想法肯定是暴力搜索。没错，这道题的确是暴力搜索。我们使用 dfs 搜索每一条路径，求出他们的异或和，取最小值即可。

我的代码存图用的是邻接矩阵，自认为要方便一点。

余下看代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int vis[11];//标记数组
long long e[11][11];//邻接矩阵
long long ans=2*1e18;//答案
void dfs(int x,long long sum){
	if(x==n){//找到答案，返回
		ans=min(ans,sum);//取最小值
		return;
	}
	for(int i=1;i<=n;i++){
		if(e[x][i]==-1||vis[i])continue;
		vis[i]=1;//标记节点
		dfs(i,sum^e[x][i]);//继续搜索
		vis[i]=0;//回溯
	}
}
int main(){
	cin>>n>>m;
	memset(e,-1,sizeof(e));
	for(int i=1;i<=m;i++){
		int u,v;
		long long w;
		cin>>u>>v>>w;
		e[u][v]=w;
		e[v][u]=w;//注意是双向的
	}
	vis[1]=1;//标记出发的节点
	dfs(1,0);//暴力搜索
	cout<<ans;
	return 0;
}

```

---

## 作者：zby0501_ (赞：0)

## 思路：
这一题不是很难，我们只要按着题意模拟就行了。

首先，我们用 dfs 求出求出所有 $1$ 到 $N$ 的所有简单路径，同时记录一下异或值，到达 $N$ 号点就将其与原答案取一个最小值就行了。

注意 $ans$ 初始时要设为 $2 \times 10^{18}$，设为 $10^{18}$ 时会 WA 两个点。
## 代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans=2e18;
bool f[15];
vector<pair<int,int> >e[15];
void dfs(int x,int sum){
	if(x==n){
		ans=min(ans,sum);
		return;
	}
	for(auto[a,b]:e[x]){
		if(f[a]) continue;
		f[a]=1;
		dfs(a,sum^b);
		f[a]=0;
	}
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v,w;cin>>u>>v>>w;
		e[u].push_back({v,w});
		e[v].push_back({u,w});
	}
	f[1]=1;
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

# Solution
从 $1$ 开始往其他的点搜索。

当前的最小值为 $res$，如果当前的点为 $1$，那么能直接走到的点和 $1$ 的边权直接赋给 $res$，否则就进行异或。

将搜索到的第一个答案赋值给 $ans$，然后继续比较，否则容易被比较强的测试点卡掉。
# Code
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 1e1 + 5;
int n, m, G[N][N], ans = -1;
bool vis[N];
void dfs(int u, int res) {
	if (u == n) {
		if (~ans) ans = min(ans, res);
		else ans = res;
		return;
	}
	for (int i = 1; i <= n; i ++) {
		if (G[u][i] == -1) continue;
		if (!vis[i]) {
			int v = res;
			if (u == 1) res = G[u][i];
			else res ^= G[u][i];
			vis[i] = 1;
			dfs(i, res);
			res = v, vis[i] = false;
		}
	}
}
signed main (int argc, char *argv[]) {
	*cin.tie(nullptr) << fixed << setprecision (20);
	cout.tie(nullptr) -> ios_base :: sync_with_stdio (false);
	
	memset(G, -1, sizeof(G));
	cin >> n >> m;
	for (int i = 1; i <= m; i ++) {
		int u, v, w;
		cin >> u >> v >> w;
		G[u][v] = G[v][u] = w;
	}
	vis[1] = true;
	dfs(1, 0ll);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：cqbzhzf (赞：0)

[vjudge 中文翻译](https://vjudge.net/problem/AtCoder-abc396_d#author=GPT_zh)
### 思路
第一眼看到题会认为是 bfs，但是注意异或的值不能通过优先队列求最小且 $2\le n \le 10$，所以使用 dfs 对答案进行求解。

实现时注意数据范围与初始化即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=15;
int n,m,vis[N],ans=LONG_LONG_MAX;
struct node
{
	int to,val;
};
vector<node> edge[N];
void dfs(int x,int sum)
{
	if(x==n)
	{
		ans=min(ans,sum);
		return;
	}
	for(node i:edge[x])
	{
		if(vis[i.to])
			continue;
		vis[i.to]=1;
		dfs(i.to,sum^i.val);
		vis[i.to]=0;
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,val;
		cin>>u>>v>>val;
		edge[u].push_back({v,val});
		edge[v].push_back({u,val});
	}
	vis[1]=1;
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：Statax (赞：0)

## 前言

蒟蒻第一次不看题解切掉 ABCDEF，写几篇题解庆祝。

## 思路

这题也是够水，$n \leq 10$。做法有很多状压 DP、暴搜都可以过。

## 代码

真没啥好讲的。
```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <vector>
using namespace std;

#define x first
#define y second
#define db double
#define pb push_back
#define ll long long
#define i128 __int128
#define ull unsigned ll
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

const int MAXN = 100 + 5;
const int inf = 2147483627;
const int mod = 19491001;
const db eps = 1e-9;

template <typename T> inline void read (T &x) {
	x = 0; T f = 1; char ch = getchar ();
	while (!isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar ();
	x *= f;
}

template <typename T, typename... Arp> inline void read (T &x, Arp &...arp) {
	read(x), read(arp...);
}

int n, m;
ll p = (1ll << 62);
bool vis[MAXN];
vector <pair <int, ll> > g[MAXN];

void dfs (int x, ll w) {
    if (x == n) 
        return p = min (p, w), void ();
    for (const auto & v : g[x]) {
        if (vis[v.x]) continue;
        vis[v.x] = true;
        dfs (v.x, w ^ v.y * 1ll);
        vis[v.x] = false;
    }
}

signed main () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
    read (n, m);
    for (int i = 1; i <= m; ++i) {
        int u, v; ll w;
        read (u, v, w);
        g[u].pb ({v, w}), g[v].pb ({u, w});
    }
    vis[1] = true;
    dfs (1, 0), printf ("%lld\n", p);
	return 0;
}
```

---

## 作者：WuMin4 (赞：0)

## 题意

找出带边权的简单连通无向图上一条从顶点 $1$ 到 $n$ 边权异或之和最小的路径。

$2\le n\le 10$

## 思路

发现 $n\le 10$，可以直接 dfs 求出每条路径的异或值，状态数大概是 $n!$ 的，可以通过本题。

注意边权会超 `int`，记得开 `long long`，还有在 dfs 时需要回溯，要重置 `vis` 数组。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int x,d;
};
int n,m,ans=LONG_LONG_MAX;
bool vis[15];
vector<node> t[15];
void dfs(int x,int xr){
	if(x==n){
		ans=min(ans,xr);
		return;
	}
	vis[x]=true;
	for(node v:t[x]){
		if(!vis[v.x]){
			dfs(v.x,xr^v.d);
		}
	}
	vis[x]=false;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int x,y,d,i=1;i<=m;i++){
		cin>>x>>y>>d;
		t[x].push_back({y,d});
		t[y].push_back({x,d});
	}
	dfs(1,0);
	cout<<ans;
	return 0; 
}
```

---

## 作者：chaqjs (赞：0)

## 题目翻译

给你一个 $n$ 个点 $m$ 条边的无向图，第 $i$ 条边从 $u_i$ 到 $v_i$，价值为 $w_i$。在所有从 $1$ 号点到 $n$ 号点的路径中，找出一条边权异或和最小的路径，输出最小异或值。

这里，一个由 $k$ 个数组成的数列 $p$ 的异或值为 $(\dots((p_1 \oplus p_2) \oplus p_3) \oplus \dots \oplus p_k)$。

## 思路

注意到 $n \le 10$，所以我们直接暴搜就行，搜索每一条从 $1$ 到 $n$ 的路径，找到最小的异或值。不过数值可能比较大，注意开 `long long`。具体看代码注释。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 10 + 5;

int n, m;
vector<pair<int, int> > g[N];// 存图 
bool vis[N];// 标记是否走过 
int ans = 0x3f3f3f3f3f3f3f3f;

void dfs(int u, int now) {// u 表示当前节点，now 表示当前答案 
	if (u == n) {// 如果走到 n 节点了 
		ans = min(ans, now);// 更新 ans 
		return ;// 返回 
	}
	for (auto edge : g[u]) {// 枚举 u 节点的所有儿子 
		int v = edge.first;
		int w = edge.second;
		if (vis[v]) continue;// 如果走过，跳过 
		vis[v] = 1;// 标记已走过 
		dfs(v, now ^ w);// 搜索下一个点 
		vis[v] = 0;// 回溯 
	}
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	
	// 读入 
	cin >> n >> m;
	for (int i = 1; i <= m; i++) { 
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back(make_pair(v, w));
		g[v].push_back(make_pair(u, w));
	}
	
	vis[1] = 1;// 这里一定要标记 1 号节点 
	dfs(1, 0);// 开始搜索 
	
	cout << ans;

	return 0;
}

```

---

