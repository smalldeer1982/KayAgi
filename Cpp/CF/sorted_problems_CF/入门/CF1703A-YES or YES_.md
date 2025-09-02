---
title: "YES or YES?"
layout: "post"
diff: 入门
pid: CF1703A
tag: []
---

# YES or YES?

## 题目描述

给定一个字符串 $s$ ，它的长度为 $3$ ，由大写字母和小写字母组成。

要求判断这个字符串是否为`YES`（不分大小写）。

例如`yES`、`Yes`、`yes`都是合法的。

## 输入格式

第一行，一个正整数 $t$ （ $1 \le t \le 10^3$ ） ，表示测试组数。

## 输出格式

$t$ 行，对于每一个字符串，如果符合要求，输出`YES`。否则输出`NO`。

## 样例 #1

### 输入

```
10
YES
yES
yes
Yes
YeS
Noo
orZ
yEz
Yas
XES
```

### 输出

```
YES
YES
YES
YES
YES
NO
NO
NO
NO
NO
```

