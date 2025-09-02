---
title: "Handshakes"
layout: "post"
diff: 提高+/省选-
pid: CF534D
tag: []
---

# Handshakes

## 题目描述

On February, 30th $ n $ students came in the Center for Training Olympiad Programmers (CTOP) of the Berland State University. They came one by one, one after another. Each of them went in, and before sitting down at his desk, greeted with those who were present in the room by shaking hands. Each of the students who came in stayed in CTOP until the end of the day and never left.

At any time any three students could join together and start participating in a team contest, which lasted until the end of the day. The team did not distract from the contest for a minute, so when another student came in and greeted those who were present, he did not shake hands with the members of the contest writing team. Each team consisted of exactly three students, and each student could not become a member of more than one team. Different teams could start writing contest at different times.

Given how many present people shook the hands of each student, get a possible order in which the students could have come to CTOP. If such an order does not exist, then print that this is impossible.

Please note that some students could work independently until the end of the day, without participating in a team contest.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=2·10^{5} $ ) — the number of students who came to CTOP. The next line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}&lt;n $ ), where $ a_{i} $ is the number of students with who the $ i $ -th student shook hands.

## 输出格式

If the sought order of students exists, print in the first line "Possible" and in the second line print the permutation of the students' numbers defining the order in which the students entered the center. Number $ i $ that stands to the left of number $ j $ in this permutation means that the $ i $ -th student came earlier than the $ j $ -th student. If there are multiple answers, print any of them.

If the sought order of students doesn't exist, in a single line print "Impossible".

## 说明/提示

In the first sample from the statement the order of events could be as follows:

- student 4 comes in ( $ a_{4}=0 $ ), he has no one to greet;
- student 5 comes in ( $ a_{5}=1 $ ), he shakes hands with student 4;
- student 1 comes in ( $ a_{1}=2 $ ), he shakes hands with two students (students 4, 5);
- student 3 comes in ( $ a_{3}=3 $ ), he shakes hands with three students (students 4, 5, 1);
- students 4, 5, 3 form a team and start writing a contest;
- student 2 comes in ( $ a_{2}=1 $ ), he shakes hands with one student (number 1).

In the second sample from the statement the order of events could be as follows:

- student 7 comes in ( $ a_{7}=0 $ ), he has nobody to greet;
- student 5 comes in ( $ a_{5}=1 $ ), he shakes hands with student 7;
- student 2 comes in ( $ a_{2}=2 $ ), he shakes hands with two students (students 7, 5);
- students 7, 5, 2 form a team and start writing a contest;
- student 1 comes in( $ a_{1}=0 $ ), he has no one to greet (everyone is busy with the contest);
- student 6 comes in ( $ a_{6}=1 $ ), he shakes hands with student 1;
- student 8 comes in ( $ a_{8}=2 $ ), he shakes hands with two students (students 1, 6);
- student 3 comes in ( $ a_{3}=3 $ ), he shakes hands with three students (students 1, 6, 8);
- student 4 comes in ( $ a_{4}=4 $ ), he shakes hands with four students (students 1, 6, 8, 3);
- students 8, 3, 4 form a team and start writing a contest;
- student 9 comes in ( $ a_{9}=2 $ ), he shakes hands with two students (students 1, 6).

In the third sample from the statement the order of events is restored unambiguously:

- student 1 comes in ( $ a_{1}=0 $ ), he has no one to greet;
- student 3 comes in (or student 4) ( $ a_{3}=a_{4}=1 $ ), he shakes hands with student 1;
- student 2 comes in ( $ a_{2}=2 $ ), he shakes hands with two students (students 1, 3 (or 4));
- the remaining student 4 (or student 3), must shake one student's hand ( $ a_{3}=a_{4}=1 $ ) but it is impossible as there are only two scenarios: either a team formed and he doesn't greet anyone, or he greets all the three present people who work individually.

## 样例 #1

### 输入

```
5
2 1 3 0 1

```

### 输出

```
Possible
4 5 1 3 2 
```

## 样例 #2

### 输入

```
9
0 2 3 4 1 1 0 2 2

```

### 输出

```
Possible
7 5 2 1 6 8 3 4 9
```

## 样例 #3

### 输入

```
4
0 2 1 1

```

### 输出

```
Impossible

```

