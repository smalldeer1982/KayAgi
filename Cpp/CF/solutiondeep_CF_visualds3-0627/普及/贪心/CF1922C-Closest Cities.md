# 题目信息

# Closest Cities

## 题目描述

There are $ n $ cities located on the number line, the $ i $ -th city is in the point $ a_i $ . The coordinates of the cities are given in ascending order, so $ a_1 < a_2 < \dots < a_n $ .

The distance between two cities $ x $ and $ y $ is equal to $ |a_x - a_y| $ .

For each city $ i $ , let's define the closest city $ j $ as the city such that the distance between $ i $ and $ j $ is not greater than the distance between $ i $ and each other city $ k $ . For example, if the cities are located in points $ [0, 8, 12, 15, 20] $ , then:

- the closest city to the city $ 1 $ is the city $ 2 $ ;
- the closest city to the city $ 2 $ is the city $ 3 $ ;
- the closest city to the city $ 3 $ is the city $ 4 $ ;
- the closest city to the city $ 4 $ is the city $ 3 $ ;
- the closest city to the city $ 5 $ is the city $ 4 $ .

The cities are located in such a way that for every city, the closest city is unique. For example, it is impossible for the cities to be situated in points $ [1, 2, 3] $ , since this would mean that the city $ 2 $ has two closest cities ( $ 1 $ and $ 3 $ , both having distance $ 1 $ ).

You can travel between cities. Suppose you are currently in the city $ x $ . Then you can perform one of the following actions:

- travel to any other city $ y $ , paying $ |a_x - a_y| $ coins;
- travel to the city which is the closest to $ x $ , paying $ 1 $ coin.

You are given $ m $ queries. In each query, you will be given two cities, and you have to calculate the minimum number of coins you have to spend to travel from one city to the other city.

## 说明/提示

Let's consider the first two queries in the example from the statement:

- in the first query, you are initially in the city $ 1 $ . You can travel to the closest city (which is the city $ 2 $ ), paying $ 1 $ coin. Then you travel to the closest city (which is the city $ 3 $ ) again, paying $ 1 $ coin. Then you travel to the closest city (which is the city $ 4 $ ) again, paying $ 1 $ coin. In total, you spend $ 3 $ coins to get from the city $ 1 $ to the city $ 4 $ ;
- in the second query, you can use the same way to get from the city $ 1 $ to the city $ 4 $ , and then spend $ 5 $ coins to travel from the city $ 4 $ to the city $ 5 $ .

## 样例 #1

### 输入

```
1
5
0 8 12 15 20
5
1 4
1 5
3 4
3 2
5 1```

### 输出

```
3
8
1
4
14```

# AI分析结果



### 综合分析与结论

**题目核心**：在数轴上设计最小费用路径，每次移动可选择支付 1 硬币（前往最近城市）或实际距离费用。  
**贪心策略**：每一步优先选择费用最低的移动方式（能走 1 硬币的最近城市则必选）。  
**关键难点**：如何高效预处理各城市的最近城市，并快速回答多组查询。  
**解决方案**：预处理两个方向（左→右、右→左）的前缀和数组，查询时直接做差值。

---

### 题解清单（≥4星）

1. **__zhuruirong__（4.5星）**  
   - **亮点**：清晰预处理 `nxt` 数组标记每个城市的最近邻居，逻辑简洁，代码易移植。  
   - **代码**：通过 `pre` 和 `suf` 数组分别处理两个方向的前缀和，直接差值输出结果。

2. **Crazyouth（4星）**  
   - **亮点**：用 `nc` 数组存储最近城市，前缀和计算逻辑紧凑。  
   - **个人心得**：强调预处理的重要性，避免暴力遍历导致 TLE。

3. **UncleSam_Died（4星）**  
   - **亮点**：代码极简，`sum` 和 `suf` 数组命名直观，边界处理明确。  
   - **技巧**：直接比较左右距离确定最近城市，无冗余操作。

---

### 最优思路与技巧提炼

1. **贪心选择依据**：每个城市移动时，优先选择费用为 1 的最近城市。  
2. **预处理数组**：  
   - 从左到右累加 `pre[i]`：若当前城市的最近邻居是右侧，费用加 1，否则加实际距离。  
   - 从右到左累加 `suf[i]`：同理处理左侧邻居。  
3. **查询优化**：利用前缀和数组在 O(1) 时间内回答任意区间查询。

**关键代码片段**（以 __zhuruirong__ 为例）：
```cpp
// 预处理最近城市
for(int i = 1; i <= n; i++) {
    if (i == 1) nxt[i] = 2;
    else if (i == n) nxt[i] = n-1;
    else nxt[i] = (a[i]-a[i-1] < a[i+1]-a[i]) ? i-1 : i+1;
}

// 构建前缀和
for(int i = 1; i <= n; i++) {
    if (nxt[i] == i+1) pre[i+1] = pre[i] + 1;
    else pre[i+1] = pre[i] + (a[i+1] - a[i]);
}

// 查询处理
cout << (l <= r ? pre[r] - pre[l] : suf[r] - suf[l]);
```

---

### 同类型题目与算法套路

- **常见场景**：数轴或单向路径的最优费用/时间问题。  
- **通用解法**：预处理前缀和或动态规划，利用贪心性质减少状态转移复杂度。  
- **类似题目**：  
  1. [CF1922C](https://codeforces.com/problemset/problem/1922/C)（本题）  
  2. [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)（路径和预处理）  
  3. [P1091 跳木桩](https://www.luogu.com.cn/problem/P1091)（贪心选择跳跃策略）

---

### 可视化与复古游戏化设计

**核心动画逻辑**：  
1. **数轴绘制**：用 Canvas 绘制城市坐标点，标注编号和费用策略。  
2. **贪心选择高亮**：当前城市闪烁，箭头指向最近城市（绿色）或普通方向（红色）。  
3. **费用累加**：每次移动显示费用，并更新前缀和数组的数值。  

**复古像素风格**：  
- **颜色方案**：城市用 8-bit 像素点（绿-最近，红-普通），背景深蓝。  
- **音效设计**：  
  - 移动选择：`1` 硬币时播放高音“哔”，距离费用时低音“嘟”。  
  - 通关提示：8-bit 胜利音效。  

**交互功能**：  
- **步进控制**：空格键单步执行，观察前缀和如何累积。  
- **自动演示**：AI 自动播放最优路径，辅以动态箭头和音效。  

---

**总结**：本题通过贪心预处理和前缀和优化，高效解决多组查询。可视化设计结合复古元素，强化对贪心策略和预处理机制的理解。

---
处理用时：141.53秒