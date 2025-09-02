---
title: "Do Not Be Distracted!"
layout: "post"
diff: 普及-
pid: CF1520A
tag: []
---

# Do Not Be Distracted!

## 题目描述

Polycarp 有 $26$ 个任务。每一个任务都由一个大写字母来决定。

老师让 Polycarp 按以下规则做任务：如果 Polycarp 开始做某些任务，那么他必须一直做它，期间不能做其它任务，直到切换任务。但在切换到另一个任务之后，Polycarp 就不能再回到以前做过的任务了。

Polycarp 只能在一天内做一个任务。每一天他会写下他做了什么任务。现在老师想知道 Polycarp 是否遵守了他的规则。

举个例子，如果 Polycarp 以`DDBBCCCBBEZ`的顺序来做任务，那么老师就会知道在第三天 Polycarp 开始做任务`B`，然后在第五天他转移到做任务`C`，在第八天 Polycarp 又回到了做任务`B`，不符合老师的规则，老师就会怀疑他。老师会怀疑的的另外的例子有：`BAB`、`AABBCCDDEEBZZ`和`AAAAZAAAAA`。

如果 Polycarp 按照 `FFGZZZY` 的顺序来做，那么老师就没有任何怀疑。请注意 Polycarp 不必须完成所有的 $26$ 个任务。老师不会怀疑的其它例子有：`BA`、`AFFFCC`和`YYYYY`。

请你帮 Polycarp 指出他的老师是否会怀疑他。

## 输入格式

第一行有一个整数 $t$（$1\leq t\leq1000$），表示数据组数。接下来分别输入这 $t$ 组数据。

对于每一组数据，第一行一个整数 $n$（$1\leq n\leq50$），表示 Polycarp 花了几天做任务。

第二行为一个长度为 $n$ 的字符串，只包括大写的字母，表示 Polycarp 每天做的任务。

## 输出格式

对于每一组数据输出：

- `YES`，表示老师不会怀疑 Polycarp。
- 否则，输出 `NO`。

你可以以任意的方式输出字母（例如，`yEs`、`yes`、`Yes`和`YES`都表示老师不会怀疑）。

## 样例 #1

### 输入

```
5
3
ABA
11
DDBBCCCBBEZ
7
FFGZZZY
1
Z
2
AB
```

### 输出

```
NO
NO
YES
YES
YES
```

