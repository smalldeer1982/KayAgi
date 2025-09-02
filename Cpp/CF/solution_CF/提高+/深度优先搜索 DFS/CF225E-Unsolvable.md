# Unsolvable

## 题目描述

Consider the following equation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF225E/546df2c440088cc1d07628a3b2e6a0b61a00f3dc.png) where sign $ [a] $ represents the integer part of number $ a $ .Let's find all integer $ z $ $ (z&gt;0) $ , for which this equation is unsolvable in positive integers. The phrase "unsolvable in positive integers" means that there are no such positive integers $ x $ and $ y $ $ (x,y&gt;0) $ , for which the given above equation holds.

Let's write out all such $ z $ in the increasing order: $ z_{1},z_{2},z_{3} $ , and so on $ (z_{i}&lt;z_{i+1}) $ . Your task is: given the number $ n $ , find the number $ z_{n} $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
1```

## 样例 #2

### 输入

```
2
```

### 输出

```
3```

## 样例 #3

### 输入

```
3
```

### 输出

```
15```

# 题解

## 作者：wwlw (赞：16)

[Link](https://www.luogu.com.cn/problem/CF225E)
----------------

### 题目描述
求所有使方程
$$z=\lfloor\frac{x}{2}\rfloor+y+xy$$
不存在正整数解 $(x,y)$ 的 $z$ 中，第 $n$ 小的 $z$ ，结果对 $10^9+7$ 取模

### 解法
向下取整不好搞，所以想到分奇偶讨论把向下取整去掉。

1. 若 $x$ 是奇数，令 $x=2k+1$。则
$$z=k+2y+2ky$$
试图化简
$$z+1=(k+1)(2y+1)$$
其中，$k$ 取遍自然数，$y$ 取遍正整数，那么 $k+1$ 取遍所有大于等于 $1$ 的正整数，$2y+1$ 取遍所有大于等于 $3$ 的奇数。这个式子就说明了若 $z+1$ 能分解出一个大于 $1$ 的奇数，那么 $z$ 就肯定不满足条件。所以 $z+1$ 只能是一个 $2$ 的次幂。我们表示为
$$z+1=2^r$$
其中 $r$ 为某个正整数。
2. 若 $x$ 是偶数，令$x=2k$。则
$$z=k+y+2ky$$
同上，分解因式
$$2z+1=(2k+1)(2y+1)=(x+1)(2y+1)$$
其中 $x+1$ 和 $2y+1$ 均为大于等于 $3$ 的奇数。上述式子说明了如果 $2z+1$ 能写成两个大于等于 $3$ 的奇数，那么 $2z+1$ 就不符合条件。而 $2z+1$ 本来就为一个奇数，若可以分解那么一定是两个奇数相乘。综上 $2z+1$ 一定为一个奇素数。表示为
$$2z+1=p$$

综合上述两条
$$\begin{cases}
z+1=2^r \\
2z+1=p
\end{cases}$$
合并得
$$2z+1=2^{r+1}-1=p$$

那么可以看出，$z$ 便是所有 $2z+1$ 是梅森素数时的值。

然后就可以从某 OEIS 复制一下数列，然后打表输出。

---

## 作者：Polarnova (赞：5)

 要求出$ z_n $,可以先变形题目给出的式子: $z=\left[\frac{x}{2}\right]+y+xy$  
 注意到有取整数部分符号，我们尝试把它去掉然后对$x$分类讨论：  
 
 若$x$为奇数，设$x=2k+1$则$z=k+y+(2k+1)y$  
 由于这是一个关于$k,y$的二次方程，因式分解得  
 $z+1=k+y+2ky+1=(2y+1)(k+1)$  
 只有当$z+1$为$2^t$即$z=2^t-1$时，方程没有正整数解
 
 若$x$为偶数,设$x=2k$则$z=k+y+2ky$  
 类似地，因式分解得：  
 $2z+1=2k+2y+4ky+1=(2k+1)(2y+1)=(x+1)(2y+1)$  
 只有当$2z+1$即$z=2^{t-1}-1$为质数时，方程没有正整数解  
 
 综上所述，$z$为梅森素数  
 我们上OEIS查到前40个$t$的值，打表+快速幂即可
 
 ```cpp
#include<cstdio>
const int mod=1e9+7;
int n,pr[41]={
    0,2,3,5,7,13,17,19,31,61,89,107,127,521,607,1279,2203,2281,3217,4253,
    4423,9689,9941,11213,19937,21701,23209,44497,86243,110503,132049,216091,
    756839,859433,1257787,1398269,2976221,3021377,6972593,13466917,20996011
    };

int pow(int x) {
    long long ans=1,base=2;
    for(;x;x>>=1) {
        if(x&1)ans=ans*base%mod;
        base=base*base%mod;
    }
    return (int)ans;
}

int main() {
    scanf("%d",&n);
    printf("%d",pow(pr[n]-1)-1);
    return 0;
}
```

---

## 作者：Richard1211 (赞：1)

# 题意简述
输入一个整数 $k$，询问方程
$$z=\lfloor\frac{x}{2}\rfloor+y+xy$$
无正整数解 $(x,y)$ 的 $z$ 中第 $k$ 小的那一个的值。  
答案对 $10^9+7$ 取模。
# 题目分析
由于有下取整，所以考虑分两种情况求解。  

当 $x$ 为偶数时，方程化为
$$z=\frac{x}{2}+y+xy$$
解得 $x=\frac{2z+1}{2y+1}-1$，因为 $2y+1$ 为奇数，容易发现 $x$ 无解当且仅当 $2z+1$ 为质数。  

当 $x$ 为奇数时，方程化为
$$z=\frac{x-1}{2}+y+xy$$
解得 $x=\frac{2z+2}{2y+1}-1$，因为 $2y+1$ 为奇数，而 $2z+2$ 为偶数，于是发现 $x$ 无解当且仅当 $2z+2$ 不包含除了 $2$ 以外的任何质因子，即 $2z+1=2^k-1$。  

若要同时满足二者，就要求 $2z+1=2^k-1$ 且为质数，那么发现答案就是梅森质数，由于题目名称已经告诉我们直接用自己的电脑跑是不可做的，于是去 OEIS 上把前四十个梅森质数的 **指数** 复制下来，然后跑快速幂输出答案即可，具体实现可以参考代码。

# Code
```cpp
[[maybe_unused]]constexpr long long N=1000100;
constexpr bool MultiCase=false;

constexpr long long P=1000000007;
inline int SolveMain([[maybe_unused]]long long TC){
	vector<long long>G;
	G.emplace_back(2);
	G.emplace_back(3);
	G.emplace_back(5);
	G.emplace_back(7);
	G.emplace_back(13);
	G.emplace_back(17);
	G.emplace_back(19);
	G.emplace_back(31);
	G.emplace_back(61);
	G.emplace_back(89);
	G.emplace_back(107);
	G.emplace_back(127);
	G.emplace_back(521);
	G.emplace_back(607);
	G.emplace_back(1279);
	G.emplace_back(2203);
	G.emplace_back(2281);
	G.emplace_back(3217);
	G.emplace_back(4253);
	G.emplace_back(4423);
	G.emplace_back(9689);
	G.emplace_back(9941);
	G.emplace_back(11213);
	G.emplace_back(19937);
	G.emplace_back(21701);
	G.emplace_back(23209);
	G.emplace_back(44497);
	G.emplace_back(86243);
	G.emplace_back(110503);
	G.emplace_back(132049);
	G.emplace_back(216091);
	G.emplace_back(756839);
	G.emplace_back(859433);
	G.emplace_back(1257787);
	G.emplace_back(1398269);
	G.emplace_back(2976221);
	G.emplace_back(3021377);
	G.emplace_back(6972593);
	G.emplace_back(13466917);
	G.emplace_back(20996011);
	register long long k=G[read()-1]-1,ans=Ksm(2LL,k,P);
	write(ans-1);
	return 0;
}
inline void InitMain(){

	return void();
}
int main(){
//	OF("test");
	InitMain();
	Test(){
		SolveMain(TestCase);
	}
	return 0;
}
```

---

## 作者：f2021ljh (赞：1)

## CF225E Unsolvable 题解

### 题目传送门：

[Codeforces](https://codeforces.com/contest/225/problem/E) | [Codeforces on Luogu](https://www.luogu.com.cn/problem/CF225E)
### 题意：

求所有使方程 $z = \left\lfloor\dfrac x2\right\rfloor + y + xy$ 不存在正整数解 $(x, y)$ 的 $z$ 中，第 $n$ 小的 $z$，结果对 $10^9+7$ 取模。

$1\le n\le40$。

### 思路：

将原式中的向下取整分类讨论得
$$
\left\{
    \begin{aligned}
        z &= k + y + 2ky, &x &= 2k; &(k \in \mathbb N, y \in \mathbb N_+) \\
        z &= k + y + (2k + 1)\cdot y, &x &= 2k + 1. &(k \in \mathbb N, y \in \mathbb{N}_+)
    \end{aligned}
\right.
$$
进一步转化得
$$
\left\{
    \begin{aligned}
        z + 1 &= (k + 1)(2y + 1), && (1) \\
        2z + 1 &= (2k + 1)(2y + 1). && (2)
    \end{aligned}
\right.
$$
于是问题转化为求第 $n$ 小的 $z$ 满足 “$\forall\, k \in \mathbb N, y \in \mathbb{N}_+,\;(1)(2)$式均不成立”。最终 $z$ 的范围即为两种情况中 $z$ 的范围的交集。

由于 $k + 1$ 可以取遍所有正整数，$2y + 1$ 可以取遍所有大于 $1$ 的奇数，所以 $(k + 1)(2y + 1)$ 恒不等于 $2^i(i\geqslant 1,i\in\mathbb N)$（因为 $2^i$ 没有奇因数）。

因此只需使 $z = 2^i - 1$ 就可以使 $(1)$ 式恒不成立。

同理，$2k + 1$ 可以取遍大于等于 $1$ 的奇数，$2y + 1$ 可以取遍大于 $1$ 的奇数，所以 $(2k + 1)(2y + 1)$ 取不到偶数、奇素数和 $1$。

由于 $2z + 1 = 2(2^i - 1) + 1 = 2^{i + 1} - 1$ 为大于等于 $3$ 的奇数，所以当 $2^{i + 1} - 1$ 为素数时满足 $(1)(2)$ 式均不成立。

形如 $2^a - 1$ 的素数称为 **梅森素数** ([梅森素数_百度百科](https://baike.baidu.com/item/%E6%A2%85%E6%A3%AE%E7%B4%A0%E6%95%B0/816141#3))。所以可以直接从 [OEIS](https://oeis.org/A000043) 上复制一波梅森素数的指数 $a_1..a_{40}$ 到数组中。答案即为 $z = (2^{a_n-1} - 1) \bmod (10^9 + 7)$。

### 参考代码：
```cpp
#include <iostream>
using namespace std;
typedef long long ll;
ll const MOD = 1e9 + 7;
ll const t[50] = {0, 2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607, 1279, 2203, 2281, 3217, 4253, 4423, 9689, 9941, 11213, 19937, 21701, 23209, 44497, 86243, 110503, 132049, 216091, 756839, 859433, 1257787, 1398269, 2976221, 3021377, 6972593, 13466917, 20996011}; //梅森素数的指数表
ll n;

inline ll qpow2(ll b, ll a = 2) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

signed main() {

	cin >> n;
	cout << (qpow2(t[n] - 1) - 1) % MOD << '\n';

	return 0;
}
```

---

## 作者：yizcdl2357 (赞：0)

# 题意

给定 $n$，求第 $n$ 小的 $z$ 使得 $\lfloor\dfrac{x}{2}\rfloor+y+xy=z$ 没有正整数解。答案 $\bmod\ 10^9+7$。

# 解题思路

我们先找“$\lfloor\dfrac{x}{2}\rfloor+y+xy=z$ 没有正整数解”的充要条件，再解决“第 $n$ 小”。

首先考虑去掉下取整符号。我们讨论 $x$ 的奇偶性。

若 $x$ 是偶数，设 $x=2k$ 其中 $k$ 是正整数。

则有

$$\begin{aligned}
\lfloor\dfrac{x}{2}\rfloor+y+xy&=z\\
\lfloor\dfrac{2k}{2}\rfloor+y+2ky&=z&\text{（等量代换）}\\
k+y+2ky&=z&\text{（去掉下取整）}\\
2k+2y+4ky&=2z\\
1+2k+2y+4ky&=1+2z\\
(1+2k)(1+2y)&=1+2z&\text{（因式分解）}\\
\end{aligned}$$

即 $(1+2k)(1+2y)=1+2z$ 无正整数解。

注意 $1+2k,1+2y$ 可以取到（大于 $1$ 的）任意奇数，$1+2z$ 也是奇数。

因此 $1+2z$ 不能分解为两个大于 $1$ 的奇数之积，即 **$2z+1$ 是素数**。

若 $x$ 是奇数，设 $x=2k-1$ 其中 $k$ 是正整数。

则有

$$\begin{aligned}
\lfloor\dfrac{x}{2}\rfloor+y+xy&=z\\
\lfloor\dfrac{2k-1}{2}\rfloor+y+(2k-1)y&=z&\text{（等量代换）}\\
k-1+2ky&=z&\text{（去掉下取整）}\\
k+2ky&=z+1\\
k(1+2y)&=z+1&\text{（因式分解）}\\
\end{aligned}$$

即 $k(1+2y)=z+1$ 无正整数解。

注意 $1+2y$ 可以取到（大于 $1$ 的）任意奇数。

因此 $z+1$ 没有奇因子，即 **$z+1$ 是 $2$ 的幂**。

所以，我们只要求满足以下条件的第 $k$ 小的正整数 $z$：
- $2z+1$ 是素数
- $z+1$ 是 $2$ 的幂

设 $z+1=2^x$，则 $2z+1=2^{x+1}-1$ 是素数。

这不禁让我们想到了 [梅森素数](https://oeis.org/A000043)：所有形如 $2^p-1$ 的素数。

于是我们先打一个梅森素数的指数表（见上网址），对于梅森素数 $2z+1=2^{x+1}-1$ 用快速幂求出 $z=2^x-1\bmod 10^9+7$ 即可。
# 代码
```cpp
#include<iostream>
#include<cstdio>
#define int long long
#define M 1000000007
using namespace std;
int mp[42]={0,2,3,5,7,13,17,19,31,61,89,107,127,521,607,1279,2203,2281,3217,4253,4423,9689,9941,11213,19937,21701,23209,44497,86243,110503,132049,216091,756839,859433,1257787,1398269,2976221,3021377,6972593,13466917,20996011,24036583};
inline int P(int y)
{
	if(y==0) return 1;
	if(y&1) return 2*P(y^1)%M;
	int tmp=P(y>>1);
	return tmp*tmp%M;
}
signed main()
{
	int n;
	cin>>n;
	cout<<P(mp[n]-1)-1;
	return 0;
}
```

---

