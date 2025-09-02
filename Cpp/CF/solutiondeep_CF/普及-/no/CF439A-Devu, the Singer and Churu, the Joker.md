# 题目信息

# Devu, the Singer and Churu, the Joker

## 题目描述

Devu is a renowned classical singer. He is invited to many big functions/festivals. Recently he was invited to "All World Classical Singing Festival". Other than Devu, comedian Churu was also invited.

Devu has provided organizers a list of the songs and required time for singing them. He will sing $ n $ songs, $ i^{th} $ song will take $ t_{i} $ minutes exactly.

The Comedian, Churu will crack jokes. All his jokes are of 5 minutes exactly.

People have mainly come to listen Devu. But you know that he needs rest of 10 minutes after each song. On the other hand, Churu being a very active person, doesn't need any rest.

You as one of the organizers should make an optimal sсhedule for the event. For some reasons you must follow the conditions:

- The duration of the event must be no more than $ d $ minutes;
- Devu must complete all his songs;
- With satisfying the two previous conditions the number of jokes cracked by Churu should be as many as possible.

If it is not possible to find a way to conduct all the songs of the Devu, output -1. Otherwise find out maximum number of jokes that Churu can crack in the grand event.

## 说明/提示

Consider the first example. The duration of the event is $ 30 $ minutes. There could be maximum $ 5 $ jokes in the following way:

- First Churu cracks a joke in $ 5 $ minutes.
- Then Devu performs the first song for $ 2 $ minutes.
- Then Churu cracks $ 2 $ jokes in $ 10 $ minutes.
- Now Devu performs second song for $ 2 $ minutes.
- Then Churu cracks $ 2 $ jokes in $ 10 $ minutes.
- Now finally Devu will perform his last song in $ 1 $ minutes.

Total time spent is $ 5+2+10+2+10+1=30 $ minutes.

Consider the second example. There is no way of organizing Devu's all songs. Hence the answer is -1.

## 样例 #1

### 输入

```
3 30
2 2 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 20
2 1 1
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
# Devu，歌手和 Churu，小丑

## 题目描述
Devu 是一位著名的古典歌手。他受邀参加许多大型活动和节日。最近，他受邀参加“世界古典歌唱节”。除了 Devu，喜剧演员 Churu 也受到了邀请。

Devu 向组织者提供了一份歌曲清单以及演唱这些歌曲所需的时间。他将演唱 $n$ 首歌曲，第 $i$ 首歌曲恰好需要 $t_{i}$ 分钟。

喜剧演员 Churu 会讲笑话。他所有的笑话恰好都持续 5 分钟。

人们主要是来听 Devu 唱歌的。但是你知道，他每唱完一首歌需要休息 10 分钟。另一方面，Churu 是一个非常活跃的人，不需要任何休息。

作为组织者之一，你应该为活动制定一个最优的日程安排。由于某些原因，你必须遵循以下条件：
- 活动的持续时间不得超过 $d$ 分钟；
- Devu 必须演唱完所有歌曲；
- 在满足前两个条件的前提下，Churu 讲的笑话数量应尽可能多。

如果无法找到一种方式来安排 Devu 的所有歌曲，输出 -1。否则，找出 Churu 在盛大活动中最多可以讲的笑话数量。

## 说明/提示
考虑第一个样例。活动的持续时间为 30 分钟。按照以下方式最多可以有 5 个笑话：
- 首先，Churu 讲一个笑话，用时 5 分钟。
- 然后，Devu 演唱第一首歌曲，用时 2 分钟。
- 接着，Churu 讲 2 个笑话，用时 10 分钟。
- 现在，Devu 演唱第二首歌曲，用时 2 分钟。
- 然后，Churu 讲 2 个笑话，用时 10 分钟。
- 最后，Devu 演唱最后一首歌曲，用时 1 分钟。
总用时为 $5 + 2 + 10 + 2 + 10 + 1 = 30$ 分钟。

考虑第二个样例。没有办法安排 Devu 的所有歌曲。因此，答案是 -1。

## 样例 #1
### 输入
```
3 30
2 2 1
```
### 输出
```
5
```

## 样例 #2
### 输入
```
3 20
2 1 1
```
### 输出
```
-1
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是先计算 Devu 演唱所有歌曲及休息所需的总时间，然后判断该时间是否超过活动总时长 $d$。若超过则无法完成演唱，输出 -1；若未超过，则计算剩余时间，进而得出 Churu 最多能讲的笑话数量。

各题解的算法要点主要集中在计算 Devu 的总用时和判断能否完成演唱，以及计算笑话数量上。解决的难点在于正确处理 Devu 唱歌和休息的时间关系，以及合理分配剩余时间给 Churu 讲笑话。

### 题解评分
- 李至擎：4 星。思路清晰，代码简洁明了，直接计算出结果，可读性高。
- 封禁用户：3 星。思路正确，使用了三目运算符增加代码灵活性，但整体逻辑稍显复杂。
- Lish_Xizse：3 星。步骤详细，对解题过程进行了分步讲解，但代码和思路中规中矩。
- naroanah：3 星。思路简洁，但没有给出代码实现。
- thomas_zjl：3 星。思路清晰，代码实现基本正确，但使用了 `#include<bits/stdc++.h>` 可能存在兼容性问题。
- k3v1n070828：3 星。思路独特，从休息期间和剩余时间分别计算笑话数量，但代码逻辑稍复杂。
- sysu_yzc：3 星。思路正确，代码实现基本正确，但公式推导可能会让人理解困难。
- CobaltChloride：3 星。代码实现较为巧妙，但初始化和逻辑处理可能会让人困惑。

### 所选题解
- 李至擎（4 星）：关键亮点在于思路简洁直接，代码可读性高，直接通过计算得出结果，没有复杂的逻辑处理。

### 关键思路或技巧
- 先计算 Devu 演唱所有歌曲及休息的总时间，判断是否能完成演唱。
- 若能完成演唱，用活动总时长减去 Devu 唱歌的总时间，再除以 5 得到 Churu 最多能讲的笑话数量。

### 拓展思路
同类型题可能会改变活动的限制条件，如增加不同类型的表演，每个表演有不同的时间和休息要求，或者改变笑话的时长等。解题思路仍然是模拟整个活动过程，合理分配时间。

### 推荐题目
- [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)：基础的输入输出题目，可用于熟悉洛谷的做题环境。
- [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：简单的模拟题目，通过模拟小玉游泳的过程来计算结果。
- [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：模拟陶陶摘苹果的过程，判断陶陶能摘到多少苹果。

### 个人心得
k3v1n070828 提到样例的解释给了很大帮助，通过解释发现每次 Devu 休息时 Churu 都可以讲两个笑话，这启示我们在解题时要充分利用样例，从中寻找解题的思路和规律。 

---
处理用时：33.29秒