---
title: "Sysadmin Bob"
layout: "post"
diff: 普及/提高-
pid: CF31B
tag: ['模拟', '字符串']
---

# Sysadmin Bob

## 题目描述

Email address in Berland is a string of the form $ A $ @ $ B $ , where $ A $ and $ B $ are arbitrary strings consisting of small Latin letters.

Bob is a system administrator in «Bersoft» company. He keeps a list of email addresses of the company's staff. This list is as a large string, where all addresses are written in arbitrary order, separated by commas. The same address can be written more than once.

Suddenly, because of unknown reasons, all commas in Bob's list disappeared. Now Bob has a string, where all addresses are written one after another without any separators, and there is impossible to determine, where the boundaries between addresses are. Unfortunately, on the same day his chief asked him to bring the initial list of addresses. Now Bob wants to disjoin addresses in some valid way. Help him to do that.

## 输入格式

The first line contains the list of addresses without separators. The length of this string is between $ 1 $ and $ 200 $ , inclusive. The string consists only from small Latin letters and characters «@».

## 输出格式

If there is no list of the valid (according to the Berland rules) email addresses such that after removing all commas it coincides with the given string, output No solution. In the other case, output the list. The same address can be written in this list more than once. If there are several solutions, output any of them.

## 样例 #1

### 输入

```
a@aa@a

```

### 输出

```
a@a,a@a

```

## 样例 #2

### 输入

```
a@a@a

```

### 输出

```
No solution

```

## 样例 #3

### 输入

```
@aa@a

```

### 输出

```
No solution

```

