---
title: "PHONELST - Phone List"
layout: "post"
diff: 普及/提高-
pid: SP4033
tag: ['字符串', '字典树 Trie']
---

# PHONELST - Phone List

## 题目描述

**【题目来源】**

	Poj3630

**【问题描述】**

	给定n个长度不超过10的数字串，问其中是否存在两个数字串S，T，使得S是T的前缀。有多组数据，数据组数不超过40。n<=10000。

## 输入格式

第一行，一个整数T，表示数据组数。
	对于每组数据，第一行一个数n，接下去n行，输入n个数字串。

## 输出格式

对于每组数据，若存在两个数字串S，T，使得S是T的前缀，则输出“NO”，否则输出“YES”。

**【数据规模】**

	n<=10000

## 样例 #1

### 输入

```
2
3
911
97625999
91125426
5
113
12340
123440
12345
98346
```

### 输出

```
NO
YES
```



---

---
title: "PALIN - The Next Palindrome"
layout: "post"
diff: 普及/提高-
pid: SP5
tag: ['字符串', '数学', '枚举']
---

# PALIN - The Next Palindrome

## 题目描述

A positive integer is called a _palindrome_ if its representation in the decimal system is the same when read from left to right and from right to left. For a given positive integer _K_ of not more than 1000000 digits, write the value of the smallest palindrome larger than _K_ to output. Numbers are always displayed without leading zeros.

## 输入格式

The first line contains integer _t_, the number of test cases. Integers _K_ are given in the next _t_ lines.

## 输出格式

For each _K_, output the smallest palindrome larger than _K_.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages**

## 样例 #1

### 输入

```
2

808

2133
```

### 输出

```
818

2222
```



---

---
title: "JULKA - Julka"
layout: "post"
diff: 普及/提高-
pid: SP54
tag: ['字符串', '数学', '高精度']
---

# JULKA - Julka

## 题目描述

 Julka surprised her teacher at preschool by solving the following riddle:

  _Klaudia and Natalia have 10 apples together, but Klaudia has two apples more than Natalia. How many apples does each of he girls have?_

 Julka said without thinking: Klaudia has 6 apples and Natalia 4 apples. The teacher tried to check if Julka's answer wasn't accidental and repeated the riddle every time increasing the numbers. Every time Julka answered correctly. The surprised teacher wanted to continue questioning Julka, but with big numbers she could't solve the riddle fast enough herself. Help the teacher and write a program which will give her the right answers.

   
Task
----

 Write a program which

- reads from standard input the number of apples the girls have together and how many more apples Klaudia has,
- counts the number of apples belonging to Klaudia and the number of apples belonging to Natalia,
- writes the outcome to standard output

## 输入格式

 Ten test cases (given one under another, you have to process all!). Every test case consists of two lines. The first line says how many apples both girls have together. The second line says how many more apples Klaudia has. Both numbers are positive integers. It is known that both girls have no more than 10 $ ^{100} $ (1 and 100 zeros) apples together. As you can see apples can be very small.

## 输出格式

For every test case your program should output two lines. The first line should contain the number of apples belonging to Klaudia. The second line should contain the number of apples belonging to Natalia.

## 样例 #1

### 输入

```
10

2

[and 9 test cases more]
```

### 输出

```
6

4

[and 9 test cases more]
```



---

