---
title: "Robot Queries"
layout: "post"
diff: 普及+/提高
pid: CF1902D
tag: []
---

# Robot Queries

## 题目描述

There is an infinite $ 2 $ -dimensional grid. Initially, a robot stands in the point $ (0, 0) $ . The robot can execute four commands:

- U — move from point $ (x, y) $ to $ (x, y + 1) $ ;
- D — move from point $ (x, y) $ to $ (x, y - 1) $ ;
- L — move from point $ (x, y) $ to $ (x - 1, y) $ ;
- R — move from point $ (x, y) $ to $ (x + 1, y) $ .

You are given a sequence of commands $ s $ of length $ n $ . Your task is to answer $ q $ independent queries: given four integers $ x $ , $ y $ , $ l $ and $ r $ ; determine whether the robot visits the point $ (x, y) $ , while executing a sequence $ s $ , but the substring from $ l $ to $ r $ is reversed (i. e. the robot performs commands in order $ s_1 s_2 s_3 \dots s_{l-1} s_r s_{r-1} s_{r-2} \dots s_l s_{r+1} s_{r+2} \dots s_n $ ).

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the length of the command sequence and the number of queries, respectively.

The second line contains a string $ s $ of length $ n $ , consisting of characters U, D, L and/or R.

Then $ q $ lines follow, the $ i $ -th of them contains four integers $ x_i $ , $ y_i $ , $ l_i $ and $ r_i $ ( $ -n \le x_i, y_i \le n $ ; $ 1 \le l \le r \le n $ ) describing the $ i $ -th query.

## 输出格式

For each query, print YES if the robot visits the point $ (x, y) $ , while executing a sequence $ s $ , but the substring from $ l $ to $ r $ is reversed; otherwise print NO.

## 说明/提示

In the first query of the first sample, the path of the robot looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1902D/4aac546138020132b74e07749db84bb06a513da8.png)In the second query of the first sample, the path of the robot looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1902D/b189da90dcd98cd79a3624a3015d7f2cf2e922e4.png)In the third query of the first sample, the path of the robot looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1902D/5220422eecc4ff8d70f683171d72758af4ccdbfe.png)

## 样例 #1

### 输入

```
8 3
RDLLUURU
-1 2 1 7
0 0 3 4
0 1 7 8
```

### 输出

```
YES
YES
NO
```

## 样例 #2

### 输入

```
4 2
RLDU
0 0 2 2
-1 -1 2 3
```

### 输出

```
YES
NO
```

## 样例 #3

### 输入

```
10 6
DLUDLRULLD
-1 0 1 10
-1 -2 2 5
-4 -2 6 10
-1 0 3 9
0 1 4 7
-3 -1 5 8
```

### 输出

```
YES
YES
YES
NO
YES
YES
```

