---
title: "HOUSEBUY - House Buying Optimizations"
layout: "post"
diff: 难度0
pid: SP31894
tag: []
---

# HOUSEBUY - House Buying Optimizations

## 题目描述

Bill 和 Scott 是商业对手。二人都想在 Javaville 买房，但他们希望彼此住得尽可能远。由于 Javaville 是个新城镇，目前没有用得上的地图信息。他们的房屋和建筑物信息是通过口耳相传收集的，确保信息一致，可能存在不完整或多余信息。

Javaville 的街道布局是一个网格状，有 **m** 条东西向街道（以字母 **‘A ’, ‘B ’, ‘C ’**… 命名）和 **n** 条南北向街道（以数字 ‘**0 ’, ‘1 ’, ‘2 ’**… 编号），其中 **m** 和 **n** 都介于 2 到 10 之间。每栋建筑物（不论是住宅还是邮局、学校等）位于两个街道的交叉口，没有两栋建筑重合于同一交叉口。有些交叉口可能没有建筑。所有距离以从一个交叉口到另一个交叉口必须通过的最小街区数来计算，可以向四个方向移动。

以下是一些可能提供给 Bill 和 Scott 的示例信息：

- 共有 5 条东西向街道和 5 条南北向街道。
- house1 位于交叉口 **A0**。
- 邮局位于交叉口 **A4**。
- 学校离 house1 有 4 个街区。
- house2 离邮局有 6 个街区。
- 学校离邮局有 6 个街区。
- house3 离邮局有 6 个街区。

通过这些信息，我们发现 Javaville 的布局有两种可能——见图 1。

![Javaville, 可能的两种布局](http://www.lydsy.com:808/JudgeOnline/upload/201112/1(4).jpg)

**图 1:** **h1, h2, h3 = 房屋, P = 邮局, S = 学校**

我们注意到 house1、邮局和学校的位置是固定的，但 house2 可能位于 C0 或 E2，house3 也可能在 C0 或 E2。显然，总是有一对房子相距 6 个街区（因为 house1 总与最远的房子相距 6 个街区），但特定的房子对最多只能保证相距 4 个街区（因为 house2 总是与 house3 距离为 4 个街区）。在这种情况下，我们建议 Bill 和 Scott 考虑让一方购置 house2，另一方购置 house3（假设他们会协商以确保其中一个建议被采纳）。

Bill 和 Scott 需要你编写一个程序，利用建筑物的位置和距离信息来计算出两个值 **D** 和 **D′**。**D** 是所有可能布局中，两栋房屋之间最大距离的最小值。**D′** 是至少有一对房子能保证相距至少 **D′** 的最大值。此外，你还需要列出所有能保证相距至少 **D′** 的房子对。

具体来讲，

定义某个可行布局 **S** 的直径 **d(S)** 为该布局中最远的两屋距离。对于任意两所住宅 **i** 和 **j**，其安全因子 **e[i, j]** 定义为所有可行布局中 **i** 与 **j** 间的最小距离。Bill 和 Scott 希望你编写程序，计算出

**D = min {d(S)} 对于所有布局 S**；  
**D′ = max {e[i, j]} 对于所有房子对 (i, j)**。

你还需要提供最安全的购买建议：即所有满足 **e[i, j] = D′** 的房子对 **(i, j)**。

举例来说，第一个布局的 **d(S1)** = 6，第二个布局的 **d(S2)** = 6。各房子对的安全因子为：

**e[1,2]** = 2, **e[1,3]** = 2, **e[2,3]** = 4。因此，

**D = min {d(S1), d(S2)}** = 6，且

**D′ = max {e[1,2], e[1,3], e[2,3]}** = 4。购买建议是：选择 house2 和 house3。

## 输入格式

输入包含一个或多个描述。每个描述从一行开始，由两个正整数 **m** 和 **n** 组成，表示每个方向的街区数（$2 \leq m, n \leq 10$）。数据描述以大写字母“END”结束。整个输入集以一对零结束。

每个数据描述中，其余行的格式��：

`name LOCATION r c`

或

`name DISTANCE d name2`

其中 `name` 和 `name2` 是只由小写字母和数字组成的字符串，长度最多为 10；`r` 是大写字母 ‘A’ 到 ‘J’ 之间的字母；`c` 是一个数字；`d` 是一个正整数。如果 `name` 的前五个字符是 “house”，则它是 Bill 或 Scott 采购的住宅候选；否则，它代表其他非住宅建筑。在“DISTANCE”行中，`name2` 总是先前在该数据集中在某行开头出现过的建筑名称（即，“DISTANCE”约束内没有未来引用的建筑）。每个描述信息是一致的（即，至少有一种布局方式符合这些描述）。每个描述至少包含两栋不同房子的相关信息。每个描述中最多有 25 个不同建筑名称，最多有 50 个约束条件（“LOCATION”或“DISTANCE”）。

## 输出格式

对于每个描述，输出包含 **D**，然后是 **D′** 的值，接着列出所有相距 **D′** 的房子对列表（可能小于最大可实现分离距离）。同一房子对不应重复列出。输出应与示例输出的格式完全相符，连续数据集之间以空行分隔。在每个房子对中，房屋按输入中的首次出现顺序排列；房子对列表按相同的顺序排序，即先按第一个元素排序，再按第二个元素排序。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5 5\nhouse1 LOCATION A 0\npostoffice LOCATION A 4\nschool DISTANCE 4 house1\nhouse2 DISTANCE 6 postoffice\nschool DISTANCE 6 postoffice\nhouse3 DISTANCE 6 postoffice\nEND\n10 10\nhouse1 LOCATION A 0\nbuilding2 DISTANCE 12 house1\nbuilding2 DISTANCE 12 house1\nhouse3 DISTANCE 7 house1\nbuilding4 DISTANCE 2 house3\nbuilding4 DISTANCE 7 building2\nbuilding4 DISTANCE 2 house3\nhouse5 DISTANCE 6 building4\nbuilding6 DISTANCE 10 building2\nbuilding6 DISTANCE 5 building4\nbuilding6 DISTANCE 2 house1\nhouse7 DISTANCE 1 house1\nhouse7 DISTANCE 1 house1\nbuilding8 DISTANCE 10 house7\nhouse9 DISTANCE 10 building2\nhouse9 DISTANCE 3 building4\nbuilding10 DISTANCE 5 house3\nbuilding10 DISTANCE 5 house3\nhouse11 DISTANCE 3 building2\nbuilding12 DISTANCE 7 house7\nbuilding12 DISTANCE 8 house1\nbuilding12 DISTANCE 9 building4\nbuilding12 DISTANCE 3 house5\nhouse13 DISTANCE 7 building8\nhouse13 DISTANCE 3 house5\nbuilding14 DISTANCE 2 building10\nbuilding14 DISTANCE 9 building8\nhouse15 DISTANCE 12 building8\nhouse15 DISTANCE 11 building12\nhouse15 DISTANCE 9 building2\nhouse15 DISTANCE 7 house13\nbuilding16 DISTANCE 6 building10\nbuilding16 DISTANCE 3 house11\nbuilding16 DISTANCE 12 house9\nbuilding16 DISTANCE 5 house7\nhouse17 DISTANCE 4 house11\nhouse17 DISTANCE 3 building12\nbuilding18 DISTANCE 8 building14\nbuilding18 DISTANCE 10 building6\nbuilding18 DISTANCE 8 building14\nbuilding18 DISTANCE 10 building6\nhouse19 DISTANCE 2 house13\nhouse19 DISTANCE 6 building18\nhouse19 DISTANCE 1 house5\nbuilding20 DISTANCE 8 building14\nEND\n0 0
```

### 输出

```
\n6 4\nhouse2 house3\n9 9\nhouse1 house11\nhouse5 house9\nhouse9 house11\nhouse9 house17
```

