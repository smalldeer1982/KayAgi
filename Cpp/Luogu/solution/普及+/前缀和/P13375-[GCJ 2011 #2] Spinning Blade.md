# [GCJ 2011 #2] Spinning Blade

## 题目描述

你对自己秘密基地设计中的陷阱感到厌倦，决定采用一种经典但总是令人愉快的装置——“旋转刀片”。你订购了一块非常重的金属板，准备从中切割出刀片；在金属板上会绘制一个均匀的 $C$ 行 $R$ 列的方格。你已经确定了刀片的最佳形状——你将首先切割出一个 $K \times K$ 的大正方形方格，其中 $K \geq 3$。然后，你会将该正方形的四个 $1 \times 1$ 的角格切掉，最终得到一个“刀片”。确定好这些后，你就开始等待金属板的到来。

当金属板到达时，你震惊地发现板材有瑕疵！你原本期望每个格子的质量都是 $D$，但实际上由于厚度的差异，每个格子的质量会有些许变化。这很糟糕，因为你想要在刀片的正中心插入一个轴并让其高速旋转，因此刀片的质心必须恰好位于其中心。二维物体的质心定义见下文。

给定方格和每个格子的质量，求你能切割出的最大尺寸的刀片，使得其质心恰好位于中心。

## 说明/提示

**样例说明**

二维物体的质心正式定义为一个点 $c$。如果你对物体中的所有点 $p$ 计算 $(p - c) \times \text{mass}(p)$ 的和，结果必须为 $0$。其中 $p$、$c$ 和 $0$ 都是二维向量。这个定义同样适用于将每个格子视为一个“点”，其全部质量集中在中心。

在现实生活中，你可以把手指放在一个平面物体的质心下方，并让物体平衡在手指上，它不会倾倒。

举例来说，在第二个样例测试中，唯一可行的刀片是 $3 \times 3$ 的刀片（去掉四个角），其质心位于点 $(1.54, 1.46)$，假设金属板左下角坐标为 $(0, 0)$，坐标分别向右和向上递增。可以通过以下等式验证：$(-1.04, 0.04) \times 9 + (-0.04, 1.04) \times 9 + (-0.04, 0.04) \times 10 + (-0.04, -0.96) \times 11 + (0.96, 0.04) \times 11 = (0, 0)$。

**数据范围**

- $1 \leq T \leq 20$。
- $0 \leq w_{ij} \leq 9$。
- 输入文件大小不超过 625KB。

**小数据范围（8 分，测试点 1 - 可见）**

- $3 \leq R \leq 10$。
- $3 \leq C \leq 10$。
- $1 \leq D \leq 100$。
- 时间限制：3 秒。

**大数据范围（12 分，测试点 2 - 隐藏）**

- $3 \leq R \leq 500$。
- $3 \leq C \leq 500$。
- $1 \leq D \leq 10^6$。
- 时间限制：6 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
6 7 2
1111111
1122271
1211521
1329131
1242121
1122211
3 3 7
123
234
345```

### 输出

```
Case #1: 5
Case #2: IMPOSSIBLE```

# 题解

## 作者：goodfish (赞：0)

# 题目大意

本题要求从给定的 $R \times C$ 网格中切割出最大的旋转刀片。具体来说，对于一个刀片：


首先切割一个 $K \times K$ 的正方形（$K \geq 3$）。随后移除四个角的 $1 \times 1$ 大小的格子。

特别的，切割所用板材存在瑕疵，其质量分布并不均匀，现给定 $w_{i,j}$，表示实际质量与期望质量的差值，要求刀片的质心恰好位于其几何中心，求最大可切割数量。

# 分析

如果我们设刀片区域为 $[r, r+K-1] \times [c, c+K-1]$，则其几何中心坐标为：

$$\left(c + \frac{K-1}{2}, r + \frac{K-1}{2}\right)$$

而对于物体的质心，其坐标为各质点质量与坐标的加权平均，在此不过多赘述，具体思路参考给出代码。

知道了质心和几何中心之后，不难想到枚举并检查是否符合**质心恰好位于其几何中心**，从而得到最大可能数量。

# 具体代码实现

由于需要计算平均值，可以通过前缀和预处理的方式加速计算过程，具体而言：

   - $b[i][j]$：质量矩阵的二维前缀和。
   - $x[i][j]$：$j \cdot m_{i,j}$ 的二维前缀和。
   - $y[i][j]$：$i \cdot m_{i,j}$ 的二维前缀和。

此外，我们还可以通过将质心条件转换为整数形式来避免浮点数计算导致的精度丢失问题：

   $$2S_x - (2c + K-1)W = (K-1)(B + D - A - C)$$
   $$2S_y - (2r + K-1)W = (K-1)(C + D - A - B)$$
   其中 $S_x, S_y$ 为子矩阵的加权和，$W$：子矩阵总质量。

这样，我们只需要先从大到小枚举 $K (\min(R,C) \to 3)$，并对每个 $K$ 枚举所有起始位置 $(r,c)$，使用前缀和计算子矩阵和，当同时满足两个方程时记录 $K$ 并跳出。

该算法的时间复杂度为 $O(RC \cdot \min(R,C))$，空间复杂度为 $O(RC)$。

# 代码实现
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

char s[555][555];
ll a[555][555], b[555][555], x[555][555], y[555][555];
int n, m, d, t, best;

int main() {
    cin >> t;
    for (int ct = 1; ct <= t; ct++) {
        best = 0;
        cout << "Case #" << ct << ": ";
        cin >> n >> m >> d;
        for (int i = 0; i < n; i++) cin >> s[i];
        
        memset(b, 0, sizeof(b));
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][j] = d + (s[i][j] - '0');
                b[i][j] = a[i][j];
                x[i][j] = 1LL * j * a[i][j];
                y[i][j] = 1LL * i * a[i][j];
                if (i) {
                    b[i][j] += b[i-1][j];
                    x[i][j] += x[i-1][j];
                    y[i][j] += y[i-1][j];
                }
                if (j) {
                    b[i][j] += b[i][j-1];
                    x[i][j] += x[i][j-1];
                    y[i][j] += y[i][j-1];
                }
                if (i && j) {
                    b[i][j] -= b[i-1][j-1];
                    x[i][j] -= x[i-1][j-1];
                    y[i][j] -= y[i-1][j-1];
                }
            }
        }
        
        int max_k = min(n, m);
        for (int k = max_k; k >= 3; k--) {
            for (int i = 0; i <= n - k; i++) {
                int ex = i + k - 1;
                for (int j = 0; j <= m - k; j++) {
                    int ey = j + k - 1;
                    
                    ll w = b[ex][ey];
                    if (i) w -= b[i-1][ey];
                    if (j) w -= b[ex][j-1];
                    if (i && j) w += b[i-1][j-1];
                    
                    ll sx = x[ex][ey];
                    if (i) sx -= x[i-1][ey];
                    if (j) sx -= x[ex][j-1];
                    if (i && j) sx += x[i-1][j-1];
                    
                    ll sy = y[ex][ey];
                    if (i) sy -= y[i-1][ey];
                    if (j) sy -= y[ex][j-1];
                    if (i && j) sy += y[i-1][j-1];
                    
                    ll A = a[i][j];
                    ll B = a[i][ey];
                    ll C = a[ex][j];
                    ll D_val = a[ex][ey]; // Avoid conflict with macro
                    
                    ll left_x = 2 * sx - (2LL * j + k - 1) * w;
                    ll right_x = (k - 1LL) * (B + D_val - A - C);
                    if (left_x != right_x) continue;
                    
                    ll left_y = 2 * sy - (2LL * i + k - 1) * w;
                    ll right_y = (k - 1LL) * (C + D_val - A - B);
                    if (left_y != right_y) continue;
                    
                    best = k;
                    goto here;
                }
            }
        }
        
        here:
        if (best == 0) cout << "IMPOSSIBLE" << endl;
        else cout << best << endl;
    }
    return 0;
}
```

注：前缀和计算时不要忘了边界条件。

---

