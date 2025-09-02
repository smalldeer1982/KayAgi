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

### **综合分析与结论**

- **题目核心**：Alice 和 Bob 在树上的路径博弈问题，关键点在于双方在路径上的位置选择及非路径分支的最大移动步数比较。
- **贪心策略**：双方交替移动，每次选择使对方剩余非路径分支步数最少的路径位置。预处理每个节点的非路径分支最大步数，利用 ST 表快速查询区间最大值，通过双指针模拟博弈过程。
- **解决难点**：将树分解为路径和非路径分支，动态维护双方可用的最大步数区间，实现高效的贪心决策。
- **可视化设计**：
  - **树结构绘制**：以路径为轴线，分支深度用不同颜色标记。
  - **双指针动画**：显示 Alice（左指针 l）和 Bob（右指针 r）的移动，高亮当前查询的区间。
  - **胜负判定**：比较当前玩家的分支步数和对方区间内的最大值，以颜色/音效提示胜负结果。
  - **复古像素风格**：用 8-bit 像素块表示树节点，移动时触发经典音效（如“移动”音效、“胜利”音效）。

---

### **题解评分 (4星)**

- **关键亮点**：
  1. **预处理分支深度**：通过 DFS 计算每个节点的非路径最大步数（`f[u]`）。
  2. **ST 表优化查询**：构建两个 ST 表处理左右区间的最大值查询，时间复杂度 O(1)。
  3. **双指针博弈模拟**：通过交替移动左右指针，动态比较双方可用步数，快速判断胜负。
- **改进建议**：变量命名可更清晰（如 `st1` 和 `st2` 改为 `left_max` 和 `right_max`），增加注释解释 ST 表含义。

---

### **最优思路提炼**

1. **路径分解**：将树分解为从根到目标节点的路径，其他部分视为分支。
2. **分支步数预处理**：计算每个路径节点在非路径方向的最大深度（`f[u]`）。
3. **区间最值查询**：用 ST 表维护路径上各区间的分支步数最大值。
4. **双指针博弈**：Alice 和 Bob 交替向中间移动，每次比较当前玩家的分支步数是否大于对方区间内的最大值，决定胜负。

---

### **同类型题与算法套路**

- **通用套路**：
  - **树博弈问题**：预处理子树信息，动态规划或贪心策略。
  - **区间最值优化**：利用 ST 表、线段树等数据结构快速查询。
- **类似题目**：
  1. **洛谷 P2585**（三色二叉树）：预处理子树状态。
  2. **洛谷 P2458**（保安站岗）：贪心选择监控点。
  3. **洛谷 P1040**（加分二叉树）：区间 DP 与树结构结合。

---

### **核心代码实现**

```cpp
// 预处理非路径分支的最大步数 f[u]
void dfs1(int u) {
    f[u] = 1;
    for (int v : ve[u]) {
        if (v == fa[u]) continue;
        dfs1(v);
    }
    for (int v : ve[u]) {
        if (v == fa[u] || vis[v]) continue;
        f[u] = max(f[u], f[v] + 1);
    }
}

// 双指针博弈过程
int l = 1, r = cnt, noww = 0, flag = 0;
while (l < r) {
    if (noww == 0) { // Alice 移动
        int cnt1 = f[c[r]] - 1;
        int cnt2 = query1(l, r-1) - (l-1);
        if (cnt1 > cnt2) { // Alice 胜
            cout << "Alice\n"; flag = 1; break;
        }
        r--;
    } else { // Bob 移动
        int cnt1 = f[c[l]] - 1;
        int cnt2 = query2(l+1, r) - (cnt - r);
        if (cnt1 > cnt2) { // Bob 胜
            cout << "Bob\n"; flag = 1; break;
        }
        l++;
    }
    noww ^= 1;
}
if (!flag) cout << (noww ? "Bob\n" : "Alice\n");
```

---

### **可视化与算法演示**

- **动画设计**：
  1. **树结构**：Canvas 绘制树，路径节点高亮为红色，分支节点为蓝色。
  2. **双指针移动**：左右指针 `l` 和 `r` 用箭头标识，移动时播放“滑动”音效。
  3. **分支步数显示**：每个节点旁显示 `f[u]` 值，颜色深浅表示大小。
  4. **胜负判定**：当某次比较成立时，屏幕闪烁红色（Alice 胜）或蓝色（Bob 胜），播放对应音效。
- **交互功能**：
  - **步进控制**：空格键单步执行，方向键调整速度。
  - **自动模式**：AI 自动运行，模拟双方最优策略。

---

### **复古游戏化设计（示例）**

```javascript
// 伪代码：绘制像素树
const canvas = document.getElementById("game-canvas");
const ctx = canvas.getContext("2d");

function drawNode(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x, y, 16, 16); // 16x16 像素块
}

// 示例：路径节点为红色，分支为蓝色
drawNode(100, 50, "#FF0000"); // 路径节点
drawNode(150, 50, "#0000FF"); // 分支节点

// 音效触发
function playSound(effect) {
    const audio = new Audio(`sfx/${effect}.wav`);
    audio.play();
}
```

---

**总结**：本题解通过预处理分支步数和区间最值优化，高效解决了树上的博弈问题。其贪心策略与数据结构结合的思路，可推广至类似树形动态规划或博弈场景。

---
处理用时：80.27秒