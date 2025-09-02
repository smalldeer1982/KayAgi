---
title: "Machined Surfaces"
layout: "post"
diff: 难度0
pid: UVA414
tag: []
---

# Machined Surfaces

## 题目描述

有一种图片，这个图片有很多行，但列数固定为 $25$。这个图片由两种字符组成：`X` 和空格每一行可能有多个空格，也可能没有空格。保证每一行的空格连续出现（如果有的话），并且每一行的最左边和最右边一定是 `X`。

空格分出了左表面和右表面（都由字符 `X` 组成），左表面的右侧和右表面的左侧都是曲面。在某些行中，左表面和右表面已接触。

如以下输入中，左表面和右表面的第 $1$ 行的宽度都为 $2$，左表面和右表面的第 $2$ 行的宽度都为 $3$。红色部分代表左表面，绿色部分代表右表面，蓝色部分代表空格（用字符 `B` 代替）。

$${\color{red}XX}{\color{blue}BBBBBBBBBBBBBBBBBBBBB}{\color{green}XX}$$
$${\color{red}XXX}{\color{blue}BBBBBBBBBBBBBBBBBBB}{\color{green}XXX}$$

右表面**整体**向左移动，就可以尽量消除一部分空格，像这样：

$${\color{red}XX}{\color{blue}BB}{\color{green}XX}$$
$${\color{red}XXX}{\color{green}XXX}$$

问题来了：**尽量**消除后的空格数量是多少？

## 输入格式

输入由多个测试样例组成。

对于每个测试样例，第一行一个整数 $N$（$N\le13$），代表图片行数。

接下来的 $N$ 行，代表图片的每一行。

注意，真实输入是**空格**，而不是字符 `B`。

测试样例由 $0$ 结束。

## 输出格式

对于每个测试样例，输出一行，代表消除后的空格数量。

翻译者亲测：不需要在每个测试用例后输出空行。

Translated by [dengzijun](https://www.luogu.com.cn/user/387836)

## 样例 #1

### 输入

```
4
XXXXBBBBBBBBBBBBBBBBXXXXX
XXXBBBBBBBBBBBBBBBXXXXXXX
XXXXXBBBBBBBBBBBBBBBBXXXX
XXBBBBBBBBBBBBBBBBBXXXXXX
2
XXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXX
1
XXXXXXXXXBBBBBBBBBBBBBBXX
0
```

### 输出

```
4
0
0
```

