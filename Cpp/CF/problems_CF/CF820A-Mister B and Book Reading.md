---
title: "Mister B and Book Reading"
layout: "post"
diff: 普及-
pid: CF820A
tag: []
---

# Mister B and Book Reading

## 题目描述

Mister B once received a gift: it was a book about aliens, which he started read immediately. This book had $ c $ pages.

At first day Mister B read $ v_{0} $ pages, but after that he started to speed up. Every day, starting from the second, he read $ a $ pages more than on the previous day (at first day he read $ v_{0} $ pages, at second — $ v_{0}+a $ pages, at third — $ v_{0}+2a $ pages, and so on). But Mister B is just a human, so he physically wasn't able to read more than $ v_{1} $ pages per day.

Also, to refresh his memory, every day, starting from the second, Mister B had to reread last $ l $ pages he read on the previous day. Mister B finished the book when he read the last page for the first time.

Help Mister B to calculate how many days he needed to finish the book.

## 输入格式

First and only line contains five space-separated integers: $ c $ , $ v_{0} $ , $ v_{1} $ , $ a $ and $ l $ ( $ 1<=c<=1000 $ , $ 0<=l&lt;v_{0}<=v_{1}<=1000 $ , $ 0<=a<=1000 $ ) — the length of the book in pages, the initial reading speed, the maximum reading speed, the acceleration in reading speed and the number of pages for rereading.

## 输出格式

Print one integer — the number of days Mister B needed to finish the book.

## 说明/提示

In the first sample test the book contains $ 5 $ pages, so Mister B read it right at the first day.

In the second sample test at first day Mister B read pages number $ 1-4 $ , at second day — $ 4-11 $ , at third day — $ 11-12 $ and finished the book.

In third sample test every day Mister B read $ 1 $ page of the book, so he finished in 15 days.

## 样例 #1

### 输入

```
5 5 10 5 4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
12 4 12 4 1

```

### 输出

```
3

```

## 样例 #3

### 输入

```
15 1 100 0 0

```

### 输出

```
15

```

