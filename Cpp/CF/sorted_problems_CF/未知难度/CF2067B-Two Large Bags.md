---
title: "Two Large Bags"
layout: "post"
diff: 难度0
pid: CF2067B
tag: []
---

# Two Large Bags

## 题目描述

You have two large bags of numbers. Initially, the first bag contains $ n $ numbers: $ a_1, a_2, \ldots, a_n $ , while the second bag is empty. You are allowed to perform the following operations:

- Choose any number from the first bag and move it to the second bag.
- Choose a number from the first bag that is also present in the second bag and increase it by one.

You can perform an unlimited number of operations of both types, in any order. Is it possible to make the contents of the first and second bags identical?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 2 \le n \le 1000 $ ) — the length of the array $ a $ . It is guaranteed that $ n $ is an even number.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ).

It is guaranteed that the sum of $ n^2 $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, print "YES" if it is possible to equalize the contents of the bags. Otherwise, output "NO".

You can output each letter in any case (for example, "YES", "Yes", "yes", "yEs", "yEs" will be recognized as a positive answer).

## 说明/提示

Let's analyze the sixth test case: we will show the sequence of operations that leads to the equality of the bags. Initially, the first bag consists of the numbers $ (3, 3, 4, 5, 3, 3) $ , and the second bag is empty.

1. In the first operation, move the number $ 3 $ from the first bag to the second. State: $ (3, 4, 5, 3, 3) $ and $ (3) $ .
2. In the second operation, increase the number $ 3 $ from the first bag by one. This operation is possible because the second bag contains the number $ 3 $ . State: $ (4, 4, 5, 3, 3) $ and $ (3) $ .
3. In the third operation, move the number $ 4 $ from the first bag to the second. State: $ (4, 5, 3, 3) $ and $ (3, 4) $ .
4. In the fourth operation, increase the number $ 4 $ from the first bag by one. State: $ (5, 5, 3, 3) $ and $ (3, 4) $ .
5. In the fifth operation, move the number $ 5 $ from the first bag to the second. State: $ (5, 3, 3) $ and $ (3, 4, 5) $ .
6. In the sixth operation, increase the number $ 3 $ from the first bag by one. State: $ (5, 3, 4) $ and $ (3, 4, 5) $ .

As we can see, as a result of these operations, it is possible to make the contents of the bags equal, so the answer exists.

## 样例 #1

### 输入

```
9
2
1 1
2
2 1
4
1 1 4 4
4
3 4 3 3
4
2 3 4 4
6
3 3 4 5 3 3
6
2 2 2 4 4 4
8
1 1 1 1 1 1 1 4
10
9 9 9 10 10 10 10 10 10 10
```

### 输出

```
Yes
No
Yes
Yes
No
Yes
No
Yes
Yes
```

