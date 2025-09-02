---
title: "PRIME1 - Prime Generator"
layout: "post"
diff: 普及-
pid: SP2
tag: ['模拟', '枚举', '素数判断,质数,筛法']
---

# PRIME1 - Prime Generator

## 题目描述

 Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!

## 输入格式

 The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

## 输出格式

For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)**   
Information
-----------

 After cluster change, please consider [PRINT](http://www.spoj.com/problems/PRINT/) as a more challenging problem.

## 样例 #1

### 输入

```
2
1 10
3 5
```

### 输出

```
2
3
5
7

3
5
```



---

---
title: "VECTAR8 - Primal Fear"
layout: "post"
diff: 普及-
pid: SP27318
tag: ['素数判断,质数,筛法']
---

# VECTAR8 - Primal Fear

## 题目描述

Changu 和 Mangu 对质数感到害怕，但他们并不是害怕所有的质数。他们只畏惧一种特殊的质数：这种质数不含数字 0，并且无论去掉多少个前导数字，剩下的部分依然是质数。举个例子，他们会害怕 4632647，因为它不包含数字 0，而且它的每一个前导截断（632647、32647、2647、647、47 和 7）都是质数。

你的任务是，对于给定的数字 $N$，找出有多少个不大于 $N$ 且被 Changu 和 Mangu 害怕的质数。

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量。接下来有 $T$ 行，每行包含一个整数 $N$。

## 输出格式

对于每个测试用例，输出一行结果，表示不大于 $N$ 的 Changu 和 Mangu 害怕的质数的个数。

## 说明/提示

$1 \le T \le 100$

$1 \le N \le 10^6$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3

2

3

4
```

### 输出

```
1

2

2
```



---

---
title: "PRIMPERM - Prime Permutations"
layout: "post"
diff: 普及-
pid: SP8591
tag: ['深度优先搜索 DFS', '素数判断,质数,筛法']
---

# PRIMPERM - Prime Permutations

## 题目描述

$t$ 组数据，每组数据给定一个整数 $n$，求 $n$ 的排列中有多少个排列是质数。

## 输入格式

共 $t+1$ 行：

第一行为一个整数 $t$。

第 $2\sim t+1$ 行每行一个整数 $n$。

## 输出格式

共 $t$ 行，每行一个整数表示 $n$ 的排列中有多少个排列是质数。

## 说明/提示

$t<10^4$，$n<10^7$

## 样例 #1

### 输入

```
2

13

110
```

### 输出

```
2

1
```



---

