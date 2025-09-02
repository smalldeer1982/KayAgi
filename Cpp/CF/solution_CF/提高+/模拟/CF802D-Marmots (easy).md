# Marmots (easy)

## 题目描述

Heidi is a statistician to the core, and she likes to study the evolution of marmot populations in each of $ V $ ( $ 1<=V<=100 $ ) villages! So it comes that every spring, when Heidi sees the first snowdrops sprout in the meadows around her barn, she impatiently dons her snowshoes and sets out to the Alps, to welcome her friends the marmots to a new season of thrilling adventures.

Arriving in a village, Heidi asks each and every marmot she comes across for the number of inhabitants of that village. This year, the marmots decide to play an April Fools' joke on Heidi. Instead of consistently providing the exact number of inhabitants $ P $ ( $ 10<=P<=1000 $ ) of the village, they respond with a random non-negative integer $ k $ , drawn from one of two types of probability distributions:

- Poisson (d'avril) distribution: the probability of getting an answer $ k $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802D/3800ef7834670e3e97c0f3e37b279e2c0c6dafbf.png) for $ k=0,1,2,3,... $ ,
- Uniform distribution: the probability of getting an answer $ k $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802D/b16ed5068242e81ea04aac7ee7fe27322715cce4.png) for $ k=0,1,2,...,2P $ .

Heidi collects exactly 250 answers per village. Every village follows either the Poisson or the uniform distribution. Heidi cannot tell marmots apart, so she may query some marmots several times, and each time the marmot will answer with a new number drawn from the village's distribution.

Can you help Heidi to find out whether a village follows a Poisson or a uniform distribution?

## 说明/提示

The full example input is visually represented below, along with the probability distribution function it was drawn from (the $ y $ -axis is labeled by its values multiplied by 250).

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802D/c9274c7e7ba8e64005598277624514dac31cbb50.png)

## 样例 #1

### 输入

```
2
92 100 99 109 93 105 103 106 101 99 ... (input is truncated)
28 180 147 53 84 80 180 85 8 16 ... (input is truncated)```

### 输出

```
poisson
uniform
```

# 题解

## 作者：luxiaomao (赞：0)

## [CF802D](https://www.luogu.com.cn/problem/CF802D) 泊松分布与平均分布

自从文章区更新后就没有写题解了。鉴于题解分快掉完了，所以来写一篇。

## Solution

看到题面的概率函数着实吓了一跳，但是仔细看了看发现其实这道蓝题是有点水的。（~~申请降黄！~~）

题目的大意：给出 $T$ 组数据，每组数据有 $250$ 个数，要求你判断每一组数据是属于**泊松分布**还是**平均分布**。

泊松分布：（~~不写概率函数了因为我不会~~）一般来说，如果一组数据中超过 $75\%$ 的数据与这组数据的平均数**接近**，那么这组数据满足泊松分布。（其中对“接近”的定义是，**与平均数的差值不超过平均数的一半**）

平均分布：在本题中，如果一组数据不满足泊松分布，那么就满足平均分布。

如果分析到这一步，那么这道题就已经成为一道较为基础的模拟了。

## Code

请看代码及注释。

```cpp
#include<bits/stdc++.h>
#define N 260
using namespace std;

int T,n = 250,a[N];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		int sum = 0,cnt = 0;//sum 用于计算平均数，cnt用于统计接近平均数的个数
		for(int i = 1;i <= n;i++)
		{
		    scanf("%d",&a[i]);
		    sum += a[i];
		}
		double k = sum*1.0/n;//计算平均数，别忘了开double
		for(int i = 1;i <= n;i++)
		{
		    if(abs(a[i]-k) < k/2)//根据“接近”平均数的定义进行判断
		        cnt++;
		}
		printf("%s\n",cnt >= 187?"poisson":"uniform");//250 个数据只要达到 187 个就算 75% 了
	}
	return 0;//完结撒花！
}
```

感谢阅读~

---

## 作者：henry_qwh (赞：0)

### 题目大意

给出 $250$ 个数据，判断这些数据满足泊松分布还是平均分布。

### 泊松分布和平均分布

#### 泊松分布

泊松分布的概率函数为：

$$P(X=k)=\frac{\lambda^k}{k!}e^{-\lambda},k=0,1,\cdots$$

其中 $\lambda$ 指的是单位时间（或单位面积）内随机事件的平均发生次数。

![](https://cdn.luogu.com.cn/upload/image_hosting/w6ikootc.png)

由上图可以看出，简单来说，泊松分布就是数据大部分都分布在平均数附近。

那么，什么叫做 **大部分** 呢？一般认为，如果 $75\%$ 的数据都分布在平均数附近，那么就说这组数据满足泊松分布。

#### 平均分布

平均分布，又称均匀分布，其概率密度函数为：

$$
f(x)=\begin{cases}
\frac{1}{b-a}&a<x<b\\
0&\text{otherwise}
\end{cases}
$$

简单来说，平均分布就是数据等概率地分布在某一范围内。在本题中，我们认为，若一组数据不满足泊松分布，则满足平均分布。

### 具体实现

我们可以算出数据的平均数。若一个数据大致分布于平均值的两侧且与平均值的差在平均值的一半以内，则称该数据满足泊松分布。记录满足泊松分布的数据个数，若其总数在数据总数的 $75\%$ 以上，则称这一组数据满足泊松分布，否则称这一组数据满足平均分布。

### 参考代码

[**AC记录**](https://www.luogu.com.cn/record/151692320)

```cpp
#include <bits/stdc++.h> 
using namespace std;

const int N = 260;
int a[N];

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int mn = 0x3f3f3f3f,mx = 0,sum = 0,ans = 0;
		for (int i = 1;i <= 250;i++)
		{
			cin >> a[i];
			sum += a[i];
			mn = min(a[i],mn);
			mx = max(a[i],mx);
		}
		double mean = sum*1.0/250;
		for (int i = 1;i <= 250;i++)
			if (a[i]-mean < mean/2 && a[i]-mean > 0-mean/2) ans++;
		if (ans >= 187)	cout << "poisson" << endl;
		else cout << "uniform" << endl;
	}
	
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题意分析
我们可以注意到题目中有两个~~陌生的~~名词，“泊松分布”和“平均分布”。

在一组数据中 $75\%$ 以上的的数据都靠近均值的分布状态称为泊松分布，反之，则为平均分布。      

对于靠近，我们有以下判断方式：
```cpp
a>=k/2 && a<=(k*3)/2
```
其中，数据的值为 $a$，均值为 $k$。         



### AC 代码：
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		int total=0;
		int sz[250];
		for(int k=0;k<250;++k)
		{
			cin>>sz[k];
			total+=sz[k];//统计总和
		}
		float pjs=(float)total/250;//计算均值
		int fhs=0;
		for(int i=0;i<250;++i)
		{
			if(sz[i]>=pjs/2&&sz[i]<=(pjs*3)/2)
			{
				fhs++;//统计靠近均值的数据数量
			}
		}
		if(fhs>=250*0.75)cout<<"poisson\n";//若为泊松分布
		else
		cout<<"uniform\n";//否则为平均分布
	}    
   return 0;//不写 return 0 ，得分 return 0 。
}
``````

---

## 作者：N1K_J (赞：0)

乐子题。

考虑泊松分布的在图象上的特征。

可以注意到大部分的数据分布在一个较小的区间内（相较于平均分布）。

注意到在泊松分布下平均数应当接近于**大部分数**。

也就是说我们可以考虑统计每个数到平均数之间的距离，如果满足 $X-\overline{X} \le X \cdot P$ 的数超过了 $p \cdot N$，那么就是泊松分布。这里 $N = 250$，$P$，$p$ 为一个需要确定的参数。

我的代码里 $p = 0.8$，$P=0.5$

[CODE](https://codeforces.com/contest/802/submission/241131244)

---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF802D)

## 前置知识：泊松分布和均匀分布

### 泊松分布

$\text{Poisson}$ 分布，是一种统计与概率学里常见到的离散概率分布，像下面这张图：

![泊松分布](https://cdn.luogu.com.cn/upload/image_hosting/0k0zs9ms.png)

我们看到，这张图里大部分数据集中于中间的几段，而分布较远的则几乎趋近于 $0$。像这种类似于正态分布的分布图象，被称为 $\text{Poisson}$ 分布。

下面是几个 $\text{Poisson}$ 分布的性质：

- 泊松分布的概率函数为：

$$P(x = k) = {{\lambda ^ k} \over {k!}}e^{-\lambda},k = 0,1,\cdots$$

- 特征函数为：

$$\psi(t) = exp(\lambda(e ^{it} - 1))$$

$1.$ 泊松分布是一种描述和分析稀有事件的概率分布。要观察到这类事件，样本含量必须很大。 

$2.$ $\lambda$ 是泊松分布所依赖的唯一参数。$\lambda$ 值愈小，分布愈偏倚，随着增大，分布趋于对称。 

$3.$当 $\lambda = 20$ 时分布泊松分布接近于正态分布；当 $\lambda = 50$ 时，可以认为泊松分布呈正态分布。实际上，当 $\lambda \geq 20$ 时就可以用正态分布来近似地处理泊松分布的问题。

### 均匀分布

在概率论和统计学中，均匀分布也叫矩形分布，它是对称概率分布，在相同长度间隔的分布概率是等可能的。

记数据中最小值为 $a$，最大值为 $b$，则概率函数可以如下表示：

$$f(x)= \begin{cases} \frac{1}{b - a} & a < x < b \\ 0 & else.\end{cases}$$


**那么，如何用 $\text{OI}$ 实现判断两者呢？**

## 分析

我们看到，泊松分布主要是集中在中部，那么我们求出整个数列的平均值，如果 $80 \%$ 的数据都分布在平均值的两侧不远，我们就判定这组数据为泊松分布，否则为均匀分布，输出答案即可。

![泊松分布](https://cdn.luogu.com.cn/upload/image_hosting/vbx0d8vv.png)

## 代码

下面是 AC 代码 $\,\,\,$ [AC 记录](https://www.luogu.com.cn/record/141734678)

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[255],ans,sum;

string work()
{
	sum = 0;
	ans = 0;
	for(int i = 1;i <= 250;i++)
	{
		cin >> a[i];
		sum += a[i];//计算数据的和，从而计算平均数 
	}
	double average = (double)sum / 250;
	double averaged = average / 2;//应当大致分布于平均值的两侧且与平均值的差在平均值的一半以内 
	for(int i = 1;i <= 250;i++)
	{
		if(a[i] - average < averaged && a[i] - average > 0 - averaged) ans++;//统计符合的个数 
	}
	if(ans >= 200) return "poisson";//大于 80%即 200个 
	else return "uniform";
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		cout << work() << endl;
	}
    return 0;
}
```


---

## 作者：Planetary_system (赞：0)

## 题面解释：
给定 $250$ 个数，问你它是泊松分布（poisson）还是均匀分布（uniform）。

同时本题多测。

## 思路分析：
这道题本身十分简单，就是要理解其中的概念。

当一个数列 $\ge 75\%$ 的数都靠近数列的均值时，称它泊松分布；反之，称它均匀分布。

而对于什么样的数算靠进数列的均值呢？我们存在以下判断方式：

```cpp
fabs((double)(a[i])-q)<=q/2
```

其中 $q$ 为均值，fabs 为求浮点数绝对值的函数。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=250;
int m,a[N+10];
signed main(){
    scanf("%lld",&m);
    while(m--){
        int sum=0,cnt=0;
        for(int i=1;i<=N;i++)
            scanf("%lld",&a[i]),sum+=a[i];
        double q=sum*1.0/N;
        for(int i=1;i<=N;i++)
            if(fabs((double)(a[i])-q)<=q/2)cnt++;
        if(cnt>=75.0*N/100)printf("poisson\n");
        else printf("uniform\n");
    }
    return 0;
}
```

谢谢！

---

## 作者：_little_Cabbage_ (赞：0)

# CF802D Marmots (easy) 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-cf802d)~~

本题主要考察对 poisson 分布和 uniform 分布的认知。

我一开始也不知道 poisson 分布和 uniform 分布是啥，看到这题一脸懵。然后查了一下，掌握了一个要点：

当一个数列 $\ge 75\%$ 的数都靠近数列的均值，即：

```cpp
fabs((double)(a[i])-x)<=x/2
```
那么就是 poisson 分布，否则就是 uniform 分布。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[260];
int main()
{
	int q;
	cin>>q;
	while(q--)
	{
		long long he=0;
		for(int i=1;i<=250;i++)
		{
			scanf("%d",&a[i]);
			he+=a[i];
		}
		double x=he*1.0/250;
		int cnt=0;
		for(int i=1;i<=250;i++)
		{
			if(fabs((double)(a[i])-x)<=x/2)
			{
				cnt++;
			}
		}
		if(cnt>=250*0.75)
		{
			printf("poisson\n");
		}
		else
		{
			printf("uniform\n");
		}
	}
}
```
[AC 记录](https://www.luogu.com.cn/record/136524114)

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF802D)
# 题意
给你一个序列，判断它是 $Poisson$ 分布还是 $Uniform$ 分布。
# 思路
均值为 $n$，数字为 $k$，当 $|n-k| \le n \times 0.5$，这个数在其数列均值附近。

当 $\ge 75\%$ 的数都在这个数列均值附近时，则是 $Poisson$ 分布。

# Code
```
#include<bits/stdc++.h>
using namespace std;
int T,i,s,sum,a[1001];
double x;
int main(){
    cin>>T;
    while(T--){
        s=sum=0;
        for(i=1;i<=250;i++)
            cin>>a[i],s+=a[i];
        x=s/250.0;
        for(i=1;i<=250;i++)
            if(abs(a[i]-x)<=x/2) sum++;
        if(sum>250.0*0.75) cout<<"poisson\n";
        else cout<<"uniform\n";
    }
    return 0;
}
```


---

## 作者：CGDGAD (赞：0)

## 题解 $\texttt{CF802D Marmots(easy)}$

----

### 题目大意

这题题面很长。但实际意思就是：给你一个序列，让你判断它的分布形式是**Poisson分布**还是**Uniform分布**。~~(我也搞不清这两种分布具体指什么，题面里这么说那就这样叫吧)~~

如图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF802D/c9274c7e7ba8e64005598277624514dac31cbb50.png)

上面为Uniform分布的一个例子，下面为Poisson分布的一个例子。

----

### 思路

主要就是在如何判定是Poisson分布还是Uniform分布。

我们仔细观察一下图，发现Poisson分布它大部分的值都在平均值附近（差不多是那条黑线）。

然而Uniform分布没啥规律，中间大，两头小。

谷歌上搜了一下Poisson分布的具体内容，全是数学公式，看都看不懂，于是打算找规律瞎做一个做法。

我们就可以根据观察结果来想一个做法：

**当 $\geq 75\%$ 的数都在这个数列均值附近时，我们就判断这是一个Poisson分布。**

定义**一个数在这个数列均值附近**：设均值为 $n$ ，数为 $k$ ，则当 $|n - k| \leq \dfrac12 \cdot n$ 即 $\dfrac12 \cdot n \leq k \leq \dfrac32 \cdot n$ 时，这个数在这个数列的均值附近。

----

### 代码

```cpp
#include <cstdio>
#include <cmath>
int t, a[251];
int main() {
  scanf("%d", &t);
  while ( t-- ) {
    int sum = 0;
    for (int i = 1; i <= 250; i += 1) {
      scanf("%d", &a[i]);
      sum += a[i];
    }
    double aver = (double)sum / 250.0;
    int count = 0;
    for (int i = 1; i <= 250; i += 1) {
    	if ( std::fabs((double)a[i] - aver) <= aver / 2 )
            count += 1;
    }
    if ( (double)count / 250.0 >= 0.75 ) {
      printf("poisson\n");
    } else {
      printf("uniform\n");
    }
  }
  return 0;
}
```



---

## 作者：18lxxrz (赞：0)

### 思路

------------

如果你仔细读题的话，那么……泊松分布和方差有关。


接下来就~~水了~~


------------

#### Code（粗鄙的代码）

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500];

int main ()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
    	memset(a,0,sizeof a);
    	int s=0,cnt=0;
    	for(register int i=0;i<250;++i)
        	scanf("%d",&a[i]),s+=a[i];//累加和
    	double ave=s/250.000;
    	for(register int i=0;i<250;++i)//求方差（纯暴力）
		{
        	if(fabs(a[i]-ave)<=ave/2) cnt++;
    	}
    	if(cnt>250*0.7500)//判断是否均匀分布
        	puts("poisson");
    	else
        	puts("uniform");
	}
	return 0;
}
```

------------
此题感谢[weixin_33716154](https://blog.csdn.net/weixin_33716154/article/details/94757271)

---

