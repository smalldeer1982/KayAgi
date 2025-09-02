# 题目信息

# Coloring a Tree

## 题目描述

You are given a rooted tree with $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , the root is the vertex number $ 1 $ .

Each vertex has a color, let's denote the color of vertex $ v $ by $ c_{v} $ . Initially $ c_{v}=0 $ .

You have to color the tree into the given colors using the smallest possible number of steps. On each step you can choose a vertex $ v $ and a color $ x $ , and then color all vectices in the subtree of $ v $ (including $ v $ itself) in color $ x $ . In other words, for every vertex $ u $ , such that the path from root to $ u $ passes through $ v $ , set $ c_{u}=x $ .

It is guaranteed that you have to color each vertex in a color different from $ 0 $ .

You can learn what a rooted tree is using the link: <a>https://en.wikipedia.org/wiki/Tree\_(graph\_theory)</a>.

## 说明/提示

The tree from the first sample is shown on the picture (numbers are vetices' indices):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/9fd1d55fa8fc46341a8b892f02c91e5845a9cee1.png)

On first step we color all vertices in the subtree of vertex $ 1 $ into color $ 2 $ (numbers are colors):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/e11b694106163670fb12fdde15a9f65a4e1cb530.png)

On seond step we color all vertices in the subtree of vertex $ 5 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/e36a2cbd1ae067ab6fd537cd6badf9d7433ee5c6.png)

On third step we color all vertices in the subtree of vertex $ 2 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/e700d0bc8664e90658b34cd2376df32d0611fede.png)

The tree from the second sample is shown on the picture (numbers are vetices' indices):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/67ba592a2c43f57a4f90fbf32ea9b4099ae3ce16.png)

On first step we color all vertices in the subtree of vertex $ 1 $ into color $ 3 $ (numbers are colors):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/a70897e485cd2f798f1fbdf16aad3be9100baa22.png)

On second step we color all vertices in the subtree of vertex $ 3 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/00b2012fb6c63cf50c8cbb62275892a14d90331b.png)

On third step we color all vertices in the subtree of vertex $ 6 $ into color $ 2 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/cbb680be6f7f4a3785c9124a3b69bfeceadc9ad8.png)

On fourth step we color all vertices in the subtree of vertex $ 4 $ into color $ 1 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/2dab5297c24ff5c2f70dfec33f37cb0e4b4866c7.png)

On fith step we color all vertices in the subtree of vertex $ 7 $ into color $ 3 $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902B/8a33180d0bd5c28d2385265618229c6952307c3c.png)

## 样例 #1

### 输入

```
6
1 2 2 1 5
2 1 1 1 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
1 1 2 3 1 4
3 3 1 1 1 2 3
```

### 输出

```
5
```

# AI分析结果



# Coloring a Tree

## 题目描述

给定一棵有 $n$ 个顶点的有根树，根节点为 1 号顶点。所有顶点初始颜色均为 0。每次操作可以选择一个顶点 $v$ 和一个颜色 $x$，将 $v$ 的整个子树（包含 $v$）染成颜色 $x$。要求用最少的操作次数将树染成目标颜色状态（保证最终颜色不为 0）。

## 算法分类
贪心（基于DFS的贪心策略）

---

## 题解分析与结论

所有题解均采用**自顶向下DFS遍历树**的贪心策略，核心思路为：在遍历过程中维护父节点的颜色，若当前节点颜色与父节点颜色不同，则必须执行染色操作。该方法保证在高层级统一染色，避免重复操作。

---

## 精选题解

### 1. pikabi（★★★★★）
**关键亮点**：
- 使用链式前向星高效存储树结构
- 直接通过颜色比较触发计数，逻辑简洁
- 空间复杂度优化到位，无冗余判断

**核心代码解析**：
```cpp
void dfs(int now, int cl){    // now:当前节点, cl:父节点的颜色
    if(cl != c[now]){         // 颜色不同则触发染色
        ans++;
        cl = c[now];          // 更新传递颜色
    }
    for(int i = head[now]; i; i = e[i].nxt)
        dfs(e[i].to, cl);     // 递归处理子节点
}
```
**个人心得**："颜色不同就答案加，不需要实际染色操作，只需传递颜色状态"

---

### 2. hank0402（★★★★☆）
**关键亮点**：
- 使用vector存储树结构，便于理解
- 显式处理根节点颜色初始化问题
- 参数命名清晰，可读性强

**核心代码片段**：
```cpp
void dfs(int x, int cc, int from) {
    if(c[x] != cc) ans++;      // 触发染色
    for(int v : g[x])          // 遍历邻接表
        if(v != from)
            dfs(v, c[x], x);   // 传递当前颜色
}
```
**实现要点**：通过from参数避免回退父节点，确保树遍历的正确性

---

### 3. 天南星魔芋（★★★☆☆）
**特色处理**：
- 使用并查集存储父节点关系
- 显式处理父子颜色比较逻辑
- 采用前向星存边方式

**代码亮点**：
```cpp
if(color[x] != color[bcj[x]]) ans++; // 比较父节点颜色
```

---

## 关键思路总结
1. **贪心染色顺序**：从根节点开始向下层处理，确保高层染色覆盖低层
2. **颜色状态传递**：在DFS过程中传递父节点颜色，避免重复计算
3. **虚拟染色机制**：通过比较颜色差异触发计数，无需实际修改数据结构

---

## 类似题目推荐
1. [P2585 三色二叉树](https://www.luogu.com.cn/problem/P2585) - 树形结构染色问题
2. [P1273 有线电视网](https://www.luogu.com.cn/problem/P1273) - 树形DP与资源分配
3. [P3177 树上染色](https://www.luogu.com.cn/problem/P3177) - 树形结构组合染色问题

---

## 调试心得摘录
- "注意初始颜色全为0的设定，WA了两次才看清题目条件" —— pikabi
- "染色操作实际是覆盖操作，子节点染色必须在父节点之后" —— 吴思诚
- "使用-1作为初始颜色避免与0冲突" —— wangyi_c

---
处理用时：57.22秒