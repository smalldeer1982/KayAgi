---
title: "Regular Bracket Sequence"
layout: "post"
diff: 普及-
pid: CF1132A
tag: []
---

# Regular Bracket Sequence

## 题目描述

A string is called bracket sequence if it does not contain any characters other than "(" and ")". A bracket sequence is called regular if it it is possible to obtain correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, "", "(())" and "()()" are regular bracket sequences; "))" and ")((" are bracket sequences (but not regular ones), and "(a)" and "(1)+(1)" are not bracket sequences at all.

You have a number of strings; each string is a bracket sequence of length $ 2 $ . So, overall you have $ cnt_1 $ strings "((", $ cnt_2 $ strings "()", $ cnt_3 $ strings ")(" and $ cnt_4 $ strings "))". You want to write all these strings in some order, one after another; after that, you will get a long bracket sequence of length $ 2(cnt_1 + cnt_2 + cnt_3 + cnt_4) $ . You wonder: is it possible to choose some order of the strings you have such that you will get a regular bracket sequence? Note that you may not remove any characters or strings, and you may not add anything either.

## 输入格式

The input consists of four lines, $ i $ -th of them contains one integer $ cnt_i $ ( $ 0 \le cnt_i \le 10^9 $ ).

## 输出格式

Print one integer: $ 1 $ if it is possible to form a regular bracket sequence by choosing the correct order of the given strings, $ 0 $ otherwise.

## 说明/提示

In the first example it is possible to construct a string "(())()(()((()()()())))", which is a regular bracket sequence.

In the second example it is possible to construct a string "", which is a regular bracket sequence.

## 样例 #1

### 输入

```
3
1
4
3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
0
0
0
0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
1
2
3
4

```

### 输出

```
0

```

