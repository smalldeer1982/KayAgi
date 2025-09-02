---
title: "BSMATH2 - Math with Bases"
layout: "post"
diff: 难度0
pid: SP5566
tag: []
---

# BSMATH2 - Math with Bases

## 题目描述

在你的帮助下，小本成功地在作业上取得了满分，他兴奋地跑回家给哥哥大本看。大本以前也做过这样的事情，所以并不太惊讶。大本自夸道：“想当年，我不仅要进行乘法和除法运算，而且数字要大得多，我们还要使用64进制呢！”

小本对此很感兴趣，便去网上搜寻相关的练习题。他发现，老师为了较高年级的学生，准备了一份与大本所说类似的64进制运算题目，结果又忘了注明每道题使用的是什么进制！

题目的要求如下：

64进制的数字与62进制相同，最后两个字符分别是单引号和双引号；所用字符集为0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz' "。

### 输入格式

第一行输入一个整数 $n$ ($1 < n < 64$)，表示题目包含的测试用例数量。每个测试用例的结构如下：

```
A - B = C
I
X1 op Y1 =
X2 op Y2 =
...
XI op YI =
```

在这里，`A - B = C` 是一个示例，这个等式是成立的；`I` (1 ≤ I ≤ 10) 表示题目的数量。随后每行都是一个运算题，格式为 `Xi op Yi =`，其中 `Xi` 和 `Yi` 是待计算的数（0 < X, Y），`op` 是四种基本运算之一：加法 `+`，减法 `-`，乘法 `*`，或取模 `%`。

### 输出格式

输出结果按照以下格式展示：

```
SECTION 1 (BASE b)
  X1 op Y1 = Z1
  X2 op Y2 = Z2
  ...
  Xi op Yi = Zi
SECTION 2 (BASE b)
  X1 op Y1 = Z1
  X2 op Y2 = Z2
  ...
  Xi op Yi = Zi
...
SECTION N (BASE b)
  X1 op Y1 = Z1
  X2 op Y2 = Z2
  ...
  Xi op Yi = Zi
```

其中，`Zi` 是 `Xi op Yi` 计算所得的结果，`b` 是所使用的进制。若进制无法确定，应选择使示例成立且题目有效的最低进制。

### 样例

**输入：**

```
4
K72Q - 9C5U = APRR
3
11JH4 - BMEB =
PB04 % DQ9O =
F0GM - UQR0 =
A654A - 9A60E = AE3B
2
B94BA + 3460A =
123A29 % 5E065 =
37CR - olh = 2KSm
5
157W % 1bIJ =
1P56 % 1Eob =
1C6I * 1"uX =
1Ktc % 1BMf =
20ne * 22V" =
BQfC - 4Kdb = 761H
2
9aFL * 3WU3 =
5fcV + 7fWL =
```

**输出：**

```
SECTION 1 (BASE 31)
  11JH4 - BMEB = KS2O
  PB04 % DQ9O = BFLB
  F0GM - UQR0 = -FQA9
SECTION 2 (BASE 15)
  B94BA + 3460A = EDAC5
  123A29 % 5E065 = 5594E
SECTION 3 (BASE 64)
  157W % 1bIJ = 157W
  1P56 % 1Eob = AIX
  1C6I * 1"uX = 2O3gS"I
  1Ktc % 1BMf = 9Wz
  20ne * 22V" = 46bA3EO
SECTION 4 (BASE 42)
  9aFL * 3WU3 = bBafS4L
  5fcV + 7fWL = DfTA
```

**注意事项**
- 输入数据可能很大。
- 输出结果可能很长。

 **本翻译由 AI 自动生成**

