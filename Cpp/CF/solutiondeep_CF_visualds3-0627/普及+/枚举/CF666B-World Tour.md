# 题目信息

# World Tour

## 题目描述

A famous sculptor Cicasso goes to a world tour!

Well, it is not actually a world-wide. But not everyone should have the opportunity to see works of sculptor, shouldn't he? Otherwise there will be no any exclusivity. So Cicasso will entirely hold the world tour in his native country — Berland.

Cicasso is very devoted to his work and he wants to be distracted as little as possible. Therefore he will visit only four cities. These cities will be different, so no one could think that he has "favourites". Of course, to save money, he will chose the shortest paths between these cities. But as you have probably guessed, Cicasso is a weird person. Although he doesn't like to organize exhibitions, he likes to travel around the country and enjoy its scenery. So he wants the total distance which he will travel to be as large as possible. However, the sculptor is bad in planning, so he asks you for help.

There are $ n $ cities and $ m $ one-way roads in Berland. You have to choose four different cities, which Cicasso will visit and also determine the order in which he will visit them. So that the total distance he will travel, if he visits cities in your order, starting from the first city in your list, and ending in the last, choosing each time the shortest route between a pair of cities — will be the largest.

Note that intermediate routes may pass through the cities, which are assigned to the tour, as well as pass twice through the same city. For example, the tour can look like that: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF666B/a1ec5df39eab48a433cbfa38b3e24c1e861f8538.png). Four cities in the order of visiting marked as overlines: $ [1,5,2,4] $ .

Note that Berland is a high-tech country. So using nanotechnologies all roads were altered so that they have the same length. For the same reason moving using regular cars is not very popular in the country, and it can happen that there are such pairs of cities, one of which generally can not be reached by car from the other one. However, Cicasso is very conservative and cannot travel without the car. Choose cities so that the sculptor can make the tour using only the automobile. It is guaranteed that it is always possible to do.

## 说明/提示

Let $ d(x,y) $ be the shortest distance between cities $ x $ and $ y $ . Then in the example $ d(2,1)=3,d(1,8)=7,d(8,7)=3 $ . The total distance equals $ 13 $ .

## 样例 #1

### 输入

```
8 9
1 2
2 3
3 4
4 1
4 5
5 6
6 7
7 8
8 5
```

### 输出

```
2 1 8 7
```

# AI分析结果



### 唯一算法分类
图论-最短路 + 枚举优化

---

### 综合分析与结论

#### 核心思路
1. **预处理全源最短路**：利用 BFS 处理所有点对之间的最短距离（边权相同）。
2. **候选节点预处理**：对每个节点维护「入边前三远」和「出边前三远」的候选节点，避免后续枚举冲突。
3. **枚举中间节点**：遍历所有可能的中间节点 b 和 c，结合候选列表快速找到不冲突的 a 和 d。

#### 解决难点
- **时间优化**：通过预处理将复杂度从 O(n⁴) 降为 O(n²)。
- **节点冲突处理**：通过维护前三大的候选节点，确保 a、b、c、d 不重复。

#### 可视化设计
- **动态枚举展示**：用像素风格显示当前枚举的 b 和 c，高亮候选 a 和 d。
- **路径动画**：用不同颜色线段表示 a→b、b→c、c→d 的路径，叠加长度数值。
- **音效反馈**：发现更优解时播放上扬音效，冲突时播放短促提示音。

---

### 题解评分（≥4星）

1. **sane1981（5星）**  
   - 思路清晰，预处理候选时使用排序取前三，代码注释详细。
   - 核心代码逻辑简洁，处理冲突条件严谨。
   - 优化方向明确，时间复杂度分析到位。

2. **WaterSun（4星）**  
   - 直接关联 CSP 原题，对比分析深入。
   - 代码结构清晰，预处理与候选选取逻辑明确。
   - 未处理极端冲突情况，但整体可行。

3. **sprads（4星）**  
   - 代码中维护动态候选列表，避免全排序。
   - 预处理时通过插入排序维护前三，减少冗余计算。
   - 可视化设计思路新颖，但代码部分未完全实现。

---

### 最优思路提炼

1. **候选列表剪枝**  
   - 对每个节点维护入边、出边前三远的候选，确保总能找到不冲突的组合。
   - 例如：候选数为 3 时，数学上可证明冲突情况至多消耗两个候选位。

2. **中间节点枚举**  
   - 仅枚举中间两个节点 b 和 c，将四层循环降为两层。
   - 计算总距离时直接查表，时间复杂度 O(1)。

3. **冲突检查优化**  
   - 候选遍历时跳过重复节点（如 a=c 或 d=b）。
   - 用 `continue` 语句提前终止无效组合的检查。

---

### 同类型题推荐

1. **P8817 [CSP-S 2022] 假期计划**  
   - 类似中间节点枚举，需处理四段路径的约束条件。

2. **P1144 最短路计数**  
   - 最短路径的动态维护与统计。

3. **P1462 通往奥格瑞玛的道路**  
   - 结合最短路与条件筛选的复合问题。

---

### 核心代码实现（sane1981 题解）

```cpp
for (int x2=1;x2<=n;x2++) {
    for (int x3=1;x3<=n;x3++){ // 枚举b,c
        if (x2==x3 || dis[x2][x3]==-1) continue;
        for (int k1=0; k1<3 && k1<B[x2].size(); k1++){ // 前3大入边候选
            int x1 = B[x2][k1].second; // 候选a
            if (x1 == x3 || x1 == x2) continue;
            for (int k2=0; k2<3 && k2<A[x3].size(); k2++){ // 前3大出边候选
                int x4 = A[x3][k2].second; // 候选d
                if (x4==x1 || x4==x2 || x4==x3) continue;
                // 更新最大距离及路径节点
                if (sum < dis[x1][x2] + dis[x2][x3] + dis[x3][x4]) {
                    sum = dis[x1][x2] + dis[x2][x3] + dis[x3][x4];
                    ans[1]=x1; ans[2]=x2; ans[3]=x3; ans[4]=x4;
                }
            }
        } 
    }
}
```

---

### 可视化算法演示

```javascript
// 伪代码：基于 Canvas 的动画框架
class Visualizer {
    constructor(nodes) {
        this.nodes = nodes; // 节点坐标信息
        this.currentBC = { b: null, c: null };
        this.candidates = { a: [], d: [] };
    }

    // 高亮当前枚举的 b 和 c
    highlightBC(b, c) {
        drawNode(b, 'blue');
        drawNode(c, 'green');
    }

    // 显示候选 a 和 d 的路径
    showCandidates(aList, dList) {
        aList.forEach(a => drawPath(a, b, 'red'));
        dList.forEach(d => drawPath(c, d, 'yellow'));
    }

    // 播放音效
    playSound(type) {
        if (type === 'improve') audio.success.play();
        else if (type === 'conflict') audio.warn.play();
    }
}
```

#### 复古像素风格设计
- **调色板**：16 色，主色为 #FF69B4（粉色高亮）、#00FF00（绿路径）。
- **网格布局**：节点按力导向算法分布，边用 1px 宽线段。
- **音效**：8-bit 风格音效，使用 Web Audio API 触发。

---
处理用时：160.05秒