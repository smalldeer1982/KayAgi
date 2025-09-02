# 题目信息

# [USACO11MAR] Tree Decoration G

## 题目描述

给定一颗以 $1$ 为根的有根树，第 $i$ 个结点的父结点为 $P_i$（$P_1=-1$），在第 $i$ 个结点上挂一个装饰物的代价为 $T_i$，每个结点可以挂任意个。现在给定每棵树子树中至少挂的装饰物个数 $C_i$，求满足要求的最少花费。

$1 \leq n \leq 10^5$，$1 \leq T_i \leq 100$，$1 \leq C_i \leq 10^7$，请注意要开 long long。

## 样例 #1

### 输入

```
5 
-1 9 3 
1 2 2 
5 3 2 
5 1 4 
2 3 3 
```

### 输出

```
20 
```

# AI分析结果



### 算法分类：贪心、深度优先搜索 DFS

---

### 综合分析与结论
题目要求以最小代价满足每个子树装饰数量的约束。所有题解均基于**贪心+DFS**思路：  
1. **核心贪心策略**：对每个节点，优先使用其子树中最小的装饰成本来补足差额装饰数量。
2. **树形处理**：通过DFS后序遍历，自底向上维护两个关键值：子树中的最小成本(`min_cost`)和当前装饰总数(`sum_cnt`)。
3. **补足逻辑**：若当前节点的`sum_cnt`不足需求，计算差额并累加总成本，更新当前节点的`sum_cnt`。

---

### 精选题解

#### 1. 作者：Idvz (4星)
**关键亮点**：  
- 代码结构清晰，使用链式前向星建树，处理无向边。
- 通过`now[u]`累加子树装饰数，`c[u]`维护子树最小成本，逻辑简洁。  
**核心代码**：
```cpp
void dfs(int u) {
    vis[u] = 1;
    for(int i = head[u]; i ;i = E[i].next) {
        int v = E[i].to;
        if(vis[v]) continue;
        dfs(v);
        c[u] = min(c[u], c[v]); // 更新子树最小成本
        now[u] += now[v];       // 累加子树装饰数
    }
    if(now[u] < t[u]) {
        ans += (t[u]-now[u]) * c[u]; // 补足差额
        now[u] = t[u];
    }
}
```

#### 2. 作者：scp020 (4星)
**关键亮点**：  
- 代码极简，使用邻接表存储树，直接递归处理。
- 变量命名明确（如`yet`表示已放数量），注释清晰。  
**核心代码**：
```cpp
void dfs(int pos,int fa) {
    for(edge *i=head[pos];i!=nullptr;i=i->next) {
        int v = i->to;
        if(v != fa) dfs(v, pos);
        c[pos] = min(c[pos], c[v]);
        yet[pos] += yet[v];
    }
    if(yet[pos] < d[pos]) {
        ans += (d[pos]-yet[pos])*c[pos];
        yet[pos] = d[pos];
    }
}
```

#### 3. 作者：moosssi (4星)
**个人心得**：  
> "统计答案时，如果子树内已放置的个数大于当前节点的所需数，不用管了，如果小于，缺多少补上去就行了，最后记得开long long。"  
**关键亮点**：  
- 变量命名直观（`siz`代替`sum_cnt`，`minc`代替`min_cost`），适合快速理解。  
**核心代码**：
```cpp
void dfs(int x,int fa){
    minc[x] = c[x];
    for(int v : son[x]) {
        dfs(v, x);
        minc[x] = min(minc[x], minc[v]);
        siz[x] += siz[v];
    }
    if(siz[x] < d[x]) {
        ans += (d[x]-siz[x]) * minc[x];
        siz[x] = d[x];
    }
}
```

---

### 最优技巧总结
1. **树的后序遍历**：确保先处理子节点再处理父节点，满足子树约束。
2. **双变量维护**：`min_cost`和`sum_cnt`动态更新，保证贪心选择。
3. **溢出处理**：使用`long long`存储累加值，避免大数溢出。

---

### 扩展题目推荐
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)（树形DP）
2. [P2014 [CTSC1997] 选课](https://www.luogu.com.cn/problem/P2014)（树形依赖背包）
3. [P3360 偷天换日](https://www.luogu.com.cn/problem/P3360)（树形DP+背包优化）

---
处理用时：50.06秒