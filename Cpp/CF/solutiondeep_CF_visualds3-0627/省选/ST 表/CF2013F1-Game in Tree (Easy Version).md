# 题目信息

# Game in Tree (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, $ \mathbf{u = v} $ . You can make hacks only if both versions of the problem are solved.

Alice and Bob are playing a fun game on a tree. This game is played on a tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . Recall that a tree with $ n $ vertices is an undirected connected graph with $ n - 1 $ edges.

Alice and Bob take turns, with Alice going first. Each player starts at some vertex.

On their turn, a player must move from the current vertex to a neighboring vertex that has not yet been visited by anyone. The first player who cannot make a move loses.

You are given two vertices $ u $ and $ v $ . Represent the simple path from vertex $ u $ to $ v $ as an array $ p_1, p_2, p_3, \ldots, p_m $ , where $ p_1 = u $ , $ p_m = v $ , and there is an edge between $ p_i $ and $ p_{i + 1} $ for all $ i $ ( $ 1 \le i < m $ ).

You need to determine the winner of the game if Alice starts at vertex $ 1 $ and Bob starts at vertex $ p_j $ for each $ j $ (where $ 1 \le j \le m $ ).

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2013F1/e1cf544a0db6c078ce895e1ac7918ee5810cf6b5.png) Tree from the first and second examples.In the first test case, the path will be ( $ 2,2 $ ). Bob starts at vertex $ 2 $ , Alice will not be able to move anywhere on her first turn and will lose.

In the second test case, the path will be ( $ 3,3 $ ). Bob starts at vertex $ 3 $ , Alice will move to vertex $ 2 $ , and Bob will have no remaining vertices to visit and will lose.

## 样例 #1

### 输入

```
3
3
1 2
2 3
2 2
3
1 2
2 3
3 3
6
1 2
1 3
2 4
2 5
1 6
4 4```

### 输出

```
Bob
Alice
Alice```

# AI分析结果



---

### 唯一算法分类  
**博弈论 + 树形DP + 区间最值查询**

---

### 综合分析与结论  
#### 题解思路与核心难点  
1. **问题转化**：将博弈过程转化为双方在路径上的移动博弈，每次移动后比较双方剩余可选步数的优势。  
2. **树形DP预处理**：计算每个节点在不走路径上的点时，能到达的最远步数（即子树深度）。  
3. **区间最值查询**：利用ST表快速查询路径上某段区间内的最大剩余步数，决定胜负关键点。  
4. **双指针模拟博弈**：用 `l` 和 `r` 表示当前双方在路径上的位置，交替移动并比较优势。  

**难点**：如何正确预处理子树深度，并在动态移动中快速比较双方的潜在优势。  

#### 核心算法流程  
1. **DFS预处理父节点**：构建树的结构，找到从 `u` 到根节点的路径。  
2. **树形DP计算 `f[u]`**：表示节点 `u` 在不走路径时的最大延伸步数。  
3. **ST表构建**：预处理路径上每个点的 `f[u]` 的两种表示（正序和逆序）。  
4. **双指针博弈模拟**：  
   - Alice 初始在路径起点 (`l=1`)，Bob 初始在路径终点 (`r=m`)。  
   - 每一步根据当前玩家查询区间最大值，判断是否能够获胜。  

#### 可视化设计思路  
- **树结构绘制**：用树状图展示节点和路径，高亮路径上的节点 `c[1..m]`。  
- **动态双指针移动**：用不同颜色标记 `l` 和 `r`，显示当前双方位置。  
- **ST表查询高亮**：在路径上绘制区间查询范围，动态显示最大值结果。  
- **胜负判定动画**：当某一方满足条件时，触发音效和闪烁效果。  

**复古游戏化设计**：  
- **像素风格树**：用 8 位色块表示节点，路径用黄色高亮，子树用绿色渐变。  
- **音效触发**：移动时播放“点击”音效，胜负时播放不同音调。  
- **自动演示模式**：模拟双方最优策略移动，展示博弈过程。  

---

### 题解清单 (评分 ≥4星)  
**题解作者：DerrickLo（4星）**  
- **亮点**：  
  1. 将博弈过程转化为区间最值比较，思路清晰。  
  2. 利用树形DP预处理子树深度，结合ST表高效查询。  
  3. 双指针模拟博弈移动，避免复杂递归。  
- **不足**：代码可读性一般，ST表部分可优化注释。  

---

### 最优思路与技巧提炼  
1. **关键变量 `f[u]`**：表示节点 `u` 在不走路径时的最大延伸步数，通过树形DP预处理。  
2. **路径区间最值**：将路径上的博弈转化为区间最值问题，用ST表快速查询。  
3. **交替移动策略**：双方每次向中间移动一步，动态比较剩余优势。  

**技巧应用**：类似问题中，若博弈双方在固定路径上移动，可考虑预处理子树信息并结合区间查询。  

---

### 同类型题与算法套路  
- **相似题目类型**：树上博弈、动态区间最值查询、双指针模拟策略。  
- **通用解法**：  
  1. 预处理子树/路径信息。  
  2. 利用数据结构（ST表、线段树）加速区间查询。  
  3. 模拟双方交替决策过程。  

---

### 推荐相似题目  
1. **CF 1110G Tree-Tac-Toe**（博弈策略与树结构）  
2. **Luogu P1850 换教室**（树形DP与路径选择）  
3. **LeetCode 1516.Move Sub-Tree**（子树操作与博弈）  

---

### 代码核心逻辑  
```cpp  
// 树形DP预处理 f[u]  
void dfs1(int u) {  
    f[u] = 1;  
    for (int v : ve[u]) {  
        if (v == fa[u] || vis[v]) continue;  
        dfs1(v);  
        f[u] = max(f[u], f[v] + 1);  
    }  
}  

// 双指针博弈模拟  
int l = 1, r = cnt, noww = 0, flag = 0;  
while (l < r) {  
    if (noww == 0) { // Alice 移动  
        int cnt1 = f[c[r]] - 1;  
        int cnt2 = query1(l, r-1) - (l-1);  
        if (cnt1 > cnt2) {  
            cout << "Alice\n"; flag = 1; break;  
        }  
        r--;  
    } else { // Bob 移动  
        int cnt1 = f[c[l]] - 1;  
        int cnt2 = query2(l+1, r) - (cnt - r);  
        if (cnt1 > cnt2) {  
            cout << "Bob\n"; flag = 1; break;  
        }  
        l++;  
    }  
    noww ^= 1;  
}  
```  

---

### 可视化与复古游戏化实现  
**Canvas 动画设计**：  
1. **树绘制**：用递归布局算法绘制树，路径节点用黄色填充。  
2. **双指针动画**：`l` 用红色方块，`r` 用蓝色方块，移动时播放“移动音效”。  
3. **ST表查询高亮**：在路径上绘制绿色半透明覆盖层表示查询区间。  

**音效设计**：  
- 移动时：8-bit “哔”声。  
- 胜利时：上扬的“胜利旋律”。  
- 失败时：低音“失败音效”。  

**自动演示模式**：  
```javascript  
function autoPlay() {  
    while (l < r) {  
        simulateMove(); // 根据当前玩家计算并移动  
        await sleep(1000); // 控制速度  
    }  
}  
```  

---

**答案结束**

---
处理用时：81.62秒