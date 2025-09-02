# 题目信息

# Need For Brake

## 题目描述

Vasya plays the Need For Brake. He plays because he was presented with a new computer wheel for birthday! Now he is sure that he will win the first place in the championship in his favourite racing computer game!

 $ n $ racers take part in the championship, which consists of a number of races. After each race racers are arranged from place first to $ n $ -th (no two racers share the same place) and first $ m $ places are awarded. Racer gains $ b_{i} $ points for $ i $ -th awarded place, which are added to total points, obtained by him for previous races. It is known that current summary score of racer $ i $ is $ a_{i} $ points. In the final standings of championship all the racers will be sorted in descending order of points. Racers with an equal amount of points are sorted by increasing of the name in lexicographical order.

Unfortunately, the championship has come to an end, and there is only one race left. Vasya decided to find out what the highest and lowest place he can take up as a result of the championship.

## 样例 #1

### 输入

```
3
teama 10
teamb 20
teamc 40
2
10 20
teama
```

### 输出

```
2 3```

## 样例 #2

### 输入

```
2
teama 10
teamb 10
2
10 10
teamb
```

### 输出

```
2 2```

# AI分析结果

### 题目内容
# 刹车需求

## 题目描述
瓦夏玩《刹车需求》这款游戏。他玩这个游戏是因为生日时收到了一个新的电脑方向盘！现在他确信自己能在最喜欢的赛车电脑游戏锦标赛中获得第一名！

锦标赛有 $n$ 名赛车手参赛，锦标赛由若干场比赛组成。每场比赛结束后，赛车手们会按名次从第一名排到第 $n$ 名（没有两名赛车手名次相同），前 $m$ 名会获得奖励。赛车手获得第 $i$ 个奖励名次会得到 $b_{i}$ 分，这些分数会加到他之前比赛获得的总分数中。已知赛车手 $i$ 当前的总分数是 $a_{i}$ 分。在锦标赛的最终排名中，所有赛车手将按分数从高到低排序。分数相同的赛车手按名字的字典序从小到大排序。

不幸的是，锦标赛已经接近尾声，只剩下一场比赛了。瓦夏想知道，作为锦标赛的结果，他能获得的最高和最低名次分别是多少。

## 样例 #1
### 输入
```
3
teama 10
teamb 20
teamc 40
2
10 20
teama
```
### 输出
```
2 3
```

## 样例 #2
### 输入
```
2
teama 10
teamb 10
2
10 10
teamb
```
### 输出
```
2 2
```

### 算法分类
模拟

### 综合分析与结论
由于暂无题解，无法进行题解间的对比分析。对于该题，核心在于模拟最后一场比赛不同得分情况下，目标赛车手在所有赛车手中的排名变化。需要考虑其他赛车手的现有分数以及最后一场比赛可能获得的分数，通过对所有可能情况进行模拟来确定目标赛车手的最高和最低排名。

### 通用建议与扩展思路
1. **通用建议**：
    - 首先，应明确如何表示每个赛车手的信息，比如可以使用结构体来存储赛车手的名字、当前分数等。
    - 对于最后一场比赛的得分情况，要全面考虑目标赛车手获得不同名次（前 $m$ 名）时的分数变化，以及其他赛车手可能获得的名次及分数变化。
    - 在计算排名时，要注意分数相同情况下按字典序排序的规则，可以先根据分数排序，分数相同的再按字典序二次排序。
2. **扩展思路**：
    - 可以增加比赛的场次，使问题更加复杂，需要考虑多场比赛后排名的变化情况。
    - 改变奖励分数的设置规则，比如根据比赛难度动态调整奖励分数，增加问题的挑战性。

### 洛谷相似题目推荐
1. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)：同样是通过模拟操作来解决问题，考察对实际问题的模拟和逻辑处理能力。
2. [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：需要模拟开关灯的过程，与本题类似，都是对一系列操作和状态变化的模拟。
3. [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：通过模拟小玉游泳的过程来解决问题，锻炼模拟实际场景的编程能力。 

---
处理用时：33.53秒