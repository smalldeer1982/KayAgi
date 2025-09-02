# 题目信息

# The Third Letter

## 题目描述

In order to win his toughest battle, Mircea came up with a great strategy for his army. He has $ n $ soldiers and decided to arrange them in a certain way in camps. Each soldier has to belong to exactly one camp, and there is one camp at each integer point on the $ x $ -axis (at points $ \cdots, -2, -1, 0, 1, 2, \cdots $ ).

The strategy consists of $ m $ conditions. Condition $ i $ tells that soldier $ a_i $ should belong to a camp that is situated $ d_i $ meters in front of the camp that person $ b_i $ belongs to. (If $ d_i < 0 $ , then $ a_i $ 's camp should be $ -d_i $ meters behind $ b_i $ 's camp.)

Now, Mircea wonders if there exists a partition of soldiers that respects the condition and he asks for your help! Answer "YES" if there is a partition of the $ n $ soldiers that satisfies all of the $ m $ conditions and "NO" otherwise.

Note that two different soldiers may be placed in the same camp.

## 说明/提示

For the first test case, we can partition the soldiers into camps in the following way: soldier:

- Soldier $ 1 $ in the camp with the coordinate $ x = 3 $ .
- Soldier $ 2 $ in the camp with the coordinate $ x = 5 $ .
- Soldier $ 3 $ in the camp with the coordinate $ x = 9 $ .
- Soldier $ 4 $ in the camp with the coordinate $ x = 11 $ .

For the second test case, there is no partition that can satisfy all the constraints at the same time.

For the third test case, there is no partition that satisfies all the constraints since we get contradictory information about the same pair.

For the fourth test case, in order to satisfy the only condition, a possible partition is:

- Soldier $ 1 $ in the camp with the coordinate $ x = 10 $ .
- Soldier $ 2 $ in the camp with the coordinate $ x = 13 $ .
- Soldier $ 3 $ in the camp with the coordinate $ x = -2023 $ .
- Soldier $ 4 $ in the camp with the coordinate $ x = -2023 $ .

## 样例 #1

### 输入

```
4
5 3
1 2 2
2 3 4
4 2 -6
6 5
1 2 2
2 3 4
4 2 -6
5 4 4
3 5 100
2 2
1 2 5
1 2 4
4 1
1 2 3```

### 输出

```
YES
NO
NO
YES```

# AI分析结果

### 题目内容重写
为了赢得最艰难的战斗，Mircea为他的军队制定了一个伟大的策略。他有$n$个士兵，并决定将他们以某种方式安排在营地中。每个士兵必须属于一个营地，并且在$x$轴上的每个整数点（在点$\cdots, -2, -1, 0, 1, 2, \cdots$）都有一个营地。

策略由$m$个条件组成。条件$i$表示士兵$a_i$应该属于一个位于士兵$b_i$所在营地前方$d_i$米的营地。（如果$d_i < 0$，则$a_i$的营地应该位于$b_i$的营地后方$-d_i$米处。）

现在，Mircea想知道是否存在一种士兵的分配方式，能够满足所有条件，并请求你的帮助！如果存在一种满足所有$m$个条件的士兵分配方式，则回答“YES”，否则回答“NO”。

注意，两个不同的士兵可能被安排在同一个营地。

### 说明/提示
对于第一个测试用例，我们可以将士兵分配到营地的方式如下：
- 士兵$1$在坐标为$x = 3$的营地。
- 士兵$2$在坐标为$x = 5$的营地。
- 士兵$3$在坐标为$x = 9$的营地。
- 士兵$4$在坐标为$x = 11$的营地。

对于第二个测试用例，没有一种分配方式可以同时满足所有约束。

对于第三个测试用例，由于我们得到了关于同一对士兵的矛盾信息，因此不存在满足所有约束的分配方式。

对于第四个测试用例，为了满足唯一的条件，一种可能的分配方式是：
- 士兵$1$在坐标为$x = 10$的营地。
- 士兵$2$在坐标为$x = 13$的营地。
- 士兵$3$在坐标为$x = -2023$的营地。
- 士兵$4$在坐标为$x = -2023$的营地。

### 样例 #1

#### 输入
```
4
5 3
1 2 2
2 3 4
4 2 -6
6 5
1 2 2
2 3 4
4 2 -6
5 4 4
3 5 100
2 2
1 2 5
1 2 4
4 1
1 2 3
```

#### 输出
```
YES
NO
NO
YES
```

### 算法分类
并查集

### 题解分析与结论
该题的核心在于处理多个约束条件，判断是否存在一种士兵的分配方式，使得所有条件都能被满足。题解中主要使用了带权并查集和DFS两种方法。

1. **带权并查集**：通过维护每个节点到其祖先的距离，判断在合并过程中是否出现矛盾。这种方法的时间复杂度较低，适合处理大规模数据。
2. **DFS**：通过深度优先搜索遍历图，检查在遍历过程中是否出现矛盾。这种方法实现简单，但在某些情况下可能会因为递归深度过大而导致栈溢出。

### 所选高星题解

#### 题解1：buaa_czx (5星)
**关键亮点**：
- 使用带权并查集维护每个节点到其祖先的距离，通过路径压缩和合并操作高效处理约束条件。
- 代码简洁，逻辑清晰，适合大规模数据处理。

**核心代码**：
```cpp
int find(int x) {
    if (x == fa[x])
        return x;
    else {
        int fx = find(fa[x]);
        dist[x] += dist[fa[x]];
        fa[x] = fx;
        return fa[x];
    }
}
void join(int x, int y, int val) {
    int fx = find(x), fy = find(y);
    fa[fx] = fy;
    dist[fx] = val + dist[y] - dist[x];
}
```

#### 题解2：sto_5k_orz (4星)
**关键亮点**：
- 使用DFS遍历图，检查在遍历过程中是否出现矛盾。
- 实现简单，适合初学者理解。

**核心代码**：
```cpp
void dfs(int u, int now) {
    if(dis[u]) return ; dis[u] = now;
    for(auto it: e[u]) {
        if(flag) return ;
        int v = it.fi, w = it.se;
        if(!dis[v]) dfs(v, dis[u] + w);
        else {
            if(dis[v] != dis[u] + w) {
                cout << "NO\n";
                flag = 1;
                return ;
            }
        }
        if(flag) return ;
    }
}
```

#### 题解3：Aewrxuk (4星)
**关键亮点**：
- 使用带权并查集处理约束条件，代码简洁，逻辑清晰。
- 通过维护每个节点到其祖先的距离，判断在合并过程中是否出现矛盾。

**核心代码**：
```cpp
int Find(int x) {
    if (x == f[x])
        return x;
    else {
        int fx = Find(f[x]);
        d[x] += d[f[x]];
        f[x] = fx;
        return f[x];
    }
}
```

### 最优关键思路与技巧
- **带权并查集**：通过维护每个节点到其祖先的距离，判断在合并过程中是否出现矛盾。这种方法高效且适合处理大规模数据。
- **DFS**：通过深度优先搜索遍历图，检查在遍历过程中是否出现矛盾。实现简单，适合初学者理解。

### 可拓展之处
- **差分约束系统**：可以将该问题转化为差分约束系统，使用SPFA算法判断是否存在负环。
- **图论**：可以将士兵和约束条件转化为图的节点和边，使用图论算法进行处理。

### 推荐题目
1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
2. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
3. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)

### 个人心得
- **调试经历**：在实现带权并查集时，需要注意路径压缩和合并操作的顺序，否则可能导致距离计算错误。
- **踩坑教训**：在使用DFS时，需要注意递归深度，避免栈溢出。
- **顿悟感想**：带权并查集在处理约束条件时非常高效，适合处理大规模数据。

---
处理用时：34.79秒