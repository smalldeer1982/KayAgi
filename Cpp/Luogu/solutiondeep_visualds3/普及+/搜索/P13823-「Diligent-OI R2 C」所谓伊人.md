# 题目信息

# 「Diligent-OI R2 C」所谓伊人

## 题目背景

> 溯洄从之，道阻且长。溯游从之，宛在水中央。——《诗经·秦风·蒹葭》

## 题目描述

给定一张 $n$ 个点，$m$ 条边的有向图，点从 $1\sim n$ 编号。图中每个点 $i$ 有点权 $p_i$。注意可能有重边自环。

如果点 $u$ 出发存在路径到达点 $v$，则你可以将 $u,v$ 的点权交换。

对于每个点 $i$，输出使 $i$ 点权最大化的最少交换次数。**请注意，每个回答是独立的，即都应该从初始给定的图开始交换。**

## 说明/提示

#### 样例 #1 解释

可以证明，$6$ 个点的点权的最大可能值分别为 $1,1,5,5,5,4$。

使 $1$ 号点点权最大化的方案：不交换。

使 $2$ 号点点权最大化的方案：不交换。

使 $3$ 号点点权最大化的方案：交换 $3$ 号和 $4$ 号点的点权。

使 $4$ 号点点权最大化的方案：不交换。

使 $5$ 号点点权最大化的方案：交换 $4$ 号和 $5$ 号点的点权。

使 $6$ 号点点权最大化的方案：不交换。

#### 数据范围

对于所有数据，保证 $1\le n,m\le 5\times10^5,1\le p_i\le10^9,1\le u,v\le n$。注意可能有重边自环。

- Subtask 1（5pts）：$n,m\le3$。
- Subtask 2（25pts）：$n,m\le10^3$。
- Subtask 3（8pts）：图为一条链。即对于所有 $i=1,2,\dots,n-1$，$i$ 与 $i+1$ 之间有且仅有一条有向边，但方向不确定。
- Subtask 4（12pts）：图为一棵树。即 $m=n-1$，且图将有向边改成无向边后连通。
- Subtask 5（20pts）：$n,m\le5\times10^4$，且图随机生成。随机生成方式见下。
- Subtask 6（10pts）：$n,m\le10^5$。
- Subtask 7（20pts）：$n,m\le5\times10^5$。

Subtask 5 的随机生成方式：

- 先确定 $n,m$ 和序列 $p$（不一定随机）。
- 然后对于 $m$ 条边，每条边的 $u,v$ 都在 $1\sim n$ 的整数中均匀随机取。

**请注意，此题需要较快的输入输出方式，并且在实现过程中，请注意常数对程序效率的影响。**

## 样例 #1

### 输入

```
6 5
1 1 4 5 1 4
1 2
2 1
3 4
4 5
3 5```

### 输出

```
0 0 1 0 1 0```

# AI分析结果


# 💡 Kay的C++算法解析：「所谓伊人」深入学习指南 💡

> "溯洄从之，道阻且长" —— 这道题就像追寻伊人的旅程，需要巧妙设计路径才能达成目标。让我们拆解这道图论难题！

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`图论建模与拆点技巧` + `01BFS最短路径`

🗣️ **初步分析**：
> 想象你在一个由房间和通道组成的城堡里，每个房间有不同价值的宝物（点权）。通道是单向的（有向边），而你可以和能到达的房间交换宝物。目标是用最少交换次数让每个房间获得它能得到的最大宝物。

- **核心思路**：将交换操作转化为状态转移问题。每个点拆成4种状态（A1/A2/B1/B2），代表不同"进出方式"。交换0次或1次对应不同状态转移
- **关键难点**：如何将抽象交换转化为可计算路径？通过拆点建模状态机，01权值边完美对应交换代价
- **可视化设计**：用8位像素城堡表示图，房间拆成4色方块（红/黄/蓝/绿）。宝物移动时播放"叮"音效，消耗交换次数时屏幕震动+闪光。自动演示模式像解谜游戏，AI小人按最优路径移动宝物

---

## 2. 精选优质题解参考

<eval_intro>
题解作者使用创新拆点法将问题转化为01BFS，思路清晰完整，代码规范高效，获得5星评价。
</eval_intro>

**题解 (来源：Night_sea_64)**
* **点评**：这份题解亮点在于**将抽象交换操作转化为精确的状态机模型**：
  - **思路**：独创性拆点方案（每点分4状态）完美建模交换代价，无向连通块预处理极大值点确保算法正确性
  - **代码**：变量命名规范（`d[]`表距离，`a[]`存点权），双端队列01BFS实现高效（O(n+m)复杂度）
  - **算法**：01BFS替代Dijkstra优化常数，DFS预处理连通块极大值点提升效率
  - **实践**：完整处理5e5数据规模，边界条件严谨（如`d[v]!=0`的重复访问判断）

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破三大关键难点，以下是结合题解提炼的策略：
</difficulty_intro>

1.  **难点1：交换操作的状态建模**
    * **分析**：交换的本质是**路径可访问性+代价计算**。优质题解通过拆解为4种状态（A1/A2/B1/B2），用0/1权值区分自由移动与交换操作
    * 💡 **学习笔记**：复杂操作可转化为状态机，用图论边权模拟代价

2.  **难点2：极大值点的分布式处理**
    * **分析**：每个连通块可能有多个极大值点。DFS预处理标记`b[]`数组，01BFS时**多点同时作为起点**，确保找到全局最优解
    * 💡 **学习笔记**：多源BFS是处理分布式起点的利器

3.  **难点3：01边权的高效处理**
    * **分析**：双端队列维护BFS队列（0权插队首，1权插队尾），避免Dijkstra的log开销。这是**稀疏图最短路的常数优化关键**
    * 💡 **学习笔记**：01BFS在特定场景下效率优于Dijkstra

### ✨ 解题技巧总结
<summary_best_practices>
通关秘籍：
</summary_best_practices>
- **拆点建模法**：当操作具有多状态特性时（如进出方向），通过增加维度（拆点）转化为图论问题
- **多源BFS优化**：多个等效起点时同时入队，避免重复计算
- **01BFS双端队列**：用`deque`实现0/1边权的最短路，时间复杂度O(n+m)
- **预处理剪枝**：DFS预先标记极大值点（`b[]`数组），减少无效计算

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是完整核心实现，融合拆点与01BFS的精髓：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：基于作者题解优化可读性，保留算法核心
* **完整核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5, M=2e6+5; // 扩大边数限制

// 图存储结构
struct Graph {
    int cnt, head[4*N], nxt[4*M], to[4*M], w[4*M];
    void add(int u, int v, int weight) {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
        w[cnt] = weight;
    }
} g; // 拆点后的图

int n, m, maxVal[N], isMax[N]; // 连通块最大值 & 标记
int dist[4*N];                 // 01BFS距离数组
vector<int> orig[N];           // 原图（无向）

// DFS求连通块最大值
void dfs(int u, int& curMax) {
    if(isMax[u] != -1) return;
    isMax[u] = 0; // 初始化非最大值
    curMax = max(curMax, val[u]);
    for(int v : orig[u]) 
        dfs(v, curMax);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    vector<int> val(n+1);
    for(int i=1; i<=n; i++) cin >> val[i];
    
    // 拆点：每个点分4状态
    for(int i=1; i<=n; i++) {
        int base = 4*i;
        g.add(base+1, base+3, 0); // A1→B1
        g.add(base+2, base+4, 0); // A2→B2
        g.add(base+1, base+4, 1); // A1→B2 (消耗1次)
        g.add(base+2, base+3, 1); // A2→B1 (消耗1次)
    }
    
    // 建图
    while(m--) {
        int u, v; cin >> u >> v;
        g.add(4*u+3, 4*v+1, 0); // uB1→vA1
        g.add(4*v+4, 4*u+2, 0); // vB2→uA2
        orig[u].push_back(v);    // 无向图连通块
        orig[v].push_back(u);
    }
    
    // 预处理连通块最大值
    memset(isMax, -1, sizeof(isMax));
    for(int i=1; i<=n; i++) {
        if(isMax[i] != -1) continue;
        int curMax = 0;
        dfs(i, curMax); // 求连通块最大值
        
        // 标记极大值点
        for(int j=i; j<=n; j++) 
            if(isMax[j] != -1 && val[j] == curMax) 
                isMax[j] = 1;
    }
    
    // 01BFS初始化
    memset(dist, -1, sizeof(dist));
    deque<int> q;
    for(int i=1; i<=n; i++) {
        if(!isMax[i]) continue;
        int base = 4*i;
        dist[base+1] = 0; q.push_back(base+1);
        dist[base+2] = 0; q.push_back(base+2);
    }
    
    // 01BFS核心
    while(!q.empty()) {
        int u = q.front(); q.pop_front();
        for(int i=g.head[u]; i; i=g.nxt[i]) {
            int v = g.to[i], w = g.w[i];
            if(dist[v] != -1) continue; // 已访问
            dist[v] = dist[u] + w;
            w ? q.push_back(v) : q.push_front(v);
        }
    }
    
    // 输出答案
    for(int i=1; i<=n; i++) {
        if(isMax[i]) cout << "0 ";
        else {
            int base = 4*i;
            int ans = min(dist[base+3], dist[base+4]);
            cout << (ans == -1 ? 0 : ans) << ' ';
        }
    }
}
```
* **代码解读概要**：
  > 1. **拆点建图**：每个点创建4个状态节点，内部转移边权0/1  
  > 2. **预处理**：DFS求无向连通块的最大值点（`isMax[]`标记）  
  > 3. **多源01BFS**：从所有极大值点状态出发，双端队列优化最短路  
  > 4. **答案生成**：对每个点取两个终止状态（B1/B2）的最小距离  

---
<code_intro_selected>
关键代码片段深度解析：
</code_intro_selected>

**拆点建模（核心创新）**
* **亮点**：将物理交换转化为状态转移机
* **核心代码片段**：
```cpp
for(int i=1; i<=n; i++) {
    int base = 4*i;
    g.add(base+1, base+3, 0); // A1→B1 (0代价)
    g.add(base+2, base+4, 0); // A2→B2 (0代价)
    g.add(base+1, base+4, 1); // A1→B2 (消耗1次)
    g.add(base+2, base+3, 1); // A2→B1 (消耗1次)
}
```
* **代码解读**：
  > 每个点拆成4个状态：  
  > - `A1/A2`：进入状态（类似"入口闸机"）  
  > - `B1/B2`：离开状态（类似"出口闸机"）  
  > 关键设计：**同向转移（A1→B1）零代价**，**交叉转移（A1→B2）消耗1次交换**  
  > 为什么这样设计？因为同进同出无需交换，改变进出方向需1次操作！

**01BFS队列优化（性能关键）**
* **亮点**：双端队列实现O(n+m)最短路
* **核心代码片段**：
```cpp
while(!q.empty()) {
    int u = q.front(); q.pop_front();
    for(int i=g.head[u]; i; i=g.nxt[i]) {
        int v = g.to[i], w = g.w[i];
        if(dist[v] != -1) continue;
        dist[v] = dist[u] + w;
        w ? q.push_back(v) : q.push_front(v); // 核心优化
    }
}
```
* **代码解读**：
  > 为什么用双端队列？  
  > - 当边权w=0时：新状态距离不变，**插队首**优先处理（类似紧急通道）  
  > - 当边权w=1时：新状态距离+1，**插队尾**按序处理  
  > 这样保证队列前端始终是当前最短路径，无需优先队列的log开销！

---

## 5. 算法可视化：像素动画演示

<visualization_intro>
下面设计一个8位像素风格的"宝物交换城堡"演示，帮你直观理解拆点与01BFS！  
（设想：FC《塞尔达传说》画风 + 《吃豆人》音效）
</visualization_intro>

* **主题**："像素勇者收集极品宝物"
* **核心演示**：拆点状态转移 + 01BFS寻宝路径
* **设计思路**：用不同颜色方块区分状态（红A1/黄A2/蓝B1/绿B2），宝物移动轨迹展示交换代价，音效强化状态转移感知

### 动画帧步骤（伪代码实现）
```javascript
// 初始化：8位像素城堡
const castle = new PixelCanvas(16*4, 16*n); // 每点4列，n行
castle.drawGrid(); // 绘制网格房间

// 状态着色规则
const stateColors = {A1: '#FF5555', A2: '#FFFF33', B1: '#5555FF', B2: '#55FF55'};

// 01BFS演示主循环
function autoPlay() {
  while (q.length) {
    const u = dequeue(); // 按01规则出队
    castle.highlightCell(u, GOLD_GLOW); // 金色高亮当前状态
    playSound('select.wav'); // 选择音效
    
    for (const edge of g[u]) {
      const [v, w] = edge;
      castle.drawArrow(u, v, w ? RED : GREEN); // 红边=代价1，绿边=0
      
      if (dist[v] === INF) {
        dist[v] = dist[u] + w;
        w ? enqueueBack(v) : enqueueFront(v); // 双端队列操作
        castle.highlightCell(v, BLUE_GLOW); // 新状态蓝色闪烁
        playSound(w ? 'swap.wav' : 'move.wav'); // 交换/移动音效
      }
    }
    castle.fadeCell(u); // 当前状态褪色
    delay(speedSlider.value); // 用户调速
  }
  castle.celebrate(); // 宝物到终点放烟花
  playSound('victory.mid'); // 8位机胜利音乐
}
```

### 关键交互设计
1. **控制面板**（复古FC风格）：
   - 速度滑块：调节动画速度
   - 单步执行：手动按方向键前进
   - 视角切换：整体城堡观 vs 单点状态机

2. **动态效果**：
   - 宝物移动：当状态转移时，宝物像素块滑动到新位置
   - 代价提示：消耗交换时红色闪光 + "💥"特效
   - 路径追踪：已访问状态渐变半透明，当前路径亮黄色

3. **游戏化元素**：
   - 宝物收集：每完成一个点权最大化，宝物栏+1
   - 交换计数器：屏幕顶部显示当前交换次数
   - 关卡设计：不同测试数据作为不同难度关卡

<visualization_conclusion>
通过像素动画，你将清晰看到：  
1) 拆点如何将抽象交换转化为可视状态转移  
2) 01BFS如何优先处理零代价路径  
3) 宝物如何通过最优路径到达极大值点
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握拆点技巧后，可解决更多图论状态转移问题：
</similar_problems_intro>

* **技巧迁移**：
  - 状态依赖型最短路（如：不同移动方式代价不同）
  - 图上游走问题（如：需记录最后几步状态）
  - 双属性决策问题（如：同时考虑时间和花费）

* **洛谷推荐**：
  1. **P1073 [NOIP2009]最优贸易**  
     🗣️ *拆点应用*：将每个点拆成"买入/卖出"状态，求最大差价路径
  2. **P4568 [JLOI2011]飞行路线**  
     🗣️ *状态分层*：通过拆点记录剩余免费次数，01BFS优化
  3. **P1522 [USACO]牛的旅行**  
     🗣️ *双属性处理*：拆点管理连通块极大值+最短路

---

## 7. 学习心得与经验分享

<insights_intro>
题解虽未提供调试心得，但根据算法特性总结经验：
</insights_intro>

> **经验提炼**：  
> 1. **拆点维度选择**：本题根据进出方向拆点，其他问题可能需按剩余步数/携带物品状态拆点  
> 2. **01BFS易错点**：双端队列插入顺序必须严格保证（0权前插，1权后插）  
> 3. **预处理优化**：连通块极大值预处理避免BFS中重复判断  

---

<conclusion>
通过拆点魔法将抽象交换转化为可视状态机，再以01BFS利剑斩开最优路径！记住：图论难题的核心在于**状态建模**。下次遇到复杂操作规则时，不妨尝试拆点转化法。继续挑战吧，少年！🎮  
</conclusion>
```

---
处理用时：253.30秒