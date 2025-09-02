---
title: "Graph Coloring (hard version)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1792F2
tag: ['动态规划 DP', '图论', '组合数学', '快速数论变换 NTT']
---

# Graph Coloring (hard version)

## 题目描述

The only difference between the easy and the hard version is the constraint on $ n $ .

You are given an undirected complete graph on $ n $ vertices. A complete graph is a graph where each pair of vertices is connected by an edge. You have to paint the edges of the graph into two colors, red and blue (each edge will have one color).

A set of vertices $ S $ is red-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through red edges and vertices from $ S $ . Similarly, a set of vertices $ S $ is blue-connected if, for every pair of vertices $ (v_1, v_2) $ such that $ v_1 \in S $ and $ v_2 \in S $ , there exists a path from $ v_1 $ to $ v_2 $ that goes only through blue edges and vertices from $ S $ .

You have to paint the graph in such a way that:

- there is at least one red edge;
- there is at least one blue edge;
- for each set of vertices $ S $ such that $ |S| \ge 2 $ , $ S $ is either red-connected or blue-connected, but not both.

Calculate the number of ways to paint the graph, and print it modulo $ 998244353 $ .

## 输入格式

The first (and only) line contains one integer $ n $ ( $ 3 \le n \le 5 \cdot 10^4 $ ).

## 输出格式

Print one integer — the number of ways to paint the graph, taken modulo $ 998244353 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
```

### 输出

```
50
```

## 样例 #3

### 输入

```
100
```

### 输出

```
878752271
```

## 样例 #4

### 输入

```
1337
```

### 输出

```
520628749
```

## 样例 #5

### 输入

```
42013
```

### 输出

```
906821221
```



---

---
title: "Zimpha Fan Club"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1975G
tag: ['快速数论变换 NTT']
---

# Zimpha Fan Club

## 题目描述

One day, Zimpha casually came up with a problem. As a member of "Zimpha fan club", you decided to solve that problem.

You are given two strings $ s $ and $ t $ of length $ n $ and $ m $ , respectively. Both strings only consist of lowercase English letters, - and \*.

You need to replace all occurrences of \* and -, observing the following rules:

- For each -, you must replace it with any lowercase English letter.
- For each \*, you must replace it with a string of any (possibly, zero) length which only consists of lowercase English letters.

Note that you can replace two different instances of - with different characters. You can also replace each two different instances of \* with different strings.

Suppose $ s $ and $ t $ have been transformed into $ s' $ and $ t' $ . Now you're wondering if there's a replacement that makes $ s'=t' $ .

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1 \leq n, m \leq 2 \cdot 10^6 $ ) — the length of the strings $ s $ and $ t $ , respectively.

The second line contains the string $ s $ of length $ n $ . It is guaranteed that $ s $ only consists of lowercase English letters, - and \*.

The third line contains the string $ t $ of length $ m $ . It is guaranteed that $ t $ only consists of lowercase English letters, - and \*.

## 输出格式

For each test case, output "Yes" if there is a replacement that makes $ s'=t' $ , and output "No" otherwise.

You can output "Yes" and "No" in any case (for example, strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive response).

## 说明/提示

In the second test case, we can transform both strings into ttklwxx. In $ s $ , - will be replaced with l. In $ t $ , \* will be replaced by the empty string with the first and second - will be replaced with k and w respectively.

In the fifth test case, we can transform both strings into bulijiojioxdibuliduo.

## 样例 #1

### 输入

```
10 10
justmonika
j-stsayori
```

### 输出

```
No
```

## 样例 #2

### 输入

```
7 8
ttk-wxx
*tt-l-xx
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
13 11
asoulwangziji
-soulg*z-y-
```

### 输出

```
No
```

## 样例 #4

### 输入

```
7 3
abc*cba
a*c
```

### 输出

```
No
```

## 样例 #5

### 输入

```
20 18
bulijiojio-dibuliduo
*li*ji-*ox*i*-du*-
```

### 输出

```
Yes
```



---

