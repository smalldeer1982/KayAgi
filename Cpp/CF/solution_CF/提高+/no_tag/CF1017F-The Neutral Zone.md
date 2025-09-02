# The Neutral Zone

## 题目描述

注意：本题的内存限制不同寻常！

战争结束后，中立区被毁坏的城市得到了重建，孩子们也重返校园。

战争改变了世界，也改变了教育。在那些艰难的日子里，诞生了一个新的数学概念。

众所周知，对数函数可以表示为：
$$
\log(p_1^{a_1}p_2^{a_2}\ldots p_k^{a_k}) = a_1 \log p_1 + a_2 \log p_2 + \ldots + a_k \log p_k
$$
其中 $p_1^{a_1}p_2^{a_2}\ldots p_k^{a_k}$ 是一个整数的质因数分解。问题在于，这个函数在定义中用到了自身，这也是它难以计算的原因。

因此，中立区的数学家们发明了这样一个概念：
$$
\text{exlog}_f(p_1^{a_1}p_2^{a_2}\ldots p_k^{a_k}) = a_1 f(p_1) + a_2 f(p_2) + \ldots + a_k f(p_k)
$$

注意，$\text{exlog}_f(1)$ 总是等于 $0$。

对于任意函数 $f$，这个概念对孩子们来说太难了。因此老师告诉他们，在日常使用中，$f$ 只能是次数不超过 $3$ 的多项式（即 $f(x) = Ax^3 + Bx^2 + Cx + D$）。

“下课了！别忘了做作业！”作业如下：
$$
\sum_{i=1}^n \text{exlog}_f(i)
$$

请帮助孩子们完成作业。由于答案可能非常大，你需要输出答案对 $2^{32}$ 取模的结果。

## 说明/提示

在第一个样例中：

$\text{exlog}_f(1) = 0$

$\text{exlog}_f(2) = 2$

$\text{exlog}_f(3) = 3$

$\text{exlog}_f(4) = 2 + 2 = 4$

$\text{exlog}_f(5) = 5$

$\text{exlog}_f(6) = 2 + 3 = 5$

$\text{exlog}_f(7) = 7$

$\text{exlog}_f(8) = 2 + 2 + 2 = 6$

$\text{exlog}_f(9) = 3 + 3 = 6$

$\text{exlog}_f(10) = 2 + 5 = 7$

$\text{exlog}_f(11) = 11$

$\text{exlog}_f(12) = 2 + 2 + 3 = 7$

$\sum_{i=1}^{12} \text{exlog}_f(i) = 63$

在第二个样例中：

$\text{exlog}_f(1) = 0$

$\text{exlog}_f(2) = (1 \times 2^3 + 2 \times 2^2 + 3 \times 2 + 4) = 26$

$\text{exlog}_f(3) = (1 \times 3^3 + 2 \times 3^2 + 3 \times 3 + 4) = 58$

$\text{exlog}_f(4) = 2 \times \text{exlog}_f(2) = 52$

$\sum_{i=1}^4 \text{exlog}_f(i) = 0 + 26 + 58 + 52 = 136$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
12 0 0 1 0
```

### 输出

```
63
```

## 样例 #2

### 输入

```
4 1 2 3 4
```

### 输出

```
136
```

# 题解

## 作者：Prean (赞：6)

~~这种板子题怎么能没有min25筛的题解呢？？？~~

题意：给定一个完全和性函数，求其前缀和。~~其实普通和性函数也能做就是了~~
$$ \sum_{i=1}^n f(i) $$
类似积性函数，我们把这玩意儿在质数幂处的值之和
$$ \sum_{i=1}^n \sum_{p^k|i,[\gcd(p^{k+1},i)=p^k]}kf(p) $$
$$ \sum_pf(p)g(n,p) $$
其中 $ g(n,p) $ 为 $ \sum_{i=1}^n \sum_k k[p^k|i \And gcd(p^{k+1},i)=p^k] $。

一个很明显的结论是 $ g(n,p)=n<p?g(\lfloor \frac n p \rfloor,p)+\lfloor \frac n p \rfloor $。

根号分治一下。当 $ n < p^2 $ 时， $ g(n,p)=\lfloor \frac n p \rfloor $。

于是：
$$ \sum_p^{\sqrt n}f(p)g(p)+\sum_{i=\sqrt n+1}^n \lfloor \frac n i \rfloor [\text {i is prime}]f(i) $$

后者相当于对于 $ [1,\sqrt n] $ 中的 $ x $ 求 $ \sum_{i=1}^{\lfloor \frac n x \rfloor}f(p) $。因为 $ f $ 是一个多项式，所以我们相当于需要求出 $ \sum_p^{\lfloor \frac n x \rfloor} p^k $。

时间复杂度 $ O(\frac {n^{\frac 3 4} } {\log n}) $，空间复杂度 $ O(\sqrt n) $。

但是 $ n \leq 3 \times 10^8 $，而 $ \sum_{i=1}^n n^2=\frac {n(n+1)(2n+1)} 6 $，$ 6 $ 在模 $ 2^{32} $ 的意义下没有逆元，而 $ n^3 $ 破了 $ 2e25 $，该怎么计算呢？

有一种办法是计算 $ 3 $ 在模 $ 2^{32} $ 意义下的逆元，另一种办法是对 $ n\%3 $ 的情况进行分类讨论。

这份代码在 CF 上面是 [rk2](https://codeforces.com/contest/1017/status/F?order=BY_CONSUMED_TIME_ASC)，因为 rk1 是一个不讲武德的特判数据的人。。。
```cpp
#include<cstdio>
#include<cmath>
typedef unsigned uint;
const uint M=17325;
uint pri[2000],p1[2000],p2[2000],p3[2000],s1[2000],s2[2000],s3[2000];
uint n,S,A,B,C,D,ans,top,id1[M],id2[M],pos[M];double invp[2000];
uint g0[M<<1],g1[M<<1],g2[M<<1],g3[M<<1];
inline uint f(const uint&n,const uint&p,const double&invp){
	return n<p?0:f(n*invp,p,invp)+(uint)(n*invp);
}
inline void Get(const uint&x,const uint&n){
	g0[x]=n;g1[x]=n*(n+1ull)/2;g3[x]=g1[x]*g1[x];
	g2[x]=n%3==1?g1[x]*(2ull*n+1)/3:((uint)(n*(n+1ull)/6))*(2ull*n+1);
	--g0[x];--g1[x];--g2[x];--g3[x];
}
inline void sieve(){
	register uint i,j,x;Get(1,n);
	for(i=2;i<=S;++i){
		Get(i,n/i);
		if(!pos[i]){
			pri[++top]=i;invp[top]=1./i+1e-15;pos[i]=top;
			s1[top]=s1[top-1]+(p1[top]=pri[top]);
			s2[top]=s2[top-1]+(p2[top]=pri[top]*p1[top]);
			s3[top]=s3[top-1]+(p3[top]=pri[top]*p2[top]);
			ans+=(A*p3[top]+B*p2[top]+C*p1[top]+D)*f(n,i,1./i+1e-15);
		}
		for(j=1;j<=top&&(x=i*pri[j])<=S;++j)if((pos[x]=j)==pos[i])break;
	}
	for(i=1;i<S;++i)Get(S+i,i);
	if(S*S!=n)Get(S<<1,i);
}
signed main(){
	register uint i,j,x,f,P1,P2,P3,S1,S2,S3;
	scanf("%u%u%u%u%u",&n,&A,&B,&C,&D);S=sqrt(n);f=S*S==n;sieve();
	for(i=1;i<=top;++i){
		P1=p1[i];P2=p2[i];P3=p3[i];S1=s1[i-1];S2=s2[i-1];S3=s3[i-1];
		for(j=1;(x=pri[i]*j)<=S;++j){
			g0[j]+=i-1-g0[x];
			g1[j]+=P1*(S1-g1[x]);
			g2[j]+=P2*(S2-g2[x]);
			g3[j]+=P3*(S3-g3[x]);
		}
		for(;pri[i]*(x=pri[i]*j)<=n&&j<=S;++j){
			x=n/x;
			g0[j]+=i-1-g0[S+x];
			g1[j]+=P1*(S1-g1[S+x]);
			g2[j]+=P2*(S2-g2[S+x]);
			g3[j]+=P3*(S3-g3[S+x]);
		}
		for(j=S-f;pri[i]*pri[i]<=j;--j){
			x=j*invp[i];
			g0[S+j]+=i-1-g0[S+x];
			g1[S+j]+=P1*(S1-g1[S+x]);
			g2[S+j]+=P2*(S2-g2[S+x]);
			g3[S+j]+=P3*(S3-g3[S+x]);
		}
	}
	g0[S+1]=top;g1[S+1]=s1[top];g2[S+1]=s2[top];g3[S+1]=s3[top];
	for(i=1;i<=S;++i){
		g3[i]-=g3[i+1];g2[i]-=g2[i+1];g1[i]-=g1[i+1];g0[i]-=g0[i+1];
		ans+=i*(A*g3[i]+B*g2[i]+C*g1[i]+D*g0[i]);	
	}
	printf("%u",ans);
}
```

---

## 作者：wsyhb (赞：5)

## 前言

为什么题解区的神仙们都是拿 bitset 卡过去的呀……

提供一种**不用 bitset，时空都不卡常，还算小清新**的做法。

------------

**UPD**（2021.9.17 14:33）：

突然想起自己把埃氏筛复杂度中的 $\log\log$ 写成了 $\ln$，已修正~

顺便看了一眼官方题解，原来官方题解就是拿 bitset 压的空间……差评！

话说回来那我这个做法的理论时间复杂度比官方题解还低一些？（不过是 $\log\log{n} \to \log\log{\sqrt{n}}$，差不多啦）

## 题解

### 答案的转化

首先，一个显然的结论：

$$\operatorname{exlog}_f(ab)=\operatorname{exlog}_f(a)+\operatorname{exlog}_f(b), \quad \forall a,b \in \mathbb{N}^{+}$$

于是有：

$$\sum_{i=1}^{n}\operatorname{exlog}_f(i)=\operatorname{exlog}_f(n!)$$

在求 $\operatorname{exlog}_f(n!)$ 以前，我们先引入一个结论，并给出证明。

### 结论

对于质数 $p$，$n!$ 的质因数分解式中 $p$ 的指数为 $\sum_{i=1}^{\infty}\lfloor \dfrac{n}{p^i} \rfloor$。


### 证明

$\lfloor \dfrac{n}{p^i} \rfloor$ 的意义：$1$ 到 $n$ 中 $p^i$ 的倍数的个数。

考虑 $[1,n]$ 中的每一个 $x$，设 $p^k \mid x$ 且 $p^{k+1} \nmid x$。（即：$x$ 的质因数分解式中 $p$ 的指数为 $k$）

由于 $x$ 是 $p^1,p^2,\cdots,p^k$ 的倍数，所以 $x$ 在 $\sum_{i=1}^{\infty}\lfloor \dfrac{n}{p^i} \rfloor$ 中被统计了 $k$ 次。

而 $n!$ 的质因数分解式中 $p$ 的指数，等于 $[1,n]$ 中所有 $x$ 的质因数分解式中 $p$ 的指数之和，故得证。

### 答案的求解

$$\operatorname{exlog}_f(n!)=\sum_{1 \le p \le n, p \; \text{是质数}}(f(p) \cdot \sum_{j=1}^{\infty}\lfloor \dfrac{n}{p^j} \rfloor)$$

使用**线性筛**筛出 $n$ 以内的质数，然后对于每个质数暴力求 $\sum_{j=1}^{\infty}\lfloor \dfrac{n}{p^j} \rfloor$。

由于质数个数是 $O(\dfrac{n}{\ln{n}})$ 级别的，而 $\sum_{j=1}^{\infty}\lfloor \dfrac{n}{p^j} \rfloor$ 的单次求解是 $O(\log_p{n})$ 的，故总时间复杂度为 $O(n)$。

------------

等等，你不会以为这道题就完了吧——

> **Notice: unusual memory limit!**

本题 $n \le 3 \times 10^8$，空间限制 16 MiB。

拿个计算器算一下，可以知道大小为 $n$ 的 bool 数组要花费 286 MiB 左右——也就是说，即便你不存储质数（换用**埃氏筛**就可以不存储质数），你都没有空间筛质数……

那怎么办呢？

首先，由于线性筛需要存储质数，可以不考虑它了。

其次，我们考虑**区间筛质数**——这是一个经典问题：

> 求区间 $[L,R]$ 中的质数，其中 $1 \le L \le R \le 10^{12}$ 且 $R-L+1 \le 10^6$。

将**根号判断质数**和埃氏筛的思想一结合，我们就得到了这一经典问题的做法：

> 线性筛筛出 $\lfloor \sqrt{R} \rfloor$ 以内的质数 $p$，并枚举每个 $p$ 在区间 $[L,R]$ 中的倍数，将这些倍数打上标记，最终没有标记的就是质数。

> 由于一个数的倍数是均匀分布的，所以区间 $[L,R]$ 中 $p$ 的倍数的个数，几乎与区间 $[1,R-L+1]$ 中 $p$ 的倍数的个数相同，即可以视作 $\lfloor \dfrac{R-L+1}{p} \rfloor$。

> 那么枚举倍数这一部分的时间复杂度就与埃氏筛的时间复杂度相同，总时间复杂度为 $O(\sqrt{R}+(R-L+1)\log{\log{(R-L+1)}})$。

于是，对于本题，我们可以**线性筛预处理出 $\lfloor \sqrt{n} \rfloor$ 以内的质数，然后用上述做法分段筛质数**，并将筛得的质数的贡献加入答案。

总时间复杂度为 $O(n\log{\log{\sqrt{n}}})$。（该时间复杂度分析和“区间筛质数”的复杂度分析非常类似，留作习题）

总空间复杂度为 $O(\sqrt{n}+B)$，其中 $B$ 是块长。

## 代码

为了方便，这份代码的块长取的是 $\sqrt{n}$。（这样就直接用线性筛的 bool 数组了）

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,A,B,C,D,R;
unsigned int ans;
inline unsigned int f(unsigned int x)
{
	return ((A*x+B)*x+C)*x+D;
}
inline void calc(int p)
{
	int expo=0,now=n/p;
	while(now)
	{
		expo+=now;
		now/=p;
	}
	ans+=expo*f(p);
}
const int max_R=17320+5;
bool mark_p[max_R];
int prime[max_R],cnt;
inline void init()
{
	for(int i=2;i<=R;++i)
		mark_p[i]=true;
	for(int i=2;i<=R;++i)
	{
		if(mark_p[i])
		{
			prime[++cnt]=i;
			calc(i);
		}
		for(int j=1;j<=cnt&&i*prime[j]<=R;++j)
		{
			mark_p[i*prime[j]]=false;
			if(i%prime[j]==0)
				break;
		}
	}
}
int main()
{
	scanf("%d%d%d%d%d",&n,&A,&B,&C,&D);
	R=sqrt(n);
	init();
	int now=R;
	while(now<n)
	{
		int l=now+1,r=min(now+R,n);
		for(int i=l;i<=r;++i)
			mark_p[i-now]=true;
		for(int i=1;i<=cnt;++i)
		{
			int p=prime[i];
			for(int j=(l+p-1)/p*p;j<=r;j+=p)
				mark_p[j-now]=false;
		}
		for(int i=l;i<=r;++i)
		{
			if(mark_p[i-now])
				calc(i);
		}
		now=r;
	}
	printf("%u\n",ans);
	return 0;
}
```

---

## 作者：皎月半洒花 (赞：4)

首先要有个 Observation，大概就是说可以发现对于每个质数的幂次 $a_i$，作为乘法系数是独立的。所以会有 $\text{exlog}_f(a\cdot b)=\text{exlog}_f(a)+\text{exlog}_f(b)$ 。但是这样直接筛的复杂度并不能过，空间会爆。然后考虑如何优化这一过程。

大概是说可以考虑每个质因数产生的贡献，彼此之间是**线性无关**的 ，所以可以分别考虑每个质数幂的贡献。具体的，我们只需要求出所有的质数以及质数的幂对答案的贡献就好了，这部分为了卡空间可以用埃氏筛。

但是发现还是过不去。因为埃氏筛的复杂度太高了。不过仔细分析一波，发现慢在诸如 $2,3,5,7$ 这种比较小的质因子 $p$，会进行 $\left\lfloor\dfrac{n}{p}\right\rfloor$ 次筛除操作。于是可以先暴力跑出 $2,3,5,7$ 的贡献，然后算其他的时就可以不考虑这些数了。

但是发现这样空间还是会有点问题。于是可以用 `bitset ` + 合并状态来压缩。合并状态的原理是刨除了所有 $2,3$ 的倍数之后，空间就可以只开 $\dfrac{1}{3}$ 。

个人觉得这题能放到 F，唯一的原因就是因为需要十分优秀的卡常 and 卡空间技术。

```cpp
#include <bitset>

#include <cstdio>

const int N = 100000005 ;

using std :: bitset ;

typedef long long ll ;

typedef unsigned int lint ;

int n ;
bitset <N> vis ;
int A, B, C, D ;

lint ans ;

inline bool chk(int x){
	return ((!(x & 1)) || (x % 3 == 0) || (x % 5 == 0)) ; 
}
lint calc(int p){
    return 1u * A * p * p * p + 1u * B * p * p + 1u * C * p + D ;
}
lint solve(int p){
    lint ret = 0, v = calc(p) ;
    for (ll x = p ; x <= n ; x *= p)
        ret += 1u * (n / x) * v ; return ret ;
}
int main(){
    scanf("%d", &n) ; ans = 0 ;
    scanf("%d%d%d%d", &A, &B, &C, &D) ;
	if (n >= 2) ans += solve(2) ; 
	if (n >= 3) ans += solve(3) ;
	if (n >= 5) ans += solve(5) ; 
    for (int i = 7 ; i <= n ; ++ i){
		if (chk(i)) continue ;
        if (vis[i / 3]) continue ; ans += solve(i) ; //printf("%u\n", ans) ;
        for (int j = i + i ; j <= n ; j += i) 
			if (!chk(j)) vis[j / 3] = 1 ;
    }
    printf("%u\n", ans) ; return 0 ;
}

```


---

## 作者：Lugar (赞：2)

这个Sigma其实可以分开算，每一个质数筛一遍就好了。每次把一次方的倍数、两次方的倍数……筛掉就好了，详情参见代码

这个题目的内存16M。~~卡的也是真的恶心~~

所以可以考虑用bitset压一下，然后发现还是不行~~~

最后发现~~（网上一波参考）~~可以先把2和3的筛掉然后再除以3下取整，就可以达到要求的空间限制

然后对2^32取模，可以祭出一手
**
自然溢出** 只要用unsigned int 就可以达到效果
```cpp
#include<bits/stdc++.h>
#define SC scanf
typedef unsigned int uint;
using namespace std;

bitset<100000001> bs;
uint n,A,B,C,D,ans;

void zad(uint x)//这里就是筛x的贡献的部分
{
    uint sum = A*x*x*x+B*x*x+C*x+D,o = n;
    while(o/x) ans += sum * (o /= x);
    return;
}

int main()
{
    SC("%u %u %u %u %u",&n,&A,&B,&C,&D);
    zad(2),zad(3);
    for(uint i = 5,ch = 2; i <= n; i += ch, ch = 6 - ch)
    {
        if(bs[i/3]) continue;
        zad(i);
        if(i > n/i) continue;
        for(uint j = i*i , v = ch; j <= n; j += v*i,v = 6 - v)
            bs[j/3] = 1;
    }
    printf("%u",ans);
}
```

---

## 作者：Argon_Cube (赞：1)

The solution of the problem is really simple (the code maybe not).

* **【题目链接】**

[Link:CF1017F](https://www.luogu.com.cn/problem/CF1017F)

* **【解题思路】**

思路和代码都极为暴力，唯一一道一分钟不到就想出来的 $2500$。

首先我们发现，每个质数的贡献独立，考虑单独计算每个质数的贡献。

显然质数 $p$ 的贡献为

$$f(p)\sum_{k=1}^{p^k\leq n}\left\lfloor\frac n{p^k}\right\rfloor$$

假如全部质数都筛好了，我们对于每个质数直接暴力计算它的贡献，复杂度都差不多 $\mathrm O(n)$。唯一的问题是怎么筛出来这些质数。

显然这并不是个问题，因为我们有 Wheel Factorization。

于是直接把 [SP6488](https://www.luogu.com.cn/problem/SP6488) 的代码复制过来就行了。

* **【实现细节】**

这题卡空间？

卡的跟没卡一样。把块长少乘一两个质数就行了。

然后我们发现存不下那么多质数。

为啥要存那么多，存 $\sqrt n$ 以下的不就行了？其它的边筛边做不用存。

块长少乘两个质数，最大点 $960\rm ms,380KB$。

对了，官方题解用的就是块长为 $2\times 3=6$ 的 Wheel Factorization。

* **【代码实现】**

```cpp
//以下代码的块长为前6个质数的乘积。
#include <iostream>
#include <bitset>
#include <array>

using namespace std;

constexpr int		wheel=2*3*5*7*11*13,wheeled=2*4*6*10*12;
array<int,wheeled>	coprime_num,coprime_diff;
array<int,wheel>	nearest_coprime,index;
array<int,20000>	primes;
bitset<wheel>		coprime,block;
unsigned int		answer,a,b,c,d,cnt_coprime,count_prime=6,limit,cnt_block;

void update(unsigned int prime)
{
	unsigned int tmp=limit/prime,cnt_p=0;
	while(tmp)
		cnt_p+=tmp,tmp/=prime;
	answer+=cnt_p*(prime*prime*prime*a+prime*prime*b+prime*c+d);
}

int main(int argc,char *argv[],char *envp[])
{
	cin>>limit>>a>>b>>c>>d,cnt_block=limit/wheel;
	primes[1]=2,primes[2]=3,primes[3]=5,primes[4]=7,primes[5]=11,primes[6]=13;
	for(int i=1;i<=count_prime;i++)
	{
		update(primes[i]);
		for(int j=1;j*primes[i]<=wheel;j++)
			coprime[primes[i]*j]=true;
	}
	for(int i=1;i<=wheel;i++)
		if(!coprime[i])
			coprime_num[cnt_coprime]=i,index[i]=cnt_coprime++;
	for(int i=0;i<wheeled-1;i++)
		coprime_diff[i]=coprime_num[i+1]-coprime_num[i];
	coprime_diff[wheeled-1]=coprime_num[0]+wheel-coprime_num[wheeled-1];
	int ptr=wheeled-1;
	for(int i=wheel-1;~i;i--)
	{
		if(ptr&&i==coprime_num[ptr-1])
			--ptr;
		nearest_coprime[i]=coprime_num[ptr]-i;
	}
	block=coprime;
	for(int i=coprime_num[1],j=1;i<wheel;i+=coprime_diff[j],j=++j%wheeled)
		if(!block[i])
		{
			primes[++count_prime]=i;
			update(i);
			if(i*i<=limit)
				for(int k=i,l=j;k*i<wheel;k+=coprime_diff[l],l=++l%wheeled)
					block.set(k*i);
		}
	for(int i=1;i<=cnt_block;i++)
	{
		block=coprime;
		int block_start=i*wheel,block_end=(i+1)*wheel-1;
		for(int j=7;primes[j]*primes[j]<=block_end;j++)
			for(int k=(block_start-1)/primes[j]+1+nearest_coprime[((block_start-1)/primes[j]+1)%wheel],l=index[k%wheel];k*primes[j]<=block_end;k+=coprime_diff[l],l=++l%wheeled)
				block.set(k*primes[j]-block_start);
		for(int j=0;j<wheeled;j++)
			if(!block.test(coprime_num[j]))
			{
				long long tmp=coprime_num[j]+block_start;
				if(tmp>limit)
					goto end_proc;
				if(tmp*tmp<=limit)
					primes[++count_prime]=tmp;
				update(tmp);
			}
	}
	end_proc:cout<<answer;
 	return 0;
}
```

---

## 作者：peterwuyihong (赞：1)

题意：定义扩展 $\log$ 函数：$\text{exlog}(p_1^{\alpha_1}p_2^{\alpha_2}p_3^{\alpha_3}\ldots)=\sum_i\alpha_if(p_i)$，其中 $f(x)=Ax^3+Bx^2+Cx+D$，求 $\sum_{i=1}^n\text{exlog(}i)$。$n\le 3\times10^8,\bmod=2^{32}$

你一眼看出来这个 $\text{exlog}$ 带有 $\log$ 的性质，是一个和性函数，于是答案就是 $\text{exlog(}n!)$。

然后你把它分解质因数，筛出 $3\times10^8$ 以内的质数，硬上就行了，复杂度其实是 $O(n)$ 的，筛素数 $O(n)$，素数有 $O(\dfrac{n}{\ln n})$ 个，对每一个素数算出 $n!$ 里有几个它是 $O(\log)$ 的，乘起来就是 $O(n)$。

关于空间问题，你掏出 [这个题](https://www.luogu.com.cn/problem/P7884)，一跑，居然只有 $16252325$ 个素数，然后那个 $\text{bool}$ 数组就直接改成 $\text{bitset}$ 就好了。

现在是 $13:44$，我看我什么时候写完。

现在是 $14:26$，我写完了。

```cpp
#include<stdio.h>
#include<bitset>
unsigned n,ans;
unsigned A,B,C,D;
std::bitset<100000001>v;
unsigned F(const unsigned&x){return D+x*(C+x*(B+x*A));}
unsigned G(const unsigned&o){
	unsigned u=n,ans=0;
	while(u)ans+=u/o,u/=o;
	return ans*F(o);
}
bool check(const unsigned&x){return x%2&&x%3&&x%5;}
signed main(){
	scanf("%u%u%u%u%u",&n,&A,&B,&C,&D);
	ans+=G(2)+G(3)+G(5);
	for(unsigned i=7;i<=n;i++){
		if(!check(i))continue;
		if(v[i/3])continue;
		ans+=G(i);
		for(unsigned j=i<<1;j<=n;j+=i)
		if(check(j))v[j/3]=1;
	}
	printf("%u",ans);
}
```
沃日，被这个空间埋伏到了。

我教大家卡空常。

1.沃日，线性筛炸了，$3e8$ 的 $\text{bitset}$ 其实有三十几个兆

2.你考虑到一个玄妙的优化，大于 $6$ 的质数都是 $\bmod6=±1$ 的，然后你记录状态时可以三个压一位，表示这三个都不行

3.调头文件，我也不知道我是什么玄妙原因，$\text{bits}\rightarrow\text{MLE}$。

4.输入，我也不知道是什么玄妙原因，$\text{cin}\rightarrow\text{MLE}$。

然后就擦着边过去了，这个题很牛逼啊

---

