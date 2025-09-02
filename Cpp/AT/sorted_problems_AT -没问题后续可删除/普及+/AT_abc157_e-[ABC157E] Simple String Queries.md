---
title: "[ABC157E] Simple String Queries"
layout: "post"
diff: 普及+/提高
pid: AT_abc157_e
tag: []
---

# [ABC157E] Simple String Queries

## 题目描述

给定长度为n的原字符串与q次操作或询问。其格式如下:

①1 i c: 将第i位字符改为c(c也是字符)。

②2 l r: 询问区间[l,r]内不同字符的个数。



感谢ducati小蒟蒻的翻译

## 输入格式

第一行输入n，表示原字符串的长度。

第二行输入原字符串。

第三行输入q，表示询问或操作的次数。

## 样例 #1

### 输入

```
7
abcdbbd
6
2 3 6
1 5 z
2 1 1
1 4 a
1 7 d
2 1 7
```

### 输出

```
3
1
5
```

