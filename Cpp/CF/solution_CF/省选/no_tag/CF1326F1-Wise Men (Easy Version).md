# Wise Men (Easy Version)

## 题目描述

This is the easy version of the problem. The difference is constraints on the number of wise men and the time limit. You can make hacks only if all versions of this task are solved.

 $ n $ wise men live in a beautiful city. Some of them know each other.

For each of the $ n! $ possible permutations $ p_1, p_2, \ldots, p_n $ of the wise men, let's generate a binary string of length $ n-1 $ : for each $ 1 \leq i < n $ set $ s_i=1 $ if $ p_i $ and $ p_{i+1} $ know each other, and $ s_i=0 $ otherwise.

For all possible $ 2^{n-1} $ binary strings, find the number of permutations that produce this binary string.

## 说明/提示

In the first test, each wise man knows each other, so every permutation will produce the string $ 11 $ .

In the second test:

- If $ p = \{1, 2, 3, 4\} $ , the produced string is $ 101 $ , because wise men $ 1 $ and $ 2 $ know each other, $ 2 $ and $ 3 $ don't know each other, and $ 3 $ and $ 4 $ know each other;
- If $ p = \{4, 1, 2, 3\} $ , the produced string is $ 110 $ , because wise men $ 1 $ and $ 4 $ know each other, $ 1 $ and $ 2 $ know each other and $ 2 $ , and $ 3 $ don't know each other;
- If $ p = \{1, 3, 2, 4\} $ , the produced string is $ 000 $ , because wise men $ 1 $ and $ 3 $ don't know each other, $ 3 $ and $ 2 $ don't know each other, and $ 2 $ and $ 4 $ don't know each other.

## 样例 #1

### 输入

```
3
011
101
110```

### 输出

```
0 0 0 6```

## 样例 #2

### 输入

```
4
0101
1000
0001
1010```

### 输出

```
2 2 6 2 2 6 2 2```

# 题解

## 作者：AutumnKite (赞：7)

考场上看到 Easy Version $n\le 14$，Hard Version $n\le 18$，莫名就想到了 meet in middle...

可以预处理出 $f_{S,T,i}$ 表示当前排列中数的集合为 $S$，导出的 01 字符串为 $T$，且排列中最后一个数为 $i$ 的方案数。

然后考虑 meet in middle，合并两边的方案。

问题来了，我好像不会快速合并两边的方案 QAQ

但是问题不大，我们可以 **暴力合并**！

直接枚举左边的数集 $S$，最后的 01 串 $T$，以及中间相邻的两个数，显然方案数可以利用 $f$ 进行计算。

但是，你可能需要一些卡常技巧（设两边的大小分别为 $B_1,B_2$）：

1. $f$ 数组只需要预处理所有 $|S|=B_1$ 或 $|S|=B_2$ 的位置，可以直接枚举所有排列进行统计，不需要进行 DP。
2. 显然 01 串反转以后答案是不变的，所以我们只计算 $T\le \operatorname{rev}(T)$ 的位置即可。
3. 可以预处理 $2^n-1,2^{B_1-1}-1,2^{B_2-1}-1$ 的值来减少运算次数。
4. 由于枚举 $T$ 以后我们可以知道中间相邻两个数是否有边，我们可以预处理出与一个点有边/无边的点来快速枚举。
5. 根据代码常数调整 $B_1,B_2$ 的大小。

为了保险，你可以再加上 Ofast 和 O3 优化。

理论时间复杂度 $O(C_{n}^{B_1}(B_1!+B_2!+2^n n^2))$，事实上有好几个 $\frac{1}{2}$ 的常数。

```cpp
int n, E[14][14], bitcnt[1 << 14], rev[1 << 14], p[14], f[1 << 14][1 << 6][14];
long long ans[1 << 14];
std::vector<int> G[14][2];
void solve(){
	read(n);
	for (register int i = 0; i < n; ++i)
		for (register int j = 0; j < n; ++j){
			while (!isdigit(E[i][j] = getchar())) ;
			E[i][j] ^= '0';
			G[i][E[i][j]].push_back(j);
		}
	bitcnt[0] = 0;
	for (register int i = 1; i < (1 << n); ++i) bitcnt[i] = bitcnt[i >> 1] + (i & 1);
	rev[0] = 0;
	for (register int i = 1; i < (1 << (n - 1)); ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << (n - 2);
	int B1 = n >> 1, B2 = n - B1;
	for (register int S = 0; S < (1 << n); ++S)
		if (bitcnt[S] == B1 || bitcnt[S] == B2){
			int cnt = 0;
			for (register int i = 0; i < n; ++i)
				if (S >> i & 1) p[cnt++] = i;
			while (1){
				int T = 0;
				for (register int i = 0; i < cnt - 1; ++i)
					if (E[p[i]][p[i + 1]]) T |= 1 << i;
				++f[S][T][p[cnt - 1]];
				if (!std::next_permutation(p, p + cnt)) break;
			}
		}
	int U = (1 << n) - 1, U1 = (1 << (B1 - 1)) - 1, U2 = (1 << (B2 - 1)) - 1;
	for (register int S = 0; S < (1 << n); ++S)
		if (bitcnt[S] == B1){
			for (register int T = 0; T < (1 << (n - 1)); ++T)
				if (T <= rev[T]){
					int T1 = T & U1, T2 = rev[T] & U2, t = (T >> (B1 - 1)) & 1, _S = U ^ S;
					for (register int i = 0; i < n; ++i)
						if (f[S][T1][i])
							for (int j : G[i][t])
								ans[T] += f[S][T1][i] * f[_S][T2][j];
				}
		}
	for (register int T = 0; T < (1 << (n - 1)); ++T)
		if (T <= rev[T]) print(ans[T], ' '); else print(ans[rev[T]], ' ');
	putchar('\n');
}
```

最后一分钟绝杀的感觉真的非常舒适（

---

## 作者：MatrixCascade (赞：3)

定义 $dp_{S1,i,S2}$ 表示当前选的点状态为 $S1$, 上一个的选的是 $i$, 生成的 $01$ 串当前是 $S2$ 的方案数

每次转移的时候暴力枚举下一位是什么, 复杂度乍一看是 $2^{2n}n^2$ 的, 但是不难发现如果把 $S1$ 的 $0$ 位去掉, 那么 $S2$ 就可以看作是 $S1$ 的子集了, 复杂度其实是 $O(3^nn^2)$ 

但是这么做的空间复杂度是 $O(n4^n)$ 需要用 vector 来实现动态降低空间复杂度至 $O(n3^n)$ (千万不要用 unordered_map, 我一开始用了这个就 T 飞了)

转移没什么细节, 核心代码:
```cpp
rdn;
up(i,0,n-1)
{
	cin>>c[i];
}
up(i,0,(1<<n)-1)
{
	int pp=__builtin_popcountll(i);
	up(j,0,n-1)
	{
		if(i&(1<<j))
		{
			siz[i][j]=(1<<(pp-1));
			dp[i][j].resize(1<<(pp-1));
		}
	}
}
//	dp[0][15][0]=1;
up(i,1,(1<<n)-1)
{
	int pp=__builtin_popcountll(i);
	up(j,0,n-1)
	{
		if(!(i&(1<<j)))continue;
		if(pp==1)dp[i][j][0]=1;
		up(x,0,siz[i][j]-1)
		{
			int y=dp[i][j][x];
			if(!y)continue;
			up(l,0,n-1)
			{
				if(i&(1<<l))continue;
				dp[i|(1<<l)][l][(x<<1)+(c[j][l]=='1')]+=y;
			}
		}
	}
}
up(j,0,n-1)
{
	up(t,0,siz[(1<<n)-1][j]-1)
	{
		ans[t]+=dp[(1<<n)-1][j][t];
	}
}
```

---

## 作者：皎月半洒花 (赞：2)

提供一种比较特别的easy的解法。

首先考虑，对于一个串 $s$ 而言，直接统计比较麻烦，麻烦在难以体现「不认识」这个限制上。所以考虑如何忽略这个限制。考虑忽略限制后，就变成了统计 $ans(s)$ 表示**至少**含有集合 $s$ 的排列数。

那么对于 $ans(s)$ 存在一个性质：如果 $s$ 和 $s'$ 中，连通分量状态相同，那么两个集合的 $ans$ 是等价的。此处连通分量指的是连续一段互相认识的人，状态相同指的是 $s$ 和 $s'$ 的这些段大小相同，排布可以不同。（比如 $0100111\Longleftrightarrow0011101\Longleftrightarrow1000111$） 。

证明很简单，因为对于生成 $01$ 的串而言，其方案数只在于有多少排列可以凑出这些 $1$ 的连续段而已。换言之就是由于是全排列，所以对称。

值得注意的是，对于一个长度为 $k$ 的 $1$ 连续段，其包含 $k+1$ 个互相认识的人，也就是该连通块大小为 $k+1$ 。

考虑如何求 $ans(s)$ 。注意到现在已经转化成了统计每一种对 $n$ 的拆分方式，有多少种排列数。那么一个比较自然的想法就是求下式

![](https://cdn.luogu.com.cn/upload/image_hosting/h4x3figo.png)

其中 $t_i$ 表示枚举的第 $i$ 个点集，$s_i$ 表示组成 $s$ 这个 $01$ 串的第 $i$ 个连通块(链形态的点集) ，$f_{i,j}$ 表示从 $size(i)=j$ 的集合 $i$ 里面选出一个大小为 $j$ 的**链**的方案数。不难知道这些限制的意义：划分必须恰好划分掉 $n$ 个点，且点集之间不存在交集(否则需要合并)。

上式的意义在于，对于 $s$ 的一个划分，每个连通块都需要从某个点集中选出，而点集之间是互不相交的，所以 $size$ 必须恰好是链长。于是可以从这个角度入手来求排列数。同时需要注意，由于我们是硬生生划定了 $p$ 个集合，并不关心集合之间是否有连边，也就代表了其中有些单点(也就是 $s$ 中的 $0$ 位置)可能是与其他连通块是一体的，这也就符合了我们对 $ans(s)$ 的定义：**至少**含有集合 $s$ 的排列数。

注意到 $f$ 是比较容易求得的。考虑 $g_{i,j}$ 表示集合 $i$ 以 $j$ 结尾的链的方案数，那么就是 $n^2$ 转移，保证每次都用最后一个点转移就可以使得形态是一条链。$f$ 就是对 $g$ 的一个累加。这一部分复杂度 $O(n^22^n)$ 。

考虑求出 $f$ 之后如何计算这个式子。一个比较直接的想法是暴力枚举子集的子集来转移，由于 $\Pi$ 对 $\Sigma$ 有分配律，可知转移是不难的。复杂度 $P(n)3^n$，其中 $P(n)$ 是本质不同的划分数。可以过掉 $n=14$ 的 $\rm F1$ 。

代码就不放了，上述过程是比较浅显的。如果需要了解细节可以去我的Hard那个题解里看。

---

## 作者：UKE_Automation (赞：1)

### CF1326F Wise Men

[$\text{Easy Version}$](https://codeforces.com/problemset/problem/1326/F1)，[$\text{Hard Version}$](https://codeforces.com/problemset/problem/1326/F2)

首先直接计数没有什么特别好的办法，因为这个限制的太死了。考虑到串中连续的一段 $1$ 代表图上相连的一条链，而如果只考虑链之间的组合应该是比现在要简单的。这样做的问题就是 $0$ 的限制没有满足，那么考虑容斥，对于串 $S$ 不考虑 $0$ 的限制，这样求出的答案实际上应该是 $S$ 的所有超集的答案之和，也就是说我们只需要再最后做一次 IFMT-and 操作就可以求出正确答案。

现在考虑怎样求出不考虑 $0$ 限制的答案，此时我们 $S$ 这个串应该对应把原图划分为若干条链。设 $S$ 对应的状态把原图划分成的链的长度的可重集合为 $\{a_1,a_2,\cdots, a_k\}$，则 $S$ 的答案应该只和这个集合有关。而这个集合的个数实际上就是把 $n$ 划分成若干正整数之和的方案数，也就是 $n$ 的划分数 $P(n)$；而在 $n=18$ 时 $P(n)=385$，所以我们可以直接爆搜求出这个集合有哪些元素，求 $S$ 答案直接找到对应集合看它的答案即可。

现在考虑怎样求一个集合的答案。首先既然是划分成若干条链那么一定要先求出划分链的方案数。设 $f(i,S)$ 表示当前链结尾为 $i$，走过的点集合为 $S$ 的方案数，直接 $O(2^nn^2)$ dp 是容易的。然后令 $g(S)$ 表示走过点集为 $S$ 的链的方案数，那么求某个集合的方案数，实际上就是求出满足 $|S_i|=a_i$，且 $S_i$ 两两无交、并为全集的 $\prod g(S_i)$ 之和。

三个限制显然不好做，考虑到我们有 $\sum a_i=n$，所以 $S_i$ 并为全集可以直接推出 $S_i$ 两两无交，然后第二个限制可以不管。接下来并为全集以及求积的条件很容易让我们想到 FMT-or，而如果没有条件 $1$ 的话直接做一下 FMT-or 就完了。有了的话其实也不难，原先我们的 $g$ 数组中每一个 $S$ 上都有值，现在我们对于一个 $a_i$，只保留 $|S|=a_i$ 的 $S$ 上的值即可。

这样的话我们在爆搜的时候把 FMT 后的 $g$ 数组的点值乘起来，到最后再做一次 IFMT-or 就能求出并为全集的答案。但实际上由于我们只要全集的答案，所以不需要每次都做 IFMT，直接用容斥 $O(2^n)$ 求出全集上的值即可。

考虑复杂度，我们对于每一个拆分都要遍历一遍然后累乘一下点值，所以设 $S(n)$ 表示 $n$ 的所有分拆数大小之和，复杂度应该是 $O(S(n)2^n)$ 的。

如此复杂度是 $O(2^n(S(n)+n^2))$ 的，可以通过。

```cpp
#include <bits/stdc++.h>
#define il inline
#define btc __builtin_popcount
#define int long long

using namespace std;

const int Maxn = 20, Maxs = 1 << 18;
const int Inf = 2e9;

int n, N, a[Maxn][Maxn];
int f[Maxn][Maxs], g[Maxn][Maxs];

il void FMT_or(int *a, int typ) {
	for(int i = 0; i < n; i++) {
		for(int S = 0; S <= N; S++) {
			if((S >> i) & 1) a[S] += typ * a[S ^ (1 << i)];
		}
	}
}

il void FMT_and(int *a, int typ) {
	for(int i = 0; i < n; i++) {
		for(int S = 0; S <= N; S++) {
			if((S >> i) & 1) a[S ^ (1 << i)] += typ * a[S];
		}
	}
}

vector <int> v;
int now[Maxn][Maxs];
map <vector <int>, int> mp;
il void dfs(int p, int x, int lst) {
	if(x == n) {
		int ret = 0;
		for(int i = 0; i <= N; i++) {
			if(btc(N ^ i) & 1) ret -= now[p][i];
			else ret += now[p][i];
		}
		mp[v] = ret;
//		for(auto i : v) cout << i << " "; cout << ": " << ret << '\n';
		return ;
	}
	for(int i = lst; i <= n - x; i++) {
		v.push_back(i);
		for(int S = 0; S <= N; S++) now[p + 1][S] = now[p][S] * g[i][S];
		dfs(p + 1, x + i, i);
		v.pop_back();
	}
}
int ans[Maxs];
vector <int> s;

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		string s; cin >> s;
		for(int j = 0; j < n; j++) a[i][j + 1] = s[j] - '0';
	}
	N = (1 << n) - 1;
	for(int i = 1; i <= n; i++) f[i][1 << (i - 1)] = 1;
	for(int S = 1; S <= N; S++) {
		for(int i = 1; i <= n; i++) {
			if(!f[i][S]) continue;
			g[btc(S)][S] += f[i][S];
			for(int j = 1; j <= n; j++) {
				if((S >> j - 1) & 1 || !a[i][j]) continue;
				f[j][S | (1 << j - 1)] += f[i][S];
			}
		}
	}
	for(int i = 1; i <= n; i++) FMT_or(g[i], 1);
//	for(int i = 1; i <= n; i++) {
//		for(int j = 0; j <= N; j++) cout << g[i][j] << " ";
//		cout << '\n';
//	}
	for(int i = 0; i <= N; i++) now[1][i] = 1;
	dfs(1, 0, 1);
	N = (1 << n - 1) - 1;
	for(int S = 0; S <= N; S++) {
		s.clear(); int tot = 0;
		for(int i = 1; i < n; i++) {
			if((S >> i - 1) & 1) tot++;
			else s.push_back(tot + 1), tot = 0;
		}
		s.push_back(tot + 1);
		sort(s.begin(), s.end());
		ans[S] = mp[s];
//		cout << bitset<2>(S) << " " << ans[S] << '\n';
	}
	FMT_and(ans, -1);
	for(int i = 0; i <= N; i++) cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：OMG_wc (赞：1)

Easy Version 中 $n$ 最大只有 $14$，可见会用一些暴力点的方法（~~Hard 版本我是不会做的~~）。

$14! \approx 8.7\times 10^{10}$，暴力枚举所有排列显然不可取。最后要统计的是每个二进制串的贡献，如果每次统计贡献的时候只是单纯的加 $1$ 肯定也不行，必定要采取某种计数方法把相同状态的贡献一起计算出来。

既然直接全排列不行，那我们把这 $n$ 个数对半分成两部分（第一部分长度为 $\lfloor {n\over 2} \rfloor$，第二部分长度为 $n-\lfloor {n\over 2} \rfloor$ ），然后各自算出所有全排列的二进制串，再拼接起来。注意拼接的时候，要考虑第一部分最后一个数和第二部分第一个数。

下面来说具体操作：

首先需要从 $n$ 个数划分为两部分，一共有 $C_n^{n\over2}$ 种。对每种组合方式，分别全排列第一部分和第二部分，这一步时间复杂度为 $O({n\over 2}!\times{n\over 2})$。

对第一部分而言，用一个数组 `d1[i][j]` 来统计最后一个数为 $i$，前${n\over2}-1$ 个数组成的二进制串为 $i$ 的方案数。第二部分同理，用一个数组 `d2[i][j]` 来统计第一个数为 $i$，后${n\over2}-1$ 个数组成的二进制串为 $i$ 的方案数。

每个部分不同的状态总数分别为 ${n\over 2}\times 2^{{n\over2}-1}$ 个，然后用四层循环来拼接两个部分，用乘法原理把总贡献算出来，这部分时间复杂度 $O(({n\over 2}\times 2^{{n\over 2}-1})^2)$。

总时间复杂度为 $O(C_n^{n\over2}({n\over 2}\times 2^{{n\over 2}-1})^2)$，把 $n=14$ 代入得到时间频度大概为 6.9 亿，能过本题。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 20;

char a[N][N];
int d1[14][64], d2[14][64];
LL ans[10005];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%s", a[i]);
    int m = n / 2, g = n - m;
    for (int s = (1 << m) - 1; s < 1 << n;) {
        vector<int> b, c;
        for (int i = 0; i < n; i++) {
            if (s >> i & 1)
                b.push_back(i);
            else
                c.push_back(i);
        }
        memset(d1, 0, sizeof d1);
        memset(d2, 0, sizeof d2);
        while (1) {
            int id = 0;
            for (int i = 0; i + 1 < b.size(); i++) {
                id *= 2;
                if (a[b[i]][b[i + 1]] == '1') id++;
            }
            d1[b.back()][id]++;
            if (!next_permutation(b.begin(), b.end())) break;
        }
        while (1) {
            int id = 0;
            for (int i = 0; i + 1 < c.size(); i++) {
                id *= 2;
                if (a[c[i]][c[i+ 1]] == '1') id++;
            }
            d2[c[0]][id]++;
            if (!next_permutation(c.begin(), c.end())) break;
        }
        for (auto t1 : b) {
            for (auto t2 : c) {
                for (int i = 0; i < 1 << m - 1; i++) {
                    for (int j = 0; j < 1 << g - 1; j++) {
                        int id = ((i * 2 + (a[t1][t2] == '1')) << (g - 1) )+ j;
                        ans[id] += (LL)d1[t1][i] * d2[t2][j];
                    }
                }
            }
        }
        int x = s & -s;
        int y = s + x;
        s = ((s & ~y) / x >> 1) | y;
    }

    for (int i = 0; i < 1 << n - 1; i++) {
        printf("%lld%c", ans[i], " \n"[i == (1 << n - 1) - 1]);
    }
    return 0;
}

```



---

## 作者：lfxxx (赞：0)

考虑容斥，我们钦定串的下标集合 $S$ 中的位置为 $1$，计算方案数，将这个方案数数组做一遍逆高维后缀和即得到答案，你发现钦定后带来的效果是按照排列的顺序走存在的边，至少走了若干条长度确定的链，不妨认为这些链构成可重集合 $T$，由于没有钦定的位置你不去管他，所以计数可以考虑先选出这么多条不交的，内部有序的链再去贡献到随意重排的状态上，如果把单点可以看成链放入 $T$ 中，所有链的长度之和为 $n$，故不同的 $T$ 有 $P(n)$ 种，其中 $P(n)$ 表示 $n$ 的拆分数，不妨将 $T$ 中的元素降序排序后写作 $t_1,t_2,\dots,t_k$，合法的排列数为 $\sum_{S_1,S_2,\dots ,S_k,|S_i| = t_i,{\cup_{i=1}^k S_i} = U} \prod dp_{S_i}$，其中 $dp_{S}$ 表示选出一个点集为 $S$ 内部有序的链的方案数，不难在 $O(2^n \times n^2)$ 的时间内求解 $dp_{S}$，注意这里两两集合不交的限制与 ${\cup_{i=1}^k S_i} = U,\sum |S_i| = n$ 等价故可以丢掉，你发现这是一个或卷积的形式，于是令 $g_{i,S} = [\text{popcount}(S) = i] \times dp_S$，合法的排列数就是 $g_{t_1},g_{t_2},\dots ,g_{t_k}$ 的或卷积的第 $U$ 项，考虑对 $g_{i,S}$ 先做一遍 FWT 然后在爆搜拆分数时直接点乘到答案数组中，最后你要求答案数组做逆 FWT 后的第 $U$ 项，于是做到了 $O(2^n \times P(n) \times n)$。

考虑优化。

第一个瓶颈是最后要做一遍逆 FWT，我们发现 FWT 后的数组就是原数组的一个高维前缀和，于是要求出逆 FWT 后的第 $U$ 项可以对至少有一个元素没选这件事做容斥 $O(2^n)$ 求出。

第二个瓶颈是你要在拆分数的搜索树上每个点做一遍 $O(2^n)$ 的点乘，考虑将拆分数最后的一连串 $1$ 压缩起来处理，也就是假若 $t_{i} = t_{i+1} = t_{i+2} = \dots = t_{k} = 1$，通过预处理 $g_{1,v}$ 的若干次方来快速处理点乘若干次，这样的话每个拆分方案会在最后多点乘至多一次，其余的点乘可以视为在合并搜索树子树（这些节点往后均存在至少两种拆分方案，是一个分叉点）中使用故只会点乘 $O(P(n))$ 次，为了进一步减小常数，我们可以把所有的 $g_{i,S}$ 处理出其的若干次幂，那么就可以将拆分数中所有连续的数字放在一起处理。

那么就做到了 $O(2^n \times P(n))$。

[代码](https://codeforces.com/contest/1326/submission/299867703)

---

