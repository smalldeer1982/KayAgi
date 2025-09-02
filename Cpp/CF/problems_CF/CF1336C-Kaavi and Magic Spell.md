---
title: "Kaavi and Magic Spell"
layout: "post"
diff: 提高+/省选-
pid: CF1336C
tag: []
---

# Kaavi and Magic Spell

## 题目描述

Kaavi, the mysterious fortune teller, deeply believes that one's fate is inevitable and unavoidable. Of course, she makes her living by predicting others' future. While doing divination, Kaavi believes that magic spells can provide great power for her to see the future.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336C/28f922a8d61b005da66667b890172094e2d89686.png)

Kaavi has a string $ T $ of length $ m $ and all the strings with the prefix $ T $ are magic spells. Kaavi also has a string $ S $ of length $ n $ and an empty string $ A $ .

During the divination, Kaavi needs to perform a sequence of operations. There are two different operations:

- Delete the first character of $ S $ and add it at the front of $ A $ .
- Delete the first character of $ S $ and add it at the back of $ A $ .

Kaavi can perform no more than $ n $ operations. To finish the divination, she wants to know the number of different operation sequences to make $ A $ a magic spell (i.e. with the prefix $ T $ ). As her assistant, can you help her? The answer might be huge, so Kaavi only needs to know the answer modulo $ 998\,244\,353 $ .

Two operation sequences are considered different if they are different in length or there exists an $ i $ that their $ i $ -th operation is different.

A substring is a contiguous sequence of characters within a string. A prefix of a string $ S $ is a substring of $ S $ that occurs at the beginning of $ S $ .

## 输入格式

The first line contains a string $ S $ of length $ n $ ( $ 1 \leq n \leq 3000 $ ).

The second line contains a string $ T $ of length $ m $ ( $ 1 \leq m \leq n $ ).

Both strings contain only lowercase Latin letters.

## 输出格式

The output contains only one integer — the answer modulo $ 998\,244\,353 $ .

## 说明/提示

The first test:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336C/fc1e4ff58b9c787fb84f7835d5e964b3b486f03c.png)

The red ones are the magic spells. In the first operation, Kaavi can either add the first character "a" at the front or the back of $ A $ , although the results are the same, they are considered as different operations. So the answer is $ 6\times2=12 $ .

## 样例 #1

### 输入

```
abab
ba
```

### 输出

```
12
```

## 样例 #2

### 输入

```
defineintlonglong
signedmain
```

### 输出

```
0
```

## 样例 #3

### 输入

```
rotator
rotator
```

### 输出

```
4
```

## 样例 #4

### 输入

```
cacdcdbbbb
bdcaccdbbb
```

### 输出

```
24
```

