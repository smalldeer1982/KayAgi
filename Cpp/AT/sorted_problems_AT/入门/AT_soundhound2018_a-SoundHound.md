---
title: "SoundHound"
layout: "post"
diff: 入门
pid: AT_soundhound2018_a
tag: ['字符串']
---

# SoundHound

## 题目描述

[problemUrl]: https://atcoder.jp/contests/soundhound2018/tasks/soundhound2018_a

kenkooooさんはSoundHound社で働いています。彼は会社の知名度を上げるため、SoundHoundに名前が似ている言葉を見つけてマーケティングを行うことにしました。手始めに、$ 2 $ 単語からなる言葉で、それぞれの単語の頭文字を順につなげると`SH`となるような単語を似ていると見なすことにしました。

あなたの仕事は、$ 2 $ 単語 $ X $ $ Y $ からなる言葉が与えられたとき、頭文字を順につなげると`SH`となるか判定することです。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ X $ $ Y $

## 输出格式

与えられた言葉がSoundHoundと似ている場合 `YES` と、そうでない場合 `NO` と出力せよ。

## 说明/提示

### 制約

- 与えられる単語は英大文字からなる
- 単語の長さは $ 1 $ 以上 $ 10 $ 以下である

## 样例 #1

### 输入

```
SAINT HELENA
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
SOUND HOUND
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
SOUND SPIDER
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
S H
```

### 输出

```
YES
```

## 样例 #5

### 输入

```
X Y
```

### 输出

```
NO
```

