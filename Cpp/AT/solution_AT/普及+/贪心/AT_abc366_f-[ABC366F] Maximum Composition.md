# [ABC366F] Maximum Composition

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc366/tasks/abc366_f

$ N $ 個の一次関数 $ f_1,f_2,\ldots,f_N $ が与えられます。$ f_i(x)=A_i\ x+B_i $ です。

$ 1 $ 以上 $ N $ 以下の**相異なる** $ K $ 個の整数からなる長さ $ K $ の数列 $ p=(p_1,p_2,\ \ldots\ p_K) $ について、$ f_{p_1}(f_{p_2}(\ldots\ f_{p_K}(1)\ldots\ )) $ としてありえる最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ K\ \leq\ \text{min}(N,10) $
- $ 1\ \leq\ A_i,B_i\ \leq\ 50 $ $ (1\ \leq\ i\ \leq\ N) $
- 入力はすべて整数

### Sample Explanation 1

ありえるすべての $ p $ とそれに対応する $ f_{p_1}(f_{p_2}(1)) $ の値は以下の通りです。 - $ p=\ (\ 1,2\ ) $ : $ f_1(f_2(1))=15 $ - $ p=\ (\ 1,3\ ) $ : $ f_1(f_3(1))=15 $ - $ p=\ (\ 2,1\ ) $ : $ f_2(f_1(1))=10 $ - $ p=\ (\ 2,3\ ) $ : $ f_2(f_3(1))=11 $ - $ p=\ (\ 3,1\ ) $ : $ f_3(f_1(1))=22 $ - $ p=\ (\ 3,2\ ) $ : $ f_3(f_2(1))=26 $ よって、 $ 26 $ と出力します。

## 样例 #1

### 输入

```
3 2
2 3
1 5
4 2```

### 输出

```
26```

## 样例 #2

### 输入

```
10 3
48 40
34 22
24 37
45 40
48 31
49 44
45 40
44 6
35 22
39 28```

### 输出

```
216223```

# 题解

## 作者：lzyqwq (赞：54)

一年一度的 L 国奥林匹克想象学竞赛（LOI）又要开始了。

> 一共有 $n\,(n\le 2\times 10^5)$ 名选手参赛，第 $i$ 名选手的信息被描述成一个一次函数 $f_i(x)=A_ix+B_i$，满足 $1\le A_i,B_i\le 50$。
>
> L 国奥林匹克想象学竞赛国家集训队只有 $k\,(k\le 10)$ 个名额，而国家队只有 $1$ 个名额。L 国计算机学会希望这个选手的 **能力值** 尽可能强。
>
> L 国国集选手的能力值按照以下方式得到：假设 L 国国集选手中排名第 $i$ **大** 的选手为 $p_i$。则对于排名最大的选手 $p_1$ 而言，它的能力值为 $g(p)_{p_1}=f_{p_1}(1)$。对于排名第 $i\,(i\ge 2)$ 的选手而言，他会通过吊打排名在他后一位的选手获得能力值 $g(p)_{p_i}=f_{p_i}(g(p)_{p_{i-1}})$。最终，国家队选手即为 $p_k$，能力值为 $g(p)_{p_k}$。
>
> L 国计算机学会（LCF）清楚每个选手的信息，因此可以通过不同的题目风格筛选选手得到不同的国集名单。因此，可以认为 LCF 能够任意选择 $k$ 个选手进入国集，并任意决定他们的名次。
>
> 小 L 作为 LCF 的特派员，也是曾经的 LOI 选手，需要决定选出哪些选手进入国集并决定他们排名，使得最终进入国家队选手的能力值最大。小 L 需要计算这个最大能力值 $\max g(p)_{p_k}$。

小 L 认为同时决定选手和排名比较困难，于是选择在已知选手的情况下确定排名。小 L 决定将其抽象成序列上的问题。假设排名从大到小选手分别为 $(p_1,\dots,p_k)$。

小 L 首先发现了一个事实：

> $\bf {Obversation\space\space1}$
>
> 若 $(q_1,\dots,q_k)$ 是 $(p_1,\dots,p_k)$ 的一个排列，且 $\exist\,x\in[1,k]\cap\mathbb{Z},q_x\ne p_x$。同时存在 $i$ 满足 $\forall\,j\in[i,k]\cap\mathbb{Z},p_j=q_j$。此时若 $g(p)_{p_{i-1}}> g(q)_{q_{i-1}}$，则 $g(p)_{p_k}> g(q)_{q_k}$。

小 L 轻松地使用数学归纳法和一次函数的单调性证明了这个结论。

有了这个结论后，小 L 发现对于得到最大国家队选手能力值的国集选手 $(p_1,\dots,p_k)$ 中，一定满足 $\forall\,i\in[1,k)\cap\mathbb{Z},A_{p_{i+1}}B_{p_i}+B_{p_{i+1}}\ge A_{p_i}B_{p_{i+1}}+B_{p_i}$。

否则，$\exist\,i\in[1,k)\cap\mathbb{Z},A_{p_{i+1}}B_{p_i}+B_{p_{i+1}}< A_{p_i}B_{p_{i+1}}+B_{p_i}$。

考虑交换 $p_i,p_{i+1}$，记得到的序列为 $(q_1,\dots,q_k)$。

强制令 $g(p)_0=1,p_0=0$，则 $g(p)_{p_1}$ 也能够使用上面的递推式表示。再令 $u=p_i,v=p_{i+1}$。由于交换，所以 $u=q_{i+1},v=q_i$。

由于前 $i$ 项均相同，因此 $g(p)_{p_{i-1}}=g(q)_{q_{i-1}}=x$。则：

- $g(p)_{p_{i+1}}=g(p)_v=f_v(f_u(x))=A_v(A_ux+B_u)+B_v=A_uA_vx+A_vB_u+B_v$。
- $g(q)_{q_{i+1}}=g(q)_u=f_u(f_v(x))=A_u(A_vx+B_v)+B_u=A_uA_vx+A_uB_v+B_u$。

第一项是相同的，后两项根据已知条件可以得到 $A_vB_u+B_v<A_uB_v+B_u$。

因此 $g(p)_{p_{i+1}}<g(q)_{q_{i+1}}$。根据 $\bf{Obversation\space \space 1}$，可以得到 $g(p)_{p_k}<g(q)_{q_k}$。因此 $p$ 一定不优。

所以，小 L 将 $(1,\dots,n)$ 按照如上规则排序得到序列 $(a_1,\dots,a_n)$，选出的 $p$ 一定是 $a$ 的一个长度为 $k$ 的子序列。

接下来，小 L 考虑 dp。设 $F_{i,j}$ 表示所有以 $j$ 结尾长度为 $i$ 的子序列 $a'$ 中，最大的 $g(a')_{a_j}$。若不存在这样的子序列，则 $F_{i,j}=-\infty$，防止其转移时产生贡献。可以考虑第 $i-1$ 个位置在哪里，根据 $\bf{Obversation\space \space 1}$，有 $F_{i,j}=\max\limits_{l=1}^{j-1}f_{a_j}(F_{i-1,l})$。

再次利用一次函数的单调性，$F_{i,j}=f_{a_j}\left(\max\limits_{l=1}^{j-1}F_{i-1,l}\right)$。对于每种长度的子序列维护一个 $F$ 值的前缀 $\max$ 即可。最后答案枚举长度为 $k$ 的子序列的结尾，统计它对答案的贡献即可。

时空复杂度均为 $\mathcal{O}(n(\log n+k))$。[小 L 的代码。](https://atcoder.jp/contests/abc366/submissions/56530757)

回顾这个过程，小 L 猛地发现一个绝望的事实。

$n$ 个选手中，只有 $k$ 个被随机区分了出来。然而被随机区分出来的 $k$ 个选手中，排名大的选手终究成为了排名靠前的选手的炮灰。垫脚石。牺牲品。

而小 L 作为失败的 LOIer，从来没有进入过那 $k$ 个位置。也就是说，他连成为炮灰的资格都没有。这是 LOI 的罪恶本质导致的。而何为原罪？菜是原罪。

小 L 如此热爱 LOI，但是却输得一无所有，成为了 LOI 的备胎。舔狗。小丑。弗如炮灰。弗如垫脚石。弗如牺牲品。

小 L 也许清楚 LOI 的意义是什么。毕竟那是意义啊。是深深令他着迷的。LOI 的。意义啊。小 L 觉得自己为意义。意义。意义。而活着。过着有意义的。惨不忍睹的。LOI 生涯。也会在意义中死去。就像在意义中出生一样。

但是小 L 永远都不可能成为最终剩下的那一个。也许这一切毫无意义。意义究竟是什么。想到这里，小 L 崩溃了，他用力地捶击着桌子。但是他不知道这有什么意义。像他不清楚 LOI 有什么意义一样。

小 L 绝望地哭了出来。但是小 L 甚至不如炮灰。牺牲品。垫脚石。它们不会哭，小 L 也不会哭。

但是小 L 会哭。哭着哭着，小 L 眼前一黑。随后他睁开了双眼，发现自己趴在桌子上。原来小 L 前一天晚上做 [ABC366F Maximum Composition](https://www.luogu.com.cn/problem/AT_abc366_f) 睡着了。刚才经历的一切都是一场梦。梦是假的。是没有意义的。

但是梦是真的。但是梦仍然是没有意义的。

---

## 作者：JuRuoOIer (赞：9)

# 题解 ABC366F - Maximum Composition

本题解为**非正解**，但能 AC 原题目及其 hack 数据。

### 题意

给定 $n \le 2\times10^5$ 个一次函数，对于每个 $1 \le i \le n$，$f_i(x)=a_ix+b_i(a_i,b_i \le 50)$。

求一个长度为 $k$ 的排列 $p(1 \le k \le \min\{n,10\})$，使得 $f_{p_1}(f_{p_2}(\dots f_{p_k}(1)\dots))$ 的值最大。

### 做法 1

我们充分发扬人类智慧：

将所有的函数按照 $a_i^2+b_i$ 的值降序排序。

根据数学直觉，在排序后，选取的函数一定是靠前的。

所以我们对前 $11$ 个函数跑状压 DP，设 $dp_s$ 为方案为 $s$ 时的最大值，转移时枚举下一个选什么即可。注意按照 $\text{popcount}$ 值的顺序枚举状态。

[这样速度快得飞起](https://atcoder.jp/contests/abc366/submissions/56619648)，在我写得特别丑（使用 `vector` 存储 $\text{popcount}(x)=i$ 的所有数）的前提下只需要 $55$ ms。

### 做法 2

我们继续发扬人类智慧：

先贪心地选 $k$ 次，每次选在当前的 $x$ 下能使新的 $x$ 最大的函数。

但这样显然是不对的。hack：

```
2 2
10 0
6 2
```

显然先选第二个是更优的。但是 $x=1$ 时 $f_1(1)=10,f_2(1)=8$，所以贪心就死了。

于是我们往上套个全排列，[这样跑得飞快](https://atcoder.jp/contests/abc366/submissions/56567257)，用状压优化可以更快。

---

## 作者：WerChange (赞：8)

推荐在 [cnblogs](https://www.cnblogs.com/WerChange/p/18354566) 上阅读
# Solution
## 题意简述

现在有 $N$ 个线性函数 $f_1,\dots,f_N$。函数 $f_i(x)=A_ix+B_i$。

找到一个长度为 $K$ 的序列 $p=(p_1,\dots,p_k)$，序列元素为 $K$ 个大小在 $[1,N]$ 的**不同整数**。

输出 $f_{p_1}(f_{p_2}(\dots f_{p_k}(1)\dots))$ 可能的最大值。

## 思路

贪心+DP。

假设现在已经选出了序列 $p$，考虑怎么放（放外层还是内层）答案更优。

钦定 $i<j$，则有两种放法：$f_i(f_j(x))$ 和 $f_j(f_i(x))$。

把 $A$，$B$ 代入：$A_iA_jx+A_iB_j+B_i$ 和 $A_iA_jx+A_jB_i+B_j$。发现其实只有后两项不同，我们钦定排序后越前面的放在越里层，所以我们可以定下排序规则为：

$$
A_iB_j+B_i<A_jB_i+B_j
$$

移项一下：

$$
\frac{A_i-1}{B_i}<\frac{A_j-1}{B_j}
$$

现在取序列 $p$ 是直接取后 $k$ 个就可以了吗？

不对。因为以上排序规则只是解决了怎么放的问题，都是在已经选好了 $p$ 的前提假设下。那怎么取呢？考虑 DP 即可。

经典二维 DP：$f_{i,j}$ 表示当前第 $i$ 个，已选 $j$ 个的最大可能答案。转移就是选与不选，由于我们的排序规则是想越前面的放里层，所以直接从前往后转移就好了，不用倒着转移。

[code](https://atcoder.jp/contests/abc366/submissions/56620226)

---

## 作者：cancan123456 (赞：3)

## 正统做法

设 $f_1(x)=A_1x+B_1,f_2(x)=A_2x+B_2$，那么 $f_2(f_1(x))>f_1(f_2(x))$ 当且仅当 $A_2A_1x+A_2B_1+B_2>A_1A_2x+A_1B_2+B_1$，即 $\dfrac{B_1}{A_1-1}>\dfrac{B_2}{A_2-1}$，所以可以按照 $\dfrac{B_i}{A_i-1}$ 从大到小排序，然后顺序 DP。

时间复杂度为 $O(nk+n\log n)$，可以通过此题。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 200005;
struct Line {
	int a, b;
	ll operator () (const ll & x) {
		return a * x + b;
	}
} line[N];
bool operator < (const Line & a, const Line & b) {
	return a.b * (b.a - 1) > b.b * (a.a - 1);
}
ll f[11][N];
int main() {
//	freopen("in.txt", "r", stdin);
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &line[i].a, &line[i].b);
	}
	sort(line + 1, line + n + 1);
	f[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		f[0][i] = 1;
	}
	for (int i = 1; i <= k; i++) {
		for (int j = i; j <= n; j++) {
			f[i][j] = max(f[i][j - 1], line[j](f[i - 1][j - 1]));
		}
	}
	printf("%lld", f[k][n]);
	return 0;
}
```

## 乱搞做法

我们充分发扬人类智慧：

按照 $A_i^2+B_i$ 从大到小排序。

根据数学直觉，在排序后，答案选取的 $p_i$ 在数组中很靠前。

因此我们取出前 $11$ 个元素，进行状压 DP，就可以通过这道题。

这样速度快得飞起，可以在 [20ms](https://atcoder.jp/contests/abc366/submissions/56618285) 内通过。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 200005, len = 11;
struct Line {
	int a, b;
} line[N];
bool operator < (const Line & a, const Line & b) {
	return a.a * a.a + a.b > b.a * b.a + b.b;
}
ll f[1 << len];
int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &line[i].a, &line[i].b);
	}
	nth_element(line, line + len, line + n);
	n = min(n, len);
	f[0] = 1;
	ll ans = 0;
	for (int S = 1; S < (1 << n); S++) {
		if (__builtin_popcount(S) <= k) {
			for (int i = 0; i < n; i++) {
				if (((S >> i) & 1) == 1) {
					int T = S ^ (1 << i);
					f[S] = max(f[S], line[i].a * f[T] + line[i].b);
				}
			}
			if (__builtin_popcount(S) == k) {
				ans = max(ans, f[S]);
			}
		}
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：ANDER_ (赞：2)

赛后怎么感觉比 E 简单多了（雾）。

## 题意

给定你 $n$ 个函数，$f_i(x) = a_i x + b_i$。现在你需要从 $[1,n]$ 选出 $k$ 个互不相同的下标，以嵌套的形式计算 $1$ 对于这个 $k$ 次函数的最大值。也就是构造长度为 $k$ 序列 $A$，计算 $f_{A_1}(f_{A_2}(f_{A_3}(...f_{A_k}(1))))$ 的最大值。

## 思路

如果我们要将 $f_i$ 嵌套到 $f_j$ 中，其实与 $f_j$ 嵌套到 $f_i$ 中只有一部分不同，其中 $i \not = j$。证明如下：
$$
\begin{aligned}
\because f_i(f_j(x)) &= a_i(a_jx + b_j) + b_i\\
&= a_ia_jx + a_ib_j + b_i\\
\because f_j(f_i(x)) &= a_j(a_ix + b_i) + b_j\\
&= a_ia_jx + a_jb_i + b_j\\
\end{aligned}
$$
$$
\therefore
\begin{cases}
f_i(f_j(x)) > f_j(f_i(x)) &\text{if }a_ib_j + b_i > a_jb_i + b_j\\
f_j(f_i(x)) > f_i(f_j(x)) &\text{if }a_jb_i + b_j > a_ib_j + b_i\\
f_j(f_i(x)) = f_i(f_j(x)) &\text{if }a_jb_i + b_j = a_ib_j + b_i
\end{cases}
$$
分析出优越性，我们可以按照上面的规则排一下序，之后题目就变成了单调最大值的问题。我们就可以用 dp 解决这道题了。设数组 $dp_{i,j}$ 表示前 $i$ 个函数嵌套了 $j$ 层达到的最大值，转移是简单的：$dp_{i,j} = \max(dp_{i-1,j}, a_{p_i} \times dp_{i-1,j-1} + b_{p_i})$，其中 $p_i$ 表示排完序后的函数下标。时间复杂度 $O(n \lg n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define endl "\n"
using namespace std;
//#define MSOD
const int N = 1e6 + 5, M = 2e6 + 2 , MOD = 1e9 + 7;

inline int C(int n, int m) {return (n == m || m == 0) ? 1 : C(n - 1, m) + C(n - 1, m - 1); }
inline int lowbit(int x) {return x & (-x); }
inline int gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b); }
inline int lcm(int a, int b) {return a * b / gcd(a, b); }
inline int exgcd(int a, int b, int &x, int &y) {if(!b) {x = 1, y = 0; return a; } int d = exgcd(b, a % b, y, x); y -= (a / b) * x; return d; }
inline int inv(int a, int m) {int x, y; exgcd(a, m, x, y); return (x % m + m) % m; }
inline int quick_pow(int a, int b) {int res = 1; while(b) {if(b & 1) {res = res * a % MOD; }a = a * a % MOD, b >>= 1; }return res; }

int n, k, a[N], b[N], p[N], dp[N][20];
inline bool cmp(int i, int j) {
	return a[j] * b[i] + b[j] > a[i] * b[j] + b[i];
}
inline void solve() {
	cin>>n>>k;
	for(int i = 1 ; i <= n ; i ++) {
		cin>>a[i]>>b[i];
		p[i] = i;
	}
	sort(p + 1, p + n + 1, cmp);
	dp[0][0] = 1;
	for(int i = 1 ; i <= n ; i ++ ){
		dp[i][0] = 1;
		for(int j = 1 ; j <= i && j <= k ; j ++) {
			dp[i][j] = max(dp[i - 1][j], a[p[i]] * dp[i - 1][j - 1] + b[p[i]]);
		}
	}
	cout<<dp[n][k];
	return;
}
signed main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);
    int T = 1;
#ifdef MSOD
	cin>>T;
#else
#endif
	while(T --) {
    solve();
	}
	return 0;
}
```
##### 2024.08.15 update：管理员大大，提交题解通过后发现公式渲染出了问题，已修正，望通过。

---

## 作者：wangshulin (赞：2)

# 前言
我爱上分。
# 思路
很容易可以想到，如果确定了选那些函数复合起来，它们的嵌套顺序是可以贪心确定的，那让我们来推一下公式——假设当前有两个函数 $f(x)= kx + b$ 和 $g(x) = k'x + b'$，当 $f(g(x))>g(f(x))$ 时：
$$
k(k'x + b')+ b > k'(k x + b) + b' \\
kk'x + kb' + b > kk'x + k'b + b' \\
kb'+b>k'b+b'
$$
可见 $f(g(x)) > g(f(x))$ 是**不由 $x$ 决定**的，而是它们自己的参数。

接着，容易~~感知~~证明仍然存在：
$$f(h_1(h_2(...g(x)...))) > g(h_1(h_2(...f(x)...)))$$
所以直接按照 $kb'+b$ 和 $k'b+b'$ 的大小关系进行排序，将内层的放在前面，这样就可以直接使用背包 dp 水过这道题啦！
# 代码
赛时 [code](https://atcoder.jp/contests/abc366/submissions/56574529)。

---

## 作者：__little__Cabbage__ (赞：1)

## Solution

我们发现 $k \le 10$，于是考虑从这里下手。

首先我们需要排个序，使得先选前面的比先选后面的结果小，也就是 $f_i(f_{i-1}(x)) < f_{i-1}(f_i(x))$，推一下式子：

$$
\begin{aligned}
f_i (f_j (x)) < f_j (f_i (x))
& \Leftrightarrow a_i (a_j x + b_j) + b_i < a_j (a_i x + b_i) + b_j \\
& \Leftrightarrow a_i a_j x + a_i b_j + b_i < a_j a_i x + a_j b_i + b_j \\
& \Leftrightarrow a_i b_j + b_i < a_j b_i + a_i
\end{aligned}
$$

发现 $f_i$ 与 $f_j$ 的先后顺序与 $x$ 无关，于是直接按照上式排序即可。

然后进行 dp。

- 设 $f_{i,j}$ 表示在前 $i$ 个函数中选 $j$ 个且**以第 $i$ 个结尾**（就是套在最外面的那个函数）的最大值；
- 设 $s_{i,j}$ 表示在前 $i$ 个函数中选 $j$ 个的最大值（**不一定要选第 $i$ 个**）。

于是就好转移了，先循环 $i$，再循环 $j$。

- $f_{i,j} = a_i \times s_{i-1,j-1} + b_i$，就是 $i-1$ 个中选 $j-1$ 个的最大值再选上第 $i$ 个的值。
- $s_{i,j} = \max(s_{i-1,j} , f_{i,j})$，这个就不用解释惹。

当然在我的代码里面，数组的第一维被滚掉了（不过不滚掉也可以，因为这题不卡空间）。当然我们也会发现，$f$ 数组其实是不需要的，但为了方便理解，我这里并没有把它扔掉。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;

const int MAXN=2e5+5;
int n,k;
struct func{int a,b;} c[MAXN];
int f[15],s[15];

signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>c[i].a>>c[i].b;
	sort(c+1,c+n+1,[](const func a,const func b)
	{
		return a.a*b.b+a.b<a.b*b.a+b.b;
	});
	
	f[0]=s[0]=1;
	for(int i=1;i<=n;++i)
		for(int j=min(i,k);j;--j)
		{
			f[j]=c[i].a*s[j-1]+c[i].b;
			s[j]=max(s[j],f[j]);
		}
	
	cout<<s[k];
	
	return 0;
}
```

---

## 作者：PineappleSummer (赞：1)

[[ABC366F] Maximum Composition](https://www.luogu.com.cn/problem/AT_abc366_f)

设 $f_{i,j}$ 为前 $i$ 个函数中选 $j$ 个的最大值，假定前面选的函数一定在后面选的函数内。

初始化 $f_{i,0}=1。$转移：$f_{i,j}=\max(f_{i-1,j},f_{i-1,j-1}\times a_i+b_i)$。

为了保证这个转移顺序是正确的，我们需要对函数进行排序。对于 $f_i(x)=a_ix+b_i$，$f_j(x)=a_jx+b_j$ 这两个函数，发现 $f_i(f_j(x))=a_i(a_jx+b_j)+b_i=a_ia_jx+a_ib_j+b_i$，同理得到 $f_j(f_i(x))=a_j(a_ix+b_i)+b_j=a_ia_jx+a_jb_i+b_j$。

两个式子都减去 $a_ia_jx$，得到 $f_i(f_j(x))>f_j(f_i(x))$ 的充要条件是 $a_ib_j+b_i>a_jb_i+b_j$，于是根据这个式子排序即可。

时间复杂度 $\mathcal O(n\log n+nk)$。

```cpp
bool operator < (Node x, Node y) {
	return x.a * y.b + x.b < y.a * x.b + y.b;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
		
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> p[i].a >> p[i].b;
	sort (p + 1, p + n + 1);
	for (int i = 0; i <= n; i++) f[i][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			f[i][j] = max (f[i - 1][j], f[i - 1][j - 1] * p[i].a + p[i].b);
	cout << f[n][k];
	return 0;
}
```

---

## 作者：Ivan422 (赞：1)

给你 $n$ 个线性函数，请你在其中选取 $k$ 个，让 $f_{p_1}(f_{p_2}(\dots f_{p_k}(1) \dots))$ 的值最大。

首先，考虑直接排序。比较相邻的两项 $f_i(x)=a_ix+b_i$ 与 $f_j(x)=a_jx+b_j$，为了让值更大，一定要函数值最大的在前面，即 $a_i\times b_j+b_i$ 一定要小于 $b_i\times a_j + b_j$。得出这个之后，再套一个动态规划。设 $f_{i,j}$ 为前 $i$ 个中选择 $j$ 函数的最大值，直接写一个类似背包的东西即可。


```cpp
//2022tysc0819
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=2e5+10,M=110,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
struct fac{int a,b;}a[N];
int n,k,f[N][M];
bool cmp(fac x,fac y){return x.a*y.b+x.b<x.b*y.a+y.b;}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i].a>>a[i].b;
	sort(a+1,a+n+1,cmp);
	f[1][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=k;j++){
			if(j+1<=k&&f[i][j])f[i+1][j+1]=max(f[i+1][j+1],f[i][j]*a[i].a+a[i].b);
			if(f[i][j])f[i+1][j]=max(f[i+1][j],f[i][j]);
		}
	}
	cout<<f[n+1][k];
    return 0;
}
//note:
```

---

## 作者：irris (赞：0)

## Preface

> 贪心 / 排序, 最优化 / dp

$*1300$，$6.5$。

## Solution

首先排除随机化做法。

假如 $n = k$，考虑如何将操作进行排序使得答案最大？

exchange argument。不妨考虑相邻的两次操作，设其为 $x \gets^{1} ax + b$，$x \gets^{2} cx + d$：

- 若先进行 $1$ 再进行 $2$，$x \gets acx + bc + d$；
- 若先进行 $2$ 再进行 $1$，$x \gets acx + ad + b$。

如果先进行 $1$ 再进行 $2$ 是优的，那么

$$ \begin{aligned}
 & acx + bc + d & > & acx + ad + b \\
\iff & bc + d & > & ad + b \\
\iff & b(c - 1) & > & d(a - 1) \\
\iff & \frac{b}{a - 1} & > & \frac{d}{c - 1} \\
\end{aligned} $$

至此我们将原式写成了，左边只和操作 $1$ 的参数有关、右边只和操作 $2$ 的参数有关的式子，显然可以证明如果「先进行 $1$ 再进行 $2$ 是优的」，「先进行 $2$ 再进行 $3$ 是优的」，那么『先进行 $1$ 再进行 $3$ 是优的』，也就是，具有传递性。

所以接下来的做法是显然的：将所有 $(a, b)$ 按上述规则排序后，不需要考虑讨厌的操作顺序了，由此设计 dp：$f_{i,j}$ 表示前 $i$ 个数使用了 $j$ 次操作，能得到的最大值，即可。

时间复杂度 $\mathcal O(n\log n + nk)$。

## Postscript

笑点解析：排序函数写错了能 AC。

---

## 作者：Sorato_ (赞：0)

# ABC366F Maximum Composition 题解

## 题目大意

给定 $N$ 个一次函数 $f_i(x)=a_ix+b_i$，从中选出 $K$ 个函数 $f_{p_1},f_{p_2},\dots,f_{p_K}$，使得 $f_{p_1}(f_{p_2}(\dots f_{p_K}))$ 最大，求最大值。

## Solve

考虑这样一种情况：我已经选定 $p_{k+1},p_{k+1},\dots,p_K$，现在要去选 $p_k$ 和 $p_{k-1}$，那么对于候选的 $i,j$，怎么选更优？

令 $T=f_{p_{k+1}}(f_{p_{k+2}}(\dots f_{p_K})$。那么选 $p_k=i$ 更优当且仅当

$$
\begin{align}
a_j(a_iT+b_i)+b_j&>a_i(a_jT+b_j)+b_i\\
\iff a_jb_i+b_j&>a_ib_j+b_i\\
\iff (a_j-1)b_i&>(a_i-1)b_j
\end{align}
$$

故我们如果按 $(a_j-1)b_i>(a_i-1)b_j$ 的规则将 $f$ 排序，即可确定嵌套的先后顺序，排在前面的嵌套时更靠里。

既然我们已经知道了先后顺序，求最值可以 dp 求解。

设 $g_{i,j}$ 表示仅从前 $j$ 个函数里选， $f_{p_i}(f_{p_{i+1}}(\dots f_{p_K}))$ 的最大值。则有 $g_{i,j}=\max(g_{i,j-1},a_j\cdot g_{i-1,j-1}+b_j)$。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N=2e5+10,K=15;
int n,m,tot;
long long f[K];
struct zzn{int a,b;}a[N];
bool cmpp(zzn x,zzn y){return x.b*(y.a-1)>y.b*(x.a-1);}
signed main()
{
	n=read();m=read();
	for(int i=1;i<=n;i=-~i)	a[i]={read(),read()};
	sort(a+1,a+n+1,cmpp);
	f[0]=1;
	for(int i=1;i<=n;i=-~i)
		for(int j=m;j;j--)
			f[j]=max(f[j],f[j-1]*a[i].a+a[i].b);
	return printf("%lld",f[m]),0;
}
```

---

## 作者：Redamancy_Lydic (赞：0)

## 题意

给你 $n$ 个一次函数，要求从里面选 $k$ 个并进行嵌套计算结果，问最大计算结果。

## 分析

首先想到 DP，如果我们要使结果最优，那么我们可以先按照函数计算值大小进行排序，然后再选择。

关键在于排序方法。对于两个一次函数 $f(x)=k_1x+b_1$ 和 $g(x)=k_2x+b_2$，进行排序的时候如果我们要判断 $f(g(x))$ 更大还是 $g(f(x))$ 更大，本质上要比较的两个式子是 $k_1(k_2x+b_2)+b_1$ 和 $k_2(k_1x+b_1)+b_2$。可以发现展开后的比较与 $x$ 无关，即我们要比较的是 $k_1b_2+b_1$ 和 $k_2b_1+b_2$。

按照这种方法排序后，我们设 $dp_{i,j}$ 表示在前 $i$ 个函数里面选择 $j$ 个进行计算的最大结果。

初始时根据题意，让 $dp_{i,0}=1(i\in [0,n])$ 即可。 

转移的时候 $dp_{i,j}$ 显然可以从 $dp_{i-1,j}$ 和 $dp_{i-1,j-1}$ 转移过来。

最后输出 $dp_{n,k}$ 就可以愉快的结束了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=5e5+10;
int n,k;
struct no
{
	int x,y;
	inline friend bool operator < (no a, no b)
	{
		return b.x*a.y+b.y>a.x*b.y+a.y;
	}
}a[maxn];
int dp[maxn][12];//前i个里面选j个
signed main() 
{
#ifdef Lydic
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		a[i]={read(),read()};
	sort(a+1,a+n+1);
	for(int i=0;i<=n;i++)dp[i][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=k;j++)
			dp[i][j]=max({dp[i][j],dp[i-1][j-1]*a[i].x+a[i].y,dp[i-1][j]});
	cout<<dp[n][k];
    return 0;
}
```
点个赞再走吧。

---

## 作者：wly09 (赞：0)

## 题意

给定 $N$ 个一次函数 $f_1,f_2,\cdots,f_{N}$，从中选出 $K$ 个，使 $f_{p_1}(f_{p2}(\dots f_{p_k}(1)\dots))$ 最大。

## 思路

先考虑将所有函数依次复合，如何使结果最大，可以联想到排序。

考虑邻项交换，对于相邻的 $f_i$ 和 $f_j$，固定其他函数的顺序，容易说明这两项复合起来越大，总的值也越大。

$$
\begin{aligned}
f_i(f_j(x))
&=f_i(a_jx+b_j)\\
&=a_i(a_jx+b_j)+b_i\\
&=a_ia_jx+a_ib_j+b_i
\end{aligned}
$$

类似地，

$$
f_j(f_i(x))=a_ia_jx+a_jb_i+b_j
$$

那么

$$
f_i(f_j(x))-f_j(f_i(x))=(a_ib_j+b_i)-(a_jb_i+b_j)
$$

因此 $f_i(f_j(x))\ge f_j(f_i(x))$ 当且仅当 $a_ib_j+b_i\ge a_jb_i+b_j$。

那么，我们可以将 $N$ 个函数排序，顺次复合，所得结果一定最大。

现在考虑只能选 $K$ 个，那么这 $K$ 个函数一定是排序后的序列的子序列，考虑 dp。

定义 $g_{i,j}$ 表示考虑前 $i$ 个函数，选了 $j$ 个函数，结果的最大值。

类似背包问题，容易写出转移方程：

$$
g_{i,j}=\max(g_{i-1,j},f_i(g_{i-1,j-1}))
$$

初值是 $g_{0,0}=1$，目标是 $g_{N,K}$。

时间复杂度是 $O(N\log N+NK)$。

[AC 记录](https://atcoder.jp/contests/abc366/submissions/56554825)

---

## 作者：Cynops (赞：0)

简单题。

我们如果找到了复合的最优顺序，直接 dp 即可解决。

具体来说，设 $f(i,j)$ 为前 $i$ 个函数，使用了 $j$ 个函数进行复合的最大价值，转移为 $f(i,j) = \max(f(i-1,j), A_if(i-1,j-1) + B_i)$。

我们考虑邻项交换，若

$$f_i(f_{i+1}(1)) - f_{i+1}(f_i(1)) \ge 0 $$

$$ A_iB_{i+1} + B_i - A_{i+1}B_i - B_{i+1} \ge 0 $$

$$\frac{A_i-1}{B_i} \ge \frac{A_{i+1}-1}{B_{i+1}}$$

那么直接按这个排序，然后 dp 即可。

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
观察题目，发现题目中的选择不太好贪心，我们先放在一边，先观察顺序。
如果我们必定选中 $1,2$ 这两个数，他们的答案分别为：
 $$A_1(A_2x+B_2)+B_1=A_1A_2x+A_1B_2+B_1$$
和
 $$A_2(A_1x+B_1)+B_2=A_1A_2x+A_2B_1+B_2$$
其中 $A_1A_2x$ 是两者共有的一个项，故没有影响，可以忽略，那么排序依据为：
 $$A_1B_2+B_1>A_2B_1+B_2$$
移项得：
 $$({A_1-1}){B_2}>({A_2-1}){B_1}$$

解决完顺序，现在来考虑选择。

用 $f_{i,j}$ 来表示前 $i$ 个数前选了 $j$ 个数的最大值，方程为 
 $$f_{i,j}=\max(f_{i,j},A_i×f_{i - 1,j-1}+B_i,f_{i,j-1})$$
答案为 $f_{n,k}$。
## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,f[5000005][15];
struct node{
	int a,b;
}val[5000005];
bool cmp(node x,node y){
	return (x.a-1)*y.b<(y.a-1)*x.b;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>val[i].a>>val[i].b;
	sort(val+1,val+n+1,cmp);
	f[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=k;j++)
        {
			f[i][j]=f[i-1][j];
			if(j!=0) f[i][j]=max(f[i][j],val[i].a*f[i-1][j-1]+val[i].b);
		}
	cout<<f[n][k];
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
首先得排序，若要让 $f_a(f_b(x))<f_b(f_a(x))$，则一定 $A_a\times B_b+B_a<A_b\times B_a+B_b$，我们就要这样排序。然后进行 dp，$dp_{i,j}=A_i\times\max(dp_{x,j-1})(x<i)+B_i$。其中 $\max(dp_{x,j-1})(x<i)$ 可以使用前缀 $\max$ 优化。答案就是 $\max(dp_{i,k})$。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, k;
ll dp[200005][15], maxx[200005];
pii a[200005];
bool cmp (const pii& a, const pii& b) {
	return a.first * b.second + a.second < b.first * a.second + b.second;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> k;
	maxx[0] = 1;
	for (int i = 1; i <= n; ++ i)
		cin >> a[i].first >> a[i].second;
	sort (a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; ++ i)
		for (int j = k; j; -- j) //要滚动就要倒着
			maxx[j] = max (maxx[j], a[i].first * maxx[j - 1] + a[i].second);
	cout << maxx[k];
	I AK IOI
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc366_f)

一道排序 + dp 题。

看到形如 $A_ix+B_i$ 就很直接地想到排序，我们思考假设现在有两个函数 $f_i,f_j$，且前面的函数嵌套出来的值为 $x$ 时会哪个函数应该被先嵌套。

显然的，$i$ 的贡献为 $A_j(A_ix+B_i)+B_j$，记作 $w_i$。$j$ 的贡献为 $A_i(A_jx+B_j)+B_i$，记作 $w_j$。那么 $i$ 比 $j$ 先嵌套当且仅当 $w_i<w_j$。

容易发现，关于 $x$ 的项可以互相抵消，那么剩下来的 $A_jB_i+B_j<A_iB_j+B_i$ 就可以进行排序。

这样会使得我们从排序后的函数序列中选出来的子序列都是按照**最优方案**进行排列的（即无论怎么交换这个嵌套顺序，这个子序列最终嵌套出来的值不会大于原来的值），现在问题转变成了：
> 给定一个长度为 $n$ 的函数序列 $f_i=A_ix+B_i$，你需要从中选出一个长度为 $k$ 的子序列 $\{p_k\}$，使得 $f_{p_k}(\dots f_{p_2}(f_{p_1}(1))\dots)$ 的值最大。

可以用 dp 解决。

设 $dp_{i,j}$ 表示对于前 $i$ 个函数，在其中选出长度为 $j$ 的子序列的答案是多少。

那么 $dp_{i,j}= \max\{dp_{i-1,j},dp_{i-1,j-1}\times A_i+B_i\}$。对于每一个 $i$，函数子序列都可以选择加入或不加入这个函数。

最终答案为 $dp_{n,k}$。

### Code
```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;
const long long MOD = 998244353;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define REP(i, l, r) for (auto i = (l); i <= (r); i++)
	#define PER(i, r, l) for (auto i = (r); i >= (l); i--)
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	#define SZ(x) (x.size())
	#define fst first
	#define snd second
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
const int N = 200005, K = 15;
int n, k;
ll a[N], b[N], id[N], dp[N][K];
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i] >> b[i], id[i] = i;
	sort(id + 1, id + 1 + n, [](int x, int y) { return a[y] * b[x] + b[y] > a[x] * b[y] + b[x]; }); // 对函数的编号排序
	for (int i = 0; i <= n; i++) dp[i][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= k; j++) dp[i][j] = Max(dp[i - 1][j], dp[i - 1][j - 1] * a[id[i]] + b[id[i]]);
	}
	cout << dp[n][k];
	return 0;
}
```

---

## 作者：Lotus_Land (赞：0)

### 题意

给你 $N$ 个线性函数 $f_1, f_2, \ldots, f_N$，其中 $f_i(x) = A_i x + B_i$。

求由 $K$ 个介于 $1$ 和 $N$ 之间不同整数组成的序列 $p = (p_1, p_2, \ldots, p_K)$ 的最大可能值 $f_{p_1}(f_{p_2}(\ldots f_{p_K}(1) \ldots ))$。

### 分析

套路化地，先来考虑 $f_i(f_j(x))>f_j(f_i(x))$ 需要满足什么条件。

$$
A_i(A_jx+B_j)B_i>A_j(A_ix+B_i)B_j\\
\dfrac{A_i-1}{B_i}>\dfrac{A_j-1}{B_j}
$$

故使得 $f_{p_1}(f_{p_2}(\ldots f_{p_K}(1) \ldots ))$ 最大的序列 $p$，一定满足 $\frac{A_{p_1}-1}{B_{p_1}}\geq\frac{A_{p_2}-1}{B_{p_2}}\geq\dots\geq\frac{A_{p_K}-1}{B_{p_K}}$。

先将原来的函数按 $\frac{A_i-1}{B_i}$ 从大到小排序，那么问题就转化成了求一个贡献最大的 $K$ 长子序列。这个问题可以用动态规划解决。

设 $dp_{i,j}$ 选到第 $i$ 个函数，总共选了 $j$ 个函数的最大贡献。对一个函数只有选与不选两种情况，得到状转方程：

$dp_{i,j}=\max(dp_{i-1,j},dp_{i-1,j-1}\times A_i+B_i)$。时间复杂度 $O(NK)$。

注意函数在计算的时候是从内层往外算的，所以函数的排序实际上是按 $\frac{A_i-1}{B_i}$ 小到大排序。

```cpp
int n,k,a[200005],b[200005],c[200005];
LL dp[200005][15];
bool cmp(int x,int y){
	return b[x]*(a[y]-1)>b[y]*(a[x]-1);
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		c[i]=i;
	}
	sort(c+1,c+1+n,cmp);
	for(int i=1;i<=n;i++){
		dp[i-1][0]=1;
		for(int j=1;j<=k;j++){
			dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]*a[c[i]]+b[c[i]]);
		}
	}
	cout<<dp[n][k];
	return 0;
}
```

---

