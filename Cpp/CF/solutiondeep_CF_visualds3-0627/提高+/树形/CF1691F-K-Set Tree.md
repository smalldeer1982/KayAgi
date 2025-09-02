# 题目信息

# K-Set Tree

## 题目描述

You are given a tree $ G $ with $ n $ vertices and an integer $ k $ . The vertices of the tree are numbered from $ 1 $ to $ n $ .

For a vertex $ r $ and a subset $ S $ of vertices of $ G $ , such that $ |S| = k $ , we define $ f(r, S) $ as the size of the smallest rooted subtree containing all vertices in $ S $ when the tree is rooted at $ r $ . A set of vertices $ T $ is called a rooted subtree, if all the vertices in $ T $ are connected, and for each vertex in $ T $ , all its descendants belong to $ T $ .

You need to calculate the sum of $ f(r, S) $ over all possible distinct combinations of vertices $ r $ and subsets $ S $ , where $ |S| = k $ . Formally, compute the following: $ $$$\sum_{r \in V} \sum_{S \subseteq V, |S| = k} f(r, S), $ $  where  $ V $  is the set of vertices in  $ G $ .</p><p>Output the answer modulo  $ 10^9 + 7$$$.

## 说明/提示

The tree in the second example is given below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1691F/e82a7a29dc0a63112d5ed3b2013f71742d57079e.png)We have $ 21 $ subsets of size $ 2 $ in the given tree. Hence, $ $$$S \in \left\{\{1, 2\}, \{1, 3\}, \{1, 4\}, \{1, 5\}, \{1, 6\}, \{1, 7\}, \{2, 3\}, \{2, 4\}, \{2, 5\}, \{2, 6\}, \{2, 7\}, \{3, 4\}, \{3, 5\}, \{3, 6\}, \{3, 7\}, \{4, 5\}, \{4, 6\}, \{4, 7\}, \{5, 6\}, \{5, 7\}, \{6, 7\} \right\}. $ $  And since we have  $ 7 $  vertices,  $ 1 \\le r \\le 7 $ . We need to find the sum of  $ f(r, S) $  over all possible pairs of  $ r $  and  $ S $ . </p><p>Below we have listed the value of  $ f(r, S) $  for some combinations of  $ r $  and  $ S $ .</p><ul> <li>  $ r = 1 $ ,  $ S = \\{3, 7\\} $ . The value of  $ f(r, S) $  is  $ 5 $  and the corresponding subtree is  $ \\{2, 3, 4, 6, 7\\} $ . </li><li>  $ r = 1 $ ,  $ S = \\{5, 4\\} $ . The value of  $ f(r, S) $  is  $ 7 $  and the corresponding subtree is  $ \\{1, 2, 3, 4, 5, 6, 7\\} $ . </li><li>  $ r = 1 $ ,  $ S = \\{4, 6\\} $ . The value of  $ f(r, S) $  is  $ 3 $  and the corresponding subtree is  $ \\{4, 6, 7\\}$$$.

## 样例 #1

### 输入

```
3 2
1 2
1 3```

### 输出

```
25```

## 样例 #2

### 输入

```
7 2
1 2
2 3
2 4
1 5
4 6
4 7```

### 输出

```
849```

# AI分析结果



## 算法分类
**换根DP + 组合数学**

## 题解思路与算法要点
### 核心思路
1. **贡献拆分**：对于每个节点u，计算其作为所有子集S的最近公共祖先（LCA）时的贡献。贡献公式为：
   $$贡献 = sz_u \times \left( \binom{sz_u}{k} - \sum_{v \in son(u)} \binom{sz_v}{k} \right)$$
   其中`sz_u`是子树大小，组合数部分表示在u子树中选k个点但不全在任一子节点子树的情况。

2. **换根动态规划**：通过两次DFS实现：
   - 第一次DFS预处理以1为根时的子树大小`sz`和组合数贡献。
   - 第二次DFS进行换根，动态维护父节点与子节点关系，计算所有节点作为根时的贡献。

### 关键变量
- `sz[u]`：以当前根为基准时u的子树大小。
- `g[u]`：组合数差值项，$\binom{sz_u}{k} - \sum \binom{sz_v}{k}$。
- `f[u]`：子树答案和，包含自身贡献和子节点贡献。

### 解决难点
- **动态维护子树大小**：换根时父节点与子节点的子树大小会交换，需要O(1)时间重新计算。
- **组合数预处理**：通过阶乘和逆元预处理组合数，支持O(1)查询。
- **负值处理**：在模运算中正确处理减法导致的负值。

## 题解评分（≥4星）
1. **dead_X（5星）**
   - **亮点**：换根逻辑清晰，通过预处理子树和父节点分类简化计算。
   - **代码优化**：使用统一公式处理三类父节点情况，减少条件判断。

2. **lingfunny（5星）**
   - **亮点**：定义明确的f和g数组，公式推导直观，换根逻辑简洁。
   - **可读性**：代码模块化程度高，组合数计算与DFS分离。

3. **candy0014（4星）**
   - **创新性**：利用连通块贡献替代DP，时间复杂度更优。
   - **数学推导**：通过巧妙的平方和转换简化问题，适合数学思维强的选手。

## 最优思路提炼
1. **换根DP框架**：
   ```python
   def dfs(u, fa):
       # 预处理sz和组合数贡献
       for v in son(u):
           dfs(v, u)
           update sz[u], g[u], f[u]

   def reroot(u, fa):
       # 动态调整父节点贡献
       for v in son(u):
           adjust sz[u], sz[v]
           update ans with new contribution
           reroot(v, u)
           restore sz[u], sz[v]
   ```

2. **组合数优化**：
   ```cpp
   // 预处理阶乘与逆元
   fac[0] = 1;
   for(int i=1; i<=n; ++i) fac[i] = fac[i-1] * i % mod;
   ifac[n] = qpow(fac[n], mod-2);
   for(int i=n-1; i>=0; --i) ifac[i] = ifac[i+1] * (i+1) % mod;

   // 计算组合数
   int C(int n, int k) {
       return (n<k) ? 0 : fac[n]*ifac[k]%mod * ifac[n-k]%mod;
   }
   ```

## 同类问题推荐
1. **CF1092F Tree with Maximum Cost**  
   - 换根DP计算节点贡献的动态调整。
2. **CF1324F Maximum White Subtree**  
   - 类似换根思想处理子树信息。
3. **Luogu P1352 没有上司的舞会**  
   - 树形DP基础训练，理解父子状态转移。

## 核心代码片段
```cpp
// 预处理DFS
void dfs(int x, int fa) {
    sz[x] = 1;
    for(int y : e[x]) if(y != fa) {
        dfs(y, x);
        sz[x] += sz[y];
        g[x] = (g[x] + C(sz[y], k)) % mod;
    }
    f[x] = (C(sz[x], k) - g[x] + mod) * sz[x] % mod;
    for(int y : e[x]) if(y != fa) 
        f[x] = (f[x] + f[y]) % mod;
}

// 换根DFS
void reroot(int x, int fa) {
    ans = (ans + f[x]) % mod;
    for(int y : e[x]) if(y != fa) {
        // 保存原值
        int old_sz_x = sz[x], old_sz_y = sz[y];
        int old_g_x = g[x], old_g_y = g[y];
        int old_f_x = f[x], old_f_y = f[y];

        // 调整x为子节点
        f[x] = (f[x] - (C(sz[x],k)-g[x]+mod)*sz[x] % mod + mod) % mod;
        f[x] = (f[x] - f[y] + mod) % mod;
        sz[x] -= sz[y];
        g[x] = (g[x] - C(sz[y],k) + mod) % mod;
        f[x] = (f[x] + (C(sz[x],k)-g[x]+mod)*sz[x] % mod) % mod;

        // 调整y为新根
        sz[y] = n;
        g[y] = (g[y] + C(sz[x],k)) % mod;
        f[y] = (f[y] + (C(sz[y],k)-g[y]+mod)*sz[y] % mod) % mod;

        reroot(y, x);

        // 恢复原值
        sz[x] = old_sz_x; sz[y] = old_sz_y;
        g[x] = old_g_x; g[y] = old_g_y;
        f[x] = old_f_x; f[y] = old_f_y;
    }
}
```

## 可视化设计
### 动画方案
1. **树结构展示**：用Canvas绘制树形结构，节点按层次排列。
2. **换根高亮**：当前根节点标记为红色，换根时显示父子关系变化动画。
3. **贡献计算**：当DFS访问节点时，显示其sz值和组合数贡献的实时计算。
4. **数据面板**：右侧显示当前节点的g值、f值和子树大小。

### 复古风格
- **8位像素风**：节点用16x16像素块表示，边用单色线段。
- **音效设计**：
  - 节点展开：短促“哔”声（Web Audio API）。
  - 贡献更新：电子“滴答”声。
  - 换根操作：滑动音效。
- **自动演示**：按深度优先顺序自动换根，用方向键控制单步执行。

### 交互功能
- **速度调节**：滑动条控制动画速度（0.5x~5x）。
- **单步调试**：空格键暂停/继续，→键单步执行。
- **贡献追踪**：点击节点显示其当前贡献计算式。

---
处理用时：115.87秒