# [BalticOI 2022] Stranded Far From Home (Day2)

## 题目描述

你就是不能放任不管……实际上你进行了闯入行动，并且最初所有事情就像计划一样进行。然而，你和你的助手之间的通讯情况变得十分糟糕（这是符合预期的，不是吗？）你没有安全返回吕贝克，而是被困在一个小岛上，并且你的潜艇没有燃料了。

为了及时返回参加 BOI 的颁奖仪式，你现在必须去岛的另一边坐船。然而，当地居民有着奇怪的传统。领带对他们来说非常重要，每个村庄都有自己喜欢的领带颜色，并且这个颜色可能会随着时间的推移而改变。

一份互联网上的报告显示，不同的村庄最初喜欢不同的领带颜色。不幸的是，这份报告已经相当过时了。从那时起，每个星期都有恰好一个村庄说服一个相邻的村庄喜欢和他们一样的领带颜色（如果两个村庄有公路直接相连，它们就是相邻的）。然而，只有当整个岛上喜欢第一个村庄的领带颜色不比喜欢第二个村庄的领带颜色的人少时，这种情况才会发生。足够长的时间过去了，所以现在所有的岛民都喜欢同样的领带颜色。

你基本可以肯定，如果你不戴符合他们喜好的领带，岛民就不会让你通过。因此，为了去渡口，你计划戴上岛民可能喜欢的每种颜色的领带。然而，戴太多的领带会让你看起来很可疑。编写一个程序，使用对岛屿的描述来计算你必须戴哪些领带。

## 说明/提示

【样例解释】

样例 #1 解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/g9hsfh2d.png)

【数据范围】

* 子任务 1（10 分）：$N,M\leq2000$；
* 子任务 2（10 分）：$s_1\geq s_2\geq\dots\geq s_n$ 且对于 $i=2\sim n$，有且仅有一个 $j$ 满足 $j$ 与 $i$ 相连；
* 子任务 3（15 分）：$i,j$ 直接相连当且仅当 $|i-j|=1$；
* 子任务 4（30 分）：有且仅有不超过 $10$ 种不同的 $s_i$；
* 子任务 5（35 分）：无特殊限制。

对于所有数据，满足 $1\le n\le 2\times 10^5$，$0\le m \le 2\times 10^5$，$1 \le s_ i\le 10^9$。

## 样例 #1

### 输入

```
4 4
2 2 4 3
1 2
1 3
2 3
3 4
```

### 输出

```
1110
```

## 样例 #2

### 输入

```
4 3
4 2 2 1
1 2
3 2
4 1
```

### 输出

```
1110
```

# 题解

## 作者：t162 (赞：4)

先考虑最大的点，这个点一定能够说服所有的村庄。而别的村庄为了能够说服这个最大的村庄，必须要先通过说服别的村庄来达到目的。

先把这个最大的村庄删掉，剩下的图就会分成若干个连通块。显然如果一个村庄能够说服图中所有的村庄，那么必然能先说服自己属于的连通块的村庄。并且能够说服这个最大的村庄，就能够说服整张图中的村庄。而如果一个连通块中的所有村庄的人数之和都没有这个最大的村庄多，那么这个连通块中的村庄就不可能说服所有村庄。把这样的连通块删掉，剩下的直接递归下去就行了。

具体实现的时候，为了方便，可以使用并查集重新建树。时间复杂度 $\mathcal O(n\log n)$。



```cpp
// Author: e3c8f1a924   Time: 2022年10月07日 星期五 14时18分51秒
#include<cstdio>
#include<algorithm>
#include<vector>
typedef long long ll;
int f[200005], _[200005], n, vis[200005], m, s[200005], ans[200005];
ll S[200005];
std::vector<int> e[200005], son[200005];
int find(int x) { return f[x] == x ? x : (f[x] = find(f[x])); }
void dfs(int u) {
	S[u] = s[u];
	for (int v : son[u]) dfs(v), S[u] += S[v];
}
void solve(int u) {
	ans[u] = 1;
	for (int v : son[u]) {
		if (S[v] >= s[u]) solve(v);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", s + i);
	for (int i = 1; i <= m; i++) {
		int u, v; scanf("%d%d", &u, &v);
		e[u].push_back(v), e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) f[i] = i;
	for (int i = 1; i <= n; i++) _[i] = i;
	std::sort(_ + 1, _ + n + 1, [=](int x, int y) { return s[x] < s[y]; });
	for (int i = 1; i <= n; i++) {      // 重新建树
		for (int j : e[_[i]]) {
			if (!vis[j]) continue;
			if (find(j) == _[i]) continue;
			son[_[i]].push_back(find(j));
			f[find(j)] = _[i];
		}
		vis[_[i]] = 1;
	}
	int tot = 0;
	for (int i = 1; i <= n; i++) if (f[i] == i) tot++;
	if (tot > 1) {
		for (int i = 0; i < n; i++) putchar('0');
		return puts(""), 0;
	}
	dfs(_[n]), solve(_[n]);
	for (int i = 1; i <= n; i++) printf("%d", ans[i]);
	return puts(""), 0;
}

```

---

## 作者：7KByte (赞：3)

手动模拟一下从 $x$ 点出发的过程，必然是先吞掉 $\le x$ 的点，总和达到 $s$，接着吞掉 $\le s$ 的点，一直下去直到不能再吞位置。

那么我们需要支持快速查询从点 $x$ 出发，经过 $\le y$ 的点能到达的连通块的大小。我们把每条边的边权赋为 $\max\{s_a,s_b\}$，那么这就可以简单用 kruscal 重构树解决。

没吞两次 $s$ 的大小至少翻倍，再考虑倍增，时间复杂度是 $\mathcal{O}(n\log ^ 2 n)$。

```cpp
#define N 400005
int k, n, m, t, fa[N], w[N], f[N][19]; LL s[N];
struct node{
	int u, v, w;
	bool operator<(const node o)const{return w < o.w;}
}e[N];
int get(int x){return fa[x] == x ? x : fa[x] = get(fa[x]);}
int main() {
	read(n, m);
	rp(i, n)read(s[i]), fa[i] = i;
	rp(i, m)read(e[i].u, e[i].v), e[i].w = max(s[e[i].u], s[e[i].v]);
	sort(e + 1, e + m + 1), t = n;
	rp(i, m){
		int x = get(e[i].u), y = get(e[i].v);
		if(x != y)++t, fa[x] = fa[y] = fa[t] = f[x][0] = f[y][0] = t, s[t] = s[x] + s[y], w[t] = e[i].w;
	}
	k = log2(t);
	rp(i, k)rp(x, t)f[x][i] = f[f[x][i - 1]][i - 1];
	rp(i, n){
		int x = i;
		while(true){
			LL p = s[x];
			pre(j, k, 0)if(f[x][j] && p >= w[f[x][j]])x = f[x][j];
			if(p == s[x])break;
		}
		if(!f[x][0])pc('1'); else pc('0');
	}el;
	return 0;
}
```

---

## 作者：_Kenba_ (赞：1)

这道题我觉得思维非常奇特，我使用的是克鲁斯卡尔重构树。

首先我们可以把村庄看作一个点，然后根据道路给他们建边，然后我们发现这样做的话会T飞，所以我们要根据村庄人数给他们排序，然后开一张新图，按顺序把点放进去，如果他跟已经放进去的点有边的联系，就把他建边。注意此时是要跟他的父亲建边，这样是等价的。这样我们就得到了一个父亲人数比儿子多的图，然后遍历整棵树，如果这个点加上他的所有子树大于等于父亲的人数就说明这个点是合法的，最后遍历树，合法的点就是可能的结果。

下面是代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int head[200010],tot;
int father[200010];
struct node {
	int to,nxt;
} e[500010];
struct st {
	int id,val;
} h[200010];
void add(int x,int y) {
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
bool cmp(st a,st b) {
	return a.val <b.val ;
}
int hd[200010],tt;
struct w {
	int to,nxt;
} r[500010];
int vis[200010];
void ad(int x,int y) {
	r[++tt].to=y;
	r[tt].nxt=hd[x];
	hd[x]=tt;
}
int vs[200010],cnt[200010];
int zal[200010];
int find(int x) {
	if(father[x]!=x) {
		father[x]=find(father[x]);
	}
	return father[x];
}
int ans[200010];
void dfs(int u) {
	cnt[u]=zal[u];
	for(int i=hd[u]; i; i=r[i].nxt) {
		int y=r[i].to;
		dfs(y);
		if(cnt[u]<=cnt[y]) {
			vs[y]=1;
		}
	}
	for(int i=hd[u]; i; i=r[i].nxt ) {
		int y=r[i].to;
		cnt[u]+=cnt[y];
	}
}
void dfs2(int u) {
	for(int i=hd[u]; i; i=r[i].nxt ) {
		int y=r[i].to;
		if(vs[y]) {
			ans[y]=1;
			dfs2(y);
		}
	}
}
signed main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		father[i]=i;
	}
	for(int i=1; i<=n; i++) {
		cin>>h[i].val;
		h[i].id=i;
		zal[i]=h[i].val;
	}
	for(int i=1; i<=m; i++) {
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	sort(h+1,h+n+1,cmp);
	for(int i=1; i<=n; i++) {
		for(int j=head[h[i].id]; j; j=e[j].nxt ) {
			int y=e[j].to;//cout<<h[i].id;
			if(vis[y]==1) {
				int a=find(y);
				if(a!=h[i].id) {
					ad(h[i].id,a);
					father[a]=h[i].id;
					//cout<<father[a]<<" "<<h[i].id;
				}
			}
		}
		vis[h[i].id]=1;
	}
	dfs(h[n].id);
	dfs2(h[n].id);
	ans[h[n].id]=1;
	for(int i=1; i<=n; i++) {
		if(ans[i]==1) {
			cout<<1;
		} else cout<<0;
	}
	return 0;
}
```

---

## 作者：541forever (赞：1)

似乎是简单的 kruskal 重构树，我们发现，边权的限制实际上可以当作 $\max(s_i,s_j)$，在这样的情况下，$s_i$ 大的村庄肯定是不受影响的，而 $s_i$ 小的村庄要想走向 $s_i$ 大的那个数本身就要满足这个约束。那么，我们考虑构建出这个图的 kruskal 重构树，注意到，一个村庄能说说服所有村庄，当且仅当他能说服他的父亲且他的父亲能说服所有村庄，而他能说服他的父亲的他这棵子树的子树和大于父亲这个点的权值。那么我们队原图做一遍 dfs 即可。

[Code](https://www.luogu.com.cn/paste/bfpiwu1l)

---

