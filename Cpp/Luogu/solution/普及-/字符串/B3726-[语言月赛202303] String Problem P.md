# [语言月赛202303] String Problem P

## 题目描述

Farmer John 有 $n$ 个字符串，第 $i$ 个字符串为 $s_i$。

现在，你需要支持如下 $q$ 次操作：

- `1 x y i`：把字符串 $s_x$ 整体插入到字符串 $s_y$ 的第 $i$ 个字符后，更新 $s_y$。
- `2 y`：求 $s_y$。

例如，设 $s_1 = \texttt{abc}$，$s_2 = \texttt{xyz}$，则执行完 `1 2 1 2` 后（把 $s_2$ 整体插入到 $s_1$ 的第 $2$ 个字符后，更新 $s_1$），$s_1 = \texttt{abxyzc}$，$s_2 = \texttt{xyz}$。

## 说明/提示

### 数据规模与约定

- 对 $60\%$ 的数据，保证 $i = |s_y|$。
- 对 $100\%$ 的数据，$1 \leq n,q \leq 10$，$1 \leq |s_i| \leq 10$。$1 \leq x, y \leq n$，$1 \leq i \leq |s_y|$。

其中 $|s_y|$ 表示进行对应操作时 $s_y$ 的长度，$|s_i|$ 表示输入时字符串的长度。

provider：一扶苏一

## 样例 #1

### 输入

```
2 2
a
b
1 1 2 1
2 2```

### 输出

```
ba```

## 样例 #2

### 输入

```
3 6
abc
ijk
xyz
1 2 3 2
1 1 3 5
1 3 1 1
2 1
2 2
2 3
```

### 输出

```
axyijkabczbc
ijk
xyijkabcz```

# 题解

## 作者：一扶苏一 (赞：4)

# [语言月赛202303] Carrot Harvest G 题解

## Source & Knowledge

2023 年 3 月语言月赛，由洛谷网校入门计划/基础计划提供。

本题考察字符串处理。

## 文字题解

### 题目大意

原题意已经非常简洁。

### 分析

可以使用 `string` 类的 `insert` 方法在一个 string 的内部插入一段字符串：`s.insert(i, t)` 表示在 $s$ 的第 $i$ 个字符后面插入字符串 $t$，$s$ 原有的字符顺次向后移动。

例如，如果 $s$ 是 $\texttt{abc}$，$t$ 是 $\texttt{xyz}$，调用 `s.insert(2,t)` 后，$s$ 将成为 $\texttt{abxyzc}$。

于是，题目中给定的操作 $1$ 就是 `s[y].insert(i, s[x])`，操作 $2$ 直接输出对应字符串即可。

## 视频题解

完整代码请在视频题解中查看

![](bilibili:BV1Vv4y1L7Vc?page=8)

---

