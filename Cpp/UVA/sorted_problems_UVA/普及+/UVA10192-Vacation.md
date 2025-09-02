---
title: "Vacation"
layout: "post"
diff: 普及+/提高
pid: UVA10192
tag: []
---

# Vacation

## 题目描述

你想要去旅游并询问了你的父母，但他们给出的路线建议可能不一样，如果你旅游的顺序与他们建议的不一样，你就会伤害到他们，但是你可以选择不去某几个城市旅游来最大限度的满足他们双方。

你用大写字母，小写字母，数字和空格来表示城市，每个字符表示一个城市。因此，你最多可以访问 $63$ 个不同的城市，但你可以多次访问同一个城市。

例如有 $a,b,c,d$ 这 $4$ 个城市，母亲的建议是 $a\rightarrow b\rightarrow c\rightarrow d$，而父亲的建议是 $a\rightarrow c\rightarrow b\rightarrow d$。你可以选择不去 $c$，而去 $a\rightarrow b\rightarrow d$ 来同时满足你的父母。

现在，你要编写一个程序读取两行旅行序列，求出在满足父母双方的前提下你最多能去多少个城市。

## 输入格式

若干行仅由大写字母，小写字母，数字，空格和’$#$‘组成的字符串。当一个字符串以’$#$‘开头（不含引号）时输入结束，你的程序不应该处理这种情况。每行字符串最多包含 $100$ 个字符。

## 输出格式

对于每个序列对，你需要在单独一行输出以下消息：

``Case #d: you can visit at most K cities.
``

其中 $d$ 表示测试用例编号（从 $1$ 开始），$k$ 表示所求的最大城市数量。

## 样例 #1

### 输入

```
abcd
acdb
abcd
dacb
#
```

### 输出

```
Case #1: you can visit at most 3 cities.
Case #2: you can visit at most 2 cities.
```

