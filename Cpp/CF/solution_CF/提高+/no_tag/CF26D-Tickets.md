# Tickets

## 题目描述

足球赛要到了，小 C 负责卖票。票价为每人 $10$ 元，而有 $n$ 个人带了 $10$ 元，$m$个人带了 $20$ 元，开始的时候小 C 有 $k$ 张 $10$ 元。假定这 $n+m$ 个人前来买票的顺序是随机的，试求小 C 能够顺利卖给这些人票的概率是多少。（译者：就是都能找开钱）

## 说明/提示

$0 \leq n,m \leq 10^5$，$0 \leq k \leq 10$。

## 样例 #1

### 输入

```
5 3 1
```

### 输出

```
0.857143
```

## 样例 #2

### 输入

```
0 5 5
```

### 输出

```
1
```

## 样例 #3

### 输入

```
0 1 0
```

### 输出

```
0
```

# 题解

## 作者：xtx1092515503 (赞：10)

这题的模型转换是~~小学奥数~~常见的套路。

我们令平面直角坐标系上一个点$(x,y)$表示：当前已经来了$x$个$10$元的人，$y$个$20$元的人。则显然，所有$x<y$，即在直线$y=x$上方的点，都是不合法的，因为这就意味着找不开钱了。

![](https://cdn.luogu.com.cn/upload/image_hosting/7aeuk3pf.png)

则我们一开始可以位于点$(k,0)$，目标点为$(n+k,m)$。我们每次可以向右走一步（来一个$10$元），或向上走一步（来一个$20$元）。可以发现，这就是从点$(k,0)$到点$(n+k,m)$的**不到直线$y=x$上方的最短路径数**。

第一组样例的图（蓝线是可以走的地方，$B$点是起点，$A$点是终点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/sggp6zk6.png)

我们直到，在平面直角坐标系中，从点$(a,b)$走到点$(c,d)$，只向上方和右方走的话，共有$\dbinom{c-a+d-b}{c-a}$种方案。我们设这个方案数为$\operatorname{dis}(A,B)$，其中$A,B$是两个点。但是，这不能满足$y=x$的限制。

我们考虑反向思考，有$\text{合法方案数=总方案数-不合法方案数}$。

对于任何一种不合法的方案，路径至少与直线$y=x+1$有一个交点。我们找到这个交点设为$D$，并将路径$B\rightarrow D$关于$y=x+1$翻折得到路径$C\rightarrow D$。

如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/1rhpxlb9.png)

我们可以发现，每一条从$B$到$A$的不合法路径，都唯一对应着从$C$到$A$的路径。

则答案为$\operatorname{dis}(B,A)-\operatorname{dis}(C,A)$。

我们可以发现，$C$的坐标是可以确定的，为$C(-1,k+1)$。

则我们得到答案为$\dbinom{n+m}{n}-\dbinom{n+m}{n+k+1}$。

化简，并除以总数（$(n+m)!$）得

$\LARGE1-\dfrac{\prod\limits_{i=m-k}^{m}i}{\prod\limits_{j=n+1}^{n+k+1}j}$


代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
double res=1;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	if(m<=k){puts("1");return 0;}
	for(int i=0;i<=k;i++)res*=1.0*(m-k+i)/(n+i+1);
	printf("%lf\n",max(1-res,0.0));
	return 0;
}
```


---

## 作者：chihik (赞：5)


不妨设$n+k>=m$ , 且$ n < m $。

![](https://cdn.luogu.com.cn/upload/image_hosting/fp1y8blg.png)

回忆一下卡塔兰数的推导过程 ， 我们用类似的方法解决此题。

首先，我们可将题意转化成从$(0,0)$到$(n,m)$，**不穿过**$y=x+k$的一条路径。

将$y=x+k$向上平移一个单位得$y=x+k+1$(黄色的函数)，原题等价于求一条路径且**不经过**$y=x+k+1$的路径。

从反面思考，我们只需找到**经过**$y=x+k+1$的路径即可。

我们不妨将$A(0,0)$关于$y=x+k+1$作对称得到$A'(-k-1,k+1)$，发现对于每一条$A' \to B$的路径，都会穿过$y=x+k+1$ , 且一定有一条$A \to B$的路径与之对应。(蓝色虚线与红色实线)

那么经过$y=x+k+1$的路径的数量为$C_{n+m}^{n+k+1}$

又因为从起点到终点的路径一共有$C_{n+m}^{n}$

所以答案为$1-\frac{C_{n+m}^{n+k+1}}{C_{n+m}^{n}}$

还有两种特殊情况：

1.$k>=m$ ， 此时直接输出$1$。

2.$n+k<m$ , 此时直接输出$0$。

这道题的$n,m$都很大，建议用自然对数的形式存阶乘。

```cpp
#include <cstdio>
#include <cmath>

const int MAXN = 300000; 
int n , m , k;
double Ans , Fac[ MAXN + 5 ];

void Init( ) {
	Fac[ 0 ] = 0;
	for( int i = 1 ; i <= MAXN ; i ++ )
		Fac[ i ] = Fac[ i - 1 ] + log( i * 1.0 );
}
double C( int n , int m ) {
	return Fac[ n ] - Fac[ m ] - Fac[ n - m ];
}

int main( ) {
	Init( );
	scanf("%d %d %d",&n,&m,&k);
	if( k >= m ) 
		Ans = 1;
	else if( n + k < m ) 
		Ans = 0;
	else
		Ans = 1 - exp( C( n + m , n + k + 1 ) - C( n + m , n ) );
	printf("%.6lf",Ans);
	return 0;
} 
```


---

## 作者：resftlmuttmotw (赞：2)

~~说是复习 其实这道题的知识点我没学过~~

[核心 我是看这篇博客学会的](https://blog.csdn.net/zoucharming/article/details/45312899)

## $Firstly$,转化题面

现在在$(k,0)$的位置

每次可以向上走一步或向右走一步

即从$(a,b)$可以到$(a+1,b)$或$(a,b+1)$

要求不能过$f(x)=x$

求走到$(n+k,m)$的方法数$P$

## $Secondly$,方法
如图 从$B(k,0)$走到$A(n+k,m)$

先不考虑不能过$f(x)=x$

方法数易得：

$$C_{n+m}^{m}$$


然后再算过了的 相减就得$P$

我们找$C$点

$C$与$B$关于$f(x)=x+1$对称

可得$c(-1,k+1)$

![](https://cdn.luogu.com.cn/upload/image_hosting/f135c9yz.png)

只要 B到A是经过了$f(x)=x$的

那么一定有一条对应的$C$到$A$的路径


**证明**：

如果$B$到$A$的路径过$f(x)=x$

那么$B$到$A$的路径一定过$f(x)=x+1$或有点在$f(x)=x+1$上

![](
https://cdn.luogu.com.cn/upload/image_hosting/eg9lziun.png)

如图 $D$点一定存在

定义$g(a,b)$为从$a$点到$b$点的方法数

则$g(c,d)=g(b,d)$

一定有$g(d,a)=g(d,a)$

所以只要 B到A是经过了$f(x)=x$的

那么一定有一条对应的$C$到$A$的路径

现在 就可以得出 

$$P=C_{n+m}^{m}-g(c,a)=C_{n+m}^{m}-C_{n+m}^{m-k-1}$$

再除以方案总数 化简可得

$$1-\frac{\displaystyle\prod_{i=m-k}^{m}i}{\displaystyle\prod_{j=n+1}^{n+k+1}j}$$

## $Code$

```cpp
#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
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
double ans = 1.0;
int main()
{
	int n = Read(1),m = Read(1),k = Read(1);
	if(n + k >= m)
	{
		for(reg i = 1;i <= k + 1;i++)
			ans *= (double)(i + m - k - 1) / (n + i);
		printf("%.5lf",1.0 - ans);
	} else printf("0");
    return 0;
}
```



---

## 作者：夙_晏清 (赞：2)

## 本题是卡特兰数列的变形，
[卡特兰数介绍](https://wenku.baidu.com/view/7261376069dc5022abea006e.html）)

本题把10元看做中有1，20元看做-1，起点在(k,0)处，要走到终点(n + k,m)处，不能超越从原点出发的对角线

![图片解释](![](file:///C:/Users/Administrator/Desktop/11.jpg))

#### 标程：
```
#include<bits/stdc++.h>

using namespace std;

int n , m , k ;

double ans = 1;

int main(){
    //freopen("ticket.in" , "r" , stdin);
    //freopen("ticket.out" , "w" , stdout);
    scanf("%d%d%d" , &n , &m , &k);
  /*  if(k > 0 && m > 0){
    ans = ((double) (n * 5 + k * 5) / (double) (m * 10 + k * 5));
}*/
    if(m > n + k) ans = 1;
    else if(m <= k) ans = 0; 
    else {
    for(int i = 0 ; i < k + 1 ; i ++){
    	ans *= (double)/*1.0 * */(m - i) / (n + k + 1 - i);
    }
}
//	if(n * 5 >= m * 10 && k == 0) ans = ((double) (m * 10) / (double) (n * 5));
//  else if(n * 5 >= m * 10 && k != 0) ans = ((double) (m * 10 + k * 5) / (double) (n * 5 + k * 5));
    printf("%.6f\n" , 1 - ans);
    //cout<<"0.857143";
}
```


---

## 作者：ZCETHAN (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF26D)

## 题目大意
卖足球赛的票，票价是 10^元^/~张~，你手中有 $k$ 张 10 元钱，并且知道有 $n$ 个人来买票时会带 10 元，$m$ 个人会带 20 元钱。你可以顺利卖票，即每次都能找得出钱的概率是多少。

## Solution
首先分析顺利卖票，由于票价是 10 元，所以带 10 元的人是不需要你找钱，相反，他们来买票还可以为你提供找 20 元的钱。所以，得出结论，10 元是好的，20 元是不好的。

我们可以先算有多少合法的序列，然后除以总方案即可。

于是，我们开始转化模型。
### step 1
由上面的结论可以轻易推出，如果一种买票的顺序，使得某一次，之前带 20 元来买票的人比带 10 元的人加上原有的 $k$ 张 10 元还要多了，那么就找不开钱，也就是没有顺利卖票了。

这很容易联想到栈，进一步的，就是典型的**卡特兰数**的变形。

问题就是，栈中原有 $k$ 个元素，现在有 $n$ 次入栈操作，$m$ 次出栈操作，问有多少种操作顺序。
### step 2
显然，这样仍不足以解决这个问题，因为毕竟不是卡特兰数的模板。我们回顾一下卡特兰数的推导：
>在一个坐标系中，从原点出发，可以向上走 $m$ 步，向右走 $n$ 步，请问有多少种方式，可以不越过直线 $y=x$ 并且到达点 $(n,m)$。

在这题中，可以把初始的 $k$ 个元素转化为：在坐标轴上，从坐标 $(k,0)$ 出发。

所以题目又转化为：  
**在一个直角坐标系中，从点 (0,k) 出发，可以向上 m 或向右 n 步，且必须在直线 y=x 的下方（包括边界），求有多少种合法的非降路径。**
### step 3
最后，为了解决上面的问题，我们仍然从卡特兰数的推导中获得启发。即利用 $P(A)=1-P(\overline{A})$。

直接算不合法的概率，当然首要还是先算不合法的方案数。

显然，可以先得出总方案数是 $C_{n+m}^n$，其中不合法的方案，反映在坐标轴上一定是经过直线 $y=x+1$ 的，由卡特兰数的路径计数推导，可以得出，我们只要将起点关于直线 $y=x+1$ 对称，即将起点变成 $(-1,k+1)$，然后可以得出，不合法的方案数是 $C_{n+m}^{k+n+1}$。因此不合法的概率就是：
$$\frac{C_{n+m}^{k+n+1}}{C_{n+m}^n}$$

因此合法的概率就是：
$$1-\frac{C_{n+m}^{k+n+1}}{C_{n+m}^n}$$
$$=1-\frac{\frac{(n+m)!}{(m-k-1)!(k+n+1)!}}{\frac{(n+m)!}{n!m!}}$$
$$=1-\frac{n!m!}{(m-k-1)!(k+n+1)!}$$

所以最后的代码就是个式子，很短。
## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1<<30
#define INF 1ll<<60
#define pb push_back
using namespace std;
int main()
{
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	if(n+k<m){puts("0");return 0;}//先判无解
	int up=m,down=k+n+1;
	double ans=1;
	for(int i=0;i<=k;i++,up--,down--)
		ans=ans*1.0*up/down;
	printf("%.5lf\n",1-ans);
}
```


---

## 作者：XL4453 (赞：0)

### 解题思路：

又是一道卡特兰数变体，提供一种和其他题解都不一样的推导方法（应该也算是常见的一种）。

考虑将所有的收 $10$ 元操作视为向右上移动一个单位，将所有的收 $20$ 元找 $10$ 元视作向右下移动一个单位。

那么整个方案数就是从一开始的 $(0,k)$ 走到 $(n+m,k-m+n)$，其中走过的路径一定不能碰到 $y=-1$ 这一条线，这样的总方案数是从 $n+m$ 个操作里选择 $n$ 个操作（或者 $m$ 个操作）：$C_{n+m}^{n}$（或者 $C_{n+m}^{m}$）。这些方案里包含了可行的和不可行的。

然后像一般的卡特兰数推导一样，将所有碰到的线向下翻折，得到不可行方案数，也就是在 $n+m$ 个操作里选择 $n+k+1$ 个操作（或者 $m-k-1$） 个操作，得到：$C_{n+m}^{n+k+1}$（或者 $C_{n+m}^{m-k-1}$）。

这样一来，可行的方案就是 $C_{n+m}^{n}-C_{n+m}^{n+k+1}$，除以所有可能的方案数得到：$1-\dfrac{C_{n+m}^{n+k+1}}{C_{n+m}^{n}}$。

化简一下，立刻有：$1-\dfrac{n!m!}{(n+k+1)!(m-k-1)!}$，直接一个循环搞定。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,m,k;
double ans;
int main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	if(m>n+k){
		printf("0");
		return 0;
	}
	ans=1;
	for(int i=0;i<=k;i++){
		ans*=(double)(m-k+i)/(double)(n+i+1);
	}
	printf("%.6lf",max(1-ans,0.0));
	return 0;
}
```


---

