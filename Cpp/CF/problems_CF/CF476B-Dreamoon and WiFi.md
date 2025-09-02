---
title: "Dreamoon and WiFi"
layout: "post"
diff: 普及-
pid: CF476B
tag: []
---

# Dreamoon and WiFi

## 题目描述

Dreamoon is standing at the position $ 0 $ on a number line. Drazil is sending a list of commands through Wi-Fi to Dreamoon's smartphone and Dreamoon follows them.

Each command is one of the following two types:

1. Go 1 unit towards the positive direction, denoted as '+'
2. Go 1 unit towards the negative direction, denoted as '-'

But the Wi-Fi condition is so poor that Dreamoon's smartphone reports some of the commands can't be recognized and Dreamoon knows that some of them might even be wrong though successfully recognized. Dreamoon decides to follow every recognized command and toss a fair coin to decide those unrecognized ones (that means, he moves to the $ 1 $ unit to the negative or positive direction with the same probability $ 0.5 $ ).

You are given an original list of commands sent by Drazil and list received by Dreamoon. What is the probability that Dreamoon ends in the position originally supposed to be final by Drazil's commands?

## 输入格式

Dreamoon is standing at the position $ 0 $ on a number line. Drazil is sending a list of commands through Wi-Fi to Dreamoon's smartphone and Dreamoon follows them.

Each command is one of the following two types:

1. Go 1 unit towards the positive direction, denoted as '+'
2. Go 1 unit towards the negative direction, denoted as '-'

But the Wi-Fi condition is so poor that Dreamoon's smartphone reports some of the commands can't be recognized and Dreamoon knows that some of them might even be wrong though successfully recognized. Dreamoon decides to follow every recognized command and toss a fair coin to decide those unrecognized ones (that means, he moves to the $ 1 $ unit to the negative or positive direction with the same probability $ 0.5 $ ).

You are given an original list of commands sent by Drazil and list received by Dreamoon. What is the probability that Dreamoon ends in the position originally supposed to be final by Drazil's commands?

## 输出格式

Output a single real number corresponding to the probability. The answer will be considered correct if its relative or absolute error doesn't exceed $ 10^{-9} $ .

## 说明/提示

Dreamoon is standing at the position $ 0 $ on a number line. Drazil is sending a list of commands through Wi-Fi to Dreamoon's smartphone and Dreamoon follows them.

Each command is one of the following two types:

1. Go 1 unit towards the positive direction, denoted as '+'
2. Go 1 unit towards the negative direction, denoted as '-'

But the Wi-Fi condition is so poor that Dreamoon's smartphone reports some of the commands can't be recognized and Dreamoon knows that some of them might even be wrong though successfully recognized. Dreamoon decides to follow every recognized command and toss a fair coin to decide those unrecognized ones (that means, he moves to the $ 1 $ unit to the negative or positive direction with the same probability $ 0.5 $ ).

You are given an original list of commands sent by Drazil and list received by Dreamoon. What is the probability that Dreamoon ends in the position originally supposed to be final by Drazil's commands?

## 样例 #1

### 输入

```
++-+-
+-+-+

```

### 输出

```
1.000000000000

```

## 样例 #2

### 输入

```
+-+-
+-??

```

### 输出

```
0.500000000000

```

## 样例 #3

### 输入

```
+++
??-

```

### 输出

```
0.000000000000

```

