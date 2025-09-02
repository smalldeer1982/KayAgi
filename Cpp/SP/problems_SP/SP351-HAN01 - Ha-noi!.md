---
title: "HAN01 - Ha-noi!"
layout: "post"
diff: 难度0
pid: SP351
tag: []
---

# HAN01 - Ha-noi!

## 题目描述

Little Sabrina loves solving puzzles. Last week she got a new puzzle: The "Tower of Hanoi" puzzle. This puzzle is based on an old legend: "The temple priests of hanoi have to transfer a tower consisting of 64 fragile disks of gold from one part of the temple to another, one disk at a time. The disks are arranged in order, no two of them the same size, with the largest on the bottom and the smallest on top. Because of their fragility, a larger disk may never be placed on a smaller one, and there is only one intermediate location where disks can be temporarily placed. It is said that before the priests complete their task the temple will crumble into dust and the world will vanish in a clap of thunder." Sabrina reconstructed the problem with some coins of different size. She solved the puzzle for three coins in 7 steps, for four coins in 15 steps,... after solving the problem with 7 coins she had the hang of it. Yesterday she started to solve the puzzle with 31 coins and her optimal strategy. After hours of moving coins from one pile to the other she was very tired and went to bed. This was a bad idea! Her little brother Robin discovered the towers of coins and - whoops! - threw it on the floor. Then he noticed a sheet of paper: "Don't touch this towers! Steps: 16543". "Oh no!" Robin has to reconstuct the tower because his sister can get very, very angry... Your task is to help Robin to reconstruct the towers. Sabrina started the game with all disks on peg number one and her goal was to move the disks to peg number two. She used her optimal strategy and noted the number of steps she had done.

## 输入格式

The first line of input contains one integer t: The number of testcases. t lines follow. Each line contains two integers n (2< n< 61) and k (0< k< 2 $ ^{n} $ ). n is the number of disks of the hanoi puzzle and k the number of steps Sabrina had done. **Please be careful, the number k can be very large, it may not fit in a 32 bit integer.**

## 输出格式

Output the reconstructed configuration of the towers after k steps. For each testcase output three lines. One for each tower. Each line consists of the tower identifier (1,2,3) a colon, one space and the disk numbers (n,n-1,...,2,1) which are seperated by a '|'-character.

## 样例 #1

### 输入

```
3
3 6
32 889397450
31 16543
```

### 输出

```
1: 1
2: 3|2
3:
1: 32|31|28|25|18|17|14|3
2: 30|29|26|13|12|11|10|9|6|5|2
3: 27|24|23|22|21|20|19|16|15|8|7|4|1
1: 31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|7|6
2: 15|8|5|4|3|2|1
3: 14|13|12|11|10|9
```

