# Plane of Tanks

## 题目描述

你正在玩坦克大战。游戏中的坦克试图摧毁别的坦克，但是你面临的任务不像 [那样](https://www.luogu.com.cn/problem/CF175D) 复杂。你只需要从地图的点 $A$ 把坦克开一条直线到点 $B$。不幸的是，在地图上有一些敌军坦克。我们可以把这些所有的坦克视作点。在一开始你的坦克在 $A$ 点，敌军坦克想要立即击毁它，但是它们的炮塔初始位置在其它的方向上。具体来说，对于每台坦克，我们知道它们的初始炮塔角度 $a_i(rad)$，表示炮塔方向和 $x$ 轴逆时针方向的夹角和它们的最大转速，用 $w_i(rad/s)$ 表示。任何时间点，如果一个敌方坦克的炮管对准了你的坦克，它会立即开火并且准确度达 $100\%$，也就是每炮必中。你的坦克的装甲可以抵挡 $k$ 次伤害。装填弹药耗时很长，所以你可以认为每台敌军坦克只会造成一次伤害。你的任务是计算出你的坦克的最低速度。无需考虑被击中会导致你坦克的速度降低或者坦克移位。

## 说明/提示

对于所有数据，$a_i$ 和 $w_i$ 在小数点后最多有 $5$ 位小数。所有的坐标都是整数。数据保证任何一台敌军坦克将会花费至少 $0.1$ 秒钟的时间来瞄准（注意此处不是说炮塔转过去然后再瞄准，而是炮塔转过去的时间）线段 $AB$ 上的任意一点且敌方坦克与线段 $AB$ 的距离不近于 $0.1$ 米。

对于所有数据，$1\leqslant n\leqslant 10^4,0\leqslant |x_i|,|y_i|\leqslant 10^5,0\leqslant a_i\leqslant2\pi,0\leqslant w_i\leqslant 100,0\leqslant k\leqslant n$。

## 样例 #1

### 输入

```
0 0 10 0
1
5 -5 4.71238 1
0
```

### 输出

```
4.2441
```

## 样例 #2

### 输入

```
0 0 10 0
1
5 -5 4.71238 1
1
```

### 输出

```
0.0000
```

# 题解

## 作者：rEdWhitE_uMbrElla (赞：0)

> 一眼二分题，check打懵逼   ——某奆佬

好吧，，，在这题中，如果$v_1 \le v_2$且$v_1$为可行解，则$v_2$必然为可行解，所以是有单调性的，所以可以二分，然后二分的check就不会打了。。

---

### **重点：关于check**

1. 分析

  分析一下，发现我们其实可以假设所有坦克都转向B点（因为如果一个坦克能在Pedalny行驶过程中（包括AB）指向Pedalny，必然能在Pedalny到达B点之前指向B点，于是只要等Pedalny来了之后一起轰击就行了），于是我们只需要计算出Pedalny到达B点之前，有多少坦克能指向B点就行了。为了让更多的坦克指向B点~~（误~~，我们需要计算出对于每个坦克，是顺时针旋转指向B点，还是逆时针旋转指向B点快。
  
2. 计算旋转时间

  然后我们发现每个坦克的旋转速度是确定的，于是我们只需要计算旋转角就行了，然后就变成了用勾股定理求出边长，然后使用求直角三角形的角的正切值之后$tan^{-1}$算出角度，然后就解决问题了。
  
  如图，CD//x轴，坦克C初始面向射线CE方向，BF$\perp$CD，题目给出了$\angle DCF$，我们只需要计算$\angle BCF$即可，具体计算为:$\angle BCF=tan^{-1}(\frac {BF} {CF})$,最终旋转角为$\angle DCF + \angle BCF$
  
  ![geogebra-export.png](https://i.loli.net/2018/12/06/5c091f3554115.png)

似乎比官方题解简单多了。。个人写实数二分较为奇怪，请勉强接受一下
  
```
#include <bits/stdc++.h>
#define EPS 1e-6
#define PI acos(-1)
using namespace std;

typedef long long ll;

int n,m,k;

struct Point {
    double x, y;
    Point() { }
    Point(double x, double y) : x(x), y(y) { }
    double abs() const { return hypot(x, y); }
    double arg() const { return atan2(y, x); }
    Point operator*(double o) const { return Point(x * o, y * o); }
    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
    bool operator<(const Point& o) const { return x < o.x - EPS || (x < o.x + EPS && y < o.y - EPS); }
};

Point A,B;
map<double, int> js;

int main(){
    scanf("%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y);
    scanf("%d", &n);
    double x,y,a,w;
    for(int i=0;i<n;i++) {
        scanf("%lf%lf%lf%lf",&x,&y,&a,&w);
        if (abs(w) < EPS) continue;
        Point p = {x,y}; double v=-2;
        for(int j=0;j<=100;j++){
            Point tp = (B-A)*(j/100.0) + A;
            double arg = (tp-p).arg() -a;
            if(arg>2*PI) arg-=2*PI;
            while(arg < 0) arg += 2 * PI;
            if (arg>2*PI-arg) arg = 2*PI-arg;
            double t = arg/w;
            v = v<-1 ? (tp-A).abs()/t : max(v, (tp-A).abs()/t);
        }
        js[v]++;
    }
    scanf("%d", &k);
    int sk = 0; double t=-10;
    for(map<double, int>::reverse_iterator it=js.rbegin(); it!= js.rend(); it++) {
        if (sk + it->second > k) {
            t = it->first;
            break;
        }
        sk += it->second;
    }
    printf("%.4lf\n", t<-1 ? 0 : t);
    return 0;
}
```

---

