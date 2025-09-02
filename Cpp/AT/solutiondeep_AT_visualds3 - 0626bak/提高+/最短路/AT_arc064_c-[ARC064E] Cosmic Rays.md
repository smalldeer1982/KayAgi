# 题目信息

# [ARC064E] Cosmic Rays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc064/tasks/arc064_c

$ x $$ y $ 平面があります。 すぬけ君は座標 $ (x_s,\ y_s) $ から座標 $ (x_t,\ y_t) $ まで移動しようとしています。 すぬけ君は好きな向きへ速さ $ 1 $ で動くことができます。 なお、すぬけ君は大きさのない点と見なすことにします。

平面上には $ N $ 個の円形のバリアが張ってあります。 $ i $ 番目のバリアは中心が $ (x_i,\ y_i) $ で半径が $ r_i $ です。 バリアは互いに重なっていたり、互いを含んでいたりすることがあります。

平面上の各座標について、その座標がどのバリアの内部にも含まれない場合、その座標には宇宙線が降り注いでいます。

すぬけ君は移動中にできるだけ宇宙線を浴びたくないので、宇宙線を浴びる時間が最小になるように移動します。 すぬけ君が移動中に宇宙線を浴びる時間の最小値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ -10^9\ <\ =\ x_s,\ y_s,\ x_t,\ y_t\ <\ =\ 10^9 $
- $ (x_s,\ y_s) $ ≠ $ (x_t,\ y_t) $
- $ 1\ <\ =N\ <\ =1,000 $
- $ -10^9\ <\ =\ x_i,\ y_i\ <\ =\ 10^9 $
- $ 1\ <\ =\ r_i\ <\ =\ 10^9 $

### Sample Explanation 1

たとえば、図のように移動すればよいです。 !\[e9c630751968b7051df5750b7ddc0e07.png\](https://atcoder.jp/img/arc064/e9c630751968b7051df5750b7ddc0e07.png)

### Sample Explanation 2

たとえば、図のように移動すればよいです。 !\[fb82f6f4df5b22cffb868ce6333277aa.png\](https://atcoder.jp/img/arc064/fb82f6f4df5b22cffb868ce6333277aa.png)

### Sample Explanation 3

たとえば、図のように移動すればよいです。 !\[d09006720c225cbe69eae3fd9c186e67.png\](https://atcoder.jp/img/arc064/d09006720c225cbe69eae3fd9c186e67.png)

## 样例 #1

### 输入

```
-2 -2 2 2

1

0 0 1```

### 输出

```
3.6568542495```

## 样例 #2

### 输入

```
-2 0 2 0

2

-1 0 2

1 0 2```

### 输出

```
0.0000000000```

## 样例 #3

### 输入

```
4 -2 -2 4

3

0 0 2

4 0 1

0 4 1```

### 输出

```
4.0000000000```

# AI分析结果



## 算法分类
**图论-最短路（Dijkstra算法）**

---

## 综合分析与结论
### 核心思路与难点
- **问题转化**：将几何问题转化为图论问题。每个圆形屏障视为图中的一个节点，起点和终点视为半径0的特殊节点。两节点间的边权为两圆心距离减去两圆半径之和（若为负则取0）。
- **几何证明**：最优路径必定由圆心之间的直线段构成。因为沿圆心连线暴露时间最短，相交圆之间暴露时间为0。
- **难点突破**：正确推导边权计算公式 `max(0, distance - r1 - r2)` 并处理浮点数精度。

### 可视化设计思路
- **动画演示**：以网格平面为背景，动态绘制圆形屏障（不同颜色区分），起点/终点标记为特殊图标。Dijkstra算法执行时：
  1. **节点高亮**：当前处理的节点以黄色闪烁，已确定最短路径的节点变为绿色。
  2. **边权显示**：边权实时计算并标注，负值边权显示为0并标红。
  3. **路径回溯**：最终路径以红色线段连接，展示屏障间的“最优穿梭”。
- **像素风格**：使用8位色块表示节点，边权计算过程伴随经典音效（如节点扩展时的“哔”声，路径找到时的胜利音效）。

---

## 题解评分 (≥4星)
1. **Noir_ (5星)**  
   - **亮点**：详细推导几何最优性，代码分情况处理n=1，注释清晰。  
   - **心得**：强调初始边权必须与0取max，避免负权错误。

2. **Accelessar (4.5星)**  
   - **亮点**：代码简洁，使用STL优先队列优化，处理浮点初始值为DBL_MAX。  
   - **技巧**：结构体封装圆心属性，增强可读性。

3. **james1BadCreeper (4星)**  
   - **亮点**：暴力建图后直接Dijkstra，代码短小精悍。  
   - **注意点**：显式处理相交圆情况，确保边权非负。

---

## 最优思路与技巧提炼
1. **模型转化**：将几何路径问题转化为图论最短路，通过圆心连线简化计算。
2. **边权计算**：`边权 = max(0, 欧氏距离 - r_i - r_j)`，确保相交圆边权为0。
3. **特殊节点处理**：起点/终点视为半径0的圆，统一节点编号。
4. **高效实现**：优先队列优化Dijkstra，时间复杂度O(n² + n log n)。

---

## 同类型题目推荐
1. **P1144 最短路计数**（基础最短路应用）
2. **P1337 [JSOI2004]平衡点**（几何与最优化的结合）
3. **P4644 [USACO05DEC]Cleaning Shifts**（区间覆盖转化为图论）

---

## 个人心得摘录
- **Noir_**：调试时发现初始化距离不足，改用`fill`替代`memset`处理double数组。
- **Accelessar**：使用`DBL_MAX`避免初始值过小导致WA，强调浮点精度处理。
- **james1BadCreeper**：提醒注意勾股定理中坐标差平方可能溢出，需用`long long`存储中间值。

---

## 可视化与算法演示
```html
<!DOCTYPE html>
<html>
<body>
<canvas id="canvas" width="800" height="600"></canvas>
<script>
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
let nodes = []; // {x, y, r, id}
let edges = [];
let path = [];

// 初始化示例数据（起点、终点、3个屏障）
function initData() {
    nodes = [
        {x:100, y:300, r:0, id:0}, {x:700, y:300, r:0, id:1},
        {x:300, y:200, r:50, id:2}, {x:500, y:400, r:80, id:3}
    ];
    // 计算所有边
    for(let i=0; i<nodes.length; i++) {
        for(let j=i+1; j<nodes.length; j++) {
            let dx = nodes[i].x - nodes[j].x;
            let dy = nodes[i].y - nodes[j].y;
            let dist = Math.sqrt(dx*dx + dy*dy);
            edges.push({
                from: i, to: j,
                weight: Math.max(0, dist - nodes[i].r - nodes[j].r)
            });
        }
    }
}

function draw() {
    ctx.fillStyle = '#000';
    ctx.fillRect(0, 0, 800, 600);
    
    // 绘制边
    edges.forEach(e => {
        ctx.strokeStyle = e.weight > 0 ? '#666' : '#f00';
        ctx.beginPath();
        ctx.moveTo(nodes[e.from].x, nodes[e.from].y);
        ctx.lineTo(nodes[e.to].x, nodes[e.to].y);
        ctx.stroke();
    });
    
    // 绘制节点
    nodes.forEach(n => {
        ctx.fillStyle = n.r === 0 ? '#0f0' : '#00f';
        ctx.beginPath();
        ctx.arc(n.x, n.y, 5, 0, Math.PI*2);
        ctx.fill();
    });
}

initData();
draw();
</script>
</body>
</html>
```

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
struct Circle { double x, y, r; } nodes[N];
vector<pair<int, double>> adj[N];
double dist[N];

double calcDist(Circle a, Circle b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return max(0.0, sqrt(dx*dx + dy*dy) - a.r - b.r);
}

void dijkstra(int s) {
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    fill(dist, dist + N, DBL_MAX);
    dist[s] = 0;
    pq.emplace(0, s);
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
}

int main() {
    int n; Circle s, t;
    cin >> s.x >> s.y >> t.x >> t.y >> n;
    nodes[0] = s; nodes[0].r = 0;
    nodes[1] = t; nodes[1].r = 0;
    for (int i=2; i<n+2; ++i)
        cin >> nodes[i].x >> nodes[i].y >> nodes[i].r;
    
    for (int i=0; i<n+2; ++i)
        for (int j=i+1; j<n+2; ++j) {
            double w = calcDist(nodes[i], nodes[j]);
            adj[i].emplace_back(j, w);
            adj[j].emplace_back(i, w);
        }
    
    dijkstra(0);
    printf("%.10lf\n", dist[1]);
}
```

---
处理用时：118.01秒