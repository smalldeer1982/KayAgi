---
title: "Campus"
layout: "post"
diff: 省选/NOI-
pid: CF571D
tag: []
---

# Campus

## 题目描述

Oscolcovo city has a campus consisting of $ n $ student dormitories, $ n $ universities and $ n $ military offices. Initially, the $ i $ -th dormitory belongs to the $ i $ -th university and is assigned to the $ i $ -th military office.

Life goes on and the campus is continuously going through some changes. The changes can be of four types:

1. University $ a_{j} $ merges with university $ b_{j} $ . After that all the dormitories that belonged to university $ b_{j} $ are assigned to to university $ a_{j} $ , and university $ b_{j} $ disappears.
2. Military office $ c_{j} $ merges with military office $ d_{j} $ . After that all the dormitories that were assigned to military office $ d_{j} $ , are assigned to military office $ c_{j} $ , and military office $ d_{j} $ disappears.
3. Students of university $ x_{j} $ move in dormitories. Lets $ k_{xj} $ is the number of dormitories that belong to this university at the time when the students move in. Then the number of students in each dormitory of university $ x_{j} $ increases by $ k_{xj} $ (note that the more dormitories belong to the university, the more students move in each dormitory of the university).
4. Military office number $ y_{j} $ conducts raids on all the dormitories assigned to it and takes all students from there.

Thus, at each moment of time each dormitory is assigned to exactly one university and one military office. Initially, all the dormitory are empty.

Your task is to process the changes that take place in the campus and answer the queries, how many people currently live in dormitory $ q_{j} $ .

## 输入格式

The first line contains two integers, $ n $ and $ m $ $ (1<=n,m<=5·10^{5}) $ — the number of dormitories and the number of queries, respectively.

Next $ m $ lines contain the queries, each of them is given in one of the following formats:

- «U $ a_{j} $ $ b_{j} $ » — merging universities;
- «M $ c_{j} $ $ d_{j} $ » — merging military offices;
- «A $ x_{j} $ » — students of university $ x_{j} $ moving in the dormitories;
- «Z $ y_{j} $ » — a raid in military office $ y_{j} $ ;
- «Q $ q_{j} $ » — a query asking the number of people in dormitory $ q_{j} $ .

 All the numbers in the queries are positive integers and do not exceed $ n $ . It is guaranteed that at the moment of the query the universities and military offices, that are present in the query, exist.

## 输出格式

In the $ i $ -th line print the answer to the $ i $ -th query asking the number of people in the dormitory.

## 说明/提示

Consider the first sample test:

- In the first query university 1 owns only dormitory 1, so after the query dormitory 1 will have 1 student.
- After the third query university 1 owns dormitories 1 and 2.
- The fourth query increases by 2 the number of students living in dormitories 1 and 2 that belong to university number 1. After that 3 students live in the first dormitory and 2 students live in the second dormitory.
- At the fifth query the number of students living in dormitory 1, assigned to the military office 1, becomes zero.

## 样例 #1

### 输入

```
2 7
A 1
Q 1
U 1 2
A 1
Z 1
Q 1
Q 2

```

### 输出

```
1
0
2

```

## 样例 #2

### 输入

```
5 12
U 1 2
M 4 5
A 1
Q 1
A 3
A 4
Q 3
Q 4
Z 4
Q 4
A 5
Q 5

```

### 输出

```
2
1
1
0
1

```

