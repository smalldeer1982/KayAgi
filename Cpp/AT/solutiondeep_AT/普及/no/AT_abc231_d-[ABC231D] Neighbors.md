# 题目信息

# [ABC231D] Neighbors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc231/tasks/abc231_d

$ 1 $ から $ N $ の番号がついた $ N $ 人を横一列に並べる方法のうち、以下の形式の $ M $ 個の条件全てを満たすものが存在するか判定してください。

- 条件：人 $ A_i $ と人 $ B_i $ は隣り合っている

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 10^5 $
- $ 1\leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,B_i) $ は相異なる

### Sample Explanation 1

例えば $ 4,1,3,2 $ の順に並べることで全ての条件を満たすことができます。

### Sample Explanation 2

どのように並べても全ての条件を満たすことはできません。

## 样例 #1

### 输入

```
4 2

1 3

2 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4 3

1 4

2 4

3 4```

### 输出

```
No```

# AI分析结果



[题目翻译]
# [ABC231D] 相邻者

## 题目描述

给定编号为 $1$ 到 $N$ 的 $N$ 个人，判断是否存在一种将他们排成一列的方法，满足以下所有 $M$ 个条件：

- 条件：人 $A_i$ 和人 $B_i$ 必须相邻

## 说明/提示

### 数据范围
- $2 \leq N \leq 10^5$
- $0 \leq M \leq 10^5$
- $1 \leq A_i < B_i \leq N$
- $(A_i,B_i)$ 互不相同

### 算法分类
并查集

---

### 题解综合分析

需满足两个核心条件：
1. **度数限制**：每个节点的度数 ≤ 2（链式结构的必要条件）
2. **无环性**：所有边不能形成环（链式结构的充分条件）

各解法均围绕这两个条件展开，主要采用以下两种思路：
- **并查集判环**：在合并节点时检测环，同时维护度数统计
- **DFS遍历判环**：构建邻接表后通过深度优先搜索检测环路

---

### 高分题解推荐

#### 1. zzy_zzy（⭐⭐⭐⭐⭐）
**核心思路**：
- 实时维护度数数组，输入时直接判断度数是否超过2
- 使用路径压缩优化的并查集，在合并时检测环
- 即时返回错误，避免无效计算

**关键代码**：
```cpp
int fa[100010], vis[100010];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    // 初始化并查集
    for(int i=1; i<=n; i++) fa[i] = i;
    
    while(m--) {
        int x, y;
        cin >> x >> y;
        vis[x]++; vis[y]++;
        // 度数检查 & 环检查
        if(vis[x]>2 || vis[y]>2 || find(x)==find(y)) {
            cout << "No"; return 0;
        }
        fa[find(x)] = find(y); // 合并集合
    }
    cout << "Yes";
}
```

#### 2. rui_er（⭐⭐⭐⭐⭐）
**优化亮点**：
- 使用按秩合并优化并查集
- 代码风格简洁高效
- 利用STL算法快速判断最大度数

**关键实现**：
```cpp
struct Dsu {
    int fa[N], rk[N];
    void init(int x) { rep(i,1,x) fa[i]=i, rk[i]=0; }
    int find(int x) { return x==fa[x] ? x : fa[x]=find(fa[x]); }
    bool merge(int x, int y) { /* 按秩合并逻辑 */ }
};

int main() {
    dsu.init(n);
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        ++deg[u]; ++deg[v];
        if(!dsu.merge(u, v)) exit(puts("No")&0); // 合并失败说明有环
    }
    if(*max_element(deg+1, deg+1+n) > 2) puts("No");
    else puts("Yes");
}
```

#### 3. charleshe（⭐⭐⭐⭐）
**图论思路**：
- 构建邻接表后通过DFS检测环路
- 提前特判边数 ≥ 节点数的无效情况
- 度数检查与环检测分离执行

**关键片段**：
```cpp
void dfs(int u, int f) {
    if(vis[u]) exit(puts("No")&0);
    vis[u] = 1;
    for(int v : G[u]) if(v != f) dfs(v, u);
}

int main() {
    if(m >= n) { /* 提前排除 */ }
    for(int i=1; i<=n; i++) 
        if(G[i].size() > 2) return puts("No"),0;
    for(int i=1; i<=n; i++)
        if(!vis[i]) dfs(i, 0); // 连通分量判环
}
```

---

### 关键技巧总结
1. **并查集双效检测**：同时处理环检测与连通性维护
2. **实时剪枝策略**：在输入阶段即时判断度数越界，避免后续无效计算
3. **路径压缩优化**：确保并查集查询复杂度接近常数级
4. **按秩合并技巧**：平衡树高提升合并效率（见于rui_er解法）

---

### 拓展练习
1. [P1955 程序自动分析](https://www.luogu.com.cn/problem/P1955) - 并查集经典应用
2. [P2661 信息传递](https://www.luogu.com.cn/problem/P2661) - 并查集找最小环
3. [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330) - 图的相邻约束问题

---
处理用时：51.85秒