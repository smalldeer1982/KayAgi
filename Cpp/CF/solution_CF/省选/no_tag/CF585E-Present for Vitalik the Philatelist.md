# Present for Vitalik the Philatelist

## 题目描述

Vitalik the philatelist has a birthday today!

As he is a regular customer in a stamp store called 'Robin Bobin', the store management decided to make him a gift.

Vitalik wants to buy one stamp and the store will give him a non-empty set of the remaining stamps, such that the greatest common divisor (GCD) of the price of the stamps they give to him is more than one. If the GCD of prices of the purchased stamp and prices of present stamps set will be equal to $ 1 $ , then Vitalik will leave the store completely happy.

The store management asks you to count the number of different situations in which Vitalik will leave the store completely happy. Since the required number of situations can be very large, you need to find the remainder of this number modulo $ 10^{9}+7 $ . The situations are different if the stamps purchased by Vitalik are different, or if one of the present sets contains a stamp that the other present does not contain.

## 说明/提示

In the first sample the following situations are possible:

- Vitalik buys the 1-st stamp, the store gives him the 2-nd stamp as a present;
- Vitalik buys the 3-rd stamp, the store gives him the 2-nd stamp as a present;
- Vitalik buys the 2-nd stamp, the store gives him the 1-st stamp as a present;
- Vitalik buys the 2-nd stamp, the store gives him the 3-rd stamp as a present;
- Vitalik buys the 2-nd stamp, the store gives him the 1-st and 3-rd stamps as a present.

## 样例 #1

### 输入

```
3
2 3 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
2
9 6
```

### 输出

```
0
```

# 题解

## 作者：mrsrz (赞：15)

[可能更好的体验](https://mrsrz.github.io/2019/12/03/CF585E/)

~~我数学是真的菜啊~~

令 $s_n$ 表示最大公因数恰好为 $n$ 的集合个数，$f_n$ 表示与 $n$ 互质的数的个数。

那么我们要求的就是 $\sum_i s_if_i$.

考虑求出 $s$ 和 $f$。

考虑计算 $f_i$。令 $c_i$ 表示数 $i$ 的出现次数。

强行莫比乌斯反演qwq
$$
f_n=\sum_i[\gcd(i,n)=1]c_i
$$
$$
=\sum_ic_i\sum_{d|i,d|n}\mu(d)
$$
$$
=\sum_{d|n}\mu(d)\sum_{d|i} c_{_i}
$$
我们令 $g_k=\sum\limits_{k|i}c_i$；$g'_k=\mu(k)g_k$，那么 $f_n=\sum\limits_{d|n} g'_d$

发现这个 $g_i$ 就表示 $i$ 的倍数的出现次数。

再考虑求 $s_i$。我们令 $s'_i$ 表示最大公因数为 $i$ 的倍数的方案数。要使最大公因数为 $i$ 的倍数，那么每个选的数必须是 $i$ 的倍数。所以容易得到 $s'_i=2^{g_i}-1$

我们又有 $s'_i=\sum\limits_{i|d}s_d$

观察上面的式子的形式，他们都是这样的形式：
$$
b_k=\sum_{i|k}a_i
$$
$$
b_k=\sum_{k|i}a_i
$$
其中，上面的式子为**狄利克雷前缀和**，下面的式子为**狄利克雷后缀和**。

这两个东西，都可以在 $O(w\log\log w)$ 的时间复杂度内完成。具体做法请见我贡献的[【模板】Dirichlet 前缀和](https://www.luogu.com.cn/problem/P5495)（后缀和与前缀和的做法本质相同，都是高维前缀和）。

计算 $g$ 和 $f$ 都是标准的狄利克雷前/后缀和形式。

但还有个问题，已知 $a$ 求 $b$ 能做了，但是那个 $s$ 的计算，是已知 $b$ 求 $a$ 的。

前面是加，那现在就把它逆回去就好了。具体就是把两重循环的反向，然后把加法改成减法就可以辣。当然也可以用高维前缀和的知识解释。

总时间复杂度 $O(n+w\log\log w)$。

## Code：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
const int N=5e5+5,M=1e7+2,md=1e9+7;
int S[M],_2[500005],a[500005],tot[M],g[M],pri[M/10],cnt,mu[M];
bool vis[M];
inline void upd(int&a){a+=a>>31&md;}
int n,lim,ans;
void sieve(const int n){
	mu[1]=1;
	for(int i=2;i<=n;++i){
		if(!vis[i])pri[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pri[j]<=n;++j){
			vis[i*pri[j]]=1;
			if(i%pri[j]==0){
				mu[i*pri[j]]=0;
				break;
			}else mu[i*pri[j]]=-mu[i];
		}
	}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(int i=*_2=1;i<=500000;++i)upd(_2[i]=_2[i-1]*2-md);
	cin>>n;
	for(int i=1;i<=n;++i)
	cin>>a[i],++tot[a[i]];
	lim=*max_element(a+1,a+n+1);
	sieve(lim);
	for(int i=1;i<=cnt;++i)
	for(int j=lim/pri[i];j;--j)
	tot[j]+=tot[j*pri[i]];
	for(int i=1;i<=lim;++i)g[i]=tot[i]*mu[i];
	for(int i=1;i<=cnt;++i)
	for(int j=1;j*pri[i]<=lim;++j)
	g[j*pri[i]]+=g[j];
	for(int i=1;i<=lim;++i)S[i]=_2[tot[i]]-1;
	for(int i=cnt;i;--i)
	for(int j=1;j*pri[i]<=lim;++j)
	upd(S[j]-=S[j*pri[i]]);
	for(register int i=lim;i>1;--i)
	ans=(ans+(LL)S[i]*g[i])%md;
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：Time_tears (赞：9)

提供一个题解中还没有的容斥解法，没有繁杂的式子，只有清晰的组合解释。（也可以当成莫比乌斯反演解法的组合解释）

考虑枚举 $x$ ，算每个合法的 $S$ 有多少种。

因为要求合法的 $S$ 的 $\gcd >1$ ，所以我们不妨再枚举一个 $S$ 的 $\gcd$，设为 $d$，满足 $\gcd(d,x)=1$，那么现在我们要求的就是对于每个 $d$ 算有多少种 $S$ 是合法的。

这是一个非常经典的问题，考虑容斥，将每个要求的答案变成 $\gcd$ 至少为 $d$ 的答案，然后做一遍容斥就是每个 $d$ 的答案，这里的容斥系数恰好就是莫比乌斯函数，用一个 $	Dirichlet$ 后缀和求出是某个 $d$ 的倍数的数有多少个然后用莫比乌斯函数进行容斥就可以求出集合 $S$ 的方案数。

但是如果我们对每个 $x$ 都做一遍如上操作复杂度肯定是遭不住的，所以考虑用所有 $d$ 的答案 $-$ $\gcd(d,x)>1$ 的 $d$ 的答案，所有的 $d$ 的答案可以一开始就求出，只用做一次上述操作。

至于 $\gcd(d,x)>1$ 的 $d$ 的答案，我们发现这样的 $d$ 所含素数的次数都为 $1$（废话要不 $\mu (d)$ 就为 $0$ 了），所以这样的 $d$ 必然是 $x$ 的约数，直接对 $x$ 质因数分解，取出所有不同的质数，再对这些质数和这些质数所能构成的数暴力做一遍容斥，就可以求出单个 $x$ 的答案了。

由于 $x$ 只有 $10^7$ 级别，这样的质数顶多只有 $8$ 个( $2,3,5,7,11,13,17,19$ 是最多的情况 ) 所以可以暴力 $2^8$ 做容斥，最坏总复杂度 $O(n\log \log n +2^8 \times n)$，实测比大多数快。

代码：

```cpp
#include<bits/stdc++.h>
#define N 500005
#define M 10000005
using namespace std;
const int mod=1e9+7;
int n,mx,ans,a[N],f[M],pw[N];
int cnt,p[M],mu[M],tmp,mn[M];
char vis[M];
int Mod(int x) {return x<mod?x:x-mod;}
inline int read() {
	int s=0,f=0;
	char ch=getchar();
	while(ch<48||ch>57)f|=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
void Pre(int n) {
	for(int i=2; i<=n; ++i) {
		if(!vis[i])vis[i]=1,mu[p[++cnt]=mn[i]=i]=-1;
		for(int j=1; j<=cnt&&p[j]*i<=n; ++j){if(vis[p[j]*i]=1,mn[p[j]*i]=p[j],i%p[j]==0)break;mu[p[j]*i]=-mu[i];}
	}
}
int pp[10],num;
void Dfs(int nw,int x) {
	if(nw==num+1)return ans=Mod(ans+Mod(mod+f[x]*mu[x])),void();
	Dfs(nw+1,x),Dfs(nw+1,x*pp[nw]);
}
void Solve(int x) {
	for(num=0; x>1; x/=mn[x])if(pp[num]!=mn[x])pp[++num]=mn[x];
	ans=Mod(ans+tmp),Dfs(1,1);
}
int main() {
	n=read();
	for(int i=1; i<=n; ++i)++f[a[i]=read()],mx=max(mx,a[i]);Pre(mx);
	for(int i=1; i<=cnt; ++i)for(int j=mx/p[i]; j; --j)f[j]+=f[j*p[i]];
	for(int i=pw[0]=1; i<=n; ++i)pw[i]=Mod(pw[i-1]<<1);
	for(int i=1; i<=mx; ++i)f[i]=pw[f[i]]-1,tmp=Mod(tmp+Mod(mod+f[i]*(-mu[i])));
	for(int i=1; i<=n; ++i)Solve(a[i]);cout<<ans;
	return 0;
}
```


---

## 作者：Querainy (赞：6)

为什么大家都要莫反啊/dk，呃不过我这个可能跟莫反有本质相同的地方?

你发现这个面值少的可怜只有1e7，这是为什么?

gcd卷积。考虑我们先把所有数卷起来得到一个 $f_i$ 表示取若干数 $\gcd$ 为 $i$ 的方案数 的序列，然后剔除掉 $f_1$ 表示这部分 $\gcd>1$ ，再卷上所有数(也就是 $c_i$ 表示 $i$ 的个数)，取第 $1$ 位就是答案。

现在问题是怎么把所有数卷起来。考虑类似于[某个经典题](https://www.luogu.com.cn/problem/CF449D)的做法，$z+z^x$ 这样的东西fmt一下乘进答案，就相当于给 $x$ 的因数全都乘上 $2$ ，所以可以打一个标记，然后用fmt来推这个标记，然后再逆fmt回去。这就做完了，复杂度 $O(n+v\log\log v)$ 。

呃为什么点乘上 $z+z^x$ fmt的结果，是把 $x$ 的因数都乘 $2$ ?考虑对这个东西做fmt，就是先给所有数 $+1$ ，然后给 $x$ 的因数 $+1$ ，那么某个东西跟这个点乘起来，不就是把它里面 $x$ 的因数全部乘 $2$ 吗（

```cpp
#include<stdio.h>

const int P=1e9+7,V=1e2;
inline void mod(int &x){ if(x>=P) x-=P; }

int prime[1000002],pcnt;
bool b[10000002];
inline void sieve(int n)
{
	for(int i=2;i<=V;i++)
	{
		if(!b[i]) prime[++pcnt]=i;
		for(int j=1;j<=pcnt&&i*prime[j]<=V;j++)
		{
			b[i*prime[j]]=1;
			if(!(i%prime[j])) break;
		}
	}
}

int n,c[10000002],f[10000002];

inline void fmt(int n,int *A)//dirichlet suffix sum
{
	for(int i=1;i<=pcnt;i++)
		for(int j=V/prime[i];j>0;j--)
			mod(A[j]+=A[prime[i]*j]);
}
inline void ifmt(int n,int *A)
{
	for(int i=1;i<=pcnt;i++)
		for(int j=1;prime[i]*j<=V;j++)
			mod(A[j]+=P-A[prime[i]*j]);
}

int main()
{
	scanf("%d",&n);
	sieve(V);
	for(int i=1;i<=V;i++) f[i]=1;//f[1]=1,fmt(V,f,1)
	for(int i=1,x;i<=n;i++) scanf("%d",&x),c[x]++,mod(f[x]*=2);
	
	for(int i=1;i<=pcnt;i++)
		for(int j=V/prime[i];j>0;j--)
			f[j]=(long long)f[prime[i]*j]*f[j]%P;
	for(int i=2;i<=V;i++) mod(f[i]+=P-1);
	ifmt(V,f);
	f[1]=0;
	fmt(V,f);
	
	fmt(V,c);
	for(int i=1;i<=V;i++) f[i]=(long long)f[i]*c[i]%P;
	ifmt(V,f);
	printf("%d\n",f[1]);
	return 0;
}
```

---

## 作者：xht (赞：5)

> [CF585E Present for Vitalik the Philatelist](https://codeforces.com/contest/585/problem/E)

## 题意

- 有一个包含 $n$ 个 $\in [2, 10^7]$ 的整数的可重集合。
- 要求满足条件的一个元素 $x$ 和一个集合 $S$ 的方案数。
- 条件：$x \notin S$，$\gcd\{S\} > 1$，$\gcd(x, \gcd\{S\}) = 1$。
- $n \le 5 \times 10^5$，答案对 $10^9+7$ 取模。

## 题解

枚举 $d = gcd\{S\}$，设 $c$ 为 $d$ 的倍数的个数，则 $d$ 对应的方案数为 $(n-c) \times (2^c - 1)$。

显然有算重的，容斥一下即可，容斥系数恰好为莫比乌斯函数的相反数。

时间复杂度 $\mathcal O(w \log w)$。

## 代码

```cpp
const int N = 5e5 + 7, M = 1e7 + 7;
int n, m, x, c[M], p[M], cnt, v[M];
modint num[N], miu[M], ans;

int main() {
	rd(n), num[0] = 1;
	for (int i = 1; i <= n; i++) rd(x), m = max(m, x), c[x]++, num[i] = num[i-1] * 2;
	miu[1] = 1;
	for (int i = 2; i <= m; i++) {
		if (!v[i]) v[i] = p[++cnt] = i, miu[i] -= 1;
		for (int j = 1; j <= cnt && i * p[j] <= m && p[j] <= v[i]; j++)
			v[i*p[j]] = p[j], miu[i*p[j]] = p[j] == v[i] ? 0 : -miu[i];
	}
	for (int i = 1; i <= m; i++) {
		cnt = 0;
		for (int j = i; j <= m; j += i) cnt += c[j];
		ans += (-miu[i]) * (n - cnt) * (num[cnt] - 1);
	}
	print(ans);
	return 0;
}
```

---

## 作者：YksKuusiTAlv (赞：4)

提供一种题解区没有的简单做法。

首先发现可以转化一下题意，题目要求 $\rm Gcd(x,\{S\})=1,x\not\in S$

既然 $\rm x \not\in S$ , 那么可以把 x,S 看成一个集合 T 。

集合 T 中分裂任意一个元素都能得到一个元素+一个集合。

假设我们可以求出来 “大小为 $\rm x$ 的集合 $\rm S , Gcd\{S\}=1$ ” 的个数，记为 $\rm num_x$ 。

那么，单步容斥（类似 isn 的一个套路），不难得到 

$$\rm ans=\sum_{i=1}^n (i*num_i-num_{i-1}*(n-(i-1)))$$

解释一下这个式子，大小为 x 的 集合 T 中每个集合都可以去掉任意一个元素，方案数是 $\rm x*num_x$ , 但是，一个 $\rm Gcd =1$ 的集合 S , 加入任意一个数， $\rm Gcd$ 必将也是 $1$ ，所以，会有 $\rm (n-(i-1))*num_{i-1}$  的重复计算，减去就好了。

接下来想如何计算 $\rm num_i$ , 这是一个比较简单的 莫比乌斯容斥 （感谢 zero4338 赐教）。

先统计出来 $\rm cnt_i$ , 代表 i 的倍数的个数，这个可以开桶+调和级数枚举 $n*ln(n)$ 求出来。

$$num_i=\sum_{d=1}^{1e7} \mu(d)*\binom {cnt_d}{i}$$

结合 $\mu$ 的实际意义不难理解， $\rm Gcd\not=1$ 的集合都被统计了 0 次。

暴力计算所有 $\rm num$ ，复杂度是 $1e7*n$ 的，但是发现只有 $\leq cnt_d$ 的 i 才会被计算到贡献，又因为 $\sum cnt \leq n*ln(n)$ , 所以可以更换枚举方式，枚举 $i$ ， 刷表贡献给所有 $\leq cnt_i$ 的 数。

空间 $\rm 250M$ 的限制开不下需要的所有数组，但是筛 $\mu$ 的数组筛出来 $\mu$ , 其他数组就没用了，可以重复利用。

* code 

```c++
#include <bits/stdc++.h>
#define R register int
#define scanf Ruusupuu = scanf
#define freopen rsp_5u = freopen
#define fre(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout)

int Ruusupuu ;
FILE * rsp_5u ;

using namespace std ;
typedef long long L ;
const int N = 5e5 + 10 ;
const int M = 1e7 + 10 ;
const int P = 1e9 + 7 ;

inline int A( int a , int b ){ return ( a + b >= P ) ? ( a + b - P ) : ( a + b ) ; }
inline void jA( int &a , int b ){ a = ( a + b >= P ) ? ( a + b - P ) : ( a + b ) ; }
inline int E( int a , int b ){ return ( a - b < 0 ) ? ( a - b + P ) : ( a - b ) ; }
inline void jE( int &a , int b ){ a = ( a - b < 0 ) ? ( a - b + P ) : ( a - b ) ; }
inline int T( int a , int b ){ return ( 1ll * a * b ) % P ; }

inline int read(){
	int w = 0 ; bool fg = 0 ; char ch = getchar() ;
	while( ch < '0' || ch > '9' ) fg |= ( ch == '-' ) , ch = getchar() ;
	while( ch >= '0' && ch <= '9' ) w = ( w << 1 ) + ( w << 3 ) + ( ch ^ 48 ) , ch = getchar() ;
	return fg ? -w : w ; 
}

int n , a [N] , buc [M] , fg [M] , pr [M] , top , mu [M] , cnt [M] , num [M] , ans ;
inline int C( int n , int m ){ if( !m ) return 1 ; if( n < m ) return 0 ; return T( pr [n] , T( fg [m] , fg [n - m] ) ) ; }

void sc(){
	n = read() ; for( R i = 1 ; i <= n ; i ++ ) a [i] = read() , buc [a [i]] ++ ;
	mu [1] = 1 ; for( R i = 2 ; i < M ; i ++ ){
		if( !fg [i] ) pr [++ top] = i , mu [i] = -1 ;
		for( R j = 1 ; j <= top && pr [j] * i < M ; j ++ ){
			fg [i * pr [j]] = 1 ;
			if( i % pr [j] == 0 ){
				mu [i * pr [j]] = 0 ; break ;
			} mu [i * pr [j]] = -mu [i] ;
		}
	}
}

void work(){
	memset( fg , 0 , sizeof( fg ) ) , memset( pr , 0 , sizeof( pr ) ) , fg [0] = fg [1] = pr [0] = pr [1] = 1 ;
	for( R i = 2 ; i < M ; i ++ ) pr [i] = T( pr [i - 1] , i ) , fg [i] = T( P - P / i , fg [P % i] ) ;
	for( R i = 2 ; i < M ; i ++ ) fg [i] = T( fg [i - 1] , fg [i] ) ; 
	for( R i = 1 ; i < M ; i ++ ) for( R j = 1 ; i * j < M ; j ++ ) cnt [i] += buc [i * j] ;
	for( R i = 1 ; i < M ; i ++ ) if( mu [i] && cnt [i] ) for( R j = 1 ; j <= cnt [i] ; j ++ )
		if( mu [i] == 1 ) jA( num [j] , C( cnt [i] , j ) ) ;
		else assert( mu [i] == -1 ) , jE( num [j] , C( cnt [i] , j ) ) ;
	for( R i = 1 ; i <= n ; i ++ ) jA( ans , E( T( i , num [i] ) , T( num [i - 1] , n - i + 1 ) ) ) ;
	printf( "%d\n" , ans ) ;
}

signed main(){	//fre(in);
	sc() ;
	work() ;
	return 0 ;
}
```

---

## 作者：StudyingFather (赞：4)

由题意可知所求为：

$$
\sum_{S \subseteq U}\sum_{x \notin S}[\gcd(S)\neq 1][\gcd(S,x)=1]
$$

我们发现一个问题：当不满足上式的第一个条件时，上式的第二个条件一定会得到满足。因此考虑用满足第二个条件的方案数减去不满足第一个条件的方案数，从而得到所求。

也就是说我们要求的实际上是：

$$
\sum_{S \subseteq U}\sum_{x \notin S}[\gcd(S,x)=1]-\sum_{S \subseteq U}\sum_{x \notin S}[\gcd(S)=1]
$$

先解决第一部分。

我们注意到，如果有集合 $A$（且 $|A|\gt 1$）满足 $\gcd(A)=1$，则从 $A$ 中任意取出一个元素作为 $x$，以去掉 $x$ 的 $A$ 集合作为 $S$，一定满足 $\gcd(S,x)=1$ 的条件。

于是考虑枚举这样的集合 $A$ 来计算第一部分的值，得到第一部分的结果为（注：$W$ 为所有元素中的最大值，$a_d$ 为所有元素中是 $d$ 的倍数的元素个数）：

$$
\begin{aligned}
\sum_{|A|\gt 1}[\gcd(A)=1]|A|&=\sum_{|A|\gt 1}\sum_{d\mid \gcd(A)}\mu(d)|A|\\
&= \sum_{d=1}^{W}\mu(d)\sum_{|A|\gt 1,d\in \gcd(A)}|A|\\
&= \sum_{d=1}^{W}\mu(d)\sum_{|A|=2}^{a_d} \binom{a_d}{|A|}|A|
\end{aligned}
$$

记 $f(x)=\sum_{i=1}^{x} \binom{x}{i}i$，则上式可写为：

$$
\sum_{d=1}^{W}\mu(d)(f(a_d)-f(1))
$$

现在考虑如何计算 $f(x)$。

稍微研究一下之后就会发现，$f(x)=2f(x-1)+2^{x-1}$。

这样我们就完成了一半的工作。

现在考虑后半部分。

和前半部分思路类似，我们枚举满足 $\gcd(S)=1$ 的集合 $S$，则所有不在 $S$ 中的数 $x$ 都是合法的选择方案。

稍微推一下就会发现：

$$
\begin{aligned}
\sum_{S}[\gcd(S)=1](n-|S|)&=\sum_{S}\sum_{d\mid \gcd(S)}\mu(d)(n-|S|)\\
&= \sum_{d=1}^{W}\mu(d)\sum_{d\mid \gcd(S)}(n-|S|)\\
&= \sum_{d=1}^{W}\mu(d)(n \sum_{|S|=1}^{a_d}\binom{a_d}{S}-\sum_{|S|=1}^{a_d}\binom{a_d}{S}|S|)\\
&= \sum_{d=1}^{W}\mu(d)(n(2^n-1)-f(a_d))
\end{aligned}
$$

这种做法的效率如何呢？由调和级数的知识可知，我们预处理 $a_d$ 的时间复杂度为 $O(W \ln W)$，而计算两部分的时间复杂度均为 $O(W)$，可以通过本题。

```cpp
// Problem : E. Present for Vitalik the Philatelist
// Contest : Codeforces - Codeforces Round #325 (Div. 1)
// URL : https://codeforces.com/contest/585/problem/E
// Memory Limit : 256 MB
// Time Limit : 5000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
#define MAXX 10000000
#define MAXN 500000
#define MOD 1000000007
using namespace std;
int vis[MAXX+5],pri[MAXX+5],mu[MAXX+5],cnt;
int x[MAXN+5],t[MAXX+5],a[MAXX+5],p2[MAXN+5];
long long f[MAXN+5],g[MAXN+5];
int main()
{
 ios::sync_with_stdio(false);
 int n;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
  cin>>x[i];
  t[x[i]]++;
 }
 mu[1]=1;
 for(int i=2;i<=MAXX;i++)
 {
  if(!vis[i])
  {
   pri[++cnt]=i;
   mu[i]=-1;
  }
  for(int j=1;j<=cnt&&i*pri[j]<=MAXX;j++)
  {
   vis[i*pri[j]]=1;
   if(i%pri[j]==0)
   {
    mu[i*pri[j]]=0;
    break;
   }
   mu[i*pri[j]]=-mu[i];
  }
 }
 for(int i=1;i<=MAXX;i++)
  for(int j=i;j<=MAXX;j+=i)
   a[i]+=t[j];
 p2[0]=1;
 for(int i=1;i<=n;i++)
 {
  p2[i]=p2[i-1]*2%MOD;
  f[i]=(2*f[i-1]+p2[i-1])%MOD;
 }
 long long ans=0;
 for(int d=1;d<=MAXX;d++)
 {
  ans=(ans+mu[d]*(f[a[d]]-a[d]))%MOD;
  ans=(ans-mu[d]*(1ll*n*(p2[a[d]]-1)-f[a[d]]))%MOD;
 }
 cout<<(ans+MOD)%MOD<<endl;
 return 0;
}
```

---

## 作者：关怀他人 (赞：3)

### CF 585E
#### Solution
提供一种只用做一次**狄利克雷前缀和**的做法。

考虑枚举$gcd$的值，设为$d$，记$c_i$为$i$的倍数的个数，那么$d$对答案的贡献为$(n-c_d)\times (2^{c_d}-1)$，但这样显然会算重，考虑容斥，不难发现容斥系数恰好为$-\mu (d)$。

下面考虑如何对于每个$i$求出$c_i$，暴力计算是调和级数$\mathcal O(w\log w)$的，但这样显然不够优秀。

考虑令$cnt_i$为恰好等于$i$的数的个数，那么$c_i=\sum_{i|j}cnt_j$，不难发现这是**狄利克雷后缀和**的形式，直接把狄利克雷前缀和反过来做即可。

时间复杂度$\mathcal O(w \log\log w)$
#### Code
```cpp
int n,tot;
int p[MAXM],a[MAXN],mu[MAXM],c[MAXM],bin[MAXN];
bool np[MAXM];

void Init(int n){
    for(int i = 2;i <= n;i++){
        if(!np[i]) p[++tot] = i, mu[i] = -1;
        for(int j = 1;j <= tot;j++){
            if(i * p[j] > n) break;
            np[i * p[j]] = 1;
            if(i % p[j] == 0) {mu[i * p[j]] = 0; break;}
            mu[i * p[j]] = -mu[i];
        }
    }
}

int main(){
    read(n); for(int i = 1;i <= n;i++) read(a[i]), c[a[i]] += 1;
    bin[0] = 1; for(int i = 1;i <= n;i++) bin[i] = 2ll * bin[i - 1] % MOD;
    int m = *max_element(a + 1,a + 1 + n); Init(m);
    for(int i = 1;i <= tot;i++)
        for(int j = m / p[i];j >= 1;j--)
            c[j] += c[j * p[i]];
    int ans = 0;
    for(int i = 1;i <= m;i++)
        ans = (ans - (ll)mu[i] * (bin[c[i]] - 1) * (n - c[i])) %MOD;
    ans = (ans + MOD) % MOD;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：yijan (赞：3)

## CF 585 E Present for Vitalik the Philatelist

### 公式渲染貌似出了锅，建议在博客查看

好久没在 luogu 发题解了。。作为第 200 紫自然就放到你谷来啦！

写过的题解都在 [这里](https://www.cnblogs.com/yijan/)

题外话：Luogu 的 Latex 怎么换行的啊。。为啥 `\\` 没办法用啊。。只好把一个公式拆成几个写。。

---

我们假设 $ f(x) $ 表示与 $ x $ 互质的数的个数，$ s(x) $ 为 gcd 为 $ x $ 的集合的个数。

那么显然答案就是
$$
\sum_{i > 1} f(i)s(i)
$$
所以我们现在考虑怎么求 $ f $ 和 $ s $ 。

先考虑 $ f $ ，
$$
f(x) = \sum_{i} [gcd(i,x) = 1] c_i
$$
$$
f(x) = \sum_{i} c_i \sum_{d|gcd(i,x)} \mu(d)
$$
$$
f(x) = \sum_{d | x} \mu(d) \sum_{d|i} c_i
$$
我们设 $ t(x) = \sum_{x|i} c_i $ ，不难发现这就是我的 [这篇博客](https://www.cnblogs.com/yijan/p/12356665.html) 里面的第二种卷积，可以筛出来。

那么
$$
f(x) = \sum_{d|x} \mu(d) t(d)
$$
然后又可以用第一种卷积来做，于是我们就跑出了 $ f $ 。

现在考虑怎么求 $ s $ ，我们可以假设 $ s'(x) $ 就是 gcd 为 $ x $ 的倍数的所有集合的个数。我们需要算出 $ x $ 的倍数的数字个数，就是 $ \sum_{x|i} c_i $ ，这个不就是前面的 $ t(x) $ 吗！

所以显然有 
$$
s'(x) = 2^{t(x)} - 1
$$
同时我们知道
$$
s'(x) = \sum_{x|d} s(d)
$$
这个东西就是第二个卷积的反过来的形式，也就是第四种卷积！

所以我们可以三次 $ O(w\log\log w) $ 跑过去啦。

开始看错 $ w $ 大小了。。MLE了两发。。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "queue"
using namespace std;
#define MAXN 10000006
#define P 1000000007
int n;
int A[500006] , c[MAXN] , _[500006] , mu[MAXN] , s[MAXN];
int pri[MAXN] , en , lim;
void sieve( int x ) {
    pri[0] = 1; mu[1] = 1;
    for( int i = 2 ; i <= x ; ++ i ) {
        if( !pri[i] ) pri[++ en] = i , mu[i] = -1;
        for( int j = 1 ; i * pri[j] <= x && j <= en ; ++ j ) {
            pri[i * pri[j]] = 1;
            if( i % pri[j] == 0 ) { mu[i * pri[j]] = 0; break; }
            mu[i * pri[j]] = -mu[i];
        }
    }
}
signed main() {
//    freopen("in","r",stdin);
    cin >> n;
    for( int i = 1 ; i <= n ; ++ i ) scanf("%d",&A[i]) , ++ c[A[i]] , lim = max( lim , A[i] );
    sieve( lim );
    for( int i = 1 ; i <= en ; ++ i )
        for( int j = lim / pri[i] ; j ; -- j )
            c[j] += c[j * pri[i]];
    for( int i = 1 ; i <= lim ; ++ i ) mu[i] *= c[i];
    for( int i = 1 ; i <= en ; ++ i )
        for( int j = 1 ; j * pri[i] <= lim ; ++ j )
            ( mu[j * pri[i]] += mu[j] ) %= P;
    _[0] = 1;for( int i = 1 ; i < 500006 ; ++ i ) _[i] = _[i - 1] * 2 % P;
    for( int i = 1 ; i <= lim ; ++ i ) s[i] = _[c[i]] - 1;
    for( int i = en ; i ; -- i )
        for( int j = 1 ; j * pri[i] <= lim ; ++ j )
            ( s[j] -= s[j * pri[i]] ) %= P;
    int ans = 0;
    for( int i = 2 ; i <= lim ; ++ i ) ( ans += 1ll * s[i] * mu[i] % P ) %= P;
    cout << ( ans + P ) % P << endl;
}
```



---

## 作者：FjswYuzu (赞：1)

设 $a_i$ 为原数组中有多少个数等于 $i$，$b_i$ 为原数组中有多少个集合，使得内部所有元素的 $\gcd$ 为 $i$。那么原题的答案显然等于：

$$
\sum_{i=1}^{10^7} \sum_{j=1}^{10^7} a_ib_j [\gcd(i,j)=1]
$$

先考虑 $b_i$ 怎么求。我们先求出有多少个集合内部元素的 $\gcd$ 为 $i$，将其设为 $t_i$，然后再容斥。显然 $b_i,b_{2i},b_{3i},b_{4i},\cdots$ 都在 $t_i$ 里面得到计算。我们从大向小枚举 $i$，减去其倍数的影响就得到 $b_i$ 了。

最后考虑上面的式子怎么算，从下面开始膜拜人赢 MatrixCascade。

考虑莫比乌斯反演：

$$
\begin{aligned}
\sum_{i=1}^{10^7} \sum_{j=1}^{10^7} a_ib_j [\gcd(i,j)=1] &= \sum_{i=1}^{10^7} \sum_{j=1}^{10^7} a_ib_j \sum_{d|\gcd(i,j)} \mu(d) \\
&= \sum_{d=1}^{10^7} \mu(d) \sum_{i=1}^{\lfloor \frac{10^7}{d} \rfloor} a_{id} \sum_{j=1}^{\lfloor \frac{10^7}{d} \rfloor} b_{jd}
\end{aligned}
$$

筛出 $\mu(i)$ 后暴力计算，时间复杂度 $O(n \ln n)$。

存在 $O(n \log \log n)$ 的做法，可以用狄利克雷前缀和优化 $\mu(d)$ 后面一坨。膜拜 MatrixCascade。因为又卡时间又卡空间就没写了。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD=1e9+7,MAXN=1e7;
const LL WY=LL(MOD)*100000;
int mu[MAXN+5],cnt,prime[MAXN/8],bin[MAXN+5],a[MAXN+5],n,upper,b[MAXN+5];
bool vis[MAXN];
void shai()
{
	mu[1]=1;
	for(int i=2;i<=upper;++i)
	{
		if(!vis[i])	mu[i]=MOD-1,prime[++cnt]=i;
		for(int j=1;j<=cnt && prime[j]*i<=upper;++j)
		{
			vis[i*prime[j]]=true;
			if(i%prime[j])	mu[i*prime[j]]=MOD-mu[i];
			else	break;
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		upper=max(upper,x);
		++a[x];
	}
	bin[0]=1;
	for(int i=1;i<=n;++i)
	{
		LL tmp=bin[i-1]<<1;
		if(tmp>MOD)	bin[i]=tmp-MOD;
		else	bin[i]=tmp;
	}
	b[1]=bin[n]-1;
	for(int i=2;i<=upper;++i)
	{
		LL ds=0;
		for(int j=1;j*i<=upper;++j)	ds+=a[i*j];
		b[i]=bin[ds]-1;
	}
	for(int i=upper;i;--i)
	{
		LL tmp=b[i];
		for(int j=2;j*i<=upper;++j)	tmp+=MOD-b[i*j];
		b[i]=tmp%MOD;
	}
	shai();
	LL ans=0;
	for(int i=1;i<=upper;++i)
	{
		if(!mu[i])	continue;
		LL t=0;
		int s=0;
		for(int j=1;j*i<=upper;++j)	s+=a[i*j],t+=b[i*j];
		ans+=LL(n-s)*t%MOD*(MOD-mu[i]);
		if(ans>WY)	ans%=MOD;
	}
	printf("%lld",ans%MOD);
	return 0;
}
```

---

## 作者：LebronDurant (赞：1)

~~这种水题咋成div1E了？~~ 我来提供一个目前题解里面没有的做法。

首先设值域为$W=1e7$。显然答案等于$\sum\limits_{i=1}^n\sum\limits_{i\notin S,S\neq\emptyset}[gcd(S)\neq1][gcd(S,x)=1]$。两个条件考虑容斥，满足第二个条件减去满足第二个条件且不满足第一个条件的方案数。由于不满足第一个条件一定满足第二个条件，所以直接满足第二个条件-不满足第一个条件。

$\sum\limits_{i=1}^n\sum\limits_{i\notin S,S\neq\emptyset}[gcd(S,x)=1]-\sum\limits_{i=1}^n\sum\limits_{i\notin S,S\neq\emptyset}[gcd(S)=1]$

分开考虑，第一部分：考虑枚举$S\cup x$，那么要求集合大小大于1，对于并集里的每个数都有贡献，系数为$siz(S)$。

$=\sum\limits_{siz(S)>1}[gcd(S)=1]siz(S)$

$=\sum\limits_{d=1}^W\mu(d)\sum\limits_{siz(S)>1,d|gcd(S)}siz(S)$

设$b[d]$为数列中有多少个数能被$d$整除，枚举约数可以在$O(WlnW)$的时间内处理出来。那么考虑枚举集合大小有：

$=\sum\limits_{d=1}^W\mu(d)\sum\limits_{j=2}^{b[d]}C_{b[d]}^j j$

设$f(n)=\sum\limits_{i=1}^nC_n^ii$，考虑第$n$个数选或不选，有$f(n)=2f(n-1)+2^{n-1}$，可$O(W)$递推预处理出来。上式后半部分就是$f(b[d])-b[d]$，带入即可。前半部分时间复杂度$O(W)$。

后半部分，考虑枚举集合$S$，每个不在集合里的数都有贡献，系数为$n-siz(S)$。

$=\sum\limits_{S\neq\emptyset}[gcd(S)=1](n-siz(S))$

$=\sum\limits_{d=1}^W\mu(d)\sum\limits_{d|gcd(S)}(n-siz(S))$

$=\sum\limits_{d=1}^W\mu(d)\sum\limits_{j=1}^{b[d]}C_{b[d]}^j(n-j)$

$=\sum\limits_{d=1}^W\mu(d)(n\sum\limits_{j=1}^{b[d]}C_{b[d]}^j-\sum\limits_{j=1}^{b[d]}C_{b[d]}^jj)$

$=\sum\limits_{d=1}^W\mu(d)(n(2^{b[d]}-1)-f(b[d]))$

后半部分时间复杂度$O(W)$，总时间复杂度$O(WlnW)$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;
#define N 10000002
typedef long long ll;
const int p=1e9+7;
int prim[N],cnt,mu[N],n,a[1000002],f[1000002],bin[1000002],b[N],ct[N];
bool isp[N];
int main()
{
    for(int i=2;i<=10000000;i++)isp[i]=1;mu[1]=1;
    for(int i=2;i<=10000000;i++)
    {
        if(isp[i])prim[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&prim[j]*i<=10000000;j++)
        {
            isp[prim[j]*i]=0;
            if(i%prim[j]==0){mu[prim[j]*i]=0;break;}
            mu[prim[j]*i]=-mu[i];
        }
    }
    scanf("%d",&n);for(int i=1;i<=n;i++)scanf("%d",&a[i]),ct[a[i]]++;
    bin[0]=1;for(int i=1;i<=n;i++)bin[i]=2ll*bin[i-1]%p;
    for(int i=1;i<=n;i++)f[i]=(2ll*f[i-1]%p+bin[i-1])%p;
    for(register int i=1;i<=10000000;i++)for(register int j=i;j<=10000000;j+=i)b[i]+=ct[j];
    int ans=0;
    for(int i=1;i<=10000000;i++)if(mu[i])
    {
        if(mu[i]==1)
        {
            ans=(ans+f[b[i]])%p;
            ans=(ans-b[i]+p)%p;
            ans=(ans-1ll*n*(bin[b[i]]-1)%p+p)%p;
            ans=(ans+f[b[i]])%p;
        }
        else
        {
            ans=(ans-f[b[i]]+p)%p;
            ans=(ans+b[i])%p;
            ans=(ans+1ll*n*(bin[b[i]]-1)%p)%p;
            ans=(ans-f[b[i]]+p)%p;
        }
    }printf("%d\n",ans);
}

```


---

## 作者：HenryHuang (赞：0)

# 「CF585E」 Present for Vitalik the Philatelist

[传送门](https://www.luogu.com.cn/problem/CF585E)

我们可以考虑枚举 $S'=S\cup\{x\}$，那么显然有 $\gcd\{S'\}=1$。

那么我们从里面可以选一个数出来作为 $x$，共有 $|S'|$ 种可能，我们记为 $(x,S)$。

但是这样显然会计算到一些不合法的情况，考虑统计。

对于一个集合 $S$，若其 $\gcd$ 为 $1$，则再任意添加一个数 $\gcd$ 仍为 $1$，这样的二元组显然是不合法的，共有 $n-|S|$ 种可能。

所以对于一个 $\gcd$ 为 $1$ 的集合 $S$，其对答案的贡献就是 $|S|-(n-|S|)=2|S|-n$。

设给出的数的集合为 $U$，故答案可表示为
$$
\sum_{S\subseteq U,S\neq \varnothing}[\gcd \{S\}=1](2|S|-n)
$$
显然可以考虑莫比乌斯反演，于是有
$$
\sum_{d}\mu(d)\sum_{S\subseteq U\cap\{x|x=kd,k\in \mathbb{Z}\},S\neq \varnothing}(2|S|-n)
$$
令 $T=U\cap\{x|x=kd,k\in \mathbb{Z}\}$，我们的问题就变为了计算
$$
\sum_{S\subseteq T,S\neq \varnothing}(2|S|-n)
$$
首先这个不等于空集很烦，我们可以把它加上最后再减去，变为
$$
n+2\sum_{S\subseteq T}|S|-\sum_{S\subseteq T}n
$$
后面那部分很好算，共有 $2^{|T|}$ 种集合，答案即为 $2^{|T|}n$。

前一部分可以考虑计算每个数对答案的贡献，枚举选某个数（共 $|T|$ 种可能），剩下的 $|T|-1$ 个元素都是选或不选，故答案为 $2(2^{|T|-1}|T|)=2^{|T|}|T|$。

然后问题就变成了如何求 $T$。

这个东西可以直接分解质因数，也可以用 $\text{Dirichlet}$ 后缀和，在此不再赘述。

总复杂度大概是 $O(V\log_2\log_2V+n)$ 的，其中 $V$ 表示值域。

贴代码

```cpp
/*---Author:HenryHuang---*/
/*---Never Settle---*/
/*---Never Enough---*/
#include<bits/stdc++.h>
#define module(x) ((x)>=p?((x)-p):(x))
using namespace std;
const int maxn=1e7+5;
const int p=1e9+7;
int pri[maxn],pp[maxn],mu[maxn],cnt;
int p2[maxn];
int sum[maxn];
void init(int mx){
	mu[1]=1;
	for(int i=2;i<=mx;++i){
		if(!pp[i]) pri[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pri[j]<=mx;++j){
			pp[i*pri[j]]=1;
			if(i%pri[j]==0){
				mu[i*pri[j]]=0;
				break;
			}
			else mu[i*pri[j]]=-mu[i];
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	p2[0]=1;
	int mx=0;
	for(int i=1;i<=n;++i){
		int x;cin>>x;mx=max(mx,x);
		++sum[x];
		p2[i]=module(p2[i-1]<<1);
	}
	init(mx);
	for(int i=1;i<=cnt;++i)
		for(int j=mx/pri[i];j;--j)
			sum[j]+=sum[j*pri[i]];
	int ans=0;
	for(int i=1;i<=mx;++i){
		if(mu[i]){
			int tmp=1ll*(1ll*p2[sum[i]]*(sum[i]-n+p)+n)%p;
			if(mu[i]>0) ans=module(ans+tmp);
			else ans=module(ans-tmp+p);
		}
	}
	cout<<module(ans+p)<<'\n';
	return 0;
}
```





---

## 作者：tzc_wk (赞：0)

[Codeforces 题目传送门](https://codeforces.com/contest/585/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF585E)

一道不算太难的 D1E 罢……虽然我不会做/kk

u1s1 似乎这场 Div1 挺水的？F 就是个 AC 自动机板子还被评到了 3k2……

首先我们注意到对于固定的 $x$ 及集合 $S$，如果 $\gcd(S)>1,\gcd(x,\gcd(S))=1$ 那么必然有 $x\notin S$，否则显然有 $\gcd(S)=\gcd(x,\gcd(S))$ 可立即推出矛盾，也就是说我们可以直接忽略这个条件。我们考虑直接枚举 $\gcd(S)=x$，设 $f_x$ 表示 $\gcd(S)=x$ 的集合 $S$，$g_x$ 表示 $a_{1...n}$ 中有多少个数与 $x$ 互质，那么这种情况对答案的贡献显然为 $f_xg_x$，累加一下即可，即 $ans=\sum\limits_{x>1}f_xg_x$

接下来考虑怎样求 $f_x,g_x$，首先是 $f_x$，按照套路我们设 $c_x$ 为可重集中 $x$ 出现了多少次，这样我们可以枚举值 instead of 下标，即 $f_x=\sum\limits_{y}[\gcd(x,y)=1]c_y$，我们按照套路进行莫反：
$$
\begin{aligned}
f_x&=\sum\limits_{y}[\gcd(x,y)=1]c_y\\
&=\sum\limits_{y}\sum\limits_{d\mid x,d\mid y}\mu(d)c_y\\
&=\sum\limits_{d\mid x}\mu(d)\sum\limits_{d\mid y}c_y
\end{aligned}
$$
接下来考虑 $g_x$，首先直接求是不容易的，不过按照套路我们设 $h_x=\sum\limits_{x\mid y}g_y$，即 $x\mid\gcd(S)$ 的集合 $S$ 个数。那么关于，显然所有是 $x$ 的倍数的数都可以被加入进 $S$ 中，如果我们设 $t_x$ 表示可重集中有多少个数是 $x$ 的倍数，那么显然有 $h_x=2^{t_x}$。而显然 $t_x=\sum\limits_{x\mid y}c_y$，故上面 $f_x$ 的式子又可以改写为 $f_x=\sum\limits_{d\mid x}\mu(d)t_d$

因此接下来我们只用实现三个操作：

- 已知 $c_x$ 求 $t_x=\sum\limits_{x\mid y}c_y$
- 已知 $\mu(d)t_d$ 求 $f_x=\sum\limits_{d\mid x}\mu(d)t_d$
- 根据 $h_x$ 即 $h_x=\sum\limits_{x\mid y}g_y$ 反解出 $g_x$

不难发现这三个操作实际上是等价的，都可以写成类似于给定序列 $a$ 求序列 $b$ 满足 $b_i=\sum\limits_{j\mid i}a_j$ 的形式。考虑什么样的 $i,j$ 满足 $a_i$ 会对 $b_j$ 产生贡献，我们将 $i,j$ 分解质因数，那么对于质因子 $p$，如果 $i$ 的质因数分解式中 $p$ 的次数为 $\alpha$，$j$ 的质因数分解式中 $p$ 的次数为 $\beta$ 那么必须有 $\alpha\ge\beta$，因此可以将这玩意儿看作一个 $\pi(n)$ 维的高维前缀和，按照高维前缀和的套路跑一下即可，时间复杂度 $n\log\log n$，据说这玩意儿有个专门的名字叫 dirichlet 狄利克雷前缀和？

```cpp
const int MAXN=5e5;
const int MAXM=1e7;
const int MOD=1e9+7;
int n,pw[MAXN+5],c[MAXM+5],f[MAXM+5],g[MAXM+5];
int pr[MAXM/10+5],pcnt=0,mu[MAXM+5];
bitset<MAXM+5> vis;
void sieve(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){pr[++pcnt]=i;mu[i]=-1;}
		for(int j=1;j<=pcnt&&pr[j]*i<=n;j++){
			vis[pr[j]*i]=1;
			if(i%pr[j]==0) break;
			else mu[i*pr[j]]=-mu[i];
		}
	}
}
int main(){
	scanf("%d",&n);pw[0]=1;sieve(MAXM);
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%MOD;
	for(int i=1,x;i<=n;i++) scanf("%d",&x),c[x]++;
	for(int i=1;i<=pcnt;i++) for(int j=MAXM/pr[i];j;j--) c[j]+=c[j*pr[i]];
	for(int i=1;i<=MAXM;i++) f[i]=pw[c[i]]-1,g[i]=c[i]*mu[i];
	for(int i=1;i<=pcnt;i++) for(int j=1;j*pr[i]<=MAXM;j++) g[j*pr[i]]+=g[j];
	for(int i=1;i<=pcnt;i++) for(int j=1;j*pr[i]<=MAXM;j++) f[j]=(f[j]-f[j*pr[i]]+MOD)%MOD;
	int ans=0;for(int i=2;i<=MAXM;i++) ans=(ans+1ll*g[i]*f[i])%MOD;
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Fading (赞：0)

给一个只用 $2$ 次 FMT 的题解...看不太懂其他人怎么做的...

首先枚举数$x$，这个大家都想得到。

设$f_i$表示所有非空集合$\gcd=i$的方案数。

$\text{cnt}_i$表示数组$i$的个数。

所以枚举$\gcd$，答案就是

$$\sum_{i=1}^{\text{MAX}}\text{cnt}_i\sum_{\gcd(d,i)=1}f_d$$

经验丰富选手看一眼就知道这个不太能做，也没有什么奇怪的数论性质，于是来一次基本容斥：

$$=\sum_{i=1}^{\text{MAX}}\text{cnt}_i
(\sum_{d=1}f_d-\sum_{\gcd(d,i)\not=1}f_d)$$


$$=\sum_{i=1}^{\text{MAX}}\text{cnt}_i
(2^n-1-\sum_{\gcd(d,i)\not=1}f_d)$$


值域很大很大，考虑如何$O(1)$计算

$$\sum_{\gcd(d,i)\not=1}f_d$$

$f$怎么计算？容斥或者莫比乌斯反演。我一开始是直接用容斥的（虽然本质一样），这里写个莫比乌斯反演的，非常方便：

设

$$F_i=\sum_{i|d}f_d$$

表示所有非空集合$i|\gcd$的方案数。显然

$$=2^{\sum_{i|d}\text{cnt}_d}$$

然后用反演定理得

$$f_i=\sum_{i|d}\mu(\frac di)2^{\sum_{i|d}\text{cnt}_d}$$

直接计算是$O(n\ln n)$的，很不优秀，先用求 FMT(and) 点值的方法算出小$\sum$，再求$2$的幂得到$F$，最后用求 IFMT(and) 点值的方法求出$f$，$O(n\log\log n)$。

事实上不需要求$f$。我们继续看：

$$\sum_{\gcd(d,i)\not=1}f_d$$

直接做也有些棘手，继续考虑它的数论意义：

设

$$X=\prod p_j$$

即其质因子的乘积。

那么
$$\sum_{\gcd(d,i)\not=1}f_d=\sum_{\gcd(d,X)\not=1}f_X$$

就是指所有与$X$不互质的数的个数。我们知道这个东西等价于所有质因子的倍数的交集的$f$之和，而这个容斥系数我们又很熟悉，就是$-\mu$。那么：

$$\sum_{\gcd(d,i)\not=1}f_d=\sum_{d\not=1,d|X}-\mu(d)\sum_{d|i}f_i$$

$$=\sum_{d\not=1,d|X}-\mu(d)F_d$$

直接计算是$O(n\ln n)$的，很不优秀，用求 FMT(or) 点值的方法（[狄利克雷前缀和](https://www.luogu.com.cn/problem/P5495)）可以做到$O(n\log\log n)$。其实可以把第一次求出的$F$直接拿来乘$-\mu$再做一次就好了。所以不需要求$f$。

一次 FMTand，一次 FMTor ，真是一道烧脑题，不过思路还挺顺的。时间复杂度$O(n\log\log n)$，但是跑得很慢很慢？

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 1000000007
using namespace std;
#define gc getchar
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
int cnt[10101010],X[10101010];
bool vis[10101010];
ll F[10101010],pw2[1101010];
int tot,p[1010101],a[1010101],lim,mu[10101010];
inline void seive(int n){
	for (int i=2;i<=n;i++){
		if (!vis[i]) p[++tot]=i,X[i]=i,mu[i]=-1;
		for (int j=1;j<=tot;j++){
			if (1ll*p[j]*i>n) break;
			vis[p[j]*i]=1,mu[p[j]*i]=-mu[i];
			if (i%p[j]==0){
				mu[i*p[j]]=0;X[i*p[j]]=X[i];break;
			}
			else X[i*p[j]]=X[i]*p[j];
		}
	}
}
inline void FMTand(ll *F,int lim){
	for (int i=1;i<=tot;i++){
    	for (int j=lim/p[i];j;j--){
    		F[j]=(F[j]+F[j*p[i]]%ljc)%ljc;
		}
	}
}
inline void FMTor(ll *F,int lim){
	for (int i=1;i<=tot;i++){
    	for (int j=1;j*p[i]<=lim;j++){
    		F[j*p[i]]=(F[j*p[i]]+F[j])%ljc;
		}
	}
}
signed main(){
	ll n=read();
	pw2[0]=1;
	for (int i=1;i<=n;i++) pw2[i]=1ll*pw2[i-1]*2%ljc;
	for (int i=1;i<=n;i++){
		a[i]=read();cnt[a[i]]++;
		lim=max(lim,a[i]);F[a[i]]=cnt[a[i]]; 
	}
	seive(lim);
	FMTand(F,lim);
	ll ONE=pw2[F[1]]-1,_=0;
	for (int i=2;i<=lim;i++){
		ONE=(ljc+ONE+mu[i]*(pw2[F[i]]-1%ljc)%ljc)%ljc;
	}
	for (int i=1;i<=lim;i++){
		F[i]=(ljc+(pw2[F[i]]-1)*(ljc-mu[i])%ljc)%ljc;
	}
	FMTor(F,lim);
	for (int i=1;i<=lim;i++){
		_=(_+1ll*cnt[i]*(pw2[n]-1-ONE-F[X[i]]+2*ljc)%ljc)%ljc;
	}
	cout<<_;
	return 0;
}

```



---

