---
title: "Chat Order"
layout: "post"
diff: 普及/提高-
pid: CF637B
tag: ['队列']
---

# Chat Order

## 题目描述

有一个队列，初始时为空。现在依次插入 $n$ 个单词，如果这个单词已经在队列中，那就把这个单词从原来位置移到队首，否则直接把这个单词放到队首。问你最后这个队列长啥样。

## 输入格式

第一行，一个整数 $n$ ( $1 \le n \le 200000 $)，表示单词的数量。接下来 $n$ 行，每行一个单词，每个单词都由小写字母构成，非空且长度均不超过 $10$ 。

## 输出格式

若干行，每行一个单词，依次表示从队首到队尾的每个单词。

## 样例 #1

### 输入

```
4
alex
ivan
roman
ivan

```

### 输出

```
ivan
roman
alex

```

## 样例 #2

### 输入

```
8
alina
maria
ekaterina
darya
darya
ekaterina
maria
alina

```

### 输出

```
alina
maria
ekaterina
darya

```

