# Balancing Weapons

## 题目描述

You've got a job in a game studio that developed an online shooter, and your first big task is to help to balance weapons. The game has $ n $ weapons: the $ i $ -th gun has an integer fire rate $ f_i $ and an integer damage per bullet $ d_i $ . The $ i $ -th gun's total firepower is equal to $ p_i = f_i \cdot d_i $ .

You have to modify the values $ d_i $ of some guns in such a way that the new values $ d_i $ will still be integers, and the firepower of all guns will become balanced. Given an integer $ k $ , the guns are said to be balanced if $ \max\limits_{1 \le i \le n}{p_i} - \min\limits_{1 \le i \le n}{p_i} \le k $ .

Since gamers that play your game don't like big changes, you need to change the values $ d_i $ for the minimum possible number of guns. What is the minimum number of guns for which you have to change these values to make the guns balanced?

Note that the new values $ d_i $ must be integers greater than $ 0 $ .

## 说明/提示

In the first test case, you can set $ d_1 = 2 $ and $ d_2 = 4 $ . You'll get an array $ d = [2, 4, 1, 2] $ , and the values of firepower will be $ p = [12, 12, 13, 14] $ . The guns are balanced, since $ 14 - 12 \le 2 $ .

In the second test case, you have to change the value $ d_i $ for all three guns. For example, you can set $ d = [5151, 5100, 5050] $ .

In the third test case, all guns are already balanced, so you don't have to change anything.

## 样例 #1

### 输入

```
5
4 2
6 3 13 7
1 2 1 2
3 2
100 101 102
100 99 98
5 0
1 12 4 4 3
12 1 3 3 4
2 50
1000 10
1000000000 1
3 5
1 19 11
49 4 72```

### 输出

```
2
3
0
1
2```

# 题解

## 作者：dbxxx (赞：17)

[欢迎您到我的博客阅读本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/cf1814d.html)

原题明显可以转化为：

给定一个长度为 $n$ 的数组，初始为 $p_i$。可以调整元素的值，但第 $i$ 个元素必须是 $a_i$ 的 **整数** 倍，并且 **必须严格大于** $\boldsymbol 0$（保证 $p_i$ 初始满足此要求）。求至少修改多少个元素，可以让数组的极差不超过 $k$。

---

首先观察到答案和数组内部顺序无关，即所给数列可看做可重集。这是很经典重要的信息，提示我们第一步可以向两个方向思考：

- 将数列排序。
- 对数列求出权值数组，在权值数组上考虑问题。

不过，我的做法并不需要做上面任意一步，但上面这个思维是必须要有的。本题有别的做法必须先对这个数组排序，因为排序后保留不改的元素是一段区间，这是一个非常良好的性质。

---

首先，修改一定有解。设 $L$ 为所有 $a_i$ 的 $\operatorname{lcm}$，我们一定可以将所有 $p_i$ 同时修改为 $L$（注意这里并没有规定 $p_i$ 的上界，即使 $L$ 可能很大也无所谓）。那也就是说，修改 $n$ 个元素一定可以达成目的。

接下来考虑修改少于 $n$ 个元素的情况，这样以来一定存在一个元素没动。因此，考虑对这 $n$ 个元素，依次钦定第 $i$ 个元素不动考虑问题，就能把修改少于 $n$ 个元素的情况全都考虑到。

接下来钦定第 $x$ 个元素不动。那么必要条件是所有元素必须落入 $[p_x - k, p_x + k]$。当然，这个条件不充分，因为这样只能保证极差不超过 $2k$。下面，我们称这个区间为 $S(x)$。这个区间是建立在数组值域上的，而非下标。

在下面，区间 $[l, r]$ 的长度被认为是 $r - l$，即一维坐标轴上点 $l$ 到点 $r$ 这条线段的长度，而非这个区间包含的整数数量 $r - l + 1$。那么，若干个数落在长度为 $k$ 的区间内，可以推得这些数的极差不超过 $k$。

为让所有元素极差不超过 $k$，我们期望所有元素落在 $S(x)$ 内部的一个长度为 $k$ 的小区间内。这样的小区间数量为 $k$，可以通式地表示为 $[l, l + k]$，其中 $p_x -k \le l \le p_x$。

全局小区间的数量不超过 $nk$，这个量级可以承受。考虑依次钦定这 $nk$ 个小区间中的每一个，计算将所有元素落入这个小区间的最小代价，然后再对求出的所有最小代价取最小值，作为全局最小代价（答案）。这样一定可以考虑到所有情况，因为任何一种少于 $n$ 个元素的修改方式，都能在 $nk$ 个小区间中找到一个小区间 $P$，使得这种修改方式会将所有元素落入 $P$ 内。

> 关于 $nk$ 这个量级是否可承受：注意到这里确实没有限制 $\sum k$，但是只要限制一个 $\sum n$ 就已经足够了。设每组数据规模分别为 $n_1, n_2, n_3, \ldots$ 和 $k_1, k_2, k_3, \ldots$，最终的代价有 $n_1k_1 + n_2k_2 + n_3k_3 + \ldots \le K\sum n$，其中 $K = \max(k_i)$，因此不用限制 $\sum k$。

$nk$ 已经将近到极限了，所以计算每个区间最小代价的复杂度不能超过 $\log $ 了（可以均摊）。然而事实上这题卡 $\log$ 的常数所以我就讲讲均摊 $\Theta(1)$ 计算每个区间的方法吧。

枚举区间本身就已经需要区间长度的复杂度，直接爆炸了。所以关键就是找到区间和区间之间的关系加速计算，使得复杂度均摊，降低。

注意到，共 $nk$ 个小区间大体是分成 $n$ 组的，同一个 $x$ 的 $S(x)$ 内部的 $k$ 个小区间是一组。不同组的区间之间基本无关，而同组区间关系密切：$[p_x - k, p_x]$ 和 $[p_x - k + 1, p_x +1]$ 有 $k - 1$ 的长度完全重合，而 $[p_x - k + 1, p_x +1]$ 和 $[p_x - k + 2, p_x + 2]$ 之间也有这种关系……得益于这种高度的重合性，用 **双指针** 加速计算同组内区间的答案：

维护两个指针 $l = p_x - k$，$r = p_x$，然后同步向右移动 $l$ 和 $r$ 恰 $k$ 步，就扫描到了 $S(x)$ 内部的这 $k$ 个小区间。如果我们能做到这 $2k$ 次指针移动中，每次移动都能快速更新辅助计算区间最小代价的信息（这里要求 $\Theta(1)$），就能做到 $\Theta(k)$ 计算出 $k$ 个小区间的答案，也即均摊 $\Theta(1)$。

当然，这里需要提前知道 $[p_x - k, p_x]$ 的信息作为初始状态。不过也可以这么理解：先令 $l = p_x - k$，$r = l - 1$，也即一个空区间，空区间内部信息一般很平凡。然后再令 $r$ 向右移动 $k +1$ 步，使得信息慢慢更新到 $[p_x - k, p_x]$，然后再让 $l$ 和 $r$ 同步向右。这样以来就是 $3k$ 次指针移动，影响较小。虽然我最后实际代码中，是直接计算初始区间，然后直接令 $l = p_x - k$，$r = p_x$ 的；但是这个思想可以一定程度简化问题，**后面的讲解可以不再考虑初始区间，只考虑指针移动时区间信息的变化，以及怎么快速维护这样的信息变化。**

接下来我们关心小区间最小代价的计算方法。显然，已经在小区间内部的 $p_i$ 无需修改，不在的必须修改，所以只要统计小区间内部 $p_i$ 的数量 $c$，代价就是 $n - c$。因此，我们应该维护小区间内部 $p_i$ 的数量 $c$。

那么双指针在移动时可以 $\Theta(1)$ 地快速更新 $c$ 值吗？这不难做到。考虑记录 $\mathrm{cnp}(j) = \sum_{i = 1}^n [p_i = j]$，这里我们只关心 $j \in S(x)$，也即 $\mathrm{cnp}$ 看做长度为 $2k + 1$ 的数组（代码实际实现时下标手动平移到 $0 \sim 2k$ 即可）。这个记录复杂度是 $\Theta(n)$ 的。

> 注意虽然 $S(x)$ 的长度是 $2k$，但是 $S(x)$ 所含整数元素数量是 $2k + 1$，所以 $\mathrm{cnp}$ 的长度（数组的长度指所含元素数）为 $2k + 1$。

对于夹在两个双指针之间的区间 $[l, r]$，其 $c$ 值是 $\sum\limits_{j = l}^r\mathrm{cnp}(j)$。这个信息用双指针维护非常简单：当 $r$ 从 $r' - 1$ 移动到 $r'$ 时，$c$ 自增 $\mathrm{cnp}(r')$；$l$ 从 $l'$ 移动到 $l' + 1$ 时，$c$ 自减 $\mathrm{cnp}(l')$。

上面的做法比较简单，但有漏洞：上面我们直接默认任何一个不在小区间内的元素，都能落入当前小区间的内部。但这个命题并不正确，因为本题中元素的调整方法在正整数域离散——必须以 $a_i$ 为步长。举个例子，$a_i = 5$，小区间 $[7, 9]$，$p_i$ 无论如何调整都无法落入该小区间内。

如果出现了这种情况，小区间的 $c$ 可以正常计算，但因为所有元素无法都落入该小区间内，**该小区间应当是不合法的，这个小区间的 $\boldsymbol{n - c}$ 不应更新答案。**所以，我们还需 **快速维护一个区间是否合法。**

**一个小区间合法，等价于所有元素都存在一个正倍数点落在这个小区间中。**

我们尝试标记所有元素的所有落在 $S(x)$ 内部的正倍数点。对于 $a_i$ 的正倍数点 $j \in S(x)$，我们记录 $j$ 这个位置是 $a_i$ 的正倍数点。**注意，一个位置可以是多个 $\boldsymbol{a_i}$ 的正倍数点。**

我们不妨调整 $S(x)$ 的定义为 $[\boldsymbol{\max(p_x - k, 1)}, p_x + k]$。这样以来，如果一个数的倍数点落在这个区间内，它一定是正数。**那么正数这个条件就不用强调了。**同时本题不会涉及到 $<1$ 的值，所以这样调整能保证不会丢掉不应该丢的情况，也同时能减少该大区间内长度为 $k$ 的小区间的数量，有助于减少常数（本题卡常）。

这里先给出枚举且仅枚举到 $t$ 在区间 $[L, R]$ 内的倍数点的思路（这是个常用技能）：

> 不小于 $L$ 的最小 $t$ 倍数点为 $u = \left\lceil\dfrac L t \right\rceil \times t$，不大于 $R$ 的最大 $t$ 倍数点为 $v = \left\lfloor\dfrac R t \right\rfloor \times t$。
>
> 从 $u$ 到 $v$ 按照 $t$ 的步长跳跃即可枚举到所有 $t$ 在 $[L, R]$ 内的倍数点，并且无多余枚举。

考虑最坏的情况，$a_i = 1$。这样以来，$S(x)$ 里的所有位置里，每个位置都是所有元素的倍数点。这样以来标记复杂度直接卡满到 $2nk$，我们要处理 $n$ 组小区间，这样总复杂度直接 $n^2k$ 了，不可取。

这意味着若坚持这个做法，我们势必要放弃一些倍数点的记录。下面我给出两种思路，都需要发掘一些性质。

**【思路一】**

性质：如果存在 $a_i \le k$，则任何一个在正整数域上连续的长度为 $k$ 的小区间，都会存在一个 $a_i$ 的倍数点。

该性质可以被一个更强的性质推出：任何一个长度为 $a_i$ 的小区间内，每个数 $\bmod a_i$ 之后恰好构成 $[0, a_i - 1]$ 的整数集。比较明显，不证明了。

因此，$a_i \le k$ 的元素不会影响任何一个小区间的合法性，只需检验是否所有 $a_i > k$ 的元素都存在倍数点落入小区间内。下面，我们称 $a_i > k$ 的元素为 **重要元素**。

这里又有特别好的性质：**单个重要元素的倍数点在任何一个长度不超过 $\boldsymbol k$ 的小区间最多出现一次。**假设它出现了，并且是 $t$，则 $t + a_i$ 和 $t- a_i$ 都不落在小区间内，其它的更不会。

这个性质又可以推出 **单个重要元素的倍数点在任何 $\boldsymbol{S(x)}$ 最多出现两次**，因为 $S(x)$ 的长度不超过 $2k$，拆分成两个长度不超过 $k$ 的小区间，用上面的性质证明即可。

于是，考虑预处理 $\mathrm{cnm}(j)$ 为 $j$ 是多少个 **重要元素** 的倍数点（只关心 $j \in S(x)$）。根据上面的讨论，这个预处理标记的过程复杂度是 $2n$。

> 小细节：因为单个重要元素 $a_i$ 的倍数点在 $S(x)$ 最多出现两次，所以只要尝试标记**【$\boldsymbol{a_i}$ 的不小于 $\boldsymbol{S(x)}$ 左端点的最小倍数点】** 以及**【$\boldsymbol{a_i}$ 的不超过 $\boldsymbol{S(x)}$ 右端点的最大倍数点】**，就能将 $a_i$ 在 $S(x)$ 内部的倍数点都标记好了。这里**【尝试标记点 $\boldsymbol u$】**，意思是如果点 $u$ 落在 $S(x)$ 内就标记，否则忽略。

然后维护信息：当前区间内，存在 $s$ 个重要元素的倍数点，**这里需保证单个重要元素的多个倍数点只被计数一次。**

因为长度为 $k$ 的小区间内部，单个重要元素的倍数点并不会出现多次。因此，当 $r - l = k$ 时，信息 $s = \sum\limits_{j = l}^r\mathrm{cnm}(j)$。

维护同 $\mathrm{cnp}$：在 $r$ 从 $r' - 1$ 转移到 $r'$ 时，$s$ 自增 $\mathrm{cnm}(r')$。$l$ 从 $l'$ 转移到 $l' + 1$ 时，$s$ 自减 $\mathrm{cnm}(l')$。

而一个区间合法，当且仅当 $s$ 与重要元素的数量相等，该判定平凡。

那么本题就做完了。考虑复杂度。

处理每组区间，预处理 $\mathrm{cnp}$ 和 $\mathrm{cnm}$，复杂度 $\Theta(n)$；双指针扫描复杂度 $\Theta(k)$。共有 $n$ 组区间，所以复杂度为 $\Theta(n^2 + nk)$。

**【思路二】**

该思路的关键在于发掘：钦定 $p_x$ 不动时，对于任意一个 $p_i$，做以下三种策略之一不劣于做其它策略：

- 不调整。
- 调整到不大于 $p_x$ 的最大 $a_i$ 倍数点 $u_i$（如果未落入 $S(x)$ 就忽略）。
- 调整到不小于 $p_x$ 的最小 $a_i$ 倍数点 $v_i$（如果未落入 $S(x)$ 就忽略）。

证明：

> 考虑钦定 $p_x$ 不动的策略，你钦定所有元素落入的小区间肯定是包含 $p_x$ 的，左端点在 $p_x$ 左侧，右端点在 $p_x$ 右侧的一个区间。设它是 $[l, l + k]$，即 $l \le p_x$，$l + k \ge p_x$。
>
> 一个元素一旦被调整，就一定会产生 $1$ 的代价，而与它调整的目标位置无关。
>
> 如果我们将 $p_i \ne u_i - ta_i$ 调整到 $u_i - ta_i$，它能落入 $[l, l + k]$，那么有 $u_i - ta_i \ge l$，于是 $u_i \ge l$。又因为 $u_i \le p_x \le l + k$，所以 $u_i$ 也一定能落入 $[l, l + k]$。因为 $p_i \ne u_i - ta_i$，所以将 $p_i$ 调整到 $u_i - ta_i$ 也会产生代价，不劣于将 $p_i$ 调整到 $u_i$。
>
> 对于 $v_i$，同理可证将 $p_i$ 调整到 $v_i + ta_i$ 不劣于 $v_i$。$u_i$ 和 $v_i$ 之间一定不存在其它 $a_i$ 倍数点了，所以所有 $p_i$ 的调整方案都已被讨论，$u_i$ 和 $v_i$ 两种调整方案不劣于其它调整方案。
>
> 当然注意，如果 $p_i = u_i - ta_i$，它可能比 $p_i$ 调整到 $u_i$ 优秀，因为保持 $p_i$ 不动没有代价，调整到 $u_i$ 则有。因此，还有一种策略是不调整，也需要考虑。

综上，我们手动强化条件，任何一个 $p_i$ 都只能保持 $p_i$，或者调到 $u_i$，或者调到 $v_i$。根据上面的讨论，这样的强化不会让原题的最优解发生变动，是可取的。如果这里 $p_i$，$u_i$，$v_i$ 三个点中，某些点不落在 $S(x)$ 里，就直接忽略。这三个点之间可能有相同的点，可以去重一下。

这样以来，任何一个 $a_i$ 都只用标记最多三个倍数点，我们称之为 **重要倍数点**。

我们尝试沿用思路一的策略，设 $\mathrm{cnm}(j)$ 为 $j$ 是多少个 $a_i$ 的某个重要倍数点。然后考虑维护双指针所夹区间内**【有多少个元素，存在一个重要倍数点落在该区间】**，记这个值为 $s$，则区间合法当且仅当 $s = n$。

然而，$r -l = k$ 时，我们不保证 $[l, r]$ 的答案 $s = \sum_{j = l}^r \mathrm{cnm}(j)$，这是因为一个元素的重要倍数点可能落在长度为 $k$ 的小区间内多次，性质并不像思路一那么美好。

不过，这个问题其实等价于经典的数颜色问题。我们考虑 $n$ 种元素对应 $n$ 个颜色，$j$ 是 $a_i$ 的某个重要倍数点等价于 $j$ 这个位置有 $i$ 这种颜色（一个位置可以有多种颜色）。然后问一个区间内部有多少种颜色。

思路一保证了一种颜色只出现在目标区间一次，所以问题简化成对颜色数求和。但事实上，没有这个条件，数颜色种数这个问题用双指针维护也是相当经典简单的。

首先我们更改状态，$\mathrm{cnm}(j)$ 修改成一个集合，它的内容是 $j$ 这个位置的所有颜色种类。然后我们在双指针维护时，新开一个数组 $\mathrm{cnt}(i)$，下标域 $[1, n]$ 的正整数，代表第 $i$ 种元素在当前双指针所夹区间内出现多少次。

然后进行如下维护：

- $r$ 从 $r' - 1$ 转移到 $r’$ 时，将 $r'$ 处的所有颜色 $i$ 进行如下操作：
    - 如果 $\mathrm{cnt}(i) = 0$，则 $s$ 自增 $1$。
    - 将 $\mathrm{cnt}(i)$ 自增 $1$。
- $l$ 从 $l'$ 转移到 $l' + 1$ 时，将 $l'$ 处的所有颜色 $i$ 进行如下操作：
    - 将 $\mathrm{cnt}(i)$ 自减 $1$。
    - 如果 $\mathrm{cnt}(i) = 0$，将 $s$ 自减 $1$。

上面的转移正确性比较明显。其复杂度虽然不能保证每次运动 $\Theta(1)$，但可以保证指针运动的全过程中，复杂度不会超过标记出的所有颜色数，也即 $3k$。均摊下来还是 $\Theta(1)$ 的。

那么这个做法也做完了，复杂度同理是 $\Theta(n^2 + nk)$。

---

下面给出做法一的 AC 代码，最大 234 ms，无任何故意的卡常，还是比较优秀的。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2023-07-11 11:17:47 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2023-07-11 17:58:41
 */
#include <bits/stdc++.h>
#define int long long
inline int read() {
	int x = 0;
	bool f = true;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-')
			f = false;
	for (; isdigit(ch); ch = getchar())
		x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : (~(x - 1));
}
inline bool gmi(int &a, int b) {
	return b < a ? a = b, true : false;
}

const int N = 3005;
int a[N], p[N];
inline int solve() {
	int n = read(), k = read();
	int ans = n, cnt = 0;
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
		cnt += a[i] > k;
	}
	for (int i = 1; i <= n; ++i)
		p[i] = read() * a[i];
	for (int x = 1; x <= n; ++x) {
		std :: vector <int> cnp((k << 1) + 1), cnm((k << 1) + 1);
		// 注意这里一定要开成 k * 2 + 1
		// 如果你平移到从 1 开始，那就得开成 k * 2 + 2
		int L = std :: max(p[x] - k, 1LL), R = p[x] + k;
		auto ins = [&](std :: vector <int>& v, int pos) {
			if (pos >= L && pos <= R)
				++v[pos - L];
		};
		for (int i = 1; i <= n; ++i) {
			ins(cnp, p[i]);	
			int u = (L + a[i] - 1) / a[i] * a[i], v = R / a[i] * a[i];
			if (a[i] > k) {
				ins(cnm, u);
				if (u != v)
					ins(cnm, v);
			}
		}
		int c = std :: accumulate(cnp.begin(), cnp.begin() + k + 1, 0LL);
		int s = std :: accumulate(cnm.begin(), cnm.begin() + k + 1, 0LL);
		for (int l = L, r = l + k; ;) {
			if (s == cnt)
				gmi(ans, n - c);
			++r;
			if (r > R)
				break;
			c += cnp[r - L] - cnp[l - L];
			s += cnm[r - L] - cnm[l - L];
			++l;
		} 
	}
	return ans;
}

signed main() {
	int T = read();
	while (T--)
		printf("%lld\n", solve());
	return 0;
}
```

如果您觉得这篇博客解决了您的问题，写的不错的话，别忘了点个赞！

---

## 作者：zesqwq (赞：6)

赛时数据锅了，导致这题的难度到了 $2500$，实际上是简单的。

如果要使答案 $<n$，那必然要让一些枪的攻击力不变，因此我们可以将枪按照攻击力排序，那么我们保留攻击力的枪必然是一个区间。

然后考虑尺取法，问题变为判定一个保留一个区间的枪的攻击力是否可行。

假设选取的枪攻击力分别为 $[p_L, p_R]$ 那么对于区间外的枪 $x$，情况分为 $2$ 种：

1. 存在 $k$ 使得 $kf_x\in [p_L,p_R]$，此时这把枪经过调整 $d_x = k$ 即可符合要求；
2. 否则，我们发现，这把枪的调整后的攻击力要尽可能靠近 $[p_L,p_R]$，我们维护一个队列，队列中存二元组 $(v, x)$，表示可以将 $p_x$ 取到 $v$。我们将最大的 $k$ 使得 $kf_x < p_L$，建立二元组 $(kf_x,x)$ 放入队列 和 最小的 $k$ 使得 $kf_x > p_R$ 建立二元组 $(kf_x,x)$ 放入队列。然后对于这个队列，我们对第一键值排序后尺取判定是否存在一个状态使得 颜色数 $=$ 放入队列 的颜色数即可。

注意调整后枪的攻击力 $> 0$，不能取到 $0$，可能需要特判。

时间复杂度 $O(n^2 \log n)$，但是常数很小，可以通过。

```cpp
const int N = 3e3 + 10;
int T, n, k;
struct Gun {
    ll d, f, p;
    inline void read() { ::read(d), ::read(f), p = d * f; }
    inline bool operator<(const Gun &b) const { return p < b.p; }
} a[N];
int col[N], top;
pair<ll, int> st[N << 1];
inline bool check(int reward, ll l, ll r) {
    if (!reward) return 1;
    int nr = 0, ccnt = 0, pl = 1;
    memset(col, 0, sizeof(col));
    sort(st + 1, st + top + 1);
    for (int i = 1; i <= top; i++)
        if (st[i].first + k >= r && st[i].first <= l + k) {
            while (nr < i) ccnt += !(col[st[++nr].second]++);
            while (nr < top && st[nr + 1].first <= min(l, st[i].first) + k)
                ccnt += !(col[st[++nr].second]++);
            while (pl < i) ccnt -= !(--col[st[pl++].second]);
            if (ccnt == reward) return 1;
        }
    return 0;
}
inline bool check(int l, int r) {
    if (r > n) return 0;
    if (a[r].p - a[l].p > k) return 0;
    ll lf = a[l].p, rf = a[r].p;
    ll ans = 0;
    top = 0;
    int reward = 0;
    for (int i = 1; i < l; i++) {
        if (a[i].p >= lf && a[i].p <= rf) continue;
        ll L = (lf / a[i].f) * a[i].f,
           R = ((rf + a[i].f - 1) / a[i].f) * a[i].f;
        if (!L) L += a[i].f;
        if (L + a[i].f <= rf || R - a[i].f >= lf) continue;
        st[++top] = {L, i}, st[++top] = {R, i}, ++reward;
    }
    for (int i = r + 1; i <= n; i++) {
        if (a[i].p >= lf && a[i].p <= rf) continue;
        ll L = (lf / a[i].f) * a[i].f,
           R = ((rf + a[i].f - 1) / a[i].f) * a[i].f;
        if (!L) L += a[i].f;
        if (L + a[i].f <= rf || R - a[i].f >= lf) continue;
        st[++top] = {L, i}, st[++top] = {R, i}, ++reward;
    }
    return check(reward, a[l].p, a[r].p);
}
int main() {
    read(T);
    for (int _ = 1; _ <= T; _++) {
        read(n), read(k);
        for (int i = 1; i <= n; i++) read(a[i].f);
        for (int i = 1; i <= n; i++) read(a[i].d), a[i].p = a[i].f * a[i].d;
        int ans = n;
        sort(a + 1, a + n + 1);
        int r = 0;
        for (int i = 1; i <= n; i++) {
            if (r < i) {
                r = i;
                if (!check(i, r)) continue;
            }
            while (check(i, ++r))
                ;
            --r;
            ans = min(ans, n - (r - i + 1));
        }
        write(ans), putc('\n');
    }
    do_flush();
    return 0;
}
```

---

## 作者：hgzxwzf (赞：4)

## [CF1814D](https://codeforces.com/contest/1814/problem/D)

### 解题思路：

如果全都改，那么答案是 $n$。

否则，枚举没有改的位置，假设为 $i$，那么对于任意的 $j$，如果改，最优情况下，$p'_j$ 是大于 $p_i$ 且是 $f_j$ 倍数的最小数或者小于等于 $p_i$ 且是 $f_j$ 倍数的最大数，这样每个数的取值就只有 $O(n)$ 种。

将所有可能得取值排序，从小到大枚举最小值，双指针扫右端点，如果区间中每个位置都出现了，那么可以更新答案。

### Code：

```c++
const int N=3e3+10;

int f[N],d[N],cnt[N],res,n,k,tot;
LL p[N];

struct node
{
	LL val;
	int id,type;
};

void add(node i)
{
	res-=i.type;
	cnt[i.id]++;
	if(cnt[i.id]==1) tot++;
}

void del(node i)
{
	res+=i.type;
	cnt[i.id]--;
	if(!cnt[i.id]) tot--;
}

int work(LL x)
{
	vector<node>vi;
	rep(i,1,n)
	{
		cnt[i]=0;
		vi.push_back({p[i],i,1});
		LL y=x/f[i]*f[i];
		if(y>0) vi.push_back({y,i,0});
		vi.push_back({y+f[i],i,0});
	}
	sort(vi.begin(),vi.end(),[](node &P,node &Q) {return P.val<Q.val;});
	int r=0,ans=n;
	res=n;
	tot=0;
	rep(ni,0,(int) vi.size()-1)
	{
		node i=vi[ni];
		while(r<vi.size()&&vi[r].val<=i.val+k) add(vi[r++]);
		if(ni) del(vi[ni-1]);
		if(tot==n) ans=min(ans,res);
	}
	return ans;
}

void work()
{
	int ans;
	cin>>n>>k;
	ans=n;
	rep(i,1,n) cin>>f[i];
	rep(i,1,n) cin>>d[i];
	rep(i,1,n) p[i]=1ll*f[i]*d[i];
	rep(i,1,n) ans=min(ans,work(p[i]));
	cout<<ans<<endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--) work();
	return 0;
}
```



---

## 作者：KingPowers (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1814D)

首先不难发现一定有解，且答案上界显然为 $n$。具体地，令 $F=\prod_{i=1}^nf_i$，则我们将每个 $d_i$ 调整为 $\frac{F}{f_i}$ 即可使所有的 $p_i$ 相等，也就是将每个 $p_i$ 调整到每个 $f_i$ 的公倍数。

所以我们只需要考虑答案不超过 $n$ 的情况，注意到此时一定会有一把枪的 $p_i$ 不变，考虑去枚举一个不变的 $p_i$，那么为了使极差不超过 $k$，其他枪最终的攻击力 $p_j$ 都要尽可能地“接近”我们钦定不变的那个 $p_i$。

不难发现此时对于其它的每把枪，$p_j$ 只会调整为以下值：

 - 不变，也就是仍为 $p_j$。
 
 - 变为不超过 $p_i$ 且为 $f_j$ 倍数的最大值。
 
 - 变为超过 $p_i$ 且为 $f_j$ 倍数的最小值。
 
显然调整为其他值都不如以上三者之一更优，因此每把枪可能的取值数量之和是 $O(n)$ 的。

考虑把这些取值全都拉出来排序，双指针扫描所有极差不超过 $k$ 的极大区间，如果某个极大区间内的所有取值包含的枪的种类数为 $n$，那么就说明此时 $n$ 把枪都有一个合法的取值，可以更新答案。

时间复杂度 $O(n^2\log n)$，比较卡常。

[提交记录](https://codeforces.com/contest/1814/submission/231086737)

---

## 作者：OldVagrant (赞：1)

## 题意
[翻译已经足够简洁](https://www.luogu.com.cn/problem/CF1814D)。
## Solution
早上断断续续想了一个小时没想出来什么做法，睡了一个小时，出去转了一会想出来一个时间复杂度 $O(nk)$，空间复杂度 $O(n^2)$ 的做法。   

首先，调整 $n$ 把枪一定可以达到目标，令所有 $f_i(i\in[1,n])$ 的最小公倍数为 $L$，则只需要将第 $i$ 把枪的 $d_i$ 调整为 $L/d_i$，此时所有枪的 $p_i$ 相等。   

然后，如果存在更优解，则必定有某一把或多把枪不需要调整，那么我们就可以暴力枚举不调整哪一把枪，接着再去求出此时最多还有多少把枪不需要调整，求完之后更新答案即可。   

瓶颈在于，如何以不高于 $O(n\log n)$ 的复杂度求出不调整第 $i$ 把枪时的答案。  
观察一下数据范围，我们可以发现很奇怪的一点，$k\le 1500$，比 $n$ 还小，这提醒我们使用一种时间复杂度依赖 $k$ 的做法。（$f$ 的范围也很小，如果你能想到什么依赖 $f$ 的做法，欢迎私信我或者直接在评论区指出）   
在不调整第 $i$ 把枪时，最终的状态一定是 $\forall i\in [1,n],p_i\in[l,l+k]$，其中 $l\in [p_i-k,p_i]$。所以如果我们可以在枚举每个合法的 $l$ 的时候都能（均摊也算） $O(1)$ 地更新当前的答案，那么问题就得到解决了。而这是很简单的，只需要维护当前有多少把枪的初始 $p_i$ 在我们所枚举的这个区间 $[l,l+k]$ 内即可，暂且称这个值为 $cnt_l$ ，那么第 $i$ 把枪的答案就是 $n-{ \underset{p_i-k\le l\le p_i} {\max} cnt_l}$。具体实现就是维护当前枚举的区间的左右端点，然后在移动端点的时候更新 $cnt$。    

看起来似乎结束了？但实际上真正的难点不在于求答案，而在于判断一个区间是否合法，因为题目要求所有的枪的 $p_i$ 都必须能在调整后落在我们所枚举的区间内。对于某些区间，会存在若干把枪无法通过调整 $d_i$ 来使得 $p_i$ 落在区间内。所以接下来要做的，就是实时维护是否所有枪的 $p_i$ 都可以落在当前区间内。这需要另开两个数组 $a$ 与 $id$ 作辅助，再进行一次 $O(n^2)$ 的预处理。   

对于第 $i$ 把枪，如果我们不调整它，那么就要把其他枪的 $p$ 调整到越接近 $p_i$ 越好。若要调整第 $j$ 把枪，则分两种情况讨论，一种是调整到小于等于 $p_i$ 的最大值 $a[i][0][j]$，另一种是大于等于 $p_i$ 的最小值 $a[i][1][j]$。这两个值是可以 $O(1)$ 算出来的，利用 `\` 下取整的特性，对于可以得到 `a[i][0][j]=p[i]\f[j]*f[j],y=(p[i]+f[j]-1)/f[j]*f[j]`。注意边界情况，即 `a[i][0][j]==0`，这意味着 $p_j$ 无法调整到比 $p_i$ 小的任何值；`a[i][1][j]-k>p[i]||a[i][0][j]+k<p[i]`，此时无法在不调整 $p_i$ 的情况下使得状态合法。出现边界情况时，应当把 $a[i][0/1][j]$ 赋值为一个不可能出现的数。  

有了 $a$ 数组之后，判断一个区间是否合法，就转化为了是否能使得 $\forall i\in [1,n],\exists a[i][k][j]\in[l,l+k](k\in[0,1])$。这个问题在对 $a[i][0][j]$ 和 $a[i][1][j]$ 内部分别排序后就可以双指针 $O(n)$ 解决。因为排过序了，而判断合法还需要知道每个 $a[i][0/1][j]$ 的原始下标，于是可以在前面预处理的同时用 $id[i][0/1][j]$ 存下 $a[i][0/1][j]$ 的对应下标。再开一个计数数组 $cont$ ，记录每个点的贡献，初始均为 $1$。如果区间的端点移动后，点 $j$ 的原始 $p_j$ 进了区间，或是 $a[i][0/1][j]$ 进了，对 $j$ 记 $-1$ 贡献，而如果 $p_j$ 或是 $a[i][0/1][j]$ 出了区间，则记 $1$ 贡献。不难发现，一个状态合法，当且仅当 $\forall i \in [1,n],cont_i\le 0$，那么维护一下 $cont_i\ge 1$ 的位置数即可。 

而如果 $a[i][0/1][j]$ 的值不为上文提到的那个不可能出现的数，则其值域实际上相当于是 $[p_i-k,p_i+k]$，$p_i$很大，但这个跨度很小，因而我们可以将值域整体左移 $p_i-k$，就变成了对一堆值域为 $[0,2k]$ 的数排序，这就可以使用 $O(k)$ 的桶排序了。至于那些“不可能出现的数”，单独处理（比如，把它们的值都当做 $-1$ 和 $2k+1$ 然后和其他值一同处理）。

至此，我们大体上解决了这道~~基础算法练习~~题。   

这个题细节挺多的，剩下的看代码吧。
## Code
```
#include <bits/stdc++.h>
#define ll long long
#define gc getchar
#define pc(x) putchar(x)
using namespace std;
const ll inf=1ll<<60;
int a[3001][2][3001],id[3001][2][3001],l[3001],r[3001],cnt[3001];
deque<int> col[3001];
int read(){
	int x=0;
	char ch=gc();
	while(ch<48||ch>57) ch=gc();
	while(ch>47&&ch<58) x=x*10+ch-48,ch=gc();
	return x;
}
void write(int x){
    if(x>9) write(x/10);
    pc(x%10+48);
}
struct guns{
	int f,d;
	ll p;
	bool operator<(const guns& b){
		return p<b.p;
	}
}g[3001];
signed main(){
	int t=read();
	while(t--){
		int n=read(),k=read(),ans=n,len=2*k;
		for(int i=1;i<=n;i++) g[i].f=read();
		for(int i=1;i<=n;i++) g[i].d=read(),g[i].p=(ll)g[i].f*g[i].d;
		sort(g+1,g+n+1);
		ll x,y;
		for(int i=1,lcnt=0,rcnt=0,cnt0=0,cnt1=0;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(j==i) continue;
				x=g[i].p/g[j].f*g[j].f,y=(g[i].p+g[j].f-1)/g[j].f*g[j].f;
				if(x==0) x=-inf;
				if(x-g[i].p+k<0) l[++lcnt]=j;
				else col[k+x-g[i].p].push_back(j);
				if(y-g[i].p>k) r[++rcnt]=j;
				else col[k+y-g[i].p].push_back(j);
			}while(lcnt) a[i][0][++cnt0]=-1,id[i][0][cnt0]=l[lcnt--];
			for(int j=0;j<=len;j++){
				if(j==k){
					while(cnt0<n-1&&!col[j].empty()){
						if(id[i][0][cnt0]==col[j].front()){
							a[i][1][++cnt1]=j,id[i][1][cnt1]=col[j].front(),col[j].pop_front();
							continue;
						}a[i][0][++cnt0]=j,id[i][0][cnt0]=col[j].front(),col[j].pop_front();
					}
				}else while(cnt0<n-1&&!col[j].empty()) a[i][0][++cnt0]=j,id[i][0][cnt0]=col[j].front(),col[j].pop_front();
				while(!col[j].empty()) a[i][1][++cnt1]=j,id[i][1][cnt1]=col[j].front(),col[j].pop_front();
			}while(rcnt) a[i][1][++cnt1]=len+1,id[i][1][cnt1]=r[rcnt--];
			cnt0=cnt1=0;
		}for(int i=1,le,ri,j=1,ma,pos0,pos1,nowl,nowr,num,c;i<=n;i++){
			ll origin=g[i].p;
			while(g[j].p+k<g[i].p) j++;
			nowr=i,nowl=j,le=0,ri=k,pos0=1,pos1=0,ma=0,memset(cnt,0,n+1<<2),num=0;
			for(int u=nowl;u<=nowr;u++) cnt[u]--;
			while(ri<=len){
				while(g[nowl].p<origin-k+le){
					cnt[nowl]++;
					if(cnt[nowl]==1) num++;
					nowl++;
				}while(nowr<n&&g[nowr+1].p<=origin-k+ri){
					nowr++,cnt[nowr]--;
					if(cnt[nowr]==0) num--;
				}while(pos0<n&&a[i][0][pos0]<le){
					c=id[i][0][pos0++];
					if(cnt[c]==0) num++;
					cnt[c]++;	
				}while(pos1<n-1&&a[i][1][pos1+1]<=ri){
					c=id[i][1][++pos1];
					if(cnt[c]==1) num--;
					cnt[c]--;
				}if(!num) ma=max(ma,nowr-nowl+1);	
				le++,ri++;
			}ans=min(ans,n-ma);
		}write(ans),pc('\n'); 
	}return 0;
}
```

---

## 作者：cwfxlh (赞：1)

## [CF1814D](https://www.luogu.com.cn/problem/CF1814D)     
不难发现 $ans$ 的上界是 $n$，因为你可以把所有的 $p_i$ 都调到 $f_i$ 的公倍数大小。   
也就是说对于其他的更优解，一定是存在至少一支枪是不修改参数的，因为 $n$ 在 $3000$ 以内，所以不妨枚举这一支枪的编号。  
再考虑如果固定了一支枪 $i$，其他枪有三种选择：不改变，改变到刚好比 $p_i$ 小一点，或者刚好比 $p_i$ 大一点。这是很明显的。    
那么对于不同的选择，对修改次数的贡献也是不同的。第一种的贡献是 $0$，二三种选择的贡献都是 $1$。所以考虑把这 $3n$ 个选项列出来，双指针进行扫描即可。复杂度 $\Theta(n^2\log n)$，当然这题也有 $\Theta(nk)$ 的做法，不过内容差不多。      

2023.6.6 Update：本题解的代码需要使用 C++20 才可通过此题，如果要更优秀复杂度的话，可以选择在列选项的时候进行优化（具体就是按值域写），即 $\Theta(nk)$。感谢 @xcrr 的提醒。

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k,f[3003],d[3003],ans,sum,mn,cz;
int v1[3003],v2[30003],l,r;
int tot,k1,k2,k3,k4,apr[30003][2];
struct pr{
    int val;
    int num;
    int jz;
}stk[300003];
bool comp(pr X,pr Y){
    return X.val<Y.val;
}
void add(int X){
    if(stk[X].jz==0){
        if(apr[stk[X].num][0]==0)cz++;
        else mn--;
        apr[stk[X].num][1]=1;
        return;
    }
    if(apr[stk[X].num][1]!=0){
        apr[stk[X].num][0]++;
        return;
    }
    if(apr[stk[X].num][0]==0){
        cz++;
        mn++;
    }
    apr[stk[X].num][0]++;
    return;
}
void nadd(int X){
    if(stk[X].jz==0){
        if(apr[stk[X].num][0]==0)cz--;
        else mn++;
        apr[stk[X].num][1]=0;
        return;
    }
    if(apr[stk[X].num][1]!=0){
        apr[stk[X].num][0]--;
        return;
    }
    if(apr[stk[X].num][0]==1){
        cz--;
        mn--;
    }
    apr[stk[X].num][0]--;
    return;
}
signed main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld%lld",&n,&k);
        for(int i=1;i<=n;i++)scanf("%lld",&f[i]);
        for(int i=1;i<=n;i++)scanf("%lld",&d[i]);
        ans=n;
        for(int i=1;i<=n;i++){
            tot=0;
            mn=0;
            cz=0;
            for(int j=1;j<=n;j++){
                apr[j][0]=0;
                apr[j][1]=0;
                v1[j]=(f[i]*d[i])/f[j];
                v2[j]=v1[j]+1;
                stk[++tot].val=v1[j]*f[j];
                stk[tot].num=j;
                stk[tot].jz=1;
                stk[++tot].val=v2[j]*f[j];
                stk[tot].num=j;
                stk[tot].jz=1;
                stk[++tot].val=d[j]*f[j];
                stk[tot].num=j;
                stk[tot].jz=0;
            }
            sort(stk+1,stk+tot+1,comp);
            l=1;
            r=1;
            add(1);
            while(r<tot){
                while(r<tot&&stk[r+1].val-stk[l].val<=k){
                    add(r+1);
                    r++;
                }
                if(stk[l].val==0||stk[r].val-stk[l].val>k){
                    l++;
                    nadd(l-1);
                    continue;
                }
                if(cz==n)ans=min(ans,mn);
                l++;
                nadd(l-1);
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：ifffer_2137 (赞：0)

诶诶直接暴力嗯做。
### 题意
有 $n$ 把枪，第 $i$ 把枪的攻击力是 $p_i=f_i\times d_i$。你需要调整 $d_i$ 使得 $\max_{1\le i\le n}p_i−\min_{1≤i≤n}p_i\le k$，要保证 $d_i>0$，求最少调整几把枪的 $d_i$ 可以满足条件。
### 分析
观察到数据范围很小，考虑暴力。

如果存在一把不用调整的枪，则我们枚举这把枪，可以发现举出这把枪后最终可能的取值区间只有 $O(k)$ 种。

所以有用的区间只有 $O(nk)$ 种。我们考虑对每一种 check 合法性并取最优。显然求需要调整的枪的数量是容易的，排序后二分区间即可。

对于一个 $f_i$ ，我们枚举出的区间左端点 $l$ 不合法当且仅当 $l\bmod f_i+k<f_i$，由于对于每把枪 $l$ 的变化是连续的，所以我们对每把枪暴力扫一遍所有 $f_i$，然后弄个 sgt 维护上面那个式子，全局加单点加（处理取模）全局 $\min$，注意到把相同的 $f_i$ 并起来以后单点加只有 $O(k\log k)$ 次，所以总复杂度是 $O(nk\log n\log k)$，但是好像跑出来不算慢。

代码实现还是要注意一些细节。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
#define mkpr make_pair
#define x first
#define y second
#define popcnt __builtin_popcountll
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w?x:-x;
}
template<class T1,class T2>inline bool Cmn(T1 &x,T2 y){return y<x?(x=y,1):0;}
template<class T1,class T2>inline bool Cmx(T1 &x,T2 y){return y>x?(x=y,1):0;}
template<class T>inline void Dbg(T *a,int l,int r){for(int i=l;i<=r;i++)cout<<a[i]<<' ';cout<<'\n';}
mt19937 rnd(time(NULL));
constexpr int inf=0x3f3f3f3f;
constexpr int maxn=3e3+5;
constexpr int maxm=5e3+5;
constexpr int mod=998244353;
constexpr int base=2137;
constexpr int V=1e9;
constexpr int H=18;
constexpr int W=64;
constexpr int Z=26;
constexpr double eps=1e-9;
inline int Redu(int x){return x-(x>=mod)*mod;}
inline void Add(int &x,int y){x=x+y-(x+y>=mod)*mod;}
inline void _Add(int &x,ll y){x=(x+y)%mod;}
inline void Del(int &x,int y){x=x-y+(x<y)*mod;}
inline void _Del(int &x,ll y){x=(x-y)%mod;x+=(x<0)*mod;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int Pow(int a,int x){int s=1;for(;x;x>>=1,a=1ll*a*a%mod)if(x&1)s=1ll*s*a%mod;return s;}
bool Mem1;
int n,k,m,ans;
int f[maxn],ff[maxn],d[maxn];
ll p[maxn],t[maxn];
int a[maxn];
vector<pii> vec[maxn];
class Segment_Tree{
#define ls (o<<1)
#define rs (o<<1|1)
private:
	int mn[maxn<<2],tag[maxn<<2];
	void pushup(int o){mn[o]=min(mn[ls],mn[rs]);}
	void pushtag(int o,int k){tag[o]+=k,mn[o]+=k;}
	void pushdown(int o){
		if(!tag[o]) return;
		pushtag(ls,tag[o]),pushtag(rs,tag[o]);
		tag[o]=0;
	}
public:
	void build(int o,int l,int r,int *a){
		tag[o]=0;
		if(l==r) return mn[o]=a[l],void();
		int mid=(l+r)>>1;
		build(ls,l,mid,a),build(rs,mid+1,r,a);
		pushup(o); 
	}
	void add(int o,int l,int r,int x,int k){
		if(l==r) return mn[o]+=k,void();
		int mid=(l+r)>>1;pushdown(o);
		if(x<=mid) add(ls,l,mid,x,k);
		else add(rs,mid+1,r,x,k);
		pushup(o);
	}
	void all_add(){pushtag(1,1);}
	int query(){return mn[1];}
#undef ls
#undef rs
}sgt;
void Init(){}
void Clear(){}
void Mymain(){
	Clear();
	ans=n=read(),k=read()+1;
	for(int i=1;i<=n;i++) ff[i]=f[i]=read();
	sort(ff+1,ff+n+1);
	m=unique(ff+1,ff+n+1)-ff-1;
	for(int i=1;i<=n;i++) d[i]=read();
	for(int i=1;i<=n;i++) t[i]=p[i]=1ll*f[i]*d[i];
	sort(t+1,t+n+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++) vec[j].clear();
		ll l=p[i]-k+1,r=p[i];
		if(l<=0) r-=l-1,l=1;
		for(int j=1;j<=m;j++) a[j]=k+(l%ff[j]?l%ff[j]:ff[j])-ff[j]-1;
		sgt.build(1,1,m,a);
		for(int j=1;j<=m;j++) if(ff[j]>k) for(ll x=(l+ff[j]-1)/ff[j]*ff[j]+1;x<=p[i];x+=ff[j]) vec[x-l+1].push_back(mkpr(j,ff[j]));
		for(int j=1;j<=k&&l<=p[i];j++,l++,r++){
			for(pii pp:vec[j]) sgt.add(1,1,m,pp.x,-pp.y);
			int x=lower_bound(t+1,t+n+1,l)-t,y=upper_bound(t+1,t+n+1,r)-t-1;
			if(sgt.query()>=0) Cmn(ans,n-(y-x+1));
			sgt.all_add();
		}
	}
	cout<<ans<<'\n';
}
bool Mem2;
signed main(){
	#ifdef LOCAL
	assert(freopen("data.in","r",stdin));
	assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	Init();int _=read();
	while(_--) Mymain();
	cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms\n";
	cerr<<"Memory: "<<(&Mem1-&Mem2)/1024.0/1024.0<<" MB\n";
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

2500![](//图.tk/1)

下文令题中的 $k$ 为 $m$。

显然每个 $d_i$ 都修改，次数就为 $n$。

考虑枚举 $i$，钦定 $d_i$ 不修改，然后枚举 $[l, l + m - 1], l \in [f_i \times d_i - m, f_i \times d_i]$ 为最后所有 $p_k$ 的取值范围（令 $r = l + m - 1$），那么 $[l, r]$ 合法当且仅当 $\forall k \in [1, n], \exists x \in [l, r], a_k \mid x$，也就是 $\forall k \in [1, n], \left\lfloor\frac{r}{a_k}\right\rfloor \ne \left\lfloor\frac{l-1}{a_k}\right\rfloor$。在此基础上修改次数为 $\sum\limits_{k=1}^n [f_k \times d_k \notin [l,r]]$。暴力枚举，复杂度 $O(n^2m)$。

考虑把判定是否合法和统计答案的 $n$ 变成 $\log$。根据抽屉原理，若 $a_k \le m$，$[l, l + m - 1]$ 中至少有一个数是 $a_k$ 的倍数。若 $a_k > m$，$[f_i \times d_i - m, f_i \times d_i + m]$ 中 $a_k$ 倍数的数是 $O(1)$ 个。找到这些数，标记，这样判定就只用查前缀和了；修改次数为 $\sum\limits_{k=1}^n [f_k \times d_k \notin [l,r]]$，很容易发现也可以离散化后前缀和优化。复杂度就变成 $O(nm \log (n + m))$ 了。

[code](https://codeforces.com/contest/1814/submission/205506607)

---

