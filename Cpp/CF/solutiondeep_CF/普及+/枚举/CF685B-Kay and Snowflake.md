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
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF685B/821209b858c843715556bbbb66f001612969fa03.png)第一个查询要求找出整棵树的重心 - 这是节点 $3$ 。如果我们删除节点 $3$ ，树将分裂成四个分量，其中两个大小为 $1$ ，两个大小为 $2$ 。

第二个节点的子树仅由该节点组成，所以答案是 $2$ 。

节点 $3$ 是其自身子树的重心。

节点 $5$ 的子树的重心是节点 $5$ 和 $6$ - 两个答案都被认为是正确的。

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
这些题解主要围绕树的重心问题展开，核心思路是利用树重心的性质，通过深度优先搜索（DFS）来预处理子树信息，从而高效回答多个查询。

1. **思路方面**：多数题解基于树重心的重要性质，即树的重心要么在根节点，要么在其重儿子（最大子树的根节点）为根的子树中。通过DFS遍历树，计算子树大小等信息，进而确定重心位置。
2. **算法要点**：
    - 利用DFS计算每个节点为根的子树大小 `size[]`，同时记录每个节点的重儿子。
    - 根据树重心性质判断当前节点是否为重心，若不是则从重儿子的重心往上跳，找到满足条件的重心。
3. **解决难点**：如何高效地处理多个查询，避免重复计算。通过一次DFS预处理所有子树信息，使得查询时能快速得到结果。时间复杂度控制在 $O(n)$ 或接近 $O(n)$ 级别。

### 所选的题解
1. **作者：mrsrz (赞：25)  星级：5星**
    - **关键亮点**：思路清晰，利用节点与其儿子节点关系，巧妙优化重心查找过程。每次让当前考虑节点往上跳并更新最优解，保证每个点最多被跳到一次，时间复杂度 $O(n)$ 。
    - **核心代码实现思想**：通过 `dfs` 函数计算子树大小 `sz[]` 和最大子树大小 `mx[]`，并在遍历儿子节点时，从儿子子树重心往上跳寻找当前子树重心。
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
2. **作者：Ryan_ (赞：11)  星级：4星**
    - **关键亮点**：代码简洁明了，直接利用树重心性质，即当某节点 $u$ 的最大子树节点 $v$ 的 `size` 的两倍小于 `size[u]` 时，该点为重心，否则暴力往上走找到重心。
    - **核心代码实现思想**：`dfs` 函数中，先计算子树大小 `size[]` 和最大子树大小 `f[]`，然后根据重心性质判断并寻找重心。
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
3. **作者：shao0320 (赞：2)  星级：4星**
    - **关键亮点**：简洁阐述思路，认为子树重心要么在重儿子子树中，要么是本身，直接从重儿子重心往上暴跳找到重心。
    - **核心代码实现思想**：`dfs` 函数计算子树大小 `siz[]` 并找到重儿子 `son[]`，然后根据重儿子子树大小与当前子树大小关系判断并寻找重心。
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

### 最优关键思路或技巧
1. **利用树重心性质**：树的重心要么在根节点，要么在重儿子子树中，这大大缩小了寻找重心的范围。
2. **DFS预处理**：通过一次DFS遍历整棵树，计算子树大小等必要信息，避免每次查询时重复计算，提高效率。
3. **向上跳跃优化**：从重儿子的重心开始往上跳来寻找当前子树重心，并利用剪枝策略（如发现往上跳结果变劣则停止），保证每个点最多被访问一次，有效控制时间复杂度。

### 可拓展之处
此类题目属于树结构上的查询问题，常见拓展方向有：
1. **增加限制条件**：例如在寻找重心时，对节点增加权值，要求在满足一定权值条件下寻找重心。
2. **动态查询**：树结构会动态变化（如添加或删除节点），需要实时更新重心信息。

### 相似知识点洛谷题目推荐
1. **P1395 会议**：经典的树的重心问题，通过寻找树的重心来解决会议选址问题。
2. **P2633  Count on a tree I**：结合树链剖分和主席树解决树上路径第 $k$ 小问题，涉及树结构的处理和数据结构应用。
3. **P3384 【模板】树链剖分**：树链剖分的模板题，用于高效处理树上路径问题，与本题都涉及对树结构的深入理解和操作。

### 个人心得摘录与总结
1. **作者：くろねこ**：最初尝试直接多次DFS，因数据规模大而超时。后深入研究树重心特性，在DFS回溯时增加特判，成功AC。总结出应根据题目数据范围合理选择算法，深入理解问题本质特性对解题至关重要。 

---
处理用时：43.57秒