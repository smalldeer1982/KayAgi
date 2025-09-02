---
title: "QUILT - Little Quilt"
layout: "post"
diff: 难度0
pid: SP1003
tag: []
---

# QUILT - Little Quilt

## 题目描述

_Little Quilt_ 是 Ravi Sethi 在他的著作《Programming Languages》中介绍的一种小型编程语言。

在这里，我们讨论 Little Quilt 语言的一个简化版本，其语法由以下 BNF 结构定义：

< QUILT > ::= A | B | turn(< QUILT >) | sew(< QUILT >, < QUILT >)

A 和 B 是两种基本的被子图案，每种图案对应一个 2 × 2 的字符矩阵。turn() 和 sew() 是用来操作这些被子的函数。

函数 turn(x) 用来将被子 x 顺时针旋转 90 度。下表展示了基本被子的样式以及 turn() 操作的效果：

![subir imagenes](https://cdn.luogu.com.cn/upload/vjudge_pic/SP1003/9c1a8c0ffb27a1b5d3bc2e9eabf05791aa72faa7.png)

函数 sew(x, y) 用于将被子 x 拼接到被子 y 的左边。注意，x 和 y 的高度必须一致，否则会出现错误信息。下图展示了 sew(A, turn(B)) 的拼接结果：

![subir imagenes](https://cdn.luogu.com.cn/upload/vjudge_pic/SP1003/33e81d2606c3f34ac71f7e51b03f32cda106d258.png)

然而，像 sew(turn(sew(B, turn(B))), A) 这样的操作会生成错误信息。

你的任务是编写一个 Little Quilt 语言的解释器。

## 输入格式

输入由一个文本文件组成，包含多个 Little Quilt 表达式，每个表达式以分号 (;) 结束。空格和换行符需被忽略，这意味着一个表达式可以跨多行书写。

## 输出格式

输出包含根据输入表达式生成的图案。

每个图案前会有一行说明，格式如下：

```
Quilt i:
```

其中 i 是图案的序号，从 1 开始。如果表达式解析出错，请输出：

```
error
```

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
sew(turn(sew(B,turn(B))),
turn(sew(turn(B),B))) ;
\n\n
sew(turn(sew(B,turn(B))),A);
sew(turn(sew(A,turn(A))),
turn(turn(
\n
turn(sew(A,turn(A))))))
;
```

### 输出

```
Quilt 1:
||--
||--
--||
--||
Quilt 2:
error
Quilt 3:
\\//
+\/+
+/\+
//\\
```

