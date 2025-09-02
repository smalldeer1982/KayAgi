# Vasily the Bear and Beautiful Strings

## 题目描述

Vasily the Bear loves beautiful strings. String $ s $ is beautiful if it meets the following criteria:

1. String $ s $ only consists of characters $ 0 $ and $ 1 $ , at that character $ 0 $ must occur in string $ s $ exactly $ n $ times, and character $ 1 $ must occur exactly $ m $ times.
2. We can obtain character $ g $ from string $ s $ with some (possibly, zero) number of modifications. The character $ g $ equals either zero or one.

A modification of string with length at least two is the following operation: we replace two last characters from the string by exactly one other character. This character equals one if it replaces two zeros, otherwise it equals zero. For example, one modification transforms string "01010" into string "0100", two modifications transform it to "011". It is forbidden to modify a string with length less than two.

Help the Bear, count the number of beautiful strings. As the number of beautiful strings can be rather large, print the remainder after dividing the number by $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample the beautiful strings are: "01", "10".

In the second sample the beautiful strings are: "0011", "1001", "1010", "1100".

In the third sample there are no beautiful strings.

## 样例 #1

### 输入

```
1 1 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 2 0
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1 1 1
```

### 输出

```
0
```

# 题解

## 作者：Warriors_Cat (赞：4)

一道组合计数好题，主要是观察到一个性质。

### $Solution:$

记每一位的位置分别为 $0, 1, ... n + m - 1$。

通过题面我们可以得到一个显而易见的结论：

**$1$ 和任何数搭配都是 $0$！**

于是从左往右第一个 $1$ 后面的数都是废的，于是只要枚举从左往右第一个 $1$ 的位置就行。

如果 $g=0$，那么 $1$ 可以在第 $0, 2, 4, ...$ 位；如果 $g=1$，那么 $1$ 可以在第 $1, 3, 5, ...$ 位。由于第一个 $1$ 前面都是 $0$，所以第一个 $1$ 后面可以直接组合数搞定。至于组合数就直接预处理阶乘和阶乘逆元就行。

注意特判一下 $n = 0$，$m = 0$，$m=1$ 的情况。

然后这道题就没了……就这么简单……

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int mod = 1000000007;
int n, m, g, jc[200010], inv[200010], ans;
inline int fpow(int n, int p){
	n %= mod; int ans = 1, base = n;
	while(p){
		if(p & 1) ans = ans * base % mod;
		base = base * base % mod;
		p >>= 1;
	}
	return ans;
}
inline int C(int n, int m){
	return jc[n] * inv[n - m] % mod * inv[m] % mod;
}
signed main(){
	n = read(); m = read(); g = read(); jc[0] = 1;
	for(int i = 1; i <= n + m; ++i) jc[i] = jc[i - 1] * i % mod; inv[n + m] = fpow(jc[n + m], mod - 2);
	for(int i = n + m - 1; i >= 0; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
	if(!n) return printf("%lld", m == 1 ? g : g ^ 1) & 0;
	if(!m) return printf("%lld", n & 1 ? g ^ 1 : g) & 0;
	if(g){
		for(int i = 1; i <= n; i += 2) ans = (ans + C(n + m - i - 1, m - 1)) % mod;
		if(m == 1){
			if(n & 1) ans = (ans - 1 + mod) % mod;
			else ans = (ans + 1) % mod;
		}
	}
	else{
		for(int i = 0; i <= n; i += 2) ans = (ans + C(n + m - i - 1, m - 1)) % mod;
		if(m == 1){
			if(n & 1) ans = (ans + 1) % mod;
			else ans = (ans - 1 + mod) % mod;
		}
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：墨舞灵纯 (赞：2)

一道关于组合数的好题，可惜没有题解吶，我来写第一篇。

这题就是对奇偶位置进行分类讨论。因为只要你后面有两个0就会替换出一个1，然后再和前面的配对又只能替换出0，我们讨论奇偶位置上0和1的摆放用组合数算一下就行。注意一下特殊判断，还有这里不能直接除要乘上逆元。
```
#include<cstdio>
const int N=1000005;
const int mod=1000000007;
typedef long long ll;
ll fac[N],ans;
int n,m,g;
ll inv(ll x)
{
	ll now=1;int p=mod-2;
	while(p)
	{
		if(p&1) now=now*x%mod;
		x=x*x%mod;
		p>>=1;
	}
	return now;
}
il ll c(int n,int m)
{
	return fac[n]*inv(fac[m]*fac[n-m]%mod)%mod;
}
int main()
{ 
	scanf("%d%d%d",&n,&m,&g);
	if(!n)
	{
		printf("%d",!g?(m==1?0:1):(m==1?1:0));
		return 0;
	}
	if(!m)
	{
		printf("%d",!g?(n&1?1:0):(n&1?0:1));
		return 0;
	}
	fac[0]=1;
	for(int i=1;i<=200000;++i) 
		fac[i]=fac[i-1]*i%mod;  
	for(int i=0;i<=n;i+=2) 
		ans=(ans+c(n+m-1-i,m-1))%mod;
	if(m==1) 
		ans=(ans+(n&1?1:-1)+mod)%mod;
	if(g) 
		ans=(c(n+m,n)-ans+mod)%mod;
	printf("%lld",ans); 
	return 0;
} 
```

---

## 作者：shinzanmono (赞：0)

和 Error_Yuan 决斗的时候的题，写一下题解。

我们考虑总方案数，等价于将 $n+m$ 个位置选出 $n$ 个放 $0$，所以答案为 $\binom{n+m}{n}$。

接着考虑将 $g=1$ 的方案数转为总方案数 $-\ g=0$ 的方案数。

然后我们考虑如何求 $g=0$ 的方案数。

若第一位为 $1$，则后面的随便放，答案为 $\binom{n+m-1}{m-1}$。

若第一位为 $0$，则后面的必须为 $1$，方案数为 $ans(n-1,m,1)$。

递归求解即可，接下来我们看看边界条件：

- $n=0$：
 
  - 如果 $m=1$，说明只能留下一位 $1$，答案为 $[g=1]$。

  - 否则说明剩下的只能为 $0$，答案为 $[g=0]$。
  
- $m=0$：

  我们可以证明每两次操作会消掉两个 $0$（`...000` $\rightarrow$ `...01` $\rightarrow$ `...0`），所以：
  
  - 若 $n$ 为奇数，答案为 $[g=0]$。
  - 否则，答案为 $[g=1]$。
  
于是这题就被切了。

```cpp
#include<iostream>
#include<algorithm>
using ll=long long;
const int sz=2e5+10;
const ll mod=1e9+7;
ll fact[sz],inv[sz];
ll qpow(ll base,ll exp){
    ll ans=1;
    while(exp!=0){
        if(exp&1)ans=ans*base%mod;
        base=base*base%mod,exp>>=1;
    }
    return ans;
}
ll C(int n,int m){
    return fact[n]*inv[m]%mod*inv[n-m]%mod;
}
ll query(int n,int m,int g){
    if(n==0){
        if(m==1)return g==1;
        else return g==0;
    }
    if(m==0){
        if(n&1)return g==0;
        else return g==1;
    }
    if(g==1)return (C(n+m,n)-query(n,m,0)+mod)%mod;
    return (C(n+m-1,m-1)+query(n-1,m,1))%mod;
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,m,g;
    std::cin>>n>>m>>g;
    fact[0]=1;
    for(int i=1;i<=n+m;i++)fact[i]=fact[i-1]*i%mod;
    inv[n+m]=qpow(fact[n+m],mod-2);
    for(int i=n+m-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
    std::cout<<query(n,m,g)<<"\n";
    return 0;
}
```

---

## 作者：2021hych (赞：0)

# 前置芝士
方案递推，组合数学。
# 思路
首先在没有 $g$ 的限制下，方案数显然是 $\dbinom{n+m}{m}$。那么我们只要设 $dp_i$ 表示 $i$ 个 $0$，$m$ 个 $1$，限制为 $g=1$ 的方案数，就可以用总方案数减掉他就能得到限制为 $g=0$ 的方案数。考虑隐藏的递推式。显然根据题意，只有一种情况：第一个数为 $0$，后面的长度为 $i-1+m$ 的串的最终值为 $0$。那么就很显然了，递推式子为：
$$dp_i=\dbinom{i-1+m}{i-1}-dp_{i-1}$$
最后特判一下 $m=0$ 的特殊情况和一些小小的细节就好了。
# AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int mod=1e9+7;
int n,m,g;
int fact[N],inv[N],dp[N];
int power(int a,int b,int p) {
	int ans=1%p;
	for(;b;b>>=1) {
		if(b&1) ans=ans*a%p;
		a=a*a%p;
	}
	return ans;
}
void init() {
	fact[0]=1;
	inv[0]=1;
	for(int i=1;i<N;i++) {
		fact[i]=fact[i-1]*i%mod;
		inv[i]=power(fact[i],mod-2,mod);
	}
}
int C(int n,int m,int p) {
	return fact[n]*inv[m]%p*inv[n-m]%p;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>g;
	if(!m) {
		if(n&1) cout<<(!g);
		else cout<<g;
		return 0;
	}
	init();
	dp[0]=(m==1);
	for(int i=1;i<=n;i++) dp[i]=(C(i-1+m,i-1,mod)-dp[i-1]+mod)%mod;
	if(g) cout<<dp[n];
	else cout<<(C(n+m,n,mod)-dp[n]+mod)%mod;
	return 0;
}

```


---

