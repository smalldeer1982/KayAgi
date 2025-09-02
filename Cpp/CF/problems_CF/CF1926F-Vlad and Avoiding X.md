---
title: "Vlad and Avoiding X"
layout: "post"
diff: 普及+/提高
pid: CF1926F
tag: []
---

# Vlad and Avoiding X

## 题目描述

Vladislav has a grid of size $ 7 \times 7 $ , where each cell is colored black or white. In one operation, he can choose any cell and change its color (black $ \leftrightarrow $ white).

Find the minimum number of operations required to ensure that there are no black cells with four diagonal neighbors also being black.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1926F/b96bca00ab008cd943717e290ba9a2dfa2e51cb4.png)The left image shows that initially there are two black cells violating the condition. By flipping one cell, the grid will work.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 200 $ ) — the number of test cases. Then follows the description of the test cases.

Each test case consists of $ 7 $ lines, each containing $ 7 $ characters. Each of these characters is either $ \texttt{W} $ or $ \texttt{B} $ , denoting a white or black cell, respectively.

## 输出格式

For each test case, output a single integer — the minimum number of operations required to ensure that there are no black cells with all four diagonal neighbors also being black.

## 说明/提示

The first test case is illustrated in the statement.

The second test case is illustrated below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1926F/7822d3ff7cf3565e0c2fe901fc2a936bc32a31de.png)In the third test case, the grid already satisfies the condition.

## 样例 #1

### 输入

```
4
WWWWWWW
WWWWBBB
WWWWWBW
WWBBBBB
WWWBWWW
WWBBBWW
WWWWWWW
WWWWWWW
WWWWWWW
WBBBBBW
WBBBBBW
WBBBBBW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WBBBBBW
BBBBBBB
BBBBBBB
WWWWWWW
BBBBBBB
BBBBBBB
BBBBBBB
```

### 输出

```
1
2
0
5
```

