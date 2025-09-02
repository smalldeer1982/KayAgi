---
title: "Make AP"
layout: "post"
diff: 入门
pid: CF1624B
tag: []
---

# Make AP

## 题目描述

$Polycarp$ 有 $3$ 个整数 $a,b,c$ 。你需要选择一个整数 $m$ ，使 $a,b,c$ 中的任意一个数乘上它，并让之后的 $a,b,c$ 构成[**算术级数**](https://en.wikipedia.org/wiki/Arithmetic_progression)。

- [**算术级数**](https://en.wikipedia.org/wiki/Arithmetic_progression)：一个数列中每一组相邻的两个数的差相等（即为**等差数列**），如：$[5,10,15]$, $[3,2,1]$, $[1,1,1]$, $[13,10,7]$ 。而 $[1,2,4]$, $[0,1,0]$, $[1,3,2]$ 则不能形成[**算术级数**](https://en.wikipedia.org/wiki/Arithmetic_progression)。

## 输入格式

第一行一个整数 $t$ $(1≤t≤10^4)$ 表示测试用例的数量。

之后 $t$ 行每一行是 $3$ 个整数 $a,b,c$  $(1≤a,b,c≤10

## 输出格式

如果存在这样一个 $m$ , 输出 ```YES``` ,否则输出 ```NO``` (对 ```YES``` 和 ```NO``` 的大小写不做要求，如 ```YeS``` ```yeS``` 也是可以的)。

## 样例 #1

### 输入

```
11
10 5 30
30 5 10
1 2 3
1 6 3
2 6 3
1 1 1
1 1 2
1 1 3
1 100000000 1
2 1 1
1 2 2
```

### 输出

```
YES
YES
YES
YES
NO
YES
NO
YES
YES
NO
YES
```

