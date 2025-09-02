# 题目信息

# Scoring Subsequences

## 题目描述

The score of a sequence $ [s_1, s_2, \ldots, s_d] $ is defined as $ \displaystyle \frac{s_1\cdot s_2\cdot \ldots \cdot s_d}{d!} $ , where $ d!=1\cdot 2\cdot \ldots \cdot d $ . In particular, the score of an empty sequence is $ 1 $ .

For a sequence $ [s_1, s_2, \ldots, s_d] $ , let $ m $ be the maximum score among all its subsequences. Its cost is defined as the maximum length of a subsequence with a score of $ m $ .

You are given a non-decreasing sequence $ [a_1, a_2, \ldots, a_n] $ of integers of length $ n $ . In other words, the condition $ a_1 \leq a_2 \leq \ldots \leq a_n $ is satisfied. For each $ k=1, 2, \ldots , n $ , find the cost of the sequence $ [a_1, a_2, \ldots , a_k] $ .

A sequence $ x $ is a subsequence of a sequence $ y $ if $ x $ can be obtained from $ y $ by deletion of several (possibly, zero or all) elements.

## 说明/提示

In the first test case:

- The maximum score among the subsequences of $ [1] $ is $ 1 $ . The subsequences $ [1] $ and $ [] $ (the empty sequence) are the only ones with this score. Thus, the cost of $ [1] $ is $ 1 $ .
- The maximum score among the subsequences of $ [1, 2] $ is $ 2 $ . The only subsequence with this score is $ [2] $ . Thus, the cost of $ [1, 2] $ is $ 1 $ .
- The maximum score among the subsequences of $ [1, 2, 3] $ is $ 3 $ . The subsequences $ [2, 3] $ and $ [3] $ are the only ones with this score. Thus, the cost of $ [1, 2, 3] $ is $ 2 $ .

 Therefore, the answer to this case is $ 1\:\:1\:\:2 $ , which are the costs of $ [1], [1, 2] $ and $ [1, 2, 3] $ in this order.

## 样例 #1

### 输入

```
3
3
1 2 3
2
1 1
5
5 5 5 5 5```

### 输出

```
1 1 2 
1 1 
1 2 3 4 5```

# AI分析结果

### 题目内容重写
# 评分子序列

## 题目描述

序列 $ [s_1, s_2, \ldots, s_d] $ 的得分定义为 $ \displaystyle \frac{s_1\cdot s_2\cdot \ldots \cdot s_d}{d!} $ ，其中 $ d!=1\cdot 2\cdot \ldots \cdot d $ 。特别地，空序列的得分为 $ 1 $ 。

对于序列 $ [s_1, s_2, \ldots, s_d] $ ，设 $ m $ 为其所有子序列中的最大得分。其成本定义为得分为 $ m $ 的子序列的最大长度。

给定一个长度为 $ n $ 的非递减整数序列 $ [a_1, a_2, \ldots, a_n] $ ，即满足 $ a_1 \leq a_2 \leq \ldots \leq a_n $ 。对于每个 $ k=1, 2, \ldots , n $ ，求序列 $ [a_1, a_2, \ldots , a_k] $ 的成本。

序列 $ x $ 是序列 $ y $ 的子序列，如果 $ x $ 可以通过从 $ y $ 中删除若干个（可能为零或全部）元素得到。

## 说明/提示

在第一个测试用例中：

- 序列 $ [1] $ 的子序列中的最大得分为 $ 1 $ 。子序列 $ [1] $ 和 $ [] $ （空序列）是唯一得分为 $ 1 $ 的子序列。因此，序列 $ [1] $ 的成本为 $ 1 $ 。
- 序列 $ [1, 2] $ 的子序列中的最大得分为 $ 2 $ 。唯一得分为 $ 2 $ 的子序列是 $ [2] $ 。因此，序列 $ [1, 2] $ 的成本为 $ 1 $ 。
- 序列 $ [1, 2, 3] $ 的子序列中的最大得分为 $ 3 $ 。子序列 $ [2, 3] $ 和 $ [3] $ 是唯一得分为 $ 3 $ 的子序列。因此，序列 $ [1, 2, 3] $ 的成本为 $ 2 $ 。

因此，这个测试用例的答案是 $ 1\:\:1\:\:2 $ ，即序列 $ [1], [1, 2] $ 和 $ [1, 2, 3] $ 的成本。

## 样例 #1

### 输入

```
3
3
1 2 3
2
1 1
5
5 5 5 5 5```

### 输出

```
1 1 2 
1 1 
1 2 3 4 5```

### 算法分类
二分

### 题解分析与结论
题目要求对于每个 $k$，找到序列 $[a_1, a_2, \ldots, a_k]$ 的成本，即得分为最大得分的子序列的最大长度。由于序列是非递减的，最大得分通常由序列的后缀部分贡献。因此，可以通过二分查找来确定每个 $k$ 的最大长度。

### 所选题解
1. **作者：SunnyYuan (5星)**
   - **关键亮点**：利用二分查找确定每个 $k$ 的最大长度，时间复杂度为 $O(n \log n)$，思路清晰且代码简洁。
   - **代码核心思想**：对于每个 $k$，使用二分查找找到第一个满足 $a[i - mid + 1] \geq mid$ 的位置，从而确定最大长度。
   ```cpp
   for (int i = 1; i <= n; i++) {
       int l = -1, r = i + 1;
       while (l + 1 < r) {
           int mid = (l + r) / 2;
           if (a[i - mid + 1] >= mid) l = mid;
           else r = mid;
       }
       cout << l << ' ';
   }
   ```

2. **作者：Iamzzr (4星)**
   - **关键亮点**：使用双指针技巧，时间复杂度为 $O(n)$，代码简洁且效率高。
   - **代码核心思想**：维护一个左指针 $l$，每次读入一个新的 $a[i]$ 后，调整 $l$ 的位置，使得 $a[l] \geq r - l + 1$，其中 $r = i$。
   ```cpp
   for (int i = 1; i <= n; i++) {
       cin >> a[i];
       r = i;
       while (a[l] < r - l + 1) l++;
       cout << r - l + 1 << " ";
   }
   ```

3. **作者：incra (4星)**
   - **关键亮点**：同样使用二分查找，思路清晰，代码简洁。
   - **代码核心思想**：对于每个 $k$，使用二分查找找到第一个满足 $a[mid] \geq k - mid + 1$ 的位置，从而确定最大长度。
   ```cpp
   for (int i = 1; i <= n; i++) {
       int l = 1, r = i;
       while (l < r) {
           int mid = l + r >> 1;
           if (a[mid] >= i - mid + 1) r = mid;
           else l = mid + 1;
       }
       cout << i - l + 1 << ' ';
   }
   ```

### 最优关键思路或技巧
- **二分查找**：利用二分查找确定每个 $k$ 的最大长度，时间复杂度为 $O(n \log n)$。
- **双指针**：使用双指针技巧，时间复杂度为 $O(n)$，效率更高。

### 拓展思路
类似的问题可以通过二分查找或双指针技巧来解决，尤其是在处理单调序列时，这两种方法通常能够有效地降低时间复杂度。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)

---
处理用时：38.98秒