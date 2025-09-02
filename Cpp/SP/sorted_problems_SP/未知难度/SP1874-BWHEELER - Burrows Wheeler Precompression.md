---
title: "BWHEELER - Burrows Wheeler Precompression"
layout: "post"
diff: 难度0
pid: SP1874
tag: []
---

# BWHEELER - Burrows Wheeler Precompression

## 题目描述

**Burrows-Wheeler 变换**（简称 **BWT**，也叫**块排序压缩**）是一种用于数据压缩的算法，被应用于如 bzip2 等技术中。该算法由 Michael Burrows 和 David Wheeler 发明。

通过 BWT 变换，一个字符串的字符本身并不改变，只是字符的顺序被重新排列。如果原始字符串中有频繁重复出现的子串，那么变换后的字符串在某些位置将会有大量连续重复的字符。这种情况对压缩算法很有帮助，因为通过“前端移动”变换和游程编码等技术可以很容易地压缩充满重复字符的字符串。

举个例子，字符串：

```
SIX.MIXED.PIXIES.SIFT.SIXTY.PIXIE.DUST.BOXES
```

经过变换后可以得到如下字符串，这显然更适合压缩因为存在许多连续重复的字符：

```
TEXYDST.E.IXIXIXXSSMPPS.B..E.S.EUSFXDIIOIIIT
```

Burrows-Wheeler 变换的步骤如下：

- 给定一个输入字符串 **S**，例如："abcba"。
- 生成 **S** 的所有循环移位。
  ```
  例如："abcba", "bcbaa", "cbaab", "baabc", "aabcb"
  ```
- 将所有移位后的字符串按字典序排序。
  ```
  例如："aabcb", "abcba", "baabc", "bcbaa", "cbaab"
  ```
- 将这些字符串排列成一个 len(S) x len(S) 的方阵。
  ```
  aabcb
  abcba
  baabc
  bcbaa
  cbaab
  ```
- 输出原始输入字符串所在行的行号（从 1 开始编号），以及最后一列字符构成的字符串。
  比如：2 bacab

现在，给定 Burrows-Wheeler 变换的输出，您是否能够恢复原始字符串？

**输入格式：**
输入包含多组测试用例。
每个测试用例的第一行是一个整数 **R**，表示在排序后的矩阵中包含原始字符串的行号。
每个测试用例的第二行是一个字符串 **Col**，代表方阵的最后一列。（1 ≤ len(Col) ≤ 1000）
**Col** 只含小写字母。1 ≤ **R** ≤ len(Col)。
输入以一行 R=0 结束，该行不需处理。

**输出格式：**
请输出经过 Burrows-Wheeler 变换之前的原始输入字符串。

**数据范围与提示：**
总共有 30 组测试用例。

**样例输入：**
```
2
bacab
3
rwlb
11
baaabaaaabbbaba
0
```

**样例输出：**
```
abcba
rbwl
baaabbbbaaaaaab
```

 **本翻译由 AI 自动生成**

