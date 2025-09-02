# 题目信息

# Optimal Reduction

## 题目描述

Consider an array $ a $ of $ n $ positive integers.

You may perform the following operation:

- select two indices $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ), then
- decrease all elements $ a_l, a_{l + 1}, \dots, a_r $ by $ 1 $ .

Let's call $ f(a) $ the minimum number of operations needed to change array $ a $ into an array of $ n $ zeros.

Determine if for all permutations $ ^\dagger $ $ b $ of $ a $ , $ f(a) \leq f(b) $ is true.

 $ ^\dagger $ An array $ b $ is a permutation of an array $ a $ if $ b $ consists of the elements of $ a $ in arbitrary order. For example, $ [4,2,3,4] $ is a permutation of $ [3,2,4,4] $ while $ [1,2,2] $ is not a permutation of $ [1,2,3] $ .

## 说明/提示

In the first test case, we can change all elements to $ 0 $ in $ 5 $ operations. It can be shown that no permutation of $ [2, 3, 5, 4] $ requires less than $ 5 $ operations to change all elements to $ 0 $ .

In the third test case, we need $ 5 $ operations to change all elements to $ 0 $ , while $ [2, 3, 3, 1] $ only needs $ 3 $ operations.

## 样例 #1

### 输入

```
3
4
2 3 5 4
3
1 2 3
4
3 1 3 2```

### 输出

```
YES
YES
NO```

# AI分析结果



### 题目内容
# 最优递减操作

## 题目描述

给定一个由 $n$ 个正整数组成的数组 $a$，你可以执行如下操作：

- 选择两个下标 $l$ 和 $r$（$1 \leq l \leq r \leq n$），然后将所有元素 $a_l, a_{l+1}, \dots, a_r$ 减 $1$。

定义 $f(a)$ 为将数组 $a$ 变为全 $0$ 所需的最少操作次数。判断对于 $a$ 的所有排列 $b$，是否均有 $f(a) \leq f(b)$。

## 说明/提示

- 若 $a$ 的排列是单峰序列（先非严格递增再非严格递减），则其操作次数为所有排列中的最小值。
- 样例中的第一个输入 `2 3 5 4` 是单峰结构，因此输出 `YES`；第三个输入 `3 1 3 2` 存在更优排列，输出 `NO`。

---

### 题解分析与结论

#### 核心思路
**关键条件**：当且仅当原数组是单峰序列时，其操作次数是所有排列中的最小值。此时对于所有其他排列 $b$，$f(a) \leq f(b)$ 成立。

**判断方法**：
1. **单峰结构验证**：数组必须存在一个峰值，使得左侧非严格递增，右侧非严格递减。
2. **实现方式**：
   - 方法一：遍历数组，确保一旦开始下降后不允许再次上升。
   - 方法二：找到最大值的位置，检查其左右是否满足递增/递减条件。

#### 高分题解精选

1. **题解作者：Jeremiahy (★★★★★)**
   - **亮点**：直接找到最大值位置，分两段验证非递减/非递增，逻辑清晰且无冗余。
   - **核心代码**：
     ```cpp
     int ans = 1; // 最大值初始位置
     for (int i = 1; i <= n; i++) 
         if (a[i] > a[ans]) ans = i;
     // 检查左段递增
     for (int i = ans-1; i >= 1; i--)
         if (a[i] > a[i+1]) flag = 1;
     // 检查右段递减
     for (int i = ans+1; i <= n; i++)
         if (a[i] > a[i-1]) flag = 1;
     puts(flag ? "NO" : "YES");
     ```

2. **题解作者：Epi4any (★★★★★)**
   - **亮点**：单次遍历动态判断是否出现二次上升，时间复杂度 $O(n)$。
   - **核心代码**：
     ```cpp
     bool f = true, ans = true;
     for (int i = 2; i <= n; i++) {
         if (a[i] > a[i-1]) {
             if (!f) { ans = false; break; }
         } else if (a[i] < a[i-1]) {
             f = false; // 开始下降
         }
     }
     ```

3. **题解作者：Toothless03 (★★★★☆)**
   - **亮点**：双向遍历找到递增和递减边界，通过边界重叠判断单峰。
   - **核心代码**：
     ```cpp
     int l = 0, r = n-1;
     while (l < n-1 && a[l+1] >= a[l]) l++;
     while (r > 0 && a[r-1] >= a[r]) r--;
     cout << (l >= r ? "YES" : "NO");
     ```

---

### 关键技巧总结
- **单峰结构判定**：通过遍历或分两段验证，确保数组形态满足递增后递减。
- **极值处理**：允许相等元素，如 `2,3,3,4` 视为有效单峰。
- **贪心思想**：操作次数的最小值对应于数组的“最紧凑”形态，避免分散的峰谷。

---

### 拓展练习
1. **积木大赛（洛谷 P1969）**  
   类似操作次数计算，验证相邻差值思想。
2. **Look Up S（洛谷 P2947）**  
   单调栈处理峰谷结构问题。
3. **接雨水（LeetCode 42）**  
   峰谷模型的双指针应用。

---
处理用时：187.96秒