---
title: "Mascot Naming"
layout: "post"
diff: 普及+/提高
pid: CF2068F
tag: []
---

# Mascot Naming

## 题目描述

在筹办大型活动时，组织者常需处理专业领域外的琐事。例如，EUC 2025 的主裁判需要为官方吉祥物命名，并满足以下条件：
- 名称必须包含特定单词作为子序列$^{\texttt{*}}$，例如活动名称和举办地。给定必须包含的 $n$ 个单词列表 $s_1, s_2, \ldots, s_n$。
- 名称不得包含去年吉祥物名称 $t$ 作为子序列$^{\texttt{*}}$。

请帮助主裁判找到有效的吉祥物名称，或判定其不存在。  
$^{\texttt{*}}$ 若字符串 $x$ 可通过删除字符串 $y$ 中若干字符（不改变剩余字符顺序）得到，则称 $x$ 是 $y$ 的子序列。例如，$\texttt{abc}$ 是 $\texttt{axbycz}$ 的子序列，但不是 $\texttt{acbxyz}$ 的子序列。

## 输入格式

第一行包含整数 $n$（$1 \le n \le 200\,000$）——必须作为子序列出现的单词数量。

接下来 $n$ 行中，第 $i$ 行包含字符串 $s_i$（$1 \le |s_i| \le 200\,000$，仅含小写字母）——必须作为子序列出现的第 $i$ 个单词。所有 $s_i$ 的总长度不超过 $200\,000$，即 $|s_1| + |s_2| + \cdots + |s_n| \le 200\,000$。

最后一行包含字符串 $t$（$1 \le |t| \le 200\,000$，仅含小写字母）——去年吉祥物的名称。


## 输出格式

若存在有效名称，输出 $\texttt{YES}$，否则输出 $\texttt{NO}$。

若存在有效名称，在第二行输出一个有效名称。输出的字符串长度不得超过 $1\,000\,000$ 且仅含小写字母。可以证明，若存在有效名称，则必存在满足此额外约束的解。

若有多个解，输出任意一个即可。

## 说明/提示

第一个样例中，必须作为子序列的单词是 $\texttt{porto}$ 和 $\texttt{euc}$，而禁止作为子序列的单词是 $\texttt{prague}$。存在多个有效名称，例如 $\texttt{poretuco}$ 或 $\texttt{xxxpppeortoucyyyy}$。

若选择 $\texttt{poretuco}$ 作为名称，可验证 $\texttt{porto}$ 和 $\texttt{euc}$ 是其子序列（例如高亮显示为 $\texttt{POReTucO}$ 和 $\texttt{porEtUCo}$），而 $\texttt{prague}$ 不是。

字符串 $\texttt{poretuc}$ 无效，因其不包含 $\texttt{porto}$ 作为子序列。字符串 $\texttt{poretucoague}$ 也无效，因其包含 $\texttt{prague}$ 作为子序列。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
porto
euc
prague
```

### 输出

```
YES
poretuco
```

## 样例 #2

### 输入

```
6
credit
debit
money
rich
bank
capitalism
trap
```

### 输出

```
YES
moncrdebditeychankpitalism
```

## 样例 #3

### 输入

```
2
axiom
choice
io
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
4
aaa
aab
abb
bbb
ba
```

### 输出

```
YES
aaabbb
```

