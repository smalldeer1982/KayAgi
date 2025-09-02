---
title: "Music"
layout: "post"
diff: 普及/提高-
pid: CF569A
tag: []
---

# Music

## 题目描述

Little Lesha loves listening to music via his smartphone. But the smartphone doesn't have much memory, so Lesha listens to his favorite songs in a well-known social network InTalk.

Unfortunately, internet is not that fast in the city of Ekaterinozavodsk and the song takes a lot of time to download. But Lesha is quite impatient. The song's duration is $ T $ seconds. Lesha downloads the first $ S $ seconds of the song and plays it. When the playback reaches the point that has not yet been downloaded, Lesha immediately plays the song from the start (the loaded part of the song stays in his phone, and the download is continued from the same place), and it happens until the song is downloaded completely and Lesha listens to it to the end. For $ q $ seconds of real time the Internet allows you to download $ q-1 $ seconds of the track.

Tell Lesha, for how many times he will start the song, including the very first start.

## 输入格式

The single line contains three integers $ T,S,q $ ( $ 2<=q<=10^{4} $ , $ 1<=S&lt;T<=10^{5} $ ).

## 输出格式

Print a single integer — the number of times the song will be restarted.

## 说明/提示

In the first test, the song is played twice faster than it is downloaded, which means that during four first seconds Lesha reaches the moment that has not been downloaded, and starts the song again. After another two seconds, the song is downloaded completely, and thus, Lesha starts the song twice.

In the second test, the song is almost downloaded, and Lesha will start it only once.

In the third sample test the download finishes and Lesha finishes listening at the same moment. Note that song isn't restarted in this case.

## 样例 #1

### 输入

```
5 2 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 4 7

```

### 输出

```
1

```

## 样例 #3

### 输入

```
6 2 3

```

### 输出

```
1

```

