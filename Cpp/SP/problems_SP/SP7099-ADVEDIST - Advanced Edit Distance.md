---
title: "ADVEDIST - Advanced Edit Distance"
layout: "post"
diff: 难度0
pid: SP7099
tag: []
---

# ADVEDIST - Advanced Edit Distance

## 题目描述

### 题意翻译
两个字符串 S 和 T 的编辑距离是将 S 转换为 T 所需的最小编辑操作次数。有效的编辑操作包括：

1. 在任意位置插入一个字符。

2. 修改一个已有字符。

3. 删除一个已有字符。

例如，“pantera”和“aorta”的编辑距离是 5，因为以下编辑链是有效的（并且没有更短的链）：

“pantera” → “antera” → “aotera” → “aoera” → “aora” → “aorta”。

我们以类似的方式定义高级编辑距离，但将两个相邻字符的交换作为额外的有效操作。在这种设置下，“pantera”和“aorta”的高级编辑距离是 4：

“pantera” → “antera” → “antra” → “aotra” → “aorta”。

你需要编写一个程序来计算给定两个单词的高级编辑距离。

## 输入格式

输入包含多个测试用例。每个测试用例在一行中描述，包含两个非空单词，每个单词最多由 1000 个小写字母组成，两个单词之间用一个空格分隔。输入的最后一行包含两个星号，用一个空格分隔，不应作为测试用例处理。

## 输出格式

对于每个测试用例，输出一行整数，表示两个输入单词的高级编辑距离。

## 样例 #1

### 输入

```
\n\npantera aorta\nzero zero\n* *\n\n
```

### 输出

```
\n\n4\n0\n
```

