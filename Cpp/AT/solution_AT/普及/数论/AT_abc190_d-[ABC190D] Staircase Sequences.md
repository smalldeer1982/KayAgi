# [ABC190D] Staircase Sequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc190/tasks/abc190_d

整数からなる公差 $ 1 $ の等差数列のうち、総和が $ N $ であるものはいくつあるでしょうか？

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 10^{12} $
- $ N $ は整数

### Sample Explanation 1

\- $ [12] $ - $ [3,\ 4,\ 5] $ - $ [-2,\ -1,\ 0,\ 1,\ 2,\ 3,\ 4,\ 5] $ - $ [-11,\ -10,\ -9,\ \dots,\ 10,\ 11,\ 12] $ の $ 4 $ 個です。

### Sample Explanation 2

\- $ [1] $ - $ [0,\ 1] $ の $ 2 $ 個です。

## 样例 #1

### 输入

```
12```

### 输出

```
4```

## 样例 #2

### 输入

```
1```

### 输出

```
2```

## 样例 #3

### 输入

```
963761198400```

### 输出

```
1920```

# 题解

## 作者：封禁用户 (赞：0)

### 题目大意

给定一个整数 $N$，求出有多少个由整数组成的等差数列各项之和为 $N$。

### 思路

根据等差数列求和可知：

$N= \frac{L+R}{2}\times (R-L+1)$，

即 $2N= (L+R) \times (R-L+1)$。

枚举 $L+R$ 并判断是否可行即可。

### 代码

```cpp
#include<iostream>
using namespace std;
int main()
{
	long long n; //不开 long long见祖宗。 
	cin>>n;
	n*=2;
	int cnt=0;
	for(long long i=1;i*i<=n;i++)
	{
		if(n%i==0&&i%2!=n/i%2) cnt++;
	}
	cout<<cnt*2;//因为题目中有负数，所以乘2。 
	return 0;
}
```


---

## 作者：loser_seele (赞：0)

首先根据等差数列求和公式，显然有 $ \sum_{i=a}^b i=\frac{(a+b)(b-a+1)}{2} $。于是问题转化为求 $ (a+b)(b-a+1)=2 \times n $ 的 $ (a,b) $ 对数。观察到对于每个 $ 2n =x \times y $，都有 $ a+b=x,b-a+1=y $，解得 $ a=\frac{x-y+1}{2},b=\frac{x+y-1}{2} $。于是对于每对约数都唯一对应一个唯一解，计算 $ 2n $ 的约数个数即可，用 Pollard-rho 分解质因数之后用唯一分解定理统计因子个数，注意最后答案要乘 $ 2 $，时间复杂度 $ \mathcal{O}(n^{\frac{1}{4}}) $，可以通过，目前是最优解。当然本题暴力枚举 $ \sqrt{n} $ 以内的因子统计也可以通过，但复杂度更劣注意因子中的 $ 2 $ 都不对答案造成贡献，因此要先除去。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
#define gc c=getchar()
#define r(x) read(x)
#define ll long long
#define int long long
template<typename T>
inline void read(T&x)
{
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}
#define li inline
#define re register
inline int add(int a,int b,int p)
{
	a+=b;
	if(a>=p)
    a-=p;
	return a;
}
inline int mul(int a,int b,int mod)
{
return (a*b-(int)((long double)a/mod*b)*mod+mod)%mod;
}
ll pow(ll a, ll b, ll m) 
{
  ll ans = 1;
  for (a %= m; b; b >>= 1, a = mul(a, a, m))
    if (b & 1) 
    ans = mul(ans, a, m);
  return ans;
}
ll gcd(ll a,ll b)
{
	return b?gcd(b,a%b):a;
}
ll lcm(ll a,ll b)
{
	return a/gcd(a,b)*b;
}
bool MR_check(ll a, ll p, ll s, int d) 
{
  ll k = pow(a, s, p);
  if (k == 1) return true;
  for (; d; --d, k = mul(k, k, p)) 
  {
    if (k == p - 1) 
    return true;
    if (k == 1) 
    return false;
  }
  return k == 1;
}
bool MR(ll x) 
{
  static const int cnt = 12;
  static const int p[cnt] = { 2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251 };
  if (x == 1) 
  return false;
  ll s = x - 1; 
  int d = 0;
  while (!(s & 1)) 
  ++d, s >>= 1;
  for (int i = 0; i < cnt; ++i) 
  {
    if (x % p[i] == 0) 
    return x == p[i];
    if (!MR_check(p[i], x, s, d)) 
    return false;
  }
  return true;
}
namespace Pollard_Rho 
{
ll PR_check(ll c, ll p) 
{
  ll y = rand() % p, z = y;
  int k = 1, j = 0;
  while(1145141919810) 
  {
    z = (mul(z, z, p) + c) % p;
    ll t = gcd(p, std::abs(z - y));
    if (t > 1) 
    return t;
    if (++j == k) 
    y = z, k <<= 1;
  }
}
void factor_(ll x, std::vector<ll> &v) 
{
  if (x == 1) return;
  if (MR(x)) { v.push_back(x); return; }
  ll y = x;
  while (y == x) y = PR_check(rand() % x, x);
  factor_(y, v);
  factor_(x / y, v);
}
void factor(ll x, std::vector<ll> &v) 
{
  v.clear();
  factor_(x, v);
  std::sort(v.begin(), v.end());
}
}
using Pollard_Rho::factor;
unordered_map<int,int>cnt;
signed main()
{
    int T=1;
    for(;T;--T)
    {
    	int n;
        r(n);
        while(n%2==0)
        n/=2;
        if(n==1)
        return !puts("2");
        int ans=1;
        vector<int>d;
        factor(n,d);
        for(auto x:d)
        ans/=(cnt[x]+1),cnt[x]++,ans*=(cnt[x]+1);
        ans*=2;
    	printf("%lld\n",ans);
    }
}
```


---

