# Peter and Snow Blower

## 题目描述

Peter got a new snow blower as a New Year present. Of course, Peter decided to try it immediately. After reading the instructions he realized that it does not work like regular snow blowing machines. In order to make it work, you need to tie it to some point that it does not cover, and then switch it on. As a result it will go along a circle around this point and will remove all the snow from its path.

Formally, we assume that Peter's machine is a polygon on a plane. Then, after the machine is switched on, it will make a circle around the point to which Peter tied it (this point lies strictly outside the polygon). That is, each of the points lying within or on the border of the polygon will move along the circular trajectory, with the center of the circle at the point to which Peter tied his machine.

Peter decided to tie his car to point $ P $ and now he is wondering what is the area of ​​the region that will be cleared from snow. Help him.

## 说明/提示

In the first sample snow will be removed from that area:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF613A/d58837ea7895097f43b3c725628f9a11757bb6b3.png)

## 样例 #1

### 输入

```
3 0 0
0 1
-1 2
1 2
```

### 输出

```
12.566370614359172464
```

## 样例 #2

### 输入

```
4 1 -1
0 0
1 2
2 0
1 1
```

### 输出

```
21.991148575128551812
```

# 题解

## 作者：zztqwq (赞：3)

[Link](https://codeforces.com/problemset/problem/613/A)

令 $(x_0,y_0)$ 在图形中能到达的最远距离为 $a$，最近距离为 $b$，那么答案为 $(a^2-b^2)\pi$。可以看出，能够取到 $a$ 或 $b$ 的点，要么是题目中给出的点 $(x_i,y_i)$，要么是 $(x_0,y_0)$ 向给出的边 $(x_i,y_i)(x_j,y_j)$ 作垂所得的垂足。如果将 $(x_i,y_i),(x_j,y_j)$ 所在直线 和 垂足与 $(x_0,y_0)$ 所在直线 分别看作一次函数 $f(x)=kx+b$ 和 $g(x)=k'x+b'$，那么垂足坐标就是 $f(x)$ 与 $g(x)$ 图像的交点。$f(x)$ 解析式很容易求，$g(x)$ 则不是很容易，需要一个引理。

> 引理：若 $f(x)=kx+b$ 的图像与 $g(x)=k'x+b'$ 的图像垂直，那么 $k'=-\dfrac{1}{k}$。
>
> 证明：
>
> ![](https://s3.ax1x.com/2021/02/05/y8IVRs.png)
>
> $\tan(\alpha+\pi/2)=-\cot\alpha=-\dfrac{1}{\tan\alpha}$  
> $\because  k=\tan\alpha,k'=\tan(\alpha+\pi/2)$  
> $\therefore k'=-\dfrac{1}{k}$

然后就可以算出垂足坐标：

![](https://s3.ax1x.com/2021/02/05/y8IpsP.png)

注意，计算垂足坐标时有三种特殊情况：

1. $x_1=x_2$，此时直线 $AB$  不是一次函数，$D$ 的坐标为 $(x_1,y_0)$；
2. $y_1=y_2$，此时直线 $CD$ 不是一次函数，$D$ 的坐标为 $(x_0,y_1)$；
3. $D$ 在线段 $AB$ 延长线上，此时这个点不合法，需要跳过。

总的时间复杂度是 $\mathcal O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
//#define double long double
const double PI=3.14159265358979323846265433832795028841971;	
double X0,Y0;
pair<double,double> cz(double X1,double Y1,double X2,double Y2)
{
	if(X1==X2) return make_pair(X1,Y0);
	if(Y1==Y2) return make_pair(X0,Y1);
	double k=(Y2-Y1)/(X2-X1),k0=-(1/k);

	double b=Y1-k*X1,b0=Y0-k0*X0;
	return make_pair((b0-b)/(k-k0),(b0-b)/(k-k0)*k0+b0);
}
double dis(double X1,double Y1,double X2,double Y2)
{return (X1-X2)*(X1-X2) + (Y1-Y2)*(Y1-Y2);}
double x[100010],y[100010];
int main()
{
//	X0=-3;Y0=3;
//	printf("%Lf,%Lf",cz(-3,2,5,3).first,cz(-3,2,5,3).second);
//	cout<<cz(0,,4,2).first<<" "<<cz(0,2,4,2).second;
//cout<<acos(-1)<<endl; 
	int n;
	scanf("%d%lf%lf",&n,&X0,&Y0);
	for(int i=1;i<=n;i++) scanf("%lf%lf",&x[i],&y[i]);
	double Min=1e18,Max=0;
	for(int i=1;i<=n;i++)
	{
		Min=min(Min,dis(X0,Y0,x[i],y[i]));
		Max=max(Max,dis(X0,Y0,x[i],y[i]));
	}
	for(int i=1;i<=n;i++)
	{
		int pre=(i==1?n:i-1);
		pair<double,double> point=cz(x[pre],y[pre],x[i],y[i]);
		if(point.first<min(x[pre],x[i]) || point.first>max(x[pre],x[i])) continue;
		if(point.second<min(y[pre],y[i]) || point.second>max(y[pre],y[i])) continue;
		Min=min(Min,dis(X0,Y0,point.first,point.second));
		Max=max(Max,dis(X0,Y0,point.first,point.second)); 
	}
	printf("%.10lf",(Max-Min)*PI);
	return 0;
}
```


---

## 作者：zhenglier (赞：2)

这一题其实就是告诉你一个多边形，求该多边形绕给出的原点转一圈以后扫过的面积。

本蒟蒻开始理解错题目了，以为只用算每个点到原点的距离的最大值和最小值就行了，但最后第三个点就被卡了。

后来经某位不愿透露姓名的大佬说，需要算出每条线段（注意是线段，不是直线）到原点的距离，因为里面的圆形可能是由一条切线绕一圈形成的。

但小蒟蒻不会，就查了一下，发现其实比较简单，就判断一下这个点到这条线段的垂足是否在线段上，若不是，则输出该点到端点的距离，若是，则输出这条垂线的长度。（关于这个垂线的长度，我用了两种方法，有一种爆精度了，代码中的是可以过的。）

~~然后这道题就变成一道水题了。~~

再不会就看代码吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct point{
    double x,y;
}p[100010],o;//点的结构体
struct line{
    double k,b;
};//线的结构体，这题没有用到
inline double dis(point a,point b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}//计算两个点的距离的平方，注意这里不能开方，要不会爆精度。
inline line make_line(point a,point b){
    line ret;
    ret.k=(a.y-b.y)/(a.x-b.x);
    ret.b=a.y-a.x*ret.k;
    return ret;
}//计算两点构成的线，这题没有用到
inline double dis_ltop(point a,line b){
    return abs(b.k*a.x+-1*a.y+b.b)/sqrt(1+b.k*b.k);
}//计算点到直线的距离，这题没有用到
inline double dis_ltop(point a,point p,point q){
    double d1=(q.x-p.x)*(a.x-p.x)+(q.y-p.y)*(a.y-p.y);//一些神奇的数学方法。
    if(d1<=0)return dis(a,p);//如果早p点一侧，且垂足不在线段上，输出a到p的距离。
    double d2=dis(p,q);
    if(d1>=d2)return dis(a,q);//如果早q点一侧，且垂足不在线段上，输出a到q的距离。
    double r=d1/d2;
    point h;//构造垂足
    h.x=p.x+(q.x-p.x)*r;
    h.y=p.y+(q.y-p.y)*r;
    return dis(h,a);
    //return dis_ltop(a,make_line(p,q));会WA的算法，因为里面涉及到一些开方。
}//计算点到线段的距离。
double mx=-1e18,mn=1e18;//注意要开到大一点，如果开小会被卡掉。
int main()
{
    cin>>n>>o.x>>o.y;
    for(int i=1;i<=n;++i){
        scanf("%lf%lf",&p[i].x,&p[i].y);
        double r=dis(p[i],o);
        mx=max(mx,r);
        mn=min(mn,r);
	}
	for(int i=1;i<=n;++i){
	    int j=i+1;if(j>n)j-=n;
	    mn=min(mn,dis_ltop(o,p[i],p[j]));
	}
	printf("%.18lf",(mx-mn)*acos(-1));//acos(-1)几乎等于圆周率，这也是某位不愿透露姓名的大佬告诉我的。
}
```

---

## 作者：liuyifan (赞：2)

## 来发一个坐标运算的板子

思路的话[这篇题解](https://www.luogu.org/blog/A3080529100/solution-cf613a)已经写的很清楚了,具体这里就不再赘述了

但是那篇题解中的一些运算不是很完全，所以来发个计算几何常用模版

资瓷点和直线的各种运算,具体见代码

code:
```cpp
#include<bits/stdc++.h>
#define reg register//register卡常 
#define ll long long//不开long long见祖宗 
#define inf 0x3f3f3f3f//lint无穷大
#define iinf 0x3f3f3f3f3f3f3f3f//long long无穷大 
#define pi acos(-1)//pi在三角函数上的标准定义,不会的回去看高一数学 
using namespace std;
class point //坐标系中的点 
{
	public:
		double x,y;//横纵坐标 
		point(reg double a=0,reg double b=0)
		{
			x=a;
			y=b;
		}//构造函数 
		inline point operator-(const point &b)const
		{
			return point(x-b.x,y-b.y);
		}//重载运算符 
		inline double operator*(const point &b)const
		{
			return x*b.x+y*b.y;
		}//同上 
		inline double operator^(const point &b)const
		{
			return x*b.y-y*b.x;
		}//同上 
};//点的模版
//上面的运算符支持各种运算 
class line //直线
//核心思想:一次函数的两点式 
{
	public:
		point s,e;//两点 
		line(point a=point(),point b=point())
		{
			s=a;
			e=b;
		}//构造函数 
};
ll n;//数据个数 
double l,r=iinf;//r要预先初始化为无穷大 
point p,a[100005];//定义点 
inline double len(reg point a)
{
	return sqrt(a*a);
}
inline double dis(reg point a,reg point b,reg point c)//点a到直线bc的模版 
{
	point x=a-b,y=c-b,z=c-a;
	if((x*y)<0)return len(x);
	if((y*z)<0)return len(z);//直接处理 
	//return fabs((x^y)/getlen(y));
	point v=c-b;
	double t=((a-b)*v)/(v*v);
	point fot=point(b.x+t*v.x,b.y+t*v.y);//求垂足，核心思想 
	return sqrt((fot.x-a.x)*(fot.x-a.x)+(fot.y-a.y)*(fot.y-a.y));
}//点到直线的距离 模版 
//下面是简单的主函数 
int main()
{
	scanf("%lld%lf%lf",&n,&p.x,&p.y);
	for(reg ll i=1;i<=n;i++)scanf("%lf%lf",&a[i].x,&a[i].y);
	a[n+1]=a[1];//处理环的常用方法 
	for(reg ll i=1;i<=n;i++)
	{
		l=max(l,len(a[i]-p));//最大 
		r=min(r,dis(p,a[i],a[i+1]));//最小
		//分别计算最大值和最小值 
	}
	printf("%.8f",pi*(l*l-r*r));//输出结果，记得乘pi 
	return 0;//圆满的结束 
}
```


---

## 作者：David24 (赞：1)


我们很容易想到：这个多边形扫过的面积是一个圆环形。那么我们只需要找出这个圆环最外边的圆的半径与最里面的圆的半径，将两者平方的差乘上 $\pi$ 即可。推导：最大的圆的面积为 $\pi r_1^2$，最小的圆的面积为 $\pi r_2^2$，圆环的面积为两者的差，即 $\pi r_1^2 - \pi r_2^2$。提取 $\pi$ 这个公因子，得：$\pi (r_1^2 - r_2^2)$。

这时，我们很容易可以得出一个做法：利用距离公式 $dis = \sqrt {(x_2 - x_1) ^2 + (y_2 - y_1)^2}$ 计算出每个点与点 P 之间的距离，然后取其中的最大值和最小值即可。很不幸的是，这个做法存在严重的问题：在某些情况下，最小的圆并不是由点绕 P 旋转得出的，而是由一条边绕点 P 得出的。这是因为，一条边在旋转过程中形成的圆的半径是点 P 到它的垂线，如果这条垂线的长度小于离点 P 最近的点与点 P 的长度，那么最小的圆就是由这条线段贡献的。

首先，题目中提到所有的边都是按照给出点的顺序顺次连接的，所以一共的边数为 $n$ 条，完全可以遍历一遍进行计算，时间复杂度为 $O(n)$。我们接下来考虑，对于每两个点来说，经过这两个点的一次函数的解析式是什么：对于经过点 $(x_1, y_1)$，$(x_2, y_2)$ 的解析式 $f(x) = kx + b$，我们可以列出方程组：
 
$\begin{cases}kx_1 + b = y_1 \space \space \space \space \space \space 1\\kx_2 + b = y_2 \space \space \space \space \space \space 2\end{cases}$

用 $1$ 式减 $2$ 式，得：$k = \dfrac{y_1 - y_2}{x_1 - x_2}$，$b = y_1 - kx_1 = y_1 - \dfrac{y_1 - y_2}{x_1 - x_2}x_1$。

因此，该函数的解析式为 $f(x) = \dfrac{y_1 - y_2}{x_1 - x_2} x + y_1 - \dfrac{y_1-y_2}{x_1 - x_2}x_1$。

这里我们有一个性质：两个一次函数如果互相垂直，那么它们的斜率之积为 $-1$。具体证明如下：

设 $f(x) = kx$，$g(x) = k'x$，函数 $f(x)$ 与 $x$ 轴的夹角为 $\alpha$，函数 $g(x)$ 与 $x$ 轴的夹角为 $\alpha + 90^{\circ}$，那么这两个函数明显互相垂直。

此时我们发现：$\tan{\alpha} = \dfrac{y}{x} = k$，$\tan(\alpha + 90^{\circ}) = \dfrac{y}{x} = k'$。也就是说，只要证明 $\tan(\alpha + 90^{\circ}) = - \dfrac{1}{\tan\alpha}$ 就可以证明 $k' = -\dfrac{1}{k}$了。

证明：$\tan(\alpha + 90^{\circ}) = \dfrac{\sin(\alpha + 90^{\circ})}{\cos(\alpha + 90^{\circ})} = \dfrac{\cos\alpha}{-\sin \alpha} = - \dfrac{1}{\tan \alpha}$

$\space \space \space \space \space \space\space \space \space \space \space \space\space \space \space \space \space \space\space \space \space \space \space \space\space \space \space \space \space \space\space \space \space \space \space \space\therefore k' = -\dfrac{1}{k}$

因为两个函数是否垂直只与其斜率有关，所以如果函数 $f(x) = kx + b$ 和 $g(x) = k'x + b'$ 垂直，那么必然有 $k' = -\dfrac{1}{k}$。

由此，我们可以算出与经过 $(x_1, y_1), (x_2, y_2)$ 两点的函数垂直的函数的斜率，设其截距为 $b'$，则其解析式为：$g(x) = \dfrac{x_2 - x_1}{y_1 - y_2}x + b'$。接下来，我们只需要找到 $f(x)$ 和 $g(x)$ 这两个函数的交点，即确定出 $g(x) = f(x)$ 的 $x$ 即可。因此，我们可以列出方程：
$$
\dfrac{x_2 - x_1}{y_1 - y_2}x + b' = \dfrac{y_1 - y_2}{x_1 - x_2} x + y_1 - \dfrac{y_1-y_2}{x_1 - x_2}x_1
$$
又因为 $g(x)$ 经过点 P$(x_p, y_p)$，所以我们可以列出方程组：
$$
\begin{cases}
\dfrac{x_2 - x_1}{y_1 - y_2}x + b' = \dfrac{y_1 - y_2}{x_1 - x_2} x + y_1 - \dfrac{y_1-y_2}{x_1 - x_2}x_1 \\
\\
\dfrac{x_2 - x_1}{y_1 - y_2}x_p + b'= y_p 
\end{cases}
$$
化简可得：

$
\begin{aligned}
b' &= y_p - \dfrac{x_2 - x_1}{y_1 - y_2}x_p \\
\dfrac{x_2 - x_1}{y_1 - y_2}x + y_p - \dfrac{x_2 - x_1}{y_1 - y_2}x_p &= \dfrac{y_1 - y_2}{x_1 - x_2}x + y_1 - \dfrac{y_1-y_2}{x_1 - x_2}x_1  \\
\dfrac{x_2 - x_1}{y_1 - y_2}x - \dfrac{y_1 - y_2}{x_1 - x_2}x &= y_1 - y_p + \dfrac{x_2 - x_1}{y_1 - y_2}x_p -\dfrac{y_1-y_2}{x_1 - x_2}x_1 \\
(\dfrac{x_2 - x_1}{y_1 - y_2} - \dfrac{y_1 - y_2}{x_1 - x_2})x &= y_1 - y_p + \dfrac{x_2 - x_1}{y_1 - y_2}x_p -\dfrac{y_1-y_2}{x_1 - x_2}x_1 \\
x &= \dfrac{y_1 - y_p + \dfrac{x_2 - x_1}{y_1 - y_2}x_p -\dfrac{y_1-y_2}{x_1 - x_2}x_1}{\dfrac{x_2 - x_1}{y_1 - y_2} - \dfrac{y_1 - y_2}{x_1 - x_2}} \\
\end{aligned} $

此时 $g(x)$ 的解析式为 $g(x) = \dfrac{x_2 - x_1}{y_1 - y_2}x + y_p - \dfrac{x_2 - x_1}{y_1 - y_2}x_p$。将 $x$ 代入，得：

$y = \dfrac{x_2 - x_1}{y_1 - y_2} \times \dfrac{y_1 - y_p + \dfrac{x_2 - x_1}{y_1 - y_2}x_p -\dfrac{y_1-y_2}{x_1 - x_2}x_1}{\dfrac{x_2 - x_1}{y_1 - y_2} - \dfrac{y_1 - y_2}{x_1 - x_2}} + y_p - \dfrac{x_2 - x_1}{y_1 - y_2}x_p$。

也就是说，此时垂足的坐标为：

$(\dfrac{y_1 - y_p + \dfrac{x_2 - x_1}{y_1 - y_2}x_p -\dfrac{y_1-y_2}{x_1 - x_2}x_1}{\dfrac{x_2 - x_1}{y_1 - y_2} - \dfrac{y_1 - y_2}{x_1 - x_2}}, \dfrac{x_2 - x_1}{y_1 - y_2} \times \dfrac{y_1 - y_p + \dfrac{x_2 - x_1}{y_1 - y_2}x_p -\dfrac{y_1-y_2}{x_1 - x_2}x_1}{\dfrac{x_2 - x_1}{y_1 - y_2} - \dfrac{y_1 - y_2}{x_1 - x_2}} + y_p - \dfrac{x_2 - x_1}{y_1 - y_2}x_p)$

我们此时只需要计算垂足和点 P 之间的距离，将其与某个点到点 P 最小值比较即可（最大值一定是点 P 与某节点的距离）。

注意：当 $x_1 = x_2$ 时，$f(x)$ 不是函数，需要特判：此时垂足坐标为 $(x_1, y_p)$。当 $y_1 = y_2$ 时，$g(x)$ 不是函数，需要特判：此时垂足坐标为 $(x_p, y_1)$。而且，当垂足不在该线段上，而是在线段的延长线上时，不应该计入答案中，需要特判垂足横坐标与纵坐标是否都大于等于线段两端点中横纵坐标的最小值且小于等于线段两端点中横纵坐标的最大值。

由于答案为平方的差与 $\pi$ 的积，而距离公式中又带有根号，我们可以将二者抵消：计算两点距离时不加根号，输出答案中直接输出最大值和最小值的差与 $\pi$ 的积。



``` c++
#include <iostream>
#include <iomanip>
using namespace std;
const int N = 1e5+10;
const double Pi = 3.141592653589793238462643383;
#define int double
int n, Px, Py, cx, cy;
int x[N], y[N];
int maxn, minn;
signed Pair;
int dis(int ax, int ay, int bx, int by) {return (ax - bx) * (ax - bx) + (ay - by) * (ay - by);}
signed main()
{
    cin >> n >> Px >> Py;
    for (signed i = 1; i <= n; i++) cin >> x[i] >> y[i];
    minn = 0x3f3f3f3f3f3f3f3f;
    maxn = 0;
    for (signed i = 1; i <= n; i++)
    {
        maxn = max(maxn, dis(Px, Py, x[i], y[i]));
        minn = min(minn, dis(Px, Py, x[i], y[i]));
    }
    for (signed i = 1; i <= n; i++)
    {
        if (i == 1) Pair = n;
        else Pair = i - 1;
        if (x[Pair] == x[i])
        {
            cx = x[i];
            cy = Py;
        }
        else if (y[Pair] == y[i])
        {
            cx = Px;
            cy = y[i];
        }
        else
        {
            cx = (y[Pair] - Py + (x[i] - x[Pair]) / (y[Pair] - y[i]) * Px - (y[Pair] - y[i]) / (x[Pair] - x[i]) * x[Pair]) / ((x[i] - x[Pair]) / (y[Pair] - y[i]) - (y[Pair] - y[i]) / (x[Pair] - x[i]));
            cy = (x[i] - x[Pair]) / (y[Pair] - y[i]) * cx + Py - (x[i] - x[Pair]) / (y[Pair] - y[i]) * Px;
        }
        if (cx < min(x[Pair], x[i]) || cx > max(x[Pair], x[i])) continue;
        if (cy < min(y[Pair], y[i]) || cy > max(y[Pair], y[i])) continue;
        minn = min(minn, dis(Px, Py, cx, cy));
    }
    cout << fixed << setprecision(16) << (maxn - minn) * Pi;
    return 0;
}
```

---

## 作者：shao0320 (赞：1)

#### CF613A Peter and Snow Blower

简单几何题目。

贡献一个初中数学解法，~~向量点积都拜拜~~

首先这题目是求一个圆环的面积，因此直接算出外面的那个圆的半径和里边这个圆的半径即可。

外边的比较好算，因为最远的一定是某个顶点，因此只需要把所有的顶点距离取个最大值即可。

重点讨论里边的。

最短距离肯定是给定的点到某条边的最短距离，那怎么求这个距离呢，考虑枚举边，然后点到直线任一点最短距离就是到垂足。

设枚举的这个边相邻的顶点是$(x_1,y_1)$和$(x_2,y_2)$

那这条边的斜率即为$k=\frac{y_2-y_1}{x_2-x_1}$

带入一个端点即可求出解析式，我们这里为了方便表示设其为$y=k_1x+b_1$

然后考虑两条直线垂直的性质，如果有两条直线为$y=kx+b$和$y=Kx+B$满足垂直，那么一定有$k\times K=-1$

假设这条垂线的解析式为$y=k_2x+b_2$，那么$k_2=-\frac{1}{k}$。

带入即可算出$b_2$

这个时候垂足就是这两条直线的交点，联立即可解出交点坐标。

如果这个点在线段上那么他一定满足横坐标大于一个端点而小于另一个端点，对于满足条件的垂足我们统计答案即可。

这里有一个问题就是如果这条边平行于坐标轴会歇逼，那么判掉这种情况即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define N 200005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n;
double maxn=0.0,minn=1e18,x[N],y[N],X,Y;
double dis(int pos){return (x[pos]-X)*(x[pos]-X)+(y[pos]-Y)*(y[pos]-Y);}
double calc(int pos)
{
	double X1=x[pos],Y1=y[pos],x2=x[pos+1],y2=y[pos+1];
	if(X1==x2)
	{
		if(Y<min(Y1,y2)||Y>max(Y1,y2))return 1e18;
		return fabs(X1-X)*fabs(X1-X);
	}
	double k=(y2-Y1)/(x2-X1),b=Y1-X1*k;
	double K=((k==0)?(1e18):(-1/k)),c=Y-K*X,posx=(b-c)/(K-k),posy=K*posx+c;
	//cout<<pos<<" "<<X1<<" "<<Y1<<" "<<x2<<" "<<y2<<" "<<posx<<" "<<posy<<" "<<k<<" "<<b<<" "<<K<<" "<<c<<endl;
	if(posx>max(X1,x2)||posx<min(X1,x2))return 1e18;
	return (X-posx)*(X-posx)+(Y-posy)*(Y-posy);
}
int main()
{
	n=read();X=read();Y=read();
	for(int i=1;i<=n;i++)
	{
		x[i]=read();
		y[i]=read();
		maxn=max(maxn,dis(i));
		minn=min(minn,dis(i));
	}
	x[n+1]=x[1];y[n+1]=y[1];
	for(int i=1;i<=n;i++)minn=min(minn,calc(i));
	printf("%.18lf\n",(maxn-minn)*acos(-1));
}

```



---

## 作者：henhen_ (赞：0)

无聊，来写题解。
### 题目大意
一个多边形，求该多边形绕给出的原点转一圈以后扫过的面积。
如果你学过高中数学必修二，那么就可以~~秒切~~这道题。
### 我的思路
我们需要找到这个多边形的最远端和最近端就可以了。

那么有同学就会说了，最远端和最近端不就是距离原点最远的点和最近的点吗？

其实不是！！！

对于最远端，它就是最远的点，找出最大值即可。

但对于最小值，则会出现以下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/dzol48t9.png)

如图：对于原点 $A$，距离它最近的点是 $B$，但我们可以很容易的发现，多边形距原点的最近端是过 $A$ 点向线段 $BC$ 做垂线。

这样，就会出现如下两种情况：

能做垂线和不能做垂线。

$\bullet$ 而对于这两种情况的判断，用余弦定理判断一下就行了。

$\bullet$ 如果不能做垂线，直接判断线段两点谁距离原点近。

对于能做垂线的情况，已经知道了三个点的坐标，连接原点和线段两点，构成了一个三角形，利用海伦公式求出面积，除以线段长，即可求出高。

不要忘了判断最后一个点和第一个点连成的线段（悲）。

### 附上代码
```
#include<bits/stdc++.h>
#define int double
using namespace std;
int n,xx,yy;
int x,y;
int minn1=LLONG_MAX,minn2=LLONG_MAX,minn3,minn,maxx=-101002;
int x1,y1,x2,y2,xx1,yy1;
signed main(){
	scanf("%lf%lf%lf",&n,&xx,&yy);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&x,&y);
		maxx=max(maxx,(x-xx)*(x-xx)+(y-yy)*(y-yy));//勾股定理求线段长 
//		minn1=minn1(minn1,(x-xx)*(x-xx)+(y-yy)*(y-yy));
    	x2=x1,y2=y1;
		x1=x,y1=y;
		int a=sqrt(abs(x1-x2)*abs(x1-x2)+abs(y1-y2)*abs(y1-y2));//求出三边长，便于判断 
		int b=sqrt(abs(x1-xx)*abs(x1-xx)+abs(y1-yy)*abs(y1-yy));
		int c=sqrt(abs(x2-xx)*abs(x2-xx)+abs(y2-yy)*abs(y2-yy));
		if(i==1){
			xx1=x,yy1=y;
			minn=b;
			continue;
		}
		if(i==n){
			a=sqrt(abs(x1-xx1)*abs(x1-xx1)+abs(y1-yy1)*abs(y1-yy1));
		    b=sqrt(abs(x1-xx)*abs(x1-xx)+abs(y1-yy)*abs(y1-yy));
		    c=sqrt(abs(xx1-xx)*abs(xx1-xx)+abs(yy1-yy)*abs(yy1-yy));
		}
//		cout<<a<<" "<<b<<" "<<c<<endl;
//		cout<<(a*a+b*b-c*c)/(2*a*b)<<" "<<(a*a+c*c-b*b)/(2*a*c)<<endl;
		if((a*a+b*b-c*c)<=0||(a*a+c*c-b*b)<=0){// 余弦定理 
		minn=min(minn,min(b,c));
	}else{
		int p=(a+b+c)/2;
		minn=min(minn,sqrt(p*(p-a)*(p-b)*(p-c))*2/a);//海伦公式 
//		cout<<minn<<endl;
	}
//	cout<<minn<<endl;
	}	
//	cout<<minn<<endl;
	printf("%.18lf",(maxx-minn*minn)*3.141592653589793238462643383279);
}
```



---

## 作者：Toothless03 (赞：0)

~~来水一篇向量题解~~

第一眼一看：多边形扫过的面积不就是个圆环吗，不就记录个定点到每个点的长度的最值吗 $r_{max},r_{min}$ 然后答案就是 $\pi(r_{max}^2-r_{min}^2)$ ，交上去： $\text{Wrong answer on test 3}$ ，~~直接爆粗口~~。

经过 $n$ 分钟后突然意识到貌似还要看看定点到每条边（**注意：边是条线段，不是直线**）的距离诶

前置芝士：点乘，叉乘

下面主要讲如何计算定点到**线段**的距离

![](https://cdn.luogu.com.cn/upload/image_hosting/2tz9kp03.png)

(先放一张图)

1) 如何判 $D$ 是否在**线段** $BC$ 上

很明显：只要 $\angle B, \angle C < \frac{\pi}{2}$ 就可以了，由于算角度精度较低，所以就有了点积的方法：

构造向量 $\vec{BA}, \vec{BC}$ 如果 $\vec{BA}\cdot\vec{BC} \ge 0$ 则 $D$ 在线段 $BC$ 上，反之不然。

2) 如何算 $A$ 到 $BC$ 的距离

（稍微吐槽直线方程亿秒钟，差点没算 s 我）

由于二维的向量叉积可以表示向量组成的平行四边形的面积，而平行四边形的面积有等于 $AD\times BC$ ， $BC$ 可以用两点距离公式算出来，于是这道题就解决了。

贴上代码
```cpp
double pi = acos(-1);
struct point {
	double x, y;
	point(double _x = 0, double _y = 0)
		: x(_x), y(_y) {}
	inline void read() {
		cin >> x >> y;
	}
	inline friend double dist(point a, point b) {//两点距离公式
		double sq1 = (a.x - b.x), sq2(a.y - b.y);
		return sqrt(sqr(sq1) + sqr(sq2));
	}
	inline friend bool operator==(point a, point b) {
		return a.x == b.x && a.y == b.y;
	}
	inline friend bool operator!=(point a, point b) {
		return a.x != b.x || a.y != b.y;
	}
	inline friend point operator-(point a, point b) {
		return point(a.x - b.x, a.y - b.y);
	}
	inline friend point operator+(point a, point b) {
		return point(a.x + b.x, a.y + b.y);
	}
	inline friend double cross(point a, point b) {//叉乘的坐标运算
		return a.x * b.y - a.y * b.x;
	}
	inline friend double dot(point a, point b) {//点乘的坐标运算
		return a.x * b.x + a.y * b.y;
	}
	inline friend point operator*(point a, double b) {
		return point(a.x * b, a.y * b);
	}
};
double dist_sqr(point a, point b) {//两点距离的平方
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}
inline double distl_sqr(point a, point p, point q) {//点到直线
	if (dot(a - q, p - q) < 0 || dot(a - p, q - p) < 0)//$D$ 没在 $BC$ 上
		return dist_sqr(a, p);
	return cross(p - a, q - a) * cross(p - a, q - a) / dist_sqr(p, q);//返回 $cross(p - a, q - a) / dist(p, q)$ 的平方
}
signed main() {
	int n; cin >> n;
	point rt; rt.read();
	vector<point> p(n);
	double maxi = 0, mini = 1e18;//$r_{max}^2$ 和 $r_{min}^2$
	for (int i = 0; i < n; i++)
		p[i].read();
	for (int i = 0; i < n; i++)
		maxi = max(maxi, dist_sqr(p[i], rt)), mini = min(mini, dist_sqr(p[i], rt));
	for (int i = 0; i < n; i++) {
		point a = p[i], b = p[(i + 1) % n];
		mini = min(mini, distl_sqr(rt, a, b));//只需要更新最近点，最远点一定在多边形的定点上
	}
	printf("%.7llf", pi * (maxi - mini));
}
```

---

