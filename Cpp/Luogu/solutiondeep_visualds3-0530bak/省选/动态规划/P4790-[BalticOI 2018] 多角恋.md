# 题目信息

# [BalticOI 2018] 多角恋

## 题目描述

**题目译自 [BalticOI 2018](https://boi2018.progolymp.se/tasks/) Day1「[Love Polygon](https://boi18-day1-open.kattis.com/problems/boi18.polygon)」**

给一张 $N$ 个点的有向图，每个点的出度为 $1$。每次可以花费 $1$ 的代价修改图上的一条边的终点，也就是改变从一个点出发所到达的点。求最少需要花费多少代价，才能使这张图形成若干个两两不相交的二元环，并且图上的所有点都在某一个环里。

## 说明/提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/1ojydan1.png)

唯一的最优解如上图所示，图的上半部分为原图，底色为粉色的三个点为需要修改的边的起点；图的下半部分表示修改后的情况。

#### 样例 2 解释

存在多组最优解。其中一种是分别改变一条以 ``a``、``b`` 和 ``d`` 为起点的边，使他们分别连接到 ``b``、``a`` 和 `c`。

#### 样例 3 解释

图中有 $3$ 个点，无论如何修改边的终点，总会有一个人不在环里。


| 子任务 | 分值 | 数据范围 | 附加限制 |
|:----------:|:-------:|:-------------:|:-------------:|
|$1$|$21$|$2\leqslant N\leqslant 20$|.|
|$2$|$25$|$2\leqslant N\leqslant 100\, 000$|每个点都有一条入边（可能有自环）|
|$3$|$29$|$2\leqslant N\leqslant 100\, 000$|不存在两个点或更多个点构成的环|
|$4$|$25$|$2\leqslant N\leqslant 100\, 000$|.|



## 样例 #1

### 输入

```
8
leonard emmy
ada emmy
isaac leonard
emmy pierre
pierre bernhard
bernhard emmy
sofia karl
karl sofia```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
a c
b c
c d
d d```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
rocky scarlet
scarlet patrick
patrick rocky```

### 输出

```
-1
```

# AI分析结果



0. **题目翻译**

---

## [BalticOI 2018] 多角恋

### 题目描述

**题目译自 [BalticOI 2018](https://boi2018.progolymp.se/tasks/) Day1「Love Polygon」**

给一张 $N$ 个点的有向图，每个点的出度为 $1$。每次可以花费 $1$ 的代价修改图上的一条边的终点，也就是改变从一个点出发所到达的点。求最少需要花费多少代价，才能使这张图形成若干个两两不相交的二元环，并且图上的所有点都在某一个环里。

### 说明/提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/1ojydan1.png)

唯一的最优解如上图所示，图的上半部分为原图，底色为粉色的三个点为需要修改的边的起点；图的下半部分表示修改后的情况。

#### 样例 2 解释

存在多组最优解。其中一种是分别改变一条以 ``a``、``b`` 和 ``d`` 为起点的边，使他们分别连接到 ``b``、``a`` 和 `c`。

#### 样例 3 解释

图中有 $3$ 个点，无论如何修改边的终点，总会有一个人不在环里。

| 子任务 | 分值 | 数据范围 | 附加限制 |
|:----------:|:-------:|:-------------:|:-------------:|
|$1$|$21$|$2\leqslant N\leqslant 20$|.|
|$2$|$25$|$2\leqslant N\leqslant 100\, 000$|每个点都有一条入边（可能有自环）|
|$3$|$29$|$2\leqslant N\leqslant 100\, 000$|不存在两个点或更多个点构成的环|
|$4$|$25$|$2\leqslant N\leqslant 100\, 000$|.|

---

1. **唯一算法分类**  
   **无算法分类**（核心为基环树分解与贪心策略）

---

### 2. 综合分析与结论

#### 核心思路
1. **奇数判定**：若 $n$ 为奇数直接输出 $-1$，因为无法形成全二元环。
2. **预处理二元环**：直接标记已存在的二元环（无需修改）。
3. **拓扑排序处理链结构**：用队列处理入度为 $0$ 的节点，贪心修改其指向。
4. **环处理**：剩余未处理的部分为若干环，每个环的修改代价为 $\lceil \frac{\text{环长}}{2} \rceil$。

#### 关键难点与解决
- **环与链的混合处理**：通过拓扑排序剥离链结构，剩余部分为纯环。
- **贪心策略的正确性**：证明拓扑处理后的环部分必然可以按固定公式计算代价。
- **自环与无效边处理**：通过标记数组 `use[]` 和 `deg[]` 动态维护有效边。

#### 可视化设计要点
- **像素风格基环树**：用 8-bit 像素风格绘制节点，绿色表示已处理链结构，红色表示环。
- **动态拓扑过程**：队列节点用闪烁动画，修改边时播放 "哔" 音效。
- **环分割动画**：将环切割为若干线段，每段用不同颜色表示配对关系。
- **音效系统**：
  - 队列弹出节点时：短促 "滴" 声
  - 修改边时：合成器 "哔" 声
  - 环处理完成时：8-bit 胜利音效

---

### 3. 题解清单 (≥4星)

1. **cc123321（★★★★☆）**
   - **亮点**：代码简洁，通过拓扑排序与环分解实现线性复杂度
   - **关键代码**：
     ```cpp
     while(q.size()) { // 拓扑处理链结构
         int now = q.front(); q.pop();
         ++ans;
         if(!use[to[now]]) {
             use[to[now]] = 1;
             --deg[to[to[now]]];
             if(!deg[to[to[now]]] && !use[to[to[now]]])
                 q.push(to[to[now]]);
         }
     }
     ```

2. **Endt（★★★★☆）**
   - **亮点**：明确分步注释，强调贪心思想的正确性证明
   - **心得摘录**："深想一点就会发现，答案就是环中节点个数除以 $2$，这需要通过数学归纳法严格证明"

3. **ynxynx（★★★★☆）**
   - **亮点**：输入优化与特判处理完善，适合大规模数据
   - **核心逻辑**：
     ```cpp
     int k = pd(i); // 计算环长
     if(k & 1) ++ans;
     ans += k / 2;
     ```

---

### 4. 关键代码实现

**cc123321 的拓扑处理与环计算**  
```cpp
// 预处理已存在的二元环
for(int i=1; i<=n; i++)
    if(i == nex[nex[i]] && !use[i] && !use[nex[i]])
        use[i] = use[nex[i]] = 1;

// 拓扑排序处理链结构
for(int i=1; i<=n; i++)
    if(!deg[i] && !use[i]) q.push(i);

while(q.size()) {
    int now = q.front(); q.pop();
    ++ans;
    if(!use[nex[now]]) {
        use[nex[now]] = 1;
        --deg[nex[nex[now]]];
        if(!deg[nex[nex[now]]] && !use[nex[nex[now]]])
            q.push(nex[nex[now]]);
    }
}

// 处理剩余环
for(int i=1; i<=n; i++)
    if(!use[i]) {
        int k = solve(i); // 环长
        if(k <= 1) continue;
        ans += k/2 + (k%2 ? 1 : 0);
    }
```

---

### 5. 同类型题推荐
1. **P2661 信息传递**（基环树找最小环）
2. **P2607 骑士**（基环树DP）
3. **P5022 旅行**（基环树贪心）

---

### 6. 可视化与游戏化方案

#### Canvas 动画设计
```javascript
class LovePolygonAnim {
    constructor() {
        this.gridSize = 40; // 像素方块大小
        this.colors = {
            chain: "#00FF00", // 链结构-绿色
            ring: "#FF0000",  // 环结构-红色
            processed: "#8888FF" // 已处理-蓝色
        };
    }

    drawNode(x, y, state) {
        ctx.fillStyle = this.colors[state];
        ctx.fillRect(x * gridSize, y * gridSize, gridSize, gridSize);
    }

    playSound(type) {
        const sfx = {
            pop: new Audio("data:audio/wav;base64,UklGRl..."), 
            modify: new Audio("data:audio/wav;base64,UklGRl...")
        };
        sfx[type].play();
    }
}
```

#### 自动演示逻辑
```javascript
autoRun() {
    // 步骤1：标记已有二元环
    this.highlightPairs(); 
    
    // 步骤2：拓扑处理链
    while(queue.length) {
        let node = queue.pop();
        this.blinkNode(node); // 闪烁当前节点
        this.playSound('pop');
        this.drawEdgeModify(node); // 画边修改动画
    }
    
    // 步骤3：环切割
    rings.forEach(ring => {
        this.splitRing(ring); // 环形切割动画
        this.showCost(ring.length); // 显示计算代价
    });
}
```

---

### 7. 总结
本题通过基环树分解与贪心策略，在线性时间内解决了看似复杂的配对问题。核心在于将问题分解为链与环的独立处理，并通过数学归纳证明其正确性。可视化设计通过像素风格与音效反馈，将抽象的图论操作转化为直观的互动体验。

---
处理用时：95.67秒