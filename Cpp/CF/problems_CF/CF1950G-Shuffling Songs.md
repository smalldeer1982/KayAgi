---
title: "Shuffling Songs"
layout: "post"
diff: 普及+/提高
pid: CF1950G
tag: ['动态规划 DP', '状态合并']
---

# Shuffling Songs

## 题目描述

Vladislav 有一个由 $n$ 首歌组成的播放列表，编号从 $1$ 到 $n$。歌曲 $i$ 属于流派 $g_i$ 并由作者 $w_i$ 创作。他希望以这样一种方式制作播放列表：每对相邻的歌曲要么有相同的作者，要么属于相同的流派（或两者兼有）。他称这样的播放列表为激动人心的。 $g_i$ 和 $w_i$ 都是长度不超过 $10^4$ 的字符串。

但是有可能不总是能使用所有歌曲制作出激动人心的播放列表，因此洗牌过程分为两步。首先，移除一些数量（可能为零）的歌曲，然后重新排列剩余的歌曲使播放列表激动人心。

由于 Vladislav 不喜欢从他的播放列表中移除歌曲，他希望尽可能少地进行移除。帮助他找出为了能重新排列剩余歌曲使播放列表激动人心而需要进行的最少移除数量。

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 1000$） ——表示多少组数据。

每个测试用例的第一行包含一个单独的整数 $n（1 \le n \le 16）$表示原始播放列表中的歌曲数量。

接着是 $n$ 行，第 $i$ 行包含两个由小写字母组成的字符串 $g_i$ 和 $w_i （1 \leq |g_i|, |w_i| \leq 10^4）$  ——第 $i$ 首歌的流派和作者。其中 $|g_i|$ 和 $|w_i|$ 是字符串的长度。

所有测试用例中 $2^n$ 的总和不超过 $2^{16}$。

所有测试用例中 $|g_i| + |w_i|$ 的总和不超过 $4 \times 10^5$。

## 输出格式

对于每个测试用例，输出一个整数，为使得结果的播放列表可以激动人心所必需的最少移除数量。

## 样例 #1

### 输入

```
4
1
pop taylorswift
4
electronic themotans
electronic carlasdreams
pop themotans
pop irinarimes
7
rap eminem
rap drdre
rap kanyewest
pop taylorswift
indierock arcticmonkeys
indierock arcticmonkeys
punkrock theoffspring
4
a b
c d
e f
g h
```

### 输出

```
0
0
4
3
```

