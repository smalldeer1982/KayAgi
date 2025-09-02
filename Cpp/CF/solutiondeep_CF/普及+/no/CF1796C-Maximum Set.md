# 题目信息

# Maximum Set

## 题目描述

A set of positive integers $ S $ is called beautiful if, for every two integers $ x $ and $ y $ from this set, either $ x $ divides $ y $ or $ y $ divides $ x $ (or both).

You are given two integers $ l $ and $ r $ . Consider all beautiful sets consisting of integers not less than $ l $ and not greater than $ r $ . You have to print two numbers:

- the maximum possible size of a beautiful set where all elements are from $ l $ to $ r $ ;
- the number of beautiful sets consisting of integers from $ l $ to $ r $ with the maximum possible size.

Since the second number can be very large, print it modulo $ 998244353 $ .

## 说明/提示

In the first test case, the maximum possible size of a beautiful set with integers from $ 3 $ to $ 11 $ is $ 2 $ . There are $ 4 $ such sets which have the maximum possible size:

- $ \{ 3, 6 \} $ ;
- $ \{ 3, 9 \} $ ;
- $ \{ 4, 8 \} $ ;
- $ \{ 5, 10 \} $ .

## 样例 #1

### 输入

```
4
3 11
13 37
1 22
4 100```

### 输出

```
2 4
2 6
5 1
5 7```

# AI分析结果

### 题目内容重写

#### Maximum Set

##### 题目描述

一个正整数集合 $S$ 被称为漂亮的，如果对于这个集合中的任意两个整数 $x$ 和 $y$，要么 $x$ 整除 $y$，要么 $y$ 整除 $x$（或两者都成立）。

给定两个整数 $l$ 和 $r$，考虑所有由不小于 $l$ 且不大于 $r$ 的整数组成的漂亮集合。你需要输出两个数字：

- 最大可能的漂亮集合的大小，其中所有元素都来自 $l$ 到 $r$；
- 具有最大可能大小的漂亮集合的数量，其中所有元素都来自 $l$ 到 $r$。

由于第二个数字可能非常大，请输出其对 $998244353$ 取模的结果。

##### 说明/提示

在第一个测试用例中，最大可能的漂亮集合的大小为 $2$，其中所有元素都来自 $3$ 到 $11$。有 $4$ 个这样的集合具有最大可能大小：

- $ \{ 3, 6 \} $ ;
- $ \{ 3, 9 \} $ ;
- $ \{ 4, 8 \} $ ;
- $ \{ 5, 10 \} $ .

##### 样例 #1

###### 输入

```
4
3 11
13 37
1 22
4 100
```

###### 输出

```
2 4
2 6
5 1
5 7
```

### 算法分类
数学、组合数学

### 题解分析与结论

#### 综合分析与结论
本题的核心在于如何构造一个最大大小的漂亮集合，并计算其数量。大多数题解都采用了相似的思路：通过将集合中的元素按倍数关系递增排列，使得每个元素都是前一个元素的倍数，从而保证集合的漂亮性。具体来说，大多数题解都采用了以下步骤：

1. **计算最大集合大小**：通过不断将 $l$ 乘以 $2$，直到超过 $r$，从而确定最大集合的大小。
2. **计算最大集合的数量**：通过枚举可能的起始点，并考虑在某些位置将倍数从 $2$ 替换为 $3$，从而计算满足条件的集合数量。

#### 精选题解

##### 题解1：作者：spider_oyster (赞：16)
- **星级**：★★★★★
- **关键亮点**：思路清晰，代码简洁，通过数学推导直接得出最大集合大小和数量，避免了复杂的枚举。
- **核心代码**：
  ```cpp
  int n=log2(r/l);
  int ans=r/(1<<n)-l+1;
  if(n>0)
  {
      int t=r/(1<<n-1)/3-l+1;
      if(t>0) ans=ans+t*n;
  }
  printf("%d %d\n",n+1,ans);
  ```
- **核心思想**：通过计算 $log_2(r/l)$ 确定最大集合大小，然后通过枚举可能的起始点和替换 $3$ 的位置来计算集合数量。

##### 题解2：作者：2huk (赞：4)
- **星级**：★★★★
- **关键亮点**：详细解释了为什么只能替换一个 $3$，并通过组合数学的方法计算集合数量。
- **核心代码**：
  ```cpp
  int q1(int l, int r)
  {
      int res = 0;
      while (l <= r) res ++ , l *= 2;
      return res;
  }
  ```
- **核心思想**：通过不断将 $l$ 乘以 $2$ 来确定最大集合大小，然后通过组合数学的方法计算集合数量。

##### 题解3：作者：forgotmyhandle (赞：4)
- **星级**：★★★★
- **关键亮点**：通过数学推导直接得出最大集合大小和数量，代码简洁且高效。
- **核心代码**：
  ```cpp
  int x = log2((1.0 * b) / a);
  int l = a, m = (b / 3) / (1 << x - 1), r = b / (1 << x);
  cout << x + 1 << " " << (r - l + 1 + (((m - l + 1) % p) * (x % p) * (m >= l)) % p) % p << "\n";
  ```
- **核心思想**：通过计算 $log_2(r/l)$ 确定最大集合大小，然后通过枚举可能的起始点和替换 $3$ 的位置来计算集合数量。

### 关键思路与技巧
1. **倍数关系**：通过将集合中的元素按倍数关系递增排列，可以保证集合的漂亮性。
2. **数学推导**：通过数学推导直接得出最大集合大小和数量，避免了复杂的枚举。
3. **组合数学**：通过组合数学的方法计算集合数量，特别是在某些位置将倍数从 $2$ 替换为 $3$ 时。

### 可拓展之处
1. **倍数关系的扩展**：可以考虑更多倍数的替换，如 $4$、$5$ 等，但需要保证集合的漂亮性。
2. **组合数学的应用**：在计算集合数量时，可以进一步应用组合数学的方法，如排列组合、容斥原理等。

### 推荐题目
1. [P1495 集合划分](https://www.luogu.com.cn/problem/P1495)
2. [P1972 集合的并](https://www.luogu.com.cn/problem/P1972)
3. [P1973 集合的交](https://www.luogu.com.cn/problem/P1973)

### 个人心得
- **调试经历**：在计算最大集合大小时，需要注意 $l$ 和 $r$ 的范围，避免溢出。
- **顿悟感想**：通过数学推导直接得出最大集合大小和数量，可以大大简化问题的复杂度。

---
处理用时：49.87秒