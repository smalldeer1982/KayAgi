# 题目信息

# [USACO09OPEN] Grazing2 S

## 题目描述

Farmer John has N (2 <= N <= 1,500) prize milk cows conveniently numbered 1..N. His newly-painted barn has S (N <= S <= 1,000,000) stalls (conveniently numbered 1..S) in a single long line; each stall is a unit distance from its neighboring stall(s).

The cows have made their way to the stalls for a rest; cow i is in stall P\_i. Antisocial as they are, the cows get grumpy if they are situated in stalls very close to each other, so Farmer John wants to move the cows to be as spread out as possible.

FJ wants to make sure that the N - 1 distances between adjacent cows are as large as possible, and he would also like them to be similar to each other (i.e., close to equi-distant spacing).

In particular, FJ would like all distances between adjacent cows to be at most 1 different from (S - 1) / (N - 1), where integer division is used. Moreover, he would like as many of these distances as possible to be exactly equal to (S - 1) / (N - 1) [integer

division]. Thus, with four cows and eight stalls, one can place the cows at positions 1, 3, 5, 8 or 1, 3, 6, 8 but not at 1, 2, 4, 7 or 1, 2, 4, 8.

Help FJ spread the cows as efficiently as possible by calculating and reporting the minimum total distance that the cows have to move in order to achieve proper spacing. Ignore the distance it takes for a cow to enter or exit a stall.

约翰有N(2≤N≤1500)头奶牛，S(N≤S≤1,000,000)个一字排开的牛棚．相邻牛棚间的距离恰好为1．

奶牛们已经回棚休息，第i只奶牛现在待在牛棚Pi．如果两只奶牛离得太近，会让奶牛们变得很暴躁．所以约翰想给一些奶牛换一个棚，让她们之间的距离变得尽量大，并且尽管接近．令d=Trunc((s-1)/(n-1))

所以约翰希望最终的奶牛的状态是：两只相邻奶牛间的距离与d之差不超过1，而且让尽量多的间距等于d．因此，对于4只奶牛8个棚的情况，1，3，5，8或1，3，6，8这样的安置情况是允许的，而1，2，4，7或1，2，4，8这样的情况是不允许的．    帮助约翰移动奶牛，让所有奶牛的移动距离之和最小，同时让最终的安置情况符合约翰心意．


## 说明/提示

1   2   3   4   5   6   7   8   9  10

Cow Locs     | A | B | C | . | . | . | . | D | E | . | 

Cows move from stall 2 to 3, 3 to 5, and 9 to 10. The total distance moved is 1 + 2 + 1 = 4. The final positions of the cows are in stalls 1, 3, 5, 8, and 10.

1   2   3   4   5   6   7   8   9  10

Init Stall     | A | B | C | . | . | . | . | D | E | . | 
Final Stall    | A | . | B | . | C | . | . | D | . | E | 
Distance moved | 0 | . | 1 | . | 2 | . | . | 0 | . | 1 | 

## 样例 #1

### 输入

```
5 10 
2 
8 
1 
3 
9 
```

### 输出

```
4 
```

# AI分析结果



**唯一算法分类**: 动态规划（DP）

---

### **题解思路、算法要点与解决难点**
**核心思路**：  
所有题解均采用动态规划，确定每头牛的最优位置，使得相邻间距为`d`或`d+1`。关键点包括：
1. **推导间距约束**：总间距数 `c2 = S-1 - (N-1)*d`，即 `d+1` 的个数。
2. **状态定义**：`dp[i][j]` 表示前 `i` 头牛中有 `j` 个间距为 `d+1` 的最小移动距离。
3. **状态转移**：第 `i` 头牛的位置由前一头牛的两种可能（间距 `d` 或 `d+1`）转移而来，即 `dp[i][j] = min(dp[i-1][j], dp[i-1][j-1]) + 移动距离`。
4. **初始条件**：第一头牛固定放在位置 `1`，移动代价为 `a[1]-1`。

**解决难点**：  
- 正确推导间距分布（`d` 和 `d+1` 的数量）。
- 动态规划状态转移方程的设计与实现，特别是如何通过 `j` 控制 `d+1` 的个数。
- 处理大范围数据时的空间优化（如滚动数组）。

---

### **题解评分 (≥4星)**
1. **Rainbow_qwq (⭐⭐⭐⭐⭐)**  
   - 思路清晰，代码简洁，初始化明确。
   - 状态转移方程推导正确，注释详细，适合新手理解。
   - 时间复杂度 `O(N^2)`，适用于题目数据范围。

2. **shadowice1984 (⭐⭐⭐⭐)**  
   - 引入滚动数组优化空间复杂度，代码更高效。
   - 倒序循环避免覆盖问题，但可读性稍差。
   - 通过平移坐标简化计算，实用性强。

3. **Elegy_of_Green_Kite (⭐⭐⭐⭐)**  
   - 详细解释状态转移的数学推导，适合深入理解。
   - 代码注释较少，但逻辑与主流解法一致。

---

### **最优思路或技巧提炼**
1. **动态规划状态压缩**：  
   - 使用二维数组 `dp[i][j]`，其中 `j` 表示 `d+1` 的个数，确保状态转移的合法性。
   - **关键公式**：第 `i` 头牛的位置为 `(i-1)*d + j`，与原位置差的绝对值为移动代价。

2. **滚动数组优化**：  
   - 仅保留前一行的状态，将空间复杂度从 `O(N^2)` 降为 `O(N)`。
   - 实现时需倒序遍历 `j`，避免覆盖未处理的状态。

3. **预处理与排序**：  
   - 必须对牛的初始位置排序，确保动态规划的正确性。

---

### **同类型题或类似算法套路**
- **相似问题类型**：  
  需要将元素按特定间距排列，并最小化移动代价的调度问题。
- **通用解法**：  
  动态规划结合数学推导，确定约束条件下的最优分布。

**推荐题目**：  
1. [P2893 USACO08FEB Making the Grade G](https://www.luogu.com.cn/problem/P2893)  
   （排序后动态规划处理最小代价）
2. [P4954 Tower of Hay](https://www.luogu.com.cn/problem/P4954)  
   （动态规划结合贪心策略）
3. [P2858 Treats for the Cows](https://www.luogu.com.cn/problem/P2858)  
   （区间动态规划与最优决策）

---

### **可视化与算法演示**
**核心算法动画方案**：  
1. **网格动态更新**：  
   - 用表格展示 `dp[i][j]` 的值，当前处理的 `(i, j)` 高亮为黄色。
   - 箭头标记转移来源（上方 `dp[i-1][j]` 和左上方 `dp[i-1][j-1]`）。

2. **牛的位置映射**：  
   - 在下方绘制一条数轴，动态显示第 `i` 头牛的最终位置 `(i-1)*d + j`，与原位置对比。

3. **复古像素风格**：  
   - 使用 8-bit 像素块表示牛棚，绿色块为初始位置，红色块为目标位置。
   - 音效：移动时播放短促“哔”声，更新最优解时播放胜利音效。

**交互设计**：  
- **控制面板**：暂停/继续、单步执行、调节速度。
- **自动模式**：AI 按最优路径自动填充表格，模拟算法决策过程。

---

### **代码实现（核心片段）**
```cpp
// 核心动态规划逻辑（Rainbow_qwq 题解）
sort(a + 1, a + n + 1);
int d = (s - 1) / (n - 1), c2 = s - 1 - (n - 1) * d;
memset(f, 0x3f, sizeof(f));
f[1][0] = a[1] - 1; // 初始化第一头牛的位置

for (int i = 2; i <= n; i++) {
    for (int j = 0; j <= min(c2, i); j++) {
        int pos = d * (i - 1) + j; // 计算目标位置
        int cost = abs(a[i] - pos);
        if (j == 0) f[i][j] = f[i - 1][j] + cost;
        else f[i][j] = min(f[i - 1][j], f[i - 1][j - 1]) + cost;
    }
}
cout << f[n][c2];
```

---

### **个人心得摘录**
- **排序必要性**：未排序直接计算会导致状态转移混乱，排序是正确性的关键。
- **边界处理**：`j` 的循环范围需严格限制为 `min(c2, i)`，避免无效状态。
- **调试技巧**：通过输出中间 `dp` 表，验证每一步的状态更新是否符合预期。

---
处理用时：108.81秒