---
title: "Mathematical Analysis Rocks!"
layout: "post"
diff: 普及-
pid: CF180F
tag: []
---

# Mathematical Analysis Rocks!

## 题目描述

Students of group 199 have written their lectures dismally. Now an exam on Mathematical Analysis is approaching and something has to be done asap (that is, quickly). Let's number the students of the group from 1 to $ n $ . Each student $ i $ ( $ 1<=i<=n $ ) has a best friend $ p[i] $ ( $ 1<=p[i]<=n $ ). In fact, each student is a best friend of exactly one student. In other words, all $ p[i] $ are different. It is possible that the group also has some really "special individuals" for who $ i=p[i] $ .

Each student wrote exactly one notebook of lecture notes. We know that the students agreed to act by the following algorithm:

- on the first day of revising each student studies his own Mathematical Analysis notes,
- in the morning of each following day each student gives the notebook to his best friend and takes a notebook from the student who calls him the best friend.

Thus, on the second day the student $ p[i] $ ( $ 1<=i<=n $ ) studies the $ i $ -th student's notes, on the third day the notes go to student $ p[p[i]] $ and so on. Due to some characteristics of the boys' friendship (see paragraph 1), each day each student has exactly one notebook to study.

You are given two sequences that describe the situation on the third and fourth days of revising:

- $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ means the student who gets the $ i $ -th student's notebook on the third day of revising;
- $ b_{1},b_{2},...,b_{n} $ , where $ b_{i} $ means the student who gets the $ i $ -th student's notebook on the fourth day of revising.

You do not know array $ p $ , that is you do not know who is the best friend to who. Write a program that finds $ p $ by the given sequences $ a $ and $ b $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of students in the group. The second line contains sequence of different integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=n $ ). The third line contains the sequence of different integers $ b_{1},b_{2},...,b_{n} $ ( $ 1<=b_{i}<=n $ ).

## 输出格式

Print sequence $ n $ of different integers $ p[1],p[2],...,p[n] $ ( $ 1<=p[i]<=n $ ). It is guaranteed that the solution exists and that it is unique.

## 样例 #1

### 输入

```
4
2 1 4 3
3 4 2 1

```

### 输出

```
4 3 1 2 
```

## 样例 #2

### 输入

```
5
5 2 3 1 4
1 3 2 4 5

```

### 输出

```
4 3 2 5 1 
```

## 样例 #3

### 输入

```
2
1 2
2 1

```

### 输出

```
2 1 
```

