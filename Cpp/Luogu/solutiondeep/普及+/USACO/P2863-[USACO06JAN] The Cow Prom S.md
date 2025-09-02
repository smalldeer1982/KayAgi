# 题目信息

# [USACO06JAN] The Cow Prom S

## 题目描述

有一个 $n$ 个点，$m$ 条边的有向图，请求出这个图点数大于 $1$ 的强连通分量个数。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $2\le n \le 10^4$，$2\le m\le 5\times 10^4$，$1 \leq a, b \leq n$。

## 样例 #1

### 输入

```
5 4
2 4
3 5
1 2
4 1```

### 输出

```
1```

# AI分析结果

### 综合分析与结论
本题主要是求有向图中节点数大于 1 的强连通分量个数，大部分题解采用 Tarjan 算法，少部分使用 Kosaraju 算法。Tarjan 算法通过维护 dfn（时间戳）和 low（能回溯到的最早节点）数组，结合栈来找出强连通分量；Kosaraju 算法基于两次 DFS，先对原图 DFS 记录节点访问顺序，再对反向图 DFS 找出强连通分量。

### 所选题解
- 作者：冈崎梦美 (赞：98)，4 星
  - 关键亮点：思路清晰，对 Tarjan 算法的原理和运行过程解释详细，代码注释丰富，易于理解。
  - 个人心得：无

### 重点代码
#### Tarjan 算法核心代码（冈崎梦美题解）
```cpp
void tarjan(int x)
{
    dfn[x]=low[x]=++cnt;
    s.push(x);
    vis[x]=used[x]=true;
    for(int i=0;i<G[x].size();i++)
    {
        int q=G[x][i];
        if (!dfn[q])
        {
            tarjan(q);
            low[x]=min(low[x],low[q]);
        }
        else if (vis[q]) low[x]=min(low[x],dfn[q]);
    }
    if (low[x]==dfn[x])
    {
        colornum++;
        while(s.top()!=x)
        {
            int t=s.top();
            paint(t);
        }
        paint(x);
    }
}
```
**核心实现思想**：
1. 初始化当前节点的 dfn 和 low 值，将节点入栈并标记已访问。
2. 遍历当前节点的所有出边：
    - 若边的终点未访问，递归调用 tarjan 函数，回溯后更新当前节点的 low 值。
    - 若边的终点已访问且在栈中，更新当前节点的 low 值。
3. 当当前节点的 dfn 和 low 值相等时，说明找到了一个强连通分量的根节点，将栈中该节点及其以上的节点出栈并染色。

### 最优关键思路或技巧
- **Tarjan 算法**：利用 dfn 和 low 数组结合栈的方式，在一次 DFS 中找出所有强连通分量，时间复杂度为 $O(n + m)$。
- **Kosaraju 算法**：通过两次 DFS，先对原图 DFS 记录节点访问顺序，再对反向图 DFS 找出强连通分量，时间复杂度也为 $O(n + m)$。

### 可拓展之处
- **缩点**：将强连通分量缩成一个点，将有向图转化为有向无环图（DAG），可以解决一些与图的连通性和拓扑排序相关的问题。
- **Tarjan 算法的其他应用**：求割点、割边、双连通分量等。

### 推荐题目
- [P2341 [HAOI2006]受欢迎的牛](https://www.luogu.org/problemnew/show/P2341)
- [P3387 【模板】缩点](https://www.luogu.org/problemnew/show/P3387)
- [P1262 间谍网络](https://www.luogu.org/problemnew/show/P1262)

### 个人心得摘录与总结
- **yqkkkkk**：提到如果 used 和 way 数组不用 bool 类型会炸（MLE），提醒我们在使用数组时要注意数据类型的选择，避免内存溢出。
- **Hyxss**：感谢 Rothen 大佬帮忙改了一下细节，说明在遇到问题时可以向他人请教，借助他人的经验和智慧来解决问题。

---
处理用时：31.69秒