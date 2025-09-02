# 题目信息

# Complete The Graph

## 题目描述

ZS the Coder has drawn an undirected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ m $ edges between them. Each edge of the graph is weighted, each weight is a positive integer.

The next day, ZS the Coder realized that some of the weights were erased! So he wants to reassign positive integer weight to each of the edges which weights were erased, so that the length of the shortest path between vertices $ s $ and $ t $ in the resulting graph is exactly $ L $ . Can you help him?

## 说明/提示

Here's how the graph in the first sample case looks like :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715B/c442fd279761bfa74ef367b518cede1e1fa97983.png)In the first sample case, there is only one missing edge weight. Placing the weight of $ 8 $ gives a shortest path from $ 0 $ to $ 4 $ of length $ 13 $ .

In the second sample case, there is only a single edge. Clearly, the only way is to replace the missing weight with $ 123456789 $ .

In the last sample case, there is no weights to assign but the length of the shortest path doesn't match the required value, so the answer is "NO".

## 样例 #1

### 输入

```
5 5 13 0 4
0 1 5
2 1 2
3 2 3
1 4 0
4 3 4
```

### 输出

```
YES
0 1 5
2 1 2
3 2 3
1 4 8
4 3 4
```

## 样例 #2

### 输入

```
2 1 123456789 0 1
0 1 0
```

### 输出

```
YES
0 1 123456789
```

## 样例 #3

### 输入

```
2 1 999999999 1 0
0 1 1000000000
```

### 输出

```
NO
```

# AI分析结果



---

## 算法分类  
**最短路径（Dijkstra 变种）**

---

## 综合分析与结论  
### 核心算法流程  
1. **两次 Dijkstra 的核心思想**  
   - **第一次**：将所有未赋权边设为最小值 1，跑最短路判断可行性。若此时最短路已超过 $L$，直接无解。  
   - **第二次**：动态调整未赋权边的权重，使得最终最路径长度精确等于 $L$。具体策略为：若当前边权允许路径缩短至 $dis[y] + \text{dif}$（$\text{dif}=L-\text{第一次最短路长度}$），则将其调整为 $dis[y] + \text{dif} - \text{当前路径长度}$。  
   - **难点**：需确保调整后的边权不破坏最短路条件，且所有未调整边不影响最终结果。

2. **可视化设计要点**  
   - **颜色标记**：  
     - 红色高亮：未赋权边在第二次 Dijkstra 中被动态调整的过程。  
     - 绿色路径：第一次 Dijkstra 的最短路径，蓝色路径：调整后的最终路径。  
   - **动画步骤**：  
     1. 初始化所有未赋权边为 1，播放第一次 Dijkstra 的松弛过程。  
     2. 显示 $\text{dif}$ 的计算结果（差值条从红色渐变到绿色）。  
     3. 在第二次 Dijkstra 中，当遍历到未赋权边时触发边权调整动画（数字跳动 + 黄色闪光）。  
     4. 最终路径用粒子效果追踪，并在终点显示 $L$ 的校验结果。  
   - **音效与风格**：  
     - 8-bit 音效：路径更新时播放「嘀」声，调整边权时播放「咔嚓」声，成功时播放经典 FC 过关音效。  
     - 像素风格：节点用 16x16 像素块表示，边权调整时显示复古数字滚动特效。

---

## 题解清单（评分 ≥4★）  
### 1. zhenliu（★★★★★）  
**亮点**：  
- 两遍 Dijkstra 逻辑清晰，首次验证可行性，二次动态调整边权。  
- 代码中通过 `zero` 数组标记未赋权边，实现简洁高效。  
**关键代码**：  
```cpp  
void dijkstra(int k) {
    // 第二次 Dijkstra 动态调整未赋权边
    if(k==1 && zero[i] && dis[x][1]+w < dis[y][0]+dif)
        w = dis[y][0] + dif - dis[x][1];
}
```

### 2. Spasmodic（★★★★）  
**亮点**：  
- 二分未赋权边的总增量，数学建模巧妙。  
- 通过 `calc(x,i)` 函数均匀分配增量，确保最短路径单调变化。  
**关键代码**：  
```cpp  
ll calc(ll x, ll i) { // 二分分配增量
    ll tms = x / e;
    x -= tms * e;
    return tms + (x >= i ? 1 : 0) + 1;
}
```

### 3. Saber_Master（★★★★）  
**亮点**：  
- 使用二维状态 `dis[i][j]` 表示经过 $j$ 条未赋权边的最短路，动态规划思路独特。  
- 通过反向 DFS 回溯调整关键边权。  

---

## 最优思路提炼  
**关键操作**：  
1. **可行性验证**：未赋权边取最小值 1 时，若最短路超过 $L$ 则无解。  
2. **差值分配**：计算 $dif = L - \text{第一次最短路长度}$，在第二次 Dijkstra 中按需分配差值到未赋权边。  
3. **动态调整**：在松弛过程中实时修改边权，确保最终路径长度精确等于 $L$。  

**思维模型**：  
- 将未赋权边视为可调节的「阀门」，通过控制其权重引导最路径流向目标值。  

---

## 相似题目推荐  
1. **[P3953 逛公园](https://www.luogu.com.cn/problem/P3953)**：最短路与动态规划结合，统计路径数。  
2. **[P1462 通往奥格瑞玛的道路](https://www.luogu.com.cn/problem/P1462)**：二分 + 最短路验证。  
3. **[CF1473E Minimum Path](https://codeforces.com/problemset/problem/1473/E)**：带权值调整的最短路变种。  

---

## 个人心得摘录  
> **zhenliu** 的调试经验：  
> “机房大佬点醒：每个满足条件的边都调整，最短路自然会收敛到 $L$。若调整后仍不满足，直接判无解。”  
> **启示**：动态调整策略需要全局视角，局部最优可能隐含全局最优。

---

## 可视化算法演示（核心逻辑）  
### 动态流程图  
![两步 Dijkstra 调整](https://cdn.luogu.com.cn/upload/image_hosting/9z6qyv7k.gif)  
**交互设计**：  
- **拖拽节点**：允许用户自定义图结构，实时显示最短路变化。  
- **速度控制**：滑动条调节 Dijkstra 执行速度，观察边权调整的逐步过程。  
- **自动演示模式**：AI 自动运行两次 Dijkstra，用箭头高亮当前处理的边。  

```javascript  
// 伪代码：边权调整动画核心逻辑  
function adjustEdge(edge, newWeight) {
    anime({
        targets: edge,
        weight: newWeight,
        duration: 1000,
        easing: 'easeOutElastic',
        update: () => drawGraph()
    });
}
```

---
处理用时：97.21秒