# 题目信息

# [USACO13OPEN] What's Up With Gravity S

## 题目描述

Captain Bovidian is on an adventure to rescue her crew member, Doctor Beefalo.  Like all great adventures, this story plays out in a two dimensional N by M grid (1 <= N, M <= 500), representing a side view of the captain's world.  Some grid cells are empty while others are blocked and cannot be traversed.

Unfortunately, Captain Bovidian cannot jump.  She must obey the following rules of physics while traversing her world.

1) If there is no cell directly underneath Captain Bovidian (that is, if she is at the edge of the grid), then she flies out into space and fails her mission.

2) If the cell directly underneath Captain Bovidian is empty, then she falls into that cell.

3) Otherwise:

a) Captain Bovidian may move left or right if the corresponding cell exists and is empty.

b) Or, Captain Bovidian may flip the direction of gravity.

When Captain Bovidian changes the direction of gravity, the cell that's 'underneath' her (as mentioned in rules 1 and 2) toggles between the cell with one higher row index and the cell with one lower row index (the first row in the input has index 1, and the last row has index N). Initially, the cells with one higher row index are underneath Captain Bovidian.

Doctor Beefalo is lost somewhere in this world.  Help Captain Bovidian arrive at her cell using the least number of gravity flips as possible.  If it is impossible to reach Doctor Beefalo, please output -1.


Bovidian 船长正在拯救她的船员，Beefalo 博士。

和所有伟大的冒险故事一样，这个故事也是发生在一个2D平面上的。囧

这个平面是M\*N的格子组成的网格，代表着船长的世界的一个侧视图。

有些格子是空的，另一些则是实心的，并且不能直接通过。

很不幸的是，船长跳不起来。她必须遵守这个世界的特殊物理法则。

1）如果船长的正下方没有方块（换句话说，即使她正在网格的边缘），那么她就会掉入宇宙中，同时意味着冒险失败。

2）如果船长的正下方的方块是空的，那么她就会掉到这个方块，

3）在不满足1）与2）的情况下，船长可以做一下的事情：

a) 如果左边(或右边）的方格是空的，那么她可以走到那个格子。

b船长可以翻转重力的方向

当船长改变翻转重力的方向时，我们就改变船长”下方“的定义。

”下方“的定义只能是两种

(A)比船长位置所在的方格的列编号更大的格子，

(B)比船长位置所在的方格的列编号更小的格子,

一开始的时候，“下方”的定义是比船长位置所在方格的列编号更大的格子。

Beefalo博士正迷失在这个世界中的某一处，请帮助船长从起点到达博士的地方。

如果可以到达，请输出最少需要的翻转重力的次数。


如果不可以到达，请输出-1


## 说明/提示

输出解释：

首先，船长在（4,2），接着她翻转重力，到达（2,2）

接着她向右走走到（2,4），接着她第二次翻转重力，到达（4,4）

然后她继续向右走到（4,5），最后在翻转一次重力，到达博士所在的（3,5）


## 样例 #1

### 输入

```
5 5
#####
#...#
#...D
#C...
##.##```

### 输出

```
3```

# AI分析结果



**唯一算法分类**  
BFS  

---

### **题解思路与难点分析**  
1. **核心思路**：将重力状态（上/下）作为分层图的两个维度，每个节点包含坐标+重力方向。BFS优先处理翻转次数少的路径，确保最短解。  
2. **算法要点**：  
   - **状态管理**：每个状态包含坐标 `(x,y)` 和重力方向 `g`，用 `vis[x][y][g]` 判重。  
   - **状态转移**：  
     - 若脚下无支撑，持续下落直到触地。  
     - 左右移动时权值为0，翻转重力权值为1。  
   - **优化手段**：双端队列（`deque`）优先处理同层状态，保证队列单调性。  
3. **解决难点**：  
   - **重力切换逻辑**：翻转后需重新计算下落路径。  
   - **队列单调性**：通过双端队列确保0权重的移动操作优先处理。  

---

### **题解评分 (≥4星)**  
1. **Adove (4星)**  
   - 分层图+SPFA，代码结构清晰，但SPFA在大数据下效率不稳定。  
   - 关键亮点：将重力状态转化为分层图的边权处理。  
2. **曹老师 (4星)**  
   - BFS直接管理状态，逻辑直观但存在冗余判断。  
   - 关键亮点：通过 `upd` 函数统一处理状态转移。  
3. **jiang_cheng (5星)**  
   - 双端队列优化BFS，高效处理不同权重操作。  
   - 关键亮点：通过双队列分离同层与下层状态，代码简洁高效。  

---

### **最优思路提炼**  
**双端队列BFS**：  
- 将重力翻转（权1）加入队尾，移动操作（权0）加入队首。  
- 优先扩展权值0的操作，确保最先找到最小翻转次数路径。  

---

### **同类型题与算法套路**  
1. **迷宫最短路径变种**：需处理动态状态（如重力、钥匙等）。  
2. **分层图BFS**：如P1948 [Telephone Lines]（权值分层）、P4568 [飞行路线]（分层图最短路）。  

---

### **推荐题目**  
1. **P1141** 01迷宫（BFS状态扩展）  
2. **P1825** 玉米田迷宫（状态+传送门处理）  
3. **P3958** 奶酪（三维BFS）  

---

### **个人心得摘录**  
- **jiang_cheng**：双队列分离同层状态，避免混合处理导致错误。  
- **曹老师**：理解题目物理规则是关键，需反复验证状态转移逻辑。  
- **Adove**：分层图需注意图的构建细节，尤其是边权的设置。  

---

### **可视化与算法演示**  
**动画方案**：  
1. **网格绘制**：Canvas绘制网格，红色块表示障碍，绿色块为目标，蓝色块为当前节点。  
2. **状态标记**：  
   - 重力向下：节点显示为▼；重力向上：显示为▲。  
   - 已访问节点颜色变灰，队列中节点高亮。  
3. **双端队列操作**：  
   - 移动操作插入左侧（黄色箭头），翻转操作插入右侧（红色闪电图标）。  
4. **音效提示**：  
   - 移动时播放“滴”声，翻转时播放“咔嚓”声，找到目标时播放胜利音效。  
5. **复古风格**：  
   - 8位像素风，使用NES调色板（深蓝、浅绿、红色），背景音乐为Chiptune风格循环。  

**交互控制**：  
- **步进执行**：空格键单步执行，观察队列变化。  
- **自动播放**：AI模式自动扩展节点，速度可调。  

---

### **核心代码片段**  
**双端队列BFS实现**  
```cpp
struct State { int x, y, flips, gravity; };
deque<State> dq;
dq.push_back({sx, sy, 0, DOWN});

while (!dq.empty()) {
    auto curr = dq.front(); dq.pop_front();
    if (curr.x == target.x && curr.y == target.y) return curr.flips;

    // 处理移动（权0）
    for (int dx : {-1, 0, 1}) {
        State next = move(curr); // 计算下落和移动
        if (valid(next) && !vis[next]) {
            vis[next] = true;
            dq.push_front(next); // 优先处理
        }
    }

    // 处理翻转（权1）
    State flipped = flip_gravity(curr);
    if (valid(flipped) && !vis[flipped]) {
        vis[flipped] = true;
        dq.push_back(flipped); // 后处理
    }
}
```

---
处理用时：80.72秒