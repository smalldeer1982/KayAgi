# 题目信息

# GamingForces

## 题目描述

Monocarp is playing a computer game. He's going to kill $ n $ monsters, the $ i $ -th of them has $ h_i $ health.

Monocarp's character has two spells, either of which he can cast an arbitrary number of times (possibly, zero) and in an arbitrary order:

- choose exactly two alive monsters and decrease their health by $ 1 $ ;
- choose a single monster and kill it.

When a monster's health becomes $ 0 $ , it dies.

What's the minimum number of spell casts Monocarp should perform in order to kill all monsters?

## 说明/提示

In the first testcase, the initial health list is $ [1, 2, 1, 2] $ . Three spells are casted:

- the first spell on monsters $ 1 $ and $ 2 $ — monster $ 1 $ dies, monster $ 2 $ has now health $ 1 $ , new health list is $ [0, 1, 1, 2] $ ;
- the first spell on monsters $ 3 $ and $ 4 $ — monster $ 3 $ dies, monster $ 4 $ has now health $ 1 $ , new health list is $ [0, 1, 0, 1] $ ;
- the first spell on monsters $ 2 $ and $ 4 $ — both monsters $ 2 $ and $ 4 $ die.

In the second testcase, the initial health list is $ [2, 4, 2] $ . Three spells are casted:

- the first spell on monsters $ 1 $ and $ 3 $ — both monsters have health $ 1 $ now, new health list is $ [1, 4, 1] $ ;
- the second spell on monster $ 2 $ — monster $ 2 $ dies, new health list is $ [1, 0, 1] $ ;
- the first spell on monsters $ 1 $ and $ 3 $ — both monsters $ 1 $ and $ 3 $ die.

In the third testcase, the initial health list is $ [1, 2, 3, 4, 5] $ . Five spells are casted. The $ i $ -th of them kills the $ i $ -th monster with the second spell. Health list sequence: $ [1, 2, 3, 4, 5] $ $ \rightarrow $ $ [0, 2, 3, 4, 5] $ $ \rightarrow $ $ [0, 0, 3, 4, 5] $ $ \rightarrow $ $ [0, 0, 0, 4, 5] $ $ \rightarrow $ $ [0, 0, 0, 0, 5] $ $ \rightarrow $ $ [0, 0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
3
4
1 2 1 2
3
2 4 2
5
1 2 3 4 5```

### 输出

```
3
3
5```

# AI分析结果

### 题目内容
# 游戏之力

## 题目描述
莫诺卡普正在玩一款电脑游戏。他要击杀\(n\)只怪物，第\(i\)只怪物有\(h_i\)点生命值。

莫诺卡普的角色有两个技能，他可以按任意顺序，任意次数（可能为零次）施展其中任何一个技能：
- 选择恰好两只存活的怪物，并将它们的生命值各减少\(1\)；
- 选择一只怪物并将其击杀。

当一只怪物的生命值降为\(0\)时，它就会死亡。

莫诺卡普为了杀死所有怪物，最少需要施展多少次技能？

## 说明/提示
在第一个测试用例中，初始生命值列表为\([1, 2, 1, 2]\)。施展三次技能：
- 对怪物\(1\)和\(2\)使用第一个技能 —— 怪物\(1\)死亡，怪物\(2\)现在生命值为\(1\)，新的生命值列表为\([0, 1, 1, 2]\)；
- 对怪物\(3\)和\(4\)使用第一个技能 —— 怪物\(3\)死亡，怪物\(4\)现在生命值为\(1\)，新的生命值列表为\([0, 1, 0, 1]\)；
- 对怪物\(2\)和\(4\)使用第一个技能 —— 怪物\(2\)和\(4\)都死亡。

在第二个测试用例中，初始生命值列表为\([2, 4, 2]\)。施展三次技能：
- 对怪物\(1\)和\(3\)使用第一个技能 —— 两只怪物现在生命值都为\(1\)，新的生命值列表为\([1, 4, 1]\)；
- 对怪物\(2\)使用第二个技能 —— 怪物\(2\)死亡，新的生命值列表为\([1, 0, 1]\)；
- 对怪物\(1\)和\(3\)使用第一个技能 —— 怪物\(1\)和\(3\)都死亡。

在第三个测试用例中，初始生命值列表为\([1, 2, 3, 4, 5]\)。施展五次技能。第\(i\)次技能使用第二个技能击杀第\(i\)只怪物。生命值列表变化：\([1, 2, 3, 4, 5]\) \(\rightarrow\) \([0, 2, 3, 4, 5]\) \(\rightarrow\) \([0, 0, 3, 4, 5]\) \(\rightarrow\) \([0, 0, 0, 4, 5]\) \(\rightarrow\) \([0, 0, 0, 0, 5]\) \(\rightarrow\) \([0, 0, 0, 0, 0]\)。

## 样例 #1
### 输入
```
3
4
1 2 1 2
3
2 4 2
5
1 2 3 4 5
```
### 输出
```
3
3
5
```

### 算法分类
贪心

### 综合分析与结论
由于暂无题解，通用建议是利用贪心策略，优先考虑使用“选择恰好两只存活的怪物，并将它们的生命值各减少\(1\)”这个技能，因为此技能一次能影响两只怪物，可减少总的技能施展次数。只有当无法再使用该技能时，再使用“选择一只怪物并将其击杀”的技能。扩展思路上，可以考虑怪物生命值分布更加复杂的情况，以及技能效果发生变化的类似题目，核心都是寻找最优的技能使用策略以减少总操作次数。

### 洛谷题目推荐
1. P1094 [NOIP2007 普及组] 纪念品分组，通过贪心策略对物品分组以满足一定条件，与本题贪心选择技能减少操作次数思路类似。
2. P1223 排队接水，利用贪心思想对排队接水顺序进行优化，和本题寻找最优操作顺序有相似之处。
3. P1781 宇宙总统，通过贪心选择最大数的策略，和本题贪心选择技能减少总次数的思维方式类似。 

---
处理用时：29.15秒