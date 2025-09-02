---
title: "Expensive Strings"
layout: "post"
diff: 省选/NOI-
pid: CF616F
tag: []
---

# Expensive Strings

## 题目描述

You are given $ n $ strings $ t_{i} $ . Each string has cost $ c_{i} $ .

Let's define the function of string ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF616F/a2be2e6a84d9d8ad3e2e42357554f4328caffa73.png), where $ p_{s,i} $ is the number of occurrences of $ s $ in $ t_{i} $ , $ |s| $ is the length of the string $ s $ . Find the maximal value of function $ f(s) $ over all strings.

Note that the string $ s $ is not necessarily some string from $ t $ .

## 输入格式

The first line contains the only integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of strings in $ t $ .

Each of the next $ n $ lines contains contains a non-empty string $ t_{i} $ . $ t_{i} $ contains only lowercase English letters.

It is guaranteed that the sum of lengths of all strings in $ t $ is not greater than $ 5·10^{5} $ .

The last line contains $ n $ integers $ c_{i} $ ( $ -10^{7}<=c_{i}<=10^{7} $ ) — the cost of the $ i $ -th string.

## 输出格式

Print the only integer $ a $ — the maximal value of the function $ f(s) $ over all strings $ s $ . Note one more time that the string $ s $ is not necessarily from $ t $ .

## 样例 #1

### 输入

```
2
aa
bb
2 1

```

### 输出

```
4

```

## 样例 #2

### 输入

```
2
aa
ab
2 1

```

### 输出

```
5

```

