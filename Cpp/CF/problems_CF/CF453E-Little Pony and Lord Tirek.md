---
title: "Little Pony and Lord Tirek"
layout: "post"
diff: 省选/NOI-
pid: CF453E
tag: []
---

# Little Pony and Lord Tirek

## 题目描述

Lord Tirek is a centaur and the main antagonist in the season four finale episodes in the series "My Little Pony: Friendship Is Magic". In "Twilight's Kingdom" (Part 1), Tirek escapes from Tartarus and drains magic from ponies to grow stronger.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF453E/643ac83a27b2195ea33883fd4f5562486272f6c4.png)The core skill of Tirek is called Absorb Mana. It takes all mana from a magic creature and gives them to the caster.

Now to simplify the problem, assume you have $ n $ ponies (numbered from 1 to $ n $ ). Each pony has three attributes:

- $ s_{i} $ : amount of mana that the pony has at time 0;
- $ m_{i} $ : maximum mana that the pony can have;
- $ r_{i} $ : mana regeneration per unit time.

Lord Tirek will do $ m $ instructions, each of them can be described with three integers: $ t_{i},l_{i},r_{i} $ . The instruction means that at time $ t_{i} $ , Tirek will use Absorb Mana on ponies with numbers from $ l_{i} $ to $ r_{i} $ (both borders inclusive). We'll give you all the $ m $ instructions in order, count how much mana Tirek absorbs for each instruction.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of ponies. Each of the next $ n $ lines contains three integers $ s_{i},m_{i},r_{i} $ $ (0<=s_{i}<=m_{i}<=10^{5}; 0<=r_{i}<=10^{5}) $ , describing a pony.

The next line contains an integer $ m $ ( $ 1<=m<=10^{5} $ ) — the number of instructions. Each of the next $ m $ lines contains three integers $ t_{i},l_{i},r_{i} $ $ (0<=t_{i}<=10^{9}; 1<=l_{i}<=r_{i}<=n) $ , describing an instruction of Lord Tirek. The instructions are given in strictly increasing order of $ t_{i} $ (all $ t_{i} $ are distinct).

## 输出格式

For each instruction, output a single line which contains a single integer, the total mana absorbed in this instruction.

## 说明/提示

Every pony starts with zero mana. For the first instruction, each pony has 5 mana, so you get 25 mana in total and each pony has 0 mana after the first instruction.

For the second instruction, pony 3 has 14 mana and other ponies have mana equal to their $ m_{i} $ .

## 样例 #1

### 输入

```
5
0 10 1
0 12 1
0 20 1
0 12 1
0 10 1
2
5 1 5
19 1 5

```

### 输出

```
25
58

```

