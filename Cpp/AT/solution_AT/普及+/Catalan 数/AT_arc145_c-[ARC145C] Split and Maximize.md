# [ARC145C] Split and Maximize

## 题目描述

对于 $ (1,2,\ldots,2N) $ 的一个排列 $ P=(P_1,P_2,\ldots,P_{2N}) $，定义其得分如下：

> 将 $ P $ 按顺序分成两个长度为 $ N $ 的（不一定连续的）子序列 $ A=(A_1,A_2,\ldots,A_N),\ B=(B_1,B_2,\ldots,B_N) $。对于所有可能的分割，取 $ \displaystyle\sum_{i=1}^{N}A_i B_i $ 的最大值作为该排列的得分。

对于所有 $ (1,2,\ldots,2N) $ 的排列，计算它们的得分，并记这些得分中的最大值为 $ M $。请你求出得分等于 $ M $ 的排列个数，并对 $ 998244353 $ 取模后输出。

## 说明/提示

## 限制

- $ 1\leq N\leq 2\times 10^5 $
- 输入均为整数

## 样例解释 1

在所有可能的 $ 24 $ 个排列中，最大得分 $ M $ 为 $ 14 $。得分为 $ 14 $ 的排列有 $ 16 $ 个。例如，排列 $ (1,2,3,4) $ 可以分割为 $ A=(1,3),\ B=(2,4) $，此时 $ \sum_{i=1}^{N}A_i B_i=14 $。

## 样例解释 2

请输出对 $ 998244353 $ 取模的答案。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2```

### 输出

```
16```

## 样例 #2

### 输入

```
10000```

### 输出

```
391163238```

# 题解

## 作者：liangbowen (赞：7)

[problem](https://www.luogu.com.cn/problem/AT_arc145_c) & [blog](https://www.cnblogs.com/liangbowen/p/17640112.html)。

小清新结论题。

---

~~提供一个不需要脑子就可以 AC 的方法：看样例解释，猜到一定是 $(1,2)(3,4)$ 这样子，于是暴力，把前几项输进 OEIS 里，做完了。~~

显然取 $\forall |A_i-B_i|=1$ 最优。

> 证明：对于 $x-3,x-2,x-1,x$，配对：
> $(x-3,x-2)(x-1,x)$ 的贡献为 $(x-3)(x-2)+(x-1)x=2x^2-6x+6$。
> $(x-3,x)(x-2,x-1)$ 的贡献为 $(x-3)x+(x-2)(x-1)=2x^2-6x+2$。
> 显然前者更优，同理容易归纳证明。

简单计数。

+ 交换 $(A_i,B_i)$ 与 $(A_j,B_j)$ 仍然最优，方案数 $n!$。
+ 交换 $A_i$ 与 $B_i$ 仍然最优，方案数 $2^n$。
+ 去掉上述情况后考虑的是 $\forall (A_i,B_i)=(2k-1,2k)$ 的问题。
+ 不妨设同一对中，先出现的为 $\alpha$，后出现的为 $\beta$，则这个序列合法，当且仅当任意时刻，$\alpha$ 的数量 $\ge \beta$ 的数量。
+ 此即卡特兰数 $\dfrac1{n+1}\cdot\begin{pmatrix}2n\\n\end{pmatrix}$。总答案即这些东西相乘。

[code](https://atcoder.jp/contests/arc145/submissions/44676392)，时间复杂度 $O(n)$。

---

## 作者：taojinchen (赞：3)

# 思路
在题目的要求中，对于当前排列对应的子序列中的元素 $\sum\limits_{i=1}^{n}A_iB_i$ 最大，就统计进入总方案数。

其中，我们知道在 $x_1 < x_2 < x_3 < \cdots  < x_m$ 并且 $y_1 < y_2 < y_3 < \cdots  < y_m$ 时，$\sum\limits_{i=1}^{m}x_iy_i$ 最大。其中 $x,y$ 为任意满足条件的两个长度为 $m$ 的数列。所以让 $\sum\limits_{i=1}^{n}A_iB_i$ 最大，只需要让越大的 $A_i$ 对应的 $B_i$ 越大即可。

我们仔细观察 $\sum\limits_{i=1}^{n}A_iB_i$ 这个式子，就可以发现以下结论。
- 根据加法交换律，如果 $A_i$ 和 $A_j$ 互换，并且 $B_i$ 和 $B_j$ 互换，结果不会发生改变。对于这 $n$ 个 $A_i \cdot B_i$，一共有 $n!$ 种不同的排列顺序。
- 根据乘法交换律，如果 $A_i$ 和 $B_i$ 互换，结果依然不会发生改变。对于这 $n$ 对 $A_i $ 和 $ B_i$，一共有 $2^n$ 种不同的排列方式。

所以总方案数等于 $2^n \cdot n! \cdot cnt$，其中 $cnt$ 表示的是 $A$ 中元素顺序确定且 $A_i$ 和 $B_i$ 不能互换两个子序列的数量。也就相当于 $A_1 < A_2 < A_3 < \cdots < A_n$ 且 $B_1 < B_2 < B_3 < \cdots < B_n$ 又 $ \forall A_i < B_i$ 的数列个数。这非常像一个[有趣的数列](https://www.luogu.com.cn/problem/P3200)。自然地，$cnt$ 就是卡特兰数。


# 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll kM = 1e6 + 5, mod = 998244353;
ll q, n, m, k, f[kM], i;
ll qpow(ll a, ll b){//快速幂
  ll ret = 1;
  while(b){
    if(b & 1) ret *= a, ret %= mod;
    a *= a, a %= mod;
    b >>= 1;
  }
  return ret;
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  m = 2 * n;
  f[0] = 1;
  for(i = 1; i <= m; i++){//求阶乘
    f[i] = f[i - 1] * i;
    f[i] %= mod;
  }
  ll t = qpow((f[n] * f[n]) % mod, mod - 2);//求逆元
  ll tt = qpow((f[n + 1] * f[n - 1]) % mod, mod - 2);
  ll ctl = ((f[m] * (t - tt)) % mod + mod) % mod;//卡特兰数
  cout << ((ctl * qpow(2, n)) % mod * f[n]) % mod;//最终结果
  return 0;
}
```

---

## 作者：hhhqx (赞：2)

这篇题解都是感性理解，没有证明。

蒟蒻第一次写卡特兰数的题解，如果有问题希望能被指正！
## 题意
对于一个 $1$ 到 $2n$ 的排列 $P$，定义 $f(P)$ 表示：把 $P$ 分为两个长 $n$ 的子序列 $A,B$ 中 $\sum\limits_{i=1}^{n}{A_iB_i}$ 最大值。

设所有排列中 $f(P)$ 的最大值为 $M$。

问有多少个排列 $P$ 满足 $f(P) = M$。

## 做法
下面可能会用到“题意”中的变量，所以可以先看看“题意”部分。

容易理解最优一定是所有 $1 \le i \le n$ 都有 $|A_i-B_i|=1$（所以 $M = \sum\limits_{i=1}^{n}{(2i-1)(2i)}$，但是这个不重要）。

也就容易理解：对于一个 $P$，$\sum\limits_{i=1}^{n}{A_iB_i}$ 最大的划分方案，是唯一的。

所以考虑统计总共多少种划分方案的 $\sum\limits_{i=1}^{n}{A_iB_i}$ 等于 $M$（**注意**如果两个划分满足 $A=A,B=B$，但是所属排列 $P$ 不同，那这两种划分方案视作不同）。

对于一种划分方案，设二元组序列 $C = (A_1,B_1),\cdots (A_i,B_i),(A_n,B_n)$。对于两种划分方案，如果 $C$ 初始不相同，但排序后相同，那这两种划分方案可以一个对应到一个上。

可以先有系数 $2^n \times n!$，那接下来只用统计多少个 $P$ 满足划分方案是 $A_i=2i-1,B_i=2i$，并且 $A_i$ 在 $P$ 中位置在 $B_i$ 在 $P$ 中位置的前面：

- 由于 $A_i$ 在 $P$ 中位置在 $B_i$ 在 $P$ 中位置的前面。
- 可以看作两个序列 $1,3,\cdots,2i-1,\cdots ,2n-1$ 和 $2,4,\cdots,2i\cdots ,2n$，每次从两个队头中取出一个加在 $P$ 的末尾，然后要求第一个序列中取的数量大于等于第二个序列中取出的数量。
- 拿到二维平面图上，很显然是卡特兰数。

所以答案是 $2^n \times n! \times Catalan(n)$。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const LL mod = 998244353;
const int MAXN= 4e5 + 3;

LL qpow(LL A, LL B){
	LL ret = 1;
	while(B > 0){
		if(B & 1) ret = ret * A % mod;
		A = A * A % mod, B >>= 1;
	}
	return ret;
}

LL fac[MAXN], ifac[MAXN];
int n, m;

LL C(int A, int B){ return fac[B] * ifac[A] % mod * ifac[B - A] % mod; }
LL Catalan(int A){ return (C(A, A + A) - C(A - 1, A + A) + mod) % mod; }

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	fac[0] = ifac[0] = 1;
	for(int i = 1; i <= 4e5; i++) fac[i] = fac[i - 1] * i % mod, ifac[i] = qpow(fac[i], mod - 2);
	cin >> n;
	cout << qpow(2, n) * fac[n] % mod * Catalan(n) % mod;
	return 0;
}
```

---

## 作者：liyixin0514 (赞：2)

# [Split and Maximize](https://www.luogu.com.cn/problem/AT_arc145_c)

根据常识可知，肯定是 $\sum_{i=1}^n 2i(2i-1)$ 最大，通俗来讲就是相邻两个数相乘是最优的。

要达到这个得分，我们应该将 $2i$ 和 $2i-1$ 一个分给 $A$，一个分给 $B$，并且要保证先后顺序一样，保证 $2i$ 可以与 $2i-1$ 配对。

把 $2i$ 看作 ```(```，把 $2i-1$ 看作 ```)```，答案一定是一个合法的括号序列。

长度为 $2n$ 的合法括号序列个数可以用卡特兰数解决，等于 $\dbinom{2n}{n}-\dbinom{2n}{n-1}=\dfrac{(2n)!}{n!\times n!}-\dfrac{(2n)!}{(n+1)!\times (n-1)!}=\dfrac{(n+1)(2n)!}{n!\times (n+1)!}-\dfrac{n(2n)!}{(n+1)!\times n!}=\dfrac{(2n)!}{(n+1)!\times n!}$。

对于一个合法的括号序列，由于 ```(``` 两两意义不同，答案需乘上 $n!$ 表示 ```(``` 的排列数，一旦 ```(``` 的顺序确定了，```)``` 的顺序也唯一了，因此不需要讨论 ```)``` 的排列数。因为 $2i$ 和 $2i-1$ 的位置可以调换，所以答案应该再乘上 $2^n$。

最终答案是 $\dfrac{(2n)!}{(n+1)!\times n!}\times n!\times 2^n$。

时间复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
using namespace std;
typedef long long ll;
const int N=2e5+3,mod=998244353;
int n;
ll jc(ll a){
	ll s=1;
	for(int i=1;i<=a;i++){
		s=s*i%mod;
	}
	return s;
}
ll ksm(ll a,ll b){
	ll s=1;
	while(b){
		if(b&1) s=s*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return s;
}
int main(){
	sf("%d",&n);
	pf("%lld\n",jc(2*n)*ksm(jc(n)*jc(n+1)%mod,mod-2)%mod*jc(n)%mod*ksm(2,n)%mod);
}
```

---

## 作者：xukehg (赞：2)

隔壁 liangbowen 大佬的题解整体上有一些难以理解（可能是我太菜了），本篇题解更倾向与方便像我一样菜的人理解题解。

设 $n$ 个数分别为 $x, x - 1 \dots 1$，考虑一个组的贡献为 $(x - y) \times (x - z)$，展开得贡献为 $x ^ 2 - (y + z)x + yz$。

很明显，求和后 $x ^ 2$ 和 $(y + z)x$ 的大小是固定的，考虑让 $yz$ 尽量大。

很明显，$(x - 0)$ 与 $(x - 1)$ 配对最优，同理 $(x - 2)$ 与 $(x - 3)$ 配最优，……，即 $(x - 2y)$ 与 $(x - 2y + 1)$ 最优，所以我们就固定了 $2 \times n$ 个数的配对。

现在就很简单了：

1. 我们把 $(2i,2i - 1)$ 中的 $2i$ 视为括号 $i$ 的左括号，$2i - 1$ 视为括号 $i$ 的右括号，**一个可以按上述规则分成** $A，B$ **的序列一定是一个合法的括号匹配序列，问题转化为合法括号匹配序列的个数，这个结果很明显是卡塔兰数第** $n$ 项。

2. $n$ 各组可以以任意顺序排序，即答案要乘 $n!$ 。

3. 显然交换组内的 $2i - 1$ 和 $2i$ 不影响最后的结果，有 $2 ^ n$ 种。

答案就是把上面三条进行乘法原理即可。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
const int N = 5e6 + 5,mod = 998244353;
using namespace std;

int n,ans = 0;
int fac[N],ifac[N],f[N];
int qpow(int a,int b) {
	int cnt = 1;
	while (b) {
		if (b & 1) cnt = cnt % mod * a % mod;
		a = a % mod * a % mod;
		b >>= 1;
	}
	return cnt;
}
int C(int n,int m) {
	if (n < 0 || m < 0 || n - m < 0) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int inv(int x) {
	return qpow(x,mod - 2);
}
signed main() {
	fac[0] = ifac[0] = 1;
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[N] = qpow(fac[N],mod - 2);
	for (int i = N - 1; i >= 1; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
	cin >> n;
	cout << fac[n] * qpow(2,n) % mod * inv(n + 1) % mod* C(2 * n,n) % mod;
}

---

