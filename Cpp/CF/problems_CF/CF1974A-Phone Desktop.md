---
title: "Phone Desktop"
layout: "post"
diff: 普及-
pid: CF1974A
tag: ['数学']
---

# Phone Desktop

## 题目描述

Little Rosie has a phone with a desktop (or launcher, as it is also called). The desktop can consist of several screens. Each screen is represented as a grid of size $ 5 \times 3 $ , i.e., five rows and three columns.

There are $ x $ applications with an icon size of $ 1 \times 1 $ cells; such an icon occupies only one cell of the screen. There are also $ y $ applications with an icon size of $ 2 \times 2 $ cells; such an icon occupies a square of $ 4 $ cells on the screen. Each cell of each screen can be occupied by no more than one icon.

Rosie wants to place the application icons on the minimum number of screens. Help her find the minimum number of screens needed.

## 输入格式

The first line of the input contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first and only line of each test case contains two integers $ x $ and $ y $ ( $ 0 \leq x, y \leq 99 $ ) — the number of applications with a $ 1 \times 1 $ icon and the number of applications with a $ 2 \times 2 $ icon, respectively.

## 输出格式

For each test case, output the minimal number of required screens on a separate line.

## 说明/提示

The solution for the first test case can look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974A/50fee263eb8faff81a1a0ba84255a68bc5871ae1.png) Blue squares represent empty spaces for icons, green squares represent $ 1 \times 1 $ icons, red squares represent $ 2 \times 2 $ iconsThe solution for the third test case can look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974A/53e483ebe35e12a51af69c31e4cb0b1e5b05aee6.png)

## 样例 #1

### 输入

```
11
1 1
7 2
12 4
0 3
1 0
8 1
0 0
2 0
15 0
8 2
0 9
```

### 输出

```
1
1
2
2
1
1
0
1
1
2
5
```

