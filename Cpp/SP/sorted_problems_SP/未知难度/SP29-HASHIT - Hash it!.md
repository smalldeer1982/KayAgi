---
title: "HASHIT - Hash it!"
layout: "post"
diff: 难度0
pid: SP29
tag: []
---

# HASHIT - Hash it!

## 题目描述

你的任务是计算一个包含101个元素的哈希表，其中包括若干个长度不超过15个字母（ASCII码 'A'……'z')的key字符串。其中可能包含以下操作：
* 查找该key值指向的元素（如果该元素不存在，那么忽略掉这次操作），
* 在这个表中插入一个key（如果该key已存在，那么忽略掉这次操作），
* 在不移动其他key的前提下，通过将key指向的元素标记为空来删除一个key（如果该key不存在，那么忽略掉这次操作）

查找、插入、删除操作定义如下：

$integer$ $Hash(string$ $key)$，

对于每一个key字符串$a_1$......$a_n$，$Hash(key)=h(key)$ $mod$ $101$。其中$h(key)$ = $19$×$(ASCII($$$a_1$$)$×$1+......$ASCII$($a_n$×$n$)
对于哈希冲突，我们采用开放地址的方法解决。例如，当我们尝试将key插入到哈希表第一个空位置时：对于$j$ = $1, ..., 19$，我们令$(Hash(key) + j^2 + 23*j)$ $ mod$ $101$，在检查20个位置后，我们就认为这次插入操作无法进行。

## 输入格式

测试组数$t$ $(t <= 100)$

操作数$n_1$，一行包含一次操作。操作有两种形式：

插入
ADD:string

或

删除
DEL:string

对于所有测试数据，行与行之间不存在空行。

## 输出格式

对于每一组测试，你都应该建立一个新的哈希表来插入或删除key，并且输出：

第一行包含一个数字，代表该哈希表中的key数量。

接下来若干行，每行输出一组 $Hash$值$:key$，按$Hash$值顺序输出这个哈希表。

## 样例 #1

### 输入

```
1
11
ADD:marsz
ADD:marsz
ADD:Dabrowski
ADD:z
ADD:ziemii
ADD:wloskiej
ADD:do
ADD:Polski
DEL:od
DEL:do
DEL:wloskiej
```

### 输出

```
5
34:Dabrowski
46:Polski
63:marsz
76:ziemii
96:z
```

