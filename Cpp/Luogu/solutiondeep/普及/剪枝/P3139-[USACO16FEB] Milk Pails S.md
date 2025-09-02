# 题目信息

# [USACO16FEB] Milk Pails S

## 题目描述

Farmer John 接到了一份需要立即完成的订单，要求他提供恰好 $M$ 单位的牛奶（$1 \leq M \leq 200$）。不幸的是，他先进的挤奶机刚刚坏了，现在他只有两个容量为整数 $X$ 和 $Y$（$1 \leq X, Y \leq 100$）的牛奶桶可以用来量取牛奶。两个桶最初都是空的。使用这两个桶，他可以执行最多 $K$ 次以下类型的操作（$1 \leq K \leq 100$）：

- 他可以将任意一个桶完全装满。

- 他可以将任意一个桶完全倒空。

- 他可以将一个桶中的牛奶倒入另一个桶，直到前者被倒空或后者被装满（以先发生的情况为准）。

尽管 FJ 意识到他可能无法最终在两个桶中得到恰好 $M$ 单位的牛奶，但请帮助他计算 $M$ 与两个桶中牛奶总量之间的最小误差。也就是说，请计算 $|M-M'|$ 的最小值，其中 $M'$ 是 FJ 可以在两个桶中共同构造的牛奶量。

## 说明/提示

在两步操作中，FJ 可以在他的桶中留下以下数量的牛奶：

```
(0, 0) = 0 单位  
(14, 0) = 14 单位  
(0, 50) = 50 单位  
(0, 14) = 14 单位  
(14, 36) = 50 单位  
(14, 50) = 64 单位  
```

最接近 32 单位的是 14 单位，误差为 18。注意，要倒空第一个桶以得到 (0, 36) 需要额外的步骤。

## 样例 #1

### 输入

```
14 50 2 32```

### 输出

```
18```

# AI分析结果

### 综合分析与结论

本题的核心是通过有限的操作次数，找到两个桶中牛奶总量的最佳近似值。题解中主要采用了DFS、BFS和DP等算法，结合剪枝和记忆化优化来减少搜索空间。整体来看，DFS和BFS的实现较为直观，而DP则通过状态转移来优化时间复杂度。尽管题解数量较多，但大多数题解在思路清晰度和代码优化上仍有提升空间。

### 所选高星题解

#### 1. 作者：NaVi_Awson (4星)
- **关键亮点**：使用DFS结合剪枝，通过`f[i][j]`记录状态是否出现过，避免重复搜索，思路清晰且代码简洁。
- **个人心得**：作者提到DFS和BFS的思路相似，但未提供BFS代码，暗示了BFS的实现方式。
- **核心代码**：
  ```cpp
  void dfs(int xn, int yn, int kn) {
      if ((f[xn][yn] == 1) || (kn - 1 > k)) return;
      f[xn][yn] = 1;
      ans = min(ans, abs(m - xn - yn));
      dfs(x, yn, kn + 1);
      dfs(xn, y, kn + 1);
      dfs(0, yn, kn + 1);
      dfs(xn, 0, kn + 1);
      if (x - xn <= yn) dfs(x, yn - (x - xn), kn + 1);
      else dfs(xn + yn, 0, kn + 1);
      if (y - yn <= xn) dfs(xn - (y - yn), y, kn + 1);
      else dfs(0, xn + yn, kn + 1);
      f[xn][yn] = 0;
  }
  ```

#### 2. 作者：SUNCHAOYI (4星)
- **关键亮点**：使用BFS结合状态记录数组`vis[i][j]`，避免重复状态入队，思路清晰且代码结构良好。
- **个人心得**：作者提醒注意递归边界，调试时发现边界条件错误，强调了边界条件的重要性。
- **核心代码**：
  ```cpp
  void search(int num) {
      if (num == k + 1) return;
      while (!q.empty()) {
          _pair now = q.front(); q.pop();
          ans = min(ans, abs(m - now.dx - now.dy));
          if (!vis[x][now.dy]) milk.push({x, now.dy}), vis[x][now.dy] = 1;
          if (!vis[now.dx][y]) milk.push({now.dx, y}), vis[now.dx][y] = 1;
          if (!vis[now.dx][0]) milk.push({now.dx, 0}), vis[now.dx][0] = 1;
          if (!vis[0][now.dy]) milk.push({0, now.dy}), vis[0][now.dy] = 1;
          if (!vis[now.dx - min(now.dx, y - now.dy)][min(y, now.dy + now.dx)])
              milk.push({now.dx - min(now.dx, y - now.dy), min(y, now.dy + now.dx)}), vis[now.dx - min(now.dx, y - now.dy)][min(y, now.dy + now.dx)] = 1;
          if (!vis[min(x, now.dx + now.dy)][now.dy - min(now.dy, x - now.dx)])
              milk.push({min(x, now.dx + now.dy), now.dy - min(now.dy, x - now.dx)}), vis[min(x, now.dx + now.dy)][now.dy - min(now.dy, x - now.dx)] = 1;
      }
      while (!milk.empty()) q.push(milk.front()), milk.pop();
      search(num + 1);
  }
  ```

#### 3. 作者：SIGSEGV (4星)
- **关键亮点**：使用BFS结合状态记录数组`vis[i][j][k]`，避免重复状态入队，代码简洁且优化到位。
- **核心代码**：
  ```cpp
  void bfs() {
      bool vis[101][101][101] = {};
      queue<Node> q;
      q.push({0, 0, 0}); vis[0][0][0] = 1;
      while (!q.empty()) {
          Node n = q.front(); q.pop();
          if (n.cnt == kk || n.x == 0 || n.y == 0) {
              ans = min(ans, abs(n.x + n.y - need));
              if (n.cnt == kk) continue;
          }
          int x = n.x, y = n.y, cnt = n.cnt + 1;
          if (!vis[b1][y][cnt]) q.push({b1, y, cnt}), vis[b1][y][cnt] = 1;
          if (!vis[x][b2][cnt]) q.push({x, b2, cnt}), vis[x][b2][cnt] = 1;
          if (!vis[0][y][cnt]) q.push({0, y, cnt}), vis[0][y][cnt] = 1;
          if (!vis[x][0][cnt]) q.push({x, 0, cnt}), vis[x][0][cnt] = 1;
          int Y = x + y, X = 0;
          if (Y > b2) X = Y - b2, Y = b2;
          if (!vis[X][Y][cnt]) q.push({X, Y, cnt}), vis[X][Y][cnt] = 1;
          X = x + y, Y = 0;
          if (X > b1) Y = X - b1, X = b1;
          if (!vis[X][Y][cnt]) q.push({X, Y, cnt}), vis[X][Y][cnt] = 1;
      }
      printf("%d", ans);
  }
  ```

### 最优关键思路与技巧

1. **状态记录与剪枝**：无论是DFS还是BFS，通过记录状态是否出现过，避免重复搜索，是减少时间复杂度的关键。
2. **边界条件处理**：在DFS和BFS中，正确处理边界条件（如操作次数是否超过K）是避免无效搜索的重要步骤。
3. **状态转移优化**：在BFS中，通过数学公式简化状态转移，减少代码冗余，提升代码可读性和执行效率。

### 可拓展之处

- **类似问题**：类似的问题可以通过状态记录和剪枝来优化搜索空间，如“倒水问题”、“拼图问题”等。
- **算法套路**：DFS/BFS结合剪枝和记忆化是解决搜索类问题的常见套路，适用于状态空间较大的问题。

### 推荐题目

1. [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 个人心得总结

- **调试经历**：SUNCHAOYI在调试时发现边界条件错误，强调了边界条件的重要性。
- **踩坑教训**：SIGSEGV在实现BFS时，通过状态记录数组避免了重复状态入队，提升了代码效率。

---
处理用时：53.16秒