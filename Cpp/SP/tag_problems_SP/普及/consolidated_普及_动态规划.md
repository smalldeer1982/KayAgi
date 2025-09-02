---
title: "DCEPC11J - Jailbreak"
layout: "post"
diff: 普及/提高-
pid: SP16212
tag: ['动态规划 DP']
---

# DCEPC11J - Jailbreak

## 题目描述

The great King Kapish has prisoned Pushap, for he loves the princess Padmavati. To make sure that Pushap and Padmavati never meet again, King Kapish has kept Pushap in his most mysterious of jail.

This jail is built in a 2D rectangular grid fashion, containing M\*N prison cells. The entrance gate for jail is at bottom left corner (0,0). The mysteriousness of this jail comes from the fact that once a prisoner is taken from entrance gate (0,0) to any prison cell, then that prisoner can escape only if he comes back to the entrance visiting the cells used on his way from entrance to his prison cell. Note that in the escape, it is not required for the prisoner to trace the exact path or visit all the cells used on his way up, rather the condition is to use/visit only those prison cells used on his way up. Additionally, when the prisoner is taken from entrance (0,0) to a prison cell, they can fathom upto 2 cells in a single move/step in either upward direction or right direction. And when the prisoner is escaping, he can fathom upto 2 cells in a single move/step in either downward or left direction.

King Kapish orders to jail prisoner Pushap in cell (M-1,N-1).

You, being a common friend to Pushap and Padmavati, have to help Pushap escape the prison. **Tell him the number of ways in which he can go up to cell (M-1,N-1) and then come back following the procedure described above. Please refer explanation part to know more.**

## 输入格式

First line contains T, the number of test cases.

Each test case contains 2 space separated integers, M and N.

## 输出格式

Output exactly T lines, each containing the required answer modulo 10^9 + 7.

## 说明/提示

**【样例解释】**

对于第二组数据，一种可能的路径如下：

$(0,0) \to (0,1) \to (0,2) \to (1,2) \to (0,2) \to (0,0)$。

## 样例 #1

### 输入

```
3
2 2
2 3
3 4

```

### 输出

```
2
7
66

```



---

---
title: "SCUBADIV - Scuba diver"
layout: "post"
diff: 普及/提高-
pid: SP181
tag: ['动态规划 DP', '背包 DP']
---

# SCUBADIV - Scuba diver

## 题目描述

A scuba diver uses a special equipment for diving. He has a cylinder with two containers: one with oxygen and the other with nitrogen. Depending on the time he wants to stay under water and the depth of diving the scuba diver needs various amount of oxygen and nitrogen. The scuba diver has at his disposal a certain number of cylinders. Each cylinder can be described by its weight and the volume of gas it contains. In order to complete his task the scuba diver needs specific amount of oxygen and nitrogen. What is the minimal total weight of cylinders he has to take to complete the task?

## 输入格式

The number of test cases _c_ is in the first line of input, then _c_ test cases follow separated by an empty line.

In the first line of a test case there are two integers _t_, _a_ separated by a single space, 1 <= _t_ <= 21 and 1 <= _a_ <= 79. They denote volumes of oxygen and nitrogen respectively, needed to complete the task. The second line contains one integer _n_, 1 <= _n_ <= 1000, which is the number of accessible cylinders. The following _n_ lines contain descriptions of cylinders; _i_-th line contains three integers _t_ _$ _{i} $_ , _a_ _$ _{i} $_ , _w_ _$ _{i} $_  separated by single spaces, (1 <= _t_ _$ _{i} $_  <= 21, 1 <= _a_ _$ _{i} $_  <= 79, 1 <= _w_ _$ _{i} $_  <= 800). These are respectively: volume of oxygen and nitrogen in the _i_-th cylinder and the weight of this cylinder.

## 输出格式

For each test case your program should output one line with the minimal total weight of cylinders the scuba diver should take to complete the task.

## 样例 #1

### 输入

```
1
5 60
5
3 36 120
10 25 129
5 50 250
1 45 130
4 20 119

```

### 输出

```
249

```



---

---
title: "ARRPRM - Prime is fun"
layout: "post"
diff: 普及/提高-
pid: SP30394
tag: ['动态规划 DP', '素数判断,质数,筛法', '前缀和']
---

# ARRPRM - Prime is fun

## 题目描述

给定一个长为 $n$ 的序列 $a$，从 $a$ 中选出若干个互不相连的长度均为质数的连续段，使这些连续段中的数的和最大。

## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

第一行，一个整数 $n$；

第二行，$n$ 个整数 $a_1, a_2, \cdots, a_n$。

## 输出格式

对于每组数据：

一行，一个整数，表示所求的值。
### 输入输出样例
#### 输入 #1
```
2
4
1 2 3 4
10
10 1 1 1 1 1 1 2 2 2
```
#### 输出 #1
```
9
21
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T \leq 100$，$1 \leq n \leq 2 \times 10^3$，$1 \leq a_i \leq 10^6$。



---

---
title: "BOOKS1 - Copying Books"
layout: "post"
diff: 普及/提高-
pid: SP43
tag: ['动态规划 DP', '贪心', '进制']
---

# BOOKS1 - Copying Books

## 样例 #1

### 输入

```
2

9 3

100 200 300 400 500 600 700 800 900

5 4

100 100 100 100 100
```

### 输出

```
100 200 300 400 500 / 600 700 / 800 900

100 / 100 / 100 / 100 100
```



---

---
title: "EDIST - Edit distance"
layout: "post"
diff: 普及/提高-
pid: SP6219
tag: ['动态规划 DP']
---

# EDIST - Edit distance

## 题目描述

给定两个字符串 $A$ 和 $B$。回答将 $A$ 转换为 $B$ 需要的最少操作次数是多少？

操作包括：

1. 从一个字符串中删除一个字母
2. 向一个字符串中插入一个字母
3. 将一个字符串中的一个字母替换为另一个字母

## 输入格式

$T$ - 测试用例的数量。

对于每个测试用例：

- 字符串 $A$
- 字符串 $B$

两个字符串只包含大写字符，且长度不超过 $2000$ 个字符。

数据集中有 $10$ 个测试用例。

## 输出格式

对于每个测试用例，输出一行，表示最少操作次数。

---

Translated by User 735713.

## 样例 #1

### 输入

```
1

FOOD

MONEY
```

### 输出

```
4
```



---

