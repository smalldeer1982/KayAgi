# Good Subarrays (Hard Version)

## 题目描述

This is the hard version of this problem. In this version, we have queries. Note that we do not have multiple test cases in this version. You can make hacks only if both versions of the problem are solved.

An array $ b $ of length $ m $ is good if for all $ i $ the $ i $ -th element is greater than or equal to $ i $ . In other words, $ b $ is good if and only if $ b_i \geq i $ for all $ i $ ( $ 1 \leq i \leq m $ ).

You are given an array $ a $ consisting of $ n $ positive integers, and you are asked $ q $ queries.

In each query, you are given two integers $ p $ and $ x $ ( $ 1 \leq p,x \leq n $ ). You have to do $ a_p := x $ (assign $ x $ to $ a_p $ ). In the updated array, find the number of pairs of indices $ (l, r) $ , where $ 1 \le l \le r \le n $ , such that the array $ [a_l, a_{l+1}, \ldots, a_r] $ is good.

Note that all queries are independent, which means after each query, the initial array $ a $ is restored.

## 说明/提示

Here are notes for first example.

In first query, after update $ a=[2,4,1,4] $ . Now $ (1,1) $ , $ (2,2) $ , $ (3,3) $ , $ (4,4) $ , $ (1,2) $ , and $ (3,4) $ are suitable pairs.

In second query, after update $ a=[2,4,3,4] $ . Now all subarrays of $ a $ are good.

In third query, after update $ a=[2,1,1,4] $ . Now $ (1,1) $ , $ (2,2) $ , $ (3,3) $ , $ (4,4) $ , and $ (3,4) $ are suitable.

## 样例 #1

### 输入

```
4
2 4 1 4
3
2 4
3 3
2 1```

### 输出

```
6
10
5```

## 样例 #2

### 输入

```
5
1 1 3 2 1
3
1 3
2 5
4 5```

### 输出

```
7
9
8```

# 题解

## 作者：OtoriEmu (赞：15)

提出一个时间空间为线性的做法。

首先延承 C1 的做法。让所有 $a_i \gets a_i-i$，判断一个子区间 $[l,r]$ 是否合法，就相当于 $\displaystyle \min_{i=l}^r a_i \geq (1-l)$。

注意到如果子区间 $[l,r]$ 合法，那么 $[l+1,r]$ 一定合法，于是可以使用双指针，在静态的问题中 $O(n)$ 求解。具体的做法是，对于一个 $i$ 求出其极长的合法子区间 $[i,p_i]$，那么答案就是 $\displaystyle \sum_{i=1}^n p_i-i+1$。注意到里面有一些只跟 $i$ 和常数有关的东西可以提出来做其他的计算，对于这部分简单处理不再赘述。

现在问题带上了修改，我们还是直接考虑维护 $p_i$ 的值，分类讨论：

- 如果 $a_x$ 修改之后变小了：之前有一些位置能越过 $x$，但是在修改之后只能停在 $x-1$；   
- 否则：之前有一些位置被卡在了 $x-1$，现在能越过 $x$ 了，被卡在更前面的位置不可能越过 $x$。

先来解决第一个问题。我们需要先找到第一个能越过 $x$ 的位置 $u$，并且找到修改后最远的**可能可以**越过 $x$ 的位置 $d$（这个意思是说，比如当前 $a_i$ 被修改成了 $-1$，那么这个最远的位置就是 $2$，因为 $1-2 = -1$）。那么现在 $\max(d,u)$ 就是实际能越过 $x$ 的位置，它们的 $p$ 值是不会变的。剩下的位置，也就是 $[u,d-1]$（可能是空区间）就只能到 $x-1$ 了。发现我们需要维护 $p$ 值的前后缀和，中间 $[u,d-1]$ 的 $p$ 值都是 $x-1$，这样就能直接算了。

再来看第二个问题。先找到被卡在 $x-1$ 的所有位置，再找到修改后最远的**可能可以**越过 $x$ 的位置 $d$（意义同上嘛）。注意到 $p$ 单调，被卡在 $x-1$ 的所有位置一定构成一个连续的区间 $[l,r]$。当然因为要可以越过 $x$，所以需要让 $l \gets \max(l,d), r \gets \max(r,d)$。然后 $[l,r]$ 里面的所有 $p$ 会发生相同的变化，具体的，$p_l'$ 为 $l$ 之后，从左往右第二个 $i$ 满足 $a_i < 1-l$。注意到这个仍然满足单调性，于是求出 $p$ 之后可以再一次双指针求出 $p'$。对 $p'$ 做一个前缀和，就可以回答查询。

现在留下来的不能线性做出的问题有找到第一个能越过 $x$ 的位置 $u$ 和找到被卡在 $x-1$ 的所有位置。注意到 $x$ 的值域只有 $O(n)$，于是可以 $O(n)$ 预处理这些信息。

时间与空间复杂度均为 $O(n)$。具体实现可以看[提交记录](https://codeforces.com/problemset/submission/1736/175849599)。

Wonderhoy!

---

## 作者：zuytong (赞：15)

[传送门](https://www.luogu.com.cn/problem/CF1736C2)


------------
## 思路：

我们考虑没有修改时（也就是 C1）该怎么做：

我们维护一个 $c$ 数组，其中 $c_i = \max(i-a_i+1, 1)$，也就是只考虑 $a_i$ 的情况下，最小的起始位置在哪里。

对于 $a_i$，显然它的最小起始位置应该是 $\max\{c_j\},~j\le i$，记为 $p_i$。

那么最终答案就是 $\frac{n(n+1)}{2}+n-\sum_{i=1}^n p_i$

如果有修改呢？

假设我们将 $a_x$ 改为 $y$，$c_x$ 也相应改为 $\max(x - y + 1,1)$；但对于 $p_x$，如果我们暴力修改，那么改一次就会是 $O(n)$ 的。

我们考虑用线段树来维护 $p$。

对于每次修改，我们就像[ 楼房重建这题 ](https://www.luogu.com.cn/problem/P4198)一样，计算左半部分对右半部分的影响。

时间复杂度为 $O(q\log^2n)$


------------
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define FOR(i, x, y) for(int i = (x); i <= (y); i++)
#define ROF(i, x, y) for(int i = (x); i >= (y); i--)
#define PFOR(i, x) for(int i = he[x]; i; i = r[i].nxt)
inline int rd()
{
    int sign = 1, re = 0; char c = getchar();
    while(!isdigit(c)){if(c == '-') sign = -1; c = getchar();}
    while(isdigit(c)){re = re * 10 + (c - '0'); c = getchar();}
    return sign * re;
}
int T, a[200005];
LL tr[800005]; int mx[800005], mn[800005];
#define ls (now << 1)
#define rs ((now << 1) | 1)
LL calc(int now, int l, int r, int v)
{
    if(mn[now] >= v) return tr[now];
    if(mx[now] <= v) return 1ll * (r - l + 1) * v;
    int mid = (l + r) >> 1;
    if(mx[ls] <= v) return calc(rs, mid + 1, r, v) + 1ll * (mid - l + 1) * v;
    else return calc(ls, l, mid, v) + tr[now] - tr[ls];
}
inline void up(int now, int l, int r)
{
    int mid = (l + r) >> 1;
    mn[now] = min(mn[ls], mn[rs]); mx[now] = max(mx[ls], mx[rs]);
    tr[now] = tr[ls] + calc(rs, mid + 1, r, mx[ls]);
}
void build(int now, int l, int r)
{
    if(l == r)
    {
        a[l] = tr[now] = mx[now] = mn[now] = max(l - rd() + 1, 1);
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    up(now, l, r);
}
void modify(int now, int l, int r, int to, int val)
{
    if(l == r)
    {
        mx[now] = mn[now] = tr[now] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if(to <= mid) modify(ls, l, mid, to, val);
    else modify(rs, mid + 1, r, to, val);
    up(now, l, r);
}
inline void solve()
{
    int n = rd();
    build(1, 1, n);
    int m = rd();
    FOR(i, 1, m)
    {
        int x = rd(), y = rd();
        modify(1, 1, n, x, max(x - y + 1, 1));
        // printf("%lld\n", tr[1]);
        printf("%lld\n", 1ll * n * (n + 1) / 2 + n - tr[1]);
        modify(1, 1, n, x, a[x]);
    }
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    T = 1;
    while(T--) solve();
    return 0;
}
```


---

## 作者：starrylasky (赞：9)

定于 $lst_i$ 表示能到达位置 $i$ 最左边的端点。那么显然可以递推得到 $lst_i=\max\{lst_{i-1},1,i-a_i+1\}$，显然答案就是 $\sum\limits_{i=1}^n i-lst_i+1$，显然此时的 $lst$ 具有单调性。

对于每次修改，$lst_p$ 会有 $3$ 种可能的结果。

* $lst_p$ 的值不变。那么对于答案也不会变.

* $lst_p$ 的值变大，二分找到后面最后一个位置 $i$ 使得 $lst_i \leq lst_p$，会对答案造成影响的就是区间 $[p,i]$，对答案造成的影响是 $\sum\limits_{j=p}^{i}lst_j-lst_p$，搞一个前缀和可以轻松解决。
* $lst_p$ 的值变小，二分找到后面最后一个位置 $i$ 使得 $lst_i\leq lst_p$，会对答案造成影响的就是区间 $[p,i]$，对答案造成的影响是 $\sum\limits_{j=p}^i lst_j-\max(lst_{j-1},j-a_j+1)$。

为了维护后面的那一坨减号，考虑离线询问，将询问按照 $p$ 的降序排列。

建一棵线段树，维护 $\max\limits_{j=p}^i\{j-a_j+1\}$。对于每次是变小的询问，二分找到最后一个小于 $x=\max(lst_{p-1},p-a_p+1)$ 的位置 $pos$，后面那一堆就是 $\sum\limits_{i=pos+1}^I Tree_i+(pos-i+1)x$。至于每次更新就是在线段树上二分找最后一个小于等于 $p-a_p+1$ 的位置，然后区间赋值。综上，线段树要支持的操作就是区间赋值，区间求和，二分查询，所以要维护区间和，区间最大值。


---

## 作者：Alex_Wei (赞：3)

### [CF1736C2 Good Subarrays (Hard Version)](https://www.luogu.com.cn/problem/CF1736C2)

设 $b_i$ 表示以 $i$ 为左端点的合法区间的最大右端点，那么 $a_i$ 产生的影响是将 $b_{1\sim i - a_i}$ 对 $i - 1$ 取 $\min$。此外还有 $b_{1\sim n}\leq n$ 的限制。

答案即 $\sum b_i - i + 1$，只要维护 $\sum b_i$。

Multiset 维护每个位置的最小限制，楼房重建线段树维护单点修改，后缀 $\min$ 和。时间复杂度 $\mathcal{O}(q\log ^ 2 n)$。在线，且修改可叠加。[代码](https://codeforces.com/contest/1736/submission/211801559)。

来点不那么暴力的。

求出 $b$，考虑一次修改 $(p, x)$：

- 若 $x < a_p$，那么产生影响的位置从 $p - a_p$ 向右移动到了 $p - x$，影响为将 $b_{p - a_p\sim p - x}$ 对 $p - 1$ 取 $\min$。根据 $b$ 的单调性转化为区间赋值：设 $z$ 为区间内第一个 $b_z \geq p$ 的位置，则将 $b_{z\sim p - x}$ 赋值为 $p - 1$。预处理 $b$ 的前缀和，二分求 $z$。
- 若 $x > a_p$，那么产生影响的位置从 $p - a_p$ 向左移动到了 $p - x$，影响为将 $b_{p - x\sim p - a_p}$ 等于 $p - 1$ 的值换成第二小的影响值。设 $c_i$ 为该值，将每个 $a_i$ 带来的影响看成二元组 $(i - a_i, i - 1)$，那么 $c_i$ 就是第一元不小于 $i$ 的，第二小的第二元。容易线性预处理，求前缀和。$b$ 值等于 $p - 1$ 的区间也容易二分求出。

目前时间复杂度是 $\mathcal{O}(q\log n)$，但显然地，直接维护 $d_i$ 表示最小的 $p$ 使得 $b_p \geq i$，本质上就是维护每个数的 “管辖范围” $[l, r]$ 表示 $b_{l\sim r} = i$，容易做到 $\mathcal{O}(n + q)$。

代码鸽了。

---

## 作者：Y2y7m (赞：2)

先做个简单转化：

$a_i\geq i-l+1$ 转化为 $l\geq i+1-a_i$。

考虑更改一次后会对答案有什么影响……

如果变小了，可能导致有些子区间原本到了这就停住了，但更改完就可以过去；当然，反之也有可能。

设更改的位置为 $p$，更改的数为 $x$。

先处理第一种情况，现在更改完可以越过去了，于是我们需要在预处理时先处理出跳过这个点（就先不管它合不合法）可以到达的最远位置，设其为 $c$。为了计算出从哪些点可以越过去，我们还要计算原本可以越过去的子区间中 $l$ 最小是多少，设这些 $l$ 所组成的数组为 $from$。先考虑这个点是不是关键点（这个点为关键点即为这个点是某一个左端点所能到达的最右边的端点），如果不是，明显不用考虑，直接输出原始答案；如果是，则可以在预处理中处理出该点是哪个左端点的关键点，留下最靠左的，设其组成的数组为 $impl$ 故会受到影响的的区间为： $(from_i-1)$ 至 $impl_i$。

然后用前缀和处理出 $c$ 数组即可，设其为 $csum$，则这段区间答案变为：$csum_{from_p}-csum_{max(p-x,impl_p-1)}$。

再考虑第二种情况，则从 $p-x$ 至 $from_p$ 都不行了（运用一开始的转化），发现这个是一段连续的区间，于是可以使用前缀和快速计算，然后这一段区间所有的左端点所能达到的最右端点即为 $p-1$，算一下即可。

---

## 作者：lingfunny (赞：2)

对于 C1，有一种做法是固定右端点，设 $f_i$ 为 $i$ 结尾的区间最长为多少，转移方程 $f_i=\min(f_{i-1} + 1, a_i)$。

我们在这个基础上解决 C2。

假设修改是 $(p, x)$，那么对于 $i < p$，$f'_i=f_i$。（$f'$ 表示修改后的 dp 数组）

如果我们能找到这样一个最小的 $q$，使得 $f'_q = a_q$，那么对于 $i\ge q$ 的 $f'_i$，值是固定的。

所以可以处理出这么一个 $g_i$，表示钦定 $f_i=a_i$ 时，后缀 $f_i$ 的值。即 $g_i=\displaystyle\sum_{j=i}^n f_j$。

假设找出了这么一个 $q$，那么答案可以直接加上 $g_q$。

还剩下 $i\in[p, q)$ 的 $f'_i$。因为这部分的 $f'_i < a_i$，所以有 $f'_i=f'_{i-1}+1$。

接下来问题是，$q$ 怎么找，$g_i$ 怎么处理。

对于找 $q$，考虑什么时候 $(i, a_i)$ 可以成为询问 $(p, x)$ 其中一个可行 $q$，即什么时候会限制询问 $(p, x)$ 的 $f'_i$ 增长。

首先由 $f_p=\min(f_{p-1} + 1, x)$，我们令 $x \gets f_p$，那么如果没有限制，$f_p\sim f_i$ 应该为 $x, x+1, x+2, x+3, \dots$，所以当 $x+i-p > a_i$ 时会产生影响。移项得 $x-p > a_i-i$。

于是我们把询问 $(p, x)$ 和原数组 $(i, a_i)$ 扔到一起，对于所有二元组 $(p, x)$，不妨按 $x - p$ 从小到大排序，不断加入限制，查询时直接在所有限制中 `upper_bound` 即可。

对于计算 $g_i$，其实也可以用类似计算询问的方法，找到一个最小的 $q(q>i)$，使得 $f_q=a_q$，$g_i=g_q+S(q-i-1)+(q-i)\times f_{i}$。

伪代码如下：

```plain
sort ALL by (x - p)
for (p, x, op) in ALL
    if op is ASK
        q = upper_bound(p) in S
        update(op)
    else 
        q = upper_bound(p) in S
        insert p into S
        update(g[p])
```

```cpp
// Problem: C2. Good Subarrays (Hard Version)
// URL: https://codeforces.com/contest/1736/problem/C2
// Group: Codeforces - Codeforces Round #825 (Div. 2)
// Time: 2022-10-10 22:36
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 2e5 + 10;
int q, n, a[mxn], m, f[mxn];
LL S[mxn], res[mxn], pre[mxn], g[mxn];

struct ASK {
	int op, x, p;
} ask[mxn * 2];

signed main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		f[i] = min(f[i - 1] + 1, a[i]);
		S[i] = S[i - 1] + i;
		pre[i] = pre[i - 1] + f[i];
		ask[++m] = { 0, a[i], i };
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		int p, x;
		scanf("%d%d", &p, &x);
		x = min(x, f[p - 1] + 1);
		ask[++m] = { i, x, p };
	}
	sort(ask + 1, ask + m + 1, [&](const ASK &a, const ASK &b) {
		int wa = a.x - a.p, wb = b.x - b.p;
		if (wa == wb) return a.op > b.op;
		else return wa < wb;
	});
	set<int> ava = { n + 1 };
	for (int i = 1; i <= m; ++i) {
		auto [op, x, p] = ask[i];
		if (!op) {
			q = *ava.upper_bound(p);
			g[p] = g[q] + S[q - p] + (LL)(q - p) * (a[p] - 1);
			ava.insert(p);
		} else {
			q = *ava.upper_bound(p);
			res[op] = pre[p - 1] + S[q - p] + (LL)(q - p) * (x - 1) + g[q];
		}
	}
	for (int i = 1; i <= m - n; ++i) printf("%lld\n", res[i]);
	return 0;
}
```

---

## 作者：Fracture_Dream (赞：0)

# 简述题意
我们定义一个数组 $b$ 是好的当且仅当所有的 $b_i \ge i$。
现在给你 $q$ 次操作，每次操作有两个数 $p$ 和 $x$，求出把 $a_p$ 赋值成 $x$ 后 $a$ 数组好的子序列的个数，每次**操作独立**。
+ $1 \le n,q \le 2 \times 10^5$，$1 \le a_i,p_j,x_j \le n$。

# 思路
首先考虑 $\text{Easy Version}$ 怎么做。
 
由于没有修改，求子序列的个数问题，一般都是从长度和端点入手。对于此题，考虑求出以 $i$ 为开头的满足条件的子序列个数。

注意到，某个元素在子序列和原序列中的下标位置并不一样，所以很难处理。考虑令 $c_i = a_i-i$（算是一个 $\text{Trick}$ 吧），那么，对于在原序列中的 $[l,r]$，其满足条件就等价于：

$$\forall i \in [l,r],c_i + (l - 1) \ge 0$$

即 

$$i \in [l,r]，\mathrm{min\{c_i\}}+(l-1) \ge 0$$

由于最小值满足单调性，所以当左端点固定时，右端点一定单调，二分求解即可，下令 $ans$ 表示未修改时 $a$ 中满足条件的子序列个数。

再考虑修改，对于每个 $i$，我们都可以求出一个 $r_i,R_i$，$r_i$ 表示对于 $\forall r \in [i , r_i]$ 都有 $[i,r]$ 是一个合法子序列，$R_i$ 表示强制钦定 $r_i$ 满足条件，即 $a_{r_i} = inf$ 后最靠右的满足 $[i,R_i]$ 是一个合法子序列的点。

由于修改独立，且注意到修改一个点，只会对左边的点产生影响。

所以，对于每次修改 $p,x$，分成以下三种情况考虑：
- $a_p=x$，直接输出 $ans$ 即可。
- $a_p<x$，那么显然原来一些不满足条件的子序列现在可能满足条件了。对于某个 $i$，如果原来 $r_i=p-1$，那么就证明 $i$ 原来扩展右端点时在 $p$ 这个点 “卡住了”，由于这样的 $i$ 是连续的（$r_i \ge r_{i-1}$），不妨二分求出 $[l,r]$ 表示对于 $\forall i \in [l,r]$ 都满足 $r_i=p-1$。显然，只满足这个条件是不够的，还需满足 $\mathrm{min\{a_i,a_{i+1},a_{i+2},...,a_{p-1},x-p\}} + (i - 1) \ge 0$ 才行，然而这样的 $i$ 又是连续的（$i$ 越往左越难满足），所以不妨求出同时满足两个条件的 $i$ 区间 $[l_2,r_2]$，那么对于 $i \in [l_2,r_2]$，其对答案的贡献不再是 $r_i-i+1$，而是 $R_i-i+1$ 了，这个通过前缀和预处理在原答案的基础上更新即可。
- $a_p>x$，同理可以二分求出 $[l,r](r < i)$， 满足 $i \in[l,r],r_i\ge p$，然后在 $[l,r]$ 的基础上，二分求出 $[l_2,r_2]$， 满足 $i \in [l_2,r_2]，\mathrm{min\{a_i,a_{i+1},a_{i+2},....,a_{p-1},x-p\}}+(i-1) < 0$，那么对于 $[l_2,r_2]$ 里面的点对答案的贡献不再是 $r_i-i+1$，而是 $(p-1)-i+1$，同理前缀和求出即可。

# 代码
码量并不大，但要注意一下二分的边界和一些 $[l,r]$ 或 $[l_2,r_2]$ 不存在的特殊情况。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int n , q , a[MAXN] , R[MAXN] , RR[MAXN] , Min[MAXN][20];
int idl[MAXN] , idr[MAXN] , pre1[MAXN] , pre2[MAXN];
int GetMin(int l , int r) {
	int s = log2(r - l + 1);
	return min(Min[l][s] , Min[r - (1 << s) + 1][s]);
}
int w(int l , int r) {return (l + r) * (r - l + 1) / 2;}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	cin >> n;
	for (int i = 1 ; i <= n ; i ++) cin >> a[i] , Min[i][0] = (a[i] -= i);
	for (int j = 1 ; j <= 18 ; j ++) {
		for (int i = 1 ; i + (1 << j) - 1 <= n ; i ++) {
			Min[i][j] = min(Min[i][j - 1] , Min[i + (1 << j - 1)][j - 1]);
		}
	}
	int lst = 0;
	for (int i = 1 ; i <= n ; i ++) {
		int l = i , r = n;
		while(l < r) {
			int mid = l + r + 1 >> 1;
			if (GetMin(i , mid) + (i - 1) >= 0) l = mid;
			else r = mid - 1;
		}
		if (!idl[l]) idl[l] = i;
		idr[l] = i;
		R[i] = l , pre1[i] = pre1[i - 1] + (l - i + 1);
		l = l + 1 , r = n;
		if (l >= n) {
			RR[i] = n , pre2[i] = pre2[i - 1] + (n - i + 1);
			continue;
		}
		int ql = l + 1;
		while(l < r) {
			int mid = l + r + 1 >> 1;
			if (GetMin(ql , mid) + (i - 1) >= 0) l = mid;
			else r = mid - 1;
		}
		pre2[i] = pre2[i - 1] + (l - i + 1) , RR[i] = l;
	}
	cin >> q;
	while(q --) {
		int p , x;
		cin >> p >> x;
		x -= p;
		if (p == 1 || a[p] == x) {
			cout << pre1[n] << '\n';
			continue;
		}
		if (a[p] < x) {
			int l = idl[p - 1] , r = idr[p - 1];
			while(l < r) {
				int mid = l + r >> 1;
				if (min(GetMin(mid , p - 1) , x) + (mid - 1) >= 0) r = mid;
				else l = mid + 1;
			}
			if (min(GetMin(l , p - 1) , x) + (l - 1) < 0) cout << pre1[n] << '\n';
			else cout << pre1[n] + (pre2[idr[p - 1]] - pre2[l - 1]) - (pre1[idr[p - 1]] - pre1[l - 1]) << '\n';
		} else {
			int l = 1 , r = p - 1;
			while(l < r) {
				int mid = l + r >> 1;
				if (R[mid] >= p) r = mid;
				else l = mid + 1;
			}
			if (R[l] < p) cout << pre1[n] << '\n';
			else {
				int l2 = l , r2 = p - 1;
				while(l2 < r2) {
					int mid = l2 + r2 + 1 >> 1;
					if (min(GetMin(mid , p - 1) , x) + (mid - 1) < 0) l2 = mid;
					else r2 = mid - 1;
				}
				if (min(GetMin(l2 , p - 1) , x) + (l2 - 1) >= 0) cout << pre1[n] << '\n';
				else cout << pre1[n] - (pre1[l2] - pre1[l - 1]) + w(p - l2 , p - l) << '\n';
			}
		}
	}
	return 0;
}
```

---

## 作者：LiveZoom (赞：0)

## Description

[link](https://www.luogu.com.cn/problem/CF1736C2)

## Solution

先考虑一下 C1 怎么做。

C1 就是设 $b_i=a_i-i$，如果区间  $[l,r]$ 满足条件，那么 $\min\{b_l,b_{l+1},\dots, b_r\}+(l-1)\geq 0$，然后对于每一个 $l$ 二分一下 $r$ 即可。

---

然后思考怎么做 C2。

设 $res_i$ 表示以 $i$ 为左端点，右端点的最大值，易知 $res_i$ 是单调递增的。

如果 $a_p=x$，对答案没有贡献。

如果 $a_p<x$，那么有一些原来不合法的区间会变得合法。如果 $[l,r]$ 原来不合法，后来变得合法，则 $\min\{b_l,\dots,b_{p-1},x-p,b_{i+1},\dots,b_r\}+(l-1)\geq 0\space\space(l\leq p\leq r)$，这就意味着 $p=res_l+1$ 且 $x-p\geq -(l-1)$。

由于这样的 $l$ 是连续的，所以预处理出 $r_i$，表示把 $res_i$ 变得可行后对答案的贡献，然后求出 $r_i$ 的前缀和即可。

如果 $a_p>x$，那么有一些原来合法的区间会变得不合法。如果 $[l,r]$ 原来合法，后来变得不合法，则 $\min\{b_l,\dots,b_{p-1},x-p,b_{i+1},\dots,b_r\}+(l-1)< 0\space\space(l\leq p\leq r)$，那么 $p\leq res_l$ 且 $x-p<-(l-1)$。

那么 $l$ 对答案的贡献就是 $-(res_l-p+1)$，然后求出 $res_i$ 的前缀和即可。

时间复杂度：$O((n+q)\log n)$。

## Code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int kMaxN = 2e5 + 5;

int n, q;
int a[kMaxN], b[kMaxN], f[kMaxN][20], lg[kMaxN], res[kMaxN], rr[kMaxN], k[kMaxN];
int sumr[kMaxN], sumres[kMaxN];

void prework() {
  lg[0] = -1;
  for (int i = 1; i <= n; ++i) {
    lg[i] = lg[i >> 1] + 1;
    f[i][0] = b[i];
  }
  for (int i = 1; i <= lg[n]; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
      f[j][i] = min(f[j][i - 1], f[j + (1 << i - 1)][i - 1]);
    }
  }
}

int query(int l, int r) {
  int k = lg[r - l + 1];
  return min(f[l][k], f[r - (1 << k) + 1][k]);
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    b[i] = a[i] - i;
  }
  prework();
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    int L = i - 1, R = n + 1;
    res[i] = i;
    while (L + 1 < R) {
      int mid = (L + R) >> 1;
      if (query(i, mid) + (i - 1) >= 0) L = res[i] = mid;
      else R = mid;
    }
    ans += res[i] - i + 1;
    L = res[i] + 1, R = n + 1;
    if (res[i] < n) rr[i] = 1;
    while (L + 1 < R) {
      int mid = (L + R) >> 1;
      if (query(res[i] + 2, mid) + (i - 1) >= 0) L = mid, rr[i] = mid - res[i];
      else R = mid;
    }
    // if(res[i] < n)cerr << res[i] << ' ' << query(res[i] + 2, n) + (i - 1) << '\n';
    sumr[i] = sumr[i - 1] + rr[i];
    sumres[i] = sumres[i - 1] + res[i];
    assert(res[i] >= res[i - 1]);
  }
  // for (int i = 1; i <= n; ++i) {
  //   cerr << res[i] << ' ';
  // }
  res[n + 1] = 1e9;
  cin >> q;
  for (int cs = 1; cs <= q; ++cs) {
    int i, x;
    cin >> i >> x;
    // cerr << i << ' ' << x << ' ' << q << '\n';
    if (a[i] < x) {
      int resl = lower_bound(res + 1, res + 2 + n, i - 1) - res;
      int resr = lower_bound(res + 1, res + 2 + n, i) - res - 1;
      resl = max(resl, i - x + 1);
      resr = min(resr, i);
      if (resl > resr || res[resl] != i - 1) cout << ans << '\n';
      else cout << ans + sumr[resr] - sumr[resl - 1] << '\n';
    } else if (a[i] == x) {
      cout << ans << '\n';
    } else {
      int resl = lower_bound(res + 1, res + 2 + n, i) - res;
      int resr = i;
      resr = min(resr, i - x);
      if (resl > resr) cout << ans << '\n';
      else cout << ans - (sumres[resr] - sumres[resl - 1] - (i - 1) * (resr - resl + 1)) << '\n';
    }
  }
}

signed main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  while (T--) solve();
  return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

给定长度为 $n$ 的序列 $a$，定义一个序列 $b$ 是好的，当且仅当对于所有 $i$ 都有 $b_i\geq i$。

给出 $q$ 次修改，每次修改给出 $p,x$ 表示 $a_p\gets x$。每次修改之后求出好的**子串**的数量。

**询问独立，也就是本次修改不影响下一次的序列。**

$1\leq n,q\leq 2\times 10^5$，$1\leq a_i,p,x\leq n$。

# 题目思路

2400？1400！

不难发现修改了这个位置，要么是原来瓶颈卡在这里的序列变长了，要么是更长的序列到这里就瓶颈了。

考虑给修改分类。

1. $a_p=x$
    
    这是最好做的。直接回答原序列的答案即可。

    不难发现 $l=i+1$ 的右端点一定不小于 $l=i$ 的右端点。原序列答案双指针维护 $l,r$，每次尝试扩展 $r$，记 $f_i$ 表示 $i$ 开始的最长的好的序列的长度，$g_i$ 表示 $i$ 开始的最长好的序列的结束点。

    $\sum\limits_{i=1}^n f_i$ 即为答案。

1. $x\gt a_p$

    这就对应了『原来瓶颈卡在这里的序列变长了』的情况。

    在双指针预处理 $f_i,g_i$ 的时候同时维护 $h_i,t_i$ 表示 $i$ 开始的**中间允许不满足一次**最长的好的序列的长度，$t_i$ 表示 $i$ 开始的**中间允许不满足一次**最长好的序列的结束点。

    同时用 $vec_i$ 存下右端点为 $i$ 的所有左端点。

    二分 $vec_{p-1}$ 中的内容。找到第一个 $t_i\geq p$ 的点 $l$，和最后一个 $t_i\geq p$ 的点 $r$。那么 $i\in[l,r]$ 的都可以造成 $h_i$ 的贡献。$i\in[1,l-1]$ 和 $i\in [r+1,n]$ 的只能造成原有的 $f_i$ 的贡献。

    二分注意一个边界条件是 $i\geq p-x+1$。必须先满足这个条件才可能让 $p$ 不是瓶颈。

1. $x\lt a_p$

    这就对应了『更长的序列到这里就瓶颈』的情况。

    还是考虑哪一部分回到这里变成瓶颈。刚才说 $i\geq p-x+1$ 才能让 $p$ 不是瓶颈，那么 $i\lt p-x+1$ 就一定都是瓶颈。

    $[1,p-x]$ 里二分，找到第一个 $g_i\geq p$ 的点 $l$ 和最后一个 $r$，这里面必须卡到 $p$ 就结束。贡献是 $(p-l+1)+(p-(l+1)-1)+(p-(l+2)-1)+\cdots +(p-r-1)$。

    $i\in[1,l-1]$ 和 $i\in [r+1,n]$ 的还是只能造成原有的 $f_i$ 的贡献。

# 完整代码

[CF submission 284879626](https://codeforces.com/contest/1736/submission/284879626)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
typedef long long ll;
int n, q;
int a[200020];
ll f[200020];
int g[200020];
ll h[200020];
int t[200020];
vector<int> vec[200020];
ll ans;
ll cnt;
void init()
{
    int l = 1, r = 0, k = 0;
    while (l <= n)
    {
        while (r + 1 <= n && a[r + 1] >= r + 1 - l + 1)
            r++;
        k = min(n, max(k, r + 1));
        while (k + 1 <= n && a[k + 1] >= k + 1 - l + 1)
            k++;
        h[l] = (t[l] = k) - l + 1;
        cnt += (f[l] = (g[l] = r) - l + 1);
        vec[r].push_back(l);
        l++;
    }
    for (int i = n; i >= 1; i--)
        f[i] += f[i + 1];
    for (int i = n; i >= 1; i--)
        h[i] += h[i + 1];
}
ll S(ll l, ll r) { return l > r ? 0 : (l + r) * (r - l + 1) / 2; }
int main()
{
    read(n);
    for (int i = 1; i <= n; i++)
        read(a[i]);
    init();
    read(q);
    while (q--)
    {
        int p, x;
        read(p, x);
        if (x == a[p])
        {
            write(cnt, '\n');
            continue;
        }
        ll ans = 0;
        // x >= p - l + 1
        // l >= p - x + 1
        if (x > a[p])
        {
            if (vec[p - 1].empty())
            {
                write(cnt, '\n');
                continue;
            }
            int L = max(p - x + 1, vec[p - 1].front()), R = vec[p - 1].back();
            int l = 1, r = 0;
            while (L <= R)
            {
                int mid = L + R >> 1;
                if (t[mid] >= p)
                    R = (l = mid) - 1;
                else
                    L = mid + 1;
            }
            L = l, R = vec[p - 1].back();
            while (L <= R)
            {
                int mid = L + R >> 1;
                if (t[mid] >= p)
                    L = (r = mid) + 1;
                else
                    R = mid - 1;
            }
            ans += h[l] - h[r + 1];
            ans += f[r + 1];
            ans += f[1] - f[l];
        }
        if (x < a[p])
        {
            int L = 1, R = p - x;
            int l = 1, r = 0;
            while (L <= R)
            {
                int mid = L + R >> 1;
                if (g[mid] >= p)
                    R = (l = mid) - 1;
                else
                    L = mid + 1;
            }
            L = l, R = p - x;
            while (L <= R)
            {
                int mid = L + R >> 1;
                if (g[mid] >= p)
                    L = (r = mid) + 1;
                else
                    R = mid - 1;
            }
            ans += S(p - r, p - l);
            ans += f[r + 1];
            ans += f[1] - f[l];
        }
        write(ans, '\n');
    }
    return 0;
}
```

---

