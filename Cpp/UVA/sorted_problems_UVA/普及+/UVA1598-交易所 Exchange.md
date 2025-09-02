---
title: "交易所 Exchange"
layout: "post"
diff: 普及+/提高
pid: UVA1598
tag: []
---

# 交易所 Exchange

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4473

[PDF](https://uva.onlinejudge.org/external/15/p1598.pdf)

## 样例 #1

### 输入

```
11
BUY 100 35
CANCEL 1
BUY 100 34
SELL 150 36
SELL 300 37
SELL 100 36
BUY 100 38
CANCEL 4
CANCEL 7
BUY 200 32
SELL 500 30
```

### 输出

```
QUOTE 100 35 - 0 99999
QUOTE 0 0 - 0 99999
QUOTE 100 34 - 0 99999
QUOTE 100 34 - 150 36
QUOTE 100 34 - 150 36
QUOTE 100 34 - 250 36
TRADE 100 36
QUOTE 100 34 - 150 36
QUOTE 100 34 - 100 36
QUOTE 100 34 - 100 36
QUOTE 100 34 - 100 36
TRADE 100 34
TRADE 200 32
QUOTE 0 0 - 200 30
```

