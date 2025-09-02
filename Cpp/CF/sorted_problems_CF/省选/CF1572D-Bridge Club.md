---
title: "Bridge Club"
layout: "post"
diff: 省选/NOI-
pid: CF1572D
tag: []
---

# Bridge Club

## 题目描述

There are currently $ n $ hot topics numbered from $ 0 $ to $ n-1 $ at your local bridge club and $ 2^n $ players numbered from $ 0 $ to $ 2^n-1 $ . Each player holds a different set of views on those $ n $ topics, more specifically, the $ i $ -th player holds a positive view on the $ j $ -th topic if $ i\ \&\ 2^j > 0 $ , and a negative view otherwise. Here $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

You are going to organize a bridge tournament capable of accommodating at most $ k $ pairs of players (bridge is played in teams of two people). You can select teams arbitrarily while each player is in at most one team, but there is one catch: two players cannot be in the same pair if they disagree on $ 2 $ or more of those $ n $ topics, as they would argue too much during the play.

You know that the $ i $ -th player will pay you $ a_i $ dollars if they play in this tournament. Compute the maximum amount of money that you can earn if you pair the players in your club optimally.

## 输入格式

The first line contains two integers $ n $ , $ k $ ( $ 1 \le n \le 20 $ , $ 1 \le k \le 200 $ ) — the number of hot topics and the number of pairs of players that your tournament can accommodate.

The second line contains $ 2^n $ integers $ a_0, a_1, \dots, a_{2^n-1} $ ( $ 0 \le a_i \le 10^6 $ ) — the amounts of money that the players will pay to play in the tournament.

## 输出格式

Print one integer: the maximum amount of money that you can earn if you pair the players in your club optimally under the above conditions.

## 说明/提示

In the first example, the best we can do is to pair together the $ 0 $ -th player and the $ 2 $ -nd player resulting in earnings of $ 8 + 5 = 13 $ dollars. Although pairing the $ 0 $ -th player with the $ 5 $ -th player would give us $ 8 + 10 = 18 $ dollars, we cannot do this because those two players disagree on $ 2 $ of the $ 3 $ hot topics.

In the second example, we can pair the $ 0 $ -th player with the $ 1 $ -st player and pair the $ 2 $ -nd player with the $ 3 $ -rd player resulting in earnings of $ 7 + 4 + 5 + 7 = 23 $ dollars.

## 样例 #1

### 输入

```
3 1
8 3 5 7 1 10 3 2
```

### 输出

```
13
```

## 样例 #2

### 输入

```
2 3
7 4 5 7
```

### 输出

```
23
```

## 样例 #3

### 输入

```
3 2
1 9 1 5 7 8 1 1
```

### 输出

```
29
```

