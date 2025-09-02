---
title: "IGALAXY - Intergalactic Highways"
layout: "post"
diff: 难度0
pid: SP11952
tag: []
---

# IGALAXY - Intergalactic Highways

## 题目描述

在未来世界，人类已发展为银河级文明。到公元 700,000 年，人类能够在 1 个时间单位内瞬间到达任何星球。然而，为了避免与小行星相撞，他们有时需要在中途停留。

Rudolph-X3000，是一个单独的类人生物，他希望从星球 A 到星球 B 的过程中，以最少的停靠次数抵达，不重复访问任何星球。他时间紧迫，非常需要一个快速的答案。你能够帮他算出他至少需要访问多少个星球吗？

而作为一名星际旅行者，Rudolph-X3000 还希望知道具体的行程。如果存在多条从星球 A 到星球 B 的最短路径，选择字典序最小的一条；若路径不存在，则输出 -1。

人类现已掌握了“Delta速度”，允许他们在 1 个时间单位内快速从地点 i 到地点 j。因此，星球间的距离始终视为 1。

## 输入格式

第一行输入一个整数 $T$，表示测试用例的数量。

对于每组测试用例，首先输入一个整数 $R$，表示星球间的关系数量。每一条关系意味着可以从星球 $i$ 到达星球 $j$，这种关系是双向的，即 $(i, j)$ 与 $(j, i)$ 保持一致。

接下来有 $R$ 行，每行包含两个字符串 $P$ 和 $Q$，分别表示星球 $P$ 与星球 $Q$ 之间的关系。

最后一行包含两个字符串 $S$ 和 $D$，分别表示出发星球和目标星球。

注意：所有星球名称由大写字母和小写字母 [A-Z] [a-z] 组成。

## 输出格式

对每个测试用例，输出格式为 “Scenario #i: ”，其中 $i$ 是测试用例编号（从 1 开始）。接下来列出访问星球的最小数量，然后在下一行依次列出访问的星球名称（包括起点和终点），使用空格分隔。

**样例输入**：

```
3

8

Mercury Venus

Venus Earth

Earth Mars

Mars Jupiter

Jupiter Saturn

Saturn Uranus

Uranus Neptune

Neptune Pluto

Earth Pluto

7

Mesopotamia Merrick

Merian Earth

Earth Venus

Merian Merrick

Venus Mesopotamia

Pluto Earth

Mesopotamia Pluto

Mesopotamia Earth

2

Earth Sun

Moon Venus

Earth Moon
```

**样例输出**：

```
Scenario #1: 7

Earth Mars Jupiter Saturn Uranus Neptune Pluto

Scenario #2: 3

Mesopotamia Pluto Earth

Scenario #3: -1
```

**解释**：

对于第二个测试用例，“Mesopotamia”到“Earth”有两条可能的路径：“Mesopotamia → Pluto → Earth”和“Mesopotamia → Venus → Earth”。我们选择字典序较小的一条。

## 说明/提示

- 1 <= T <= 100
- 1 <= R <= 100,000
- 1 <= |P|, |Q|, |S|, |D| <= 50
- 不超过 10,000 个不同星球。

 **本翻译由 AI 自动生成**

