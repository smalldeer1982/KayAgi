# Phys Ed Online

## 题目描述

一所不知名大学的学生没有体育课。这就是为什么他们中的$q$个人决定自己去附近的健身房。健身房共开放$n$天，并设有门票系统。在第$i$天，一张门票的费用等于$a_i$，您被允许每天可以购买一张以上的门票。

您可以在第$i$天或之后的任何一天激活已购买的门票。每张已激活的门票仅在$k$天内有效。换句话说，如果您在第$t$天激活了门票，它将仅在第$t$天、第$t+1$,...,第$t+k-1$天有效。

您现在知道第$j$个学生想要在从$l_i$到$r_i$的每一天都去健身房。而每个学生将在第$i$天$(l_i \le i \le r_i)$通过下列的步骤进入健身房:

$1.$一个学生来到健身房门口的售票处，用$a_i$的价格购买几张门票。($a_i$可能为零)

$2.$如果这个学生至少有一张已激活的有效门票，便可直接进入健身房。否则，这个学生必须激活一张今天或是更早时候购买的门票才能进入健身房。

注意，每个学生从第$l_j$天开始就会去健身房，所以每个学生必须在第$l_j$天购买至少一张门票。

请帮助学生们计算去健身房的最低花费。

## 说明/提示

让我们看看每个学生如何花钱：

$\bullet$第一名学生应在第$1$天购买一张门票。

$\bullet$第二名学生应在第$3$天购买一张门票，在第$4$天购买两张门票。注意，学生们可以在接下来的几天中保留已购买的门票。

$\bullet$第三名学生应在第$5$天购买一张门票。

$\bullet$第四名学生应在第$7$天购买一张门票。

$\bullet$第五名学生应在第$3$天购买一张门票，第$4$天购买一张门票。

## 样例 #1

### 输入

```
7 5 2
2 15 6 3 7 5 6
1 2
3 7
5 5
7 7
3 5```

### 输出

```
2
12
7
6
9```

# 题解

## 作者：摸鱼酱 (赞：5)

没有多组询问时显然是可以贪心的。设 $b_i=\min_{j=i-k}^i\{a_i\}$，则询问 $[l,r]$ 的答案为 $a_l+b_{l+k}+\min\{b_{l+k},b_{l+2k}\}...+\min\{b_{l+k},b_{l+2k}+\dots +b_{l+tk}\}$，其中 $t$ 是最大的满足 $l+tk\leq r$ 的整数。

考虑后面那个前缀 $\min$ 的前缀和的形式，我们把它抽离出来，设得到了序列 $c_{1\cdots m}$，求 $f_i=\sum_{j=i}^n \min\{c_{i\cdots j}\}$，这部分可以用单调栈处理出 $nxt_i$ 表示 $i$ 后面第一个值小于 $c_i$ 的位置，则 $f_i=f_{nxt_i}+(nxt_i-i)·c_i$。

题目中求的形式是 $\sum_{i=l}^r \min\{c_{l\cdots i}\}$，求这个可以找到 $c_p=\min\{c_{l\cdots r}\}$，则前面的式子就等于 $f_l-f_p+c_p·(r-p+1)$，这个的意义是从 $l$ 到 $p$ 都是用的 $f_l$ 的方案，从 $p$ 开始往后，$f_l,f_p$ 用的都是同一个方案，对应的值自然相同，可以相减，而 $[p,r]$ 段用的最小值都是 $c_p$，再加回来即可。

精细实现可以做到线性，但 ST 表就可以通过了，时间复杂度 $O(n\log n)$。

[code](https://codeforces.com/contest/1601/submission/133210519)。

---

## 作者：陈刀仔 (赞：4)

考虑一次询问的情况，显然有一个贪心：
$$
ans=\sum_{i=l+kx,i\leq r}\min\limits_{l\leq j\leq i}\{a[j]\}
$$
考虑优化这个前缀最小值的前缀和。

考虑到只会在与 $l$ 模 $k$ 同余的时候取值，我们把每个长度为 $k+1$ 的段捆包，右端点为 $i$ 记为 $c_i$ ，一个 $c_i$ 造成的影响范围必然是对于后面的某一段里面，新的 $c_j(j>i)$ 不如 $c_i$ 优，直到遇到比 $c_i$ 优的再换。那么我们可以通过从 $l+k$ 开始查询后继，再计算贡献，这种方式可以起到一点点优化效果。

一个个跳非常的慢，我们考虑倍增。

我们枚举每一种余数，在所有同余的位置上跑一个单调栈，预处理一个 $to[i][j]$ 表示 $i$ 后面第 $2^j$ 个比 $c_i$ 小的位置，再计算一个产生的贡献 $s[i][j]$ ，倍增跳求解即可。

---

## 作者：feecle6418 (赞：4)

百年一遇的简单 div.1 E。

首先注意到可以把贡献写成 

$$\sum_{i=l+xK,l\le i\le r,x\in Z} \min_{l\le j\le i} a_j$$

因此可以直接认为 $r=l+k\lfloor\dfrac {r-l}k\rfloor$，这样 $l,r$ 就模 $k$ 同余了。

把询问按照 $l,r$ 模 $k$ 的余数分类，对于模 $k$ 余 $p$ 的那一类，设 $g(i)=\min_{iK+p+1\le j\le (i+1)K+p}$，那么答案就可以写成（式子只要涉及下取整，都会有加一减一之类的问题，读者可以自己推一下，这里只想说明大体思路）

$$\sum_{i\le \frac{r}{K}} \min(a_l,\min_{\frac lK\le j\le i} g(j))$$

这个显然可以单调栈求，从后往前扫 $g$，然后二分找到 $a_l$ 的管辖区，再二分找到 $\dfrac rK$ 的位置，然后分段计算答案。只需要在单调栈上做 $g(st_i)(st_i-st_{i-1})$ 的前缀和。

总时间复杂度 $O(K\times \dfrac nK\times \log n)=O(n\log n)$。

---

## 作者：Super_Cube (赞：1)

# Solution

其实是求这么个东西：$\displaystyle\sum_{l+ki\le r}\min_{j=l}^{l+ki}a_j$。

设 $b_i=\displaystyle\min_{j=i-k}^ia_j$，那答案为 $a_l+\displaystyle\sum_{l+ki\le r}\min_{1\le j\le i}b_{l+kj}$。

可以看出 $\forall j,l\equiv l+kj\pmod k$，而且 $\left\lfloor\dfrac{l+kj}{k}\right\rfloor=\left\lfloor\dfrac{l}{k}\right\rfloor+j$ 是连续的一段，于是把 $b_i$ 挂在 $i\bmod k$ 上，答案相当于在序列 $l\bmod k$ 的一段区间上的前缀最小值之和。

到这就成经典问题了，把它提取出来：对于任意给定的序列 $a$，多次询问 $\displaystyle\sum_{j=l}^r\min_{i=l}^ja_i$ 的值。

下面介绍一种在线做法。找到 $x\in[l,r]$ 使得 $a_x=\displaystyle\min_{i=l}^ra_i$，那么对于 $j\ge x$ 的贡献为 $a_x(r-x+1)$。关于 $j<x$ 的部分？设 $f_{l,r}$ 表示左端点为 $l$，右端点在 $[l,r]$ 的贡献，所以 $i<x$ 部分即为 $f_{l,x-1}$。

现在的需求是快速算任意 $f_{l,r}$。利用单调栈找到 $suf_i$ 为从 $i$ 开始往后第一个小于 $a_i$ 的位置，对于 $[l,suf_l)$ 的最小值都为 $a_l$，于是 $f_{l,r}=a_l(suf_l-l)+f_{suf_l,r}$。发现转移与 $r$ 无关，直接去掉：$f_l=a_l(suf_l-l)+f_{suf_l}$。现在的 $f_l-f_r$ 就是原来的 $f_{l,r-1}$。

所以答案为 $a_x(r-x+1)+f_l-f_x$。

---

## 作者：tzc_wk (赞：0)

> 摘自我的 [贪心/构造/DP 杂题选做Ⅲ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp3.html) 中的第 $59$ 题

其实感觉在重大考试出纯贪心题是占少数，倒是有不少题是将贪心与计数/数据结构结合，这种数据结构/计数题一般是先给你一堆操作，问你有多少个序列符合在多少多少次操作之内达成什么目标/要动态维护一个集合之类的东西并查询最少进行多少次操作才能打成什么目标之类的，而发现如何实现最优策略的过程，就需要贪心。此题就是典型，~~虽然它的贪心还不算困难~~

~~比赛现场先开 D 后开 E，巨大的失误。~~

首先一个非常显然的性质是我们肯定会恰好在 $l,l+k,l+2k,\cdots$ 时刻用攒下来的入场券，这就要求我们在 $[l,l],[l,l+k],[l,l+2k],\cdots$ 时刻中各买一个入场券，而显然我们肯定会买这些区间中 $a_i$ 最小的入场券，因此对于一组询问，它的答案可以表示为：
$$
\sum\limits_{l+tk\le r,t\ge0}(\min\limits_{i=l}^{l+tk}a_i)
$$
考虑如何求之。不难发现，询问的右端点其实不算太重要，因为对于使得 $l+tk\le r$​ 最大的 $t$​ 相同、左端点也相同的两个询问，它们的答案肯定是相同的。而左端点就不同了，所有查询 $\min$​ 的区间的左端点都等于 $l$​，且区间长度都模 $k$​ 余 $1$​，这不禁启发我们将 $l\bmod k$​ 相同的询问放在一起处理。我们将询问挂在 $l$​ 处然后枚举 $l\bmod k$​ 的值 $i$​ 并批量处理 $i\equiv l\pmod{k}$​ 的询问们。当我们处理 $i\equiv l\pmod{k}$​ 的询问时，我们将 $i\equiv j\pmod{j}$​ 的点设为关键点，然后对于关键点之间的区间，我们提取出它们的最小值，这样我们可以得到一个长度大概是 $\dfrac{2n}{k}$​ 的序列，然后我们在这个序列上从后往前扫一遍单调栈，单调栈的同时处理出上相邻两个点 $stk_{tp},stk_{tp-1}$​ 之间有多少关键点 $cnt$​，并求出 $a_{stk_{tp}}·cnt$ 的前缀和，这样查询时就在单调栈上二分离栈底最近的 $\le l+\lfloor\dfrac{r-l}{k}\rfloor·k$ 的点，前面的段使用前缀和算出，最后一段单独处理一下即可做到 $\Theta(\log n)$ 地查询。

总复杂度 $\Theta((n+q)\log n)$。

```cpp
namespace fastio {
	#define FILE_SIZE 1 << 23
	char rbuf[FILE_SIZE], *p1 = rbuf, *p2 = rbuf, wbuf[FILE_SIZE], *p3 = wbuf;
	inline char getc() {
		return p1 == p2 && (p2 = (p1 = rbuf) + fread(rbuf, 1, FILE_SIZE, stdin), p1 == p2) ? -1: *p1++;
	}
	inline void putc(char x) {(*p3++ = x);}
	template <typename T> void read(T &x) {
		x = 0; char c = getchar(); T neg = 0;
		while (!isdigit(c)) neg |= !(c ^ '-'), c = getchar();
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
		if (neg) x = (~x) + 1;
	}
	template <typename T> void recursive_print(T x) {
		if (!x) return;
		recursive_print (x / 10);
		putc (x % 10 ^ 48);
	}
	template <typename T> void print(T x) {
		if (!x) putc('0');
		if (x<0) putc('-'), x = -x;
		recursive_print(x);
	}
	template <typename T> void print(T x,char c) {print(x); putc(c);}
	void print_final() {fwrite(wbuf, 1, p3-wbuf, stdout);}
}
using namespace fastio;
const int MAXN = 3e5;
const int LOG_N = 19;
int n, qu, k, a[MAXN + 5] ,L[MAXN + 5], R[MAXN + 5];
pii st[LOG_N + 2][MAXN + 5]; vector<int> qv[MAXN + 5];
pii query_st(int l, int r) {
	int k = 31 - __builtin_clz(r - l + 1);
	return min(st[k][l], st[k][r - (1 << k) + 1]);
}
ll res[MAXN + 5];
int query(int l, int r, int x) {
	int posl = l / k * k + x;
	if (posl < l) posl += k;
	int posr = r / k * k + x;
	if (posr > r) posr -= k;
	if (posl > posr) return 0;
	return (posr - posl) / k + 1;
}
int main() {
	read(n); read(qu); read(k);
	for (int i = 1; i <= n; i++) read(a[i]), st[0][i] = mp(a[i], i);
	for (int i = 1; i <= qu; i++) read(L[i]), read(R[i]), qv[L[i]].pb(i);
	for (int i = 1; i <= LOG_N; i++) for (int j = 1; j + (1 << i) - 1 <= n; j++)
		st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
	for (int i = 1; i <= k; i++) {
		vector<int> vec;
		for (int j = i; j <= n; j += k) {
			if (k != 1 && j - k >= 1)
				vec.pb(query_st(j - k + 1, j - 1).se);
			vec.pb(j);
		}
		static int stk[MAXN + 5];
		static ll sum[MAXN + 5];
		int tp = 0;
		for (int j = (int)(vec.size()) - 1; ~j; j--) {
			int p = vec[j];
			while (tp && a[stk[tp]] >= a[p]) tp--; stk[++tp] = p;
			sum[tp] = sum[tp - 1] + 1ll * a[p] * query(p, stk[tp - 1] - 1, i % k);
			if ((p - i) % k == 0) {
				for (int id : qv[p]) {
					int pos = (R[id] - L[id]) / k * k + L[id];
					int l = 1, r = tp, pp = 0;
					while (l <= r) {
						int mid = l + r >> 1;
						if (stk[mid] <= pos) pp = mid, r = mid - 1;
						else l = mid + 1;
					}
					res[id] = sum[tp] - sum[pp] + 1ll * a[stk[pp]] * query(stk[pp], pos, i % k);
				}
			}
		}
	}
	for (int i = 1; i <= qu; i++) print(res[i], '\n');
	print_final();
	return 0;
}
```

---

