# Petya and Coloring

## 题目描述

--
$Petya$喜欢计数。他想计算：

   用$K$种颜色绘制尺寸为$n*m$ ( $n$行，$m$列)的矩形棋盘的方法数。
   
此外，着色应满足以下要求：
   
   对于沿格子的线穿过的任何垂直线，会将棋盘分成两个非空的部分，这两个部分中的不同颜色的数量应相同。
  
帮助$Petya$对这些颜色进行计数。

## 样例 #1

### 输入

```
2 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2 2
```

### 输出

```
8
```

## 样例 #3

### 输入

```
3 2 2
```

### 输出

```
40
```

# 题解

## 作者：Unstoppable728 (赞：3)

[博客欢迎来踩QAQ](https://www.cnblogs.com/blog-Dr-J/p/10389476.html)

## 解题思路：

要求一条直线分割矩阵时左右颜色数一样，那么就说明一个问题：
直线左右移动时是不会改变左右矩阵的颜色集合的。

所以说明：2~m-1列的颜色集一定属于第一列与第m列颜色集的交集，而且第一列与第m列颜色集大小相等。

显然需要预处理前n个点前m种颜色的方案数，设为$g(i,j)$

这样，只需要确定第一列和最后一列颜色集，假设交集是$i$种颜色，就可以算出中间的颜色方案数：$i^{n*(m-2)}$

假设两边颜色个数都是$j$（$j\ge i$）那么两边颜色的答案为$(g(n,j)j!)^2$

这$i$种颜色共有$C_k^i$种选法，两边各$j$种颜色，且只有$i$种颜色相同的方案就是：

$\Large C_k^iC_{k-i}^{2(j-i)}C_{2(j-i)}^{j-i}$

那么最后答案就是

$\Large\sum\limits_{i=1}^{n}\sum\limits_{j=i}^{n}C_k^iC_{k-i}^{2(j-i)}C_{2(j-i)}^{j-i}{(g(n,j)j!)^2}{i^{n(m-2)}}$

代码：

```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long lnt;
const lnt mod=1000000007;
lnt g[1010][1010];
lnt fac[1000010];
lnt inv[1000010];
int n,m,k;
lnt ans;
lnt ksm(lnt a,lnt b)
{
    lnt ans=1;
    while(b)
    {
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b=b/2;
    }
    return ans;
}
lnt C(int x,int y)
{
    if(y>x)return 0;
    return fac[x]*inv[y]%mod*inv[x-y]%mod; 
}
lnt squ(lnt x)
{
    return x*x%mod;
}
int main()
{
    g[0][0]=1;
    fac[0]=inv[0]=fac[1]=inv[1]=1;
    for(int i=2;i<=1000000;i++)
    {
        fac[i]=(fac[i-1]*i)%mod;
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
    }
    for(int i=1;i<=1000000;i++)inv[i]=inv[i]*inv[i-1]%mod;
    scanf("%d%d%d",&n,&m,&k);
    if(m==1)
    {
        printf("%I64d\n",ksm(k,n));
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i&&j<=k;j++)
        {
            g[i][j]=(g[i-1][j-1]+g[i-1][j]*j)%mod;
        }
    }
    for(int i=0;i<=n;i++)
    {
        lnt tmp=ksm(i,n*(m-2))*C(k,i)%mod;
        for(int j=i;j<=n;j++)
        {
            ans=(ans+tmp*C(k-i,(j-i)*2)%mod*C((j-i)*2,j-i)%mod*squ(g[n][j]*fac[j]%mod)%mod)%mod;
        }
    }
    printf("%I64d\n",(ans%mod+mod)%mod);
    return 0;
}
```

---

## 作者：zifanwang (赞：3)

很明显这是一道组合题。

首先特判一下，当 $m=1$ 时，答案就是 $k^n$。

对于 $m>1$ 的情况，我们可以得出一个结论：

对于沿格子的线穿过的任何垂直线，会将棋盘分成两个非空的部分，这两个部分中的不同颜色的数量相同**且总是不变**。设这个不同颜色的数量为 $i$，那么左边这部分的颜色一定是固定的 $i$ 种颜色，右边那部分也一定是固定的 $i$ 种颜色。

由于分开前两列的垂线的左边部分只有第一列的格子，所以左边的 $i$ 种颜色中的每一种都一定至少会在第一列中出现一次，最后一列同理。

我们设左边的颜色为集合 $S1$，右边的颜色为集合 $S2$，$|S1|=|S2|=i$，那么中间的 $m-2$ 列能染的颜色的种数为 $|S1\cap S2|$。

我们可以先枚举 $i$，再枚举 $|S1\cap S2|$ （设其为 $j$），那么 $S1$ 和 $S2$ 就总共有 ${k \choose j}{k-j \choose i-j}{k-i \choose i-j}$ 种取法，给中间 $m-2$ 列染色的方案数为 $j^{(m-2)n}$，给前后两列染色的方案数可以用容斥得出。

我们设 $f(m)$ 表示给 $n$ 个格子染 $m$ 种颜色每一种颜色都至少出现一次的方案数，我们用容斥得出 $f(m)$：

$$f(m)=\sum_{i=0}^{m} (-1)^i\times {m\choose i}(m-i)^n$$

整理得到最终的答案：

$$\sum_{i=1}^{min(k,n)} f(i)^2\times \sum_{j=0}^{i} {k \choose j}{k-j \choose i-j}{k-i \choose i-j}\times j^{(m-2)n}$$

这个值可以在 $O(n^2(\log n+\log m))$ 的时间复杂度内得到。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 1000003
#define md 1000000007
#define rep(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
int n,m,k,xi,inv[mxn],fac[mxn],ifac[mxn];
ll ans;
inline ll C(int n,int m){
	if(m>n)return 0;
	return (ll)fac[n]*ifac[n-m]%md*ifac[m]%md;
}
inline ll power(ll x,int y){
	ll ans=1;
	for(;y;y>>=1){
		if(y&1)ans=ans*x%md;
		x=x*x%md;
	}
	return ans;
}
inline ll p2(ll x){
	return x*x%md;
}
ll color(int n,int m){
	ll ans=0;
	xi=1;
	rep(i,0,m){
		ans=(ans+C(m,i)*power(m-i,n)%md*xi)%md;
		xi*=-1;
	}
	return ans;
}
signed main(){
	cin>>n>>m>>k;
	if(m==1){
		cout<<power(k,n);
		return 0;
	}
	inv[1]=fac[1]=ifac[1]=1;
	fac[0]=ifac[0]=1;
	rep(i,2,1000000){
		inv[i]=(ll)inv[md%i]*(md-md/i)%md;
		fac[i]=(ll)fac[i-1]*i%md;
		ifac[i]=(ll)ifac[i-1]*inv[i]%md;
	}
	rep(i,1,min(n,k)){
		xi=p2(color(n,i));
		rep(j,0,i)ans=(ans+C(k,j)*C(k-j,i-j)%md*C(k-i,i-j)%md*xi%md*power(j,(m-2)*n))%md;
	}
	cout<<(ans+md)%md;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# CF111D 题解

[$\text{Link}$](http://codeforces.com/problemset/problem/111/D)

## 思路分析

独立切的第一道 CF2300 的题，好耶

设 $\mathbf S_i$ 表示第 $i$ 列使用的颜色集合，$\mathbf L_i$ 表示第 $1$ 列到第 $i$ 列用的颜色集合，$\mathbf R_i$ 表示第 $i$ 列到第 $n$ 列用的颜色集合

考虑从 $\mathbf L_i$ 转移到 $\mathbf L_{i+1}$ 的过程，由定义我们知道 $\mathbf L_{i+1}=\mathbf L_{i}\cup\mathbf S_{i+1}$，所以我们可以得到 $\mathbf L_i\subseteq \mathbf L_{i+1}$，因此得到 $|\mathbf L_i|\le |\mathbf L_{i+1}|$，因此，$|\mathbf L_{1}|\sim|\mathbf L_m|$ 单调不降

同理，我们可以得到 $|\mathbf R_1|\sim|\mathbf R_m|$ 单调不升

但是，我们有 $|\mathbf L_1|=|\mathbf R_2|,|\mathbf L_2|=|\mathbf R_3|,\cdots,|\mathbf L_{m-1}|=|\mathbf R_m|$

所以 $|\mathbf R_2|=|\mathbf L_1|\leq |\mathbf L_2|=|\mathbf R_{3}|$，又 $|\mathbf R_3|\le|\mathbf R_2|$，所以得到 $|\mathbf R_2|=|\mathbf R_3|$

类推可知，$|\mathbf L_1|=|\mathbf L_2|=\cdots=|\mathbf L_{m-1}|=|\mathbf R_2|=|\mathbf R_3|=\cdots=|\mathbf R_m|$



考虑 $\mathbf S_1$ 和 $\mathbf S_2$ 的关系，由定义可得 $\mathbf S_1=\mathbf L_1,\mathbf S_1\cup\mathbf S_2=\mathbf L_2$，所以有 $\mathbf L_1\subseteq\mathbf L_{2}$，又因为 $|\mathbf L_1|=|\mathbf L_2|$，所以我们得到：$\mathbf L_1=\mathbf L_2$

所以有 $\mathbf S_1=\mathbf S_1\cup\mathbf S_2$ 因此 $\mathbf S_2\subseteq \mathbf S_1$

同理继续分析，考虑 $\mathbf L_2$ 和 $\mathbf L_3$ 的关系，注意到 $\mathbf L_2=\mathbf L_1=\mathbf S_1$，所以类似上面的过程，也能得到 $\mathbf S_3\subseteq\mathbf S_1$

类推到 $\mathbf S_4\sim\mathbf S_{m-1}$，都有这个性质，最终我们得到 $\mathbf S_2\sim\mathbf S_{m-1}\subseteq \mathbf S_1$

然后再看 $\mathbf R _m$ 和 $\mathbf R_{m-1}$ 的关系，观察到 $\mathbf R_m=\mathbf S_m$，然后用上面类似的方法同理可得：$\mathbf S_{2}\sim\mathbf S_{m-1}\subseteq \mathbf S_{m}$

联立上下，可知 $\mathbf S_2\sim\mathbf S_{m-1}\subseteq \mathbf S_1\cap\mathbf S_m$

又因为 $|\mathbf L_1|=|\mathbf R_m|$ 且 $\mathbf L_1=\mathbf S_1,\mathbf R_m=\mathbf S_m$，所以有 $|\mathbf S_1|=|\mathbf S_m|$



此时整理一下我们的得到的条件：

1. $|\mathbf S_1|=|\mathbf S_m|$
2. $\forall i\in(1,m),\mathbf S_i\in \mathbf S_1\cap\mathbf S_m$

 然后我们可以考虑进行计数，首先枚举 $|\mathbf S_1|,|\mathbf S_m|$，设为 $p$，然后枚举 $|\mathbf S_1\cap\mathbf S_m|$，设为 $i$，然后考虑分步计数：

1. 确定 $\mathbf S_1,\mathbf S_m$，首先求出 $\mathbf S_1\cap\mathbf S_m$，共有 $\dbinom ki$ 种情况，然后求出 $\mathbf S_1$ 的剩下部分，共有 $\dbinom{k-i}{p-i}$ 种情况，最后求出 $\mathbf S_m$ 的剩下部分，共有 $\dbinom {k-p}{p-i}$ 种情况，总数即三步情况数相乘，共有 $\dbinom ki\dbinom{k-i}{p-i}\dbinom{k-p}{p-i}$ 种

2. 求出中间 $m-2$ 列的**具体**涂色情况，每个格子都有 $i$ 种涂色方式，没有其它的限制，故情况数为 $i^{n(m-2)}$

3. 求出第 $1$ 列和第 $m$ 列的染色情况，不难发现这两列的染色情况数是相同的，且只与 $p$ 有关，即**恰好**使用 $p$ 种颜色染 $n$ 个格子的方案数，不妨记为 $f_n(p)$，显然，我们可以通过容斥原理计算 $f_n(p)$ 的值，考虑枚举强制让 $x$ 个格子不选，其余列无限制的方案数，显然就是 $(n-x)^p$ 种，然后做一次简单容斥可得：

$$
f_n(p)=\sum_{x=0}^n (-1)^x\dbinom p x(n-x)^p
$$

综上所述，我们得到：
$$
\text{Answer}=\sum_{p=1}^{\min(k,n)}\left[\sum_{x=0}^n (-1)^x\dbinom px(n-x)^p\right]^2\left[\sum_{i=0}^p \dbinom ki\dbinom{k-i}{p-i}\dbinom{k-p}{p-i}i^{n(m-2)}\right]
$$
直接计算，时间复杂度 $\Theta(n^2)$

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e6+1,MOD=1e9+7;
int inv[MAXN],fac[MAXN];
inline int ksm(int a,int b=MOD-2,int m=MOD) {
	int res=1;
	while(b) {
		if(b&1) res=res*a%m;
		a=a*a%m;
		b=b>>1;
	}
	return res;
}
inline void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<MAXN;++i) fac[i]=fac[i-1]*i%MOD;
	inv[MAXN-1]=ksm(fac[MAXN-1]);
	for(int i=MAXN-2;i>0;--i) inv[i]=inv[i+1]*(i+1)%MOD;
}
inline int C(int m,int n) {
	if(n<0||n>m) return 0;
	return fac[m]*inv[n]%MOD*inv[m-n]%MOD;
}
signed main() {
	init();
	int n,m,k,res=0;
	scanf("%lld%lld%lld",&n,&m,&k);
	if(m==1) {
		printf("%lld\n",ksm(k,n));
		return 0;
	}
	for(int p=1;p<=k&&p<=n;++p) {
		int f=0;
		for(int i=0,op=1;i<=p;++i,op*=-1) {
			f+=op*C(p,i)*ksm(p-i,n)%MOD;
			f=(f%MOD+MOD)%MOD;
		}
		for(int i=0;i<=p;++i) {
			int t=f*f%MOD;
			t=t*C(k,i)%MOD;
			t=t*C(k-i,p-i)%MOD;
			t=t*C(k-p,p-i)%MOD;
			t=t*ksm(i,n*(m-2))%MOD;
			res=(res+t)%MOD;
		}
	}
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：MCAdam (赞：1)

[题目](https://www.luogu.com.cn/problem/CF111D)

有一个很明显的性质：

假设左边$a$列和右边的$m-a$列颜色种类是相同的，那么当$a$往右移动一位时：左边的颜色集合不会减，右边的颜色集合不会加

如果左半部分的颜色集合有增加，那么说明$a+1$中存在前$a$列都没有的颜色，那么显然不符合一开始的假设。所以可以得到，这个边界线每次往右移动时，左边和右边的颜色集合都不会发生变化

换句话说：第$2$到第$m-1$列都应该是第$1$列和第$m$列颜色集合的子集，且中间这些集合都要相等；第$1$列和最后一列的颜色集合大小相等

那么就只需要计算第$1$列和第$m$列的方案数，中间的用组合数计算一下就行了

设$f[i][j]$表示前$i$个位置，有$j$种颜色的方案数

$f[i][j]=f[i-1][j]\times j+f[i-1][j-1]$

现在枚举第$1$列和最后一列的颜色数为$i$，中间列的颜色数为$j$，那么方案数就为：

$\displaystyle (f[n][i]\times i!)^2\times \binom{k}{i} \times \binom{k-j}{i-j}\times\binom{i}{j}\times j^{n(m-2)}$

首先选出$i$个颜色，然后要乘上$i!$是因为上面的DP所有的颜色都是等价的

然后$k$个颜色里选出$i$个作为第一列，$k-i$个中还要选取$i-j$个放到最后一列，中间放$j$个颜色

注意枚举$j$的下界为$0$，$j=0$只有在$m=2$时才是有意义的，这时候快速幂调用进去是求$0^0=1$；当$m\neq 2$时，快速幂会返回$0$。所以可以不用特判$m=2$的情况，但是需要特判$m=1$的情况

```cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int N=1e3+10,M=1e6;
const ll mod=1e9+7;
ll f[N][N],fac[M+10],inv[M+10];
inline ll power(ll a,ll b)
{
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1) res=res*a%mod;
	return res;
}
inline ll C(int x,int y)
{
	if(x<y) return 0;
	return fac[x]%mod*inv[y]%mod*inv[x-y]%mod;
}
int main()
{
	fac[0]=1; for(int i=1;i<=M;i++) fac[i]=fac[i-1]*i%mod;
	inv[M]=power(fac[M],mod-2); for(int i=M-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	int n,m,k; ll ans=0;
	scanf("%d%d%d",&n,&m,&k);
	if(m==1)
	{
		printf("%lld\n",power(k,n));
		return 0;
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			f[i][j]=(j*f[i-1][j]+f[i-1][j-1])%mod;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=i;j++)
		{
			ll col=f[n][i]*fac[i]%mod*f[n][i]%mod*fac[i]%mod;
			ll t=C(k,i)*C(k-i,i-j)%mod*C(i,j)%mod*power(j,n*(m-2))%mod;
			ans=(ans+col*t%mod)%mod;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：baka24 (赞：0)

先考虑 $m\ne 1$。

注意到分割线从左往右移动的过程中左边颜色数单调不降，右边颜色数单调不增，所以可以得到两边颜色数始终相等。

假设第 $i$ 列颜色集合为 $S_i$，该矩阵应当满足 $\bigcup_{1<i<m}S_i\in S_1\cap S_m$。

原因：

在分割线移动过程中左区间一定包含 $S_1$，右区间一定包含 $S_m$。

同时，考虑分割线在最左和最右的情况，可以得到 $|S_1|=|S_m|$。

那么对于中间的部分，它不能对区间的颜色数产生任何影响。也就是说，当第 $i$ 列在左时应有 $S_i\in S_1$，在右时应有 $S_i\in S_m$。

这相当于 $S_i\in S_1\cap S_m$。

考虑这个东西如何计数。

可以先枚举 $S_1,S_m$ 交集大小，设其为 $x$，则 $2\sim m-1$ 列的方案数即是 $\binom{k}{x}x^{n(m-2)}$。先选出用了哪些颜色，每个位置有 $x$ 种选择。

之后便要考虑 $S_1,S_m$ 非并集的部分，由于 $|S_1|=|S_m|$，所以可以枚举非交集部分 $y$，即 $x+y=|S_1|=|S_m|$。

那么方案数就是：
$$
\binom{k-x}{y}\binom{k-x-y}{y}({n\brace x+y}(x+y)!)^2
$$

原因：

首先我们选出 $S_1$ 剩下的部分：$\binom{k-x}{y}$，不能选之前选过的所以 $k$ 减去 $x$。

之后选出 $S_m$ 剩下的部分：$\binom{k-x-y}{y}$，同理，不能选选过的。

其中，${n\brace x+y}$ 为第二类斯特林数，表示 $n$ 个数分配到 $x+y$ 个非空集合的方案数。

此处，${n\brace x+y}(x+y)!$ 表示用选好的 $x+y$ 个颜色填进 $n$ 个格子的方案数。

先把每个格子分进 $x+y$ 个集合（斯特林数），再考虑集合的顺序（阶乘）。

这么算的原因是需要保证 $n$ 个格子一定出现了所有颜色，否则会算重。

斯特林数递推求法在后文。

综上，我们可以写出答案。

$$
\sum_{i=0}^{\min(n,k)}\binom{k}{i}i^{n(m-2)}\sum_{j=0}^{n-i}\binom{k-i}{j}\binom{k-i-j}{j}({n\brace i+j}(i+j)!)^2
$$

最后，还需要特判 $m=1$ 时的情况。

可以枚举其颜色数：
$$
\sum_{i=1}^{\min(n,k)}\binom{k}{i}{n\brace i}i!
$$

颜色方案数 $\binom{k}{i}$，填色方案数 ${n\brace i}i!$，原因与上文类似，不再赘述。

组合数和斯特林数都可以预处理，复杂度 $O(n^2)$。

关于第二类斯特林数 $O(n^2)$ 递推式：

$$
{n\brace m}={n-1\brace m-1}+{n-1\brace m}\times m
$$

考虑其组合意义：对于第 $n$ 个数，新开一个集合，或者放到一个已有的集合中。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0,f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}x=c-'0';c=getchar();while(c<='9'&&c>='0'){x*=10;x+=c-'0';c=getchar();}return x*f;}
const int MAXN=1010,N=30,MAXM=1000010,Mod=1000000007;
int Pow(int x,int y){int rt=1;while(y){if(y&1)rt=rt*x%Mod;x=x*x%Mod,y>>=1;}return rt;}
int n,m,k,ans,jc[MAXM],ny[MAXM],s[MAXN][MAXN];
int C(int x,int y){return jc[x]*ny[x-y]%Mod*ny[y]%Mod;}
void add(int &x,int y){x+=y;if(x>=Mod)x-=Mod;}
void slv(){
    n=read(),m=read(),k=read();
    if(m==1){
        for(int i=1;i<=min(k,n);i++)add(ans,C(k,i)*s[n][i]%Mod*jc[i]%Mod);
        printf("%lld",ans);
        return;
    }
    for(int i=0;i<=min(k,n);i++){
        int tmp=0;
        for(int j=0;j+i<=n&&j+j+i<=k;j++){
            add(tmp,
                C(k-i,j)*C(k-i-j,j)%Mod
                *s[n][i+j]%Mod*jc[i+j]%Mod
                *s[n][i+j]%Mod*jc[i+j]%Mod
            );
        }
        add(ans,tmp*C(k,i)%Mod*Pow(i,(m-2)*n)%Mod);
    }
    printf("%lld",ans);
}
signed main(){
 	freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    s[0][0]=jc[0]=ny[0]=1;
    for(int i=1;i<=MAXM-5;i++)jc[i]=jc[i-1]*i%Mod,ny[i]=Pow(jc[i],Mod-2);
    for(int i=1;i<=MAXN-5;i++){
        for(int j=1;j<=i;j++){
            s[i][j]=(s[i-1][j-1]+s[i-1][j]*j%Mod)%Mod;
        }
    }
    slv();
    return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

当竖直线从左往右移动的时候，左半部分的颜色数不降，右半部分的颜色数不升。而题目又说自始至终两边颜色数相等，故左边颜色数与右边颜色数始终不变。故中间 $m-2$ 列的颜色为第 $1$ 列与第 $m$ 列的颜色的子集，并且第 $1$ 列与第 $m$ 列颜色数相等。

首先枚举中间列的颜色数 $i$ ，则中间列的颜色集合有 $\binom{k}{i}$ 种，并且填充中间列的方案数有 $i^{n(m-2)}$ 种。

然后枚举两边的颜色种类数 $j$ 。由于中间列颜色集包含于两边的颜色集，故真正需要枚举的只是两列不同于中间列的其他颜色。先枚举两列不同部分的并，方案数为 $\binom{k}{2i-j}$，再枚举其中一列的不同部分，方案数为 $\binom{2i-j}{i-j}$。对于每一边的填充，我们可以先看作将每一格划分到 $j$ 个颜色集合中，然后枚举这些颜色的相对顺序，方案数为 ${n \brace j}j!$，两列的方案数为其平方。

综上，答案为 

$$\sum \limits_{i=1}^n \binom{k}{i} i^{n(m-2)} \sum \limits_{j=i}^n \binom{k}{2i-j} \binom{2i-j}{i-j} ({n \brace j}j!)^2$$

代码：


```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
#define int long long
 
constexpr int maxn=1000;
constexpr int maxk=1e6;
constexpr int mod=1e9+7;
 
int Mod(int x){
	while(x<0){
		x+=mod;
	}
	return x>=mod?x%mod:x;
}
 
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1){
			ans=Mod(ans*a);
		}
		a=Mod(a*a);
		b>>=1;
	}
	return ans;
}
 
int sterlin[maxn+5][maxn+5];
int frac[maxk+5];
int inv[maxk+5];
int n,m,k;
 
void init(){
	sterlin[0][0]=1;
	for(int j=1;j<=maxn;j++){
		for(int k=1;k<=j;k++){
			sterlin[j][k]=Mod(sterlin[j-1][k-1]+Mod(sterlin[j-1][k]*k));
		}
	}
	frac[0]=1;
	for(int i=1;i<=maxk;i++){
		frac[i]=Mod(frac[i-1]*i);
	}
	inv[maxk]=ksm(frac[maxk],mod-2);
	for(int i=maxk-1;i>=0;i--){
		inv[i]=Mod(inv[i+1]*(i+1));
	}
}
 
int binom(int n,int m){
	if(n<m){
		return 0;
	}
	return Mod(frac[n]*Mod(inv[m]*inv[n-m]));
}
 
int ping(int x){
	return Mod(x*x);
}
 
signed main(){
	init();
	cin>>n>>m>>k;
	if(m==1){
		cout<<ksm(k,n);
		return 0;
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		for(int j=i;j<=n;j++){
			int s1=Mod(binom(k,i)*Mod(binom(k-i,2*(j-i))*binom(2*(j-i),j-i)));
			int s2=ping(Mod(sterlin[n][j]*frac[j]));
			int s3=ksm(i,n*(m-2));
			ans=Mod(ans+Mod(s1*Mod(s2*s3)));
		}
	}
	cout<<ans;
}
```

---

## 作者：forgotmyhandle (赞：0)

[原题传送门](http://codeforces.com/problemset/problem/111/D)

[你谷传送门](https://www.luogu.com.cn/problem/CF111D)

## 分析
考虑将竖直线从左往右扫，发现左半部分的颜色种类数不减，而右半部分颜色种类数不增。于是如果要保证任意时刻两半颜色数量一样，则这个相等的颜色数量一定不变。考虑竖直线在 $1$、$2$ 列之间和在 $m - 1$、$m$ 列之间时，发现这两个时刻左半部分颜色数量相等，也就是 $2$ 到 $m - 1$ 列中的所有颜色都在第 $1$ 列中出现过。同理 $2$ 到 $m - 1$ 列中的颜色也都在第 $m$ 列出现过。也就是中间可以染的颜色集合一定是两边两列颜色集合之交的子集。其次两边两列的颜色种类数一定相同，因为他们都等于竖直线在 $m - 1$、$m$ 列之间时线左边的颜色种类数。

于是可以考虑枚举左右两列颜色的交集大小，然后枚举左右两列放多少种颜色。
先定义 $f[i][j]$ 表示在 $i$ 个位置上按顺序放 $j$ 种颜色的方案数，这个可以 $dp$。设当前交集大小为 $i$，左右两列放 $j$ 种颜色，则中间列的染色方案共有 $i^{n(m - 2)}$种。交集里有 $i$ 种颜色，于是有 $C_{k}^{i}$ 种选法。两边两列去掉交集后颜色互不相同，于是在剩下的颜色中选出 $2(j - i)$ 种，有 $C_{k - i}^{2(j - i)}$ 种选法。在 $2(j - i)$ 种颜色中选出 $j - i$ 种放在左 / 右边，有 $C_{2(j - i)}^{j - i}$ 种选法。于是 $C_{k}^{i}C_{k - i}^{2(j - i)}C_{2(j - i)}^{j - i}$ 即为 $j$ 种颜色之中恰好有 $i$ 种颜色相同的方案数。两边的 $j$ 种颜色分别有 $f[n][j] \times j!$ 种方案，于是合一起两边共有 $(f[n][j] \times j!) ^ 2$ 种方案。最终答案即为 $\sum_{i = 0}^{n}\sum_{j = i}^{n} (f[n][j] \times j!) ^ 2 \times C_k^iC_{k - i}^{2(j - i)}C_{2(j - i)}^{j - i} \times i^{n(m - 2)}$。

## 代码
```cpp
#include <iostream>
#define int long long
using namespace std;
const int p = 1e9 + 7;
int n, m, k;
int frac[1000005], inv[1000005], invf[1000005];
int C(int a, int b) { return a < b ? 0 : (frac[a] * invf[b] % p * invf[a - b]) % p; }
int f[1005][1005];
int qpow(int x, int y) {
    int ret = 1;
    while (y) {
        if (y & 1) 
            ret = ret * x % p;
        y >>= 1;
        x = x * x % p;
    }
    return ret;
}
signed main() {
    cin >> n >> m >> k;
    if (m == 1) {
        cout << qpow(k, n);
        return 0;
    }
    frac[1] = invf[1] = inv[1] = invf[0] = inv[0] = frac[0] = 1;
    for (int i = 2; i <= max(k, n << 1); i++) inv[i] = (p - p / i) * inv[p % i] % p;
    for (int i = 2; i <= max(k, n << 1); i++) frac[i] = frac[i - 1] * i % p, invf[i] = invf[i - 1] * inv[i] % p;
    int ans = 0;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(i, k); j++) 
            f[i][j] = (f[i - 1][j - 1] + f[i - 1][j] * j % p) % p;
    }
    for (int i = 0; i <= n; i++) {
        int t = qpow(i, n * (m - 2));
        for (int j = i; j <= n; j++) {
            ans = (ans + f[n][j] * frac[j] % p * f[n][j] % p * frac[j] % p * 
                t % p * C(k, i) % p * C(k - i, 2 * (j - i)) % p * C(2 * (j - i), j - i)) % p;
        }
    }
    cout << (ans % p + p) % p;
    return 0;
}
```

---

