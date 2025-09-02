---
title: "Infinite Game"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1784E
tag: ['动态规划 DP', 'DP 套 DP']
---

# Infinite Game

## 题目描述

Alice and Bob are playing an infinite game consisting of sets. Each set consists of rounds. In each round, one of the players wins. The first player to win two rounds in a set wins this set. Thus, a set always ends with the score of $ 2:0 $ or $ 2:1 $ in favor of one of the players.

Let's call a game scenario a finite string $ s $ consisting of characters 'a' and 'b'. Consider an infinite string formed with repetitions of string $ s $ : $ sss \ldots $ Suppose that Alice and Bob play rounds according to this infinite string, left to right. If a character of the string $ sss \ldots $ is 'a', then Alice wins the round; if it's 'b', Bob wins the round. As soon as one of the players wins two rounds, the set ends in their favor, and a new set starts from the next round.

Let's define $ a_i $ as the number of sets won by Alice among the first $ i $ sets while playing according to the given scenario. Let's also define $ r $ as the limit of ratio $ \frac{a_i}{i} $ as $ i \rightarrow \infty $ . If $ r > \frac{1}{2} $ , we'll say that scenario $ s $ is winning for Alice. If $ r = \frac{1}{2} $ , we'll say that scenario $ s $ is tied. If $ r < \frac{1}{2} $ , we'll say that scenario $ s $ is winning for Bob.

You are given a string $ s $ consisting of characters 'a', 'b', and '?'. Consider all possible ways of replacing every '?' with 'a' or 'b' to obtain a string consisting only of characters 'a' and 'b'. Count how many of them result in a scenario winning for Alice, how many result in a tied scenario, and how many result in a scenario winning for Bob. Print these three numbers modulo $ 998\,244\,353 $ .

## 输入格式

The only line contains a single string $ s $ ( $ 1 \le |s| \le 200 $ ), consisting of characters 'a', 'b', and '?'.

## 输出格式

Print three integers: how many ways result in a scenario winning for Alice, how many result in a tied scenario, and how many result in a scenario winning for Bob, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, there are four ways to replace the question marks:

- $ s = \mathtt{aa} $ : Alice wins every set $ 2:0 $ — the scenario is winning for Alice;
- $ s = \mathtt{ab} $ : Alice and Bob win sets in turns, with the score of $ 2:1 $ each — the scenario is tied;
- $ s = \mathtt{ba} $ : Bob and Alice win sets in turns, with the score of $ 2:1 $ each — the scenario is tied;
- $ s = \mathtt{bb} $ : Bob wins every set $ 2:0 $ — the scenario is winning for Bob.

## 样例 #1

### 输入

```
??
```

### 输出

```
1
2
1
```

## 样例 #2

### 输入

```
?aa?b
```

### 输出

```
1
3
0
```

## 样例 #3

### 输入

```
a???ba
```

### 输出

```
4
3
1
```

## 样例 #4

### 输入

```
????????
```

### 输出

```
121
14
121
```

## 样例 #5

### 输入

```
ba????a?a???abbb?
```

### 输出

```
216
57
239
```

## 样例 #6

### 输入

```
a????a??????b??abbababbbb?a?aaa????bb
```

### 输出

```
97833
28387
135924
```

## 样例 #7

### 输入

```
??????????????a????????????????b?????
```

### 输出

```
484121060
448940322
484613337
```

