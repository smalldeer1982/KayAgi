# 「CROI · R1」浣熊的溪石

## 题目背景

>回首往昔，碧空如洗，日暖风恬。\
溪石深浅有致地错落在明澈似玉的梦枫溪里。\
浣熊们水上跑酷的无限趣忆亦于此伊始……


## 题目描述

日升月落，春去秋来，梦枫溪石的高度千变万化。
爱思考的小浣熊 CleverRaccoon 想探寻这些溪石究竟能构成多少种不同的高度序列。

现有若干个长度为 $n$ 的非负整数列 $a$。

当 $n>1$ 时，$a_1,a_n$ 的取值为 $0\sim m$，其它数 $a_i$ 的取值为 $0\sim m-1$，其中 $2\leq i \leq n-1$。

当 $n=1$ 时，$a_1$ 的取值为 $0\sim m+1$。

**定义**：当且仅当 $\forall i\in\{1,2,\dots ,n\},a_i=b_i$ 或 $\forall i\in\{1,2,\dots ,n\},a_i=b_{n-i+1}$ 时，数列 $a,b$ 相同。

现给定 $n,m$，请求出最多有多少个**不同**的数列，答案对 $998244353$ 取模。

## 说明/提示

#### 解释 #1

当 $n=1,m=3$ 时，$a_i\in\{0,1,2,3,4\}$，共有 $5$ 种不同的高度序列。

当 $n=2,m=2$ 时，共有 $6$ 种不同的高度序列，详情如下：

|序号|$a_1=$|$a_2=$|
|:-:|:-:|:-:|
|$1$|$0$|$0$|
|$2$|$0$|$1$|
|$3$|$0$|$2$|
|$4$|$1$|$1$|
|$5$|$1$|$2$|
|$6$|$2$|$2$|

#### 数据范围
**本题采用 Subtask 捆绑测试。**

|Subtask|$n\leq$|$m\leq$|$T\leq$|特殊性质|Score|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$0$|$10$|$10$|$10$|无特殊性质|$10$|
|$1$|$10^3$|$1$|$10^3$|$m=1$|$5$|
|$2$|$10^3$|$3$|$10$|$m=3$|$10$|
|$3$|$10^3$|$10^3$|$1$|无特殊性质|$15$|
|$4$|$10^6$|$10^3$|$100$|无特殊性质|$10$|
|$5$|$10^6$|$10^6$|$10^6$|无特殊性质|$20$|
|$6$|$10^9$|$10^9$|$10^6$| $n$ 为奇数|$10$|
|$7$|$10^9$|$10^9$|$10^6$| $n$ 为偶数|$10$|
|$8$|$10^{18}$|$10^9$|$10^6$|无特殊性质|$10$|

对于 $100\%$ 的数据，保证 $1\leq n\leq10^{18},1\leq m\leq10^9,1\leq T\leq10^6$。

## 样例 #1

### 输入

```
3
1 3
2 2
6 3```

### 输出

```
5
6
666
```

# 题解

## 作者：Register_int (赞：7)

出题人题解太绷了。

设原串成回文串的方案数为 $x$，没有要求的方案数为 $y$。由于每个非回文串都一定对应另一个回文串，答案为 $\dfrac{x-y}2+y=\dfrac{x+y}2$。

$x$ 显然为 $(m+1)^2m^{n-2}$。$y$ 如何计算？由于只要确定前半部分，即前 $\left\lceil\dfrac n2\right\rceil$ 个元素，就可以确定整个回文串，所以答案即为 $(m+1)m^{\left\lceil\frac n2\right\rceil-1}$。直接计算即可。

出题人改值域的原因可能是给推式子加难度，但我这样做的时候我感觉这题有一种强行二合一的美。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 998244353;
const int inv = mod + 1 >> 1;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; p >>= 1, b = b * b % mod) if (p & 1) res = res * b % mod;
	return res;
}

int t; ll ans, n, m;

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%lld%lld", &n, &m), ans = (m + 1) * qpow(m, n - 1 >> 1) % mod;
		if (n == 1) printf("%d\n", m + 2);
		else printf("%lld\n", (ans * ans % mod * (n & 1 ? qpow(m, mod - 2) : 1) % mod + ans) * inv % mod);
	}
}
```

---

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P9554)

### 思路

既然题目中有关于 $n=1$ 的特判，那么我们不难发现，当 $n=1$ 时，从 $0$ 到 $m+1$ 中有 $m+2$ 种不同的方案。

其他情况，要根据是否回文分为两种情况：

1. 不回文。前后都是 $m+1$ 种，中间 $m$ 种，总和是 $(m+1)^2m^{n-2}$ 种。

2. 回文。前一半和不回文的情况一致，但是后半段却因回文已经确定了，答案需要在不回文的情况下 $\times\lceil\frac{n}{2}\rceil$。

**注意事项：**

- 注意每一步计算都要**取模**。
- 容易超时，建议用**快速幂**。

---

## 作者：金刚xkb (赞：3)

我的做法并不够简洁，偏向纯数学，其余几位巨佬的解法比本篇题解更简洁易懂。

读完整道题目之后，我们可以在数据范围中看到对于 $n$ 奇偶性的提示，由此我们不妨先讨论 $n$ 为奇数和偶数时所有可能情况数之间的关系。

设数列长度为 $n$ 时，所有可能的情况数为 $\text{\text{ans}}_n$。

以 $\text C$ 表示一个数，则长度为 $2n$、$2n+1$、$2n+2$ 的数列分别是这个样子的：

$$\begin{matrix}\underbrace{\text C\,\cdots\,\text C}&-&\underbrace{\text C\,\cdots\,\text C}\\n&&n\end{matrix}$$

$$\begin{matrix}\underbrace{\text C\,\cdots\,\text C}&-\ \text C\ -&\underbrace{\text C\,\cdots\,\text C}\\n&&n\end{matrix}$$

$$\begin{matrix}\underbrace{\text C\,\cdots\,\text C}&-\ \text C-\text C\ -&\underbrace{\text C\,\cdots\,\text C}\\n&&n\end{matrix}$$

观察可得长度为 $2n+1$ 的数列可由长度为 $2n$ 的数列在数列的正中间**增加一个数**得到，这个增加的数可以有 $m$ 个取值。

又因为原来已经有 $\text{ans}_{2n}$ 种情况，因此可得：

$$\text{ans}_{2n+1}=m\ \text{ans}_{2n}$$

这样一来，我们只需要求解 $\text{ans}_{2n}$ 的值就可以完成本题了。

考虑递推，由 $\text{ans}_{2n}$ 向 $\text{ans}_{2n+2}$ 推广，相当于在数列的正中间加入两个新的数，这两个新数的取值分别有 $m$ 种情况，情况分布如下：

| $(a_{n+1},a_{n+2})$ | $0$ | $1$ | $\cdots$ | $m-1$ |
| :-: | :-: | :-: | :-: | :-: |
| $0$ | $\color{red}(0,0)$ | $(0,1)$ | $\cdots$ | $(0,m-1)$ |
| $1$ | $(1,0)$ | $\color{red}(1,1)$ | $\cdots$ | $(1,m-1)$ |
| $\cdots$ | $\cdots$ | $\cdots$ | $\cdots$ | $\cdots$ |
| $m-1$ | $(m-1,0)$ | $(m-1,1)$ | $\cdots$ | $\color{red}(m-1,m-1)$ |

对于总共的 $m^2$ 种情况，每一种对答案的贡献都为 $\text{ans}_{2n}$，然后我们需要减去其中重复的部分。

注意到：当且仅当左右两边的 $n$ 个节点的权值**左右对称**时，会出现重复的情况。例如数列 $110$ $\color{blue}01$ $011$ 和 $110$ $\color{blue}10$ $011$ 是相同的。

这是因为中间新加入的两个数**交换顺序**后得到的数列**恰好与原数列顺序相反**，属于重复的情况。

由表格可见，**只有黑色部分会出现重复的情况**，

接下来计算重复数。由于**左右两侧对称**，所以只要确定了任意一侧 $n$ 个数的取值情况，另一侧的情况也可以唯一确定。假设一共有 $x$ 个新增的组可能出现重复，那么重复数即为一侧 $n$ 个数取值情况数的 $x$ 倍，即 $x\ (m+1)\ m^{n-1}$。

$$\text{ans}_{2n+2}=m^2\ \text{ans}_{2n}-x\ (m+1)\ m^{n-1}$$
$$x=\frac{m^2-m}{2}=\frac{m(m-1)}{2}$$

带入 $x$：

$$\text{ans}_{2n+2}=m^2\ \text{ans}_{2n}-\frac{m^2-1}{2}\ m^n$$

至此，我们已经可以用 $O(Tn)$ 的递推拿到 $70$ 分，而剩下的 $30$ 分需要求出通式，使用快速幂达到 $O(T\log n)$。

$$\begin{cases}\text{ans}_{2n+2}&=m^2\ \text{ans}_{2n}-\frac{m^2-1}{2}\ m^n\\m^2\ \text{ans}_{2n}&=m^4\ \text{ans}_{2n-2}-\frac{m^2-1}{2}\ m^{n+1}\\&\ \vdots\\m^{2n-2}\ \text{ans}_4&=m^{2n}\ \text{ans}_2-\frac{m^2-1}{2}\ m^{2n-1}\\\text{ans}_2&=(m+1)^2-\frac{m(m+1)}{2}=\frac{(m+1)(m+2)}{2}\end{cases}$$

迭加可得：

$$\begin{aligned}\text{ans}_{2n+2}&=\frac{(m+1)(m+2)}{2}\ m^{2n}-\sum_{i=1}^n \frac{m^2-1}{2}\ m^{n+i-1}\\&=\frac{(m+1)(m+2)}{2}\ m^{2n}-\frac{m^2-1}{2}\ m^n\sum_{i=1}^n m^{i-1}\\&=\frac{(m+1)(m+2)}{2}\ m^{2n}-\frac{m^2-1}{2}\ m^n\ \frac{1-m^n}{1-m}\\&=\frac{(m+1)^2}{2}\ m^{2n}+\frac{m+1}{2}\ m^n\end{aligned}$$

因此：

$$\text{ans}_{2n}=\frac{(m+1)^2}{2}\ m^{2n-2}+\frac{m+1}{2}\ m^{n-1}$$

$$\text{ans}_{2n+1}=\frac{(m+1)^2}{2}\ m^{2n-1}+\frac{m+1}{2}\ m^n$$

经检验，$\text{ans}_2=\frac{(m+1)(m+2)}{2}$ 成立。

整理得：

$$\text{ans}_n=\begin{cases}m+2&n=1\\\frac{(m+1)^2}{2}\ m^{n-2}+\frac{m+1}{2}\ m^{\frac n 2-1}&n=2k&(k\in \mathbb N_+)\\\frac{(m+1)^2}{2}\ m^{n-2}+\frac{m+1}{2}\ m^{\frac{n-1}{2}}&n=2k+1&(k\in \mathbb N_+)\end{cases}$$

还有一点要注意的是，通式中的 $\frac{1}{2}$ 不能直接用整除来运算，而是要先求出 $2$ 的逆元。

附上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define p 998244353
ll quick_pow(ll x,ll y){
    ll ta=1;
    while(y){
        if(y&1) ta=ta*x%p;
        x*=x;
        x%=p;
        y>>=1;
    }
    return ta;
}
inline ll get_inv(ll x){
    return quick_pow(x,p-2);
}
int main(){
    int T;
    ll n,m,inv_2,ans,k;
    inv_2=get_inv(2);
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&n,&m);
        if(n==1){printf("%lld\n",(m+2)%p);continue;}
        k=n>>1;
        ans=(m+1)*(m+1)%p*inv_2%p*quick_pow(m,(k<<1)-2)%p+(m+1)*inv_2%p*quick_pow(m,k-1)%p;
        ans%=p;
        if(n&1) ans=ans*m%p;
        printf("%lld\n",ans);
    }
    return 0;
}

```
完结撒花。

---

## 作者：small_john (赞：2)

## 前言

话说为啥要用逆元？把除以 $2$ 放取模前面不就行了吗？

## 思路

一道比较基本的排列组合题。

首先，左边 $\lfloor \frac n2\rfloor$ 个数可以随便填，第一个数有 $m+1$ 种填法，中间 $\lfloor \frac n2\rfloor-1$ 个数有 $m$ 种填法。所以共 $(m+1)\times m^{\lfloor \frac n2\rfloor-1}$ 种，设这个数为 $ans$。

其次，讨论右边的情况。

1. 如果不是回文串，右边就有 $ans-1$ 种，注意这种情况要去重（正着来和反着来），所以这种情况有 $\frac{ans\times(ans-1)}2$ 种。

2. 如果是回文串，就没必要去重，所以一共有 $ans$ 种。

那么，$ans$ 就应该赋值为 $\frac{ans\times(ans-1)}2+ans$。

还有一种特殊的情况，即 $n$ 为奇数，那么最中间这个数就不受影响，方案数乘上 $m$。

最后输出这个 $ans$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int qpow(int x,int y)//快速幂
{
	int res = 1;
	while(y)
	{
		if(y&1) res = res*x%mod;
		y>>=1;
		x = x*x%mod;
	}
	return res;
}
int t,n,m,ans;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		if(n==1)//n为1时情况不一样，需要特判
		{
			cout<<m+2<<'\n';
			continue;
		}
		ans = (m+1)*qpow(m,n/2-1)%mod,ans = (ans*(ans-1)/2%mod+ans)%mod;
		if(n%2) ans = ans*m%mod;
		ans = (ans+mod)%mod;//ans转正数
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：船酱魔王 (赞：2)

# P9554 「CROI · R1」浣熊的溪石 题解

## 题意回顾

一个整数数组，长度为 $ n $，头尾取值范围 $ [0,m] $，中间取值范围 $ [0,m-1] $，$ n=1 $ 时取值范围为 $ [0,m+1] $。如果一个数组**整体翻转**后得到另一个数组，我们认为这两个数组是等价的。求互不等价的数组的个数。

多测，$ T $ 组数据。$ 1 \le n \le 10^{18} $，$ 1 \le m \le 10^9 $，$ 1 \le T \le 10^6 $。

## 分析

$ n=1 $ 特判即可，意义不明。

$ n \ge 2 $ 时，如果整体翻转不计为等价的话，显然有 $ m^{n-2}\times(m+1)^2 $ 种可能，这个数记为 $ p $。

记 $ h=\lceil\frac{n}{2}\rceil $，则回文串有 $ (m+1) \times m^{h-1} $ 个，因为确定前半部分（$ n $ 为奇数则含中间）即可确定后半部分，这个数记为 $ q $。

对于非回文数组，显然两个翻转后相等的数组才能对应一个符合要求的数组；对于回文数组，显然一个回文数组就能对应一个符合要求的数组。因为对于数组元素大小的限制也是回文的，所以一个非回文数组合法时，翻转后必然也合法。因此答案为非回文串的一半加上回文串总数，即 $ \frac{p-q}{2}+q $，化简后为 $ \frac{p+q}{2} $，则可用快速幂求出答案。

注意这里应用了分类讨论的算法代替逆元，不难理解。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;
const int mod = 998244353;
int T;
int pw(int a, long long b) {
	int ans = 1;
	int mul = a;
	while(b) {
		if(b & 1) {
			ans = (long long)ans * mul % mod;
		}
		mul = (long long)mul * mul % mod;
		b >>= 1;
	}
	return ans;
}
int main() {
	scanf("%d", &T);
	long long n;
	int m;
	for(int ti = 1; ti <= T; ti++) {
		scanf("%lld%d", &n, &m);
		if(n == 1) {
			printf("%d\n", m + 2);
			continue;
		}
		long long hf = n / 2;
		if(n % 2 != 0) {
			hf++;
		}
		int ans = ((long long)pw(m + 1, 2) * pw(m, n - 2) % mod + (long long)pw(m + 1, 1) * pw(m, hf - 1) % mod) % mod;
		if(ans % 2 != 0) {
			ans += mod;
		}
		ans /= 2;
		printf("%d\n", ans);
	}
	return 0;
}
```

## 总结与评价

本题难度建议评黄，属于基础计数题。

从 $ 9 $ 个档位的分数和 $ 41 $ 个测试点来看，本题造题是认真走心的，赞美出题人！

---

## 作者：One_JuRuo (赞：2)

## 思路与分析

这道题乍一看还挺难的，但是如果把这个序列拆成两半就会容易一些。

首先，讨论一下序列长度 $n$，如果 $n$ 为偶数，就可以对半分开；如果是 $n$ 奇数，就把中间那位单独拿出来，然后再对半分开。

![](https://cdn.luogu.com.cn/upload/image_hosting/vax2rr5d.png)

我们称上面一部分为 $a$ 序列，下面一部分为 $b$ 序列。

需要注意的是，这里 $b$ 序列的方向与总序列和 $a$ 序列有点不同，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/i70drl5q.png)

黑线的方向代表总序列的顺序，蓝线的方向代表 $a$ 序列的顺序，红线的方向代表 $b$ 序列的顺序。

我们可以发现如果 $a$ 序列和 $b$ 序列交换一下，总序列就相当于颠倒了一次，根据题意，这两个序列算相同的。

如果只关注 $a$ 序列，不考虑其他的，总共有 $M=(m+1)\times m^{\lfloor n/2\rfloor-1}$ 种可能。

我们来大概模拟一下过程：

1. $a$ 序列随机选一种，那么 $b$ 序列共有 $M$ 种取法。
2. $a$ 序列在剩下的情况中再随机选一种，那么 $b$ 序列不能选择 $a$ 序列上次选择的那个，否则就会和上一步的某个序列相同了（因为 $a$ 的取法定然包含于第一步 $b$ 的某个取值，如果 $b$ 和第一步 $a$ 一样，就等于总序列颠倒一次，算同种序列），所以共有 $M-1$ 种取法。

$\cdots$

我们发现如果只考虑 $a$ 序列和 $b$ 序列的话，共有 $\frac{M\times (M+1)}{2}$ 种情况，如果 $n$ 为奇数，那就再乘上 $m$ 就好了，因为单独的中间格子无论怎么取都不会有影响。

所以整个过程就会变得非常简单，先求出 $M$ 然后再算一遍 $\frac{M\times (M+1)}{2}$，再判断个特殊情况。

## 优化还是懒？

只是，我们发现过程种有个除以 $2$ 的过程，再取模的情况下，我们需要求逆元，但是我实在是太懒了，懒得写拓欧，所以我就想了个取巧的偷懒方法。

因为 $(m+1)$ 和 $m$ 中必定有一个是偶数，所以我们先在取模前就除以个 $2$。也就是说求 $M$ 时，我们先除以 $2$ 得到 $N=\frac{M}{2}=\frac{m\times (m+1)}{2} \times m^{\lfloor n/2\rfloor-2}$。

然后再算 $N\times (2\times N+1)$。

这样就不需要拓展欧几里得求逆元了，当然，$n$ 比较小的时候就需要特判了。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const unsigned long long mod=998244353;//当时不知道为什么，复制模数的时候复制了两边，后面才发现，索性就全开unsigned long long了
unsigned long long T,n,m,a;
unsigned long long qsm(unsigned long long a,unsigned long long b)//快速幂
{
	unsigned long long ans=1;
	while(b)
	{
		if(b&1) ans=a*ans%mod;
		a=a*a%mod,b>>=1;
	}
	return ans;
}
int main()
{
	scanf("%llu",&T);
	while(T--)
	{
		scanf("%llu%llu",&n,&m);
		if(n==1) printf("%llu\n",(m+2)%mod);//特判，这个最简单了，我觉得不需要讲
		else if(n==2) printf("%llu\n",(m+2)*(m+1)/2%mod);
		else if(n==3) printf("%llu\n",(m+2)*(m+1)/2%mod*m);//把n比较小的特判了
		else if(n%2==0) a=(m+1)*m/2%mod*qsm(m,n/2-2)%mod,a=(2*a%mod+1)*a%mod,printf("%llu\n",a%mod);//n为偶数的情况
		else a=(m+1)*m/2%mod*qsm(m,n/2-2)%mod,a=(2*a%mod+1)*a%mod,printf("%llu\n",a*m%mod);//n为奇数的情况，要多乘以一个m
	}
	return 0;
}
```

P.S.偷懒是第一生产力（doge

---

## 作者：joy2010WonderMaker (赞：2)

这题我觉得应该是前三题里面最简单的~~我不会告诉你这是因为我第一题没看出来导致的~~。

### 题目分析

题目很明显，要分为两类。

- 当 $n=1$ 时，答案显然为 $m+2$。

- 当 $n\not=1$ 时，不去掉重复，答案应为 $(m+1)^2m^{n-2}$。（首尾 $m+1$ 种，中间每位 $m$ 种）。

考虑如何去掉重复，观察后即可发现，除了回文数都会和它倒过来的数重复。设回文数个数为 $x$ 个，答案即为 $\dfrac{(m+1)^2m^{n-2}+x}{2}$。

再次观察后发现，回文数的个数等于前 $\lceil \dfrac{n}{2}\rceil$ 个位置能组成的数的个数。

### 代码

```cpp
#include<bits/stdc++.h>
#define MOD 998244353
using namespace std;
long long T,n,m,inv2;
long long qpow(long long a,long long b){
	long long res=1,tmp=a%MOD;
	while(b){
		if(b&1)
			res=res*tmp%MOD;
		tmp=tmp*tmp%MOD;
		b>>=1;
	}
	return res;
}
int main(){
	inv2=qpow(2,MOD-2);
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		if(n==1){
			printf("%lld\n",(m+2)%MOD);
			continue;
		}
		long long tmp=(n+1)/2;
		printf("%lld\n",((m+1)%MOD*(m+1)%MOD*qpow(m,(n-2)%(MOD-1))%MOD+(m+1)%MOD*qpow(m,(tmp-1)%(MOD-1))%MOD)*inv2%MOD);
        	//在这里我多使用了一下欧拉定理，不过不用也能过
	}
	return 0;
}
```


---

## 作者：North_encounter (赞：1)

### 题解：「CROI・R1」浣熊的溪石

~~简单数学题~~

### 题意：

给定一个数列，首尾位置的数字共有 $m+1$ 种取值，其余位置上有 $m$ 种，正反相同的视为一种，求数列总数

### 思路：

我们考虑，除回文串之外，每一种排列方式都一定存在一个相反的、可视为一种排列方式，如果我们直接统计，就会重复计算这些方式，所以，除回文串之外，其余的排列方式都应除以二。公式的话建议自己推推，其他的大佬也说得很清楚了，不多赘述。提示一下，其实没有必要对奇偶数分类讨论，$m^{\left\lceil \frac{n}{2} \right\rceil - 1}$，就是除了头尾之外的情况总数。

### 注意：

我以为能一遍过，结果交了四次，注意在每一步运算时都要取模，模意义下，除以一个数等于乘上它在模意义下的逆元，还有，别忘了换行……

### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int t;
int n,m;
inline int read(){
	int f=1,k=0;
	char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-'){
			f=-1;
		}
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return f*k;
}
inline int power(int a,int b){
	int ret=1;
	while(b){
		if(b&1){
			ret=ret*a%mod;
		}
		a=a*a%mod;
		b=b>>1;
	}
	return ret;
}
signed main(){
	t=read();
	while(t--){
		n=read(),m=read();
		if(n==1){
			printf("%lld\n",(m+2)%mod);
			continue;
		}
		int all=power(m+1,2)%mod*power(m,n-2)%mod;
		int fw=(m+1)%mod*power(m,(n+1)/2-1)%mod;
		cout<<(all+fw)%mod*power(2,mod-2)%mod<<endl;
	}
	return 0;
} 
```

可以随时私信，同时欢迎指出错误。

完结

---

## 作者：Vct14 (赞：1)

前置知识：乘法原理。

$n=1$ 时，答案为 $(m+1)-0+1=m+2$ 个。特判即可。

$n\ne1$ 时，首尾都有 $m+1$ 种取值，中间 $n-2$ 个数每个数都有 $m$ 种取值。根据乘法原理，一共 $(m+1)^2m^{n-2}$ 种方案。

然后还要去重。观察可知回文串会重复计算。$a_1$ 共有 $m+1$ 种取值，其他 $d=\left\lceil\dfrac{n-2}{2}\right\rceil$ 个数都只有 $m$ 种取值。根据乘法原理，一共 $(m+1)m^d$ 种方案。

由于非回文串会重复计算，即从首至尾和从尾至首，所以非回文串的结果要除以 $2$。则最终答案为 $\dfrac{(m+1)^2m^{n-2}-(m+1)m^d}{2}+(m+1)m^d=\dfrac{(m+1)^2m^{n-2}+(m+1)m^d}{2}$。记得取模。

---

## 作者：Unordered_OIer (赞：1)

为啥绿（

这题里两个数列相等的定义其实就是要么相同要么反过来，显然回文数列是比较特殊的情况。

根据定义 $n=1$ 特判一下，然后 $n>1$ 的时候，不考虑回文限制，头尾各 $m+1$ 种，中间的每个都是 $m$ 种，所以一共 $(m+1)^2m^{n-2}$ 种。

然后考虑回文，可以当作确定前半后，后半就确定了，那么第一个仍然 $m+1$ 种，剩下的到数列中间位置各 $m$ 种，注意到 $n$ 为奇数时中间的数也有 $m$ 种，所以 $\dfrac{n}{2}$ 应为上取整。

无限制时，相同的数列正序反序都会在里面，所以答案要乘 $\dfrac{1}{2}$，回文单独累加即可。如果写成更简洁的柿子，也就是大多数题解里的加起来再 $/2$。

```cpp
n=read(),m=read();
if(n==1){writeln((m+2)%mod);continue;}
ll qwq=pw(m+1,2)%mod*pw(m,n-2)%mod,qaq=(m+1)%mod*pw(m,(n-1)>>1)%mod;
writeln((qwq+qaq)%mod*499122177%mod);
```

---

## 作者：makerY (赞：1)

[原题](https://www.luogu.com.cn/problem/P9554)

## 思路
1. $n=1$ 时有 $m+2$ 种取值，直接输出答案 $m+2$ 即可，~~虽然不知道题目搞这个分类有啥用~~。
2. $n>1$ 时，需要考虑题中要求：**两个互为相反顺序的序列记为相同**，开始容易想到将全部随意排列的总情况数直接除以 $2$，但是这样对**本身是回文的序列**进行了错误的计数，因为回文的序列反过来为本身，并不会使情况数减少，所以答案为**非回文序列的情况数**除以 $2$ 加上回文序列的情况数。

先算出**回文序列的情况数**（直接对序列的一半计数，另一半可以直接对应）：$(m+1) \times m^{ \lceil \frac{n}{2}\rceil -1}$。

- 为什么 $\frac{n}{2}$ 要向上取整？如果序列长度为奇数，则中间的位置的情况也要计数，序列长度为偶数，则直接计算一半即可。

而直接使用乘法原理，把每一位的情况数相乘，得出**全部随意排列的总情况数**为 $(m+1)(m+1) \times m^{n-2}$。

所以直接根据上面的分析表示出答案为 $\frac{(m+1)(m+1) \times m^{n-2}-(m+1) \times m^{ \lceil \frac{n}{2}\rceil -1}}{2}+(m+1) \times m^{ \lceil \frac{n}{2}\rceil -1}$。

注意本题需要取模，而式子出现了除法，需要先通过费马小定理（模数是质数故可以使用）计算 $2$ 在模 $998244353$ 意义下的逆元。

使用快速幂计算，总复杂度为 $O(T \log n)$。
## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#define ull unsigned long long//注意数据范围 
using namespace std;
const ull Mod=998244353;
ull n,m,t;
ull qpow(ull a,ull p)//快速幂 
{
	ull ans=1;
	while(p)
	{
		if(p&1) ans=ans*a%Mod;
		a=a*a%Mod;
		p>>=1;
	}
	return ans;
}
const ull inv=qpow(2,Mod-2)%Mod;//2在模998244353意义下的逆元
int main()
{
	scanf("%llu",&t);
	while(t--)
	{
		scanf("%llu%llu",&n,&m);
		ull res;
		if(n==1) res=m+2;//特判 
		else res=(((m+1)%Mod*(m+1)%Mod*qpow(m,n-2)%Mod+Mod-(m+1)%Mod*qpow(m,(n+1)/2-1)%Mod)*inv%Mod+(m+1)%Mod*qpow(m,(n+1)/2-1)%Mod)%Mod;
		printf("%llu\n",res);
	}
	return 0;
}
 
```


---

## 作者：teylnol_evteyl (赞：1)

首先，特判 $n=1$ 的情况。

对于 $n$ 是偶数，左半部分（即 $1~n/2$ 位）的取值是没有限制的，所以共有 $t=(m+1)m^{n/2-1}$ 种方案。如果不是回文串，右半部分需要满足翻转后与左半部分不同，所以减去相同的即可，根据乘法原理，方案数为 $t(t-1)$，这部分的方案要除以 $2$；如果是回文串则左右部分相同，有 $t$ 种方案。所以总方案数为 $\dfrac{t(t-1)}{2}+t$。

对于 $n$ 是奇数，相当于在 $n-1$ 的情况下，在第 $n/2$ 位后插入一个数，这个数是不受限制的，所以总方案为 $n-1$ 的情况乘以 $m$。

```cpp
typedef long long LL;

const int P = 998244353, INV2 = (P + 1) / 2;

LL ksm(LL a, LL n)
{
	LL res = 1;
	while(n)
	{
		if(n & 1) res = res * a % P;
		a = a * a % P;
		n >>= 1;
	}
	return res;
}
LL solve(LL n, LL m)
{
	if(n == 1) return (m + 2) % P;
	LL r = (m + 1) * ksm(m, n / 2 - 1) % P;
	r = (r * (r - 1 + P) % P * INV2 % P + r) % P;
	if(n & 1) r = r * m % P;
	return r;
}
```

---

## 作者：xiaoqian02 (赞：1)

### 一：闲话

这题赛时没几分钟就有人 AC 了，确实不是很难。

但是我调了 30 min，后来发现快速幂写挂了……

### 二：思路

一看就是一道计数。

首先，对于 $n=1$ 的情况，一看就和其余的不一样，直接特判掉即可，答案为 $m+2$。注意到 $10^9>998244353$，所以这里也要取模。

接下来看其余的情况。

首先排列组合出所有可能的情况，然后再排除其中相同的。这是一种常用的思路。

要求出所有的情况，我们观察到两边的石头非常特殊，因此这两个要拉出来单独算。

其余的根据乘法原理乘起来即可。方案总数为 $(m-1)^2 \times m^{n-2}$。

接下来排除相同的情况。我们看到，在题目中，“相同”的定义是完全一样或倒过来一样。

想到除以 $2$。但是这样就少考虑了一种情况：回文。

如果这个数列是回文的，那么它在计算总数的时候只被算了 $1$ 次，所以它不该除以 $2$。原因很明显，如果它倒过来，还是原数列。其余的数列倒过来就不是自己了，所以要除以 $2$ 排除相同的。但是这个回文数列倒过来还是自身，它自身在统计时不会被算 $2$ 遍。

这个问题的解决方案也很直白：在统计的时候只算 $1$ 遍，现在就人工加上 $1$ 遍，这样就凑足 $2$ 遍了。

统计回文串的个数需要一个小技巧：如果前一半定了下来，后一半当然也对称地定下来了。

所以可以只统计前一半，这样能保证序列回文，并且不重不漏。

注意这个“一半”是要上取整的，因为如果序列总长度为奇数，我们还要多确定一个中间的值。

当然，最左边那个石头还是要单独拿出来算。

将这两项加起来，现在总可以除以 $2$ 了吧？

不行，因为答案太大，我们取了模，不能那么简单地除以 $2$。

所以又是一个技巧：求逆元。使用费马小定理解决。具体可以参照[这题](https://www.luogu.com.cn/problem/P3811)第一篇题解中的方法。因为 $998244353$ 显然是一个质数，所以可以用逆元。

原本的除以 $2$，现在就变成了乘 $2$ 的逆元，有点类似于除以一个数等于乘这个数的倒数。

最后，我们乘上这个逆元，再取一次模——终于终于结束了。

### 三：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void IOS()//关同步流优化
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return;
}
long long T,n,m;
const long long mod=998244353;
long long ksm(long long a,long long p)//快速幂，必备
{
	long long ans=1;
	while(p)
	{
		if(p&1) ans=ans*a%mod;
		a=a*a%mod;
		p>>=1;
	}
	return ans;
}
int main()
{
    IOS();
    cin>>T;
    while(T--)
    {
    	cin>>n>>m;
    	if(n==1) cout<<(m+2)%mod<<endl;//特判 n=1 的情况
    	else cout<<((m+1)%mod*(m+1)%mod*ksm(m,n-2)%mod+(m+1)%mod*ksm(m,(n-1)/2)%mod)*ksm(2ll,mod-2)%mod<<endl;//很长的式子，一段一段分析
        //(m+1)%mod*(m+1)%mod*ksm(m,n-2)%mod 计算总数。将 2 个 m+1 拆出来，剩下的快速幂
        //(m+1)%mod*ksm(m,(n-1)/2)%mod 统计回文的情况。(n-1)/2 是因为原先应当是 (n+1)/2 个，但是因为去掉了一个左边的石头，需要减去 1
        //ksm(2ll,mod-2) 求逆元
        //最后注意随时取模即可
	}
    return 0;
}
```

---

## 作者：251Sec (赞：1)

基础对称性计数练习题，难度大概橙，为啥 T3。

官方题解写的什么鬼。

---

$n=1$ 特判。感觉题目给这个东西意义不明。

考虑题目给的这个翻转同构的条件，设不考虑该条件下不同串的数目为 $f$，回文串的个数为 $g$，则该条件下答案为 $\dfrac{f+g}{2}$，理由是每个非回文串和另一个非回文串一一对应。

易得 $f=(m+1)^2m^{n-2}$，而可以发现回文串与其前 $\left\lceil\dfrac{n}{2}\right\rceil$ 位构成双射，于是直接对前 $\left\lceil\dfrac{n}{2}\right\rceil$ 位计数，有 $g=(m+1)m^{\left\lceil\frac{n}{2}\right\rceil-1}$。直接快速幂计算即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P = 998244353, I2 = 499122177;
int T;
ll n, m;
ll QPow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % P;
        a = a * a % P;
        b >>= 1;
    }
    return res;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &n, &m);
        if (n == 1) { printf("%lld\n", m + 2); continue; }
        ll f = (m + 1) * (m + 1) % P * QPow(m, n - 2) % P;
        ll g = (m + 1) * QPow(m, (n + 1) / 2 - 1) % P;
        printf("%lld\n", (f + g) % P * I2 % P);
    }
    return 0;
}
```

---

## 作者：DecemberFox (赞：0)

# P9554 「CROI · R1」浣熊的溪石 题解

## 题目分析

要求求出长度为 $n$ 序列 $a$，且满足题目中对每一个 $a_i$ 的限制条件的不同的 $a$ 序列有多少种。注意这里定义的不同是指序列 $a$ 本身或其回文与另一个序列 $b$ 都不相同。

## 解法分析

- 对于 $n=1$ 的情况，此时序列 $a$ 只有一个数 $a_1$，且其取值范围为 $[0,m+1]$，显然序列 $a$ 共有 $m+2$ 种。
- 对于 $n>1$ 的情况，此时若不考虑序列的回文情况，仅考虑相同的情况，则首尾各有 $(m+1)$ 种选择的方案，而中间段有 $m$ 种选取方案，根据乘法原理，不考虑回文时方案总数为 $(m+1)^2m^{n-2}$。

  此时考虑一些序列的回文情况，一个序列 $a$ 的回文序列与其本身是等价的，此时就不能算入，那么答案就是上述式子乘以 $\dfrac{1}{2}$ 了吗？**其中的回文序列较为特别**，其在不考虑回文情况时同样没有被计算两次，若此时直接乘以 $\dfrac{1}{2}$，回文序列的数量就会产生变化。

  那么此时考虑将自身回文的序列重新计算出来，回文序列非常好计算，确定了前半段后，后半段序列也就确定了。因此根据乘法原理，回文序列的方案数就为首尾端 $(m+1)$ 种方案数和中间端**一半**的方案数，即 $(m+1)m^{\lceil\frac{n}{2}\rceil-1}$。注意到若序列长度为奇数，那么正中间的数 $a_{\lceil\frac{n}{2}\rceil}$ 可以取得 $0$ 到 $m-1$ 种的任何数。

  需要注意，在第一个式子 $(m+1)^2m^{n-2}$ 乘以 $\dfrac{1}{2}$ 后，自身回文的序列仅减少了 $\dfrac{1}{2}$，并不是全部，因此在相加时需要让自身回文的方案数也乘上 $\dfrac{1}{2}$。

  综上，$n>1$ 的情况可以使用下面的式子表示：

  $$\frac{(m+1)^2m^{n-2}}{2}+\dfrac{(m+1)m^{\lceil\frac{n}{2}\rceil-1}}{2}=\frac{(m+1)^2m^{n-2}+(m+1)m^{\lceil\frac{n}{2}\rceil-1}}{2}$$

  该式子的值使用快速幂容易求解，需要注意其中出现了除法，故要使用乘法逆元。$2$ 在模 $998244353$ 意义下的乘法逆元为 $499122177$。当然也可以使用快速幂（费马小定理）或欧几里得算法求乘法逆元。

时间复杂度为 $O(T\log n)$。

```cpp
#include<iostream>
#include<cstdio>
namespace io
{
	void read()
	{
		return;
	}
	template<typename nowtype,typename ...nexttype>
	void read(nowtype &now,nexttype &...next)
	{
		register char c=getchar();
		register int sign(1);
		now=0;
		while(!isdigit(c)){if(c=='-') sign=-1;c=getchar();}
		while(isdigit(c)){now=(now<<1)+(now<<3)+(c^48);c=getchar();}
		now*=sign;
		read(next...);
	}
	template<typename nowtype>
	void write(nowtype num,char end='\n')
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-1ll*num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
	}
	template<typename nowtype,typename ...nexttype>
	void write(nowtype num,char end,nexttype ...next)
	{
		register unsigned long long unum(0);
		if(num<0) putchar('-'),unum=-1ll*num;
		else unum=num;
		register int c[35],top(0);
		do c[top++]=unum%10,unum/=10;while(unum);
		while(top) putchar(c[--top]+48);
		putchar(end);
		write(next...);
	}
}
using namespace io;
namespace SOLVE
{
	typedef long long ll;
	typedef unsigned long long ull;
	typedef __int128 lll;
	typedef unsigned __int128 ulll;
	const ll mod=998244353;
	const ll rmod=(mod+1)/2;
	ll pow(ll a,ll x)
	{
		ll ans(1);
		while(x)
		{
			if(x&1) ans=(ans*a)%mod;
			a=(a*a)%mod;
			x>>=1;
		}
		return ans%mod;
	}
	void solve()
	{
		ll n,m;
		read(n,m);
		if(n==1) write((m+2)%mod);
		else write(((((pow(m+1,2)*pow(m,n-2))%mod+((m+1)*pow(m,(n+1)/2-1))%mod)%mod)*rmod)%mod);
	}
}
int main()
{
	int t;
	read(t);
	while(t--) SOLVE::solve();
	return 0;
}
```

---

## 作者：_Emperorpenguin_ (赞：0)

## 思路

- 特判：$n=1$，答案为 $m+2$。

当 $n\gt 1$ 时可先算出所有可能的序列的个数。由题意可知，$a_1$ 和 $a_n$ 各有 $m+1$ 种取值，而其余的数各有 $m$ 种取值。
所以这种序列共有 $(m+1)^2\times m^{n-2}$ 个。 

然后，求出回文序列的个数。只需确定回文字符串的前 $\lceil \dfrac{n}{2} \rceil$ 项，便可确定整个回文串。第一项有 $m+1$ 种取值，
其余 $\lceil \dfrac{n}{2} \rceil - 1$ 项有 $m$ 种取值。所以，回文串一共有 $(m+1)\times m^{\lceil \frac{n}{2} \rceil - 1}$ 种情况。

综上，答案为 $\dfrac{(m+1)^2\times m^{n-2}+(m+1)\times m^{\lceil \frac{n}{2} \rceil - 1}}{2}$。 

附快速幂模板：

```cpp
#define ll long long
const ll Mod=998244353;

ll fpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1){
			res*=a;
			res%=Mod;
		}
		a*=a;
		b>>=1;
	}
	return res;
}
``` 

---

## 作者：yzm0325 (赞：0)

作为 CROI 成员赛后当然得来写写题解对吧（

### 思路

首先特判 $n=1$ 输出 $m+2$（**易错点：也要取模**）。

首先考虑序列所有情况。两边的数有 $m+1$ 种可能，中间的有 $m$ 种可能，根据乘法原理，一共有 $(m+1)^2m^{n-2}$ 种可能的情况。

接着考虑回文序列，发现只要确定前 $\lceil \frac{n}{2} \rceil$ 个数即可确定整个序列。第一个数有 $m+1$ 种选法，其他数有 $m$ 种选法，总共有 $(m+1)m^{\lceil\frac{n}{2}\rceil-1}$ 种回文序列。所以合法情况的种数为：

$$\frac{(m+1)^2m^{n-2}+(m+1)m^{\lceil\frac{n}{2}\rceil-1}}{2}$$

使用快速幂求解即可。注意取模。

### 代码

```cpp
#include <bits/stdc++.h>
#define p 998244353
using namespace std;
long long t, n, m;
long long qpow(long long a, long long b) {
    long long base = a, ans = 1;
    while(b > 0) {
        if(b & 1) ans = (ans * base % p) % p;
        base = (base % p * base % p) % p;
        b >>= 1;
    }
    return ans % p;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> m;
        if(n == 1) cout << (m + 2) % p << '\n';
        else {
            long long a = ((m + 1) * (m + 1) % p * qpow(m, n - 2)) % p;
            long long b = ((m + 1) * qpow(m, (n + 1) / 2 - 1)) % p;
            cout << (a + b) % p * 499122177 % p << '\n';
        }
    }
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

首先我们先算出所有的情况：$(m+1) \times (m+1)+m^{n-2}$，第一个数和最后一个数有 $m+1$ 种选法，中间的 $n-2$ 个数有 $m$ 种选法，根据乘法原理，乘起来就可以了。

接下来我们要去掉其中重复的数列。

发现只有回文数列倒着过来后才不会其他重复的数列，所以我们只需要确认回文数列的个数，因为是回文数列，所以只要确定前半部分的答案，即前面 $\lceil \frac{n}{2} \rceil$ 的位置的数。

第一个数有 $m+1$ 种选法，剩下的有 $m$ 种选法，那么回文数列的选法为：$(m+1) \times m^{\lceil \frac{n}{2} \rceil-1}$。


则我们的答案为：

$$\frac{(m+1) \times (m+1)+m^{n-2}+(m+1) \times m^{\lceil \frac{n}{2} \rceil-1}}{2}$$

至于为什么要加在一起除以 $2$ 呢？因为对于全部的选法不是回文数列的选法中，比如说 $0,0,1$ 和 $1,0,0$ 是重复的数列，所以要除以 $2$，这样加在一起就有 $2$ 倍数量的回文数列，和不是回文数的数列，除以 $2$ 刚好。

所以还有一个好理解的式子为：

$$\frac{(m+1) \times (m+1)+m^{n-2}-((m+1) \times m^{\lceil \frac{n}{2} \rceil-1})}{2}+((m+1) \times m^{\lceil \frac{n}{2} \rceil-1}$$

注意取模和求逆元（费马小定理即可）。

### 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,m,ans;
ll qpow(ll x,ll y){
	ll ans=1;
	while(y){
		if(y&1)
		  ans=(ans*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return ans;
}
int main(){
	T=read();
	while(T--){
		ans=0;
		n=read(),m=read()%mod;
		if(n==1)
		  write(m+2);
		else{
			ans=(((((m+1)*(m+1)%mod)*qpow(m,n-2))%mod+(((m+1)%mod)*qpow(m,(n+1)/2-1))%mod)*qpow(2,mod-2))%mod;
            //ans=((((((m+1)*(m+1)%mod)*qpow(m,n-2))%mod-((((m+1)%mod)*qpow(m,(n+1)/2-1))%mod)+mod)*qpow(2,mod-2))%mod+(((m+1)%mod)*qpow(m,(n+1)/2-1))%mod)%mod;
			write(ans);			
		}
		putchar('\n');
	}
	return 0;
}
```


---

