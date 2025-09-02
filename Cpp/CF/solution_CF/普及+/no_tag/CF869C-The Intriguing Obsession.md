# The Intriguing Obsession

## 题目描述

齐心协力，我们可以以超乎想象的速度到达任何地方！现在，火炎姐妹 (Fire Sisters) —— 火怜 (Karen) 和月火 (Tsukihi) 正在前往一个她们从未到达的地方——水中的小岛！

有三种不同类型的小岛，方便地，各自涂上了红，蓝，紫三色。每种颜色的小岛各自有 $a,b,c$ 个。

这些小岛之间初始时互相分离。可以在小岛之间架桥，两个小岛间最多架一座桥。

但要满足：任意两个不同的颜色相同的小岛的最短距离要大于等于 $3$（桥的长度为 $1$）。

火炎姐妹已经准备好迎接未知了，但是她们想测试一下你的勇气。你需要计算出不同的架桥方案有多少种，如果有两个小岛之间造桥的方案变了，我们就说这两个造桥的方案不同。答案对 $998244353$ 取模。

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
1 2 2
```

### 输出

```
63
```

## 样例 #3

### 输入

```
1 3 5
```

### 输出

```
3264
```

## 样例 #4

### 输入

```
6 2 9
```

### 输出

```
813023575
```

# 题解

## 作者：zct_sky (赞：12)

### Solution:
-----
首先，因为两个同色小岛的距离要大于 $3$。

所以，我们能得出：

1. 同色岛之间不能相连。
2. 一个岛不能同时与两个颜色相同的岛相连。

那么只有三种连法：$A-B,B-C,A-C$。

而且这三种方法都是独立的。

所以最终答案就是这三种方法数相乘。

接下来讲如何推出两种不同颜色岛之间的连接方法数。

比如求 $A$ 色岛与 $B$ 色岛之间的方法数。

因为一个 $A$ 色岛只能连一个 $B$ 色岛，所以它的方法数就是：从 $a$ 个岛里选 $0$ 个的方法数 $\times$ 从 $b$ 个岛里选 $0$ 个的方法数 $\times$ $0$ 个数的总排列数 + 从 $a$ 个岛里选 $1$ 个的方法数 $\times$ 从 $b$ 个岛里选 $1$ 个的方法数 $\times$ $1$ 个数的总排列数 + $\dots$ + 从 $a$ 个岛里选 $a$ 个的方法数 $\times$ 从 $b$ 个岛里选 $a$ 个的方法数 $\times$ $a$ 个数的总排列数。（$a$ 表示 $A$ 色岛的数量，$b$ 表示 $B$ 色岛的数量，且 $a\leq b$）。

也就是 $1+\sum\limits_{i=1}^a{C^i_a \times C^i_b \times i!}$（$1$ 是从 $a$ 个岛里选 $0$ 个的方法数 $\times$ 从 $b$ 个岛里选 $0$ 个的方法数 $\times$ $0$ 个数的总排列数）。

或者是 $1+\sum\limits_{i=1}^a{A^i_a\times C^i_b}$。

最后讲一下计算方法。

我们可以用杨辉三角来求组合数 $C^n_m$，再加上一个暴力求阶乘的函数，总复杂度 $\Theta(c^2)$（$a$ 表示 $A$ 色岛的数量，$b$ 表示 $B$ 色岛的数量，$c$ 表示 $C$ 色岛的数量，假设 $a\leq b\leq c$）。

### Code1:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
const int MOD=998244353;
ll fac[5005]={1},a,b,c;
ll C[5005][5005];
void init(){
	C[0][0]=1;
	for(int i=1;i<=c;i++){//杨辉三角求组合数 
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
	}
	for(int i=1;i<=c;i++)fac[i]=fac[i-1]*i,fac[i]%=MOD;//暴力求阶乘 
}	
ll solve(ll a,ll b){//求方案数 
	ll ans=1;
	for(int i=1;i<=a;i++){
		ans=(ans+(C[a][i]*C[b][i])%MOD*fac[i]%MOD)%MOD;
	}
	return ans;
}
int main(){
	a=read(),b=read(),c=read();
	if(b<a)swap(a,b);if(c<a)swap(a,c);if(c<b)swap(b,c);
	init();
	printf("%lld",(solve(a,b)*solve(b,c)%MOD*solve(a,c)%MOD));
	return 0;
}
```

但是，我们发现，真正有用的组合数实际上只有 $C^1_a,C^1_b,C^1_c,C^2_a,C^2_b,C^2_c\dots C^a_a,C^b_b,C^c_c$。

甚至将它变成第二个式子后连 $C^1_a,C^2_a,C^3_a\dots C^a_a$ 都没用了（虽然需要算 $A^1_a,A^1_b,A^2_a,A^2_b,\dots A^a_a,A^b_b$）。

而这些用暴力计算的复杂度只有 $\Theta (a+b+c)$。

但是，暴力算时遇到了一个麻烦，我们知道 $C^n_m= \dfrac{\prod_{i=1}^n m-i+1}{\prod_{i=1}^n i}(n\leq m)$

计算乘法很好解决，那计算除法呢？

这时我们就需要 乘法逆元 了（没学过乘法逆元的[点这里](https://www.luogu.com.cn/problem/P3811)）。

我们先预处理好 $1,2,3\dots c$ 的逆元，然后就能枚举 $i$，然后，每次乘以 $m-i+1$，除以 $i$ 时只需要乘它的逆元就行了。

这样时间复杂度就降到了 $\Theta(a+b+c)$ 了。
### Code2:
-----
```c++
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-')y=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0')x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x*y;
}
const int N=5007;
ll Aa[N],Ab[N];
ll Cb[N],Cc[N];
ll inv[N];
ll a,b,c,x,ac,bc,ab,ans;
const ll MOD=998244353;
void init(){
	//线性求逆元 
	inv[1]=1;
	for(int i=2;i<=c;i++)inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
	
	x=1;
	//求a的排列（A(a,i)） 
	for(ll i=1;i<=a;i++){ 
		x*=(a-i+1);x%=MOD;
		Aa[i]=x;
	}
	x=1;
	//求b的排列（A(b,i)） 
	for(ll i=1;i<=b;i++){
		x*=(b-i+1);x%=MOD;
		Ab[i]=x;
	} 
	x=1;
	//求b的组合（C(b,i)） 
	for(ll i=1;i<=b;i++){
		x*=(b-i+1);x%=MOD;x*=inv[i];x%=MOD;
		Cb[i]=x;
	} 
	x=1;
	//求c的组合（C(c,i)） 
	for(ll i=1;i<=c;i++){
		x*=(c-i+1);x%=MOD;x*=inv[i];x%=MOD;
		Cc[i]=x;
	}  
} 
int main(){
	a=read(),b=read(),c=read();
	if(b<a)swap(a,b);if(c<a)swap(a,c);if(c<b)swap(b,c);
	init();
	for(ll i=1;i<=a;i++)//暴力求解 
		ab=(ab+(Aa[i]*Cb[i])%MOD)%MOD;
	for(ll i=1;i<=a;i++)
		ac=(ac+(Aa[i]*Cc[i])%MOD)%MOD;
	for(ll i=1;i<=b;i++)
		bc=(bc+(Ab[i]*Cc[i])%MOD)%MOD;
	ab++,ac++,bc++;
	ab%=MOD,ac%=MOD,bc%=MOD;
	ans=((ab*ac)%MOD*bc)%MOD;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Styx (赞：8)

哇，这场的背景是物语系列啊~又找到了一场动漫场……

首先来考虑一下哪些情况是会被hack掉的

第一种情况显然是同一个区域里连一条边，这样同一个区域里

![](https://images2018.cnblogs.com/blog/1188068/201807/1188068-20180711181655320-1298503177.png)

所以我们一定每次不能连相同区中的两个点，除此之外还有吗？

![](https://images2018.cnblogs.com/blog/1188068/201807/1188068-20180711182503982-1721981847.png)

显然如果一个点连了另一个区域内的两个点，会让这两个点之间的距离变成2，然后GG

于是我们得出了一个结论

如果在两个区域里连点，两个区域内选的点数一定要相等

即a中选出i个点，必须与b中选出i个点相连

连接种类数为
![](https://images2018.cnblogs.com/blog/1188068/201807/1188068-20180711183451020-1576025612.png)

然后我们再来看，如果ab中有两点相连，其中一点再与c相连会出事吗？

![](https://images2018.cnblogs.com/blog/1188068/201807/1188068-20180711183636399-1188883255.png)

很显然不会对答案产生任何影响

所以我们可以得出另外一个结论

a-b b-c c-a所连的边无论如何都是两两独立的

也就是说，如果a-b连边的可能数为x，b-c连边的可能数为y，c-a连边的可能数为z

![](https://images2018.cnblogs.com/blog/1188068/201807/1188068-20180711184057516-1066434806.png)

那么既连ab有连bc的可能性是可以直接用乘法原理推得为xy

同理 ab ca为xz,bc ca为yz

所以总答案就是1+x+y+z+xy+yz+xz+xyz

代码如下:

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define mod 998244353
using namespace std;

long long ans=1ll,fac[5010],inv[5010],aa,bb,cc,ab,bc,ca;

long long kasumi(long long a,long long b)
{
    long long ans=1;
    while(b)
    {
        if(b&1)
        {
            ans=((ans%mod)*a)%mod;
        }
        a=((a%mod)*a)%mod;
        b>>=1;
    }
    return ans;
}

long long c(long long n,long long m)
{
    if(n==m)
    {
        return 1;
    }
    return (((fac[m]*inv[n])%mod)*inv[m-n])%mod;
}


int main()
{
    fac[1]=1;
    for(int i=2;i<=5000;i++)
    {
        fac[i]=fac[i-1]*i%mod;
    }
    inv[5000]=kasumi(fac[5000],mod-2);
    for(int i=4999;i>=1;i--)
    {
        inv[i]=inv[i+1]*(i+1)%mod;
    }
    scanf("%lld%lld%lld",&aa,&bb,&cc);
    for(int i=1;i<=min(aa,bb);i++)
    {
        ab+=(((c(i,aa)*c(i,bb))%mod)*fac[i])%mod;
    }
    for(int i=1;i<=min(cc,bb);i++)
    {
        bc+=(((c(i,cc)*c(i,bb))%mod)*fac[i])%mod;
    }
    for(int i=1;i<=min(aa,cc);i++)
    {
        ca+=(((c(i,aa)*c(i,cc))%mod)*fac[i])%mod;
    }
    ca%=mod;
    bc%=mod;
    ab%=mod;
    ans+=ca+bc+ab;
    ans+=ca*bc;
    ans%=mod;
    ans+=ca*ab;
    ans%=mod;
    ans+=ab*bc;
    ans%=mod;
    ans+=(((ca*bc)%mod)*ab)%mod;
    printf("%lld\n",ans%mod);
}
```


---

## 作者：pldzy (赞：3)

此题算法：模拟。

**题目概述**

  _由题意可得_，此题是让我们连接三种不同颜色的点，
  
  要求同颜色的点距离大于等于 3 （每条边的距离为 1 ），
  
  任意两个点至多连 1 条边，
  
  问有多少种连接方案（答案需取模）。
  

------------

  
**Part 1 - 主要思路**

 _首先，_ 

因为：同颜色的点距离大于等于 3 ，

所以我们可以得出：

- 显然，一个点不能与它同色的点相连；

- 一个点不能同时与两个同色点相连。

*综上，*

只有 3 种连接方案—— a 与 b ， b 与 c , a 与 c 。 

且！ 3 种连接方案都是独立的。

接着，我们就只用计算每两种颜色最多可以有多少种连接方案。


------------


**Part 2 - 计算方案**

举一个栗子：求 a 与 b 连接的方案总数。

总数 = 从 a 与 b 中各挑 0 个的方案数 + 
各挑 1 个的方案数 + 各挑 2 个的方案数 + ······ + 各挑 $min (a, b)$ 的方案数 。

且，

从 a 与 b 中各挑 i 个方案数 = 从 a 中挑 i 个数的方案数 $*$ 从 b 中挑 i 个数的方案数 $*$  i 个数的排列情况总数。

这个， 不就是~~我们小学就学过的~~排列组合 + 阶乘吗？


------------


**Part 3 - 计算 + 完善**

 _1 . 排列组合计算：_
 
 用二维数组 $C[i][j]$ 来模拟组合的计算,
 
 表示从 i 个里面挑 j 个数。
 
 通过~~我们又在小学就学过的~~杨辉三角可以对数组 C 进行预处理，后面直接用即可。
 
 特别注意：不要忘记还有从 0 个里面挑 0 个的情况，这个直接特殊处理，在最后的时候再加上即可。
 
  _2 . i 个数排列情况计算：_
  
  这个相对 1 来说就简单多了，情况总数 = i 的阶乘。
  
  类似 1 里面的处理方法，我们用数组 jc ~~（请原谅我的变量名）~~ 进行预处理，后面直接用即可。
  
   _3 . 最终完善：_
   
   最后的答案就是三种情况的数量相乘，不要忘记取模！！！
   

------------

   
   **最后的最后：**
   
   记得开 $longlong$ 。
   

------------
**$Code$**
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
int a, b, c;
const int Mod = 998244353;
const int maxn = 5005;
int jc[maxn];
int C[maxn][maxn];
int maxx;

inline void jc_init ()
{
	jc[1] = 1;
	for (int i = 2; i <= maxx; i++) jc[i] = (jc[i - 1] * i) % Mod;
}

inline void C_init ()
{
	C[0][0] = 1;
	for (int i = 1; i <= maxx; i++)
		for (int j = 0; j <= i; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Mod;
}

inline int calcu (int x, int y)
{
	int res = 1;
	int minn = min (x, y);
	for (int i = 1; i <= minn; i++)
		res = (res + C[x][i] * C[y][i] % Mod * jc[i] % Mod) % Mod;
	return res;
}

signed main()
{
	scanf ("%lld%lld%lld", &a, &b, &c);
	maxx = max (a, max (b, c));
	jc_init ();
	C_init ();
	printf ("%lld\n", calcu (a, b) * calcu (b, c) % Mod * calcu (c, a) % Mod);
	return 0;
}
```


------------
该题解篇幅较长，如果该题解中有错误，请您及时给本蒟蒻指正，感谢。


---

## 作者：迟暮天复明 (赞：2)

[题面](http://codeforces.com/contest/869/problem/C)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16277342.html)

Description:

有 $a$ 个红色岛，$b$ 个蓝色岛，$c$ 个紫色岛，在岛之间连边，使得任意两个同色岛屿之间的距离不小于 $3$，问有几种连边方法。

-----

不用组合数的 DP 方法。

设 $f(i,j)$ 为在数量为 $i$ 的颜色的岛与数量为 $j$ 的颜色的岛之间连边的方案数。比如，$f(1,1)=2$，因为我既可以选择不连边，也可以选择连一条边。那么，答案就是 $f(a,b)\times f(b,c)\times f(a,c)$。

考虑 $f$ 的递推式。明显的，同一个点只能连出去一条边，也可以不连边。如果我连边，则要在 $j$ 个点中选一个点和它相连，有 $j$ 种可能性，而 $i$ 要减一，$j$ 也要减一。如果我不连边，则只有一种可能性，$i$ 减一，$j$ 不变。于是我们得到了方程。
$$f(i,j)=f(i-1,j-1)\times j+f(i-1,j)$$

边界条件明显是 $f(i,0)=f(0,i)=1$。前面的式子直接递推即可。时间复杂度在默认 $a,b,c$ 同阶的情况下是 $O(a^2)$，可以通过本题。

[代码](https://pastebin.ubuntu.com/p/RCxNVtK5N8/)

---

## 作者：三点水一个各 (赞：2)

在机房想都没想就把标程交了。

结果教练要我讲，


这就尴尬了，像我这种蒟蒻怎么可能会做。

***

### 思路

因为` or the shortest distance between them is at least 3 ` ，所以去掉以下两种情况

```
1.对于两个颜色的岛屿，到对面有桥的岛屿数量不一样
 （这就意味着桥数大的两个岛屿距离为2，如左下图的蓝1，蓝2）

2.单种颜色岛内有边相连
 （如右下图的紫1，紫2）
```
![](http://codeforces.com/predownloaded/ce/99/ce99521933acb94fcf989ddf0b962c8c25978194.png)

现分类讨论AB，AC，BC，最终的答案即为三者之积。

A与B中，从A中选x个（也就是$C_A^x$)，从B中就也得选x个（也就是$C_B^x$)，这种情况下各有$x!$个，所以选x个时的情况总数是

   $C_A^x$ * $C_B^x$ * $x!$个。

因为$A_x$和$B_x$相等，所以x的范围是1~$Min_  (a,b)$

所以A与B的情况综合是

 $C_A^1$ * $C_B^1$ * $1!$ * $C_A^2$ * $C_B^2$ * $2!$ * … * $C_A^Min_(A,B)$ * $C_B^Min_(A,B)$ * $Min_(A,B)!$

所以答案即为

 $C_A^1$ * $C_B^1$ * $1!$ * $C_A^2$ * $C_B^2$ * $2!$ * … * $C_A^Min_(A,B)$ * $C_B^Min_(A,B)$ * $Min_(A,B)!$ * $C_A^1$ * $C_C^1$ * $1!$ * $C_A^2$ * $C_C^2$ * $2!$ * … * $C_A^Min_(A,C)$ * $C_C^Min_(A,C)$ * $Min_(A,C)!$ * $C_B^1$ * $C_C^1$ * $1!$ * $C_B^2$ * $C_C^2$ * $2!$ * … * $C_B^Min_(B,C)$ * $C_C^Min_(B,C)$ * $Min_(B,C)!$。

这实在是太长了，所以我们把他拆了再乘。

别忘了膜那998啥的。

### 后记

~~叫练再也不用担心我不会讲课啦~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#define ll long long
long long n,a,b,c,t,p=998244353,x[5001][5001],y[5001];
int main()
{
    ll i,j;
    scanf("%lld%lld%lld",&a,&b,&c);
    if (a>b) n=a; else n=b;
    if (c>n) n=c;
    x[0][0]=1; y[0]=1;
    for (i=1;i<=n;i++)
      for (j=0;j<=i;j++)
	x[i][j]=(x[i-1][j-1]+x[i-1][j])%p;  //暴力打表组合数
    ll ans1=0,k=a,l=b;
  
    if (k>l) {t=k;k=l;l=t;}
    for (j=1;j<=l;j++) y[j]=(y[j-1]*j)%p; //打表阶乘
    for (i=0;i<=k;i++) ans1=(ans1+(x[k][i]*x[l][i])%p*y[i])%p; //如题解，算AB的情况总数
  
    ll ans2=0; k=b; l=c;
    if (k>l) {t=k;k=l;l=t;} 
    for (j=1;j<=l;j++) y[j]=(y[j-1]*j)%p; //接着膜
    for (i=0;i<=k;i++) ans2=(ans2+(x[k][i]*x[l][i])%p*y[i])%p;
  
    ll ans3=0; k=a; l=c; 
    if (k>l) {t=k;k=l;l=t;} 
    for (j=1;j<=l;j++) y[j]=(y[j-1]*j)%p;
    for (i=0;i<=k;i++) ans3=(ans3+(x[k][i]*x[l][i])%p*y[i])%p;
  
    ans1=ans1*ans2%p; //继续膜
    printf("%lld",ans1*ans3%p); //还是膜
    return 0;
} 
```

---

## 作者：Digital_Sunrise (赞：1)

## CF869C题解
## 思路
**前置知识**

排列组合：

$C^n_m$表示在$m$个不同元素中挑出$n$个元素的方法数量(不计顺序)

$$C^n_m=\frac{\prod^m_{m-n+1}}{\prod^n_1}$$

证明：

在$m$个不同元素中挑 $n$ 个

挑第1个,有 $m$ 种方法。

挑第2个,有 $(m-1)$ 种方法。

挑第3个,有 $(m-2)$ 种方法。

$\qquad\quad\vdots$

挑第 n 个,有 $(m-n+1)$ 种方法。

根据加乘原理，共有$\prod^m_{m-n+1}$种方式。

但是 $C^n_m$ 的定义是:

>在$m$个不同元素中挑出 $n$ 个元素的方法数量(不计顺序)

所以我们要做一些去重工作，

$n$个元素有$n!$种内部排序方式，

所以我们在乘完之后要除回 $n!$。

**关于本题**

首先，注意到
>任意两个不同的颜色相同的小岛的最短距离要大于等于 3（桥的长度为 1）

所以
>1.一个岛不能同时与两座颜色相同的岛连线

>2.一个岛不能与颜色与自己相同的岛

So，有三种连线情况:AB相连,BC相连,AC相连。

举例: AB 相连

首先，在 A 中选择 $x$ 个岛屿，同时B中也要同时选择 $x$ 个岛屿。

这是，我们将$A$中的岛屿的顺序固定下来，让B中的岛屿与其配对，共有$x!$中排列方法。

所以， AB 相连$x$个岛屿有$C^x_A*C^x_B*x!$中方法。

根据加乘原理，则AB相连总共有：

$C^1_A*C^1_B*1! * C^2_A*C^2_B*2! *...C^{min_{a,b}}_A*C^{min_{a,b}}_B*{min_{a,b}}!$

BC 相连与 AC 相连同理。

但由于这三种情况是**相互独立**的，所以我们最后把他们相加。
## 代码
提醒：
>10年OI一场空，不开long long见祖宗

AC Coding:
```cpp
#include <bits/stdc++.h>
#define int long long
const int mod = 998244353;
using namespace std;
int a,b,c,C[5005][5005];
int ans1 = 0,ans2 = 1;
int rem[5005];
int factorial(int u)
{
	if(rem[u] != 0) return rem[u];
	rem[u] = factorial(u - 1) * u % mod;
	return rem[u];
}
signed main()
{
	C[0][0] = 1;
	rem[0] = rem[1] = 1;
	for(int i = 1;i <= 5000;i++) for(int j = 0;j <= i;j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	cin >> a >> b >> c;
	for(int i = 1;i <= min(a,b);i++) ans1 = ans1 + C[a][i] % mod * C[b][i] % mod * factorial(i) % mod,ans1 %= mod;
	ans1++;ans2 = ans2 * ans1 % mod,ans1 = 0;
	for(int i = 1;i <= min(b,c);i++) ans1 = ans1 + C[b][i] % mod * C[c][i] % mod * factorial(i) % mod,ans1 %= mod;
	ans1++;ans2 = ans2 * ans1 % mod,ans1 = 0;
	for(int i = 1;i <= min(a,c);i++) ans1 = ans1 + C[a][i] % mod * C[c][i] % mod * factorial(i) % mod,ans1 %= mod;
	ans1++;ans2 = ans2 * ans1 % mod;
	cout << ans2;
	return 0;
}
```


---

## 作者：lichenghan (赞：1)

# CF869C 

Ps：为表述方便，本题解中“小岛”称作“点”，“桥”称作“连线”

[**传送门**](https://www.luogu.com.cn/problem/CF869C)

## 先讲讲思路

首先，题目中有一个重要的条件：
>
任意两个不同的颜色相同的小岛的最短距离要大于等于 3（桥的长度为 1）。

所以：
>
1. 2个同色点之间不能连线。
2. 一个点不能连接两个异色的点。


总结一下，一个点要么连接一个异色的点，要么连接两个异色且互相也异色的点。

可以看出，两种颜色之间的连线的种数是**相互独立的！**

然后问题就简化成了**2种颜色连线种数**相乘！

那么，**两种颜色怎么求呢？**

~~小学奥数开始~~

我们以红蓝为例，

先从红点中选 $x$ 个（ $x$ 为边数），$C^x_a$ 种；

再从蓝点中选 $x$ 个，$C^x_b$ 种；

最后 $x$ 种连线，$x!$ 种。

所以红蓝连线的种数为： 
$\sum_{x=1}^{\min(a,b)}{C^x_a*C^x_b*x!}$

答案为：

$$
\Bigg(\sum_{x=1}^{\min(a,b)}{C^x_a*C^x_b*x!}+1\Bigg)*
\Bigg(\sum_{x=1}^{\min(a,c)}{C^x_a*C^x_c*x!}+1\Bigg)*
\Bigg(\sum_{x=1}^{\min(c,b)}{C^x_c*C^x_b*x!}+1\Bigg)
$$

## Code

#### Tips：不开long long见祖宗！

```cpp
#include <iostream>
#define int long long
using namespace std;
const int mod=998244353;
const int N=5005;
int fac[N];
int C[5005][5005];
int calc(int x,int y){//计算2个颜色的种数
	int ret=0;
	int minn=min(x,y);
	for(int i=1;i<=minn;i++){
		ret=(ret+C[x][i]*C[y][i]%mod*fac[i]%mod)%mod;
	}
	return ret;
}
signed main(){
	int a,b,c;
	cin>>a>>b>>c;
	int maxn=max(a,max(b,c));
	fac[1]=1;//暴力阶乘
	for(int i=2;i<=maxn;i++){
		fac[i]=(fac[i-1]*i)%mod;
	}
	C[0][0]=1;//暴力组合数（杨辉三角）
	for(int i=1;i<=maxn;i++){
		for(int j=0;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	cout<<(calc(a,b)+1)*(calc(b,c)+1)%mod*(calc(c,a)+1)%mod;
} 
```

---

## 作者：Eason_cyx (赞：0)

因为两个相同颜色的岛屿之间的距离至少为 $\color{red}\bf{3}$，所以显然有以下两条：

- 两个相同颜色的岛屿之间不能连边。

- 假设一个岛屿颜色为 $\bf{A}$，那么它不能同时和两个 $\bf{B}$ 颜色岛屿有连边。

综上，我们的连边方式只能是 $\bf{A-B}$，$\bf{B-C}$ 或者 $\bf{C-A}$。因为三种情况之间没有交集，所以假设它们的方案数分别为 $ans_1$，$ans_2$，$ans_3$，那么根据乘法原理，答案就是 $ans_1 \times ans_2 \times ans_3$。现在考虑如何计算 $ans$：

以 $\bf{A-B}$ 举例，我们可以枚举 $1 \sim \min(a,b)$ 之间的所有 $j$。那么，$j$ 个 $\bf{A}$ 和 $j$ 个 $\bf{B}$ 连接的方案数就是 $\operatorname{C}_{a}^{j} \times \operatorname{C}_{b}^{j} \times j!$。注意，$j=0$ 时恰好有 $1$ 种方案。那么就有

$$ans_1=1+\sum_{j=1}^{\min(a,b)}\operatorname{C}_{a}^{j} \times \operatorname{C}_{b}^{j} \times j!$$

$ans_2$，$ans_3$ 同理。

那么就得到了最终答案。预处理一下组合数，假设 $a \le b \le c$，那么时间复杂度为 $O(c^2)$，可以通过。[提交记录](https://codeforces.com/contest/869/submission/304839165)

---

