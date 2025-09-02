# 题目信息

# Rectangle Arrangement

## 题目描述

You are coloring an infinite square grid, in which all cells are initially white. To do this, you are given $ n $ stamps. Each stamp is a rectangle of width $ w_i $ and height $ h_i $ .

You will use each stamp exactly once to color a rectangle of the same size as the stamp on the grid in black. You cannot rotate the stamp, and for each cell, the stamp must either cover it fully or not cover it at all. You can use the stamp at any position on the grid, even if some or all of the cells covered by the stamping area are already black.

What is the minimum sum of the perimeters of the connected regions of black squares you can obtain after all the stamps have been used?

## 说明/提示

In the first test case, the stamps can be used as shown on the left. Each stamp is highlighted in its own color for clarity.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2027A/eb6eb9753bb0b7d5590d43612099263639e3e940.png)After all these stamps are used, there is one black region (as shown on the right), and its perimeter is $ 20 $ . It can be shown that there is no way of using the stamps that yields a lower total perimeter.

In the second test case, the second and third stamps can be used entirely inside the first one, so the minimum perimeter is equal to $ 8 $ .

## 样例 #1

### 输入

```
5
5
1 5
2 4
3 3
4 2
5 1
3
2 2
1 1
1 2
1
3 2
3
100 100
100 100
100 100
4
1 4
2 3
1 5
3 2```

### 输出

```
20
8
10
400
16```

# AI分析结果



# Rectangle Arrangement

## 题目描述

你正在给一个无限大的正方形网格涂色，所有单元格初始为白色。给定 $n$ 个矩形印章，每个印章的宽度为 $w_i$，高度为 $h_i$。

每个印章必须使用一次，在网格上以相同尺寸的黑色矩形覆盖。不能旋转印章，每个单元格必须被完全覆盖或不覆盖。印章可以放置在任意位置，即使覆盖区域已有黑色。

求所有印章使用完毕后，黑色连通区域的周长的最小总和。

## 说明/提示

第一个测试用例中，所有印章可以合并为一个连通块，周长为 $20$。第二个测试用例中，后两个印章完全覆盖在第一个内部，最小周长为 $8$。

---

### 综合分析与结论

**核心思路**：  
总周长的最小值为所有矩形中最大宽度和最大高度之和的两倍，即 $2 \times (\text{max\_width} + \text{max\_height})$。通过将所有矩形合理排列，使得最大矩形覆盖其他所有矩形，此时总周长仅由最大矩形决定。

**正确性验证**：  
所有样例均符合该规律，例如：
- 当最大矩形的尺寸为 $5 \times 5$ 时，周长为 $20$。
- 当最大矩形为 $100 \times 100$ 时，周长为 $400$。

**算法实现**：  
遍历所有矩形，记录最大宽度和最大高度，计算其和的二倍。

---

### 关键代码实现

```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, max_w = 0, max_h = 0;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int w, h;
            cin >> w >> h;
            max_w = max(max_w, w);
            max_h = max(max_h, h);
        }
        cout << 2 * (max_w + max_h) << endl;
    }
    return 0;
}
```

**实现思想**：  
直接遍历所有输入的矩形，维护最大宽度 `max_w` 和最大高度 `max_h`，最终输出两者之和的两倍。

---

### 相似题目推荐

1. **P1880 [NOI1995] 石子合并**  
   考察区间合并的最优化问题，与矩形覆盖的合并思想类似。
   
2. **P1090 [NOIP2004 提高组] 合并果子**  
   贪心策略选择最优合并顺序，与最小化周长的贪心思路相似。

3. **P1020 [NOIP1999 提高组] 导弹拦截**  
   寻找最长序列覆盖问题，涉及极值分析与优化。

---
处理用时：71.62秒