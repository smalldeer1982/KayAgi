---
title: "Chocolate"
layout: "post"
diff: 提高+/省选-
pid: CF490D
tag: []
---

# Chocolate

## 题目描述

Polycarpus likes giving presents to Paraskevi. He has bought two chocolate bars, each of them has the shape of a segmented rectangle. The first bar is $ a_{1}×b_{1} $ segments large and the second one is $ a_{2}×b_{2} $ segments large.

Polycarpus wants to give Paraskevi one of the bars at the lunch break and eat the other one himself. Besides, he wants to show that Polycarpus's mind and Paraskevi's beauty are equally matched, so the two bars must have the same number of squares.

To make the bars have the same number of squares, Polycarpus eats a little piece of chocolate each minute. Each minute he does the following:

- he either breaks one bar exactly in half (vertically or horizontally) and eats exactly a half of the bar,
- or he chips of exactly one third of a bar (vertically or horizontally) and eats exactly a third of the bar.

In the first case he is left with a half, of the bar and in the second case he is left with two thirds of the bar.

Both variants aren't always possible, and sometimes Polycarpus cannot chip off a half nor a third. For example, if the bar is $ 16×23 $ , then Polycarpus can chip off a half, but not a third. If the bar is $ 20×18 $ , then Polycarpus can chip off both a half and a third. If the bar is $ 5×7 $ , then Polycarpus cannot chip off a half nor a third.

What is the minimum number of minutes Polycarpus needs to make two bars consist of the same number of squares? Find not only the required minimum number of minutes, but also the possible sizes of the bars after the process.

## 输入格式

Polycarpus likes giving presents to Paraskevi. He has bought two chocolate bars, each of them has the shape of a segmented rectangle. The first bar is $ a_{1}×b_{1} $ segments large and the second one is $ a_{2}×b_{2} $ segments large.

Polycarpus wants to give Paraskevi one of the bars at the lunch break and eat the other one himself. Besides, he wants to show that Polycarpus's mind and Paraskevi's beauty are equally matched, so the two bars must have the same number of squares.

To make the bars have the same number of squares, Polycarpus eats a little piece of chocolate each minute. Each minute he does the following:

- he either breaks one bar exactly in half (vertically or horizontally) and eats exactly a half of the bar,
- or he chips of exactly one third of a bar (vertically or horizontally) and eats exactly a third of the bar.

In the first case he is left with a half, of the bar and in the second case he is left with two thirds of the bar.

Both variants aren't always possible, and sometimes Polycarpus cannot chip off a half nor a third. For example, if the bar is $ 16×23 $ , then Polycarpus can chip off a half, but not a third. If the bar is $ 20×18 $ , then Polycarpus can chip off both a half and a third. If the bar is $ 5×7 $ , then Polycarpus cannot chip off a half nor a third.

What is the minimum number of minutes Polycarpus needs to make two bars consist of the same number of squares? Find not only the required minimum number of minutes, but also the possible sizes of the bars after the process.

## 输出格式

In the first line print $ m $ — the sought minimum number of minutes. In the second and third line print the possible sizes of the bars after they are leveled in $ m $ minutes. Print the sizes using the format identical to the input format. Print the sizes (the numbers in the printed pairs) in any order. The second line must correspond to the first bar and the third line must correspond to the second bar. If there are multiple solutions, print any of them.

If there is no solution, print a single line with integer -1.

## 样例 #1

### 输入

```
2 6
2 3

```

### 输出

```
1
1 6
2 3

```

## 样例 #2

### 输入

```
36 5
10 16

```

### 输出

```
3
16 5
5 16

```

## 样例 #3

### 输入

```
3 5
2 1

```

### 输出

```
-1

```

