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



## 算法分类
贪心算法

## 综合分析与结论
### 核心思路与算法要点
本题的核心在于通过贪心策略发现：所有矩形叠加后的总周长的最小值等于所有矩形中最大宽度与最大高度的和的两倍。无论这些矩形如何排列，只要存在至少一个矩形的宽度等于最大宽度，且至少一个矩形的高度等于最大高度，总周长即可达到该值。

### 解决难点
- **数学规律推导**：观察样例发现，所有样例的答案均符合 `2*(max_w + max_h)`，需通过逻辑验证该规律的正确性。
- **重叠边优化**：矩形叠加后，内部重叠的边不计入总周长，外接矩形的边界边仅计算一次。

### 可视化设计思路
- **动画展示**：在Canvas中绘制每个矩形的位置，高亮最大宽度和最大高度的矩形，动态显示外接矩形的形成过程。
- **颜色标记**：用不同颜色区分当前处理的矩形，红色标出最大宽度的矩形，蓝色标出最大高度的矩形，黄色框表示外接矩形。
- **步进控制**：允许单步执行，展示如何逐步选择最大宽和最大高的矩形，最终形成外接矩形。

## 题解评分与清单
### 题解清单（5星）
1. **贪心策略求最大宽高**
   - **亮点**：直接遍历所有矩形，记录最大宽度和高度，时间复杂度为O(n)，代码简洁高效。
   - **评分**：★★★★★
   - **代码片段**：
     ```cpp
     int main() {
         int T;
         cin >> T;
         while (T--) {
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

## 最优思路提炼
关键思路：**总周长的最小值由最大宽度和最大高度决定**。通过贪心策略选择每个矩形的最大尺寸，确保所有矩形叠加后的外接矩形周长最小。

## 同类型题与类似套路
- **相似套路**：涉及几何覆盖问题时，常通过寻找最大/最小边界简化问题。
- **类似题目**：  
  1. **CF1118E - Rectangle Cutting**：通过分析矩形切割后的尺寸关系求解。  
  2. **LeetCode 963 - Minimum Area Rectangle II**：寻找最小面积覆盖矩形。  
  3. **洛谷 P1889 - 士兵站队**：通过中位数和极值优化排列。

## 推荐题目
1. [CF1118E - Rectangle Cutting](https://codeforces.com/problemset/problem/1118/E)  
2. [LeetCode 963 - Minimum Area Rectangle II](https://leetcode.com/problems/minimum-area-rectangle-ii/)  
3. [洛谷 P1889](https://www.luogu.com.cn/problem/P1889)

## 可视化与算法演示
- **动画方案**：Canvas绘制矩形叠加过程，高亮最大宽/高矩形，逐步形成外接矩形。
- **复古像素风**：使用8-bit风格渲染，音效提示最大宽/高的更新。
- **交互设计**：支持暂停/继续，调整动画速度，观察每一步的覆盖效果。

---

## 完整代码实现
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, max_w = 0, max_h = 0;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            int w, h;
            cin >> w >> h;
            if (w > max_w) max_w = w;
            if (h > max_h) max_h = h;
        }
        cout << 2 * (max_w + max_h) << endl;
    }
    return 0;
}
```

---
处理用时：424.22秒