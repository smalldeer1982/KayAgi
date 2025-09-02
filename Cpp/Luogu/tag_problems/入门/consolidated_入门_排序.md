---
title: "谁考了第 k 名"
layout: "post"
diff: 入门
pid: B2158
tag: ['排序', '结构体']
---
# 谁考了第 k 名
## 题目描述

在一次考试中，每个学生的成绩都不相同，现知道了每个学生的学号和成绩，求考第 $k$ 名学生的学号和成绩。
## 输入格式

第一行有两个整数，分别是学生的人数 $n(1\le n\le100)$ 和求第 $k$ 名学生的 $k(1\le k\le n)$。

其后有 $n$ 行数据，每行包括一个学号（整数）和一个成绩（浮点数），中间用一个空格分隔。
## 输出格式

输出第 $k$ 名学生的学号和成绩，中间用空格分隔。（注：请用 `%g` 输出成绩）
## 样例

### 样例输入 #1
```
5 3
90788001 67.8
90788002 90.3
90788003 61
90788004 68.4
90788005 73.9
```
### 样例输出 #1
```
90788004 68.4
```


---

---
title: "[蓝桥杯青少年组省赛 2022] 字母组合"
layout: "post"
diff: 入门
pid: B4289
tag: ['2022', '排序', '蓝桥杯青少年组']
---
# [蓝桥杯青少年组省赛 2022] 字母组合
## 题目描述

给定 $N$ 个小写字母，然后将这 $N$ 个小写字母按照字典序排序后组合成一个字符串输出。

例如 $N=4$，$4$ 个小写字母分别为 $\tt c$、$\tt d$、$\tt a$、$\tt c$，按照字典序排序后组合成的字符串为：$\tt{accd}$。
## 输入格式

第一行输入一个正整数 $N$（$2 < N < 100$），表示小写字母的个数。

第二行输入 $N$ 个小写字母，且小写字母之间以一个空格隔开。
## 输出格式

将 $N$ 个小写字母按照字典序排序后组成一个字符串并输出。
## 样例

### 样例输入 #1
```
4
c d a c
```
### 样例输出 #1
```
accd
```


---

---
title: "[JOIG 2024] ダンス / Dance"
layout: "post"
diff: 入门
pid: P11199
tag: ['贪心', '2024', 'O2优化', '排序', 'JOI（日本）']
---
# [JOIG 2024] ダンス / Dance
## 题目描述

一所中学的一个班级有 $2N$ 名学生，第 $i(1\le i\le 2N)$ 名学生的身高是 $A_i$。

在即将开始的体育课上，学生们将两两配对，形成 $N$ 组进行舞蹈。

要跳出优美的舞蹈，每一对舞伴之间的身高差必须小于或等于 $D$。

给定每个学生的身高，确定能否跳出优美的舞蹈。
## 输入格式

第一行输入两个整数 $N,D$。

第二行输入 $2N$ 个整数 $A_1,A_2,\ldots,A_{2N}$。
## 输出格式

输出一行一个字符串，如果可以跳出优美的舞蹈输出 `Yes`，否则输出 `No`。
## 样例

### 样例输入 #1
```
1 5
2 7
```
### 样例输出 #1
```
Yes
```
### 样例输入 #2
```
3 0
10 10 10 11 10 10
```
### 样例输出 #2
```
No
```
### 样例输入 #3
```
6 4
22 15 32 36 16 30 42 30 39 23 17 18
```
### 样例输出 #3
```
Yes
```
## 提示

#### 【样例解释 #1】

只有一种配对方案，满足 $|2-7|\le 5$，符合条件。

该样例满足子任务 $1,3$ 的限制。

#### 【样例解释 #2】

无论如何都没法进行配对，使得任意一对舞伴的身高差 $\le 0$。

该样例满足子任务 $2,3$ 的限制。

#### 【样例解释 #3】

考虑如下配对方案：

- 身高 $39$ 的学生和身高 $42$ 的学生配对；
- 身高 $22$ 的学生和身高 $23$ 的学生配对；
- 身高 $16$ 的学生和身高 $17$ 的学生配对；
- 身高 $32$ 的学生和身高 $36$ 的学生配对；
- 身高 $15$ 的学生和身高 $18$ 的学生配对；
- 身高 $30$ 的学生和身高 $30$ 的学生配对。

符合条件。

该样例满足子任务 $3$ 的限制。

#### 【数据范围】

- $1\le N\le 100$；
- $0\le D\le 100$；
- $1\le A_i\le 100(1\le i\le 2N)$。

#### 【子任务】

1. （$20$ 分）$N=1$；
2. （$40$ 分）$D=0$；
3. （$40$ 分）无附加限制。


---

---
title: "欢乐的跳"
layout: "post"
diff: 入门
pid: P1152
tag: ['模拟', '枚举', '排序']
---
# 欢乐的跳
## 题目描述

一个 $n$ 个元素的整数数组，如果数组两个连续元素之间差的绝对值包括了 $[1,n-1]$ 之间的所有整数，则称之符合“欢乐的跳”，如数组 $\{1,4,2,3\}$ 符合“欢乐的跳”，因为差的绝对值分别为：$3,2,1$。

给定一个数组，你的任务是判断该数组是否符合“欢乐的跳”。

## 输入格式

每组测试数据第一行以一个整数 $n(1 \le n \le 1000)$ 开始，接下来 $n$ 个空格隔开的在 $[-10^8,10^8]$ 之间的整数。

## 输出格式

对于每组测试数据，输出一行若该数组符合“欢乐的跳”则输出 `Jolly`，否则输出 `Not jolly`。

## 样例

### 样例输入 #1
```
4 1 4 2 3

```
### 样例输出 #1
```
Jolly

```
### 样例输入 #2
```
5 1 4 2 -1 6
```
### 样例输出 #2
```
Not jolly
```
## 提示

$1 \le n \le 1000$



---

---
title: "[科大国创杯初中组 2023] 评分"
layout: "post"
diff: 入门
pid: P11950
tag: ['模拟', '2023', '安徽', '排序', '科大国创杯']
---
# [科大国创杯初中组 2023] 评分
## 题目描述

小可可在观看跳水比赛。

有 $n$ 名选手来参加跳水比赛，有 $m$ 名评委。在每位选手跳水之后，每位评委会给出他的分数。为了保证尽量公正客观，每位选手的得分是所有评委给出的分数中去掉最大值和最小值（如果有多个最大值/最小值，只去掉一个）之后，剩下的分数的平均值。

最后得分最大的选手获得第一名，得分第二大的选手获得第二名，以此类推。但是可能会出现同分的情况，在这种情况下，小可可会默认编号较小的选手排名更靠前。即，如果 $3$ 号选手和 $5$ 号选手的得分都是 $70$，那么小可可会认为 $3$ 号选手的排名比 $5$ 号选手更靠前。

现在小可可已经知道了所有选手得到所有评委的分数，他想让你帮他算出来选手的排名表，即对于 $1 \leq i \leq n$，算出排名第 $i$ 的选手的编号是什么。
## 输入格式

第一行两个整数 $n, m$，分别表示选手个数和评委个数。

接下来 $n$ 行每行 $m$ 个整数，第 $i$ 行第 $j$ 个整数 $a_{i,j}$ 表示在第 $i$ 个选手跳水之后，第 $j$ 个评委给出的分数。
## 输出格式

输出一行 $n$ 个整数，第 $i$ 个整数表示排名为 $i$ 的选手的编号。
## 样例

### 样例输入 #1
```
4 4
4 70 69 34
18 43 85 71
100 50 69 80
67 82 90 43
```
### 样例输出 #1
```
3 4 2 1
```
## 提示

### 样例 1 解释

四位选手的去掉最大、最小值之后的平均分分别是：$51.5, 57, 74.5, 74.5$，但由于三号选手编号比四号选手小，所以排名从 $1$ 到 $4$ 的选手分别为：$3, 4, 2, 1$。

### 数据规模与约定

对于 $30\%$ 的数据，满足 $n, m \leq 3$；

对于 $60\%$ 的数据，满足 $n, m \leq 10$；

对于 $100\%$ 的数据，满足 $2 \leq n \leq 100$，$3 \leq m \leq 100$，$0 \leq a_{i,j} \leq 100$。


---

---
title: "[蓝桥杯 2022 省 Python B] 排列字母"
layout: "post"
diff: 入门
pid: P12363
tag: ['2022', '排序', '蓝桥杯省赛']
---
# [蓝桥杯 2022 省 Python B] 排列字母
## 题目描述

小蓝要把一个字符串中的字母按其在字母表中的顺序排列。

例如，$\tt{LANQIAO}$ 排列后为 $\tt{AAILNOQ}$。

又如，$\tt{GOODGOODSTUDYDAYDAYUP}$ 排列后为 $\tt{AADDDDDGGOOOOPSTUUYYY}$。

请问对于以下字符串，排列之后字符串是什么？

$$\tt{WHERETHEREISAWILLTHEREISAWAY}$$
## 输出格式

这是一道结果填空的题，你只需要算出结果后提交即可。本题的结果为一个字符串，在提交答案时只需要**编写一个程序输出这个字符串**，输出多余的内容将无法得分。


---

---
title: "[NERC 2020 Online] Kate' s 2021 Celebration"
layout: "post"
diff: 入门
pid: P12860
tag: ['模拟', '2020', 'Special Judge', 'O2优化', '排序', 'ICPC', 'NERC/NEERC', 'STL']
---
# [NERC 2020 Online] Kate' s 2021 Celebration
## 题目描述

Kate did not have a good year 2020 and she is glad that it is coming to an end. She is planning to celebrate New Year 2021 on a grand scale. 

Kate has decided to buy four balloons with digits $\texttt{2} \texttt{0} \texttt{2} \texttt{1}$ painted on them for her 2021 celebration. She went to a store's web site and has found that balloons with digits are sold in packs containing different assortments of balloons of various sizes, colors, and with different digits painted on them. Kate does not care about their size, color, or other attributes. She only cares about digits written on those balloons. Fortunately, the store has all the information about different packs of balloons that are available. Kate has managed to retrieve it through the store's REST API and extracted just the information she needs --- the price and the digits that are written on balloons in each pack. 

Please, help Kate with the final task of figuring out what is the cheapest pack of balloons she can buy that would get her the four digits she needs for her 2021 celebration.
## 输入格式

The first line of the input file contains an integer $n$ ($1 \le n \le 1000$) --- the number of packs of balloons available in the store.  

The next $n$ lines contain descriptions of packs, one line per pack. Each pack is described by an integer $p$ ($1 \le p \le 10^5$) --- the price of the pack in roubles, followed by a string of at least one and at most $100$ digits (each digit is from $\texttt{0}$to $\texttt{9}$) --- the digits on the balloons in the pack.
## 输出格式

Output a single integer --- the number of the cheapest pack that Kate can buy to get the digits for her $2021$ celebration. Packs of balloons are numbered starting from $1$ in the order they are given in the input. If there are multiple packs with the same price, output any one of them.

Output $0$ if there is no pack in the store that Kate can buy for her 2021 celebration.
## 样例

### 样例输入 #1
```
4
100 9876543210
200 00112233445566778899
160 012345678924568
150 000000123456789
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5
100 0123456789
120 0022446688
200 00224466883456789
10 0
10 1
```
### 样例输出 #2
```
0
```
## 提示

In the first example, 2nd and 3rd packs of balloons contain digits $\texttt{2} \texttt{0} \texttt{2} \texttt{1}$ and the 3rd one is the cheapest.


---

---
title: "三角函数"
layout: "post"
diff: 入门
pid: P1888
tag: ['数学', '排序', '最大公约数 gcd']
---
# 三角函数
## 题目描述

输入一组勾股数 $a,b,c（a\neq b\neq c）$，用分数格式输出其较小锐角的正弦值。（要求约分。）

## 输入格式

一行，包含三个正整数，即勾股数 $a,b,c$（无大小顺序）。

## 输出格式

一行，包含一个分数，即较小锐角的正弦值

## 样例

### 样例输入 #1
```
3 5 4
```
### 样例输出 #1
```
3/5
```
## 提示

数据保证：$a,b,c$ 为正整数且 $\in [1,10^9]$。


---

---
title: "[USACO07DEC] Bookshelf B"
layout: "post"
diff: 入门
pid: P2676
tag: ['贪心', '2007', 'USACO', '排序']
---
# [USACO07DEC] Bookshelf B
## 题目描述

Farmer John 最近为奶牛们的图书馆添置了一个巨大的书架，尽管它是如此的大，但它还是几乎瞬间就被各种各样的书塞满了。现在，只有书架的顶上还留有一点空间。 

所有 $N(1 \le N \le 20,000)$ 头奶牛都有一个确定的身高 $H_i(1 \le H_i \le 10,000)$。设所有奶牛身高的和为S。书架的高度为 $B$，并且保证 $1 \le B \le S < 2,000,000,007$。 

为了够到比最高的那头奶牛还要高的书架顶，奶牛们不得不像演杂技一般，一头站在另一头的背上，叠成一座“奶牛塔”。当然，这个塔的高度，就是塔中所有奶牛的身高之和。为了往书架顶上放东西，所有奶牛的身高和必须不小于书架的高度。

显然，塔中的奶牛数目越多，整座塔就越不稳定，于是奶牛们希望在能够到书架顶的前提下，让塔中奶牛的数目尽量少。 现在，奶牛们找到了你，希望你帮她们计算这个最小的数目。

## 输入格式

* 第 $1$ 行: 2 个用空格隔开的整数：$N$ 和 $B$；
* 第 $2\dots N+1$ 行: 第 $i+1$ 行是 $1$ 个整数：$H_i$。

## 输出格式

* 第 $1$ 行: 输出 $1$ 个整数，即最少要多少头奶牛叠成塔，才能够到书架顶部

## 样例

### 样例输入 #1
```
6 40
6
18
11
13
19
11
```
### 样例输出 #1
```
3
```
## 提示

输入说明:

一共有 $6$ 头奶牛，书架的高度为 $40$，奶牛们的身高在 $6\dots19$之间。


输出说明:

一种只用 $3$ 头奶牛就达到高度 $40$ 的方法：$18+11+13$。当然还有其他方法，在此不一一列出了。



---

---
title: "[COCI 2006/2007 #1] Modulo"
layout: "post"
diff: 入门
pid: P4325
tag: ['2006', '枚举', '排序', 'COCI（克罗地亚）']
---
# [COCI 2006/2007 #1] Modulo
## 题目描述

Given two integers A and B, A modulo B is the remainder when dividing A by B. For example, the numbers 7, 14, 27 and 38 become 1, 2, 0 and 2, modulo 3. Write a program that accepts 10 numbers as input and outputs the number of distinct numbers in the input, if the numbers are considered modulo 42.
## 输入格式

The input will contain 10 non-negative integers, each smaller than 1000, one per line.
## 输出格式

Output the number of distinct values when considered modulo 42 on a single line.
## 样例

### 样例输入 #1
```
1
2
3
4
5
6
7
8
9
10
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
42
84
252
420
840
126
42
84
420
126
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
39
40
41
42
43
44
82
83
84
85
```
### 样例输出 #3
```
6
```
## 提示

In the first example, the numbers modulo 42 are 1, 2, 3, 4, 5, 6, 7, 8, 9 and 10.
In the second example all numbers modulo 42 are 0.
In the third example, the numbers modulo 42 are 39, 40, 41, 0, 1, 2, 40, 41, 0 and 1. There are 6 distinct numbers.
## 题目翻译

给出 $10$ 个整数，问这些整数除以 $42$ 后得到的余数有多少种。

- 第一个样例的十个结果是 $1,2,3,4,5,6,7,8,9,10$，有 $10$ 个不同的结果；
- 第二个样例结果都是 $0$，只有一个不同的结果；
- 第三个样例余数是 $39,40,41,0,1,2,40,41,0,1$，有 $0,1,2,39,40,41$ 这六个不同的结果。


---

---
title: "[COCI 2006/2007 #2] ABC"
layout: "post"
diff: 入门
pid: P4414
tag: ['模拟', '2006', '排序', 'COCI（克罗地亚）']
---
# [COCI 2006/2007 #2] ABC
## 题目描述

You will be given three integers A, B and C. The numbers will not be given in that exact order, but we do know that A is less than B and B less than C.
In order to make for a more pleasant viewing, we want to rearrange them in the given order.
## 输入格式

The first line contains three positive integers A, B and C, not necessarily in that order. All three numbers will be less than or equal to 100.
The second line contains three uppercase letters 'A', 'B' and 'C' (with no spaces between them) representing the desired order.
## 输出格式

Output the A, B and C in the desired order on a single line, separated by single spaces.
## 样例

### 样例输入 #1
```
1 5 3
ABC
```
### 样例输出 #1
```
1 3 5
```
### 样例输入 #2
```
6 4 2
CAB
```
### 样例输出 #2
```
6 2 4
```
## 题目翻译

**【题目描述】**

三个整数分别为 $A,B,C$。这三个数字不会按照这样的顺序给你，但它们始终满足条件：$A < B < C$。为了看起来更加简洁明了，我们希望你可以按照给定的顺序重新排列它们。

**【输入格式】**

第一行包含三个正整数 $A,B,C$，不一定是按这个顺序。这三个数字都小于或等于 $100$。第二行包含三个大写字母 $A$、$B$ 和 $C$（它们之间**没有**空格）表示所需的顺序。

**【输出格式】**

在一行中输出 $A$，$B$ 和 $C$，用一个 ` `（空格）隔开。

感谢 @smartzzh 提供的翻译


---

---
title: "[COCI 2011/2012 #2] NAJBOLJIH 5"
layout: "post"
diff: 入门
pid: P7614
tag: ['2011', '枚举', '排序', 'COCI（克罗地亚）']
---
# [COCI 2011/2012 #2] NAJBOLJIH 5
## 题目描述

给定 $8$ 个数字 $X_1,X_2,...,X_8$，从中选出 $5$ 个数字，使得这 $5$ 个数字的总和最大。输出这 $5$ 个数字的和以及它们的编号。$X_i$ 的编号为 $i$。
## 输入格式

输入共 $8$ 行，第 $i$ 行包含一个正整数 $X_i$。**保证所有 $X_i$ 互不相同**。
## 输出格式

输出共两行。

第一行包含一个整数，表示最大的总和。

第二行包含 $5$ 个整数，表示 $5$ 个数的编号，**按升序排序**。
## 样例

### 样例输入 #1
```
20
30
50
48
33
66
0
64
```
### 样例输出 #1
```
261
3 4 5 6 8
```
### 样例输入 #2
```
20
0
50
80
77
110
56
48
```
### 样例输出 #2
```
373
3 4 5 6 7
```
### 样例输入 #3
```
20
30
50
80
110
11
0
85
```
### 样例输出 #3
```
355
2 3 4 5 8
```
## 提示

#### 【数据范围】

对于 $100\%$ 的数据，$1 \le X_i \le 150$。

#### 【说明】

本题分值按 COCI 原题设置，满分 $50$。

题目译自 **[COCI2011-2012](https://hsin.hr/coci/archive/2011_2012/) [CONTEST #2](https://hsin.hr/coci/archive/2011_2012/contest2_tasks.pdf)** ___T1 NAJBOLJIH 5___。


---

