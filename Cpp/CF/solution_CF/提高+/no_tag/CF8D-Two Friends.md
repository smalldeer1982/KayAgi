# Two Friends

## 题目描述

平面上有3个点：A，B，C.(a cinema, a shop and the house) 现在Alice和Bob都在A，Alice想要走到B，走的路线长度减去最短路线长度不得超过t1，Bob想经过C然后到B， 走的路径长减去最短路径长不超过t2。 要求设计他们的路线，使得从A开始的公共部分尽可能长（也就是一旦两人分开，即使重 新会合也不计入公共部分的长度了）

## 样例 #1

### 输入

```
0 2
0 0
4 0
-3 0
```

### 输出

```
1.0000000000
```

## 样例 #2

### 输入

```
0 0
0 0
2 0
1 0
```

### 输出

```
2.0000000000
```

# 题解

## 作者：C3H5ClO (赞：7)

题目翻译有错！是Alan先去C再去B，而不是Bob。

思路另外几位大佬已经基本讲了，我来谈谈二分法的细节。

### 第一步，分类讨论

如果Bob有充足时间陪Alan先去C再去B，则陪他走完。然而，时间可能还有剩余，俩朋友可能会原地转圈圈聊天。

此时的条件为AC+BC-AB<=t2

路程需要小于AB＋t2，还要小于AC＋CB＋t1，因此

路程＝min(AC+CB+t1,AB+t2)

### 第二步，二分

既然Alan无法一路陪Bob，就求出从A开始两人一起走的最大路程。不妨设一起走的位移终点为P，则路程为AP。由于AP越大，方案显然越不可行（满足单调性)，因此用二分来枚举AP并判断可不可行。

![](https://cdn.luogu.com.cn/upload/pic/60201.png)

### 第三步，判断方案可行性。

对于Alan，AP+PC+CB-AC+CB<=t1，即AP+PC-AC<=t1,PC<=AC-AP+t1

P点的可行位置在以C为圆心，AC-AP+t1为半径的圆内（包括圆上）

同理，P也应该在以B为圆心，AB-AP+t2为半径的圆内（包括圆上）

而由于AP一定，P同样应该在以A为圆心，AP为半径的圆上（不包括圆内）

因此，问题转化为了判断圆A是否与另外两圆的交有交点，等价于判断三圆是否有公共区域（可以退化为一个点）。

三圆要有公共区域，前提是圆两两不相离。

然后分类讨论，在圆两两不相离的前提下，若一个圆被另一个圆包含，则三圆必定有公共区域。（画图辅助理解）

![](https://cdn.luogu.com.cn/upload/pic/60211.png)

若圆不存在包含关系，可能会出现下左的情况。

![](https://cdn.luogu.com.cn/upload/pic/60212.png)

因此，只需要随便哪个两圆交点在另一个圆内就可以得出三圆有公共区域的结论。

本题涉及计算几何内容有:

1.判断圆与圆位置关系（相离、相切、相交、包含）
2.求圆与圆的交点（两圆方程相减转化为直线和圆的交点处理）
3.判断点与圆位置关系

着重讲一下，由于反复计算导致精度误差大，解一元二次方程时eps要在5e-10以上，在加上本题对精度要求较高，因此eps取6e-10至1e-9为宜。

其他细节在代码里讲解！
```cpp
#include<cstdio>
#include<math.h>
#include<algorithm>
using namespace std;
const double eps=6e-10;
const int INF=987654321;
double t1,t2,l,r,mid;
struct point
{
    double x,y;
};
struct circle
{
    double r;
    point p;
    double c,d,e;
}c1,c2,c3;//圆的方程:(x-p.x)^2+(y-p.y)^2=r^2或x^2+y^2+cx+dy+e=0
struct line
{
    double a,b,c;
};//直线方程:ax+by+c=0，避免斜截式处理k=INF的情况
inline double sqr(double x)
{
    return x*x;
}
inline void change(circle &c)//圆两种表示形式的转换
{
    c.c=-c.p.x*2;
    c.d=-c.p.y*2;
    c.e=sqr(c.p.x)+sqr(c.p.y)-sqr(c.r);
}
inline double getDis(point a,point b)//两点间距离
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline double getDis(point p,line l)//点到直线距离
{
    return fabs(l.a*p.x+l.b*p.y+l.c)/sqrt(l.a*l.a+l.b*l.b);
}
inline int pointAndCircle(point p,circle c)//判断点与圆的位置关系
{
    if(getDis(p,c.p)-c.r>eps)return 0;
    if(fabs(getDis(p,c.p)-c.r)<=eps)return 1;
    return 2;
}
inline int lineAndCircle(line l,circle c)//判断直线与圆位置关系
{
    if(getDis(c.p,l)-c.r>eps)return 0;
    if(fabs(getDis(c.p,l)-c.r)<=eps)return 1;
    return 2;
}
inline int circleAndCircle(circle c1,circle c2)//判断圆与圆位置关系
{
    if(getDis(c1.p,c2.p)-c1.r-c2.r>eps)return 0;
    if(fabs(getDis(c1.p,c2.p)-c1.r-c2.r)<=eps)return 1;
    if(c1.r-getDis(c1.p,c2.p)-c2.r>eps)return 3;
    if(c2.r-getDis(c1.p,c2.p)-c1.r>eps)return 4;
    return 2;
}
inline int jyyecfc(double a,double b,double c,double &x1,double &x2)//解方程ax^2+bx+c=0，返回值表示解个数
{
    if(fabs(a)<=eps&&fabs(b)<=eps&&fabs(c)<=eps)return INF;
    if(fabs(a)<=eps&&fabs(b)<=eps)return 0;
    if(fabs(a)<=eps)
    {
        x1=-c/b;
        return 1;
    }
    double d=b*b-a*c*4;
    if(d<-eps)return 0;
    if(fabs(d)<=eps)
    {
        x1=-b/a/2;
        return 1;
    }
    x1=(-b+sqrt(d))/a/2;
    x2=(-b-sqrt(d))/a/2;
    return 2;
}
inline int lineCutCircle(line l,circle c,point &p1,point &p2)//求解直线与圆的交点，返回值表示交点个数
{
    int x=lineAndCircle(l,c);
    if(x==0)return 0;
    double x1,x2;
    if(l.a==0)
    {
        jyyecfc(1,c.c,c.e+c.d*(-l.c/l.b)+sqr(-l.c/l.b),x1,x2);
        p1.x=x1;
        p1.y=p2.y=-l.c/l.b;
        p2.x=x2;
    }
    else if(l.b==0)
    {
        jyyecfc(1,c.d,c.e+c.c*(-l.c/l.a)+sqr(-l.c/l.a),x1,x2);
        p1.x=p2.x=-l.c/l.a;
        p1.y=x1;
        p2.y=x2;
    }
    else
    {
        jyyecfc(1+sqr(l.a/l.b),c.c+l.a*l.c*2/l.b/l.b-l.a*c.d/l.b,c.e+sqr(l.c/l.b)-l.c*c.d/l.b,x1,x2);
        p1.x=x1;
        p1.y=-l.a*x1/l.b-l.c/l.b;
        p2.x=x2;
        p2.y=-l.a*x2/l.b-l.c/l.b;
    }
    return x;
}
inline int circleCutCircle(circle c1,circle c2,point &p1,point &p2)//将两圆交点转换为直线与圆交点求解，返回值表示交点个数
{
    line l;
    l.a=c1.c-c2.c;
    l.b=c1.d-c2.d;
    l.c=c1.e-c2.e;
    return lineCutCircle(l,c2,p1,p2);
}
inline bool isok(double x)//二分中的验证函数
{
    c1.r=x;
    c2.r=getDis(c1.p,c2.p)+t2-x;
    c3.r=getDis(c1.p,c3.p)+t1-x;
    if(x<-eps||c2.r<-eps||c3.r<-eps)return 0;
    change(c1);
    change(c2);
    change(c3);
    int o1=circleAndCircle(c1,c2),o2=circleAndCircle(c1,c3),o3=circleAndCircle(c2,c3);
    if(o1==0||o2==0||o3==0)return 0;
    if(o1>2||o2>2||o3>2)return 1;
    point a,b,c,d,e,f;
    o1=circleCutCircle(c1,c2,a,b);
    o2=circleCutCircle(c1,c3,c,d);
    o3=circleCutCircle(c2,c3,e,f);
    if(pointAndCircle(a,c3)||o1==2&&pointAndCircle(b,c3))return 1;
    if(pointAndCircle(c,c2)||o2==2&&pointAndCircle(d,c2))return 1;
    if(pointAndCircle(e,c1)||o3==2&&pointAndCircle(f,c1))return 1;
    return 0;
}
int main()
{
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&t1,&t2,&c1.p.x,&c1.p.y,&c2.p.x,&c2.p.y,&c3.p.x,&c3.p.y);
    if(getDis(c1.p,c3.p)+getDis(c3.p,c2.p)-getDis(c1.p,c2.p)-t2<=eps)//分类讨论Bob一路陪着Alan的情况
        printf("%.10lf",min(getDis(c1.p,c3.p)+getDis(c3.p,c2.p)+t1,getDis(c1.p,c2.p)+t2));
    else
    {
        l=0;
        r=min(getDis(c1.p,c3.p)+getDis(c3.p,c2.p)+t1,getDis(c1.p,c2.p)+t2);
        while(r-l>eps)
        {
            mid=(l+r)/2;
            if(isok(mid))l=mid;
            else r=mid;
        }
        printf("%.10lf",mid);
    }
}
```


---

## 作者：panjoel (赞：4)

可以证明出最优的分离点肯定是在p0,p1,p2组成的三角形之间。

因此可以求出p0出发的角度，一旦角度确定，能走的最远路程可以通过二分求得。

同时发现当角度左右偏离，那么都只会有利于某一方，所以三分角度，二分距离。

角度可以三分p1,p2上的点。

判断一下两个人能否一起到shop然后回家，如果不能：

两个人一定在三角形内部某一点分开，假设沿着直线走，可以将问题简化。

三分从电影院出来时候的角度，在对应的直线上二分出一个分离点即可。

三分角度的方法：在shop和home两个点之间找一个点p，链接p和电影院，在这个线段上面二分出分离点。

### **注意：精度。**

## Code:

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
#define sqr(x) ((x)*(x))
#define eps 1e-6
 
struct POINT {
    double x, y;
    POINT() {}
    POINT(double _x, double _y): x(_x), y(_y) {}
} c, s, h;
double t1, t2;
 
double dist(POINT &x, POINT &y) {
    return sqrt(sqr(x.x-y.x) + sqr(x.y-y.y));
}
double calc(double m) {
    POINT a = POINT(s.x*(1-m) + h.x*m, s.y*(1-m) + h.y*m);
    POINT b;
    double ac = dist(a, c);
    double ah = dist(a, h);
    double as = dist(s, a);
    if (ac + ah <= t2 && ac + as <= t1) {
        return min(t2-ah, t1-as);
    }
    double l = 0, r = 1, mid, la, lb, lc;
    for (int i=0; i<300; i++) {
        mid = (l + r)/2.0;
        b = POINT(c.x*(1-mid) + a.x*mid, c.y*(1-mid) + a.y*mid);
        la = dist(b, c);
        lb = dist(b, h);
        lc = dist(b, s);
        if (la+lb<=t2 && la+lc<=t1) l = mid;
        else r = mid;
    }
    b = POINT(c.x*(1-l) + a.x*l, c.y*(1-l) + a.y*l);
    return dist(b, c);
}
int main() {
 
    cin >>t1>>t2>>c.x>>c.y>>h.x >> h.y >> s.x>> s.y;
    double la, lb, lc;
    la = dist(c, s);
    lb = dist(c, h);
    lc = dist(s, h);
 
    if (lb + t2 >= la + lc) {
        printf("%.10lf\n", min(lb+t2, la+lc+t1));
        return 0;
    }
    t1 += la + 1e-10;
    t2 += lb + 1e-10;
 
    double l = 0, r = 1, lm, rm, ans = 0, v1, v2;
    for (int i=0; i<300; i++) {
        lm = (2*l + r)/3.0, rm = (2*r + l)/3.0;
        v1 = calc(lm), v2 = calc(rm);
        ans = max(ans, max(v1, v2));
        if (v1 < v2) l = lm;
        else r = rm;
    }
 
    printf("%.10lf\n", ans);
 
    return 0;
}
```


---

## 作者：封禁用户 (赞：2)

这题首先分3种情况

一.Bob陪Alan到商店

二.不陪到商店，但陪的时候不绕弯路，只走直线

三.不陪到商店，陪的时候绕弯路

经过分析

可以发现分离开其实是不划算的。

所以一最优，但有些时候走不到商店

这时我们可以断定他们是在一个点分离的（废话）

分离后要走直线，为分离前的Discuss节省时间

二可以理解

但三是为什么？

因为如果在某一点是最佳分离点（在这个点分离，两个人走的路都可以符合条件，不会很长）

但是直着走过去再走回家，发现还有一些时间怎么办？

那就在路上（甜蜜的时光）绕点弯路。

画画图就知道了。

最佳分离点一定在商店与家的线段上。（到商店和家的距离和最小）


现在我们来想一想二如何解决？

画个图：

然后你会想到一件事

那就是二的情况相似于三的情况，只不过二时走不到商店与家的线段上，故没有多余的时间给你绕圈圈

所以分离点一定在三角形内部。（易证）

现在
根据题意

要满足两个不等式：

e+t2>=a+b

d+f+t1>=a+c+f//即d+t1>=a+c

有三个未知数。a,b,c

但其实这3个未知数都和一个点有关，那就是Parting Point（简称P）

只需求坐标

但不能枚举（炸，1e-4）

注意到两个式子中都含a

不如假设a一定时

P往左时b减小，c增大

往右时c减小，b增大

那么在中间可能有一段

使不等式成立，

这不就是一个单坑（单峰）函数吗。

三分可以解决

先二分a，再三分角度。

但是，图有很多种画法，我的只是一种。

单是三分角度，都要人一命，更何况这是一道卡精度的题？

三分的角必须是劣弧，优弧会炸

要开long double,还只能用cin//至今不知long double 如何scanf

别忘了你还要计算第三种......

然后就是无限WA的命。。。。。。


然后一种逆天的思路出现了，它拂去了这道题计算几何的气息，

收敛了WA大魔王嚣张的气焰，还让我们有能力一句话计算完三。

最佳分离点一定在商店与家的线段上。

分离点一定在三角形内部。

有上述两个条件，那么想一想，我们三分角度，得到一条直线，如果这个直线上有最优解，那么他一定与商店与家的线段相交！

三分商店与家的线段上的一点D，就相当于三分角度

D与电影院链接，然后一句话特判完三的情况

然后再二分D与电影院的线段上的一点。

二分和三分一个点，除了分长度，还可以分比例


---

## 作者：kczno1 (赞：1)

首先分类讨论相同路径是否经过$c$。  
如果经过，那么$A,B$接下来一定都走向$b$，
所以特判一下就好了。  
如果不经过，那么一定是$A,B$一起走到一个点$p$，即$A$走a->p->c->b，$B$走a->p->b。  
二分$|ap|$，可以发现问题转化为判断三个圆有无交点。  
首先判断是否两两有交，然后枚举任意两个圆，判断是否相互包含或交点在第三个圆内。  
我写的似乎误差很大啊，改成$long$ $double$且$eps=1e-12$才过。
```cpp
//by kcz 1552920354@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;

template <typename T> void chmin(T &x,const T &y)
{
	if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
	if(x<y)x=y;
}
typedef long long ll;
typedef pair<int,int> pii;
typedef long double Lf;
typedef pair<Lf,Lf> point;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define pb push_back
#define mp make_pair
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'-');
    if(c=='-')
    {
        int x=gc-'0';
        while(gc>='0')x=x*10+c-'0';
        return -x;
    }
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
#undef gc
const Lf eps=1e-12;
const Lf I=sqrt(-1);
const point O=mp(0,0);
int cmp(const Lf &x)
{
	return x<-eps?-1:x>eps;
}
void read(point &p)
{
	cin>>p.first>>p.second;
}
point operator -(const point &p1,const point &p2)
{
	return mp(p1.first-p2.first,p1.second-p2.second);
}
void operator -=(point &p1,const point &p2)
{
	p1.first-=p2.first;p1.second-=p2.second;
}
Lf sqr(const Lf &x)
{
	return x*x;
}
Lf dis2(point p1,point p2=O)
{
	return sqr(p1.first-p2.first)+sqr(p1.second-p2.second);
}
Lf dis(point p1,point p2=O)
{
	return sqrt(sqr(p1.first-p2.first)+sqr(p1.second-p2.second));
}
point a,b,c;
Lf t1,t2;
void jie(Lf &x1,Lf &x2,Lf a,Lf b,Lf c)
{
//	if(cmp(b*b-4*a*c)<0)
//			puts("-1");
	Lf s=-b/(2*a),d=cmp(b*b-4*a*c)<=0?0:sqrt(b*b-4*a*c)/(2*a);
	x1=s-d;x2=s+d;
}
bool ok(point B,Lf l1,point C,Lf l2,Lf l)
{
	if(cmp(l1-dis(B)-l)>=0)return 1;
	if(cmp(l-dis(B)-l1)>=0)return 1;
	Lf a=2*B.first,b=2*B.second,c=sqr(l1)-sqr(l)-sqr(B.first)-sqr(B.second);
	Lf x1,x2,y1,y2;
	if(!cmp(b))
	{
//		if(!cmp(a))
//			puts("-1");
		x1=x2=-c/a;
		if(cmp(sqr(l)-sqr(x1))<=0)
		{
			y1=y2=0;
		}
		else
		{
			y1=sqrt(sqr(l)-sqr(x1));
			y2=-y1;
		}
	}
	else
	{
		a=-a/b;c=-c/b;
		jie(x1,x2,1+sqr(a),2*a*c,sqr(c)-sqr(l));
		y1=a*x1+c;y2=a*x2+c;
	}
/*	if(cmp(dis(C,mp(x1,y1))-l2)<=0)
		printf("%lf %lf\n",x1,y1);
	if(cmp(dis(C,mp(x2,y2))-l2)<=0)
		printf("%lf %lf\n",x2,y2);*/
	return cmp(dis(C,mp(x1,y1))-l2)<=0||cmp(dis(C,mp(x2,y2))-l2)<=0;
}
bool ok(const Lf &l)
{
	Lf l2=t2-l,l1=t1-l;
	if(cmp(sqr(l1+l2)-dis2(b,c))<0)return 0;
	return ok(b,l1,c,l2,l)||ok(c,l2,b,l1,l)||ok(b-c,l1,O-c,l,l2);
}

int main()
{
	freopen("1.in","r",stdin);//freopen("1.out","r",stdin);
	cin>>t2>>t1;
	read(a);read(b);read(c);
	b-=a;c-=a;
	t1+=dis(b);t2+=dis(c);
//	printf("%lf %lf %lf\n",dis(c),dis(b,c),t1);
	if(cmp(dis(c)+dis(b,c)-t1)<=0) 
	{
		printf("%lf\n",(double)min(t2+dis(b,c),t1));
		return 0;
	}
	Lf l=0,r=min(t1,t2);
	rep(o,1,40)
	{
		Lf mid=(l+r)/2;
		if(ok(mid))l=mid;
		else r=mid;
	}
//	printf("%d\n",ok(l));
	printf("%lf\n",(double)l);
}
```

---

## 作者：Chen_Johnny (赞：0)

# CodeForces 8D Two Friends
一言难尽，又恶心又好，这种题考的是数学……

不过这篇题解讲的很详细，希望大家能看完，内涵全推导以及思考过程以及纯数学知识！
## 1. 题目分析
这道题的题目很长，但是总结出来其实就三句话：

1. 如图，有三个点，$A,B,C$。
2. 随便找一个点 $K$ 使得：
$\begin{cases}
    AC + t_1 \leqslant AK + KC \\
    AB + t_2 \leqslant AK + KB
\end{cases}$
3. 求 $AP$ 的长度的最大值。
![](https://cdn.luogu.com.cn/upload/image_hosting/3gncjdza.png?x-oss-process=image/resize,m_lfit,h_500,w_1225)
## 2. 思路
### 2.1 二分答案
首先，我们发现这个 $AK$ 的长度不仅是答案，而且是整个题目不可或缺的一个数据，那么我们来想一想。不知道长度🤔，枚举！

又我们发现，其实这个 $AK$ 的长度有可行性上的单调性，既然如此，我们二分答案。
### 2.2 几何！
我们得到了 $AK$ 的长度，那么就可以开始画圆了。以 $A$ 为圆心 $AK$ 为半径的圆（粉色的圆）。不难发现，我们回到刚开始的式子：

$\begin{cases}
    AC + t_1 \leqslant AK + KC \\
    AB + t_2 \leqslant AK + KB
\end{cases}\Rightarrow\begin{cases}
    AC + t_1 - AK \leqslant KC \\
    AB + t_2 - AK \leqslant KB
\end{cases}$

很明显，$AC, AB, t_1, t_2, AK$ 均为已知，所以再以 $B, C$ 为圆心，$AB + t_2 - AK, AC + t_1 - AK$ 作圆（分别为绿色和蓝色的圆）。

![](https://cdn.luogu.com.cn/upload/image_hosting/q04nrwf0.png?x-oss-process=image/resize,m_lfit,h_500,w_1225)
因此，我们发现当且仅当满足三个圆有公共区域，结论成立。不难发现，其实就是两个圆的交点在第三个园内。那么这个我们发现其实就是一个和圆的幂有关的数学问题。
### 1. 求交点的坐标
首先，设交点的坐标为 $x, y$，$C,B$ 坐标为 $(x_1,y_1),(x_2,y_2)$，蓝圆和绿圆的半径分别为 $r_1,r_2$。

由平面直角坐标系的距离公式：$\begin {cases} 
(x-x_1)^2 + (y - y_1)^2 = r_1^2\\
(x - x_2)^2 + (y - y_2)^2 = r_2^2
\end{cases}$

两式相减得：
$$x_1^2 - x_2^2 + y_1^2 - y_2^2 + 2x (x_2 - x_1) + 2y (y_2 - y_1) = r_1^2 - r_2^2$$

为了演示方便，设 $$A = 2(x_2 - x_1), B = 2(y_2 - y_1), C = x_2^2 - x_1^2 + y_2^2 - y_1^2$$。

则：
$$y = \frac {C - Ax}{B}$$

代入原式得：
$$(x - x_1)^2 + (\frac {C - Ax} {B} - y_1)^2 = r_1^2$$
计算得：
$$(A^2 + B^2)x^2 - 2(B^2x_1+2AC-2ABy_1) + (x_1^2B^2 + C^2 - 2BCy_1 + y_1^2B^2 + r_1^2B^2) = 0$$
最后，我们用 $\triangle$ 来判断方程的解并求解$(x,y)$（用一元二次方程的求根公式)。
### 2. 求是否在园内
只需要判断 $(x,y)$ 与 $A$ 点的距离是不是不比 $AK$ 大就行了。
## 代码
这道题代码很复杂，但其实很简单，就是以上做的几步，我这里给大家一个警告：

浮点数运算不算精度误差会爆零！注意用 ```eps = 1e-10``` 来进行精度误差的调整！

---

