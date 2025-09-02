---
title: "GSS1 - Can you answer these queries I"
layout: "post"
diff: 提高+/省选-
pid: SP1043
tag: ['线段树', '分治', '前缀和']
---

# GSS1 - Can you answer these queries I

## 题目描述

You are given a sequence A\[1\], A\[2\], ..., A\[N\] . ( |A\[i\]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:   
 Query(x,y) = Max { a\[i\]+a\[i+1\]+...+a\[j\] ; x ≤ i ≤ j ≤ y }.   
 Given M queries, your program must output the results of these queries.

## 输入格式

- The first line of the input file contains the integer N.
- In the second line, N numbers follow.
- The third line contains the integer M.
- M lines follow, where line i contains 2 numbers xi and yi.

## 输出格式

 Your program should output the results of the M queries, one query per line.

## 样例 #1

### 输入

```
3 
-1 2 3
1
1 2
```

### 输出

```
2
```



---

---
title: "DCEPC14D - Finding GP"
layout: "post"
diff: 提高+/省选-
pid: SP23878
tag: ['根号分治']
---

# DCEPC14D - Finding GP

## 题目描述

There is an array A of n elements . You need to tell the number of subsets of size greater than 1 which can form geometric progressions having integral common ratios.

**Constraints:**

1<=N<=1\*10^4  
1<=A\[i\]<=1000000

## 输入格式

The first line contains a single integer denoting the number of integers in the array (N). The second line contains N space separated integers representing the elements of the array.

## 输出格式

The output should contain a single line with the answer to this problem MODULUS 1000000007 .

## 样例 #1

### 输入

```
7\n2 4 4 2 8 16 8
```

### 输出

```
\n\n41
```



---

---
title: "CLOSEST - Closest Triplet"
layout: "post"
diff: 提高+/省选-
pid: SP7209
tag: ['分治']
---

# CLOSEST - Closest Triplet

## 题目描述

### 题意
多组询问，每组询问给出二维平面上的 $n$ 个点，在这 $n$ 个点中选出3个点，使这3个点两两之间的距离的和最小，输出这个最小距离。

## 输入格式

对于每组数据，第一行一个整数 $n$，接下来的 $n$ 行，每行两个整数 $x , y$，表示这 $n$ 个点的坐标。

当输入的 $n$ 为 $-1$ 时，输入结束。

## 输出格式

对于每组数据，输出一行一个浮点数，表示最小距离和，保留三位小数。

## 说明/提示

$3 \le n \le 3000$

$1 \le x,y \le 10^6$

## 样例 #1

### 输入

```
\n4\n1 1\n4 1\n1 5\n1000 1000\n9\n100000 200000\n200000 200000\n150000 286603\n60000 140000\n240000 140000\n150000 340000\n1 340000\n300000 340000\n150000 87087\n-1\n\n
```

### 输出

```
12.000\n300000.796
```



---

