---
title: "Cursor Distance"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1246F
tag: []
---

# Cursor Distance

## 题目描述

There is a string $ s $ of lowercase English letters. A cursor is positioned on one of the characters. The cursor can be moved with the following operation: choose a letter $ c $ and a direction (left or right). The cursor is then moved to the closest occurence of $ c $ in the chosen direction. If there is no letter $ c $ in that direction, the cursor stays in place. For example, if $ s = \mathtt{abaab} $ with the cursor on the second character ( $ \mathtt{a[b]aab} $ ), then:

- moving to the closest letter $ \mathtt{a} $ to the left places the cursor on the first character ( $ \mathtt{[a]baab} $ );
- moving to the closest letter $ \mathtt{a} $ to the right places the cursor the third character ( $ \mathtt{ab[a]ab} $ );
- moving to the closest letter $ \mathtt{b} $ to the right places the cursor on the fifth character ( $ \mathtt{abaa[b]} $ );
- any other operation leaves the cursor in place.

Let $ \mathrm{dist}(i, j) $ be the smallest number of operations needed to move the cursor from the $ i $ -th character to the $ j $ -th character. Compute $ \displaystyle \sum_{i = 1}^n \sum_{j = 1}^n \mathrm{dist}(i, j) $ .

## 输入格式

The only line contains a non-empty string $ s $ of at most $ 10^5 $ lowercase English letters.

## 输出格式

Print a single integer $ \displaystyle \sum_{i = 1}^n \sum_{j = 1}^n \mathrm{dist}(i, j) $ .

## 说明/提示

In the first sample case, $ \mathrm{dist}(i, j) = 0 $ for any pair $ i = j $ , and $ 1 $ for all other pairs.

## 样例 #1

### 输入

```
abcde

```

### 输出

```
20

```

## 样例 #2

### 输入

```
abacaba

```

### 输出

```
58

```

