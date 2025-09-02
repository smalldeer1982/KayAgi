---
title: "Showmatch"
layout: "post"
diff: 难度0
pid: CF2087B
tag: []
---

# Showmatch

## 题目描述

In a showmatch for a computer game, $ 2n $ esports players are set to participate; the rating of the $ i $ -th player is $ a_i $ . The ratings of all players are distinct.

For each player, the most exciting match will be with the player whose rating is the closest to theirs. Formally, for the $ i $ -th player, the best opponent is another player $ j $ such that the absolute difference in their ratings $ |a_i-a_j| $ is minimized among all ways to choose player $ j $ . Note that some player can have more than one best opponent.

For example, if there are $ 4 $ esports players with ratings $ [3, 7, 5, 12] $ , then:

- for player $ 1 $ , the best opponent is player $ 3 $ ;
- for player $ 2 $ , the best opponent is player $ 3 $ ;
- for player $ 3 $ , the best opponents are players $ 1 $ and $ 2 $ ;
- for player $ 4 $ , the best opponent is player $ 2 $ .

The organizers of the showmatch want to pair the participants so that each player is in exactly one pair, and in each pair, the players are best opponents for each other. Determine whether such a pairing exists.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

Each test case consists of two lines:

- the first line contains a single integer $ n $ ( $ 2 \le n \le 50 $ );
- the second line contains $ 2n $ integers $ a_1, a_2, \dots, a_{2n} $ ( $ 1 \le a_i \le 10^5 $ ; all $ a_i $ are distinct).

## 输出格式

For each test case, if it is possible to pair the participants such that in each pair the participants are best opponents for each other, output YES. Otherwise, output NO.

## 说明/提示

In the first example, pairing is impossible. For instance, if we form pairs $ (1, 3) $ and $ (2, 4) $ , participant $ 4 $ will not be the best opponent for participant $ 2 $ .

In the second example, it is possible to pair the participants as $ (1, 3) $ and $ (2, 4) $ .

## 样例 #1

### 输入

```
3
2
3 7 5 12
2
3 7 5 8
2
3 7 5 9
```

### 输出

```
NO
YES
YES
```

