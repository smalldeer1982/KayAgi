---
title: "StORage room"
layout: "post"
diff: 普及-
pid: CF1903B
tag: []
---

# StORage room

## 题目描述

In Cyprus, the weather is pretty hot. Thus, Theofanis saw this as an opportunity to create an ice cream company.

He keeps the ice cream safe from other ice cream producers by locking it inside big storage rooms. However, he forgot the password. Luckily, the lock has a special feature for forgetful people!

It gives you a table $ M $ with $ n $ rows and $ n $ columns of non-negative integers, and to open the lock, you need to find an array $ a $ of $ n $ elements such that:

- $ 0 \le a_i < 2^{30} $ , and
- $ M_{i,j} = a_i | a_j $ for all $ i \neq j $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

The lock has a bug, and sometimes it gives tables without any solutions. In that case, the ice cream will remain frozen for the rest of eternity.

Can you find an array to open the lock?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^{3} $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^{3} $ ) — the size of the hidden array.

The next $ n $ lines describe the rows of $ M $ , line $ i $ contains the table values $ M_{i,1}, M_{i,2}, \ldots, M_{i,n} $ ( $ 0 \le M_{i,j} < 2^{30} $ ).

It is guaranteed that $ M_{i,i} = 0 $ and $ M_{i,j} = M_{j,i} $ for all $ 1 \le i,j \le n $ .

It is also guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^{3} $ .

## 输出格式

For each test case, if there is a solution print YES and an array that satisfies the property, otherwise print NO.

If there are multiple solutions, print any of them.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 样例 #1

### 输入

```
4
1
0
4
0 3 3 5
3 0 3 7
3 3 0 7
5 7 7 0
5
0 7 7 5 5
7 0 3 2 6
7 3 0 3 7
5 2 3 0 4
5 6 7 4 0
3
0 0 1
0 0 0
1 0 0
```

### 输出

```
YES
7
YES
1 3 2 5 
YES
5 2 3 0 4
NO
```

