# Varying Kibibits

## 题目描述

You are given $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Denote this list of integers as $ T $ .

Let $ f(L) $ be a function that takes in a non-empty list of integers $ L $ .

The function will output another integer as follows:

- First, all integers in $ L $ are padded with leading zeros so they are all the same length as the maximum length number in $ L $ .
- We will construct a string where the $ i $ -th character is the minimum of the $ i $ -th character in padded input numbers.
- The output is the number representing the string interpreted in base 10.

For example $ f(10,9)=0 $ , $ f(123,321)=121 $ , $ f(530,932,81)=30 $ .

Define the function

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/d730bfc2d6a92400175f0319f4f66324ea578631.png) Here, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/cbe1963e07d9486bdfb07e1dbd14017f5caa5e0f.png) denotes a subsequence.In other words, $ G(x) $ is the sum of squares of sum of elements of nonempty subsequences of $ T $ that evaluate to $ x $ when plugged into $ f $ modulo $ 1000000007 $ , then multiplied by $ x $ . The last multiplication is not modded.

You would like to compute $ G(0),G(1),...,G(999999) $ . To reduce the output size, print the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/8f5e81fbdf6da04693b872f68826db1077fb8afc.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/4298d47c0191af3c0a3103f431751061bc7e2362.png) denotes the bitwise XOR operator.

## 说明/提示

For the first sample, the nonzero values of $ G $ are $ G(121)=144611577 $ , $ G(123)=58401999 $ , $ G(321)=279403857 $ , $ G(555)=170953875 $ . The bitwise XOR of these numbers is equal to $ 292711924 $ .

For example, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/80f1729ba4a2b96fab1f9859f95517b43796aaad.png), since the subsequences $ [123] $ and $ [123,555] $ evaluate to $ 123 $ when plugged into $ f $ .

For the second sample, we have ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/9bd3e43505031904f9ba81eca399add9357f139b.png)

For the last sample, we have ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/7321daac88d9c4bf2177a9da2946fe31cfad61d4.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF772D/19620adc13a0563d84e1e536cfd1730ef5b2a55f.png) is the binomial coefficient.

## 样例 #1

### 输入

```
3
123 321 555
```

### 输出

```
292711924
```

## 样例 #2

### 输入

```
1
999999
```

### 输出

```
997992010006992
```

## 样例 #3

### 输入

```
10
1 1 1 1 1 1 1 1 1 1
```

### 输出

```
28160
```

# 题解

## 作者：Soulist (赞：6)

~~用 FWT 似乎可以解释得很清楚...~~

然而我不会高维FWT...

----


考虑容斥，对于 $G(x)$ 统计至少为 $x$ 的贡献系数 $g(x)$。

即统计：

集合内所有 $a_i$ 中均满足 $\textrm{bit}_{10}(y)\ge \textrm{bit}_{10}(x)$ 的 $y$ 的贡献和，即 10 进制下每一位都大于 $x$ 的 $y$ 造成的贡献和。

即 $\sum (\sum y)^2$

我们发现我们容斥所求实际上可以看作是有 $6$ 个维度，每个维度的取值为 $0\sim 9$ 的高维后缀和。

在高维后缀和进行合并的时候我们需要计算：

$$\sum_{i\in S} \sum_{j\in T}(i+j)^2$$

简单化简会发现只需要维护 $\sum i^2,\sum i$ 以及集合内的数的个数，具体合并方式为考虑每一对的乘积的贡献以及被算的次数。

然后我傻乎乎的按照容斥计算式想了半天还是计算无法在 $km^k$ 复杂度内容斥出正确答案。

然后你会发现实际上我们计算的 $g(x)$ 是正确答案的高维后缀和，所以我们其实只需要计算一个高维差分即可。

复杂度 $O(n\log_{10} n)$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 1e6 + 5 ; 
const int P = 1e9 + 7 ;  
const int maxn = 1e6 + 5 ; 
const int M = 999999 ;
int n, a[N], g[N], ans[N], fac[N] ; 
struct node {
	int f1, f2, f3 ; 
	void init( int x ) { f3 = 1, f2 = x, f1 = x * x % P ; }
} f[N] ;
node operator * ( node x, node y ) {
	return (node){
		( x.f1 * fac[y.f3] % P + x.f2 * y.f2 * 2 % P + fac[x.f3] * y.f1 % P ) % P,
		( x.f2 * fac[y.f3] % P + y.f2 * fac[x.f3] % P ) % P, x.f3 + y.f3 } ;
}

signed main()
{
	n = gi(), fac[0] = 1 ; 
	rep( i, 1, n ) fac[i] = fac[i - 1] * 2 % P ; 
	rep( i, 1, n ) {
		a[i] = gi() ; node u ; u.init(a[i]) ;
		f[a[i]] = f[a[i]] * u ;
	}
	int l = 1 ;
	rep( k, 0, 5 ) {
		drep( i, 0, M )
			if( (( i / l ) % 10) ^ 9 ) {
				f[i] = f[i] * f[i + l] ;
			}
		l = l * 10 ;
	}
	rep( i, 0, M ) g[i] = f[i].f1 ; 
	l = 1 ; int Ans = 0 ; 
	rep( k, 0, 5 ) {
		rep( i, 0, M ) 
			if( (( i / l ) % 10) ^ 9 ) g[i] = ( g[i] - g[i + l] + P ) % P ;
		l = l * 10 ;
	}
	rep( i, 0, M ) Ans ^= ( i * ( g[i] % P ) ) ;
	printf("%lld\n", Ans ) ;
	return 0 ;
}
```

---

## 作者：tzc_wk (赞：3)

UPD：删了代码前面的板子，代码更美观了

[Codeforces 题目传送门](https://codeforces.com/contest/772/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF772D)

首先很容易注意到一件事，那就是对于所有 $f(S)$ 可能成为 $x$ 的集合 $S$，必定有 $\forall y\in S$，$x$ 的每一位都 $\le y$ 的对应位，于是我们考虑设 $h(x)$ 表示所有满足 $x$ 的对应位都小于 $f(S)$ 的对应位的 $S$ 的贡献之和，显然我们求出 $h(x)$ 之后，可以把 $0\sim 999999$ 中的数都看作一个拥有六个维度，每个维度中的数都 $\in[0,9]$ 的元素，然后仿照二进制下的高维差分跑一遍高维差分即可。

接下来考虑怎样求出 $h(x)$，下记 $[x\subseteq y]$ 表示 $x$ 是否每一位都 $\le y$ 的对应位，那显然根据之前的定义有 $h(x)=\sum\limits_{S\subseteq T}[\forall y\in S,x\subseteq y](\sum\limits_{y\in S}y)^2$，这里面带个平方，可能不是特别显然，我们考虑一个简单些的问题，那就是假设每个集合 $S$ 的贡献都是 $1$ 而不是 $(\sum\limits_{y\in S}y)^2$，那我们只需求出 $c(x)=\sum\limits_{y\in T}[x\subseteq y]$，那么显然就有 $h(x)=2^{c(x)}$。回到原题，注意到我们高维前缀和的实质是合并两个集合 $S,T$ 的贡献，也就是倘若我们已经知道了 $S$ 的贡献和 $T$ 的贡献，怎样支持快速求出 $S\cup T$ 的贡献。我们如果记 $st(x)=\{y|y\in T,x\subseteq y\}$，那么 $h(x)=\sum\limits_{S\subset st(x)}(\sum\limits_{y\in S}y)^2$。并且此题还带个平方，做过 P6144 [USACO20FEB]Help Yourself P 的同学应该都知道，碰到这类高次方求和的问题，我们都可用二项式定理将其拆成若干个低次方的和，然后将它们一一合并即可。具体来说，根据~~二项式定理~~初一课内有 $(x+y)^2=x^2+2xy+y^2$，故我们对于每个集合 $S$ 维护零次方和、一次方和和二次方和，即 $S_0=\sum\limits_{S'\subseteq S}1,S_1=\sum\limits_{S'\subseteq S}\sum\limits_{x\in S'}x,S_2=\sum\limits_{S'\subseteq S}(\sum\limits_{x\in S'}x)^2$，那么当合并两个集合 $S,T$ 时，就有：

- $(S\cup T)_0=\sum\limits_{U\subseteq(S\cup T)}1=\sum\limits_{U\subseteq S,V\subseteq T}1=\sum\limits_{U\subseteq S}\sum\limits_{V\subseteq T}1=S_0T_0$
- $$\begin{aligned}(S\cup T)_1&=\sum\limits_{U\subseteq(S\cup T)}\sum\limits_{x\in U}x=\sum\limits_{U\subseteq S,V\subseteq T}(\sum\limits_{x\in U}x+\sum\limits_{x\in V}x)\\&=\sum\limits_{U\subseteq S}\sum\limits_{V\subseteq T}(\sum\limits_{x\in U}x+\sum\limits_{x\in V}x)\\&=\sum\limits_{U\subseteq S}\sum\limits_{x\in U}x·\sum\limits_{V\subseteq T}1+\sum\limits_{V\subseteq T}\sum\limits_{x\in V}x·\sum\limits_{U\subseteq S}1\\&=S_1T_0+S_0T_0\end{aligned}$$
- $$\begin{aligned}(S\cup T)_2&=\sum\limits_{U\subseteq(S\cup T)}(\sum\limits_{x\in U}x)^2=\sum\limits_{U\subseteq S,V\subseteq T}(\sum\limits_{x\in U}x+\sum\limits_{x\in V}x)^2\\&=\sum\limits_{U\subseteq S}\sum\limits_{V\subseteq T}((\sum\limits_{x\in U}x)^2+(\sum\limits_{x\in V}x)^2+2\sum\limits_{x\in U}x\sum\limits_{x\in V}x)\\&=\sum\limits_{U\subseteq S}(\sum\limits_{x\in U}x)^2·\sum\limits_{V\subseteq T}1+\sum\limits_{V\subseteq T}(\sum\limits_{x\in V}x)^2·\sum\limits_{U\subseteq S}1+2\sum\limits_{U\subseteq S}\sum\limits_{x\in U}x·\sum\limits_{V\subseteq T}\sum\limits_{x\in V}x\\&=S_2T_0+S_0T_2+2S_1T_1\end{aligned}$$

高维前缀和维护下即可，最好开个结构体，时间复杂度 $6\times 999999$。

~~老缝合怪了~~

```cpp
const int MAXN=1e6;
const int MOD=1e9+7;
int n,pw[MAXN+5],ret[MAXN+5];
struct data{
	int sum0,sum1,sum2;
	data(){sum0=sum1=sum2=0;}
	data(int x){sum0=1;sum1=x;sum2=1ll*x*x%MOD;}
	data(int _sum0,int _sum1,int _sum2):sum0(_sum0),sum1(_sum1),sum2(_sum2){}
	data operator +(const data &rhs){
		return data(
		sum0+rhs.sum0,
		(1ll*sum1*pw[rhs.sum0]+1ll*pw[sum0]*rhs.sum1)%MOD,
		(1ll*sum2*pw[rhs.sum0]%MOD+2ll*sum1*rhs.sum1+1ll*pw[sum0]*rhs.sum2)%MOD);
	}
} f[MAXN+5];
int main(){
	scanf("%d",&n);pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=2ll*pw[i-1]%MOD;
	for(int i=1,x;i<=n;i++) scanf("%d",&x),f[x]=f[x]+data(x);
	int cur=1;
	for(int i=0;i<=5;i++){
		for(int j=MAXN-1;~j;j--){
			if((j/cur)%10!=9) f[j]=f[j]+f[j+cur];
		}
		cur=cur*10;
	}
	for(int i=0;i<MAXN;i++) ret[i]=f[i].sum2;
	cur=1;
	for(int i=0;i<=5;i++){
		for(int j=0;j<MAXN;j++){
			if((j/cur)%10!=9) ret[j]=(ret[j]-ret[j+cur]+MOD)%MOD;
		}
		cur=cur*10;
	} ll ans=0;
	for(int j=0;j<MAXN;j++) ans^=1ll*j*ret[j];
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：ywy_c_asm (赞：3)

orz CQZhangyu 神犇，这题我研究了一下午[他的题解](https://www.cnblogs.com/CQzhangyu/p/8445231.html)……

首先，$f(S)$是让每一位上的数位都取个$min$组成新的数，这玩意实质上等同于十进制意义下的按位与（想一下，二进制不也是这么干的吗？），然后你需要处理**子集在十进制意义下按位与等于i的和的平方的和**，子集的与，我们可以想到FWT，这个东西我们思考一下它的本质就会发现它在十进制意义下也是成立的，就是我们从低位到高位，在前缀相同的情况下逐步的将**该位大的统计到小的里面**，最后再逆着来一遍。我们举个栗子：

121234

121233

就比如有这两个数构成的集合，他们除了最后一位不同，前缀是相同的，显然我们做一遍FWT之后，121234的贡献会统计到121233里面，然后121234和121233的贡献会被统计到121232里面，但是他们在10进制下的与等于121233，并不是121232，但是我们在逆FWT的时候会将每个数的“超集”（在10进制意义下，121233就相当于121232的“超集”）的贡献从这个数里面减掉，这就相当于我们做了一个**容斥**，我先统计出有多少数他们与起来是$i$的“超集”，把这些的所有集合的贡献统计进去，记为$f[i]$，然后我们枚举$i$的“超集”$j$，不断地让$f[i]-f[j]$，最终$f[i]$剩下的就是与起来等于$i$的所有集合的贡献。

（所以FWT的本质其实就是个容斥……

那么我们现在要干的事就是统计在第一遍FWT贡献给$i$的这个集合的所有子集的和的平方的和，即$\sum_{T\subseteq S}(\sum_{a_i\in T}a_i)^2$。

很显然我们可以套路的去对每个$a_i$枚举$a_j$考虑产生了多少$a_ia_j$的贡献，可以分两种情况：

①$i\not=j:$那么就是要使这个子集$T$满足$a_i,a_j\in T$，显然有$2^{|S|-2}$个$T$。

②$i=j$即$a_i^2$的贡献，显然你枚举一个包含$a_i$的子集就会产生一个$a_i^2$，有$2^{|S|-1}$个。

然后这个怎么算？我们不是算这个吗：

$2^{|S|-2}\sum_{a_i\in S}a_i\sum_{a_j\in S,j\not=i}a_j+2^{|S|-1}\sum_{a_i\in S}a_i^2$

我们把它变形一下，然后神奇的事情就发生了——

$2^{|S|-2}\sum_{a_i\in S}a_i\sum_{a_j\in S,j\not=i}a_j+2^{|S|-2}\sum_{a_i\in S}a_i^2+2^{|S|-2}\sum_{a_i\in S}a_i^2$

$=2^{|S|-2}\sum_{a_i\in S}a_i\sum_{a_j\in S}a_j+2^{|S|-2}\sum_{a_i\in S}a_i^2$

$=2^{|S|-2}((\sum_{a_i\in S}a_i)^2+\sum_{a_i\in S}a_i^2)$

哈哈，那么我们只要维护3个数组：$cnt[i]$表示序列里有多少个$i$，$sig[i]$表示序列里值为$i$的总和，$sig2[i]$表示序列里值为$i$的平方和，然后把这3个数组FWT一下，得到的$cnt[i]$就相当于$|S|$，$sig[i]$就相当于$\sum_{a_i\in S}a_i$，$sig2[i]$就相当于$\sum_{a_i\in S}a_i^2$，然后就能算啦~

然后这题虽然神但是代码特别的短~

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define p 1000000007
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	ll f[2000001], cnt[2000001], sig[2000001], sig2[2000001];
	inline void fwt(int n) {
	    for (register int bit = 1; bit < n; bit *= 10) {
	        for (register int i = n - 1; i >= 0; i--) {
	            if ((i / bit) % 10 != 0) {
	                cnt[i - bit] = (cnt[i - bit] + cnt[i]) % p;
	                sig[i - bit] = (sig[i - bit] + sig[i]) % p;
	                sig2[i - bit] = (sig2[i - bit] + sig2[i]) % p;
	            }
	        }
	    }
	}
	inline void ifwt(int n) {
	    for (register int bit = 1; bit < n; bit *= 10) {
	        for (register int i = 0; i < n; i++) {
	            if ((i / bit) % 10 != 0)
	                f[i - bit] = (f[i - bit] - f[i] + p) % p;
	        }
	    }
	}
	ll dk[1000001];
	void ywymain() {
	    int n = get();
	    dk[0] = 1;
	    for (register int i = 1; i <= n; i++) {
	        int a = get();
	        cnt[a]++;
	        sig[a] = (sig[a] + a) % p;
	        sig2[a] = (sig2[a] + (ll)a * a) % p;
	        dk[i] = (dk[i - 1] << 1) % p;
	    }
	    fwt(1000000);
	    for (register int i = 0; i < 1000000; i++) {
	        if (!cnt[i])
	            continue;
	        if (cnt[i] == 1) {
	            f[i] = sig2[i];
	            continue;
	        }
	        f[i] = (dk[cnt[i] - 2] * ((sig[i] * sig[i] + sig2[i]) % p)) % p;
	    }
	    ifwt(1000000);
	    ll ans = 0;
	    for (register int i = 0; i < 1000000; i++) ans ^= ((ll)i * f[i]);
	    cout << ans << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：chenxia25 (赞：3)

显然要算出每个 $G(x)$。注意到，仅当 $x'$ 的每一位都 $\geq$ $x$ 的每一位，$x'$ 才可能被包含在 $f(S)=x$ 的 $S$ 里。然后如果满足这样条件的 $S$ 会有 $f(S)$ 的每一位都 $\geq$ $x$ 的每一位，那么可以先求出这样的 $S$ 的和平方和，然后 $\dfrac{G(x)}x$ 就高维差分一下即可得到（非 bitmask 的高维差分 / 前缀和啊，刺激）（注意一点：这时候高维差分的循环顺序也要反向，之前写的都是 bitmask 的高维差分，不反向依然是对的，所以一直没发现错误）。

然后我们考虑如何求，对 $m$ 个数的集合组成的 $2^m$ 个子集的和平方和该如何求。每个 $m$ 个数的集合都是每一位 $\geq$ 某个数的每一位的所有数组成的集合，有高维后缀和内味了。那么我们考虑，对于两个集合，该如何合并它们。

先考虑和零次方和，那显然就乘起来即可。然后是和一次方和（和的和），那么我们还须要记录两个集合的子集个数（$2^?$），然后配合和的和算出来合并起来的结果。到这里都是我们一般做的题目的样子，非常自然。

那么和二次方和该如何求呢？我们考虑列式计算：$\sum\sum(x+y)^2=\sum\sum\left(x^2+2xy+y^2\right)=\sum y^0\sum x^2+2\sum x^1\sum y^1+\sum x^2\sum y^0$。那么我们需要记录两个集合的和 $0\sim 2$ 次方和。那么我们考虑将和 $0\sim 2$ 次方和作为一个整体的元素（`struct` 实现将会异常方便），定义它们之间的二元合并运算，它显然是运算律什么的都满足的。事实上次数更高的话，可以用二项式定理展开。

得出结论：这是一个非二进制高维前缀和 & 差分 与 二项式定理维护和的低次方的套路 的缝合怪。

**_[code](https://www.luogu.com.cn/paste/8ivndkcu)_**

---

## 作者：Prean (赞：1)

~~什么阴间十进制状压~~

题意：给定 $ n $ 数字，求定义函数 $ G(x) $ 能够表示 **满足“十进制按位与为 $ x $”的集合的平方和之和乘上 $ x $**，求 $ \bigoplus _{i=0}^{999999}G(i) $。

这个题很明显干的事情就是让我们对每个数求出一车集合，然后将这一车集合用奇怪的方式加密输出。

当你在求恰好的时候，先想想如何求包含，因为恰好特别难求。

包含不就是个十进制的超集求和？

枚举哪一位，内层再套一个枚举每一个下标，如果这个下标的这一位是 $ 9 $ 就不转移，否则就做一个后缀和。

然后已经得到包含了，如何得到恰好？

先不想十进制，先来想想二进制干了些什么。

二进制似乎就是做了类似 $ a[n][m]=s[n][m]-s[n-1][m]-s[n][m-1]+s[n-1][m-1] $ 的事情？

也就是差分，所以再差分回去。

不过要注意最前面的后缀和是合并集合意义上的后缀和，后面的差分仅仅是对平方和的差分。

为什么是这样的？

假设这个数组是 $ f[S] $，那么 $ f[S] $ 包含的是一车平方和之和，平方和之间没有任何关系，当然可以做一个差分把多的部分扔掉。

那么问题来了，如何维护平方和？
$$ (\sum_{x \in S1} x+\sum_{y \in S2} y)^2=(\sum_{x \in S1})(\sum_{y \in S2}y)^2+(\sum_{x \in S1}x)(\sum_{y \in S2}y)+(\sum_{x \in S1}x)^2(\sum_{y \in S2} $$
所以维护一个 $ 0 $ 次和与一个一次和，再维护一个二次和。可以做到 $ O(6 \times 10^6 \times 2^2) $。

一次和用类似的推柿子即可。

不过理论上来说这玩意儿实际上是低次多项式，所以可以使用将多项式转化为下降幂多项式的 trick，$ O(2) $ 合并两个下降幂多项式，最后 $ O(2) $ 得到答案，复杂度是 $ O(6 \times 10^6 \times 2+10^6 \times 2+2^2) $。~~不过没有啥意义~~

~~注意一下这题的输出有点儿奇怪，是取模之后乘上一个数再异或，而不是乘上一个数之后取模再异或~~
```cpp
#include<cstdio>
#include<cctype>
typedef unsigned ui;
const ui M=1000005,mod=1e9+7,pw10[]={1,1,10,100,1000,10000,100000};
ui n,B[M];char buf[M*7],*p=buf;
inline ui read(){
	ui n(0);char s;while(!isdigit(s=*p++));while(n=n*10+(s&15),isdigit(s=*p++));return n;
}
struct data{
	ui s0,s1,s2;
	data(const ui&s0=1,const ui&s1=0,const ui&s2=0):s0(s0),s1(s1),s2(s2){}
	inline data operator*(const data&it)const{
		return data(1ull*s0*it.s0%mod,(1ull*s1*it.s0+1ull*s0*it.s1)%mod,(1ull*s2*it.s0+2ull*s1*it.s1+1ull*s0*it.s2)%mod);
	}
}f[M];
signed main(){
	ui i,j,k,x;unsigned long long ans(0);fread(buf,1,sizeof buf,stdin);n=read();
	for(i=1;i<=n;++i)x=read(),f[x]=f[x]*data(2,x,1ull*x*x%mod);
	for(i=1;i<=6;++i)for(j=999999;~j;--j)if(j/pw10[i]%pw10[2]^9)f[j]=f[j]*f[j+pw10[i]];
	for(i=0;i^1000000;++i)B[i]=f[i].s2;
	for(i=1;i<=6;++i)for(j=0;j^1000000;++j)if(j/pw10[i]%pw10[2]^9)B[j]=(B[j]+mod-B[j+pw10[i]])%mod;
	for(i=0;i^1000000;++i)ans^=1ull*i*(B[i]%mod);printf("%llu",ans);
}
```

---

## 作者：E_M_T (赞：0)

强推 tzc 大佬的[题解](https://www.luogu.com.cn/article/y0bg9pis)！讲的超级清晰。

以下两个整数 $a$ 和 $b$ 的 $a\subseteq b$ 均指十进制下 $a$ 的每一位都 $\le b$ 对应位上的数字。

考虑设 $F(x)$ 为所有 $f(S)\subseteq x$ 的 $S$ 的贡献总和。这个东西求出来之后用一个十进制意义下类似高维前缀和的东西差分回去就可以了。

先求解 $F(x)$。

根据定义，$F(x)=\sum\limits_{S\subseteq T,\forall p\in S,p\subseteq x} (\sum\limits_{p\in S} p)^2$。

考虑怎么将一个 $x\subseteq y$ 的 $F(y)$  合并到 $F(x)$ 上。直接维护两个答案并不是很好合并。这里用到了同时维护零次方、一次方和二次方的 trick。

设 $s_k(x)$ 为 $F(x)$ 这个贡献的 $k$ 次方和：

$$s_k(x)=\sum\limits_{S\subseteq T,\forall p\in S,p\subseteq x} (\sum\limits_{p\in S} p)^k$$

可以简化这个形式。设 $g(x)=\{ p\mid x\subseteq p,p\in T\}$。

则 $s_0(x)=\sum\limits_{S\subseteq g(x)} 1=2^{|g(x)|}$，$s_1(x)=\sum\limits_{S\subseteq g(x)} (\sum\limits_{p\in S} p)$，$s_2(x)=\sum\limits_{S\subseteq g(x)} (\sum\limits_{p\in S} p)^2$。

最后分开讨论 $F(x)$ 合并 $F(y)$ 的贡献之后的 $F(x)'$ 的零一二次方分别是怎么合并的。这篇[题解](https://www.luogu.com.cn/article/y0bg9pis)推的很详细就不多说具体合并过程了。

然后将贡献差分回去这道题就做完了，注意大小顺序。最重要的可能就是那个维护三个次方的trick 了，瞪了好久不知道怎么维护。

```cpp
#include<bits/stdc++.h>
#define sd std::
#define int long long
#define il inline
#define db double
#define ldb long double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define X first
#define Y second
#define kg putchar(' ')
#define Fr(a) for(auto it:a)
#define dbg(x) sd cout<<#x<<": "<<x<<sd endl
#define tu3 sd tuple<int,int,int>
#define g(a,b) sd get<b>(a)
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
il void printk(int x){print(x);kg;}
const int N=1e6+10,P=1e9+7;
int n,x;
tu3 s[N];//维护0次方,1次方,2次方
tu3 merge(tu3 x,tu3 y)
{
	return sd make_tuple(g(x,0)*g(y,0)%P,(g(x,0)*g(y,1)%P+g(x,1)*(g(y,0)))%P,(g(x,2)*g(y,0)%P+g(y,2)*g(x,0)%P+2*g(x,1)*g(y,1)%P)%P);
}
int po[6];
int f[N];
il void solve()
{
	n=read();
	F(i,0,999999) s[i]=sd make_tuple(1,0,0);
	F(i,1,n) x=read(),s[x]=merge(s[x],sd make_tuple(2,x,x*x%P));
	po[0]=1;
	F(i,0,5)
	{
		if(!po[i]) po[i]=po[i-1]*10;
		f(j,999999,0) if((j/po[i])%10<9) s[j]=merge(s[j],s[j+po[i]]);
	}
	F(i,0,999999) f[i]=g(s[i],2);
	F(i,0,5) F(j,0,999999) if((j/po[i])%10<9) f[j]=(f[j]-f[j+po[i]]+P)%P;
	int ans=0;
	F(j,0,999999) ans^=j*f[j];
	put(ans);
}
signed main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：bruhify (赞：0)



注：该文章中的 $a \geq b$ 符号指 $a$ 在每一位上的值都不少于 $b$。

首先，一坨式子取模后再不带取模地乘 $x$ 又异或到一起...... 这明显没有什么性质。所以考虑计算里面的式子 $F(x)$，最后 $ans=\operatorname{xor}^n_{i=1} x \cdot F(x)$。

接着，$f(S)$ 是一个对集合中的元素每一位取 $\min$ 的函数。使与 $\min$ 有关的函数恰好等于 $x$ 通常是非常困难的，所以可以考虑通过容斥将 「恰好」转化为 「至少」，设 

$$\begin{aligned}S(x)=\sum_{i \geq x} F(i) = (\sum_{S \subseteq T,S \neq \emptyset,f(S) \geq x} (\sum_{y \in S}y)^2) \bmod 1000000007 \end{aligned}$$

如果将 $x$ 的每一位看作一个维度，那么 $S(x)$ 实际上是 $F(x)$ 的高维后缀和。

如何计算 $S(x)$？可以发现如果 $f(S) \leq f(T)$，那么 $T \subseteq S$。所以，$S(x)$ 可以从单元素的集合 $S(f( \{a_i\} ))$ 通过高维后缀和的合并计算出来。

剩下的问题只有求一个集合所有子集的「元素之和的平方」之和，设其为 $h(x)=S(f(x))$。设 $c(x)$ 为 $x$ 中所有元素之和，$g(x)$ 为 $x$ 所有子集的「元素之和」之和，则有 $h$ 的递推式

$$\begin{aligned}h(S \cup T)&=\sum_{x\subseteq S}\sum_{y\subseteq T} (c(x)+c(y))^2 \\&= \sum_{x\subseteq S}\sum_{y\subseteq T} c^2(x)+c^2(y)+2c(x)c(y) \\ &=2^{|T|} h(S)+2^{|S|}h(T)+2g(S)g(T)\end{aligned} $$

$g$ 的递推式

$$\begin{aligned}g(S \cup T)&=\sum_{x\subseteq S}\sum_{y\subseteq T} c(x)+c(y)\\ &=2^{|T|} g(S)+2^{|S|}g(T)\end{aligned} $$

两式均满足交换律，结合律，可以直接在高维后缀和的过程中计算。

计算出 $S(x)$ 后，再做一遍高维差分就得到了 $F(x)$。

~~第一次独立想出这么恶心的式子，好在代码不复杂~~


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;

int n;

const int m=1e6;

ll a[1000005];

ll f[1000005],g[1000005],h[1000005];

ll ans=0;

ll Pow2[1000005];

int main() {
	scanf("%d",&n);
	Pow2[0]=1;
	for(int i=1;i<=n;i++) {
		Pow2[i]=Pow2[i-1]*2%mod;
	}
	for(int i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		h[a[i]]=(h[a[i]]*2+Pow2[f[a[i]]]*a[i]%mod*a[i]%mod+2*g[a[i]]*a[i]%mod)%mod; // h(x)
		g[a[i]]=(g[a[i]]*2+Pow2[f[a[i]]]*a[i]%mod)%mod;// g(x)
		f[a[i]]++;// |x|
	}
	int W=1;
	for(int i=0;i<6;i++) {
		for(int j=m-1;j>=0;j--) {
			if(f[j]==0) {
				continue;
			}
			if((j/W)%10!=0) {
				h[j-W]=(h[j-W]*Pow2[f[j]]+Pow2[f[j-W]]*h[j]+2*g[j-W]*g[j])%mod;
				g[j-W]=(g[j-W]*Pow2[f[j]]+Pow2[f[j-W]]*g[j])%mod;
				f[j-W]=(f[j-W]+f[j])%mod;
			}
		}
		W*=10;
	}
	W=1;
	for(int i=0;i<6;i++) {
		for(int j=0;j<m;j++) {
			if((j/W)%10!=0) {
				h[j-W]=(h[j-W]-h[j]+mod)%mod;
			}
		}
		W*=10;
	}
	for(int i=0;i<m;i++) {
		ans^=i*h[i];
	}
	printf("%lld",ans);
	return 0;
}

```


---

