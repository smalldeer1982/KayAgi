# 题目信息

# An unavoidable detour for home

## 题目描述

Those unwilling to return home from a long journey, will be affected by the oddity of the snail and lose their way. Mayoi, the oddity's carrier, wouldn't like this to happen, but there's nothing to do with this before a cure is figured out. For now, she would only like to know the enormous number of possibilities to be faced with if someone gets lost.

There are $ n $ towns in the region, numbered from $ 1 $ to $ n $ . The town numbered $ 1 $ is called the capital. The traffic network is formed by bidirectional roads connecting pairs of towns. No two roads connect the same pair of towns, and no road connects a town with itself. The time needed to travel through each of the roads is the same. Lost travelers will not be able to find out how the towns are connected, but the residents can help them by providing the following facts:

- Starting from each town other than the capital, the shortest path (i.e. the path passing through the minimum number of roads) to the capital exists, and is unique;
- Let $ l_{i} $ be the number of roads on the shortest path from town $ i $ to the capital, then $ l_{i}>=l_{i-1} $ holds for all $ 2<=i<=n $ ;
- For town $ i $ , the number of roads connected to it is denoted by $ d_{i} $ , which equals either $ 2 $ or $ 3 $ .

You are to count the number of different ways in which the towns are connected, and give the answer modulo $ 10^{9}+7 $ . Two ways of connecting towns are considered different if a pair $ (u,v) $ ( $ 1<=u,v<=n $ ) exists such there is a road between towns $ u $ and $ v $ in one of them but not in the other.

## 说明/提示

In the first example, the following structure is the only one to satisfy the constraints, the distances from towns $ 2,3,4 $ to the capital are all $ 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814E/41aec6960c240a1fb09480a0a613ecf71bad9b6b.png)In the second example, the following two structures satisfy the constraints.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF814E/5dfe5b5d19d9938739604a89ad14ef6620891ff1.png)

## 样例 #1

### 输入

```
4
3 2 3 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
2 3 3 2 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
2 2 2 2 2
```

### 输出

```
2
```

## 样例 #4

### 输入

```
20
2 2 2 2 3 2 3 2 2 2 2 2 2 2 2 2 2 3 3 2
```

### 输出

```
82944
```

# AI分析结果



## 算法分类
动态规划（DP）

---

## 综合分析与结论

### 核心思路与难点
题目要求构造满足特定最短路条件且度数正确的无向图。关键难点在于：
1. 最短路树的结构限制（层内边只能连接同层节点）
2. 度数约束的巧妙处理（分层转移时剩余度数的动态维护）

题解普遍采用动态规划，以层为单位进行转移：
- **状态定义**：`f[i][j]` 表示前i个节点中最后j个节点位于同一层，`g[i][j][k]` 表示当前层i个节点，上层剩余j个度数为2、k个度数为3的节点的方案数
- **转移方程**：分四种情况处理同层边（环、链）与跨层边的连接方式

### 可视化设计要点
1. **像素动画演示**：
   - 用不同颜色表示层结构（如蓝色表示已处理层，红色表示当前层，黄色表示下一层）
   - 动态展示`g`数组的转移过程：当处理度数为2的节点时，用绿色方块闪烁提示；处理度数为3的节点时用紫色方块
   - 步进控制：允许暂停观察每层连接后的度数变化（如剩余度数用数字标签显示在节点旁）

2. **音效交互**：
   - 连接同层边时播放"哔"音效
   - 完成一层转移时播放"叮"音效
   - 错误转移（如度数超限）时播放"咔"警告音

---

## 题解评分（≥4星）

### 1. CXY07（5星）
- **亮点**：分层预处理同层连边方案，引入容斥系数优化空间至O(n²)
- **代码**：结构清晰，使用滚动数组优化

### 2. Karry5307（4星）
- **亮点**：首篇完整推导状态转移方程，给出明确的数学证明
- **代码**：完整实现三维DP，便于理解核心逻辑

### 3. Styx（4星）
- **亮点**：代码简洁，重点突出转移方程的实现
- **心得**：在注释中强调"避免重复计算环"的关键点

---

## 最优思路提炼

### 关键技巧
```cpp
// g数组转移核心逻辑
g[i][j][k] = j*g[i-1][j-1][k] + k*g[i-1][j+1][k-1];
```
- **分层处理**：将图分解为BFS树的层级结构
- **度数转换**：将度数约束转化为剩余度数问题（d[i]-1作为剩余度数）
- **组合计数**：通过排列组合处理同层边的合法连接方式

### 同类型题
1. [CF1004D] 矩阵构造（类似的分层约束）
2. [洛谷P3587] 树形DP与度数约束
3. [ABC231G] 分层背包问题

---

## 核心代码实现
```cpp
// Karry5307 题解关键片段
void calc() {
    g[0][0][0] = 1;
    // 处理无当前层的情况
    for(int k=2; k<=n; k++) {
        for(int l=3; l<k; l++) {
            g[0][0][k] += g[0][0][k-l-1] * C(k-1,l) * fac[l] / 2;
        }
    }
    // 处理有当前层的情况
    for(int i=1; i<=n; i++) {
        for(int j=0; j<=n; j++) {
            for(int k=0; k<=n; k++) {
                if(j) g[i][j][k] += j * g[i-1][j-1][k];
                if(k) g[i][j][k] += k * g[i-1][j+1][k-1];
            }
        }
    }
}
```

---

## 复古像素动画设计（伪代码）
```javascript
class LayerAnimation {
    constructor() {
        this.canvas = document.createElement('canvas');
        this.layers = [ /* 存储各层节点数据 */ ];
        this.colors = ['#FF0000', '#00FF00', '#0000FF']; // 红绿蓝表示不同状态
    }
    
    drawLayer(layerId) {
        // 绘制层结构，高亮当前处理层
        this.ctx.fillStyle = this.colors[layerId % 3];
        this.ctx.fillRect(x, y, 16, 16); // 16x16像素块
    }
    
    playSound(effect) {
        // 8-bit音效生成
        const osc = new OscillatorNode(ctx, {type: 'square'});
        osc.frequency.value = effect === 'error' ? 220 : 440;
        osc.connect(ctx.destination);
        osc.start();
    }
}
```

---

## 个人心得摘录
> "调试时发现忘记处理度数转换（d[i]-1），导致方案数多算。教训：必须明确每个状态的实际含义" —— Styx题解

> "将环分解为包含最后一个点的子环，避免重复计数，这是突破点" —— CXY07博客

---
处理用时：56.88秒