# Follow Traffic Rules

## 题目描述

Everybody knows that the capital of Berland is connected to Bercouver (the Olympic capital) by a direct road. To improve the road's traffic capacity, there was placed just one traffic sign, limiting the maximum speed. Traffic signs in Berland are a bit peculiar, because they limit the speed only at that point on the road where they are placed. Right after passing the sign it is allowed to drive at any speed.

It is known that the car of an average Berland citizen has the acceleration (deceleration) speed of $ a $ km/h $ ^{2} $ , and has maximum speed of $ v $ km/h. The road has the length of $ l $ km, and the speed sign, limiting the speed to $ w $ km/h, is placed $ d $ km ( $ 1<=d<l $ ) away from the capital of Berland. The car has a zero speed at the beginning of the journey. Find the minimum time that an average Berland citizen will need to get from the capital to Bercouver, if he drives at the optimal speed.

The car can enter Bercouver at any speed.



## 样例 #1

### 输入

```
1 1
2 1 3
```

### 输出

```
2.500000000000
```

## 样例 #2

### 输入

```
5 70
200 170 40
```

### 输出

```
8.965874696353
```

# 题解

## 作者：Ajwallet (赞：9)

[更好的阅读体验](https://blog.csdn.net/xuxiayang/article/details/89811207)

#### $Description$
给定一条长度为$l$的道路，现在你从原点出发向$l$这个点行驶，你的加速度为$a$，$d$这个点的限速为$w$，你车辆的最高速度为$v$，求行驶到$l$点的最短时间

数据范围：不爆$double$
***
#### $Solution$
一道物理题

引用一下之前大佬的公式：

匀速运动时：$v=\frac s t$

匀变速时：$v=v_0+at$

位移公式：$x=v_0t+\frac {at^2}2$

位移速度关系式：$v^2-v_0^2=2ax$
***
第四条证明：

由第三条$x=v_0t+\frac{at^2}2$

两边同时乘$2a$得到

$2v_0at+a^2t^2=2ax$

分配率

$at(2v_0+at)=2ax$

由第二条

$at(v+v_0)=2ax$

再由第二条移项得到

$(v-v_0)(v+v_0)=2ax$

平方差

$v^2-v_0^2=2ax$

简单吧。。。

***
 
设函数$f(v_0,v,a,l)$表示初始速度为$v1$，限速$v2$，加速度$a$，通过长度为$l$的路程的时间

设位移距离$s=\frac{v^2-v_0^2}{2a}$

如果$s\geq l$，那么直接跑即可，得到方程$\frac 1 2at^2+v_0t-l=0$，用公式法解得$t=\frac{-v_0+\sqrt{v_0^2+2al}}a$

否则前面做加速，后面做匀速

得到$t=\frac {v-v_0}a+\frac{l-s}{v}$，即加速的时间和通过剩余路程的时间

***

主程序部分

`加红的字`表示前面那个变量的名称

设$s$`特判`$=\frac{w^2}{2a}$，表示加速到$w$行驶的距离

当$w\geq v\ or\ s$`特判`$\geq d$时，即连最高时速都没有限速那么高或者一直加速$w$时已经过了$d$了，这时限不限速就不重要了，直接一直加速到$v$开过去即可，$ans=f(0,v,a,l)$

当$w< v$时，设$t_1$表示$[0\sim d]$的时间，$t_2$表示$[d\sim l]$的时间，显然$t_2=f(w,v,a,l-d)$

现在我们的主要任务是求$t_1$，我们可以模仿人的开车过程

当没有摄像头时，你一直加速到最高时速，发现前方有摄像头，你又慢慢减速到限速，我们此时就需要求出这个你开始减速的时间

又是一个一元二次方程啊。。。$t$`加速阶段`$=\sqrt{\frac{2ad+w^2}{2a^2}}$
若$at$`加速阶段`$\leq v$，那么我们来不及加速到$w$，只能加速到某一速度，然后减速到$v$，此时$t$`加速`$=t$`减速到0`

得到$t_1=t$`加速阶段`$+t$`减速到w`$=t$`加速阶段`$+(t$`减速到0`$-t$`加速到w`$=2t$`加速阶段`$t$`加速到w`$2t$`加速阶段`$-\frac w a$

否则若$at$`加速阶段`$>v$，则说明我们时间足够充裕，可以先加速到$w$，然后匀速行驶一段时间，再减速到$v$，此时$t_1=\frac v a+\frac{v-w}{a}+(d-$(加速路程+减速路程))$/v$，分别表示加速的时间，减速的时间和匀速行驶的时间

答案即为$t_1+t_2$

说白了就是一道物理题呀QwQ

时间复杂度？$O(1)$
***
#### $Code$
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
double a,v,l,d,w,t1,t2,ans;
inline double F(double x){return x*x;}
inline double f(double v0,double v,double a,double l) 
{
	double s=(v+v0)*(v-v0)/2/a;
	if(s>=l) return (-v0+sqrt(F(v0)+2*a*l))/a;
	else return (v-v0)/a+(l-s)/v;
}
signed main()
{
	scanf("%lf%lf%lf%lf%lf",&a,&v,&l,&d,&w);
	double stp=F(w)/2/a;
	if(w>=v||stp>=d) ans=f(0,v,a,l);
	else
	{
		t2=f(w,v,a,l-d);
		double tjs=sqrt((2*a*d+F(w))/2/a/a);
		if(tjs*a<=v) t1=2*tjs-w/a;
		else
		{
			double sf=F(v)/2/a;
			double sl=(v+w)*(v-w)/2/a;
			t1=v/a+(v-w)/a+(d-sf-sl)/v;
		}
		ans=t1+t2;
	}
	printf("%.12f",ans);
}
```

---

## 作者：XL4453 (赞：3)

### 解题思路：

高一物理题。考虑将路程分成两段处理。

---

前半段有速度限制。

如果一直加速都无法超过速度限制，那么直接一直加速即可。

这种情况下：$\dfrac{at^2}{2}=d$ 得到 $t=\sqrt{\dfrac{2d}{a}}$，乘上加速度得到：$v=\sqrt{2ad}$ 并要求 $v<w$。

---
否则可以考虑用方程求解，设最大速度为 $v$，则前半段的路程有等式：$2ax_1=v^2-0^2$ 得到：$x_1=\dfrac{v^2}{2a}$，后半段则有：$x_2=\dfrac{v^2-w^2}{2a}$，两者之和为：$\dfrac{2v^2-w^2}{2a}$，恰好等于 $d$。求得 $v=\sqrt{\dfrac{2ad+w^2}{2}}$。

这一段的时间为：$t=\dfrac{v}{a}+\dfrac{v-w}{a}=\dfrac{2v-w}{a}$。

---

后半段则比较简单，直接加速即可，若设最终的速度为 $v_1$，有：$2a(l-d)=v^2-v_1^2$ ，得到：$v_1=\sqrt{v^2-2a(l-d)}$，算出时间：$t=\dfrac{v1-v}{a}$。

---
### 代码：


```cpp
#include<cstdio>
#include<cmath>
using namespace std;
double v,a,b,l,w,d,t,ans,v1,s,t1,v2;
int main(){
	scanf("%lf%lf%lf%lf%lf",&a,&v,&l,&d,&w);
	t=sqrt(2*d/a);
	if(a*t<=w){
		ans=t;
		v1=a*t;
		if(v1>=v){
			v1=v;
			t=v/a;
			s=d-t*t/2*a;
			t+=s/v;
		}
	}
	else{
		v1=sqrt(a*d+w*w/2);
		if(v1>v){
			v1=v;
			t=v/a;
			s=d-t*t/2*a;
			if(v>w){
				t1=(v-w)/a;
				s-=(v*v-w*w)/2/a;
				t+=t1+s/v;
				v1=w;
			}
			else{
				t+=s/v;
			}
		}
		else{
			t=(2*v1-w)/a;
			v1=w;
		}
	}
	v2=sqrt(v1*v1+2*a*(l-d));
	if(v2>=v){
		t1=(v-v1)/a;
		s=l-d-(v1*t1+t1*t1/2*a);
		t+=t1;
		t+=s/v;
	}
	else{
		t+=(v2-v1)/a;
	}
	printf("%.10lf\n",t);
	return 0;
}
```


---

## 作者：Tzs_yousa (赞：2)

本蒟蒻调了好久才调出来嘤嘤嘤，明明是个物理小水题，可是我写了这么久。
## 正题
其实就分类讨论多了一点，有高中物理知识基础（可以学一下的）就能写出来了。
首先是 $v$ 比 $w$ 小，那么直接算出来速度提升到 $v$ 时走的距离，再比较这个距离和 $l$ 之间的大小处理即可。
```cpp
if(v <= w)
	{
		double x1 = v * v / 2 / a;
		if(x1 <= l) printf("%.10lf", (v / a) + (l - x1) / v);
		else 
		{
			printf("%.10lf", sqrt(2 * l / a));
		}
	}
```
然后就是 $v$ 比 $w$ 大，这个分类就有点多了。
直接写在代码里看吧。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
double a, v, l, d, w;
signed main()
{
	scanf("%lf%lf%lf%lf%lf", &a, &v, &l, &d, &w);
	if(v <= w)
	{
		double x1 = v * v / 2 / a;
		if(x1 <= l) printf("%.10lf", (v / a) + (l - x1) / v);
		else 
		{
			printf("%.10lf", sqrt(2 * l / a));
		}
	}
	else
	{
		double x1 = w * w / 2 / a;//x1是一直加速到w所走的距离 
		if(x1 <= d)//当这个距离比d小，那么一定有更加优秀的方案，就是先加速到v0再减速到w 
		{
			double v0 = sqrt(a * d + w * w / 2);
			if(v0 <= v)//如果中途的v0是比v小的，那就可以直接算了 
			{
				double x2 = w * (v - w) / a + (v - w) * (v - w) / 2 / a;//x2是在限速牌后面加速到v走的距离 
				if(x2 <= l - d) printf("%.10lf", (v0 / a) + (v0 - w) / a + (v - w) / a + (l - d - x2) / v);
				else 
				{
					double v1 = sqrt(2 * a * (l - d) + w * w);
					printf("%.10lf ", (v0 / a) + (v0 - w) / a + (v1 - w) / a);
				}//这两就很显然了 
			}
			else//否则就是直接加速到v然后匀速一段然后再减速到w 
			{
				double x2 = w * (v - w) / a + (v - w) * (v - w) / 2 / a;
				double x3 = v * v / 2 / a + w * (v - w) / a + (v - w) * (v - w) / a / 2;
				if(x2 <= l - d) printf("%.10lf", (v / a) + (v - w) / a + (d - x3) / v + (v - w) / a + (l - d - x2) / v);
				else 
				{
					double v1 = sqrt(2 * a * (l - d) + w * w);
					printf("%.10lf ", (v / a) + (v - w) / a + (d - x3) / v + (v1 - w) / a);
				}
			}
		}//如果x1比d大的话就直接算就可以了 
		else
		{
			double x2 = a * (v / a) * (v / a) / 2;
			if(x2 <= l) printf("%.10lf ", (v / a) + (l - x2) / v);
			else printf("%.10lf ", sqrt(2 * l / a));
		}
	}
	return 0;
}
```
差不多就是这样了，完结撒花！

---

## 作者：小闸蟹 (赞：2)

```cpp
// 这一题就是纯正的物理题，搞不懂和编程有什么关系
// 不过它的分类讨论也有一点点的繁琐
// 但是比起高三的时候做的运动学问题已经好很多了
// 要注意这一题有一个坑点：
// 就是不是[0, d]的最大速度为w，而是只要通过d这一点时
// 速度为w即可，为了这个点我还WA了一发
// 详见代码里面的注释
#include <iostream>
#include <cmath>

// 返回以初速为v1，最大速率为v2，加速度为a，通过l的最短时间
double Move(double v1, double v2, double a, double l)
{
    double t = 0.0;
    double s = (v2 * v2 - v1 * v1) / 2 / a;
    if (s >= l)
    {
        t = (-v1 + std::sqrt(v1 * v1 + 2 * a * l)) / a;
    }
    else
    {
        double t1 = (v2 - v1) / a;
        double t2 = (l - (v2 * v2 - v1 * v1) / 2 / a) / v2;
        t = t1 + t2;
    }

    return t;
}

int main()
{
    double a, v, l, d, w, t;
    std::cin >> a >> v >> l >> d >> w;

    double s = v * v / 2 / a;
    if (w >= v) // 如果最大速率还达不到限速，那就一直开过去就好了
    {
        t = Move(0, v, a, l);
    }
    else
    {
        double s1 = w * w / 2 / a;
        if (s1 >= d)    // 如果一直加速到d还没达到限速w
        {               // 那就一直开过去没事的
            t = Move(0, v, a, l);
        }
        else   // 这里的讨论就需要自己动手画个图，解一下简单的方程了
        {
            double t11 = std::sqrt((2 * a * d + w * w) / 2 / a / a);

            double t1;  // [0, d]的总时间
            if (t11 * a <= v)   // 加速到某一速度然后减速到w通过d
            {
                t1 = 2 * t11 - w / a;
            }
            else   // 先加速到v，然后匀速行驶一段，最后减速到w通过d
            {
                double s11 = v * v / 2 / a; // 加速阶段走的路程
                double s12 = (v * v - w * w) / 2 / a;   // 减速阶段走的路程
                t1 = v / a + (v - w) / a + (d - s11 - s12) / v;
            }
            double t2 = Move(w, v, a, l - d);   // 通过d后一直到l的时间
            t = t1 + t2;
        }
    }

    std::printf("%.12f\n", t);

    return 0;
}
```

---

## 作者：Loner_Knowledge (赞：2)

这是一道物理题
---

题目给出了最大速度和在`d`点的限速，求所花费最小时间，只需要分类讨论并使用适合的公式及其变式即可。

## 主要公式

速度公式$v=\frac{s}{t}$(匀速)

速度公式$v=v_0+at$(匀变速)

位移公式$x=v_0t+\frac{at^2}{2}$(匀变速)

位移速度关系式$v^2-v_0^2=2ax$(匀变速)

```cpp
#include<cstdio>
#include<cmath>
int main() {
	double a,v,l,d,w,t,t1,t2,t3,x1,x2,x3;
    				//t为答案
                    //1代表初速度为0，末速度为v的匀变速运动，t1是其所花时间，x1是其位移大小
                    //2代表初速度为0，末速度为w的匀变速运动，t2是其所花时间，x2是其位移大小
                    //3代表初速度为w，末速度为v的匀变速运动，t3是其所花时间，x3是其位移大小
                    //以下皆用数字表示是那种运动
	scanf("%lf%lf%lf%lf%lf",&a,&v,&l,&d,&w);
	t1=v/a;
	x1=a*t1*t1/2;	//求出t1与x1
	if(w<v) {		//如果w<v，代表需要考虑d点限速，反之则不需要
		t2=w/a;
		x2=a*t2*t2/2;	//求出t2与x2
		if(x2<d) {		//如果x2<d，代表需要考虑d点限速，反之相当于w>=v的情况
			t3=(v-w)/a;
			x3=w*t3+a*t3*t3/2;			//求出t3与x3
            							//由于只有d点限速，所以x2至d这段需要先加速到v2（v2大于w，不超过v），之后有一段可能的匀速运动，再减速直到刚好减速到w时到达d点
			if(x1+x3<d)					//考虑d点前的部分，如果x1+x3<d，代表需要考虑在1（相当于2+3）后的匀速运动，反之则不需要考虑匀速运动
				t=t1+t3+(d-x1-x3)/v;
			else
				t=t2+2*(sqrt(a*(d-x2)+w*w)-w)/a;
			if(x3<l-d)					//考虑d点后的部分，如果x3<l-d，代表需要考虑在3后的匀速运动，反之则不需要考虑匀速运动
				t+=t3+(l-d-x3)/v;
			else
				t+=(sqrt(2*a*(l-d)+w*w)-w)/a;
		}
		else
			goto I;
	}
	else {
		I:
		if(x1<l)			//如果x1<l，代表需要考虑在1后的匀速运动，反之则不需要考虑匀速运动
			t=t1+(l-x1)/v;
		else
			t=sqrt(2*l/a);
	}
	printf("%.12lf",t);
	return 0;
}
```

---


---

## 作者：封禁用户 (赞：0)

## 思路

一道物理题。如果有没学过匀加速运动的可以看一下公式，其中 $a$ 表示加速度。

$t$ 秒末速度公式 $v_{t}=v_{0}+at$。

位移公式 $x=v_{0}t+\frac{1}{2}at^{2}$。

速方差公式 $v_{t}^{2}-v_{0}^{2}=2ax$。

然后模拟开车的过程：

在限速牌前面要一直做初速度为 0 的匀加速运动直到达到限速。此时分两类讨论：

1.当车速未达到限速即 $v<w$ 时 $d=\frac{1}{2}at^{2}$，$v=at=a\sqrt{\frac{2d}{a}}=\sqrt{2ad}$。

2.当车速达到限速且以限速行驶了一段时间时，可用方程求解。$x_{sum}=\frac{2v^{2}-w^{2}}{2a}$，从而 $v_{1}=\sqrt{\frac{2ad+w^{2}}{2a}}$，$v_{2}=\sqrt{v^{2}-2a\left(l-d\right)}$
所以 $t_{sum}=\frac{v_{1}+v_{2}-w}{a}$。

最后把数据带进去就好了。

---

## 作者：_JF_ (赞：0)

[CF5D Follow Traffic Rules ](https://www.luogu.com.cn/problem/CF5D)

~~被物理击杀了。~~

首先你需要知道三个公式：

$$v_t=v_0+a_t$$
$$s=v_0t+\frac{1}{2}at^2$$
$$v_t^2-v_0^2=2as$$

首先 $v\le w$ 是简单的，直接加速从头到尾，如果到 $v$ 就变成匀速，两段统计即可。

然后看看 $v >w$。

然后我们不妨分成两段看。就是监测点前和监测点后。

关于监测点后，这部分是简单的。

假设在监测点时速度为 $x$，我们只用看 $x$ 加速到 $v$ 所需要的距离是不是超过了 $l-d$，如果超过，那么无脑加速走即可。否则就是加速到 $v$ 然后匀速直线运动。

关于检测点前，需要再次分类。

如果我从开始加速到检测点，速度还 $<w$，那直接无脑加速走即可。

如果到监测点时候速度已经 $>x$ 了，这时候还有两种情况：

- 我可以加速到 $v$，然后按着 $v$ 速度走一段时间，然后从 $v$ 下降成 $w$。
- 时间不够，不允许加速到 $v$ 后立刻减速，那么就加速到某个临界状态，然后直接减速。

解释一下第二种情况为什么不会按着某个值走一段时间再降速，其实你拍到 $v-t$ 图像看，面积就是位移，如果你按照“某个值走一段时间”，是一个矩形，不优：

![](https://cdn.luogu.com.cn/upload/image_hosting/wbafsjfn.png)

这其实是 whk 知识/xk，对于这种情况不好搞，我只会二分它。。。

然后就是一堆细节的写了。


```cpp
#include<bits/stdc++.h>
using namespace std;
double a,v,l,d,w,eps=1e-8;
double Slove(double len){
	double l=0,r=10000000.0;
	while((r-l)>eps){
		double t1=(l+r)/2;
		if((a*t1*t1/2+(a*t1+w)/2*((a*t1-w)/a)-len)>eps)	r=t1;
		else	l=t1;
	}
	return l;
}
int main(){
	cin>>a>>v>>l>>d>>w;
	if(v<=w){
		double T1=v/a,S1=a*T1*T1/2;
//		cout<<l-S1<<endl;
		if(l-S1>eps)
			T1+=(l-S1)/v;
		else{
			double pre1=sqrtl(2*a*l);
			T1=pre1/a;
		}
		cout<<fixed<<setprecision(7)<<T1<<endl;
		return 0;
	}
	double Nowsp,T=0,now=sqrtl(2*a*d);
	if(now-w<eps){
		Nowsp=now,T=(now)/a;
	} // can't get w  
	else{
		double Now=v*v/(2*a)+(v*v-w*w)/(2*a);
		
		if(d-Now<eps){
			double t1=Slove(d);
			T=t1+(a*t1-w)/a;
		}// F 1 
		else	T=(d-Now)/v+(v/a)+(v-w)/a;
		Nowsp=w;
	}
	double S1=(v*v-Nowsp*Nowsp)/(2*a);
	if(S1-(l-d)>eps){
		double pre1=sqrtl(2*a*(l-d)+Nowsp*Nowsp);
		T+=(pre1-Nowsp)/a;
	}// can go  
	else{
		double T1=(v-Nowsp)/a,S1=Nowsp*T1+a*T1*T1/2;
		double dis=l-d-S1;
		T+=(dis/v)+T1;
	}
	cout<<fixed<<setprecision(7)<<T<<endl;
	return 0;
}
/*
4 120
5112 3000 130
*/
```

---

## 作者：Walter_Fang (赞：0)

### 前置知识

远古 CF 物理题，搞懂公式后并不难。

需要知道的公式：

- $v=s\div t$
- $v=v_0+at$
- $t=v_0t+(at)^2\div2$
- $v^2-(v_0)^2=2ax$
### 思路/解析

将全程分为两段，并设 $v$ 为最大合法时速，得：

$\begin{cases}x_1=v^2\div(2a)\\x_2=(v^2-w^2)\div(2a)\\t=(2v-w)\div a\end{cases}$。

前半段限速，后半段不限速，因此可以一直加速。

代入式子得 $v^2=2a(x_1+x_2)$，且 $v<w$。

后半段加速，得 $t=(v_1-v)\div a$。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
double a,v,l,d,w,t,t1,t2,t3,x1,x2,x3;
int main(){
	cin>>a>>v>>l>>d>>w;
	t1=v/a;
	x1=a*t1*t1/2;
	if(w<v){
		t2=w/a;
		x2=a*t2*t2/2;
		if(x2<d){
			t3=(v-w)/a;
			x3=w*t3+a*t3*t3/2;
			if(x1+x3<d)t=t1+t3+(d-x1-x3)/v;
			else t=t2+2*(sqrt(a*(d-x2)+w*w)-w)/a;
			if(x3<l-d)t+=t3+(l-d-x3)/v;
			else t+=(sqrt(2*a*(l-d)+w*w)-w)/a;
		}
		else if(x1<l)t=t1+(l-x1)/v;
		else t=sqrt(2*l/a);
	}
	else if(x1<l)t=t1+(l-x1)/v;
	else t=sqrt(2*l/a);
	printf("%.5lf",t);
}
```

---

## 作者：ncwzdlsd (赞：0)

~~死去的高中物理突然开始攻击我~~

这题纯纯物理题QwQ，但是和物理题一样要注意分情况讨论。

先求出速度到达 $w$ 的时间，然后利用 $v=a\times t_1$ 计算出该时刻的速度；
- 如果 $v\leq w$，说明不会超速，所以就让车一直加速到最大值就好啦，记得判断一下车的位移是否够路的总长，如果没有走完，则继续匀速行驶。

- 如果超速：
1. 在 $0\sim d$ 的距离，先加速到最大值，然后减速到 $w$，在限速点后继续加速。注意，$d$ 之前并不是一直加减速，首先要算出加速需要的时间和减速需要的时间，还可能有一段时间是保持最大速度匀速直线运动的，一定要注意这一点分类讨论，否则小心WA。

2. 通过B之后，就让车一直加速到最大速度后匀速或者一直加速就好啦。

具体的实现套公式就好了，其他题解写得很详细就不再赘述了。

代码就不放了，像这样的分情况讨论题自己码才能有收获啊QwQ

---

## 作者：Supor__Shoep (赞：0)

要不是学了一些高级的物理知识，我可能根本做不来这个题。

所以为什么把物理题放在编程里面？太离谱了。

首先，我们要慢慢分情况考虑，对于不会超速的情况，我们可以一直加速达到最优解，即：
```
w>=v||w*w/(2*a)>d
```
另一种情况就是超速的情况，也是比较难处理的情况。

我们需要单独讨论限速段，同时控制好加速的时间和距离，接着计算出限速段其余的路程进行分支讨论，如果此时没有加速到最高速，就给答案统计：
```
double tv=sqrt(2*a*d+w*w);
ans+=2*(tv-w)/a;
```
否则统计：
```
ans+=2*(v-w)/a+2*(d-tx)/v;
```
这里要注意加速加满之后的运动情况，是匀速运动。

到了限速段之后，我们再进行类似的操作，如果还是没有达到最高速，就统计答案：
```
double tv=sqrt(2*a*l+w*w);
ans+=(tv-w)/a;
```
否则统计：
```
ans+=(v-w)/a+(l-tx)/v;
```
这里同样是加速加满后匀速运动。

最后保留小数就可以了。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
double slove(double a,double b,double c)
{
    return (-b+sqrt(b*b-4*a*c))/(2*a);
}
int main()
{
    double a,v,len,d,w,ans=0;
    scanf("%lf%lf%lf%lf%lf",&a,&v,&len,&d,&w);
    if(w>=v||w*w/(2*a)>d)
    {
        double x=(v*v)/(2*a);
        if(x>=len)
        {
            ans+=sqrt(2*a*len)/a;
        }
        else
        {
            ans+=(len-x)/v+v/a;
        }
    }
    else
    {
        len-=d;
        double tx=w*w/(2*a);
        double t=w/a;
        d-=tx;
        ans+=t;d/=2;
        tx=(v*v-w*w)/(2*a);
        if(tx>d)
        {
            double tv=sqrt(2*a*d+w*w);
            ans+=2*(tv-w)/a;
        }
        else
        {
            ans+=2*(v-w)/a+2*(d-tx)/v;
        }
        tx=(v*v-w*w)/(2*a);
        if(tx>len)
        {
            double tv=sqrt(2*a*len+w*w);
            ans+=(tv-w)/a;
        }
        else
        {
            ans+=(v-w)/a+(len-tx)/v;
        }
    }
    printf("%.12lf\n",ans);
    return 0;
}
```

---

