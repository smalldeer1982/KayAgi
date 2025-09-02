---
title: "NWERC10H - Stock Prices"
layout: "post"
diff: 难度0
pid: SP8629
tag: []
---

# NWERC10H - Stock Prices

## 题目描述

这道题目涉及到股票价格的计算。以下是关于股票价格你需要了解的几点：

- 「卖价」是指某人愿意以最低价格出售一股股票。
- 「买价」是指某人愿意以最高价格购买一股股票。
- 「股票价格」指的是最近一次成交的价格。

当买价大于或等于卖价时，就会促成一笔交易。出价为买价的买单会与要价为卖价的卖单匹配，按照卖价进行股票交易，直到卖单或买单（或两者）完全满足（也就是买家不再需要更多股票，或者卖家不再愿意出售更多股票）。你将获得一系列订单（包括买入或卖出），需要在每个订单之后计算当前的卖价、买价和股票价格。

## 输入格式

第一行是一个正整数，表示测试用例的数量，最多可以有 100 个。接着对于每个测试用例：

- 一行包含一个整数 $n$，表示订单数量（$1 \le n \le 10^5$）。
- 接下来的 $n$ 行，每行格式为「_order_type x 股以 y 价格」，其中 _order_type 是「buy」或「sell」，$x$（$1 \le x \le 10^5$）表示股数，$y$（$1 \le y \le 10^5$）表示价格。

## 输出格式

对于每个测试用例：

- 输出 $n$ 行，每行格式为「ai bi si」，其中 ai、bi 和 si 分别表示在处理第 i 个订单后，并完成所有可能交易后的当前卖价、买价和股票价格。如果某个价格未定义，则以「-」代替。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
6
buy&nbsp;10&nbsp;shares&nbsp;at&nbsp;100
sell&nbsp;1&nbsp;shares&nbsp;at&nbsp;120
sell&nbsp;20&nbsp;shares&nbsp;at&nbsp;110
buy&nbsp;30&nbsp;shares&nbsp;at&nbsp;110
sell&nbsp;10&nbsp;shares&nbsp;at&nbsp;99
buy&nbsp;1&nbsp;shares&nbsp;at&nbsp;120
6
sell&nbsp;10&nbsp;shares&nbsp;at&nbsp;100
buy&nbsp;1&nbsp;shares&nbsp;at&nbsp;80
buy&nbsp;20&nbsp;shares&nbsp;at&nbsp;90
sell&nbsp;30&nbsp;shares&nbsp;at&nbsp;90
buy&nbsp;10&nbsp;shares&nbsp;at&nbsp;101
sell&nbsp;1&nbsp;shares&nbsp;at&nbsp;80
```

### 输出

```
-&nbsp;100&nbsp;-
120&nbsp;100&nbsp;-
110&nbsp;100&nbsp;-
120&nbsp;110&nbsp;110
120&nbsp;100&nbsp;99
-&nbsp;100&nbsp;120
100&nbsp;-&nbsp;-
100&nbsp;80&nbsp;-
100&nbsp;90&nbsp;-
90&nbsp;80&nbsp;90
100&nbsp;80&nbsp;90
100&nbsp;-&nbsp;80
```

