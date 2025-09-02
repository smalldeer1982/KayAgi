# 题目信息

# A Growing Tree

## 题目描述

You are given a rooted tree with the root at vertex $ 1 $ , initially consisting of a single vertex. Each vertex has a numerical value, initially set to $ 0 $ . There are also $ q $ queries of two types:

- The first type: add a child vertex with the number $ sz + 1 $ to vertex $ v $ , where $ sz $ is the current size of the tree. The numerical value of the new vertex will be $ 0 $ .
- The second type: add $ x $ to the numerical values of all vertices in the subtree of vertex $ v $ .

After all queries, output the numerical value of all of the vertices in the final tree.

## 说明/提示

In the first case, the final tree with the assigned numerical values will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1891F/450cfb88a93df41b0d4048df05e79ddc23a1fc76.png) The final tree with the assigned numerical values

## 样例 #1

### 输入

```
3
9
2 1 3
1 1
2 2 1
1 1
2 3 2
1 3
2 1 4
1 3
2 3 2
5
2 1 1
1 1
2 1 -1
1 1
2 1 1
5
1 1
1 1
2 1 1
2 1 3
2 2 10```

### 输出

```
7 5 8 6 2 
1 0 1 
4 14 4```

# AI分析结果

### 题目翻译

**题目描述**

给定一棵以 $1$ 为根的树，初始时只有一个节点 $1$，每个节点的初始值为 $0$。接下来有 $q$ 次操作，操作分为两种：

1. 第一种操作：在节点 $v$ 下添加一个子节点，编号为当前树的大小加一，新节点的值为 $0$。
2. 第二种操作：将节点 $v$ 的子树中所有节点的值加上 $x$。

在所有操作结束后，输出最终树中每个节点的值。

**说明/提示**

在第一个样例中，最终树的节点值如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1891F/450cfb88a93df41b0d4048df05e79ddc23a1fc76.png)

**样例 #1**

**输入**

```
3
9
2 1 3
1 1
2 2 1
1 1
2 3 2
1 3
2 1 4
1 3
2 3 2
5
2 1 1
1 1
2 1 -1
1 1
2 1 1
5
1 1
1 1
2 1 1
2 1 3
2 2 10
```

**输出**

```
7 5 8 6 2 
1 0 1 
4 14 4
```

### 算法分类
树状数组、DFS、离线处理

### 题解分析与结论

这道题的核心在于如何处理动态树的子树修改操作。由于树的结构在操作过程中不断变化，直接在线处理会比较复杂。大多数题解采用了离线处理的方法，即先构建出最终的树结构，然后通过DFS序将树转化为线性序列，最后使用树状数组或线段树来处理子树修改和查询操作。

### 高星题解

#### 题解1：RsCb (5星)
**关键亮点**：
- 离线处理：先构建完整的树结构，然后倒序处理操作。
- 使用DFS序将树转化为线性序列，方便区间修改。
- 使用树状数组维护差分序列，实现高效的区间修改和单点查询。

**核心代码**：
```cpp
void slv(){
    scanf("%lld", &q);
    n = 1;
    for(int i=1; i<=q; i++){
        scanf("%lld", t+i);
        if(t[i] == 1){
            scanf("%lld", v+i);
            e[v[i]].push_back(++n);
            v[i] = n;
        }
        else{
            scanf("%lld%lld", v+i, x+i);
        }
    }
    cnt = 0; dfs(1);
    t[0] = 1; v[0] = 1;
    for(int i=q; i>=0; i--){
        if(t[i] == 1){
            w[v[i]] = st::qry(dfn[v[i]]);
        }
        else{
            st::upd(dfn[v[i]], dfn[v[i]]+sz[v[i]], x[i]);
        }
    }
    for(int i=1; i<=n; i++)
        printf("%lld%c", w[i], " \n"[i==n]);
    for(int i=1; i<=n; i++){
        e[i].clear();
    }
    st::clear();
}
```

#### 题解2：Svemit (4星)
**关键亮点**：
- 使用树状数组维护从根节点到当前节点的操作链。
- 通过DFS遍历树，动态维护每个节点的值。
- 回溯时撤销操作，避免影响其他节点的计算。

**核心代码**：
```cpp
void dfs(int u) {
    for(auto k : g[u]) {
        modify(k.se, k.fi);
    }
    ans[u] = query(q) - query(u - 1);
    for(auto v : e[u]) {
        dfs(v);
    }
    for(auto k : g[u]) {
        modify(k.se, -k.fi);
    }
}
```

#### 题解3：_Wind_Leaves_ShaDow_ (4星)
**关键亮点**：
- 离线处理，倒序操作，避免动态树的复杂性。
- 使用DFS序将树转化为线性序列，方便区间修改。
- 使用线段树实现区间修改和单点查询。

**核心代码**：
```cpp
void solve(){
    n=1;idd=0;
    Q=read();
    for(ri i=1;i<=Q;i++){
        op[i]=read()-1;xp[i]=read();
        if(op[i])vp[i]=read();
        else v[xp[i]].pb(++n);
    }
    dfs(1,0);
    build(1,idd,1);
    for(;Q;Q--){
        if(op[Q])add(ld[xp[Q]],rd[xp[Q]],1,idd,1,vp[Q]);
        else{
            Ans[n]=sqr(ld[n],1,idd,1);
            n--;
        }
    }
    Ans[1]=sqr(1,1,n,1);
    for(ri i=1;i<=idd;i++){
        write(Ans[i]);
        putchar(32);
    }
    puts("");
    for(ri i=1;i<=idd;i++)v[i].resize(0);
    return;
}
```

### 最优关键思路
1. **离线处理**：先构建完整的树结构，避免动态树的复杂性。
2. **DFS序**：将树转化为线性序列，方便区间修改和查询。
3. **树状数组/线段树**：高效处理区间修改和单点查询。

### 拓展思路
类似的问题可以扩展到其他动态树结构，如动态森林、动态图的子树操作等。可以通过离线处理、DFS序和树状数组/线段树等方法来简化问题。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)
3. [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)

### 个人心得
在处理动态树的问题时，离线处理是一个非常有效的策略。通过先构建完整的树结构，可以避免动态树的复杂性，简化问题的处理。此外，DFS序和树状数组/线段树的结合，能够高效地处理子树修改和查询操作。

---
处理用时：55.81秒