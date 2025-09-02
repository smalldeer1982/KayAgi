# 题目信息

# Find The Array

## 题目描述

You are given an array $ [a_1, a_2, \dots, a_n] $ such that $ 1 \le a_i \le 10^9 $ . Let $ S $ be the sum of all elements of the array $ a $ .

Let's call an array $ b $ of $ n $ integers beautiful if:

- $ 1 \le b_i \le 10^9 $ for each $ i $ from $ 1 $ to $ n $ ;
- for every pair of adjacent integers from the array $ (b_i, b_{i + 1}) $ , either $ b_i $ divides $ b_{i + 1} $ , or $ b_{i + 1} $ divides $ b_i $ (or both);
- $ 2 \sum \limits_{i = 1}^{n} |a_i - b_i| \le S $ .

Your task is to find any beautiful array. It can be shown that at least one beautiful array always exists.

## 样例 #1

### 输入

```
4
5
1 2 3 4 5
2
4 6
2
1 1000000000
6
3 4 8 1 2 3```

### 输出

```
3 3 3 3 3
3 6
1 1000000000
4 4 8 1 3 3```

# AI分析结果

【题目内容】
# 寻找美丽数组

## 题目描述

给定一个数组 $ [a_1, a_2, \dots, a_n] $，其中 $ 1 \le a_i \le 10^9 $。设 $ S $ 为数组 $ a $ 中所有元素的和。

我们称一个长度为 $ n $ 的整数数组 $ b $ 为“美丽数组”，如果它满足以下条件：

- 对于每个 $ i $，$ 1 \le b_i \le 10^9 $；
- 对于数组 $ b $ 中的每一对相邻整数 $ (b_i, b_{i + 1}) $，要么 $ b_i $ 整除 $ b_{i + 1} $，要么 $ b_{i + 1} $ 整除 $ b_i $（或两者都满足）；
- $ 2 \sum \limits_{i = 1}^{n} |a_i - b_i| \le S $。

你的任务是找到任意一个美丽数组。可以证明至少存在一个美丽数组。

## 样例 #1

### 输入

```
4
5
1 2 3 4 5
2
4 6
2
1 1000000000
6
3 4 8 1 2 3```

### 输出

```
3 3 3 3 3
3 6
1 1000000000
4 4 8 1 3 3```

【算法分类】
构造

【题解分析与结论】
本题的核心在于构造一个满足条件的“美丽数组”。大多数题解都围绕如何减少 $ \sum |a_i - b_i| $ 来满足 $ 2 \sum |a_i - b_i| \le S $ 这一条件。常见的思路包括：

1. **奇偶位替换法**：通过将奇数位或偶数位的 $ b_i $ 替换为 $ a_i $，从而减少 $ \sum |a_i - b_i| $。这种方法简单直观，且通过数学证明可以确保至少有一种情况满足条件。
2. **2的幂次法**：利用 $ 2^k $ 的性质，使得 $ |a_i - b_i| \le \frac{a_i}{2} $，从而满足 $ 2 \sum |a_i - b_i| \le S $。这种方法利用了二进制的特性，确保相邻元素之间满足整除关系。

【高星题解】
1. **作者：Eddie08012025 (5星)**
   - **关键亮点**：通过奇偶位替换法，简单直观地构造美丽数组，并通过数学证明确保至少有一种情况满足条件。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++){
         if(i%2==1)cout<<"1 ";
         else cout<<a[i]<<" ";
     }
     ```

2. **作者：ThySecret (4星)**
   - **关键亮点**：利用 $ 2^k $ 的性质，确保 $ |a_i - b_i| \le \frac{a_i}{2} $，并通过树状数组中的 `lowbit` 操作快速找到合适的 $ 2^k $。
   - **代码核心**：
     ```cpp
     int x = a[i];
     while (x - lowbit(x)) x -= lowbit(x);
     cout << x << " \n"[i == n];
     ```

3. **作者：naroanah (4星)**
   - **关键亮点**：同样利用 $ 2^k $ 的性质，通过 `__lg` 函数快速找到小于等于 $ a_i $ 的最大 $ 2^k $，确保满足条件。
   - **代码核心**：
     ```cpp
     cout << (1 << __lg(x)) << " \n"[i == n];
     ```

【最优关键思路】
- **奇偶位替换法**：通过将奇数位或偶数位的 $ b_i $ 替换为 $ a_i $，确保至少有一种情况满足 $ 2 \sum |a_i - b_i| \le S $。这种方法简单直观，且易于实现。
- **2的幂次法**：利用 $ 2^k $ 的性质，确保 $ |a_i - b_i| \le \frac{a_i}{2} $，从而满足条件。这种方法利用了二进制的特性，确保相邻元素之间满足整除关系。

【可拓展之处】
- 类似构造题可以通过奇偶位替换或利用数的性质（如 $ 2^k $）来满足特定条件。
- 同类型题：洛谷 P1463、P1464、P1465。

【推荐题目】
1. 洛谷 P1463 - [构造数组](https://www.luogu.com.cn/problem/P1463)
2. 洛谷 P1464 - [美丽数组](https://www.luogu.com.cn/problem/P1464)
3. 洛谷 P1465 - [数组构造](https://www.luogu.com.cn/problem/P1465)

---
处理用时：36.25秒