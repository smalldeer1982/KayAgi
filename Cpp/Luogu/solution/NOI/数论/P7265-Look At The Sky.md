# Look At The Sky

## 题目背景

![Look At The Sky](https://mivik.gitee.io/image/nurture/look_at_the_sky.jpeg)

> Look at the sky, I'm still here
>
> I'll be alive next year
>
> I can make something good, oh
>
> Something good

本题加强版：[U148588](https://www.luogu.com.cn/problem/U148588)

## 题目描述

Mivik 又把 $(x+y)^2$ 当成 $(x^2+y^2)$ 来算了！蒟蒻的他望向天空，看见朵朵白云飘散又融合，忽然来了灵感，写下了一个序列 $S$ 的 $k$ 阶平均数的定义：
$$
avg_k(S)=\frac{\sum_{i=1}^{|S|}{S_i^k}}{\left(\sum_{i=1}^{|S|}S_i\right)^k}
$$
Mivik 想起 2020 年发生的一切，对他而言很重要的一共有 $n$ 件。例如，举办了自己的第一场比赛、见证了 Porter Robinson 时隔一年后重新在音乐界活跃、和那个人相遇... 其中有一些事件之间相互有联系，也就是说它们形成了一张无向图。Mivik 把这个无向图的所有极大连通块的大小依次写在了一张白纸上，认为这代表了他 2020 年所经历的一切。或美好、或悲伤，Mivik 现在把这张白纸折成了纸飞机准备放飞它。不过在此之前，Mivik 想要求一下这个白纸上的数的 $k$ 阶平均数，并作为 2020 年的纪念记录在日记本上。

可惜的是，Mivik 的记性不太好：他只记得一共发生了 $n$ 件大事，但却记不清它们之间的关系了。Mivik 干脆让你求出在所有可能的情况下，这个白纸上的数的 $k$ 阶平均数之和。实际上，Mivik 并不在意 $k$ 是什么，他只在意最终的答案写在日记本上是否美观，于是他干脆让你对所有 $k\in [0,K]$ 算出上面的值，这样他好选出一个。

两种情况本质不同，当且仅当存在两件事情，它们在一种情况中没有联系而在另一种情况中有。

形式化题意：记一张无向图的连通块集合 $f(G)$ 为这张图所有极大连通块的大小形成的任意顺序的序列，要求对所有 $k\in [0,K]$ 求：
$$
\sum_{G\in S(n)}\frac{\sum_{i=1}^{|f(G)|}{f(G)_i^k}}{\left(\sum_{i=1}^{|f(G)|}f(G)_i\right)^k}
$$
$S(n)$ 为所有大小为 $n$ 的无向图形成的集合。答案对 $998244353$ 取模。如果你不知道如何将一个有理数对质数取模，可以参考 [有理数取模](https://www.luogu.com.cn/problem/P2613)。

## 说明/提示


### 样例解释

样例一：两个点的无向图只有两种，即两个点之间有边和无边，那么 $k=0$ 时的答案为 $\frac{1^0+1^0}{(1+1)^0}+\frac{2^0}{(2)^0}=1+2=3$。

样例二：三个点的无向图有以下 8 种：

![样例二](https://cdn.luogu.com.cn/upload/image_hosting/bu2h64fw.png)

$k=0$ 时，答案为 $\frac{1^0+1^0+1^0}{(1+1+1)^0}+3\times\frac{1^0+2^0}{(1+2)^0}+4\times\frac{3^0}{(3)^0}=3+3\times2+4\times1=13$；

$k=1$ 时，答案为 $\frac{1^1+1^1+1^1}{(1+1+1)^1}+3\times\frac{1^1+2^1}{(1+2)^1}+4\times\frac{3^1}{(3)^1}=1+3\times1+4\times1=8$；

$k=2$ 时，答案为 $\frac{1^2+1^2+1^2}{(1+1+1)^2}+3\times\frac{1^2+2^2}{(1+2)^2}+4\times\frac{3^2}{(3)^2}=\frac13+3\times\frac59+4\times1=6$。

### 数据范围

对于全部数据，有 $1\le n\le 2\cdot10^5$，$0\le K\le 5000$。

Subtask 1 (5 pts)：保证 $n=1$。

Subtask 2 (10 pts)：保证 $n=2$。

Subtask 3 (25 pts)：保证 $K=0$。

Subtask 4 (25 pts)：保证 $0\le K\le 10$。

Subtask 5 (35 pts)：无特殊限制。


## 样例 #1

### 输入

```
2 0```

### 输出

```
3```

## 样例 #2

### 输入

```
3 2```

### 输出

```
13
8
6```

## 样例 #3

### 输入

```
10 0```

### 输出

```
83728116```

# 题解

## 作者：SSerxhs (赞：5)

套路二合一

$n^kans=\sum\limits_{G}\sum\limits_{v\in G} v^k$

$=\sum\limits_{v=1}^n v^kf_v$

$f_v$ 表示数量 $v$ 对答案的贡献

考虑选 $v$ 个点硬点他们连通，有 $f_v=\tbinom{n}{v}g_v h_{n-v}$，其中 $g_v$ 表示 $v$ 个点连通的方案数， $h_{v}$ 表示 $v$ 个点的方案数

考虑每条边选或不选有 $h_v=2^{\frac{v(v-1)}{2}}$

$g_v$ 是[城市规划](https://www.luogu.com.cn/problem/P4841)问题，没做过建议先写这题

于是我们 $O(n\log n)$ 计算出所有 $f_v$

接下来考虑如何对所有的 $k$ 求解

暴力求解是 $O(kn)$ 的，卡了一年常没卡进去

幂函数是很烦的，考虑套路第二类斯特林数展开（证明可以参考[这篇题解](https://www.luogu.com.cn/blog/SSerxhs/solution-p2791)）

$ans=\sum\limits_{v=1}^n f_v\sum\limits_{j=0}^kS_2(k,j)j!\tbinom{v}{j}$

$=\sum\limits_{j=0}^kS_2(k,j)\sum\limits_{v=1}^n f_v\frac{v!}{(v-j)!}$

后面明显是个差卷积，没学过可以写一下[力](https://www.luogu.com.cn/problem/P3338)

那么可以对所有的 $j$ 计算出后面的值 $x_j$

则 $ans=\sum\limits_{j=0}^kS_2(k,j)x_j$

那么只需要知道第二类斯特林数就可以计算答案了

考虑斯特林数的组合意义， $n$ 个球放入 $m$ 个盒子，那么第 $n$ 个可以和前面的一起或者新加一个盒子

那么 $S_2(n,m)=S_2(n-1,m)\times m+S_2(n-1,m-1)$

边界条件 $S_2(n,0)=[n=0]$

可以递推得到所有所需的第二类斯特林数。本题可能卡空间，可以滚动数组优化。

总复杂度 $O(n\log n+k^2)$
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
std::mt19937 rnd(time(0));
inline int sj(int n)
{
	unsigned int x=rnd();
	return x%n+1;
}
#define rand fst
template<typename typC> void read(register typC &x)
{
	register int c=getchar(),fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
template<typename typC> void write(register typC x)
{
	if (x<0) putchar('-'),x=-x;
	static int st[100];
	register int tp=1,y;st[1]=x%10;x/=10;
	while (x) y=x/10,st[++tp]=x-y*10,x=y;++tp;
	while (--tp) putchar(st[tp]|48);
}
template<typename typC> void write(register typC *a,register int num)
{
	for (register int i=1;i<=num;i++) write(a[i]),putchar(i==num?10:32);
}
#define space(x) write(x),putchar(32)
#define enter(x) write(x),putchar(10)
const int N=262145<<1,p=998244353;
inline void inc(register int &x,const int y)
{
	if ((x+=y)>=p) x-=p;
}
inline void dec(register int &x,const int y)
{
	if ((x-=y)<0) x+=p;
}
inline int ksm(register int x,register int y)
{
	register int r=1;
	while (y)
	{
		if (y&1) r=(ll)r*x%p;
		x=(ll)x*x%p;y>>=1;
	}
	return r;
}
int a[N],b[N];
int f[N],ff[N],x[N],g[N],mi[N],r[N],yg[N],ig[N],inv[N],ifac[N],fac[N],s[2][5002];
int n,m,i,j,l,biglim,ans;
inline void ycl(int l,int limit)
{
	for (int i=1;i<limit;i++) r[i]=r[i>>1]>>1|(i&1)<<l;
}
inline void getg(int limit)
{
	ig[limit]=ksm(yg[limit]=ksm(3,(p-1)/limit),p-2);
	for (int i=limit>>1;i;i>>=1)
	{
		yg[i]=(ll)yg[i<<1]*yg[i<<1]%p;
		ig[i]=(ll)ig[i<<1]*ig[i<<1]%p;
	}
}
void dft(int *a,int xs,int limit)
{
	int i,j,k,l,w,wn,b,c;
	for (i=1;i<limit;i++) if (i<r[i]) swap(a[i],a[r[i]]);
	for (i=1;i<limit;i=l)
	{
		l=i<<1;
		if (xs) wn=yg[l]; else wn=ig[l];
		for (j=0;j<limit;j+=l)
		{
			w=1;
			for (k=0;k<i;k++,w=(ll)w*wn%p)
			{
				b=a[j|k];c=(ll)a[j|k|i]*w%p;
				a[j|k]=(b+c)%p;
				a[j|k|i]=(b+p-c)%p;
			}
		}
	}
	if (!xs)
	{
		xs=ksm(limit,p-2);
		for (i=0;i<limit;i++) a[i]=(ll)a[i]*xs%p; 
	}
}
inline void ginv(int n)
{
	inv[1]=ifac[0]=ifac[1]=1;
	for (int i=2;i<=n;i++) ifac[i]=(ll)ifac[i-1]*(inv[i]=p-(ll)p/i*inv[p%i]%p)%p;
}
inline void ji(int *a,int n)
{
	for (int i=n+1;i;i--) a[i]=(ll)a[i-1]*inv[i]%p;
	a[0]=1;
}
inline void dao(int *a,int n)
{
	for (int i=0;i<n;i++) a[i]=(ll)a[i+1]*(i+1)%p;
	a[n]=0;
}
void getinv(int *f,int *g,int biglim)
{
	int i,l=1,limit,j;
	g[0]=ksm(f[0],p-2);
	for (i=2;i<=biglim;i=limit,l++)
	{
		limit=i<<1;
		memcpy(x,f,limit<<1);
		ycl(l,limit);
		dft(x,1,limit);dft(g,1,limit);
		for (j=0;j<limit;j++) g[j]=(ll)g[j]*(2-(ll)g[j]*x[j]%p+p)%p;
		dft(g,0,limit);
		memset(g+i,0,limit<<1);
	}
}
inline int C(register int n,register int m)
{
	return (ll)fac[n]*ifac[m]%p*ifac[n-m]%p;
}
int main()
{
	read(n);read(m);
	if (n==1)
	{
		for (i=0;i<=m;i++) puts("1");return 0;
	}
	if (n==2)
	{
		puts("3");
		for (i=1;i<=m;i++) printf("%d\n",(1+ksm(ksm(2,p-2),i-1))%p);
		return 0;
	}
	fac[0]=1;
	for (i=1;i<=n;i++) fac[i]=(ll)fac[i-1]*i%p;
	ginv(n);
	for (i=0;i<=n;i++) f[i]=(ll)(ff[i]=ksm(2,((ll)i*(i-1)>>1)%(p-1)))*ifac[i]%p;
	biglim=1;
	while (biglim<=n) biglim<<=1;
	getg(biglim<<1);
	getinv(f,g,biglim);
	dao(f,n);
	biglim<<=1;
	dft(f,1,biglim);dft(g,1,biglim);
	for (i=0;i<biglim;i++) f[i]=(ll)f[i]*g[i]%p;
	dft(f,0,biglim);
	ji(f,n);
	for (i=1;i<=n;i++) f[i]=(ll)f[i]*fac[i]%p;
	for (i=1;i<=n;i++) f[i]=(ll)f[i]*ff[n-i]%p*C(n,i)%p*fac[i]%p;
	f[0]=0;memset(f+n+1,0,sizeof(f)-(n+1<<2));
	memset(g,0,sizeof(g));
	for (i=0;i<=n;i++) g[n-i]=f[i];
	memset(f,0,sizeof(f));
	for (i=0;i<=n;i++) f[i]=ifac[i];
	dft(f,1,biglim);dft(g,1,biglim);
	for (i=0;i<biglim;i++) f[i]=(ll)f[i]*g[i]%p;
	dft(f,0,biglim);
	memset(g,0,sizeof(g));
	for (i=0;i<=n;i++) g[n-i]=f[i];
	register int i,j;int nn=n,mm=m;
	register int n=nn,m=mm,ans=0,y;
	s[0][0]=1;
	for (j=0;j<=m;j++)
	{
		ans=0;y=j&1;
		for (i=0;i<=j;i++) ans=(ans+(ll)s[y][i]*g[i])%p;
		s[y^1][0]=0;++j;
		for (i=1;i<=j+1;i++) s[y^1][i]=((ll)s[y][i]*i+s[y][i-1])%p;
		--j;ans=(ll)ans*ksm(ksm(n,j),p-2)%p;printf("%d\n",ans);
	}
}
```

---

## 作者：Mivik (赞：5)


[欢迎到我的博客查看](https://mivik.gitee.io/2021/solution/mivik-round-nurture-look-at-the-sky/)

## Subtask 1

显然输出 $(K+1)$ 行 `1` 即可。

## Subtask 2

发现答案就是 $\frac{1^k+1^k}{2^k}+\frac{2^k}{2^k}=2^{1-k}+1$，直接计算即可。

## Subtask 3

观察到分母恒为 $n^k$，那么就变成了问所有 $n$ 个点的无向图的连通块大小的 $k$ 次方之和。这个是很显然的。首先我们设 $n$ 个点无向图的个数的 EGF 为 $H(x)$，显然有：
$$
H(x)=\sum_{i=0}^\infty\frac{2^\binom i2}{i!}x^i
$$
设 $n$ 个点无向连通图的个数的 EGF 为 $G(x)$。由于无向图是由多个无向连通图形成的连通块组合形成的，那么根据 EGF 的组合意义我们得到：
$$
\begin{aligned}
H(x)&=\sum_{i=0}^\infty \frac{G^i(x)}{i!}\\
&=e^{G(x)}
\end{aligned}
$$
于是有 $G(x)=\ln H(x)$。然后我们来考虑答案。对于一个 $k$ 来讲，我们枚举连通块的大小及其贡献，得到：
$$
ans_k=\frac1{n^k}\sum_{i=1}^ni^k\binom niG_iH_{n-i}
$$
我们设 $G_i H_{n-i}$ 为 $F_i$，那么有：
$$
\begin{aligned}
ans_k&=\frac1{n^k}\sum_{i=1}^ni^k\binom niF_i\\
&=\frac{n!}{n^k}\sum_{i=1}^n\frac{F_i}{i!(n-i)!}i^k\\
&=\frac{n!}{n^k}\sum_{i=1}^n\frac{F_i}{i!(n-i)!}\sum_{j=0}^k\begin{Bmatrix}k\\j\end{Bmatrix}i^{\underline{j}}\\
&=\frac{n!}{n^k}\sum_{j=0}^k\begin{Bmatrix}k\\j\end{Bmatrix}\sum_{i=j}^n\frac{F_i}{(n-i)!(i-j)!}
\end{aligned}
$$
后面那个东西下标反转后很明显可以卷积，那么就 $O(n\log n+k^2)$ 解决了。

此外这道题实际上可以做 $1\le K\le 2\cdot 10^5$。这里是 [加强版](https://www.luogu.com.cn/problem/U148588) 和 [题解](https://mivik.gitee.io/2021/solution/mivik-round-nurture-look-at-the-sky-ex/)。

[mivik.h](https://mivik.gitee.io/mivik.h)

[代码](https://paste.ubuntu.com/p/ftMcytXd59/)


---

## 作者：苹果蓝17 (赞：1)

[题目传送门（简单版）](https://www.luogu.com.cn/problem/P7265)

[题目传送门（加强版）](https://www.luogu.com.cn/problem/U148588)

[更好的阅读体验](https://www.cnblogs.com/Appleblue17/p/15091975.html)

套路二合一……

#### 题意简述

记 $S(n)$ 为所有大小为 $n$ 的无向图形成的集合，一张无向图的连通块集合 $f(G)$ 为这张图所有极大连通块的大小形成的任意顺序的序列，对所有 $k \in [0,K]$ 求：

$$s_k=\sum\limits_{G \in S(n)} \dfrac{\sum\limits_{i=1}^{|f(G)|}f(G)_i^k}{(\sum\limits_{i=1}^{|f(G)|}f(G)_i)^k}$$

$n,k \leq 2 \times 10^5$。

#### 题目分析

显然分母是 $n^k$，记 $s_k=\sum\limits_{G \in S(n)} \sum\limits_{i=1}^{|f(G)|}f(G)_i^k$。

接下来变成了求和的形式，交换和号：

$$s_k=\sum\limits_{i=1}^n i^k \sum\limits_{G \in S(n)} [i \in f(G)]$$

后面的和式与 $k$ 无关了，记 $f_t=\sum\limits_{G \in S(n)} [t \in f(G)]$。

记 $g_t$ 为大小为 $t$ 的无向图个数， $h_t$ 为大小为 $t$ 的联通无向图个数，有：

$$g_t=2^{t(t-1)/2}$$

由 exp 的组合意义（或者有标号 Set 构造），设 $\hat H(x)$，$\hat G(x)$ 分别为 $h_t$，$g_t$ 的指数型生成函数，有 $\hat G(x)=\exp \hat H(x)$，即 $\hat H(x)=\ln \hat G(x)$。

显然有 $f_t= \dbinom{n}{t} h_t g_{n-t}$，即先选取 $t$ 个点组成联通块，再用剩下的 $n-t$ 个点组成无向图。

现在 $f_t$ 求出来了，只需要求出 $s_k=\sum \limits_{i=1}^n i^k f_i$。

这是一个经典问题，考虑写出 $s_k$ 的生成函数 $S(x)$：

$$S(x)=\sum\limits_{k} x^k \sum\limits_{i=1}^n i^kf_i=\sum\limits_{i=1}^n f_i \sum\limits_{k} (ix)^k=\sum\limits_{i=1}^n \dfrac{f_i}{1-ix}$$

直接分治 NTT 即可，总时间复杂度 $O(n \log^2 n+k \log k)$。

~~为啥简单版这么卡常……~~

#### 代码

```cpp
......
int n,K;
int F[N],G[N],H[N];
int lenp[N],lenq[N],tmp[N];
vector <int> P[N],Q[N];
 
void init(int o,int l,int r){
	int len=r-l+1,mid=(l+r)>>1ll;
	if(o==1) len=max(n,K);
	lenp[o]=len;
	lenq[o]=len;
	P[o].resize(2*lenp[o]+2);
	Q[o].resize(2*lenq[o]+2);
	if(l==r) return ;
	init(o<<1,l,mid);
	init(o<<1|1,mid+1,r);
}
 
void solve(int o,int l,int r){
	int len=r-l+1;
	if(l==r){
		P[o][0]=F[l];
		Q[o][0]=1,Q[o][1]=(mod-l)%mod;
		return ;
	}
	int mid=(l+r)>>1;
	solve(o<<1,l,mid);
	solve(o<<1|1,mid+1,r);
	
	NTT::solve(P[o].data(),P[o<<1].data(),Q[o<<1|1].data(),lenp[o<<1],lenq[o<<1|1]);
	NTT::solve(tmp,Q[o<<1].data(),P[o<<1|1].data(),lenq[o<<1],lenp[o<<1|1]);
	for(int i=0;i<=len;i++) P[o][i]=(P[o][i]+tmp[i])%mod;
	
	NTT::solve(Q[o].data(),Q[o<<1].data(),Q[o<<1|1].data(),lenq[o<<1],lenq[o<<1|1]); 
}

int main(){
	pre();
	cin>>n>>K;
	for(int i=0;i<=n;i++) H[i]=1ll*ksm(2,S(i))*inv[i]%mod;//求出 H(x)
	poly::Ln(G,H,n);//求出 G(x)
	for(int i=0;i<=n;i++) F[i]=1ll*G[i]*mul[i]%mod*H[n-i]%mod*mul[n-i]%mod*C(n,i)%mod;//求出 F(x)
	init(1,1,n);
	solve(1,1,n);
	INV::solve(Q[1].data(),Q[1].data(),K);
	NTT::solve(P[1].data(),P[1].data(),Q[1].data(),K,K);
	for(int k=0;k<=K;k++) printf("%lld\n",1ll*P[1][k]*ksm(n,mod-1-k)%mod);
}
```

---

## 作者：littlez_meow (赞：0)

朴素的图论计数二合一。

[题目指路](https://www.luogu.com.cn/problem/P7265)。

## 思路

发现分母始终为 $n^k$，问题变成求 $n$ 个点有标号无向图所有极大连通块大小的 $k$ 次方和。

写成式子，就是：

$$\sum\limits_{G\in S(n)}\sum\limits_{t\in f(G)}t^k$$

交换枚举顺序，得到：

$$\sum\limits_{i=1}^ni^k\sum\limits_{G\in S(n)}[i\in f(G)]$$

考虑求 $\sum\limits_{G\in S(n)}[i\in f(G)]$。钦定其中有 $i$ 个点的连通块，剩下点随便连，还要钦定标号，得到：

$$\sum\limits_{G\in S(n)}[i\in f(G)]=g_ih_{n-i}\dbinom{n}{i}$$

其中 $g_n$ 为 $n$ 个点有标号无向连通图个数，$h_n$ 为 $n$ 个点有标号无向图个数。设其 EGF 分别为 $G(x),H(x)$，根据[经典结论](https://www.luogu.com.cn/problem/P4841)，有 $[\dfrac {x^n}{n!}]H(x)=2^{\binom n 2},G(x)=\ln H(x)$。

然后就可以 $O(n\log n)$ 求出 $\sum\limits_{G\in S(n)}[i\in f(G)]$，设其为 $f_i$。

回到求分子。带入 $f_i$，得到：

$$\sum\limits_{i=1}^ni^kf_i$$

经典套路，将普通幂换成下降幂：

$$\sum\limits_{i=1}^nf_i\sum\limits_{j=0}^k S(k,j)i^{\underline{j}}$$

交换求和号，展开下降幂：

$$\sum\limits_{j=0}^k S(k,j)\sum\limits_{i=1}^n\dfrac{f_ii!}{(i-j)!}$$

一次差卷积。第二类斯特林数暴力递推。

总的时间复杂度 $O(n\log n+k^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i) 
#define ll long long
using namespace std;
const int MAXN=(1<<20)+1;
const int MOD=998244353,G=3;
inline ll qpow(ll base,int expo){
	ll res(1);
	while(expo){
		(expo&1)&&(res=res*base%MOD);
		base=base*base%MOD,expo>>=1;
	}
	return res;
}
const int INVG=qpow(G,MOD-2),I=qpow(G,(MOD-1)/4);
int gpow[21],invgpow[21];
inline void calc(){
	F(i,1,20) gpow[i]=qpow(G,(MOD-1)>>i),invgpow[i]=qpow(INVG,(MOD-1)>>i);
	return;
}
inline void meow(int&t){
	t<0&&(t+=MOD);
	t>=MOD&&(t-=MOD);
	return;
}
int rev[MAXN];
inline void NTT(int*poly,int len,bool inv){
	F(i,0,len-1) (i<rev[i])&&(swap(poly[i],poly[rev[i]]),1);
	static ll g[MAXN];
	g[0]=1;
	for(int i(1),expo(1);i<len;i<<=1,++expo){
		ll omega=inv?invgpow[expo]:gpow[expo];
		F(j,1,i-1) g[j]=g[j-1]*omega%MOD;
		for(int j(0);j<len;j+=(i<<1)) F(k,0,i-1){
			int&x(poly[j|k]),&y(poly[i|j|k]);
			ll qwq(g[k]*y%MOD);
			y=x-qwq;
			y<0&&(y+=MOD);
			x+=qwq;
			x>=MOD&&(x-=MOD);
		}
	}
	if(inv){
		ll invl=qpow(len,MOD-2);
		F(i,0,len-1) poly[i]=poly[i]*invl%MOD;
	}
	return;
}
struct poly{
	int num[MAXN]={};
	int len=0;
	
	inline void resize(const int a){
		for(;len>a;--len) num[len]=0;
		len=a;
		if(len<0) len=0;
		return;
	}
	inline poly operator+(const poly a)const{
		poly res;
		res.len=max(a.len,len);
		F(i,0,res.len) res.num[i]=((num[i]+a.num[i])%MOD+MOD)%MOD;
		return res;
	}
	inline poly operator+(const int a)const{
		poly res=*this;
		int&qwq(res.num[0]);
		qwq+=a;
		meow(qwq);
		return res;
	}
	inline poly operator-(const poly a)const{
		return a*(-1)+*this;
	}
	inline poly operator-(const int a)const{
		return *this+(-a);
	}
	inline poly operator*(const poly a)const{
		poly x,y=*this;
		if(a.len*1ll*len<=1e5){
			x.len=a.len+len;
			F(i,0,len) F(j,0,a.len){
				int&qwq(x.num[i+j]);
				qwq+=a.num[j]*1ll*num[i]%MOD;
				qwq>=MOD&&(qwq-=MOD);
			}
			return x;
		}
		x=a;
		int expo=max(__lg(((len+a.len+1)<<1)+1)+1,1),l=1<<expo;
		F(i,0,l-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<(expo-1));
		NTT(x.num,l,0);
		NTT(y.num,l,0);
		F(i,0,l-1) x.num[i]=1ll*x.num[i]*y.num[i]%MOD;
		NTT(x.num,l,1);
		x.resize(len+a.len);
		return x;
	}
	inline poly operator*(const int a)const{
		poly res=*this;
		F(i,0,len){
			int&qwq(res.num[i]);
			qwq=a*1ll*qwq%MOD;
			meow(qwq);
		}
		return res;
	}
	inline poly inv(){
		poly res;
		res.num[0]=qpow(num[0],MOD-2);
		for(int l(2),expo(1);l<(len<<1);l<<=1,++expo){
			int tmp[MAXN]={};
			F(i,0,(l<<1)-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<expo);
			memcpy(tmp,num,sizeof(int)*l);
			NTT(tmp,l<<1,0);
			NTT(res.num,l<<1,0);
			F(i,0,(l<<1)-1){
				int&qwq(res.num[i]),t(2-1ll*qwq*tmp[i]%MOD);
				meow(t);
				qwq=1ll*qwq*t%MOD;
			}
			NTT(res.num,l<<1,1);
			F(i,l,(l<<1)-1) res.num[i]=0;
		}
		res.resize(len);
		return res;
	}
	inline poly diff(){
		poly res;
		res.len=len-1;
		F(i,0,res.len) res.num[i]=1ll*num[i+1]*(i+1)%MOD;
		return res;
	}
	inline poly inte(){
		poly res;
		res.len=len+1,res.num[0]=0;
		F(i,1,res.len) res.num[i]=1ll*num[i-1]*qpow(i,MOD-2)%MOD;
		return res;
	}
	inline poly ln(){
		poly res;
		res=diff()*inv();
		res=res.inte();
		res.resize(len);
		return res;
	}
};
int fact[MAXN],inv[MAXN];
int n,k;
ll mother;
poly f,g,h;
int S[2][MAXN];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	calc();
	cin>>n>>k;
	if(n==2){
		F(i,0,k) cout<<(1+1+qpow(2,i))*qpow(qpow(n,i),MOD-2)%MOD<<"\n";
		return 0;
	}
	fact[0]=1;
	F(i,1,200001) fact[i]=fact[i-1]*1ll*i%MOD;
	inv[200001]=qpow(fact[200001],MOD-2);
	R(i,200001,1) inv[i-1]=inv[i]*1ll*i%MOD;
	h.len=n;
	F(i,0,n) h.num[i]=qpow(2,((i-1ll)*i>>1)%(MOD-1))*inv[i]%MOD;
	g=h.ln();
	f.num[0]=0;
	f.len=n;
	F(i,1,n) f.num[i]=fact[n]*1ll*g.num[i]%MOD*h.num[n-i]%MOD*fact[i]%MOD;
	F(i,0,n) g.num[i]=inv[i];
	reverse(f.num,f.num+n+1);
	f=f*g;
	reverse(f.num,f.num+n+1);
	S[0][0]=1;
	F(i,0,k){
		int child(0),now=i&1;
		F(j,0,i) child=(child+S[now][j]*1ll*f.num[j])%MOD;
		cout<<child*qpow(qpow(n,i),MOD-2)%MOD<<"\n";
		S[now^1][0]=0;
		F(j,1,i+1) S[now^1][j]=(S[now][j-1]+S[now][j]*1ll*j)%MOD;
	}
	return 0;
}
```

---

