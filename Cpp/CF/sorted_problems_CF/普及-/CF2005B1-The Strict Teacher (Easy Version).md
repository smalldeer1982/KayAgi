---
title: "The Strict Teacher (Easy Version)"
layout: "post"
diff: 普及-
pid: CF2005B1
tag: ['数学', '分类讨论']
---

# The Strict Teacher (Easy Version)

## 题目描述

This is the easy version of the problem. The only differences between the two versions are the constraints on $ m $ and $ q $ . In this version, $ m=2 $ and $ q=1 $ . You can make hacks only if both versions of the problem are solved.

Narek and Tsovak were busy preparing this round, so they have not managed to do their homework and decided to steal David's homework. Their strict teacher noticed that David has no homework and now wants to punish him. She hires other teachers to help her catch David. And now $ m $ teachers together are chasing him. Luckily, the classroom is big, so David has many places to hide.

The classroom can be represented as a one-dimensional line with cells from $ 1 $ to $ n $ , inclusive.

At the start, all $ m $ teachers and David are in distinct cells. Then they make moves. During each move

- David goes to an adjacent cell or stays at the current one.
- Then, each of the $ m $ teachers simultaneously goes to an adjacent cell or stays at the current one.

This continues until David is caught. David is caught if any of the teachers (possibly more than one) is located in the same cell as David. Everyone sees others' moves, so they all act optimally.

Your task is to find how many moves it will take for the teachers to catch David if they all act optimally.

Acting optimally means the student makes his moves in a way that maximizes the number of moves the teachers need to catch him; and the teachers coordinate with each other to make their moves in a way that minimizes the number of moves they need to catch the student.

Also, as Narek and Tsovak think this task is easy, they decided to give you $ q $ queries on David's position. Note: this is the easy version, and you are given only one query.

## 输入格式

In the first line of the input, you are given a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases. The description of each test case follows.

In the first line of each test case, you are given three integers $ n $ , $ m $ , and $ q $ ( $ 3 \le n \le 10^9 $ , $ m=2 $ , $ q=1 $ ) — the number of cells on the line, the number of teachers, and the number of queries.

In the second line of each test case, you are given $ m $ distinct integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \le b_i \le n $ ) — the cell numbers of the teachers.

In the third line of each test case, you are given $ q $ integers $ a_1, a_2, \ldots, a_q $ ( $ 1 \le a_i \le n $ ) — David's cell number for every query.

It is guaranteed that for any $ i $ , $ j $ such that $ 1 \le i \le m $ and $ 1 \le j \le q $ , $ b_i \neq a_j $ .

## 输出格式

For each test case, output $ q $ lines, the $ i $ -th of them containing the answer of the $ i $ -th query.

## 说明/提示

In the first example, the student can just stay at cell $ 2 $ . The teacher, initially located in cell $ 1 $ , can reach cell $ 2 $ in one move. Therefore, the answer is $ 1 $ .

In the second example, the student should just stay at cell $ 1 $ . The teacher, initially located in cell $ 3 $ , can reach cell $ 1 $ in two moves. Therefore, the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
10 2 1
1 4
2
8 2 1
3 6
1
8 2 1
3 6
8
```

### 输出

```
1
2
2
```

