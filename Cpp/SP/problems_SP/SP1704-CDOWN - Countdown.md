---
title: "CDOWN - Countdown"
layout: "post"
diff: 难度0
pid: SP1704
tag: []
---

# CDOWN - Countdown

## 题目描述

Ann Sister 经营着一个家谱数据库服务，为客户提供家族树记录。当客户登录系统时，他们可以使用多种服务，例如搜索、打印和查询。最近，一个客户提出了一个新的问题，超出了系统的现有功能：「家族中哪位成员孙辈最多？」这位客户最终不得不亲自查阅数据库来找到答案。为了应对将来可能提出的类似问题——例如曾孙或玄孙最多的问题——Ann 决定开发一个软件解决方案。

## 输入格式

输入由多个测试用例组成。第一行是一个整数，表示测试用例的数量。每个测试用例首先有一行包含两个正整数 $n$ 和 $d$：$n$ 表示接下来的 $n$ 行描述家族树的信息，$d$ 指定了我们关心的后代层级。例如，$d = 1$ 时，我们关心拥有最多子女（相隔一代）的人；$d = 2$ 时，我们关心最多孙辈（相隔两代）的人，以此类推。接下来的 $n$ 行每行格式如下：

_名字 m 子女名字 $_{1}$ 子女名字 $_{2}$ ... 子女名字 $_{m}$

其中，_名字_ 是家族成员的名字，_m_ 是其子女的数量，子女名字 $_{1}$ 到子女名字 $_{m}$ 是其子女的名字。这些数据行的顺序是随机的。可以假设所有 $n$ 行共同描述了一个单一且连通的家族树。家族树中的成员最多为 1000 人，所有名字的长度不超过 10 个字符。

## 输出格式

对于每个测试用例，按指定后代数量降序输出最多三个人名。如果出现数量相同的情况，则按字母顺序输出名字。如满足条件的人数不足三人，则仅输出符合条件的人名（不需输出没有指定后代的人的名字）。如果列表底部出现并列情况，可能会输出多于三个人名。每行输出一个名字，后面跟一个空格和对应的后代数量。在每个测试用例的输出开头，加上一行：

树 _i_:

其中 _i_ 代表测试用例编号（从 1 开始）。每个测试用例的输出之间用一个空行分隔。

## 说明/提示

- $1 \le n \le 1000$
- $1 \le d \le 10$
- 1 \le \text{名字长度} \le 10$

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
8 2
Barney 2 Fred Ginger
Ingrid 1 Nolan
Cindy 1 Hal
Jeff 2 Oliva Peter
Don 2 Ingrid Jeff
Fred 1 Kathy
Andrea 4 Barney Cindy Don Eloise
Hal 2 Lionel Mary
6 1
Phillip 5 Jim Phil Jane Joe Paul
Jim 1 Jimmy
Phil 1 Philly
Jane 1 Janey
Joe 1 Joey
Paul 1 Pauly
6 2
Phillip 5 Jim Phil Jane Joe Paul
Jim 1 Jimmy
Phil 1 Philly
Jane 1 Janey
Joe 1 Joey
Paul 1 Pauly
```

### 输出

```
Tree 1:
Andrea 5
Don 3
Cindy 2
Tree 2:
Phillip 5
Jane 1
Jim 1
Joe 1
Paul 1
Phil 1
Tree 3:
Phillip 5
```

