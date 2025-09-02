# 题目信息

# Vessels

## 题目描述

There is a system of $ n $ vessels arranged one above the other as shown in the figure below. Assume that the vessels are numbered from 1 to $ n $ , in the order from the highest to the lowest, the volume of the $ i $ -th vessel is $ a_{i} $ liters.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF371D/f198564e53bb2ea5c99e17b823930a432879118f.png)Initially, all the vessels are empty. In some vessels water is poured. All the water that overflows from the $ i $ -th vessel goes to the $ (i+1) $ -th one. The liquid that overflows from the $ n $ -th vessel spills on the floor.

Your task is to simulate pouring water into the vessels. To do this, you will need to handle two types of queries:

1. Add $ x_{i} $ liters of water to the $ p_{i} $ -th vessel;
2. Print the number of liters of water in the $ k_{i} $ -th vessel.

When you reply to the second request you can assume that all the water poured up to this point, has already overflown between the vessels.

## 样例 #1

### 输入

```
2
5 10
6
1 1 4
2 1
1 2 5
1 1 4
2 1
2 2
```

### 输出

```
4
5
8
```

## 样例 #2

### 输入

```
3
5 10 8
6
1 1 12
2 2
1 1 6
1 3 2
2 2
2 3
```

### 输出

```
7
10
5
```

# AI分析结果



---

**唯一算法分类**：并查集（路径压缩优化）

---

### **题解思路、算法要点与解决难点**

1. **核心思路**  
   所有题解的核心在于**跳过已满容器**：通过维护每个容器的“下一个未满容器”指针（`nxt`或`fa`数组），在加水时快速定位到溢出的目标位置，避免暴力遍历。

2. **关键实现**  
   - **并查集/链表结构**：用数组模拟指针跳转，如`nxt[i]`表示容器`i`溢出后的首个未满容器。  
   - **路径压缩**：当容器`i`填满后，合并其父节点（`fa[i]`或`nxt[i-1]`）到`i+1`，后续操作直接跳过`i`。  
   - **溢出处理**：递归将溢出的水量传递到下一个未满容器，直到无法溢出或到达底部。

3. **解决难点**  
   - **时间复杂度优化**：均摊复杂度从暴力`O(nm)`优化为`O(n + m)`。  
   - **指针维护**：确保每次跳转后`nxt`或`fa`数组始终指向正确的未满容器。

---

### **题解评分（≥4星）**

1. **sto_5k_orz (5星)**  
   - **亮点**：代码简洁，并查集路径压缩逻辑清晰，`find`函数直接维护溢出跳转。  
   - **关键代码**：通过`nxt[find(x-1)] = find(x)`合并节点，直接跳过已满容器。

2. **b6e0_ (4星)**  
   - **亮点**：详细分析并查集的优化原理，强调每个沙漏最多被访问一次。  
   - **关键代码**：维护`fa`数组并递归处理溢出，逻辑与`sto_5k_orz`类似但变量命名更直观。

3. **Kirisame_Marisa_ (4星)**  
   - **亮点**：从暴力优化到链表跳转的逐步推导，分析时间复杂度均摊特性。  
   - **关键代码**：链表式维护`nxt`数组，通过循环更新跳转路径。

---

### **最优思路或技巧提炼**

1. **并查集路径压缩**  
   - **核心逻辑**：容器`i`填满后，将其父节点合并到`i+1`的父节点，后续操作直接跳过`i`。  
   - **代码片段**：  
     ```cpp
     while (x <= n && water[x] > a[x]) {
         nxt[find(x - 1)] = find(x); // 合并x-1到x的父节点
         water[x+1] += water[x] - a[x];
         water[x] = a[x];
         x = find(x) + 1;
     }
     ```

2. **链表式跳跃优化**  
   - **核心逻辑**：维护`nxt[i]`为下一个未满容器，递归传递溢出水量并更新指针。  
   - **代码片段**：  
     ```cpp
     while (nxt[now]) {
         if (x + N[now] >= A[now]) x -= (A[now] - N[now]);
         else { N[now] += x; break; }
         now = nxt[now];
     }
     ```

---

### **同类型题或类似算法套路**

1. **跳跃指针优化**  
   - **示例题目**：  
     - [LeetCode 41. First Missing Positive](https://leetcode.com/problems/first-missing-positive/)：通过数组索引跳跃标记已访问元素。  
     - [洛谷 P2835 刻录光盘](https://www.luogu.com.cn/problem/P2835)：并查集维护连通性。

2. **均摊复杂度分析**  
   - **示例题目**：  
     - [CF 911F Tree Destruction](https://codeforces.com/contest/911/problem/F)：贪心操作均摊O(n)。  
     - [洛谷 P1540 机器翻译](https://www.luogu.com.cn/problem/P1540)：队列维护最近使用，均摊O(1)。

---

### **推荐洛谷题目**

1. **P3367 【模板】并查集**  
   - 并查集基础操作，路径压缩与按秩合并的经典实现。

2. **P1551 亲戚**  
   - 并查集应用，判断节点连通性。

3. **P1197 [JSOI2008] 星球大战**  
   - 反向并查集，动态维护连通块。

---

### **个人心得摘录**

1. **sto_5k_orz**  
   > “精华在于`nxt[find(x-1)] = find(x)`，直接跳过已满节点，合并后复杂度骤降。”

2. **scc36**  
   > “链表实现需注意指针更新顺序，否则可能跳过未处理节点，调试时反复验证`nxt`数组。”

3. **MuYC**  
   > “线段树分块处理TLE后，转向并查集实现，顿悟维护溢出路径才是关键。”

---

### **可视化与算法演示**

1. **核心动画设计**  
   - **像素风格容器**：用16色块表示容器状态（绿色未满/红色已满）。  
   - **高亮跳转路径**：加水时当前容器闪烁，溢出水流动态传递到`nxt`指向的容器。  
   - **并查集合并特效**：已满容器变灰，父节点箭头指向下一个未满容器。

2. **交互功能**  
   - **步进控制**：允许单步执行加水操作，观察`nxt`或`fa`数组的更新。  
   - **音效提示**：  
     - `加水`：短促“滴答”声。  
     - `溢出`：水流声伴随容器变红。  
     - `合并`：金属碰撞声，父节点箭头刷新。

3. **自动演示模式**  
   - **AI逻辑**：模拟随机加水操作，自动展示指针跳转与路径压缩过程。  
   - **积分系统**：每次成功合并得10分，连续跳过多个容器触发连击奖励。

---

**代码片段（并查集核心逻辑）**  
```cpp
int fa[N], water[N], capacity[N];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void add(int p, int x) {
    int u = p;
    water[u] += x;
    while (u <= n && water[u] > capacity[u]) {
        int overflow = water[u] - capacity[u];
        water[u] = capacity[u];
        fa[find(u)] = find(u + 1); // 合并到下一个未满容器
        u = find(u);
        water[u] += overflow;
    }
}
```

---

**可视化实现要点（伪代码）**  
```javascript
// Canvas绘制容器
function drawVessels() {
    ctx.fillStyle = "#00FF00"; // 未满
    vessels.forEach((v, i) => {
        if (v.isFull) ctx.fillStyle = "#FF0000"; // 已满
        ctx.fillRect(i * 30, 100, 25, v.waterLevel);
    });
}

// 并查集合并动画
function mergeAnimation(u) {
    highlight(u); // 高亮当前容器
    playSound("merge"); // 播放合并音效
    drawArrow(fa[u], fa[u] + 1); // 绘制父节点跳转箭头
}
```

---
处理用时：88.14秒