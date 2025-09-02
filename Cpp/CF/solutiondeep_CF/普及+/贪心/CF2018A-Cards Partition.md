# 题目信息

# Cards Partition

## 题目描述

[DJ Genki vs Gram - Einherjar Joker](https://soundcloud.com/leon-hwang-368077289/einherjar-joker-dj-genki-vs-gram)

⠀



You have some cards. An integer between $ 1 $ and $ n $ is written on each card: specifically, for each $ i $ from $ 1 $ to $ n $ , you have $ a_i $ cards which have the number $ i $ written on them.

There is also a shop which contains unlimited cards of each type. You have $ k $ coins, so you can buy at most $ k $ new cards in total, and the cards you buy can contain any integer between $ \mathbf{1} $ and $ \mathbf{n} $ , inclusive.

After buying the new cards, you must partition all your cards into decks, according to the following rules:

- all the decks must have the same size;
- there are no pairs of cards with the same value in the same deck.

Find the maximum possible size of a deck after buying cards and partitioning them optimally.

## 说明/提示

In the first test case, you can buy one card with the number $ 1 $ , and your cards become $ [1, 1, 1, 1, 2, 2, 3, 3] $ . You can partition them into the decks $ [1, 2], [1, 2], [1, 3], [1, 3] $ : they all have size $ 2 $ , and they all contain distinct values. You can show that you cannot get a partition with decks of size greater than $ 2 $ , so the answer is $ 2 $ .

In the second test case, you can buy two cards with the number $ 1 $ and one card with the number $ 3 $ , and your cards become $ [1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5] $ , which can be partitioned into $ [1, 2, 3], [1, 2, 4], [1, 2, 5], [1, 2, 5], [2, 3, 5], [2, 4, 5] $ . You can show that you cannot get a partition with decks of size greater than $ 3 $ , so the answer is $ 3 $ .

## 样例 #1

### 输入

```
9
3 1
3 2 2
5 4
2 6 1 2 4
2 100
1410065408 10000000000
10 8
7 4 6 6 9 3 10 2 8 7
2 12
2 2
2 70
0 1
1 0
1
3 0
2 1 2
3 1
0 3 3```

### 输出

```
2
3
1
7
2
2
1
1
2```

# AI分析结果



# Cards Partition 题目翻译

## 题目描述

你有一些卡片。每张卡片上写有一个介于 $1$ 到 $n$ 之间的整数：具体来说，对于每个从 $1$ 到 $n$ 的 $i$，你有 $a_i$ 张写有数字 $i$ 的卡片。

商店中每种类型的卡片供应无限。你拥有 $k$ 枚硬币，因此最多可以购买 $k$ 张新卡片，购买的卡片可以包含 $1$ 到 $n$ 之间的任意整数。

购买新卡片后，你需要将所有卡片分成若干牌组，满足以下规则：

- 所有牌组的大小必须相同；
- 同一牌组中不能存在两张相同数字的卡片。

求购买卡片并最优分配后，牌组大小的最大可能值。

## 说明/提示

在第一个测试用例中，你可以购买一张数字 $1$ 的卡片，此时卡片变为 $[1, 1, 1, 1, 2, 2, 3, 3]$。可以将其分为 $[1, 2], [1, 2], [1, 3], [1, 3]$，每个牌组大小为 $2$。无法得到更大的牌组，因此答案为 $2$。

在第二个测试用例中，购买两张 $1$ 和一张 $3$，卡片变为 $[1,1,1,1,2,2,2,2,2,2,3,3,4,4,5,5,5,5]$，可分成六个大小为 $3$ 的牌组。

---

## 题解分析与结论

### 关键思路
1. **枚举牌组大小**：从最大可能的牌组大小（即数字种类数 $n$）开始向下枚举。
2. **数学条件判断**：
   - 总堆数 $y$ 必须满足 $y \ge \max(a_i)$，确保每个数字出现次数不超过堆数。
   - 总牌数加上购买的卡片数后必须能整除牌组大小，且总购买数不超过 $k$。

### 最优解法亮点
- **分情况处理**：当初始总牌数不足时，需保证购买后足够；当足够时，需补足余数。
- **高效枚举**：从大到小枚举牌组大小，及时终止，时间复杂度 $O(n)$。

---

## 精选题解

### 题解1 by Super_Cube（★★★★★）
**关键亮点**：  
- 分情况讨论，数学推导清晰。
- 代码简洁高效，直接枚举可能的牌组大小。

**核心代码**：
```cpp
for(int i=n;i;--i)
    if((s<v*i&&s+m>=v*i)||(s>=v*i&&(i-s%i)%i<=m))
        printf("%d\n",i),i=1;
```

### 题解2 by chenxi2009（★★★★☆）
**关键亮点**：  
- 条件合并简化，统一判断总堆数和总购买数。
- 代码直观易懂，但枚举顺序可能导致效率略低。

**核心代码**：
```cpp
for(int i = 1;i <= n;i ++)
    if((sum + k) / i * i >= sum && (sum + k) / i >= mx)
        ans = i;
```

---

## 拓展与习题推荐
**相似题目**：  
1. [P4377 USACO18OPEN Talent Show G](https://www.luogu.com.cn/problem/P4377)  
2. [P2218 HAOI2007 覆盖问题](https://www.luogu.com.cn/problem/P2218)  
3. [P1648 看守](https://www.luogu.com.cn/problem/P1648)  

**总结**：  
- 此类问题通常需要数学建模与贪心策略结合，通过枚举或二分快速验证条件。
- 调试时需重点验证边界情况，确保条件覆盖所有可能。

---
处理用时：447.07秒