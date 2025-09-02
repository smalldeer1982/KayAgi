# 题目信息

# Rectangle Filling

## 题目描述

There is an $ n \times m $ grid of white and black squares. In one operation, you can select any two squares of the same color, and color all squares in the subrectangle between them that color.

Formally, if you select positions $ (x_1, y_1) $ and $ (x_2, y_2) $ , both of which are currently the same color $ c $ , set the color of all $ (x, y) $ where $ \min(x_1, x_2) \le x \le \max(x_1, x_2) $ and $ \min(y_1, y_2) \le y \le \max(y_1, y_2) $ to $ c $ .

This diagram shows a sequence of two possible operations on a grid:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1966B/d8e91236088d989799638772d594a0a137d702f1.png)Is it possible for all squares in the grid to be the same color, after performing any number of operations (possibly zero)?

## 说明/提示

In the first example, it is impossible to ever change the color of any square with an operation, so we output NO.

The second example is the case pictured above. As shown in that diagram, it is possible for all squares to be white after two operations, so we output YES.

In the third and fourth examples, all squares are already the same color, so we output YES.

In the fifth example we can do everything in two operations. First, select positions $ (2, 1) $ and $ (1, 4) $ and color all squares with $ 1 \le x \le 2 $ and $ 1 \le y \le 4 $ to white. Then, select positions $ (2, 1) $ and $ (3, 4) $ and color all squares with $ 2 \le x \le 3 $ and $ 1 \le y \le 4 $ to white. After these two operations all squares are white.

## 样例 #1

### 输入

```
8
2 1
W
B
6 6
WWWWBW
WBWWWW
BBBWWW
BWWWBB
WWBWBB
BBBWBW
1 1
W
2 2
BB
BB
3 4
BWBW
WBWB
BWBW
4 2
BB
BB
WW
WW
4 4
WWBW
BBWB
WWBB
BBBB
1 5
WBBWB```

### 输出

```
NO
YES
YES
YES
YES
NO
YES
NO```

# AI分析结果



### 综合分析与结论  
**题目核心**：通过矩形染色操作，判断能否将整个网格变为单一颜色。  
**核心贪心策略**：  
1. **对顶角同色优先**：若存在一组对顶角同色（如左上↔右下或右上↔左下），直接染全图。  
2. **四边覆盖策略**：若某颜色的格子覆盖了四条边（每边至少一个该颜色），则可通过多次操作逐步覆盖全图。  

**解决难点**：  
- 如何快速判断是否存在对顶角同色或四边覆盖条件。  
- 避免暴力枚举所有可能的染色路径，通过贪心性质简化判断逻辑。  

**可视化设计思路**：  
- **动画演示**：  
  - 步骤1：高亮对顶角，若同色则全图染色。  
  - 步骤2：若对顶角不同色，遍历四边格子，标记某颜色覆盖四条边的过程。  
  - 步骤3：模拟逐步扩展染色区域（如从四边向内合并）。  
- **复古像素风格**：用 8-bit 网格展示，每次操作时播放提示音效，自动步进演示染色过程。  

---

### 题解清单（≥4星）  
1. **yyz1005（4.5星）**  
   - **亮点**：直接判断四条边是否被同色覆盖，代码简洁高效。  
   - **关键代码**：遍历四边，统计每边是否存在目标颜色。  

2. **QoQ_（4星）**  
   - **亮点**：清晰的四边检查逻辑，代码结构简单易读。  
   - **关键代码**：用 `visw` 和 `visb` 数组标记四条边的颜色存在性。  

3. **Lame_Joke（4星）**  
   - **亮点**：通过双重循环统计四边颜色，逻辑直击贪心条件。  

---

### 最优思路与代码实现  
**核心逻辑**：  
```cpp
// 检查四条边是否被同一颜色覆盖
bool check_edges(char target) {
    bool left = false, right = false, top = false, bottom = false;
    for (int i = 1; i <= n; i++) {
        if (grid[i][1] == target) left = true;
        if (grid[i][m] == target) right = true;
    }
    for (int j = 1; j <= m; j++) {
        if (grid[1][j] == target) top = true;
        if (grid[n][j] == target) bottom = true;
    }
    return left && right && top && bottom;
}

// 主判断逻辑
if (corners_same || check_edges('W') || check_edges('B')) {
    cout << "YES" << endl;
} else {
    cout << "NO" << endl;
}
```

---

### 同类型题目与算法套路  
**贪心应用场景**：  
- **覆盖问题**：如区间覆盖、矩阵染色、最小操作次数等。  
- **关键性质发现**：通过观察操作特性，提取充分必要条件。  

**类似题目**：  
1. **CF1028C**（矩形覆盖最小次数）  
2. **洛谷 P1880**（区间合并）  
3. **LeetCode 1326**（灌溉花园的最少水龙头数目）  

---

### 可视化与游戏化设计  
**复古像素动画方案**：  
1. **Canvas 绘制**：  
   - 网格用 16x16 像素块表示，白色（#FFFFFF）和黑色（#000000）。  
   - 每次操作时，用高亮色（如红色）标记选择的两个角，染色区域渐变填充。  
2. **音效设计**：  
   - 选择格子时播放“哔”声，成功染色时播放“叮”声，错误操作时播放“嘟”声。  
3. **自动演示模式**：  
   - AI 自动检测四边条件，逐步染色并高亮当前操作区域。  

**交互示例**：  
```javascript
// 伪代码：自动演示四边覆盖策略
function autoPlay() {
    if (checkCorners()) {
        highlightCorners();
        fillEntireGrid();
    } else {
        highlightEdges('W');
        expandFromEdges();
    }
}
```

---

### 个人心得摘录  
- **yyz1005**：*“四条边的覆盖条件是此题的关键，避免陷入复杂操作路径的误区。”*  
- **Lame_Joke**：*“初次尝试暴力枚举所有可能，后来发现只需判断四边即可，思维跃迁很重要。”*  

---

### 总结  
本题通过贪心策略快速判断对顶角或四边条件，时间复杂度为 O(n+m)，适合大规模数据。可视化设计可直观展示覆盖过程，帮助理解贪心选择的本质。

---
处理用时：67.70秒