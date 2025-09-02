# 题目信息

# Gorilla and Permutation

## 题目描述

Gorilla and Noobish\_Monk found three numbers $ n $ , $ m $ , and $ k $ ( $ m < k $ ). They decided to construct a permutation $ ^{\dagger} $ of length $ n $ .

For the permutation, Noobish\_Monk came up with the following function: $ g(i) $ is the sum of all the numbers in the permutation on a prefix of length $ i $ that are not greater than $ m $ . Similarly, Gorilla came up with the function $ f $ , where $ f(i) $ is the sum of all the numbers in the permutation on a prefix of length $ i $ that are not less than $ k $ . A prefix of length $ i $ is a subarray consisting of the first $ i $ elements of the original array.

For example, if $ n = 5 $ , $ m = 2 $ , $ k = 5 $ , and the permutation is $ [5, 3, 4, 1, 2] $ , then:

- $ f(1) = 5 $ , because $ 5 \ge 5 $ ; $ g(1) = 0 $ , because $ 5 > 2 $ ;
- $ f(2) = 5 $ , because $ 3 < 5 $ ; $ g(2) = 0 $ , because $ 3 > 2 $ ;
- $ f(3) = 5 $ , because $ 4 < 5 $ ; $ g(3) = 0 $ , because $ 4 > 2 $ ;
- $ f(4) = 5 $ , because $ 1 < 5 $ ; $ g(4) = 1 $ , because $ 1 \le 2 $ ;
- $ f(5) = 5 $ , because $ 2 < 5 $ ; $ g(5) = 1 + 2 = 3 $ , because $ 2 \le 2 $ .

Help them find a permutation for which the value of $ \left(\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)\right) $ is maximized.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation (as $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation (as $ n=3 $ , but $ 4 $ appears in the array).

## 说明/提示

In the first example, $ \left(\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)\right) = 5 \cdot 5 - (0 \cdot 3 + 1 + 3) = 25 - 4 = 21 $

## 样例 #1

### 输入

```
3
5 2 5
3 1 3
10 3 8```

### 输出

```
5 3 4 1 2
3 2 1
10 9 8 4 7 5 6 1 2 3```

# AI分析结果



### 中文题目重写

#### 题目描述
Gorilla 和 Noobish_Monk 发现了三个数 $n$, $m$, $k$（$m < k$），他们决定构造一个长度为 $n$ 的排列 $^{\dagger}$。

对于这个排列，Noobish_Monk 定义函数 $g(i)$ 表示前 $i$ 个元素中不超过 $m$ 的所有数的和，Gorilla 定义函数 $f(i)$ 表示前 $i$ 个元素中不小于 $k$ 的所有数的和。要求构造排列使得 $\sum_{i=1}^n f(i) - \sum_{i=1}^n g(i)$ 最大。

$^{\dagger}$ 排列是长度为 $n$ 的数组，包含 $1$ 到 $n$ 的每个数恰好一次。

#### 输入格式
多组测试数据。每组输入 $n$, $m$, $k$，输出所求排列。

#### 样例
输入：
```
3
5 2 5
3 1 3
10 3 8
```
输出：
```
5 3 4 1 2
3 2 1
10 9 8 4 7 5 6 1 2 3
```

---

### 题解分析与结论

#### 核心思路
1. **贡献最大化**：每个数的贡献次数与其位置相关，位置越靠前的数对前缀和的累积影响越大。
2. **分类处理**：
   - **高区间**（$\geq k$）：降序排列在最前面，使大数尽可能早出现，最大化 $f$ 的贡献。
   - **低区间**（$\leq m$）：升序排列在最后面，减少 $g$ 的贡献次数。
   - **中区间**（$m+1$ 到 $k-1$）：顺序不影响结果，可任意排列。

#### 最优题解

##### 题解1：Garry_HJR（★★★★☆）
**关键亮点**：
- 简洁明了地将所有大于 $m$ 的数降序排列，并直接输出低区间升序。
- 通过样例调试发现低区间需要升序排列的关键点。

**代码核心**：
```cpp
for(int i=n; i>m; i--) cout<<i<<' '; // 处理高区间及中区间
for(int i=1; i<=m; i++) cout<<i<<' '; // 低区间升序
```

##### 题解2：MhxMa（★★★★★）
**关键亮点**：
- 明确将数分为三个区间，逻辑清晰。
- 独立处理各区间，代码可读性强。

**代码核心**：
```cpp
for(int i=n; i>=k; --i) cout<<i<<" "; // 高区间降序
for(int i=m+1; i<=k-1; ++i) cout<<i<<" "; // 中区间任意
for(int i=1; i<=m; ++i) cout<<i<<" "; // 低区间升序
```

##### 题解3：SnapYust（★★★★☆）
**关键亮点**：
- 明确贪心策略，强调大数前置、小数后置。
- 代码简洁，直接体现构造逻辑。

**代码核心**：
```cpp
for(int i=n; i>m; i--) cout<<i<<' '; // 处理高区间及中区间
for(int i=1; i<=m; i++) cout<<i<<' '; // 低区间升序
```

---

### 关键代码实现
```cpp
// MhxMa 的完整处理逻辑
for(int i = n; i >= k; --i) // 高区间降序
    cout << i << " ";
for(int i = m + 1; i <= k - 1; ++i) // 中区间任意顺序
    cout << i << " ";
for(int i = 1; i <= m; ++i) // 低区间升序
    cout << i << " ";
```

---

### 拓展与总结
1. **同类问题**：构造排列时，若需最大化/最小化某种前缀相关函数，通常需要考虑元素位置对累积贡献的影响。
2. **举一反三**：类似题目如构造排列使得逆序对最少（贪心排序）、或特定区间和最大（优先安排关键元素）。

#### 推荐题目
1. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)（构造双向序列）
2. [P2879 排队布局](https://www.luogu.com.cn/problem/P2879)（贪心排序应用）
3. [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)（贪心构造最优排列）

---
处理用时：141.82秒