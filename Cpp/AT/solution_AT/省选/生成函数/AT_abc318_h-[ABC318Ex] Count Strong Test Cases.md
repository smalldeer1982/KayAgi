# [ABC318Ex] Count Strong Test Cases

## 题目描述

すぬけ君想出了如下的问题。

> 给定 $ (1,2,\ldots,N) $ 的排列 $ P=(P_1,P_2,\ldots,P_N), Q=(Q_1,Q_2,\ldots,Q_N) $。按照以下方法构建一个有 $ N $ 个顶点和 $ N $ 条边的图。
>
> - 对于 $ i=1,2,\ldots,N $，依次将顶点 $ i $ 与顶点 $ P_i $ 之间连接一条权值为 $ Q_i $ 的无向边。
>
> 当你删除若干条边使得图中不包含环时，请求出被删除的边的权值之和的最小值。

Alice 和 Bob 分别想出了如下的解法。

Alice：将答案初始化为 $ 0 $。对于 $ i=1,2,\ldots,N $，如果顶点 $ i $ 与顶点 $ P_i $ 之间的边在环中，则删除这条边，并将其权值加到答案中。

Bob：将答案初始化为 $ 0 $。对于 $ i=N,N-1,\ldots,1 $，如果顶点 $ i $ 与顶点 $ P_i $ 之间的边在环中，则删除这条边，并将其权值加到答案中。

すぬけ君发现 Alice 和 Bob 的解法都是错误的，所以他想知道，有多少组输入使得 Alice 和 Bob 的解法的答案都与正确答案不同。

输入共有 $ (N!)^2 $ 种可能，请你输出其中 Alice 和 Bob 的解法的答案都与正确答案不同的输入的个数，模 $ 998244353 $。

## 说明/提示

### 限制条件

- $ 1\leq N\leq 2\times 10^5 $
- 输入的所有数均为整数

### 样例解释 1

满足条件的输入共有以下 $ 4 $ 种：
- $ P=(2,3,1), Q=(2,1,3) $
- $ P=(2,3,1), Q=(3,1,2) $
- $ P=(3,1,2), Q=(2,1,3) $
- $ P=(3,1,2), Q=(3,1,2) $

例如，对于 $ P=(2,3,1), Q=(2,1,3) $，正确答案是 $ 1 $，但 Alice 的解法输出 $ 2 $，Bob 的解法输出 $ 3 $。

### 样例解释 2

也有可能不存在满足条件的输入。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3```

### 输出

```
4```

## 样例 #2

### 输入

```
2```

### 输出

```
0```

## 样例 #3

### 输入

```
6```

### 输出

```
314708```

## 样例 #4

### 输入

```
318```

### 输出

```
321484323```

# 题解

## 作者：_YangZJ_ (赞：8)

提供一个不需要 $\text{exp}$ 的做法。

正难则反，考虑用总方案数 $(n!)^2$ 减去所有 $\text{Alice}$ 求出的是正解的方案数，也就是排列构成的所有置换环中的最小点权都在环编号最小的点的方案数。对称一下就是 $\text{Bob}$ 的方案数。最后加上两者都求出正解的方案数：只有一种情况就是每个置换环大小为 $1$，方案数就是分配权值的方案数：$n!$。

考虑 $\text{dp}$，设 $f_i$ 表示长度为 $i$ 的时候，$\text{Alice}$ 求出的是正解的方案数。转移考虑钦定 $1$ 所在的置换环：
$$
f_i=\sum_{j=0}^{i-1}f_jg_{i,i-j}
$$
其中 $g_{i,j}$ 表示从 $i$ 个点中选出 $j$ 个点（包含 $1$）构成置换环，并且该置换环满足最小权值在编号最小的点上的方案数。首先要选出另外 $j-1$ 个点：${i-1\choose j-1}$，然后选出 $j$ 个权值：${i \choose j}$，构成置换环：$(j-1)!$，钦定最小的权值在 $1$ 处，剩余权值随意：$(j-1)!$。因此：
$$
g_{i,j}={i-1 \choose j-1}{i \choose j}(j-1)!(j-1)!
$$
代入 $f$ 的转移方程并化简：
$$
f_i=(i-1)!i!\sum_{j=0}^{i-1}\frac{1}{(j!)^2}f_j\cdot \frac{1}{i-j}
$$
设 $dp_i = f_i\cdot \frac{1}{(i!)^2}$，转移：
$$
f_i=(i-1)!i!\sum_{j=0}^{i-1}dp_j\cdot \frac{1}{i-j}
$$
用分治 $\text{NTT}$ 优化即可。复杂度 $O(n\log^2n)$。

最后的答案即为：$(n!)^2-2f_n+n!$。

code：

```cpp
int n, f[N], dp[N], G[N];

inline void solve(int l,int r) {
	if(l==r) {
		if(l) f[l] = 1ll*fc[l-1]*fc[l]%P*f[l]%P;
		return dp[l] = 1ll*f[l]*ifc[l]%P*ifc[l]%P, void();
	}
	int mid = l+r>>1;
	solve(l,mid); 
	poly F(mid-l+1), G(r-l+1);
	for(int i=l;i<=mid;i++) F[i-l] = dp[i];
	for(int i=0;i<=r-l;i++) G[i] = iv[i];
	auto res = F*G;
	for(int i=mid+1;i<=r;i++) inc(f[i],res[i-l]);
	solve(mid+1,r);
}

signed main() {
	n = read(); fc[0] = ifc[0] = iv[0] = 1;
	for(int i=1;i<=n;i++) fc[i] = 1ll*i*fc[i-1]%P, ifc[i] = inv(fc[i]), iv[i] = inv(i);
	f[0] = 1;
	solve(0,n);
	int sub = pls(2ll*f[n]%P,P-fc[n]);
	int ans = pls(1ll*fc[n]*fc[n]%P,P-sub);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Register_int (赞：3)

[Over all](/blog/const1e7/abc318-solution)

先来一个小容斥，分别考虑 A 可能 WA 且 B AC、A AC 且 B 可能 WA、A AC 且 B AC 的情况。均 AC 只有可能为每个点都有环，而剩下两种情况是对称的，只要求出一种即可。

考虑长度为 $i$ 的环有 $a_i$ 个，那么每个环内钦定最大值保证 A 能够 AC，得到答案为：

$$\dfrac1{(\sum a_i)!}\left(n!\prod^n_{i=1}\dfrac1{i!^{a_i}}\right)\left(\prod^n_{i=1}(i-1)!^{a_i}\right)\left(n!\prod^n_{i=1}\dfrac1{i^{a_i}}\right)$$

稍稍化简得到：

$$n!^2\dfrac1{(\sum a_i)!}\left(\prod^n_{i=1}\dfrac1{i^{2a_i}}\right)$$

设 $F(x)=\sum_{i=1}\frac1{i^2}x^i$，则该式为 $n!^2[x^n]\exp F(x)$，答案为：

$$n!^2+n!-2\times n!^2[x^n]\exp F(x)$$

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define _POW_OPTIMIZE_FOR_K

namespace polynomial {
	// by register_int.
}

using namespace polynomial;

const int MAXN = 2e5 + 10;

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

int n; ll ans;

int main() {
	scanf("%d", &n), init(n); poly<ll> f(n + 1);
	for (int i = 1; i <= n; i++) f[i] = inv((ll)i * i % mod); f = exp(f);
	printf("%lld", (fac[n] * fac[n] % mod * (1 - 2 * f[n] % mod + mod) % mod + fac[n]) % mod);
}
```

---

## 作者：EuphoricStar (赞：1)

首先做一些初步的观察：A 和 B 的解法是对称的，所以 A 对的方案数等于 B 对的方案数。同时若 A 和 B 同时对则每个置换环环长为 $1$，方案数为 $n!$。

所以，若设 A 对的方案数为 $x$，那么答案为 $n!^2 - (x - n!) - (x - n!) - n! = n!^2 + n! - x$。所以转化为算 $x$。

A 对当且仅当每个置换环的最大边刚好是编号最小的点的出边。设确定 $p_i$ 后环长分别为 $l_1, l_2, \ldots, l_m$，那么安排边权的方案数为 $n! \prod\limits_{i = 1}^m \frac{1}{l_i}$，其中 $n!$ 可以放到最后乘。

那么设环的 EGF 为 $\hat F(x)$，有：

$$\hat F(x) = \sum\limits_{i \ge 0} \frac{(i - 1)!}{i \times i!} = \sum\limits_{i \ge 0} \frac{1}{i^2}$$

其中 $(i - 1)!$ 为长度为 $i$ 的圆排列方案数。

设答案的 EGF 为 $\hat G(x)$，有标号的组合对象拼接，可得：

$$\hat G(x) = \sum\limits_{i \ge 0} \frac{\hat F(x)^i}{i!} = \exp(\hat F(x))$$

那么 $x = n!^2 [x^n] \hat F(x)$。

时间复杂度 $O(n \log n)$。

[code](https://atcoder.jp/contests/abc318/submissions/53284144)

---

## 作者：hyman00 (赞：1)

容易想到容斥，共 $(n!)^2$ 个方案，两个人都对显然是 $P=[1,2,\dots,n]$ 且 $Q$ 任意的，共 $n!$ 个方案。

显然两人是对称的，设第一个人对的有 $k$ 个方案，则：
$$
ans=(n!)^2-2k+n!
$$
下面计算 $k$：
$$
k=\sum_{a_1+\dots+a_m=n}\frac{\binom{n}{a_1,\dots,a_m}^2\times(\prod(a_i-1)!)^2}{\prod c_i!}=\sum_{a_1+\dots+a_m=n}\frac{(n!)^2}{(\prod a_i^2)(\prod c_i!)}=\sum(n!)^2\times \prod_{i=1}^{n}\frac{1}{i^{2c_i}\times c_i!}
$$
第一步是暴力枚举 $P$ 生成的环长分别是 $a_1,\dots,a_m$，且令 $c_i$ 表示 $i$ 在 $a$ 中出现次数，然后组合数表示把 $1\dots n$ 分成这么多部分的方案数，两个 $(a_i-1)!$ 表示 $P$ 中求原排列以及 $Q$ 中钦定最小的放第一个剩下随便放，分母是 $a$ 中重复的要去重。

第二步是拆开组合数并和阶乘约掉一些。

第三步是改变求和方式，从每个数考虑，$i$ 出现 $c_i$ 次给答案的贡献。

于是考虑类似划分数的生成函数：

$$
k=(n!)^2\sum_{c}\prod_{i=1}^{n}\frac{1}{c_i!\times(i^2)^{c_i}}=(n!)^2[x^n]\prod_{i=1}^{n}\sum_{j=1}^{\inf}\frac{x^{ij}}{j!(i^2)^j}=(n!)^2[x^n]\prod_{i=1}^{n}\sum_{j=1}^{\inf}\frac{(\frac{x^i}{i^2})^{j}}{j!}=(n!)^2[x^n]\prod_{i=1}^{n}\exp(\frac{x^i}{i^2})=(n!)^2[x^n]\exp(\sum_{i=1}^{n}\frac{1}{i^2}x^i)
$$

先写成求和形式。

第二步把求和化为幂级数乘积。

发现分母出现阶乘，分子可以写成指数，想到用 $\exp$ 做，最后化简。

照着式子算即可。

---

## 作者：SoyTony (赞：1)

考虑容斥，总方案数是 $(n!)^2$，Alice 和 Bob 都正确当且仅当是恒等置换，即 $n!$ 种 $Q$ 赋值的方案。

现在只需要计算 Alice 正确的方案数，不难发现 Bob 正确的方案数和 Alice 相同，每个方案只需要把边权顺序完全调换即可。


不妨设构成 $k$ 个置换环，其中升序排序后环长为 $l_i$，对于每个 $l$ 序列求解之后求和就是答案。

为置换环分配编号的方案是：

$$\dbinom{n}{l_1,l_2,\cdots,l_k}\dfrac{1}{k!}\prod_{i=1}^{k} (l_i-1)!$$

这部分就是多重集排列数，除去环标号的方案，再乘上圆排列。

分配 $Q$ 的方案数是：

$$n!\prod_{i=1}^{k} \dfrac{1}{l_i}$$

容易发现每个环边权最小值和编号最小值对应的概率是环长的倒数。

上下两个式子乘起来整理，得到：

$$(n!)^2 \dfrac{1}{k!}\prod_{i=1}^{k} \dfrac{1}{l_i^2}$$

设 $F(x)=\sum_{i\ge 1} \frac{1}{i^2}x^i$，结果就是 $(n!)^2 [x^n]\exp(F(x))$。

最终答案是 $(n!)^2-2(n!)^2[x^n]\exp(F(x))+n!$。

---

