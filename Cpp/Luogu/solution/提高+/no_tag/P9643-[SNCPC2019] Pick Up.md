# [SNCPC2019] Pick Up

## 题目描述

格子城是一个位于无限二维平面上的城市，其中对于所有 $k \in \mathbb{Z}$（$\mathbb{Z}$ 是所有整数的集合），直线 $x = k$ 和 $y = k$ 是城市的街道。人们只能沿着道路从一个位置移动到另一个位置。这就是为什么这个城市被称为格子城！

两个朋友，宝宝和梦想格子，快乐地生活在这个城市里。今天宝宝正从他位于 $(x_A, y_A)$（$x_A, y_A \in \mathbb{Z}$）的家出发，前往位于 $(x_C, y_C)$（$x_C, y_C \in \mathbb{Z}$）的购物中心。然而，这段路对他来说太远了，所以他决定叫住在 $(x_B, y_B)$（$x_B, y_B \in \mathbb{Z}$）的梦想格子来帮忙。

宝宝和梦想格子同时从他们的家出发。不同于以每分钟 $a$ 个单位速度步行的宝宝，梦想格子开车并以每分钟 $b$ 个单位速度移动。当梦想格子和宝宝在同一个点相遇时，梦想格子可以接上宝宝，然后他们可以一起以每分钟 $b$ 个单位速度移动。转身或接上宝宝不需要时间。

从宝宝的家到购物中心所需的最短时间是多少？请注意，如果梦想格子接上宝宝会更慢，则不需要梦想格子接宝宝。

## 样例 #1

### 输入

```
3
1 2
0 2 1 0 2 2
1 3
1 1 0 1 3 1
1 2
0 0 100 100 1 1```

### 输出

```
1.500000000000000
1.000000000000000
2.000000000000000```

# 题解

## 作者：SDLTF_凌亭风 (赞：2)

无非就是考虑接还是不接。先算出让 BaoBao 自己去的时间。

在网格图上的走路可以抽象成一个矩形（即把所有的边界线画出来）中的曼哈顿距离，那么假设 A、B 这两点构成的矩形中，在矩形的内部和边界上有一个点 T 到 C 的曼哈顿距离最近。问题就变成了谁先到这个点。

其实也很容易发现，如果 BaoBao 先到，由于 DreamGrid 要走得越快越好，那么总共到商场的时间就是 DreamGrid 直接到的时间。

如果是 DreamGrid 先到，那么肯定希望能接上 BaoBao 一起去。那么 DreamGrid 应该先到 D 点，再到 A 点，然后接上 BaoBao，然后两个人一起去商场。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
using ld = long double;
inline ld gtime(int xa, int ya, int xb, int yb, int v) { return (abs(xb - xa) + abs(yb - ya)) * 1.0 / v; }
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for(int a, b, xa, ya, xb, yb, xc, yc; T; -- T) {
        cin >> a >> b >> xa >> ya >> xb >> yb >> xc >> yc; ld ans = gtime(xa, ya, xc, yc, a);
        int sqrleft = min(xa, xb), sqrright = max(xa, xb), sqrdown = min(ya, yb), sqrtop = max(ya, yb), xminn = max(sqrleft, min(sqrright, xc)), yminn = max(sqrdown, min(sqrtop, yc));
        ld tmatod = gtime(xa, ya, xminn, yminn, a), tmbtod = gtime(xb, yb, xminn, yminn, b);
        if(tmatod < tmbtod) ans = min(ans, gtime(xb, yb, xc, yc, b));
        else {
            ld dis = abs(xc - xa) + abs(yc - ya) - a * gtime(xa, ya, xb, yb, a + b);
            ans = min(ans, gtime(xa, ya, xb, yb, a + b) + dis / b);
        }
        cout << fixed << setprecision(12) << ans << endl;
    }
}
```

---

## 作者：naught (赞：1)

[更好的阅读体验](https://www.cnblogs.com/naughty-naught/p/18469592)

# [SNCPC2019] Pick Up

## 题意

给出甲的坐标和速度，乙的坐标和速度，商场的坐标，可以让乙去接甲，求甲前往商场的最短用时。

## Solution

分类讨论。

思考乙是否要去接甲。这个很简单，令 $ans1$ 为甲自己出发耗时，$ans2$ 为乙接甲耗时，两者取最小值即可。

$ans1$ 很好算，那么 $ans2$ 呢？

直接思考三个点比较困难，考虑把甲乙放在一起（也就是以两点建矩形），设该矩形内或矩形上有一点 $P$ 距离商场最近。

1.甲先到 $P$ 点。那么乙自然越快到商场越好，那么 $ans2$ 为乙到商场的时间。

2.乙先到 $P$ 点。显然让乙去接甲，同时让甲直接冲向 $P$，乙去拦住甲并接上甲。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double lb;
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define fr(i, r, l) for (int i = l; i >= r; --i)
// #define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
// char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}
inline ll lread(ll x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}
// void train() {ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);}

int a, b, x_a, y_a, x_b, y_b, x_c, y_c, l, r, d, u, x, y;
ll dis_1, dis_2;

ll Distance(int a, int b, int c, int d) { return 0ll + abs(a-c) + abs(b-d); }

lb Time(int a, int b, int c, int d, int v) {return (Distance(a, b, c, d) * 1.0) / (v * 1.0);}

lb ans1, ans2;

int main()
{
    int _ = read();
    while( _-- )
    {
        a = read(), b = read(), x_a = read(), y_a = read(), x_b = read(), y_b = read(), x_c = read(), y_c = read();
        ans1 = Time(x_a, y_a, x_c, y_c, a), l = min(x_a, x_b), r = x_a + x_b - l, d = min(y_a, y_b), u = y_a + y_b - d;
        x = max(l, min(r, x_c)), y = max(d, min(u, y_c));
        if( Time(x_a, y_a, x, y, a) < Time(x_b, y_b, x, y, b) ) ans2 = Time(x_b, y_b, x_c, y_c, b);
        else
        {
            lb dist = Distance(x_a, y_a, x_c, y_c) - (1.0 * a) * Time(x_a, y_a, x_b, y_b, a + b);
            ans2 = Time(x_a, y_a, x_b, y_b, a + b) + dist / b;
        }
        printf("%.7Lf\n", min(ans1, ans2));
    }
    return 0;
}
```

## Tips

记得保留至少 $7$ 位小数。

---

