# Crossed Ladders

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1507

[PDF](https://uva.onlinejudge.org/external/105/p10566.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10566/04bd930627e82cc986e14b41bdaa0b69d1b37635.png)

## 样例 #1

### 输入

```
30 40 10
12.619429 8.163332 3
10 10 3
10 10 1```

### 输出

```
26.033
7.000
8.000
9.798```

# 题解

## 作者：Nepenthe (赞：3)

![](https://cdn.luogu.com.cn/upload/pic/24779.png
)

由相似三角形的知识,我们用两种方法分别表示出图中Lx,就可以得出一个等式关系:$$\frac{1}{b}+\frac{1}{a}=\frac{1}{c}       ⋯⋯(1)$$
又有等式$$a=\sqrt{x^2-t^2},b=\sqrt{y^2-t^2}$$
把这两式代入(1)式可以得到$$\frac{1}{\sqrt{x^2-t^2}}+\frac{1}{\sqrt{y^2-t^2}}=\frac{1}{c}$$
我们并不需要把它解出来
可以发现左边的式子关于t是单调的,所以我们二分t即可

**Code**
```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define siz 
#define minn(a,b) (a<b?a:b)
using namespace std;
double x, y, c;
double work(double t) {
	return 1 / sqrt(x * x - t * t) + 1 / sqrt(y * y - t * t);
}
int main() {

	while( ~scanf("%lf%lf%lf",&x,&y,&c) ) {
		double l = 0, r = minn(x,y), mid;
		while(r - l > 1e-5) {
			mid = l + (r - l) / 2; 
			if( work(mid) > (1/c) ) r=mid;
			else l=mid;
		}
		printf("%.3lf\n",mid);
	}
	return 0;
}
```
**Tips**
- ```mid = l + (r - l) / 2;``` 之所以这样求mid,是怕有恶心数据让(l+r)越界
- ```(r-l)>>1``` 是错误的! double是不能使用右移运算的

---

## 作者：追梦_Chen (赞：3)

看到这道题我想起了我的初中班主任---欧阳红老师，不禁内牛满面......
------------
咳咳，这是一道比较简单的几何体，根据相似三角形的知识，我们可以设所求之边为d，然后我们就可以推出一个华丽丽的表达式了233
![](https://s1.ax1x.com/2018/07/20/P8e5vQ.png)
# 表达式如下
(d1/d)+(d2/d)=1---------------(1)
# 由方程（1）可变形得到
```
c*sqrt(x*x-d*d)+c*sqrt(y*y-d*d)==
sqrt(x*x-d*d)*sqrt(y*y-d*d)
```
# 利用二分查找！！！代码如下：
```
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;   
double x,y,c;
double d;
bool calc(double w){
	double a,b;
	a=sqrt(x*x-w*w);  //这是我们的公式
	b=sqrt(y*y-w*w);   
	if(a*b>=c*(a+b))
		return false;
	else
		return true;
}
int main(){
	while((scanf("%lf%lf%lf",&x,&y,&c))!=EOF){
		double l=0,r=min(x,y);
		for(int i=1;i<100;i++){     //二分查找
			double mid=(l+r)/2;
			if(calc(mid))	r=mid;
			else l=mid;
		}
		printf("%.3f\n",l);	  
	}
	return 0;
}

```

---

## 作者：d3NtMDAw (赞：1)

一道不错的二分题   
基本上数学想到了，就没什么难度  
简单的设两未知直角边分别为a，b；    
有数学知识容易得到1/a+1/b=1/c   
在二分的mid单调增大时   
易知1/a单调增（即c单调减），   
符合二分答案的单调性

-------我是分割线-----


```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
double a,b,c;
double f(double x)
{
    double k1=sqrt(a*a-x*x);
    double k2=sqrt(b*b-x*x);
    double k3=(k1*k2)/(k1+k2);
    return k3；
}  
int main()
{
    double l,r,mid,k; 
    while(cin>>a>>b>>c)//scanf("%lf%lf%lf",&a,&b,&c)
    {
     l=0;
     r=min(a,b);
     while(r-l>0.000001)
     {
     k=f(l);
     if(abs(l-c)<0.000001)
     {
       printf("%.3lf\n",l);
       break;	
     }
     mid=(l+r)/2;
     k=f(mid);
     if(k-c>0.000001)
     {
       l=mid;	
     }
     else
       r=mid;
     }
     printf("%.3lf\n",r);	
    }
    return 0;
}


---

## 作者：HUTEHE (赞：0)

## 题目大意

给出两把梯子的高长度 $x$ 和 $y$，以及交叉点 $c$ 的高度，求道路的宽（即两梯子底端之间的距离）。

## 解题思路

### 数学 + 二分

可以利用梯子的长度和梯子与地面的夹角来求得道路的宽。

设梯子 $x$ 与 $y$ 与地面的夹角分别为 $\alpha$ 和 $\beta$，道路的宽设为 $w$，梯子 $x$ 的底端与交叉点在地面的水平投影距离为 $h$。

![](https://cdn.luogu.com.cn/upload/image_hosting/yqzxgw45.png)

则有 $\sin(\alpha)=\frac{c}{x}$，$\sin(\beta)=\frac{c}{y}$，$\cos(\alpha)=\frac{w+h}{x}$，$\cos(\beta)=\frac{w}{y}$。

解出 $h$ 为：
$$
h=y\times\cos(\beta)=y\times\sqrt{1-\sin^2(\beta)}=y\times\sqrt{1-\frac{c^2}{y^2}}=y\times\frac{\sqrt{y^2-c^2}}{y}=\sqrt{y^2-c^2}
$$
并表示道路宽 $w$ 为：
$$
w=x\times\cos(\alpha)-h=x\times\sqrt{1-\sin^2(\alpha)}-h=x\times\sqrt{1-\frac{c^2}{x^2}}-h=x\times\frac{\sqrt{x^2-c^2}}{x}-h=\sqrt{x^2-c^2}-h
$$
将 $h=\sqrt{y^2-c^2}$ 代入，得：
$$
w=\sqrt{x^2-c^2}-\sqrt{y^2-c^2}
$$
不难看出，该解析式具有单调递减性，又由于数据为实数，则可以使用实数二分，不断逼近所需精度。

## 代码

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define int long long
#define endl "\n" 
using namespace __gnu_cxx;
using namespace __gnu_pbds;
using namespace std;
double x,y,c;
inline bool check(long double m)//检查函数
{
	long double h1=sqrt(x*x-m*m);
	long double h2=sqrt(y*y-m*m);
	return (h1*h2)<(h1*c+h2*c);//返回精度偏小（true）还是偏大（false）。
}
signed main() 
{
    while(cin>>x>>y>>c)
    {
    	long double l=0,r=min(x,y);//左右端点
    	long double m;
    	while(r-l>=1e-6)//实数二分
    	{
    		m=(l+r)/2;//注意 double 类型不能用右移运算
    		if(check(m))r=m;
    		else l=m;
    	}
    	cout<<fixed<<setprecision(3)<<l<<endl;
    }
    return 0;
}
```

---

## 作者：0x00AC3375 (赞：0)

## 1. 大致题意

- 两栋楼挨得比较近，两侧分别斜靠着长度为 $x$ 和 $y$ 的两个梯子，已知两个梯子交点到地面的垂直距离为 $c$，求两栋楼之间的距离 $t$。
- 输入有多组数据。

## 2. 分析
解决本题需要一定的几何知识。

设左边倚靠点到地面的高度为 $h_1$，右边为 $h_2$，要求的距离为 $t$，根据勾股定理有
$$t^2+h_1^2=x^2$$
$$t^2+h_2^2=y^2$$
若过焦点作地面的垂线，根据相似三角形的几何性质，有几何关系
$$\dfrac{1}{c}=\dfrac{1}{h_1}+\dfrac{1}{h_2}$$
联立以上三个式子，可以得到
$$\dfrac{c}{\sqrt{x^2-t^2}}+\dfrac{c}{\sqrt{y^2-t^2}}-1=0$$
根据上式求出 $t$ 保留三位小数的值即可，其中 $t$ 的取值范围为 $[0,\min(x,y))$，这里是**左闭右开区间**。

容易看出，在指定的范围内，函数
$$f(t)=\dfrac{c}{\sqrt{x^2-t^2}}+\dfrac{c}{\sqrt{y^2-t^2}}-1$$
是一个随着 $t$ 单调递增的函数，因此可以考虑使用二分求解。
考虑到分母不能为零，因此初始时可以设左端值 $l=0$，右端值 $r=\min(x,y)-10^{-6}$。不断进行二分直到达到符合题意的精度即可。

## 3. 代码
```cpp
#include<cstdio>
#include<cstdlib>
#include<cmath>
double c,x,y,eps=1e-8;
double Min(double a, double b)
{
	return a<b?a:b;
}
double f(double t)
{
	return 1.*c/sqrt(x*x-t*t)+1.*c/sqrt(y*y-t*t)-1.;
}
void kernel(void)
{
	if(scanf("%lf%lf%lf",&x,&y,&c)==EOF) exit(0);
	double l=0.,r=Min(x,y)-1e-6,mid;
	while(r-l>=eps)
	{
		mid=(l+r)/2.;
		if(f(mid)<0) l=mid;
		else r=mid;
	}
	printf("%.3lf\n",l);
}
int main()
{
	while(1) kernel();
} 
```

## 4. 拓展
通过上面的分析可知，本题可以转化为一个解方程问题并且这个方程对应的函数 $f(t)$ 是一个**可导函数**。因此理论上本题也可以使用牛顿法来求解。

牛顿法通过迭代公式 $t_{n+1}=t_n-\dfrac{f(t_n)}{f'(t_n)}$ 不断递推求出满足精度要求的值，但是在本题中使用牛顿法会出现 [Wrong Answer](https://www.luogu.com.cn/record/122462689)，原因和**函数的定义域**有关。

牛顿法迭代需要用户自行定义一个初始值 $t_0$。不管将方程化成什么形式，表达式中总是会含有 $\sqrt{x^2-t^2}$ 和 $\sqrt{y^2-t^2}$。在 $t$ 接近 $\min(x,y)$ 的时候，函数 $f(t)$ 的值非常大。如果某一次迭代的结果落在了定义域外，下一次迭代就可能无法进行。就本题而言，如果**使用牛顿法，很可能需要针对不同的三元组 $(x,y,c)$ 选择不同的初始值**，这无疑是小题大做。

---

## 作者：Huhu12346 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA10566)

# 题意：
给两把梯子的长度 $x$，$y$ 和他们交点的高度 $c$，求两梯子底部之间的距离。

# 思路：

1. 建立平面直角坐标系：

```cpp
double Rectangular_Plane_Coordinate_System(double t)
{
	double k1 = sqrt(y * y - t * t) / t, k2 = -sqrt(x * x - t * t) / t;
	return k1 * k2 * t / (k2 - k1);
}
```
2. 设两房之间的宽度为 $t$，两条直线方程为 

$ \left\{
\begin{aligned}
y=k_1x \\ 
y={k_2}(x-t)\\
 t>0 \\
\end{aligned}
\right.
$
（$k_1=\dfrac {\sqrt{y^2-t^2}}t,k_2=\dfrac {-\sqrt{x^2-t^2}}t$）

最后列一个二元一次方程组求解就可以了。
```cpp
int main()
{
	while (~scanf("%lf%lf%lf", &x, &y, &c))
	{
		double l = 0, r = min(x, y), t;
		while (r - l > cnt)
		{
			t = (l + r) / 2;
			if (Rectangular_Plane_Coordinate_System(t) < c)
				r = t;
			else
				l = t;
		}
		printf("%.3lf\n", t);
	}
	return 0;
}
```
最后附上完整代码：

```cpp
#include <cstring>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const double cnt = 1e-5;

double x, y, c;

double Rectangular_Plane_Coordinate_System(double t)
{
	double k1 = sqrt(y * y - t * t) / t, k2 = -sqrt(x * x - t * t) / t;
	return k1 * k2 * t / (k2 - k1);
}

int main()
{
	while (~scanf("%lf%lf%lf", &x, &y, &c))
	{
		double l = 0, r = min(x, y), t;
		while (r - l > cnt)
		{
			t = (l + r) / 2;
			if (Rectangular_Plane_Coordinate_System(t) < c)
				r = t;
			else
				l = t;
		}
		printf("%.3lf\n", t);
	}
	return 0;
}
```



---

## 作者：Graphcity (赞：0)

**题目简述**

就是有一条街道和两栋房子，房子和街道垂直。可以参照 PDF 里的图，有两架梯子，长度分别为 $x$ 和 $y$ ，架在两栋房子上，它们的交点距离地面长度是 $c$ , 求街道长度。

**思路**

如果街道长度越窄，那么两架梯子的交点距离地面肯定越高，这时就可以想到 **二分答案** 二分长度了。

二分长度（ 假设当前长度是 $l$ ）后，我们还需要求出以 $l$ 为长度时，两架梯子的交点与地面的距离。先用勾股定理求出两架梯子的倾斜程度（ 类似于斜率 ），设为 $k_1$ 和 $k_2$ ：

$$
\begin{matrix}
k_1=\dfrac{\sqrt{x^2-l^2}}{l}\\\\
k_2=\dfrac{\sqrt{y^2-l^2}}{l}
\end{matrix}
$$

把两架梯子搬到坐标轴上，再设交点的横坐标为 $p$ , 那么

$$
\begin{matrix}
k_1 \cdot (l-p)=k_2 \cdot p \\\\
p(k_1+k_2)=k_1 \cdot l \\\\
p=\dfrac{k_1-l}{k_1+k_2}
\end{matrix}
$$

得到横坐标后，交点的纵坐标就是 $k_2 \cdot p$ 了。

**注意**

- 二分答案的时候不需要用 while，容易死循环。

- 判断大小的时候，注意精度问题。

- 这道题目有多组数据。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-8;//精度

inline int Check(double x,double y)//判断大小
{
    x=x-y;
    if(fabs(x)<=eps) return 0;
    if(x>0) return 1;
    else return 2;
}
inline double Get(double x,double y,double l)//获取交点的纵坐标
{
    double k1=sqrt(x*x-l*l)/l;
    double k2=sqrt(y*y-l*l)/l;
    double p=(k1*l)/(k1+k2);
    return p*k2;
}

int main()
{
    double x,y,c;
    while(cin>>x>>y>>c)
    {
        double l=eps,r=max(x,y);
        int flag=0;//标记是否已有答案
        for(register int i=1;i<=50;++i)//二分答案
        {
            double mid=(l+r)/2;
            double res=Get(x,y,mid);
            if(Check(res,c)==0)
            {
                printf("%.3lf\n",mid);
                flag=1;
                break;
            }
            else if(Check(res,c)==1) l=mid;
            else r=mid;
        }
        if(!flag)
            printf("%.3lf\n",l);
    }
    return 0;
}
```

---

## 作者：yoyiETO (赞：0)

在**我的博客**查看效果更好 [传送门](https://www.luogu.com.cn/blog/Rainbow-Ring/solution-uva10566)

![](https://cdn.luogu.com.cn/upload/image_hosting/o7qss8x2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

**题意简述**:在两栋楼之间有一条街道,如图所示放着两个长度分别为x,y的梯子,梯子的交点离地面c,求街道宽度。

由**勾股定理**可知a= $\sqrt{x^2-c^2}$,b= $\sqrt{y^2-c^2}$.

根据**相似三角形**,  $\frac{1}{a}$ + $\frac{1}{b}$ = $\frac{1}{c}$ .

 $\frac{1}{a}$ + $\frac{1}{b}$ = $\frac{1}{c}$ 等价于**ac+bc=ab**(check函数).
 
check:
```cpp
bool check(double c)
{
    double a,b;
    a=sqrt(x*x-c*c);
    b=sqrt(y*y-c*c);   
    retrun a*b<=a*c+b*c;
}
```
当a增大时, $\frac{1}{a}$ 变小, $\frac{1}{a}$ + $\frac{1}{b}$ 变小, $\frac{1}{c}$ 变小,c增大,具有单调性,考虑**二分答案**.

二分代码:

```cpp
for(int i=1;i<=50;i++)
{
    double mid=(l+r)/2;
    if(check(mid)) r=mid;
    else l=mid;
}
```

合并一下就能AC了！
```cpp
#include<bits/stdc++.h>
using namespace std;
double x,y,c;
bool check(double n)//注意！变量名不能重复！！ 
{
    double a,b;
    a=sqrt(x*x-n*n);
    b=sqrt(y*y-n*n);   
    if(a*b>=a*c+b*c)
    	return 0;
    else return 1;
}
int main()
{
	while(cin>>x>>y>>c)
	{
		double l=0,r=min(x,y);
		for(int i=1;i<=50;i++)//任性的二分... 
		{
    		double mid=(l+r)/2;
   	 	    if(check(mid)) r=mid;
    		else l=mid;
		}
		printf("%.3lf\n",l);
	}
	return 0;
}
```

---

