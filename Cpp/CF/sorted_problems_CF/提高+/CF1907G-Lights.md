---
title: "Lights"
layout: "post"
diff: 提高+/省选-
pid: CF1907G
tag: []
---

# Lights

## 题目描述

In the end of the day, Anna needs to turn off the lights in the office. There are $ n $ lights and $ n $ light switches, but their operation scheme is really strange. The switch $ i $ changes the state of light $ i $ , but it also changes the state of some other light $ a_i $ (change the state means that if the light was on, it goes off and vice versa).

Help Anna to turn all the lights off using minimal number of switches, or say it is impossible.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Descriptions of test cases follow.

The first line of each test case contains the integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the number of lights.

The second line of each test case contains the string of $ n $ characters, the initial state of the lights. Character "0" means that the corresponding light is off, and "1" means that it is on.

The third line of each test case contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le n $ , $ a_i \neq i $ ) — the switch $ i $ changes the states of light $ i $ and light $ a_i $ .

It is guaranteed that sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $

## 输出格式

For each test case output the integer $ k $ , the minimal number of switches to use, then in the separate line output the list of $ k $ switches.

If it is impossible to turn off all the lights, output single integer $ -1 $ .

## 样例 #1

### 输入

```
8
5
11101
4 3 4 2 2
2
10
2 1
10
0000000011
9 10 10 7 10 9 9 9 10 2
10
1000111101
9 3 8 9 2 1 3 7 2 7
10
0001101010
5 7 6 10 8 3 6 6 2 2
10
0101100010
8 7 7 9 9 4 1 4 2 7
10
1010111010
7 9 10 7 7 2 8 6 10 4
10
1110000001
3 10 10 1 10 8 6 3 2 1
```

### 输出

```
3
1 5 3 
-1
1
9 
5
5 6 10 2 3 
6
4 9 5 10 8 7 
3
5 4 9 
6
1 3 5 9 7 8 
2
2 1
```

