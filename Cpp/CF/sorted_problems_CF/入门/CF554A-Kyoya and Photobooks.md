---
title: "Kyoya and Photobooks"
layout: "post"
diff: 入门
pid: CF554A
tag: []
---

# Kyoya and Photobooks

## 题目描述

Kyoya Ootori is selling photobooks of the Ouran High School Host Club. He has 26 photos, labeled "a" to "z", and he has compiled them into a photo booklet with some photos in some order (possibly with some photos being duplicated). A photo booklet can be described as a string of lowercase letters, consisting of the photos in the booklet in order. He now wants to sell some "special edition" photobooks, each with one extra photo inserted anywhere in the book. He wants to make as many distinct photobooks as possible, so he can make more money. He asks Haruhi, how many distinct photobooks can he make by inserting one extra photo into the photobook he already has?

Please help Haruhi solve this problem.

## 输入格式

The first line of input will be a single string $ s $ ( $ 1<=|s|<=20 $ ). String $ s $ consists only of lowercase English letters.

## 输出格式

Output a single integer equal to the number of distinct photobooks Kyoya Ootori can make.

## 说明/提示

In the first case, we can make 'ab','ac', $ ... $ ,'az','ba','ca', $ ... $ ,'za', and 'aa', producing a total of 51 distinct photo booklets.

## 样例 #1

### 输入

```
a

```

### 输出

```
51

```

## 样例 #2

### 输入

```
hi

```

### 输出

```
76

```

