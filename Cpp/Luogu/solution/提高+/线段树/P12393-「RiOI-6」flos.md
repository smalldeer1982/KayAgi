# 「RiOI-6」flos

## 题目背景

![](bilibili:BV1Gi4y1g77Q)

即使是像萝卜这样不起眼的小木头，也有被人喜欢的日子呢！

帽子的表白真是突如其来，小萝卜拼尽全力才战胜了自己上扬的嘴角，没有在上课划水的时候笑出来。

今年的 2.14，终于！可以！两个人过了！

## 题目描述

帽子要摘一些小萝卜最喜欢的花装点礼物。

小萝卜最喜欢的花长在一棵根为 $1$ 的树上，其中每个节点都有一朵花。当帽子从点 $u$ 开始摘花时，花的芳香度 $w_v$ 定义为 $\operatorname{dis}(u,v)$，也即 $u$ 到 $v$ 的最短距离。帽子只能摘下一朵花。

帽子只有 $t$ 秒的时间。具体的，他从 $u$ 开始沿着边移动，当他向上爬一条边（即**远离根**）时消耗 $1$ 单位时间，向下滑一条边（即**接近根**）时不消耗时间，全过程中剩余时间不能少于 $0$。

小萝卜有 $q$ 个问题，每次形如：帽子从点 $x_i$ 出发，有 $t_i$ 时间，摘的花的最大芳香度是多少。各个询问相互独立。

特别的，有时候小萝卜会在帽子摘完花后才会问下一个问题，所以在一些测试点中你需要强制在线。

## 说明/提示

#### 【样例解释】

对于样例 $1$，三个询问分别如下：

- 从 $1$ 出发，体力值为 $2$。此时能摘下的其中一朵芳香度最大的花是 $4$，芳香度为 $2$。帽子可以向上爬 $2$ 条边到达 $4$。
- 从 $1$ 出发，体力值为 $4$。此时能摘下的其中一朵芳香度最大的花是 $5$，芳香度为 $3$。帽子可以向上爬 $3$ 条边到达 $5$。
- 从 $2$ 出发，体力值为 $2$。此时能摘下的其中一朵芳香度最大的花是 $4$，芳香度为 $3$。帽子可以先向下滑一条边到 $1$，再向上爬 $2$ 条边到达 $4$。

对于样例 $2$，暂时不能给你一个明确的答复。

#### 【数据范围】

**本题开启捆绑测试。**

|子任务|分数|$n,q\le$|$d=$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$20$|$10^3$|$0$||
|$2$|$10$|$2\times10^5$|$0$|$\forall i,u_i+1=v_i$|
|$3$|$20$|$2\times10^5$|$0$|$\forall i,t_i=n$|
|$4$|$20$|$2\times10^5$|$0$||
|$5$|$30$|$2\times10^5$|$1$||

对于 $100\%$ 的数据，$1\le n,q\le 2\times10^5,d\in\{0,1\},1\le x_i\le n,0\le t_i\le n$。

## 样例 #1

### 输入

```
5 3 0
1 2
1 3
3 4
4 5
1 2
1 4
2 2
```

### 输出

```
2
3
3
```

## 样例 #2

### 输入

```
10 5 1
1 2
1 3
3 4
2 5
4 6
4 7
7 8
8 9
9 10
1 0
4 2
2 4
2 1
8 0
```

### 输出

```
0
4
3
2
8
```

# 题解

## 作者：chenly8128 (赞：6)

其实这道题不需要上数据结构。

我的方法是：预处理，然后分类、拆分。根本途径是通过**倍增**求解。

### 预处理

通过两次深搜，分别求出：

1. 深度，倍增跳表，向下的最长链，向下的次长链，向下最长链的儿子编号。（最长链和次长链要求不能有重复的边，但是长度可以相同，如果凑不齐两条链，就空着作 0）。
2. 向上最长链。

### 分类

1. 如果无论如何都无法将时间全部用光，那么最简单，直接将向下最长链和向上最长链取较大值即可。
2. 否则的话……需要对路径进行拆分。

### 拆分和贪心

首先，很明显，下滑后不应该走回头路向上爬，这样做一定劣。

在上述情况 2 的基础上，我们进行贪心。

贪心原则：**下滑后，仍然能滑动「时间限制」条不走回头路的边的前提下，尽可能向下滑到深度最小的节点。**

滑到这样的节点后，**计算下滑了的距离，再加上给定的时间限制**，就是询问的答案。

**注意：滑到这样的点之后，可能需要继续向下滑动。但是继续下滑的距离不用特意计算在答案内，因为已经被包含在答案里了。**

至于如何贯彻这一贪心原则，我的办法是倍增，深度大的节点一定比深度小的节点更容易满足「能滑动时间限制条边」这一条件，因为深度大的节点还可以继续下滑到深度小的节点，但是深度小的节点不能走回头路。满足单调性。

太抽象了，举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/j03vugx7.png)

询问：从节点 7 出发，总共有 2 单位的时间。

通过倍增可以发现，下滑后，仍然能滑动时间限制条边的节点有：节点 7 自身、节点 4（从 4 到 2 的边数 为 3、从 4 到 5 也就是向下次长链长度为 2）和节点 3（从 3 到 2 的边数为 2）。但是由于节点 3 下滑得更多，所以贪心的选择节点 3。

所以答案为 $2+2 = 4$。第一个 $2$ 是下滑了距离；第二个 $2$ 是时间限制。实际路径为 `7 -> 4 -> 3 -> 1 -> 2`。

注意：在这里，虽然下滑到节点 3 之后，还在继续下滑，但是后面下滑的距离被包含在了「时间限制」部分，不用刻意计算。

### 代码

代码时间复杂度 $O((n + q) \log n)$，瓶颈在于倍增。

```cpp

// Author: chenly8128
// Created: 2025-05-01 16:39:16

#include <bits/stdc++.h>
using namespace std;
inline int read(void) {
	int res = 0;bool flag = true;char c = getchar();
	while (c < '0' || c > '9') {flag ^= (c == '-');c = getchar();}
	while (c >= '0' && c <= '9') {res = (res << 3) + (res << 1) + (c ^ 48);c = getchar();}
	return flag ? res : -res;
}
const int MAXN = 2e5+10;
const int MLOG = 21;
int n,q,d,ans = 0,u,v;
int l1[MAXN],l2[MAXN],fr[MAXN],dp[MAXN],de[MAXN];
int step[MAXN][MLOG];
vector <int> g[MAXN];
int dfs1 (int x,int fa) {
	l1[x] = l2[x] = 0;
	step[x][0] = fa;
	for (int i = 1;i < MLOG;i++)
		if (step[x][i-1] == 0) break;
		else step[x][i] = step[step[x][i-1]][i-1];
	for (int y : g[x])
		if (y != fa) {
			de[y] = de[x]+1;
			int tmp = dfs1(y,x);
			if (l1[x] < tmp) {
				l2[x] = l1[x];
				l1[x] = tmp;
				fr[x] = y;
			}
			else if (l2[x] < tmp) l2[x] = tmp;
		}
	return l1[x]+1;
}
void dfs2 (int x,int fa,int k) {
	dp[x] = k;
	for (int y : g[x])
		if (y != fa)
			dfs2(y,x,max(k,(y == fr[x] ? l2[x] : l1[x])) + 1);
}
int main (void) {
	n = read(); q = read(); d = read();
	for (int i = 1;i < n;i++) {
		u = read(); v = read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(1,0);
	dfs2(1,0,0);
	while (q--) {
		u = read(); v = read();
		if (d) {
			u ^= ans;
			v ^= ans;
		}
		int ori = de[u];
		if (max(dp[u],l1[u]) >= v) {
			for (int i = MLOG-1;i >= 0;i--) {
				if (step[u][i] > 0) {
					int t = step[step[u][i]][0];
					if (t == 0) continue;
					int p = max(dp[t],fr[t] == step[u][i] ? l2[t] : l1[t]);
					if (p >= v) u = step[u][i];
				}
			}
			int t = step[u][0];
			if (t != 0) {
				int p = max(dp[t],fr[t] == u ? l2[t] : l1[t]);
				if (p >= v) u = step[u][0];
			}
			printf ("%d\n",ans = v+ori-de[u]);
		}
		else printf ("%d\n",ans = max(dp[u],l1[u]));
	}
	return 0;
}
```

---

## 作者：Register_int (赞：6)

先考虑离线。把询问挂点上，可以直接对树进行搜索，维护出当前点 $u$ 到根链上每个点除了 $u$ 子树外的最深节点深度。设祖先 $f$ 的深度为 $d_f$，树内最深节点到他的距离为 $w_f$，那么你要求的就是 $\max_f(d_u-d_f+\min(t,w_f))$。对值域开个线段树，$\le t$ 的查最大的 $w_f-d_f$，$>t$ 的查最大的 $-d_f$ 即可。

发现上面这个过程是好在线的，你线段树换主席树就行了。时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int inf = 0x3f3f3f3f;

struct node {
	int l, r, vx, vy;
	node(int l = 0, int r = 0, int vx = -inf, int vy = -inf)
		: l(l), r(r), vx(vx), vy(vy) {}
} t[MAXN << 6]; int n, m, op, rt[MAXN], cnt, last;

void modify(int &p, int pre, int k, int x, int l = 1, int r = n) {
	t[p = ++cnt] = t[pre];
	t[p].vx = max(t[p].vx, k - x), t[p].vy = max(t[p].vy, -x);
	if (l == r) return ; int mid = l + r >> 1;
	if (k <= mid) modify(t[p].l, t[pre].l, k, x, l, mid);
	else modify(t[p].r, t[pre].r, k, x, mid + 1, r);
}

int qx(int p, int ql, int qr, int l = 1, int r = n) {
	if (!p || ql > qr || r < ql || l > qr) return -inf;
	if (ql <= l && r <= qr) return t[p].vx; int mid = l + r >> 1;
	return max(qx(t[p].l, ql, qr, l, mid), qx(t[p].r, ql, qr, mid + 1, r));
}

int qy(int p, int ql, int qr, int l = 1, int r = n) {
	if (!p || ql > qr || r < ql || l > qr) return -inf;
	if (ql <= l && r <= qr) return t[p].vy; int mid = l + r >> 1;
	return max(qy(t[p].l, ql, qr, l, mid), qy(t[p].r, ql, qr, mid + 1, r));
}

vector<int> g[MAXN]; int dep[MAXN], d[MAXN], ans[MAXN];

multiset<int, greater<int>> s[MAXN];

void init(int u, int f) {
	dep[u] = dep[f] + 1;
	for (int v : g[u]) if (v != f) init(v, u), d[u] = max(d[u], d[v] + 1);
}

void dfs(int u, int f) {
	for (int v : g[u]) if (v != f) s[u].emplace(d[v]);
	for (int v : g[u]) {
		if (v == f) continue; s[u].erase(s[u].find(d[v]));
		modify(rt[v], rt[u], (s[u].empty() ? 0 : *s[u].begin() + 1), dep[u]);
		s[u].emplace(d[v]), dfs(v, u);
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &op);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		g[u].emplace_back(v), g[v].emplace_back(u);
	}
	init(1, 0), dfs(1, 0);
	for (int u, t; m--; ) {
		scanf("%d%d", &u, &t);
		if (op) u ^= last, t ^= last;
		int x = dep[u] + qx(rt[u], 1, t);
		int y = dep[u] + t + qy(rt[u], t + 1, n);
		printf("%d\n", last = max(min(d[u], t), max(x, y)));
	}
}
```

---

## 作者：_lmh_ (赞：0)

观察题面，发现远离根节点需要代价，而接近根节点没有代价，所以我们肯定希望先往根节点走一段，然后再从所在节点的另外一棵子树向外走。

预处理 $g_u$ 代表从 $u$ 的父亲开始，不经过 $u$ 所在子树往外走的最远的距离，则答案为 $\max_{fa_u\in anc(x)}(dep_x-dep_{fa_u}+\min(g_u,t))$。

对于 $g_u\ge t$ 的节点，显然只有深度最小的是有意义的，设其为 $v$。而对于 $g_u<t$ 的节点，只有当它是 $v$ 的祖先时是有意义的。

前面一部分可以用树上倍增找到 $u$，后面直接预处理 $h_u=\max_{v\in anc(u)}(g_v-dep_{fa_v})$ 即可。

时间复杂度 $O(n\log n)$。本题有一些 corner case，可以参考代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
const ll N=200007;
ll T,n,m,ans,dep[N],f[N],p[N][20],g[N][20],h[N];
vector<ll> to[N];
void dfs1(int u,int fa){
	f[u]=dep[u]=dep[fa]+1;
	p[u][0]=fa;
	for (int i=1;i<20;++i) p[u][i]=p[p[u][i-1]][i-1];
	ll tmp=0;
	for (auto v:to[u]) if (v!=fa){
		dfs1(v,u);
		if (f[v]>tmp) tmp=f[v];
		if (tmp>f[u]) swap(f[u],tmp);
	}
	for (auto v:to[u]) if (v!=fa) g[v][0]=(f[u]==f[v]?tmp:f[u])-dep[u];
}
void dfs2(int u,int fa){
	f[u]-=dep[u];
	if (u!=1) h[u]=max(h[fa],g[u][0]-dep[fa]);
	for (int i=1;i<20;++i) g[u][i]=max(g[u][i-1],g[p[u][i-1]][i-1]);
	for (auto v:to[u]) if (v!=fa) dfs2(v,u);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>T;
	for (int u,v,i=1;i<n;++i){
		cin>>u>>v;
		to[u].emplace_back(v);to[v].emplace_back(u);
	}
	dep[0]=-1;
	dfs1(1,0);dfs2(1,0);
//	for (int i=1;i<=n;++i) cout<<f[i]<<' '<<g[i][0]<<' '<<h[i]<<endl;
	for (int x,d,_=1;_<=m;++_){
		cin>>x>>d;
		if (T){
			x^=ans;d^=ans;
		}
		if (x==1){
			ans=min(f[x],d);
			cout<<ans<<'\n';continue;
		}
		if (d==0){
			ans=dep[x];
			cout<<ans<<'\n';continue;
		}
		if (g[x][19]<d){
			ans=max(min(f[x],d),dep[x]+h[x]);
			cout<<ans<<'\n';continue;
		}
		int u=x;
		ans=min(f[u],d);
		for (int i=19;~i;--i) if (g[p[u][i]][19]>=d) u=p[u][i];
		u=p[u][0];
		ans=max(ans,dep[x]+max(d-dep[u],h[u]));
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

