---
title: "Rock-paper-scissors"
layout: "post"
diff: 入门
pid: CF48A
tag: ['字符串', '枚举']
---

# Rock-paper-scissors

## 题目描述

### 题面描述

三个人玩石头剪刀布，问谁赢了。

## 输入格式

输入三行，每行一个字符串（`rock`(石头)，`scissors`(剪刀)，`paper`(布)），分别表示这三个人出的手势。

石头打破剪刀，剪刀剪纸，纸裹在石头上。

当有一个人同时赢过其他两人时，他获胜，否则胜负不分。

## 输出格式

如果第一个人赢了输出`F`，第二个人赢了输出`M`，第三个人赢了输出`S`，胜负不分输出`?`。
Translated by Khassar

## 样例 #1

### 输入

```
rock
rock
rock

```

### 输出

```
?

```

## 样例 #2

### 输入

```
paper
rock
rock

```

### 输出

```
F

```

## 样例 #3

### 输入

```
scissors
rock
rock

```

### 输出

```
?

```

## 样例 #4

### 输入

```
scissors
paper
rock

```

### 输出

```
?

```

