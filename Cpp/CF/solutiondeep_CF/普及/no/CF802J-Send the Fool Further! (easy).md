# 题目信息

# Send the Fool Further! (easy)

## 题目描述

Heidi's friend Jenny is asking Heidi to deliver an important letter to one of their common friends. Since Jenny is Irish, Heidi thinks that this might be a prank. More precisely, she suspects that the message she is asked to deliver states: "Send the fool further!", and upon reading it the recipient will ask Heidi to deliver the same message to yet another friend (that the recipient has in common with Heidi), and so on.

Heidi believes that her friends want to avoid awkward situations, so she will not be made to visit the same person (including Jenny) twice. She also knows how much it costs to travel between any two of her friends who know each other. She wants to know: what is the maximal amount of money she will waste on travel if it really is a prank?

Heidi's $ n $ friends are labeled $ 0 $ through $ n-1 $ , and their network of connections forms a tree. In other words, every two of her friends $ a $ , $ b $ know each other, possibly indirectly (there is a sequence of friends starting from $ a $ and ending on $ b $ and such that each two consecutive friends in the sequence know each other directly), and there are exactly $ n-1 $ pairs of friends who know each other directly.

Jenny is given the number $ 0 $ .

## 说明/提示

In the second example, the worst-case scenario goes like this: Jenny sends Heidi to the friend labeled by number $ 2 $ (incurring a cost of $ 100 $ ), then friend $ 2 $ sends her to friend $ 1 $ (costing Heidi $ 3 $ ), and finally friend $ 1 $ relays her to friend $ 4 $ (incurring an additional cost of $ 2 $ ).

## 样例 #1

### 输入

```
4
0 1 4
0 2 2
2 3 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
6
1 2 3
0 2 100
1 4 2
0 3 7
3 5 10
```

### 输出

```
105
```

## 样例 #3

### 输入

```
11
1 0 1664
2 0 881
3 2 4670
4 2 1555
5 1 1870
6 2 1265
7 2 288
8 7 2266
9 2 1536
10 6 3378
```

### 输出

```
5551
```

# AI分析结果



# Send the Fool Further! (easy)

## 题目描述

Heidi的朋友Jenny要求Heidi将一封重要信件交给她们的共同朋友。由于Jenny是爱尔兰人，Heidi怀疑这可能是个恶作剧。具体来说，她怀疑信件内容可能是"Send the fool further!"，收件人在阅读后会要求Heidi将同样的信息传递给另一个共同朋友，依此类推。

Heidi认为她的朋友们想避免尴尬情况，所以她不会被要求重复访问同一个人（包括Jenny）。她已知朋友间直接认识的旅行花费，想知道如果真是恶作剧，她可能浪费的最大旅行费用是多少？

Heidi的$n$个朋友编号为$0$到$n-1$，她们的社交网络构成一棵树。即任意两个朋友$a$、$b$都相互认识（可能间接），且恰好存在$n-1$对直接认识的朋友关系。Jenny的编号是$0$。

## 算法分类
深度优先搜索 DFS

---

## 题解分析与结论

**题目核心**：在树结构中寻找从根节点出发的最长路径（权值和最大）

**关键思路对比**：
1. **Velix解法**：使用邻接表存储树结构，通过vis数组记录访问状态，递归计算每个子树的最大路径。时间复杂度O(n)。
2. **流绪解法**：采用父节点回溯法，通过传递父节点参数避免重复访问，无需额外空间存储访问状态，直接维护全局最大值。

**最优技巧**：通过父节点参数控制遍历方向（避免回退），直接累加路径权值，实时更新全局最大值。该方法空间复杂度更优（省去vis数组），代码更简洁。

---

## 精选题解

### 流绪题解（⭐⭐⭐⭐⭐）
**亮点**：
- 父节点回溯法避免重复访问
- 全局最大值实时更新
- 无冗余数据结构

**核心代码**：
```cpp
void dfs(int x,int v,int sum) {
    ans = max(ans,sum);
    for(int i=head[x];i;i=p[i].nex)
        if(p[i].v != v)  // 通过父节点参数避免回溯
            dfs(p[i].v,x,sum+p[i].c);
}
```

### Velix题解（⭐⭐⭐⭐）
**亮点**：
- 邻接表实现清晰
- 递归逻辑简洁

**注意点**：虽然使用vis数组在树结构中略显冗余，但能正确处理遍历逻辑

---

## 拓展建议
**同类问题套路**：
1. 树的最长路径（直径问题）：两次DFS/BFS
2. 带权路径统计：结合前缀和优化
3. 受限路径搜索：如必须包含特定节点

**推荐练习**：
1. P1395 树的直径（模板题）
2. P1352 没有上司的舞会（树形DP）
3. P2015 二叉苹果树（有限边权路径）

---
处理用时：45.13秒