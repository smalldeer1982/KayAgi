---
title: "Exams"
layout: "post"
diff: 提高+/省选-
pid: CF732D
tag: []
---

# Exams

## 题目描述

Vasiliy has an exam period which will continue for $ n $ days. He has to pass exams on $ m $ subjects. Subjects are numbered from 1 to $ m $ .

About every day we know exam for which one of $ m $ subjects can be passed on that day. Perhaps, some day you can't pass any exam. It is not allowed to pass more than one exam on any day.

On each day Vasiliy can either pass the exam of that day (it takes the whole day) or prepare all day for some exam or have a rest.

About each subject Vasiliy know a number $ a_{i} $ — the number of days he should prepare to pass the exam number $ i $ . Vasiliy can switch subjects while preparing for exams, it is not necessary to prepare continuously during $ a_{i} $ days for the exam number $ i $ . He can mix the order of preparation for exams in any way.

Your task is to determine the minimum number of days in which Vasiliy can pass all exams, or determine that it is impossible. Each exam should be passed exactly one time.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{5} $ ) — the number of days in the exam period and the number of subjects.

The second line contains $ n $ integers $ d_{1},d_{2},...,d_{n} $ ( $ 0<=d_{i}<=m $ ), where $ d_{i} $ is the number of subject, the exam of which can be passed on the day number $ i $ . If $ d_{i} $ equals 0, it is not allowed to pass any exams on the day number $ i $ .

The third line contains $ m $ positive integers $ a_{1},a_{2},...,a_{m} $ ( $ 1<=a_{i}<=10^{5} $ ), where $ a_{i} $ is the number of days that are needed to prepare before passing the exam on the subject $ i $ .

## 输出格式

Print one integer — the minimum number of days in which Vasiliy can pass all exams. If it is impossible, print -1.

## 说明/提示

In the first example Vasiliy can behave as follows. On the first and the second day he can prepare for the exam number 1 and pass it on the fifth day, prepare for the exam number 2 on the third day and pass it on the fourth day.

In the second example Vasiliy should prepare for the exam number 3 during the first four days and pass it on the fifth day. Then on the sixth day he should prepare for the exam number 2 and then pass it on the seventh day. After that he needs to prepare for the exam number 1 on the eighth day and pass it on the ninth day.

In the third example Vasiliy can't pass the only exam because he hasn't anough time to prepare for it.

## 样例 #1

### 输入

```
7 2
0 1 0 2 1 0 2
2 1

```

### 输出

```
5

```

## 样例 #2

### 输入

```
10 3
0 0 1 2 3 0 2 0 1 2
1 1 4

```

### 输出

```
9

```

## 样例 #3

### 输入

```
5 1
1 1 1 1 1
5

```

### 输出

```
-1

```

