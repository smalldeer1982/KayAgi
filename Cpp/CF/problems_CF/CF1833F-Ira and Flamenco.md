---
title: "Ira and Flamenco"
layout: "post"
diff: 普及+/提高
pid: CF1833F
tag: []
---

# Ira and Flamenco

## 题目描述

Ira loves Spanish flamenco dance very much. She decided to start her own dance studio and found $ n $ students, $ i $ th of whom has level $ a_i $ .

Ira can choose several of her students and set a dance with them. So she can set a huge number of dances, but she is only interested in magnificent dances. The dance is called magnificent if the following is true:

- exactly $ m $ students participate in the dance;
- levels of all dancers are pairwise distinct;
- levels of every two dancers have an absolute difference strictly less than $ m $ .

For example, if $ m = 3 $ and $ a = [4, 2, 2, 3, 6] $ , the following dances are magnificent (students participating in the dance are highlighted in red): $ [\color{red}{4}\color{black}, 2,\color{red}{2}\color{black},\color{red}{3}\color{black}, 6] $ , $ [\color{red}{4}\color{black}, \color{red}{2}\color{black}, 2, \color{red}{3}\color{black}, 6] $ . At the same time dances $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, 6] $ , $ [4, \color{red}{2}\color{black}, \color{red}{2}\color{black}, \color{red}{3}\color{black}, 6] $ , $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, \color{red}{6}\color{black}] $ are not magnificent.

In the dance $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, 6] $ only $ 2 $ students participate, although $ m = 3 $ .

The dance $ [4, \color{red}{2}\color{black}, \color{red}{2}\color{black}, \color{red}{3}\color{black}, 6] $ involves students with levels $ 2 $ and $ 2 $ , although levels of all dancers must be pairwise distinct.

In the dance $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, \color{red}{6}\color{black}] $ students with levels $ 3 $ and $ 6 $ participate, but $ |3 - 6| = 3 $ , although $ m = 3 $ .

Help Ira count the number of magnificent dances that she can set. Since this number can be very large, count it modulo $ 10^9 + 7 $ . Two dances are considered different if the sets of students participating in them are different.


## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — number of testcases.

The first line of each testcase contains integers $ n $ and $ m $ ( $ 1 \le m \le n \le 2 \cdot 10^5 $ ) — the number of Ira students and the number of dancers in the magnificent dance.

The second line of each testcase contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — levels of students.

It is guaranteed that the sum of $ n $ over all testcases does not exceed $ 2 \cdot 10^5 $ .


## 输出格式

For each testcase, print a single integer — the number of magnificent dances. Since this number can be very large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first testcase, Ira can set such magnificent dances: $ [\color{red}{8}\color{black}, 10, 10, \color{red}{9}\color{black}, \color{red}{6}\color{black}, 11, \color{red}{7}\color{black}] $ , $ [\color{red}{8}\color{black}, \color{red}{10}\color{black}, 10, \color{red}{9}\color{black}, 6, 11, \color{red}{7}\color{black}] $ , $ [\color{red}{8}\color{black}, 10, \color{red}{10}\color{black}, \color{red}{9}\color{black}, 6, 11, \color{red}{7}\color{black}] $ , $ [\color{red}{8}\color{black}, 10, \color{red}{10}\color{black}, \color{red}{9}\color{black}, 6, \color{red}{11}\color{black}, 7] $ , $ [\color{red}{8}\color{black}, \color{red}{10}\color{black}, 10, \color{red}{9}\color{black}, 6, \color{red}{11}\color{black}, 7] $ .

The second testcase is explained in the statements.

## 样例 #1

### 输入

```
9
7 4
8 10 10 9 6 11 7
5 3
4 2 2 3 6
8 2
1 5 2 2 3 1 3 3
3 3
3 3 3
5 1
3 4 3 10 7
12 3
5 2 1 1 4 3 5 5 5 2 7 5
1 1
1
3 2
1 2 3
2 2
1 2
```

### 输出

```
5
2
10
0
5
11
1
2
1
```

