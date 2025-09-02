---
title: "コンベア"
layout: "post"
diff: 难度0
pid: AT_past202012_h
tag: []
---

# コンベア

## 题目描述

给定一个 $h \times w$ 的平面网格图 $s$，网格图中的每一个字符都是`^`、`v`，`<`、`>`、`.`、`#`之一。移动规则如下：

- `.`：你可以向任意方向移动一格。
- `#`：此处不可移动。
- `^`：只可向上移动一格。
- `v`：只可向下移动一格。
- `<`：只可向左移动一格。
- `>`：只可向右移动一格。

现在给出一个目的地坐标 $(r,c)$，请判断：对于每一个不为`#`的方格，是否能从此处出发，到达 $(r,c)$？

## 输入格式

输入以以下格式由标准输入读入：

>$h$ $w$
>
>$r$ $c$
>
>$s_{1,1}$ $s_{1,2}$ ... $s_{1,w}$
>
>$s_{2,1}$ $s_{2,2}$ ... $s_{2,w}$
>
>...
>
>$s_{h,1}$ $s_{h,2}$ ... $s_{h,w}$

## 输出格式

输出一个 $h \times w$ 的网格。按如下规则输出：

- $(x,y)$ 为`#`时：照原样输出。
- $(x,y)$ 不为`#`时：若可以到达目的地输出`o`，否则输出`x`。

## 说明/提示

#### 数据规模与约定

对于全部测试点，数据保证：

- $1 \le h,w$，且 $h \times w \le 10^6$；
- $1 \le r \le h$，$1 \le c \le w$；

## 样例 #1

### 输入

```
3 3
1 1
..#
^^.
><.
```

### 输出

```
oo#
ooo
xxo
```

## 样例 #2

### 输入

```
10 12
9 1
#.^<..><<...
#<>.#<^.<<.^
^.<>.^.^.^>.
^.>#^><#....
.>.^>#...<<>
....^^.#<.<.
.>^..^#><#.^
......#>....
..<#<...^>^.
<..^>^^...^<
```

### 输出

```
#xxxxxxxxxxx
#xxx#xxxxxxx
xooxxxxxxxxx
xox#xxx#xxxx
oooxx#xxxxxx
ooooxxx#xxxx
ooooox#xx#xx
oooooo#xxxxx
ooo#xoooxxxx
xooxooooooxx
```

## 样例 #3

### 输入

```
15 20
13 9
####..<#^>#>.<<><^..
#.>#>.^#^.>><>...^..
>..<>.#.>.>.>...#..<
<^>.#..<>^#<#.>.<.^.
>#<^>.>#^>#^.^.#^><^
<^.^.#<...<.><#>...#
.<>....^..#>>#..>>><
.<#<^#.>#>^^.>.##.^<
.#.^.....<<#^#><^<<<
^.#>.#^.>.^.^<<>..><
.^#^<^^^<......^>.#^
.<..#>...^>^.^<..<.^
#.^.#..#.....>#.^^.>
.#^..>>><>>>^..#^.^^
.>#..<..<>.#>..^.#.^
```

### 输出

```
####xxx#xx#xxxxxxxxx
#xx#xxx#xxxxxxxxxxxx
xxxxxx#xxxxxxxxx#xxx
xxxx#xxxxx#x#xxxxxxx
x#xxxxx#xx#xxxx#xxxx
xxoxo#xxxxxxxx#xxxx#
xxoooooxxx#xx#xxxxxx
xx#xo#ox#xxxxxx##xxx
x#xxooooooo#x#xxxxxx
xx#oo#ooooooxxxoooxx
xx#ooxoooooooooooo#x
xxoo#oooooooooooooox
#ooo#oo#ooooox#oooox
x#oooxxxxoooooo#ooox
xx#oooooooo#oooxo#ox
```

