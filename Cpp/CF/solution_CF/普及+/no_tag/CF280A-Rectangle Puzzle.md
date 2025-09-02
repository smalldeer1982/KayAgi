# Rectangle Puzzle

## 题目描述

You are given two rectangles on a plane. The centers of both rectangles are located in the origin of coordinates (meaning the center of the rectangle's symmetry). The first rectangle's sides are parallel to the coordinate axes: the length of the side that is parallel to the $ Ox $ axis, equals $ w $ , the length of the side that is parallel to the $ Oy $ axis, equals $ h $ . The second rectangle can be obtained by rotating the first rectangle relative to the origin of coordinates by angle $ α $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF280A/052b43ecd665cd6e4ffd3e118c46f92dcd4eb612.png)Your task is to find the area of the region which belongs to both given rectangles. This region is shaded in the picture.

## 说明/提示

The second sample has been drawn on the picture above.

## 样例 #1

### 输入

```
1 1 45
```

### 输出

```
0.828427125
```

## 样例 #2

### 输入

```
6 4 30
```

### 输出

```
19.668384925
```

# 题解

## 作者：wanggk (赞：6)

刚学计算几何，方法偏暴力。

## 前置知识

### 1.向量逆时针旋转 $\theta$
设原向量为 $(x,y)$。则旋转后的向量为 $(x\cos\theta - y\sin\theta,x\sin\theta+y\cos\theta)$

解释：可以把 $(x,y)$ 分解成 $(x,0)$ 和 $(y,0)$ 分别旋转。

### 2.叉积求三角形面积

$$S=\frac{1}{2}\left|\overrightarrow{AB} \times \overrightarrow{AC}\right|$$

### 3.判断线段相交
每条线段的两端都跨过另一条线段。

即判断线段 $AB$ 和 $CD$ 是否满足 $\overrightarrow{AB} \times \overrightarrow{AC}$ 与 $\overrightarrow{AB} \times \overrightarrow{AD}$ 正负相反，且 $\overrightarrow{CD} \times \overrightarrow{CA}$ 与 $\overrightarrow{CD} \times \overrightarrow{CB}$ 正负也相反。

## 题解
首先是一些处理。

- 如果 $w<h$，将两边交换。
- 如果旋转角大于 $180$，先减去 $180$。
- 减完后如果为 $0$ ，直接输出矩形面积。
- 否则，如果大于 $90$ ，用 $180$ 减去旋转角。

接着将 $\overrightarrow{OA},\overrightarrow{OB},\overrightarrow{OC},\overrightarrow{OD}$ 分别旋转，得到 $EFGH$ 的顶点坐标。

此时会出现两种情况。
### 情况 1
**当线段 $AB$ 和 $HE$ 不相交时**，两个矩形有 $4$ 个交点，如图。
![](https://cdn.luogu.com.cn/upload/image_hosting/8w74f5lj.png)

此时只需要求出交点 $I_1$ 和 $I_2$，求出平行四边形的面积。

### 情况 2

**当线段 $AB$ 和 $HE$ 相交时**，两个矩形有 $8$ 个交点，如图。
![](https://cdn.luogu.com.cn/upload/image_hosting/ytg1d1yj.png)

分别记作 $I_1$ 至 $I_8$，重叠面积就是这 $8$ 个点围成的多边形面积。

$$S=\frac{1}{2}(\left|\overrightarrow{OI_1} \times \overrightarrow{OI_2}\right|+\left|\overrightarrow{OI_2} \times \overrightarrow{OI_3}+\right|+...+\left||\overrightarrow{OI_7} \times \overrightarrow{OI_8}\right|+\left||\overrightarrow{OI_8} \times \overrightarrow{OI_1}\right|)$$

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long double eps=1e-8;
const long double PI=acos(-1.0);

long double ans;
long double w,h,a;

int sgn(double x){ return (fabs(x)<eps)?0:(x<0?-1:1); }
struct Point{
    long double x,y;
    Point(long double x=0.0,long double y=0.0):x(x),y(y){}
};
typedef Point Vector;
//向量四则运算
Vector operator + (Vector A,Vector B){ return Vector(A.x+B.x,A.y+B.y); }
Vector operator - (Vector A,Vector B){ return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (Vector A,long double p){ return Vector(A.x*p,A.y*p); }
Vector operator / (Vector A,long double p){ return Vector(A.x/p,A.y/p); }

//cross为叉积，rotate为向量旋转（rad为弧度制表示），bool型函数判段线段是否相交
long double cross(Vector A,Vector B){ return A.x*B.y-A.y*B.x; }
Vector rotate(Vector A,long double rad){
	return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
bool Properintersection(Point A,Point B,Point P,Point Q){
	return sgn(cross(B-A,P-A))*sgn(cross(B-A,Q-A))<0
		 &&sgn(cross(Q-P,A-P))*sgn(cross(Q-P,B-P))<0;
}

//两条直线求交点，用P+t*v表示一条直线（P为一个点，v为表示直线方向的向量，t为实数）
Point intersection(Point P,Vector v,Point Q,Vector w)
{
    Vector u=P-Q;
    long double t=cross(w,u)/cross(v,w);
    return P+v*t;
}
//将两个坐标表示的直线，转化为P+t*v的表示，扔进intersection函数。
Point pre_itsc(Point X,Point Y,Point M,Point N){
	return intersection(X,Y-X,M,N-M);
}

signed main()
{
	cin>>w>>h>>a;
    if(w<h) swap(w,h);//不加WA on 13

	if(a>=180.0) a-=180.0;
	if(a==0){
		cout<<fixed<<setprecision(8)<<w*h<<endl;
		return 0;
	}
	if(a>90) a=180-a;//这句不加WA on 6
	a=a/180.0*PI;//角度值转弧度制

	//求出旋转前后矩形顶点坐标
	Point A(-w/2.0,h/2.0),B(-w/2.0,-h/2.0),C(w/2.0,-h/2.0),D(w/2.0,h/2.0);
	Point E=rotate(A,a),F=rotate(B,a),G=rotate(C,a),H=rotate(D,a);

	//判断 EH 和 AB 是否相交，分类讨论（否则 WA on 7）
	if(Properintersection(E,H,A,B))
	{//对应情况 2
		Point I1=pre_itsc(A,D,E,H),I2=pre_itsc(A,B,E,H),
			  I3=pre_itsc(A,B,E,F),I4=pre_itsc(B,C,E,F),
			  I5=pre_itsc(B,C,F,G),I6=pre_itsc(C,D,F,G),
			  I7=pre_itsc(C,D,H,G),I8=pre_itsc(A,D,H,G);

		ans=fabs(cross(I1,I2))/2.0+fabs(cross(I2,I3))/2.0+
			fabs(cross(I3,I4))/2.0+fabs(cross(I4,I5))/2.0+
			fabs(cross(I5,I6))/2.0+fabs(cross(I6,I7))/2.0+
			fabs(cross(I7,I8))/2.0+fabs(cross(I8,I1))/2.0;
	}else{//对应题解情况 1
		Point I1=pre_itsc(E,H,B,C),I2=pre_itsc(F,G,B,C);
		ans=fabs(I1.x-I2.x)*h;
	}
	cout<<fixed<<setprecision(8)<<ans<<endl;
    return 0;
}
```

---

## 作者：lql1 (赞：3)

# 矩形 题解
爆算！
## Step.1 确定旋转后的顶点坐标
首先，已知矩形的长宽分别为 $w$,$h$，同时由于矩形中心点在 $x,y$ 轴交集的原点处，因此可以确定原顶点的坐标分别是：
$$
A \left(-\frac{w}{2},\frac{h}{2}\right)
$$
$$
B\left(-\frac{w}{2},-\frac{h}{2}\right)
$$
$$
C\left(\frac{w}{2},-\frac{h}{2}\right)
$$
$$
D\left(\frac{w}{2},\frac{h}{2}\right)
$$
               
![](https://cdn.luogu.com.cn/upload/image_hosting/md3ruijb.png)
如上图，四个顶点的坐标分别为：
$$
A\;(-4,3)\quad B\;(-4,-3)\quad C\;(4,-3)\quad D\;(4,3)
$$

若原矩形绕中心点旋转$\alpha^\circ$，假设原顶点坐标为$(x,y)$，旋转后的坐标为$(x',y')$，则$(x,y)$与$(x',y')$的关系如下：
$$
\begin{pmatrix} 
x' \\ y' 
\end{pmatrix} 
=\begin{pmatrix} 
x \cos \alpha - y \sin \alpha \\ 
x \sin \alpha + y \cos \alpha 
\end{pmatrix}
$$

![](https://cdn.luogu.com.cn/upload/image_hosting/fcz6ry4t.png)
如上图，矩形旋转后的顶点坐标分别为（取近似小数）：
$$
A\;(-4.95,-0.71)\quad B\;(-0.71,-4.95)\quad C\;(4.95,0.71)\quad D\;(0.71,4.95)
$$

## Step.2  求出旋转后矩形与原矩形的交点

![](https://cdn.luogu.com.cn/upload/image_hosting/k54e1bx9.png)
如图中，$F,G,H,I,J,K,L,M$ 均为矩形$ABCD$ 与矩形 $A'B'C'D'$ 的交点

考虑如何用直线方程来表示具体交点：

### 1. 使用直线方程来表示线段

假设现在求的线段是 $L_1$ 和 $L_2$，他们分别由两点 $P_1(x_1,y_1)$、$P_2(x_2,y_2)$和$Q_1(x_3,y_3)$、$Q_2(x_4,y_4)$;

线段 $L_1$ 可以表示为：$(x - x_1) \times (y_2 - y_1) = (y - y_1) \times (x_2 - x_1)$

类似地，线段 $L_2$ 可以表示为：$(x - x_3) \times (y_4 - y_3) = (y - y_3) \times (x_4 - x_3)$

这两条直线的交点满足：
$$
(x - x_1) \times (y_2 - y_1) = (y - y_1) \times (x_2 - x_1)\\
(x - x_3) \times (y_4 - y_3) = (y - y_3) \times (x_4 - x_3)
$$

### 2. 求解方程

可以通过代数方法解这两个方程，得到交点的坐标 $(x,y)$。

为了简化后面的公式，我们首先定义一些中间量：

$$
A_1 = y_2 - y_1\quad B_1 = x_1 - x_2\quad C_1 = A_1 \times x_1 + B_1 \times y_1\\
A_2 = y_4 - y_3\quad B_2 = x_3 - x_4\quad C_2 = A_2 \times x_3 + B_2 \times y_3
$$

则交点坐标$(x,y)$的计算公式为：
$$
D = A_1 \times B_2 - A_2 \times B_1\\
\quad\\
x = \frac{C_1 \times B_2 - C_2 \times B_1}{D}\\
\quad\\
y = \frac{A_1 \times C_2 - A_2 \times C_1}{D}
$$
注意，如果 $D = 0$，则说明两条直线平行或重合，此时无交点。

### 3.判断交点是否合法

虽然求出了直线的交点，但这个交点不一定在两个线段上。我们需要进一步判断交点是否在两个线段的范围内，即检查交点 $(x, y)$ 是否满足：
$$
\begin{cases}
& \min(x_1, x_2) & \le & x & \le & \max(x_1, x_2)\\
& \min(y_1, y_2) & \le & y & \le & \max(y_1, y_2)\\
& \min(x_3, x_4) & \le & x & \le & \max(x_3, x_4)\\
& \min(y_3, y_4) & \le & y & \le & \max(y_3, y_4)\\
\end{cases}
$$
如果以上条件都满足，则 $(x, y)$ 是这两条线段的交点。

## Step.3 排序交点

现在我们已经得到了所有的交点，但是为了防止我们按照默认顺序连接交点后形成凹多边形或自交多边形，我们需要按照每组交点的极角来排序。

由于两个矩形的几何中心点都在原点 $(0,0)$ ，因此我们定义极角基准点为点 $P_0(x_0,y_0)=(0,0)$。

接下来，我们对于每一个点 $P(x,y)$，都计算它与 $P_0$ 的极角（即与 $x$ 轴正方向的夹角），通过 $\text{math}$ 库的 $\text{atan2}$ 函数来计算，即：
$$
\theta=\text{atan2}(y-y_0,x-x_0)
$$
然后按照$\theta$的值从小到大排序后，按照逆时针连接即可

## Step.4 计算面积

多边形面积公式，又称**鞋带公式**
![](https://cdn.luogu.com.cn/upload/image_hosting/5v2f8lzc.png)

具体计算方式如图所示。

对于程序中一组已排序号的交点 $(P_1,P_2,\dots,P_n)$，面积公式为：
$$
\text{Area}=\frac{1}{2}\left|\sum_{i=1}^{n}(x_i\cdot y_{i+1}-y_i\cdot x_{i+1})\right|
$$
$\texttt{Tips:\;}$这里$P_{n+1}=P_1$，即图中的**首尾相连**

于是，我们就成功地用**解析几何**的方式完成了这道题！

最后附上$\text{cpp}$代码：

$\text{Code\;:}$
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define elif else if
#define sf scanf
#define pf printf 
#define eps 1e-9

const double pi=acos(-1.0);

double w,h,alpha,radian;
vector<pair<double,double>> point;

void change_xy(double& x,double& y,double radian) {
    double old_x=x;
    double old_y=y;
    x=cos(radian)*old_x-sin(radian)*old_y;
    y=sin(radian)*old_x+cos(radian)*old_y;
}

//是否在矩形内部
bool inside(double x,double y,double up,double down,double lft,double rgt) {
    return (x>=lft&&x<=rgt&&y>=down&&y<=up)?true:false;
}

//计算交点 
bool check_line(double x1,double y1,double x2,double y2,
                       double x3,double y3,double x4,double y4,
                       double& ix,double& iy) {
    double tmp=(y4-y3)*(x2-x1)-(x4-x3)*(y2-y1);
    if(fabs(tmp)<eps) return false; 
    double ua=((x4-x3)*(y1-y3)-(y4-y3)*(x1-x3))/tmp;
    double ub=((x2-x1)*(y1-y3)-(y2-y1)*(x1-x3))/tmp;
    if(ua<0||ua>1||ub<0||ub>1)return false;  // 交点不在这两条线段上
    ix=x1+ua*(x2-x1);
    iy=y1+ua*(y2-y1);
    return true;
}

double ccl_area(vector<pair<double,double>> point) {
	//鞋带公式 
    double area=0;
    int n=point.size();
    for(int i=0;i<n;i++) {
        int j=(i+1)%n;
        area+=point[i].first*point[j].second-point[j].first*point[i].second;
    }
    return fabs(area)/2.0;
}

//利用极角排序 atan2 
bool compare(const pair<double,double>& a,const pair<double,double>& b) {
    return atan2(a.second,a.first)<atan2(b.second,b.first);
}

int main() {
    cin>>w>>h>>alpha;
    radian=alpha*pi/180;
    vector<pair<double,double>> xy={
        {-w/2,h/2},
        {w/2,h/2},
        {w/2,-h/2},
        {-w/2,-h/2}
    };//初始 
    vector<pair<double,double>> changed;
    for(auto& it:xy) {
        double x=it.first;
        double y=it.second;
        change_xy(x,y,radian);
        changed.push_back({x,y});
}
    //原边界
    double up=max({xy[0].second,xy[1].second,xy[2].second,xy[3].second});
    double down=min({xy[0].second,xy[1].second,xy[2].second,xy[3].second});
    double lft=min({xy[0].first,xy[1].first,xy[2].first,xy[3].first});
    double rgt=max({xy[0].first,xy[1].first,xy[2].first,xy[3].first});
    for(auto& it:changed) {
        if(inside(it.first,it.second,up,down,lft,rgt)) {
            point.push_back(it);
        }
    }
    for(auto it:xy) {
        double x=it.first;
        double y=it.second;
        double changed_x=x*cos(-radian)-y*sin(-radian);
        double changed_y=x*sin(-radian)+y*cos(-radian);
        if(inside(changed_x,changed_y,up,down,lft,rgt)) {
            point.push_back(it);
        }
    }
    double ix,iy;
    for(int i=0;i<4;++i) {
        double x1=changed[i].first;
        double y1=changed[i].second;
        double x2=changed[(i+1)%4].first;
        double y2=changed[(i+1)%4].second;

        for(int j=0;j<4;++j) {
            double x3=xy[j].first;
            double y3=xy[j].second;
            double x4=xy[(j+1)%4].first;
            double y4=xy[(j+1)%4].second;

            if(check_line(x1,y1,x2,y2,x3,y3,x4,y4,ix,iy)) {
                point.push_back({ix,iy});
            }
        }
    }
    if(point.size()<3) {
        pf("%.4lf",0);
    } else {
        sort(point.begin(),point.end(),compare);
        pf("%.4lf",ccl_area(point));
    }
    return 0;
}
```

---

## 作者：yanhao40340 (赞：2)

蒟蒻的第一篇计算几何题解，有不对的地方敬请谅解 + 评论区指出。

## 题意

给定一个长为 $w$，宽为 $h$ 的长方形 $a$，绕其中心逆时针旋转 $\alpha$ 度得到长方形 $b$，求 $a$ 与 $b$ 的重叠面积 $S$。

数据范围：$1\le w,h\le 10^6, 0 \le \alpha \le 180$。

## 分析

当 $\alpha=0$ 或 $180$ 时，$S=wh$。

显然，逆时针旋转 $\alpha\left(\alpha>90\right)$ 度，等价于顺时针旋转 $180-\alpha$ 度。因为长方形是轴对称图形，所以顺时针旋转等价于逆时针旋转，即逆时针旋转 $\alpha\left(\alpha>90\right)$ 度等价于逆时针旋转 $180-\alpha$ 度。

那么现在我们只需要解决 $0< \alpha \le 90$ 的情况即可。

### I.旋转

更多相关证明和补充内容：[link](https://oi.wiki/math/linear-algebra/vector/)。

设向量 $s=(x,y)$，则其逆时针旋转 $\theta$ 度角得到的向量 $t=(x\cos\theta-y\sin\theta,y\cos\theta+x\sin\theta)$。

那么就可以用上述公式计算出长方形 $b$ 的四个顶点。代码如下：

```cpp
pdd rotate(pdd a,double w){
	return {a.x*cos(w)-a.y*sin(w),a.y*cos(w)+a.x*sin(w)};
}
```

### II.判断相交

更多相关证明和补充内容：[link](https://oi.wiki/geometry/2d/)。

自己多造几组数据可以发现，在 $0<\alpha\le 90$ 时，$a$ 和 $b$ 的交点只有两种可能，$4$ 个或 $8$ 个。当 $a$ 和 $b$ 只有 $4$ 个交点时，$AC$ 与 $EG$ 没有交点（如下图 $2$），而当 $a$ 和 $b$ 之间有 $8$ 个交点时， $AC$ 和 $EG$ 会相交于一点（如下图 $1$）。

那么我们只需要通过判断线段 $AC$ 和线段 $EG$ 是否相交就可以确定题目是属于哪一种情况了。

判断相交最常用的方法就是向量积，通过判断一条线段的两个端点是否在另一条线段的两侧来判断这两条线段是否相交。代码如下：

```cpp
bool collide(pdd a,pdd b,pdd c,pdd d){
	if (signbit((b-a)*(c-a))^signbit((b-a)*(d-a)))
		if (signbit((d-c)*(c-a))^signbit((d-c)*(c-b))) return true;
	return false;
}
```

注：`cmath` 库中的 `signbit` 函数可以判断一个浮点数是否为负数，是返回 `true`，否则返回 `false`。

### III.$a$ 与 $b$ 有 $8$ 个交点

![](https://cdn.luogu.com.cn/upload/image_hosting/3xq71vv7.png)

$$\texttt{图 }1$$

如图 $1$，$\begin{cases}S=AB\times AC-S_{\Delta FMN}-S_{\Delta EPQ}-S_{\Delta SGT}-S_{\Delta XHY}\\S_{\Delta FMN}=S_{\Delta SGT}\\S_{\Delta EPQ}=S_{\Delta XHY}\end{cases}$。

设 $F=(x1,y1)$，$E=(x2,y2)$，则 $S_{\Delta FMN}=\dfrac{1}{2}MN\times\left(\ y1-\dfrac{h}{2}\right)$，$S_{\Delta EPQ}=\dfrac{1}{2}PQ\times\left(\ -\dfrac{w}{2}-x2\right)$。

那么只需要求出 $MN$ 和 $PQ$ 的长度即可。要求出 $MN$ 和 $PQ$ 的长，我们可以暴力求出每一个点的坐标，然后相减即可。这样，求阴影面积就变成了求 $M,N,P,Q$ 四点的坐标，而这 $4$ 点都分别是两条已知线段的交点。

### IV.$a$ 与 $b$ 有 $4$ 个交点

![](https://cdn.luogu.com.cn/upload/image_hosting/hs95lzsw.png)

$$\texttt{图 }2$$

如图 $2$，$S=PQ\times AC=PQ\times h$。

所以只需要求出 $P,Q$ 两点的坐标即可。

### V.求交点坐标

更多相关证明和补充内容：[link](https://oi.wiki/geometry/2d/)。

综上，无论是 $a$ 和 $b$ 的交点数是 $4$ 个还是 $8$ 个，我们都可以将其化归为求两条线段交点的问题。求交点代码如下 ~~（不太会解释，反正是板子，背下来就行）~~：

```cpp
pdd point(pdd a,pdd b,pdd c,pdd d){
	return a+b*((d*(a-c))/(b*d));
}
```

## 代码

部分代码已经给出，完整代码见 [link](https://codeforces.com/contest/280/submission/201939464)。

---

## 作者：xukuan (赞：2)

计算几何的好题

思路很常规：直接做高法+正弦定理求高。

就是注意一些坑的点：

1.输入角可能>90度

2.C++<cmath>中sin等三角函数中传入的值采用弧度制

3.C++<cmath>中arcsin等函数写作asin
  
代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
using namespace std;

inline double sqr(double v){return v*v;}

double a,w,h;

int main(){
    cin>>w>>h>>a;
    double ans=w*h;
    if(a>90) a=180-a;//确保输入角小于90度
    a=a/180.0*acos(-1);//将a转化位弧度制
    if(w<h) swap(w,h);//确保w与h之间的大小关系
    double h1=w/2*sin(a)+h/2*cos(a)-h/2,
    h2=w/2*cos(a)+h/2*sin(a)-w/2,
    b=2*atan(h/w);
    //求出高的长度
    if(a<b){
        if(a>0) ans-=(sqr(h1)+sqr(h2))/(sin(a)*cos(a));//减去多算的面积
        printf("%.10lf\n",ans);
    }
    else printf("%.10lf\n",sqr(h)/sin(a));
    return 0;
}
```

---

## 作者：Eleveslaine (赞：0)

观前预警：本篇题解**方法极其暴力**，**代码较长**，不过基本只需要初中几何知识，~~因此很适合像我一样菜菜的不会向量叉积的初中生观看~~。

**题意：** 给定横向长为 $w$，纵向长为 $h$，中心为原点的矩形，将其绕原点逆时针旋转 $\alpha\degree(0 \le \alpha \le 180)$，求旋转前后重叠部分的面积。

初中简单计算几何。前置知识有：

- 一次函数；
- 海伦公式；
- 弧度制和（任意角）三角函数。

容易发现对于同一个 $\alpha,w=x,h=y$ 和 $w=y,h=x$ 的答案是一样的，而 $w\le h,w>h$ 的处理方式不同，所以不妨**设 $\boldsymbol{w \le h}$**，若不满足则交换 $w,h$。下文的讨论仅适用于 $w \le h$ 的情况。

为方便讨论，首先把 $\alpha$ 转成弧度。约定矩形的四个顶点 $A\left(\dfrac w2,\dfrac h2\right),B\left(-\dfrac w2,\dfrac h2\right),C\left(-\dfrac w2,-\dfrac h2\right),D\left(\dfrac w2,-\dfrac h2\right)$，矩形的四条边所在直线 $l_1=AD,l_2=BC,l_3=AB,l_4=CD$；旋转后顶点的对应点分别为 $A_1,B_1,C_1,D_1$，旋转后边 $l_i(1 \le i \le 4)$ 的对应直线为 $l_{i+4}$。

可以用（反）三角函数得到旋转后的点的坐标。具体地，设 $\beta = \angle xOA = \tan^{-1} \dfrac hw,r=\sqrt{\left(\dfrac w2\right)^2+\left(\dfrac h2\right)^2}$（即外接圆的半径），那么

$$
\begin{aligned}
A_1&\left(r\cos(\alpha+\beta),r\sin(\alpha+\beta)\right) \\
B_1&\left(r\cos(\pi-\beta+\alpha),r\sin(\pi-\beta+\alpha)\right) \\
C_1&\left(r\cos(\pi+\alpha+\beta),r\sin(\pi+\alpha+\beta)\right) \\
D_1&\left(r\cos(\alpha-\beta),r\sin(\alpha-\beta)\right).
\end{aligned}
$$

在这里贴一张[图](https://www.desmos.com/geometry/pnc8g1vcvj?lang=zh-CN)。点都是可拖动的。

有了这些坐标，就可以得出 $l_5,l_6,l_7,l_8$ 的解析式。我们知道这个重叠部分可能是八边形或平行四边形，下面我们分四种情况讨论。

1. 我们先看八边形的情况。当 $0 < \alpha < 2\beta$ 时，如[图](https://www.desmos.com/geometry/6nla2awzjs?lang=zh-CN)所示，可以求出点 $E,F,...,L$ 的坐标，进而把八边形拆成 $6$ 个三角形，用海伦公式求解。

2. 平行四边形的情况，当 $2\beta \le \alpha \le \pi-2\beta$ 时，如[图](https://www.desmos.com/geometry/a5sadc5l1c?lang=zh-CN)所示，可以求出点 $U,V,W,X$ 的坐标，进而把平行四边形拆成 $2$ 个三角形，用海伦公式求解。

3. 当 $\pi-2\beta < \alpha < \pi$ 时，还是一个八边形，如[图](https://www.desmos.com/geometry/8ai6eqvmej?lang=zh-CN)所示，同第一种情况。之所以把它与第一种情况分开，是因为过点 $E,F,...,L$ 的直线发生了变化，不能直接套用代码。 

4. 特判 $\alpha=0$ 或 $\alpha=\pi$ 的情况，答案为 $wh$。

**代码：** RMJ 又爆炸了，见 [Submission](https://codeforces.com/contest/280/submission/222160403)。

注：代码实现上，求过两点的直线解析式 `l = cross(A, B)`；  
求直线 $l$ 与直线 $y=v$ 的交点 `P = intersect(l, (lineY){v})`；  
求直线 $l$ 与直线 $x=v$ 的交点 `P = intersect(l, (lineX){v})`；  
用海伦公式求 $S_{\triangle ABC}$ `ans = S(A, B, C)`。

---

