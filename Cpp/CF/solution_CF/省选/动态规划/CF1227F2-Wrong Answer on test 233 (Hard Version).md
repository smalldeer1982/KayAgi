# Wrong Answer on test 233 (Hard Version)

## 题目描述

你的程序又出错了。这一次它在第 $233$ 个测试点上得到了“答案错误”。

这是该问题的更难版本。在本版本中，$1 \le n \le 2\cdot10^5$。如果你锁定了本题，可以对其进行 hack。但只有在你同时锁定了两个问题时，才能 hack 前一个问题。

问题描述如下：你需要完成 $n$ 道单选题。每道题有 $k$ 个选项，且只有一个选项是正确的。第 $i$ 道题的正确答案是 $h_i$，如果你对第 $i$ 道题的作答为 $h_i$，则你获得 $1$ 分，否则该题得 $0$ 分。所有 $h_1, h_2, \dots, h_n$ 在本题中均已知。

然而，你的程序有一个错误。它会将答案顺时针移动一位！假设所有 $n$ 个答案排成一个环。由于程序的错误，它们会循环右移一位。

具体来说，程序会将第 $i$ 道题的答案移动到第 $(i \bmod n) + 1$ 道题的位置。也就是说，第 $1$ 题的答案被移动到第 $2$ 题，第 $2$ 题的答案被移动到第 $3$ 题，……，第 $n$ 题的答案被移动到第 $1$ 题。

我们把所有 $n$ 个答案合起来称为一个“答案序列”。一共有 $k^n$ 种可能的答案序列。

你想知道，有多少个答案序列满足如下条件：经过顺时针移动 $1$ 位后，新答案序列的总得分严格大于原序列的得分。你需要输出满足条件的答案序列数，结果对 $998\,244\,353$ 取模。

例如，若 $n=5$，你的答案序列为 $a=[1,2,3,4,5]$，由于程序错误，提交的答案为 $a'=[5,1,2,3,4]$。若正确答案序列为 $h=[5,2,2,3,4]$，则 $a$ 得 $1$ 分，$a'$ 得 $4$ 分。由于 $4>1$，所以 $a=[1,2,3,4,5]$ 应被计入答案。

## 说明/提示

对于第一个样例，合法的答案序列有 $[2,1,1], [2,1,2], [2,1,3], [3,1,1], [3,1,2], [3,1,3], [3,2,1], [3,2,2], [3,2,3]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
1 3 1
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5 5
1 1 4 2 2
```

### 输出

```
1000
```

## 样例 #3

### 输入

```
6 2
1 1 2 2 1 1
```

### 输出

```
16
```

# 题解

## 作者：wind_whisper (赞：12)

## $\text{Description}$
有 $n$ 道题，你的程序在上交答案时把答案交串了，第 $i$ 个答案变成了第 $i\bmod n+1$ 个.  
给出 $n$ 道题的正确答案以及选项数 $k$ ，求有多少中初始上交的答案，能使交串后正确的题目数变多.  
## $\text{Solution}$
### easy version
$n\le2000,k\le10^9$  
设计 $dp_{i,j}$ 表示填到第 $i$ 题，多填对了 $j$ 道题的方案数.  
暴力转移即可.  
### hard version
$n\le2\times10^5,k\le10^9$  
原来 dp 的做法行不通了，我们需要另辟蹊径.  
设 $f_i$ 表示多对了 $i$ 道题的方案数，由于对称性，有 $f_i=f_{-i}$.  
所以我们的答案其实就是：
$$\dfrac{k^n-f_0}{2}$$
所以我们只需要求出 $f_0$ 就行了.  
连续两个答案相同无法产生差异，我们扫一遍求出有 $m$ 个位置可以产生差异.  
枚举答对（答错）的题目数，则有：
$$f_0=\sum_{i=0}^{\lfloor\frac{m}{2}\rfloor}k^{n-m}\times C_m^i\times C_{m-i}^i\times (k-2)^{m-2i}$$
直接求解即可.
## $\text{Code}$
dp:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2050;
const int mod=998244353;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
ll dp[2][N<<1];
int now,nxt,o=2000,a[N];
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();k=read();
  for(int i=1;i<=n;i++) a[i]=read();
  dp[nxt=1][0+o]=1;
  for(int i=1;i<=n;i++){
    swap(now,nxt);
    memset(dp[nxt],0,sizeof(dp[nxt]));
    for(int j=-i;j<=i;j++){
      if(a[i]==a[i%n+1]) (dp[nxt][j+o]+=dp[now][j+o]*k)%=mod;
      else{
	(dp[nxt][j+1+o]+=dp[now][j+o])%=mod;
	(dp[nxt][j-1+o]+=dp[now][j+o])%=mod;
	(dp[nxt][j+o]+=(k-2)*dp[now][j+o])%=mod;
      }
    }
  }
  ll res(0);
  for(int i=1;i<=n;i++) (res+=dp[nxt][i+o])%=mod;
  printf("%lld\n",res);
  return 0;
}
/*
*/

```
组合数：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
const int mod=998244353;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m,k;
int a[N];
ll ans;
ll ksm(ll x,ll k){
  ll res=1;
  while(k){
    if(k&1) res=res*x%mod;
    x=x*x%mod;
    k>>=1;
  }
  return res;
}
ll jc[N],ni[N],mi[N];
inline ll C(int n,int m){
  return jc[n]*ni[m]%mod*ni[n-m]%mod;
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();k=read();
  if(k==1){
    printf("0");return 0;
  }
  for(int i=1;i<=n;i++) a[i]=read();
  for(int i=1;i<=n;i++) m+=(a[i]!=a[i%n+1]);
  jc[0]=1;
  for(int i=1;i<=m;i++) jc[i]=jc[i-1]*i%mod;
  ni[m]=ksm(jc[m],mod-2);
  for(int i=m-1;i>=0;i--) ni[i]=ni[i+1]*(i+1)%mod;
  mi[0]=1;
  for(int i=1;i<=n;i++) mi[i]=mi[i-1]*(k-2)%mod;
  ans=ksm(k,n);ll w=ksm(k,n-m);
  for(int i=0;i<=m/2;i++) ans=(ans+mod-w*C(m,i)%mod*C(m-i,i)%mod*mi[m-2*i]%mod)%mod;
  ans*=ksm(2,mod-2);ans%=mod;
  printf("%lld\n",ans);
  return 0;
}
/*
*/

```


---

## 作者：Lily_White (赞：5)

*UPD ON 5/2: fix typo*

本质上是一个组合题。

定义$f(n,k)$表示**前$n$位得分差为$k$的方案数**。对它 DP 可以过第一个 Subtask。

要过第二个，我们就要注意到，$f(n, k) = f(n, -k)$。这样，我们可以**算出不变的方案数，用$k^n$减去它，除以$2$即可**。

也即，

$$ans=\frac{k^n-f(n,0)}2$$
问题就变为求出$f(n,0)$的值。而**对于每一题，它可以在旋转后多得$1$分，少得$1$分，或者分数不变。**

注意到**我们不关心实际上的答案是多少，只在乎分数的变化。** 同时，一个测试点可能对总分造成影响，当且仅当它和下一个点正确答案不同，我们记这样的点有$m$个。

对于所有$0 \le i \le \lfloor\frac{m}2\rfloor$，我们认为，加分的题有$C^i_m$种，减分的题有$C_{m-i}^i$种，剩下的题只要对分数没有影响就可以随便填，有$(k-2)^{m-2i}$种。

因此，我们有

$$f(n,0)=\sum_{i=0}^{\lfloor\frac{m}2\rfloor}C^i_mC_{m-i}^i(k-2)^{m-2i}$$
代回上面的式子，我们就得到答案为

$$ans=\frac{k^n-f(n,0)}2=\frac{k^n-\sum_{i=0}^{\lfloor\frac{m}2\rfloor}C^i_mC_{m-i}^i(k-2)^{m-2i}}2$$

计算即可。[Code](https://codeforces.com/contest/1262/submission/65728386)。

---

## 作者：sylqwq (赞：4)

这道题二维 dp 的方法就行不通了。我尝试优化 dp 状态但是失败了（悲），考虑一下奇妙的性质和数学手段。

我做这个题还是基于简单版的式子的。先把式子一放：

设 $f_{i,j}$ 表示填完前 $i$ 个位置，提交答案错位后比原来多对了 $j$ 个题的方案数。

如果 $a_i=a_{(i \bmod n) +1}$，则 $f_{i,j}=f_{i-1,j}\times k$。

否则 $f_{i,j}=f_{i-1,j+1}+f_{i-1,j-1}+f_{i-1,j}\times(k-2)$。

式子很好理解，不懂的话随便去简单版的题解区看一眼就懂了。

有一个性质：$f_{i,j}=f_{i,-j}$。即固定 $i$ 后第二维对称位置相等。尝试用数学归纳的思想证明这个结论，即从 $f_i$ 这一维性质成立推出 $f_{i+1}$ 这一维也成立。

首先考虑 $i=0$，$f_{0,0}=1$，其余值都为 $0$，满足对称性质。

现在假设 $f_i$ 这一维已经成立了，我们推 $f_{i+1}$ 这一维。

先看 $a_i=a_{(i \bmod n) +1}$ 的情况。$f_{i+1,j}=f_{i,j}\times k$ 且 $f_{i+1,-j}=f_{i,-j}\times k$。由于第 $i$ 维满足那个性质，所以 $f_{i,j}=f_{i,-j}$，故 $f_{i+1,j}=f_{i+1,-j}$。

再考虑其余情况。$f_{i+1,j}=f_{i,j+1}+f_{i,j-1}+f_{i,j}\times(k-2)$ 且 $f_{i+1,-j}=f_{i,-j+1}+f_{i,-j-1}+f_{i,-j}\times(k-2)$。由于第 $i$ 维满足性质，所以 $f_{i,j}=f_{i,-j}$，$f_{i,j-1}=f_{i,-j+1}$，$f_{i,j+1}=f_{i,-j-1}$。不难发现，$f_{i+1,j}$ 和 $f_{i+1,-j}$ 还是相等。

于是我们成功证明了 $f_{i,j}=f_{i,-j}$。

我们最后的答案是 $\sum_{i=1}^n f_{n,i}$，结合上面的性质，这个东西其实就是总方案减去 $f_{n,0}$ 再除以 $2$。即：

$$
\frac{k^n-f_{n,0}}{2}
$$

问题变成了填完 $n$ 个位置的数有多少种方案满足错不错位得分一样。这就是一道简单的组合数学题了。有一些位置 $i$ 满足 $a_i=a_{(i \bmod n) +1}$，这些位置可以随便填，因为错不错位这个数对应的正确答案都是一样的，错位和不错位两种情况在该题的正误情况应该相同。计不满足该条件的位置数量为 $m$，这些位置是需要仔细考虑的。

对于这 $m$ 个位置，我们枚举 $i$，表示原来的答案和错位的答案分别有 $i$ 个位置是正确的。我们先从这 $m$ 个位置中挑 $i$ 个位置让原来答案的这一位正确，再从 $m-i$ 个位置中挑 $i$ 个位置让错位答案的这一位正确。还剩 $m-2\times i$ 个位置，这些位置要求原答案和错位答案都错，每位有 $k-2$ 种填法（扣除 $a_i$ 和 $a_{(i\bmod n)+1}$ 两种填法）。于是：

$$
f_{n,0}=k^{n-m}\times \sum_{i=0}^{\left\lfloor\frac{m}{2}\right\rfloor}\times C_{m}^i\times C_{m-i}^i\times (k-2)^{m-2\times i}
$$

代码很好写，不放了。任何疑问欢迎评论区留言，我会尽量及时回复。

---

## 作者：caidzh (赞：3)

怎么你们都用多项式做的啊，这边提供一个清新自然的非多项式做法

要是我$\text{CSP}$之前做了这题$\text{Day2T1}$就肯定会做了，并且不会$\text{FST}$掉那$32$分，可惜啊$\text{/dk/dk}$

首先我们来康康这题的$\text{easy version}$怎么做

显然的想法就是定义$f_{i,j}$为填到第$i$个数，当前填的正确答案个数减去移位后的正确答案个数的值等于$j$的方案数

显然地，我们有一个动态规划的思路：

我们定义一个点$i$移位后的位置为$to$，那么状态转移即为：

$$f_{i,j}+=f_{i-1,j}(h_i=h_{to})$$

$$f_{i,j}+=f_{i-1,j-1}+f_{i-1,j+1}+(k-2)f_{i-1,j}(h_i\ne h_{to})$$

意义显然，这里不多讲了，复杂度$O(n^2)$

然后我们来考虑怎么愉快地切掉这个$\text{hard version}$

由上面的思路，我们可以想到对于$h_i=h_{to}$的点和$h_i\ne h_{to}$的点分开处理，显然$h_i=h_{to}$的点是什么对于差值没有意义，我们不管取什么都不能改变差值，这很好理解，然后我们接下来考虑$h_i\ne h_{to}$的情况

根据上面的转移我们有一个想法，就是说枚举移位后对差值影响为$1$的位置的个数，然后枚举对差值影响为$-1$的位置的个数，接下来我们可以直接减法得出影响为$0$的位置的个数，从而直接表示答案：

我们设$h_i=h_{to}$的点有$a$个，不等的有$b$个，答案为：

$$k^a\times (\sum_{i=0}^bC_{b}^{i}\sum_{j=0}^{i-1}C_{b-i}^{j}(k-2)^{b-i-j})$$

我们考虑怎么计算后面那个玩意儿，看着两项在内层的$\sum$里很不舒服是吗，我们可以把它们提出来，交换求和号！

$$k^a\times (\sum_{i=1}^bC_{b}^{b-i}(k-2)^{b-i}\sum_{j=\frac{i}{2}+1}^iC_{i}^j)$$

后面那个$\sum$只需要奇偶分类讨论一下就可以以$O(1)$的时间得出，前面的暴力枚举计算一下就好，复杂度$O(n)$。下面的代码是我写丑了，复杂度$O(nlogn)$
```cpp
#include<bits/stdc++.h>
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=200010,mod=998244353;
int n,k,a,b,h[maxn],ans,sum,fac[maxn],inv[maxn];
int Pow(int x,int y){
	int ans=1;while(y){if(y&1)ans=1ll*ans*x%mod;x=1ll*x*x%mod;y>>=1;}return ans;
}
int C(int x,int y){return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
int main()
{
	n=read();k=read();
	for(int i=1;i<=n;i++)h[i]=read();
	if(n==1){cout<<0;return 0;}
	for(int i=1;i<=n;i++){
		int to;if(i==n)to=1;else to=i+1;
		if(h[i]==h[to])a++;else b++;
	}ans=Pow(k,a);fac[0]=1;inv[0]=1;
	for(int i=1;i<=b;i++)fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=1;i<=b;i++)inv[i]=Pow(fac[i],mod-2);
	for(int i=1;i<=b;i++){
		int S;if(i&1)S=Pow(2,i-1);
		else S=((1ll*Pow(2,i)*inv[2]%mod-1ll*C(i,i/2)*inv[2]%mod)%mod+mod)%mod;
		sum=(sum+1ll*Pow(k-2,b-i)*C(b,b-i)%mod*S%mod)%mod;
	}cout<<1ll*ans*sum%mod;return 0;
}
```


---

## 作者：Soulist (赞：3)

假设$t$个位置为满足这一位和下一位相同，$r$个位置为不同

则可以知道答案为：

$$m^t\sum_{i=1}^r\sum_{j=0}^{min(i-1,r-i)}\dbinom{r}{i}\dbinom{r-i}{j}\times (m-2)^{r-i-j}$$

于是要特判$m=1$。。。因为认为$0^0=1$所以可以顺便把$m=2$给判掉

$$m^t\sum_{i=1}^r\sum_{j=0}^{min(i-1,r-i)}\dbinom{r}{i}\dbinom{r-i}{j}\times (m-2)^{r-i-j}$$

$$m^t\times r!\sum_{i=1}^r\sum_{j=0}^{min(i-1,r-i)}\dfrac{1}{i!j!(r-i-j)!}\times (m-2)^{r-i-j}$$

容易发现对于一组固定的$i+j=k$，其对于答案的贡献为固定的$\dfrac{(m-2)^{r-k}}{(r-k)!}$

然后就考虑有多少组$i,j$满足$i+j=k$

注意到$k\le i$，所以必然有$i+j\le r$于是原式即要求：

$$m^tr!\sum_{k=1}^{r}\dfrac{(m-2)^{r-k}}{(r-k)!}\sum_{i+j=k}[i>j]\dfrac{1}{i!}\dfrac{1}{j!}$$

由于$[i>j]$的存在它不能普通的直接卷积得到...

然而事实上其相当于减掉了一半，于是特判掉$i=j$之后直接卷积就可以了$...$

然后答案除以$2$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 998244353 ;
const int Gi = 332748118 ;
const int G = 3 ; 
const int N = 2e5 + 5 ; 
const int M = 8e5 + 5 ; 
int n, m, Ans, T, t, h[N], fac[N], inv[N], A[M], R[M], L, Inv, limit ; 
int fpow( int x, int k ) {
	int ans = 1, base = x % P ;
	while( k ) {
		if( k & 1 ) ans = ( ans * base ) % P ;
		base = ( base * base ) % P, k >>= 1 ;
	} return ans ; 
}
void init( int x ) {
	limit = 1, L = 0 ; while( limit < x ) limit <<= 1, ++ L ; 
	rep( i, 0, limit ) R[i] = ( R[i >> 1] >> 1 ) | ( ( i & 1 ) << ( L - 1 ) ) ;
	Inv = fpow( limit, P - 2 ) ;
}
inline void NTT( int *a, int type ) {
	for( re int i = 0; i < limit; ++ i ) if( R[i] > i ) swap( a[i], a[R[i]] ) ; 
	for( re int k = 1; k < limit; k <<= 1 ) {
		int d = fpow( ( type == 1 ) ? G : Gi, ( P - 1 ) / ( k << 1 ) ) ;
		for( re int i = 0; i < limit; i += ( k << 1 ) )
		for( re int j = i, g = 1 ; j < i + k; ++ j, g = ( g * d ) % P ) {
			int Nx = a[j], Ny = ( a[j + k] * g ) % P ; 
			a[j] = ( Nx + Ny ) % P, a[j + k] = ( Nx - Ny + P ) % P ; 
		}
	} 
	if( type != 1 ) for( re int i = 0; i < limit; ++ i ) a[i] = a[i] * Inv % P ; 
}
signed main()
{
	n = gi(), m = gi() ; rep( i, 1, n ) h[i] = gi() ; 
	rep( i, 1, n ) {
		if( h[i] == h[i % n + 1] ) ++ T ; 
		else ++ t ; 
	} inv[0] = fac[0] = 1 ;
	rep( i, 1, t ) fac[i] = fac[i - 1] * i % P, inv[i] = fpow( fac[i], P - 2 ) ;
	if( m == 1 ) { puts("0") ; exit(0) ; }
	rep( i, 0, t ) A[i] = inv[i] ; 
	init( t + t + 1 ), NTT( A, 1 ) ;
	rep( i, 0, limit ) A[i] = A[i] * A[i] % P ; 
	NTT( A, -1 ) ; int Iv = fpow( 2, P - 2 ) ;
	rep( i, 0, limit ) if( i % 2 == 0 ) A[i] = ( A[i] - inv[i / 2] * inv[i / 2] % P + P ) % P ; 
	rep( i, 0, limit ) A[i] = A[i] * Iv % P ; 
	for( re int i = 1; i <= t; ++ i ) {
		int k = fpow( m - 2, t - i ) * inv[t - i] % P ; 
		Ans = ( Ans + k * A[i] % P ) % P ; 
	}
	printf("%I64d\n", Ans * fpow( m, T ) % P * fac[t] % P ) ;
	return 0 ;
}
```


---

## 作者：Iwara_qwq (赞：2)

### CF1227F2$\quad$2400\*$\quad$组合数学
题意：      
给一个长度为 $n$，值域为 $[1,k]$ 的序列 $a$，令 $b$ 为满足 $\forall i \in [1,n],b_i=a_{i\bmod n+1}$ 的序列（其实就是 $a$ 整个向左移一位）。求有多少个序列 $c$ 满足 $\forall i \in [1,n],c_i\in [1,k]$ 且 $\sum\limits_{i=1}^{n}[a_i=c_i]<\sum\limits_{i=1}^{n}[b_i=c_i]$。       
思路：       
显然，对于 $a_i=b_i$ 的位置，$c_i$ 是什么对结果都没有影响。那么记 $A=\sum\limits_{i=1}^{n}[a_i\ne b_i]$。然后枚举这 $A$ 个位置有多少位满足 $a_i\ne c_i$ 且 $b_i\ne c_i$（即对结果没有影响）。显然，若有 $i$ 个位置满足如上条件，那么这 $i$ 个位置的方案数为 $C=C_{A}^{i}\times (k-2)^i$（先从 $A$ 个位置中选 $i$ 个然后再确定选什么数字）。然后剩下 $A-i$ 个位置 $c_i$ 要么等于 $a_i$，要么等于 $b_i$，显然等于 $b_i$ 的位置更多，那么这部分答案为 $D=\sum\limits_{j=0}^{\lfloor\frac{A-i-1}{2}\rfloor}C_{A-i}^{j}$（剩下 $A-i$ 个位置中最多有 $\lfloor\frac{A-i-1}{2}\rfloor$ 个位置 $a_i=c_i$）。那么答案就等于 $\sum\limits_{i=0}^{A-1} C\cdot D$。       
#### tips: 关于 $D$ 怎么求。      
显然 $\sum\limits_{j=0}^{A-i}C_{A-i}^{j}=2^{A-i}$，那么对于 $A-i\bmod 2=1$ 的情况，$D=2^{A-i}\times \frac{1}{2}$，对于 $A-i\bmod 2 =0$ 的情况，$D=(2^{A-i}-C_{A-i}^{\frac{A-i}{2}})\times\frac{1}{2}$。      
#### code：     
应该比较清楚了。       
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
const ll INF=0x7f7f7f7f7f,inf=0x3f3f3f3f3f;
namespace Yorihime_Nao{
	template<class T> T MAX(T x,T y){
		return x>y?x:y;
	}
	template<class T> T MIN(T x,T y){
		return x<y?x:y;
	}
	template<class T,class ... Arg> T MAX(T x,T y,Arg ... arg){
		return MAX(x>y?x:y,arg...);
	}
	template<class T,class ... Arg> T MIN(T x,T y,Arg ... arg){
		return MIN(x<y?x:y,arg...);
	}
	template<class T> T lowbit(T x){
		return x&-x;
	}
	template<class T> void SWAP(T &x,T &y){
		T qwq=x;
		x=y;
		y=qwq;
		return;
	}
}
using namespace Yorihime_Nao;
const ll MAXN=5e5+5,MOD=998244353;
ll n,k;
ll a[MAXN],b[MAXN];
ll A,B;
ll ans,sum;
ll pre[MAXN]={1},frac[MAXN]={1},bit[MAXN]={1};
ll inv(ll x){
	ll ans=1,y=MOD-2;
	while(y){
		if(y&1)ans=ans*x%MOD;
		x=x*x%MOD;
		y>>=1; 
	}
	return ans;
}
ll con(ll n,ll m){
	return (pre[n]*inv(pre[n-m]*pre[m]%MOD)+MOD)%MOD;
}
int main(){
//	freopen("dawnseeker.in","r",stdin);
//	freopen("dawnseeker.out","w",stdout);
	cin>>n>>k;
	k%=MOD;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)b[i]=a[i%n+1];
	for(int i=1;i<=n;i++)a[i]!=b[i]?A++:B++;
//	cout<<"A: "<<A<<" B: "<<B<<endl;
	ans=1;
	for(int i=1;i<=B;i++)(ans*=k)%=MOD;
	for(int i=1;i<=A;i++)pre[i]=pre[i-1]*i%MOD;
	for(int i=1;i<=A;i++)frac[i]=frac[i-1]*(k-2)%MOD;
	for(int i=1;i<=A;i++)bit[i]=((bit[i-1]<<1)+MOD)%MOD;
//	for(int i=1;i<=A;i++)cout<<bit[i]<<endl;
	for(int i=0;i<=A-1;i++){
		ll C=con(A,i)*frac[i]%MOD;
		ll D=((A-i)%2?bit[A-i]:(bit[A-i]-con(A-i,(A-i)>>1))+MOD)%MOD;
//		cout<<C<<" "<<D<<endl;
		(sum+=C*D)%=MOD;
	}
//	cout<<sum<<endl;
	cout<<ans*sum%MOD*inv(2)%MOD;
	return 0;
}
```
咕咕咕~

---

## 作者：HyperSQ (赞：2)

~~自己想出来的数学题，非常开心~~

我们先将答案全体左移一位得到 $ans'$ ，并要求序列与 $ans$ 匹配数严格小于 $ans'$ 的匹配数。

考虑两种情况：

第一种是 $ans_i=ans'_i $ 。于是这种情况怎么填答案都会同时得分或不得分，不会产生影响。

第二种是 $ans_i\not= ans'_i$ 。这还要分两类情况填答案，第一种是答案不填这两种，于是会同时失分；另一种是填这两者之一，仅仅有这种情况会产生得分差异。

所以我们设不同的位置个数为 $d$，填 $ans'_i$ 有 $a$ 个位置， $ans_i$ 有 $b$ 个位置。显然必须要让 $a>b$。于是我们的答案为

$$
k^{n-d}\sum_{a>b,a+b\leq d}\binom{d}{a}\binom{d-a}{b}(k-2)^{d-a-b}
$$

把后面的系数提出来，$O(n^2)$ 枚举 $a,b$，就可以过 easy version 了。

要优化这个式子，我们要注意到一个事实：

$$
\binom{n}{a}\binom{a}{b}=\binom{n}{b}\binom{n-b}{n-a}
$$

于是

$$
\begin{aligned}
&\sum_{a>b,a+b\leq d}\binom{d}{a}\binom{d-a}{b}(k-2)^{d-a-b}\\
=&\sum_{a>b,a+b\leq d}\binom{d}{d-a}\binom{d-a}{b}(k-2)^{d-a-b}\\
=&\sum_{a>b,a+b\leq d}\binom{d}{b}\binom{d-b}{a}(k-2)^{d-a-b}\\
=&\frac{1}{2}\sum_{a\not=b,a+b\leq d}\binom{d}{a}\binom{d-a}{b}(k-2)^{d-a-b}
\end{aligned}
$$

如果无视 $a\not=b$ 这个条件，上式根据二项式定理，可以化为

$$
\begin{aligned}
&\frac{1}{2}\sum_{a+b\leq d}\binom{d}{a}\binom{d-a}{d-a-b}(k-2)^{d-a-b}\\
=&\frac{1}{2}\sum_{a\leq d}\binom{d}{a}(k-1)^{d-a}\\
=&\frac{1}{2}k^{d}
\end{aligned}
$$

加上 $a\not=b$ 这个条件，只要让上式减去

$$
\begin{aligned}
&\frac{1}{2}\sum_{a=b,a+b\leq d}\binom{d}{a}\binom{d-a}{d-a-b}(k-2)^{d-a-b}\\
\end{aligned}
$$

即可。复杂度 $O(n\log n)$。

[Code](https://www.luogu.com.cn/paste/njcts2ze)

---

## 作者：xht (赞：2)

首先如果相邻两个正确选项一样，那么这个位置选什么都不会产生影响，因此直接将答案 $\times k$。

如果不一样，那么对于每一个位置的生成函数为 $F(x) = x^{-1} + (k - 2) + x$。

设相邻两个正确选项不一样的位置有 $c$ 个，那么答案就是 $F^c(x)$ 的正项系数和 $\times k^{n-c}$。

枚举 $(k-2)$ 项的次数，设剩下的次数为 $i$，此时正项系数和为 $\binom{c}{i}\sum_{2j > i} \binom{i}{j} = \binom{c}{i} \times \frac{2^i - [2|i]\binom{i}{\frac{i}{2}}}2$。

忽略模运算后时间复杂度为 $\mathcal O(n)$。

```cpp
const int N = 2e5 + 7;
int n, k, a[N], c;
modint p[N], ans;

int main() {
	rd(n), rd(k);
	for (int i = 1; i <= n; i++) rd(a[i]);
	c = a[1] != a[n];
	for (int i = 1; i < n; i++) c += a[i] != a[i+1];
	p[0] = 1;
	for (int i = 1; i <= c; i++) p[i] = p[i-1] * i;
	for (int i = 0; i <= c; i++) ans += (p[c] / p[i] / p[c-i]) * (((modint)2 ^ i) - ((i & 1) ? 0 : p[i] / p[i>>1] / p[i>>1])) * ((modint)(k - 2) ^ (c - i)) / 2;
	ans *= (modint)k ^ (n - c);
	print(ans);
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

[也许有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/cf1227f2.html)

## 简要题意

给定 $n$，$k$ 和值域 $[1,k]$ 的 $n$ 个整数 $h_i$，求有多少个长为 $n$ 的整数序列 $a$ 满足值域 $[1,k]$，且 $\sum\limits_{i=1}^n[a_i=h_i]<\sum\limits_{i=1}^n[a_i=h_{(i\bmod{n})+1}]$。答案对 $998244353$ 取模。

$1 \leq n \leq 2\times 10^5,1 \leq k \leq 10^9$

## 思路

如果你不会这道题的 [Easy Version](https://codeforces.com/problemset/problem/1227/F1)，可以先看看 [这篇博客](https://www.cnblogs.com/zheyuanxie/p/cf1227f1.html)。这道题与简单版的最大区别是这道题无法使用 $O(n^2)$ 的 DP。

简单版的解法是：令 $f_{i,j}$ 为截止到第 $i$ 位，比原来的少错 $j$ 个数的方案数。然后可以 $O(1)$ 转移。总时间复杂度 $O(n^2)$。

- 结论 1： $f_{n,i}=f_{n,-i}$。因为对 $j$ 道题与错 $j$ 道题的方案本质上是对称的。
- 结论 2：$\sum_{i=1}^{n}f_{n,i}=\dfrac{k^n-f_0}{2}$。因为 $f_{n,i}=f_{n,-i}$，所以 $k^n-f_0=\sum_{i=-n}^{-1}f_i+\sum_{i=1}^{n}f_i=2\sum_{i=1}^{n}f_{n,i}$。

所以我们其实要求的是 $f_{n,0}$。也就是不改变正确个数的方案总数。

不改变正确的个数的方案总数一定是变换时正确了 $k$ 个，错了 $k$ 个。且 $0\leq k\leq\lfloor\dfrac{M}{2}\rfloor$，其中 $M$ 是 $h$ 中变换后不同的个数。

所以：

$$
f_{n,0}=\sum_{i=1}^{\frac{M}{2}}{F(i)}
$$

$F(i)$ 是给出正确 / 错误的个数，求方案数。我们考虑如何求 $F(i)$。

考虑 $F(i)$ 的来自三个部分的贡献：

1. 正确的 $i$ 个，为 $\binom{M}{i}$。
2. 错误的 $i$ 个，为 $\binom{M-i}{i}(k-2)^{M-2i}$。注意原来的和错误的都要错，所以是 $M-2i$。要排除正确的和本身的，所以是 $k-2$。
3. 没有贡献的，为 $k^{M}$。

所以 $f_{n,0}$ 就求出来了：

$$
f_{n,0}=\sum_{i=1}^{\frac{M}{2}}\binom{M}{i}\binom{M-i}{i}(k-2)^{M-2i}k^{M}
$$

预处理阶乘、阶乘逆元、$k$ 的幂和 $k-2$ 的幂，可以做到严格线性。

时间复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#define int long long
using namespace std;

const int mod = 998244353;
const int N = 2e5+5;

int n,k,m,h[N],fact[N]={1}, inv[N]={1,1}, ret, k2p[N]={1}, kp[N]={1};

int M(const int x){return (x%mod+mod)%mod;}
int c(int m, int n){assert(n-m>=0);return M(fact[n]*M(inv[n-m]*inv[m]));}

signed main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>k;
    if(k==1){cout<<0;return 0;}
    for(int i=1;i<=n;i++) cin>>h[i];
    for(int i=1;i<=n;i++) m+=(h[i]!=h[i%n+1]);
    for(int i=1;i<=n;i++) fact[i]=M(fact[i-1]*i);
    for(int i=2;i<=n;i++) inv[i]=M(M(mod-mod/i)*inv[mod%i]);
    for(int i=2;i<=n;i++) inv[i]=M(inv[i-1]*inv[i]);
    for(int i=1;i<=n;i++) kp[i]=M(kp[i-1]*k);
    for(int i=1;i<=n;i++) k2p[i]=M(k2p[i-1]*(k-2));
    for(int i=0;i<=(m>>1);i++){
        ret=M(ret+M(M(c(i,m)*c(i,m-i))*M(k2p[m-(i<<1)]*kp[n-m])));
    }
    cout<<M((kp[n]-ret)*inv[2])<<'\n';;
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

## 思路

F1 的 dp 是彻底没法用了，考虑用数学方法解题。

首先我们把所有 $a_i=b_i$ 的都踢出去，这样的 $i$ 每一个对答案的贡献是 $k$，有 $m$ 个，贡献就是 $k^m$，单独算即可。

然后考虑正难则反。我们要求出的就是最后第一个人 $\lt$ 第二个人的情况数量。令 $d$ 表示第二个人参加的减去第一个人参加的差值，则我们要求的就是所有方案中，$d>0$ 的部分。

考虑所有的 $d$ 的取值有什么。显然我们随便一个方案都有贡献，所以所有 $d$ 的取值就是 $k^n$。

然后我们只需要减去 $d<0$ 的和 $d=0$ 的即可。

我们发现一个重要的性质，那就是 $d<0$ 的方案数和 $d>0$ 的方案数是一样的。原因是，如果你 $d>0$ 的任意一个方案，它在第 $i$ 个位置上放了一个 $=a_i$ 的数，你就可以对称着放一个 $=b_i$ 的数；如果放了一个 $=b_i$ 的，就对称着放一个 $=a_i$ 的数。可以证明，这样放完之后结果就是原来结果的相反数，并且方案数和原来的一模一样。

所以我们现在就只需要求出 $d=0$ 的方案数，用总方案数减去之后除以 $2$ 即可。

考虑当 $d=0$ 的时候，相当于参加数量一样。我们可以枚举所有的 $i$ 表示第一个人参加了多少个活动，则第二个人也参加了 $i$ 个。那么这个方案数很好求，显然是 $C_{n}^{i} \times C_{n-i}^{i}$。

那么这样的话我们其他的位置就只能放 $\neq a_i$ 也 $\neq b_i$ 的值了，有 $k-2$ 种取值，有 $n-2i$ 个位置，所以一共 $(k-2)^{n-2i}$ 种方案。

但是我们没有考虑 $a_i=b_i$ 的情况，所以我们假设有 $m$ 个 $a_i=b_i$ 的 $i$，则他们的贡献我们单算，剩下的 $n-m$ 个 $i$ 都满足 $a_i \neq b_i$。然后还是套用上面的式子，即 $C_{n-m}^{i} \times C_{n-m-i}^{i} \times (k-2)^{n-2_i}$。但是注意我们这里还有 $m$ 个任意取得位置，所以还要乘上 $k^m$。

所以 $d=0$ 的方案数就是 $C_{n-m}^{i} \times C_{n-m-i}^{i} \times (k-2)^{n-2i} \times k^m$。记这个结果为 $D_0$，则最终我们要求的答案就是总方案数减去这个 $D_0$ 再除以 $2$，即 $\dfrac{k^n-D_0}{2}$。

这里面所有的乘方我们使用快速幂，然后再加一个乘法逆元即可做到 $O(n \log k)$。

## Code

```cpp
#include <bits/stdc++.h>
inline int qr(){
	char ch=getchar(); bool f=1; int w=0;
	for(;ch<'0' || ch>'9';ch=getchar()) if(ch=='-')f=0;
	for(;ch>='0' && ch<='9';ch=getchar()) w=w*10+ch-'0';
	return f?w:-w;
}
void write(int x){
	if(x>9) write(x/10);
	putchar(x%10+48);
}

using namespace std;
const int MAXN=300005,mod=998244353;
int a[MAXN],b[MAXN],frac[MAXN];

inline int ksm(int x,int y){
	int ans=1;
	while(y){
		if(y&1) ans=1ll*ans*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ans;
}
inline int inv(const int &x){return ksm(x,mod-2);}
inline int C(const int &x,const int &y){return 1ll*frac[x]*inv(frac[y])%mod*inv(frac[x-y])%mod;}

int main(){
	int n=qr(),k=qr(),m=0;
	for(int i=1;i<=n;i++) a[i]=qr();
	for(int i=1;i<=n;i++) b[i]=a[i%n+1];
	for(int i=1;i<=n;i++) if(a[i]!=b[i]) m++;
	
	int ans=0; frac[0]=1;
	for(int i=1;i<=n;i++) frac[i]=1ll*frac[i-1]*i%mod;
	
	for(int i=0;i<=m/2;i++) ans=(ans+1ll*C(m,i)*C(m-i,i)%mod*ksm(k-2,m-i*2)%mod*ksm(k,n-m)%mod)%mod;
	write((1ll*(ksm(k,n)-ans+mod)%mod*inv(2))%mod);
	return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

比 std 蠢，但是也是一种做法。

首先我们发现相邻两个不同的生成函数是 $F(x)=(x+(k-2)+x^{-1})$，相邻两个相同会给答案乘上 $k$。因此我们要求的就是 $G(x)=F(x)^t=(x+(k-2)+x^{-1})^t$ 的所有正数次项的系数之和。

这里最简洁的方法是观察到系数是对称的，因此只需要计算 $\frac{k^t-[x^0]G(x)}{2}$ 即可，而常数项是容易枚举一维组合数算出的。

然而如果你没有意识到这件事情，我们也可以大力求出所有的系数。我们先把 $-1$ 次项乘掉，转而求 $F(x)=x^2+(k-2)x+1$ 的情况。

我们可以考虑两边求导：

$$
G(x)=F(x)^t \\
G'(x)=tF'(x)F(x)^{t-1}
$$

这时候你发现右边乘上一个 $F(x)$ 就能合成大 $G(x)$，所以给他乘一下，得到：

$$
F(x)G'(x)=tF'(x)G(x)
$$

很显然这是一个至多三阶的线性递推，因此我们只需要确定初值 $g_0=1,g_1=t(k-2)$，接下来的 $g$ 都容易求出，再求和就行了。时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
#define debug(x) cerr<<(#x)<<": "<<x<<endl
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=4e5+9,Mod=998244353;
ll n,K,a[N],t,res=1,g[N<<1];
ll fac[N],ifac[N],inv[N];
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%Mod;
        x=x*x%Mod,p>>=1;
    }
    return res;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),K=read();
    rep(i,1,n)a[i]=read();
    fac[0]=1;
    rep(i,1,n*2)fac[i]=fac[i-1]*i%Mod;
    ifac[n*2]=pw(fac[n*2],Mod-2);
    per(i,n*2-1,0)ifac[i]=ifac[i+1]*(i+1)%Mod;
    rep(i,1,n*2)inv[i]=ifac[i]*fac[i-1]%Mod;
    rep(i,1,n){
        if(a[i]!=a[i%n+1])t++;
        else res=res*K%Mod;
    }
    g[0]=1,g[1]=t*(K-2)%Mod;
    rep(i,1,t*2-1){
        ll lf=(K-2)*i%Mod*g[i]%Mod;
        if(i>=2)lf=(lf+(i-1)*g[i-1])%Mod;
        ll rg=(2*t*g[i-1]+(K-2)*t%Mod*g[i])%Mod;
        rg=(rg-lf+Mod)%Mod;
        g[i+1]=rg*inv[i+1]%Mod;
    }
    ll ans=0;
    rep(i,t+1,t*2)ans=(ans+g[i])%Mod;
    write(ans*res%Mod),putchar('\n');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：Missa (赞：0)

pupil 自己想到了 *2400 题目的做法，很开心，加上这是第 $120$ 紫，于是来写题解了。

题意：

> 给定 $n$ 数 $a_i \in [1,k]$，对满足以下要求 $c$ 计数：
> 
> - $\displaystyle\sum\limits_{i=1}^n [a_i=c_i] < \sum\limits_{i=1}^n [a_i=c_{(i \bmod n) + 1}]$
> 
> $n \leq 2 \cdot 10^5,k \leq 10^9$

- 先想 dp，试着一位一位填 $c$，发现给的两个式子的差需要被记录，做不下去。
- 发现数字相对大小不重要，只有是否相等重要。
- 把连续的一段数缩成一个数，令 $b_i(i \in [1,m])$ 表示第 $i$ 段的大小。首尾同样视作相连，因为我们只在意相对顺序。
- 再发现事实上每一段只有最右边的一个数有用，因为其它数字右移一位时对齐的 $a_i$ 相等。
- 问题转化为：$m$ 数，每个数可以选择 $a_i$（仅对左式产生 $1$ 贡献）、$a_{(i \bmod n) + 1}$（仅对右式产生 $1$ 贡献），其它（$k-2$ 填法，两边均不贡献），求方案数，再乘上 $k^{n-m}$。
- 枚举前面两类数字的总数，得到答案计算公式:

$$\displaystyle ans= k^{n-m} \sum\limits_{i=1}^{m} (k-2)^{m-i} \binom{m}{i} \sum_{j=1}^{(i-1)/2} \binom{i}{j}$$

- 考虑化简关于 $j$ 的那个求和。注意到 $j$ 几乎取到了一半值域，而杨辉三角是对称的。熟知 $\displaystyle \sum_{i=0}^n \binom{n}{i} = 2^n$，因此

$$
\begin{aligned}
\binom{n}{i}=\binom{n}{n-i} & \iff \sum_{i=0}^n \binom{2n}{i} = \dfrac{2^{2n}-\binom{2n}{n}}{2} \\
& \iff \sum_{i=0}^n \binom{2n+1}{n} = \dfrac{2^{2n+1}}{2} = 2^{2n+1}
\end{aligned}
$$

- 直接维护即可。复杂度 $O(n)$，如果用快速幂 $O(n \log n)$。
- 代码相当好写，不给了。

---

## 作者：Exber (赞：0)

发现我的做法和大家的都不一样？

## 做法

递推+组合计数。

令**满足 $a_i=h_i$ 的所有 $i$ 的集合为 $A$，满足 $a_i=h_{i\operatorname{mod} n+1}$ 的所有 $i$ 的集合为** $B$。

注意到**对于所有满足 $h_i=h_{i\operatorname{mod} n+1}$ 的位置 $i$，无论 $a_i$ 选什么数都不会对两个集合的大小有影响**，所以**记这样的 $i$ 有 $cnt$ 个，令** $m=n-cnt$。问题就转化成了**求在 $m$ 个不同的元素中选取两个集合 $C$ 和 $D$，满足 $|C|<|D|$ 的方案数**。

对于这个新的问题，不妨考虑**递推**求解。**令 $f_i$ 为在 $i$ 个不同的元素中选取两个集合 $S$ 和 $T$，满足 $|S|<|T|$ 的方案数，首先显然有 $f_0=0,f_1=1$**。

考虑在**共有 $i-1$ 个元素的情况下加进元素** $i$ 的贡献，可以分成两部分：

- $i$ 加入了集合 $T$，**那么原来所有的方案和原来 $|S|=|T|$ 的方案**都合法，贡献即为 $f_{i-1}+[(i-1)\operatorname{mod} 2=0]\dbinom{i-1}{\frac{i-1}{2}}$
- $i$ 加入了集合 $S$，那么原来 $|S|<|T|-1$ 的方案合法，**相当于用原来所有的方案数减去原来 $|S|=|T|-1$ 的方案数**，贡献即为 $f_{i-1}-[(i-1)\operatorname{mod} 2=1]\dbinom{i-1}{\lfloor\frac{i-1}{2}\rfloor}$

所以有递推式：

$$f_i=\begin{cases}0&i=0\\1&i=1\\2f_{i-1}+[(i-1)\operatorname{mod} 2=0]\dbinom{i-1}{\frac{i-1}{2}}-[(i-1)\operatorname{mod} 2=1]\dbinom{i-1}{\lfloor\frac{i-1}{2}\rfloor}&i\ge2\end{cases}$$

回到本题，答案即为：

$$k^{cnt}\sum\limits_{l=1}^m\dbinom{m}{l}f_{l}(k-2)^{m-l}$$

即**先计算 $cnt$ 个特殊位置的方案数，再枚举 $l=|A|+|B|$。$\dbinom{m}{l}$ 相当于选出了 $l$ 个普通位置给 $A$ 和 $B$，而 $(k-2)^{m-l}$ 相当于剩下没用到的普通位置选数的方案数**。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int p=998244353;

int n,k;
int h[200005];
int fra[200005],inv[200005];
int f[200005];

inline int qpow(int x,int y=p-2)
{
	int res=1;
	for(;y>0;y>>=1,x=1ll*x*x%p) res=(y&1)?1ll*res*x%p:res;
	return res;
}

inline int C(int n,int m)
{
	return 1ll*fra[n]*inv[n-m]%p*inv[m]%p;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&h[i]);
	}
	fra[0]=1;
	for(int i=1;i<=n;i++)
	{
		fra[i]=1ll*fra[i-1]*i%p;
	}
	inv[n]=qpow(fra[n]);
	for(int i=n;i>=1;i--)
	{
		inv[i-1]=1ll*inv[i]*i%p;
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		cnt+=h[i]==h[i%n+1];
	}
	int m=n-cnt;
	f[0]=0;
	f[1]=1;
	for(int i=2;i<=m;i++)
	{
		f[i]=2ll*f[i-1]%p;
		if((i-1)%2==0)
		{
			f[i]=(f[i]+C(i-1,(i-1)/2))%p;
		}
		else
		{
			f[i]=(f[i]-C(i-1,(i-1)/2)+p)%p;
		}
	}
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		ans=(ans+1ll*C(m,i)*qpow(k-2,m-i)%p*f[i]%p)%p;
	}
	ans=1ll*ans*qpow(k,cnt)%p;
	printf("%d\n",ans);
	return 0;
}
```

---

