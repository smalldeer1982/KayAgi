# 题目信息

# Rendez-vous de Marian et Robin

## 题目描述

In the humble act of meeting, joy doth unfold like a flower in bloom.



Absence makes the heart grow fonder. Marian sold her last ware at the Market at the same time Robin finished training at the Major Oak. They couldn't wait to meet, so they both start without delay.

The travel network is represented as $ n $ vertices numbered from $ 1 $ to $ n $ and $ m $ edges. The $ i $ -th edge connects vertices $ u_i $ and $ v_i $ , and takes $ w_i $ seconds to travel (all $ w_i $ are even). Marian starts at vertex $ 1 $ (Market) and Robin starts at vertex $ n $ (Major Oak).

In addition, $ h $ of the $ n $ vertices each has a single horse available. Both Marian and Robin are capable riders, and could mount horses in no time (i.e. in $ 0 $ seconds). Travel times are halved when riding. Once mounted, a horse lasts the remainder of the travel. Meeting must take place on a vertex (i.e. not on an edge). Either could choose to wait on any vertex.

Output the earliest time Robin and Marian can meet. If vertices $ 1 $ and $ n $ are disconnected, output $ -1 $ as the meeting is cancelled.

## 说明/提示

In the first test case, Marian rides from vertex $ 1 $ to vertex $ 2 $ , Robin waits.

In the second test case, vertices $ 1 $ and $ 3 $ are not connected.

In the third test case, both Marian and Robin travel to vertex $ 2 $ to meet.

In the fourth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides to vertex $ 3 $ to meet Robin.

In the fifth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides back to vertex $ 1 $ and then to vertex $ 3 $ . Robin waits.

## 样例 #1

### 输入

```
6
2 1 1
1
1 2 10
3 1 2
2 3
1 2 10
3 3 1
2
1 2 4
1 3 10
2 3 6
4 3 2
2 3
1 2 10
2 3 18
3 4 16
3 2 1
2
1 2 4
1 3 16
7 7 1
3
1 5 2
2 6 12
1 2 12
6 4 8
7 3 4
6 3 4
7 6 4```

### 输出

```
5
-1
6
19
14
12```

# AI分析结果



# Rendez-vous de Marian et Robin 题解分析

## 唯一算法分类
分层图最短路

---

## 综合分析与结论

### 核心思路
将每个顶点拆分为两个状态：未骑马（第一层）和已骑马（第二层）。有马的顶点在第一层到第二层之间建立 0 权边，第二层图中的边权为原值的一半。分别从起点（1号节点）和终点（n号节点）跑两次 Dijkstra，最后枚举所有顶点在两层中的四种组合情况，取最大时间的最小值。

### 解决难点
1. **状态转移建模**：用分层图表示是否骑过马的状态切换，有马节点通过 0 权边连接两层。
2. **边权动态变化**：第二层所有边权自动减半，无需单独记录骑马状态。
3. **时间计算**：两人可能在骑马或未骑马状态下相遇，需同时考虑四种组合。

### 可视化设计
1. **动画方案**：
   - 用双层网格表示分层图，下层为普通状态，上层为骑马状态。
   - 红色箭头表示普通边（原权值），绿色箭头表示骑马边（半权值）。
   - 当访问有马节点时，高亮黄色并绘制向上箭头表示状态切换。
2. **交互功能**：
   - 步进按钮控制 Dijkstra 的每一步松弛操作。
   - 速度滑块调节动画速度，支持暂停/继续。
3. **像素风格**：
   - 节点用 16x16 像素方块表示，普通状态为蓝色，骑马状态为金色。
   - 边权变化时播放 8-bit 音效（普通移动：短促「滴」声，骑马移动：连续「哒哒」声）。

---

## 题解评分（≥4星）

### thh_loser（4.5星）
- **亮点**：代码结构清晰，使用邻接表高效存储图结构，注释明确。
- **核心代码**：
  ```cpp
  add(x, x+n, 0); // 骑马状态转移边
  add(u+n, v+n, z/2); // 第二层减半边权
  ```

### WRT_Partisan（4星）
- **亮点**：使用 vector 存储邻接表，变量命名规范，多测数据清空彻底。
- **核心代码**：
  ```cpp
  mp[a[i]].push_back({a[i] + n, 0}); // 骑马点连接两层
  ans = min(ans, max(min(dis1[i], dis1[i+n]), min(disn[i], disn[i+n])));
  ```

### zengziqvan（4星）
- **亮点**：提醒 long long 陷阱，代码包含调试教训，适合新手学习。
- **关键片段**：
  ```cpp
  if(hr)w>>=1; // 骑马状态边权减半
  ans = min(ans, max(dis1[i][0], dis2[i][0]));
  ```

---

## 最优思路提炼

### 关键技巧
1. **分层图建模**：用两层图区分骑马状态，通过 0 权边实现状态切换。
2. **对称处理双源**：分别从起点和终点计算最短路，避免单源局限性。
3. **状态组合枚举**：对每个顶点计算两人四种状态组合的最小最大值。

### 代码实现
```cpp
// 分层图构建核心逻辑
for (有马节点x) add_edge(x, x + n, 0);
for (原边u-v权值w) {
    add_edge(u, v, w);      // 第一层普通边
    add_edge(u+n, v+n, w/2);// 第二层减半边
}

// 结果计算逻辑
ll ans = INF;
for (int i=1; i<=n; ++i) {
    ll marian = min(dis1[i], dis1[i+n]); // 起点到i的最短时间
    ll robin = min(dis2[i], dis2[i+n]);  // 终点到i的最短时间
    ans = min(ans, max(marian, robin));
}
```

---

## 同类题目推荐
1. **P4568 [JLOI2011]飞行路线**（分层图+免费次数）
2. **P1948 [USACO08JAN]电话线**（最短路+二分答案）
3. **P1266 速度限制**（动态边权最短路）

---

## 可视化演示设计
1. **Canvas 绘制**：
   - 节点用不同颜色区分状态（蓝：未骑马，金：已骑马）。
   - 边权实时显示，减半边用绿色标注。
2. **音效系统**：
   - `move_sound()`：普通移动时播放。
   - `horse_sound()`：骑马状态切换时触发。
3. **自动演示模式**：
   - 模拟 Dijkstra 算法过程，优先队列自动弹出最小节点。
   - 遇到最优解时角色头顶显示✨，播放胜利音效。

---

## 个人心得摘录
- **thh_loser**：注意多测清空图的存储结构，否则会导致 WA。
- **zengziqvan**：开 long long！所有涉及时间的变量必须用 64 位整数。
- **conti123**：分层图本质是状态机，用二维 dis 数组比物理拆点更省内存。

---
处理用时：70.97秒