---
title: "Balanced Chemical Equations"
layout: "post"
diff: 难度0
pid: UVA1562
tag: []
---

# Balanced Chemical Equations

## 题目描述

#### 题目翻译
给定t个未配平的化学方程式,且每种分子内同种原子最多出现9次

要求你配平这些方程式(配平后每个分子的系数最大为9)

若无法配平,输出"IMPOSSIBLE"

否则输出${x1x2{\cdots}xMy1y2{\cdots}yN}$(从左至右将分子系数拼成的一个十进制数)最小的方案

## 输入格式

第一行输入一个整数 t (${1{\le}t{\le}10}$)表示t组数据

接下来t行,每行输入一个不平的方程式,保证一行不超过200个字符

## 输出格式

若可以配平,输出满足题意的系数 x1 x2 ..xM y1 y2 ..yN

不能配平则输出"IMPOSSIBLE"

#### 样例输入
```
3
HCl+CaO2H2=CaCl2+H2O
HCl+H2SO4=NaCl
HCl+NaOH=NaCl+H2O
```
#### 样例输出
```
2 1 1 2
IMPOSSIBLE
1 1 1 1
```

