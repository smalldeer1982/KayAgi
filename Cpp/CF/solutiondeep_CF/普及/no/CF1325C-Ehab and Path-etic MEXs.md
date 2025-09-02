# 题目信息

# Ehab and Path-etic MEXs

## 题目描述

You are given a tree consisting of $ n $ nodes. You want to write some labels on the tree's edges such that the following conditions hold:

- Every label is an integer between $ 0 $ and $ n-2 $ inclusive.
- All the written labels are distinct.
- The largest value among $ MEX(u,v) $ over all pairs of nodes $ (u,v) $ is as small as possible.

Here, $ MEX(u,v) $ denotes the smallest non-negative integer that isn't written on any edge on the unique simple path from node $ u $ to node $ v $ .

## 说明/提示

The tree from the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1325C/3987a692dde98854639547ed68f742fb6eeb5979.png)

## 样例 #1

### 输入

```
3
1 2
1 3```

### 输出

```
0
1```

## 样例 #2

### 输入

```
6
1 2
1 3
2 4
2 5
5 6```

### 输出

```
0
3
2
4
1```

# AI分析结果

【题目内容】
# Ehab and Path-etic MEXs

## 题目描述

给定一棵包含 $n$ 个节点的树。你需要在树的边上写一些标签，满足以下条件：

- 每个标签是一个介于 $0$ 到 $n-2$ 之间的整数。
- 所有标签互不相同。
- 在所有节点对 $(u,v)$ 中，$MEX(u,v)$ 的最大值尽可能小。

其中，$MEX(u,v)$ 表示从节点 $u$ 到节点 $v$ 的唯一简单路径上未出现的最小非负整数。

## 说明/提示

第二组样例的树如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1325C/3987a692dde98854639547ed68f742fb6eeb5979.png)

## 样例 #1

### 输入

```
3
1 2
1 3```

### 输出

```
0
1```

## 样例 #2

### 输入

```
6
1 2
1 3
2 4
2 5
5 6```

### 输出

```
0
3
2
4
1```

【算法分类】  
构造

【题解分析与结论】  
该题的核心是通过构造边权分配，使得任意两节点路径上的MEX最大值最小化。所有题解都围绕如何避免边权0、1、2同时出现在一条路径上展开，主要思路是找到一个度数大于等于3的节点，并将0、1、2分配给它相连的三条边，其余边随意分配。这样可以确保MEX的最大值为2，且无法进一步优化。

【评分较高的题解】  
1. **作者：Provicy (赞：13)**  
   - **星级：5**  
   - **关键亮点**：思路清晰，代码简洁，详细解释了如何通过度数大于等于3的节点来避免0、1、2同时出现在一条路径上。  
   - **核心代码**：通过遍历找到度数大于等于3的节点，并将0、1、2分配给它的三条边，其余边按顺序分配。
   ```cpp
   for(ri int i=1;i<=n;i++)
   {
       if(deg[i]>=3)
       {
           for(ri int j=0;j<3;j++) book[e[i][j]]=++cnt;
           break;
       }
   }
   ```

2. **作者：Limit (赞：7)**  
   - **星级：4**  
   - **关键亮点**：代码实现简洁，通过度为1的节点来分配0、1、2，逻辑清晰。  
   - **核心代码**：在前三个度为1的节点的出边赋值上0、1、2，其余边按顺序分配。
   ```cpp
   REP(i,1,N)
   {
       if(out[i]==1)
       {
           answer[p[i]]=++cnt;
           if(cnt==3) break;
       }
   }
   ```

3. **作者：huayucaiji (赞：5)**  
   - **星级：4**  
   - **关键亮点**：通过“T型”结构来解释如何避免0、1、2同时出现在一条路径上，思路直观。  
   - **核心代码**：找到度数大于等于3的节点，并将0、1、2分配给它的三条边，其余边按顺序分配。
   ```cpp
   for(int i=1;i<=n;i++) {
       if(bi[i].size()>=3) {
           for(int j=0;j<3;j++) ans[bi[i][j]]=j;
           now=3; break;
       }
   }
   ```

【最优关键思路】  
通过找到一个度数大于等于3的节点，将0、1、2分配给它的三条边，可以确保MEX的最大值为2，且无法进一步优化。其余边可以随意分配。

【可拓展之处】  
类似的问题可以通过构造特定的边权分配来优化某些路径性质，例如最小化路径上的最大值或最小值。这类问题通常需要找到树中的关键节点或结构，并通过合理的分配策略来达到目标。

【推荐题目】  
1. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)  
2. [P2661 信息传递](https://www.luogu.com.cn/problem/P2661)  
3. [P3388 割点](https://www.luogu.com.cn/problem/P3388)

---
处理用时：31.10秒