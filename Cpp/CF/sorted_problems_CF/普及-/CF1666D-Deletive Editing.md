---
title: "Deletive Editing"
layout: "post"
diff: 普及-
pid: CF1666D
tag: []
---

# Deletive Editing

## 题目描述

Daisy 喜欢玩有关文字的游戏。最近，她一直在和 Daniel 玩下面描述的删除与编辑的文字游戏。

这个游戏按以下描述的方式进行：Daisy 最初选择一个词，例如 `DETERMINED`。在游戏的每个回合里，Daniel 选择一个字母，例如 `E`，接下来 Daisy 删除掉在这个词中出现的第一个这个字母，这时她得到 `DTERMINED`，这个回合结束。

在下面的回合中，Daniel 依次选择 `D`、`I`、`N`、`D`，而 Daisy 依次得到 `TERMINED`、`TERMNED`、`TERMED`、`TERME`。现在，如果 Daniel 选择 `E`，Daisy 会得到 `TRME`。但如果她最开始选择的词为 `DETERMINED`，Daisy 将不可能得到 `TERM` 这个词。

Daisy 现在好奇在给定初始的词时，她能否在 $0$ 个或多个回合内通过这个游戏得到她选择的最终词。你的任务是帮助她判断这是否可行。

## 输入格式

第一行有一个整数 $n$，代表子任务组数（$1 \le n \le 10000$），接下来 $n$ 行，每行一个子任务。

每一个子任务包含 $2$ 个用空格分隔的字符串 $s$ 和 $t$。这两个字符串由不超过 $30$ 个大写英语字母构成。其中，$s$ 是 Daisy 初始选择的词，$t$ 是 Daisy 想要得到的词。

## 输出格式

输出 $n$ 行，每行代表一个子任务的答案。如果 Daisy 以 $s$ 为初始词能通过这个游戏得到 $t$，输出 `YES`；否则输出 `NO`。

## 样例 #1

### 输入

```
6
DETERMINED TRME
DETERMINED TERM
PSEUDOPSEUDOHYPOPARATHYROIDISM PEPA
DEINSTITUTIONALIZATION DONATION
CONTEST CODE
SOLUTION SOLUTION
```

### 输出

```
YES
NO
NO
YES
NO
YES
```

