---
title: "The Snail"
layout: "post"
diff: 入门
pid: UVA573
tag: []
---

# The Snail

## 题目描述

有一只蜗牛，从深度为 $h$ 的井里向上爬，每天白天可以爬 $u$ 米，晚上回滑下来 $d$ 米，$f$ 为蜗牛的疲劳度百分比，当疲劳度为 $0$ 时，蜗牛这一天不能向上爬。

假如蜗牛爬到了井口，输出 ```success on day xxx```，```xxx```为从开始到成功的天数。

假如蜗牛滑回了井底，输出 ```failure on day xxx```，```xxx```为从开始到失败的天数。

**本题多测**

## 输入格式

每行读入四个如题面的数字，如果 $h = 0$，结束读入。

## 输出格式

输出读入 $-1$ 行，每行一个字符串，代表答案。

## 说明/提示

$1\le h,u,d,f\le100$。

## 样例 #1

### 输入

```
6 3 1 10
10 2 1 50
50 5 3 14
50 6 4 1
50 6 3 1
1 1 1 1
0 0 0 0
```

### 输出

```
success on day 3
failure on day 4
failure on day 7
failure on day 68
success on day 20
failure on day 2
```

