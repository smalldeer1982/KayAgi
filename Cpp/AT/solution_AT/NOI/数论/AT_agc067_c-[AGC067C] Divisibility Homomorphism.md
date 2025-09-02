# [AGC067C] Divisibility Homomorphism

## 题目描述

我们称一个正整数$(a_1,a_2，…)$的无限序列为好，当且仅当它满足以下两个条件：

- 存在一个有限常数$C$，使得对于所有$1 \leq n，a_n \leq C⋅n$。
- 对于所有正整数对$(n,m)$，$a_n|a_m$当且仅当$n∣m$。这里，$x∣y$表示$x$除以$y$。

你将得到一个长度为N的正整数序列
$A=(A_1,A_2,…,A_N)$。检查是否存在一个以$(A_1,A_2,…,A_N)$开头的良好无穷序列。
你要解决$T$个样例。

## 说明/提示

- $1≤T≤5000$  
- $1≤N≤5000$  
- $1≤Ai≤10^18$

## 样例解释

对于第$1$个测试用例，$a_n=n$，这符合条件。

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
5
1 4 9 16 25
5
1 4 6 8 10
5
1 2 4 4 5
5
1 2 3 5 4```

### 输出

```
Yes
Yes
Yes
No
No```

# 题解

## 作者：Presentation_Emitter (赞：3)

以下是整理并补充证明的赛时思路，可能比官方题解麻烦。思路来自于瞪样例。部分证明可能略去了一些细节。

偏口胡。有误请指出。

引理 1：$A_i$ 两两不同。更一般地，不存在两个 $i,j$ 满足 $i<j$ 且 $A_j|A_i$。

证明：考虑反证法。若存在两个不同的 $i,j$ 使得 $A_j|A_i$（不妨令 $i<j$），那么此时 $i|j$ 不成立，或者 $A_i|A_{j+i}$ 不成立，或者 $A_j|A_{j+i}$，均与条件 2 矛盾。$\Box$

对所有 $A_i$ 质因数分解。记 $v_m(x)$（$m \ge 2$）为最大的满足 $m^k|x$ 的非负整数 $k$。考虑一个质数 $p$ 以及两个不同的 $i,j$ 满足 $v_p(j)=1+v_p(i)$。推广引理 1 的证明，可以得到必定存在一个质数 $p'$ 满足 $v_{p'}(A_j)>v_{p'}(A_i)$。

引理 2：对于任意质数 $p$，其唯一占用一个 $p'$。形式化地，定义 $S_p$ 为通过下面方式构造出的集合：

- 对于两个不同的 $i,j$ 满足所有质数中恰好只有 $p$ 满足 $v_{p}(j)>v_{p}(i)$，若对于某个质数 $p'$ 有 $v_{p'}(a_j)>v_{p'}(a_i)$，则将 $p'$ 加入 $S_p$；

则对于一个质数 $p$，对于上述定义中满足上述条件的 $i,j$（除了有限数量的特例），存在一个 $p' \not\in \bigcup\limits_{q \neq p,\ q \in \text{prime}}S_q$ 满足 $v_{p'}(a_j)>v_{p'}(a_i)$。

口胡：考虑反证法。假设上述命题不成立，记 $P=\prod\limits_{q\neq p,\ q \in \text{prime} \atop q \le n}q$，那么存在一个正整数 $k$ 使得 $a_j|a_{(1+kp)Pi}$，与条件 2 矛盾，除非某个质数 $q$ 仅在 $j'|j$ 时才存在一个 $i' \neq i$ 使得 $v_q(j')>v_q(i')$ 且有一个 $q' \in S_p \cap S_q$，而这样的二元组 $(i',j')$ 数量是有限的。

发现还没用上条件 1，于是尝试使用。得到了：

引理 3：$p$ 仅唯一占用 $p$。

口胡：考虑反证法。假设存在一个质数唯一占用一个不同的质数，那么不难证明存在一个质数 $p$ 使得其唯一占用的质数均 $>p$。记这些质数中最小的为 $p'$，则有 $\forall k \in \mathbb{N}^{*},a_{p^k} \ge \epsilon a'^k$（其中 $\epsilon$ 为某个常数），与条件 1 矛盾。

由引理 3 进一步可以得到引理 2 中提到的“有限多个特例”数量为 $0$。

由引理 1 的推广和引理 3 可以得到，$\forall p \in \text{prime}, v_p(i)<v_p(j) \Rightarrow v_p(a_i)<v_p(a_j)$。于是我们得到了一个必要条件。

下面说明充分性：

构造 $\{a_n\}$ 使得对所有质数 $p$ 均有 $v_p(a_i)=\max\limits_{j<i,\ v_p(j)<v_p(i)}\{v_p(a_j)\}+1$，于是 $v_p(a_i) \le \max\limits_{j \le n}\{v_p(A_j)\}+v_p(i)$，满足条件 1。对于两个不同的 $i,j$，令 $i<j$，则 $i|j$ 成立，或者存在一个质数 $p$ 满足 $v_p(a_i) > v_p(a_{\gcd(i,j)})=v_p(a_j)$。于是条件 2 也满足了。

最后我们得到了这个题的做法：检验 $\forall p \in \text{prime}, v_p(i)<v_p(j) \Rightarrow v_p(A_i)<v_p(A_j)$ 是否对所有 $1 \le i,j \le N$ 成立即可。$\Box$

时间复杂度：存在 $\Theta(N^2)$ 做法。

[Code](https://atcoder.jp/contests/agc067/submissions/56975252)。

---

## 作者：251Sec (赞：2)

约定 $p_k$ 代表第 $k$ 小的质数。$v_P(x)$ 代表 $x$ 的唯一分解里包含质数 $P$ 的数量，$f(n)$ 代表 $a_n$。

给出如下结论：对于合法的 $a$ 序列，有 $\frac{f(p_ku)}{f(u)}$ 包含至少一个 $\ge p_k$ 的质因子，且 $f(p_k^n)$ 在 $n$ 足够大时等于 $C_kp_k^n$，其中 $C_k$ 为一关于 $k$ 的常数。

考虑归纳证明，对于 $k=0$ 显然。然后对于 $k>0$，考虑令 $x$ 为 $\prod\limits_{i < k}p_i^L$ 其中 $L$ 足够大，则必须有 $f(p_ku) \nmid f(xu)$，即 $\frac{f(p_ku)}{f(u)} \nmid \frac{f(xu)}{f(u)}$。对于右侧，我们发现对于 $t < k$ 有 $f(p_t^L) \mid f(xu)$，$p_t^L \mid f(p_t^L)$，即右侧包含足够多的 $<p_k$ 的质因子，所以左侧一定包含 $\ge p_k$ 的因子。于是我们证明了结论的前半部分。接下来，有 $f(p_ku) \ge p_kf(u)$，且对于确定的常数 $C$，不取等的次数只有常数次，所以后半部分也得证。

有了这个结论，我们可以得到：$v_P(x)>v_P(y) \Rightarrow v_P(f(x))>v_P(f(y))$。反证，假设 $v_P(f(x)) \le v_P(f(y))$，令 $z=\prod\limits_{i \le K \land p_i \ne P}p_i^L$ 其中 $L,K$ 足够大。则 显然 $x \nmid yz$。且 $f(yz)$ 中，对于 $t \le K \land p_t \ne P$ 都包含足够多个该质因子。而 $f(y) \mid f(yz)$，则 $v_P(f(x)) \le v_P(f(y)) \le v_P(f(yz))$，因此我们得到 $f(x) \mid f(yz)$，与 $x \nmid yz$ 矛盾。

实际上，我们可以知道，对于原序列满足 $f(n) \mid f(m) \Leftrightarrow n \mid m$，且 $v_P(x)>v_P(y) \Rightarrow v_P(f(x))>v_P(f(y))$，是存在合法解的充分条件。我们直接对于 $i>n$ 和每个质数 $p$ 构造 $v_p(f(i))= 1+\max\limits_{j<i \land v_p(j)<v_p(i)} v_p(f(j))$。不难验证它的合法性。

上述内容不难在 $O(n^2)$ 复杂度内检查。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5000;
int T, n;
ll a[5005], pri[5005], cnt;
ll x[5005], y[5005];
bool chk[5005];
ll V(ll x, ll y) {
	int res = 0;
	while (x % y == 0) x /= y, res++;
	return res;
}
vector<ll> p[80];
int main() {
	scanf("%d", &T);
	for (int i = 2; i <= N; i++) {
		if (!chk[i]) pri[++cnt] = i;
		for (int j = 1; j <= cnt && 1ll * i * pri[j] <= N; j++) {
			chk[i * pri[j]] = true;
			if (i % pri[j] == 0) break;
		}
	}
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%lld", a + i);
		bool flg = true;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				flg &= (a[i] % a[j] == 0) == (i % j == 0);
			}
		}
		for (int i = 1; i <= cnt && pri[i] <= n; i++) {
			ll l = 0;
			for (int j = 1; j <= n; j++) {
				x[j] = V(j, pri[i]), y[j] = V(a[j], pri[i]);
				l = max(l, x[j]), p[x[j]].push_back(y[j]);
			}
			ll maxV = -1e18;
			for (int j = 0; j <= l; j++) {
				ll minV = 1e18;
				for (ll x : p[j]) minV = min(minV, x);
				flg &= (maxV < minV);
				for (ll x : p[j]) maxV = max(maxV, x);
			}
			for (int j = 0; j <= l; j++) p[j].clear();
		}
		puts(flg ? "Yes" : "No");
	}
	return 0;
}
```

---

