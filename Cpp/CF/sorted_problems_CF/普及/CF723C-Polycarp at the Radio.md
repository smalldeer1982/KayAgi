---
title: "Polycarp at the Radio"
layout: "post"
diff: 普及/提高-
pid: CF723C
tag: []
---

# Polycarp at the Radio

## 题目描述

Polycarp is a music editor at the radio station. He received a playlist for tomorrow, that can be represented as a sequence $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is a band, which performs the $ i $ -th song. Polycarp likes bands with the numbers from $ 1 $ to $ m $ , but he doesn't really like others.

We define as $ b_{j} $ the number of songs the group $ j $ is going to perform tomorrow. Polycarp wants to change the playlist in such a way that the minimum among the numbers $ b_{1},b_{2},...,b_{m} $ will be as large as possible.

Find this maximum possible value of the minimum among the $ b_{j} $ ( $ 1<=j<=m $ ), and the minimum number of changes in the playlist Polycarp needs to make to achieve it. One change in the playlist is a replacement of the performer of the $ i $ -th song with any other group.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=m<=n<=2000 $ ).

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ), where $ a_{i} $ is the performer of the $ i $ -th song.

## 输出格式

In the first line print two integers: the maximum possible value of the minimum among the $ b_{j} $ ( $ 1<=j<=m $ ), where $ b_{j} $ is the number of songs in the changed playlist performed by the $ j $ -th band, and the minimum number of changes in the playlist Polycarp needs to make.

In the second line print the changed playlist.

If there are multiple answers, print any of them.

## 说明/提示

In the first sample, after Polycarp's changes the first band performs two songs ( $ b_{1}=2 $ ), and the second band also performs two songs ( $ b_{2}=2 $ ). Thus, the minimum of these values equals to $ 2 $ . It is impossible to achieve a higher minimum value by any changes in the playlist.

In the second sample, after Polycarp's changes the first band performs two songs ( $ b_{1}=2 $ ), the second band performs three songs ( $ b_{2}=3 $ ), and the third band also performs two songs ( $ b_{3}=2 $ ). Thus, the best minimum value is $ 2 $ .

## 样例 #1

### 输入

```
4 2
1 2 3 2

```

### 输出

```
2 1
1 2 1 2 

```

## 样例 #2

### 输入

```
7 3
1 3 2 2 2 2 1

```

### 输出

```
2 1
1 3 3 2 2 2 1 

```

## 样例 #3

### 输入

```
4 4
1000000000 100 7 1000000000

```

### 输出

```
1 4
1 2 3 4 

```

