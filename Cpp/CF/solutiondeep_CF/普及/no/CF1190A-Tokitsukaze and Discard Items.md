# 题目信息

# Tokitsukaze and Discard Items

## 题目描述

Recently, Tokitsukaze found an interesting game. Tokitsukaze had $ n $ items at the beginning of this game. However, she thought there were too many items, so now she wants to discard $ m $ ( $ 1 \le m \le n $ ) special items of them.

These $ n $ items are marked with indices from $ 1 $ to $ n $ . In the beginning, the item with index $ i $ is placed on the $ i $ -th position. Items are divided into several pages orderly, such that each page contains exactly $ k $ positions and the last positions on the last page may be left empty.

Tokitsukaze would do the following operation: focus on the first special page that contains at least one special item, and at one time, Tokitsukaze would discard all special items on this page. After an item is discarded or moved, its old position would be empty, and then the item below it, if exists, would move up to this empty position. The movement may bring many items forward and even into previous pages, so Tokitsukaze would keep waiting until all the items stop moving, and then do the operation (i.e. check the special page and discard the special items) repeatedly until there is no item need to be discarded.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1190A/a059bb92f5a4888ea9bb5a2b1a83486b43dcecf3.png)Consider the first example from the statement: $ n=10 $ , $ m=4 $ , $ k=5 $ , $ p=[3, 5, 7, 10] $ . The are two pages. Initially, the first page is special (since it is the first page containing a special item). So Tokitsukaze discards the special items with indices $ 3 $ and $ 5 $ . After, the first page remains to be special. It contains $ [1, 2, 4, 6, 7] $ , Tokitsukaze discards the special item with index $ 7 $ . After, the second page is special (since it is the first page containing a special item). It contains $ [9, 10] $ , Tokitsukaze discards the special item with index $ 10 $ .Tokitsukaze wants to know the number of operations she would do in total.

## 说明/提示

For the first example:

- In the first operation, Tokitsukaze would focus on the first page $ [1, 2, 3, 4, 5] $ and discard items with indices $ 3 $ and $ 5 $ ;
- In the second operation, Tokitsukaze would focus on the first page $ [1, 2, 4, 6, 7] $ and discard item with index $ 7 $ ;
- In the third operation, Tokitsukaze would focus on the second page $ [9, 10] $ and discard item with index $ 10 $ .

For the second example, Tokitsukaze would focus on the second page $ [6, 7, 8, 9, 10] $ and discard all special items at once.

## 样例 #1

### 输入

```
10 4 5
3 5 7 10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
13 4 5
7 8 9 10
```

### 输出

```
1
```

# AI分析结果

### 题目内容重写
最近，Tokitsukaze 发现了一个有趣的游戏。游戏开始时，她有 $n$ 个物品。然而，她觉得物品太多了，所以现在她想丢弃其中的 $m$ 个特殊物品（$1 \le m \le n$）。

这些 $n$ 个物品被标记为从 $1$ 到 $n$ 的索引。最初，索引为 $i$ 的物品被放置在第 $i$ 个位置。物品被有序地分成若干页，每页包含恰好 $k$ 个位置，最后一页的最后位置可能为空。

Tokitsukaze 会执行以下操作：专注于第一个包含至少一个特殊物品的特殊页，并在一次操作中丢弃该页上的所有特殊物品。当一个物品被丢弃或移动后，它的旧位置将为空，然后它下面的物品（如果存在）将上移填补这个空位。移动可能会导致许多物品前移，甚至进入前一页，因此 Tokitsukaze 会等待所有物品停止移动，然后重复执行操作（即检查特殊页并丢弃特殊物品），直到没有物品需要被丢弃。

### 算法分类
模拟

### 题解分析与结论
本题的核心在于模拟物品的删除过程，并计算删除操作的次数。由于物品的删除会导致后续物品的前移，因此需要动态地计算每个物品所在的页数。所有题解都采用了类似的思路，即通过维护一个变量来记录已经删除的物品数量，从而动态计算当前物品所在的页数，并统计删除操作的次数。

### 精选题解
1. **作者：hsfzLZH1 (4星)**
   - **关键亮点**：通过维护 `lst` 变量记录已经删除的物品数量，动态计算当前物品所在的页数，并统计删除操作的次数。代码简洁且高效。
   - **核心代码**：
     ```cpp
     while(cur<=m)
     {
         lst=cur-1;
         nww=(p[cur]-lst+k-1)/k;
         for(;((p[cur]-lst+k-1)/k)==nww;cur++);
         ans++;
     }
     ```
   - **个人心得**：通过观察删除后的物品位置变化，巧妙地避免了复杂的模拟过程，直接通过数学计算得出结果。

2. **作者：Alex_Wei (4星)**
   - **关键亮点**：通过维护 `del` 变量记录已经删除的物品数量，动态计算当前物品所在的页数，并统计删除操作的次数。代码逻辑清晰，易于理解。
   - **核心代码**：
     ```cpp
     while(poi<m){
         s++;p[poi]-=del;
         while((++poi)<m&&(p[poi]-del)/k==p[poi-1]/k)p[poi]-=del;
         del=poi;
     }
     ```
   - **个人心得**：通过将物品索引减一，简化了页数的计算过程，使得代码更加简洁。

3. **作者：FLAMEs_ (4星)**
   - **关键亮点**：通过维护 `used` 变量记录已经删除的物品数量，动态计算当前物品所在的页数，并统计删除操作的次数。代码逻辑清晰，易于理解。
   - **核心代码**：
     ```cpp
     while(pos<=m)
     {
         used=pos-1;
         int temp=(a[pos]-used+k-1)/k;
         for(;(a[pos]-used+k-1)/k==temp;pos++);
         ans++;
     }
     ```
   - **个人心得**：通过观察删除后的物品位置变化，巧妙地避免了复杂的模拟过程，直接通过数学计算得出结果。

### 最优关键思路
通过维护一个变量记录已经删除的物品数量，动态计算当前物品所在的页数，并统计删除操作的次数。这种方法避免了复杂的模拟过程，直接通过数学计算得出结果，极大地提高了代码的效率。

### 可拓展之处
类似的问题可以通过维护一个变量来记录已经处理的数据量，从而动态计算当前数据的位置或状态。这种方法可以应用于其他需要动态调整数据的场景，如删除、插入等操作。

### 推荐题目
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)

---
处理用时：32.81秒