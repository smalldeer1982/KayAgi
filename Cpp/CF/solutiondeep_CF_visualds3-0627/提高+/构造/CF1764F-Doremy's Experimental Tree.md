# 题目信息

# Doremy's Experimental Tree

## 题目描述

Doremy has an edge-weighted tree with $ n $ vertices whose weights are integers between $ 1 $ and $ 10^9 $ . She does $ \frac{n(n+1)}{2} $ experiments on it.

In each experiment, Doremy chooses vertices $ i $ and $ j $ such that $ j \leq i $ and connects them directly with an edge with weight $ 1 $ . Then, there is exactly one cycle (or self-loop when $ i=j $ ) in the graph. Doremy defines $ f(i,j) $ as the sum of lengths of shortest paths from every vertex to the cycle.

Formally, let $ \mathrm{dis}_{i,j}(x,y) $ be the length of the shortest path between vertex $ x $ and $ y $ when the edge $ (i,j) $ of weight $ 1 $ is added, and $ S_{i,j} $ be the set of vertices that are on the cycle when edge $ (i,j) $ is added. Then,
 $$ f(i,j)=\sum_{x=1}^{n}\left(\min_{y\in S_{i,j}}\mathrm{dis}_{i,j}(x,y)\right).  $$
 
 Doremy writes down all values of  $ f(i,j) $  such that  $ 1 \leq j \leq i \leq n $ , then goes to sleep. However, after waking up, she finds that the tree has gone missing. Fortunately, the values of  $ f(i,j) $  are still in her notebook, and she knows which  $ i $  and  $ j $  they belong to. Given the values of  $ f(i,j)$, can you help her restore the tree?

It is guaranteed that at least one suitable tree exists.

## 说明/提示

In the first test case, the picture below, from left to right, from top to bottom, shows the graph when pairs $ (1,1) $ , $ (1,2) $ , $ (1,3) $ , $ (2,2) $ , $ (2,3) $ , $ (3,3) $ are connected with an edge, respectively. The nodes colored yellow are on the cycle.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764F/65b459471236cb3c4f73ac2ff04b74120b42f624.png)

## 样例 #1

### 输入

```
3
7
3 5
0 2 8```

### 输出

```
2 3 3
1 2 2```

## 样例 #2

### 输入

```
9
8081910646
8081902766 8081903751
8081902555 8081903540 8081905228
3090681001 3090681986 3090681775 7083659398
7083657913 7083658898 7083658687 2092437133 15069617722
1748216295 1748217280 1748217069 5741194692 749972427 10439821163
2377558289 2377559274 2377559063 6370536686 1379314421 5028071980 8866466178
1746983932 1746984917 1746984706 5739962329 748740064 10438588800 5026839617 10448447704
2341942133 2341943118 2341942907 6334920530 1343698265 4992455824 8830850022 4991223461 9115779270```

### 输出

```
1 2 985
2 3 211
2 4 998244353
2 5 998244853
4 6 671232353
6 8 1232363
4 7 356561356
7 9 35616156```

# AI分析结果



---

## 【算法分类】
生成树（最小生成树）

---

## 【题解思路、算法要点与解决难点】

### 核心思路
通过给定的 $f(i,j)$ 计算所有点对间的距离，构造最小生成树恢复原树结构。关键公式：
$$ \text{dis}(i,j) = \frac{f(i,i) + f(j,j) - 2f(i,j)}{n} $$

### 解决难点
1. **距离公式推导**：发现 $f(i,i)$ 是所有点到 $i$ 的距离和，利用容斥思想推导出点对距离公式。
2. **生成树构造**：证明原树是点对距离的最小生成树，确保边权正确性。
3. **边权计算**：直接使用计算的 $\text{dis}(i,j)$ 作为边权，无需额外步骤。

### 算法流程
1. **计算所有点对距离**：遍历所有 $i,j$，应用上述公式。
2. **Kruskal 算法**：将所有边按距离排序，选择边构建最小生成树。

---

## 【题解评分 (≥4星)】
1. **MSqwq 的题解（5星）**
   - **亮点**：代码简洁，直接应用公式与 Kruskal 算法，逻辑清晰。
   - **核心代码**：
     ```cpp
     for (int i=1;i<=n;i++)
         for (int j=1;j<=i;j++) e[++num]={i,j,(a[i][i]+a[j][j]-2*a[i][j])/n};
     sort(e+1,e+1+num,cmp);
     Kruskal(); // 输出最小生成树的边
     ```

2. **spdarkle 的题解（4星）**
   - **亮点**：明确公式推导，指出生成树是原树的核心性质。
   - **代码**：类似 MSqwq，但未显式展示边权计算。

3. **Alex_wei 的题解（4星）**
   - **亮点**：结合最大生成树性质，通过随机检查优化判断边存在性。

---

## 【最优思路或技巧提炼】
- **关键公式**：$\text{dis}(i,j)=\frac{f(i,i)+f(j,j)-2f(i,j)}{n}$ 是解题核心，将问题转化为生成树问题。
- **生成树构造**：原树是点对距离的最小生成树，直接应用 Kruskal/Prim 算法。
- **边权直接读取**：无需子树大小计算，$\text{dis}$ 即为真实边权。

---

## 【同类型题或类似算法套路】
- **树结构恢复**：利用点对信息（如距离、LCA）重构树，常用生成树或贪心法。
- **公式推导**：通过数学变换将复杂条件转化为可计算量（如距离、边权）。

---

## 【推荐题目】
1. **P1547 Out of Hay**（最小生成树边权最大值）
2. **P1967 货车运输**（最大生成树与路径查询）
3. **P2872 Building Roads**（生成树边权计算）

---

## 【可视化与算法演示】

### 动画设计
1. **初始化网格**：以像素风格绘制节点，初始孤立。
2. **边排序与选择**：高亮当前处理的边（绿色为选中，红色为丢弃）。
3. **生成树构建**：逐步连接节点，显示当前生成树边。
4. **音效提示**：
   - **选中边**：清脆“叮”声。
   - **完成构造**：胜利音效。

### 交互功能
- **步进控制**：空格键暂停/继续，方向键调整速度。
- **自动演示**：AI 自动运行 Kruskal 算法，展示边排序与合并过程。

---

## 【代码实现（关键部分）】
```cpp
#include <algorithm>
#include <iostream>
using namespace std;

struct Edge { int u, v; long long w; };
Edge edges[2000000]; // 假设 n ≤ 2000，总边数约 2e6

int main() {
    int n; cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            long long f_ii, f_jj, f_ij;
            // 输入处理（伪代码）
            edges[cnt++] = {i, j, (f_ii + f_jj - 2*f_ij)/n};
        }
    }
    sort(edges, edges + cnt, [](Edge a, Edge b) { return a.w < b.w; });
    // Kruskal 并查集略...
    // 输出选中的边
}
```

---

## 【复古游戏化效果】
- **像素风格**：16色调色板，节点为8×8像素方块。
- **Canvas 动画**：边按权重排序后逐个飞入画面，选中边闪烁。
- **音效**：使用 Web Audio API 播放芯片音乐，增强复古感。

---
处理用时：213.21秒