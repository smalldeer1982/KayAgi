---
title: "The hat"
layout: "post"
diff: 普及+/提高
pid: CF1019B
tag: ['交互题']
---

# The hat

## 题目描述

This is an interactive problem.

Imur Ishakov decided to organize a club for people who love to play the famous game «The hat». The club was visited by $ n $ students, where $ n $ is even. Imur arranged them all in a circle and held a draw to break the students in pairs, but something went wrong. The participants are numbered so that participant $ i $ and participant $ i+1 $ ( $ 1<=i<=n-1 $ ) are adjacent, as well as participant $ n $ and participant $ 1 $ . Each student was given a piece of paper with a number in such a way, that for every two adjacent students, these numbers differ exactly by one. The plan was to form students with the same numbers in a pair, but it turned out that not all numbers appeared exactly twice.

As you know, the most convenient is to explain the words to the partner when he is sitting exactly across you. Students with numbers $ i $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1019B/59f224a8151ecadc368b840c31ed2d1a88e25415.png) sit across each other. Imur is wondering if there are two people sitting across each other with the same numbers given. Help him to find such pair of people if it exists.

You can ask questions of form «which number was received by student $ i $ ?», and the goal is to determine whether the desired pair exists in no more than $ 60 $ questions.

## 输入格式

At the beginning the even integer $ n $ ( $ 2<=n<=100000 $ ) is given — the total number of students.

You are allowed to ask no more than $ 60 $ questions.

## 输出格式

To ask the question about the student $ i $ ( $ 1<=i<=n $ ), you should print «? $ i $ ». Then from standard output you can read the number $ a_{i} $ received by student $ i $ ( $ -10^{9}<=a_{i}<=10^{9} $ ).

When you find the desired pair, you should print «! $ i $ », where $ i $ is any student who belongs to the pair ( $ 1<=i<=n $ ). If you determined that such pair doesn't exist, you should output «! -1». In both cases you should immediately terminate the program.

The query that contains your answer is not counted towards the limit of $ 60 $ queries.

Please make sure to flush the standard output after each command. For example, in C++ use function fflush(stdout), in Java call System.out.flush(), in Pascal use flush(output) and stdout.flush() for Python language.

Hacking

Use the following format for hacking:

In the first line, print one even integer $ n $ ( $ 2<=n<=100000 $ ) — the total number of students.

In the second line print $ n $ integers $ a_{i} $ ( $ -10^{9}<=a_{i}<=10^{9} $ ) separated by spaces, where $ a_{i} $ is the number to give to $ i $ -th student. Any two adjacent elements, including $ n $ and $ 1 $ , must differ by $ 1 $ or $ -1 $ .

The hacked solution will not have direct access to the sequence $ a_{i} $ .

## 说明/提示

Input-output in statements illustrates example interaction.

In the first sample the selected sequence is $ 1,2,1,2,3,4,3,2 $

In the second sample the selection sequence is $ 1,2,3,2,1,0 $ .

## 样例 #1

### 输入

```
8

2

2

```

### 输出

```

? 4

? 8

! 4

```

## 样例 #2

### 输入

```
6

1

2

3 

2

1

0
```

### 输出

```

? 1

? 2

? 3

? 4

? 5

? 6

! -1
```

