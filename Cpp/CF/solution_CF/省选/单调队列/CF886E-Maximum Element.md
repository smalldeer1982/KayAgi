# Maximum Element

## 题目描述

从前有一个叫$Petya$的神仙，嫌自己的序列求max太慢了，于是将序列求max的代码改成了下面这个样子：

```cpp
int fast_max(int n,int a[])
{
	int ans=0;
	int offset=0;
	for(int i=0;i<n;++i)
	{
		if(ans<a[i])
		{
			ans=a[i];
			offset=0;
		}
		else
		{
			offset++;
			if(offset==k)return ans;
		}
	}
	return ans;
}
//大括号换行，无多余空格，by wucstdio
```

这个函数的原理是，如果碰到一个数后面连续的$k$个数都比它小，那么就把这个数当做序列的最大值。

然而很显然，这份代码是错的。这位$Petya$神仙对它出错的情况很感兴趣。于是他找到了同为神仙的你，让你求有多少长度为$n$的排列，这个函数会返回错误的结果，即返回值不是$n$。由于答案过大，你只需要输出这个数对$10^9+7$取模的结果。

## 样例 #1

### 输入

```
5 2
```

### 输出

```
22
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
6
```

## 样例 #3

### 输入

```
6 3
```

### 输出

```
84
```

# 题解

## 作者：da32s1da (赞：13)

考虑一个排列的返回值是**错误**的，当且仅当在$n$前有连续的$k$个数，它们均小于前面的某个数。

也就是说，一个排列的返回值是**正确**的，当且仅当在$n$出现前，**还没有返回**。

考虑令$f[i]$为长度为$i$且还没有返回的排列数量。

显然有$$f[i]=\sum_{j=i-k+1}^{i}f[j-1]\times \binom{i-1}{i-j}\times (i-j)\ !$$

表示最大值$i$出现在第$j$位上，于是还有$i-1$个数，选出$i-j$个放到后面，就是$\binom{i-1}{i-j}$。后面$i-j$个数还有$(i-j)\ !\ $种放法，前面的$j-1$个数还有$f[j-1]$种放法。

化简一下式子。

- $f[i]=\sum_{j=i-k+1}^{i}f[j-1]\times \binom{i-1}{i-j}\times (i-j)\ !$
- $\ \ \ \ \ \ =(i-1)\ !\times \sum_{j=i-k+1}^{i}\frac{f[j-1]}{(j-1)\ !}$
- $\ \ \ \ \ \ =(i-1)\ !\times \sum_{j=i-k}^{i-1}\frac{f[j]}{j\ !}$

令$g[i]=\frac{f[i]}{i\ !}$，则$g[i]=\frac{\sum_{j=i-k}^{i-1}g[j]}{i}$

易知答案为$$Ans=n\ !\ -\sum_{i=1}^nf[i-1]\times \binom{n-1}{n-i}\times (n-i)\ !$$

化简得

- $Ans=n\ !\ -\sum_{i=1}^nf[i-1]\times \binom{n-1}{n-i}\times (n-i)\ !$
- $\ \ \ \ \ \ \ =n\ !\ -\sum_{i=1}^ng[i-1]\times (i-1)\ !\times \binom{n-1}{n-i}\times (n-i)\ !$
- $\ \ \ \ \ \ \ =n\ !\ -(n-1)\ !\times \sum_{i=1}^ng[i-1]$
- $\ \ \ \ \ \ \ =(n-1)\ !\times (n-\sum_{i=1}^ng[i-1])$

$g[i]$记个前缀和$O(n)$求一遍，$1-n\ $的逆元$O(n)$求，总复杂度$O(n)$。

```
#include<cstdio>
const int mod=1e9+7;
const int N=1e6+50;
int n,k,g[N],inv[N],Sum,Ans,fac;
int main(){
	scanf("%d%d",&n,&k);
	g[0]=fac=1;Ans=n;
    //初始化
	for(int i=1;i<=n;i++){
		inv[i]=(-1ll*(mod/i)*inv[mod%i]%mod+mod+(i==1))%mod;
        //递推逆元
		Sum=(Sum+g[i-1])%mod;
		if(i>k)Sum=(Sum-g[i-k-1]+mod)%mod;
		g[i]=1ll*Sum*inv[i]%mod;
        //计算新的g[i]
		Ans=(Ans-g[i-1]+mod)%mod;
        //计算n-sum{g[i-1]}
		if(i!=1)fac=1ll*fac*(i-1)%mod;
        //计算(n-1)!
	}
	printf("%d\n",1ll*fac*Ans%mod);
}
```

---

## 作者：wind_whisper (赞：5)

[更糟的阅读体验](https://blog.csdn.net/BUG_Creater_jie/article/details/122304311) 
## $\text{Solution}$
纯纯的dp题。
关键在于我们 dp 时只关注**不同元素之间的相对大小**。

非法情况不易统计，考虑转而考虑合法情况再用全排列减。  
设计 $f_i$ 为长度为 $i$ 的排列循环到一直最后也没有跳出的方案数。  
枚举最大的元素 $i$ 放置的位置 $j$，由于不能跳出，$j$ 只能放在$[i-k+1,i]$ 的位置。  
那么就有：
$$f_i=\sum_{j=i-k+1}^i \binom{i-1}{j-1}\times f_{j-1}\times (j-i)!$$
解释一下，当元素 $i$ 放在位置 $j$ 时，选出 $j-1$ 个数放前面，方案是$\binom{i-1}{j-1}$；前面的方案就是 $f_{j-1}$（和排列是等价的）；后面随便放，方案就是阶乘。  
然后把组合数拆一下，变成：
$$f_i=\sum_{j=i-k+1}^i\frac{(i-1)!}{(j-1)!} \times f_{j-1}$$
$$=(i-1)!\times\sum_{j=i-k+1}^i\frac{f_{j-1}}{(j-1)!} $$
$$=(i-1)!\times\sum_{j=i-k}^{i-1}\frac{f_{j}}{j!} $$
把后面的东西拿前缀和优化一下即可线性求出 $f$ 数组。  
求出 $f$ 之后，枚举 $n$ 所在的位置 $i$，答案就是：
$$ans=\sum_{i=1}^n\binom{n-1}{i-1}\times f_{i-1}\times (n-i)!$$
## $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}


const int N=1e6+100;
const int mod=1e9+7;
int n,m,k;
inline ll ksm(ll x,ll k){
  ll res(1);
  while(k){
    if(k&1) res=x*res%mod;
    x=x*x%mod;
    k>>=1;
  }
  return res;
}
ll jc[N],ni[N];
ll f[N],sum[N];
inline ll C(ll n,ll m){
  return jc[n]*ni[m]%mod*ni[n-m]%mod;
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();k=read();
  jc[0]=1;
  for(int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
  ni[n]=ksm(jc[n],mod-2);
  for(int i=n-1;i>=0;i--) ni[i]=ni[i+1]*(i+1)%mod;
  f[0]=1;sum[0]=1;
  for(int i=1;i<=n;i++){
    f[i]=jc[i-1]*(sum[i-1]+mod-(i-k>0?sum[i-k-1]:0))%mod;
    sum[i]=(sum[i-1]+f[i]*ni[i])%mod;
  }
  ll ans(0);
  for(int i=1;i<=n;i++){
    (ans+=f[i-1]*C(n-1,i-1)%mod*jc[n-i]%mod)%=mod;
  }
  printf("%lld\n",(jc[n]+mod-ans)%mod);
  return 0;
}
/*
*/
```



---

## 作者：chihik (赞：5)

我们只关心元素的大小关系，并且是排列计数(即元素不同)，所以任意一个子序列都可看作一个排列。

令 $f_i$ 表示 $1 \sim i$ 的所有排列，没有中途退出的排列数。（这个返回值应该是 $i$ ）

显然满足要求的排列的最大值 $i$ 的位置只能在 $[i-k+1,i]$ , 不妨枚举这个位置

那么有：

$$\begin{aligned}
f_i&=\sum_{j=i-k+1}^i \binom{i-1}{j-1}f_{j-1} (i-j)! \\
 &=\sum_{j=i-k+1}^i f_{j-1} \frac{(i-1)!}{(j-1)!} \\
 &=(i-1)!\sum_{j=i-k}^{i-1} \frac{f_j}{j!}
\end{aligned}$$

维护长度为 $k$ 的 $\frac{f_i}{i!}$ 的值的和，便可以 $\mathcal O(n)$ 推出 $f$。

现在再考虑如何计算答案，显然我们可以用总排列数减去返回值为 $n$ 的排列数。

同样我们可以枚举 $n$ 的位置，那么我们只需要保证 $n$ 之前没有返回即可，答案即为

$$\sum_{i=1}^n \binom{n-1}{i-1}f_{i-1}(n-i)!$$

最后用 $n!$ 减去上面的答案即可。

```cpp
#include <cstdio>

const int MAXN = 1e6 , Mod = 1e9 + 7;
int Add( int x , int y ) { x += y; return x >= Mod ? x - Mod : x; }
int Sub( int x , int y ) { x -= y; return x < 0 ? x + Mod : x; }
int Mul( int x , int y ) { return 1ll * x * y % Mod; }
int Qkpow( int x , int po ) { int Ans = 1; for( ; po ; po >>= 1 , x = Mul( x , x ) ) if( po & 1 ) Ans = Mul( Ans , x ); return Ans; } 
int Inv( int x ) { return Qkpow( x , Mod - 2 ); }
int fac[ MAXN + 5 ] , ivf[ MAXN + 5 ];
void Init() {
	fac[ 0 ] = 1;
	for( int i = 1 ; i <= MAXN ; i ++ ) fac[ i ] = Mul( fac[ i - 1 ] , i );
	ivf[ MAXN ] = Inv( fac[ MAXN ] );
	for( int i = MAXN ; i >= 1 ; i -- ) ivf[ i - 1 ] = Mul( ivf[ i ] , i );
}
int C( int n , int m ) { return n < m ? 0 : Mul( fac[ n ] , Mul( ivf[ m ] , ivf[ n - m ] ) ); }

int n , k , f[ MAXN + 5 ] , s;
int main( ) {
	Init();
	scanf("%d %d",&n,&k);
	
	f[ 0 ] = 1; s = 1;
	for( int i = 1 ; i <= n ; i ++ ) {
		f[ i ] = Mul( fac[ i - 1 ] , s );
		s = Add( s , Mul( f[ i ] , ivf[ i ] ) );
		if( i - k >= 0 ) s = Sub( s , Mul( f[ i - k ] , ivf[ i - k ] ) );
	}
	
	int Ans = fac[ n ];
	for( int i = 1 ; i <= n ; i ++ ) Ans = Sub( Ans , Mul( C( n - 1 , i - 1 ) , Mul( f[ i - 1 ] , fac[ n - i ] ) ) );
	printf("%d\n", Ans );
	return 0;
}
```

---

## 作者：N2MENT (赞：3)

[my blog](https://www.cnblogs.com/0x0620AF/articles/CF886E.html)

[CF886E](https://www.luogu.com.cn/problem/CF886E)

模拟赛出来这道，自己写出来了，虽然花了挺久的，开心！开心！

---

首先看到 $n\leq10^6$ 不是线性 dp 就是数学。

---

数往后 $k$ 个数小于自己实在是太蠢了，不好计数，但是反过来，输出正确答案的情况十分优美。

输出正确的情况大致可以抽象为这样一个形式，对于一个原序列的上升子序列 $S$， $S$ 的相邻两项之间的数小于它们，子序列最后一项后面的数也小于它，并且子序列的相邻两项在原列的位置之差不超过 $k$。

![](https://cdn.luogu.com.cn/upload/image_hosting/7dyoq9cd.png)



现在随便胡一个二维状态应该可以做到 $O(n^3)$ 或者 $O(n^2)$，可是 $n\leq 10^6$，考虑设一维状态。

由于题目要求是一个序列，所以我们不关心一个数实际的大小，我们只关心相对大小，我们可以设一个状态 $f_i$ 表示对于一个 $n = i$ 的数列， 我们钦定最后一个数是 $n$，满足上述条件的方案数。转移可以枚举一个转移点，然后把新增的数插板插进原数列中，即： 

$$f_i = \sum_{j = \max(1, i - k)}^{i - 1} f_j \binom{i - 2}{j - 1}(i - j - 1)!$$

简单拆一下：

$$f_i = \sum_{j = \max(1, i - k)}^{i - 1} f_j \dfrac{(i - 2)!}{(j - 1)!(i - j - 1) !}(i - j - 1)!$$
$$f_i = (i - 2)!\sum_{j = \max(1, i - k)}^{i - 1}  \dfrac{f_j}{(j - 1)!}$$

前缀和优化转移即可。

答案只需要枚举 $n$ 在哪个位置，然后乘上 $n$ 后面的数带来的贡献，即：

$$ans = n! - \sum_{i = 1}^{n} f_i \binom{n - 1}{i - 1}(n - i)$$

~~我真聪明。~~

code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
ll Pow(ll a, ll b, ll mod) {
	ll res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod, b >>= 1;
	}
	return res;
}
int f[maxn];
int pre[maxn];
int fac[maxn];
int ifac[maxn];
int C(int n, int m) {
	return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int n, k;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	ifac[0] = fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod; 
	ifac[n] = Pow(fac[n], mod - 2, mod);
	for(int i = n - 1; i; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
	f[1] = 1;
	pre[1] = 1;
	for(int i = 2; i <= n; i++) {
		int l = max(1, i - k);
		f[i] = 1ll * fac[i - 2] * ((1ll * pre[i - 1] - pre[l - 1] + mod) % mod) % mod;
		pre[i] = (pre[i - 1] + 1ll * f[i] * ifac[i - 1] % mod) % mod;
	}
	int ans = 0;
	for(int i = n; i >= 1; i--) {
		ans = ans + 1ll * f[i] * fac[n - i] % mod * C(n - 1, i - 1) % mod;
		ans %= mod;
	}
	cout << (fac[n] - ans + mod) % mod;
}
```

---

## 作者：JWRuixi (赞：2)

这是一道很好的组合题，可以锻炼组合思维和推式子能力。

- 题意

给定长度为 $n$ 的排列 $a$，问有多少个不同的排列满足不存在一个非最大值比之后的连续 $k$ 个数大。

- 分析

看似没有头绪，那就我脑动规！！！

设 $f_i$ 表示 $i$ 个数的排列，有多少个没有退出的答案。

考虑最大值只能出现在后 $k$ 位，我现在钦定最大值 $i$ 出现在第 $j$ 位，则我可以视前 $j$ 位为一个排列，后 $i - j$ 位自由组合，由此得到状态转移方程：

$$f_i=\sum\limits_{j=i-k+1}^{i} \binom{i-1}{j-1} f_j (i-j)! $$

考虑拆开组合数，转换成阶乘定义方式，即：

$$f_i=\sum\limits_{j=i-k+1}^{i} \frac{(i-1)!}{(i-j)!(j - 1)!}f_j(i-j)!$$

so

$$f_i=(i-1)!\sum\limits_{j=i-k+1}^{i} \frac{f_j}{j!}$$

于是维护一个前缀和，$O(n)$ 搞定 $f$。

此时考虑统计答案，答案其实就是在长度为 $n$ 的排列中做同样的操作。

同时记得，这里统计的是正确的答案，容斥一下还要加个减号，即：

$$n! - \sum\limits_{i=1}^{n}f_{i-1} \binom{n-1}{i-1} (n-i)!$$

- code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn = 1e6 + 500, mod = 1e9 + 7;
int n, k, f[maxn], s, inv[maxn], fac[maxn], ifac[maxn], sum;

inline int c (int i, int j) {
	return fac[i] * ifac[i - j] % mod * ifac[j] % mod;
}

signed main () {
	n = read(), k = read();
	inv[1] = fac[0] = ifac[0] = 1;
	for (int i = 2; i <= n; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod, ifac[i] = ifac[i - 1] * inv[i] % mod;
	f[0] = s = 1;
	for (int i = 1; i <= n; i++) {
		f[i] = s * fac[i - 1] % mod;
		s = (s + f[i] * ifac[i] % mod) % mod;
		if (i - k >= 0) s = (s - f[i - k] * ifac[i - k] % mod + mod) % mod;
	}
	for (int i = 1; i <= n; i++) sum = (sum + f[i - 1] * c(n - 1, i - 1) % mod * fac[n - i] % mod) % mod;
	write((fac[n] - sum + mod) % mod);
}
```

---

## 作者：Lynkcat (赞：2)

看不懂题解里那些柿子是怎么推出来的。讲一下我自己不同于题解的思考方式，但是两者殊途同归，代码部分大体一致。

考虑 $f_i$ 表示长度为 $i$ 的以 $i$ 为最大值的每个位置后面不出现连续 $k$ 个小于它的排列数量，注意，这时候我们仅仅考虑前面这些数的相对关系。

接下来考虑从 $f_i$ 转移到 $f_j$，这时候我们强制转移的时候 $i+1\sim j-1$ 的数均小于 $i$ 和 $j$ 位置上最终填的数。

首先显然 $j-i-1<k$ 时才能转移。

中间的数在计算的时候考虑将这个数插进去能插在哪个位置，假设前面有 $k$ 个数，根据条件这个数要小于最大值，所以答案 $\times k$，然后 $k++$。

而第 $j$ 个数前面没有一个数可能大于他了，所以他只有唯一的一种选择是成为最大值。

所以我们最终发现这个转移系数是一个差为 $1$ 的递增数列的乘积，把它拆成 $\frac{fac_j}{fac_i}$ 的形式之后就可以前缀和优化转移了。

算完这个了，我们可以枚举最终 $n$ 在位置 $i$ ，那么 $\text{ans}=n$ 的排列要满足前面每个位置后面不出现连续 $k$ 个小于它，并且发现剩下的数也能够考虑插进去的方案数。所以类似的，$f_i$ 对答案的贡献的系数也是一个差为 $1$ 的递增数列的乘积。

时间复杂度 $O(n)$。

```c++
//The Hunting Party - Keys To The Kingdom
//好想做嘉然小姐的狗啊~
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 1000000007
#define int ll
#define N 2000005
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,m,fac[N],inv[N];
int f[N];
int s[N];
int ans;
int quickPower(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
void What_will_Diana_eat_today()
{
	n=read(),m=read();
	fac[0]=1;
	for (int i=1;i<=n;i++)
	{
		fac[i]=fac[i-1]*i%mod;
	}
  	inv[n]=quickPower(fac[n],mod-2);
   	for (int i=n;i>=1;i--) inv[i-1]=inv[i]*i%mod;
	f[1]=1;
	for (int i=1;i<n;i++)
	{
		s[i]=(s[i-1]+f[i]*inv[i-1]%mod)%mod;
		int x=i-m;
		if (x<0) x=0;
		f[i+1]=f[i+1]+fac[i-1]*(s[i]-s[x]+mod)%mod;
		f[i+1]=(f[i+1])%mod;
	}
	for (int i=1;i<=n;i++) ans=(ans+f[i]*(fac[n-1]*inv[i-1]%mod)%mod)%mod;
	writeln((fac[n]-ans+mod)%mod);
	
}
signed main()
{
	int T=1;
	while (T--)
	{
	 	  What_will_Diana_eat_today();
	}
}
/*
*/
```

---

## 作者：A_Pikachu (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF886E)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-xie-cf886e-maximum-element)）

$\Large\mathscr{Part\,\,1\;\;}\text{基本思路}$

定义通过执行代码能得出正确答案的序列为合法的，反之为不合法的。不难发现，通过截取一个合法序列得到的连续子序列依旧是合法的，设合法的长度为 $x$ 的**排列**个数为 $f[x]$。

考虑通过长度为 $x$ 的合法**排列**唯一推出长度为 $y$ 的合法**排列**。先考虑数 $y$ 在排列中的位置。如果它在 $(x+1)$ 位以前或以后，那么 $y$ 以前的子序列也是合法的，就会出现由两个合法排列推出同一排列的情况，故只考虑 $y$ 在第 $(x+1)$ 位。又因为如果 $y \gt x+k$，那么将前 $(x+k)$ 个数构成的子序列按相对大小变成排列后一定也是合法的，也会出现二推一的重复情况，故也不考虑。

现在先以长度为 $x$ 的排列为相对大小，在 $(y-1)$ 个数中确定一个序列，共 $\dbinom{y-1}{x}$ 种方案。再将剩下的 $(y-x-1)$ 个数在第 $(x+1)$ 位后任意排列，共 $(y-x-1)!$ 种方案，总计对 $f[y]$ 贡献 $f[x] \times \dbinom{y-1}{x} \times (y-x-1)!$

那么长度为 $n$ 的合法排列一样可以拆分成长度为 $x$ 的合法排列（代表前 $x$ 个数的相对大小）和数 $n$ 以及 $(n-x-1)$ 个任意数。所以长度为 $n$ 的合法序列总数为 $\displaystyle\sum_{x=0}^{n-1} f[x] \times \dbinom{n-1}{x} \times (n-x-1)!$，用 $n!$ 减去即为不合法的序列总数。

这里时间复杂度瓶颈在于求解 $f$ 数组。虽说可以利用线段树实现区间加上等比数列在 $\Theta(n \log n)$ 时间内得到最终数组，但实际上将原式改写成累加式可以得到：

$$\begin{aligned} f[y]&=\displaystyle\sum_{x=y-k}^{y-1} f[x] \times \dbinom{y-1}{x} \times (y-x-1)! \\ &= \displaystyle\sum_{x=y-k}^{y-1} f[x] \times \frac{(y-1)!}{(y-x-1)!\ x!} \times (y-x-1)! \\ &= (y-1)! \displaystyle\sum_{x=y-k}^{y-1} \frac{f[x]}{x!} \end{aligned}$$

那么只需要维护 $\frac{f[x]}{x!}$ 的前缀和就可以 $\Theta(n)$ 推出 $f$ 数组，即可求出答案。

$\Large\mathscr{Part\,\,2\;\;}\text{Code}$

```cpp
#include <cstdio>
const int N=1e6+5,MOD=1000000007;
int n,k,ans,inv[N],fac[N],f[N];
int C(int x,int y){return 1LL*fac[x]*inv[x-y]%MOD*inv[y]%MOD;}
int main(){
	scanf("%d%d",&n,&k);
	inv[0]=inv[1]=f[0]=fac[1]=fac[0]=1;
	for(int i=2; i<=n; i++) inv[i]=(-1LL*inv[MOD%i]*(MOD/i)%MOD+MOD)%MOD;
	for(int i=2; i<=n; i++) inv[i]=1LL*inv[i-1]*inv[i]%MOD,fac[i]=1LL*fac[i-1]*i%MOD;
	ans=fac[n-1];
	for(int i=1; i<n; i++){
		f[i]=1LL*fac[i-1]*((f[i-1]-(i-k-1>=0?f[i-k-1]:0)+MOD)%MOD)%MOD;
		ans=(ans+1LL*f[i]*C(n-1,i)%MOD*fac[n-i-1]%MOD)%MOD;
		f[i]=(1LL*f[i]*inv[i]%MOD+f[i-1])%MOD;
	}
	printf("%d\n",(fac[n]-ans+MOD)%MOD);
	return 0;
}
```

时间复杂度 $\Theta(n)$。

---

## 作者：liaiyang (赞：1)

我们设 $f_i$ 为对于 $1\sim i$ 的排列可以完整运行一遍的排列数。

如果在结尾时 $k$ 刚好用完而结束运行的话，就不能算在 $f_i$ 里。

我们如果想要知道 $f_i$ 的话，最大值 $n$ 必须在 $i-k+1\sim i$ 之间。

假设最大值在第 $i-k+1 \leq j \leq n$ 个位置，那么我们要保证 $1\sim j-1$ 可以完整运行，后面的 $j+1\sim n$ 个随便排就行。

我们并不关心前面具体的数值，只关心前面的大小关系，所以前面的方案数就是 

$$
\binom{i-1}{j-1}f_{j-1}
$$

所以此时它对于 $f_i$ 的贡献是 

$$
\binom{i-1}{j-1}f_{j-1}(i-j)!
$$

所以 $f_i$ 就是

$$
\sum_{j=i-k+1}^{i}\binom{i-1}{j-1}f_{j-1}(i-j)!
$$

$$

=\sum_{j=i-k+1}^{i}\frac{(i-1)!}{(i-j)!(j-1)!}f_{j-1}(i-j)!
$$

$$

=\sum_{j=i-k+1}^{i}\frac{(i-1)!}{(j-1)!}f_{j-1}
$$

$$

=(i-1)!\sum_{j=i-k+1}^{i}\frac{f_{j-1}}{(j-1)!}
$$

$$

=(i-1)!\sum_{j=i-k}^{i-1}\frac{f_j}{j!}
$$

对于右边的和我们可以边算 $f_i$ 边维护前缀和。

答案就是最大值放在任意位置，前面保证不退出，后面随便排的方案数。

$$
ans=\sum_{i=1}^{n}\binom{n-1}{i-1}f_{i-1}(n-i)!
$$

$$
=\sum_{i=1}^{n}\frac{(n-1)!}{(n-i)!(i-1)!}f_{i-1}(n-i)!
$$

$$
=\sum_{i=1}^{n}\frac{(n-1)!}{(i-1)!}f_{i-1}
$$

$$
=(n-1)!\sum_{i=1}^{n}\frac{f_{i-1}}{(i-1)!}
$$

$$
=(n-1)!\sum_{j=0}^{n-1}\frac{f_i}{i!}
$$

右边已经前缀和处理过了，所以不用再次计算。

时间复杂度 $O(n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define modd(x) (((x)%mod+mod)%mod)
#define P pair<int,int>
#define all(a) a.begin(),a.end()
#define x first 
#define y second 
const int inf=~0U>>1;
const int linf=~0ULL>>1;
const int mod=1e9+7;
const int N=1e6+10;
int n,k;
int fac[N],inv[N],sum[N],f[N];
int power(int x,int k){
	int res=1;
	while(k){
		if(k&1) res=res*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return res;
}
main(){
	IOS
	cin>>n>>k;
	fac[0]=1;f[0]=1; 
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	inv[n]=power(fac[n],mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++){
		if(i<=k) f[i]=fac[i];
		else f[i]=fac[i-1]*(sum[i-1]-sum[i-k-1]+mod)%mod;
		sum[i]=(sum[i-1]+f[i]*inv[i]%mod)%mod;	
	}
	cout<<modd(fac[n]-fac[n-1]*(sum[n-1]+1)%mod)<<endl;
	return 0;
} 
```

---

## 作者：oisdoaiu (赞：1)

*tag:计数dp*

---
~~经典看完dp定义秒懂~~

考虑算出满足条件的再用总数减。若一个排列满足条件，那么就不能在遇到 $a_i=n$ 之前返回。所以只需要考虑 $a_i=n$ 前面的部分。

为什么使用dp？若一个排列扫完之后没有返回，那么单独把这个排列的任何一段区间拿出来扫，都不会返回，并且拿出来的这个区间可以看作一个 $[1,len]$ 的排列。设 $f_i$ 为长度为 $i$ 的满足条件的排列个数。

---
那么答案就是：
$$
ans=\sum_{i=1}^nf_{i-1}\binom {n-1}{n-i}(n-i)!
$$

枚举 $n$ 所在位置 $i$，$[1,i-1]$ 的方案为 $f_{i-1}$，$[i+1,n]$ 的方案为 $(n-i)!$，选数的方案为 $\binom{n-1}{n-i}$。

---
考虑转移，要使得递归到子问题时，这个子问题只与区间长度有关系。考虑枚举 $mx$ 的位置，因为扫完排列后没有返回，所以 $mx$ 的位置一定在 $[len-k,len]$，于是就可以递归下去了。
$$
f_x = \sum_{i=x-k}^xf_{i-1}\binom{x-1}{x-i}(x-i)!
$$

枚举 $mx$ 的位置 $i$，$[1,i-1]$ 为 $f_{i-1}$，$[i+1,len]$ 为 $(x-i)!$，选数为 $\binom{x-1}{x-i}$。

---
简单化简一下：
$$
f_x=(x-1)!\sum_{i=x-k-1}^{x-1}\frac{f_{i-1}}{(i-1)!}
$$
和式部分可以直接用一个 $sum$ 变量维护着走（去头添尾），于是复杂度 $O(n)$

---
```cpp
#include<bits/stdc++.h>
using namespace std;

template<typename T>
inline void Read(T &n){
	char ch; bool flag=false;
	while(!isdigit(ch=getchar())){if(ch=='-')flag=true;}
	for(n=ch^48; isdigit(ch=getchar()); n=(n<<1)+(n<<3)+(ch^48));
	if(flag) n=-n;
}

enum{
	MAXN = 1000005,
	MOD = 1000000007
};

inline int dec(int a, int b){
	a -= b;
	if(a<0) a += MOD;
	return a;
}

inline void ddec(int &a, int b){a = dec(a,b);}

int n, k;
int f[MAXN], sum, inv[MAXN], jc[MAXN], ans;

inline int C(int n, int m){return 1ll*jc[n]*inv[m]%MOD*inv[n-m]%MOD;}

int main(){
	Read(n); Read(k);
	inv[1] = 1; for(register int i=2; i<=n; i++) inv[i] = 1ll*(MOD-MOD/i)*inv[MOD%i]%MOD;
	inv[0] = 1; for(register int i=2; i<=n; i++) inv[i] = 1ll*inv[i]*inv[i-1]%MOD;
	jc[0] = 1; for(register int i=1; i<=n; i++) jc[i] = 1ll*jc[i-1]*i%MOD;
	sum = 1; f[0] = 1;
	for(register int i=1; i<=n; i++){
		f[i] = 1ll*sum*jc[i-1]%MOD;
		if(i-k>=0) ddec(sum,1ll*f[i-k]*inv[i-k]%MOD);
		sum = (sum+1ll*f[i]*inv[i])%MOD;
		ans = (ans+1ll*f[i-1]*C(n-1,n-i)%MOD*jc[n-i])%MOD;
	}
	cout<<dec(jc[n],ans)<<endl;
	return 0;
}
```

---

## 作者：SUNCHAOYI (赞：0)

正难则反，考虑长度为 $i$ 的排列得到正确的结果的方案数。

设 $dp_i$ 表示长度为 $i$ 的排列直到循环完也没有提前 `return` 的方案数。考虑 $i$ 所放置的位置，由于不会提前 `return`，也就说明该数字所在的位置为 $[i - k + 1,i]$ 的范围中。因此可以枚举 $i$ 的位置为 $j$，则相当于将 $[1,i]$ 的区间分为 $[1,j - 1],[j],[j + 1,i]$。

第一段为 $i - 1$ 个数字中选择 $j - 1$ 个，也就是 $\binom{i-1}{j-1}$，然后合法的方案数为 $dp_{j - 1}$；第二段放最大值 $i$，第三段还剩下 $i - j$ 个数字，随意放置，也就是 $(i - j)!$。虽然说 $dp_i$ 的状态考虑的是排列，但是显然我们只需要考虑数字之间的**相对大小**，因此第一段的方案数是合理的。可以得到以下转移：

$$dp_i=\sum_{j=i-k+1}^i \binom{i-1}{j-1}\times dp_{j-1}\times (i-j)!$$

尝试进行化简，可以得到：

$$
dp_i = \sum_{j=i-k+1}^i \frac{(i - 1)!}{(j - 1)! \times ((i - 1) - (j - 1))!}\times dp_{j-1}\times (i-j)! \\
= \sum_{j=i-k+1}^i\frac{(i - 1)!}{(j - 1)!} \times dp_{j - 1} \\
= (i - 1)! \times \sum_{j=i-k}^{i - 1} \frac{dp_j}{j!}
$$

维护一段长度为 $k$ 的 $\frac{dp_i}{i!}$ 的和即可 $O(n)$ 求出 $dp_i$。

最后再考虑答案。若最后求得的答案是正确的，我们只需要枚举 $n$ 所在的位置即可。因此总共合法的方案数为：

$$
ans = \sum_{i = 1}^n \binom {n - 1}{i - 1} \times dp_{i - 1} \times (n - i)!
$$

最后的答案就是 $n!-ans$。代码如下：

```cpp
#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define pii pair <int,int>
using namespace std;
const int MAX = 1e6 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,k;ll tot,sum,dp[MAX],f[MAX],inv[MAX];
ll qpow (ll x,ll y)
{
    ll res = 1;
    while (y)
    {
        if (y & 1) res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}
int main ()
{
    n = read ();k = read ();
    inv[0] = f[0] = 1;
    for (int i = 1;i <= n;++i) f[i] = f[i - 1] * i % MOD;
    inv[n] = qpow (f[n],MOD - 2);
    for (int i = n - 1;i;--i) inv[i] = inv[i + 1] * (i + 1) % MOD;
    dp[0] = sum = 1;
    for (int i = 1;i <= n;++i)
    {   
        dp[i] = f[i - 1] * sum % MOD;
        sum = (sum + dp[i] * inv[i] % MOD) % MOD;
        if (i >= k) sum = (sum - dp[i - k] * inv[i - k] % MOD + MOD) % MOD;
    }
    for (int i = 1;i <= n;++i) tot = (tot + dp[i - 1] * f[n - 1] % MOD * inv[i - 1] % MOD) % MOD;
    printf ("%lld\n",(f[n] - tot + MOD) % MOD);
    return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
    {
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：ax_by_c (赞：0)

考虑用 $n!$ 减去返回值为 $n$ 的排列个数，即 $n$ 前面扫完后没有返回的排列个数。

设 $f_i$ 为 $i$ 个数没有返回且下一个 max 刷新的排列个数，转移考虑枚举最大值位置 $j$，则 $f_i=\sum_{j=\max(i-k+1,1)}^{i}f_{j-1}\binom{i-1}{i-j}(i-j)!=\sum_{j=\max(i-k+1,1)}^{i}\frac{f_{j-1}(i-1)!}{(j-1)!}=(i-1)!\sum_{j=\max(i-k+1,1)}^{i}\frac{f_{j-1}}{(j-1)!}$。

对 $\frac{f_i}{i!}$ 计算前缀和即可优化，时间复杂度 $O(n)$。

枚举 $n$ 的位置 $i$，则答案为 $\sum_{i=1}^{n}f_{i-1}\binom{n-1}{i-1}(n-i)!$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=1e9+7;
const int N=1e6+5;
ll ksm(ll a,ll b,ll p){
	a=a%p;
	ll r=1;
	while(b){
		if(b&1)r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r%p;
}
ll fac[N],inv[N];
void Init(int n){
	fac[0]=1;
	rep(i,1,n)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2,mod);
	per(i,n,1)inv[i-1]=inv[i]*i%mod;
}
ll C(int n,int m){
	if(n<m||n<0||m<0)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int n,k;
ll f[N],s[N];
void slv(){
	scanf("%d %d",&n,&k);
	Init(n);
	f[0]=1;
	s[0]=1;
	rep(i,1,n){
		f[i]=s[i-1];
		if(i-k>0)f[i]=(f[i]-s[i-k-1]+mod)%mod;
		f[i]=f[i]*fac[i-1]%mod*inv[i]%mod;
		s[i]=(s[i-1]+f[i])%mod;
	}
	rep(i,0,n)f[i]=f[i]*fac[i]%mod;
	ll ans=0;
	rep(i,1,n)ans=(ans+f[i-1]*C(n-1,i-1)%mod*fac[n-i]%mod)%mod;
	printf("%lld\n",(fac[n]-ans+mod)%mod);
}
void main(){
	int T=1;
//	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Claire0918 (赞：0)

首先，我们只关心数的大小关系，所以具体的数值不重要，从而我们不要求序列一定是排列，只须是互不相同的数。

题目中给出的代码有两处可以返回。我们记 $f_i$ 表示长度为 $i$ 的任两数互不相同的可以在最后一处返回的序列数量。特别的，$f_0 = 1$。转移时枚举最大值的位置 $j \in (\max\{0, i - k\}, i]$，有 $f_i = \sum_{j = \max\{1, i - k + 1\}}^{i} f_{j - 1} \times {i - 1 \choose i - j} \times (i - j)!$。其中 ${i - 1 \choose i - j} \times (i - j)!$ 的意义是在除最大值之外的 $i - 1$ 个数中选择 $i - j$ 个填在位于 $(j, i]$ 的位置中的方案数。

暴力转移显然无法通过，考虑化简式子。
$$
\begin{aligned}
f_i
&= \sum_{j = \max\{1, i - k + 1\}}^{i} f_{j - 1} \times {i - 1 \choose i - j} \times (i - j)!\\
&= \sum_{j = \max\{1, i - k + 1\}}^{i} f_{j - 1} \times \frac{(i - 1)!}{(i - j)!(j - 1)!} \times (i - j)!\\
&= \sum_{j = \max\{1, i - k + 1\}}^{i} f_{j - 1} \times \frac{(i - 1)!}{(j - 1)!}\\
&= (i - 1)! \times \sum_{j = \max\{0, i - k\}}^{i - 1} \frac{f_j}{j!}\\
\end{aligned}
$$
维护前缀和 $\displaystyle s_i = \sum_{j = 0}^{i - 1} \frac{f_j}{j!}$ 即可单次 $\mathcal{O}(1)$ 转移。

我们发现问题中函数返回值正确，当且仅当在 $n$ 出现之前没有返回。枚举 $n$ 在序列中的位置 $i \in [1, n]$，得到返回值正确的序列数量
$$
\begin{aligned}
\sum_{i = 1}^{n} f_{i - 1} \times {n - 1 \choose n - i} \times (n - i)!
&= \sum_{i = 1}^{n} f_{i - 1} \times \frac{(n - 1)!}{(n - i)!(i - 1)!} \times (n - i)!\\
&= (n - 1)! \times \sum_{i = 1}^{n} \frac{f_{i - 1}}{(i - 1)!}\\
&= (n - 1)! \times s_{n}\\
\end{aligned}
$$
序列一共有 $n!$ 个，所以返回值错误的序列有 $n! - (n - 1)! \times s_{n}$ 个。

时间复杂度为转移复杂度 $\mathcal{O}(n)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 1e6 + 10, mod = 1e9 + 7;

int n, k;
int fac[maxn], ifac[maxn], pre[maxn];

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

inline long long ksm(long long a, long long b){
    long long res = 1;
    while (b){
        if (b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline long long inv(long long x){
    return ksm(x, mod - 2);
}

int main(){
    scanf("%d %d", &n, &k);
    fac[0] = 1;
    for (int i = 1; i <= n; i++){
        fac[i] = (long long)fac[i - 1] * i % mod;
    }
    ifac[n] = inv(fac[n]);
    for (int i = n - 1; ~i; i--){
        ifac[i] = (long long)ifac[i + 1] * (i + 1) % mod;
    }
    pre[1] = 1;
    for (int i = 1; i < n; i++){
        pre[i + 1] = mod_add(pre[i], (long long)fac[i - 1] * mod_add(pre[i], mod - pre[max(0, i - k)]) % mod * ifac[i] % mod);
    }
    printf("%d", mod_add(fac[n], mod - (long long)fac[n - 1] * pre[n] % mod));

return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑枚举最大值的位置 $p$，相当于从 $n-1$ 个数中选 $p-1$ 个放到 $p$ 前面，后面 $n-1-p$ 个随意放，再乘上 $[1,p-1]$ 任意排列使得其中一定能触发题目给定的最大值判定的方案数。

不难发现，假若没有触发最大值判定，那么任何一个数其右边小于其的数一定不大于等于 $k$ 个，也就是建立笛卡尔树之后，不存在一个点的右子树大小大于等于 $k$，不妨直接令 $dp_i$ 表示大小为 $i$ 的笛卡尔树填排列的方案，有 $dp_{i} = \sum_{j=0}^{min(i-1,k-1)} dp_j \times dp_{i-j-1} \times {i-1 \choose j}$，注意到 $i < k$ 时 $dp_i = i!$，所以可以写成 $dp_{i} = \sum_{j=0}^{min(i-1,k-1)} j! \times dp_{i-j-1} \times {i-1 \choose j}$，再化简下就是 $dp_{i} = \sum_{j=0}^{min(i-1,k-1)} dp_{i-j-1} \times (i-1)! \times \frac{1}{(i-j-1)!}$ 也就是 $dp_i = (i-1)! \sum_{j=0}^{min(i-1,k-1)} dp_{i-j-1} \times \frac{1}{(i-j-1)!}$，记录下 $dp_{i-j-1} \times \frac{1}{(i-j-1)!}$ 的前缀和即可做到 $O(n \log mod)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
int qpow(int a,int b){
	if(b==0) return 1;
	if(b==1) return a;
	int res=qpow(a,b/2);
	res=res*res%mod;
	if(b%2==1) res=res*a%mod;
	return res;
}
const int maxn = 1e6+114;
int fac[maxn];
int dp[maxn];//长度为 i 的排列，建立的笛卡尔树右子树大小不大于 k 的方案 
int pre[maxn];
int n,k;
int ans;
int C(int n,int m){
	if(m>n) return 0;
	return fac[n]*qpow(fac[m],mod-2)%mod*qpow(fac[n-m],mod-2)%mod;
}
signed main(){
	cin>>n>>k;
	fac[0]=1;
	for(int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod;
	dp[0]=1;
	pre[0]=1;
	for(int i=1;i<=n;i++){
		if(i-k-1>=0) dp[i]=(pre[i-1]+mod-pre[max(0*1ll,i-k-1)])%mod;
		else dp[i]=pre[i-1];
		dp[i]=dp[i]*fac[i-1]%mod;
		pre[i]=(pre[i-1]+dp[i]*qpow(fac[i],mod-2)%mod)%mod;
	}
	for(int i=0;i<n;i++){
		int res=C(n-1,i)*fac[n-1-i]%mod;
		int cnt=(fac[i]+mod-dp[i])%mod;
		ans=(ans+cnt*res%mod)%mod;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：ncwzdlsd (赞：0)

DP+推柿子。

性质：对于一个序列，返回值是正确的，当且仅当出现 $n$ 之前还没有返回值。

设 $f_i$ 表示长度为 $i$ 且直到最后也没有返回值的序列数量，考虑如何计算 $f_i$。

枚举序列最大值 $i$ 所在的位置 $j$，由于不能有返回值，所以 $j$ 一定在区间 $[i-k+1,i]$ 中。对于位置 $j$ 后面的情况，从 $i-1$ 个数里选择 $i-j$ 个数，方案数为 $\binom{i-1}{j-1}$，对其求排列的方案数乘上 $(i-j)!$ 即可。位置 $j$ 前面的方案数为 $f_{j-1}$。

所以，

$$
\begin{aligned}
f_i&=\sum_{j=i-k+1}^i\binom{i-1}{j-1}f_{j-1}(j-i)!\\
&=\sum_{j=i-k+1}^i\frac{(i-1)!}{(j-1)!}f_{j-1}\\
&=(i-1)!\sum_{j=i-k+1}^i\frac{f_{j-1}}{(j-1)!}\\
&=(i-1)!\sum_{j=i-k}^{i-1}\frac{f_{j}}{j!}
\end{aligned}
$$

对于 $\dfrac{f_j}{j!}$ 这部分，考虑使用前缀和预处理，把时间复杂度降为 $O(n)$。预处理阶乘的逆元。

枚举 $i$ 所在的位置，答案即为：

$$
\begin{aligned}
\text{ans}&=n!-\sum_{i=1}^n\binom{n-1}{i-1}f_{i-1}(n-i)!\\
&=n!-\sum_{i=1}^n\frac{f_i}{i}(i-1)!\binom{n-1}{n-i}(n-i)!\\
&=n!-(n-1)!\sum_{i=1}^n\frac{f_i}{i}
\end{aligned}
$$

代码如下，注意取模操作的负数情况：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

const int mod=1e9+7,maxn=1e6+5;
int fac[maxn],inv[maxn],f[maxn],g[maxn];

int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}

int C(int n,int m)
{return fac[n]*inv[m]%mod*inv[n-m]%mod;}

signed main()
{
	int n,k;cin>>n>>k;
	fac[0]=1,f[0]=1,g[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    inv[n]=quickpow(fac[n],mod-2);
    for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod; 
    for(int i=1;i<=n;i++)
	{
		if(i<=k) f[i]=fac[i-1]*(g[i-1]+mod)%mod;
		else f[i]=fac[i-1]*(g[i-1]-g[i-k-1]+mod)%mod;
		g[i]=(g[i-1]+f[i]*inv[i])%mod;
	}
	cout<<(fac[n]-fac[n-1]*g[n-1]%mod+mod)%mod;
	return 0;
}
```



---

## 作者：linyihdfj (赞：0)

## CF886E Maximum Element
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
考虑如果 $n$ 在位置 $i$，那么要使得返回值为 $n$ 也就是前 $i-1$ 个不会返回。

那么假设我们可以得到这么一个值：$f[i]$ 代表 $[1,i]$ 的排列中间没有返回值的方案数。

那么我们最后的答案就是：
$$
\sum_{i=1}^n \binom{n-1}{i-1} f_{i-1} (n-i)!
$$
其实就是枚举一下 $n$ 的位置，前面 $i-1$ 个只需要关注其相对大小关系所以可以看作排列，后 $n-i$ 个随便排都可以，因为显然都一定小于 $n$。

那么 $f$ 数组怎么求呢，其实也是差不多的道理：
$$
f[i] = \sum_{j=i-k+1}^{i}  \binom{i-1}{j-1} f_{j-1} (i-j)!
$$
注意这个下界是 $i-k+1$ 因为我们如果 $i$ 的位置小于 $i-k+1$ 那么因为后面的数一定会小于 $i$，所以至少 $i$ 不会不返回。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6+5;
const int MOD = 1e9+7;
int f[N],fac[N],inv[N];
int mod(int x){
	return ((x % MOD) + MOD)%MOD;
}
int power(int a,int b){
	int res = 1;
	while(b){
		if(b & 1)	res = mod(res * a);
		a = mod(a * a);
		b >>= 1;
	}
	return res;
}
int C(int n,int m){
	if(n < m)	return 0;
	return mod(mod(fac[n] * inv[m]) * inv[n - m]);
}
signed main(){
	int n,k;
	scanf("%lld%lld",&n,&k);
	fac[0] = 1;
	for(int i=1; i<=n; i++)	fac[i] = mod(fac[i-1] * i);
	inv[n] = power(fac[n],MOD-2);
	for(int i=n-1; i>=0; i--)	inv[i] = mod(inv[i+1] * (i + 1));
	f[0] = 1;
	int sum = 1;
	for(int i=1; i<=n; i++){
		f[i] = mod(fac[i-1] * sum);
		sum = mod(sum + f[i] * inv[i]);
		if(i - k >= 0)	sum = mod(sum - f[i-k] * inv[i-k]);
	}
	int ans = fac[n];
	for(int i=1; i<=n; i++){
		ans = mod(ans - mod(C(n-1,i-1) * f[i-1]) * fac[n-i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

