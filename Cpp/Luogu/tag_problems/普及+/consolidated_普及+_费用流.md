---
title: "[NOIP 2000 提高组] 方格取数"
layout: "post"
diff: 普及+/提高
pid: P1004
tag: ['动态规划 DP', '2000', '递归', 'NOIP 提高组', '费用流']
---
# [NOIP 2000 提高组] 方格取数
## 题目背景

NOIP 2000 提高组 T4
## 题目描述

设有 $N \times N$ 的方格图 $(N \le 9)$，我们将其中的某些方格中填入正整数，而其他的方格中则放入数字 $0$。如下图所示（见样例）:

![](https://cdn.luogu.com.cn/upload/image_hosting/0bpummja.png)

某人从图的左上角的 $A$ 点出发，可以向下行走，也可以向右走，直到到达右下角的 $B$ 点。在走过的路上，他可以取走方格中的数（取走后的方格中将变为数字 $0$）。  
此人从 $A$ 点到 $B$ 点共走两次，试找出 $2$ 条这样的路径，使得取得的数之和为最大。

## 输入格式

输入的第一行为一个整数 $N$（表示 $N \times N$ 的方格图），接下来的每行有三个整数，前两个表示位置，第三个数为该位置上所放的数。一行单独的 $0$ 表示输入结束。

## 输出格式

只需输出一个整数，表示 $2$ 条路径上取得的最大的和。

## 样例

### 样例输入 #1
```
8
2 3 13
2 6  6
3 5  7
4 4 14
5 2 21
5 6  4
6 3 15
7 2 14
0 0  0

```
### 样例输出 #1
```
67
```
## 提示

数据范围：$1\le N\le 9$。


---

---
title: "[NOIP 2008 提高组] 传纸条"
layout: "post"
diff: 普及+/提高
pid: P1006
tag: ['动态规划 DP', '2008', 'NOIP 提高组', '费用流']
---
# [NOIP 2008 提高组] 传纸条
## 题目描述

小渊和小轩是好朋友也是同班同学，他们在一起总有谈不完的话题。一次素质拓展活动中，班上同学安排坐成一个 $m$ 行 $n$ 列的矩阵，而小渊和小轩被安排在矩阵对角线的两端，因此，他们就无法直接交谈了。幸运的是，他们可以通过传纸条来进行交流。纸条要经由许多同学传到对方手里，小渊坐在矩阵的左上角，坐标 $(1,1)$，小轩坐在矩阵的右下角，坐标 $(m,n)$。从小渊传到小轩的纸条只可以向下或者向右传递，从小轩传给小渊的纸条只可以向上或者向左传递。

在活动进行中，小渊希望给小轩传递一张纸条，同时希望小轩给他回复。班里每个同学都可以帮他们传递，但只会帮他们一次，也就是说如果此人在小渊递给小轩纸条的时候帮忙，那么在小轩递给小渊的时候就不会再帮忙。反之亦然。

还有一件事情需要注意，全班每个同学愿意帮忙的好感度有高有低（注意：小渊和小轩的好心程度没有定义，输入时用 $0$ 表示），可以用一个 $[0,100]$ 内的自然数来表示，数越大表示越好心。小渊和小轩希望尽可能找好心程度高的同学来帮忙传纸条，即找到来回两条传递路径，使得这两条路径上同学的好心程度之和最大。现在，请你帮助小渊和小轩找到这样的两条路径。

## 输入格式

第一行有两个用空格隔开的整数 $m$ 和 $n$，表示班里有 $m$ 行 $n$ 列。

接下来的 $m$ 行是一个 $m \times n$ 的矩阵，矩阵中第 $i$ 行 $j$ 列的整数表示坐在第 $i$ 行 $j$ 列的学生的好心程度。每行的 $n$ 个整数之间用空格隔开。

## 输出格式

输出文件共一行一个整数，表示来回两条路上参与传递纸条的学生的好心程度之和的最大值。

## 样例

### 样例输入 #1
```
3 3
0 3 9
2 8 5
5 7 0

```
### 样例输出 #1
```
34
```
## 提示

**【数据范围】**

对于 $30\%$ 的数据，满足 $1 \le m,n \le 10$。  
对于 $100\%$ 的数据，满足 $1 \le m,n \le 50$。

**【题目来源】**

NOIP 2008 提高组第三题。


---

---
title: "负载平衡问题"
layout: "post"
diff: 普及+/提高
pid: P4016
tag: ['数学', '贪心', '网络流', 'O2优化', '费用流', '网络流与线性规划 24 题']
---
# 负载平衡问题
## 题目描述

$G$ 公司有 $n$ 个沿铁路运输线环形排列的仓库，每个仓库存储的货物数量不等。如何用最少搬运量可以使 $n$ 个仓库的库存数量相同。搬运货物时，只能在相邻的仓库之间搬运。

## 输入格式

第一行一个正整数 $n$，表示有 $n$ 个仓库。

第二行 $n$ 个正整数，表示 $n$ 个仓库的库存量。

## 输出格式

输出最少搬运量。

## 样例

### 样例输入 #1
```
5
17 9 14 16 4
```
### 样例输出 #1
```
11
```
## 提示

$1 \leq n \leq 100$。



---

---
title: "[COCI 2006/2007 #1] Bond"
layout: "post"
diff: 普及+/提高
pid: P4329
tag: ['搜索', '2006', 'Special Judge', '图论建模', '二分图', '费用流', 'COCI（克罗地亚）', '状压 DP']
---
# [COCI 2006/2007 #1] Bond
## 题目描述

Everyone knows of the secret agent double-oh-seven, the popular Bond (James Bond). A lesser known fact is that he actually did not perform most of his missions by himself; they were instead done by his cousins, Jimmy Bonds. Bond (James Bond) has grown weary of having to distribute assign missions to Jimmy Bonds every time he gets new missions so he has asked you to help him out.
Every month Bond (James Bond) receives a list of missions. Using his detailed intelligence from past missions, for every mission and for every Jimmy Bond he calculates the probability of that particular mission being successfully completed by that particular Jimmy Bond. Your program should process that data and find the arrangement that will result in the greatest probability that all missions are completed successfully.
Note: the probability of all missions being completed successfully is equal to the product of the probabilities of the single missions being completed successfully.
## 输入格式

The first line will contain an integer N, the number of Jimmy Bonds and missions (1 ≤ N ≤ 20).
The following N lines will contain N integers between 0 and 100, inclusive. The j-th integer on the ith line is the probability that Jimmy Bond i would successfully complete mission j, given as a percentage.
## 输出格式

Output the maximum probability of Jimmy Bonds successfully completing all the missions, as a percentage.
## 样例

### 样例输入 #1
```
2
100 100
50 50
```
### 样例输出 #1
```
50.000000
```
### 样例输入 #2
```
2
0 50
50 0
```
### 样例输出 #2
```
25.00000
```
### 样例输入 #3
```
3
25 60 100
13 0 50
12 70 90
```
### 样例输出 #3
```
9.10000
```
## 提示

Clarification of the third example: If Jimmy bond 1 is assigned the 3rd mission, Jimmy Bond 2 the 1st mission and Jimmy Bond 3 the 2nd mission the probability is: 1.0 * 0.13 * 0.7 = 0.091 = 9.1%. All other arrangements give a smaller probability of success.
Note: Outputs within ±0.000001 of the official solution will be accepted.
## 题目翻译

有 $n$ 个人去执行 $n$ 个任务，每个人执行每个任务有不同的成功率，每个人只能执行一个任务，求所有任务都执行的总的成功率。

输入第一行，一个整数 $n$（$1\leq n\leq 20$），表示人数兼任务数。接下来 $n$ 行每行 $n$ 个数，第 $i$ 行第 $j$ 个数表示第 $i$ 个人去执行第 $j$ 个任务的成功率（这是一个百分数，在 $0$ 到 $100$ 间）。

输出最大的总成功率（这应也是一个百分数）


---

