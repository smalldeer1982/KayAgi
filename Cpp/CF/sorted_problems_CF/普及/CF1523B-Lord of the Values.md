---
title: "Lord of the Values"
layout: "post"
diff: 普及/提高-
pid: CF1523B
tag: []
---

# Lord of the Values

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523B/98f109d71d38cfa25029619d650ed4d2b886de82.png)While trading on his favorite exchange trader William realized that he found a vulnerability. Using this vulnerability he could change the values of certain internal variables to his advantage. To play around he decided to change the values of all internal variables from $ a_1, a_2, \ldots, a_n $ to $ -a_1, -a_2, \ldots, -a_n $ . For some unknown reason, the number of service variables is always an even number.

William understands that with his every action he attracts more and more attention from the exchange's security team, so the number of his actions must not exceed $ 5\,000 $ and after every operation no variable can have an absolute value greater than $ 10^{18} $ . William can perform actions of two types for two chosen variables with indices $ i $ and $ j $ , where $ i < j $ :

1. Perform assignment $ a_i = a_i + a_j $
2. Perform assignment $ a_j = a_j - a_i $

 William wants you to develop a strategy that will get all the internal variables to the desired values.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 20 $ ). Description of the test cases follows.

The first line of each test case contains a single even integer $ n $ ( $ 2 \le n \le 10^3 $ ), which is the number of internal variables.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ $ (1 \le a_i \le 10^9) $ , which are initial values of internal variables.

## 输出格式

For each test case print the answer in the following format:

The first line of output must contain the total number of actions $ k $ , which the strategy will perform. Note that you do not have to minimize $ k $ . The inequality $ k \le 5\,000 $ must be satisfied.

Each of the next $ k $ lines must contain actions formatted as "type i j", where "type" is equal to "1" if the strategy needs to perform an assignment of the first type and "2" if the strategy needs to perform an assignment of the second type. Note that $ i < j $ should hold.

We can show that an answer always exists.

## 说明/提示

For the first sample test case one possible sequence of operations is as follows:

1. "2 1 2". Values of variables after performing the operation: \[1, 0, 1, 1\]
2. "2 1 2". Values of variables after performing the operation: \[1, -1, 1, 1\]
3. "2 1 3". Values of variables after performing the operation: \[1, -1, 0, 1\]
4. "2 1 3". Values of variables after performing the operation: \[1, -1, -1, 1\]
5. "2 1 4". Values of variables after performing the operation: \[1, -1, -1, 0\]
6. "2 1 4". Values of variables after performing the operation: \[1, -1, -1, -1\]
7. "1 1 2". Values of variables after performing the operation: \[0, -1, -1, -1\]
8. "1 1 2". Values of variables after performing the operation: \[-1, -1, -1, -1\]

For the second sample test case one possible sequence of operations is as follows:

1. "2 1 4". Values of variables after performing the operation: \[4, 3, 1, -2\]
2. "1 2 4". Values of variables after performing the operation: \[4, 1, 1, -2\]
3. "1 2 4". Values of variables after performing the operation: \[4, -1, 1, -2\]
4. "1 2 4". Values of variables after performing the operation: \[4, -3, 1, -2\]
5. "1 3 4". Values of variables after performing the operation: \[4, -3, -1, -2\]
6. "1 1 2". Values of variables after performing the operation: \[1, -3, -1, -2\]
7. "1 1 2". Values of variables after performing the operation: \[-2, -3, -1, -2\]
8. "1 1 4". Values of variables after performing the operation: \[-4, -3, -1, -2\]

## 样例 #1

### 输入

```
2
4
1 1 1 1
4
4 3 1 2
```

### 输出

```
8
2 1 2
2 1 2
2 1 3
2 1 3
2 1 4
2 1 4
1 1 2
1 1 2
8
2 1 4
1 2 4
1 2 4
1 2 4
1 3 4
1 1 2
1 1 2
1 1 4
```

