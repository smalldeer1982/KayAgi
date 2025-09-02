---
title: "BLHETA - Legend of Heta"
layout: "post"
diff: 难度0
pid: SP27378
tag: []
---

# BLHETA - Legend of Heta

## 题目描述

Heta 是一个用于表示希腊字母 Eta (Η) 及其变体中辅音 /h/ 的传统名称（出处：维基百科）。由于受到 N'Zoth 腐化者的教唆，Heta 立志要摧毁所有现存的字母表（虚构情节）。

Heta 有一本收藏了多种删除字符咒语的魔法书。带上这本书，Heta 开始了他的摧毁之旅。途中，他发现了一个非常长的字符串。为了彻底消除这个字符串，Heta 从头开始逐个检查每个字符。若在任何时候，他发现某个连续的子串在他的魔法书中有对应的咒语，那么该咒语就会立即被施放，删除这个子串。接着，他继续向后处理字符串，直到无法再施放任何咒语为止。如果某个时刻可以施放多个咒语，则优先使用魔法书中最先出现的那个。请确定 Heta 完成任务后，剩下的字符串是什么。

## 输入格式

第一行是一个由大写字母 A-Z 组成的字符串，其长度在 1 到 100000 个字符之间。第二行输入一个整数 N，表示魔法书中的咒语数量（1 < N < 100）。接下来的 N 行，每行是一个咒语，由大写字母 A-Z 组成，长度为 1 到 100 个字符，按出现顺序排列。

## 输出格式

输出一行，内容是 Heta 施法完成后剩余的字符串。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
KUKUKAKIKUKAKEKKUKAKAKKUKAKUKAKU
2
KEK
UK
```

### 输出

```
KAKIKAKAKAKKAKAKU

Input:
HEATHLEDGER
2
HEATH
LEDGER

Output:


Input:
KAPKAPPAPAK
1
KAPPA

Output:
K

Input:
CABAI
3
ABA
AB
B

Output:
CAI
```

