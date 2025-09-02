---
title: "[ABC370C] Word Ladder"
layout: "post"
diff: 普及-
pid: AT_abc370_c
tag: ['贪心']
---

# [ABC370C] Word Ladder

## 题目描述

有两个由小写英文字母组成的字符串 $S$ 和  $T$ 。其中保证 $S$ 和 $T$ 的长度相等。

新开一个数组 $X$ ，并重复以下操作，直到
$S$ 与 $T$ 相等：

更改 $S$ 中的一个字符，并将修改之后的 $S$ 添加到到 $X$ 的末尾。

求以这种方式获得的元素数量最少的字符串数组 $X$ 。如果有多个这样的数组，其元素数量最少，输出字典序最小的一个即可。

## 输入格式

两行 分别代表字符串 $S$ 和 $T$ （令长度为 $len$ )

## 输出格式

第一行输出修改的次数 （设它为 $M$ )

接下来 $M$ 行，输出 $X$ 数组，每一行输出 $len$ 个字符。

（我这里的表述与原题干有区别，如有歧义请大佬们指出qwq）

## 样例 #1

### 输入

```
adbe
bcbc
```

### 输出

```
3
acbe
acbc
bcbc
```

## 样例 #2

### 输入

```
abcde
abcde
```

### 输出

```
0
```

## 样例 #3

### 输入

```
afwgebrw
oarbrenq
```

### 输出

```
8
aawgebrw
aargebrw
aarbebrw
aarbebnw
aarbebnq
aarbeenq
aarbrenq
oarbrenq
```

