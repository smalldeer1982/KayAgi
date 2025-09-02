# 题目信息

# Aerodynamic

## 题目描述

Guy-Manuel and Thomas are going to build a polygon spaceship.

You're given a strictly convex (i. e. no three points are collinear) polygon $ P $ which is defined by coordinates of its vertices. Define $ P(x,y) $ as a polygon obtained by translating $ P $ by vector $ \overrightarrow {(x,y)} $ . The picture below depicts an example of the translation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1299B/83c2f1baf8b89730630e4ed629298d51b68af048.png)

Define $ T $ as a set of points which is the union of all $ P(x,y) $ such that the origin $ (0,0) $ lies in $ P(x,y) $ (both strictly inside and on the boundary). There is also an equivalent definition: a point $ (x,y) $ lies in $ T $ only if there are two points $ A,B $ in $ P $ such that $ \overrightarrow {AB} = \overrightarrow {(x,y)} $ . One can prove $ T $ is a polygon too. For example, if $ P $ is a regular triangle then $ T $ is a regular hexagon. At the picture below $ P $ is drawn in black and some $ P(x,y) $ which contain the origin are drawn in colored:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1299B/7e534d615e6a5f78b53ffae5177d7d1ddaf49471.png)

The spaceship has the best aerodynamic performance if $ P $ and $ T $ are similar. Your task is to check whether the polygons $ P $ and $ T $ are [similar](https://tinyurl.com/vp5m7vl).

## 说明/提示

The following image shows the first sample: both $ P $ and $ T $ are squares. The second sample was shown in the statements.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1299B/e9bf2b6bd412db56abfa4dcfff0f19e57982f841.png)

## 样例 #1

### 输入

```
4
1 0
4 1
3 4
0 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
3
100 86
50 0
150 0```

### 输出

```
nO```

## 样例 #3

### 输入

```
8
0 0
1 0
2 1
3 3
4 6
3 6
2 5
1 3```

### 输出

```
YES```

# AI分析结果

### 题目翻译
# 空气动力学

## 题目描述
盖伊 - 曼努埃尔（Guy - Manuel）和托马斯（Thomas）打算建造一艘多边形宇宙飞船。

给定一个严格凸多边形 $P$（即不存在三点共线），它由其顶点的坐标定义。定义 $P(x,y)$ 为将 $P$ 按向量 $\overrightarrow {(x,y)}$ 平移后得到的多边形。下图展示了一个平移的示例：

（此处插入对应的图片链接）

定义 $T$ 为所有包含原点 $(0,0)$ 的 $P(x,y)$ 的并集（原点既可以严格在 $P(x,y)$ 内部，也可以在其边界上）。还有一个等价定义：点 $(x,y)$ 属于 $T$ 当且仅当在 $P$ 中存在两点 $A$、$B$ 使得 $\overrightarrow {AB} = \overrightarrow {(x,y)}$。可以证明 $T$ 也是一个多边形。例如，如果 $P$ 是一个正三角形，那么 $T$ 是一个正六边形。在下图中，$P$ 用黑色绘制，一些包含原点的 $P(x,y)$ 用彩色绘制：

（此处插入对应的图片链接）

如果 $P$ 和 $T$ 相似，那么这艘宇宙飞船的空气动力学性能最佳。你的任务是检查多边形 $P$ 和 $T$ 是否[相似](https://tinyurl.com/vp5m7vl)。

## 说明/提示
下图展示了第一个样例：$P$ 和 $T$ 都是正方形。第二个样例在题目描述中已经给出。

（此处插入对应的图片链接）

## 样例 #1
### 输入
```
4
1 0
4 1
3 4
0 3
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
3
100 86
50 0
150 0
```
### 输出
```
nO
```

## 样例 #3
### 输入
```
8
0 0
1 0
2 1
3 3
4 6
3 6
2 5
1 3
```
### 输出
```
YES
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是将判断多边形 $P$ 和 $T$ 是否相似的问题转化为判断多边形是否为中心对称图形。因为通过对闵可夫斯基和等概念的分析，发现满足条件的多边形与原多边形相似比为 2，且边存在共线等特征，最终得出判断中心对称的结论。判断中心对称的方法是检查多边形对应点连线的中点是否重合。

### 所选题解
- **syksykCCC（5星）**
    - **关键亮点**：思路清晰，先引入闵可夫斯基和的前置知识，详细推导得出判断中心对称的结论，代码可读性高，对浮点数比较使用了误差范围处理。
    - **个人心得**：提到是写给没写过计算几何的人，有引导作用。
- **lemonfor（4星）**
    - **关键亮点**：简洁明了地指出题目是找边数为偶数的中心对称图形，代码实现较为规范，使用了宏定义和自定义输入函数。
- **ShineEternal（4星）**
    - **关键亮点**：对题目进行了清晰的翻译和解读，直接点明判断中心对称的思路，代码简洁易懂。

### 重点代码
#### syksykCCC 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const double EPS = 1e-10;
double x[N], y[N];
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    if(n & 1) { cout << "NO\n"; return 0; }
    int mid = n >> 1;
    double px = (x[1] + x[mid + 1]) / 2.0;
    double py = (y[1] + y[mid + 1]) / 2.0;
    bool ok = true;
    for(int i = 2; i <= mid; i++)
    {
        double kx = (x[i] + x[mid + i]) / 2.0;
        double ky = (y[i] + y[mid + i]) / 2.0;
        if(fabs(px - kx) >= EPS || fabs(py - ky) >= EPS) ok = false;
    }
    if(ok) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}
```
**核心实现思想**：先判断边数是否为奇数，若是则直接输出 `NO`。然后计算第一组对应点连线的中点坐标，再遍历其他组对应点，计算其中点坐标并与第一组的中点坐标比较，若有不相等则标记为 `NO`。

### 最优关键思路或技巧
- **思维方式**：通过对闵可夫斯基和的理解和图形特征的分析，将复杂的多边形相似判断问题转化为简单的中心对称判断问题。
- **代码实现**：在比较浮点数时使用误差范围 `EPS` 来避免精度问题。

### 拓展思路
同类型题目可能会涉及其他几何图形的对称性质判断，或者在不同的变换（如旋转、缩放等）下判断图形的相似性。类似算法套路可以先分析图形变换的性质，尝试将复杂问题转化为简单的几何特征判断问题。

### 推荐洛谷题目
- P1182 数列分段 Section II
- P1024 一元三次方程求解
- P1075 质因数分解

---
处理用时：39.78秒