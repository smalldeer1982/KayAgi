# [PA 2013] Działka

## 题目描述

给定 $k\times k$ 平面中的 $n$ 个点，$m$ 次询问，每次询问一个边平行于坐标轴的矩形内部（包含边界）的点构成的凸包面积。

## 说明/提示

$1\leq k\leq 10^6$，$3\leq n\leq 3\times 10^3$，$1\leq m\leq 10^6$，$0\leq x_i,y_i,a_i,b_i,c_i,d_i\leq k，a_i<c_i,b_i<d_i$。

## 样例 #1

### 输入

```
9 7
1 1
1 3
3 3
3 1
6 5
6 6
7 3
3
0 4 0 4
2 7 0 7
3 7 3 6```

### 输出

```
4.0
10.0
6.0```

# 题解

## 作者：jiangly (赞：19)

首先可以扫描线 + 线段树求出每个询问四个方向的第一个点，通过这些点把询问拆成四个方向的凸包。

预处理每对点逆时针沿凸包走的叉积和 (如左下到右上就是沿右下凸包走)。每个询问将四个方向求和再除以 $2$ 即可。

时间复杂度 $O(n^2+m\log m)$。

```cpp
#include <bits/stdc++.h>

constexpr int N = 3e3, M = 1e6, S = 1 << 21;

int n, m, k;
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
} p[N];
bool operator<(const Point &lhs, const Point &rhs) {
    return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
}
int64_t cross(const Point &lhs, const Point &rhs) {
    return 1ll * lhs.x * rhs.y - 1ll * lhs.y * rhs.x;
}
Point operator-(const Point &lhs, const Point &rhs) {
    return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}

int a[N];
int64_t f[N][N];

int xl[M], xr[M], yl[M], yr[M];
int b[M];
int pt[M][4];

int lg;
int arr[S];

void modify(int x, int v) {
    for (x += (1 << lg) + 1; x; x /= 2)
        arr[x] = std::min(arr[x], v);
}

int rangeMin(int l, int r) {
    int res = n;
    for (l += (1 << lg), r += (1 << lg) + 2; l ^ r ^ 1; l /= 2, r /= 2) {
        if (l % 2 == 0)
            res = std::min(res, arr[l ^ 1]);
        if (r % 2 == 1)
            res = std::min(res, arr[r ^ 1]);
    }
    return res;
}

void work(int id, int offset = 0) {
    std::iota(a, a + n, 0);
    std::sort(a, a + n, [&](int i, int j) {
        return p[i] < p[j];
    });
    
    std::iota(b, b + m, 0);
    std::sort(b, b + m, [&](int i, int j) {
        return xl[i] > xl[j];
    });
    
    std::fill(arr, arr + (1 << (lg + 1)), n);
    
    for (int i = n - 1, qi = 0; i >= 0; --i) {
        int u = a[i];
        int w = u;
        for (int j = i + 1; j < n; ++j) {
            int v = a[j];
            if (p[v].y < p[u].y)
                continue;
            if (cross(p[w] - p[u], p[v] - p[u]) <= 0)
                w = v;
            f[u][v] = cross(p[u], p[w]) + f[w][v];
        }
        
        modify(p[u].y + offset, i);
        
        int lim = i == 0 ? -k - 1 : p[a[i - 1]].x;
        while (qi < m && xl[b[qi]] > lim) {
            int j = b[qi];
            pt[j][id] = a[rangeMin(yl[j] + offset, yr[j] + offset)];
            ++qi;
        }
    }
}

void rotate() {
    for (int i = 0; i < n; ++i) {
        std::swap(p[i].x, p[i].y);
        p[i].x = -p[i].x;
    }
    for (int i = 0; i < m; ++i) {
        std::swap(xl[i], yl[i]);
        std::swap(xr[i], yr[i]);
        std::swap(xl[i], xr[i]);
        xl[i] = -xl[i];
        xr[i] = -xr[i];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cin >> k >> n;
    while ((1 << lg) < k + 3)
        ++lg;
    for (int i = 0; i < n; ++i)
        std::cin >> p[i].x >> p[i].y;
    std::cin >> m;
    for (int i = 0; i < m; ++i)
        std::cin >> xl[i] >> xr[i] >> yl[i] >> yr[i];
    
    work(0);
    rotate();
    work(3);
    rotate();
    work(2, k);
    rotate();
    work(1, k);
    
    for (int i = 0; i < m; ++i) {
        int64_t area = 0;
        for (int j = 0; j < 4; ++j)
            area += f[pt[i][j]][pt[i][(j + 1) % 4]];
        std::cout << area / 2 << "." << "05"[area % 2] << "\n";
    }
    
    return 0;
}
```

---

## 作者：小胖同学 (赞：5)

# P6818 [PA2013]Działka


## 前言

我太菜了。。。。

对着 [ **jiangly** ](https://www.luogu.com.cn/user/149656) 大佬的题解研究了一下午研究了一下午才搞出来（泪目。

作为一个蒟蒻，我就详细的讲一下我对与本题的理解。


## 题意

本题的的题意描述的还是比较明了。

在二维坐标系中，输入 $n$ 个点 $m$ 次询问，

每次询问，给出一个矩阵，

求出矩阵内极大凸包的面积。


## 题解

### 1.如何求面积

二维平面的计算几何题，较常见的做法就是利用叉积。本题亦如此。

叉积有个优美的性质，我们可以发现对于 $\vec{a} \times \vec{b}$ 可以在二维平面赋予特殊意义（ $S$ 为三角形面积）。

 $\vec{a} \times \vec{b} = 2S$   
 
利用这个性质我们就可以求出任意凸包的面积。

举个例子，$4$ 个点坐标为 $(1 , 1) (1 , 3) (3 , 3) (3 , 1)$ 在此记为 $0$ 号点到 $3$ 号点，$G$ 记为原点，

那要求出其凸包的面积就可以写作：

${ \vec{G0} \times \vec{G3} + \vec{G3} \times \vec{G2} + \vec{G1} \times \vec{G0} + \vec{G1} \times \vec{G0} \over 2}$  



![](https://cdn.luogu.com.cn/upload/image_hosting/4kps0jpw.png)

其实就可以理解为绿色的三角形相加。

![](https://cdn.luogu.com.cn/upload/image_hosting/nfude60g.png)

再容斥一下减去红色三角(由于叉乘的顺寻原因出来的红色三角形负数)。

![](https://cdn.luogu.com.cn/upload/image_hosting/bcph30kj.png)

剩下的就是索要求的凸包面积。

因为本题 $n \le 3000$ 我们可以考虑直接 $O(n ^ 2)$ 预处理出每两个向量的叉乘(其实不是任意两个的叉乘，详见第三部分)。

呢么下面的任务就是快速找到凸包外面的点。

---

### 2.如何找凸包

如何找凸包呢？有一个十分优雅的方法。可以考虑寻找类似于四分之一扇形的凸包，然后每次旋转找到 $4$ 个半圆再求和。假设我们先找右上角的扇形。

对于如下图形如何优美的找到凸包呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/34gqvacp.png)

我们可以考虑将点以优先 $x$ 从大到小后 $y$ 从大到小的顺序找（过程可以顺便预处理前面提到的任意两点的距离）。

手模一下发现，我们先会从 $1$ 号点就可以轻易的找到 ${1 , 3 , 4}$ 的点集。

呢如何记录高效的记录答案呢？

---

### 3.如何记录答案

直接枚举每个问题，显然会 T 飞。

考虑在记录两点间距离的时候直接记录最外面凸包的距离，例如前面的图片，在记录 $\vec{1} \times \vec{4}$ 的时可以直接记录为 $\vec{1} \times \vec{3} + \vec{3} \times \vec{4}$。样我们在统计答案的时候实际上只需要记录只需要记录他最接近边界的两个点就可了。

考虑每一次记录答考虑使用线段树加扫描线的思想，如下图为每个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/7sqwvpui.png)

当我们更新完最外面的橙色的点还没有处理蓝色的点的时候，考虑有哪些区间里的提问是可以被更新的。  



![](https://cdn.luogu.com.cn/upload/image_hosting/2x3b6n8i.png)

黄色的区间是可以被更新的，利用扫描线的思想做到 $O(m \log m)$ 维护每个图形的边界。

---

### $\bullet$ 加强版

模拟赛出了这道题的加强版，若坐标的范围改成 $-10^7 \le x ,y \le 10^7$。

两个办法，一是使用效率更高的 zkw 线段树，二是数据离散化。

当然本题用普通线段树就可以切了。

## Code

代码跟 [**jiangly**](https://www.luogu.com.cn/user/149656) 大佬的没有本质区别，就不粘了（doge去翻上一篇题解吧。

---

