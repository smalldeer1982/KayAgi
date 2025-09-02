# 题目信息

# Pleasant Pairs

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ consisting of $ n $ distinct integers. Count the number of pairs of indices $ (i, j) $ such that $ i < j $ and $ a_i \cdot a_j = i + j $ .

## 说明/提示

For the first test case, the only pair that satisfies the constraints is $ (1, 2) $ , as $ a_1 \cdot a_2 = 1 + 2 = 3 $

For the second test case, the only pair that satisfies the constraints is $ (2, 3) $ .

For the third test case, the pairs that satisfy the constraints are $ (1, 2) $ , $ (1, 5) $ , and $ (2, 3) $ .

## 样例 #1

### 输入

```
3
2
3 1
3
6 1 5
5
3 1 5 9 2```

### 输出

```
1
1
3```

# AI分析结果

### 题目内容
# 愉快的数对

## 题目描述
给定一个由 $n$ 个不同整数组成的数组 $a_1, a_2, \dots, a_n$ 。计算满足 $i < j$ 且 $a_i \cdot a_j = i + j$ 的索引对 $(i, j)$ 的数量。

## 说明/提示
对于第一个测试用例，满足条件的唯一数对是 $(1, 2)$ ，因为 $a_1 \cdot a_2 = 1 + 2 = 3$ 。
对于第二个测试用例，满足条件的唯一数对是 $(2, 3)$ 。
对于第三个测试用例，满足条件的数对是 $(1, 2)$ 、$(1, 5)$ 和 $(2, 3)$ 。

## 样例 #1
### 输入
```
3
2
3 1
3
6 1 5
5
3 1 5 9 2
```
### 输出
```
1
1
3
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是基于对条件 $a_i \cdot a_j = i + j$ 的数学推导，利用 $i + j \leq 2n$ 得出 $a_i \cdot a_j \leq 2n$ ，进而优化枚举范围。各题解主要区别在于实现细节和对边界条件的处理。
1. **itisover题解**：先对数组排序，利用排序后的单调性在枚举 $i, j$ 时加上 $a_i \cdot a_j \leq 2n$ 的条件，通过调和级数证明时间复杂度为 $O(nlogn)$ 。
2. **Acc_Robin题解**：利用元素两两不同且值域小的特点开桶记录值对应的下标，将问题转化为在桶中找满足 $ij = b_i + b_j$ 的数对，同样利用 $ij \leq 2n$ 优化枚举范围，分析了时间和空间复杂度。
3. **LinkZelda题解**：定义 $k_i=\left\lfloor \frac{2\times n}{a_i}\right\rfloor$ ，通过桶记录位置，利用调和级数结论得出时间复杂度为 $O(nlogn)$ 。
4. **_Veritas题解**：将原式变形为 $a_j=\frac{i + j}{a_i}$ ，得出 $(i, j)$ 为愉快数对的必要条件是 $a_i \mid i + j$ ，通过枚举 $i$ 并按条件枚举 $j$ 实现，证明时间复杂度为 $O(nlogn)$ 。
5. **Temperature_automata题解**：指出 $i + j < 2n$ ，进而得出 $a_i \cdot a_j < 2n$ ，在枚举 $a_j$ 范围时根据 $2n / a_i$ 是否整除进行不同处理。

### 所选的题解
- **itisover题解**：★★★★
  - **关键亮点**：通过排序和巧妙的枚举条件优化，利用调和级数证明时间复杂度，代码实现简洁清晰。
  ```cpp
  for(int i=1;i<=n;i++){
      for(int j=i+1;j<=n&&a[i]*a[j]<=2*n;j++){
          if(a[i]*a[j]==b[a[i]]+b[a[j]]) ans++;
      }
  }
  ```
  核心实现思想：双重循环枚举 $i$ 和 $j$ ，在循环条件中加入 $a_i \cdot a_j \leq 2n$ 的限制，若满足 $a_i \cdot a_j$ 等于对应下标的和则答案加一。
- **Acc_Robin题解**：★★★★
  - **关键亮点**：利用桶优化，清晰分析时间和空间复杂度，对问题转化理解深刻。
  ```cpp
  for(int i=1;i<=m;i++)if(b[i])for(int j=i+1;j<=m && i*j<=2*n;j++)if(b[j] && i*j==b[i]+b[j])r++;
  ```
  核心实现思想：通过两层循环枚举桶中的值 $i$ 和 $j$ ，若满足 $i \times j$ 等于对应下标的和则答案加一。
- **Temperature_automata题解**：★★★★
  - **关键亮点**：准确指出 $i + j < 2n$ 这一细节，针对 $2n / a_i$ 是否整除进行不同处理，代码更严谨。
  ```cpp
  if(int(2*n/a[i])*a[i]==2*n) {
      for ( int j = 1 ; j < 2*n/a[i] ; j ++ ) {
          if(b[j]&&i!=b[j]&&i+b[j]==a[i]*j)
              ans ++ ;
      }
      b[a[i]]=i;
  }
  else {
      for ( int j = 1 ; j <= (2*n/a[i]) ; j ++ ) {
          if(b[j]&&i!=b[j]&&i+b[j]==a[i]*j)
              ans ++ ;
      }
      b[a[i]]=i;
  }
  ```
  核心实现思想：根据 $2n / a_i$ 是否整除来确定枚举 $j$ 的范围，若满足条件则答案加一。

### 最优关键思路或技巧
利用 $i + j \leq 2n$ 推出 $a_i \cdot a_j \leq 2n$ ，通过桶记录值对应的下标，优化枚举范围，将时间复杂度从 $O(n^2)$ 降低到 $O(nlogn)$ 。

### 可拓展之处
此类题目属于基于数学推导优化枚举的类型，类似套路是通过对给定等式进行数学分析，找出变量的范围限制，从而优化暴力枚举过程。

### 洛谷推荐题目
1. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)：涉及区间动态规划和数学推导优化。
2. [P2141 珠心算测验](https://www.luogu.com.cn/problem/P2141)：利用桶和数学关系进行计数。
3. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：通过数学分析优化枚举范围。 

---
处理用时：43.96秒