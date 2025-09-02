---
title: "Corporation Mail"
layout: "post"
diff: 普及-
pid: CF56C
tag: []
---

# Corporation Mail

## 题目描述

The Beroil corporation structure is hierarchical, that is it can be represented as a tree. Let's examine the presentation of this structure as follows:

- $ employee $ ::= $ name $ . | $ name $ : $ employee_{1} $ , $ employee_{2} $ , ... , $ employee_{k} $ .
- $ name $ ::= name of an employee

That is, the description of each employee consists of his name, a colon (:), the descriptions of all his subordinates separated by commas, and, finally, a dot. If an employee has no subordinates, then the colon is not present in his description.

For example, line MIKE:MAX.,ARTEM:MIKE..,DMITRY:DMITRY.,DMITRY... is the correct way of recording the structure of a corporation where the director MIKE has subordinates MAX, ARTEM and DMITRY. ARTEM has a subordinate whose name is MIKE, just as the name of his boss and two subordinates of DMITRY are called DMITRY, just like himself.

In the Beroil corporation every employee can only correspond with his subordinates, at that the subordinates are not necessarily direct. Let's call an uncomfortable situation the situation when a person whose name is $ s $ writes a letter to another person whose name is also $ s $ . In the example given above are two such pairs: a pair involving MIKE, and two pairs for DMITRY (a pair for each of his subordinates).

Your task is by the given structure of the corporation to find the number of uncomfortable pairs in it.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF56C/9868b26a06de68925d83118f98afdf9f4510a164.png)

## 输入格式

The first and single line contains the corporation structure which is a string of length from 1 to 1000 characters. It is guaranteed that the description is correct. Every name is a string consisting of capital Latin letters from 1 to 10 symbols in length.

## 输出格式

Print a single number — the number of uncomfortable situations in the company.

## 样例 #1

### 输入

```
MIKE:MAX.,ARTEM:MIKE..,DMITRY:DMITRY.,DMITRY...

```

### 输出

```
3

```

## 样例 #2

### 输入

```
A:A..

```

### 输出

```
1

```

## 样例 #3

### 输入

```
A:C:C:C:C.....

```

### 输出

```
6

```

