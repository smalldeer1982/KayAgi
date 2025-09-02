# 题目信息

# Look Back

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ . You need to make it non-decreasing with the minimum number of operations. In one operation, you do the following:

- Choose an index $ 1 \leq i \leq n $ ,
- Set $ a_i = a_i \cdot 2 $ .

An array $ b_1, b_2, \ldots, b_n $ is non-decreasing if $ b_i \leq b_{i+1} $ for all $ 1 \leq i < n $ .

## 说明/提示

No operations are needed in the first test case.

In the second test case, we need to choose $ i = 2 $ , after which the array will be $ [2, 2] $ .

In the third test case, we can apply the following operations:

- Choose $ i = 3 $ , after which the array will be $ [3, 2, 2] $ ,
- Choose $ i = 3 $ , after which the array will be $ [3, 2, 4] $ ,
- Choose $ i = 2 $ , after which the array will be $ [3, 4, 4] $ .

## 样例 #1

### 输入

```
9
1
1
2
2 1
3
3 2 1
4
7 1 5 3
5
11 2 15 7 10
6
1 8 2 16 8 16
2
624323799 708290323
12
2 1 1 3 3 11 12 22 45 777 777 1500
12
12 11 10 9 8 7 6 5 4 3 2 1```

### 输出

```
0
1
3
6
10
3
0
2
66```

# AI分析结果

【题目翻译】
# 回头看

## 题目描述

给定一个整数数组 $a_1, a_2, \ldots, a_n$，你需要通过最少的操作使其变为非递减数组。每次操作可以选择一个索引 $1 \leq i \leq n$，并将 $a_i$ 乘以 2。

一个数组 $b_1, b_2, \ldots, b_n$ 是非递减的，当且仅当对于所有 $1 \leq i < n$，有 $b_i \leq b_{i+1}$。

## 说明/提示

在第一个测试用例中，不需要任何操作。

在第二个测试用例中，需要选择 $i = 2$，操作后数组变为 $[2, 2]$。

在第三个测试用例中，可以进行以下操作：

- 选择 $i = 3$，操作后数组变为 $[3, 2, 2]$，
- 选择 $i = 3$，操作后数组变为 $[3, 2, 4]$，
- 选择 $i = 2$，操作后数组变为 $[3, 4, 4]$。

【算法分类】
贪心

【题解分析与结论】
该题的核心思路是通过贪心策略，确保每个元素在尽可能少的操作下满足非递减条件。大多数题解都采用了类似的方法：通过计算相邻元素的差值，确定需要乘以 2 的次数，并利用前缀和来累计总操作次数。难点在于如何高效地计算这些差值，避免直接暴力乘 2 导致的时间复杂度过高或数据溢出。

【评分较高的题解】
1. **作者：One_JuRuo (赞：14)**  
   - **星级：5**  
   - **关键亮点**：通过计算相邻元素的差值，利用前缀和来累计操作次数，避免了暴力乘 2 的问题。代码简洁且高效。  
   - **核心代码**：
     ```cpp
     while(l<r) l<<=1,++c1; // 少乘几个2
     while(l>r) r<<=1,++c2; // 多乘几个2
     sum += c2 - c1, sum = max(0ll, sum), ans += sum;
     ```
   - **个人心得**：通过将问题转化为差值的计算，大大减少了时间复杂度。

2. **作者：N_Position (赞：4)**  
   - **星级：4**  
   - **关键亮点**：将每个数的操作次数 $t_i$ 作为状态进行转移，利用对数函数计算差值，避免了数据溢出的问题。  
   - **核心代码**：
     ```cpp
     if(a[i] >= a[i-1]) t[i] = max(0ll, t[i-1] - floor(log2((double)a[i]/a[i-1])));
     if(a[i] < a[i-1]) t[i] = max(0ll, t[i-1] + ceil(log2((double)a[i-1]/a[i])));
     ```
   - **个人心得**：通过引入对数函数，简化了计算过程，避免了高精度问题。

3. **作者：ZLCT (赞：0)**  
   - **星级：4**  
   - **关键亮点**：通过差分思想，将问题转化为差分数组的非负性检查，避免了直接乘 2 的操作。  
   - **核心代码**：
     ```cpp
     c[i] = make_c(a[i-1], a[i]); // 计算差值
     c[i] += c[i-1], c[i] = max(0ll, c[i]); // 累计操作次数
     ```
   - **个人心得**：通过差分数组的优化，避免了直接乘 2 的操作，提高了效率。

【最优关键思路】
通过计算相邻元素的差值，利用前缀和或差分数组来累计操作次数，避免了直接暴力乘 2 的问题。这种方法不仅高效，还能有效避免数据溢出。

【可拓展之处】
类似的问题可以通过差分或前缀和的思想来解决，尤其是在处理需要多次操作或累加的场景中。例如，处理数组的递增或递减问题时，可以考虑通过计算差值来优化操作次数。

【推荐题目】
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)

---
处理用时：27.38秒