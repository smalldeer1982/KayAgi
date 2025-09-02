# Bingo!

## 题目描述

The game of bingo is played on a $ 5×5 $ square grid filled with distinct numbers between $ 1 $ and $ 75 $ . In this problem you will consider a generalized version played on an $ n×n $ grid with distinct numbers between $ 1 $ and $ m $ $ (m>=n^{2}) $ .

A player begins by selecting a randomly generated bingo grid (generated uniformly among all available grids). Then $ k $ distinct numbers between $ 1 $ and $ m $ will be called at random (called uniformly among all available sets of $ k $ numbers). For each called number that appears on the grid, the player marks that cell. The score at the end is 2 raised to the power of (number of completely marked rows plus number of completely marked columns).

Determine the expected value of the score. The expected score may be very large. If the expected score is larger than $ 10^{99} $ , print $ 10^{99} $ instead (for example as "1e99" without the quotes).

## 样例 #1

### 输入

```
1 2 1
```

### 输出

```
2.5
```

## 样例 #2

### 输入

```
2 4 3
```

### 输出

```
4
```

## 样例 #3

### 输入

```
7 59164 40872
```

### 输出

```
3.1415926538
```

# 题解

## 作者：nofind (赞：3)

## [题意](https://www.luogu.com.cn/problem/CF457D)

感觉网上的题解都不太清楚，按照自己的理解写了一篇，如果出锅了请指出。

考虑$2^t$的实际意义：$t$表示被染黑的行和列的个数，那么$2^t$表示从这些染黑的行和列中选出一个子集（一些行和列）的方案数。
   
期望等于总和除以总方案数。  
$1.$总方案数为$C_m^{n^2}\times C_{m}^k$。  
$2.$总和：  
我们选出$r$行$c$列，方案数为$C_n^r\times C_n^c$，计算其贡献。  
这$r$行$c$列的贡献，即算有多少状态中**至少**这$r$行$c$列被染黑：  
先选定棋盘：$C_{m}^{n^2}$，那么这$r$行$c$列共$num=(r+c)*n-r*c$个数就确定了，我们选出的$K$个数中至少要包含这$num$个数，其他数随便选，方案数为$C_{m-num}^{k-num}$。

综上：  
$ans=\frac{1}{C_m^{n^2}C_m^k}\sum\limits_{r=0}^{n}\sum\limits_{c=0}^nC_n^rC_n^cC_m^{n^2}C_{m-num}^{k-num}=\sum\limits_{r=0}^n\sum\limits_{c=0}^n\frac{C_n^rC_n^cC_{m-num}^{k-num}}{C_m^k}$

code:
```
#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
const int maxn=100010;
int n,m,K;
ld ans;
ld fac[maxn];
inline int read()
{
    char c=getchar();int res=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
    return res*f;
}
inline ld C(int n,int m){return fac[n]-fac[n-m]-fac[m];}
int main()
{
	n=read(),m=read(),K=read();
	for(int i=1;i<=m;i++)fac[i]=fac[i-1]+log(1.0*i);
	for(int r=0;r<=n;r++)
		for(int c=0;c<=n;c++)
		{
			int num=r*n+c*n-r*c;
			if(num<=K)ans+=exp(C(n,r)+C(n,c)+C(m-num,K-num)-C(m,K));
		}
	if(ans>1e99)ans=1e99;
	printf("%.10lf",(double)ans);
	return 0;
}
```


---

## 作者：resftlmuttmotw (赞：3)

好久没做概率题了

基本上自己想不出来~~每次都得看题解学~~

这道题基本上没人写 题解 ，我来占个沙发

### $Firstly$,思路


$2019.10.26$

补充 ：
>  你的最终得分为$2^t$ 求得分的期望 

对于$2^t$ 我们可以理解为有一个集合$A ,S.T.|A|=t \Rightarrow$ $A$有$2^t$个子集


期望
$$ans=\displaystyle\sum^{n}_{r=0}\sum^{n}_{c=0}C_{n}^{r}*C_{n}^{c}*p_{r,c}$$

重点算$p_{r,c}$

从$m$中选出$k$个数分布在选中的$r$行$c$列

$r$行$c$列 共有 $num=(r+c)*n-r*c$个

$num$个数已经选出来且分布在选中的$r$行$c$列

剩下$C_{m-num}^{k-num}$选数方式

$$p_{r,c}=\frac{C_{m-num}^{k-num}}{C_{m}^{k}}$$

$2019.10.26$

补充：这里会与$P_{R,C}(R>=r,C>=c)$算重 但这样反而是正确的

针对每一个$t$ 我们都算了她的子集 所以 是$2^t$

~~这句话感性理解下就好~~我也不是很懂 **欢迎懂的人跟我讲**



关键是此题数据很大 又没有说取模

那么可以想到用指数进行运算


应该知道

$$log(n)=log_{e}n$$

$$exp(x)=e^x$$

### $Attention$

用$long double$

输出 转成$double$ 再用$lf$ 输出

用 $Lf$输出$long double$本地可过 $CF$上会错 （雾）

$vjudge$ 上语言选 GNU $G++11 5.1.0$

### $Code$

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define isdigit(x) ('0' <= (x)&&(x) <= '9')
template<typename T>
inline T Read(T Type)
{
	T x = 0,f = 1;
	char a = getchar();
	while(!isdigit(a)) {if(a == '-') f = -1;a = getchar();}
	while(isdigit(a)) {x = (x << 1) + (x << 3) + (a ^ '0');a = getchar();}
	return x * f;
}
typedef long double lb;
const int MAXN = 100010;
lb f[MAXN],ans;
inline lb C(int n,int m)
{
	return f[n] - f[m] - f[n - m];
}
int main()
{
	int n = Read(1),m = Read(1),k = Read(1);
	for(reg i = 1;i <= 1e5;i++) f[i] = f[i - 1] + log(1.0 * i);
	for(reg i = 0;i <= n;i++)
	{
		for(reg j = 0;j <= n;j++)
		{
			int num = (i + j) * n - i * j;
			if(num <= k)
			{
				lb p = C(n,i) + C(n,j) + C(m - num,k - num) - C(m,k);
				ans = min(ans + exp(p),(lb)1e99);
			}
		}
	}
	printf("%.10lf",(double)ans);
    return 0;
}
```



---

## 作者：tommymio (赞：1)

初看题面，这题唯一看不懂的，是那个 $2^t$。不妨想想这个东西的组合意义：在全部被涂黑的行与列之和共 $t$ 大小的集合中，选出一个子集的方案数。

然后我们就来考虑，这个东西对于整个期望式的贡献。很显然把这个方案数拆出来作为一个计数是非常好的，于是直接分别枚举被涂黑的行数和列数，有期望式：

$$
ans=\frac{\sum\limits_{r=0}^n\sum\limits_{c=0}^nC_n^rC_n^cC_{m}^{n^2}C_{m-t}^{k-t}}{C_m^{n^2}C_{m}^{k}}
$$

分数线上面的是所有情况下被涂黑的行列数之和，下面的是所有情况的情况数，这就是一个标准的计数题，不过披上了期望的外壳。

由于答案可能非常大，想到使用 $\log$ 与 $\exp$ 避免精度问题。

**Show the Code**

```cpp
#include<cstdio>
#include<cmath>
typedef long double ld;
ld fac[100005];
inline ld binom(int n,int m) {return fac[n]-fac[n-m]-fac[m];}
int main() {
    int n,m,k; ld ans=0.00;
    scanf("%d%d%d",&n,&m,&k);
    for(register int i=1;i<=m;++i) fac[i]=fac[i-1]+log(1.00*i);
    for(register int r=0;r<=n;++r) {
        for(register int c=0;c<=n;++c) {
            int t=(r+c)*n-r*c;
            if(k>=t) ans+=exp(binom(n,r)+binom(n,c)+binom(m-t,k-t)-binom(m,k));
        }
    }
    if(ans>1e99) printf("%.10lf\n",(double)1e99);
    else printf("%.10lf",(double)ans);
    return 0;
}
```

---

