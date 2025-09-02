---
title: "Destroyer"
layout: "post"
diff: 入门
pid: CF1836A
tag: []
---

# Destroyer

## 题目描述

John is a lead programmer on a destroyer belonging to the space navy of the Confederacy of Independent Operating Systems. One of his tasks is checking if the electronic brains of robots were damaged during battles.

A standard test is to order the robots to form one or several lines, in each line the robots should stand one after another. After that, each robot reports the number of robots standing in front of it in its line.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1836A/4852f684dc3056e14effb6b67744c8fa8dbee24a.png) An example of robots' arrangement (the front of the lines is on the left). The robots report the numbers above.The $ i $ -th robot reported number $ l_i $ . Unfortunately, John does not know which line each robot stands in, and can't check the reported numbers. Please determine if it is possible to form the lines in such a way that all reported numbers are correct, or not.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ), denoting the number of test cases.

The first line in each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ) — the number of robots.

The second line in each test case contains $ n $ integers $ l_1, l_2, \ldots, l_n $ ( $ 0 \leq l_i < 100 $ ), $ l_i $ is equal to the number of robots in front of the $ i $ -th robot in its line.

The sum of $ n $ over all test cases won't exceed $ 200 $ .

## 输出格式

For each test case, output "YES", if there exists a robot arrangement consistent with robots' reports. Otherwise, output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

Example arrangement consistent with robot statements from the first example test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1836A/43b66909972c39c8c77ebbd5fb94cd377f6488da.png)Example arrangement consistent with robot statements from the second example is shown in the statement.

In the third test case, the third robot claims that there are two machines in front of it. In such a case, the robot directly in front of it would have one machine in front. No robot claims that, so there is no valid arrangement.

## 样例 #1

### 输入

```
5
6
0 1 2 0 1 0
9
0 0 0 0 1 1 1 2 2
3
0 0 2
1
99
5
0 1 2 3 4
```

### 输出

```
YES
YES
NO
NO
YES
```

