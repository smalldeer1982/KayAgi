# 题目信息

# [USACO09FEB] Fair Shuttle G

## 题目描述

Although Farmer John has no problems walking around the fair to collect prizes or see the shows, his cows are not in such good shape; a full day of walking around the fair leaves them exhausted. To help them enjoy the fair, FJ has arranged for a shuttle truck to take the cows from place to place in the fairgrounds.

FJ couldn't afford a really great shuttle, so the shuttle he rented traverses its route only once (!) and makes N (1 <= N <= 20,000) stops (conveniently numbered 1..N) along its path. A total of K (1 <= K <= 50,000) groups of cows conveniently numbered 1..K wish to use the shuttle, each of the M\_i (1 <= M\_i <= N) cows in group i wanting to ride from one stop S\_i (1 <= S\_i < E\_i) to another stop E\_i (S\_i < E\_i <= N) farther along the route.

The shuttle might not be able to pick up an entire group of cows (since it has limited capacity) but can pick up partial groups as appropriate.

Given the capacity C (1 <= C <= 100) of the shuttle truck and the descriptions of the groups of cows that want to visit various sites at the fair, determine the maximum number of cows that can ride the shuttle during the fair.


## 说明/提示

【样例说明】

班车可以把 $2$ 头奶牛从 $1$ 送到 $5$，$3$ 头奶牛从 $5$ 送到 $8$，$2$ 头奶牛从 $8$ 送到 $14$，$1$ 头奶牛从 $9$ 送到 $12$，$1$ 头奶牛从 $13$ 送到 $14$，$1$ 头奶牛从 $14$ 送到 $15$。


## 样例 #1

### 输入

```
8 15 3
1 5 2
13 14 1
5 8 3
8 14 2
14 15 1
9 12 1
12 15 2
4 6 1
```

### 输出

```
10
```

# AI分析结果



### **唯一算法分类**
贪心 + 线段树

---

### **题解思路与核心难点分析**

#### **核心算法逻辑**
1. **贪心策略**：将奶牛组按右端点升序排序（右端点相同时按左端点升序）。优先处理结束早的组，为后续留出更多容量。
2. **线段树维护**：用线段树维护区间内的最大乘客数，每次查询当前组的区间内最大乘客数，计算可搭载的奶牛数量，并更新线段树。

#### **解决难点**
- **贪心正确性**：结束早的组占用容量时间短，后续有更多空间。类似活动选择问题，数学归纳法可证明其最优性。
- **高效维护区间容量**：线段树支持区间最大值查询（判断剩余容量）和区间加法（更新已搭载量），时间复杂度为 \(O(K \log N)\)，\(K\) 为组数，\(N\) 为站点数。

#### **关键代码片段**
```cpp
// 线段树核心操作（以 Cry_For_theMoon 的代码为例）
void update(int x, int l, int r, int ql, int qr, int value) {
    if (ql <= l && qr >= r) {
        tree[x] += value;
        tag[x] += value;
        return;
    }
    push_down(x); // 下传懒惰标记
    // 递归更新左右子树
    // ...
    push_up(x); // 合并子树结果
}

int query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[x];
    push_down(x);
    // 递归查询左右子树最大值
    // ...
}
```

---

### **题解评分 (≥4星)**

| 作者               | 星级 | 亮点                                                                 |
|--------------------|------|----------------------------------------------------------------------|
| Cry_For_theMoon    | ⭐⭐⭐⭐⭐ | 详细证明贪心正确性，代码结构清晰，线段树实现高效                     |
| King丨帝御威       | ⭐⭐⭐⭐ | 提供纯贪心和线段树两种解法，对比分析思路清晰                         |
| Hank               | ⭐⭐⭐⭐ | 直接使用线段树维护，代码简洁，适合快速理解核心逻辑                   |

---

### **最优思路与技巧提炼**
1. **贪心排序**：按右端点排序是区间调度问题的经典策略，确保局部最优扩展为全局最优。
2. **线段树优化**：区间最大值查询与区间加法操作完美匹配容量限制的动态维护。
3. **部分装载处理**：`min(m_i, c - maxn)` 确保每次尽可能搭载最多奶牛。

---

### **同类型题与算法套路**
- **类似问题**：区间覆盖最大值（如 [P2894 USACO08FEB Hotel G](https://www.luogu.com.cn/problem/P2894)）
- **通用套路**：贪心排序 + 区间数据结构维护（线段树、树状数组、优先队列等）

---

### **推荐相似题目**
1. [P1937 USACO10MAR Barn Allocation](https://www.luogu.com.cn/problem/P1937)  
   （区间覆盖，贪心+线段树）
2. [P2894 USACO08FEB Hotel G](https://www.luogu.com.cn/problem/P2894)  
   （区间合并，线段树维护）
3. [P1253 扶苏的问题](https://www.luogu.com.cn/problem/P1253)  
   （区间加减与最值查询）

---

### **个人心得摘录**
- **线段树调试**：需注意区间端点的开闭（如 `r-1` 是否包含终点），懒惰标记的下传时机。
- **贪心反直觉**：部分题解未严格证明贪心正确性，需通过类比活动选择问题理解。

---

### **可视化与算法演示设计**

#### **动画方案**
1. **核心流程**：
   - **站点轴**：横向时间轴展示站点 1~N，班车从左向右移动。
   - **奶牛组**：不同颜色矩形表示各组（起点→终点），高度表示当前乘客数。
   - **线段树**：下方以树形结构动态显示区间最大值和更新过程。

2. **关键操作高亮**：
   - **查询阶段**：当前组区间变为黄色，线段树对应节点高亮。
   - **更新阶段**：搭载数量以绿色填充，线段树节点值变化时闪烁红色。

3. **复古像素风格**：
   - **8位音效**：查询时播放“滴”声，更新时“嘟”声，成功搭载后播放胜利音效。
   - **Canvas 绘制**：站点用像素方块表示，线段树节点显示为嵌套矩形。

#### **交互功能**
- **步进控制**：支持暂停/继续，拖动进度条观察每一步的状态。
- **自动演示**：AI 模式自动按排序顺序处理各组，速度可调。

#### **代码片段（JS伪代码）**
```javascript
// Canvas 绘制线段树节点
function drawNode(node, x, y) {
    ctx.fillStyle = node.highlight ? "#FFD700" : "#FFFFFF";
    ctx.fillRect(x, y, 40, 20);
    ctx.fillText(node.value, x + 5, y + 15);
}

// 音效触发
function playSound(type) {
    if (type === "query") beep(440, 50);
    else if (type === "update") beep(880, 50);
}
```

---

### **总结**
本题通过贪心排序与线段树的结合，高效解决了动态区间容量限制问题。可视化设计通过复古像素动画和交互式步进，直观展现了算法核心逻辑，适合教学与自学。

---
处理用时：72.57秒