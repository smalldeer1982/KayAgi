---
title: "MONODIG - Monodigital Representations"
layout: "post"
diff: 难度0
pid: SP200
tag: []
---

# MONODIG - Monodigital Representations

## 题目描述

给定一个十进制数字 $K$，且 $K$ 不为 $0$。我们定义一个算术表达式为整数 $X$ 的 **$K$-表示**，如果这个表达式的值是 $X$，并且仅包含由数字 $K$ 组成的数。（所有数都为十进制）。表达式中可以使用的算术运算包括加法、减法、乘法和除法。也允许使用圆括号。只有当被除数整除除数时，才允许出现除法运算。

## 输入格式

第一行是测试用例的数量 $t$。接下来的 $t$ 个测试用例中，每个用例之间用空行分隔。每个测试用例的第一行包含一个数字 $K$，其中 $K$ 为 $\{1, \ldots, 9\}$ 中的一个。第二行是一个数字 $n$，满足 $1 \le n \le 10$。接下来的 $n$ 行，每行包含一个自然数 $a_1, \ldots, a_n$，其中 $1 \le a_i \le 32000$（对于 $i = 1, \ldots, n$），每行一个数。

## 输出格式

对于每个测试用例，输出 $n$ 行。第 $i$ 行应包含：

- 如果存在一个长度不超过 8 的 $K$-表示，则返回代表 $a_i$ 的最小长度的该种表示法；
- 如果 $a_i$ 的最小长度的 $K$-表示超过 8，则输出 `NO`。

## 说明/提示

测试用例个数满足 $1 \le t \le 10$，$K$ 为 $1$ 到 $9$ 之间的整数。每个测试用例包含 $n$ 个数，其中 $1 \le n \le 10$，且每个数满足 $1 \le a_i \le 32000$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
The number of test cases t is in the first line of input, then t test cases follow separated by an empty line.
The first line of each test case contains digit K,  K is en element of
{1,...,9}. The second line
contains number n,  1&lt;=n&lt;=10. In the following  n lines there is the series  of natural numbers
 a1,...,an,  
1&lt;=ai&lt;=32000 (for i=1,..,n), one number in each line. 
```

### 输出

```
The output for each test case composes of  n lines. The i-th line should
contain: 


 exactly one number which is the minimal length of K-representation of ai,
  assuming that such a representation of length not grater then 8 exists,
 one word NO, if the minimal length of the K-representation of the number
   ai
  is grater than 8. 


Example

Sample input:
1
5
2
12
31168

Sample output
4
NO
```

## 样例 #2

### 输入

```
1
5
2
12
31168
```

### 输出

```
None
```

