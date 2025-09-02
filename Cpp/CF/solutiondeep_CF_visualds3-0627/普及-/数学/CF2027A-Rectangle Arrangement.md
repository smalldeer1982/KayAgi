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



---

**算法分类**  
几何

---

### 综合分析与结论  
本题核心在于如何通过合理排列矩形，使得所有覆盖区域的连通块总周长最小。关键在于发现：总周长的最小值等于所有矩形中最大宽度和最大高度的和的两倍。  

**关键公式推导**  
- 设所有矩形的最大宽度为 `max_w`，最大高度为 `max_h`，则最小总周长为 `2 * (max_w + max_h)`。  
- **证明思路**：存在至少一个矩形的宽度为 `max_w`，另一个高度为 `max_h`。将这两个矩形分别放置在坐标系中，覆盖足够大的区域，其他矩形可填充在内部或边缘，使得所有区域合并成一个连通块，其包围盒的周长即为所求。

**解决难点**  
- 需要发现周长仅由最大宽度和高度决定，与具体排列方式无关。  
- 正确性验证：无论其他矩形如何排列，总存在一种方式使得合并后的连通块尺寸为 `max_w × max_h`。

---

### 最优思路提炼  
1. **核心观察**：最终连通区域的周长仅由最大的宽度和高度决定。  
2. **实现步骤**：  
   - 遍历所有矩形，记录最大宽度 `max_w` 和最大高度 `max_h`。  
   - 直接计算 `2 * (max_w + max_h)` 即可得到答案。  
3. **数学本质**：通过覆盖最大尺寸的矩形，其他矩形填充其内部或边缘，确保所有区域连通。

---

### 代码实现  
```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int max_w = 0, max_h = 0;
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

---

### 同类型题目套路  
- **几何覆盖问题**：通常寻找极值（如最大/最小尺寸）来简化计算。  
- **合并区域优化**：通过观察覆盖后的形状特性（如包围盒）直接推导答案。

---

### 推荐相似题目  
1. **P2735 [USACO3.4] 网 Electric Fences**（几何覆盖与极值计算）  
2. **P1059 [NOIP2006 普及组] 明明的随机数**（极值统计与去重）  
3. **P2785 矩形覆盖**（几何覆盖与最优排列）  

---

### 可视化与算法演示  
**动画方案**：  
1. **像素风格画布**：用不同颜色绘制每个矩形，动态合并为一个大矩形。  
2. **高亮步骤**：  
   - 初始时所有矩形分散排列。  
   - 逐步将最大宽度和高度的矩形移动到坐标系原点，其他矩形填充到其内部。  
3. **音效提示**：当选中最大矩形时播放确认音效，最终合并完成时播放胜利音效。  

**复古游戏化设计**：  
- **8位像素风格**：用简单色块表示矩形，合并时显示包围盒边框。  
- **自动演示模式**：自动排列矩形，逐步展示合并过程。  

---

### 个人心得  
本题关键在于跳出具体排列方式的思维陷阱，转而观察极值特性。通过数学推导，直接锁定答案，避免了复杂的几何覆盖计算。

---
处理用时：139.40秒