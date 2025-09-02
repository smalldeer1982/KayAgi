# 题目信息

# Squid Game

## 题目描述

After watching the new over-rated series Squid Game, Mashtali and Soroush decided to hold their own Squid Games! Soroush agreed to be the host and will provide money for the winner's prize, and Mashtali became the Front Man!

 $ m $ players registered to play in the games to win the great prize, but when Mashtali found out how huge the winner's prize is going to be, he decided to kill eliminate all the players so he could take the money for himself!

Here is how evil Mashtali is going to eliminate players:

There is an unrooted tree with $ n $ vertices. Every player has $ 2 $ special vertices $ x_i $ and $ y_i $ .

In one operation, Mashtali can choose any vertex $ v $ of the tree. Then, for each remaining player $ i $ he finds a vertex $ w $ on the simple path from $ x_i $ to $ y_i $ , which is the closest to $ v $ . If $ w\ne x_i $ and $ w\ne y_i $ , player $ i $ will be eliminated.

Now Mashtali wondered: "What is the minimum number of operations I should perform so that I can remove every player from the game and take the money for myself?"

Since he was only thinking about the money, he couldn't solve the problem by himself and asked for your help!

## 说明/提示

Explanation for the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1610H/2f92b74ef3689103fc27552fedd0869997b9492b.png)In the first operation, Mashtali can choose vertex $ 1 $ and eliminate players with colors red and blue. In the second operation, he can choose vertex $ 6 $ and eliminate the player with orange color.In the second sample, Mashtali can't eliminate the first player.

## 样例 #1

### 输入

```
6 3
1 1 1 4 4
1 5
3 4
2 6```

### 输出

```
2```

## 样例 #2

### 输入

```
5 3
1 1 3 3
1 2
1 4
1 5```

### 输出

```
-1```

# AI分析结果



### **综合分析与结论**

#### **核心思路与难点**
1. **问题拆解**：将路径分为直链（祖先后代路径）和曲链（非祖先后代路径）。
2. **贪心策略**：
   - **直链处理**：选择深度最大的路径的关键点（`w`），优先覆盖更多路径。
   - **曲链处理**：若直链处理后仍有未覆盖的曲链，额外选择根节点。
3. **无解条件**：存在长度为 1 的路径（`x` 和 `y` 是父子关系）。
4. **数据结构**：使用树形 DP 维护子树覆盖情况，或贪心排序后覆盖。

#### **可视化设计思路**
1. **动态树形结构**：用 Canvas 绘制树，高亮当前选择的点 `v` 及其覆盖的路径。
2. **颜色标记**：
   - 红色：当前选择的点 `v`。
   - 绿色：已覆盖的路径。
   - 黄色：待处理的路径。
3. **步进控制**：单步执行贪心选择，展示每次操作后的剩余路径。
4. **复古像素风格**：使用 8-bit 音效（如选择时“哔”声），背景音乐循环播放。

---

### **题解评分（≥4星）**

| 作者          | 评分 | 亮点                                                                 |
|---------------|------|----------------------------------------------------------------------|
| **tzc_wk**    | ⭐⭐⭐⭐⭐ | 贪心思路清晰，覆盖直链与曲链，代码简洁高效。                          |
| **chl_cl**    | ⭐⭐⭐⭐   | 树形 DP 状态设计巧妙，详细解释转移逻辑，适合动态规划学习者。          |
| **DaiRuiChen**| ⭐⭐⭐⭐   | 代码短小精悍，综合贪心与 DP，适合竞赛选手快速实现。                   |

---

### **最优思路提炼**

#### **贪心策略核心**
1. **直链覆盖**：按深度从大到小排序，每次选择路径 `u→v` 的最近公共祖先 `w` 的最深点，覆盖最多未处理路径。
2. **曲链覆盖**：若所有直链处理后仍有曲链未被覆盖，额外选根节点 `1`。

#### **关键代码片段（DaiRuiChen007 版本）**
```cpp
void dfs(int u) {
    for (int v : G[u]) dfs(v), dp[u] += dp[v]; // 累加子树覆盖
    for (int v : Q[u]) dp[u] = max(dp[u], dp[v] + 1); // 处理直链
}
int main() {
    // ... 预处理 LCA 和路径分类
    dfs(1);
    for (auto [u, v] : P) dp[1] = max(dp[1], dp[u] + dp[v] + 1); // 处理曲链
    cout << dp[1];
}
```

---

### **同类型题目推荐**
1. **P3574 [POI2014] FAR-FarmCraft**：树形 DP + 贪心选择遍历顺序。
2. **P5021 [NOIP2018 提高组] 赛道修建**：树上路径覆盖，贪心选择最长边。
3. **P3523 [POI2011] DYN-Dynamite**：树上关键点选择，覆盖特定路径。

---

### **个人心得摘录**
- **调试教训**：未正确处理路径长度为 1 的情况导致 WA，需注意边界条件。
- **顿悟点**：曲链的覆盖仅需根节点，与直链的贪心选择相互独立，可分开处理。

---

### **可视化与算法演示**

#### **贪心过程动画设计**
1. **初始化**：绘制树结构，标记所有直链（蓝色）和曲链（橙色）。
2. **贪心选择**：
   - **Step 1**：选择最深直链的 `w` 点（红色），覆盖其子树内路径。
   - **Step 2**：更新剩余路径，重复选择最深未覆盖直链。
   - **Final**：若曲链未覆盖，高亮根节点 `1`。
3. **交互功能**：支持暂停/继续，调整动画速度，查看覆盖逻辑。

#### **复古游戏化实现**
```javascript
// 伪代码：Canvas 绘制树与路径
function drawTree() {
    ctx.fillStyle = "#000"; // 黑色背景
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    // 绘制树节点（像素风格）
    nodes.forEach(node => {
        ctx.fillStyle = node === selected ? "#FF0000" : "#FFF";
        ctx.fillRect(node.x, node.y, 8, 8);
    });
    // 播放音效
    if (step === 'select') playSound('beep.wav');
}
```

---

### **代码实现（贪心 + DP 完整版）**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
vector<int> G[N], Q[N];
vector<pair<int, int>> P;
int n, m, dp[N], f[N][20], dep[N];

void dfs(int u, int fa) {
    f[u][0] = fa;
    for (int i = 1; i < 20; i++) f[u][i] = f[f[u][i-1]][i-1];
    for (int v : G[u]) if (v != fa) dep[v] = dep[u] + 1, dfs(v, u);
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19; i >= 0; i--) if (dep[f[u][i]] >= dep[v]) u = f[u][i];
    return u == v ? u : f[u][0];
}

void solve(int u) {
    for (int v : G[u]) solve(v), dp[u] += dp[v];
    for (int v : Q[u]) dp[u] = max(dp[u], dp[v] + 1);
}

int main() {
    cin >> n >> m;
    for (int i = 2, u; i <= n; i++) cin >> u, G[u].push_back(i);
    dfs(1, 0);
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        if (dep[u] > dep[v]) swap(u, v);
        int w = lca(u, v);
        if (w == u) {
            if (dep[v] - dep[u] == 1) return puts("-1"), 0;
            for (int j = 19; j >= 0; j--) if (dep[f[v][j]] > dep[u]) v = f[v][j];
            Q[v].push_back(u);
        } else P.emplace_back(u, v);
    }
    solve(1);
    for (auto [u, v] : P) dp[1] = max(dp[1], dp[u] + dp[v] + 1);
    cout << dp[1] << endl;
    return 0;
}
```

---
处理用时：78.71秒