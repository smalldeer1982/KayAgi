---
title: "War of the Corporations"
layout: "post"
diff: 普及-
pid: CF625B
tag: []
---

# War of the Corporations

## 题目描述

A long time ago, in a galaxy far far away two giant IT-corporations Pineapple and Gogol continue their fierce competition. Crucial moment is just around the corner: Gogol is ready to release it's new tablet Lastus 3000.

This new device is equipped with specially designed artificial intelligence (AI). Employees of Pineapple did their best to postpone the release of Lastus 3000 as long as possible. Finally, they found out, that the name of the new artificial intelligence is similar to the name of the phone, that Pineapple released 200 years ago. As all rights on its name belong to Pineapple, they stand on changing the name of Gogol's artificial intelligence.

Pineapple insists, that the name of their phone occurs in the name of AI as a substring. Because the name of technology was already printed on all devices, the Gogol's director decided to replace some characters in AI name with "\#". As this operation is pretty expensive, you should find the minimum number of characters to replace with "\#", such that the name of AI doesn't contain the name of the phone as a substring.

Substring is a continuous subsequence of a string.

## 输入格式

The first line of the input contains the name of AI designed by Gogol, its length doesn't exceed $ 100000 $ characters. Second line contains the name of the phone released by Pineapple 200 years ago, its length doesn't exceed $ 30 $ . Both string are non-empty and consist of only small English letters.

## 输出格式

Print the minimum number of characters that must be replaced with "\#" in order to obtain that the name of the phone doesn't occur in the name of AI as a substring.

## 说明/提示

In the first sample AI's name may be replaced with "int#llect".

In the second sample Gogol can just keep things as they are.

In the third sample one of the new possible names of AI may be "s#ris#ri".

## 样例 #1

### 输入

```
intellect
tell

```

### 输出

```
1
```

## 样例 #2

### 输入

```
google
apple

```

### 输出

```
0
```

## 样例 #3

### 输入

```
sirisiri
sir

```

### 输出

```
2
```

