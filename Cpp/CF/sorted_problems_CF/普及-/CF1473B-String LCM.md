---
title: "String LCM"
layout: "post"
diff: 普及-
pid: CF1473B
tag: []
---

# String LCM

## 题目描述

如果字符串 $s$ 可以变成 $n$ 个字符串 $s_1$ 首尾相连，则说 $s$ 能被 $s_1$ 整除或 $s_1$ 能整除 $s$。

定义两个字符串 $s_1,s_2$ 的最短公倍串为：**可以被 $s_1$ 和 $s_2$ 整除的最短的非空串**。

例如： $baba$ 和 $ba$ 的最短公倍串为 $baba$；$aa$ 和 $aaa$ 的最短公倍串为 $aaaaaa$；$aba$ 和 $ab$ 没有最短公倍串。

## 输入格式

第一行一个整数 $t(1 \leq t \leq 2000)$，表示测试数据组数。

对于每一个测试数据，一共两行，每行一个字符串 $s_1,s_2(1 \leq |s_1|,|s_2| \leq 20)$，两个字符串都由 $'a'$ 和 $'b'$ 组成。

## 输出格式

对于每一个测试数据，输出 $s_1,s_2$ 的最短公倍串，如果没有输出 $-1$。

translated by [me](https://www.luogu.com.cn/user/390770)

## 样例 #1

### 输入

```
3
baba
ba
aa
aaa
aba
ab
```

### 输出

```
baba
aaaaaa
-1
```

