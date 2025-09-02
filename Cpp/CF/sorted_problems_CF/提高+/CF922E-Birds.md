---
title: "Birds"
layout: "post"
diff: 提高+/省选-
pid: CF922E
tag: ['动态规划 DP', '背包 DP']
---

# Birds

## 题目描述

Apart from plush toys, Imp is a huge fan of little yellow birds!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922E/3bbf7144a65fde520de46a3e8b677997bfb55fe8.png)To summon birds, Imp needs strong magic. There are $ n $ trees in a row on an alley in a park, there is a nest on each of the trees. In the $ i $ -th nest there are $ c_{i} $ birds; to summon one bird from this nest Imp needs to stay under this tree and it costs him $ cost_{i} $ points of mana. However, for each bird summoned, Imp increases his mana capacity by $ B $ points. Imp summons birds one by one, he can summon any number from $ 0 $ to $ c_{i} $ birds from the $ i $ -th nest.

Initially Imp stands under the first tree and has $ W $ points of mana, and his mana capacity equals $ W $ as well. He can only go forward, and each time he moves from a tree to the next one, he restores $ X $ points of mana (but it can't exceed his current mana capacity). Moving only forward, what is the maximum number of birds Imp can summon?

## 输入格式

The first line contains four integers $ n $ , $ W $ , $ B $ , $ X $ ( $ 1<=n<=10^{3},0<=W,B,X<=10^{9} $ ) — the number of trees, the initial points of mana, the number of points the mana capacity increases after a bird is summoned, and the number of points restored when Imp moves from a tree to the next one.

The second line contains $ n $ integers $ c_{1},c_{2},...,c_{n} $ ( $ 0<=c_{i}<=10^{4} $ ) — where $ c_{i} $ is the number of birds living in the $ i $ -th nest. It is guaranteed that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF922E/b8ab3a37e0e8b12e9f9885a28b92f283792874ef.png).

The third line contains $ n $ integers $ cost_{1},cost_{2},...,cost_{n} $ ( $ 0<=cost_{i}<=10^{9} $ ), where $ cost_{i} $ is the mana cost to summon a bird from the $ i $ -th nest.

## 输出格式

Print a single integer — the maximum number of birds Imp can summon.

## 说明/提示

In the first sample base amount of Imp's mana is equal to $ 12 $ (with maximum capacity also equal to $ 12 $ ). After he summons two birds from the first nest, he loses $ 8 $ mana points, although his maximum capacity will not increase (since $ B=0 $ ). After this step his mana will be $ 4 $ of $ 12 $ ; during the move you will replenish $ 4 $ mana points, and hence own $ 8 $ mana out of $ 12 $ possible. Now it's optimal to take $ 4 $ birds from the second nest and spend $ 8 $ mana. The final answer will be — $ 6 $ .

In the second sample the base amount of mana is equal to $ 1000 $ . The right choice will be to simply pick all birds from the last nest. Note that Imp's mana doesn't restore while moving because it's initially full.

## 样例 #1

### 输入

```
2 12 0 4
3 4
4 2

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 1000 10 35
1 2 4 5
1000 500 250 200

```

### 输出

```
5

```

## 样例 #3

### 输入

```
2 10 7 11
2 10
6 1

```

### 输出

```
11

```

