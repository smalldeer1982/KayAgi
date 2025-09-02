---
title: "Item World"
layout: "post"
diff: 提高+/省选-
pid: CF105C
tag: []
---

# Item World

## 题目描述

你有 $n$ 个物品，每个物品都有攻击力 $atk$，防御力 $def$，魔法值 $res$。

每件物品都属于以下三种之一：武器 $\text{weapon}$，防具 $\text{armor}$ 和宝具 $\text{orb}$。

现在有 $m$ 个居民住在物品中，每个居民都会给所居住的物品提供加成。

每个居民都属于以下三种之一：斗士 $\text{gladiator}$，侍卫 $\text{sentry}$ 和法师 $\text{physician}$。

其中，斗士可以增加物品的 $atk$ 值，侍卫可以增加物品的 $def$ 值，法师可以增加物品的 $res$ 值。

每个物品都有一个容量，表示能生存在这个物品内的最大居民数量，我们可以让居民在不同物品中跑来跑去。在一个时刻内我们可以在一件物品中取出若干个居民，并分散至若干个别的容量还没满的物品中。我们不可以把居民扔到物品外面，在任意时刻中居民都需要生存在物品中。

Laharl 有一些物品。他想在挪动一些居民后装备上一件武器、一件防具和一件宝具。在 Laharl 挪动居民后，应该使他装备的武器的 $atk$ 值最大。在满足以上条件的前提下，要尽量使他装备的防具的 $def$ 值最大。在满足以上两个条件的前提下，要尽量使他装备的宝具的 $res$ 值最大。

请你找到最佳的装备方案。

## 输入格式

第一行包含一个整数 $n\ (3 \leq n \leq 100)$，代表 Laharl 的物品数。

接下来有 $n$ 行，每一行描述一件装备，形为两个字符串和四个数：$\text{name\ \ class}\ \ atk\ \ def\ \ res\ \ size$，分别代表物品的名称，物品的种类，物品的攻击力，物品的防御力，物品的魔法值和物品的容量。

- $\text{name}$ 是个字符串，代表物品的名称。$1\leq|\text{name}|\leq10$，且 $\text{name}$ 中只包含小写字母。
- $\text{class}$ 是个字符串，可以是 $\text{weapon},\text{armor},\text{orb}$ 中的任意一种。
- $0\leq atk, def, res \leq 1000$
- $1\leq size \leq 10$

下一行包含一个整数 $k\ (1\leq k \leq 1000)$，代表居民的个数。

接下来有 $k$ 行，每一行描述一个居民，形为三个字符串和一个数：$\text{name\ \ type}\ \ bonus\ \ \text{home}$。

- $\text{name}$ 是个字符串，代表居民的名字。$1\leq|name|\leq10$，且 $\text{name}$ 中只包含小写字母。
- $\text{type}$ 是个字符串，可以是 $\text{gladiator},\text{sentry},\text{physician}$ 中的任意一种。
- $1\leq bonus \leq 100$ 表示这个居民的加成值。这个加成值会按自己的类型增加给相对应的物品。
- $\text{home}$ 是一个字符串，表示这个居民目前所在的物品名称。

保证每件物品初始时里面的居民数不超过物品的容量。

所有物品名和人名均是唯一的。

输入中所有字符串和整数都由一个空格隔开。

## 输出格式

第一行，输出选中武器的名字，在挪动居民后选中武器中的居民数，和居民的名字。

第二行输出防具，第三行输出宝具，格式同上。

若有多组解，输出任意一组即可。

## 样例 #1

### 输入

```
4
sword weapon 10 2 3 2
pagstarmor armor 0 15 3 1
iceorb orb 3 2 13 2
longbow weapon 9 1 2 1
5
mike gladiator 5 longbow
bobby sentry 6 pagstarmor
petr gladiator 7 iceorb
teddy physician 6 sword
blackjack sentry 8 sword

```

### 输出

```
sword 2 petr mike 
pagstarmor 1 blackjack 
iceorb 2 teddy bobby 

```

## 样例 #2

### 输入

```
4
sword weapon 10 2 3 2
pagstarmor armor 0 15 3 1
iceorb orb 3 2 13 2
longbow weapon 9 1 2 1
6
mike gladiator 5 longbow
bobby sentry 6 pagstarmor
petr gladiator 7 iceorb
teddy physician 6 sword
blackjack sentry 8 sword
joe physician 6 iceorb

```

### 输出

```
longbow 1 mike 
pagstarmor 1 bobby 
iceorb 2 petr joe 

```

