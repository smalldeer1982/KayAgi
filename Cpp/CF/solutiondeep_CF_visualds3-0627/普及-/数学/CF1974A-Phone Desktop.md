# 题目信息

# Phone Desktop

## 题目描述

Little Rosie has a phone with a desktop (or launcher, as it is also called). The desktop can consist of several screens. Each screen is represented as a grid of size $ 5 \times 3 $ , i.e., five rows and three columns.

There are $ x $ applications with an icon size of $ 1 \times 1 $ cells; such an icon occupies only one cell of the screen. There are also $ y $ applications with an icon size of $ 2 \times 2 $ cells; such an icon occupies a square of $ 4 $ cells on the screen. Each cell of each screen can be occupied by no more than one icon.

Rosie wants to place the application icons on the minimum number of screens. Help her find the minimum number of screens needed.

## 说明/提示

The solution for the first test case can look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974A/50fee263eb8faff81a1a0ba84255a68bc5871ae1.png) Blue squares represent empty spaces for icons, green squares represent $ 1 \times 1 $ icons, red squares represent $ 2 \times 2 $ iconsThe solution for the third test case can look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974A/53e483ebe35e12a51af69c31e4cb0b1e5b05aee6.png)

## 样例 #1

### 输入

```
11
1 1
7 2
12 4
0 3
1 0
8 1
0 0
2 0
15 0
8 2
0 9```

### 输出

```
1
1
2
2
1
1
0
1
1
2
5```

# AI分析结果



---

## 唯一算法分类
组合数学

---

## 综合分析与结论

### 核心思路
通过数学建模分析，问题的解由两个关键条件共同决定：
1. **2x2图标的布局限制**：每个屏幕最多容纳2个2x2图标，需至少 `ceil(y/2)` 个屏幕。
2. **总空间需求**：所有图标的面积总和为 `x + 4y`，需至少 `ceil((x+4y)/15)` 个屏幕。

最终答案为二者的最大值，即 `max(ceil(y/2), ceil((x+4y)/15))`。

### 数学推导
1. **布局限制分析**：5x3的屏幕最多放2个2x2图标（每个占4格，且无法并排第三个）。
2. **面积计算**：总需求面积为 `x + 4y`，每个屏幕总空间为15格。
3. **公式联立**：取两种条件的最严格值，确保同时满足布局和空间需求。

### 可视化设计
1. **像素化动态演示**：在Canvas中以5x3网格动态填充图标，用不同颜色区分1x1和2x2图标。
2. **步骤高亮**：逐步放置图标时，当前操作的区域用闪烁边框标记，剩余空间实时更新。
3. **公式同步显示**：右侧面板实时计算并展示 `ceil(y/2)` 和 `ceil((x+4y)/15)` 的过程，比较后显示最终结果。

---

## 最优思路与技巧提炼
- **关键公式**：`max(ceil(y/2), ceil((x+4y)/15))`，解决布局限制与面积需求的矛盾。
- **优化思维**：通过数学建模将复杂布局问题转化为数值比较，避免复杂模拟。
- **实现技巧**：利用整数运算技巧（如 `(y+1)//2` 计算上取整）简化代码。

---

## 代码实现
```cpp
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;
        int screens_for_y = (y + 1) / 2;
        int total_area = x + 4 * y;
        int screens_for_area = (total_area + 14) / 15;
        cout << max(screens_for_y, screens_for_area) << endl;
    }
    return 0;
}
```

---

## 同类型题与拓展
1. **资源分配问题**：如背包问题中考虑体积和重量双重限制。
2. **二维装箱问题**：将不同大小的物品放入固定尺寸的箱子，最小化箱子数量。
3. **组合优化**：通过数学建模简化多维约束问题。

---

## 相似题目推荐
1. **P1044** - 装箱问题（一维空间优化）
2. **P1059** - 纪念品分组（双指针贪心）
3. **P1094** - 矩形覆盖（几何排列）

---

## 可视化与游戏化设计
### 像素动画实现
- **网格绘制**：用Canvas绘制5x3网格，每个单元格为20x20像素。
- **图标放置动画**：2x2图标用红色填充，1x1用绿色，放置时播放8-bit音效。
- **公式跟踪面板**：右侧显示当前y和总面积的屏幕需求，动态比较并高亮最大值。

### 游戏化元素
- **自动演示模式**：AI自动填入测试用例，逐步展示计算过程。
- **得分系统**：根据解题速度和正确率累计积分，解锁不同像素主题。

---

通过数学建模与像素化动态演示的结合，直观呈现组合优化问题的核心逻辑，提升理解与记忆。

---
处理用时：221.19秒