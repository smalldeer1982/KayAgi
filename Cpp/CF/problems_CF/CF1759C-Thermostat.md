---
title: "Thermostat"
layout: "post"
diff: 普及-
pid: CF1759C
tag: []
---

# Thermostat

## 题目描述

Vlad came home and found out that someone had reconfigured the old thermostat to the temperature of $ a $ .

The thermostat can only be set to a temperature from $ l $ to $ r $ inclusive, the temperature cannot change by less than $ x $ . Formally, in one operation you can reconfigure the thermostat from temperature $ a $ to temperature $ b $ if $ |a - b| \ge x $ and $ l \le b \le r $ .

You are given $ l $ , $ r $ , $ x $ , $ a $ and $ b $ . Find the minimum number of operations required to get temperature $ b $ from temperature $ a $ , or say that it is impossible.

## 输入格式

The first line of input data contains the single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the test.

The descriptions of the test cases follow.

The first line of each case contains three integers $ l $ , $ r $ and $ x $ ( $ -10^9 \le l \le r \le 10^9 $ , $ 1 \le x \le 10^9 $ ) — range of temperature and minimum temperature change.

The second line of each case contains two integers $ a $ and $ b $ ( $ l \le a, b \le r $ ) — the initial and final temperatures.

## 输出格式

Output $ t $ numbers, each of which is the answer to the corresponding test case. If it is impossible to achieve the temperature $ b $ , output -1, otherwise output the minimum number of operations.

## 说明/提示

In the first example, the thermostat is already set up correctly.

In the second example, you can achieve the desired temperature as follows: $ 4 \rightarrow 10 \rightarrow 5 $ .

In the third example, you can achieve the desired temperature as follows: $ 3 \rightarrow 8 \rightarrow 2 \rightarrow 7 $ .

In the fourth test, it is impossible to make any operation.

## 样例 #1

### 输入

```
10
3 5 6
3 3
0 15 5
4 5
0 10 5
3 7
3 5 6
3 4
-10 10 11
-5 6
-3 3 4
1 0
-5 10 8
9 2
1 5 1
2 5
-1 4 3
0 2
-6 3 6
-1 -4
```

### 输出

```
0
2
3
-1
1
-1
3
1
3
-1
```

