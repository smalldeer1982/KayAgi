# Iahub and Permutations

## 题目描述

Iahub is so happy about inventing bubble sort graphs that he's staying all day long at the office and writing permutations. Iahubina is angry that she is no more important for Iahub. When Iahub goes away, Iahubina comes to his office and sabotage his research work.

The girl finds an important permutation for the research. The permutation contains $ n $ distinct integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ $ (1<=a_{i}<=n) $ . She replaces some of permutation elements with -1 value as a revenge.

When Iahub finds out his important permutation is broken, he tries to recover it. The only thing he remembers about the permutation is it didn't have any fixed point. A fixed point for a permutation is an element $ a_{k} $ which has value equal to $ k $ $ (a_{k}=k) $ . Your job is to proof to Iahub that trying to recover it is not a good idea. Output the number of permutations which could be originally Iahub's important permutation, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

For the first test example there are two permutations with no fixed points are \[2, 5, 4, 3, 1\] and \[5, 1, 4, 3, 2\]. Any other permutation would have at least one fixed point.

## 样例 #1

### 输入

```
5
-1 -1 4 3 -1
```

### 输出

```
2
```

# 题解

## 作者：Narcissusany (赞：20)

orz 一个十分巧妙的转化，大概就是对于这种带有**放置限制**的排列问题，比如某个下标不能放置某个数，那么可以将这个排列对应到一个 $n$ 阶摆 $rook$ （即 $n\times n$ 的棋盘上放 $n$ 个互不攻击的车）问题上。这样一方面可以把「位置 x 不能放 y」约束展开，抽象成一个二维约束点 $(x,y)$ 上不能放车的约束；另一方面可以知道这个对应一定是完备的。

那么就转化成了，有些行和列已经放了车，整个棋盘对角线不能放车，有多少种本质不同的放车方案数。首先可以发现，如果某行某列有车，这一行一列就可以删掉；同时如果对于某个 $-1$ ，他所在的这个位置对应的行/列恰好被删了（同时存在位于下标 $k$ 的 $-1$ 和一个 $pos$ 使得 $a_{pos}=k$ ），那么对于这个 $-1$ 而言就没有限制了。

这样考虑 $dp$ 。$f_{i,j}$ 表示 $i\times i$ 的方格里考虑 $j$ 个限制的方案数。那么 $f_{i,0}=i!$。同时注意到 $f_{i,j-1}$ 到 $f_{i,j}$ 恰好多了一个限制，这个限制对应的应该是 $f_{i-1,j-1}$ 的方案数。所以有转移

$$f_{i,j}=f_{i,j-1}-f_{i-1,j-1}$$

复杂度 $n^2$ 。



---

## 作者：FFTotoro (赞：12)

## 前言

Update：将写错的字母更改了一下。

偶然翻到一个 CF 远古题，看起来不错的样子，花了 $3\operatorname{min}$ 写掉了。

翻了翻题解区，清一色的 DP，跟我一样用数论的寥寥无几。

## 解法

本做法需要使用容斥原理和基本数论。

考虑如果没有 $a_i\ne i$ 的时候有多少种方法。显然地，设已经填好的数有 $c$ 个，那么剩下的数可以看成一个全排列，答案为 $(n-c)!$。

我们发现如果直接判断合法的状态有多少种有些麻烦。正难则反，想想什么时候答案是**不合法**的。

假设先固定一个数在不合法的位置上，那么不管怎么放最终都是不合法的，剩下的数一共有 $(n-c-1)!$ 种排法。

那如果两个数**同时固定在不合法的位置上**呢？利用上面的算法直接进行计算，会有重复计算的情况发生。这个时候就需要使用**容斥原理**，按照容斥原理的基本公式，设**可能出现在不合法位置上的数的数量** $^{(1}$ 为 $s$，最终不合法的情况总数即为：

$$\sum\limits_{i=1}^{s}(-1)^iC_{s}^{i}(n-c-i)!$$

当然，最终我们要求得的是合法的方案数量，用 $(n-c)!$ 减去上面的式子的值即可。细心的人可以发现，在上面的式子中如果 $i=0$，那么 $\sum$ 后面那串东西的值就为 $(n-c)!$。所以，直接把 $i\in[1,s]$ 改为 $i\in[0,s]$ 即可。

$^{(1}$：“可能出现在不合法位置上的数”指满足如下条件的数：

- 这个数未在原数列中出现；

- 原数列中以这个数为下标的数是 $-1$，即这个数是待填入的；

可以证明，满足上述两个条件的数是有可能在最终不合法的方案中出现在不合法的位置上。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int a[2001],f[2001]={1,1};
int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)r=r%mod*a%mod;
    a=a%mod*a%mod; b>>=1;
  }
  return r;
}
int inv(int a,int b){return a*qpow(b,mod-2)%mod;}
int com(int n,int m){return inv(f[n],f[n-m]*f[m]%mod);}
// 经典三件套：快速幂、逆元和组合数
main(){
  ios::sync_with_stdio(false);
  int n,c=0,s=0,r=0; cin>>n;
  for(int i=2;i<=n;i++)f[i]=f[i-1]*i%mod; // 阶乘预处理
  map<int,bool> m,p;
  for(int i=1;i<=n;i++){
    if(cin>>a[i];a[i]==i){cout<<"0\n"; return 0;}
    // 特判无解，如果原来的排列就起了冲突，那么最终一定无解
    if(a[i]==-1)p[i]=true;
    else m[a[i]]=true,c++;
  }
  for(int i=1;i<=n;i++)s+=(!m[i]&&p[i]); // 统计位置可能不合法的数的数量
  for(int i=0;i<=s;i++) // 计算求和式
    if(i&1)r=(r-com(s,i)*f[n-c-i]%mod+mod)%mod;
    else r=(r+com(s,i)*f[n-c-i]%mod)%mod;
  cout<<r<<endl;
  return 0;
}
```

---

## 作者：alskdjfhgzmxncbv (赞：8)

### 除了DP的方法外，本题还可以使用容斥原理来做
（什么？你不知道什么是[容斥原理](https://baike.baidu.com/item/容斥原理/10146840)？）

我们来分析一下问题。

#### 先不考虑那个a[k]!=k的条件

一个排列缺少了一部分，如果要填回这些部分，那么我们填回的这些部分的方案数，就是缺失的部分的元素个数的全排列个数。

#### 考虑这个条件呢？

正难则反，我们先考虑不合法的情况，然后再减去就好啦

先考虑有一个元素k满足a[k]==k的排列，其他的元素咱们先不管是不是合法。这就相当于先固定了这一个位置上的数，剩下的缺失元素做全排列。好了，我们找出来一些不合法的解，减去它们。

然而有些排列在这一步被计算了两遍三遍甚至四遍五遍一百遍怎么办呢？

好，那我们考虑有两个元素i，j满足a[i]==1,且a[j]==j的排列。同样，其他的不管。这就是相当于固定了这两个元素，剩下的做全排列。由于我们分别考虑一个元素i和一个元素j的时候一定考虑过了这种情况，那就再加回来。

同样的，我们再考虑三个元素四个元素……好多好多元素不合法的情况，再分别做一些加减工作求出所有不合法排列的个数。诶？这不就是容斥原理计算的过程么……

那我们如果把某一个元素a[i]不合法的情况的排列的集合记为S[ei],现在的问题就是要求所有S[ei]的并集的元素个数啦。

#### 公式来啦

（一些约定：使用符号C（m,n）表示从n个元素中选择m个元素的组合数，A（m,n）表示从n个元素中选择m个元素的排列数，sigma（i，m，n）f（i）表示从m开始到n的所有整数i的f（i）求和）

我们设原排列有p个元素缺失，有q个缺失的元素填回去后有可能满足a[k]==k的非法条件，即记q为原序列中a[k]==-1,且k未出现在给出序列中的元素个数。

那对于这q个集合选取集合计算时，若选取了i个元素，则选取集合方式就有
C（i，q）种，剩余（p-i）个元素做全排列，即每种方式下有A（p-i，p-i）个全排列。

由于我们计算的是反面，所以要从全部里减去。因此计算选取i个元素时就要在答案里加上（-1）^i \* C（i,q）\* A(p-i,p-i)，那么总的答案就是

A（p，p）+sigma（i，1，q）（（-1）^i \* C（i,q）\* A(p-i,p-i)）

##### 这样我们就省去了DP的过程把题目转化成了好想好写的容斥原理啦

#### 小Tips

要开long long,并且在mod 1e9+7下ans可能会输出负，这时要调整成正的。

##### 附上代码一份：（代码渣，dalao见谅）

```cpp
#include<iostream>
#define ll long long
using namespace std;
ll M=1000000007;//模数
ll fac[2010];//阶乘
ll facinv[2010];//阶乘逆元
ll ext[2010];//某元素是否已经在排列中
ll a[2010];//排列
ll num,cnt;//分别记录缺失元素个数和可能有a[i]==i的元素个数
ll qpow(ll d,ll p)//快速幂
{
	ll ret=1;
	while(p)
	{
		if(p%2) ret=(ret*d)%M;
		d=(d*d)%M;
		p/=2;
	}
	return ret;
}
int main()
{
	ll n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==-1) num++;
		else ext[a[i]]=1;
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==-1&&!(ext[i]))
			cnt++;
	}
	fac[0]=1;
	for(int i=1;i<=num;i++)//求阶乘
	{
		fac[i]=(fac[i-1]*i)%M;
	}
	facinv[num]=qpow(fac[num],M-2);
	for(int i=num-1;i;i--)//求逆元
	{
		facinv[i]=facinv[i+1]*(i+1)%M;
	}
	facinv[0]=1;
	ll ans=fac[num];
	for(int i=1;i<=cnt;i++)//计算答案
	{
		ans+=((((qpow(-1,i%2)*fac[cnt])%M)*facinv[cnt-i]%M)*facinv[i]%M)*fac[num-i]%M;
	}
	while(ans<0)//调整
	{
		ans+=M;
	}
	cout<<ans%M;
	return 0;
}
```

---

## 作者：Milmon (赞：4)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF340E) & [Problem](//www.luogu.com.cn/problem/CF340E)

## 题目大意

- 给定一个长度为 $n$ 的序列 $a$，求将序列中所有的 $-1$ 替换成一个正整数使得 $\{a_1,\ a_2,\ \cdots,\ a_n\}=\{1,\ 2,\ \cdots,\ n\}$ 且 $\forall\ 1\leq i\leq n,\ a_i\not=i$ 的方案数目模 $10^9+7$。

- $2\leq n\leq 2\times 10^3$

![](https://cdn.luogu.com.cn/upload/image_hosting/578g6dmu.png)

## 分析

显然当 $\exists\ a_i=i$ 时，答案为 $0$。

将 $a_i=-1$ 的位置 $i$ 分为两类：

- 第一类，$\forall\ a_j\not=i$，即 $i$ 这个数的位置还未确定，则该位置只能放除了 $i$ 以外的数；

- 第二类，$\exists\ a_j=i$，即 $i$ 这个数的位置已经确定，则该位置放的数不受限制。

设第一类的位置有 $tot_1$ 个，第二类的位置有 $tot_2$ 个。问题转化为有 $tot_1$ 个位置只能放除了 $i$ 以外的数，有 $tot_2$ 个位置放的数不受限制，求方法数。

## 解法 1

容斥原理。

考虑满足 $a_i=i$ 的位置 $i$ 的个数，下面研究至少有 $k
$ 个位置满足 $a_i=i$ 的方法数。

从只能放除了本身以外的数的 $tot_1$ 个位置中，选出 $k$ 个放本身值，有 $C_{tot_1}^k$ 种情形。剩余 $tot_1+tot_2-i$ 个位置任意放，有 $\left(tot_1+tot_2-k\right)!$ 种情形。由乘法原理，方法数为

$$\binom{tot_1}k\cdot\left(tot_1+tot_2-k\right)!.$$

由容斥原理，最终方法数为

$$\sum_{i=0}^{tot_1}\binom{tot_1}i\cdot\left(tot_1+tot_2-i\right)!\cdot\left(-1\right)^i.$$

预处理组合数时间复杂度 $\Theta(n^2)$，预处理阶乘时间复杂度 $\Theta(n)$，计算时间复杂度 $\Theta(n)$，最终时间复杂度 $\Theta(n^2)$。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
int n,a[2001],tot1,tot2;
//tot1: 不能放自身的位置个数 
//tot2: 可以随便放的位置个数 
long long answer;
bool p[2001];

long long fac[2001],C[2001][2001];
void initfac(int N){
	fac[0]=1;
	for(int i=1;i<=N;i++)
		fac[i]=fac[i-1]*i%mod;
}
void initC(int N){
	for(int i=0;i<=N;i++)
		C[i][0]=1;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		if(a[i]==i){
			printf("0\n");
			return 0;
		}
		if(a[i]!=-1)p[a[i]]=true;
		else tot1++;
	}
	initfac(tot1);
	for(int i=1;i<=n;i++)
		if(a[i]==-1&&p[i])tot1--,tot2++;
	initC(tot1);
	for(int i=0;i<=tot1;i++){
		int t=(i&1)?-1:1;
		answer+=fac[tot1+tot2-i]*C[tot1][i]%mod*t;
		answer=(answer+mod)%mod;
	}
	printf("%lld\n",answer);
    return 0;
}
```

## 解法 2

二维动态规划。

设状态 $dp_{i,\ j}$ 表示有 $i$ 个位置只能放除了本身以外的数，有 $j$ 个位置放的数不受限制时的方法数。则答案为 $dp_{tot_1,\ tot_2}$。

显然有边界 $dp_{0,\ j}=j!$，下面讨论边界 $dp_{i,\ 0}$。

位置 $i$ 只能放 $1\sim i-1$ 的数，有 $i-1$ 种可能。不妨设位置 $i$ 放的是 $x$。

- 位置 $x$ 放的是 $i$。此时有 $dp_{i-2,\ 0}$ 种情况；
- 位置 $x$ 放的不是 $i$。此时等价于 $dp_{i-1,\ 0}$ 的情况。

综上所述，$dp_{i,\ 0}=(i-1)\left(dp_{i-1,\ 0}+dp_{i-2,\ 0}\right)$。

讨论 $dp_{i,\ j}$（$i,\ j\geq 1$）。任取一放的数不受限制的位置。

- 若放的是这 $i$ 个数中的数，有 $dp_{i-1,\ j}$ 种情况，共有 $i\cdot dp_{i-1,\ j}$ 种情况；

- 若放的是这 $j$ 个数中的数，有 $dp_{i,\ j-1}$ 种情况，共有 $j\cdot dp_{i,\ j-1}$ 种情况；

综上所述，$dp_{i,\ j}=i\cdot dp_{i-1,\ j}+j\cdot dp_{i,\ j-1}$。

时间复杂度 $\Theta(n^2)$。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
int n,a[2001],tot1,tot2;
//tot1: 不能放自身的位置个数 
//tot2: 可以随便放的位置个数 
long long dp[2001][2001];
//dp[i][j]: 有 i 个位置不能放自身，j 个位置可以随便放 
bool p[2001];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		if(a[i]==i){
			printf("0\n");
			return 0;
		}
		if(a[i]!=-1)p[a[i]]=true;
		else tot1++;
	}
	for(int i=1;i<=n;i++)
		if(a[i]==-1&&p[i])tot1--,tot2++;
	dp[0][0]=1;
	for(int i=2;i<=tot1;i++)
		dp[i][0]=(dp[i-1][0]+dp[i-2][0])%mod*(i-1)%mod;
	for(int j=1;j<=tot2;j++)
		dp[0][j]=dp[0][j-1]*j%mod;
	for(int i=1;i<=tot1;i++)
		for(int j=1;j<=tot2;j++)
			dp[i][j]=(i*dp[i-1][j]%mod+j*dp[i][j-1]%mod)%mod;
	printf("%d\n",dp[tot1][tot2]);
    return 0;
}
```

## 解法 3

动态规划。

设状态 $dp_i$ 表示有 $i$ 个位置只能放除了本身以外的数，有 $tot_2$ 个位置放的数不受限制时的方法数。则答案为 $dp_{tot_1}$。

显然有边界 $dp_0=tot_2!$，下面讨论 $dp_i$（$i\geq 1$）。

- 若 $i$ 这个数放的是不受限制的 $tot_2$ 个位置中的一个，有 $tot_2dp_{i-1}$ 种情况；

- 其余情况类似「解法 2」中错位排列的求法，有 $(i-1)(dp_{i-1}+dp_{i-2})$ 中情况。

综上所述，$dp_i=tot_2dp_{i-1}+(i-1)(dp_{i-1}+dp_{i-2})$。

注意 $i=1$ 时，$dp_{i-2}$ 会发生数组越界，需要特殊处理。

时间复杂度 $\Theta(n)$。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
int n,a[2001],tot1,tot2;
//tot1: 不能放自身的位置个数 
//tot2: 可以随便放的位置个数 
long long answer;
bool p[2001];
long long dp[2001]={1};

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		if(a[i]==i){
			printf("0\n");
			return 0;
		}
		if(a[i]!=-1)p[a[i]]=true;
		else tot1++;
	}
	for(int i=1;i<=n;i++)
		if(a[i]==-1&&p[i])tot1--,tot2++;
	for(int i=1;i<=tot2;i++)dp[0]=dp[0]*i%mod; 
	dp[1]=tot2*dp[0]%mod;
	for(int i=2;i<=tot1;i++){
		dp[i]=(dp[i-1]+dp[i-2])%mod*(i-1)%mod;
		dp[i]=(dp[i]+tot2*dp[i-1]%mod)%mod;
	}
	printf("%lld\n",dp[tot1]);
    return 0;
}
```

---

## 作者：Karry5307 (赞：3)

### 题意

给定一个长度为 $n$ 的序列，求有多少种方案将 $-1$ 替换为 $1\sim n$ 的整数使得这个序列是个错排。

$\texttt{Data Range:}1\leq n\leq 2000$

### 题解

简单 DP，由于数据范围比较小我就 $O(n^2)$ 艹过去了。

对于序列中的每个为 $-1$ 位置，考虑这个位置是不是可以填可填数集合中所有数的。比如序列 $(-1,-1,4,5,-1)$ 中，可填数集合为 $\{1,2,3\}$。所以，前两个位置是不能填自身的，最后一个位置就可以填所有数。

所以很显然可以设 $f_{i,j}$ 表示有 $i$ 个位置可以填任何数，$j$ 个位置不能填自身，考虑一个可填任何数的位置，很显然有

$$f_{i,j}=if_{i-1,j}+jf_{i,j-1}$$

其中，$f_{i,0}=i!,f_{0,i}=D_i$。

然后 $O(n)$ 数出有多少个位置可以填任何数和有多少个位置不能填自身即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e3+51,MOD=1e9+7;
ll n,u,v;
ll x[MAXN],mp[MAXN],f[MAXN][MAXN];
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
int main()
{
	n=read(),f[0][0]=1;
	for(register int i=1;i<=n;i++)
	{
		x[i]=read(),f[i][0]=(li)f[i-1][0]*i%MOD;
		x[i]!=-1?mp[x[i]]=1:1;
	}
	for(register int i=2;i<=n;i++)
	{
		f[0][i]=((li)i*f[0][i-1]+(i&1?MOD-1:1))%MOD;
	}
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			f[i][j]=((li)i*f[i-1][j]+(li)j*f[i][j-1])%MOD;
		}
	}
	for(register int i=1;i<=n;i++)
	{
		x[i]==-1?mp[i]?u++:v++:1;
	}
	printf("%d",f[u][v]);
}
```

---

## 作者：fisheep (赞：3)

## 前言：
首先这道题我觉得用组合数加逆元有亿点麻烦。

然后看到标签有$dp$然后就尝试一下，借鉴了一些大佬的思想，然后就很轻松的过了这道题。

## 想法：
我们可以把数分为两类：

* 第一类是$a[i]=-1$ 且$i$其他位置没有出现过。

* 第二类是$a[i]=-1$且$i$在其他位置出现过。

对于第二种位置就相当于随便放，对于第一种位置就相当于错排。我们设$x$为第二类位置的个数，$y$为第一类位置的个数。

首先考虑错排：

设$dp[i]$为前$i$个数字的错排方案，当然不能放在$i$号位。则在前$i-1$个数中选择一个数$k$，有两种方案。

* 第一种是$i$与$k$调换，相当于对剩下$i-2$个数错排，即方案数为$dp[i-2]$；

* 第二种是$k$放在不在$k$的任意位置，即$dp[i-1]$种方案。

所以我们就可以得到转移方程：

$dp[i]=(i-1)* (dp[i-1]+dp[i-2])$

## Code:
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
const int maxn=2008,mod=1e9+7;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

int n,x,y;
int a[maxn],dp[maxn];
signed main(){
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) {
        if(a[i]!=-1){
            if(a[a[i]]==-1) x++;
        }
        else y++;
    }
    y-=x;
    dp[0]=1;
    for(int i=2;i<=x;i++){
        dp[0]=(dp[0]*i)%mod;
    }
    for(int i=1;i<=y;i++){
        dp[i]=(dp[i]+(i-1)*dp[i-1]%mod)%mod;
        if(i>=2) dp[i]=(dp[i]+(i-1)*dp[i-2]%mod)%mod;
        dp[i]=(dp[i]+x*dp[i-1]%mod)%mod;
    }
    printf("%lld",dp[y]);
}

```

---

## 作者：inexistent (赞：2)

**详见我的[博客](https://www.cnblogs.com/qixingzhi/p/9317339.html)**

题意：

有一个长度为$n$的排列（即各元素互不相同），其中有一些为-1。现要求将数填到这些-1上，使得原排列是一个错位排列。问有几种方法？

思路分析：

　　又是一道超级难的DP……

　　这不就是一个错排的模板题吗？不是只要看有几个-1就做多少的错排吗？确实，样例很不良心，那就给你一组反例吧……

　　5

　　-1 -1 2 3 -1

　　我们注意到了，并不是剩下的元素全是错排。因为原来我们认为2不能处在2的位置，但是4作为第二个元素是可以处在2的位置的。这样一来……就错得很离谱了。

　　但是这道题跟错排的关系依然是很大的。如果还不了解错排，可以参见我的另一篇博客「错位排列及有关例题」

 

　　 我们首先可以根据数字是否为-1，以及数字i是否被使用过，把给的数字$a[i]$分成几类：

　　　第一类，$a[i] = -1$ 且 数字$i$还没有被使用过（即数字$i$没有出现在给定的序列中），那么这个位置除了其位置本身对应的数字$i$以外，其他剩余的数字都可以填进来。

　　　第二类，$a[i] = -1$ 且 数字$i$已经被使用过了，那么任何剩余的数字都可以填进来而且不会影响错位排列，想填什么就填什么。

　　　第三类，$a[i] ≠ -1$ 且 数字$i$还没有被使用过，这种数字的个数应该和第一类相同，都是有限制的随便填。
   
　　　第四类，$a[i] ≠ -1$ 且 数字$i$已经被使用过了，这种东西用都没有，就当他们是垃圾就好了。

　　首先我们可以统计出一类（或三类）数字的出现次数$y$，以及二类数字的出现次数$x$。我们只考虑二类数字可能组成的方案数，将有$x$个数字填到$x$个无限制的位置中，方案数就是$P_x^x$。

　　下面正式开始DP。令$f[i]$表示加入$i$个一类数字后的方案数。因此很容易得到$f[0] = P_x^x，即 x!$

　　下面开始状态转移。对于第$i$个一类数字，我们可以把他填入到无限制的二类数字的位置中，方案数是$x * f[i-1]$。剩余的就直接做错位排列即可。

代码注意点：

　　随手MOD

---

## 作者：ncwzdlsd (赞：1)

前置芝士：错位排列

考虑 DP。

我们分析可得一共有 $4$ 种情况：

1. $a_i=-1$ 且 $i$ 出现过

2. $a_i=-1$ 且 $i$ 未出现过

3. $a_i\neq-1$ 且 $i$ 出现过

4. $a_i\neq-1$ 且 $i$ 未出现过

统计情况 $1$ 的数量 $p_1$ 和情况 $2$ 的数量 $p_2$。

对于当前考虑到的位置 $i$，如果是情况 $1$ 或 $3$ 的情况，此时没有任何限制，只要不是它自己就可以随便填，相当于把问题转化为错排列。如果是情况 $4$，由于对方案数不会产生影响，所以可以先暂不考虑。对于情况 $2$，此时无任何限制，相当于把问题转化为全排列。

我们设计状态 $f_i$ 表示对于已经考虑到第 $i$ 个 $1$ 类数的方案数，初始化显然 $f_0=A_{p_2}^{p_2}=x!$。

对于考虑到的第 $i$ 个位置，如果将其按照情况 $2$ 考虑，方案数为 $p_2\times f_{i-1}$，对于剩下的的情况，按照错排列考虑即可。

由此得到状态转移方程：

$$
f_i=p_2\times f_{i-1}+(i-1)\times f_{i-1}
$$

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=2005,mod=1e9+7;
int f[maxn],a[maxn];
bool flag[maxn];

signed main()
{
	int n;cin>>n;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i];
		if(a[i]!=-1) flag[a[i]]=1;
	}
	int p1=0,p2=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]==-1&&!flag[i]) p1++;
		if(a[i]==-1&&flag[i]) p2++;
	}
	f[0]=1;
	for(int i=1;i<=p2;i++) f[0]=f[0]*i%mod;
	for(int i=1;i<=p1;i++)
		f[i]=(p2*f[i-1]+(i-1)*f[i-1])%mod,f[i]=(f[i]+(i-1)*f[i-2])%mod;
	cout<<f[p1];
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

## 思路

首先，我们考虑原序列中为 $-1$ 的且 $a_i$ 对应的 $i$ 已经被填入的 $a_i$ 占用的位置。因为这些位置不论随便填什么数，都无法满足 $a_i=i$。

此时，我们考虑到直接计算不好算，可以固定至少 $1\sim n$ 个数必须要满足 $a_i=i$，其他随意。这样我们就可以非常容易地计算出来至少有 $i$ 个 $a_i=i$ 的方案数。这时，我们可以使用容斥来计算即可。假设 $-1$ 有 $x$ 个。其中为 $-1$ 的且 $a_i$ 对应的 $i$ 已经被填入的 $a_i$ 占用的位置有 $y$ 个。则考虑首先从 $y$ 个位置中强制选中 $i$ 个，方案数为 $C_y^i$。然后，剩下 $x-i$ 个位置随便排列 $(x-i)!$。则答案为 $\sum_{i=0}^yC_y^i\times(x-i)!\times(-1)^i$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int b[2005];
int C[2005][2005];
int fac[2005];
signed main() { 
	for(int i=0;i<=2000;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=C[i-1][j-1]+C[i-1][j];
			C[i][j]%=mod;
		} 
	}
	fac[0]=1;
	for(int i=1;i<=2000;i++){
		fac[i]=(fac[i-1]*i)%mod;
	}
    int n;
    cin>>n;
    int a[n+1];
    int nd=0;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	if(!(a[i]+1)) nd++;
    	else b[a[i]]=1;
	}
	int cansame=0;
	for(int i=1;i<=n;i++){
		if((!(a[i]+1))&&!b[i]) cansame++;
	}
	int tot=0;
	for(int i=0;i<=cansame;i++){
		if(i%2==0){
			tot=(tot+fac[nd-i]*C[cansame][i]%mod)%mod;
		}
		else{
			tot=(tot+mod-fac[nd-i]*C[cansame][i]%mod)%mod;
		}
	}
	cout<<tot;
}
```

---

## 作者：Mihari (赞：1)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF340E)

# 题解

错排，显然的容斥.

记我们要填入的数字有 $s$ 个，其中可以任意填的数字有 $q$ 个，现在对这个问题进行分析.

总方案数显然 $s!$，那么如何去重？

考虑用错排的经典思路，减去至少不合法，加上两个不合法，减去三个不合法，加上四个不合法...

容斥式就可以得出
$$
Ans=s!+\sum_{i=1}^{s-q}(-1)^i{s-q\choose i}(s-i)!
$$
预处理之后套公式即可.

# 代码

```cpp
#include<cstdio>

#define rep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i<=i##_end_;++i)
#define fep(i,__l,__r) for(signed i=(__l),i##_end_=(__r);i>=i##_end_;--i)
#define erep(i,u) for(signed i=tail[u],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
#define writc(a,b) fwrit(a),putchar(b)
#define mp(a,b) make_pair(a,b)
#define fi first
#define se second
typedef long long LL;
// typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned uint;
#define Endl putchar('\n')
// #define int long long
// #define int unsigned
// #define int unsigned long long

#define cg (c=getchar())
template<class T>inline void read(T& x){
    char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    if(f)x=-x;
}
template<class T>inline T read(const T sample){
    T x=0;char c;bool f=0;
    while(cg<'0'||'9'<c)f|=(c=='-');
    for(x=(c^48);'0'<=cg&&c<='9';x=(x<<1)+(x<<3)+(c^48));
    return f?-x:x;
}
template<class T>void fwrit(const T x){//just short,int and long long
    if(x<0)return (void)(putchar('-'),fwrit(-x));
    if(x>9)fwrit(x/10);
    putchar(x%10^48);
}
template<class T>inline T Max(const T x,const T y){return x<y?y:x;}
template<class T>inline T Min(const T x,const T y){return x<y?x:y;}
template<class T>inline T fab(const T x){return x>0?x:-x;}
inline int gcd(const int a,const int b){return b?gcd(b,a%b):a;}
inline LL mulMod(const LL a,const LL b,const LL mod){//long long multiplie_mod
    return ((a*b-(LL)((long double)a/mod*b+1e-8)*mod)%mod+mod)%mod;
}

const int mod=1000000007;
const int maxn=2000;

inline int getmod(const int x){
    return (x%mod+mod)%mod;
}

int C[maxn+5][maxn+5];
int fac[maxn+5];

int n,a[maxn+5];

bool exist[maxn+5];

/** @brief 记录有多少位置是 -1*/
int s;
/** @brief 记录有多少数字可以任意填*/
int q;

inline void Init(){
    rep(i,0,n){
        C[i][0]=C[i][i]=1;
        rep(j,1,i-1){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
            if(C[i][j]>=mod)C[i][j]-=mod;
        }
    }
    fac[0]=1;
    rep(i,1,n)fac[i]=1ll*fac[i-1]*i%mod;
}

#define sign(i) ((i&1)?-1:1)

signed main(){
    n=read(1);
    Init();
    rep(i,1,n){
        a[i]=read(1);
        if(a[i]==-1)++s;
        else exist[a[i]]=true;
    }
    //它是要填入的数, 但是它自己的位置被人占了
    rep(i,1,n)if(!exist[i] && a[i]!=-1)++q;
    int ans=fac[s];
    rep(i,1,s-q){
        ans+=1ll*sign(i)*C[s-q][i]*fac[s-i]%mod;
        ans=getmod(ans);
    }writc(ans,'\n');
    return 0;
}
```



---

## 作者：Autre (赞：0)

给定两个大小相等的集合 $A,B$，求满足 $f(i)\not=i$ 的双射 $f$ 的数量。

若 $A=B$ 则为错排问题，所以我们考虑类似地通过递推解决这个问题。

令 $S=A\cap B$，设 $f(n,m)$ 为 $|S|=n,|A|=|B|=n+m$ 时这样的双射 $f$ 的数量。

显然 $f(0,m)=m!$。$n>0$ 时我们令 $t=\inf S$，对所有 $f$ 按照 $f(t)$ 进行分类讨论：

- 若 $f(t)\in S$ 且 $f(t)=f^{-1}(t)$，显然有这种情况下所有合法 $f$ 到 $A,B$ 均去掉 $t,f(t)$ 后所有合法 $f$ 的双射，所以这种情况的方案数为 $(n-1)f(n-2,m)$
- 否则，通过令 $f^{-1}(t)$ 映射到 $f(t)$，可以得到所有合法 $f$ 到 $A,B$ 均去掉 $t$ 后所有合法 $f$ 的双射，所以这种情况的方案数为 $(n+m)f(n-1,m)$。

由此可以得到递推式 $f(n,m)=(n-1)f(n-2,m)+(n+m)f(n-1,m)$。可见合法的状态只有 $O(n)$ 种。

---

## 作者：WilliamFranklin (赞：0)

一道二项式反演板子题。

### 主要思路

首先复习一下二项式反演。

设 $g(i)$ 表示恰好选了 $i$ 个的方案数，$f(i)$ 表示至少选 $i$ 个的方案数，那么就有：

$$g(n) = \sum_{i = n}^{m}{(-1)^{i - n}\binom{i}{n}}f(i)$$

如果想看详细解说的话可以到百度上或 oi-wiki 上学一下。

那么下面再来看这道题，不存在 $a_i = i$ 就是恰好有 $0$ 个位置满足 $a_i = i$，也就是 $g(0)$，所以直接带入到式子中求即可。

下面就说一下 $f(i)$ 怎么求，首先我们考虑全是 $-1$ 的情况，那么 $f(i)$ 就是从这 $n$ 个位置中选出 $i$ 个位置必须满足 $a_i = i$ 的方案数，所以可以得到下面式子：

$$f(i) = \binom{n}{i} (n - i)!$$

对于题目中的情况可以直接从上面简单的情况类比过了，就不细讲了，细节看下代码吧。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 2005, mod = 1e9 + 7;
int a[N];
int n;
bool vis[N];
long long fac[N];
long long ifac[N];
long long quickpow(long long a, long long b, long long mod) {
	long long res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
long long C(long long x, long long y) {
	//cout << fac[x] << ' ' << fac[x - y] << ' ' << ifac[y] << '\n';
	return fac[x] * ifac[x - y] % mod * ifac[y] % mod;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	For(i, 1, n) cin >> a[i];
	int nn = n;
	For(i, 1,n) {
		if (a[i] != -1) {
			vis[a[i]] = 1;
			vis[i] = 1;
			nn--;
		}
	}
	int m = 0;
	For(i, 1, n) m += !vis[i];
	fac[0] = 1;
	For(i, 1, n) fac[i] = fac[i - 1] * i % mod;
	For(i, 0, n) ifac[i] = quickpow(fac[i], mod - 2, mod); 
	long long ans = 0; 
	For(i, 0, m) {
		if (i % 2 == 0) {
			ans = (ans + C(m, i) * fac[nn - i] % mod) % mod;
		} else {
			ans = (ans - C(m, i) * fac[nn - i] % mod + mod) % mod;
		} 
		//cout << C(m, i) << ' ' << fac[nn - i] << ' ' << ans << '\n';
	}
	cout << ans;
	return 0;
} 
```

### 谢谢观看

---

## 作者：极寒神冰 (赞：0)

对于没有出现的数字可以分为两类

$1$.自己原来所在的位置已经被其他数占据,那么这个数就可以随便放

$2$.自己原来的位置还没有被其他数放

我们可以假设这两个数共有$s$个，有$a$个数可以随便放，那没就有$s-a$个数就要错排。

考虑容斥：所有数随便排的方案减去至少有一个数放在原来位置加上至少两个数放在原来位置……

答案即为$s!-\sum\limits_{i=1}^{s-a}(-1)^i\binom{s-a}{i}(s-i)!$

---

