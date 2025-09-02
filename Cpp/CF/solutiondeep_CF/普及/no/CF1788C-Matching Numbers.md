# 题目信息

# Matching Numbers

## 题目描述

You are given an integer $ n $ . Pair the integers $ 1 $ to $ 2n $ (i.e. each integer should be in exactly one pair) so that each sum of matched pairs is consecutive and distinct.

Formally, let $ (a_i, b_i) $ be the pairs that you matched. $ \{a_1, b_1, a_2, b_2, \ldots, a_n, b_n\} $ should be a permutation of $ \{1, 2, \ldots, 2n\} $ . Let the sorted list of $ \{a_1+b_1, a_2+b_2, \ldots, a_n+b_n\} $ be $ s_1 < s_2 < \ldots < s_n $ . We must have $ s_{i+1}-s_i = 1 $ for $ 1 \le i \le n - 1 $ .

## 说明/提示

For the third test case, each integer from $ 1 $ to $ 6 $ appears once. The sums of matched pairs are $ 4+2=6 $ , $ 1+6=7 $ , and $ 3+5=8 $ , which are consecutive and distinct.

## 样例 #1

### 输入

```
4
1
2
3
4```

### 输出

```
Yes
1 2
No
Yes
1 6
3 5
4 2
No```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个整数 $n$，将整数 $1$ 到 $2n$ 配对（即每个整数恰好出现在一个对中），使得每对数的和是连续且不同的。

形式上，设 $(a_i, b_i)$ 为你匹配的对。$\{a_1, b_1, a_2, b_2, \ldots, a_n, b_n\}$ 应该是 $\{1, 2, \ldots, 2n\}$ 的一个排列。设 $\{a_1+b_1, a_2+b_2, \ldots, a_n+b_n\}$ 的排序列表为 $s_1 < s_2 < \ldots < s_n$。我们必须满足 $s_{i+1}-s_i = 1$，其中 $1 \le i \le n - 1$。

#### 说明/提示

对于第三个测试用例，每个整数从 $1$ 到 $6$ 出现一次。匹配对的和为 $4+2=6$，$1+6=7$，和 $3+5=8$，它们是连续且不同的。

#### 样例 #1

##### 输入

```
4
1
2
3
4
```

##### 输出

```
Yes
1 2
No
Yes
1 6
3 5
4 2
No
```

### 算法分类
构造

### 题解分析与结论

#### 综合分析

本题的核心在于构造一种配对方式，使得每对数的和形成一个连续的等差数列。所有题解都指出，当 $n$ 为偶数时无解，因为等差数列的和与 $1$ 到 $2n$ 的和在奇偶性上不匹配。当 $n$ 为奇数时，题解提供了不同的构造方法，主要思路是将 $1$ 到 $n$ 的数与 $n+1$ 到 $2n$ 的数配对，并通过调整配对的顺序来满足等差数列的条件。

#### 所选高星题解

1. **题解作者：Remilia1023 (赞：5)**
   - **星级：5星**
   - **关键亮点**：通过等差数列的数学推导，明确 $n$ 为偶数时无解，并提供了简洁的构造方法。代码实现清晰，易于理解。
   - **个人心得**：作者提到最初花费了1.5小时，最终发现构造方式其实很简单，强调了数学推导的重要性。
   - **核心代码**：
     ```cpp
     int a = 2 * n, b = 3 * (n + 1) / 2 - 2;
     for (int i = 1; i <= n; i++) 
         if (i & 1) cout << i << ' ' << a-- << endl;
         else cout << i << ' ' << b-- << endl;
     ```

2. **题解作者：xzyg (赞：3)**
   - **星级：4星**
   - **关键亮点**：通过具体的例子（$n=5$）展示了构造过程，并给出了详细的配对规则。代码实现较为复杂，但思路清晰。
   - **核心代码**：
     ```cpp
     for(ll i = 1; i <= n/2 + 1; i++)
         cout << i << " " << 2 * n - 2 * i + 2 << '\n'; 
     for(ll i = n/2 + 2; i <= n; i++)
         cout << i << " " << 2 * n - 2 * i + 2 * (n + 1) / 2 + 1 << '\n';
     ```

3. **题解作者：copper_ingot (赞：2)**
   - **星级：4星**
   - **关键亮点**：通过等差数列的平均数推导出无解条件，并提供了两种不同的配对方式，代码实现简洁。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= m / 2 + 1; i++)
         printf("%d %d\n", i, j), j -= 2;
     for (int i = m / 2 + 2; i <= m; i++)
         printf("%d %d\n", i, j), j -= 2;
     ```

### 最优关键思路或技巧

1. **数学推导**：通过等差数列的求和公式推导出 $n$ 为偶数时无解，并确定等差数列的首项。
2. **配对策略**：将 $1$ 到 $n$ 的数与 $n+1$ 到 $2n$ 的数配对，并通过调整配对的顺序来满足等差数列的条件。
3. **代码实现**：通过简单的循环和条件判断实现配对，代码简洁且高效。

### 可拓展之处

本题的构造思路可以推广到类似的配对问题，尤其是需要满足特定数列条件的配对问题。类似的题目可能涉及不同的数列条件或更复杂的配对规则。

### 推荐题目

1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)

---
处理用时：34.70秒