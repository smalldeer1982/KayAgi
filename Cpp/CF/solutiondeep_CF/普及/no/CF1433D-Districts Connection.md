# 题目信息

# Districts Connection

## 题目描述

There are $ n $ districts in the town, the $ i $ -th district belongs to the $ a_i $ -th bandit gang. Initially, no districts are connected to each other.

You are the mayor of the city and want to build $ n-1 $ two-way roads to connect all districts (two districts can be connected directly or through other connected districts).

If two districts belonging to the same gang are connected directly with a road, this gang will revolt.

You don't want this so your task is to build $ n-1 $ two-way roads in such a way that all districts are reachable from each other (possibly, using intermediate districts) and each pair of directly connected districts belong to different gangs, or determine that it is impossible to build $ n-1 $ roads to satisfy all the conditions.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
5
1 2 2 1 3
3
1 1 1
4
1 1000 101 1000
4
1 2 3 4```

### 输出

```
YES
1 3
3 5
5 4
1 2
NO
YES
1 2
2 3
3 4
YES
1 2
1 3
1 4```

# AI分析结果

### 题目翻译
#### 题目描述
小镇中有 $n$ 个区域，第 $i$ 个区域属于第 $a_i$ 个强盗帮派。最初，这些区域之间没有任何连接。

你是这个城市的市长，希望建造 $n-1$ 条双向道路来连接所有区域（两个区域可以直接连接，也可以通过其他连接的区域间接连接）。

如果两个属于同一帮派的区域直接通过一条道路连接，该帮派将会发动叛乱。

为了避免这种情况，你的任务是建造 $n-1$ 条双向道路，使得所有区域之间都可以相互到达（可能通过中间区域），并且每一对直接连接的区域属于不同的帮派，或者确定无法建造满足所有条件的 $n-1$ 条道路。

你需要回答 $t$ 个独立的测试用例。

### 算法分类
构造、并查集

### 题解分析与结论
本题的核心在于构造一个满足条件的树结构，使得所有区域连通且直接相连的区域属于不同的帮派。题解主要集中在以下思路：

1. **构造法**：大多数题解采用构造法，通过选择一个中心节点（如第一个节点），然后将所有与中心节点不同帮派的节点与其连接，再将同帮派的节点连接到这些不同帮派的节点上。这种方法的时间复杂度为 $O(n)$，简洁高效。
  
2. **并查集**：部分题解使用并查集来维护连通性，通过遍历所有可能的边，选择符合条件的边来构建树。这种方法的时间复杂度为 $O(n^2)$，虽然较慢，但思路清晰，适合理解并查集的应用。

3. **菊花图构造**：一些题解采用菊花图的构造方式，通过将中心节点与所有不同帮派的节点连接，再将同帮派的节点连接到这些不同帮派的节点上。这种构造方式简单直观，易于实现。

### 高星题解推荐
#### 题解1：KSToki (4星)
**关键亮点**：
- 简洁的构造思路，时间复杂度为 $O(n)$。
- 代码清晰，易于理解。

**核心代码**：
```cpp
for(register int i=2;i<=n;++i)
    if(a[i]!=a[1])
    {
        printf("1 %d\n",i);
        t=i;
    }
for(register int i=2;i<=n;++i)
    if(a[i]==a[1])
        printf("%d %d\n",i,t);
```
**核心思想**：首先将所有与第一个节点不同帮派的节点与其连接，然后将同帮派的节点连接到这些不同帮派的节点上。

#### 题解2：sto__Liyhzh__orz (4星)
**关键亮点**：
- 采用树的分层构造思路，清晰易懂。
- 代码结构良好，逻辑清晰。

**核心代码**：
```cpp
for(int i=2;i<=n;i++)
{
    if(a[i]!=a[1])
    {
        cout<<"1 "<<i<<endl;
        id=i;
    }
}
for(int i=2;i<=n;i++)
{
    if(a[i]==a[1]) cout<<i<<" "<<id<<endl;
}
```
**核心思想**：将所有与第一个节点不同帮派的节点作为第二层节点，将同帮派的节点作为第三层节点，连接到第二层节点上。

#### 题解3：fls233666 (4星)
**关键亮点**：
- 使用并查集维护连通性，思路清晰。
- 通过预处理所有可能的边，确保构造的树满足条件。

**核心代码**：
```cpp
for(rgt i=1;i<=n;i++){
    for(rgt j=i+1;j<=n;j++){
        if(ai[i]!=ai[j]){
            tmp.u=i;
            tmp.v=j;
            e.push_back(tmp);
        }
    }
}
for(rgt fu,fv,i=0;i<e.size();i++){
    fu=getfa(e[i].u);
    fv=getfa(e[i].v);
    if(fu!=fv){
        fa[fu]=fv;
        lu++;
        use[lu]=e[i];
    }
    if(lu==n-1)
        break;
}
```
**核心思想**：预处理所有可能的边，使用并查集选择符合条件的边来构建树。

### 最优关键思路
最优的思路是采用构造法，通过选择一个中心节点，将所有与中心节点不同帮派的节点与其连接，再将同帮派的节点连接到这些不同帮派的节点上。这种方法时间复杂度低，代码简洁，易于实现。

### 拓展思路
类似的问题可以扩展到图论中的树构造问题，如最小生成树、最大生成树等。通过选择合适的中心节点和边，可以构造出满足特定条件的树结构。

### 推荐题目
1. [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
2. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
3. [P3371 【模板】单源最短路径](https://www.luogu.com.cn/problem/P3371)

---
处理用时：32.67秒