---
title: "Name That Tune"
layout: "post"
diff: 普及+/提高
pid: CF498B
tag: []
---

# Name That Tune

## 题目描述

It turns out that you are a great fan of rock band AC/PE. Peter learned that and started the following game: he plays the first song of the list of $ n $ songs of the group, and you have to find out the name of the song. After you tell the song name, Peter immediately plays the following song in order, and so on.

The $ i $ -th song of AC/PE has its recognizability $ p_{i} $ . This means that if the song has not yet been recognized by you, you listen to it for exactly one more second and with probability of $ p_{i} $ percent you recognize it and tell it's name. Otherwise you continue listening it. Note that you can only try to guess it only when it is integer number of seconds after the moment the song starts playing.

In all AC/PE songs the first words of chorus are the same as the title, so when you've heard the first $ t_{i} $ seconds of $ i $ -th song and its chorus starts, you immediately guess its name for sure.

For example, in the song Highway To Red the chorus sounds pretty late, but the song has high recognizability. In the song Back In Blue, on the other hand, the words from the title sound close to the beginning of the song, but it's hard to name it before hearing those words. You can name both of these songs during a few more first seconds.

Determine the expected number songs of you will recognize if the game lasts for exactly $ T $ seconds (i. e. you can make the last guess on the second $ T $ , after that the game stops).

If all songs are recognized faster than in $ T $ seconds, the game stops after the last song is recognized.

## 输入格式

The first line of the input contains numbers $ n $ and $ T $ ( $ 1<=n<=5000 $ , $ 1<=T<=5000 $ ), separated by a space. Next $ n $ lines contain pairs of numbers $ p_{i} $ and $ t_{i} $ ( $ 0<=p_{i}<=100 $ , $ 1<=t_{i}<=T $ ). The songs are given in the same order as in Petya's list.

## 输出格式

Output a single number — the expected number of the number of songs you will recognize in $ T $ seconds. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
2 2
50 2
10 1

```

### 输出

```
1.500000000

```

## 样例 #2

### 输入

```
2 2
0 2
100 2

```

### 输出

```
1.000000000

```

## 样例 #3

### 输入

```
3 3
50 3
50 2
25 2

```

### 输出

```
1.687500000

```

## 样例 #4

### 输入

```
2 2
0 2
0 2

```

### 输出

```
1.000000000

```

