---
title: "DZY Loves Strings"
layout: "post"
diff: 普及/提高-
pid: CF447B
tag: []
---

# DZY Loves Strings

## 题目描述

DZY loves collecting special strings which only contain lowercase letters. For each lowercase letter $ c $ DZY knows its value $ w_{c} $ . For each special string $ s=s_{1}s_{2}...\ s_{|s|} $ ( $ |s| $ is the length of the string) he represents its value with a function $ f(s) $ , where

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF447B/47a1fab5618b8aab7370048ef8382ed56e397765.png)Now DZY has a string $ s $ . He wants to insert $ k $ lowercase letters into this string in order to get the largest possible value of the resulting string. Can you help him calculate the largest possible value he could get?

## 输入格式

The first line contains a single string $ s (1<=|s|<=10^{3}) $ .

The second line contains a single integer $ k (0<=k<=10^{3}) $ .

The third line contains twenty-six integers from $ w_{a} $ to $ w_{z} $ . Each such number is non-negative and doesn't exceed $ 1000 $ .

## 输出格式

Print a single integer — the largest possible value of the resulting string DZY could get.

## 说明/提示

In the test sample DZY can obtain "abcbbc", $ value=1·1+2·2+3·2+4·2+5·2+6·2=41 $ .

## 样例 #1

### 输入

```
abc
3
1 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

```

### 输出

```
41

```

