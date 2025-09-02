# Barcelonian Distance

## 题目描述

In this problem we consider a very simplified model of Barcelona city.

Barcelona can be represented as a plane with streets of kind $ x = c $ and $ y = c $ for every integer $ c $ (that is, the rectangular grid). However, there is a detail which makes Barcelona different from Manhattan. There is an avenue called Avinguda Diagonal which can be represented as a the set of points $ (x, y) $ for which $ ax + by + c = 0 $ .

One can walk along streets, including the avenue. You are given two integer points $ A $ and $ B $ somewhere in Barcelona. Find the minimal possible distance one needs to travel to get to $ B $ from $ A $ .

## 说明/提示

The first example is shown on the left picture while the second example us shown on the right picture below. The avenue is shown with blue, the origin is shown with the black dot.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1032D/d9be16980f00189d5199b81c1601b819612b0d94.png)

## 样例 #1

### 输入

```
1 1 -3
0 3 3 0
```

### 输出

```
4.2426406871
```

## 样例 #2

### 输入

```
3 1 -9
0 3 3 -1
```

### 输出

```
6.1622776602
```

# 题解

## 作者：是个汉子 (赞：5)

算是自己切的第一道计算几何了，写篇题解记录一下。

### Solution

首先，我们发现，如果 $(x_1,y_1)$ 到 $(x_2,y_2)$ 是经过 $ax+by+c=0$ 的，那么一定是从 $x=x_1$ 或 $y=y_1$ 到 $x=x_2$ 或 $y=y_2$ ，所以我们可以枚举这四种路径和不经过 $ax+by+c=0$ 的路径，取最小值即可。

然后可以用初中学过的方法求出 $ax+by+c=0$ 和那四条直线的交点： $(x_3,y_3)=(x_1,\frac {-a\times x_1-c}b),(x_4,y_4)=(\frac {-b\times y_1-c}a,y_1),(x_5,y_5)=(x_2,\frac {-a\times x_2-c}b),(x_6,y_6)=(\frac {-b\times y_2-c}a,y_2)$ 

然后再用初中学过的勾股定理算出路径长

然后算就完了！~~奥力给~~

小细节：记得用 $fabs$ ，不然样例都过不去。

### 代码

```c++
#include<cmath>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<iostream>

using namespace std;
double a,b,c,x[10],y[10],ans;

int main(){
    ios::sync_with_stdio(false);
    cin>>a>>b>>c>>x[1]>>y[1]>>x[2]>>y[2];
    ans=fabs(x[1]-x[2])+fabs(y[1]-y[2]);
    x[3]=x[1];
    y[3]=(-a*x[1]-c)/b;
    x[4]=(-b*y[1]-c)/a;
    y[4]=y[1];
    x[5]=x[2];
    y[5]=(-a*x[2]-c)/b;
    x[6]=(-b*y[2]-c)/a;
    y[6]=y[2];
    for(int i=3;i<=4;i++)
        for(int j=5;j<=6;j++){
            ans=min(ans,fabs(x[1]-x[i])+fabs(y[1]-y[i])+
                    sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))+
                    fabs(x[2]-x[j])+fabs(y[2]-y[j]));
        }
    cout<<setprecision(12)<<ans<<endl;
    return 0;
}
```



---

## 作者：MoyunAllgorithm (赞：1)

为什么现在的题解代码都写得那么长。。。

**结论：路径必然属于以下五种：**

- 只走网格；

- 先横着走，上斜线，后竖着（如样例）；

- 先横着走，上斜线，后横着；

- 先竖着走，上斜线，后竖着；

- 先竖着走，上斜线，后横着。

**容易证明（感性理解）**，由勾股定理，必然不会经过多次斜线或提前离开斜线，这是不优的。

设

- $C$ 为 $A$ 同一横线上的斜线点；

- $D$ 为 $A$ 同一竖线上的斜线点；

- $E$ 为 $B$ 同一横线上的斜线点；

- $F$ 为 $B$ 同一竖线上的斜线点。

求出 $C$、$E$ 的横坐标和 $B$、$F$ 的纵坐标。以 $C$ 的横坐标为例，设 $A$ 的纵坐标为 $k$，有

$$Ax+Bk+C=0$$

解得

$$x=\dfrac{-Bk-C}{A}$$

另外三项同理。


之后暴力计算五种路径的长度，取最小值即可。

```cpp
#include <bits/stdc++.h>
#define DB double
using namespace std;
const int MAXN=1e5+5;
int A,B,C,xa,ya,xb,yb;
DB Dis(DB xi,DB yi,DB xj,DB yj)
{
	return sqrt((xi-xj)*(xi-xj)+(yi-yj)*(yi-yj));
}
int main()
{
	scanf("%d %d %d %d %d %d %d",&A,&B,&C,&xa,&ya,&xb,&yb);
	DB ans=1.0*abs(ya-yb)+abs(xa-xb);
	DB ay=((DB)1.0*-B*ya-C)/A; //C
	DB ax=((DB)1.0*-A*xa-C)/B; //D
	DB by=((DB)1.0*-B*yb-C)/A; //E
	DB bx=((DB)1.0*-A*xb-C)/B; //F
   //求出C,D,E,F点
	DB d1=1.0*abs((DB)ay-xa)+Dis(ay,ya,xb,bx)+abs((DB)bx-yb);
	DB d2=1.0*abs((DB)ay-xa)+Dis(ay,ya,by,yb)+abs((DB)by-xb);
	DB d3=1.0*abs((DB)ax-ya)+Dis(xa,ax,xb,bx)+abs((DB)bx-yb);
	DB d4=1.0*abs((DB)ax-ya)+Dis(xa,ax,by,yb)+abs((DB)by-xb);
	ans=min(ans,min(min(d1,d2),min(d3,d4)));
	printf("%.10lf\n",ans);
	return 0;
}
```

---

## 作者：WLR__jr (赞：1)

### 这题其实就是计算曼哈顿距离
~~也可以当作纯暴力数学计算~~

直接交代码，并不打算解释（写出来消耗了我一年的脑细胞）

```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
double dis(double a,double b,double c,double d)
{
    return sqrt((a-c)*(a-c)+(b-d)*(b-d));
}
int main()
{
    ll a,b,c,x_1,y_1,x_2,y_2;
    scanf("%lld%lld%lld",&a,&b,&c);
    scanf("%lld%lld%lld%lld",&x_1,&y_1,&x_2,&y_2);
    double ans,ans1,xx1,yy1,xx2,yy2;//曼哈顿距离
    ans=1.0*(abs(x_2-x_1)+abs(y_2-y_1));
    //x 1 y 1
    ans1=0;
    xx1=1.0*x_1;
    yy1=-1.0*(1.0*a*x_1+c)*(1.0/b);
    xx2=1.0*x_2;
    yy2=-1.0*(1.0*a*x_2+c)*(1.0/b);
    ans1+=fabs(yy1-y_1)+fabs(yy2-y_2);//fabs--小数的绝对值 
    ans1+=dis(xx1,yy1,xx2,yy2);
    ans=min(ans,ans1);
    //x 1 y 0
    ans1=0;
    xx1=1.0*x_1;
    yy1=-1.0*(1.0*a*x_1+c)*(1.0/b);
    xx2=-1.0*(1.0*b*y_2+c)*(1.0/a);
    yy2=1.0*y_2;
    ans1+=fabs(yy1-y_1)+fabs(xx2-x_2);
    ans1+=dis(xx1,yy1,xx2,yy2);
    ans=min(ans,ans1);
    //x 0 y 0
    ans1=0;
    xx1=-1.0*(1.0*b*y_1+c)*(1.0/a);
    yy1=1.0*y_1;
    xx2=-1.0*(1.0*b*y_2+c)*(1.0/a);
    yy2=1.0*y_2;
    ans1+=fabs(xx1-x_1)+fabs(xx2-x_2);
    ans1+=dis(xx1,yy1,xx2,yy2);
    ans=min(ans,ans1);
    //x 0 y 1
    ans1=0;
    xx1=-1.0*(1.0*b*y_1+c)*(1.0/a);
    yy1=1.0*y_1;
    xx2=1.0*x_2;
    yy2=-1.0*(1.0*a*x_2+c)*(1.0/b);
    ans1+=fabs(xx1-x_1)+fabs(yy2-y_2);
    ans1+=dis(xx1,yy1,xx2,yy2);
    ans=min(ans,ans1);
    printf("%.10f\n",ans);//运算4次，输出结果 
    return 0;//完结撒花 
}
```

---

## 作者：BLX32M_10 (赞：0)

## 题意

给定整点 $A$ 和点 $B$，以及一条直线（用 $ax+bx+c=0$ 表示），从 $A$ 走到 $B$，规定除在直线上行走之外只能走水平或垂直路径（**不一定要走到整点！**），求最小化的路径长度。

## 题解

不难发现本题的路径如果经过直线，将分为 $3$ 段：$A$ 到直线、直线上的线段和直线到 $B$。

易得最优的从直线到两点的线段一定是水平或者垂直的，于是我们求出该直线与 $A$、$B$ 各所在的水平和垂直线的交点并两两配对，取总路径的最小值（当然，最后别忘了与直接垂直走求最小值，并且要特判 $a=0$ 或 $b=0$ 的情况）。

![](https://cdn.luogu.com.cn/upload/image_hosting/y6xf9fub.png)

方法如图所示。经过比较，最短的路径就是 $A\rightarrow b\rightarrow$ 一段直线 $\rightarrow c\rightarrow B$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline double dis(double x1, double y1, double x2, double y2) //两点间距离
{
    return sqrt(0.0 + (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
inline double ldis(double x1, double y1, double x2, double y2) //垂直距离
{
	return abs(x1 - x2) + abs(y1 - y2);
}
signed main()
{
    int a, b, c, x1, y1, x2, y2;
    scanf("%lld %lld %lld %lld %lld %lld %lld", &a, &b, &c, &x1, &y1, &x2, &y2);
    if (a == 0 || b == 0) //特判
    {
        printf("%lld", abs(x1 - x2) + abs(y1 - y2));
        return 0;
    }
    double x11 = x1, y11 = y1, x12 = x1, y12 = y1;
    double x21 = x2, y21 = y2, x22 = x2, y22 = y2;
    y11 = 1.0 * (a * x1 + c) / (-b);
    x12 = 1.0 * (b * y1 + c) / (-a);
    y21 = 1.0 * (a * x2 + c) / (-b);
    x22 = 1.0 * (b * y2 + c) / (-a);
    printf("%.10lf", min(min(min(ldis(x1, y1, x11, y11) + dis(x11, y11, x21, y21) + ldis(x2, y2, x21, y21),
                      ldis(x1, y1, x11, y11) + dis(x11, y11, x22, y22) + ldis(x2, y2, x22, y22)),min(
                      ldis(x1, y1, x12, y12) + dis(x12, y12, x21, y21) + ldis(x2, y2, x21, y21),
                      ldis(x1, y1, x12, y12) + dis(x12, y12, x22, y22) + ldis(x2, y2, x22, y22))), ldis(x1, y1, x2, y2)));
    return 0;
}

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1032D)

&nbsp;

### 题目大意：
给定一个网格图，对于任意 $k$ 图中都有两条形如 $y=k$ 和 $x=a$ 的道路，同时还有一条形如 $ax+by+c=0$ 的道路。

现给定一个起点和一个终点，求从起点到终点需经过的最短路程。

&nbsp;

### 解题思路：
考虑朴素做法，发现对于两个在 $ax+by+c=0$ 这条线上的点，直接走斜线显然比按照网格线走要优。于是将行走过程分为五种情况：
- 沿 $y=x_S$ 走到直线上，随后沿斜线走到 $y=x_T$ 上，然后走到 $T$
- 沿 $y=x_S$ 走到直线上，随后沿斜线走到 $x=y_T$ 上，然后走到 $T$
- 沿 $x=y_S$ 走到直线上，随后沿斜线走到 $y=x_T$ 上，然后走到 $T$
- 沿 $x=y_S$ 走到直线上，随后沿斜线走到 $x=y_T$ 上，然后走到 $T$
- 沿网格图走到 $T$

取最小值输出即可。

代码如下：
```
int main(){
	scanf("%lf%lf%lf%lf%lf%lf%lf",&a,&b,&c,&fx,&fy,&tx,&ty);
	
	double ans=abs(tx-fx)+abs(ty-fy);
	
	double pos1=(0-b*fy-c)/a；
	double pos2=(0-b*ty-c)/a；
	
	ans=min(ans,abs(pos1-fx)+calc(pos1,fy,pos2,ty)+abs(pos2-tx));
	
	pos2=(0-a*tx-c)/b;
	ans=min(ans,abs(pos1-fx)+calc(pos1,fy,tx,pos2)+abs(pos2-ty));
	
	pos1=(0-a*fx-c)/b;
	ans=min(ans,abs(pos1-fy)+calc(fx,pos1,tx,pos2)+abs(pos2-ty));
	
	pos2=(0-b*ty-c)/a;
	ans=min(ans,abs(pos1-fy)+calc(fx,pos1,pos2,ty)+abs(pos2-tx));
	printf("%.7lf",ans);
	
    return 0；
}
```

---

## 作者：NastiY_iN_saNitY (赞：0)

## Solution 1

这是一道暴力分讨题。但是现有题解都没有比较详细的讲实现。

不妨令 $A$ 在 $B$ 左。但是这个时候 $A$ 在 $B$ 上还是下仍然不知道。我的实现是，如果 $B$ 在 $A$ 上，你可以把整个图关于 $y=y_A$ 对称一下，然后 $B$ 就在 $A$ 下面了。注意到这条直线也要变。

![](https://cdn.luogu.com.cn/upload/image_hosting/gbx0l757.png)


然后我们就可以画出这些情况：如果 $a=0$ 或者 $b=0$，那么答案显然还是曼哈顿距离（如左下两张图）。如果斜率 $k>0$，答案也是曼哈顿距离，因为这条直线方向都是反的我们不会用到。

我的实现没有特判这种情况，因为这个情况算出来的一定大于曼哈顿距离，所以取个 $\min$ 就好了。

第一排三种情况只需要用勾股定理算一下就行了。

但是这个题有的点还是有点卡精度的，这里有两个建议：

- `double` 变成 `long double`。
- 这个题用除法就行了，用乘法反而会掉精度。

### Implementation

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
struct line { double a, b, c; };
struct point { double x, y; }; point A, B;
double solvex(line l, double y) { return -(l.b * y / l.a + l.c / l.a); }
double solvey(line l, double x) { return -(l.a * x / l.b + l.c / l.b); }//计算交点
double manhattan(point A, point B) { return fabs(A.x - B.x) + fabs(A.y - B.y); }
double sq(double x) { return x * x; }
double dist(point A, point B) { return sqrtl(sq(A.x - B.x) + sq(A.y - B.y)); }
int printt(double x) { cout << fixed << setprecision(10) << min(x, manhattan(A, B)) << endl; return 0; } //取 min 实现
int solve() {
    line l; cin >> l.a >> l.b >> l.c;
    cin >> A.x >> A.y >> B.x >> B.y;
    if(l.a == 0 || l.b == 0) return printt(manhattan(A, B));
    if(A.x > B.x) swap(A, B);
    if(A.y < B.y) {
        B.y = 2 * A.y - B.y;
        l.c = l.c + 2 * A.y * l.b;
        l.b *= -1;
        //对称实现
    }
    if(A.x == B.x || A.y == B.y) {return printt(manhattan(A, B));}
    double dx = solvex(l, A.y), dy = solvey(l, A.x);
    if(dx >= A.x) {
        double res = 0, ddy = solvey(l, B.x);
        res += dx - A.x;
        if(ddy <= B.y) {
            double ddx = solvex(l, B.y);
            res += B.x - ddx;
            res += dist({dx, A.y}, {ddx, B.y});
            return printt(res);
        }
        res += ddy - B.y;
        res += dist({dx, A.y}, {B.x, ddy});
        return printt(res);
    } else {
        double res = 0, ddx = solvex(l, B.y);
        res += A.y - dy;
        if(ddx >= B.x) {
            double ddy = solvey(l, B.x);
            res += ddy - B.y;
            res += dist({A.x, dy}, {B.x, ddy});
            return printt(res);
        }
        res += fabs(ddx - B.x);
        res += dist({A.x, dy}, {ddx, B.y});
        return printt(res);
    }
    return 0;
}
signed main() { solve(); system("pause"); return 0; }
// Sample 11:
// -89307 44256 -726011368
// -1 16403 -8128 3
```

### Solution 2

暴力把 $6$ 个点跑出来之后连边最短路就行了，但是题解区已经有这种做法了，这里不再讲。

---

