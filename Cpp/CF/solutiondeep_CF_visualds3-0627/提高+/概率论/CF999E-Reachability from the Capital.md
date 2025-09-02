# 题目信息

# Reachability from the Capital

## 题目描述

在 Berland 有 $n$ 座城市和 $m$ 条道路，每条道路连接着一对城市。

Berland 的道路都是**单向**的

为了能让首都能够到达所有的城市，最少需要新修建多少新道路？

新道路也是单向的

## 说明/提示

样例 1：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF999E/cfa72c5c5f72e8ccb5babda1e509efae921c1e73.png)

例如，您可以添加道路 ( 6, 4 ) , ( 7 , 9 ) , ( 1 , 7 )，以使从 $s = 1$ 可到达所有城市。
样例 2：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF999E/62d78c6df2be4fcc0d6c17ba856e4ad627c47d5f.png)

在此样例中，您可以添加道路（5 , 1），（5 , 2），（5 , 3），（5 , 4）中的任何一条，以使可从 $s = 5$ 到达所有城市。

## 样例 #1

### 输入

```
9 9 1
1 2
1 3
2 3
1 5
5 6
6 1
1 8
9 8
7 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 4 5
1 2
2 3
3 4
4 1
```

### 输出

```
1
```

# AI分析结果



### 唯一算法分类  
**强连通分量（SCC）与缩点**

---

### 综合分析与结论  
**核心思路**  
1. 将所有城市通过 Tarjan 算法缩点为强连通分量（SCC），同一 SCC 内的城市互相可达。  
2. 统计缩点后每个 SCC 的入度。  
3. 答案等于入度为 0 的 SCC 数量，减去首都所在 SCC 的入度是否为 0 的修正项。  

**解决难点**  
- **缩点后的入度统计**：需遍历原始边，仅在不同 SCC 之间统计入度。  
- **特判首都所在 SCC**：若首都所在 SCC 入度为 0，需从答案中减去 1（首都无需额外连边）。  

**可视化设计**  
1. **Tarjan 缩点动画**：  
   - 用不同颜色块表示不同 SCC，节点展开为网格结构。  
   - 栈操作时高亮当前节点，回溯时显示 low 值更新过程。  
2. **DAG 与入度展示**：  
   - 缩点后的 DAG 以箭头连接，每个节点标注入度值。  
   - 入度为 0 的节点闪烁红色，首都所在节点标记为金色。  
3. **复古像素风格**：  
   - 使用 8-bit 音效：缩点时播放“滴答”声，入度更新时触发“咔哒”声。  
   - Canvas 绘制网格化 SCC，边添加时显示像素箭头生长动画。  

---

### 题解清单 (≥4星)  
1. **作者：MyukiyoMekya（5星）**  
   - **亮点**：DFS 标记可达 SCC，逻辑清晰，代码模块化。  
   - **代码可读性**：结构分明，缩点与入度统计分离。  

2. **作者：让风忽悠你（4星）**  
   - **亮点**：注释详细，变量命名规范，特判逻辑明确。  
   - **个人心得**："注意首都所在 SCC 的入度是否为 0，否则答案会多算 1 条边。"  

3. **作者：chihik（4星）**  
   - **亮点**：代码简洁，直接遍历边统计入度，无冗余操作。  

---

### 最优思路提炼  
**关键步骤与技巧**  
1. **缩点优化**：将 SCC 视为单个节点，简化图为 DAG。  
2. **入度统计法**：仅需遍历原始边，统计跨 SCC 边的入度。  
3. **特判修正项**：若首都所在 SCC 入度为 0，答案需减 1。  

**代码实现核心**  
```cpp
// Tarjan 缩点核心（作者：chihik）
void tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    S.push(x); inq[x] = 1;
    for (int v : G[x]) {
        if (!dfn[v]) tarjan(v), low[x] = min(low[x], low[v]);
        else if (inq[v]) low[x] = min(low[x], dfn[v]);
    }
    if (dfn[x] == low[x]) {
        cntc++;
        while (S.top() != x) {
            col[S.top()] = cntc;
            inq[S.top()] = 0; S.pop();
        }
        col[x] = cntc; inq[x] = 0; S.pop();
    }
}

// 统计入度并计算答案（作者：attack）
for (int i=1; i<=N; i++) 
    for (int j=head[i]; j!=-1; j=E[j].nxt) 
        if (color[E[j].u] != color[E[j].v])
            inder[color[E[j].v]]++;
ans = 0;
for (int i=1; i<=colornum; i++)
    if (inder[i] == 0) ans++;
if (inder[color[S]] == 0) ans--;
```

---

### 同类型题与推荐  
1. **类似算法套路**：缩点后统计入度/出度（如 P3387 缩点、P2746 校园网）。  
2. **推荐题目**：  
   - P3387 【模板】缩点  
   - P2746 [USACO5.3] 校园网  
   - P1262 间谍网络  

---

### 个人心得摘录  
- **Schwarzkopf_Henkal**："若一个 SCC 入度为 0 且非首都所在，必加一条边，这是覆盖所有情况的最简策略。"  
- **LSG_waterlyf**："贪心选择最大可达集合的 DFS 策略，本质是模拟最优覆盖路径。"  

---

### 可视化与复古游戏化设计  
**动画方案**  
1. **Tarjan 过程**：  
   - 节点显示为像素方块，压栈时变黄，回溯时变绿。  
   - 栈操作音效：8-bit "blip" 声。  
2. **DAG 构建**：  
   - 缩点后节点用色块表示，边用闪烁箭头连接。  
   - 入度更新时显示数字浮动效果，音效为 "beep"。  
3. **自动演示模式**：  
   - 按空格键单步执行，Enter 键自动播放。  
   - 成功时播放胜利音效，背景音乐为 Chiptune 风格循环。  

**代码片段（Canvas 绘制）**  
```javascript
// 绘制 SCC 节点（伪代码）
function drawSCC(ctx, scc) {
    scc.nodes.forEach(node => {
        ctx.fillStyle = scc.color;
        ctx.fillRect(node.x * 30, node.y * 30, 25, 25);
        ctx.fillStyle = '#000';
        ctx.fillText(scc.id, node.x * 30 + 8, node.y * 30 + 15);
    });
}
// 播放音效（Web Audio API）
function playSound(freq) {
    let oscillator = audioCtx.createOscillator();
    oscillator.type = 'square';
    oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
    oscillator.connect(audioCtx.destination);
    oscillator.start();
    oscillator.stop(audioCtx.currentTime + 0.1);
}
```

---
处理用时：73.53秒