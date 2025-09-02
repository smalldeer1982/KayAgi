# 题目信息

# Walking in the Rain

## 题目描述

In Berland the opposition is going to arrange mass walking on the boulevard. The boulevard consists of $ n $ tiles that are lain in a row and are numbered from $ 1 $ to $ n $ from right to left. The opposition should start walking on the tile number $ 1 $ and the finish on the tile number $ n $ . During the walk it is allowed to move from right to left between adjacent tiles in a row, and jump over a tile. More formally, if you are standing on the tile number $ i $ $ (i&lt;n-1) $ , you can reach the tiles number $ i+1 $ or the tile number $ i+2 $ from it (if you stand on the tile number $ n-1 $ , you can only reach tile number $ n $ ). We can assume that all the opposition movements occur instantaneously.

In order to thwart an opposition rally, the Berland bloody regime organized the rain. The tiles on the boulevard are of poor quality and they are rapidly destroyed in the rain. We know that the $ i $ -th tile is destroyed after $ a_{i} $ days of rain (on day $ a_{i} $ tile isn't destroyed yet, and on day $ a_{i}+1 $ it is already destroyed). Of course, no one is allowed to walk on the destroyed tiles! So the walk of the opposition is considered thwarted, if either the tile number $ 1 $ is broken, or the tile number $ n $ is broken, or it is impossible to reach the tile number $ n $ from the tile number $ 1 $ if we can walk on undestroyed tiles.

The opposition wants to gather more supporters for their walk. Therefore, the more time they have to pack, the better. Help the opposition to calculate how much time they still have and tell us for how many days the walk from the tile number $ 1 $ to the tile number $ n $ will be possible.

## 说明/提示

In the first sample the second tile gets destroyed after day three, and the only path left is $ 1→3→4 $ . After day five there is a two-tile gap between the first and the last tile, you can't jump over it.

In the second sample path $ 1→3→5 $ is available up to day five, inclusive. On day six the last tile is destroyed and the walk is thwarted.

## 样例 #1

### 输入

```
4
10 3 5 10
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
10 2 8 3 5
```

### 输出

```
5
```

# AI分析结果

### 题目内容
# 在雨中行走

## 题目描述
在伯兰，反对派打算在林荫大道上组织大规模游行。这条林荫大道由 $n$ 块瓷砖组成，它们排成一排，从右到左编号为 $1$ 到 $n$ 。反对派必须从编号为 $1$ 的瓷砖开始行走，并在编号为 $n$ 的瓷砖处结束。在行走过程中，允许在一排相邻瓷砖之间从右向左移动，也可以跳过一块瓷砖。更正式地说，如果你站在编号为 $i$（$i < n - 1$）的瓷砖上，你可以从它到达编号为 $i + 1$ 的瓷砖或编号为 $i + 2$ 的瓷砖（如果你站在编号为 $n - 1$ 的瓷砖上，你只能到达编号为 $n$ 的瓷砖）。我们可以假设反对派的所有移动都是瞬间发生的。

为了挫败反对派的集会，伯兰血腥政权安排了降雨。林荫大道上的瓷砖质量很差，在雨中会迅速损坏。我们知道第 $i$ 块瓷砖在降雨 $a_{i}$ 天后会损坏（在第 $a_{i}$ 天瓷砖还未损坏，而在第 $a_{i} + 1$ 天它已经损坏）。当然，任何人都不允许在损坏的瓷砖上行走！所以，如果编号为 $1$ 的瓷砖损坏，或者编号为 $n$ 的瓷砖损坏，或者如果在未损坏的瓷砖上无法从编号为 $1$ 的瓷砖到达编号为 $n$ 的瓷砖，那么反对派的游行就被认为是失败的。

反对派希望为他们的游行聚集更多的支持者。因此，他们准备的时间越多越好。帮助反对派计算他们还剩下多少时间，并告诉我们从编号为 $1$ 的瓷砖到编号为 $n$ 的瓷砖的游行还能持续多少天。

## 说明/提示
在第一个样例中，第二块瓷砖在第三天后损坏，剩下的唯一路径是 $1→3→4$ 。在第五天后，第一块和最后一块瓷砖之间有两块瓷砖的间隔，你无法跳过它。

在第二个样例中，路径 $1→3→5$ 直到第五天（包括第五天）都是可用的。在第六天，最后一块瓷砖损坏，游行失败。

## 样例 #1
### 输入
```
4
10 3 5 10
```
### 输出
```
5
```

## 样例 #2
### 输入
```
5
10 2 8 3 5
```
### 输出
```
5
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路基本一致，都基于贪心策略。要点在于考虑到只要有相邻两块瓷砖都损坏就无法通过，所以对于每对相邻瓷砖 $i$ 和 $i + 1$，其不能行走的时间为 $\max(a_i, a_{i + 1})$ ，然后从这些时间中找出最小值。同时，还需考虑起点和终点提前损坏的特殊情况，即最终答案要与 $a_1$ 和 $a_n$ 取最小值。各题解在思路清晰度和代码风格上略有差异，但整体算法实现相近。

### 通用建议与扩展思路
对于此类贪心问题，关键在于准确分析出影响结果的关键因素（如本题中相邻瓷砖的损坏时间），并基于此设计贪心策略。相似类型的题目通常围绕如何在一系列条件限制下，通过合理选择（如本题选择可通行的瓷砖）来达到最优结果。可以通过多练习贪心相关题目，加深对贪心策略的理解和运用能力。

### 推荐题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
2. [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
3. [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123) 

---
处理用时：26.47秒