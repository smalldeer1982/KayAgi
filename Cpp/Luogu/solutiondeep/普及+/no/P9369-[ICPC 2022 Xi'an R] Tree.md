# 题目信息

# [ICPC 2022 Xi'an R] Tree

## 题目描述

给定大小为 $n$ 的有根树 $T$，根节点为 $1$。定义 $\mathrm{subtree}(u)$ 表示结点 $u$ 的子树。

称集合 $S$ 是好的，当且仅当 $S$ 至少满足下列条件之一：

- 对于 $u, v\in S$ 且 $u\neq v$，$u\in \mathrm{subtree}(v)$ 或 $v\in \mathrm{subtree}(u)$。
- 对于 $u, v\in S$ 且 $u\neq v$，$u\notin \mathrm{subtree}(v)$ 且 $v\notin \mathrm{subtree}(u)$。

将 $T$ 划分为若干好的集合，求集合数量的最小值。

共有 $Q$ 组数据。

$1\leq Q\leq 10 ^ 5$，$1\leq n, \sum n\leq 10 ^ 6$，每个点的父亲编号 $1\leq p_i < i$。

## 样例 #1

### 输入

```
2
7
1 1 2 2 2 3
5
1 2 3 4
```

### 输出

```
3
1
```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
本题的核心在于如何将树划分为满足条件的集合，且集合数量最小。各题解主要采用了贪心策略，通过长链剖分或模拟剥叶子的方式，选择最优的集合划分方式。难点在于如何高效地处理树的结构，并找到最小的集合数量。

### 所选题解
1. **作者：Dreamer_Boy (5星)**
   - **关键亮点**：通过长链剖分，将问题转化为选择最长的链作为集合，剩余部分通过贪心策略处理。思路清晰，代码简洁高效。
   - **核心实现思想**：通过两次DFS进行长链剖分，排序后枚举选择前i条长链作为第一类集合，剩余部分作为第二类集合，取最小值。
   ```cpp
   void dfs1(int x) {
       for (int y : g[x]) {
           dfs1(y);
           if (len[y] > len[son[x]]) son[x] = y;
       }
       len[x] = len[son[x]] + 1;
   }
   void dfs2(int x, int l = 0) {
       if (!son[x]) lp.push_back(l);
       else {
           dfs2(son[x], l + 1);
           for (int y : g[x]) if (y != son[x]) dfs2(y, 1);
       }
   }
   ```

2. **作者：Missa (4星)**
   - **关键亮点**：通过分析A型和B型集合的性质，提出最优解的形式，并通过DFS增量构造。思路严密，代码实现清晰。
   - **核心实现思想**：计算每个点到其子树中叶结点的最大距离，枚举B型集合的数量，取最小值。
   ```cpp
   void solve() {
       int n; scanf("%d", &n);
       std::vector<int> fa(n + 1), mx(n + 1), cnt(n + 1);
       for (int i = 2; i <= n; i++) 
           scanf("%d", &fa[i]);
       for (int i = n; i >= 1; i--) {
           mx[fa[i]] = std::max(mx[fa[i]], mx[i] + 1);
           ++cnt[mx[i]];
       }
       int ans = n;
       for (int i = 0; i <= n; i++)
           ans = std::min(ans, cnt[i] + i);
       printf("%d\n", ans);
   }
   ```

3. **作者：蒟蒻君HJT (4星)**
   - **关键亮点**：通过模拟剥叶子的过程，逐步减少树的深度，计算最小集合数量。思路新颖，代码简洁。
   - **核心实现思想**：模拟剥叶子的过程，每轮剥去所有叶子，计算剩余叶子数量和轮数，取最小值。
   ```cpp
   void solve(){
       scanf("%d", &n);
       for(int i = 1; i <= n; ++i) d[i] = 0;
       for(int i = 2; i <= n; ++i){
           int x; scanf("%d", &x);
           ++d[x]; fa[i] = x;
       }
       leaf.clear(), tmp.clear();
       for(int i = 1; i <= n; ++i) if(!d[i]) leaf.push_back(i);
       int num = 0, ans = 1e9;
       while(leaf.size()){
           ans = std::min(ans, num + (int)leaf.size());
           num += 1;
           for(auto v : leaf) {
               --d[fa[v]];
               if(!d[fa[v]]) tmp.push_back(fa[v]);
           }
           leaf.clear();
           std::swap(leaf, tmp);
       }
       printf("%d\n", ans);
   }
   ```

### 最优关键思路或技巧
- **长链剖分**：通过长链剖分将树分解为若干长链，便于后续贪心选择。
- **贪心策略**：选择最长的链作为集合，剩余部分通过贪心策略处理，确保集合数量最小。
- **模拟剥叶子**：通过模拟剥叶子的过程，逐步减少树的深度，计算最小集合数量。

### 可拓展之处
- **类似算法套路**：在处理树结构问题时，长链剖分和贪心策略是常用的优化手段，适用于多种树相关题目。
- **同类型题**：可以尝试解决其他树划分问题，如最小覆盖集、最大独立集等。

### 推荐题目
1. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)
2. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
3. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)

---
处理用时：27.04秒