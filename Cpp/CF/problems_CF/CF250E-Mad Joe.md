---
title: "Mad Joe"
layout: "post"
diff: 普及+/提高
pid: CF250E
tag: []
---

# Mad Joe

## 题目描述

Joe has been hurt on the Internet. Now he is storming around the house, destroying everything in his path.

Joe's house has $ n $ floors, each floor is a segment of $ m $ cells. Each cell either contains nothing (it is an empty cell), or has a brick or a concrete wall (always something one of three). It is believed that each floor is surrounded by a concrete wall on the left and on the right.

Now Joe is on the $ n $ -th floor and in the first cell, counting from left to right. At each moment of time, Joe has the direction of his gaze, to the right or to the left (always one direction of the two). Initially, Joe looks to the right.

Joe moves by a particular algorithm. Every second he makes one of the following actions:

- If the cell directly under Joe is empty, then Joe falls down. That is, he moves to this cell, the gaze direction is preserved.
- Otherwise consider the next cell in the current direction of the gaze. 
  - If the cell is empty, then Joe moves into it, the gaze direction is preserved.
  - If this cell has bricks, then Joe breaks them with his forehead (the cell becomes empty), and changes the direction of his gaze to the opposite.
  - If this cell has a concrete wall, then Joe just changes the direction of his gaze to the opposite (concrete can withstand any number of forehead hits).

Joe calms down as soon as he reaches any cell of the first floor.

The figure below shows an example Joe's movements around the house.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF250E/aabe6062681eed440c39038fe1d895d0f5c78597.png)Determine how many seconds Joe will need to calm down.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=100 $ , $ 1<=m<=10^{4} $ ).

Next $ n $ lines contain the description of Joe's house. The $ i $ -th of these lines contains the description of the $ (n-i+1) $ -th floor of the house — a line that consists of $ m $ characters: "." means an empty cell, "+" means bricks and "\#" means a concrete wall.

It is guaranteed that the first cell of the $ n $ -th floor is empty.

## 输出格式

Print a single number — the number of seconds Joe needs to reach the first floor; or else, print word "Never" (without the quotes), if it can never happen.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
3 5
..+.#
#+..+
+.#+.

```

### 输出

```
14
```

## 样例 #2

### 输入

```
4 10
...+.##+.+
+#++..+++#
++.#++++..
.+##.++#.+

```

### 输出

```
42

```

## 样例 #3

### 输入

```
2 2
..
++

```

### 输出

```
Never
```

