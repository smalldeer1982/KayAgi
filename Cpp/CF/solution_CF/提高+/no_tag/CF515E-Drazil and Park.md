# Drazil and Park

## 题目描述

Drazil is a monkey. He lives in a circular park. There are $ n $ trees around the park. The distance between the $ i $ -th tree and ( $ i+1 $ )-st trees is $ d_{i} $ , the distance between the $ n $ -th tree and the first tree is $ d_{n} $ . The height of the $ i $ -th tree is $ h_{i} $ .

Drazil starts each day with the morning run. The morning run consists of the following steps:

- Drazil chooses two different trees
- He starts with climbing up the first tree
- Then he climbs down the first tree, runs around the park (in one of two possible directions) to the second tree, and climbs on it
- Then he finally climbs down the second tree.

But there are always children playing around some consecutive trees. Drazil can't stand children, so he can't choose the trees close to children. He even can't stay close to those trees.

If the two trees Drazil chooses are $ x $ -th and $ y $ -th, we can estimate the energy the morning run takes to him as $ 2(h_{x}+h_{y})+dist(x,y) $ . Since there are children on exactly one of two arcs connecting $ x $ and $ y $ , the distance $ dist(x,y) $ between trees $ x $ and $ y $ is uniquely defined.

Now, you know that on the $ i $ -th day children play between $ a_{i} $ -th tree and $ b_{i} $ -th tree. More formally, if $ a_{i}<=b_{i} $ , children play around the trees with indices from range $ [a_{i},b_{i}] $ , otherwise they play around the trees with indices from ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515E/d3b74f54842bc3f076dfae535193a349f2e5a3fa.png).

Please help Drazil to determine which two trees he should choose in order to consume the most energy (since he wants to become fit and cool-looking monkey) and report the resulting amount of energy for each day.

## 样例 #1

### 输入

```
5 3
2 2 2 2 2
3 5 2 1 4
1 3
2 2
4 5
```

### 输出

```
12
16
18
```

## 样例 #2

### 输入

```
3 3
5 1 4
5 1 4
3 3
2 2
1 1
```

### 输出

```
17
22
11
```

# 题解

## 作者：Tony102 (赞：17)

[更好的阅读体验](https://tony102.xyz/index.php/2020/11/10/cf515e-drazil-and-park/)

[Link](https://www.luogu.com.cn/problem/CF515E)

### Description

给定 $n$ 个点 $i$ 到点 $i+1$ 的距离 $d[i]$，每个点有一个权值 $h[i]$。现在有 $m$ 组询问，每次询问 $[l,r]$ 内两点 $x, y$， 使得$2\times(h_x + h_y) + dis(x,y)$ 最大。其中 $dis(x,y)$ 表示 $x$ 到 $y$ 的距离。



### Sol

**墙裂推荐的好题**

首先它给你的个点之间的距离是个环状的，你要断环成链。

接下来你要考虑如何将 $2\times(h_x + h_y) + dis(x,y)$ 最大化。先考虑将 $2\times(h_x + h_y) $ 和 $dis(x,y)$ 分别最大化。

显然将他们两个分别最大化的情况下，最大化的结果的 $x,y$ 坐标很有可能不是同一对。

**假如两个最大值你不好同时查，就换成把最大化一个东西，再最小化另外一个并把加法做成减法**

绝活。

考虑 $dis(x, y)$ 怎么计算，设 $sum[]$ 是 $d[]$ 的前缀和，那么 $dis(x,y) = sum[y] - sum[x]$ 

这个时候我们就是要让 $sum_y - sum_x + 2 \times h_x + 2 \times h_y$ 最大

套路：把跟同一个东西相关的东西一起处理

现在变成了：$sum_y + 2 \times h_y - sum_x + 2 \times h_x$ 最大。那就让 $sum_y + 2 \times h_y$ 最大，$sum_x - 2 \times h_x$ 最小

因为没有修改操作，RMQ问题就可以用ST表，也可以用线段树之类的。

但是考虑一个问题，这样子做有可能查到的这两个的最大最小的位置是同一个位置，这样不符合要求。所以当我们查到了两个相同的位置的时候，就在 $[l, pos - 1] $ 和 $[pos + 1, r]$ 中查一下最大最小的位置就可以了。其中 $pos$ 是第一查到的最大最小位置。

同时注意到刚才我们要查的是位置，所以维护RMQ信息的时候要维护的是 RMQ 的下标。



### Code

我实现用的线段树，比较好懂。用魔力`ae86`快读以后吊打 ST 表做法。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int SIZE = 2e5 + 5;
const int inf = 1e18;

int n, m;
int d[SIZE], h[SIZE], sumMin[SIZE], sumMax[SIZE];

struct node {
	int l, r, maxx, minn;
} tree[SIZE << 2];

namespace ae86 {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c)) a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::read;

inline int getMax(int x, int y)
{
	return sumMax[x] > sumMax[y] ? x : y;
}

inline int getMin(int x, int y)
{
	return sumMin[x] < sumMin[y] ? x : y;
}

#define lson(p) p << 1
#define rson(p) p << 1 | 1

inline void pushUp(int p)
{
	tree[p].maxx = getMax(tree[lson(p)].maxx, tree[rson(p)].maxx);
	tree[p].minn = getMin(tree[lson(p)].minn, tree[rson(p)].minn);
}

inline void build(int p, int l, int r)
{
	tree[p].l = l, tree[p].r = r;
	if (l == r) {
		tree[p].maxx = tree[p].minn = l;
		return;
	}
	int mid = (l + r) >> 1;
	build(lson(p), l, mid); build(rson(p), mid + 1, r);
	pushUp(p);
}

inline int queryMax(int p, int l, int r)
{
	if (l <= tree[p].l && tree[p].r <= r) {
		return tree[p].maxx;
	}
	int mid = (tree[p].l + tree[p].r) >> 1, ans = 0;
	if (l <= mid) ans = queryMax(lson(p), l, r);
	if (r > mid) ans = getMax(queryMax(rson(p), l, r), ans);
	return ans;
}

inline int queryMin(int p, int l, int r)
{
	if (l <= tree[p].l && tree[p].r <= r) {
		return tree[p].minn;
	}
	int mid = (tree[p].l + tree[p].r) >> 1, ans = 0;
	if (l <= mid) ans = queryMin(lson(p), l, r);
	if (r > mid) ans = getMin(queryMin(rson(p), l, r), ans);
	return ans;
}

inline int calcMin(int l, int r)
{
	if (l > r) return 0;
	return queryMin(1, l, r);
}

inline int calcMax(int l, int r)
{
	if (l > r) return 0;
	return queryMax(1, l, r);
}

inline int solve(int l, int r)
{
	int minn = calcMin(l, r), maxx = calcMax(l, r);
	if (minn != maxx) return sumMax[maxx] - sumMin[minn];
	int minn2 = getMin(calcMin(l, minn - 1), calcMin(minn + 1, r));
	int maxx2 = getMax(calcMax(l, maxx - 1), calcMax(maxx + 1, r));
	return std::max(sumMax[maxx2] - sumMin[minn], sumMax[maxx] - sumMin[minn2]);
}

signed main()
{
	// freopen("code.in", "r", stdin);
	// freopen("code.out", "w", stdout);
	n = read(), m = read();
	for (register int i = 1; i <= n; ++ i) {
		d[i % n + 1] = d[i % n + 1 + n] = read();
	}
	for (register int i = 1; i <= n; ++ i) {
		h[i] = h[i + n] = read();
	}	
	int sum = 0; sumMax[0] = -inf, sumMin[0] = inf;
	for (register int i = 1; i <= (n << 1); ++ i) {
		sum += d[i];
		sumMax[i] = sum + 2 * h[i];
		sumMin[i] = sum - 2 * h[i];
	}
	build(1, 1, 2 * n + 1);
	while (m --) {
		int l = read(), r = read();
		if (l <= r) printf("%lld\n", solve(r + 1, n + l - 1));
		else printf("%lld\n", solve(r + 1, l - 1));
	}
	return 0;
}
```



l

---

## 作者：Mobius127 (赞：8)

感觉没有黑难度？

[题目传送门](https://www.luogu.com.cn/problem/CF515E)

首先考虑 $dist(x,\ y)$，如果我们每次询问都去查询这个值，是很困难的，我们考虑用坐标换距离，即记 $sum_x=\sum_{i=1}^{x}$，这样 $dist(x,\ y)$ 就变成了 $sum_{y-1}-sum_{x-1}$，这时我们再回头看原式 。

$$2(h_x+h_y)+sum_{y-1}-sum_{x-1}=(2h_y+sum_{y-1})+(2h_x-sum_{x-1})$$

我们现在要做的就是让这个柿子取到最大值，由于两个括号之间互无关联，所以我们只要将两个部分分别最大化即可，而本题的 $h$ 与 $sum$ 都是给出的，这就变成了：查询一个区间的最大值（即 $RMQ$ ）问题。

**窝会！！1这事线段树裸题。**

一个细节：取最大值时可能会取到同一个点上，我们只需稍稍修改 $pushup$ 函数即可。（这里窝用重载运算符实现）

```cpp
struct node{
	ll mx, mn, ans;
	//mx=2*h[l]+sum[l-1]
	//mn=2*h[l]-sum[l-1]
	void clear(){mx=mn=ans=-INF;return ;}
	//初始化 
}st;
node operator + (node a, node b){
	#define max(x, y) (x>y?x:y)
	#define min(x, y) (x<y?x:y)
	node c;
	c.mx=max(a.mx, b.mx), c.mn=max(a.mn, b.mn);
	c.ans=max(a.mn+b.mx, max(a.ans, b.ans));
	return c;
}
```

既然会重叠，我们只需多开一个辅助空间，分三种情况考虑（两个点都在左/右儿子区间或一个点在左另一点在右）

然后还有一个事情要考虑：环状的怎么办？

很简单，断环为链即可。

至此，本题得到完美解决。

### Code

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#define gc() getchar()
#define N 200005
using namespace std;
typedef long long ll;
const ll INF=0x3f3f3f3f3f3f3f3f;
inline ll read(){
	char ch=gc();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=gc();}
	return x*f;
}
int n, m;
ll sum[N], h[N], a[N];
struct node{
	ll mx, mn, ans;
	//mx=2*h[l]+sum[l-1]
	//mn=2*h[l]-sum[l-1]
	void clear(){mx=mn=ans=-INF;return ;}
	//初始化 
}st;
node operator + (node a, node b){
	#define max(x, y) (x>y?x:y)
	#define min(x, y) (x<y?x:y)
	node c;
	c.mx=max(a.mx, b.mx), c.mn=max(a.mn, b.mn);
	c.ans=max(a.mn+b.mx, max(a.ans, b.ans));
	return c;
}
struct Segment_Tree{
	#define ls k<<1
	#define rs k<<1|1
	#define mid (l+r>>1)
	node data[N*4];
	void build(int k, int l, int r){
		if(l==r){
			data[k].clear();
			data[k].mx=sum[l-1]+2*h[l], data[k].mn=-sum[l-1]+2*h[l];
			return ;
		}
		build(ls, l, mid);build(rs, mid+1, r);
		data[k]=data[ls]+data[rs];
	}
	node query(int k, int l, int r, int x, int y){
		if(x<=l&&r<=y) return data[k];
		node ret;ret.clear();
		if(x<=mid) ret=ret+query(ls, l, mid, x, y);
		if(mid<y) ret=ret+query(rs, mid+1, r, x, y);
		return ret;
	}
}chtholly;
ll solve(int a, int b){
	if(a<=b) return chtholly.query(1, 1, n, b+1, a+n/2-1).ans;
	else return chtholly.query(1, 1, n, b+1, a-1).ans;
}
signed main(){
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; i++) a[i]=a[i+n]=read();
	for(int i=1; i<=n; i++) h[i]=h[i+n]=read();n*=2;
	for(int i=1; i<=n; i++) sum[i]=a[i]+sum[i-1];
	chtholly.build(1, 1, n);
	for(int i=1; i<=m; i++){
		int a=read(), b=read();
		printf("%lld\n", solve(a, b));
	}
	return 0;
}
```

---

## 作者：輕山柒海 (赞：6)

# 考虑线段树

先按照题目意思画出第一个样例的草图：

$$
4{\overbrace{--}^{2}}\underbrace{5{\overbrace{--}^{2}}2{\overbrace{--}^{2}}1{\overbrace{--}^{2}}4}{\overbrace{--}^{2}}
$$


### 线段树节点的区间表示

如草图所示，下大括号表示的一段区间包含四棵树，三段路，形式上，一段区间要恰好包含 $x$ 棵树，$x-1$ 段路。

---

### 线段树节点维护的值

* $mx$ 表示 $2*h(x)+dist(x,y)+2*h(y)$ 的最大值，其中树 $x$，$y$ 属于这个节点表示的区间。

* $lmx$ 表示 $dist(x,y)+2*h(y)$ 的最大值，其中树 $x$ 为这个区间最左段的树，树 $y$ 属于这个区间。

* $rmx$ 表示 $dist(x,y)+2*h(x)$ 的最大值，其中树 $y$ 为这个区间最右端的树，树 $x$ 属于这个区间。

* $sum$ 表示这个区间里所有的路的长度之和。



看一下草图括的这个区间对应的值为：
* $mx$：$x$ 选第 $2$ 个树，$y$ 选第 $5$ 个树，即为$2\times5+6+2\times4=24$
* $lmx$：$y$ 选第 $5$ 个树，即为 $6+2\times4=14$
* $rmx$：$x$ 选第 $2$ 个树，即为 $2\times5+6=16$
* $sum$：即为 $2+2+2=6$

---

### 合并区间

对照第一个样例再画一个草图：

$$
4{\overbrace{--}^{2}}\underbrace{\underbrace{5{\overbrace{--}^{2}}2}_{L}\underbrace{{\overbrace{--}^{2}}}_{gap}\underbrace{1{\overbrace{--}^{2}}4}_{R}}_{res}{\overbrace{--}^{2}}
$$

通过已知的 $L$ 区间和 $R$ 区间，外加一段间隔的路的长度 $gap$，合并成为新的 $res$ 区间。

* $res$ 区间的 $mx$ 会是 $L$ 区间的 $mx$ 或者 $R$ 区间的 $mx$，还有一种可能就是 $L$ 和 $R$ 合并所产生的 $mx$，即为 $L$ 区间的 $rmx+R$ 区间的 $lmx+gap$。
* $res$ 区间的 $lmx$ 会是原本的 $L$区间的 $lmx$，还有一种可能就是合并所产生的新值，即为 $L$ 区间的 $sum+R$ 区间的 $lmx$。
* $res$ 区间的 $rmx$ 同上。
* $res$ 区间的 $sum$ 即为 $L$ 区间的 $sum+R$ 区间的 $sum+gap$。

---

### 处理环

先画一个草图：（为了方便观察数字的含义换成了下标）

$$
\underbrace{1}_{R}{--}\overbrace{2{--}3}^{play}{--}\underbrace{4{--}5}_{L}\underbrace{{--}}_{gap}
$$

如图，孩子们在 $[2,3]$ 这个区间玩耍，这样合并 $L$ 和 $R$ 区间就可以了。

另一种情况：

$$
\overbrace{1{--}2}^{play}{--}\underbrace{3{--}4}_{res}{--}\overbrace{5{--}}^{play}
$$

很明显了，孩子们在 $[5,1]$ 这个区间玩耍，直接询问 $[3,4]$ 就可以了。

# 参考代码
~~~cpp
#include<bits/stdc++.h>
#define int long long
struct Data {
	int mx, lmx, rmx, sum;
	Data() {
		mx = lmx = rmx = sum = 0;
	}
};
struct SegmentTree {
#define ls rt << 1
#define rs rt << 1 | 1
	std::vector<int> b, h;
	std::vector<Data> s;
	SegmentTree(int n) :
		b(n + 1), h(n + 1), s(n << 2)
	{}
	Data pushup(Data L, Data R, int gap) {
		Data res;
		res.mx = std::max({ L.mx, R.mx, L.rmx + R.lmx + gap });
		res.lmx = std::max({ L.lmx, L.sum + gap + R.lmx });
		res.rmx = std::max({ R.rmx, R.sum + gap + L.rmx });
		res.sum = L.sum + gap + R.sum;
		return res;
	}
	void build(int rt, int L, int R) {
		if (L == R) {
			s[rt].lmx = s[rt].rmx = 2 * h[L];
			s[rt].mx = 0;
			s[rt].sum = 0;
			return;
		}
		int mid = (L + R) >> 1;
		build(ls, L, mid);
		build(rs, mid + 1, R);
		s[rt] = pushup(s[ls], s[rs], b[mid]);
		return;
	}
	Data query(int rt, int L, int R, int l, int r) {
		if (l <= L && R <= r) return s[rt];
		int mid = (L + R) >> 1;
		Data tmp1, tmp2; bool ok1 = 0, ok2 = 0;
		if (l <= mid) tmp1 = query(ls, L, mid, l, r), ok1 = 1;
		if (r > mid) tmp2 = query(rs, mid + 1, R, l, r), ok2 = 1;
		if (ok1 && !ok2) return tmp1;
		if (!ok1 && ok2) return tmp2;
		return pushup(tmp1, tmp2, b[mid]);
	}
#undef ls
#undef rs
};
signed main() {
	int n, m;
	scanf("%lld%lld", &n, &m);
	SegmentTree segt(n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &segt.b[i]);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &segt.h[i]);
	}
	segt.build(1, 1, n);
	for (int i = 1, l, r; i <= m; i++) {
		scanf("%lld%lld", &l, &r);
		if (l <= r) {
			if (r == n) printf("%lld\n", segt.query(1, 1, n, 1, l - 1).mx);
			else if (l == 1) printf("%lld\n", segt.query(1, 1, n, r + 1, n).mx);
			else printf("%lld\n", segt.pushup(segt.query(1, 1, n, r + 1, n), segt.query(1, 1, n, 1, l - 1), segt.b[n]).mx);
		}
		else printf("%lld\n", segt.query(1, 1, n, r + 1, l - 1).mx);
	}
	return 0;
}
~~~


---

## 作者：Farkas_W (赞：3)

### 思路：

$\quad$对于此题考虑使用线段树维护，因为有环，所以断环为链，数组开两倍，另外距离换成坐标(距离的前缀和)，假设最后求的两棵树分别为 $x$ ， $y$ $(dis_x<dis_y)$，那么答案就是 $2\times (h_x+h_y)+dis_y-dis_x$ ，就是 $(2\times h_x-dis_x)+(2\times h_y+dis_y)$ ，那么我们线段树维护这两个值及答案，一个作答案的左端点( $x$ )，一个作答案的右端点( $y$ )，注意要保证 $dis_x<dis_y$ ，建树和询问的代码应重点看看，另外询问返回的值是结构体，数值初始化应为 $-inf$ ，因为 $sumr$ 的值可能为负，时间复杂度为 $O((n+m)\log {2n})$。

```cpp
struct node{
  int suml,sumr,Max;
}t[N<<2];
il void build(int k,int l,int r)
{
  if(l==r){t[k].suml=h[l]+dis[l];t[k].sumr=h[l]-dis[l];t[k].Max=-inf;return;}//suml表示作右端点，sumr表示作左端点
  int mid=l+r>>1;
  build(k<<1,l,mid);build(k<<1|1,mid+1,r);
  t[k].suml=max(t[k<<1].suml,t[k<<1|1].suml);
  t[k].sumr=max(t[k<<1].sumr,t[k<<1|1].sumr);
  t[k].Max=max(t[k<<1].Max,max(t[k<<1|1].Max,t[k<<1|1].suml+t[k<<1].sumr));//取 (左儿子的最大值，右儿子的最大值，左儿子中最适合作左端点的加上右儿子中最适合作右端点的和) 这三者的最大值 
}
il node query(int k,int l,int r,int x,int y)
{
  if(x<=l&&y>=r)return t[k];
  int mid=l+r>>1;node t1,t2,t3;
  t1.suml=t1.sumr=t1.Max=t2.suml=t2.sumr=t2.Max=t3.suml=t3.sumr=t3.Max=-inf;
  if(x<=mid)t1=query(k<<1,l,mid,x,y);
  if(y>mid)t2=query(k<<1|1,mid+1,r,x,y);
  t3.suml=max(t1.suml,t2.suml);
  t3.sumr=max(t1.sumr,t2.sumr);
  t3.Max=max(t1.Max,max(t2.Max,t2.suml+t1.sumr));
  return t3;
}
```

$\quad$关于变量名的解释：用数组 $h_i$ 表示第 $i$ 棵树的高度(或 $i-n$ )，数组 $d_i$ 表示第 $i$ 棵树和第 $i+1$ 棵树的距离，数组 $dis_i$ 表示第 $i$ 棵树的坐标， $sumr$ 指最大的可做左端点的数， $suml$ 指最大的可做右端点的数， $Max$ 指这个区间的最大答案

$\quad$再看看主函数吧，求补集的操作要额外注意
```cpp
signed main()
{
  n=read();m=read();
  for(re i=1;i<=n;i++)d[i]=d[i+n]=read();
  for(re i=1;i<=n;i++)h[i]=h[i+n]=read()<<1;
  for(re i=1;i<=n<<1;i++)dis[i]=dis[i-1]+d[i-1];//注意d[i-1]表示的才是第i-1棵树与第i棵树的距离
  build(1,1,n<<1);//建树
  while(m--)
    {
      re x=read(),y=read();
      if(y<x){swap(x,y);x++;y--;}  //这个求补集的操作也要额外注意
      else {swap(x,y);x++;y=y+n-1;}//这个求补集的操作也要额外注意
      print(query(1,1,n<<1,x,y).Max);putchar('\n');
    }
  return 0;
}
```

---

## 作者：xuyifei0302 (赞：2)

首先，这里是一个环，所以我们考虑断环成链，方便我们操作。

然后，我们发现，我们任选两棵树。则此时的运动量为之间的总距离加上这两棵树的高度的两倍。由于我们一开始将环转化成了链，所以可以把这个距离用前缀和预处理出来。

我们定义 $maxn_i$ 表示从 $1$ 到 $i$ 中，树之间的距离之和加上这棵树的两倍。$minn_i$ 表示从 $1$ 到 $i$ 中，树之间的距离之和减去这棵树的两倍。将二者作差，就可以求出选择这两棵树的运动量。

我们接着考虑查询的问题。

每次查询，都是一个区间，我们要想运动量最大，就需要找到这个区间内的最大值和最小值，很明显，我们可以用线段树来维护。那么，每次的答案就是最大值减去最小值。

这里，我们需要注意，万一这棵树的高度太高了，整个区间的最大值和最小值都是它，我们就要把次大值和次小值与这棵树进行配对，选取最大的一种作为答案。

接下来是代码环节：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, d[200005], h[200005], maxn[200005], sumd[200005], minn[200005], maxx[800005], minx[800005];
void buildtree(int p, int l, int r) {
	if (l == r) {
		maxx[p] = l;
		minx[p] = l;
		return;
	}
	int mid = (l + r) >> 1;
	buildtree(p * 2, l, mid);
	buildtree(p * 2 + 1, mid + 1, r);
	if (maxn[maxx[p * 2]] >= maxn[maxx[p * 2 + 1]]) {
		maxx[p] = maxx[p * 2];
	} else {
		maxx[p] = maxx[p * 2 + 1];
	}
	if (minn[minx[p * 2]] <= minn[minx[p * 2 + 1]]) {
		minx[p] = minx[p * 2];
	} else {
		minx[p] = minx[p * 2 + 1];
	}
}
int get_max(int p, int l, int r, int ll, int rr) {
	if (ll <= l && r <= rr) {
		return maxx[p];
	}
	int mid = (l + r) >> 1, maxn1 = 0, maxn2 = 0;
	if (ll <= mid) {
		maxn1 = get_max(p * 2, l, mid, ll, rr);
	}
	if (rr > mid) {
		maxn2 = get_max(p * 2 + 1, mid + 1, r, ll, rr);
	}
	if (maxn[maxn1] >= maxn[maxn2]) {
		return maxn1;
	} else {
		return maxn2;
	}
}
int get_min(int p, int l, int r, int ll, int rr) {
	if (ll <= l && r <= rr) {
		return minx[p];
	}
	int mid = (l + r) >> 1, minn1 = 0, minn2 = 0;
	if (ll <= mid) {
		minn1 = get_min(p * 2, l, mid, ll, rr);
	}
	if (rr > mid) {
		minn2 = get_min(p * 2 + 1, mid + 1, r, ll, rr);
	}
	if (minn[minn1] <= minn[minn2]) {
		return minn1;
	} else {
		return minn2;
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		if (i == n) {
			cin >> d[1];
			d[n + 1] = d[1];
			continue;
		}
		cin >> d[i + 1];
		d[i + n + 1] = d[i + 1];
	}
	for (int i = 1; i <= n; i ++) {
		cin >> h[i];
		h[i + n] = h[i];
	}
	for (int i = 1; i <= n * 2; i ++) {
		sumd[i] = sumd[i - 1] + d[i];
	}
	for (int i = 1; i <= n * 2; i ++) {
		maxn[i] = sumd[i] + 2 * h[i];
		minn[i] = sumd[i] - 2 * h[i];
	}
	maxn[0] = -1e18;
	minn[0] = 1e18;
	buildtree(1, 1, 2 * n + 1);
	while (m --) {
		int l, r;
		cin >> l >> r;
		if (l <= r) {
			int i = get_max(1, 1, 2 * n + 1, r + 1, n + l - 1), j = get_min(1, 1, 2 * n + 1, r + 1, n + l - 1);
			if (i == j) {
				int k, k1, kk, kk1;
				k = get_max(1, 1, 2 * n + 1, r + 1, i - 1);
				k1 = get_max(1, 1, 2 * n + 1, i + 1, n + l - 1);
				kk = get_min(1, 1, 2 * n + 1, r + 1, j - 1);
				kk1 = get_min(1, 1, 2 * n + 1, j + 1, n + l - 1);
				cout << max(max(maxn[k], maxn[k1]) - minn[j], maxn[i] - min(minn[kk], minn[kk1])) << "\n";
			} else {
				cout << maxn[i] - minn[j] << "\n";
			}
		} else {
			int i = get_max(1, 1, 2 * n + 1, r + 1, l - 1), j = get_min(1, 1, 2 * n + 1, r + 1, l - 1);
			if (i == j) {
				int k, k1, kk, kk1;
				k = get_max(1, 1, 2 * n + 1, r + 1, i - 1);
				k1 = get_max(1, 1, 2 * n + 1, i + 1, l - 1);
				kk = get_min(1, 1, 2 * n + 1, r + 1, j - 1);
				kk1 = get_min(1, 1, 2 * n + 1, j + 1, l - 1);
				cout << max(max(maxn[k], maxn[k1]) - minn[j], maxn[i] - min(minn[kk], minn[kk1])) << "\n";
			} else {
				cout << maxn[i] - minn[j] << "\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：Helloworldwuyuze (赞：2)

# Drazil and Park 题解

## 题意描述

在一个环上有 $n$ 个点，每个点到它前一个点的距离为 $d_i$，高度为 $h_i$。对于每个点对 $(x,y)$，总有两条路径可以走到。现在第 $i$ 天给定 $a_i,b_i$，若 $a_i\le b_i$，则封禁 $[a_i,b_i]$，否则封禁 $[a_i,n]\cup[1,b_i]$。因此每个点对之间的路径一定，距离一定，求

$$\max_{1\le i<j\le n}2(h_i+h_j)+\operatorname{dis}(x,y)$$

要求 $i,j$ 不在封禁的点内。

## Solution

### 破环为链

因为问题在环上，因此我们将这个环延长两倍变成一条链，对于 $a_i\le b_i$ 的情况，我们可以处理区间 $[b_i+1,a_i+n-1]$，否则可以处理区间 $[b_i+1,a_i-1]$。

画个图理解一下（绿色表示可选范围，红色标识封禁范围）：

$a_i\le b_i$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/66msyn2t.png)

$a_i>b_i$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/u8onfml6.png)

### 拆式子

对于 $2(h_i+h_j)+\operatorname{dis}(i,j)$，$i,j$ 会相互影响，因此拆成：

$$2(h_i+h_j)+\operatorname{dis}(i,j)=2h_i-\operatorname{dis}(1,i)+2h_j+\operatorname{dis}(1,j).$$

因此维护两个线段树，一个维护 $2h_x-\operatorname{dis}(1,x)$，另一个维护 $2h_j+\operatorname{dis}(1,j)$，每次在查找的区间内分别求两个线段树的最大值相加即可。

### 证明

但注意到还有限制 $i<j$，但我们分别求最大值并不能够保证它们的位置。我们设 $d_i=\operatorname{dis}(1,i)$，假设第一棵线段树的最大值位置在 $i$，第二棵在 $j$，$i>j$，即

$$\left\{\begin{matrix} 
  2h_i-d_i>2h_j-d_j \\  
  2h_j+d_j>2h_i+d_i
\end{matrix}\right. $$

因此

$$\left\{\begin{matrix} 
  2h_i-2h_j>d_i-d_j \\  
  2h_i-2h_j<d_j-d_i
\end{matrix}\right. $$

因为 $i>j$，必然 $d_i>d_j$，因此

$$\left\{\begin{matrix} 
  2h_i-2h_j>0 \\  
  2h_i-2h_j<0
\end{matrix}\right. $$

显然出现矛盾，因此 $i\le j$。

于是我们分类讨论：

- $i<j$，显然当前的答案就是最大答案，输出即可。

- $i=j$，显然我们要舍弃起点或者终点，若舍弃起点，那么在 $(l,loca-1)$ 内找到一个最大起点即可；如果舍弃终点，那么在 $(loca+1,r)$ 之间找到一个最大终点即可，其中 $loca$ 表示 $i$ 或者 $j$。答案对两种情况取 $\max$。

## AC CODE

``` cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<ctime>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
#include<vector>
#include<map>

using namespace std;

const int N = 2e5 + 10;
const int M = 2e5 + 10;
#define endl '\n'
#define int long long
const int INF = 0x3f3f3f3f3f3f3f3f;
typedef pair<int,int> PII;

int n,d[N],h[N],l,r,m;

struct node{
	int left,right,maxx,loca;
};

struct tree{
	node t[N<<2];
	void push_up(int p){
		if(t[p<<1].maxx<t[p<<1|1].maxx)	t[p].maxx=t[p<<1|1].maxx, t[p].loca=t[p<<1|1].loca;
		else	t[p].maxx=t[p<<1].maxx, t[p].loca=t[p<<1].loca;
	}
	void build(int p,int left,int right,int flag){
		t[p].left=left, t[p].right=right, t[p].maxx=0;
		if(left==right){
			t[p].loca=left;
			t[p].maxx=2*h[left]+flag*d[left];
			return ;
		}
		int mid=left+right>>1;
		build(p<<1,left,mid,flag), build(p<<1|1,mid+1,right,flag);
		push_up(p);
	}
	PII query(int p,int left,int right){
		if(left<=t[p].left&&t[p].right<=right)	return make_pair(t[p].maxx,t[p].loca);
		int mid=t[p].left+t[p].right>>1;
		PII res=make_pair(-INF,0);
		if(left<=mid)	res=max(res,query(p<<1,left,right));
		if(right>mid)	res=max(res,query(p<<1|1,left,right));
		return res;
	}
}t1,t2;

int solve(int l,int r){
	PII m1=t1.query(1,l,r), m2=t2.query(1,l,r);
	if(m1.second!=m2.second)	return m1.first+m2.first;
	else	return max(t1.query(1,l,m1.second-1).first+m2.first,t2.query(1,m1.second+1,r).first+m1.first);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)	cin>>d[i], d[i]+=d[i-1];
	for(int i=1;i<=n;++i)	cin>>h[i], h[i+n]=h[i];
	for(int i=n+1;i<=n<<1;++i)	d[i]=d[n]+d[i-n];
	for(int i=n<<1;i;--i)	d[i]=d[i-1];
	n<<=1;
	t1.build(1,1,n,-1), t2.build(1,1,n,1);
	int idx=0;
	while(m--){
		cin>>l>>r;
		if(l<=r)	cout<<solve(r+1,l+n/2-1)<<endl;
		else	cout<<solve(r+1,l-1)<<endl;
	}
	return 0;
}
```

---

## 作者：炎炎龙虾 (赞：2)

# [CF515E]Drazil and Park

Algorithm: 前缀和, 线段树
Created: Jun 20, 2020 11:45 PM
Difficulty: NOI/NOI+/CTSC
URL: https://codeforces.com/contest/515/problem/E

# 题目链接：

[Problem - E - Codeforces](https://codeforces.com/contest/515/problem/E)

[https://codeforces.ml/contest/515/problem/E](https://codeforces.com/contest/515/problem/E)  (Codeforces镜像站）

[Drazil and Park](https://www.luogu.com.cn/problem/CF515E)

# 题目大意：

就当是练习一下英语，大家自己去读题吧!

# 题解：

看到环想到什么？  没错，断环为链，拷贝两份，方便处理。

看到两点间距离想到什么？ 没错，计算前缀和。

看到询问多次最大值想到什么？ 没错，线段树维护最值

### 那么

从第一步开始。

读入，

然后断环为链并拷贝，计算前缀和

```cpp
for(int i=1;i<=n;i++)
    {
        cin>>d[i];
        d[n+i]=d[i];//断环为链
    }
    for(int i=1;i<=n;i++)
    {
        cin>>h[i];
        h[i]*=2;
        h[n+i]=h[i];//断环为链
    }
    for(int i=1;i<=2*n;i++)
        d[i]+=d[i-1];  //处理为前缀和的形式
```

由题意可知，若Dravil选择了两棵树$x$和$y$，那么他可以消耗的能量即为$d_x+d_(x+1)+⋯+d_(y-1)+2*(h_x+h_y)$

转换一下，即$(d_1+d_2+...+d(y-1)+2*h_y)+(2*h_x-(d_1+d_2+...+d(x-1)))$

设$a_k$为$(d_1+d_2+...+d(k-1)+2*h_k)$，设$b_k$为$(2*h_k-(d_1+d_2+...+d(k-1)))$

```cpp
t[x].a=h[l]+d[l-1];//前面已经处理为前缀和了，这里直接加减
t[x].b=h[l]-d[l-1];
```

题目中说孩子玩耍的区间为$[a,b]$，那么Dravil就不能经过该区间，若$a≤b$，则他可以经过区间$[b+1,a+n+1]$（因为此处已断环成链），否则，他可以经过的区间为$[b+1,a-1]$，设该区间为$I$。  $u,v∈I$，要使消耗的能量最大，即使$a_u+b_v$最大，即RMQ（区间最值）问题，因此可以用线段树维护每个区间的最值。

```cpp
int mid=(l+r)/2;
build(x*2,l,mid);
build(x*2+1,mid+1,r);
t[x].a=max(t[x*2].a,t[x*2+1].a);
t[x].b=max(t[x*2].b,t[x*2+1].b);
t[x].maxn=max(t[x*2].maxn,max(t[x*2+1].maxn,t[x*2].b+t[x*2+1].a)); //区间最值
```

$m$天中每天孩子玩耍的区间可以看做是$m$个询问，这样就转化为线段树上的问题了

最后附上AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+7;
const long long inf = 1LL*1e17;
long long d[MAXN],h[MAXN];
int n,m,a,b;
struct segment_tree //线段树
{
    int l,r;
    long long a,b,maxn;
}t[4*MAXN];
void build(int x,int l,int r)
{
    t[x].l=l;
    t[x].r=r;
    if(l==r)
    {
        t[x].a=h[l]+d[l-1];
        t[x].b=h[l]-d[l-1];
        t[x].maxn=-inf;
    }
    else
    {
        int mid=(l+r)/2;
        build(x*2,l,mid);
        build(x*2+1,mid+1,r);
        t[x].a=max(t[x*2].a,t[x*2+1].a);
        t[x].b=max(t[x*2].b,t[x*2+1].b);
        t[x].maxn=max(t[x*2].maxn,max(t[x*2+1].maxn,t[x*2].b+t[x*2+1].a)); //区间最值
    }
}
segment_tree ask(int x,int l,int r) //询问操作
{
    int lv=t[x].l,rv=t[x].r;
    if(l<=lv && rv<=r)
        return t[x];
    int mid=(lv+rv)/2; //二分
    segment_tree t1,t2,t3;//左子树，右子树，合并后树
    t1.a=t1.b=t1.maxn=t2.a=t2.b=t2.maxn=t3.a=t3.b=t3.maxn= -1*inf; //全部初始化为负无穷
    if(l<=mid)
        t1=ask(x*2,l,r);
    if(r>mid)
        t2=ask(x*2+1,l,r);
    t3.a=max(t1.a,t2.a);
    t3.b=max(t1.b,t2.b);
    t3.maxn=max(t1.maxn,max(t2.maxn,t1.b+t2.a));//区间最值
    return t3;
}
int main()
{
    ios::sync_with_stdio(false); //优化
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>d[i];
        d[n+i]=d[i];//断环为链
    }
    for(int i=1;i<=n;i++)
    {
        cin>>h[i];
        h[i]*=2;
        h[n+i]=h[i];//断环为链
    }
    for(int i=1;i<=2*n;i++)
        d[i]+=d[i-1];  //处理为前缀和的形式
    build(1,1,2*n);  //建树
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        if(a<=b)
            cout<<ask(1,b+1,a+n-1).maxn<<endl; //取补集进行操作
        else
            cout<<ask(1,b+1,a-1).maxn<<endl;
    }
    return 0;
}
```



---

## 作者：nydry (赞：1)

首先，对于一个环上的问题，常用的一个技巧是破环成链，具体做法是：开两倍的空间。这样，环上的区间总是能对应到链上的区间。

本题要求在某个区间内选择两个点 $x,y$，使得 $dis(x,y)+2(h_x+h_y)$ 最大。容易想到维护 $1$ 号点到每个点的距离 $d_i$，则原式变为 $d_y-d_x+2h_x+2h_y$，再整理成分别与 $x$ 和 $y$ 有关的两部分，即 $(2h_x-d_x)+(2h_y+d_y)$。所以可以对于每个点，维护 $a_i=2h_i-d_i$ 和 $b_i=2h_i+d_i$。原问题转化为在区间内选择 $i$ 和 $j$ 使得 $i<j$ 且 $a_i+b_j$ 最大。这可以用线段树维护。

```cpp
/*
(2*h[i]-dis[i])+(2*h[j]+dis[j])
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node{
	ll max1=-0x3f3f3f3f3f3f3f3f,max2=-0x3f3f3f3f3f3f3f3f,ans=-0x3f3f3f3f3f3f3f3f;
}t[800010];
int n,m;
ll d[200010];
ll h[200010];
ll dis[200010];
ll s1[200010],s2[200010];
void pushup(node&p,node l,node r){
	p.max1=max(l.max1,r.max1);
	p.max2=max(l.max2,r.max2);
	p.ans=max(max(l.ans,r.ans),l.max1+r.max2);
}
void build(int p,int lp,int rp){
	if(lp==rp){
		t[p].max1=s1[lp];
		t[p].max2=s2[lp];
		t[p].ans=-0x3f3f3f3f3f3f3f3f;
		return;
	}
	int mid=lp+rp>>1;
	build(p<<1,lp,mid);
	build(p<<1|1,mid+1,rp);
	pushup(t[p],t[p<<1],t[p<<1|1]);
}
node getsum(int l,int r,int p,int lp,int rp){
	if(l<=lp&&rp<=r)return t[p];
	int mid=lp+rp>>1;
	if(l<=mid&&r>mid){
		node res;
		pushup(res,getsum(l,r,p<<1,lp,mid),getsum(l,r,p<<1|1,mid+1,rp));
		return res;
	}
	else if(l<=mid)return getsum(l,r,p<<1,lp,mid);
	else return getsum(l,r,p<<1|1,mid+1,rp);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		d[n+i]=d[i];
	}
	for(int i=1;i<=n;i++){
		cin>>h[i];
		h[n+i]=h[i];
	}
	for(int i=1;i<=2*n;i++){
		dis[i]=dis[i-1]+d[i-1];
		s1[i]=2LL*h[i]-dis[i];
		s2[i]=2LL*h[i]+dis[i];
	}
	build(1,1,2*n);
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		int l=b+1,r=a-1;
		if(l>r)r+=n;
		node tmp=getsum(l,r,1,1,2*n);
		cout<<tmp.ans<<"\n";
	}
	return 0;
}
```

---

## 作者：run_away (赞：1)

## 题意

有一组圆环排列的树，给出 $i$ 到 $i+1$（$n$ 到 1）的距离 $d_i$ 和第 $i$ 棵树的高度 $h_i$。

一只猴子每天选择两棵树 $x,y$，然后消耗 $2(h_x+h_y)+dist(x,y)$ 的体力，其中 $dist(x,y)$ 表示 $x$ 到 $y$ 的距离。

每天都有孩子在 $a_i\sim b_i$ 的区间内玩耍，猴子只能在其他区间内活动，因此 $dist(x,y)$ 是一定的。

给出每天的 $a,b$，求猴子每天能消耗的最大体力。

## 分析

求区间最大值，考虑用线段树。

两棵树之间的距离可以破环成链后前缀和求解，设 $sum_i$ 为第 $i$ 位之前的距离和。

不妨设 $y>x$，则原函数为 $2h_x+2h_y+sum_y-sum_x=2h_x-sum_x+2h_y+sum_y$。

可以用线段树维护 $2h_i+sum_i$ 和 $2h_i-sum_i$，然后区间查找最大值即可。（其实是很裸的线段树）

## Code

```cpp
#include<bits/stdc++.h>
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll maxn=2e5+5;
ll n,m,d[maxn],h[maxn],sum[maxn];
struct linetree{ll v1,v2,ans;}t[maxn<<2];
inline linetree operator+(linetree a,linetree b){
	return {max(a.v1,b.v1),max(a.v2,b.v2),max({a.ans,b.ans,a.v2+b.v1})};
}
inline void buildtree(ll x,ll l,ll r){
    if(l==r){
        t[x].v1=h[l]*2+sum[l];
		t[x].v2=h[l]*2-sum[l];
        return;
    }
    buildtree(ls,l,mid),buildtree(rs,mid+1,r);
    t[x]=t[ls]+t[rs];
}
inline linetree treeask(ll x,ll s,ll e,ll l,ll r){
    if(l>=s&&r<=e)return t[x];
	if(e<=mid)return treeask(ls,s,e,l,mid);
	else if(s>mid)return treeask(rs,s,e,mid+1,r);
	return treeask(ls,s,e,l,mid)+treeask(rs,s,e,mid+1,r);
}
signed main(){
	n=read(),m=read();
	for(ll i=1;i<=n;++i)d[i]=d[i+n]=read();
	for(ll i=1;i<=n;++i)h[i]=h[i+n]=read();
	for(ll i=1;i<=n*2;++i)sum[i]=sum[i-1]+d[i-1];
	buildtree(1,1,n*2);
	while(m--){
		ll a=read(),b=read(),ans=0;
		if(a<=b){
			if(a!=1)ans=max(ans,treeask(1,1,a-1,1,n<<1).ans);
			if(b!=n){
				ans=max(ans,treeask(1,b+1,a+n-1,1,n<<1).ans);
				ans=max(ans,treeask(1,b+n+1,n<<1,1,n<<1).ans);
				
			}
		}
		else ans=max(ans,treeask(1,b+1,a-1,1,n<<1).ans);
		printf("%lld\n",ans);
	}
}
```

---

## 作者：xxbbkk (赞：1)

### 题目描述
有$n$个点，每个点有权值$h[i]$，第$i$个点与第$j$个点距离为$d[i]$,第$1$个点与第$n$个点相邻，$Q$次询问,每次询问给出$1$段区间，求区间内的两个点$i,j$，使$dis(i,j)+2*(h_i+h_j)$最大。
### 题目分析
一 环状：考虑断环为链；
二 最大化 $dis(i,j)+2(h_i+h_j)$
   
   前缀和维护$dis(i,j)=sum_j-sum_i$
   
   
   式子拆掉
  
   
  = $sum_j-sum_i+2*h_i+2*h_j$
  
 与$i$相关的放一起， 与$j$相关的放一起
 
  =$sum_j+2*h_j-(sum_i-2*h_i)$
  
  所以要最大化$sum_j+2*h_j$，最小化$sum_i-2*h_j$
  
  可以用$ST$表、线段树维护区间最值
  
  三 注意到$i,j$应为不同的两点，而直接用$ST$表存最值可能会出现两处最值在同一个点上，所以在处理$ST$表的同时要存一下最值的下标。如果在查询时遇到$(l,r)$最大最小在同一个点$pos$上的情况，处理出$(l,pos-1)$并$  (pos+1,r)$的最大最小值所在的位置，再与$pos$组合即可。
  
  四 记得开$long$ $long$
  
  ## code
  ```cpp
#include<bits/stdc++.h>
#define ll long long
#define N (500010)
using namespace std;
ll n,Q,a,b,t=22;
ll d[N],s[N],h[N];
//d:距离 h:如题 s:距离的前缀和
ll st1[N][25],st2[N][25],p1[N][25],p2[N][25];
//st1:最大值  st2:最小值
//p1:最大值的位置 p2:最小值的位置
inline void pre(){
	for(int i=1;i<=n+n;i++){
		st1[i][0]=s[i]+2*h[i];
		st2[i][0]=s[i]-2*h[i];
		p1[i][0]=p2[i][0]=i;
	}
	for(int j=1;j<t;j++){
		for(int i=1;i<=n+n;i++){
			if((i+(1<<(j-1)))>n+n) break;
			st1[i][j]=max(st1[i][j-1],st1[i+(1<<(j-1))][j-1]);
			if(st1[i][j-1]>st1[i+(1<<(j-1))][j-1]) p1[i][j]=p1[i][j-1];
			else p1[i][j]=p1[i+(1<<(j-1))][j-1];
			st2[i][j]=min(st2[i][j-1],st2[i+(1<<(j-1))][j-1]);
			if(st2[i][j-1]<st2[i+(1<<(j-1))][j-1]) p2[i][j]=p2[i][j-1];
			else p2[i][j]=p2[i+(1<<(j-1))][j-1];
		}
	}
	return;
}
//ST表预处理
inline ll askmax(ll l,ll r){
	ll tt=log2(r-l+1);
	if(st1[l][tt]>st1[r-(1<<tt)+1][tt]) return p1[l][tt];
	return p1[r-(1<<tt)+1][tt];
}
inline ll askmin(ll l,ll r){
	ll tt=log2(r-l+1);
	if(st2[l][tt]<st2[r-(1<<tt)+1][tt]) return p2[l][tt];
	return p2[r-(1<<tt)+1][tt];
}
//查询最大最小值所在的位置
inline ll calc(ll x,ll y){return s[x]+2*h[x]-s[y]+2*h[y];}
//计算两点之间的贡献
inline ll ask(ll l,ll r){
	ll pos1=askmax(l,r),pos2=askmin(l,r);
	if(pos1!=pos2) return calc(pos1,pos2);
	else{
		if(pos1>l&&pos1<r){
		   ll res1=max(calc(pos1,askmin(l,pos1-1)),calc(pos1,askmin(pos1+1,r)));
		   ll res2=max(calc(askmax(l,pos1-1),pos1),calc(askmax(pos1+1,r),pos1));
		   return max(res1,res2);
		}
		if(pos1==l&&pos1<r){
			ll res1=max(calc(askmax(pos1+1,r),pos1),calc(pos1,askmin(pos1+1,r)));
			return res1;
		}
		if(pos1==r&&pos1>l){
			ll res1=max(calc(askmax(l,pos1-1),pos1),calc(pos1,askmin(l,pos1-1)));
			return res1;
		}
	}
	return 0;
}
//如题解
int main(){
	scanf("%lld%lld",&n,&Q);
	for(int i=1;i<=n;i++){
		scanf("%lld",&d[i]);
		d[n+i]=d[i];
		s[i+1]=s[i]+d[i];
	}
	for(int i=n+1;i<=n+n;i++) s[i+1]=s[i]+d[i];
	for(int i=1;i<=n;i++){
		scanf("%lld",&h[i]);
		h[i+n]=h[i];
	}
	pre();
	while(Q--){
		scanf("%lld%lld",&a,&b);
		if(a>b) printf("%lld\n",ask(b+1,a-1));
		else printf("%lld\n",ask(b+1,a-1+n));
	}
	return 0;
}

```
完结撒花

---

## 作者：pikabi (赞：1)

### 前言
估计大家可能被点的权值（h）和边的长度（d）两者的维护卡了好久。我们可以来一次简单的转换，使复杂的数据变得简单。

### Main Tips

不妨把边长看成一个点，它拥有权值 $d_i$ ,那么相对应的原先的点也获得一个权值 $d_i = 0$ 。**为了不让边完全成为一个“点”**，**我们将它的 $h_i$ 设为 -inf，保证不是从边进入或出来。再用线段树维护一条 $4 \times n - 3$ 的点边集(再乘个二是因为我们要拆一个环)**， $l\_val$、 $r\_val$、$no\_val$、$two\_val$ 分别表示只有左端有 $h_i$ ，只有右端有 $h_i $，两端都无和两端都有。现在，它就变成了一道经典的线段树维护两端点权值 + 端点间距离的题目了。最后 query 一下就 OK 啦！

举个栗子：

$h_i: $ $ 2\qquad\quad 4 \qquad\quad 3 \quad\qquad  2\quad\qquad 4$

$\quad\,\,\,\, $1 $-->$ 2 $-->$ 3 $-->$ 1 $-->$ 2
   
$d_i: $ $ \quad\quad 2\quad\qquad 2 \quad\qquad 3 \quad\quad\quad  2$

上面是点权，下面边权，中间是编号。它现在变成惹 $-->$

$h_i: $ $2\quad -inf\qquad 4\quad-inf\quad\,\,\,\,3\quad-inf\qquad 3\quad-inf\qquad 4$


$\quad\,\,\,\, $ 1$-->$2$-->$3$-->$4$-->$5$-->$6$-->$7$-->$8$-->$9

$d_i:$ $\,\, 0\qquad\,\, 2\qquad\quad 0\qquad 2\quad\qquad0\qquad\quad 3\qquad 0\qquad\quad 2\qquad 0$

上面是更改后的点权，下面是更改后的边权，中间是更改后的编号。最后的答案就是 $two\_ans$ （两端都有 $h_i$）。目前为最优解 rank2 。

### Code

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define ll long long
#define inf 10000000000000000

using namespace std;

inline ll read(){
	ll x=0,w=0;char ch=getchar();
	while (!isdigit(ch))w|=ch=='-',ch=getchar();
	while (isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return w?-x:x;
}

struct node{
	ll two_val, l_val, r_val, no_val;
}a[8000005];

ll n, m, h[800005], dis[800005], two_ans, l_ans, r_ans, no_ans;

inline ll ls(ll p){
	return p << 1;
}

inline ll rs(ll p){
	return p << 1 | 1;
}

inline void update(int p){
	a[p].two_val = max(a[ls(p)].l_val + a[rs(p)].r_val, max(a[ls(p)].two_val , a[rs(p)].two_val ));
	a[p].l_val = max(a[ls(p)].l_val + a[rs(p)].no_val, a[rs(p)].l_val ) ;
	a[p].r_val = max(a[ls(p)].no_val + a[rs(p)].r_val, a[ls(p)].r_val ) ;
	a[p].no_val = a[ls(p)].no_val + a[rs(p)].no_val ;
}

inline void build(ll p, ll l, ll r){
	if(l == r){
		a[p].l_val = h[l] + dis[l];
		a[p].r_val = h[l] + dis[l];
		a[p].no_val = dis[l];
		return ;
	}
	ll mid = l + r >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	update(p);
}

inline ll query(ll p, ll l, ll r, ll L, ll R){
	if(L <= l && r <= R){
		two_ans = max(two_ans, max(a[p].two_val , l_ans + a[p].r_val ));
		l_ans = max(l_ans + a[p].no_val , max(a[p].l_val , l_ans));
		return 0;
	}
	ll mid = l + r >> 1;
	if(mid >= L) query(ls(p), l, mid, L, R);
	if(mid < R) query(rs(p), mid + 1, r, L, R);
}

int main(){
	n = read();
	m = read();
	for(int i = 2; i <= 2 * n; i += 2)
	dis[i] = read(), dis[i - 1] = 0;
	for(int i = 1; i <= 2 * n; i += 2)
	h[i] = read() * 2, h[i + 1] = -inf;
	for(int i = 1; i <= 2 * n; i++)
	dis[2 * n + i] = dis[i], h[i + 2 * n] = h[i];
	build(1, 1, 4 * n - 1);
	for(int i = 1; i <= m; i++){
		ll x = read(), y = read();
		two_ans = l_ans = -inf;
		if(x == y){
			query(1, 1, 4 * n - 1, 2 * x + 1, 2 * x - 3 + 2 * n);
		}
		else if(x < y){
			query(1, 1, 4 * n - 1, 2 * y + 1, 2 * x - 3 + 2 * n);
		}
		else {
			query(1 , 1, 4 * n - 1, 2 * y + 1, 2 * x - 3);
		}
		printf("%lld\n",two_ans);
	}
    return 0;
}

```

完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：lhc0707 (赞：0)

### 题意

给定一个环，求不在区间 $[a_i,b_i]$ 的两个不同的元素 $x,y$ 的 $2(h_x+h_y)+\operatorname{dis}(x,y)$ 的最大值。

### 题解

环上问题一般不好处理，我们可以参考 DP 中的处理方式，通过开二倍的方式，把环剖成链。对于给定的不能走的区间，如果 $a_i \leq b_i$，就在区间 $[b_i+1,a_i+n-1]$ 内查找最大值，否则在区间 $[b_i+1,a_i-1]$ 内查找最大值。

给出的式子包含两个点的信息，我们不好处理，考虑把这个式子拆成两个含有独立元素的式子。利用差分的思想，原式可表示为 $2h_x - \operatorname{dis}(1,x) + 2h_y +\operatorname{dis}(1,y)$，这样我们开两颗线段树，分别维护区间内 $2h_x - \operatorname{dis}(1,x)$ 和 $2h_x + \operatorname{dis}(1,x)$ 的最大值，另外要考虑如果 $x = y$，则应当在区间内另找两个最大值统计答案。

代码：

```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int N=200005;
int n,d[N],h[N],v[N][2],m,t[N<<2][2];
inline int getmax(int x,int y,int p){return v[x][p]>v[y][p]?x:y;}
void build(int p,int pl,int pr)
{
	if(pl==pr){t[p][0]=t[p][1]=pl;return;}
	int mid=(pl+pr)>>1;
	build(p<<1,pl,mid);build(p<<1|1,mid+1,pr);
	t[p][0]=getmax(t[p<<1][0],t[p<<1|1][0],0);
	t[p][1]=getmax(t[p<<1][1],t[p<<1|1][1],1);
}
int query(int p,int pl,int pr,int L,int R,int op)
{
	if(L<=pl&&pr<=R)return t[p][op];
	int mid=(pl+pr)>>1,ret=0ll;
	if(L<=mid)ret=getmax(ret,query(p<<1,pl,mid,L,R,op),op);
	if(R>mid)ret=getmax(ret,query(p<<1|1,mid+1,pr,L,R,op),op);
	return ret;
}
inline int qmax(int l,int r,int op){return l>r?0:query(1,1,n*2+1,l,r,op);}
inline int solve(int l,int r)
{
	int x=qmax(l,r,0),y=qmax(l,r,1);
	if(x!=y)return v[x][0]+v[y][1];
	int ret1=getmax(qmax(l,x-1,0),qmax(x+1,r,0),0);
	int ret2=getmax(qmax(l,x-1,1),qmax(x+1,r,1),1);
	return max(v[ret1][0]+v[y][1],v[x][0]+v[ret2][1]);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){cin>>d[i%n+1];d[i%n+1+n]=d[i%n+1];}
	for(int i=1;i<=n;i++){cin>>h[i];h[i+n]=h[i];}
	int sum=0;v[0][0]=v[0][1]=-1e18;
	for(int i=1;i<=n*2;i++)sum+=d[i],v[i][0]=2*h[i]-sum,v[i][1]=2*h[i]+sum;
	build(1,1,n*2+1);
	while(m--)
	{
		int a,b;cin>>a>>b;
		if(a<=b)cout<<solve(b+1,a+n-1)<<"\n";
		else cout<<solve(b+1,a-1)<<"\n";
	}
	return 0;
}
```

---

## 作者：Cxny (赞：0)

## Preface
难度远没有黑。
## Solution
环上问题首先破环成链。
 
询问中不能取区间 $[l,r]$，等价于只能取 $[l',r']$，其中
$$l'=r+1,r'=l+n-1\ \ \ \ (l\le r)$$
$$l'=r-1,r'=l+1\ \ \ \ (l>r)$$
对于距离，令 $dis_i=\sum_{j=1}^{i-1}d_j$，则两点 $x,y$ 间距离可简单转化为 $|dis_x-dis_y|$。
 
于是原问题转化为在给定区间中选出不同两点 $x,y$，最大化
$$2h_x+2h_y+|dis_x-dis_y|$$
不妨设 $dis_x>dis_y$，则原式转化为
$$2h_x+dis_x+2h_y-dis_y$$
将与 $x$ 和 $y$ 有关的部分分别计算即可。
 
具体地，分别计算出两部分最大值所对应的 $x,y$，若两者不同则直接相加，相同则某一部分取次大值。次大值位置可以同时维护，也可以二次查询。代码采用前者。

可以证明，得到的 $x,y$ 一定满足 $dis_x>dis_y$。

若 $dis_x<dis_y$，那么交换 $x,y$ 后得到的答案一定严格更优。而交换后的答案在计算时已经纳入考虑。

完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define lson (p << 1)
#define rson (p << 1 | 1)
#define mid ((l + r) >> 1)
const int maxn = 2e5 + 10;
int n, q;
ll a[maxn], h[maxn], sum1[maxn], sum2[maxn];
struct Node{
	int pos1, pos2;
	Node(){} Node(int p1, int p2): pos1(p1), pos2(p2){}
	Node operator + (const Node &t) const{
		return Node((sum1[pos1] > sum1[t.pos1] ? pos1 : t.pos1), (sum2[pos2] > sum2[t.pos2] ? pos2 : t.pos2));
	}
}t[maxn << 2];
void build(int l, int r, int p){
	if(l == r) return t[p] = Node(l, l), void();
	build(l, mid, lson), build(mid + 1, r, rson), t[p] = t[lson] + t[rson];
}
Node query(int l, int r, int p, int ql, int qr){
	if(r < ql || qr < l || ql > qr) return Node();
	if(ql <= l && r <= qr) return t[p];
	return query(l, mid, lson, ql, qr) + query(mid + 1, r, rson, ql, qr);
}
int main(){
	scanf("%d%d", &n, &q), sum1[0] = -1e18, sum2[0] = -1e18;
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i + 1]), a[i + n + 1] = a[i + 1];
	for(int i = 1; i <= n; i++) scanf("%lld", &h[i]), h[i + n] = h[i]; n *= 2;
	for(int i = 1; i <= n; i++) a[i] += a[i - 1], sum1[i] = h[i] * 2 + a[i], sum2[i] = h[i] * 2 - a[i];
	// for(int i = 1; i <= n; i++) printf("%lld - %lld\n", sum1[i], sum2[i]);
	build(1, n, 1); // print(1, n, 1);
	while(q--){
		int ql, qr, l, r; scanf("%d%d", &ql, &qr);
		if(ql <= qr) l = qr + 1, r = ql + n / 2 - 1;
		else l = qr + 1, r = ql - 1;
		Node res = query(1, n, 1, l, r);
		if(res.pos1 != res.pos2){printf("%lld\n", sum1[res.pos1] + sum2[res.pos2]); continue;}
		Node qwq = query(1, n, 1, l, res.pos1 - 1) + query(1, n, 1, res.pos1 + 1, r);
		printf("%lld\n", max(sum1[res.pos1] + sum2[qwq.pos2], sum1[qwq.pos1] + sum2[res.pos2]));
	}
	return 0;
}
```

---

