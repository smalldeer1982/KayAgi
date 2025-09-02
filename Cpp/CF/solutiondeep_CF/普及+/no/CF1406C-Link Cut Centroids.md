# 题目信息

# Link Cut Centroids

## 题目描述

#### 题意

给定一棵节点数为 $n$ 的树 ， 删一条边然后加上一条边 ， 使得该树的重心唯一 。（删掉的边和加上的边可以是同一条）

## 样例 #1

### 输入

```
2
5
1 2
1 3
2 4
2 5
6
1 2
1 3
1 4
2 5
2 6```

### 输出

```
1 2
1 2
1 3
2 3```

# AI分析结果

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先判断树的重心数量，若只有一个重心，就随便删一条边再加回来；若有两个重心，就通过调整边的连接方式使重心唯一。各题解的主要区别在于实现细节和调整边的具体方式。

- **思路对比**：大部分题解都是基于树的重心性质，对于两个重心的情况，有的是从一个重心的子树中取叶子节点连到另一个重心上，有的是将一个重心的儿子节点连到另一个重心上。
- **算法要点**：都需要先找出树的重心，一般通过深度优先搜索（DFS）计算每个节点的子树大小和最大子树大小来确定重心。
- **解决难点**：主要难点在于证明调整边的连接方式后树的重心唯一，不同题解采用了不同的证明方法，如反证法、分析子树大小变化等。

### 所选题解
- **作者：QwQcOrZ (赞：29) - 4星**
    - **关键亮点**：思路清晰，代码实现简洁，对树的重心性质的运用和证明较为详细。
- **作者：Chinese_zjc_ (赞：10) - 4星**
    - **关键亮点**：分类讨论明确，代码结构清晰，对调整边的方式和证明过程有详细说明。
- **作者：gyh20 (赞：6) - 4星**
    - **关键亮点**：思路简洁明了，代码实现简单，对调整边的方式有合理的解释。

### 重点代码
#### 作者：QwQcOrZ
```cpp
// 计算子树大小和最大子树大小
void dfs(int now,int fa)
{
    siz[now]=Max[now]=1;
    for (int i=head[now];i;i=e[i].nxt)
    if (e[i].to!=fa)
    {
        int to=e[i].to;
        dfs(to,now);
        siz[now]+=siz[to];
        Max[now]=max(Max[now],siz[to]);
    }
    Max[now]=max(Max[now],n-siz[now]);
    if (Max[now]<Min) Min=Max[now];
}
// 找到叶子节点
int find(int now,int fa)
{
    for (int i=head[now];i;i=e[i].nxt)
    if (e[i].to!=fa)
    {
        tmp2=now;
        return find(e[i].to,now);
    }
    return now;
}
```
核心实现思想：通过 `dfs` 函数计算每个节点的子树大小和最大子树大小，从而找到重心；通过 `find` 函数找到一个重心子树中的叶子节点。

#### 作者：Chinese_zjc_
```cpp
// 初始化子树大小
void init(int now)
{
    siz[now]=1;
    for(int i=0;i<(int)son[now].size();++i)
    {
        if(fa[now]==son[now][i])
        {
            swap(son[now][i],son[now].back());
            --i;
            son[now].pop_back();
            continue;
        }
        fa[son[now][i]]=now;
        init(son[now][i]);
        siz[now]+=siz[son[now][i]];
    }
}
// 求删掉这个点后的最大连通块大小
void dfs(int now)
{
    v[now]=siz[1]-siz[now];
    for(int i=0;i<(int)son[now].size();++i)
    {
        v[now]=max(v[now],siz[son[now][i]]);
        dfs(son[now][i]);
    }
}
// 找到叶子节点
int fin(int now)
{
    if(son[now].size())
    {
        return fin(son[now][0]);
    }
    else
    {
        return now;
    }
}
```
核心实现思想：`init` 函数初始化每个节点的子树大小，`dfs` 函数计算删掉每个节点后的最大连通块大小，从而找到重心；`fin` 函数找到一个重心子树中的叶子节点。

#### 作者：gyh20
```cpp
// 计算子树大小和最大子树大小，找到重心
void dfs(int x,int f){
    fa[x]=f,size[x]=1;
    int mx=0;
    for(int y:g[x]){
        if(y==f)continue;
        dfs(y,x);
        size[x]+=size[y];
        mx=max(mx,size[y]);
    }
    mx=max(mx,n-size[x]);
    if(mx<minn)minn=mx,cent1=x,cent2=0;
    else if(mx==minn)cent2=x;
}
// 找到叶子节点
void dfs2(int x,int f){
    if(g[x].size()==1){
        S=x;
        return ;
    }
    for(int y:g[x]){
        if(y==f)continue;
        dfs2(y,x);
    }
}
```
核心实现思想：`dfs` 函数计算每个节点的子树大小和最大子树大小，找到重心；`dfs2` 函数找到一个重心子树中的叶子节点。

### 最优关键思路或技巧
- 利用树的重心性质：一棵树最多有两个重心，且相邻。通过深度优先搜索计算子树大小和最大子树大小来确定重心。
- 对于两个重心的情况，通过调整边的连接方式改变子树大小，使两个重心的最大子树大小不再相等，从而使重心唯一。

### 可拓展之处
同类型题可能会有更多的限制条件，如要求调整边的次数最少、调整边的权值最小等。类似算法套路可以应用到其他树的结构调整问题中，如树的直径调整、树的连通性调整等。

### 推荐题目
- [P1364 医院设置](https://www.luogu.com.cn/problem/P1364)：求树的重心相关问题。
- [P2986 [USACO10MAR]Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)：涉及树的重心和树的遍历。
- [P4299 首都](https://www.luogu.com.cn/problem/P4299)：与树的重心和树的结构调整有关。

### 个人心得
- **作者：code_hunter**：提到因为没有注意边必须是存在的而WA，提醒我们在做题时要仔细审题，注意题目中的细节。

---
处理用时：47.80秒