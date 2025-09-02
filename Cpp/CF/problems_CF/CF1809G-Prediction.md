---
title: "Prediction"
layout: "post"
diff: 省选/NOI-
pid: CF1809G
tag: []
---

# Prediction

## 题目描述

Consider a tournament with $ n $ participants. The rating of the $ i $ -th participant is $ a_i $ .

The tournament will be organized as follows. First of all, organizers will assign each participant an index from $ 1 $ to $ n $ . All indices will be unique. Let $ p_i $ be the participant who gets the index $ i $ .

Then, $ n-1 $ games will be held. In the first game, participants $ p_1 $ and $ p_2 $ will play. In the second game, the winner of the first game will play against $ p_3 $ . In the third game, the winner of the second game will play against $ p_4 $ , and so on — in the last game, the winner of the $ (n-2) $ -th game will play against $ p_n $ .

Monocarp wants to predict the results of all $ n-1 $ games (of course, he will do the prediction only after the indices of the participants are assigned). He knows for sure that, when two participants with ratings $ x $ and $ y $ play, and $ |x - y| > k $ , the participant with the higher rating wins. But if $ |x - y| \le k $ , any of the two participants may win.

Among all $ n! $ ways to assign the indices to participants, calculate the number of ways to do this so that Monocarp can predict the results of all $ n-1 $ games. Since the answer can be large, print it modulo $ 998244353 $ .

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 2 \le n \le 10^6 $ ; $ 0 \le k \le 10^9 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_1 \le a_2 \le \dots \le a_n \le 10^9 $ ).

## 输出格式

Print one integer — the number of ways to assign the indices to the participants so that Monocarp can predict the results of all $ n-1 $ games.

## 说明/提示

In the first example, a match with any pair of players can be predicted by Monocarp, so all $ 24 $ ways to assign indices should be counted.

In the second example, suitable ways are $ [1, 3, 2] $ , $ [2, 3, 1] $ , $ [3, 1, 2 $ \] and $ [3, 2, 1] $ .

## 样例 #1

### 输入

```
4 3
7 12 17 21
```

### 输出

```
24
```

## 样例 #2

### 输入

```
3 7
4 9 28
```

### 输出

```
4
```

## 样例 #3

### 输入

```
4 1
1 2 3 4
```

### 输出

```
0
```

## 样例 #4

### 输入

```
4 1
1 2 2 4
```

### 输出

```
12
```

## 样例 #5

### 输入

```
16 30
8 12 15 27 39 44 49 50 51 53 58 58 59 67 68 100
```

### 输出

```
527461297
```

