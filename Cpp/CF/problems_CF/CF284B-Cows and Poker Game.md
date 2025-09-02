---
title: "Cows and Poker Game"
layout: "post"
diff: 普及-
pid: CF284B
tag: []
---

# Cows and Poker Game

## 题目描述

There are $ n $ cows playing poker at a table. For the current betting phase, each player's status is either "ALLIN", "IN", or "FOLDED", and does not change throughout the phase. To increase the suspense, a player whose current status is not "FOLDED" may show his/her hand to the table. However, so as not to affect any betting decisions, he/she may only do so if all other players have a status of either "ALLIN" or "FOLDED". The player's own status may be either "ALLIN" or "IN".

Find the number of cows that can currently show their hands without affecting any betting decisions.

## 输入格式

The first line contains a single integer, $ n $ ( $ 2<=n<=2·10^{5} $ ). The second line contains $ n $ characters, each either "A", "I", or "F". The $ i $ -th character is "A" if the $ i $ -th player's status is "ALLIN", "I" if the $ i $ -th player's status is "IN", or "F" if the $ i $ -th player's status is "FOLDED".

## 输出格式

The first line should contain a single integer denoting the number of players that can currently show their hands.

## 说明/提示

In the first sample, cows 1, 4, 5, and 6 can show their hands. In the second sample, only cow 3 can show her hand.

## 样例 #1

### 输入

```
6
AFFAAA

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3
AFI

```

### 输出

```
1

```

