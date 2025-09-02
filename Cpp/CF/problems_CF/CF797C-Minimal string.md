---
title: "Minimal string"
layout: "post"
diff: 普及/提高-
pid: CF797C
tag: []
---

# Minimal string

## 题目描述

Petya recieved a gift of a string $ s $ with length up to $ 10^{5} $ characters for his birthday. He took two more empty strings $ t $ and $ u $ and decided to play a game. This game has two possible moves:

- Extract the first character of $ s $ and append $ t $ with this character.
- Extract the last character of $ t $ and append $ u $ with this character.

Petya wants to get strings $ s $ and $ t $ empty and string $ u $ lexicographically minimal.

You should write a program that will help Petya win the game.

## 输入格式

First line contains non-empty string $ s $ ( $ 1<=|s|<=10^{5} $ ), consisting of lowercase English letters.

## 输出格式

Print resulting string $ u $ .

## 样例 #1

### 输入

```
cab

```

### 输出

```
abc

```

## 样例 #2

### 输入

```
acdb

```

### 输出

```
abdc

```

