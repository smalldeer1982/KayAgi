---
title: "New Rating"
layout: "post"
diff: 普及/提高-
pid: CF2029C
tag: ['动态规划 DP', '动态规划 DP']
---

# New Rating

## 题目描述

Hello, Codeforces Forcescode!





Kevin used to be a participant of Codeforces. Recently, the KDOI Team has developed a new Online Judge called Forcescode.

Kevin has participated in $ n $ contests on Forcescode. In the $ i $ -th contest, his performance rating is $ a_i $ .

Now he has hacked into the backend of Forcescode and will select an interval $ [l,r] $ ( $ 1\le l\le r\le n $ ), then skip all of the contests in this interval. After that, his rating will be recalculated in the following way:

- Initially, his rating is $ x=0 $ ;
- For each $ 1\le i\le n $ , after the $ i $ -th contest, 
  - If $ l\le i\le r $ , this contest will be skipped, and the rating will remain unchanged;
  - Otherwise, his rating will be updated according to the following rules: 
      - If $ a_i>x $ , his rating $ x $ will increase by $ 1 $ ;
      - If $ a_i=x $ , his rating $ x $ will remain unchanged;
      - If $ a_i<x $ , his rating $ x $ will decrease by $ 1 $ .

You have to help Kevin to find his maximum possible rating after the recalculation if he chooses the interval $ [l,r] $ optimally. Note that Kevin has to skip at least one contest.

## 输入格式

Each test contains multiple test cases. The first line of the input contains a single integer $ t $ ( $ 1\le t\le 5\cdot 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 3\cdot 10^5 $ ) — the number of contests.

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1\le a_i\le n $ ) — the performance ratings in the contests.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible rating after the recalculation if Kevin chooses the interval optimally.

## 说明/提示

In the first test case, Kevin must skip at least one contest. If he chooses any interval of length $ 1 $ , his rating after the recalculation will be equal to $ 5 $ .

In the second test case, Kevin's optimal choice is to select the interval $ [3,5] $ . During the recalculation, his rating changes as follows:

 $ $$$ 0 \xrightarrow{a_1=1} 1 \xrightarrow{a_2=2} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{a_6=3} 3 \xrightarrow{a_7=4} 4  $ $ </p><p>In the third test case, Kevin must skip the only contest, so his rating will remain at the initial value of  $ 0 $ .</p><p>In the fourth test case, Kevin's optimal choice is to select the interval  $ \[7,9\] $ . During the recalculation, his rating changes as follows:</p><p> $ $  0 \xrightarrow{a_1=9} 1 \xrightarrow{a_2=9} 2 \xrightarrow{a_3=8} 3 \xrightarrow{a_4=2} 2 \xrightarrow{a_5=4} 3 \xrightarrow{a_6=4} 4 \xrightarrow{\mathtt{skip}} 4 \xrightarrow{\mathtt{skip}} 4 \xrightarrow{\mathtt{skip}} 4  $ $ </p><p>In the fifth test case, Kevin's optimal choice is to select the interval  $ \[5,9\]$$$.

## 样例 #1

### 输入

```
5
6
1 2 3 4 5 6
7
1 2 1 1 1 3 4
1
1
9
9 9 8 2 4 4 3 5 3
10
1 2 3 4 1 3 2 1 1 10
```

### 输出

```
5
4
0
4
5
```

