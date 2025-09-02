# 题目信息

# Shocking Arrangement

## 题目描述

You are given an array $ a_1, a_2, \ldots, a_n $ consisting of integers such that $ a_1 + a_2 + \ldots + a_n = 0 $ .

You have to rearrange the elements of the array $ a $ so that the following condition is satisfied:

$$\max\limits_{1 \le l \le r \le n} \lvert a_l + a_{l+1} + \ldots + a_r \rvert < \max(a_1, a_2, \ldots, a_n) - \min(a_1, a_2, \ldots, a_n)$$ 

where  $ |x| $  denotes the absolute value of  $ x $ .More formally, determine if there exists a permutation  $ p_1, p_2, \ldots, p_n $  that for the array  $ a_{p_1}, a_{p_2}, \ldots, a_{p_n} $ , the condition above is satisfied, and find the corresponding array.Recall that the array  $ p_1, p_2, \ldots, p_n $  is called a permutation if for each integer  $ x $  from  $ 1 $  to  $ n $  there is exactly one  $ i $  from  $ 1 $  to  $ n $  such that  $ p_i = x$.

## 说明/提示

In the first test case $ \max(a_1, \ldots, a_n) - \min(a_1, \ldots, a_n) = 9 $ . Therefore, the elements can be rearranged as $ [-5, -2, 3, 4] $ . It is easy to see that for such an arrangement $ \lvert a_l + \ldots + a_r \rvert $ is always not greater than $ 7 $ , and therefore less than $ 9 $ .

In the second test case you can rearrange the elements of the array as $ [-3, 2, -3, 2, 2] $ . Then the maximum modulus of the sum will be reached on the subarray $ [-3, 2, -3] $ , and will be equal to $ \lvert -3 + 2 + -3 \rvert = \lvert -4 \rvert = 4 $ , which is less than $ 5 $ .

In the fourth test example, any rearrangement of the array $ a $ will be suitable as an answer, including $ [-1, 0, 1] $ .

## 样例 #1

### 输入

```
7
4
3 4 -2 -5
5
2 2 2 -3 -3
8
-3 -3 1 1 1 1 1 1
3
0 1 -1
7
-3 4 3 4 -4 -4 0
1
0
7
-18 13 -18 -17 12 15 13```

### 输出

```
Yes
-5 -2 3 4
Yes
-3 2 -3 2 2
Yes
1 1 1 -3 1 1 1 -3
Yes
-1 0 1
Yes
4 -4 4 -4 0 3 -3
No
Yes
13 12 -18 15 -18 13 -17```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个由整数组成的数组 $a_1, a_2, \ldots, a_n$，满足 $a_1 + a_2 + \ldots + a_n = 0$。

你需要重新排列数组 $a$ 的元素，使得以下条件成立：

$$\max\limits_{1 \le l \le r \le n} \lvert a_l + a_{l+1} + \ldots + a_r \rvert < \max(a_1, a_2, \ldots, a_n) - \min(a_1, a_2, \ldots, a_n)$$

其中 $|x|$ 表示 $x$ 的绝对值。更正式地说，确定是否存在一个排列 $p_1, p_2, \ldots, p_n$，使得对于数组 $a_{p_1}, a_{p_2}, \ldots, a_{p_n}$，上述条件成立，并找到对应的数组。回忆一下，如果对于每个整数 $x$ 从 $1$ 到 $n$，存在唯一一个 $i$ 从 $1$ 到 $n$ 使得 $p_i = x$，则数组 $p_1, p_2, \ldots, p_n$ 被称为一个排列。

#### 说明/提示

在第一个测试用例中，$\max(a_1, \ldots, a_n) - \min(a_1, \ldots, a_n) = 9$。因此，元素可以重新排列为 $[-5, -2, 3, 4]$。容易看出，对于这样的排列，$\lvert a_l + \ldots + a_r \rvert$ 始终不大于 $7$，因此小于 $9$。

在第二个测试用例中，你可以将数组的元素重新排列为 $[-3, 2, -3, 2, 2]$。然后，最大绝对值的和将在子数组 $[-3, 2, -3]$ 上达到，等于 $\lvert -3 + 2 + -3 \rvert = \lvert -4 \rvert = 4$，这小于 $5$。

在第四个测试用例中，任何数组 $a$ 的重新排列都是合适的答案，包括 $[-1, 0, 1]$。

#### 样例 #1

##### 输入

```
7
4
3 4 -2 -5
5
2 2 2 -3 -3
8
-3 -3 1 1 1 1 1 1
3
0 1 -1
7
-3 4 3 4 -4 -4 0
1
0
7
-18 13 -18 -17 12 15 13```

##### 输出

```
Yes
-5 -2 3 4
Yes
-3 2 -3 2 2
Yes
1 1 1 -3 1 1 1 -3
Yes
-1 0 1
Yes
4 -4 4 -4 0 3 -3
No
Yes
13 12 -18 15 -18 13 -17```

### 算法分类

构造

### 题解分析与结论

本题的核心在于如何重新排列数组，使得任意子数组的和的绝对值小于数组的最大值与最小值之差。题解中主要采用了贪心策略，通过维护前缀和，并在每一步选择与当前前缀和符号相反的数来构造满足条件的排列。

#### 题解对比

1. **一扶苏一的题解**：
   - **思路**：通过维护前缀和，选择与当前前缀和符号相反的数来构造排列。
   - **难点**：正确性证明较为详细，通过数学归纳法证明了构造的正确性。
   - **代码实现**：将正数和负数分别排序，然后根据前缀和的正负选择相应的数。
   - **评分**：5星，思路清晰，代码可读性好，优化程度高。

2. **ncwzdlsd的题解**：
   - **思路**：与前一个题解类似，通过维护前缀和，选择与当前前缀和符号相反的数来构造排列。
   - **难点**：转化条件为前缀和的形式，简化了问题。
   - **代码实现**：直接排序数组，然后根据前缀和的正负选择相应的数。
   - **评分**：4星，思路清晰，代码简洁，但缺少详细证明。

3. **masonpop的题解**：
   - **思路**：与前两个题解类似，通过维护前缀和，选择与当前前缀和符号相反的数来构造排列。
   - **难点**：直接考虑充分条件，简化了问题。
   - **代码实现**：未提供完整代码，但思路与前两个题解一致。
   - **评分**：3星，思路清晰，但缺少代码实现和详细证明。

### 最优关键思路

通过维护前缀和，并在每一步选择与当前前缀和符号相反的数来构造排列，确保任意子数组的和的绝对值小于数组的最大值与最小值之差。

### 可拓展之处

类似的问题可以通过维护前缀和或使用贪心策略来解决，例如在需要控制子数组和的绝对值或和的上下界的情况下。

### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)

### 个人心得

在构造题中，贪心策略往往能有效简化问题，特别是在需要控制某些变量（如和、最大值、最小值等）的情况下。通过维护前缀和，可以有效地控制子数组的和，从而满足题目的条件。

---
处理用时：42.76秒