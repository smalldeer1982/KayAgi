# [BalticOI 1996] A SQUARE AND A CIRCLE (Day 1)

## 题目描述

一个平面上有一个正方形和一个圆，给定正方形的两个相对顶点的坐标和圆的圆心坐标和半径，求这个正方形和这个圆的公共面积。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$-1200.00 \le x_i,y_i \le 1200.00$，$0 < r \le 200.00$。
#### 分值说明  
本题分值按 BOI 原题设置，**满分** $30$ 。
#### 题目说明  
来源于 Baltic Olympiad in Informatics 1996 的 [Day 1:A SQUARE AND A CIRCLE](https://boi.cses.fi/files/boi1996_day1.pdf) 。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
0 5.0
10.00 -5
3.0 1 4.00```

### 输出

```
46.64```

# 题解

## 作者：_outcast_ (赞：5)

暂时还没有想到简单的做法

不过这个题是可以套板子的

事实上，我们不仅能做正方形与圆的面积交，还能做任
意多边形与圆的面积交。

由于洛谷上没有相关的题目只好先写在这里了 ~~(虽然这是黄题)~~

### 前置芝士
- 向量的叉积：

如果你不知道什么是向量的叉积可以看这篇 [blog](https://blog.csdn.net/hc14519/article/details/50716299)，
我这里直接给定理了：
>设 $\Delta ABC$ 中的两条边 $\vec{a}=(x_1,y_1)$，$\vec{b}=(x_2,y_2)$，
有$S_{\Delta ABC}=\dfrac{|x_1y_2-x_2y_1|}{2}$，即 $\vec{a}\times \vec{b}=|\vec{a}||\vec{b}|\sin<\vec{a},\vec{b}>$

这个公式可以帮助我们利用向量快速求三角形面积

### 解析
我们知道任意一个多边形内选取一点，可以把多边形划分为多个三角形，像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/kgqr66xw.png)

凹多边形也是可以的，你可以自己画一画
（事实上平面内任意一点都可以把一个多边形划分为多个三角形）

所以问题就转化为了把一个多边形划分为多个三角形，然后分别求它与圆的面积交

新的问题产生了：我们该选哪一个点来划分呢？相信聪明的你已经猜到是圆的圆心了吧

划分的三角形有以下的情况：

- 三角形两边都在圆内

![](https://cdn.luogu.com.cn/upload/image_hosting/elour57x.png)

对于这种情况，直接计算三角形面积就行了

- 一边在圆内，一边在圆外

![](https://cdn.luogu.com.cn/upload/image_hosting/chap2ukq.png)

对于这种情况，计算 $\Delta OBD$ 和扇形 $OED$ 的面积

- 两边在圆外，且 $AB$ 与圆不相交

![](https://cdn.luogu.com.cn/upload/image_hosting/28n1o39l.png)

对于这种情况，计算扇形 $OEF$ 的面积

- 两边在圆外，且 $AB$ 与圆相交

![](https://cdn.luogu.com.cn/upload/image_hosting/02y59a28.png)

这个与第二种差不多求一个三角形和两个扇形的面积

（emm，这图片尺寸调不来啊>_<）

至此，我们相当于已经理论切掉了这道题，但是这道题的代码比较难写
### 代码实现
此题主要采用向量运算，来看看具体怎么实现

- 向量的基本运算

这个不用我多说了吧，看注释
```cpp
double det(point a,point b){ return a.x*b.y-a.y*b.x;}//叉乘 
double dot(point a,point b){ return a.x*b.x+a.y*b.y;}//数量积（点乘） 
point operator *(point a,double t){ return point(a.x*t,a.y*t);}//数乘 
point operator +(point a,point b){ return point(a.x+b.x,a.y+b.y);}//加 
point operator -(point a,point b){ return point(a.x-b.x,a.y-b.y);}//减 
double Length(point A){return sqrt(dot(A,A));}//向量模长
```
- 判断一边是否在圆内

这个也非常简单，直接比较长度和圆的半径
```cpp
int dcmp(double x){//这个函数是用来判断三角形上的向量是否在圆内（外） 
    if(fabs(x)<eps) return 0;
	if(x<0) return -1;
	return 1;
}
```

- 三角形两边都在圆内

直接叉乘算三角形面积
```cpp
if(dcmp(DOA-C.r)<0&&dcmp(DOB-C.r)<0) return det(OA,OB)*0.5;//两边都在圆内，直接叉乘算面积 
```
（上面的 DOA，DOB 指的是向量 OA，OB 的模长，C.r 指圆的半径，下面不再赘述）

- 一边在圆内，一边在圆外

这个比较难，再来看一下图

![](https://cdn.luogu.com.cn/upload/image_hosting/chap2ukq.png)

我们先用叉乘求出 $\Delta OAB$ 的面积，我们要求 $\Delta OBD$ 的面积，就要算 $BD$，如何用已知量来表示 $BD$？

可以过 $O$ 做 $AB$ 的垂线交于 $M$ (由于图床空间不太够，我这里就不放图了，大家可以自己画一画)

推一下式子
$$
BD= \dfrac{(BM+MD)\times AB}{AB}
$$
$$
BD= \dfrac{\vec{BO} \cdot \vec{BA}+AB \times MD}{AB}
$$
问题转化为了用已知量求 AB $\times$ MD，于是
$$
AB\times MD= \sqrt{AB^2\times MD^2}
$$
勾股定理有
$$
AB\times MD= \sqrt{AB^2\times (OM^2+OD^2)}
$$
发现 $OD$ 正好是圆的半径，$OM=BO\sin\angle _{OBA}$ 于是

$$
AB\times MD=\sqrt{AB^2r^2+AB^2BO^2\sin^2\angle _{OBA}}
$$

发现 $AB\times BO\sin\angle _{OBA}$ 正好是 $\vec{BA}\times\vec{BO}$ ( 叉积 )

这样我们就把 $BD$ 用已知量表示出了
$$
BD=\dfrac{\vec{OB}\cdot\vec{BA}+\sqrt{AB^2r^2+(\vec{BA}\times\vec{BO})(\vec{BA}\times\vec{BO})}}{AB}
$$

再来计算扇形的面积，问题又转化为求$\angle_{DOE}$

考虑三角形面积公式
$$
S_{\Delta OAD}=\dfrac{OA\times OD\times\sin\angle_{DOE}}{2}
$$

利用反正弦函数（arcsin）求出 $\angle_{DOE}$

具体看代码
```cpp
    else if(DOB<r&&DOA>=r){//情况二 
        double x=(dot(BA,BO)+sqrt(r*r*DAB*DAB-det(BA,BO)*det(BA,BO)))/DAB;
        double TS=det(OA,OB)*0.5;
        return asin(TS*(1-x/DAB)*2/r/DOA)*r*r*0.5+TS*x/DAB;
        //这里比较难，要好好理解一下 
    }
    else if(DOB>=r&&DOA<r){
        double y=(dot(AB,AO)+sqrt(r*r*DAB*DAB-det(AB,AO)*det(AB,AO)))/DAB;
        double TS=det(OA,OB)*0.5;
        return asin(TS*(1-y/DAB)*2/r/DOB)*r*r*0.5+TS*y/DAB;
        //同上 
    }
```
- 两边在圆外，且 $AB$ 与圆不相交

这个就比较简单了，就是一个扇形的面积，反正弦函数求出角度即可

（需要注意的是反正弦函数只对 $[-\frac{\pi}{2},\frac{\pi}{2}]$ 有定义，所以对钝角的情况需要特判一下）

```cpp
    else if(fabs(det(OA,OB))>=r*DAB||dot(AB,AO)<=0||dot(BA,BO)<=0){
        if(dot(OA,OB)<0){
            if(det(OA,OB)<0) return (-acos(-1.0)-asin(det(OA,OB)/DOA/DOB))*r*r*0.5;
            else return (acos(-1.0)-asin(det(OA,OB)/DOA/DOB))*r*r*0.5;
        }
        else return asin(det(OA,OB)/DOA/DOB)*r*r*0.5;
    }
```

- 两边在圆外，且 $AB$ 与圆相交

求法与第二种情况相似，相信聪明的你一定会做吧！
```cpp
    else{
        double x=(dot(BA,BO)+sqrt(r*r*DAB*DAB-det(BA,BO)*det(BA,BO)))/DAB;
        double y=(dot(AB,AO)+sqrt(r*r*DAB*DAB-det(AB,AO)*det(AB,AO)))/DAB;
        double TS=det(OA,OB)*0.5;
        return (asin(TS*(1-x/DAB)*2/r/DOA)+asin(TS*(1-y/DAB)*2/r/DOB))*r*r*0.5 + TS*((x+y)/DAB-1);
    }
```
综上，我们就完成了所有情况的讨论

下面的代码给出了 n 边形与圆的面积交
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int maxn=200010;
const double eps=1e-12;
struct point{
    double x,y;
    point(){}
    point(double xx,double yy):x(xx),y(yy){}
};
struct Circle{
    point c; double r;
};
/*向量运算*/ 
double det(point a,point b){ return a.x*b.y-a.y*b.x;}
double dot(point a,point b){ return a.x*b.x+a.y*b.y;}
point operator *(point a,double t){ return point(a.x*t,a.y*t);}
point operator +(point a,point b){ return point(a.x+b.x,a.y+b.y);}
point operator -(point a,point b){ return point(a.x-b.x,a.y-b.y);}
double Length(point A){return sqrt(dot(A,A));}
 
int dcmp(double x){
    if(fabs(x)<eps) return 0;
	if(x<0) return -1;
	return 1;
}

/*计算圆与三角形面积交*/
double TriAngleCircle(Circle C, point A, point B){ 
    point OA=A-C.c,OB=B-C.c;
    point BA=A-B, BO=C.c-B;
    point AB=B-A, AO=C.c-A;
    double DOA=Length(OA),DOB=Length(OB),DAB=Length(AB),r=C.r;
    if(dcmp(det(OA,OB))==0) return 0;
    if(dcmp(DOA-C.r)<0&&dcmp(DOB-C.r)<0) return det(OA,OB)*0.5;
    else if(DOB<r&&DOA>=r){
        double x=(dot(BA,BO)+sqrt(r*r*DAB*DAB-det(BA,BO)*det(BA,BO)))/DAB;
        double TS=det(OA,OB)*0.5;
        return asin(TS*(1-x/DAB)*2/r/DOA)*r*r*0.5+TS*x/DAB;
    }
    else if(DOB>=r&&DOA<r){
        double y=(dot(AB,AO)+sqrt(r*r*DAB*DAB-det(AB,AO)*det(AB,AO)))/DAB;
        double TS=det(OA,OB)*0.5;
        return asin(TS*(1-y/DAB)*2/r/DOB)*r*r*0.5+TS*y/DAB;
    }
    else if(fabs(det(OA,OB))>=r*DAB||dot(AB,AO)<=0||dot(BA,BO)<=0){
        if(dot(OA,OB)<0){
            if(det(OA,OB)<0) return (-acos(-1.0)-asin(det(OA,OB)/DOA/DOB))*r*r*0.5;
            else return (acos(-1.0)-asin(det(OA,OB)/DOA/DOB))*r*r*0.5;
        }
        else return asin(det(OA,OB)/DOA/DOB)*r*r*0.5;
    }
    else{
        double x=(dot(BA,BO)+sqrt(r*r*DAB*DAB-det(BA,BO)*det(BA,BO)))/DAB;
        double y=(dot(AB,AO)+sqrt(r*r*DAB*DAB-det(AB,AO)*det(AB,AO)))/DAB;
        double TS=det(OA,OB)*0.5;
        return (asin(TS*(1-x/DAB)*2/r/DOA)+asin(TS*(1-y/DAB)*2/r/DOB))*r*r*0.5 + TS*((x+y)/DAB-1);
    }
}
point a[maxn];
int main(){
    double X,Y,r,ans=0; int N;
    cin>>N;
	rep(i,1,N) cin>>a[i].x>>a[i].y;
	cin>>X>>Y>>r;
	Circle C;
    C.c=point(X,Y); C.r=r;
    a[N+1]=a[1]; ans=0;
    rep(i,1,N) ans+=TriAngleCircle(C,a[i],a[i+1]);
    printf("%.2lf",fabs(ans));
}
```
这道题只是正方形与圆的面积交，稍微改一改上面的代码就可以了
### 后记

或许你不知道如何根据正方形不相邻的两点求出所有点的坐标（因为这个题不保证正方形的边与坐标轴平行）

可以看看[这里](https://zhidao.baidu.com/question/374490574378994124.html)

~~（其实是我太懒了）~~

还有一点 tips

细心的你一定发现我上面算叉积时没有加绝对值，而是在最后输出答案才加的，这样有什么好处呢？来看看下面一种情况

![](https://cdn.luogu.com.cn/upload/image_hosting/uyseskwk.png)

$\Delta ABC$ 与圆的面积交显然是黄色部分，但如果划分之后会发现 $\Delta OAB$，$\Delta OAC$，$\Delta OBC$ 分别与圆的面积交显然会大于黄色部分面积，算叉积时不取绝对值，就类似于容斥，可以避免上述情况


---

## 作者：AzzyZhe (赞：4)

## 题解 P7651 A SQUARE AND A CIRCLE
$\rightarrow$ [题目传送门](https://www.luogu.com.cn/problem/P7651)

基本思路是像微积分一样，将重叠图形分成很多小矩形，也用到了旋转，那就我再顺便讲下旋转的具体原理吧。

（图片瞎眼预警

### 思路&实现
----
不如让我们先考虑更为简单的情况：正方形中心在坐标原点，四个顶点都在坐标轴上。

![](https://cdn.luogu.com.cn/upload/image_hosting/bkxtvkqr.png)

可以利用微积分的思想，将所求面积分为许多小矩形，求其面积和。

![](https://cdn.luogu.com.cn/upload/image_hosting/f6ykrr3w.png)

以 $l(x)$ 表示在 $x$ 处小矩形的高，则总重叠面积可以表示为 $\int_a^bl(x)\,\mathrm{d}x$（或者说 $\sum\limits_{i=a}^b l(x + i\Delta x)\,\Delta x$）。

在 $x$ 处作一条横轴的垂线，合适范围内，其与两个图形分别产生两个交点。

则用两个上交点中较低一个的纵坐标减去两个下交点的较高一个的纵坐标即可得到 $l(x)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/twj8hc9b.png)

交点纵坐标直接用解析几何方法求解即可。

值得一提的是，记正方形对角线长的一半为 $len$ ，则其四边的方程可合并为：
$$\left\vert x\right\vert + \left\vert y\right\vert = len$$

特别地，由以上方法计算出的 $l(x)$ 为负时，我们视为矩形高度为 $0$，也就是没有。

而可能出现重合的 $x$ 的范围是两者左顶点中较大一个到右顶点较小一个，同时也能保证垂线分别有两个交点，此区间上求解即可。

将原问题转化为以上情况，旋转和平移即可。

我们该如何处理旋转呢？

可以将平面直角坐标系中的点看作复平面上的复数。则对任一点 $A(a,b)$ 有与之对应的复数 $z=a+bi$。

而欧拉告诉我们，对于复数 $z$ 还有：
$$z = \left\vert r\right\vert e^{\theta i} = \left\vert r\right\vert (\cos\theta + \sin\theta i)$$

由中间的式子我知道两个向量相加，模长相乘，复角相加；由最后面的式子我们知道可以通过三角与代数计算复数。

很容易推知只需给一个向量乘上一个复角为 $\theta$ 的单位复数（模长为 $1$ 的复数）$e^{\theta i}$，即可将其对应的点逆时针旋转 $\theta$。

而显然对于两个复数相乘：
$$z_1z_2 = (a + bi)(c + di) = (ac-bd) + (ad+bc)i$$

这里即为：
$$ze^{\theta i} = (a\cos\theta - b\sin\theta) + (a\sin\theta + b\cos\theta)i$$

因此我们只需计算该对角线的斜率，求出其倾斜角（利用反正切函数），再将几个点顺时针转过这个角大小（角取负）即可使正方形对角线与横轴平行。

由于`double`型里面是含有`inf`和`-inf`的（`cmath`库的三角函数也接受），所以无需对正方形对角线旋转前垂直于坐标轴分类讨论。

相信平移的部分不用赘述大家也理解，这个问题就被我们转化回了之前的问题。

由于本题精确到 $10^{-2}$，所以我们取 $\mathrm{d}x$ 为 $10^{-4}$。（其实仍不保险，不过本题 $10^{-3}$ 就可通过）（可根据 $\frac{\text{精度}}{l(x)_{max}}$ 设置 $\mathrm{d}x$）

实现的时候注意由于`y1`和`x1`等变量名是在头文件中定义了的，由于还是不想改变量名，我们使用`namespace`来防止重定义而 CE。

宏定义里的`##`表示连接变量名，例如下方代码中的`move(1)`展开后为`{x1-=x0,y1-=y0;}`。

### 代码
----
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace stO;
namespace AzzyZhe{
	double x1,y1,x2,y2,x3,y3,r;//各点坐标 圆半径
	double len,theta;//正方形半对角线长 要旋转度角度
	double x0,y0,px,py;//平移所用向量 旋转所用单位复数
	double ans=0.0;//面积
	#define dist(a,b) sqrt(pow(x##a-x##b,2)+pow(y##a-y##b,2)) 
	#define roll(id) {double tx,ty;tx=x##id*px-y##id*py,ty=x##id*py+y##id*px;x##id=tx,y##id=ty;} //旋转
	#define move(id) {x##id-=x0,y##id-=y0;} //平移
	void solve()
	{
		scanf("%lf%lf",&x1,&y1);
		scanf("%lf%lf",&x2,&y2);
		scanf("%lf%lf%lf",&x3,&y3,&r);
		theta=-atan((y1-y2)/(x1-x2));
		px=cos(theta),py=sin(theta);
		roll(1);roll(2);roll(3);
		x0=(x1+x2)/2,y0=(y1+y2)/2;
		move(1);move(2);move(3);
		if(x1>x2)
			swap(x1,x2),
			swap(y1,y2);
		len=(x2-x1)/2;
		double dx=1e-4,dl,r0;//微分x的大小 当前x下小矩形高度 当前x下圆方程解出y上下的偏移
		for(double x=max(x3-r,x1),y,z=min(x3+r,x2);x<z;x+=dx)
		{
			y=(len-fabs(x));
			r0=sqrt(pow(r,2)-pow(x-x3,2));
			dl=min(y3+r0,y)-max(y3-r0,-y);
			if(dl>0)
				ans+=dx*dl;
		}
		printf("%.2lf",ans);
	}
}
int mian()
{
	AzzyZhe::solve();
	return 0;
}
```


---

## 作者：StayAlone (赞：0)

参考了[该题解](https://www.luogu.com.cn/article/qfp7hdmj)的方式，但是提供一种通过向量计算圆与三角形面积交的方法。

先给出最简单的求出正方形四个顶点的方式：将 $A,D$ 分别绕对角线中点旋转 $\frac{\pi}{2}$ 即可。

-----------------

为了方便处理，将圆心移到坐标系原点。

以下图这种情况为例：

![](https://s21.ax1x.com/2025/03/21/pE0KDsS.png)

只要求出 $\overrightarrow{OD}$ 即可，这样就将问题转化为 $\overrightarrow{OD}$ 与 $\overrightarrow{OB}$ 的夹角（扇形面积）以及 $\overrightarrow{OA}$ 与 $\overrightarrow{OD}$ 围成的三角形面积。

都是容易处理的，注意面积的正负。

$\overrightarrow{OD}=\overrightarrow{OA}+\overrightarrow{AD}$，而 $\overrightarrow{AD}=\overrightarrow{AM}+\overrightarrow{MD}$。

其中 $\overrightarrow{AM}$ 是 $\overrightarrow{AO}$ 在 $\overrightarrow{AB}$ 上的投影向量；$\overrightarrow{MD}$ 的模长容易算（在直角三角形 $OMD$ 中），方向就是 $\overrightarrow{AB}$ 向量的方向，于是就都能简单地算出来。

这种方法在钝角情况同样适用，原因是向量投影下来是有方向的。

![](https://s21.ax1x.com/2025/03/21/pE0MeOS.png)

其他情况都类似，计算夹角使用 asin，并要注意特判钝角。

[AC record](https://www.luogu.com.cn/record/209150736)

```cpp
namespace Geometry {
    const double eps = 1e-9, pi = acos(-1), inf = 2e18;
    struct Vector {
        double x, y;
        Vector() {x = y = 0;}
        Vector(const double &x, const double &y) : x(x), y(y) {}
        Vector(const Vector &t) : x(t.x), y(t.y) {}
        friend Vector operator - (const Vector &x, const Vector &y) { return Vector(x.x - y.x, x.y - y.y); }
        Vector &operator -= (const Vector &t) { x -= t.x, y -= t.y; return *this; }
        friend Vector operator + (const Vector &x, const Vector &y) { return Vector(x.x + y.x, x.y + y.y); }
        Vector &operator += (const Vector &t) { x += t.x; y += t.y; return *this; }
        friend Vector operator / (const Vector &x, const double &y) { return Vector(x.x / y, x.y / y); }
        Vector &operator /= (const double t) { x /= t; y /= t; return *this; }
        friend Vector operator * (const Vector &x, const double &y) { return Vector(x.x * y, x.y * y); }
        friend Vector operator * (const double &y, const Vector &x) { return Vector(x.x * y, x.y * y); }
        Vector &operator *= (const double t) { x *= t; y *= t; return *this; }
        friend double operator * (Vector a, Vector b) { return a.x * b.x + a.y * b.y; } // dot Product
        friend double operator ^ (Vector a, Vector b) { return a.x * b.y - a.y * b.x; } // cross Product
        friend bool operator == (Vector a, Vector b) { return abs(a.x - b.x) < eps && abs(a.y - b.y) < eps; }
        friend bool operator < (Vector a, Vector b) { return abs(a.x - b.x) >= eps ? a.x < b.x : b.y - a.y >= eps; }
        il double mod() { return hypot(x, y); }
        il double mod2() { return x * x + y * y; }
        il void input() { scanf("%lf%lf", &x, &y); }
        il void print(char ch = '\n') { printf("%.3lf %.3lf%c", x, y, ch); }
    };
    typedef Vector Point;
    il double dot(Vector a, Vector b) { return a * b; }
    il double cross(Vector a, Vector b) { return a ^ b; }
    il double cross(Vector a, Vector b, Vector c) { return (b - a) ^ (c - a);}

    // it's a line segment when seg = true
    struct Line {
        Point A, B; double angle;
        Line() { }
        Line(const Point &A, const Point &B) : A(A), B(B), angle(atan2((B - A).y, (B - A).x)) {}
        il bool left(const Point &x) const { return cross(B - A, x - A) > 0; }
        il bool right(const Point &x) const { return cross(B - A, x - A) < 0; }
        // friend bool operator == (Line a, Line b) {return a.A == b.A && a.B == b.B; }
        friend bool operator < (const Line &x, const Line &y) {
            if (abs(x.angle - y.angle) < eps) return y.left(x.A);
            return x.angle < y.angle;
        }
        il void print() { A.print(' '); ptc(' '); B.print('\n'); }
    };

    Point intersection(const Line &x, const Line &y) { // ensure they aren't parallel
        Vector AB = y.A - x.A, v1 = x.B - x.A, v2 = y.B - y.A;
        return x.A + (((AB ^ v2) / (v1 ^ v2)) * v1);
    }

    il double dis(const Point &p, const Line &l) {
        Vector pA = l.A - p, pB = l.B - p, AB = l.B - l.A;
        return fabs(pA ^ pB) / AB.mod();
    }

    il double entri(Point A, Point B) { return (A ^ B) / 2; }

    il double enfan(Point A, Point B) {
        if (A * B < 0) {
            if ((A ^ B) < 0) return -pi - asin((A ^ B) / A.mod() / B.mod());
            return pi + asin((A ^ B) / A.mod() / B.mod());
        } return asin((A ^ B) / A.mod() / B.mod());
    }

    il double triangle(double R, Point A, Point B) {
        auto AB = Line(A, B);
        const double dA = A.mod(), dB = B.mod(), S = R * R / 2, ds = dis({0, 0}, AB);
        bool flg1 = dA - R > eps, flg2 = dB - R > eps;
        Vector ba = A - B, _B = -1 * B;
        Vector ab = B - A, _A = -1 * A;
        if (dB < eps || dA < eps) return 0;
        if (!flg1 && !flg2) return entri(A, B);
        else if (!flg1) {
            Vector x1 = ab / ab.mod() * (_A * ab / ab.mod());
            double flen = sqrt(R * R - ds * ds); x1 += ab / ab.mod() * flen;
            Point D = A + x1;
            return entri(A, D) + enfan(D, B) * S;
        } else if (!flg2) {
            Vector x1 = ba / ba.mod() * (_B * ba / ba.mod());
            double flen = sqrt(R * R - ds * ds); x1 += ba / ba.mod() * flen;
            Point D = B + x1;
            return enfan(A, D) * S + entri(D, B);
        } else {
            if (ds - R > eps || dot(ab, -1 * A) < -eps || dot(ba, -1 * B) < -eps) return enfan(A, B) * S;
            else {
                Vector x1 = ba / ba.mod() * (_B * ba / ba.mod());
                double flen = sqrt(B.mod2() - ds * ds) + sqrt(R * R - ds * ds); x1 = x1 / x1.mod() * flen;
                Point D1 = B + x1;
                Vector x2 = ab / ab.mod() * (_A * ab / ab.mod());
                double flen2 = sqrt(A.mod2() - ds * ds) + sqrt(R * R - ds * ds); x2 = x2 / x2.mod() * flen2;
                Point D2 = A + x2;
                return enfan(A, D1) * S + entri(D1, D2) + enfan(D2, B) * S;
            }
        }
    }
}
using namespace Geometry;
double x[4], y[4];
double x5, y5, r, opt;

int main() {
    cin >> x[0] >> y[0] >> x[2] >> y[2] >> x5 >> y5 >> r;
    x[0] -= x5; y[0] -= y5; x[2] -= x5; y[2] -= y5; x5 = y5 = 0;
    double mx = (x[0] + x[2]) / 2, my = (y[0] + y[2]) / 2;
    x[1] = (x[0] - mx) * cos(pi / 2) - (y[0] - my) * sin(pi / 2) + mx, y[1] = (y[0] - my) * cos(pi / 2) + (x[0] - mx) * sin(pi / 2) + my;
    x[3] = (x[2] - mx) * cos(pi / 2) - (y[2] - my) * sin(pi / 2) + mx, y[3] = (y[2] - my) * cos(pi / 2) + (x[2] - mx) * sin(pi / 2) + my;
    rep1(i, 0, 3) opt += triangle(r, Point(x[i], y[i]), Point(x[(i + 1) & 3], y[(i + 1) & 3]));
    printf("%.2lf", abs(opt));
    return 0;
}
```

---

