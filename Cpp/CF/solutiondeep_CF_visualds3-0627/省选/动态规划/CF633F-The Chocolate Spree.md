# 题目信息

# The Chocolate Spree

## 题目描述

Alice and Bob have a tree (undirected acyclic connected graph). There are $ a_{i} $ chocolates waiting to be picked up in the $ i $ -th vertex of the tree. First, they choose two different vertices as their starting positions (Alice chooses first) and take all the chocolates contained in them.

Then, they alternate their moves, selecting one vertex at a time and collecting all chocolates from this node. To make things more interesting, they decided that one can select a vertex only if he/she selected a vertex adjacent to that one at his/her previous turn and this vertex has not been already chosen by any of them during other move.

If at any moment one of them is not able to select the node that satisfy all the rules, he/she will skip his turns and let the other person pick chocolates as long as he/she can. This goes on until both of them cannot pick chocolates any further.

Due to their greed for chocolates, they want to collect as many chocolates as possible. However, as they are friends they only care about the total number of chocolates they obtain together. What is the maximum total number of chocolates they may pick?

## 说明/提示

In the first sample, Alice may start at the vertex $ 9 $ and Bob at vertex $ 8 $ . Alice will select vertex $ 1 $ and Bob has no options now. Alice selects the vertex $ 7 $ and they both stop.

In the second sample, both of them will pick either of the nodes alternately.

## 样例 #1

### 输入

```
9
1 2 3 4 5 6 7 8 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
```

### 输出

```
25
```

## 样例 #2

### 输入

```
2
20 10
1 2
```

### 输出

```
30
```

# AI分析结果



0. **题目翻译**

# 巧克力狂欢

## 题目描述

Alice和Bob有一棵树（无环连通无向图）。第i个顶点上有a_i块巧克力等待被收集。首先，他们选择两个不同的顶点作为起始位置（Alice先选），并拿走这两个顶点的所有巧克力。

然后，他们轮流移动，每次选择一个顶点，拿走该顶点的所有巧克力。规则是：每次只能选择与上一次自己选择的顶点相邻且未被双方选过的顶点。

当某一方无法选择合法顶点时，将跳过回合，由另一方继续操作直到双方都无法行动。他们想要最大化共同获得的巧克力总数。求这个最大值。

## 说明/提示

样例1中Alice选顶点9，Bob选顶点8。之后Alice选顶点1，Bob无动作。Alice再选顶点7后双方停止。

样例2中两人交替选两个顶点。

## 样例 #1

输入输出与原题一致...

---

1. **唯一算法分类**  
无算法分类（树形动态规划）

2. **综合分析与结论**  
核心难点在于建模树上两条不相交路径的最大权值和。关键状态设计为：
- f[u][0]: 子树中最长两条链之和
- f[u][1]: 子树中最长单链
- g[u]: 从u到叶子的链+另一条不相交链的最大值
- down[u]: 从u到叶子的最长链

可视化设计采用树形展开动画，用不同颜色标记当前处理的子树：
1. 红色闪烁显示当前节点u
2. 蓝色高亮正在计算的down[u]路径
3. 绿色动态延伸g[u]的复合路径
4. 每次状态更新时播放清脆的电子音效

3. **题解清单 (4星以上)**

【NOIPZZY题解】★★★★★
- 亮点：四状态设计清晰，转移方程覆盖所有情况
- 关键代码段：
```cpp
f[cur][0] = max(f[cur][0], f[cur][1]+f[u][1]);  // 合并两条单链
g[cur] = max(g[cur], down[cur]+f[u][1]);        // 当前链+子树最长链
```

【Liuxizai题解】★★★★☆
- 亮点：五状态设计更细致，注释详细
- 核心转移：
```cpp
dp[now][0] = max(dp[now][0], dp[x][2] + dp[now][4]); // 穿当前节点的复合链
```

【傅思维题解】★★★★
- 亮点：代码简洁，关键状态命名易懂
- 创新点：h[u]维护子树最大单链辅助转移

4. **最优思路提炼**  
树形DP维护四种关键状态：
1. 单子树最长链（down）
2. 子树内两条链（f0）
3. 复合链（当前节点连接两条子链）
4. 兄弟子树间的链组合

通过后序遍历合并子树信息，用辅助状态h[u]记录兄弟节点中的最大值，实现O(n)复杂度。

5. **同类型题目**  
- [洛谷P4383] 选课（树形DP+分组背包）
- [洛谷P2634] 聪聪可可（树上路径统计）
- [CF14D] Two Paths（不相交路径）

6. **可视化方案（像素风格）**  
```javascript
// Canvas绘制树节点示例
function drawNode(x, y, val, color) {
  ctx.fillStyle = color;
  ctx.fillRect(x-15, y-15, 30, 30); // 方形节点
  ctx.fillStyle = '#000';
  ctx.font = '12px retro';
  ctx.fillText(val, x-8, y+5);
}

// DP状态更新动画
function animateDP(u) {
  highlight(u, '#FF0000'); // 红色高亮当前节点
  playSound('bleep');      // 电子提示音
  for(let v of children[u]) {
    drawLine(u, v, '#00FF00'); // 绿色绘制转移路径
    updateMatrix(v);           // 更新子节点状态
  }
}
```

7. **核心代码实现**  
NOIPZZY题解状态转移核心：
```cpp
void dfs(int cur, int fa) {
    down[cur] = w[cur];
    for(int u : G[cur]) if(u != fa) {
        dfs(u, cur);
        // 关键转移逻辑
        f[cur][0] = max(f[cur][0], f[cur][1] + f[u][1]);
        f[cur][1] = max(f[cur][1], down[cur] + down[u]);
        g[cur] = max(g[cur], down[cur] + f[u][1]);
        down[cur] = max(down[cur], down[u] + w[cur]);
    }
}
```

---
处理用时：52.74秒