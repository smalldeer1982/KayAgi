# 题目信息

# Medals

## 题目描述

[problemUrl]: https://atcoder.jp/contests/snuke21/tasks/snuke21_g

# AI分析结果

### 题目内容
【题目描述】
有 $n$ 个人进行比赛，选手的编号是从 $1$ 到 $n$。不会存在排名相同的情况。给定 $m$ 个关系，满足 $a_i$ 的排名在 $b_i$ 的前面，问前三名的合法方案有多少种。

### 算法分类
图论

### 题解分析与结论
该题解通过将问题转化为图论问题，利用拓扑排序和集合划分的方法，计算前三名的合法方案数。具体思路是将每个关系转换为图中的边，然后通过拓扑排序得到节点的顺序，并将节点按度数划分为不同的集合，最后根据集合中的节点计算合法方案数。

### 所选题解
#### 题解作者：xuan_gong_dong (赞：2)
- **星级**: 4
- **关键亮点**: 
  - 将问题转化为图论问题，利用拓扑排序和集合划分的方法，思路清晰。
  - 代码实现较为完整，考虑了多种情况，如`000`、`001`、`011`、`012`等方案的计算。
  - 使用了`queue`进行拓扑排序，`vector`存储节点和边，数据结构选择合理。

### 关键代码片段
```cpp
for(int i=1;i<=n;i++)
{
    if(in[i]==0)
    {
        q.push(i);
    }
}
while(!q.empty())
{
    int x=q.front();
    q.pop();
    for(int i=0;i<be[x].size();i++)
    {
        if(book[be[x][i]]==1)
        {
            book[x]=1;
            fa[x].clear();
            break;
        }	
        fa[x].push_back(be[x][i]);
        for(int j=0;j<fa[be[x][i]].size();j++)
        {
            fa[x].push_back(fa[be[x][i]][j]);
        }
    }
    if(!book[x])
    {
        sort(fa[x].begin(),fa[x].end());
        fa[x].erase(unique(fa[x].begin(),fa[x].end()),fa[x].end());
        if(fa[x].size()>=3)
        {
            book[x]=1;
            fa[x].clear();
        }
    }
    for(int i=0;i<oe[x].size();i++)
    {
        in[oe[x][i]]--;
        if(in[oe[x][i]]==0)
        {
            q.push(oe[x][i]);
        }
    }
}
```
**核心实现思想**: 通过拓扑排序处理节点，并根据节点的度数划分集合，最终计算合法方案数。

### 最优关键思路或技巧
- **图论转化**: 将排名关系转化为图中的边，利用图的性质解决问题。
- **拓扑排序**: 通过拓扑排序确定节点的顺序，便于后续计算。
- **集合划分**: 将节点按度数划分为不同的集合，简化问题复杂度。

### 可拓展之处
- **类似问题**: 可以拓展到其他需要处理依赖关系的问题，如任务调度、课程安排等。
- **算法优化**: 可以进一步优化集合划分和方案计算的方法，减少时间复杂度。

### 推荐题目
1. [P1113 杂务](https://www.luogu.com.cn/problem/P1113)
2. [P1983 车站分级](https://www.luogu.com.cn/problem/P1983)
3. [P2146 [NOI2015] 软件包管理器](https://www.luogu.com.cn/problem/P2146)

---
处理用时：20.95秒