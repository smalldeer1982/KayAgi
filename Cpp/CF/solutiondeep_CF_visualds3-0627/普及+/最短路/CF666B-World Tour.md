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



# 算法分类  
**最短路径（BFS） + 枚举优化**

---

## 综合分析与结论  
### 核心算法流程  
1. **预处理全源最短路**：通过 BFS 计算所有点对的最短距离 $d(i,j)$  
2. **构建候选列表**：对每个点 $u$，分别存储：  
   - 前驱列表：所有能到达 $u$ 的点中，$d(v,u)$ 前 3 大的点  
   - 后继列表：所有 $u$ 能到达的点中，$d(u,v)$ 前 3 大的点  
3. **枚举中间点**：遍历所有可能的中间点对 $(b,c)$  
4. **组合候选点**：从前驱列表中选 $a$，从后继列表中选 $d$，确保 $a,b,c,d$ 互不重复  
5. **计算最大值**：记录最大的 $d(a,b) + d(b,c) + d(c,d)$  

### 解决难点  
- **时间复杂度优化**：通过预处理候选列表，将复杂度从 $O(n^4)$ 降至 $O(n^2)$  
- **重复冲突处理**：候选列表中存储前 3 大的点，确保总能找到不重复的合法组合  

### 可视化设计思路  
1. **像素风格动画**：  
   - 用不同颜色方块表示城市（红色：起点 $a$，黄色：中间点 $b/c$，蓝色：终点 $d$）  
   - 高亮当前枚举的中间点对 $(b,c)$，动态绘制候选的 $a$ 和 $d$  
2. **关键步骤音效**：  
   - 发现更大路径时播放上升音效（类似 FC 金币音）  
   - 候选冲突时播放短促“错误”音效  
3. **自动演示模式**：  
   - 按 $b,c$ 的枚举顺序自动播放候选组合过程  
   - 可暂停观察当前最优解的路径连接关系  

---

## 题解清单 (≥4星)  
### 1. Juanzhang（★★★★☆）  
**亮点**：  
- 预处理前三远的候选点解决冲突  
- 代码逻辑清晰，使用 `pre[j]` 和 `nxt[k]` 分别存储前驱/后继  
**核心代码**：  
```cpp  
for (int j = 1; j <= n; j++) {  
    for (int k = 1; k <= n; k++) {  
        if (j == k) continue;  
        for (pii p1 : pre[j]) { // 前驱候选  
            int i = p1.sec;  
            for (pii p2 : nxt[k]) { // 后继候选  
                int l = p2.sec;  
                if (i,l 无冲突) 更新最大值  
            }  
        }  
    }  
}  
```

### 2. sane1981（★★★★☆）  
**亮点**：  
- 与 CSP-S 2022 假期计划对比，强调候选点的冲突处理  
- 使用双排序分别处理前驱/后继列表  
**核心代码**：  
```cpp  
sort(A[i].begin(), A[i].end(), cmp); // 按 d(i,j) 降序  
sort(B[i].begin(), B[i].end(), cmp); // 按 d(j,i) 降序  
```

### 3. sprads（★★★★☆）  
**亮点**：  
- 预处理前三远的候选点并动态调整顺序  
- 使用独立数组 `to[i][j]` 和 `fr[i][j]` 存储前驱/后继  
**核心代码**：  
```cpp  
for (int k = 0; k < 3; k++) // 动态插入候选  
    if (dis[i][j] > 当前候选) 调整排序  
```

---

## 最优思路提炼  
1. **候选列表剪枝**：每个点只保留前 3 大的候选，解决枚举冲突问题  
2. **双指针冲突处理**：当候选点重复时，交替尝试前驱和后继的次优解  
3. **方向分离存储**：分别维护每个点的最大前驱（进入该点的路径）和最大后继（离开该点的路径）  

---

## 同类型题与套路  
- **类似题目**：  
  - P8817 [CSP-S 2022] 假期计划（预处理 4 段路径的最优组合）  
  - P5304 [GXOI/GZOI2019] 旅行者（多源最短路 + 候选点剪枝）  
- **通用套路**：  
  1. 预处理所有点对的最短路径  
  2. 对中间点枚举，通过候选列表优化组合选择  
  3. 利用排序和截断操作降低时间复杂度  

---

## 推荐题目  
1. [洛谷 P8817](https://www.luogu.com.cn/problem/P8817)  
2. [洛谷 P5304](https://www.luogu.com.cn/problem/P5304)  
3. [洛谷 P2149](https://www.luogu.com.cn/problem/P2149)（最短路 + 路径计数）  

---

## 个人心得摘录  
> “考试时想到预处理前三候选，但漏掉了交替选择次优解的情况，调试后发现必须同时处理前驱和后继的冲突”——sprads  
> “将问题拆解为中间两点枚举后，代码复杂度骤降”——WaterSun  

---

## 可视化代码片段（JS 伪代码）  
```javascript  
// 绘制候选点动画  
function drawCandidate(a, b, c, d) {  
    ctx.fillStyle = "#FF0000"; // 红色：起点 a  
    ctx.fillRect(a.x, a.y, 20, 20);  
    ctx.fillStyle = "#FFFF00"; // 黄色：中间点 b/c  
    ctx.fillRect(b.x, b.y, 20, 20);  
    ctx.fillRect(c.x, c.y, 20, 20);  
    ctx.fillStyle = "#0000FF"; // 蓝色：终点 d  
    ctx.fillRect(d.x, d.y, 20, 20);  
    playSound("coin.wav"); // 发现更优解时播放音效  
}  
```

---
处理用时：70.24秒