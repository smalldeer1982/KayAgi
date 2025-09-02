# 题目信息

# The Child and Toy

## 题目描述

On Children's Day, the child got a toy from Delayyy as a present. However, the child is so naughty that he can't wait to destroy the toy.

The toy consists of $ n $ parts and $ m $ ropes. Each rope links two parts, but every pair of parts is linked by at most one rope. To split the toy, the child must remove all its parts. The child can remove a single part at a time, and each remove consume an energy. Let's define an energy value of part $ i $ as $ v_{i} $ . The child spend $ v_{f1}+v_{f2}+...+v_{fk} $ energy for removing part $ i $ where $ f_{1},f_{2},...,f_{k} $ are the parts that are directly connected to the $ i $ -th and haven't been removed.

Help the child to find out, what is the minimum total energy he should spend to remove all $ n $ parts.

## 说明/提示

One of the optimal sequence of actions in the first sample is:

- First, remove part $ 3 $ , cost of the action is $ 20 $ .
- Then, remove part $ 2 $ , cost of the action is $ 10 $ .
- Next, remove part $ 4 $ , cost of the action is $ 10 $ .
- At last, remove part $ 1 $ , cost of the action is $ 0 $ .

So the total energy the child paid is $ 20+10+10+0=40 $ , which is the minimum.

In the second sample, the child will spend $ 400 $ no matter in what order he will remove the parts.

## 样例 #1

### 输入

```
4 3
10 20 30 40
1 4
1 2
2 3
```

### 输出

```
40
```

## 样例 #2

### 输入

```
4 4
100 100 100 100
1 2
2 3
2 4
3 4
```

### 输出

```
400
```

## 样例 #3

### 输入

```
7 10
40 10 20 10 20 80 40
1 5
4 7
4 5
5 2
5 7
6 4
1 6
1 3
4 3
1 4
```

### 输出

```
160
```

# AI分析结果



## 算法分类
贪心

---

## 题解思路与算法要点

### 核心逻辑
所有题解均围绕以下两个等价结论展开：
1. **边的视角**：每条边对答案的贡献是两端点权值的较小者，总和即为最优解
2. **点的视角**：按点权从大到小删除，确保每个点在删除时，相邻的更大权值节点已被移除

### 解决难点对比
| 题解类型          | 实现复杂度 | 思维跳跃性 | 正确性证明难度 |
|----------------|-------|-------|--------|
| 直接累加边贡献（主流解法） | O(m)  | 低     | 中等     |
| 拓扑排序+缩点      | O(m+n) | 高     | 高      |
| 优先队列删点       | O(nlogn) | 中     | 中等     |

**关键推导过程**：
1. 最终所有边都会被删除，每条边的贡献只能来自其中一个端点
2. 对于边(u,v)，若先删u则贡献v的权值，先删v则贡献u的权值
3. 最优方案要求所有边的贡献取两端点权值的较小者

---

## 题解评分（≥4星）

### 五星题解
1. **无心揽青丝**（赞21）
   - 亮点：最早提出边贡献视角，代码仅需10行
   - 代码：[见完整代码部分]
   
2. **Prean**（赞3）  
   - 亮点：数学证明完备，指出所有边贡献最小值之和的必然性
   - 关键代码：`ans += min(a[u], a[v])`

3. **雄鹰展翅**（赞2）  
   - 亮点：详细推导删点顺序与边贡献的关系，给出完整逻辑链

---

## 最优思路与代码实现

### 核心代码片段
```cpp
int main() {
    scanf("%d%d", &n, &m);
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    long long ans = 0;
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        ans += min(a[u], a[v]);
    }
    printf("%lld\n", ans);
}
```

### 同类型题目套路
1. 图论问题中的边贡献转化
2. 贪心策略下的极值问题
3. 无需构建完整图结构的简化处理

---

## 推荐练习题
1. **P1967 货车运输**（最大生成树+路径极值）
2. **P1330 封锁阳光大学**（二分图染色+奇偶分析） 
3. **P1231 教辅的组成**（网络流中的边权处理）

---

## 可视化设计

### 像素动画方案
1. **画面布局**：
   - 左侧：8-bit风格节点图，节点显示权值
   - 右侧：累加器显示当前总消耗
   - 底部：当前处理的边高亮显示

2. **动画流程**：
   ```mermaid
   graph TD
   A[初始化节点和边] --> B{是否还有未处理边}
   B -->|是| C[高亮当前边u-v]
   C --> D[显示min(v_u, v_v)]
   D --> E[累加到总和]
   E --> B
   B -->|否| F[播放胜利音效]
   ```

3. **音效设计**：
   - 边处理：8-bit "哔"声（[JSFiddle示例](https://jsfiddle.net/7go4hLdq/)）
   - 完成时：FC游戏通关音效

---

## 实现代码（Web版）
```html
<!DOCTYPE html>
<canvas id="game" width="640" height="480"></canvas>
<script>
const canvas = document.getElementById('game');
const ctx = canvas.getContext('2d');
let edges = [[1,4], [1,2], [2,3]]; // 样例输入
let values = [10,20,30,40]; // 节点权值
let total = 0, currentEdge = 0;

function drawEdge(u, v) {
    // 绘制边并高亮当前处理边
}

function playBeep() {
    // Web Audio API实现音效
}

function animate() {
    if(currentEdge < edges.length) {
        let [u, v] = edges[currentEdge];
        total += Math.min(values[u-1], values[v-1]);
        drawEdge(u, v);
        playBeep();
        currentEdge++;
        requestAnimationFrame(animate);
    } else {
        // 显示最终结果
    }
}
animate();
</script>
```

---
处理用时：74.40秒