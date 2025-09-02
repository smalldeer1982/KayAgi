# 题目信息

# Tree of Life (easy)

## 题目描述

Heidi has finally found the mythical Tree of Life – a legendary combinatorial structure which is said to contain a prophecy crucially needed to defeat the undead armies.

On the surface, the Tree of Life is just a regular undirected tree well-known from computer science. This means that it is a collection of $ n $ points (called vertices), some of which are connected using $ n-1 $ line segments (edges) so that each pair of vertices is connected by a path (a sequence of one or more edges).

To decipher the prophecy, Heidi needs to perform a number of steps. The first is counting the number of lifelines in the tree – these are paths of length $ 2 $ , i.e., consisting of two edges. Help her!

## 说明/提示

In the second sample, there are four lifelines: paths between vertices $ 1 $ and $ 3 $ , $ 2 $ and $ 4 $ , $ 2 $ and $ 5 $ , and $ 4 $ and $ 5 $ .

## 样例 #1

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
3```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
3 5
```

### 输出

```
4```

# AI分析结果



# Tree of Life (easy) 中文重写

## 题目描述

海蒂终于找到了传说中的生命之树——一种传奇的组合结构，据说其中包含击败不死军团所需的关键预言。

从表面上看，生命之树只是一个计算机科学中常见的无向树结构。这意味着它由 $n$ 个顶点和 $n-1$ 条边组成，保证任意两个顶点之间都有唯一路径相连。

为了解读预言，海蒂需要先计算树中长度为 $2$ 的路径（即包含两条边的路径）的数量。请你帮助她完成这个任务。

## 说明/提示

第二个样例中的四条生命线是：顶点 $1$ 和 $3$ 之间，$2$ 和 $4$ 之间，$2$ 和 $5$ 之间，以及 $4$ 和 $5$ 之间的路径。

---

**算法分类**：图论、组合数学

---

## 题解分析与结论

**核心思路**：  
每个长度为2的路径（u-v-w）必然经过中间节点v。统计每个节点的度数k，该节点作为中间节点时贡献C(k,2)条路径。等价实现方式为：遍历每个节点的所有邻居，累加邻居的度数减一（排除自身），最终结果除以2消除重复计数。

**关键技巧**：  
1. 利用邻接表存储树结构  
2. 通过组合数学简化计算：每个中间节点贡献k*(k-1)/2条路径  
3. 通过遍历邻居的方式避免显式计算组合数  

**最优题解**：

1. **xxxr_2024（5星）**  
   亮点：代码简洁高效，时间复杂度O(n)  
   ```cpp
   for(int i=1;i<=n;i++)
       for(auto it:g[i])
           ans += g[it].size()-1;
   cout << ans/2;
   ```

2. **Arrtan_73（5星）**  
   亮点：图文结合解释清晰，代码可读性强  
   ```cpp
   for(int i=1;i<=n;i++)
       for(int j=0;j<G[i].size();j++)
           ans += G[G[i][j]].size()-1;
   ```

3. **Ryan_Adam（4星）**  
   亮点：代码极简，使用位运算优化除法  
   ```cpp
   for(i=1;i<=n;++i)
       for(auto j:v[i])
           s += v[j].size()-1;
   cout << (s>>1);
   ```

---

**同类题目推荐**：  
1. P1351 [NOIP2014 提高组] 联合权值  
2. CF191C Fools and Roads（树上路径统计）  
3. P1395 会议（树的重心应用）

---

**个人心得总结**：  
- 调试时注意路径重复计数问题（必须除以2）  
- 理解"度数减一"的关键：排除当前节点自身作为邻居的影响  
- 树结构问题常可转化为对节点的局部统计

---
处理用时：138.43秒