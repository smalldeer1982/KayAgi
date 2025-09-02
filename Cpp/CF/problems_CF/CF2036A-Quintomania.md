---
title: "Quintomania"
layout: "post"
diff: 入门
pid: CF2036A
tag: ['模拟']
---

# Quintomania

## 题目描述

Boris Notkin composes melodies. He represents them as a sequence of notes, where each note is encoded as an integer from $ 0 $ to $ 127 $ inclusive. The interval between two notes $ a $ and $ b $ is equal to $ |a - b| $ semitones.

Boris considers a melody perfect if the interval between each two adjacent notes is either $ 5 $ semitones or $ 7 $ semitones.

After composing his latest melodies, he enthusiastically shows you his collection of works. Help Boris Notkin understand whether his melodies are perfect.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of melodies.

Each melody is described by two lines.

The first line contains an integer $ n $ ( $ 2 \leq n \leq 50 $ ) — the number of notes in the melody.

The second line contains $ n $ integers $ a_{1}, a_{2}, \dots, a_{n} $ ( $ 0 \leq a_{i} \leq 127 $ ) — the notes of the melody.

## 输出格式

For each melody, output "YES", if it is perfect; otherwise, output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 样例 #1

### 输入

```
8
2
114 109
2
17 10
3
76 83 88
8
38 45 38 80 85 92 99 106
5
63 58 65 58 65
8
117 124 48 53 48 43 54 49
5
95 102 107 114 121
10
72 77 82 75 70 75 68 75 68 75
```

### 输出

```
YES
YES
YES
NO
YES
NO
YES
YES
```

