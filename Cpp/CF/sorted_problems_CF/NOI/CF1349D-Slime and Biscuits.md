---
title: "Slime and Biscuits"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1349D
tag: []
---

# Slime and Biscuits

## 题目描述

Slime and his $ n $ friends are at a party. Slime has designed a game for his friends to play.

At the beginning of the game, the $ i $ -th player has $ a_i $ biscuits. At each second, Slime will choose a biscuit randomly uniformly among all $ a_1 + a_2 + \ldots + a_n $ biscuits, and the owner of this biscuit will give it to a random uniform player among $ n-1 $ players except himself. The game stops when one person will have all the biscuits.

As the host of the party, Slime wants to know the expected value of the time that the game will last, to hold the next activity on time.

For convenience, as the answer can be represented as a rational number $ \frac{p}{q} $ for coprime $ p $ and $ q $ , you need to find the value of $ (p \cdot q^{-1})\mod 998\,244\,353 $ . You can prove that $ q\mod 998\,244\,353 \neq 0 $ .

## 输入格式

The first line contains one integer $ n\ (2\le n\le       100\,000) $ : the number of people playing the game.

The second line contains $ n $ non-negative integers $ a_1,a_2,\dots,a_n\ (1\le a_1+a_2+\dots+a_n\le 300\,000) $ , where $ a_i $ represents the number of biscuits the $ i $ -th person own at the beginning.

## 输出格式

Print one integer: the expected value of the time that the game will last, modulo $ 998\,244\,353 $ .

## 说明/提示

For the first example, in the first second, the probability that player $ 1 $ will give the player $ 2 $ a biscuit is $ \frac{1}{2} $ , and the probability that player $ 2 $ will give the player $ 1 $ a biscuit is $ \frac{1}{2} $ . But anyway, the game will stop after exactly $ 1 $ second because only one player will occupy all biscuits after $ 1 $ second, so the answer is $ 1 $ .

## 样例 #1

### 输入

```
2
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
5
0 0 0 0 35
```

### 输出

```
0
```

## 样例 #4

### 输入

```
5
8 4 2 0 1
```

### 输出

```
801604029
```

