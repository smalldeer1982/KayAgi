---
title: "Nephren gives a riddle"
layout: "post"
diff: 普及+/提高
pid: CF896A
tag: ['字符串', '递归']
---

# Nephren gives a riddle

## 题目描述

奈芙莲有一个字符串数组 $f_{0\dots\infty}$。

$f_0$ 为 `What are you doing at the end of the world? Are you busy? Will you save us?`。

她想让更多人了解这个数组，所以她定义：

$$
\forall i\ge 1,f_i=\texttt{What are you doing while sending "}+f_{i-1}\\
+\texttt{"? Are you busy? Will you send "}+f_{i-1}+\texttt{"?}
$$

**注意其中的引号。**

奈芙莲会询问 $q$ 次，第 $i$ 次给定 $n,k$，你需要求出 $f_{n,k}$ 的值。**注意字符串从 $1$ 开始。**

## 输入格式

第一行一个正整数 $q$，表示询问的次数。

接下来 $q$ 行，每行两个整数 $n,k$。

## 输出格式

输出一行 $q$ 个字符。第 $i$ 个字符表示第 $i$ 组询问时 $f_{n,k}$ 的值。如果第 $i$ 组询问时 $\lvert f_n\rvert<k$，则第 $i$ 个字符输出 `.`。

## 说明/提示

对于所有数据，$1\le q\le 10,1\le n\le 10^5,1\le k\le 10^{18}$。

## 样例 #1

### 输入

```
3
1 1
1 2
1 111111111111

```

### 输出

```
Wh.
```

## 样例 #2

### 输入

```
5
0 69
1 194
1 139
0 47
1 66

```

### 输出

```
abdef
```

## 样例 #3

### 输入

```
10
4 1825
3 75
3 530
4 1829
4 1651
3 187
4 584
4 255
4 774
2 474

```

### 输出

```
Areyoubusy
```

