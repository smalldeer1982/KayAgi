---
title: "Palindromic Matrix"
layout: "post"
diff: 普及+/提高
pid: CF1118C
tag: []
---

# Palindromic Matrix

## 题目描述

Let's call some square matrix with integer values in its cells palindromic if it doesn't change after the order of rows is reversed and it doesn't change after the order of columns is reversed.

For example, the following matrices are palindromic:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/1dd62ecf9cdea049a4333ac1caa6ce864c1d5fc5.png)The following matrices are not palindromic because they change after the order of rows is reversed:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/2143b8b786a0f045139a90d99c3f905c3e226fac.png)The following matrices are not palindromic because they change after the order of columns is reversed:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/fe33a9bda586416fffd510345806131041ef4caa.png)You are given $ n^2 $ integers. Put them into a matrix of $ n $ rows and $ n $ columns so that each number is used exactly once, each cell contains exactly one number and the resulting matrix is palindromic. If there are multiple answers, print any. If there is no solution, print "NO".

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 20 $ ).

The second line contains $ n^2 $ integers $ a_1, a_2, \dots, a_{n^2} $ ( $ 1 \le a_i \le 1000 $ ) — the numbers to put into a matrix of $ n $ rows and $ n $ columns.

## 输出格式

If it is possible to put all of the $ n^2 $ numbers into a matrix of $ n $ rows and $ n $ columns so that each number is used exactly once, each cell contains exactly one number and the resulting matrix is palindromic, then print "YES". Then print $ n $ lines with $ n $ space-separated numbers — the resulting matrix.

If it's impossible to construct any matrix, then print "NO".

You can print each letter in any case (upper or lower). For example, "YeS", "no" and "yES" are all acceptable.

## 说明/提示

Note that there exist multiple answers for the first two examples.

## 样例 #1

### 输入

```
4
1 8 8 1 2 2 2 2 2 2 2 2 1 8 8 1

```

### 输出

```
YES
1 2 2 1
8 2 2 8
8 2 2 8
1 2 2 1

```

## 样例 #2

### 输入

```
3
1 1 1 1 1 3 3 3 3

```

### 输出

```
YES
1 3 1
3 1 3
1 3 1

```

## 样例 #3

### 输入

```
4
1 2 1 9 8 4 3 8 8 3 4 8 9 2 1 1

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
1
10

```

### 输出

```
YES
10 

```

