# 题目信息

# Rectangular Game

## 题目描述

The Smart Beaver from ABBYY decided to have a day off. But doing nothing the whole day turned out to be too boring, and he decided to play a game with pebbles. Initially, the Beaver has $ n $ pebbles. He arranges them in $ a $ equal rows, each row has $ b $ pebbles ( $ a>1 $ ). Note that the Beaver must use all the pebbles he has, i. e. $ n=a·b $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF177B1/72b3400d0a6aa691e5c49fe273a750815ff16b58.png) 10 pebbles are arranged in two rows, each row has 5 pebbles Once the Smart Beaver has arranged the pebbles, he takes back any of the resulting rows (that is, $ b $ pebbles) and discards all other pebbles. Then he arranges all his pebbles again (possibly choosing other values of $ a $ and $ b $ ) and takes back one row, and so on. The game continues until at some point the Beaver ends up with exactly one pebble.

The game process can be represented as a finite sequence of integers $ c_{1},...,c_{k} $ , where:

- $ c_{1}=n $
- $ c_{i+1} $ is the number of pebbles that the Beaver ends up with after the $ i $ -th move, that is, the number of pebbles in a row after some arrangement of $ c_{i} $ pebbles ( $ 1<=i<k $ ). Note that $ c_{i}>c_{i+1} $ .
- $ c_{k}=1 $

The result of the game is the sum of numbers $ c_{i} $ . You are given $ n $ . Find the maximum possible result of the game.

## 说明/提示

Consider the first example ( $ c_{1}=10 $ ). The possible options for the game development are:

- Arrange the pebbles in 10 rows, one pebble per row. Then $ c_{2}=1 $ , and the game ends after the first move with the result of 11.
- Arrange the pebbles in 5 rows, two pebbles per row. Then $ c_{2}=2 $ , and the game continues. During the second move we have two pebbles which can be arranged in a unique way (remember that you are not allowed to put all the pebbles in the same row!) — 2 rows, one pebble per row. $ c_{3}=1 $ , and the game ends with the result of 13.
- Finally, arrange the pebbles in two rows, five pebbles per row. The same logic leads us to $ c_{2}=5,c_{3}=1 $ , and the game ends with the result of 16 — the maximum possible result.

## 样例 #1

### 输入

```
10
```

### 输出

```
16
```

## 样例 #2

### 输入

```
8
```

### 输出

```
15
```

# AI分析结果

### 题目内容
# 矩形游戏

## 题目描述
来自ABBYY的聪明海狸决定休息一天。但一整天无所事事实在太无聊了，于是他决定用石子玩一个游戏。最初，海狸有 $n$ 颗石子。他将它们排成 $a$ 个相等的行，每行有 $b$ 颗石子（$a > 1$）。注意，海狸必须用完他所有的石子，即 $n = a·b$ 。

![10颗石子排成两行，每行5颗](https://cdn.luogu.com.cn/upload/vjudge_pic/CF177B1/72b3400d0a6aa691e5c49fe273a750815ff16b58.png) 10颗石子排成两行，每行5颗石子。一旦聪明海狸排好石子，他会拿走其中一行（即 $b$ 颗石子）并丢弃所有其他石子。然后他再次排列所有石子（可能选择其他的 $a$ 和 $b$ 值），再拿走一行，如此类推。游戏持续进行，直到某一时刻海狸最终只剩下一颗石子。

游戏过程可以用一个有限整数序列 $c_{1},...,c_{k}$ 表示，其中：
- $c_{1} = n$
- $c_{i + 1}$ 是海狸在第 $i$ 次移动后最终剩下的石子数，即在对 $c_{i}$ 颗石子进行某种排列后一行中的石子数（$1 \leq i < k$）。注意 $c_{i} > c_{i + 1}$ 。
- $c_{k} = 1$

游戏的结果是数字 $c_{i}$ 的总和。给定 $n$ ，求游戏可能的最大结果。

## 说明/提示
考虑第一个例子（$c_{1} = 10$）。游戏发展的可能选项有：
- 将石子排成10行，每行1颗石子。那么 $c_{2} = 1$ ，游戏在第一次移动后结束，结果为11。
- 将石子排成5行，每行2颗石子。那么 $c_{2} = 2$ ，游戏继续。在第二次移动中，我们有2颗石子，它们只能以一种方式排列（记住不允许将所有石子放在同一行！）——2行，每行1颗石子。$c_{3} = 1$ ，游戏结束，结果为13。
- 最后，将石子排成2行，每行5颗石子。同样的逻辑得出 $c_{2} = 5$，$c_{3} = 1$ ，游戏结束，结果为16——这是可能的最大结果。

## 样例 #1
### 输入
```
10
```
### 输出
```
16
```

## 样例 #2
### 输入
```
8
```
### 输出
```
15
```

• **算法分类**：贪心
• **综合分析与结论**：所有题解都采用贪心策略，核心思路是每次排列石子时，为使每次操作后剩下的石子数之和最大，应让矩形的行数最少，这样每行的石子个数最多，操作后剩下的石子数也最多。难点在于处理 $n$ 为质数的情况，此时只能排成 $n$ 行一列的矩形。各题解在代码实现上略有不同，如输入方式、判断质数的细节、循环结束条件等，但整体思路一致。
• **通用建议与扩展思路**：对于此类贪心问题，关键在于准确分析出能使结果最优的贪心策略。可拓展到其他类似的资源分配求最值问题，同样从如何分配能使每次操作后剩余资源最多的角度思考。
• **洛谷相似题目推荐**：
  - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过合理分组，运用贪心策略使组数最少。
  - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及策略选择的贪心问题，需要分析如何选择武将能使自己得分最高。
  - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间进行排序，利用贪心思想求出最优排队方案。 

---
处理用时：32.17秒