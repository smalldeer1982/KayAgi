---
title: "Before an Exam"
layout: "post"
diff: 普及-
pid: CF4B
tag: ['贪心', '优先队列', '前缀和']
---

# Before an Exam

## 题目描述

Tomorrow Peter has a Biology exam. He does not like this subject much, but $ d $ days ago he learnt that he would have to take this exam. Peter's strict parents made him prepare for the exam immediately, for this purpose he has to study not less than $ minTime_{i} $ and not more than $ maxTime_{i} $ hours per each $ i $ -th day. Moreover, they warned Peter that a day before the exam they would check how he has followed their instructions.

So, today is the day when Peter's parents ask him to show the timetable of his preparatory studies. But the boy has counted only the sum of hours $ sumTime $ spent him on preparation, and now he wants to know if he can show his parents a timetable $ sсhedule $ with $ d $ numbers, where each number $ sсhedule_{i} $ stands for the time in hours spent by Peter each $ i $ -th day on biology studies, and satisfying the limitations imposed by his parents, and at the same time the sum total of all $ schedule_{i} $ should equal to $ sumTime $ .

## 输入格式

The first input line contains two integer numbers $ d,sumTime $ ( $ 1<=d<=30,0<=sumTime<=240 $ ) — the amount of days, during which Peter studied, and the total amount of hours, spent on preparation. Each of the following $ d $ lines contains two integer numbers $ minTime_{i},maxTime_{i} $ ( $ 0<=minTime_{i}<=maxTime_{i}<=8 $ ), separated by a space — minimum and maximum amount of hours that Peter could spent in the $ i $ -th day.

## 输出格式

In the first line print YES, and in the second line print $ d $ numbers (separated by a space), each of the numbers — amount of hours, spent by Peter on preparation in the corresponding day, if he followed his parents' instructions; or print NO in the unique line. If there are many solutions, print any of them.

## 样例 #1

### 输入

```
1 48
5 7

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
2 5
0 1
3 5

```

### 输出

```
YES
1 4 
```



---

