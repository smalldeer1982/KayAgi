# 题目信息

# Digit Game

## 题目描述

Everyone knows that agents in Valorant decide, who will play as attackers, and who will play as defenders. To do that Raze and Breach decided to play $ t $ matches of a digit game...

In each of $ t $ matches of the digit game, a positive integer is generated. It consists of $ n $ digits. The digits of this integer are numerated from $ 1 $ to $ n $ from the highest-order digit to the lowest-order digit. After this integer is announced, the match starts.

Agents play in turns. Raze starts. In one turn an agent can choose any unmarked digit and mark it. Raze can choose digits on odd positions, but can not choose digits on even positions. Breach can choose digits on even positions, but can not choose digits on odd positions. The match ends, when there is only one unmarked digit left. If the single last digit is odd, then Raze wins, else Breach wins.

It can be proved, that before the end of the match (for every initial integer with $ n $ digits) each agent has an ability to make a turn, i.e. there is at least one unmarked digit, that stands on a position of required parity.

For each of $ t $ matches find out, which agent wins, if both of them want to win and play optimally.

## 说明/提示

In the first match no one can make a turn, the only digit left is $ 2 $ , it's even, so Breach wins.

In the second match the only digit left is $ 3 $ , it's odd, so Raze wins.

In the third match Raze can mark the last digit, after that Breach can only mark $ 0 $ . $ 1 $ will be the last digit left, it's odd, so Raze wins.

In the fourth match no matter how Raze plays, Breach can mark $ 9 $ , and in the end there will be digit $ 0 $ . It's even, so Breach wins.

## 样例 #1

### 输入

```
4
1
2
1
3
3
102
4
2069```

### 输出

```
2
1
1
2```

# AI分析结果

### 题目内容
# 数字游戏

## 题目描述
众所周知，《无畏契约》中的特工们会决定谁将扮演进攻方，谁将扮演防守方。为此，雷泽（Raze）和布蕾奇（Breach）决定进行 $t$ 场数字游戏……

在这 $t$ 场数字游戏的每一场中，都会生成一个正整数。它由 $n$ 个数字组成。这个整数的数字从最高位到最低位依次编号为 $1$ 到 $n$ 。在宣布这个整数之后，游戏开始。

特工们轮流进行操作。雷泽先开始。在一轮中，一名特工可以选择任何一个未标记的数字并标记它。雷泽只能选择奇数位置上的数字，但不能选择偶数位置上的数字。布蕾奇只能选择偶数位置上的数字，但不能选择奇数位置上的数字。当只剩下一个未标记的数字时，游戏结束。如果最后剩下的单个数字是奇数，那么雷泽获胜，否则布蕾奇获胜。

可以证明，在游戏结束之前（对于任何由 $n$ 个数字组成的初始整数），每个特工都有能力进行一轮操作，即至少有一个未标记的数字位于所需奇偶性的位置上。

对于这 $t$ 场游戏中的每一场，找出如果双方都想获胜并且都以最优策略进行游戏，哪名特工将获胜。

## 说明/提示
在第一场游戏中，没有人可以进行操作，剩下的唯一数字是 $2$，它是偶数，所以布蕾奇获胜。

在第二场游戏中，剩下的唯一数字是 $3$，它是奇数，所以雷泽获胜。

在第三场游戏中，雷泽可以标记最后一个数字，之后布蕾奇只能标记 $0$ 。剩下的最后一个数字将是 $1$，它是奇数，所以雷泽获胜。

在第四场游戏中，无论雷泽如何操作，布蕾奇都可以标记 $9$ ，最后剩下的数字将是 $0$ 。它是偶数，所以布蕾奇获胜。

## 样例 #1
### 输入
```
4
1
2
1
3
3
102
4
2069
```
### 输出
```
2
1
1
2
```

### 算法分类
数学

### 题解综合分析与结论
所有题解的核心思路都是基于游戏规则进行分类讨论。由于游戏规则限定了双方可选数字的位置奇偶性，且最终结果取决于最后剩下数字的奇偶性，所以根据数字总位数的奇偶性来判断最后剩下数字所在位置的奇偶性，进而通过判断该位置上是否存在对相应玩家有利的数字（奇数位上有奇数则雷泽胜，偶数位上有偶数则布蕾奇胜）得出结果。各题解在实现细节上略有不同，如统计数字的方式、代码风格等，但整体思路一致。

### 通用建议与扩展思路
解决此类博弈问题，关键在于依据游戏规则，深入分析双方的最优策略，并结合题目给定的条件，找出决定胜负的关键因素。对于同类型题，通常可从以下方向拓展：改变游戏规则，如改变可选数字的条件、获胜条件等；增加游戏轮次或复杂度；与其他知识点结合，如结合概率，让数字的生成具有一定概率分布等。

### 洛谷相似题目推荐
 - [P1118 数字三角形](https://www.luogu.com.cn/problem/P1118)：涉及数字的排列与决策，与本题类似，需考虑不同位置数字对结果的影响。
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过合理安排顺序以达到最优结果，与本题在寻找最优策略方面有相似思路。
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：同样是基于给定规则，通过分析找出最优排列顺序，与本题在策略分析上有共通之处。 

---
处理用时：29.16秒