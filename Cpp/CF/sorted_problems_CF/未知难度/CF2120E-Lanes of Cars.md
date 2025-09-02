---
title: "Lanes of Cars"
layout: "post"
diff: 难度0
pid: CF2120E
tag: []
---

# Lanes of Cars

## 题目描述

Harshith is the president of TollClub. He tasks his subordinate Aryan to oversee a toll plaza with $ n $ lanes. Initially, the $ i $ -th lane has $ a_i $ cars waiting in a queue. Exactly one car from the front of each lane passes through the toll every second.

The angriness of a car is defined as the number of seconds it had to wait before passing through the toll. Consider it takes 1 sec for each car to pass the toll, i.e., the first car in a lane has angriness $ 1 $ , the second car has angriness $ 2 $ , and so on.

To reduce congestion and frustration, cars are allowed to switch lanes. A car can instantly move to the back of any other lane at any time. However, changing lanes increases its angriness by an additional $ k $ units due to the confusion caused by the lane change.

Harshith, being the awesome person he is, wants to help the drivers by minimising the total angriness of all cars. He asks Aryan to do so or get fired. Aryan is allowed to change lanes of any car anytime (possibly zero), but his goal is to find the minimum possible total angriness if the lane changes are done optimally. Help Aryan retain his job by determining the minimum angriness he can achieve.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le k \le 10^6 $ ) — the number of lanes and the increment in angriness on a lane change.

The second line of each test case contains $ n $ space-separated integers, denoting array $ a $ — the $ i $ -th number representing the number of cars in the $ i $ -th lane ( $ 1 \le a_i \le 10^6 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

Note that the sum of $ \max a_i $ over all test cases is not bounded.

## 输出格式

For each test case, output a single integer in a new line, denoting the minimum total angriness.

## 说明/提示

In the first test case, Aryan shifts two cars from lane $ 1 $ to lane $ 3 $ , after which the array becomes $ [11, 7, 6] $ . The total angriness is $ \frac{11\cdot 12}{2}+\frac{7\cdot 8}{2}+\frac{6\cdot 7}{2}+2\cdot 4=123 $ . It can be proven that this is the minimum possible angriness.

In the fourth test case, there is only one lane, so cars can't shift lanes. Total angriness is $ \frac{6\cdot7}{2}=21 $ .

## 样例 #1

### 输入

```
6
3 4
13 7 4
4 9
6 12 14 5
5 3
2 4 13 5 10
1 7
6
13 4
10 26 34 39 9 43 48 41 1 38 13 4 46
16 3
176342 171863 70145 80835 160257 136105 78541 100795 114461 45482 68210 51656 29593 8750 173743 156063
```

### 输出

```
123
219
156
21
5315
82302351405
```

