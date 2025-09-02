---
title: "TKV1000 - Takeover Wars"
layout: "post"
diff: 难度0
pid: SP18170
tag: []
---

# TKV1000 - Takeover Wars

## 题目描述

Takeover Incorporated 和 Buyout Limited 两家公司在竞争。Takeover Incorporated 有 $n$ 家子公司而 Buyout Limited 有 $m$ 家子公司。每家子公司有一个权值。两家公司轮流操作，每次操作可以执行一下两种收购之一：

1. 友好的收购，即将自家两家子公司合并，合并后的子公司权值为原两家子公司权值之和。
2. 有敌意的收购，即当自家的子公司权值大于对手的一家子公司的权值时，用自家的子公司去吞并对手的子公司，对手的子公司消失，而自家不变。

Takeover Incorporated 先操作，如果两家公司都按照最优方案操作，问谁能获胜。

## 输入格式

**每个测试点有多组数据**。需要读入到文件末尾。

对于每组数据，第一行输入 $n,m$。接下来一行 $n$ 个数 $a_i$ 代表 Takeover Incorporated 每家子公司的权值。接下来一行 $m$ 个数 $b_i$ 代表 Buyout Limited 每家子公司的权值。

## 输出格式

对于第 $i$ 组数据，先输出 `Case i: `（冒号后面有空格），然后输出 `Takeover Incorporated` 或 `Buyout Limited`，代表最终获胜的公司。

## 样例 #1

### 输入

```
3 2
7 1 1
5 5
4 2
3 3 3 3
5 5
```

### 输出

```
Case 1: Takeover Incorporated&nbsp;
```

