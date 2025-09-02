# 题目信息

# Turtle and a MEX Problem (Easy Version)

## 题目描述

The two versions are different problems. In this version of the problem, you can choose the same integer twice or more. You can make hacks only if both versions are solved.

One day, Turtle was playing with $ n $ sequences. Let the length of the $ i $ -th sequence be $ l_i $ . Then the $ i $ -th sequence was $ a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i} $ .

Piggy gave Turtle a problem to solve when Turtle was playing. The statement of the problem was:

- There was a non-negative integer $ x $ at first. Turtle would perform an arbitrary number (possibly zero) of operations on the integer.
- In each operation, Turtle could choose an integer $ i $ such that $ 1 \le i \le n $ , and set $ x $ to $ \text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}) $ .
- Turtle was asked to find the answer, which was the maximum value of $ x $ after performing an arbitrary number of operations.

Turtle solved the above problem without difficulty. He defined $ f(k) $ as the answer to the above problem when the initial value of $ x $ was $ k $ .

Then Piggy gave Turtle a non-negative integer $ m $ and asked Turtle to find the value of $ \sum\limits_{i = 0}^m f(i) $ (i.e., the value of $ f(0) + f(1) + \ldots + f(m) $ ). Unfortunately, he couldn't solve this problem. Please help him!

 $ ^{\dagger}\text{mex}(c_1, c_2, \ldots, c_k) $ is defined as the smallest non-negative integer $ x $ which does not occur in the sequence $ c $ . For example, $ \text{mex}(2, 2, 0, 3) $ is $ 1 $ , $ \text{mex}(1, 2) $ is $ 0 $ .

## 说明/提示

In the first test case, when $ x $ is initially $ 2 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}) = \text{mex}(2, 7, 0, 1, 5) = 3 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 3 $ , so $ f(2) = 3 $ .

It can be seen that $ f(0) = 3 $ , $ f(1) = 3 $ , $ f(2) = 3 $ , $ f(3) = 3 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16 $ .

In the second test case, when $ x $ is initially $ 1 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(1, 1, 3, 0, 3, 3) = 2 $ , and choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(2, 1, 3, 0, 3, 3) = 4 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 4 $ , so $ f(1) = 4 $ .

It can be seen that $ f(0) = 4 $ , $ f(1) = 4 $ , $ f(2) = 4 $ , $ f(3) = 4 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 4 + 4 + 4 + 4 = 20 $ .

In the fourth test case, it can be seen that $ f(0) = 3 $ and $ f(1) = 3 $ . So $ f(0) + f(1) = 3 + 3 = 6 $ .

## 样例 #1

### 输入

```
6
3 4
2 0 2
3 2 3 3
4 7 0 1 5
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
2 50
2 1 2
2 1 2
1 1
7 1 2 4 1 4 9 5
4 114514
2 2 2
5 7 3 6 0 3
3 0 1 1
5 0 9 2 1 5
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556```

### 输出

```
16
20
1281
6
6556785365
1842836177961```

# AI分析结果



### 综合分析与结论

**题目核心**：利用每个序列的次小 mex 的最大值，确定所有初始值 x 的 f(x) 最大值。通过两次操作同一序列可达到该序列的次小 mex，最终答案取决于所有序列中的最大次小 mex。

**贪心策略**：  
1. **关键点**：每个序列的次小 mex（即 mex 两次后的值）决定了其能提升 x 的上限。  
2. **正确性**：无论初始 x 如何，两次操作同一序列可将其提升至次小 mex，且无法通过其他操作获得更大值。  
3. **实现**：遍历所有序列，计算其次小 mex，取最大值作为全局上限。

**解决难点**：  
- 发现次小 mex 的决定性作用。  
- 证明无法通过多次操作其他序列突破该上限。

**可视化设计**：  
- **动画步骤**：  
  1. 展示每个序列的 mex 计算（高亮缺失的最小非负整数）。  
  2. 添加第一次 mex 结果，重新计算次小 mex（颜色区分两次计算）。  
  3. 比较所有次小 mex，标记最大值。  
- **复古像素风**：用不同颜色块表示 mex 值和次小 mex，音效提示关键步骤（如选中最大值时的上扬音效）。  
- **交互控制**：允许单步执行，观察每个序列的两次 mex 计算过程。

---

### 题解评分 (≥4星)

1. **Exp10re 的题解（5星）**  
   - **亮点**：简洁推导次小 mex 的决策作用，代码清晰高效。  
   - **引用**：“取 x = mex(x, a_p) 可得到 u_p 或 v_p” 直击核心。  

2. **Defy_HeavenS 的题解（4星）**  
   - **亮点**：详细分析操作序列后的状态转移，代码注释完整。  
   - **优化点**：代码中对 mex 的两次计算可进一步封装。

---

### 最优思路与代码实现

**核心思路**：  
1. 对每个序列计算两次 mex，取次小 mex 的最大值 `ma`。  
2. 求和公式：  
   - 若 `m ≤ ma`，总和为 `(m + 1) * ma`。  
   - 若 `m > ma`，总和为 `ma*(ma + 1) + (ma + 1 + m) * (m - ma) / 2`。

**关键代码（Exp10re）**：  
```cpp
for (LL i = 1; i <= n; i++) {
    set<LL> s;
    vector<int> cnt(n + 5, 0);
    for (int j = 0; j <= n + 2; j++) s.insert(j);
    for (auto val : a[i]) {
        if (val > n + 2) val = n + 2;
        if (!cnt[val]++) s.erase(val);
    }
    int u = *s.begin();
    if (!cnt[u]++) s.erase(u); // 添加第一次 mex 结果
    ans = max(ans, (LL)*s.begin()); // 取次小 mex
}
```

**完整代码**：见 Exp10re 的题解代码。

---

### 同类型题目与套路

**算法套路**：  
- **Mex 性质应用**：次小 mex 作为操作上限。  
- **贪心选择**：多选项中取最大增益。  

**相似题目**：  
1. [CF1527D Mex Tree](https://www.luogu.com.cn/problem/CF1527D)  
2. [CF1945E Mex and Update](https://codeforces.com/contest/1945/problem/E)  
3. [P4137 Rmq Problem / mex](https://www.luogu.com.cn/problem/P4137)

---

### 个人心得摘录

- **Exp10re**：强调两次 mex 操作的重要性，启发于 HD 版本的同性质。  
- **Defy_HeavenS**：通过分析操作后状态变化，简化问题至次小 mex 的决策。

---

### 复古游戏化动画设计

**实现要点**：  
1. **像素风格**：  
   - 序列元素用色块表示，mex 值用闪烁边框标记。  
   - 次小 mex 结果以绿色高亮，最大值用金色闪烁。  
2. **音效设计**：  
   - 计算 mex 时播放“滴”声，选中最大值时播放胜利音效。  
3. **自动演示**：  
   - AI 自动遍历所有序列，展示两次 mex 计算，最终输出总和公式。  
4. **交互关卡**：  
   - 第一关：计算单个序列的 mex。  
   - 第二关：计算次小 mex。  
   - 第三关：比较所有结果，计算总和。

**代码片段（JS 伪代码）**：  
```javascript
function calculateMex(arr) {
    let set = new Set(arr);
    let mex = 0;
    while (set.has(mex)) mex++;
    return mex;
}
// 展示每个序列的两次 mex 计算
```

---
处理用时：85.38秒