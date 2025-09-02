---
title: "Letters Shop"
layout: "post"
diff: 普及-
pid: CF1187B
tag: []
---

# Letters Shop

## 题目描述

字母商店的橱窗其实是一个由 $n$ 个小写字母组成的字符串 $s$！店如其名，这家店就是卖字母的。

字母商店卖的东西很奇怪，卖的方式更奇怪，它只从左往右卖，意思是说，你只能买这个字符串 $s$ 的前缀。

你有 $m$ 个好基友，第 $i$ 个的名字叫做 $t_i$。他们听说了这家店，都打算来买点字母，来拼出自己的名字，当然买来的字母是可以被打乱顺序或者干脆不用的。他们都想知道至少要买下几个字母才能拼出自己的名字。

举几个例子

- $s="arrayhead" , t_i="arya"$时，必须买下$"\underline{array}head"$ $5$个字母

- $s="arrayhead" , t_i="harry"$时，必须买下$"\underline{arrayh}ead"$ $6$个字母

- $s="arrayhead" , t_i="ray"$时，必须买下$"\underline{array}head"$ $5$个字母

- $s="arrayhead" , t_i="r"$时，必须买下$"\underline{ar}rayhead"$ $2$个字母

- $s="arrayhead" , t_i="areahydra"$时，必须买下$"\underline{arrayhead}"$ $9$个字母

字母商店的字母很齐全，所有的朋友肯定都能拼出自己的名字。

要注意的是，你的朋友们都只是在Doing [window shopping](https://baike.baidu.com/item/%E6%A9%B1%E7%AA%97%E8%B4%AD%E7%89%A9/9473660?fr=aladdin&fromid=8209896&fromtitle=Window+shopping)。他们只要你帮他们算出答案，并不会真正买下这些字母。

## 输入格式

第一行是一个整数 $n(1\leq n \leq 2 \times10^5)$ 表示橱窗 $s$ 的长度

第二行是字符串 $s$

第三行一个整数 $m(1 \leq m \leq 5 \times10^4)$ 表示你的朋友个数

此后 $m$ 行 ,每一行有一个字符串 $t_i(1 \leq |t_i| \leq 2 \times 10^5)$

你的朋友都很正常，所以他们名字总长度不会超过$2\times10^5$

## 输出格式

共$m$行，第 $i$ 行对于第 $i$ 个朋友的询问输出他至少要买下几个字母才能拼出自己的名字。

## 样例 #1

### 输入

```
9
arrayhead
5
arya
harry
ray
r
areahydra

```

### 输出

```
5
6
5
2
9

```

