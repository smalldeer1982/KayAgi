# [CERC2013] Escape

## 题目描述

### 题目背景

在经历和巫妖王史诗级别的战斗后，英雄们想要从地牢中逃走。


这个地牢是由 $n$ 个房间和 $n-1$ 条走廊连接组成的树状结构，英雄一开始在 $1$ 号房间，而且他只有抵达 $t$ 号房间才能逃离这个地牢。从 $1$ 号房间出发可以抵达任何一个其它的房间，可惜的是，在经历激烈的战斗后，英雄的精力使用完了，所以一开始该英雄的精力为 $0$，并且一旦英雄的精力低于 $0$，那么英雄就会当场逝世，以悲剧结束。在这些房间中，里面暗藏玄机，里面可能有怪兽，也有可能是可以补充精力的魔泉，当然也可能什么也没有，如果是怪兽，那么英雄就必须与它战斗从而消耗一些精力，如果是魔泉，那么英雄可以补充自己的精力。所有的怪兽只会战斗一次，所有的魔泉只能使用一次。（换句话说就是所有的精力的上升或者下降只会发生在第一次访问这个房间的时候）

英雄的精力没有上限，每一个房间都可以反复走多次。

## 样例 #1

### 输入

```
2
7 7
0 -3 2 2 3 -4 0
1 2
2 3
2 4
1 5
5 6
6 7
3 2
3 3 -4
1 3
2 3
```

### 输出

```
escaped
trapped
```

# 题解

## 作者：Krimson (赞：10)

## 简述题意

给定一棵树，每个点有一个权值 $a_{u}$ ，每次新经过一个没有到达过的点 $u$ 则会令当前的 $HP \leftarrow HP+a_{u}$。

询问从 $1$ 出发能否到达 $t$ ，并且任意时刻 $HP\geq 0$。 



## Solution


一道经典题了，唯一的印象就是去年 hehezhou 讲过，但是当时还太菜听不懂，现在回来补一下。

考虑直接做 DP ，设 $f_{u,i}$ 表示以 $i$ 的血量进入子树 $u$ 中最多可以获得 $f_{u,i}$ 的血量。

至于判断是否能到达 $t$ ，就新加入一个权值为 $+\infty$ 的点连接在 $t$ 上，最后看 $f_{1,0}$ 是否为 $+\infty$ 即可。

$f_{u}$ 虽然查询快，但是修改是 $O(W)$ 的，而我们只需要查询一次。

同时，即使使用线段树维护，也不太方便实现两个 $f$ 数组之间的合并，因为要考虑到可能在两个子树间 “反复横跳” 的情况。

因此，我们尝试用另一种方法来得到 $f_{u}$ ，设 $g_{u}$ 为若干个二元组 $(x,y)$ 的集合，表示如果当前血量 $\geq x$ ，则可以再额外加上 $y$ 。（这个东西和 $f_{u}$ 的差分数组很像不过并不完全一样）

那么原来的 $f_{u,i}$ 就变成了这样一个过程：

- 初始令 $HP=i$ 
- 取出当前 $g_{u}$ 中 $x$ 最小的那个二元组 $(x,y)$ ，如果 $HP>x$ 就结束，否则让 $HP \leftarrow HP+y$ ，并删掉二元组 $(x,y)$
- 重复上述步骤

最后得到的 $HP$ 就是 $f_{u,i}+i$ 。

这样子虽然查询一次的复杂度变高了，但是合并就方便了，考虑如何合并两颗子树 $p,q$ ，实际上就是把两个集合给合并起来。

那么现在要把 $u$ 加入到这个子树合并而成的集合中，该如何操作？

1. $a_{u} > 0$  

   直接往当前集合中丢入一个 $(0,a_{u})$

2.  $a_{u}<0$

   我们令 $cur$ 表示以当前 $HP$ 状态下能额外提供的血量为 $cur$ ，$L$ 表示如果要进入子树 $u$ ，初始的 $HP$ 至少应该为多少。

   - 初始令 $cur=a_{u},L=-a_{u}$，表示初始至少有 $-a_{u}$ 的血才能进入，能够额外得到 $a_{u}$ 的血量。
   - 取出最小的二元组 $(x,y)$ 
   - 如果 $x\leq L \or cur < 0$ ，就令 $L\leftarrow\max(L,x-cur),cur\leftarrow cur+y$ 
   - 重复上述操作直到集合为空或者不满足条件
   - 如果最后 $cur>0$ ，就往集合中加入二元组 $(L,cur)$ 

   这样做是考虑我们初始的状态对这个集合的影响。

   如果 $L\geq x$ ，那么二元组 $(x,y)$ 一定会被统计上，同时如果初始 $HP$ 在 $[x,L)$ 之间则不应该得到二元组 $(x,y)$ 的贡献，因此直接将 $(x,y)$ 附加到初始状态上，变成一个新的子问题。

   如果 $cur<0$ ，光拿 $HP\geq L$ 的这一部分一定不优，肯定是还拿了集合里的其他二元组，因此继续将二元组附加到初始状态上直到 $cur\geq 0$ 为止。

可以发现我们每次查询的都是集合里最小值，因此可以用堆来维护，最后只需要查询一下 $f_{1,0}$ 。

如果使用左偏树来维护堆是 $O(n\log n)$ 的，当然直接用 STL 外加启发式合并也可以通过此题，而且比较好写。



## Code

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
#define ll long long 
#define ri int
#define pll pair<ll,ll>
const int MAXN=2e5+7;
const ll inf=1e18;
int n,t;
ll a[MAXN];
vector<int> g[MAXN];
priority_queue<pll,vector<pll>,greater<pll> > q[MAXN];
void merge(priority_queue<pll,vector<pll>,greater<pll> > &p,priority_queue<pll,vector<pll>,greater<pll> > &q){
    if(p.size()<q.size()) p.swap(q);
    while(!q.empty()) p.push(q.top()),q.pop();
}
void dfs(int u,int fa){
    for(auto v:g[u]){
        if(v==fa) continue;
        dfs(v,u);
        merge(q[u],q[v]);
    }
    if(a[u]>0) q[u].push((pll){0,a[u]});
    if(a[u]<0){
        ll cur=a[u],L=-cur;
        while(!q[u].empty()&&(cur<0||q[u].top().first<(L))) L=max(L,q[u].top().first-cur),cur+=q[u].top().second,q[u].pop();
        if(cur>0) q[u].push((pll){L,cur});
    }
}
void work(){
    scanf("%d%d",&n,&t);
    for(ri i=1;i<=n+1;++i) g[i].clear();
    for(ri i=1;i<=n;++i) scanf("%lld",a+i);
    for(ri i=1;i<n;++i){
        int u,v;scanf("%d%d",&u,&v);
        g[u].push_back(v),g[v].push_back(u);
    }
    ++n;
    for(ri i=1;i<=n;++i) while(!q[i].empty()) q[i].pop();
    g[n].push_back(t),g[t].push_back(n);a[n]=inf;
    dfs(1,0);
    ll hp=0;
    while(!q[1].empty()&&hp>=q[1].top().first){
        hp+=q[1].top().second;
        q[1].pop();
    }
    if(hp*2>=inf) puts("escaped");
    else puts("trapped");
}
int main(){
    int T;cin>>T;while(T--) work();
}
```



---

## 作者：command_block (赞：6)

**题意**：有一棵 $n$ 个顶点的树，点 $u$ 有权值 $w_u$。

初始时玩家在顶点 $1$，游戏目标是到达顶点 $t$。

记玩家血量为 $H$，初始为 $0$。第一次到达顶点 $u$ 时，令 $H\gets H+w_u$，若此时 $H<0$，（无论 $u$ 是否是终点）则游戏失败。

判断游戏是否能成功。

多组数据，$n\leq 2\times 10^5$，$\sum n\leq 5\times10^5$。

------------

将 $1$ 视为根。

观察可能的策略：当你血少的时候，可能无法越过某些节点，要在一些分支赚到足够的血，然后越过之前无法越过的点，在其子树赚取更多的血，不断重复……确实很像闯关变强的过程。

为了统一问题，为 $t$ 添加一个子节点 $t'$，令 $w_{t'}=\infty$，问题变为判定最后 $H$ 是否能变为无穷大。

-----

可以猜想，任意子树可以等效为双层菊花图，每个花瓣形如 $\longrightarrow(-x)\longrightarrow(+y)$，$x$ 为进入花瓣的门槛，$y$ 为花瓣的收益（一定大于 $x$）。同时，花瓣的数量（决策段数）是不多的。

一种证明如下：

考虑 DP，记 $f_{u,a}$ 表示从外部获取的血量为 $a$，在子树 $u$ 中能赚的血量。

由于只关心 $f$，我们可以将任意子树等效为双层菊花图：

- 第 $a$ 个花瓣为分支：$\longrightarrow(-a-f_{u,a-1})\longrightarrow(+a+f_{u,a})$。
- 不难发现，若从外部获取血量 $a$，走且仅能前 $a$ 个花瓣，最终权值为 $f_{u,a}$。
- 花瓣数量很多，但有大量花瓣无收益，可以省去。
- 这样构造出的花瓣是最简的。

-----

将花瓣 $\longrightarrow(-x)\longrightarrow(+y)$ 记为二元组 $(x,y)$。

- **观察**：在最简形式中，所有花瓣对应的 $[x,y]$ 不交。

  **证明**：若存在 $\longrightarrow(-x_1)\longrightarrow(+y_1),\ \longrightarrow(-x_2)\longrightarrow(+y_2)$ 满足：

  - $x_1\leq x_2\leq y_1 \leq y_2$：仅从 $x_1$ 开始可以吃完两个分支，两者可以化简为一个花瓣。
  - $x_1\leq x_2\leq y_2\leq y_1$：$x_2$ 更大但获利更少，矛盾。

-----

在树上，先假设根节点的权值为 $0$，考虑两个子树的合并，也就是将两个菊花的所有花瓣直接加起来。

（花瓣是原问题中已有的模型，它的合并是自然的，这是该思路的最大好处）

进行启发式合并，每次加入一个花瓣。对花瓣集合进行化简。

若存在花瓣 $(x_1,y_1),(x_2,y_2)$ 使得 $x_1\leq x_2\leq y_1(\leq y_2)$，若能走花瓣 $(x_1,y_1)$，则一定可以走花瓣 $(x_2,y_2)$，故可以将两者删除并插入 $(x_1,y_1+y_2-x_2)$。不断这样合并，可以使得各个花瓣的 $[x,y]$ 不交。

这可以用 `std::map` 维护。

接下来考虑根节点 $w_u$ 的权值：

- $w_u>0$：相当于插入一个花瓣 $(0,w_u)$。

- $w_u<0$，记 $k=-w_u$。（即“门票”价格）

  按 $a$ 从小到大考虑花瓣 $(x,y)$：

  - 若 $y-x\leq k$（这个花瓣赚的钱尚不够付门票），令 $k\leftarrow k-(b-a)$（将目前累计可以赚的钱从门票中扣除），并删除花瓣 $(x,y)$；
  - 若 $y-x>k$（已经足够支付门票），则 $x\leftarrow x+k$，结束。

复杂度为 $O(n\log^2n)$。

代码中的 `fir` 是 $x$，`sec` 是 $y-x$。

```cpp
#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>
#define fir first
#define sec second

using ll = long long;
using Pr = std::pair<ll,ll>;
using Itor = std::map<ll,ll>::iterator;
const int MaxN = 200050;
const ll INF = 1ll<<60;

void insert(std::map<ll,ll> &f, const Pr &now) {
	bool flag = true; 
	Itor it = f.upper_bound(now.fir);
	if (it!=f.begin()) {
		it--;
		if (now.fir <= it->fir+it->sec){
			it->sec += now.sec;
			flag = false;
		}
	}
	if (flag)
		it = f.insert(now).fir;
	while(true) {
		Itor it2 = it;
		it2++;
		if (it2==f.end() || it->fir+it->sec < it2->fir)
			break;
		it->sec += it2->sec;
		f.erase(it2);
	}
}

void sub(std::map<ll,ll> &f, ll det) {
	while(!f.empty()) {
		if (f.begin()->sec <= det) {
			det -= f.begin()->sec;
			f.erase(f.begin());
		} else {
			Pr now = *f.begin();
			now.fir += det;
			now.sec -= det;
			f.erase(f.begin());
			f.insert(now);
			break;
		}
	}
}

std::map<ll,ll> f[MaxN];
std::vector<int> g[MaxN];
ll w[MaxN];

void dfs(int u,int fa) {
	int t = 0;
	for (int v : g[u])
		if (v != fa) {
			dfs(v,u);
			if (!t) {t=v; continue;}
			if (f[t].size() < f[v].size())
				std::swap(t,v);
			for (const Pr &now : f[v])
				insert(f[t], now);
		}
	if (t) std::swap(f[u], f[t]);
	if (w[u]>0)
		insert(f[u], std::make_pair(0,w[u]));
	if (w[u]<0)
		sub(f[u], -w[u]);
}

void addLine(int u, int v) {
	g[u].push_back(v);
	g[v].push_back(u);
}

void solve() {
	int N, t;
	scanf("%d%d", &N, &t);
	for (int i=1; i<=N; i++)
		scanf("%lld", &w[i]);
	for (int i=1; i<N; i++) {
		int u,v;
		scanf("%d%d", &u, &v);
		addLine(u, v);
	}
	w[N+1] = 2*INF;
	addLine(t, N+1);

	dfs(1,0);
	if (!f[1].empty() && f[1].begin()->fir==0 && f[1].begin()->sec>INF)
		puts("escaped");
	else 
		puts("trapped");

	for (int i=1; i<=N+1; i++) {
		g[i].clear();
		f[i].clear();
	}
}

int main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：vеctorwyx (赞：5)

奇妙的思想，感觉不看题解根不能想不到。

前排友情提示：~~十年OI一场空，不开longlong见祖宗~~。

看完题第一反应：

dp， 维护每个点最多可以出去走一圈回多少血，然后在起点到终点的链上跑，看能不能到终点。

然后假了，发现可以沿着链走回血在往回走找别的子树回血。

然后就有了一个很妙的做法：

每个点维护一个集合， 每个元素是一个二元组 $(a, b)$ 表示以 $a$ 的代价进入可以有 $b$ 的收益（元素之间是并列关系）。

每次转移，就把当前节点的所有儿子加进来，并且加入一个 $(0, v[x])$ 。

转移后要把代表当前节点的元素 $i$ 与其他元素合并，具体有两种情况：

1. 如果 $i$ 的收益是负的，显然没有价值，要把它合并掉；

2. 如果存在元素 $j$ 满足 $i.a + i.b > j.a$，即 $i$ 合法的情况下 $j$ 一定合法，那么合并，保证元素合法并相互独立。

合并时显然 $a$ 越小（代价越小）越容易到达，可以用优先队列维护元素。

在终点后面加一个权值为极大值的点，如果从起点出发能让血量大于等于极大值，就说明能够到达终点，否则不能。

code:

```
#include<bits/stdc++.h>
#define mp make_pair
#define int long long
using namespace std;
int t, n, m;
struct node{
	int to, nxt;
}e[2000010];
int h[200010], cnt, a[200010];
void add(int x, int y){
	e[++cnt].to = y;
	e[cnt].nxt = h[x];
	h[x] = cnt;
}
priority_queue<pair<int, int> >q[200010];
void dfs(int x, int fa){
	for(int i = h[x]; i; i = e[i].nxt){
		int y = e[i].to;
		if(y == fa)
			continue;
		dfs(y, x);
		if(q[x].size() < q[y].size())//启发式合并
			swap(q[x], q[y]);
		while(!q[y].empty())
			q[x].push(q[y].top()), q[y].pop();
	}
	int a1 = 0, a2 = a[x];
	while(!q[x].empty() && (a2 <= 0 || a1 + a2 >= -q[x].top().first)){//两种情况合并。
		a1 = max(a1, -q[x].top().first - a2);
		a2 += q[x].top().second;
		q[x].pop();
	}
	if(a2 >= 0)
		q[x].push(mp(-a1, a2));
}
signed main(){
	scanf("%lld", &t);
	while(t--){
		cnt = 0;
		memset(h, 0, sizeof(h));
		scanf("%lld%lld", &n, &m);
		for(int i = 1; i <= n; i++){
			scanf("%lld", &a[i]);
			while(!q[i].empty())
				q[i].pop();
		}
		for(int i = 1; i < n; i++){
			int x, y;
			scanf("%lld%lld", &x, &y);
			add(x, y);
			add(y, x);
		}
		q[m].push(mp(0, 0x7f7f7f7f7f7f));//加入极大值
		dfs(1, 0);
		int a1 = 0, a2 = 0;//处理起点会出现血量的情况
		while(!q[1].empty()){
			int x = q[1].top().first;
			int y = q[1].top().second;
			q[1].pop();
			a1 = max(a1, -x - a2);
			a2 += y;
		}
		if(a1 != 0){//没有足够的血量进行移动
			puts("trapped");
			continue;
		}
		if(a2 >= 0x7f7f7f7f7f7f)
			puts("escaped");
		else
			puts("trapped");
	}
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：2)

## P7011

### 题意

你有一棵 $n$ 个点的树还有值 $s$，初始时 $s = 0$。树上每个点又有参数 $a_i$，表示：

+ 如果 $a_i = 0$，那么什么也不会发生。

+ 如果 $a_i > 0$，那么第一次抵达点 $i$ 时，$s$ 会加上 $a_i$。

+ 如果 $a_i < 0$，那么第一次抵达点 $i$ 时，$s$ 会减去 $a_i$。

初始时在点 $1$，请问在 $s$ 始终非负的情况下能不能到达点 $t$。

### 标签

思维，dp

### 做法

添加一个 $t$ 的儿子，参数为 $+\infty$，问题就变成了 $s$ 的最大值能不能达到 $+\infty$。

首先考虑一个暴力的 dp：$f_{u, x}$ 表示在 $u$ 子树内，在 $s = x$ 的初始条件下，最多能额外增加多少。最终的结果就是 $f_{1, 0}$ 是否是 $+\infty$。

显然 $f_{u, x}$ 是在 $u$ 固定时是关于 $x$ 单调不减的，并且具有有限个分界点，只需要关注那些与上一项 $f_{u, x - 1}$ 不同的 $f_{u, x}$。

于是就可以通过这样的 $x$ 和 $f_{u, x}$ 完全描述子树 $u$ 的状态。先考虑如何在子树已经合并的情况下在这样的描述中更新 $a_u$ 的影响。

+ 当 $a_u > 0$ 时，新增一个 $(x, f_{u, x})$ 的一对 $(0, a_u)$

+ 当 $a_u < 0$ 时。初始进入 $u$ 时所需的 $s$ 至少为 $x' = -a_u$，进入后 $s$ 会增加 $f_{u, x}' = a_u$。以 $x$ 从小到大的顺序遍历子树合并后的二元组 $(x, y)$，如果 $x \ge x'$ 或者 $f_{u, x}' < 0$，就让 $x' = \max\{x', x - f_{u, x}'\}, f_{u, x}' = f_{u, x}' + y$，否则再遍历也不会增加任何收益，不需要再遍历了。如果 $f_{u, x}' > 0$，那么最后再在 $(x, f_{u, x})$ 的集合中加入 $(x', f_{u, x}')$

接下来考虑如何合并子树。发现对于两个子树的二元组 $(x, f_{u, x})$ 与 $(y, f_{v, y})$ 可以合并的条件是走完一棵子树后能用这棵子树提供的收益更新另外一棵子树，相当于区间 $[x, x + f_{u, x}]$ 与区间 $[y, y + f_{v, y}]$ 有交，这样合并之后的二元组就变成了 $(\min\{x, y\}, f_{u, x} + f_{v, y})$。在每次对于 $a_u < 0$ 的 $u$ 进行更新 $a_u$ 的影响时不断用堆不断取出并合并 $x$ 最小的二元组即可。

### 代码

```cpp
//#pragma GCC optimize("Ofast")
#include <stdio.h>
#include <vector>
#include <queue>
typedef long long lld;
using namespace std;
const int N = 400010;
int T;
int n, t;
vector<int> G[N];
struct node {
	lld x, y;
	int id;
} a[N];
inline bool operator < (const node &x, const node &y) {
	if (y.x <= y.y && x.x > x.y) return 1;
	if (y.x > y.y && x.x <= x.y) return 0;
	if (x.x <= x.y) return x.x > y.x;
	return x.y < y.y;
}
int fa[N];
inline void dfs(int u, int f) {
	fa[u] = f;
	for (int v : G[u])
		if (v != f) dfs(v, u);
}
int ffa[N];
inline int find(int u) {
	return (ffa[u] ^ u) ? (ffa[u] = find(ffa[u])) : u;
}
priority_queue<node> pq;
bool vis[N];
int main() {
	scanf("%d", &T);
	for (; T --; ) {
		scanf("%d%d", &n, &t);
		for (int i = 1; i <= n; ++ i) vector<int>().swap(G[i]), fa[i] = 0;
		lld p;
		for (int i = 1; i <= n; ++ i) {
			scanf("%lld", &p);
			if (p > 0) a[i] = {0, p, i};
			else a[i] = {-p, 0, i};
			if (i == t) a[i].y = 0x3f3f3f3f3f3f3f3fll;
		}
		for (int i = 1, u, v; i < n; ++ i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(1, 0);
		for (int i = 1; i <= n; ++ i) pq.push(a[i]), ffa[i] = i, vis[i] = 0;
		vis[1] = 1;
		for (int u; pq.size(); ) {
			u = pq.top().id; pq.pop();
			if (!vis[u]) {
				vis[u] = 1;
				int v = find(fa[u]);
				a[v].x = max(a[v].x, a[v].x - a[v].y + a[u].x);
				a[v].y = max(a[u].y, a[u].y - a[u].x + a[v].y);
				ffa[u] = v;
				pq.push(a[v]);
			}
		}
		puts(a[1].x ? "trapped" : "escaped");
	}
}
```

---

## 作者：Helloworldwuyuze (赞：1)

# P7011 [CERC2013] Escape 题解

## 题意

一颗根为 1 的树共有 $n$ 个节点，每个节点有权值 $a_i$，当第一次到达一个节点的时候，可以将初始为 0 的体力值加上 $a_i$。每个点可以经过多次，问存不存在一种走法能够在中途所有情况体力都不为负的情况下到达点 $t$。

## Solution

### 简单情况

一种很简单的情况就是菊花图，所有的点都与 1 直接相连，那么很容易想到我们把权值为正的点都收集起来，然后比较这个和与 $-a_t$ 哪个更大，更大就可以到达。

### 稍微复杂

如果菊花图的每一个与 1 相连的子树都是一条链，那么很容易想到每一条链都计算一下最大能够增加多少体力，然后去和 $-a_t$ 比较。但是如果我们在一开始在一条链上无法向下深入，但在攒够了一定体力之后又可以突破向下探索，得到更多的体力值，那么我们就会在树上反复横跳，直到探索所有未探索的点都不优时才停止。

### 引入思想

既然我们无法很好地判断是否继续向下，不妨就先搁置保存。我们设二元组 $(x,y)$ 表示在一个节点的贡献，表示能够在体力值至少为 $x$ 到达时能够产生 $y$ 的贡献。例如如果一个点的权值为 $-4$，那么它的二元组就是 $(4,-4)$，因为走到它至少需要 $4$ 的体力，并且它会给你减少 $4$ 个体力。显然 $y\le0$ 或 $x<0$ 的二元组是无意义的。

如果我们已经求出了所有点的二元组，那么怎么判断能不能够到达点 $t$ 呢？容易想到在点 $t$ 下面挂一个点 $n+1$，且 $a_{n+1}=\infty$，那么如果能够到达点 $t$，那么最终的贡献就一定会非常大，否则肯定达不到 $\infty$ 的量级。于是判断最终能够积攒多少体力值就能够判断出能否到达 $t$。

至于如何求体力的最大值，贪心的思想是从 $x$ 最小的开始，一路往上加体力，如果体力仍够下一个就继续加，不够就退出，最终就可以得到体力的最大值。

### 求解二元组

设 $u$ 是树上一点，$v_1,v_2,v_3$ 是 $u$ 的三个儿子，并且 $a_{v_1}=1,a_{v_2}=2,a_{v_3}=-1$。显然，三个儿子的二元组分别是 $(0,1),(0,2),(1,-1)$。考虑如何将这三个二元组合并到父亲上。

- $a_u>0$ 的情况（以 $a_u=3$ 举例）

> 相对于直接将多个二元组合并为一个二元组，似乎将多个二元组打包成一个集合更加容易一些。因此我们设一个集合 $U=\{(0,1),(0,2)\}$，其中 $(1,-1)$ 中 $y<0$，因此将它舍去。又因为父亲还可以产生 $3$ 的体力贡献，因此将它也加进去，得到 $U=\{(0,1),(0,2),(0,3)\}$。
>
> 总结一下，对于 $a_u>0$ 的情况，将儿子里面的二元组打包起来变成集合，再把自己加进去就行了。

- $a_u<0$ 的情况（以 $a_u=-2$ 举例）

> 首先，容易证明走进子树 $u$ 比不走优。
> 
> 我们仍然先将儿子打包成一个集合，即 $U=\{(0,1),(0,2)\}$。然后发现此时 $u$ 节点的二元组是 $(2,-2)$，那么现在就可以将 $U$ 中的二元组与 $(2,-2)$ 进行真正合并。
>
> 设现在体力值为 $cur$，初始值 $cur=0$，$qr$为进入 $u$ 需要的体力，且初始值为 $-a_u$，$prf$ 是 $u$ 的收益且初始值 $prf=a_u$，那么贪心遍历 $U$ 中的二元组，对于一个 $U$ 中的二元组 $(x,y)$，需要分类讨论：
>
> - 如果 $cur\ge x$，那么显然可以得到 $y$ 的体力，并且收益也需要加上 $y$，于是令 ```cur+=y, prf+=y```。
>
> - 否则，现在的体力不足以进入 $u$ 的一个子树来获得体力，那么就需要让进入 $u$ 的初始体力更高，而且加高初始体力之后 $cur$ 也会变成现在需要的体力，然后 $cur$ 就会满足要求来获取体力 $y$，即 ```qr+=x-cur, cur=x, cur+=y, prf+=y```。需要注意的是我们需要保证在贪心时的顺序，父亲需要在儿子之前被计算，因此就需要父亲的二元组中的 $x$ 要小于任何一个儿子的，在求值时应加上这个条件。

然后一直往上递归直到全部汇集在 1 号节点，贪心即可。

### 数据结构

因为时时需要队列基本有序，因此容易想到堆，直接放到 ```pair<int,int>``` 里面维护即可。

## CODE

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
const int M = 2e5 + 10;
#define int long long
#define endl '\n'
#define pb(x) push_back(x)
typedef pair<int,int> PII; 
const int INF = 1e18;

int T,n,t,a[N];
vector<int> v[N];
priority_queue<PII, vector<PII>, greater<PII> > q[N];

void Print(priority_queue<PII, vector<PII>, greater<PII> > q,int x){
	cout<<x<<" "<<"--------------------"<<endl;
	while(!q.empty())	cout<<q.top().first<<" "<<q.top().second<<endl, q.pop();
}

void dfs(int x,int fa){
	for(auto y:v[x]){
		if(y==fa)	continue;
		dfs(y,x);
		if(q[y].size()>q[x].size())	swap(q[x],q[y]);
		while(!q[y].empty())	q[x].push(q[y].top()), q[y].pop();
	}
	if(a[x]>0)	q[x].push(make_pair(0,a[x]));
	if(a[x]<0){
		int cur=0, qr=-a[x], prf=a[x];
		while(!q[x].empty()&&(qr>q[x].top().first||prf<0)){
			PII p=q[x].top(); q[x].pop();
			if(cur<p.first)	qr+=p.first-cur, cur=p.first;
			cur+=p.second, prf+=p.second;
		}
		if(prf>0)	q[x].push(make_pair(qr,prf));
	}
}

void mian(){
	cin>>n>>t;
	for(int i=1;i<=n+1;++i)	v[i].clear();
	for(int i=1;i<=n+1;++i)	while(!q[i].empty())	q[i].pop();
	for(int i=1;i<=n;++i)	cin>>a[i];
	for(int i=1,x,y;i<n;++i)	cin>>x>>y, v[x].pb(y), v[y].pb(x);
	++n;
	v[n].pb(t), v[t].pb(n); a[n]=INF;
	dfs(1,0);
	int cur=0;
	while(!q[1].empty()&&cur>=q[1].top().first)
		cur+=q[1].top().second, q[1].pop();
	if(cur*2>=INF)	cout<<"escaped"<<endl;
	else	cout<<"trapped"<<endl; 
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>T; while(T--)	mian();
	return 0;
}

```

---

## 作者：岸芷汀兰 (赞：1)

# 一、题目：

[洛谷原题](https://www.luogu.com.cn/problem/P7011)

[codeforces原题](https://codeforces.com/gym/100299)

# 二、思路：

这道题又是一道非常新奇的思维题。我觉得能想到这种算法的人真得很了不起。~~（反正我是看了题解才琢磨出来。）~~

我们考虑类似树形 DP 的方式，从下向上转移。对于每个子树 $x$，我们都维护一个集合 $S_x$。$S_x$ 中的元素是二元组 $(a,b)$，代表**如果你有至少 $a$ 的血量，那么你的血量可以增加 $b$**。现在我们来考虑，如果对于 $x$ 的任意一个儿子 $y$，我们都已知了 $S_y$，如何求出 $S_x$？

1. 新建一个集合 $S$。

2. 将所有 $S_y$ 中的所有元素全部塞到 $S$ 中。

   这样肯定会使一些 $[a,a+b]$ 产生交集，我们将这些 $[a,a+b]$ 合并成大的区间。$(*)$

3. 尝试将二元组 $(0,v_x)$ 加入到集合 $S$ 中。如果可以合并，就不断的从小到大进行合并。直到不能合并为止。

最终怎么判断能不能 Escape 呢？我们可以新增一个点 $t'$，让 $t'$ 与 $t$ 相连，并把 $t'$ 的权值设置成 $+\infty$。最终看一下 $S_1$ 中有没有元素的 $b$ 大于等于 $+\infty$。

可以用 set 来维护集合。合并的时候用启发式合并就可以了。

但是，总感觉 $(*)$ 这一步没有必要。

事实上，$(*)$ 这一步的确没必要。仔细想想，我们其实没有必要使得所有的 $[a,a+b]$ 两两之间没有交集。这并不影响我们的求解过程。

所以，我们只需要用小根堆来维护集合，而不必使用 set。

具体实现过程还必须看代码注释。

# 三、代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;
#define FILEIN(s) freopen(s, "r", stdin);
#define FILEOUT(s) freopen(s, "w", stdout)
#define mem(s, v) memset(s, v, sizeof s)

typedef pair<long long, long long> PLL;

inline int read(void) {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return f * x;
}

const int MAXN = 200005;
const long long INF = 1e15;

int n, t;
long long val[MAXN];
vector<int>linker[MAXN];

priority_queue<PLL, vector<PLL>, greater<PLL> >q[MAXN];

void dfs(int x, int fa) {
	while (!q[x].empty()) q[x].pop();
	for (auto &y : linker[x]) {
		if (y == fa) continue;
		dfs(y, x);
		if (q[y].size() > q[x].size()) swap(q[x], q[y]); // 启发式合并
		while (!q[y].empty()) { q[x].push(q[y].top()); q[y].pop(); }
	}
	PLL u = { 0, val[x] }, v;
	while (!q[x].empty() && (u.second < 0/*条件1*/ || q[x].top().first <= u.first + u.second/*条件2*/)) {
		v = q[x].top(); q[x].pop();
		u = { max(u.first, v.first - u.second), u.second + v.second };
        // 根据while语句的条件，如果靠的是条件2进入的循环，那么max一定会取到u.first。
        // 如果靠的是条件1进入的循环，那么max一定会取到v.first-u.second，意思是提高v的门槛。
        // （注意所有的v.first都是非负的。）
	}
	if (u.second >= 0) q[x].push(u); // 如果该条件不满足，那么q[x]一定是空的。
}

int main() {
	int testdata = read();
	while (testdata --) {
		n = read(); t = read();
		for (int i = 1; i <= n; ++ i) val[i] = read();
		for (int i = 1; i < n; ++ i) {
			int x = read(), y = read();
			linker[x].push_back(y); linker[y].push_back(x);
		}
		++ n; val[n] = INF; linker[t].push_back(n); linker[n].push_back(t);
		dfs(1, 0);
		if (!q[1].empty() && q[1].top().first == 0 && q[1].top().second >= INF) puts("escaped");
		else puts("trapped");

		for (int i = 1; i <= n; ++ i) linker[i].clear();
	}
	return 0;
}
```



---

