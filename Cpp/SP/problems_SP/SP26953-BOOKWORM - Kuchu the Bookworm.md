---
title: "BOOKWORM - Kuchu the Bookworm"
layout: "post"
diff: 难度0
pid: SP26953
tag: []
---

# BOOKWORM - Kuchu the Bookworm

## 题目描述

In this problem, you’ll be helping a little bookworm, Kuchu.

Recently “Omuk book shop” has announced a huge sale on various books. Being a bookworm, Kuchu could not miss this opportunity and went there immediately!

When reached there, she noticed that conditions of the sale are:

1. One must buy exactly B books to get the discount.
2. Maximum number of pages in any book is no more than 100.


As she wants to read as much as possible, Kuchu wants to get maximum number of pages satisfying the conditions above. Now she is wondering if there are N books in the store, how many different ways are there to choose exactly B books so that the number of pages is maximum possible.

Not all books are interesting to little kids, so you are given two information about each book-

1. Number of pages P.
2. Interest value V. V is 1 if the book is interesting for kids and 0 otherwise.

### Input

First line contains an integer T, the number of test cases.

For each test case, the first line contains two integers N and B as mentioned above. Next N lines contain two integers each P $ _{i} $ and V $ _{i} $ , number of pages and interest factor of ith book.

1

1

1

1

0

### Output

For each test case, print one integer, the number of different ways to choose exactly B **interesting books** from those N books so that the number of pages is maximum possible. As result can be pretty large, print it modulo **1,000,000,007 (10^9+7)**.

### Example

 ```
<pre style="text-align: left;"><strong>Input:</strong>
<p>2<br></br>2 1<br></br>2 0<br></br>3 0<br></br>5 3<br></br>10 0<br></br>5 1<br></br>2 1<br></br>2 1<br></br>2 1</p><strong>Output:</strong>
<p>0<br></br>3</p>
```

