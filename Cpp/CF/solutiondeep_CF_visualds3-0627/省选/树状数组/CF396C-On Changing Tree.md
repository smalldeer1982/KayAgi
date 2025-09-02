# 题目信息

# On Changing Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is a vertex number $ 1 $ .

Initially all vertices contain number $ 0 $ . Then come $ q $ queries, each query has one of the two types:

- The format of the query: $ 1 $ $ v $ $ x $ $ k $ . In response to the query, you need to add to the number at vertex $ v $ number $ x $ ; to the numbers at the descendants of vertex $ v $ at distance $ 1 $ , add $ x-k $ ; and so on, to the numbers written in the descendants of vertex $ v $ at distance $ i $ , you need to add $ x-(i·k) $ . The distance between two vertices is the number of edges in the shortest path between these vertices.
- The format of the query: $ 2 $ $ v $ . In reply to the query you should print the number written in vertex $ v $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

Process the queries given in the input.

## 说明/提示

You can read about a rooted tree here: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 样例 #1

### 输入

```
3
1 1
3
1 1 2 1
2 1
2 2
```

### 输出

```
2
1
```

# AI分析结果



### 唯一算法分类
树状数组/线段树 + DFS序区间操作

---

### 综合分析与结论
#### 核心算法流程
1. **DFS序预处理**：通过DFS遍历获取每个节点的进入时间戳（l[u]）和离开时间戳（r[u]），将子树操作转换为区间操作。
2. **拆分贡献项**：将修改公式 $x - (dep_v - dep_u)k$ 拆分为 $(x + dep_u·k) - dep_v·k$。
3. **双树状数组维护**：
   - 树状数组1维护 $(x + dep_u·k)$ 的区间加法
   - 树状数组2维护 $k$ 的区间加法
4. **查询计算**：$ans = sum1[v] - dep_v·sum2[v]$，其中sum1和sum2分别来自两个树状数组的查询结果

#### 可视化设计思路
1. **树结构展示**：左侧显示树形结构，右侧展示DFS序映射的线性区间
2. **区间染色动画**：
   - 修改操作时，用绿色渐变动画显示当前修改的区间 [l[u], r[u]]
   - 树状数组更新时，用金色高亮显示当前更新的节点路径
3. **深度关联可视化**：
   - 每个节点显示实时计算的 $(x + dep_u·k)$ 和 $k$ 的累计值
   - 查询时，用红色箭头动态连接两个树状数组的查询结果
4. **像素风格实现**：
   - 使用16色调色板（深绿表示未修改区域，亮黄表示活跃修改）
   - Canvas网格布局，每个网格单元对应一个DFS序位置
   - 音效设计：区间修改时播放"哔"声，查询时播放"叮"声

---

### 题解清单（4星及以上）
1. **nekko（5星）**  
   - 亮点：最早提出拆分贡献的数学推导，双树状数组实现简洁高效  
   - 代码：仅50行，完美利用树状数组的区间操作特性

2. **Pengzt（4.5星）**  
   - 亮点：代码最精简（仅34行），使用vector存储DFS序信息  
   - 优化：直接调用树状数组的区间更新函数

3. **Milthm（4星）**  
   - 亮点：完整注释的树状数组模板，适合新手学习  
   - 特色：严格处理负数取模，确保结果正确性

---

### 核心代码实现
```cpp
// nekko 题解核心代码
void dfs(int u) {
    static int tot = 0;
    l[u] = ++tot; // 进入时间戳
    for(int v: g[u]) dfs(v);
    r[u] = tot;   // 离开时间戳
}

// 修改操作处理
if(op == 1) {
    scanf("%d%d%d", &v, &x, &k);
    a.add(l[v], r[v], k % mod);            // 树状数组2维护k
    b.add(l[v], r[v], (x + 1ll*dep[v]*k) % mod); // 树状数组1维护x+dep_v*k
} else {
    scanf("%d", &v);
    ll qa = a.ask(l[v]);  // 累计k之和
    ll qb = b.ask(l[v]);  // 累计(x+dep_u*k)之和
    ll ans = (-dep[v]*qa + qb) % mod;  // 合并计算结果
}
```

---

### 相似题目推荐
1. **P3384 【模板】树链剖分** - 子树/路径修改查询
2. **P3373 【模板】线段树 2** - 双标记区间操作
3. **CF343D Water Tree** - DFS序区间覆盖操作

---

### 可视化代码片段（Canvas动画核心）
```javascript
// 绘制树状数组更新动画
function drawBITUpdate(l, r, color) {
    ctx.fillStyle = color;
    for(let i=l; i<=r; i++) {
        let x = (i-1)*CELL_SIZE;
        ctx.fillRect(x, 0, CELL_SIZE-2, CELL_SIZE-2);
        // 树状数组更新路径高亮
        while(i <= n) {
            highlightNode(i, '#ff0');
            i += i & -i;
        }
    }
}

// 音效触发
function playSound(type) {
    if(type === 'update') 
        new Audio('data:audio/wav;base64,UklGRl9...').play();
    else if(type === 'query')
        new Audio('data:audio/wav;base64,UklGRl9...').play();
}
```

---

### 个人心得摘录
> "在调试时发现，忘记处理负数取模会导致结果错误。例如当 (x+dep*v*k) 为负时，必须加上mod再取模。" —— nekko  
> "突然意识到深度差可以转化为两个独立变量的线性组合，这是突破的关键时刻。" —— shadowice1984

---

### 算法演示说明
1. **初始化阶段**：展示树的DFS遍历过程，动态生成时间戳
2. **修改操作**：  
   - 选中节点v，其子树区间[lv, rv]变为绿色  
   - 树状数组更新路径显示为金色闪烁线条
3. **查询操作**：  
   - 目标节点闪烁红色，显示从两个树状数组获取值的动画
4. **自动演示模式**：  
   - 按DFS序自动执行修改/查询，配8-bit背景音乐
   - 支持暂停/单步/回放功能

通过这种多维度的可视化呈现，学习者可以直观理解DFS序与树状数组在子树操作中的协同工作原理。

---
处理用时：63.99秒