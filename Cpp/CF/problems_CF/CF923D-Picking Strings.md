---
title: "Picking Strings"
layout: "post"
diff: 省选/NOI-
pid: CF923D
tag: []
---

# Picking Strings

## 题目描述

Alice has a string consisting of characters 'A', 'B' and 'C'. Bob can use the following transitions on any substring of our string in any order any number of times:

- A ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923D/5a518872d8942914aef6c33d251688a64a8d6d74.png)BC
- B ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923D/5a518872d8942914aef6c33d251688a64a8d6d74.png)AC
- C ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923D/5a518872d8942914aef6c33d251688a64a8d6d74.png)AB
- AAA ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923D/5a518872d8942914aef6c33d251688a64a8d6d74.png) empty string

Note that a substring is one or more consecutive characters. For given queries, determine whether it is possible to obtain the target string from source.

## 输入格式

The first line contains a string $ S $ ( $ 1<=|S|<=10^{5} $ ). The second line contains a string $ T $ ( $ 1<=|T|<=10^{5} $ ), each of these strings consists only of uppercase English letters 'A', 'B' and 'C'.

The third line contains the number of queries $ Q $ ( $ 1<=Q<=10^{5} $ ).

The following $ Q $ lines describe queries. The $ i $ -th of these lines contains four space separated integers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ , $ d_{i} $ . These represent the $ i $ -th query: is it possible to create $ T[c_{i}..d_{i}] $ from $ S[a_{i}..b_{i}] $ by applying the above transitions finite amount of times?

Here, $ U[x..y] $ is a substring of $ U $ that begins at index $ x $ (indexed from 1) and ends at index $ y $ . In particular, $ U[1..|U|] $ is the whole string $ U $ .

It is guaranteed that $ 1<=a<=b<=|S| $ and $ 1<=c<=d<=|T| $ .

## 输出格式

Print a string of $ Q $ characters, where the $ i $ -th character is '1' if the answer to the $ i $ -th query is positive, and '0' otherwise.

## 说明/提示

In the first query we can achieve the result, for instance, by using transitions ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF923D/bc389404fee8abb9f1186ea5ef11a96a445486ca.png).

The third query asks for changing AAB to A — but in this case we are not able to get rid of the character 'B'.

## 样例 #1

### 输入

```
AABCCBAAB
ABCB
5
1 3 1 2
2 2 2 4
7 9 1 1
3 4 2 3
4 5 1 3

```

### 输出

```
10011

```

