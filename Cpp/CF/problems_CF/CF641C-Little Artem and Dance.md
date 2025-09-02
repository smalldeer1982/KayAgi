---
title: "Little Artem and Dance"
layout: "post"
diff: 普及+/提高
pid: CF641C
tag: []
---

# Little Artem and Dance

## 题目描述

Little Artem is fond of dancing. Most of all dances Artem likes rueda — Cuban dance that is danced by pairs of boys and girls forming a circle and dancing together.

More detailed, there are $ n $ pairs of boys and girls standing in a circle. Initially, boy number $ 1 $ dances with a girl number $ 1 $ , boy number $ 2 $ dances with a girl number $ 2 $ and so on. Girls are numbered in the clockwise order. During the dance different moves are announced and all pairs perform this moves. While performing moves boys move along the circle, while girls always stay at their initial position. For the purpose of this problem we consider two different types of moves:

1. Value $ x $ and some direction are announced, and all boys move $ x $ positions in the corresponding direction.
2. Boys dancing with even-indexed girls swap positions with boys who are dancing with odd-indexed girls. That is the one who was dancing with the girl $ 1 $ swaps with the one who was dancing with the girl number $ 2 $ , while the one who was dancing with girl number $ 3 $ swaps with the one who was dancing with the girl number $ 4 $ and so one. It's guaranteed that $ n $ is even.

Your task is to determine the final position of each boy.

## 输入格式

The first line of the input contains two integers $ n $ and $ q $ ( $ 2<=n<=1000000 $ , $ 1<=q<=2000000 $ ) — the number of couples in the rueda and the number of commands to perform, respectively. It's guaranteed that $ n $ is even.

Next $ q $ lines contain the descriptions of the commands. Each command has type as the integer $ 1 $ or $ 2 $ first. Command of the first type is given as $ x $ ( $ -n<=x<=n $ ), where $ 0<=x<=n $ means all boys moves $ x $ girls in clockwise direction, while $ -x $ means all boys move $ x $ positions in counter-clockwise direction. There is no other input for commands of the second type.

## 输出格式

Output $ n $ integers, the $ i $ -th of them should be equal to the index of boy the $ i $ -th girl is dancing with after performing all $ q $ moves.

## 样例 #1

### 输入

```
6 3
1 2
2
1 2

```

### 输出

```
4 3 6 5 2 1

```

## 样例 #2

### 输入

```
2 3
1 1
2
1 -2

```

### 输出

```
1 2

```

## 样例 #3

### 输入

```
4 2
2
1 3

```

### 输出

```
1 4 3 2

```

