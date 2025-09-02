# [JSOI2015] symmetry

## 题目描述

张老师正在课堂上讲解正方形的对称模式。为了简单起见，他用 $01$ 方阵代表一个正方形图形，即把正方形分解成 $n\times n$ 的方格阵，$0$ 代表一个白色方格，$1$ 代表一个黑色方格。

首先讲到的是容易辨别的轴对称，正方形有 $4$ 个对称轴，分别是水平中线，竖直中线和两条对角线。如果一个正方形图形以某个对称轴做反射变换后保持不变，就称为轴对称图形。例如下面的两个图形都是轴对称图形。

```plain
100  010
100  101
111  000
```

张老师继续讲解正方形的旋转对称。如果一个正方形图形以中心点旋转 $180$ 度后保持不变，就称为 $180$ 度对称图形。如果以中心点顺时针旋转 $90$ 度后保持不变，就称为 $90$ 度对称图形，例如下面的两个图形左边是 $180$ 度对称图形，右边是 $90$ 度对称图形。

```plain
0011  1011
1110  1110
0111  0111
1100  1101
```

张老师接着说，如果一个正方形图形具有两个互相垂直的对称轴，就称为 $4$ 对称图形，如果关于 $4$ 个对称轴全部对称，就称为 $8$ 对称图形。按照定义，$90$ 度对称图形也是 $180$ 度对称图形，$8$ 对称图形也是 $4$ 对称图形。当正方形图形的边长为偶数时，该图形的中心是最中间 $4$ 个方格的公共顶点，当正方形图形的边长为奇数时，该图形有一个中心方格，该图
形的中心也是它的中心方格的中心。边长为 $1$ 的图形显然是 $8$ 对称图形。

张老师给学生证明了两个定理。

- 定理 $1$：一个正方形图形是 $4$ 对称图形当且仅对它是 $180$ 度对称图形和轴对称图形。
- 定理 $2$：一个正方形图形是 $8$ 对称图形当且仅对它是 $90$ 度对称图形和轴对称图形。

最后是练习时间，张老师要求学生寻找在大正方形图形中出现的各种对称图形。请你编程实现这个要求。设输入一个 $01$ 方阵，输出满足 $8$ 对称，$90$ 度对称，$4$ 对称，$180$ 度对称和轴对称的最大子连续方阵的边长。子连续方阵是指选择若干相邻行列的子方阵，代表在大图形中出现的小图形。

## 说明/提示

#### 样例说明

大图形有水平对称轴，左上角有一个 $2\times 2$ 的 $8$ 对称图形，中间 $3$ 行最右 $3$ 列构成 $4$ 对称图形。

---

#### 数据范围

对于 $100\%$ 的数据，$5\leq n\leq 500$。

## 样例 #1

### 输入

```
5
11100
11000
10111
11000
11100```

### 输出

```
2 2 3 3 5```

# 题解

## 作者：阔耐滴小云呀 (赞：0)

~~本题怎么这么少人提交~~

我们先考虑构造出原正方形经过 $4$ 种轴对称变换以及 $2$ 种旋转变换之后的正方形都构造出来，然后对所得的 $7$ 个正方形都跑一遍二维哈希。

这样我们就可以通过哈希，在 $O(n^2)$ 时间内判断原正方形中是否存在某一类型的某一大小的子正方形。

#### 但是如果我们枚举边长，复杂度就会达到 $O(n^3)$ 级别，显然过不了。

考虑优化：我们发现对于任意一种类型的正方形，它把最外面一圈去掉之后还是满足原来的性质，所以我们可以二分来求。需要注意的是我们不好同时计算奇数边长和偶数边长的正方形，所以要二分两次。

### 参考代码：
```cpp:
#include <cstdio>
#define rg register
#define file(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
template < class T > inline T max(T a, T b) { return a > b ? a : b; }
template < class T > inline void read(T& s) {
    s = 0; int f = 0; char c = getchar();
    while ('0' > c || c > '9') f |= c == '-', c = getchar();
    while ('0' <= c && c <= '9') s = s * 10 + c - 48, c = getchar();
    s = f ? -s : s;
}
 
typedef unsigned long long ull;
const int _ = 502;
const ull base1 = 19491001, base2 = 19260817;
int n; ull pw1[_], pw2[_], h[7][_][_];
 
inline ull gethash(int k, int x1, int y1, int x2, int y2) {
    int w = x2 - x1 + 1;
    return h[k][x2][y2] - h[k][x1 - 1][y2] * pw1[w] - h[k][x2][y1 - 1] * pw2[w] + h[k][x1 - 1][y1 - 1] * pw1[w] * pw2[w];
}
 
inline bool check_90(int x1, int y1, int x2, int y2) {
    return gethash(0, x1, y1, x2, y2) == gethash(5, y1, n - x2 + 1, y2, n - x1 + 1);
}
 
inline bool check_180(int x1, int y1, int x2, int y2) {
    return gethash(0, x1, y1, x2, y2) == gethash(6, n - x2 + 1, n - y2 + 1, n - x1 + 1, n - y1 + 1);
}
 
inline bool check_diag(int x1, int y1, int x2, int y2) {
    return gethash(0, x1, y1, x2, y2) == gethash(1, x1, n - y2 + 1, x2, n - y1 + 1)
        || gethash(0, x1, y1, x2, y2) == gethash(2, n - x2 + 1, y1, n - x1 + 1, y2)
        || gethash(0, x1, y1, x2, y2) == gethash(3, y1, x1, y2, x2)
        || gethash(0, x1, y1, x2, y2) == gethash(4, n - y2 + 1, n - x2 + 1, n - y1 + 1, n - x1 + 1);
}
 
inline bool check_4(int x1, int y1, int x2, int y2) {
    return check_180(x1, y1, x2, y2) && check_diag(x1, y1, x2, y2);
}
 
inline bool check_8(int x1, int y1, int x2, int y2) {
    return check_90(x1, y1, x2, y2) && check_diag(x1, y1, x2, y2);
}
 
template < class T > inline bool check(T f, int x) {
    for (rg int i = x; i <= n; ++i)
        for (rg int j = x; j <= n; ++j)
            if  (f(i - x + 1, j - x + 1, i, j)) return 1;
    return 0;
}
 
template < class T > inline int solve(T f) {
    int res = 0, l, r, mid;
    l = 0, r = (n - 1) >> 1;
    while (l < r) {
        mid = (l + r + 1) >> 1;
        if (check(f, mid << 1 | 1)) l = mid; else r = mid - 1;
    }
    res = max(res, l << 1 | 1);
    l = 1, r = n >> 1;
    while (l < r) {
        mid = (l + r + 1) >> 1;
        if (check(f, mid << 1)) l = mid; else r = mid - 1;
    }
    res = max(res, l << 1);
    return res;
}
 
int main() {
#ifndef ONLINE_JUDGE
    file("cpp");
#endif
    read(n);
    for (rg int i = 1; i <= n; ++i)
        for (rg int j = 1; j <= n; ++j) {
            scanf("%1d", &h[0][i][j]);
            h[1][i][n - j + 1] = h[0][i][j];
            h[2][n - i + 1][j] = h[0][i][j];
            h[3][j][i] = h[0][i][j];
            h[4][n - j + 1][n - i + 1] = h[0][i][j];
            h[5][j][n - i + 1] = h[0][i][j];
            h[6][n - i + 1][n - j + 1] = h[0][i][j];
        }
    pw1[0] = 1; for (rg int i = 1; i <= n; ++i) pw1[i] = pw1[i - 1] * base1;
    pw2[0] = 1; for (rg int i = 1; i <= n; ++i) pw2[i] = pw2[i - 1] * base2;
    for (rg int k = 0; k < 7; ++k) {
        for (rg int i = 1; i <= n; ++i) for (rg int j = 1; j <= n; ++j) h[k][i][j] += h[k][i - 1][j] * base1;
        for (rg int i = 1; i <= n; ++i) for (rg int j = 1; j <= n; ++j) h[k][i][j] += h[k][i][j - 1] * base2;
    }
    printf("%d %d %d %d %d\n", solve(check_8), solve(check_90), solve(check_4), solve(check_180), solve(check_diag));
    return 0;
}
```

---

