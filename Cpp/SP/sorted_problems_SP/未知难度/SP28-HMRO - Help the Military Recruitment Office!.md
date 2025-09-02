---
title: "HMRO - Help the Military Recruitment Office!"
layout: "post"
diff: 难度0
pid: SP28
tag: []
---

# HMRO - Help the Military Recruitment Office!

## 题目描述

 At the end of year 2004, the regional agencies of the Polish Military Recruitment Office (known as WKU in Polish) is sending a call to all boys born in 1984. Every recruit has his personal 11-digit identification number (PESEL, format: YYMMDDXXXXX, where YYMMDD is the date of birth, and XXXXX is a zero-padded integer smaller than 100000). Every agency of the Military Recruitment Office has its own code (MRO, format: a place code consisting of 3 upper case letters and a one-digit number). But this year the army underwent some reforms and not all boys at conscription age are going to be recruited. The list of closed down MRO points is as follows: the code of the closed down MRO is followed by the code of some other MRO, to which all the recruits are now going to be assigned. The list of recruits contains their PESEL codes. Your task is to prepare the complete list of recruits and determine the codes of their new MRO-s.

## 输入格式

```

s [the number of tests <= 10]
p [the number of boys at conscription age <= 100000]
PESEL and MRO code
z [the number of closed down MRO points <= 100000]
old_code new_code [old_code - the code of closed down MRO,
new_code - its new MRO code]
p [the number of recruits <= 100000]
PESEL [PESEL code of recruit]
[empty line]
[next tests]
```

## 输出格式

```

one PESEL and MRO code per line in the order of input
[empty line between tests]
[other results]
```

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages**

## 样例 #1

### 输入

```
1
4
84101011111 GDA1
84010122222 GDA2
84010233333 GDA2
84020255555 GDY1
1
GDA2 GDA1
3
84101011111
84010122222
84020255555
```

### 输出

```
84101011111 GDA1
84010122222 GDA1
84020255555 GDY1
```

