# 题目信息

# [USACO05FEB] Rigging the Bovine Election S

## 题目描述

农场被划分为 $5\times 5$ 的格子，每个格子中都有一头奶牛，并且只有荷斯坦（标记为 `H`）和杰西（标记为 `J`）两个品种。如果一头奶牛在另一头上下左右四个格子中的任一格里，我们说它们相连。奶牛要大选了。现在杰西奶牛们想选择 $7$ 头相连的奶牛，划成一个竞选区，使得其中它们品种的奶牛比荷斯坦的多。

要求你编写一个程序求出方案总数。


## 样例 #1

### 输入

```
HHHHH
JHJHJ
HHHHH
HJHHJ
HHHHH```

### 输出

```
2```

# AI分析结果

### 综合分析与结论

本题的核心是通过DFS或暴力枚举来寻找符合条件的7个连通格子，并确保其中`J`的数量多于`H`。题解中主要采用了DFS和暴力枚举两种思路，难点在于如何高效地判重和剪枝。大多数题解通过排序、哈希或map来去重，部分题解通过提前剪枝优化了性能。整体来看，DFS结合哈希或map去重的思路较为清晰且高效，适合本题。

### 所选高星题解

#### 1. **MoonCake2011 (4星)**
- **关键亮点**：使用DFS结合哈希去重，代码结构清晰，优化了搜索过程，通过排序和哈希确保了方案唯一性。
- **核心实现思想**：DFS从每个点开始扩散，记录选中的7个点，排序后计算哈希值存入数组，最后去重得到答案。
- **代码片段**：
  ```cpp
  void dfs(int x, int y, int cnt, int p) {
      v.push_back({x, y});
      if (p == 7) {
          if (cnt > 3) {
              node x = node();
              for (int i = 0; i < 7; i++) x[i] = v[i];
              x.Sort();
              ans.push_back(x.get_hash());
          }
          v.pop_back();
          return;
      }
      vis[x][y] = 1;
      for (int i = 0; i < v.size(); i++) {
          int ux = v[i].first, uy = v[i].second;
          for (int j = 0; j < 4; j++) {
              int tx = ux + d[j][0], ty = uy + d[j][1];
              if (!vis[tx][ty] && check(tx, ty))
                  dfs(tx, ty, cnt + (a[tx][ty] == 'J'), p + 1);
          }
      }
      v.pop_back();
      vis[x][y] = 0;
  }
  ```

#### 2. **xiaoli12345678 (4星)**
- **关键亮点**：DFS结合坐标排序去重，代码结构清晰，通过提前剪枝优化了搜索过程。
- **核心实现思想**：DFS从每个点开始扩散，记录选中的7个点，排序后检查是否重复，最后统计符合条件的方案数。
- **代码片段**：
  ```cpp
  void dfs(int k, int x, int y) {
      if (k > 7) {
          if (x > y) {
              for (int i = 1; i <= 7; i++) c[i] = b[i];
              sort(c + 1, c + 1 + 7, cmp);
              int i = 0;
              for (i = 1; i <= ans; i++) {
                  int j = 0;
                  for (j = 1; j <= 7; j++) {
                      if (c[j].x != v_ans[i][j].x || c[j].y != v_ans[i][j].y) break;
                  }
                  if (j > 7) break;
              }
              if (i > ans) {
                  ans++;
                  for (i = 1; i <= 7; i++) v_ans[ans][i] = c[i];
              }
          }
          return;
      }
      for (int i = 1; i < k; i++) {
          for (int j = 0; j < 4; j++) {
              int xx = b[i].x + dir[j][0], yy = b[i].y + dir[j][1];
              if (xx >= 0 && xx < 5 && yy >= 0 && yy < 5 && !v[xx][yy]) {
                  b[k].x = xx; b[k].y = yy;
                  v[xx][yy] = 1;
                  if (map[xx][yy] == 'J') dfs(k + 1, x + 1, y);
                  else dfs(k + 1, x, y + 1);
                  v[xx][yy] = 0;
              }
          }
      }
  }
  ```

#### 3. **lovely_codecat (4星)**
- **关键亮点**：DFS结合哈希去重，通过坐标压缩优化了哈希计算，代码简洁且高效。
- **核心实现思想**：DFS从每个点开始扩散，记录选中的7个点，压缩坐标后计算哈希值，最后去重得到答案。
- **代码片段**：
  ```cpp
  void dfs(int k, int j) {
      if (k > 7) {
          if (j > 3) chk(ss);
          return;
      }
      if (j + (7 - k) < 3) return;
      for (int h = 0; h < k - 1; h++) {
          for (int i = 0; i < 4; i++) {
              int nx = ss[h].first + dx[i], ny = ss[h].second + dy[i];
              if (!vis[nx][ny] && nx > 0 && nx < 6 && ny > 0 && ny < 6) {
                  vis[nx][ny] = 1;
                  ss.push_back({nx, ny});
                  dfs(k + 1, j + (s[nx][ny] == 'J'));
                  ss.pop_back();
                  vis[nx][ny] = 0;
              }
          }
      }
  }
  ```

### 最优关键思路与技巧
1. **DFS+哈希去重**：通过DFS搜索连通块，使用哈希或map去重，确保方案唯一性。
2. **提前剪枝**：在DFS过程中提前判断是否可能满足条件，减少不必要的搜索。
3. **坐标压缩**：将坐标压缩为单一数值，简化哈希计算。

### 可拓展之处
- **类似题目**：可以扩展到更大规模的矩阵或更复杂的连通条件，如8连通或更长的路径。
- **算法套路**：DFS+哈希去重的思路可以应用于其他需要枚举并去重的问题，如数独、迷宫等。

### 推荐题目
1. [P1074 靶形数独](https://www.luogu.com.cn/problem/P1074)
2. [P1120 小木棍](https://www.luogu.com.cn/problem/P1120)
3. [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)

### 个人心得总结
- **调试经历**：部分题解提到在调试过程中发现剪枝不充分导致超时，通过优化剪枝策略后成功AC。
- **踩坑教训**：在去重时，直接使用坐标排序可能会导致性能问题，使用哈希或map可以更高效地处理去重。
- **顿悟感想**：DFS结合哈希去重的思路在处理枚举问题时非常有效，尤其是在需要去重的场景下。

---
处理用时：60.05秒