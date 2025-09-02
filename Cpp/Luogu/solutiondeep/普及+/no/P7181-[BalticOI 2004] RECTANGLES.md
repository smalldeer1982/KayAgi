# 题目信息

# [BalticOI 2004] RECTANGLES

## 题目描述

平面上有 $n$ 个矩形。矩形边平行于坐标轴。这些长方形可以重叠、重合或相互分离。它们的顶点坐标 $(x,y)$ 中，$x,y$ 都是非负整数，横坐标不超过 $x_{\max}$，纵坐标不超过 $y_{\max}$。

$A$ 点位于 $(0,0)$，若 $C(x_{\max},0),D(0,y_{\max}),E(x_{\max},y_{\max})$，则 $B$ 点位于线段 $CE$ 或 $DE$ 上。

线段 $AB$ 可能与矩形相交（即使只与一个矩形**顶点**相交，也视为相交）。

你需要找到一个 $B$，使与线段 $AB$ 相交的矩形尽可能**多**。

## 说明/提示

#### 样例 1 说明

![](https://cdn.luogu.com.cn/upload/image_hosting/n987wmyr.png)

输出也可以为 `5 22 11`。

#### 数据规模与约定

对于 $100\%$ 的数据，有 $1\le n\le 10^4$，$0\le x_{\max},y_{\max}\le 10^9$。

#### 说明

译自 [BalticOI 2004 Day2 B RECTANGLES](https://boi.cses.fi/files/boi2004_day2.pdf)

#### 特别感谢

感谢 @[tiger2005](https://www.luogu.com.cn/user/60864) 提供的 SPJ！

## 样例 #1

### 输入

```
22 14 8
1 8 7 11
18 10 20 12
17 1 19 7
12 2 16 3
16 7 19 9
8 4 12 11
7 4 9 6
10 5 11 6```

### 输出

```
5 22 12```

# AI分析结果

### 算法分类
排序

### 综合分析与结论
本题的核心在于如何高效地找到线段 $AB$ 与最多矩形相交的点 $B$。两个题解都采用了将问题转化为区间覆盖的思路，通过排序和扫描线的方法来求解。KohaD_SEGA的题解通过将矩形的边界点映射到边界上，然后对这些点进行排序和扫描，最终找到最优解。qiliu的题解则通过计算斜率，将问题转化为在边界上寻找被最多区间覆盖的点，同样使用了排序和扫描线的方法。

### 所选题解
#### 题解1：KohaD_SEGA
- **星级**：4星
- **关键亮点**：通过将矩形的边界点映射到边界上，简化了问题，代码结构清晰，逻辑严谨。
- **个人心得**：在处理浮点数精度问题时，使用了 `ceil` 和 `floor` 函数，并添加了微小偏移量来避免精度误差。

```cpp
inline void add(int x,int y,int tp)
{
    double a;
    m[++len].tp=tp;
    if(x*1LL*maxy<=y*1LL*maxx)	m[len].h=maxy;
    else
    {
        a=(long long)maxx*1LL*y;
        a=a*1.0/x;
        if(tp>0)	m[len].h=ceil(a-0.0001);
        else	m[len].h=floor(a+0.0001);
    }
}
```

#### 题解2：qiliu
- **星级**：4星
- **关键亮点**：通过计算斜率，将问题转化为在边界上寻找被最多区间覆盖的点，思路清晰，代码简洁。
- **个人心得**：在处理斜率比较时，使用了自定义的比较运算符，避免了浮点数精度问题。

```cpp
struct xyxy{
    double x,y;
    bool operator>(const xyxy &xx)const{return y*xx.x>x*xx.y;}
    bool operator!=(const xyxy &xx)const{return y*xx.x!=x*xx.y;}
};
```

### 最优关键思路或技巧
1. **区间覆盖与扫描线**：将问题转化为区间覆盖问题，通过排序和扫描线的方法高效求解。
2. **斜率计算与比较**：通过计算斜率，将问题转化为在边界上寻找被最多区间覆盖的点，避免了复杂的几何计算。
3. **浮点数精度处理**：在处理浮点数时，使用 `ceil` 和 `floor` 函数，并添加微小偏移量来避免精度误差。

### 可拓展之处
类似的问题可以通过将几何问题转化为区间覆盖或扫描线问题来解决，例如求最大重叠区域、最小覆盖点等。

### 推荐题目
1. [P1884 [USACO12OPEN]Balanced Cow Subsets](https://www.luogu.com.cn/problem/P1884)
2. [P1904 [USACO08DEC]Secret Message](https://www.luogu.com.cn/problem/P1904)
3. [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)

这些题目都涉及到区间覆盖、扫描线或几何问题的转化，可以帮助进一步巩固相关算法和技巧。

---
处理用时：19.38秒