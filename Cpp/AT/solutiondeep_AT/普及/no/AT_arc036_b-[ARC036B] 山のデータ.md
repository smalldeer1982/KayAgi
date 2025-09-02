# 题目信息

# [ARC036B] 山のデータ

## 题目描述

现在，有 $N$ 个地点。从西起第 $i(1 \le i \le N)$ 个地点的高度为 $h_i$。

这样，就有了一个三元组 $(s，t，u)$，$(1 \le s \le t \le u \le N)$。

那么，这一个三元组是山，当且仅当：

对于满足 $s \le i \le t-1$ 的任意整数中的 $i$，满足 $h_i < h_{i+1}$ 且在对于满足 $t \le i \le u-1$ 的任意整数中的 $i$，满足 $h_i > h_{i+1}$。

现在，需要找出山的**最大**长度。（定义山的长度为 $u - s + 1$）。

## 说明/提示

$1 \le N \le 3 \times 10^5, 1 \le h_i \le 10^9$。

每一个 $h_i$ 互不相同（即对于 $1 \le i < j \le N$，$h_i \ne h_j$）。

## 样例 #1

### 输入

```
6

4

5

1

6

9

7```

### 输出

```
4```

## 样例 #2

### 输入

```
7

90

70

50

30

20

10

5```

### 输出

```
7```

# AI分析结果



# [ARC036B] 山のデータ

## 题目描述
现有 $N$ 个地点，从西起第 $i(1 \le i \le N)$ 个地点的高度为 $h_i$。定义三元组 $(s, t, u)$ 为"山"，当满足：
- 对所有 $s \le i \le t-1$，有 $h_i < h_{i+1}$
- 对所有 $t \le i \le u-1$，有 $h_i > h_{i+1}$

求山的最大长度（$u - s + 1$）。

## 算法分类
贪心

---

### 综合分析与结论
题目要求寻找满足先严格递增后严格递减的最长连续子序列。核心在于高效定位每个可能的峰顶，并计算其左右延伸的最大范围。预处理每个位置的左右单调区间长度是更可靠的解法。

#### 关键思路
1. **预处理左右区间**：分别计算每个位置向左递增的长度（`left[i]`）和向右递减的长度（`right[i]`）。以每个位置为峰顶的山长度为 `left[i] + right[i] + 1`。
2. **线性扫描**：通过两次遍历预处理左右数组，时间复杂度 $O(N)$。

---

### 推荐题解
#### 预处理左右数组法（5星）
**关键亮点**：  
- 思路清晰，逻辑严谨，直接对应题目定义  
- 预处理方法保证线性时间复杂度，适合大规模数据  

**核心代码**：
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n), left(n, 0), right(n, 0);
    for (int i = 0; i < n; ++i) cin >> h[i];
    
    // 预处理左递增区间
    for (int i = 1; i < n; ++i) 
        if (h[i] > h[i-1]) left[i] = left[i-1] + 1;
    
    // 预处理右递减区间
    for (int i = n-2; i >= 0; --i) 
        if (h[i] > h[i+1]) right[i] = right[i+1] + 1;
    
    int max_len = 1;
    for (int i = 0; i < n; ++i) 
        if (left[i] + right[i] > 0)  // 至少存在左右其一有长度
            max_len = max(max_len, left[i] + right[i] + 1);
    
    cout << max_len << endl;
    return 0;
}
```

---

### 拓展与相似题目
1. **[LeetCode 845. Longest Mountain in Array](https://leetcode.com/problems/longest-mountain-in-array/)**  
   （同样利用左右数组预处理求最大山脉长度）
2. **[洛谷 P2947 [USACO09MAR] Look Up S](https://www.luogu.com.cn/problem/P2947)**  
   （单调栈处理右侧第一个更大元素）
3. **[洛谷 P1564 膜拜](https://www.luogu.com.cn/problem/P1564)**  
   （利用前缀和统计区间特性）

---
处理用时：241.65秒