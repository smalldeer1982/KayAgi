# 题目信息

# [ABC376G] Treasure Hunting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc376/tasks/abc376_g

頂点に $ 0 $ から $ N $ までの番号がついた $ N\ +\ 1 $ 頂点の根付き木があります。頂点 $ 0 $ は根で、頂点 $ i $ の親は頂点 $ p_i $ です。  
 頂点 $ 1 $, 頂点 $ 2 $, $ \dots $, 頂点 $ N $ のうちどこか $ 1 $ 頂点に宝が隠されています。頂点 $ i $ に宝がある確率は $ \frac{a_i}{\sum_{j=1}^N\ a_j} $ です。 また、各頂点には「探索済」と「未探索」のどちらか一方の状態を持ちます。はじめ頂点 $ 0 $ は探索済で、それ以外の頂点は未探索です。  
 あなたは、宝がある頂点が探索済になるまで以下の操作を行います。

- 親が探索済であるような未探索の頂点を選び、その頂点を探索済にする。
 
操作回数の期待値が最小になるように行動した時の操作回数の期待値を $ \text{mod\ }998244353 $ で求めてください。

$ T $ 個のテストケースが与えられるので、それぞれに対して答えを求めてください。

  期待値 $ \text{mod\ }{998244353} $ の定義 求める期待値は必ず有理数になることが証明できます。 また、この問題の制約のもとでは、その値を既約分数 $ \frac{P}{Q} $ で表した時、$ Q\ \not\ \equiv\ 0\ \pmod{998244353} $ となることも証明できます。このとき、$ R\ \times\ Q\ \equiv\ P\ \pmod{998244353},\ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ が一意に定まります。この $ R $ を答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ p_i\ \lt\ i $
- $ 1\ \leq\ a_i $
- $ \sum_{i=1}^N\ a_i\ \leq\ 10^8 $
- 全てのテストケースに対する $ N $ の総和は $ 2\ \times\ 10^5 $ 以下
- 入力される値は全て整数
 
### Sample Explanation 1

$ 1 $ 番目のテストケースにおける操作回数の期待値は $ \frac{13}{6} $ です。

## 样例 #1

### 输入

```
3

3

0 0 1

1 2 3

5

0 1 0 0 0

8 6 5 1 7

10

0 1 1 3 3 1 4 7 5 4

43 39 79 48 92 90 76 30 16 30```

### 输出

```
166374061

295776107

680203339```

# AI分析结果



---

## 唯一算法分类
**贪心/并查集/优先队列**

---

## 综合分析与结论

### 核心算法流程
1. **贪心策略**：将每个节点视为初始独立集合，按特定优先级合并到父节点集合。  
2. **合并条件**：对于两个子树 $A$ 和 $B$，优先合并 $\frac{\text{sum}_A}{\text{siz}_A} \geq \frac{\text{sum}_B}{\text{siz}_B}$ 的子树（sum为子树总概率，siz为节点数）。  
3. **数据结构**：用优先队列维护每个集合的优先级，并查集快速查询集合归属。  
4. **动态更新**：合并后更新父集合的 sum、siz 和期望值，重新入队。

### 可视化设计思路
- **动画效果**：  
  - **节点高亮**：当前选中的节点显示为红色，父节点集合显示为蓝色。  
  - **合并过程**：用箭头动态连接被合并节点到父节点集合，实时更新队列中的元素。  
  - **数据面板**：展示队列中前5个集合的 sum/siz 比值及当前总期望值。  
- **8位像素风格**：  
  - 树结构以网格布局，每个节点用 16x16 像素方块表示，合并时播放“咔哒”音效。  
  - 背景音乐为循环的 8-bit 风格旋律，成功合并时触发高音效。  

---

## 题解清单（≥4星）

### 1. 作者：zhm080507（★★★★☆）  
**亮点**：  
- 推导合并条件的数学表达式清晰，代码简洁高效。  
- 使用优先队列与并查集实现动态合并，时间复杂度 $O(n \log n)$。  
- 注释明确，关键变量命名合理（如 `val`、`siz`、`p`）。

### 2. 作者：RAND_MAX（★★★★☆）  
**亮点**：  
- 通过图示直观解释合并条件（如 `siz_x * sum_y` 的贡献）。  
- 代码模块化，分离并查集操作与期望计算。  
- 提供与类似题（AT_agc023_f）的对比，拓展性强。

### 3. 作者：沉石鱼惊旋（★★★★☆）  
**亮点**：  
- 从排列构造角度切入，明确转化为贪心问题。  
- 讨论绑定节点的平均权值排序，理论分析深入。  
- 代码虽未展示，但思路描述完整，适合进阶理解。

---

## 最优思路与代码实现

### 关键代码（zhm080507）
```cpp
struct Node {
    int val, siz, p, id; // 期望贡献、节点数、总概率、集合ID
};
bool operator<(Node x, Node y) {
    return x.siz * y.p > y.siz * x.p; // 优先队列比较条件
}
Node operator+(Node x, Node y) { // 合并操作
    return { (x.val + x.siz * y.p + y.val) % mod, 
             x.siz + y.siz, 
             (x.p + y.p) % mod, 
             x.id };
}
void sol() {
    priority_queue<Node> q;
    for (int i=1; i<=n; i++) q.push({a[i], 1, a[i], i});
    while (!q.empty()) {
        Node u = q.top(); q.pop();
        int fa_id = getfa(fa[u.id]); // 获取父集合ID
        merge(u.id, fa_id);          // 合并到父集合
        q.push(updated_node);         // 更新后重新入队
    }
    cout << root.val * inv_sum % mod; // 最终期望值
}
```

---

## 同类型题推荐
1. **AT_agc023_f**：树上的01序列构造，类似贪心合并。  
2. **CF1253F**：优先队列维护充电站优先级。  
3. **Luogu P1090**：合并果子，基础贪心+优先队列。

---

## 可视化实现（JS伪代码）
```javascript
class NodeViz {
    constructor() {
        this.canvas = document.getElementById("tree-canvas");
        this.ctx = this.canvas.getContext("2d");
        this.nodes = []; // 节点坐标与状态
        this.playSound("bgm", true); // 循环背景音乐
    }
    drawMerge(from, to) {
        this.highlightNode(from, "red");
        this.highlightNode(to, "blue");
        this.drawArrow(from, to); // 绘制合并箭头
        this.playSound("merge");  // 触发音效
    }
    playSound(type, loop=false) {
        const sfx = { bgm: "8bit_loop.wav", merge: "click.wav" };
        const audio = new Audio(sfx[type]);
        audio.loop = loop;
        audio.play();
    }
}
```

---

## 个人心得摘录
- **huangrenheluogu**：  
  > “赛后发现很多地方挂了，罚了3发才好的... 并查集合并时需确保父节点已初始化。”  
  **启示**：初始化细节和路径压缩的正确性需反复验证。  
- **zifanwang**：  
  > “比较条件中的乘法可能溢出，改用交叉相乘避免除法。”  
  **教训**：数值比较时注意模运算下的合法转换。

---
处理用时：98.43秒