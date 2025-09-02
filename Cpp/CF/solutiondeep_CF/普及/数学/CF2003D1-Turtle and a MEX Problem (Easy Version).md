# 题目信息

# Turtle and a MEX Problem (Easy Version)

## 题目描述

The two versions are different problems. In this version of the problem, you can choose the same integer twice or more. You can make hacks only if both versions are solved.

One day, Turtle was playing with $ n $ sequences. Let the length of the $ i $ -th sequence be $ l_i $ . Then the $ i $ -th sequence was $ a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i} $ .

Piggy gave Turtle a problem to solve when Turtle was playing. The statement of the problem was:

- There was a non-negative integer $ x $ at first. Turtle would perform an arbitrary number (possibly zero) of operations on the integer.
- In each operation, Turtle could choose an integer $ i $ such that $ 1 \le i \le n $ , and set $ x $ to $ \text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}) $ .
- Turtle was asked to find the answer, which was the maximum value of $ x $ after performing an arbitrary number of operations.

Turtle solved the above problem without difficulty. He defined $ f(k) $ as the answer to the above problem when the initial value of $ x $ was $ k $ .

Then Piggy gave Turtle a non-negative integer $ m $ and asked Turtle to find the value of $ \sum\limits_{i = 0}^m f(i) $ (i.e., the value of $ f(0) + f(1) + \ldots + f(m) $ ). Unfortunately, he couldn't solve this problem. Please help him!

 $ ^{\dagger}\text{mex}(c_1, c_2, \ldots, c_k) $ is defined as the smallest non-negative integer $ x $ which does not occur in the sequence $ c $ . For example, $ \text{mex}(2, 2, 0, 3) $ is $ 1 $ , $ \text{mex}(1, 2) $ is $ 0 $ .

## 说明/提示

In the first test case, when $ x $ is initially $ 2 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}) = \text{mex}(2, 7, 0, 1, 5) = 3 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 3 $ , so $ f(2) = 3 $ .

It can be seen that $ f(0) = 3 $ , $ f(1) = 3 $ , $ f(2) = 3 $ , $ f(3) = 3 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16 $ .

In the second test case, when $ x $ is initially $ 1 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(1, 1, 3, 0, 3, 3) = 2 $ , and choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(2, 1, 3, 0, 3, 3) = 4 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 4 $ , so $ f(1) = 4 $ .

It can be seen that $ f(0) = 4 $ , $ f(1) = 4 $ , $ f(2) = 4 $ , $ f(3) = 4 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 4 + 4 + 4 + 4 = 20 $ .

In the fourth test case, it can be seen that $ f(0) = 3 $ and $ f(1) = 3 $ . So $ f(0) + f(1) = 3 + 3 = 6 $ .

## 样例 #1

### 输入

```
6
3 4
2 0 2
3 2 3 3
4 7 0 1 5
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
2 50
2 1 2
2 1 2
1 1
7 1 2 4 1 4 9 5
4 114514
2 2 2
5 7 3 6 0 3
3 0 1 1
5 0 9 2 1 5
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556```

### 输出

```
16
20
1281
6
6556785365
1842836177961```

# AI分析结果

### 题目内容中文重写

# 乌龟与MEX问题（简单版）

## 题目描述

两个版本是不同的问题。在这个版本的问题中，你可以多次选择相同的整数。只有当两个版本都解决时，你才能进行hack。

有一天，乌龟在玩$n$个序列。设第$i$个序列的长度为$l_i$，那么第$i$个序列为$a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}$。

当乌龟在玩的时候，小猪给乌龟出了一个题目。题目描述如下：

- 最初有一个非负整数$x$。乌龟可以对整数进行任意次（可能为零次）操作。
- 每次操作中，乌龟可以选择一个整数$i$，使得$1 \le i \le n$，并将$x$设为$\text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i})$。
- 乌龟需要找到答案，即在执行任意次操作后$x$的最大值。

乌龟轻松地解决了上述问题。他定义了$f(k)$为当$x$的初始值为$k$时上述问题的答案。

然后小猪给乌龟一个非负整数$m$，并要求乌龟找到$\sum\limits_{i = 0}^m f(i)$的值（即$f(0) + f(1) + \ldots + f(m)$的值）。不幸的是，他无法解决这个问题。请帮助他！

$^{\dagger}\text{mex}(c_1, c_2, \ldots, c_k)$定义为序列$c$中未出现的最小非负整数$x$。例如，$\text{mex}(2, 2, 0, 3)$是$1$，$\text{mex}(1, 2)$是$0$。

## 说明/提示

在第一个测试用例中，当$x$初始为$2$时，乌龟可以选择$i = 3$并将$x$设为$\text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}) = \text{mex}(2, 7, 0, 1, 5) = 3$。可以证明乌龟无法使$x$的值大于$3$，因此$f(2) = 3$。

可以看出$f(0) = 3$，$f(1) = 3$，$f(2) = 3$，$f(3) = 3$，$f(4) = 4$。因此$f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16$。

在第二个测试用例中，当$x$初始为$1$时，乌龟可以选择$i = 3$并将$x$设为$\text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(1, 1, 3, 0, 3, 3) = 2$，然后再次选择$i = 3$并将$x$设为$\text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(2, 1, 3, 0, 3, 3) = 4$。可以证明乌龟无法使$x$的值大于$4$，因此$f(1) = 4$。

可以看出$f(0) = 4$，$f(1) = 4$，$f(2) = 4$，$f(3) = 4$，$f(4) = 4$。因此$f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 4 + 4 + 4 + 4 = 20$。

在第四个测试用例中，可以看出$f(0) = 3$，$f(1) = 3$。因此$f(0) + f(1) = 3 + 3 = 6$。

## 样例 #1

### 输入

```
6
3 4
2 0 2
3 2 3 3
4 7 0 1 5
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
2 50
2 1 2
2 1 2
1 1
7 1 2 4 1 4 9 5
4 114514
2 2 2
5 7 3 6 0 3
3 0 1 1
5 0 9 2 1 5
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556```

### 输出

```
16
20
1281
6
6556785365
1842836177961```

### 题解分析与结论

#### 综合分析与结论

1. **Exp10re的题解**：
   - **思路**：通过计算每个序列的次小未出现非负整数（$v_i$），并找到最大的$v_p$，最终答案可以表示为$\sum\limits_{i=0}^m \max(i, v_p)$。
   - **难点**：理解如何通过操作序列的MEX值来达到最大$x$值，并证明其正确性。
   - **评分**：4星，思路清晰，代码简洁，时间复杂度优化到$O(\sum l_i)$。

2. **Defy_HeavenS的题解**：
   - **思路**：通过固定一个序列，计算其MEX值的次小值，并找到所有序列中最大的次小值$ma$，最终答案为$\sum\limits_{i=0}^m \max(i, ma)$。
   - **难点**：理解如何通过多次操作一个序列来达到最大$x$值，并证明其正确性。
   - **评分**：4星，思路清晰，代码实现详细，时间复杂度优化到$O(\sum l_i)$。

3. **_O_v_O_的题解**：
   - **思路**：通过计算每个序列的MEX值的次小值，并找到最大的次小值$k$，最终答案为$k^2 + (m + k) \times (m - k - 1)$。
   - **难点**：理解如何通过操作序列的MEX值来达到最大$x$值，并证明其正确性。
   - **评分**：4星，思路清晰，代码简洁，时间复杂度优化到$O(\sum l_i)$。

#### 最优关键思路或技巧

- **关键思路**：通过计算每个序列的MEX值的次小值，并找到所有序列中最大的次小值，最终答案可以表示为$\sum\limits_{i=0}^m \max(i, ma)$。
- **技巧**：使用`set`数据结构来高效计算MEX值，时间复杂度优化到$O(\sum l_i)$。

#### 可拓展之处

- **同类型题**：类似的问题可以通过计算序列的MEX值来求解，例如CF2003D2。
- **算法套路**：使用`set`数据结构来高效计算MEX值，可以应用于其他需要计算MEX的问题。

#### 推荐题目

1. [CF2003D2](https://www.luogu.com.cn/problem/CF2003D2)
2. [P3919](https://www.luogu.com.cn/problem/P3919)
3. [P3374](https://www.luogu.com.cn/problem/P3374)

#### 个人心得

- **调试经历**：在使用`set`计算MEX值时，需要注意序列中可能出现的重复元素，避免重复计算。
- **顿悟感想**：通过多次操作一个序列，可以快速达到最大$x$值，这在实际问题中是一个非常有用的性质。

---
处理用时：61.44秒