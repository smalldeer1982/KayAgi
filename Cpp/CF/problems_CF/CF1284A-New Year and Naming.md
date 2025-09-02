---
title: "New Year and Naming"
layout: "post"
diff: 入门
pid: CF1284A
tag: []
---

# New Year and Naming

## 题目描述

新年快乐！在韩国 $2020$ 年也被称为庆州年(Year Gyeongja，경자년，gyeongja-nyeon)。该名字从何而来？让我们简要的看一下韩国传统的给年份命名的系统 $Gapja \ system$。

这里有两个序列，元素都是字符串，长度分别为 $n$、$m$，元素分别为 $s_1,s_2,s_3,\dots,s_n$、$t_1,t_2,t_3,\dots,t_n$。这些字符串只包含小写字母。可能有相同的字符串。

我们将在不改变顺序的前提下将字符串 $x$ 与 $y$ 写下来得到的字符串称作字符串 $x$ 与字符串 $y$ 的串联。例如：“code”和“forces”的串联字符串为“codeforces”。

第一年被命名为 $s_1$ 和 $t_1$ 的串联，当年份增加一时，两个被串联在一起的字符串下标加一。如果超出了字符串序列的长度，则超出长度的那一个序列回到序列开始的位置，也就是下标为 $1$ 的位置。

例如：如果 $n=3,m=4,s=$\{"a","b","c"\} , $t=\{"d","e","f","g"\}$，产生的年份的名称如下表所示
![Codeforces 1284A](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1284A/a92046f960f1c789c95190d41b023dfd6242560d.png)注意年份的名称可以重复。

给你两个序列长度分别为 $n$，$m$ 和 $q$ 个询问。每个查询给你当前的年份，请你从 $Gapja \ system$ 系统中找出它的名字。

## 输入格式

第一行有两个整数 $n,m \ (1 \le n,m \le 20)$。

下一行有由空格分隔的 $n$ 个字符串 $s_1,s_2,s_3,\dots,s_n$，每个字符串仅有小写字母构成，字符串的长度在一到十之间。

下一行有由空格分隔的 $m$ 个字符串 $t_1,t_2,t_3,\dots,t_m$，每个字符串仅有小写字母构成，字符串的长度在一到十之间。

所给的字符串中可能有重复。

下一行一个整数 $q \ (1 \le q \le 2020)$ 表示询问的个数。

接下来的 $q$ 行，每行一个整数 $y \ (1 \le y \le 10 ^ 9)$，表示询问你年份 $y$ 的名称。

## 输出格式

输出共 $q$ 行，第 $i$ 行表示第 $i$ 个询问的答案。

## 说明/提示

字符串序列的长度 $n,m$ 满足 $1 \le n,m \le 20$。

询问个数 $q$ 满足 $1 \le q \le 2020$。

询问的年份 $y$ 满足 $1 \le y \le 10 ^ 9$

**关于样例**

第一个样例使用的是实际的 $Gapja \ system$。这些字符串一般是数字或动物的名称。

translated by [yu__xuan](https://www.luogu.com.cn/user/142110)。

## 样例 #1

### 输入

```
10 12
sin im gye gap eul byeong jeong mu gi gyeong
yu sul hae ja chuk in myo jin sa o mi sin
14
1
2
3
4
10
11
12
13
73
2016
2017
2018
2019
2020
```

### 输出

```
sinyu
imsul
gyehae
gapja
gyeongo
sinmi
imsin
gyeyu
gyeyu
byeongsin
jeongyu
musul
gihae
gyeongja
```

