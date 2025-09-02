# 题目信息

# Web of Lies

## 题目描述

When you play the game of thrones, you win, or you die. There is no middle ground.

Cersei Lannister, A Game of Thrones by George R. R. Martin



There are $ n $ nobles, numbered from $ 1 $ to $ n $ . Noble $ i $ has a power of $ i $ . There are also $ m $ "friendships". A friendship between nobles $ a $ and $ b $ is always mutual.

A noble is defined to be vulnerable if both of the following conditions are satisfied:

- the noble has at least one friend, and
- all of that noble's friends have a higher power.

You will have to process the following three types of queries.

1. Add a friendship between nobles $ u $ and $ v $ .
2. Remove a friendship between nobles $ u $ and $ v $ .
3. Calculate the answer to the following process.

The process: all vulnerable nobles are simultaneously killed, and all their friendships end. Then, it is possible that new nobles become vulnerable. The process repeats itself until no nobles are vulnerable. It can be proven that the process will end in finite time. After the process is complete, you need to calculate the number of remaining nobles.

Note that the results of the process are not carried over between queries, that is, every process starts with all nobles being alive!

## 说明/提示

Consider the first example. In the first type 3 query, we have the diagram below.

In the first round of the process, noble $ 1 $ is weaker than all of his friends ( $ 2 $ and $ 3 $ ), and is thus killed. No other noble is vulnerable in round 1. In round 2, noble $ 3 $ is weaker than his only friend, noble $ 4 $ , and is therefore killed. At this point, the process ends, and the answer is $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1548A/eccd6f0add10562eaeff6f7302fe13d3e1f9be51.png)In the second type 3 query, the only surviving noble is $ 4 $ .

The second example consists of only one type $ 3 $ query. In the first round, two nobles are killed, and in the second round, one noble is killed. The final answer is $ 1 $ , since only one noble survives.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1548A/af37f9a008f1a978239a03ac88fceea275d5859b.png)

## 样例 #1

### 输入

```
4 3
2 1
1 3
3 4
4
3
1 2 3
2 3 1
3```

### 输出

```
2
1```

## 样例 #2

### 输入

```
4 3
2 3
3 4
4 1
1
3```

### 输出

```
1```

# AI分析结果

### 题目内容重写

#### 题目描述

当你玩权力的游戏时，要么赢，要么死。没有中间地带。

——瑟曦·兰尼斯特，《权力的游戏》乔治·R·R·马丁

有 $n$ 个贵族，编号从 $1$ 到 $n$。贵族 $i$ 的权力为 $i$。还有 $m$ 条“友谊”。贵族 $a$ 和 $b$ 之间的友谊总是相互的。

一个贵族被定义为“脆弱的”，当且仅当满足以下两个条件：

- 该贵族至少有一个朋友，且
- 该贵族的所有朋友的权力都比他高。

你需要处理以下三种类型的查询：

1. 在贵族 $u$ 和 $v$ 之间添加一条友谊。
2. 删除贵族 $u$ 和 $v$ 之间的友谊。
3. 计算以下过程的答案。

过程：所有脆弱的贵族同时被杀死，他们的所有友谊结束。然后，可能会有新的贵族变得脆弱。该过程重复进行，直到没有贵族是脆弱的。可以证明，该过程将在有限时间内结束。过程结束后，你需要计算剩余的贵族数量。

注意，过程的结果不会在查询之间传递，即每个过程开始时所有贵族都是活着的！

#### 说明/提示

考虑第一个例子。在第一个类型为 3 的查询中，我们有下图。

在第一轮过程中，贵族 $1$ 比他的所有朋友（$2$ 和 $3$）都弱，因此被杀死。第一轮没有其他贵族是脆弱的。在第二轮中，贵族 $3$ 比他唯一的朋友 $4$ 弱，因此被杀死。此时，过程结束，答案为 $2$。

在第二个类型为 3 的查询中，唯一幸存的贵族是 $4$。

第二个例子只有一个类型为 $3$ 的查询。在第一轮中，两个贵族被杀死，在第二轮中，一个贵族被杀死。最终答案为 $1$，因为只有一个贵族幸存。

### 算法分类

**图论**

### 题解分析与结论

#### 综合分析

本题的核心在于如何高效地处理三种操作，特别是第三种操作，即计算在多次删除脆弱贵族后剩余的贵族数量。所有题解都基于一个共同的观察：一个贵族是否会被删除，取决于他是否有比他自己权力更大的朋友。因此，可以通过维护每个贵族比他自己权力更大的朋友的数量，来快速判断他是否会被删除。

#### 最优关键思路

1. **维护比每个贵族权力更大的朋友数量**：通过一个数组 `out[i]` 或 `cnt[i]` 来记录贵族 $i$ 比他自己权力更大的朋友数量。如果 `out[i] > 0`，则贵族 $i$ 会被删除；否则，他会存活。
2. **动态更新答案**：在添加或删除友谊时，根据 `out[i]` 的变化动态更新答案 `ans`。初始时，所有贵族都存活，`ans = n`。当 `out[i]` 从 0 变为 1 时，`ans` 减 1；当 `out[i]` 从 1 变为 0 时，`ans` 加 1。
3. **时间复杂度优化**：通过上述方法，所有操作的时间复杂度均为 $O(1)$，适合处理大规模数据。

#### 推荐题解

1. **作者：Gokix（赞：32）**
   - **星级：5**
   - **关键亮点**：思路清晰，代码简洁，直接维护 `out[i]` 和 `ans`，处理三种操作的时间复杂度均为 $O(1)$。
   - **代码核心**：
     ```cpp
     if(out[u]==0) ans--;
     out[u]++;
     ```

2. **作者：Sora1336（赞：4）**
   - **星级：4**
   - **关键亮点**：通过反证法证明了一个贵族是否会被删除的结论，代码实现与 Gokix 类似，但提供了更多的理论支持。
   - **代码核心**：
     ```cpp
     if(alive[y] == 1) ans--;
     alive[y]++;
     ```

3. **作者：xiaoxiaoxia（赞：4）**
   - **星级：4**
   - **关键亮点**：详细解释了在加边和删边时如何更新 `cnt[i]` 和 `ans`，代码实现清晰。
   - **代码核心**：
     ```cpp
     if(cnt[min(u,v)]==1) ans--;
     cnt[min(u,v)]++;
     ```

#### 关键代码片段

```cpp
// 添加友谊
if(out[u]==0) ans--;
out[u]++;

// 删除友谊
out[u]--;
if(out[u]==0) ans++;
```

#### 拓展思路

类似的问题可以扩展到其他图论场景，例如在社交网络中判断某个用户是否会被“淘汰”，或者在竞争环境中判断某个参与者是否会被“淘汰”。这类问题通常可以通过维护每个节点的“威胁”数量来快速判断其是否会被删除。

#### 推荐题目

1. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
2. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
3. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)

#### 个人心得

在调试过程中，发现需要特别注意在添加和删除友谊时，如何正确地更新 `out[i]` 和 `ans`。特别是在处理边界情况时，例如当 `out[i]` 从 0 变为 1 或从 1 变为 0 时，必须确保 `ans` 的更新是准确的。

---
处理用时：31.70秒