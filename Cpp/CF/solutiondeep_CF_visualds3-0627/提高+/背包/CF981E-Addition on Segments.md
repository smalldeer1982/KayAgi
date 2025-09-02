# 题目信息

# Addition on Segments

## 题目描述

Grisha come to a contest and faced the following problem.

You are given an array of size $ n $ , initially consisting of zeros. The elements of the array are enumerated from $ 1 $ to $ n $ . You perform $ q $ operations on the array. The $ i $ -th operation is described with three integers $ l_i $ , $ r_i $ and $ x_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1 \leq x_i \leq n $ ) and means that you should add $ x_i $ to each of the elements with indices $ l_i, l_i + 1, \ldots, r_i $ . After all operations you should find the maximum in the array.

Grisha is clever, so he solved the problem quickly.

However something went wrong inside his head and now he thinks of the following question: "consider we applied some subset of the operations to the array. What are the possible values of the maximum in the array?"

Help Grisha, find all integers $ y $ between $ 1 $ and $ n $ such that if you apply some subset (possibly empty) of the operations, then the maximum in the array becomes equal to $ y $ .

## 说明/提示

Consider the first example. If you consider the subset only of the first query, the maximum is equal to $ 1 $ . If you take only the second query, the maximum equals to $ 2 $ . If you take the first two queries, the maximum becomes $ 3 $ . If you take only the fourth query, the maximum becomes $ 4 $ . If you take the fourth query and something more, the maximum becomes greater that $ n $ , so you shouldn't print it.

In the second example you can take the first query to obtain $ 1 $ . You can take only the second query to obtain $ 2 $ . You can take all queries to obtain $ 3 $ .

In the third example you can obtain the following maximums:

- You can achieve the maximim of $ 2 $ by using queries: $ (1) $ .
- You can achieve the maximim of $ 3 $ by using queries: $ (2) $ .
- You can achieve the maximim of $ 5 $ by using queries: $ (1, 2) $ .
- You can achieve the maximim of $ 6 $ by using queries: $ (3) $ .
- You can achieve the maximim of $ 8 $ by using queries: $ (1, 3) $ .
- You can achieve the maximim of $ 9 $ by using queries: $ (2, 3) $ .

## 样例 #1

### 输入

```
4 3
1 3 1
2 4 2
3 4 4
```

### 输出

```
4
1 2 3 4 
```

## 样例 #2

### 输入

```
7 2
1 5 1
3 7 2
```

### 输出

```
3
1 2 3 
```

## 样例 #3

### 输入

```
10 3
1 1 2
1 1 3
1 1 6
```

### 输出

```
6
2 3 5 6 8 9 
```

# AI分析结果



**算法分类**  
动态规划（背包问题变种）、线段树分治

---

**题解思路、算法要点与解决难点**  
**核心思路**：  
所有可能的y值由各位置的可能值取并集。每个位置的可能值由其覆盖的操作子集之和决定。两种主流解法：  
1. **动态规划+状态设计**：将问题转化为带条件的背包问题，状态记录最左/右端点以保证区间覆盖。  
2. **线段树分治+bitset**：利用线段树将操作分配到节点，遍历时合并bitset记录可能值，最终取并集。

**解决难点**：  
- **动态规划**：需保证操作的区间覆盖允许转移。通过排序和状态设计（如最左端点）实现条件转移。  
- **线段树分治**：高效处理每个位置的可能值，避免重复计算。利用bitset的位运算优化时间复杂度。

---

**题解评分 (≥4星)**  
1. **zhaoyp（5星）**：状态设计巧妙，代码简洁，时间复杂度分析清晰，适合竞赛实践。  
2. **一扶苏一（4星）**：线段树分治思路清晰，结合bitset高效处理，但代码稍复杂。  
3. **万弘（4星）**：与一扶苏一思路一致，代码更简洁，附详细解释。

---

**最优思路提炼**  
**动态规划状态设计**：  
- 状态定义：`f[j]`表示最大值j对应的最左端点位置。  
- 转移条件：若当前区间覆盖`f[j-x_i]`的位置，则更新`f[j]`为`max(f[j-x_i], l_i)`。  
- 排序优化：按左端点排序，倒序处理区间，确保转移的有效性。  
- 最终筛选：若`f[j] ≤ n`，则j为可行解。

**线段树分治+bitset**：  
- 将操作分配到线段树节点，每个节点维护覆盖该区间的操作集合。  
- 遍历线段树时，每个节点应用其操作集合的bitset或操作。  
- 叶子节点记录该位置的可能值，最终取所有叶子的并集。

---

**同类型题/算法套路**  
- **动态规划+区间覆盖**：适用于带条件的背包问题，如CF366C、洛谷P1156。  
- **线段树分治+bitset**：适合处理多区间影响下的集合运算，如CF1012C、洛谷P3730。

---

**推荐洛谷题目**  
1. P1776 宝物筛选（多重背包+二进制优化）  
2. P4095 [HEOI2013]Eden的背包问题（线段树分治应用）  
3. P3224 [HNOI2012]永无乡（并查集+线段树合并）

---

**可视化与算法演示**  
**动态规划过程动画设计**：  
- **网格展示**：纵轴为操作序号，横轴为可能的值j，每个格子表示`f[j]`的值。  
- **颜色标记**：  
  - 红色：当前处理的区间i。  
  - 绿色：可转移的状态`j-x_i`，其左端点≤当前区间的右端点。  
  - 蓝色：更新后的`f[j]`值。  
- **步进控制**：单步执行区间处理，显示状态转移的详细步骤。

**线段树分治可视化**：  
- **树形结构展示**：绘制线段树节点，每个节点显示其操作集合。  
- **bitset动态变化**：节点处理时，高亮当前应用的x值，展示bitset的或操作结果。  
- **叶子节点高亮**：最终合并所有叶子的bitset，用不同颜色标记有效y值。

---

**代码片段**  
**动态规划核心代码**（zhaoyp题解）：  
```cpp
void DP() {
    memset(f, 0x3f, sizeof(f));
    f[0] = 1;
    for (int i = m; i; i--)
        for (int j = n; j >= a[i].x; j--)
            if (f[j - a[i].x] <= a[i].r)
                f[j] = min(f[j], max(f[j - a[i].x], a[i].l));
}
```

**线段树分治核心代码**（万弘题解）：  
```cpp
void calc(const int o) {
    auto u = tree + o;
    for (auto p : u->opid) bt[o] |= bt[o] << op[p].x;
    if (u->ld) {
        bt[u->ld] = bt[u->rd] = bt[o];
        calc(u->ld); calc(u->rd);
    } else ans |= bt[o];
}
```

---

**复古游戏化设计**  
- **8位像素风格**：用16色块表示线段树节点，绿色表示有效操作，红色表示当前处理节点。  
- **音效设计**：  
  - 操作应用时播放“滴”声，bitset更新时播放“咔嚓”声。  
  - 叶子节点处理完成时播放上升音阶。  
- **AI自动演示**：自动遍历线段树，按中序展示处理流程，速度可调。

---
处理用时：137.90秒