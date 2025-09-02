---
title: "Crypt Kicker II"
layout: "post"
diff: 普及/提高-
pid: UVA850
tag: []
---

# Crypt Kicker II

## 题目描述

## 题目大意
一种常见的字符串加密方式是将原串中所有字母替换掉，如原串为 $\text{abc}$，替换为 $a\to x,b\to y,c\to z$，则加密后的字符串为 $\text{xyz}$。由于要保证加密后的文本可以被解密，所以原串中不同的字母不会被替换成相同的字母。         
现在给出若干个加密后的字符串，其中一个字符串加密前为 $\text{the quick brown fox jumps over the lazy dog}$。     
你的任务是将所有字符串解密并输出。      
（若有多个文本可以解密成 $\text{the quick brown fox jumps over the lazy dog}$，选择第一个）       
题目有多组数据。

## 输入格式

第一行一个整数 $n$ 表示数据组数。     
接下来是 $n$ 组数据，相邻两组数据之间用一个空行隔开。     
字符串长度不超过 $80$，输入行数不超过 $100$。

## 输出格式

对于每组数据，如果有解，则输出解密后的字符串。如果无解，输出 $\text{No solution.}$（注意有句号！）。     
相邻两组数据的答案之间用空行隔开。

## 样例 #1

### 输入

```
1
vtz ud xnm xugm itr pyy jttk gmv xt otgm xt xnm puk ti xnm fprxq
xnm ceuob lrtzv ita hegfd tsmr xnm ypwq ktj
frtjrpgguvj otvxmdxd prm iev prmvx xnmq
```

### 输出

```
now is the time for all good men to come to the aid of the party
the quick brown fox jumps over the lazy dog
programming contests are fun arent they
```

