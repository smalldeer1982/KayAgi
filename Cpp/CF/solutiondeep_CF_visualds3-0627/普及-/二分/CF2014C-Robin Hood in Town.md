# 题目信息

# Robin Hood in Town

## 题目描述

In Sherwood, we judge a man not by his wealth, but by his merit.



Look around, the rich are getting richer, and the poor are getting poorer. We need to take from the rich and give to the poor. We need Robin Hood!

There are $ n $ people living in the town. Just now, the wealth of the $ i $ -th person was $ a_i $ gold. But guess what? The richest person has found an extra pot of gold!

More formally, find an $ a_j=max(a_1, a_2, \dots, a_n) $ , change $ a_j $ to $ a_j+x $ , where $ x $ is a non-negative integer number of gold found in the pot. If there are multiple maxima, it can be any one of them.

A person is unhappy if their wealth is strictly less than half of the average wealth $ ^{\text{∗}} $ .

If strictly more than half of the total population $ n $ are unhappy, Robin Hood will appear by popular demand.

Determine the minimum value of $ x $ for Robin Hood to appear, or output $ -1 $ if it is impossible.

 $ ^{\text{∗}} $ The average wealth is defined as the total wealth divided by the total population $ n $ , that is, $ \frac{\sum a_i}{n} $ , the result is a real number.

## 说明/提示

In the first test case, it is impossible for a single person to be unhappy.

In the second test case, there is always $ 1 $ happy person (the richest).

In the third test case, no additional gold are required, so the answer is $ 0 $ .

In the fourth test case, after adding $ 15 $ gold, the average wealth becomes $ \frac{25}{4} $ , and half of this average is $ \frac{25}{8} $ , resulting in $ 3 $ people being unhappy.

In the fifth test case, after adding $ 16 $ gold, the average wealth becomes $ \frac{31}{5} $ , resulting in $ 3 $ people being unhappy.

## 样例 #1

### 输入

```
6
1
2
2
2 19
3
1 3 20
4
1 2 3 4
5
1 2 3 4 5
6
1 2 1 1 1 25```

### 输出

```
-1
-1
0
15
16
0```

# AI分析结果



## 算法分类选择
**二分**

---

## 题解思路、算法要点与解决难点

### 核心思路
题目要求找到最小的非负整数 $x$，使得在给最富有的人增加 $x$ 后，超过一半的人的财富严格小于平均财富的一半。关键点在于如何高效判断不同 $x$ 是否满足条件。

### 解法对比
#### 二分法（如 Temp113 的题解）
1. **搜索区间**：初始区间为 $[0, 10^{18}]$，利用答案的单调性（若 $x$ 可行，则更大的 $x$ 也可行）。
2. **验证条件**：对每个 $x$，修改最大值后计算总财富 $sum+x$，统计有多少人的财富严格小于 $\frac{sum+x}{2n}$。
3. **收缩区间**：若满足条件（超过半数不快乐），则尝试更小的 $x$（右边界左移）；否则增大 $x$（左边界右移）。
4. **复杂度**：$O(n \log n + n \log x)$，其中 $x$ 的二分次数约为 $\log_2(10^{18}) \approx 60$。

#### 数学推导（如 Karieciation 的题解）
1. **排序与中位数**：将数组排序后，取第 $k = \lfloor n/2 \rfloor +1$ 位的元素 $a_k$。
2. **条件推导**：要求 $a_k < \frac{sum +x}{2n}$，解得 $x > 2n \cdot a_k - sum$。若原 $sum \ge 2n \cdot a_k$，则 $x=0$ 即可；否则 $x = 2n \cdot a_k - sum +1$。
3. **复杂度**：$O(n \log n)$（仅需排序一次）。

### 解决难点
- **二分法**：需正确维护最大值的位置（排序后最大值在末尾），并在验证时不破坏原数组。
- **数学法**：需严格证明中间元素的条件能覆盖超过半数的人，并处理边界情况（如 $sum = 2n \cdot a_k$ 时需 $x \ge 1$）。

---

## 题解评分 (≥4星)
1. **Karieciation 的题解（5星）**
   - **亮点**：通过数学推导直接计算答案，时间复杂度最优，代码简洁。
   - **代码**：排序后取中间元素，推导 $x$ 的最小值。
2. **alan1118 的题解（5星）**
   - **亮点**：与数学推导一致，正确处理边界条件，代码高效。
3. **Temp113 的题解（4星）**
   - **亮点**：直观的二分思路，代码可读性强，适用于通用场景。

---

## 最优思路或技巧提炼
1. **数学推导法**：
   - 排序后取中间元素 $a_k$，保证至少前 $k$ 个元素满足条件。
   - 推导 $x$ 的公式：$x = \max(0, 2n \cdot a_k - sum +1)$。
2. **边界处理**：
   - 特判 $n \leq 2$ 时无解。
   - 确保 $x \ge 0$，避免负数。

---

## 同类型题或类似算法套路
1. **中位数性质**：利用排序后的中间元素作为分界点（如快速选择算法）。
2. **二分答案**：当问题具有单调性时，通过二分快速逼近解（如最大值最小化问题）。

---

## 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)  
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
3. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)

---

## 个人心得摘录
- **调试教训**：必须开 `long long` 避免溢出（多个题解强调）。
- **思维顿悟**：中间元素的严格小于条件能保证超过半数的人不快乐。

---

## 可视化与算法演示（二分过程）
### 动画方案
1. **初始化**：显示排序后的数组，高亮最大值和中间元素。
2. **二分步骤**：
   - 显示当前搜索区间 $[L, R]$ 和 $mid$。
   - 用红色标记满足条件的区间收缩方向（左移右边界或右移左边界）。
3. **条件验证**：
   - 动态计算 $sum + mid$ 和半平均线 $\frac{sum + mid}{2n}$。
   - 用颜色区分满足条件的元素（绿色）和不满足的（红色）。
4. **终止条件**：当 $L > R$ 时，高亮最终的 $ans$。

### 复古像素风格设计
- **界面**：8-bit 风格，数组元素以像素方块展示，区间变化伴随经典音效。
- **音效**：更新 $mid$ 时播放“哔”声，找到答案时播放胜利音效。

---

## 核心代码片段（数学推导法）
```cpp
sort(a + 1, a + n + 1);
ll k = a[(n >> 1) + 1];
ll required = 2 * n * k;
if (sum >= required) cout << 0 << endl;
else cout << required - sum + 1 << endl;
```

---

## 总结
本题通过数学推导找到中间元素的条件，直接计算最小 $x$，时间复杂度最优。二分法虽然普适，但数学方法更高效。两种思路均需注意边界条件和数据类型溢出。

---
处理用时：297.51秒