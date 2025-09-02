# Bath Queue

## 题目描述

有 $n$ 个学生住在学校里。学校中有 $m$ 个洗漱间，其中第 $i$ 个洗漱间中有 $a_i$ 个水盆。

每天早上所有的学生同时醒来并去洗漱。每一个学生随机进入一个洗漱间。随后，每一个房间内的学生尽量平均地分配到每一个水盆前，使得最长的队伍尽可能短。

请你求出所有的洗漱间中最长队伍的期望长度。

## 样例 #1

### 输入

```
1 1
2
```

### 输出

```
1.00000000000000000000
```

## 样例 #2

### 输入

```
2 2
1 1
```

### 输出

```
1.50000000000000000000
```

## 样例 #3

### 输入

```
2 3
1 1 1
```

### 输出

```
1.33333333333333350000
```

## 样例 #4

### 输入

```
7 5
1 1 2 3 1
```

### 输出

```
2.50216960000000070000
```

# 题解

## 作者：PPL_ (赞：6)

# 前言

经小提示做出来的DP，~~因为题解没看懂，淦~~

# 题目

[洛谷](https://www.luogu.com.cn/problem/CF28C)

[CF](http://codeforces.com/problemset/problem/28/C)

题目大意：

有$n(1≤n≤50)$个学生同时洗衣服，有$m(1≤m≤50)$个洗衣房，第$i$个洗衣房里有$a_i(1≤a_i≤50)$台洗衣机。

每个学生会从$m$个洗衣房里随机选择一个，选择同一个洗衣房的学生会按照房间里洗衣机的数量平均排队，求最长队列人数的期望，输出误差不大于$10^{-9}$。

平均排队是指不存在两个队列人数相差大于二。

# 讲解

既然我们期望学的差，就不要试图直接DP转移期望了~~(所以没看懂题解qwq)~~

所以我们DP求**方案数**！

我们令$dp[i][j][k]$为前$i$个房间去$j$个人，最长队列**恰好**为$k$的方案数，转移为当前房间进入$l$个人，由$i-1$转移而来

考虑状态转移方程怎么写

第一维：$i-1$到$i$

第二维：$j$到$j+l$

第三维：$k$到$max(⌈\frac{l}{a_i}⌉,k)$

那么$dp[i][j][k]$提供的贡献是多少呢？因为人是不一样的，所以我们要从剩下的$n-j$人中选出$l$个人来，所以要乘上$C_{n-j}^{l}$

所以总的状态转移方程即为：

$$dp[i][j+l][max(ceil(l/a[i]),k)]=\sum dp[i-1][j][k]*C_{n-j}^{l}$$

由于多个$\sum$会使得转移方程看起来过于冗长且没有什么太大意义，所以我省略掉了

所以总方案数为：$T=\sum_{i=0}^n dp[m][n][i]$

期望与带权平均差不多，而每个$dp[m][n][i]$的权值即为$i$

所以答案为：

$$\sum_{i=1}^{n}\frac{i*dp[m][n][i]}{T}$$

什么？你问我为什么$i$从$1$开始？难道和从$0$开始有什么区别吗？

注意：

1.输入的$n,m$分别指人和房间数，不要搞反了

2.输出位数不要太少了

3.建议用$\texttt{double}$存，万一用$\texttt{long long}$出事了呢

# 代码

```cpp
int n,m,a[MAXN];
double C[MAXN][MAXN],dp[MAXN][MAXN][MAXN],ans,T;
void pre()
{
	C[0][0] = 1;
	for(int i = 1;i <= 50;++ i)
	{
		C[i][0] = 1;
		for(int j = 1;j <= i;++ j) C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	pre();
	n = Read(); m = Read();
	for(int i = 1;i <= m;++ i) a[i] = Read();
	dp[0][0][0] = 1;
	for(int i = 1;i <= m;++ i)
		for(int j = 0;j <= n;++ j)
			for(int k = 0;k <= j;++ k)
				for(int l = 0;l <= n-j;++ l)
					dp[i][j+l][Max(((l+a[i]-1)/a[i]),k)] += dp[i-1][j][k]*C[n-j][l];
	for(int i = 0;i <= n;++ i) T += dp[m][n][i];
	for(int i = 1;i <= n;++ i) ans += i * dp[m][n][i] / T;
	printf("%.10f",ans);
	return 0;
}
```



---

## 作者：MikukuOvO (赞：2)

注：$Latex$在博客里看好像没问题$w$

首先我们发现这个期望不太好计算，我们可以计算出如果最长的队列长度为$l$的方案数，那么期望就是：

$P= \frac{\sum_{i=0}^{n}i \times ans[i]}{\sum_{i=0}^{n}ans[i]}$

我们考虑$f[i][j][l]$表示考虑前$i$个房间，分配了$j$个学生，目前最长的队列长度为$l$的方案数。

那么假设我们考虑到$f[i][j][l]$，为了使最长长度为$l$，我们这里可以大力分类讨论一下：

如果第$i$个房间的队列长度为$l$，那么前面的房间就可以全部任意。

否则前$i-1$个房间一定存在一个队列长度为$l$的房间。

这样我们不难写出递推式：

$p_i$表示第$i$个房间使得队列长为$l$的人数集合。

$
f[i][j][l]=\sum_{p \in p_i} \sum_{k=0}^{l}f[i-1][j-p][k] \times
\begin{pmatrix} n-(j-p) \\ p \end{pmatrix}
\quad
+\sum_{k=0}^{min(p_i)-1}f[i-1][j-k][l] \times
\begin{pmatrix} n-(j-k) \\ k \end{pmatrix}
\quad
$

代码：

```cpp
const int N=55;

int n,m;
int a[N];
db c[N][N],f[N][N][N];

int main()
{
	fio();
	gi(n),gi(m);
	for(int i=1;i<=m;++i) gi(a[i]);
	for(int i=0;i<=n;++i) c[i][0]=1;
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) c[i][j]=c[i-1][j]+c[i-1][j-1];
	f[0][0][0]=1;
	for(int i=1;i<=m;++i)
	{
		for(int j=0;j<=n;++j)
		{
			for(int l=0;l<=j;++l)
			{
				for(int p=a[i]*(l-1)+1;p<=a[i]*l&&p<=j;++p)
				{
					for(int k=0;k<=l;++k)
					{
						f[i][j][l]+=c[n-(j-p)][p]*f[i-1][j-p][k];
					}
				}
				for(int k=0;k<=a[i]*(l-1)&&k<=j;++k) f[i][j][l]+=c[n-(j-k)][k]*f[i-1][j-k][l];
			}
		}
	}
	db sum=0,val=0;
	for(int i=0;i<=n;++i) sum+=f[m][n][i],val+=f[m][n][i]*i;
	printf("%.20lf\n",val/sum);
	end();
}
```

---

## 作者：UperFicial (赞：1)

切掉的一道题，感觉不错就放在这里了。

期望明显不好做，可以考虑计数，设 $h_i$ 表示队列最长长度为 $i$ 的方案数，那么答案为 $\dfrac{\sum_{i=0}^{n}h_i\times i}{\sum_{i=0}^nh_i}$。

考虑如何计算最长队伍长度为 $i$ 的方案数，既然值域都这么小就把涉及的量都装进 DP 状态里。

设 $f_{i,j,k}$ 表示，考虑了前 $i$ 个房间，前 $j$ 个学生，且最长队列长度为 $k$ 的方案数。

转移很简单，枚举一下第 $i$ 个房间被 $l$ 个人进入，然后第 $i$ 个房间最长队伍即为 $\lceil\frac{l}{a_i}\rceil$，然后这 $l$ 个学生，是从前 $(i-1)$ 个房间剩余的 $(n-j)$ 个学生中随意选的，所以方案数为 $\binom{n-j}{l}$。

那么就得到了状态转移方程：

$$f_{i,j+l,\max(\lceil\frac{l}{a_i}\rceil,k)}\leftarrow f_{i,j+l,\max(\lceil\frac{l}{a_i}\rceil,k)}+f_{i-1,j,k}\times \binom{n-j}{l}$$

通过杨辉三角预处理一下组合数就可以做到 $O(n^4)$ 的复杂度了。

---

## 作者：C6H14 (赞：1)

## 广告

[题目传送门](https://www.luogu.com.cn/problem/CF28C)

[My blog](https://www.luogu.com.cn/blog/128433/#)

## 思路

题面有误：应当是要计算期望值，~~垃圾翻译~~。

数据范围这么小，直接 dp 即可。

令 $f(i,j,k)$ 表示前 $i$ 个房间已经有 $j$ 个学生，最长队伍的长度为 $k$ 的方案数。

那么下一个房间额外安排 $x$ 个人的方案数为 $C_{n-j}^l$，将 $f(i,j,k)$ 转移到每个 $f(i+1,j+x,\max(k,\left\lceil\dfrac{x}{a_{i+1}}\right\rceil))$ 即可。

答案即为 $\dfrac{\sum \limits_{i=1}^{n} if(m,n,i)}{\sum \limits_{i=0}^n f(m,n,i)}$，时间复杂度为 $\Theta (n^4)$。

## 代码
```cpp
int n,m,a[55];
ll c[55][55];
double f[55][55][55],ans,avg;
int main()
{
	n=read(),m=read();
	c[0][0]=1;
	for (int i=1;i<=50;++i)
		for (int j=0;j<=i;++j)
			if (j==0)
				c[i][j]=1;
			else
				c[i][j]=c[i-1][j]+c[i-1][j-1];
	for (int i=1;i<=m;++i)
		a[i]=read();
	f[0][0][0]=1;
	for (int i=0;i<m;++i)
		for (int j=0;j<=n;++j)
			for (int k=0;k<=n;++k)
				if (f[i][j][k])
					for (int l=0;l+j<=n;++l)
						f[i+1][j+l][max(k,l/a[i+1]+(l%a[i+1]?1:0))]+=f[i][j][k]*c[n-j][l];
	for (int i=0;i<=n;++i)
		avg+=f[m][n][i];
	for (int i=1;i<=n;++i)
		ans+=f[m][n][i]*i;
	printf("%.10f",ans/avg);
	return 0;
}
```

---

## 作者：linyihdfj (赞：0)

## CF28C Bath Queue
想要更优质的阅读体验，就来[这里](https://www.cnblogs.com/linyihdfj/p/16893607.html)吧。
### 题目分析：
显然可以考虑 $dp$。

然后用期望推了好久都没有推出来，那么就可以考虑使用期望的定义推，也就是算方案数。

那么就可以考虑设 $dp[i][j][k]$ 表示前 $i$ 个洗衣房，去了 $j$ 个人，最大值为 $k$ 的方案数。

转移也是很显然：
$$
dp[i][j][k] \times \binom{n-j}{p} \to dp[i+1][j + p][\max(\lfloor \dfrac{p}{a_{i+1}} \rfloor,k)]
$$
具体为什么要乘组合数，因为我们稍微模拟一下再手模一下会发现人和人之间是有区别的。

初值就是 $dp[0][0][0] = 1$
那么我们的答案就十分显然了：
$$
\dfrac{\sum_{i=1}^n i \times dp[m][n][i]}{\sum_{i=1}^n dp[m][n][i]}
$$
但是这个题仿佛会爆 $long \ long$，那么用一下 $double$ 就好了。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
double C[N][N],dp[N][N][N];
int a[N];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; i++)	scanf("%d",&a[i]);
	C[0][0] = 1;
	for(int i=1; i<=n; i++){
		C[i][0] = 1;
		for(int j=1; j<=i; j++)	C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
	dp[0][0][0] = 1;
	for(int i=0; i<m; i++){
		for(int j=0; j<=n; j++){
			for(int k=0; k<=n; k++){
				for(int p=0; p<=n; p++){
					if(j + p <= n)	dp[i+1][j+p][max((p + a[i+1] - 1) / a[i+1],k)] += dp[i][j][k] * C[n-j][p];
				}
			}
		}
	}
	double tmp = 0;
	for(int i=1; i<=n; i++)	tmp += dp[m][n][i];  //总方案数
	double ans = 0;
	for(int i=1; i<=n; i++)	ans = ans + 1.0 * dp[m][n][i] * i / tmp; 
	printf("%.12f\n",ans);
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2200}$
---
### 解题思路：

设最长队伍为 $i$ 的 可能情况有 $sum_i$ 种，那么根据全期望公式可知最终的答案为：$\dfrac{\sum_{i=1}^n i\times sum_{i}}{\sum_{i=1}^nsum_i}$。然后问题就是如何求出 $sum_i$。

考虑动态规划。设 $f_{i,j,k}$ 表示考虑到第 $i$ 个房间，$j$ 已有 $j$ 个学生进入了房间，剩下 $n-j$ 个学生尚未还处于空闲状态，此时的最长队伍为 $k$ 的方案数。

然后考虑转移，这里用填表法比较方便。考虑当前位置的下一个位置中放上 $l$ 个学生，则当前的 $f_{i,j,k}$ 就可以转移到 $f_{i+1,j+l,\max(k,\left\lceil\frac{a_{i+1}}{l}\right\rceil)}$，然后再乘上选择学生的可能方案数 $C_{n-j}^l$。

总复杂度 $O(n^4)$。

注意用 $\text{double}$ 存储数据。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int n,m,a[55];
double ans,f[55][55][55],c[55][55],cnt1,cnt2;
signed main(){
	scanf("%I64d%I64d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%I64d",&a[i]);
	c[0][0]=1;
	for(int i=1;i<=50;i++)
	for(int j=0;j<=i;j++){
		if(j==0){c[i][j]=1;continue;}
		c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	f[0][0][0]=1;
	for(int i=0;i<m;i++)
	for(int j=0;j<=n;j++)
	for(int k=0;k<=n;k++)
	for(int l=0;l<=n-j;l++)
	f[i+1][j+l][max(k,(l/a[i+1])+(l%a[i+1]!=0))]+=f[i][j][k]*c[n-j][l];
	for(int i=0;i<=n;i++){
		cnt1+=f[m][n][i];
		cnt2+=f[m][n][i]*i;
	}
	ans=(double)cnt2/cnt1;
	printf("%.15lf\n",ans);
	return 0;
}
```


---

