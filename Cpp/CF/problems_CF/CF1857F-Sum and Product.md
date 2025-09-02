---
title: "Sum and Product"
layout: "post"
diff: 普及+/提高
pid: CF1857F
tag: []
---

# Sum and Product

## 题目描述

You have an array $ a $ of length $ n $ .

Your task is to answer $ q $ queries: given $ x,y $ , find the number of pairs $ i $ and $ j $ ( $ 1 \le i < j \le n $ ) that both $ a_i + a_j = x $ and $ a_i \cdot a_j = y $ .

That is, for the array $ [1,3,2] $ and asking for $ x=3,y=2 $ the answer is $ 1 $ :

- $ i=1 $ and $ j=2 $ fail because $ 1 + 3 = 4 $ and not $ 3, $ also $ 1 \cdot 3=3 $ and not $ 2 $ ;
- $ i=1 $ and $ j=3 $ satisfies both conditions;
- $ i=2 $ and $ j=3 $ fail because $ 3 + 2 = 5 $ and not $ 3, $ also $ 3 \cdot 2=6 $ and not $ 2 $ ;

## 输入格式

The first line contains one integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

The second line of each test case contains one integer $ n $ ( $ 1 \le n \le 2\cdot 10^5 $ ) — the length of the array $ a $ .

The third line of each test case contains $ n $ integers $ a_1,a_2,\dots,a_n $ ( $ 1 \le |a_i| \le 10^9 $ ) — array $ a $ .

The fourth line of each test case contains the integer $ q $ ( $ 1 \le q \le 2\cdot 10^5 $ ) — the number of requests.

The next $ q $ lines contain two numbers each $ x $ and $ y $ ( $ 1 \le |x|\le 2\cdot 10^9,1\le |y|\le 10^{18} $ ) — request.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ . This is also guaranteed for the sum of $ q $ values.

## 输出格式

For each test case print a line with $ q $ numbers — the answers to the queries.

## 说明/提示

For the first test case, let's analyze each pair of numbers separately:

- pair $ (a_1,a_2) $ : $ a_1 + a_2 = 4 $ , $ a_1 \cdot a_2 = 3 $
- pair $ (a_1,a_3) $ : $ a_1 + a_3 = 3 $ , $ a_1 \cdot a_3 = 2 $
- pair $ (a_2,a_3) $ : $ a_2 + a_3 = 5 $ , $ a_2 \cdot a_3 = 6 $

 From this, we can see that for the first query, the pair $ (a_1,a_3) $ is suitable, for the second query, it is $ (a_2,a_3) $ , and there are no suitable pairs for the third and fourth queries.In the second test case, all combinations of pairs are suitable.

## 样例 #1

### 输入

```
3
3
1 3 2
4
3 2
5 6
3 1
5 5
4
1 1 1 1
1
2 1
6
1 4 -2 3 3 3
3
2 -8
-1 -2
7 12
```

### 输出

```
1 1 0 0 
6 
1 1 3
```

