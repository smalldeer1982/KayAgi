# 题目信息

# Twist the Permutation

## 题目描述

Petya got an array $ a $ of numbers from $ 1 $ to $ n $ , where $ a[i]=i $ .

He performed $ n $ operations sequentially. In the end, he received a new state of the $ a $ array.

At the $ i $ -th operation, Petya chose the first $ i $ elements of the array and cyclically shifted them to the right an arbitrary number of times (elements with indexes $ i+1 $ and more remain in their places). One cyclic shift to the right is such a transformation that the array $ a=[a_1, a_2, \dots, a_n] $ becomes equal to the array $ a = [a_i, a_1, a_2, \dots, a_{i-2}, a_{i-1}, a_{i+1}, a_{i+2}, \dots, a_n] $ .

For example, if $ a = [5,4,2,1,3] $ and $ i=3 $ (that is, this is the third operation), then as a result of this operation, he could get any of these three arrays:

- $ a = [5,4,2,1,3] $ (makes $ 0 $ cyclic shifts, or any number that is divisible by $ 3 $ );
- $ a = [2,5,4,1,3] $ (makes $ 1 $ cyclic shift, or any number that has a remainder of $ 1 $ when divided by $ 3 $ );
- $ a = [4,2,5,1,3] $ (makes $ 2 $ cyclic shifts, or any number that has a remainder of $ 2 $ when divided by $ 3 $ ).

Let's look at an example. Let $ n=6 $ , i.e. initially $ a=[1,2,3,4,5,6] $ . A possible scenario is described below.

- $ i=1 $ : no matter how many cyclic shifts Petya makes, the array $ a $ does not change.
- $ i=2 $ : let's say Petya decided to make a $ 1 $ cyclic shift, then the array will look like $ a = [\textbf{2}, \textbf{1}, 3, 4, 5, 6] $ .
- $ i=3 $ : let's say Petya decided to make $ 1 $ cyclic shift, then the array will look like $ a = [\textbf{3}, \textbf{2}, \textbf{1}, 4, 5, 6] $ .
- $ i=4 $ : let's say Petya decided to make $ 2 $ cyclic shifts, the original array will look like $ a = [\textbf{1}, \textbf{4}, \textbf{3}, \textbf{2}, 5, 6] $ .
- $ i=5 $ : let's say Petya decided to make $ 0 $ cyclic shifts, then the array won't change.
- $ i=6 $ : let's say Petya decided to make $ 4 $ cyclic shifts, the array will look like $ a = [\textbf{3}, \textbf{2}, \textbf{5}, \textbf{6}, \textbf{1}, \textbf{4}] $ .

You are given a final array state $ a $ after all $ n $ operations. Determine if there is a way to perform the operation that produces this result. In this case, if an answer exists, print the numbers of cyclical shifts that occurred during each of the $ n $ operations.

## 说明/提示

The first test case matches the example from the statement.

The second set of input data is simple. Note that the answer $ [3, 2, 1] $ also gives the same permutation, but since the total number of shifts $ 3+2+1 $ is greater than $ 0+0+1 $ , this answer is not correct.

## 样例 #1

### 输入

```
3
6
3 2 5 6 1 4
3
3 1 2
8
5 8 1 3 2 6 4 7```

### 输出

```
0 1 1 2 0 4 
0 0 1 
0 1 2 0 2 5 6 2```

# AI分析结果

### 题目重写
# Twist the Permutation

## 题目描述

Petya 得到了一个包含数字从 1 到 n 的数组 $a$，其中 $a[i]=i$。

他依次执行了 $n$ 次操作。最终，他得到了数组 $a$ 的一个新状态。

在第 $i$ 次操作中，Petya 选择了数组的前 $i$ 个元素，并将它们向右循环移动任意次数（索引为 $i+1$ 及以后的元素保持不变）。一次向右循环移动的变换是将数组 $a=[a_1, a_2, \dots, a_n]$ 变为 $a = [a_i, a_1, a_2, \dots, a_{i-2}, a_{i-1}, a_{i+1}, a_{i+2}, \dots, a_n]$。

例如，如果 $a = [5,4,2,1,3]$ 且 $i=3$（即这是第三次操作），那么这次操作后，他可能得到以下三种数组之一：

- $a = [5,4,2,1,3]$（进行了 0 次循环移动，或任何能被 3 整除的次数）；
- $a = [2,5,4,1,3]$（进行了 1 次循环移动，或任何除以 3 余 1 的次数）；
- $a = [4,2,5,1,3]$（进行了 2 次循环移动，或任何除以 3 余 2 的次数）。

来看一个例子。设 $n=6$，即初始时 $a=[1,2,3,4,5,6]$。一个可能的操作过程如下：

- $i=1$：无论进行多少次循环移动，数组 $a$ 都不会改变。
- $i=2$：假设 Petya 决定进行 1 次循环移动，那么数组将变为 $a = [\textbf{2}, \textbf{1}, 3, 4, 5, 6]$。
- $i=3$：假设 Petya 决定进行 1 次循环移动，那么数组将变为 $a = [\textbf{3}, \textbf{2}, \textbf{1}, 4, 5, 6]$。
- $i=4$：假设 Petya 决定进行 2 次循环移动，数组将变为 $a = [\textbf{1}, \textbf{4}, \textbf{3}, \textbf{2}, 5, 6]$。
- $i=5$：假设 Petya 决定进行 0 次循环移动，那么数组不会改变。
- $i=6$：假设 Petya 决定进行 4 次循环移动，数组将变为 $a = [\textbf{3}, \textbf{2}, \textbf{5}, \textbf{6}, \textbf{1}, \textbf{4}]$。

给定最终数组状态 $a$，判断是否存在一种操作方式能够产生这个结果。如果存在，输出每次操作中进行的循环移动次数。

## 说明/提示

第一个测试用例与题目描述中的例子一致。

第二个输入数据较为简单。注意，答案 $[3, 2, 1]$ 也给出了相同的排列，但由于总移动次数 $3+2+1$ 大于 $0+0+1$，因此这个答案不正确。

## 样例 #1

### 输入

```
3
6
3 2 5 6 1 4
3
3 1 2
8
5 8 1 3 2 6 4 7```

### 输出

```
0 1 1 2 0 4 
0 0 1 
0 1 2 0 2 5 6 2```

### 算法分类
构造

### 题解分析与结论
该题的核心思路是通过逆向思维，从最终状态逐步还原出每次操作的循环移动次数。大多数题解都采用了从后向前处理的策略，通过逐步将数组恢复到初始状态来确定每次操作的移动次数。

### 高星题解推荐
1. **作者：lizhous (赞：7)**
   - **星级：4星**
   - **关键亮点：通过逆向思维，从最终状态逐步还原出每次操作的循环移动次数，代码逻辑清晰，时间复杂度为 $O(n^2)$。**
   - **核心代码：**
     ```cpp
     for (int i = 1; i < n; i++) {
         itt = ton[i]; //当前序列的结尾，就是上次插入的
         it = ton[i + 1]; //从新插入的数往前扫，找到最近的b[j]
         while (a[it] > i) { //往前找b[j]
             it--;
             if (it == 0) it = n;
         }
         while (a[itt] != a[it]) { //在当前b中找到j
             itt--;
             if (itt == 0) itt = n;
             while (a[itt] > i) {
                 itt--;
                 if (itt == 0) itt = n; //指针往前移动模拟一次操作
             }
             ans[i]++; //顺便累加操作次数
         }
     }
     ```

2. **作者：tuxuanming2024 (赞：0)**
   - **星级：4星**
   - **关键亮点：通过倒序处理，逐步将数组恢复到初始状态，代码简洁，时间复杂度为 $O(n^2)$。**
   - **核心代码：**
     ```cpp
     for (int i = n; i >= 1; i--) {
         memset(b, 0, sizeof(b));
         int pos = 1;
         while (a[pos] != i) pos++; //寻找 a[pos]=i 
         if (pos == i) continue; //如果 i 本身就在第 i 个位置，则说明当前轮未进行操作 
         //交换 
         for (int j = pos + 1; j <= i; j++) b[++b[0]] = a[j];
         for (int j = 1; j <= pos; j++) b[++b[0]] = a[j];
         for (int j = i + 1; j <= n; j++) b[++b[0]] = a[j];
         memcpy(a, b, sizeof(b));
         ans[i] += pos; //记录答案 
     }
     ```

3. **作者：DaiRuiChen007 (赞：0)**
   - **星级：4星**
   - **关键亮点：使用双端队列进行逆推，代码实现较为优雅，时间复杂度为 $O(n^2)$。**
   - **核心代码：**
     ```cpp
     for (register int i = n; i >= 1; --i) {
         while (q.back() != i) {
             q.push_back(q.front());
             q.pop_front();
             ++ans[i];
         }
         q.pop_back();
     }
     ```

### 最优关键思路
通过逆向思维，从最终状态逐步还原出每次操作的循环移动次数。这种方法不仅逻辑清晰，而且易于实现，适合处理类似的构造问题。

### 可拓展之处
类似的问题可以通过逆向思维来解决，例如在排列组合问题中，通过从最终状态逐步还原出操作步骤。

### 推荐题目
1. [P1969 积木大赛](https://www.luogu.com.cn/problem/P1969)
2. [P1045 最大子段和](https://www.luogu.com.cn/problem/P1045)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：49.93秒