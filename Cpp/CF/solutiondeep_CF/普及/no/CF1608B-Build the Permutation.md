# 题目信息

# Build the Permutation

## 题目描述

You are given three integers $ n, a, b $ . Determine if there exists a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ , such that:

- There are exactly $ a $ integers $ i $ with $ 2 \le i \le n-1 $ such that $ p_{i-1} < p_i > p_{i+1} $ (in other words, there are exactly $ a $ local maximums).
- There are exactly $ b $ integers $ i $ with $ 2 \le i \le n-1 $ such that $ p_{i-1} > p_i < p_{i+1} $ (in other words, there are exactly $ b $ local minimums).

If such permutations exist, find any such permutation.

## 说明/提示

In the first test case, one example of such permutations is $ [1, 3, 2, 4] $ . In it $ p_1 < p_2 > p_3 $ , and $ 2 $ is the only such index, and $ p_2> p_3 < p_4 $ , and $ 3 $ the only such index.

One can show that there is no such permutation for the third test case.

## 样例 #1

### 输入

```
3
4 1 1
6 1 2
6 4 0```

### 输出

```
1 3 2 4
4 2 3 1 5 6
-1```

# AI分析结果

### 题目翻译

# 构建排列

## 题目描述

给定三个整数 $n, a, b$。确定是否存在一个排列 $p_1, p_2, \ldots, p_n$，其中包含从 $1$ 到 $n$ 的整数，且满足以下条件：

- 恰好有 $a$ 个整数 $i$（$2 \le i \le n-1$）满足 $p_{i-1} < p_i > p_{i+1}$（即恰好有 $a$ 个局部最大值）。
- 恰好有 $b$ 个整数 $i$（$2 \le i \le n-1$）满足 $p_{i-1} > p_i < p_{i+1}$（即恰好有 $b$ 个局部最小值）。

如果存在这样的排列，请找出任意一个满足条件的排列。

## 说明/提示

在第一个测试用例中，一个满足条件的排列是 $[1, 3, 2, 4]$。其中 $p_1 < p_2 > p_3$，且 $2$ 是唯一满足条件的索引；$p_2 > p_3 < p_4$，且 $3$ 是唯一满足条件的索引。

可以证明，第三个测试用例中不存在这样的排列。

## 样例 #1

### 输入

```
3
4 1 1
6 1 2
6 4 0
```

### 输出

```
1 3 2 4
4 2 3 1 5 6
-1
```

### 算法分类
构造

### 题解分析与结论

本题的核心在于构造一个满足特定局部最大值和最小值数量的排列。各题解的思路主要集中在以下几点：

1. **无解条件**：几乎所有题解都提到，当 $|a - b| > 1$ 或 $a + b > n - 2$ 时，问题无解。这是因为局部最大值和最小值必须交替出现，且排列的两端不能成为局部极值。

2. **构造策略**：大多数题解采用了交替构造局部最大值和最小值的方法，通过控制排列的上升和下降趋势来满足条件。具体来说，可以通过交替选择当前最小值和最大值来构造“峰”和“谷”。

3. **分类讨论**：部分题解根据 $a$ 和 $b$ 的大小关系进行了分类讨论，分别处理 $a > b$、$a < b$ 和 $a = b$ 的情况，以确保构造的排列满足条件。

4. **优化与简化**：一些题解通过简化代码逻辑或优化构造过程，使得代码更加简洁高效。

### 精选题解

#### 题解1：作者：activeO (赞：13)
- **星级**：5
- **关键亮点**：代码简洁，逻辑清晰，通过交替选择最小值和最大值来构造排列，且处理了无解情况。
- **核心代码**：
  ```cpp
  int l=1,r=n,t=(a>b);
  for(int i=1;i<=n;i++){
      if(t) printf("%d ",l++);
      else printf("%d ",r--);
      if(i<=a+b) t^=1;
  }
  ```
- **实现思想**：通过交替选择最小值和最大值来构造排列，确保局部最大值和最小值的数量满足要求。

#### 题解2：作者：清烛 (赞：0)
- **星级**：4
- **关键亮点**：详细分类讨论了 $a = b$、$a > b$ 和 $a < b$ 的情况，构造过程清晰。
- **核心代码**：
  ```cpp
  if (a == b) {
      FOR(i, 1, a + 1) ans[i * 2 - 1] = i;
      FOR(i, 1, a) ans[i * 2] = i + a + 1;
      FOR(i, 2 * a + 2, n) ans[i] = i;
  }
  ```
- **实现思想**：根据 $a$ 和 $b$ 的关系，分别构造不同的排列模式，确保局部最大值和最小值的数量满足要求。

#### 题解3：作者：SalomeJLQ (赞：0)
- **星级**：4
- **关键亮点**：通过交替构造局部最大值和最小值，并在尾部处理剩余元素，确保排列满足条件。
- **核心代码**：
  ```cpp
  if(x==y){
      int l=n-s,r=n;
      while(l<r)printf("%d ",r),r--,printf("%d ",l),l++;
      if(l==r)printf("%d ",r);
      for(int i=n-s-1;i;i--)printf("%d ",i);
  }
  ```
- **实现思想**：通过交替选择最大值和最小值来构造排列，并在尾部处理剩余元素，确保局部最大值和最小值的数量满足要求。

### 最优关键思路
通过交替选择当前最小值和最大值来构造排列，确保局部最大值和最小值的数量满足要求。同时，根据 $a$ 和 $b$ 的大小关系进行分类讨论，处理不同的构造模式。

### 拓展思路
类似的问题可以通过控制排列的上升和下降趋势来构造满足特定条件的排列。例如，构造一个排列使得其逆序对数量满足特定条件，或者构造一个排列使得其满足特定的单调性条件。

### 推荐题目
1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)

---
处理用时：38.12秒