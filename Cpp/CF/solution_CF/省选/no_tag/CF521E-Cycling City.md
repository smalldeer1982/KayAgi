# Cycling City

## 题目描述

You are organizing a cycling race on the streets of the city. The city contains $ n $ junctions, some pairs of them are connected by roads; on each road you can move in any direction. No two roads connect the same pair of intersections, and no road connects the intersection with itself.

You want the race to be open to both professional athletes and beginner cyclists, and that's why you will organize the race in three nominations: easy, moderate and difficult; each participant will choose the more suitable nomination. For each nomination you must choose the route — the chain of junctions, consecutively connected by roads. Routes must meet the following conditions:

- all three routes should start at the same intersection, and finish at the same intersection (place of start and finish can't be the same);
- to avoid collisions, no two routes can have common junctions (except for the common start and finish), and can not go along the same road (irrespective of the driving direction on the road for those two routes);
- no route must pass twice through the same intersection or visit the same road twice (irrespective of the driving direction on the road for the first and second time of visit).

Preparing for the competition is about to begin, and you need to determine the routes of the race as quickly as possible. The length of the routes is not important, it is only important that all the given requirements were met.

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 4
4 1
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
5 6
1 2
1 3
1 4
2 5
3 5
4 5
```

### 输出

```
YES
3 5 4 1
3 5 3 1
3 5 2 1
```

# 题解

## 作者：Kewth (赞：35)

其实这题的想法可以暴力一点的。。。


存在两个点之间有三条不相交的路径等价于存在两个环有边相交。这又等价于对于一颗生成树，**存在一条树边同时被两条非树边覆盖**。

用树上差分可以求出每条树边的覆盖次数进而进行判定，但是并没有必要，更主要的问题是树上差分虽然可以判断可行性，但**难以给出一组方案**。

直接暴力枚举非树边暴力覆盖，**只要有一条树边的覆盖次数达到了 2 就可以退出了**，因此只需要记每条树边被哪条非树边覆盖，如果覆盖 (a, b) 的时候发现有一条边已经被 (c, d) 覆盖了，那么根据 (a, b) 和 (c, d) 就可以得到方案。

不妨令 dfs 树作为生成树，令 b 为 a 的祖先，d 为 c 的祖先，b 的深度比 d 的深度浅。

不需要任何分类讨论，画个图就很容易明白，三条路径铁定就是：

- d -> lca(a, c)
- d -> b -> a -> lca(a, c)
- d -> c -> lca(a, c)

![灵魂画手](https://cdn.luogu.com.cn/upload/image_hosting/062uwbm4.png)

~~灵魂画手上线~~

求 lca 可以暴力求，路径也可以暴力找。

做法虽然暴力，**复杂度却是线性的**。

实现的时候可以一边 dfs 一边暴力覆盖，以下参考实现：

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 200005;
std::vector<int> G[maxn];
bool vis[maxn], ins[maxn];
int fa[maxn], deep[maxn];
int cx[maxn], cy[maxn];

int lca(int x, int y) {
	while(deep[x] > deep[y]) x = fa[x];
	while(deep[y] > deep[x]) y = fa[y];
	while(x != y) x = fa[x], y = fa[y];
	return x;
}

int tmp[maxn], tp;
void print() {
	printf("%d", tp);
	for(int i = 1; i <= tp; i ++)
		printf(" %d", tmp[i]);
	puts("");
	tp = 0;
}

void add_path(int x, int y) {
	while(x != y) {
		tmp[++ tp] = x;
		x = fa[x];
	}
	tmp[++ tp] = y;
}

void get(int a, int b, int c, int d) {
	if(deep[b] > deep[d]) {
		std::swap(a, c);
		std::swap(b, d);
	}
	int e = lca(a, c);

	puts("YES");

	add_path(e, d);
	std::reverse(tmp + 1, tmp + tp + 1);
	print();

	add_path(d, b);
	add_path(a, e);
	print();

	tmp[++ tp] = d;
	add_path(c, e);
	print();

	exit(0);
}

void dfs(int u) {
	deep[u] = deep[fa[u]] + 1;
	vis[u] = ins[u] = 1;
	for(int v : G[u])
		if(v != fa[u]) {
			if(!vis[v]) {
				fa[v] = u;
				dfs(v);
			}
			else if(ins[v]) {
				for(int x = u; x != v; x = fa[x])
					if(cx[x] and cy[x])
						get(cx[x], cy[x], u, v);
					else {
						cx[x] = u;
						cy[x] = v;
					}
			} 
		}
	ins[u] = 0;
}

int main() {
	int n = read, m = read;
	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i = 1; i <= n; i ++)
		if(!vis[i])
			dfs(i);
	puts("NO");
}
```

---

## 作者：Caiest_Oier (赞：5)

# [CF521E](https://www.luogu.com.cn/problem/CF521E)   
首先我们搞出图的一棵 dfs 树（注意不是任意生成树都可以）。因为是张无向图，所以只存在前向边、树边与返祖边，不存在横叉边。这是一个非常有用的性质。    

考虑存在满足要求的点对会是什么情况，首先我们不选择互相没有祖先关系的点，因为这样的话一定在二者 $lca$ 处会有满足条件的另一对点且它们有祖先关系。对于两个存在祖先关系的点，二者中间已经存在一条由树边构成的路径，则如果有两条返祖边覆盖二者之间的路径，这两条返祖边一定可以构成两组新路径，并且这很明显也是必要条件。于是问题就解决了。对于每一条返祖边，不断往上覆盖，如果与另一条返祖边边的覆盖重合，则把重合路径取出来，构造答案即可。复杂度 $O(m+n)$，即 dfs 树的生成与边的覆盖。    

丑陋的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k1,k2,k3,k4,k5,k6,k7,k8,k9,fa[500003],mk[500003][2],dfn[500003],idx,st,ed,rem;
vector<int>E[500003];
void dfs(int now){
	dfn[now]=++idx;
	for(auto i:E[now]){
		if(i!=fa[now]&&dfn[i]==0){
			fa[i]=now;
			dfs(i);
		}
	}
	return;
}
int stk[2000003],tot;
void getlj(int bg,int tn1,int tn2,int fn){
	tot=0;
	k1=bg;
	while(1){
		stk[++tot]=k1;
		if(k1==tn1)break;
		k1=fa[k1];
	}
	k1=tn2;
	while(1){
		stk[++tot]=k1;
		if(k1==fn)break;
		k1=fa[k1];
	}
	printf("%d ",tot);
	for(int i=1;i<=tot;i++)printf("%d ",stk[i]);
	printf("\n");
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&k1,&k2);
		E[k1].emplace_back(k2);
		E[k2].emplace_back(k1);
	}
	for(int i=1;i<=n;i++){
		idx=0;
		if(!dfn[i])dfs(i);
	}
	for(int i=1;i<=n;i++){
		for(auto j:E[i]){
			if(j==fa[i]||fa[j]==i||dfn[i]<dfn[j])continue;
			k1=i;
			while(k1!=j){
				if(mk[k1][0]!=0){
					if(ed!=0&&(mk[k1][0]!=mk[ed][0]||mk[k1][1]!=mk[ed][1]))break;
					if(ed==0)ed=k1;
					st=fa[k1];
				}
				else{
					mk[k1][0]=i;
					mk[k1][1]=j;
				}
				k1=fa[k1];
			}
			if(st!=0){
				puts("YES");
				tot=0;
				k1=ed;
				while(1){
					stk[++tot]=k1;
					if(k1==st)break;
					k1=fa[k1];
				}
				printf("%d ",tot);
				for(int i=tot;i;i--)printf("%d ",stk[i]);
				printf("\n");
				getlj(st,j,i,ed);
				getlj(st,mk[ed][1],mk[ed][0],ed);
				return 0;
			}
		}
	}
	puts("NO");
	return 0;
}
```


---

## 作者：ningago (赞：4)

没有思维的智儿做法。

首先三条路径的问题，肯定不弱于两条路径的问题，故对于每个点双而言，答案是独立的。

若该点双是树边或单环，显然不存在答案。

否则对于该点双中的任意一个环，必然存在一条环外的路径连接环上两个点（否则是单环），也就是说存在答案。

随便搜出一个环，找一个环上度数大于三的点把路径搜出来即可。

由于是简单图，细节会比较少。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctype.h>
#include <cmath>
#include <vector>
#include <queue>
#include <numeric>
#include <map>

char ST;
//#define int long long
#define ll long long
#define inf 0x3f3f3f3f
//#define inf 0x3f3f3f3f3f3f3f3f
int read()
{
	int x = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(;  isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

int readstr(char *str, int base)
{
	int len = base - 1;
	char c = getchar();
	for(; !isalpha(c) && !isdigit(c) && c != '.' && c != '*' && c != '#'; c = getchar());
	for(;  isalpha(c) ||  isdigit(c) || c == '.' || c == '*' || c == '#'; c = getchar()) str[++len] = c;
	return len;
}

#define debug(...) fprintf(stderr, __VA_ARGS__)
#define gline debug("now is #%d\n", __LINE__)
#define pii std::pair <int, int>
#define mkp std::make_pair
#define fi first
#define se second

template <typename T> void ckmax(T &x, T y) { x = x > y ? x : y; }
template <typename T> void ckmin(T &x, T y) { x = x < y ? x : y; }
template <typename T> T max(T x, T y) { return x > y ? x : y; }
template <typename T> T min(T x, T y) { return x < y ? x : y; }
#define mod 998244353
//#define mod 1000000007

void plus_(int &x, int y) { x = x + y >= mod ? x + y - mod : x + y; }
void mul_(int &x, int y) { x = 1ll * x * y % mod; }
int ksm(int a, int b)
{
	int res = 1;
	for(; b; b >>= 1, mul_(a, a)) if(b & 1) mul_(res, a);
	return res;
}

#define N 200010
int n, m;
int h[N], e[N << 1], ne[N << 1], from[N << 1], idx = -1;
void add_edge(int x, int y) { ne[++idx] = h[x], h[x] = idx, from[idx] = x, e[idx] = y; }
void add(int x, int y) { add_edge(x, y), add_edge(y, x); }
int dfn[N], low[N];
int sta[N], top;
int x_[N], y_[N], edgecnt;
int tmp[N], vis[N], nodecnt;
bool ok; int flag;
int nxt[N], pre[N];
void dfs1(int k, int S, int in_edge)
{
	vis[k] = 1; sta[++top] = k;
	for(int i = h[k]; ~i; i = ne[i])
	{
		if(i == in_edge) continue;
		int nx = e[i];
		if(vis[nx]) { if(nx == S) { nxt[k] = S, pre[S] = k, flag = 1; return; } }
		else nxt[k] = nx, pre[nx] = k, dfs1(nx, S, i ^ 1);
		if(flag) return;
	}
	vis[k] = 0, top--;
}
bool viss[N];
int dfs2(int k, int in_edge, int S)
{
	if(vis[k]) 
	{
		if(k != S)
			return k;
		return 0;
	}
	viss[k] = 1;
	for(int i = h[k]; ~i; i = ne[i])
	{
		if(i != in_edge && !viss[e[i]]) 
		{
			tmp[++nodecnt] = e[i];
			int t = dfs2(e[i], i ^ 1, S);
			if(t) return t;
			nodecnt--;
		}
	}
	viss[k] = 0;
	return 0;
}
void calc()
{
	memset(vis, 0, sizeof(vis));
	memset(h, idx = -1, sizeof(h));
	n = nodecnt, m = edgecnt;
	for(int i = 1; i <= m; i++)
		add(x_[i], y_[i]);
	top = 0;
	dfs1(tmp[1], tmp[1], -1);
	std::sort(sta + 1, sta + 1 + top);
	for(int _ = 1; _ <= top; _++)
	{
		int k = sta[_];
		flag = 0;
		int in_e = 0;
		for(int i = h[k]; ~i; i = ne[i])
		{
			int nx = e[i];
			if(nx != nxt[k] && nx != pre[k]) flag = nx, in_e = i;
			else continue;
		}
		if(flag)
		{
			tmp[nodecnt = 1] = k;
			tmp[nodecnt = 2] = flag;
			int ed = dfs2(flag, in_e ^ 1, k), tot = 0;
			printf("YES\n");
			if(nodecnt > n) { printf("??? %d %d %d %d %d\n", k, flag, ed, nodecnt, tmp[nodecnt]); return; }
			for(int p = k; ; p = pre[p]) { tot++; if(p == ed) break; } printf("%d ", tot);
			for(int p = k; ; p = pre[p]) { printf("%d ", p); if(p == ed) break; }
			putchar('\n'); tot = 0;
			for(int p = k; ; p = nxt[p]) { tot++; if(p == ed) break; } printf("%d ", tot);
			for(int p = k; ; p = nxt[p]) { printf("%d ", p); if(p == ed) break; }
			putchar('\n'); printf("%d ", nodecnt);
			for(int p = 1; p <= nodecnt; p++) { printf("%d ", tmp[p]); }
			putchar('\n');
			return;
		}
	}
}
void tarjan(int k, int in_edge)
{
	dfn[k] = low[k] = ++dfn[0];
	for(int i = h[k]; ~i; i = ne[i])
	{
		if(i == in_edge) continue;
		int nx = e[i];
		if(!dfn[nx])
		{
			sta[++top] = i;
			tarjan(nx, i ^ 1);
			if(ok) return;
			ckmin(low[k], low[nx]);
			if(low[nx] > dfn[k])
				top--;
			else if(low[nx] == dfn[k])
			{
				nodecnt = edgecnt = 0;
				while(1)
				{
					int v = sta[top--];
					x_[++edgecnt] = from[v];
					y_[edgecnt] = e[v];
					if(!vis[e[v]]) vis[tmp[++nodecnt] = e[v]] = 1;
					if(v == i) break;
				}
				if(edgecnt != nodecnt) { ok = 1; calc(); }
				else for(int i = 1; i <= nodecnt; i++) vis[tmp[i]] = 0;
			}
		}
		else if(dfn[nx] < dfn[k])
		{
			ckmin(low[k], dfn[nx]);
			sta[++top] = i;
		}
	}
}

void solve()
{
	n = read(), m = read();
	for(int i = 1, x, y; i <= m; i++) x = read(), y = read(), add(x, y);
	for(int i = 1; !ok && i <= n; i++)
		if(!dfn[i])
			tarjan(i, -1);
	if(!ok) printf("NO\n");
}

char ED;
signed main()
{
	memset(h, idx = -1, sizeof(h));
	int T = 1; while(T--) solve();
	return 0;
}


```

---

## 作者：Feyn (赞：3)

给出一种实现上可能不是非常简洁，但应该很好理解的写法。本题解代码向，思路可以参照其它更加详细的题解。

我用的是在生成树上找被覆盖两次边的做法。前面求生成树森林的部分太简单了就略过，然后我们需要做的就是给一条非树边染色。大概代码是：

```cpp
for(int i=1;i<=n;i++){
	int x=a[i].x,y=a[i].y;int ll=lca(x,y),color=0;
	while(x!=ll){if(c[x])return found(c[x],i),0;c[x]=i;x=f[x];}
	while(y!=ll){if(c[y])return found(c[y],i),0;c[y]=i;y=f[y];}
}
```

大概就是说如果发现要染色的边已经染过色了，那么说明肯定存在一种合法解，返回即可。而在 found 函数中，我们需要做的主要有两个：

- 找出两个环的交。
- 输出三条路径的方案。

对于前者有暴力的想法是说给两个环上的点分别染色，这样一来就可以找到两个环的交了。另外同时我们还需要确定起点和终点，发现如果把交的部分抽离出来，起点和终点的度数都是 $1$，只需要统计一下度数即可。

```cpp
makeColor(x,cx);makeColor(y,cy);//染色
for(int i=1;i<=m;i++)cc[i]=cx[i]&&cy[i];
for(int wh=1;wh<=m;wh++)
	if(cc[wh])for(int i=head[wh];i;i=e[i].nxt)nowD[e[i].t]++;//统计度数
int px=0,py=0;
for(int i=1;i<=m;i++)
	if(cc[i]&&nowD[i]==1)px==0?(px=i):(py=i);//找到路径的起始点和终点
```

要输出的三条路径中有一条是很简单的，就是树上的一条路径。于是可以：

```cpp
vector<int> findPath(int s,int t){
	int ll=lca(s,t);vector<int>ans,rem;
	while(t!=ll)rem.push_back(t),t=f[t];
	while(s!=ll)ans.push_back(s),s=f[s];
	ans.push_back(ll);for(int i=rem.size()-1;i>=0;i--)ans.push_back(rem[i]);
	return ans;
}
inline void printPath(vector<int>ans){
	printf("%d ",ans.size());
	for(int x:ans)printf("%d ",x);
	putchar('\n');
}
```

剩下的两条路径本质相同，拿一条来说。

![](https://cdn.luogu.com.cn/upload/image_hosting/m78yhq7q.png)

红色的点是起始点和终点，蓝色的点是环上的点，发现整条路径可以分成三个部分：$px$ 到 $x$，$x$ 到 $y$，$y$ 到 $py$。那么如何确定哪个是 $x$，哪个是 $y$ 呢？看图可知，如果一个点 $p$，满足 $dis(p,px)<dis(p,py)$，那么这个点是 $x$，否则是 $y$。所以在顺序不对的时候需要交换两个点。

```cpp
int xx=a[x].x,yy=a[x].y;
if(dis(xx,px)>dis(xx,py))swap(xx,yy);
vector<int>an=findPath(px,xx);
vector<int>rem=findPath(yy,py);
for(int wh:rem)an.push_back(wh);
printPath(an);
```

然后就做完了。由于我太弱了，在写这道题的时候绕了一些圈，所以想要写一篇题解来帮助那些对实现上有困惑的同学（虽然估计没谁会需要呜呜呜）。

[最后推销一下博客。](https://feynn.github.io/)

---

## 作者：xht (赞：3)

> [CF521E Cycling City](https://codeforces.com/contest/521/problem/E)

## 题面

- 给定一张 $n$ 个点 $m$ 条边的无向简单图。
- 问图中能否找到两个点，满足这两个点之间有至少三条完全不相交的简单路径。
- $n,m \le 2 \times 10^5$，图不保证连通。

## 题解

首先建出 dfs 树，那么有解的充要条件是**存在至少一条树边被至少两条返祖边覆盖**，这显然可以树上差分判定。

若有解，考虑如何构造方案。

可以通过两次二分，每次判定使用树上差分，找到两条**至少有一条树边被它们覆盖**的返祖边。

在只保留这两条边的情况下构造方案即可，具体方法见代码。

总时间复杂度 $\mathcal O(n \log m)$，可以做到线性但没必要。

## 代码

```cpp
const int N = 2e5 + 7;
int n, m, v[N], dfn[N], num, f[N], t, d[N];
vi e[N], ans[3];
pi p[N];

void dfs(int x) {
	dfn[x] = ++num;
	for (auto y : e[x])
		if (!dfn[y]) f[y] = x, dfs(y);
		else if (y != f[x] && dfn[y] < dfn[x]) p[++t] = mp(x, y);
}

void dfs1(int x) {
	v[x] = 1;
	for (auto y : e[x])
		if (f[y] == x) dfs1(y), d[x] += d[y];
}

inline void work(int o) {
	--d[p[o].se], ++d[p[o].fi];
}

inline bool ask(int l, int r) {
	for (int i = l; i <= r; i++) work(i);
	for (int i = 1; i <= n; i++) if (!v[i]) dfs1(i);
	bool ok = 0;
	for (int i = 0; i <= n; i++) ok |= d[i] > 1, d[i] = v[i] = 0;
	return ok;
}

int main() {
	rd(n), rd(m);
	for (int i = 1, x, y; i <= m; i++)
		rd(x), rd(y), e[x].pb(y), e[y].pb(x);
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
	if (!ask(1, t)) return prints("NO"), 0;
	else prints("YES");
	int l = 2, r = t;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (ask(1, mid)) r = mid;
		else l = mid + 1;
	}
	int R = l;
	l = 1, r = R - 1;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (ask(mid, R)) l = mid;
		else r = mid - 1;
	}
	int L = l;
	work(L), work(R);
	for (int i = 1; i <= n; i++) if (!v[i]) dfs1(i);
	int Y = 0;
	for (int i = 1; i <= n; i++)
		if (d[i] == 2 && dfn[i] > dfn[Y]) Y = i;
	int X = Y;
	ans[0].pb(X);
	while (d[X] == 2) ans[0].pb(X = f[X]);
	reverse(ans[0].begin(), ans[0].end());
	for (int i = 1; i < 3; i++) {
		int Z = X, o = i == 1 ? L : R;
		ans[i].pb(Z);
		while (Z != p[o].se) ans[i].pb(Z = f[Z]);
		ans[i].pb(Z = p[o].fi);
		while (Z != Y) ans[i].pb(Z = f[Z]);
	}
	for (int i = 0; i < 3; i++) {
		print(ans[i].size(), ' ');
		for (auto x : ans[i]) print(x, ' ');
		prints("");
	}
	return 0;
}
```

---

## 作者：DarkMoon_Dragon (赞：3)

## 题意：
+ 给定一个无向图，判断是否存在两个点之间有至少三条点不相交（除了起点和终点）的简单路径。
   
## $Solution$:
+ 可以用判断仙人掌来做，我这里写得$LCA$路径覆盖。
+ 判断是否存在合法方案很简单，将原来的无向图重建成一颗$dfs$树~~（常规操作）~~,对于非树边$u,v$,把路径上的边差分$+1$。然后显然对于一条边，如果它的边权$>1$,那么一定存在三条路径。（本身一条，加边权的贡献边两条），也就是$dfs$的时候记录所有非树边覆盖了每条树边多少次。回溯时把差分标记传回去。
+ 这道题恶心就恶心在输出方案。
+ 考虑如下几种情况。
![mine](https://cdn.luogu.com.cn/upload/image_hosting/iy3rwoqu.png)
+ 具体细节看下面代码就懂了，主要是要想得到这几种情况。打星号的点很关键。用$LCA$来求。
  
```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define rr int
using namespace std;
typedef long long ll;
inline ll read() {
    char i = getchar();
    ll f = 1, res = 0;
    while (i < '0' || i > '9') {
        if (i == '-') f = -1;
        i = getchar();
    }
    while (i >= '0' && i <= '9') {
        res = res * 10 + i - '0';
        i = getchar();
    }
    return res * f;
}
const int N = 2e5 + 50;
int n, m, cnt, head[N], f[N][21], vis[N], c[N], dep[N], S;
vector<int> path;
struct zk {
    int next, v;
} ed[N << 1];
inline void adde(int u, int v) {
    ed[++cnt].v = v;
    ed[cnt].next = head[u];
    head[u] = cnt;
}
inline void rebuild(int u, int fa) {
    vis[u] = 1;
    for (rr i = head[u]; ~i; i = ed[i].next) {
        int v = ed[i].v;
        if (v == f[u][0]) continue;
        if (!vis[v]) {
            dep[v] = dep[u] + 1;
            f[v][0] = u;
            rebuild(v, u);
        } else if (dep[v] < dep[u]) {  // 差分减
            c[v]--;
            c[u]++;
        }
    }
    c[f[u][0]] += c[u];
}
int l1, l2, r1, r2;
inline void dfs(int u) {
    for (rr i = head[u]; ~i; i = ed[i].next) {
        int v = ed[i].v;
        if (v == f[u][0]) continue;
        if (dep[v] == dep[u] + 1) {
            dfs(v);
            if (l2) return;
        } else if (dep[v] < dep[S]) {
            if (l1)
                r2 = u, l2 = v;
            else
                r1 = u, l1 = v;
            if (l2) return;
        }
    }
}
inline int LCA(int a, int b) {
    // puts("st");
    if (dep[a] > dep[b]) swap(a, b);
    int h = dep[b] - dep[a];
    for (rr i = 20; i >= 0; --i) {
        if (h & (1 << i)) b = f[b][i];
    }
    if (a == b) return a;
    for (rr i = 20; i >= 0; --i) {
        if (f[a][i] == f[b][i]) continue;
        a = f[a][i];
        b = f[b][i];
    }
    // puts("end");
    return f[a][0];
}
int main() {
    memset(head, -1, sizeof head);
    n = read();
    m = read();
    for (rr i = 1; i <= m; ++i) {
        int u = read(), v = read();
        adde(u, v);
        adde(v, u);
    }
    for (rr i = 1; i <= n; ++i) {
        if (!vis[i]) rebuild(i, 0);
    }
    S = 0;
    for (rr i = 1; i <= n; ++i) {
        if (c[i] > 1) {
            S = i;  // S的上一条边经过了两次
            break;
        }
    }
    if (!S) {
        puts("NO");
        return 0;
    }
    puts("YES");
    dfs(S);
    for (rr j = 1; j < 21; ++j) {
        for (rr i = 1; i <= n; ++i) f[i][j] = f[f[i][j - 1]][j - 1];
    }
    int T = LCA(r1, r2);
    // puts("dsa");
    if (dep[l1] < dep[l2]) swap(l1, l2), swap(r1, r2);
    S = l1;  // 只能走下面
    int now = T;
    while (1) {
        // cout << now << endl;
        path.push_back(now);
        if (now == S) break;
        now = f[now][0];
    }
    int sz = path.size();
    printf("%d ", sz);
    for (rr i = 0; i < sz; ++i) printf("%d ", path[i]);
    puts("");
    path.clear();
    path.push_back(S);
    now = r1;
    while (1) {
        // cout << now <<endl;
        path.push_back(now);
        if (now == T) break;
        now = f[now][0];
    }
    sz = path.size();
    printf("%d ", sz);
    for (rr i = sz - 1; i >= 0; --i) printf("%d ", path[i]);
    puts("");
    path.clear();
    if (S == l2) {
        path.push_back(S);
        now = r2;
        while (1) {
            path.push_back(now);
            if (now == T) break;
            now = f[now][0];
        }
    } else {
        now = S;
        while (1) {
            path.push_back(now);
            if (now == l2) break;
            now = f[now][0];
        }
        now = r2;
        while (1) {
            path.push_back(now);
            if (now == T) break;
            now = f[now][0];
        }
    }
    sz = path.size();
    printf("%d ", sz);
    for (int i = sz - 1; i >= 0; --i) printf("%d ", path[i]);
    return 0;
}
```

---

## 作者：tzc_wk (赞：2)

[Codeforces 题面传送门](https://codeforces.ml/contest/521/problem/E) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF521E)

大家都是暴力找生成树然后跳路径，代码不到 50 行（暴论）的一说……好，那本蒟蒻决定提供一种代码 150 行，但复杂度也是线性的分类讨论做法。

首先大家都是从“如果存在两个环相交，就一定存在符合要求的路径”这个性质入手的，而我不是。注意到题目条件涉及“简单路径”，因此我首先想到的是，如果两个点 $u,v$ 之间存在三条互不相交的路径，那么 $u,v$ 在同一个点双连通分量中必定是必要条件，因此不同点双之间的点必然是没有贡献的，我们只用考虑同一点双中的点即可。

考虑什么样的点双中存在符合条件的两个点，通过手玩数据我发现，一个环的情况显然是不行的，其余情况都存在符合要求的两个点。因此直觉告诉我，一个点双中存在符合条件的两个点的充要条件就是这个点双不是一个环。事实也的确如此，考虑怎么构造符合条件的路径。

我们考虑随便定一个根节点，并以从根节点开始 DFS 找出点双的一棵 DFS 树，那么由于原图是一个点双，必然有与根节点 $r$ 相连的树边只有一条，因为根据 DFS 树的性质，该点双中所有非树边都是连接 DFS 树上某个点与其祖先的边，因此如果根节点存在多个分叉，那么这些分叉代表的子树之间两两是没有边的，换句话说，去掉根节点后图不连通，不符合点双的定义。考虑就此分三种情况讨论：

1. 存在两个及以上与根节点相连的非树边

   假设这两条非树边分别是 $r\to u$ 和 $r\to v$，那么考虑找出 $w=\text{LCA}(u,v)$，那么 $r,w$ 之间存在三条符合要求的路径，一条是 $w$ 直接跳到 $r$，一条是 $w$ 向下走到 $u$，$u$ 再到 $r$，一条是 $w$ 向下走到 $v$，$v$ 再到 $r$​​。

   如下图所示，三种颜色分别代表了三条不同的路径：

   ![](https://cdn.luogu.com.cn/upload/image_hosting/3xjfbpsn.png)

2. 只有一条与根节点相连的非树边

   显然，由于原图是一个点双，不能不存在非树边与根节点相连，否则去掉根节点唯一的儿子后，图就不连通了（这里假定点双大小 $\ge 3$，如果点双大小 $\le 2$ 直接判掉即可）

   那么我们不妨假设这条非树边为 $r\to u$，到这里我们继续分类讨论：

   1. 如果 $u$ 不是叶子

      那么我们考虑找到 $u$ 子树中一个叶子 $v$，再找到所有与 $v$ 相连的点中，**深度最浅的那个点** $w$，还是根据图是一个点双这个性质，必然**有 $w$ 的深度严格浅于 $u$ 的深度**，否则去掉 $w$ 之后图不连通，这样考虑 $u\to w$ 的路径，有以下三条：

      - $u$ 向上直接跳到 $w$
      - $u$ 跳到根节点 $r$，再向下走到 $w$
      - $u$ 向下走到 $v$，再向上跳到 $w$​

      ![](https://cdn.luogu.com.cn/upload/image_hosting/25pedckv.png)

   2. 如果 $u$ 是叶子

      我们考虑找到一条非树边，不同于 $r\to u$ 这条边，并且这两条边**至少有一个端点**在 $u\to r$ 这条链上，可以说明我们总能找到这样的边，否则图不满足点双的性质，读者自证不难，那么我们假设这条边为 $x,y$，其中 $x$ 为深度较小者，设离 $y$ 最近的、在 $u\to r$ 这条链上的节点为 $w$，那么考虑构造这样三条 $w\to x$ 的路径：

      - $w$ 直接向上跳到 $x$
      - $w$ 向下走到 $y$，再走到 $x$
      - $w$ 向下走到 $u$，跳到 $r$，再向下走到 $x$​

      ![](https://cdn.luogu.com.cn/upload/image_hosting/2m4dub2h.png)

分类讨论一下即可，复杂度 $\mathcal O(n)$

```cpp
const int MAXN=2e5;
int n,m,U[MAXN+5],V[MAXN+5];
struct graph{
	int hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=1;
	void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
} g,ng,t;
int dfn[MAXN+5],low[MAXN+5],tim=0;
int stk[MAXN+5],tp=0,bel[MAXN+5],cmp=0,in_stk[MAXN+5];
void tarjan(int x){
//	printf("tarjan %d\n",x);
	dfn[x]=low[x]=++tim;
	for(int e=g.hd[x];e;e=g.nxt[e]){
		int y=g.to[e];
		if(!dfn[y]){
			stk[++tp]=e>>1;in_stk[e>>1]=1;
			tarjan(y);chkmin(low[x],low[y]);
			if(low[y]>=dfn[x]){
//				printf("find an edcc %d %d\n",x,y);
				cmp++;int o;do{
					o=stk[tp--];bel[o]=cmp;
					in_stk[o]=0;
				} while(o^(e>>1));
			}
		} else {
			chkmin(low[x],dfn[y]);
			if(dfn[y]<dfn[x]&&!in_stk[e>>1]){
				stk[++tp]=e>>1;in_stk[e>>1]=1;
			}
		}
	}
}
vector<int> bp[MAXN+5];
int in[MAXN+5],fa[MAXN+5],dep[MAXN+5],deg[MAXN+5];
bool vis[MAXN+5],ont[MAXN+5];
void dfs(int x){
	vis[x]=1;
	for(int e=ng.hd[x];e;e=ng.nxt[e]){
		int y=ng.to[e];
		if(!vis[y]){
			ont[e>>1]=1;t.adde(x,y);
			fa[y]=x;deg[x]++;deg[y]++;dep[y]=dep[x]+1;dfs(y);
		}
	}
}
void prt(vector<int> res1,vector<int> res2,vector<int> res3){
	puts("YES");
	printf("%d",res1.size());for(int x:res1) printf(" %d",x);printf("\n");
	printf("%d",res2.size());for(int x:res2) printf(" %d",x);printf("\n");
	printf("%d",res3.size());for(int x:res3) printf(" %d",x);printf("\n");
	exit(0);
}
void work(int id){
	for(int e:bp[id]) ng.adde(U[e],V[e]),ng.adde(V[e],U[e]);
	dfs(U[bp[id][0]]);int rt=U[bp[id][0]],cnt=0;
	for(int e=ng.hd[rt];e;e=ng.nxt[e]) cnt+=(!ont[e>>1]);
	assert(cnt>=1);
	if(cnt>=2){
		int x=0,y=0;vector<int> p1,p2,p3;p1.pb(rt),p2.pb(rt);
		for(int e=ng.hd[rt];e;e=ng.nxt[e]) if(!ont[e>>1]){
			if(!x) x=ng.to[e];else if(!y) y=ng.to[e];
		} if(dep[x]<dep[y]) swap(x,y);
		while(dep[x]>dep[y]) p1.pb(x),x=fa[x];
		while(x^y) p1.pb(x),p2.pb(y),x=fa[x],y=fa[y];
		p1.pb(x);p2.pb(x);
		while(x^rt) p3.pb(x),x=fa[x];p3.pb(rt);
		reverse(p3.begin(),p3.end());prt(p1,p2,p3);
	} else {
		int p=0,pe=0;
		for(int e=ng.hd[rt];e;e=ng.nxt[e]) if(!ont[e>>1])
			p=ng.to[e],pe=e>>1;
		if(deg[p]!=1){
			int q=p;while(deg[q]!=1){
				for(int e=t.hd[q];e;e=t.nxt[e])
					if(t.to[e]!=fa[q]){q=t.to[e];break;}
			} int r=0;for(int e=ng.hd[q];e;e=ng.nxt[e])
				if(!r||dep[r]>dep[ng.to[e]]) r=ng.to[e];
			vector<int> p1,p2,p3;int cp=p,cq=q;
			while(cp^r) p1.pb(cp),cp=fa[cp];p1.pb(cp);
			while(cp^rt) p2.pb(cp),cp=fa[cp];p2.pb(rt);
			reverse(p2.begin(),p2.end());p2.insert(p2.begin(),p);
			while(cq^p) p3.pb(cq),cq=fa[cq];p3.pb(cq);
			reverse(p3.begin(),p3.end());p3.pb(r);
			prt(p1,p2,p3);
		} else {
			int cp=p;static bool on_ch[MAXN+5]={0};
			while(cp^rt) on_ch[cp]=1,cp=fa[cp];on_ch[rt]=1;
			int u=0,v=0;vector<int> p1,p2,p3;
			for(int e=1;e<=(ng.ec>>1);e++) if(!ont[e]&&e!=pe){
				int x=ng.to[e<<1],y=ng.to[e<<1|1];
				if(on_ch[x]||on_ch[y]){u=x;v=y;break;}
			} if(dep[u]<dep[v]) swap(u,v);
			while(!on_ch[u]) p1.pb(u),u=fa[u];p1.pb(u);
			reverse(p1.begin(),p1.end());p1.pb(v);
			int cu=u,cv=v;while(cu^v) p2.pb(cu),cu=fa[cu];p2.pb(v);
			cu=p;while(cv^rt) p3.pb(cv),cv=fa[cv];p3.pb(rt);
			while(cu^u) p3.pb(cu),cu=fa[cu];p3.pb(cu);
			reverse(p3.begin(),p3.end());prt(p1,p2,p3);
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&U[i],&V[i]);
		g.adde(U[i],V[i]);g.adde(V[i],U[i]);
	} for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=m;i++) bp[bel[i]].pb(i);
//	for(int i=1;i<=m;i++) printf("%d\n",bel[i]);
	for(int id=1;id<=cmp;id++){
		int cc=0;
		for(int e:bp[id]){
			if(!in[U[e]]) in[U[e]]=1,cc++;
			if(!in[V[e]]) in[V[e]]=1,cc++;
		} if(cc<bp[id].size()){
			work(id);
		} for(int e:bp[id]) in[U[e]]=in[V[e]]=0;
	} puts("NO");
	return 0;
}
```



---

## 作者：plyyyyy (赞：1)

# 题意

 - 给定一张 $n$ 个点 $m$ 条边的无向简单图。
 - 问图中能否找到两个点，满足这两个点之间有至少三条完全不相交的简单路径。
 - $n,m\leq2\times10^5$，图不保证连通。

# 题解

首先假设图联通，我们可以求出图的 DFS 树。如果两个点之间有至少三条完全不相交的路径，那么其中一个点一定是另一个点的祖先，并且在以 DFS 序更大的点（以下称为起点）为根的子树内一定有至少两条返祖边连向 DFS 序小的点（以下称为终点）以及其祖先。

那怎么找那两个点呢？注意到如果两条返祖边的终点是同一个点，那么要找的终点一定在交点的位置（因为如果不在那里路径就会重复），否则要找的终点一定在 DFS 序更大的终点的位置，同理两条返祖边的起点一定分别在要找的起点的两个儿子中。

显然如果从一个起点出发可以到达多个终点，而我们只需要维护终点中 DFS 序最小的点和 DFS 序最大的点即可找到答案。

输出方案的时候可以通过记录每个点的父节点 从 DFS 序最大的点往上跳输出答案。

记第 $i$ 个点的 DFS 序为 $dfn_i$，$i$ 所能通过其子树内的某条返祖边到达的 DFS 序小于 $i$ 的点（也就是 $i$ 的祖先）中 DFS 序最小的点的编号 $mn_i$、最大的点的编号 $mx_i$。


```c++
const int N=2e5+5;
int dfn[N],mx[N],mn[N],max[N],min[N];//max/min为终点DFS序最大/最小的返祖边的起点编号
```

在 DFS 回溯的过程中更新当前节点的 $mn$ 和 $mx$。

```c++
void dfs(int u,int fa){//u为当前所在的节点，fa为父节点
    f[u]=fa;//f[i]记录节点i的父节点
    dfn[u]=++cnt;
    for(int v:a[u]){
        if(v==fa)continue;
        if(!dfn[v]){//先遍历子节点
            dfs(v,u);
            //如果从u出发走已经遍历过的点能到达的DFS序最大的点 DFS序大于等于从v出发能到达的DFS序最小的点，那么直接输出答案
            if(mx[u]&&mn[v]!=inf&&dfn[mn[v]]<=dfn[mx[u]])print(u,v);
            //更新当前点能到达的DFS序最大/最小的点编号
            if(mx[v]&&dfn[mx[v]]<dfn[u]&&(!mx[u]||dfn[mx[u]]<dfn[mx[v]]))mx[u]=mx[v],max[u]=max[v];
            if(mn[v]!=inf&&dfn[mn[v]]<dfn[u]&&(mn[u]==inf||dfn[mn[u]]>dfn[mn[v]]))mn[u]=mn[v],min[u]=min[v];
        }
    }
    for(int v:a[u]){
        if(v==fa)continue;
        if(dfn[v]<dfn[u]){
            if(!mx[u])mx[u]=v;
            if(mn[u]==inf)mn[u]=v;
            //注意要把max/min改成u
            if(dfn[mx[u]]<dfn[v])mx[u]=v,max[u]=u;
            if(dfn[mn[u]]>dfn[v])mn[u]=v,min[u]=u;
        }
    }
    if(mx[u]&&mn[u]!=inf&&((dfn[mn[u]]==dfn[mx[u]]&&max[u]!=min[u])||dfn[mn[u]]<dfn[mx[u]]))print(u,u);
}
```

输出答案。

```c++
void print(int u,int v){
    std::cout<<"YES\n";
    //在DFS树上的链
    for(int i=u;i!=mx[u];i=f[i])ans.pb(i);
    std::cout<<ans.size()+1<<" ";
    for(int i:ans)std::cout<<i<<" ";
    std::cout<<mx[u]<<"\n";
    //终点DFS序大的链
    ans.clear();
    for(int i=max[u];i!=u;i=f[i])ans.pb(i);//从答案起点到链的起点
    std::cout<<ans.size()+2<<" "<<u<<" ";
    while(!ans.empty()){
        std::cout<<ans.back()<<" ";
        ans.pop_back();
    }
    std::cout<<mx[u]<<"\n";//链的终点就是答案终点
    //终点DFS序小的链
    for(int i=mx[u];i!=mn[v];i=f[i])ans.pb(i);//从答案终点到链的终点
    ans.pb(mn[v]);//别忘了链的终点
    for(int i=min[v];i!=u;i=f[i])ans.pb(i);//同上
    std::cout<<ans.size()+1<<" "<<u<<" ";
    while(!ans.empty()){
        std::cout<<ans.back()<<" ";
        ans.pop_back();
    }
    exit(0);//直接退出
}
```
别忘了对每个联通块都 DFS 一次。

[完整代码](https://plyyyyyy.github.io/2024/04/12/CF521E-Cycling-City-%E9%A2%98%E8%A7%A3/)

---

## 作者：王熙文 (赞：1)

提供一个新的、基于随机化的题解，比较好想。

## 思路

最初我以为任选一个 dfs 树，如果有解，则解中至少一个是一个点和它的祖先。但是这是不对的，比如下面这个图：![](https://cdn.luogu.com.cn/upload/image_hosting/e3ptnwv9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

但是感性理解一下，如果随机若干次 dfs 树，有解时得到解的概率是很高的。因为对于每一组解，若想让它们在 dfs 树中不是祖孙关系，需要在 dfs 过程中碰到这两个点之一之前切断这两个点（删掉已走过的点后这两个点不连通），而这两个点之间还有大于等于三条路径，所以切断很难。

因此现在考虑如何在 dfs 树上找到一组解。考虑找到这些解中必定存在的一个特征，即对于任何有解的图都有一个解满足这个特征。

考虑现在找到了一组解 $(a,b)$，令 $a$ 为 dfn 较大的点。我们在这三条路径中找到两条不经过 $a$ 到它在 dfs 树上的父亲的路径，设 $x,y$ 表示这两条路径第一个 dfn 比 $a$ 小的点，令 $x$ 为 dfn 较大的点。我们将 $b$ 设为 $x$，第一条路径变为原路径上 $a \to x$ 这一段，第二条路径变为原路径上 $a \to y$ 这一段加上 dfs 树上 $y \to x$ 这一段。再将第三条路径变成 dfs 树上 $a \to x$ 这一段。显然新的三条路径仍然互不相交。

但是这样的解性质还不够，因为前两条路径有可能在 $a$ 点子树内跳来跳去。考虑找到这两条路径跳到 $x,y$ 上一个点，设为 $c,d$，将 $a$ 设为这两个点的 $\text{lca}$。将前两条路径在原 $a$ 下面的部分变成 $a\to c,a \to d$ 这两段，并将第三条路径延长。这样，这三条路径互不相交且有如下性质：第一条路径为从 $a$ 沿着 dfs 树向下走若干步并跳上去的路径，第二条路径为从 $a$ 沿着 dfs 树向下走若干步跳上去再向下走到 $b$ 的路径，第三条路径为 $a$ 沿着 dfs 树向上走到 $b$ 的路径。

最后的问题是找到这三条路径。对于一个点，维护它自己和它子树内向上跳一步能到达的最小 dfn 的点。检查一个点自己和它的各个儿子的子树是否存在大于等于两个可以跳到 dfn 比 $a$ 小的点即可。

## 代码

```cpp
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int n,m;
vector<int> e[200010];
int p[200010];
int tot,dfn[200010],low[200010],id[200010];
int fa[200010];
int in[200010],wz[200010];
vector<int> ans;
void push(int u,int v)
{
	int now=u;
	while(now!=v) ans.push_back(now),now=fa[now];
	ans.push_back(v);
}
void output()
{
	cout<<ans.size()<<' ';
	for(int i:ans) cout<<i<<' ';
	cout<<'\n';
	ans.clear();
}
void dfs(int u)
{
	dfn[u]=low[u]=++tot,id[tot]=u;
	in[u]=2e9;
	int fir=0,gf,sec=0,gs;
	for(int v:e[u])
	{
		if(dfn[v]==0)
		{
			fa[v]=u,dfs(v);
			if(in[u]>in[v]) in[u]=in[v],wz[u]=wz[v];
			if(in[v]<dfn[u]) fir==0?fir=wz[v],gf=in[v]:sec=wz[v],gs=in[v];
		}
		else if(v!=fa[u]) low[u]=min(low[u],dfn[v]);
	}
	if(in[u]>low[u]) in[u]=low[u],wz[u]=u;
	if(low[u]<dfn[u]) fir==0?fir=u,gf=low[u]:sec=u,gs=low[u];
	if(sec!=0)
	{
		cout<<"YES\n";
		if(gf<gs) swap(fir,sec),swap(gf,gs);
		gf=id[gf],gs=id[gs];
		push(u,gf),output();
		push(fir,u),reverse(ans.begin(),ans.end()),ans.push_back(gf),output();
		push(gf,gs),push(sec,u),reverse(ans.begin(),ans.end()),output();
		exit(0);
	}
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>n>>m;
	for(int i=1; i<=m; ++i)
	{
		int u,v;
		cin>>u>>v;
		e[u].push_back(v),e[v].push_back(u);
	}
	for(int i=1; i<=n; ++i) p[i]=i;
	for(int t=1; t<=25; ++t)
	{
		for(int i=1; i<=n; ++i) shuffle(e[i].begin(),e[i].end(),rnd);
		shuffle(p+1,p+n+1,rnd);
		tot=0,memset(dfn,0,(n+5)*4);
		for(int i=1; i<=n; ++i)
		{
			if(dfn[p[i]]==0) dfs(p[i]);
		}
	}
	cout<<"NO";
	return 0;
}
```

---

## 作者：honglan0301 (赞：1)

提供一个基于点双且不需要分类讨论的简单写法。

## 题目分析

首先发现满足要求两个点必属于同一个点双中（否则必然经过割点，只能找到一条路径），于是我们只需要考虑点双内的情况。

如果点双只是一个简单环（$|V|=|E|$）显然是不行的，而其余情况（$|V|<|E|$）自己玩一玩感觉都可行，事实上也容易发现这就是充要条件，构造性的证明如下：

* 首先由抽屉原理知此时必然有一个点的度数 $d_u\geq 3$，记其为 $u$，任意选出其的两条连边，记它们分别指向 $v_1,v_2$。

* 此时断开 $(u,v_1),(u,v_2)$，该点双一定还连通，于是记当前 $v_1,v_2$ 在以 $u$ 为根的 $\text{dfs}$ 树上的 $\text{lca}$ 为 $w$。我们下面只需证明 $w\not=u$ 就可以了，因为能够选出 $u\rightarrow v_1\rightarrow w$，$u\rightarrow v_2\rightarrow w$，$u\rightarrow w$ 这三条满足要求的路径。

	而 $w\not=u$ 很好证：假如 $w=u$，那么这意味着在 $\text{dfs}$ 树上点 $u$ 连了至少两条树边，也就意味着把点 $u$ 删掉后它的子树们不连通，即 $u$ 是割点，这与它们同在一个点双中矛盾，所以 $w\not=u$，做完了。
    
## 代码

个人感觉已经非常简洁优美了。

```cpp
#define mp make_pair
#define pb push_back
#define fi first
#define se second

int n,m,u,v,aa,bb,dep[200005],fa[200005],vis[200005];
int dfn[200005],low[200005],cntd,stk[200005],top,topb,du[200005];
vector <int> e[200005],g[200005],nd,ans1,ans2,ans3;
pair <int,int> stkb[200005];

void dfs2(int x)
{
	vis[x]=1;
	for(auto i:g[x])
	{
		if(vis[i]||(dep[x]==1&&(i==aa||i==bb))) continue; 
		dep[i]=dep[x]+1; fa[i]=x; dfs2(i);
	}
}
void solve()
{
	for(auto i:nd)
	{
		if(g[i].size()>2)
		{
			aa=g[i][0],bb=g[i][1]; dep[i]=1; dfs2(i);
			ans1.pb(i); ans2.pb(i); ans1.pb(aa); ans2.pb(bb);
			while(aa!=bb) {if(dep[aa]>=dep[bb]) aa=fa[aa],ans1.pb(aa); else bb=fa[bb],ans2.pb(bb);}
			ans3.pb(aa); while(aa!=i) aa=fa[aa],ans3.pb(aa);
			reverse(ans3.begin(),ans3.end());
			cout<<"YES"<<endl;
			cout<<ans1.size()<<" "; for(auto j:ans1) cout<<j<<" "; cout<<endl;
			cout<<ans2.size()<<" "; for(auto j:ans2) cout<<j<<" "; cout<<endl;
			cout<<ans3.size()<<" "; for(auto j:ans3) cout<<j<<" "; cout<<endl;
			return;
		}
	}
}

void dfs1(int x,int fat)
{
	dfn[x]=low[x]=++cntd; stk[++top]=x;
	for(auto i:e[x])
	{
		if(i==fat) continue;
		if(!dfn[i])
		{
			stkb[++topb]=mp(x,i); dfs1(i,x); low[x]=min(low[x],low[i]);
			if(low[i]>=dfn[x])
			{
				nd.clear(); nd.pb(x); int ns=0;
				while(1) {int nr=stk[top--]; nd.pb(nr); if(nr==i) break;}
				while(1) 
				{
					auto nr=stkb[topb--]; ns++;
					g[nr.fi].pb(nr.se); g[nr.se].pb(nr.fi); if(nr.fi==x&&nr.se==i) break;
				}
				if(ns>nd.size()) solve(),exit(0);
				for(auto j:nd) g[j].clear();
			}
		}
		else if(dfn[i]<dfn[x]) stkb[++topb]=mp(x,i),low[x]=min(low[x],dfn[i]);
	}
}

signed main()
{
	cin>>n>>m; for(int i=1;i<=m;i++) cin>>u>>v,e[u].pb(v),e[v].pb(u);
	for(int i=1;i<=n;i++) if(!dfn[i]) dfs1(i,i); cout<<"NO"<<endl;
}
```


---

## 作者：wrzSama (赞：1)

## 题目大意

给定 $n$ 个点 $m$ 条边的无向简单图（不保证图联通），问能否找到两个点满足这两点间至少有 $3$ 条完全不相交的简单路径，如果可以就输出 YES 并输出这 $2$ 点间任意 $3$ 条路径，否则输出 NO。
$n,m \le 2 \times 10^5$。

## 思路

我们可以发现满足题意的 $2$ 个点的 $3$ 条路径是由 $2$ 个有相交部分的环组成的，而这 $2$ 个点就是环相交部分的 $2$ 个端点。也就是说，只要有一条边同时属于 $2$ 个不同的环，我们就可以找到答案。我们可以先生成 $1$ 棵树，每找到 $1$ 条非树边就将与这条边形成环的所有树边都标记上这条边的信息。具体地，我们记录每个节点的父节点和深度，每次从非树边连接的较深的点不断向上找父亲直到找到另一个连接的点，标记这之中所有遍历过的边。如果要标记的边已经被别的非树边标记过了，则说明这些边同时属于这 $2$ 条非树边与树形成的 $2$ 个环，即有答案，下面我们就通过这 $2$ 条非树边和树查找路径。若这 $2$ 条非树边连接的节点分别为 $a,b$ 和 $c,d$（$a$ 的深度大于 $b$ 的深度，$c$ 的深度大于 $d$ 的深度，$b$ 的深度小于 $d$ 的深度），设 $a$ 和 $c$ 的最近公共祖先为 $x$，那么这 $3$ 条路径就分别是 $d \rightarrow x$，$d \rightarrow c \rightarrow x$ 和 $d \rightarrow b \rightarrow a \rightarrow x$。因为每条树边在找到答案前只会被非树边标记 $1$ 次，而找到答案后统计路径和求最近公共祖先同样也是线性的，所以总时间复杂度也是线性的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
vector<int>s[200005];
int n,m,fa[200005],d[200005],h[200005],t[200005],ans[200005],tl;
bool vis[200005];
inline int lca(int x,int y)
{
	if(d[x]<d[y]) swap(x,y);
	while(d[x]>d[y]) x=fa[x];
	while(x!=y)
	{
		x=fa[x];
		y=fa[y];
	}
	return x;
}
inline void add(int x,int y)
{
	while(x!=y)
	{
		ans[++tl]=x;
		x=fa[x];
	}
	ans[++tl]=y;
}
inline void print()
{
	write(tl);
	putchar(' ');
	for(int i=1;i<=tl;++i)
	{
		write(ans[i]);
		putchar(' ');
	}
	puts("");
	tl=0;
}
inline void get(int a,int b,int x,int y)
{
	if(d[b]>d[y])
	{
		swap(a,x);
		swap(b,y);
	}
	puts("YES");
	int wrz=lca(a,x);
	add(wrz,y);
	for(int i=1;i+i<=tl;++i) swap(ans[i],ans[tl-i+1]);
	print();
	add(y,b);
	add(a,wrz);
	print();
	ans[++tl]=y;
	add(x,wrz);
	print();
	exit(0);
}
inline void dfs(int u)
{
	d[u]=d[fa[u]]+1;
	vis[u]=1;
	for(int i=0;i<s[u].size();++i)
	{
		int v=s[u][i];
		if(v==fa[u]) continue;
		if(!d[v])
		{
			fa[v]=u;
			dfs(v);
		}
		else if(vis[v])
		{
			for(int j=u;j!=v;j=fa[j])
			{
				if(h[j]) get(h[j],t[j],u,v);
				else
				{
					h[j]=u;
					t[j]=v;
				}
			}
		}
	}
	vis[u]=0;
}
int main()
{
	n=read();
	m=read();
	for(int i=1;i<=m;++i)
	{
		int u=read(),v=read();
		s[u].push_back(v);
		s[v].push_back(u);
	}
	for(int i=1;i<=n;++i)
	{
		if(d[i]) continue;
		d[i]=1;
		dfs(i);
	}
	puts("NO");
	return 0;
}
```


---

## 作者：xzzduang (赞：1)

[传送门](https://codeforces.com/problemset/problem/521/E)

写完发现好像我和其他题解的做法不太一样。

如果这题问的是两条点不相交路径的话，做法是 tarjan，所以三条我们也可以考虑 tarjan，因为是无向图，找出 dfs 树后非树边只有返祖边，所以我们找出来的答案应该是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/xr64oazp.png?x-oss-process=image/resize,m_lfit,h_500,w_1000)

答案路径就是：$u\rightarrow t2,u\rightarrow v2\rightarrow t2,u\rightarrow v1\rightarrow t1\rightarrow t2$。所以做法呼之欲出，我们维护 tarjan 的 `low` 数组的时候不止维护最小值，还维护一个次小值，当最小值和次小值都比 $u$ 的 dfs 序小的时候我们就找到了一组答案。

```cpp
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<vector>
#include<stack>
#define N 200005
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,f=0; char ch=getchar();
	while(!isdigit(ch)) f|=(ch==45),ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
struct edge{
	int b,n;
}e[N*2];
vector <int> ans;
stack <int> st;
int n,m,h[N],tot,dfn[N],rev[N],fa[N];
pair<int,int> low[N];
inline void charu(int a,int b){
	e[++tot].b=b,e[tot].n=h[a],h[a]=tot;
}
void dfs(int u){
	dfn[u]=++dfn[0],rev[dfn[0]]=u;
	pair<int,int> t1={dfn[0],u},t2={(int)1e9,0};
	for(int i=h[u];i;i=e[i].n){
		int v=e[i].b;
		if(!dfn[v]){
			fa[v]=u;
			dfs(v);
			if(low[v]<t1) swap(low[v],t1);
			if(low[v]<t2) swap(low[v],t2);
		}
		else if(v!=fa[u]){
			pair<int,int> tmp={dfn[v],u};
			if(tmp<t1) swap(tmp,t1);
			if(tmp<t2) swap(tmp,t2);
		}
	}
	if(t1.fi<dfn[u] && t2.fi<dfn[u]){
		puts("YES");
		int T=rev[t2.fi],now=u;
		while(now!=T){
			ans.push_back(now);
			now=fa[now];
		}
		ans.push_back(T);
		printf("%d ",ans.size());
		for(int v:ans) printf("%d ",v);
		puts("");
		ans.clear();
		now=t2.se;
		while(now!=u){
			st.push(now);
			now=fa[now];
		}
		st.push(u);
		while(!st.empty()){
			ans.push_back(st.top());
			st.pop();
		}
		ans.push_back(T);
		printf("%d ",ans.size());
		for(int v:ans) printf("%d ",v);
		puts("");
		ans.clear();
		now=t1.se;
		while(now!=u){
			st.push(now);
			now=fa[now];
		}
		st.push(u);
		while(!st.empty()){
			ans.push_back(st.top());
			st.pop();
		}
		now=T;
		while(now!=rev[t1.fi]){
			st.push(now);
			now=fa[now];
		}
		st.push(rev[t1.fi]);
		while(!st.empty()){
			ans.push_back(st.top());
			st.pop();
		}
		printf("%d ",ans.size());
		for(int v:ans) printf("%d ",v);
		exit(0);
	}
	low[u]=t1;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		charu(x,y),charu(y,x);
	}
	for(int i=1;i<=n;++i) if(!dfn[i]) dfs(i);
	puts("NO");
	return 0;
}

```



---

## 作者：绝顶我为峰 (赞：1)

容易得到三条不相交的公共路径意味着两个环相交，而判断环相交就非常简单了，直接跑出 dfs 树然后树上差分即可，如果有一条树边被覆盖了两次以上就有环相交。

那么我们现在假设已经找到了一条这样的树边，那么我们直接遍历所有非树边，判断这条非树边是否覆盖了当前这个树边，由于所有非树边都是返祖边，因此这个工作容易用 LCA 解决。

找到两条覆盖了这条树边的非树边 $(u1,v1)(u2,v2)$ 之后，我们看看怎样找路径,这时候图大概长这样（$x,y$ 是那条树边的两端点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/yaqcvt5c.png)

于是就很清晰了，我们要找的路径是 $u2\rightarrow lca$ 的三条路径，直接暴力找就好了。

但在写法上我把 $u,v$ 中深度小的当做了 $u1$ 和 $v1$，这样可能会导致 $u1,v1$ 之间并没有边，然后会挂掉，所以要打一个 tag 记录一下。

还要注意图不一定连通，所以每个联通块都要这么跑一遍。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct edge
{
    int nxt,to;
}e[200001<<1];
bool vis[200001];
vector<int> g[200001],ans;
vector<pair<int,int> > nt;
int n,m,dep[200001],d[200001],tot,h[200001],fa[200001][21];
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
inline void add(int x,int y)
{
    e[++tot].nxt=h[x];
    h[x]=tot;
    e[tot].to=y;
}
inline int lca(int x,int y)
{
    if(dep[x]<dep[y])
        x^=y^=x^=y;
    for(register int d=dep[x]-dep[y],i=0;1<<i<=d;++i)
        if(d&(1<<i))
            x=fa[x][i];
    if(x==y)
        return x;
    for(register int i=20;~i;--i)
        if(fa[x][i]^fa[y][i])
        {
            x=fa[x][i];
            y=fa[y][i];
        }
    return fa[x][0];
}
inline void solve(int x,int y)
{
    puts("YES");
    int cnt=0,u[3]={0},v[3]={0};
    bool tag=0;
    for(register int i=0;i<(int)nt.size();++i)
    {
        u[0]=nt[i].first,v[0]=nt[i].second;
        if(dep[u[0]]>dep[v[0]])
            u[0]^=v[0]^=u[0]^=v[0];
        if(lca(x,u[0])==u[0]&&lca(y,v[0])==y)
        {
            ++cnt;
            u[cnt]=u[0];
            v[cnt]=v[0];
        }
        if(cnt==2)
            break;
    }
    if(dep[u[1]]>dep[u[2]])
    {
        u[1]^=u[2]^=u[1]^=u[2];
        tag^=1;
    }
    if(dep[v[1]]>dep[v[2]])
    {
        v[1]^=v[2]^=v[1]^=v[2];
        tag^=1;
    }
    int LCA=lca(v[1],v[2]),node=LCA;
    /*u2->x->y->lca*/
    ans.clear();
    ans.push_back(node);
    while(node!=u[2])
    {
        node=fa[node][0];
        ans.push_back(node);
    }
    reverse(ans.begin(),ans.end());
    printf("%d ",(int)ans.size());
    for(register int i=0;i<(int)ans.size();++i)
        printf("%d ",ans[i]);
    puts("");
    /*end*/
    /*u2->u1->v1->lca*/
    ans.clear();
    ans.push_back(u[2]);
    node=u[2];
    while(node!=u[1])
    {
        node=fa[node][0];
        ans.push_back(node);
    }
    node=v[1+tag];
    ans.push_back(node);
    while(node!=LCA)
    {
        node=fa[node][0];
        ans.push_back(node);
    }
    printf("%d ",(int)ans.size());
    for(register int i=0;i<(int)ans.size();++i)
        printf("%d ",ans[i]);
    puts("");
    /*end*/
    /*u2->v2->lca*/
    ans.clear();
    ans.push_back(u[2]);
    node=v[2-tag];
    ans.push_back(node);
    while(node!=LCA)
    {
        node=fa[node][0];
        ans.push_back(node);
    }
    printf("%d ",(int)ans.size());
    for(register int i=0;i<(int)ans.size();++i)
        printf("%d ",ans[i]);
    puts("");
    /*end*/
}
void dfs1(int k,int f,int deep)
{
    dep[k]=deep;
    vis[k]=1;
    fa[k][0]=f;
    for(register int i=1;i<=20;++i)
        fa[k][i]=fa[fa[k][i-1]][i-1];
    for(register int i=h[k];i;i=e[i].nxt)
    {
        if(e[i].to==f)
            continue;
        if(vis[e[i].to])
        {
            ++d[k];
            --d[e[i].to];
            nt.push_back(make_pair(k,e[i].to));
        }
        else
            if(!dep[e[i].to])
            {
                g[k].push_back(e[i].to);
                dfs1(e[i].to,k,deep+1);
            }
    }
    vis[k]=0;
}
void dfs2(int k,int f)
{
    for(register int i=0;i<(int)g[k].size();++i)
    {
        dfs2(g[k][i],k);
        d[k]+=d[g[k][i]];
    }
    if(d[k]>=2)
    {
        solve(f,k);
        exit(0);
    }
}
int main()
{
    n=read(),m=read();
    for(register int i=1;i<=m;++i)
    {
        int x=read(),y=read();
        add(x,y);
        add(y,x);
    }
    for(register int i=1;i<=n;++i)
        if(!dep[i])
        {
            nt.clear();
            dfs1(i,0,1);
            dfs2(i,0);
        }
    puts("NO");
    return 0;
}
```


---

## 作者：约瑟夫用脑玩 (赞：1)

~~为什么感觉第一篇题解的图是错的啊~~

这里提供一种简单的实现，找路径时只用跳父亲，无需遍历。

要求两个点之间有至少三条完全不相交的简单路径就是要找两个有相交边的环。

显然先将连通块间生成一个生成树，那么找两条非树边覆盖了同一段路径即可。

所以我们暴力给路径打标记，如果已被打过标记就说明有非树边相交了。

将非树边拿出来，分别设为 a-b 和 c-d，相交的路径为 x-y：

![](https://cdn.luogu.com.cn/upload/image_hosting/qeanbdag.png)

注意，这里的 a-x、b-y、c-x、d-y 都可能退化为一个点，但没有影响。

但要输出路径，为了方便，我们将某一端(如 a)当作根，将树拿起来，变成了这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/02l8uzzc.png)

那么路径就是：

- x->a->b->y

- x->c->d->y

- x->y

由于树已经拿起来了(以 a 为根)，那么 x->a、x->c、b->y、d->y 就可以直接往上跳父亲来找到。

[核心代码](https://www.luogu.com.cn/paste/p523q2yt)

---

## 作者：AKPC (赞：0)

结论题的最好解题方式就是观察样例。样例 $1$ 用处不大，样例 $2$ 给的图带有两个环，且两个环相互重叠。这也告诉我们只要图上有两个有重叠的环，就一定有答案。证明也十分地简单。

如果需要找有重叠的环，一个经典套路是生成树然后树上差分，但实际上树上差分并不好写。不过，因为只需统计重叠次数 $\geq2$ 的边，所以直接暴力覆盖，这样复杂度是线性的。

如果找到了有重叠的边，那么就有方案可寻，本题的输出方案直接模拟一遍跳边即可。

---

## 作者：liaiyang (赞：0)

首先建出 dfs 树，我们找到两条有交的返祖边，分类讨论返祖边包含，相交，末端位于不同子树三种关系，构造方案。

设我们找到的两条返祖边为 $(x_1,y_1)$，$(x_2,y_2)$ 并假定 $dep_{x_1}\le dep_{x_2},dep_{x_1}<dep_{y_1},dep_{x_2}<dep_{y_2}$，则我们有以下三种情况：

$\operatorname{lca}(y_1,y_2)=y_1$，此时我们构造 $y_1\rightarrow x_1 \rightarrow x_2$，$y_1 \rightarrow x_2$，$y_1\rightarrow y_2 \rightarrow x_2$ 三条路径。

$\operatorname{lca}(y_1,y_2)=y_2$，此时我们构造 $y_2\rightarrow z\rightarrow x_2$，$y_2 \rightarrow x_2$，$y_2\rightarrow y_1 \rightarrow x_1 \rightarrow x_2$ 三条路径。

$\operatorname{lca}(y_1,y_2)\neq y_1\land\operatorname{lca}(y_1,y_2)\neq y_2$，此时我们构造 $\operatorname{lca}(y_1,y_2)\rightarrow x_2$，$\operatorname{lca}(y_1,y_2)\rightarrow y_2 \rightarrow x_2$，$\operatorname{lca}(y_1,y_2)\rightarrow y_1\rightarrow x_1\rightarrow x_2$ 三条路径。


我们可以暴力枚举相交部分，由于我们只会在答案处暴力，暴力完会直接结束程序，所以代码中的实现方式复杂度是线性的。

时间复杂度 $O(n)$，注意图不保证连通。

```cpp
#include<bits/stdc++.h>
using namespace std;
// #pragma GCC optimize(1)
// #pragma GCC optimize(2)
// #pragma GCC optimize(3,"Ofast")
#define int long long
#define y0 Y0
#define y1 Y1
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define min(a,b) (a<b?a:b) 
#define max(a,b) (a>b?a:b)
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-(x)))
#define abs(x) ((x)<0?-(x):(x))
#define submod(x,y,mod) (((x-=y)<0)&&(x+=mod))
#define addmod(x,y,mod) (((x+=y)>=mod)&&(x-=mod))
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
// #define fflush() fwrite(obuf,1,O-obuf,stdout)
// char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
// #define putchar(x) (O-obuf<(1<<21)?*O++=(x):(fwrite(obuf,1,1<<21,stdout),O=obuf,*O++=(x)))
inline int read(int u=0, char c=getchar(), bool f=false){
    for(;!isdigit(c);c=getchar()) f|=c=='-';
    for(;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+(c^'0');
    return f?-u:u;
}
inline void read(string &s,char c=getchar()){
    for(;c<'a'||c>'z';c=getchar());s="";
    for(;c>='a'&&c<='z';c=getchar()) s+=c;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar((x%10)^'0');
}
inline void wt(string s){for(char c:s) putchar(c);}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1,iinf=1e18;
const int mod=998244353,g=3,gi=332748118;
const int N=2e5+10,logN=20;
vector<int>e[N],tmp;
int dep[N],st[N],ed[N];
int n,m,f[N][logN];
int kth(int x,int k){
    for(int j=19;j>=0;j--) if(k>=(1<<j)) x=f[x][j],k-=(1<<j);
    return x;   
}
int lca(int x,int y){
    if(dep[x]>dep[y]) swap(x,y);    
    y=kth(y,dep[y]-dep[x]);
    if(x==y) return x;
    for(int j=19;j>=0;j--) if(f[x][j]!=f[y][j]) x=f[x][j],y=f[y][j];
    return f[x][0];
}
void dfs(int x,int fa){
    f[x][0]=fa;dep[x]=dep[fa]+1;
    for(int j=1;j<=19;j++) f[x][j]=f[f[x][j-1]][j-1];
    for(int i:e[x]) if(i!=fa){
        if(!dep[i]) dfs(i,x);
        else if(dep[x]<dep[i]){
            for(int s=i;s!=x;s=f[s][0]){
                if(st[s]||ed[s]){
                    int nst=x,ned=i;wt("YES\n");tmp.clear();
                    int u1=st[s],v1=ed[s],u2=nst,v2=ned,lc=lca(v1,v2);
                    // cout<<lc<<" "<<u1<<" "<<v1<<" "<<u2<<" "<<v2<<endl;
                    if(dep[u1]>dep[u2]) swap(u1,u2),swap(v1,v2);
                    if(lc!=v1&&lc!=v2){
                        wt(dep[u2]-dep[u1]+1+dep[v1]-dep[lc]+1,' ');
                        for(int j=u2;j!=u1;j=f[j][0]) wt(j,' ');wt(u1,' ');
                        for(int j=v1;j!=lc;j=f[j][0]) wt(j,' ');wt(lc,'\n');
                        wt(dep[v2]-dep[lc]+2,' ');wt(u2,' ');
                        for(int j=v2;j!=lc;j=f[j][0]) wt(j,' ');wt(lc,'\n');
                        wt(dep[lc]-dep[u2]+1,' ');
                        for(int j=lc;j!=u2;j=f[j][0]) tmp.push_back(j);tmp.push_back(u2);
                        for(int j=tmp.size()-1;j>=0;j--) wt(tmp[j]," \n"[!j]);
                    }
                    else if(lc==v1){
                        wt(dep[u2]-dep[u1]+2,' ');
                        for(int j=u2;j!=u1;j=f[j][0]) wt(j,' ');
                        wt(u1,' ');wt(v1,'\n');
                        wt(dep[v2]-dep[v1]+2,' ');wt(u2,' ');
                        for(int j=v2;j!=v1;j=f[j][0]) wt(j,' ');
                        wt(v1,'\n');wt(dep[v1]-dep[u2]+1,' ');
                        for(int j=v1;j!=u2;j=f[j][0]) tmp.push_back(j);tmp.push_back(u2);
                        for(int j=tmp.size()-1;j>=0;j--) wt(tmp[j]," \n"[!j]);
                    }
                    else{
                        wt(dep[u2]-dep[u1]+1+dep[v1]-dep[v2]+1,' ');
                        for(int j=u2;j!=u1;j=f[j][0]) wt(j,' ');wt(u1,' ');
                        for(int j=v1;j!=v2;j=f[j][0]) wt(j,' ');wt(v2,'\n');
                        wt(2,' ');wt(u2,' ');wt(v2,'\n');
                        wt(dep[v2]-dep[u2]+1,' ');
                        for(int j=v2;j!=u2;j=f[j][0]) tmp.push_back(j);tmp.push_back(u2);
                        for(int j=tmp.size()-1;j>=0;j--) wt(tmp[j]," \n"[!j]);                 
                    }
                    exit(0);
                }
                st[s]=x,ed[s]=i;
            }
        }
    }
}
main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=rd,m=rd;
    for(int i=1;i<=m;i++){
        int x=rd,y=rd;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for(int i=1;i<=n;i++) if(!dep[i]) dfs(i,i);
    wt("NO\n");
    // fflush();
    return 0;
}
```

---

## 作者：关怀他人 (赞：0)

#### Solution
不难发现，有解当且仅当存在两个环有边相交。

对于每个连通块先随便找一颗生成树，通过树上差分找出一条被至少两个环经过的边，然后从这条边中深度较深那个点去dfs它的子树，找到两条对应的非树边的起点，分别记为$u_1$和$u_2$，它们对应的非树边的终点记为$v_1$和$v_2$，且假设$dep_{v_1}>dep_{v_2}$

那么最终的答案的起点就是$LCA(u_1,u_2)$，终点就是$v_1$，然后直接把路径取出来即可。

时间复杂度$\mathcal O(n)$
#### Code
```cpp
int n,m,len,u1,u2,v1,v2,p;
int head[MAXN],vis[MAXN],f[MAXN],dep[MAXN],d[MAXN];
vector<int> vec,tmp;

struct Edge{
    int to,next;
} e[MAXN << 1];

void add_edge(int u,int v){
    e[++len] = (Edge){v,head[u]};
    head[u] = len;
}

void dfs1(int u,int fa){
    f[u] = fa; vis[u] = 1; dep[u] = dep[fa] + 1;
    for(int i = head[u];i != -1;i = e[i].next){
        int v = e[i].to;
        if(v == fa) continue;
        if(!vis[v]) dfs1(v,u), d[u] += d[v]; 
        else if(dep[v] < dep[u]) d[u] += 1, d[v] -= 1;
    }
}

void dfs2(int u,int fa){
    for(int i = head[u];i != -1;i = e[i].next){
        int v = e[i].to;
        if(dep[v] == dep[u] + 1) dfs2(v,u);
        else if(dep[v] < dep[p] && v != fa){
            if(u1) u2 = u, v2 = v;
            else u1 = u, v1 = v;
        }
        if(u2) return;
    }
}

int LCA(int u,int v){
    while(u != v){
        if(dep[u] > dep[v]) u = f[u];
        else v = f[v];
    }
    return u;
}

void GetPath(int u,int v){
    int t = v;
    if(dep[u] < dep[v]){
        tmp.clear(); v = f[v];
        while(u != v) 
            tmp.push_back(v), v = f[v];
        tmp.push_back(u);
        for(int i = tmp.size() - 1;i >= 0;i--)
            vec.push_back(tmp[i]);
    }else{
        while(u != v)
            vec.push_back(u), u = f[u];
    }
    vec.push_back(t);
}

void print(){
    printf("%d",vec.size());
    for(int x : vec) printf(" %d",x);
    printf("\n"); vec.clear();
}

int main(){
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i = 1,u,v;i <= m;i++){
        scanf("%d%d",&u,&v);
        add_edge(u,v); add_edge(v,u);
    }
    for(int i = 1;i <= n;i++){
        if(!vis[i])
            dfs1(i,0);
    }
    for(int i = 1;i <= n;i++){
        if(d[i] >= 2){
            p = i;
            break;
        }
    }
    if(!p) {puts("NO"); return 0;}
    puts("YES");
    dfs2(p,f[p]);
    if(dep[v2] < dep[v1]) swap(u1,u2), swap(v1,v2);
    int lca = LCA(u1,u2);

    GetPath(lca,u1);
    GetPath(v1,v2);
    print();

    GetPath(lca,u2);
    vec.push_back(v2);
    print();

    GetPath(lca,v2);
    print();
    return 0;
}
```

---

## 作者：lgswdn_SA (赞：0)

感觉这道题的图论很好玩，写一个题解讲一下我（看题解后）的思考。

考虑画出这 $3$ 条路径。

![image.png](https://i.loli.net/2020/09/07/kWdS5Kca3ysLPZI.png)

我们可以发现，本质上这 $3$ 条路径构成了两个有重合边的环。

![image.png](https://i.loli.net/2020/09/07/stXxUJ17ow2miyk.png)

然后如果有两个重合边的环，那么同样也可以得到三条不相交路径（第一个环除去重叠路径，第二个环除去重叠路径以及重叠路径）。

所以有没有这三条不相交的路径，转化为了**有没有两个重叠的环**。而上面这个条件，就是仙人掌的定义。所以我们只需要判断这个图是否是仙人掌。方法的话就是看每一个边是否属于两个及以上的环（做法和 tarjan 有一点点像），具体实现细节看代码。

然后考虑如何求出路径。首先我们可以通过 dfs （判断仙人掌）的时候找到每一边可以经过哪些非树边（众所周知，非树边会导致环）。现在考虑两条非树边 $(u_1,v_1)$ 和 $(u_2,v_2)$。

（虚边代表中间还有很多节点）  
![image.png](https://i.loli.net/2020/09/07/dRFDcTNxOLk2jWi.png)

很显然这里的两个环是 $(u_1,v_1,lca), (u_1,u_2,v_2,lca)$，于是三条路径为 $u_1\to lca, u_1\to v_1\to lca, u_1\to u_2\to v_2\to lca$。

求 $lca$ 直接暴力爬树然后记录即可即可。时间复杂度 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;

struct edge {int to,nxt;}e[N*2]; int hd[N],tot;
void add(int u,int v) {e[++tot]=(edge){v,hd[u]};hd[u]=tot;}

int n,m,d[N],f[N],u1,v1,u2,v2,l[N],r[N];
bool vst[N],in[N],flag;
void dfs(int u,int fa) {
	vst[u]=in[u]=1, d[u]=d[fa]+1, f[u]=fa;
	for(int i=hd[u],v;i;i=e[i].nxt) {
		if((v=e[i].to)==fa) continue;
		else if(!vst[v]) dfs(v,u);
		else if(in[v]) {
			for(int p=u;p!=v;p=f[p]) {		//找到返祖边，遍历树边 
				//l代表在返祖边的子孙，r代表返祖边的祖先 
				if(!l[p]||!r[p]) l[p]=u, r[p]=v;	//第一条返祖边 
				else {								//集齐两条返祖边
					u1=r[p], u2=v, v1=l[p], v2=u;
					flag=1; return;
				}
			}
		}
		if(flag) return;
	}
	in[u]=0;
}
vector<int>route;
int lca(int u,int v) {
	if(d[u]<d[v]) swap(u,v);
	while(d[u]>d[v]) u=f[u];
	while(u!=v) u=f[u], v=f[v];
	return u;
}
void find(int u,int v) {
	for(int p=u;p!=v;p=f[p]) route.push_back(p);
	route.push_back(v);
}
void write(bool type) {
	printf("%d ",route.size());
	if(type==0) for(int i=0;i<route.size();i++) printf("%d ",route[i]);
	else for(int i=route.size()-1;i>=0;i--) printf("%d ",route[i]);
	puts("");
	route.clear();
}
void print() {
	if(!u1||!u2||!v1||!v2) {puts("NO"); return;}
	puts("YES");
	if(d[u1]<d[u2]) swap(u1,u2), swap(v1,v2);
	int la=lca(v1,v2);
	find(la,u1); write(1);
	route.push_back(u1), find(v1,la); write(0);
	find(u1,u2), find(v2,la); write(0);
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++) scanf("%d%d",&u,&v), add(u,v), add(v,u);
	for(int i=1;i<=n;i++) if(!vst[i]&&!flag) dfs(i,0);
	print();
	return 0;
}
```

---

## 作者：liuyifan (赞：0)

## 判断一下是否为仙人掌,然后输出路径即可

1.什么是仙人掌?

仙人掌是不含自环的,一条边最多属于一个简单环的无向连通图.

从定义不难看出树其实也是仙人掌的一种,也就是说这几个概念的关系大概是:

树是一种特殊的仙人掌,仙人掌是一类特殊的无向连通图.

从图片来观察一下. 

![](https://www.lydsy.com/JudgeOnline/images/1023/1.jpg)

2.关于仙人掌这里就不多说了,说一下如何找起点

因为路径不能有交点，那么终点一定是两条返祖边的下面端点的LCA，起点就是两条返祖边上端点中较深的点，因为如果是较浅的点的话，就会和树边上的路径有交点,就得到了起点的具体位置

3.你们最期待的code：（不要抄袭！！！）
```cpp
#include<bits/stdc++.h>
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
int dep[200005],fa[200005],f[200005],d[200005],a,b,n,m,l1,l2,r1,r2,s,t,x,y;
vector<int>e[200005];
inline void dfs(reg int x,reg int prt)
{
    dep[x]=dep[prt]+1;
    fa[x]=prt;
    for(reg int i=0;i<e[x].size();i++)
    if(!dep[e[x][i]])dfs(e[x][i],x);
    else if(dep[e[x][i]]<dep[x]&&e[x][i]!=prt)
    f[e[x][i]]--,f[x]++;
    f[prt]+=f[x];
}
inline void dfs2(reg int x)
{
    for(reg int i=0;i<e[x].size();i++)
    if(dep[e[x][i]]==dep[x]+1)
    {
        dfs2(e[x][i]);
        if(l2)return;
    }
    else if(dep[e[x][i]]<dep[s]&&e[x][i]!=fa[x])
    {
        if(l1)r2=x,l2=e[x][i];
        else r1=x,l1=e[x][i];
        if(l2)return;
    }
}//搜索仙人掌
inline void go(reg int l,reg int r)
{
    reg int k=t;
    t+=abs(dep[r]-dep[l])+1;
    if(dep[l]>dep[r])
    for(reg int i=l,j=k+1;j<=t;i=fa[i],j++)d[j]=i;
    else for(reg int i=r,j=t;j>k;i=fa[i],j--)d[j]=i;
}//查找
int main()
{
    scanf("%d%d",&n,&m);
    for(reg int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        e[a].push_back(b);
        e[b].push_back(a);
    }//二维vector的操作,其实可以理解为n个通过下标访问的vector
    for(reg int i=1;i<=n;i++)if(!dep[i])dfs(i,0);//dfs预处理
    for(reg int i=1;i<=n;i++)
    if(f[i]>1)
    {
        s=i;
        break;
    }
    if(!s)return puts("NO"),0;//直接特判不行的情况
    dfs2(s);
    puts("YES");
    if(dep[l1]>dep[l2])swap(l1,l2),swap(r1,r2);
    for(x=r1,y=r2;x!=y;)dep[x]>dep[y]?x=fa[x]:y=fa[y];
    t=0;
    go(x,r1);
    go(l1,l2);
    printf("%d ",t);
    for(reg int i=1;i<=t;i++)printf("%d ",d[i]);//输出结果
    cout<<endl;
    t=0;
    go(x,r2);//依次处理
    go(l2,l2);
    printf("%d ",t);
    for(reg int i=1;i<=t;i++)printf("%d ",d[i]);//同上
    cout<<endl;
    t=0;
    go(x,l2);//同上
    printf("%d ",t);
    for(reg int i=1;i<=t;i++)printf("%d ",d[i]);//同上
    return 0;
}
```

部分表述转载自[CSDN](https://www.cnblogs.com/nbwzyzngyl/p/8029865.html)

有关仙人掌的更多内容详见[CSDN2](https://blog.csdn.net/creationaugust/article/details/48007069)

---

