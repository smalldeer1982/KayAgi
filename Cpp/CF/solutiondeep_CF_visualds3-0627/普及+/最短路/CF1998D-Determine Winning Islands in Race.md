# 题目信息

# Determine Winning Islands in Race

## 题目描述

MOOOOOOOOOOOOOOOOO

— Bessie the Cow, The Art of Racing on Islands



Two of Farmer John's cows, Bessie and Elsie, are planning to race on $ n $ islands. There are $ n - 1 $ main bridges, connecting island $ i $ to island $ i + 1 $ for all $ 1 \leq i \leq n - 1 $ . Additionally, there are $ m $ alternative bridges. Elsie can use both main and alternative bridges, while Bessie can only use main bridges. All bridges are one way and can only be used to travel from an island with a lower index to an island with a higher index.

Initially, Elsie starts on island $ 1 $ , and Bessie starts on island $ s $ . The cows alternate turns, with Bessie making the first turn. Suppose the cow is on island $ i $ . During a cow's turn, if there are any bridges connecting island $ i $ to island $ j $ , then the cow can move to island $ j $ . Then, island $ i $ collapses, and all bridges connecting to island $ i $ also collapse. Also, note the following:

- If there are no bridges connecting island $ i $ to another island, then island $ i $ collapses, and this cow is eliminated from the race.
- If the other cow is also on island $ i $ , then after this cow moves to another island, the island collapses, and the other cow is eliminated from the race.
- After an island or bridge collapses, no cows may use them.
- If a cow is eliminated, their turn is skipped for the rest of the race.

The race ends once either cow reaches island $ n $ . It can be shown that regardless of the cows' strategies, at least one cow reaches island $ n $ . Bessie wins if and only if she reaches island $ n $ first.

For each $ 1 \leq s \leq n - 1 $ , determine whether Bessie wins if she starts the race on island $ s $ . Assume both cows follow optimal strategies to ensure their own respective victories.

## 说明/提示

In the first test case, there are no alternative bridges for Elsie to overtake Bessie and reach island $ n $ first, so Bessie will win on all islands because she always moves first.

In the second case, Bessie will lose if she starts on island $ 3 $ because:

- Bessie's Turn: Take a main bridge from island $ 3 $ to island $ 4 $ .
- Elsie's Turn: Take a main bridge from island $ 1 $ to island $ 2 $ .
- Bessie's Turn: Take a main bridge from island $ 4 $ to island $ 5 $ .
- Elsie's Turn: Take an alternative bridge from island $ 2 $ to island $ 6 $ . Elsie reaches island $ n $ first.

## 样例 #1

### 输入

```
5
6 0
6 1
2 6
6 1
1 5
10 4
1 3
1 6
2 7
3 8
15 3
2 8
4 9
8 15```

### 输出

```
11111
11011
10011
100001111
11000111000111```

# AI分析结果



**唯一算法分类**：动态规划/贪心

---

### **题解思路、算法要点与解决难点**

**核心思路**  
所有题解的共同点在于计算Elsie到达各点的最短时间，并与Bessie的时间比较。Bessie的时间固定为 `v-s`（从起点`s`到`v`），而Elsie的最短时间通过动态规划（DP）计算。

**关键步骤**  
1. **动态规划预处理**：  
   - 维护 `dis[i]` 表示Elsie到达点`i`的最短时间。  
   - 主桥处理：`dis[i] = min(dis[i], dis[i-1]+1)`。  
   - 备用桥处理：对每条`u→v`的边，更新 `dis[v] = min(dis[v], dis[u]+1)`。  

2. **判断胜负条件**：  
   - 对每个备用桥`u→v`，若Elsie的时间`dis[v]`小于Bessie的时间`v-s`，则Elsie赢。  
   - 通过维护全局变量 `mnp`（最大的`s`值使得Bessie输），合并所有备用桥的影响。

**解决难点**  
- **高效合并区间**：通过动态维护`mnp`，避免复杂的区间合并操作。  
- **时间复杂度优化**：将问题转化为线性DP，时间复杂度为 `O(n + m)`。

---

### **题解评分 (≥4星)**

1. **Redshift_Shine (⭐⭐⭐⭐⭐)**  
   - **亮点**：线性DP思路清晰，代码简洁高效，维护`mnp`变量直接判断胜负。  
   - **关键代码**：  
     ```cpp
     for (int u = 1; u < n; u++) {
         dp[u] = min(dp[u], dp[u-1] + 1);
         for (int v : g[u]) {
             mnp = max(mnp, v - dp[u]);
         }
         res[u] = (u >= mnp) ? '1' : '0';
     }
     ```

2. **KarmaticEnding (⭐⭐⭐⭐)**  
   - **亮点**：利用差分数组标记无效区间，适用于区间覆盖问题。  
   - **关键代码**：  
     ```cpp
     for (auto [u, v] : edges) {
         int l = u + 1, r = v - dis[u] - 1;
         if (l <= r) diff[l]++, diff[r+1]--;
     }
     ```

3. **Register_int (⭐⭐⭐)**  
   - **亮点**：简洁的贪心实现，但代码可读性稍差。  
   - **关键代码**：  
     ```cpp
     for (int u = 1; u < n; u++) {
         dis[u] = min(dis[u], dis[u-1] + 1);
         for (int v : g[u]) {
             res = min(res, n - v + dis[v]);
         }
     }
     ```

---

### **最优思路或技巧提炼**

1. **动态规划预处理**：  
   - 通过线性DP计算Elsie的最短路径，充分利用图的DAG性质。  
   - 主桥和备用桥的更新顺序确保每个点的时间最优。

2. **全局变量`mnp`维护**：  
   - 对每条备用桥`u→v`，计算其影响的`s`范围，更新`mnp = max(mnp, v - dis[u])`。  
   - 最终只需比较`s >= mnp`即可判断Bessie是否必胜。

3. **差分数组优化区间覆盖**（备用方案）：  
   - 标记所有导致Bessie输的区间，前缀和统计覆盖情况。

---

### **同类型题推荐**

1. **CF 1472E - Correct Placement**  
   - 类似区间覆盖和贪心判断。

2. **LeetCode 45. Jump Game II**  
   - 贪心+动态规划优化跳跃问题。

3. **洛谷 P1359 租用游艇**  
   - DAG上的最短路径动态规划。

---

### **可视化与算法演示**

**动画设计**：  
1. **像素风格岛屿与桥梁**：  
   - 岛屿用方块表示，主桥为绿色，备用桥为黄色。  
   - Elsie（牛头图标）和Bessie（另一颜色图标）移动时触发坍塌动画。

2. **动态更新`dis`与`mnp`**：  
   - 每处理一个岛屿`u`，显示`dis[u]`的值，并高亮更新的备用桥。  
   - `mnp`值用红色进度条展示，直观反映Bessie的胜负临界点。

3. **音效与交互**：  
   - 移动时播放“滴答”音效，坍塌时播放爆炸音效。  
   - 用户可拖动滑块调整`s`值，实时查看胜负结果。

**复古像素效果**：  
- **Canvas绘制**：岛屿按网格排列，移动时图标逐帧更新。  
- **音效**：8-bit风格BGM，关键操作（如到达终点）触发胜利音效。

---

### **代码实现（核心逻辑）**

**Redshift_Shine的优化代码**  
```cpp
#include <vector>
using namespace std;

const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
int dp[MAXN], mnp;

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        dp[i] = i;  // 初始化为最大可能时间
    }
    for (int u, v; m--; ) {
        cin >> u >> v;
        g[u].push_back(v);
    }
    
    mnp = 0;
    for (int u = 1; u < n; u++) {
        dp[u] = min(dp[u], dp[u-1] + 1);  // 主桥更新
        for (int v : g[u]) {
            dp[v] = min(dp[v], dp[u] + 1);  // 备用桥更新
            mnp = max(mnp, v - dp[u]);      // 更新临界点
        }
        cout << (u >= mnp ? '1' : '0');
    }
    cout << "\n";
}
```

---

### **个人心得摘录**

- **临界点维护是关键**：`mnp`的更新需要理解每条备用桥对`s`的影响范围。  
- **线性DP的威力**：通过顺序处理岛屿，自然覆盖所有可能路径，避免复杂数据结构。

---
处理用时：106.80秒