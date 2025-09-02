# Serval and Bonus Problem

## 题目描述

越来越接近数学家的 Serval 成为了 Japari 大学数学专业的一名大学生。在微积分课上，老师教他如何计算给定线段的随机子线段的期望长度。然后老师留了一个加分题作为作业，奖励是一套 IOI 的手办。加分题是将这个问题推广到更一般的情形：

给定一条长度为 $l$ 的线段。我们随机选择 $n$ 条线段，每次通过在给定线段上等概率地选择两个点（坐标可以不是整数），这两个点之间的区间构成一条线段。你会得到随机选择的线段数 $n$ 和另一个整数 $k$。这 $2n$ 个端点将原线段分成了 $2n+1$ 个区间。你的任务是计算被 $n$ 条随机线段中至少 $k$ 条覆盖的所有区间的期望总长度。

你需要将答案对 $998244353$ 取模。

## 说明/提示

在第一个样例中，期望总长度为 $\int_0^1 \int_0^1 |x-y| \,\mathrm{d}x\,\mathrm{d}y = \frac{1}{3}$，而 $3^{-1}$ 对 $998244353$ 取模的结果是 $332748118$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
332748118
```

## 样例 #2

### 输入

```
6 2 1
```

### 输出

```
760234711
```

## 样例 #3

### 输入

```
7 5 3
```

### 输出

```
223383352
```

## 样例 #4

### 输入

```
97 31 9984524
```

### 输出

```
267137618
```

# 题解

## 作者：猪脑子 (赞：39)

这题思路很神仙……

我们看看这题咋做。

首先，我们可以将l看作1，然后将答案乘以l，这样答案显然不变。

然后我们有一种积分的想法：

我们考虑对于一个位置x，它被至少k个线段覆盖的概率。那么我们将这个概率求一个积分就是答案（根据期望的定义就可以知道）。

但是我们发现这东西并不好求……

怎么办呢？我们有一个相当神仙的思路：

我们可以再设另外一个随机变量$X(0\leq X\leq 1)$，然后我们发现，$X$被至少k个线段覆盖的概率就等于我们上面要求的积分！（为什么，因为我们把l看作了1啊，然后这个概率其实就等于原来的积分除以1。）

那么现在我们要求的就是$X$被至少k个线段覆盖的概率。

这玩意怎么求？这时，我们会发现一个显然却非常神仙的事实：我们随机出的$(2n+1)$个点本身的位置并不重要，我们只要知道它们的相对位置就行了！！

（你问我如果两个点重合怎么办？这个概率太小，可以认为就是0，我们并不需要管它……）

所以问题就变成了这样：求有多少种点的排列方式，使得点$X$在至少被k个线段覆盖。

~~通过观察数据范围~~我们发现这玩意可以dp。

我们设$dp_{i,j,k}$表示我们选了i个点，有j个左端点还没匹配上，然后k表示点$X$是否被选，那么转移应该是挺显然的：

$$dp_{i,j,k}\to dp_{i+1,j+1,k}$$

$$dp_{i,j,k}\times j\to dp_{i+1,j-1,k}$$

$$dp_{i,j,0}\to dp_{i+1,j,1}(j\geq k)$$

这三个转移我们是分别考虑加一个左端点，加一个右端点，还有加入点$X$的情况讨论的。

那么我们要求的就是$dp_{2n+1,0,1}$。

但是这样还没完。注意到每一个线段的两个端点可以互换，并且n个线段的顺序也可以互换（我们dp时其实将线段强行规定了顺序），并且我们还要除以总的排列数（我们求的是概率），所以最后答案是

$$\frac{dp_{2n+1,0,1}\times 2^n\times n!}{(2n+1)!}$$

然后代码就很好写了：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define Mod 998244353
using namespace std;
long long fpow(long long a,long long b)
{
	long long ans=1,t=a;
	while(b)
	{
		if(b&1)ans=ans*t%Mod;
		t=t*t%Mod;
		b>>=1;
	}
	return ans;
}
long long inv(long long a)
{
	return fpow(a,Mod-2);
}
void add(int& a,int b)
{
	a+=b;
	if(a>=Mod)a-=Mod;
}
int dp[4010][4010][2];
int fac[5010];
int main(){
	int n,k,l;
	scanf("%d %d %d",&n,&k,&l);
	dp[0][0][0]=1;
	for(int i=0;i<=n*2;i++)
		for(int j=0;j<=i;j++)
			for(int o=0;o<=1;o++)
			{
				add(dp[i+1][j+1][o],dp[i][j][o]);
				if(o==0&&j>=k)add(dp[i+1][j][1],dp[i][j][o]);
				if(j)add(dp[i+1][j-1][o],(long long)dp[i][j][o]*j%Mod);
			}
	fac[0]=1;
	for(int i=1;i<=n*2+1;i++)
		fac[i]=(long long)fac[i-1]*i%Mod;
	printf("%lld\n",(long long)dp[n*2+1][0][1]*fpow(2,n)%Mod*fac[n]%Mod*inv(fac[n*2+1])%Mod*l%Mod);
	return 0;
}

```


~~无耻求赞~~

---

## 作者：leukocyte (赞：24)

提供一个 $\mathcal O(n)$ 的做法。

不妨设 $l=1$ 。

考虑每个点被覆盖的概率，显然有：

$$p_x=\sum_{i=k}^n\binom{n}{i}(2x(1-x))^i(1-2x(1-x))^{n-i}$$

然后我们直接积分：

$$Ans=\int_0^1\sum_{i=k}^n\binom{n}{i}(2x(1-x))^i(1-2x(1-x))^{n-i}dx$$
$$=\sum_{i=k}^n\binom{n}{i}\int_0^1(2x(1-x))^i\sum_{j=0}^{n-i}(-1)^j\binom{n-i}{j}(2x(1-x))^{j}dx$$
$$=\sum_{i=k}^n\binom{n}{i}\sum_{j=0}^{n-i}(-1)^j\binom{n-i}{j}2^{i+j}\int_0^1x^{i+j}(1-x)^{i+j}dx$$

接着我们发现后面是一个 $Beta$ 积分，所以可以化成：

$$Ans=\sum_{i=k}^n\binom{n}{i}\sum_{j=0}^{n-i}(-1)^j\binom{n-i}{j}2^{i+j}B(i+j+1,i+j+1) $$

其中 $B(x,y)=\frac{(x-1)!(y-1)!}{(x+y-1)!}$ 。
  
然后注意到 $\binom{n}{i}\binom{n-i}{j}=\binom{n}{i+j}\binom{i+j}{j}$ 。

所以我们可以先枚举 $i+j$ ，那么有：

$$Ans=\sum_{i=k}^n\binom{n}{i}2^iB(i+1,i+1)\sum_{j=0}^{i-k}(-1)^j\binom{i}{j}$$

基本上所有题解到这就直接将式子展开做卷积，但实际上，我们有：

$$\sum_{j=0}^{i-k}(-1)^j\binom{i}{j}$$
$$=\sum_{j=0}^{i-k}(-1)^j\left(\binom{i-1}{j}+\binom{i-1}{j-1}\right)$$
$$=\sum_{j=0}^{i-k}(-1)^j\binom{i-1}{j}-\sum_{j=0}^{i-k-1}(-1)^j\binom{i-1}{j}$$
$$=(-1)^{i-k}\binom{i-1}{i-k}$$

所以：

$$Ans=\sum_{i=k}^n(-1)^{i-k}\binom{i-1}{i-k}\binom{n}{i}2^iB(i+1,i+1)$$

这样我们就能在 $\mathcal O(n)$ 的复杂度内解决问题。



---

## 作者：wucstdio (赞：12)

打VP第$n$次差$5$分钟调出来最后一道题，心态崩了

首先发现$l$是没有用的，因为只需要把最后的答案乘$l$。

考虑答案可以怎么求，我们可以对于每一个位置$x(0\le x\le 1)$，求出来它被覆盖的概率，然后把这个玩意做一个积分就是答案。

对于一个位置$x$，它被覆盖的概率是$2x(1-x)$，所以我们可以枚举它被覆盖了几次：

$$f(x)=\sum_{i=k}^n\binom{n}{i}(2x(1-x))^i(1-2x(1-x))^{n-i}$$

发现中间的两个幂可以预处理，所以时间复杂度是$O(n^3)$的。

如果你像我一样觉得CF机子很快就直接写了$n^3$，那么恭喜你，Time Limit Exceeded on test 5。

发现后面的多项式乘法可以用NTT进行优化。时间复杂度降到$O(n^2\log n)$。

然而因为NTT常数太大而且长度还是$2n$，这个算法并不能过掉第五个点，经过实测$n=2000$还要2s多一点。

怎么办呢？我们发现我们其实并不关心这个多项式的每一项，也就是说我们完全可以中间都用点值来算，直到最后求积分了再NTT回来。

同时我们发现多项式的幂的点值也是可以递推的，时间复杂度降到$O(n^2)$。

差5分钟调出来好自闭啊……

![](https://cdn.luogu.com.cn/upload/pic/61418.png)

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const ll MOD=998244353;
ll quick_pow(ll x,ll a)
{
	ll ans=1;
	while(a)
	{
		if(a&1)ans=ans*x%MOD;
		x=x*x%MOD;
		a>>=1;
	}
	return ans;
}
ll f[5005],pow1[2005][5005],pow2[2005][5005],c[2005][2005];
int n,k,l;
int limit,L,r[10005];
ll omega[2][15][1<<14];
void pre()
{
	for(int mid=1,i=0;i<=14;mid<<=1,i++)
	{
		ll w1=quick_pow(3,(MOD-1)/(mid<<1));
		ll w2=quick_pow(3,MOD-1-(MOD-1)/(mid<<1));
		omega[0][i][0]=omega[1][i][0]=1;
		for(int k=1;k<mid;k++)
		{
			omega[1][i][k]=omega[1][i][k-1]*w1%MOD;
			omega[0][i][k]=omega[0][i][k-1]*w2%MOD;
		}
	}
}
void NTT(ll*A,int type) 
{
	for(int i=0;i<limit;i++)
	  if(i<r[i])swap(A[i],A[r[i]]);
	if(type==-1)type=0;
	for(int mid=1,i=0;mid<limit;mid<<=1,i++)
	{
		for(int R=mid<<1,j=0;j<limit;j+=R)
		{
			for(int k=0;k<mid;k++)
			{
				ll x=A[j+k]%MOD,y=omega[type][i][k]*A[j+mid+k]%MOD;
				A[j+k]=x+y;
				A[j+mid+k]=x-y;
			}
		}
	}
	for(int i=0;i<limit;i++)
	{
		A[i]%=MOD;
		if(A[i]<0)A[i]+=MOD;
	}
	if(type==0)
	{
		ll inv=quick_pow(limit,MOD-2);
		for(int i=0;i<limit;i++)A[i]=A[i]*inv%MOD;
	}
}
ll tmp1[10005],tmp2[10005];
int main()
{
	pre();
	scanf("%d%d%d",&n,&k,&l);
	limit=1,L=0;
	while(limit<=(2*n))limit<<=1,L++;
	for(int i=0;i<limit;i++)
	  r[i]=(r[i>>1]>>1)|((i&1)<<(L-1));
	c[0][0]=1;
	for(int i=0;i<=n;i++)
	for(int j=0;j<=n;j++)
	{
		if(c[i][j]>=MOD)c[i][j]-=MOD;
		c[i+1][j+1]+=c[i][j];
		c[i+1][j]+=c[i][j];
	}
	pow1[0][0]=1;
	pow1[1][1]=2,pow1[1][2]=-2;
	NTT(pow1[0],1);
	NTT(pow1[1],1);
	for(int i=2;i<=n;i++)
	  for(int x=0;x<limit;x++)
		pow1[i][x]=pow1[i-1][x]*pow1[1][x]%MOD;
	pow2[0][0]=1;
	pow2[1][0]=1,pow2[1][1]=-2,pow2[1][2]=2;
	NTT(pow2[0],1);
	NTT(pow2[1],1);
	for(int i=2;i<=n;i++)
	  for(int x=0;x<limit;x++)
		pow2[i][x]=pow2[i-1][x]*pow2[1][x]%MOD;
	for(int i=k;i<=n;i++)
	{
		for(int j=0;j<limit;j++)
		{
			tmp1[j]=pow1[i][j];
			tmp2[j]=pow2[n-i][j];
		}
		for(int j=0;j<limit;j++)
		  tmp1[j]=tmp1[j]*tmp2[j]%MOD;
		for(int j=0;j<limit;j++)
		  f[j]=(f[j]+tmp1[j]*c[n][i])%MOD;
	}
	NTT(f,-1);
	ll ans=0;
	for(int i=0;i<=2*n;i++)
	  ans+=quick_pow(i+1,MOD-2)*f[i]%MOD;
	ans%=MOD;
	if(ans<0)ans+=MOD;
	printf("%I64d\n",ans*l%MOD);
	return 0;
}
```

---

## 作者：λᴉʍ (赞：9)

#  CF1153F Serval and Bonus Problem


---

其实这个题很呆，但是考场上沙雕了，看见实数，期望什么的样例还积分，不会就溜了

大致题意：

有一段长为$l$的线段，有$n$个区间，左右端点在$[0,l)$间均匀随机（可能不是整数）

求期望被至少$k$段区间覆盖的长度，对998244353取膜

其实这个模型很呆，但像我这么sb的第一次看见（可能是忘了）就不会

因为是范围内的实数，那么可以认为没有重合，那么这条线段会被$2n$个端点分成$2n+1$段，因为端点也是随机的，所以每一段期望长度都相同，都是$\frac{l}{2n+1}$

所以只要对于每一段，计算这一段被至少$k$段区间覆盖的概率

既然算概率当然直接算方案数了，直接dp，设$f[i][j]$表示有$i$个端点，第$i$个端点后面的区间被$j$个线段覆盖的方案数。转移直接枚举$i$是一个区间的开始还是结束，如果是结束还要乘$j$转移，表示这个端点可以匹配前面$j$个的任意一个

最后直接枚举合法的方案就行了，记住这个算的是方案数，还要除以$f[2n][0]$才是概率。

```cpp
#include<bits/stdc++.h>
#define il inline
#define vd void
#define mod 998244353
typedef long long ll;
il ll gi(){
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
	return x*f;
}
il int pow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}
	return ret;
}
int f[4010][2010],p[2010];
int main(){
#ifdef XZZSB
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int n=gi(),k=gi(),l=1ll*gi()*pow(n<<1|1,mod-2)%mod;
	p[0]=1;for(int i=1;i<=n;++i)p[i]=1ll*i*p[i-1]%mod;
	f[0][0]=1;
	for(int i=0;i<n<<1;++i){
		for(int j=std::min(n,i);~j;--j){
			f[i+1][j+1]=(f[i+1][j+1]+f[i][j])%mod;
			if(j)f[i+1][j-1]=(f[i+1][j-1]+1ll*f[i][j]*j)%mod;
		}
	}
	int ans=0;
	for(int i=1;i<=n<<1;++i)
		for(int j=k;j<=n;++j)
			ans=(ans+1ll*f[i][j]*f[(n<<1)-i][j]%mod*p[j])%mod;
	printf("%lld\n",1ll*ans*l%mod*pow(f[n<<1][0],mod-2)%mod);
	return 0;
}
```


---

## 作者：xzCyanBrad (赞：8)

## CF1153F

牛逼坏了——这题好唬人，题面是实数均匀取值，样例解释上积分，根本不可做。

为了下面讨论方便先简化题目。第一眼发现 $l$ 没有用，可以通过放缩坐标轴改成 $1$（最后输出答案时 $\times l$）。

下面的三个做法，都建立在数轴上随机两点，它们重合概率看作 $0$ 这一基础上的；复杂度都是 $\Theta(n^2)$。

#### Sol 1 - 智障做法

我们考虑算出一个点 $x$ 的合法的概率，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/vylbgtru.png)

当 $k=n$ 时因为要覆盖所有线段，概率为 $p(x)=(2x(1-x))^n$。

当 $k<n$ 时我们发现有可能这个点被 $k+1$ 条线段覆盖到了，也是合法的。所以我们考虑枚举，钦定 $i$ 条线段覆盖了 $x$，概率为：
$$
f(x)=\sum_{i=k}^n\binom nip(x)^i(1-p(x))^{n-i}
$$
这样我们就知道了一个 $x$ 的概率，而所有 $x\in[0,1]$ 呢？显然直接积分即可。我们设 $q(x)=1-p(x)$，答案为：
$$
\int_0^1f(x)\text{\,d}x=\sum_{i=k}^n\binom ni\int_0^1p(x)^iq(x)^{n-i}\text{\,d}x\\
$$
这个式子通过多项式快速幂已经可以做到 $\Theta(n^2\log n)$ 了，但是有题目中的 $2\times 2$ 倍常数和多项式的巨大常数。于是实测它要跑 2.5s，刚好错过时限。

发现 $p(x),q(x)$ 都是二次多项式，发现每次暴力乘、除它的代价为常数，所以考虑设 $g_i(x)=p(x)^iq(x)^{n-i}$。我们发现 $g_i(x)=\frac{g_{i-1}(x)p(x)}{g_i(x)}$ 只需要一次乘法一次除法，做到了线性！那么我们可以将式子补充完整了：
$$
\int_0^1f(x)\text{\,d}x=\sum_{i=k}^n\binom nig_i(x)\Big|_0^1
$$
多项式积分是容易的，所以这题就解决了。**注意我们不能用 NTT 进行乘法，否则复杂度会退化；必须直接暴力！**

[Code](https://codeforces.com/contest/1153/submission/291018882)

#### Sol 2 - 正常做法

这个做法可以用来承接 Sol 1&3。

> The $2n$ endpoints of the chosen segments split the segment into $(2n+1)$ intervals.

题目已经把这东西明明白白地给在这里了，还不用？？？

考虑设这 $2n$ 个端点为 $A_1,A_2,\dots,A_{2n}$。那么我们有：

1. （对称性）$\forall 1\le i<2n,|A_iA_{i+1}|=|A_1A_2|=\frac 1{2n+1}$。
2. （区间内全同性）$\forall 1\le i<2n,x\in[A_i,A_{i+1}]$，$x$ 的状态（是否是答案）恒定 $0/1$。

这两个命题的证明都很容易。这样我们就把 Sol 1 的关于 $x$ 连续的积分化成了 $2n-1$ 个离散的东西。

仍旧考虑钦定 $i$ 条线段，我们设现在 $x\in[A_j,A_{j+1}]$，则我们要在左边（$A_1\dots A_j$）和右边（$A_{j+1}\dots A_n$）各选出：

- $i$ 个一类点（左与右相连）。注意配对是有序的，所以贡献是 $j^{\underline i}\binom {n-j+1}i$。

- 两边分别有 $(j-i),(n-j+1-i)$ 个二类点（内部相连）。我们设有 $x$ 个二类点的方案数为 $F(x)$，则：
  $$
  F(2n)=\frac{(2n)^{\underline n}}{2^n}
  $$
  注意特判，若 $n$ 为负数，$0$；若 $x$ 是奇数那么有落单的，$0$。否则就是选出 $n$ 个去右边，而且它们有序，所以是排列数（下降幂）；同时 $1-3,3-1$ 算一种连法，所以要除掉表示方向的 $2^n$。

综合一下，答案即为：
$$
\frac 1{2n+1}\sum_{i=k}^n\sum_{j=1}^{2n}j^{\underline i}\binom {n-j+1}iF(j-i)F(n-j+1-i)
$$
第一个因子是因为 $|A_iA_{i+1}|=\frac{1}{2n+1}$。

代码没写。

#### Sol 3 - 神仙做法

考虑继续这个 $A_1\dots A_{2n}$ 定点的思路。我们设 $B(x)$，也就是 $B$ 点在数轴上表示的数是 $x$。

发现一条重要的性质：$B$ 和 $A_1\dots A_{2n}$ 的值都不重要，即 $x$ 不重要！重要的只有它们的相对关系。

非常对，因为我们区间覆盖是相对的，跟绝对值没关系。所以考虑一个 dp。$f(i,j,k)$ 表示我们要放 $2n+1$ 个点，已经放到了第 $i$ 个，其中 $A$ 有 $j\ge 0$ 个左端点，且 $B$ 放了（$k=1$）或没放（$k=0$），方案数。

有显然的三个转移：
$$
\begin{cases}f(i,j,k)\leftarrow (j+1)f(i-1,j+1,k),&(1)\\f(i,j,k)\leftarrow f(i-1,j-1,k),&(2)\\f(i,j,1)\leftarrow f(i-1,j,0),&(3)\\\end{cases}
$$
其中第 $(1)(2)$ 转移放 $A$，$(1)$ 放右端点，$(2)$ 放左端点；$(3)$ 放 $B$。边界和初值显然。

答案取 $f(2n+1,0,1)$。但是发现我们这些线段同样有顺序、大小关系，所以要 $\times n!2^n$，类似上面；然后再把方案数变成期望（除以总方案数 $(2n+1)!$）即可。

[Code](https://codeforces.com/contest/1153/submission/291059236)

---

## 作者：newbiechd (赞：7)

# CF1153F Serval and Bonus Problem

UPD：在洛谷上有些公式不能正常显示，但在博客园和其他地方都没有问题，~~因为懒得改了~~，还是建议大家点下面的链接到我的博客里查看。

日常[广告](https://www.cnblogs.com/cj-chd/p/10715436.html)

官方的解法是$O(n ^ 2)$的，这里给出一个$O(n \log n)$的做法。

首先对于长度为$l$的线段，显然它的答案就是长度为$1$的线段的答案$\times l$，这样做只是为了方便计算。

考虑对于数轴上区间$[0,1]$内任意一个点$x$，它被一条随机线段覆盖的概率是多少：线段的两个端点都在它左边的概率是$x ^ 2$、都在它右边的概率是$(1 - x) ^ 2$，那么它被覆盖的概率即为$p(x) = 1 - x^2 - (1 - x) ^ 2 = 2 x (1 - x)$。

那么他被$\ge k$条线段覆盖的概率为$f(x) = \sum \limits _{i = k} ^ n \binom{n}{i} p(x) ^ i (1 - p(x)) ^ {n - i}$。

根据定积分的定义就得到区间$[0,1]$内被$\ge k$条线段覆盖的长度期望为$\int _{0} ^{1} f(x) \mathrm{d} x$。

现在我们的问题就是怎么算这个东西了：

$$\begin{align*} \int _ 0 ^ 1 f(x) \mathrm{d} x & = \int _ 0 ^ 1 \sum \limits _{i = k} ^ n \binom {n} {i} (2x (1 - x)) ^ i (1 - 2x (1 - x)) ^ {n - i} \mathrm{d} x \\ & = \sum \limits _{i = k} ^ n \binom {n} {i} \int _ 0 ^ 1 (2x (1 - x)) ^ i \sum \limits _{j = 0} ^ {n - i} \binom {n - i} {j} (-2x(1 - x)) ^ j \mathrm{d} x \\ & = \sum \limits _{i = k} ^n \binom {n} {i} \sum \limits _{j = 0} ^ {n - i} \binom {n - i} {j} (-1) ^ j 2 ^ {(i + j)} \int _ 0 ^ 1 x ^ {i + j} (1 - x) ^ {i + j} \mathrm{d} x \end{align*}$$

推到这里，就可以把积分去掉了，这是一个[Beta Function](https://en.wikipedia.org/wiki/Beta_function)的形式：~~记结论吧~~

$$B(x, y) = \int _ 0 ^ 1 t ^ {x - 1} (1 - t) ^ {y - 1} \mathrm{d} x = \frac {(x - 1) ! (y - 1) !} {(x + y - 1) !}$$

代入得：

$$\begin{align*} \int _ 0 ^ 1 f(x) \mathrm{d} x & = \sum \limits _{i = k} ^n \binom {n} {i} \sum \limits _{j = 0} ^ {n - i} \binom {n - i} {j} (-1) ^ j 2 ^ {(i + j)} \frac {((i + j) ! ) ^ 2} {(2(i + j) + 1) !} \\ & = n ! \sum  \limits _{i = k} ^ n \sum \limits _ {j = 0} ^ {n - i} \frac {1} {i !} \frac {(-1) ^ j} {j !} \frac {2 ^ {i + j} ((i + j) !) ^ 2} {(2(i+ j) + 1) ! (n - (i + j)) !} \end{align*}$$

令$t = i + j$，$f[i] = \frac {1} {i}$，$g[j] = \frac {(-1) ^ j} {j !}$，$h[t] = \frac{2^t (t !) ^ 2} {(2 t + 1) ! (n - t) !}$，考虑枚举$t$：

$$\begin{align*} \int _ 0 ^ 1 f(x) \mathrm{d} x & = n ! \sum \limits _{t = k} ^ n h[t] \sum \limits _ {i = k} ^ t f[i] g[t - i] \end{align*}$$

这后面就是一个非常显然的卷积式子了，直接FFT即可。

答案记得$\times l$。

```cpp
//written by newbiechd
#include <cstdio>
#include <cctype>
#include <algorithm>
#define BUF 1000000
using namespace std;
const int N = 100003, yyb = 998244353, Gg = 3, Gi = 332748118;
char buf[BUF], *p1, *p2;
inline char gc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUF, stdin), p1 == p2) ? EOF : *p1++; }
inline int rd() {
    register int f = 0;
    register char c;
    while (!isdigit(c = gc())) {}
    do
        f = f * 10 + (c ^ 48);
    while (isdigit(c = gc()));
    return f;
}
int rev[N], G[2][N];
inline int power(int x, int y) {
    register int o = 1;
    for (; y; y >>= 1, x = 1ll * x * x % yyb)
        if (y & 1)
            o = 1ll * o * x % yyb;
    return o;
}
inline void ntt(int *f, int len, int opt) {
    register int i, j, k, x, y, p, q;
    for (i = 1; i < len; ++i)
        if (i < rev[i])
            swap(f[i], f[rev[i]]);
    for (i = 1; i < len; i <<= 1) {
        p = G[opt][i];
        for (j = 0; j < len; j += i << 1)
            for (k = 0, q = 1; k < i; ++k, q = 1ll * p * q % yyb)
                x = f[j | k], y = 1ll * q * f[i | j | k] % yyb, f[j | k] = (x + y) % yyb, f[i | j | k] = (x - y) % yyb;
    }
}
int fac[N], invFac[N], f[N], g[N], h[N];
int main() {
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
#endif
    int n = rd(), m = n << 1 | 1, k = rd(), l = rd(), i, len, tmp, ans = 0;
    fac[0] = 1;
    for (i = 1; i <= m; ++i)
        fac[i] = 1ll * fac[i - 1] * i % yyb;
    invFac[m] = power(fac[m], yyb - 2);
    for (i = m; i; --i)
        invFac[i - 1] = 1ll * invFac[i] * i % yyb;
    for (i = k; i <= n; ++i)
        f[i] = invFac[i];
    for (i = 0; i <= n; ++i)
        g[i] = i & 1 ? yyb - invFac[i] : invFac[i];
    for (len = 1; len <= m; len <<= 1) {}
    for (i = 1; i < len; ++i)
        rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? len >> 1 : 0);
    for (i = 1; i < len; i <<= 1)
        G[0][i] = power(Gg, (yyb - 1) / (i << 1)), G[1][i] = power(Gi, (yyb - 1) / (i << 1));
    ntt(f, len, 0), ntt(g, len, 0);
    for (i = 0; i < len; ++i)
        f[i] = 1ll * f[i] * g[i] % yyb;
    ntt(f, len, 1), tmp = power(len, yyb - 2);
    for (i = 1; i <= n; ++i)
        f[i] = 1ll * f[i] * tmp % yyb;
    for (i = 1, tmp = 2; i <= n; tmp = (tmp << 1) % yyb, ++i)
        h[i] = 1ll * fac[i] * fac[i] % yyb * tmp % yyb * invFac[i << 1 | 1] % yyb * invFac[n - i] % yyb;
    for (i = k; i <= n; ++i)
        ans = (1ll * f[i] * h[i] % yyb + ans) % yyb;
    ans = 1ll * ans * fac[n] % yyb * l % yyb, printf("%d\n", (ans + yyb) % yyb);
    return 0;
}

```

目前CF速度rk1。

---

## 作者：_ztyqwq (赞：5)

提供一种不需要积分的做法（也不需要 `dp`）。

首先发现 $ l $ 是没有用的，只要最后乘上即可，因此考虑 $ [0, 1] $ 的线段内取区间。

一共有 $ n $ 个区间，故所有左右端点一共有 $ 2n $ 个（因为随机，端点重合的情况可以视为不可能事件），令这些端点从左到右排序后分别为 $ P_1, ..., P_{2n} $。令整个线段的左端点（即 $ 0 $）为 $ P_0 $，整个线段的右端点（即 $ 1 $）为 $ P_{2n + 1} $。

因为所有区间都是随机选取的，所有端点也是随机的，所以可以考虑**先随机端点序列** $ P_1, ..., P_{2n} $，然后对于**所有端点两两连接的方式**（构造 $ n $ 个区间），计算答案的总长，除以总方式数即得期望长度。

这样我们把 $ [0, 1] $ 分成了 $ P_0P_1, P_1P_2, ..., P_{2n}P_{2n + 1} $ 共 $ 2n + 1 $ 段。容易发现**每一段的点是等价的**，因此计算时只要将每一段作为整体分析即可。

又因为 $ P_0P_1 $ 与 $ P_{2n}P_{2n + 1} $ 内的点不可能被任何一个区间覆盖到（最边缘），故不予考虑。

考虑**恰好被 $ k $ 个区间覆盖**的总长，枚举可能产生贡献的线段：

$$ Sum_k = \sum_{i=k}^{2n - k}[2 | (i - k)]C_i^k (2n - i)^{\underline k}(i - k - 1)!!(2n - i - k - 1)!!P_iP_{i + 1} $$

看不懂？~~这么大个柿子丢在这儿谁搞得明白啊喂~~
 
 - $ \sum_{i = k}^{2n - k} $： 因为线段要被 $ k $ 个区间覆盖到，因此线段的左侧至少有 $ k $ 个端点（不计 $ P_0 $），线段的左端点最左在 $ P_k $；同理可得线段的右端点最右在 $ P_{2n - k + 1} $，即左端点最右在 $ P_{2n - k} $。因此对于所有的 $ k \leqslant i \leqslant 2n - k $ 分析线段 $ P_iP_{i + 1} $。

 - $ [2 | (i - k)] $： 因为恰好被 $ k $ 个区间覆盖，即有 $ k $ 个区间横跨过 $ P_iP_{i + 1} $，则左侧共 $ i $ 个端点除去 $ k $ 个后，还有 $ i - k $ 个必须在左侧连接成区间，因此 $ i - k $ 为偶数。（右侧的剩余端点数为 $ 2n - i - k $，容易发现与 $ i - k $ 同奇偶）
 
 - $ C_i^k $： 从左侧的 $ i $ 个端点中选出 $ k $ 个，作为横跨 $ P_iP_{i + 1} $ 的 $ k $ 个区间的左端点。
 
 - $ (2n - i)^{\underline k} $： 从右侧的 $ 2n - i - k $ 个端点中选出 $ k $ 个，作为横跨 $ P_iP_{i + 1} $ 的 $ k $ 个区间的右端点。注意这里的选取是**有顺序**的。（可以理解为按左端点从左往右依次选取右端点，第一个 $ 2n - i $ 种，第二个 $ 2n - i - 1 $ 种...）
 
 - $ (i - k - 1)!! $： 左侧剩余的 $ i - k $ 个点连接成的区间。考虑第一个点有 $ i - k - 1 $ 种连接方式，第二个点有 $ i - k - 3 $ 种...
 （$ (2x - 1)!! = (2x - 1)(2x - 3)... \times 3 \times 1 $）
 
 - $ (2n - i - k - 1)!! $： 右侧剩余的 $ 2n - i - k $ 个点连接成的区间，原理同上。
 
 - $ P_iP_{i + 1} $： 线段的长度。

~~柿子可能在边界情况有些 bug，比如需要 $ (-1)!! = 1 $~~

开始推柿子 QAQ（其实应该已经可以做了 但是写得简洁一些不好嘛 qwq

首先看这个偶数的限制就觉得~~后患无穷~~，考虑改为枚举 $ j = \dfrac{i - k}{2} \in \mathbb{N}^+ $，此时 $ i = k + 2j $。

$ Sum_k = \sum\limits_{i=k}^{2n - k}[2 | (i - k)]C_i^k (2n - i)^{\underline k}(i - k - 1)!!(2n - i - k - 1)!!P_iP_{i + 1} $（抄了一遍）

$$ = \sum_{j = 0}^{n - k}C_{k + 2j}^k(2n - 2j - k)^{\underline k}(2j - 1)!!(2n - 2j - 2k - 1)!!P_{i}P_{i + 1} $$

（$ i $ 用 $ j $ 代进去，$ P_iP_{i + 1} $ 就免了~~懒~~）

然后把 $ !! $ 消灭，因为

$$ (2x - 1)!! = \dfrac{2x \times (2x - 1) \times ... \times 2 \times 1}{2x \times (2x - 2) \times ... \times 4 \times 2} $$

$$ = \dfrac{2x \times (2x - 1) \times ... \times 2 \times 1}{2x \times 2(x - 1) \times ... \times 2 \cdot 2 \times 2 \cdot 1} $$

$$ = \dfrac{(2x)!}{2^x \cdot x!} $$

因此

$$ Sum_k = \sum_{j = 0}^{n - k}C_{k + 2j}^k(2n - 2j - k)^{\underline k} \cdot \dfrac{(2j)!}{j! \cdot 2^j} \cdot \dfrac{(2n - 2j - 2k)!}{(n - j - k)! \cdot 2^{n - j - k}} \cdot P_{i}P_{i + 1} $$

又因为 $ x^{\underline k} = \dfrac{x!}{(x - k)!} $

$$ Sum_k = \sum_{j = 0}^{n - k}C_{k + 2j}^k \cdot \dfrac{(2n - 2j - k)!}{(2n - 2j - 2k)!} \cdot \dfrac{(2j)!}{j! \cdot 2^j} \cdot \dfrac{(2n - 2j - 2k)!}{(n - j - k)! \cdot 2^{n - j - k}} \cdot P_{i}P_{i + 1} $$

拆组合数

$$ Sum_k = \sum_{j = 0}^{n - k} \dfrac{(k + 2j)!}{k! \cdot (2j)!} \cdot \dfrac{(2n - 2j - k)!}{(2n - 2j - 2k)!} \cdot \dfrac{(2j)!}{j! \cdot 2^j} \cdot \dfrac{(2n - 2j - 2k)!}{(n - j - k)! \cdot 2^{n - j - k}} \cdot P_{i}P_{i + 1} $$

~~淦哦这怎么这么长~~

整理下

$$ Sum_k = \dfrac{1}{k!2^{n - k}} \sum_{j = 0}^{n - k} \dfrac{(k + 2j)!(2n - k - 2j)!}{j!(n - j - k)!} P_{i}P_{i + 1} $$

此时你发现 $ P_iP_{i + 1} $ 成为了眼中钉。

但 $ P_1, ..., P_{2n} $ 都是**独立随机选取**的，因此应该有 $ E(P_0P_1) = E(P_1P_2) = ... = E(P_{2n - 1}P_{2n}) = E(P_{2n}P_{2n + 1}) $，即分割出 $ 2n + 1 $ 条线段的期望长度应该都相等，都等于 $ \dfrac{1}{2n + 1} $~~（我比较菜不会证 但感性理解）~~

因此

$$ E(Sum_k) = \dfrac{1}{k!2^{n - k}(2n + 1)} \sum_{j = 0}^{n - k} \dfrac{(k + 2j)!(2n - k - 2j)!}{j!(n - j - k)!}  $$

最后的答案就是 $ \sum\limits_{i = k}^n E(Sum_i) $。

然后你发现这个柿子不太可卷，只能 $ O(n^2) $ 地做。

然后你看向了数据范围，那没事了。

预处理阶乘和 $ 2 $ 的幂即可。（~~其实推出第一个柿子后就可以动态更新组合数与双阶乘的值做了，为什么要再推出这么多精神污染的柿子呢，可能是本来想卷结果太菜没卷出来罢 /kk~~）

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
const int mod = 998244353;
inline int fastpow(int a, int n)
{
	int ans = 1;
	while(n)
	{
		if(n & 1)
			ans = ans * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return ans;
}
inline int inv(int x)
{
	return fastpow(x, mod - 2);
}
int fac[4001], p2[2001], ifac[4001], ip2[2001];
inline void Init(int n)
{
	fac[0] = p2[0] = ifac[0] = ip2[0] = 1;
	for(int i = 1; i <= 2 * n; i++)
	{
		fac[i] = fac[i - 1] * i % mod;
		ifac[i] = inv(fac[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		p2[i] = p2[i - 1] * 2 % mod;
		ip2[i] = inv(p2[i]);
	}
}
signed main()
{
	int n, K, l;
	scanf("%lld %lld %lld", &n, &K, &l);
	Init(n);
	int ans = 0;
	for(int k = K; k <= n; k++)
	{
		int tot = 0;
		for(int i = 0; i <= n - k; i++)
			tot = (tot + fac[k + 2 * i] * fac[2 * n - k - 2 * i] % mod * ifac[n - i - k] % mod * ifac[i]) % mod;
		ans = (ans + tot * ifac[k] % mod * ip2[n - k]) % mod;
	}
	ans = ans * ifac[2 * n] % mod * fac[n] % mod * p2[n] % mod;
	printf("%lld\n", ans * inv(2 * n + 1) % mod * l % mod);
	return 0;
}
```

---

## 作者：hsfzLZH1 (赞：3)

## 题目大意

给定一个长度为 $l$ 的线段，你在这条线段上分别随机选择两个点，连成一条线段，按照这样的方法生成 $n$ 条线段，求被至少 $k$ 条线段覆盖的长度的期望。答案取模 $998244353$ 。

$1\le k\le n\le 2000,1\le l\le 10^9$

## 解题思路

不失一般性，不妨讨论 $l=1$ 时的情况。

由于我们每次是在线段上选择一个点，我们可以认为两个点重合的概率为 $0$ 。

现在，有 $2\times n$ 个线段的端点，我们再随机选择一个点 $P$ ，由于这 $2\times n+1$ 个点的选择都是随机且独立的，所以我们只需要知道 $P$ 出现在合法位置的概率，也就是 $P$ 在所有可能的方案中出现在合法位置的方案数。

我们可以用时间复杂度为 $O(n^2)$ 的 DP 解决这个问题。

定义 $f[i][j][x]$ 为已经处理完了前 $i$ 个点，其中有 $j$ 个结点还没有配对的点（意思就是在接下来选择的这个点左侧的点上会被 $j$ 条线段覆盖）， $x$ 表示是否已经确定了点 $P$ 的位置。

有以下三种转移方式：

1.将当前位置设为点 $P$ 的位置。

若 $j\ge k$ ， $f[i][j][1]+=f[i-1][j][0]$ 。

2.新添加一个没有被配对的点。

若 $i+j-x\le 2\times n$ （该限制条件使最后所有点都被配对后满足条件）， $f[i][j][x]+=f[i-1][j-1][x]$ 。

3.和之前一个没有被配对的点配对。

$f[i][j][x]+=f[i-1][j+1][x]\times (j+1)$ 。

初始条件为 $f[0][0][0]=1$ 。

$f[2\times n+1][0][1]$ 为最终获得满足条件的点 $P$ 的方案数。

所有点随意排列的方案数为 $(2\times n+1)!$ 。但由于我们在 DP 时没有考虑相同位置线段为不同编号的结点的情况，所以方案数要除以 $n!$ 。由于一条线段的两端点可以任意交换，所以方案数还要除以 $2^n$ 。

所以，最后的答案为 $\frac {f(2\times n+1,0,1)\times n! \times 2^n} {(2\times n+1)!}$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2010;
typedef long long ll;
const ll mod=998244353;
ll ksm(ll a,ll k)
{
	ll ret=1ll,x=a;
	while(k)
	{
		if(k&1)ret=ret*x%mod;
		k>>=1;x=x*x%mod;
	} 
	return ret;
}
ll n,k,l,f[maxn*2][maxn][2],ans1,ans2; 
int main()
{
	scanf("%lld%lld%lld",&n,&k,&l);
	f[0][0][0]=1;
	for(int i=1;i<=2*n+1;i++)for(int j=0;j<=n;j++)
	{
		if(j>=k)f[i][j][1]+=f[i-1][j][0],f[i][j][1]%=mod;
		for(int x=0;x<=1;x++)
		{
			if(i+j+1-x<=2*n+1&&j-1>=0)f[i][j][x]+=f[i-1][j-1][x],f[i][j][x]%=mod;
			f[i][j][x]+=(j+1)*f[i-1][j+1][x]%mod,f[i][j][x]%=mod;
		}
	}
	//for(int i=1;i<=2*n+1;i++)for(int j=0;j<=n;j++)
	//printf("%d %d %lld %lld\n",i,j,f[i][j][0],f[i][j][1]);
	ans1=f[2*n+1][0][1];ans2=1;
	for(int i=1;i<=n;i++)ans1=ans1*i%mod,ans1=ans1*2%mod;
	for(int i=1;i<=2*n+1;i++)ans2=ans2*i%mod;
	printf("%lld\n",ans1*ksm(ans2,mod-2)%mod*l%mod);
	return 0;
}
```

---

## 作者：LKY928261 (赞：1)

考虑先计算线段长度为 $1$ 的情况，最后乘上 $l$ 即为答案。

满足条件部分的长度难以直接计算，于是对线段上的点单独计算其在合法部分的概率。设函数 $f(x)$ 表示到线段左端点距离为 $x(x\in[0,1])$ 的点合法的概率，则答案为该函数在区间 $[0,1]$ 上的定积分，即 $\int_0^1 f(x) \mathrm{d}x$。

$n$ 个区间的情况下，$f(x)$ 同样难以直接计算，于是先计算 $1$ 个区间的情况。设位于 $x$ 的点被一个区间包含的概率为 $p_x$，不难得出 $f(x)=\sum_{i=k}^{n}{\binom{n}{i}p_x^i(1-p_x)^{n-i}}$。

计算 $p_x$ 是容易的。记区间为 $[l,r]$，则 $0\le l\le x\le r\le 1$ 的概率即为所求。考虑将区间表示在平面直角坐标系上。具体地，令 $x$ 轴表示 $l$，$y$ 轴表示 $r$，则所有区间对应的点集为下图中的蓝色区域，所有满足条件的区间对应的点集为红色区域。

![](https://pic.imgdb.cn/item/659cd107871b83018a079544.png)

结合图片容易得出 $p_x=2x-2x^2$。

则最终答案为：

$$
\begin{aligned}
&l\times\int_0^1 f(x) \mathrm{d}x\\
=&l\times\int_0^1\sum_{i=k}^{n}{\binom{n}{i}p_x^i(1-p_x)^{n-i}}\mathrm{d}x\\
=&l\times\int_0^1\sum_{i=k}^{n}{\binom{n}{i}(2x-2x^2)^i(1-2x+2x^2)^{n-i}}\mathrm{d}x
\end{aligned}
$$

注意到 $n\le2000$，可以直接暴力计算出后面的多项式，定积分的值即为多项式的不定积分除去常数项之外的所有系数之和，最后乘上 $l$ 即可。

实现时，可以求和的同时维护 $(2x-2x^2)^i(1-2x+2x^2)^{n-i}$，每次 $\times(2x-2x^2)\div(1-2x+2x^2)$，由于这两个多项式项数都很少，直接采用朴素的多项式乘除法即可做到 $O(n)$ 计算，用 NTT 反而会多个 $\log$。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vec;
const ll _=4005,M=998244353;
ll fac[_],inv[_],Iv[_];
inline ll qp(ll x,ll y){ll z=1;for(;y;y>>=1,x=x*x%M)if(y&1)z=z*x%M;return z;}
inline ll iv(ll x){return x<_?Iv[x]:qp(x,M-2);}
inline ll binom(ll x,ll y){return (y<0||x-y<0)?0:fac[x]*inv[y]%M*inv[x-y]%M;}
ll R[_],w[_];
vec operator+(vec a,vec b){
	ll n=max(a.size(),b.size()),i;
	a.resize(n,0);b.resize(n,0);
	for(i=0;i<n;i++)a[i]=(a[i]+b[i])%M;
	return a;
}
vec operator*(vec a,ll k){for(auto &it:a)it=it*k%M;return a;}
vec operator*(vec a,vec b){
	ll t=a.size()+b.size()-1,i,j;vec c(t);
	for(j=b.size();j--;)for(i=a.size();i--;)c[i+j]+=a[i]*b[j];
	for(auto &it:c)it%=M;return c;
}
vec operator/(vec a,vec b){
	if(a.size()<b.size())return {0};
	ll t=a.size()-b.size()+1,x,i,j;vec c(t);
	for(i=t;i--;){
		j=b.size();c[i]=x=a[i+j-1]*iv(b[j-1])%M;
		while(j--)(a[i+j]+=M-x*b[j]%M)%=M;
	}
	return c;
}
vec Int(vec a){
	a.emplace_back(0);
	for(ll i=a.size()-1;i;i--)a[i]=a[i-1]*Iv[i]%M;
	a[0]=0;return a;
}
ll n,k,l,s,i;vec A={0,2,M-2},B={1,M-2,2},C={1},S={0};
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(fac[0]=i=1;i<_;i++)fac[i]=fac[i-1]*i%M;
	for(i=_-1,inv[i]=qp(fac[i],M-2);i;i--)inv[i-1]=inv[i]*i%M;
	for(i=1;i<_;i++)Iv[i]=fac[i-1]*inv[i]%M;
	cin>>n>>k>>l;
	for(i=0;i<k;i++)C=C*A;
	for(i=0;i<n-k;i++)C=C*B;
	for(i=k;i<=n;i++)S=S+C*binom(n,i),C=C*A/B;
	S=Int(S);
	for(auto it:S)s+=it;
	cout<<s%M*l%M<<'\n';
}
```

---

## 作者：Leasier (赞：1)

来点无脑做法。

首先答案为在 $[0, 1)$ 中选点的情况乘上 $l$，于是我们只需要计算 $l = 1$ 的答案。

考虑枚举 $k \leq i \leq n$，对每个 $x \in [0, 1)$ 求解答案：

- $C_n^i$ 表示从 $n$ 条线段里选 $i$ 条。
- $(2x(1 - x))^i$ 表示钦定那 $i$ 条包含 $x$。
- $(2(\frac{1}{2} - x(1 - x)))^{n - i}$ 表示钦定另外 $n - i$ 条不包含 $x$。

于是答案为 $2^n \displaystyle\sum_{i = k}^n C_n^i \int_0^1 (x(1 - x))^i (\frac{1}{2} - x(1 - x))^{n - i} dx$。

不妨设 $f(x) = 1 - x, g(x) = \frac{1}{2} - f(x)$。

考虑枚举 $i = 1 \to n$，初始令 $h(x) \leftarrow g(x)^n$，每次令 $h(x) \leftarrow \dfrac{h(x)f(x)}{g(x)}$ 即可求得当前 $i$ 对应的 $h(x)$，对其积分即可。

时间复杂度为 $O(n^2)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

typedef struct {
	int n;
	ll a[4007];
} Polynomial;

const int mod = 998244353, inv2 = 499122177;
int c[2007][2007];
ll inv[4007];
Polynomial f[2007], g[2007];

Polynomial operator *(Polynomial &a, Polynomial &b){
	Polynomial ans;
	ans.n = a.n + b.n;
	for (register int i = 0; i <= ans.n; i++){
		ans.a[i] = 0;
	}
	for (register int i = 0; i <= a.n; i++){
		for (register int j = 0; j <= b.n; j++){
			int t = i + j;
			ans.a[t] = (ans.a[t] + a.a[i] * b.a[j] % mod) % mod;
		}
	}
	return ans;
}

void operator *=(Polynomial &a, Polynomial &b){
	a = a * b;
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

Polynomial operator /(Polynomial a, Polynomial &b){
	ll inv = quick_pow(b.a[b.n], mod - 2, mod);
	Polynomial ans;
	ans.n = a.n - b.n;
	for (register int i = ans.n; i >= 0; i--){
		ans.a[i] = a.a[i + b.n] * inv % mod;
		for (register int j = 0; j <= b.n; j++){
			int t = i + j;
			a.a[t] = ((a.a[t] - ans.a[i] * b.a[j] % mod) % mod + mod) % mod;
		}
	}
	return ans;
}

void operator /=(Polynomial &a, Polynomial &b){
	a = a / b;
}

inline void init(int n, int m){
	c[0][0] = 1;
	for (register int i = 1; i <= n; i++){
		c[i][0] = 1;
		for (register int j = 1; j <= i; j++){
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
	inv[0] = inv[1] = 1;
	for (register int i = 2; i <= m; i++){
		inv[i] = mod - (mod / i) * inv[mod % i] % mod;
	}
}

int main(){
	int n, k, l;
	ll ans = 0;
	Polynomial f, g, h;
	scanf("%d %d %d", &n, &k, &l);
	init(n, n * 2 + 1);
	f.n = 2;
	f.a[0] = 0;
	f.a[1] = 1;
	f.a[2] = mod - 1;
	g.n = 2;
	g.a[0] = inv2;
	g.a[1] = mod - 1;
	g.a[2] = 1;
	h.n = 0;
	h.a[0] = 1;
	for (register int i = 1; i <= n; i++){
		h *= g;
	}
	for (register int i = 1; i <= n; i++){
		h *= f;
		h /= g;
		if (i >= k){
			ll sum = 0;
			for (register int j = 0; j <= h.n; j++){
				sum = (sum + h.a[j] % mod * inv[j + 1] % mod) % mod;
			}
			ans = (ans + sum * c[n][i] % mod) % mod;
		}
	}
	ans = ans * l % mod;
	for (register int i = 1; i <= n; i++){
		ans = ans * 2 % mod;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：pengyule (赞：1)

因为一个智障问题调了 40min。

首先根据 Arcs on a Circle 那道 AGC 题的套路，实数期望类问题都可以转化为一条线段的若干等分点的选择方案问题。对于此题而言，线段的 $2n$ 个端点重合的概率是 $0$，根端点 $0,l$ 重合的概率也是 $0$，因此将 $[0,l)$ 等分成 $2n+1$ 段，中间的 $2n$ 个点每个点恰好分给一条线段作为端点，求每个位置被覆盖 $\ge k$ 次的概率 $\times \dfrac{l}{2n+1}$ 之和。

第 $i(1\le i<2n)$ 个点后的线段被覆盖 $\ge k$ 次的方案数用如下方法计算，加起来最后除以总数 $n!(2n)!!$ 即可。

$$
\sum_{j=k}^{\min(i,2n-i)}{n\choose j}{i\choose j}{2n-i\choose j}(j!)^{\color{red}{2}}(i-j)!!(2n-i)!!
$$

注意标红的平方，我一开始下意识乘了一个 $j!$ 大概还有一个配对的 $j!$ 却漏了！

这样就比 dp 还无脑了！

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=4005,mod=998244353;
int n,K,L,ans,jc[N],ijc[N],jjc[N];
inline int qp(int a,int b){
	int c=1;for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)c=1ll*c*a%mod;
	return c;
}
inline int C(int n,int m){if(n<0||m<0||n<m)return 0;return 1ll*jc[n]*ijc[m]%mod*ijc[n-m]%mod;}
inline void add(int &x,int y){(x+=y)>=mod&&(x-=mod);}
int main(){
	cin>>n>>K>>L;
	jjc[0]=1;
	for(int i=2;i<=2*n;i+=2)jjc[i]=1ll*jjc[i-2]*(i-1)%mod;
	ijc[0]=jc[0]=1;for(int i=1;i<=2*n;i++)jc[i]=1ll*i*jc[i-1]%mod;
	ijc[2*n]=qp(jc[2*n],mod-2);for(int i=2*n-1;i;i--)ijc[i]=(i+1ll)*ijc[i+1]%mod;
	for(int i=1;i<2*n;i++){
		for(int j=K;j<=min(min(i,2*n-i),n);j++){
			add(ans,1ll*C(i,j)%mod*C(2*n-i,j)%mod*jjc[i-j]%mod*jjc[2*n-i-j]%mod*jc[j]%mod);
		}
	}
	cout<<ans*(1ll*L*qp(2*n+1,mod-2)%mod)%mod*qp(jjc[2*n],mod-2)%mod<<'\n';
}
```

---

## 作者：intel_core (赞：0)

首先，把长度为 $l$ 直接看成长度为 $1$，最后乘回来即可。

很显然，期望就是对于线段上的所有点 $x$，求出至少被 $k$ 条线段覆盖的概率然后积分。

注意到题目中所说的 $2n+1$ 条线段的长度都是一样的，所以我们只需要考虑这分出来的 $2n+1$ 条线段的长度全都是 $\frac{1}{2n+1}$ 即可。

我们令 $f_{i,j}$ 表示第 $i$ 个点后的线段被 $j$ 个区间覆盖的方案数。转移只有两种，分别将 $i+1$ 视为区间的左或右端点。

最后记得除一个卡特兰数（总方案），再把线段长度 $l$ 算进去，复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=998244353;
const int NR=2e3+10;
int n,k,l,f[NR<<1][NR<<1][2],fac[NR<<1];
void add(int &x,int y){x=(x+y)%MOD;}

int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=res*x%MOD;
		x=x*x%MOD;y>>=1;
	}
	return res;
}
int Inv(int x){return qpow(x,MOD-2);}

signed main(){
	cin>>n>>k>>l;
	fac[0]=1;
	for(int i=1;i<=2*n+1;i++)fac[i]=fac[i-1]*i%MOD;
	f[0][0][0]=1;
	for(int i=0;i<=n*2;i++)
		for(int j=0;j<=i;j++)
			for(int x=0;x<=1;x++){
				add(f[i+1][j+1][x],f[i][j][x]);
				if(x==0&&j>=k)add(f[i+1][j][1],f[i][j][x]);
				if(j)add(f[i+1][j-1][x],f[i][j][x]*j);
			}
	printf("%lld\n",f[n*2+1][0][1]*qpow(2,n)%MOD*fac[n]%MOD*Inv(fac[n*2+1])%MOD*l%MOD);
	return 0;
}
```

---

