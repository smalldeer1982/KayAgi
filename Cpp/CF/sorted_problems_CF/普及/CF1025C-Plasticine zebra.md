---
title: "Plasticine zebra"
layout: "post"
diff: 普及/提高-
pid: CF1025C
tag: ['字符串']
---

# Plasticine zebra

## 题目描述

Is there anything better than going to the zoo after a tiresome week at work? No wonder Grisha feels the same while spending the entire weekend accompanied by pretty striped zebras.

Inspired by this adventure and an accidentally found plasticine pack (represented as a sequence of black and white stripes), Grisha now wants to select several consequent (contiguous) pieces of alternating colors to create a zebra. Let's call the number of selected pieces the length of the zebra.

Before assembling the zebra Grisha can make the following operation $ 0 $ or more times. He splits the sequence in some place into two parts, then reverses each of them and sticks them together again. For example, if Grisha has pieces in the order "bwbbw" (here 'b' denotes a black strip, and 'w' denotes a white strip), then he can split the sequence as bw|bbw (here the vertical bar represents the cut), reverse both parts and obtain "wbwbb".

Determine the maximum possible length of the zebra that Grisha can produce.

## 输入格式

The only line contains a string $ s $ ( $ 1 \le |s| \le 10^5 $ , where $ |s| $ denotes the length of the string $ s $ ) comprised of lowercase English letters 'b' and 'w' only, where 'w' denotes a white piece and 'b' denotes a black piece.

## 输出格式

Print a single integer — the maximum possible zebra length.

## 说明/提示

In the first example one of the possible sequence of operations is bwwwbww|bw $ \to $ w|wbwwwbwb $ \to $ wbwbwwwbw, that gives the answer equal to $ 5 $ .

In the second example no operation can increase the answer.

## 样例 #1

### 输入

```
bwwwbwwbw

```

### 输出

```
5

```

## 样例 #2

### 输入

```
bwwbwwb

```

### 输出

```
3

```

