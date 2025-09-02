---
title: "Hidden Password"
layout: "post"
diff: 普及+/提高
pid: UVA1314
tag: []
---

# Hidden Password

## 题目描述

给定一个全部由小写字母构成的长度为L字符串s，考虑将其前i(0≤i<L，L为字符串长度）个字母接到后面得到的字符串。比如qwert,得到的就是

qwert

wertq

ertqw

rtqwe

tqwer

5个字符串，从上到下标号为0，1，...，L-1.其中字典序最小的是ertqw,标号为2.则原字符串对应的密码就是2.

现在给定长度为L（5≤L≤100000）的小写字母字符串，求其对应的密码。如果有多个密码符合要求，输出最小的那个。

