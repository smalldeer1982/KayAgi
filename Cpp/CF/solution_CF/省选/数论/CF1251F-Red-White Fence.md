# Red-White Fence

## 题目描述

Polycarp想在他家附近建一道栅栏。他有$n$个白板和$k$个红板去建造它。每一块板都有一个整数长度。

一个好的栅栏应由一块红板和几块（可能是零块）白板组成。红色的板应该在这道栅栏中是**最长的**，而且红板前的板子长度应为递增，而红板之后的板子长度为递减。如果用了$m$块板子，它们的长度从左到右依次是$l_1,l_2,…,l_m$，那么应该符合以下条件

①栅栏上应**有且只有一块**红板，设其序号为$j$

②对于所有的$i∈[1,j-1]$有$l_i<l_{i+1}$

③对于所有的$i∈[j,m-1]$有$l_i>l_{i+1}$

在Polycarp建造他的栅栏时，他会从左向右在$0$高度上放置所有板，没有间隙，所以这些板将会组成一个多边形：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1251F/3ccd14049951133b56808a6aa4dc98b4083c170d.png)

例图：一个栅栏的板长数组为$[3,5,4,2,1]$，第二个板是红板。栅栏的周长是$20$。Polycrp对一些特殊周长的栅栏感兴趣。他有喜欢的$q$个偶整数$[Q_1,Q_2,…,Q_q]$，对于每个这样的整数$Q_i$，他想计算有几种不同的周长是$Q_i$的篱笆可以被造出来（如果两个篱笆的板长排列不同，那么就认为这两个篱笆是不同的）你可以帮他计算这些数值吗？

## 说明/提示

对于第一个样例，可能的长度序列有（红板加粗）

·周长为$6$：$[$**2**$]$

·周长为$8$：$[1,$ **2**$]$,$[$**2**$,1]$

·周长为$10$：$[1,$ **2**$,1]$,$[$**4**$]$

·周长为$12$：$[1,$ **4**$]$,$[3,$ **4**$]$,$[$**4**$,1]$,$[$**4**$,3]$

·周长为$14$：$[1,$ **4**$,1]$,$[1,$ **4**$,3]$,$[3,$ **4**$,1]$,$[3,$ **4**$,3]$,$[1,3,$ **4**$]$,$[$**4**$,3,1]$

·周长为$16$：$[1,$ **4**$,3,1]$,$[3,$ **4**$,3,1]$,$[1,3,$ **4**$,1]$,$[1,3,$ **4**$,3]$

·周长为$18$：$[1,3,$ **4**$,3,1]$

## 样例 #1

### 输入

```
5 2
3 3 1 1 1
2 4
7
6 8 10 12 14 16 18
```

### 输出

```
1
2
2
4
6
4
1
```

## 样例 #2

### 输入

```
5 5
1 2 3 4 5
1 2 3 4 5
4
4 8 10 14
```

### 输出

```
1
3
5
20
```

# 题解

## 作者：Karry5307 (赞：12)

### 题意

有$n$块白板和$m$块红板，第$i$块白板的高度为$a_i$，第$i$块红板的高度为$b_i$。

规定一个栅栏是好的当且仅当组成它的只有一块红板，并且这块红板左边的所有白板高度严格递增，右边的高度严格递减。

现在有$q$组询问，每组询问有一个$Q$，你需要回答有多少种好的栅栏满足栅栏的周长为$Q$。

$\texttt{Data Range:}1\leq n,q,a_i,b_i\leq 3\times 10^5,1\leq m\leq 5,1\leq Q_i\leq 1.2\times 10^6$

### 题解

考虑到$\texttt{\color{black}E\color{red}ternalAlexander}$不贴代码还要让我们这等蒟蒻去$\texttt{CF}$上看，我决定写一篇有代码的题解。

组合计数好题。

因为栅栏高度是单峰的，~~由小学奥数可得~~，周长为$($中间红板的高度$+$组成栅栏的板子的个数$)\times 2$。于是，不妨把所有的询问除以$2$再看。

发现红色板子最多只有$5$个，我们可以考虑枚举每一个红色板子，在枚举得同时，中间红板子的高度就确定下来了。

先$\texttt{dp}$。设$dp_{i,j}$为用前$i$小的板子选出$j$个构成先上升后下降中间可以相等（这里只有白板子，所以可以相等）的方案数，有

$$dp_{i,j}=dp_{i-1,j-1}+2\times dp_{i,j-1}+[t_i\geq 2]dp_{i-1,j-2}$$

其中$t_i$是长度第$i$小的板子的个数，这个还是比较显然的。

但是这样做是$O(n^2)$的，并且这样一看好像写不出生成函数。

于是我们可以分开考虑这个$\texttt{dp}$式子。

假设所有板子互不相同，则答案为$2^jC_i^j$，对于选出的$j$个板子，任选放到左边或者右边即可。

如果所有长度相同的板子都有$2$块，答案是$C_{2i}^{j}$。

现在两个东西都有，所以我们考虑卷一起。

对于枚举到的长度为$b$红色木条，考虑$f_i=2^iC_{u}^i$和$g_i=C_{2v}^i$，其中$u$为长度小于$b$且数量为$1$的木条个数，$v$为长度小于$b$且数量大于等于$2$的木条个数，

把$f$和$g$卷起来就可以算出对于枚举到的木条对于每个周长的方案数，加一下即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=1048581,MOD=998244353,G=3,INVG=332748118;
ll cnt,kk,ccnt,x,u,v;
ll f[MAXN],g[MAXN],rev[MAXN],rres[MAXN],res[MAXN],p[MAXN];
ll fact[MAXN],finv[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
} 
inline ll qpow(ll base,ll exponent)
{
    ll res=1;
    while(exponent)
    {
        if(exponent&1)
        {
            res=(li)res*base%MOD;
        }
        base=(li)base*base%MOD,exponent>>=1;
    }
    return res;
}
inline void setup(ll cnt)
{
    fact[0]=finv[0]=1;
    for(register int i=1;i<cnt;i++)
    {
        fact[i]=(li)fact[i-1]*i%MOD;
    }
    finv[cnt-1]=qpow(fact[cnt-1],MOD-2);
    for(register int i=cnt-2;i;i--)
    {
        finv[i]=(li)finv[i+1]*(i+1)%MOD;
    }
}
inline ll comb(ll m,ll n)
{
	return m<n?0:(li)fact[m]*finv[m-n]%MOD*finv[n]%MOD;
}
inline void NTT(ll *cp,ll cnt,ll inv)
{
    ll cur=0,res=0,omg=0;
    for(register int i=0;i<cnt;i++)
    {
        if(i<rev[i])
        {
            swap(cp[i],cp[rev[i]]);
        }
    }
    for(register int i=2;i<=cnt;i<<=1)
    {
        cur=i>>1,res=qpow(inv==1?G:INVG,(MOD-1)/i);
        for(register ll *p=cp;p!=cp+cnt;p+=i)
        {
            omg=1;
            for(register int j=0;j<cur;j++)
            {
                ll t=1ll*omg*p[j+cur]%MOD,t2=p[j];
                p[j+cur]=(t2-t+MOD)%MOD,p[j]=(t2+t)%MOD;
                omg=1ll*omg*res%MOD;
            }
        }
    }
    if(inv==-1)
    {
        ll invl=qpow(cnt,MOD-2);
        for(register int i=0;i<=cnt;i++)
        {
            cp[i]=1ll*cp[i]*invl%MOD;
        }
    }
}
inline void conv(ll cnt,ll *f,ll *g,ll *res)
{
	static ll tmpf[MAXN],tmpg[MAXN];
	for(register int i=0;i<cnt;i++)
	{
		tmpf[i]=f[i],tmpg[i]=g[i];
	}
	ll limit=log2(cnt)-1;
	for(register int i=0;i<cnt;i++)
	{
		rev[i]=(rev[i>>1]>>1)|((i&1)<<limit);
	}
	NTT(tmpf,cnt,1),NTT(tmpg,cnt,1);
	for(register int i=0;i<cnt;i++)
	{
		res[i]=(li)tmpf[i]*tmpg[i]%MOD;
		tmpf[i]=tmpg[i]=0;
	}
	NTT(res,cnt,-1);
}
int main()
{
	setup((cnt=read())<<1),kk=read(),ccnt=1;
	while(ccnt<=(cnt<<1))
	{
		ccnt<<=1;
	}	
	for(register int i=1;i<=cnt;i++)
	{
		p[read()]++;
	}
	for(register int i=1;i<=kk;i++)
	{
		x=read(),u=v=0;
		for(register int j=1;j<x;j++)
		{
			p[j]==1?u++:p[j]>=2?v++:v;
		}
		for(register int j=0;j<ccnt;j++)
		{
			f[j]=(li)comb(u,j)*qpow(2,j)%MOD;
			g[j]=comb(v<<1,j);
		}
		conv(ccnt,f,g,rres);
		for(register int j=0;j<=cnt;j++)
		{
			res[j+x+1]=(res[j+x+1]+rres[j])%MOD;
		}
	}
	ccnt=read();
	for(register int i=0;i<ccnt;i++)
	{
		printf("%d\n",res[read()>>1]);
	}
}
```



---

## 作者：EternalAlexander (赞：10)

首先发现所求周长等于(中间红栅栏的高度+栅栏个数) $\times 2$，因此不妨先把所有询问都除以 $2$。然后注意到红栅栏个数很小，可以枚举中间的红色栅栏是什么。  

考虑所有 $a_i$ 互不相同的情况，询问 $k$ 的答案是 $2^k C_n^k$，因为可以任选 $k$ 个，每个可以放左边或者右边。  

接下来考虑相同的 $a_i$ ，不难发现两个以上相同的等价于两个相同的，假设有 $x$ 对相同的栅栏，答案为 $C_{2x}^k$，可以理解为任意一对如果第一个被选则表示左边放一个，第二个被选表示右边放一个，两个都被选表示两边都放。  

然后把两种情况卷一下得到答案。注意要加上当前红栅栏的长度 $+ 1$。

小号在cf上的提交暂时是最短解？  
[代码](https://codeforces.com/contest/1251/submission/63386062)

---

## 作者：dead_X (赞：5)

多项式学习 Day 3.

第一篇多项式题解 >_<
## 思路
注意到周长其实就是红板长度加上选的板子的数量。

于是当我们确定了红板长度 $L$ 和周长 $C$ 之后，我们需要取出 $\frac{C}{2}-L-1$ 块白板。

然后很恶心的是虽然板子不能一样长，但是可以在**红板两侧**各来一块相同长度的白板。

于是我们发现一种颜色的白板超过两条和两条是**等价的**。

然后我们考虑两种特殊情况：

* 所有白板都只有一条。

这种情况下，我们可以先选 $j$ 条，然后分别考虑每条放左边还是右边。

如果从 $i$ 种白板中选出 $j$ 条，那么有 $2^j\binom{i}{j}$ 种方案。

* 所有白板都有两条。

我们让第一条代表放在左边，第二条代表放在右边。

那么一种方案和选 $j$ 条板子是一一对应的。

那么如果从 $i$ 种白板种选出 $j$ 条，那么有 $\binom{2i}{j}$  种方案。

然后我们发现选出 $i$ 条白板的过程可以拆解成选出 $j$ 条**只有一条**的白板和 $i-j$ 条**有两条**的白板。

于是我们只需要把两部分拆开即可，先算出选出 $j$ 条**只有一条**的白板和**有两条**的白板的方案数，然后卷积即可。

**注意到白板的长度要小于红板，所以要对于每块红版单独 $\text{NTT}$ 一次。**
## 代码
```
//zhoukangyang AK IOI!
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const long long p=998244353;
long long qp(long long x,int y)
{
    long long res=1;
    for(long long now=x; y; now=now*now%p,y>>=1) if(y&1) res=res*now%p;
    return res;
}
long long A[6000003],B[6000003];
int rev[6000003],N=1;
void init()
{
    int d=N>>1;
    rev[0]=0,rev[1]=N>>1;
    for(int i=2; i<=N; i<<=1)
    {
        d>>=1;
        for(int j=0; j<i; ++j) rev[i+j]=rev[j]|d;
    }
    return ;
}
void NTT(long long* F,int op)
{
    for(int i=0; i<N; ++i) if(rev[i]>i) swap(F[i],F[rev[i]]);
    for(int len=2,M=1; len<=N; len<<=1,M<<=1)
    {
        long long w=qp(op?3:332748118,998244352/len);
        //omega(m,1)
        for(int l=0,r=len-1; l<=N; l+=len,r+=len)
        {
            long long w0=1;
            for(int i=l; i<l+M; ++i)
            {
                long long x=(F[i]+w0*F[i+M]%p)%p,y=(F[i]+p-w0*F[i+M]%p)%p;
                F[i]=x,F[i+M]=y,w0=w0*w%p;
            }
        }
    }
}
int cnt[1000003],b[13],q[1000003];
long long ans[1000003];
int t;
void solve(int lim)
{
	int P=0,Q=0;
	for(int i=1; i<lim; ++i) if(cnt[i]==1) ++P; else if(cnt[i]>=2) ++Q;
	Q<<=1;
	for(;N<=P+Q;N<<=1);
	for(int i=0; i<N; ++i) A[i]=B[i]=0;
	long long fz=1,fm=1;
    for(int i=0; i<=P; ++i,fz=fz*(P+1-i)%p,fm=fm*i%p) A[i]=fz*qp(fm,p-2)%p*qp(2,i)%p;
    fz=fm=1;
    for(int i=0; i<=Q; ++i,fz=fz*(Q+1-i)%p,fm=fm*i%p) B[i]=fz*qp(fm,p-2)%p;
    init();
    NTT(A,1),NTT(B,1);
    for(int i=0; i<N; ++i) A[i]=A[i]*B[i]%p;
    NTT(A,0);
    long long inv=qp(N,998244351);
    for(int i=0; i<N; ++i) A[i]=A[i]*inv%p;
    for(int j=1; j<=t; ++j) if(q[j]-lim>=0) ans[j]=(ans[j]+A[q[j]-lim])%p;
    return ;
}
signed main()
{
    int n=read(),k=read();
    for(int i=1; i<=n; ++i) ++cnt[read()];
    for(int i=1; i<=k; ++i) b[i]=read();
    t=read();
    for(int i=1; i<=t; ++i) q[i]=(read()>>1)-1;
    for(int i=1; i<=k; ++i) solve(b[i]);
	for(int i=1; i<=t; ++i) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Prean (赞：4)

很容易看出来答案之和红板子的高度以及白板子的数量有关系。。。

看到 $k\leq 5$ 所以直接考虑枚举红板子。

然后注意到，同样长度的板子超过 $2$ 无所谓，所以分为三类讨论：没有，有一个，有两个以上。

没有的情况对答案的贡献是 $1$，有一个的话可以放到左边或者右边，贡献为 $2$，两个以上可以只拿一个出来，也可以左边右边各一个。

设某种长度的白板子有 $c_kk$ 个，那么其贡献函数 $F_c(x)=(1+2x+x^2)\bmod{x^{k+1}}$。

那么要求的多项式就是 $G(x)=\prod_{c<b}F_c(x)$，然后求 $2(\sum g_i\times(b+i+1))$。

先对红白板子的长度排序，然后统计前缀有 $1$ 个和不小于 $2$ 个板子的数量。假设分别是 $a$ 和 $b$，那么计算一个 $(1+2x)^a(1+x)^{2b}$ 即可。显然可以做到 $O(kn\log n)$。

然后。。。这东西是可以列 ODE 算的。。。

设 $F(x)=(1+x)^a(1+2x)^b$，直接求导：
$$F'(x)=a(1+x)^{a-1}(1+2x)^{b}+2b(1+x)^{a}(1+2x)^{b-1}$$
$$(1+3x+2x^2)F'(x)=(a+2ax)F(x)+(2b+2bx)F(x)$$
$$(1+3x+2x^2)F'(x)=(a+2b+(2a+2b)x)F(x)$$
$$(n+1)\times f_{n+1}+3n\times f_{n}+(2n-2)\times f_{n-1}=(a+2b)\times f_{n}+(2a+2b)\times f_{n-1}$$
$$n\times f_{n}+(3n-3)\times f_{n-1}+(2n-4)\times f_{n-2}=(a+2b)\times f_{n-1}+(2a+2b)\times f_{n-2}$$
$$f_{n}=\frac{1}{n}((a+2b-3n+3)\times f_{n-1}+(4+2a+2b-2n)\times f_{n-2})$$
```cpp
#include<algorithm>
#include<cstdio>
#include<cctype>
#define IMP(lim,act) for(int qwq=(lim),i=0;i^qwq;++i)act
const int M=1<<20|5,mod=998244353;
int n,k,ans[M<<1],x[M],y[10],a[10],b[10],inv[M];
inline int Getlen(const int&n){
	int len(0);while((1<<len)<n)++len;return len;
}
inline int pow(int a,int b=mod-2){
	int ans(1);for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;return ans;
}
inline void init(const int&n){
	inv[0]=inv[1]=1;for(int i=2;i<n;++i)inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}
inline void Get(int*f,const int&a,const int&b){
	const int&n=a+b+1;f[0]=1;f[1]=(a+b*2)%mod;
	for(int i=2;i<n;++i){
		f[i]=1ll*((a+2ll*b+(mod-3ll)*i+3)%mod*f[i-1]+(4ll+2*a+2*b+(mod-2ll)*i)%mod*f[i-2])%mod*inv[i]%mod;
	}
}
inline int read(){
	int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
}
inline void write(int n){
	static char s[15];int top(0);while(s[++top]=n%10^48,n/=10);while(putchar(s[top]),--top);putchar(10);
}
signed main(){
	n=read();k=read();for(int i=1;i<=n;++i)x[i]=read();for(int i=1;i<=k;++i)y[i]=read();
	init(n+1<<1);std::sort(x+1,x+n+1);std::sort(y+1,y+k+1);
	for(int id(1),sum(0),A(0),B(0),t=1;t<=k;++t){
		while(x[id]<y[t]&&id<=n){
			++sum;
			if(x[id]!=x[id+1]){
				if(sum==1)++A;else if(sum)++B;
				sum=0;
			}
			++id;
		}
		static int F[M];Get(F,B<<1,A);IMP(A+B*2+1,ans[i+y[t]+1<<1]=(ans[i+y[t]+1<<1]+F[i])%mod);
	}
	k=read();while(k--)write(ans[read()]);
}
```

---

## 作者：tzc_wk (赞：3)

考虑这个奇怪的东西的周长是什么玩意儿，通过小学教的平移法可以求出 $C=(\text{红色木板的长度}+\text{选用的木板个数})\times 2$。

看到 $k$ 这么小，那肯定要枚举选择哪个红色木板，这样也可以唯一确定选用的木板的个数。

于是考虑状态 $dp_{i,j}$ 表示选择的红色木板编号为 $i$，选择 $j$ 个木板的方案数。

那么怎样求 $dp_{i,j}$ 呢？

首先肯定要明确的一点是，同一种长度的白色木板顶多出现 $2$ 次。

考虑枚举白色木板的长度，再设 $f_{i,j}$ 表示对于长度 $\leq i$ 的木板，选择了 $j$ 个的方案数。

分情况讨论：

1. 若没有长度为 $i$ 的白色木板，那显然 $f_{i,j}=f_{i-1,j}$

2. 若只有 $1$ 个长度为 $i$ 的木板，那 $f_{i,j}=f_{i-1,j}+2f_{i-1,j-1}$，$f_{i-1,j}$ 表示不选这个长度为 $i$ 的木板，$2f_{i-1,j-1}$ 表示选择长度为 $i$ 的木板，而它有放在红色木板左边和右边两种选择，故要乘个 $2$。

3. 若有 $2$ 个（或更多）长度为 $i$ 的木板，那 $f_{i,j}=f_{i-1,j}+2f_{i-1,j-1}+f_{i-1,j-2}$，$f_{i-1,j}$ 表示不选这个长度为 $i$ 的木板，$2f_{i-1,j-1}$ 表示选择一个长度为 $i$ 的木板，而它有放在红色木板左边和右边两种选择，故要乘个 $2$，$f_{i-1,j-2}$ 表示选择两个长度为 $i$ 的木板，显然它们只能一左一右地放，故只有 $1$ 种选择。

通过上面的分析，不难看出情况 $1$ 相当于啥也没干，情况 $2$ 相当于将多项式 $f$ 与 $2x+1$ 求一个卷积，情况 $3$ 相当于将多项式 $f$ 与 $x^2+2x+1$ 求个卷积。

设 $c_i$ 表示有多少个长度为 $i$ 的木板，故我们只用求出 $c_i=1$ 和 $c_i\geq 2$ 的 $i$ 的个数，将其假设为 $x_1,x_2$。

那么最终的 $f$ 就是 $(2x+1)^{x_1}\times (x^2+2x+1)^{x_2}$，稍微求个卷积即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXW=3e5;
const int MAXR=5;
const int MAXL=3e5;
const int MAXP=1<<19;
const int pr=3;
const int MOD=998244353;
int qpow(int x,int e){int ret=1;for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;return ret;}
int n,k,qu,a[MAXW+5],b[MAXR+5],c[MAXL+5];
int LEN=1,LOG=0,A[MAXP+5],B[MAXP+5],C[MAXP+5],ipr,rev[MAXP+5],inv[MAXP+5],prs[MAXP+5][2];
int f[MAXR+5][MAXW+5];
void NTT(int *a,int len,int type){
	int lg=log2(len);
	for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=2;i<=len;i<<=1){
		int W=prs[i][type<0];
		for(int j=0;j<len;j+=i){
			int w=1;
			for(int k=0;k<(i>>1);k++,w=1ll*w*W%MOD){
				int X=a[j+k],Y=1ll*a[(i>>1)+j+k]*w%MOD;
				a[j+k]=(X+Y)%MOD;a[(i>>1)+j+k]=(X-Y+MOD)%MOD;
			}
		}
	}
	if(type==-1) for(int i=0;i<len;i++) a[i]=1ll*a[i]*inv[len]%MOD;
}
void solve(int x){
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++) if(a[i]<b[x]) c[a[i]]++;
	int c1=0,c2=0;
	for(int i=1;i<b[x];i++){
		if(c[i]==1) c1++;
		if(c[i]>=2) c2++;
	}
//	printf("%d %d\n",c1,c2);
	for(int i=0;i<LEN;i++) A[i]=B[i]=C[i]=0;
	A[0]=B[0]=B[2]=1;A[1]=B[1]=2;
	NTT(A,LEN,1);NTT(B,LEN,1);
	for(int i=0;i<LEN;i++) A[i]=qpow(A[i],c1);
	for(int i=0;i<LEN;i++) B[i]=qpow(B[i],c2);
	for(int i=0;i<LEN;i++) C[i]=1ll*A[i]*B[i]%MOD;
	NTT(C,LEN,-1);
//	for(int i=0;i<=n;i++) printf("%d ",C[i]);printf("\n");
	for(int i=0;i<=n;i++) f[x][i]=C[i];
}
int main(){
	scanf("%d%d",&n,&k);ipr=qpow(pr,MOD-2);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=k;i++) scanf("%d",&b[i]);
	while(LEN<=n) LEN<<=1,LOG++;
	for(int i=1;i<=LEN;i<<=1){
		inv[i]=qpow(i,MOD-2);
		prs[i][0]=qpow(pr,(MOD-1)/i);
		prs[i][1]=qpow(ipr,(MOD-1)/i);
	}
	for(int i=1;i<=k;i++) solve(i);
	scanf("%d",&qu);
	while(qu--){
		int x;scanf("%d",&x);x>>=1;x--;int ans=0;
		for(int i=1;i<=k;i++) if(x-b[i]>=0&&x-b[i]<=n) ans=(ans+f[i][x-b[i]])%MOD;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Kinesis (赞：3)

呜呜呜这道题想用$f^k(x) = e^{k\ln f(x)}$来偷懒的，结果被卡常了QAQ

首先对于周长的询问，可以发现其仅由所选红板子的高度$h = b_k$，以及所选白板子的数目$n$所决定，也即$Q = 2h + 2(n+1)$，故对于单个红板子$k$来说，可以预处理出对于每个$Q_i$，当栅栏选红板子$k$时所需要白板子的数量$N_i = \frac{Q_i - 2b_k}{2} - 1$。

其次由于红板子很小，可以轻松的把思路引向从单个红板子进行分析。

对于一个栅栏来说，由于栅栏的板长严格递增（递减），故在同侧无高度相同的板子。对于红板子$b_k$，预处理出所有比$a_i<b_k$的白板子长度及其数目。可以发现对于相同长度的白板子，至多只能选两个（放在红板子两侧）；当选一个白板子可以放在红板子的或左或右一侧。那么思路就很清晰啦：

> （1）对于相同长度的白板子来说，若数量只有1个，其可以选上放在栅栏的左侧或右侧，或者不选。
>
> （2）若数量大于1个，可以选两个放在栅栏的两侧，选一个放左侧或右侧，或者不选。

对于情况（1）,对于相同长度的白板子可以用生成函数$f_1(x) = 1 + 2x$来表示状态；对于情况（2），则可以用$f_2(x) = 1 + 2x + x^2 = (1+x)^2$来表示。

假设当前的红板子$k$，小于$b_k$的白板子的不同长度中，数量仅为1的白板子数量为$k_1$，数量大于1的白板子数量为$k_2$；则最终答案的状态可以表示为$f(x) = f_1^{k_1}(x) * f_2^{2k_2}(x)$。如果用 **指数多项式** 来加快多项式幂$f^k$的计算，再将$f_1^{k_1}*f_2^{2k_2},$复杂度为$O(knlogn)$（但指数多项式常数大的离谱- -总之我是TLE了）。发现$f_1,f_2$的幂都可用`binomial`来计算多项式系数，最后再乘起来，复杂度为$O(knlogn)$（其只来自于两个多项式的乘积）。

代码~~优化地有点丑~~：

```cpp
//code sourced from kinesis
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;

#define _REP(i,a,b) for(int i = (a) ; i >= (int)(b) ; --i )
#define REP(i,a,b) for(register int i = (a) ; i <= (int)(b) ; ++i )
#define UREP(i,u) for(int i = p[(u)] ; i + 1 ; i = edge[i].next)
//iterator: for(int u:x),x is container
#define x(p) (p).first
#define y(p) (p).second
#define pii pair<int,int>
#define mp(x,y) make_pair((x), (y))
#define sign(x) (fabs(x) < eps ? 0 : ((x) > 0 ? 1 : -1))
#define ll long long
#define L7 __int128//1<<7 bit
#define ull unsigned long long
const int inf = 0x3f3f3f3f;
const ll inff = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-9;
#define ri1(x) scanf("%d", &(x))
#define ri2(x,y) scanf("%d%d", &(x), &(y))
#define ri3(x,y,z) scanf("%d%d%d", &(x), &(y), &(z))
#define ri4(a,b,c,d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
//#define Debug
#ifdef Debug
#endif // Debug

namespace fastIO//支持int,ll,__int128.ull没有测试过
{
    static char buf[100000],*h=buf,*d=buf;//缓存开大可减少读入时间、、看题目给的空间
    #define gc h==d&&(d=(h=buf)+fread(buf,1,100000,stdin),h==d)?EOF:*h++//不能用fread则换成getchar
    template<typename T>
    inline void read(T&x)
    {
        int f = 1;x = 0;
        register char c(gc);
        while(c>'9'||c<'0'){
            if(c == '-') f = -1;
            c=gc;
        }
        while(c<='9'&&c>='0')x=(x<<1)+(x<<3)+(c^48),c=gc;
        x *= f;
    }
    template<typename T>
    void output(T x)
    {
        if(x<0){putchar('-');x=~(x-1);}
        static int s[20],top=0;
        while(x){s[++top]=x%10;x/=10;}
        if(!top)s[++top]=0;
        while(top)putchar(s[top--]+'0');
        putchar('\n');
    }
}
using fastIO::read;
using fastIO::output;

const int maxn = 524290;
namespace NTT
{
    const int mod = 998244353;//998244353,1004535809,469762049,985661441. g = 3
    inline int qp(ll base,ll n)//快速幂
    {
        ll res = 1;
        while(n){
            if(n&1) (res *= base) %= mod;
            (base *= base) %= mod;
            n>>=1;
        }
        return (int)res;
    }
    int rev[maxn<<1];
    inline void change(vector<int> &x,int len)
    {
        int bit = 0;
        while ((1<<bit)<len) bit++;
        REP(i,1,len-1){
            rev[i] = (rev[i>>1] >> 1) | ((i & 1) << (bit - 1));
            if (i<rev[i]) swap(x[i],x[rev[i]]);
        }//前面和FFT一样
    }
    inline void ntt(vector<int> &x, int lim, int opt)
    {
        change(x,lim);
        for (int m = 2; m <= lim; m <<= 1){
            int k = m >> 1;
            int gn = qp(3, (mod - 1) / m);
            for (int i = 0; i < lim; i += m){
                int g = 1;
                for (int j = 0; j < k; j+=2, g = 1ll * g * gn % mod){
                    int tmp = 1ll * x[i + j + k] * g % mod;
                    x[i + j + k] = (x[i + j] - tmp + mod) % mod;
                    x[i + j] = (x[i + j] + tmp) % mod;
                    if(j+1<k){
                        g = 1ll * g * gn % mod;
                        tmp = 1ll * x[i + j + 1 + k] * g % mod;
                        x[i + j + 1 + k] = (x[i + j + 1] - tmp + mod) % mod;
                        x[i + j + 1] = (x[i + j + 1] + tmp) % mod;
                    }
                }
            }
        }
        if (opt == -1){
            reverse(x.begin() + 1, x.begin() + lim);
            int inv = qp(lim, mod - 2);
            REP(i,0,lim-1) x[i] = 1ll * x[i] * inv % mod;
        }
    }
}
using NTT::ntt;

ll qp(ll base,ll n) {
    ll res = 1;
    base%=mod;
    while(n){
        if(n&1) (res *= base) %= mod;
        (base *= base) %= mod;
        n >>= 1;
    }
    return res;
}
namespace Comb
{
    ll Finv[maxn+10],fac[maxn+10],inv[maxn+10];
    void init()//n<N
    {
        int n = maxn;
        inv[1]=1;
        for(int i=2;i<=n;++i)inv[i]=((mod-mod/i)*inv[mod%i])%mod;
        fac[0]=Finv[0]=1;
        for(int i=1;i<=n;++i)fac[i]=fac[i-1]*i%mod,Finv[i]=Finv[i-1]*inv[i]%mod;
        //Finv[n]=modpow(jc[n],mod-2,mod);
        //for(int i=n-1;i>=1;--i)Finv[i]=Finv[i+1]*(i+1)%mod;
    }
    ll C(ll n,ll m)
    {
        if(m<0||m>n)return 0;
        return fac[n]*Finv[n-m]%mod*Finv[m]%mod;
    }
}
using Comb::C;

int a[maxn],b[10],Q[maxn],N[maxn],length[maxn],ans[maxn];
vector<int> f1(maxn<<1),f2(maxn<<1);

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);//cf needn't delete this
    #endif // ONLINE_JUDGE
    Comb::init();
    int n,m;
    read(n),read(m);
    REP(i,1,n) read(a[i]);
    REP(i,1,m) read(b[i]);
    int q;
    read(q);
    REP(i,1,q) read(Q[i]);
    REP(k,1,m){
        REP(i,1,b[k]) length[i] = 0;
        int k1 = 0,k2 = 0,mxN = 0,mxN2 = -inf,_2 = 1;
        REP(i,1,n) if(b[k] > a[i]) length[a[i]]++;
        REP(i,1,b[k]-1){
            if(length[i]==1) k1++,mxN++;
            if(length[i]>1) k2+=2,mxN+=2;
        }
        REP(i,1,q) N[i] = (Q[i] - 2 * b[k]) / 2 - 1,mxN2 = max(mxN2,N[i]);
        if(mxN2<0) continue;
        mxN = min(mxN,mxN2);
        mxN++;
        REP(i,0,mxN-1) f1[i] = 1LL * C(k1,i) * _2 % mod,_2 = 1LL * _2 * 2 % mod;
        REP(i,0,mxN-1) f2[i] = C(k2,i);
        int lim = 1;
        while(lim<(mxN * 2)) lim <<= 1;
        REP(i,mxN,lim-1) f1[i] = f2[i] = 0;
        ntt(f1,lim,1),ntt(f2,lim,1);
        REP(i,0,lim-1) f1[i] = 1LL * f1[i] * f2[i] % mod;
        ntt(f1,lim,-1);
        REP(i,1,q) if(0<=N[i]&&N[i]<=mxN) (ans[i] += f1[N[i]]) %= mod;
        REP(i,0,lim-1) f1[i] = f2[i] = 0;
    }
    REP(i,1,q) output(ans[i]);
    return ~~(0-0);
}
```

---

