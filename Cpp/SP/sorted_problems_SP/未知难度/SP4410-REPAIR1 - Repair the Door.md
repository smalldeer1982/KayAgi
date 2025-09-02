---
title: "REPAIR1 - Repair the Door"
layout: "post"
diff: 难度0
pid: SP4410
tag: []
---

# REPAIR1 - Repair the Door

## 题目描述

Once upon a time, there was a famous university called Famous University. As thousands of students studied and lived in FU, a gigantic residential building was built, which is called 'B37'. All students lived in B37 happily.

After decades, FU is still as famous as it had been in the past; however, the students living in it are now unhappy, because B37 is too old. Although the door of the building looks fine, it can be easily broken when being opened by some careless student too forcefully.

So, Blue Mary, the accommodation officer of B37, is facing an extremely serious problem.

With some mysterious methods, Blue Mary has predicted that exactly _N_ students will enter or exit B37 during the next term. Unfortunately she doesn't know who the careless ones are, so she assumes that every student opening the door has a probability of _P_ percent to be a careless one. When the door is broken by some careless guy, Blue Mary may repair it immediately or after some time, with a cost of _A_ yuan. Unfortunately when a student goes through the door and finds it already broken and not repaired, she will report it to the headmaster, and Blue Mary will be subject to a fine of _B_ yuan. The door is in good condition before the term begins, and will be repaired by the university after the term ends, so Blue Mary can leave the door unrepaired at the end of the term.

Being good at mathematics, Blue Mary has made a strategy, to decide when to and when not to repair the door, in order to minimize her expense.

Please write a program to calculate the expectation of her expense.

## 输入格式

The input consists of multiple test cases, the number of them is about 200000.

For each test case, there is one line containing four non-negative integers _N_, _P_, _A_, _B_ described as above, with 0<=_N_<=100000, 0<=_P_<=100, 0<=_A_<=100, 0<=_B_<=100.

End of input is indicated by a line consisting of four zeros.

## 输出格式

For each test case, output one line containing the expectation of Blue Mary's minimal expense. We accept solutions with absolute error less than 10 $ ^{-4} $ .

## 样例 #1

### 输入

```
10 100 0 1
10 100 1 0
2 50 2 1
0 0 0 0
```

### 输出

```
0.0000
0.0000
0.5000
```

