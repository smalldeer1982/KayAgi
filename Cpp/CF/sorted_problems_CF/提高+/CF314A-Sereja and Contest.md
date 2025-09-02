---
title: "Sereja and Contest"
layout: "post"
diff: 提高+/省选-
pid: CF314A
tag: []
---

# Sereja and Contest

## 题目描述

During the last Sereja's Codesecrof round the server crashed many times, so the round was decided to be made unrated for some participants.

Let's assume that $ n $ people took part in the contest. Let's assume that the participant who got the first place has rating $ a_{1} $ , the second place participant has rating $ a_{2} $ , $ ... $ , the $ n $ -th place participant has rating $ a_{n} $ . Then changing the rating on the Codesecrof site is calculated by the formula ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF314A/c51703a6e7729252fb6f20e8a44b483ddf07fc8e.png).

After the round was over, the Codesecrof management published the participants' results table. They decided that if for a participant $ d_{i}&lt;k $ , then the round can be considered unrated for him. But imagine the management's surprise when they found out that the participants' rating table is dynamic. In other words, when some participant is removed from the rating, he is removed from the results' table and the rating is recalculated according to the new table. And of course, all applications for exclusion from the rating are considered in view of the current table.

We know that among all the applications for exclusion from the rating the first application to consider is from the participant with the best rank (the rank with the minimum number), for who $ d_{i}&lt;k $ . We also know that the applications for exclusion from rating were submitted by all participants.

Now Sereja wonders, what is the number of participants to be excluded from the contest rating, and the numbers of the participants in the original table in the order of their exclusion from the rating. Pay attention to the analysis of the first test case for a better understanding of the statement.

## 输入格式

The first line contains two integers $ n $ , $ k $ $ (1<=n<=2·10^{5},-10^{9}<=k<=0) $ . The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ — ratings of the participants in the initial table.

## 输出格式

Print the numbers of participants in the order in which they were removed from the table. Print the initial numbers of the participants, that is, the numbers that the participants had in the initial table.

## 说明/提示

Consider the first test sample.

1. Initially the sequence of the contest participants' ratings equals \[5, 3, 4, 1, 2\]. You can use this sequence to calculate the sequence of rating changes: \[0, -9, -13, 8, 14\]. According to the problem statement, the application of the participant who won the second place will be considered first.
2. As soon as the second place winner is out from the ratings, the participants' rating sequence will equal \[5, 4, 1, 2\]. By this sequence you can count the new sequence of rating changes: \[0, -8, 2, 6\]. According to the problem statement, the application of the participant who won the second place will be considered. Initially this participant won third place.
3. The new rating sequence equals \[5, 1, 2\], the new sequence of rating changes equals \[0, -1, 1\]. The second place participant's application is taken into consideration, initially this participant won the fourth place.
4. The new rating sequence equals \[5, 2\], the new sequence of rating changes equals \[0, 0\]. No more applications will be considered.

Thus, you should print 2, 3, 4.

## 样例 #1

### 输入

```
5 0
5 3 4 1 2

```

### 输出

```
2
3
4

```

## 样例 #2

### 输入

```
10 -10
5 5 1 7 5 1 2 4 9 2

```

### 输出

```
2
4
5
7
8
9

```

