# 题目信息

# Selling a Menagerie

## 题目描述

You are the owner of a menagerie consisting of $ n $ animals numbered from $ 1 $ to $ n $ . However, maintaining the menagerie is quite expensive, so you have decided to sell it!

It is known that each animal is afraid of exactly one other animal. More precisely, animal $ i $ is afraid of animal $ a_i $ ( $ a_i \neq i $ ). Also, the cost of each animal is known, for animal $ i $ it is equal to $ c_i $ .

You will sell all your animals in some fixed order. Formally, you will need to choose some permutation $ ^\dagger $ $ p_1, p_2, \ldots, p_n $ , and sell animal $ p_1 $ first, then animal $ p_2 $ , and so on, selling animal $ p_n $ last.

When you sell animal $ i $ , there are two possible outcomes:

- If animal $ a_i $ was sold before animal $ i $ , you receive $ c_i $ money for selling animal $ i $ .
- If animal $ a_i $ was not sold before animal $ i $ , you receive $ 2 \cdot c_i $ money for selling animal $ i $ . (Surprisingly, animals that are currently afraid are more valuable).

Your task is to choose the order of selling the animals in order to maximize the total profit.

For example, if $ a = [3, 4, 4, 1, 3] $ , $ c = [3, 4, 5, 6, 7] $ , and the permutation you choose is $ [4, 2, 5, 1, 3] $ , then:

- The first animal to be sold is animal $ 4 $ . Animal $ a_4 = 1 $ was not sold before, so you receive $ 2 \cdot c_4 = 12 $ money for selling it.
- The second animal to be sold is animal $ 2 $ . Animal $ a_2 = 4 $ was sold before, so you receive $ c_2 = 4 $ money for selling it.
- The third animal to be sold is animal $ 5 $ . Animal $ a_5 = 3 $ was not sold before, so you receive $ 2 \cdot c_5 = 14 $ money for selling it.
- The fourth animal to be sold is animal $ 1 $ . Animal $ a_1 = 3 $ was not sold before, so you receive $ 2 \cdot c_1 = 6 $ money for selling it.
- The fifth animal to be sold is animal $ 3 $ . Animal $ a_3 = 4 $ was sold before, so you receive $ c_3 = 5 $ money for selling it.

Your total profit, with this choice of permutation, is $ 12 + 4 + 14 + 6 + 5 = 41 $ . Note that $ 41 $ is not the maximum possible profit in this example.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but $ 4 $ is present in the array).

## 样例 #1

### 输入

```
8
3
2 3 2
6 6 1
8
2 1 4 3 6 5 8 7
1 2 1 2 2 1 2 1
5
2 1 1 1 1
9 8 1 1 1
2
2 1
1000000000 999999999
7
2 3 2 6 4 4 3
1 2 3 4 5 6 7
5
3 4 4 1 3
3 4 5 6 7
3
2 1 1
1 2 2
4
2 1 4 1
1 1 1 1```

### 输出

```
1 2 3
2 4 5 1 6 3 7 8
3 4 5 1 2
1 2
7 5 1 3 2 6 4
5 3 2 4 1
3 2 1
3 4 1 2```

# AI分析结果

### 题目重写
#### 题目描述
你是一个动物园的拥有者，动物园里有 $n$ 只动物，编号从 $1$ 到 $n$。然而，维护动物园的费用非常高，因此你决定卖掉这些动物！

已知每只动物都害怕另一只动物。具体来说，动物 $i$ 害怕动物 $a_i$（$a_i \neq i$）。此外，每只动物的价值也是已知的，动物 $i$ 的价值为 $c_i$。

你将按照某种固定的顺序卖掉所有的动物。形式上，你需要选择一个排列 $p_1, p_2, \ldots, p_n$，并按照这个顺序依次卖掉动物 $p_1, p_2, \ldots, p_n$。

当你卖掉动物 $i$ 时，有两种可能的结果：
- 如果动物 $a_i$ 在动物 $i$ 之前被卖掉，你将获得 $c_i$ 的收益。
- 如果动物 $a_i$ 在动物 $i$ 之前没有被卖掉，你将获得 $2 \cdot c_i$ 的收益。（令人惊讶的是，当前害怕的动物更有价值。）

你的任务是选择一个卖动物的顺序，以最大化总收益。

#### 样例
##### 输入
```
8
3
2 3 2
6 6 1
8
2 1 4 3 6 5 8 7
1 2 1 2 2 1 2 1
5
2 1 1 1 1
9 8 1 1 1
2
2 1
1000000000 999999999
7
2 3 2 6 4 4 3
1 2 3 4 5 6 7
5
3 4 4 1 3
3 4 5 6 7
3
2 1 1
1 2 2
4
2 1 4 1
1 1 1 1
```

##### 输出
```
1 2 3
2 4 5 1 6 3 7 8
3 4 5 1 2
1 2
7 5 1 3 2 6 4
5 3 2 4 1
3 2 1
3 4 1 2
```

### 算法分类
贪心、图论

### 题解分析与结论
该题的核心在于如何通过贪心策略和图论中的拓扑排序来最大化收益。大多数题解都采用了类似的思路：首先处理没有入度的节点（即没有动物害怕的动物），然后处理环中的节点，通过贪心策略选择环中价值最小的节点作为最后卖出的节点。

### 评分较高的题解
#### 题解1：BINYU (赞：8)
**星级：5星**
**关键亮点：**
- 思路清晰，通过拓扑排序处理无环部分，贪心处理环部分。
- 代码简洁，时间复杂度为 $O(n)$，效率高。
**核心代码：**
```cpp
void solve() {
    cin >> n;
    memset(vis, 0, sizeof(vis));
    memset(sum, 0, sizeof(sum));
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) cin >> c[i], sum[a[i]] += c[i];
    rep(i, 1, n) pq.push((node){sum[i], i});
    while (!pq.empty()) {
        int u = pq.top().pos; pq.pop();
        if (vis[u]) continue;
        vis[u] = 1; cout << u << ' ';
        sum[a[u]] -= c[u];
        pq.push((node){sum[a[u]], a[u]});
    }
    cout << '\n';
}
```
**核心思想：**
- 使用优先队列处理每个节点的价值，优先卖出价值最小的节点，以最大化收益。

#### 题解2：Wf_yjqd (赞：3)
**星级：4星**
**关键亮点：**
- 通过拓扑排序处理无环部分，贪心处理环部分。
- 代码简短，时间复杂度为 $O(n \log n)$。
**核心代码：**
```cpp
void topsort() {
    for (int i = 1; i <= n; i++)
        if (!du[i]) q.push(i);
    while (!q.empty()) {
        t = q.front(); q.pop();
        ans[++cnt] = t; vis[t] = 1;
        du[a[t]]--;
        if (!du[a[t]]) q.push(a[t]);
    }
}
```
**核心思想：**
- 使用拓扑排序处理无环部分，贪心处理环部分，选择环中价值最小的节点作为最后卖出的节点。

#### 题解3：Special_Tony (赞：2)
**星级：4星**
**关键亮点：**
- 通过拓扑排序处理无环部分，贪心处理环部分。
- 使用并查集处理环部分，代码结构清晰。
**核心代码：**
```cpp
void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) du[i] = 0, f[i] = i;
    for (int i = 1; i <= n; ++i) cin >> a[i], ++du[a[i]];
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i <= n; ++i) if (!du[i]) q.push(i);
    while (!q.empty()) {
        x = q.front(); q.pop();
        cout << x << ' ';
        if (!--du[a[x]]) q.push(a[x]);
    }
    for (int i = 1; i <= n; ++i) if (du[i]) f[find(i)] = find(a[i]);
    for (int i = 1; i <= n; ++i) if (du[i] && (!mini[find(i)] || c[mini[f[i]]] > c[i])) mini[f[i]] = i;
    for (int i = 1; i <= n; ++i) if (du[i] && i == mini[f[i]]) {
        for (int j = a[i]; j != i; j = a[j]) cout << j << ' ';
        cout << i << ' ';
    }
    cout << '\n';
}
```
**核心思想：**
- 使用并查集处理环部分，选择环中价值最小的节点作为最后卖出的节点。

### 最优关键思路或技巧
1. **拓扑排序**：首先处理没有入度的节点，确保这些节点在它们害怕的节点之前被卖出。
2. **贪心策略**：对于环中的节点，选择价值最小的节点作为最后卖出的节点，以最大化收益。
3. **优先队列**：使用优先队列来动态调整节点的卖出顺序，确保每次卖出价值最小的节点。

### 可拓展之处
该题的思路可以拓展到其他需要处理依赖关系的贪心问题，例如任务调度、资源分配等。通过拓扑排序和贪心策略的结合，可以有效解决这类问题。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)
3. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)

### 个人心得摘录
- **BINYU**：通过拓扑排序和贪心策略的结合，能够有效处理环中的节点，确保收益最大化。
- **Wf_yjqd**：拓扑排序处理无环部分，贪心处理环部分，代码简洁且高效。
- **Special_Tony**：使用并查集处理环部分，代码结构清晰，易于理解。

---
处理用时：61.97秒