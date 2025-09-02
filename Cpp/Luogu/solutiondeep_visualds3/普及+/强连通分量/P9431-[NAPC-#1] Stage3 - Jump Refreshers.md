# 题目信息

# [NAPC-#1] Stage3 - Jump Refreshers

## 题目背景

> ![](https://cdn.luogu.com.cn/upload/image_hosting/wkktxonu.png)

## 题目描述

**注意本题中 kid 的移动方式与 iw 游戏中不同（）。**

kid 面前有一个无穷大的竖直二维平面。坐标系 $x$ 轴正方向为从左到右，$y$ 轴正方向为从下到上。

地图（该平面）内有 $n$ 个**位置互不相同**的**可以无限重复使用**的跳跃球。当 kid 正好位于某跳跃球位置时，他可以让 shift 键按下，然后他会瞬间上升 $d$ 格（此期间不能左右移动）。他每秒往下坠落 $1$ 格，同时每秒 kid 可以选择：向左或向右移动 1 格，或者不移动。当 kid 不在跳跃球上时他不能起跳。

![](https://cdn.luogu.com.cn/upload/image_hosting/1abzjhjs.png)

上图是一个例子，蓝色区域表示 kid 在跳跃球（箭头）处起跳（$d=2$）后可以达到的区域。**kid 每秒时的横纵坐标只能是整数，即：我们认为他不能达到非整点位置。**

现在，kid 把存档放在了第 $c$ 个跳跃球处（即起点是第 $c$ 个跳跃球处；此时可以立即起跳）。定义 kid 的得分为他经过（即在某处起跳：显然起跳之后可以回到原位置）的**不同**跳跃球的个数。kid 想知道他可以最多获得多少得分（**不需要**（但可以）**回到起点**），请你告诉他吧。

再次提醒：**跳跃球可以无限重复使用，即 kid 可以在某个跳跃球上无限起跳。**

## 说明/提示

### 【数据范围】

**本题采用捆绑测试。**
$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c|c}
\textbf{Subtask} & id= & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1& 1\sim3,36 & n\leqslant10,T\leqslant10 & 10 \r
\textsf2& 4\sim7 & \sum n\leqslant200 & 15 \r
\textsf3& 8\sim13 & \mathbf A & 25 \r
\textsf4& 14\sim18 & \mathbf B & 10 \r
\textsf5& 19\sim35 & - & 40 \r
\end{array}
$$
其中 $\sum n$ 表示单测试点内所有 $n$ 的总和。

$id=1\sim3,36$ 表示 $id\in\{1,2,3,36\}$。
- 特殊性质 $\mathbf A$：保证对于任意不同跳跃球 $u,v$，如果 kid 理论上能从 $u$ 跳到 $v$（理论上：不考虑 kid 能否从起点到达 $u$ 的问题，下同），那么他理论上**一定不可以**从 $v$ 跳到 $u$。
- 特殊性质 $\mathbf B$：保证对于任意跳跃球 $u,v$，如果 kid 理论上能从 $u$ 跳到 $v$，那么他理论上**一定可以**从 $v$ 跳到 $u$。

注意上面的“从 $u$ 跳到 $v$"不一定非得一跳到位。比如样例 #1-2 中可以从第 $3$ 个跳到第 $5$ 个：$3\to2\to4\to5$。

对于 $100\%$ 的数据，$1\leqslant T\leqslant 1000$，$1\leqslant n\leqslant 3000$，$\sum n\leqslant 3000$，$1\leqslant d\leqslant 10^9$，$1\leqslant c\leqslant n$，$1\leqslant x_i,y_i\leqslant10^6$，$(x_i,y_i)$ 互不相同。

---
#### 【样例解释 #1-1】
![](https://cdn.luogu.com.cn/upload/image_hosting/zpc7sm2i.png)

$d=2$，容易发现离开初始位置就上不去了。所以 kid 要么往左边碰第 $2$ 个跳跃球，得分为 $2$；要么往右边跳，经过第 $3$ 和第 $4$ 个跳跃球，得分为 $3$。
#### 【样例解释 #1-2】
![](https://cdn.luogu.com.cn/upload/image_hosting/q8ks8qb4.png)

$d=3$，kid 可以先往下走一圈（$4\to3\to2\to4$）跳回起点，然后往右去碰第 $5$ 个球。左上角的第 $1$ 个跳跃球是碰不到的。
#### 【样例解释 #1-3】
![](https://cdn.luogu.com.cn/upload/image_hosting/akghkpe9.png)

通过最上面那个球是可以跳到右边的。
#### 【样例解释 #1-4】
![](https://cdn.luogu.com.cn/upload/image_hosting/50smzomm.png)

有 的 人 。

## 样例 #1

### 输入

```
4 0
4 2 1
2 4
1 1
5 2
4 1
5 3 4
1 7
2 4
3 2
4 5
8 2
4 1 2
1 1
1 2
1 3
4 1
4 2 1
1 1
4 1
1 4
4 4```

### 输出

```
3
4
4
1```

# AI分析结果


### 💡 Kay的C++算法解析：Stage3 - Jump Refreshers 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：图论 - 强连通分量缩点与DAG动态规划  
🗣️ **初步分析**：  
> 本题可抽象为有向图模型：每个跳跃球是节点，若从球u能跳到球v则建边 \(u \to v\)。解题核心在于处理图中的环（强连通分量），通过**Tarjan算法**将环缩为超级节点（点权=分量大小），转化为有向无环图（DAG），最后用**拓扑排序+DP**求最长路径。  

- **关键步骤可视化设计**：
  - **建图阶段**：用像素网格展示球的位置，高亮满足跳跃条件的边（如绿色箭头）
  - **缩点阶段**：用颜色标记强连通分量，动态演示栈操作和low值更新
  - **DP阶段**：在DAG上用流动光效展示拓扑顺序，节点大小随DP值增大而膨胀

#### 2. 精选优质题解参考
**题解一（来源：DevilsFlame）**  
* **点评**：  
  思路清晰直白：暴力建图 → Tarjan缩点 → 拓扑DP。亮点在于用**map判重边**避免冗余，代码规范性极强（变量名`to/siz`含义明确），边界处理严谨（多测清空全面）。实践价值高，可直接用于竞赛。

**题解二（来源：Svemit）**  
* **点评**：  
  分层讲解特殊性质（A/B）引导思考，突出从特殊到通用的解题逻辑。亮点在于**跳跃条件判断的数学推导**（\(\Delta y + d \geq \Delta x\)），代码模块化（分离建图/缩点/DP），调试心得（赛时看错题目的教训）极具参考性。

**题解三（来源：y_kx_b）**  
* **点评**：  
  提供完整解题框架，亮点在于**反图拓扑DP**的设计，避免记忆化搜索递归开销。代码含详细注释，变量命名规范（`ccb_cnt`表强连通分量数），对缩点后DAG的性质分析深入。

#### 3. 核心难点辨析与解题策略
1. **难点1：跳跃条件建模**  
   * **分析**：需将物理运动转化为数学约束 \(\Delta y + d \geq |\Delta x|\)，优质题解通过坐标差计算实现  
   * 💡 **学习笔记**：二维问题常转化为绝对值不等式处理

2. **难点2：环的处理与缩点**  
   * **分析**：强连通分量内节点可互达，Tarjan算法通过DFS栈识别分量，缩点后点权为分量大小  
   * 💡 **学习笔记**：缩点将图简化为DAG，是处理环问题的核心手段

3. **难点3：DAG上的最长路径**  
   * **分析**：拓扑排序保证无后效性，DP状态 \(f[u]\) 表示以 \(u\) 为终点的最大点权和  
   * 💡 **学习笔记**：\(f[v] = \max(f[v], f[u] + siz[v])\) 体现最优子结构

✨ **解题技巧总结**  
- **图论建模**：将运动约束转化为边存在性判断  
- **分量压缩**：Tarjan缩点处理环，降低问题复杂度  
- **拓扑DP**：按DAG层级递推，避免重复计算  

#### 4. C++核心代码实现赏析
```cpp
// 通用核心实现（综合自优质题解）
#include <bits/stdc++.h>
using namespace std;
const int N = 3005;

struct Point { int x, y; } p[N];
vector<int> G[N], newG[N];
int dfn[N], low[N], scc_id[N], scc_size[N];
int dp[N], stk[N], top, idx, scc_cnt;
bool in_stack[N];

// 跳跃条件判断
bool canJump(int u, int v, int d) {
    return p[u].y + d - p[v].y >= abs(p[u].x - p[v].x);
}

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    stk[++top] = u; in_stack[u] = true;
    for (int v : G[u]) {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (in_stack[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        scc_cnt++;
        while (true) {
            int v = stk[top--];
            in_stack[v] = false;
            scc_id[v] = scc_cnt;
            scc_size[scc_cnt]++;
            if (u == v) break;
        }
    }
}

int main() {
    int T, id; cin >> T >> id;
    while (T--) {
        int n, d, c; cin >> n >> d >> c;
        // 初始化与建图
        for (int i = 1; i <= n; i++) 
            cin >> p[i].x >> p[i].y;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (i != j && canJump(i, j, d))
                    G[i].push_back(j);

        // Tarjan缩点
        tarjan(c);
        // 建新图（DAG）
        for (int u = 1; u <= n; u++) 
            for (int v : G[u])
                if (scc_id[u] != scc_id[v])
                    newG[scc_id[u]].push_back(scc_id[v]);

        // 拓扑排序DP（从起点分量开始）
        queue<int> q;
        q.push(scc_id[c]);
        dp[scc_id[c]] = scc_size[scc_id[c]];
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : newG[u]) {
                if (dp[v] < dp[u] + scc_size[v]) {
                    dp[v] = dp[u] + scc_size[v];
                    q.push(v);
                }
            }
        }
        // 输出最大DP值
        cout << *max_element(dp + 1, dp + scc_cnt + 1) << endl;
    }
}
```

**题解一核心片段赏析**  
```cpp
// 判断跳跃条件（DevilsFlame）
if (abs(v[i].y - v[j].y) + v[j].x - v[i].x - d <= 0)
    e[i].push_back(j);
```
* **亮点**：数学变形避免绝对值计算  
* **解读**：将 \(\Delta y + d \geq |\Delta x|\) 转化为 \(\Delta x + \Delta y \leq d\)，减少计算次数  
* **学习笔记**：不等式变形可优化代码性能  

**题解二拓扑DP片段**  
```cpp
// Svemit的DP递推
for (int u : topo_order) 
    for (int v : newG[u])
        dp[v] = max(dp[v], dp[u] + scc_size[v]);
```
* **亮点**：显式拓扑排序保证无后效性  
* **解读**：先求拓扑序再DP，比记忆化搜索更易理解边界  
* **学习笔记**：DAG上DP常与拓扑排序结合  

#### 5. 算法可视化：像素动画演示
**主题**：8-bit风格《算法探险者》  
**核心演示**：  
1. **场景初始化**  
   - 复古像素网格（FC红白机风格），跳跃球显示为不同颜色圆点  
   - 控制面板：单步执行/自动播放速度滑块（0.5x~2x）  

2. **建图阶段**  
   - 动态绘制有向边：满足跳跃条件时触发"滴"音效，边显示为绿色箭头  
   - 高亮当前判断的点对，显示不等式计算过程  

3. **Tarjan缩点**  
   - 栈操作可视化：入栈节点闪烁，low/dfn值实时显示  
   - 缩点特效：强连通分量收缩为超级节点（像素爆炸动画+胜利音效）  

4. **拓扑DP过程**  
   - 节点按拓扑序脉冲发光，DP值以像素数字显示  
   - 状态转移：光流从u节点流向v节点，伴随数据更新音效  

**交互设计**：  
- **AI演示模式**：自动播放完整流程（类似贪吃蛇AI）  
- **错误反馈**：无效跳跃时播放短促"错误"音效，节点变红  

#### 6. 拓展练习与相似问题
**通用技巧迁移**：  
缩点+DP适用于：状态传递有环的计数问题、路径统计问题  

**洛谷推荐**：  
1. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)  
   * 理由：巩固缩点与DAG上DP的基本应用  
2. [P3627 [APIO2009] 抢掠计划](https://www.luogu.com.cn/problem/P3627)  
   * 理由：练习带点权的缩点+最长路变形  
3. [P2741 [USACO4.4] 重叠的图像](https://www.luogu.com.cn/problem/P2741)  
   * 理由：拓扑排序在DAG中的应用拓展  

#### 7. 学习心得与经验分享
> **参考经验（来自 Svemit）**：  
> "赛时因看错跳跃条件调试1小时，后通过打印中间变量发现坐标转换错误"  
>   
> **点评**：  
> 典型调试教训：  
> 1. 复杂条件应先写伪代码验证  
> 2. 输出中间值（如 \(\Delta x, \Delta y\)）可快速定位逻辑错误  
> 3. 多测数据必须全面清空（特别是栈、DFN数组）  

---
**结语**：  
掌握图论建模与分量分解是解决此类问题的关键。记住：将运动约束转化为图模型 → 缩点消除环 → DAG上DP的三步走策略，配合调试技巧，你一定能征服更多图论难题！🚀

---
处理用时：114.02秒