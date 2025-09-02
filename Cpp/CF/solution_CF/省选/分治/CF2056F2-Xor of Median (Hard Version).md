# Xor of Median (Hard Version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in this version, the constraints on $ t $ , $ k $ , and $ m $ are higher. You can hack only if you solved all versions of this problem.

A sequence $ a $ of $ n $ integers is called good if the following condition holds:

- Let $ \text{cnt}_x $ be the number of occurrences of $ x $ in sequence $ a $ . For all pairs $ 0 \le i < j < m $ , at least one of the following has to be true: $ \text{cnt}_i = 0 $ , $ \text{cnt}_j = 0 $ , or $ \text{cnt}_i \le \text{cnt}_j $ . In other words, if both $ i $ and $ j $ are present in sequence $ a $ , then the number of occurrences of $ i $ in $ a $ is less than or equal to the number of occurrences of $ j $ in $ a $ .

You are given integers $ n $ and $ m $ . Calculate the value of the bitwise XOR of the median $ ^{\text{∗}} $ of all good sequences $ a $ of length $ n $ with $ 0\le a_i < m $ .

Note that the value of $ n $ can be very large, so you are given its binary representation instead.

 $ ^{\text{∗}} $ The median of a sequence $ a $ of length $ n $ is defined as the $ \left\lfloor\frac{n + 1}{2}\right\rfloor $ -th smallest value in the sequence.

## 说明/提示

In the first example, $ n = 10_2 = 2 $ and $ m = 3 $ . All possible sequences with elements less than $ m $ are: $ [0, 0] $ , $ [0, 1] $ , $ [0, 2] $ , $ [1, 0] $ , $ [1, 1] $ , $ [1, 2] $ , $ [2, 0] $ , $ [2, 1] $ , $ [2, 2] $ . All of them are good, so the answer is: $ 0 \oplus 0 \oplus 0 \oplus 0 \oplus 1 \oplus 1 \oplus 0 \oplus 1 \oplus 2 = 3 $ .

In the second example, $ n = 11_2 = 3 $ and $ m = 3 $ . Some good sequences are $ [2, 2, 2] $ , $ [1, 0, 1] $ , and $ [2, 0, 1] $ . However, a sequence $ [2, 0, 0] $ is not good, because $ \text{cnt}_0 = 2 $ , $ \text{cnt}_2 = 1 $ . Therefore, if we set $ i = 0 $ and $ j = 2 $ , $ i < j $ holds, but $ \text{cnt}_i \le \text{cnt}_j $ does not.

## 样例 #1

### 输入

```
6
2 3
10
2 3
11
5 1
11101
7 9
1101011
17 34
11001010001010010
1 1000000000
1```

### 输出

```
3
2
0
8
32
0```

# 题解

## 作者：rsg26 (赞：4)

想了一个小时左右，感觉很牛，但是可能是我水平太低做的比较复杂，但是总体上感觉还算优美的！

**下文的 $k$ 和原题的 $k=\log n$ 不是一个东西，原题中的 $k$ 下文用 $C$ 替代之，请注意辨识。**

## F1

考虑如何去生成一个合法的序列，由于有个 $cnt$ 的大小关系很烦，我们直接随一个 $cnt$ 序列，然后按大小排序后依次升序对应一个 $[0, m)$ 的数，随后对于每个数，我们给其在长度为 $n$ 的序列中随 $cnt$ 个位置即可。

因此我们就可以计数这个序列，具体而言，设出现了了 $k$ 种数 $p_1\le p_2\cdots \le p_k$，其个数分别为 $cnt_1\cdots cnt_k$，我们记录 $s_i=\sum_{i=1}^{i}cnt_i$，序列的个数是 $\prod_{i = 1}^{k}\begin{pmatrix} n-s_{i-1}\\ cnt_i\end{pmatrix}$。

现在看来还是无从下手，但是我们发现题目要求的 xor，这就意味着我们只关心包含某个数作为中位数的序列的个数的奇偶性。那么我们上述的刻画一个序列生成的过程就有一个优势：对于相同的 $k, p, cnt$，我们的中位数是相同的。也就是如果后面那个乘积的式子是个偶数，当前的 $k, p, cnt$ 对答案的影响就可以忽略。

我们思考 $\prod_{i = 1}^{k}\begin{pmatrix} n-s_{i-1}\\ cnt_i\end{pmatrix}$ 何时可以为奇数？很明显需要每一项都是奇数。首先，需要 $\begin{pmatrix} n\\ cnt_1\end{pmatrix}$ 是奇数，根据 Lucas 定理，其成立需要二进制下 $cnt_i\subseteq n$。此时 $n - s_1$ 相当于搞一个 $n_1$ 表示 $n$ 把 $cnt_1$ 对应的位置全变为 0，我们需要 $\begin{pmatrix} n_1\\ cnt_2\end{pmatrix}$ 为奇数，也就要求 $cnt_2\subseteq n_1$。同理我们搞出 $n_2\cdots n_k$，其中 $n_k = 0$，并进行类似的分析，可知 $cnt$ 数组是 $n$ 二进制下不重不漏的划分！也就是说，有：
1. $\forall i, cnt_i\subseteq n$
2. $\forall i, j, cnt_i\operatorname{AND} cnt_j = 0$
3. $\operatorname{OR}_{i=1}^{k}cnt_i = n$

此时看似已经可做很多了，因为我们注意到对于一个符合以上要求的 $cnt$ 数列，其中位数一定是 $p
_k$ 即出现过的最大数。这一点可以由 $n$ 二进制对应的最高位 1 归哪个 $cnt$ 哪个 $p$ 就已经成为了唯一绝对众数，而 $cnt$ 不降看出。同时此情况下 $cnt$ 不可能重复。

显然此时只关心 $n$ 二进制下 1 的个数。因此我们 dp。令 $f_{i, j}$ 表示 $i$ 个数划分 $j$ 个二进制位的方案数，这里 $i$ 的一维是无序的，$j$ 的一维是有序的，因此我们去按二进制为 1 的位从高到低转移。

最后统计答案，我们判断一个数 $x\in [0, m)$ 在满足以上条件的所有序列里作为中位数，即最大值的次数是不是奇数。我们枚举 $x, k$，那么判断 $\begin{pmatrix} x\\ k-1\end{pmatrix}\cdot f_{k, n}$ 的奇偶性即可。最后对于同一个 $x$，不同的 $k$ 求和即可。

由于 F1 数据范围小，所以怎么写都能过，我直接最暴力的做法，$O(mC^2)$。

评测记录：https://codeforces.com/contest/2056/submission/301501162

## F2

数据范围跨度很大，我们考虑优化 dp 很难了，可能需要推一些组合上的性质。

注意到上文的 $f$ 就是第二类 Stirling 数。参考 SPOJ 106，第二类 Stirling 数的奇偶性可以和 Lucas 类似用二进制下是否包含判断。具体的，$f_{i, j} = S(i, j)$ 为奇数当且仅当如下条件成立：令 $t = \lfloor \frac{x+1}{2}\rfloor$，二进制下 $(t-1)\subseteq (j-i+t-1)$。

回顾我们 F1 最后统计答案的部分，我们只调用了 $f_{x,n}$ 即 $S(x, n)$，由于 $n$ 的量级是可以接受的，所以我们先预处理出这些东西的奇偶性。

F1 统计答案部分中，如果一个 $\begin{pmatrix} x\\ k-1\end{pmatrix}\cdot f_{k, n}$ 是奇数，那么这个式子里两部分都是奇数。组合数的部分为奇数，那么有 $(k-1)\subseteq x$。因此，我们对于一个特定的中位数 $x$，需要求 $\operatorname{XOR}_{(k-1)\subseteq x}{f_{k, n}}$，这一部分直接通过上一段预处理的东西做一遍 SOSDP 即可。

此时我们的时间复杂度是 $O(m\log m)$。

我们注意到对于后 $\log C$ 位相同的两个 $x$，他们 $\begin{pmatrix} x\\ k-1\end{pmatrix}\cdot f_{k, n}$ 的奇偶性一定是相同的，因为 $\operatorname{XOR}_{(k-1)\subseteq x}{f_{k, n}}$ 是相同的，因此我们只去枚举 $O(C)$ 个不同的最后 $\log C$ 位，然后后 $\log C$ 位相同的，其他的位不同的所有数一起统计进答案，可以使用前缀 xor 的根据模 4 分讨的 $O(1)$ 计算方法。

总时间复杂度 $O(C\log C)$。

评测记录：https://codeforces.com/contest/2056/submission/301615214

---

## 作者：DengDuck (赞：3)

前置知识：组合数和第二类斯特林数模 $2$ 的计算方式。

注意到最大的数字出现次数应该最多，所以 $\text{Cnt}_{\max}\geq \text{highbit}(n)$，$\text{highbit}(n)$ 表示 $n$ 二进制最高位。

由于 $2\times\text{highbit}(n)>n$，于是中位数必然是最大值。

推广一下我们发现答案应该和 $n$ 没关系，我们关心 $b=\text{popcount}(n)$ 就行了。

考虑枚举出现的最大数字 $x$，出现数字的总数 $k$。

我们把二进制分配到 $k$ 个集合里再排序就满足条件了，所以中位数是 $x$ 的方案数为：
$$
f(x)=\sum_{k=1}^m {b\brace k}\binom{x}{k-1}
$$
注意到这题是把东西都异或起来，所以我们只关心上面那玩意的奇偶性，相当于模 $2$，所以后面那个组合相当于二进制下 $k-1\in x$。

换而言之，我们可以把上面的式子换成这个形式：
$$
f(x)=\sum_{k\in x}^m {b\brace k+1}\pmod 2
$$
直觉上这是一个高维前缀和，问题是 $x$ 很大，动动脑子发现 $b$ 不大，所以有用的 $k\leq 2^{18}$，你 $x$ 多出来的位都没用的。

换句话说就是 $x\geq2^{18}$ 时 $f(x)=f(x\bmod 2^{18})$。

所以我们枚举 $x\in [0,2^{18}-1]$，并计算整个同余等价类的 $f(x)$，然后求异或和是简单的。

顺便，这题有视频讲解，大家关注一下 B 站 @小猫和小鸭训练中心 谢谢喵。

---

## 作者：int08 (赞：2)

## 前言
好题，考察知识点的综合运用。

"[_cherish_](https://music.163.com/song?id=1909956662)"
# Solution
### F1 Solution
拿到题目，我的第一反应是：先做枚举中位数之类的操作，考虑这个中位数的贡献次数，这样这道题就变成了一道**对 $2$ 取模**的序列计数题。

不过这个序列长度大得有点过分了，不可能是直接做，我绝对忽略了什么。

先做 $n$ 比较小的情况，获得一个多项式做法就行。那么我可以枚举每个数的选择次数做背包，中位数就是让背包超过一半的那个数。

不过我发现当每个数选择次数固定的时候，序列的排列方式还涉及一个多项组合数。

这时候是一个难点：需要知道一个经典结论：$\binom{x}{y}\equiv1(\text{mod } 2)$ 等价于 `x&y==y`，证明考虑运用 Lucas 定理拆为每一位的组合数的乘积。

根据该结论，我发现了一个惊人的事实：$cnt$ 一定形如 $n$ 所有为 $1$ 的位的一种划分，否则那个多项组合数值模 $2$ 必为 $0$。

感觉这个结论很牛，至少让 $n$ 不再是天文数字。

(**在下面的分析里，$n$ 变为非零位的数量**)

而且由于是划分，$cnt$ 数组的大小直接由最高位决定了。

进一步，容易发现，占到最高位的那个数，由于在整个序列中的出现次数超过一半，一定也是中位数。又因为它是出现最多的那个数，而 $cnt$ 数组递增，所以序列的最大值就是中位数。

于是考虑设计 dp：$dp_{i,j}$ 表示考虑到从高往低第 $i$ 个非 $0$ 位，前 $i$ 位已经分配给了 $cnt$ 数组中前 $j$ 大的方案数。

考虑转移：要么把这一位分配给一个新的位置（$dp_{i,j}\to dp_{i+1,j+1}$），要么分配给前 $j$ 个中的任何一个都可以（$dp_{i,j}\times j\to dp_{i+1,j}$）（为什么？因为不是最高位不影响相对大小）。

接下来就很简单了，枚举序列最大值 $i$ 和 $cnt$ 数组中非零位置的数量 $j$，$i$ 的贡献次数为 $dp_{n,j}\binom{i}{j-1}$，因为剩下 $j-1$ 个位置可以按大小顺序任意置于小于 $i$ 的数中。

[F1 AC Code](https://codeforces.com/problemset/submission/2056/306604209)，复杂度 $O(k(k+m))$。

### F2 Solution
上面的做法前后两部分在 F2 都不可接受，分别优化。

虽然我没有注意到那个 dp 是第二类斯特林数，还是优化出来了：

考虑前半部分的 dp 在模 $2$ 意义下可以等价于下面这张图片：

![](https://cdn.luogu.com.cn/upload/image_hosting/6kh3ejdl.png)

（$j$ 是偶数时候向上的箭头消失了）

这和格路计数并无区别，其中一维除以 $2$ 罢了。

于是前半部分优化到 $O(n)$。

考虑后半部分的式子 $\oplus_{i=0}^{m-1}\oplus_{j=1}^{\min(n,i+1)}i\cdot (dp_{n,j}\binom{i}{j-1}\mod 2)$。

假设 $x$ 为最小的 $2^y>n$，再次根据上文结论，我发现 $i$ 加上 $x$ 的倍数答案不变，因为 $x$ 往上的位没有用，加上一个就让 $j$ 大于 $n$ 了。于是 $i$ 只需要枚举到 $x-1$，贡献形如一个公差为 $x$ 的等差数列求异或。

而 $j-1$ 必须是 $i$ 的子集，考虑直接枚举子集，于是最终复杂度 $O(k^{\log_23})$。

进一步由于系数相等，可以 Sosdp。

## AC Code
最短解，大家都喜欢。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,k,m,i,j,n,dp[1<<19];
int C(int x,int y) {return (x&y)==y;}
int calc(int x)
{
	if(x<=1) return 0;
	int h=1<<__lg(x);
	return calc(x-h)^(h==2)^(((x-h)&1)*h);
}
string s;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>k>>m>>s;n=0;
		for(auto x:s) n+=(x=='1');
		k=1<<__lg(n)+1;
		for(i=1;i<=n;i++)
		{
			int x=(i-1)/2,z=n-i;
			dp[i]=C(x+z,z);
		}
		int ans=0;
		for(i=0;i<k;i++)
		{
			int an=dp[1];
			for(j=i;j;j=(j-1)&i) an^=dp[j+1];
			if(!an) continue;
			int cnt=(m+k-i-1)/k;
			if(cnt&1) ans^=i;
			ans^=calc(cnt)*k;
		}
		for(i=1;i<=n;i++) dp[i]=0;
		cout<<ans<<"\n";
	}
}
```
# The End.

---

## 作者：rlc202204 (赞：0)

**题意：**

定义一个序列是好的，当且仅当：

- 对于任意两个不同的 $i,j$ 满足 $i,j$ 都出现了至少一次，如果 $i < j$，则 $i$ 的出现次数不多于 $j$ 的出现次数。

求所有长度为 $N$，值域在 $[0,m)$ 的好的整数序列的中位数的异或和。中位数定义为排序后第 $\lfloor\frac{n+1}{2}\rfloor$。

$N$ 以二进制形式给出，$\log_2 N \le 2 \times 10^5,m \le 10^9$。

**题意：**

注意到这题求的是异或和，这意味着如果某个方案出现了偶数次相当于没有出现。

序列是否有序不影响好坏，但是计数的时候是有序的。

对于所有出现的数，不妨设出现次数是 $cnt_1,\dots,cnt_k$，方案数是：

$$
\binom{N}{cnt_1,cnt_2,\dots,cnt_k}
$$

如果这个东西是偶数，那么显然是不会计入答案的。

这是一个多项式系数，可以表示为若干个二项式系数的乘积，也就是组合数：

$$
\binom{N}{cnt_1}\binom{N-cnt_1}{cnt_2}\dots \binom{N - cnt_1-cnt_2-\dots,-cnt_{k-1}}{cnt_k}
$$

奇偶性相当于对 $2$ 取模，而组合数对小质数取模考虑 Lucas 定理。

如果最终是奇数，就要求 $cnt_1$ 在二进制每一位上都 $\le N$ 的每一位，$cnt_2$ 在二进制每一位上都 $\le N-cnt_1$ 的每一位，以此类推。

而注意到 $\sum_i cnt_i = N$，所以这个限制本质上就是 $cnt_1,cnt_2,\dots,cnt_k$ 构成了 $N$ 的所有 $=1$ 的二进制位的划分。那么显然出现次数最多的数严格大于一半，所以中位数就是出现次数最多，也就是最大的那个数。

这样就非常好做了，也成功理解了题目为什么给我们 $N$ 的二进制表示。不妨设 $n$ 表示 $N$ 的二进制下 $=1$ 的位置的个数，

先不管复杂度，我们考虑枚举 $0 \le k < m$，设计一个 dp：$f(i,j,x)$ 表示当前分完了前 $i$ 位，当前所有有 $j$ 个数，最小的一个是 $x$。

如果这一位是 $0$，则直接 $i \to i+1$ 复制过去，否则，有两种可能：

- $j$ 个数中某个数拿走，由于是二进制，所以不会影响大小关系。$f(i,j,x) \to j \times f(i+1,j,x)$。

- 新增一个 $< x$ 的数，$f(i,j,x) \to f(i+1,j,t)(t < x)$。

这样 dp 是 $O(nm^3)$，因为还要枚举 $k$，连 F1 都过不了。

但是注意到这很没必要，每个 $k$ 都要单独计算，所以我们把状态反过来定义，$f(i,j,x)$ 表示前 $i$ 位之后的都确定了，前 $i$ 位有 $j$ 个数，最小的是 $k$。

这样就变一次 $dp$ 即可统计答案，时间复杂度 $O(nm^2)$。可以过掉 F1。

但是 F2 的数据范围很大，我们上面的做法枚举了 $k$，这是 $O(m)$ 的，显然无法接受，我们考虑如何将这个 $k$ 融入到 dp 的贡献中。

注意到实际上 $j$ 的范围是 $n$ 而不是 $m$，这意味着实际上我们可以将 $k,j$ 相同的视作一种方案，最后乘上 $\binom{k}{j-1}$ 即可。

我们发现一个事：实际上 dp 的时候 $x$ 不影响转移系数，我们考虑化成两维：设 $f(i,j)$ 表示前 $i$ 位之后已经确定，前 $i$ 位有 $j$ 个数的总贡献是多少。

转移类似：

- 当 $j$ 是奇数的时候，可以 $f(i+1,j) \to f(i+1,j)$。

- 也可以 $f(i+1,j+1) \to f(i+1,j)$。

关键是如何设定初值？

注意到对于初始固定了要选 $j$ 个数的方案，$k$ 可行当且仅当 $\binom{k}{j-1}$ 是奇数，如果是奇数我们才计入贡献。

这样 dp 就是 $O(nm)$ 的了，但是依然和 $m$ 有关。

那么我们需要将初值和 dp 两部分分别优化。

观察这个 dp 的式子，我们发现从 $j$ 的变化是这样的：每一次 $j$ 是偶数只能变成 $j+1$，否则可以变成 $j,j+1$ 中的一个，最终会变成某个 $k$。

也就是 $n$ 长度的一个序列：$1,1,1,2,3,3,3,4,5,5,5,\dots$ 这样的。

注意到 $1 \sim k$ 一定至少出现一次，而奇数还可以多出现几次，设有 $t$ 个奇数，则相当于求解不定方程 $x_1+x_2+\dots+x_t = n - k$，这个可以组合数直接计算，注意到我们只关心奇偶性，所以可以直接拆位 $O(\log n)$ 计算。

所以如果我们能求出初值，我们也能求出最终的方案，$O(n)$ 枚举一共选了几个数即可。

现在我们考虑怎么求初值，相当于求 $0 \le t < m,\binom{t}{j-1}$ 为奇数的 $t$ 的异或和。我们注意到这就是要求 $t$ 的每一位都 $\ge j-1$ 的每一位，我们可以直接数位 dp，设 $f(i,0/1),g(i,0/1)$ 分别表示前 $i$ 位是否贴着上界的方案数和总贡献，转移的时候如果某一位填了 $1$ 并且前面的方案数是奇数就可以给贡献加上这一位。

这样我们就能在 $O(\log m)$ 的时间内计算出初值，从而在 $O(n \log m)$ 的时间内解决这个问题。


```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;

int C(int n, int m) {//计算模 2 的余数 
	if (n < m)
		return 0;
	if (n == 0 || m == 0)
		return 1;
	for (int j = 20; j >= 0; j--)
		if ((n >> j & 1) < (m >> j & 1))
			return 0;
	return 1;
}
int CC(int n, int m) {//总和为 n，m 个变量 
	return C(n + m - 1, m - 1);
}

const int k = 30;

int n, m;

int num[2][35] = {{0}};
int f[35][2] = {{0}};
int g[35][2] = {{0}};
void add(int &x, int y) {
	x ^= y;
}

int cal(int t) {
	for (int j = k; j >= 1; j--)
		num[1][j] = (t >> (j - 1) & 1);
	memset(f, 0, sizeof f), memset(g, 0, sizeof g);
	f[0][0] = 1;
	for (int j = 1; j <= k; j++) {
		//转移 f[j][0]
		if (f[j - 1][0])
			add(g[j][0], (1 << (j - 1)));
		if (num[1][j]) {
			add(f[j][0], f[j - 1][0]);
			add(g[j][0], g[j - 1][0]);	
		}
		//转移f[j][1] 
		if (num[0][j]) {//一定可以填 1 并且一定贴上界 
			add(f[j][1], f[j - 1][1]);
			add(g[j][1], g[j - 1][1]);
			if (num[0][j] && f[j - 1][1])
				add(g[j][1], (1 << (j - 1)));
			if (!num[1][j]) {
				add(f[j][1], f[j - 1][0]);
				add(g[j][1], g[j - 1][0]);
			}
		}
		else if (num[0][j] == num[1][j]) {
			add(f[j][1], f[j - 1][1]);
			add(g[j][1], g[j - 1][1]);//填 0 
		}
//		cout << j << " ?? " << f[j][0] << " g:" << g[j][0] << " ?? f: " << f[j][1] << " g: " << g[j][1] << endl;
	}
	return g[k][1];
}
void slv() {
	scanf("%d%d", &n, &m);
	int t = 0;
	for (int i = 0, x; i < n; i++)
		scanf("%1d", &x), t += x;
	for (int j = k; j >= 1; j--)
		num[0][j] = (m >> (j - 1) & 1);
	n = t;
	int ans = 0;
	for (int i = 1; i <= n; i++) 
		if (CC(n - i, (i + 1) / 2))
			ans ^= cal(i - 1);//i - 1的所有贡献
	printf("%d\n", ans);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		slv();	
	return 0;
}
/*
1
2 3
10
*/
```

---

## 作者：masonpop (赞：0)

困难 *3000。

用 $c$ 代替题面中的 $\text{cnt}$，因为不想打 `\text{}`。

考虑如何通过 F1。

注意到题目要求的是异或，而在 $c$ 数组确定时中位数 $x$ 也是确定的。因此我们要考虑的，就是对于一个指定的 $c$ 数组，有多少个合法的原数组，并且只需要考虑这个值的**奇偶性**。而这个值显然就是多重集全排列，即

$$\begin{aligned}\dbinom{n}{c_0,c_1,\cdots,c_{m-1}}\operatorname{mod}2\end{aligned}$$

由卢卡斯定理的经典结论，设 $n$ 中为 $1$ 的二进制位的集合是 $S$，则这个式子为 $1$ 当且仅当 $c_0,c_1,\cdots,c_{m-1}$ 不重不漏的划分了 $S$。即，$S$ 中每一位都恰属于一个 $c_i$。

考虑最大的 $c$，设为 $c_x$。则一定有 $2c_x\ge n$，因为 $c_x$ 包含了 $n$ 的最高位。那么中位数其实就是 $x$。

由于 F1 中 $m,k$ 较小，可以枚举一些东西。尝试枚举非零元的数量 $y$，那么划分 $S$ 的方案数直接可以用斯特林数计算。然后就是把划分出来的数按大小关系填进 $c$ 里面去，显然只需选位置就行，又因为最大值在 $x$ 处，因此这部分方案数就是 $\dbinom{x}{y-1}$。

到这里可以得到最终答案表达式：

$$\begin{aligned}\bigoplus_{y=1}^{\min(m,|S|)}\end{aligned}\bigoplus_{x=0}^{m-1}\left[\dbinom{x}{y-1}\begin{Bmatrix}|S|\\y\end{Bmatrix}\operatorname{mod} 2\right]\times x$$

直接实现上式就是 $O(km)$ 的，可以通过 F1。

继续做的话首先需要前置知识：

$\dbinom{n}{m}$ 为奇数等价与 $n\operatorname{and} m=m$。

$\begin{Bmatrix}n\\m\end{Bmatrix}$ 为奇数等价于 $(n-m)\operatorname{and} {\lfloor\frac{m-1}{2}\rfloor}=0$。

（前者是卢卡斯定理，后者可以考虑递推公式中 $m$ 的奇偶性证明。）

考虑继续优化。发现如果对某个特定的 $x$，能快速找出对应的 $y$ 的贡献总和就很好。利用上述结论可知，设 $f(y)=\begin{Bmatrix}|S|\\y+1\end{Bmatrix}\operatorname{mod} 2$，则 F1 中的式子可以进一步化简为

$$\begin{aligned}\bigoplus_{x=0}^{m-1}x\times \left[\left(\bigoplus_{y\subset x}f(y)\right)\operatorname{mod} 2\right]\end{aligned}$$

这里的 包含符号 是二进制意义下的。

看上去还是要枚举 $x$，但实际上由于 $y$ 很小，设 $r=\log |S|$，后面那个求和式子的值只跟 $x$ 的后 $r$ 位有关。枚举这些位，发现我们要算一个 $0\oplus 1\oplus 2\cdots \oplus w$ 的形式，这是容易的，分类讨论一下就行。

子集的 $f$ 之和显然可以高维前缀和。

至此我们以 $O(k\log k)$ 的复杂度解决了 F2。[F2 submission](https://codeforces.com/contest/2056/submission/303870014)。

---

