---
title: "Bear and String Distance"
layout: "post"
diff: 普及/提高-
pid: CF628C
tag: []
---

# Bear and String Distance

## 题目描述

------------
Limak是一只小北极熊。他喜欢单词——只由小写字母构成，长度为n的单词。

他规定dist(s,s')的值为s与s'在26个字母中的间距。如，dist(c,e)=dist(e,c)=2,dist(a,z)=dist(z,a)=25。

而且，当dist两个单词时，其值为dist第一个字母+dist第二个字母+……
如，dist(af,db)=dist(a,d)+dist(f,b)=3+4=7,dist(bear,roar)=16+10+0+0=26。                   

现在，Limak给你一个字母或单词s和值k，令你寻找一个s'使dist(s,s')=k。输出s'。如果没有合适的s'，输出-1。

注意：最好用标准输入输出流，如C++的cin和cout，Java的Scanner/System.out 。

## 输入格式

------------
第一行输入两个数：n和k。 ( 1<=n<=10^5 
  , 0<=k<=10^6 
  )。

第二行输入只由小写字母构成，长度为n的单词s。

## 输出格式

------------
如果没有合适的s'，输出-1。

否则，输出s',令dist(s,s')=k。

**输入输出样例**
------------

**输入#1**       
4 26

bear

**输出#1**

roar                    
**输入#2**

2 7

af

**输出#2**

db

**输入#3** 

3 1000

hey

**输出#3**

-1

## 样例 #1

### 输入

```
4 26
bear

```

### 输出

```
roar
```

## 样例 #2

### 输入

```
2 7
af

```

### 输出

```
db

```

## 样例 #3

### 输入

```
3 1000
hey

```

### 输出

```
-1

```

