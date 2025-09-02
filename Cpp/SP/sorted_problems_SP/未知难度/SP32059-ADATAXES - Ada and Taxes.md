---
title: "ADATAXES - Ada and Taxes"
layout: "post"
diff: 难度0
pid: SP32059
tag: []
---

# ADATAXES - Ada and Taxes

## 题目描述

 As you might already know, Ada the Ladybug is a farmer. She grows vegetables in a long furrow. All of the vegetables have some height. Local politicians tax small vegetables, but as the furrow is very long, they always tax just a part of it.

 The taxes always have some limit on height. They are calculated very simply: Tax collectors multiply the heights of all vegetables, which are lesser or equal to limit and are on desired segment.

 The taxes might be very high so tax collectors just round their income and take only **1000000007** (**10 $ ^{9} $ +7**) banknotes. They are very kind, so they always leave the rest to Ada. She is interested in how much they will leave her.

**NOTE:** If none of the vegeteble is lesser/equal to given limit, Ada is left with symbolical 1 "money".

## 输入格式

The first line contains an integer  **1 , the number of vegetables Ada grows and the number of times the tax collectors come.**

The second line contains **N** integers **1 , the heights of vegetables.**

The next **Q** lines contains three integers **0 , the left and right vegetables of segment and **1, the limit.****

## 输出格式

Print a single line for each query with the number of money Ada will be left with after each tax collecting.

