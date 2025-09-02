---
title: "SHUFFLEN - Shuffle Music"
layout: "post"
diff: 难度0
pid: SP7333
tag: []
---

# SHUFFLEN - Shuffle Music

## 题目描述

我家到办公室距离很远，每天我都坐公交上班，这要花费不少时间。而且由于交通拥堵，路上耗时并不固定。为了充分利用这段时间，我随身携带音乐播放器。我的音乐播放器有一个“随机播放”模式。在这个模式下，播放器会随机选择一首当前会话中没听过的曲目（**在下次随机播放前**），开始播放。它会这样继续下去，直到我停止播放，或者已经听完所有曲目。

在这个问题中，你可以假设所有曲目的时长相等。播放器通过维护一个播放记录来随机选择曲目。即如果我现在听了一首歌，那么在下一个随机播放会话中，这首曲目会被标记为已播放。

**另外，在停止后重新播放下一首时，**播放器选择已经听过的曲目的概率是未曾听过的两倍。我每天早上去上班，晚上回家，各进行一次随机播放。

从我家到办公室的时间至少为 $p$ 分钟，最多为 $q$ 分钟，且该时长总是整数。你可以假设所有可能的到达时间都等概率分布（比如，如果 $p = 2$ 且 $q = 4$，那么在 $t$ 分钟内到达办公室的概率 $P(t)$ 满足 $P(2) = P(3) = P(4)$）。如果每首曲目播放时长均为 1 分钟，平均需要多少天才能听完所有曲目？

## 输入格式

输入的第一行包含一个整数 $T$，表示测试用例的数量。每个测试用例包含 5 个整数：$N, p_1, q_1, p_2, q_2 (0 < N \le 100, 0 \le p_1 \le q_1 \le 100, 0 \le p_2 \le q_2 \le 100)$，其中 $N$ 是曲目总数，$p_1, q_1$ 是白天的最短和最长听歌时间，$p_2, q_2$ 是晚上的最短和最长听歌时间。

## 输出格式

对于每个测试用例，输出测试用例编号，后接听完所有曲目所需的平均天数。如果无法完成，输出 `IMPOSSIBLE`。

评测时会忽略至多 $10^{-6}$ 的浮点误差。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
\n\n11\n1 0 1 0 1\n20 0 26 1 3
10 11 21 0 0
64 0 0 1 23
48 0 0 0 0
42 18 29 6 13
29 19 25 0 0
32 0 0 8 27
75 0 1 0 1
75 0 1 0 0
75 0 0 0 1
```

### 输出

```
\n
Case 1: 1.3333333\nCase 2: 3.1143655
Case 3: 1.0000000
Case 4: 39.6303478
Case 5: IMPOSSIBLE
Case 6: 7.1950023
Case 7: 4.7682679
Case 8: 8.1514607
Case 9: 660.4533446
Case 10: 1320.4066892
Case 11: 1320.4066892\n\nHint\n\nCalculate  P [n] [ rest ] [q] [next].  It is in this session, we have not heard the song in each n songs played,\nwith "rest" number of songs never heard,  with q minutes played so far, \n the probability of "next" song been played for the first time.  Dp by this O (N ^ 2q ^ 2).\nSum over [0, q] to get  P [n] [rest] [qsum] [next], so we can use subtraction to get interval sums.\n\nNow let 0 be day, 1 by night, then we compute dp[0][rest], dp[1] [rest], the expected number of days it takes to\nfinish all the songs if only considering day or night. dp [0] [rest] is [0, rest) of dp [1] [rest] and P [n] [rest] [qsum] [next].\nUsing O ( rest ) can be calculated as as X = dp[0][rest], Y = dp[1] [rest], then {X = a Y + c, Y = b X + d}.\nSolving this, and done.\nIn the base case with rest=1, use infinite geometric series to compute overall O (TN ^ 2 + N ^ 2q ^ 2).\n\n
```

