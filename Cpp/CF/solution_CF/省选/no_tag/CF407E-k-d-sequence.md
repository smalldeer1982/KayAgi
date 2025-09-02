# k-d-sequence

## 题目描述

We'll call a sequence of integers a good $ k $ - $ d $ sequence if we can add to it at most $ k $ numbers in such a way that after the sorting the sequence will be an arithmetic progression with difference $ d $ .

You got hold of some sequence $ a $ , consisting of $ n $ integers. Your task is to find its longest contiguous subsegment, such that it is a good $ k $ - $ d $ sequence.

## 说明/提示

In the first test sample the answer is the subsegment consisting of numbers 2, 8, 6 — after adding number 4 and sorting it becomes sequence 2, 4, 6, 8 — the arithmetic progression with difference 2.

## 样例 #1

### 输入

```
6 1 2
4 3 2 8 6 2
```

### 输出

```
3 5
```

# 题解

## 作者：loceaner (赞：23)

## 思路

要素察觉：必须要是一个公差为 $d$ 的等差数列。

### 特判

首先要特判掉 $d=0$ 的情况，这样的情况下就是要寻找最长的一段数字相同的区间，找到之后输出左右端点即可（可以 $O(n)$ 扫一遍）。

### 其他情况

再来看别的情况，对于一个区间 $[l,r]$，如果要满足是一个公差为 $d$ 的等差序列，那么：

- 这个等差数列里的所有数 $\bmod d$ 的结果应该一样.
- 区间内没有重复的数.

现在考虑如何实现上述条件：

- 首先将序列分成若干个 $x \bmod d$ 都一样的子区间。

  在从左往右扫的过程中，如果遇到了与前面 $x\bmod d$ 的值不同的数，就将左边 $x\bmod d$ 值相同的数作为一个独立的区间来处理，这样就可以把序列分成若干个 $x \bmod d$ 都一样的区间。

- 对于一个满足 $x\bmod d=c$ 的数列，把所有的 $x$ 变成 $\dfrac{x-c}{d}$ （因为整形的性质，可以直接除）。

  这一步称之为归一化，实现了将一个区间的的公差化为 $1$，
  
  问题就转化成了加入 $k$ 个数，使区间排序后公差为 $1$。

- 对于一个区间 $[L,R]$，算出最少加几个数。

  需要满足的条件显然就是不能有重复，那么最少加的数的个数就是 $\max(L,R)-\min(L,R)+1-(R-L+1)$。

- 从小到大枚举 $R$。

  那么问题就相当于求最小的 $L$，使得

  - $[L,R]$ 无重复。

    从小到大枚举 $R$,对于新的 $a[R]$ 很容易知道它前面一个和他相等的数 $a[T]$ （可以用$map$实现），那么 $L$ 至少要大于 $T$。

  - 加的数不能多于 $k$ 个。

    也就是 $\max(L,R)-\min(L,R)+1-(R-L+1)\le k$，转化一下即 $\max(L,R)-\min(L,R)+L\le k + R$，

    用线段树维护 $w[L]=\max(L,R)-\min(L,R)+L$，

    假如 $L$ 的下界是 $T$，那么我们要在 $[T+1,R]$ 中找最左的位置使得 $w\le k + R$。

如果能完成上述过程，这道题就做完了，那么现在的问题是，如何维护 $w$。

#### 维护 $w$的方法

用单调栈。维护一个单调递减的栈和一个单调递增的栈，两个栈的维护方法是同理的，此处以单调递减的栈为例进行讲解。

因为单调栈递减的性质，所以当一个大于栈顶的元素加入时，会不断地弹出栈顶，直到栈顶元素大于此元素为止，再将此元素入栈，由此，**单调栈可以将 $\max(L,R)$ 分成递减的若干段**，考虑是如何实现的：

1. 如图所示，假设有一个单调递减的单调栈，其中 $S1> S2> S3$，$S3$ 为栈顶元素。

   ![1](https://cdn.luogu.com.cn/upload/image_hosting/t2ijx361.png)

2. 由于单调栈的性质，$S1$ 和栈中上一个元素之间可能是有别的元素的，所以 $S1,S2,S3$ 其实代表了三个区间的最大值。

   ![2](https://cdn.luogu.com.cn/upload/image_hosting/ygxa0sv4.png)

3. 此时，单调栈中来了一个新的元素 $a$，显然 $a>S1>S2>S3$，为了维护单调栈的性质，所以我们要将 $S1,S2,S3$ 弹栈。

   ![3](https://cdn.luogu.com.cn/upload/image_hosting/d9smyt4p.png)

4. 在弹栈时，因为此时这三个元素的值不能代表上述三个段的最大值了，所以我们需要将三个段的贡献从线段树中减去。

   ![4](https://cdn.luogu.com.cn/upload/image_hosting/al5zxa69.png)

5. 同时，新的元素 $a$ 就加进来了，这个时候就可以发现原来三个段的代表元素被弹出之后，其实就被新元素所接管了，整个区间的最大值变成 $a$ 元素的值，所以再对一整个区间进行区间加操作。

   ![5](https://cdn.luogu.com.cn/upload/image_hosting/qg3k2one.png)

这样单调栈就实现了将 $\max(L,R)$ 分成了递减的若干段，由此就可以不断进行段树的区间加、区间减。

$\min$ 的维护与 $\max$ 同理。

总时间复杂度 $O(n\log n)$。

## 代码

```cpp
/*
Author:loceaner
线段树，单调栈 
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;

const int A = 2e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

bool flag;
map <int, int> last;
int sl[A], topl, sr[A], topr;
struct tr { int l, r, lazy, w; } t[A << 2];
int n, k, d, ansl = 1, ansr = 1, a[A], ans;

inline void pushup(int rt) {
  t[rt].w = min(t[lson].w, t[rson].w);
}

inline void calc(int rt, int x) {
  t[rt].lazy += x, t[rt].w += x;
}

inline void pushdown(int rt) {
  if (t[rt].lazy && t[rt].l < t[rt].r) {
    calc(lson, t[rt].lazy), calc(rson, t[rt].lazy);
    t[rt].lazy = 0;
  }
}

void build(int rt, int l, int r) {
  t[rt].l = l, t[rt].r = r, t[rt].lazy = 0, t[rt].w = 0;
  if (l == r) { t[rt].w = l; return; }
  int mid = (l + r) >> 1;
  build(lson, l, mid), build(rson, mid + 1, r);
  pushup(rt);
}

void insert(int rt, int l, int r, int k) {
  if (l <= t[rt].l && t[rt].r <= r) return calc(rt, k);
  pushdown(rt);
  int mid = (t[rt].l + t[rt].r) >> 1;
  if (l <= mid) insert(lson, l, r, k);
  if (r > mid) insert(rson, l, r, k);
  pushup(rt);
}

int work(int rt, int k) {
  if (t[rt].l == t[rt].r) return t[rt].l;
  pushdown(rt);
  if (t[lson].w <= k) return work(lson, k);
  else return work(rson, k);
}

void query(int rt, int l, int r, int k) {
  if (l <= t[rt].l && t[rt].r <= r) {
    if (t[rt].w <= k) flag = 1, ans = work(rt, k);
    return;
  }
  pushdown(rt);
  int mid = (t[rt].l + t[rt].r) >> 1;
  if (l <= mid && !flag) query(lson, l, r, k);
  if (r > mid && !flag) query(rson, l, r, k);
}

void del(int rt, int x) {
  if (x < t[rt].l || x > t[rt].r) return;
  pushdown(rt);
  if (t[rt].l == x && t[rt].r == x) { t[rt].w = 0; return; }
  del(lson, x), del(rson, x);
  pushup(rt);
}

int main() {
  n = read(), k = read(), d = read();
  for (int i = 1; i <= n; i++) a[i] = read() + inf;
  if (d == 0) {
    for (int i = 1; i <= n; i++) {
      int l = i;
      while (a[i] == a[i + 1] && i < n) i++;
      if (ansr - ansl < i - l) ansl = l, ansr = i;
    }
    cout << ansl << ' ' << ansr << '\n';
    return 0;
  }
  build(1, 1, n);
  //枚举右端点 
  for (int i = 1, L = 1; i <= n; i++) {
    int tmp = L;
    if (a[i] % d == a[i - 1] % d) L = max(L, last[a[i]] + 1);
    else L = i;
    last[a[i]] = i;
    while (tmp < L) del(1, tmp++);
    //递增栈 
    while (topl && sl[topl] >= L && a[sl[topl]] >= a[i]) {
      insert(1, max(L, sl[topl - 1] + 1), sl[topl], a[sl[topl]] / d);
      topl--;
    }
    insert(1, max(L, sl[topl] + 1), i, -a[i] / d);
    sl[++topl] = i;
    //递减栈
    while (topr && sr[topr] >= L && a[sr[topr]] <= a[i]) {
      insert(1, max(L, sr[topr - 1] +1), sr[topr], -a[sr[topr]] / d);
      topr--;
    }
    insert(1, max(L, sr[topr] + 1), i, a[i] / d);
    sr[++topr] = i;
    flag = 0, ans = 0;
    query(1, L, i, k + i); //思路中的式子 
    if (ansr - ansl < i - ans) ansl = ans, ansr = i;
  }
  cout << ansl << " " << ansr << '\n';
  return 0;
}
```

---

## 作者：Forever1507 (赞：9)

## CF407E

很厉害的数据结构题！

如果你做过 CF526F Pudding Monsters 的话，你应该会处理区间值域连续段的方法。注意到区间连续段等价于公差为 $1$ 的等差序列，因此考虑如何把本题的公差任意的等差序列进行转化。

注意到两个模 $d$ 不相等的数不可能划分进同一个子区间内，因此考虑先将原问题划分成若干个模 $d$ 相等的连续段，段内每个数直接除掉 $d$，这样就直接转化成了维护区间连续段的问题。

如何判断一个区间是否是值域连续段呢？一个显然的转化是 $\max-\min=r-l$ 且区间内的数两两互不相同。后一个条件是好维护的，我们暂时先只考虑前面这个式子。那么至多加入 $k$ 个数，也就是 $(\max-\min)-(r-l)\le k$，这个也是显然的。

我们对于 $r$ 这一维进行扫描线，维护 $val_i$ 表示当 $l=i$ 时 $\max-\min+l$ 的值，假如我们得到了这个就直接找到最小的 $i$ 满足 $val_i\le r+k$ 并且 $[i,r]$ 中没有重复元素即可，重复元素这里直接开一个 `std::map` 存一下即可。

套用 CF526F 的技巧，我们考虑线段树维护这个信息，显然 $\max,\min,l$ 时可以分开维护的。

最简单的是  $l$，建树的时候直接把叶子节点的值赋值为序列上对应的下标即可。$\min,\max$ 可以使用单调栈，由于这两个部分本质相同我们这里就只考察 $\min$ 的情形。设 $L_i,R_i$ 分别表示 $i$ 左右第一个小于 $a_i$ 的位置，这个用单调栈是简单的，然后我们考虑贡献，相当于左端点在 $[L_i+1,i]$，右端点在 $[i,R_i-1]$ 之内的所有区间的 $\min$ 都是 $a_i$，那么相当于做一个矩形加，按照扫描线的模板差分后离线成两个区间修改即可。

这样的话我们就可以在 $r$ 递增的过程中动态得到维护了 $val_i$ 的线段树，那么维护一个区间最小值就可以直接在线段树上二分了。

特别的，这个做法不适用 $d=0$，但是 $d=0$ 直接找到一个最长连续段就行了。

---

## 作者：do_while_true (赞：8)

题意：求最长区间使得加入 $k$ 个数后 sort 后最后为一个公差为 $d$ 的等差数列。多解输出 $l$ 最小的答案。

$n,k\leq 2\times 10^5,0\leq d\leq 10^9$

- $d=0$ 的情况特判一下，找最长的值都相同的段即可

- $d\neq 0$ 的情况：

是公差为 $d$ 等差数列需要满足两个条件：

- $\bmod\ d$ 相同；
- 值两两不同。

可以单独处理每个极长的同余的段，然后分开处理：

先都整除一下 $d$，问题都转化成处理公差 $d$ 为 $1$ 的情况。

这个区间合法要求 $\max-\min+1-(R-L+1)\leq k$，枚举 $r$ 统计最小的 $l$ 使得：

- $[L,R]$ 内元素无重复；

- $\max-\min+1-(R-L+1)\leq k$。

其中 $\max$/$\min$ 为区间 $[L,R]$ 的最大/小值

无重复的条件很好做，记录一下每个值上次出现的位置，然后记录一下 $l$ 的下界 $T$。

设 $w_L=\max(L,R)-\min(L,R)+L$

求 $[T+1,R]$ 中最左的 $L$ 使得 $w_L\leq k+R$，假如我们可以快速维护 $w$ ，就可以解决这个问题。

怎样维护 $w$？

注意 $\max(L,R)$ 是递减的，$\min$ 也类似。$\max(L,R)$ 可以维护一个单调栈，栈中的每个点都代表一段区间，它们的 $\max(L,R)$ 是这个栈中的这个元素。那么每次弹出的时候修改这个区间的 $w$ 即可。

操作是区间加减，需要支持的查询为区间最左侧小于等于某个数的位置，这是个经典问题，记录一下区间最小值即可。

均摊下来复杂度是对的，操作数仅有 $\mathcal{O}(n)$ 个。

实现上有几个小细节，对于每个同余段重新建一棵大小为这个段长度的树，如果每次都 $\mathcal{O}(n)$ 建树，复杂度是错误的。$a_i$ 有负数，提前全加上 $10^9$ 转化成非负数，不影响答案。

综上所述，我们完美的解决了这个问题，时间复杂度 $O(n\log n)$

```cpp
//Code by do_while_true
#include<iostream>
#include<cstdio>
#include<map>
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r <<1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
const int N = 200010;
const int INF = 0x7fffffff;
int n, k, d;
int a[N];
std::map<int, int>pre; 
#define tl tree[x].l
#define tr tree[x].r
#define ls tree[x].lson
#define rs tree[x].rson
int trnt;
struct SGT {
	int l, r, sum, mn, tag, lson, rson;
}tree[N << 1];
inline void pushup(int x) { tree[x].mn = Min(tree[ls].mn, tree[rs].mn); }
inline void pushdown(int x) {
	if(tree[x].tag) {
		int &p = tree[x].tag;
		tree[ls].mn += p; tree[rs].mn += p;
		tree[ls].tag += p; tree[rs].tag += p;
		p = 0; 
	}
}
int build(int l, int r) {
	int x = ++trnt; tl = l; tr = r;
	tree[x].mn = tree[x].tag = tree[x].lson = tree[x].rson = 0;
	if(l == r) return x;
	ls = build(l, (l + r) >> 1); rs = build(tree[ls].r+1, r);
	return x;
}
void modify(int x, int l, int r, int v) {
	if(tree[x].l >= l && tree[x].r <= r) {
		tree[x].mn += v;
		tree[x].tag += v;
		return ;
	}
	pushdown(x);
	int mid = (tr + tl) >> 1;
	if(mid >= l) modify(ls, l, r, v);
	if(mid < r) modify(rs, l, r, v);
	pushup(x); 
}
int query(int x, int l, int r, int v) {
	if(tree[x].mn > v) return INF;
	if(tl >= l && tr <= r) {
		if(tl == tr) return tl;
		pushdown(x); int sumq = 0;
		if(tree[ls].mn <= v) sumq = query(ls, l, r, v);
		else sumq = query(rs, l, r, v);
		pushup(x);
		return sumq;
	}
	pushdown(x);
	int mid = (tl + tr) >> 1, sumq;
	if(r <= mid) sumq = query(ls, l, r, v);
	else if(l > mid) sumq = query(rs, l, r, v);
	else {
		sumq = query(ls, l, r, v);
		if(sumq == INF) sumq = query(rs, l, r, v);
	}
	pushup(x);
	return sumq;
}
#undef tl
#undef tr
#undef ls
#undef rs
int L[N], R[N], bcnt, ansl = 1, ansr = 1;
int st1p[N], st1x[N], top1;
int st2p[N], st2x[N], top2;
int down;
signed main() {
//	freopen("in.txt", "r", stdin);
	read(n); read(k); read(d);
	if(!d) {
		for(int i = 1; i <= n; ++i) read(a[i]);
		int l = 1;
		for(int i = 2; i <= n; ++i) {
			if(a[i] != a[i-1]) {
				if(i - l > ansr - ansl + 1) ansl = l, ansr = i-1;
				l = i;
			}
		}
		printf("%d %d\n", ansl, ansr);
		return 0;
	}
	for(int i = 1; i <= n; ++i) read(a[i]), a[i] += 1000000000;
	L[bcnt = 1] = 1;
	for(int i = 2; i <= n; ++i) {
		if(a[i] % d != a[i-1] % d) {
			R[bcnt] = i-1;
			L[++bcnt] = i;
		}
	}
	R[bcnt] = n;
	for(int i = 1; i <= bcnt; ++i) {
		if(R[i] - L[i] == 0) continue ;
		int nowl = 1, nowr = 0;
		pre.clear();
		top1 = top2 = 0; trnt = 0; down = 1;
		build(1, R[i] - L[i] + 1);
		for(int j = L[i]; j <= R[i]; ++j) a[j] /= d;
		for(int j = L[i]; j <= R[i]; ++j) {
			if(pre[a[j]]) down = Max(down, pre[a[j]]-L[i]+2);
			pre[a[j]] = j;
			while(top1 && st1x[top1] <= a[j]) modify(1, st1p[top1-1]+1, st1p[top1], -st1x[top1]), --top1;
			while(top2 && st2x[top2] >= a[j]) modify(1, st2p[top2-1]+1, st2p[top2], st2x[top2]), --top2;
			st1x[++top1] = a[j]; st1p[top1] = j-L[i]+1;
			st2x[++top2] = a[j]; st2p[top2] = j-L[i]+1;
			modify(1, st1p[top1-1]+1, st1p[top1], st1x[top1]);
			modify(1, st2p[top2-1]+1, st2p[top2], -st2x[top2]);
			modify(1, j-L[i]+1, j-L[i]+1, j);
			int pl = query(1, down, j-L[i]+1, k+j);
			if(pl != INF && j - (pl+L[i]-1) + 1 > nowr - nowl + 1) nowl = pl+L[i]-1, nowr = j;
		}
		if(nowr - nowl + 1 > ansr - ansl + 1) ansl = nowl, ansr = nowr; 
	}
	printf("%d %d\n", ansl, ansr);
	return 0;
} 
```

---

## 作者：FutaRimeWoawaSete (赞：6)

CF407E。

其实没有 3100 难度的，虽然我憨了维护简单的东西居然去想吉司机，但是确实是没有这个难度。

我们考虑两个基础的问题：给定一个区间，如何用尽量少的信息判断它是一个可插入的区间并计算区间至少需要插入的元素个数。

第一问很简单，显然等差数列中的每个数 $\text{mod}$ $d$ 的值相等，并且不能有数重复，两个条件即可限制第一问了。

第二问对于区间 $[l,r]$ 我们直接用 $\frac{\max_{i = l} ^ r a_i - \min_{i = l} ^ r a_i}{d} + 1 - (r - l + 1)$ 即可计算，即数列总项减去数列中已有的项数。

然后就板了。对于第一问我们先限制第一个条件，将序列分成许多模意义下值相同的颜色段处理，对于每个颜色段我们扫描线，每次处理 $r$ 为右端点的答案，维护 $\text{lst}_i$ 表示一个颜色 $i$ 上一次在序列出现的位置，滚一个 $\text{lst}$ 的前缀 $\text{max}$ 即可维护在做 $r$ 时，$l$ 至多能选到哪里。

对于这个区间的点也不完全合法。我们还需要找到最靠左的 $l$ 满足至多填入 $k$ 个数就将区间 $[l,r]$ 重排成公差为 $d$ 的等差数列。

考虑上述的计算式，我们显然可以让 $a_i$ 在模意义下值相同时统一变成 $\lfloor \frac{a_i}{d} \rfloor$，记为 $b_i$，则原关系写成：

- $\max_{i = l} ^ r b_i - \min_{i = l} ^ r b_i + 1 - (r - l + 1) \leq k$

移项一下就变成：

- $\max_{i = l} ^ r b_i - \min_{i = l} ^ r b_i + l \leq k + r$

右式 $r$ 固定时可计算，对于左式记 $p_l = \max_{i = l} ^ r b_i - \min_{i = l} ^ r b_i + l$。

显然我们可以开单调递增和单调递减的单调栈，然后就将 $\max$ 与 $\min$ 做成区间加的问题了，具体来说我们栈内存的节点将当前处理的段分成一些小段，每一段的 $\max(l,r)$ 或 $\min(l,r)$ 是相等的（即将 $l$ 作为变元的意义下），在弹出和加入时都可以直接撤销/加入贡献，问题自然也就变成了区间加。

维护区间 $p$ 值的 $\min$，每个 $r$ 就可以用线段树二分找其最靠左的合法 $l$ 了。

时间复杂度 $O(n \log n)$。注意颜色段选取时判相等时应用绝对值判。

```cpp
/*
显然我们先找出来区间最小数。
诶呀这道题非得 dp 吗。
我们知道的是插入不影响 false，所以一定有一个单调 limit 使得后面的都不行。
找到它，然后直接差分算答案？
然后一个区间的需求元素就是 (maxn - minn) / k - len
这个数据结构可做吧，扫描线然后吉司机？ 
随便瞄了下题解感觉思路很不一样，也许寄了。 
sb，这个可以直接单调栈，这都看不出来吗脑瘫。 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)
int mn[Len << 2],tag[Len << 2];
void push_up(int x){mn[x] = min(mn[ls(x)] , mn[rs(x)]);}
void push_down(int p)
{
	if(tag[p])
	{
		tag[ls(p)] += tag[p] , tag[rs(p)] += tag[p];
		mn[ls(p)] += tag[p] , mn[rs(p)] += tag[p];
		tag[p] = 0;
	}
}
void build(int p,int l,int r)
{
	if(l == r) 
	{
		mn[p] = l;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
}
void update(int p,int l,int r,int nl,int nr,int w)
{
	if(nl <= l && nr >= r){tag[p] += w , mn[p] += w;return;}
	push_down(p);
	int mid = (l + r) >> 1;
	if(nl <= mid) update(ls(p) , l , mid , nl , nr , w);
	if(nr > mid) update(rs(p) , mid + 1 , r , nl , nr , w);
	push_up(p);	
}
int idx(int p,int l,int r,int nl,int nr,int w)
{
	if(r < nl || l > nr || mn[p] > w) return 0; 
	if(l == r) return l;
	push_down(p);
	int mid = (l + r) >> 1 , res = 0;
	res = idx(ls(p) , l , mid , nl , nr , w);
	if(res) return res;
	return idx(rs(p) , mid + 1 , r , nl , nr , w);
}
int n,k,d,lst[Len],a[Len],b[Len],lsh[Len],cnt,Ansl,len;
int stkmx[Len],topmx,stkmn[Len],topmn;
void push_mx(int x)
{
	while(topmx && a[stkmx[topmx]] < a[x])
	{
		update(1 , 1 , n , stkmx[topmx - 1] + 1 , stkmx[topmx] , -a[stkmx[topmx]]);
		topmx --;
	}
	stkmx[++ topmx] = x;
	update(1 , 1 , n , stkmx[topmx - 1] + 1 , stkmx[topmx] , a[stkmx[topmx]]);
}
void push_mn(int x)
{
	while(topmn && a[stkmn[topmn]] > a[x])
	{
		update(1 , 1 , n , stkmn[topmn - 1] + 1 , stkmn[topmn] , a[stkmn[topmn]]);
		topmn --;
	}
	stkmn[++ topmn] = x;
	update(1 , 1 , n , stkmn[topmn - 1] + 1 , stkmn[topmn] , -a[stkmn[topmn]]);
}
void Work(int L,int R)
{
	stkmx[0] = stkmn[0] = L - 1;int Ll = L - 1;
	for(int i = L ; i <= R ; i ++) a[i] /= d;
	for(int i = L ; i <= R ; i ++)
	{
		int fd = k + i;
		push_mx(i) , push_mn(i);
		Ll = max(Ll , lst[b[i]]);
		int ll = idx(1 , 1 , n , Ll + 1 , i , fd) , rr = i , las = rr - ll + 1;
		//printf("%d %d\n",ll,rr);
		if(las > len || las == len && (ll < Ansl))
		{
			Ansl = ll;
			len = las;
		}
		lst[b[i]] = i;
	}
	topmx = topmn = 0;
	for(int i = L ; i <= R ; i ++) lst[b[i]] = 0;
}
int main()
{
	n = read() , k = read() , d = read();
	for(int i = 1 ; i <= n ; i ++) a[i] = lsh[i] = read();
	if(!d)
	{
		int lst = 1;
		for(int i = 1 ; i <= n ; i ++) 
		{
			if(a[i] != a[lst])
			{
				int ll = lst , rr = i - 1 , las = rr - ll + 1;
				if(las > len){Ansl = ll;len = las;} 
				lst = i;
			}
		}
		printf("%d %d\n",Ansl,Ansl + len - 1);
		return 0;
	}
	sort(lsh + 1 , lsh + 1 + n);
	cnt = unique(lsh + 1 , lsh + 1 + n) - lsh - 1;
	for(int i = 1 ; i <= n ; i ++) b[i] = lower_bound(lsh + 1 , lsh + 1 + cnt , a[i]) - lsh;
	int lst = 1;build(1 , 1 , n);
	for(int i = 2 ; i <= n ; i ++)
	{
		if((a[lst] % d + d) % d != (a[i] % d + d) % d)
		{
			Work(lst , i - 1);
			lst = i;
		}
	}
	Work(lst , n);
	printf("%d %d\n",Ansl,Ansl + len - 1);
	return 0;
}
```

---

## 作者：KazamaRuri (赞：4)

## 题意

找一个最长的子区间使得该子区间加入至多 $ k $ 个数以后，排序后是一个公差为 $ d $ 的等差数列。

## 分析

由简入难，由一般入特殊，考虑特殊情况怎么做。

发现公差为 $ d $ 的限制非常难办，那就从 $ d $ 入手简化问题。

当 $ d = 0 $ 时，答案显然是最长相同数的连续段。

进一步的，当 $ d = 1 $ 时，找等差数列变成了找一段同时被加上任意一个数的排列，我们可以得到一个区间 $ [l,r] $ 满足条件的充要条件为：
$$
[ \text{ 区间中没有重复元素 } ] \land [ \max_{i=l}^{r} a_i - \min_{i=l}^{r} a_i + 1 - ( r - l + 1 ) \le k ]
$$

简单解释一下第二个条件，$ \max - \min + 1 $ 表示这个等差数列“应有”的长度，$ r - l + 1 $ 表示等差数列“实际”拥有的长度，而 $ k $ 恰好是我们把理想化作实际的纽带，只有能用 $ k $ 个数把这个区间“补”成等差数列，这个区间才是符合条件的。

对于这种情况实现的话，考虑枚举右端点 $ r $，计算出最左边满足条件的 $ l $ ，来更新答案。满足条件怎么弄？第一个条件很好解决，开一个 map 就好了。第二个条件的话，需要维护每次移动右端点时会影响某些区间的极值，可以用两个单调栈分别维护 $ \max $ 和 $ \min $，在出栈时更新每个单调栈“划分”出的区间的极值就好了，明显能用线段树维护一下。但是还是不可做，将第二个条件参变分离一下得到：
$$
 \max_{i=l}^{r} a_i - \min_{i=l}^{r} a_i + l \le r + k 
$$
右边在枚举的时候都可以视作定值，而极值已经维护好了，只需在建线段树时附上初值 $ l $ 就好了，查询就是查询满足条件的第一个 $ l $，直接在线段树上维护线段树点值的最小值，分治一下即可，不会写的可以参考一下我的代码。总时间复杂度是均摊 $ O( n \log n ) $。

到了普遍情况，$ d \gt 1 $ 时，~~因为懒得思考新做法所以~~思考是否能转成特殊情况处理。发现只要将 $ a_i \leftarrow \lfloor \frac{a_i}{d} \rfloor $ 即可转为 $ d = 1 $ 的情况了，同时在做除法前要保证区间内所有的数在取模 $ d $ 的意义下同余，因为是等差数列嘛，不同于也就不等差了。呃呃，666 这样就做完了呢。

## 代码

没有刻意压行，自认为写的挺简单的捏。


```cpp
#include <iostream>
#include <unordered_map>
#define lc(x) (x<<1)
#define rc(x) (x<<1|1) 
using namespace std; const int N=2e5+5; unordered_map<int,int>mp;
int n,m,d,a[N],L,R,st[2][N],top[2],t[N<<2],tg[N<<2];
void push_up(int x){ t[x]=min(t[lc(x)],t[rc(x)]); }
void push_down(int x){ int &k=tg[x]; if(!k) return ; t[lc(x)]+=k,t[rc(x)]+=k,tg[lc(x)]+=k,tg[rc(x)]+=k,k=0; }
void build(int x,int l,int r){
	if(l==r) return t[x]=l,void(); int mid=l+r>>1;
	build(lc(x),l,mid),build(rc(x),mid+1,r),push_up(x);
}
void upd(int x,int l,int r,int u,int v,int k){
	if(l>v||r<u) return ; if(u<=l&&r<=v) return t[x]+=k,tg[x]+=k,void(); int mid=l+r>>1;
	push_down(x),upd(lc(x),l,mid,u,v,k),upd(rc(x),mid+1,r,u,v,k),push_up(x);
}
int ask(int x,int l,int r,int u,int v,int k){
	if(l>v||r<u||t[x]>k) return 0; if(l==r) return l; int mid=l+r>>1; push_down(x); 
	int y=ask(lc(x),l,mid,u,v,k); return y?y:ask(rc(x),mid+1,r,u,v,k);
}
int main(){
	scanf("%d%d%d",&n,&m,&d),L=R=1;
	for(int i=1;i<=n;i++) scanf("%d",a+i),a[i]+=1e9;
	if(d){ build(1,1,n);
		for(int i=1,j=0,lst=0;i<=n;i++){
			j=max(j,mp[a[i]]+1),mp[a[i]]=i; if(a[i]%d!=a[i-1]%d) j=i;
			for(;top[0]&&a[st[0][top[0]]]<a[i];top[0]--) upd(1,1,n,st[0][top[0]-1]+1,st[0][top[0]],-a[st[0][top[0]]]/d);
			for(;top[1]&&a[st[1][top[1]]]>a[i];top[1]--) upd(1,1,n,st[1][top[1]-1]+1,st[1][top[1]],a[st[1][top[1]]]/d);
			upd(1,1,n,st[0][top[0]]+1,i,a[i]/d),upd(1,1,n,st[1][top[1]]+1,i,-a[i]/d),st[0][++top[0]]=i,st[1][++top[1]]=i;
			int res=ask(1,1,n,j,i,m+i); if(res&&R-L<i-res) R=i,L=res;
		}
	}else
		for(int i=1,j=1;i<=n;i++){
			for(;a[i]^a[j];j++);
			if(R-L<i-j) R=i,L=j;
		}
	return !printf("%d %d",L,R);
}
```

---

## 作者：徐致远 (赞：4)

广告：[本蒟蒻的Blog](https://www.chnxuzhiyuan.cn/2019/03/14/%E3%80%8CZJOI%E6%A8%A1%E6%8B%9F%E8%B5%9B%E3%80%8DBug%E7%BA%A7%E7%9A%84%E5%AD%98%E5%9C%A8-Solution/)

### 题解
首先一个区间满足条件，必须要有整个区间内的$A_i$模$d$同余，并且没有相同元素，暂时先不考虑需要补上的数的个数。

考虑从左往右枚举右端点$head$，再用一个指针$tail$来控制合法的左端点所在区间，如果$[head,tail]$这个区间不合法，那么就让$tail++$，此时如果左端点$L$在$[head,tail]$区间内构成的所有区间$[L,head]$都合法。而且很显然当$head$变大时，$tail$单调不将。

然后对于左端点$L (L\in[tail,head])$，考虑需要补上的元素个数是否会超过$k$，推一下式子，移一下项，发现当满足以下式子时的左端点$L$就是合法的：

$\frac{\max_{i=L}^{R}{a_i}-\min_{i=L}^{R}{a_i}}{d}+L\leq R+k$

此时当右端点确定时，式子的右边也是确定的。也就是说，我们要找一个满足上式的且最靠左的左端点$L$。可以通过一些办法维护每个左端点$L$到当前枚举到的右端点区间内的最大值和最小值。

当右端点向右移动的时候，考虑维护两个单调栈，一个单调增，一个单调降，就拿单调增的来举例。由单调栈的性质可以得出，区间$[stack[top-1]+1,stack[top]]$内的每一个元素的值都大于$stack[top]$的值，所以当栈顶要被弹出时，将区间$[stack[top-1]+1,stack[top]]$内的每一个左端点的最小值都减去当前值与栈顶的差值。最大值同理。可以用线段树来维护。

然后就可以在线段树上二分来找满足条件的最靠左的左端点，如果当前遍历到的节点的左节点所管辖的区间内中有满足条件的节点就往左走，否则就往右走。
### 代码
```cpp
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=200005;const LL inf=0x3F3F3F3F3F3F3F3Fll;
int n,k,d,A[maxn],Area[maxn],num,hed,til,top1,stk1[maxn],top2,stk2[maxn],ans,ansL,ansR;map<int,int> H;
inline int read()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
struct SegmentTree
{
	struct Node{LL Mi,Ma,TagMi,TagMa,Val;}Tree[maxn*4];
	void PushUp(int rt)
	{
		Tree[rt].Mi=min(Tree[rt*2].Mi,Tree[rt*2+1].Mi);
		Tree[rt].Ma=max(Tree[rt*2].Ma,Tree[rt*2+1].Ma);
		Tree[rt].Val=min(Tree[rt*2].Val,Tree[rt*2+1].Val);
	}
	void PushDown(int rt)
	{
		Tree[rt*2].Mi+=Tree[rt].TagMi;Tree[rt*2].TagMi+=Tree[rt].TagMi;Tree[rt*2].Val-=Tree[rt].TagMi;
		Tree[rt*2].Ma+=Tree[rt].TagMa;Tree[rt*2].TagMa+=Tree[rt].TagMa;Tree[rt*2].Val+=Tree[rt].TagMa;
		Tree[rt*2+1].Mi+=Tree[rt].TagMi;Tree[rt*2+1].TagMi+=Tree[rt].TagMi;Tree[rt*2+1].Val-=Tree[rt].TagMi;
		Tree[rt*2+1].Ma+=Tree[rt].TagMa;Tree[rt*2+1].TagMa+=Tree[rt].TagMa;Tree[rt*2+1].Val+=Tree[rt].TagMa;
		Tree[rt].TagMi=Tree[rt].TagMa=0;
	}
	void RangeUpdateMin(int LL,int RR,int delta,int L=1,int R=n,int rt=1)
	{
		if(LL<=L&&R<=RR){Tree[rt].Mi+=delta;Tree[rt].TagMi+=delta;Tree[rt].Val-=delta;return;}
		PushDown(rt);
		int M=(L+R)/2;
		if(LL<=M) RangeUpdateMin(LL,RR,delta,L,M,rt*2);
		if(M<RR) RangeUpdateMin(LL,RR,delta,M+1,R,rt*2+1);
		PushUp(rt);
	}
	void RangeUpdateMax(int LL,int RR,int delta,int L=1,int R=n,int rt=1)
	{
		if(LL<=L&&R<=RR){Tree[rt].Ma+=delta;Tree[rt].TagMa+=delta;Tree[rt].Val+=delta;return;}
		PushDown(rt);
		int M=(L+R)/2;
		if(LL<=M) RangeUpdateMax(LL,RR,delta,L,M,rt*2);
		if(M<RR) RangeUpdateMax(LL,RR,delta,M+1,R,rt*2+1);
		PushUp(rt);
	}
	void Delete(int P,int L=1,int R=n,int rt=1)
	{
		if(L==P&&R==P){Tree[rt].Val=inf;return;}
		PushDown(rt);
		int M=(L+R)/2;
		if(P<=M) Delete(P,L,M,rt*2);
		if(M<P) Delete(P,M+1,R,rt*2+1);
		PushUp(rt);
	}
	void Build(int L=1,int R=n,int rt=1)
	{
		if(L==R){Tree[rt].Val=L;Tree[rt].Mi=Tree[rt].Ma=A[L];return;}
		int M=(L+R)/2;
		Build(L,M,rt*2);
		Build(M+1,R,rt*2+1);
		PushUp(rt);
	}
	LL Query(int num,int L=1,int R=n,int rt=1)
	{
		if(L==R) return L;
		int M=(L+R)/2;
		PushDown(rt);
		if(Tree[rt*2].Val<=num) return Query(num,L,M,rt*2);
		else return Query(num,M+1,R,rt*2+1);
	}
}T;
int main()
{
	n=read();k=read();d=read();
	for(int i=1;i<=n;i++) A[i]=read()+1000000000;
	if(!d)
	{
		for(int i=1,j;i<=n;)
		{
			j=i;
			while(j<n&&A[j+1]==A[i]) j++;
			if(j-i+1>ans){ans=j-i+1;ansL=i;ansR=j;}
			i=j+1;
		}
		printf("%d %d\n",ansL,ansR);
		return 0;
	}
	for(int i=1;i<=n;)
	{
		int j=i;Area[i]=i;
		while(j<n&&A[j+1]%d==A[i]%d){j++;Area[j]=i;}
		i=j+1;
	}
	til=1;T.Build();
	while(hed<n)
	{
		hed++;H[A[hed]]++;
		while(H[A[hed]]>1||Area[hed]!=Area[til]){T.Delete(til);H[A[til]]--;til++;}
		while(top1>0&&A[hed]<=A[stk1[top1]])
		{
			T.RangeUpdateMin(stk1[top1-1]+1,stk1[top1],A[hed]/d-A[stk1[top1]]/d);
			top1--;
		}
		stk1[++top1]=hed;
		while(top2>0&&A[hed]>=A[stk2[top2]])
		{
			T.RangeUpdateMax(stk2[top2-1]+1,stk2[top2],A[hed]/d-A[stk2[top2]]/d);
			top2--;
		}
		stk2[++top2]=hed;
		LL L=T.Query(hed+k);
		if(L>=til&&hed-L+1>ans){ans=hed-L+1;ansL=L;ansR=hed;}
	}
	printf("%d %d\n",ansL,ansR);
	return 0;
}
```

---

## 作者：CYJian (赞：4)

做这题的时候脑子很糊，不知道在想啥。。

![](https://cdn.luogu.com.cn/upload/image_hosting/dsaftktk.png)

---

首先先有一个大概的思路：

我们每次肯定是对于一段模 $d$ 同余的区间求答案，然后再取最大值。

那么这里就要特判一个地方：$d=0$.那么这个时候就是求最长的权值相同的区间。直接扫一遍就出来了。

然后继续考虑 $d>0$ 的情况：

我们注意到，满足要求的区间应该满足下面这个充要条件：

$$ \frac{max-min}{d} \leq R - L + 1 + k\ \ \ \ \text{且区间内无重复元素}$$

啥意思呢？

不考虑加入元素，构成一个等差数列的话，区间中 最大值 减去 最小值 除以 公差 就等于 区间长度。

但是考虑到可以加入 $k$ 个元素，所以我们可以认为是把区间长度扩充至 $R-L+1+k$，但是扩充的元素可能会变成最大值或者最小值，那么 最大值 减去 最小值 除以 公差 就有可能小于区间长度。那么就是上面那个不等式了。

但是我们发现，这个东西并不是特别好维护的。还需要一些技巧。

首先我们移个项：

$$ \frac{max-min}{d} + L - R - 1 \leq k $$

然后我们对于每一个位置，动态维护其作为区间左端点的上式左侧的值。

那么 $+L-1$ 就可以直接解决。 $-R$ 可以在移动右端点的时候整体 $-1$ 维护。

但是现在的问题是如何维护 最大值 和 最小值。

考虑使用单调栈：

我们分别维护一个 单调**递增** 的单调栈表示 最**小**值 和一个 单调**递减** 的单调栈表示 最**大**值。(注意别弄反了)

然后对于单调栈里头的元素，第 $i$ 个元素所管辖的最大/小值的区间是当前这个元素与上一个元素之间的 左开右闭 区间。那么入栈和出栈就可以用支持 区间加减 的线段树解决这个问题了。

再考虑对于一个右端点，怎么找到最靠左的合法左端点。

因为我们判断合法的条件是小于某一个阈值，所以可以通过维护区间最小值来判断区间内是否存在合法点。那么用询问的时候就可以在线段树上二分解决了。

最后还有一个问题：不能有重复元素。这个也很好解决，我们只需要将上个出现重复元素的地方以前的位置加上一个很大的数，就可以确保选出来的区间不会有重复元素了。

代码：

```cpp
#if By_CYJian
为什么 CYJian 那么菜啊...
#endif

#include <bits/stdc++.h>

using namespace std;

#define FILE(Name) freopen(Name"in", "r", stdin), freopen("out", "w", stdout)

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

template<typename T> inline void chkmax(T&a, T b) { a = a > b ? a : b; }
template<typename T> inline void chkmin(T&a, T b) { a = a < b ? a : b; }

typedef unsigned uit;
typedef long long ll;
typedef double db;

const int MAXN = 200100;

int n, k, d;
int a[MAXN];

int res = 1;
int res_l = 1;
int res_r = 1;

struct Segment_Tree {
#define ls (x << 1)
#define rs (x << 1 | 1)

	struct Node { ll v, t; } T[MAXN << 2];

	inline void pushup(int x) { T[x].v = min(T[ls].v, T[rs].v); }
	inline void pushdown(int x) {
		ll&t = T[x].t; if(!t) return ;
		T[ls].v += t, T[ls].t += t;
		T[rs].v += t, T[rs].t += t;
		t = 0;
	}

	inline void build(int x, int l, int r) {
		T[x].v = T[x].t = 0; if(l == r) return ;
		int mid = (l + r) >> 1; build(ls, l, mid), build(rs, mid + 1, r);
	}

	inline void Modify(int x, int l, int r, int L, int R, ll v) {
		if(L <= l && r <= R) return T[x].v += v, T[x].t += v, void();
		int mid = (l + r) >> 1; pushdown(x);
		if(L <= mid) Modify(ls, l, mid, L, R, v);
		if(mid < R) Modify(rs, mid + 1, r, L, R, v);
		pushup(x);
	}

	inline int Find(int x, int l, int r, int p) {
		if(l == r) return T[x].v <= k ? l : -1;
		int mid = (l + r) >> 1; pushdown(x);
		if(T[ls].v <= k) return Find(ls, l, mid, p);
		if(mid < p) return Find(rs, mid + 1, r, p);
		return -1;
	}

#undef ls
#undef rs
}seg;

int b[MAXN];
map<int, int>pos;
stack<int>up, down;

inline void solve(int l, int r) {
	for(int i = l; i <= r; i++) a[i - l + 1] = b[i] / d;
	int n = r - l + 1, las = 0; seg.build(1, 1, n), pos.clear();
	for(int i = 1; i <= n; i++) {
		int v = a[i];
		if(pos.count(v)) {
			seg.Modify(1, 1, n, las + 1, pos[v], 1000000000);
			las = pos[v];
		} pos[v] = i;
		seg.Modify(1, 1, n, 1, n, -1);
		seg.Modify(1, 1, n, i, i, i);
		while(up.top() && a[up.top()] > v) {
			int p = up.top(); up.pop();
			seg.Modify(1, 1, n, up.top() + 1, p, a[p]);
		} seg.Modify(1, 1, n, up.top() + 1, i, -v); up.push(i);
		while(down.top() && a[down.top()] < v) {
			int p = down.top(); down.pop();
			seg.Modify(1, 1, n, down.top() + 1, p, -a[p]);
		} seg.Modify(1, 1, n, down.top() + 1, i, v); down.push(i);
		int L = seg.Find(1, 1, n, i);
		if((~L) && res < i - L + 1) res = i - L + 1, res_l = L + l - 1, res_r = i + l - 1;
	} while(up.top()) up.pop(); while(down.top()) down.pop();
}

int main() {
	gi(n), gi(k), gi(d);
	if(d == 0) {
		int len = 1, now = -1, x = 0, pos = 0, L = 1, R = 1;
		for(int i = 1; i <= n; i++) {
			gi(x);
			if(x != now) {
				if(len < i - pos)
					len = i - pos, L = pos, R = i - 1;
				now = x, pos = i;
			}
		} if(len < n - pos + 1) L = pos, R = n;
		print(L), pc(' '), print(R), pc('\n');
		return 0;
	} int mi = 2147483647;
	for(int i = 1; i <= n; i++) gi(b[i]), chkmin(mi, b[i]);
	for(int i = 1; i <= n; i++) b[i] -= mi - 1;
	int las = b[1] % d, pos = 1;
	up.push(0), down.push(0);
	for(int i = 2; i <= n + 1; i++)
		if(las != b[i] % d || i == n + 1)
			solve(pos, i - 1), pos = i, las = b[i] % d;
	print(res_l), pc(' '), print(res_r), pc('\n');
	return 0;
}
```

---

## 作者：caoshurui (赞：2)

非常好的一道题，使我的思路旋转。

### 提示 1

可以思考什么样的区间可以组成一个公差为 $d$ 的等差数列。具体的，可以先假设可以添加任意个数；然后再思考满足前一个条件下还需要满足什么条件。

### 提示 2

一个合法的区间需要满足下面三个条件：
1. 区间内的数模 $d$ 的值相等（相当于把区间的值整体平移一个数）。
2. 区间内没有重复的数。
3. 设 $b_i = \lfloor \frac{a_i}{d} \rfloor$，当前区间为 $[l,r]$，则还需要满足 $0 \le \max\limits_{i = l}^{r} b_i - \min\limits_{i = l}^{r} b_i - (r - l) \le k$。

### 提示 3

思考怎么维护上面的信息。

第一个条件很好维护，可以把原数组分成若干个模数相同的块去处理。

对于第二个条件来说，假设当前我们从小到大枚举 $r$，设第 $i$ 个元素 $b_i$ 上一次出现的次数是 $p_i$，则一个合法的 $l$ 需要满足 $l > \max\limits_{i = l}^{r} p_i$。显然的，如果一个 $l \le p_i$，则它一定可以取到这个 $p_i$ 所对的 $i$，就一定会重复。因此这个条件是充要条件。结合上述内容，我们可以对每一个 $r$ 确定一个 $l$ 的左边界 $T$。

第三个条件因为已经保证了区间内不会出现重复的数，因此式子一定会大于等于零。接下来可以把式子转换成下面这样。

$$\max\limits_{i = l}^{r} b_i - \min\limits_{i = l}^{r} b_i + l \le r + k$$

其中 $\max\limits_{i = l}^{r} b_i - \min\limits_{i = l}^{r} b_i + l$ 可以使用某种数据结构来维护。因为 $r$ 是往右移的，因此可能需要实现区间取 $\min$ 和 $\max$ 了。不过先别急着写吉司机，容易发现在 $[T, r]$ 中的最大最小值是一段段连续的区间的，并且每次区间修改都会推平一部分区间。显然的，因为每次最多增加一个区间，且每个区间最多被推平一次，所以均摊是 $O(1)$ 的。这个区间很容易就可以想到用单调栈来维护，区间推平只需要用线段树维护区间加区间减就行了。

### 提示 4

不过还没有结束。现在的任务就是在 $[T, r]$ 内找到最左边的一个 $l$ 使得他的值 $\le r + k$。我们可以在线段树上维护出一个区间最小值，然后二分就行了。

因为你还需要实现区间查，所以直接这么做是 $\log^2$ 的。我们可以在每次移动 $T$ 的时候记录原先的值 $T'$，把 $[T', T-1]$ 赋值成 $\inf$。这样就可以树上直接二分，从而做到单 $\log$ 了。

### 提示 5


```cpp
#include <algorithm>
#include <iostream>
#include <map>
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define lop(i, x, y) for (int i = x; i >= y; i--)
#define int long long

using namespace std;

using pii = pair<int, int>;
using ll = long long;

const int MAXN = 2e5 + 5, inf = 1e18;

int n, k, d, L = 1, R = 1;
int a[MAXN], b[MAXN];

map<int, int> pos;

struct node {
  int v, id;
} mx[MAXN], mn[MAXN];

int top1, top2, T;

struct Sgt {
  struct Node {
    int l, r, v, tag;
  } a[MAXN << 2];
#define mid (l + r >> 1)
#define ls (rt << 1)
#define rs (rt << 1 | 1)

  void push_up(int rt) { a[rt].v = min(a[ls].v, a[rs].v); }
  void addtag(int rt, int v) { a[rt].v += v, a[rt].tag += v; }
  void push_down(int rt) { addtag(ls, a[rt].tag), addtag(rs, a[rt].tag), a[rt].tag = 0; }

  void build(int rt, int l, int r) {
    a[rt] = {l, r, inf, 0};
    if (l == r) return a[rt].v = l, void();
    build(ls, l, mid), build(rs, mid + 1, r);
  }

  void update(int rt, int L, int R, int v) {
    int l = a[rt].l, r = a[rt].r;
    if (L <= l && r <= R) return addtag(rt, v);
    push_down(rt);
    if (L <= mid) update(ls, L, R, v);
    if (mid < R) update(rs, L, R, v);
    push_up(rt);
  }

  int query(int rt, int v) {
    int l = a[rt].l, r = a[rt].r;
    if (l == r) return a[rt].v <= v ? l : 0;
    push_down(rt);
    return query(a[ls].v <= v ? ls : rs, v);
  }
} tree;

signed main() {
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> k >> d;
  rep(i, 1, n) cin >> a[i];

  if (d == 0) {
    int ans = 0, cnt = 0;
    rep(i, 1, n) {
      if (a[i] != a[i - 1]) cnt = 0;
      cnt++;
      if (R - L + 1 < cnt) R = i, L = i - cnt + 1;
    }
    cout << L << ' ' << R;
    exit(0);
  }

  rep(i, 1, n) b[i] = a[i] / d;
  tree.build(1, 1, n);

  rep(i, 1, n) {
    int _T = max(1ll, T);
    if ((a[i] % d + d) % d == (a[i - 1] % d + d) % d) {
      T = max(T, pos[a[i]] + 1);
    } else {
      T = i, top1 = top2 = 0;
    }
    if (_T < T) tree.update(1, _T, T - 1, inf);

    mx[0].id = mn[0].id = T - 1;

    for (; top1 && mx[top1].v <= b[i]; top1--) {
      int l = mx[top1 - 1].id + 1, r = mx[top1].id;
      if (l <= r) tree.update(1, l, r, b[i] - mx[top1].v);
    }
    for (; top2 && mn[top2].v >= b[i]; top2--) {
      int l = mn[top2 - 1].id + 1, r = mn[top2].id;
      if (l <= r) tree.update(1, l, r, mn[top2].v - b[i]);
    }
    mx[++top1] = mn[++top2] = {b[i], i};

    int ansl = tree.query(1, i + k);
    if (ansl && i - ansl > R - L) R = i, L = ansl;
    pos[a[i]] = i;
  }
  cout << L << ' ' << R;
  return 0;
}

```

### 总结

挺好的一道题，每一步都挺有意思的。不过我还是搞不明白为什么黑哥说这道题要用到扫描线……

---

## 作者：wangyibo201026 (赞：2)

## solution

我是大糖丸。

首先你发现可以将 $x$ 转化为 $\lfloor \frac{x}{d} \rfloor$，然后 $d$ 就变成 $1$ 了，当然如果原本 $d = 0$ 你可以特判处理一下。

于是我们发现一个区间需要增加的数其实是 $\max a_i - \min a_i - ( r - l )$ 个的，然后我们考虑怎么做。

我们将式子列出来：

$$ \max a_i - \min a_i - ( r - l ) \le k$$

然后转化一下：

$$ \max a_i - \min a_i + l \le k + r$$

于是我们从左到右扫描 $r$，维护一个单调递增的单调栈用于求 $\min$，维护一个单调递减的单调栈用于求 $\max$，每次我们单调栈剔除结点时，我们将其一段区间全部撤销操作。然后 $+ l$ 我们每扫一次然后将当前位置加上就行（相当于是你 $ + \max$ 的贡献和 $- \min$ 的贡献拆开来算，不懂可以看代码）。

于是你对于每个 $r$，都可以在线段树上二分到一个最远的满足条件的 $l$ 了。

## code

代码里我懒写的双 $\log$：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e5 + 5;

int n, k, d;
int a[N], p[N], q[N];
map < int, int > tong;

int tree[N << 2], tag[N << 2];

void pushup ( int node ) {
  tree[node] = min ( tree[node << 1], tree[node << 1 | 1] );
}

void addtag ( int node, int k ) {
  tree[node] += k;
  tag[node] += k;
}

void pushdown ( int node ) {
  if ( !tag[node] ) {
    return ;
  }
  addtag ( node << 1, tag[node] ), addtag ( node << 1 | 1, tag[node] );
  tag[node] = 0;
}

void update ( int node, int lt, int rt, int x, int y, int k ) {
  if ( y < lt || x > rt ) {
    return ;
  }
  if ( x <= lt && rt <= y ) {
    addtag ( node, k );
    return ;
  }
  pushdown ( node );
  int mid = lt + rt >> 1;
  update ( node << 1, lt, mid, x, y, k ), update ( node << 1 | 1, mid + 1, rt, x, y, k );
  pushup ( node );
}

int query ( int node, int lt, int rt, int x, int y ) {
  if ( y < lt || x > rt ) {
    return 0x3f3f3f3f3f3f3f3f;
  }
  if ( x <= lt && rt <= y ) {
    return tree[node];
  }
  pushdown ( node );
  int mid = lt + rt >> 1;
  return min ( query ( node << 1, lt, mid, x, y ), query ( node << 1 | 1, mid + 1, rt, x, y ) );
}

stack < pii > stk1, stk2;

void Solve () {
  cin >> n >> k >> d;
  for ( int i = 1; i <= n; i ++ ) {
    cin >> a[i];
  }
  if ( !d ) {
    if ( d == 0 ) {
      int ans = 0, lst = 1, posl = 1, posr = 1;
      for ( int i = 1; i <= n; i ++ ) {
        if ( a[i] != a[lst] ) {
          if ( ans < i - lst ) {
            ans = max ( ans, i - lst );
            posl = lst, posr = i - 1;
          }
          lst = i;
        }
      }
      cout << posl << " " << posr;
    }
  }
  else {
    int l = 1;
    for ( int i = 1; i <= n; i ++ ) {
      while ( l + 1 <= n && ( a[l] % d + d ) % d != ( a[i] % d + d ) % d ) {
        l ++;
      }
      q[i] = l;
    }
    l = 1;
    for ( int i = 1; i <= n; i ++ ) {
      tong[a[i]] ++;
      while ( l + 1 <= n && tong[a[i]] > 1 ) {
        tong[a[l]] --;
        l ++;
      }
      p[i] = max ( l, q[i] );
    }
    for ( int i = 1; i <= n; i ++ ) {
      a[i] = a[i] / d;
    }
    int ans = 0, posl = 0, posr = 0;
    stk1.push ( { -0x3f3f3f3f3f3f3f3f, 0 } ), stk2.push ( { 0x3f3f3f3f3f3f3f3f, 0 } );
    for ( int i = 1; i <= n; i ++ ) {
      while ( !stk1.empty () && stk1.top ().first >= a[i] ) {
        int r = stk1.top ().second, val = stk1.top ().first;
        stk1.pop ();
        int l = stk1.top ().second + 1;
        update ( 1, 1, n, l, r, val );
      }
      while ( !stk2.empty () && stk2.top ().first <= a[i] ) {
        int r = stk2.top ().second, val = stk2.top ().first;
        stk2.pop ();
        int l = stk2.top ().second + 1;
        update ( 1, 1, n, l, r, -val );
      }
      update ( 1, 1, n, stk1.top ().second + 1, i, -a[i] );
      update ( 1, 1, n, stk2.top ().second + 1, i, a[i] );
      stk1.push ( { a[i], i } ), stk2.push ( { a[i], i } );
      update ( 1, 1, n, i, i, i );
      int l = p[i] - 1, r = i + 1;
      while ( l + 1 < r ) {
        int mid = l + r >> 1;
        if ( query ( 1, 1, n, p[i], mid ) <= k + i ) {
          r = mid;
        }
        else {
          l = mid;
        }
      }
      if ( i - r + 1 > ans ) {
        ans = i - r + 1, posl = r, posr = i;
      }
      else if ( i - r + 1 == ans && posl > r ) {
        posl = r, posr = i;
      }
      // for ( int j = 1; j <= n; j ++ ) {
      //   cout << query ( 1, 1, n, j, j ) << " ";
      // }
      // cout << '\n';
    }
    cout << posl << " " << posr;
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

---

## 作者：acb437 (赞：2)

# 题解：[CF407E k-d-sequence](https://www.luogu.com.cn/problem/CF407E)

## 思路简述
观察题目要求，可以发现对于一个完整的，项数为 $len$ 的，公差为 $d$ 的等差数列，它的形式为： $b_1, b_2=b_1+d, b_3=b_1+2 \times d, \dots, b_{len}=b_1+ len \times d$。

可以发现这个形式和同余式相似，也就是说，对于一个公差为 $d$ 的等差数列，它满足 $b_i \equiv b_1 \pmod d$。这一条件显然是题目所求子区间的必要条件。

发现上述条件显然并不充分，因为满足这一条件的数列排序后可能并不连续，这时就需要将题目所给的 $k$ 个数插入空位中。当空位数不多于 $k$ 时，题目所求条件才可能被满足。一个完整的等差数列的项数应该是 $(\text{末项}-\text{首项}) \div d+1$，对于未排序的子区间首项就是子区间中最小的数，末项就是子区间中最大的数。那么空位的数量就是项数减去区间长度。

此时似乎已经完备了，但实际上还漏了一个条件——不重不漏，我们只考虑了不漏。当 $d \neq 0$ 时，等差数列中是没有相等的数的。若是 $d=0$，特判掉，用双指针找到最长的相等的一段即可。如此，我们就得到了题目所求子区间的充要条件：
1. 其中每一项满足 $b_i \equiv b_1 \pmod d$。
2. $(b_{max}-b_{min}) \div d+1 \le r-l+1+k$，具体实现中，可以直接用 $c_i=b_i \div d$ 来比较，也就是 $c_{max}-c_{min} \le r-l+k$。
3. 当 $d \neq 0$ 时，有 $\forall 1 \le i,j \le len \land i \neq j,b_i \neq b_j$。可以用 map 维护每个数上一次出现的位置以确定范围。

考虑到求的是最长子区间，又有上述条件，可以使用双指针、扫描线来处理。从 $1\sim n$ 枚举右端点，设当前右端点为 $r$，其左端点显然在一区间 $[L,r]$ 中，$L$ 可以直接用条件1、3约束，在扫描过程中可以直接更新。因此条件2就成为了主要考虑的方向。

在约束2中，$r$ 和 $k$ 是与要找的最左可行 $l$无关的条件，将其归至一侧，得到 $c_{\max}-c_{\min}+l \le r+k$，其中，$c_{\max}$、$c_{\min}$ 都是以当前枚举的 $r$ 为右端点的后缀，在确定 $r$ 的情况下，这三项都只与每一个可能的 $l$ 相关，考虑用线段树维护这个式子。

对于一段后缀的 $\max$ 和 $\min$，可以用单调栈维护，这是因为对于每一个 $\max/ \min$，它一定是前一个比它更大/更小的数所在位置到 $r$ 的区间内最大/最小的，而在它之前的比它更小/更大的数一定不会成为任何一段区间的 $\max/\min$。

如此，便可以维护每一个位置的 $\max$ 和 $\min$ 了。更新线段树时，只要把单调栈中被出栈的段的信息更新为新的信息即可。而查询时则通过线段树上二分，找到最靠左的，满足 $c_{\max}-c_{\min}+l \le r+k$ 的位置作为左端点即可。时间复杂度 $O(n\log_2n)$。

## 代码
```cpp
#include <cstdio>
#include <iostream>
#include <map>
#define INF 1e9
#define N 200005
#define lc(u) u << 1
#define rc(u) u << 1 | 1
using namespace std;
int n, k, d, a[N];
int ansl = 1, ansr;
map <int, int> lst;
int top1, top2, stk1[N], stk2[N];

struct node
{
	int l, r;
	int val, add;
}tr[N << 2];
void flash(int u, int add){tr[u].val += add, tr[u].add += add;}
void pushup(int u){tr[u].val = min(tr[lc(u)].val, tr[rc(u)].val);}
void pushdown(int u)
{
	if(!tr[u].add)return;
	flash(lc(u), tr[u].add);
	flash(rc(u), tr[u].add);
	tr[u].add = 0;
}
void build(int u, int l, int r)
{
	tr[u].l = l, tr[u].r = r;
	if(l == r)return void(tr[u].val = l);
	int m = (l + r) >> 1;
	build(lc(u), l, m), build(rc(u), m + 1, r);
	pushup(u);
}
void modify(int u, int l, int r, int add)
{
	if(l <= tr[u].l && tr[u].r <= r)return flash(u, add);
	int m = (tr[u].l + tr[u].r) >> 1;pushdown(u);
	if(l <= m)modify(lc(u), l, r, add);
	if(m < r)modify(rc(u), l, r, add);
	pushup(u);
}
int query(int u, int l, int r, int val)
{
	if(tr[u].val > val)return -1;
	if(tr[u].l == tr[u].r)return tr[u].l;
	int res = -1, m = (tr[u].l + tr[u].r) >> 1;pushdown(u);
	if(l <= m)res = query(lc(u), l, r, val);
	if(m < r && res == -1)res = query(rc(u), l, r, val);
	return res;
}

int main()
{
	scanf("%d%d%d", &n, &k, &d);
	for(int i = 1;i <= n;i++)scanf("%d", &a[i]), a[i] += INF;build(1, 1, n);
	if(!d)
	{
		for(int r = 1, l = 1;r <= n;r++)
		{
			if(a[r] != a[l])l = r;
			if(r - l > ansr - ansl)ansl = l, ansr = r;
		}
		printf("%d %d\n", ansl, ansr);
		return 0;
	}
	for(int i = 1, l = 1;i <= n;i++)
	{
		if(a[i] % d != a[i - 1] % d)l = i;
		l = max(l, lst[a[i]] + 1), lst[a[i]] = i;
		while(top1 && a[stk1[top1]] > a[i])top1--, modify(1, stk1[top1] + 1, stk1[top1 + 1], a[stk1[top1 + 1]] / d - a[i] / d);stk1[++top1] = i;
		while(top2 && a[stk2[top2]] < a[i])top2--, modify(1, stk2[top2] + 1, stk2[top2 + 1], a[i] / d - a[stk2[top2 + 1]] / d);stk2[++top2] = i;
		int resl = query(1, l, i, k + i);
		if(i - resl > ansr - ansl)ansl = resl, ansr = i;
	}
	printf("%d %d\n", ansl, ansr);
	return 0;
}
```

---

## 作者：PhantasmDragon (赞：2)

先特判掉 $d=0$ 的情况

显然如果一段连续的数里面 $\%d$ 的值不唯一，那这个区间无论如何也无法被填成等差数列。

那么考虑将 $\%d$  的值相同的数放在一起讨论。我们只会考虑连续一段 $\%d$ 相同的数。

先将所有数加成正数，然后除以 $d$，把 $d$ 转化为1处理。

首先发现，一个区间 $[l,r]$ 是合法的，当且仅当：

1. 区间内无相同的数字
2. $\max[l,r]-min[l,r]-(r-l) \leq m$

条件1很显然，条件2的意思就是这个区间代表的值域长度为 $max[l,r]-min[l,r]+1$， 我们需要把中间的空缺补满，而我们现在值域中已经有了 $r-l+1$ 个数字，所以我们需要填的数字个数就是两者之差。那么根据题意，只要不超过 $m$ 即可。

现在，只考虑一段连续的 $\%d$ 相同的数，其长度为 $len$.

对于一段数字，我们要统计满足以上两个条件的，并且长度最长的区间，显然可以很套路地从大到小枚举左端点，对于每个左端点找到满足条件的最大的右端点。

首先，先对每个位置找以它为左端点，极大的一个右端点使得它们之间没有重复数字，记为 $rpos_i$

当 $l$ 固定的时候，可以把条件2写成 $\max[l,r]-min[l,r]- r \leq m + l$。 这样就可以用线段树去维护 $\max[l,r]-min[l,r]- r$, 对于每个 $l$ 在进行线段树二分，找到满足维护的值 $\leq m+l$ 的最大的 $r$.

考虑如何用线段树去维护这个值。 当 $l$ 左移的时候，可以开两个单调栈，维护从 $l$ 到 $len$ 的一个单调递减和一个单调递增的数列。 

在单调递增的栈里，每当加入一个数 $x$ 的时候，我们会pop掉比它小的数。 那么对于每个pop掉的数 $v$，它原来管辖的区间(它到栈中下一个位置之间的所有右端点)的最大值本来是它，但是现在 $x$ 把它替代掉了，那么对于这个数管辖的区间，我们维护的值就会增加 $x-v$，在线段树上进行区间加即可。 单调递减的栈同理。

再考虑不重复的限制。 在讨论的左端点为 $l$ 时，可以强制把线段树上 $[rpos_l+1,len]$ 这个区间加成无穷大，这样线段树二分时就不可能找到 $rpos_l$ 后面的位置。

这样，处理一段连续的数的复杂度便是 $O(Len* log\ Len)$ 的，我们处理的所有连续区间显然是没有交的，所以总复杂度就是 $O(nlogn)$ 的。

------

贴上代码

```
#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<map>
#define ll long long
#define ls (p<<1)
#define rs (p<<1|1)
#define maxn 200005
using namespace std;
int n,m,k,a[maxn];
ll val[maxn<<2],lz[maxn<<2];
map<int,int> mp; int tot;
vector<int> vec[maxn];
void Putdown(int p)
{
	if(lz[p])
	{
		val[ls]+=lz[p],lz[ls]+=lz[p];
		val[rs]+=lz[p],lz[rs]+=lz[p];
		lz[p]=0;
	}
}
void Add(int p,int l,int r,int x,int y,ll v)
{
	if(x<=l&&r<=y) return (void)(val[p]+=v,lz[p]+=v);
	Putdown(p);
	int mid=(l+r)>>1;
	if(x<=mid&&y>=l) Add(ls,l,mid,x,y,v);
	if(y>mid&&x<=r) Add(rs,mid+1,r,x,y,v);
	val[p]=min(val[ls],val[rs]);
}
int Query(int p,int l,int r,int d)
{
	if(l==r) return l;
	Putdown(p);
	int mid=(l+r)>>1;
	if(val[rs]<=d) return Query(rs,mid+1,r,d);
	return Query(ls,l,mid,d);
}
void Init(int p,int l,int r)
{
	lz[p]=0;
	if(l==r) return (void)(val[p]=-l);
	int mid=(l+r)>>1;
	Init(ls,l,mid),Init(rs,mid+1,r);
	val[p]=min(val[ls],val[rs]);
}
stack<int> sinc,sdec;
map<int,int> vis;
int rpos[maxn]; int ansl=1,ansr=0;
void GetAns(int l,int r)
{
	int L=r-l+1;
	Init(1,1,L);	
	vis.clear(),rpos[r]=r;
	vis[a[r]]=r;
	for(int i=r-1;i>=l;i--)
	{
		rpos[i]=min(rpos[i+1],(vis.find(a[i])==vis.end()?r:vis[a[i]]-1));
		vis[a[i]]=i;
	}
	for(int i=r;i>=l;i--)
	{
		while(sinc.size()&&a[sinc.top()]<=a[i])
		{
			int nw=sinc.top(); sinc.pop();
			Add(1,1,L,nw-l+1,(sinc.size()?sinc.top():r+1)-l,-a[nw]);
		}
		while(sdec.size()&&a[sdec.top()]>=a[i])
		{
			int nw=sdec.top(); sdec.pop();
			Add(1,1,L,nw-l+1,(sdec.size()?sdec.top():r+1)-l,a[nw]);
		}
		Add(1,1,L,i-l+1,(sinc.size()?sinc.top():r+1)-l,a[i]);
		Add(1,1,L,i-l+1,(sdec.size()?sdec.top():r+1)-l,-a[i]);
		
		if(rpos[i]!=r) Add(1,1,L,rpos[i]-l+2,r-l+1,2e9);
		if(i!=l) Add(1,1,L,1,i-l,2e9);
		
		int rp=Query(1,1,L,m-(i-l+1))+l-1;
		if(rp-i>ansr-ansl) ansr=rp,ansl=i;
		else if(rp-i==ansr-ansl&&ansl>i) ansr=rp,ansl=i;
		
		if(rpos[i]!=r) Add(1,1,L,rpos[i]-l+2,r-l+1,-2e9);
		if(i!=l) Add(1,1,L,1,i-l,-2e9);
		
		sinc.push(i),sdec.push(i);
	}
	while(sinc.size()) sinc.pop();
	while(sdec.size()) sdec.pop();
}
void Solve(int id)
{
	int pre=vec[id][0];
	for(int i=1;i<vec[id].size();i++)
		if(vec[id][i-1]+1!=vec[id][i]) GetAns(pre,vec[id][i-1]),pre=vec[id][i];
	GetAns(pre,vec[id][vec[id].size()-1]);
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]+=1e9;
	if(k==0)
	{
		for(int i=1;i<=n;i++)
		{
			int tl=i;
			while(a[i]==a[i+1]) i++;
			if(i-tl>ansr-ansl) ansl=tl,ansr=i;
		}
		printf("%d %d\n",ansl,ansr);
		return 0;
	}
	for(int i=1;i<=n;vec[mp[a[i]%k]].push_back(i),i++)
		if(mp.find(a[i]%k)==mp.end()) mp[a[i]%k]=++tot;
	for(int i=1;i<=n;i++) a[i]/=k;
	for(int i=1;i<=tot;i++) Solve(i);
	printf("%d %d\n",ansl,ansr);
	return 0;
}
```



---

## 作者：Defy_HeavenS (赞：1)

这是一个重要的模型，好好整理了一下。

## [Problem - 407E - Codeforces](https://codeforces.com/problemset/problem/407/E)

### 题面

给定一个长度为 $n$ 的序列 $a$，求这个序列的一个最长子串，满足在这个子串内插入最多 $k$ 个数，排序后形成一个公差为 $d$ 的等差数列。

### 题解

一个显而易见的性质：在一个公差为 $d$ 的等差数列中，任意两个元素**除以 $d$ 的余数相同**。由于 $d$ 固定，所以先把序列 $a$ 分成若干个**极大子串**，使得每一个子串内的数除以 $d$ 的余数相同。这样，答案的左右端点一定是在**同一个子串**内的，保证了不同的子串之间互不影响。

考虑怎么计算一段区间 $\{a_l,a_{l+1},\dots,a_r\}$ 需要插入的数的个数：

- 若这段区间内有**相同的数**，那么一定不能组成一个公差 $>0$ 的等差数列（$d=0$ 一会我们要特判掉）。实现上，用 $map$ 做即可；
- 否则，先做一个**归一化**，对于一个子串 $b$，其元素除以 $d$ 的余数为 $c$，那么使 $b_i\gets \frac{b_i-c}{d}$。这样操作后，需要插入的数的个数就是 $(\max_{i=l}^{r}a_i-\min_{i=l}^{r}a_i+1)-(r-l+1)$。

单独拎一个子串 $b$ 出来。枚举子串右端点 $r$，我们要求的就是一个**下标最小**的左端点 $l$，满足区间 $\{a_l,a_{l+1},\dots,a_r\}$ 需要插入的数的个数 $\le k$，即 $(\max_{i=l}^{r}a_i-\min_{i=l}^{r}a_i+1)-(r-l+1)\le k$。整理一下，把未知放一边，已知放一边，$\max_{i=l}^{r}a_i-\min_{i=l}^{r}a_i+l\le k+r$。

设 $w_l=\max_{i=l}^{r}a_i-\min_{i=l}^{r}a_i+l$，考虑在 $r$ 变化时维护 $w$。这里考虑用[[单调栈&单调队列#单调栈|单调栈]]和[[线段树]]的组合，单调栈用于维护最大值最小值，线段树用于优化 $w$ 的修改。用一个递减的单调栈维护最大值，一个递增的单调栈维护最小值。这两个栈维护起来差不多，无非就是大于小于和加法减法的区别，以**递减的维护最大值**为例子。

当原来的 $r'$ 往后移成 $r$，就相当于插入一个 $a_r$（前面说，限制在子串 $b$ 内，但实现时需要判断一下是否是子串的分界，更新一下所在子串的左边界。同时，你可以在线段树上把上一个子串的 $w$ 情况，但不清空也不影响）。单调栈中为了维护单调性，需要弹出小于 $a_r$ 的栈顶元素，弹出**前**需要把以栈顶为最大值的区间的 $w$ 去掉栈顶所贡献的最大值。最后弹完了，插入 $a_r$，再把以 $a_r$ 为最大值的区间的 $w$ 加上 $a_r$ 所贡献的最大值。最小值同理，但是要注意，因为维护的是 $\max_{i=l}^{r}a_i-\min_{i=l}^{r}a_i+l$，所以最大值去掉贡献是减，加上贡献是加；而最小值去掉贡献是加，加上贡献是减。

最后找到下标最小的 $l$，使 $w_l\le k+r$。这里就是在，所在子串的左端点到枚举的 $r$ 这段区间内，找到第一个 $w_l\le k+r$ 的 $l$，这个用线段树做。首先将要操作的区间分成 $\log n$ 个线段树上的节点，然后从左边向右边找到第一个，这个节点所待表的区间内 $w$ 最大值小于等于 $k+r$ 的，然后在这个节点所待表的区间内找第一个满足条件的位置，那就是要找的 $l$。

一种特殊情况，$d=0$，直接找最长的一段子串，满足子串内的数都相等。

### 代码

```cpp
#include<bits/stdc++.h>
#define umap unordered_map
#define uset unordered_set
#define mset multiset
#define yes cout<<"Yes\n"
#define no cout<<"No\n"
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define tmax(a,b) (a)=max((a),(b))
#define tmin(a,b) (a)=min((a),(b))

using namespace std;
typedef long long LL;
typedef pair<int,int> PII;

const int N=2e5+5,Inf=1e9+7;
int n,k,d,a[N],ansl,ansr,flag,ans;
map<int,int>last;
deque<int>L,R;
struct SegNode{
	int w,tag;
}tr[N<<2];

#define lc (rt<<1)
#define rc (rt<<1|1)
void pushup(int rt){
	tr[rt].w=min(tr[lc].w,tr[rc].w);
}
void pushdown(int rt){
	if(tr[rt].tag){
		tr[lc].tag+=tr[rt].tag;
		tr[rc].tag+=tr[rt].tag;
		tr[lc].w+=tr[rt].tag;
		tr[rc].w+=tr[rt].tag;
		tr[rt].tag=0;
	}
}
void build(int rt,int L,int R){
	if(L==R){
		tr[rt].w=L;
		return;
	}
	int mid=L+R>>1;
	build(lc,L,mid),build(rc,mid+1,R);
	pushup(rt);
}
void update(int rt,int l,int r,int L,int R,int val){
	if(l>=L&&r<=R){
		tr[rt].tag+=val;
		tr[rt].w+=val;
		return;
	}
	pushdown(rt);
	int mid=l+r>>1;
	if(R<=mid){
		update(lc,l,mid,L,R,val);
	}else if(L>mid){
		update(rc,mid+1,r,L,R,val);
	}else{
		update(lc,l,mid,L,mid,val);
		update(rc,mid+1,r,mid+1,R,val);
	}
	pushup(rt);
}
int get_pos(int rt,int l,int r,int val){
	if(l==r){
		return l;
	}
	pushdown(rt);
	int mid=l+r>>1;
	if(tr[lc].w<=val){
		return get_pos(lc,l,mid,val);
	}else{
		return get_pos(rc,mid+1,r,val);
	}
}
void query(int rt,int l,int r,int L,int R,int val){
	if(l>=L&&r<=R){
		if(tr[rt].w<=val){
			flag=1,ans=get_pos(rt,l,r,val);
		}
		return;
	}
	pushdown(rt);
	int mid=l+r>>1;
	if(R<=mid){
		query(lc,l,mid,L,R,val);
	}else if(L>mid){
		query(rc,mid+1,r,L,R,val);
	}else{
		query(lc,l,mid,L,mid,val);
		if(!flag) query(rc,mid+1,r,mid+1,R,val);
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	ansl=ansr=1;
	cin>>n>>k>>d;
	for(int i=1,ma=-1;i<=n;i++){
		cin>>a[i];
		a[i]+=Inf;
	}
	if(!d){
		for(int r=1,l;r<=n;r++){
			l=r;
			while(r<n&&a[r]==a[r+1]){
				r++;
			}
			if(ansr-ansl<r-l){
				ansl=l,ansr=r;
			}
		}
		cout<<ansl<<" "<<ansr<<"\n";
		return 0;
	}
	build(1,1,n);
	for(int r=1,l=1,lastl;r<=n;r++){
		lastl=l;
		if(a[r]%d==a[r-1]%d){
			tmax(l,last[a[r]]+1);
		}else{
			l=r;
		}
		last[a[r]]=r;
		//MIN
		while(L.size()&&L.front()<l){
			L.pop_front();
		}
		while(L.size()&&a[L.back()]>=a[r]){
			int val=L.back();
			L.pop_back();
			update(1,1,n,max(l,(L.size()?L.back():0)+1),val,a[val]/d);
		}
		update(1,1,n,max(l,(L.size()?L.back():0)+1),r,-a[r]/d);
		L.pb(r);
		//MAX
		while(R.size()&&R.front()<l){
			R.pop_front();
		}
		while(R.size()&&a[R.back()]<=a[r]){
			int val=R.back();
			R.pop_back();
			update(1,1,n,max(l,(R.size()?R.back():0)+1),val,-a[val]/d);
		}
		update(1,1,n,max(l,(R.size()?R.back():0)+1),r,a[r]/d);
		R.pb(r);
		flag=ans=0;
		query(1,1,n,l,r,k+r);
		if(ansr-ansl<r-ans){
			ansl=ans,ansr=r;
		}
	}
	cout<<ansl<<" "<<ansr;
	return 0;
}
```

---

## 作者：wptt (赞：1)

[让人作呕的阅读体验](https://www.xn--6fr34mpqi8zd.top/post/shu-ju-jie-gou-za-ti/)

首先特判 $d=0$ 的情况，然后继续分析。

考虑如何确定一个区间是否合法：

- 满足这个区间没有重复的数。
- 这个区间所有的数都关于 $d$ 同余。
- $\dfrac{\max-\min}{d}+l-r\le k$。

套路的考虑枚举有端点，计算 $l$ 的最小值。

对于第一个要求直接开一个桶就行了，对于第二个要求也可以直接维护出来，比较有难度的其实是如何维护第 $3$ 个要求。

因为 $r$ 是固定的，我们把 $r$ 移过去得到：

$$\begin{aligned}
\dfrac{\max-\min}{d} +l\le k+r
\end{aligned}$$

因为除 $d$ 很难维护，不妨整体乘上去，得到：

$$\begin{aligned}
\max-\min +l\times d\le d\times (k+r)
\end{aligned}$$

考虑写一个扫描线，显然对于 $l+d$ 直接在线段树里赋值就行了。

对于 $\min$ 和 $\max$ 的处理也是比较套路的。

考虑维护两个单调栈，那么如果 $r\gets r+1$ 时就把 $a_{r}$ 加入栈中，把栈中从上到小数第二个元素（第一个是 $a_{r}$）到 $r$ 的 $\min$ 和 $\max$ 都分别改了就行了。

处理之后直接在线段树上二分找最小的 $l$ 就行了。

这里有一些细节，笔者写的时候脑子是瓦特的所以没有注意。

首先，不需要维护 $\min$ 和 $\max$ 的具体值的，直接区间加或者区间减就行了。

其次，对于线段树上二分被 $1,2$ 限制所拒绝的点直接赋 $+\infty$ 就行了，因为这个位置显然是单调的。

最后，不建树可以跑到第 $11$ 个点，别问笔者怎么知道的。

时间复杂度为 $O(n\log n)$。

[Submission #309348907 - Codeforces](https://codeforces.com/problemset/submission/407/309348907)

---

## 作者：ast123 (赞：1)

### Part 1 推式子？
根据题目描述，不难发现一个子区间 $[l,r]$ 满足题目的要求当且仅当
1. $a_l,a_{l+1},\dots,a_r$ 对模 $d$ 同余；
2. $a_l,a_{l+1},\dots,a_r$ 两两不同；
3. 需要加入的数字不大于 $k$ 个，即

$$
\frac{\max_{i=l}^{r}a_i - \min_{i=l}^{r}}{d} \le r - l + 1 + k
$$

对于条件 1，可以顺序遍历数组，计算 $a_i$ 对模 $d$ 的结果，并判断是否与 $a_{i-1}$ 属于同一个同余的区间；对于条件 2，处理出每个值的最后一个值 $lst_{a_{i}}$，这可以用 map 实现；对于条件 3，需要对式子进行一些变形。对每一个 $a_i \to \lfloor \frac{a_i}{d} \rfloor$，得  
$$
\max_{i=l}^{r}a_i - \min_{i=l}^{r}a_i + l \le k+r
$$
### Part 2 代码实现

对于等号左边的东西，我们用一颗线段树维护一下，将 $r$ 从 1 到 $n$ 遍历，求值的时候在线段树上二分一下，但是修改可能有点麻烦：需要先找到当前区间内离 $r$ 最近的满足 $a_i > a_r$ 的 $i$，然后将区间 $[i+1,r]$ 减去原来的答案，然后加上 $a_i$。最小值同理。我们发现，这很像一个单调栈做的事情，下面只讨论维护最近满足 $a_i > a_r$ 的 $i$ 的单调递减栈。当栈顶的 $a_{st_{top}} \le a_i$ 时，栈顶元素出栈，并对 $a_{st_{top}}$ 修改的区间减去 $a_{st_{top}}$。对于当前的 $a_{st_{top}}$，若它没有使别的元素弹出，那么 $st_{top-1} = st_{top}-1$，它修改的区间为 $[st_{top}, st_{top}]=[st_{top-1}+1, st_{top}]$。若它使别的元素弹出了，则 $st_{top-1}$ 之后的元素修改的区间都被它修改过了，同上。单调递增栈同理。注意：
1. 根据公式，单调递增栈的贡献是负的，入栈时要减去贡献，出栈时要加回去。
2. $a_i$ 可能是负数，我是把 $a_i$ 全部加上 $10^9$。
3. 特判 $k=0$ 的情况。相当于求最长的一段元素值相同的子区间。
4. $lst_{a_i}$ 要用 除以 $d$ 之前的 $a_i$。

[代码链接](https://codeforces.com/contest/407/submission/273468289)

---

## 作者：luogubot (赞：1)

给定序列 $a_{1\cdots n}$，找一个最长的子区间使得该子区间加入至多 $k$ 个数之后，排序后是一个公差为 $d$ 的等差数列。多个解输出 $l$ 最小的。

$n,k\leq 2\times 10^5$，$|a_i|,d\leq 10^9$。

特判掉 $d=0$，则区间 $[l,r]$ 合法当且仅当：

- 相邻两个数的 $\Delta$ 是 $d$ 的倍数。
- 没有重复元素。
- $r-l+k\ge\frac{\max-\min}{d}$。

注意到答案（长度）是没有单调性的，所以不要二分。

前两个限制是容易处理的，对于第三个限制，变形为 $\max-\min-Rd\leq (k-L)d$，当我们固定 $L$ 时右边是常数，左边的 $\max-\min$ 关于 $R$ 单调。 对于单个 $L$，考虑这样一个结算 $\max-\min$ 的方式：记 $s_R$ 表示 $[L,R]$ 的 $\max-\min$，找到 $L$ 后第一个比 $a_L$ 大的位置 $a_x$，则 $s_{x\cdots n}$ 都应该加上 $a_x-a_L$，再往后找到第一个比 $a_x$ 大的，以此类推；$\min$ 部分同理。

一个想法是向后面第一个比自己大/小的点连父边，但这题中会建立两棵树，信息不方便合并，于是只能整体维护（$\max-\min$）。另外发现，本质是从后往前维护了两个单调栈，栈中相邻两个元素之间会有 $s$ 的后缀加。

对于前两个限制，合法的 $R$ 是一个 $L$ 开始的前缀 $[L,r]$，二分出这个 $r$，然后需要查询 $L\leq R\leq r$，满足 $s_R-Rd\leq (k-L)d$ 的最大的 $R$，不妨整体维护 $s_R-Rd$，于是本质是需要维护一个序列 $val$，支持区间加，查询区间最靠后一个满足 $val_i\leq x$ 的 $i$，线段树二分可以 $O(n\log n)$ 解决这样的问题。



---

## 作者：Graphcity (赞：1)

~~这可能是本题跑的最慢的题解~~

首先特判掉 $d=0$ 的情况，这个就是最长的相同子串。

然后考虑 $d>0$。如果直接枚举左端点找右端点的话似乎不太好处理，这个时候可以考虑分治。

如果分治区间的长度 $\le 2$，完全可以直接计算。如果 $>2$ 的话，考虑左端点在 $[l,mid]$，右端点在 $(mid,r]$ 的贡献。

如果这个东西可以在 $O(m\log m)$ 的时间复杂度实现（$m$ 为区间长度），那总时间复杂度就可以降至 $O(n\log^2n)$。

设合法的区间为 $[u,v]$ 这个区间至少要满足两个条件：

- $\forall i\in [u,v],\ a_i\equiv a_{mid}\pmod d$

- $\forall i,j\in [u,v]\ (i\not=j),\ a_i\not=a_j$

可以直接扫一遍找到满足条件的最长前缀和后缀。（这里的前缀指的是 $mid+1$ 往后的部分，后缀指的是 $mid$ 及以前的部分）

接下来就可以双指针了。从左往右枚举左端点，显然合法的右端点是递增的。

一直到这里，时间复杂度均为 $O(m\log m)$。

如果一个不重的，模 $d$ 同余的数列 $l$ 加入至多 $k$ 个数可以形成一个等差数列，充要条件就是

$$
|l|+k-1\ge \frac{\max_l-\min_l}{d}
$$

放到一段区间 $[l,r]$ 中，就是

$$
\begin{aligned}
r-l+k &\ge \frac{\max_{[l,r]}-\min_{[l,r]}}{d}\\
d(r-l+k) &\ge \max_{[l,r]}-\min_{[l,r]}
\end{aligned}
$$

回到双指针。设当前的后缀最大值为 $smax$，最小值为 $smin$，分三种情况讨论：

![](https://cdn.luogu.com.cn/upload/image_hosting/ptdqmzwa.png)

由于有多个合法右端点，所以有多个前缀最大值和最小值。他们组成了一条向上的直线和一条向下的直线，设它们分别为 $pmax$ 和 $pmin$。

1. $[pmin,pmax]\subseteq [smin,smax]$，也就是图中的 $[mid+1,p]$ 段。这东西可以二分求。此时序列的最大值就是 $smax$，最小值就是 $smin$，所以不等式变为 $d(r-l+k)\ge smax-smin$，显然 $r$ 越大越好，所以检查 $p$ 是否合法即可。

2. $[smin,smax]\subset [pmin,pmax]$，也就是图中的 $(q,r]$ 段。这东西也可以二分求。此时序列的最大值是 $pmax_r$，最小值是 $pmin_r$，不等式变为 $d(k-l)\ge pmax_r-pmin_r-dr$，发现左边是定值，右边可以直接预处理。观察到一点：由于左端点是从左到右扫描的，所以 $[smin,smax]$ 这个区间会越来越靠拢，$q$ 就会递减。所以利用双指针就可以直接维护这一段区间对应的信息。不等式可以用 fhqTreap 来维护，而且这就是模板。

3. 也就是图中的 $(p,q]$ 段。这一段要么是 $pmax>smax$，要么是 $pmin<smin$。这里以 $pmax>smax$ 为例，不等式化为 $d(k-l)+smin\ge pmax_r-dr$，用与情况二相同的办法维护即可。

可以发现时间复杂度依然是 $O(m\log m)$。总时间复杂度 $O(n\log^2n)$。代码难度较大。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=4e5,inf=1e9;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

struct Tree
{
    struct Node{int l,r,key,idx,num; ll val;} t[Maxn+5];
    int tot=0,rt=0;
    #define ls(x) t[x].l
    #define rs(x) t[x].r
    inline int NewNode(ll x,int y)
    {
        t[++tot]=(Node){0,0,rand(),y,y,x};
        return tot;
    }
    inline void push_up(int p) {t[p].num=max(t[ls(p)].num,max(t[rs(p)].num,t[p].idx));}
    inline void Split(int now,ll val,int idx,int &x,int &y)
    {
        if(!now) {x=y=0; return;}
        if(t[now].val<val || (t[now].val==val && t[now].idx<=idx))
            x=now,Split(rs(now),val,idx,rs(now),y);
        else y=now,Split(ls(now),val,idx,x,ls(now));
        push_up(now);
    }
    inline int Merge(int x,int y)
    {
        if(!x || !y) return x+y;
        if(t[x].key<=t[y].key) {rs(x)=Merge(rs(x),y),push_up(x); return x;}
        else {ls(y)=Merge(x,ls(y)),push_up(y); return y;}
    }
    inline void Insert(ll x,int y)
    {
        int a,b; x=NewNode(x,y); Split(rt,t[x].val,y,a,b);
        rt=Merge(a,Merge(x,b));
    }
    inline void Delete(ll x,int y)
    {
        int a,b,c; Split(rt,x,y,a,c),Split(a,x,y-1,a,b);
        rt=Merge(a,Merge(Merge(ls(b),rs(b)),c));
    }
    inline int Count(ll x)
    {
        int a,b,c; Split(rt,x,inf,a,b); c=t[a].num;
        rt=Merge(a,b); return c;
    }
    inline void Clear() {rt=tot=0;}
} T1,T2,T3;

int n,k,d,a[Maxn+5],ans,ansl;
int Max[Maxn+5],Min[Maxn+5];
ll vals[Maxn+5],vall[Maxn+5],valr[Maxn+5];
int al,ar,bl,br,cl,cr;
map<int,int> mp;

inline void Check(int x,int y)
{
    if(ans<x) ans=x,ansl=y;
    else if(ans==x && y<ansl) ansl=y;
}
inline int Stage1(int ql,int p,int qr)
{
    if(Max[p+1]>Max[ql] || Min[p+1]<Min[ql]) return p;
    int l=p+1,r=qr;
    while(l<r)
    {
        int mid=(l+r+1)/2;
        if(Max[ql]>=Max[mid] && Min[ql]<=Min[mid]) l=mid;
        else r=mid-1;
    }
    if(1ll*d*(l-ql+k)>=Max[ql]-Min[ql]) Check(l-ql+1,ql);
    return l;
}
inline int Stage3(int ql,int p,int qr)
{
    if(Max[ql]>=Max[qr] || Min[ql]<=Min[qr]) return qr+1;
    int l=p+1,r=qr;
    while(l<r)
    {
        int mid=(l+r)/2;
        if(Max[mid]>Max[ql] && Min[mid]<Min[ql]) r=mid;
        else l=mid+1;
    }
    if(!cl && !cr)
    {
        cl=l,cr=qr;
        For(i,l,qr) T3.Insert(vals[i],i);
    }
    else
    {
        while(cl>l) --cl,T3.Insert(vals[cl],cl);
        while(cr<qr) ++cr,T3.Insert(vals[cr],cr);
    }
    int res=T3.Count(1ll*d*(k-ql));
    if(res) Check(res-ql+1,ql);
    return l;
}
inline void Stage2(int ql,int p,int nl,int nr)
{
    if(Min[nl]<Min[ql])
    {
        if(!al && !ar)
        {
            al=nl,ar=nr;
            For(i,al,ar) T1.Insert(vall[i],i);
        }
        else
        {
            while(nl<al) al--,T1.Insert(vall[al],al);
            while(ar<nr) ar++,T1.Insert(vall[ar],ar);
            while(nl>al) T1.Delete(vall[al],al),al++;
            while(ar>nr) T1.Delete(vall[ar],ar),ar--;
        }
        int res=T1.Count(1ll*d*(k-ql)-1ll*Max[ql]);
        if(res) Check(res-ql+1,ql);
    }
    else
    {
        if(!bl && !br)
        {
            bl=nl,br=nr;
            For(i,bl,br) T2.Insert(valr[i],i);
        }
        else
        {
            while(nl<bl) bl--,T2.Insert(valr[bl],bl);
            while(br<nr) br++,T2.Insert(valr[br],br);
            while(nl>bl) T2.Delete(valr[bl],bl),bl++;
            while(br>nr) T2.Delete(valr[br],br),br--;
        }
        int res=T2.Count(1ll*d*(k-ql)+1ll*Min[ql]);
        if(res) Check(res-ql+1,ql);
    }
}
inline void Count(int l,int r,int mid)
{
    int typ=a[mid]%d,ql=mid,qr=mid+1;
    al=ar=bl=br=cl=cr=0;
    T1.Clear(),T2.Clear(),T3.Clear();
    if(a[mid]%d!=a[mid+1]%d) return;
    if(a[mid]==a[mid+1]) return;
    Min[mid]=Max[mid]=a[mid];
    Min[mid+1]=Max[mid+1]=a[mid+1];
    mp.clear(); mp[a[mid]]=1;
    Rof(i,mid-1,l)
    {
        if(a[i]%d!=typ) break;
        if(mp[a[i]]) break;
        ql=i,Min[i]=min(a[i],Min[i+1]),Max[i]=max(a[i],Max[i+1]),mp[a[i]]=1;
    }
    mp.clear(); mp[a[mid+1]]=1;
    For(i,mid+2,r)
    {
        if(a[i]%d!=typ) break;
        if(mp[a[i]]) break;
        qr=i,Min[i]=min(a[i],Min[i-1]),Max[i]=max(a[i],Max[i-1]),mp[a[i]]=1;
    }
    For(i,mid+1,qr) vals[i]=-1ll*d*i+Max[i]-Min[i],
                    vall[i]=-1ll*d*i-Min[i],valr[i]=-1ll*d*i+Max[i];
    mp.clear();
    For(i,ql,mid) mp[a[i]]=1;
    int nr=mid;
    For(i,ql,mid)
    {
        if(i-1>=ql) mp.erase(a[i-1]);
        while(nr<qr && mp.find(a[nr+1])==mp.end()) nr++;
        if(nr>mid)
        {
            int p1=Stage1(i,mid,nr);
            int p3=Stage3(i,mid,nr);
            if(p1+1<=p3-1) Stage2(i,mid,p1+1,p3-1);
        }
    }
}
inline void dfs(int l,int r)
{
    if(l==r) {Check(1,l); return;}
    if(r==l+1)
    {
        if(a[r]%d==a[l]%d && a[l]!=a[r] && abs(a[r]-a[l])/d+1<=k+2) Check(2,l);
        dfs(l,l),dfs(r,r); return;
    }
    int mid=(l+r)>>1;
    Count(l,r,mid);
    dfs(l,mid),dfs(mid+1,r);
}
inline void Run0()
{
    int pre=1;
    For(i,1,n)
        if(a[i]!=a[pre])
        {
            Check(i-pre,pre);
            pre=i;
        }
    Check(n-pre+1,pre);
    printf("%d %d\n",ansl,ansl+ans-1);
}

signed main()
{
    srand(time(0));
    n=read(),k=read(),d=read();
    int Min=0;
    For(i,1,n) a[i]=read(),Min=min(Min,a[i]);
    For(i,1,n) a[i]+=abs(Min);
    if(d==0) {Run0(); return 0;}
    dfs(1,n);
    printf("%d %d\n",ansl,ansl+ans-1);
    return 0;
}
```

---

## 作者：_HL_ (赞：1)

# 扫描线 区间子区间问题

显然 只有 $\mod d$ 同余的才有可能成 $d$ 等差数列

分段 将连续且 $\mod d$ 同余的分在一段 剪掉余数除以 d 判断  $max - min - r + l - k$ 是否小于 $0$

分别解决每段的子问题 考虑平面表示区间 做法同[CF997E](https://www.luogu.com.cn/problem/CF997E)

[我的题解](https://www.luogu.com.cn/blog/hl2021hcj/solution-cf997e)

然后呢还是傻傻的把所有玩意都表示成矩形加

有一个显然的性质是一个区间满足则其子区间满足 因此线段树上二分第一个小于 $ 0 $ 的即可 可以平凡地维护

**坑点 特判 $d=0$** ljdl 题

时间空间稳稳倒数

```cpp
#include <bits/stdc++.h>
#define int long long
#define oo 10000000000
using namespace std;
map<int,int>pre;
const int N=2e5+3;
int n,k,d,a[N],cntl,cntq;
struct _b
{
	int l,r;
}block[N],lim_max[N],lim_min[N];
struct _ans
{
	int l,r,len;
}ans,qwq_ans;
struct _stc
{
	int id;
	int key;
	bool friend operator < (const _stc a,const _stc b)
	{
		return a.key<b.key;
	}
	bool friend operator > (const _stc a,const _stc b)
	{
		return a.key>b.key;
	}
	bool friend operator <= (const _stc a,const _stc b)
	{
		return a.key<=b.key;
	}
	bool friend operator >= (const _stc a,const _stc b)
	{
		return a.key>=b.key;
	}
};
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')f=1;
		c=getchar();
	}
	while(c<='9'&&c>='0')
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return f?-x:x;
}

inline void stc_max(int l,int r)
{
	stack<_stc>stc;
	stc.push({l-1,100000000});
	for(int i=l;i<=r;i++)
	{
		_stc sa={i,a[i]};
		if(stc.top()>sa)
		{
			lim_max[i].l=stc.top().id;
			stc.push(sa);
		}
		else
		{
			while(stc.top()<=sa&&stc.top().id!=l-1)
			{
				lim_max[stc.top().id].r=i;
				stc.pop();
			}
			lim_max[i].l=stc.top().id;
			stc.push(sa);
		}
	}
	while(stc.top().id!=l-1)
	{
		lim_max[stc.top().id].r=r+1;
		stc.pop();
	}
}

inline void stc_min(int l,int r)
{
	stack<_stc>stc;
	stc.push({l-1,-1});
	for(int i=l;i<=r;i++)
	{
		_stc sa={i,a[i]};
		if(stc.top()<sa)
		{
			lim_min[i].l=stc.top().id;
			stc.push(sa);
		}
		else
		{
			while(stc.top()>=sa&&stc.top().id!=l-1)
			{
				lim_min[stc.top().id].r=i;
				stc.pop();
			}
			lim_min[i].l=stc.top().id;
			stc.push(sa);
		}
	}
	while(stc.top().id!=l-1)
	{
		lim_min[stc.top().id].r=r+1;
		stc.pop();
	}
}

struct node
{
	int l_l,l_r,r,v;
	bool friend operator < (const node a,const node b)
	{
		return a.r<b.r;
	}
}line[N<<4];

struct seg
{
	int key;
	int tag;
}
t[N<<2];
#define ls p<<1
#define rs p<<1|1
inline void update(int p)
{
	t[p].key=min(t[ls].key,t[rs].key);
}
inline void pushdown(int p)
{
	if(t[p].tag!=0)
	{
		t[ls].tag+=t[p].tag;
		t[rs].tag+=t[p].tag;
		t[ls].key+=t[p].tag;
		t[rs].key+=t[p].tag;
		t[p].tag=0;
	}
}
void modify(int l,int r,int ql,int qr,int dx,int p)
{
	if(ql<=l&&r<=qr)
	{
		t[p].key+=dx;
		t[p].tag+=dx;
		return;
	}
	int mid=l+r>>1;
	pushdown(p);
	if(ql<=mid)modify(l,mid,ql,qr,dx,ls);
	if(qr>mid)modify(mid+1,r,ql,qr,dx,rs);
	update(p);
}

int query(int l,int r,int ql,int qr,int p,bool &type)
{
	if(type)
	{
		if(l==r)
		return l;
		pushdown(p);
		int mid=l+r>>1;
		if(t[ls].key<=0)return query(l,mid,ql,qr,ls,type);
		return query(mid+1,r,ql,qr,rs,type);
	}
	if(ql<=l&&r<=qr)
	{
		if(t[p].key<=0)
        {
            type=1;
		    return query(l,r,ql,qr,p,type);
        }
		return oo;
	}
	int mid=l+r>>1;
	pushdown(p);
	int res=oo;
	if(ql<=mid)res=query(l,mid,ql,qr,ls,type);
	if(type)return res;
	if(qr>mid)res=query(mid+1,r,ql,qr,rs,type);
	return res;
}

inline void solve(int l,int r)
{
	ans={0,0,0};
	stc_max(l,r);
	stc_min(l,r);
	for(int i=l;i<=r;i++)
	{
		line[++cntl]={1,n,i,-1};
		line[++cntl]={lim_max[i].l+1,i,i,a[i]};
		line[++cntl]={lim_max[i].l+1,i,lim_max[i].r,-a[i]};
		line[++cntl]={lim_min[i].l+1,i,i,-a[i]};
		line[++cntl]={lim_min[i].l+1,i,lim_min[i].r,a[i]};
	}
	sort(line+cntq,line+cntl+1);
	for(int i=l;i<=r;i++)
	{
		while(line[cntq].r<=i&&cntq<=cntl)
		{
			modify(1,n,line[cntq].l_l,line[cntq].l_r,line[cntq].v,1);
			cntq++;
		}
		if(pre[a[i]]>=l)
		modify(1,n,l,pre[a[i]],oo,1);
		pre[a[i]]=i;
		bool ttt=0;
		ans.l=query(1,n,l,i,1,ttt);
		ans.r=i;
		ans.len=ans.r-ans.l+1;
		if(qwq_ans.len<ans.len)
	    qwq_ans=ans;
	}
}
int cntb;
signed main()
{
	n=read();
	k=read();
	d=read();
	if(d==0)
	{
	    int cnt=1;
	    a[1]=read();
	    int l,r=1;
	    int tcnt=1;
	    l=1;
	    int tl;
	    for(int i=2;i<=n;i++)
	    {
	        a[i]=read();
	        if(a[i]==a[i-1])tcnt++;
	        else
	        {
	            if(cnt<tcnt)
	            {
	                cnt=tcnt;
	                l=tl;
	                r=i-1;
                }
	            tcnt=1;
	            tl=i;
            }
        }
        cnt=max(cnt,tcnt);
        cout<<l<<" "<<r;
        return 0;
    }
	a[1]=read();
	cntb=1;
	block[cntb].l=1;
	int rest[2];
	rest[0]=a[1]%d;
	if(rest[0]<0)rest[0]+=d;
	int w=1;
	for(int i=2;i<=n;i++,w^=1)
	{
		a[i]=read();
		rest[w]=a[i]%d;
		if(rest[w]<0)rest[w]+=d;
		if(rest[w]!=rest[w^1])
		{
			block[cntb].r=i-1;
			block[++cntb].l=i;
		}
		a[i-1]=(a[i-1]-rest[w^1])/d;
	}
	for(int i=1;i<=n;i++)pre[a[i]]=0;
	a[n]=(a[n]-rest[w^1])/d;
	block[cntb].r=n;
	cntq=1;
	qwq_ans.len=-oo;
	for(int i=1;i<=n;i++)line[++cntl]={i,i,1,i-k};
	for(int i=1;i<=cntb;i++)
	{
		solve(block[i].l,block[i].r);
	}
	printf("%lld %lld",qwq_ans.l,qwq_ans.r);
	return 0;
}
```


---

## 作者：Coffee_zzz (赞：1)

为了方便，先把 $d=0$ 特判掉，并给所有 $a_i$ 增加 $10^9$。显然这样做不会影响答案。

刻画一下区间 $[l,r]$ 合法的条件：

- $a_l \sim a_r$ 互不相同。
- $a_l \sim a_r$ 在模 $d$ 意义下相等；
- $\max\limits_{i=l}^r a_i - \min\limits_{i=l}^r a_i \le (r-l+k)d$；

考虑对第三个条件变形：

$$
\max\limits_{i=l}^r a_i - \min\limits_{i=l}^r a_i+ ld \le rd+kd
$$

设 $v_i=\max\limits_{i=l}^r a_i - \min\limits_{i=l}^r a_i+ ld$。

我们首先尝试，在从 $1$ 到 $n$ 不断枚举 $r$ 的同时，对于每个不大于 $r$ 的 $l$，动态地维护 $v_l$ 的值。

我们分别：

- 用一棵线段树维护 $v_l$ 的值；
- 用一个单调栈 $mx$ 维护 $a_l \gt \max\limits_{i=l+1}^{r} a_i$ 的所有位置；
- 用一个单调栈 $mn$ 维护 $a_l \lt \min\limits_{i=l+1}^{r} a_i$ 的所有位置。

我们考虑在每次 $r$ 增加 $1$ 后进行下面的操作：

- 把 $v_r$ 的值增加 $rd$；
- 把 $mx$ 中所有满足 $a_{mx_k} \le a_r$ 的位置弹掉，并在弹掉 $mx_k$ 时把 $v_{mx_{k-1}+1}\sim v_{mx_k}$ 的值减少 $a_{mx_k}$；把位置 $r$ 加入到 $mx$ 的栈顶，设加入后 $mx$ 的大小为 $s$，把 $v_{mx_{s-1}+1} \sim v_r$ 的值增加 $a_r$；
- 把 $mn$ 中所有满足 $a_{mn_k} \ge a_r$ 的位置弹掉，并在弹掉 $mn_k$ 时把 $v_{mn_{k-1}+1}\sim v_{mn_k}$ 的值增加 $a_{mn_k}$；把位置 $r$ 加入到 $mn$ 的栈顶，设加入后 $mn$ 的大小为 $s$，把 $v_{mn_{s-1}+1} \sim v_r$ 的值减少 $a_r$。

这样我们就做到了在 $\mathcal O(n \log n)$ 的时间复杂度内动态维护 $v_l$ 的值。

接下来，我们尝试在枚举 $r$ 的过程中，不断寻找最小的正整数 $f_r$，使得区间 $[f_r,r]$ 是合法的。

我们考虑下面的做法：

- 设 $p_r$ 表示在只考虑**前两个条件**（即 $a_l \sim a_r$ 互不相同和 $a_l \sim a_r$ 在模 $d$ 意义下相等）时 $f_r$ 的值；
- 显然序列 $p$ 是单调不减的，因为在只考虑前两个条件时区间越小越容易合法，所以可以先把 $p_r$ 的值设为 $p_{r-1}$；
- 考虑第一个条件：由于需要满足 $a_{f_r} \sim a_r$ 互不相同，设 $las_x$ 表示当前上一个值为 $x$ 的位置，则需要把 $p_r$ 的值赋为 $\max(las_{a_r}+1,p_r)$，并把 $las_{a_r}$ 的值赋为 $r$；
- 考虑第二个条件：由于需要满足 $a_{f_r} \sim a_r$ 在模 $d$ 意义下相等，若 $a_{p_r} \not\equiv a_r$，则需要把 $p_r$ 的值赋为 $r$，因为 $a_{p_{r-1}} \sim a_{r-1}$ 在模 $d$ 意义下都相等；
- 考虑第三个条件：由于只需要满足 $v_{f_r} \le rd+kd$，所以可以通过线段树二分在 $[p_r,r]$ 内找到最靠左的不大于 $rd+kd$ 的 $v_{f_r}$。

这样做的时间复杂度为 $\mathcal O(n \log n)$，可以通过。于是我们只需要找到 $[f_r,r]$ 中最长的区间里最靠左的区间即可。

```cpp
#include <bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define i128 __int128
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define vei vector<int>
#define pq priority_queue
#define lb lower_bound
#define ub upper_bound
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;
const int N=2e5+5,V=1e9;
const ll inf=1e18;
int n,k,d,a[N],mx[N],mn[N],tx,tn,p[N],f[N],ansl=1,ansr=0;
map <int,int> las;
ll val[N<<2],tag[N<<2];
void down(int g){
	val[g<<1]+=tag[g];
	val[g<<1|1]+=tag[g];
	tag[g<<1]+=tag[g];
	tag[g<<1|1]+=tag[g];
	tag[g]=0;
}
void modify(int g,int l,int r,int x,int y,ll v){
	if(x<=l&&r<=y){
		val[g]+=v;
		tag[g]+=v;
		return;
	}
	if(r<x||y<l) return;
	int m=(l+r)>>1;
	down(g);
	modify(g<<1,l,m,x,y,v);
	modify(g<<1|1,m+1,r,x,y,v);
	val[g]=min(val[g<<1],val[g<<1|1]);
}
int ask(int g,int l,int r,int x,int y,ll v){
	if(r<x||y<l) return -1;
	if(val[g]>v) return -1;
	if(l==r) return l;
	int m=(l+r)>>1;
	down(g);
	int res=ask(g<<1,l,m,x,y,v);
	if(res!=-1) return res;
	return ask(g<<1|1,m+1,r,x,y,v);
}
void solve(){
	cin>>n>>k>>d;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]+=V;
	if(d==0){
		int x=1,y=0;
		for(int l=1,r=1;r<=n;r++){
			l=r;
			while(a[r+1]==a[l]) r++;
			if(r-l>y-x) x=l,y=r;
		}
		cout<<x<<' '<<y<<endl;
		return;
	}
	f[0]=1;
	for(int r=1;r<=n;r++){
		modify(1,1,n,r,r,1ll*r*d);
		while(tx>0&&a[mx[tx]]<=a[r]){
			modify(1,1,n,mx[tx-1]+1,mx[tx],-a[mx[tx]]);
			tx--;
		}
		mx[++tx]=r;
		modify(1,1,n,mx[tx-1]+1,mx[tx],a[mx[tx]]);
		while(tn>0&&a[mn[tn]]>=a[r]){
			modify(1,1,n,mn[tn-1]+1,mn[tn],a[mn[tn]]);
			tn--;
		}
		mn[++tn]=r;
		modify(1,1,n,mn[tn-1]+1,mn[tn],-a[mn[tn]]);
		p[r]=max(p[r-1],las[a[r]]+1);
		las[a[r]]=r;
		if(a[p[r]]%d!=a[r]%d) p[r]=r;
		f[r]=ask(1,1,n,p[r],r,1ll*r*d+1ll*k*d);
		if(ansr-ansl<r-f[r]) ansl=f[r],ansr=r;
	}
	cout<<ansl<<' '<<ansr<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

