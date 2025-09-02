---
title: "Mark-up"
layout: "post"
diff: 普及-
pid: UVA391
tag: []
---

# Mark-up

## 题目描述

## 题目背景

`Mark-up` 是一种支持格式化文本的计算机语言（类似 Markdown）。一些关键字（就是 C++ 里的逃逸字符，如`\n`）被用于标记文本，支持更改字体、页面样式、段落样式等等。

$\TeX$、HTML 以及 Troff 文本编辑软件都使用了 `Mark-up` 语言。

为了能够正确检查拼写语法，拼写检查器需要一个前置代码，来删去关键字。


你需要制作一个程序，用于对一个小型 `Mark-up` 子集执行删除关键字的操作。你的程序应该输出“净文本”，即处理完毕的字符串。

本 `Mark-up` 子集包含五种关键字，每种都由反斜杠 `\` 开头。如果 `\` 后面不是一个合法关键字，那么这个字符被正常处理（即：不转义，保留 `\` 字符，这点不同于 C++）。以下是五种关键字：
> `\b` 切换是否**加粗**，默认为否；
> 
> `\i` 切换是否*斜体*，默认为否；
> 
> `\s` 设置字体大小，s 后**可选地**连接一个数值，如果没有数值则恢复到上次使用 `\s` 时的字体；数值可以包含小数，并且 `.5`、`3.` 这样的小数也允许。
> 
> `\*` 切换是否为 `Mark-up` 模式，默认为是，当关闭时所有的文字都视为**非关键字**（除 `\*` 本身），不会按关键字处理；
> 
> `\\` 用于输出一个 `\` 字符。

## 输入格式

任意多行，为原字符串

## 输出格式

行数同输入行数，为净文本。

## 样例 #1

### 输入

```
\s18.\bMARKUP sample\b\s
\*For bold statements use the \b command.\*
If you wish to \iemphasize\i something use the \\i command.
For titles use \s14BIG\s font sizes, 14 points usually works well.
Remember that all of the commands toggle except for the \\s command.
```

### 输出

```
MARKUP sample
For bold statements use the \b command.
If you wish to emphasize something use the \i command.
For titles use BIG font sizes, 14 points usually works well.
Remember that all of the commands toggle except for the \s command.
```

