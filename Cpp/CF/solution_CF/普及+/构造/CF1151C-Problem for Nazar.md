# Problem for Nazar

## 题目描述

Nazar, a student of the scientific lyceum of the Kingdom of Kremland, is known for his outstanding mathematical abilities. Today a math teacher gave him a very difficult task.

Consider two infinite sets of numbers. The first set consists of odd positive numbers ( $ 1, 3, 5, 7, \ldots $ ), and the second set consists of even positive numbers ( $ 2, 4, 6, 8, \ldots $ ). At the first stage, the teacher writes the first number on the endless blackboard from the first set, in the second stage — the first two numbers from the second set, on the third stage — the next four numbers from the first set, on the fourth — the next eight numbers from the second set and so on. In other words, at each stage, starting from the second, he writes out two times more numbers than at the previous one, and also changes the set from which these numbers are written out to another.

The ten first written numbers: $ 1, 2, 4, 3, 5, 7, 9, 6, 8, 10 $ . Let's number the numbers written, starting with one.

The task is to find the sum of numbers with numbers from $ l $ to $ r $ for given integers $ l $ and $ r $ . The answer may be big, so you need to find the remainder of the division by $ 1000000007 $ ( $ 10^9+7 $ ).

Nazar thought about this problem for a long time, but didn't come up with a solution. Help him solve this problem.

## 说明/提示

In the first example, the answer is the sum of the first three numbers written out ( $ 1 + 2 + 4 = 7 $ ).

In the second example, the numbers with numbers from $ 5 $ to $ 14 $ : $ 5, 7, 9, 6, 8, 10, 12, 14, 16, 18 $ . Their sum is $ 105 $ .

## 样例 #1

### 输入

```
1 3
```

### 输出

```
7```

## 样例 #2

### 输入

```
5 14
```

### 输出

```
105```

## 样例 #3

### 输入

```
88005553535 99999999999
```

### 输出

```
761141116```

# 题解

## 作者：xrk2006 (赞：2)

# 【题解】CF1151C Problem for Nazar

[博客园使用效果更佳](https://www.cnblogs.com/xrkforces/p/CF1151C.html)

距离 CSP 剩下 10 天了，据说考前写题解可以增加 RP~所以我来写一篇题解+水点贡献分~

看题解区没有用二分答案来解决这道题的，我来提供一个二分做法。

---

## 题目链接

[CF1151C Problem for Nazar](https://www.luogu.com.cn/problem/CF1151C)

## 题意概述

设正奇数集合为 $\mathrm{A}$，正偶数集合为 $\mathrm{B}$，这两个集合是无限集。

在黑板上写了无数轮数，第 $i$ 轮写下了 $2^{(i-1)}$ 个数.

当$i$为奇数时，从集合 $\mathrm{A}$ 中向后取数，当 $i$ 为偶数时，从集合 $\mathrm{B}$ 中向后取数。

求黑板上第 $l$ 个数到第 $r$ 个数的和，模 $\mathrm{1000000007}$（$10^9+7$）

## 数据范围

$1 \le l,r \le 10^{18}$

## 思路分析

首先看到这个数据范围，可以考虑到时间复杂度大概率是 $\log n$ 这个级别的。

求的是下标为区间 $[l,r]$ 的和，那我们很自然联想到差分：可以先把区间 $[1,r]$ 的和求出来减去区间 $[1,l-1]$ 的和。

那么问题就转化为怎么求出前 $x$ 个数的和。

观察题目条件可以发现，黑板上的数无非就是一串奇数+一串偶数+一串奇数……这样排列的。

且**相邻的两串奇数**之间一定是连续的，也就是假如这一串奇数的结尾是 $k$，那么**与它相邻的下一串奇数**的第一个数一定是 $k+2$。

相邻的两串偶数之间也同理。

> 注意：这里的相邻的两串奇数与相邻的两串数含义不同，每相邻的两串奇数之间隔着一串偶数。

那么我们能否把前 $x$ 个数的和转化为所有的奇数串之和加上所有的偶数串之和呢？

答案是肯定的。

考虑最终形成的序列一定是这样的：

$2^0$ 个奇数+$2^1$ 个偶数+$2^2$ 个奇数+$2^3$ 个偶数+ $\cdots$ +$2^{(i-1)}$ 个不知道是奇数还是偶数的一串数+某个数 $k$ 到 $x$。

很显然第 $i$ 串数的奇偶性取决于 $i$ 的奇偶性，并与 $i$ 的奇偶性相同。

这里的 $k$ 是第 $i-1$ 串数的最后一个数 +2。

那么我们其实可以考虑把前 $i$ 串数的和求出来，然后再单独把从 $k$ 到 $x$ 的和求出来然后相加。

那么我们首先要求出这个 $i$。

因为前 $i$ 个串的长度和为 $2^0+2^1+2^2+\cdots+2^{(i-1)}=2^i-1$，所以我们可以对于每个 $x$ 直接二分求出这个 $i$ 是多少。

具体代码如下：

```cpp
int now=0,ret=0;
for(int step=(1ll<<60);step>=1;step>>=1)
{
	if(now+step<=60&&(1ll<<(now+step))-1<x)now+=step;
}
```

（这里采用的是倍增二分）

最后得到的这个 $now$ 就是我们所说的 $i$。

由于前面已经提到过，相邻的两串奇数/偶数之间都是连续的。

那我们可以直接将前 $i$ 串数的和分成奇数列和偶数列来求。

显然，对于前 $i$ 串数，有 $i/2$ 串偶数列，有 $i-i/2$ 串是奇数列。

那么我们可以预处理出来奇数列和偶数列单独的和。

用 $sum1_i$ 表示整个序列中前 $i$ 串奇数列中有多少个数，$sum2_i$ 表示整个序列中前 $i$ 串偶数列中有多少个数，预处理如下：

```cpp
void init()
{
	int cnt1=0,cnt2=0;
	for(int i=1;i<=60;i++)//之所以是 60，因为 2^60-1 已经大于 1e18 了，所以最多有 60 串数。
	{
		if(i&1)
		{
			cnt1++;
			sum1[cnt1]=sum1[cnt1-1]+(1ll<<(i-1));
		}
		else
		{
			cnt2++;
			sum2[cnt2]=sum2[cnt2-1]+(1ll<<(i-1));
		}
	}
}
```

那么对于前 $i$ 串数，有 $sum2[i/2]$ 个偶数，$sum1[i-i/2]$ 个奇数。

接下来要利用一些等差数列的知识：

- 等差数列第 $n$ 项为 $a_1+nd$（$a_1$ 表示首项，$d$ 表示公差）。

- 等差数列前 $n$ 项的和为 $\frac{(a_1+a_n)*n}{2}$。

那么第 $sum2[i/2]$ 个偶数就为 $sum2[i/2] \times 2$，第 $sum1[i-i/2]$ 个奇数就为 $sum1[i-i/2] \times 2-1$。

所以前 $i$ 串数中偶数列之和为 $s_1=\frac{(2+sum2[i/2]\times 2) \times sum2[i/2]}{2}$，奇数列之和为 $s2=\frac{(1+sum1[i-i/2]*2-1) \times sum1[i-i/2]}{2}$

然后对于最后 $k$ 到 $x$ 的那一段和，可以先把 $k$ 求出来：当 $i$ 为奇数时，$k=sum2[i/2]\times 2+2$，当 $i$ 为偶数时，$k=sum1[i-i/2] \times 2+2$。然后再把 $x$ 求出来：当 $i$ 为奇数时，$k=sum2[i/2] \times 2+(x-2^i+1)\times 2$，当 $i$ 为偶数时，$k=sum1[i-i/2] \times 2+(x-2^i+1)\times 2$。

然后从 $k$ 到 $x$ 也可以直接等差数列求和，设结果为 $s$。

那么最后答案就是 $s1+s2+s$。

## 易错点

别忘了及时取模以及负数保护！！！防止爆 long long！~~我在这挂了 2h……老毛病又犯了。。~~

## 代码实现

```cpp
//CF1151C
#include<cstdio>
#include<iostream>
#define int long long
//#define debug
using namespace std;
const int maxn=105;
const int mod=1e9+7;
int sum1[maxn],sum2[maxn],n;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

void init()
{
	int cnt1=0,cnt2=0;
	for(int i=1;i<=60;i++)
	{
		if(i&1)
		{
			cnt1++;
			sum1[cnt1]=sum1[cnt1-1]+(1ll<<(i-1));
		}
		else
		{
			cnt2++;
			sum2[cnt2]=sum2[cnt2-1]+(1ll<<(i-1));
		}
	}
}

int work(int x)
{
	int now=0,ret=0;
	for(int step=(1ll<<60);step>=1;step>>=1)
	{
		if(now+step<=60&&(1ll<<(now+step))-1<x)now+=step;
	}
	int L=now;
	int re=x-(1ll<<L)+1;
	int tt=L>>1;
	int num=sum2[tt];
	int tot1=num*2;
	int s1=(2+tot1)/2%mod*(num%mod)%mod;
	int kk=L-tt;
	num=sum1[kk];
	int tot2=num*2-1;
	int s2=(1+tot2)/2%mod*(num%mod)%mod;
	if(L&1)
	{
		(ret=(s1+s2)%mod+(tot1+2+tot1+re*2)/2%mod*(re%mod)%mod)%=mod;
	}
	else
	{
		(ret=(s1+s2)%mod+(tot2+2+tot2+re*2)/2%mod*(re%mod)%mod)%=mod;
	}
	return ret;
}

signed main()
{
	init();
	int l,r;
	l=read();r=read();
	cout<<(work(r)-work(l-1)+mod)%mod<<'\n';
	return 0;
}
```



---

## 作者：Erusel (赞：2)

一道挺好的数学题

这应该是比较简洁的题解了

首先，题目要求区间内的和，下意识的想到前缀和

因此，我们的问题转化成了求$1$到$n$之间的和。

我们把它拆成两个序列：

1.奇数序列

2.偶数序列

因此，我们只要知道奇数序列有多少个元素，偶数序列有多少个元素

因为每次奇数和偶数都是$2^{k}$个元素拼接而成的

所以我们可以在$O(logn)$的时间内计算出两个数列的元素个数

代码：

```
ll k=log2(x+1LL),c1=0LL,c2=0LL;//c1，c2代表奇数，偶数序列的长度
for(ll i=0;i<k;i++)//枚举
{
	if(i%2==1)c2=((1LL<<i)+c2)%mod;
	else c1=((1LL<<i)+c1)%mod;//分类讨论并计算
}
ll t=(x-(1LL<<k)+1LL)%mod;
```

但这样似乎还缺些什么

对于最后留下来的几个数，我们也要进行判断，

把它们归到哪一类

代码：
```
ll t=(x-(1LL<<k)+1LL)%mod;//计算余下数的个数
if(k&1)c2=(t+c2)%mod;else c1=(t+c1)%mod;
```

这样还没完

对于一个奇数序列：$1,3,5,7……$

设它有$k$项

那么它的和为$(1+1+(k-1)*2)*k/2=k*k=k^{2}$

对于一个偶数序列：$2,4,6,8……$

设它有$k$项

那么它的和为$(2+2+(k-1)*2)*k/2=k*(k+1)$

因此，当知道两个序列的长度时，我们可以在O(1)的时间内计算出它们的和

完整代码：

```
#include<bits/stdc++.h>

#define rd(x) x=read()

using namespace std;

typedef long long ll;

ll l,r;

const ll mod=1000000007;

inline ll read()
{
    ll x=0ll,f=1ll;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(ll x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

ll solve(ll x)
{
	ll k=log2(x+1LL),c1=0LL,c2=0LL;
	for(ll i=0;i<k;i++)
	{
		if(i%2==1)c2=((1LL<<i)+c2)%mod;
		else c1=((1LL<<i)+c1)%mod;
	}
	ll t=(x-(1LL<<k)+1LL)%mod;
	if(k&1)c2=(t+c2)%mod;else c1=(t+c1)%mod;
	return (c1*c1%mod+c2*(c2+1)%mod+mod)%mod;
}

int main()
{
	rd(l),rd(r);
//	printf("%lld\n",solve(r));
//	printf("%lld\n",solve(l-1));
	printf("%lld\n",(solve(r)-solve(l-1)+mod)%mod);
	
    return 0;
}


```




---

## 作者：Special_Tony (赞：1)

# 思路
根据等差数列求和公式，$1+3+5+\dots+(2n-1)=\frac{(2n-1+1)\times n}2=n^2,2+4+6+\dots+2n=\frac{(2n+2)\times n}2=n\times(n+1)$。所以对于求 $f(s)$（前 $1\sim s$ 个数的和），我们只要枚举每一轮，统计奇偶共有几个数并直接求和即可。最后求 $l\sim r$ 个数，只需要差分求 $f(r)-f(l-1)$ 即可。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const ll mod = 1e9 + 7;
ll l, r;
int i;
ll f (ll x) {
	ll sum1 = 0, sum2 = 0;
	for (i = 0; i < 63; x -= 1ll << i, ++ i)
		if (1ll << i > x) {
			if (i & 1)
				sum2 += x;
			else
				sum1 += x;
			break ;
		} else if (i & 1)
			sum2 += 1ll << i;
		else
			sum1 += 1ll << i;
	sum1 %= mod, sum2 %= mod;
	return (sum1 * sum1 + sum2 * (sum2 + 1)) % mod;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> l >> r;
	cout << ((f (r) - f (l - 1)) % mod + mod) % mod;
	return 0;
}
```

---

## 作者：Yuno (赞：1)

### 题意：  
设正奇数集合为 $\mathrm{A}$，正偶数集合为$\mathrm{B}$。  
在黑板上写了无数轮数，第 $i$ 轮写下了 $2^{(i-1)}$个数。  
当 $i$ 为奇数时，从集合 $\mathrm{A}$ 中向后取数;  
当 $i$ 为偶数时，从集合 $\mathrm{B}$ 中向后取数。  
求黑板上第 $l$ 个数到第 $r$ 个数的和
***
### 题解：

首先看到 $l∼r$ 的求和，立刻就应该想到转化成前缀和。   
也就是说，现在只要计算 $1∼l-1$ 和 $1∼r$ 就可以了。  
先介绍下两个~~妇孺皆知的~~公式  
#### 前 $n$ 个正奇数的和等于 $n^2$
#### 前 $n$ 个正偶数的和等于 $n^2+n$
这个用等差数列推导一下就好了。  
然后发现每轮写下的数都是 $2$ 的幂次，这启发我们记录下有几个奇数，几个偶数。  
具体地，把 $n$ 分解成    
### $n=2^0+2^1+2^2+...+2^k+c$  
因为不一定能完全分解，所以加上 $c$。  
然后上式中的奇数项之和就是奇数个数，偶数项之和就是偶数个数。  
于是就做完了。	
复杂度：$\Theta(log_2n)$  
$Code:$  
```cpp
#include <bits/stdc++.h>
#define int long long
using std::cin;
using std::cout;
const int mo = 1e9 + 7;

int sqr(int x) {return x * x % mo;}

int calc(int x) {
	int t = 1, flag = 1, cnt = 0, odd = 0, even = 0;
	while (cnt + t <= x) {
		cnt += t;
		if (flag) odd += t;
		else even += t;
		t <<= 1;
		flag ^= 1;
	}
	if (flag) odd += x - cnt;
	else even += x - cnt;
	odd %= mo;
	even %= mo;
	int res = ((sqr(odd) + sqr(even)) % mo + even) % mo;
	return res;
}

signed main() {
	std::ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int l, r;
	cin >> l >> r;
	cout << (calc(r) - calc(l - 1) + mo) % mo << '\n';
	return 0;
}
```


---

## 作者：liuzhongrui (赞：0)

## 思路

这个问题涉及到两个无限集合，即正奇数集合 $\mathrm{A} = \{1, 3, 5, 7, \ldots\}$ 和正偶数集合 $\mathrm{B} = \{2, 4, 6, 8, \ldots\}$。我们在黑板上按轮次书写这些数字，按照特定的规则，逐轮增加数量且轮次间切换数字的来源。具体的模式是：

1. 在第 $1$ 轮写出 $2^{(1-1)} = 1$ 个数，从集合 $\mathrm{A}$ 中开始，得到 $1$。
2. 在第 $2$ 轮写出 $2^{(2-1)} = 2$ 个数，从集合 $\mathrm{B}$ 中，得到 $2, 4$。
3. 在第 $3$ 轮写出 $2^{(3-1)} = 4$ 个数，从集合 $\mathrm{A}$ 中，得到 $3, 5, 7, 9$。
4. 在第 $4$ 轮写出 $2^{(4-1)} = 8$ 个数，从集合 $\mathrm{B}$ 中，得到 $6, 8, 10, 12, 14, 16, 18, 20$。

以此类推，依次进行下去。

题目要求我们求出从第 $l$ 个数到第 $r$ 个数的和。由于 $l$ 和 $r$ 的范围是 $10^{18}$，直接生成和遍历所有数是不可行的。

我们首先需要弄清楚在给定范围内的数是哪个轮次生成的。我们可以计算出每一轮生成的数字总数，直到该总数超过 $r$。

在确定了第 $l$ 和第 $r$ 所在的轮次后，我们需要分别计算这两个轮次中的具体数值。包括确定是奇数还是偶数的序列，并找到在该轮中是第几个数。

最后，我们将计算出的数值进行求和，并对 $10^9+7$ 取模，时间复杂度 $O(\log n)$。

## 代码
我看其他大佬的代码都很长，我来一个简短的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MOD=1e9+7;
int l,r;
inline int calc(int n) {
	int sx=0,sy=0,*x=&sx,*y=&sy;
	for(int k=1; n>=k; k<<=1) {
		*x+=k;
		n-=k;
		swap(x,y);
	}
	*x+=n;
	sx%=MOD,sy%=MOD;
	return(sx*sx+(sy+1)*sy)%MOD;
}
signed main() {
	cin>>l>>r;
	cout<<(calc(r)-calc(l-1)+MOD)%MOD;
	return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 思路：

先考虑连续偶数的和：

$ \begin{matrix}
\sum_{i=1}^{n} 2i \\
=2\sum_{i=1}^{n}i \\
=2\frac{n(n+1)}{2}\\
=n(n+1)
\end{matrix} $。

然后是奇数的和：

$\begin{matrix}
\sum_{i=0}^{n} 2i+1 \\
=(2\sum_{i=0}^{n-1}i)+n \\
=2\frac{n(n-1)}{2}+n\\
=n(n-1)+n\\
=n^2
\end{matrix}$

于是可以求出进行 $k$ 轮的和。

那么对于一个 $n$ 求第 $1,2 \dots n$ 所有数的和可以考虑先求出最大的 $k$ 使得 $2^k-1 \le n$。

那么对于进行了 $k$ 轮后没算的数字可以考虑 $k$ 的奇偶，然后算出要添加的种类的数的总个数，用总个数的贡献减去已有的贡献即可。

然后对于 $[l,r]$ 这段区间可以拆分成 $[1,r] - [1,l-1]$，然后按照上面说的做即可。

由于中途怕爆 `long long`，所以用了 `__int128`。

## Code：
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1e9 + 7;

ll l, r;
array<ll, 3> s[70];

ll power(ll a, ll b) {
	ll res = 1;

	for (; b; b >>= 1, a = a * a % mod)
		if (b & 1) res = res * a % mod;

	return res;
}

ll solve(ll n) {
	if (!n) return 0;

	ll k = 1;
	while ((1ll << (k + 1)) - 1 <= n)
		++k;

	// cout << n << ' ' << k << endl;
	ll ans = s[k][0];
	if (k & 1) {
		ll even = s[k][2], cnt = n - s[k][1];
		ans = (__int128)ans + (__int128)cnt * (cnt + 1) % mod - (__int128)even * (even + 1) % mod;
		ans = (ans + mod) % mod;
	} else {
		ll odd = s[k][1], cnt = n - s[k][2];
		// cout << odd << ' ' << cnt <<  ' ' << n << endl;
		ans = ((__int128)ans + (__int128)cnt * (cnt - 1) % mod - (__int128)odd * (odd - 1) % mod + cnt - odd) % mod;
		ans = (ans + mod) % mod;
	}

	return ans;
}

int main() {
	ll odd = 0, even = 0;
	for (ll i = 1; i <= 60; ++i) {
		if (i & 1) odd += (1ll << (i - 1ll));
		else even += (1ll << (i - 1ll));

		s[i] = {((__int128)even * ((__int128)even + 1) % mod + (__int128)odd * ((__int128)odd - 1) % mod + (__int128)odd % mod) % mod, odd, even};
//		cout << s[i][0] << ' ' << i << endl;
	}

	scanf("%lld%lld", &l, &r);

	// cout << solve(r) << ' ' << solve(l - 1) << endl;

	printf("%lld\n", (solve(r) - solve(l - 1) + mod) % mod);

	return 0;
}
```

---

## 作者：dbxxx (赞：0)

[您可在我的博客中查看本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/cf1151c.html)

题目并没有给出 $r - l$ 的限制，这意味着 $l = 1, r = 10^{18}$ 的查询也需要在我们能处理的范围之内。

那可放心差分：第 $l$ 个数到第 $r$ 个数所有和，就是前 $r$ 个数的和减去前 $l - 1$ 个数的和。前缀和一般都比区间和好处理。

前 $r$ 个数一定可以拆分为两个子序列：一个长度为 $p$ 的从 $1$ 开始的连续奇数序列；一个长度为 $q$ 的从 $2$ 开始的连续偶数序列。

简单的数学知识可以推导得答案为 $p^2 + q^2 + q$。那么问题变成求解 $p$ 和 $q$。

根据题意，把 $r$ 分解为 $2^0 + 2^1 + 2^2 + \cdots + 2^k +c$。这个式子里，奇数项之和就是 $p$，偶数项之和就是 $q$。

朴素的 $\log r$ 分解就可以了。

时间复杂度 $\mathcal{O}(\log r)$。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-10-17 16:42:44 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-10-17 16:50:53
 */
#include <bits/stdc++.h>
#define int long long

const int mod = (int)1e9 + 7;

inline int read() {
    int x = 0;
    bool flag = true;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            flag = false;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    if(flag)
        return x;
    return ~(x - 1);
}

inline int solve(int n) {
    int p = 0, q = 0, t = 1;
    for (int s = 1; s <= n; s <<= 1, t ^= 1) {
        n -= s;
        if (t)
            (p += s) %= mod;
        else
            (q += s) %= mod;
    }

    if (t)
        (p += n) %= mod;
    else
        (q += n) %= mod;
    
    return (((p * p % mod + q * q % mod) % mod) + q) % mod;
}

signed main() {
    int l = read(), r = read();
    printf("%lld\n", (solve(r) - solve(l - 1) + mod) % mod);
    return 0;
}
```

如果觉得这篇题解写得好，请不要忘记点赞，谢谢！

---

## 作者：_Clown_ (赞：0)

[更好的阅读体验!](https://www.cnblogs.com/Xsmyy/p/13553024.html)
$$\huge\mathcal{SOLUTION}$$
设黑板上的序列为$A_1,A_2,\ldots$

则题目求的是：
$$
\sum_{i=Left}^{Right}A_i
$$
我们容易想到差分：
$$
\sum_{i=Left}^{Right}A_i
=\sum_{i=1}^{Right}A_i-\sum_{i=1}^{Left-1}A_i
$$
这里需要用到两个公式：
- 奇数序列的前$k$项和为$k^2$
- 偶数序列的前$k$项和为$k^2+k$

所以我们只需要知道有多少个奇数，多少个偶数，就可以用$\mathcal O(1)$的时间复杂度求出和。

考虑如何求项数？

因为每次奇数和偶数都是$2^k$个元素拼接而成的。

所以我们可以在$\mathcal O(logN)$的时间内计算出两个数列的元素个数。

然后就$AC$了$\ldots$
$$\huge\mathcal{CODE}$$
```cpp
#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;
inline long long Sum(long long Length)
{
	register long long i;
	register long long Len1,Len2;
	Len1=Len2=0;
	register long long Log;
	Log=log2(Length+1LL);
	for(i=0;i<Log;i++)
	{
		if(!(i&1))
		{
			Len1+=(1LL<<i);
			Len1%=MOD;
		}
		else
		{
			Len2+=(1LL<<i);
			Len2%=MOD;
		}
	}
	register long long Other;
	Other=Length-(1LL<<Log)+1LL;
	Other%=MOD;
	if(!(Log&1))
	{
		Len1+=Other;
		Len1%=MOD;
	}
	else
	{
		Len2+=Other;
		Len2%=MOD;
	}
	return (Len1*Len1%MOD+Len2*(Len2+1)%MOD+MOD)%MOD;
}
int main(void)
{
	register long long Left,Right;
	cin>>Left>>Right;
	cout<<(Sum(Right)-Sum(Left-1)+MOD)%MOD<<endl;
	return 0;
}
```

---

## 作者：冒泡ioa (赞：0)

>[My Blog](http://bubbleioa.top/archives/858)

## 题解
这次的题目真的都还挺不错的，考的比较活  
**two times more**这个关键信息告诉我们序列变化的规律，即为 $2^i$ 变换一次  
于是我们可以考虑倍增  

我们用 $s[i]$ 来表示第1到i段(每一次变化称为一段)的数字和  
$ls1$ 为奇数序列，$ls2$ 为偶数序列  
$lst1$ 表示当前奇数序列的首项，$lst2$ 同理  

假设现在计算第i段的值（假设是奇数段，偶数段同理）  

我们就有：

- 首项：$lst1$
- 末项：$lst1+(2^{i-1})\times 2$
- 项数：$2^{i-1}$

于是得到值为：
$$(lst1+2^{j-1}-1)\times 2^{i-1}$$

预处理完之后我们就可以处理查询啦（与上面同理）

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int MAXN = 61;
ll l, r;
ll p[MAXN], s[MAXN], l1[MAXN], l2[MAXN];

ll calc(ll x)
{
	for (int i = 60; i >= 0; i--)
	{
		if (p[i] <= x)
		{
			if (i & 1)
				return (s[i] + ((l2[i] + x - p[i] - 1) % mod) * ((x - p[i]) % mod)) % mod;
			return (s[i] + ((l1[i] + x - p[i] - 1) % mod) * ((x - p[i]) % mod)) % mod;
		}
	}
	return 0;
}

void pre()
{
	ll lst1 = 1, lst2 = 2;
	l1[0] = 1, l2[0] = 2;
	for (int i = 1; i <= 60; i++)
	{
		p[i] = p[i - 1] + (1ll << (i - 1));
		if (i & 1)
		{
			s[i] = (s[i - 1] + ((lst1 + (1ll << i - 1) - 1) % mod) * ((1ll << i - 1) % mod)) % mod;
			lst1 += 1ll << i;
		}
		else
		{
			s[i] = (s[i - 1] + ((lst2 + (1ll << i - 1) - 1) % mod) * ((1ll << i - 1) % mod)) % mod;
			lst2 += 1ll << i;
		}
		l1[i] = lst1, l2[i] = lst2;
	}
}

int main()
{
	pre();
	cin >> l >> r;
	cout << ((calc(r) - calc(l - 1)) % mod + mod) % mod << endl;
	return 0;
}


```

---

## 作者：cz666 (赞：0)

 $ Div.2 $ 的~~数论大难题~~，想了我两个小时 $ QAQ $ 。
 
 ### 拒绝抄题解，所以我代码就不贴了，只提供数论做法的思路。
 
 ## 题意简述：
 
 构造一个数列，要求如下：
 
 1. 先把 $ 1 $ 、 $ 2 $ 、 $ 3 $ 、 $ 4 $  $ …… $ 的数字分成奇数和偶数两部分。
 
 2. 然后先放入一个奇数 $ 1 $ ，作为数列第一个；再放入两个偶数 $ 2 $ 和 $ 4 $ ，表示数列第二项和第三项，后面每一块的长度都是 $ 2 $ 的幂次排列，数列前几项如下：
 
```plain
1 2 4 3 5 7 9 6 8 10 12 14 16 18 20 11 13 15... 
```

现在给出一个 $ l $ 和一个 $ r $ ，求该数列中 $ l $ 到 $ r $ 的区间总和，答案对 $ 1e9+7 $ 取模。

 $ l $ 和 $ r $ 的范围都在 $ 1e18 $ 内。
 
 ## 思路：
 
 首先看到这道题内心是崩溃的 $ QAQ $ ， $ l $ 到 $ r $ 的范围为什么要开到 $ 1e18 $ ，崩溃，只能找规律了 $ QAQ $ 。
 
 我们进行大力猜想，首先题目给出的题意说每一块长度都是 $ 2 $ 的幂次，不管三七二十一先写一个快速幂，记录 $ longlong $ 范围里面 $ 2 $ 的幂次。
 
 但由于分奇数和偶数存放，所以我们也要合理分配，快速幂应该求出下面三组需要用到的东西：
 
 1. 奇数组幂次前缀和（便与后续求如果第 $ l $ 个数，就可以在极短的时间里求出 $ l $ 是在奇数组的第几个区块的第几个，进而用等差数列公式求得 $ a[l] $ 的值）（当然也可以是来求 $ r $ 的值）。
 
    求出来应该是这样的：
    
    ```plain
    1 4 16 64 256 1024...
    ```
 
 2. 偶数组幂次前缀和（便与后续求如果第 $ l $ 个数，就可以在极短的时间里求出 $ l $ 是在偶数组的第几个区块的第几个，进而用等差数列公式求得 $ a[l] $ 的值）（当然也还是可以来求 $ r $ 的值）。
 
    求出来应该是这样的：
    
    ```plain
    2 8 32 128 512 2048...
    ```
    
3. 幂次前缀和（便于寻找 $ l $ 到 $ r $ 包括了多少个区块，便于统计答案）。

然后我们只需要求出 $ a[l] $ 所在的区块和它本身的值， $ a[r] $ 所在的区块和它本身的值， $ l $ 到 $ r $ 之间所有完整区块的总和（等差数列求和首项末项相加乘以项数除以二，由于区块长度为 $ 2 $ 的幂次，不会出现项数除以二有小数的情况）。

最后对 $ l $ 所在区间求后缀和， $ r $ 所在的区间做一下前缀和，把所有得到的总和结果进行求和，最后取模就是答案。

最后算一下复杂度：

时间：由于每个区块都是等差数列，计算总和、前缀和、后缀和时间复杂度都是 $ O(1) $ ，而且我们时间复杂度都花费在快速幂上，而 $ longlong $ 范围内只要循环 $ 61 $ 次就可以了，所以整个程序时间复杂度就是一个极小极小的常数，不用担心时间问题。

空间：也就开了三个长度为 $ 60 $ 的 $ longlong $ 数组以及几个变量，远远不会超出限制范围，所以就可以放心水过此题了。

---

