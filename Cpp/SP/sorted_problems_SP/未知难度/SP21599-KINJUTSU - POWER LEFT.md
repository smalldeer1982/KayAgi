---
title: "KINJUTSU - POWER LEFT"
layout: "post"
diff: 难度0
pid: SP21599
tag: []
---

# KINJUTSU - POWER LEFT

## 题目描述

鸣人正在战斗中，他目前的力量值为 $p$。他使用多重影分身之术来创造最多 $n$ 个分身，并决定将不超过 $p/2$ 的力量分配给尽可能多的分身。第一个分身总是分配到 $1$ 的力量，第 $i$ 个分身得到的力量为一个以 $1$ 为首项的等差数列的第 $i$ 项，且这个等差数列的总和不能超过 $p/2$。鸣人将所有偶数编号的分身派去侦查，将奇数编号的分身派去战斗。战斗结束后，只留下负责侦查的分身和拥有最高力量的分身。请计算鸣人召回所有分身后，他的剩余力量。

## 输入格式

第一行给出测试用例的数量 $t$（$t \leq 1000$）。接下来有 $t$ 行，每行包含两个整数 $p$ 和 $n$（$1 \leq p, n \leq 10^9$）。

## 输出格式

输出应包含 $t$ 行，每行输出对应每个测试用例中的结果。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1\n200 10\n
```

### 输出

```
155\n\n \nExplanation:- Naruto is going to give 100 power to 10 clones. So there will be an AP with first term as 1 common difference 2.\n&nbsp;On adding required terms we get 55, and hence total power is 155. \n
```

