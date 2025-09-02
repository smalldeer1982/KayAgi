# Mice problem

## 题目描述

Igor the analyst fell asleep on the work and had a strange dream. In the dream his desk was crowded with computer mice, so he bought a mousetrap to catch them.

The desk can be considered as an infinite plane, then the mousetrap is a rectangle which sides are parallel to the axes, and which opposite sides are located in points $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ .

Igor wants to catch all mice. Igor has analysed their behavior and discovered that each mouse is moving along a straight line with constant speed, the speed of the $ i $ -th mouse is equal to $ (v_{i}^{x},v_{i}^{y}) $ , that means that the $ x $ coordinate of the mouse increases by $ v_{i}^{x} $ units per second, while the $ y $ coordinates increases by $ v_{i}^{y} $ units. The mousetrap is open initially so that the mice are able to move freely on the desk. Igor can close the mousetrap at any moment catching all the mice that are strictly inside the mousetrap.

Igor works a lot, so he is busy in the dream as well, and he asks you to write a program that by given mousetrap's coordinates, the initial coordinates of the mice and their speeds determines the earliest time moment in which he is able to catch all the mice. Please note that Igor can close the mousetrap only once.

## 说明/提示

Here is a picture of the first sample

Points A, B, C, D - start mice positions, segments are their paths.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/0c2fcb8709057e532ca0131544d2596c5ce57683.png)

Then, at first time when all mice will be in rectangle it will be looks like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/243afe4c229018b391d2ff30ae0186ebf1cbce8c.png)

Here is a picture of the second sample

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF793C/c8ca503e68f8ea8d507deb9be3b10b823dad4205.png)

Points A, D, B will never enter rectangle.

## 样例 #1

### 输入

```
4
7 7 9 8
3 5 7 5
7 5 2 4
3 3 7 8
6 6 3 2
```

### 输出

```
0.57142857142857139685
```

## 样例 #2

### 输入

```
4
7 7 9 8
0 3 -5 4
5 0 5 4
9 9 -1 -6
10 5 -7 -10
```

### 输出

```
-1
```

# 题解

## 作者：tZEROちゃん (赞：2)

不算很难的计算几何，CF 上评分 2300，感觉高了点（虽然交了 8 发才过。

考虑转化为一维问题，我们分别考虑横坐标和纵坐标。

首先，如果一个点它的 $vx =0$，且它的横坐标不在捕鼠器横坐标的范围内，那么它就一直可以逍遥法外，因此输出 $-1$；若 $vy = 0$ 也同理。

然后我们分别计算一只老鼠横坐标和纵坐标进入捕鼠器的范围内的时间。假设横坐标在范围内的时间是 $[t_1, t_2]$，纵坐标是 $[t_3, t_4]$，那么这只老鼠在捕鼠器里的时间就是这两个区间的交集。因此，对每只老鼠都取一下范围，然后取这些范围区间的交集即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)
#define per(i, r, l) for(auto i = (r); i >= (l); --i)

#define i64 long long

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n; cin >> n;
  vector<double> X(3), Y(3);
  auto Range = [&](int a, int b, int c) -> bool {
    return a < b && b < c;
  };
  cin >> X[1] >> Y[1] >> X[2] >> Y[2];
  double mn = 0, mx = 1e9;
  while (n--) {
    double x, y, vx, vy; cin >> x >> y >> vx >> vy;
    if (vx == 0) {
      if (!Range(X[1], x, X[2])) {
        cout << "-1" << '\n'; return 0;
      }
    }
    else {
      double t1 = (X[1] - x) / vx, t2 = (X[2] - x) / vx; 
      if (t1 > t2) swap(t1, t2);
      mn = max(mn, t1), mx = min(mx, t2);
    }
    if (vy == 0) {
      if (!Range(Y[1], y, Y[2])) {
        cout << "-1" << '\n'; return 0;
      }
    }
    else {
      double t1 = (Y[1] - y) / vy, t2 = (Y[2] - y) / vy; 
      if (t1 > t2) swap(t1, t2);
      mn = max(mn, t1), mx = min(mx, t2);
    }
  }
  if (mn > mx - 1e-10) cout << -1 << '\n';
  else cout << fixed << setprecision(15) << mn << '\n';
  return ~~(0 ^ 0);
}
```

---

## 作者：Priestess_SLG (赞：0)

比较简单的 $2300$。考虑把横纵坐标拆分考虑然后分别计算出横纵坐标在矩形内的时间区间 $[tl,tr]$，将全部这些区间取交集即可。时间复杂度为 $O(n)$。

特殊的，需要判断速度为 $0$ 的情况，**以及注意点在矩形边界上不算做矩形内。**

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500010;
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int T;
    cin >> T;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    vector<tuple<int, int, int>> v;
    while (T--) {
        int x_1, y_1, x_2, y_2;
        cin >> x_1 >> x_2 >> y_1 >> y_2;
        if (y_1) {
            v.emplace_back(x_1, y_1, 1);
        } else {
            if (x1 < x_1 && x_1 < x2) ;
            else {
                cout << "-1\n";
                return 0;
            }
        }
        if (y_2) {
            v.emplace_back(x_2, y_2, 0);
        } else {
            if (y1 < x_2 && x_2 < y2) ;
            else {
                cout << "-1\n";
                return 0;
            }
        }
    }
    double L = 0, R = 1e18;
    for (auto &[x, y, o] : v) {
        if (o) {
            double v1 = 1. * (x1 - x) / y;
            double v2 = 1. * (x2 - x) / y;
            if (v1 > v2) swap(v1, v2);
            L = max(L, v1), R = min(R, v2);
        } else {
            double v1 = 1. * (y1 - x) / y;
            double v2 = 1. * (y2 - x) / y;
            if (v1 > v2) swap(v1, v2);
            L = max(L, v1), R = min(R, v2);
        }
    }
    if (L < R) cout << L << '\n';
    else cout << -1 << '\n';
    return 0;
}


```

---

## 作者：xzggzh1 (赞：0)

题意：

给你一个捕鼠器坐标（为矩形），和各个老鼠的的坐标以及相应坐标的移动速度，问你是否存在一个时间点可以关闭捕鼠器抓住所有的老鼠，相对误差不能超过 $10^{-6}$。

---

是一道比较普通的计算几何的题。

我们只要把每一个老鼠在矩形里的时间段算出来然后取交集，若交集非空则输出交集中的任意点即可。

主要有以下两个要点：

1. 计算每一只老鼠在矩形里的时间：将横坐标和纵坐标分开计算取交集即可。

2. 如何取交集：交集的左端点是所有集合的左端点的最大值，交集的右端点是所有集合右端点的最小值。

（由于集合都是连续的，所以这个方法的正确性反证即易证）。

---
核心代码：

```cpp
double l=0,r=1e11;
void updata(int pos,int lb,int rb,int v){
    if(v==0){
        if(pos>lb&&pos<rb)return;
        r=-1;//无解 
    }
    double t1=(double)(lb-pos)/v,t2=(double)(rb-pos)/v;
    if(t1>t2)swap(t1,t2);
    l=max(l,t1);
    r=min(r,t2);
}
int x,y,vix,viy,n,x1,y1,x2,y2;
int main(){
    scanf("%d",&n);
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    for(int i=1;i<=n;i++){
        scanf("%d %d %d %d",&x,&y,&vix,&viy);
        updata(x,x1,x2,vix);
        updata(y,y1,y2,viy);
    }
    if(r-l>=1e-11&&r>0)printf("%.10lf\n",l);
    else printf("-1\n");
}
```

---

