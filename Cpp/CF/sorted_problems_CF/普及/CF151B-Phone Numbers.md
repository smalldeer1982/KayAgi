---
title: "Phone Numbers"
layout: "post"
diff: 普及/提高-
pid: CF151B
tag: []
---

# Phone Numbers

## 题目描述

Nvodsk 的冬天刺骨般的冷！于是一行 $n$ 个朋友们会坐出租车，点一个披萨，然后给女生打电话。这个城市中的电话由三组数字组成（如 12-34-56）。每个朋友都有一本大小为 $s_{i}$（此为电话号码的数量）的电话簿。出租车司机的电话号由六个相同的数字构成（如 22-22-22），披萨外卖的电话则由六个递减的数字构成（如 98-73-21），剩下的号码都是女生的电话。

现在你朋友的电话簿都交到了你手里。计算一下当你想做某件事时最好去找谁（有着最多相应类型的电话号码的人）。

如果一个人的电话簿中同一个电话号码出现了两次，你也需要计数两次。也就是说，你需要考虑每个号码出现在电话簿中的次数。

## 输入格式

第一行包含一个整数 $n$($1\le n\le 100$) 为朋友的数量。

接下来的 $n$ 组数据用来描述每个朋友的电话簿。每一组数据的格式如下：

第一行包含一个整数 $s_{i}$ 和一个字符串 $name_{i}$($0\le s_{i}\le 100$)，用以表示第 $i$ 个朋友的电话簿中的电话号码的数量和第 $i$ 个朋友的名字。名字为一个由大写和小写拉丁字母组成的不超过 20 个字符的非空字符串。接下来的 $s_{i}$ 行为形如“XX-XX-XX”的电话号码，其中 X 为 $0$ 到 $9$ 之间的任意数字。

## 输出格式

在第一行输出“If you want to call a taxi, you should call: ”。然后输出所有朋友中拥有出租车司机电话号码最多的朋友的名字。

在第二行输出“If you want to order a pizza, you should call: ”。然后输出所有朋友中拥有披萨外卖电话号码最多的朋友的名字。

在第三行输出“If you want to go to a cafe with a wonderful girl, you should call: ”。然后输出所有朋友中拥有女生电话号码最多的朋友的名字。

## 说明/提示

第一个样例中有四个朋友。Fedorov 的电话簿包含一个出租车司机的电话号码和一个披萨外卖的电话号码，Melnikov 的电话簿只有 $3$ 个女孩的电话号码，而Rogulenko 的电话簿则有 $6$ 个出租车司机的电话号码和一个披萨外卖的电话号码，Kaluzhin 的电话簿有 $2$ 个出租车司机的电话号码和一个披萨外卖的电话号码。

因此，如果你想要打出租车，显然你应该给 Rogulenko 打电话，如果你想要定个披萨，你可以给 Rogulenko、Fedorov、Kaluzhin 中的任何一个打电话（他们每个人都只有一个电话号码）。Melnikov 则有最多的女生的电话号码。

## 样例 #1

### 输入

```
4
2 Fedorov
22-22-22
98-76-54
3 Melnikov
75-19-09
23-45-67
99-99-98
7 Rogulenko
22-22-22
11-11-11
33-33-33
44-44-44
55-55-55
66-66-66
95-43-21
3 Kaluzhin
11-11-11
99-99-99
98-65-32

```

### 输出

```
If you want to call a taxi, you should call: Rogulenko.
If you want to order a pizza, you should call: Fedorov, Rogulenko, Kaluzhin.
If you want to go to a cafe with a wonderful girl, you should call: Melnikov.

```

## 样例 #2

### 输入

```
3
5 Gleb
66-66-66
55-55-55
01-01-01
65-43-21
12-34-56
3 Serega
55-55-55
87-65-43
65-55-21
5 Melnik
12-42-12
87-73-01
36-04-12
88-12-22
82-11-43

```

### 输出

```
If you want to call a taxi, you should call: Gleb.
If you want to order a pizza, you should call: Gleb, Serega.
If you want to go to a cafe with a wonderful girl, you should call: Melnik.

```

## 样例 #3

### 输入

```
3
3 Kulczynski
22-22-22
65-43-21
98-12-00
4 Pachocki
11-11-11
11-11-11
11-11-11
98-76-54
0 Smietanka

```

### 输出

```
If you want to call a taxi, you should call: Pachocki.
If you want to order a pizza, you should call: Kulczynski, Pachocki.
If you want to go to a cafe with a wonderful girl, you should call: Kulczynski.

```

