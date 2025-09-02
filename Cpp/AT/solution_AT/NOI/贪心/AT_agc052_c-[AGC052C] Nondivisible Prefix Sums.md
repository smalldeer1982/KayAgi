# [AGC052C] Nondivisible Prefix Sums

## 题目描述

给定一个素数 $P$，这是你讨厌的数字。

对于一个整数序列 $A_1,\ A_2,\ \dots,\ A_N$，如果可以重新排列这些元素，使得任意前缀和都不能被 $P$ 整除（即，重新排列后，对于所有 $1 \le i \le N$，都不存在 $A_1 + A_2 + \dots + A_i \equiv 0 \pmod{P}$），那么称这个序列为**好**序列。

长度为 $N$ 的整数序列，每个元素都在 $1$ 到 $P-1$ 之间（包含 $1$ 和 $P-1$），这样的序列一共有 $(P-1)^N$ 种。请问其中有多少个**好**序列。

由于答案可能非常大，请输出其对 $998244353$ 取模的结果。

## 说明/提示

## 限制条件

- $1 \le N \le 5000$
- $2 \le P \le 10^8$
- $P$ 是素数。

## 样例解释 1

好序列有 $[1,\ 1]$，$[1,\ 2]$，$[1,\ 3]$，$[2,\ 1]$，$[2,\ 2]$，$[2,\ 4]$，$[3,\ 1]$，$[3,\ 3]$，$[3,\ 4]$，$[4,\ 2]$，$[4,\ 3]$，$[4,\ 4]$ 共 $12$ 种。

## 样例解释 2

好序列有 $[1,\ 1,\ 1,\ 2]$，$[1,\ 1,\ 2,\ 1]$，$[1,\ 2,\ 1,\ 1]$，$[2,\ 1,\ 1,\ 1]$，$[2,\ 2,\ 2,\ 1]$，$[2,\ 2,\ 1,\ 2]$，$[2,\ 1,\ 2,\ 2]$，$[1,\ 2,\ 2,\ 2]$ 共 $8$ 种。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 5```

### 输出

```
12```

## 样例 #2

### 输入

```
4 3```

### 输出

```
8```

## 样例 #3

### 输入

```
5000 99999989```

### 输出

```
51699346```

## 样例 #4

### 输入

```
2021 307```

### 输出

```
644635349```

# 题解

## 作者：jun头吉吉 (赞：13)

## 题意
给定 $N,P$，一个数组 $A_1,\dots,A_N$ 是好的当且仅当：

- $1\le A_i<P$
- 存在一种重排方式使得 $\forall i\in[1,n],\sum_{j=1}^iA_j\not\equiv0\pmod P$

求好的数组数量。

$1\le N\le5000,2\le P\le10^8$ 且为素数。

## 题解
首先一个好的数组，所有元素的和不能是 $P$ 的倍数。接下来只考虑和不为 $P$ 的倍数的数组。

假设 $1$ 是出现次数最多的元素，出现了 $N-M$ 次（如果不是 $1$ 乘上最多的数的逆元即可），剩下的数为 $B_1,B_2,\dots,B_{M}$，那么有解的充要条件是：
$$
N-M\le(P-B_1)+(P-B_2)+\dots+(P-B_M)+P-1
$$
 必要性是显然的，考虑如果不满足，则 $\sum A_i=N-M+\sum B_i\ge (M+1)P$，又因为不为 $P$ 的倍数所以至少是 $(M+1)P+1$，跨过 $P,2P,\dots,(M+1)P$ 的时一定不能用 $1$，但是不为 $1$ 的只有 $M$ 个所以就寄了。

然后充分性，考虑一种构造方法，设 $x$ 是当前众数，$sum$ 为已经确定的和

- 如果 $sum+x\not\equiv0\pmod P$，那么在末尾附加 $x$
- 否则取任意不为 $x$ 的元素 $y$，在末尾加上 $y,x$

可以证明这个算法不会寄。假设寄了，那么一定是 $sum+x\equiv 0\pmod P$ 且剩下的数只有 $x$。然后因为和不是 $P$ 的倍数所以至少有两个。不难发现这个过程中，如果一个数是众数，那么之后它的个数不会比众数的个数少超过 $1$，因此可以断定 $x=1$，且 $1$ 一直是众数。

所以情况现在是这样的：
$$
\overbrace{1,\dots,1}^{P-1},B_1,\overbrace{1,\dots,1}^{P-B_1},B_2,\overbrace{1,\dots,1}^{P-B_2},\dots,B_M,\overbrace{1,\dots,1}^{P-B_M},\overbrace{1,1}^{\ge2}
$$
 但是这个不满足上面的条件。所以我们断定不会出现这种情况。

这样我们就证明了条件的充分性。

然后计数就简单了。首先考虑和不为 $P$ 的数组怎么计算。不妨设 $a_n$ 为和为 $P$ 的倍数的长度为 $n$ 的数组数量，$b_n$ 为不为 $P$ 的倍数的长度为 $n$ 的数组数量 $/(P-1)$，也就是对任意 $1\le y<P$，$\sum A_i\equiv y\pmod P$ 的方案数，有转移：
$$
\begin{aligned}
&a_{n+1}=(P-1)b_n\\
&b_{n+1}=a_n+(P-2)b_n
\end{aligned}
$$
意义是显然的。

最后我们得到 $(P-1)b_N$ 表示长度为 $N$ 的非 $P$ 倍数的个数。然后考虑减去不符合条件的。

设 $f_{i,j}$ 表示 $\sum_{j=1}^i P-B_i=j$ 的 $\{B_1,\dots,B_i\}$ 数量。这个就是一个背包，然后答案就是：
$$
\sum_{i=0}^N\sum_{j=0}[N-i-j\not\equiv 0\pmod P][N-i>j+P-1]f_{i,j}\binom Ni(P-1)
$$
前两个条件就是和不为 $p$ 的倍数且不符合条件，然后乘 $\binom Ni$ 表示选出不为 $1$ 的位置，然后因为众数不一定为 $1$ 所以还要乘上 $p-1$。这个不会算重是因为此时的众数一定是绝对众数了。

因为有用的 $j$ 的值域是 $\mathcal O(N)$ 的所以复杂度 $\mathcal O(N^2)$。

## 代码
```cpp
const int N=5e3+10;
int n,p;mint fac[N],ifac[N],f[N],sum[N],a=1,b=0,res;
mint C(int n,int m){return fac[n]*ifac[m]*ifac[n-m];}
signed main(){
	fac[0]=ifac[0]=1;for(int i=1;i<N;i++)fac[i]=fac[i-1]*i,ifac[i]=1/fac[i];
	read(n,p);
	for(int i=1;i<=n;i++)tie(a,b)=mp((p-1)*b,a+(p-2)*b);
	res=(p-1)*b;
	f[0]=1;if(n%p&&p<=n)res-=(p-1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++)sum[j]=f[j];
		for(int j=1;j<=n;j++)sum[j]+=sum[j-1];
		memset(f,0,sizeof f);
		for(int j=1;j<=n;j++){
			f[j]=sum[j-1]-(j-(p-2)-1>=0?sum[j-(p-2)-1]:0);
			if((n-i-j)%p!=0&&n-i>=p+j)res-=f[j]*C(n,i)*(p-1);
		}
	}
	writeln(res.x);
}
```

---

## 作者：zhiyangfan (赞：6)

> [AGC052C] Nondivisible Prefix Sums
>
> 对于质数 $p$，定义一个长为 $n$，值域为 $[1,p-1]$ 中整数的序列 $a$ 是好的，当且仅当存在一个 $1$ 到 $n$ 的排列 $\mathcal{P}$ 满足：
> - 对于所有的 $1\le i\le n$，都有 $\sum\limits_{j=1}^i a_{\mathcal{P}_j}$ 不是 $p$ 的倍数。
>
> 给出 $n,p$，求有多少好的序列。($1\le n\le 5\times 10^3,1\le p\le 10^8$)

注意到这个任意重排的限制很松，所以我们来考虑什么样的序列即使在这么松的限制下都不是好的。

显然，如果 $a$ 的序列和是 $p$ 的倍数，那就寄了，接下来我们不考虑这种情况。然后我们考虑把任意重排的过程视为不断从其中选择一个元素，则我们考虑坏的情况一定是我们被强制选择一个刚好使得当前序列模 $p$ 余 $0$。而能使得序列非法的数只有一个，也就是说，只有在剩下的数全部相同时才会出现这种情况。

这启发我们，坏的序列一定是存在某个数出现了太多次。不妨设这个数为 $1$。（这样比较好分析，对于其他数 $x$ 的情况，我们只需要乘一个 $x$ 的逆元就能转化到这里了，显然序列的好坏不变）不妨设剩下 $>1$ 数形成的序列为 $b$。

注意到手里剩下太多相同的数会出问题，所以我们优先打出 $1$。这里可以打出 $p-1$ 个。然后我们打出 $b_1$，之后又能打出 $p-b_1$ 个 $1$。以此类推，我们最多能消耗掉 $p-1+\sum\limits_i p-b_i$ 个 $1$。我们考虑如果 $1$ 不到这个数会不会出问题。考虑 $1$ 用完的时刻，此时由于 $1$ 是原来的众数，所以剩下所有数的出现次数都不超过这个值，这样变成了一个类似的子问题，且限制更松。所以可以发现，$1$ 的个数不超过上述上界是好序列的必要条件。

既然发现一个必要条件，我们来考虑这个条件是否充分。注意到事实上我们需要跳过 $kp,k\in \mathbb{N}_+$ 这些地方，而每次跳过都需要一个 $>1$ 的数，而由于 $1$ 的个数超过上述上界，所以整个序列的和至少是 $(|b|+1)p+1$，即我们需要跳过至少 $|b|+1$ 次 $p$ 的整数倍，而只有 $|b|$ 个数给我们用，显然无解。

所以 $1$ 的个数不超过 $p-1+\sum\limits_i p-b_i$ 且 $1$ 是众数是序列是好的的充要条件。

我们考虑怎么对这个东西计数。$1$ 是众数的条件非常难受，且注意到假设我们直接设朴素状态 $f_{i,j}$ 表示长为 $i$ 的序列，$\sum p-x$ 为 $j$ 的方案数，统计答案的时候需要统计 $n-i\le j+p-1$，这东西 $j$ 可以很大，无法统计。

事实上，就像我们刚刚说的，好的序列看起来就很多。所以我们不妨反过来统计坏的序列。此时首先 $n-i>j+p-1$ 的话，$j$ 就有一个显然的很小的上界。不仅如此，注意到一旦 $1$ 的个数大于上界，显然 $1$ 一定是绝对众数。所以我们的统计就变得简单多了。

按照上述 $\rm dp$ 朴素转移，每次选择的数值域是 $[1,p-2]\cap \mathbb{Z}$，前缀和优化转移即可。得到完整的 $f_{i,j}$ 后，如果 $n-i\ge j+p$ 且 $n-i\not\equiv j\pmod{p}$，就把 $f_{i,j}\binom{n}{i}$ 统计入坏序列个数。然后我们对这一部分的序列，需要乘上 $p-1$。注意到此时如果是坏序列，绝对众数是唯一的，所以不会算重。

接下来的问题变为了如何求出和为 $p$ 的倍数的序列。我们考虑一项一项填，只要前 $i-1$ 项之和不是 $p$ 的倍数，第 $i$ 项就有唯一的填的方案。通过递推可得长度为 $n$ 的序列方案为：
$$\sum_{i=1}^{n-1}(p-1)^i(-1)^{n-1-i}$$
等比数列求和可得方案数为：
$$\dfrac{(p-1)^n+(-1)^n(p-1)}{p}$$
所以坏的序列个数我们就求完了，减一下即可。

时间复杂度 $\mathcal{O}(n^2)$。
```cpp
#include <cstdio>
#include <algorithm>
const int N = 5e3 + 10, mod = 998244353; int f[N][N], C[N][N], pre[N];
inline int sum(int l, int r) { return (pre[r] + mod - (!l ? 0 : pre[l - 1])) % mod; } 
inline void mo(int& x) { x >= mod ? x -= mod : x; }
inline int ksm(int a, int b)
{
	int ret = 1;
	while (b)
	{
		if (b & 1) ret = 1ll * ret * a % mod;
		a = 1ll * a * a % mod; b >>= 1;
	}
	return ret;
}
int main()
{
	int n, p; scanf("%d%d", &n, &p);
	f[0][0] = C[0][0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}
	for (int i = 0; i <= n; ++i) pre[i] = 1;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			f[i][j] = sum(std::max(0, j - p + 2), j - 1);
		pre[0] = 0;
		for (int j = 1; j <= n; ++j)
			pre[j] = (pre[j - 1] + f[i][j]) % mod;
	}
	int tot = 0;
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n; ++j)
			if (n - i >= j + p && (n - i) % p != j % p) 
				mo(tot += 1ll * f[i][j] * C[n][i] % mod);
	tot = 1ll * tot * (p - 1) % mod;
	mo(tot += 1ll * ksm(p, mod - 2) * (ksm(p - 1, n) + ((n & 1) ? (mod - p + 1) : (p - 1))) % mod);
	int ans = (ksm(p - 1, n) + mod - tot) % mod;
	printf("%d\n", ans); return 0;
}
```

---

## 作者：zhiyin123 (赞：5)

# 简要题意

给定一个素数 $P$，这是你讨厌的数字。

对于整数序列 $A_1,\ A_2,\ \dots,\ A_N$，如果可以重新排列元素使得任意前缀和都无法被 $P$ 整除，则称该列为**良好**序列（即，重新排列后，不存在 $1\ \le\ i\ \le\ N$ 使得 $A_1\ +\ A_2\ +\ \dots\ +\ A_i \equiv 0 \pmod{P}$）。

元素范围在 $1$ 到 $P-1$ 之间的长度为 $N$ 的整数列的总数是 $(P-1)^N$ 种，其中**良好**序列的数量又有多少呢？

由于答案可能非常大，请输出结果对 $998244353$ 取余后的值。

$1\leq N\leq 5000$，$2\leq P\leq {10}^8$，$P$ 是素数。

# 一

不妨定义**非**“良好序列”为**坏序列**，那么可以轻松找到坏序列的一个**充分条件**：序列**总和**是 $P$ 的正整数倍。

# 二

再考虑一个特殊情况，当序列 $\{A_i\}$ 的总和**不是** $P$ 的整数倍，并且 $\{A_i\}$ 的元素**互不相同**时，它是否是**良好序列**。

考虑构造 $\{A_i\}$ 的一个**排列** $\{\mathcal{A}_i\}$，使得其**所有前缀和**都**不能被 $P$ 整除**。如果构造成功了，那么就说明 $\{A_i\}$ 是良好序列。

首先，将 $\{A_i\}$ 的所有元素**放入集合** $S$，然后考虑逐位确定 $\{\mathcal{A}_i\}$。这里不妨设 $\{A_i\}$ 的长度为 $N$。那么，我们让变量 $i$ 从 $1$ 遍历到 $N$，并再遍历的过程中确定 $\mathcal{A}_i$ 的值。不妨从集合 $S$ 中取出 $1$ 个任意元素 $a$（取出 $a$ 的意思是，把 $a$ 从 $S$ 中**删除**），直接令 $\mathcal{A}_i\leftarrow a$，那么就会有 $2$ 中情况：

1. $\displaystyle\sum_{t=1}^i\mathcal{A}_t$ 是 $P$ 的**正整数倍**。
2. $\displaystyle\sum_{t=1}^i\mathcal{A}_t$ **不是** $P$ 的正整数倍。

如果是情况 $2$，那么直接**什么都不做**，继续让 $i$ 遍历即可。但如果是情况 $1$，那么需要改变序列 $\{\mathcal{A}_i\}$ 让它的前缀和不被 $P$ 整除。如何改变呢？首先，需要明确的是，如果情况 $1$ 发生了，那 $i$ **一定不等于** $N$，否则就与“序列 $\{A_i\}$ 的总和**不是** $P$ 的整数倍”矛盾。因为 $i\not =N$，所以此时集合 $S$ 不为空，所以我们可以从 $S$ 中再取出一个元素 $a'$，根据“$\{A_i\}$ 的元素**互不相同**”，一定有 $a\neq a'$，所以可以直接令 $\mathcal{A}_i\leftarrow a'$，$\mathcal{A}_{i+1}\leftarrow a$，由于 $a,a'<P$，故 $\displaystyle\sum_{t=1}^i\mathcal{A}_t$ 和 $\displaystyle\sum_{t=1}^{i+1}\mathcal{A}_t$ 均不是 $P$ 的正整数倍。接下来，要确定 $\mathcal{A}_{i+1}$ 时，什么都不做即可，因为 $\mathcal{A}_{i+1}$ 已经被提前确定了。

于是，我们就得到结论，该序列**一定是良好序列**。

# 三

考虑一个序列 $\{A_i\}$，虽然它“的总和**不是** $P$ 的整数倍”，但是它可能有**相等元素**，那么，还能用上述构造排列的方法吗？

考虑**直接套用上述构造方法**。考察其有何变化。显著的变化就是，集合 $S$ 变成了**可重集**。在考虑“情况 $2$”的行为有和变化：当我们从 $S$ 中试图取出 $a'$，使得 $a'\neq a$ 时，**有可能无法完成**，因为有可能 $S$ 中的所有元素都是 $a$。为了尝试避免这一点，我们可以进行这样一个**贪心原则**：

1. 取出 $a$ 时，一定要让 $a$ 是 $S$ 的**众数**。
2. 取出 $a'$ 时，如果能让 $a'$ 是 $S$ 的**众数**，则取众数，否则取**次众数**。

很容易证明，当 $\{A_i\}$ 中**没有绝对众数**时，这个贪心方法是奏效的。

# 四

再考虑一个序列 $\{A_i\}$，它“的总和**不是** $P$ 的整数倍”，但是它“**有绝对众数**”，那么它**一定是坏序列吗**？显然不是。不过我们可能很快就能找到真正的充要条件。

先设 $\{A_i\}$ 的**绝对众数**为 $x$，那么，我们可以给所有的 $A_i$ 乘上 **$x$ 模 $P$ 意义下的逆元**，这样 $\{A_i\}$ 的绝对众数就是 $1$ 了。

不妨设 $\{A_i\}$ 的绝对众数是 $1$，那么我们再来构造一下 $\{A_i\}$ 的排列 $\{\mathcal{A}_i\}$。不妨设 $\{A_i\}$ 中 $1$ 的个数为 $cnt$，然后将 $\{A_i\}$ 中所有**不是 $1$ 的数**加入序列 $\{B_i\}$，则 $\{B_i\}$ 的长度为 $N - cnt$。考虑构造 $\{\mathcal{A}_i\}$ 时**尽可能的消耗** $1$，所以，先令 $\mathcal{A}_1,\mathcal{A}_2,\dots,\mathcal{A}_{p-1}\leftarrow 1$，这是，只能令 $\mathcal{A}_{p}\leftarrow B_1$ 了，接着，又可以令 $\mathcal{A}_{p+1},\mathcal{A}_{p+2},\dots,\mathcal{A}_{p+(p-B_1)}\leftarrow 1$。不断进行这个过程，我们就可以确定 $cnt$ 的上界：

$$
cnt \leq P - 1 + \sum_{i = 1} ^ {N - cnt} (P - B_i)
$$
容易证明这个条件时**充要的**。

# 五

最后，我们就可以用 dp 来统计答案了。

不妨设 $f[i][j]$ 表示长度为 $i$ 的 $\{B_t\}$ 序列，满足 $\displaystyle \sum_{t = 1} ^ i (P - B_t) = j$ 的有**多少种**。考虑到我们想计算**坏序列**的个数，所以就有

$$j = \sum_{t = 1} ^ {N - cnt} (P - B_t) < cnt - (P - 1) \leq N - (P - 1)\leq N$$

所以 $f[i][j]$ 的状态数 $O(N ^ 2)$ 的。容易写出转移：

- $\forall v\in [2,P)$ 且 $v\in\mathbb{N}$，转移 $f[i + 1][j + v] \leftarrow f[i + 1][j + v] + f[i][j]$。

有初值 $f[0][0]\leftarrow 1$。使用**差分优化**转移（每次转移都是区间加）可做到 $O(N ^ 2)$。

然后，再设 $g[i]$ 表示长度为 $i$ 的、总和为 $P$ 的正整数倍的序列 $\{A_t\}$ 有多少种。考虑到长度为 $i - 1$、总和**不**为 $P$ 的正整数被的序列 $\{A_t\}$ 有 $(P - 1) ^ {i - 1} - g[i - 1]$ 种（总个数减去其他个数），而 $g[i]$ 所记录的序列**只能**由前面 $(P - 1) ^ {i - 1} - g[i - 1]$ 种序列**在末尾添加 $1$ 个数得到**，所以 $g[i] = (P - 1) ^ {i - 1} - g[i - 1]$。直接转移 $g[i]$ 复杂度为 $O(N\log N)$（用快速幂）。

最后，统计答案。设记录答案的变量为 $ans$，给它赋初值 $ans\leftarrow (P - 1) ^ N$，然后减去**坏序列的个数**。

首先，令 $ans\leftarrow ans - g[N]$。

然后，$\forall i,j$，考察 $f[i][j]$ 对答案有何贡献。首先，能计算出 $f[i][j]$ 对应序列的 $cnt$，是 $cnt = N - i$，然后判断是否有 $cnt > P - 1 + j$，如果是，再判断 $cnt - j$ 是否是 $P$ 的倍数（即对应序列 $\{A_t\}$ 的总和是否是 $P$ 的倍数），如果**不是**，那么就令

$$
ans\leftarrow ans - f[i][j] \binom{N}{cnt}(P - 1)
$$

其中，$\displaystyle\binom{N}{cnt}$ 的意思是在 $f[i][j]$ 所对应的 $\{B_t\}$ 中**插入** $cnt$ 个 $1$ 的方案数；$(P - 1)$ 的意思是，**绝对众数**不止可能是 $1$，而是有 $(P - 1)$ 种取值。

于是，我们就以 $O(N ^ 2)$ 的总复杂度完成了此题。

# 代码


```cpp
#include<iostream>
#include<iomanip>
#include<utility>
#include<algorithm>
using std::cerr; using std::setw; using std::endl;
using std::cin; using std::cout;
using ll=long long;
constexpr ll MO=998244353ll,MAXN=5000;
ll fac[MAXN+5]={},inv[MAXN+5]={},ifac[MAXN+5]={};
ll mo(ll x){return x>=MO?x-MO:x;}
void n_add(ll &x,ll y){x=mo(x+y); return ;}
void n_sub(ll &x,ll y){x=mo(x+MO-y); return ;}
ll C(ll x,ll y){if(x<y) return 0ll; return fac[x]*ifac[y]%MO*ifac[x-y]%MO;}
ll qpow(ll x,ll u){
    ll y=1ll;
    while(u){
        if(u&1) y=y*x%MO;
        x=x*x%MO;
        u>>=1;
    }
    return y;
}
ll N=0,P=0,f[MAXN+1][MAXN+2]={},g[MAXN+5]={};
int main(){
    std::ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    fac[0]=1ll; for(ll i=1;i<=MAXN;i++) fac[i]=fac[i-1]*i%MO;
    inv[1]=1ll; for(ll i=2;i<=MAXN;i++) inv[i]=MO-MO/i*inv[MO%i]%MO;
    ifac[0]=1ll; for(ll i=1;i<=MAXN;i++) ifac[i]=ifac[i-1]*inv[i]%MO;
    cin>>N>>P;
    f[0][0]=1ll;
    for(ll i=0;i<N;i++){
        for(ll j=0;j<=N;j++){
            if(j+1<=N) n_add(f[i+1][j+1],f[i][j]);
            if(j+(P-2)+1<=N) n_sub(f[i+1][j+(P-2)+1],f[i][j]);
        }
        for(int j=1;j<=N;j++) n_add(f[i+1][j],f[i+1][j-1]);
    }
    ll gret=0;
    for(ll i=0;i<=N;i++){
        for(ll j=0;j<=N;j++){
            ll cnt1=N-i;
            if(cnt1-P+1>j&&(((-j)%P+P)+cnt1)%P!=0){
                n_add(gret,f[i][j]*C(N,i)%MO*(P-1)%MO);
            }
        }
    }
    g[1]=0ll; for(ll i=2;i<=N;i++) g[i]=mo(qpow(P-1,i-1)+MO-g[i-1]);
    ll ans=(qpow(P-1,N)+MO-g[N]+MO-gret)%MO;
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：UltiMadow (赞：3)

考虑一个序列 $a$ 什么时候合法。

显然序列的和不能是 $p$ 的倍数，接下来考虑和不是 $p$ 的倍数的情况。

不妨设序列的众数为 $1$（如果众数是 $x$ 则把序列整体乘上 $x^{-1}$，把众数变成 $1$）。

记序列 $b$ 为序列 $a$ 除去 $1$ 所得的序列，则序列 $a$ 合法当且仅当 $1$ 的个数 $\le p-1+\sum p-b_i$。

证明：先证必要性，假设 $1$ 的个数 $\ge p+1+\sum p-b_i$，则序列和至少为 $p(k+1)+1$，其中 $k$ 为 $b$ 的长度。

考虑到每次序列经过 $p$ 的倍数时都需要一个 $>1$ 的数，此时至少需要经过 $k+1$ 次 $p$ 的倍数，而 $>1$ 的数只有 $k$ 个，矛盾。

下证充分性，考虑按照如下方法给序列重新排序：

> 记此时序列中剩下的数的众数为 $x$，此时已经排好的序列和为 $sum$，若 $sum+x$ 不为 $p$ 的倍数，则把 $x$ 加入序列，否则在剩下的数中任取一个不为 $x$ 的数 $y$，把 $y,x$ 依次加入序列。

那么不难发现一个合法的序列等价于可以通过此方法重排，考虑什么情况下重排会失败。

显然重排失败只会在剩余序列中只剩下一种数且数量 $>1$ 时发生，而这种数一定是原序列的众数，也就是 $1$。

此时的序列形态一定是 $p-1$ 个 $1$，$b_1$，$p-b_1$ 个 $1$，$\dots$，$b_k$，$p-b_k$ 个 $1$，剩余序列中还有至少两个 $1$，而此时 $1$ 的个数超过了 $p-1+\sum p-b_i$，矛盾。

回到原题，考虑对不合法的序列计数。

首先是和为 $p$ 的倍数的情况，记长度为 $i$，和为 $p$ 的倍数的序列有 $g_i$ 个，则显然 $g_i=(p-1)^{i-1}-g_{i-1}$。

接下来是和不为 $p$ 的倍数且 $1$ 的个数 $\ge p+\sum p-b_i$ 的情况。

记 $f_{i,j}$ 为 $b$ 中选了 $i$ 个数，$\sum p-b_k=j$ 的方案数，可以用前缀和 $\mathcal O(1)$ 转移。

那么不合法序列对应的 $(i,j)$ 应满足 $n-i\ge p+j$ 且 $n-i\not\equiv j\pmod p$。

而众数不只是 $1$，所以这部分方案数要乘上 $p-1$。

时间复杂度 $\mathcal O(n^2)$。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 5010
#define p 998244353
using namespace std;
const int N=5000;
int qpow(int x,int y){
	int ret=1;
	for(;y;y>>=1,x=x*x%p)if(y&1)ret=ret*x%p;
	return ret;
}
int n,q,ans;
int f[MAXN][MAXN];
int fac[MAXN],ifac[MAXN];
int C(int x,int y){return x<y?0:fac[x]*ifac[y]%p*ifac[x-y]%p;}
signed main(){
	fac[0]=1;for(int i=1;i<=N;i++)fac[i]=fac[i-1]*i%p;
	ifac[N]=qpow(fac[N],p-2);
	for(int i=N;i;i--)ifac[i-1]=ifac[i]*i%p;
	scanf("%lld%lld",&n,&q);
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=1;j<=n;j++){
			sum=(sum+f[i-1][j-1])%p;
			if(j>=q-1)sum=(sum-f[i-1][j-q+1]+p)%p;
			f[i][j]=sum;
		}
	}
	ans=qpow(q-1,n);
	ans=(ans-(qpow(q-1,n)+(n&1?-q+1:q-1)+p)*qpow(q,p-2)%p+p)%p;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			if(n>=i+j+q&&((n-i-j)%q))ans=(ans-f[i][j]*C(n,i)%p*(q-1)%p+p)%p;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：云浅知处 (赞：2)

考虑分析什么样的序列是合法的。首先，总和不能是 $P$ 的倍数；接下来我们考虑每次尝试填入一个数，如果会导致前缀和 $\bmod P=0$，我们就换一个数填入。这样每次我们填入当前出现次数最多的数，只要不存在一个数的出现次数 $>\frac{N}{2}$，就一定能够填完。

如果存在一个数的出现次数 $>\frac{N}{2}$，设其为 $x$，我们把所有数都乘上 $x^{-1}\bmod P$（注意 $P$ 是质数，因此存在逆元），那么就转化为 $x=1$ 的情形。设有 $k$ 个 $1$，我们考虑每次前缀和经过某个 $i\times P$ 的时候，都需要一个 $>1$ 的数来跨过去，所以总和最多为 $(n-k)\times P+P-1$。只要总和不超过这个数，发现只要执行上面那个过程就可以得到一组解了。

最后我们考虑计数，考虑算不合法的方案数。首先计算总和为 $P$ 的倍数的方案数，设 $f_i$ 表示 $i$ 个数和为 $P$ 的倍数的方案数，我们让前 $i-1$ 个数任意填，只要和不是 $P$ 的倍数，最后一个数总有唯一的方案使得总共的和是 $P$ 的倍数；否则一定无解。于是 $f_i=(P-1)^{i-1}-f_{i-1}$。

接下来考虑总和不是 $P$ 的倍数的方案数，我们钦定 $1$ 出现的次数 $>\frac{N}{2}$，再钦定其他数的总和爆掉。

设 $dp(i,j)$ 表示 $i$ 个 $>1$ 的数，其 $\sum P-a_i+P-1=j$ 的方案数，考虑什么时候不合法。

那么只需要 $N-i>j$ 且 $i<\frac{N}{2}$，这个状态就不合法。不过可能会多算一些总和为 $P$ 的倍数的情况，此时相当于 $N-i-j\equiv 1\pmod P$，把这些情况判掉就好了。使用前缀和优化 DP 即可做到 $O(N^2)$。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,ll y,int p=mod){
	int ans=1;y%=(p-1);
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
mt19937 rnd(time(0));
int randint(int l,int r){return rnd()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}
int cmod(int x){if(x>=mod)x-=mod;return x;}

template<typename T>void cmax(T &x,T v){x=max(x,v);}
template<typename T>void cmin(T &x,T v){x=min(x,v);}

const int N=5005;
int dp[2][N],n,P,f[N],fac[N],ifac[N];
void init(int V){
	fac[0]=1;for(int i=1;i<=V;i++)fac[i]=1ll*fac[i-1]*i%mod;
	ifac[V]=inv(fac[V]);for(int i=V-1;i>=0;i--)ifac[i]=1ll*ifac[i+1]*(i+1)%mod;
}
int C(int x,int y){
	if(x<y)return 0;
	return 1ll*fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif

	n=read(),P=read();init(n);
	f[0]=1;for(int i=1;i<=n;i++)f[i]=cmod(ksm(P-1,i-1)-f[i-1]+mod);
	int ans=ksm(P-1,n);add(ans,mod-f[n]);
	if(P-1>=n){cout<<ans<<endl;return 0;}

	// cout<<"now ans = "<<ans<<endl;

	int cur=0;dp[cur][P-1]=1;
	if(n%P!=0)add(ans,mod-(P-1));
	for(int i=1;i<=(n-1)/2;i++){
		memset(dp[cur^1],0,sizeof(dp[cur^1]));
		for(int j=1;j<n;j++)add(dp[cur][j],dp[cur][j-1]);
		for(int j=1;j<n;j++){
			dp[cur^1][j]=cmod(dp[cur][j-1]-dp[cur][max(0,j-P+1)]+mod);
		}
		cur^=1;
		for(int j=0;i+j<n;j++)if((n-i-j)%P!=1&&dp[cur][j]){
			add(ans,mod-1ll*dp[cur][j]*C(n,i)%mod*(P-1)%mod);
		}
	}
	cout<<ans<<endl;

	return 0;
}
```

---

