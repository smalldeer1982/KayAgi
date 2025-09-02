---
title: "Spell Check"
layout: "post"
diff: 入门
pid: CF1722A
tag: ['模拟']
---

# Spell Check

## 题目描述

输入一个字符串，请判断这个字符串是不是字符串 `Timur` 的一种排列。

例如：`Timur` ，`miurT` ，`Trumi` ，`mriTu` 都是正确的排列。

**注意：正确的排列必须包含大写的T和小写的其他字母。**

---

## 输入格式

输入的第一行一个整数 $t$ ，表示有 $t$ 组数据。

对于每组数据，第一行一个整数 $n$，表示输入的名字排列的长度。

第二行一个字符串，表示需要判断的排列。

---

## 输出格式

对于每组数据，如果当前排列事是正确的，则输出 `YES`，否则输出 `NO`。

---

## 说明/提示

$ 1 \le t \le 10^3 $ , $1 \le n \le 10$。

Translate By @Andy_L

## 样例 #1

### 输入

```
10
5
Timur
5
miurT
5
Trumi
5
mriTu
5
timur
4
Timr
6
Timuur
10
codeforces
10
TimurTimur
5
TIMUR
```

### 输出

```
YES
YES
YES
YES
NO
NO
NO
NO
NO
NO
```

