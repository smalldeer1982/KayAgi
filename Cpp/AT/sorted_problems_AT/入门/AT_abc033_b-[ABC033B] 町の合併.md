---
title: "[ABC033B] 町の合併"
layout: "post"
diff: 入门
pid: AT_abc033_b
tag: []
---

# [ABC033B] 町の合併

## 题目描述

有 $N$ 个城市，第 $i$ 个城市有两个数据：人口数量 $P_i$ 和城市名 $S_i$。    
现在这 $N$ 个城市要合并在一起，要找出一个新城市名，找名字的规则如下：   
首先计算出所有城市人口数之和，之后寻找一个城市，这个城市的人口数要比人口数之和的一半多。如果存在这个城市，则继续沿用这个城市的名字。如果没有，则新城市名为```atcoder```。

## 输入格式

输入共 $N+1$ 行。   
第 $1$ 行，一个整数 $N$。   
第 $2$ 到 $N+1$ 行，每行两个数据，为 $S_i$ 和 $P_i$。

## 输出格式

一个字符串，为最后的城市名。

## 样例 #1

### 输入

```
4
unagi 20
usagi 13
snuke 42
smeke 7
```

### 输出

```
snuke
```

## 样例 #2

### 输入

```
5
a 10
b 20
c 30
d 40
e 100
```

### 输出

```
atcoder
```

## 样例 #3

### 输入

```
14
yasuzuka 3340
uragawara 4032
oshima 2249
maki 2614
kakizaki 11484
ogata 10401
kubiki 9746
yoshikawa 5142
joetsu 100000
nakago 4733
itakura 7517
kiyosato 3152
sanwa 6190
nadachi 3169
```

### 输出

```
joetsu
```

