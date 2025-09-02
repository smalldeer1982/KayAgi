# 题目信息

# Railway System

## 题目描述

As for the technology in the outside world, it is really too advanced for Gensokyo to even look up to.

—Yasaka Kanako, Symposium of Post-mysticism



This is an interactive problem.

Under the direct supervision of Kanako and the Moriya Shrine, the railway system of Gensokyo is finally finished. GSKR (Gensokyo Railways) consists of $ n $ stations with $ m $ bidirectional tracks connecting them. The $ i $ -th track has length $ l_i $ ( $ 1\le l_i\le 10^6 $ ). Due to budget limits, the railway system may not be connected, though there may be more than one track between two stations.

The value of a railway system is defined as the total length of its all tracks. The maximum (or minimum) capacity of a railway system is defined as the maximum (or minimum) value among all of the currently functional system's [full spanning forest](https://en.wikipedia.org/wiki/Spanning_tree#Spanning_forests).

In brief, full spanning forest of a graph is a spanning forest with the same connectivity as the given graph.

Kanako has a simulator only able to process no more than $ 2m $ queries. The input of the simulator is a string $ s $ of length $ m $ , consisting of characters 0 and/or 1. The simulator will assume the $ i $ -th track functional if $ s_i= $ 1. The device will then tell Kanako the maximum capacity of the system in the simulated state.

Kanako wants to know the the minimum capacity of the system with all tracks functional with the help of the simulator.

The structure of the railway system is fixed in advance. In other words, the interactor is not adaptive.

## 说明/提示

Here is the graph of the example, satisfying $ l_i=i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1687B/91ed2595ccd5b28c792f8d64dc85c03cf1c73365.png)

## 样例 #1

### 输入

```
5 4

0

5

9

7```

### 输出

```
? 0000

? 1110

? 1111

? 1101

! 7```

# AI分析结果



**算法分类**：最小生成树/Kruskal算法

---

### **综合分析与结论**
**核心思路**：  
1. **确定边权**：通过 m 次单边查询获取所有边权值。  
2. **排序边**：按边权从小到大排序，模拟 Kruskal 的贪心策略。  
3. **动态维护生成森林**：每次尝试加入一条边，通过查询结果判断该边是否连接两个新连通块。若最大生成森林的总权值增加量等于当前边权，则保留该边。  

**解决难点**：  
- 传统 Kruskal 使用并查集判断连通性，此处通过查询总权值变化间接判断。  
- 总查询次数严格控制在 2m 次（m 次边权查询 + m 次动态维护）。  

**可视化设计**：  
- **动态高亮**：当前处理的边以绿色高亮，已加入生成树的边用蓝色，被拒绝的边用红色。  
- **权值变化显示**：每次查询后，总权值以浮动数字更新，配合音效（加入成功时播放清脆音效，失败时低沉音效）。  
- **复古像素风格**：节点用圆形像素块表示，边用线条连接，背景音乐为 8-bit 风格循环。  

---

### **题解清单（≥4星）**
1. **GaryH（5星）**  
   - **亮点**：代码简洁，利用 `lst` 变量复用查询结果，逻辑清晰。  
   - **核心代码**：动态维护 `s` 字符串表示当前边集，通过 `x == lst + e[i].fi` 判断是否保留边。  

2. **StayAlone（4.5星）**  
   - **亮点**：直接模拟 Kruskal，代码高度可读，变量命名清晰。  
   - **心得引用**：*“与 Kruskal 的唯一区别在于用查询代替并查集”*  

3. **ncwzdlsd（4星）**  
   - **亮点**：通过 `tmp1 != sum + ans[i].fst` 判断边是否冗余，代码紧凑。  

---

### **最优思路提炼**
**关键技巧**：  
1. **边权排序 + 动态查询**：将并查集的连通性判断转化为总权值变化比较。  
2. **贪心复用查询结果**：每次查询后保留当前最大生成森林的总权值，避免重复计算。  

**代码实现思想**：  
```cpp
// 核心代码片段（GaryH 题解）
sort(e + 1, e + m + 1); // 按边权排序
int mst = 0, lst = 0;
rep(i, 1, m) {
    s[e[i].se - 1] = '1'; // 尝试加入当前边
    int x = qry();        // 查询当前最大生成森林权值
    if (x == lst + e[i].fi) mst += e[i].fi; // 判断是否保留
    lst = x; // 更新历史总权值
}
```

---

### **同类型题与推荐题目**
**类似算法套路**：  
- 交互式贪心问题，通过有限查询推断结构。  
- 动态维护生成树性质（如最大/最小边权）。  

**推荐题目**：  
1. [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)  
2. [P2872 Building Roads S](https://www.luogu.com.cn/problem/P2872)（最大生成树应用）  
3. [CF1628D1 Game on Sum (Easy Version)](https://codeforces.com/problemset/problem/1628/D1)（交互策略问题）  

---

### **可视化与算法演示**
**动画方案**：  
1. **网格布局**：节点按网格排列，边以线段连接，当前边高亮。  
2. **颜色反馈**：  
   - 绿色：当前处理边，若成功加入则保留为蓝色，否则变红。  
   - 灰色：未处理的边。  
3. **音效触发**：  
   - 成功加入：`beep(440, 100)`（高音）  
   - 失败：`beep(220, 100)`（低音）  

**复古风格实现**：  
```javascript
// 伪代码：Canvas绘制边与节点
function drawEdge(edge, color) {
    ctx.strokeStyle = color;
    ctx.beginPath();
    ctx.moveTo(node1.x, node1.y);
    ctx.lineTo(node2.x, node2.y);
    ctx.stroke();
}

// 自动演示逻辑
let currentEdge = 0;
function autoPlay() {
    if (currentEdge >= edges.length) return;
    let edge = edges[currentEdge];
    drawEdge(edge, "#00FF00"); // 高亮当前边
    setTimeout(() => {
        let newSum = query(edge);
        if (newSum === lastSum + edge.weight) {
            drawEdge(edge, "#0000FF"); // 保留为蓝色
            lastSum = newSum;
        } else {
            drawEdge(edge, "#FF0000"); // 标记为红色
        }
        currentEdge++;
        autoPlay();
    }, 1000);
}
```

---

**总结**：通过巧妙地将 Kruskal 算法的连通性判断转化为查询结果的数值比较，此方法在保证正确性的同时严格满足交互次数限制，是贪心策略与交互问题结合的经典案例。

---
处理用时：98.86秒