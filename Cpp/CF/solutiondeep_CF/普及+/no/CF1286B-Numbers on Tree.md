# 题目信息

# Numbers on Tree

## 题目描述

Evlampiy was gifted a rooted tree. The vertices of the tree are numbered from $ 1 $ to $ n $ . Each of its vertices also has an integer $ a_i $ written on it. For each vertex $ i $ , Evlampiy calculated $ c_i $ — the number of vertices $ j $ in the subtree of vertex $ i $ , such that $ a_j < a_i $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1286B/07b62e73f95acfbaad655944569605534cdd333f.png)Illustration for the second example, the first integer is $ a_i $ and the integer in parentheses is $ c_i $ After the new year, Evlampiy could not remember what his gift was! He remembers the tree and the values of $ c_i $ , but he completely forgot which integers $ a_i $ were written on the vertices.

Help him to restore initial integers!

## 样例 #1

### 输入

```
3
2 0
0 2
2 0```

### 输出

```
YES
1 2 1```

## 样例 #2

### 输入

```
5
0 1
1 3
2 1
3 0
2 0```

### 输出

```
YES
2 3 2 1 2```

# AI分析结果

### 题目内容翻译
# 树上的数字

## 题目描述
Evlampiy 收到了一棵有根树作为礼物。树的顶点编号从 $1$ 到 $n$。每个顶点上还写有一个整数 $a_i$。对于每个顶点 $i$，Evlampiy 计算出了 $c_i$ —— 以顶点 $i$ 为根的子树中满足 $a_j < a_i$ 的顶点 $j$ 的数量。

![图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1286B/07b62e73f95acfbaad655944569605534cdd333f.png) 第二个样例的图示，第一个整数是 $a_i$，括号内的整数是 $c_i$

新年过后，Evlampiy 不记得他的礼物是什么了！他记得树的结构和 $c_i$ 的值，但完全忘记了每个顶点上写的整数 $a_i$ 是什么。

请帮助他恢复最初的整数！

## 样例 #1
### 输入
```
3
2 0
0 2
2 0
```
### 输出
```
YES
1 2 1
```

## 样例 #2
### 输入
```
5
0 1
1 3
2 1
3 0
2 0
```
### 输出
```
YES
2 3 2 1 2
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是围绕构造满足条件的权值方案展开。首先判断无解情况，即当 $c_i$ 大于等于以 $i$ 为根的子树大小时无解。对于有解的情况，不同题解采用了不同的方法来构造权值。

- **思路对比**：
    - 部分题解（如 ix35、kevinZ99、zhouzihang1 等）从点权最小的点开始确定，通过维护集合或标记未使用的数，逐步确定每个点的权值。
    - 部分题解（如 gyh20、liuyz11、yspm、_JF_ 等）通过合并子树信息，将当前节点插入到合适的位置，以满足 $c_i$ 的要求。
    - 部分题解（如 Purple_wzy、KiDDOwithTopTree）使用堆或平衡树等数据结构来优化操作。
- **算法要点**：
    - 利用深度优先搜索（DFS）遍历树的节点。
    - 维护子树的信息，如子树大小、节点权值等。
    - 根据 $c_i$ 的值确定当前节点的权值。
- **解决难点**：
    - 处理节点权值相等的情况，多数题解通过构造不同权值的方案来避免。
    - 优化时间复杂度，部分题解使用数据结构（如堆、平衡树）来优化操作。

### 所选题解
- **ix35（4星）**
    - **关键亮点**：思路清晰，容易理解。通过优先队列维护点权最小的点，逐步确定每个点的权值。代码实现简洁明了。
    - **个人心得**：无
- **KiDDOwithTopTree（4星）**
    - **关键亮点**：提供了两种时间复杂度的解法，包括用数组实现的 $O(n^2)$ 解法和用平衡树优化的 $O(n \log n)$ 解法，对数据结构的运用有一定的参考价值。
    - **个人心得**：作者表示在模拟赛上一开始没做出来，后来才发现是自己会的题，提醒我们要仔细审题。
- **liuyz11（4星）**
    - **关键亮点**：利用 pair 方便排序，将当前节点插入到合适的位置，思路简单直接，代码实现也比较清晰。
    - **个人心得**：作者表示一开始不会做，百度题解后才通过，说明参考他人思路可以帮助我们解决问题。

### 重点代码
#### ix35 的核心代码
```cpp
// 优先队列的比较函数
struct cmp {
    bool operator () (int a,int b) {return dep[a]>dep[b];}
};
priority_queue <int,vector<int>,cmp> q;

// 深度优先搜索计算深度和初始化优先队列
void dfs (int x,int fa) {
    dep[x]=dep[fa]+1;
    for (int i=hd[x];i;i=nx[i]) {
        if (ver[i]!=fa) {
            dfs(ver[i],x);
        }
    }
    if (c[x]==0) {q.push(x);}
    return;
}

// 主函数
int main () {
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf("%d%d",&f[i],&c[i]);
        if (f[i]==0) {r=i;}
        if (f[i]) {add_edge(i,f[i]),add_edge(f[i],i);}
    }
    dfs(r,0);
    int cnt=0;
    while (!q.empty()) {
        int tmp=q.top();
        q.pop();
        cnt++;
        a[tmp]=cnt;
        while (tmp) {
            if (--c[tmp]==0) {q.push(tmp);}
            tmp=f[tmp];
        }
    }
    if (cnt==n) {
        printf("YES\n");
        for (int i=1;i<=n-1;i++) {
            printf("%d ",a[i]);
        }
        printf("%d\n",a[n]);
    } else {
        printf("NO\n");
    }
    return 0;
}
```
**核心实现思想**：通过深度优先搜索计算每个节点的深度，并将 $c_i = 0$ 的节点加入优先队列。每次从优先队列中取出队首节点，确定其权值，并更新其祖先节点的 $c_i$ 值。

#### KiDDOwithTopTree 的核心代码（平衡树部分）
```cpp
// 平衡树节点结构
struct fhq_treap{
    int lson,rson;
    int size;
    int key;
};
fhq_treap fhq[N];
int root[N],a[N];

// 新建节点
inline int newnode(int pos){
    fhq[pos].key=rand();
    fhq[pos].size=1;
    return pos;
}

// 上传节点信息
inline void pushup(int pos){
    int ls=fhq[pos].lson,rs=fhq[pos].rson;
    fhq[pos].size=fhq[ls].size+fhq[rs].size+1;
}

// 分裂操作
void fhq_split(int pos,int size,int &x,int &y){
    if(!pos) return void(x=y=0);
    int checker=fhq[fhq[pos].lson].size+1;
    if(checker<=size){
        x=pos;
        fhq_split(fhq[x].rson,size-checker,fhq[x].rson,y);
        pushup(x);
    }
    else{
        y=pos;
        fhq_split(fhq[y].lson,size,x,fhq[y].lson);
        pushup(y);
    }
}

// 合并操作
int fhq_merge(int x,int y){
    if(!x||!y) return x+y;
    if(fhq[x].key<fhq[y].key){
        fhq[x].rson=fhq_merge(fhq[x].rson,y);
        pushup(x);
        return x;
    }
    else{
        fhq[y].lson=fhq_merge(x,fhq[y].lson);
        pushup(y);
        return y;
    }
}

// 插入操作
void ins(int &rt,int pos,int size){
    int x,y;
    fhq_split(rt,size,x,y);
    rt=fhq_merge(fhq_merge(x,newnode(pos)),y);
}

// 启发式合并
void fhq_dfs(int x,int &y){
    if(!x) return ;
    int ls=fhq[x].lson,rs=fhq[x].rson;
    fhq[x].lson=fhq[x].rson=0;
    fhq_dfs(ls,y);
    ins(y,x,fhq[y].size);
    fhq_dfs(rs,y);
}
void merge(int &x,int &y){
    if(fhq[x].size>fhq[y].size)
        swap(x,y);
    fhq_dfs(x,y);
}

// 深度优先搜索计算答案
bool flag;
void dfs(int u){
    for(int i=e.head[u];~i;i=e.e[i].nxt){
        int v=e.e[i].to;
        dfs(v);
        merge(root[v],root[u]);
    }
    if(a[u]>fhq[root[u]].size) flag=true;
    else if(!flag) ins(root[u],u,a[u]);
}
```
**核心实现思想**：使用平衡树（fhq treap）来维护子树的信息，通过分裂、合并和插入操作来更新平衡树。在深度优先搜索过程中，将子树的平衡树合并，并插入当前节点。

#### liuyz11 的核心代码
```cpp
// 深度优先搜索
void dfs(int u){
    ve[u].clear();
    sz[u] = 1;
    rep(i, 0, SZ(edge[u]) - 1){
        int v = edge[u][i];
        dfs(v);
        sz[u] += sz[v];
        rep(j, 0, SZ(ve[v]) - 1) ve[u].pb(ve[v][j]);
    }
    if(c[u] >= sz[u]){
        puts("NO");
        exit(0);
    }
    sort(all(ve[u]));
    rep(i, 0, SZ(ve[u]) - 1) ve[u][i].fi = i + 1;
    ve[u].insert(ve[u].begin() + c[u], mp(c[u] + 1, u));
    rep(i, c[u] + 1, SZ(ve[u]) - 1) ve[u][i].fi++;
}
```
**核心实现思想**：通过深度优先搜索合并子树的信息，将子树中的节点按权值排序，然后将当前节点插入到合适的位置，更新后续节点的权值。

### 最优关键思路或技巧
- 利用深度优先搜索遍历树的节点，方便处理子树信息。
- 对于节点权值的构造，通过维护子树的相对大小关系，避免处理权值相等的复杂情况。
- 可以使用优先队列、堆、平衡树等数据结构来优化操作，提高时间复杂度。

### 拓展思路
同类型题或类似算法套路：
- 其他构造类的树相关问题，如构造满足特定条件的树的形态、节点权值等。
- 利用数据结构（如平衡树、堆）优化树的操作的问题。

### 推荐题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：树型动态规划问题，与本题的树结构处理有一定相似性。
- [P2014 选课](https://www.luogu.com.cn/problem/P2014)：树形依赖的背包问题，也涉及树的遍历和信息维护。
- [P1131 [ZJOI2007] 时态同步](https://www.luogu.com.cn/problem/P1131)：树的深度优先搜索应用，通过调整边的权值来满足特定条件。

### 个人心得摘录与总结
- KiDDOwithTopTree：作者在模拟赛上一开始没做出来，后来才发现是自己会的题，提醒我们要仔细审题，不要轻易放弃。
- liuyz11：作者表示一开始不会做，百度题解后才通过，说明参考他人思路可以帮助我们解决问题，但也要注意理解和消化。

---
处理用时：87.89秒