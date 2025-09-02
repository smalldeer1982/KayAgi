# 「SWTR-3」Counting Trees

## 题目背景

一个风和日丽的早晨，小 $\mathrm{S}$ 带着他的好朋友小 $\mathrm{A}$ 在小树林里面数树。

看着满树林的树，小 $\mathrm{S}$ 灵感一闪，想到了一道题目。

---

$$\mathrm{Suddenly,\ Little\ S\ thought\ of\ a\ supercalifragilisticexpialidocious\ problem.}$$

$$\mathrm{He\ wanted\ Little\ A\ to\ answer\ it.}$$

## 题目描述

现在有 $n$ 个点，每个点有一个权值 $v_i$。

小 $\mathrm{S}$ 想要小 $\mathrm{A}$ 从中选一些点组成一个集合，设集合 $S=\{d_1,d_2,\dots,d_m\}(1\leq m\leq n)$。

当然，小 $\mathrm{A}$ 还需要保证这些点能形成一颗树，且 $d_i$ 的度数为 $v_{d_i}(i\in[1,m])$。

- 节点的度数：与它相邻的节点的个数。

小 $\mathrm{S}$ 想问小 $\mathrm{A}$ 有多少种满足条件的方案。

小 $\mathrm{A}$ 深知自己肯定不会这道题目，所以他就拿来问你了。

由于方案数可能很大，所以请对 $998244353$ 取模。

## 说明/提示

---

### 样例说明

- 对于样例 $1$，在三个节点中任选两个即可，答案为 $C^{2}_{3}=3$。

- 对于样例 $2$，如图，共有 $8$ 种选择节点的方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/g0suqsi0.png)

---

### 数据范围与约定

**本题使用捆绑测试。**

| Subtask 编号 | $n\leq$ | 特殊性质 | 得分 |
| :-: | :-: | :-: | :-: |
| $1$ | $20$ | 无 | $11$ |
| $2$ | $50$ | 无 | $12$ |
| $3$ | $300$ | 无 | $10$ |
| $4$ | $2500$ | 无 | $17$ |
| $5$ | $4\times 10^4$ | 无 | $6$ |
| $6$ | $3\times 10^5$ | $v_i\leq 3$ | $8$ |
| $7$ | $3\times 10^5$ | 数据随机 | $7$ |
| $8$ | $5\times 10^5$ | 无 | $29$ |

对于 $100\%$ 的数据，$2 \leq n \leq 5 \times 10^5$，$\ 1 \leq v_i \leq n$。

---

$\mathrm{Subtask\ 7}$ 中“数据随机”指：对于所有 $v_i$，$\frac{1}{3}$ 的概率为 1，$\frac{2}{3}$ 的概率为 $[2,n]$ 中等概率选择一个数。

---

对于前 $4$ 个 $\mathrm{Subtask}$，时间限制 $1\mathrm{s}$。

对于第 $5$ 个 $\mathrm{Subtask}$，时间限制 $3\mathrm{s}$。

对于后 $3$ 个 $\mathrm{Subtask}$，时间限制 $6\mathrm{s}$。

对于所有测试点，空间限制 $256\mathrm{MB}$。

## 样例 #1

### 输入

```
3
1 1 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 2 1 3 1
```

### 输出

```
8```

## 样例 #3

### 输入

```
8
1 2 1 2 4 1 3 1
```

### 输出

```
44```

## 样例 #4

### 输入

```
50
8 1 10 2 2 1 2 1 1 2 5 1 11 6 13 13 10 4 1 13 11 2 2 11 13 10 1 1 4 3 4 2 15 2 2 1 1 2 1 7 14 2 2 4 13 2 7 5 6 10 ```

### 输出

```
176873472```

# 题解

## 作者：command_block (赞：5)

$\color{blue}\text{(重制于 2020.11.26)}$

由于时间关系没有现场打，赛后来肝题。

看到数树以为是大毒瘤，没想到这树就是来开玩笑的……

树的必要条件 : $\text{度数和}=2(\text{点数}-1)$

若度数符合要求,根据 $\rm prufer$ 序列,必然能够造出符合要求的树。则上面的是充要条件。

移项整理得到 $\text{度数和}-2\text{点数}=-2$

我们每加一个点扣除 $2$ 点贡献，每有一个度数加上 $1$ 点贡献，具体处理方式就是 $\rm OGF$。

全部卷积起来之后，$[x^{-2}]$ 项就是答案。

(我在CSP2019曾因为没看出这个trick白丢了16分qwq)

也就是说我们需要求 $[x^{-2}]\prod\limits_{i=1}^n(1+x^{v_i-2})$

怎么还有负数次项啊，又没法分治NTT，一脸不可做的样子……

首先对于 $v_i=2$ 的点单独提出来(次数为0),设有 $m$ 个,最后答案乘以 $2^m$ 。

首先对于 $v^i<2$ 的部分，只可能有 $(1+x^{-1})$ 。这部分直接记录次数 $c$ ,二项式定理即可。

得到 $F1(x)$ ,最低有 $-c$ 次项，注意到正负项可能相消，我们后面正次数的多项式保留 $\bmod\ x^{c-1}$ 的项即可。

对于 $v_i>2$ 的部分，无法分治NTT。

令 $a_i=v_i-2$ (此时余下的所有 $a_i>0$ )

${\rm Ans}=\prod\limits_{i=1}^n(1+x^{a_i})$

类似 `P4389` 考虑将每个东西 $\ln$ 之后加在一起再 $\exp$ 回来。

不难发现 $\ln(1+x^a)$ 只在 $a$ 的倍数次数处有值。

具体而言，根据 $-\ln(1-x)=\sum\limits_{i=1}\dfrac{x^i}{i}$

可推知 $\ln(1+x^a)=\sum\limits_{i=0}\dfrac{(-x)^{ia}}{i}$

需要累加的项是 $O\Big(\sum\limits_{i=1}^nn/i\Big)=O(n\log n)$ 的。

剩下的就是 `P4389` 了,得到这部分的 $F2(x)$。

最后把 $F1,F2$ 卷起来就是答案，负指数加法卷积的规则和正指数类似。

本题中可以把 $F1$ 整体平移来处理。

```cpp
#include<algorithm>
#include<cstdio>
#include<ctime>
#define ll long long
#define mod 998244353
#define G 3
#define Maxn 530000
using namespace std;
inline int read()
{
  register int X=0;
  register char ch=0;
  while(ch<48||ch>57)ch=getchar();
  while(ch>=48&&ch<=57)X=X*10+(ch^48),ch=getchar();
  return X;
}
ll powM(ll a,ll t=mod-2)
{
  ll ans=1;
  while(t){
  	if(t&1)ans=ans*a%mod;
  	a=a*a%mod;
  	t>>=1;
  }return ans;
}
int tr[Maxn<<1];
ll invG=powM(G);
void NTT(ll *f,short op,int n)
{
  for (int i=0;i<n;i++)
    if (i<tr[i])swap(f[i],f[tr[i]]);
  for(int p=2;p<=n;p<<=1){
    int len=p>>1,
        tG=powM(op==1 ? G:invG,(mod-1)/p);
    for (int k=0;k<n;k+=p){
  	  ll buf=1;
  	  for (int i=k;i<k+len;i++){
  	  	int sav=f[len+i]*buf%mod;
  	  	f[len+i]=(f[i]-sav+mod)%mod;
  	  	f[i]=(f[i]+sav)%mod;
  	  	buf=buf*tG%mod;
  	  }
    }
  }
}
ll _g1[Maxn<<1];
void times(ll *f,ll *g,int len1,int len2,int lim)
{
  int m=len1+len2-1,n;
  for(int i=0;i<len2;i++)_g1[i]=g[i];
  #define g _g1
  for(n=1;n<m;n<<=1);
  for(int i=len2;i<n;i++)g[i]=0;
  ll invn=powM(n);
  for(int i=0;i<n;i++)
    tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
  NTT(f,1,n);NTT(g,1,n);
  for(int i=0;i<n;++i)f[i]=f[i]*g[i]%mod;
  NTT(f,-1,n);
  for(int i=0;i<lim;++i)
    f[i]=f[i]*invn%mod;
  for(int i=lim;i<n;++i)f[i]=0;
  #undef g
}
ll _w2[Maxn<<1],_r2[Maxn<<1];
void invp(ll *f,int m)
{
  int n;for (n=1;n<m;n<<=1);
  #define w _w2
  #define r _r2
  w[0]=powM(f[0]);
  for (int len=2;len<=n;len<<=1){
  	for (int i=0;i<(len>>1);i++)
      r[i]=(w[i]<<1)%mod;
  	times(w,w,len>>1,len>>1,len);
  	times(w,f,len,len,len);
  	for (int i=0;i<len;i++)
      w[i]=(r[i]-w[i]+mod)%mod;
  }for (int i=0;i<m;i++)f[i]=w[i];
  for (int i=0;i<n;i++)w[i]=r[i]=0;
  #undef w
  #undef r
}
ll fac[Maxn],inv[Maxn],inp[Maxn];
ll C(int n,int m)
{return fac[n]*inv[m]%mod*inv[n-m]%mod;}
void Init(int m)
{
  int lim=1;
  for (;lim<m;lim<<=1)
  fac[0]=1;
  for (int i=1;i<=lim;i++)
    fac[i]=fac[i-1]*i%mod;
  inv[lim]=powM(fac[lim]);
  for (int i=lim;i;i--){
    inv[i-1]=inv[i]*i%mod;
    inp[i]=inv[i]*fac[i-1]%mod;
  }
}
void dao(ll *f,int m)
{
  for (int i=1;i<m;i++)
   f[i-1]=f[i]*i%mod;
  f[m-1]=0;
}
void jifen(ll *f,int m)
{
  for (int i=m;i;i--)
    f[i]=f[i-1]*powM(i)%mod;
  f[0]=0;
}
ll _s3[Maxn<<2];
void lnp(ll *f,int m)
{
  ll *sav=_s3;
  for (int i=0;i<m;i++)sav[i]=f[i];
  invp(sav,m);dao(f,m);
  times(f,sav,m-1,m,m);
  jifen(f,m-1);
  for (int i=0;i<m;i++)sav[i]=0;
}
ll _xp[Maxn<<2],_xp2[Maxn<<2];
void exp(ll *f,int m)
{
  ll *s=_xp,*s2=_xp2;
  int n=1;for(;n<m;n<<=1);
  s2[0]=1;
  for (int len=2;len<=n;len<<=1){
  	for (int i=0;i<(len>>1);i++)s[i]=s2[i];
  	lnp(s,len);
  	for (int i=0;i<len;i++)
  	  s[i]=(f[i]-s[i]+mod)%mod;
  	s[0]=(s[0]+1)%mod;
  	times(s2,s,len>>1,len,len);
  }for (int i=0;i<m;i++)f[i]=s2[i];
  for (int i=0;i<n;i++)s[i]=s2[i]=0;
}
ll buf,F1[Maxn],F2[Maxn];
int n,c[Maxn],m;
int main()
{
  n=read();
  for (int i=1;i<=n;i++)c[read()]++;
  m=c[1];
  if (m<2){printf("0");return 0;}
  Init(m);
  for (int i=0;i<m-1;i++)F1[i]=C(m,i);
  m--;
  for (int i=3;i<=n;i++){
    ll a=i-2;
    for (int j=1;j*a<m;j++)
      F2[j*a]=(F2[j*a]+1ll*c[i]*((j&1) ? inp[j] : mod-inp[j]))%mod;
  }
  exp(F2,m);
  times(F1,F2,m,m,m);
  printf("%lld",F1[m-1]*powM(2,c[2])%mod);
  return 0;
}
```




---

## 作者：Alex_Wei (赞：4)

$\color{#00008B}\mathrm{This\ is\ Sweet\ Round\ 03.}$

[$\color{#00008B}\mathrm{Link:T6\ Counting\ Trees}$](https://www.luogu.com.cn/problem/T112465)

基础多项式优化背包。

---

本题的 $\mathrm{idea}$ 来源于 @sunyx。

---

$\mathrm{Sol\ 1}:$

$01$ 枚举集合 $S$ 中的元素，判断选出的集合是否合法。

#### 如何判断集合 $S$ 中的点是否可以组成一棵树？

假如一棵树有 $m$ 个节点，节点 $1$ 到节点 $m$ 的度数分别为 $d_1,d_2,\dots,d_m(d_i>0)$ ，那么有 $\sum_{i=1}^m d_i=2 \times m-2$，反之亦然。

因此，将选出的所有数的权值加起来，判断是否等于 $2 \times m-2$ 即可。

时间复杂度：$\mathcal O(2^n \times n)$。

- 可以通过 $\mathrm{Subtask}$ $1$。

期望得分：$8\%$。

---

$\mathrm{Sol\ 2}:$

不难想到 $\mathrm{DP}$ 算法：$f_{i,j,k}$ 表示 **在前 $i$ 个数中，选了 $j$ 个数，选出的数和为 $k$ 的方案数。**

转移方程为 $f_{i,j,k}=f_{i-1,j,k}+f_{i-1,j-1,k-v_i}$。

最后的答案为 $\sum_{i=1}^nf_{n,i,i \times 2-1}$。

时间复杂度：$\mathcal O(n^4)$。

- 可以通过 $\mathrm{Subtask}$ $1,2$。

期望得分：$23\%$。

---

$\mathrm{Sol\ 3}:$

$\mathrm{Sol\ 2}$ 中 $\mathrm{DP}$ 的第三维只用枚举到 $2 \times n-1$，这样可以优化到 $\mathcal O(n^3)$.

- 可以通过 $\mathrm{Subtask}$ $1,2,3$。

期望得分：$33\%$。

---

$\mathrm{Sol\ 4}:$

发现 $\mathrm{Sol\ 1}$ 中的式子可以变形为 $\sum_{i=1}^nd_i-2=-2$ 。那么这道题就变为一道背包的题目。

先将每个 $v_i$ 都减 $2$ 。设$f_{i,j}$为在前 $i$ 个数中，选出的数和为 $j$ 的方案数。转移方程：$f_{i,j}=f_{i-1,j}+f_{i-1,j-v_i}$，答案为 $f_{n,-2}$ 。由于下标存在负数，对每个数 $+2$ 即可。

和 $\mathrm{Sol\ 3}$ 一样。该算法也可以进行优化。上述 $\mathrm{DP}$ 状态大于 $n$ 的状态都可以不用考虑。

时间复杂度： $\mathcal O(n^2)$。

- 可以通过 $\mathrm{Subtask}$ $1,2,3,4$。

期望得分：$50\%$。

---

$\mathrm{Sol\ 5}:$

当 $v_i \leq 3$ 的时候，设 $c_1,c_2,c_3$ 分别为选择 $1,2,3$ 的个数，$t_1,t_2,t_3$ 分别为 $1,2,3$ 的总数。

由之前推导的公式可以知道：$c_1-c_3=2$，而 $c_2$ 可以为任意值。所以可以枚举 $c_1$ 使得 $1 \leq c_1 \leq t_1,\ 1 \leq c_1-2 \leq t_3$，然后用组合数计算对答案的贡献，即 $C^{c_1}_{t_1}\times C^{c_1-2}_{t_3}\times 2^{t_2}$

时间复杂度：$\mathcal O(n)$。

- 可以通过 $\mathrm{Subtask}$ $6$。

期望得分：$8\%$。

结合 $\mathrm{Sol\ 4}$，可以获得 $58\%$ 的分数。

---

$\mathrm{Sol\ 6}:$

以上解法都是基于对背包状态进行的优化，而该解法是对背包本身进行的优化。

- 前置芝士：$\mathrm{NTT}$，多项式 $\mathrm{ln\ \&\ exp}$ 运算。

如果不会，请先移步 $\mathrm{P3803,P4725,P4726}$。

先看以下一个问题：

#### 有 $n$ 个数 $a_1,a_2,\dots,a_n$，求选出一些数（下标不重复）使得它们和恰为 $S$ 的方案数模 $998244353$，$n,S$ 均小于 $10^5$。

构造一个生成函数，形如 $(1+x^{a_1})(1+x^{a_2})(1+x^{a_3})\dots(1+x^{a_n})$，将这个式子展开并合并同类项后 $x^S$ 前的系数就是答案。

而该式子可以写成 $exp(ln(1 + x^{a_1})+ln(1+ x^{a_2})+\dots+ln(1 + x^{a_n}))$

又 $ln(1+x)$ 的展开式为 $\sum_{i}^{\infty}(-1)^{i-1} \times \frac{x^i}{i}$。

因此 $ln(1+x^n)$ 的展开式为 $\sum_{i}^{\infty}(-1)^{i-1} \times \frac{x^{n\times i}}{i}$

而因为 $S$ 小于 $10^5$，所以只用考虑多项式 $mod\ x^{100000}$ 的情形。对于每一个$a_i$，在多项式 $[1,100000]$ 中所有 $a_i$ 的倍数的项数 $x$ 上加上 $(-1)^{\frac{i}{a_i}-1} \times \frac{i}{a_i}^{-1}$，再对这个多项式取一遍 $\mathrm{exp}$ 即可。

#### 上述问题解决了，这道题也就迎刃而解了。

和 $\mathrm{Sol\ 4}$ 一样，我们将每个 $v_i$ 减 $2$。但是 $v_i$ 值出现了负数和零，无法简单地按照上述思路执行。

不过只可能出现一种负数 $-1$，并且 $0$ 的个数可以为任意值，那么假设 $-1$ 的总个数为 $t_1$，$0$ 的总个数为 $t_2$，将值大于 $0$ 的部分按照上述思路求出最后的多项式。然后枚举 $-1$ 的个数，设为 $x$，用乘法原理计算对答案的贡献：$C^{x}_{t_1}\times 2^{t_2} \times$ 多项式 $x-2$ 次项前的系数。

时间复杂度：$\mathcal O(n\times \log n)$。

- 可以通过所有测试点。

期望得分：$100\%$。

---

$\mathrm{std:}$

因为出题人太菜，还不会写多项式 $\mathrm{EXP}$，所以代码中的 $\mathrm{EXP}$ 来自于 @yybyyb 在 $\mathrm{P4389}$ 中的题解。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=998244353;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
int fpow(int base,int e){
    int ans=1;
    while(e){
		if(e&1)	ans=ans*base%MOD;
		base=base*base%MOD;
		e>>=1;
	}
    return ans;
}
int n,cnt1=0,cnt2=0;
int F[1500005],FF[1500005];
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1;y=0;
		return a;
	}
	int t=exgcd(b,a%b,x,y);
	int temp=x;
	x=y;
	y=temp-(a/b)*y;
	return t;
}
int _inv(int a,int b){
	int x,y;
	exgcd(a,b,x,y);
	return x;
}
inline void init(){
	F[0]=1;
	for(int i=1;i<=500000;i++)	F[i]=F[i-1]*i%MOD;
	FF[500000]=1ll*(_inv(F[500000],MOD)+MOD*MOD)%MOD;
	for(int i=499999;i>=0;i--)	FF[i]=FF[i+1]*(i+1)%MOD;
}
inline int func_C(int a,int b){
	return 1ll*F[a]*FF[b]%MOD*FF[a-b]%MOD;
}
int r[1500005],N,l,M;
int Og[1500005];
void NTT(int *P,int opt,int n){
    for(N=1,l=0;N<n;N<<=1)	++l;
    for(register int i=0;i<N;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    for(register int i=0;i<N;++i)
		if(i<r[i])swap(P[i],P[r[i]]);
    for(register int i=1;i<N;i<<=1){
        register int W=fpow(3,(MOD-1)/(i<<1));Og[0]=1;
        for(register int j=1;j<i;++j)Og[j]=1ll*Og[j-1]*W%MOD;
        for(register int p=i<<1,j=0;j<N;j+=p)
            for(register int k=0;k<i;++k){
                register int X=P[j+k],Y=1ll*Og[k]*P[i+j+k]%MOD;
                P[j+k]=(X+Y)%MOD;P[i+j+k]=(X+MOD-Y)%MOD;
            }
    }
    if(opt==-1){
        reverse(&P[1],&P[N]);
        for(register int i=0,inv=fpow(N,MOD-2);i<N;++i)
			P[i]=1ll*P[i]*inv%MOD;
    }
}
int inv[1500005];
void initinv(int N){
    inv[0]=inv[1]=1;
    for(register int i=2;i<N;++i)
		inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
}
int A[1500005],B[1500005];
void Inv(int *a,int *b,int len){
    if(len==1){
		b[0]=fpow(a[0],MOD-2);
		return;
	}
    Inv(a,b,len>>1);
    for(register int i=0;i<len;++i)
		A[i]=a[i],B[i]=b[i];
    NTT(A,1,len<<1);
	NTT(B,1,len<<1);
    for(register int i=0;i<(len<<1);++i)
		A[i]=1ll*A[i]*B[i]%MOD*B[i]%MOD;
    NTT(A,-1,len<<1);
    for(register int i=0;i<len;++i)
		b[i]=(b[i]+b[i])%MOD;
    for(register int i=0;i<len;++i)
		b[i]=(b[i]+MOD-A[i])%MOD;
    for(register int i=0;i<(len<<1);++i)
		A[i]=B[i]=0;
}
int C[1500005],D[1500005];
void Dao(int *a,int *b,int len){
    for(register int i=1;i<len;++i)
		b[i-1]=1ll*i*a[i]%MOD;
    b[len]=b[len-1]=0;
}
void Jifen(int *a,int *b,int len){
    for(register int i=1;i<len;++i)
		b[i]=1ll*a[i-1]*inv[i]%MOD;
    b[0]=0;
}
void Getln(int *a,int *b,int len){
    int A[1500005],B[1500005];
    memset(A,0,sizeof(A));memset(B,0,sizeof(B));
    Dao(a,A,len);
    Inv(a,B,len);
    NTT(A,1,len<<1);NTT(B,1,len<<1);
    for(register int i=0;i<(len<<1);++i)
		A[i]=1ll*A[i]*B[i]%MOD;
    NTT(A,-1,len<<1);
    Jifen(A,b,len);
    for(register int i=0;i<(len<<1);++i)
		A[i]=B[i]=0;
}
int E[1500005];
void Exp(int *a,int *b,int len){
    if(len==1){
		b[0]=1;
		return;
	}
    Exp(a,b,len>>1);
    for(register int i=0;i<len;++i)
		D[i]=b[i];
    Getln(b,E,len);
    for(register int i=0;i<len;++i)
		E[i]=(MOD-E[i]+a[i])%MOD;E[0]=(E[0]+1)%MOD;
    NTT(E,1,len<<1);
	NTT(D,1,len<<1);
    for(register int i=0;i<(len<<1);++i)
		D[i]=1ll*D[i]*E[i]%MOD;
    NTT(D,-1,len<<1);
    for(register int i=0;i<len;++i)
		b[i]=D[i];
    for(register int i=0;i<(len<<1);++i)
		D[i]=E[i]=0;
}
void FastPow(int *a,int *b,int K,int len){
    memset(E,0,sizeof(E));
    Getln(a,E,len);
    for(register int i=0;i<len;++i)
		E[i]=1ll*K*E[i]%MOD;
    Exp(E,b,len);
}
int X[1500005],Y[1500005],TT[1500005],a[1500005],cnt[1500005];
signed main(){
	init();
    n=read();
    int N;for(N=1;N<=n;N<<=1);
	initinv(N);
    for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]>n)	continue;
		if(a[i]==1)			cnt1++;
		else if(a[i]==2)	cnt2++;
		else{
			cnt[a[i]-2]++;
		}
	}
	for(int i=1;i<=n;i++){
		if(cnt[i]>0){
			for(int j=i;j<=n;j+=i){
				if((j/i)%2==1)
					X[j]=(X[j]+inv[j/i]*cnt[i]%MOD)%MOD;
				else
					X[j]=(X[j]-inv[j/i]*cnt[i]%MOD+MOD)%MOD;
			}
		}
	}
    Exp(X,Y,N);
	int ans=0;
	for(int i=2;i<=cnt1;i++){
    	ans=(ans+1ll*func_C(cnt1,i)%MOD*fpow(2,cnt2)%MOD*Y[i-2]%MOD)%MOD;
	}
	print(ans);
    return 0;
}
```

---

## 作者：jun头吉吉 (赞：2)

## 题意
$n$个点，每个点度数给定。

选出若干个点能组成树的方案数。
## 题解
对于一棵树，有$n$个点，有$n-1$条边，$\sum_{i=1}^ndeg_i=2(n-1)$,即$\sum_{i=1}^ndeg_i-2=-2$。所以$\sum^n_{i=1} v_i-2=-2$是一个必要条件。（充分条件留给读者自证）

看做生成函数，对于$v_i$，其生成函数就是$1+x^{v_i-2}$即选或不选。

$$F(x)=\prod_{i=1}^n(1-x^{v_i-2}),ans=[x^{-2}]F(x)$$
可这个负数次很讨厌，我们无法愉快地计算，因此需要乱搞。
$$
F(x)=\overbrace{\prod_{v_i=1}(1+x^{-1})}^{m\text{个}}
\overbrace{\prod_{v_i=2}(1+1)}^{k\text{个}}
\overbrace{\prod_{v_i>2}(1+x^{v_i-2})}^{n-m-k\text{个}}
$$
那么给所有$1+x^{-1}$乘上$x$，那么就相当于$1+x$，记$a=\{|v_i-2|,v_i=1|v_i>2\}$

$$
\begin{aligned}
x^mF(x)
&=2^k\prod_{i}(1+x^{a_i})\\
&=2^k\exp(\sum_{i}\ln(1+x^a_i))\\
&=2^k\exp(\sum_{i}\int(\ln(1+x^{a_i}))^\prime dx)\\
&=2^k\exp(\sum_{i}\int\frac{a_ix^{a_i-1}}{1+x^{a_i}}dx)\\
&=2^k\exp(\sum_{i}a_ix^{a_i-1}\int\sum_{j=0}^\infty (-x^{a_i})^jdx)\\
&=2^k\exp(\sum_{i}a_ix^{a_i-1}\int\sum_{j=0}^\infty (-1)^jx^{a_ij}dx)\\
&=2^k\exp(\sum_{i}\int\sum_{j=0}^\infty (-1)^ja_ix^{a_i(j+1)-1}dx)\\
&=2^k\exp(\sum_{i}\sum_{j=0}^\infty (-1)^j\int a_ix^{a_i(j+1)-1}dx)\\
&=2^k\exp(\sum_{i}\sum_{j=0}^\infty (-1)^j\frac{a_ix^{a_i(j+1)}}{a_i(j+1)}dx)\\
&=2^k\exp(\sum_{i}\sum_{j=1}^\infty (-1)^{j-1}\frac{x^{a_ij}}{j}dx)\\

\end{aligned}
$$
就是一个小套路。

最后$ans=[x^{m-2}]x^mF(x)$就行了。
## 代码
最后送上萌新慢的要死的代码
```cpp
#include<bits/stdc++.h>
//#define faster
namespace in{
	#ifdef faster
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	#else
	inline int getc(){return getchar();}
	#endif
	template <typename T>inline void read(T& t){
		t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
	    while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
}
namespace out{
	char buffer[1<<21];int p1=-1;const int p2 = (1<<21)-1;
	inline void flush(){fwrite(buffer,1,p1+1,stdout),p1=-1;}
	inline void putc(const char &x) {if(p1==p2)flush();buffer[++p1]=x;}
	template <typename T>void write(T x) {
		static char buf[15];static int len=-1;if(x>=0){do{buf[++len]=x%10+48,x/=10;}while (x);}else{putc('-');do {buf[++len]=-(x%10)+48,x/=10;}while(x);}
		while (len>=0)putc(buf[len]),--len;
	}
}
using namespace std;
template<const int mod>
struct modint{
    int x;
    modint<mod>(int o=0){x=o;}
    modint<mod> &operator = (int o){return x=o,*this;}
    modint<mod> &operator +=(modint<mod> o){return x=x+o.x>=mod?x+o.x-mod:x+o.x,*this;}
    modint<mod> &operator -=(modint<mod> o){return x=x-o.x<0?x-o.x+mod:x-o.x,*this;}
    modint<mod> &operator *=(modint<mod> o){return x=1ll*x*o.x%mod,*this;}
    modint<mod> &operator ^=(int b){
        modint<mod> a=*this,c=1;
        for(;b;b>>=1,a*=a)if(b&1)c*=a;
        return x=c.x,*this;
    }
    modint<mod> &operator /=(modint<mod> o){return *this *=o^=mod-2;}
    modint<mod> &operator +=(int o){return x=x+o>=mod?x+o-mod:x+o,*this;}
    modint<mod> &operator -=(int o){return x=x-o<0?x-o+mod:x-o,*this;}
    modint<mod> &operator *=(int o){return x=1ll*x*o%mod,*this;}
    modint<mod> &operator /=(int o){return *this *= ((modint<mod>(o))^=mod-2);}
	template<class I>friend modint<mod> operator +(modint<mod> a,I b){return a+=b;}
    template<class I>friend modint<mod> operator -(modint<mod> a,I b){return a-=b;}
    template<class I>friend modint<mod> operator *(modint<mod> a,I b){return a*=b;}
    template<class I>friend modint<mod> operator /(modint<mod> a,I b){return a/=b;}
    friend modint<mod> operator ^(modint<mod> a,int b){return a^=b;}
    friend bool operator ==(modint<mod> a,int b){return a.x==b;}
    friend bool operator !=(modint<mod> a,int b){return a.x!=b;}
    bool operator ! () {return !x;}
    modint<mod> operator - () {return x?mod-x:0;}
	modint<mod> &operator++(int){return *this+=1;}
};
const int N=4e6+5;
const int mod=998244353;
const modint<mod> GG=3,Ginv=modint<mod>(1)/3,I=86583718;
struct poly{
	vector<modint<mod>>a;
	modint<mod>&operator[](int i){return a[i];}
	int size(){return a.size();}
	void resize(int n){a.resize(n);}
	void reverse(){std::reverse(a.begin(),a.end());}
};
int rev[N];
inline int ext(int n){int k=0;while((1<<k)<n)k++;return k;}
inline void init(int k){int n=1<<k;for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));}
inline void ntt(poly&a,int k,int typ){
	int n=1<<k;
	for(int i=0;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int mid=1;mid<n;mid<<=1){
		modint<mod> wn=(typ>0?GG:Ginv)^((mod-1)/(mid<<1));
		for(int r=mid<<1,j=0;j<n;j+=r){
			modint<mod> w=1;
			for(int k=0;k<mid;k++,w=w*wn){
				modint<mod> x=a[j+k],y=w*a[j+k+mid];
				a[j+k]=x+y,a[j+k+mid]=x-y;
			}
		}
	}
	if(typ<0){
		modint<mod> inv=modint<mod>(1)/n;
		for(int i=0;i<n-1;i++)a[i]*=inv;
	}
}
inline poly one(){poly a;a.a.push_back(1);return a;}
poly operator +(poly a,poly b){
	int n=max(a.size(),b.size());a.resize(n),b.resize(n);
	for(int i=0;i<n;i++)a[i]+=b[i];return a;
}
poly operator -(poly a,poly b){
	int n=max(a.size(),b.size());a.resize(n),b.resize(n);
	for(int i=0;i<n;i++)a[i]-=b[i];return a;
}
inline poly operator*(poly a,poly b){
	int n=a.size()+b.size()-1,k=ext(n);
	a.resize(1<<k),b.resize(1<<k),init(k);
	ntt(a,k,1);ntt(b,k,1);for(int i=0;i<(1<<k);i++)a[i]*=b[i];
	ntt(a,k,-1),a.resize(n);return a;
}
inline poly operator*(poly a,modint<mod> b){for(int i=0;i<a.size();i++)a[i]*=b;return a; }
inline poly operator/(poly a,modint<mod> b){for(int i=0;i<a.size();i++)a[i]/=b;return a; }
inline poly operator-(poly a){for(int i=0;i<a.size();i++)a[i]=-a[i];return a; }
poly inv(poly F,int k){
	int n=1<<k;F.resize(n);
	if(n==1){F[0]=modint<mod>(1)/F[0];return F;}
	poly G,H=inv(F,k-1);
	G.resize(n),H.resize(n<<1),F.resize(n<<1);
	for(int i=0;i<n/2;i++)G[i]=H[i]*2;
	init(k+1),ntt(H,k+1,1),ntt(F,k+1,1);
	for(int i=0;i<(n<<1);i++)H[i]=H[i]*H[i]*F[i];
	ntt(H,k+1,-1),H.resize(n);
	for(int i=0;i<n;i++)G[i]-=H[i];return G;
}
inline poly inv(poly a){
	int n=a.size();
	a=inv(a,ext(n)),a.resize(n);return a;;
}
inline poly deriv(poly a){//求导 
	int n=a.size()-1;
	for(int i=0;i<n;i++)a[i]=a[i+1]*(i+1);
	a.resize(n);return a;
}
inline poly inter(poly a){//求原 
	int n=a.size()+1;a.resize(n);
	for(int i=n;i>=1;i--)a[i]=a[i-1]/i;
	a[0]=0;return a;
}
inline poly ln(poly a){
	int n=a.size();
	a=inter(deriv(a)*inv(a));
	a.resize(n);return a;
}
poly exp(poly a,int k){
	int n=1<<k;a.resize(n);
	if(n==1)return one();
	poly f0=exp(a,k-1);f0.resize(n);
	return f0*(one()+a-ln(f0)); 
}
poly exp(poly a){
	int n=a.size();
	a=exp(a,ext(n));a.resize(n);return a;
}
int n,m,k,v[N],cnt[N];
poly F;
signed main(){
	in::read(n);for(int i=1;i<=n;i++)
		in::read(v[i]),(v[i]==2?k:cnt[abs(v[i]-2)])++,v[i]==1&&(m++);
	F.resize(m);
	for(int i=1;i<m;i++)
		for(int j=1;i*j<m;j++)
			F[i*j]+=((j&1)?modint<mod>(cnt[i]):-modint<mod>(cnt[i]))/j;
	F=exp(F);out::write((F[m-2]*(modint<mod>(2)^k)).x);
	out::flush();
	return 0;
}
```

---

## 作者：Hagasei (赞：1)

水了发（暂时的）最优解。感叹一下 $O(n\log^2n) \exp$ 的优越性。

**题意简述**：有个序列 $v$，问有多少子序列满足以它们的值为度数能构成一颗树。

---

「能构成一棵树」这个条件也太怪了吧，肯定是要转化的。怎么题解区都是结论怪啊？我不懂什么充要的结论，但是略微研究一下，能发现两条性质：

- 度为 $1$ 的点（称为一度点）能且只能当叶子。

- 度为 $2$ 的点（称为二度点）可忽略，因为它可以任意替换一条树边。

对于度 $\ge3$ 的点（称为多度点），设它们有 $c_0$ 个，度数之和为 $s$。

由性质一，它们一定是联通的。从而内部有 $c_0-1$ 条边、还需要外接 $s-2(c_0-1)$ 个一度点（因为一条边会贡献两个度数）。

设一度点有 $c_1$ 个，则「能构成一棵树」当且仅当 $s-2(c_0-1)=c_1$。

> 上面的证明严谨吗？非也。因为我们并不知道是否对于任意多度点的组合都**存在**一个树形连通块，如果不存在就无从谈起往里面加一度点了——虽然它的存在性几乎是显然的，只需考虑一条链。

再设 $v$ 中为 $1$ 的数有 $t_1$ 个、为 $2$ 的数有 $t_2$ 个。

上式提示我们，对于任意多度点的组合都唯一对应了一度点的**数量**（即使我们不知道它们是谁），而二度点是否存在无关紧要。故对于**一组**多度点的组合，它「能构成一棵树」的方案数就为

$$
2^{t_2}\binom{t_1}{s-2(c_0-1)}
$$

于是我们只需计数**每个** $s-2(c_0-1)$ 有多少。

先剔除 $v_i$ 中 $\le2$ 的元素，再令 $v^\prime_i\leftarrow v_i-2$，则 $s^\prime=s-2c_0$。

即我们只需对所有 $s^\prime-2=p\in[0,t_1]$ 统计 $v^\prime_i$ 的和为 $p$ 的子序列。

而这是经典问题。设答案为 $[z^p]F(z)$，则有

$$
F(z)=\prod\limits_{k\in v^\prime}(1+z^k)
$$

乘积不好处理，两边同时 $\ln$，有

$$
\ln F(z)=\sum\limits_{k\in v^\prime}\ln(1+z^k)
$$

由泰勒公式，有

$$
\ln(1+z)=z-\frac{z^2}2+\frac{z^3}3-\cdots=\sum\limits_{j=1}^\infty\frac{(-1)^j}{j}z^j
$$

则

$$
\ln(1+z^k)=\sum\limits_{j=1}^\infty\frac{(-1)^j}{j}z^{jk}
$$

这个式子可以暴力算了吗？当然不行。即使在模 $z^{t_1+1}$ 意义下，$\ln(1+z^k)$ 只会有 $\lfloor\frac{t_1+1}k\rfloor$ 项，但是如果所有 $k$ 都是 $1$，我们的复杂度依旧是 $O(t_1^2)=O(n^2)$。

注意到，如果多个相同的 $k$ 一起加，则只会让**变化量**相应扩倍。通过桶的方式，将相同的 $k$ 放在一起，这样暴力计算 $\ln F$ ，即使在最坏情况下，我们的枚举次数也只有

$$
\sum\limits_{k=1}^{t_1}\lfloor\frac{t_1+1}k\rfloor\leq\sum\limits_{k=1}^{t_1}\frac{t_1+1}k=(t_1+1)H_{t_1}=\Theta(t_1\log t_1)=O(n\log n)
$$

次，足以通过本题。

要是桶这部分不理解可以去看看 [经 典 老 番](https://www.luogu.com.cn/problem/P4389)

最后再求一遍 $\exp$，答案就到手了。总复杂度 $O(n\log n)$。

~~不过我的 $\sout{\exp}$ 是 $\sout{O(n\log^2n)}$ 的。~~

---

代码（省去了取模类与多项式类的定义）：

```cpp
Mod fac[MAXN],ifac[MAXN];
inline void init(int n){
    fac[0]=1; for(int i=1;i<=n;++i) fac[i]=fac[i-1]*i;
    ifac[n]=~fac[n]; for(int i=n;i>=1;--i) ifac[i-1]=ifac[i]*i;
}
inline Mod C(int n,int m){return fac[n]*ifac[m]*ifac[n-m];}

int buc[MAXN];
Mod pi[MAXN];
int main(){
    int n;
    qr(n);
    int c1=0,c2=0;
    for(int i=1;i<=n;++i){
        int u;
        qr(u);
        if(u==1) ++c1;
        if(u==2) ++c2;
        if(u>=3) ++buc[u-2];
    }
    Poly f(c1+1);
    for(int i=1;i<=c1;++i) pi[i]=(Mod)1/i;
    for(int i=1;i<=c1;++i){
        if(!buc[i]) continue;
        for(int j=i,t=1;j<=c1;j+=i,t*=-1) f[j]+=pi[j/i]*t*buc[i];
    }
    Poly g=exp(f);
    init(c1);
    Mod ans=0;
    for(int s=0;s<=c1;++s){
        ans+=g[s]*C(c1,s+2);
    }
    cout<<ans*qpow(2,c2);
}
```

---

## 作者：81179332_ (赞：1)

一些点可以组成一棵树当且仅当这些点的度数和 $=2n-2$

我们将所有点的度数 $-2$，则问题转化为求和为 $-2$ 的集合数

即求：$[x^{-2}]\prod\limits_{i=1}^n(1+x^{v_i-2})$

如果都是正整数次幂，很好解决：

$\prod\limits_{i=1}^n(1+x^{a_i})=Exp(\sum\limits_{i=1}^nLn(1+x^{a_i}))$

由于 $Ln(1+x^{a_i})=\sum\limits_{j=0}^{\inf}(-1)^{j-1}\dfrac{x^{a_ij}}{j}$，而我们只关心不大于 $n$ 次的项，所以很容易计算

设多项式 $G=\prod\limits_{i=1,v_i>2}^n(1+x^{v_i-2})$

问题就出在有非正整数幂，对于 $v_i=0$ 的项，显然选不选没有任何影响，所以我们直接在统计答案的时候乘上 $2^{cnt_0}$ 即可

对于 $v_i=-1$ 的项，我们枚举选了 $i$ 个，则 $ans+=\dbinom{cnt_{-1}}{i}G_{i-2}$

```cpp
const int mod = 998244353;
void up(int &a) { a += a >> 31 & mod; }
int qpow(int a,int b) { int ans = 1;for(;b;a = (ll)a * a % mod,b >>= 1) if(b & 1) ans = (ll)ans * a % mod; return ans; }
const int N = 2000010,G = 3,Gi = 332748118;
int rev[N];
void NTT(int *a,int n,int type)
{
	for(int i = 0;i < n;i++) if(i < rev[i]) swap(a[i],a[rev[i]]);
	for(int l = 2;l <= n;l <<= 1)
	{
		int m = l / 2;ll wn = qpow(~type ? G : Gi,(mod - 1) / l);
		for(int *p = a;p != a + n;p += l)
			for(int i = 0,w = 1;i < m;i++,w = (ll)w * wn % mod)
			{
				int t = (ll)w * p[i + m] % mod;
				up(p[i + m] = p[i] - t);
				up(p[i] = p[i] + t - mod);
			}
	}if(~type) return;
	int inv = qpow(n,mod - 2);
	for(int i = 0;i < n;i++) a[i] = (ll)a[i] * inv % mod;
}
void calc_rev(int &n,int &lim,int m)
{
	n = 1,lim = 0;while(n < m) n <<= 1,lim++;
	for(int i = 1;i < n;i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << lim - 1);
}
void Mul(int *a,int *b,int *c,int m1,int m2)
{
	static int x[N],y[N];
	int n,lim;calc_rev(n,lim,m1 + m2);
	for(int i = 0;i < m1;i++) x[i] = a[i];for(int i = m1;i < n;i++) x[i] = 0;
	for(int i = 0;i < m2;i++) y[i] = b[i];for(int i = m2;i < n;i++) y[i] = 0;
	NTT(x,n,1),NTT(y,n,1);for(int i = 0;i < n;i++) c[i] = (ll)x[i] * y[i] % mod;
	NTT(c,n,-1);for(int i = m1 + m2 - 1;i < n;i++) c[i] = 0;
}
void Inv(int *a,int *b,int len)
{
	static int c[N];
	if(len == 1) { b[0] = qpow(a[0],mod - 2);return; }
	Inv(a,b,len + 1 >> 1);
	int n,lim;calc_rev(n,lim,len << 1);
	for(int i = 0;i < len;i++) c[i] = a[i];for(int i = len;i < n;i++) c[i] = 0;
	NTT(c,n,1),NTT(b,n,1);
	for(int i = 0;i < n;i++) b[i] = (ll)(2 - (ll)c[i] * b[i] % mod + mod) * b[i] % mod;
	NTT(b,n,-1);for(int i = len;i < n;i++) b[i] = 0;
}
void Der(int *a,int *b,int len) { for(int i = 1;i < len;i++) b[i - 1] = (ll)a[i] * i % mod;b[len - 1] = 0; }
void Inte(int *a,int *b,int len) { for(int i = len - 1;i;i--) b[i] = (ll)a[i - 1] * qpow(i,mod - 2) % mod;b[0] = 0; }
void Ln(int *a,int *b,int len)
{
	static int c[N],inv[N];
	memset(inv,0,sizeof(inv));
	Der(a,c,len),Inv(a,inv,len);
	Mul(c,inv,c,len,len);
	Inte(c,b,len);
}
void Exp(int *a,int *b,int len)
{
	static int c[N];
	if(len == 1) { b[0] = 1;return; }
	Exp(a,b,len + 1 >> 1);
	int n,lim;calc_rev(n,lim,len << 1);
	Ln(b,c,len);
	for(int i = 0;i < n;i++) up(c[i] = a[i] - c[i]);
	c[0]++;for(int i = len;i < n;i++) c[i] = b[i] = 0;
	Mul(b,c,b,len,len);for(int i = len;i < n;i++) b[i] = 0;
}
int n,m,cnt[N];
int fac[N],ifac[N],inv[N];
int C(int n,int m) { return (ll)fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
void init()
{
	fac[0] = 1;for(int i = 1;i <= n;i++) fac[i] = (ll)fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n],mod - 2);for(int i = n;i;i--) ifac[i - 1] = (ll)ifac[i] * i % mod;
	for(int i = 1;i <= n;i++) inv[i] = (ll)ifac[i] * fac[i - 1] % mod;
}
int f[N],g[N],ans;
int main()
{
	n = read();init();
	for(int i = 1,x;i <= n;i++) if((x = read() - 2) == -1) m++; else cnt[x]++;
	for(int i = 1;i <= n;i++) if(cnt[i])
		for(int j = i,k = 1;j <= n;j += i,k++)
			if(k & 1) up(f[j] += (ll)inv[k] * cnt[i] % mod - mod);
			else up(f[j] -= (ll)inv[k] * cnt[i] % mod);
	Exp(f,g,n + 1);int res = qpow(2,cnt[0]);
	for(int i = 2;i <= m;i++) up(ans += (ll)C(m,i) * res % mod * g[i - 2] % mod - mod);
	fprint(ans);
}
```

---

## 作者：qczrz6v4nhp6u (赞：0)

最开始以为是计算树的个数，想了好久都不会做（

### Solution

考虑判别集合 $\{d_1,d_2,\cdots,d_m\}$ 能否组成树。不难得到条件：

$$\sum_{i=1}^mv_{d_i}=2m-2$$

不难证明这个条件是充要的。

把 $2m$ 移到左边去，就有：

$$\sum_{i=1}^mv_{d_i}-2=-2$$

构造生成函数 $F(x)=\prod_{i=1}^n(1+x^{v_i-2})$，则答案即为 $[x^{-2}]F(x)$。

发现 $F(x)$ 可能有负次数项，考虑将 $v_i-2$ 按正负性分别计算贡献，最后再乘起来。注意到 $v_i-2<0$ 当且仅当 $v_i=1$，则其贡献为 $(1+x^{-1})^k=\sum_{i=0}^k{k\choose i}x^{-i}$（$k=\sum_{i=1}^n[v_i-2<0]$），我们不必计算 $v_i-2<0$ 的生成函数；$v_i-2=0$ 的贡献是 $2$ 的幂次，我们可以在最后统计这部分的贡献。

接下来的任务是计算 $G(x)=\prod_{i=1}^n[v_i-2>0](1+x^{v_i-2})$。喜闻乐见的，考虑 $\ln-\exp$：

$$G(x)=\exp(\sum_{i=1}^n[v_i-2>0]\ln(1+x^{v_i-2}))$$

考虑计算 $\ln(1+x^p)$。一个经典的结论是：

$$\ln(1+x)=\sum_{i\ge 1}\frac{(-1)^{i-1}x^i}{i}$$

该式不难通过泰勒展开证明。于是有：

$$\ln(1+x^p)=\sum_{i\ge 1}\frac{(-1)^{i-1}x^{pi}}{i}$$

调和级数均摊可以直接统计，将得到的多项式进行 $\exp$ 即可。时间复杂度 $O(n\log n)$。

### Code

给出多项式模板以外的部分，使用的多项式模板可以在 [这里](https://www.luogu.com.cn/paste/84l2m647) 找到。

```cpp
int n,v[N],c0,c1;
ll F[N],c[N],fac[N],ifac[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>v[i],v[i]-=2;
		if(!v[i])++c0;
		else if(v[i]==-1)++c1;
		else ++c[v[i]];
	}
	if(c1<2)return cout<<0<<'\n',0;
	else if(c1==2)return cout<<qpow(2,c0)<<'\n',0;
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	ifac[n]=qpow(fac[n],-1);
	for(int i=n;i>=1;i--)ifac[i-1]=ifac[i]*i%mod;
	int m=c1-2;
	for(int i=1;i<=m;i++)
		for(int j=1;i*j<=m;j++)
			F[i*j]=(F[i*j]+c[i]*(j&1?1:mod-1)%mod*ifac[j]%mod*fac[j-1])%mod;
	Poly::exp(F,m+1,F);
	ll ans=0;
	for(int i=0;i<=m;i++)
		ans=(ans+F[i]*fac[c1]%mod*ifac[i+2]%mod*ifac[c1-i-2])%mod;
	cout<<ans*qpow(2,c0)%mod<<'\n';
	return 0;
}
```

---

