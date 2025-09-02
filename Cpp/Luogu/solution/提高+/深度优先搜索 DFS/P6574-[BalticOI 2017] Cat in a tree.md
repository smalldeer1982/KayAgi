# [BalticOI 2017] Cat in a tree

## 题目描述

小猫在一棵有 $n$ 个节点的树上，它通过标记节点来划分领地。  
它标记的节点满足彼此距离不小于 $d$。  
两节点之间的距离指的是两点间路径上节点的个数（包括端点）。   
求小猫最多能标记多少个节点。

## 说明/提示

#### 数据范围与约定

**本题采用捆绑测试。**

- Subtask 1（11 pts）：$n \le 18$。
- Subtask 2（40 pts）：$n \le 1500$。
- Subtask 3（49 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,d \le 2 \times 10^5$，$0 \le x_i < i$。

#### 说明

**翻译自 [BOI 2017 D2](https://boi.cses.fi/files/boi2017_day2.pdf) T1 Cat in a tree。**  
翻译者：@[一只书虫仔](https://www.luogu.com.cn/user/114914)。

## 样例 #1

### 输入

```
4 3
0
0
1```

### 输出

```
2```

## 样例 #2

### 输入

```
3 1000
0
0```

### 输出

```
1```

# 题解

## 作者：Marser (赞：6)

省选前最后一篇题解，感觉是个比较清新的贪心题。  
Tweetuzki 神仙写了长链剖分和线段树，私以为不必要。
### 题意
定义点集 $V$ 为树的一个 $k-$独立集，当且仅当 $\forall x,y\in V,dis(x,y)\ge k$。  
给定一棵大小为 $n$ 的树，求最大 $k-$独立集的大小。  
$1\le n,k\le 2\times 10^5$。

### 题解
首先证明一个重要结论：对于以 $x$ 为根的子树，假设该子树的最大 $k-$独立集大小为 $f_x$，则 $x$ 子树对 $x$ 的父亲的贡献为 $f_x-1$ 或 $f_x$。

这个上界非常显然，不作赘述。  
考虑证明这个下界。假设我们当前在求子树 $x$ 的答案，正在考虑合并子树 $y$ 的答案，我们令 $a,b$ 分别表示之前已经选中的点中，深度最小点和非严格次小点，$c,d$ 分别表示子树 $y$ 中深度最小点和非严格次小点，$d_1=dis(x,a),d_2=dis(x,b),d_3=dis(y,c),d_4=dis(y,d)$，显然存在 $d_1\le d_2,d_3\le d_4$。  
$\because dis(a,b)\ge k$，$x$ 是 $a,b$ 的公共祖先    
$\therefore d_1+d_2\ge k$  
同理，$d_3+d_4\ge k$。

考虑这样一个贪心策略：
- 如果 $d_1+d_3+1\ge k$，则子树 $y$ 的所有节点都可以计入答案，取到上界 $f_y$。
- 如果 $d_1+d_3+1 < k$，
	- 如果 $d_3+1>d_1$，在最终答案中删除 $a$，加入子树 $y$ 的所有节点，方案仍然合法且最优，贡献为下界 $f_y-1$。
    - 如果 $d_3+1\le d_1$，加入子树 $y$ 除 $c$ 以外的所有节点，方案仍然合法且最优，贡献为下界 $f_y-1$。
    
对于后面两种策略，最优性不难证明。由于一定无法取到 $f_y$，因此只删去一个点一定是最优的。  
对于 $d_3+1>d_1$ 的情况，最终只选择了 $b,c,d$ 三个点。由于 $dis(c,d)\ge k$，我们只需要证明 $dis(b,c)\ge k$ 即可。  
$\because d_1<d_3+1,d_1+d_2\ge k$  
$\therefore dis(b,c)=d_2+d_3+1 > d_2+d_1\ge k$  
$\therefore dis(b,c)>k$

对于 $d_3+1\le d_1$ 的情况，最终选择了 $a,b,d$ 三个点，我们只需证明 $dis(a,d)\ge k$。  
$\because d_3+1\le d1,d_3+d_4\ge k$  
$\therefore dis(a,d)=d_1+d_4+1\ge d_3+d_4+2\ge k+2$  
$\therefore dis(a,d)>k$

所以，每棵子树的贡献至少为 $f_x-1$。

我们在 dfs 的过程中维护每棵子树最大 $k-$独立集的大小 $f_x$，以及所有取到最大值的方案中，深度最小的点的最大深度 $dep_x$。
- 当 $dep_x+dep_y+1\ge k$ 时，$dep_x\gets \min(dep_x,dep_y+1)$，$f_x\gets f_x+f_y$。
- 当 $dep_x+dep_y+1< k$ 时，$dep_x\gets \max(dep_x,dep_y+1)$，$f_x\gets f_x+f_y-1$。

合并完所有子树后，再判断一下能不能选根节点即可。时间复杂度 $O(n)$，代码极为简单。

### 代码
```cpp
#include<bits/stdc++.h>
#define reg register
typedef long long ll;
using namespace std;
const int MN=2e5+5;
int to[MN<<1],nxt[MN<<1],h[MN],cnt;
inline void ins(int s,int t){
	to[++cnt]=t;nxt[cnt]=h[s];h[s]=cnt;
	to[++cnt]=s;nxt[cnt]=h[t];h[t]=cnt;
}
int n,m,f[MN],dep[MN];
void dfs(int st,int fa=0){
	dep[st]=1e9;
	for(reg int i=h[st];i;i=nxt[i])
		if(to[i]!=fa){
			dfs(to[i],st);
			if(dep[st]+1+dep[to[i]]>=m){
				f[st]+=f[to[i]];
				dep[st]=min(dep[st],dep[to[i]]+1);
			}
			else{
				f[st]+=f[to[i]]-1;
				dep[st]=max(dep[st],dep[to[i]]+1);
			}
		}
	if(dep[st]>=m)f[st]++,dep[st]=0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(reg int i=2,x;i<=n;i++)
		scanf("%d",&x),ins(i,x+1);
	dfs(1);printf("%d\n",f[1]);
	return 0;
}
```

---

## 作者：xj22yangyichen (赞：4)

阅读题面发现这题和 [P3942 将军令](https://www.luogu.com.cn/problem/P3942) 题意基本相反，前者是求树上最多有几个点距离 $\ge d$，后者大意是求树上最少有几个点距离 $\le d$，因此考虑相似的贪心策略，即每次取深度最大的点。

## 贪心正确性证明

每次取一个点都会使得与它距离小于 $d$ 的点不能再被取（不妨称为“失效”），而因为取深度最小的点而导致失效的节点数小于取深度次小的点而导致失效的节点数。

举个例子，假设 $d = 3$，在下图这棵树中，如果选择节点 6，会导致节点 4，5，6 无法选择；

![](https://cdn.luogu.com.cn/upload/image_hosting/1ra5302a.png)

而如果选择节点 5，会导致节点 1，4，5，6，8 都无法选择，这其中包括了上面的 4，5，6，因此选择 6 更优。

![](https://cdn.luogu.com.cn/upload/image_hosting/4ywsqpzm.png)

如果存在节点 $u$，$v$ 深度相同，可以证明先选任意一个，答案相同。若选择节点 $u$ 会导致 $v$ 无法选择，即 $u$ 和 $v$ 的距离小于 $d$，那么选择两个节点中的任意一个，对答案的贡献相同；反之，根据贪心策略，$u$ 和 $v$ 都会被选，答案与选择的先后顺序无关。

## 怎样计算当前节点能否选择

一种暴力的思路是，每选择一个节点，就将与它距离小于 $d$ 的点都标记为不可选，复杂度为 $O(n^2)$，可以得到 51 分。

暴力的方法中，一次标记操作时间复杂度为 $O(n)$，而查询当前节点能否选择的时间复杂度为 $O(1)$，于是考虑平衡两种操作的时间复杂度。

每次选择一个节点后，仅向上更新该节点的祖先到该节点的距离，直到某祖先到该节点的距离超过 $d$ 时停止更新；查询一个节点能否选择时，同样向上查找，如果存在一个祖先到它的距离加上该祖先到选择过的节点的距离小于 $d$，则该节点不可被选择，否则可以选择。

## 复杂度分析

直观地考虑两种极端情况：

当树的形态为链时，选择的节点为 $n$，$n-d$，$n-2d$ 以此类推，每两个节点中间的节点在 check 时都会 $O(1)$ 地被判断为不能选择，而树上每个节点都被标记一次，总时间复杂度为 $O(n)$。

当树的形态为满二叉树时，可以通过优化（见代码注释）使每一层的节点被选择时，其上方的节点至多被标记一次，从而标记操作的总次数为 $\frac{n}{2} + \frac{n}{4} + \cdots + 1 = n$，查询操作同理，总时间复杂度为 $O(n)$。

综上所述，结合随机数据检验，以上做法的时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

## 代码

```cpp
#include<queue>
#include<stdio.h>
#include<ctype.h>
#include<utility>
#include<string.h>
#include<algorithm>
#define N 200001
#define inf 0x3f3f3f3f
using namespace std;

int read(){
	int ans = 0;
	char ch = getchar();
	while(!isdigit(ch)){
		ch = getchar();
	}
	while(isdigit(ch)){
		ans *= 10;
		ans += ch ^ 48;
		ch = getchar();
	}
	return ans;
}

int n, d, head[N], cnt, fa[N], dep[N], dist[N];
struct edge{
	int to, next;
}e[N << 1];
void add(int u, int v){
	e[++cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}
priority_queue<pair<int, int>> q;

void dfs(int u, int f){
	fa[u] = f;
	dep[u] = dep[f] + 1;
	q.push({dep[u], u});
	for(int i = head[u]; i; i = e[i].next){
		int v = e[i].to;
		if(v == f) continue;
		dfs(v, u);
	}
}

bool check(int u, int dis){
	if(!u) return 1;
	if(dis > d) return 1;
	if(dis + dist[u] < d) return 0;
	return check(fa[u], dis + 1);
}

void update(int u, int dis){
	if(!u || dis >= d) return;
	if(dist[u] <= dis) return;//优化：被同一层的其它节点更新过的节点，其本身和祖先都不用再更新
	dist[u] = dis;
	update(fa[u], dis + 1);
}

int main(){
	int u;
	n = read(), d = read();
	for(int i = 2; i <= n; i++){
		u = read() + 1;
		add(i, u), add(u, i);
	}
	dfs(1, 0);
	
	int ans = 0;
	memset(dist, inf, sizeof(dist));
	while(!q.empty()){
		int u = q.top().second;
		q.pop();
		if(check(u, 0)){
			ans++;
			update(fa[u], 1);
		}
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：Tweetuzki (赞：4)

> 给出一棵 $n$ 个点的树。定义 $k-$ 独立集为一个点集，这个点集内满足任意两点间距离不小于 $k$。求这棵树的最大 $d-$ 独立集。
> 
> $n, d \le 2 \times 10 ^ 5$。

欢迎观赏睿智做法！~~贪心不够，数据结构来凑~~

直接上一个暴力 DP，$f_{u, i}$ 表示选完 $u$ 子树内的点，最后一个选的点与 $u$ 的距离为 $i$ 的最多选点个数。

考虑加入一个儿子 $v$ 的子树时如何转移。

1. 儿子部分不选点，没有更新，$f_{u, i} = f_{u, i}$。
1. 已加入部分不选点，全部从儿子部分过继过来。即 $f_{u, i}  = \max(f_{u, i}, f_{v, i + 1})$。
1. 已加入部分和儿子部分都选点，不妨设儿子部分最后一个选的点与 $v$ 距离为 $j$，则当且仅当 $i + j + 1 \ge d$ 的时候可以转移，转移到 $\min(i, j + 1)$ 的位置。即 $f_{u, \min(i, j + 1)} = \max(f_{u, \min(i, j + 1)}, f_{u, i} + f_{v, j})$。

前两种直接转移就是线性的，第三种用前缀 / 后缀最大值优化后也可以做到线性转移。到此时间复杂度 $\mathcal{O}(n ^ 2)$。

注意到 DP 状态与深度有关，直接上长链剖分进行优化。按照长剖套路，DP 数组直接从偏爱儿子过继过来，其它儿子暴力转移。因为这里的 DP 数组涉及到了修改和取最大值，要套一个线段树来代替之前的前缀 / 后缀最大值加速转移的方法。

长剖是线性的，只有个线段树的 $\log$。所以时间复杂度 $\mathcal{O}(n \log n)$。

代码：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>

const int MaxN = 200000, MaxV = (1 << 19);

struct graph_t {
  int cnte;
  int head[MaxN + 5], to[MaxN + 5], next[MaxN + 5];

  inline void addEdge(int u, int v) {
    cnte++;
    to[cnte] = v;
    next[cnte] = head[u];
    head[u] = cnte;
  }
};

int N, D;
int Fa[MaxN + 5], Len[MaxN + 5], Wson[MaxN + 5];
int Id[MaxN + 5], Dfn[MaxN + 5], Dfc;
graph_t Gr;

struct SegTree {
  int L[MaxV + 5], R[MaxV + 5];
  int Mx[MaxV + 5];

  void buildTree(int left, int right, int i = 1) {
    L[i] = left, R[i] = right;
    Mx[i] = 0;
    if (L[i] == R[i]) return;
    int mid = (L[i] + R[i]) >> 1;
    buildTree(left, mid, i << 1);
    buildTree(mid + 1, right, i << 1 | 1);
  }

  void updateTree(int pos, int val, int i = 1) {
    if (L[i] == R[i]) {
      Mx[i] = std::max(Mx[i], val);
      return;
    }
    int mid = (L[i] + R[i]) >> 1;
    if (pos <= mid) updateTree(pos, val, i << 1);
    else updateTree(pos, val, i << 1 | 1);
    Mx[i] = std::max(Mx[i << 1], Mx[i << 1 | 1]);
  }

  int queryTree(int left, int right, int i = 1) {
    if (left > right) return 0;
    if (L[i] == left && R[i] == right) return Mx[i];
    int mid = (L[i] + R[i]) >> 1;
    if (right <= mid) return queryTree(left, right, i << 1);
    else if (left > mid) return queryTree(left, right, i << 1 | 1);
    else return std::max(queryTree(left, mid, i << 1), queryTree(mid + 1, right, i << 1 | 1));
  }
};
SegTree T;

void init() {
  scanf("%d %d", &N, &D);
  for (int i = 1; i < N; ++i) {
    int f;
    scanf("%d", &f);
    Gr.addEdge(f + 1, i + 1);
  }
}

void dfs1(int u) {
  Len[u] = 0;
  for (int i = Gr.head[u]; i; i = Gr.next[i]) {
    int v = Gr.to[i];
    Fa[v] = u;
    dfs1(v);
    if (Len[v] + 1 > Len[u]) {
      Len[u] = Len[v] + 1;
      Wson[u] = v;
    }
  }
}

void dfs2(int u) {
  Dfc++;
  Id[u] = Dfc, Dfn[Dfc] = u;
  if (Wson[u] != 0) dfs2(Wson[u]);
  for (int i = Gr.head[u]; i; i = Gr.next[i]) {
    int v = Gr.to[i];
    if (v == Wson[u]) continue;
    dfs2(v);
  }
}

inline void upt(int u, int v) {
  int n = Len[v] + 1;
  static int a[MaxN + 5], sufmax[MaxN + 5], f[MaxN + 5];
  for (int i = 0; i < n; ++i) a[i + 1] = T.queryTree(Id[v] + i, Id[v] + i);
  sufmax[n] = a[n];
  for (int i = n - 1; i >= 1; --i) sufmax[i] = std::max(sufmax[i + 1], a[i]);
  for (int i = 0; i <= n; ++i) f[i] = 0;
  for (int i = 0; i <= n; ++i) {
    if (i > D - i) break;
    if (D - i > n) continue;
    f[i] = std::max(f[i], T.queryTree(Id[u] + i, Id[u] + i) + sufmax[D - i]);
  }
  for (int i = 1; i <= n; ++i) {
    int val = sufmax[i] + T.queryTree(std::max(Id[u] + i, Id[u] + D - i), Id[u] + Len[u]);
    f[i] = std::max(f[i], val);
  }
  for (int i = 0; i <= n; ++i) T.updateTree(Id[u] + i, f[i]);
}

void dfs3(int u) {
  if (Wson[u] != 0) dfs3(Wson[u]);
  T.updateTree(Id[u], T.queryTree(Id[u] + D, Id[u] + Len[u]) + 1);
  for (int i = Gr.head[u]; i; i = Gr.next[i]) {
    int v = Gr.to[i];
    if (v == Wson[u]) continue;
    dfs3(v);
    upt(u, v);
  }
}

void solve() {
  dfs1(1);
  dfs2(1);
  T.buildTree(1, N);
  dfs3(1);
  printf("%d\n", T.queryTree(Id[1], Id[1] + Len[1]));
}

int main() {
  init();
  solve();
  return 0;
}
```

---

## 作者：Rainbow_qwq (赞：1)

看到 ix35 在 cmd 博客下评论“弦图最大独立集”于是想出了这个做法（（（

这个问题可以转化为每个点向与它 $dis\le k-1$ 的点连边，求最大独立集。

这是一个子树图（连边向一个树上连通块），而子树图的完美消除序列是按照最浅点从深到浅排列的。

于是把所有点按照 $dep$ 从大到小排序直接贪心，能加入就加入。（需要判断 $dis\le k-1$ 的点有没有已经被加入了的，可以拉个点分树板子）。交上去发现这样是对的。

代码就不放了。

---

## 作者：Rusalka (赞：1)

### [BalticOI 2017] Cat in a tree

神仙美少女 Tweetuzki 学姐用了长剖+线段树，私以为长剖可以做到线性。

##### 简要题意

- 给定 $n$ 个点的树，点集 $S$ 合法当且仅当 $\forall u,v\in S, dis(u,v)\ge k$。求 $\max |S|$。

- $n \le 2\times 10^5$。

##### 题解

记 $f_{u,i}$ 表示以 $u$ 为根的子树中，选择的深度最浅的点深度**大于等于** $i$ 的最大点集大小。此处深度针对这一子树而言。转移考虑加入一棵子树，方程比较简单：更新 $f_{u,j}$ 时，记 $t = \max(j,k-j)$（分别保证状态的合法性和答案的合法性），$f_{u,j}\leftarrow \max(f_{u,j}+f_{v,t-1}, f_{u,t}+f_{v,j-1})$，最后做一遍后缀 $\max$ 即可。

注意到当 $j \gt dep_u$ 时，$f_{u,j}=0$。所以转移时只需要枚举到 $dep_v$ 即可。这启发我们使用长剖优化。

##### 代码

注意边界细节。

``` cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 200010;

int n, K;
struct edge{
	int ne, to;
	edge(int N=0,int T=0):ne(N),to(T){}
}e[MAXN<<1];
int fir[MAXN], num = 0;
inline void join(int a, int b)
{
	e[++num] = edge(fir[a], b);
	fir[a] = num;
}
int buf[MAXN], *f[MAXN], *now = buf, dep[MAXN], son[MAXN], fa[MAXN];
void predfs(int u, int pa)
{
	fa[u] = pa;
	for(int i=fir[u],v;i;i=e[i].ne) if((v = e[i].to) != pa)
	{
		predfs(v, u);
		dep[u] = max(dep[u], dep[v]+1);
		if(dep[son[u]] < dep[v]) son[u] = v;
	}
	dep[u] = dep[son[u]] + 1;
}
void dfs(int u)
{
	f[u][0] = 1; 
	if(son[u])
	{
		f[son[u]] = f[u] + 1;
		dfs(son[u]);
		if(K-1 < dep[son[u]]) f[u][0] += f[son[u]][K-1];
		f[u][0] = max(f[u][1], f[u][0]);
	}
	for(int i=fir[u],v;i;i=e[i].ne) if((v=e[i].to) != fa[u] && v != son[u])
	{
		f[v] = now; now += dep[v];
		dfs(v);
		for(int j=0;j<=dep[v];j++)
		{
			int k = max(j, K-j);
			f[u][j] = max(((k) ? (j<dep[u]?f[u][j]:0) + (k<=dep[v]?f[v][k-1]:0) : 0), (j ? (k<dep[u]?f[u][k]:0) + f[v][j-1] : 0));
		}
		for(int j=dep[v];~j;j--) f[u][j] = max(f[u][j], j==dep[u]-1?0:f[u][j+1]);
	}
}

int main()
{
	scanf("%d%d",&n,&K);
	for(int i=2,x;i<=n;i++)
	{
		scanf("%d",&x);
		join(i, ++x);
		join(x, i);
	}
	predfs(1, 0);
	f[1] = now; now += dep[1];
	dfs(1);
	printf("%d\n",f[1][0]);
	return 0;
}
```



---

