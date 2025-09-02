# [JRKSJ R8] C0mp0nents

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/m71eooc6.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/b626ra6r.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/it3ulcpz.png)

## 题目描述

小 I 有一张 $n$ 个点、$m$ 条边的无向图，保证图无重边、无自环。初始时第 $i$ 个点的点权 $a_i = i$。小 I 有一个额外的常量 $k$。

小 R 可以进行很多很多次操作。每次操作，她选择图上两个相邻的节点 $x, y$ 满足 $\lvert a_x - a_y \rvert = k$，随后小 I 会将 $a_x$ 设为 $a_y$。

对每个 $1 \leq s \leq n$，**如果在过程中不修改 $\bm{a_x = s}$ 的节点 $\bm x$ 的权值**，小 I 想知道：若干次操作后，图上最多有多少个点满足 $a_i = s$。

## 说明/提示

### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 0（0 pts）：样例；
- Subtask 1（5 pts）：$n \leq 200$，$m \leq 400$；
- Subtask 2（20 pts）：$n \leq 5000$，$m \leq 10^4$；
- Subtask 3（25 pts）：$n \leq 10^5$，$m \leq 3\times 10^5$；
- Subtask 4（50 pts）：无特殊限制。

对于所有数据，满足 $1 \leq k \leq n \leq 4\times 10^5$，$1 \leq u, v \leq n$，$0 \leq m \leq 10^6$，保证图无重边、无自环。

## 样例 #1

### 输入

```
5 6 1
1 2
1 3
1 5
2 3
2 4
4 5```

### 输出

```
3 3 5 5 5
```

## 样例 #2

### 输入

```
8 10 1
1 3
1 4
1 5
2 3
2 7
3 6
4 6
5 8
6 7
7 8
```

### 输出

```
8 8 7 7 5 4 3 3
```

## 样例 #3

### 输入

```
14 19 2
1 3
1 4
1 9
2 5
2 14
3 7
4 5
4 6
4 7
4 8
5 6
5 11
6 8
7 9
8 10
8 12
9 10
10 11
11 12
```

### 输出

```
2 1 2 4 1 4 2 4 2 5 1 5 1 1
```

# 题解

## 作者：irris (赞：7)

## Preface

deleted。

## Solution

### $\mathcal O((n + m)\log n)$

不失一般性，$k = 1$，否则我们把点按照 $\bmod k$ 同余分成若干类，每一类是一个独立的问题。另注：我们需要忽视 $(u - v) \bmod k \neq 0$ 的所有边 $(u, v)$。

解决 $s = 1$。我们发现若初始权值为 $[1, i]$ 的所有点的最终权值都是 $1$，这要求每个初始权值为 $[1, i)$ 的点 $x$ 都与至少一个初始权值在 $(x, i]$ 内的点相连。我们显然可以 $\mathcal O(n)$ 解决。

解决 $s$ 是一般值的情况。考虑 $[l, r]$ 最终全是 $s$ 的充要条件是

- $[l, r]$ 联通；
- 每个 $(s, r)$ 与 $(s, r]$ 里更大的点直接有边；
- 每个 $(l, s)$ 与 $[l, s)$ 里更小的点直接有边。

忽视第一个条件，第二个条件我们对每个 $r$ 找到最大的 $s + 1$，这可以从小到大扫描 $r$，不断加入 $x$ 的贡献，用并查集维护连续段解决；第三个条件同理。

接下来我们对每个 $s$ 找到了如果第一个条件成立下的 $L = l_{\min}$ 和 $R = r_{\max}$，于是这些点被划分成了三个部分：$[L, s) [s, s] (s, R]$。

显然，如果 $[s, s]$ 与 $[L, s) (s, R]$ 中其中 $0$ 或 $2$ 个部分联通，我们可以简单计算最终连通块的大小；否则我们不妨设 $[s, s]$ 与 $[L, s)$ 联通而不与 $(s, R]$ 联通，但我们注意到这个时候最终连通块不一定仅仅是 $[L, s]$，也有可能是 $[L, s)$ 与 $(s, R]$ 内有边导致最终的最大连通块为 $[L, R]$。判断两个区间内的点是否有边可以离线后二维偏序解决。

于是时间复杂度为 $\mathcal O((n + m)\log n)$。

### $\mathcal O(n + m)$

我们线性计算上面的每个部分。

- 对于每个 $i$ 计算最大的 $R_i$ 满足 $[i, R_i)$ 的每个点 $x$ 都与 $(x, R_i]$ 间的一个点相连，对称同理

断言：$R_i = R_{i+1}$ 或 $R_i = i$，证明显然：若无 $R_i \leq R_{i+1}$ 则有矛盾；若 $R_i \in (i, R_{i+1})$ 依然有矛盾。那么枚举 $i$ 的出边即可。

- 对于若干个 $i$，判断 $[L_{i-1}, i)$ 与 $(i, R_{i+1}]$ 之间是否有边

对于一条边 $u, v (u < v)$，能够让 $L_{i-1} \leq u \leq i - 1$，$i + 1 \leq v \leq R_{i+1}$ 的点合法。由于 $L$，$R$ 的单调性，这可以转化为有某个 $[l, r]$ 使得 $i \in [l, r]$ 是合法的。这可以差分预处理。

于是时间复杂度为 $\mathcal O(n + m)$。

另一个线性做法：欢迎报名月赛讲评。

---

## 作者：Corzica (赞：4)

先把图按照对 $k$ 的余数拆分开来，显然，对 $k$ 余数不同的点相互之间不可能有贡献。

把拆分后的图的点权重新标为从 $1$ 开始的连续的一段，之后讨论在这样一张图中做 $k=1$ 的情况。

假设你有了一个 $s$，讨论如何计算答案。注意到每一个点的点权都是不重的，所以将一个点的点权转化为另一个点的点权代表着有一个值的消失。而所有满足 $a_x=s$ 的点又不能进行修改，所以你不会作出类似于把 $s+k$ 变为 $s+k+1$ 这样的事，因为 $s+k$ 这个值补不回来了，这些数降不回去。

所以，每个数都只会接近 $s$ 地改变，若一个值得区间 $[l,r]$ 最终都变成了 $s$，那么一定有：

- $[l,r]$ 联通。
- $(s,r)$ 中的每一个点要向至少一个比它大的且在 $[l,r]$  中的点连边。
- $(l,s)$ 中的每一个点要向至少一个比它小的且在 $[l,r]$  中的点连边。

考虑处理上面的三个部分。

第二和第三部分类似，对每一个点维护它能连到的距离它最小的比它大和比它小的点。

以第二部分为例。可以发现这个玩意真是单单又调调，每一个 $s$ 对应的右端点单调递增（因为限制严格减少）。相应的，我们倒序枚举 $s$，这个东西就会递减。倒序去计算它，如果当前的没有向比它大的点连边，或是连到的点超出了上一个点的右端点，把 $r$ 置为 $s$，一直处理下去即可。

最后再判断第一个条件，检查 $[l_s,s-1],s,[s+1,r_s]$ 相互之间是否有边即可。

最后的复杂度就是 $O(n+m)$。

---

## 作者：Lyrella (赞：3)

# 题解

困难题。

考虑所有 $i\equiv x\pmod k$ 才可能互相贡献答案，于是我们将点分类并对每一类按照除以 $k$ 的商排序，然后忽略无意义的边。接下来我们对每一类分别计算答案。考虑所有数同时除以 $k$ 之后就变成了若干个连续且公差为一的等差数列，所以我们只考虑 $k=1$ 的情况。

假设我们现在要求 $s=1$ 时的答案。我们发现如果 $[1,i]$ 的所有点都能变成 $1$ 说明每个 $x\in[1,i)$ 都向后至少连了一条边到 $(x,i]$，原因是如果我们想让 $i$ 变成 $1$，就要经历 $i\rightarrow i-1\rightarrow\dots\rightarrow1$ 的过程。所以 $i$ 一定和 $i-1$ 有连边；$i-2$ 一定有边连到 $\{i-1,i\}$ 中，以此类推。

拓展到一般情况，如果 $[l,r]$ 能够变成 $s$，那么：

- 每个 $x\in(s,r)$ 都向后至少连了一条边到 $(x,r]$；
- 每个 $x\in(l,s)$ 都向前至少连了一条边到 $[l,x)$；
- $[l,r]$ 是一个连通块。

我们可以先处理前两个限制，对于最后一个判断是否有边从 $s$ 的前面连向后面即可。现在具体讲一下怎么处理前面两个东西，首先可以发现这两个东西本质相同所以只考虑第一个的处理，第二个类比即可。

现在说第一个限制的处理方式。因为我们的 $s$ 在不停地向右移动，所以对区间的限制在不断变少，所以区间的右端点在单调递增。这启发我们线性处理。这里有一个比较显然但是很关键的性质，就是假设对 $i$ 满足条件的最大 $r$ 记做 $rp_i$，有 $rp_i=rp_{i+1}$ 或 $i$。证明考虑如果当前点 $i$ 向区间 $(i,rp_{i+1}]$ 存在连边则有 $rp_i=rp_{i+1}$，否则就是 $rp_i=i$。于是我们就可以倒着扫一遍序列即可。

最后我们还需要判断区间之间是否有边。我们转换视角，考虑**每条边对哪一段区间有贡献**。对于一条边 $(u,v),u<v$，如果存在 $i$ 满足 $lp_i\le u<i<v\le rp_i$ 即合法。考虑到 $lp_i,rp_i$ 都具有单调性所以合法的点一定是一段连续的区间。现在考虑求这段区间。因为二维的限制不好处理所以我们把它变成两个一维限制扫一遍即可。最后处理出对哪些区间有贡献后需要做一些区间加以及单点查，这个可以差分实现。

# 代码

```cpp
void solve(int rr){
    tot = n / k + (n % k >= rr); lp[1] = 1; rp[tot] = tot; sf[0] = 0; pr[tot + 1] = tot + 1;
    for(int i = 1; i <= tot; ++i)pos[a[i] = i * k - k + rr] = i, d[i] = 0;
    for(int u = 1; u <= tot; ++u){
        l[u] = 0, r[u] = tot + 1;
        for(int i = hd[a[u]], v; i; i = e[i].nxt)if((v = pos[e[i].to]) < u)l[u] = max(l[u], v); else r[u] = min(r[u], v);
    }
    for(int i = 2; i <= tot; ++i){lp[i] = lp[i - 1]; if(l[i - 1] < lp[i] and lp[i] ^ i - 1)lp[i] = i - 1;}
    for(int i = tot - 1; i; --i){rp[i] = rp[i + 1]; if(rp[i] < r[i + 1] and rp[i] ^ i + 1)rp[i] = i + 1;}
    for(int i = 1; i <= tot; ++i)for(sf[i] = sf[i - 1]; sf[i] < tot and lp[sf[i] + 1] <= i; ++sf[i]);
    for(int i = tot; i; --i)for(pr[i] = pr[i + 1]; pr[i] > 1 and i <= rp[pr[i] - 1]; --pr[i]);

    for(int u = 1; u <= tot; ++u)for(int i = hd[a[u]], v; i; i = e[i].nxt)if(u < (v = pos[e[i].to])){
        int bg = max(u + 1, pr[v]), ed = min(v - 1, sf[u]);
        if(bg <= ed)++d[bg], --d[ed + 1];
    }
    for(int i = 1; i <= tot; ++i){
        d[i] += d[i - 1];
        if(l[i] < lp[i] and rp[i] < r[i])lp[i] = rp[i] = i;
        else if(! d[i])if(l[i] < lp[i])lp[i] = i; else if(rp[i] < r[i])rp[i] = i;
        ans[a[i]] = rp[i] - lp[i] + 1;
    }
}
```

---

## 作者：modfish_ (赞：2)

## 思路
首先有一件显然的事情：无论 $k$ 为多少，最后总能转换为 $k=1$ 的问题。这是因为，如果两个点之间满足 $\lvert a_x-a_y\rvert=k$，那么它们模 $k$ 的余数相同，所以只有模 $k$ 余数相同的点之间可以进行操作。那么，我们仅保留 $u\bmod k=v\bmod k$ 的边，就可以转换为对若干个连通块进行 $k=1$ 的操作了（每个点的 $a_i$ 均除以 $k$ 并上取整即可）。

那么，我们只需考虑 $k=1$ 的情形。

因为每次操作发生在数值相邻的两个点中，故 $a_x$ 的变化是连续的。所以，在 $s$ 确定时，大于 $s$ 的一定只会变小（否则变不回来），小于 $s$ 的一定只会变大。且不可能有大于 $s$ 的变成小于 $s$ 的，也不可能有小于 $s$ 的变成大于 $s$ 的。所以对大于、小于 $s$ 的点可以分开看待。

实际上，整个过程可以看作一个“感染”过程：一开始，若某个点 $x$（假定 $x<s$）与 $x+1$ 相邻，则 $x$ 可以变成 $x+1$，它们组成了一个 $x+1$ 的连通块；若这个连通块与 $x+2$ 相邻，则 $x+2$ 可以把它们都“感染”成 $x+2$，组成一个 $x+2$ 的连通块。依此类推，直到形成一个 $y$ 的连通块时，$y+1$ 与该连通块不相邻了，那么这个连通块也就无法被“感染”成 $y+1$ 了。

我们发现，在这样形成的连通块中，若 $x\le z\le y$，所有原来比 $z$ 小的点都可以被“感染”成 $z$，这是一个十分有趣的性质。假设我们从点 $L$ 开始，按上述方法扩张，最后形成的连通块包含 $s$，那么编号在 $L$ 到 $s$ 之间的每个点都可以被“感染”成 $s$。

对于 $x>s$ 的点同理，也可以扩张成一个连通块。若从点 $R$ 开始，从大往小扩张，最后形成的连通块包含 $s$，则编号在 $s$ 到 $R$ 之间的所有点都可以被“感染”成 $s$。

如果我们能找到最小的 $L$ 和最大的 $R$，那就非常好了。那么如何找呢？

不妨从 $x_0=1$ 开始，从小往大扩张，最后形成连通块的最大值记为 $x_1-1$。然后再从 $x_1$ 继续扩张，依此类推。容易发现，这样只要找到 $x_i\le s<x_{i+1}$，则 $L=x_i$。同理，从 $y_0=n$ 开始，从大往小扩张，最后形成的连通块的最小值记为 $y_1+1$，再从 $y_1$ 继续扩张。同理，这样若 $y_{i+1}<s\le y_i$，则 $R=y_i$。

如何寻找 $x_i,y_i$ 呢？考虑 BFS。先将 $1$ 的所有相邻的点扔进一个小根堆中，每次从中取出最小的。记上次取出的为 $pre$，若取出的 $now=pre+1$，说明这个连通块还可以继续扩张，则再把 $now$ 的所有相邻的点扔进堆中（注意已经在堆中的和比 $now$ 小的就不必扔了）；若 $now\ne pre+1$，说明此连通块已经扩张到极限了，退出去，再从 $pre+1$ 开始 BFS。这样，每次开始 BFS 的那个点就是 $x_i$。对 $y_i$ 同理。

接下来，枚举 $s$，找到其对应的 $L,R$，答案是否就是 $R-L+1$ 呢？

并不是。我们分以下情况讨论：

- $L<s<R$。此时，答案为 $R-L+1$。

- $L=s=R$。此时，答案为 $1$。

- $L=s<R$ 或 $L<s=R$。这两种情况比较复杂，后面再讨论。

先看第一种。设 $L=x_i,R=y_j$，则显然 $[L,s]$ 和 $[s,R]$ 都可以变成 $s$，那么，其他的点就不能变成 $s$ 了吗？

一定不可能。以 $[x_{i-1},x_i-1]$ 中的点为例，根据 $x$ 的获取过程，这个连通块中的点都恰好可以变成 $x_i-1$，而不可以变成 $x_i$，更不可能变成 $s$。同理 $[y_i+1,y_{i-1}]$ 中的点不可能变成 $y_i$，也不可能变成 $s$。

第二种与第一种类似，不讨论。

对于第三种，以 $L=s<R$ 为例。仍设 $L=x_i,R=y_j$。如果按照第一种的讨论，这种看上去也符合，但为什么并非如此呢？

考虑 $[x_{i-1},x_i-1]$ 中的点，这里面的点都可以变成 $x_i-1$，也即 $s-1$。注意，这只是说在**只对 $[x_{i-1},x_i-1]$ 中的点进行操作**的条件下，这些点不可能变成 $s$。但如果我们对 $[s,R]$ 中的点进行操作，情况便有所不同：值为 $s$ 的点的数量增多了，它们形成了一个新的连通块——$[s,R]$（容易证明这一定是一个连通块）。如果 $[s,R]$ 中的点与 $[x_{i-1},x_i-1]$ 中的点有连边，那么 $[x_{i-1},x_i-1]$ 中的 $s-1$ 都可以变成 $s$，则总答案为 $R-x_{i-1}+1$。

对于 $L<s=R$ 的情况是类似的。现在，我们如何判断 $[a,b]$ 中的点与 $[c,d]$ 之间的点是否有连边呢？

考虑建立平面直角坐标系，每一条边 $(u,v)$ 均可看做点 $(u,v)$。则该问题转换为在 $x\in[a,b],y\in[c,d]$ 的区域内有没有点，是一个二维数点问题，可以离线用树状数组做。~~试过了在线动态开点线段树 TLE 了~~。

总时间复杂度 $O((n+m)\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e5 + 5;

int n, m, k;
vector<int> G[maxn];
int vis[maxn], inq[maxn];
int st1[maxn], st2[maxn], tp1 = 0, tp2 = 0;
priority_queue<int, vector<int>, greater<int> > q1;
priority_queue<int> q2;
int ans[maxn], wait[maxn], r1[maxn], r2[maxn], res[maxn], qq = 0;
struct node{
	int l, r, x, id, tp;
}qs[maxn];
int tr[maxn];

bool cmp(node x, node y){
	return x.x < y.x;
}
void init(int n){
	for(int i = 1; i <= n; i ++) tr[i] = 0;
}
void upd(int id, int n, int r){
	if(id < 1 || id > n) return;
	for(int i = id; i <= n; i += i & -i) tr[i] += r;
}
int query(int id, int n){
	if(id < 1 || id > n) return 0;
	int s = 0;
	for(int i = id; i > 0; i -= i & -i) s += tr[i];
	return s;
}

void bfs1(int st){
	q1.push(st);
	inq[st] = 1;
	int pre = 0;
	while(!q1.empty()){
		int x = q1.top();
		if(x != st && x != pre + k) break;
		q1.pop();
		vis[x] = 1, pre = x;
		for(int i = 0; i < G[x].size(); i ++){
			int j = G[x][i];
			if(inq[j]) continue;
			inq[j] = 1;
			q1.push(j);
		}
	}
	while(!q1.empty()) inq[q1.top()] = 0, q1.pop();
}
void bfs2(int st){
	q2.push(st);
	inq[st] = 1;
	int pre = 0;
	while(!q2.empty()){
		int x = q2.top();
		if(x != st && x != pre - k) break;
		q2.pop();
		vis[x] = 1, pre = x;
		for(int i = 0; i < G[x].size(); i ++){
			int j = G[x][i];
			if(inq[j]) continue;
			inq[j] = 1;
			q2.push(j);
		}
	}
	while(!q2.empty()) inq[q2.top()] = 0, q2.pop();
}

int main(){
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= m; i ++){
		int u, v;
		scanf("%d %d", &u, &v);
		if(u % k == v % k) G[u].push_back(v), G[v].push_back(u);
	}
	for(int t = 1; t <= k; t ++){
		int n1 = (n - t + k) / k;
		for(int i = 0; i < n1; i ++){
			if(!vis[i * k + t]){
				bfs1(i * k + t);
				st1[++ tp1] = i;
			}
		}
		for(int i = 0; i < n1; i ++) vis[i * k + t] = inq[i * k + t] = 0;
		for(int i = n1 - 1; i >= 0; i --){
			if(!vis[i * k + t]){
				bfs2(i * k + t);
				st2[++ tp2] = i;
			}
		}
		for(int i = 0; i < n1; i ++) vis[i * k + t] = inq[i * k + t] = 0;
		st1[tp1 + 1] = n1, st2[tp2 + 1] = -1;
		for(int i = 0; i < n1; i ++){
			int l = 1, r = tp1, res1 = 0;
			while(l <= r){
				int mid = l + r >> 1;
				if(st1[mid] <= i) l = mid + 1, res1 = mid;
				else r = mid - 1;
			}
			l = 1, r = tp2;
			int res2 = 0;
			while(l <= r){
				int mid = l + r >> 1;
				if(st2[mid] >= i) l = mid + 1, res2 = mid;
				else r = mid - 1;
			}
			if(i != 0 && i != n1 - 1 && i == st1[res1] && i != st2[res2]){
				if(st2[res2 + 1] < i - 1) ans[i * k + t] = st2[res2] - st1[res1 - 1] + 1;
				else{
					wait[++ qq] = i, r1[qq] = st2[res2] - st1[res1 - 1] + 1, r2[qq] = st2[res2] - i + 1;
					qs[qq * 2 - 1] = (node){st2[res2 + 1] + 1, st2[res2] + 1, st1[res1 - 1] - 1, qq, -1}, qs[qq * 2] = (node){st2[res2 + 1] + 1, st2[res2] + 1, st1[res1] - 1, qq, 1};
				}
			}else if(i != 0 && i != n1 - 1 && i != st1[res1] && i == st2[res2]){
				if(st1[res1 + 1] > i + 1) ans[i * k + t] = st2[res2 - 1] - st1[res1] + 1;
				else{
					wait[++ qq] = i, r1[qq] = st2[res2 - 1] - st1[res1] + 1, r2[qq] = i - st1[res1] + 1;
					qs[qq * 2 - 1] = (node){st1[res1], st1[res1 + 1], st2[res2], qq, -1}, qs[qq * 2] = (node){st1[res1], st1[res1 + 1], st2[res2 - 1], qq, 1};
				}
			}else{
				ans[i * k + t] = st2[res2] - st1[res1] + 1;
			}
		}
		sort(qs + 1, qs + qq * 2 + 1, cmp);
		int s = 1;
		while(s <= qq * 2 && qs[s].x == -1) s ++;
		for(int i = 0; i < n1; i ++){
			int u = i * k + t;
			for(int j = 0; j < G[u].size(); j ++){
				int v = (G[u][j] % k) ? (G[u][j] / k) : (G[u][j] / k - 1);
				upd(v + 1, n1, 1);
			}
			while(s <= qq * 2 && qs[s].x == i){
				res[qs[s].id] += qs[s].tp * (query(qs[s].r, n1) - query(qs[s].l, n1));
				s ++;
			}
		}
		for(int i = 1; i <= qq; i ++){
			if(res[i]) ans[wait[i] * k + t] = r1[i];
			else ans[wait[i] * k + t] = r2[i];
			res[i] = wait[i] = r1[i] = r2[i] = 0;
		}
		tp1 = tp2 = qq = 0;
		init(n1);
	}
	for(int i = 1; i <= n; i ++) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}
```

## 二维数点
顺便讲一下二维数点问题。即给定若干个点，和若干询问 $(l,r,x,y)$，查询横坐标在 $[l,r]$ 之间，纵坐标在 $[x,y]$ 之间的点数（或点权和之类的）。

可以将其拆分为 $(1,l-1,x,y)$ 和 $(1,r,x,y)$，最后答案一减即可。

对于上述两种问题，均可概括为 $(p,x,y)$。按 $p$ 将询问排序，用扫描线从左往右扫，树状数组维护点数即可。

---

## 作者：orange_new (赞：1)

节选自：[图论做题记录（三）（2025.5.24 - 2025.31）](https://www.luogu.com.cn/article/2xi85b8k)

[安利一下我的博客](https://www.cnblogs.com/JPGOJCZX/p/18902820)

特别神秘的题目，难想，但是不好写。

我们首先可以发现，图中只有点权之差的绝对值为 $k$ 的倍数的点的点权才有可能变成一样的，因此我们可以按 $\bmod k$ 的值将整张图划分成几个部分，只有每个部分内的边才保留，部分之间的边就可以删掉了。

接下来，我们把所有 $\bmod ~k$ 同余的点拉出来放在一个序列上，然后我们考虑每一个点 $s$。如果 $t(t > s)$ 这个点的点权最终能变成 $s$，那么首先，$t$ 必须和 $s$ 连通，其次， $t$ 必然经历了 $t \rightarrow t - k \rightarrow t - 2 \times k \rightarrow \dots \rightarrow s$ 的过程，因此 $s + k$ 必须存在在 $s$ 处在的连通块中，$s + 2 \times k$ 必须与 $s$ 或 $s + k$ 连边，$s + 3 \times k$ 必须与 $s + 2 \times k$、$s + k$ 或 $s$ 连边，以此类推。一旦有一个 $s + m \times k$ 没有与 $[s, s + (m - 1) \times k]$ 连边，那么比它大的点也就无法通过它作为跳板继续变小了。因此，最终点权能变成 $s$ 的点必然是一段区间 $[l, r]$，而根据我们刚才的推导，$[l, r]$ 应该满足以下性质：

- $[l, r]$ 连通；

- 对于所有 $x \in (s, r)$，$x$ 都至少向 $(x, r]$ 中比它大的点连了一条边。

- 对于所有 $x \in (l, s)$，$x$ 都至少向 $(l, x)$ 中比它小的点连了一条边。

如图，此时所有点的权值都可以变成 $s$：

![](https://cdn.luogu.com.cn/upload/image_hosting/2g82zpy6.png)

我们先考虑后两个性质。此时我们对于每个 $s$ 都需要求出最大的 $rp_s$ 满足 $(s, rp_s]$ 中每个点 $x$ 都至少与 $(x, rp_s]$ 中的一个点连边。其实我们会发现，当 $s$ 左移的时候，如果 $s$ 与 $[s + k, rp_{s + k}]$ 中的点有连边，那么 $rp_s$ 应该等于 $rp_{s + k}$，否则 $rp_s$ 就应该等于 $s$。因此我们处理出与 $x$ 相连通的点中最大的点 $r_s$ 与最小的点 $l_s$，然后倒着扫一遍就可以了（$lp_s$ 的意义与求法和 $rp_s$ 类似，不再赘述）。

此时我们再来考虑第一个性质，根据 $rp_s$ 和 $lp_s$ 的定义 $(s, rp_s]$ 中的点以及 $[lp_s, s)$ 中的点已经连通了，我们现在只需要判断 $[lp_s, s)$、$[s, s]$ 和 $(s, rp_s]$ 是否连通。与 $[s, s]$ 判断连通是容易的，但是有一种情况，$[lp_s, s)$ 和 $(s, rp_s]$ 连边，而 $[lp_s, s)$ 和 $(s, rp_s]$ 中有一个区间与 $[s, s]$ 连边，这也是合法的，此时我们就需要判断两个区间之间是否有连边。显然可以把这两个区间变成二维平面中的两个点，把它们作为对角线上的两个顶点，可以得到一个矩形，我们再把边 $(u, v)$ 也变成二维平面中的一个点，此时只用扫描线数一下这个矩形内有没有点就可以了，不过这样子会带一个 $\log$，考虑优化成线性。

我们考虑一条边 $(u, v)$ 会连接哪几个区间，如果 $(u, v)$ 连接了 $[lp_i, s)$ 和 $(s, rp_i]$，那么一定是如下的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/tflwhkz6.png)

它需要满足 $lp_s \leq u \leq s \leq v \leq rp_s$，根据 $lp_s$ 和 $rp_s$ 的性质，可以知道它们都是单增的，那么 $(u, v)$ 贡献到的 $s$ 必然是一段连续的区间。我们设 $pre_u$ 表示比 $u$ 小的最大的 $lp_s$，$suf_u$ 表示比 $u$ 大的最小的 $rp_s$，那么一条边 $(u, v)$ 贡献到的 $s$ 的区间就是 $[\max(u + k, pre_v), \min(v - k, suf_u)]$，可以用差分处理。

此时就可以对于每一个 $s$ 判断 $[lp_s, s)$、$[s, s]$ 和 $(s, rp_s]$ 的连通性了，那么我们就用 $O(n)$ 的时间复杂度解决了这个问题。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXSIZE (1 << 20)
char buf[MAXSIZE], *p1, *p2;
char pbuf[MAXSIZE], *pp;
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) ? EOF : *p1++)
#define pc putchar
inline int read(){
	int x = 0;
	char ch = gc();
	while(!isdigit(ch))
		ch = gc();
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = gc();
	}
	return x;
}
inline void write(int x){
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 4e5 + 9, M = 1e6 + 9, INF = 1e9 + 9;
struct Edge{
    int v, nex;
} e[M << 1];
int head[N], ecnt;
void addEdge(int u, int v){
    e[++ecnt] = Edge{v, head[u]};
    head[u] = ecnt;
}
int n, m, k, ans[N], l[N], r[N], lp[N], rp[N], pre[N], suf[N], sum[N];
int main(){
    n = read();
    m = read();
    k = read();
    for(int i = 1; i <= m; i++){
        int u, v;
        u = read();
        v = read();
        if(u % k == v % k){
            addEdge(u, v);
            addEdge(v, u);
        }
    }
    for(int re = 1; re <= k; re++){
        int tot = n / k + (n % k >= re), up = (tot - 1) * k + re;
        for(int u = re; u <= n; u += k){
            l[u] = -INF, r[u] = INF;
            for(int i = head[u]; i; i = e[i].nex){
                int v = e[i].v;
                if(v < u)
                    l[u] = max(l[u], v);
                else
                    r[u] = min(r[u], v);
            }   
        }
        lp[re] = re;
        for(int i = re + k; i <= n; i += k){
            if(l[i - k] < lp[i - k] && lp[i] != i - k)
                lp[i] = i - k;
            else
                lp[i] = lp[i - k];
        }
        rp[up] = up;
        for(int i = up - k; i >= re; i -= k){
            if(rp[i + k] < r[i + k] && rp[i] != i + k)
                rp[i] = i + k;
            else
                rp[i] = rp[i + k];
        }
        for(int i = re; i <= n; i += k){
            suf[i] = i == re ? i - k : suf[i - k];
            while(suf[i] + k <= n && lp[suf[i] + k] <= i)
                suf[i] += k;
        }
        for(int i = up; i >= re; i -= k){
            pre[i] = i == up ? up + k : pre[i + k];
            while(pre[i] - k >= re && rp[pre[i] - k] >= i)
                pre[i] -= k;
        }
        for(int u = re; u <= n; u += k){
            for(int i = head[u]; i; i = e[i].nex){
                int v = e[i].v;
                if(u >= v)
                    continue;
                int x = max(u + k, pre[v]), y = min(v - k, suf[u]);
                if(x <= y){
                    sum[x]++;
                    sum[y + k]--;
                }
            }
        }
        for(int i = re; i <= n; i += k){
            sum[i] += i == re ? 0 : sum[i - k];
            if(l[i] < lp[i] && rp[i] < r[i])
                lp[i] = rp[i] = i;
            else if(!sum[i]){
                if(l[i] < lp[i])
                    lp[i] = i;
                else if(rp[i] < r[i])
                    rp[i] = i;
            }
            ans[i] = (rp[i] - lp[i] + k) / k;
        }
    }
    for(int i = 1; i <= n; i++){
        write(ans[i]);
        pc(' ');
    }
    return 0;
}
```

---

## 作者：bunH2O (赞：1)

不难发现 $k$ 的数值在题中无用，以下默认 $k=1$。

我们先考虑 $s=1$ 该怎么做，发现由于初始时 $a_i=i$，假如我们此时令 $a_i\leftarrow a_i-1$，那么所有 $j>i$ 都无法变成 $1$。因此能变成 $1$ 的必然是一个前缀。

考虑如下的贪心：令 $u$ 从 $n-1$ 到 $1$ 遍历，对于所有的边 $(u,v)$，若 $a_v=a_u+1$，则将 $a_v$ 及所在的与其值相同的连通块均变为 $a_u$。可以证明该做法正确。**事实上，任意时刻值相同的点都是联通的，而且他们在编号上也是连续的。**

这样我们就解决了 $s=1$ 或 $s=n$ 的情况。

在下文中，我们认为 $i$ 在 $j$ 左侧当且仅当 $i<j$，$i$ 在 $j$ 右侧同理。

考虑更一般的情况，我们称如上的贪心为「向左推进」，与之相对的，处理 $s=n$ 的贪心为「向右推进」。我们在向左推进的过程中，维护数组 $r_i$ 表示向左推进到该点时的右端点；在向右推进的过程中，维护 $l_i$ 表示向右推进到该点时的左端点。我们发现，在多数情况下，答案即为 $r_s-l_s+1$，即 $s$ 点左右互不影响。

然而，在某些情况下，我们将 $s$ 点右侧点向左推进至 $s$ 后，原本无法向右推进到 $s$ 的点此时可以推进。也即存在一条边 $e<u,v>$，满足 $u$ 能够向右推进至 $s-1$，而 $v$ 能够向左推进至 $s$。此时可以将 $u$ 推进到 $v$。

考虑解决这种情况，由于合法的 $u$ 和 $v$ 都在一个区间内。此时我们将 $e$ 视作二维平面上的点，$u$ 和 $v$ 视作一个矩形。问题转为二维数点，可以 $O(n\log n)$ 进行解决。

---

## 作者：exCat (赞：1)

## 前置

图论建模

## 思路

1. 因为 $|a_x-a_y|=k$ 才能操作，所以只有 $a_x \equiv a_y \pmod k$ 的点才有可能相互转化，所以将点按对 $k$ 去模分类。对于同一类的点，我们发现只有相对大小有用，就从小到大重新编号和排列，问题等价为原问题 $k=1$ 的情况。

2. 我们思考什么时候 $l\le s\le r,[l,r]$ 区间内的点都可以变成 $s$ 。我们可以发现在 $\forall x\in(l,s)$ 都至少要向 $[l,x-1]$ 有一条连边。你可能会疑惑为什么不是 $x$ 必须向 $x-1$ 连边，明明只有差 $1$ 的时候才能转移。事实上，在添加 $x$ 之前，   $[l,x-1]$ 都可以被全部改成  $[l,x-1]$ 中的任意值，只需要全部改成 $x-1$ 就能转移了（可以理解为变成一个大的点了）。同理，有 $\forall x\in(s,r)$ 都至少向 $(x,r]$ 有一条连边。完了吗？ 没有，我们发现左边所有数都可以变成 $s-1$ ,右边的所有数都可以变成 $s+1$ ,但是 $s$ 不一定可以连到左边或右边，所以我们还有看 $s$ 与左右两边的连通关系。

3. 我们可以先对每个点预处理出，左边有连边的最大的点 $l_i$ ，右边有连边的最小的点 $r_i$ 。对于第一个条件可以预处理，从左向右扫新加入一个点就判断，看它是否与前面有连边，否则就只能拓展到自己， $O(n)$ 算出 $lp_i$ ，同理处理出 $rp_i$ 。最后一条限制就可以快速判断了比较 $l$ 与 $lp_i$ 以及 $r$ 与 $rp_i$ 的大小关系即可。

4. 但是还有一种情况考虑漏了，如果 $s$ 只有左边有连边，但是左边与右边有连边，岂不是可以将整个左边染成 $s$ 后再染右边，所以我们还得处理这种情况。对每个 $s$ 去判断是非常不优的，所以可以对每条边判断对那些 $s$ 有贡献，有贡献当且仅当  $lp_i\le u<s<v\le rp_i $ ,我们还可以预处理，考虑左边，对每个点 $i$ 存最大的 $s$ 使 $lp_i\le i$ ，右边同理，就可以快速求出 $s$ 的区间，用差分 $O(1)$ 修改即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=6e5+10;
int n,m,k,l[N],r[N],lp[N],rp[N],pr[N],nx[N],ans[N],pos[N],bj[N];
vector<int> ve[N];
void solve(int ys)
{
	int zs=(n/k)+(n%k>=ys);
	lp[1]=1,rp[zs]=zs,pr[0]=0,nx[zs+1]=zs+1;//初始化,对边界要特殊处理
	for(int i=1;i<=zs;i++)pos[ys+(i-1)*k]=i,bj[i]=0;
	for(int i=1;i<=zs;i++)
	{
		int u=ys+(i-1)*k;
		l[i]=0,r[i]=n+2;
		for(int v:ve[u])
		{
			int j=pos[v];
			//cout<<u<<" "<<v<<" "<<i<<" "<<j<<'\n'; 
			l[i]=max(l[i],j);
			r[j]=min(r[j],i);
		}
	} 
	//for(int i=1;i<=zs;i++)cout<<i<<" "<<l[i]<<" "<<r[i]<<'\n';
	for(int i=2;i<=zs;i++)
	{
		lp[i]=lp[i-1];
		if(l[i-1]<lp[i])lp[i]=i-1;
	} 
	for(int i=zs-1;i>=1;i--)
	{
		rp[i]=rp[i+1];
		if(r[i+1]>rp[i])rp[i]=i+1;
	} 
	//for(int i=1;i<=zs;i++)cout<<lp[i]<<" "<<rp[i]<<'\n';
	for(int i=1;i<=zs;i++)
	{
		pr[i]=pr[i-1];
		while(lp[pr[i]+1]<=i&&pr[i]+1<=zs)pr[i]++;
	} 
	for(int i=zs;i>=1;i--)
	{
		nx[i]=nx[i+1];
		while(rp[nx[i]-1]>=i&&nx[i]-1>=1)nx[i]--;
	}
	//for(int i=1;i<=zs;i++)cout<<pr[i]<<" "<<nx[i]<<'\n';
	for(int i=1;i<=zs;i++)
	{
		int u=ys+(i-1)*k;
		for(int v:ve[u])
		{
			int j=pos[v];
			int kt=max(j+1,nx[i]),jw=min(i-1,pr[j]);
			//cout<<kt<<" "<<jw<<'\n';
			if(kt<=jw)bj[kt]++,bj[jw+1]--;
		}
	} 
	for(int i=1;i<=zs;i++)bj[i]+=bj[i-1];
	for(int i=1;i<=zs;i++)
	{
		int s=ys+(i-1)*k;
		if(lp[i]>l[i]&&rp[i]<r[i])lp[i]=rp[i]=i;
		else if(!bj[i])
			{
				if(lp[i]>l[i])lp[i]=i;
				else if(rp[i]<r[i])rp[i]=i;
		 	} 
		ans[s]=rp[i]-lp[i]+1;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		int u,v;cin>>u>>v;
		if(u<v)swap(u,v);//保证u大于v
		if(u%k==v%k)ve[u].push_back(v); 
	}
	for(int i=1;i<=k;i++)solve(i);
	for(int i=1;i<=n;i++)cout<<ans[i]<<" "; 
	return 0; 
} 
```

---

## 作者：david0911 (赞：0)

首先转化限制，$|a_x-a_y|=k$ 的一个**必要条件**是 $a_x\equiv a_y\pmod k$。于是我们只关心模 $k$ 同余的点之间的边。

先把这些点拿出来，然后就转化为了 $k=1$ 的情形。不妨将点按编号大小从小到大排成一排。

考虑如何算 $s=1$ 的答案，注意到答案的最终形态必定是 $[1,r]$ 的连通块，且 $x\in[1,r)$ 必定向 $(x,r]$ 中的某个点连了边。

那么推广到一般情况，可以知道对于 $s=i$ 的情况，答案的形态为 $[l,r]$ 的连通块。$x\in[i,r)$ 必定向 $(x,r]$ 连了边。对称的情况是类似的。

为了得到上述 $l,r$，我们定义 $L_i$ 表示**只考虑 $i$ 左侧的边**，$i$ 向左能连通 $[L_i,i]$ 的最远位置，$R_i$ 同理。

容易发现 $L_i=i$ 或 $L_i=L_{i-1}$。$R_i$ 同理。于是扫一遍检查连边就可以得到 $L_i$ 和 $R_i$。

于是答案的连通块必定**包含于** $[L_{i-1},R_{i+1}]$ 中，将其分为三部分来看待以便得到答案：$[L_{i-1},i-1],[i,i],[i+1,R_{i+1}]$。这里需要一点分类讨论：

1. 如果 $[i,i]$ 与左右都连通，即 $L_i=L_{i-1} \land R_i=R_{i+1}$，那么答案就是 $R_{i+1}-L_{i-1}+1$。

2. 如果 $[i,i]$ 与左右都不连通，那么答案就是 $1$。

3. 如果 $[i,i]$ 只与单侧连通，由于 $L_i,R_i$ 的定义，并没有考虑到**跨过 $i$ 的边**对连通性的影响。如果此时 $[L_{i-1},i-1]$ 与 $[i+1,R_{i+1}]$ 之间有边相连，那么答案应当同第一种情况（这时可以先将单侧变为 $i$，然后再将另一侧变为 $i$），否则只计算单边的答案。

现在的问题就是判定两个区间之间是否有边相连。

可以直接将边 $(u,v)$ 视为二维平面上一点，然后就是数矩形内是否有点。这样实现的复杂度是 $O(m\log n)$。

也可以发现 $L_i,R_i$ 具有单调性。对于一条边 $(u,v)$ 考虑可以使得哪些 $i$ 合法（$u>v$）。写出限制：$v\ge L_{i-1}\land v\le i-1\land u\ge i+1\land u\le R_{i+1}$。

发现符合条件的 $i$ 是一段区间，进行差分可以标记出符合条件的 $i$。左右端点可以二分，复杂度 $O(m\log n)$。可以精细实现去掉二分，复杂度线性。

---

## 作者：XZhuRen (赞：0)

首先只有差为 $k$ 倍数的边才能转移，所以问题等价于 $k=1$。

考虑怎么做：

从图上来看，一次操作可以视为合并两个点，合并后两点同时变化。

一次操作的目标为 $tgt$，则我们每次合并一定是朝着 $tgt$ 方向合并的。

因为每个点值只有一个，合并可以视为删点，这时答案必然在值域上连续。

考虑扫出前缀 $L_i$ 和后缀答案 $R_i$，发现还有一种情况，即合并后 $[L_{tgt},tgt]$ 与 $[tgt+1,R_{tgt+1}]$ 之间有连边（或反之），这个直接扫出来之后 BIT 维护一下即可。

然后就结束了，注意重编号。

---

