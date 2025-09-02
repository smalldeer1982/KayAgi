# 题目信息

# [ICPC 2021 Nanjing R] Klee in Solitary Confinement

## 题目描述

Since the traveler comes, People in Monstadt suddenly raise great interest in computer programming and algorithms, including Klee, the Spark Knight of the Knights of Favonius.

![](https://cdn.luogu.com.cn/upload/image_hosting/xcnn0v4q.png)

Being sent to solitary confinement by Jean again, Klee decides to spend time learning the famous Mo's algorithm, which can compute with a time complexity of $\mathcal{O}(n^{1.5})$ for some range query problem without modifications.

To check whether Klee has truly mastered the algorithm (or in fact making another bombs secretly), Jean gives her a problem of an integer sequence $a_1, a_2, \cdots, a_n$ along with some queries $[l_i, r_i]$ requiring her to find the mode number in the contiguous subsequence $a_{l_i}, a_{l_i + 1}, \cdots, a_{r_i}$. The mode number is the most common number (that is to say, the number which appears the maximum number of times) in the subsequence.

With the help of Mo's algorithm, Klee solves that problem without effort, but another problem comes into her mind. Given an integer sequence $a_1, a_2, \cdots, a_n$ of length $n$ and an integer $k$, you can perform the following operation at most once: Choose two integers $l$ and $r$ such that $1 \le l \le r \le n$ and add $k$ to every $a_i$ where $l \le i \le r$. Note that it is OK not to perform this operation. Compute the maximum occurrence of the mode number of the whole sequence if you choose to perform (or not perform) the operation optimally.

## 说明/提示

For the first sample test case, choose $l = 1$ and $r = 2$ and we'll result in the sequence $\{4, 4, 4, 4, 4\}$. The mode number is obviously $4$ which appears $5$ times.

For the second sample test case, choose $l = 4$ and $r = 6$ and we'll result in the sequence $\{3, 2, 3, 3, 3, 3, 3\}$. The mode number is $3$ which appears $6$ times.

For the fourth sample test case, choose not to perform the operation. The mode number is $1$ and $-2$ which both appear $3$ times.

## 样例 #1

### 输入

```
5 2
2 2 4 4 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
7 1
3 2 3 2 2 2 3
```

### 输出

```
6
```

## 样例 #3

### 输入

```
7 1
2 3 2 3 2 3 3
```

### 输出

```
5
```

## 样例 #4

### 输入

```
9 -100
-1 -2 1 2 -1 -2 1 -2 1
```

### 输出

```
3
```

# AI分析结果



**算法分类**: 差分

**分析与结论**  
题目要求在最多一次区间加k操作后，求众数的最大出现次数。各题解核心思路一致：统计原数组各数的出现次数，动态维护修改区间对每个数的增益，实时更新最大众数次数。关键点包括：  
- 偏移量处理负数，转为数组下标。  
- 维护增益数组，记录每个数在修改后的变化。  
- 遍历时更新增益并取最大值，避免显式枚举区间。  

**推荐题解**  
1. **keepwatcher_kensap（5星）**  
   **亮点**：思路清晰，代码简洁高效，使用数组代替map优化速度，特判处理到位。  
   **关键代码**：  
   ```cpp
   for (int i=1;i<=n;i++) {
       g[a[i]] = max(g[a[i]]-1, 0); // 当前数增益减1，保持非负
       g[a[i]+m]++; // 加k后的数增益加1
       result = max(result, g[a[i]+m] + f[a[i]+m]); // 更新最大值
   }
   ```
   
2. **卷王（4星）**  
   **亮点**：代码结构清晰，偏移量处理明确，注释简洁。  
   **关键代码**：  
   ```cpp
   for(int i=1;i<=n;i++){
       ds[a[i]+delta]--; 
       ds[a[i]+delta+k]++; 
       ans=max(ans, ds[a[i]+delta+k] + cnt[a[i]+delta+k]);
   }
   ```
   
3. **L_zaa_L（4星）**  
   **亮点**：变量命名直观，处理增益数组时优化负数情况。  
   **关键代码**：  
   ```cpp
   for(int i=1;i<=n;i++){
       f[a[i]]--, f[a[i]+k]++;
       ans=max(ans, f[a[i]+k] + s[a[i]+k]);
   }
   ```

**关键思路**  
- **差分增益**：通过维护每个数的增益变化，避免枚举区间，将问题转化为动态调整最大增益。  
- **偏移处理**：将负数转为正数组下标，解决负数存储问题。  
- **贪心更新**：确保增益非负，类似最大子段和中的Kadane算法思想。  

**拓展与相似题**  
- **类似题目**：  
  1. [P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)（最大子段和的变形）  
  2. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)（差分统计区间操作）  
  3. [P3667 USACO17OPEN Bovine Genomics G](https://www.luogu.com.cn/problem/P3667)（利用前缀和统计区间特征）  

**心得体会**  
- **调试教训**：使用map会导致超时，必须用数组优化。  
- **顿悟**：区间修改的增益可以分解为对每个元素的独立贡献，无需显式处理区间连续性。

---
处理用时：162.41秒