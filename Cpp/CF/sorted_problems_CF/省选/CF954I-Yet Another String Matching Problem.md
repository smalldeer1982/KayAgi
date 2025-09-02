---
title: "Yet Another String Matching Problem"
layout: "post"
diff: 省选/NOI-
pid: CF954I
tag: []
---

# Yet Another String Matching Problem

## 题目描述

Suppose you have two strings $ s $ and $ t $ , and their length is equal. You may perform the following operation any number of times: choose two different characters $ c_{1} $ and $ c_{2} $ , and replace every occurence of $ c_{1} $ in both strings with $ c_{2} $ . Let's denote the distance between strings $ s $ and $ t $ as the minimum number of operations required to make these strings equal. For example, if $ s $ is abcd and $ t $ is ddcb, the distance between them is $ 2 $ — we may replace every occurence of a with b, so $ s $ becomes bbcd, and then we may replace every occurence of b with d, so both strings become ddcd.

You are given two strings $ S $ and $ T $ . For every substring of $ S $ consisting of $ |T| $ characters you have to determine the distance between this substring and $ T $ .

## 输入格式

The first line contains the string $ S $ , and the second — the string $ T $ ( $ 1<=|T|<=|S|<=125000 $ ). Both strings consist of lowercase Latin letters from a to f.

## 输出格式

Print $ |S|-|T|+1 $ integers. The $ i $ -th of these integers must be equal to the distance between the substring of $ S $ beginning at $ i $ -th index with length $ |T| $ and the string $ T $ .

## 样例 #1

### 输入

```
abcdefa
ddcb

```

### 输出

```
2 3 3 3 

```

