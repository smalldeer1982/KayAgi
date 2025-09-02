# 题目信息

# Buy a Ticket

## 题目描述

Musicians of a popular band "Flayer" have announced that they are going to "make their exit" with a world tour. Of course, they will visit Berland as well.

There are $ n $ cities in Berland. People can travel between cities using two-directional train routes; there are exactly $ m $ routes, $ i $ -th route can be used to go from city $ v_{i} $ to city $ u_{i} $ (and from $ u_{i} $ to $ v_{i} $ ), and it costs $ w_{i} $ coins to use this route.

Each city will be visited by "Flayer", and the cost of the concert ticket in $ i $ -th city is $ a_{i} $ coins.

You have friends in every city of Berland, and they, knowing about your programming skills, asked you to calculate the minimum possible number of coins they have to pay to visit the concert. For every city $ i $ you have to compute the minimum number of coins a person from city $ i $ has to spend to travel to some city $ j $ (or possibly stay in city $ i $ ), attend a concert there, and return to city $ i $ (if $ j≠i $ ).

Formally, for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938D/035d166bda223ecd5c31eb614a76bdcc9b8fe8c4.png) you have to calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938D/f2e29a8bb6e05026242d6e3afeeabb7241997635.png), where $ d(i,j) $ is the minimum number of coins you have to spend to travel from city $ i $ to city $ j $ . If there is no way to reach city $ j $ from city $ i $ , then we consider $ d(i,j) $ to be infinitely large.

## 样例 #1

### 输入

```
4 2
1 2 4
2 3 7
6 20 1 25
```

### 输出

```
6 14 1 25 
```

## 样例 #2

### 输入

```
3 3
1 2 1
2 3 1
1 3 1
30 10 20
```

### 输出

```
12 10 12 
```

# AI分析结果



### 唯一算法分类
**最短路 + 虚拟源点**

---

### 综合分析与结论
**核心思路**：将点权转化为虚拟源点的边权，通过一次 Dijkstra 求出所有城市的最优解。  
**关键步骤**：
1. **虚拟源点**：建立虚拟源点 0，向每个城市 i 连一条边权为 a_i 的单向边。
2. **边权处理**：原图中的双向边权乘 2（往返费用）。
3. **单源最短路**：从虚拟源点 0 出发，跑一次 Dijkstra，结果即为每个城市的最小费用。

**难点**：  
- 如何将点权与路径权结合，避免多次单源最短路的高时间复杂度。
- 理解虚拟源点的作用：将每个城市的票价视为从虚拟源点到该城市的一条边权。

**解决方案**：  
通过虚拟源点统一处理所有城市的票价，使最优解对应虚拟源点到各城市的最短路径。

---

### 题解清单（≥4星）

1. **傅思维666（★★★★★）**  
   - **亮点**：详细解释虚拟源点的思路，附带代码注释，强调边权乘 2 和 long long 的重要性。
   - **代码**：完整可运行，结构清晰。

2. **Mr_think（★★★★☆）**  
   - **亮点**：图示辅助理解，正确性证明简洁，推荐同类题目。
   - **代码**：使用优先队列优化，可读性高。

3. **FREEH（★★★★）**  
   - **亮点**：提供两种方法对比，代码规范，注释明确。
   - **心得**：强调虚拟源点的思想。

---

### 最优思路与技巧提炼
**核心技巧**：  
- **虚拟源点**：将点权转化为虚拟源点的边权，统一处理所有起点。
- **边权设计**：将原边权乘 2（往返），虚拟源点边权为票价（单程）。
- **单次 Dijkstra**：时间复杂度 O((n+m) log n)，适合大数据范围。

**关键代码片段**：
```cpp
// 虚拟源点连边
for (int i=1; i<=n; i++) {
    ll w; scanf("%lld", &w);
    add(0, i, w); // 虚拟源点 0 连向城市 i，边权为票价
}

// 原图边权乘 2
for (int i=1; i<=m; i++) {
    int u, v; ll w;
    scanf("%d%d%lld", &u, &v, &w);
    add(u, v, 2*w); // 往返费用
    add(v, u, 2*w);
}
```

---

### 同类型题与算法套路
**相似问题**：  
1. **昂贵的聘礼**：虚拟源点处理点权，转化为最短路问题。
2. **多源汇最短路**：通过虚拟节点统一处理多个起点。

**推荐题目**：  
1. [P1629 邮递员送信](https://www.luogu.com.cn/problem/P1629)  
2. [P4568 飞行路线](https://www.luogu.com.cn/problem/P4568)  
3. [P1265 公路修建](https://www.luogu.com.cn/problem/P1265)

---

### 个人心得摘录
- **long long 陷阱**：多个题解因未开 long long 导致 WA，需注意数据范围。
- **翻译歧义**：原题要求往返费用，部分中文翻译未明确说明，需仔细读题。

---

### 可视化与算法演示
**动画设计**：  
1. **虚拟源点高亮**：用红色节点表示虚拟源点 0，蓝色节点表示普通城市。  
2. **边权显示**：虚拟边显示票价，原边显示 2 倍路费。  
3. **Dijkstra 过程**：  
   - **优先队列**：动态显示队列中的节点和当前最短距离。  
   - **路径更新**：用绿色高亮当前处理的边，黄色标记已确定最短路的节点。  

**复古像素风格**：  
- **调色板**：8 位风格，红（虚拟源点）、蓝（城市）、绿（最短路径）。  
- **音效**：每次更新节点时播放“滴”声，找到最短路径时播放胜利音效。  

**交互功能**：  
- **步进控制**：支持暂停/继续/单步执行，速度可调。  
- **自动演示**：AI 自动运行，模拟 Dijkstra 的扩展过程。  

**Canvas 示例**：  
```javascript
// 伪代码：绘制虚拟源点和边
ctx.fillStyle = '#FF0000'; // 红色虚拟源点
ctx.fillRect(0, canvasHeight/2, 10, 10);

for (let city of cities) {
    ctx.fillStyle = '#0000FF'; // 蓝色城市
    ctx.fillRect(city.x, city.y, 10, 10);
    drawDashedLine(0, city, a_i); // 虚线表示虚拟边
}
```

---

**总结**：通过虚拟源点巧妙转化问题，结合一次高效的最短路算法，解决了大规模数据下的最优解计算。

---
处理用时：66.16秒