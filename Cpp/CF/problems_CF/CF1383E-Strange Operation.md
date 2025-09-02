---
title: "Strange Operation"
layout: "post"
diff: 省选/NOI-
pid: CF1383E
tag: []
---

# Strange Operation

## 题目描述

Koa the Koala has a binary string $ s $ of length $ n $ . Koa can perform no more than $ n-1 $ (possibly zero) operations of the following form:

In one operation Koa selects positions $ i $ and $ i+1 $ for some $ i $ with $ 1 \le i < |s| $ and sets $ s_i $ to $ max(s_i, s_{i+1}) $ . Then Koa deletes position $ i+1 $ from $ s $ (after the removal, the remaining parts are concatenated).

Note that after every operation the length of $ s $ decreases by $ 1 $ .

How many different binary strings can Koa obtain by doing no more than $ n-1 $ (possibly zero) operations modulo $ 10^9+7 $ ( $ 1000000007 $ )?

## 输入格式

The only line of input contains binary string $ s $ ( $ 1 \le       |s| \le 10^6 $ ). For all $ i $ ( $ 1 \le i \le |s| $ ) $ s_i =       0 $ or $ s_i = 1 $ .

## 输出格式

On a single line print the answer to the problem modulo $ 10^9+7 $ ( $ 1000000007 $ ).

## 说明/提示

In the first sample Koa can obtain binary strings: $ 0 $ , $ 00 $ and $ 000 $ .

In the second sample Koa can obtain binary strings: $ 1 $ , $ 01 $ , $ 11 $ , $ 011 $ , $ 101 $ and $ 0101 $ . For example:

- to obtain $ 01 $ from $ 0101 $ Koa can operate as follows: $ 0101 \rightarrow 0(10)1 \rightarrow 011 \rightarrow         0(11) \rightarrow 01 $ .
- to obtain $ 11 $ from $ 0101 $ Koa can operate as follows: $ 0101 \rightarrow (01)01 \rightarrow 101 \rightarrow         1(01) \rightarrow 11 $ .

Parentheses denote the two positions Koa selected in each operation.

## 样例 #1

### 输入

```
000
```

### 输出

```
3
```

## 样例 #2

### 输入

```
0101
```

### 输出

```
6
```

## 样例 #3

### 输入

```
0001111
```

### 输出

```
16
```

## 样例 #4

### 输入

```
00101100011100
```

### 输出

```
477
```

