---
title: "Number of Subsequences"
layout: "post"
diff: 普及+/提高
pid: CF1426F
tag: []
---

# Number of Subsequences

## 题目描述

You are given a string $ s $ consisting of lowercase Latin letters "a", "b" and "c" and question marks "?".

Let the number of question marks in the string $ s $ be $ k $ . Let's replace each question mark with one of the letters "a", "b" and "c". Here we can obtain all $ 3^{k} $ possible strings consisting only of letters "a", "b" and "c". For example, if $ s =  $ "ac?b?c" then we can obtain the following strings: $ [ $ "acabac", "acabbc", "acabcc", "acbbac", "acbbbc", "acbbcc", "accbac", "accbbc", "accbcc" $ ] $ .

Your task is to count the total number of subsequences "abc" in all resulting strings. Since the answer can be very large, print it modulo $ 10^{9} + 7 $ .

A subsequence of the string $ t $ is such a sequence that can be derived from the string $ t $ after removing some (possibly, zero) number of letters without changing the order of remaining letters. For example, the string "baacbc" contains two subsequences "abc" — a subsequence consisting of letters at positions $ (2, 5, 6) $ and a subsequence consisting of letters at positions $ (3, 5, 6) $ .

## 输入格式

The first line of the input contains one integer $ n $ $ (3 \le n \le 200\,000) $ — the length of $ s $ .

The second line of the input contains the string $ s $ of length $ n $ consisting of lowercase Latin letters "a", "b" and "c" and question marks"?".

## 输出格式

Print the total number of subsequences "abc" in all strings you can obtain if you replace all question marks with letters "a", "b" and "c", modulo $ 10^{9} + 7 $ .

## 说明/提示

In the first example, we can obtain $ 9 $ strings:

- "acabac" — there are $ 2 $ subsequences "abc",
- "acabbc" — there are $ 4 $ subsequences "abc",
- "acabcc" — there are $ 4 $ subsequences "abc",
- "acbbac" — there are $ 2 $ subsequences "abc",
- "acbbbc" — there are $ 3 $ subsequences "abc",
- "acbbcc" — there are $ 4 $ subsequences "abc",
- "accbac" — there is $ 1 $ subsequence "abc",
- "accbbc" — there are $ 2 $ subsequences "abc",
- "accbcc" — there are $ 2 $ subsequences "abc".

So, there are $ 2 + 4 + 4 + 2 + 3 + 4 + 1 + 2 + 2 = 24 $ subsequences "abc" in total.

## 样例 #1

### 输入

```
6
ac?b?c
```

### 输出

```
24
```

## 样例 #2

### 输入

```
7
???????
```

### 输出

```
2835
```

## 样例 #3

### 输入

```
9
cccbbbaaa
```

### 输出

```
0
```

## 样例 #4

### 输入

```
5
a???c
```

### 输出

```
46
```

