# 「KFCOI Round #1」缥缈

## 题目背景

这个世界这么大，是机缘让我们相遇，也是机缘促使我们分开。

是爱情促使我们沉沦，也是爱情让我们形同陌路。

在这一路上，为什么就刚好喜欢上你呢？

## 题目描述

你需要求出满足如下条件的长度为 $m$ 的序列 $B$ 的个数：
- $B$ 中全为正整数。
- $B$ 中不包含 $x$。
- $B$ 中元素两两不同。
- $B$ 中元素在范围 $[1,n]$ 中。
- $B$ 中任意两个元素相差不会超过 $t$。

$q$ 次询问，每次给出 $x$ 和 $t$。

由于结果可能很大，输出答案对 $10^9+7$ 取余的结果。

## 说明/提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 1（10 points）：$n \le 12$，$m\le 7$，$q\le 10$。
- Subtask 2（15 points）：$n \le 2000$，$m=2$，$q\le 2000$。
- Subtask 3（15 points）：$m=2$。
- Subtask 4（20 points）：$x\le t$。
- Subtask 5（40 points）：无特殊限制。

对于所有测试数据，$2\le n \le 2 \times 10 ^5$，$2 \le m \le n$，$1 \le x \le n$，$m - 1\le t < n$，$1 \le q \le 2\times 10^5$。


## 样例 #1

### 输入

```
6 3 3
1 3
2 3
3 5```

### 输出

```
42
30
60```

## 样例 #2

### 输入

```
10 7 5
3 9
8 6
5 7
9 6
10 7```

### 输出

```
181440
5040
15120
10080
75600```

# 题解

## 作者：Su777 (赞：6)

**【背景】**

看了眼榜，发现 D 的通过率出奇地高，于是顺手切掉了。个人认为中位绿。

**【题意】**

在 $[1,n]$ 的正整数中选择 $m$ 个，不能选择 $x$，选择的任何两个数相差不能超过 $t$，求方案数。

**【解法】**

从最后一个条件（任何两个数相差不能超过 $t$）入手，我们可以把整个问题分解：

- 在 $[1,1+t]$ 的正整数中选择 $m$ 个，不能选择 $x$。
- 在 $[2,2+t]$ 的正整数中选择 $m$ 个，不能选择 $x$。
- ……
- 在 $[n-t,n]$ 的正整数中选择 $m$ 个，不能选择 $x$。

这个最难的条件就被我们分解掉了。每个子问题很简单，如果区间包含 $x$，答案即为 $t \choose m$；如果区间不包含 $x$，答案即为 $t+1 \choose m$。组合数使用阶乘逆元计算。

注意各个子问题的答案不能简单相加。相邻的两个子问题会出现算重的情况（**注意 $t=m-1$ 时下面这些子问题的方案数均为 $0$，需要特判**），这时候我们再减去下面这些子问题的答案：

- 在 $[2,1+t]$ 的正整数中选择 $m$ 个，不能选择 $x$。
- 在 $[3,2+t]$ 的正整数中选择 $m$ 个，不能选择 $x$。
- ……
- 在 $[n-t,n-1]$ 的正整数中选择 $m$ 个，不能选择 $x$。

就可以得到最终答案，但是会 TLE。[暴力代码在这里](https://www.luogu.me/paste/kkljetqw)。考虑优化。

其实，我们不需要枚举所有的区间。只需要通过简单的推导算出这些值：

- 长度为 $t+1$ 且包含 $x$ 的区间数量，设为 $a$。
- 长度为 $t+1$ 且不包含 $x$ 的区间数量，设为 $b$。
- 长度为 $t$ 且包含 $x$ 的区间数量，设为 $c$。
- 长度为 $t$ 且不包含 $x$ 的区间数量，设为 $d$。

根据上述推理，最终答案可以表示为 $a\times {t\choose m} + b\times {t+1\choose m}-c\times{t-1\choose m}-d\times{t\choose m}$，相当于拆贡献，正确性显然。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
const ll M = 2e5 + 10;
ll fac[M], inv[M];
ll qpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1ll) res = res * a % mod;
		a = a * a % mod; b >>= 1;
	}
	return res % mod;
}
ll C(ll n, ll m) {
	return fac[n] % mod * inv[m] % mod * inv[n - m] % mod;
}

int main() {
	fac[0] = 1;
	inv[0] = 1;
	for (ll i = 1; i <= 200000; i ++) {
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = qpow(fac[i], mod - 2);
	}
    ll n, m, q;
    cin >> n >> m >> q;
    while (q--) {
        ll x, t, ans = 0;
        cin >> x >> t;
        ll all = n - t, have_x_cnt = 0;
        have_x_cnt = (min(n, x + t) - t) - (max(1ll, x - t)) + 1;
        ans += have_x_cnt % mod * C(t, m) % mod; ans %= mod;
        ans += (all - have_x_cnt) % mod * C(t + 1, m) % mod;
        ans %= mod;

        all = (n - t) - 2 + 1, have_x_cnt = 0;
        have_x_cnt = (min(n - 1, x + t - 1) - (t - 1)) - max(2ll, x - (t - 1)) + 1;
        if (t - 1 >= m) ans = (ans + mod - have_x_cnt * C(t - 1, m)) % mod;
        ans = (ans + mod) % mod;
        ans = (ans + mod - (all - have_x_cnt) * C(t, m)) % mod;
        ans = (ans + mod) % mod;
        ans = ans % mod * fac[m] % mod;
        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：Autream (赞：4)

[另解](https://www.luogu.com.cn/article/hxpxje77)。

文中使用的部分中括号是[艾佛森括号](https://baike.baidu.com/item/%E8%89%BE%E4%BD%9B%E6%A3%AE%E6%8B%AC%E5%8F%B7/22361197)。
### Subtask 1
DFS 全排列后判断合法性即可。
### Subtask 2
对于 $m=2$，考虑枚举每个 $i \in [1,n-1]$，它可以与 $[i+1,\min\{i + t, n\}]$ 当中的数字任意组合，然后再除去包含 $x$ 的情况就是答案：
$$
\sum _{i = 1 \wedge i \ne x} ^{n - 1} (\min\{t, n - i\} \times 2 - [x \in [i+1,\min\{i + t, n\}]] \times 2)
$$
### Subtask 3
考虑化简 Subtask 2 的式子。
$$
\begin{aligned}
& \sum _{i = 1 \wedge i \ne x} ^{n - 1} (\min\{t, n - i\} \times 2 - [x \in [i+1,\min\{i + t, n\}]] \times 2) \\
= & 2 \begin{pmatrix} \begin{aligned} \sum \limits _{i = 1} ^{n - 1} \min\{t, n - i\} - \sum \limits _{i = 1} ^{n - 1} [x \in [i+1,\min\{i + t, n\}]] \end{aligned} - \min\{t, n - x\} - 1 \end{pmatrix}\\
= & 2 [t \times (n - t - 1) + \sum _{i = n - t} ^{n - 1} (n - i) - (x - 1 - \max\{0, x - t - 1\})] \\
= & 2 [t \times (n - t - 1) + tn - \frac{t(2n - t - 1)}{2} - (x - 1 - \max\{0, x - t - 1\})]
\end{aligned}
$$
先用乘法分配律把 $2$ 提出来，然后将求和拆开，减去 $i = x$ 的贡献，接下来就可以探讨性质了。

$\sum \limits _{i = 1} ^{n - 1} \min\{t, n - i\}$ 本质上是所有的满足 $t < n - i$ 的 $i$ 和所有的满足 $n - i \le t$ 的 $i$ 的权值和。不等式移下项就是 $n - t$ 个 $t$ 加 $\sum \limits _{i = n - t} ^{n - 1} (n - i)$，展开得 $tn - \sum \limits _{i = n - t} ^{n - 1} i = tn - \frac{t(2n - t - 1)}{2}$。

$\sum \limits _{i = 1} ^{n - 1} [x \in [i+1,\min\{i + t, n\}]]$ 本质上是所有包含 $x$ 的区间个数，不难发现只有 $i + 1 \le x \le i + t \Rightarrow x - t \le i < x - 1$ 的 $x - 1 - \max\{0, x - t - 1\}$ 个 $i$ 对答案有贡献。
### Subtask 4 & 5
由于题目中对于 $B$ 的约束，我们可以把这道题拆分成若干个子问题来解答。

> $B$ 中的任意两个元素相差不会超过 $t$

任意两个元素相差不会超过 $t$，实际上就是序列中最大的元素和最小的元素不超过 $t$ 就行了，也就是序列的**极差**。

我们先不考虑第一个条件，假设当前所允许的最大极差为 $t$，因为序列 $B$ 中元素的唯一性，只需要枚举每一个 $i \in [1,n-t]$，在区间 $[i,i+t]$ 中任选 $m$ 个数字即可，每个区间的方案数为：
$$
\begin{pmatrix}t+1 \\ m\end{pmatrix}
$$
但是这 $n-t$ 个区间中会有 $n-t-1$ 个区间与前面的一个区间重复，如下：
$$
\underbrace{\{1,2,3,\dots,t,t+1\},\{2,3,4,\dots,t+1,t+2\},\{3,4,5,\dots,t+2,t+3\},\dots,\{n-t,n-t+1,\dots,n-1,n\}}_{n-t}
$$
不难发现，除第一个区间外，所有区间的前 $t$ 项都与该区间的前一个的后 $t$ 项相同，也就是说这一个相同的部分会被计算两次，所以我们要在除第一个区间外的区间的方案数上减去这个贡献，即：
$$
\begin{pmatrix}t+1 \\m \end{pmatrix}-\begin{pmatrix}t \\m \end{pmatrix}
$$
总方案数为：
$$
\begin{pmatrix}t+1 \\m \end{pmatrix}+(n-t-1) \left [ \begin{pmatrix}t+1 \\m \end{pmatrix}-\begin{pmatrix}t \\m \end{pmatrix} \right ] = (n-t)\begin{pmatrix}t+1 \\m \end{pmatrix}-(n-t-1)\begin{pmatrix}t \\m \end{pmatrix}
$$
方便起见，我们定义：
$$
f(len,size)=len\begin{pmatrix}size \\m \end{pmatrix}-(len-1)\begin{pmatrix}size-1 \\m \end{pmatrix}
$$

> $B$ 中**不包含** $x$

现在来考虑加上第一个条件后应该如何做。

对于第四个条件，我们已经有了一个“把 $1 \sim n$ 分成 $n-t$ 个区间分别求方案数” 的思路，现在我们加上这个性质，无疑就把在那些包含了 $x$ 的区间长度减一。

现在我们的问题转化为了求有多少个区间包含 $x$。

简单标记后如下：
$$
\overbrace{\textcolor{#0077ff}{\underbrace{\{1,2,\dots,t+1\},\dots,\{x-t-1,x-t,\dots,x-1\}}_{x-t-1}},\textcolor{#ff5577}{\underbrace{\{x-t,x-t+1,\dots,x\}\dots,\{x,x+1,\dots,t+x\}}_{t+1}},\textcolor{#55ddcc}{\underbrace{\{x+1,x+2,\dots,t+x+1\},\dots,\{n-t,n-t+1,\dots,n\}}_{n-x-t}}}^{n-t}
$$
直观地，我们的 $n-t$ 个区间被分为了 $3$ 部分：$x$ 出现之前的区间，有 $x$ 出现的区间，$x$ 出现之后的区间。

对于这三个部分，它们的**最长长度**分别为 $x-t-1$，$t+1$ 和 $n-t-x$。

证明：

因为我们枚举的区间是按字典序从小到大的顺序排列的。

我们就可以把“区间的选取” 抽象为一个大小为 $t+1$ 的滑动窗口向后滑动，窗口的末尾从 $t+1$ 开始，向后移动 $x-t$ 次第一次遇到 $x$，故“$x$ 出现之前的区间” 的最长长度为 $x-t-1$。

因为窗口长度为 $t+1$，所以总共会有 $t+1$ 个时刻 $x$ 被窗口包含，因此“有 $x$ 出现的区间” 的最长长度为 $t+1$。

显然，“$x$ 出现之后的区间” 的最长长度即为剩下的 $n-t-x$。

证毕。

从上面的推导中还可以发现一个性质：**除 $x$ 出现之后的区间外**，其他的区间总共有 $x$ 个。

显然它们的长度是会根据 $x$ 的大小而变化的，我们需要分类讨论。

#### 对于 $x\geq t+1$
此时会有“$x$ 出现之前的区间” 出现。
##### 如果 $x-t-1 \geq n-t$
此时，“$x$ 出现之前的区间” 的出现次数为 $n-t$，总答案为：
$$
m!\times f(n-t,t+1)
$$
##### 否则
此时，“$x$ 出现之前的区间” 会完整地出现，即出现次数为 $x-t-1$，对答案的贡献是：
$$
f(x-t-1,t+1)
$$
###### 如果 $x<n-t$
即 $x-t-1+t+1<n-t$。
此时，“有 $x$ 出现的区间“和”$x$ 出现之后的区间” 都会完整地出现。

“有 $x$ 出现的区间” 出现次数为 $t+1$，对答案的贡献是：
$$
f(t+1,t)-\begin{pmatrix}t \\ m\end{pmatrix}
$$
”$x$ 出现之后的区间” 出现次数为 $n-x-t$，对答案的贡献是：
$$
f(n-x-t,t+1)-\begin{pmatrix}t \\ m\end{pmatrix}
$$
这里减去的是与前一个区间重复的部分。
###### 否则
此时不会有”$x$ 出现之后的区间” 的出现。

**这样，当 $x<n-t$ 时的总方案数为：**
$$
m! \left \{ f(x-t-1,t+1) + f(\min\{t+1,n-x+1\},t) - \begin{pmatrix} t \\ m \end{pmatrix} + [x<n-t] \left [f(n-x-t,t+1)-\begin{pmatrix}t \\ m\end{pmatrix} \right] \right \}
$$
#### 对于 $x < t+1$（满足 Subtask 3 的条件）
此时不会有“$x$ 出现之前的区间” 的出现，“有 $x$ 出现的区间“会出现 $x$ 次，对答案的贡献为：
$$
f(x,t)
$$
##### 如果 $x<n-t$
此时，”$x$ 出现之后的区间” 都会完整地出现，即出现次数为 $n-x-t$，对答案的贡献为：
$$
f(n-x-t,t+1)-\begin{pmatrix}t \\ m\end{pmatrix}
$$
这里减去的是与前一个区间重复的部分。
##### 否则
此时不会有”$x$ 出现之后的区间” 出现。

**这样，当 $x\leq n-t$ 时的总方案数为：**

$$
m!\left \{ f(\min\{x,n-t\},t) + [x<n-t] \left [ f(n-x-t,t+1)-\begin{pmatrix}t \\ m\end{pmatrix} \right] \right \}
$$

## AC Code

```c++
// Problem: T551348 「KFCOI Round #1」缥缈
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T551348
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Date: 2024/12/13 21:47:44
// Author: Li_Feiy

#include <bits/stdc++.h>
#define arrout(a, n) rep(i, 1, n) printk(a[i])
#define arrin(a, n) rep(i, 1, n) a[i] = read()
#define rep(i, x, n) for(int i = x; i <= n; i++)
#define dep(i, x, n) for(int i = x; i >= n; i--)
#define erg(i, x) for(int i = head[x]; i; i = e[i].nex)
#define dbg(x) std::cout << #x << ":" << x << " "
#define mem(a, x) memset(a, x, sizeof a)
#define all(x) x.begin(), x.end()
#define arrall(a, n) a + 1, a + 1 + n
#define PII std::pair<int, int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
int read() {
	char ch = getchar();
	int r = 0, w = 1;
	while(ch < '0' || ch > '9') w = ch == '-' ? -1 : w, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return r * w;
}

void print(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}template<typename ...Args>
void print(int t, Args... args) { print(t), print(args...); }

void printl(int x) { print(x), putchar('\n'); }
template<typename ...Args>
void printl(int t, Args... args) { printl(t), printl(args...); }

void printk(int x) { print(x), putchar(' '); }
template<typename ...Args>
void printk(int t, Args ... args) { printk(t), printk(args...); }

CI N = 2e5 + 5, MOD = 1e9 + 7;
int n, m, q, ans, a[N], inv[N], fac[N];
int qpow(int a, int b) {
	int ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return ans;
}
void pre(int n) {
	fac[0] = inv[0] = 1;
	rep(i, 1, n) fac[i] = fac[i - 1] * i % MOD;
	inv[n] = qpow(fac[n], MOD - 2);
	dep(i, n - 1, 1) inv[i] = inv[i + 1] * (i + 1) % MOD;
}
int C(int m, int n) { return fac[n] * inv[m] % MOD * inv[n - m] % MOD; }
int A(int m, int n) { return fac[n] * inv[n - m] % MOD; }
int calc(int len, int size) { return (C(m, size) * len % MOD - C(m, size - 1) * (len - 1) % MOD + MOD) % MOD; }
signed main() {
	n = read(), m = read(), q = read();
	pre(n + 5);
	while(q--) {
		int x = read(), t = read(), ans;
		if(x > t + 1) {
			if(x - t - 1 >= n - t) ans = fac[m] * calc(n - t, t + 1) % MOD;
			else {
				int len = std::min(t + 1, n - x + 1);
				ans = (
					calc(x - t - 1, t + 1) + 
					calc(len, t) - C(m, t) + MOD + 
					(bool)(x < n - t) * (calc(n - t - x, t + 1) - C(m, t) + MOD
					) % MOD + MOD) % 
				MOD * fac[m] % MOD;
			}
		} else {
			int len = std::min(x, n - t);
			ans = (
				calc(len, t) +
				(bool)(x < n - t) * (calc(n - t - len, t + 1) - C(m, t) + MOD
				) % MOD + MOD) 
			% MOD * fac[m] % MOD;
		}
		std::cout << ans % MOD << "\n";
	}
	return 0;
}
```

---

## 作者：E_M_T (赞：3)

考虑先求出包含数不同的序列的个数，然后乘上 $m!$。

第四个限制为主要限制，考虑在值域上枚举两端 $l,r$ 作为最小最大值，然后计数。

确定 $l,r$ 之后，因为序列中数互不相同，所以再在 $(l,r)$ 范围内选出剩下不确定的 $m-2$ 个数即可。

* 若 $x\not \in [l,r]$，则方案数为 $\begin{pmatrix}len-2 \\m-2\end{pmatrix}$。
* 若 $x\in [l,r]$，因为 $x$ 不可选，方案数为 $\begin{pmatrix}len-3 \\m-2\end{pmatrix}$。

注意判掉两端等于 $x$ 的情况。


```cpp
F(i,1,n-m+1)//值域上枚举最小值
{
	F(j,i+m-1,i+t)//值域上枚举最大值
	{
		if(i==x||j==x) continue;
		int len=j-i+1;
		(ans+=C(len-2-(i<=x&&x<=j),m-2))%=P;
	}
}
```

把这个式子写出来，利用组合数性质 $\sum\limits_{i=0}^n \binom{i}{k}=\binom{n+1}{k+1}$ 化简。

我是先化到每次询问 $O(n)$ 再化到 $O(1)$ 的，根据贡献不同分类讨论即可。因为中间没有什么瓶颈所以过程略掉。

不依赖每次询问 $n,m$ 一样的。

```cpp
int x=read(),t=read(),ans=0,L,R;
//1.1
L=MAX(1,MAX(n-t,x+1)),R=n+m-1;
if(L<=R) (ans+=(C(n-L+1,m)-C(n-R,m)+P)%P)%=P;
//1.2
L=MAX(1,MAX(n-t,x-m+1)),R=MIN(x-1,n-m+1);
if(L<=R) (ans+=(C(n-L,m)-C(n-R-1,m)+P)%P)%=P;
//1.3
L=MAX(1,n-t),R=MIN(n-m+1,x-m);
if(L<=R) (ans+=(C(n-L,m)-C(n-R-1,m)+P)%P)%=P;
//2.1
L=MAX(1,x+1),R=MIN(n-m+1,n-t-1);
if(L<=R) (ans+=(R-L+1)*C(t,m-1)%P)%=P;
//2.2
L=MAX(1,x-m+1),R=MIN(n-m+1,MIN(n-t-1,x-1));
if(L<=R) (ans+=(R-L+1)*C(t-1,m-1)%P)%=P;
//2.3
L=MAX(1,x-t),R=MIN(n-m+1,MIN(x-m,n-t-1));
if(L<=R) (ans+=(R-L+1)*C(t-1,m-1)%P)%=P;
//2.4
L=1,R=MIN(n-m+1,MIN(n-t-1,x-t-1));
if(L<=R) (ans+=(R-L+1)*C(t,m-1)%P)%=P;
put(ans*jc[m]%P);
```

---

## 作者：Strelizia_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11767)

## P11767 「KFCOI Round #1」缥缈


真正需要考虑的只有两个条件：

**$P$：序列中不包含 $x$**。  
**$Q$：序列的极差小于等于 $t$**。

对这两个条件使用容斥原理，$P \cap Q $ 的情况数等于 $Q$ 的情况数减去 $ \neg P \cap Q$ 的情况数。

我们把给序列选数的过程看做是在数轴上固定右端点地选点。

先算 $Q$ 的情况数 $ = {t\choose m-1} \times (n-t) + \sum_{i = m-1}^{t-1} {i\choose m-1}$

解释一下：每次在数轴上选取一个右端点，我们可以在以她为右端点，长度为 $t+1$ 的线段上选数，这样就保证了极差符合要求。  
因为已经选了一个右端点，所以还能在 $t$ 个数中选 $m-1$ 个。这样完整的长度为 $t+1$ 的线段能选出 $n-t$ 段。  
然后因为左端点最多左移到 $1$，所以还有不完整的线段，右端点最多左移到 $m-1$，把这一份贡献算上，很好表示。

再算 $ \neg P \cap Q$ 的情况数：  
右端点最左移到  $l=\max(x,t+1)$，右端点最右移到 $r=\min(x+t,n)$。建议画个数轴理解一下。  
这时我们选定右端点和 $x$ 两个点。和上面同理，完整的线段贡献是 $(r-l+1)\times{t-1\choose m-2}$。  
这里注意如果 $l\le x\le r$，要在上面把一份 ${t-1\choose m-2}$ 改成 ${t\choose m-1}$，因为这时有一个右端点与 $x$ 重合，相当于只选定了一个点。  
如果 $x\ge t+1$，那么我们不用算不完整的线段的贡献。  
否则，分类讨论：  
如果 $x< m$，右端点最左移到 $m$，这时加上 $\sum_{i = m-2}^{t-2} {i\choose m-2}$ 的贡献。  
如果 $x\ge m$，右端点最左移到 $x$，这时一样有重叠，要加上 $ {x-1\choose m-1}+\sum_{i = x-1}^{t-2} {i\choose m-2} $ 的贡献。

观察上文 $\sum$ 的部分有一维是固定的，显然可以前缀和。

拜拜。

code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int mod=1e9+7;
#define int long long
long long powp[N],inv[N];
long long qpow(long long x,int y){
	long long res=1;
	while(y>0){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
long long C[N];//C(i,m-1) 
long long C2[N];//C(i,m-2) 
long long calc(int n,int m){
	return powp[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	int n,m,q;
	cin>>n>>m>>q;
	powp[0]=1;
	for(int i=1;i<=n;i++){
		powp[i]=powp[i-1]*i%mod;
	}
	inv[n]=qpow(powp[n],mod-2);
	for(int i=n-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
	C[m-2]=0;
	for(int i=m-1;i<n;i++){
		C[i]=(C[i-1]+calc(i,m-1))%mod;
	}
	C2[n+1]=0;
	for(int i=n;i>=m-2;i--){
		C2[i]=(C2[i+1]+calc(i,m-2))%mod;
	}
	for(int i=1;i<=q;i++){
		int x,t;
		cin>>x>>t;
		long long ansfirst=(C[t-1]+calc(t,m-1)*(n-t)%mod)%mod;
		int r=min(x+t,n),l=max(x,t+1);
		long long anssecond=0;
		if(x>=l && x<=r) {
			anssecond=(1ll*(r-l)*calc(t-1,m-2)%mod+calc(t,m-1)%mod)%mod;
		}else{
			anssecond=1ll*(r-l+1)*calc(t-1,m-2)%mod;
		}
		if(x<t+1){
			if(x<m){
				anssecond=(anssecond+C2[m-2]-C2[t-1]+2*mod)%mod;
			}else{
				anssecond=(anssecond+C2[x-1]+calc(x-1,m-1)-C2[t-1]+mod)%mod;
			}
		}
		long long final=(ansfirst-anssecond+mod)%mod*powp[m]%mod;
		cout<<final<<"\n";
	}
	return 0;
}
```

---

## 作者：_lmh_ (赞：1)

先考虑如下子问题：一个大小为 $n$ 的集合 $S$，求元素两两不同，且包含 $S$ 中最大值和最小值的长度为 $m$ 的序列个数，显然这个东西的答案是 $H(n,m)=\binom{n-2}{m-2}m!$。

然后考虑没有 $B$ 中不包含 $x$ 的限制的子问题，此时可以枚举极差，答案即为 $F(n,t)=\sum_{i=1}^{t}H(i+1,m)(n-i)$。

现在我们挖掉了一个数 $x$，这可以被转化为在 $1\sim n-1$ 的序列中间添加一个占位符。对于所有新序列上极差 $<t$ 的段，它在原序列上对应的极差一定 $\le t$；也就是说，我们只需要考虑新序列上极差 $=t$ 且不跨过那个占位符的序列。

答案为 $G(n,x,t)=F(n-1,t-1)+H(t,m)(\max\{0,x-k-1\}+\max\{0,n-x-k\})$，预处理 $F,H$ 可以做到单组询问 $O(1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007,MOD=1e9+7;
ll n,m,q,x,k,f[N],g[N],fac[N],ifac[N];
ll qpow(ll x,ll k){
	ll sum=1;
	while(k){
		if (k&1) (sum*=x)%=MOD;
		(x*=x)%=MOD;k>>=1;
	}
	return sum;
}
ll C(ll n,ll m){if (n<m||m<0) return 0;return fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	for (int i=fac[0]=1;i<N;++i) fac[i]=fac[i-1]*i%MOD;
	ifac[N-1]=qpow(fac[N-1],MOD-2);
	for (int i=N-1;i;--i) ifac[i-1]=ifac[i]*i%MOD;
	cin>>n>>m>>q;
	for (int i=m;i<=n;++i) f[i-1]=C(i-2,m-2)*fac[m]%MOD;
	for (int i=1;i<=n;++i) g[i]=(g[i-1]+f[i]*(n-i-1))%MOD;
	while(q--){
		cin>>x>>k;
		cout<<(g[k-1]+f[k]*(max(0ll,x-k-1)+max(0ll,n-x-k)))%MOD<<'\n';
	}
	return 0;
}
```

---

## 作者：ycy1124 (赞：1)

### 前言
因为组合技计数的细节调了一个下午，最后发现自己是个唐诗，写篇题解纪念一下。
### 思路
很显然的是我们可以枚举最大值或最小值然后求解。这篇题解采用的是枚举最小值。考虑从小到大枚举最小值，当我们枚举到最小值 $i$ 时我们最大可以取到 $i+t$，但是我们直接求 $\dbinom{t+1}{m}$ 会发现算重了，因为可能没有取 $i$，所以我们只需要强制取一个 $i$ 求 $\dbinom{t}{m-1}$ 就行了。这里是求的 $i\sim i+t$ 内全部的数都能取的方案，但是如果其中有 $x$ 不能取，那么其方案数就会变成 $\dbinom{t-1}{m-1}$。我们只需要求出所有不包含 $x$ 的与包含 $x$ 的最小值个数，然后乘上每一个的贡献那么这部分就计算完了。不包含的个数为 $\max(x-t-1,0)+\max(n-x-t,0)$，也就是将 $x$ 两边不包含他的加起来。包含的个数为 $\min(x-1,x-t)-\max(x-t,1)+1$，就是能包含 $x$ 的最大数减去最小数加一。

计算完上面的，我们其实还有一部份贡献漏掉了。因为有时候 $i+t>n$ 但是 $i\sim n$ 中还是可以取出 $m$ 个数。对于这部分的贡献，我们发现由于 $m$ 已经确定，所以在没有 $x$ 的情况下是可以直接前缀和求解的。接下来考虑包含 $x$ 的情况，首先对于那些最小值大于 $x$ 的肯定没有影响。对于其他的，其实就是将最小值等于 $x$ 的不算贡献并且将最小值小于 $x$ 的能选的数字个数全部减一。不难发现他就等于前一个前缀和。

最后我们只需要预处理一下阶乘，阶乘的逆元，前缀和即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define md 1000000007
using namespace std;
#define flush() fwrite(obuf,1,O-obuf,stdout)
#define putchar(x) ((O==obuf+(1<<21))&&(flush(),O=obuf)),*O++=x
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	register int x=0,f=1;
	register char ch=getchar();
	while(!(ch>='0'&&ch<='9'))
		ch=getchar();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch^48),ch=getchar();
	return x*f;
}
inline void write(register int x){
    (x>9)?write(x/10):void();
    putchar((x%10)^48);
}
struct Flush{
    ~Flush(){flush();}
}_;
int n,m,q,sum[200005],inv[200005],qzh[200005];
inline int power(int w){
    int qwq=md-2,base=w,Sum=1;
    while(qwq){
        (qwq&1)?Sum*=base,Sum%=md:qwq;
        qwq>>=1;
        base*=base;
        base%=md;
    }
    return Sum;
}
inline void getsum(int n){
	sum[0]=inv[0]=1;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]*i%md;
    }
}
inline void getinv(int n){
	for(int i=1;i<=n;i++){
		inv[i]=power(sum[i]);
	}
}
inline int C(int N,int M){
	if(N<M){
		return 0;
	}
	return sum[N]*inv[N-M]%md*inv[M]%md;
}
inline void getqzh(int w){
	for(int i=1;i<=w;i++){
		qzh[i]=qzh[i-1]+C(i-1,m-1);
        qzh[i]%=md;
	}
}
signed main(){
	n=read(),m=read(),q=read();
	getsum(max(n,m));
	getinv(max(n,m));
	getqzh(max(n,m));
	while(q--){
		int x,t,ans=0;
		x=read(),t=read();
		ans+=qzh[max(t-(x>n-t),0ll)];//前缀和
		ans%=md;
		ans+=(min(x-1,n-t)-max(x-t,1ll)+1)%md*C(t-1,m-1)%md;//包含了x的贡献
		ans%=md;
		ans+=(max(x-t-1,0ll)+max(n-x-t,0ll))%md*C(t,m-1)%md;//没包含x的贡献
		ans%=md;
		ans*=sum[m];
		ans%=md;
		write(ans);
        putchar('\n');
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/208784566)。

---

