---
title: "KQUERYO - K-Query Online"
layout: "post"
diff: 提高+/省选-
pid: SP23776
tag: []
---

# KQUERYO - K-Query Online

## 题目描述

给出一个长度为 $n$ 的序列，$q$ 个询问，询问 $[i,j]$ 区间大于 $k$ 的数的个数

## 输入格式

* 第一行：$n\space (1\le n\le 3\times 10^4)$
* 第二行：$n$ 个整数 $a_1, a_2 .. a_n \space (1 ≤ a_i ≤ 10^9) $
* 第三行：$q\space (1\le q\le 2\times 10^5)$，询问个数
* 接下来 $q$ 行，每行三个数 $a,b,c$，你需要进行以下操作
    * i = a xor last_ans
    * j = b xor last_ans
    * k = c xor last_ans

其中 last_ans 为上一次询问的答案，定义初始 last_ans 为0  。

## 输出格式

对于每个询问，单独输出一行表示答案

## 说明/提示

$1\le k \le10^9$    
如果 $i>j$，定义答案为 $0$。

## 样例 #1

### 输入

```
6
8 9 3 5 1 9
5
2 3 5
3 3 7
0 0 11
0 0 2
3 7 4
```

### 输出

```
1
1
0
0
2
```

