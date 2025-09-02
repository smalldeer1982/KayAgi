# 题目信息

# Anton and Tree

## 题目描述

Anton is growing a tree in his garden. In case you forgot, the tree is a connected acyclic undirected graph.

There are $ n $ vertices in the tree, each of them is painted black or white. Anton doesn't like multicolored trees, so he wants to change the tree such that all vertices have the same color (black or white).

To change the colors Anton can use only operations of one type. We denote it as $ paint(v) $ , where $ v $ is some vertex of the tree. This operation changes the color of all vertices $ u $ such that all vertices on the shortest path from $ v $ to $ u $ have the same color (including $ v $ and $ u $ ). For example, consider the tree

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/e17d4eda0dc67dbbca220a370e8bf45f5d1faeb0.png)and apply operation $ paint(3) $ to get the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/eabfeb953964c829d6d1820bd3bcad690b9ae826.png)Anton is interested in the minimum number of operation he needs to perform in order to make the colors of all vertices equal.

## 说明/提示

In the first sample, the tree is the same as on the picture. If we first apply operation $ paint(3) $ and then apply $ paint(6) $ , the tree will become completely black, so the answer is $ 2 $ .

In the second sample, the tree is already white, so there is no need to apply any operations and the answer is $ 0 $ .

## 样例 #1

### 输入

```
11
0 0 0 1 1 0 1 0 0 1 1
1 2
1 3
2 4
2 5
5 6
5 7
3 8
3 9
3 10
9 11
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
0 0 0 0
1 2
2 3
3 4
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
## 安东和树

### 题目描述
安东正在他的花园里种一棵树。如果你忘了的话，树是一种连通的无环无向图。

树中有 $n$ 个顶点，每个顶点被染成黑色或白色。安东不喜欢彩色的树，所以他想改变这棵树，使所有顶点具有相同的颜色（黑色或白色）。

为了改变颜色，安东只能使用一种类型的操作。我们将其表示为 $paint(v)$，其中 $v$ 是树的某个顶点。此操作会改变所有顶点 $u$ 的颜色，使得从 $v$ 到 $u$ 的最短路径上的所有顶点（包括 $v$ 和 $u$）具有相同的颜色。例如，考虑这棵树：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/e17d4eda0dc67dbbca220a370e8bf45f5d1faeb0.png)
并应用操作 $paint(3)$ 得到以下结果：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF734E/eabfeb953964c829d6d1820bd3bcad690b9ae826.png)
安东感兴趣的是，为了使所有顶点的颜色相同，他需要执行的最少操作次数。

### 说明/提示
在第一个样例中，树与图片中的树相同。如果我们先应用操作 $paint(3)$，然后应用 $paint(6)$，树将完全变成黑色，所以答案是 $2$。

在第二个样例中，树已经是白色的，所以不需要应用任何操作，答案是 $0$。

### 样例 #1
#### 输入
```
11
0 0 0 1 1 0 1 0 0 1 1
1 2
1 3
2 4
2 5
5 6
5 7
3 8
3 9
3 10
9 11
```
#### 输出
```
2
```

### 样例 #2
#### 输入
```
4
0 0 0 0
1 2
2 3
3 4
```
#### 输出
```
0
```

### 综合分析与结论
这些题解的核心思路都是将相同颜色的连通块缩点，把原树转化为黑白相间的树，然后求该树的直径，最终答案为 `(直径 + 1) / 2`。不同题解在缩点和求直径的实现方法上有所差异。
- **缩点方法**：部分题解使用并查集将相邻同色点合并，部分题解通过深度优先搜索（DFS）判断节点颜色是否相同来缩点。
- **求直径方法**：主要有两遍 DFS 和树形 DP 两种方法。

### 所选题解
- **作者：ShallowDream 雨梨（5 星）**
    - **关键亮点**：思路清晰，不使用并查集，通过设置边权来简化问题，代码简洁，使用树形 DP 求树的直径。
    - **核心代码**：
```cpp
void dp(int x,int fa){
    for(int i=head[x];i;i=a[i].next){
        int to=a[i].to;
        if(to==fa) continue;
        dp(to,x);
        anss=max(anss,d[x]+d[to]+a[i].v);
        d[x]=max(d[x],d[to]+a[i].v);
    }
}
```
    - **核心思想**：在树形 DP 过程中，`d[x]` 表示以 `x` 为根节点的子树中到 `x` 的最长路径，通过递归更新 `d[x]` 和 `anss`（树的直径）。

- **作者：superMB（4 星）**
    - **关键亮点**：详细解释了缩点和求直径的过程，使用并查集缩点，提供了两种不同的代码实现，一种使用两遍 DFS 求直径，另一种优化了缩点过程。
    - **个人心得**：强调了数据量较大时使用读优输优的重要性。
    - **核心代码（并查集部分）**：
```cpp
inline int find(int x){
    if(father[x]!=x) father[x]=find(father[x]);
    return father[x];
}
inline void join(int x,int y){
    x=find(x),y=find(y);
    if(x!=y) father[x]=y;
}
```
    - **核心思想**：通过 `find` 函数查找节点的根节点，`join` 函数将两个节点合并到同一个集合中。

- **作者：二狗子（4 星）**
    - **关键亮点**：思路清晰，使用两次 BFS 求树的直径，在 BFS 过程中判断节点颜色是否相同来更新距离。
    - **核心代码（BFS 部分）**：
```cpp
void bfs1(){
    sum=0;
    d[1]=0;
    v[1]=1;
    q.push(1);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=Next[i]){
            int y=ver[i];
            if(v[y]) continue;
            if(color[x]==color[y]){
                d[y]=d[x];
            }
            else{
                d[y]=d[x]+1;
                if(d[y]>sum){
                    sum=d[y];
                    s=y;
                }
            }
            q.push(y);
            v[y]=1;
        }
    }
}
```
    - **核心思想**：在 BFS 过程中，若相邻节点颜色相同则距离不变，否则距离加 1，通过两次 BFS 找到树的直径。

### 最优关键思路或技巧
- **缩点思想**：将相同颜色的连通块缩成一个点，把原问题转化为求黑白相间树的直径问题，简化了问题的复杂度。
- **边权设置**：不使用并查集时，通过设置边权，若边两端颜色相同则边权为 0，否则为 1，避免了缩点的复杂操作。

### 拓展思路
同类型题目可能会改变树的性质（如带权树）或操作规则（如每次操作的限制不同），但核心思路仍然是将问题转化为树的直径问题。类似算法套路包括使用并查集进行集合合并、使用 DFS 或 BFS 遍历树等。

### 推荐题目
- [P1099 树网的核](https://www.luogu.com.cn/problem/P1099)
- [P3304 [SDOI2013]直径](https://www.luogu.com.cn/problem/P3304)
- [P4408 [NOI2003] 逃学的小孩](https://www.luogu.com.cn/problem/P4408)

### 个人心得总结
- **superMB**：数据量较大时，使用读优输优可以提高程序效率。
- **HSY666**：使用并查集缩点时，要先把所有相同颜色连通块缩好点，再建图，否则会出现不是根与根相连的情况导致 WA。 

---
处理用时：43.14秒