# 题目信息

# Harmonious Graph

## 题目描述

You're given an undirected graph with $ n $ nodes and $ m $ edges. Nodes are numbered from $ 1 $ to $ n $ .

The graph is considered harmonious if and only if the following property holds:

- For every triple of integers $ (l, m, r) $ such that $ 1 \le l < m < r \le n $ , if there exists a path going from node $ l $ to node $ r $ , then there exists a path going from node $ l $ to node $ m $ .

In other words, in a harmonious graph, if from a node $ l $ we can reach a node $ r $ through edges ( $ l < r $ ), then we should able to reach nodes $ (l+1), (l+2), \ldots, (r-1) $ too.

What is the minimum number of edges we need to add to make the graph harmonious?

## 说明/提示

In the first example, the given graph is not harmonious (for instance, $ 1 < 6 < 7 $ , node $ 1 $ can reach node $ 7 $ through the path $ 1 \rightarrow 2 \rightarrow 7 $ , but node $ 1 $ can't reach node $ 6 $ ). However adding the edge $ (2, 4) $ is sufficient to make it harmonious.

In the second example, the given graph is already harmonious.

## 样例 #1

### 输入

```
14 8
1 2
2 7
3 4
6 3
5 7
3 8
6 8
11 12
```

### 输出

```
1
```

## 样例 #2

### 输入

```
200000 3
7 9
9 8
4 5
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
你得到了一个包含 $n$ 个节点和 $m$ 条边的无向图。节点编号从 $1$ 到 $n$。

当且仅当满足以下属性时，该图被认为是和谐的：

- 对于每一个整数三元组 $(l, m, r)$，满足 $1 \le l < m < r \le n$，如果存在一条从节点 $l$ 到节点 $r$ 的路径，那么就存在一条从节点 $l$ 到节点 $m$ 的路径。

换句话说，在一个和谐的图中，如果我们可以通过边从节点 $l$ 到达节点 $r$（$l < r$），那么我们也应该能够到达节点 $(l + 1), (l + 2), \ldots, (r - 1)$。

我们需要添加的最少边数是多少才能使图变得和谐？

### 算法分类
并查集

### 综合分析与结论
这些题解都围绕并查集来解决使图和谐所需添加最少边数的问题。不同题解在实现细节和优化方式上有所不同。
- 灵茶山艾府的题解思路简洁，通过维护当前能访问到的最大点，若当前点所在连通分量的最大点不等于该最大点，则连边，逻辑清晰。
- fengxiaoyi 的题解采用暴力加优化的方式，对每个节点的连通块进行检查，通过标记避免重复访问，减少时间复杂度。
- 李伟业的题解考虑了连通块的最值和节点和，但在更新连通块最值时易出错，且代码相对复杂。
- ZLCT 的题解转换题意，采用类似双指针的思路，结合并查集维护连通块右端点，优化了时间复杂度。

### 所选的题解
- 灵茶山艾府（4星）：关键亮点是思路简洁清晰，通过维护最大点的方式，巧妙地利用并查集合并连通分量，代码实现简洁高效。
- ZLCT（4星）：关键亮点是转换题意，采用类似双指针的思路，结合并查集维护连通块右端点，将时间复杂度优化到 $O(n\alpha(n))$。
- fengxiaoyi（4星）：关键亮点是采用暴力加优化的方式，通过标记避免重复访问，减少不必要的计算，在一定程度上优化了时间复杂度。

### 重点代码
#### 灵茶山艾府
```go
// 初始化并查集
fa := make([]int, n+1)
for i := range fa {
    fa[i] = i
}
var find func(int) int
find = func(x int) int {
    if fa[x] != x {
        fa[x] = find(fa[x])
    }
    return fa[x]
}
merge := func(from, to int) int {
    // 把小的合并到大的上，并返回大的
    ff, ft := find(from), find(to)
    if ff > ft {
        ff, ft = ft, ff
    }
    fa[ff] = ft
    return ft
}

for ; m > 0; m-- {
    Fscan(in, &v, &w)
    merge(v, w)
}
max := -1
for i := range fa {
    if i > max {
        max = find(i)
    } else if find(i) != max {
        max = merge(i, max)
        ans++
    }
}
```
核心实现思想：先初始化并查集，将小的连通分量合并到大的连通分量上。然后遍历每个点，维护当前能访问到的最大点，若当前点所在连通分量的最大点不等于该最大点，则连边。

#### ZLCT
```cpp
int find(int x){
    if(x==fa[x])return x;
    maxx[fa[x]]=max(maxx[fa[x]],maxx[x]);
    return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    x=find(x);y=find(y);
    if(x==y)return;
    if(rk[x]==rk[y]){
        rk[x]++;fa[y]=x;
        maxx[x]=max(maxx[x],maxx[y]);
    }else if(rk[x]>rk[y]){
        fa[y]=x;
        maxx[x]=max(maxx[x],maxx[y]);
    }else{
        fa[x]=y;
        maxx[y]=max(maxx[x],maxx[y]);
    }
}
for(int i=1;i<=n;i=maxx[find(i)]+1){
    for(int j=i+1;j<=maxx[find(i)];++j){
        if(find(i)==find(j))continue;
        merge(i,j);
        ans++;
    }
}
```
核心实现思想：通过并查集维护连通块的右端点，采用类似双指针的思路，枚举左端点 $i$，并不断根据递归思路枚举 $j$，若 $i$ 和 $j$ 不连通，则连边。

#### fengxiaoyi
```cpp
int Find(int k){
    if(fa[k]==k) return k;
    return fa[k]=Find(fa[k]);
}
void H(int k1,int k2){
    int x=Find(k1),y=Find(k2);
    fa[x]=y;
    mn[y]=min(mn[x],mn[y]);
    mx[y]=max(mx[x],mx[y]);
}
for(int i=1;i<=n;i++){
    int f=Find(i);
    if(v[f]) continue;
    v[f]=1;
    for(int j=mn[f]+1;j<mx[f];j++){
        int fj=Find(j);
        if(fj!=f) H(fj,f),ans++;
    }
}
```
核心实现思想：先初始化并查集，合并连通块时更新连通块的最值。然后遍历每个节点，若该连通块未被访问过，则暴力搜索该连通块内的节点，若节点不在该连通块内，则合并并增加边数。

### 最优关键思路或技巧
- 利用并查集维护连通分量，在合并时更新连通分量的最值信息。
- 采用标记的方式避免重复访问，减少不必要的计算。
- 类似双指针的思路，结合并查集维护连通块的右端点，优化时间复杂度。

### 拓展思路
同类型题或类似算法套路：
- 其他图的连通性问题，如判断图是否连通、计算连通分量的数量等。
- 利用并查集解决集合合并与查询的问题，如 Kruskal 算法求最小生成树。

### 推荐洛谷题目
- P1197 [JSOI2008]星球大战：考察并查集的逆序操作。
- P1525 关押罪犯：考察并查集的扩展域或边带权。
- P3367 【模板】并查集：考察并查集的基本操作。

### 个人心得
李伟业：开开心心的敲完，样例都过了，交，WA，自闭，改！问题出在每次新加入连通块时，当前连通块的最大值和最小值都可能会发生改变。另外，和谐了的连通块要标记，不要再找块中的点了，否则会T。
总结：在使用并查集维护连通块信息时，要注意更新连通块的最值信息，同时要避免重复计算，可通过标记已处理的连通块来优化时间复杂度。 

---
处理用时：51.43秒