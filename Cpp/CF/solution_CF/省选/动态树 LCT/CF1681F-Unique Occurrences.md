# Unique Occurrences

## 题目描述

You are given a tree, consisting of $ n $ vertices. Each edge has an integer value written on it.

Let $ f(v, u) $ be the number of values that appear exactly once on the edges of a simple path between vertices $ v $ and $ u $ .

Calculate the sum of $ f(v, u) $ over all pairs of vertices $ v $ and $ u $ such that $ 1 \le v < u \le n $ .

## 样例 #1

### 输入

```
3
1 2 1
1 3 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3
1 2 2
1 3 2```

### 输出

```
2```

## 样例 #3

### 输入

```
5
1 4 4
1 2 3
3 4 4
4 5 5```

### 输出

```
14```

## 样例 #4

### 输入

```
2
2 1 1```

### 输出

```
1```

## 样例 #5

### 输入

```
10
10 2 3
3 8 8
4 8 9
5 8 5
3 10 7
7 8 2
5 6 6
9 3 4
1 6 3```

### 输出

```
120```

# 题解

## 作者：7KByte (赞：33)

原文见[我的博客](https://www.cnblogs.com/7KByte/p/16308773.html)。

>给定一个 $n$ 个结点的树，每条边有一个颜色，记 $f(x,y)$ 表示结点 $x$ 到 $y$ 的路径上只出现了一次的颜色的数量，求 $\sum\limits_{x < y}f(x, y)$ 。数据保证 $n \le 5 \times 10^5$ 。

题面很短，解法很多。

由于我们是求所有 $f(x,y)$ 的总和，根据经验我们将问题转化为对每个颜色 $w$ 计算有多少路径经过恰好一条颜色为 $w$ 的边。这样每种颜色是独立的，可以分开计算。

## 方法一：虚树

很自然我们可以想到虚树的解法，我们将颜色相同的边的两个端点保留下来，建立虚树后直接跑 DP。

## 方法二：二次扫描换根

如果我们设 DP 的状态 $f_i$ 表示以 $i$ 为根子树中，以 $i$ 为起点，不经过颜色 $w$ 的单链数量，同理 $g_i$ 表示删去 $i$ 的子树的数量，那么一条颜色为 $w$ 的边的贡献就是两端 $f,g$ 的乘积。$f$ 可以在 DFS 的同时维护栈求得，然后二次扫描换根求得 $g$。

## 方法三：线段树分治

如果现在考虑颜色 $w$，那么删去所有该颜色的边，求得剩下每个连通块的大小，那么每条颜色 $w$ 的边的贡献就是两端连通块大小的乘积。显然这个过程可以通过线段树分治快速维护。

## 方法四：线段树

固定一个根，如果我们把颜色为 $w$ 的边的深度较深的点记为关键点，考虑用 DS 快速求出方法三中的连通块大小。

我们先将树上每个点赋值为 $1$，将关键点按 DFS 序排序，每次求得子树和记为连通块大小，然后将子树内所有点赋值为 $0$，这些都可以用数据结构快速维护。

-----------------------------------------

代码实现的是方法三，因为好想好写，时间复杂度 $\mathcal{O}(n\log ^2 n)$。

```cpp
#define N 500005
int n, fa[N], sz[N];
inline int get(int x){while(x != fa[x])x = fa[x]; return x;}
vector<Pr>u[N << 2], c[N];
#define ls (x << 1)
#define rs (ls | 1)
void ins(int x,int L,int R,int l,int r,Pr w){
	if(L >= l && R <= r){u[x].pb(w); return;}
	int mid = (L + R) >> 1;
	if(mid >= l)ins(ls, L, mid, l, r, w);
	if(mid < r)ins(rs, mid + 1, R, l, r, w);
}
LL ans;
void solve(int x,int l,int r){
	vector<int>dl;
	go(w, u[x]){
		int p = get(w.fi), q = get(w.se);
		if(sz[p] > sz[q])swap(p, q);
		dl.pb(p), sz[q] += sz[p], fa[p] = q;
	}
	if(l == r)go(w, c[l])ans += sz[get(w.fi)] * 1LL * sz[get(w.se)];
	else {
		int mid = (l + r) >> 1;
		solve(ls, l, mid), solve(rs, mid + 1, r);
	}
	reverse(dl.begin(), dl.end());
	go(w, dl)sz[fa[w]] -= sz[w], fa[w] = w;
}
int main() {
	read(n);
	rp(i, n - 1){
		int x, y, z; read(x, y, z);
		c[z].pb(mp(x, y));
		if(z > 1)ins(1, 1, n, 1, z - 1, {x, y});
		if(z < n)ins(1, 1, n, z + 1, n, {x, y});
	}
	rp(i, n)sz[fa[i] = i] = 1;
	solve(1, 1, n);
	printf("%lld\n", ans);
	return 0;
}
```



---

## 作者：LinkZelda (赞：21)

> 给定一棵 $n$ 个节点的树，每条边有一个颜色 $w_i$，定义 $f(u,v)$ 表示 $u,v$ 的路径上出现恰好一次的颜色数量，求 $\sum_{u<v}f(u,v)$。  

考虑对于每一种颜色，分别计算经过恰好一条这种颜色的边的方案数。

如果删去所有某种颜色的边，剩下一些连通块，然后我们枚举每一条这个颜色的边，把两个大小相乘然后求和，就是这种颜色的贡献了。

考虑优化这个过程，对于每个点 $u$，定义这个点的颜色是**这个点到父亲的这条边颜色**，我们只需要计算以 $u$ 为根的子树内不经过和 $u$ 颜色相同的点可以到达的点数，我们把这个值用 $dp_u$ 表示。

我们可以直接 dfs 计算 $dp_u$，过程中用栈维护每种颜色最近一次出现的且比它深度小的点的编号即可。

然后我们再 dfs 一次，还是用栈维护每种颜色最近一次出现的且比它深度小的点的编号，计算每个点颜色和栈顶元素的两个 $dp$ 值的乘积，然后求和即可。

时间复杂度为 $O(n)$。[代码](https://www.luogu.com.cn/paste/nde46uj7)

---

## 作者：sylqwq (赞：10)

[link](https://www.luogu.com.cn/problem/CF1681F)。

一篇友好的，不需要任何高科技的题解！

感觉做法很多，什么线段树分治、虚树，我都不会，来一个纯线段树做法。

不难发现每一种颜色是可以独立做的。对于一种颜色，我们把这种颜色的边全部删除，这样就形成了若干个连通块。我们定义“两个连通块相邻”，指的是在加入某一条删除的边后这两个连通块能够联通。于是这一种颜色的贡献就是每一对相邻连通块大小的乘积之和。考虑怎么快速求出所有连通块大小，对 dfs 序建立线段树，初始全置为 $1$，把该颜色的边连接的深度较大的点按照 dfs 序降序排序（我们称这些点为“询问点”），然后依次查询询问点的子树和，查完把这棵子树置为 $0$。不难发现，每次询问的这个子树和就是当前询问点下方连通块的大小。

然后再考虑怎么判定“相邻连通块”并计算贡献。对于每一个连通块，我们只考虑计算它和它下面的相邻连通块产生的贡献，这样就做到了不重不漏。我们开一个栈，每次对于一个询问点，和栈内能产生贡献的连通块计算出贡献，然后把这些算过的都弹栈（不难发现，每个连通块只会被其上面的连通块计算一次），然后把当前这个询问点压进栈。由于询问点是按照 dfs 序降序进栈，可以发现，**每一个连通块一定会和当前栈中从栈顶开始的连续的一段产生贡献**。但是和哪些能贡献？设当前询问点为 $u$，当前栈顶询问点为 $v$，若 $u$ 是 $v$ 的祖先则可以贡献。这样每个点进出栈一次，很高效。

还有一个问题：对于每一种颜色，我们要钦定根节点为询问点，这样整棵树最上面的剩余部分就不会漏掉了。

时间复杂度 $O(n\log n)$。

---

## 作者：XLao (赞：7)

长的这么像点分治的题目，怎么会没有点分治的题解。

点分治也是能做的。下面提供一种 $O(n\log n)$ 的做法。

如有任何错误，请大力指出，作者现在脑子不清楚。

---

### $\text{Solution :}$

#### 1.
首先改变一下求和顺序，对每条边单独算贡献。

也就是问每条边（设颜色为 $c$），有多少路径经过他，且路径上不含别的颜色为 $c$ 的边。

$calc(u)$ 时，我们显然只需关心：当前子树内有的颜色，对答案的贡献。

所以点分治大概是能弄出一个复杂度正确的解法。

#### 2.

$calc$ 函数大概是这样的：

设当前处理到 $u$ 的子树 $v$。

$sum_{0,c}$ 表示从 $u$ 到子树 $v$ 内，如果不走颜色为 $c$ 的边，能到多少点。

$sum_{1,c}$ 表示从 $u$ 到子树 $v$ 内，走**恰好一条**颜色为 $c$ 的边，能到多少点。

$pre_{0,c},\space pre_{1,c}$ 表示前几颗子树的 $sum$ 数组和。

要注意把 $u\to v$ 这条边也加进去。

此时容易算出答案。（但是算答案的复杂度不对，“4” 里会讲）

#### 3.

问题是怎么算 $sum$ 数组。

比如一个点，不走颜色 $c_1$ 也能到，不走颜色 $c_2$ 也能到，不走……

那这个点会同时贡献到很多个 $sum_{0,c}$ 里面，

但是我们注意到，如果算 “从 $u$ 到子树 $v$ 内，走 $>0$ 条颜色为 $c$ 的边，能到多少点”，是可以算的。减一下就得到 $sum_{0,c}$ 了。

$dfs$ 时维护从 $u$ 到当前点，每种颜色的边有几条。

如果碰到一条边的颜色（设为 $c$）还没出现过，那么这个边通往的那颗子树内所有点都是“走 $>0$ 条颜色为 $c$ 的边能到的点”。

$sum_{1,c}$ 也是类似求法。

每次求 $sum$ 数组的问题规模是 $O(size_v)$，可以接受。

#### 4.

会注意到，我们如果要算当前子树 $v$ 对前几颗子树的贡献，我们不仅要考虑子树 $v$ 内出现的颜色，还要考虑在前几颗子树出现的颜色。

那样复杂度就错了。

于是我们考虑点分治的一个奇怪 trick，做题太少，今天刚想出来的。

如果我们把所有子树都处理完，然后答案加上 $\sum\limits_{c}pre_{0,c}\times pre_{1,c}$，就包含了所有合法路径，不过多算了一些非简单路径，即所有**不跨子树的**点对被多算了。

那在处理每个子树 $v$ 时减掉就好了。

即每个子树 $v$ 处理完答案都减去 $\sum\limits_{c}sum_{0,c}\times sum_{1,c}$。

此时整个 $calc$ 函数就在 $O(size_u)$ 的复杂度下完成了。

#### 5.

具体实现也很简单，代码里没有求 $sum$ 数组，$cnt$ 数组是 “3” 里引号内的意思。

注意清空和 long long。

代码能力太弱，实现的很丑，常数很大。简单看一下吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+1;

int n,col[N];

struct edge {
	int nex,to,c;
} a[N<<1];
int h[N],tot;
void add(int x,int y,int c) {
	a[++tot]=(edge) {h[x],y,c}, h[x]=tot;
}

int S,rt,size[N],mx[N],vis[N];
void getrt(int u,int f) {
	mx[u]=0, size[u]=1;
	for(int i=h[u]; i; i=a[i].nex) {
		int v=a[i].to;
		if(v!=f && !vis[v]) {
			getrt(v,u);
			size[u]+=size[v];
			mx[u] = max(mx[u], size[v]);
		}
	}
	mx[u] = max(mx[u], S-size[u]);
	if(mx[u]<mx[rt]) rt=u;
}
void init(int u,int f) {
	size[u]=1;
	for(int i=h[u]; i; i=a[i].nex) {
		int v=a[i].to;
		if(v!=f && !vis[v]) init(v,u), size[u]+=size[v];
	}
}
int cnt[2][N],bj[N],tong[N],tt;
void go(int u,int f) {
	for(int i=h[u]; i; i=a[i].nex) {
		int v=a[i].to;
		if(v!=f && !vis[v]) {
			++bj[a[i].c];
			if(bj[a[i].c]==1) cnt[0][a[i].c]+=size[v];
			else if(bj[a[i].c]==2) cnt[1][a[i].c]+=size[v];
			tong[++tt]=a[i].c;
			go(v,u);
			--bj[a[i].c];
		}
	}
}
void clean() {
	for(int j=1; j<=tt; ++j) {
		int c=tong[j];
		bj[c]=cnt[0][c]=cnt[1][c]=0;
	}
	tt=0;
}
long long ans;
void calc(int u) {
//	printf("%d %lld\n",u,ans);
	init(u,0);
	if(size[u]==1) return;
//	for(int i=1;i<=n;++i) printf("%d ",size[i]); puts("--");
	for(int i=h[u]; i; i=a[i].nex) {
		int v=a[i].to;
		if(vis[v]) continue;
//		printf("%d:\n",v);
		++bj[a[i].c];
		cnt[0][a[i].c] = size[v];
		tong[++tt]=a[i].c;
		go(v,u);
		--bj[a[i].c];
		for(int j=1; j<=tt; ++j) {
			int c=tong[j];
			if(bj[c]) continue;
			bj[c]=1;
			int cnt0 = size[v]-cnt[0][c], cnt1 = cnt[0][c]-cnt[1][c];
//			printf("%d %d %d!\n",c,cnt0,cnt1);
			ans -= 1ll*cnt1*cnt0;
		}
		clean();
	}
	go(u,0);
	for(int j=1; j<=tt; ++j) {
		int c=tong[j];
		if(bj[c]) continue;
		bj[c]=1;
		int cnt0 = size[u]-cnt[0][c], cnt1 = cnt[0][c]-cnt[1][c];
		ans += 1ll*cnt0*cnt1;
	}
	clean();
}
void solve(int u) {
	calc(u);
	vis[u]=1;
	for(int i=h[u]; i; i=a[i].nex) {
		int v=a[i].to;
		if(vis[v]) continue;
		rt=0;
		S=size[v];
		getrt(v,u);
		solve(rt);
	}
}

int main() {
	n=read();
	for(int i=1,x,y,c; i<n; ++i) {
		x=read(), y=read(), c=read();
		add(x,y,c);
		add(y,x,c);
	}
	mx[0]=1e9;
	S=n;
	getrt(1,0);
	solve(rt);
	printf("%lld\n",ans);
}
```

---

#### $\text{Postscript :}$

的确，自己写出来一题，比看着题解照着思路写十题有用，成就感也更强。

这题本来完全没思路，还没学线段树分治，但是其实想一想就可做了。

---

## 作者：orz_z (赞：5)

### CF1681F Unique Occurrences

线段树分治练手题，半小时秒了。

考虑对每个颜色 $w$ 计算有多少路径经过恰好一条颜色为 $w$ 的边。

具体地，将所有颜色为 $w$ 的边从原树中删去，对于每一条颜色为 $w$ 的边的两端点连通块大小乘积的和即为这个颜色的答案。

将颜色看作时间线，那么一条颜色为 $w$ 的边建在时间 $[1,w-1]$ 和 $[w+1,n]$ 上，线段树优化即可。

计算连通块大小用并查集即可，线段树分治考虑可撤销并查集。

时间复杂度 $\mathcal O(n\log^2n)$。 

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace Fread
{
	const int SIZE = 1 << 23;
	char buf[SIZE], *S, *T;
	inline char getchar()
	{
		if (S == T)
		{
			T = (S = buf) + fread(buf, 1, SIZE, stdin);
			if (S == T)
				return '\n';
		}
		return *S++;
	}
}

namespace Fwrite
{
	const int SIZE = 1 << 23;
	char buf[SIZE], *S = buf, *T = buf + SIZE;
	inline void flush()
	{
		fwrite(buf, 1, S - buf, stdout);
		S = buf;
	}
	inline void putchar(char c)
	{
		*S++ = c;
		if (S == T)
			flush();
	}
	struct NTR
	{
		~NTR()
		{
			flush();
		}
	} ztr;
}

#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif

//#define int long long
typedef long long ll;
#define ha putchar(' ')
#define he putchar('\n')

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x * f;
}

inline void write(ll x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int _ = 5e5 + 10;

int n, x, y, z, sz[_], fa[_], top;

ll ans;

vector<pair<int, int>> d[_], e[_ << 2];

int find(int x)
{
	while (x ^ fa[x])
		x = fa[x];
	return x;
}

void upd(int o, int l, int r, int L, int R, pair<int, int> pi)
{
	if (L <= l && r <= R)
		return e[o].push_back(pi), void();
	int mid = (l + r) >> 1;
	if (L <= mid)
		upd(o << 1, l, mid, L, R, pi);
	if (R > mid)
		upd(o << 1 | 1, mid + 1, r, L, R, pi);
}

void solve(int o, int l, int r)
{
	vector<int> dl;
	for (auto v : e[o])
	{
		int p = find(v.first), q = find(v.second);
		if (p == q)
			continue;
		if (sz[p] > sz[q])
			swap(p, q);
		dl.push_back(p), sz[q] += sz[p], fa[p] = q;
	}
	if (l == r)
		for (auto v : d[l])
			ans += 1ll * sz[find(v.first)] * sz[find(v.second)];
	else
	{
		int mid = (l + r) >> 1;
		solve(o << 1, l, mid), solve(o << 1 | 1, mid + 1, r);
	}
	reverse(dl.begin(), dl.end());
	for (auto v : dl)
		sz[fa[v]] -= sz[v], fa[v] = v;
}

signed main()
{
	n = read();
	for (int i = 1; i < n; ++i)
	{
		x = read(), y = read(), z = read();
		d[z].push_back({x, y});
		if (z > 1)
			upd(1, 1, n, 1, z - 1, {x, y});
		if (z < n)
			upd(1, 1, n, z + 1, n, {x, y});
	}
	for (int i = 1; i <= n; ++i)
		sz[fa[i] = i] = 1;
	solve(1, 1, n);
	write(ans), he;
	return 0;
}

```



---

## 作者：xfrvq (赞：5)

[$\tt Link$](/problem/CF1681F)。

提供一个虚树动态规划的思路。

你注意到每种颜色的贡献是独立的，所以枚举颜色 $c$，计算 $c$ 颜色的答案。我们用这种颜色的所有边的所有端点建立虚树，然后在虚树上跑 $\tt dp$。

你会发现在虚树上，假如断掉颜色为 $c$ 的边，就会剩下一些「联通块」。而这个颜色的答案就是 **$\sum$ 有边相连的「联通块」的大小乘起来**。这个是因为如果一条路径进入了大于两个「联通块」，那么就会出现两条颜色为 $c$ 的边。

说说 $\tt dp$，你要用 $\tt dp$ 计算出两个数组 $s,t$，其中。

+ $s_i$ 代表 $i$ 子树内和 $i$ 在同个「联通块」的有几个点。
+ $t_i$ 代表 $i$ 子树内与 $i$ 相邻的「联通块」的大小总和。

我们定义 $u,v,w$ 分别为父，子，以及其边权。我们定义 $siz$ 为原树上子树大小。然后考虑转移。

$$
\begin{cases}
s_u=1+\color{red}\sum s_v[w\ne c]\color{black}+\color{blue}siz_u-\sum siz_v\\
t_u=\color{red}\sum t_v[w\ne c]+\color{blue}\sum s_v[w=c]\color{black}
\end{cases}
$$

解释一下：

+ $s$ 的 $1$ 是自己本身
+ $s$ 的红色部分是虚树上所有和它在同个「联通块」的儿子的子树贡献
+ $s$ 的蓝色部分是不在虚树上的儿子的贡献
* $t$ 的红色部分是和它在同个「联通块」的儿子的子树贡献
* $t$ 的蓝色部分是和它在不同「联通块」的儿子的联通块贡献

最后统计答案，应该是每个「联通块」的根，把自己的「联通块」的大小乘上身边「联通块」的大小总和，形式化地，

$$
res=\sum s_ut_u[u=rt\operatorname{or} w(u,fa_u)=c]
$$

问题至此解决。

代码写的很烂，不放了，要可以找我。

---

## 作者：lingfunny (赞：5)

# CF1681F

提供一个不同于 CF 题解的 $O(n)$ 做法。

~~本题解甚至有[英文版](https://codeforces.com/blog/entry/103163?#comment-915879)（（~~

推销 [Edu Rd 题解](https://280800.blog.luogu.org/cf-edu-rd-129-div-2)。~~标签里怎么会有 LCT 呢（雾~~

第一步转有根树先把括号序拍下来，然后对于每一种边权考虑。

对于一种边权 $w$，设拆掉所有边权为 $w$ 的边后分裂成若干棵子树，那么 $w$ 的贡献就是这些边连接的两棵子树的大小的乘积之和。

如下图：

![Snipaste_2022-05-25_15-13-21_.png](https://s2.loli.net/2022/05/25/dNiEUSwzo1v6WD3.png)

边权 $2$ 的贡献为 $3\times3+3\times1=10$。

所以问题可以转化为在一棵树上删掉一些边后，求这些边连接的子树的大小乘积之和。

删边的顺序可以人为规定，不妨设将删边顺序顺序定为 dfs 序，这样的好处后文再说。

考虑在括号序上删掉子树有什么表现：
$$
\texttt{4 5 5 6 7 7 6 1 2 2 3 3 1 4}
$$

$$
\texttt{4 5 5 6 [7 7] 6 [1 2 2 3 3 1] 4}
$$

只需要减掉方括号括起来的所有元素，剩下的元素除以 $2$ 即为**当前子树大小**。

然后用当前子树大小乘上所有**方括号所代表的子树大小**即可。

在这个例子中，方括号所代表的子树大小似乎是方括号的区间长度除以 $2$，实际上并非如此，因为**方括号内部显然可以嵌套方括号**，所以应该递归下去处理子树，返回自己子树大小。

这时候删边顺序定为 dfs 序的好处就体现出来了，每次新增的方括号一定是**嵌套在原有的方括号里面**的（你可以看作初始时有一个 $[1,2n]$ 的方括号），可以递归下去处理。

流程公示：

1. 记当前子树管理的括号序为 $[L,R]$，子树大小为 $\mathrm{siz}=\frac{R-L+1}{2}$，当前处理到第 $p$ 条边。
2. 记每一条边，如果这条边在子树所管的范围内，$\mathrm{siz}$ 减去目标子树大小，递归下去查询这条边，$p$ 应该带**引用**地传递下去（这是时间复杂度的必要保证）。
3. 此时新的 $p$ 一定不会还在刚才查询的那条边的子树内（因为递归处理完了所有字数内的边），同时 $p$ 一定是单调递增的。
4. 返回自己大小。

注意到 $p$ 是单调的，同时递归一定伴随着 $p$ 的增加，边的数量是 $O(n)$ 的，时间复杂度是 $O(n)$ 的。

如果你 WA 了，有可能是没有保证边的单调递增。可以试试下面这个数据：

```plain
input:
5
1 2 1
2 3 1
3 4 1
4 5 1
```

```plain
answer:
4
```

## 参考实现

```cpp
// Problem: F. Unique Occurrences
// From: Codeforces - Educational Codeforces Round 129 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1681/problem/F
// Time: 2022-05-23 22:35
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 5e5+10;

int n, dfn[mxn<<1], dfc, L[mxn], R[mxn];
vector <pair<int, int>> G[mxn], E[mxn];
LL ans;
void dfs(int u, int f) {
	dfn[L[u] = ++dfc] = u;
	for(auto [v, w]: G[u]) if(v != f) E[w].push_back({u, v}), dfs(v, u);
	dfn[R[u] = ++dfc] = u;
}
int solve(int Lp, int Rp, int &p, const vector <pair<int, int>> &E) {
	vector <int> sub;
	int lst = -1, cur = (Rp - Lp + 1)>>1;
	for(int i = p; i < (int)E.size(); ++i) {
		int v = E[i].second;
		if(L[v] > Rp) { p = i-1; break; }
		if(lst == -1 || L[v] > R[lst]) lst = v, cur -= (R[v] - L[v] + 1)>>1, sub.push_back((R[v] - L[v] + 1)>>1);
		else {
			sub.pop_back();
			sub.push_back(solve(L[lst], R[lst], i, E));
		}
		p = i;
	}
	for(int x: sub) ans += (LL)cur*x;
	return cur;
}

signed main() {
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	dfs(1, 0);
	for(int i = 1; i <= n; ++i) if(E[i].size()) {
		int x = 0;
		solve(1, n<<1, x, E[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：luogubot (赞：3)

来点不动脑子的简单 2log 线段树分治。

发现答案的计算方式可以是对于每种颜色的边，将其删除后剩下若干连通块，贡献就是这些边连接的连通块大小的乘积（恰好经过一条该颜色的边），于是线段树分治把删除变为两段存在，也就是颜色为 $c$ 的边在处理颜色 $[1,c-1],[c+1,n]$ 时都存在，用仅按秩合并的并查集维护连通块大小即可，到底层结点枚举对应颜色的所有边计算贡献，复杂度 $O(n\log^2 n)$，跑的不算特别慢。

[代码](https://codeforces.com/contest/1681/submission/159113766) 非常好写。



---

## 作者：E1_de5truct0r (赞：2)

~~线段树分治好题！好题！好题！（破音）~~

## 思路

发现直接枚举无法优化，正难则反，考虑对每条边计算贡献。

我们发现，一条边只经过一次，则显然只能从 **到达这条边的一个较近端点的路径上，不包含其他相同颜色的边的点** 所组成的集合中，选取这条边两端的任意两点，都会产生一次贡献。

因此，考虑维护出这条边两边的符合条件的点的集合。

由于树上路径唯一，而我们要求不能经过相同颜色的边，所以不妨每次先把这些边断开。

于是会形成若干个联通块。发现每条边的贡献就是它两边的联通块大小乘起来。所以只需要维护断开每条边之后，所有的联通块的大小即可。

这个其实很像线段树分治。我们线段树可以基于颜色开一个。然后，我们把每条边的颜色 $w$ 变成“这条边在我们删除颜色 $[1,w-1]$ 和 $[w+1,n]$ 的时候有效”这个条件，然后插入线段树。

最后，遍历一遍线段树，用可撤销并查集维护一下每个联通块的大小和深度（大小用来计算贡献，深度用来按秩合并）。然后此题就做完了。

复杂度 $O(n \log^2 n)$，但是六秒钟时限肯定没问题。（其实最慢的点也只跑了不到 3s。）

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long 

// 省去了缺省源（快读快写和一些手写的 min/max 等函数）。

using namespace std;
const int MAXN=500005;

int fa[MAXN],h[MAXN],sze[MAXN]; // fa 是维护祖先，sze 维护大小，h 维护高度
int find(int k){return fa[k]==k?k:find(fa[k]);}
struct Node{int u,v,add;}; // 用来存储哪些点被合并过

stack<Node> s; // 用来存储撤销操作的时候应该撤销啥

inline void Merge(int u,int v){ // 合并 (u,v)
	int fu=find(u),fv=find(v);
	if(fu==fv) return; // 这里一定加一下，否则它可能会重复合并好多次。
	if(h[fu]<h[fv]) swap(fu,fv); // 按秩合并
	s.push((Node){fu,fv,h[fu]==h[fv]}); // 记录信息（fv 合并到 fu，深度增加了 (h[fu]==h[fv]) 这么多
	h[fu]+=(h[fu]==h[fv]);
	sze[fu]+=sze[fv];
	fa[fv]=fu;
}

vector<pair<int,int> > tr[MAXN<<2],bian[MAXN]; // tr 记录这个节点的边，bian[i] 记录第 i 种颜色的边
void upd(int p,int l,int r,int st,int en,int x,int y){
	if(l>en || r<st) return;
	if(st<=l && r<=en) return tr[p].push_back(make_pair(x,y)),void(); // 插入一条边
	int mid=(l+r)>>1;
	upd(p<<1,l,mid,st,en,x,y);
	upd(p<<1|1,mid+1,r,st,en,x,y);
}

int ans=0;
void solve(int p,int l,int r){ // 遍历线段树求解
	int tmp=s.size(); // 记录一开始没合并的时候栈的大小，方便后面撤销操作
	for(pair<int,int> u:tr[p]) Merge(u.first,u.second); // 合并所有这个节点上的点
	if(l==r){ // 递归到一个颜色了
		for(pair<int,int> u:bian[l]){ // 枚举这种颜色的边
			ans+=(sze[find(u.first)]*sze[find(u.second)]); // 计算贡献
		}
	}else{ // 否则继续递归下去
		int mid=(l+r)>>1;
		solve(p<<1,l,mid);
		solve(p<<1|1,mid+1,r);
	}
	while(s.size()>tmp){ // 可撤销
		Node tmp=s.top(); s.pop();
		h[tmp.u]-=tmp.add;
		sze[tmp.u]-=sze[tmp.v];
		fa[tmp.v]=tmp.v;
	}
}

signed main(){
	int n; read(n);
	for(int i=1;i<=n;i++) fa[i]=i,h[i]=sze[i]=1;
	for(int i=1;i<n;i++){
		int u,v,w; read(u,v,w);
		upd(1,1,n,1,w-1,u,v); // 把边插入线段树
		upd(1,1,n,w+1,n,u,v);
		bian[w].push_back(make_pair(u,v)); // 记录边的集合
	}
	solve(1,1,n); // 遍历线段树计算答案
	write(ans);
	return flush(),0;
}
```

---

## 作者：PersistentLife (赞：2)

博客：[CF DS题选做](https://www.luogu.com.cn/blog/302837/cf-2300-ds-ti-zuo-ti-bi-ji)

题意：给定一棵树，边有边权 $w_i$，定义 $f(u,v)$ 为，$u,v$ 路径上只出现一次的权值个数，求 $\sum_{1\le u < v \le n} f(u,v)$，$1 \le n,w_i \le 5 \times 10^5$。

---
分析：考虑求出每种边权对答案的贡献，将某条权值为 $w$ 的边放到中间（图中标记的边权值为 $w$，其余均不为 $w$）。

将 $<6,7>$ 放在中间。

![1687F P1](https://cdn.luogu.com.cn/upload/image_hosting/c2bcd2uh.png)

考虑能使 $<6,7>$ 产生贡献的路径个数

显然，路径的一端要在 $\{1,3,4,6\}$ 里面选择，另一端在 $\{7,9\}$ 里面选择，可以理解为那些其他同权值的边把树断开了。

如果将所有权值为 $w$ 的边删除，那么某一条权值为 $w$ 的边对答案的贡献为两端连通块大小的乘积。

直接做时间复杂度为 $O(n^2)$，考虑基于值域分值。

定义 $solve(l,r)$ 为，求解所有 $w_i \in [l,r]$ 的边的贡献和，我们可以先将 $w_i \in [l,mid]$ 的所有边加入并查集，然后调用 $solve(mid+1,r)$，结束后将 $w_i \in [l,mid]$ 的所有边撤销，加入 $w_i \in [mid+1,r]$ 的所有边，并调用 $solve(l,mid)$，当 $l=r$ 时，只有一种权值的边没有加入，在并查集上查询求解即可。

由于并查集要可撤销，故不能路径压缩，运用按秩合并保证复杂度，总复杂度为 $O(n \log^2 n)$

此外这题可以用 LCT 求解，枚举到某一个权值，先将对应的边删除，求解，再加入，LCT 中维护树的大小即可，复杂度 $O(n \log n)$

---

## 作者：LroseC (赞：2)

给出一个虚树的实现，和其他题解略有不同。

### 前置知识
* [虚树](https://oi-wiki.org/graph/virtual-tree/)

### 解题思路
显然考虑把贡献的计算放到边上，显然每一条边的贡献就是边两端不经过同颜色边能到达的点数的乘积。

好像有点抽象？那我给一个式子。

设 $f(u,c)$ 表示从点 $u$ 出发，不经过颜色为 $c$ 的边能到达的点的数量。

那么对于每条边 $(u, v)$，若其颜色为 $c$，这条边对答案的贡献显然就是 $f(u, c) \times f(v, c)$。

自然想到考虑枚举每一种颜色算贡献，每次把同种颜色的边的贡献一起算完。然后想一想就觉得可以套上虚树。（然而貌似虚树是本题最毒瘤的做法？

我们考虑把边变成点然后染上对应的颜色，这样每次枚举到颜色 $c$ 的时候，关键点就是颜色为 $c$ 的点。

边变成的点只会往外连两条边，并且虚树会钦定根为 $1$，故其对应的贡献就是走父亲边不经过颜色为 $c$ 的点能到达的点的数量乘上走儿子边不经过颜色为 $c$ 的点能到达的点的数量。

形式化的，设 $f(u,c)$ 表示点 $u$ 不经过颜色为 $c$ 的点能到达的子树中的点的数量，设 $g(u,c)$ 表示点 $u$ 不经过颜色为 $c$ 的点能到达的非子树中节点的数量。

颜色 $c$ 的贡献等于 $\sum_{color(u)=c}f(u,c)\times g(u,c)$。

所以做法就是枚举 $c$，把关键点拿出来建出虚树，dp 出 $f(u,c),g(u,c)$ 两个数组，然后计算贡献即可。

直接 dp 求 $f,g$ 两个数组有点复杂，考虑令 $f(u,c)$ 等于点 $u$ 不经过颜色为 $c$ 的点 **不能** 到达的子树中的点的数量，$g$ 数组同理变成不能。

这样方程会简单很多，讨论会变少。

令 $fa(u)$ 表示 $u$ 在虚树上的父亲。

在虚树上的方程就会变成
$$
f(u) = \sum_{fa(v) = u}
\begin{cases}
f(v), color(v) \neq c\\
size(v), color(v) = c
\end{cases}
$$
相信 $f$ 数组大家都能理解。

$g$ 数组就略微复杂，设 $son(u, v)$ 表示在**原树** 中，$u$ 在 $v$ 方向的儿子。

$$
g(u) =
\begin{cases}
n - size(son(fa(u),u)), color(fa(u)) = c\\
g(fa(u))+f(fa(u)) - 
\begin{cases}
f(u), color(u) \neq c\\
size(u),color(u) = c
\end{cases}
\end{cases}
$$
理解一下，如果父亲颜色为 $c$，我们不能走父亲的其他子树和父亲上面的点。

否则，$g(u) = g(fa(u)) + f(fa(u))$，再减去 $u$ 对 $fa(u)$ 的 $f$ 数组的贡献。

然后这题就写完了。


### 参考代码

CF 上的[提交记录](https://codeforces.com/contest/1681/submission/166085494)，很长，很毒瘤。

---

## 作者：蒟蒻君HJT (赞：2)


## 一、题意：

- 给定一棵 $n$ 个节点的树，每条边有颜色 $c$。

- 求 $\sum_{u=1}^{n} \sum_{v=u+1}^{n} f(u,v)$。

- 其中 $f(u,v)$ 的意义是点 $u$ 到点 $v$ 的简单路径上**恰好出现一次**的颜色的数量。

- $n\in [2,5\cdot 10^5],c\in [1,n]$。

## 二、分析：

显然朴素做法是直接枚举 $u,v$ 并计数，复杂度 $O(n^3)$，不能通过。

稍微优化一下，枚举起点 $u$ 去深度优先搜索整棵树，并沿途记录每种颜色当前的出现次数，搜到一个点 $v$ 就把 $f(u,v)$ 累加进答案，搜完子树后回溯，可以将时间复杂度降低到 $O(n^2)$，还是不能通过。

可以考虑拆贡献。即不去枚举路径，而是去枚举每条边能在多少个点对的路径间对答案产生 $1$ 的贡献：钦定路径通过当前在枚举的边，控制该路径不能通过其他相同颜色的边。

任意一条边将整棵树切分成一个子树和一个缺角的大树。如果如上述一般来做的话事情就会变得非常麻烦，因为我们很难通过某一简单数据结构维护其他那些相同颜色的边能使多少个点对变得不可能。

很自然地，我们在本题非常关心的是边的颜色（的相同与否）。那么，可以按照每一种颜色来计算，即枚举颜色，把这些颜色所对应的边找出来，然后全局考虑贡献。这样的枚举复杂度依旧是 $O(n)$，因为每条边还是只会被枚举一次。

请看以下例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/j16bdlyk.png)

当前正在考虑颜色为 $c$ 的所有边。实线代表颜色不为 $c$ 的边，而两条虚线代表颜色为 $c$ 的边。可以容易发现，整棵树被切分成了 $3$ 个连通块（当然也是树），每个连通块有唯一的深度最浅的“根节点。

再进一步观察这张图，我们需要统计的是经过恰好一条虚线边的路径数量。这是什么呢？这就是在**任意两个相邻连通块**中各选一个点，然后在这两个点间的路径！不能在一个连通块中，这种情况不经过虚线边；也不能在非相邻的连通块间，因为这时候一定跨过了一个或多个整块连通块，从而经过了至少两条虚线边。

建议在这里好好想想。

假设颜色为 $c$ 的边的数量为 $T$。冷静下来可以发现，虽然连通块数量为 $O(T)$，但相邻连通块的配对数也是 $O(T)$ 的，不可能达到 $O(T^2)$。所以，枚举这个相邻关系的复杂度也是可以接受的。两个相邻连通块产生的贡献，显然就是它们的大小（所包含节点个数）的乘积。比如，上图颜色为 $c$ 的边产生的总贡献就是 $2\times 5 + 2\times 5 = 20$。

## 三、解题方法：

不妨钦定整棵树的根节点为 $1$ 号点。

先枚举好颜色，把所有包含该颜色的边 $R(u,v)$ 取出来。

根据上文的分析，我们需要什么？

- 1. 每个连通块的大小。

- 2. 每条边 $R(u,v)$ 连接了两个点 $u,v$（$u$ 为 $v$ 的父节点） ，它们分别属于哪个连通块。

我们在每个连通块的根节点处计算它的大小。这样的话，第二条中的 $v$ 的所属非常简单，重点在于找出 $u$ 的所属。

怎么计算每个连通块的大小？由于连通块可以是奇形怪状的，所以看起来非常麻烦。我们换一种思路。

考虑某一个连通块，它的根节点是 $p$。记整棵树中，以 $x$ 点为根节点的子树大小为 $Size_x$，那么这个连通块的大小 $S_p$ 可以表示为 $S_p=Size_p-\sum_{y}S_y$，其中 $y$ 为在 $p$ 的子树中（不包括 $p$ 点）的所有连通块的根节点。 

我们在预处理每个子树大小的时候顺便求出每个点 $x$ 的 dfs 序 $dfn_x$，于是有一个常见结论：若点 $y$ 在点 $z$ 的子树中，则 $dfn_y\in [dfn_z,dfn_z+Size_z-1]$，$Size_z$ 表示子树 $z$ 的大小。

因此，取出所有颜色为 $c$ 的边 $R(u,v)$ 后（别忘了 $u$ 是 $v$ 的父节点），**我们将所有 $v$ 点按照 $dfn_v$ 降序排序**（这实际上是为了保证遍历完整棵子树中的所有点之后再遍历这棵子树的根节点），然后从前往后遍历这些排好序的点，计算 $S_v=Size_v-\sum_{x,dfn_x\in [dfn_v,dfn_v+Size_v-1]}S_x$。（注意区分 $S$ 和 $Size$！）这个算式可以抽象成区间查询和以及单点修改，用树状数组维护即可。

有一个小小的注意点：在刚才的过程中根节点 $1$ 号点并未被考虑到，它所在连通块的大小可以用 $n-\sum_{x}S_x$（即减去其他连通块的大小）来简单表示。

好了，现在唯一剩下的问题就是对于边 $R(u,v)$，如何求出点 $u$ 所在连通块的根节点编号。这一块也挺奇思妙想的。我们先在整棵树上给所有点 $v$（即所有连通块的根节点）打上 $+1$ 的标记，然后再记 $f_x$ 表示从点 $x$ 回到根节点的路径上，标记的总和是多少。$f_x$ 的维护非常简单，再开一个差分树状数组，找出所有 $v$ 后，对每个 $v$ 执行 $[dfn_v,dfn_v+Size_v-1]$ 的区间 $+1$ 即可。

再拿出之前的例子（为了看的清楚，我只标注了 $f_x$ 的信息，树的形态是完全相同的）：

![](https://cdn.luogu.com.cn/upload/image_hosting/tmdyjkb9.png)

拿 $(4,6)$ 这条边来举例。我们发现，要找出 $4$ 号点所在连通块的根节点，就是找出 $4$ 号点的某一祖先 $Anc$（当然也可以是它自己），使得 $f_4=f_{Anc}$ 且 $Anc$ 的深度最浅。这是有单调性的，也就是说一个深度较浅的祖先 $A$ 如果满足 $f_4=f_A$，那么深度更深的祖先 $B$ 也一定满足 $f_4=f_B$。因此，我们使用树上倍增。预处理每个点在树上的 $2^k$ 级祖先 $k\in [0,19]$，然后尝试从 $u$ 点往上跳，检查即将要跳到的的点 $t$，在差分树状数组上单点查询 $f_t$，若 $f_t=f_u$，则跳上去；否则不跳。最终跳到的节点 $q$ 就是 $u$ 点所在连通块的根节点。将 $S_q\times S_v$ 累加进答案即可。

整段代码的时间复杂度为 $O(n\log^2n)$，瓶颈在于倍增过程，但这个过程实际上是卡不满的，所以可以通过本题。

最后别忘了处理完某一种颜色之后，撤回在两个树状数组上执行的所有操作。

## 四、代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
const int N=500005;
int n,col[N],nxt[N*2],ver[N*2],head[N],tot=0,fa[N],c[N*2];
int dfn[N],siz[N],dsum=0,nf,anc[20][N],d[N],cnt,Ans=0,Siz[N];
vector<int>vc[N];
void adde(int x,int y,int z){
	++tot,
	nxt[tot]=head[x],
	head[x]=tot;
	ver[tot]=y;
	c[tot]=z;
	return ;
}
void dfs(int x){
	dfn[x]=++dsum;
	siz[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		if(ver[i]==fa[x]) continue;
		fa[ver[i]]=x;
		col[ver[i]]=c[i];
		vc[col[ver[i]]].push_back(ver[i]);
		dfs(ver[i]);
		siz[x]+=siz[ver[i]];
	}
	return ;
}
bool cmp(int x,int y){
	return dfn[x]>dfn[y];
}
int C1[500005];
int ask1(int x){
	int r=0;
	for(int i=x;i;i-=lowbit(i)) r+=C1[i];
	return r;
}
void add1(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)) C1[i]+=y;
	return ;
}
int qry(int x,int y){
	return ask1(y)-ask1(x-1);
}
int C2[500005];
int ask2(int x){
	int r=0;
	for(int i=x;i;i-=lowbit(i)) r+=C2[i];
	return r;
}
void add2(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)) C2[i]+=y;
	return ;
}
void modify(int x,int y,int z){
	add2(x,z);
	if(y!=n) add2(y+1,-z);
	return ;
}
signed main(){
	scanf("%lld",&n);
	int x,y,z;
	for(int i=1;i<=n-1;++i){
		scanf("%lld%lld%lld",&x,&y,&z);
		adde(x,y,z);
		adde(y,x,z);
	}
	dfs(1);
	for(int i=1;i<=n;++i) anc[0][i]=fa[i];
	for(int i=1;i<=19;++i){
		for(int j=1;j<=n;++j){
			anc[i][j]=anc[i-1][anc[i-1][j]];
		}
	}
	for(int i=1;i<=n;++i){
		nf=n;
		if(vc[i].size()==0) continue;
		int s=vc[i].size();
		for(int j=0;j<s;++j){
			d[j+1]=vc[i][j];
			modify(dfn[d[j+1]],dfn[d[j+1]]+siz[d[j+1]]-1,1);
		}
		modify(1,n,1);
		sort(d+1,d+s+1,cmp);
		for(int j=1;j<=s;++j){
			Siz[d[j]]=siz[d[j]]-qry(dfn[d[j]],dfn[d[j]]+siz[d[j]]-1);
			add1(dfn[d[j]],Siz[d[j]]);
			nf-=Siz[d[j]];
		}
		Siz[1]=nf;
		for(int j=1;j<=s;++j){
			int nw=fa[d[j]],T;
			int r=19;
			T=ask2(dfn[nw]);
			while(r>=0){
				if(anc[r][nw]!=0 && T==ask2(dfn[anc[r][nw]])){
					nw=anc[r][nw];
				}
				--r;
			}
			Ans+=1ll*Siz[nw]*Siz[d[j]];
		}	
		for(int j=1;j<=s;++j){
			add1(dfn[d[j]],-Siz[d[j]]);
			modify(dfn[d[j]],dfn[d[j]]+siz[d[j]]-1,-1);
		}
		modify(1,n,-1);
	}
	printf("%lld\n",Ans);
	return 0;
}
```

码字不易，求点赞~~

---

## 作者：MatrixCascade (赞：1)

显然每一种颜色是独立的，考虑分别计算每种颜色的答案。想到这里发现好像随便虚树一下就做完了。

但我不想写虚树，考虑用更无脑的做法  

假设我们在统计颜色为 $w$ 的答案，那么你可以先把所有颜色是 $w$ 的边断开，发现形成了若干个连通块，$w$ 这个颜色的贡献和就是 $\sum\limits_{(u,v),col(u,v)=w}siz_u\times siz_v$（$siz_x$ 为 $x$ 所在连通块的大小），因为一条路径上只能有一条颜色是 $w$ 的边。

这个东西直接用 lct 维护子树信息来实现加边删边，就做完了。

[代码](https://codeforces.com/contest/1681/submission/158768144)

---

## 作者：FelFa_1414666 (赞：1)

[传送门](https://codeforces.com/contest/1681/problem/F)

---

## Analysis

不妨设 $g(x)$ 为**边权为 $x$ 的边被且仅被经过 1 次的路径个数**。那么答案为 $\sum_{i=1}^ng(x)$。

接下来分析对于特定 $x$，如何去求得 $g(x)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/xcv3v27n.png)

以这棵树为例，我们设当前要求 $g(2)$，即通过且仅通过边权为 2 的边一次的路径个数。

我们将所有边权为 2 的边删去，得到下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/nyzu6uxd.png)

然后发现由于边的断开，这棵树分成了若干个连通块。观察发现，对于每条边权为 2 的边，它对答案的贡献就是它**连接的两个连通块节点个数的乘积**(确定路径的起点和终点)。

我们沿着这个思想，来考虑如何求得所有的 $g(x)$。

---

## Solution 1

第一种解法是**并查集分治**。

要处理区间  $[l,r]$ 内所有边权的 $g(x)$ 之和，每次可以从中点将区间分成两半，递归求解左半段时，就将右半段所有边连上；递归求解右半段时，先把右半段所有边断开，再把左半段所有点连上。

这样当我们递归到某个确切的边权 $w$ 时，除了 $w$ 以外其他边权的所有边都连上了，对每个边权为 $w$ 的边求两个端点所在连通块节点个数的乘积。

这一过程可以用**栈 + 并查集**维护。并查集只能写按秩合并，不写路径压缩，否则无法撤销边。栈内存当前连上的所有边，递归结束回溯时就把栈内多出来的边都撤销。

因为并查集没有路径压缩，所以时间复杂度多了一个 $\operatorname O(\log n)$。

### Code

tourist 大神的现场代码 orz。

```cpp
/**
 *    author:  tourist
 *    created: 23.05.2022 18:44:02       
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    --a; --b; --c;
    g[c].emplace_back(a, b);
  }
  vector<int> p(n);//并查集
  iota(p.begin(), p.end(), 0);
  vector<int> sz(n, 1);
  vector<pair<int, int>> ops;//栈，存储当前所有连起来的边
  auto Get = [&](int i) {//并查集找根
    while (i != p[i]) {
      i = p[i];
    }
    return i;
  };
  auto Unite = [&](int i, int j) {//按秩合并
    i = Get(i);
    j = Get(j);
    if (i != j) {
      if (sz[i] > sz[j]) {
        swap(i, j);
      }
      ops.emplace_back(i, p[i]);
      p[i] = j;
      ops.emplace_back(~j, sz[j]);
      sz[j] += sz[i];
    }
  };
  auto Rollback = [&](int T) {//撤销边
    while ((int) ops.size() > T) {
      int i = ops.back().first;
      int j = ops.back().second;
      ops.pop_back();
      if (i >= 0) {
        p[i] = j;
      } else {
        sz[~i] = j;
      }
    }
  };
  long long ans = 0;
  function<void(int, int)> Dfs = [&](int l, int r) {//分治函数
    if (l == r) {
      for (auto& p : g[l]) {
        int x = Get(p.first);
        int y = Get(p.second);
        ans += (long long) sz[x] * sz[y];
      }
      return;
    }
    int mid = (l + r) >> 1;
    {
      int save = (int) ops.size();
      bool fail = false;
      for (int i = mid + 1; i <= r; i++) {
        for (auto& p : g[i]) {
          Unite(p.first, p.second);
        }
      }
      Dfs(l, mid);
      Rollback(save);
    }
    {
      int save = (int) ops.size();
      bool fail = false;
      for (int i = l; i <= mid; i++) {
        for (auto& p : g[i]) {
          Unite(p.first, p.second);
        }
      }
      Dfs(mid + 1, r);
      Rollback(save);
    }
  };
  Dfs(0, n - 1);
  cout << ans << '\n';
  return 0;
}

```

时间复杂度：$\operatorname O(n\log^2 n)$

空间复杂度：$\operatorname O(n)$

---

## Solution 2

沿用同样的思想，但是我们考虑一次性 dfs 求出所有的 $g(x)$ 。

首先 dfs 一次预处理每个节点子树的节点个数 $sz_u$。

再次 dfs，过程中，对于每一个边权 $w$，记录 $cur_w$ 表示当前所在的被 $w$ 分开的连通块编号、序列 ${x_w}_i$ 表示当前被 $w$ 分开的连通块中第 $i$ 个的节点数，以及 ${fa_w}_i$ 表示其父亲连通块的编号。

每次向下走，设经过的边权为 $w$，到达的节点为 $u$。就新产生了一个新的被边权为 $w$ 的边分开的连通块 ${x_w}_i=sz_u$，且 ${fa_w}_i=cur_w$。同时令 ${x_w}_{cur_w}\gets {x_w}_{cur_w}-sz_u$。下一步递归时 $cur_w\gets i$。

如此 dfs 完整棵树，就得到了所有边权对应的所有连通块，以及与之相邻的父亲连通块。

对所有边权 $w$，有 $g(w)=\sum_i{x_w}_i\times {x_w}_{{fa_w}_i}$。

接下来放出鄙人现场写的拙劣的 AC 代码。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
int n,ans,sz[500005],cur[500005];
vector<int> fa[500005],x[500005];
vector<pii> G[500005];//邻接表
void dfs0(int u,int p)//预处理每个子树节点个数
{
	sz[u]=1;
	for(auto pp:G[u])
		if (pp.F!=p)
		{
			int to=pp.F;
			dfs0(to,u);
			sz[u]+=sz[to];
		}
}
void dfs(int u,int p)//核心代码
{
	for(auto pp:G[u])
		if (pp.F!=p)
		{
			int to=pp.F,w=pp.S;
			x[w].pb(sz[to]);
			fa[w].pb(cur[w]);
			x[w][cur[w]]-=sz[to];
			int tmp=cur[w];
			cur[w]=(int)x[w].size()-1;
			dfs(to,u);
			cur[w]=tmp;
		}
}
signed main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n;
	for(int i=0;i<n-1;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;--u,--v,--w;
		G[u].pb(mp(v,w));
		G[v].pb(mp(u,w));
	}
	dfs0(0,-1);
	for(int w=0;w<n;w++)//初始化
		x[w].pb(sz[0]),fa[w].pb(-1);
	dfs(0,-1);
	for(int w=0;w<n;w++)
		for(int i=0;i<(int)x[w].size();i++)
			if (fa[w][i]!=-1)
				ans+=x[w][i]*x[w][fa[w][i]];//求答案
	cout<<ans<<endl;
	return 0;
}
```

时间复杂度：$\operatorname O(n)$

空间复杂度：$\operatorname O(n)$



---

