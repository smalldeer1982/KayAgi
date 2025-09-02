# Number Challenge

## 题目描述

Let's denote $ d(n) $ as the number of divisors of a positive integer $ n $ . You are given three integers $ a $ , $ b $ and $ c $ . Your task is to calculate the following sum:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF235E/6b4d9893ce96bd0459ff1289a8bf3491052ac12a.png)Find the sum modulo $ 1073741824 $ $ (2^{30}) $ .

## 说明/提示

For the first example.

- $ d(1·1·1)=d(1)=1 $ ;
- $ d(1·1·2)=d(2)=2 $ ;
- $ d(1·2·1)=d(2)=2 $ ;
- $ d(1·2·2)=d(4)=3 $ ;
- $ d(2·1·1)=d(2)=2 $ ;
- $ d(2·1·2)=d(4)=3 $ ;
- $ d(2·2·1)=d(4)=3 $ ;
- $ d(2·2·2)=d(8)=4 $ .

So the result is $ 1+2+2+3+2+3+3+4=20 $ .

## 样例 #1

### 输入

```
2 2 2
```

### 输出

```
20
```

## 样例 #2

### 输入

```
4 4 4
```

### 输出

```
328
```

## 样例 #3

### 输入

```
10 10 10
```

### 输出

```
11536
```

# 题解

## 作者：2018ljw (赞：6)

莫反推柿子的极致体验。

首先要知道一个基本公式：

$$
d(xy)=\sum_{i\mid x}\sum_{j\mid y}[\gcd(i,j)=1]
$$

证明部分参考[约数个数和](https://www.luogu.com.cn/problem/solution/P3327)的第一篇题解，有个人理解。

> 假设 $xy$ 有因子 $k$，$p^c$ 为其一个因子，$x$ 中有因子 $p^a$，$y$ 中有因子 $p^b$。特别的，我们认为在 $y$ 中选出 $p^e$ 视为选出 $p^{a+e}$。
> 1. 若 $c\le a$，在 $x$ 中选出 $p^a$。
> 2. 若 $c>a$，在 $y$ 中选出 $p^{c-a}$。
>
> 关注到这样选完后，对于因子 $k$ 的某个质因子 $p$ 不会同时被 $x,y$ 选且对每种 $c$ 的情况均有唯一对应的选法。

那么要这个有什么用呢？考虑扩展一下。

$$
d(xyz)=\sum_{i\mid x}\sum_{j\mid y}\sum_{k\mid z}[\gcd(i,j)=1][\gcd(j,k)=1][\gcd(k,i)=1]
$$

相似的方法证明：

假设 $xyz$ 有因子 $k$，$p^d$ 为其一个因子，$x$ 中有因子 $p^a$，$y$ 中有因子 $p^b$，$z$ 中有因子 $p^c$。认为在 $y$ 中选 $p^{e}$ 视为选出 $p^{a+e}$，$z$ 中视为选出 $p^{a+b+e}$。
1. 若 $c\le a$，在 $x$ 中选出 $p^a$。
2. 若 $a<c\le a+b$，在 $y$ 中选出 $p^{c-a}$。
3. 若 $c>a+b$，在 $z$ 中选出 $p^{c-a-b}$。

相似的，对于每种 $d$ 我们给其唯一对应了一种选法，故选出的数也会两两互质且不重不漏。

那么，就可以愉悦的推式子了。

$$
ans=\sum_{i=1}^a\sum_{j=1}^b\sum_{k=1}^c\sum_{x\mid i}\sum_{y\mid j}\sum_{z\mid k}[\gcd(x,y)=1][\gcd(y,z)=1][\gcd(z,x)=1]\\
=\sum_{x=1}^a\sum_{y=1}^b\sum_{z=1}^c[\gcd(x,y)=1][\gcd(y,z)=1][\gcd(z,x)=1]\lfloor\frac{a}{x}\rfloor\lfloor\frac{b}{y}\rfloor\lfloor\frac{c}{z}\rfloor\\
=\sum_{x=1}^a\lfloor\frac{a}{x}\rfloor\sum_{y=1}^b\sum_{z=1}^c[\gcd(x,y)=1][\gcd(y,z)=1][\gcd(z,x)=1]\lfloor\frac{b}{y}\rfloor\lfloor\frac{c}{z}\rfloor
$$

$a,b,c$ 都很小，考虑直接枚举 $x$。那么剩下的项中唯一有两个变量的是 $[\gcd(y,z)=1]$，考虑对其莫反。

$$
\sum_{y=1}^b\lfloor\frac{b}{y}\rfloor[\gcd(x,y)=1]\sum_{z=1}^c[\gcd(x,z)=1]\lfloor\frac{c}{z}\rfloor\sum_{d\mid y,d\mid z}\mu(d)\\
=\sum_{d=1}^{\min(b,c)}\mu(d)\sum_{y=1}^{\lfloor\frac{b}{d}\rfloor}\lfloor\frac{\lfloor\frac{b}{d}\rfloor}{y}\rfloor[\gcd(x,dy)=1]\sum_{z=1}^{\lfloor\frac{c}{d}\rfloor}\lfloor\frac{\lfloor\frac{c}{d}\rfloor}{z}\rfloor[\gcd(x,dz)=1]
$$

需要注意这里两个下取整均利用性质将其变形成了式子中的形式。

根据 $[\gcd(x,pq)=1]\iff [\gcd(x,p)=1][\gcd(x,q)=1]$，再次展开:

$$
\sum_{d=1}[\gcd(x,d)=1]\mu(d)\sum_{y=1}^{\lfloor\frac{b}{d}\rfloor}[\gcd(x,y)=1]\lfloor\frac{\lfloor\frac{b}{d}\rfloor}{y}\rfloor\sum_{z=1}^{\lfloor\frac{c}{d}\rfloor}[\gcd(x,z)=1]\lfloor\frac{\lfloor\frac{c}{d}\rfloor}{z}\rfloor
$$

$d$ 依旧不好处理，但我们目前仅枚举了 $x$，所以可以再枚举 $d$ 处理掉前两项。关注到此时后两个 $\sum$ 均为单自变量，除此之外的变量只有 $x$ 和 $\lfloor\frac{b}{d}\rfloor$，所以可以分别求解。由于状态数最多 $2000^2$，考虑直接表示出来。

设 $g(x,y)=\sum\limits_{i=1}^y[\gcd(x,i)=1]\lfloor\frac{y}{i}\rfloor$，那么我们最终要求得答案就是：

$$
ans=\sum_{x=1}^a\lfloor\frac{a}{x}\rfloor\sum_{d=1}^{\min(b,c)}[\gcd(x,d)=1]\mu(d)g(x,\lfloor\frac{b}{d}\rfloor)g(x,\lfloor\frac{c}{d}\rfloor)
$$

$x$ 和 $d$ 都是枚举处理的，那么唯一的问题就是如何快速预处理 $g$ 数组。

$$
g(x,y)=\sum\limits_{i=1}^y[\gcd(x,i)=1]\lfloor\frac{y}{i}\rfloor
$$

我们考虑每个 $i$ 对每个 $g(x,y)$ 的贡献。显然，若 $\gcd(x,i)\neq 1$，必定没有贡献。

枚举 $i$ 和有贡献的 $x$，此时 $i$ 对 $g(x,y)$ 的贡献为 $\lfloor\frac{y}{i}\rfloor$。关注到下取整变化的是上半部分，换而言之每次产生相同贡献的位置是一个长为 $i$ 的连续段。将 $g$ 数组差分，对于每个 $x$ 和 $i$ 至多有 $\lceil\frac {2000}i\rceil$ 个位置会被修改。显然这是调和级数，暴力即可。最后差分数组转回原数组得解。

复杂度 $O(n^2\log n)$，其中 $n=\max\{a,b,c\}$。

```cpp
#include<cstdio>
const int mod=1<<30;
int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
int a,b,c;
long long g[2001][2001];
bool isp[2001];
int p[2001],u[2001],tot;
void s(){
	int i,j;
	u[1]=1;
	for(i=2;i<=2000;i++){
		if(!isp[i])p[++tot]=i,u[i]=-1;
		for(j=1;j<=tot&&i*p[j]<=2000;j++){
			isp[i*p[j]]=1;
			if(i%p[j]==0)break;
			u[i*p[j]]=u[i]*u[p[j]];
		}
	}
}
int main(){
	int i,j,k;
	long long res=0;
	s();
	for(i=1;i<=2000;i++){
		for(j=1;j<=2000;j++){
			if(gcd(i,j)!=1)continue;
			for(k=i;k<=2000;k+=i)g[j][k]++;
		}
	}
	for(i=1;i<=2000;i++)for(j=1;j<=2000;j++)g[i][j]+=g[i][j-1],g[i][j]%=mod;
	scanf("%d%d%d",&a,&b,&c);
	for(i=1;i<=a;i++){
		for(j=1;j<=b&&j<=c;j++){
			if(gcd(i,j)!=1)continue;
			res+=g[i][b/j]*g[i][c/j]%mod*(a/i)*u[j]%mod+mod;
			res%=mod;
		}
	}
	printf("%lld",res);
}
```

---

## 作者：i207M (赞：3)

~~模$2^{30}$好评~~

求$\sum^a_{i=1}\sum^b_{j=1}\sum^c_{k=1}{d\left(ijk\right)}$

$a,b,c < 2000$

一看到除数函数，并且内部是两个数的乘积，我们可以想到SDOI<约数个数和>这道题。回想我们当时是如何统计答案的。

显然，$ij$的因数，一定是i的因数和j的因数乘起来的结果。但是一个因数可能会被枚举两遍，怎么办？我们可以加一些限制条件，例如，使因数的组成大部分从i中来，也就是要求

$\sum^n_{i=1}\sum^m_{j=1}\sum_{u|i}\sum_{v|j}{[(u,j/v) == 1]} $

又因为枚举$v,j/v$是相同的，所以可以：

$\sum^n_{i=1}\sum^m_{j=1}\sum_{u|i}\sum_{v|j}{[(u,v) == 1]} $

对于3D的情况，类似的。我们把因数优先放到i，其次放到j，最后是k。

$\sum^a_{i=1}\sum^b_{j=1}\sum^c_{k=1}\sum_{u|i}\sum_{v|j}\sum_{w|k}[(u,v)==1][(u,w)==1][(v,w)==1]$

~~你以为我和下面的题解一样？怎么可能！~~

事实上，这个神奇的等式成立：

![](https://cdn.luogu.com.cn/upload/pic/48855.png)

证明可以这样理解：上图的$i,j,k$就是上个式子的$u,v,w$。我们枚举三个互质的数对，看它们可以被哪些数枚举到。

![](https://cdn.luogu.com.cn/upload/pic/48867.png)

复杂度瓶颈在求gcd上，可以$O(n^2)$求1-n互相的gcd的，但是我懒得写了（方法：记忆化）

```cpp
int A,B,C;
bool vis[N];
int S[N][N],G[N][N];
vector<int>Q;
void prework()
{
	if(A>B) swap(A,B); if(A>C) swap(A,C);
	if(B>C) swap(B,C);
	for(ri i=1; i<=C; ++i)
		for(ri j=1; j<=i; ++j)
			G[i][j]=G[j][i]=__gcd(i,j);
	for(ri i=1,j,t; i<=B; i=j+1)
	{
		j=B/(B/i),t=B/i;
		if(!vis[t]) vis[t]=1,Q.pb(t);
	}
	for(ri i=1,j,t; i<=C; i=j+1)
	{
		j=C/(C/i),t=C/i;
		if(!vis[t]) vis[t]=1,Q.pb(t);
	}
	for(ri i=1; i<=A; ++i)
	{
		static int cop[N];
		for(ri j=1; j<=C; ++j) cop[j]=(G[i][j]==1)+cop[j-1];
		for(solid v:Q)
		{
			int ans=0;
			for(ri k=1,h; k<=v; k=h+1)
			{
				h=v/(v/k);
				ans+=v/k*(cop[h]-cop[k-1]);
			}
			S[i][v]=ans;
		}
	}
}
void solve()
{
	int ans=0;
	for(ri i=1; i<=A; ++i)
	{
		int sum=0;
		for(ri j=1; j<=B; ++j)
		{
			if(!mu[j]||G[i][j]>1) continue;
			sum+=mu[j]*S[i][B/j]*S[i][C/j];
		}
		ans+=A/i*sum;
	}
	ans&=1073741823;
	out(ans);
}
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("out.out","w",stdout);
#endif
	sieve(2000);
	in(A,B,C);
	prework();
	solve();
	return 0;
}
```

---

## 作者：whiteqwq (赞：3)

[CF235E Number Challenge](https://www.luogu.com.cn/problem/CF235E)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1772613)

## 题意
- 给定$a,b,c$，求$\sum_{i=1}^a\sum_{j=1}^b\sum_{k=1}^c d(i\times j\times k)$
- $1\leqslant a,b,c\leqslant 2000$

## 分析

第一眼就看出来好像见过这道题，然后想起来它是[P4619 [SDOI2018]旧试题](https://www.luogu.com.cn/problem/P4619)的弱化版~~到底是CCF抄CF的还是CF抄CCF的呢~~：

我们先证明一个毒瘤式子$d(x\cdot y\cdot y)=\sum_{i\mid x}\sum_{j\mid y}\sum_{k\mid z}[\gcd(i,j,k)==1]$

当$x=\prod_{i=1}^s p_i^{k_i}$因为$d(x)=\prod_{i=1}^s(k_i+1)$为$x$的因数个数，因此考虑将$x\cdot y\cdot z$的每个因数对应一组互质的因数

对于每个质数$p\mid x\cdot y\cdot z$，且$x$中$p$的幂次为$a$，$y$中$p$的幂次为$b$，$z$中$p$的幂次为$c$，则$x\cdot y\cdot z$中$p$的幂次为$a+b+c$。

根据$d$的积性与$\gcd(p^{a+b+c},\frac{x\cdot y\cdot z}{p^{a+b+c}})==1$，得：$d(x\cdot y\cdot z)=d(\frac{x\cdot y\cdot z}{p^{a+b+c}})\cdot d(p^{a+b+c})=d(\frac{x\cdot y\cdot z}{p^{a+b+c}})\cdot(a+b+c+1)$，即$p$对左式的贡献为$a+b+c+1$

令$i\mid x,j\mid y,k\mid z$且$\gcd(i,j,k)=1$，则$i$中$p$的幂次$u$不超过$a$，$j$中$p$的幂次$v$不超过$b$，$k$中$p$的幂次$w$不超过$c$，且$u$，$v$，$w$中起码有两个为$0$

- 当$v=w=0,u\ne 0$时，$u=1,2,\cdots a$，即有$a$种取值
- 当$u=w=0,v\ne 0$时，$v=1,2,\cdots b$，即有$b$种取值
- 当$u=v=0,w\ne 0$时，$w=1,2,\cdots c$，即有$c$种取值
- 当$u=v=w=0$时，只有$1$种取值

即每个$p$可以对右式同样产生$a+b+c+1$的贡献，因此对于每个$x\cdot y\cdot z$的质因子$p$，其会对左右两式均产生$a+b+c+1$即$p$的指数$+1$的贡献

因此我们可以把原式化为：$\sum_{i=1}\sum_{j=1}^B\sum_{k=1}^C\sum_{x\mid i}\sum_{y\mid j}\sum_{z\mid k}[\gcd(x,y,z)==1]$
$=\sum_{i=1}\sum_{j=1}^B\sum_{k=1}^C\sum_{x\mid i}\sum_{y\mid j}\sum_{z\mid k}[\gcd(x,y)==1][\gcd(y,z)==1][\gcd(x,z)==1]$

改变枚举顺序可得：$\sum_{x=1}^A\lfloor\frac{A}{x}\rfloor\sum_{y=1}^B\lfloor\frac{B}{y}\rfloor\sum_{z=1}^C\lfloor\frac{C}{z}\rfloor[\gcd(x,y)==1][\gcd(y,z)==1][\gcd(x,z)==1]$

使用莫比乌斯反演得原式可得：$\sum_{x=1}^A\lfloor\frac{A}{x}\rfloor\sum_{y=1}^B\lfloor\frac{B}{y}\rfloor\sum_{z=1}^C\lfloor\frac{C}{z}\rfloor\sum_{u\mid\gcd(x,y)}\mu(u)\sum_{v\mid\gcd(y,z)}\mu(v)\sum_{w\mid\gcd(x,z)}\mu(w)$

继续交换枚举顺序得：$\sum_{u=1}^{min(A,B)}\mu(u)\sum_{v=1}^{min(B,C)}\mu(v)\sum_{w=1}^{min(A,C)}\mu(w)\sum_{i=1}^{\lfloor\frac{A}{lcm(u,v)}\rfloor}\lfloor\frac{A}{lcm(u,v)\cdot i}\rfloor\sum_{j=1}^{\lfloor\frac{B}{lcm(v,w)}\rfloor}\lfloor\frac{B}{lcm(v,w)\cdot j}\rfloor\sum_{k=1}^{\lfloor\frac{C}{lcm(u,w)}\rfloor}\lfloor\frac{C}{lcm(u,w)\cdot k}\rfloor$

由引理$\lfloor\frac{a}{b\cdot c}\rfloor=\lfloor\frac{\lfloor\frac{a}{b}\rfloor}{c}\rfloor$得：$\sum_{i=1}^{\lfloor\frac{x}{y}\rfloor}\lfloor\frac{x}{y\cdot i}\rfloor=\sum_{i=1}^{\lfloor\frac{x}{y}\rfloor}\lfloor\frac{\lfloor\frac{x}{y}\rfloor}{i}\rfloor$，原式化为：$\sum_{u=1}^{min(A,B)}\mu(u)\sum_{v=1}^{min(B,C)}\mu(v)\sum_{w=1}^{min(A,C)}\mu(w)\sum_{i=1}^{\lfloor\frac{A}{lcm(u,v)}\rfloor}\lfloor\frac{\lfloor\frac{A}{lcm(u,v)}\rfloor}{i}\rfloor\sum_{j=1}^{\lfloor\frac{B}{lcm(v,w)}\rfloor}\lfloor\frac{\lfloor\frac{B}{lcm(v,w)}\rfloor}{j}\rfloor\sum_{k=1}^{\lfloor\frac{C}{lcm(u,w)}\rfloor}\lfloor\frac{\lfloor\frac{C}{lcm(u,w)}\rfloor}{k}\rfloor$

设$f(x)=\sum_{i=1}^x\lfloor\frac{x}{i}\rfloor$，考虑如何预处理$f(x)$：对于每一个$i\leqslant x$，$x$都会得到$i$的贡献$\lfloor\frac{x}{i}\rfloor$，即在$[1,x]$的范围内$i$的倍数个数。

因此$f(x)=\sigma(x)=\sum_{d\mid x}d$即约数和函数，这个函数通过可以枚举每个数的倍数在$O(n\log n)$的时间内预处理。

原式可化为：$\sum_{u=1}^{min(A,B)}\sum_{v=1}^{min(B,C)}\sum_{w=1}^{min(A,C)}\mu(u)\cdot\mu(v)\cdot\mu(w)\cdot\sigma(\frac{A}{lcm(u,v)})\cdot\sigma(\frac{B}{lcm(v,w)})\cdot\sigma(\frac{C}{lcm(u,w)})$

但是最后的式子还是$O(n^3)$的，就比暴力快一点点。

首先，我们可以把所有$\mu(x)=0$的$x$删去，这种$x$有不少，因此可以快很多。

其次，因为$\sigma(0)=0$，因此所有的$lcm(u,v)>A,lcm(v,w)>B,lcm(u,w)>C$可以剪掉。（其实不剪掉也没有关系，对答案没有影响，因此我们将$A,B,C$统一改为$max(A,B,C)$）

为了达到更低的复杂度，我们可以使用一种毒瘤算法：三元环计数。感性理解一下，枚举三个数$u,v,w$，且满足$lcm(u,v)\leqslant A,lcm(v,w)\leqslant B,lcm(u,w)\leqslant C$就相当于在一张只要任意两个点满足其最小公倍数小于等于$max(A,B,C)$边会有一条边的图中枚举三元环。

三元环计数算法可以在$O(m\sqrt{m})$的时间内求出所有三元环，具体见nekko的博客：[不常用的黑科技——「三元环」](https://www.luogu.com.cn/blog/KingSann/fou-chang-yong-di-hei-ke-ji-san-yuan-huan-post)

时间复杂度：$O(m\sqrt{m})$。

## 代码
直接拿的旧试题的代码，加了亿点常数优化，凑合着看吧。
```
#include<stdio.h>
#include<vector>
#include<string.h>
#define int long long
using namespace std;
const int maxn=1000005,maxm=1000005,mod=1073741824;
int i,j,k,a,b,c,e,mx,mn,T,cnt,tot,ans;
int lst[maxn],d[maxn],p[maxn],mu[maxn],ok[maxn],ord[maxn],deg[maxn],f[maxn],from[maxm],to[maxm],lcm[maxm],mrk[maxn];
vector<int>v[maxn],w[maxn];
inline int min(int a,int b){
	return a<b? a:b;
}
inline int max(int a,int b){
	return a>b? a:b;
}
inline int gcd(int a,int b){
	return b==0? a:gcd(b,a%b);
}
signed main(){
	p[1]=mu[1]=1;
	for(int i=2;i<maxn;i++){
		if(p[i]==0)
			lst[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt;j++){
			if(i*lst[j]>=maxn)
				break;
			p[i*lst[j]]=1;
			if(i%lst[j]==0){
				mu[i*lst[j]]=0;
				break;
			}
			mu[i*lst[j]]=-mu[i];
		}
	}
	for(int i=1;i<maxn;i++)
		if(mu[i]!=0)
			ok[++tot]=i,ord[i]=tot;
	for(int i=1;i<maxn;i++){
		for(int j=1;i*j<maxn;j++)
			d[i*j]++;
		f[i]=(f[i-1]+d[i])%mod;
	}
	scanf("%lld%lld%lld",&a,&b,&c);
	mn=min(min(a,b),c),mx=max(max(a,b),c);
	e=ans=0;
	for(int i=1;i<=tot;i++){
		if(ok[i]>mx)
			break;
		for(int j=1;j<=tot;j++){
			if(ok[i]*ok[j]>mx)
				break;
			if(mu[ok[i]*ok[j]]==0)
				continue;
				for(int k=j+1;k<=tot;k++){
				if(ok[i]*ok[j]*ok[k]>mx)
					break;
				if(mu[ok[i]*ok[k]]==0||gcd(ok[j],ok[k])>1)
					continue;
				from[++e]=ord[ok[i]*ok[j]],to[e]=ord[ok[i]*ok[k]],lcm[e]=ok[i]*ok[j]*ok[k];
				deg[from[e]]++,deg[to[e]]++;
			} 
		}
	}
	for(int i=1;i<=tot;i++){
		if(ok[i]>mn)
			break;
		ans+=mu[ok[i]]*mu[ok[i]]*mu[ok[i]]*f[a/ok[i]]*f[b/ok[i]]*f[c/ok[i]];
	}
	for(int i=1;i<=e;i++){
		v[from[i]].push_back(to[i]),w[from[i]].push_back(lcm[i]);
		v[to[i]].push_back(from[i]),w[to[i]].push_back(lcm[i]);
	}
	for(int i=1;i<=tot;i++){
		if(ok[i]>min(a,b))
			break;
		for(int j=0;j<v[i].size();j++){
			int x=ok[i],y=ok[v[i][j]],z=w[i][j];
			ans=(ans+mu[x]*mu[y]*mu[y]*f[a/z]*f[b/z]*f[c/y]%mod+mod)%mod;
			ans=(ans+mu[x]*mu[x]*mu[y]*f[a/x]*f[b/z]*f[c/z]%mod+mod)%mod;
			ans=(ans+mu[x]*mu[x]*mu[y]*f[a/z]*f[b/x]*f[c/z]%mod+mod)%mod;
		}
	}
	memset(v,0,sizeof(v));
	memset(w,0,sizeof(w));
	for(int i=1;i<=e;i++){
		if(deg[from[i]]>=deg[to[i]])
			v[from[i]].push_back(to[i]),w[from[i]].push_back(lcm[i]);
		else v[to[i]].push_back(from[i]),w[to[i]].push_back(lcm[i]);
	}
	for(int i=1;i<=tot;i++){
		if(ok[i]>mx)
			break;
		for(int j=0;j<v[i].size();j++)
			mrk[v[i][j]]=w[i][j];
		for(int j=0;j<v[i].size();j++){
			int x=v[i][j];
			for(int k=0;k<v[x].size();k++){
				int y=v[x][k],p=mrk[y],q=w[i][j],r=w[x][k];
				if(mrk[y]==0)
					continue;
				int st1,st2,st3,st4,st5,st6;
				st1=f[a/p]*f[b/q]*f[c/r]%mod;
				st2=f[a/p]*f[b/r]*f[c/q]%mod;
				st3=f[a/q]*f[b/p]*f[c/r]%mod;
				st4=f[a/q]*f[b/r]*f[c/p]%mod;
				st5=f[a/r]*f[b/p]*f[c/q]%mod;
				st6=f[a/r]*f[b/q]*f[c/p]%mod;
				ans=(ans+mu[ok[i]]*mu[ok[x]]*mu[ok[y]]*(st1+st2+st3+st4+st5+st6)%mod+mod)%mod;
			}
		}
		for(int j=0;j<v[i].size();j++)
			mrk[v[i][j]]=0;
	}
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}
```

---

## 作者：legendgod (赞：3)

[题目](https://www.luogu.com.cn/problem/CF235E)

本题解就是想提供一种稍微简单的写法，因为 $a,b,c\le2000$ 所以我们的复杂度可以是 $O(n^2 \sqrt{n})$，这就导致我们并不需要将所有的 gcd 都进行反演，只要反演一个就可以了。

首先我们发现这个模数十分的毒瘤，所以马上开了 long long 。

其次本题有一个黑科技:

$$d(ij) = \sum_{a | i} \sum_{b | j} [gcd(i,j) == 1]$$

这其实是本题的简单版，我们继续考虑 $d(ijk)$ 的情况。

$$d(ijk) = \sum_{a | i} \sum_{b | j} \sum_{c | k} [gcd(i,j) == gcd(j, k) == gcd(k,i) == 1]$$

这样我们就可以愉快得推式子了:

$$\sum_{i = 1} ^ A\sum_{j = 1} ^B \sum_{k = 1} ^ C d(ijk)$$

$$= \sum_{i = 1} ^ A\sum_{j = 1} ^B \sum_{k = 1} ^ C \sum_{a | i} \sum_{b | j} \sum_{c | k} [gcd(i,j) == gcd(j, k) == gcd(k,i) == 1]$$

$$= \sum_{a = 1} ^ A\sum_{b = 1} ^B \sum_{c = 1} ^ C \sum_{a | i}^A\sum_{b | j}^B \sum_{c | k}^C [gcd(a,b) == gcd(b, c) == gcd(c,a) == 1]$$

$$= \sum_{a = 1} ^ A\sum_{b = 1} ^B \sum_{c = 1} ^ C \lfloor \frac{A}{a}\rfloor \lfloor \frac{B}{b}\rfloor \lfloor \frac{C}{c}\rfloor[gcd(a,b) == gcd(b, c) == gcd(c,a) == 1]$$

$$= \sum_{i = 1} ^ A\sum_{j = 1} ^B \sum_{k = 1} ^ C \lfloor \frac{A}{i}\rfloor \lfloor \frac{B}{j}\rfloor \lfloor \frac{C}{k}\rfloor[gcd(i,j) == gcd(j, k) == gcd(k,i) == 1]$$

$$= \sum_{i = 1} ^ A\sum_{j = 1} ^B \sum_{k = 1} ^ C \lfloor \frac{A}{i}\rfloor \lfloor \frac{B}{j}\rfloor \lfloor \frac{C}{k}\rfloor \sum_{d | gcd(i,j)}\mu (d)[gcd(j, k) == gcd(k,i) == 1]$$

$$=\sum_{k = 1} ^ C \sum_{d = 1} ^ {min(A,B)} \mu (d) \sum_{i = 1} ^ {\lfloor \frac{A}{d} \rfloor} \lfloor \frac{A}{id}\rfloor [gcd(id,k) == 1]\sum_{j = 1} ^ {\lfloor \frac{B}{d} \rfloor} \lfloor \frac{B}{jd}\rfloor [gcd(jd, k) == 1]$$

----
现在，我们已经得到了本题的答案，笔者在这里提供几个优化：

> 优化 1 : 我们可以预处理 $\sum_{i = 1} ^ {\lfloor \frac{A}{d} \rfloor} \lfloor \frac{A}{id}\rfloor [gcd(id,k) == 1]$ 后面的 B 同理。

> 优化 2 : 判断是否互质的时候可以用空间换时间。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
template <class T> 
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; !isdigit(c);c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c);c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f; 
} 

const int maxn = 2e3 + 5;
#define mod 1073741824
#define int long long
int n, m;
bool vis1[maxn];
int tot, pr[maxn], mu[maxn];
int a, b, c;
int gcd(int a,int b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}
int sum[maxn];
void init(int x) {
	mu[1] = sum[1] = 1;
	for(int i = 2;i <= x; ++i) {
		if(!vis1[i]) pr[++ tot] = i, mu[i] = -1;
		for(int j = 1,k;k = pr[j] * i, k <= x && j <= tot; ++j) {
			vis1[k] = 1;
			if(!(i % pr[j])) {
				mu[k] = 0;
				break;
			}
			mu[k] = -mu[i];
		}
		sum[i] = (sum[i - 1] + mu[i]);
//		printf("%lld ", i);
	} 
//	for(int i = 2;i <= x; ++i) printf("%lld ", mu[i]);
}

//template <typename T> inline T Mod(const T value) { return value>=mod?value-mod:value; }
#define Mod(x) (x % mod)

int fa[maxn][maxn], fb[maxn][maxn];
int vis[maxn][maxn];

void init1() {
	for(register int k = 1;k <= 2000; ++k) {
		for(register int i = 1;i <= 2000; ++ i) {
			if(gcd(i, k) != 1)  vis[k][i] = 1;
		}
	} // 预处理出互质的数 。 
	for(register int k = 1;k <= c; ++k) {
		for(register int d = 1 , lim = min(a, b);d <= lim; ++ d) {
			for(register int i = 1 , lim2 = a / d;i <= lim2; ++ i) {
				if(!vis[k][i * d]) {
					fa[k][d] = Mod(fa[k][d] + a / (d * i));				
				}
			}
		}
	}
//	cerr<<"ttt";
	for(register int k = 1;k <= c; ++k) {
		for(register int d = 1 , lim = min(a, b);d <= lim; ++ d) {
			for(register int i = 1 , lim2 = b / d;i <= lim2; ++i) {
				if(!vis[k][i * d]) {
					fb[k][d] = Mod(fb[k][d] + b / (d * i));
				}
			}
		}
	} // 计算 A, B 两部分。 
	return ;
}

signed main() {
	r1(a), r1(b), r1(c);
	init(2000), init1();
//	puts("________");
	int ans(0);
	for(int k = 1;k <= c; ++k) {
		
		int tmp(0);
		
		for(int d = 1;d <= min(a, b); ++ d) {
			tmp = (tmp + fa[k][d] * fb[k][d] % mod * mu[d] % mod) % mod;
		}
		ans = (ans + tmp * (c / k) % mod) % mod;
	} // 直接暴力计算 。 
	ans %= mod;
	printf("%lld\n", (ans + mod) % mod);
	return 0;
}


```


---

## 作者：WeLikeStudying (赞：1)

- 我发现个人给这篇题解的主要解法给了一点分析。

**[题意](https://www.luogu.com.cn/problem/P4619)**
- 给定 $A,B,C$，求：
$$\sum_{i=1}^A\sum_{j=1}^B\sum_{k=1}^C\sigma_{0}(i\cdot j\cdot k)$$

**分析**
- 经过[套路](https://www.luogu.com.cn/blog/luo1gu1zui1bang1/solution-p4619)之后，我们得到了平方的解法。
- 设：
$$G(n)=\sum_{i=1}^n\sigma_0(n)$$
- 我们要求的就是（注意求和号的上标其实可以是有界的）：
$$\sum_{i=1}^{+\infty}\sum_{j=1}^{+\infty}\sum_{k=1}^{+\infty}\mu(i)\mu(j)\mu(k)G\bigg(\frac A{\operatorname{lcm}(i,j)}\bigg)G\bigg(\frac B{\operatorname{lcm}(i,k)}\bigg)G\bigg(\frac C{\operatorname{lcm}(j,k)}\bigg)$$
- 感觉有效的项似乎很稀疏，因此我们把所有有效果的项看作是是 $[1,n]$ 上任何莫比乌斯函数不为 $0$ 且最小公倍数小于 $n$ 的点互相连边，然后它的三元环的个数就是枚举的复杂度。
- 我们知道无向图三元环的个数可以由根号分治算得为 $O(m\sqrt m)$ 级别，那么接下来问题在于图的边数是多少呢？我们可以得到这个式子：
$$\sum_{i=1}^{+\infty}\sum_{j=1}^{+\infty}\mu^2(i)\mu^2(j)[\text{lcm}(i,j)\le n]$$
- 显然，它与这个式子等价：
$$\sum_{i=1}^n\mu^2(i)3^{\omega(i)}$$
- 因此我们可以轻易地推知它是 $O(n\log^2n)$ 级别的，因为可以看作为两重因子枚举，因此最终我们得到的复杂度就是 $O(n\sqrt n\log^3n)$，不太可过的理论复杂度，不过在实际中，$n=10^5$ 的建边数：
$$\frac 12\sum_{i=1}^{10^5}\mu^2(i)(3^{\omega(i)}-1)=760741$$
- [代码](https://www.luogu.com.cn/paste/ttd1onws)，这告诉我们理论复杂度这东西有多么不靠谱。

**另外一种方法**
- 非常恰好，[这篇](https://www.luogu.com.cn/blog/luo1gu1zui1bang1/du-liu-zhi-shen-di-kao-yan)里面提到了计算内积的一种有趣方法。
- 我认为这里可以用纯纯的数论方法来做，接下来的问题是需要哪些式子？

---

## 作者：lingying (赞：1)

其实这道题有[加强版](https://www.luogu.com.cn/problem/P4619)。

之后会了也写一篇题解（

# 题意

求：

$$
\sum\limits_{i=1}^A\sum\limits_{j=1}^B\sum\limits_{k=1}^C d(ijk) \pmod {1073741824}
$$

$A,B,C\le 2000$。

# 解法

$$

\begin{aligned}

\sum\limits_{i=1}^A\sum\limits_{j=1}^B\sum\limits_{k=1}^C d(ijk) &=\sum\limits_{i=1}^A\sum\limits_{j=1}^B\sum\limits_{k=1}^C\sum\limits_{a\mid i}\sum\limits_{b\mid j}\sum\limits_{c\mid k} \left[\gcd(a,b)=1\right]\left[\gcd(b,c)=1\right]\left[\gcd(a,c)=1\right]\\&=\sum\limits_{a=1}^A\sum\limits_{b=1}^B\sum\limits_{c=1}^C \left[\gcd(a,b)=1\right]\left[\gcd(b,c)=1\right]\left[\gcd(a,c)=1\right] \left\lfloor \dfrac{A}{a}\right\rfloor\left\lfloor\dfrac{B}{b} \right\rfloor \left\lfloor \dfrac{C}{c}\right\rfloor
\\&=\sum\limits_{a=1}^A\sum\limits_{b=1}^B \sum\limits_{c=1}^C\left(\sum\limits_{i\mid a,i\mid b}\mu (i) \right)\left[\gcd(b,c)=1\right]\left[\gcd(a,c)=1\right] 
\left\lfloor \dfrac{A}{a}\right\rfloor\left\lfloor\dfrac{B}{b} \right\rfloor \left\lfloor \dfrac{C}{c}\right\rfloor

\\&=\sum\limits_{i=1}^{\min(A,B)}\mu(i)\sum\limits_{a=1}^{\left\lfloor \frac{A}{i} \right\rfloor} \sum\limits_{b=1}^{\left\lfloor \frac{B}{i} \right\rfloor}\sum\limits_{c=1}^C \left[\gcd(b,c)=1\right]\left[\gcd(a,c)=1\right] \left\lfloor \dfrac{A}{ai} \right\rfloor \left\lfloor \dfrac{B}{bi} \right\rfloor \left\lfloor \dfrac{C}{c} \right\rfloor

\\&=\sum\limits_{i=1}^{\min(A,B)}\mu(i)\sum\limits_{c=1}^C\left\lfloor \dfrac{C}{c} \right\rfloor \left( \sum\limits_{a=1}^{\left\lfloor \frac{A}{i}\right\rfloor} \left[ \gcd(ai,c)=1\right]  \left\lfloor\dfrac{A}{ai} \right\rfloor \right)   \left( \sum\limits_{b=1}^{\left\lfloor \frac{B}{i}\right \rfloor} \left[ \gcd(bi,c)=1\right]  \left\lfloor\dfrac{B}{bi} \right\rfloor \right)

\end{aligned}
$$

预处理一下 $\gcd$，时间复杂度为 $O(n^2\ln n)$。

$n=\max(A,B,C)$。

# 代码

```
#include<bits/stdc++.h>
using namespace std;

typedef unsigned int uint;

const int N=2005;

int a,b,c;
int prime[N],mu[N];
bool mark[N][N],nt_prime[N];

int gcd(int a,int b){return b?gcd(b,a%b):a;}

void prepare()
{
	mu[1]=1;
	int idx=0;
	for(int i=2;i<N;i++)
	{
		if(!nt_prime[i])prime[++idx]=i,mu[i]=-1;
		for(int j=1;j<=idx&&i*prime[j]<N;j++)
		{
			nt_prime[i*prime[j]]=1;
			if(i%prime[j]==0)break;
			mu[i*prime[j]]=-mu[i];
		}
	}
}

int main()
{
	prepare();
	for(int i=1;i<N;i++)
		for(int j=1;j<N;j++)
			mark[i][j]=(gcd(i,j)==1);
	cin>>a>>b>>c;
	uint ans=0;
	for(int i=1;i<=min(a,b);i++)
	{
		uint sum=0;
		for(int j=1;j<=c;j++)
		{
			uint tot=c/j;
			uint t1=0;
			uint t2=0;
			for(int k=1;k<=a/i;k++)t1+=mark[i*k][j]*(a/(i*k));
			for(int k=1;k<=b/i;k++)t2+=mark[i*k][j]*(b/(i*k));
			tot=tot*t1*t2;
			sum+=tot;
		}
		sum=sum*mu[i];
		ans+=sum;
	}
	ans&=1073741823;
	cout<<ans;
	return 0;
}
```

---

## 作者：namelessgugugu (赞：1)

暴力过题好文明。

#### 题意

给定 $a, b, c$，求所有 $\sum\limits_{i=1}^a\sum\limits_{j=1}^b\sum\limits_{k=1}^c d(i \cdot j \cdot k)$，其中 $d(n)$ 表示正整数 $n$ 的因数个数。

$1 \leq a, b, c \leq 2000$。

#### 题解

我不会莫反也不会经典结论，所以这是个暴力解法。

考虑枚举质数 $p$，然后枚举 $i, j, k$ 三个数各有多少个因子 $p$。

直接实现是把 $i, j, k$ 全放进状态里，连空间都开不下，所以应该改为存 $\lfloor \frac{a}{i} \rfloor, \lfloor \frac{b}{i} \rfloor, \lfloor \frac{c}{i} \rfloor$，设 $n = \max\{a, b, c\}$，则这样的状态数是 $O(n^{1.5})$ 的，可以接受。

同时枚举 $i, j, k$ 各有多少个因子 $p$ 也很慢，注意到，如果 $i, j, k$ 共有 $t$ 个因子 $p$，则 $d(i, j, k)$ 需要乘上 $t + 1$，这是记录 $t$ 唯一的用途。所以考虑用组合意义优化，不是枚举因子数量，而是不断给 $i, j, k$ 中的某一个乘上 $p$（为了防止算重，应该先不断给 $i$ 乘 $p$，再不断给 $j$ 乘 $p$，最后不断给 $k$ 乘 $p$），然后选择在某一次乘法时打上标记或不打标记，这样乘了 $t$ 个 $p$ 就自然有 $t + 1$ 种方案了。

再发现枚举质数也可以优化，因为 $i, j, k$ 中各只会有一个大于 $\sqrt{n}$ 的质因数，而 $2000$ 以内质数只有约 $300$ 个，所以先枚举这三个数各自的大质因数是多少，再只对 $\leq \sqrt{n}$ 的质数跑上面的 DP。

两部分复杂度分别是 $O((\frac{n}{\log n})^3)$ 和 $O(\frac{n^2}{\log n})$，注意这里用 $O(\frac{n}{\log n})$ 和 $O(\frac{\sqrt{n}}{\log n})$ 估计 $n$ 以内和 $\sqrt n$ 以内的质数个数。需要实现不那么放飞自我才能通过。

#### 代码

```
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int N = 2005, M = 105;
typedef unsigned int ui;
int n[3], m[3], V;
std::vector<int> id[3];
int mp[3][N];
std::vector<int> pri[2];
ui f[M][M][M][2];
int main(void)
{
	scanf("%d%d%d", n + 0, n + 1, n + 2), V = std::max({n[0], n[1], n[2]});
	for(int o = 0;o < 3;++o)
	{
		memset(mp[o], 0xff, sizeof(mp[o]));
		for(int l = 1, r;l <= n[o];l = r + 1)
		{
			int v = n[o] / l;
			r = n[o] / v;
			id[o].push_back(v);
		}
		id[o].push_back(0);
		std::reverse(id[o].begin(), id[o].end());
		m[o] = (signed)id[o].size() - 1;
		for(int i = 0;i <= m[o];++i)
			mp[o][id[o][i]] = i;
	}
	for(int i = 2;i <= V;++i)
	{
		bool flag = 1;
		for(int j = 2;1ll * j * j <= i;++j)
			if(i % j == 0)
			{
				flag = 0;
				break;
			}
		if(flag)
			pri[i * i > V].push_back(i);
	}
	pri[1].push_back(1); // 有可能 i, j, k 没有大于根号 n 的质因数
	for(int a : pri[1])
		for(int b : pri[1])
			for(int c : pri[1])
			{
				int tmp[3] = {a, b, c};
				if(tmp[0] > tmp[1])
					std::swap(tmp[0], tmp[1]);
				if(tmp[1] > tmp[2])
					std::swap(tmp[1], tmp[2]);
				if(tmp[0] > tmp[1])
					std::swap(tmp[0], tmp[1]);
				ui v = 1;
				for(int l = 0, r;l < 3;l = r)
				{
					r = l;
					while(r < 3 && tmp[l] == tmp[r])
						++r;
					if(tmp[l] != 1)
						v *= (r - l + 1);
				}
				f[mp[0][n[0] / a]][mp[1][n[1] / b]][mp[2][n[2] / c]][0] += v;
			}
	for(int x : pri[0])
	{
		int it[3] = {};
		for(int o = 0;o < 3;++o)
			for(it[0] = m[0];it[0] >= 1;--it[0])
				for(it[1] = m[1];it[1] >= 1;--it[1])
					for(it[2] = m[2];it[2] >= 1;--it[2])
					{
						int to[3] = {it[0], it[1], it[2]};
						to[o] = mp[o][id[o][it[o]] / x];
						ui *g = f[to[0]][to[1]][to[2]], *fr = f[it[0]][it[1]][it[2]];
						g[0] += fr[0];
						g[1] += fr[0] + fr[1];
					}
		for(int i = 1;i <= m[0];++i)
			for(int j = 1;j <= m[1];++j)
				for(int k = 1;k <= m[2];++k)
					f[i][j][k][0] += f[i][j][k][1], f[i][j][k][1] = 0;
	}
	ui ans = 0;
	for(int i = 1;i <= m[0];++i)
		for(int j = 1;j <= m[1];++j)
			for(int k = 1;k <= m[2];++k)
				ans += f[i][j][k][0];
	ans &= (1 << 30) - 1;
	printf("%u\n", ans);
	return 0;
}
```

---

