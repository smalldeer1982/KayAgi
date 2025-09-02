# 题目信息

# Playing Cubes

## 题目描述

Petya and Vasya decided to play a little. They found $ n $ red cubes and $ m $ blue cubes. The game goes like that: the players take turns to choose a cube of some color (red or blue) and put it in a line from left to right (overall the line will have $ n+m $ cubes). Petya moves first. Petya's task is to get as many pairs of neighbouring cubes of the same color as possible. Vasya's task is to get as many pairs of neighbouring cubes of different colors as possible.

The number of Petya's points in the game is the number of pairs of neighboring cubes of the same color in the line, the number of Vasya's points in the game is the number of neighbouring cubes of the different color in the line. Your task is to calculate the score at the end of the game (Petya's and Vasya's points, correspondingly), if both boys are playing optimally well. To "play optimally well" first of all means to maximize the number of one's points, and second — to minimize the number of the opponent's points.

## 说明/提示

In the first test sample the optimal strategy for Petya is to put the blue cube in the line. After that there will be only red cubes left, so by the end of the game the line of cubes from left to right will look as \[blue, red, red, red\]. So, Petya gets 2 points and Vasya gets 1 point.

If Petya would choose the red cube during his first move, then, provided that both boys play optimally well, Petya would get 1 point and Vasya would get 2 points.

## 样例 #1

### 输入

```
3 1
```

### 输出

```
2 1
```

## 样例 #2

### 输入

```
2 4
```

### 输出

```
3 2
```

# AI分析结果



【题目翻译】
# 玩积木

## 题目描述

Petya和Vasya决定玩一个小游戏。他们找到$n$个红色积木和$m$个蓝色积木。游戏规则如下：玩家轮流选择某种颜色（红或蓝）的积木，从左到右摆成一列（最终队列将有$n+m$个积木）。Petya先手。Petya的目标是让相邻同色积木对尽可能多，Vasya的目标是让相邻异色积木对尽可能多。

你的任务是计算游戏结束时的得分（Petya和Vasya各自的得分），假设两个男孩都采取最优策略。"最优策略"首先意味着最大化自己的得分，其次是最小化对手的得分。

【算法分类】
数学

【题解分析】

所有题解的核心思路均基于两点数学观察：
1. 总相邻对数为 $n+m-1$，且两种得分的和为定值
2. Vasya的得分上限为 $\min(n,m)$，剩余得分自然属于Petya

关键推导过程：
- 当两种颜色交替放置时达到最大异色对数（Vasya的得分）
- 剩余的同色积木必须连续排列，此时同色对数达到最大值 $\max(n,m)-1$

【高分题解】

1. 作者：cff_0102（4星）
   关键亮点：简明扼要地指出总对数关系，直接给出公式推导
   ```cpp
   cout << max(n,m)-1 << ' ' << min(n,m);
   ```

2. 作者：H6_6Q（4星）
   关键亮点：详细解释先手首块不计分的处理逻辑
   ```cpp
   printf("%d %d", max(n,m)-1, min(n,m));
   ```

【核心思路总结】
最优策略的关键在于：
1. 总得分恒等式：Petya得分 + Vasya得分 = n+m-1
2. 异色对的最大值由颜色数量的较小值决定（$\min(n,m)$）
3. 同色对的极值推导需考虑首块不产生得分的特性（$\max(n,m)-1$）

【拓展建议】
类似博弈问题可考虑：
1. 分析总得分恒等式
2. 寻找决定胜负的关键极值点
3. 处理先手/后手的起始状态差异

【推荐习题】
1. P1223 排队接水（贪心策略）
2. P1803 线段覆盖（极值选择）
3. P1090 合并果子（最优合并策略）

【心得知乎】
H6_6Q在题解中指出：
"首次放置一定不得分，所以还要减一"
这一观察点明了先手策略的特殊处理，是推导公式的关键环节。其他题解虽正确但未明确强调此细节，容易导致理解偏差。

---
处理用时：40.34秒