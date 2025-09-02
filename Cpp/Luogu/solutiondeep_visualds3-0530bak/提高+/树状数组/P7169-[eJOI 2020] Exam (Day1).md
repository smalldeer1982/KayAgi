# 题目信息

# [eJOI 2020] Exam (Day1)

## 题目描述

给定一个长度为 $N$ 的序列 $A_i$，你可以进行无数次下面这个操作：

- 选定一个大小不小于 $2$ 的区间，使得这个区间里的数等于这个区间里的最大值。

你需要用这些操作使得 $A_i=B_i$，求最多能使得多少数满足要求。

## 说明/提示

#### 样例 1 解释

可以选择对区间 $[1,2]$ 进行操作，最多能有 $2$ 个数满足要求。

#### 样例 2 解释

$A_2$ 或 $A_3$ 能满足要求，但他们不能同时满足要求。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（14 pts）：$N \le 10$。
- Subtask 2（12 pts）：$N \le 10^5$，所有 $B_i$ 都相等。
- Subtask 3（13 pts）：$N \le 5000$，$A_i$ 为严格单调递增序列。
- Subtask 4（23 pts）：$N \le 10^5$，$A_i$ 两两不同。
- Subtask 5（16 pts）：$N \le 200$。
- Subtask 6（22 pts）：$N \le 5000$。

对于 $100\%$ 的数据：

- $2 \le N$。
- $1 \le A_i \le 10^9$。
- $1 \le B_i \le 10^9$。

#### 说明

翻译自 [eJOI 2020 Day1 C Exam](https://ejoi2020.ge/static/assets/Day1/Problems/Exam.pdf)。

## 样例 #1

### 输入

```
3
1 2 3
2 2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
4
10 1 9 1
10 9 10 9```

### 输出

```
3```

# AI分析结果



**唯一算法分类**  
动态规划 + 树状数组优化

---

### **题解思路与算法要点**

1. **核心观察**  
   - 每个位置 `i` 的 `B[i]` 必须等于某个区间的最大值，该区间的左端点 `L[i]` 或右端点 `R[i]` 必须满足：  
     - `A[L[i]] = B[i]` 或 `A[R[i]] = B[i]`  
     - 区间 `[L[i], i]` 或 `[i, R[i]]` 中的值均不超过 `B[i]`  
   - **关键难点**：如何快速找到合法的 `L[i]` 和 `R[i]`，并设计高效 DP 状态转移。

2. **预处理 L[i] 和 R[i]**  
   - **方法**：将 `A` 和 `B` 合并排序（降序优先，`A` 优先于 `B`），用 `set` 动态维护位置，二分查找最近的合法端点。  
   - **示例代码**（Lice 题解核心部分）：  
     ```cpp
     set<int> rec({0, n + 1});
     for (auto it : tmp) {
         if (it.second < 0) {
             int l = *rec.lower_bound(-it.second);
             if (A[l] == it.first) R[-it.second] = l;
             int r = *--rec.upper_bound(-it.second);
             if (A[r] == it.first) L[-it.second] = r;
         } else rec.insert(it.second);
     }
     ```

3. **动态规划优化**  
   - **状态设计**：树状数组维护前缀最大值，记录以某个端点结尾的最大可行数量。  
   - **转移方程**：  
     - `f(i, L[i]) = max(f(j ≤ L[i])) + 1`  
     - `f(i, R[i]) = max(f(j ≤ R[i])) + 1`  
   - **树状数组实现**：  
     ```cpp
     void upd(int p, int v) {
         for (; p <= n; p += p & -p) tr[p] = max(tr[p], v);
     }
     int get(int p) {
         int v = 0;
         for (; p; p -= p & -p) v = max(tr[p], v);
         return v;
     }
     ```

---

### **题解评分 (≥4星)**

1. **Lice（⭐⭐⭐⭐⭐）**  
   - **亮点**：预处理与树状数组实现简洁，代码可读性高；通过排序和 `set` 高效求 `L[i]/R[i]`。  
   - **优化**：树状数组直接维护前缀最大值，避免冗余状态。

2. **红火恍惚cxy（⭐⭐⭐⭐）**  
   - **亮点**：详细图解交叉线段的影响，辅助理解不相交约束；预处理部分代码清晰。  
   - **不足**：代码实现稍显冗长。

3. **xs_siqi（⭐⭐⭐⭐）**  
   - **亮点**：结合线段树与 ST 表验证 `L[i]/R[i]` 合法性，确保正确性。  
   - **优化**：双树维护 `L` 和 `R` 的 DP 状态。

---

### **最优思路提炼**

1. **预处理策略**  
   - 合并 `A` 和 `B` 数组按值降序排序，`set` 维护位置快速查找端点，时间复杂度 `O(n log n)`。

2. **树状数组优化 DP**  
   - 将状态转移转化为前缀最大值查询，树状数组单点更新和区间查询均为 `O(log n)`。

---

### **同类题目推荐**

1. **LeetCode 300. 最长递增子序列**  
   - 树状数组优化 LIS 的经典问题。

2. **洛谷 P1091 合唱队形**  
   - 双向 LIS 的变种，预处理左右端点。

3. **Codeforces 1313C2. Skyscrapers (hard version)**  
   - 单调栈预处理左右边界，动态规划求解。

---

### **可视化设计**

1. **动画演示**  
   - **步骤 1**：显示 `A` 和 `B` 数组，高亮当前处理的 `i` 和对应的 `L[i]/R[i]`（红色框标记）。  
   - **步骤 2**：树状数组更新时，动态绘制节点颜色渐变（黄色表示更新，绿色表示当前最大值）。  
   - **步骤 3**：最终结果以柱状图展示，绿色柱子表示成功匹配 `B[i]` 的位置。

2. **复古像素风格**  
   - **颜色方案**：8-bit 调色板（深蓝背景，亮绿/红色标记当前操作）。  
   - **音效**：树状数组更新时播放“滴”声，匹配成功时播放经典 FC 过关音效。

---

### **代码实现（核心逻辑）**

```cpp
// 预处理 L[i] 和 R[i]
vector<pair<int, int>> tmp(n * 2);
set<int> rec({0, n + 1});
for (int i = 1; i <= n; i++) tmp[i - 1] = {A[i], i};
for (int i = 1; i <= n; i++) tmp[i + n - 1] = {B[i], -i};
sort(tmp.begin(), tmp.end(), greater<pair<int, int>>());

for (auto it : tmp) {
    if (it.second < 0) {
        int l = *rec.lower_bound(-it.second);
        if (A[l] == it.first) R[-it.second] = l;
        int r = *--rec.upper_bound(-it.second);
        if (A[r] == it.first) L[-it.second] = r;
    } else rec.insert(it.second);
}

// 树状数组 DP
int tr[N];
for (int i = 1; i <= n; i++) {
    int l = get(L[i]), r = get(R[i]);
    if (L[i]) upd(L[i], l + 1);
    if (R[i]) upd(R[i], r + 1);
}
printf("%d\n", get(n));
```

---
处理用时：78.95秒