---
title: "ARBITRAG - Arbitrage"
layout: "post"
diff: 普及+/提高
pid: SP9340
tag: []
---

# ARBITRAG - Arbitrage

## 题目描述

套利是指利用货币汇率的差异，将一种货币的一个单位转换为同一货币的一个以上单位。例如，假设1美元购买0.5英镑，1英镑购买10.0法国法郎，1法国法郎购买0.21美元。然后，通过兑换货币，聪明的交易者可以从1美元开始买入0.5×10.0×0.21=1.05美元，获利5%。

您的工作是编写一个程序，该程序以货币汇率列表作为输入，然后确定套利是否可行。

## 输入格式

多组测试数据，每组数据第一行一个数 N，表示有 N 个币种。当 N=0 的时候结束。
接下来 N 行每行表示一个币种的名称。
第 N+2 行一个数 M，表示有 M 个存在的兑换汇率关系。
接下来 M 行，每行一个字符串 S1，一个 D，再一个字符串 S2，表示 S1 币种与 S2 币种
的单向汇率是中间的实数。

## 输出格式

每组数据输出一行一个字符串”Yes”或者”No”（没有引号），表示能否套汇得利。

## 样例 #1

### 输入

```
3
USDollar
BritishPound
FrenchFranc
3
USDollar 0.5 BritishPound
BritishPound 10.0 FrenchFranc
FrenchFranc 0.21 USDollar

3
USDollar
BritishPound
FrenchFranc
6
USDollar 0.5 BritishPound
USDollar 4.9 FrenchFranc
BritishPound 10.0 FrenchFranc
BritishPound 1.99 USDollar
FrenchFranc 0.09 BritishPound
FrenchFranc 0.19 USDollar

0
```

### 输出

```
Case 1: Yes
Case 2: No
```

