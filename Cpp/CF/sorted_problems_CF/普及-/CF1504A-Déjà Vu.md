---
title: "Déjà Vu"
layout: "post"
diff: 普及-
pid: CF1504A
tag: []
---

# Déjà Vu

## 题目描述

定义一个回文串为正着读与倒着读都相同的字符串，比如 `z`，`aba` 和 `abccba` 都是回文串。你恨回文串因为它给你“既视感”。

现有一字符串  $s$，你必须插入恰好一个字母 `a` 在  $s$ 的某处。若操作后的新字符串可能**不是**回文串，你需要找到一个例子；反之，你需要报告这是不可能的

比如，假设  $s$ 为 `cbabc`，通过插入一个字母 `a`，可以得到 `acbabc`、`cababc`、`cbaabc`、`cbabac`、或 `cbabca`。然而，`cbaabc` 是回文串，所以你应当输出其它字符串中的一个。

## 输入格式

第  $1$ 行一个整数  $t$，代表  $t$ 组测试数据

第  $2$ 行至第  $n+1$ 行，每行一个字符串

## 输出格式

对于每个字符串
- 若不可能使新字符串不是回文串，输出 `NO`
- 反之，输出 `YES`，换行并举出一例

换行

`YES` 与 `NO` 可以是小写或大写

## 说明/提示

$1 \leq t \leq 10^4$

字符串总长度不超过  $3 \times 10^5$

## 样例 #1

### 输入

```
6
cbabc
ab
zza
ba
a
nutforajaroftuna
```

### 输出

```
YES
cbabac
YES
aab
YES
zaza
YES
baa
NO
YES
nutforajarofatuna
```

