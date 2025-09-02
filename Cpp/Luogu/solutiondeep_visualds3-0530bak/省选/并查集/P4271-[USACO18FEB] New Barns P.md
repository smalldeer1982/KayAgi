# 题目信息

# [USACO18FEB] New Barns P

## 题目描述

给你一棵树，初始没有节点。你需要支持两种操作：  

- `B p` 表示新建一个节点，将它与 $p$  节点连接；若 $p=-1$，则表示不与其它节点相连  

- `Q k` 表示查询在 $k$ 节点所在的连通块中，距它最远的点的距离。这里距离的定义是两点间经过的边数。

## 说明/提示

【数据范围】  

对于 $100%$ 的数据，$1 \le q \le 10^5$。  
保证操作合法。

The example input corresponds to this network of barns:
```
  (1) 
    \   
     (2)---(4)
    /
  (3)
```
In query 1, we build barn number 1. In query 2, we ask for the distance of 1 to the farthest connected barn. Since barn 1 is connected to no other barns, the answer is 0. In query 3, we build barn number 2 and connect it to barn 1. In query 4, we build barn number 3 and connect it to barn 2. In query 5, we ask for the distance of 3 to the farthest connected barn. In this case, the farthest is barn 1, which is 2 units away. In query 6, we build barn number 4 and connect it to barn 2. In query 7, we ask for the distance of 2 to the farthest connected barn. All three barns 1, 3, 4 are the same distance away, which is 1, so this is our answer.

Problem credits: Anson Hu

## 样例 #1

### 输入

```
7
B -1
Q 1
B 1
B 2
Q 3
B 2
Q 2```

### 输出

```
0
2
1
```

# AI分析结果



**唯一算法分类**  
树的直径维护

---

### 综合分析与结论

**核心思路**  
所有题解均基于以下两个关键性质：  
1. 树中任意点的最远点必为直径端点之一  
2. 合并两棵树的新直径端点只能是原直径端点组合中的两个  

**算法流程与可视化设计**  
1. **维护直径端点**：每个连通块记录直径端点u、v  
2. **合并操作**：当新节点x与连通块A合并时，计算x到A的直径端点的距离，更新A的直径为max(原直径, x到u的距离, x到v的距离)  
3. **查询操作**：计算查询点k到当前连通块两个端点的距离取最大值  

**可视化设计要点**  
- **像素动画**：用不同颜色方块表示节点（红色为查询点，蓝色为直径端点）  
- **连接动画**：显示新节点如何与父节点连接，并高亮当前计算的路径  
- **直径更新**：当合并后直径改变时，用闪烁效果突出新端点  
- **音效触发**：合并成功时播放“连接”音效，查询结果出现时播放“成功”音效  

---

### 题解清单（≥4星）

1. **暴力出奇迹（★★★★★）**  
   - 亮点：离线建树+倍增LCA，代码简洁高效  
   - 关键代码：通过预处理的LCA快速计算距离，用并查集维护直径端点  

2. **ywy_c_asm（★★★★）**  
   - 亮点：LCT动态维护轻儿子子树深度堆  
   - 个人心得：通过可删堆维护轻儿子信息，实现O(log²n)复杂度  

3. **Genius_Z（★★★★）**  
   - 亮点：LCT维护直径端点，代码模块化清晰  
   - 关键优化：Splay维护路径信息实现O(logn)查询  

---

### 核心代码实现（暴力出奇迹版）

```cpp
int dis(int x, int y) {
    return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}

void merge(int x, int new_node) {
    int rt = find(x); // 找到连通块根
    int u = d[rt][0], v = d[rt][1];
    int d1 = dis(u, new_node), d2 = dis(v, new_node);
    if (d1 > d[rt].max_len) d[rt] = {d1, u, new_node};
    if (d2 > d[rt].max_len) d[rt] = {d2, v, new_node};
}

int query(int k) {
    int rt = find(k);
    return max(dis(k, d[rt].u), dis(k, d[rt].v));
}
```

---

### 同类型题目推荐

1. **P3304 [SDOI2013]森林** - 动态维护森林中的直径  
2. **P1099 树的核心** - 利用直径性质寻找最优位置  
3. **P4381 [IOI2008]Island** - 基环树直径的综合应用  

---

### 可视化与交互设计

**动画方案**：  
1. **节点连接**：新节点以绿色闪烁出现，连接到父节点时显示黄色连线  
2. **直径更新**：当新端点出现时，原端点变为蓝色，新端点变为红色并持续闪烁3次  
3. **查询高亮**：查询时显示从查询点到两个端点的路径，路径颜色随距离动态渐变  

**音效设计**：  
- `link_sound.mp3`：连接操作成功时播放（8-bit风格短音）  
- `max_distance.wav`：查询结果显示时播放上升音调  

**自动演示模式**：  
- 按空格键逐步执行操作，按'A'键切换自动播放速度（1x/2x/0.5x）

---

### 总结与心得

通过维护树的直径端点，将动态问题转化为静态距离计算，避免了复杂数据结构的使用。离线预处理LCA与并查集的结合使得代码既高效又易于实现。调试时需特别注意合并时四种端点组合的完全比较，避免遗漏可能的更大直径路径。

---
处理用时：52.89秒