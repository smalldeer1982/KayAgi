# [PA 2021] Zbalansowane słowa

## 题目描述

定义一个字符串 $s$ 是好的，当且仅当它包含的所有字符出现次数相同。

好的字符串例如：`mama`、`aabbcbcccbaa`。

不好的字符串例如：`ovo`。

给定一个字符串 $s$，求出 $s$ 好的**子串**数量。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq |s| \leq 3 \times 10^5$，$s$ 中只含 `a`、`b`、`c` 三个小写字母。

## 样例 #1

### 输入

```
aabbabcccba```

### 输出

```
28```

# 题解

## 作者：喵仔牛奶 (赞：10)

$\mathcal{O}(n\cdot\lvert\Sigma\rvert)$ 题解，可以加强到 $\lvert\Sigma\rvert=26$ 及以上。

# Solution

## Part I

我们观察一个子串的合法条件，记 $S$ 为子串 $[l,r]$ 中字符组成的集合，$e_i$ 为 $i$ 的出现次数，从 $S$ 中任选一个数 $x$，可以得到条件为：
$$\forall i\in S,e_i-e_x=0$$

我们记 $s_{i,j}$ 是前 $i$ 个位置中 $j$ 的出现次数，则上述条件变为：
$$\forall i\in S,s_{r,i}-s_{l-1,i}-s_{r,x}+s_{l-1,x}=0$$
$$\forall i\in S,s_{r,i}-s_{r,x}=s_{l-1,i}-s_{l-1,x}$$

也就是说，我们固定 $S,x$，记 $d_{i,j}=s_{i,j}-s_{i,x}$，子串 $[l,r]$ 的合法条件就是：
$$
\begin{cases}
\forall i\in S,d_{r,i}=d_{l-1,i},\\
\forall i\notin S,s_{r,i}=s_{l-1,i}
\end{cases}
$$

## Part II

我们要枚举的是 $S$，当然不能大力 $2^{\lvert\Sigma\rvert}$ 枚举。我们有结论：
- 固定左端点 $l$，所有右端点 $r$ 产生 $S$ 的种类只有 $\lvert\Sigma\rvert$ 种。固定右端点同理。

我们考虑向右拓展，一种字符之后被加入一次。我们记 $L_i$ 是右端点为 $i$ 向左拓展过程中所有 $S$ 的集合，$R_i$ 是左端点为 $i$ 向右拓展过程中所有 $S$ 的集合。

我们同时枚举端点与集合。枚举左端点与集合 $(l,S)$（$S\in R_l$）、右端点与集合 $(r,T)$（$T\in L_r$）。为了方便，我们将 $x$ 取集合中最小值，即 $x=\min S,x'=\min T$。将 $d,s$ 统一，记 $p_{i,j}=s_{i,j}-\begin{cases}s_{i,x}&j\in S\\0&j\notin S\end{cases}$，$q_{i,j}=s_{i,j}-\begin{cases}s_{i,x'}&j\in T\\0&j\notin T\end{cases}$。可以得出 $[l,r]$ 合法的条件是：
$$
\begin{cases}
l\leq r,\\
S=T,\\
p_{l-1}=q_r
\end{cases}
$$

大力枚举是 $\mathcal{O}(n^2\cdot\lvert\Sigma\rvert^2)$ 的，我们发现三个条件除了第一个都是相等，自然分别枚举 $(l,S),(r,T)$ 放进哈希表计数。

考虑到 $l\leq r$，我们枚举 $i=0,1,2,\cdots,n$，先统计以 $i$ 为右端点的答案，即枚举 $S\in L_i$，算出 $p$，答案加上哈希表里 $(S,p)$ 的个数；再枚举 $T\in R_{i-1}$，算出 $q$，将 $(T,q)$ 放入哈希表。

枚举的时候每次往 $S,T$ 里加入一个字符，所以 $p,q$ 与哈希值也是可以维护的。时间复杂度 $\mathcal{O}(n\cdot\lvert\Sigma\rvert)$。 

细节见代码，有注释。

# Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef unsigned long long ULL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5, B = 1e7 + 7;
	
	LL n, m, rs, a[N], ct[N][26]; string st;
	ULL pw[N]; vector<int> L[N], R[N];
	unordered_map<ULL, int> S;
	
	void ins(vector<int>& s, int x) {
		int t = -1;
		for (int i = 0; i < s.size(); i ++)
			if (s[i] == x) t = i;
		if (t != -1) s.erase(s.begin() + t);
		s.insert(s.begin(), x);
	} // s 中没有 x 则将 x 加到最前，有则将里面 x 的位置放到最前。
	
	int main() {
		cin >> st, n = st.size();
		REP(i, 1, n) {
			a[i] = st[i - 1] - 'a', m = max(m, a[i] + 1);
			REP(j, 0, 25) ct[i][j] = ct[i - 1][j] + (a[i] == j); // ct 是题解中的 s
		}
		REP(i, 1, n) L[i] = L[i - 1], ins(L[i], a[i]);
		DEP(i, n, 1) R[i] = R[i + 1], ins(R[i], a[i]);
		// 处理出 L,R
		pw[0] = 1;
		REP(i, 1, n + m) pw[i] = pw[i - 1] * B;
		
		REP(i, 0, n) {
			if (i > 0) {
				ULL v = 0, w = 0, s = 0, c = 1e9; // v 是 p 的哈希值，w 是 S 的哈希值，s 辅助求哈希值，c 是 x（最小值）
				DEP(j, m - 1, 0) v = v * B + ct[i][j];
				for (int x : L[i]) {
					if (x < c) v += s * (c < m ? ct[i][c] - ct[i][x] : 0), c = x;  // 最小值改变，要改变之前 -ct[i][c] 的部分（即 s）
					v -= ct[i][c] * pw[x], s += pw[x], w |= 1 << x; // 加入一个数
					rs += S[v + w * pw[m]]; // 统计答案
				}
			}
			ULL v = 0, w = 0, s = 0, c = 1e9;
			DEP(j, m - 1, 0) v = v * B + ct[i][j];
			for (int x : R[i + 1]) {
				if (x < c) v += s * (c < m ? ct[i][c] - ct[i][x] : 0), c = x;
				v -= ct[i][c] * pw[x], s += pw[x], w |= 1 << x; // 和前面一模一样
				S[v + w * pw[m]] ++;
			}
		}
		cout << rs << '\n';
		return 0;
	}
}
int main() {
//	freopen("c.in", "r", stdin);
//	freopen("c.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：modfish_ (赞：2)

## 思路
考虑维护三个前缀数组 $s1_i,s2_i,s3_i$，分别表示第 $1$ 个到第 $i$ 个字符中 `a`,`b`,`c` 的出现次数。特别地，$s1_0=s2_0=s3_0=0$。

注意到好的字符串的定义是**其包含的字符**出现次数均相同。于是不难想到，本题中仅存在 $7$ 种好的字符串：仅包含 `a` 的、仅包含 `b` 的、仅包含 `c` 的、仅包含 `a`,`b` 的、仅包含 `b`,`c` 的、仅包含 `a`,`c` 的和包含 `a`,`b`,`c` 的。其本质只有 $3$ 类，即包含一种的、包含两种的和包含三种的。

先考虑包含一种的。这种很好统计，原序列必定由若干 `a`,`b`,`c` 的连续段组成，对于每一段，设其长度为 $len$，则其贡献为 $\frac{len(len+1)}{2}$。

再考虑包含两种的。以包含 `a`,`b` 的为例，若存在 $i,j(i>j)$，满足 $s1_i-s1_j=s2_i-s2_j,s3_i=s3_j$，则 $[j+1,i]$ 是一个好的子串。转换一下，即要满足 $s1_i-s2_i=s1_j-s2_j,s3_i=s3_j$。所以，用 `map` 维护数对 $(s1_i-s2_i,s3_i)$，每次找前面有多少个数对和当前一样。

最后是包含三种的。和上一种同理，需要满足 $s1_i-s1_j=s2_i-s2_j=s3_i-s3_j$，整理得 $s1_i-s2_i=s1_j-s2_j,s1_i-s3_i=s1_j-s3_j$，同样维护 $(s1_i-s2_i,s1_i-s3_i)$ 即可。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 3e5 + 5;

char s[maxn];
map<pair<ll, ll>, ll> mp, mpa, mpb, mpc;

int main(){
	scanf("%s", s + 1);
	ll n = strlen(s + 1);
	mp[make_pair(0, 0)] = mpa[make_pair(0, 0)] = mpb[make_pair(0, 0)] = mpc[make_pair(0, 0)] = 1;
	ll ans = 0, sa = 0, sb = 0, sc = 0, pre = 1;
	for(ll i = 1; i <= n; i ++){
		if(i > 1 && s[i] != s[i - 1]){
			ans += (i - pre + 1) * (i - pre) / 2;
			pre = i;
		}
		if(s[i] == 'a') sa ++;
		else if(s[i] == 'b') sb ++;
		else sc ++;
		ans += mp[make_pair(sa - sb, sa - sc)] + mpa[make_pair(sb - sc, sa)] + mpb[make_pair(sa - sc, sb)] + mpc[make_pair(sa - sb, sc)];
		mp[make_pair(sa - sb, sa - sc)] ++, mpa[make_pair(sb - sc, sa)] ++, mpb[make_pair(sa - sc, sb)] ++, mpc[make_pair(sa - sb, sc)] ++;
	}
	ans += (n - pre + 2) * (n - pre + 1) / 2;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：liuyidu (赞：2)

这题挺难的，绿或者蓝吧，橙是不应该的。

首先看到本题，我们可以想到那种常见的前缀和处理，就是根据前缀和的可差分性进行处理，但是这里数据范围太大了，加上有三种字符，挺难处理的，做应该是可以做，但我不推荐。

这里我采用的是随机化的算法，目前的最优解，其实根据题目描述我们也能想到另一个对于前缀和的处理，就是将一类物品设为正值，另一类为负值（绝对值相同），那么区间和为 $0$ 就意味着这个区间内两类数字出现次数相同。

可是同样的问题来了，这里有三种字母，三个量如何处理呢？这里我就采用了随机化的算法，给前两个字母分别赋一个值，将剩下的那个字母权值设为前两个字母和的相反数。

这里细节挺多的，下面讲一些。

1. 要注意一个区间中可能只有两种甚至是一种字符，所以对每种情况需分类讨论。

1. 由于随机化的处理难免会有一些问题，所以我用了无符号整数加上 `hash` 的处理，用 `map` 也能过

1. $ans$ 记得开 `long long`。

---

