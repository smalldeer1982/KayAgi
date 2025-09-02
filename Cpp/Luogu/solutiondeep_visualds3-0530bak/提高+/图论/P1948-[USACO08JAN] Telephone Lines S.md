# 题目信息

# [USACO08JAN] Telephone Lines S

## 题目描述

Farmer John wants to set up a telephone line at his farm. Unfortunately, the phone company is uncooperative, so he needs to pay for some of the cables required to connect his farm to the phone system.

There are N (1 ≤ N ≤ 1,000) forlorn telephone poles conveniently numbered 1..N that are scattered around Farmer John's property; no cables connect any them. A total of P (1 ≤ P ≤ 10,000) pairs of poles can be connected by a cable; the rest are too far apart.

The i-th cable can connect the two distinct poles Ai and Bi, with length Li (1 ≤ Li ≤ 1,000,000) units if used. The input data set never names any {Ai, Bi} pair more than once. Pole 1 is already connected to the phone system, and pole N is at the farm. Poles 1 and N need to be connected by a path of cables; the rest of the poles might be used or might not be used.

As it turns out, the phone company is willing to provide Farmer John with K (0 ≤ K < N) lengths of cable for free. Beyond that he will have to pay a price equal to the length of the longest remaining cable he requires (each pair of poles is connected with a separate cable), or 0 if he does not need any additional cables.

Determine the minimum amount that Farmer John must pay.

多年以后，笨笨长大了，成为了电话线布置师。由于地震使得某市的电话线全部损坏，笨笨是负责接到震中市的负责人。该市周围分布着 $1\le N\le1000$ 根据 $1\cdots N$ 顺序编号的废弃的电话线杆，任意两根线杆之间没有电话线连接，一共有 $1\le p\le10000$ 对电话杆可以拉电话线。其他的由于地震使得无法连接。

第i对电线杆的两个端点分别是 $a_i$ ，$b_i$，它们的距离为 $1\le l_i\le1000000$。数据中每对 $(a_i,b_i)$ 只出现一次。编号为 $1$ 的电话杆已经接入了全国的电话网络，整个市的电话线全都连到了编号 $N$ 的电话线杆上。也就是说，笨笨的任务仅仅是找一条将 $1$ 号和 $N$ 号电线杆连起来的路径，其余的电话杆并不一定要连入电话网络。

电信公司决定支援灾区免费为此市连接 $k$ 对由笨笨指定的电话线杆，对于此外的那些电话线，需要为它们付费，总费用决定于其中最长的电话线的长度（每根电话线仅连接一对电话线杆）。如果需要连接的电话线杆不超过 $k$ 对，那么支出为 $0$。

请你计算一下，将电话线引导震中市最少需要在电话线上花多少钱？


## 样例 #1

### 输入

```
5 7 1
1 2 5
3 1 4
2 4 8
3 2 3
5 2 9
3 4 7
4 5 6
```

### 输出

```
4
```

# AI分析结果



### 唯一算法分类
二分答案 + 最短路（双端队列 BFS）

---

### 题解核心思路与难点分析

#### 核心算法流程：
1. **二分答案**：在 [0, 1e6] 范围内二分最大花费 mid
2. **权值转换**：将边权 > mid 的视为 1（需使用免费次数），≤ mid 的视为 0
3. **双端队列 BFS**：处理 0-1 权值的最短路问题，0 边插入队首，1 边插入队尾
4. **可行性判断**：若终点距离 ≤ K 则说明 mid 可行

#### 解决难点：
- **正确性证明**：第 K+1 大的边权决定最终花费，通过二分确保免费覆盖前 K 大边
- **高效验证**：双端队列 BFS 处理 0-1 图的时间复杂度为 O(N+P)，显著优于普通 SPFA
- **无解处理**：初始左边界设为 -1 兼容无法连通的情况

---

### 题解评分（≥4星）

1. **Blair3863（5星）**
   - 关键亮点：双端队列 BFS 实现极简且高效
   - 代码亮点：用 `deque` 天然实现 0-1 权值分层处理
   ```cpp
   deque<int> q;
   if(edge <= x) q.push_front(y);  // 0 边插队首
   else q.push_back(y);            // 1 边插队尾
   ```

2. **浅色调（4星）**
   - 关键亮点：最经典的二分+SPFA 实现
   - 代码亮点：权值转换逻辑清晰易懂
   ```cpp
   if(e[i].v > x) s = dis[now] + 1;  // 权值转换
   else s = dis[now];
   ```

3. **hf_xz（4星）**
   - 关键亮点：动态规划状态转移思路
   - 代码亮点：`dis[v][k]` 表示到节点 v 使用 k 次免费的最小花费
   ```cpp
   dis[v][k] = min(max(dis[u][k], w), dis[u][k-1])
   ```

---

### 最优思路提炼
**双端队列 BFS + 二分答案**
- **权值分层**：将问题转化为 0-1 权值图的最短路径问题
- **队列优化**：0 边插队首保证优先处理，天然维护路径单调性
- **边界处理**：初始 l=-1 兼容无解情况，r=1e6 覆盖最大边权

---

### 同类型题与算法套路
1. **P2939 [USACO09FEB]Revamping Trails**：分层图最短路模板
2. **P4568 [JLOI2011]飞行路线**：免费次数限制的最短路
3. **P1186 玛丽卡**：删边最短路变种，需类似二分思想

---

### 个人心得摘录
> "双端队列 BFS 处理 0-1 图时，就像贪吃蛇优先吃近处的食物，遇到障碍才绕远路" —— Blair3863 题解形象比喻队列插入策略  
> "初始 l=-1 的设定让我少交 3 次 WA，无解判断必须严谨" —— _LPF_ 调试经验

---

### 可视化算法演示设计
**复古像素风格演示（HTML/JS 伪代码）**
```javascript
// Canvas 初始化
const grid = new PixelGrid(16, 16); // 16x16 像素网格
grid.drawNode(1, {color: '#00FF00'}); // 起点绿色
grid.drawNode(n, {color: '#FF0000'}); // 终点红色

// 双端队列动画
function animateBFS(mid) {
  let q = new Deque([1]);
  while (!q.empty()) {
    const u = q.popFront();
    grid.highlight(u, '#FFFF00'); // 当前节点黄色高亮
    playSound('step.wav');        // 步进音效
    for (const [v, w] of edges[u]) {
      const cost = w > mid ? 1 : 0;
      if (updateDistance(v, cost)) {
        if (cost === 0) q.pushFront(v); 
        else q.pushBack(v);
        grid.drawEdge(u, v, cost ? '#FF00FF' : '#00FFFF'); // 边权颜色区分
      }
    }
  }
}
```

**交互功能**  
- **速度滑块**：调节动画帧率（10ms~1000ms/步）
- **自动/手动模式**：空格键暂停/继续，→ 键单步执行
- **音效触发**：找到路径时播放 8-bit 胜利音效，无解时播放低沉错误音

---

### 核心代码实现（Blair3863 题解）
```cpp
bool check(int x) {
  deque<int> q;
  memset(dis, 0x3f, sizeof(dis));
  dis[1] = 0; q.push_back(1);
  while (!q.empty()) {
    int u = q.front(); q.pop_front();
    for (int i = head[u]; i; i = e[i].next) {
      int v = e[i].to, w = e[i].w > x ? 1 : 0;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        if (w == 0) q.push_front(v); // 0 边插队首
        else q.push_back(v);         // 1 边插队尾
      }
    }
  }
  return dis[n] <= k;
}
```

---
处理用时：79.75秒