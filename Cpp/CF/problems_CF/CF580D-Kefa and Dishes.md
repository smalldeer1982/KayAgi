---
title: "Kefa and Dishes"
layout: "post"
diff: 普及+/提高
pid: CF580D
tag: ['动态规划 DP', '枚举', '状态合并']
---

# Kefa and Dishes

## 题目描述

$\texttt{songshe}$ 进入了一家餐厅，这家餐厅中有 $n\ (1\leqslant n\leqslant18)$ 个菜。$\texttt{songshe}$ 对第 $i$ 个菜的满意度为 $a_i\ (0\leqslant a_i\leqslant10^9)$。

对于这 $n$ 个菜，有 $k\ (0\leqslant k\leqslant n^2-n)$ 条规则：如果 $\texttt{songshe}$ 在吃完第 $x_i$ 个菜之后立刻吃了第 $y_i\ (x_i\neq y_i)$ 个菜，那么会额外获得 $c_i\ (0\leqslant c_i\leqslant10^9)$ 的满意度。

$\texttt{songshe}$ 要吃 $m\ (1\leqslant m\leqslant n)$ 道任意的菜，但是他希望自己吃菜的顺序得到的满意度最大，请你帮 $\texttt{songshe}$ 解决这个问题。

## 输入格式

第 $1$ 行包含三个整数 $n,m,k$。

第 $2$ 行 $n$ 个非负整数，第 $i$ 个数表示 $\texttt{songshe}$ 对第 $i$ 道菜的满意度为 $a_i$。

若 $k\neq0$，第 $3$ 行到第 $k+2$ 行每行 $3$ 个整数 $x_i,y_i,c_i$，含义见上文。

## 输出格式

一行一个整数，表示最大满意度。

## 样例 #1

### 输入

```
2 2 1
1 1
2 1 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 3 2
1 2 3 4
2 1 5
3 4 2

```

### 输出

```
12

```

