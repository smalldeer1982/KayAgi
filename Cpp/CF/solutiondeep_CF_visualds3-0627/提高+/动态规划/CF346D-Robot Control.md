# 题目信息

# Robot Control

## 题目描述

The boss of the Company of Robot is a cruel man. His motto is "Move forward Or Die!". And that is exactly what his company's product do. Look at the behavior of the company's robot when it is walking in the directed graph. This behavior has been called "Three Laws of Robotics":

- Law 1. The Robot will destroy itself when it visits a vertex of the graph which it has already visited.
- Law 2. The Robot will destroy itself when it has no way to go (that is when it reaches a vertex whose out-degree is zero).
- Law 3. The Robot will move randomly when it has multiple ways to move (that is when it reach a vertex whose out-degree is more than one). Of course, the robot can move only along the directed edges of the graph.

Can you imagine a robot behaving like that? That's why they are sold at a very low price, just for those who are short of money, including mzry1992, of course. mzry1992 has such a robot, and she wants to move it from vertex $ s $ to vertex $ t $ in a directed graph safely without self-destruction. Luckily, she can send her robot special orders at each vertex. A special order shows the robot which way to move, if it has multiple ways to move (to prevent random moving of the robot according to Law 3). When the robot reaches vertex $ t $ , mzry1992 takes it off the graph immediately. So you can see that, as long as there exists a path from $ s $ to $ t $ , she can always find a way to reach the goal (whatever the vertex $ t $ has the outdegree of zero or not).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF346D/70cbc1b898581d5fe7e403c459e5024fa4aa2e72.png) Sample 2 However, sending orders is expensive, so your task is to find the minimum number of orders mzry1992 needs to send in the worst case. Please note that mzry1992 can give orders to the robot while it is walking on the graph. Look at the first sample to clarify that part of the problem.

## 说明/提示

Consider the first test sample. Initially the robot is on vertex 1. So, on the first step the robot can go to vertex 2 or 3. No matter what vertex the robot chooses, mzry1992 must give an order to the robot. This order is to go to vertex 4. If mzry1992 doesn't give an order to the robot at vertex 2 or 3, the robot can choose the "bad" outgoing edge (return to vertex 1) according Law 3. So, the answer is one.

## 样例 #1

### 输入

```
4 6
1 2
2 1
1 3
3 1
2 4
3 4
1 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 5
1 2
2 1
1 3
2 4
3 4
1 4
```

### 输出

```
1
```

# AI分析结果



# 题目翻译

## 题目描述

机器人公司的老板是个残酷的人。他的座右铭是“前进或死亡！”。而这正是他的公司产品的行为方式。观察该公司机器人在有向图中的行走行为。这种行为被称为“机器人三定律”：

- **定律 1**：当机器人访问图中已访问过的顶点时，会自毁。
- **定律 2**：当机器人无路可走时（即到达出度为 0 的顶点），会自毁。
- **定律 3**：当机器人有多个移动方向时（即到达出度大于 1 的顶点），会随机移动。当然，机器人只能沿着有向边移动。

你能想象这样的机器人吗？这就是为什么它们售价低廉，专为囊中羞涩的人设计，当然也包括 mzry1992。mzry1992 希望将机器人从顶点 $s$ 安全移动到顶点 $t$ 而不自毁。她可以在每个顶点向机器人发送特殊指令，指定移动方向（当存在多个出边时）。当机器人到达顶点 $t$ 时，立即将其移出图。只要存在从 $s$ 到 $t$ 的路径，她总能找到方法实现目标。

请计算在最坏情况下需要发送的最小指令数。

## 输入输出样例

### 样例 #1

输入：
```
4 6
1 2
2 1
1 3
3 1
2 4
3 4
1 4
```
输出：
```
1
```

### 样例 #2

输入：
```
4 5
1 2
2 1
1 3
2 4
3 4
1 4
```
输出：
```
1
```

---

## 算法分类
**线性DP**

---

## 综合分析与结论

### 核心思路
1. **反向建图与动态规划**  
   从终点 $t$ 反向进行动态规划，定义 $dp[u]$ 为从 $u$ 到 $t$ 的最小指令数。状态转移分为两种情况：
   - **主动发令**：选择最优出边，代价为 $\min(dp[v] + 1)$
   - **被动随机**：最坏情况下选择最大代价出边，代价为 $\max(dp[v])$

2. **01-BFS 优化**  
   利用相邻状态差值不超过 1 的特性，使用双端队列维护节点处理顺序：
   - 当更新代价为 $0$ 时，节点插入队首
   - 当更新代价为 $1$ 时，节点插入队尾

3. **入度控制转移**  
   维护每个节点的剩余未处理出边数 $in[u]$，当 $in[u]=0$ 时允许被动随机转移

### 可视化设计
- **动态规划矩阵**：以网格展示每个节点的 $dp$ 值，当前处理节点高亮为黄色
- **边权着色**：红色箭头表示 $\max$ 转移（无指令），绿色箭头表示 $\min+1$ 转移（有指令）
- **双端队列动画**：队列元素按处理顺序流动，队首弹出时播放 "pop" 音效，插入时根据位置播放不同音调
- **像素风格**：使用 16 色调色板，节点绘制为 32x32 像素方块，边用虚线箭头表示

---

## 题解清单（4星及以上）

### 题解1：369Pai（⭐⭐⭐⭐⭐）
- **亮点**：清晰的状态转移方程，完整实现 01-BFS 优化
- **核心代码**：
  ```cpp
  while(!dq.empty()) {
    int u = dq.front(); dq.pop_front();
    if(vis[u]) continue;
    vis[u] = 1;
    for(int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].to;
      in[v]--;
      if(!in[v] && f[u] < f[v]) { // 被动转移
        f[v] = f[u];
        dq.push_front(v);
      } else if(in[v] && f[u]+1 < f[v]) { // 主动转移
        f[v] = f[u]+1;
        dq.push_back(v);
      }
    }
  }
  ```

### 题解2：yaoyuchen2021（⭐⭐⭐⭐）
- **亮点**：简洁的 01-BFS 实现，注释明确
- **关键注释**：  
  "当所有出边处理完毕时，取最大值不消耗指令"

### 题解3：yspm（⭐⭐⭐⭐）
- **亮点**：正向反向图分离处理，展示更通用的 DP 思路
- **核心代码**：
  ```cpp
  for(auto t:revG[fr]) if(dp[fr]+1<=dp[t]) {
    dp[t] = dp[fr]+1;
    if(!vis[t]) q.push(t), vis[t] = 1;
  }
  ```

---

## 核心代码实现
```cpp
const int N = 1e6 + 10;
vector<int> G[N], revG[N];
int in[N], dp[N], vis[N];

void solve(int s, int t) {
  deque<int> dq;
  memset(dp, 0x3f, sizeof(dp));
  dp[t] = 0;
  dq.push_back(t);
  
  while (!dq.empty()) {
    int u = dq.front(); dq.pop_front();
    if (vis[u]) continue;
    vis[u] = 1;
    
    for (int v : revG[u]) {
      if (--in[v] == 0 && dp[u] < dp[v]) { // 被动转移
        dp[v] = dp[u];
        dq.push_front(v);
      } else if (dp[u] + 1 < dp[v]) { // 主动转移
        dp[v] = dp[u] + 1; 
        dq.push_back(v);
      }
    }
  }
  
  cout << (dp[s] > 1e9 ? -1 : dp[s]);
}
```

---

## 相似题目推荐
1. [CF1005F Berland and the Shortest Paths](https://www.luogu.com.cn/problem/CF1005F)  
   **关键词**：最短路径树、边权分配

2. [P4568 [JLOI2011]飞行路线](https://www.luogu.com.cn/problem/P4568)  
   **关键词**：分层图最短路、多决策转移

3. [P1772 [ZJOI2006]物流运输](https://www.luogu.com.cn/problem/P1772)  
   **关键词**：动态规划与最短路结合

---

## 可视化动画设计

### 动画逻辑
1. **初始化阶段**：
   - 绘制反向图结构，终点 $t$ 显示为绿色，起点 $s$ 为红色
   - DP 矩阵初始化为无穷大，$dp[t]=0$ 显示为金色

2. **处理节点**：
   ```javascript
   function animateStep() {
     let u = deque.shift();
     highlightNode(u, YELLOW); // 高亮当前节点
     for (let v of reverseEdges[u]) {
       inDegree[v]--;
       if (inDegree[v] === 0 && dp[u] < dp[v]) {
         dp[v] = dp[u]; 
         playSound('zero'); // 无消耗音效
         deque.unshift(v);  // 插入队首
       } else if (dp[u]+1 < dp[v]) {
         dp[v] = dp[u]+1;
         playSound('one');  // 消耗指令音效 
         deque.push(v);     // 插入队尾
       }
       updateGrid(v, dp[v]); // 更新矩阵显示
     }
   }
   ```

3. **像素风格**：
   - 使用 `Canvas` 绘制 8-bit 风格的节点和边
   - 节点尺寸 32x32 像素，边为 2px 虚线

4. **音效设计**：
   - `zero.wav`: 清脆的 "叮" 声（无消耗转移）
   - `one.wav`: 沉闷的 "咚" 声（指令消耗）
   - `bgm.ogg`: 8-bit 风格循环背景音乐

---

## 总结
本题通过反向图上的动态规划，结合 01-BFS 的队列优化，将看似复杂的指令最小化问题转化为经典的图论问题。关键点在于理解两种转移方式对应的最坏情况处理，以及入度控制如何保证转移顺序的正确性。可视化设计通过像素风格和音效反馈，将抽象的 DP 过程具象化为可交互的动画体验。

---
处理用时：103.93秒