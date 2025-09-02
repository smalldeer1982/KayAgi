# Zeros and Ones

## 题目描述

Let $ S $ be the [Thue-Morse sequence](https://en.wikipedia.org/wiki/Thue-Morse_sequence). In other words, $ S $ is the $ 0 $ -indexed binary string with infinite length that can be constructed as follows:

- Initially, let $ S $ be "0".
- Then, we perform the following operation infinitely many times: concatenate $ S $ with a copy of itself with flipped bits.For example, here are the first four iterations:
  
   Iteration $ S $ before iteration $ S $ before iteration with flipped bitsConcatenated $ S $ 1010120110011030110100101101001401101001100101100110100110010110 $ \ldots $  $ \ldots $  $ \ldots $  $ \ldots $

You are given two positive integers $ n $ and $ m $ . Find the number of positions where the strings $ S_0 S_1 \ldots S_{m-1} $ and $ S_n S_{n + 1} \ldots S_{n + m - 1} $ are different.

## 说明/提示

The string $ S $ is equal to 0110100110010110....

In the first test case, $ S_0 $ is "0", and $ S_1 $ is "1". The Hamming distance between the two strings is $ 1 $ .

In the second test case, $ S_0 S_1 \ldots S_9 $ is "0110100110", and $ S_5 S_6 \ldots S_{14} $ is "0011001011". The Hamming distance between the two strings is $ 6 $ .

## 样例 #1

### 输入

```
6
1 1
5 10
34 211
73 34
19124639 56348772
12073412269 96221437021```

### 输出

```
1
6
95
20
28208137
48102976088```

# 题解

## 作者：Alex_Wei (赞：8)

首先，根据数列的构造方式，我们发现在第 $k + 1$ 次操作中 $S_i(0\leq i < 2 ^ k)$ 翻转得到 $S_{i + 2 ^ k}$。对于某个 $i$，从 $0$ 开始从低位到高位一步步构造得到 $i$ 可以证明 $S_i$ 等于 $i$ 在二进制下 $1$ 的个数的奇偶性，即 $S_i = \mathrm{popcount}(i)\bmod 2$。因此，问题相当于求 $\sum\limits_{i = 0} ^ {m - 1} (\mathrm{popcount}(i \oplus (i + n)) \bmod 2)$。

考虑 $i + n$ 在二进制下的计算方式，最低的 $i$ 位会对 $i + 1$ 产生至多 $1$ 的进位贡献。因此，考虑数位 DP，设 $f_{i, c, p, l}$ 表示当前考虑到第 $i$ 位，低 $i - 1$ 位向第 $i$ 位进位 $c$，当前 $\mathrm{popcount}$ 奇偶性为 $p$，$l$ 表示当前是否被 $m$ 限制。

转移枚举第 $i - 1$ 位的值 $v$ 和第 $i - 1$ 位得到进位 $cc$，设 $b$ 为 $m$ 在第 $i - 1$ 位的值，$d$ 为 $n$ 在第 $i - 1$ 位的值。考虑大小限制，若 $l = 1$ 且 $b = 0$ 且 $v = 1$ 则不合法。考虑进位限制，若 $[v + d + cc \geq 2]\neq c$ 则不合法。否则 $f_{i, c, p, l}$ 转移到 $f_{i - 1, cc, p \oplus d\oplus cc, l\land [v = b]}$，因为 $i \oplus (i + n)$ 的当前位为 $v \oplus (v \oplus d\oplus cc)$，所以新的 $\mathrm{popcount}$ 即 $p \oplus d \oplus cc$。

答案即 $f_{0, 0, 1, 0}$，时间复杂度 $\mathcal{O}(T\log n)$。[代码](https://codeforces.com/contest/1734/submission/173376384)。

---

## 作者：fanypcd (赞：5)

尝试写出 $S$：
$$
S_i=
\begin {cases}
0 &(i=0)\\
S_{i-{\rm hibit}(i)}\oplus 1&(i \neq 1)
\end {cases}
$$

然后发现 $S_i={\rm popcount}(i)\%2$。

于是，原询问的答案等价于有多少个整数 $x \in [0,m-1]$，满足 $S_{x}\neq S_{x+n}$，即 $x$ 和 $x+n$ 在二进制下不同位的数量是奇数。

考虑用数位 dp 完成这一过程。

设 $f_{i,j,k}$ 表示选到二进制表示下的第 $i$ 位（最低位为第 0 位），前面连续的 1 的个数的奇偶性为 $j$，前面的变化位数的奇偶性为 $k$ 的选法数。

状态数是 $\log n$ 级别，复杂度 $O(T \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
template <class T> inline void read(T &x) {
	x = 0; int f = 0; char ch = getchar();
	while(!isdigit(ch))
		f |= ch == '-', ch = getchar();
	while(isdigit(ch))
		x = x * 10 + ch - 48, ch = getchar();
	x = f ? -x : x; return;
}
#define inf 0x3f3f3f3f
#define int long long
#define fir first
#define sec second
int b[65], bsz, addb[65], asz;
int f[65][2][2];
int dfs(int p, int lim, int prlen, int st) {
	if(!~p) return st;
	if(!lim && ~f[p][prlen][st]) return f[p][prlen][st];
	int res = 0, up = (lim ? b[p] : 1);
	for(int bit = 0; bit <= up; bit++) {
		int nb = bit ^ addb[p], pb = bit & addb[p];
		res += dfs(p - 1, lim && (bit == up), nb ? (!pb * prlen) ^ 1 : 0ll, st ^ (bit ^ nb) ^ (pb ? prlen ^ 1 : 0));
	}
	if(!lim) f[p][prlen][st] = res;
	return res;
}
signed main() {
//	freopen("data.in", "r", stdin);
	int T, n, m; read(T); while(T--) {
		read(n), read(m);
		memset(f, -1, sizeof(f));
		memset(b, 0, sizeof(b));
		memset(addb, 0, sizeof(addb));
		int x = m - 1; bsz = -1; while(x) {
			b[++bsz] = x & 1;
			x >>= 1;
		}
		x = n; asz = -1; while(x) {
			addb[++asz] = x & 1;
			x >>= 1;
		}
		printf("%lld\n", dfs(max(asz, bsz), 1, 0, 0));
	}
	return 0;
}
```

---

## 作者：小木虫 (赞：3)

### Problem Statement
有一个无限长的 01 串，其生成方式为：  
一开始为一个长度为 1 的 0。  
之后每一次将自己 filp 后拼接到后面。  
现在给你 $n$ 和 $m$，问你这个 01 串的 $[0,m-1]$ 和 $[n,n+m-1]$ 两个子串有多少个位置相同。  
### Solution  
我们容易发现一个位置为 0 还是 1 与其位置的 $\text{popcnt}$ 有关，当 $\text{popcnt}$ 为偶数的时候为 0，反之为 1。  

那么看着如此大的数据范围，你想到了数位 dp。  
由于与 $\text{popcnt}$ 相关，这个数位肯定为二进制数位。  
$[0,m-1]$ 是好处理的，因为从 0 开始，便于计算 $\text{popcnt}$。  
而 $[n,n+m-1]$ 则是 $[0,m-1]$ 的基础上加上一个 $n$。  

于是我们把 $n$ 的数位也搞出来，加上 $n$ 可以直接在 dp 的时候做一个类似于高精度加法的东西同时计算 $[n,n+m-1]$ 的 $\text{popcnt}$，这时候需要充分激发我们的创造性思维，以往的数位 dp 都是从高位往低位走，但是这个加法则需要从低位向高位走。  

那么设状态 $f_{pos,x,y,z,limit}$ 为当前选到 $pos$ 位，$x,y$ 分别代表两个位置目前的 $\text{popcnt}$ 为偶数还是奇数，$z$ 为加法是否进位，$limit$ 的定义则不同于一般的数位 dp，其代表这个位能不能选大于等于这个位上的数的数。  
什么时候不能选呢？显然是低位上有一个后缀，这个后缀的选择第一个大于，其他的全部大于等于其位上的数的情况下。  

code：  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m;
int N[65],M[65];
int f[65][2][2][2][2];
bool vis[65][2][2][2][2];
int dfs(int pos,int x,int y,int z,int limit){
	if(pos==61&&limit)return 0;
	if(pos==61&&x!=(y^z))return 1;
	if(pos==61)return 0;
	if(vis[pos][x][y][z][limit])
		return f[pos][x][y][z][limit];
	vis[pos][x][y][z][limit]=1;
	int sz=M[pos];
	int u=z^N[pos];int res=0;
	for(int i=0;i<=1;i++){
		int l=i>sz;if(limit&&i==sz)l=1;
		res+=dfs(pos+1,x^i,y^i^u,(i&&N[pos])||(i&&z)||(z&&N[pos]),l);
	}return f[pos][x][y][z][limit]=res;
}
void init(){
	
}
void solve(){
	cin>>n>>m;m--;
	for(int i=0;i<=60;i++){
		N[i]=((n>>i)&1);
		M[i]=((m>>i)&1);
		//cout<<(n>>i)<<" "<<N[i]<<" "<<(m>>i)<<" "<<M[i]<<endl;
	}memset(f,0,sizeof(f));
	memset(vis,0,sizeof(vis));
	cout<<dfs(0,0,0,0,0)<<endl;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)init(),solve();
}

```


---

## 作者：PosVII (赞：3)

**前言**

------------

有个小 trick，会了差不多就能做了。

$O(n)$ 做法

------------

考虑暴力枚举点对，不难发现点对 $(i,i+n)$ 的结果可以转化为 $[\text{popcount}(i \oplus (i+n))\mod 2]$，不会的可以想一想，它的转化就是每次 $i=i-2^{\lfloor log_2(i)\rfloor}$，直到 $i=0$ 所操作的次数，显然就是 $\text{popcount}$ 的意思。

$O(\log_2^2 n)$ 做法

------------

打个关于 $i$ 和 $j$ 的表，整出来下面这个矩阵：

```
xooxoxxooxxoxooxoxxox
oxxoxooxxooxoxxoxooxo
oxxoxooxxooxoxxoxooxo
xooxoxxooxxoxooxoxxox
oxxoxooxxooxoxxoxooxo
xooxoxxooxxoxooxoxxox
xooxoxxooxxoxooxoxxox
oxxoxooxxooxoxxoxooxo
oxxoxooxxooxoxxoxooxo
xooxoxxooxxoxooxoxxox
xooxoxxooxxoxooxoxxox
oxxoxooxxooxoxxoxooxo
xooxoxxooxxoxooxoxxox
oxxoxooxxooxoxxoxooxo
oxxoxooxxooxoxxoxooxo
xooxoxxooxxoxooxoxxox
oxxoxooxxooxoxxoxooxo
xooxoxxooxxoxooxoxxox
xooxoxxooxxoxooxoxxox
oxxoxooxxooxoxxoxooxo
xooxoxxooxxoxooxoxxox
```

我们要求的点对是差值相同的，也就是在矩阵上的一条斜线的和。

设函数 $f(i,j)$ 表示从点对 $(0,i)$ 到 $(j-1,i+j-1)$ 这条斜线的和。

整个矩阵其实是一个二维的 Thue-Morse，所以可以发现不同的斜线是可以有规律地拼凑而成的，最显然的是当 $i$ 是偶数时，$f(i,j)=f(i/2,\lfloor j/2 \rfloor)+f(i/2,\lceil j/2 \rceil)$。那么当 $i$ 是奇数时，$f(i,j)=j-f(\lfloor i/2 \rfloor,\lceil j/2 \rceil)-f(\lceil i/2 \rceil,\lfloor j/2 \rfloor)$。

直接搞还是 $O(n)$ 级别的，但是可以用 $\text{map}$ 记忆化一下，秒变 $O(\log_2^2 n)$。

---

## 作者：cryozwq (赞：2)


根据这个神秘生成方式，我们发现一个把一个下标写成二进制，那么在某一位上把 $0$ 变成 $1$ 后，这个值肯定变了，也就是说，每一位取值和下标二进制的 `popcount` 奇偶性是相同的。原问题转化为给定 $n,m$，求 $0$ 至 $n$ 中有多少个 $x$，满足 $x$ 和 $x+m$ `popcount` 奇偶性不同。

如果 $n$ 是二的幂次，那么数位 dp 是容易的，$dp_i,0/1,0/1,0/1$ 表示 $x$ 与 $x+m$ 第 $i-1$ 位是否进位，且 $i-1$ 位 `popcount` 奇偶性是否相同。值得注意是存在 $m>n$ 的情况，这种情况下，考虑 $m>n$ 的部分的 `popcount` 奇偶，枚举最后一位是否进位和奇偶性，就可以统计答案。

那么当 $n$ 不是二的幂次的时候，把它拆成若干个二的幂次，然后可以看成是 给定 $n,m$，求 $0$ 至 $n$ 中有多少个 $x$，满足 $x+m1$ 和 $x+m2$ `popcount` 奇偶性不同，这里不理解可以看代码，相当于把它之前算了的下标加进来，这个问题原来的 dp 仍然适用。

代码见 CF 提交。

---

## 作者：EricWan (赞：1)

这是一个很绕的题。

规定：
+ $\mathrm{highbit}$ 为二进制下最高位对应的二的整数次幂，例如  $\mathrm{highbit}(10)=8$；
+ $\mathrm{popcount}$ 为二进制下 $1$ 的个数，例如  $\mathrm{popcount}(10)=2$。

先分析数列长什么样。$S$ 的定义可以被形式化地写为 $S_i = \lnot S_{i-\mathrm{highbit}(i)}$ 且 $S_0=0$。下标 $i$ 每次减掉一个 $\mathrm{highbit}$，直到 $0$，一共自然会减 $\mathrm{popcount}(i)$ 次，则 $S_i=\mathrm{popcount}(i)$。（我认为这是一个非常简单易懂的证明方法了）

考虑数位 DP，答案问的就是 $[1,m)$ 中有多少个整数 $i$ 满足 $\mathrm{popcount}(i)\bmod2\neq\mathrm{popcount}(n+i)\bmod2$。

然后我们就可以设 $dp_{digit,limit,carry,difference}$ 表示处理完 $digit$ 以上的位置，是否已经小于 $m$，是否需要第 $digit-1$ 位向 $digit$ 位进位，$digit$ 以上位中，$i$ 和 $i+n$ 不同的位的个数为 $difference$ 的数的个数。

初始化自然是 $dp_{61,1,0,0,0}=1$。

转移时就一种可能一种可能人脑分讨就可以。

这里细说以下转移逻辑，我将要将的是我写的主动转移的方法。

$digit$ 一维从大到小枚举。

$limit$ 和其他数位 DP 处理方法相同：
+ $limit=0$ 则 $digit-1$ 位可以填 $0$ 或 $1$；
+ $m$ 在第 $digit-1$ 位是 $1$ 则可以填 $0$ 并取消 $limit-1$ 限制或者填 $1$；
+ 否则填 $0$。

然后我们需要分讨的东西只剩下我们从 $dp_{digit,limit}$ 转移到 $dp_{digit-1,limit'}$ 时的具体转移方法了，其中 $n$ 在第 $digit-1$ 位的值和第 $digit-1$ 位填的数已经知道。

这时就需要再通过 $n$ 在第 $digit-1$ 位的值和 $digit-1$ 位填的数将这个问题分为四种子情况，每种子情况都再需要分第 $digit-2$ 位是否转移这两种子子情况，这里就可以看代码了。

```cpp
#include <bits/stdc++.h>
#define multiple_cases(T) signed T; cin >> T; while (T--)
using namespace std;
#define int long long
int dp[65][2][2][2], n, m, N;
void update(int (*dp1)[2], int (*dp2)[2], int x) {
// 这个函数对应题解中『从 $dp_{digit,limit}$ 转移到 $dp_{digit-1,limit'}$』这一步
	if (x && N) { // 如果 $i+n$ 一定会在 $digit-1$ 位进位
		dp2[0][1] += dp1[1][0];
		dp2[0][0] += dp1[1][1];
		dp2[1][0] += dp1[1][0];
		dp2[1][1] += dp1[1][1];
	} else if (x || N) { // 如果 $i+n$ 是否会在 $digit-1$ 位进位取决于 $i+n$ 是否会在 $digit-2$ 位进
		dp2[0][0] += dp1[0][1 ^ x];
		dp2[0][1] += dp1[0][0 ^ x];
		dp2[1][1] += dp1[1][1 ^ x];
		dp2[1][0] += dp1[1][0 ^ x];
	} else { // 如果 $i+n$ 一定不会在 $digit-1$ 位进位
		dp2[0][1] += dp1[0][1];
		dp2[0][0] += dp1[0][0];
		dp2[1][0] += dp1[0][1];
		dp2[1][1] += dp1[0][0];
	}
}
signed main() {
	multiple_cases(T) {
		cin >> n >> m;
		memset(dp, 0, sizeof(dp));
		dp[61][1][0][0] = 1;
		for (int i = 60; i >= 0; i--) {
			N = bool(n & (1ll << i)); // 为了方便，先计算 $n$ 的第 $i$ 位的值
			update(dp[i + 1][0], dp[i][0], 1); // 这一行和下一行对应题解中『$limit$ 这样处理』第一条
			update(dp[i + 1][0], dp[i][0], 0);
			if (m & (1ll << i)) { // 对应题解中『$limit$ 这样处理』第二条
				update(dp[i + 1][1], dp[i][1], 1);
				update(dp[i + 1][1], dp[i][0], 0);
			} else { // 对应题解中『$limit$ 这样处理』第三条
				update(dp[i + 1][1], dp[i][1], 0);
			}
		}
		cout << dp[0][0][0][1] << endl;
		// 答案状态一定是：第 $0$ 以上的位处理完，不可以从 $-1$ 位进位，$difference=1$
		// 因为题目问 $<m$ 的 $i$，所以 $limit=0$
	}
	return 0;
}
```

---

## 作者：esquigybcu (赞：1)

很奇怪的一种做法，但是过了。好像跟 editorial 的递归做法差不多。

## 题意

定义 $S$ 是 Thue-Morse sequence，构造：

1. 一开始 $S=\texttt{0}$
2. 然后把 $S$ 按位取反之后拼接在 $S$ 后面
3. 把 2 重复无限多次

然后 $q$ 次询问，给定 $n,m$，求 $S_{[0,m)}$ 和 $S_{[n,n+m)}$ 有多少个位不同，下标从 $0$ 开始。

## 做法

首先注意到 $S_i$ 就是 $i$ 的二进制中 $1$ 的个数的奇偶性。

> 证明：对 $i$ 归纳。设 $i$ 的二进制中最高的一位是 $2^k$，那么 $2^k\le n<2^{k+1}$，由构造有 $S_i$ 与 $S_{i-2^k}$ 相反。$\square$

那么问题就变成了对多少个 $0\le i<m$ 有 $S_i\ne S_{i+n}$. 分类讨论 $i$ 的奇偶性。

若 $2|i$ 那么设 $i=2k$，就有 $S_i=S_k,S_{i+n}=S_{k+\lfloor n/2\rfloor}\oplus (n\bmod 2)$（$\oplus$ 记异或）。那么条件就变为 $S_k\ne S_{k+\lfloor n/2\rfloor}\oplus(n\bmod 2)$. 然后问题就被转化为了 $\dfrac{m}{2}$ 规模的问题。$2\nmid i$ 的情况同理。

## 时间/空间复杂度

根据上面的讨论我们知道每次 $(n,m)\mapsto(\lfloor n/2\rfloor,\lfloor (m+1)/2\rfloor),(\lfloor(n+1)/2\rfloor,\lfloor m\rfloor)$，从而我们只需要数 $m$ 和 $n$ 分别可能变成哪些数。

> 引理：有正整数 $n$，每次可以把她变成 $\lfloor n/2\rfloor$ 或者 $\lfloor (n+1)/2\rfloor$，至多可以达到 $O(\log n)$ 个数。

这里感谢 I_am_Accepted 大佬的证明。

> 证明：不难对 $k$ 归纳证明，操作 $k$ 次可以达到的数是两个相邻的数。而操作次数至多 $O(\log n)$，即证。

从而每次至多达到 $O(\log n\log m)$ 个不同的 $(n,m)$，从而时间空间都是 $O(q\log n\log m)$ 的。

## 代码

注意 `unordered_map` 要防 hack。代码中的 `dfs(n, m, i)` 表示有多少个 $0\le j<m$ 满足 $S_j\oplus S_{j+n}\ne i$.

```cpp
// Let QwQ bless me. I love QwQ forever!
 
#include <stdio.h>
#include <stdint.h>
#include <utility>
#include <unordered_map>
#include <chrono>
#include <random>
 
#pragma GCC optimize("-Ofast")
#pragma GCC target("avx2")
 
using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
 
struct hesh
{
    inline size_t operator()(std::pair<u64, u64> p) const
    {
        static const u64 r = std::chrono::high_resolution_clock().now().time_since_epoch().count();
        u64 x = p.first + p.second * r;
        x ^= r;
        x ^= (x >> 29);
        x *= 9;
        return x;
    }
};
 
std::unordered_map<std::pair<u64, u64>, u64, hesh> umap;
 
u64 solve(u64 n, u64 m, u64 i)
{
    if (i == 1) return m - solve(n, m, 0);
    if (m == 0) return 0;
    if (m == 1) return __builtin_parity(n) != 0;
    if (umap.count({n, m})) return umap[{n, m}];
    u64 ans = solve(n / 2, (m + 1) / 2, n % 2) + solve((n + 1) / 2, m / 2, n % 2);
    umap[{n, m}] = ans;
    return ans;
}
 
int main()
{
    int q; scanf("%d", &q);
    while (q--)
    {
        u64 n, m; scanf("%lld %lld", &n, &m);
        printf("%lld\n", solve(n, m, 0));
    }
}
```

---

## 作者：Komomo (赞：0)

这个数列应该是有实际含义的，直觉告诉你这应该是二进制下 popcount 的奇偶，具体就是每次反转就是前半部分的最高位加个 $0$，后半部分最前面加个 $1$。

然后枚举 $i<m$，求的其实是 $\sum\limits_{i=0}^{m-1}\operatorname{popcnt}(i\operatorname{xor} (i+n))\bmod 2$。

这个一看就很数位 dp 对吧。因为加法设计进位，所以我们从低位往高位转移。令 $f_{d,x,P,li}$ 表示目前决策到从低到高第 $d$ 位，$d$ 位之前上面那个和式 $\bmod\ 2$ 的值为 $x$，从 $d-1$ 进位了 $P$，是否有限制。

这个限制有点不一样的。观察到如果从低到高第 $d$ 位出现了超过 $m$ 这一位的值，那么 $d$ 之后必须有一位严格小于 $m$ 的，那可以直接打 $li$ 的标记。

看着前面某些题解的 dp 设计的有点烦，这里放个我的实现：

```cpp
int dfs(int d, int x, int P, bool li) {
	int &mem = f[d][x][P][li];
	
	if (d == 60) return !li * (P ^ x);
	if (~mem) return mem;

	int res = 0;
	for (int i : {0, 1}) {
		int n_li = i > b[d] || li && i >= b[d];
		int dig = a[d] + i + P;
		res += dfs(d + 1, x ^ (dig + i & 1), dig >= 2, n_li);
	}

	return mem = res;
}

void work() {
	int st = read(), l = read() - 1;
	for (int i = 0; i < 60; i ++)
		a[i] = st >> i & 1, b[i] = l >> i & 1;
	
	memset(f, -1, sizeof f);
	cout << dfs(0, 0, 0, 0) << '\n';
}
```

---

