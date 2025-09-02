---
title: "Kirchhoff's Current Loss"
layout: "post"
diff: 省选/NOI-
pid: CF1280E
tag: []
---

# Kirchhoff's Current Loss

## 题目描述

Your friend Kirchhoff is shocked with the current state of electronics design.

"Ohmygosh! Watt is wrong with the field? All these circuits are inefficient! There's so much capacity for improvement. The electrical engineers must not conduct their classes very well. It's absolutely revolting" he said.

The negativity just keeps flowing out of him, but even after complaining so many times he still hasn't lepton the chance to directly change anything.

"These circuits have too much total resistance. Wire they designed this way? It's just causing a massive loss of resistors! Their entire field could conserve so much money if they just maximized the potential of their designs. Why can't they just try alternative ideas?"

The frequency of his protests about the electrical engineering department hertz your soul, so you have decided to take charge and help them yourself. You plan to create a program that will optimize the circuits while keeping the same circuit layout and maintaining the same effective resistance.

A circuit has two endpoints, and is associated with a certain constant, $ R $ , called its effective resistance.

The circuits we'll consider will be formed from individual resistors joined together in series or in parallel, forming more complex circuits. The following image illustrates combining circuits in series or parallel.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280E/28f2a272e8afd0f2565ec77a5e038d7431f9ecf6.png)According to your friend Kirchhoff, the effective resistance can be calculated quite easily when joining circuits this way:

- When joining $ k $ circuits in series with effective resistances $ R_1, R_2, \ldots, R_k $ , the effective resistance $ R $ of the resulting circuit is the sum $ $$$R = R_1 + R_2 + \ldots + R_k. $ $ <p> </p></li><li> When joining  $ k $  circuits in <span class="tex-font-style-underline">parallel</span> with effective resistances  $ R\_1, R\_2, \\ldots, R\_k $ , the effective resistance  $ R $  of the resulting circuit is found by solving for  $ R $  in  $ $ \frac{1}{R} = \frac{1}{R_1} + \frac{1}{R_2} + \ldots + \frac{1}{R_k}, $ $  <span class="tex-font-style-underline">assuming all  $ R\_i > 0 $ </span>; if at least one  $ R\_i = 0 $ , then the effective resistance of the whole circuit is simply  $ R = 0 $ . </li></ul><p>Circuits will be represented by strings. Individual resistors are represented by an asterisk, "<span class="tex-font-style-tt">*</span>". For more complex circuits, suppose  $ s\_1, s\_2, \\ldots, s\_k $  represent  $ k \\ge 2 $  circuits. Then:</p><ul> <li> "<span class="tex-font-style-tt">( $ s\_1 $  S  $ s\_2 $  S  $ \\ldots $  S  $ s\_k $ )</span>" represents their <span class="tex-font-style-underline">series</span> circuit; </li><li> "<span class="tex-font-style-tt">( $ s\_1 $  P  $ s\_2 $  P  $ \\ldots $  P  $ s\_k $ )</span>" represents their <span class="tex-font-style-underline">parallel</span> circuit. </li></ul><p>For example, "<span class="tex-font-style-tt">(* P (* S *) P *)</span>" represents the following circuit:</p><center> <img class="tex-graphics" src="//espresso.codeforces.com/20aa87fefe6adf3989884422c259a4596d9e48d4.png" style="max-width: 100.0%;max-height: 100.0%;" /> </center><p>Given a circuit, your task is to assign the resistances of the individual resistors such that they satisfy the following requirements:</p><ul> <li> Each individual resistor has a <span class="tex-font-style-underline">nonnegative integer</span> resistance value; </li><li> The effective resistance of the whole circuit is  $ r $ ; </li><li> The sum of the resistances of the individual resistors is minimized. </li></ul><p>If there are  $ n $  individual resistors, then you need to output the list  $ r\_1, r\_2, \\ldots, r\_n $  ( $ 0 \\le r\_i $ , and  $ r\_i $  is an integer), where  $ r\_i $  is the resistance assigned to the  $ i $ -th individual resistor that appears in the input (from left to right). If it is impossible to accomplish the task, you must say so as well.</p><p>If it is possible, then it is guaranteed that the minimum sum of resistances is at most  $ 10^{18}$$$.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 32000 $ ), denoting the number of test cases. The next lines contain descriptions of the test cases.

Each test case consists of a single line containing the integer $ r $ ( $ 1 \le r \le 10^6 $ ), space, and then the string representing the circuit. It is guaranteed that the string is valid and follows the description above. The number of individual resistors (symbols "\*") is at least $ 1 $ and at most $ 80000 $ .

It is guaranteed that the total number of individual resistors across all test cases is at most $ 320000 $ .

## 输出格式

For each test case, print a single line:

- If it's possible to achieve an effective resistance of $ r $ , print "REVOLTING" (without quotes) and then $ n $ integers $ r_1, r_2, \ldots, r_n $ — the resistances assigned to the individual resistors. Here, $ n $ denotes the number of the individual resistors in the circuit.  There may be multiple possible such assignments with a minimal sum of resistances of the individual resistors, you can output any of them;
- If it's impossible, print the string: "LOSS" (without quotes).

## 说明/提示

The following illustrates the third sample case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280E/852e127bec4be806dc910057e8c7ff02af314dbc.png)Here, the sum of the resistances of the individual resistors is $ 2 + 1 + 1 = 4 $ , which can be shown to be the minimum. Note that there may be other assignments that achieve this minimum.

## 样例 #1

### 输入

```
3
5 *
1 (* S *)
1 (* P (* S *))

```

### 输出

```
REVOLTING 5
REVOLTING 1 0
REVOLTING 2 1 1

```

