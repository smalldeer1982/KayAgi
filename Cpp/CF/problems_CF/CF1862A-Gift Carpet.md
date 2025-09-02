---
title: "Gift Carpet"
layout: "post"
diff: 入门
pid: CF1862A
tag: []
---

# Gift Carpet

## 题目描述

Recently, Tema and Vika celebrated Family Day. Their friend Arina gave them a carpet, which can be represented as an $ n \cdot m $ table of lowercase Latin letters.

Vika hasn't seen the gift yet, but Tema knows what kind of carpets she likes. Vika will like the carpet if she can read her name on. She reads column by column from left to right and chooses one or zero letters from current column.

Formally, the girl will like the carpet if it is possible to select four distinct columns in order from left to right such that the first column contains "v", the second one contains "i", the third one contains "k", and the fourth one contains "a".

Help Tema understand in advance whether Vika will like Arina's gift.

## 输入格式

Each test consists of multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 1 \le n, m \le 20 $ ) — the sizes of the carpet.

The next $ n $ lines contain $ m $ lowercase Latin letters each, describing the given carpet.

## 输出格式

For each set of input data, output "YES" if Vika will like the carpet, otherwise output "NO".

You can output each letter in any case (lowercase or uppercase). For example, the strings "yEs", "yes", "Yes", and "YES" will be accepted as a positive answer.

## 说明/提示

In the first sample, Vika can read her name from left to right.

In the second sample, Vika cannot read the character "v", so she will not like the carpet.

## 样例 #1

### 输入

```
5
1 4
vika
3 3
bad
car
pet
4 4
vvvv
iiii
kkkk
aaaa
4 4
vkak
iiai
avvk
viaa
4 7
vbickda
vbickda
vbickda
vbickda
```

### 输出

```
YES
NO
YES
NO
YES
```

