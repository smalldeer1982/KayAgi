---
title: "A Prosperous Lot"
layout: "post"
diff: 普及-
pid: CF934B
tag: ['贪心', '构造']
---

# A Prosperous Lot

## 题目描述

Apart from Nian, there is a daemon named Sui, which terrifies children and causes them to become sick. Parents give their children money wrapped in red packets and put them under the pillow, so that when Sui tries to approach them, it will be driven away by the fairies inside.

Big Banban is hesitating over the amount of money to give out. He considers loops to be lucky since it symbolizes unity and harmony.

He would like to find a positive integer $ n $ not greater than $ 10^{18} $ , such that there are exactly $ k $ loops in the decimal representation of $ n $ , or determine that such $ n $ does not exist.

A loop is a planar area enclosed by lines in the digits' decimal representation written in Arabic numerals. For example, there is one loop in digit $ 4 $ , two loops in $ 8 $ and no loops in $ 5 $ . Refer to the figure below for all exact forms.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF934B/ef09358ad2ff9bd7af31e67d589f7cc1105bcc74.png)

## 输入格式

The first and only line contains an integer $ k $ ( $ 1<=k<=10^{6} $ ) — the desired number of loops.

## 输出格式

Output an integer — if no such $ n $ exists, output -1; otherwise output any such $ n $ . In the latter case, your output should be a positive decimal integer not exceeding $ 10^{18} $ .

## 样例 #1

### 输入

```
2

```

### 输出

```
462
```

## 样例 #2

### 输入

```
6

```

### 输出

```
8080
```

