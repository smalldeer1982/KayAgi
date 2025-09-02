---
title: "Dima and Magic Guitar"
layout: "post"
diff: 提高+/省选-
pid: CF366E
tag: []
---

# Dima and Magic Guitar

## 题目描述

Dima loves Inna very much. He decided to write a song for her. Dima has a magic guitar with $ n $ strings and $ m $ frets. Dima makes the guitar produce sounds like that: to play a note, he needs to hold one of the strings on one of the frets and then pull the string. When Dima pulls the $ i $ -th string holding it on the $ j $ -th fret the guitar produces a note, let's denote it as $ a_{ij} $ . We know that Dima's guitar can produce $ k $ distinct notes. It is possible that some notes can be produced in multiple ways. In other words, it is possible that $ a_{ij}=a_{pq} $ at $ (i,j)≠(p,q) $ .

Dima has already written a song — a sequence of $ s $ notes. In order to play the song, you need to consecutively produce the notes from the song on the guitar. You can produce each note in any available way. Dima understood that there are many ways to play a song and he wants to play it so as to make the song look as complicated as possible (try to act like Cobein).

We'll represent a way to play a song as a sequence of pairs $ (x_{i},y_{i}) $ $ (1<=i<=s) $ , such that the $ x_{i} $ -th string on the $ y_{i} $ -th fret produces the $ i $ -th note from the song. The complexity of moving between pairs $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF366E/129d9e481d290acfa8db6ee14b7e888ae0d5095a.png) + ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF366E/0b7383bdbf6df32e7843f9a60054de19cedafc98.png). The complexity of a way to play a song is the maximum of complexities of moving between adjacent pairs.

Help Dima determine the maximum complexity of the way to play his song! The guy's gotta look cool!

## 输入格式

The first line of the input contains four integers $ n $ , $ m $ , $ k $ and $ s $ $ (1<=n,m<=2000,1<=k<=9,2<=s<=10^{5}) $ .

Then follow $ n $ lines, each containing $ m $ integers $ a_{ij} $ $ (1<=a_{ij}<=k) $ . The number in the $ i $ -th row and the $ j $ -th column ( $ a_{ij} $ ) means a note that the guitar produces on the $ i $ -th string and the $ j $ -th fret.

The last line of the input contains $ s $ integers $ q_{i} $ $ (1<=q_{i}<=k) $ — the sequence of notes of the song.

## 输出格式

In a single line print a single number — the maximum possible complexity of the song.

## 样例 #1

### 输入

```
4 6 5 7
3 1 2 2 3 1
3 2 2 2 5 5
4 2 2 2 5 3
3 2 2 1 4 3
2 3 1 4 1 5 1

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4 4 9 5
4 7 9 5
1 2 1 7
8 3 4 9
5 7 7 2
7 1 9 2 5

```

### 输出

```
4

```

