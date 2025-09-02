---
title: "Jugs"
layout: "post"
diff: 普及+/提高
pid: UVA571
tag: []
---

# Jugs

## 题目描述

有两个桶  $A$ 和  $B$，容量分别为  $Ca$ 和  $Cb$，且  $Ca$ 与  $Cb$ **互质**。

请利用这两个罐子相互取水，倒水，最后在  $A$ 或  $B$ 罐子里刚好能得到所要水的量  $N$。

## 输入格式

本题包括**多组数据**，每行  $3$ 个整数  $Ca, Cb, N$。

## 输出格式

输出方案。举例：

- `fill A`：表示把  $A$ 装满
- `empty B`：倒空  $B$
- `pour A B`：把  $A$ 的水倒在  $B$ 里
- `success`：表示成功。

## 样例 #1

### 输入

```
3 5 4
5 7 3
```

### 输出

```
fill B
pour B A
empty A
pour B A
fill B
pour B A
success
fill A
pour A B
fill A
pour A B
empty B
pour A B
success
```

