---
title: "Supermarket"
layout: "post"
diff: 普及+/提高
pid: UVA1316
tag: ['贪心', '并查集', '排序']
---

# Supermarket

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4062

[PDF](https://uva.onlinejudge.org/external/13/p1316.pdf)

## 样例 #1

### 输入

```
4 50 2 10 1 20 2 30 1
7 20 1 2 1 10 3 100 2 8 2 5 20 50 10
```

### 输出

```
80 
185
```



---

---
title: "Corporative Network"
layout: "post"
diff: 普及+/提高
pid: UVA1329
tag: ['并查集']
---

# Corporative Network

## 题目描述

有 $N$ 个结点，初始时每个结点的父结点都不存在。你的任务是执行一次 $I$ 操作和 $E$ 操作，格式如下：  
- $I\ u\ v$：把结点 $u$ 的父结点设为 $v$，距离为 $|u-v| \bmod 1000$。输入保证执行指令前 $u$ 没有父结点。  
- $E\ u$：询问 $u$ 到根节点的距离。

## 输入格式

输入第一行为测试数据组数 $T$。每组数据第一行为 $n$ $(5\leq n\leq 20000)$。接下来有不超过 $20000$ 行，每行一条指令，以大写英文字母 `O` 结尾。$I$ 指令的个数小于 $n$。

## 输出格式

对于每条 $E$ 指令，输出查询结果。

## 样例 #1

### 输入

```
1
4
E 3
I 3 1
E 3
I 1 2
E 3
I 2 4
E 3
O

```

### 输出

```
0
2
3
5

```



---

