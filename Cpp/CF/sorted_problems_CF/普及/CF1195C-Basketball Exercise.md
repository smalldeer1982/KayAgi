---
title: "Basketball Exercise"
layout: "post"
diff: 普及/提高-
pid: CF1195C
tag: []
---

# Basketball Exercise

## 题目描述

Finally, a basketball court has been opened in SIS, so Demid has decided to hold a basketball exercise session. $ 2 \cdot n $ students have come to Demid's exercise session, and he lined up them into two rows of the same size (there are exactly $ n $ people in each row). Students are numbered from $ 1 $ to $ n $ in each row in order from left to right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195C/05855164ffa55108436f13cfefdb8a460d04c2d7.png)Now Demid wants to choose a team to play basketball. He will choose players from left to right, and the index of each chosen player (excluding the first one) will be strictly greater than the index of the previously chosen player. To avoid giving preference to one of the rows, Demid chooses students in such a way that no consecutive chosen students belong to the same row. The first student can be chosen among all $ 2n $ students (there are no additional constraints), and a team can consist of any number of students.

Demid thinks, that in order to compose a perfect team, he should choose students in such a way, that the total height of all chosen students is maximum possible. Help Demid to find the maximum possible total height of players in a team he can choose.

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of students in each row.

The second line of the input contains $ n $ integers $ h_{1, 1}, h_{1, 2}, \ldots, h_{1, n} $ ( $ 1 \le h_{1, i} \le 10^9 $ ), where $ h_{1, i} $ is the height of the $ i $ -th student in the first row.

The third line of the input contains $ n $ integers $ h_{2, 1}, h_{2, 2}, \ldots, h_{2, n} $ ( $ 1 \le h_{2, i} \le 10^9 $ ), where $ h_{2, i} $ is the height of the $ i $ -th student in the second row.

## 输出格式

Print a single integer — the maximum possible total height of players in a team Demid can choose.

## 说明/提示

In the first example Demid can choose the following team as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195C/9a3e2230ef98dd0879303ff329fc9cb7b1cf5209.png)In the second example Demid can choose the following team as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195C/c3c20000e8e493da34f3e2b1ef145d407e671b29.png)

## 样例 #1

### 输入

```
5
9 3 5 7 3
5 8 1 4 5

```

### 输出

```
29

```

## 样例 #2

### 输入

```
3
1 2 9
10 1 1

```

### 输出

```
19

```

## 样例 #3

### 输入

```
1
7
4

```

### 输出

```
7

```

