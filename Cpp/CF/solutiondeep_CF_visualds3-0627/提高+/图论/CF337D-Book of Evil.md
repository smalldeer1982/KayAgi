# 题目信息

# Book of Evil

## 题目描述

Paladin Manao caught the trail of the ancient Book of Evil in a swampy area. This area contains $ n $ settlements numbered from 1 to $ n $ . Moving through the swamp is very difficult, so people tramped exactly $ n-1 $ paths. Each of these paths connects some pair of settlements and is bidirectional. Moreover, it is possible to reach any settlement from any other one by traversing one or several paths.

The distance between two settlements is the minimum number of paths that have to be crossed to get from one settlement to the other one. Manao knows that the Book of Evil has got a damage range $ d $ . This means that if the Book of Evil is located in some settlement, its damage (for example, emergence of ghosts and werewolves) affects other settlements at distance $ d $ or less from the settlement where the Book resides.

Manao has heard of $ m $ settlements affected by the Book of Evil. Their numbers are $ p_{1},p_{2},...,p_{m} $ . Note that the Book may be affecting other settlements as well, but this has not been detected yet. Manao wants to determine which settlements may contain the Book. Help him with this difficult task.

## 说明/提示

Sample 1. The damage range of the Book of Evil equals 3 and its effects have been noticed in settlements 1 and 2. Thus, it can be in settlements 3, 4 or 5.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF337D/bb5982168a46056c0b6c7bf34dd6accd73b10df3.png)

## 样例 #1

### 输入

```
6 2 3
1 2
1 5
2 3
3 4
4 5
5 6
```

### 输出

```
3
```

# AI分析结果



## 算法分类
**树的直径 + 三次DFS**

---

## 题解思路与核心难点

### 核心算法逻辑
题目要求找到所有节点，使得这些节点到所有「鬼节点」的距离 ≤ d。关键难点在于如何高效判断所有鬼节点的距离约束。

#### **最优解法：三次DFS（树的直径思想）**
1. **核心思路**：找到两鬼节点 A 和 B，使得它们是最远的一对鬼节点（类似树的直径）。若某节点到 A 和 B 的距离均 ≤ d，则该节点满足题意。
2. **正确性证明**：若存在某鬼节点 C 到当前节点距离 > d，则 C 到 A/B 的距离会超过 A-B 的距离，与 A-B 是最远矛盾。
3. **实现步骤**：
   - 第一次DFS：任选节点，找到离其最远的鬼节点 A。
   - 第二次DFS：以 A 为起点，找到离其最远的鬼节点 B。
   - 第三次DFS：计算所有节点到 B 的距离，最终统计同时满足到 A 和 B 距离 ≤ d 的节点数。

#### **可视化设计**
- **动画流程**：
  1. **首次DFS**：从任意节点出发，动态高亮遍历路径，标红最远鬼节点 A。
  2. **二次DFS**：从 A 出发，标蓝最远鬼节点 B，显示 A-B 路径为「直径」。
  3. **三次DFS**：遍历所有节点，绿色标记到 A 和 B 距离均 ≤ d 的节点。
- **高亮交互**：点击节点显示到 A/B 的距离；滑动条调节 d 值，实时更新合格节点。

---

## 题解评分（≥4星）

### 1. Elma_（★★★★★）
- **亮点**：三次DFS思路简洁，正确性证明严谨，代码仅需三次遍历，O(n) 复杂度。
- **代码**：通过两次DFS找最远点，第三次计算距离，逻辑清晰。

### 2. Wen_kr（★★★★☆）
- **亮点**：树形DP维护子树内外最大距离，换根技巧处理全局约束。
- **难点**：需维护次大值避免重复路径，实现稍复杂。

### 3. RainAir（★★★★☆）
- **亮点**：与三次DFS思路类似，但用 BFS 实现，适合理解广度优先的读者。

---

## 最优技巧提炼

### 关键思路
- **树的直径应用**：最远鬼节点对 A-B 的路径覆盖了全局距离约束，只需验证到这两点的距离。
- **三次DFS**：线性时间完成最远点查找与距离计算。

### 代码片段
```cpp
// 三次DFS核心代码（Elma_题解）
void dfs(int u, int fath, int dep, int* dis) {
    dis[u] = dep;
    for (int v : edges[u]) {
        if (v != fath) dfs(v, u, dep + 1, dis);
    }
}

// 主逻辑
int A = findFarthest(1); // 第一次DFS找A
int B = findFarthest(A); // 第二次DFS找B
dfs(A, -1, 0, disA);     // 计算到A的距离
dfs(B, -1, 0, disB);     // 计算到B的距离
int ans = 0;
for (int i = 1; i <= n; i++) {
    if (disA[i] <= d && disB[i] <= d) ans++;
}
```

---

## 同类题目推荐
1. **CF 455C**（树的直径合并）
2. **洛谷 P1099**（树网的核，类似最远距离约束）
3. **洛谷 P4381**（树的最长路径，树的直径变体）

---

## 个人心得摘录
- **Elma_**：通过类比树的直径，将复杂约束简化为两点验证，避免暴力枚举。
- **Wen_kr**：调试中发现次大值未更新导致错误，强调维护次大值的必要性。

---

## 复古像素化动画设计

### 实现要点
- **像素风格**：使用 16 色调色板，节点用 8x8 像素块表示，路径用棕色线条。
- **音效**：遍历时播放「嘀」声，找到最远点时播放「升级」音效，合格节点闪烁绿光。
- **自动演示**：AI 按步骤执行三次DFS，用户可暂停观察中间状态。
- **Canvas 交互**：点击节点显示距离数值，拖拽调节 d 值实时刷新结果。

```javascript
// 伪代码：动画核心逻辑
function animateDFS(node, target, color) {
    let timer = setInterval(() => {
        highlight(node, color); // 高亮当前节点
        if (node === target) {
            playSound('success');
            clearInterval(timer);
        }
        node = nextNode();
    }, 100);
}
// 初始化三次DFS动画
animateDFS(root, A, RED);
animateDFS(A, B, BLUE);
animateCheckNodes();
```

---

## 总结
通过树的直径思想将全局约束简化为两点验证，三次DFS实现高效求解。树形DP适用于更复杂的距离维护场景，但本题最优解仍为三次DFS，兼具效率与简洁性。

---
处理用时：69.27秒