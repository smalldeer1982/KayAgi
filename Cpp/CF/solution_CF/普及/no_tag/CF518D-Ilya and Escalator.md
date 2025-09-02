# Ilya and Escalator

## 题目描述

Ilya got tired of sports programming, left university and got a job in the subway. He was given the task to determine the escalator load factor.

Let's assume that $ n $ people stand in the queue for the escalator. At each second one of the two following possibilities takes place: either the first person in the queue enters the escalator with probability $ p $ , or the first person in the queue doesn't move with probability $ (1-p) $ , paralyzed by his fear of escalators and making the whole queue wait behind him.

Formally speaking, the $ i $ -th person in the queue cannot enter the escalator until people with indices from $ 1 $ to $ i-1 $ inclusive enter it. In one second only one person can enter the escalator. The escalator is infinite, so if a person enters it, he never leaves it, that is he will be standing on the escalator at any following second. Ilya needs to count the expected value of the number of people standing on the escalator after $ t $ seconds.

Your task is to help him solve this complicated task.

## 样例 #1

### 输入

```
1 0.50 1
```

### 输出

```
0.5
```

## 样例 #2

### 输入

```
1 0.50 4
```

### 输出

```
0.9375
```

## 样例 #3

### 输入

```
4 0.20 2
```

### 输出

```
0.4
```

# 题解

## 作者：VenusM1nT (赞：13)

期望 $\textbf{DP}$。  
显然是假的难度……  
令 $f_{i,j}$ 表示考虑到第 $i$ 个人，时间为第 $j$ 秒的期望人数，分别考虑走不走上电梯：

 - 如果上电梯，则 $f_{i,j}$ 由 $f_{i-1,j-1}$ 转移过来，概率为 $p$；
 - 如果不上电梯，则 $f_{i,j}$ 由 $f_{i,j-1}$ 转移过来，概率为 $(1-p)$。

综上，可以得出转移方程：
$$f_{i,j}=(1-p)\times f_{i,j-1}+p\times (f_{i-1,j-1}+1)$$

直接 $\text{O}(nt)$ 就可以搞了。

---

## 作者：基地A_I (赞：10)

~~期望小白现学现卖~~ ,概率/期望dp真是太好玩了！

期望的定义：

$$E(x)=\sum P(x)*x$$

文字定义：一系列事件发生的可能性，和这些事件的价值（一种更通俗的解释是加权平均）

回到题目：

有n个人，每个人进电梯的概率是 $p$

问 $t$ 秒后电梯里的期望人数

很明显，时间 $t$ 和电梯里的人数 $n$ 可以做为dp的阶段进行划分，所以：

设 $f [ i ][ j ]$ 表示 $i$ 秒后电梯里有 $j$ 人的概率

考虑局面的变化，每一秒局面都有两条分支

- $f[i+1][j]$ 表示没有人进入电梯，进入这条分支的概率是 $(1-p)$
 
- $f[i+1][j+1]$ 表示有一个人进入电梯，进入这条分支的概率是 $p$

所以推出概率dp动态转移方程：

$$f[i][j]=f[i-1][j]*(1-p)+f[i-1][j-1]*p$$

这里涉及到一些概率的小知识

和事件：相当于并集的概率，只需其中一件发生就算发生 $P(C) = P(A) + P(B)$ 

积事件：相当于交集的概率，必须全部发生才算发生 $P(C)=P(A)*P(B)$

以上摘自洛谷提高组讲义 (当然如果这些知识还是不会的话建议先学概率/期望基础qwq)

回归题目：

我们推出这个方程后，还要考虑一些边界的特殊情况

- $f[i][0]=f[i-1][0]*(1-p)$ 因为当前电梯里面没有人，所以只能从没有人转移过来

- $f[i][n]=f[i-1][n]+f[i-1][n-1]*p$ 因为当前电梯里的人满了，也就说明电梯外没有人，所以一定可以从上一个$n$人的状态转移过来(即$100\%$的概率)，和上一个$n-1$人的状态 $p$ 概率转移过来

最后统计答案，第 $t$ 秒电梯里有 $i$ 个人的概率是 $f[t][i] $，回到我们期望的定义，得出答案：

$$ans=\sum_{i=0}^n f[t][i]*i$$

Code

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#define N 2007
using namespace std;
int n,t;
double p;
double f[N][N];	//i秒后电梯里有j个人的概率 
int main()
{
	scanf("%d%lf%d",&n,&p,&t);
	f[0][0] = 1.0;
	for(int i=1;i<=t;++i)
		for(int j=0;j<=n;++j) {
			if(j == 0) f[i][j] = f[i-1][j]*(1-p);	//现在有0人，只能从0人转移过来 
			if(j == n) f[i][j] = f[i-1][j] + f[i-1][j-1]*p;	//现在有n人，只能从n人或n-1人转移 
			else f[i][j] = f[i-1][j]*(1-p) + f[i-1][j-1]*p;
		}
	double ans = 0.0;
	for(int i=0;i<=n;++i)
		ans += f[t][i] * i;
	printf("%lf",ans);
	return 0;
}
```

期望dp入门题 ``普及-`` 吧，有点恶意评分了

各位看官见我这个期望小白写了这么多不妨点个赞吧！

---

## 作者：DreamFox (赞：4)

设 $dp_{i,j}$ 为 $i$ 秒后，电梯上有 $j$ 个人的概率，那么答案是：

$$\sum\limits_{k=0}^{n} dp_{T,k} \times k$$

所以我们只需要求 $dp_{i,j}$ 就可以了，初始值 $dp_{0,0}=1$，采用刷表法。

式子如下：

$$dp_{i+1,j+1}=dp_{i,j} \times p$$

$$ dp_{i+1,j} = dp_{i,j} \times (1-p) $$

AC 代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n, t;
double p, f[2010][2010], ans;
int main() {
	cin >> n >> p >> t;
	f[0][0] = 1.0;
	for(int i = 0; i < t; i ++) { 
		for(int j = 0; j < n; j ++) 
			f[i + 1][j + 1] += f[i][j] * p, f[i + 1][j] += f[i][j] * (1.0 - p);
		f[i + 1][n] += f[i][n];
	}
	for(int i = 0; i <= n; i ++)
		ans += f[t][i] * i;
	printf("%.10lf\n", ans);
	return 0;
}
```


---

## 作者：da32s1da (赞：4)

我们设$f[i][j]$为考虑到第$i$个人，在第$j$秒的期望人数。

显然$f[i][j]$有$(1-p)$的概率由$f[i][j-1]$转移过来，有$p$的概率由$f[i-1][j-1]$转移过来。

于是有状态转移方程$$f[i][j]=(1-p)\times f[i][j-1]+p\times (f[i-1][j-1]+1)$$

然后就做完了。。。
```
#include<cstdio>
const int N=2018;
typedef double D;
D f[N][N],p;
int n,t;
int main(){
	scanf("%d%lf%d",&n,&p,&t);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=t;j++)  
	f[i][j]=(1-p)*f[i][j-1]+p*(f[i-1][j-1]+1);
	printf("%.12f\n",f[n][t]);
}
```

---

## 作者：x7103 (赞：2)

[**蒟蒻的blog**](https://blog.csdn.net/m0_46374167/article/details/114445527?spm=1001.2014.3001.5501)
## Solution

 - 由于 $n,t\le 2\times 10^3$，考虑 $O(nt)$ 做法。
 - 设 $g_{i,j}$ 表示在第 $i$ 秒，电梯上有 $j$ 个人的概率。
 - 初始状态，$g_{0,0}=1$。
 - 易得状态转移方程为
$$
g_{i,j}=\begin{cases}
g_{i-1,j}\times(1-p),&j=0\\
g_{i-1,j-1}\times p+g_{i-1,j}\times(1-p)&0<j<n\\
g_{i-1,j-1}\times p+g_{i-1,j},&j=n
\end{cases}
$$
 - 答案即为 $\sum_{i=0}^{n}i*g_{t,i}$
## Code
```cpp
#include<cstdio>
using namespace std;
const int maxn=2020;
int n,t;
double p,g[maxn][maxn],ans;
int main(){
	scanf("%d%lf%d",&n,&p,&t);
	g[0][0]=1;
	for(int i=1;i<=t;++i){
		g[i][0]=g[i-1][0]*(1-p);
		for(int j=1;j<n;++j)
			g[i][j]=g[i-1][j-1]*p+g[i-1][j]*(1-p);
		g[i][n]=g[i-1][n-1]*p+g[i-1][n];
	}
	for(int i=0;i<=n;++i)
		ans+=i*g[t][i];
	printf("%.9lf",ans);
	return 0;
}
```


---

## 作者：XL4453 (赞：1)

### 解题思路：

用 $f_{i,j}$ 表示考虑到第 $i$ 秒，剩下 $j$ 个人的概率。

考虑转移，当 $j=0$ 有：$f_{i,0}=f_{i-1,0}+p\times f_{i-1,1}$，否则有：$f_{i,j}=(1-p)\times f_{i-1,j}+p\times f{i-1,j+1}$。

最后的期望就是 $\sum_{i=1}^ni\times f_i$。

---

可以用矩阵乘法优化转移，但本题数据范围较小，没有必要。

---
### 代码：

```
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
double p,ans,f[2005];
int main(){
    scanf("%d%lf%d",&n,&p,&m);
    f[n]=1;
    for(int i=1;i<=m;i++){
        f[0]+=f[1]*p;
        for(int i=1;i<=n;i++)
        f[i]=f[i]*(1-p)+f[i+1]*p;
    }
    for(int i=0;i<=n;i++){
        ans+=f[i]*(n-i);
    }
    printf("%.8lf",ans);
    return 0;
}
```


---

## 作者：hanzhongtlx (赞：1)

这里重点讲一下 $t\leq n$ 时的 $\mathcal O(1)$ 做法，对于其他情况用 $\mathcal O(n^2)$ 解法即可（其实也有式子，只是不适合此题）。  

当 $t\leq n$ 时，人**一定**够用。  

考虑期望的定义，在这个题中，容易知道;  

$$E(x)=\sum_{i=1}^t i\dbinom{t}{i}p^{i}(1-p)^{t-i}$$  

考虑组合数的一个性质 

$$\dbinom{t}{i}i=\dfrac{t!\times i}{(t-i)!\times i!}=t\dfrac{(t-1)!}{(t-1-(i-1))!\times(i-1!)}=t\dbinom{t-1}{i-1}$$  

考虑将式子枚举项改变：  

$$E(x)=t\sum_{i=0}^{t-1}\dbinom{t-1}{i}p^{i}(1-p)^{t-1-i}$$

我们发现提出一个 $p$ 就能构造二项式定理：  

于是有：

$$E(x)=tp(p+1-p)^{t-1}=tp$$   

故直接输出 $tp$ 即可。

给出代码： 

```
#include"cstdio"
#include"cmath"
#include"cstring"
#include"iostream"
using namespace std;

#define MAXN 2005

double p,q;
int n,t;
double dp[MAXN][MAXN];

int main()
{
    scanf("%d%lf%d",&n,&p,&t);
    if(t<=n) return printf("%.6lf\n",p*t),0;
    else
    {
    	for(int i=1;i<=t;i++) dp[i][0]=0.00;
    	for(int j=1;j<=n;j++) dp[0][j]=0.00;
    	for(int i=1;i<=t;i++)
    	{
    		for(int j=1;j<=n;j++)
    		{
    			dp[i][j]=(p*(dp[i-1][j-1]+1.00)+(1-p)*dp[i-1][j]);
			}
		}
		printf("%.6lf\n",dp[t][n]);
	}
    return 0;
}
```

---

## 作者：eros1on (赞：1)

~~[博客食用更佳](https://tle666.github.io/2019/06/05/[CF518D]%20Ilya%20and%20Escalator/)~~

# **Description**

有 $n$ 个人排成一列，每秒中队伍最前面的人 $p$ 的概率走上电梯（一旦走上就不会下电梯）或者有 $(1-p)$ 的概率不动。问 $t$ 秒过后，在电梯上的人的数量的期望。

对于 $100 \%$ 的数据，满足 $n,t\leq2000$

[题目链接戳这里](https://www.luogu.org/problemnew/show/CF518D)

> 注：如果下面 LaTeX 显示出现问题，请到我的博客中查看~

# **Solution**

期望 $DP$ 。

设 $dp_{i,j}$ 表示第 $i$ 秒已经走上 $j$ 个人的概率。

则有

 $$ans = \sum_{i = 1}^n dp_{t, i}$$

转移方程如下（一定注意边界！）：

$$dp_{i, j}=\left\{ \begin{array}{ll}dp_{i -1,0}\times(1-p)  & j=0\\dp_{i - 1, j - 1}\times p+dp_{i-1,j}\times (1-p) & 1\le j<n \\dp_{i - 1, n}+dp_{i - 1, n - 1}\times p & j=n\end{array} \right.\ \ \\\ $$

# **Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2020;

int n, t;

double p, dp[N][N], ans;

inline void DP() {
  dp[0][0] = 1.0;
  for (int i = 1; i <= t; i++) {
    dp[i][0] = (1.0 - p) * dp[i - 1][0];
    for (int j = 1; j < n; j++)
      dp[i][j] = dp[i - 1][j - 1] * p + (1.0 - p) * dp[i - 1][j];
    dp[i][n] = dp[i - 1][n] + p * dp[i - 1][n - 1];
  }
}

int main() {
  scanf("%d%lf%d", &n, &p, &t);
  DP();
  for (int i = 1; i <= n; i++)
    ans += (double) (i * dp[t][i]);
  printf("%lf\n", ans);
  return 0;
}
```



---

## 作者：nekko (赞：1)

一顿操作猛如虎，一看数据范围$n,t \le 2000$

于是一个大胆的$dp$做法跃然纸上

设$f_{i,j}$表示前$i$秒，电梯中有$j$个人的概率

那么答案就是$\sum_{i=0}^{n}i \times f_{t,i}$

考虑如何更新答案：

首先有$f_{0,0}=1$，因为时刻$0$电梯里一定只有$0$个人

考虑$f_{i,0}$，那么只能是由上一秒仍然没人转移过来，也就是说$f_{i,0}=f_{i-1,0} \times (1-p)$

考虑$f_{i,n}$，如果上一秒已经有了$n$个人，那么这一秒一定只会有$n$个人；如果上一秒有$n-1$个人，那么这一秒有$p$的概率会变为$n$个人；即$f_{i,n}=f_{i-1,n}+f_{i-1,n-1} \times p$

对于其余情况，显然有$f_{i,j}=f_{i-1,j} \times (1-p) + f_{i-1,j-1} \times p$

``` cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
int n, t;
double p, f[N][N];

int main() {
	cin >> n >> p >> t;
	
	f[0][0] = 1;
	for(int i = 1 ; i <= t ; ++ i)
		for(int j = 0 ; j <= n ; ++ j)
			if(j == n)
				f[i][j] = f[i - 1][j - 1] * p + f[i - 1][j];
			else if(j == 0)
				f[i][j] = f[i - 1][j] * (1 - p);
			else
				f[i][j] = f[i - 1][j - 1] * p + f[i - 1][j] * (1 - p);
	
	double ans = 0;
	for(int i = 0 ; i <= n ; ++ i)
		ans += i * f[t][i];
	printf("%.12lf\n", ans);
}
```

---

## 作者：Plozia (赞：0)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/113954628)

这道题的 DP 还是比较简单的。

设 $f_{i,j}$ 表示第 $i$ 个人在第 $j$ 秒做出决策时的期望，那么：

1. 走上电梯，那么为 $(f_{i-1,j-1}+1) \times p$。
2. 不走上电梯，那么为 $f_{i,j-1} \times (1-p)$

综上，我们有：

$$f_{i,j}=(f_{i-1,j-1}+1) \times p+f_{i,j-1} \times (1-p)$$

然后递推即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef double db;
typedef long long LL;
const int MAXN = 2000 + 10;
int n, t;
double p, f[MAXN][MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
	return (fh == -1) ? -sum : sum;
}

int main()
{
	n = read(); scanf("%lf", &p); t = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= t; ++j)
			f[i][j] = f[i][j - 1] * (1 - p) + (f[i - 1][j - 1] + 1) * p;
	printf("%.10lf\n", f[n][t]);
	return 0;
}
```

---

## 作者：Arghariza (赞：0)

设 $dp_{i,j}$ 为第 $i$ 秒到第 $j$ 个人的概率。

- 这个人走上去的概率是前一秒（第 $i-1$ 秒）前一个人（第 $j-1$ 人）走上去的概率乘以 $p$ ，再加上自己走上去的概率，也就是 $(dp_{i-1,j-1}+1)\cdot p$ 
- 这个人不走上去的概率是前一秒也没有走上去的概率乘以 $1-p$ ，也就是 $dp_{i-1,j} \cdot (1-p)$ 

加起来就是 $dp_{i,j}=(dp_{i-1,j-1}+1)\cdot p+dp_{i-1,j} \cdot (1-p)$ 

时间复杂度 $O(nt)$ ，空间复杂度 $O(nt)$ 。

```cpp
#include <bits/stdc++.h>
#define maxn 2020
using namespace std;

int n, t;
double dp[maxn][maxn];
double p;

int main() {
	scanf("%d%lf%d", &n, &p, &t);
	for (int i = 1; i <= t; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = dp[i - 1][j] * (1 - p) + (dp[i - 1][j - 1] + 1) * p;
		}
	}
	printf("%lf", dp[t][n]);
	return 0;
}
```

然后因为每次转移 $j$ 的那个维度只依赖于 $j,j-1$ ，所以可以直接滚了：

```cpp
#include <bits/stdc++.h>
#define maxn 2020
using namespace std;

int n, t, k;
double dp[maxn][2];
double p;

int main() {
	scanf("%d%lf%d", &n, &p, &t);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= t; j++) {
			dp[j][k] = dp[j - 1][k] * (1 - p) + (dp[j - 1][!k] + 1) * p;
		}
		k = !k;
	}
	printf("%lf", dp[t][!k]);// 注意最后要取反qwq
	return 0;
}
```

空间复杂度 $O(t)$ 

---

## 作者：czyczyczyczyczy (赞：0)

# [题解] 概率$DP$

## [原题链](https://www.luogu.com.cn/problem/CF518D)

## 解题思路

~~这是第一道自己做出来的概率$dp$题~~

这个题其实有两种做法(似乎还没有$dalao$把两种方法一起讲了)。

### 第一种：设期望

设$f[i][j]$表示当前考虑第$i$个人，在$j$时刻电梯里的期望人数，那么很容易得到转移方程：要么是进来一个人，要么是没进来人，所以$f[i][j]=(f[i-1][j - 1]+1)*p+f[i][j-1]*(1-p)$

### 第二种：设概率

设$f[i][j]$表示 $i$时刻电梯里有$j$个人的概率。同样很轻松的得到转移方程：$f[i][j]=f[i - 1][j]*(1-p)+f[i -1][j-1]*p$，不过要注意的是如果已经有$n$个人了的话，就不能再用之前的转移方程了。因为如果上一个时刻电梯已经有$n$个人的话现在一定还是$n$个人，不用乘概率。也就是说$f[i][n] = f[i-1][n]+f[i-1][n-1]*p$。如果一开始电梯上还没有人，那么从$f[i-1][j-1]$转移过来是不合法的，因为不存在$-1$个人。

这两种做法唯一的区别就是转移方程中对于**电梯进来人**这个状态的描述，如果是算期望我们知道期望等于**权值乘以概率，所以如果电梯进来人的话要表示成**$(f[i-1][j-1]+1)*p$，而如果是设概率的话则不用考虑人数（权值）的变化。当然两个的答案统计方法也不一样。如果是期望的话直接输出就好了。如果是概率的话依然考虑期望的定义，需要枚举最终的时刻电梯内不同人数的概率，答案就是$\sum_{i=1}^nf[T][i]*i$

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
double f[2010][2010];
int main(){
    int n,T;
    double p;
    scanf("%d%lf%d",&n,&p,&T);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= T;j++){//设期望
            f[i][j] = (f[i - 1][j - 1] + 1) * p + f[i][j - 1] * (1 - p);
        }
    }
    printf("%.7lf",f[n][T]);
    return 0;
}
```
----

````cpp
#include <bits/stdc++.h>
using namespace std;
double f[2010][2010];
int main(){
    int n,T;
    double p;
    scanf("%d%lf%d",&n,&p,&T);
    f[0][0] = 1.000;
    for(int i = 1;i <= T;i++){//设概率
    	for(int j = 0;j <= n;j++){
            if(j == n)//特殊情况，只能从n或n-1转移
                f[i][j] = f[i - 1][j] + f[i - 1][j - 1] * p;
            else if(j == 0)//特殊情况，只能从f[i-1][0]转移
                f[i][j] = f[i - 1][j] * (1 - p);
            else f[i][j] = f[i - 1][j] * (1 - p) + f[i - 1][j - 1] * p;
        }
    }
    double ans = 0.0;
    for(int i = 0;i <= n;i++)ans += f[T][i] * i;//有概率推算期望
    printf("%.7lf",ans);
    return 0;
}

````



---

## 作者：When (赞：0)

#### 算法

期望DP入坑题

#### 思路

设$f_{i,j}$为第$i$时刻，电梯上正好有$j$人的概率，于是有：

$$\left\{\begin{array}{l}{f_{i + 1,j + 1}=f_{i,j}\times p}\\{f_{i+1,j}=f_{i,j}\times (1-p)} \end{array} \right. $$

采用刷表法进行DP。边界条件：$f_{0,0}=1$。

**注意:**

+ 每次要额外处理$f_{i,n}$，因为这一情况下不能再有人上电梯了；
+ 这样DP完以后只求出了概率，最后$Ans = \sum^{n}_{i=1}{f_{t,i}\times i}$。
+ 由于使用了刷表法，所以时间那一维只需要循环$t-1$次！

#### 参考代码

```cpp
/*
 * @Author: When_C 
 * @Date: 2020-11-17 19:19:48 
 * @Last Modified by: When_C
 * @Last Modified time: 2020-11-17 19:36:01
 */
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 2010;

int n,t;
double p,f[maxn][maxn],Ans;

int main(){
    scanf("%d%lf%d", &n, &p, &t);
    f[0][0] = 1;
    for(int i = 0; i < t; ++ i){
        f[i + 1][n] += f[i][n];
        for(int j = 0; j < n; ++ j){
            f[i + 1][j + 1] += f[i][j] * p;
            f[i + 1][j] += f[i][j] * (1 - p);
        }
    }
    for(int i = 1; i <= n; ++ i) Ans += f[t][i] * i;
    printf("%lf\n", Ans);
    return 0;
}
```



---

