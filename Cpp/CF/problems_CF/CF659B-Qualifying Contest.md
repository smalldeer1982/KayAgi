---
title: "Qualifying Contest"
layout: "post"
diff: 普及/提高-
pid: CF659B
tag: []
---

# Qualifying Contest

## 题目描述

有 $n$ 个人，$m$ 个区。你需要从每个区域中选出成绩最好的两个人去参加比赛，输出这两个人的名字。如果第三个人的成绩和第二个人的成绩相同，则输出 ?，保证结果不确定。

## 输入格式

第一行输入两个正整数 $n$ 和 $m (2 \le n \le 100000, 1 \le m \le 10000, n\ge 2 m)$ ，接下来是 n 行，每行分别是这位选手的姓名，来自区域，分数。

## 输出格式

输出 $m$ 行，如果该区域结果确定，输出参加比赛的两人名字；如果结果不确定，输出 “？”。

## 样例 #1

### 输入

```
5 2
Ivanov 1 763
Andreev 2 800
Petrov 1 595
Sidorov 1 790
Semenov 2 503

```

### 输出

```
Sidorov Ivanov
Andreev Semenov

```

## 样例 #2

### 输入

```
5 2
Ivanov 1 800
Andreev 2 763
Petrov 1 800
Sidorov 1 800
Semenov 2 503

```

### 输出

```
?
Andreev Semenov

```

