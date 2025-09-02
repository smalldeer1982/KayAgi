# Dumb Bones

## 题目描述

你正在尝试用多米诺骨牌搭成一条直线，以便最后试验时推倒它们

（确实，搭建某些东西仅仅为了推倒看上去没啥意义，但你有一些奇怪的爱好）

然而你在搭建过程中可能会弄倒骨牌，这将波及到邻近的部分

现在需要你来求将骨牌搭建完成所需的期望步数

## 样例 #1

### 输入

```
10 0.25 0.25
10 0.1 0.4
10 0.0 0.5
0```

### 输出

```
46.25
37.28
20.00```

# 题解

## 作者：Guitar_Jasmine (赞：13)

有没有跟我一样翻完题解对着状态转移方程一脸懵 * 的蒟蒻。/kk

设$f[i]$表示搭好$i$个连续的骨牌的期望次数，由于两段不连续的区间肯定互不影响，所以我们可以考虑枚举最后一个放的位置，根据期望的线性性质进行累加。

例如：
$1 \ 2 \ ? \ 4 \ 5 $

假设$?$位置是我们最后一个放骨牌的位置，那么显然我们在摆放$1 \  2$的时候不会影响到$4\ 5$，同理摆放$4\ 5$的时候也不会影响到$1\ 2$。

对于每个$i$，我们枚举一个$j$表示最后一个放的位置，状态转移如下：

$f[i]=min( \frac{1-pr}{1-pl-pr}\times f[j-1] + \frac{1-pl}{1-pl-pr}\times f[i-j] )+ \frac{1}{1-pl-pr}$

如何理解这个转移呢？

* 以下为一个插曲：

@Binary_Search_Tree 神仙前几天给了我一个结论：某事件$A$第一次发生的期望次数 $ =\frac{1}{P(A)}$（其中$P(A)$表示$A$发生的概率）

因为萌新初学期望之前也没听说这个东西，如果要证明的话我只能说你随便举个例子然后用期望的定义自己推一下（逃）。

再给一个 [知乎上的栗子](https://www.zhihu.com/question/289969453/answer/469172454)（可以直接看他后面通俗的解释）

* 回到正题，我们来解释这个转移方程：

首先看转移方程后面的那个$\frac{1}{1-pl-pr}$：我们单独考虑最后你要放的那个骨牌的期望次数，发现你有$1-pl-pr$的概率不倒，直接套用上面结论即可。

然后我们拿最后摆放位置的**左边**为例解释一下$\frac{1-pr}{1-pl-pr}\times f[j-1]$（右边同理）：

根据上面我们知道在最后一张骨牌放好前那张牌总共会倒$\frac{1}{1-pl-pr}-1$次（因为最后一次他就放好了所以要减一个$1$），整理一下也就是$\frac {pl+pr}{1-pl-pr}$次，注意这是**总共会倒的次数**，那么向左倒的次数就应该乘一个$\frac{pl}{pl+pr}$，所以向左倒的次数为：
$$\frac {pl+pr}{1-pl-pr} \times \frac{pl}{pl+pr}= \frac{pl}{1-pl-pr}$$
，由于$j$是我们最后一个摆的位置，也就是之前我们还会把左边的牌先摆一遍，所以你摆左边这些牌的总次数为$\frac{pl}{1-pl-pr}+1= \frac{1-pr}{1-pl-pr}$，那么左边这些牌对$f[i]$的贡献显然就是
$$\frac{1-pr}{1-pl-pr}\times f[j-1]$$
了吧（终于推完了），最后每个位置去个$min$就完事了。

时间复杂度:$O(n^2)$

至于$O(n)$的做法嘛，转移方程的理解最重要嘛，所以就不讲了，~~优化什么优化，能过就行~~。

这是初学期望的萌新对这个题的理解，如果有非常简单的对转移方程的理解欢迎在评论区或者私信~~打脸~~。

代码：
```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=1009;
int n;
double pl,pr,f[N];

void work()
{
	scanf("%d",&n);
	while(n)
	{
		scanf("%lf %lf",&pl,&pr);
		f[0]=0,f[1]=1/(1-pl-pr);
		for (int i=2;i<=n;i++)
		{
			f[i]=1<<30;
			for (int j=1;j<=i;j++)
				f[i]=min(f[i],(1-pr)/(1-pr-pl)*f[j-1]+(1-pl)/(1-pr-pl)*f[i-j]);
			f[i]+=1/(1-pl-pr);
		}
		printf("%.2lf\n",f[n]);
		scanf("%d",&n);
	}
}

int main()
{
	work();
	return 0;
}
```

---

## 作者：zyn0309 (赞：10)

# UVA10529
[题目传送门](https://www.luogu.com.cn/problem/UVA10529)
## 思路
$P_l$ 为向左边倒的概率，$P_r$ 为向右边倒的概率，可以推出在一个点倒一次的概率为 $P_l+P_r$，倒两次的概率为 $(P_l+P_r)^2$ ，倒 $n$ 次的概率为 $(P_l+P_r)^n$。

根据上面的推导，我们将在一个点倒下的期望次数为 $cnt$，容易得出以下式子。
 $$cnt=\sum _ {i = 1} ^ {inf} (P_l+P_r)^i$$ 
由于题目中只要求保留两位小数，我们只需要枚举 $10^3$ 位就足够我们在本题目中使用。

现在已知倒下的期望次数 $cnt$，所以向左倒的期望次数 $cntl$ 为 $cnt \times P_l \div (P_l+P_r)$，向右倒的期望次数 $cntr$ 为 $cnt \times P_r \div (P_l+P_r)$。

然后开始动态规划，设连续摆 $i$ 个的期望次数为 $f_i$，如果原来在左边放了 $len$ 个，在右边就放了 $i - len - 1$ 个，此时 $f_i = f_{len} \times (cnt_l+1) + f_{i - len - 1} \times (cnt_r+1) + cnt +1$。然后我们只需要枚举 $len$  的长度，取最小值即可。 
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n;
double f[N],pl,pr;
double query(double x){
	double ans=0,y=x;
	for(int i=1;i<=1000;++i){
	  ans+=y;
	  y*=x;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    while(1){
      cin>>n;
      if(!n)break;
      cin>>pl>>pr;
      double cntl,cntr,cnt;
      cnt=query(pl+pr);
      cntl=cnt*pl/(pl+pr);
      cntr=cnt*pr/(pl+pr);
      for(int i=1;i<=n;++i){
        f[i]=cnt+1;
        double res=2e9;
        for(int len=0;len<i;++len){
          res=min(res,(cntl+1)*f[len]+(cntr+1)*f[i-len-1]);
		}
		f[i]+=res;
	  }
	  cout<<fixed<<setprecision(2)<<f[n]<<"\n";
	}
	return 0;
}
```

---

## 作者：⚡LZSY01_XZY⚡ (赞：7)

## 前言
一道锻炼**概率**$DP$的~~好题~~

## 题意
要摆放$N$块骨牌，放每一个骨牌时，有$pl$的几率向左倒，有$pr$的几率向右倒，求搭好$N$个骨牌的平均步数（即期望步数）。

## 解法
$\text{设$dp[n]$表示搭一个长度为$n$的骨牌的平均步数。}$  
$\text{则状态转移方程为：}$
$$dp[n]=min\{\frac{1-pr}{1-pl-pr}*dp[k]+\frac{1-pl}{1-pl-pr}*dp[n-k-1]+\frac{1}{1-pl-pr}\}(0\le k<n)$$
$\text{边界：}dp[0]=0,dp[1]=\frac{1}{1-pl-pr}$ 

## 解释一下状态转移方程
对于边界，搭$0$块当然为$0$，对于搭$1$块，搭一次有$1-pl-pr$的几率搭好，我们要**保证**搭好，就要让它的期望达到$1$，所以$dp[1]=\frac{1}{1-pl-pr}$。  
我们把第$n$块骨牌插入时，有$pr$的几率向右倒，也就是说有$1-pr$的几率不向右倒，要把左边搭好。那么，搭左边的期望次数便是$\frac{1-pr}{1-pl-pr}$。搭右边和它相似，期望次数是$\frac{1-pl}{1-pl-pr}$，我们只需将他们分别乘上搭建代价就好。处理好左右两边后，还需处理第$n$块，把第$n$块搭好的期望步数是$\frac{1}{1-pl-pr}$，只需把它加上就好。

$O(n^2)\text{算法：}$
```cpp
//我的O(N^2)的code是所有O(N^2)的code中最快的
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
inline T read()
{
	T x=0,f=1;char c=getchar();
	while (c<'0' || c>'9'){if (c=='-')f=-1;c=getchar();}
	while (c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
	return x*f;
}

const int MAXN=1005;
int n;
double pl,pr,dp[MAXN];

inline double calc(int l,int r)
{
	return ((1-pr)/(1-pl-pr)*dp[l])+((1-pl)/(1-pl-pr)*dp[r])+(1/(1-pl-pr));
}

int main()
{
	while (true)
	{
		n=read<int>();
		if (n==0) break;
		scanf("%lf%lf",&pl,&pr);
		dp[0]=0;dp[1]=1/(1-pl-pr);
		for (int i=2;i<=n;i++)
		{
			dp[i]=calc(0,i-1);
			for (int j=1;j<i;j++)
				dp[i]=min(dp[i],calc(j,i-j-1));
		}
		printf("%0.2lf\n",dp[n]);
	}
	return 0;
}
```

$O(n)$算法我不会证明，以后再来填坑。实现只要加一个$last$变量就好。

$O(n)\text{算法：}$
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
inline T read()
{
	T x=0,f=1;char c=getchar();
	while (c<'0' || c>'9'){if (c=='-')f=-1;c=getchar();}
	while (c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
	return x*f;
}

const int MAXN=1005;
int n,last;
double pl,pr,res,dp[MAXN];

inline double calc(int l,int r)
{
	return ((1-pr)/(1-pl-pr)*dp[l])+((1-pl)/(1-pl-pr)*dp[r])+(1/(1-pl-pr));
}

int main()
{
	while (true)
	{
		n=read<int>();
		if (n==0) break;
		scanf("%lf%lf",&pl,&pr);
		dp[0]=0;dp[1]=1/(1-pl-pr);
		last=0;
		for (int i=2;i<=n;i++)
		{
			dp[i]=calc(last,i-last-1);
			for (int j=last+1;j<i;j++)
			{
				res=calc(j,i-j-1);
				if (res<dp[i]) {dp[i]=res;last=j;}
				else break;
			}
		}
		printf("%0.2lf\n",dp[n]);
	}
	return 0;
}
```  
$Please~give~a~like.Thanks.$

---

## 作者：china·xyc (赞：3)

额，看见很多大佬写了DP，然后这里提供一个记忆化搜索的方法

#### 最开始的想法

对于一段区间[i，j]，往里面插入第$j-i+2$块骨牌，最后复杂度是$O(n^3)$，转移方程：

$f[i][j]=min(f[i][k-1]\times\frac{1-pr}{1-pl-pr}+f[k+1][j]\times\frac{1-pl}{1-pl-pr}+\frac{1}{1-pl-pr})(i<k<j)$

#### 如何优化

得到第一个$O(n^3)$的做法之后，我们发现其实i到j并不重要，只需考虑i到j的骨牌数量就好了，复杂度为$O(n^2)$，转移方程：

$f[i]=min(ans,f[j]\times\frac{1-pr}{1-pl-pr}+f[i-j-1]\times\frac{1-pl}{1-pl-pr}+\frac{1}{1-pl-pr})(0\le j\le i)$

#### 再优化

利用决策单调性，优化成$O(n)$，由于这题n只有1000，这里就不过多赘述（其实是我也不会呀QAQ）

### 放代码

```cpp
//DP代码
#include<bits/stdc++.h>
using namespace std;
int n;
double pl,pr,f[1005];
int main(){
	do{
		memset(f,0,sizeof(f));
	    scanf("%d",&n);
	    if(n==0) break;
		scanf("%lf%lf",&pl,&pr);
		f[1]=1/(1-pl-pr);
		for(int i=2;i<=n;i++){
			f[i]=(1-pl)/(1-pl-pr)*f[i-1]+f[1];
		    for(int j=1;j<i;j++)
		        f[i]=min(f[i],(1-pr)/(1-pl-pr)*f[j]+(1-pl)/(1-pl-pr)*f[i-j-1]+f[1]);
		}
		printf("%.2f\n",f[n]);
	}while(1);
	return 0;
}
```
```cpp
//记忆化搜索代码
#include<bits/stdc++.h>
using namespace std;
int n;
double pl,pr,f[1005];
double calc(int x){
	if(x==1) return 1/(1-pl-pr);
	if(x==0) return 0;
	if(f[x]) return f[x];
	double ans=(1-pl)/(1-pl-pr)*calc(x-1)+1/(1-pl-pr);
	for(int i=1;i<x;i++)
	    ans=min(ans,(1-pr)/(1-pl-pr)*calc(i)+(1-pl)/(1-pl-pr)*calc(x-i-1)+1/(1-pl-pr));
	f[x]=ans;
	return ans;
}
int main(){
	do{
		memset(f,0,sizeof(f));
	    scanf("%d",&n);
	    if(n==0) break;
		scanf("%lf%lf",&pl,&pr);
		printf("%.2f\n",calc(n));
	}while(1);
	return 0;
}
```


---

## 作者：lajioj (赞：3)

### 概率dp

翻译有一个小锅，不是某个多米诺的向左，向右倾倒的概率，而是“每个”


最开始以为是一个递推，后面发现骨牌并不是按照顺序来放置的,然后就开始强势懵逼。。。然后翻了一下网上的题解（一句话）：用 $dp[i]$ 表示连续放置 $i$ 块骨牌的期望步数，因为放置骨牌顺序不定，可以枚举最后一张骨牌放置的位置。

于是有：

### $dp[0] = 0$

### $dp[1] = \frac{1}{1 - pl - pr}$

然后开始推状态：放置第 $n$ 块骨牌时，它有可能向左，也有可能向右，当发生这两种情况是，需要花费步骤去扶起左（右）边的骨牌，这里产生的期望是：

## $pl*\frac{dp[l] + 1}{1 -pl - pr}$

和

## $pr*\frac{dp[r] + 1}{1 -pl - pr}$

其中 $dp[l]$ 和 $dp[r]$ 分别表示左边骨牌的期望和右边骨牌的期望。

但放最后一块骨牌时，它还可能刚好不倒。  
所以就有了状态转移方程：


### $dp[i]=pl*\frac{dp[l] + 1}{1 -pl - pr}+pr*\frac{dp[r] + 1}{1 -pl - pr}+dp[l]+dp[r]+1$

接下来要做的就是枚举位置了，然后每次找到一个最优的点，并更新最优位置，最后输出 $dp[n]$

code:

```cpp
#include<stdio.h>
#define min(a,b) a<b?a:b
using namespace std;
int n;double pl,pr;int p;
double dp[1001];//表示放置连续的多米诺的期望步数 

inline double f(int l, int r){
	return (dp[l]+1)*pl / (1-pl-pr) + (dp[r] + 1)*pr / (1-pl-pr) + (1-pl-pr) * (dp[l] + dp[r] + 1) / (1-pl-pr);
}

int main(){
	
	while(~scanf("%d",&n) && n){
		scanf("%lf%lf",&pl,&pr);
		dp[0] = 0;
		dp[1] = 1/(1-pl-pr);
		
		p=0;
		
		for(int i=2;i<=n;++i){
			dp[i] = f(p,i-p-1);
			for(int j=p+1;j<=i;++j){
				double ans = f(j,i-j-1);
				
				if(ans<=dp[i]){
					dp[i] = ans;
					p = j;
				}
				
				else break;
			}
		}
		
		printf("%.2lf\n",dp[n]);
	}
	return 0;
	
} 
```

但这是$O(n^2)$的算法，网上有大佬说可以优化到$O(n)$  
原话：“可以根据动态规划时候，$dp[i]$ 这个数组在找寻最小值的时候，其实方程是满足一个下凹函数的，所以这步实际上可以利用三分求解，复杂度为$O(nlog(n))$，然后实际上，对于下凹函数，那么其实对于下次找最小值的位置，是不会减小的，因此如果每次维护记录下上次找到答案的位置，这样均摊下来，时间复杂度就能优化到$O(n)$”

反正我没怎么理解，但他的意思就是把

```cpp
for(int i=2;i<=n;++i){
			dp[i] = f(p,i-p-1);
			for(int j=p+1;j<=i;++j){
				double ans = f(j,i-j-1);
				
				if(ans<=dp[i]){
					dp[i] = ans;
					p = j;
				}
				
				else break;
			}
		}
```

改成

```cpp
for(int i = 2; i <= n; ++i) {
        dp[i] = calc(0, i - 1);
        for(int j = 1; j < i; ++j) {
            dp[i] = min(dp[i], calc(j, i - j - 1));
        }
    }
```

于是我就试了一下$......$

[$O(n)$](https://www.luogu.org/record/show?rid=8144763)的  
[$O(n^2)$](https://www.luogu.org/record/show?rid=8144731)的

~~于是愉快地翻车了~~

---

## 作者：Gyan (赞：2)

## Dumb Bones 骨牌

[更好的阅读体验](https://www.cnblogs.com/gyan083/p/15523314.html)

#### 题意
[UVA10529 Dumb Bones 骨牌](https://www.luogu.com.cn/problem/UVA10529)

你试图把一些多米诺骨牌排成直线，然后推倒它们。但是如果你在放骨牌的时候不小心把刚放的骨牌碰倒了，它就会把相临的一串骨牌全都碰倒，而你的工作也被部分的破坏了。

比如你已经把骨牌摆成了 `DD__DxDDD_D` 的形状（侧视图）（其中 `D` 代表骨牌， `_` 和 `x` 均代表还没有放骨牌的空位），而想要在 `x` 这个位置再放一块骨牌。它可能会把左边的一块骨牌或右边的三块骨牌碰倒，而你将不得不重新摆放这些骨牌。

给出你要摆放的骨牌数目，以及放骨牌时它向左和向右倒的概率（每一块骨牌都一样）。

为了使期望摆放骨牌的次数最少，你可以采用某种特定的摆放顺序。求这个最少的期望摆放骨牌次数。


------------

#### 算法 1

概率 + 最优解，可以考虑用区间 DP。

考虑一个区间。枚举这个区间里最后摆放的一块骨牌的位置，把原区间分割成左右两个子区间。

设原区间期望最少摆放次数为 $E$ ，左区间为 $E_1$ ，右区间 $E_2$ 。此时最后一块骨牌还没有放上去，那么设这个空位的位置是 $x$ 。

已知每块骨牌向左倒的概率是 $P_l$ ，向右是 $P_r$ 。

单独看 $x$ 这一个骨牌，它不倒的概率是 $1-P_l-P_r$ ，那么使它不倒的期望摆放次数是 $\dfrac1{1-P_l-P_r}$ 。

注意这个次数里：最后一次是不倒的，之前的有些向左有些向右。因为向左的概率是 $P_l$ ，所以向左倒的次数就是 $\dfrac1{1-P_l-P_r}\times P_l$ 。由于每向左倒一次，左区间的就要全部重新摆放。左区间放好一次需要 $E_1$ 个摆放，所以一共左区间要摆 $\dfrac{P_l}{1-P_l-P_r}\times E_1$ 次。同理右区间一共要放置 $\dfrac{P_r}{1-P_l-P_r}\times E_2$ 次。

还有就是放 $x$ 之前需要先把左右区间都摆好一次，共 $E_1+E_2$ 个摆放。

**最后状态转移方程就是**
$$
E=E_1+E_2+\frac1{1-P_l-P_r}+\frac{P_l\times E_1}{1-P_l-P_r}+\frac{P_r\times E_2}{1-P_l-P_r}
$$
*于是我们轻松的写出了下面这一坨：*

```cpp
int n;
double pl, pr;//向左、向右倒的概率
double f[N][N];//dp 数组（记忆化搜索）

double dfs(int l, int r) {//区间左右端点
	double &E = f[l][r];//使用引用方便又快捷
	if (E > eps) return E;//记忆化
	if (l > r) return E = 0.0;//边界
	if (l == r) return E = 1.0/(1.0-pl-pr);//只放一个
	E = inf;//先来一个极大值
	for (int i=l; i<=r; ++i) {//枚举最后一个摆放的位置 i
		double E1 = dfs(l, i-1);//左区间摆放次数
		double E2 = dfs(i+1, r);//右区间
		E = std::min(
			E,
			E1 + E2 + 1.0/(1.0-pl-pr) + pl*E1/(1.0-pl-pr) + pr*E2/(1.0-pl-pr)//刚才的方程
		);//通过 min 获得最优解
	}
	return E;
}
```

~~然后光荣地 T 飞爆零了。~~


------------


#### 算法 2

上面的算法是 $O(n^3)$ 的，当然过不了，我们考虑降维。

因为每块牌都一模一样，显然对于所有长度相同的区间，它们的 $E$ 都是相同的。

把状态重新设置为区间长度，就只有不同长度的区间才需要转移，状态转移方程不变。

**获得正解：**

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

#define N 1030
const double eps = 1e-8;
const double inf = 1e20;

double pl, pr;//向左、向右倒的概率
double f[N];

double dfs(int n) {//长度为 n 的区间
	double &E = f[n], E1, E2;//还是引用
	if (E > -0.5) return E;//让 f[0]=0.0 和 f[1]=1.0/(1.0-pl-pr) 都可以自然转移
	E = inf;
	for (int i=1; i<=n; ++i) {
		E1 = dfs(i-1), E2 = dfs(n-i);//左、右区间的答案
		E = min(
			E,
			E1 + E2 + f[1] + pl*E1*f[1] + pr*E2*f[1]
		);
	}
	return E;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);//关闭流同步
	while (true)
	{
		int n;
		cin >> n;
		if (!n) break;
		cin >> pl >> pr;
		for (int i=2; i<=n; ++i) f[i] = -1.0;//注意细节
		f[1] = 1.0 / (1.0 - pl - pr);//同时 f[0]=0.0
		printf("%.2f\n", dfs(n));
	}
	return 0;
}
```



---

## 作者：Strelitzia (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/UVA10529)

---

定义 $dp_i$ 为搭 $i$ 张骨牌的期望次数。有答案为 $dp_n$，初始状态为  $Up = \dfrac{1}{1-P_l-P_r},dp_0 = 0,dp_1 = Up$ 。

我们枚举在搭好的 $i - 1$ 张骨牌中插入的位置，根据定义可以得到转移式：


$dp[i] = \min(dp_{j - 1} + dp_{i - j} + 1 + (dp_{j - 1} + 1) * Up * Pl + (dp_{i - j} + 1) * Up * Pr,dp_i)$

这是为什么呢，$Up$ 是要重构的期望值，有 $Pl$ 的概率向左边倒去，这时候，

我们又需要重构 $dp_{j - 1}$ 和当前这个骨牌，所以是 $(dp_{j - 1} + 1) * Up * Pl$，右边同理。

```cpp
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 100005;

int n;
double Pl,Pr,dp[maxn];
int main () {
	read(n);
	while (n) {
		scanf("%lf %lf",&Pl,&Pr);
		memset(dp,0,sizeof dp);
		double Up = 1.0 / (1 - Pl - Pr);
		dp[1] = Up;
		for (int i = 2 ; i <= n ; ++ i) {
			dp[i] = 99999999;
			for (int j = 1 ; j <= i ; ++ j) {
				dp[i] = min(dp[j - 1] + dp[i - j] + 1 + (dp[j - 1] + 1) * Up * Pl + (dp[i - j] + 1) * Up * Pr,dp[i]);
			}
		}
		printf("%.2lf\n",dp[n]);
		read(n);
	}
	return 0;
}
```

---

## 作者：pomelo_nene (赞：1)

定义 $dp_i$ 为搭 $i$ 张骨牌的期望次数。有答案为 $dp_n$，初始状态为 $dp_0 \gets 0,dp_1 \gets \dfrac{1}{1-P_l-P_r}$。

考虑转移，我们枚举在搭好的 $n-1$ 张骨牌中插入的位置，根据定义可以得到方程：

$$
dp_{i} = \min (dp_{j-1}+dp_{i-j}+1+\dfrac{dp_{j-1} \times P_l}{1-P_l-P_r}+\dfrac{dp_{i-j} \times P_r}{1-P_l-P_r})
$$

解释这个方程，我们枚举插入点 $j$，现在我们搭好的骨牌分成了两部分。首先期望次数需要合并，再加上我们新加入的骨牌。考虑这个骨牌对两边骨牌的影响，我们期望重构 $\dfrac{1}{1-P_l-P_r}$ 次，左边的为 $j-1$ 一段，右边的为 $i-j$ 一段。返回看 dp 定义，这个方程就是正确的了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long double dp[1005];
/*
dp[i] i骨牌 期望次数 
*/
int main(){
	int n;
	while(scanf("%d",&n) && n)
	{
		long double pl,pr;
		scanf("%Lf %Lf",&pl,&pr);
		long double fall=1-pl-pr;
		dp[0]=0,dp[1]=1.0/fall;
		for(int i=2;i<=n;++i)
		{
			long double p=-1;
			for(int j=1;j<=i;++j)
			{
				if(p==-1)	p=dp[j-1]+dp[i-j]+1+(dp[j-1]+1)/fall*pl+(dp[i-j]+1)/fall*pr;
				p=min(p,dp[j-1]+dp[i-j]+1+(dp[j-1]+1)/fall*pl+(dp[i-j]+1)/fall*pr);
			}
			dp[i]=p;
		}
		printf("%.2Lf\n",dp[n]);
	}
	return 0;
}
```

---

## 作者：Y_QWQ_Y (赞：1)

本题是一道期望与概率的dp问题。

请先阅读[前置](https://www.luogu.com.cn/blog/lahm/solution-uva10529)。

式子在这只大佬的题解里，我也就不赘述了。

但是他用的是 $\Theta(n^2)$ 的算法，但我们不能满足于时间仅仅卡过，所以我们需要优化。

我们可以发现，其实 $E$ 是单增的，所以我们可以用二分优化，时间复杂度：$\Theta(n\log n)$。

但是我们还可以继续优化，因为 $E$ 不仅是单增的，还是凹的。

通过这个性质，我们可以证明决策中的 $k$ 是不减的，所以可以记录上次使用的 $k$ 来优化算法。

通过上面的优化，我们得到了一个 $\Theta(n)$ 的算法。

说句大实话：其实 $\Theta(n)$ 算法的代码跟 $\Theta(n^2)$ 算法的代码比起来长度差不多。

下面是代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define sycn ios::sync_with_stdio (0),cin.tie (0), cout.tie (0)
using namespace std;
int n;
double l, r, f[1001];
double dp (int i, int j){return f[j] + f[i - j - 1] + (1 + l * f[j] + r * f[i - j - 1]) / (1 - l - r);}
signed main ()
{
	sycn;
	while (cin >> n && n)
	{
		cin >> l >> r;
		for (int i = 1, j = 0; i <= n; ++ i)
		{
			while (j < i - 1 && dp (i, j) > dp (i, j + 1))++ j;
			f[i] = dp (i, j);
		}
		printf ("%.2lf\n", f[n]);
	}
	return 0;
}
```

---

## 作者：Rorschachindark (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/UVA10529)
# 题目大意
给出 $n,pl,pr$ ，表示有 $n$ 个多米诺骨牌，每放一个有 $pl$ 的概率往左倒，有 $pr$ 的概率往右倒，放列顺序不定，问放完 $n$ 个多米诺骨牌的最小期望步数。（一个多米诺骨牌倒了它所倒方向的相邻多米诺骨牌也会倒）

$n\le 1000$
# 思路
看到题解里面似乎讲得不是特别清楚，这里发一篇造福大众。

首先需要注意的是 **：放列顺序不定** ，于是我们就不能直接递推，怎么办呢？我们发现，如果我们要构成连续的 $i$ 个多米诺骨牌，如果我们选择最后放 $j$ 这个位置，那么 $[1,j)$ 以及 $(j+1,i]$ 一定已经放好了。我们发现这其实就是我们的突破口。我们可以设 $f_i$ 表示放好连续的 $i$ 个多米诺骨牌的期望次数，可以得到转移式：

$$f_i=\min_{j=1}^{i} \{\dfrac{1-pr}{1-pl-pr}\times f_{j-1}+\dfrac{1-pl}{1-pl-pr}\times f_{i-j}\}+\dfrac{1}{1-pl-pr}$$

解释一下，$\dfrac{1-pr}{1-pl-pr}$ 其实就是 $[1,j)$ 重构的次数，因为会倒 $\dfrac{1}{1-pl-pr}-1$ 次，而每次都有 $\dfrac{pl}{pl+pr}$ 的概率往左边倒，让 $[1,j)$ 全部重构。右边同理。

于是我们就可以 $\Theta(n^2)$ 解决这道题目。

但是这并不能满足我们对时间复杂度的渴求，我们通过打表发现以下两个事情：

![](https://i.loli.net/2020/08/13/Bciynjh5WKVzEfg.png)

![](https://i.loli.net/2020/08/13/98okzxq1iSQC4Ve.png)

用自然语言描述就是：

- **决策点单调递增**

- **对于 $\forall i$ ，点 $j$ 对 $i$ 产生的贡献是一个下凸函数**

感性理解一下其实就是说 $f_{j-1}$ 会比 $f_{i-j}$ 变化速度更慢 ，当 $j\le i-j$ 的时候。于是，我们就可以直接推着决策点走就行了，时间复杂度 $\Theta(n)$ 。

不过看到题解里面有人打的是这种的：

![](https://i.loli.net/2020/08/13/XPDnhzlZBf74svQ.png)

我自认为的话这种打法其实还是 $\Theta(n^2)$ ，很明显，决策点都是 $1$ 的时候它就死掉了，不过可能常数比较小。
# $\texttt{Code}$
## $\Theta(n)$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define MAXN 1005

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

int n;double pl,pr,dp[MAXN];

double contri (int i,int j){return (1.0 - pr) / (1.0 - pl - pr) * dp[j - 1] + (1.0 - pl) / (1.0 - pl - pr) * dp[i - j] + 1.0 / (1.0 - pl - pr);}

signed main(){
	while (1){
		read (n);
		if (!n) return 0;
		scanf ("%lf%lf",&pl,&pr);
		dp[1] = 1.0 / (1.0 - pl - pr);
		int st = 1;
		for (Int i = 2;i <= n;++ i){
			dp[i] = 0x3f3f3f3f;
			while (st < i && contri (i,st + 1) < contri (i,st)) ++ st;
			dp[i] = contri (i,st);
		}
		printf ("%.2f\n",dp[n]);
	}
	return 0;
}
```
## $\Theta(n^2)$
```cpp
#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define MAXN 1005

template <typename T> inline void read (T &t){t = 0;char c = getchar();int f = 1;while (c < '0' || c > '9'){if (c == '-') f = -f;c = getchar();}while (c >= '0' && c <= '9'){t = (t << 3) + (t << 1) + c - '0';c = getchar();} t *= f;}
template <typename T,typename ... Args> inline void read (T &t,Args&... args){read (t);read (args...);}
template <typename T> inline void write (T x){if (x < 0){x = -x;putchar ('-');}if (x > 9) write (x / 10);putchar (x % 10 + '0');}

int n;double pl,pr,dp[MAXN];

signed main(){
	while (1){
		read (n);
		if (!n) return 0;
		scanf ("%lf%lf",&pl,&pr);
		dp[1] = 1.0 / (1.0 - pl - pr);
		for (Int i = 2;i <= n;++ i){
			dp[i] = 0x3f3f3f3f;
			for (Int j = 1;j <= i;++ j)
				dp[i] = min (dp[i],(1.0 - pr) / (1.0 - pl - pr) * dp[j - 1] + (1.0 - pl) / (1.0 - pl - pr) * dp[i - j] + 1.0 / (1.0 - pl - pr));
		}
		printf ("%.2f\n",dp[n]);
	}
	return 0;
}
```
# P.S.
虽然这道题数据比较小看不出 $\Theta(n)$ 和 $\Theta(n^2)$ 的差距，不过还是有点区别的，如下：

![](https://i.loli.net/2020/08/13/Oys7mYAV9uIt3iL.png)

---

## 作者：封禁用户 (赞：0)

首先，我们应该明确怎么找到最佳排放策略。我们可以考虑在位置 $i$ 放上最后一块骨牌，显然 $i$ 与前面的 $i - 1$ 块骨牌和后面 $n - i$ 块骨牌是互不影响的。所以，我们可以假设摆放 $i-1$ 快骨牌需要的次数平均是 $E_1$，拜访 $n - i$ 块骨牌需要的次数平均是 $E_2$。摆完这两段后，我们在摆上最后一块。如果把左边碰到了，那只能重新摆放，右边也同理。所以摆放的平均值 $E$ 是：

$E = \dfrac{1-P_r}{1-P_l-P_r}E_1+\dfrac{1-P_l}{1-P_l-P_r}E_2+\dfrac{1}{1-P_l-P_r}$ 。

得到这个式子后，我们就可以通过 **动态规划** 来得到最优的方案。假设 $E_i$ 是摆放第 $i$ 块骨牌需要的最少期望次数，那么我们可以得到状态转移方程是：

$E_i = \min(\dfrac{1-P_r}{1-P_l-P_r}E_k + \dfrac{1-P_l}{1-P_l-P_r}E_{i-1-k}+\dfrac{1}{1-P_l-P_r}) (0 \le k \le i - 1)$。

这样我们就得到了一个 $O(n^2)$ 的算法。这样很容易超市。所以，我们要想一个 $O(n)$ 的算法。

如果我们用二分进行优化，时间复杂度就将为了 $O(nlog_n)$ 。但是， $E$ 这个数列不是单增的，而是凸的（如果 $P_lP_r = 0$ ，就不凹也不凸，但也不影响讨论），所以我们可以证明 $k$ 一定不减。所以，我们只需记录上一次使用的 $k$，就能得到一个 $O(n)$ 的算法。

## AC代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long LL;
const int MAXN = 2e5 + 10;
const int INF = 0x3f;
int n;
double pl, pr, f[MAXN];
inline double dp(int i, int j){
	return f[j] + f[i - j - 1] + (1 + pl * f[j] + pr * f[i - j - 1]) / (1 - pl - pr);
}
int main()
{
	int i, j;
	while(true){
		cin >> n;
		if(n == 0)break;
		cin >> pl >> pr;
		for(i = 1,j = 0;i <= n; i++){
			while(j < i - 1 && dp(i, j) > dp(i, j + 1))j++;
			f[i] = dp(i, j);
		}
		cout << f[n];
	}
    return 0;
}
```

---

