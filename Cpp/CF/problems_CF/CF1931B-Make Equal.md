---
title: "Make Equal"
layout: "post"
diff: 普及-
pid: CF1931B
tag: ['前缀和']
---

# Make Equal

## 题目描述

There are $ n $ containers of water lined up, numbered from left to right from $ 1 $ to $ n $ . Each container can hold any amount of water; initially, the $ i $ -th container contains $ a_i $ units of water. The sum of $ a_i $ is divisible by $ n $ .

You can apply the following operation any (possibly zero) number of times: pour any amount of water from the $ i $ -th container to the $ j $ -th container, where $ i $ must be less than $ j $ (i.e. $ i<j $ ). Any index can be chosen as $ i $ or $ j $ any number of times.

Determine whether it is possible to make the amount of water in all containers the same using this operation.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then the descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of containers with water.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the amounts of water in the containers. It is guaranteed that the sum of $ a_i $ in each test case does not exceed $ 2 \cdot 10^9 $ . Also, the sum of $ a_i $ is divisible by $ n $ .

It is guaranteed that the sum of $ n $ over all test cases in the input does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Output $ t $ lines, each of which is the answer to the corresponding test case. As the answer, output "YES" if it is possible to make the amount of water in all containers the same using the described operation. Otherwise, output "NO".

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 说明/提示

In the third test case of the example ( $ a=[4, 5, 2, 1, 3] $ ), you can proceed as follows:

- pour $ 1 $ unit of water from the first vessel to the fourth, then $ a=[3, 5, 2, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the third, then $ a=[3, 4, 3, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the fourth, then $ a=[3, 3, 3, 3, 3] $ .

## 样例 #1

### 输入

```
6
1
43
2
1 3
5
4 5 2 1 3
3
1 2 3
7
4 5 5 0 6 4 4
7
6 5 5 1 3 4 4
```

### 输出

```
YES
NO
YES
NO
NO
YES
```

