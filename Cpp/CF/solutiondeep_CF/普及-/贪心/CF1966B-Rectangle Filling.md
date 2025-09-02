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



### 题目内容

#### 题目描述

有一个 $n \times m$ 的网格，每个格子为白色（W）或黑色（B）。每次操作可以选择两个颜色相同的格子作为对顶点，将其之间的子矩形内所有格子染成该颜色。判断是否可以通过若干次操作将所有格子染成同一颜色。

#### 说明/提示

- 若初始网格四个角存在对顶同色，则可以直接染成该颜色。
- 若四条边每条边都至少有一个同一颜色的格子，则可以通过多次操作覆盖整个网格。

---

### 题解综合分析与结论

**关键思路**：  
判断是否存在一种颜色（白或黑），使得该颜色在网格的四条边（左边、右边、上边、下边）上各至少出现一次。若满足，则可以统一颜色；否则无法达成。

**正确性证明**：  
1. **对顶同色**：若存在对顶同色的角，直接覆盖整个网格。  
2. **四条边条件**：若每条边都有同一颜色的格子，可以通过逐步覆盖横向和纵向区域，最终统一颜色。

---

### 高星题解推荐

#### 题解作者：yyz1005（5星）
**关键亮点**：  
- 思路简洁直接，通过遍历四条边判断是否存在同一颜色。
- 代码高效，时间复杂度为 $O(nm)$，适用于大网格。

**核心代码**：  
```cpp
// 检查四条边是否存在同一颜色的格子
for (int i = 1; i <= n; i++) {
    if (a[i][1] == 'W') cnt1[0] = 1; // 左边是否有白
    if (a[i][m] == 'W') cnt1[1] = 1; // 右边是否有白
    ...
}
for (int i = 1; i <= m; i++) {
    if (a[1][i] == 'W') cnt1[2] = 1; // 上边是否有白
    if (a[n][i] == 'W') cnt1[3] = 1; // 下边是否有白
    ...
}
// 若白色或黑色满足四条边条件，输出YES
if (cnt1所有标志为1 || cnt2所有标志为1) YES;
```

#### 题解作者：Lame_Joke（4.5星）
**关键亮点**：  
- 代码结构清晰，通过标记数组简化逻辑。
- 直接遍历所有边上的点，无需处理顶点特殊情况。

**核心代码**：  
```cpp
// 遍历所有边上的点，标记颜色存在性
for (int i = 1; i <= n; i++) {
    if (a[i][1] == 'W') w_left = 1;
    if (a[i][m] == 'B') b_right = 1;
    ...
}
// 判断是否四条边均存在某颜色
if (w的四边标记全为1 || b的四边标记全为1) YES;
```

#### 题解作者：QoQ_（4星）
**关键亮点**：  
- 代码实现直观，通过四个循环分别处理四条边。
- 变量命名清晰，便于理解逻辑。

**核心代码**：  
```cpp
// 检查四条边的颜色分布
for (int i = 1; i <= n; i++) {
    if (a[i][1] == 'W') temp[0] = true;
    if (a[i][m] == 'W') temp[1] = true;
    ...
}
for (int i = 1; i <= m; i++) {
    if (a[1][i] == 'W') temp[2] = true;
    if (a[n][i] == 'W') temp[3] = true;
    ...
}
// 判断是否满足全边条件
if (temp或cmpb全为true) YES;
```

---

### 最优思路总结
**核心技巧**：  
1. **边覆盖法**：通过检查四条边是否各存在至少一个目标颜色点，确保可以通过多次矩形覆盖操作统一颜色。  
2. **直接遍历**：无需处理顶点特殊情形，直接遍历每条边的所有格子，标记颜色存在性。

**拓展思路**：  
- 类似问题可转化为对边界的覆盖性检查，例如连通性判断或区域覆盖问题。
- 适用于网格操作的题目，如染色、连通块扩展等。

---

### 相似题目推荐
1. **P1162 填涂颜色**：通过边界扩展染色。  
2. **P1501 矩阵覆盖**：利用矩形操作覆盖网格。  
3. **P2895 [USACO08FEB] Meteor Shower S**：基于网格的广度优先搜索与状态覆盖。

---
处理用时：238.35秒