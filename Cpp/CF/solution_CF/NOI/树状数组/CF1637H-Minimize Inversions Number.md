# Minimize Inversions Number

## 题目描述

给定一个长度为 $n$ 的排列 $p$。

你可以选择任意一个子序列，将其从排列中移除，并保持其原有顺序插入到排列的开头。

对于每个 $k$，$0 \leq k \leq n$，求在选择长度恰好为 $k$ 的子序列后，排列中可能的最小逆序对数。

## 说明/提示

在第二个测试用例中：

- 长度为 $0$ 时：$[4, 2, 1, 3] \rightarrow [4, 2, 1, 3]$，逆序对数为 $4$。
- 长度为 $1$ 时：$[4, 2, \mathbf{1}, 3] \rightarrow [1, 4, 2, 3]$，逆序对数为 $2$。
- 长度为 $2$ 时：$[4, \mathbf{2}, \mathbf{1}, 3] \rightarrow [2, 1, 4, 3]$，或 $[4, 2, \mathbf{1}, \textbf{3}] \rightarrow [1, 3, 4, 2]$，逆序对数为 $2$。
- 长度为 $3$ 时：$[4, \mathbf{2}, \mathbf{1}, \mathbf{3}] \rightarrow [2, 1, 3, 4]$，逆序对数为 $1$。
- 长度为 $4$ 时：$[\mathbf{4}, \mathbf{2}, \mathbf{1}, \mathbf{3}] \rightarrow [4, 2, 1, 3]$，逆序对数为 $4$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1
1
4
4 2 1 3
5
5 1 3 2 4```

### 输出

```
0 0
4 2 2 1 4
5 4 2 2 1 5```

# 题解

## 作者：小粉兔 (赞：25)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/CF1637.html](https://www.cnblogs.com/PinkRabbit/p/CF1637.html)。

**【题意简述】**

给定一个 $1 \sim n$ 的排列 $p_1, p_2, \ldots, p_n$。

对于每个 $k = 0, 1, \ldots, n$：

- 你需要在 $p_1, p_2, \ldots, p_n$ 中取出一个长度为 $k$ 的子序列，并将其按原顺序移动到 $p$ 的开头。
- 你需要求出在所有选取方案中的逆序对数的最小值。

输出这 $n + 1$ 个答案。

**【题解】**

考虑 $k = 1$ 时的情况，即选取一个数移动到首位。

- 如果选取了 $p_i$，逆序对数将减少 $\displaystyle \sum_{j = 1}^{i - 1} [p_j > p_i] - \sum_{j = 1}^{i - 1} [p_j < p_i]$，即位置 $i$ 之前的与 $p_i$ 构成的逆序对数减去顺序对数。
- 将这个数记为 $d_i$。

显然，当 $k = 1$ 时，即是选择 $d_i$ 最大的那个移动到首位即可。

接下来考虑当 $k \ge 2$ 时，逆序对数的变化量。可以看出，如果按从左到右的顺序将选取的子序列中的每个元素移到首位，则变化量恰好为子序列的 $d_i$ 之和。然而如此操作后得到的排列与定义不同：选取的子序列被翻转了，于是需要将子序列翻转回来，故原序列的逆序对数将减少「选取的子序列中的顺序对数减去逆序对数」。

即，假设选取的子序列下标为 $\{ i_1, i_2, \ldots, i_k \}$，子序列为 $q_1, q_2, \ldots, q_k$（$q_i = p_{i_j}$），则原序列的逆序对数等于 $\displaystyle \operatorname{inv}(p_{1 \sim n}) - \left( \sum_{j = 1}^{k} d_{i_j} + \left( \left( \binom{k}{2} - \operatorname{inv}(q_{1 \sim k}) \right) - \operatorname{inv}(q_{1 \sim k}) \right) \right)$，其中 $\displaystyle \binom{k}{2} - \operatorname{inv}(q_{1 \sim k})$ 一项即为顺序对数。

整理一下即得到需要最大化 $\displaystyle \sum_{j = 1}^{k} d_{i_j} - 2 \operatorname{inv}(q_{1 \sim k})$。

这时我们需要一个关键结论：对于每个逆序对 $(i, j)$（即 $i < j$ 且 $p_i > p_j$），如果 $i$ 被选取在子序列中，则 $j$ 也被选取在子序列中一定不更劣。我们使用反证 + 调整法证明此结论：

- 假设存在逆序对 $(i, j)$ 且 $p_i$ 被选取而 $p_j$ 未被选取，我们将证明存在比此种情况不更劣的情况。
- 由于满足此条件的逆序对存在，考虑选取其中 $i, j$ 距离最小的那一对，即 $j - i$ 最小的且满足 $i$ 被选取而 $j$ 未被选取的逆序对。
- 由此，在 $i, j$ 之间不存在：
  
  - 值在 $p_j$ 与 $p_i$ 之间的元素；
  - 值大于 $p_i$ 且已被选取的元素；
  - 值小于 $p_j$ 且未被选取的元素。
  
  否则，将与 $j - i$ 的最小性矛盾。
- 考虑将 $i$ 从子序列中删去，并加入 $j$，考察元素 $p_k$ 对最终逆序对数量的贡献：
  
  - 如果 $k < i$ 且 $p_k$ 被选取：$p_k$ 与 $p_i, p_j$ 的相对位置无变化，贡献 $0$；
  - 如果 $k < i$ 且 $p_k$ 未被选取：只有 $p_k$ 介于 $p_j$ 与 $p_i$ 之间时，会有贡献 $-2$，否则贡献 $0$；
  - 如果 $k > j$ 且 $p_k$ 未被选取：$p_k$ 与 $p_i, p_j$ 的相对位置无变化，贡献 $0$；
  - 如果 $k > j$ 且 $p_k$ 被选取：只有 $p_k$ 介于 $p_j$ 与 $p_i$ 之间时，会有贡献 $-2$，否则贡献 $0$；
  - 如果 $i < k < j$：只有「$p_k > p_i$ 且 $p_k$ 被选取」或「$p_k < p_j$ 且 $p_k$ 未被选取」时才有贡献 $1$，其他情况均贡献 $-1$。
  
  然而前文已说明并不存在这两类（「$p_k > p_i$ 且 $p_k$ 被选取」或「$p_k < p_j$ 且 $p_k$ 未被选取」）使得贡献为正数的情况，再加上 $i, j$ 本身从逆序对变为顺序对的 $-1$ 贡献，于是总变化量必然为负数。
- 因为每次调整后选取的子序列的下标之和必然增加，调整法将在有限步内结束。证毕。

于是，前文需最大化的 $\displaystyle \sum_{j = 1}^{k} d_{i_j} - 2 \operatorname{inv}(q_{1 \sim k})$ 中的第二项可改为 $\displaystyle \sum_{j = 1}^{k} \sum_{l = i_j + 1}^{n} [p_l < p_{i_j}]$。

令 $\displaystyle c_i = d_i - 2 \sum_{j = i + 1}^{n} [p_j < p_i]$。即是要最大化 $\displaystyle \sum_{j = 1}^{k} c_{i_j}$。

将 $c$ 从大到小排序后逐个选取即可。

所有 $c_i$ 的计算和最初逆序对数 $\operatorname{inv}(a_{1 \sim n})$ 的计算均可在 $\mathcal O(n \log n)$ 内完成。

时间复杂度为 $\mathcal O(n \log n)$。

**【AC 代码】**

```cpp
#include <cstdio>
#include <algorithm>
#include <functional>

#define F(i, a, b) for(int i = a; i <= (b); ++i)
#define dF(i, a, b) for(int i = a; i >= (b); --i)

void Solve();

int main() {
	int tests = 1;
	scanf("%d", &tests);
	while (tests--)
		Solve();
	return 0;
}

typedef long long ll;
const int MN = 500005;

int n, a[MN], c[MN];
int b[MN];
inline void Add(int i, int x) {
	for (; i <= n; i += i & -i)
		b[i] += x;
}
inline int Qur(int i) {
	int s = 0;
	for (; i; i -= i & -i)
		s += b[i];
	return s;
}

void Solve() {
	scanf("%d", &n);
	F(i, 1, n) scanf("%d", &a[i]);
	ll ans = 0;
	F(i, 1, n) b[i] = 0;
	F(i, 1, n) {
		int d = Qur(a[i]);
		ans += i - 1 - d;
		c[i] = i - 1 - 2 * d;
		Add(a[i], 1);
	}
	F(i, 1, n) b[i] = 0;
	dF(i, n, 1) {
		c[i] -= 2 * Qur(a[i]);
		Add(a[i], 1);
	}
	std::sort(c + 1, c + n + 1, std::greater<>());
	printf("%lld ", ans);
	for (int k = 1; k <= n; ++k) {
		ans -= c[k] + (k - 1);
		printf("%lld%c", ans, " \n"[k == n]);
	}
}
```

---

## 作者：Tyyyyyy (赞：7)

## CF1637H

_vp的时候猜结论过了，补个严谨题解_。

### 题意简述
给定一个 $1\sim n$ 的排列 $P$。对于 $\forall k\in[0,n]$ 求，若从排列中选择一个长为 $k$ 的子序列，保持它们的相对位置放到排列的开头，则排列的逆序对数量最小是多少。

$1\leq n\leq 5\times 10^5$。

### 题目分析

下面我们将排列中的一个元素当作二维平面上的一个点 $(i,p_i)$。

#### 结论
最优的选择方案满足：若 $p_i$ 被选择，则满足 $i<j,p_i>p_j$ 的 $p_j$ 一定被选择。否则，一定可以找到一个方案，使得新方案不比当前方案劣。

#### 证明
反证法。假设最优方案中，存在 $i,j$ 满足 $p_i$ 被选择，$p_j$ 未被选择，且$i<j,p_i>p_j$。

考虑将平面直角坐标系的第一象限根据 $(i,p_i),(j,p_j)$ 两点划分为 $9$ 个部分。即以直线 $x=i,x=j,y=p_i,y=p_j$ 为分界线。对于 $9$ 个部分，分别考虑将 $p_i$ 换成 $p_j$ 后，逆序对减少的数量。

若某个元素 $(k,p_k)$ 满足 $k<i,p_k>p_i$ 或 $k<i,p_k<p_j$ 或 $k>j,p_k>p_i$ 或 $k>j,p_k<p_j$，则将 $p_i$ 换成 $p_j$ 后元素 $(k,p_k)$ 对逆序对个数的贡献不变。

若某个元素 $(k,p_k)$ 满足 $k<i,p_j<p_k<p_i$，则将 $p_i$ 换成 $p_j$ 后，若元素 $(k,p_k)$ 原来被选择，则它对逆序对个数的贡献不变；否则，它对逆序对个数的贡献 $+2$。

以此类推，我们可以得到假设存在元素 $(k,p_k)$，且它满足以下两种条件之一，则将 $p_i$ 换成 $p_j$ 后，它对逆序对个数的贡献会减少：

- 该元素本来被选择，且 $i<k<j,p_k>p_i$。

- 该元素本来未被选择，且 $i<k<j,p_k<p_j$。

所以只要我们执行下面的算法，就可以不断缩减 $j-i$ 的大小：

- 不断找到某个被选且贡献为负的元素，然后让 $i$ 变为该元素。

- 不断找到某个未被选且贡献为负的元素，然后让 $j$ 变为该元素。

这时，$i,j$ 中间没有负贡献的元素，所以把 $i$ 换成 $j$ 不会使答案更劣。

证毕。

#### 解法
定义 $d_i$ 表示**选择且仅选择**第 $i$ 个元素放到排列开头，逆序对个数的减少量。显然 $d_i=\sum_{j=1}^i [p_j>p_i]-\sum_{j=1}^i [p_j<p_i]$。

那么设我们选择了一个子序列 $seq$，排列中的逆序对总个数为 $tot$，$seq$ 中的元素构成的逆序对个数为 $cnt$，则选择该子序列放到排列开头后，新的逆序对个数为

$$tot-\sum_{i\in seq}d_i+cnt-(\frac{|seq|(|seq|-1)}{2}-cnt)$$

设满足 $i<j,p_i>p_j$ 的数对个数为 $s_i$，则满足 $i>j,p_i>p_j$ 的数对个数显然为 $p_i-s_i-1$，满足 $i>j,p_i<p_j$ 的数对个数为 $(i-1)-(p_i-s_i-1)=i-p_i+s_i$。

所以，$cnt=\sum_{i\in seq}s_i,d_i=(i-p_i+s_i)-(p_i-s_i-1)=i-2p_i+2s_i+1$。

新逆序对个数即可化为

$$tot-\sum_{i\in  seq}i-2p_i+1-\frac{|seq|(|seq|-1)}{2}$$

设 $c_i=i-2p_i-1$，我们发现对于 $i<j,p_i>p_j$ 的点对 $(i,j)$，必然有 $c_i<c_j$。因此，为了最小化逆序对个数，我们应该先选 $c_i$ 较大，也即更偏右下方的元素。这也印证了我们刚刚的结论。

Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e5+10;
int t,n,p[N],v[N];
struct BIT
{
	int c[N];
	void add(int x,int y){for(;x<=n;x+=x&(-x))c[x]+=y;}
	ll ask(int x)
	{
		ll res=0;
		for(;x;x-=x&(-x))res+=c[x];
		return res;
	}
}tr;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&p[i]),v[i]=i-2*p[i];
		ll tot=0,sum=0;
		for(int i=1;i<=n;i++)tot+=tr.ask(n)-tr.ask(p[i]),tr.add(p[i],1);
		printf("%lld ",tot);
		sort(v+1,v+n+1),reverse(v+1,v+n+1);
		for(int k=1;k<=n;k++)
		{
			sum+=v[k];
			printf("%lld ",tot-sum-1ll*k*(k+1)/2);
		}
		puts("");
		for(int i=1;i<=n;i++)tr.c[i]=0;
	}
	return 0;
}
```

---

## 作者：Claire0918 (赞：3)

我们将题目中的排列 $\{p_i\}$ 改记作 $\{a_i\}$。记 $s$ 表示 $\{a_i\}$ 中的逆序对数量。

对于 $k = 1$ 的情况，我们考量仅移动第 $i$ 个数的答案。

对于一个 $j < i$，如果 $a_j > a_i$，那么其本来构成一个逆序对，但移动后不再构成，所以逆序对数量减 $1$；如果 $a_j < a_i$，那么其本来不构成一个逆序对，但是当 $a_i$ 移动到开头后其构成了一个逆序对，所以逆序对数量加 $1$。对于任何的 $j > i$，移动后 $a_i$ 与 $a_j$ 的相对位置不变，对逆序对数量没有贡献。

综上，答案将会减少 $\displaystyle d_i = \sum_{j = 1}^{i - 1} [a_j > a_i] - \sum_{j = 1}^{i - 1} [a_j < a_i]$。

我们接下来考量移动 $k$ 个位置 $\{p_i\}$。先考量另外一种移动方式：从小到大依次将 $\{p_i\}$ 中的位置移动到序列的开头。这样，对于每一个 $p_i$，逆序对数量恰减少了 $d_{p_i}$，所以这种移动方式的答案为 $\displaystyle s - \sum_{i = 1}^{k} d_{p_i}$。

我们发现通过这种移动方式，移动到前面的 $p_i$ 所构成的前缀顺序与题目要求的是相反的，即我们需要将其翻转。翻转时前缀中顺序对变成了逆序对，逆序对变成了顺序对。所以总逆序对数量加上正确顺序前缀的逆序对数量减去正确顺序前缀的顺序对数量，即 $\displaystyle\sum_{i = 1}^{k} \sum_{j = i + 1}^{k} [a_{p_j} < a_{p_i}] - \sum_{i = 1}^{k} \sum_{j = i + 1}^{k} [a_{p_j} > a_{p_i}]$。

综上，移动 $k$ 个位置 $\{p_i\}$ 的答案为
$$
\begin{aligned}
& s - \sum_{i = 1}^{k} d_{p_i} + \sum_{i = 1}^{k} \sum_{j = i + 1}^{k} [a_{p_j} < a_{p_i}] - \sum_{i = 1}^{k} \sum_{j = i + 1}^{k} [a_{p_j} > a_{p_i}]\\
&= s - \sum_{i = 1}^{k} d_{p_i} + \sum_{i = 1}^{k} \sum_{j = i + 1}^{k} [a_{p_j} < a_{p_i}] - ({k \choose 2} - \sum_{i = 1}^{k} \sum_{j = i + 1}^{k} [a_{p_j} < a_{p_i}])\\
&= s - {k \choose 2} - \sum_{i = 1}^{k} d_{p_i} + 2\sum_{i = 1}^{k} \sum_{j = i + 1}^{k} [a_{p_j} < a_{p_i}]\\
&= s - {k \choose 2} - (\sum_{i = 1}^{k} d_{p_i} - 2\sum_{i = 1}^{k} \sum_{j = i + 1}^{k} [a_{p_j} < a_{p_i}])\\
&= s - {k \choose 2} - (\sum_{i = 1}^{k} (d_{p_i} - 2\sum_{j = i + 1}^{k} [a_{p_j} < a_{p_i}]))\\
\end{aligned}
$$
我们希望最小化答案，即最大化 $\displaystyle \sum_{i = 1}^{k} (d_{p_i} - 2\sum_{j = i + 1}^{k} [a_{p_j} < a_{p_i}])$

我们要说明一个重要的结论：如果 $i < j, a_i > a_j$ 且 $i \in \{p_i\}, j \notin \{p_i\}$，那么调整为 $i \notin \{p_i\}, j \in \{p_i\}$ 更优。

---

证明：

我们讨论满足题设的 $j - i$ 最小的一组 $i, j$。

由于 $j - i$ 最小，所以满足以下任意一条的 $k \in (i, j)$ 不存在：

+ $a_k < a_j$ 且 $k \notin \{p_i\}$。
+ $a_k \in (a_j, a_i)$。
+ $a_k > a_i$ 且 $k \in \{p_i\}$。

我们接下来讨论调整后 $k \notin \{i, j\}$ 对答案贡献的变化。

+ $k < i$
  + $k \in \{p_i\}$。此时 $k$ 与 $i, j$ 相对位置不变，变化 $0$。
  + $k \notin \{p_i\}$。
    + $a_k \in (a_j, a_i)$。原本答案中是 $(i, k)$ 逆序对和 $(k, j)$ 逆序对，调整后变成 $(k, i)$ 顺序对和 $(j, k)$ 顺序对，变化 $-2$。
    + 否则原本是顺序对的调整后仍然是顺序对，原本是逆序对的调整后仍然是逆序对，变化 $0$。
+ $k > j$
  + $k \in \{p_i\}$。同 $k < i, k \notin \{p_i\}$。
  + $k \notin \{p_i\}$。同 $k < i, k \in \{p_i\}$。
+ $k \in (i, j)$
  + $a_k < a_j$
    + $k \in \{p_i\}$。原本答案中是 $(i, k)$ 逆序对和 $(k, j)$ 顺序对，调整后变成 $(i, k)$ 顺序对和 $(k, j)$ 顺序对，变化 $-1$。
    + $k \notin \{p_i\}$。与上文 $j - i$ 最小的要求矛盾。
  + $a_k > a_i$
    + $k \in \{p_i\}$。与上文 $j - i$ 最小的要求矛盾。
    + $k \notin \{p_i\}$。原本答案中是 $(i, k)$ 顺序对和 $(k, j)$ 逆序对，调整后变成 $(i, k)$ 顺序对和 $(j, k)$ 顺序对，变化 $-1$。
  + $a_k \in (a_j, a_i)$。与上文 $j - i$ 最小的要求矛盾。

综上，对于任何的 $k \notin \{i, j\}$，对答案的贡献变化一定非正。而原本答案中是 $(i, j)$ 逆序对，调整后变成 $(j, i)$ 顺序对，对答案贡献变化 $-1$。从而答案的变化一定为负，即更优。$\square$

---

于是，对于一个 $i \in \{p_i\}$，如果 $j > i, a_j < a_i$，一定有 $j \in \{p_i\}$。否则调整即可。

从而
$$
\begin{aligned}
& \sum_{i = 1}^{k} (d_{p_i} - 2\sum_{j = i + 1}^{k} [a_{p_j} < a_{p_i}])\\
&= \sum_{i = 1}^{k} (d_{p_i} - 2\sum_{j = p_i + 1}^{n} [a_{j} < a_{p_i} \wedge j \in \{p_i\}])\\
&= \sum_{i = 1}^{k} (d_{p_i} - 2\sum_{j = p_i + 1}^{n} [a_{j} < a_{p_i}])\\
&= \sum_{i = 1}^{k} (\sum_{j = 1}^{p_{i} - 1} [a_j > a_{p_i}] - \sum_{j = 1}^{p_{i} - 1} [a_j < a_{p_i}] - 2\sum_{j = p_i + 1}^{n} [a_{j} < a_{p_i}])\\
&= \sum_{i = 1}^{k} ((\sum_{j = 1}^{p_{i} - 1} 1 - \sum_{j = 1}^{p_{i} - 1} [a_j < a_{p_i}]) - \sum_{j = 1}^{p_{i} - 1} [a_j < a_{p_i}] - 2(\sum_{j = 1}^{n} [a_j < a_{p_i}] - \sum_{j = 1}^{p_{i} - 1} [a_j < a_{p_i}]))\\
&= \sum_{i = 1}^{k} (\sum_{j = 1}^{p_{i} - 1} 1 - 2\sum_{j = 1}^{n} [a_j < a_{p_i}])\\
&= \sum_{i = 1}^{k} ((p_i - 1) - 2(a_{p_i} - 1))\\
&= \sum_{i = 1}^{k} (p_i - 2a_{p_i} + 1)\\
\end{aligned}
$$
记 $c_i = i - 2a_i + 1$，那么移动 $k$ 个位置 $\{p_i\}$ 的答案为
$$
s - {k \choose 2} - \sum_{i = 1}^{k} c_{p_i}
$$
将 $c_i$ 从大到小排序，对 $k$ 求答案时选择前 $k$ 大的 $c_i$ 求和即可。

排序和求逆序对数量均可以在 $\mathcal{O}(n\log n)$ 时间复杂度内完成。整体复杂度 $\mathcal{O}(n\log n)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 5e5 + 10;

int t, n;
int a[maxn], c[maxn];

namespace BIT{
    int tree[maxn];
    inline int lowbit(int x){
        return x & -x;
    }
    inline void modify(int x, int k){
        for (;x <= n; x += lowbit(x)){
            tree[x] += k;
        }
    }
    inline int query(int x){
        int res = 0;
        for (;x; x -= lowbit(x)){
            res += tree[x];
        }
        return res;
    }
}

int main(){
    scanf("%d", &t);
    while (t--){
        scanf("%d", &n);
        for (int i = 1; i <= n; i++){
            scanf("%d", &a[i]), c[i] = i - (a[i] << 1) + 1;
        }
        sort(c + 1, c + n + 1, greater<int>());
        fill(BIT::tree + 1, BIT::tree + n + 1, 0);
        long long all = 0;
        for (int i = 1; i <= n; i++){
            all += i - 1 - BIT::query(a[i]);
            BIT::modify(a[i], 1);
        }
        printf("%lld ", all);
        for (int i = 1; i <= n; i++){
            printf("%lld ", all -= c[i] + (i - 1));
        }
        putchar('\n');
    }

return 0;
}
```

---

## 作者：Mirasycle (赞：2)

选择单个元素 $p_i$，逆序对数会变化 $\sum\limits_{j<i}[p_j<p_i]-\sum\limits_{j<i}[p_j>p_i]$，记为 $w_i$。

选择多个元素，下标序列为 $a_1,a_2...a_k$，变化 $\sum w_{a_i}+2\times [逆序对数-顺序对数]$。

其中逆序对数 $-$ 顺序对数可以转化为 $2\times [逆序对数]-{k\choose 2}$。

尝试打表，可以发现选择 $i+1$ 个数的方案恰好是选 $i$ 个数的方案基础上再选择一个数。

有了这个观察就很好做了，我们只需要满足单步最优，累计起来就是多步最优了。否则你很难刻画选择子序列一堆数中逆序对数。

直接动态维护加入每个 $a_i$，会产生多少代价，每次选择最小代价的加入。难以单 $\log$。

需要发现一些性质，将每个点看成 $(i,p_i)$ 放到二维平面中。采用调整法，对于 $i<j$，选择 $p_j$ 一定是更优的。对于 $(i,p_i)$ 和 $(j,p_j)$ 为分界点，平面划分出来的若干个区域进行分别讨论即可，对于单个区域贡献不劣。

于是上述加入某个数 $p_i$ 之前，对于所有 $j>i$ 且 $p_j<p_i$ 的数已经被添加过了，所以上述第二项子序列逆序对数贡献对于单个元素可以提前确定了，单个数的贡献可以变成独立的了，不会依赖于之前选择了什么而变化，直接排序即可。时间复杂度 $O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=5e5+10;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int n,p[maxn],f[maxn]; ll ans;
struct BIT{
	int c[maxn];
	void init(){ for(int i=1;i<=n;i++) c[i]=0; }
	int lowbit(int x){ return x&-x; }
	void modify(int x){ for(;x<=n;x+=lowbit(x)) c[x]++; }
	int query(int x){ int res=0; for(;x;x-=lowbit(x)) res+=c[x]; return res; }
}t;
void solve(){
	cin>>n; t.init(); ans=0;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++){
		int z=t.query(p[i]);
		ans+=i-1-z;
		f[i]=z-(i-1-z)+2*(p[i]-1-z);
		t.modify(p[i]);
	}
	sort(f+1,f+1+n); cout<<ans<<" ";
	for(int i=1;i<=n;i++) ans+=f[i]-(i-1),cout<<ans<<" ";
	cout<<endl;
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T; cin>>T;
	while(T--) solve(); 
	return 0;
}
```

---

## 作者：2022dyx (赞：1)

题目的这个操作有点复杂，我们先从简单的情况入手。对于 $k=1$ 的情况，移动 $i$ 位置的数会使逆序对数减少前面的逆序对数减前面的顺序对数，也即：
$$lst+\sum_j[j<i][a_j>a_i]-\sum_j[j<i][a_j<a_i]$$

证明显然。设选 $i$ 导致的增加量为 $d_i$，$d$ 可 $O(n\log n)$ 简单求得，只要选 $d_i$ 最大的即可。

对于要选多个数来说，直接算 $\sum_i d_i$ 显然是不对的，因为这样等价于从前往后把每个数丢到数组开头，与题目要求顺序正好相反。但这也就意味着顺序对和逆序对互换了，因此答案为：
$$lst - (\sum_i d_i + \binom{k}{2}-inv-inv)=lst+\binom{k}{2}-(\sum_i d_i-2inv)$$
其中 $inv$ 为选出序列的逆序对个数。

我们终于把答案写出来了，但是这个东西还不能直接求，需要先发掘一些性质。就最简单的直觉上来看，一定要尽量地破坏原本的逆序对，也就是说若 $(i,j)$ 组成了一个逆序对，则要尽量选 $j$ 而不是 $i$。使用增量法分析可知，此性质确实成立，因此只要选了 $i$，后面比 $a_i$ 大的数全部要选，这使得 $inv$ 可以化为和 $i$ 有关的形式，即：
$$inv=\sum_i\sum_j[j>i][a_j<a_i]$$
进一步地，答案可化为： 
$$lst+\binom{k}{2}-\sum_i(d_i-2\sum_j[j>i][a_j<a_i])$$
设求和号里的部分为 $c_i$，则只需选出最大的 $k$ 个 $c_i$ 来求答案即可。

时间复杂度为 $O(n\log n)$。

代码如下：
```
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define file(x) freopen(#x ".in", "r", stdin); freopen(#x ".out", "w", stdout);
using namespace std;
constexpr int N = 5e5 + 5;
int t, n, a[N], tree[N], c[N], ans;
int lowbit(int x) { return x & (-x); }
void modify(int x) { for (int i = x; i <= n; i += lowbit(i)) ++tree[i]; }
int query(int x) { int ret = 0; for (int i = x; i; i -= lowbit(i)) ret += tree[i]; return ret; }
signed main() {
    cin.tie(0) -> sync_with_stdio(false); 
    cin >> t;
    while(t--) {
        cin >> n, ans = 0;
        fill(tree, tree + n + 1, 0);
        for (int i = 1; i <= n; ++i) cin >> a[i], c[i] = i - (a[i] << 1);
        for (int i = n; i >= 1; --i) ans += query(a[i]), modify(a[i]);  
        sort(c + 1, c + n + 1, greater <int> ());
        cout << ans << ' ';
        for (int i = 1; i <= n; ++i) cout << (ans -= i + c[i]) << ' ';
        cout << '\n';
    }
}
```

---

## 作者：LgDan321 (赞：0)

## CF1637H

给定一个长度为 $n$ 的排列 $p_1,p_2,…,p_n$。对于每个 $k=0,1,...,n$，求：

- 做一次操作：选出 $P$ 的任意一个子序列 $Q$，然后将该子序列提取到原序列的开头。
- 最小化新序列的逆序对数。

---

求多个 $k$ 的问题，一般考虑 dp 或者增量维护。注意样例已经不凸了，所以 dp 比较困难，试图找性质维护增量。

通过打表能发现一个惊人的结论：答案序列只会不断加入新位置，不会删除已选的位置。

```
14
14 12 13 10 1 2 4 9 11 8 6 5 3 7 
62
54 13
49 5 13
44 5 6 13
38 5 6 12 13
33 5 6 12 13 14
28 5 6 7 12 13 14
22 5 6 7 11 12 13 14
20 5 6 7 10 11 12 13 14
21 5 6 7 8 10 11 12 13 14
24 5 6 7 8 9 10 11 12 13 14
29 4 5 6 7 8 9 10 11 12 13 14
39 2 4 5 6 7 8 9 10 11 12 13 14
49 2 3 4 5 6 7 8 9 10 11 12 13 14
62 1 2 3 4 5 6 7 8 9 10 11 12 13 14
```

选取其中一个随机排列的结果，上面是输入，下面的三角形左侧第一个值是对应的 $k$ 的答案，右边若干数是选用的位置。

只要每次得到一个逆序对减少量最大的位置，似乎就能得到答案。直接 KDT 维护平面加，查找全局最优值应该可以做到 $O(n\sqrt n)$，但是对于 $n\le 5\times 10^5$ 还是难以接受，于是试图分析增量，如果找到好的增量表示方式，这个结论可能可以顺便证出来。

不妨先分析 $k=1$ 的增量。对于任何一个点，其相比 $\mathrm{inv}(P)$ 的减少量都为：
$$
d_x=\sum_{i=1}^{x-1}[p_i>p_x]-[p_i<p_x]=x-1-2\sum_{i=1}^{x-1}[p_i<p_x]
$$
对于 $k=1$ 的情况，先求 $\mathrm{inv}(P)$ 并减掉最大的 $d_x$ 即可。

于是对于任意一个点，提取走它，贡献都算出来了。但是对于子序列 $Q$，本来减掉的逆序对，因为两个点都被提取，贡献需要加上 $({k\choose 2}-\mathrm{inv}(Q))-\mathrm{inv}(Q)$，也就是对 $Q$ 内的点对贡献取反。总结果为：
$$
\mathrm{inv}(P)-\left(\sum_{x\in Q}d_x+\left({k\choose 2}-\mathrm{inv}(Q)\right)-\mathrm{inv}(Q)\right)
$$
所以我们要最大化 $\sum_{x\in Q}d_x-2\mathrm{inv}(Q)$。$\mathrm{inv}(Q)$ 依旧不直观。

接下来考虑能否使用贪心调整的方法优化。先试着局部调整，可以选择直接拿出一个点对，看一下其中一个被选，另外一个没被选，是否能够调整。经过笔者手搓，顺序对的调整并不理想，但逆序对可以发现这样的性质：如果 $(i,j)$ 中 $p_i>p_j$ ，则选 $p_i$ 时必定选择了 $p_j$。考虑证明。

- 对于多个 $(i,j)$，首先考虑最近的一对，即 $j-i$ 最小，这样位于中间的点就会尽可能少。
- 于是分析中间有哪些影响答案的 $p_k\{i<k<j\}$ ：
  - $p_j<p_k<p_i$ 一定不存在。无论 $k$ 有没有选中都会矛盾。
  - $p_k<p_j$，此时 $k$ 一定选中了，此时改为提取 $p_j$，原本 $p_i>p_k$ 产生的贡献不再存在。
  - $p_k>p_i$，此时 $k$ 一定没选中，此时改为提取 $p_j$，原本 $p_k>p_j$ 产生的贡献不再存在。
- 对于外面影响答案的 $p_k$，对于 $k<i$ 或者 $j<k$ 时，此时向前提取的点变小了，产生的贡献一定更优。

所以 $p_i$ 就可以调整到 $p_j$。这种调整肯定是有限步结束的。前面需要最大化 $\mathrm{inv}(Q)$，对于任何一个点 $i$，有刚刚的结论，那么所有 $i<j\wedge p_i>p_j$ 的 $j$ 一定选中了。这样逆序对就很直接了。那么定义$d'_x=d_x+2\sum_{i=x+1}^n [a_x>a_i]$，直接最大化 $\sum d'_i$ 就行了。确实顺便证明了不断增加点进行构造的正确性。

很短的 code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef long long ll;
constexpr int N=500005;
struct BIT{
    int val[N];
    void add(int x,int y){
        for(;x<N;x+=(x&(-x)))val[x]+=y;
    }
    int sum(int x){
        int ret=0;
        for(;x;x&=(x-1))ret+=val[x];
        return ret;
    }
}B;
int n,c[N],a[N];
ll res;
void solve(){
    res=0;
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        c[i]=i-1-2*B.sum(a[i]);
        res+=i-1-B.sum(a[i]);
        B.add(a[i],1);
    }
    for(int i=1;i<=n;++i)B.add(i,-1);
    for(int i=n;i>=1;--i){
        c[i]-=2*B.sum(a[i]);
        B.add(a[i],1);
    }
    for(int i=1;i<=n;++i)B.add(i,-1);
    sort(c+1,c+1+n);
    reverse(c+1,c+1+n);
    for(int i=0;i<=n;++i){
        res-=c[i];
        cout<<res-(1ll*i*(i-1)/2)<<' ';
    }
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}

---

