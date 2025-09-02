# Maximum Waterfall

## 题目描述

Emuskald was hired to design an artificial waterfall according to the latest trends in landscape architecture. A modern artificial waterfall consists of multiple horizontal panels affixed to a wide flat wall. The water flows down the top of the wall from panel to panel until it reaches the bottom of the wall.

The wall has height $ t $ and has $ n $ panels on the wall. Each panel is a horizontal segment at height $ h_{i} $ which begins at $ l_{i} $ and ends at $ r_{i} $ . The $ i $ -th panel connects the points $ (l_{i},h_{i}) $ and $ (r_{i},h_{i}) $ of the plane. The top of the wall can be considered a panel connecting the points $ (-10^{9},t) $ and $ (10^{9},t) $ . Similarly, the bottom of the wall can be considered a panel connecting the points $ (-10^{9},0) $ and $ (10^{9},0) $ . No two panels share a common point.

Emuskald knows that for the waterfall to be aesthetically pleasing, it can flow from panel $ i $ to panel $ j $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269D/5a41f87b0168f94e6178285e1ee91e69b10580d9.png)) only if the following conditions hold:

1. $ max(l_{i},l_{j})&lt;min(r_{i},r_{j}) $ (horizontal projections of the panels overlap);
2. $ h_{j}&lt;h_{i} $ (panel $ j $ is below panel $ i $ );
3. there is no such panel $ k $ $ (h_{j}&lt;h_{k}&lt;h_{i}) $ that the first two conditions hold for the pairs $ (i,k) $ and $ (k,j) $ .

Then the flow for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269D/5a41f87b0168f94e6178285e1ee91e69b10580d9.png) is equal to $ min(r_{i},r_{j})-max(l_{i},l_{j}) $ , the length of their horizontal projection overlap.

Emuskald has decided that in his waterfall the water will flow in a single path from top to bottom. If water flows to a panel (except the bottom of the wall), the water will fall further to exactly one lower panel. The total amount of water flow in the waterfall is then defined as the minimum horizontal projection overlap between two consecutive panels in the path of the waterfall. Formally:

1. the waterfall consists of a single path of panels ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269D/94bd9e9fe8db4cd80fd47cf8dd35094a595a876f.png);
2. the flow of the waterfall is the minimum flow in the path ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269D/94bd9e9fe8db4cd80fd47cf8dd35094a595a876f.png).

 To make a truly great waterfall Emuskald must maximize this water flow, but there are too many panels and he is having a hard time planning his creation. Below is an example of a waterfall Emuskald wants:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF269D/772bd38da020894115b05646ae3719e2b6fc3c60.png)Help Emuskald maintain his reputation and find the value of the maximum possible water flow.

## 说明/提示

The first test case corresponds to the picture.

## 样例 #1

### 输入

```
5 6
4 1 6
3 2 7
5 9 11
3 10 15
1 13 16
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 5
4 2 8
3 1 2
2 2 3
2 6 12
1 0 7
1 8 11
```

### 输出

```
2
```

# 题解

## 作者：command_block (赞：8)

**题意** : 给出若干条水平线段，形如 $(l_i,h_i)\leftrightarrow(r_i,h_i)$。

此外，还有两条无限延伸的线段，一条在 $y=0$ ，另一条在 $y=\infty$。

若两条线段 $i,j$ 满足如下条件，则在图中连接有向边 $i\rightarrow j$ 。

- $[l_i,r_i)∩[l_j,r_j)\neq \varnothing$ ，即两者的投影有交。

- $h_i>h_j$

- 不存在 $k$ 使得有序二元组 $(i,k)$ 与 $(k,j)$ 满足上述条件。

边权为 ${\rm len}\big([l_i,r_i)∩[l_j,r_j)\big)=\min(r_i,r_j)-\max(l_i,l_j)$。

问从 $y=\infty$ 到 $y=0$ 的最小瓶颈路，即最小边权最大的路径。输出这个最小边权。

保证各个线段没有交点。

$n\leq 10^5$ ，时限$\texttt{2s}$。

------------

5min 胡出来，太感动了……

首先不难发现该图是个 DAG ，于是在 DAG 上进行 DP 求最小瓶颈路，复杂度即为 $O(n^2)$。

考虑数据结构优化。

将所有线段按照 $h$ 从低到高排序，逐个进行转移。（这捕捉了该 DAG 的一种拓扑序）

对于每个线段，其**可能的**转移前驱为 ： 下方所有线段的上包络线中，在自己投影中的部分。

如图 ，蓝色描边为可能转移的线段 ：

![](https://cdn.luogu.com.cn/upload/image_hosting/pqz3l7k1.png)

不难发现，此后这些蓝色部分就被新加入的线段覆盖了。维护上包络线等价于 ODT ，所以有结论 ： 每次转移涉及到的候选线段的条数和是 $O(n)$ 的。

在按顺序取出各个候选线段后，再用条件 ③ 除去不合法的线段。

利用上包络线的性质不难证明，每个候选线段只需要检查左右两个线段是否会导致自己不合法。

转移时暴力即可。

ODT 可以使用线段树或平衡树实现。

复杂度 $O(n\log n)$。

```cpp
#include<algorithm>
#include<cstdio>
#include<set>
#define MaxN 105000
using namespace std;
const int INF=1000000001;
struct Data{int l,r,h;}b[MaxN];
bool cmp(const Data &A,const Data &B)
{return A.h<B.h;}
struct Seg{
  int l,p;
  bool operator < (const Seg &B) const
  {return l<B.l;}
}st[MaxN<<1];
set<Seg> s;
int dp[MaxN];
bool chk(int u,int v)
{return b[u].h>b[v].h&&min(b[u].r,b[v].r)>max(b[u].l,b[v].l);}
void solve(int l,int r,int p)
{
  set<Seg>::iterator it=s.upper_bound((Seg){l,0});
  it--;
  int tn=0;
  for (;it!=s.end()&&it->l<r;it++)st[++tn]=*it;
  if (it!=s.end()&&it->l>r)s.insert((Seg){r,st[tn].p});
  for (int i=st[1].l<l ? 2: 1;i<=tn;i++)s.erase(st[i]);
  int top=0;
  for (int i=1;i<=tn;i++){
    int u=st[i].p;
    if (i>1&&chk(st[i-1].p,st[i].p))continue;
    if (i<tn&&chk(st[i+1].p,st[i].p))continue;
    dp[p]=max(dp[p],min(min(r,b[st[i].p].r)-max(l,b[st[i].p].l),dp[st[i].p]));
  }s.insert((Seg){l,p});
}
int n;
int main()
{
  scanf("%d%*d",&n);
  for (int i=1;i<=n;i++)
    scanf("%d%d%d",&b[i].h,&b[i].l,&b[i].r);
  b[++n]=(Data){-INF,INF,INF};
  sort(b+1,b+n+1,cmp);
  b[0]=(Data){-INF,INF,0};
  s.insert((Seg){-INF,0});
  s.insert((Seg){INF,-1});
  dp[0]=INF<<1;
  for (int i=1;i<=n;i++)
    solve(b[i].l,b[i].r,i);
  printf("%d",dp[n]);
  return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

这是黑题？蓝题封顶。

很显然，我们只需要求出每个隔板能到其他哪些隔板即可。

由于没有隔板重叠，所以我们可以考虑目前每个位置能流到哪个挡板。

方便起见，我们把 $[x,x+1]$ 这条线段成为线段 $x$，因此我们覆盖的位置 $[l,r]$ 实际上看做是线段 $[l,r-1]$。这样会让判断重叠容易的多。

每次我们加入一条线段 $[l,r-1]$。那么所有和 $[l,r-1]$ 有交的线段看起来都是能到的。因此类似珂朵莉树的方法把被 $[l,r-1]$ 包含的区间删掉，部分重叠的线段砍去重叠的部分。这样建图之后就可以在 DAG 上进行动态规划了。

然而这是错的。考虑类似的的图形：

```
   -----------    
-------    ----------
   -----------
```

最下面这个隔板是不可以被最上方的隔板流到的。而产生这种情况是因为最下面这个图形被部分覆盖了。所以，右边被部分覆盖的线段必须是当前查询线段的最右边，左边被覆盖的线段必须是当前查询线段的最左边，都覆盖必须是唯一的那个。再开两个记录一下 bool 即可。

代码：[code](https://codeforces.com/problemset/submission/269/212808267)

---

## 作者：红黑树 (赞：0)

[可能更好的阅读体验](https://rbtr.ee/CF269D)

## [题目](https://codeforces.com/contest/269/problem/D)

## 题解
能流水的板子的个数为 $\mathcal O\left(n\right)$ 个，原因是能流水板子要么包含上一个板子，要么被上一个板子包含，要么有交但不包含。

如果包含或被包含那就只会有一个板子能流水。

而最多只会有两个 有交但不包含 的板子。

![](https://rbtr.ee/usr/uploads/2024/05/3193140782.svg)

因此只要能快速找到这些能流水的板子，然后 DP 一下即可。

这里我用了一个很笨的办法。

离散化啥的不用多说。

按高度从大到小扫所有的板子，用线段树维护区间颜色是否唯一，在线段树上二分，找到每个颜色段，然后记录。这里的颜色就表示线段的 id。

复杂度 $\mathcal O\left(n \log n\right)$。

## 代码
```cpp
// :/

struct bar {
  tp d, t;
  
  bar() = default;
  bar(tp d, tp t) : d(d), t(t) {}
};

tp op(tp l, tp r) {
  if (l == -2 || r == -2) return l + r + 2;
  if (l == r) return l;
  return -1;
}

tp e() { return -2; }

tp mapping(bar t, tp x) {
  if (t.t != -1) return t.d;
  return x;
}

bar composition(bar x, bar y) {
  if (x.t == -1) return y;
  if (y.t == -1) return x;
  if (x.t < y.t) return x;
  return y;
}

bar id() { return bar(-1, -1); }

struct foo {
  tp h, l, r;
  
  bool operator<(const foo& comp) const {
    return h > comp.h;
  }
};

signed STRUGGLING([[maybe_unused]] unsigned long TEST_NUMBER) {
  tp n, t; bin >> n >> t;
  vector<foo> a(n + 2);
  for (tp i = 1; i <= n; ++i) bin >> a[i].h >> a[i].l >> a[i].r;
  a[0].h = INF; a[0].l = -INF; a[0].r = INF;
  ++n;
  a[n] = a[0]; a[n].h = 0;
  auto dc = a;
  [&] {
    vector<tp> bar;
    for (tp i = 0; i <= n; ++i) {
      bar.push_back(a[i].l);
      bar.push_back(a[i].r);
    }
    auto baz = lib::Discretization(bar);
    for (tp i = 0; i <= n; ++i) {
      dc[i].l = baz[i * 2].first;
      dc[i].r = baz[i * 2 + 1].first;
    }
  }();
  vector<set<tp>> rem(n + 1);
  lib::Segtree<tp, op, e, bar, mapping, composition, id> o(2 * n + 2);
  map<tp, vector<tp>, greater<tp>> baz;
  for (tp i = 0; i <= n; ++i) baz[a[i].h].push_back(i);
  for (auto& qux : baz) {
    for (auto& i : qux.second) {
      tp l = dc[i].l, r = dc[i].r;
      tp now = l;
      bg(l, r, o.prod(l, r));
      while (o.prod(now, r) == -1) {
        tp bar = o.max_right(now, [](tp x) { return x != -1; });
        tp t = o.get(bar - 1);
        if (min(a[t].r - a[i].l, a[i].r - a[t].l) > 0) {
          tp a = max(dc[t].l, dc[i].l) + 1, b = min(dc[t].r, dc[i].r) - 1;
          if (a > b || o.prod(a, b) == t) rem[i].insert(t);
        }
        now = bar;
      }
      tp t = o.prod(now, r);
      if (min(a[t].r - a[i].l, a[i].r - a[t].l) > 0) {
        tp a = max(dc[t].l, dc[i].l) + 1, b = min(dc[t].r, dc[i].r) - 1;
        if (a > b || o.prod(a, b) == t) rem[i].insert(t);
      }
    }
    for (auto& i : qux.second) {
      tp l = dc[i].l, r = dc[i].r;
      o.apply(l, r, bar(i, a[i].h));
      bg(l, r, i, "WRITE");
    }
  }
  vector<tp> f(n + 1);
  f[0] = INF;
  rem.back().erase(0);
  auto bar = rem;
  for (auto& qux : baz) {
    if (qux.first == INF) continue;
    for (auto& i : qux.second) {
      auto t = rem[i];
      for (auto& j : t) {
        if (a[j].l <= a[i].l && a[i].r <= a[j].r) f[i] = max(f[i], min(f[j], a[i].r - a[i].l));
        else if (a[i].l <= a[j].l && a[j].r <= a[i].r) f[i] = max(f[i], min(f[j], a[j].r - a[j].l));
        else f[i] = max(f[i], min(f[j], min(a[i].r - a[j].l, a[j].r - a[i].l)));
      }
    }
  }
  for (tp i = 0; i <= n; ++i) bg(i, f[i]);
  bin << f[baz.rbegin()->second.front()] << '\n';
  return 0;
}

void MIST() {
}

// :\ *//
```

---

## 作者：Drind (赞：0)

### 题目解析

这题要让我们找一条流量最大的瀑布。

我们发现可以用动态规划解决这个问题，对于每个横板，我们找到它能流的所有板子，然后更新答案即可，我们发现这就是一个颜色段均摊的问题，所以可以用 ODT 维护，总的更新次数和 ODT 的复杂度一样，是线性的。

我们从上往下把横板一个个覆盖，对于每次覆盖的区间，我们取出这个区间内所有颜色段，然后一个个更新即可。但是我们少判断一个条件就是更新前后两个横板中间不能有第三者承上启下。 

我们考虑两个原本能流的横板中间出现了第三者，那么这个第三者肯定插入到原来两个横板的交之间了，所以在 ODT 上一定覆盖了原先上层的隔板，也就是对于上层的隔板，去找谁覆盖了它就行，也就是在它旁边的两个颜色段，单次判断 $O(1)$ 不影响复杂度。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
const int inf=1e9;

struct node{
	int h,l,r;
}a[N];

struct data{
	int l,r;
	mutable int v;
	inline bool operator <(const data &x) const{
		return l<x.l;
	}
}d[N];

struct ODT{
	set<data>S;
	int n;
	inline auto split(int pos){
		if(pos>n) return S.end();
		auto it= --S.upper_bound({pos,0,0});
		if(it->l==pos) return it;
		int l=it->l; int r=it->r; int v=it->v;
		S.erase(it); S.insert({l,pos-1,v});
		return S.insert({pos,r,v}).first;
	}
	inline void assign(int l,int r,int v){
		auto itr=split(r+1),itl=split(l);
		S.erase(itl,itr); S.insert({l,r,v});
	}
};

int dp[N];

inline bool check(int x,int y){
	return a[x].h<a[y].h&&(min(a[x].r,a[y].r)-max(a[x].l,a[y].l)>=0);
}

inline void fake_main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].h>>a[i].l>>a[i].r;
		a[i].r--;//把点转换成线段的覆盖关系
	}
	sort(a+1,a+n+1,[](node x,node y){
		return x.h>y.h;
	});
	
	ODT tr; tr.S.insert({-inf,inf,0}); tr.n=inf;
	a[0]={m,-inf,inf}; a[n+1]={0,-inf,inf};
	dp[0]=inf*2;
	for(int i=1;i<=n+1;i++){
		auto itr=tr.split(a[i].r+1);
		auto itl=tr.split(a[i].l);
		int cnt=0;
		for(;itl!=itr;++itl) d[++cnt]=*itl;//找当前转移区间中的每个颜色段
		for(int j=1;j<=cnt;j++){
			if(j!=1&&check(d[j-1].v,d[j].v)) continue;
			if(j!=cnt&&check(d[j+1].v,d[j].v)) continue;
			int w=min(d[j].r,a[i].r)-max(d[j].l,a[i].l)+1;
			dp[i]=max(dp[i],min(dp[d[j].v],w));
		}
		tr.assign(a[i].l,a[i].r,i);
	}
	cout<<dp[n+1]<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：BotYoung (赞：0)

前置知识：**颜色段均摊**，**简单 DP**
## 题意
在一个值域为 $[-10^9,10^9]$ 的二维平面坐标系上有 $n$ 条平行于 $x$ 轴且互不相交的线段。瀑布从直线 $y=t$ 开始，令当前线段为 $j$，每次可以选择满足如下要求的线段 $i$ 下落：

- $h_i<h_j$

- $\max(l_i,l_j)<\min(r_i,r_j)$

- $\nexists k$，$(j,k)$ 和 $(k,i)$ 都满足条件

瀑布下落路径的价值定义为路径上所有相邻线段的长度交的最小值，求可能的路径最大价值。
## 思路
由于最终路径的高度单调递减，所以瀑布在线段之间的转移可以看作一个 DAG（有向无环图）。把线段看作图上的节点。对于每一条线段，向所有满足要求的下一层线段连边，并令边权为两条线段的长度交。最后按拓扑序跑一个 DP 即可。
### Q1：有向图的大小及建图实现？
我们可以先大胆猜想 ~~（因为蒟蒻我没直接想出来）~~，最终 DAG 的边数是与 $n$ 同阶的。

首先一定是将线段按照高度从高至低排序，因为高度更低的线段会挡住其上方的所有线段。

考虑向图中依次加入排序后的线段，显然这个过程就是一个颜色段均摊。由于题目保证线段之间互不相交，所以对于已经被覆盖过的位置，原本覆盖它的线段的高度一定高于当前需要加入的线段。根据这个性质，我们只需要把每个位置染成最后一次覆盖它的对应线段的下标，那么一个位置在覆盖前对应的线段就**有可能**向当前线段连边。

到这里就能够证明我们猜测的结论了。加边的次数等价于一个区间被重复覆盖的次数，根据颜色段均摊的结论，这个值是与线段数量同阶的，即有向图的边数是与 $n$ 同阶的。

具体实现的话，只要对排序后的线段依次先连边后覆盖就可以了。
### Q2：如何判断两条线段是否相邻？
接上文，为什么不能直接从一个点原本对应的线段向当前线段连边呢？

这个问题比较好想。根据题目条件，两条线段之间能够连边，当且仅当两条线段存在交集且**两条线段之间没有其它线段**。

所以我们现在只解决了判断线段交集的问题，而没有考虑到，可能存在两条线段之间的另一条线段，这一条线段已经对两条线段中的较高一条进行了覆盖，那么这两条线段之间不能存在转移。

处理的方法也并不难想。进行区间修改操作时，我们需要知道原区间上不同的颜色段。考虑将这些颜色段单独拿出来处理，结合前面的结论，你会发现：对于一个颜色段，能够对它进行覆盖的“另一条线段”，一定是当前区间中与它相邻的颜色段。

所以对于每一个颜色段，先判断它两边的颜色段对应的原线段是否覆盖了它对应的原线段。如果没有，我们才能把它与当前新加入的节点连边。

不难发现排序后的加边顺序就是 DAG 的拓扑序，加完边后直接进行 DP 转移即可，用 set 实现 ODT，时间复杂度为 $O(n\log\log n)$。

喜闻乐见：
```cpp
#include <bits/stdc++.h>
#define reg register
#define rep(i, l, r) for (reg int i = l; i <= r; i++)
#define per(i, r, l) for (reg int i = r; i >= l; i--)
using namespace std;
typedef long long ll;
typedef unsigned long long llu;
namespace io {
inline ll read(){
    reg ll s = 0, f = 1;
    reg char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') s = (s << 1) + (s << 3) + (ch ^ '0'), ch = getchar(); 
    return s * f;
}
inline void write(reg ll x){
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10); putchar(x % 10 ^ '0');
}
inline void write(reg ll x, reg char c){
    write(x), putchar(c);
}
}//namespace io
using namespace io;
const int N = 2e5 + 5, inf = 1e9;
struct stair{
    int h, l, r;
    inline bool operator <(const stair &t) const{
        return h > t.h;
    }
}a[N];
struct edge{
    int v, w;
};
int n, m, h, l, r, s, t;
int in[N], topo[N], dp[N];
vector<edge> G[N];
struct node{
    int l, r;
    mutable int v;
    inline bool operator <(const node &x) const{
        return l < x.l;
    }
}b[N];
struct ODT{
    set<node> S;
    int n;
    inline auto split(int x){
        if (x > n) return S.end();
        auto it = --S.upper_bound({x, 0, 0});
        if (it->l == x) return it;
        int l = it->l, r = it->r, v = it->v;
        S.erase(it); S.insert({l, x - 1, v});
        return S.insert({x, r, v}).first;
    }
    inline void assign(int l, int r, int v){
        auto itr = split(r + 1), itl = split(l);
        S.erase(itl, itr); S.insert({l, r, v});
    }
};
inline bool check(int x, int y){
    return a[x].h < a[y].h && min(a[x].r, a[y].r) >= max(a[x].l, a[y].l);
}
int main(){
    n = read(), m = read();
    ODT T; T.S.insert({-inf, inf, s}); T.n = inf;
    rep(i, 1, n) a[i].h = read(), a[i].l = read(), a[i].r = read() - 1;
    sort(a + 1, a + n + 1);
    a[0] = {m, -inf, inf}, a[n + 1] = {0, -inf, inf};
    dp[0] = inf << 1;
    rep(i, 1, n + 1){
        auto itr = T.split(a[i].r + 1), itl = T.split(a[i].l);
        int cnt = 0;
        for (; itl != itr; ++itl) b[++cnt] = *itl;
        rep(j, 1, cnt){
            if (j != 1 && check(b[j - 1].v, b[j].v)) continue;
            if (j != cnt && check(b[j + 1].v, b[j].v)) continue;
            int w = min(b[j].r, a[i].r) - max(b[j].l, a[i].l) + 1;
            dp[i] = max(dp[i], min(dp[b[j].v], w));
        }
        T.assign(a[i].l, a[i].r, i);
    }
    write(dp[n + 1]);
    return 0;
}
```

---

## 作者：abensyl (赞：0)

原题：[CF269D Maximum Waterfall](https://www.luogu.com.cn/problem/CF269D)。

## 思路

因为每个木板只能往在它下方，水平方向有交的，最高的木板上流，所以显然，所有可能的转移是一个 DAG 结构。

那么也就说明了，转移的次数是线性的，我们只需要考虑求出 DAG 中所有的边就可以了。

求出 DAG 中的所有边，就是求每个木板下方最高的与之有交的木板。

考虑将所有木板的左右端点从左向右排序，遇到左端点就加入 set，遇到右端点就从 set 中删除，每个木板下方最近有交的木板就是 set 中对应高度最大木板的编号。

注意，如果一个木板上方没有符合条件的木板，就作为源点，下方没有符合条件可转移的模板，就视为汇点。

计算答案，从源点开始按照 DAG 进行转移即可，答案就是每个汇点答案的最大值。

---

