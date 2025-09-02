# Wizards and Trolleybuses

## 题目描述

In some country live wizards. They love to ride trolleybuses.

A city in this country has a trolleybus depot with $ n $ trolleybuses. Every day the trolleybuses leave the depot, one by one and go to the final station. The final station is at a distance of $ d $ meters from the depot. We know for the $ i $ -th trolleybus that it leaves at the moment of time $ t_{i} $ seconds, can go at a speed of no greater than $ v_{i} $ meters per second, and accelerate with an acceleration no greater than $ a $ meters per second squared. A trolleybus can decelerate as quickly as you want (magic!). It can change its acceleration as fast as you want, as well. Note that the maximum acceleration is the same for all trolleys.

Despite the magic the trolleys are still powered by an electric circuit and cannot overtake each other (the wires are to blame, of course). If a trolleybus catches up with another one, they go together one right after the other until they arrive at the final station. Also, the drivers are driving so as to arrive at the final station as quickly as possible.

You, as head of the trolleybuses' fans' club, are to determine for each trolley the minimum time by which it can reach the final station. At the time of arrival at the destination station the trolleybus does not necessarily have zero speed. When a trolley is leaving the depot, its speed is considered equal to zero. From the point of view of physics, the trolleybuses can be considered as material points, and also we should ignore the impact on the speed of a trolley bus by everything, except for the acceleration and deceleration provided by the engine.

## 说明/提示

In the first sample the second trolleybus will catch up with the first one, that will happen at distance 510.5 meters from the depot. The trolleybuses will go the remaining 9489.5 meters together at speed 10 meters per second. As a result, both trolleybuses will arrive to the final station by the moment of time 1000.5 seconds. The third trolleybus will not catch up with them. It will arrive to the final station by the moment of time 11000.05 seconds.

## 样例 #1

### 输入

```
3 10 10000
0 10
5 11
1000 1
```

### 输出

```
1000.5000000000
1000.5000000000
11000.0500000000
```

## 样例 #2

### 输入

```
1 2 26
28 29
```

### 输出

```
33.0990195136
```

# 题解

## 作者：wangziyang_NORE (赞：3)

# 思路
这道题涉及到了很多物理知识。

先出结论，当电车行驶到指定路程时，有两种可能。

我们先分析一下两种可能的临界位置。

![](https://cdn.luogu.com.cn/upload/image_hosting/j6nfaw1c.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

根据图片，当速度达到最高时，位移就是阴影部分三角形的面积。根据三角形面积公式得：$x=\frac{1}{2}\cdot v_{max}\cdot t=\frac{v_{max}^{2}}{2a}$

（事先声明：$x$：位移，$a$：加速度，$t$：时间，$v$：速度，$v_{max}$：最大速度）
### 情况一：在加速过程中到达终点 （$\frac{v_{max}^{2}}{2a}\ge x$）
先说一个公式：$x=\frac{1}{2}at^{2}$

怎么证明呢？

根据上图，在匀加速直线运动中：$a=\frac{\Delta v}{\Delta t}$，在 $v-t$ 图像中，$x$ 就是以 $t$ 为底，$v$ 为高的三角形的面积。

该三角形的底为 $t$，高为 $v$，因为起始速度为 $0$，且时间从 $0$ 开始，所以 $\Delta v$ 和 $\Delta t$ 可以直接理解为 $v$ 和 $t$，所以面积 $x=\frac{1}{2}vt$，所以原等式就是：$x=\frac{1}{2}at^{2}$，移项得 $t=\sqrt{\frac{2x}{a}}$。
### 情况二：在匀速时到达终点 （$\frac{v_{max}^{2}}{(2a)}<x$）
这个就比较麻烦了

![](https://cdn.luogu.com.cn/upload/image_hosting/1nkl091r.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

这里的路程 $x$ 就是以 $t1$（跑完加速路段所用时长）为底，$v_{max}$ 为高的三角形的面积加上一个长为 $t-t1$，宽为 $v_{max}$ 的长方形。

那么可以列出式子：$x=\frac{1}{2}\times v_{max}\times t1+v_{max}(t-t1)$。

我们又知道：$t1=\frac{v_{max}}{a}$（原式是 $a=\frac{v}{t}$）

化简原式：$x=\frac{v_{max}^{2}}{2a}+v_{max}\times t-\frac{v_{max}^{2}}{a}=v_{max}\times t-\frac{v_{max}^{2}}{2a}$

继续化简：$x+\frac{v_{max}^{2}}{2a}=v_{max}\times t$

两边同时除以 $v_{max}$：$t=\frac{x}{v_{max}}+\frac{v_{max}}{2a}$

**综上所述：当 $\frac{v_{max}^{2}}{2a}\ge x$ 时，$t=\sqrt{\frac{2x}{a}}$;当 $\frac{v_{max}^{2}}{2a}<x$ 时，$t=\frac{x}{v_{max}}+\frac{v_{max}}{2a}$。**
# 注意事项
**开 long double！**

**电车互相之间不能超车！**

**出发时间不同！**
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,s,t,v;
long double ans[100005];
int main()
{
	scanf("%lld%lld%lld",&n,&a,&s);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&t,&v);
		if(v*v/a/2>=s)
		{
			ans[i]=(long double)sqrt(2.0*s/a);
		}
		else
		{
			ans[i]=(long double)s*1.0/v+v*1.0/2/a;
		}
		ans[i]+=t;
		ans[i]=max(ans[i-1],ans[i]);
		printf("%.10Lf\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

## 题解：CF167A Wizards and Trolleybuses

### 解题思路

**贪心** $+$ **分情况讨论**即可。

贪心思考：**使用最大加速一定不劣于较小的加速度**。

- 情况 $1$：在加速路段中到达终点，答案为 $ans_i = \sqrt{\frac{2d}{a}} + t_i$，也就是自 $t_i$ 时出发后使用最大加速，直到终点。
- 情况 $2$：在完成加速后经过一段匀速运动到达终点，答案为 $ans_i = \frac{d-\frac{v_i^2}{2a}}{v_i} + \sqrt{\frac{v_i^2}{2a}} + t_i$，即使用最大加速，直到最高速度，匀速前进到终点。

但是需要注意，~~这是单车道，不能超车，~~ 最后第 $i$ 辆车到达的时间 $ans_i$ 为 $\max(ans_i , ans_i - 1)$。

证明：[link](https://www.luogu.com.cn/article/98wy39mi)。

### 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
double a , d , ans[1000005] , t[1000005] , v[1000005] , tmp , tmp2;
int n;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin >> n >> a >> d; 
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> t[i] >> v[i];
		if(a * d * 2 < v[i] * v[i])
		{
			ans[i] = sqrt(d / a * 2) + t[i];
		}
		else
		{
			tmp = v[i] * v[i] / a / 2;
			tmp2 = tmp;
			tmp = d - tmp2;
			ans[i] = tmp / v[i] + sqrt(tmp2 / a * 2) + t[i];
		}
	}
	ans[0] = -1;
	for(int i = 1 ; i <= n ; i++)
	{
		ans[i] = max(ans[i] , ans[i - 1]);
		printf("%.12lf\n" , ans[i]);
	}
	return 0;
}
```

很早以前 A 的，补个题解。

---

## 作者：WLR__jr (赞：2)

# 思路:

### ~~物理模拟题~~,判断在到达终点的时候速度是否达到最大值,分情况讨论即可

~~下面上代码~~~~（逃~~



------------


```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
double ans[110000];
int main()
{
	double n,a,d;scanf("%lf%lf%lf",&n,&a,&d);
	for(int i=1;i<=n;i++)
	{
		double t,v;scanf("%lf%lf",&t,&v);
		if(v*v>=2*a*d)ans[i]=sqrt(2*d/a)+t;
		else
		{
			double tmp=v*v/2/a;
			double x=tmp;
			tmp=d-tmp;
			ans[i]=tmp/v+sqrt(2*x/a)+t;
		}
	}
	for(int i=2;i<=n;i++)ans[i]=max(ans[i],ans[i-1]);
	for(int i=1;i<=n;i++)printf("%.7f\n",ans[i]);
	return 0;
}
```

---

