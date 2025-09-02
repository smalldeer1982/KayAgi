# Nice to Meet You

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf17-relay-open/tasks/relay2_i

りんご海に $ N $ 個の島が浮かんでおり、$ M $ 社の業者がこれらの島を結ぶ船便を運行しています。便宜上、これらの島を島 $ 1, $ $ 2, $ $ …, $ $ N $ と呼び、これらの業者を業者 $ 1 $, $ 2 $, $ …, $ $ M $ と呼びます。

りんご海の海流は毎日大きく変わります。業者 $ i $ $ (1\ <\ =\ i\ <\ =\ M) $ は、その日の海の状況に応じて、島 $ a_i $ から $ b_i $ への便または島 $ b_i $ から $ a_i $ への便のどちらか一方のみを運行します。どちらの方向の便が運行されるかは、それぞれの業者について独立に、等確率で決定されるものとします。

いま、島 $ 1 $ に高橋くんが、島 $ 2 $ に低橋くんがいます。$ M $ 社の業者による船便を用いて、高橋くんと低橋くんがその日のうちに同じ島に移動することができる確率を $ P $ とします。ただし、船の所要時間などは無視します。このとき、$ P\ ×\ 2^M $ は整数となります。$ P\ ×\ 2^M $ を $ 10^9\ +\ 7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =\ N\ <\ =\ 15 $
- $ 1\ <\ =\ M\ <\ =\ N(N-1)/2 $
- $ 1\ <\ =\ a_i\ <\ b_i\ <\ =\ N $
- 組 $ (a_i,\ b_i) $ はすべて異なる。

### Sample Explanation 1

!\[36cba65088d9b1224a6ce9665aa44048.png\](https://img.atcoder.jp/relay2/36cba65088d9b1224a6ce9665aa44048.png) 上図に示した $ 2^M\ =\ 8 $ 通りの状況が等確率で発生し、そのうち高橋くんと低橋くんが同じ島で出会える状況は $ 6 $ 通りです。したがって、$ P\ =\ 6/2^M, $ $ P\ ×\ 2^M\ =\ 6 $ となります。

## 样例 #1

### 输入

```
4 3
1 3
2 3
3 4```

### 输出

```
6```

## 样例 #2

### 输入

```
5 5
1 3
2 4
3 4
3 5
4 5```

### 输出

```
18```

## 样例 #3

### 输入

```
6 6
1 2
2 3
3 4
4 5
5 6
1 6```

### 输出

```
64```

# 题解

## 作者：MikeDuke (赞：3)

### 简单状态压缩DP。

记 $ F[i][S] $ 为从 $i$ 出发，恰好能通过 $S$ 集合内所有点的方案数

如 $F[1][12]$表示从 $1$ 号点出发，能到达 $1,3,4$ 号点的给边定向的方案数$(12 = 1101)$

记 $ fully[S] $ 为 两端点**都在** $S$ 集合内的边的数量

记 $ partly[S] $ 为 两端点**至少有一个在** $S$ 集合内的边的数量

### 考虑容斥算出$F$

初值为$F[i][S] = 2^{fully[sub]}$ ，即 $S$ 内的边方向任意

接着，$F[i][s] -= F[i][S-subset] * 2^{fully[subset]})$，即减去 $i$ 只能到达 $S$ 的一个子集内的点的方案，此时 $S$ 内除该子集外剩余的边方向任意。

### 考虑容斥算出$ans$

初值为 $ ans = 2^m $，即所有边方向任意

然后减去$1$能到达的点和 $2$ 能到达的点没有交集的情况。

接下来枚举两个子集 $sub1$ 和 $sub2$ ，要求为 $(sub1 ~ \& ~ sub2)$ $ = 0$，且 $sub1$ 和 $sub2$ 之间没有边相连。

保证后者成立的原因是，如果子集之间有边相连，那么不管方向如何，两个子集都会联通。

$ans -= f[1][sub1] * f[2][sub2] * 2^{m-partly[sub1|sub2]}$，即，保证条件（ $1$ 只能到达 $sub1$，$2$ 只能到达 $sub2$ ）成立后，剩余的与 $sub1,sub2$ 没有关系的边方向任意。

于是就做完了。

$code$

使用 $pw$ 预处理 $2$ 的整数次幂。


```cpp
#include <iostream>

using namespace std;

#define M 405
#define ll long long
#define MOD 1000000007

int n, m, all;
int u[M], v[M], fully[(1<<16)], partly[(1<<16)];
ll ilegal, pw[M], f[3][(1<<16)];

inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { (x *= 10) += ch - '0'; ch = getchar(); }
	return x * f;
}

int main()
{
	n = read(), m = read(); all = (1 << n);
	for (int i = 1; i <= m; i++)
		u[i] = read(), v[i] = read();

	pw[0] = 1;
	for (int i = 1; i <= m; i++)
		pw[i] = pw[i-1] * 2 % MOD;

	for (int sta = 0; sta < all; sta++)
		for (int j = 1; j <= m; j++)
		{
			if ( ((sta >> (u[j]-1)) & 1) & ((sta >> (v[j]-1)) & 1) ) fully[sta]++;
			if ( ((sta >> (u[j]-1)) & 1) | ((sta >> (v[j]-1)) & 1) ) partly[sta]++;
		}
		
	for (int i = 1; i <= 2; i++)
		for (int sta = 0; sta < all; sta++)
		{
			if ( !((sta >> (i-1)) & 1) ) continue;
			f[i][sta] = pw[fully[sta]];
			for (int sub = sta; sub; sub = (sub-1) & sta)
				f[i][sta] = ((f[i][sta] - f[i][sta-sub] * pw[fully[sub]] % MOD) % MOD + MOD) % MOD;
		}
		
	for (int sub1 = 0; sub1 < all; sub1++)
		for (int sub2 = 0; sub2 < all; sub2++)
			if ( !(sub1 & sub2) && fully[sub1] + fully[sub2] == fully[sub1|sub2])
				ilegal = (ilegal + f[1][sub1] * f[2][sub2] % MOD * pw[m - partly[sub1|sub2]] % MOD) % MOD; 
 
	cout << ((pw[m] - ilegal) % MOD + MOD) % MOD;

	return 0;
}
```

---

## 作者：AmaoFox (赞：0)

## 题意

+ 有 $N$ 个岛，高桥君和低桥君一个住在岛 $1$，一个住在岛 $2$。（抽象成一张图上的点。）
+ 有 $M$ 艘船，船 $i$ 连接岛 $a_i$ 和岛 $b_i$。但是船每天等概率的往其中的一个方向开。（抽象成有向图上可以任意确定边的方向。）
+ 求高桥和低桥能够走到同一个点的概率乘 $2^M$ 的结果。（这个描述就挺抽象的。）

## 思路

好不容易求出来一个概率，然后你又给我乘回去了？那不又变成求方案数了。  
所以这个问题兜兜转转其实还是让你求最终的方案数。

转眼一看数据范围，什么，$N \le 15$，我于是立刻拿出了我的状压 DP。很迅速的，我发现这个题应该要用 DP 求出从一个点出发，到达指定的点的方案数，以便日后使用。于是我假设 `dp[i][S]` 表示从点 $i$ 出发，恰好到达点集 $S$ 中的每一个点的方案数。显然其实只需要计算 `dp[1][*]` 和 `dp[2][*]` 就足够本道题了。（以下假设 $S$ 是用位压缩过的点集。）

然后我就发现这个题正着做的话要考虑的东西实在是太多了，于是正难则反，考虑使用容斥原理，将所有不符合的情况全都减掉就好了。

不符合的情况指的便是 $1$ 能到达的点和 $2$ 能到达的点集没有重合点的情况，即不连通。考虑两个点集，如果有任何一条边连接两个点集中各一个点，那么这两个点集就联通了。所以我们要找两个不相邻的点集。

为了解决这个问题，让我们引入一个数组 `single[]`，其中 `single[S]` 表示和集合 $S$ 中所有点相连的边的数量。直接 $O(2^N\times M)$ 暴力枚举即可完事。然后，我们开始枚举两个点集 $S_1$ 和 $S_2$。虽然时间复杂度是 $O(2^{2N})$，但是只要代码常数小，你便可以相信你的代码。  
第一步，确保两个点集不是相交的，直接用 `S_1&S_2` 求交集即可。  
第二步，确保两个点集没有相连的边。那么我又要引入一个数组 `couple[]`，其中 `couple[S]` 表示连接集合 $S$ 两个点的边的数量。那么，如果 `couple[S_1] + couple[S_2] == couple[S_1 + S_2]`，我们便可以判断它们之间没有新的边。  
于是，我们便可以得出，没有交集的情况总数应该是 `dp[1][S_1] * dp[2][S_2] * pow(2, m - single[S_1|S_2])`。即点 $1$ 能到达 $S_1$，点 $2$ 能到达 $S_2$，求完点集的并集然后算剩下的自由边数。

接下来你会发现你忘记求 `dp` 数组了，~~比如我当时做题的时候真的忘了~~。`dp` 同样可以用容斥来做。假设说你正在求 `dp[i][S]`，首先你会有 $2^{couple_S}$ 种任意选边的方案。然后，枚举 $S$ 的每一个子集，将只能到达 $S$ 的某一个子集而并不能到达剩余的部分减去即可。不满足的情况是 `dp[i][S_1] * pow(2, couple[S - S_1])`，即只能到达该子集，剩下的边任意摆放。

## 代码

```cpp
#include <iostream>

using namespace std;

const int M = 205, N2 = 1 << 17, mod = 1000000007;

long long a[M], b[M], couple[N2], single[N2], pow2[M], dp[5][N2];

int main() {
  int n, m;
  cin >> n >> m;
  pow2[0] = 1;
  for(int i = 1; i <= m; i++) {
    cin >> a[i] >> b[i];
    pow2[i] = pow2[i - 1] * 2 % mod;
  }
  for(int S = 0; S < (1 << n); S++) {
    for(int j = 1; j <= m; j++) {
      couple[S] += ((S >> (a[j] - 1)) & 1) & ((S >> (b[j] - 1)) & 1); 
      single[S] += ((S >> (a[j] - 1)) & 1) | ((S >> (b[j] - 1)) & 1); 
    }
  }
  for(int i = 1; i <= 2; i++) {
    for(int S = 0; S < (1 << n); S++) {
      if(!((S >> (i - 1)) & 1))  {
        continue; // i 本身必须要到达 i 
      } 
      dp[i][S] = pow2[couple[S]];
      for(int sub = S; sub; sub = (sub - 1) & S) {
        dp[i][S] = ((dp[i][S] - dp[i][S - sub] * pow2[couple[sub]] % mod) % mod + mod) % mod;
      }
    }
  }
  int ans = pow2[m];
  for(int S1 = 0; S1 < (1 << n); S1++) {
    for(int S2 = 0; S2 < (1 << n); S2++) {
      if(!(S1 & S2) && couple[S1] + couple[S2] == couple[S1|S2]) {
        ans = (ans - dp[1][S1] * dp[2][S2] % mod * pow2[m - single[S1 | S2]] % mod + mod) % mod;
      }
    }
  }
  cout << ans;
  return 0;
}
```

## 总结

[AC](https://www.luogu.com.cn/record/133910011)
有的时候一个题需要用 DP，不代表 DP 能求答案，说不定 DP 只是其中的一环。

---

