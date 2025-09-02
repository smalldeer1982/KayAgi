# Too Min Too Max

## 题目描述

Given an array $ a $ of $ n $ elements, find the maximum value of the expression:

 $ $$$|a_i - a_j| + |a_j - a_k| + |a_k - a_l| + |a_l - a_i| $ $ </p><p>where  $ i $ ,  $ j $ ,  $ k $ , and  $ l $  are four <span class="tex-font-style-bf">distinct</span> indices of the array  $ a $ , with  $ 1 \\le i, j, k, l \\le n $ .</p><p>Here  $ |x| $  denotes the absolute value of  $ x$$$.

## 说明/提示

In the first test case, for any selection of $ i $ , $ j $ , $ k $ , $ l $ , the answer will be $ 0 $ . For example, $ |a_1 - a_2| + |a_2 - a_3| + |a_3 - a_4| + |a_4 - a_1| = |1 - 1| + |1 - 1| + |1 - 1| + |1 - 1| = 0 + 0 + 0 + 0 = 0 $ .

In the second test case, for $ i = 1 $ , $ j = 3 $ , $ k = 2 $ , and $ l = 5 $ , the answer will be $ 6 $ . $ |a_1 - a_3| + |a_3 - a_2| + |a_2 - a_5| + |a_5 - a_1| = |1 - 2| + |2 - 1| + |1 - 3| + |3 - 1| = 1 + 1 + 2 + 2 = 6 $ .

## 样例 #1

### 输入

```
5
4
1 1 1 1
5
1 1 2 2 3
8
5 1 3 2 -3 -1 10 3
4
3 3 1 1
4
1 2 2 -1```

### 输出

```
0
6
38
8
8```

