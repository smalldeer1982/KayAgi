---
title: "NATALIAS - Natalia Has Another Problem"
layout: "post"
diff: 难度0
pid: SP12244
tag: []
---

# NATALIAS - Natalia Has Another Problem

## 题目描述

Natalia 又有一个问题需要你帮忙解决。你还有精力吗？

一个「逻辑字符串」是由布尔表达式构成的字符串，包含运算符 AND、OR 和 NOT，以及布尔值。布尔表达式是递归的，这意味着运算符可以以其他运算符作为参数。例如，以下几种是有效的「逻辑字符串」：

- T  
- F  
- AND(T, T)  
- OR(T, F)  
- NOT(T)  
- AND(OR(T, F), AND(F, F))  
- AND(AND(AND(OR(T, F), F), F), T)  
- AND ( AND ( OR ( T,F),OR(F,F)),T)

需要注意的是，运算符和操作数之间可以有空格，但是运算符的字母之间不能有空格。因此，"AND(T,T)" 是有效的「逻辑字符串」，而 "A N D(T,T)" 不是。

给定一个「逻辑字符串」，请计算并输出其真值。

## 输入格式

第一行为整数 $T$（$1 \le T \le 10^5$），表示测试用例的数量。随后 $T$ 行中，每行包含一个有效的「逻辑字符串」。

## 输出格式

对于每个「逻辑字符串」，输出其真值。如果结果为真，输出 `T`；否则，输出 `F`。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
7\nT\nF\nAND(T, T)\nOR(T, F)\nNOT(T)\nAND(OR(T, F), AND(F, F))\nAND(AND(AND(OR(T, F), F), F), T)
```

### 输出

```
T\nF\nT\nT\nF\nF\nF
```

