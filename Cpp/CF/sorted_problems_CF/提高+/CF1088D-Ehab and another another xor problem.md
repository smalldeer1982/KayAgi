---
title: "Ehab and another another xor problem"
layout: "post"
diff: 提高+/省选-
pid: CF1088D
tag: ['交互题']
---

# Ehab and another another xor problem

## 题目描述

交互题，系统有两个整数 $(a,b)$，你每次可以询问一组整数 $(c,d)$，系统会回答：
- $1$ 如果 $a\oplus c>b\oplus d$
- $0$ 如果 $a\oplus c=b\oplus d$
- $-1$ 如果 $a\oplus c<b\oplus d$

其中操作 $a\oplus b$ 表示 $a$ 和 $b$ [按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

你需要在询问不超过 $62$ 次之后输出 $(a,b)$ 的值，保证 $0\le a, b < 2^{30}$。

## 输入格式

请见“交互”

## 输出格式

输出 `! a b` 以输出答案，不要忘了在输出答案后清除缓冲区

### 交互：

输出 `? c d` 以询问，$c$ 和 $d$ 都应该是小于 $2^{30}$ 的非负整数，不要忘了在输出每一次询问后清除缓冲区

你可以用下列操作来清除缓冲区：

- C++：`fflush(stdout)`
- Java：`System.out.flush()`
- Python：`stdout.flush()`
- Pascal：`fflush(stdout)`
- 对于其它语言请参考文档

~~Hacking:~~

~~输出两个用空格隔开的整数 $a$ 和 $b$ 来 hack 别人（$0\le a,b<2^{30}$）~~

## 样例 #1

### 输入

```
1
-1
0
```

### 输出

```
? 2 1
? 1 2
? 2 0
! 3 1
```

