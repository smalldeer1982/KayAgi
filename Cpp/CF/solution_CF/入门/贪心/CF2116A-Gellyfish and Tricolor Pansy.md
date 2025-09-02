# Gellyfish and Tricolor Pansy

## 题目描述

Gellyfish 和 Flower 正在玩一个名为“决斗”的游戏。

Gellyfish 有 $a$ 点生命值，Flower 有 $b$ 点生命值。

他们每人都有一名骑士。Gellyfish 的骑士有 $c$ 点生命值，Flower 的骑士有 $d$ 点生命值。

他们将轮流进行游戏，直到其中一方获胜。对于 $k = 1, 2, \ldots$，他们将依次执行以下操作：

- 如果 $k$ 是奇数且 Gellyfish 的骑士还活着：
  - Gellyfish 的骑士可以攻击 Flower，使 $b$ 减少 $1$。如果 $b \leq 0$，则 Gellyfish 获胜。或者，
  - Gellyfish 的骑士可以攻击 Flower 的骑士，使 $d$ 减少 $1$。如果 $d \leq 0$，则 Flower 的骑士死亡。
- 如果 $k$ 是偶数且 Flower 的骑士还活着：
  - Flower 的骑士可以攻击 Gellyfish，使 $a$ 减少 $1$。如果 $a \leq 0$，则 Flower 获胜。或者，
  - Flower 的骑士可以攻击 Gellyfish 的骑士，使 $c$ 减少 $1$。如果 $c \leq 0$，则 Gellyfish 的骑士死亡。

作为世界上最聪明的人之一，你想在游戏开始前告诉他们谁会获胜。假设双方都采取最优策略。

可以证明，游戏永远不会平局。也就是说，某一方总有策略能在有限步内结束游戏。

## 说明/提示

在第一个测试用例中，Gellyfish 只有 $1$ 点生命值。因此，无论 Gellyfish 在第一回合做什么，Flower 的骑士都会在第二回合攻击 Gellyfish，使 Flower 获胜。

在第二个测试用例中，Flower 的骑士只有 $1$ 点生命值。Gellyfish 会在第一回合攻击 Flower 的骑士。之后 Flower 的骑士将无法再攻击，从而 Gellyfish 获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 2 3 4
100 999 1 1
10 20 10 30
12 14 13 11
998 244 353 107```

### 输出

```
Flower
Gellyfish
Flower
Gellyfish
Gellyfish```

