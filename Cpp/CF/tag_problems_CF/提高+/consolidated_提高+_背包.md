---
title: "Xorcerer's Stones"
layout: "post"
diff: 提高+/省选-
pid: CF1779F
tag: ['背包 DP', '树形 DP']
---

# Xorcerer's Stones

## 题目描述

Misha had been banned from playing chess for good since he was accused of cheating with an engine. Therefore, he retired and decided to become a xorcerer.

One day, while taking a walk in a park, Misha came across a rooted tree with nodes numbered from $ 1 $ to $ n $ . The root of the tree is node $ 1 $ .

For each $ 1\le i\le n $ , node $ i $ contains $ a_i $ stones in it. Misha has recently learned a new spell in his xorcery class and wants to test it out. A spell consists of:

- Choose some node $ i $ ( $ 1 \leq i \leq n $ ).
- Calculate the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) $ x $ of all $ a_j $ such that node $ j $ is in the subtree of $ i $ ( $ i $ belongs to its own subtree).
- Set $ a_j $ equal to $ x $ for all nodes $ j $ in the subtree of $ i $ .

Misha can perform at most $ 2n $ spells and he wants to remove all stones from the tree. More formally, he wants $ a_i=0 $ to hold for each $ 1\leq i \leq n $ . Can you help him perform the spells?

A tree with $ n $ nodes is a connected acyclic graph which contains $ n-1 $ edges. The subtree of node $ i $ is the set of all nodes $ j $ such that $ i $ lies on the simple path from $ 1 $ (the root) to $ j $ . We consider $ i $ to be contained in its own subtree.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \leq n \leq 2\cdot 10^5 $ ) — the size of the tree

The second line contains an array of integers $ a_1,a_2,\ldots, a_n $ ( $ 0 \leq a_i \leq 31 $ ), describing the number of stones in each node initially.

The third line contains an array of integers $ p_2,p_3,\ldots, p_n $ ( $ 1 \leq p_i \leq i-1 $ ), where $ p_i $ means that there is an edge connecting $ p_i $ and $ i $ .

## 输出格式

If there is not a valid sequence of spells, output $ -1 $ .

Otherwise, output a single integer $ q $ ( $ 0 \leq q \leq 2n $ ) in the first line — the number of performed spells.

In the second line output a sequence of integers $ v_1,v_2,\ldots,v_q $ ( $ 1 \leq v_i \leq n $ ) — the $ i $ -th spell will be performed on the subtree of node $ v_i $ . Please note that order matters.

If multiple solutions exist, output any. You don't have to minimize the number of operations.

## 说明/提示

Please refer to the following pictures for an explanation of the third test. Only the first $ 4 $ spells are shown since the last $ 2 $ do nothing. The first picture represents the tree initially with the number of stones for each node written above it in green. Changes applied by the current spell are highlighted in red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1779F/87049d0f1cff376d7b36c99b33f175c4877519fa.png)

## 样例 #1

### 输入

```
2
13 13
1
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
7
5 2 8 3 4 1 31
1 1 2 2 3 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
9
3 31 1 2 7 30 7 3 1
1 1 1 2 5 5 3 4
```

### 输出

```
6
3 2 3 1 2 2
```



---

---
title: "Checkout Assistant"
layout: "post"
diff: 提高+/省选-
pid: CF19B
tag: ['动态规划 DP', '背包 DP']
---

# Checkout Assistant

## 题目描述

Bob 来到一家现购自运商店，将 $n$ 件商品放入了他的手推车，然后到收银台付款。每件商品由它的价格 $c_i$ 和收银员扫描它的时间 $t_i$ 秒定义。

当收银员正在扫描某件商品时，Bob 可以从他的手推车中偷走某些其它商品。Bob 需要恰好 $1$ 秒来偷走一件商品。Bob 需要付给收银员的最少钱数是多少？请记住，收银员扫描商品的顺序由 Bob 决定。

## 输入格式

输入第一行包含数 $n$（$1 \le n \le 2000$）。接下来 $n$ 行每行每件商品由一对数 $t_i$，$c_i$（$0 \le t_i \le 2000$，$1 \le c_i \le 10^9$）描述。如果 $t_i$ 是 $0$，那么当收银员扫描商品 $i$ 时，Bob 不能偷任何东西。

## 输出格式

输出一个数字—— Bob 需要支付的最小金额是多少。

## 样例 #1

### 输入

```
4
2 10
0 20
1 5
1 3

```

### 输出

```
8

```

## 样例 #2

### 输入

```
3
0 1
0 10
0 100

```

### 输出

```
111

```



---

---
title: "Modulo Sum"
layout: "post"
diff: 提高+/省选-
pid: CF577B
tag: ['数学', '背包 DP', '前缀和']
---

# Modulo Sum

## 题目描述

# 题面描述

给出 $1$ 个长度为 $n$ 的序列，以及 $1$ 个正整数 $m$。问这个原序列中是否存在非空子序列，使其元素之和能被 $m$ 整除。

## 输入格式

第 $1$ 行，有 $2$ 个正整数，分别为原序列的长度 $n$ 和 除数 $m$。
（数据范围：$1 \leqslant n \leqslant 10^{6}$，$2 \leqslant m \leqslant 10^{3}$）
第 $2$ 行，有 $n$ 个自然数，表示该原序列的元素 $a_i$。
（数据范围：$0 \leqslant a_i \leqslant 10^{9}$）

## 输出格式

仅 $1$ 行，如果存在符合条件的子序列，输出 **YES**，否则输出 **NO**。

# 样例解释

- 第 $1$ 组样例的解释：
存在符合条件的子序列 $\{2,3\}$，其元素之和为 $2 + 3 = 5$，$5$ 可以被 $5$ 整除。
- 第 $2$ 组样例的解释：
由于原序列中只有 $1$ 个元素，因此它只有 $1$ 个子序列 $\{5\}$，但显然 $5$ 不可以被 $6$ 整除。
- 第 $3$ 组样例的解释：
存在符合条件的子序列 $\{3,3\}$，其元素之和为 $3 + 3 = 6$，$6$ 可以被 $6$ 整除。
- 第 $4$ 组样例的解释：
选择整个原序列作为子序列，其元素之和为 $5 + 5 + 5 + 5 + 5 + 5 = 30$，$30$ 可以被 $6$ 整除。

Translated by Sooke

## 样例 #1

### 输入

```
3 5
1 2 3

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
1 6
5

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
4 6
3 1 1 3

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
6 6
5 5 5 5 5 5

```

### 输出

```
YES

```



---

---
title: "Bottles"
layout: "post"
diff: 提高+/省选-
pid: CF730J
tag: ['贪心', '枚举', '背包 DP']
---

# Bottles

## 题目描述

有 $n$ 瓶水，第 $i$ 瓶水的水量为 $a_i$，容量为 $b_i$。将 $1$ 单位水从一个瓶子转移到另一个瓶子所消耗时间为 $1$ 秒，且可以进行无限次转移。求储存所有水所需最小瓶子数 $k$ 以及该情况下所用最小时间 $t$。

## 输入格式

第一行输入一个正整数 $n$（$1\le n\le 100$）。

第二行输入 $n$ 个正整数，第 $i$ 个正整数表示 $a_i$（$1\le a_i \le 100$）。

第三行输入 $n$ 个正整数，第 $i$ 个正整数表示 $b_i$（$1\le b_i \le100$）。

对于每一个 $i$，满足$a_i\le b_i$。

## 输出格式

输出一行两个整数：$k$ 和 $t$。

## 样例 #1

### 输入

```
4
3 3 4 3
4 7 6 5

```

### 输出

```
2 6

```

## 样例 #2

### 输入

```
2
1 1
100 100

```

### 输出

```
1 1

```

## 样例 #3

### 输入

```
5
10 30 5 6 24
10 41 7 8 24

```

### 输出

```
3 11

```



---

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



---

---
title: "Lucky Country"
layout: "post"
diff: 提高+/省选-
pid: CF95E
tag: ['背包 DP', '连通块', '进制']
---

# Lucky Country

## 题目描述

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 744 $ , $ 4 $ are lucky and $ 5 $ , $ 17 $ , $ 467 $ are not.

One night Petya was sleeping. He was dreaming of being the president of some island country. The country is represented by islands connected by two-way roads. Between some islands there is no road way, even through other islands, that's why the country is divided into several regions. More formally, each island belongs to exactly one region, there is a path between any two islands located in the same region; there is no path between any two islands from different regions. A region is lucky if the amount of islands in it is a lucky number.

As a real president, Petya first decided to build a presidential palace. Being a lucky numbers' fan, Petya wants to position his palace in one of the lucky regions. However, it is possible that initially the country has no such regions. In this case Petya can build additional roads between different regions, thus joining them. Find the minimum number of roads needed to build to create a lucky region.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{5} $ ). They are the number of islands and the number of roads correspondingly. Next $ m $ lines contain road descriptions. Each road is defined by the numbers of islands that it connects: that is, by two integers $ u $ and $ v $ ( $ 1<=u,v<=n $ ). Some roads can connect an island with itself; there can be more than one road between a pair of islands. Numbers in each line are separated by exactly one space character.

## 输出格式

If there's no solution, output the only number "-1" (without the quotes). Otherwise, output the minimum number of roads $ r $ that need to be built to get a lucky region.

## 样例 #1

### 输入

```
4 3
1 2
2 3
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5 4
1 2
3 4
4 5
3 5

```

### 输出

```
-1

```



---

---
title: "Addition on Segments"
layout: "post"
diff: 提高+/省选-
pid: CF981E
tag: ['线段树', '分治', '背包 DP']
---

# Addition on Segments

## 题目描述

Grisha come to a contest and faced the following problem.

You are given an array of size $ n $ , initially consisting of zeros. The elements of the array are enumerated from $ 1 $ to $ n $ . You perform $ q $ operations on the array. The $ i $ -th operation is described with three integers $ l_i $ , $ r_i $ and $ x_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1 \leq x_i \leq n $ ) and means that you should add $ x_i $ to each of the elements with indices $ l_i, l_i + 1, \ldots, r_i $ . After all operations you should find the maximum in the array.

Grisha is clever, so he solved the problem quickly.

However something went wrong inside his head and now he thinks of the following question: "consider we applied some subset of the operations to the array. What are the possible values of the maximum in the array?"

Help Grisha, find all integers $ y $ between $ 1 $ and $ n $ such that if you apply some subset (possibly empty) of the operations, then the maximum in the array becomes equal to $ y $ .

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \leq n, q \leq 10^{4} $ ) — the length of the array and the number of queries in the initial problem.

The following $ q $ lines contain queries, one per line. The $ i $ -th of these lines contains three integers $ l_i $ , $ r_i $ and $ x_i $ ( $ 1 \leq l_i \leq r_i \leq n $ , $ 1 \leq x_i \leq n $ ), denoting a query of adding $ x_i $ to the segment from $ l_i $ -th to $ r_i $ -th elements of the array, inclusive.

## 输出格式

In the first line print the only integer $ k $ , denoting the number of integers from $ 1 $ to $ n $ , inclusive, that can be equal to the maximum in the array after applying some subset (possibly empty) of the given operations.

In the next line print these $ k $ integers from $ 1 $ to $ n $ — the possible values of the maximum. Print these integers in increasing order.

## 说明/提示

Consider the first example. If you consider the subset only of the first query, the maximum is equal to $ 1 $ . If you take only the second query, the maximum equals to $ 2 $ . If you take the first two queries, the maximum becomes $ 3 $ . If you take only the fourth query, the maximum becomes $ 4 $ . If you take the fourth query and something more, the maximum becomes greater that $ n $ , so you shouldn't print it.

In the second example you can take the first query to obtain $ 1 $ . You can take only the second query to obtain $ 2 $ . You can take all queries to obtain $ 3 $ .

In the third example you can obtain the following maximums:

- You can achieve the maximim of $ 2 $ by using queries: $ (1) $ .
- You can achieve the maximim of $ 3 $ by using queries: $ (2) $ .
- You can achieve the maximim of $ 5 $ by using queries: $ (1, 2) $ .
- You can achieve the maximim of $ 6 $ by using queries: $ (3) $ .
- You can achieve the maximim of $ 8 $ by using queries: $ (1, 3) $ .
- You can achieve the maximim of $ 9 $ by using queries: $ (2, 3) $ .

## 样例 #1

### 输入

```
4 3
1 3 1
2 4 2
3 4 4

```

### 输出

```
4
1 2 3 4 

```

## 样例 #2

### 输入

```
7 2
1 5 1
3 7 2

```

### 输出

```
3
1 2 3 

```

## 样例 #3

### 输入

```
10 3
1 1 2
1 1 3
1 1 6

```

### 输出

```
6
2 3 5 6 8 9 

```



---

