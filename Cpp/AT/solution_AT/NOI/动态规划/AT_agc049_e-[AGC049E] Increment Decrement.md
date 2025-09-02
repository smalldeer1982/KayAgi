# [AGC049E] Increment Decrement

## 题目描述

maroon くん想出了如下的问题。

---

すぬけ君有一个长度为 $N$ 的整数序列 $a$。最开始，对于所有 $i$（$1 \leq i \leq N$），都有 $a_i=0$。

すぬけ君可以按任意顺序、任意次数重复以下两种操作：

- 操作 $1$：选择任意整数 $i$（$1 \leq i \leq N$）和 $x$（$x=1$ 或 $x=-1$），将 $a_i$ 替换为 $a_i+x$。每执行一次该操作，花费 $1$ 的代价。
- 操作 $2$：选择任意整数 $l,r$（$1 \leq l \leq r \leq N$）和 $x$（$x=1$ 或 $x=-1$），对于所有 $i$（$l \leq i \leq r$），将 $a_i$ 替换为 $a_i+x$。每执行一次该操作，花费 $C$ 的代价。

给定一个长度为 $N$ 的整数序列 $A$。すぬけ君的目标是使得对于所有 $i$，都有 $a_i=A_i$。请你求出达成目标所需的总代价的最小值。

---

然而，在准备这个问题时，发现了许多未曾预料的解法。因此，问题被修改如下：

---

现在，すぬけ君有 $N$ 个整数序列 $B_1,B_2,\cdots,B_N$，以及整数 $C,K$。每个 $B_i$（$1 \leq i \leq N$）都是长度为 $K$ 的整数序列。

接下来，すぬけ君要构造一个长度为 $N$ 的整数序列 $A$，并求出上述问题的答案。$A_i$ 的取值可以从 $B_{i,1},B_{i,2},\cdots,B_{i,K}$ 中任选一个。即使 $B_i$ 中有重复的值，也要将它们视为不同的选择。也就是说，$A$ 的构造方式共有 $K^N$ 种。

请你计算，对于所有可能的 $A$，上述问题的答案之和，并对 $10^9+7$ 取模。

---

请解决本题。

## 说明/提示

### 数据范围

- $1 \leq N \leq 50$
- $1 \leq C \leq N$
- $1 \leq K \leq 50$
- $1 \leq B_{i,j} \leq 10^9$
- 所有输入均为整数。

### 样例解释 1

$A=(2,3,1,2,1)$。一种最优操作方案如下：

- 以 $l=1,r=5,x=1$ 执行操作 $2$，此时 $a=(1,1,1,1,1)$。
- 以 $l=1,r=4,x=1$ 执行操作 $2$，此时 $a=(2,2,2,2,1)$。
- 以 $i=2,x=1$ 执行操作 $1$，此时 $a=(2,3,2,2,1)$。
- 以 $i=3,x=-1$ 执行操作 $1$，此时 $a=(2,3,1,2,1)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 2 1
2
3
1
2
1```

### 输出

```
6```

## 样例 #2

### 输入

```
3 2 3
1 2 3
1 2 3
1 2 3```

### 输出

```
126```

## 样例 #3

### 输入

```
10 4 1
8
10
10
1
5
9
5
5
9
1```

### 输出

```
45```

## 样例 #4

### 输入

```
10 5 10
79 48 35 56 16 26 37 6 75 23
39 99 57 100 49 90 18 9 12 91
29 97 49 86 30 94 78 63 49 22
100 27 48 91 66 14 6 20 23 84
12 60 99 75 88 95 61 58 20 46
10 11 30 38 55 94 9 52 92 75
27 22 46 85 83 88 50 63 95 91
49 59 19 37 53 27 11 26 2 91
95 36 20 76 84 41 59 95 67 66
52 60 17 11 28 57 75 69 95 24```

### 输出

```
877826779```

# 题解

## 作者：EuphoricStar (赞：16)

好题。同时考查了 slope trick 和选手的计数能力，不愧是 AGC E。

----

先考虑问题的第一部分。

> 你现在有一个初始全为 $0$ 的序列 $b$。你每次可以给 $b$ 单点 $\pm 1$，代价为 $1$，或区间 $\pm 1$，代价为 $m$。求把 $b$ 变成给定序列 $a$ 的最小代价。

考虑先执行区间加减操作，设操作完的序列为 $c$，那么之后单点加减操作的代价就是 $\sum\limits_{i = 1}^n |c_i - a_i|$。对 $c$ 差分，可以发现最少的区间操作次数就是差分后数组的**正数项**的值的和。所以总代价就是 $\sum\limits_{i = 1}^n |c_i - a_i| + m \sum\limits_{i = 1}^n \max(c_i - c_{i - 1}, 0)$。

考虑 dp，设 $f_{i, j}$ 为 $c_i = j$ 的最小代价（显然最优时 $c_i \ge 0$）。初始有 $\forall i \ge 0, f_{0, i} = mi$。转移枚举 $c_{i - 1}$，可得：

$$f_{i, j} = |a_i - j| + \min\limits_k f_{i - 1, k} + m \max(j - k, 0)$$

看到转移式里面有计算绝对值，联想到 **slope trick**。发现 $f_i$ 是凸函数，并且每段的斜率在 $[-1, m + 1]$ 之间。容易归纳，我们初始的图像是一条斜率为 $m$ 的射线，然后我们先进行 $f_{i, j} \gets \min\limits_k f_{i - 1, k} + m \max(j - k, 0)$ 的更新，这个更新产生的影响就是，斜率为 $-1$ 的段被拍平（**斜率变成** $0$），斜率为 $m + 1$ 的段**斜率变成** $m$。然后我们给这个图像整体加上 $|a_i - j|$ 的分段函数，也就是把 $\le a_i$ 的段斜率**减少** $1$，$> a_i$ 的段斜率**增加** $1$。

考虑运用 slope trick，用 `multiset` 维护这个分段函数。回忆一下在 slope trick 中，我们维护的是分段函数图像变化的断点，并且一个断点代表斜率增加 $1$。那么在这题中，我们初始往 `multiset` 添加 $m$ 个 $0$ 代表断点为 $0$ 且斜率为 $m$，然后当 $i = 1$ 时，因为**图像不存在斜率为 $-1$ 或 $m + 1$ 的段**，因此我们不需要进行删除操作，直接添加两个 $a_i$ 表示 $a_i$ 处斜率变化为 $2$。当 $i > 1$ 时，我们先删除 `multiset` 中的最小值和最大值表示这两个断点被拍平了，不存在了，再添加两个 $a_i$。

至于统计答案，我们在每次添加两个 $a_i$ 后统计，此时 `multiset` 中的最小值就是斜率 $-1 \to 0$ 变化的断点，因此我们把答案累加 $a_i - p$，其中 $p$ 为 `multiset` 中的最小值（不用加绝对值是因为此时加入 $a_i$ 后 $p$ 一定 $\le a_i$）。

于是我们现在可以 $O(n \log n)$ 求解这个问题了。

----

考虑问题的第二部分，即统计所有可能的 $a_i$ 对应的答案之和。

考虑我们上面的算法流程。

> 初始往 `multiset` 中添加 $m$ 个 $0$。$i = 1$ 时，往 `multiset` 中添加 $2$ 个 $a_i$，然后计算 $a_i - p$，其中 $p$ 为 `multiset` 中最小值；$i > 1$ 时，先删除 `multiset` 中的最小值和最大值，然后往其中添加 $2$ 个 $a_i$，再计算 $a_i - p$。

$a_i$ 部分的贡献系数是容易统计的，就是 $K^{n - 1}$（选定 $a_i$ 后其他的可以任意选，都能产生贡献）。问题还剩下统计所有 $p$ 的和。

我们枚举 $nK$ 个可能的 $p$，分别计算最小值 $< p$ 和最小值 $\le p$ 的方案数，二者**差分**一下就是 $p$ 的贡献系数。

直接做不好维护 `multiset`，但是如果 $a_i \in \{0, 1\}$，我们就能维护 $1$ 的个数来表示整个 `multiset` 了（**非常经典的套路：任意值转** $01$）。我们不妨让 $a_i \gets [a_i \ge p]$，这样最小值 $< p$ 等价于最小值 $= 0$。

发现只有 $1$ 的个数是 $m + 2$ 时，`multiset` 中的最小值才不是 $0$。因此考虑一个容斥，总方案数减去最小值为 $1$ 的方案数。总方案数显然是 $nK^n$（一共 $n$ 轮，$a$ 数组有 $K^n$ 种产生方式），如果我们设 $f_{i, j}$ 为进行到第 $i$ 轮，`multiset` 中有 $j$ 个 $1$ 的方案数，那么最小值为 $1$ 的方案数就是 $\sum\limits_{i = 1}^n K^{n - i} f_{i, m + 2}$（乘上 $K^{n - i}$ 是因为第 $i + 1 \sim n$ 轮中 $a_i$ 的选择都不影响第 $i$ 轮的最小值是 $1$）。

现在考虑 $f_{i - 1} \to f_i$。对于一个 $f_{i - 1, j}$，我们先进行删除操作，即 $j \gets j - [j > 0] - [j = m + 2]$，然后我们考虑选择 $a_i$，设 $t = \sum\limits_{j = 1}^K [b_{i, j} \ge p]$，也就是能选的 $1$ 的个数，那么 $f_{i, j} \gets (K - t) f_{i - 1, j}$，$f_{i, j + 2} \gets t f_{i - 1, j}$。记得特判 $i = 1$。

----

至此我们终于以 $O(n^3K)$ 的时间复杂度完成了这题。

[code](https://atcoder.jp/contests/agc049/submissions/43753061)

---

## 作者：275307894a (赞：12)

感觉题解区的 slope trick 做法有点牛的，但是我感觉五次做法比较容易想到啊！

首先因为每次只会加减一，因此可以认为，$A$ 的每一层的值是独立的。具体的，我们枚举每个 $x$，看 $A_i$ 是否 $\geq x$，并计算将 $B_i=[A_i\geq x]$ 归零的贡献，然后将所有贡献加起来就是答案。

而若 $B_i$ 没有变化，贡献是不变的，因此我们可以将值域分成 $O(nm)$ 段，每段计算贡献然后相加。

枚举分界的值 $x$，计算每个数 $\geq x$ 的个数和 $<x$ 的个数，然后记 $f_{i,x,y}$ 表示到了第 $i$ 个数，当前没有区间向后覆盖的最小权值是 $x$，有向后区间的最小权值是 $y$，转移容易做到 $O(1)$，因此总复杂度 $O(n^4m)$。

[submission](https://atcoder.jp/contests/agc049/submissions/54189968)

---

## 作者：UltiMadow (赞：4)

先考虑如何对于一个序列 $\{a\}$ 求答案

记 $p_i$ 为执行完所有操作二之后的 $a$ 序列，则操作一贡献为 $\sum|p_i-a_i|$，操作二贡献为 $\sum c\max\{p_{i+1}-p_i,0\}$

考虑 dp，记 $f_{i,j}$ 为考虑前 $i$ 个数，$p_i=j$ 的最小代价

则 $f_{i,j}=\min\{f_{i-1,k}+c\max\{j-k,0\}+|j-a_i|\}$，为了方便，我们记 $f_{0,j}=cj$，最后答案即为 $f_{n+1,0}$

我们把 $f_i$ 画成折线，考虑归纳证明 $f_i$ 是下凸的

记 $f_{i-1}$ 的最小值在 $k$ 处取到，则对于所有 $j\le k$ 都有 $f_{i,j}\leftarrow f_{i-1,k}$

记 $f_{i-1,w+1}-f_{i-1,w}$ 在 $w$ 处第一次 $\ge c$，则对于所有 $j\ge w$ 都有 $f_{i,j}\leftarrow f_{i-1,w}$

其他的 $j$ 都有 $f_{i,j}\leftarrow f_{i-1,j}$

所以可以得到 $f_{i,j}-|j-a_i|$ 是下凸的，又 $|j-a_i|$ 是下凸的，所以 $f_i$ 是下凸的

考虑维护折线的端点，不难发现每次转移之前所有斜率都在 $[-1,c+1]$ 之间，每次转移先把斜率为 $-1$ 的一端变成斜率为 $0$，把斜率为 $c+1$ 的一端变成斜率为 $c$，最后把 $\le a_i$ 的地方斜率 $-1$，$\ge a_i$ 的地方斜率 $+1$

所以可以用一个可重集合来维护折线端点，初始时集合中有 $c$ 个 $0$，每次在集合中加入两个 $a_i$，表明 $a_i$ 处斜率变化为 $2$；然后取出集合中的最小值 $p$，代表斜率 $-1$ 结束的地方，也就是折线的最小值所在的位置，把 $a_i-p$ 加入答案，代表这次转移加入的 $|j-a_i|$ 使得折线最小值增加了 $a_i-p$；最后从集合中删除最小值和最大值，表明把斜率为 $-1$ 的一端变成斜率为 $0$，把斜率为 $c+1$ 的一端斜率变为 $c$

这样就可以在 $\mathcal O(n\log n)$ 的时间内解决单个序列的问题

回到原问题，考虑如何计数

显然直接计数不好做，考虑对于每个数 $x$ 计算 $F(x)$ 表示 $x$ 作为最小值从集合中删除了多少次

最小值恰好为 $x$ 可以通过差分变成计算最小值小于 $x$，所以可以把 $<x$ 的数看做 $0$，$\ge x$ 的数看做 $1$，统计 $0$ 被作为最小值删除了多少次

显然如果集合中 $c+2$ 个数均为 $1$ 才是不合法的情况，所以可以设 $g_{i,j}$ 表示前 $i$ 个数，集合中有 $j$ 个 $1$ 的方案数，转移显然，最后拿总删除次数减去 $1$ 被删去的次数即可

时间复杂度 $\mathcal O(n^2k(k+c))$

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define p 1000000007
using namespace std;
int n,c,K,ans,b[55][55];
int f[55][55],a[55][55];
int pw[55],unq[2510],N;
int calc(int x){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=K;j++)
			a[i][j]=(b[i][j]>=x);
	memset(f,0,sizeof(f));f[0][0]=1;
	for(int i=1;i<=n;i++){
		int c0=0,c1=0;
		for(int j=1;j<=K;j++)c0+=(!a[i][j]),c1+=a[i][j];
		for(int j=0;j<=c+2;j++){
			int s=j,t=c+2-j;
			if(s&&t)s--;
			else if(s)s-=2;
			f[i][s+2]=(f[i][s+2]+f[i-1][j]*c1)%p;
			f[i][s]=(f[i][s]+f[i-1][j]*c0)%p;
		}
	}int ret=pw[n]*n%p;
	for(int i=1;i<=n;i++)ret=(ret-f[i][c+2]*pw[n-i]%p+p)%p;
	return ret;
}
signed main(){
	scanf("%lld%lld%lld",&n,&c,&K);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=K;j++)scanf("%lld",&b[i][j]),unq[++N]=b[i][j];
	sort(unq+1,unq+N+1);N=unique(unq+1,unq+N+1)-unq-1;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*K%p;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=K;j++)ans=(ans+b[i][j])%p;
	ans=ans*pw[n-1]%p;
	for(int i=1;i<=N;i++)ans=(ans-unq[i]*(calc(unq[i]+1)-calc(unq[i])+p)%p+p)%p;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Scintilla (赞：3)

### [E](https://atcoder.jp/contests/agc049/tasks/agc049_e)

首先考虑如何对于一个序列求解答案。

显然我们可以钦定所有的区间修改操作都是区间 $-1$。设 $f_{i, j}$ 表示考虑到 $i$，有 $j$ 次区间操作覆盖 $i$ 所需的最小代价，转移可拆解为三步：

1. 令 $f_{i, j} = f_{i - 1, j}$；
2. 令 $f_{i, j} \leftarrow f_{i. j} + |a_i - j|$；
3. 令 $f_{i, j} \leftarrow f_{i, k} + c \cdot \max\{j - k, 0\}$。

经典地，使用 slope trick。发现第三个条件会使得不存在斜率为负数的部分，所以我们只需要用一个 `multiset` 维护所有斜率变化的位置。而第三个条件在 $j > k$ 时相当于限制 `multiset` 中的元素数量恰好为 $c$（开始时我们需要往 `multiset` 中加入 $c$ 个 $0$）。

于是我们在经过一些精简后可以写出如下代码：

```cpp
i64 calc() {
  i64 res = 0;
  multiset <int> s;
  rep(i, 1, c) s.insert(0);
  rep(i, 1, n) {
    s.insert(a[i]), s.insert(a[i]);
    res += a[i] - *s.begin();
    s.erase(s.begin()), s.erase(-- s.end());
  }
  return res;
}
```

考虑计算答案。不难想到对于每对 $(i, j, k, l)$，计算 $a_{k, l} - a_{i, j}$ 被统计了多少次。容易通过 dp 求出 $f_{i, j, t, rk}$ 表示 $a_{i, j}$ 在上述代码循环完 $t$ 这一轮之后仍然在 $s$ 中，且排名为 $rk$ 的方案数，于是可以计算答案。

直接做是 $\mathcal{O}(n^5)$ 的，但是容易优化至 $\mathcal{O}(n^4)$。

提交记录：[Submission #43045440 - AtCoder Grand Contest 049](https://atcoder.jp/contests/agc049/submissions/43045440)

---

## 作者：Purslane (赞：2)

# Solution

今天模拟赛搬了这个，感觉是唯一一道算得上是“题”的。做不出来纯作孽吧。

首先，考虑怎么算一个序列 $a$ 需要的最小代价，考虑把问题变成“删到 $0$”。容易想到，我们一定先用单点 $\pm 1$ 的操作使得序列变得比较平坦，然后用区间 $\pm 1$ 变成全 $0$。

基础的调整告诉我们，单点 $\pm 1$ 之后所有的数在原序列 $a$ 中一定出现（或者是 $0$）。

这样容易设计 DP：设 $dp_{i,j}$ 为令 $a'_i=j$ 的最小代价。给定 $a'$ 总代价就是 $C \sum_{i=0}^n \max\{a_i - a_{i+1},0\}$.

转移形如：

$$
dp_{i,j} = |a_i-j| + \min_k \{dp_{i-1,k} + C \max \{j-k,0\}\}
$$

如果你只看这个式子大概率是想不出 $\rm 01 \ trick$ 的。

但是这种式子看着就能用 slope trick。显然是下凸的（二阶差分 $>0$ 的感觉）。考虑 $f_j=\min_k \{dp_{i-1,k} + C \max \{j-k,0\}\}$。那么 $f$ 本质上是将后缀斜率 $> C$ 的进行推平，并且将前缀斜率 $<0$ 的进行推平。

然后是加上 $|a_i-j|$。相当于加入两个横坐标为 $a_i$ 的斜率分界点。当 $x \to + \infty$ 的斜率超过 $C$ 的时候，我们删掉最后一斜率分界点。一定要删掉第一个分界点。

考虑计算 $dp_{i,0}$。由于我们进行了前缀区间推平，所以 $dp_{i,0}$ 就是最小值。

考虑 $dp_{i,0}$ 实际上是什么呢。就是不断加上 $a_i$，并且减去第一个分界点的横坐标。

发现这里就可以 $01$ trick：把 $[a_i \ge v]$ 当做主要的变量，然后计算。容易证明仍然正确。

这样记录一下方案和总答案，就可以做到 $O(Cn^2k)$。

初始的时候 $dp_{0,0}=0$，$dp_{0,x} = + \infty$。当然这是不方便的，实际上设 $dp_{0,x} = cx$ 是可行的。

------

如果你是超级波特直接转成了 $01$ 序列，实际上有更简单的维护方式（虽然我自己也想到了，但是还是感谢 Petit_Souris 给出）：直接维护 $dp_{i,0}$ 和 $dp_{i,1}$。一般来说，你需要维护 $dp_{i,0}$ 以及 $dp_{i,1}$。但是实际上你最终只需要求 $dp_{i,0}$ 的和，转移的时候也只关心 $dp_{i,1} - dp_{i,0}$，因此你可以只在状态里面记录 $dp_{i,1} - dp_{i,0}$ 而把 $dp_{i,0}$ 扔进 DP 的值里面。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50+10,MAXM=2500+5,MOD=1e9+7;
int n,m,c,ans,b[MAXN][MAXM],lsh[MAXN*MAXM],tot,cnt[MAXN][2];
int dp1[MAXN][MAXN],dp2[MAXN][MAXN];
vector<int> upd[MAXN*MAXM];
int main() {
	freopen("mex.in","r",stdin);
	freopen("mex.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>c>>m;
	ffor(i,1,n) ffor(j,1,m) cin>>b[i][j],lsh[++tot]=b[i][j];
	sort(lsh+1,lsh+tot+1),tot=unique(lsh+1,lsh+tot+1)-lsh-1;
	ffor(i,1,n) ffor(j,1,m) upd[lower_bound(lsh+1,lsh+tot+1,b[i][j])-lsh].push_back(i);
	ffor(i,1,n) cnt[i][0]=m;
	roff(tc,tot,1) {
		for(auto id:upd[tc]) cnt[id][0]--,cnt[id][1]++;
		dp1[0][c]=0,dp2[0][c]=1;
		ffor(i,1,n) {
			ffor(j,0,c) dp1[i][j]=dp2[i][j]=0;
			ffor(j,0,c) if(dp2[i-1][j]) {
				int c0=j,c1=c-j;
				ffor(op,0,1) {
					int mul=cnt[i][op],ad=op;
					if(!mul) continue ;
					int nc0=c0+((op^1)<<1),nc1=c1+(op<<1);
					if(nc0) nc0--; else nc1--,ad--;
					if(nc1) nc1--; else nc0--;
					dp2[i][nc0]=(dp2[i][nc0]+1ll*dp2[i-1][c0]*mul)%MOD;
					dp1[i][nc0]=(dp1[i][nc0]+1ll*ad*dp2[i-1][c0]%MOD*mul+1ll*dp1[i-1][c0]*mul)%MOD;
				}
			}
		}
		int res=0;
		ffor(i,0,c) res=(res+dp1[n][i])%MOD;
		ans=(ans+1ll*res*(lsh[tc]-lsh[tc-1]))%MOD;
	}
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：VegeBeany (赞：2)

五次方做法，对@[275307894a](https://www.luogu.com.cn/user/181766) 题解的一个补充。

每个操作都是加一减一，发现可以按值域拆贡献。

先离散化，假设 $a$ 已确定，枚举一层 $b_x\sim b_{x+1}$，把 $a_i$ 设为 $[a_i\ge b_{x+1}]$。

然后算出来把 $a$ 全变为 $0$ 的花费 $w_x$，于是 $\sum{w_x(b_{x+1}-b_x)}$ 就是答案。

然后考虑一层如何算。

设 $f_i$ 为把 $a_{1\sim i}$ 变成 $0$ 的花费。则

$$f_i=\min\{f_{i-1}+[a_i=1],f_k+S_{i}-S_{k}+C\}$$

$S_i$ 表示前缀 $0$ 的个数。

维护一下 $mn=\min\{f_k+S_{i}-S_{k}\}$ 就能 $\mathcal{O}(1)$ 转移。

具体地，每次 $mn\leftarrow \min(mn+[a_i=0],f_i)$ 即可。

最后计数，只需把这个过程塞进状态就行了。

设 $dp_{i,j,k}$ 表示 $f_i=j,mn=k$ 的方案数，可以 $\mathcal{O}(1)$ 转移。

总体 $\mathcal{O}(n^5)$。

```cpp
#include<bits/stdc++.h>
using namespace std;using ll=long long;
int rd(int x=0,char c=getchar()){int f=1;while(!isdigit(c))f=(c^'-'?1:-1),c=getchar();while(isdigit(c))x=x*10+(c^48),c=getchar();return x*f;}
const int N=55;const ll mod=1e9+7;
int n,c,k,T;
ll a[N][N];
ll val[N*N];
ll f[N][N][N];
pair<int,int> to(int a,int b,int p){
	return {min(a+p,b+c+!p),min(b+!p,a)};
}
int main(){
	n=rd(),c=rd(),k=rd();
	for(int i=1;i<=n;i++)for(int j=1;j<=k;j++)a[i][j]=rd(),val[++T]=a[i][j];
	val[++T]=0;
	sort(val+1,val+1+T);
	T=unique(val+1,val+1+T)-val-1;
	ll ans=0;
	for(int B=1;B<T;B++){
		ll w=val[B+1]-val[B];
		memset(f,0,sizeof f);
		f[0][0][0]=1;
		for(int i=1;i<=n;i++){
			int x=0;
			for(int j=1;j<=k;j++)x+=(a[i][j]<=val[B]);
			for(int j=0;j<=i;j++)for(int l=0;l<=i;l++){
				auto X=to(j,l,0);
				(f[i][X.first][X.second]+=f[i-1][j][l]*x)%=mod;
				X=to(j,l,1);
				(f[i][X.first][X.second]+=f[i-1][j][l]*(k-x))%=mod;
			}
		}
		for(int j=0;j<=n;j++)for(int l=0;l<=n;l++)(ans+=f[n][j][l]*j%mod*w)%=mod;
	}printf("%lld",ans);
	return 0;
}
```

---

## 作者：xzy090626 (赞：1)

铜牌题。

这个题目需要一个基本结论：通过 $3$ 操作完成一个序列的代价是 $C\sum \max(a_i-a_{i-1},0)$。

我们可以钦定先做区间、再做单点修改。

那我们考虑先对一个序列做 dp，不妨把状态想得暴力一点，设 $f_{i,j}$ 为当前计算了前 $i$ 个位置，第 $j$ 个位置在区间操作之后为 $c_i$。

那么转移方程就是 $f_{i,j}=|a_i-j|+\min_k (f_{i-1,k}+C\max(j-k,0))$。

然后我们这个地方要用 slope trick 优化了。我之前没有学过这个，所以现在学一下。

学完了。我们考虑分步进行这个转移的过程，首先进行 $f_{i,j}\leftarrow \min(\min_{k\leq j} f_{i-1,k}+C(j-k),\min_{k>j} f_{i-1,k})$。

考虑对于 $k>j$ 的情况，实际上只需要考虑左半边（单调递减），发现可以全部推平为最小值；

对于 $k<j$ 的情况，我们考虑什么时候可以更新，首先显然是只有右半边需要考虑。可以先把所有 $f_{i,j}$ 置为 $f_{i-1,j}$，然后考虑要满足 $f_{i-1,j}>f_{i-1,k}+Cj-Ck$，整理一下就是 $f_{i-1,j}-Cj>f_{i-1,k}-Ck$，这个可以用函数 $f^\prime(i)=f(i)-Ci$ 来表示，$f^\prime(i)$ 实质上就是原函数所有的直线斜率减少 $C$，而不等式的意义是 $f^\prime(j)>f^\prime(k)$。考虑不等式满足的条件，发现新的零点就是原来斜率为 $C$ 的直线的右端点，因此可以用这个零点去更新斜率 $>C$ 的位置，即全部推平。至于为什么不能使用新零点左边的点来更新的原因是，我们发现左侧斜率 $\leq C$，而附加代价的变化率就是 $C$ 了，因此向左一定不优。

然后对于 $|a_i-j|$ 的贡献的维护就是老生常谈了，往维护的容器里塞两个 $a_i$ 即可。

我们注意到，根据更新操作的特点，实际上斜率总是 $\in [-1,C+1]$。那我们考虑使用 multiset 维护斜率集合，操作可以如下刻画：

- 预处理：加入 $C+2$ 个 $0$，这是因为 $f_0(i)=Ci$，即斜率均为 $C$。
- 对于每一轮操作，删去最大值和最小值，这是推平 $-1$ 和 $C+1$ 的段。

- 加入两个 $a_i$。这是加入一个绝对值函数，表示 $a_i$ 处的斜率变化值为 $2$。
- 计算贡献，考虑最小值的变化，也是很套路地统计原来最小值的位置和 $a_i$ 的最小距离，设原来斜率为 $-1$ 的右端点为 $p$，它在更新后斜率变为 $0$，因此贡献要加上 $a_i-p$。显然，$p$ 也是 multiset 里的最小值。

现在，我们可以 $O(n\log n)$ 地解决这个子问题了。

考虑整个流程，即加入 $C+2$ 个 $0$ 之后要循环做的事情：

> 删去最大值和最小值，加入两个 $a_i$，$ans\leftarrow a_i-\min$。

考虑拆开做，首先计算 $a_i$ 部分的贡献系数。由于选了 $a_i$ 之后可以随便选，都能产生贡献，因此贡献系数为 $K^{n-1}$。

考虑统计所有情况下的 $p$ 之和。这里就需要一些 trick 了，首先考虑从值域出发，枚举所有可能的 $p$，计算最小值 $\leq p$ 和 $<p$ 的方案数的差值，就是 $p$ 的贡献系数。这样，就把统计的单点问题转化成区间问题了，而我们也就不关心最大值的情况了。

那我们考虑将问题进一步简化为 $01$ 问题，这样的好处是将 multiset 的维护转化成了单个变量（$1$ 的个数）的维护问题了。不妨让 $a_i\leftarrow [a_i\geq p]$，这样相当于如果有 $0$，那么最小值 $<p$ 成立。

考虑何种情况下最小值不为 $0$。发现每次删除最小值时都会删掉一个最初加上的 $0$（第一轮会删掉两个），因此 $C+1$ 轮之后如果此前全都有 $a_i=1$，那么在第 $C+2$ 轮时如果 $a_i=1$ 那么本轮会出现一次这样的情况。也就是说，当出现 $C+2$ 个 $a_i=1$ 时才能满足条件。此后如果一直满足 $a_i=1$ 那么 $1$ 的数量就会维持在 $C+2$（全部为 $1$），于是可以据此 dp。

设 $f_{i,j}$ 为前 $i$ 个位置，$1$ 的数量为 $j$，那么最小值为 $1$ 的方案数就是 $\sum\limits_{i=1}^n K^{n-i} f_{i,C+2}$；可以容斥一下，总方案数是 $nK^n$，即每个位置都有 $K^n$ 种情况产生或者不产生贡献，这样两个值相减就得到了所有位置满足最小值 $<p$ 的方案数之和 $\sum\limits_{i=1}^n K^n-K^{n-i}f_{i,C+2}$。

现在考虑如何转移。考虑当前的 $f_{i,j}$ 向后进行第 $i+1$ 轮的转移，先删去最大值和最小值，即 $j\leftarrow j-[j>0]-[j=C+2]$。

然后枚举可选的 $K$ 种 $a_i$，注意它们本质的不同只在于与 $p$ 的关系，即有多少个当前能作为 $1$，剩下的作为 $0$。

这样，我们 dp 的复杂度就是 $O(n^2CK)$，这也是总时间复杂度。

---

## 作者：Mirasycle (赞：1)

一个最优化套计数的好题。

先思考最优化，也就是给定唯一 $b$ 序列的情况。将所有数加成 $b_{i,j}$ 看成将 $b_{i,j}$ 削成 $0$。于是下文的所有操作都反过来，加法变减法，减法变加法。

首先这个区间加显然是无意义的，首先单纯加会使得我们背离变成 $0$ 的目标，其次如果区间加和区间减复合的话，我们发现如果一个区间减被 $k$ 个区间加覆盖的话，那么会变成 $k+1$ 个区间减，反正代价都是 $(k+1)C$，那么可以被 $(k+1)$ 个区间减平替。

设这个序列为 $\{a_i\}$，如果只有区间操作的话，那么根据 [P1969 [NOIP 2013 提高组] 积木大赛](https://www.luogu.com.cn/problem/P1969) 的结论，我们的代价是 $C\sum\limits_{i=1}^n \max(0,a_i-a_{i-1})$。

不过我们还有单点加减 $1$ 的操作，这个可以通过设计 DP 来解决。设 $f_{i,j}$ 表示调整之后 $a'_i=j$ 的最小代价。

注意到只有 $j\in \{a_i\}$ 的 $j$ 才是有效值，因为我们 $\pm 1$ 的目的是将一些值调整成一样的，便于一起减。

$$f_{i,j}=|a_i-j|+\min\limits_{k}\{f_{i-1,k}+C\max(0,j-k)\}$$

暴力转移是 $O(n^3)$ 的。注意到这是很显然的 slope trick 的结构，于是可以维护这个下凸函数。

先进行对于 $j<k$ 的转移，就是一个往后的 chkmin 的形式，也就是要把前缀的斜率小于 $0$ 的部分推平。对于 $j>k$ 的转移，可以发现是把后缀斜率大于 $C$ 的部分推平。由于涉及删点，所以考虑用 ` multiset ` 来维护。

初始加入 $C$ 个 $0$ 表示 $a_0$ 的变化代价，第一次的时候可以发现没有大于 $C$ 的斜率和 小于 $0$ 的斜率可以按照常用的加入绝对值函数的方式塞入两个 $a_i$。后面的时候可以发现每次都恰好有一条斜率为 $-1$ 的直线和斜率为 $C+1$ 的直线，直接弹出即可。同时维护斜率为 $0$ 的那一段的高度就是最后的答案，每次动态维护抬升代价即可。由于每次最小点对应的就是斜率为 $0$ 的线的转折点，所以每次累加 $a_i-\rm mn$ 即可。时间复杂度 $O(n\log n)$。

现在考虑如何对于所有序列计算答案，使用考虑贡献法。发现贡献出现在 $a_i$ 和 $\rm mn$ 上面。对于 $a_i$ 是固定贡献，$a_i\times m^{n-1}$。但是 $\rm mn$ 就需要我们进行精细计算了，直接做不好做，涉及相对大小的问题可以通过二分转 $01$ 来计算贡献。

枚举阈值 $v$，将 $\ge v$ 的值设置为 $1$。$v$ 能产生贡献当且仅当 ` multiset ` 中有 $C+2$ 个 $1$，我们需要统计这个方案数。

设 $g_{i,j}$ 表示 $i$ 轮之后 ` multiset ` 内部有 $j$ 个 $1$ 的方案数。每次模拟上述 slope trick 中的更新集合的方式来转移 DP 数组即可。时间复杂度 $O(n^3m)$。


```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pb emplace_back
#define mp make_pair
using namespace std;
const int maxn=55;
const int maxm=2510;
const int mod=1e9+7;
void add(int &x,int y){ x=x+y>=mod?x+y-mod:x+y; }
void sub(int &x,int y){ x=x-y<0?x-y+mod:x-y; }
void cmin(int &x,int y){ x=x<y?x:y; }
void cmax(int &x,int y){ x=x>y?x:y; }
int b[maxn][maxm],a[maxn*maxm],tot,n,C,m,ans=0;
int dp[maxn][maxn],c[maxn],pw[maxn];
int solve(int v){
	memset(dp,0,sizeof(dp));	
	for(int i=1;i<=n;i++) c[i]=m-(lower_bound(b[i]+1,b[i]+1+m,v)-b[i]-1);
	dp[1][0]=m-c[1]; dp[1][2]=c[1]a
	for(int i=2;i<=n;i++)
		for(int j=0;j<=C+2;j++){
			if(!dp[i-1][j]) continue;
			int nj=j-(j>0)-(j==C+2);
			dp[i][nj]=(dp[i][nj]+1ll*dp[i-1][j]*(m-c[i]))%mod;
			dp[i][nj+2]=(dp[i][nj+2]+1ll*dp[i-1][j]*c[i])%mod;
		}
	int res=0;
	for(int i=1;i<=n;i++) add(res,1ll*dp[i][C+2]*pw[n-i]%mod);
	return res;
}
int main(){
	cin>>n>>C>>m; pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=1ll*pw[i-1]*m%mod; 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>b[i][j];
			a[++tot]=b[i][j];
			add(ans,1ll*b[i][j]*pw[n-1]%mod);
		}
	for(int i=1;i<=n;i++) sort(b[i]+1,b[i]+1+m);
	sort(a+1,a+1+tot); tot=unique(a+1,a+1+tot)-(a+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) b[i][j]=lower_bound(a+1,a+1+tot,b[i][j])-a;
	for(int i=1;i<=tot;i++)
		sub(ans,1ll*(a[i]-a[i-1])*solve(i)%mod);
	cout<<ans;
	return 0;
}
```

---

