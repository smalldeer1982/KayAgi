# 题目信息

# [USACO07NOV] Cow Hurdles S

## 题目描述

Farmer John wants the cows to prepare for the county jumping competition, so Bessie and the gang are practicing jumping over hurdles. They are getting tired, though, so they want to be able to use as little energy as possible to jump over the hurdles.

Obviously, it is not very difficult for a cow to jump over several very short hurdles, but one tall hurdle can be very stressful. Thus, the cows are only concerned about the height of the tallest hurdle they have to jump over.

The cows' practice room has $N$ stations, conveniently labeled $1,\dots,N$. A set of $M$ one-way paths connects pairs of stations; the paths are also conveniently labeled $1,\dots,M$. Path $i$ travels from station $S_i$ to station $E_i$ and contains exactly one hurdle of height $H_i$. Cows must jump hurdles in any path they traverse.

The cows have $T$ tasks to complete. Task $i$ comprises two distinct numbers, $A_i$ and $B_i$, which connote that a cow has to travel from station $A_i$ to station $B_i$ (by traversing over one or more paths over some route). The cows want to take a path the minimizes the height of the tallest hurdle they jump over when traveling from $A_i$ to $B_i$ . Your job is to write a program that determines the path whose tallest hurdle is smallest and report that height.


Farmer John 想让她的奶牛准备郡级跳跃比赛，Bessie 和她的伙伴们正在练习跨栏。她们很累，所以她们想消耗最少的能量来跨栏。 显然，对于一头奶牛跳过几个矮栏是很容易的，但是高栏却很难。于是，奶牛们总是关心路径上最高的栏的高度。 

奶牛的训练场中有 $N$ 个站台，分别标记为 $1,\dots,N$。所有站台之间有 $M$ 条单向路径，第 $i$ 条路经是从站台 $S_i$ 开始，到站台 $E_i$，其中最高的栏的高度为 $H_i$。无论如何跑，奶牛们都要跨栏。 

奶牛们有 $T$ 个训练任务要完成。第 $i$ 个任务包含两个数字 $A_i$ 和 $B_i$，表示奶牛必须从站台 $A_i$ 跑到站台 $B_i$，可以路过别的站台。奶牛们想找一条路径从站台 $A_i$ 到站台 $B_i$，使路径上最高的栏的高度最小。 你的任务就是写一个程序，计算出路径上最高的栏的高度的最小值。


## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 300$，$1 \le M \le 2.5 \times 10^4$，$1 \le H_i \le 1 \times 10^6$，$1 \le T \le 4 \times 10^4$，$1 \le A_i,B_i \le N$。

感谢 @gaozhiyong @_Cppsteve_ 提供翻译


## 样例 #1

### 输入

```
5 6 3
1 2 12
3 2 8
1 3 5
2 5 3
3 4 4
2 4 8
3 4
1 2
5 1
```

### 输出

```
4
8
-1
```

# AI分析结果

### 综合分析与结论

本题的核心问题是在有向图中找到从起点到终点的路径，使得路径上最高的栏的高度最小。题解中主要采用了两种算法：Floyd算法和SPFA算法。Floyd算法由于其$O(n^3)$的时间复杂度，适用于$n \leq 300$的较小规模图，而SPFA算法则通过优化减少了重复计算，提升了效率。

### 所选高质量题解

#### 1. 作者：沉辰 (赞：41) - 5星
- **关键亮点**：使用了Floyd算法，并巧妙地通过`min(max(d[i][k], d[k][j]), d[i][j])`来更新路径上的最高栏高度。代码简洁，思路清晰。
- **核心代码**：
  ```cpp
  for(int k=1;k<=n;k++)
     for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
       d[i][j]=min(max(d[i][k],d[k][j]),d[i][j]);
  ```
- **个人心得**：无

#### 2. 作者：thoq (赞：17) - 4星
- **关键亮点**：使用SPFA算法，并通过记录每个起点的最短路径来避免重复计算，显著提升了效率。代码结构清晰，优化思路明确。
- **核心代码**：
  ```cpp
  void spfa(int s)
  {
      queue<int>q;
      memset(inque,0,sizeof(inque));
      memset(d[s],inf,sizeof(d[s]));
      q.push(s);
      inque[s]=1;
      d[s][s]=0;
      while(!q.empty())
      {
          int u=q.front();
          q.pop();
          inque[u]=0;
          for(int i=h[u];~i;i=e[i].nxt)
          {
              int v=e[i].to;
              if(d[s][v]>max(d[s][u],e[i].w))
              {
                  d[s][v]=max(d[s][u],e[i].w);
                  if(!inque[v])
                  {
                      q.push(v);
                      inque[v]=1;
                  }
              }
          }
      }
  }
  ```
- **个人心得**：通过记录每个起点的最短路径，避免了重复计算，提升了效率。

#### 3. 作者：Starlight237 (赞：6) - 4星
- **关键亮点**：对Floyd算法进行了优化，当`f[i][k]`为无穷大时跳过无用计算，提升了算法效率。代码实现简洁，优化思路明确。
- **核心代码**：
  ```cpp
  for(reg int k=1;k<=n;++k)
      for(reg int i=1;i<=n;++i)
          if(f[i][k]!=0x3f3f3f3f)
              for(reg int j=1;j<=n;++j)
                  f[i][j]=min(f[i][j],max(f[i][k],f[k][j]));
  ```
- **个人心得**：通过跳过无用计算，提升了Floyd算法的效率。

### 最优关键思路与技巧

1. **Floyd算法的变形**：通过`min(max(d[i][k], d[k][j]), d[i][j])`来更新路径上的最高栏高度，适用于小规模图。
2. **SPFA算法的优化**：通过记录每个起点的最短路径，避免重复计算，提升效率。
3. **跳过无用计算**：在Floyd算法中，当`f[i][k]`为无穷大时跳过计算，减少不必要的操作。

### 可拓展之处

- **类似算法套路**：Floyd算法和SPFA算法可以应用于其他需要求解最短路径或最小化最大值的图论问题。
- **同类型题目**：可以考虑处理带权图的最短路径问题，或者需要最小化路径上某些属性的最大值的问题。

### 推荐题目

1. [P2912 [USACO08DEC]Pasture Walking](https://www.luogu.com.cn/problem/P2912)
2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
3. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

### 通用建议与扩展思路

- **算法选择**：对于小规模图，Floyd算法是简单且有效的选择；对于大规模图，考虑使用SPFA或Dijkstra算法。
- **优化思路**：通过记录中间结果或跳过无用计算，可以显著提升算法效率。
- **代码实现**：保持代码简洁，注重可读性和可维护性，便于调试和优化。

---
处理用时：33.11秒