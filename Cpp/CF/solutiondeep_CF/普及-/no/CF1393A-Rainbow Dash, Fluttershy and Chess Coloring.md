# 题目信息

# Rainbow Dash, Fluttershy and Chess Coloring

## 题目描述

One evening Rainbow Dash and Fluttershy have come up with a game. Since the ponies are friends, they have decided not to compete in the game but to pursue a common goal.

The game starts on a square flat grid, which initially has the outline borders built up. Rainbow Dash and Fluttershy have flat square blocks with size $ 1\times1 $ , Rainbow Dash has an infinite amount of light blue blocks, Fluttershy has an infinite amount of yellow blocks.

The blocks are placed according to the following rule: each newly placed block must touch the built on the previous turns figure by a side (note that the outline borders of the grid are built initially). At each turn, one pony can place any number of blocks of her color according to the game rules.

Rainbow and Fluttershy have found out that they can build patterns on the grid of the game that way. They have decided to start with something simple, so they made up their mind to place the blocks to form a chess coloring. Rainbow Dash is well-known for her speed, so she is interested in the minimum number of turns she and Fluttershy need to do to get a chess coloring, covering the whole grid with blocks. Please help her find that number!

Since the ponies can play many times on different boards, Rainbow Dash asks you to find the minimum numbers of turns for several grids of the games.

The chess coloring in two colors is the one in which each square is neighbor by side only with squares of different colors.

## 说明/提示

For $ 3\times3 $ grid ponies can make two following moves: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1393A/e700c5c9ebb73cd50fb6689a87a04ee305695b19.png)

## 样例 #1

### 输入

```
2
3
4```

### 输出

```
2
3```

# AI分析结果

### 题目内容
# 云宝黛西、小蝶与棋盘染色

## 题目描述
一天晚上，云宝黛西和小蝶想出了一个游戏。由于她们是朋友，所以决定在游戏中不竞争，而是共同追求一个目标。

游戏在一个方形平面网格上开始，网格最初已构建好轮廓边界。云宝黛西有无限数量的浅蓝色方块，小蝶有无限数量的黄色方块。

方块的放置遵循以下规则：每个新放置的方块必须通过一条边与前几轮构建的图形相接触（注意，网格的轮廓边界最初就已构建好）。在每一轮中，一只小马可以根据游戏规则放置任意数量她颜色的方块。

云宝和小蝶发现她们可以通过这种方式在游戏网格上构建图案。她们决定从简单的开始，所以下定决心放置方块以形成棋盘染色。云宝黛西以速度快而闻名，所以她对她和小蝶将整个网格用方块覆盖形成棋盘染色所需的最少轮数感兴趣。请帮助她找出这个数字！

由于小马们可以在不同的棋盘上玩很多次，云宝黛西要求你为几个游戏网格找出最少轮数。

双色棋盘染色是指每个方块仅与颜色不同的方块通过边相邻。

## 说明/提示
对于3×3的网格，小马们可以进行以下两步操作：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1393A/e700c5c9ebb73cd50fb6689a87a04ee305695b19.png)

## 样例 #1
### 输入
```
2
3
4
```
### 输出
```
2
3
```

• **算法分类**：数学
• **综合分析与结论**：这些题解思路大多是通过找规律或分析填涂过程得出公式。大家普遍发现最优的填涂方式是从外向内一圈一圈地进行。难点在于理解为什么一圈一圈填涂是最优，以及根据 $n$ 的奇偶性准确得出填涂次数。不同题解有的通过列举小数据找规律，有的从理论上分析每一圈的填涂情况来推导公式，本质上都得出了 $ans = \lfloor\frac{n}{2}\rfloor + 1$ 这个结论。
• **通用建议与扩展思路**：对于此类找规律的题目，可先从小规模数据入手，通过画图等方式直观感受规律，再尝试从理论角度进行推导验证。同类型题常通过分析操作过程中的不变量或最优策略，得出一般性结论。类似算法套路是先模拟过程，总结规律，再证明其正确性。
• **洛谷相似题目**：
  - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)，通过分析数据得出满足条件的结果，考察找规律和简单数学运算。
  - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)，需要分析不同购买方案，找出最优解，与本题找最优策略类似。
  - [P5732 杨辉三角](https://www.luogu.com.cn/problem/P5732)，通过观察杨辉三角的规律进行编程实现，和本题找规律解题思路一致。 

---
处理用时：28.59秒