# Karen and Test

## 题目描述

可怜刚刚到达学校，并且她今天有一场数学考试。

这场考试是关于基本的加减法的。不幸的是，老师们都忙于给Codeforces rounds出测试，以至于没有时间出一个实际的考试。所以，他们仅在这场考试中出了一道包含所有分数的题。

有$n$ 个整数被写在一行上。可怜必须对相邻的两个整数交替进行加减法，并把结果写在下一行。她需要重复这个过程直到只剩下一个整数。第一个操作应当是加法。

注意，如果在上一行她以加法结束，那么下一行她应当以减法开始，反之亦然。

老师们将只关心最后一个整数，如果它正确，可怜将得到所有分数，否则她这场考试将爆零。

可怜在这场考试发挥的很好，但是她害怕会在某处犯错误，并导致她的最终答案错误。如果按这个过程下来，她最后一行应写什么数？

因为这个数可能非常大，仅需输出一个对$10^9+7$ 取模后的非负整数的结果。

## 样例 #1

### 输入

```
5
3 6 9 12 15
```

### 输出

```
36
```

## 样例 #2

### 输入

```
4
3 7 5 2
```

### 输出

```
1000000006
```

# 题解

## 作者：Computer1828 (赞：6)

很明显，这题并不能用暴力模拟的方法。

### 做法一：

考虑找每个数字对最终答案的贡献，我们可以暴力寻找规律。

首先可以对 $n$ 取 $1\dots 15$ 分别计算对答案的贡献，可以发现：

- 当 $n \% 4 = 0$ 时，第 $i$ 个数（$i$ 为奇数）的贡献排列出来很像二项式展开后的系数，而对于 $i$ 为偶数的贡献，将其排列出来后，发现与奇数的差不多，只是正负号相反，于是推得：对于第 $i$ 个数，它的贡献是 $C_{\frac{n-2}{2}}^{\left\lfloor\frac{i-1}{2}\right\rfloor}  \cdot (-1)^{i}$。
- 当 $n \% 4 = 1$ 时，像上面一样找规律，会发现 $i$ 为偶数的时候没有贡献，不难发现通项：对于 $i$ 为奇数，贡献为 $C_{\frac{n-1}{2}}^{\left\lfloor\frac{i-1}{2}\right\rfloor}$，对于 $i$ 为偶数，贡献为 $0$。
- 当 $n \% 4 = 2$ 时，第 $i$ 项的贡献为 $C_{\frac{n-2}{2}}^{\left\lfloor\frac{i-1}{2}\right\rfloor}$。
- 当 $n \% 4 = 3$ 时，暴力跑一遍，此时的第一项的符号是加号，也就是变成了 $n \% 4 = 2$ 的情况。

```cpp
#include<bits/stdc++.h>
#define N 200005
#define mod 1000000007
#define ll long long
using namespace std;
int n;
ll a[N];
ll s[N];
ll ans;

inline ll qpow(ll a,ll b){
	ll res = 1,base = a;
	while(b){
		if(b&1) res = res*base%mod;
		base = base*base%mod;
		b>>=1; 
	}
	return res;
}
inline ll C(ll a,ll b){
	return s[b]*qpow(s[a],mod-2)%mod*qpow(s[b-a],mod-2)%mod;
}

inline void d0(){//情况1
	ll dow = (n-2)/2;
	int opt = 1;
	for(int i = 1;i<=n;++i){
		ans += (C((i-1)/2,dow)*opt*a[i])%mod;
		ans = (ans+mod)%mod;
		opt = -1*opt;
	}
}

inline void d1(){//情况2
	ll dow = (n-1)/2;
	bool opt = true;
	for(int i = 1;i<=n;++i){
		if(opt){
			ans = (ans+C((i-1)/2,dow)*a[i])%mod;
			opt = false;
		}
		else opt = true;
	}
}

inline void d2(){//情况3
	ll dow = (n-2)/2;
	for(int i = 1;i<=n;++i){
		ans = (ans+C((i-1)/2,dow)*a[i])%mod;
	}
}

inline void d3(){//情况4
	bool opt = true;
	for(int i = 1;i<n;++i){
		if(opt) a[i] = (a[i]+a[i+1])%mod,opt = false;
		else a[i] = (a[i]-a[i+1]+mod)%mod,opt = true;
	}
	n--;
	d2();
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;++i) scanf("%lld",a+i);
	s[1] = s[0] = 1;
	for(ll i = 2;i<=n;++i) s[i] = s[i-1]*i%mod;
	bool opt = true;
	switch(n%4){
		case 0:d0();break;
		case 1:d1();break;
		case 2:d2();break;
		case 3:d3();break;
	}
	printf("%lld",ans);
	return 0;
}
```

### 做法2：

考虑 $n$ 为偶数的情况，倒数第二行的两个数满足 $a_i$ 的贡献是 $C_{\frac{n}{2}-1}^{\frac{i-1}{2}}$，而最后一个符号又和 $n$ 是否能被 $4$ 整除。对于 $n$ 为奇数的情况，可以暴力跑一遍让他变成偶数。

---

## 作者：RocksonLee (赞：2)

## Problem

[codeforces](https://codeforces.com/contest/815/problem/B)

[Luogu](https://www.luogu.com.cn/problem/CF815B)

## Solution

$n \leq 200000$ 通过这个数据告诉我们，我们的算法至差应该为 $O(nlogn)$

我们就是在计算过程中，你应该会无从下手。

减法啊，那要怎么办呢，如果只是加法就好了啊，你就可以二项式定理上手搞。

我们尝试填充第一二行的符号可以发现：

如果 $n$ 为奇数，那么第二行的第一个符号就和第一行的符号不一样，就是为减号。

如果 $n$ 为偶数，那么第二行的第一个符号应该为加号。

为什么要思考这一些呢，因为我们在寻找一个共性。

然后你把 $n=4$ 的数列出来

![pica](https://cdn.jsdelivr.net/gh/RocksonLee/PicGo/202203242142295.png)

这时候可以发现后面有一个化成加法的东西。

![picb](https://cdn.jsdelivr.net/gh/RocksonLee/PicGo/202203242143686.png)

于是可以再写一下，你就可以发现规律了

在后面中，第奇数个 $a[i]$（按照你懂的某种方式）加起来就可以作为最后一次运算左边的那个数，

而偶数个 $a[i]$（按照你懂的某种方式）加起来就可以作为最后一次运算右边的那个数。

![picc](https://cdn.jsdelivr.net/gh/RocksonLee/PicGo/202203242148007.png)

蓝色和蓝色相加可以变成 $a_1+2a_3+a_5$。

$1 2 1$

你是否想到什么呢？对，就是二项式定理。

考虑最后的操作符

每一行比上一行多上 $i$ 个，如果多上奇数个，那么就会改变最下面的操作符，而我们加上偶数个却不改变，所以我们可以得到，最后一个操作符应该是按四循环，$n%4$ 可以得到

> ++--++--
> 01230123

我们已经知道了，最后两个数的计算方法

> 奇数个 $a[i]$ 乘上系数加起来就可以作为最后一次运算左边的那个数，
> 偶数个 $a[i]$ 乘上系数加起来就可以作为最后一次运算右边的那个数。

所以我们最后一个操作符是什么，那么我们做完最后一次运算就可以得到答案了。

$$n\%4==0$$

![pic1](https://cdn.jsdelivr.net/gh/RocksonLee/PicGo/202203242213006.png)

$$n\%4==2$$

![pic3](https://cdn.jsdelivr.net/gh/RocksonLee/PicGo/202203242214293.png)

那 $n$ 为奇数怎么办呢，我们暴力解决就好了，直接暴力递推到下一行。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define il inline
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define cl(a, b) memset(a, b, sizeof(a))
typedef long long ll;
typedef unsigned long long ull;

il ll qpow(ll a, ll b)
{
    ll res = 1, base = a;
    while (b)
    {
        if (b & 1) res = res * base % MOD;
        base = base * base % MOD;
        b >>= 1;
    }
    return res;
}

#define N 200010

ll fac[N], n, a[N], ans;

ll C(int m, int n)
{
    return fac[n] % MOD * qpow(fac[m], MOD - 2) % MOD * qpow(fac[n - m], MOD - 2) % MOD;
}

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    fac[0] = 1;
    for (int i = 1; i <= n / 2 + 10; i++) fac[i] = (fac[i - 1] * i) % MOD;
    if (n == 1)
    {
        printf("%lld", a[n]);
        return 0;
    }
    if (n % 2 == 1)
    {
        n--;
        for (int i = 1, op = 1; i <= n; i++, op *= -1) a[i] = a[i] + op * a[i + 1];
    }
    for (int i = 1, op = 1; i <= n; i++)
    {
        int qwq = ((i - 1) / 2);
        ans += a[i] * op * C(qwq, (n - 2) / 2);
        ans %= MOD;
        op *= (n % 4 == 2 ? 1 : -1);
    }
    printf("%lld", (ans + MOD) % MOD);

    return 0;
}
```


---

