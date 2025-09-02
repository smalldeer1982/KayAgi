# 题目信息

# Substring

## 题目描述

You are given a graph with $ n $ nodes and $ m $ directed edges. One lowercase letter is assigned to each node. We define a path's value as the number of the most frequently occurring letter. For example, if letters on a path are "abaca", then the value of that path is $ 3 $ . Your task is find a path whose value is the largest.

## 说明/提示

In the first sample, the path with largest value is $ 1→3→4→5 $ . The value is $ 3 $ because the letter 'a' appears $ 3 $ times.

## 样例 #1

### 输入

```
5 4
abaca
1 2
1 3
3 4
4 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 6
xzyabc
1 2
3 1
2 3
5 4
4 3
6 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 14
xzyzyzyzqx
1 2
2 4
3 5
4 5
2 6
6 8
6 5
2 10
3 9
10 9
4 6
1 10
2 8
3 7
```

### 输出

```
4
```

# AI分析结果



## 唯一算法分类
**拓扑排序 + 动态规划**

---

## 综合分析与结论

### 核心思路与难点
1. **环检测**：通过拓扑排序判断是否存在环（若拓扑后节点数 < 总节点数则有环）。
2. **动态规划设计**：定义 `dp[i][j]` 表示到节点 `i` 时字母 `j` 的最大出现次数，结合拓扑顺序转移。
3. **转移方程**：
   - 若当前节点的字母为 `j`，则 `dp[y][j] = max(dp[y][j], dp[x][j] + 1)`
   - 否则 `dp[y][j] = max(dp[y][j], dp[x][j])`

### 可视化设计要点
- **拓扑排序动画**：用队列可视化入度为0的节点处理过程，高亮当前处理的节点及其出边。
- **DP更新效果**：用颜色区分不同字母的 `dp` 值变化，例如红色表示当前字母的 `dp` 值增加。
- **复古像素风格**：
  - **网格布局**：节点以像素块形式排列，边用箭头连接。
  - **音效触发**：节点入队时播放“滴”声，环检测失败时播放低沉音效。
  - **自动演示**：按拓扑顺序逐步执行，每步展示 `dp` 值的更新逻辑。

---

## 题解清单（≥4星）

### 1. Merron（⭐️⭐️⭐️⭐️⭐️）
- **关键亮点**：
  - 使用拓扑排序判断环，逻辑清晰。
  - DP初始化直接利用节点自身字母的初始计数。
  - 代码结构模块化，注释详细。
- **代码片段**：
  ```cpp
  while(!Q.empty()) {
      int x = Q.front(); Q.pop();
      for (int y : E[x]) {
          for (int j=1; j<=26; j++) {
              if (val[y]==j) dp[y][j] = max(dp[y][j], dp[x][j]+1);
              else dp[y][j] = max(dp[y][j], dp[x][j]);
          }
          // 入度处理略...
  ```

### 2. Binary_Lee（⭐️⭐️⭐️⭐️）
- **关键亮点**：
  - 字母映射为0-25简化处理。
  - 代码简洁，转移逻辑与拓扑排序耦合度高。
- **代码片段**：
  ```cpp
  for (int j=0; j<26; j++) {
      if (b[tmp]==j) f[tmp][j] = max(f[tmp][j], f[k][j]+1);
      else f[tmp][j] = max(f[tmp][j], f[k][j]);
  }
  ```

### 3. ArcherHavetoLearnWhk（⭐️⭐️⭐️⭐️）
- **关键亮点**：
  - 初始化时直接设置 `dp[i][s[i]] = 1`，逻辑直观。
  - 自环特判优化。
- **代码片段**：
  ```cpp
  if (x == y) { cout << -1; return 0; } // 自环直接判-1
  ```

---

## 核心代码实现

### 拓扑排序 + DP 核心逻辑
```cpp
// 拓扑排序与DP转移
queue<int> q;
for (int i=1; i<=n; i++) 
    if (in[i]==0) q.push(i);

int cnt = 0;
while (!q.empty()) {
    int u = q.front(); q.pop();
    cnt++;
    for (int v : edges[u]) {
        for (int j=0; j<26; j++) {
            dp[v][j] = max(dp[v][j], dp[u][j] + (s[v]-'a'==j ? 1 : 0));
        }
        in[v]--;
        if (in[v]==0) q.push(v);
    }
}
// 环检测
if (cnt < n) cout << -1;
else {
    int ans = 0;
    for (int i=1; i<=n; i++)
        for (int j=0; j<26; j++)
            ans = max(ans, dp[i][j]);
    cout << ans;
}
```

---

## 同类型题推荐
1. **P1113 杂务**：DAG 上的拓扑排序与最长路径。
2. **P4017 最大食物链计数**：拓扑排序结合路径计数 DP。
3. **P3388 割点**：图论基础，检测关键节点。

---

## 个人心得摘录
- **Merron**：在输入字符时发现 `cin` 与 `getchar()` 的玄学问题，提醒注意输入细节。
- **Isshiki·Iroha**：初始代码因数组大小错误 WA 多次，强调边界条件验证的重要性。

---

## 可视化算法演示（伪代码）
```javascript
// 伪代码：拓扑排序与DP的Canvas动画
class TopoAnim {
    constructor(nodes, edges) {
        this.nodes = nodes; // 节点坐标与颜色
        this.edges = edges; // 边集合
        this.queue = [入度为0的节点];
    }

    drawStep() {
        // 高亮当前处理的节点u
        drawNode(u, 'yellow');
        // 遍历u的邻边，绘制边动画
        edges[u].forEach(v => {
            drawEdge(u, v, 'green');
            // 更新v的dp值并高亮变化
            updateDPColor(v, dp[v]);
        });
        // 节点v入队时播放音效
        if (in[v]==0) playSound('enqueue.wav');
    }
}
```

---
处理用时：67.01秒