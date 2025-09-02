---
title: "MAIN74 - Euclids algorithm revisited"
layout: "post"
diff: 提高+/省选-
pid: SP8547
tag: []
---

# MAIN74 - Euclids algorithm revisited

## 题目描述

Consider the famous euclid algoithm to calculate the GCD of two integers (a, b):

 ```

int gcd(int a, int b) {
    while (b != 0) {
        int temp = a;
        a = b;
        b = temp % b;
    }
    return a;
}
```
for input (7, 3) the 'while' loop will run 2 times as follows: (7, 3) => (3, 1) => (1, 0)

Now given an integer N you have to find the smallest possible sum of two non-negative integers a, b (a >= b) such that the while loop in the above mentioned function for (a, b) will run exactly N times.

## 输入格式

First line of input contains T (1 <= T <= 50) the number of test cases. Each of the following T lines contains an integer N (0 <= N <= 10^18).

## 输出格式

For each test case print the required answer modulo 1000000007 in a seperate line.

## 样例 #1

### 输入

```
1
1
```

### 输出

```
2
```

