---
title: "MUTDNA - DNA"
layout: "post"
diff: 提高+/省选-
pid: SP13105
tag: ['字符串', '动态规划 DP', '数学', '栈']
---

# MUTDNA - DNA

## 题目描述

我们发现了一种新型 $DNA$ ,这种 $DNA$ 只由 $N$ 个字母 $A$ 构成,在一次辐射中这种 $dna$  变成了由总共 $N$ 个字母  $A$ 和 $B$ 构成,在辐射中只会发生两种异变： 1.将某个任意位置字母反转 ,例如：将第 $K$  位置的 $A$ 变为 $B$ ，或将  $B$ 变为  $A$ . 2.将  $1$ 到 $K$ 位置上的所有字母反转， $1≤K≤N$ 并且  $K$  可以任选. 请你计算将全  $A$  序列转化为最终序列需要最少多少次异变.每发生一个  $1$  异变或  $2$  异变都计入一次总异变数.

## 输入格式

第一行包含正整数  $N(1≤N≤1 000 000)$ ,代表  $DNA$ 的长度. 第二行输入包含一个有  $N$ 个字符的字符串，每个字符都是  $A$ 或  $B$ .

## 输出格式

一行一个数字代表最小的异变数.

感谢@不许雷同 提供的翻译

## 样例 #1

### 输入

```
1:
4
ABBA
```

### 输出

```
1:
2
```



---

---
title: "CTGAME - City Game"
layout: "post"
diff: 提高+/省选-
pid: SP277
tag: ['栈']
---

# CTGAME - City Game

## 题目描述

Bob is a strategy game programming specialist. In his new city building game the gaming environment is as follows: a city is built up by areas, in which there are streets, trees, factories and buildings. There is still some space in the area that is unoccupied. The strategic task of his game is to win as much rent money from these free spaces. To win rent money you must erect buildings, that can only be rectangular, as long and wide as you can. Bob is trying to find a way to build the biggest possible building in each area. But he comes across some problems - he is not allowed to destroy already existing buildings, trees, factories and streets in the area he is building in.

Each area has its width and length. The area is divided into a grid of equal square units.The rent paid for each unit on which you're building stands is 3$.

Your task is to help Bob solve this problem. The whole city is divided into **K** areas. Each one of the areas is rectangular and has a different grid size with its own length **M** and width **N**. The existing occupied units are marked with the symbol **R**. The unoccupied units are marked with the symbol **F**.

## 输入格式

The first line of the input contains an integer **K** - determining the number of datasets. Next lines contain the area descriptions. One description is defined in the following way: The first line contains two integers-area length **M**<=1000 and width **N**<=1000, separated by a blank space. The next **M** lines contain **N** symbols that mark the reserved or free grid units,separated by a blank space. The symbols used are:

**R** - reserved unit

**F** - free unit

In the end of each area description there is a separating line.

## 输出格式

For each data set in the input print on a separate line, on the standard output, the integer that represents the profit obtained by erecting the largest building in the area encoded by the data set.

## 样例 #1

### 输入

```
2

5 6

R F F F F F

F F F F F F

R R R F F F

F F F F F F

F F F F F F



5 5

R R R R R

R R R R R

R R R R R

R R R R R

R R R R R
```

### 输出

```
45

0
```



---

