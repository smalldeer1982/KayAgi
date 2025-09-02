---
title: "Running Over The Bridges"
layout: "post"
diff: 提高+/省选-
pid: CF730D
tag: []
---

# Running Over The Bridges

## 题目描述

Polycarp is playing a game called "Running Over The Bridges". In this game he has to run over $ n $ bridges from the left to the right. Bridges are arranged one after the other, so the $ i $ -th bridge begins where the $ (i-1) $ -th bridge ends.

You have the following data about bridges: $ l_{i} $ and $ t_{i} $ — the length of the $ i $ -th bridge and the maximum allowed time which Polycarp can spend running over the $ i $ -th bridge. Thus, if Polycarp is in the beginning of the bridge $ i $ at the time $ T $ then he has to leave it at the time $ T+t_{i} $ or earlier. It is allowed to reach the right end of a bridge exactly at the time $ T+t_{i} $ .

Polycarp can run from the left side to the right one with speed $ 0.5 $ , so he will run over a bridge with length $ s $ in time $ 2·s $ . Besides, he has several magical drinks. If he uses one drink, his speed increases twice (i.e. to value 1) for $ r $ seconds. All magical drinks are identical. Please note that Polycarp can use a drink only at integer moments of time, and he drinks it instantly and completely. Additionally, if Polycarp uses a drink at the moment $ T $ he can use the next drink not earlier than at the moment $ T+r $ .

What is the minimal number of drinks Polycarp has to use to run over all $ n $ bridges? If this number is not greater than $ 10^{5} $ , then you have to find out the moments of time when Polycarp has to use each magical drink.

## 输入格式

The first line contains two integers $ n $ and $ r $ ( $ 1<=n<=2·10^{5} $ , $ 1<=r<=10^{12} $ ) — the number of bridges and the duration of the effect of a magical drink.

The second line contains a sequence of integers $ l_{1},l_{2},...,l_{n} $ ( $ 1<=l_{i}<=5·10^{6} $ ), where $ l_{i} $ is equal to the length of the $ i $ -th bridge.

The third line contains a sequence of integers $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{i}<=10^{7} $ ), where $ t_{i} $ is equal to the maximum allowed time which Polycarp can spend running over the $ i $ -th bridge.

## 输出格式

The first line of the output should contain $ k $ — the minimal number of drinks which Polycarp has to use, or -1 if there is no solution.

If the solution exists and the value of $ k $ is not greater than $ 10^{5} $ then output $ k $ integers on the next line — moments of time from beginning of the game when Polycarp has to use drinks. Print the moments of time in chronological order. If there are several solutions, you can output any of them.

## 说明/提示

In the first case, there is only one bridge and it is clear that Polycarp cannot run over it without magical drinks. So, if he will use one magical drink on start (moment of time $ 0 $ ), and the second one — three seconds later (moment of time $ 3 $ ), he will be able to reach the end of the bridge in time. Please note, in this case there are several possible answers to the problem. For example, Polycarp can use the first drink at the moment of time $ 4 $ and the second one — at the moment of time $ 7 $ .

In the second case, Polycarp cannot run over all bridges even if he will use magical drinks. So, answer in this case is -1.

In the fourth case, Polycarp can run over all bridges without magical drinks.

## 样例 #1

### 输入

```
1 3
7
10

```

### 输出

```
2
0 3

```

## 样例 #2

### 输入

```
3 3
3 3 3
3 3 2

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
3 100000
5 5 5
5 7 8

```

### 输出

```
1
0 

```

## 样例 #4

### 输入

```
4 1000
1 2 3 4
10 9 10 9

```

### 输出

```
0


```

