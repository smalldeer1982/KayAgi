# 题目信息

# Sum in the tree

## 题目描述

Mitya has a rooted tree with $ n $ vertices indexed from $ 1 $ to $ n $ , where the root has index $ 1 $ . Each vertex $ v $ initially had an integer number $ a_v \ge 0 $ written on it. For every vertex $ v $ Mitya has computed $ s_v $ : the sum of all values written on the vertices on the path from vertex $ v $ to the root, as well as $ h_v $ — the depth of vertex $ v $ , which denotes the number of vertices on the path from vertex $ v $ to the root. Clearly, $ s_1=a_1 $ and $ h_1=1 $ .

Then Mitya erased all numbers $ a_v $ , and by accident he also erased all values $ s_v $ for vertices with even depth (vertices with even $ h_v $ ). Your task is to restore the values $ a_v $ for every vertex, or determine that Mitya made a mistake. In case there are multiple ways to restore the values, you're required to find one which minimizes the total sum of values $ a_v $ for all vertices in the tree.

## 样例 #1

### 输入

```
5
1 1 1 1
1 -1 -1 -1 -1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2 3 1
1 -1 2 -1 -1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
1 2
2 -1 1
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
# 树中的和

## 题目描述
米佳（Mitya）有一棵有根树，树中有 $n$ 个顶点，顶点编号从 $1$ 到 $n$，其中根节点的编号为 $1$。最初，每个顶点 $v$ 上都写有一个整数 $a_v \ge 0$。对于每个顶点 $v$，米佳计算了 $s_v$：从顶点 $v$ 到根节点的路径上所有顶点上所写值的总和，以及 $h_v$ —— 顶点 $v$ 的深度，即从顶点 $v$ 到根节点的路径上的顶点数。显然，$s_1=a_1$ 且 $h_1=1$。

然后米佳擦除了所有的数字 $a_v$，并且不小心还擦除了所有深度为偶数的顶点（即 $h_v$ 为偶数的顶点）的 $s_v$ 值。你的任务是恢复每个顶点的 $a_v$ 值，或者判断米佳是否出错。如果有多种恢复值的方法，你需要找到一种能使树中所有顶点的 $a_v$ 值总和最小的方法。

## 样例 #1
### 输入
```
5
1 1 1 1
1 -1 -1 -1 -1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
5
1 2 3 1
1 -1 2 -1 -1
```
### 输出
```
2
```

## 样例 #3
### 输入
```
3
1 2
2 -1 1
```
### 输出
```
-1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，通过合理设置未知的 $s$ 值，使得所有顶点的 $a$ 值总和最小。主要步骤包括：先判断无解的情况，即子节点的 $s$ 值小于父节点的 $s$ 值；然后对于未知的 $s$ 值，将其设为子节点 $s$ 值的最小值。

不同题解的实现方式略有不同，有的使用邻接表存储树的结构，有的使用深度优先搜索（DFS）遍历树。但总体思路都是一致的，即通过贪心策略来解决问题。

### 所选题解
- 览遍千秋（4星）
  - 关键亮点：思路清晰，先指出错误思路，再引出正确思路，代码实现简洁明了。
- tXX_F（4星）
  - 关键亮点：详细解释了贪心的原理，代码实现中使用了快速读入输出优化。
- 子谦。（4星）
  - 关键亮点：对不同情况进行了详细分析，包括叶子节点、只有一个子节点和多个子节点的情况，代码实现较为完整。

### 重点代码
#### 览遍千秋的代码
```cpp
void dfs1(int x){
    s[fa[x]]=min(s[fa[x]],s[x]);
    for(int i=Head[x];i;i=Next[i]){
        dfs1(to[i]);
    }
}

void dfs2(int x){
    if(s[x]<s[fa[x]]){
        puts("-1");exit(0);
    }
    if(s[x]!=INF)
        ans+=s[x]-s[fa[x]];
    for(int i=Head[x];i;i=Next[i]){
        dfs2(to[i]);
    }
}
```
核心实现思想：`dfs1` 函数用于将子节点的 $s$ 值上提，更新父节点的 $s$ 值为子节点 $s$ 值的最小值；`dfs2` 函数用于判断是否无解，并计算 $a$ 值的总和。

#### tXX_F 的代码
```cpp
inline long long Dfs(int n) {
    if (s[n] != -1)	return s[n];
    else {
        int k = F[n];
        long long _min = INT_MAX;
        while (k != -1)_min = min(Dfs(V[k]), _min), k = Next[k];
        s[n] = _min;
        return s[n];
    }
}
```
核心实现思想：递归地计算未知的 $s$ 值，将其设为子节点 $s$ 值的最小值。

#### 子谦。的代码
```cpp
void dfs(int u,int fa){
    for(int i=head[u];~i;i=e[i].next){
        int v=e[i].to;
        if(~s[v]){
            if((dep[v]&1)^1){ans=1;return;}
        }
        else{
            if(dep[v]&1){ans=1;return;}
            s[v]=(s1[v]==1000000001?s[u]:s1[v]);
        }
        if(s[v]<s[u]){ans=1;return;}
        sum+=s[v]-s[u];
        dfs(v,u);if(ans)return;
    }
}
```
核心实现思想：深度优先搜索遍历树，判断是否无解，并计算 $a$ 值的总和。对于未知的 $s$ 值，根据子节点的情况进行更新。

### 最优关键思路或技巧
- **贪心策略**：对于未知的 $s$ 值，将其设为子节点 $s$ 值的最小值，这样可以使 $a$ 值总和最小。
- **深度优先搜索（DFS）**：通过 DFS 遍历树，方便处理父子节点之间的关系。

### 拓展思路
同类型题或类似算法套路：
- 其他树结构上的贪心问题，如树的染色问题、树的路径问题等。
- 可以结合动态规划，在树结构上进行状态转移，解决更复杂的问题。

### 推荐题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：树型 DP 问题，与本题的树结构处理有相似之处。
- [P2016 战略游戏](https://www.luogu.com.cn/problem/P2016)：树型 DP 问题，需要考虑树的节点覆盖问题。
- [P2458 [SDOI2006] 保安站岗](https://www.luogu.com.cn/problem/P2458)：树型 DP 问题，涉及树的节点选择和代价计算。

### 个人心得
览遍千秋：一开始有一个非常直观的想法，对于每一个结点，如果不知道它的 $s$，就直接设它为 $0$，可是在 $\mathrm{WA}$ 了几次之后，就会考虑到这样的一种情况：有一结点 $x$，$s$ 未知，如果这时候令其点权为 $k$，则其每一个儿子都可以比令 $x$ 点权为 $0$ 少掉 $k$ 的代价，这种情况显然比直接令 $x$ 优。这个错误的思路可以打开我们正确的思路。

总结：在解题过程中，错误的思路也可能为正确思路提供启发，需要不断尝试和思考。

---
处理用时：47.83秒