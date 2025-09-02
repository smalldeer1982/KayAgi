---
title: "Music in Car"
layout: "post"
diff: 省选/NOI-
pid: CF746F
tag: []
---

# Music in Car

## 题目描述

Sasha reaches the work by car. It takes exactly $ k $ minutes. On his way he listens to music. All songs in his playlist go one by one, after listening to the $ i $ -th song Sasha gets a pleasure which equals $ a_{i} $ . The $ i $ -th song lasts for $ t_{i} $ minutes.

Before the beginning of his way Sasha turns on some song $ x $ and then he listens to the songs one by one: at first, the song $ x $ , then the song $ (x+1) $ , then the song number $ (x+2) $ , and so on. He listens to songs until he reaches the work or until he listens to the last song in his playlist.

Sasha can listen to each song to the end or partly.

In the second case he listens to the song for integer number of minutes, at least half of the song's length. Formally, if the length of the song equals $ d $ minutes, Sasha listens to it for no less than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF746F/a0138c33f01c951ba371aceb046ff51db6674fec.png) minutes, then he immediately switches it to the next song (if there is such). For example, if the length of the song which Sasha wants to partly listen to, equals $ 5 $ minutes, then he should listen to it for at least $ 3 $ minutes, if the length of the song equals $ 8 $ minutes, then he should listen to it for at least $ 4 $ minutes.

It takes no time to switch a song.

Sasha wants to listen partly no more than $ w $ songs. If the last listened song plays for less than half of its length, then Sasha doesn't get pleasure from it and that song is not included to the list of partly listened songs. It is not allowed to skip songs. A pleasure from a song does not depend on the listening mode, for the $ i $ -th song this value equals $ a_{i} $ .

Help Sasha to choose such $ x $ and no more than $ w $ songs for partial listening to get the maximum pleasure. Write a program to find the maximum pleasure Sasha can get from the listening to the songs on his way to the work.

## 输入格式

The first line contains three integers $ n $ , $ w $ and $ k $ ( $ 1<=w<=n<=2·10^{5} $ , $ 1<=k<=2·10^{9} $ ) — the number of songs in the playlist, the number of songs Sasha can listen to partly and time in minutes which Sasha needs to reach work.

The second line contains $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{4} $ ), where $ a_{i} $ equals the pleasure Sasha gets after listening to the $ i $ -th song.

The third line contains $ n $ positive integers $ t_{1},t_{2},...,t_{n} $ ( $ 2<=t_{i}<=10^{4} $ ), where $ t_{i} $ equals the length of the $ i $ -th song in minutes.

## 输出格式

Print the maximum pleasure Sasha can get after listening to the songs on the way to work.

## 说明/提示

In the first example Sasha needs to start listening from the song number $ 2 $ . He should listen to it partly (for $ 4 $ minutes), then listen to the song number $ 3 $ to the end (for $ 3 $ minutes) and then partly listen to the song number $ 4 $ (for $ 3 $ minutes). After listening to these songs Sasha will get pleasure which equals $ 4+3+5=12 $ . Sasha will not have time to listen to the song number $ 5 $ because he will spend $ 4+3+3=10 $ minutes listening to songs number $ 2 $ , $ 3 $ and $ 4 $ and only $ 1 $ minute is left after that.

## 样例 #1

### 输入

```
7 2 11
3 4 3 5 1 4 6
7 7 3 6 5 3 9

```

### 输出

```
12

```

## 样例 #2

### 输入

```
8 4 20
5 6 4 3 7 5 4 1
10 12 5 12 14 8 5 8

```

### 输出

```
19

```

## 样例 #3

### 输入

```
1 1 5
6
9

```

### 输出

```
6

```

## 样例 #4

### 输入

```
1 1 3
4
7

```

### 输出

```
0

```

