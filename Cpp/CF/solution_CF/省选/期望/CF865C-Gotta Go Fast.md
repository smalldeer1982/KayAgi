# Gotta Go Fast

## 题目描述

You're trying to set the record on your favorite video game. The game consists of $ N $ levels, which must be completed sequentially in order to beat the game. You usually complete each level as fast as possible, but sometimes finish a level slower. Specifically, you will complete the $ i $ -th level in either $ F_{i} $ seconds or $ S_{i} $ seconds, where $ F_{i}&lt;S_{i} $ , and there's a $ P_{i} $ percent chance of completing it in $ F_{i} $ seconds. After completing a level, you may decide to either continue the game and play the next level, or reset the game and start again from the first level. Both the decision and the action are instant.

Your goal is to complete all the levels sequentially in at most $ R $ total seconds. You want to minimize the expected amount of time playing before achieving that goal. If you continue and reset optimally, how much total time can you expect to spend playing?

## 说明/提示

In the first example, you never need to reset. There's an $ 81% $ chance of completing the level in $ 2 $ seconds and a $ 19% $ chance of needing $ 8 $ seconds, both of which are within the goal time. The expected time is $ 0.81·2+0.19·8=3.14 $ .

In the second example, you should reset after the first level if you complete it slowly. On average it will take $ 0.25 $ slow attempts before your first fast attempt. Then it doesn't matter whether you complete the second level fast or slow. The expected time is $ 0.25·30+20+0.85·3+0.15·9=31.4 $ .

## 样例 #1

### 输入

```
1 8
2 8 81
```

### 输出

```
3.14
```

## 样例 #2

### 输入

```
2 30
20 30 80
3 9 85
```

### 输出

```
31.4
```

## 样例 #3

### 输入

```
4 319
63 79 89
79 97 91
75 87 88
75 90 83
```

### 输出

```
314.159265358
```

# 题解

## 作者：ღꦿ࿐ (赞：14)

## 题意：

你是一个 up 主，你要录一段速通 RA2YR 的视频，

战役有 $n$ 关，每关你有 $p_i\%$ 的可能性花 $F_i$ 的时间通过，$(1-p_i)\%$ 的可能性花掉 $S_i$ 的时间通过（失误了），其中保证 $F_i>S_i$。

但因为你想“速通”，你不希望你的视频长度超过 $m$。

当你认为自己接下来可能录不完（接着录录完不如重新录）时，你会重新开始录，求录完整个游戏的时间期望。

## 思路：

首先不考虑时间限制，用 $f(i)$ 表示打完前 $i$ 关的期望时间，那么由期望的线性性易得转移方程为：

$$ f(i)=f(i-1)+p_i \times F_i+(1-p_i)\times S_i $$

然后考虑时间限制，那么打到第 $i$ 关用时 $a,b(a<b)$ 时打完的期望是不同的，（可能会重来）

所以为状态再加一维：$f(i,j)$ 表示打过了第 $i$ 关用时为 $j$ 时打完的期望。

易知 $f(n,j)=0$，要求 $f(0,0)$，每一位都有其后一位有关，所以是由 $n$ 倒推至 $0$。

转移方程为：

$$ f(i,j)=\begin{cases}
0 ,& i=n,j\le m\\
f(0,0),& j >m \\ 
\min(f(0,0),e1+e2) ,& \text{otherwise.}
\end{cases} $$

其中 $ e_1=p_{i+1} \times f(i+1,j+f_{i+1})+f_{i+1}))   $。

$e_2=p_{i+1}\times(1-p_{i+1})\times(f(i+1,j+S_{i+1})+S_{i+1})$ 。

$f(0,0)$ 表示回到最开始重新打（如果重新打的期望已经比现在更优就重新打，如果超过 $m$ 也要重新从头开始），

其余部分和正常求期望相同。

现在就出现了问题：这不是一个 dp，它的转移有环，转移关系如图 ：

![](https://cdn.luogu.com.cn/upload/image_hosting/od5cpao8.png)

$f(0,0)$ 决定着每一个 $f$ 值，又要由其它 $f$ 值得到，形成了环。

那么应该怎么处理环呢？

显然，每个未知 $f$ 值都对应一个转移，也就是说这些转移形成了一个由 $m\times n+1$ 个方程，$m\times n+1$ 个未知数组成的方程组。

所以我们似乎可以使用高斯消元？

$\text{O}(n^3 m^3)$ 的复杂度很明显不能接受，而且 $\min$ 函数的存在会让消元变得复杂。

分析发现造成这些环的”罪魁祸首“都是 $f(0,0)$ ，把 $f(0,0)$ 看作常数，那么就可以无环转移，怎么转移呢?

使用 dp！

很显然我们需要找到正确的停下时间，因为最优重开时间一定是等于期望时间的，并且显然由单调性，所以二分停下的时间即可。

```cpp
//dp[i][j]=(dp[i+1][j+a[i]]+a[i])*p[i]+(p[i+1][j+b[i]]+b[i])*(1-p[i])
#include<bits/stdc++.h>
#define eps 0.00000000002
using namespace std;
long double f[52][50002];int a[5003],b[5300],p[5300];
int n,m;
bool check(long double v)
{
	f[n][0]=0.000000;
	for(int i=n-1;i>=0;--i)
	  {
	  	for(int j=m+1;j<=5002;++j)
	  	  f[i+1][j]=v;
	  	for(int j=0;j<=m;++j)
		   f[i][j]=min(v,(f[i+1][j+a[i+1]]+a[i+1])*p[i+1]/100.0+(f[i+1][j+b[i+1]]+b[i+1])*(100.0-p[i+1])/100.0);
	  }
	return f[0][0]<v; 
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	  cin>>a[i]>>b[i]>>p[i];
	long double l=0,r=1e9,ans=-1.000;
	int cnt=0;
	while(r-l>eps)
	 {
	 	cnt++;
	 	if(cnt-200>0)break;
	 	long double mid=(l+r)/2.00;
	 	if(check(mid)) ans=mid,r=mid-eps;
	 	else l=mid+eps;
	 }
	 printf("%.9Lf",ans);
}
```

Solution By : [ღꦿ࿐（kk）](https://www.luogu.com.cn/user/161697)

Image & Stuff By：[black_trees](https://www.luogu.com.cn/user/304550)

---

## 作者：alvis (赞：5)

# **特此鸣谢$dxy$巨人**

## 题目大意
现有 $\text{n}$ 个任务，对于每个任务有 $\operatorname{p_i}$ 的概率以$\operatorname{a_i}$的速度通过，有 $\operatorname{(1-p_i)}$ 的概率以 $\operatorname{b_i}$ 的速度通过。所有任务需要在 $\text{m}$ 秒内完成。

可以重新开始游戏。

求通过所有关卡的期望时间。
## 思路

期望问题。

我们可以把这个问题转化为计数DP。

考虑设计一下状态。

我们设 $\operatorname{f_{i,j}}$ 为当前在第 $\text{i}$ 关，已经花了 $\text{j}$ 秒钟，期望还要多久打通关。

那么我们的式子就很好想了。

$f_{i,j}=(f_{i+1,j+a[i]}+a[i])*p[i]\%+(f_{i+1,j+b[i]}+b[i])*(1-p[i])\%$

并且时间大于 $\text{m}$ 时应该直接结束。

但是我们还有可以重新开始游戏这一条件。
考虑如何处理。

考虑生活情景，当我们~~为了刷排行榜~~为了获得更好的成绩，我们什么时候会重新开始游戏。

显然如果我们当前的成绩不是很理想，那么我们就会直接重新开始游戏。

那么我们设选择重新开始的临界时间为 $\text{t}$。

当我们计算出的时间大于 $\text{t}$ 时，说明 $\text{t}$ 应该变大。

同理，当我们计算出的时间小于 $\text{t}$ 时，说明 $\text{t}$ 应该变小。

等一下，是不是发现我们可以利用**二分**来解决了！

所以，我们二分 $\text{mid}$（即上面的 $\text{t}$），~~不仅变快了~~，还解决了转移带环的问题。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

long long n, m;
double f[60][5100];
long long a[1001], b[1001], p[1001];

bool check(double mid){
    for(int i = n;i >= 1;i --){
    	//超时的不计入最终答案。
        for(int t = m+2; t <= 5010;t ++)f[i+1][t] = mid;
        //进行转移
        for(int j = 1;j <= m+1;j ++)f[i][j] = min(mid, (f[i+1][j+a[i]]+a[i])*p[i]/100 + (f[i+1][j+b[i]]+b[i])*(100-p[i])/100);
    }
    return f[1][1] < mid;
}

int main(){
    //读入优化
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= n;i ++){
        cin >> a[i] >> b[i] >> p[i];
    }

    double l = 1, r = 1e9, cnt=1;
    //二分mid，即重复挑战的临界时间
    while(l + 0.000000005 < r){
        if(cnt > 100)break;
        double mid = (l+r)/2;
        cnt ++;
        if(check(mid))r = mid;
        else l = mid;
    }
    printf("%.9f", l);
return 0;
}
```


---

## 作者：Purslane (赞：4)

# Solution

设我们已经结束了第 $i$ 关，且目前这一把里面用时为 $j$ 的期望用时为 $dp_{i,j}$。

那么容易写出状态转移方程：

$$dp_{i,j}=\left \{\begin{matrix}
0 ,&i=n , j \le m \\
dp_{0,0}, &j>m \\
\min\{dp_{0,0},p_{i+1}(dp_{i+1,j+a}+a)+(1-p_{i+1})(dp_{i+1,j+b}+b)\},&\text{otherwise}
\end{matrix}\right.$$

但是这个式子有一定的漏洞，好像 $dp_{i,j} \equiv 0$ 也是他的解啊？？？所以我们在 $i=j=0$ 的时候不能走 $dp_{0,0}$ 自身。于是有

$$dp_{i,j}=\left \{\begin{matrix}
0 ,&i=n , j \le m \\
dp_{0,0}, &j>m \\
p_1(dp_{1,a}+a)+(1-p_1)(dp_{1,b}+b),&i=j=0\\
\min\{dp_{0,0},p_{i+1}(dp_{i+1,j+a}+a)+(1-p_{i+1})(dp_{i+1,j+b}+b)\},&\text{otherwise}
\end{matrix}\right.$$

这个方程具有后效性，而且由于这个 $\min$ 的存在，你甚至很难使用高斯消元。

设 $dp_{0,0}=c$，我们就可以把转移方程式中所有的 $dp_{0,0}$ 换为 $c$，得到：

$$dp_{i,j}=\left \{\begin{matrix}
0 ,&i=n , j \le m \\
c, &j>m \\
p_1(dp_{1,a}+a)+(1-p_1)(dp_{1,b}+b),&i=j=0\\
\min\{c,p_{i+1}(dp_{i+1,j+a}+a)+(1-p_{i+1})(dp_{i+1,j+b}+b)\},&\text{otherwise}
\end{matrix}\right.$$

最终我们希望 $dp_{0,0}$ 恰好为 $c$。因此我们考察 $f_{i,j}=dp_{i,j}-c$。得到了：

$$f_{i,j}=\left \{\begin{matrix}
-c ,&i=n , j \le m \\
0, &j>m \\
p_1(f_{1,a}+a)+(1-p_1)(f_{1,b}+b),&i=j=0\\
\min\{0,p_{i+1}(f_{i+1,j+a}+a)+(1-p_{i+1})(f_{i+1,j+b}+b)\},&\text{otherwise}
\end{matrix}\right.$$

然后很明显发现了，$f_{i,j}$ 随着 $c$ 的增加显然是单调不增的。

因此我们可以使用二分法来寻找使得 $f_{0,0}$ 恰好为 $0$ 的 $c$。

我想这才是本题能想到“二分法”最关键的分析。但其他题解都没有提及这一点。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50+10,MAXM=5000+10; 
int n,m,a[MAXN],b[MAXN],vis[MAXN][MAXM];
long double p[MAXN],dp[MAXN][MAXM];
long double dfs(int i,int j,long double c) {
	if(i==n&&j<=m) return 0;
	if(j>m) return c;
	if(vis[i][j]) return dp[i][j];
	vis[i][j]=1;
	return dp[i][j]=min(c,p[i+1]*(dfs(i+1,j+a[i+1],c)+a[i+1])+(1-p[i+1])*(dfs(i+1,j+b[i+1],c)+b[i+1]));
}
int check(long double c) {
	memset(vis,0,sizeof(vis));
	return dfs(0,0,c)<c-1e-10;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>a[i]>>b[i]>>p[i],p[i]/=100;
	long double l=0,r=50000000;
	while((r-l)>1e-10) {
		long double mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid;	
	}
	cout<<fixed<<setprecision(10)<<l;
	return 0;
}
```

---

## 作者：Tyyyyyy (赞：4)

## Tags:DP，二分
[原题](https://codeforces.com/contest/866/problem/C)
### 题目大意
有一个游戏有 $N$ 关，第 $i$ 关有 $P_i$ 的概率在 $F_i$ 的时间通过，有 $1-P_i$ 的概率在 $S_i$ 的时间通过。现在想要在 $R$ 秒内通关游戏，每一关之后都可以重置到第一关开始之前。求在采用最优策略重置的情况下，通关的期望时间。

数据范围：$N \leq 50 , 80 \leq P_i \leq 99 , 1 \leq F_i \leq S_i \leq 100 , \sum F_i \leq R \leq \sum S_i$

### 分析
首先想到 dp ，但是因为有重置操作，状态之间有循环无法 dp ，需要想办法绕开重置。

假设在每两关（及第一关之前）添加一个进入“固定关卡”的机会，同时不再可以重置。完成“固定关卡”的时间恒为 $K$ 。完成原有关卡或固定关卡都算完成游戏。

定义 $dp_{i,j}$ 表示：玩了 $1 \dots i$ 关花了 $j$ 时间，要玩之后的关卡的最小时间 。从后往前 dp ，有方程如下：

$$dp_{i,j}=\begin{cases}\min(k,cost),j+f_i \leq r\\k ,j+f_i>r\end{cases}$$
$$cost=\begin{cases}(f_i+dp_{i+1,j+f_i}) \times p_i+(s_i+dp_{i+1,j+s_i})\times (1-p_i),j+s_i \leq r\\(f_i+dp_{i+1,j+f_i})\times p_i+(s_i+k)\times (1-p_i),j+s_i>r\end{cases}$$

其中，$k$ 是二分得到的固定关卡所需时间，如果 $dp_{1,0} < k$ ，说明实际答案比 $k$ 小；否则实际答案比 $k$ 大（这里的单调性可以用来解释为什么要使用二分）。

时间复杂度为 $O(NR\operatorname{log}maxt)$ 。

代码如下：
```cpp
#include<bits/stdc++.h>
#define ld long double
using namespace std;
int n,r,f[55],s[55];
ld dp[55][10010],p[55];
bool check(ld k)
{
	memset(dp,0,sizeof(dp));
	for(int i=n;i>=1;i--)
	{
		for(int j=0;j<=r;j++)
		{
			if(j+f[i]<=r)
			{
				ld cost=(1.0*f[i]+dp[i+1][j+f[i]])*1.0*p[i];
				if(j+s[i]<=r)
					cost+=(1.0*s[i]+dp[i+1][j+s[i]])*1.0*(1-p[i]);
				else
					cost+=(1.0*s[i]+k)*1.0*(1-p[i]);
				dp[i][j]=min(k,cost);
			}
			else dp[i][j]=k;
		}
	}
	return dp[1][0]<k;
}
int main()
{
	scanf("%d%d",&n,&r);
	for(int i=1;i<=n;i++)scanf("%d%d%Lf",&f[i],&s[i],&p[i]);
	for(int i=1;i<=n;i++)p[i]/=100;
	ld l=0,r=1e9,mid;
	for(int i=1;i<=100;i++)
	{
		mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid; 
	}
	printf("%.9Lf",l);
	return 0;
}
```

---

## 作者：Dita (赞：2)

**题目大意**

> 某一通关游戏，有 $P_i$ 的概率以 $a_i$ 秒通过第 $i$ 关，或者 $(1 − P_i)$ 的概率以 $b_i$ 秒通过第 $i$ 关
>
> 每打过一关可以选择打下一关， 或者重新从第一关开始打
>
> 需要在 $R$ 秒内打过这个游戏，求最少期望要花费多少秒？ 
>
> $N ≤ 50, F_i < S_i ≤ 100, 0.8 ≤ P_i ≤ 0.99, ∑F_i ≤ R ≤ ∑S_i$

**solution**

$f_{i,j}$  表示当前在第 $i$ 关，已经花费了 $j$ 秒，通关还需要多少秒

**转移**

$f_{i,j} = (f_{i + 1,j + a_i} + a_i)*(1 - p_i) + (f_{i + 1, j + b_i} + b_i)*p_i$

特判当 $j + a_i$  或者 $j + b_i$  超过 $R$ 时，从头开始

某些情况发现通关的概率很小，要重新开始

怎么找这些情况捏?

我们二分枚举答案 $f_{0,0}$ 的值 $mid$ ，那么提前超时需要重开的那些状态的 $dp$  值都会成为 $mid$（中途已经超时了当然重开嘛） ，然后 $dp$ 一遍肯定会新求出一个 $f'_{0,0}$ ，如果 $mid$ 比  $f'_{0,0}$ 大的话，那么 $f_{0,0}$ 肯定要比 $f'_{0,0}$ 大，所以 $mid$  要减小，反之要增大

**Time**: $O(kn^2a_i)$，k 为二分次数

```
/*
work by:Ariel_
*/
#include <iostream>
#include <cstdio>
#define db double
using namespace std;
const int T = 5000, N = 120;
int read(){
    int x = 0,f = 1; char c = getchar();
    while(c < '0'||c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') {x = x*10 + c - '0'; c = getchar();}
    return x*f;
}
int n, R, p[N], a[N], b[N];
db f[51][T], l, r = 1e9;
bool check(db mid){
   for(int i = n - 1; i >= 0; i--){ 
     for(int j = R + 1; j < T; j++) f[i + 1][j] = mid;//提前超时滴
     for(int j = 0; j <= R; j++)
       f[i][j] = min(mid, (f[i + 1][j + a[i]] + a[i]) * p[i] / 100 + (f[i + 1][j + b[i]] + b[i]) * (100 - p[i])/100);
   }
   return mid > f[0][0]; 
}
int main(){
   n = read(), R = read();
   for(int i = 0; i < n; i++)
   	 a[i] = read(), b[i] = read(), p[i] = read(); 
   db mid = (l + r) / 2;
   for(int i = 1; i <= 100; i++, mid = (l + r) / 2)
   	  (check(mid)) ? r = mid : l = mid; 
   printf("%.10f\n", l);
   return 0;
}

```

---

## 作者：skylee (赞：2)

### 题解地址：
[[CF865C]Gotta Go Fast - skylee's Blog](http://www.cnblogs.com/skylee03/p/8984001.html)

### 题目大意：  
一个游戏关卡有$n(n\le50)$个任务，若在$m$秒内按顺序完成所有任务则算作通过当前关卡。每个关卡有三个属性$a_i,b_i,p_i(1\le a_i<b_i\le100,80\le p_i\le99)$，表示有$p_i\%$的概率用$a_i$秒完成任务$i$，有$1-p_i\%$的概率用$b_i$秒完成任务$i$。每完成一个任务后可以选择继续下一个任务或重新开始当前关卡。问通过当前关卡的期望时间。

### 思路：  
二分答案$k$，并用期望DP进行检验。  
用$f[i][j]$表示从第$n$个任务到第$i$个任务，倒计时还剩$j$秒，总时间的期望。  
$f[i][j]=(f[i+1][j+a_i]+a_i)p_i+(f[i+1][j+b_i]+b_i)(1-p_i)$。  
若$f[i][j]>k$，重新开始当前关卡更优，令$f[i][j]=k$。  则状态转移方程为$f[i][j]=\min((f[i+1][j+a_i]+a_i)p_i+(f[i+1][j+b_i]+b_i)(1-p_i),k)$。  
若$f[0][0]<k$，则期望不大于$k$。  

### 源代码：
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x;
}
const int N=51,M=5001;
const double eps=1e-9;
int n,m,a[N],b[N],p[N];
double f[N][M];
inline bool check(const double &k) {
	for(register int i=n-1;~i;i--) {
		for(register int j=m+1;j<M;j++) f[i+1][j]=k;
		for(register int j=0;j<=m;j++) {
			f[i][j]=std::min((f[i+1][j+a[i]]+a[i])*p[i]/100+(f[i+1][j+b[i]]+b[i])*(100-p[i])/100,k);
		}
	}
	return f[0][0]<k;
}
int main() {
	n=getint(),m=getint();
	for(register int i=0;i<n;i++) {
		a[i]=getint(),b[i]=getint(),p[i]=getint();
	}
	double l=0,r=1e9;
	while(r-l>eps) {
		const double mid=(l+r)/2;
		(check(mid)?r:l)=mid;
	}
	printf("%.10f\n",r);
	return 0;
}
```

---

## 作者：zifanwang (赞：0)

考虑二分答案然后 dp，钦定 $mid$ 为重新开始的期望时间。若求出的期望时间 $<mid$ 小，则答案 $<mid$。

记 $f_{i,j}$ 表示当前到了第 $i$ 关，用了 $j$ 单位时间通关需要花费的的期望总时间。考虑怎么转移：

- 若 $j>R$，则必须重启，$f_{i,j}=j+mid$。
- 若 $j\le R$，则 $f_{i,j}=\min(j+mid,\frac{p_i}{100}f_{i+1,j+a_i}+(1-\frac{p_i}{100})f_{i+1,j+b_i})$。

比较 $f_{1,0}$ 与 $mid$ 即可。时间复杂度 $\mathcal O(nR\log V)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
#define drep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int n,s,sm,a[53],b[53],p[53];
long double l,r,f[53][5003];
bool check(long double mid){
	rep(i,0,sm)f[n+1][i]=i>s?i+mid:i;
	drep(i,n,1){
		rep(j,0,sm){
			f[i][j]=j>s?j+mid:min(j+mid,p[i]/100.0*f[i+1][j+a[i]]+(1-p[i]/100.0)*f[i+1][j+b[i]]);
		}
	}
	return f[1][0]<mid;
}
signed main(){
	scanf("%d%d",&n,&s);
	rep(i,1,n)scanf("%d%d%d",&a[i],&b[i],&p[i]),sm+=b[i];
	r=1e9;
	while(l+1e-11<r){
		long double mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid;
	}
	printf("%.10Lf",l);
	return 0;
}
```

---

