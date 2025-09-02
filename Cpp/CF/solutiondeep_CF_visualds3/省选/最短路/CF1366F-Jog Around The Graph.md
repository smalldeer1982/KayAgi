# 题目信息

# Jog Around The Graph

## 题目描述

You are given a simple weighted connected undirected graph, consisting of $ n $ vertices and $ m $ edges.

A path in the graph of length $ k $ is a sequence of $ k+1 $ vertices $ v_1, v_2, \dots, v_{k+1} $ such that for each $ i $ $ (1 \le i \le k) $ the edge $ (v_i, v_{i+1}) $ is present in the graph. A path from some vertex $ v $ also has vertex $ v_1=v $ . Note that edges and vertices are allowed to be included in the path multiple times.

The weight of the path is the total weight of edges in it.

For each $ i $ from $ 1 $ to $ q $ consider a path from vertex $ 1 $ of length $ i $ of the maximum weight. What is the sum of weights of these $ q $ paths?

Answer can be quite large, so print it modulo $ 10^9+7 $ .

## 说明/提示

Here is the graph for the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1366F/982d98828c2c04ce07da51dfc61efa355738e144.png)Some maximum weight paths are:

- length $ 1 $ : edges $ (1, 7) $ — weight $ 3 $ ;
- length $ 2 $ : edges $ (1, 2), (2, 3) $ — weight $ 1+10=11 $ ;
- length $ 3 $ : edges $ (1, 5), (5, 6), (6, 4) $ — weight $ 2+7+15=24 $ ;
- length $ 4 $ : edges $ (1, 5), (5, 6), (6, 4), (6, 4) $ — weight $ 2+7+15+15=39 $ ;
- $ \dots $

So the answer is the sum of $ 25 $ terms: $ 3+11+24+39+\dots $

In the second example the maximum weight paths have weights $ 4 $ , $ 8 $ , $ 12 $ , $ 16 $ and $ 20 $ .

## 样例 #1

### 输入

```
7 8 25
1 2 1
2 3 10
3 4 2
1 5 2
5 6 7
6 4 15
5 3 1
1 7 3```

### 输出

```
4361```

## 样例 #2

### 输入

```
2 1 5
1 2 4```

### 输出

```
60```

## 样例 #3

### 输入

```
15 15 23
13 10 12
11 14 12
2 15 5
4 10 8
10 2 4
10 7 5
3 10 1
5 6 11
1 13 8
9 15 4
4 2 9
11 15 1
11 12 14
10 8 12
3 6 11```

### 输出

```
3250```

## 样例 #4

### 输入

```
5 10 10000000
2 4 798
1 5 824
5 2 558
4 1 288
3 4 1890
3 1 134
2 3 1485
4 5 284
3 5 1025
1 2 649```

### 输出

```
768500592```

# AI分析结果


# 💡 Kay的C++算法解析：Jog Around The Graph 深入学习指南 💡

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`动态规划` + `凸包优化`  

🗣️ **初步分析**：
> 本题的核心在于将问题拆解为两个阶段：  
> **1. 有限步长阶段**：用动态规划计算前 m 步的最优路径  
> **2. 无限步长阶段**：用凸包优化处理直线族最大值问题  
> 就像在游戏中先规划短途路线，再选择最佳"刷分点"反复移动。  
> 
> **算法流程**：  
> 1. DP 计算前 m 步每个点的最大路径权重  
> 2. 为每条边生成直线 y = w*x + b  
> 3. 构建凸包找到分段最大值直线  
> 4. 对每个凸包线段进行等差数列求和  
>
> **像素动画设计**：  
> - 顶点显示为不同颜色的像素方块（起点：绿色）  
> - DP 过程：角色从起点扩散，高亮当前处理的顶点和边  
> - 凸包构建：右侧区域动态绘制直线和凸包栈  
> - 音效：移动时8位脚步声，直线入栈时"放置"音效，凸包完成时胜利音效

---

## 2. 精选优质题解参考

**题解：tzc_wk**
* **点评**：该解法思路清晰完整，将问题分为DP预处理和凸包优化两阶段。代码规范：变量命名合理（`dp`/`mx`/`lines`），边界处理严谨（`chkmax`/`chkmin`）。算法亮点：通过斜率排序和单调栈将复杂度优化至O(n log n)。实践价值高：完整处理模运算和数据类型转换（int→long long），可直接用于竞赛。

---

## 3. 核心难点辨析与解题策略

1.  **DP状态转移设计**
    * **分析**：状态定义 `dp[i][v]` 需准确表示经过 i 条边到达 v 的最大权重。转移时需遍历所有邻边更新状态，关键在理解状态维度（步数+顶点）的物理意义
    * 💡 **学习笔记**：DP状态是动态规划的基石，必须覆盖所有可能状态

2.  **直线截距计算**
    * **分析**：截距 b = dp[i][u] - w*i 的推导是本问题核心，表示"抵达边时的基础值"。需注意当不同步数抵达同一边时取最大值
    * 💡 **学习笔记**：截距计算本质是剥离后续固定收益的预处理

3.  **凸包构建与区间划分**
    * **分析**：维护上凸包需按斜率排序+单调栈，利用交点确定每条直线的有效区间。难点在于处理斜率相同情况和浮点精度（EPS=1e-7）
    * 💡 **学习笔记**：凸包优化将 O(n²) 问题降为 O(n log n)

### ✨ 解题技巧总结
- **阶段拆解**：将大问题分解为有限步数 DP + 无限步数凸包优化
- **凸包维护**：斜率排序 → 过滤相同斜率 → 单调栈维护交点单调性
- **边界防御**：DP 初始化为负无穷，凸包交点计算添加 EPS 防溢出

---

## 4. C++核心代码实现赏析

**本题通用核心C++实现参考**
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2000;
const double EPS = 1e-7;
const int MOD = 1e9+7;
const int INV2 = 500000004; // 2的逆元

int n, m, q;
int dp[MAXN+5][MAXN+5]; // dp[步数][顶点]
ll mx[MAXN+5]; // 各边最大截距
struct Edge { int u, v, w; } edges[MAXN+5];
vector<pair<int, int>> graph[MAXN+5];

struct Line {
    int k; ll b; // 斜率(边权), 截距
    bool operator<(const Line& o) const {
        return k != o.k ? k < o.k : b < o.b;
    }
};

double inter(Line a, Line b) {
    return (double)(b.b - a.b)/(a.k - b.k);
}

int main() {
    // 输入初始化
    scanf("%d%d%d", &n, &m, &q);
    for(int i=1; i<=m; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
        graph[edges[i].u].push_back({edges[i].v, edges[i].w});
        graph[edges[i].v].push_back({edges[i].u, edges[i].w});
    }

    // DP预处理
    memset(dp, 0x80, sizeof(dp)); // 初始化为负无穷
    dp[0][1] = 0; // 起点初始化
    
    for(int i=0; i<m; i++) {
        for(int u=1; u<=n; u++) {
            if(dp[i][u] < 0) continue; // 无效状态跳过
            for(auto [v, w] : graph[u]) {
                dp[i+1][v] = max(dp[i+1][v], dp[i][u] + w);
            }
        }
    }
    
    // 计算前m步答案
    ll ans = 0;
    for(int i=1; i<=min(m, q); i++) {
        int cur = 0;
        for(int u=1; u<=n; u++) 
            cur = max(cur, dp[i][u]);
        ans = (ans + cur) % MOD;
    }
    
    // 生成直线族
    vector<Line> lines;
    memset(mx, 0x80, sizeof(mx)); // 初始化为负无穷
    
    for(int i=1; i<=m; i++) {
        for(int u=1; u<=n; u++) {
            if(dp[i][u] < 0) continue;
            for(auto [v, w] : graph[u]) {
                mx[v] = max(mx[v], (ll)dp[i][u] - (ll)w*i);
            }
        }
    }
    
    for(int i=1; i<=m; i++) {
        auto [u, v, w] = edges[i];
        ll b_val = max(mx[u], mx[v]);
        if(b_val > -1e18) // 有效截距
            lines.push_back({w, b_val});
    }
    
    // 构建凸包
    sort(lines.begin(), lines.end());
    vector<Line> hull;
    
    for(auto& line : lines) {
        // 过滤相同斜率
        if(!hull.empty() && hull.back().k == line.k) {
            if(hull.back().b < line.b) hull.pop_back();
            else continue;
        }
        // 维护上凸性
        while(hull.size() >= 2) {
            Line l1 = hull[hull.size()-2];
            Line l2 = hull.back();
            double x1 = inter(l1, line);
            double x2 = inter(l1, l2);
            if(x1 <= x2 + EPS) hull.pop_back();
            else break;
        }
        hull.push_back(line);
    }
    
    // 区间求和
    int L = m+1, R = q;
    for(int i=0; i<hull.size(); i++) {
        double lft = (i==0) ? L : inter(hull[i-1], hull[i]);
        double rht = (i==hull.size()-1) ? R : inter(hull[i], hull[i+1]);
        
        int segL = max(L, (int)ceil(lft+EPS));
        int segR = min(R, (int)floor(rht));
        if(segL > segR) continue;
        
        ll a1 = (hull[i].k * (ll)segL + hull[i].b) % MOD;
        ll an = (hull[i].k * (ll)segR + hull[i].b) % MOD;
        ll cnt = segR - segL + 1;
        ll sum = (a1 + an) * cnt % MOD * INV2 % MOD;
        ans = (ans + sum) % MOD;
    }
    printf("%lld\n", ans);
}
```

**代码解读概要**：  
1. **DP初始化**：`dp[i][v]` 表示 i 步到达 v 的最大权重  
2. **直线生成**：对每条边计算截距 `b = dp[i][u] - w*i`  
3. **凸包构建**：按斜率排序 → 过滤相同斜率 → 单调栈维护凸性  
4. **区间求和**：对每个有效区间使用等差数列公式 `(首项+末项)*项数/2`

---

## 5. 算法可视化：像素动画演示

* **主题**："图论探险家：DP与凸包之旅"（8位像素风格）  
* **核心内容**：动态展示DP状态扩展 + 凸包构建过程  

**动画设计**：  
1. **场景布局**  
   - 左区：像素化图结构（顶点：彩色方块，边：发光线条）  
   - 右区：坐标系区域（动态绘制直线和凸包）  
   - 控制面板：步进/播放/调速滑块  

2. **DP阶段演示**  
   - 起点(1号顶点)高亮绿色，随步数增加向外扩散  
   - 当前处理的顶点闪烁黄色，更新的边显示红色  
   - 音效：移动时8-bit脚步声，状态更新时"滴"声  

3. **凸包构建阶段**  
   - 坐标系区域动态添加直线（不同颜色）  
   - 栈操作时显示交点计算过程（坐标值弹跳显示）  
   - 音效：直线入栈"咔嗒"声，弹出时"啵"声  

4. **游戏化元素**  
   - 每完成一个DP阶段解锁成就徽章  
   - 凸包构建成功时播放胜利音效 + 像素烟花特效  
   - 控制台显示实时得分（当前求和值）  

**交互设计**：  
- 单步执行：空格键逐步执行算法  
- 自动演示：速度滑块控制0.5x~5x速度  
- 视角切换：Tab键切换图结构/凸包视图  

---

## 6. 拓展练习与相似问题思考

* **技巧迁移**：凸包优化适用于：  
  1. 带距离费用的DP优化（如任务调度）  
  2. 时间-收益线性模型求最大值  
  3. 资源分配中的分段线性规划  

* **洛谷推荐**：  
  1. **P3195 [HNOI2008]玩具装箱**  
     → 巩固凸包优化在DP中的应用  
  2. **P3628 [APIO2010]特别行动队**  
     → 练习直线族最大值问题变形  
  3. **P2900 [USACO08MAR]Land Acquisition**  
     → 学习凸包在二维规划中的应用  

---

## 7. 学习心得与经验分享

> **来自tzc_wk的经验**："最初因爆int一直WA，赛后2分钟改为long long解决"  
>   
> **Kay点评**：数据范围是算法竞赛的经典陷阱！在涉及：  
> - 大数求和（q≤1e9）  
> - 权值累加（w≤1e3, m≤2000 → 最大约2e6）  
> 时务必使用long long。调试时输出中间变量范围是必备技能。

---

通过本次分析，我们掌握了动态规划与凸包优化的组合应用。记住：好算法=正确阶段划分+高效数据结构！下次挑战见！💪

---
处理用时：231.03秒