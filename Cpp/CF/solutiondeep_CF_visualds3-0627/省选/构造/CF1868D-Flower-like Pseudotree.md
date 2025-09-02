# 题目信息

# Flower-like Pseudotree

## 题目描述

A pseudotree is a connected graph which has exactly one cycle and no self-loops. Note that a pseudotree may contain multiple-edges. It can be shown that a pseudotree with $ n $ vertices always contains $ n $ edges.

After deleting all edges on the cycle in the pseudotree, a forest $ ^{\dagger} $ will be formed. It can be shown that each tree in the forest will contain exactly one vertex which is on cycle before removing the edges. If all trees in the forest have the same depth $ ^{\ddagger} $ when picking the vertex on cycle as root, we call the original pseudotree flower-like.

Our friend sszcdjr, had a flower-like pseudotree with $ n $ vertices and $ n $ edges. However, he forgot all the edges in the pseudotree. Fortunately, he still remembers the degrees of vertices. Specifically, the degree of the $ i $ -th vertex is $ d_i $ .

You have to help sszcdjr construct a possible flower-like pseudotree with $ n $ vertices, where the degree of the $ i $ -th vertex is exactly $ d_i $ , or tell him that it is impossible.

 $ ^{\dagger} $ A forest is a graph in which all connectivity components are trees. A connected graph without cycles and self-loops is called a tree.

 $ ^{\ddagger} $ The depth of a tree with a root is the maximum distance from the root to the vertex of this tree.

## 说明/提示

In the first test case, the only possible flower-like psuedotree is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1868D/cef326e6c38f8a7ed31108a0dd8a82ca77066a75.png)After deleting all edges on the cycle in the pseudotree, each tree has depth $ 0 $ .

In the second test case, it can be proven that there's no such flower-like psuedotree.

In the third test case, one of the possible flower-like psuedotrees is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1868D/48e01c1853662d07718526eb1ce31700d09724f0.png)

## 样例 #1

### 输入

```
6
3
2 2 2
4
1 2 3 4
7
4 3 3 1 1 1 1
6
1 1 2 2 3 3
10
1 1 5 2 1 1 1 1 1 6
9
1 1 3 1 1 4 1 1 5```

### 输出

```
Yes
1 2
2 3
3 1
No
Yes
1 2
2 3
3 1
1 4
1 5
2 6
3 7
Yes
5 6
6 5
1 3
2 4
3 5
4 6
No
Yes
3 6
6 9
9 3
1 3
2 6
4 6
5 9
7 9
8 9```

# AI分析结果



## 算法分类
构造、贪心、基环树

---

## 综合分析与结论

### 题目核心
构造满足度数条件的基环树，要求删环后各子树深度相同。核心难点在于环的选择与非环点的分配策略。

### 题解思路对比
1. **Rainbow_qwq** 提出将环固定为两个度数最大的点，按度数降序交替构建两条链，最后处理叶子。通过调整链长度差解决大部分情况。
2. **Alex_Wei** 将所有非叶节点排序，优先用度数大的点构造环，剩余点形成链式结构，利用队列动态分配。
3. **DeaphetS** 通过贪心策略将非叶节点挂到环两侧，若出现链长度差则调整父节点。

### 解决难点
- **环的确定**：选择度数最大的两个点作为环的核心，确保度数足够支撑后续挂链。
- **链的平衡**：交替分配非叶节点到环两侧，减少深度差。
- **叶子的处理**：确保每个叶子正确连接到非叶节点的空位上。

### 可视化设计
- **动画流程**：
  1. 初始显示环上两个大度数点（红色高亮）。
  2. 非叶节点（黄色）按度数降序依次挂到环两侧，形成链。
  3. 叶子（绿色）动态连接到非叶节点的空位。
  4. 调整阶段：若链差为1，高亮待调整点，展示交换父节点过程。
- **复古风格**：用8位像素风绘制节点，链式生长时播放“连接”音效，调整失败时触发短促错误音效。

---

## 题解清单（≥4星）

### Rainbow_qwq（★★★★★）
- **亮点**：逻辑清晰，通过交替挂链平衡深度，处理链差情况的方法巧妙。
- **关键代码**：
  ```cpp
  // 交替挂链核心逻辑
  Rep(i,n,2) if(vec[i].size()) {
    for(int u:vec[i]) {
      if(dx<=dy) fa[u]=nx, nx=u, dx++;
      else fa[u]=ny, ny=u, dy++;
    }
  }
  ```

### Alex_Wei（★★★★☆）
- **亮点**：代码简洁，利用排序和队列动态分配节点，减少分类讨论。
- **关键代码**：
  ```cpp
  // 动态分配链
  while(!lar.empty()) {
    auto nu = get();
    add2(u, nu); fill(u); u = nu;
    auto nv = get();
    add2(v, nv); fill(v); v = nv;
  }
  ```

### DeaphetS（★★★★☆）
- **亮点**：贪心处理链式分配，调整策略直接。
- **关键代码**：
  ```cpp
  // 调整父节点
  for(int i=1;i<lst;i++) if(a[i].deg && dep[a[i].id]<dep[fa[a[lst].id]]){
    swap(fa[a[lst].id], a[i].id); // 找到更浅的父节点
    break;
  }
  ```

---

## 最优思路提炼
1. **环的选择**：取度数最大的两个点作为环的核心。
2. **链的平衡**：按度数降序交替挂链，确保深度差最小。
3. **叶子处理**：最后统一填充叶子，利用队列或栈管理空位。

---

## 相似题目推荐
1. [P1355 图的m着色问题](https://www.luogu.com.cn/problem/P1355)（基环树构造）
2. [P2661 信息传递](https://www.luogu.com.cn/problem/P2661)（基环树找环）
3. [P2607 骑士](https://www.luogu.com.cn/problem/P2607)（基环树DP）

---

## 个人心得摘录
- **Rainbow_qwq**提到在调整链差时，需找到深度最小的叶子，否则无法保证合法性。
- **DeaphetS**在调试中发现，当非叶节点数为奇数时需特殊处理，否则会遗漏情况。

---

## 可视化算法演示
### 核心流程
1. **初始环**：红色节点（度数最大）连接成环。
2. **挂链阶段**：
   - 黄色节点按度数依次挂到左右链，链末端高亮。
   - 每次挂节点播放“咔”音效。
3. **叶子填充**：绿色叶子连接到非叶节点的空位，播放“滴”音效。
4. **调整阶段**：
   - 若链差为1，高亮待调整节点（闪烁）。
   - 成功调整播放上升音调，失败播放下降音调。

### 复古风格实现
- **Canvas绘制**：节点用16x16像素块表示，环节点红色，链节点黄色，叶子绿色。
- **音效**：Web Audio API生成8位音效，连接时短促方波，调整成功时上升琶音。

```javascript
// 示例：连接音效
function playConnectSound() {
  const osc = audioCtx.createOscillator();
  osc.type = 'square';
  osc.frequency.setValueAtTime(440, audioCtx.currentTime);
  osc.connect(audioCtx.destination);
  osc.start();
  osc.stop(audioCtx.currentTime + 0.1);
}
```

---

通过上述设计，学习者可直观理解基环树的构造过程，并通过交互式操作加深对贪心策略的理解。

---
处理用时：61.03秒