---
title: "PAINTTMP - Paint templates"
layout: "post"
diff: 难度0
pid: SP174
tag: []
---

# PAINTTMP - Paint templates

## 题目描述

画室正在准备大量生产画作，采用的是不同大小的方阵。一个大小为 $i$ 的方阵有 $2^i$ 行和 $2^i$ 列。在某些行和列的交点上会有孔洞。对于大小为 0 的方阵，就是一个含有一个孔洞的点阵。而对于 $i > 0$，大小为 $i$ 的方阵由四个 $2^{(i-1)} \times 2^{(i-1)}$ 的小方阵组成。请参考下图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP174/104973dafa2ff5ffca869a0fb29e8194ed4634f6.png)

右侧的两个小方阵和左下角的小方阵都是大小为 $i-1$ 的矩阵，而左上角的小方阵没有孔洞。画作的制作过程如下：我们先固定三个非负整数 $n$、$x$ 和 $y$。然后，选两个大小为 $n$ 的方阵，将其中一个放在另一个之上，并将上面的方阵向右移动 $x$ 列，向上移动 $y$ 行。将这种排列放在白色画布上，并用黄色颜料涂抹两个方阵重叠部分的孔洞。如此一来，我们在画布上得到黄色斑点，这些斑点正好是两个方阵孔洞重合的位置。

## 输入格式

第一行为测试用例的数量 $t$，接下来是 $t$ 个测试用例，每个测试用例之间空一行。

每个测试用例的第一行是一个整数 $n$，满足 $0 \le n \le 100$，表示画作中使用的方阵的大小。接下来的第二行包含一个整数 $x$，第三行包含一个整数 $y$，满足 $0 \le x, y \le 2^n$。整数 $x$ 是上方方阵向右移动的列数，$y$ 是向上移动的行数。

## 输出格式

对每个测试用例，程序应该输出一行，包含一个整数，即画布上黄色斑点的数量。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
The number of test cases t is in the first line of input, then t test cases follow separated by an empty line
There is one integer n, 0 &lt;= n &lt;= 100 in the first line of each test case. This number is the size of matrices used for production of paintings. In the second line there is one integer x and in the third line one integer y, where 0 &lt;= x,y &lt;= 2n. The integer x is the number of columns and y is the number of rows that the upper matrix should be shifted by.
```

### 输出

```
For each test case your program should produce one line with exactly one integer - the number of stains on the canvas.

Example
Sample input:
1
2
2
2

Sample output:
3
```

## 样例 #2

### 输入

```
1
2
2
2
```

### 输出

```
None
```

