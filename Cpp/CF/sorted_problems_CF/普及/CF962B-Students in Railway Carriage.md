---
title: "Students in Railway Carriage"
layout: "post"
diff: 普及/提高-
pid: CF962B
tag: []
---

# Students in Railway Carriage

## 题目描述

There are $ n $ consecutive seat places in a railway carriage. Each place is either empty or occupied by a passenger.

The university team for the Olympiad consists of $ a $ student-programmers and $ b $ student-athletes. Determine the largest number of students from all $ a+b $ students, which you can put in the railway carriage so that:

- no student-programmer is sitting next to the student-programmer;
- and no student-athlete is sitting next to the student-athlete.

In the other words, there should not be two consecutive (adjacent) places where two student-athletes or two student-programmers are sitting.

Consider that initially occupied seat places are occupied by jury members (who obviously are not students at all).

## 输入格式

The first line contain three integers $ n $ , $ a $ and $ b $ ( $ 1 \le n \le 2\cdot10^{5} $ , $ 0 \le a, b \le 2\cdot10^{5} $ , $ a + b > 0 $ ) — total number of seat places in the railway carriage, the number of student-programmers and the number of student-athletes.

The second line contains a string with length $ n $ , consisting of characters "." and "\*". The dot means that the corresponding place is empty. The asterisk means that the corresponding place is occupied by the jury member.

## 输出格式

Print the largest number of students, which you can put in the railway carriage so that no student-programmer is sitting next to a student-programmer and no student-athlete is sitting next to a student-athlete.

## 说明/提示

In the first example you can put all student, for example, in the following way: \*.AB\*

In the second example you can put four students, for example, in the following way: \*BAB\*B

In the third example you can put seven students, for example, in the following way: B\*ABAB\*\*A\*B

The letter A means a student-programmer, and the letter B — student-athlete.

## 样例 #1

### 输入

```
5 1 1
*...*

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6 2 3
*...*.

```

### 输出

```
4

```

## 样例 #3

### 输入

```
11 3 10
.*....**.*.

```

### 输出

```
7

```

## 样例 #4

### 输入

```
3 2 3
***

```

### 输出

```
0

```

