# 题目信息

# Legacy

## 题目描述

Rick and his co-workers have made a new radioactive formula and a lot of bad guys are after them. So Rick wants to give his legacy to Morty before bad guys catch them.

There are $ n $ planets in their universe numbered from $ 1 $ to $ n $ . Rick is in planet number $ s $ (the earth) and he doesn't know where Morty is. As we all know, Rick owns a portal gun. With this gun he can open one-way portal from a planet he is in to any other planet (including that planet). But there are limits on this gun because he's still using its free trial.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786B/9ce8ffb5132d0e638eaee42e56a9bbc8517d720d.png)By default he can not open any portal by this gun. There are $ q $ plans in the website that sells these guns. Every time you purchase a plan you can only use it once but you can purchase it again if you want to use it more.

Plans on the website have three types:

1. With a plan of this type you can open a portal from planet $ v $ to planet $ u $ .
2. With a plan of this type you can open a portal from planet $ v $ to any planet with index in range $ [l,r] $ .
3. With a plan of this type you can open a portal from any planet with index in range $ [l,r] $ to planet $ v $ .

Rick doesn't known where Morty is, but Unity is going to inform him and he wants to be prepared for when he finds and start his journey immediately. So for each planet (including earth itself) he wants to know the minimum amount of money he needs to get from earth to that planet.

## 说明/提示

In the first sample testcase, Rick can purchase $ 4 $ th plan once and then $ 2 $ nd plan in order to get to get to planet number $ 2 $ .

## 样例 #1

### 输入

```
3 5 1
2 3 2 3 17
2 3 2 2 16
2 2 2 3 3
3 3 1 1 12
1 3 3 17
```

### 输出

```
0 28 12 
```

## 样例 #2

### 输入

```
4 3 1
3 4 1 3 12
2 2 3 4 10
1 2 4 16
```

### 输出

```
0 -1 -1 12 
```

# AI分析结果


### 💡 Kay的C++算法解析：Legacy 深入学习指南 💡

> **核心思想**：本题要求处理点对点、点对区间、区间对点的连边操作，并求最短路。直接暴力建边会导致 $O(n^2)$ 复杂度，需用**线段树优化建图**将区间操作转化为 $O(\log n)$ 条边，通过两棵线段树（出树和入树）实现高效建图。

---

### 1. 题目解读与核心算法识别  
✨ **本题主要考察**：`线段树优化建图 + 最短路算法`  

🗣️ **初步分析**：  
> 解决本题需构建两棵线段树：  
> - **出树（自上而下）**：用于处理点向区间连边（操作2），父节点指向子节点（边权0）  
> - **入树（自下而上）**：用于处理区间向点连边（操作3），子节点指向父节点（边权0）  
> 两树叶子节点对应原图的点，并通过边权为0的边相互连接。操作1直接在叶子节点间连边。  

**可视化设计**：  
- **像素风格**：8位复古游戏风格，左侧出树（蓝色箭头向下），右侧入树（红色箭头向上），叶子节点黄色  
- **关键动画**：  
  - 操作1：点对点连红色箭头（伴随"叮"声）  
  - 操作2：点向出树区间节点连橙色箭头（区间节点闪烁）  
  - 操作3：入树区间节点向点连绿色箭头  
  - Dijkstra执行时，当前处理的节点像素块闪烁，更新路径高亮  

---

### 2. 精选优质题解参考  
**题解一（tzc_wk）**  
* **亮点**：  
  - 清晰图解线段树结构，双树（出树/入树）分工明确  
  - 代码用常量 `D=5e5` 区分两树节点，避免冲突  
  - 空间优化：动态计算节点数，避免浪费  

**题解二（maoyiting）**  
* **亮点**：  
  - 引入“入树叶子→出树区间”的连边逻辑，代码模块化  
  - 强调叶子节点双向连接的重要性  
  - 复杂度分析严谨：边数 $O(n + q\log n)$  

**题解三（张鑫杰）**  
* **亮点**：  
  - 分层思想：原图点与线段树节点分离  
  - 处理操作3时反向建边逻辑简洁  
  - 代码注释详细，适合初学者  

> **共同优势**：均使用堆优化Dijkstra，避免SPFA不稳定问题  

---

### 3. 核心难点辨析与解题策略  
1. **难点1：双树协同与叶子连接**  
   * **分析**：若未正确连接两树叶子节点，则点→区间→点的路径断裂。优质解法均通过0权边连接两树叶子（如 `add(leaf, leaf+D, 0)`）  
   * 💡 **学习笔记**：叶子节点是原图与线段树的桥梁，必须双向连接  

2. **难点2：区间拆分的边界处理**  
   * **分析**：操作2/3需递归拆分区间至线段树节点。若边界判断错误（如`mid`计算），会导致漏连或多连  
   * 💡 **学习笔记**：使用标准线段树查询逻辑：`[l,mid]` 和 `[mid+1,r]`  

3. **难点3：空间分配与节点编号**  
   * **分析**：双树节点编号需与原点隔离（如原点1~n，树节点从n+1开始）。动态开点可避免溢出  
   * 💡 **学习笔记**：总节点数上限 $5n + q\log n$  

### ✨ 解题技巧总结  
- **技巧1：双树分工**  
  出树处理点→区间（操作2），入树处理区间→点（操作3）  
- **技巧2：常量偏移**  
  用 `D` 或 `+K` 区分两树节点（如入树节点 `id + D`）  
- **技巧3：Dijkstra优化**  
  用 `priority_queue` 避免重复松弛  

---

### 4. C++核心代码实现赏析  
**通用核心实现参考**（综合优质题解）：  
```cpp
const int N = 1e5 + 5, D = 4e5; // D 为偏移量
vector<pair<int, ll>> G[N * 5]; // 总节点数 5n

void build(int k, int l, int r) {
    if (l == r) {
        // 叶子节点连接两棵树
        G[k + D].push_back({k, 0});
        G[k].push_back({k + D, 0});
        return;
    }
    int mid = (l + r) >> 1;
    // 出树：父->子（0权）
    G[k].push_back({k << 1, 0});
    G[k].push_back({k << 1 | 1, 0});
    // 入树：子->父（0权）
    G[(k << 1) + D].push_back({k + D, 0});
    G[(k << 1 | 1) + D].push_back({k + D, 0});
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
}

// 操作2：点v -> 区间[l, r]
void add_point_to_range(int v, int l, int r, ll w) {
    if (ql <= l && r <= qr) {
        G[v + D].push_back({k, w}); // 从入树叶子到出树区间
        return;
    }
    // 递归拆分区间...
}
```

**题解一核心片段**（tzc_wk）：  
```cpp
// 操作3：区间[l, r] -> 点v
void connect(int k, int l, int r, int v, int w, int tp) {
    if (L <= l && r <= R) {
        if (tp) G[k + D].push_back({v, w}); // 入树区间连点
        else G[v].push_back({k, w});        // 点连出树区间
        return;
    }
    // 递归拆分区间
}
```
* **学习笔记**：`tp` 标记区分操作类型，逻辑紧凑  

---

### 5. 算法可视化：像素动画演示  
**主题**：像素探险家寻宝（8位复古风）  
**核心演示流程**：  
1. **初始化场景**：  
   - 左侧蓝色出树（边向下），右侧红色入树（边向上），底部黄色原点  
   - 控制面板：开始/暂停/单步/速度滑块  

2. **操作演示**（音效触发）：  
   - 操作1：底部两点间红色箭头（"叮"声）  
   - 操作2：从黄点→出树区间节点（橙色箭头，区间闪烁）  
   - 操作3：从入树区间节点→黄点（绿色箭头，节点闪烁）  

3. **Dijkstra执行**：  
   - 起点 `s` 像素块高亮，加入队列  
   - 当前节点闪烁，更新邻居时路径高亮（成功时"胜利"音效）  
   - 最终最短路显示在原图点上  

---

### 6. 拓展练习与相似问题  
**通用技巧迁移**：  
线段树优化建图适用于：区间→点的批量操作（如炸弹波及范围、网络广播）  

**推荐练习**：  
1. **洛谷 P3588**  
   - 区间约束问题，强化双树协同  
2. **洛谷 P5025**  
   - 炸弹连锁反应，转化为区间覆盖  
3. **洛谷 P6348**  
   - 区间到区间的连边，扩展思维  

---

> **总结**：线段树优化建图通过两棵树将区间操作降为 $O(\log n)$，是处理大规模图论问题的利器。重点掌握双树构建、叶子连接和操作拆分，结合Dijkstra高效求解。

---
处理用时：127.59秒