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



---

## 算法分类
**前缀和/预处理**

---

## 题解思路与核心难点

### 核心思路
题目要求计算两点间的最小移动费用，关键在于预处理两个方向（从左到右、从右到左）的前缀和数组。每个位置的费用取决于是否选择“最近城市”的移动方式：  
1. **预处理最近城市**：对每个城市，判断其最近城市是左还是右（距离更小的方向）。
2. **构建前缀和数组**：  
   - `pre[i]` 表示从城市1到城市i的总费用。若从城市i-1到i的移动选择最近城市（费用1），否则支付实际距离费用。  
   - `suf[i]` 表示从城市n到城市i的总费用，逻辑与`pre`对称。  
3. **查询处理**：根据起点和终点的位置关系，取对应前缀和的差值。

### 解决难点
- **正确预处理最近城市**：需处理边界条件（如首尾城市只能单向移动），并保证距离唯一性。  
- **前缀和数组的索引对齐**：确保数组索引与城市编号对应，避免偏移错误。  
- **时间复杂度优化**：预处理O(n)，查询O(1)，避免每次遍历计算。

---

## 题解评分（≥4星）

1. **__zhuruirong__（5星）**  
   - 思路清晰，预处理`nxt`数组明确每个城市的移动方向。  
   - 前缀和数组`pre`和`suf`的构建逻辑简洁，代码高效。  
   - 边界处理正确，如首尾城市的特殊处理。

2. **Crazyouth（4星）**  
   - 代码简洁，直接通过条件判断构建前缀和数组。  
   - 变量命名简洁（`sum1`, `sum2`），逻辑直观。  
   - 处理索引偏移正确，适合快速理解。

3. **Jerry_heng（4星）**  
   - 明确区分从左到右和从右到左的预处理逻辑。  
   - 代码注释清晰，边界条件处理到位。  
   - 前缀和累加方式直接，可读性强。

---

## 最优思路与技巧

### 关键技巧
1. **贪心选择最近城市**：每一步优先选择费用为1的移动，减少总费用。  
2. **前缀和优化**：通过预处理将路径费用转化为数组差值，实现O(1)查询。  
3. **双向预处理**：分别处理从左到右和从右到左的移动，覆盖所有查询方向。

### 代码实现片段
```cpp
// 预处理最近城市数组nxt[]
for (int i = 1; i <= n; i++) {
    if (i == 1) nxt[i] = 2;
    else if (i == n) nxt[i] = n - 1;
    else {
        if (a[i] - a[i-1] < a[i+1] - a[i]) 
            nxt[i] = i + 1;
        else 
            nxt[i] = i - 1;
    }
}

// 构建前缀和数组pre[]
pre[1] = 0;
for (int i = 1; i <= n; i++) {
    if (nxt[i] == i + 1)
        pre[i+1] = pre[i] + 1;
    else 
        pre[i+1] = pre[i] + (a[i+1] - a[i]);
}

// 查询处理
if (l <= r) 
    cout << pre[r] - pre[l] << endl;
else 
    cout << suf[r] - suf[l] << endl;
```

---

## 相似题目与算法套路

1. **前缀和优化路径问题**：如[洛谷P1219 八皇后](https://www.luogu.com.cn/problem/P1219)（路径计数）。  
2. **贪心选择最优子结构**：如[CF474D Flowers](https://codeforces.com/problemset/problem/474/D)（每一步选择影响全局）。  
3. **双向预处理**：如[LeetCode 42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)（左右最大值预处理）。

---

## 可视化设计

### 动画方案
1. **数轴展示**：用水平数轴标注城市坐标，高亮当前处理的城市。  
2. **前缀和更新**：动态显示`pre`和`suf`数组的累加过程，颜色标记“1费用”和“实际距离费用”。  
3. **查询模拟**：用箭头表示移动路径，实时显示总费用差值。

### 复古像素风格
- **8位网格**：城市用不同颜色方块表示，移动路径用闪烁像素线连接。  
- **音效设计**：  
  - 移动时播放“哔”声（8-bit音效）。  
  - 预处理完成时播放胜利音效。  
- **自动演示**：按空格键切换手动/自动模式，自动逐步显示预处理步骤。

---

## 个人心得摘录
- **预处理索引对齐**：调试中发现`pre`数组索引偏移错误，需多次验证边界条件。  
- **贪心正确性**：最初尝试动态规划，但贪心选择已被题目条件保证最优，无需复杂状态转移。

---
处理用时：183.68秒