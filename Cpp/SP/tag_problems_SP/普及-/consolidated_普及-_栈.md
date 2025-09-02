---
title: "ONP - Transform the Expression"
layout: "post"
diff: 普及-
pid: SP4
tag: ['模拟', '递归', '栈']
---

# ONP - Transform the Expression

## 题目描述

请你将 $n$ 个中缀表达式转换为后缀表达式。

## 输入格式

第一行一个整数 $n$ 代表中缀表达式个数。

接下来 $n$ 行代表 $n$ 个中缀表达式。

## 输出格式

$n$ 行代表每个中缀表达式转换过来的后缀表达式。

## 说明/提示

对于 $100\%$ 的数据，$n \le 100$ , 表达式长度 $\le 400$ 。

Translated by @[稀神探女](/user/85216)

## 样例 #1

### 输入

```
3

(a+(b*c))

((a+b)*(z+x))

((a+t)*((b+(a+c))^(c+d)))
```

### 输出

```
abc*+

ab+zx+*

at+bac++cd+^*
```



---

