# Palindromic Problem

## 题目描述

You are given a string $ s $ of length $ n $ , consisting of lowercase Latin letters.

You are allowed to replace at most one character in the string with an arbitrary lowercase Latin letter.

Print the lexicographically minimal string that can be obtained from the original string and contains the maximum number of palindromes as substrings. Note that if a palindrome appears more than once as a substring, it is counted the same number of times it appears.

The string $ a $ is lexicographically smaller than the string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ are different, the string $ a $ contains a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 样例 #1

### 输入

```
5
aabaa```

### 输出

```
15
aaaaa```

## 样例 #2

### 输入

```
5
aaaaa```

### 输出

```
15
aaaaa```

## 样例 #3

### 输入

```
4
awoo```

### 输出

```
7
aooo```

# 题解

## 作者：蒟蒻君HJT (赞：8)

不需要脑子的题目。但是没开 long long 把我送走了。

key observation（这也算 observation？）：改变一个字符后，所有经过它的，不以它为中心的回文串都消失了。

先枚举回文中心 $x$，求出原本的回文串数量 $pans$。

这里不妨先假设 $x$ 是某个字符。$x$ 是两个字符中间的情况是是类似的。

定义回文半径 $r$ 为以 $x$ 为中心的回文串的数量，考虑要使得一个回文中心的回文半径 $r$ 增大，需要修改 $s[x-r]$ 或 $s[x+r]$ 为两者中的另一个。修改完之后，我们再求出 $s[x+r+1\sim n]$ 和倒过来看的 $s[1\sim x-r-1]$ 的最长公共前缀长度 $len$，则修改对答案的增加量是 $len+1$。

定义 $f_{i,j}$ 表示将 $s[i]$ 修改为字母 $j$ 对答案增加的贡献（只考虑增加，不考虑减少）。这个用上述方法求即可。

另外还要考虑减少的回文串。对于一个固定的 $x$，若修改 $s[j],x-r+1\leq j \leq x-1$，以 $x$ 为中心的回文串数量减少 $r-i+j$。当 $x+1\leq j \leq x+r-1$，减少量为 $r+i-j$。这两个量都可以表示为关于 $j$ 的一次函数，对一次项系数和零次项系数分别差分维护即可。

由此我们可以快速求出将 $s[i]$ 修改为 $j$ 对答案的改变量。之后只剩下一些 trivial 的讨论，相信来补这道题的同学们应该能自己讨论明白。

因为是 CF 比赛，强烈不建议用哈希，这题用后缀数组求 $\text{lcp}$ 应该是效率最高的。复杂度是 $\Theta(n\log n+n|\sum|)$，$|\sum|$ 是字符集大小。

[for reference only.](https://codeforces.com/contest/1913/submission/237894993)

---

## 作者：2huk (赞：4)

> - 给你一个长为 $n$ 的由小写字母组成的字符串 $s$。你可以将至多一个字母替换为任意小写字母（也可以不换），使得这样操作之后字符串中的回文子串数量最多。输出最多的回文子串数量以及字典序最小的方案。
> - $n \le 3 \times 10^5$。

我们只考虑回文中心为整数的情况（例如 `aba`）。不为整数的情况（例如 `abba`）请读者自行类比完成。~~我不会告诉你让你类比的原因是细节多到这个菜不会写。~~

显然我们可以枚举将哪个位置修改为哪个字符。不妨我们令 $h(i, j)$ 表示将 $a_i \gets j$ 后字符串的回文子串数量。若你所见，$j$ 是一个 `char`。

求解完 $h(i, j)$ 后，$\max h(i, j)$ 即为第一问所求。第二问构造方案也是平凡的。

可以轻易地求出**原**字符串中回文子串的数量 $ori$（比如 manachar 或下文提到的二分 + Hash）。若我们可以求出：

- $f(i, j)$：将 $a_i \gets j$ 后增加了多少回文子串。也即，有多少 $[l, r]$ 满足在原串中不回文，在新串中回文。
- $g(i, j)$：将 $a_i \gets j$ 后减少了多少回文子串。也即，有多少 $[l, r]$ 满足在原串中回文，在新串中不回文。

那么显然有 $h(i, j) = ori + f(i, j) - g(i, j)$。我们考虑分别求解 $f(i, j), g(i, j)$。

---

求解 $f(i, j)$。

首先可以二分 + Hash 求出每个位置的回文半径。即对于每个 $i$ 二分出最大的 $p_i$ 使得 $[i-p_i+1, i+p_i-1]$ 为原串的回文子串。这里有个天然的性质是 $s_{i-p_i} \ne s_{i+p_i}$（若 $i-p_i \ge 1,i+p_i \le n$ 的话）。

顺带说一句，此时 $\sum p_i$ 就是原串的回文子串数量，即上文的 $ori$。

若原串的回文子串数量能增加，就意味着需要存在一些 $p_i$ 增加。也就是说，我们希望让 $s_{i-p_i} \ne s_{i+p_i}$ 变成 $s_{i-p_i} = s_{i+p_i}$。

对于一个位置 $i + p_i$ 而言，若我们将 $s_{i + p_i}$ 修改为 $s_{i - p_i}$，那么以 $i$ 为中心的回文子串数量至少会增加 $1$。但具体增加了多少又可以通过二分计算。若计算出增加了 $\Delta p$，我们就可以将 $\Delta p$ 累加进 $f(i+p_i, s_{i-p_i})$ 中。

同理，对于一个位置 $i - p_i$ 而言，若我们将 $s_{i - p_i}$ 修改为 $s_{i + p_i}$，那么以 $i$ 为中心的回文子串数量至少会增加 $1$。但具体增加了多少又可以通过二分计算。若计算出增加了 $\Delta p$，我们就可以将 $\Delta p$ 累加进 $f(i-p_i, s_{i+p_i})$ 中。

于是实现思路就是用 vector 存储每个 $i \pm p_i$ 所对应的 $i$（代码就是 `vec[i + p[i]].push_back(i), vec[i - p[i]].push_back(i)`），然后访问每个 vector 中的每个位置，修改 $s_{i \pm p_i}$，二分计算增长量 $\Delta p$，将 $\Delta p$ 累加进 $f(i-p_i, s_{i+p_i})$ 或 $f(i+p_i, s_{i-p_i})$，恢复现场。

---

求解 $g(i, j)$。

显然 $g(i, s_i) = 0$。而且对于所有原串的回文子串，只要不是它的回文中心的值发生改变，其余位置改成**任意值**，这个回文子串都会消失。

也就是说我们可以直接求解 $g(i)$ 表示将 $s_i$ 修改为其它任意值后，减少的回文子串的数量。

首先，原串中的所有回文子串，都可以被描述为区间 $[k-y, k+y]$（$y \in [0, p_k - 1]$）的形式。那么若 $i \in [k-y, k+y]$ 且 $i \ne k$，这个子串就可以累加进 $g(i)$ 的计算中。

其中「$i \in [k-y, k+y]$ 且 $i \ne k$」等价于「$i \in [k - y, k - 1]$ 或 $i \in [k + 1, k + y]$」。

所以暴力求解 $g(i)$ 直接枚举 $k, y$ 即可。总复杂度 $\mathcal O(n^3)$。

先考虑优化至 $\mathcal O(n^2)$。仍枚举 $i,k$，然后我们计算 $y$ 有几种合法取值。$y$ 的合法取值数量就是对于 $k$ 而言应该累计入 $g(i)$ 的数量。

分类讨论：

- 当 $i = k$ 时，相当于修改回文中心。这是对回文子串数量没有影响的。
- 当 $i < k$ 时，相当于求有多少 $y$ 满足 $k-y \le i$（表示 $i \in[k - y, k - 1]$），且仍有 $y \in [0, p_k - 1]$，即 $\left\{ \begin{matrix} i < k,\\ k-y \le i,\\0 \le y \le p_k - 1\end{matrix}\right.$。解这个关于 $y$ 的不等式组得 $k - i \le y \le p_k - 1$。那么 $y$ 的取值有 $p_k-k+i$ 种。
- 当 $i > k$ 时，相当于求有多少 $y$ 满足 $k+y \ge i$（表示 $i \in[k + 1, k + y]$），且仍有 $y \in [0, p_k - 1]$，即 $\left\{ \begin{matrix} i > k,\\ k+y \ge i,\\0 \le y \le p_k - 1\end{matrix}\right.$。解这个关于 $y$ 的不等式组得 $i - k \le y \le p_k - 1$。那么 $y$ 的取值有 $p_k+k-i$ 种。

尝试继续优化至线性。我们枚举 $k$，然后计算当前 $k$ 会影响到哪些 $g(i)$。

还是分类讨论：

- 当 $i \in [k - p_k, k - 1]$ 时，$g(i)$ 应增加 $p_k - k + i$。
- 当 $i \in [k + 1, k + p_k]$ 时，$g(i)$ 应增加 $p_k + k - i$。

这个是很好差分维护的。

---

分析复杂度。求解回文半径 $p_i$ 可以用 $\mathcal O(n)$ 的 manacher 或 $\mathcal O(n \log n)$ 的二分 + Hash。求解 $f(i, j)$ 时，遍历每个 vector 中的所有元素均摊 $\mathcal O(n)$，二分求增长的回文半径 $\Delta p$ 复杂度 $\mathcal O(\log n)$，总复杂度 $\mathcal O(n \log n)$。求解 $g(i, j)$ 时，差分复杂度 $\mathcal O(1)$，总复杂度 $\mathcal O(n |\Sigma|)$，其中 $|\Sigma| = 26$。计算最终答案复杂度 $\mathcal O(n |\Sigma|)$。

总复杂度 $\mathcal O(n \log n + n|\Sigma|)$。可过。

~~代码这个菜实在不会写就不给了。~~

---

## 作者：Sunny郭 (赞：3)

虽然是 CF，但是赛后补题。hash， 启动！~~（其实是不会SA）~~

字符集是 $26$ 的，可以考虑直接枚举改哪个字符，改成什么。

但是我们不可能每次都去枚举，考虑修改一个字符对于答案的改变。

设当前修改位置为 $k$。

- 本来跨过 $k$ 的回文串都会消失

考虑怎么计算预处理这个事情。

发现当回文串形如 `a b c b a` 时，改变每个位置的字符后减少的回文串数量形如 `1 2 3 2 1` 这样先上升再下降的形式。考虑维护这个东西。

设 $l$ 为回文串左端点，$r$ 为回文串右端点，$i$ 为回文串中心。我们不用平时的一阶变化（即直接差分，形如 $s_l+1$，$s_{r+1}-1$）。考虑二阶变化，我们维护一个 $dt$ 数组记录变化量，在 $dt_l+1$，$dt_{i+1}-2$，$dt_{r+1}+1$，我们再维护一个数组 $c$，这个也就是最终记录每个位置有多少字符串跨过去的影响了。

考虑如何维护 $c$？从左往右扫，记录累加的变化量 $dt$ 并记录在 $c$ 中。

对于形如 `a b c c b a` 的字符串留给作者思考。

- 本来回文串右端点为 $k-1$ 且回文中心小于 $k$ 的，或者本来回文串左端点为 $k+1$ 且回文中心大于 $k$ 的。

这是好维护的，用 vector 预处理每个地方有哪些回文中心，枚举 $k$ 的时候拿出来算就行。考虑怎么算？直接 hash + 二分！

时间复杂度是 $O(n|\Sigma|+ n \log n)$

记得开 long long。

```cpp
//奇回文串：形如aba，偶回文串：形如abba
#include<bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;

const int N = 3e5 + 7;
const int B = 1721, M = 1e9 + 3;
int i, j, k, n, m, l, r, mid, res, sum, L, R, ans, ai;
int hl[N], hr[N], g[N];//hash使用 
int p[N], q[N];//pi表示以i为回文中心的奇回文串的回文半径，q偶回文串 
int c[N], dt[N];
//dt变化量，c回文串个数， 
vector<int> u[N], v[N];
//u_i以i为端点的奇回文串的回文中心，v_i存偶回文串 
char s[N], as;
int subl(int x, int y) {return (hl[y] - hl[x] * g[y - x] % M + M) % M;}
int subr(int x, int y) {return (hr[x] - hr[y] * g[y - x] % M + M) % M;}
void init_hash() {
	for(g[0]=i=1; i<=n; i++) g[i] = g[i-1] * B % M;
	for(i=1; i<=n; i++) hl[i] = (hl[i-1] * B % M + s[i]) % M;
	for(i=n; i>=1; i--) hr[i] = (hr[i+1] * B % M + s[i]) % M;
}
void init_string() {
	for(i=1; i<=n; i++) {
		l = 0, r = min(i, n - i + 1);
		while(l <= r) {
			mid = l + r >> 1;
			if(subl(i - mid, i) == subr(i, i + mid)) res = mid, l = mid + 1;
			else r = mid - 1;
		}
		sum += p[i] = res, l = i - res + 1, r = i + res - 1;
		u[l].pb(i);
		if(l != r) u[r].pb(i);
		++dt[l], ++dt[r+2], dt[i+1] -= 2;
	}
	for(i=1; i<n; i++) {
		if(s[i] != s[i+1]) continue;
		l = 0, r = min(i, n - i);
		while(l <= r) {
			mid = l + r >> 1;
			if(subl(i - mid, i) == subr(i+1, i + mid + 1)) res = mid, l = mid + 1;
			else r = mid - 1;
		}
		sum += q[i] = res, l = i - res + 1, r = i + res;
		v[l].pb(i);
		if(l != r) v[r].pb(i);
		++dt[l], ++dt[r+2], --dt[i+1], --dt[i+2];
	}
	int d = 0, s = 0;
	for(i=1; i<=n; i++) d += dt[i], s += d, c[i] = s;
	ans = sum;
}
void solve() {
	for(k=1; k<=n; k++) {
		for(char s='a'; s<='z'; s++) {
			int tmp = sum - c[k] + p[k];
			for(int i : u[k-1]) {
				if(i >= k) continue;
				l = p[i] + 2, r = min(i, n - i + 1);
				L = i - p[i], R = i + p[i] + 1;
				if(::s[L] != s) continue;
				--L; res = l - 1;
				while(l <= r) {
					mid = l + r >> 1;
					if(subl(i - mid, L) == subr(R, i + mid)) res = mid, l = mid + 1;
					else r = mid - 1;
				}
				tmp += res - p[i];
			}
			for(int i : u[k+1]) {
				if(i <= k) continue;
				l = p[i] + 2, r = min(i, n - i + 1);
				L = i - p[i] - 1, R = i + p[i];
				if(::s[R] != s) continue;
				++R; res = l - 1;
				while(l <= r) {
					mid = l + r >> 1;
					if(subl(i - mid, L) == subr(R, i + mid)) res = mid, l = mid + 1;
					else r = mid - 1;
				}
				tmp += res - p[i];
			}
			for(int i : v[k-1]) {
				if(i >= k-1) continue;//注意这里，要-1，不然会被讨论区大佬hack
				L = i - q[i], R = i + q[i] + 2;
				l = q[i] + 2, r = min(i, n - i);
				if(::s[L] != s) continue;
				--L; res = l - 1;
				while(l <= r) {
					mid = l + r >> 1;
					if(subl(i - mid, L) == subr(R, i + mid + 1)) res = mid, l = mid + 1;
					else r = mid - 1;
				}
				tmp += res - q[i];
			}
			if(::s[k-1] == s) {
				i = k - 1; res = 1;
				l = 2, r = min(i, n - i);
				L = i - 1, R = k + 1;
				while(l <= r) {
					mid = l + r >> 1;
					if(subl(i - mid, L) == subr(R, i + mid + 1)) res = mid, l = mid + 1;
					else r = mid - 1;
				}
				tmp += res;
			}
			for(int i : v[k+1]) {
				if(i <= k) continue;
				L = i - q[i] - 1, R = i + q[i] + 1;
				l = q[i] + 2, r = min(i, n - i);
				if(::s[R] != s) continue;
				++R; res = l - 1;
				while(l <= r) {
					mid = l + r >> 1;
					if(subl(i - mid, L) == subr(R, i + mid + 1)) res = mid, l = mid + 1;
					else r = mid - 1;
				}
				tmp += res - q[i];
			}
			if(::s[k+1] == s) {
				i = k; res = 1;
				l = 2, r = min(i, n - i);
				L = k - 1, R = k + 2;
				while(l <= r) {
					mid = l + r >> 1;
					if(subl(i - mid, L) == subr(R, i + mid + 1)) res = mid, l = mid + 1;
					else r = mid - 1;
				}
				tmp += res;
			}
			if(tmp == ans) {
				if(ai != k && (::s[ai] < as || (::s[ai] == as && ::s[k] > s))) ai = k, as = s;
			}
			if(tmp > ans) {
				ans = tmp;
				ai = k, as = s;
			}
		}
	}
}
signed main() {
	scanf("%lld%s", &n, s+1);
	init_hash();
	init_string();
	solve();
	s[ai] = as;
	printf("%lld\n%s", ans, s+1);
	return 0;
}

```

---

## 作者：Nt_Tsumiki (赞：2)

考虑修改第 $x$ 位会造成什么影响。

一下只讨论奇回文串，偶回文串同理。

具体的，对于每个回文中心 $i$ 求出原串的极长回文串的左右端点 $L,R$，那么本质不同 $x$ 只有两段，$[L,i)\cup(i,R]$ 和 $L-1,R+1$。

对于 $x\in[L,i)\cup(i,R]$，不难发现只要改了那么一定会造成回文串减少，对于回文中心 $i$ 来说，当 $x\in[L,i)$ 时减少的数量为 $x-L+1$；当 $x\in(i,R]$ 时减少的数量为 $R-x+1$。上面这两项都是与 $x$ 有关的一次函数差分前缀和即可。

对于 $x=L-1$ 或者 $x=R+1$ 时，我们求出 $k=\text{LCP}(s^R[n-L+3:n],s[R+2:n])$ 那么当 $s_{L-1}$ 改为 $s_{R+1}$ 或者 $s_{R+1}$ 改为 $s_{L-1}$ 时会产生 $k+1$ 的贡献，开数组记录一下就行。

最后我们枚举 $x$ 和改成什么就行。

但是输出字典序最小方案有点没素质了。

考虑把 $x$ 改成小于 $s_x$ 的字符，从前往后扫一遍，然后判一下什么也不改是否最优，最后在考虑把 $x$ 改成大于 $s_x$ 的尽可能小的字符，从后往前扫一遍，中途出现答案直接 break 就行。

[submission](https://codeforces.com/contest/1913/submission/306303658)

---

## 作者：ddxrS_loves_zxr (赞：2)

枚举改变的位置以及字符。

考虑修改位置 $i$ 的字符对回文串数量造成的影响：**原答案**减去**包含 $i$ 的回文串数量**再加上**以 $i$ 为中心的回文串数量**和**新增的回文串数量**。

我们可以将答案分成这四个部分来分别求解。

可以预处理出以每个位置（也包括两个字符之间的位置）作为回文中心能够得到的回文串的左右区间 $[L_i,R_i]$。那么以 $i$ 为中心的回文串数量就是 $\lceil\frac{R_i-L_i+1}{2}\rceil$，对每个 $i$ 求和即可得到原答案。

接下来考虑如何求解包含 $i$ 的回文串数量。我们知道了每个中心所拥有的回文串的区间，$L_i$ 和 $R_i$ 的贡献是 $1$，$L_i+1$ 和 $R_i-1$ 的贡献是 $2$，以此类推。我们可以通过两遍差分来计算。

具体来说，对于 $[L_i,i]$ 这个区间，回文串数量从 $1$ 一直加到 $L_i-i+1$，对于 $[i,R_i]$（若是以 $i$ 和 $i+1$ 之间为中心就是 $[i+1,R_i]$） 这个区间，回文串数量从 $R_i-i+1$ 一直减到 $1$。我们可以先用一个差分数组来维护增量的差值，求前缀和得到每个位置会**增加/减少**的回文串数量，再求前缀和得到包含这个位置的回文串数量。

最后是统计新增回文串的数量。考虑什么情况下，我们改变一个位置的字符会使回文串数量增加。对于一个回文中心，若我们想让以它为中心的回文串数量增加，我们可以将 $s_{L_i-1}$ 修改为 $s_{R_i+1}$ 或把 $s_{R_i+1}$ 修改为 $s_{L_i-1}$。新增的回文串数量也可以用二分来求出。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll base = 29, mod = 1e9 + 7;
const int N = 3e5 + 5, M = 27;
int n, p1, p2;
string s;
ll has[N][2], pw[N], L[N + N], R[N + N], tot[N], cnt[N][M], sum, ans, res;
ll get(int l, int r, int opt) {return (l > r) || (!opt ? (has[r][opt] + mod - has[l - 1][opt] * pw[r - l + 1] % mod) % mod : (has[l][opt] + mod - has[r + 1][opt] * pw[r - l + 1] % mod) % mod);}
int find(int p1, int p2) {
    if(p1 < 1 || p2 > n) return 0;
    int l = 0, r = min(p1, n - p2 + 1), ans = 0;
    while(l <= r) {
        int mid = l + r >> 1, L = p1 - mid + 1, R = p2 + mid - 1;
        if(get(L, p1, 0) == get(p2, R, 1)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    return ans;
}
int main() {
    cin>>n>>s; s = '#' + s;
    for(int i = pw[0] = 1; i <= n; i++) has[i][0] = (has[i - 1][0] * base % mod + s[i]) % mod, pw[i] = pw[i - 1] * base % mod;
    for(int i = n; i >= 1; i--) has[i][1] = (has[i + 1][1] * base % mod + s[i]) % mod;
    for(int i = 1; i <= n; i++) {
        int d = find(i, i);
        L[i] = i - d + 1, R[i] = i + d - 1, sum += d;
        if(L[i] > 1 && R[i] < n) {
            int k = find(L[i] - 2, R[i] + 2);
            cnt[L[i] - 1][s[R[i] + 1] - 'a'] += (k + 1);
            cnt[R[i] + 1][s[L[i] - 1] - 'a'] += (k + 1);
        }
        if(L[i] <= R[i]) tot[L[i]]++, tot[i + 1]--, tot[i + 1]--, tot[R[i] + 1 + 1]++;
    }
    for(int i = 1; i < n; i++) {
        int d = find(i, i + 1);
        L[n + i] = i - d + 1, R[n + i] = i + 1 + d - 1, sum += d;
        if(L[n + i] > 1 && R[n + i] < n) {
            int k = find(L[n + i] - 2, R[n + i] + 2);
            cnt[L[n + i] - 1][s[R[n + i] + 1] - 'a'] += (k + 1);
            cnt[R[n + i] + 1][s[L[n + i] - 1] - 'a'] += (k + 1);
        }
        if(L[n + i] <= R[n + i]) tot[L[n + i]]++, tot[i + 1]--, tot[i + 1 + 1]--, tot[R[n + i] + 1 + 1]++;
    }
    ans = sum, p1 = 1, p2 = s[1] - 'a';
    for(int i = 1, pre = 0; i <= n; i++) {
        pre += tot[i], res += pre;
        for(int j = 0; j < 26; j++) {
            ll tmp = sum - res + (R[i] - L[i] + 1 + 1) / 2 + cnt[i][j];
            if(j == s[i] - 'a') tmp = sum;
            if(tmp > ans) p1 = i, p2 = j, ans = tmp;
            else if(tmp == ans && (p1 < i && p2 >= s[p1] - 'a' || p1 == i && j < p2)) p1 = i, p2 = j; 
        }
    }
    cout<<ans<<'\n';
    for(int i = 1; i <= n; i++) cout<<(p1 == i ? char(p2 + 'a') : s[i]);
    return 0;
}
```

---

## 作者：Le0Chan (赞：2)

考虑改变某一位对答案的影响。

从减少和增加两方面考虑。

先看增加，这里和其他题解类似。

对于改变每个位置后增加的回文串，先想出一个暴力一些的计算方式：枚举每一位，枚举改变成哪个字符，重新计算回文串数量，复杂度相当炸裂。发现很多位置的改变毫无意义，反而会减少原有的回文串。不如反过来从回文串的角度考虑。对于一个回文中心 $i$，最长的回文半径是 $r_i$。则在 $[i-r_i+1,i+r_i-1]$ 内改变某个位置对于当前的 $i$ 只有负贡献。发现只有在 $i-r_i$ 和 $i+r_i$ 进行改变，让两者相同，能对当前 $i$ 产生正贡献。贡献还可能不止 $1$。考虑如何计算这个贡献，进行转化后实际上是 $S_{i+r_i+1,n}$ 与 翻转的 $S_{1,i-r_i-1}$ 的最长公共前缀加一。

这个很好求。可以使用二分哈希，SA，后缀树等等。由于是 cf 题，不建议使用哈希。下面的实现给出的是后缀树。还有前面的最长回文半径，可以使用马拉车，当然上面的几个都可以求。

考虑改变每个位置后减少的回文串。

发现两个结论。

- 每个位置只要发生改变，造成的负贡献是一定的。

这个是显然的，不管改成哪个字符，都不能与原回文串的对应位置匹配上。

- 每个位置发生改变，只有经过他的回文串会减少。对于奇回文串来说，回文中心除外。

也是显然的。

考虑枚举改变的位置 $x$。

先考虑奇回文串，偶回文串类似，不再赘述。

对于一个回文中心 $i$，最长回文半径 $r_i$。

则对 $i$ 的位置先做出限制。

假设 $i>x$，则对于 $i-r_i\le x$ 的 $i$，$ans_x$ 都要减去 $x-i+r_i$。

其中 $ans_x$ 为改变 $x$ 造成的贡献。

这是一个二维偏序问题，扫描线+树状数组可以解决。具体来说维护两个树状数组，枚举到 $i$ 时，在第一棵 bit 的下标 $i-r_i$ 处加上 $1$，第二棵加上 $-i+r_i$。查询时分别求出两棵 bit 在 $x-1$ 处的前缀和。给答案先加上前者乘 $x$ 再加后者即可。

对于 $x<i$，类似可得，但需要维护后缀。

考虑构造方案。先求出最大的贡献。从前往后枚举每一位，从小到大（字典序）枚举他变成哪个字符。如果变成的字符小于原位置的字符，且造成的贡献最大，直接输出。

如果没找到小于的。就从后向前枚举每一位，从小到大枚举变成哪个字符。如果他的贡献最大，直接输出。

时间复杂度 $O(n\sum+n+n\log n)$。分别是 sam 构建后缀树，求解正贡献和二维偏序求负贡献。
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Le0{
#define LL long long
const int N=3e5+5;
int n,m,p1,p2;
int mx[N],mx2[N];
LL del[N],maxn,tot;
LL ans[N][27];
string s;
struct sam{
    int las=1,nt=1,df=0;
    int ed[N<<1],son[N<<2][27],fa[N<<2],len[N<<2],dfn[N<<2],st[N<<2][24];
    vector<int> g[N<<2];
    void build(char c,int id){
        int p=las,q=++nt;las=q;
        len[q]=len[p]+1;ed[id]=q;
        for(;p&&!son[p][c-'a'];p=fa[p]) son[p][c-'a']=q;
        if(!p) fa[q]=1;
        else{
            int x=son[p][c-'a'];
            if(len[x]==len[p]+1) fa[q]=x;
            else{
                int y=++nt;
                fa[y]=fa[x];
                fa[x]=fa[q]=y;
                memcpy(son[y],son[x],sizeof(son[x]));
                len[y]=len[p]+1;
                for(;p&&son[p][c-'a']==x;p=fa[p]) son[p][c-'a']=y;
            }
        }
    }
    void add(int x,int y){g[x].push_back(y);}
    void dfs(int x,int fa){
        st[dfn[x]=++df][0]=fa;
        for(int y:g[x]){
            if(y!=fa){
                dfs(y,x);
            }
        }
    }
    int cm(int x,int y){return dfn[x]>dfn[y]?y:x;}
    int lca(int x,int y){
        if(x==y) return x;
        x=dfn[x],y=dfn[y];
        if(x>y) swap(x,y);
        x++;
        int S=__lg(y-x+1);
        return cm(st[x][S],st[y-(1<<S)+1][S]);
    }
    int lcp(int j,int i){
        if(j>m||j<1) return 0;
        if(i>m||i<1) return 0;
        return len[lca(ed[m-j+1],ed[m-i+1])];
    }
    void work(){
        for(int i=2;i<=nt;i++) add(fa[i],i);
        dfs(1,0);
        for(int j=1;j<=20;j++)
            for(int i=1;i+(1<<j)-1<=nt;i++)
                st[i][j]=cm(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
}sm;
struct b1t{
	LL t[N];
	int lb(int x){return x&(-x);}
	void add(int x,LL k){
		x++;for(int i=x;i<=n+2;i+=lb(i)) t[i]+=k;
	}
	LL query(int x){
		x++;LL as=0;
		for(int i=x;i;i-=lb(i)) as+=t[i];
		return as;
	}
}bt,bt2;
struct b2t{
	LL t[N];
	int lb(int x){return x&(-x);}
	void add(int x,LL k){
		x++;for(int i=x;i;i-=lb(i)) t[i]+=k;
	}
	LL query(int x){
		x++;LL as=0;
		for(int i=x;i<=n+2;i+=lb(i)) as+=t[i];
		return as;
	}
}bt3,bt4;
void work(){
	for(int i=n;i>=1;i--){
		LL as=bt.query(i-1);
		LL as2=bt2.query(i-1);
		del[i]+=as*i+as2;
		bt.add(i-mx[i],-1);
		bt2.add(i-mx[i],i-mx[i]);
	}
	memset(bt.t,0,sizeof(bt.t));
	memset(bt2.t,0,sizeof(bt2.t));
	for(int i=1;i<=n;i++){
		LL as=bt3.query(i+1);
		LL as2=bt4.query(i+1);
		del[i]+=as*i+as2;
		bt3.add(i+mx[i],1);
		bt4.add(i+mx[i],-i-mx[i]);
	}
	memset(bt3.t,0,sizeof(bt3.t));
	memset(bt4.t,0,sizeof(bt4.t));
	for(int i=n-1;i>=1;i--){
		bt.add(i-mx2[i],-1);
		bt2.add(i-mx2[i],i-mx2[i]);
		LL as=bt.query(i-1);
		LL as2=bt2.query(i-1);
		del[i]+=as*i+as2;
	}
	for(int i=1;i<=n;i++){
		LL as=bt3.query(i);
		LL as2=bt4.query(i);
		del[i]+=as*i+as2-as;
		bt3.add(i+mx2[i],1);
		bt4.add(i+mx2[i],-i-mx2[i]);
	}
}
int main(){
    cin>>n>>s;m=n*2+1;
    reverse(s.begin(),s.end());
    string t=s;
    reverse(s.begin(),s.end());
    s.append("{");
    s.append(t);
    s=" "+s;
    for(int i=1;i<s.size();i++) sm.build(s[i],i);
    sm.work();
    for(int i=1;i<=n;i++){
        mx[i]=sm.lcp(2*n+2-i,i);
        if(i!=n) mx2[i]=sm.lcp(i+1,2*n+1-i+1);
    }
    for(int i=1;i<=n;i++){
        if(i+mx[i]>=n+1) continue;
        if(i-mx[i]<=0) continue;
        LL as=sm.lcp(i+mx[i]+1,m-(i-mx[i]-1)+1)+1;
        ans[i-mx[i]][s[i+mx[i]]-'a']+=as;
        ans[i+mx[i]][s[i-mx[i]]-'a']+=as;
    }
    for(int i=1;i<n;i++){
    	if(i+mx2[i]>=n) continue;
    	if(i-mx2[i]<=0) continue;
    	LL as=sm.lcp(i+mx2[i]+2,m-(i-mx2[i]-1)+1)+1;
    	ans[i-mx2[i]][s[i+mx2[i]+1]-'a']+=as;
        ans[i+mx2[i]+1][s[i-mx2[i]]-'a']+=as;
	}
    work(); 
    for(int i=1;i<=n;i++){
    	for(int j=0;j<26;j++){
    		if(j==s[i]-'a') continue;
    		maxn=max(maxn,ans[i][j]+del[i]);
		}
	}
	bool fg=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<26;j++){
			if(j<s[i]-'a'&&ans[i][j]+del[i]==maxn){
				p1=i,p2=j;
				fg=1;
				break;
			}
		}
		if(fg) break;
	}
	for(int i=1;i<=n;i++) tot+=mx[i];
	for(int i=1;i<n;i++) tot+=mx2[i];
	cout<<tot+maxn<<"\n"; 
	if(!p1){
		fg=0;
		for(int i=n;i>=1;i--){
			for(int j=0;j<26;j++){
				if(ans[i][j]+del[i]==maxn){
					p1=i,p2=j;
					fg=1;
					break;
				}
			}
			if(fg) break;
		}
	}
	for(int i=1;i<=n;i++){
		if(i==p1){
			cout<<(char)(p2+'a');
			continue;
		}
		cout<<s[i];
	}
    return 0;
}
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    return Le0::main();
}
```


---

## 作者：ax_by_c (赞：1)

个人感觉和 CF1988E 有异曲同工之妙，同样考虑快速计算修改某个位置后的变化。

预处理出以 $i$ 为中心的最长回文子串 $S_{i-len_i+1,i+len_i-1}$ 可求出原串的回文子串个数 $s$。

考虑修改 $S_i$ 为 $x$，如果 $S_i=x$，直接返回 $s$。

1. 对于所有在 $i$ 处失配的 $S_{j-len_j+1,j+len_j-1}$，将 $j$ 挂到 $i$ 处，并预处理出以 $j$ 为中心且允许一次失配的最长回文子串 $S_{j-plen_j+1,j+plen_j-1}$ ，统计时只需判断 $x$ 是否等于失配的另一个字符。

2. 对于 $i\in[j-len_j+1,j+len_j-1]$，修改后以 $j$ 为中心的最长回文子串长度可以计算得出。

使用差分优化第 2 类的计算即可。

时间复杂度为 $O(n\log n+n\lvert\sum\rvert)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,char> ND;
const ull P=1145141;
const int N=6e5+5;
int n,n_,len[N],plen[N];
char s[N];
ull pw[N],h1[N],h2[N];
vector<int>ls[N],rs[N];
ll wk[N],wb[N],ans,sum;
ND mx={-1,-1};
ull Q1(int l,int r){
	return h1[r]-h1[l-1]*pw[r-l+1];
}
ull Q2(int l,int r){
	return h2[l]-h2[r+1]*pw[r-l+1];
}
int ceildiv(int x,int y){
	return x/y+bool(x%y);
}
int cal(int p,int len){
    if(p%2==0)return ceildiv(len,2);
    return len/2;
}
ll Q(int pos,char x){
    if(x==s[pos])return sum;
    ll res=sum-(wk[pos]*(pos/2)+wb[pos]);
    for(auto i:ls[pos])if(x==s[i+len[i]])res+=cal(i,plen[i])-cal(i,len[i]);
    for(auto i:rs[pos])if(x==s[i-len[i]])res+=cal(i,plen[i])-cal(i,len[i]);
    return res;
}
ND MX(ND x,ND y){
	if(x.first==-1){
		if(s[y.first]<y.second)return x;
		return y;
	}
	if(x.first>y.first)swap(x,y);
	if(x.first==y.first){
		if(x.second<y.second)return x;
		return y;
	}
	if(s[x.first]<x.second)return y;
	if(s[x.first]>x.second)return x;
	if(s[y.first]<y.second)return x;
	return y;
}
void main(){
	scanf("%d",&n);
	s[++n_]='!';
	for(int i=1;i<=n;i++){
		scanf(" %c",&s[++n_]);
		s[++n_]='@';
	}
	s[n_]='#';
	n=n_;
	pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*P;
	for(int i=1;i<=n;i++)h1[i]=h1[i-1]*P+s[i];
	for(int i=n;i>=1;i--)h2[i]=h2[i+1]*P+s[i];
	for(int i=1;i<=n;i++){
		int l=1,r=min(i,n-i+1)-1,mid,res=0;
		while(l<=r){
			mid=l+((r-l)>>1);
			if(Q1(i-mid+1,i)==Q2(i,i+mid-1))res=mid,l=mid+1;
			else r=mid-1;
		}
		len[i]=res;
		if(len[i]<min(i,n-i+1)-1){
			l=len[i]+1,r=min(i,n-i+1)-1,res=len[i]+1;
			while(l<=r){
				mid=l+((r-l)>>1);
				if(Q1(i-mid+1,i-len[i]-1)==Q2(i+len[i]+1,i+mid-1))res=mid,l=mid+1;
				else r=mid-1;
			}
			plen[i]=res;
            ls[i-len[i]].push_back(i);
            rs[i+len[i]].push_back(i);
		}
        if(len[i]>=2){
        	wb[i-len[i]+1]+=cal(i,len[i]);
            wb[i]-=cal(i,len[i]);
            wb[i+1]+=cal(i,len[i]);
            wb[i+len[i]]-=cal(i,len[i]);
        	int mj=i-len[i]+1;
        	if(mj%2)mj++;
        	wk[mj]++;
        	wk[i]--;
        	wb[mj]-=i/2;
        	wb[i]+=i/2;
        	mj=i+len[i]-1;
        	if(mj%2)mj--;
        	wk[i+1]--;
        	wk[mj+1]++;
        	wb[i+1]+=ceildiv(i,2);
        	wb[mj+1]-=ceildiv(i,2);
        }
        sum+=cal(i,len[i]);
	}
    for(int i=1;i<=n;i++)wk[i]+=wk[i-1],wb[i]+=wb[i-1];
    for(int i=1;i<=n;i++){
        if(i%2==0){
            for(char x='a';x<='z';x++){
            	ll tmp=Q(i,x);
            	if(tmp>ans){
            		ans=tmp;
            		mx={i,x};
				}
				else if(tmp==ans)mx=MX(mx,{i,x});
            }
        }
    }
    printf("%lld\n",ans);
    if(mx.first==-1){
    	for(int i=1;i<=n;i++)if(i%2==0)putchar(s[i]);
	}
    else{
    	for(int i=1;i<=n;i++){
    		if(i%2==0){
    			if(i==mx.first)putchar(mx.second);
    			else putchar(s[i]);
			}
		}
	}
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

无脑题，构造方案比求答案麻烦/ch。

求出所有位置的回文半径，假设 $i$ 的回文半径是 $r_i$，即以 $i$ 为中心的最长回文子串为 $[i-r_i+1,i+r_i-1]$。（偶数长度的回文串与奇数长度的处理方式相似，在此不表。）

一个关键观察是，我们只会修改某个 $i$ 对应的 $i-r_i$ 或 $i+r_i$，如果修改 $i-r_i$ 必然会改成 $s_{i+r_i}$，如果修改 $i+r_i$ 必然会修改成 $s_{i-r_i}$，否则无法增加回文子串个数。枚举修改的位置，那么增加的贡献就是 $i-r_i$ 前缀翻转后和 $i+r_i$ 后缀的 LCP，可以二分 + 哈希求出。这样我们就知道了 $d_{i,j}$ 表示位置 $i$ 修改成 $j$ 的贡献。

还有一个关键观察是，修改了某个位置 $p$ 后，所有经过 $p$ 且不以 $p$ 为中心的回文串都会消失。因此我们求出回文半径之后，就能计算出经过每个位置的回文串个数了。是一个区间加一次函数的形式，维护二阶差分即可。

最后枚举所有的 $(i,j)$ 计算答案。注意到题目要求字典序最小，因此你需要分类讨论一下最优的 $(i,j)$，具体地，字典序变小的比字典序变大的优先，字典序变小的当中位置靠前的优先，字典序变大的当中位置靠后的优先。

时间复杂度 $\mathcal O(n\log n+n|\Sigma|)$。

```cpp
// Problem: F. Palindromic Problem
// Contest: Codeforces - Educational Codeforces Round 160 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1913/F
// Memory Limit: 512 MB
// Time Limit: 5000 ms

#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const ll N=3e5+9;
const ull B=137;
ll n,r1[N],r2[N],dt[N],ans,mpos,d[N][26];
ull h1[N],h2[N],pw[N];
char ch[N],bst,ch2[N];
ull H1(ll a,ll b){
	return h1[b]-h1[a+1]*pw[a-b+1];
}
ull H2(ll a,ll b){
	return h2[b]-h2[a-1]*pw[b-a+1];
}
int main(){
	n=read();
	scanf("%s",ch+1);
	rep(i,1,n)h2[i]=h2[i-1]*B+ch[i];
	per(i,n,1)h1[i]=h1[i+1]*B+ch[i];
	pw[0]=1;
	rep(i,1,n)pw[i]=pw[i-1]*B;
	rep(i,1,n){
		ll l=1,r=min(n-i+1,i);
		while(l<=r){
			ll mid=(l+r)>>1;
			if(H1(i,i-mid+1)==H2(i,i+mid-1))r1[i]=mid,l=mid+1;
			else r=mid-1;
		}
		ans+=r1[i];
		dt[i-r1[i]+1]++;
		dt[i]--;
		dt[i]-=r-1;
		dt[i+1]+=r-1;
		dt[i+1]+=r-1;
		dt[i+2]-=r-1;
		dt[i+2]--;
		dt[i+r1[i]+1]++;
	}
	rep(i,1,n-1){
		ll l=1,r=min(i,n-i);
		while(l<=r){
			ll mid=(l+r)>>1;
			if(H1(i,i-mid+1)==H2(i+1,i+mid))r2[i]=mid,l=mid+1;
			else r=mid-1;
		}
		if(!r2[i])continue;
		ans+=r2[i];
		dt[i-r2[i]+1]++;
		dt[i+1]--;
		dt[i+2]--;
		dt[i+r2[i]+2]++;
	}
	rep(i,1,n)dt[i]+=dt[i-1];
	rep(i,1,n)dt[i]+=dt[i-1];
	rep(i,1,n){
		ll pl=i-r1[i],pr=i+r1[i];
		if(pl<1||pr>n)continue;
		char tl=ch[pl],tr=ch[pr];
		ll l=r1[i]+2,r=min(n-i+1,i),op=r1[i]+1;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(H1(pl-1,i-mid+1)==H2(pr+1,i+mid-1))op=mid,l=mid+1;
			else r=mid-1;
		}
		d[pl][tr-'a']+=op-r1[i];
		l=r1[i]+2,r=min(n-i+1,i),op=r1[i]+1;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(H1(pl-1,i-mid+1)==H2(pr+1,i+mid-1))op=mid,l=mid+1;
			else r=mid-1;
		}
		d[pr][tl-'a']+=op-r1[i];
	}
	rep(i,1,n-1){
		ll pl=i-r2[i],pr=i+r2[i]+1;
		if(pl<1||pr>n)continue;
		char tl=ch[pl],tr=ch[pr];
		ll l=r2[i]+2,r=min(i,n-i),op=r2[i]+1;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(H1(pl-1,i-mid+1)==H2(pr+1,i+mid))op=mid,l=mid+1;
			else r=mid-1;
		}
		d[pl][tr-'a']+=op-r2[i];
		l=r2[i]+2,r=min(i,n-i),op=r2[i]+1;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(H1(pl-1,i-mid+1)==H2(pr+1,i+mid))op=mid,l=mid+1;
			else r=mid-1;
		}
		d[pr][tl-'a']+=op-r2[i];
	}
	ll tmp=ans;
	rep(i,1,n){
		rep(j,0,25){
			if(tmp+d[i][j]-dt[i]>ans){
				ans=tmp+d[i][j]-dt[i];
				mpos=i,bst=j+'a';
			}
			else if(tmp+d[i][j]-dt[i]==ans){
				if(i<mpos){
					if(j+'a'<ch[i])mpos=i,bst=j+'a';
					else if(j+'a'>ch[i])continue;
					else if(bst<ch[mpos])continue;
					else mpos=i,bst=j+'a';
				}
				else if(i==mpos){
					if(j+'a'<bst)bst=j+'a';
				}
				else {
					if(bst<ch[mpos])continue;
					else if(bst>ch[mpos])mpos=i,bst=j+'a';
					else if(j+'a'<ch[i])mpos=i,bst=j+'a';
					else continue;
				}
			}
		}
	}
	write(ans),putchar('\n');
	if(tmp<ans){
		ch[mpos]=bst;
		rep(i,1,n)putchar(ch[i]);
	}
	else {
		rep(i,1,n)ch2[i]=ch[i];
		ch2[mpos]=bst;
		ll fl=0;
		rep(i,1,n){
			if(ch[i]<ch2[i]){
				fl=1;
				break;
			}
			if(ch[i]>ch2[i]){
				fl=0;
				break;
			}
		}
		if(fl){
			rep(i,1,n)putchar(ch[i]);
		}
		else {
			rep(i,1,n)putchar(ch2[i]);
		}
	}
	return 0;
}

```

---

