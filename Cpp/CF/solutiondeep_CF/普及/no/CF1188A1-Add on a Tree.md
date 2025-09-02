# 题目信息

# Add on a Tree

## 题目描述

Note that this is the first problem of the two similar problems. You can hack this problem only if you solve both problems.

You are given a tree with $ n $ nodes. In the beginning, $ 0 $ is written on all edges. In one operation, you can choose any $ 2 $ distinct leaves $ u $ , $ v $ and any real number $ x $ and add $ x $ to values written on all edges on the simple path between $ u $ and $ v $ .

For example, on the picture below you can see the result of applying two operations to the graph: adding $ 2 $ on the path from $ 7 $ to $ 6 $ , and then adding $ -0.5 $ on the path from $ 4 $ to $ 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/4514fbf35a3201a7ca3b335f667bd3e11a688c5b.png)Is it true that for any configuration of real numbers written on edges, we can achieve it with a finite number of operations?

Leaf is a node of a tree of degree $ 1 $ . Simple path is a path that doesn't contain any node twice.

## 说明/提示

In the first example, we can add any real $ x $ to the value written on the only edge $ (1, 2) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/25d412324353a5cacb63d72803d1f9b15e742633.png)In the second example, one of configurations that we can't reach is $ 0 $ written on $ (1, 2) $ and $ 1 $ written on $ (2, 3) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/e16117f5a283e54a35e77dfddddf18a8df81966b.png)Below you can see graphs from examples $ 3 $ , $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/1d0c41f73ee7e0beb3f827a01577bfa07941d15e.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/91469666c4af6f377da3f6104280ec7d6081a3a0.png)

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3
1 2
2 3
```

### 输出

```
NO```

## 样例 #3

### 输入

```
5
1 2
1 3
1 4
2 5
```

### 输出

```
NO```

## 样例 #4

### 输入

```
6
1 2
1 3
1 4
2 5
2 6
```

### 输出

```
YES```

# AI分析结果

【题目内容】
# 在树上添加

## 题目描述

注意这是两个相似问题中的第一个问题。你只能在解决这两个问题后才能hack这个问题。

你被给定一棵有 $n$ 个节点的树。开始时，所有边上的值都为 $0$。在一次操作中，你可以选择任意两个不同的叶子节点 $u$ 和 $v$，以及任意实数 $x$，并将 $x$ 加到 $u$ 和 $v$ 之间的简单路径上的所有边的值上。

例如，在下图中，你可以看到对图应用两次操作的结果：在从 $7$ 到 $6$ 的路径上添加 $2$，然后在从 $4$ 到 $5$ 的路径上添加 $-0.5$。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/4514fbf35a3201a7ca3b335f667bd3e11a688c5b.png)是否对于任何写在边上的实数配置，我们都可以通过有限次操作实现它？

叶子是树的度数为 $1$ 的节点。简单路径是不包含任何节点两次的路径。

## 说明/提示

在第一个例子中，我们可以将任意实数 $x$ 加到唯一边 $ (1, 2) $ 的值上。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/25d412324353a5cacb63d72803d1f9b15e742633.png)在第二个例子中，我们无法达到的一个配置是 $0$ 写在 $ (1, 2) $ 上，$1$ 写在 $ (2, 3) $ 上。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/e16117f5a283e54a35e77dfddddf18a8df81966b.png)在下面你可以看到例子 $3$ 和 $4$ 的图：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/1d0c41f73ee7e0beb3f827a01577bfa07941d15e.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/91469666c4af6f377da3f6104280ec7d6081a3a0.png)

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3
1 2
2 3
```

### 输出

```
NO```

## 样例 #3

### 输入

```
5
1 2
1 3
1 4
2 5
```

### 输出

```
NO```

## 样例 #4

### 输入

```
6
1 2
1 3
1 4
2 5
2 6
```

### 输出

```
YES```

【算法分类】
构造

【题解分析与结论】
题目要求判断是否可以通过有限次操作将树上的边权从全0变为任意实数配置。关键在于树的节点度数：如果树中存在度数为2的节点，则无法实现任意配置，否则可以实现。

【题解1】
作者：Priori_Incantatem (赞：10)
星级：5
关键亮点：详细分析了不同度数节点的情况，特别是度数为3及以上的处理方式，逻辑清晰，代码简洁。
核心代码：
```cpp
bool check() {
    for(int i=1;i<=n;++i)
        if(d[i]==2) return 0;
    return 1;
}
```
核心思想：遍历所有节点，检查是否存在度数为2的节点，若有则输出`NO`，否则输出`YES`。

【题解2】
作者：OIerWu_829 (赞：5)
星级：4
关键亮点：使用DFS遍历树并统计节点度数，代码结构清晰，易于理解。
核心代码：
```cpp
void dfs(int u, int fa) {
    d[u] = G[u].size();
    for (int v : G[u])
        if (v != fa) dfs(v, u);
}
```
核心思想：通过DFS遍历树，统计每个节点的度数，然后检查是否存在度数为2的节点。

【题解3】
作者：Bai_R_X (赞：4)
星级：4
关键亮点：简洁明了地分析了不同度数节点的情况，代码实现简单直接。
核心代码：
```cpp
for(i=1;i<=n;i++) {
    if(head[i]==2) {
        cout<<"NO";
        return 0;
    }
}
```
核心思想：遍历所有节点，检查是否存在度数为2的节点，若有则输出`NO`，否则输出`YES`。

【最优关键思路】
关键在于判断树中是否存在度数为2的节点。若存在，则无法通过操作实现任意边权配置；否则，可以实现。

【可拓展之处】
类似问题可以扩展到其他图结构，如判断是否可以通过某种操作实现图的特定配置。

【推荐题目】
1. P3388 【模板】割点（割顶）
2. P3379 【模板】最近公共祖先（LCA）
3. P3367 【模板】并查集

---
处理用时：39.75秒