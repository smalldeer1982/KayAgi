# 题目信息

# Unique Occurrences

## 题目描述

You are given a tree, consisting of $ n $ vertices. Each edge has an integer value written on it.

Let $ f(v, u) $ be the number of values that appear exactly once on the edges of a simple path between vertices $ v $ and $ u $ .

Calculate the sum of $ f(v, u) $ over all pairs of vertices $ v $ and $ u $ such that $ 1 \le v < u \le n $ .

## 样例 #1

### 输入

```
3
1 2 1
1 3 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3
1 2 2
1 3 2```

### 输出

```
2```

## 样例 #3

### 输入

```
5
1 4 4
1 2 3
3 4 4
4 5 5```

### 输出

```
14```

## 样例 #4

### 输入

```
2
2 1 1```

### 输出

```
1```

## 样例 #5

### 输入

```
10
10 2 3
3 8 8
4 8 9
5 8 5
3 10 7
7 8 2
5 6 6
9 3 4
1 6 3```

### 输出

```
120```

# AI分析结果



## 算法分类
线段树分治

---

## 题解思路与核心要点

### 核心思路
所有题解的核心均围绕**颜色独立贡献计算**展开。具体来说，将问题转化为：对于每种颜色 $w$，计算有多少路径恰好包含一条颜色为 $w$ 的边。最终将所有颜色的贡献累加即为答案。

### 关键步骤
1. **颜色分离**：将每条颜色为 $w$ 的边从树中删除后，形成多个连通块。
2. **贡献计算**：颜色 $w$ 的每条边 $(u,v)$ 的贡献为两端连通块大小的乘积。
3. **高效维护**：通过数据结构或递归策略快速计算每个颜色对应的连通块信息。

---

## 题解评分与亮点（≥4星）

### 1. 作者：lingfunny（★★★★★）
- **思路亮点**：O(n) 复杂度，通过递归处理 DFS 序降序排列的关键点，利用树状数组维护子树和。
- **代码优势**：无需复杂数据结构，仅用两次 DFS 预处理和树状数组即可高效计算贡献。
- **核心代码**：
  ```cpp
  void solve(int Lp, int Rp, int &p, const vector<pair<int, int>> &E) {
      vector<int> sub;
      int lst = -1, cur = (Rp - Lp + 1)>>1;
      for(int i = p; i < (int)E.size(); ++i) {
          int v = E[i].second;
          if(L[v] > Rp) { p = i-1; break; }
          if(lst == -1 || L[v] > R[lst]) {
              lst = v;
              cur -= (R[v] - L[v] + 1)>>1;
              sub.push_back((R[v] - L[v] + 1)>>1);
          } else {
              sub.pop_back();
              sub.push_back(solve(L[lst], R[lst], i, E));
          }
          p = i;
      }
      for(int x: sub) ans += (LL)cur*x;
      return cur;
  }
  ```

### 2. 作者：7KByte（★★★★☆）
- **方法亮点**：线段树分治 + 可撤销并查集，将颜色作为时间轴分治处理。
- **实现优势**：代码结构清晰，通过线段树分治将颜色划分为多个区间，利用并查集维护连通块。
- **核心代码**：
  ```cpp
  void solve(int x, int l, int r) {
      vector<int> dl;
      for (auto [u, v] : u[x]) {
          int p = find(u), q = find(v);
          if (sz[p] > sz[q]) swap(p, q);
          dl.push_back(p), sz[q] += sz[p], fa[p] = q;
      }
      if (l == r) {
          for (auto [u, v] : c[l]) ans += sz[find(u)] * sz[find(v)];
      } else {
          int mid = (l + r) >> 1;
          solve(ls, l, mid), solve(rs, mid + 1, r);
      }
      reverse(dl.begin(), dl.end());
      for (auto w : dl) sz[fa[w]] -= sz[w], fa[w] = w;
  }
  ```

### 3. 作者：FelFa_1414666（★★★★☆）
- **优化思路**：递归处理 DFS 时动态维护每个颜色对应的连通块，通过栈记录子树大小变化。
- **代码简洁性**：仅需两次 DFS 和简单数组操作，避免复杂数据结构。
- **核心代码**：
  ```cpp
  void dfs(int u) {
      for (auto [v, w] : G[u]) {
          x[w].push_back(sz[v]);
          fa[w].push_back(cur[w]);
          x[w][cur[w]] -= sz[v];
          int tmp = cur[w];
          cur[w] = x[w].size() - 1;
          dfs(v);
          cur[w] = tmp;
      }
  }
  ```

---

## 最优思路提炼
**DFS序递归分割法**（lingfunny）：
1. **预处理**：通过 DFS 记录每个节点的子树大小和 DFS 序。
2. **降序处理**：将颜色为 $w$ 的边按 DFS 序降序排列，保证子树优先处理。
3. **连通块计算**：递归过程中用树状数组维护子树和，动态计算每个连通块的大小。
4. **贡献统计**：在递归返回时累加相邻连通块的乘积贡献。

---

## 相似题目推荐
1. [CF741D - Arpa’s letter-marked tree](https://codeforces.com/problemset/problem/741/D)
2. [洛谷P4213 - 子树统计](https://www.luogu.com.cn/problem/P4213)
3. [洛谷P2664 - 树上游戏](https://www.luogu.com.cn/problem/P2664)

---

## 可视化与算法演示

### 动画设计思路
1. **像素风格渲染**：用 8-bit 色块表示树节点，不同颜色边用不同色调高亮。
2. **关键步骤高亮**：
   - **颜色分割**：当处理颜色 $w$ 时，对应的边变为红色，其他边灰化。
   - **连通块划分**：通过闪烁效果展示每次递归分割后的连通块区域。
3. **交互控制**：
   - **步进控制**：允许用户逐层展开递归过程，观察连通块大小的动态更新。
   - **贡献显示**：在连通块分割完成后，用浮动数字显示当前颜色贡献值。

### 复古音效设计
- **分割音效**：每次递归进入新颜色时播放短促的“哔”声。
- **贡献计算**：在乘积计算时播放金币音效增强反馈。

---

## 代码实现（lingfunny 方法核心）
```cpp
void solve(int Lp, int Rp, int &p, const vector<pair<int, int>> &E) {
    vector<int> sub;
    int lst = -1, cur = (Rp - Lp + 1) >> 1;
    for (int i = p; i < (int)E.size(); ++i) {
        int v = E[i].second;
        if (L[v] > Rp) { p = i - 1; break; }
        if (lst == -1 || L[v] > R[lst]) {
            lst = v;
            cur -= (R[v] - L[v] + 1) >> 1;
            sub.push_back((R[v] - L[v] + 1) >> 1);
        } else {
            sub.pop_back();
            sub.push_back(solve(L[lst], R[lst], i, E));
        }
        p = i;
    }
    for (int x : sub) ans += (LL)cur * x;
    return cur;
}
```

---

## 总结
本题解法的核心在于**颜色独立贡献计算**和**高效连通块维护**。最优解通过 DFS 序降序处理，将时间复杂度优化至 O(n)，避免了复杂数据结构的使用。线段树分治方法则通过分治策略平衡了代码复杂度和效率，适合大规模数据处理。

---
处理用时：83.59秒