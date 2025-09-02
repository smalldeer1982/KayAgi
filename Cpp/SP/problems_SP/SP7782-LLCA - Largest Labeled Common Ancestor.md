---
title: "LLCA - Largest Labeled Common Ancestor"
layout: "post"
diff: 难度0
pid: SP7782
tag: []
---

# LLCA - Largest Labeled Common Ancestor

## 题目描述

在一个标号的完全 $k$ 叉树中，给定两个节点，你需要找出它们的最大标号公共祖先。在这个完全 $k$ 叉树中，节点是从左到右、从上到下依次标号的。最大标号公共祖先指的是一个节点，它既是 $A$ 的后代，也是 $B$ 的后代，并且在这样的节点中标号最大。注意，一个节点也被视为自己的后代。

**请注意，输入文件的大小限制为 256 字节。**

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量（$1 \le T \le 100$）。接下来的每个测试用例包含三个整数 $K$、$A$ 和 $B$，分别表示树的叉数和两个给定节点的标号（$2 \le K \le 100$；$1 \le A, B \le 2,000,000,000$）。

## 输出格式

对于每个测试用例，输出一行，表示最大标号的公共祖先节点。

## 数据范围
- $1 \le T \le 100$
- $2 \le K \le 100$
- $1 \le A, B \le 2,000,000,000$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n\n\n4\n3 42 7\n2 2 6\n2 1 105\n4 10 13\n\n
```

### 输出

```
\n\n\n2\n1\n1\n3\n\nWhitespace Explanation:\nIf there no input in any line, then the output for that line is a blank line :)) Sorry for inconvenience. >:)
```

