---
title: "WERTYU"
layout: "post"
diff: 普及-
pid: UVA10082
tag: []
---

# WERTYU

## 题目描述

一个常见的打字错误是将手放在键盘上比正确位置偏右一行。因此，$\tt Q$ 被打成了 $\tt W$，$\tt J$ 被打成了 $\tt K$，依此类推。你的任务是解码以这种方式输入的信息。

![](https://cdn.luogu.com.cn/upload/image_hosting/hi99zuat.png)

## 输入格式

输入由若干行文本组成。每行可能包含数字、空格、大写字母（除了 $\tt Q$、$\tt A$、$\tt Z$），或者上方显示的标点符号（不包括反引号 $\texttt{`}$）。带有单词标签的按键（$\tt Tab$，$\tt BackSp$，$\tt Control$ 等）不会出现在输入中。

## 输出格式

你需要将每个字母或标点符号替换为在上方所示的 QWERTY 键盘上其左边的字符。输入中的空格在输出中应保持不变。

---

Translated by User 735713.

## 样例 #1

### 输入

```
O S, GOMR YPFSU/
```

### 输出

```
I AM FINE TODAY.
```

