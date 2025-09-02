---
title: "SNGINT - Encode Integer"
layout: "post"
diff: 普及/提高-
pid: SP18273
tag: ['贪心']
---

# SNGINT - Encode Integer

## 题目描述

Given an integer N **(0 <= N < 10 $ ^{7} $ )**. Encode N into another possible smallest integer M **(M > 0)**, such that product of digits of M equals to N.

## 输入格式

First line input is T **(total no. of test cases)**, followed by T **(T < 10001)** lines containing integer N.

## 输出格式

For each N output M or -1 **(if encoding is not possible)** in each line.

## 样例 #1

### 输入

```
3

24

5

11
```

### 输出

```
38

5

-1
```



---

---
title: "STAMPS - Stamps"
layout: "post"
diff: 普及/提高-
pid: SP3375
tag: ['贪心', '排序']
---

# STAMPS - Stamps

## 题目描述

大家都讨厌Raymond。他是地球上最大的邮票收藏家，正因为如此，他总是在集邮聚会上取笑其他人。幸运的是，每个人都爱露西，她有自己的计划。她私下问她的朋友们是否可以借给她一些邮票，这样她就可以通过展示比Raymond更大的藏品来让Raymond难堪。Raymond对自己的优越性很有把握，所以他总是说他要展示多少邮票。露西知道她拥有多少邮票，所以她知道她还需要多少邮票。她也知道有多少朋友会借给她一些邮票。但她喜欢向尽可能少的朋友借邮票，如果她需要向太多的朋友借邮票，那么她宁愿根本不去与Raymond比。你能告诉她需要向多少朋友借邮票吗？

## 输入格式

第一行包含方案的数量。每个场景都描述了一个收藏家聚会，它的第一行告诉你露西需要借多少邮票(1 ~ 1000000)，还有多少朋友(1 ~ 1000)提供给她一些邮票。在第二行，你将得到邮票的数量(1 ~ 10000)，她的每个朋友提供的身份证(?)。

## 输出格式

每个场景的输出以包含**"Scenario #i:"**的一行开始，其中我是从1开始的场景数。然后用最少的朋友数量打印一行，露西需要向他们借邮票。如果这是不可能的，即使她从每个人那里借来了一切，那就写"**impossible**  "。**用空行终止方案的输出**

## 样例 #1

### 输入

```
3

100 6

13 17 42 9 23 57

99 6

13 17 42 9 23 57

1000 3

314 159 265
```

### 输出

```
Scenario #1:

3



Scenario #2:

2



Scenario #3:

impossible
```



---

---
title: "BOOKS1 - Copying Books"
layout: "post"
diff: 普及/提高-
pid: SP43
tag: ['动态规划 DP', '贪心', '进制']
---

# BOOKS1 - Copying Books

## 样例 #1

### 输入

```
2

9 3

100 200 300 400 500 600 700 800 900

5 4

100 100 100 100 100
```

### 输出

```
100 200 300 400 500 / 600 700 / 800 900

100 / 100 / 100 / 100 100
```



---

