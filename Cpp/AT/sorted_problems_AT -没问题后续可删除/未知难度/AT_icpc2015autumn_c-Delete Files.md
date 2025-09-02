---
title: "Delete Files"
layout: "post"
diff: 难度0
pid: AT_icpc2015autumn_c
tag: []
---

# Delete Files

## 题目描述

现在有一个文件夹，你需要删除一些不用了的文件。

每一个文件名都显示在一个矩形区域内，这个区域称为文件名区域。每个文件名区域都与窗口的左侧对齐。每个文件名区域的高度为 1，每个文件名区域的宽度为文件名长度。例如，当三个文件`acm.in1`、`acm.c~`和`acm.c`按此顺序存储在一个文件夹中时，在文件管理器窗口中看起来是这样子的：

![FigC1](https://img.atcoder.jp/other/jag2015_autumn/fgvhjik/figC1.png)

你需要按照以下步骤删除文件：

- 选择一个矩形区域。该区域称为选择区域；
- 按下键盘上的删除键。删除时**当且仅当文件名区域与选择区域相交时，文件才会被删除。**

例如这张图：

![FigC2](https://img.atcoder.jp/other/jag2015_autumn/fgvhjik/figC2.png)

删除后，会将文件名区域移到窗口的上侧，**不会在任何剩余的文件名区域上留下任何上边距**，就像这样：

![FigC3](https://img.atcoder.jp/other/jag2015_autumn/fgvhjik/figC3.png)

需要求出删除的最小次数。

## 输入格式

第一行包含一个整数 $N (1 \le N \le 10^3)$，即文件夹中的文件数。

接下来的 $N$ 行每行包含一个字符 $D_i$ 和一个整数 $L_i(1 \le L_i \le 10^3)$：
- $D_i$ 表示是否删除第 $i$ 个文件，如果 $
- $L_i$ 为第 $i$ 个文件的文件名长度。

## 输出格式

一个数，表示删除的最小次数。

