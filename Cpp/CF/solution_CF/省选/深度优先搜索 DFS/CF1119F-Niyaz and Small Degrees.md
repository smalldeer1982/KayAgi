# Niyaz and Small Degrees

## 题目描述

Niyaz 有一棵包含 $n$ 个顶点的树，顶点编号从 $1$ 到 $n$。树是一种无环连通图。

树中的每条边都有一个严格为正的整数权值。一个顶点的度数是与该顶点相连的边的数量。

Niyaz 不喜欢树中有顶点的度数过大。对于每个 $x$，其中 $0 \leq x \leq n-1$，他想要找到删除一组边的最小总权值，使得所有顶点的度数都不超过 $x$。

## 说明/提示

在第一个样例中，顶点 $1$ 与所有其他顶点相连。因此对于每个 $x$，你应该删除顶点 $1$ 上权值最小的 $(4-x)$ 条边，所以答案分别为 $1+2+3+4$，$1+2+3$，$1+2$，$1$ 和 $0$。

在第二个样例中，对于 $x=0$，你需要删除所有的边；对于 $x=1$，你可以删除权值为 $1$ 和 $5$ 的两条边；对于 $x \geq 2$，不需要删除任何边，所以答案分别为 $1+2+5+14$，$1+5$，$0$，$0$ 和 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 2 1
1 3 2
1 4 3
1 5 4
```

### 输出

```
10 6 3 1 0 ```

## 样例 #2

### 输入

```
5
1 2 1
2 3 2
3 4 5
4 5 14
```

### 输出

```
22 6 0 0 0 ```

# 题解

## 作者：AutumnKite (赞：29)

[给我的 Blog 打个广告](https://autumnkite.github.io/cf1119f-sol/)

[题目传送门](http://codeforces.com/contest/1119/problem/F)

## 题意

给定一棵 $n$ 个节点的树，有边权，对于所有 $x\ (0\le x < n)$，可以删去一些边，求使得所有节点的度数 $\le x$ 的删掉的边的边权之和的最小值。

节点的度数指以该点为某一端点的边的数量。

$n\le 250\,000$

## 暴力——独立求解

显然是树形 DP，记 $dp_{u,0/1}$ 表示 $u$ 与父亲的连边不删/删时，以 $u$ 为根的子树满足所有节点度数 $\le x$ 的删掉的边的最小值。

不考虑度数限制，显然有 $dp_{u,0}=dp_{u,1}=\sum \min(dp_{v,0},dp_{v,1}+w)$（$v$ 是 $u$ 的儿子，$w$ 表示对应边的边权）。记 $d_i$ 表示 $i$ 的度数，把 $dp_{v,1}+w\le dp_{v,0}$ 的儿子 $v$ 叫做好儿子，其余叫做坏儿子。考虑度数限制，假设求 $dp_{u,0}$（$dp_{u,1}$ 同理），记 $cnt$ 为好儿子数量，我们需要把 $\max(0,d_i-x-cnt)$ 个坏儿子变成好儿子。

只需要维护一个堆，将所有坏儿子 $dp_{v,1}+w-dp_{v,0}$ 的值压入堆中，将前 $\max(0,d_i-x-cnt)$ 小的值之和记为 $sum$，则 $dp_{u,0}=sum+\sum dp_{v,0}$。

时间复杂度 $O(n^2\log n)$。

## 暴力代码

注意代码实现与上述有很大差别，但思想一致。

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 250005
#define INF 0x3f3f3f3f3f3f3f3fll
int n;
int edge, to[N << 1], pr[N << 1], tw[N << 1], hd[N];
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
}
long long dp[N][2];
void dfs(int X, int u, int fa = 0){
	std :: vector<long long> val;
	dp[u][0] = dp[u][1] = 0;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa) dfs(X, v, u), val.push_back(dp[v][1] + tw[i] - dp[v][0]), dp[u][0] += dp[v][0];
	dp[u][1] = dp[u][0];
	std :: sort(val.begin(), val.end());
	int d = val.size();
	for (register int i = 0; i < d && (i < d - X || val[i] < 0); ++i) dp[u][1] += val[i];
	if (!X) return dp[u][0] = INF, void(0);
	++d;
	for (register int i = 0; i < d - 1 && (i < d - X || val[i] < 0); ++i) dp[u][0] += val[i];
}
int main(){
	n = read();
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), addedge(u, v, w), addedge(v, u, w);
	for (register int i = 0; i < n; ++i) dfs(i, 1), printf("%lld ", dp[1][1]);
}
```

## 正解

可以发现对于某个 $x$，若一个节点 $u$ 的度数 $\le x$，那这个点本身就不需要考虑了，只需要将 $w(u,v)$ 加入与 $v$ 的堆中。

也就是说，我们把 $u$ 当做叶子节点来看待，即：

```
  /\       /\
 /__\     /__\
     \   /
       u
```

也相当于把 $u$ “删去”，不同的是，与 $u$ 相连的点的度数不会改变。

如果我们可以每次在把所有度数 $\le x$ 的点删去后的森林中进行 DP（对每棵树进行 DP 然后把每棵树根节点的 $dp$ 值加起来，具体是加 $dp_{i,0}$ 还是 $dp_{i,1}$ 要看写法），点数之和为 $\sum_{x=0}^{n-1}\sum_{i=1}^{n} [d_i>x]=\sum_{i=1}^{n} d_i=2n-2=O(n)$，总时间复杂度就变为 $O(n\log n)$ 了。

具体实现时，可以用两个普通堆实现一个支持删除的堆。每次“删去”一个点 $u$ 时，在所有与该点相连的点 $v$ 对应的堆中加入 $w(u,v)$；DP 时，假设需要把 $cnt$ 个坏儿子变为好儿子，则我们强制使得堆中只有 $cnt$ 个值，同时记录堆中所有值之和，这样 $dp$ 值就可以很容易地求出；求出 $dp$ 值之后，为了避免每次重新执行所有“删点操作”，我们需要将堆中由“删点”得来的值保留，即把强制删去的值重新插入堆中，把 DP 时得来的值从堆中删去。

## 正解代码

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 250005
#define INF 0x3f3f3f3f3f3f3f3fll
int n, d[N], X, vis[N];
long long sum;
std :: vector< std :: pair<int, int> > E[N];
std :: pair<int, int> D[N];
void addedge(int u, int v, int w){
	E[u].push_back(std :: make_pair(v, w)), ++d[u];
}
bool cmp(std :: pair<int, int> x, std :: pair<int, int> y){
	return d[x.first] > d[y.first];
}
struct Normal_Heap{ // 普通大根堆
	std :: vector<long long> a;
	void push(long long x){ a.push_back(x), std :: push_heap(a.begin(), a.end()); }
	long long top(){ return a[0]; }
	void pop(){ std :: pop_heap(a.begin(), a.end()), a.pop_back(); }
	long long popn(){ long long x; return std :: pop_heap(a.begin(), a.end()), x = a[a.size() - 1], a.pop_back(), x; }
	int size(){ return a.size(); }
};
struct Erase_Heap{ // 用两个普通堆实现的支持删除的大根堆
	Normal_Heap a, b;
	int sz; long long sum;
	void push(long long x){ a.push(x), ++sz, sum += x; }
	void erase(long long x){ b.push(x), --sz, sum -= x; }
	void pre(){ while (a.size() && b.size() && a.top() == b.top()) a.pop(), b.pop(); }
	long long top(){ return pre(), a.top(); }
	void pop(){ pre(), --sz, sum -= a.top(), a.pop(); }
	int size(){ return sz; }
}H[N];
void die(int u){ // “删点”操作
	for (auto to : E[u]){
		register int v = to.first, w = to.second;
		if (d[v] <= X) break;
		H[v].push(w);
	}
}
long long dp[N][2];
std :: vector<long long> tmp, del;
void dfs(int u, int fa = 0){
	vis[u] = X;
	int num = d[u] - X;
	long long res = 0;
	for (; H[u].size() > num; H[u].pop()) ;
	for (auto to : E[u]){
		register int v = to.first, w = to.second;
		if (v == fa) continue;
		if (d[v] <= X) break;
		dfs(v, u);
	}
	tmp.clear(), del.clear();
	for (auto to : E[u]){
		register int v = to.first, w = to.second;
		if (v == fa) continue;
		if (d[v] <= X) break;
		long long x = dp[v][1] + w - dp[v][0];
		if (x <= 0){ --num, res += dp[v][1] + w; continue; }
		res += dp[v][0], H[u].push(x), del.push_back(x);
	}
	for (; H[u].size() && H[u].size() > num; H[u].pop()) tmp.push_back(H[u].top()); // 强制弹堆
	dp[u][0] = res + H[u].sum;
	for (; H[u].size() && H[u].size() > num - 1; H[u].pop()) tmp.push_back(H[u].top()); // 强制弹堆
	dp[u][1] = res + H[u].sum;
	for (auto i : tmp) H[u].push(i); // 还原强制弹堆时删除的值
	for (auto i : del) H[u].erase(i); // 删除 DP 得来的值
}
int main(){
	n = read();
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), addedge(u, v, w), addedge(v, u, w), sum += w;
	printf("%lld", sum);
	for (register int i = 1; i <= n; ++i)
		D[i] = std :: make_pair(d[i], i), std :: sort(E[i].begin(), E[i].end(), cmp);
	std :: sort(D + 1, D + 1 + n);
	register int i = 1;
	for (X = 1; X < n; ++X){
		while (i <= n && D[i].first == X) die(D[i].second), ++i;
		long long ans = 0;
		for (register int j = i; j <= n; ++j){
			register int v = D[j].second;
			if (vis[v] == X) continue;
			dfs(v), ans += dp[v][0];
		}
		printf(" %lld", ans);
	}
	putchar('\n');
}
```

---

## 作者：xfrvq (赞：14)

双倍经验 [$\tt P7600$](/problem/P7600)，改改代码就能过。

---

考虑固定 $x$ 怎么做。我们树形 $\tt dp$，记

+ $f_{u,0}$ **删除 $u$ 到父亲的边**，让 $u$ 子树符合度数条件的最小代价
+ $f_{u,1}$ **保留 $u$ 到父亲的边**，让 $u$ 子树符合度数条件的最小代价
+ $d_u$ 为 $u$ 的度数，$u$ 点要删除的总边数是 $de_u-x(de_u\gt x)$。

然后对于若干个 $u$ 的儿子 $v$ 以及它们之间边权 $w$，每种都有

1. 删除 $u$ 到 $v$ 的边，代价 $f_{v,0}+w$（一类贡献 $a_1$）
2. 保留 $u$ 到 $v$ 的边，代价 $f_{v,1}$（二类贡献 $a_2$）

+ 对于 $f_{u,0}$ 的计算而言，需要至少删除 $de_u-x-1$ 条到儿子的边（在至少 $de_u-x-1$ 个儿子那里取 $a_1$，剩下儿子取 $a_2$）
+ 对于 $f_{u,1}$ 的计算而言，需要至少删除 $de_u-x$ 条到儿子的边（在至少 $de_u-x$ 个儿子那里取 $a_1$，剩下儿子取 $a_2$）

我们先假设全部取 $a_2$，然后在找出代价最小的某种方式，替换若干个 $a_2$ 为 $a_1$。

我们先计算出所有 $v$ 的 $a_2$ 的和，然后对于每个 $v$ 我们计算出 $a_1-a_2$ 的值，挑出最小的那些加上到这个和里面即可（注意 $a_1-a_2=f_{v,0}+w-f_{v,1}$）。

对于 $u$ 的 $\tt dfs$ 过程中，我们用堆维护出所有 $a_1-a_2$ 的值，然后从小往大加到 $a_2$ 的和里面（即完成了替换若干个 $a_2$ 为 $a_1$ 这步）。

总复杂度 $\mathcal O(n\log n)$。

---

现在考虑从小往大计算每一个 $x_0$ 怎么做。

我上面说树上 $\tt dfs$ 时要对每个点维护一个堆，但是那个堆是对每个点而言的，一旦这个点的计算结束之后，这个堆也就没用了。

如果我们是朴素的对每个 $x_0$ 都计算，总有某些信息会被重复计算，所以我们这里给每个点都维护堆，加上“从小往大枚举”这个条件，尝试让后来的计算可以利用以前算过的信息。

观察从小往大这个条件，如果一个 $u$ 有 $d_u\le x_0$，那在后续的 $x_0\sim n$ 的计算中，这个 $u$ 就没用了，因为它的度数已经满足条件了。而一个点 $u$ 只会有用 $d_u$ 次，而 $\sum d_u=O(n)$，所以我们对于每个 $x_0$ 都只计算当前有用的点，时间是可行的

我们以有用的点为根进行 $\tt dfs$，无用点视为叶子，虽然有若干个由有用点构成的子树共用一个叶子（无用点将会有多个父亲），但是无妨因为无用点根本不会处理，可以当作其不存在。

![](https://img-blog.csdnimg.cn/556a68634c0045c29c68bb7659b84edb.png)

如图，$u$ 是无用点，$p,q$ 是两个有用点的子树，我们从 $p,q$ 中任意挑一个点开始 $\tt dfs$ 都可以把这个子树给 $\tt dfs$ 完一遍。因为无用点是叶子，此时它相邻的有用点（$p_3,q_2$）全都可以视为它父亲。

因为只会计算有用的点，所以一个点被标记无用之后，就应该处理它余留的贡献。由这个父子关系，它带给每个父亲的贡献是一个 $u$ 的 $a_1-a_2$ 的权。因为无用点没有子树，所以不删边没有子树代价（$a_2=0$），删边只会有删边自身的代价（$a_1=w$），这个权就等于 $w$，即这个点连向他父亲的边的权，我们把这个权放进它父亲的堆里就把这个点的余留贡献处理完了。

然后考虑这个 $\tt dfs$ 的过程。首先肯定要计算所有儿子 $a_2$ 的和，然后把 $a_1-a_2$ 的值放到堆里。堆里此时会有两类元素。

1. 无用点儿子带来的贡献（所有无用点儿子 $v_0$ 的 $w_0$ 值）这个东西在后面的计算中还有用，因为无用点儿子的父子关系是不会变的。
2. 有用点儿子带来的贡献（所有有用点儿子 $v_1$ 的 $a_1-a_2$ 权值）这个东西只在这轮计算中有用，因为下一轮又有些点会变得没用，有用点树形态发生改变。

我们可以考虑在这轮 $\tt dfs$ 完之后撤销堆中二类元素的加入。复杂度分析还是 $\sum d_u\log d_u=\mathcal O(n\log n)$。

在处理好堆中的东西之后，我们计算前若干小的元素之和，这个可以通过动态维护堆元素和，然后踢掉多余元素的方法解决。但是你踢掉的可能有不应该踢掉的一类元素，所以此时还需要撤销这些踢掉的操作。

总体而言就是需要一个可删除撤销删除，插入操作的堆。这个可以维护两个堆分别表示插入和删除，插入元素放插入堆删除元素放删除堆，求 `top` 需要先踢掉两个堆顶部的相同元素，复杂度可以均摊。

---

实现时很容易不小心让复杂度带上一个 $n^2$，也需要一些优化。

```cpp
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2.5e5 + 5;

int n,dg[N],de,p[N],pos,vis[N];
ll tot,f[2][N],ans[N];
vector<int> D[N];
vector<pair<int,int>> G[N];
vector<ll> ins,ers;

struct heap{ // 能撤销插入/删除操作的堆
	priority_queue<int> q1,q2; ll cnt; // 插入堆，删除堆，动态维护的堆元素和
	void ins(int x){ q1.push(x); cnt += x; }
	void ers(int x){ q2.push(x); cnt -= x; }
	void fls(){ while(q1.size() && q2.size() && q1.top() == q2.top()) q1.pop(),q2.pop(); }
    // flush：清空两个堆顶部的相同元素，之后才能正常求 top()/pop()
	int top(){ fls(); return q1.top(); }
	void pop(){ cnt -= top(); q1.pop(); }
	int size(){ return q1.size() - q2.size(); } // 注意是两个堆大小之差
} H[N];

void mark(int u){ // 把有用点标记为无用，处理其余留贡献
	for(auto[v,w] : G[u])
		if(dg[v] <= de) break; else H[v].ins(w);
}

void dfs(int u,int ft){
	int del = dg[u] - (vis[u] = de);
    // 这里有个 vis，每轮固定设为当前的 de，防止同个子树被搜多次
    // del 就是要删的边的个数
	while(H[u].size() > del) H[u].pop();
    // 之后要删的边数只会越来越少，这轮没用的一些值后面也没用了
	for(auto[v,w] : G[u]) if(v != ft)
		if(dg[v] <= de) break; else dfs(v,u); // 先 dfs 儿子
	ins.clear(),ers.clear(); // 记录应该撤销的值
    // 刚刚先 dfs 儿子，因为后面这个 ins 和 ers 是每次函数都要调用一遍的
	for(auto[v,w] : G[u]) if(v != ft){
		if(dg[v] <= de) break; // 那个排序优化的用武之地
		ll val = f[0][v] + w - f[1][v]; // a1-a2 的值
        tot += f[1][v]; // 用 tot 装 a2 的和，f 数组装 a1-a2 的和，最后加起来
		if(val <= 0) tot += val,--del; // 如果取 a1（即删边）会更优，不删白不删
		else H[u].ins(val),ins.push_back(val); // 把 a1-a2 放到堆中（注意撤销）
	}
	while(H[u].size() && H[u].size() > del) ers.push_back(H[u].top()),H[u].pop();
    // 删的只剩下前 del 个最小值，但是注意多删的要放进撤销数组里面
	f[1][u] = H[u].cnt;
	while(H[u].size() && H[u].size() > del - 1) ers.push_back(H[u].top()),H[u].pop();
    // 删的只剩下前 del-1 个最小值，
	f[0][u] = H[u].cnt;
	for(int x : ers) H[u].ins(x); // 撤销不该删除的
	for(int x : ins) H[u].ers(x); // 撤销不该加入的
}

int main(){
	scanf("%d",&n);
	for(int i = 1,u,v,w;i < n;++i){
		scanf("%d%d%d",&u,&v,&w);
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
		ans[0] += w; // ans[0] = sum w(u,v)
	}
	for(int i = 1;i <= n;++i) dg[i] = G[i].size(),p[i] = i;
	sort(p + 1,p + n + 1,[](int a,int b){return dg[a] < dg[b];});
	auto cmp = [](auto a,auto b){return dg[a.first] > dg[b.first];};
	for(int i = 1;i <= n;++i) ranges::sort(G[i],cmp);
    // 【优化】把每个点的所有邻点都按照 dg 降序排序，如果遇到哪个点无用，后面的点肯定都是无用
	for(de = 1,pos = 1;de < n;++de,tot = 0){
		for(;pos <= n && dg[p[pos]] == de;) mark(p[pos++]); // [1,pos) 是当前的无用点
        // p 内部将所有点按照 dg 升序排序，目的是方便处理无用点
		for(int j = pos;j <= n;++j) // 后面 [pos,n] 都是有用点
			if(vis[p[j]] != de) dfs(p[j],0),tot += f[1][p[j]];
		ans[de] = tot;
	}
	for(int i = 0;i < n;++i) printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：3)

[CF1119F Niyaz and Small Degrees](https://www.luogu.com.cn/problem/CF1119F)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17763762.html)

首先考虑暴力怎么做，即做 $n$ 次树形 DP，设 $f_{i,0}$ 表示**强制**删掉 $(i,fa_i)$ 这条边的最小代价，$f_{i,1}$ 表示**强制**保留 $(i,fa_i)$ 这条边的最小代价。

对于一个点 $u$，在限制度数为 $x$ 时，对于 $f_{i,0}$ 需要删 $deg_u-x-1$ 个儿子，$f_{i,1}$ 需要删 $deg_u-x$ 个儿子。

删去 $(u,v)$ 的代价是 $val+f_{v,0}$，不删的代价是 $f_{v,1}$。首先强制一条边都不删，然后我们选一些儿子用 $cost=val+f_{v,0}-f_{v,1}$ 来替代，我们要选择最小的一些 $cost$ 加到 $f_u$ 里，需要排序，复杂度为 $\mathcal O(n^2\log n)$。

考虑如何优化，观察题目中的限制，度数是一个比较特殊的东西，手玩几组数据可以发现对于一个度数较小的节点，在 $x\geq deg_u$ 的时候，$f_{u,0}$ 和 $f_{u,1}$ 都选择了全部的儿子，没有进行替代操作，但对于每次 DP 它都需要计算一次，非常的呆，考虑删去这些节点，把这个节点的东西存在它相邻的有用的节点即度数 $>x$ 的节点里。然后每次只 DP 度数 $>x$
 的点，这样复杂度就是对的，因为 $\sum deg=2n-2$，而一个点被 DP，当且仅当 $x\in[0,deg]$，这样一个点最多被计算 $deg$ 次。

记当前度数限制为 $x$，设 $deg_u\leq x$ 的点为无用点，$deg_u>x$ 的点为有用点，我们对于当前的答案只需要 DP 有用点，对于已经无用的点 $u$，它的 $f_{u,0}$ 和 $f_{u,1}$ 之间只差了一个 $(u,fa_u)$ 的权值（因为它不需要删任何子树内的边，只需要满足 DP 状态的限制），所以它的 $cost$ 就是一条边权 $val$。

但是这样可能会出现一个点变成了无用点，它的父亲是有用点，儿子也是有用点，此时我们不需要 DP 它，但是需要 DP 它的父亲和儿子。

考虑删掉一些无用点后会形成若干个连通块，在对它的父亲所在连通块 DP 时可以把它直接看成叶子，而对于它的儿子所在连通块 DP 是可以把也它看成叶子，这样一个点可能有多个父亲，但是由于它是无用的，它的 $cost$ 只和边权有关，删掉它的时候只考虑连接它的有用点并想办法存下它的 $cost$ 即可。而对于无用点和无用点之间的边，我们一定会选择保留，所以这部分是不需要考虑的。

图大概是这样的：

![image.png](https://s2.loli.net/2023/10/14/9UPkYwcsgfp5nSN.png)

其中 $2,4$ 是无用点，剩下的都是有用点，对于一个红色的连通块，它的内部仍然先原来一样 DP，只不过它还连了一些无用点，这些无用点对它有一个 $cost$ 的影响，即选择 $cost$ 来替代是是不一定全需要从它的有用点子树里找，也可以选无用点，所以我们现在的问题是如何解决无用点对有用点的贡献。

暴力计算是不对的，因为我们上面只保证了 DP 有用点点数的正确性，如果对于每个有用点都扫一遍连接它的所有无用点，那一个菊花就噶了。

但是发现 DP 连接**有用点和有用点的边**的总个数也是线性的，刚刚复杂度假掉的原因是计算了**有用点和无用点的边**所以我们考虑用一个数据结构维护一个点的所有 $cost$，然后从中选一些最小的。

理一下思路，我们需要支持加数（无用点对于有用点以及有用点的有用点儿子对他自己的 $cost$），删数（当前有用点的儿子可能在 $x$ 时的 $cost$ 和在 $x+1$ 时不同，所以 DP 完一次要删掉一个有用点的儿子对他自己的 $cost$），可以用堆维护，这样总复杂度就是 $\mathcal O(n\log n)$。

代码也不太好写，有注释，一不小心复杂度就假了。

```cpp
struct Heap
{
	priority_queue<int> q1,q2;
	int sum;
	inline void add(int x){q1.e(x),sum+=x;}
	inline void del(int x){q2.e(x),sum-=x;}
	inline void update(){while(!q1.empty()&&!q2.empty()&&q1.top()==q2.top())q1.pop(),q2.pop();}
	inline int top(){return update(),q1.top();}
	inline void pop(){sum-=top(),q1.pop();}
	inline int size(){return q1.size()-q2.size();}
}a[250001];//可删堆
vector<pii> T[250001];
vector<int> ins,ers;
int pos,dg,vis[250001],ans[250001],f[250001][2],n,deg[250001],p[250001];
bool cmp(pii x,pii y){return deg[x.fi]>deg[y.fi];}
bool cmp2(int x,int y){return deg[x]<deg[y];}
inline void del(int k){for(auto [to,v]:T[k])if(deg[to]<=dg)break;else a[to].add(v);}//删除无用点是把它的 $cost$ 即边权 $v$ 存到它旁边的所有有用点的堆里
inline void dfs(int k,int fa)
{
	int del=deg[k]-(vis[k]=dg);//需要删的边数
	while(a[k].size()>del)a[k].pop();//删的边一定越来越少，堆里存太多无用点也是没用的，只保留cost最小的
	for(auto [to,v]:T[k])if(to!=fa){if(deg[to]<=dg)break;else dfs(to,k);}//按度数排序后只DP有用点
	ins.clear(),ers.clear();
   //ins 存的有用点儿子的所有 cost，在最后把它删掉
  	//在找前 del 大的时候需要弹堆知道 siz=del，可能会弹出一些需要保留的无用点的 cost
   //ers 存的不小心被弹出的无用点的 cost，它还是有用的
	int sum=0;
	for(auto  [to,v]:T[k])
	{
		if(to==fa)continue;
		if(deg[to]<=dg)break;
		int val=f[to][0]+v-f[to][1];sum+=f[to][1];//val 即 cost
		if(val<=0)ans[dg]+=val,--del;
      //有时删边比留边优秀，而对于删边是没有限制的，可以把它连接的边全删了即把 del 减成负数，要加特判，否则 WA on test 4
		else a[k].add(val),ins.eb(val);
	}
	while(a[k].size()&&a[k].size()>del)ers.eb(a[k].top()),a[k].pop();//删 deg-x 条
	f[k][1]=sum+a[k].sum;
	while(a[k].size()&&a[k].size()>=del)ers.eb(a[k].top()),a[k].pop();//删 deg-x-1 条
	f[k][0]=sum+a[k].sum;
	for(int x:ers)a[k].add(x);
	for(int x:ins)a[k].del(x);
}
void mian()
{
	read(n);int x,y,z;
	for(int i=1;i<n;++i)read(x,y,z),ans[0]+=z,++deg[x],++deg[y],T[x].eb(mp(y,z)),T[y].eb(mp(x,z));
	for(int i=1;i<=n;++i)sort(T[i].begin(),T[i].end(),cmp),p[i]=i;//把边按 deg 排序保证复杂度
	sort(p+1,p+1+n,cmp2);//把点按 deg 排序保证复杂度
	for(dg=1,pos=1;dg<n;++dg)
	{
		while(pos<=n&&deg[p[pos]]<=dg)del(p[pos++]);//p_pos 变成无用点 
		if(pos>n)break;
		for(int j=pos;j<=n;++j)if(vis[p[j]]!=dg)dfs(p[j],0),ans[dg]+=f[p[j]][1];
	}
	for(int i=0;i<n;++i)write(ans[i]);
}
```

---

## 作者：zac2010 (赞：2)

一道很好口糊，但是实现细节颇多的题（时间复杂度容易假掉）。

我们先考虑固定 $x$ 的情况，用 $dp[u][0]$ 表示删除点 $u$ 到其父亲的连边的最小删边代价，用 $dp[u][1]$ 表示不删除点 $u$ 到其父亲的连边的最小删边代价。对于儿子 $v$ 有两种转移方式，第一种 $dp[v][0]+cost(u,v)$，第二种 $dp[v][1]$。发现直接转移要多加一维，和树上背包类似。但是复杂度会爆炸。故而我们选择一种带反悔的方法，一开始所有都选 $dp[v][1]$，再把一些 $1$ 的换成 $0$ 的。那么只要用堆 $dp[v][0]+cost(u,v)-dp[v][1]$ 即可。

之后我们考虑从小到大枚举 $x$，对于所有度数大于 $x$ 的点的联通块按上述简易版方法跑一遍树 $\text{DP}$。那些不用跑的点我们在枚举到的度数等于它时就已经把其删除，对所有它连出去的点的大根堆放入了它的权值了（注意当前进行树 $\text{DP}$ 时已经删除的点不用操作就满足，故而不会产生额外贡献）。

时间复杂度 $O(\text{度数})$，若要更具体的可以就代码分析。

[代码](https://codeforces.com/contest/1119/submission/201200448)。

---

## 作者：abruce (赞：2)

纪念一下自己独立切掉的第一个 *3400（  

首先我们考虑暴力怎么做，我们需要求的即每个点度数不超过 $k$，你要让选的边边权和最大。我们考虑从小到大枚举这个 $k$，然后我们设 $f_{i,0/1}$ 表示 $i$ 这个点在当前的度数限制下面有没有连父亲方向的边的最大代价。  
然后我们发现对于 $v\in son_u$，$f_{u,0}$ 在转移的时候最多只能选 $k$ 个 $f_{v,1}$，$f_{u,1}$ 同理，这是一个费用流模型，于是我们考虑带悔贪心。就每个点维护两个对顶堆（可以用 set 实现），分别表示 $f_{u,0/1}$ 的选中 $f_{v,1}$ 的集合和选中 $f_{v,0}$ 的集合，堆里面的代价是 $f_{v,1}-f_{v,0}$。每次扫整棵树就可以做到 $O(n^2\log n)$。  

接下来我们考虑这样一件事情，我们发现，如果在枚举 $k$ 的时候一个点 $deg_u< k$，那么这个限制相当于无用，我们很容易就能维护。然后发现 $\sum\limits_u deg_u=2n-2$，所以我们考虑如何每次只扫 $deg_u\ge k$ 的这些点。我们设 $deg_u\ge k$ 的 $u$ 为黑点，其余为白点。假设我们现在已经维护好黑点 $u$ 子树内的信息。首先我们需要进行反悔贪心的扩容和反悔操作。首先我们把那些选中 $f_{v,1}$ 但是堆中权值 $<0$ 踢出，然后尝试对选中 $f_{v,0}$ 的进行扩容（注意不能扩容进去一个权值 $<0$ 的）。然后是反悔，我们把选中 $f_{v,1}$ 的权值最小值和选中 $f_{v,0}$ 的权值最大值进行比较，如果小就交换。  
现在我们需要往上爬进行更新。假设我们找到了这个点往上走，走到第一个父亲是黑点的点（或者根），设其为 $tp$，这个可以并查集维护。由于 $u$ 到 $tp$ 中间没有任何限制，我们可以直接更新 $tp$ 的 $f$ 值，然后再更新 $tp$ 的父亲 $v$ 的集合。于是这题就做完了，时间复杂度 $O(n\log n)$。  
```cpp
#include<bits/stdc++.h>
#define fi first
#define sc second
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef set<pi>::iterator iter;
typedef vector<int>::iterator ite;
const int maxn=2.5e5+5;
struct edge {
	int next,to,v;
} e[maxn*2];
int h[maxn],cnt,n,deg[maxn],p[maxn],pos,fa[maxn],ff[maxn],b[maxn];
ll f[maxn][2],lf[maxn][2],ans[maxn],sum;
set<pi> s[maxn][2],d[maxn][2];
bool book[maxn][2];
vector<int> v;
void addedge(int x,int y,int z) {
	e[++cnt].next=h[x],e[cnt].to=y,e[cnt].v=z,h[x]=cnt;
}
int getf(int x) {
	return fa[x]==x?x:fa[x]=getf(fa[x]);
}
void dfs(int u,int fa) {
	p[u]=++pos,ff[u]=fa;
	for(int i=h[u]; i; i=e[i].next) {
		int v=e[i].to;
		if(v==fa)continue;
		f[v][1]=e[i].v,dfs(v,u),d[u][0].insert(pi(e[i].v,v)),d[u][1].insert(pi(e[i].v,v));
	}
}
bool cmp1(int x,int y) {
	return p[x]>p[y];
}
bool cmp2(int x,int y) {
	return deg[x]>deg[y];
}
int main() {
	int x,y,z;
	scanf("%d",&n);
	for(int i=1; i<n; i++) {
		scanf("%d%d%d",&x,&y,&z),deg[x]++,deg[y]++;
		addedge(x,y,z),addedge(y,x,z),sum+=z;
	}
	for(int i=1; i<=n; i++)b[i]=fa[i]=i;
	sort(b+1,b+n+1,cmp2),dfs(1,0);
	printf("%lld ",sum);
	for(int k=1; k<n; k++) {
		v.clear();
		for(int i=1; i<=n&&deg[b[i]]>=k; i++)v.push_back(b[i]);
		sort(v.begin(),v.end(),cmp1);
		for(ite it=v.begin(); it!=v.end(); it++)lf[*it][0]=f[*it][0],lf[*it][1]=f[*it][1];
		for(ite it=v.begin(); it!=v.end(); it++) {
			int u=*it,tp=getf(u);
			if(deg[tp]<k)lf[tp][0]=f[tp][0],lf[tp][1]=f[tp][1];
			pi x,y;
			for(int w=0; w<=1; w++) {
				while(!s[u][w].empty()&&(x=*s[u][w].begin()).fi<0)s[u][w].erase(x),f[u][w]-=x.fi,book[x.sc][w]=0,d[u][w].insert(x);
				while(s[u][w].size()<k-w&&!d[u][w].empty()&&(x=*d[u][w].rbegin()).fi>0)d[u][w].erase(x),f[u][w]+=x.fi,book[x.sc][w]=1,s[u][w].insert(x);//扩容
				while(!d[u][w].empty()&&!s[u][w].empty()&&s[u][w].begin()->fi<d[u][w].rbegin()->fi) {
					x=*s[u][w].begin(),s[u][w].erase(x);
					y=*d[u][w].rbegin(),d[u][w].erase(y);
					f[u][w]+=y.fi-x.fi,book[y.sc][w]=1,book[x.sc][w]=0,s[u][w].insert(y),d[u][w].insert(x);
				}//反悔
			}
			ll val;
			if(tp!=u)val=max(f[u][1],f[u][0])-max(lf[u][1],lf[u][0]),f[tp][0]+=val,f[tp][1]+=val;//更新f_tp
			if(tp!=1) {
				int v=ff[tp];
				for(int w=0; w<=1; w++)
					if(book[tp][w])s[v][w].erase(pi(lf[tp][1]-lf[tp][0],tp)),s[v][w].insert(pi(f[tp][1]-f[tp][0],tp)),f[v][w]+=f[tp][1]-lf[tp][1];
					else d[v][w].erase(pi(lf[tp][1]-lf[tp][0],tp)),d[v][w].insert(pi(f[tp][1]-f[tp][0],tp)),f[v][w]+=f[tp][0]-lf[tp][0];//更新f_v
			}
			if(deg[u]==k) {
				for(int i=h[u]; i; i=e[i].next) {
					int v=e[i].to;
					if(v==ff[u])continue;
					fa[v]=fa[u];
				}
			}//更新tp
		}
		printf("%lld ",sum-f[1][0]);
	}
	return 0;
}
```

---

## 作者：i207M (赞：2)

~~因为各种zz错误，WA了好几次~~

~~这道题卡复杂度卡的很严格，稍有不注意就可能变成$O(n^2)$~~

考虑我们如何$O(n\log n)$算出$\lim=d$的答案？我们设$dp[x][0/1]$表示使x的度数满足限制，且x与父亲的边否/是断掉的最小代价。

那么我们转移是，把$dp[v][1]+w-dp[v][0]$放在set中，取前$deg[x]-\lim$小的。

然后如何对每个$\lim$算出答案，做法非常神仙：

我们从小到大考虑，如果$deg[x]\le \lim$，那么这个点无论如何都满足要求，我们可以直接把$w$放到$v$的set里。

删除这些点，剩下若干联通块。我们对每个联通块做一遍DP即可，这样每个点会被遍历$deg$次，总复杂度也就是$O(n\log n)$

一些注意事项：

1. 显然我们每次只能遍历和一个点相邻的度数比它大的点，所以要把边表sort一遍

2. 看代码里的WARN，如果你和我写的一样，是set暴力删除多余的数的写法，那么要把set里多余的，不可能成为最优解的数删掉，否则复杂度会变成$\sum deg_i^2$

```cpp
#define N 250005
int n;
vector<pii>E[N];
LL ans;
vector<int>du[N];
LL sum[N];
multiset<LL> S[N];
il void ins(int x,int v)
{
	S[x].insert(v),sum[x]+=v;
}
il void del(int x,int v)
{
	S[x].erase(S[x].find(v)),sum[x]-=v;
}
il void Del(int x,int siz)
{
	while(Size(S[x])>siz) del(x,*S[x].rbegin());
}
il void Del(int x,int siz,vector<int> &vec)
{
	while(Size(S[x])>siz) vec.pb(*S[x].rbegin()),del(x,*S[x].rbegin());
}
bool vis[N];
int Lim;
int p[N];
LL dp[N][2];
void dfs(int x)
{
	int m=Size(E[x])-Lim; vis[x]=1;
	Del(x,max(0,m)); // WARN this!!!
	LL tot=0;
	vector<int> a,b;
	while(p[x]<Size(E[x])&&Size(E[E[x][p[x]].fi])<=Lim) ++p[x];
	for(ri i=p[x]; i<Size(E[x]); ++i)
	{
		int v=E[x][i].fi,w=E[x][i].se;
		if(vis[v]) continue;
		dfs(v);
		if(dp[v][1]+w<=dp[v][0]) --m,tot+=dp[v][1]+w;
		else
		{
			tot+=dp[v][0];
			LL t=dp[v][1]+w-dp[v][0];
			a.pb(t),ins(x,t);
		}
	}
	Del(x,max(0,m),b);
	dp[x][0]=tot+sum[x];
	Del(x,max(0,m-1),b);
	dp[x][1]=tot+sum[x];
	while(!b.empty()) ins(x,b.back()),b.pop_back();
	while(!a.empty()) del(x,a.back()),a.pop_back();
}
vector<int>hv[N];
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("ot.out","w",stdout);
#endif
	in(n);
	for(ri i=1,a,b,c; i<n; ++i)
	{
		in(a,b,c); ans+=c;
		E[a].pb(mp(b,c)),E[b].pb(mp(a,c));
	}
	out(ans,' ');
	for(ri i=1; i<=n; ++i) sort(E[i].begin(),E[i].end(),[](const pii &a,const pii &b) {return Size(E[a.fi])<Size(E[b.fi]);});
	for(ri i=1; i<=n; ++i) du[Size(E[ i])].pb(i);
	for(ri i=1; i<n; ++i)
		for(solid v:du[i]) for(ri j=1; j<i; ++j) hv[j].pb(v);
	for(Lim=1; Lim<n; ++Lim)
	{
		for(solid u:du[Lim])
		{
			vis[u]=1;
			for(solid it:E[u])
			{
				int v=it.fi,w=it.se;
				if(vis[v]) continue;
				ins(v,w);
			}
		}
		ans=0;
		for(solid v:hv[Lim]) // WARN this!!!
			if(!vis[v])
			{
				dfs(v);
				ans+=dp[v][0];
			}
		out(ans,' ');
		for(solid v:hv[Lim]) vis[v]=0;
	}
	return 0;
}
```


---

## 作者：JK_LOVER (赞：1)

# 题意
有一个 $N$ 个结点的树，每条边有边权，结点度数就是与之相连的边数量。对于 $0≤x<N$ ，删掉一些边使每个结点的度数不大于 $x$ ，求出删掉的边的权值和最小值。
# 分析
## 简化问题
求解 $x = D$ 时的问题。考虑 $dp$ ，定义 $f_{i,0/1}$ 为，结点 $i$ 为根子树满足 $\forall d_{son_i}\le D$ ，且与父亲的边是否断掉的最小代价。那么对于一个度数大于 $D$ 的节点，如果不断父亲的边，我们就要选择 $d_i-D$ 个儿子断掉，如果断父亲的边则选择 $d_i-D-1$ 个儿子。那么贪心的考虑哪些儿子是最优的。我们 $f_{son_i,1}-E_{u,son_i}+f_{son_i,0} \ge 0$ 的儿子的值放在一个平衡树中，对于小于 $0$ 的，直接加 $f_{son_i,1}+E_{u,son_i}$ 。然后贪心选取前几个就好了。时间复杂度为 $O(n^2\log n)$ 。 
## 原问题 
考虑由小到大枚举 $D$ 。如果一个节点的度数已经小于或者等于 $D$ ，那么这个节点再也不会在后面的决策中考虑到了。那么只需要在去掉这个节点的森林中每个联通块做一次 $dp$ 。那么每个节点考虑的次数为 $d_i$ ，而 $\sum_i^n d_i = 2n-2$ ，对于一个联通块的 $dp$ 一定不会从一个节点转移到一个度数小于等于 $D$ 的节点，那么可以对边和节点度数排序降低复杂度。所以加上平衡树的复杂度，总的复杂度为 $O(n\log n)$ 。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define P pair<LL,LL>
#define It multiset<LL>::iterator
const int N = 250005;
LL ans,sum[N],f[N][2];
vector<P> G[N<<1]; 
P d[N];
multiset<LL> H[N];
void insert(int x,LL val) {
	H[x].insert(val);
}
void erase(LL x,LL val) {
	It it = H[x].lower_bound(val);H[x].erase(it);
}
bool vis[N];
LL Max,du[N],n;
void die(LL x) {
	for(LL i = 0;i < G[x].size();i++) {
		LL y = G[x][i].second;
		if(du[y] <= Max) break;
		insert(y,G[x][i].first);sum[y] += G[x][i].first;
	}
}
bool cmp(P a,P b){
	return du[a.second] > du[b.second];
}
vector<LL> ins,del;
void dfs(int x,int fa) {
	vis[x] = 1;
	LL m = du[x] - Max;
	while(H[x].size() && H[x].size() > m) {
		It it = H[x].end();--it;sum[x]-= *it;H[x].erase(it);
	} 
	for(LL i = 0;i < G[x].size();i++) {
		LL y = G[x][i].second;
		if(y == fa) continue;
		if(du[y] <= Max) break;
		dfs(y,x); 
	}
	ins.clear();del.clear();
	LL Ans = 0;
	for(int i = 0;i < G[x].size();i++) {
		int y = G[x][i].second;
		if(y == fa) continue;
		if(du[y] <= Max) break;
		LL val = f[y][1] + G[x][i].first - f[y][0];
		if(val <= 0) {Ans += f[y][1] + G[x][i].first;m--;continue;}
		insert(x,val);del.push_back(val);
		Ans += f[y][0];sum[x] += val;
	}
	while(H[x].size() && H[x].size() > m) {
		It it = H[x].end();--it;
		sum[x] -= *it,ins.push_back(*it),H[x].erase(it);
	} 
	f[x][0] = Ans + sum[x];
	while(H[x].size() && H[x].size() > m-1) {
		It it = H[x].end();--it;
		sum[x] -= *it,ins.push_back(*it),H[x].erase(it);
	} 
	f[x][1] = Ans + sum[x];
	for(LL i = 0;i < ins.size();i++) insert(x,ins[i]),sum[x] += ins[i];
	for(LL i = 0;i < del.size();i++) erase(x,del[i]),sum[x] -= del[i];
}
int main() {
	scanf("%lld",&n);	
	for(int i = 1,a,b,c;i < n;i++) {
		scanf("%lld%lld%lld",&a,&b,&c);ans += c;
		G[a].push_back(P(c,b));
		G[b].push_back(P(c,a));
		du[a]++;du[b]++;
	}
	for(int i = 1;i <= n;i++) {
		d[i] = P(du[i],i);
		sort(G[i].begin(),G[i].end(),cmp);
	}
	sort(d+1,d+1+n);
	printf("%lld ",ans);
	LL pos = 1;
	for(Max = 1;Max < n;Max++) {
		while(pos <= n && d[pos].first <= Max) die(d[pos].second),++pos;
		ans = 0;memset(vis,0,sizeof(vis));
		for(int j = pos;j <= n;j++) {
			if(vis[d[j].second]) continue;
			dfs(d[j].second,0);
			ans += f[d[j].second][0];
		}
		printf("%lld ",ans);
	}
	printf("\n");
	return 0;
}


```


---

## 作者：UKE_Automation (赞：0)

### CF1119F Niyaz and Small Degrees / P7600 [APIO2021] 封闭道路

[$\text{CF Link}$](https://codeforces.com/problemset/problem/1119/F)，[$\text{Luogu Link}$](https://www.luogu.com.cn/problem/P7600)

首先先来看对于单独的固定的 $x$ 如何求答案，显然考虑树形 dp，设 $dp(i,0/1)$ 表示钦定点 $i$ 与父亲的连边不删除或删除时，让 $i$ 子树内合法的最小代价。转移是比较好想的，对于一个儿子 $v$，有两种决策：该边不删除，代价为 $dp(v,0)$；该边删除，代价为 $dp(v,1)+w$。为了让 $i$ 也满足条件，显然删除的边的数量至少有 $deg_i-x$，但是对于每个儿子只取最优解并不一定能满足这个要求。因此对于所有取到不删除的点，把代价之差 $dp(v,1)+w-dp(v,0)$ 扔到一个堆里，然后取最小的加到答案中即可。

这样做单次复杂度为 $O(n^2\log n)$，无法通过。考虑进一步观察性质，容易发现对于一个 $x$，$deg_i\le x$ 的点是完全不用重新 dp 的，称这样的点为无用点。将无用点从树中删去后就形成了若干连通块，每次只需要对连通块 dp 即可。此时再看复杂度，对于一个点 $i$，它会被处理 $deg_i$ 次，所以总复杂度是 $O(\sum deg_i)=O(n)$ 的，那么这个做法是有前途的。

考虑对于以有用点为根进行 dp，然后将无用点视为一个叶子节点，此时这个节点不删除的代价为 $0$，删除的代价就是边权 $w$。按道理来讲此时直接按照上述过程实现就行了，不过实际上不然。因为我们复杂度的正确性是建立在每一次只遍历有用点的基础上的，如果每次还要把无用点扔进堆复杂度是不正确的。

解决方法实际上也比较容易，无用点的贡献一定是不变的，所以对于每个点，其堆中含有的无用点贡献也是不变的。那么我们只需要在一个点变为无用点时向其周围的有用点的堆中加入贡献即可；同时对于每个点，如果把堆中无用点的贡献删掉了，我们也要重新加回来。这个用 `set` 实现会方便一点，或者用两个堆拼成可删堆实现，复杂度还是 $O(n\log n)$ 的。

但是还有最后一个问题：如果我们每一次把 `set` 中最小的 $deg_i-x$ 个暴力删除求和的话复杂度还是不对，会退化成 $O(\sum deg_i^2)$。考虑我们实际上是对 `set` 中一段前缀求和，可以转化为用总和减去一段后缀的和。而求后缀就给了我们操作空间；在最开始的时候，集合中应该只有无用点，我们先把它的大小压到 $deg_i-x$ 以内，然后加入有用点，此时要删到只剩 $deg_i-x$ 个点最多只用有用点个数步。这样的话这一部分的复杂度也变成了有用点的个数之和，总复杂度就是 $O(n\log n)$ 的了。

```cpp
#include <bits/stdc++.h>
#define il inline
#define int long long

using namespace std;

const int Maxn = 2.5e5 + 5;
const int Inf = 2e9;
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool flg = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	flg ? putchar('\n') : putchar(' ');
}

int n;
#define pii pair<int, int>
#define mk make_pair
#define fi first
#define se second
vector <pii> V[Maxn];
int deg[Maxn];
void add(int u, int v, int w) {
	deg[u]++, deg[v]++;
	V[u].push_back(mk(v, w)), V[v].push_back(mk(u, w));
}
int id[Maxn];

multiset <int> s[Maxn];
int f[Maxn][2], sum[Maxn]; 
int vis[Maxn];
void del(int x) {
	for(auto p : V[x]) {
		int to = p.fi, w = p.se;
		s[to].insert(w); sum[to] += w;
	}
}

vector <int> dl, is;
void dfs(int x, int fth, int lim) {
	int tar = deg[x] - lim; int res = 0;
	for(auto p : V[x]) {
		int to = p.fi;
		if(to == fth) continue;
		if(deg[to] <= lim) break;
		dfs(to, x, lim);
	}
	while(s[x].size() > tar) sum[x] -= *(--s[x].end()), s[x].erase(--s[x].end());
	res = sum[x]; vis[x] = 1;
	dl.clear(), is.clear();
	for(auto p : V[x]) {
		int to = p.fi, w = p.se;
		if(to == fth) continue;
		if(deg[to] <= lim) break;
		int v1 = f[to][1] + w, v2 = f[to][0];
		res += v1;
		if(v1 <= v2) tar--;
		else s[x].insert(v1 - v2), is.push_back(v1 - v2);
	}
	while(s[x].size() && (signed)s[x].size() > tar) {
		auto it = --s[x].end();
		dl.push_back(*it), res -= *it, s[x].erase(it); 
	}
	f[x][0] = res;
	while(s[x].size() && (signed)s[x].size() >= tar) {
		auto it = --s[x].end();
		dl.push_back(*it), res -= *it, s[x].erase(it); 
	}
	f[x][1] = res;
	for(auto i : dl) s[x].insert(i);
	for(auto i : is) s[x].erase(s[x].find(i));
}

signed main() {
	read(n); int sum = 0;
	for(int i = 1, u, v, w; i < n; i++) {
		read(u), read(v), read(w);
		add(u, v, w); sum += w;
	}
	for(int i = 1; i <= n; i++) id[i] = i, sort(V[i].begin(), V[i].end(), [](pii x, pii y){return deg[x.fi] > deg[y.fi];});
	sort(id + 1, id + n + 1, [](int x, int y){return deg[x] < deg[y];}); int pos = 1;
	write(sum, 0);
	for(int i = 1; i < n; i++) {
		while(pos <= n && deg[id[pos]] <= i) del(id[pos]), pos++;
		int ans = 0;
		for(int j = pos; j <= n; j++) {
			int x = id[j];
			if(!vis[x]) {
				dfs(x, 0, i), ans += f[x][0];
			}
		}
		write(ans, 0);
		for(int j = pos; j <= n; j++) vis[id[j]] = 0;
	}	
	return 0;
} 
```

---

## 作者：123456xwd (赞：0)

先考虑固定 $x$ 的情况，考虑一下树形 dp。

设 $dp_{u,0/1}$ 表示考虑了以 $u$ 为根的子树的最小代价，$0$ 表示删除 $(u,fa_u)$，反之表示保留。

我们发现，对于一个点，设 $deg_u$ 表示他的度数，则对于 $dp_{u,0}$，他至少要删除 $deg_u-x-1$ 条边；对于 $dp_{u,1}$，他至少要删除 $deg_u-x$ 条边。

我们先假设他都不删除边，设 $dp_{u,0/1}=\sum_{v\in son_u} dp_{v,1}$。

当然，我们是不可能不删除的，考虑维护一个集合 $S$，$S$ 集合内存的是对于 $v\in son_u$，所有的 $dp_{v,0}+w-dp_{v,1}$，其中 $w$ 是 $(u,v)$ 的边权。

我们分别取最小的 $deg_u-x-1$ 和 $deg_u-x$ 个元素贡献给 $dp_{u,0}$ 和 $dp_{u,1}$ 即可。（注意，若其中还有元素为负数，可以都放进去）。

这样子我们就可以 $\mathcal{O}(n^2\log n)$ 求解出来对于单个 $x$ 了，先枚举 $x$，现在考虑如何优化这一过程。

首先，我们发现，对于 $deg_u\le x$ 的点，我们考虑他就没有意义了，设其为无用点，反之为有用点。

我们很明显只用在若干个由有用点构成的连通块上面考虑，剩下的过程同上。

但是，我们的无用点还是对有用点有贡献的，就是他同有用点之间的连边的边权，我们考虑对于每一个点维护一个堆，把所有和他相连的无用点的边权都放进去，然后对于上面说的 dp 过程，我们也可以利用这个堆，不过需要这个堆支持删除元素。

我们只需要用两个堆就可以解决了，详见代码。

分析一下时间复杂度，点会被遍历 $\sum deg_u=2n-2=\mathcal{O}(n)$。

然后计算那个堆的时间复杂度，每个点会在他变为无用点的时候给其相邻的点贡献 $\log n$ 的复杂度，也就是 $\sum deg_u\log n=\mathcal{O}(n\log n)$。

最后每个点在其变为无用点之前，每次会给其父亲贡献 $\log n$ 的复杂度，算下来也是 $\mathcal{O}(n\log n)$。

总的算下来就是 $\mathcal{O}(n\log n)$ 的。

```c++
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
#define p_b push_back
using namespace std;
static char buf[2000000],*p1=buf,*p2=buf,obuf[2000000],*p3=obuf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,2000000,stdin),p1==p2)?EOF:*p1++
//#define putchar(x) (p3-obuf<2000000)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
template<typename dy> dy abs(dy x){return x>0?x:-x;}
template<typename dy> dy max(dy x,dy y){return x>y?x:y;}
template<typename dy> dy min(dy x,dy y){return x<y?x:y;}
//template<typename dy> void swap(dy &x,dy &y){x^=y;y^=x;x^=y;}
template<typename dy>
void read(dy &x){
	x=0;int f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	x*=f;
}
template<typename dy>
void write(dy x){
	if(x<0){putchar('-');x=-x;}
	if(x>9) write(x/10);
	putchar(x%10+48);
}
void write(char x){putchar(x);}
void read(char *s){
	while((*s=getchar())==' '||*s=='\n');
	while((*++s=getchar())!=' '&&*s!='\n'&&*s!=EOF);
	*s=0;
}
template<typename dy,typename... Args> void read(dy &x,Args &...args){read(x);read(args...);}
template<typename dy,typename... Args> void write(dy x,Args ...args){write(x);write(args...);}

const int N=250000+5,INF=0x3f3f3f3f;
int du[N];
struct node{
	int fi,se;
	bool operator<(const node &y)const{
        return du[fi]>du[y.fi];
    }
};
vector<node> G[N];
bool cmp1(int x,int y){return du[x]<du[y];}
ll ans;
int deg;
struct Heap{
	priority_queue<int> q1,q2;ll sum;
	void clean(){while(!q1.empty()&&!q2.empty()&&q1.top()==q2.top()) q1.pop(),q2.pop();}
	void insert(int x){q1.push(x);sum+=x;}
	void erase(int x){q2.push(x);sum-=x;}
	int top(){clean();return q1.top();}
	void pop(){sum-=top();q1.pop();}
	int size(){return q1.size()-q2.size();}
}H[N];
void work(int u){
	for(auto i : G[u]){
		if(du[i.fi]<=deg) break;
		H[i.fi].insert(i.se);
	}
}
int vis[N],n,p[N];
ll dp[N][2];
vector<int> A,B;//多加入的,多删除的
void dfs(int u,int fa){
	vis[u]=vis[fa];
	for(auto i : G[u]){
		if(du[i.fi]<=deg) break;
		if(i.fi!=fa) dfs(i.fi,u);	
	}
	int v,w,need=du[u]-deg;
	ll sum=0;
	A.clear(),B.clear();
	while(H[u].size()>need) H[u].pop();//删除一定无用的
	for(auto i : G[u]){
		if(du[i.fi]<=deg) break;
		if(i.fi==fa) continue;
		v=i.fi,w=i.se;
		if(dp[v][0]+w<=dp[v][1]) need--,sum+=dp[v][0]+w;
		else{
			A.p_b(dp[v][0]+w-dp[v][1]);
			H[u].insert(dp[v][0]+w-dp[v][1]);
			sum+=dp[v][1];
		}
	}
	dp[u][0]=dp[u][1]=sum;
	while(H[u].size()&&H[u].size()>need) B.p_b(H[u].top()),H[u].pop();
	dp[u][1]+=H[u].sum;
	while(H[u].size()&&H[u].size()>need-1) B.p_b(H[u].top()),H[u].pop();
	dp[u][0]+=H[u].sum;
	for(auto x : B) H[u].insert(x);
	for(auto x : A) H[u].erase(x);
}

int main(){
	read(n);
	int u,v,w;
	for(int i=1;i<n;i++){
		read(u,v,w);
		G[u].p_b({v,w});
		G[v].p_b({u,w});
		du[u]++,du[v]++;
		p[i]=i;
		ans+=w;
	}
	p[n]=n;
	sort(p+1,p+1+n,cmp1);
	for(int i=1;i<=n;i++) sort(G[i].begin(),G[i].end());
	write(ans,' ');
	for(int i=1,j=1;i<n;i++){
		vis[0]=deg=i;ans=0;
		while(j<=n&&du[p[j]]<=i) work(p[j]),j++;
		for(int k=j;k<=n;k++){
			if(vis[p[k]]==i) continue;
			dfs(p[k],0);
			ans+=dp[p[k]][1];
		}
		write(ans,' ');
	}
	//fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```

---

## 作者：orz_z (赞：0)



先暴力贪心。

设 $f_{u,0/1}$ 分别表示是否删除 $u$ 和父亲之间的边，**子树内**的最小代价。

我们要满足的就是 $u$ 被删除的边数 $k$ 满足 $du_u-k \le x$。

这下每个 $v$，不是选 $w+f_{v,1}$ 就要选 $f_{v,0}$，也就是二选一，且尽量删边。

对于所有儿子 $v$，如果 $f_{v,1}+w_{u,v}\leq f_{v,0}$，那么我们选它是不劣的。

如果我们选了这些后，度数还是无法满足条件。

将未选边按照 $f_{v,1}+w_{u,v}-f_{v,0}$ 排序，从最小开始选就行了。

简化一点，选择前 $du_u-x$ 小的 $f_{v,0}+w_{u,v}$，其他选择 $\min(f_{v,0}+w_{u,v},f_{v,1})$。

$f_{u,1}$ 同理。

发现当 $du_u \leq x$ 时，就是选择了子树内的最优方案，且无需满足度数限制，且 $f_{u,0}$ 和 $f_{u,1}$ 对父亲的影响只有 $w_{u,v}$。

这启发我们，如果我们的可以做到每次只 `dp` 有用的点，那么复杂度是 $\mathcal O(\sum_x \sum_i [du_i>x])=\mathcal O(\sum du_i)=\mathcal O(n)$。

删掉无用点后，将我们要用到的边权记到有用的点上。

**为什么，无用点和无用点之间的边是肯定满足的，那么无用点只会对有用点产生贡献，所以每次相当于将无用点看成联通块无用的叶子。**

考虑有用点和无用点之间的决策，能产生影响的就只有 $w_{u,v}$。

---

## 作者：SunsetSamsara (赞：0)

## CF1119F

### 题意

给定一棵带权树。对于从 $1$ 到 $n$ 的所有 $x$，删除一些边使所有点度数都不超过 $x$，求最小化删除的边的权值和。

### 做法

思维，dp，平衡树 / Trie

### 做法

记 $f_{u,0/1}$ 表示 $u$ 子树内符合要求并且点 $u$ 向父亲的连边有/没有被删除所需的最小权值和。显然 $f_{u,1}\ge f_{u,0}$。

考虑断掉一条边 $(u, v, w)$ 的代价，即 $w - (f_{v, 1} - f_{v, 0})$。

那么对于 $f_{u,1}$，先不考虑 $u$ 的限制，完全不删边的代价是 $\sum\limits_{v\in s_u}f_{v,1}$。

接下来先把 $w - (f_{v, 1} - f_{v, 0}) \le 0$ 的 $v$ 都删除向 $u$ 的连边，并将 $w - (f_{v, 1} - f_{v, 0})$ 累计到代价上。

设上一步删除了 $p$ 条边，那么还需要删除 $d - x - p$ 条边，其中 $d$ 是 $u$ 的度数（包括连向父亲的边）。既然是 $f_{u,1}$，那么不需要删除向父亲的连边，再用平衡树 / Trie 树选出子节点中前 $d - x - p$ 小的 $w - (f_{v, 1} - f_{v, 0})$ 的和累计上答案。

$f_{u,0}$ 同理，改变的就是删除的边数变为 $d - x - p - 1$。

注意到需要进行 dp 的关键点都是度数大于 $x$ 的点。于是从大往小考虑 $x$，每次只考虑合法的点，一开始对于所有点 $u$ 将所有向子节点的边 $(u, v, w)$ 的权值 $w$ 加入以 $u$ 为根的平衡树 / Trie 树中，每次加入新的合法点时将其向其他合法点的连边 $(u, v, w)$ 从以 $u$ 和以 $v$ 为根的平衡树/ Trie 树中删除即可。

最终复杂度 $O(\sum\limits_{x=1}^{n-1}\sum\limits_{u}[x\le \operatorname{deg}_ u]) = O(\sum\limits_{u}\sum\limits_{x=1}^{n-1}[x\le \operatorname{deg}_ u]) = O(\sum\limits_{u}\operatorname{deg}_ u) = O(n)$

### 代码

```cpp
#pragma GCC optimize("O2")
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
typedef long long lld;
using namespace std;
const int N = 250010;
namespace Trie {
	struct node {
		int ch[2];
		lld sum, val, cnt;
	} tr[N * 30];
	int tot;
	inline void insert(int &rt, lld val, lld cnt) {
		if (!rt) rt = ++ tot;
		int p = rt;
		for (int i = 25, b; ~i; -- i) {
			tr[p].sum += val * cnt;
			tr[p].cnt += cnt;
			b = (val >> i) & 1;
			int &v = tr[p].ch[b];
			if (!v) v = ++ tot;
			p = v;
		}
		tr[p].val = val;
		tr[p].sum += val * cnt;
		tr[p].cnt += cnt;
	}
	inline lld query(int rt, lld k) {
		int p = rt;
		lld ret = 0;
		for (int i = 25; ~i; -- i) {
			if (tr[p].cnt < k) return 0x3f3f3f3f3f3f3f3fll;
			if (!k) break;
			if (tr[tr[p].ch[0]].cnt > k) p = tr[p].ch[0];
			else {
				k -= tr[tr[p].ch[0]].cnt;
				ret += tr[tr[p].ch[0]].sum;
				p = tr[p].ch[1];
			}
		}
		if (tr[p].cnt < k) return 0x3f3f3f3f3f3f3f3fll;
		ret += tr[p].val * k;
		return ret;
	}
}
int n;
vector<pair<int, lld> > G[N], G2[N];
int srt[N];
int rt[N];
lld ans[N];
int deg[N];
vector<int> a;
bool ext[N];
lld f[N][2];
bool vis[N];
inline bool cmp(int x, int y) {
	return deg[x] > deg[y];
}
int t;
inline void dfs(int u) {
	vis[u] = 1;
	f[u][0] = f[u][1] = 0;
	vector<lld> vec;
	int cnt = 0;
	lld sum = 0;
	for (pair<int, lld> &e : G2[u]) {
		int v = e.first;
		lld w = e.second;
		if (!vis[v]) {
			dfs(v);
			f[v][1] += w;
			sum += f[v][0];
			if (f[v][1] <= f[v][0]) ++ cnt, sum += f[v][1] - f[v][0];
			else vec.push_back(f[v][1] - f[v][0]);
		}
	}
	sort(vec.begin(), vec.end());
	int k = deg[u] - cnt - t;
	f[u][0] = Trie::query(rt[u], k);
	lld res = 0;
	for (lld v : vec) {
		if (!k) break;
		-- k;
		res += v;
		f[u][0] = min(f[u][0], res + Trie::query(rt[u], k));
	}
	f[u][0] += sum;
	k = deg[u] - cnt - t - 1;
	f[u][1] = Trie::query(rt[u], k);
	res = 0;
	for (lld v : vec) {
		if (!k) break;
		-- k;
		res += v;
		f[u][1] = min(f[u][1], res + Trie::query(rt[u], k));
	}
	f[u][1] += sum;
}
int main() {
	scanf("%d", &n);
	for (int i = 1, u, v, w; i < n; ++ i) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
		ans[0] += w;
		Trie::insert(rt[u], w, 1);
		Trie::insert(rt[v], w, 1);
		++ deg[u];
		++ deg[v];
	}
	for (int i = 1; i <= n; ++ i) srt[i] = i;
	sort(srt + 1, srt + n + 1, cmp);
	int p = 1;
	for (t = n - 1; t; -- t) {
		for (; p && deg[srt[p]] > t; ++ p) {
			int u = srt[p];
			a.push_back(u);
			ext[u] = 1;
			for (pair<int, lld> &e : G[u])
				if (ext[e.first]) {
					int v = e.first;
					Trie::insert(rt[u], e.second, -1);
					Trie::insert(rt[v], e.second, -1);
					G2[u].push_back(make_pair(v, e.second));
					G2[v].push_back(make_pair(u, e.second));
				}
		}
		for (int u : a) vis[u] = 0;
		for (int u : a) if (!vis[u]) dfs(u), ans[t] += f[u][0];
	}
	for (int i = 0; i < n; ++ i) printf("%lld ", ans[i]);
}
```

---

