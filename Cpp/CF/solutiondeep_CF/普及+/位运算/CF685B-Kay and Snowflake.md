# 题目信息

# Kay and Snowflake

## 题目描述

After the piece of a devilish mirror hit the Kay's eye, he is no longer interested in the beauty of the roses. Now he likes to watch snowflakes.

Once upon a time, he found a huge snowflake that has a form of the tree (connected acyclic graph) consisting of $ n $ nodes. The root of tree has index $ 1 $ . Kay is very interested in the structure of this tree.

After doing some research he formed $ q $ queries he is interested in. The $ i $ -th query asks to find a centroid of the subtree of the node $ v_{i} $ . Your goal is to answer all queries.

Subtree of a node is a part of tree consisting of this node and all it's descendants (direct or not). In other words, subtree of node $ v $ is formed by nodes $ u $ , such that node $ v $ is present on the path from $ u $ to root.

Centroid of a tree (or a subtree) is a node, such that if we erase it from the tree, the maximum size of the connected component will be at least two times smaller than the size of the initial tree (or a subtree).

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)The first query asks for a centroid of the whole tree — this is node $ 3 $ . If we delete node $ 3 $ the tree will split in four components, two of size $ 1 $ and two of size $ 2 $ .

The subtree of the second node consists of this node only, so the answer is $ 2 $ .

Node $ 3 $ is centroid of its own subtree.

The centroids of the subtree of the node $ 5 $ are nodes $ 5 $ and $ 6 $ — both answers are considered correct.

## 样例 #1

### 输入

```
7 4
1 1 3 3 5 3
1
2
3
5
```

### 输出

```
3
2
3
6
```

# AI分析结果

### 题目重写
# Kay和雪花

## 题目描述
在一片恶魔之镜的碎片击中Kay的眼睛后，他不再对玫瑰的美丽感兴趣。现在他喜欢观察雪花。

曾几何时，他发现了一片巨大的雪花，其形状为一棵树（连通无环图），由 $n$ 个节点组成。树的根节点索引为 $1$ 。Kay对这棵树的结构非常感兴趣。

经过一番研究，他提出了 $q$ 个自己感兴趣的查询。第 $i$ 个查询要求找出节点 $v_{i}$ 的子树的重心。你的目标是回答所有查询。

节点的子树是树的一部分，由该节点及其所有后代（直接或间接）组成。换句话说，节点 $v$ 的子树由节点 $u$ 组成，使得从 $u$ 到根的路径上存在节点 $v$ 。

树（或子树）的重心是这样一个节点：如果我们将其从树中删除，最大连通分量的大小将至少比初始树（或子树）的大小小两倍。

## 说明/提示
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)第一个查询要求找出整棵树的重心，答案是节点 $3$ 。如果我们删除节点 $3$ ，树将分裂为四个分量，其中两个大小为 $1$ ，两个大小为 $2$ 。

第二个节点的子树仅由该节点组成，所以答案是 $2$ 。

节点 $3$ 是其自身子树的重心。

节点 $5$ 的子树的重心是节点 $5$ 和节点 $6$ ，两个答案都被认为是正确的。

## 样例 #1
### 输入
```
7 4
1 1 3 3 5 3
1
2
3
5
```
### 输出
```
3
2
3
6
```

### 题解综合分析与结论
这些题解的核心思路都是利用树的重心性质来求解每个子树的重心。主要思路包括：
1. **预处理子树信息**：通过深度优先搜索（DFS）遍历树，计算每个节点的子树大小 `size`，以及最大子树大小 `mx` 等信息。
2. **确定重心可能位置**：利用树的重心性质，如重心在初始根节点或者最重子树上，一棵子树的重心要么是它本身，要么在其重儿子的子树中。
3. **向上跳跃查找重心**：从重儿子的重心开始向上跳，根据重心性质判断是否继续往上跳，直到找到满足条件的重心。

解决的难点在于如何高效地处理每个子树的重心查询，避免暴力搜索导致的超时问题。各题解通过不同方式优化，如利用重心性质减少搜索范围，避免重复计算等。

### 所选的题解
- **作者：mrsrz (5星)**
    - **关键亮点**：思路清晰，利用重心在子树中的位置关系，通过一次DFS预处理，在 $O(n)$ 时间复杂度内解决问题。代码简洁，逻辑紧凑。
    - **核心代码**：
```cpp
void dfs(int now,int pre){
    sz[now]=1;
    for(int i=head[now];i;i=e[i].nxt){
        dfs(e[i].to,now);
        sz[now]+=sz[e[i].to];
        mx[now]=std::max(mx[now],sz[e[i].to]);
    }
    int id=now,me=mx[now];
    for(int i=head[now];i;i=e[i].nxt){
        int it=rt[e[i].to],pre=std::max(mx[it],sz[now]-sz[it]),p=it;
        while(fa[it]!=now){
            it=fa[it];
            int New=std::max(mx[it],sz[now]-sz[it]);
            if(New<pre)pre=New,p=it;else break;
        }
        if(me>pre){
            me=pre;
            id=p;
        }
    }
    rt[now]=id;
}
```
    - **核心思想**：在DFS过程中，先计算当前节点子树大小及最大子树大小。然后遍历每个儿子，从儿子子树重心开始向上跳，更新当前最优解，记录当前节点子树的重心。
- **作者：Ryan_ (4星)**
    - **关键亮点**：代码简洁明了，直接利用树的重心性质，通过DFS计算子树信息并确定重心。注释详细，便于理解。
    - **核心代码**：
```cpp
void dfs(int x) {
    ans[x]=x;
    size[x]=1;
    int maxn=0,t=0;
    for(int i=first[x]; i; i=nxt[i]) {
        int v=go[i];
        dfs(v);
        size[x]+=size[v];
        if(size[v]>maxn) {
            maxn=size[v];
            t=v;
        }
    }
    f[x]=maxn;
    if(f[x]*2<size[x])ans[x]=x;
    else {
        int now=ans[t];
        while(fa[now]&&max(f[now],size[x]-size[now])>max(f[fa[now]],size[x]-size[fa[now]]))now=fa[now];
        ans[x]=now;
    }
}
```
    - **核心思想**：DFS过程中，先初始化当前节点为重心，计算子树大小并找到最大子树。根据最大子树大小与子树总大小关系判断当前节点是否为重心，否则从重儿子子树重心向上跳找到重心。
- **作者：shao0320 (4星)**
    - **关键亮点**：代码简洁，逻辑清晰，利用重心要么在重儿子子树中，要么是本身这一性质，通过DFS处理每个节点的子树重心。
    - **核心代码**：
```cpp
void dfs(int x)
{
    int sizz=G[x].size();siz[x]=1;
    for(int i=0;i<sizz;i++)
    {
        int v=G[x][i];
        if(v==fa[x])continue;
        dfs(v);siz[x]+=siz[v];
        if(siz[v]>siz[son[x]])son[x]=v;
    }
    if(siz[son[x]]*2<=siz[x])
    {
        ans[x]=x;
    }
    else
    {
        int xx=ans[son[x]];
        while(max(siz[son[xx]],siz[x]-siz[xx])*2>siz[x])xx=fa[xx];
        ans[x]=xx;
    }
}
```
    - **核心思想**：DFS遍历节点，计算子树大小并确定重儿子。根据重儿子子树大小与子树总大小关系判断重心，若不在当前节点，则从重儿子子树重心向上跳找到重心。

### 最优关键思路或技巧
1. **利用重心性质**：树的重心在初始根节点或者最重子树上，以及重心的其他性质，如以重心为根时所有子树大小不超过整棵树大小一半，以此来缩小搜索范围，提高效率。
2. **DFS预处理**：通过一次DFS遍历整棵树，计算每个节点的子树大小等信息，为后续查找重心提供基础数据。在DFS过程中同时处理每个节点子树的重心，避免重复计算。

### 可拓展之处
同类型题通常围绕树的重心相关性质展开，如求树中到所有点距离和最小的点（即重心），或者在树的动态变化（如添加或删除节点）过程中维护重心。类似算法套路包括利用树的结构特点，如重链剖分、DFS序等优化对树的操作，以及利用重心性质进行贪心策略的设计。

### 推荐题目
1. **P1395 会议**：经典的树的重心问题，通过寻找树的重心来解决会议选址问题。
2. **P2680 运输计划**：结合树的路径和重心相关知识，通过二分答案和树的操作来优化运输计划。
3. **P3478 [POI2008]STA-Station**：同样是关于树的重心性质应用，通过计算树中各节点到其他节点距离和，加深对树重心性质的理解。

### 个人心得摘录
- **作者：くろねこ**：一开始采用暴力DFS超时，后通过研究树的重心特性，在DFS回溯时添加特判，成功AC。总结出应合理利用树的重心性质优化算法，避免暴力搜索导致超时。 

---
处理用时：40.36秒