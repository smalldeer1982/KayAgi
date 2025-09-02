---
title: "ADAAPPLE - Ada and Apple"
layout: "post"
diff: 提高+/省选-
pid: SP30785
tag: ['线段树', '树链剖分']
---

# ADAAPPLE - Ada and Apple

## 题目描述

Ada the Ladybug is currently on a trip on apple [tree](https://en.wikipedia.org/wiki/Tree_(data_structure)). There are many apples on the tree connected with branches. Each apple is inhabited by either Psylloideas or by Woolly Apple Aphids. Psylloideas and Aphids doesn't like each other, so it is strictly prohibited to walk from apple of Psylloideas to apple of aphids (and vice versa). Ada has some questions, whether it is possible to go from node **I** to node **J**.

Anyway note, that as Aphids and Psyllodeas doesn't like each other, they sometime conquer an apple of the others. Also note, that it is a real apple tree (not some bush) so no apple is connected with more than 50 other apples.

## 输入格式

The first line contains **1 , number apples on tree and number for queries.**

The next line contains **N** characters (either 0 or 1), indicating whether **i** $ ^{th} $ apple belongs to Psyllodeas or to Aphids.

Next **N-1** lines contains two numbers, the branches (edges) of apple tree (**0 , **I ≠ J**).**

Each of following **Q** lines contains one of following types of queries:

 **0 I**, **0 , meaning that ownership of **I** $ ^{th} $ apple has changed.**

 **1 I J**, **0 , question, whether it is possible to go from **I** $ ^{th} $ to **J** $ ^{th} $ apple.**

## 输出格式

For each query of second kind (1) print "YES", if it is possible or "NO" if it is impossible!

