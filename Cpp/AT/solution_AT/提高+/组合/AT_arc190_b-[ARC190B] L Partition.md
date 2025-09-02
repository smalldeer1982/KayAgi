# [ARC190B] L Partition

## 题目描述

有一个 $N \times N$ 的网格。从上往下第 $i$ 行、从左往右第 $j$ 列的格子记作 $(i,j)$。

对于 $K=1,2,\ldots,N$，级别 $K$ 的 **L 型** 是指由 $2K-1$ 个格子组成的集合，且满足以下四个条件中的至少一个：

- 从某个格子 $(i,j)$ 出发，向下或向右移动 $0$ 格以上、$K-1$ 格以下所到达的所有格子（其中 $1 \leq i \leq N-K+1$，$1 \leq j \leq N-K+1$）。
- 从某个格子 $(i,j)$ 出发，向下或向左移动 $0$ 格以上、$K-1$ 格以下所到达的所有格子（其中 $1 \leq i \leq N-K+1$，$K \leq j \leq N$）。
- 从某个格子 $(i,j)$ 出发，向上或向右移动 $0$ 格以上、$K-1$ 格以下所到达的所有格子（其中 $K \leq i \leq N$，$1 \leq j \leq N-K+1$）。
- 从某个格子 $(i,j)$ 出发，向上或向左移动 $0$ 格以上、$K-1$ 格以下所到达的所有格子（其中 $K \leq i \leq N$，$K \leq j \leq N$）。

给定格子 $(a,b)$ 以及 $Q$ 个查询 $k_1, \ldots, k_Q$。

对于每个 $i$，请计算将整个网格划分为级别 $1, \ldots, N$ 的 L 型各一个的方法数（要求格子 $(a,b)$ 包含在级别 $k_i$ 的 L 型中），结果对 $998244353$ 取模后输出。


## 说明/提示

### 约束条件

- $1 \leq N \leq 10^7$
- $1 \leq a \leq N$
- $1 \leq b \leq N$
- $1 \leq Q \leq \min\{ N, 200000 \}$
- $1 \leq k_1 < \cdots < k_Q \leq N$
- 输入中的所有值均为整数

### 样例解释 1

存在如下图所示的 $6$ 种满足条件的方法。图中格子上的整数 $k$ 表示该格子属于级别 $k$ 的 L 型。 

![](https://img.atcoder.jp/arc190/d853bd693f0d3848c725803512dc382a.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 1 2
1
2```

### 输出

```
6```

## 样例 #2

### 输入

```
5 2 5
3
1 3 5```

### 输出

```
4
32
128```

## 样例 #3

### 输入

```
100 50 50
4
1 10 50 100```

### 输出

```
934228871
758172260
444239843
0```

# 题解

## 作者：roBotic (赞：8)

update on 1.23, 2025：简单更新了一处勘误。

从长度为 $1$ 的开始填不好做，我们考虑从长度为 $n$ 的开始倒着填，我们对于 $n\times n$ 的方格，长度 $n$ 只有四种填法。进一步地，我们发现，填入该图形就相当于每次选取边缘的一行和一列删除，而题目所求的即为：正好在第 $n-k+1$ 次删除到给定方格的方案数。注意到，行和列是独立的，我们可以考虑行和列的方案数然后相乘。

观察到：能在正好第 $k$ 次删除到第 $A$ 行第 $B$ 列的充要条件是：**正好**在第 $k$ 次删除了第 $A$ 行**或**第 $B$ 列，并且之前**从未删除**第 $A$ 行和第 $B$ 列。

因为行列独立，我们先考虑行，列同理。给定 $n$ 个格子排成一行，每次可以删除首或尾，我们记 $f_{0,k}$ 删除 $k$ 次，并且正好最后一次删除到第 $A$ 个的方案数，并且记 $g_{0,k}$ 表示删除了 $k$ 次，并且还未删除到 $A$ 的方案数，$f_{1,k},g_{1,k}$ 则分别表示列对应的状态。

考虑先求解 $f$ 数组，同样以行为例。如果删除到了 $A$，显然要么从左往右 $A$ 个都删完了，要么从右往左 $n-A+1$ 个都删完了，那么：

- 如果 $k \geq A$，那么可以从左往右删完 $A$ 个，剩下 $k-A$ 个从右往左删，其中第 $k$ 个一定删 $A$，剩下 $k-1$ 个删除的方案数为 $\binom{k-1}{A-1}$。
- 如果 $k \geq n-A+1$，那么可以从右往左删完，剩下 $k-n+A-1$ 个从左往右删，方案数同理为 $\binom{k-1}{n-A}$。

**注意到如果 $k=n$ 的时候，这两种方案是等价的，只需要算一种。**

然后我们考虑求 $g$ 数组，同样以行为例。使用递推，平凡的，我们有（列同理）：

$$g_{0,i}=\left\{\begin{aligned}&1,&i=0,\\&0，&i=n,&\\&g_{0,i-1}\times 2-f_{0,i},&\text{otherwise}.\end{aligned}\right.$$

事实上，你通过递推也可以得到 $g_n=0$，但是递推的系数非 $2$ 而是乘以 $1$。

然后我们可以求答案了，针对一个输入的 $k$，我们考虑从大往小删除，删除 $k'=n-k+1$ 次，然后根据我们得到的充要条件得到方案数为：

$$\text{Answer}=(f_{0,k'}\times g_{1,k'}+f_{1,k'}\times g_{0,k'}+f_{0,k'}\times f_{1,k'})\times 4^{n-k'-1}.$$

之所以要乘以 $4^{n-k'-1}$ 次方是因为我们只考虑了做 $k'$ 次的方案，剩下还有 $n-k'-1$ 次可以任意删除（最后一次删除的是固定的），行和列各有 $2^{n-k'-1}$ 次方案，相乘即为 $4^{n-k'-1}$ 次。其中根据上文需要特判当 $k'=n$ 的方案。

[Submission](https://atcoder.jp/contests/arc190/submissions/61641726).

总时间复杂度 $O(n+\log P+Q\log n)$，其中预处理阶乘及其逆元是 $O(n+\log P)$ 的，以及预处理 $f,g$ 数组是 $O(n)$ 的，然后询问因为要快速幂所以是 $O(Q\log n)$，但是可以通过预处理 $2$ 的幂优化成 $O(n+\log P+Q)$。

---

## 作者：xieziheng (赞：5)

优雅而美好的题目。

考虑没有限制，显然可以从大到小填，方案就是 $4^{n-1}$。

加上限制之后，可以发现 $(a,b)$ 一定在一个 $k\times k$ 的正方形的边界上。

先看正方形内的方案：

- $k=1$ ： 就是 $1$。

- $(a,b)$ 在角上：$3\times 4^{k-2}$。

- $(a,b)$ 在边上：$2\times 4^{k-2}$。

然后看外面的，设正方形左上角为 $(x,y)$，可以打表找规律发现方案数为 $\binom{n-k}{x-1}\binom{n-k}{y-1}$。

角上的方案可以 $\mathcal{O}(1)$ 算，主要看边上的怎么算。

由对称性，不妨只考虑 $(a,b)$ 在正方形上面的那条边，发现 $x=a,y\in[b+2-k,b-1]$，那么方案为 $\binom{n-k}{a-1}\sum_{i=b+1-k}^{b-2} \binom{n-k}{i}$，记 $f_k$ 为后面那一项，注意到只有 $k$ 是变量且上边界不变，展开即有 $f_k=2f_{k+1}-\binom{n-k-1}{b-2}-\binom{n-k-1}{b-k}$。

于是对于一组询问可以 $\mathcal{O}(1)$ 算，复杂度 $\mathcal{O}(n+q)$。

---

## 作者：2008verser (赞：5)

~~前置知识：都是被这场 A 题害得。~~

先想想怎么数 $N\times N$ 的网格有多少种 L 的放法，设为 $F(n)$。

如果我们将 L 从大到小考虑，填完最大的以后，剩下的内容就是独立的了，于是我们有 $F(n)=4F(n-1)$。并且 $F(1)=1$。

这表明，从大到小放置的过程中，每一个时刻留空的区域都是一个正方形。

比如 $(a,b)$，若它在 $k$ 级 L 里，就是说当留空的区域是 $k\times k$ 时，新选的 L 型覆盖到它了。

我们画出一个 $k\times k$ 的正方形，它可以在 $N\times N$ 的网格里随意移动但是 $(a,b)$ 必须要在它内部的边缘。 

当 $(a,b)$ 不在它角落上时，下一步的 L 有两种选法，否则有三种。

对于第一种情况，枚举 $k\times k$ 的位置以后，我们用 $2$ 乘以【从 $N\times N$ 搞到 $k\times k$ 的方案数】乘以 $F(k-1)$，求和。第二种情况是类似的。

那怎么求【从 $N\times N$ 搞到 $k\times k$ 的方案数】呢？

设 $k\times k$ 的矩形上面、左边分别还有 $x,y$ 的空间，则这个矩形的位置就被刻画出来了。

仍然考虑从大到小填 L，每一步相当于将竖着和横着的剩余空间分别选一个，一起减一。

我的方法是用 $n-k$ 个二元组，因为只需要计数，所以 ${n-k\choose x}{n-k\choose y}$ 就是对的。

接下来的工作就是机械地将上面对 $k\times k$ 的矩阵的枚举写成数学式子，没什么难度而且很不好讲，跳过。

总之到最后我们对每个 $1\leq k\leq n$ 求出答案，每次都要计算组合数在 $n-k$ 这一行其中一段的和。

而两行之间要求的部分相差 $O(1)$，经典地将一行的答案乘以 $2$，调整一下边界就可以搞成下一行。

所以最后时间复杂度是 $O(n+q)$。

[AC 链接](https://atcoder.jp/contests/arc190/submissions/61648992)

---

## 作者：Optimistic2 (赞：3)

# [ARC190B] L Partition solution

一道挺好的计数题，主要考察推式子的能力以及对排列组合的理解。

题目大意：
给你一个 $n\times n$ 的矩形，以及矩形上的一个定点 $(x,y)$，求出用 $1 \sim n$ 的 L 型将矩形进行填充，并且第 $k$ 种 L 形必须覆盖这个点的方案数。

多个 $k$。

## 分析

首先考虑从大到小铺，铺 $n-k$ 次就会得到一个 $k\times k$ 的矩形，此时分类讨论定点在角上和在边上的情况，所以将内部和外部的答案乘起来即可。

### 定点在 $k\times k$ 矩形的角上

这种情况比较简单，内部有 $3\times 4^{k-2}$ 种情况，外部考虑有 $\binom{n-k}{x-1}\times \binom{n-k}{y-1}$ 种情况，所以答案为 $3\times 4^{k-2}\times \binom{n-k}{x-1}\times \binom{n-k}{y-1}$。

为什么是 $\binom{n-k}{x-1}\times \binom{n-k}{y-1}$ 呢？

因为考虑每一次铺 L 形的过程，每一次即让上下左右的两边减去 $1$，并且上下不能同时减去，左右不能同时减去，上下和左右的出现次数的和均为 $n-k$，所以可以分两维考虑，即考虑 $x$ 和 $y$ 的匹配，两者相乘即是答案。

注意特判 $k=1$ 的情况，此时答案为 $\binom{n-k}{x-1}\times \binom{n-k}{y-1}$。

### 定点在 $k\times k$ 矩形的边上

内部的计算是类似的，式子是 $2\times 4^{k-2}$，因为只有两种 L 形的铺法了。

外部这种情况比较复杂，考虑矩形的上面一条边（其他的是一样的），发现它的答案是形如 $\sum\limits_{i=B-k+1}^{B-2} \binom{n-k}{i}$ 的和乘上 $\binom{n-k}{A-1}$，发现可以将 $k$ 离线，然后递推来求解，每次从 $k$ 到 $k+1$ 相当于加上两边的组合数并除以 $2$，这个最好自己思考一下，递推证明即可。


总结：一道很好的计数题，主要考察推式子的能力以及对排列组合的理解。

~~可能分讨有点多。~~

code:

https://atcoder.jp/contests/arc190/submissions/61670001

---

## 作者：Coffins (赞：2)

套路题。

首先考虑把条件刻画的有个人样。我们考虑从大到小放 L 型，这样每次操作都是在一个正方形中仍取一个角作为 L 的中间。我们不妨考虑 $(a,b)$ 这个点在每次操作的时候在方形内部的位置，这样每次操作都是移动向 $(a,b),(a-1,b),(a,b-1),(a-1,b-1)$ 四个点之一，如果在 $n-k$ 次操作后恰好在以 $(1,1),(k,k)$ 为两个顶点的正方形的边上就会有一个 2 的贡献，特别的，在角上会有一个 3 的贡献，最后再乘上 $4^{k-2}$ 即可。

于是就转化成了一个方格走点问题。

我们设在 $(a,b)$ 通过 $c$ 步走到 $(a-i,b-j)$ 的方案数为 $f(c,i,j)$（因为显然与 $a,b$ 的值无关），然后打个表发现 $f(c,i,j)=\dbinom{c}{i}\dbinom{c}{i}$。原因其实也显然，因为两维可以拆开考虑，每维都是显然的组合数。

然后就可以做到每次查询 $O(n)$ 了。

然后如果你把 $O(n)$ 写出来就会发现你需要对于每一个 $k$ 快速计算 $\sum\limits_{i=a-k+1}^{a-2}\dbinom{n-k}{i}$（$b$ 类似），这个东西显然可以递推过去，然后就完事了，复杂度 $O(n+q\log p)$（其实 log 也可以不要）。

~~你怎么知道我系数写错了调了 40min~~

https://atcoder.jp/contests/arc190/submissions/61642315

---

## 作者：int_R (赞：2)

感觉赛时最大的问题是没有想到把两维独立开。

----

考虑按从大到小的顺序填入 $k$ 级 L-shape，那么每次会把一个 $k$ 级正方形占掉两条邻边，变成一个$k-1$ 级正方形。

要求 $(a,b)$ 在 $k$ 级 L-shape 中，就相当于要求 $(a,b)$ 属于 $k$ 级正方形，而不属于 $k-1$ 级正方形，于是可以差分。

仅考虑使横坐标满足限制，即现在有若干条长度为 $k,k+1,\cdots,n$ 的区间，要求 $a\in I_k\subsetneq I_{k+1}\subsetneq\cdots\subsetneq I_n = [1,n]$，发现这样两维就独立开了。

----

$a\in I_k$ 时 $a\in I_{k+1}$，一个长度为 $k+1$ 的区间是“丢掉”了一个端点来得到一个长度为 $k$ 的区间的，当“丢掉”了 $a$ 后就不合法了，也就是我们要减去这样的区间的个数。

到 $k+1$ 级区间时相当于做了 $n-k-1$ 次操作，要求一个端点为 $a$ 就是在 $a$ 前面做了 $a-1$ 次操作，或者在 $a$ 后面做了 $n-a$ 次操作，于是 $f_k=2f_{k+1}-(\binom{n-k-1}{a-1}+\binom{n-k-1}{n-a})$。

---

## 作者：louisliang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc190_b)

很显然每次填完 L 之后所覆盖的图形为正方形，不然最最后无法填出正方形。现在假设我们已经确定了一个 $k$ 阶的 L，要求它的方案数。

对于 $[1,k-1]$ 阶 L 的放法，每阶的 $4$ 种方向都对应着一种方案，但 $1$ 阶 $4$ 种都是一样的，所以总方案数为 $4^{k-2}$ 种。

对于 $[k+1,n]$ 阶 L 的放法，设其 $k$ 阶 L 离上、下、左、右边界的距离分别为 $a,b,c,d$，那么从中选出那些是覆盖上面的，那些是覆盖左边的，即可唯一确定一种放法，方案数 $\binom{a+b}{a}\binom{c+d}{c}$。

枚举 $(a,b)$ 是在 L 的四个角上或四个方向的边上，角的情况下 L 是确定的，直接算就行了。边上的情况中 L 是可以上下或左右平移的，其式子就是组合数的前缀和。记 $f(n,k)=\sum\limits_{i=0}^k\binom{n}{k}$。显然可以从 $f(n,k)$ 转移到 $f(n,k-1)$ 和 $f(n,k+1)$。又有 
$$\binom{n}{k}=\binom{n-1}{k-1}+\binom{n-1}{k}$$
所以
$$f(n,k)=f(n-1,k-1)+f(n-1,k)$$
$$f(n-1,k)=\frac{f(n,k)+\binom{n-1}{k}}{2}$$
这样我们就能从 $f(n,k)$ 转移到 $f(n-1,k)$ 了。可以观察到总移动次数是 $O(n)$ 的，直接转移即可。

一些注意的点：
- 角的方案要 $\times 3$，边的方案要 $\times 2$。
- 转移的过程中可能会转移到 $f(n,k)$ 中 $k>n$ 的情况，这时候要从 $f(n,n)=2^n$ 去转移。

Code：
```cpp
const int N = 2e7 + 10, MOD = 998244353;
int n, a, b, q;
long long jc[N], jny[N], ny[N], pw2[N];
vector < pair <int, int> > vt, pt;
long long C(int x, int y){
	return jc[y] * jny[x] % MOD * jny[y - x] % MOD; 
}
long long gt(int x, int k){
	if(x < 0)
		return 0;
	auto t = (x < k / 2)? make_pair(0, 1ll) : make_pair(k, pw2[k]);
	for(auto i : vt)
		if(i.first <= k && abs(t.first - x) > abs(i.first - x))
			t = i;
	while(t.first < x)
		t.first++, t.second = (t.second + C(t.first, k)) % MOD;
	while(t.first > x)
		t.second = (t.second - C(t.first, k) + MOD) % MOD, t.first--;
	pt.push_back(t);
	return t.second;
}
long long calc(int a, int b, int c, int d){
	if(a <= 0 || b <= 0 || c > n || d > n)
		return 0;
	return C(a - 1, a - 1 + n - c) * C(b - 1, b - 1 + n - d) % MOD;
}
long long calc(int x, int y, int k){
	int l = max(1, y - k + 2), r = min(n - k + 1, y - 1);
	if(l > r)
		return 0;
	long long t = (gt(r - 1, n - k) - gt(l - 2, n - k) + MOD) % MOD, sum = 0;
	if(x + k - 1 <= n)
		sum = (sum + t * C(x - 1, n - k)) % MOD;
	if(x - k + 1 > 0)
		sum = (sum + t * C(n - x, n - k)) % MOD;
	return sum;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> a >> b >> q;
	jc[0] = jc[1] = ny[0] = ny[1] = jny[0] = jny[1] = pw2[0] = 1, pw2[1] = 2;
	for(int i = 2; i <= 2 * n; i++)
		ny[i] = (MOD - MOD / i) * ny[MOD % i] % MOD, jc[i] = jc[i - 1] * i % MOD, jny[i] = jny[i - 1] * ny[i] % MOD, pw2[i] = pw2[i - 1] * 2 % MOD;
	int la = n;
	while(q--){
		int k;
		cin >> k;
		while(la > n - k){
			la--;
			for(auto &i : vt)
				i.second = (i.second + C(i.first, la)) % MOD * ny[2] % MOD;
		}
		pt.clear();
		long long sum = (calc(a, b, k) + calc(b, a, k)) * 2 % MOD;
		if(k > 1)
			sum = (sum +(calc(a - k + 1, b - k + 1, a, b) + calc(a - k + 1, b, a, b + k - 1) + calc(a, b - k + 1, a + k - 1, b) + calc(a, b, a + k - 1, b + k - 1)) * 3) % MOD;
		else
			sum = (sum + calc(a, b, a, b)) % MOD;
		swap(pt, vt);
		sort(vt.begin(), vt.end());
		vt.erase(unique(vt.begin(), vt.end()), vt.end());
		cout << sum * pw2[max(0, k - 2) * 2] % MOD << "\n";
	}
}
```

---

## 作者：wfc284 (赞：1)

我们把题意转化一下：（从 $n$ 级 L-shape 开始倒着填）每次操作就是删去首或尾行、首或尾列，在第 $n-k$ 次操作后（填 $k+1$ 级 L-shape 后），$(a,b)$ 刚好在剩下正方形的边缘上。  
也就是说，我们剩下的一定是个 $k \times k$ 的正方形。

有一个思路：确定剩余的 $k \times k$ 正方形（左上角）的位置 $(x,y)$，计算其【外部贡献】和【内部贡献】。  
若 $(x, y)$ 确定，发现行列独立，用删行删列的方式理解，【外部贡献】就有 $\binom{n-k}{x-1} \binom{n-k}{y-1}$ 种方案。

我们将 $(a, b)$ 分为在剩余正方形的顶点处和边上：

- 顶点处：$k$ 级 L-shape 有 $3$ 种填法，【内部贡献】为 $3 \times 4^{k-2}$。此时 $(x, y)$ 是可以直接算出来的，故【外部贡献】可以 $O(1)$ 计算。
- 边上（不在顶点上）：$k$ 级 L-shape 有 $2$ 种填法，【内部贡献】为 $2 \times 4^{k-2}$。我们不妨令正方形的上边贴着 $(a, b)$，则 $x=a,y \in [b-k+2,b-1]$，即 $i = y-1 \in [b-k+1,b-2]$，其他情况对称处理。故一部分【外部贡献】为：
  $$
  \binom{n-k}{a-1} \sum_{i=b-k+1}^{b-2}\binom{n-k}{i}
  $$
  记 $f_k = \sum_{i=b-k+1}^{b-2}\binom{n-k}{i}$，于是：
  $$
  \begin{aligned}
  f_k &= \sum_{i=b-k+1}^{b-2} \left [ \binom{n-k-1}{i} + \binom{n-k-1}{i-1} \right] \\
  &= \sum_{i=b-(k+1)+2}^{b-2} \binom{n-(k+1)}{i} + \sum_{i=b-(k+1)}^{b-3}\binom{n-(k+1)}{i} \\
  &= \left [ \sum_{i=b-(k+1)+1}^{b-2} \binom{n-(k+1)}{i} \right ] - \binom{n-k-1}{b-k} + \left  [\sum_{i=b-(k+1)+1}^{b-2} \binom{n-(k+1)}{i} \right ] - \binom{n-k-1}{b-2}\\
  &= f_{k+1} - \binom{n-k-1}{i} + f_{k+1} - \binom{n-k-1}{b-2} \\
  &= 2f_{k+1} - \binom{n-k-1}{i} - \binom{n-k-1}{b-2}
  \end{aligned}
  $$
  就可以 $O(n)$ 预处理出 $f$ 数组，$O(1)$ 询问了。

有一个小技巧，在对称处理的时候，只需要把 $(a, b)$【转】几下，每【转】一下算一次贡献，具体见代码。

时间复杂度 $O(n+q)$。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
#define int long long
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)
//#define multi_cases 1

namespace Traveller {
	const int N = 1e7+2, P = 998244353;
	void vadd(int &a, int b) { a = (a + b) % P; }
	const int dir[4][2] = {{0, 0}, {0, -1}, {-1, 0}, {-1, -1}};
	
	int n, a[4], b[4], q;
	
	int frac[N], inv[N], frac_inv[N];
	int pow4[N];
	void init() {
		inv[1] = 1;
		for(int i = 2; i <= n; ++i) inv[i] = (P - P/i) * inv[P % i] % P;
		frac[0] = frac_inv[0] = pow4[0] = 1;
		for(int i = 1; i <= n; ++i)
			frac[i] = frac[i-1] * i % P, 
			frac_inv[i] = frac_inv[i-1] * inv[i] % P,
			pow4[i] = pow4[i-1] * 4 % P;
	}
	int C(int n, int m) {
		if(n < 0 || m < 0 || n < m) return 0;
		return frac[n] * frac_inv[m] % P * frac_inv[n-m] % P; 
	}
	
	int f[4][N];
	void update(int *f, int a, int b) {
		for(int y = b-n+1; y <= b-2; ++y) vadd(f[n], C(0, y));
		for(int k = n-1; k >= 3; --k)
			f[k] = (2 * f[k+1] - C(n-k-1, b-k) - C(n-k-1, b-2) + 2*P) % P;
	}
	int query(int k) {
		if(k == 1) return C(n-1, a[0]-1) * C(n-1, b[0]-1) % P;
		int res = 0;
		for(int o = 0; o < 4; ++o)
			vadd(res, C(n-k, a[o]-1) * f[o][k] % P * 2 * pow4[k-2] % P);
		for(int o = 0; o < 4; ++o) {
			int x = a[0] + dir[o][0] * (k-1), y = b[0] + dir[o][1] * (k-1);
			vadd(res, C(n-k, x-1) * C(n-k, y-1) % P * 3 * pow4[k-2] % P);
		}
		return res;
	}
	
	void main() {
		cin >> n >> a[0] >> b[0] >> q;
		
		init();
		for(int o = 1; o < 4; ++o) a[o] = b[o-1], b[o] = n - a[o-1] + 1;
		for(int o = 0; o < 4; ++o) update(f[o], a[o], b[o]);
		
		for(int i = 1, k; i <= q; ++i) {
			scanf("%lld", &k);
			printf("%lld\n", query(k));
		}
	}
}

signed main() {
#ifdef filename
	FileOperations();
#endif
	
	signed _ = 1;
#ifdef multi_cases
	scanf("%d", &_);
#endif
	while(_--) Traveller::main();
	return 0;
}
```

---

## 作者：Claire0918 (赞：0)

我们首先重新定义组合数
$$
{n \choose m} = 
\begin{cases}
n^{\underline{m}} & m \geq 0, n \geq m\\
0 & \text{otherwise}\\
\end{cases}
$$
此时无论如何都有 $\displaystyle {n \choose m} = {n - 1 \choose m} + {n - 1 \choose m - 1}$。

我们有一个定理：填入 $n$ 个 L 形的方案数 $f(n) = 4^{n - 1}$。这是因为显然有 $f(1) = 1$。在填完 $n - 1$ 个后，第 $n$ 个有 $4$ 种填的方案，所以 $f(n) = 4f(n - 1)$。归纳证得 $f(n) = 4^{n - 1}$。

---

从小往大填入是难以计算的，我们考虑从大到小填入。不难发现填入一个 L 形等价于在上方或下方删除一行，左侧或右侧删除一列，且行和列的删除互相独立。

换而言之，原本的 $(a, b)$ 在填入一个后可以变成 $(x, y)$，其中 $x \in \{a, a - 1\}, y \in \{b, b - 1\}$。

我们来考量填入 $n - k$ 个比第 $k$ 个大的 L 形之后 $(a, b)$ 需要变成什么样的 $(x, y)$ 才能被第 $k$ 大的 L 形覆盖。

---

$(x, y)$ 在角上，即 $x \in \{1, k\}$ 且 $y \in \{1, k\}$。在 $n - k$ 次操作中将 $a$ 变化成 $1$ 的方案数为 $\displaystyle {n - k \choose a - 1}$，同理得到总操作方式 $\displaystyle ({n - k \choose a - 1} + {n - k \choose a - k})({n - k \choose b - 1} + {n - k \choose b - k})$。每一个 $(x, y)$ 可以被 $3$ 种 L 形覆盖，并且我们还要考虑剩余 $k - 1$ 个 L 形的方案数，所以答案还要乘上 $3 \times 4^{k - 2}$。

---

$(x, y)$ 在边上且不在角上，即 $x \in [2, k - 1]$ 且 $y \in \{1, k\}$ 或 $x \in \{1, k\}$ 且 $y \in [2, k - 1]$。我们仅考量 $x \in [2, k - 1]$ 的情况。如果我们在 $n - k$ 次操作中选取了 $p$ 次操作使得 $x \gets x - 1$，因为 $x \in [2, k - 1]$，所以 $a - p \in [2, k - 1]$，解得 $p \in [a - k + 1, a - 2]$，所以方案数为 $\displaystyle f_k = \sum_{i = a - k + 1}^{a - 2} {n - k \choose i}$。

直接计算单次复杂度是 $\mathcal{O}(n)$ 的，考虑预处理。我们有
$$
\begin{aligned}
&2f_{k + 1}\\
&= 2\sum_{i = a - k}^{a - 2} {n - k - 1 \choose i}\\
&= \sum_{i = a - k + 1}^{a - 2} {n - k - 1 \choose i} + \sum_{i = a - k + 1}^{a - 2} {n - k - 1 \choose i - 1} + {n - k - 1 \choose a - k} + {n - k - 1 \choose a - 2}\\
&= \sum_{i = a - k + 1}^{a - 2} ({n - k - 1 \choose i} + {n - k - 1 \choose i - 1}) + {n - k - 1 \choose a - k} + {n - k - 1 \choose a - 2}\\
&= \sum_{i = a - k + 1}^{a - 2} {n - k \choose i} + {n - k - 1 \choose a - k} + {n - k - 1 \choose a - 2}\\
&= f_k + {n - k - 1 \choose a - k} + {n - k - 1 \choose a - 2}\\
\end{aligned}
$$
所以 $\displaystyle f_{k + 1} = \frac{f_k + {n - k - 1 \choose a - k} + {n - k - 1 \choose a - 2}}{2}$。又有初始化 $f_3 = {n - k \choose a - 2}$，直接 $\mathcal{O}(n)$ 转移即可。

类似地，我们设 $\displaystyle g_k = \sum_{i = b - k + 1}^{b - 2} {n - k \choose i}$，类似 $f_k$ 进行转移，那么总操作方案数为
$$
f_k \times ({n - k \choose b - 1} + {n - k \choose b - k}) + g_k \times ({n - k \choose a - 1} + {n - k \choose a - k})
$$
每一个 $(x, y)$ 可以被 $2$ 种 L 形覆盖，同时我们还要考虑剩余 $k - 1$ 个的方案数，所以答案乘上 $2 \times 4^{k - 2}$。

---

注意在 $k = 1$ 时上述方法显然不适用，特判即可。

时间复杂度 $\mathcal{O}(n + q\log n)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;

const int maxn = 1e7 + 10, mod = 998244353, inv2 = 499122177;

int n, a, b, q;
int fac[maxn], ifac[maxn], f[maxn], g[maxn];

inline long long ksm(long long a, long long b){
    long long res = 1;
    while (b){
        if (b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline long long inv(long long x){
    return ksm(x, mod - 2);
}

inline long long c(int n, int m){
    if (m < 0 || n < m){
        return 0;
    }
    return (long long)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

int main(){
    scanf("%d %d %d %d", &n, &a, &b, &q);
    fac[0] = 1;
    for (int i = 1; i <= n; i++){
        fac[i] = (long long)fac[i - 1] * i % mod;
    }
    ifac[n] = inv(fac[n]);
    for (int i = n - 1; ~i; i--){
        ifac[i] = (long long)ifac[i + 1] * (i + 1) % mod;
    }
    f[3] = c(n - 3, a - 2);
    for (int i = 4; i <= n; i++){
        f[i] = (f[i - 1] + c(n - i, a - i + 1) + c(n - i, a - 2)) % mod * inv2 % mod;
    }
    g[3] = c(n - 3, b - 2);
    for (int i = 4; i <= n; i++){
        g[i] = (g[i - 1] + c(n - i, b - i + 1) + c(n - i, b - 2)) % mod * inv2 % mod;
    }
    while (q--){
        int k;
        scanf("%d", &k);
        if (k == 1){
            printf("%lld\n", c(n - k, a - 1) * c(n - k, b - 1) % mod);
            continue;
        }
        const long long t1 = mod_add(c(n - k, a - 1), c(n - k, a - k)), t2 = mod_add(c(n - k, b - 1), c(n - k, b - k));
        const long long r1 = t1 * t2 % mod, r2 = mod_add(t2 * f[k] % mod, t1 * g[k] % mod);
        printf("%lld\n", mod_add(r1 * 3 % mod, (r2 << 1) % mod) * ksm(4, k - 2) % mod);
    }

return 0;
}
```

---

