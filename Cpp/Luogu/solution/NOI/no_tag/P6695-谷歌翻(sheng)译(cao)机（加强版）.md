# 谷歌翻(sheng)译(cao)机（加强版）

## 题目背景

本题由@[wolfind](https://www.luogu.com.cn/user/104593)提供。

[原题链接](https://www.luogu.com.cn/problem/P6693)（注意原题与加强版**有且仅有**`理解方式`中的**式子不同**、**模数不同**、**数据范围不同**）。

## 题目描述

**注：为了方便描述，下文所有字符串起始位置都为 $1$，即都从 $1$ 开始标号。**

小 L 将每次生草前的原文和生草后的结果看作两个**仅由小写字母组成**的两个字符串 $A$ 和 $B$。

我们按如下方式定义「分割数列」和「分割串」：

- 对于一个长度为 $n$ 的字符串，定义它的一条「分割数列」为：存在长度为 $k+2$ 的数列 $p$，使得 $0=p_0<p_1<p_2<...<p_k<p_{k+1}=n+1$。对于一条「分割数列」，定义其「分割串」为 $p_i+1$ 到 $p_{i+1}-1$ 之间字符构成的子串（$i \in[0,k]$）（可以为空串）。显然，对于一条长度为 $k+2$ 的分割数列，一共有 $k+1$ 个分割串。

- 对于同一个字符串，两条分割数列（$p$ 和 $q$）不同**当且仅当两条数列长度不同（$k_1\neq k_2$）**，或**存在 $i$ 使得 $p_i\neq q_i$**。

不同人对于同样的原文和结果，他们的理解方式都是不同的。我们按如下方式定义一种理解方式：

- 对于字符串 $A$ 和 $B$，我们为这两个字符串各找一条分割数列（$p$ 和 $q$），这两个分割数列满足以下要求：
1. 两个分割数列长度相等（$k_1=k_2$）。
1. 对于任意 $i$，有 $A[p_i]=B[q_i]$，即 **$A$ 第 $p_i$ 个位置的字符与 $B$ 第 $q_i$ 个位置的字符相同**。

- 定义这种理解方式的「生草程度」为**此时两个字符串的所有分割串长度的 $t$ 次方和**，即 $\sum\limits_{i=0}^{k_1}(p_{i+1}-p_i-1)^t+\sum\limits_{i=0}^{k_2}(q_{i+1}-q_i-1)^t$。

- 两种理解方式不同**当且仅当**两种理解方式的 $p$ 不同，或两种理解方式的 $q$ 不同。

小 L 想要知道所有理解方式的生草程度之和的结果。由于他（也）不喜欢 $998244353$ 这个数，他不希望你告诉他的结果会是这个数，所以你要将结果对 $998244353$ 取模。

## 说明/提示

对于样例一，一共有以下理解方式：
+ $p=\{0,4\},q=\{0,5\}$，生草程度为 $25$。
+ $p=\{0,1,4\},q=\{0,2,5\}$，生草程度为 $9$。
+ $p=\{0,2,4\},q=\{0,1,5\}$，生草程度为 $11$。
+ $p=\{0,2,4\},q=\{0,4,5\}$，生草程度为 $11$。
+ $p=\{0,3,4\},q=\{0,3,5\}$，生草程度为 $9$。
+ $p=\{0,1,2,4\},q=\{0,2,4,5\}$，生草程度为 $3$。
+ $p=\{0,1,3,4\},q=\{0,2,3,5\}$，生草程度为 $3$。
+ $p=\{0,2,3,4\},q=\{0,1,3,5\}$，生草程度为 $3$。

总生草程度为 $74$。

### 数据范围

「本题采用捆绑测试」

- Subtask 1( $20\%$ )：$n,m\leq 50,t\leq 2$。
- Subtask 2( $30\%$ )：$n,m\leq 200,t\leq 2$。
- Subtask 3( $20\%$ )：$t\leq 10$。
- Subtask 4( $30\%$ )：无特殊限制。

对于 $100\%$ 的数据，$n,m\leq 1000,t\leq 1000000$，$A$ 和 $B$ **仅包含小写字母**。

## 样例 #1

### 输入

```
3 4 2
abc
bacb
```

### 输出

```
74```

## 样例 #2

### 输入

```
7 8 5
ccbbacb
bbbdadba```

### 输出

```
337322```

## 样例 #3

### 输入

```
3 4 1000000
abc
bacb
```

### 输出

```
424285944```

# 题解

## 作者：littleKtian (赞：29)

以下题解内容由@[w6666](https://www.luogu.com.cn/user/104593)提供，~~因为他懒得开博客所以~~就被放在我的博客里了

------------


记$f[i][j]$表示在$A$的前$i$个与$B$的前$j$个中有多少相同的子序列（包含空串）


$g[i][j]$表示在$A$的后$i$个与$B$的后$j$个中有多少相同的子序列（同上）

考虑$A$中的区间$[i,k]$在所有分割串的方案中出现的次数。

那就需要在$A$中的子序列$P$跨过$[i,k]$这个区间，必须要有$i-1$和$k+1$这两个位置，且其他的位置在$[1,i-2]$或$[k+2,n]$之间。

枚举在$B$中与$P$匹配的子序列$Q$，设$P$的$i-1$这个位置与$Q$在$j$匹配，

那就有式子$f[i-2][j-1]\times(g[k+1][j+1]-g[k+2][j+1])$，且$A[i-1]=B[j]$。

故在$A$中总答案就是$\sum\limits^{n}_ {i=1} \sum\limits^{n}_ {k=i} \sum\limits^{m+1}_ {A[i-1]=B[j]}f[i-2][j-1]\times(g[k+1][j+1]-g[k+2][j+1])\times(k-i+1)^t$

时间复杂度$O(n^3)$。

设$j$是固定的，构造多项式$G[x]=g[x+1][j+1]-g[x+2][j+1]$，
$V[x]=x^t$


原式变为$\sum\limits^{m+1}_ {j=0}\sum\limits_ {A[i-1]=B[j]} f[i-2][j-1] \sum\limits^{n}_ {k=i}  G[k]\times V[k-i+1]$

只要把$G$翻转然后用$NTT$把$G$和$V$做卷积，对于每个$i$取卷积后的第$n-i+1$项系数即可。

时间复杂度$O(n^2logn)$。~~应该不卡常吧，std开O2跑500ms~~

（std中枚举的是区间$[i+1,k]$，会有所不同）
```cpp
#include<bits/stdc++.h>
#define N 1010
#define MOD 998244353
#define ll long long
using namespace std;
int n,m,t,ans;
int a[N<<2],v[N<<2],f[N][N],g[N][N];
//v[i]=i^t
//f[i][j]表示前(i,j)里相同子序列的方案数
//g[i][j]表示后(i,j)里相同子序列的方案数
char s1[N],s2[N];
//视s1[0]=s2[0],s1[n+1]=s2[m+1]
int rev[N<<2];
int len,bit;
//ntt用 
inline int ksm(int x,int k)
{
	int res=1;
	while(k)
	{
		if(k&1)res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;
		k>>=1; 
	}
	return res;
}
inline int qm(ll x)
{
	return (x%MOD+MOD)%MOD;
}
inline void ntt(int len,int a[],int inv)
{
	for(int i=1;i<len;i++)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for(int i=1;i<len;i<<=1)
	{
		int gi,up=i<<1;
		if(inv==1)gi=ksm(3ll,(MOD-1)/up);
		else gi=ksm(1ll*(MOD+1)/3,(MOD-1)/up);
		for(int j=0;j<len;j+=up)
		{
			int gx=1;
			for(int k=0;k<i;k++)
			{
				int x=a[j+k],y=1ll*gx*a[i+j+k]%MOD;
				a[j+k]=qm(x+y),a[i+j+k]=qm(x-y);
				gx=1ll*gx*gi%MOD;
			}
		}
	}
	if(inv==-1)
	{
		int invx=ksm(len,MOD-2);
		for(int i=0;i<len;i++)
			a[i]=1ll*a[i]*invx%MOD;
	}
}
inline void getmul(int lenx,int a[])
{
	ntt(len,a,1);
	for(int i=0;i<len;i++)
		a[i]=1ll*a[i]*v[i]%MOD;
	ntt(len,a,-1);
	for(int i=lenx;i<len;i++)
		a[i]=0;
}
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	scanf("%s",s1);
	scanf("%s",s2);
	for(int i=n;i>=1;i--)s1[i]=s1[i-1];
	for(int i=m;i>=1;i--)s2[i]=s2[i-1];
	for(int i=max(n,m);i>=1;i--)
		v[i]=ksm(i,t);
	len=1,bit=-1;
	while(len<2*max(n,m)+1)len<<=1,++bit;
	for(int i=1;i<len;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<bit);
	ntt(len,v,1);//因为都是与V做卷积，直接预处理 ,当然不这样也能过
	s1[0]=s2[0]=' ';
	for(int i=0;i<=n;i++)f[i][0]=1;
	for(int i=0;i<=m;i++)f[0][i]=1;
	for(int i=1;i<=n+1;i++)g[i][m+1]=1;
	for(int i=1;i<=m+1;i++)g[n+1][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			f[i][j]=qm(f[i-1][j]+f[i][j-1]-f[i-1][j-1]);
			if(s1[i]==s2[j])
				f[i][j]=qm(f[i][j]+f[i-1][j-1]);
		}
	for(int i=n;i>=1;i--)
		for(int j=m;j>=1;j--)
		{
			g[i][j]=qm(g[i+1][j]+g[i][j+1]-g[i+1][j+1]);
			if(s1[i]==s2[j])
				g[i][j]=qm(g[i][j]+g[i+1][j+1]);
		}
	//计算A中答案 
	for(int j=1;j<=m;j++)
	{
		a[n]=0;
		for(int k=1;k<=n;k++)
			a[n-k]=qm(g[k+1][j+1]-g[k+2][j+1]);//构造多项式 
		getmul(n,a);//计算卷积 
		for(int i=1;i<=n;i++)
			if(s1[i]==s2[j])//此处枚举的是区间[i+1,k] 
				ans=qm(ans+1ll*a[n-i]*f[i-1][j-1]%MOD);
	}
	for(int i=1;i<=n;i++)a[i]=0;
	//计算B中答案 
	for(int i=1;i<=n;i++)
	{
		a[m]=0;
		for(int k=1;k<=m;k++)
			a[m-k]=qm(g[i+1][k+1]-g[i+1][k+2]);
		getmul(m,a);
		for(int j=1;j<=m;j++)
			if(s1[i]==s2[j])
				ans=qm(ans+1ll*a[m-j]*f[i-1][j-1]%MOD);
	}
	for(int i=max(n,m);i>=1;i--)
		v[i]=ksm(i,t);
	for(int k=1;k<=n;k++)
		ans=qm(ans+1ll*qm(1ll*qm(g[k+1][1]-g[k+2][1])*v[k]%MOD));//f[-1][j-1]特殊处理 
	for(int k=1;k<=m;k++)
		ans=qm(ans+1ll*qm(1ll*qm(g[1][k+1]-g[1][k+2])*v[k]%MOD));
	printf("%d",ans);
}
```

---

