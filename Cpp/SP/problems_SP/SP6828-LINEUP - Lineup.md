---
title: "LINEUP - Lineup"
layout: "post"
diff: 难度0
pid: SP6828
tag: []
---

# LINEUP - Lineup

## 题目描述

On June 13th team Germany has its first match in the FIFA world cup against team Australia. As the coach of team Germany, it is your duty to select the lineup for the game. Given this is your first game in the cup, naturally you want to make a good impression. Therefore you'd like to play with the strongest lineup possible.

![example image](https://cdn.luogu.com.cn/upload/vjudge_pic/SP6828/6365b0697fd54b0959c866fa1ef6d71053a36d5b.png)

You have already decided on the tactical formation you wish to use, so now you need to select the players who should fill each of the _11_ positions in the team. Your assistant has selected the _11_ strongest players from your squad, but this still leaves the question where to put which player.

Most players have a favoured position on the field where they are strongest, but some players are proficient in different positions. Your assistant has rated the playing strength of each of your _11_ players in each of the _11_ available positions in your formation, where a score of _100_ means that this is an ideal position for the player and a score of 0 means that the player is not suitable for that position at all. Find the lineup which maximises the sum of the playing strengths of your players for the positions you assigned them. All positions must be occupied, however, do not put players in positions they are not proficient with (i.e.\\ have a score of 0).

## 输入格式

The input consists of several test cases. The first line of input contains the number _C_ of test cases. For each case you are given _11_ lines, one for each player, where the _i_-th line contains _11_ integer numbers _s $ _{ij} $_  between 0 and _100_. _s $ _{ij} $_  describes the _i_-th player's strength on the _j_-th position. No player will be proficient in more than five different positions.

## 输出格式

For each test case output the maximum of the sum of player strengths over all possible lineups. Each test case result should go on a separate line. There will always be at least one valid lineup.

## 样例 #1

### 输入

```
1
100 0 0 0 0 0 0 0 0 0 0
0 80 70 70 60 0 0 0 0 0 0
0 40 90 90 40 0 0 0 0 0 0
0 40 85 85 33 0 0 0 0 0 0
0 70 60 60 85 0 0 0 0 0 0
0 0 0 0 0 95 70 60 60 0 0
0 45 0 0 0 80 90 50 70 0 0
0 0 0 0 0 40 90 90 40 70 0
0 0 0 0 0 0 50 70 85 50 0
0 0 0 0 0 0 66 60 0 80 80
0 0 0 0 0 0 50 50 0 90 88
```

### 输出

```
970
```

