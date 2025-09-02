---
title: "COMPRESS - Compressed String"
layout: "post"
diff: 难度0
pid: SP5153
tag: []
---

# COMPRESS - Compressed String

## 题目描述

## 题目内容

压缩字符串。

给出两个字符串 $A$ 和 $B$，$B$ 是标准的字符串，$A$ 是可能存在错误的字符串，请将两个压缩后的字符串转换为未压缩状态的字符串并进行比较。若 $A$ 与 $B$ 压缩前的字符串一致，输出 $\texttt{YES}$；否则输出 $\texttt{NO}$ 和第一个出现不一致的位置。

以下是字符串压缩的标准：

- 将字符串的连续字符压缩成“**[子字符串]重复次数**”的形式，如字符串 $\texttt{cabababd}$ 可以压缩成 $\texttt{c[ab]3d}$；
- 请注意：对于一个字符串，可以存在多种压缩方式，如上述字符串还可以压缩成 $\texttt{c[ab]1ababd}$、$\texttt{ca[ba]2bd}$ 等等。

## 输入格式

题目有多个测试点。

第一行输入一个整数 $T$，代表有 $T$ 个测试点。

接下来 $T \times 2$ 行，是T个测试点的数据。对于每个测试点，第一行是字符串 $A$ ，第二行是字符串 $B$ 。每个字符串仅由小写字母、中括号（$\texttt{[}$ 和 $\texttt{]}$）和数字组成。每组中括号后必须接上一个数字，代表括号内子串的重复次数。注意：该数字可以为 $0$，括号可以嵌套。

## 输出格式

先输出测试点编号，如 $\texttt{Case \#1:}$，再输出结果。

## 输入输出样例

输入：

```
5
a[a]12 
[[a]3]4a 
[z]12 
zzzzzzzzz 
[a[ba]2b]12 
[ab]36 
[a]123123123[icpc]2 
[[a]123]1001001inter 
aismoreeasierthanc 
gismuchharderthanj 
```

输出

```
Case #1: YES
Case #2: NO 10 
Case #3: YES 
Case #4: NO 123123125 
Case #5: NO 1 
```

## 说明/提示

以上输入输出样例中，测试点 $3$ 中 $A$ 字符串 $\texttt{[a[ba]2b]12}$ 可以写为 $\texttt{[ababab]12}$，进一步写为 $\texttt{[[ab]3]12}$，最后写为 $\texttt{[ab]36}$。

测试点中的数字可能非常大，不能以 $32$ 位整数存储。

翻译由 smart_kai 提供。

