# 题目信息

# Jamie and Tree

## 题目描述

To your surprise, Jamie is the final boss! Ehehehe.

Jamie has given you a tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . Initially, the root of the tree is the vertex with number $ 1 $ . Also, each vertex has a value on it.

Jamie also gives you three types of queries on the tree:

 $ 1\ v $ — Change the tree's root to vertex with number $ v $ .

 $ 2\ u\ v\ x $ — For each vertex in the subtree of smallest size that contains $ u $ and $ v $ , add $ x $ to its value.

 $ 3\ v $ — Find sum of values of vertices in the subtree of vertex with number $ v $ .

A subtree of vertex $ v $ is a set of vertices such that $ v $ lies on shortest path from this vertex to root of the tree. Pay attention that subtree of a vertex can change after changing the tree's root.

Show your strength in programming to Jamie by performing the queries accurately!

## 说明/提示

The following picture shows how the tree varies after the queries in the first sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916E/9b296178af98e90dbbac00c785fb2ed88745e7bd.png)

## 样例 #1

### 输入

```
6 7
1 4 2 8 5 7
1 2
3 1
4 3
4 5
3 6
3 1
2 4 6 3
3 4
1 6
2 2 4 -5
1 4
3 3
```

### 输出

```
27
19
5
```

## 样例 #2

### 输入

```
4 6
4 3 5 6
1 2
2 3
3 4
3 1
1 3
2 2 4 3
1 1
2 2 4 -3
3 1
```

### 输出

```
18
21
```

# AI分析结果

# 💡 Kay的C++算法解析：Jamie and Tree 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：树链剖分（重链剖分）+ 线段树 + 换根分类讨论


### 🗣️ 初步分析
你可以把这道题想象成**“给树换个‘视角’，然后快速修改/查询子树”**的游戏：树原本有个根（比如1号节点），但我们可以随时把根换成另一个节点（就像从不同角度看树）。之后需要做三件事：  
1. 换根（改变视角）；  
2. 找到包含u和v的最小子树（其实就是换根后的LCA的子树），给这个子树的所有节点加值；  
3. 查询某个节点的子树总和（从当前视角看的子树）。


#### 核心算法：树链剖分（Tree Chain Partitioning）+ 线段树
树链剖分的作用是**把树“拆”成一条条连续的链**，这样就能用线段树（处理区间问题的神器）来快速修改/查询子树或路径。而换根操作不需要真的改变树的结构——我们只需要**分类讨论当前根的位置**，把“换根后的子树操作”转化为“原树（以1为根）的区间操作”。


#### 关键思路与难点
- **难点1：换根后的子树怎么找？**  
  假设原树以1为根，当前根是R，要处理节点X的子树：  
  1. 如果R=X：子树是整棵树（所有节点）；  
  2. 如果R不在X的子树里：X的子树和原树一样（直接用原树的DFS序区间）；  
  3. 如果R在X的子树里：X的子树是**整棵树减去R所在的“分支”**（用容斥原理，先操作整棵树，再减去分支的影响）。  

- **难点2：换根后的LCA怎么求？**  
  换根后的LCA其实是三个LCA中最深的那个：原树中u和v的LCA、u和R的LCA、v和R的LCA。因为换根后，LCA的位置会偏向根的一侧。


#### 可视化设计思路
我们用**8位像素风**模拟树的结构（比如FC游戏里的“冒险岛”风格）：  
- 节点用彩色像素块表示（根节点是红色，当前处理的子树是蓝色，LCA是黄色）；  
- 换根时，红色块会“跳”到新的根节点；  
- 子树修改时，蓝色块会闪烁并扩展（比如根在子树内时，蓝色会覆盖整棵树，然后“抠掉”R所在的分支）；  
- 用“叮”的音效提示关键操作（比如找到LCA、修改子树），“胜利”音效表示操作完成。


## 2. 精选优质题解参考

### 题解一（作者：Siyuan，赞：29）
**点评**：这道题解的**思路清晰度**和**代码严谨性**都非常突出！作者没有真的换根，而是通过**分类讨论根的位置**，把所有操作转化为原树的区间问题。比如：  
- 用DFS序把树转化为线性数组，用线段树处理区间加/求和；  
- 用倍增法快速求原树的LCA；  
- 对于换根后的子树操作，分三种情况处理（根是子树根、根不在子树内、根在子树内），逻辑非常清晰。  
代码中的变量命名也很规范（比如`dfn`表示DFS序，`sz`表示子树大小），边界条件处理得很严谨（比如判断根是否在子树内的逻辑），非常适合初学者参考。


### 题解二（作者：绝顶我为峰，赞：23）
**点评**：这道题解的**LCA分析**特别详细！作者用多幅图展示了换根后LCA的6种情况，把抽象的LCA问题变得直观。比如：  
- 当u和v在原树中的LCA是x时，换根后的LCA可能是y（如果根在y的子树里）；  
- 当u和v不在同一子树时，换根后的LCA可能是根本身（如果根在u和v的路径上）。  
代码中`LCA`函数的分类讨论逻辑非常全面，覆盖了所有可能的情况，对于理解换根后的LCA很有帮助。


### 题解三（作者：zhiyangfan，赞：16）
**点评**：这道题解的**LCT（Link-Cut Tree）实现**很有特色！虽然树链剖分已经能解决问题，但作者用LCT（动态树数据结构）实现了子树操作，展示了另一种思路。比如：  
- 用LCT的`access`操作求LCA；  
- 维护虚子树的信息（`szl`表示虚子树大小，`suml`表示虚子树和），处理子树加/求和。  
虽然LCT的代码复杂度更高，但对于想深入学习动态树的同学来说，这是很好的参考。


## 3. 核心难点辨析与解题策略

### 1. 难点1：换根后的子树如何转化为原树的区间？
**分析**：换根后的子树其实是“从当前根看过去的子树”，但我们可以用**原树的DFS序**来判断：  
- 原树中，每个节点X的子树对应DFS序的区间是`[dfn[X], dfn[X]+sz[X]-1]`（`dfn`是DFS序，`sz`是子树大小）；  
- 如果当前根R在X的子树里（即`dfn[R]`在`[dfn[X], dfn[X]+sz[X]-1]`内），那么X的子树是**整棵树减去R所在的“分支”**（这个分支是X的儿子中包含R的那个节点的子树）。  

**学习笔记**：换根不改变树的结构，只改变“子树的定义”——用原树的DFS序和子树大小就能快速转化。


### 2. 难点2：换根后的LCA如何计算？
**分析**：换根后的LCA是三个LCA中最深的那个：  
- `lca(u, v)`：原树中u和v的LCA；  
- `lca(u, R)`：原树中u和当前根R的LCA；  
- `lca(v, R)`：原树中v和当前根R的LCA。  
因为换根后，LCA的位置会偏向根的一侧，最深的那个节点就是新的LCA。

**学习笔记**：换根后的LCA可以通过原树的LCA推导出来，不需要重新预处理。


### 3. 难点3：如何用树剖+线段树处理子树操作？
**分析**：树链剖分的核心是把树拆成链，让每个子树对应一个**连续的区间**（DFS序的区间）。这样：  
- 子树加操作就是线段树的区间加；  
- 子树求和就是线段树的区间查询。  
即使换根了，只要把换根后的子树转化为原树的区间，就能用同样的方法处理。

**学习笔记**：树剖的本质是“将树线性化”，让复杂的树操作变成简单的区间操作。


### ✨ 解题技巧总结
1. **分类讨论是关键**：换根后的所有操作都可以通过“原树的信息+分类讨论”解决，不需要真的改变树结构；  
2. **DFS序是桥梁**：把树的子树转化为线性区间，用线段树处理；  
3. **LCA的推导**：换根后的LCA可以通过原树的LCA计算，不需要重新预处理；  
4. **边界条件要注意**：比如根等于子树根的情况（操作整棵树），或者根在子树内的情况（容斥处理）。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
**说明**：综合了Siyuan和绝顶我为峰的题解思路，实现了树链剖分+线段树+换根分类讨论。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int LOG = 17;

vector<int> G[N];
int n, q, root = 1;
int a[N], dfn[N], rk[N], sz[N], dep[N], fa[N][LOG+1], son[N], top[N];
ll seg[N<<2], tag[N<<2];
int cnt;

// 线段树：pushup
void pushup(int rt) {
    seg[rt] = seg[rt<<1] + seg[rt<<1|1];
}

// 线段树：build
void build(int rt, int l, int r) {
    if (l == r) {
        seg[rt] = a[rk[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
    pushup(rt);
}

// 线段树：pushdown
void pushdown(int rt, int l, int r) {
    if (tag[rt]) {
        int mid = (l + r) >> 1;
        seg[rt<<1] += tag[rt] * (mid - l + 1);
        seg[rt<<1|1] += tag[rt] * (r - mid);
        tag[rt<<1] += tag[rt];
        tag[rt<<1|1] += tag[rt];
        tag[rt] = 0;
    }
}

// 线段树：区间加
void update(int rt, int l, int r, int L, int R, ll k) {
    if (L <= l && r <= R) {
        seg[rt] += k * (r - l + 1);
        tag[rt] += k;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(rt<<1, l, mid, L, R, k);
    if (R > mid) update(rt<<1|1, mid+1, r, L, R, k);
    pushup(rt);
}

// 线段树：区间查询
ll query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return seg[rt];
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    ll res = 0;
    if (L <= mid) res += query(rt<<1, l, mid, L, R);
    if (R > mid) res += query(rt<<1|1, mid+1, r, L, R);
    return res;
}

// 树剖：dfs1（处理父节点、深度、子树大小、重儿子）
void dfs1(int u, int f) {
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    sz[u] = 1;
    son[u] = 0;
    for (int v : G[u]) {
        if (v == f) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

// 树剖：dfs2（处理链顶、DFS序）
void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++cnt;
    rk[cnt] = u;
    if (son[u]) dfs2(son[u], tp); // 重儿子继承链顶
    for (int v : G[u]) {
        if (v != fa[u][0] && v != son[u]) {
            dfs2(v, v); // 轻儿子开新链
        }
    }
}

// 倍增法求LCA
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    // 把u跳到和v同一深度
    for (int i = LOG; i >= 0; --i) {
        if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    }
    if (u == v) return u;
    // 一起跳
    for (int i = LOG; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

// 换根后的LCA（三个LCA中最深的）
int get_new_lca(int u, int v) {
    int a = lca(u, v);
    int b = lca(u, root);
    int c = lca(v, root);
    if (dep[b] > dep[a]) a = b;
    if (dep[c] > dep[a]) a = c;
    return a;
}

// 找X的儿子中包含R的节点（用于容斥）
int find_son(int X, int R) {
    while (top[R] != top[X]) {
        if (fa[top[R]][0] == X) return top[R];
        R = fa[top[R]][0];
    }
    return son[X]; // 如果在同一条链里，就是重儿子
}

// 换根后的子树修改
void modify_subtree(int X, ll k) {
    if (X == root) {
        update(1, 1, n, 1, n, k); // 整棵树
        return;
    }
    if (dfn[root] < dfn[X] || dfn[root] > dfn[X] + sz[X] - 1) {
        // R不在X的子树里，直接修改原树的子树
        update(1, 1, n, dfn[X], dfn[X] + sz[X] - 1, k);
        return;
    }
    // R在X的子树里，容斥：整棵树 - R所在的分支
    int S = find_son(X, root);
    update(1, 1, n, 1, n, k);
    update(1, 1, n, dfn[S], dfn[S] + sz[S] - 1, -k);
}

// 换根后的子树查询
ll query_subtree(int X) {
    if (X == root) return query(1, 1, n, 1, n);
    if (dfn[root] < dfn[X] || dfn[root] > dfn[X] + sz[X] - 1) {
        return query(1, 1, n, dfn[X], dfn[X] + sz[X] - 1);
    }
    int S = find_son(X, root);
    return query(1, 1, n, 1, n) - query(1, 1, n, dfn[S], dfn[S] + sz[S] - 1);
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    // 预处理倍增LCA
    dfs1(1, 0);
    for (int j = 1; j <= LOG; ++j) {
        for (int i = 1; i <= n; ++i) {
            fa[i][j] = fa[fa[i][j-1]][j-1];
        }
    }
    // 树剖
    dfs2(1, 1);
    build(1, 1, n);
    
    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &root);
        } else if (op == 2) {
            int u, v, x;
            scanf("%d%d%d", &u, &v, &x);
            int l = get_new_lca(u, v);
            modify_subtree(l, x);
        } else if (op == 3) {
            int x;
            scanf("%d", &x);
            printf("%lld\n", query_subtree(x));
        }
    }
    return 0;
}
```

**代码解读概要**：  
1. **树剖部分**：`dfs1`处理树的基本信息（父节点、深度、子树大小、重儿子），`dfs2`处理链顶和DFS序，把树拆成链；  
2. **线段树部分**：`build`初始化线段树，`update`区间加，`query`区间查询；  
3. **LCA部分**：用倍增法求原树的LCA，`get_new_lca`求换根后的LCA；  
4. **换根处理**：`modify_subtree`和`query_subtree`根据根的位置分类处理，转化为线段树的区间操作。


### 题解一核心代码片段赏析（作者：Siyuan）
**亮点**：用DFS序和子树大小快速判断根是否在子树内，容斥处理子树操作。

**核心代码片段**：
```cpp
void treeModify(int u, int k) {
    int l = dfn[u], r = dfn[u] + sz[u] - 1;
    if (u == root) modify(1, n, 1, 1, n, k);
    else if (dfn[root] < l || dfn[root] > r) modify(l, r, 1, 1, n, k);
    else {
        int son = jump(root, dep[root] - dep[u] - 1);
        modify(1, n, 1, 1, n, k), modify(dfn[son], dfn[son]+sz[son]-1, 1, 1, n, -k);
    }
}
```

**代码解读**：  
- `dfn[u]`和`sz[u]`是原树中u的DFS序和子树大小，对应区间`[l, r]`；  
- 如果`u == root`：修改整棵树（区间1~n）；  
- 如果`root`不在u的子树里（`dfn[root]`不在`[l, r]`）：直接修改原树的子树；  
- 否则：找到u的儿子中包含root的节点`son`（用`jump`函数跳`dep[root]-dep[u]-1`步），然后修改整棵树，再减去`son`的子树的影响（容斥）。

**学习笔记**：容斥是处理“根在子树内”的关键，把复杂的子树转化为两个简单的区间操作。


## 5. 算法可视化：像素动画演示

### 🎮 动画主题：像素树的“视角变换”游戏
我们用**8位像素风**（类似FC游戏《冒险岛》）模拟树的结构，让你直观看到换根、子树修改的过程！


### 🎨 设计思路
- **风格**：8位像素色板（比如红、蓝、黄、绿），节点用3x3的像素块表示，边用1x1的像素线连接；  
- **交互**：支持“单步执行”“自动播放”“重置”，速度滑块调节动画速度；  
- **音效**：换根时播放“叮”的音效，子树修改时播放“滋滋”的音效，查询完成时播放“滴”的音效。


### 📽️ 动画步骤演示
1. **初始化**：树以1号节点（红色）为根，其他节点是绿色，显示DFS序区间（比如节点2的区间是[2,3]）；  
2. **换根操作**（op=1 6）：红色块从1号节点“跳”到6号节点，树的“视角”改变；  
3. **子树修改**（op=2 2 4 -5）：找到换根后的LCA（比如节点4），蓝色块覆盖节点4的子树（此时根在6号，节点4的子树是整棵树减去节点3的子树），蓝色块闪烁表示加-5；  
4. **子树查询**（op=3 3）：黄色块覆盖节点3的子树，显示查询结果（比如5）。


### 🧠 为什么这样设计？
- 用颜色区分不同状态（根、子树、LCA），让你一眼看懂当前操作的对象；  
- 用“跳跃”动画展示换根，直观理解“视角变换”；  
- 用“闪烁”和“覆盖”展示子树修改，清楚看到容斥的过程。


## 6. 拓展练习与相似问题思考

### 通用思路迁移
树链剖分+换根分类讨论的思路可以解决**所有需要“动态换根+子树/路径操作”的问题**，比如：  
1. 动态换根后，查询某条路径的和；  
2. 动态换根后，修改某条路径的节点值；  
3. 动态换根后，求子树的最大值/最小值。


### 洛谷练习推荐
1. **P3979 遥远的国度**：和本题几乎一样的换根+子树操作，巩固分类讨论的思路；  
2. **P2014 选课**：树型DP结合树链剖分，处理带依赖的选课问题；  
3. **P2345 奶牛集会**：树链剖分处理路径查询，练习路径操作的转化；  
4. **P3384 树链剖分**：树剖的模板题，熟悉树剖的基本操作。


## 7. 学习心得与经验分享
### 参考经验（来自Siyuan的题解）
> “我在解决这个问题时，最初想真的换根，但发现每次换根都要重新DFS，时间复杂度太高。后来想到，换根后的子树可以通过原树的DFS序和子树大小来判断，这样就不需要真的改变树结构了。”

**点评**：这个经验非常重要！很多同学会陷入“真的换根”的误区，但实际上，换根只是“视角的变化”，我们可以用原树的信息来模拟这种变化，避免重复预处理。


## 💪 总结
这道题的核心是**“用原树的信息处理换根后的操作”**：树链剖分将树线性化，线段树处理区间操作，分类讨论解决换根的影响。通过这道题，你可以掌握树剖的基本用法，以及如何处理动态换根的问题。

记住：**换根不改变树的结构，只改变你看树的角度**——用原树的信息，就能应对所有变化！

下次遇到树的换根问题，不妨先想想：“我能不能用原树的DFS序和子树大小来解决？” 你会发现，很多问题都会变得简单起来！ 🚀

---
处理用时：149.22秒