---
title: "Valera and Contest"
layout: "post"
diff: 普及-
pid: CF369B
tag: []
---

# Valera and Contest

## 题目描述

Valera loves to participate in competitions. Especially in programming contests. Today he has participated in the contest with his team, consisting of $ n $ students (including Valera). This contest was an individual competition, so each student in the team solved problems individually.

After the contest was over, Valera was interested in results. He found out that:

- each student in the team scored at least $ l $ points and at most $ r $ points;
- in total, all members of the team scored exactly $ s_{all} $ points;
- the total score of the $ k $ members of the team who scored the most points is equal to exactly $ s_{k} $ ; more formally, if $ a_{1},a_{2},...,a_{n} $ is the sequence of points earned by the team of students in the non-increasing order $ (a_{1}>=a_{2}>=...>=a_{n}) $ , then $ s_{k}=a_{1}+a_{2}+...+a_{k} $ .

However, Valera did not find out exactly how many points each of $ n $ students scored. Valera asked you to recover any distribution of scores between the students of the team, such that all the conditions above are met.

## 输入格式

The first line of the input contains exactly six integers $ n,k,l,r,s_{all},s_{k} $ ( $ 1<=n,k,l,r<=1000 $ ; $ l<=r $ ; $ k<=n $ ; $ 1<=s_{k}<=s_{all}<=10^{6} $ ).

It's guaranteed that the input is such that the answer exists.

## 输出格式

Print exactly $ n $ integers $ a_{1},a_{2},...,a_{n} $ — the number of points each student scored. If there are multiple solutions, you can print any of them. You can print the distribution of points in any order.

## 样例 #1

### 输入

```
5 3 1 3 13 9

```

### 输出

```
2 3 2 3 3 
```

## 样例 #2

### 输入

```
5 3 1 3 15 9

```

### 输出

```
3 3 3 3 3 
```

