# Fifa and Fafa

## 题目描述

Fifa and Fafa are sharing a flat. Fifa loves video games and wants to download a new soccer game. Unfortunately, Fafa heavily uses the internet which consumes the quota. Fifa can access the internet through his Wi-Fi access point. This access point can be accessed within a range of $ r $ meters (this range can be chosen by Fifa) from its position. Fifa must put the access point inside the flat which has a circular shape of radius $ R $ . Fifa wants to minimize the area that is not covered by the access point inside the flat without letting Fafa or anyone outside the flat to get access to the internet.

The world is represented as an infinite 2D plane. The flat is centered at $ (x_{1},y_{1}) $ and has radius $ R $ and Fafa's laptop is located at $ (x_{2},y_{2}) $ , not necessarily inside the flat. Find the position and the radius chosen by Fifa for his access point which minimizes the uncovered area.

## 样例 #1

### 输入

```
5 3 3 1 1
```

### 输出

```
3.7677669529663684 3.7677669529663684 3.914213562373095
```

## 样例 #2

### 输入

```
10 5 5 5 15
```

### 输出

```
5.0 5.0 10.0
```

# 题解

## 作者：到底几只鱼呢 (赞：4)

## 计算几何-圆+相似三角形

![](https://cdn.luogu.com.cn/upload/image_hosting/0czebkso.png)

### solution:

题目要求不包含给定点的最大圆，我们可以想到这个圆的最大直径即为 $R+ $圆心到给定点的距离，如上图所示。

至此，问题中的最大半径问题得解。

接下来考虑如何解决新圆的圆心坐标，如下图所示，当给定点在圆心内部时容易构造一种相似关系，从而圆心得解。

![](https://cdn.luogu.com.cn/upload/image_hosting/62dfg24h.png)

设圆心坐标为 $(xx,yy)$ ,给定点的坐标为 $(x2,y2)$ ,新圆的圆心坐标为 $(x,y)$ ;

对于给定点在圆外的情况，原来的圆即为答案，判断圆心与给定点间的距离是否大于等于 $R$ 即可；

$len_{AB}=tmp1$ , $len_{BC}=tmp2$ 

由相似关系：

$$ \frac{tmp1}{tmp2}=\frac{x-x2}{xx-x2}=\frac{y-y2}{yy-y2}$$

解方程可得：

$$x=\frac{tmp1}{tmp2} * (xx-x2)+x2$$

$$y=\frac{tmp1}{tmp2} * (yy-y2)+y2$$

### Attention:

注意特判 $tmp2=0$ 的情况（分母不为 $0$ ），这种情况就是给定点与圆心重合，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ef1cc5uv.png)

圆心即为 $(xx+R/2,yy)$ ,半径即为 $R/2$ ，特判即可。

Code：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdlib>
using namespace std;

double R,xx,yy,x2,y2;
double r,x,y;

double dist(double a,double b,double c,double d) {
	return sqrt((a-c)*(a-c)+(b-d)*(b-d));
}

int main() {
	scanf("%lf%lf%lf%lf%lf",&R,&xx,&yy,&x2,&y2);
	if(dist(x2,y2,xx,yy)>=R) {
		printf("%.16lf %.16lf %.16lf",xx,yy,R);
		return 0;
	}
	else {
		double tmp1=(dist(x2,y2,xx,yy)+R)/2;
		double tmp2=dist(x2,y2,xx,yy);
		if(tmp2==0) {
			printf("%lf %lf %lf",xx+R/2,yy,R/2);
			return 0;
		}
		printf("%.16lf %.16lf ",(xx-x2)*tmp1/tmp2+x2,(yy-y2)*tmp1/tmp2+y2);
		printf("%.16lf",tmp1);
	}
	return 0;
}
```


---

## 作者：Wf_yjqd (赞：3)

好水一道几何题啊。。比赛祭特判，

具体来说，特判一个点是否在圆内。

------------

如何求特殊排除的点 $P$ 到圆的最大距离呢？

显然，连一下圆点 $O$ 和 $P$，延长好了。

证明的话，连一条辅助线，三角形两边之和大于第三边就行了。

它的距离 $R_1$ 就是 $OP+$ 圆的半径 $r$。

则答案的半径 $R$ 为 $\frac{R_1}{2}$。

然后，我们考虑求答案的圆点 $O_1$。

$O_1O$ 的长度是一定的,即 $R-OP$。

接下来，考虑对顶角相等，过 $P$ 做 $PX$ 垂直过 $O$ 的一条直线 $l$ 于 $X$，过 $O_1$ 做 $O_1Y$ 垂直 $l$ 于 $Y$，易证：$\Delta XPO\backsim\Delta YO_1O(AA)$。

因此，有结论 $YO_1=XP\times\frac{O_1O}{PO}$，$YO=XO\times\frac{O_1O}{PO}$。

然后分类讨论一下 $O$ 和 $P$ 的位置关系就结束了。

记得特判 $P$ 在圆外的情况。

------------

这题代码也不大有人需要看吧。。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
db r,x,y,xx,yy,rr,R,pr,ansx,ansy;
inline db sqr(db x){
    return x*x;
}
int main(){
    scanf("%lf%lf%lf%lf%lf",&r,&x,&y,&xx,&yy);
    rr=sqrtl(sqr(x-xx)+sqr(y-yy));
    if(rr+0.000001>=r){
        printf("%.8lf %.8lf %.8lf",x,y,r);
        return 0;
    }
    R=(rr+r)/2.0;
    pr=R-rr;
    if(rr<=0.000001){
        ansx=x;
        ansy=y-R;
    }
    else if(xx>=x&&yy>=y){
        ansx=x-pr/rr*(xx-x);
        ansy=y-pr/rr*(yy-y);
        //右上
    }
    else if(xx<=x&&yy>=y){
        ansx=x+pr/rr*(x-xx);
        ansy=y-pr/rr*(yy-y);
        //左上
    }
    else if(xx>=x&&yy<=y){
        ansx=x-pr/rr*(xx-x);
        ansy=y+pr/rr*(y-yy);
        //右下
    }
    else if(xx<=x&&yy<=y){
        ansx=x-pr/rr*(xx-x);
        ansy=y-pr/rr*(yy-y);
        //左下
    }
    printf("%.8lf %.8lf %.8lf",ansx,ansy,R);
	return 0;
}
```


---

## 作者：DPair (赞：0)

## 【前言】
计算几何的好题，初中知识就够了。

## 【题意】
这道题题意大概是酱紫的：

给你一个圆的圆心坐标和半径，以及另一个点的坐标，要在大圆中截一个完全在大圆内且不包含另一点的**最大**圆。

求该圆的圆心以及半径。


------------

不好理解？看一看样例......

如图，圆$C$即为所求圆：

![](https://cdn.luogu.com.cn/upload/pic/61922.png)

然后就解释了样例......

## 【思路】
知道了题意，怎么去想呢？

### 【性质1】
首先发现，由于误差为$10^{-6}$，所以可以使所求圆过原本不该过的点（图中点$B$），可见新圆应该要过点$B$、并与大圆相切（切点设为$D$）才可能取最大。

### 【性质2】
如果$BD$，不为所求圆直径，那么所求圆一定有在大圆外的部分（自己理解一下，不给出证明）。因此，$BD$为所求圆直径。

### 【性质3】
$$|AB| + |AD| \geq |BD|$$
所以$|BD|_{max}=|AB|+|AD|$

此时$A,B,D$三点共线，且圆面积最大。

然后就做出来了，先求大圆圆心$A$到$B$距离，看是否在圆内，然后用相似求出点$D$坐标（不赘述），最后求两点中点就是圆心。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;

double r, x, y, xx, yy;

int main()
{
    scanf("%lf%lf%lf%lf%lf", &r, &x, &y, &xx, &yy);
    double dis = sqrt((x - xx) * (x - xx) +  (y - yy) * (y - yy));
    if(dis == 0.0)
    {
        printf("%.16lf %.16lf %.16lf", x + (r / 2), y, r / 2);
        return 0;
    }
    if(dis >= r)
    {
        printf("%.1lf %.1lf %.1lf", x, y, r);
        return 0;
    }
    double x1, y1, tmp = (r / dis);
    x1 = (x - xx) * tmp + x;
    y1 = (y - yy) * tmp + y;
    dis = sqrt((x1 - xx) * (x1 - xx) +  (y1 - yy) * (y1 - yy));
    printf("%.16lf %.16lf %.16lf", (x1 + xx) / 2, (y1 + yy) / 2, dis / 2);
}
```

---

