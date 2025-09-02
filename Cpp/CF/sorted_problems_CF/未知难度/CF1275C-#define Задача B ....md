---
title: "#define Задача B ..."
layout: "post"
diff: 难度0
pid: CF1275C
tag: []
---

# #define Задача B ...

## 题目描述

程序员Vasya喜欢使用c/ c++语言来编程。他是C语言的忠实粉丝，因为只有C语言才能充分发挥Define-Oriented program的潜力。在C语言中，define允许在代码中的任何位置直接进行替换。例如，在执行下一个代码时，v的值将等于11 (表达式3+4*2的结果)。

```c
#define add(x) + x
#define mul(y) * y
int v = 3 add(4) mul(2);
```
Vasya最近写了一个程序来为数组赋值：

```
#define A0(x) x
#define A1(x) A0(x) A0(x + 1) A0(x + 3) A0(x + 4)
#define A2(x) A1(x) A1(x + 1) A1(x + 3) A1(x + 4)
#define A3(x) A2(x) A2(x + 1) A2(x + 3) A2(x + 4)
#define A4(x) A3(x) A3(x + 1) A3(x + 3) A3(x + 4)
...
#define A24(x) A23(x) A23(x + 1) A23(x + 3) A23(x + 4)
#define A25(x) A24(x) A24(x + 1) A24(x + 3) A24(x + 4)
const long long values[1125899906842624] = { A25(0) }
```


不幸的是，由于Vasya的电脑有问题，他的程序不能编译，但他很想知道程序运行后values数组中会有什么值。现在需要你帮他找出答案。

## 输入格式

第一行是一个整数 $n$（$1\leq n\leq 1000$），代表查询的个数。

下面 $n$ 行分别是数组下标 $pos_i$（$0\leq pos_i\leq 1125899906842623$），保证合法。

## 输出格式

输出共 $n$ 行，分别为数组中相对应的值。

## 样例 #1

### 输入

```
5
0
1
3
5
8

```

### 输出

```
0
1
4
2
3

```

