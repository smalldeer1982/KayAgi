---
title: "ZgukistringZ"
layout: "post"
diff: 普及+/提高
pid: CF551B
tag: []
---

# ZgukistringZ

## 题目描述

Professor GukiZ doesn't accept string as they are. He likes to swap some letters in string to obtain a new one.

GukiZ has strings $ a $ , $ b $ , and $ c $ . He wants to obtain string $ k $ by swapping some letters in $ a $ , so that $ k $ should contain as many non-overlapping substrings equal either to $ b $ or $ c $ as possible. Substring of string $ x $ is a string formed by consecutive segment of characters from $ x $ . Two substrings of string $ x $ overlap if there is position $ i $ in string $ x $ occupied by both of them.

GukiZ was disappointed because none of his students managed to solve the problem. Can you help them and find one of possible strings $ k $ ?

## 输入格式

The first line contains string $ a $ , the second line contains string $ b $ , and the third line contains string $ c $ ( $ 1<=|a|,|b|,|c|<=10^{5} $ , where $ |s| $ denotes the length of string $ s $ ).

All three strings consist only of lowercase English letters.

It is possible that $ b $ and $ c $ coincide.

## 输出格式

Find one of possible strings $ k $ , as described in the problem statement. If there are multiple possible answers, print any of them.

## 说明/提示

In the third sample, this optimal solutions has three non-overlaping substrings equal to either $ b $ or $ c $ on positions $ 1–2 $ ( $ ab $ ), $ 3–4 $ ( $ ab $ ), $ 5–7 $ ( $ aca $ ). In this sample, there exist many other optimal solutions, one of them would be $ acaababbcc $ .

## 样例 #1

### 输入

```
aaa
a
b

```

### 输出

```
aaa
```

## 样例 #2

### 输入

```
pozdravstaklenidodiri
niste
dobri

```

### 输出

```
nisteaadddiiklooprrvz
```

## 样例 #3

### 输入

```
abbbaaccca
ab
aca

```

### 输出

```
ababacabcc
```

