# Marmots (medium)

## 题目描述

Good job! Now that Heidi is able to distinguish between Poisson and uniform distributions, she is in a good position to actually estimate the populations.

Can you help Heidi estimate each village's population?

# 题解

## 作者：Confringo (赞：1)

本题考查的是泊松分布和均匀分布之间的区别。

根据我们在 easy 题的经验，我们已经可以分辨出泊松分布和平均的区别了，那么我们把写过的代码 ~~copy~~ 借鉴过来，在输出的地方修改一下即可。 

如果是泊松分布，我们只需求所有数据的平均值，这是我们早已求过的 ave 变量。而对于均匀分布，我们可以用最大值和最小值的平均值来解决问题。

需要注意的是 maxn 和 minn 最开始应该分别初始化为 -inf 和 inf 。

好，接下来上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
    	int a[255];
    	int s=0,maxn=INT_MIN,minn=INT_MAX;
    	for (int i=0;i<250;i++){
        	scanf("%d",&a[i]);
        	if (a[i]>maxn) maxn=a[i];//最大
        	if (a[i]<minn) minn=a[i];//同上，最小
        	s+=a[i];
    	}
    	double ave=s/250.0;//此处计算平均值
    	int cnt=0;
    	for (int i=0;i<250;i++){
       		if (fabs(a[i]-ave)<=ave/2) cnt++;
    	}
    	if (cnt>250*0.75) cout<<int(round(ave))<<"\n";//泊松分布，输出平均
    	else cout<<int((maxn+minn)/2)<<"\n";//平均分布，输出最大和最小的平均值
	}
	return 0;
}
```
备注：代码部分借鉴了 easy 题代码。地址：[https://blog.csdn.net/weixin_34161083/article/details/93597988](https://blog.csdn.net/weixin_34161083/article/details/93597988)

---

## 作者：N1K_J (赞：0)

被乐子题弄得汗流浃背了。

只看翻译可能看不同题意，在此提供一个我理解的翻译。

有 $T$ 个村庄，每个村庄给出 $N=250$ 个数据以表示其人数，这 $N$ 个数据服从平均分布或泊松分布。easy version 问 $N$ 个数据服从哪一种分布，hard version 要估计村庄人数。

[前置知识（easy version）](https://www.luogu.com.cn/blog/yyz666-lg-blog/marmots-easy-ti-xie)

用 easy version 的方法判断是否为泊松分布。

由于泊松分布下大部分数据分布于一个较小的区间上，因此平均数同样应当接近该区间，所以平均值就是结果。

平均分布应当满足如下条件。

对于实际值（答案）$S$，$N$ 个数分布在 $[S-X,S+X]$ 上概率基本相同，这里 $X$ 是一个足够大的正整数。

因此，答案应当接近于 $\dfrac{\min\left\{a_1,a_2,a_3,\cdots,a_n\right\}+\max\left\{a_1,a_2,a_3,\cdots,a_n\right\}}{2}$。

做完了.

[CODE](https://codeforces.com/contest/802/submission/241133927)

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

题目要求输出村庄人数 $p$ 的值。

显然，当为泊松分布时，村庄人数 $p$ 的值为所有输入数据的均值。若为平均分布，村庄人数 $p$ 的值为所有输入数据的最大值和最小值的平均值。

### AC 代码：
```cpp
#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int maxn,minn;
	for(int i=1;i<=n;++i)
	{
		maxn=-1e9;//定义最大值
		minn=1e9;//定义最小值
		int total=0;
		int sz[250];
		for(int k=0;k<250;++k)//反复输入
		{
			cin>>sz[k];
			total+=sz[k];//计算总和
			if(sz[k]>maxn)maxn=sz[k];//更新最大值
			if(sz[k]<minn)minn=sz[k];//更新最小值
		}
		float pjs=(float)total/250;//计算均值
		int fhs=0;
		for(int i=0;i<250;++i)
		{
			if(sz[i]>=pjs/2&&sz[i]<=(pjs*3)/2)//判断是否靠近均值
			{
				fhs++;
			}
		}
		if(fhs>=250*0.75)cout<<(int)pjs<<"\n";//判断是否为泊松分布
		else
		cout<<(int)(maxn+minn)/2<<"\n";//若不为泊松分布，输出最大值与最小值的均值
	}
}
``````

---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF802E)

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

我们看到，泊松分布主要是集中在中部，那么我们求出整个数列的平均值，如果 $80 \%$ 的数据都分布在平均值的两侧不远，我们就判定这组数据为泊松分布，否则为均匀分布。

如果为泊松分布，那么输出整个数列的平均数 $\text{average}$，如果为均匀分布，由上面所讲的概率函数，输出最大值和最小值的平均数即可。

![泊松分布](https://cdn.luogu.com.cn/upload/image_hosting/vbx0d8vv.png)

## 代码

下面是 AC 代码 $\,\,\,$ [AC 记录](https://www.luogu.com.cn/record/141735115)

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[255],ans,sum,minn,maxn;

int work()
{
	minn = 2e9,maxn = -1;
	sum = 0;
	ans = 0;
	for(int i = 1;i <= 250;i++)
	{
		cin >> a[i];
		sum += a[i];//计算数据的和，从而计算平均数 
		minn = min(minn,a[i]);//最小值 
		maxn = max(maxn,a[i]);//最大值 
	}
	double average = (double)sum / 250;
	double averaged = average / 2;//应当大致分布于平均值的两侧且与平均值的差在平均值的一半以内 
	for(int i = 1;i <= 250;i++)
	{
		if(a[i] - average < averaged && a[i] - average > 0 - averaged) ans++;//统计符合的个数 
	}
	if(ans >= 200) return (int)average;//大于 80%即 200个 
	else return (int)maxn * 0.5 - minn * 0.5;
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

## 作者：_little_Cabbage_ (赞：0)

# CF802E Marmots (medium) 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-cf802e)~~

此题跟 [CF802D](https://www.luogu.com.cn/problem/CF802D) 唯一的区别就是在输出部分不是判断而是输出平均值。

uniform 分布的平均值大家肯定都会算，就是最大数与最小数的平均值。那 poisson 分布呢？

poisson 分布的平均值其实就是我们在 [CF802D](https://www.luogu.com.cn/problem/CF802D) 就已经求过的那 $250$ 个数的平均值四舍五入的结果。

AC 代码
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
		int mx=INT_MIN,mi=INT_MAX;
		for(int i=1;i<=250;i++)
		{
			scanf("%d",&a[i]);
			he+=a[i];
			mx=max(mx,a[i]);
			mi=min(mi,a[i]);
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
			printf("%d\n",int(round(x)));
		}
		else
		{
			printf("%d\n",int((mx+mi)*1.0/2));
		}
	}
}
```

---

