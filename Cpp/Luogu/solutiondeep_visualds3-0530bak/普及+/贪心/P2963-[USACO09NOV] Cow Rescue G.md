# 题目信息

# [USACO09NOV] Cow Rescue G

## 题目描述

Bessie is trapped in a triangular maze with N rows (1 <= N <= 1,000,000). A three row maze is shown below:

The i'th row of the maze contains 2\*i-1 triangles. Numbering from the left, the triangles are named (i,1), (i,2), and so on.

Bessie can travel to the (often three) triangles which share an edge with her current triangle. For example, if she is at (3, 3), she can travel to (3, 2), (3, 4) and (4, 4). Bessie takes one minute to travel from one triangle to the next.

FJ has learned the Bessie is trapped and knows by tracking her iPhone that she starts her exit trek at triangle (Si,Sj). FJ's love for Bessie knows no bounds so he wants her back in the minimum possible time.

The maze has M (1 <= M <= 10,000) exits found in locations throughout the set of triangles. Any one of these will enable Bessie to escape. Once she enters an exit triangle, she leaves the maze in just one more minute.

Find the minimum time in minutes, T, required for Bessie to exit the maze and report the optimal exit location she uses, (OUTi, OUTj). If more than one location requires only T minutes, output the location with the smallest row. If two optimal rows are the same, output the one with smaller column.

贝希被困在一个三角形的迷宫之中。这个迷宫有 $N$ 行（$1 \le N \le 1000000$）。比如下图是一个 $3$ 行的迷宫。  迷宫的第 $i$ 行有 $2i-1$ 个三角形，从左到右分别编号为 $(i, 1)$、$(i, 2)$ 等等。

贝希每次可以从一个三角形走到任意一个一个跟当前的三角形有邻边的三角形。

比如说，如果她目前处于三角形 $(3, 3)$，那么，她可以走到三角形 $(3, 2)$、$(3, 4)$ 和 $(4, 4)$。贝希每次需要一分钟的时间来移动到下一个三角形。

农夫约翰发现贝希被困了！于是她跟踪贝希的iPhone手机（可怜的触摸屏～），得知贝希目前处于三角形 $(S_i, S_j)$。

因为约翰对贝希有著无穷无尽的浓浓爱意，所以他希望贝希能尽可能快地回到他的身边。 在迷宫的三角形之中，有 $M$（$1 \le M \le 10000$）个是出口。在任何一个出口都可以让贝希逃离迷宫。一旦贝希进入一个作为出口的三角形，她用多一分钟就可以逃离这个迷宫。 找到一个可以让贝希逃离迷宫最小时间 $T$，并输出她应该从哪一个出口逃离迷宫，这个出口记为 $(\text{OUT}_i, \text{OUT}_j)$。

如果有多个出口同时需要时间 $T$，输出那个行的编号小的出口，如果仍然有多个出口，输出那个列的编号小的。


## 样例 #1

### 输入

```
4 2 
2 1 
3 5 
4 4 
```

### 输出

```
4 4 
4 
```

# AI分析结果



### 综合分析与结论  
本题目核心在于快速计算三角形迷宫中两点间的最短路径。由于数据规模庞大（N ≤ 1e6），传统 BFS 不可行，需通过数学建模推导出两点间距离的 O(1) 公式。各题解的核心思路均围绕几何规律展开，通过行差、列差及方向调整推导出最短路径长度，最终遍历所有出口取最小值。

#### 贪心策略与可视化设计  
- **贪心选择**：题解中未涉及典型贪心策略，但部分题解（如 zjo_2001）通过预处理对出口排序，确保在相同时间下优先选择字典序最小的出口，属于贪心的预处理策略。  
- **可视化设计**：  
  1. **动画方案**：展示三角形迷宫中每个出口的位置，动态计算其到起点的最短路径长度，用颜色梯度表示时间差异。  
  2. **高亮标记**：当前最优出口高亮显示，对比其他候选出口。  
  3. **复古像素风**：用 8-bit 像素风格绘制迷宫，贝希移动路径以闪烁动画呈现，音效提示最优解选择。

---

### 题解清单 (≥4星)  
1. **chenly8128（★★★★★）**  
   - **亮点**：公式推导清晰，代码简洁高效，时间复杂度 O(M)。通过行差、列差及方向调整因子直接计算最短路径。  
   - **心得**：特别注意出口需要额外加 1 分钟，避免遗漏。

2. **Tracy_Loght（★★★★☆）**  
   - **亮点**：区间判断法，通过行差生成列区间，快速计算是否需额外调整步数。  
   - **心得**：手绘规律图辅助理解，直观性强。

3. **zjo_2001（★★★★☆）**  
   - **亮点**：坐标转换与贪心排序，预处理出口按字典序排序，确保遍历时优先选择正确出口。  
   - **心得**：通过新坐标系简化移动方向分析。

---

### 最优思路与代码实现  
**核心思路**：将三角形迷宫抽象为几何模型，计算两点间行差（垂直移动次数）和列差（非垂直移动次数），结合方向调整因子，推导最短路径公式：  
`距离 = max(列差, 行差 - 1 + 方向调整) + 行差 + 1`  

**代码片段**（chenly8128 的关键逻辑）：  
```cpp
for (int j = 1; j <= m; j++) {
    cin >> ex[j] >> ey[j];
    sum = -1;
    // 计算方向调整因子 t
    if ((ey[j] & 1) ^ (ex[j] <= sx)) sum++;
    if (flag ^ (ex[j] >= sx)) sum++;
    sum += abs(ex[j] - sx); // 行差
    int k = abs(-ex[j] + ey[j] + sx - sy); // 列差
    sum = max(k, sum) + 1; // 总时间
    // 更新最优解
    if (sum < ans) { ... }
}
```

---

### 同类型题目与推荐  
1. **P1002 过河卒**：网格路径计数，需处理移动限制。  
2. **P1219 八皇后**：坐标转换与位置冲突判断。  
3. **CF1772C Different Differences**：区间构造与贪心选择。

---

### 可视化设计要点  
1. **像素风格**：用 Canvas 绘制三角形迷宫，起点与出口以不同颜色标记。  
2. **动态计算**：实时显示每个出口的时间计算过程，公式参数动态变化。  
3. **音效交互**：  
   - 发现更优解时播放上升音效。  
   - 最终确定答案时播放胜利音效。  
4. **自动演示**：AI 自动遍历所有出口，高亮当前最优解，步进速度可调。

---

**总结**：本题解法的核心在于几何建模与公式推导，通过数学优化将复杂度降至 O(M)。在类似网格路径问题中，寻找几何规律与方向调整因子是通用解题思路。

---
处理用时：163.29秒