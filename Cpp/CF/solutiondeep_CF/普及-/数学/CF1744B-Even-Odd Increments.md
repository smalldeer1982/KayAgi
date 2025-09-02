# 题目信息

# Even-Odd Increments

## 题目描述

You are given $ n $ of integers $ a_1, a_2, \ldots, a_n $ . Process $ q $ queries of two types:

- query of the form "0 $ x_j $ ": add the value $ x_j $ to all even elements of the array $ a $ ,
- query of the form "1 $ x_j $ ": add the value $ x_j $ to all odd elements of the array $ a $ .

Note that when processing the query, we look specifically at the odd/even value of $ a_i $ , not its index.

After processing each query, print the sum of the elements of the array $ a $ .

Please note that the answer for some test cases won't fit into 32-bit integer type, so you should use at least 64-bit integer type in your programming language (like long long for C++).

## 说明/提示

In the first test case, the array $ a = [2] $ after the first query.

In the third test case, the array $ a $ is modified as follows: $ [1, 3, 2, 4, 10, 48] $ $ \rightarrow $ $ [7, 9, 2, 4, 10, 48] $ $ \rightarrow $ $ [7, 9, 7, 9, 15, 53] $ $ \rightarrow $ $ [7, 9, 7, 9, 15, 53] $ $ \rightarrow $ $ [10, 12, 10, 12, 18, 56] $ $ \rightarrow $ $ [22, 24, 22, 24, 30, 68] $ $ \rightarrow $ $ [23, 25, 23, 25, 31, 69] $ .

## 样例 #1

### 输入

```
4
1 1
1
1 1
3 3
1 2 4
0 2
1 3
0 5
6 7
1 3 2 4 10 48
1 6
0 5
0 4
0 5
1 3
0 12
0 1
6 7
1000000000 1000000000 1000000000 11 15 17
0 17
1 10000
1 51
0 92
0 53
1 16
0 1```

### 输出

```
2
11
14
29
80
100
100
100
118
190
196
3000000094
3000060094
3000060400
3000060952
3000061270
3000061366
3000061366```

# AI分析结果

### 题目重写
#### Even-Odd Increments

**题目描述**

给定一个包含 $n$ 个整数的数组 $a_1, a_2, \ldots, a_n$。处理 $q$ 次查询，查询分为两种类型：

- 查询形式为 "0 $x_j$"：将值 $x_j$ 加到数组 $a$ 中的所有偶数元素上。
- 查询形式为 "1 $x_j$"：将值 $x_j$ 加到数组 $a$ 中的所有奇数元素上。

注意，在处理查询时，我们关注的是 $a_i$ 的奇偶性，而不是其索引。

在处理完每次查询后，输出数组 $a$ 中所有元素的和。

请注意，某些测试用例的答案可能无法用 32 位整数类型存储，因此你应使用至少 64 位整数类型（如 C++ 中的 `long long`）。

**说明/提示**

在第一个测试用例中，数组 $a = [2]$ 在第一次查询后。

在第三个测试用例中，数组 $a$ 的修改过程如下：$[1, 3, 2, 4, 10, 48]$ $\rightarrow$ $[7, 9, 2, 4, 10, 48]$ $\rightarrow$ $[7, 9, 7, 9, 15, 53]$ $\rightarrow$ $[7, 9, 7, 9, 15, 53]$ $\rightarrow$ $[10, 12, 10, 12, 18, 56]$ $\rightarrow$ $[22, 24, 22, 24, 30, 68]$ $\rightarrow$ $[23, 25, 23, 25, 31, 69]$。

### 题解分析与结论

#### 综合分析与结论
本题的核心在于高效处理多次查询，避免直接遍历数组导致超时。各题解的共同思路是通过统计数组中奇数和偶数的个数，以及数组的总和，来快速计算每次查询后的总和。关键点在于如何处理奇偶性变化的情况，即当加数为奇数时，奇数和偶数的个数会发生变化。

#### 精选题解

1. **作者：深度产业观察 (赞：4)**
   - **星级：4.5**
   - **关键亮点**：思路清晰，代码简洁，直接通过统计奇偶数的个数来快速计算总和，并处理奇偶性变化的情况。
   - **代码核心思想**：
     ```cpp
     if(a==0){
         cnt+=os*b;
         if(b%2!=0){
             js+=os;
             os=0;
         }
     }
     else{
         cnt+=js*b;
         if(b%2!=0){
             os+=js;
             js=0;
         }
     }
     ```
   - **个人心得**：通过统计奇偶数的个数，避免了直接遍历数组，大大提高了效率。

2. **作者：_Haoomff_ (赞：3)**
   - **星级：4**
   - **关键亮点**：详细解释了奇偶性变化的数学原理，代码实现清晰，适合初学者理解。
   - **代码核心思想**：
     ```cpp
     if(x==0){
         ans+=os*y;
         if(y%2==1){
             js+=os;
             os=0;
         }
     }
     else if(x==1){
         ans+=js*y;
         if(y%2==1){
             os+=js;
             js=0;
         }
     }
     ```
   - **个人心得**：通过数学原理推导出奇偶性变化的规律，使得代码实现更加直观。

3. **作者：xiezheyuan (赞：1)**
   - **星级：4**
   - **关键亮点**：通过全局变量维护奇偶数的个数和总和，代码简洁高效，适合竞赛使用。
   - **代码核心思想**：
     ```cpp
     if(op==0){
         sum += even*x;
         if(x&1){
             odd=n;
             even=0;
         }
     }
     else{
         sum += odd*x;
         if(x&1){
             even=n;
             odd=0;
         }
     }
     ```
   - **个人心得**：通过全局变量维护状态，避免了重复计算，提高了代码的效率。

### 最优关键思路与技巧
- **统计奇偶数个数**：通过统计数组中奇数和偶数的个数，可以快速计算每次查询后的总和。
- **处理奇偶性变化**：当加数为奇数时，奇数和偶数的个数会发生变化，需要及时更新。
- **全局变量维护状态**：通过全局变量维护奇偶数的个数和总和，避免重复计算，提高效率。

### 可拓展之处
- **类似问题**：可以扩展到其他需要对数组元素进行分类操作的问题，如根据元素的其他属性（如质数、平方数等）进行分类操作。
- **算法套路**：统计分类元素的个数，通过数学原理推导出操作后的变化规律，避免直接遍历数组。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

---
处理用时：41.59秒