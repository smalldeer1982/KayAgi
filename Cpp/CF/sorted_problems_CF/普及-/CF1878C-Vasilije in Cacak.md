---
title: "Vasilije in Cacak"
layout: "post"
diff: 普及-
pid: CF1878C
tag: []
---

# Vasilije in Cacak

## 题目描述

Aca and Milovan, two fellow competitive programmers, decided to give Vasilije a problem to test his skills.

Vasilije is given three positive integers: $ n $ , $ k $ , and $ x $ , and he has to determine if he can choose $ k $ distinct integers between $ 1 $ and $ n $ , such that their sum is equal to $ x $ .

Since Vasilije is now in the weirdest city in Serbia where Aca and Milovan live, Cacak, the problem seems weird to him. So he needs your help with this problem.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The only line of each test case contains three integers $ n $ , $ k $ and $ x $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le k \le n $ , $ 1 \le x \le 4 \cdot 10^{10} $ ) — the maximum element he can choose, the number of elements he can choose and the sum he has to reach.

Note that the sum of $ n $ over all test cases may exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output one line: "YES", if it is possible to choose $ k $ distinct integers between $ 1 $ and $ n $ , such that their sum is equal to $ x $ , and "NO", if it isn't.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as a positive answer).

## 说明/提示

In the first test case $ n = 5,\ k=3,\ x=10 $ , so we can choose the numbers: $ 2 $ , $ 3 $ , $ 5 $ , whose sum is $ 10 $ , so the answer is "YES".

In the second test case $ n = 5, \ k=3, \ x=3 $ , there is no three numbers which satisfies the condition, so the answer is "NO". It can be shown that there are no three numbers whose sum is $ 3 $ .

## 样例 #1

### 输入

```
12
5 3 10
5 3 3
10 10 55
6 5 20
2 1 26
187856 87856 2609202300
200000 190000 19000000000
28 5 2004
2 2 2006
9 6 40
47202 32455 613407217
185977 145541 15770805980
```

### 输出

```
YES
NO
YES
YES
NO
NO
YES
NO
NO
NO
YES
YES
```

