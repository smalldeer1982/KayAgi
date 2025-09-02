---
title: "Weapon Upgrade"
layout: "post"
diff: 难度0
pid: CF2087F
tag: []
---

# Weapon Upgrade

## 题目描述

Monocarp is playing a game. The game is divided into stages, and there are a total of $ 1337 $ stages. The game character uses a weapon with two attack modes: physical and elemental. Initially, the weapon's physical attack power is $ 1 $ , and its elemental attack power is also $ 1 $ .

During the $ i $ -th stage of the game, the following events occur in order:

1. If $ i \le n $ , a monster with a physical defense $ a_i $ and elemental defense $ b_i $ appears. Otherwise, nothing happens.
2. Monocarp can shoot at exactly one of the remaining monsters. If the monster's physical defense is at most the character's physical attack power or the monster's elemental defense is at most the character's elemental attack power, the monster will be killed. Otherwise, nothing happens.
3. Each surviving monster deals $ 1 $ damage to the game character.

After each kill, Monocarp can upgrade one of the attacks of the weapon by $ 1 $ .

Your task is to calculate the minimum damage that Monocarp can get in order to kill all the monsters in the game (or report that it is impossible to kill all the monsters).

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 500 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 500 $ ).

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 500 $ ).

## 输出格式

Print a single integer — the minimum damage that Monocarp can get in order to kill all the monsters in the game; if it is impossible to kill all the monsters, print -1.

## 说明/提示

In the first example, Monocarp can proceed as follows:

 $ 1 $ -st stage:

- $ 1 $ -st monster appears;
- Monocarp cannot kill any monster;
- $ 1 $ alive monster deals $ 1 $ damage, so the total damage Monocarp got is $ 1 $ .

 $ 2 $ -nd stage: - $ 2 $ -nd monster appears;
- Monocarp kills $ 2 $ -nd monster (using elemental attack) and upgrades physical damage;
- $ 1 $ alive monster deals $ 1 $ damage, so the total damage Monocarp got is $ 2 $ .

 $ 3 $ -rd stage: - $ 3 $ -rd monster appears;
- Monocarp kills $ 1 $ -st monster (using physical attack) and upgrades elemental damage;
- $ 1 $ alive monster deals $ 1 $ damage, so the total damage Monocarp got is $ 3 $ .

 $ 4 $ -th stage: - $ 4 $ -th monster appears;
- Monocarp kills $ 4 $ -th monster (using elemental attack) and upgrades elemental damage;
- $ 1 $ alive monster deals $ 1 $ damage, so the total damage Monocarp got is $ 4 $ .

 $ 5 $ -th stage: - Monocarp kills $ 3 $ -rd monster (using elemental attack) and upgrades physical damage;
- all monsters are killed and the total damage Monocarp got is $ 4 $ .

## 样例 #1

### 输入

```
4
2 1 5 3
5 1 3 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
3 1 5 3
5 1 3 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3
1 1 1
1 2 3
```

### 输出

```
0
```

## 样例 #4

### 输入

```
8
6 4 1 2 3 5 1 6
6 3 2 1 2 3 4 3
```

### 输出

```
16
```

