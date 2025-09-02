# 题目信息

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# AI分析结果



# Fox And Jumping 题解分析

## 算法分类
动态规划（基于 GCD 状态转移）

---

## 核心思路与难点解析

### 核心算法流程
1. **裴蜀定理转化**：通过裴蜀定理将问题转化为求选定卡片的最大公约数为 1 的最小代价。
2. **动态规划状态设计**：使用 `map<int, int>` 维护当前所有可能的 GCD 值及其最小代价。
3. **状态转移**：对于每张新卡片，将其与已有 GCD 值计算新的 GCD，并更新对应最小代价。

### 解决难点
- **GCD 状态爆炸**：通过 map 动态维护有效状态，避免预存所有可能的 GCD。
- **最优子结构**：每个 GCD 状态的最小代价均可通过已有状态与新卡片组合得到。
- **剪枝优化**：仅保留每个 GCD 值的最小代价，减少无效状态扩展。

---

## 题解评分（≥4星）

### 4星题解：Kohakuwu（map动态规划）
- **思路清晰**：直接利用裴蜀定理转化为 GCD 状态维护。
- **代码简洁**：仅需 20 行核心逻辑，使用 STL map 实现状态转移。
- **可扩展性**：适用于任意数值范围，无需质因数分解等预处理。

```cpp
map<int, int> mp;
int main() {
    for (int i=1; i<=n; i++) {
        for (auto x : mp) {
            int g = gcd(x.first, l[i]);
            if (!mp.count(g)) mp[g] = x.second + c[i];
            else mp[g] = min(mp[g], x.second + c[i]);
        }
        mp[l[i]] = min(mp[l[i]], c[i]);
    }
    cout << (mp[1] ? : -1);
}
```

### 4星题解：ZYF_B（状压DP）
- **数学优化**：通过质因数分解进行状态压缩（最多 9 个质因数）。
- **高效转移**：O(n²2⁹) 复杂度稳定，适合大规模同质因数数据。
- **实现技巧**：预处理每个数的质因数集合，通过位运算快速处理交集。

```cpp
int f[1<<9]; // 状态压缩存储质因数集合
for (int i=1; i<=n; i++) {
    int s = 计算当前卡片质因数位掩码;
    for (int k=0; k<M; k++)
        f[k&s] = min(f[k&s], f[k]+cost[j]);
}
```

### 4星题解：fanfansann（Dijkstra最短路）
- **建模创新**：将 GCD 状态视为图中的节点，费用为边权。
- **优先队列优化**：快速找到当前最小代价路径，类似最短路径算法。
- **动态剪枝**：利用 visited 标记避免重复处理相同 GCD 状态。

```cpp
priority_queue<pair<int, int>> pq;
unordered_map<int, int> dist;
void dijkstra() {
    while (!pq.empty()) {
        int u = pq.top().second;
        for (卡片 l[i]) {
            int v = gcd(u, l[i]);
            if (dist[v] > dist[u] + c[i]) {
                dist[v] = dist[u] + c[i];
                pq.push({-dist[v], v});
            }
        }
    }
}
```

---

## 最优思路提炼

### 关键技巧
1. **GCD 状态空间压缩**：利用动态数据结构（map）维护有效状态。
2. **滚动更新策略**：每加入新卡片时，仅需遍历已有状态生成新 GCD。
3. **数学性质应用**：裴蜀定理将无限跳跃问题转化为离散 GCD 求值。

### 代码实现要点
- 初始化 `map[0] = 0` 作为起始状态（未选任何卡片）。
- 双重循环更新：外层遍历卡片，内层遍历当前所有 GCD 状态。
- 使用 `gcd(a,b)` 函数快速计算新状态，保证 O(1) 转移。

---

## 同类型题目推荐
1. **P4549 裴蜀定理**：求 n 个数的最小非零绝对值组合。
2. **P1072 Hankson 的趣味题**：通过 GCD 和 LCM 性质求解约束条件。
3. **P2448 无尽的生命**：基于数论的状态转移与动态规划。

---

## 可视化设计（复古像素风格）

### 动画元素
- **8-bit 网格**：每个格子表示一个 GCD 值，颜色深浅表示代价大小。
- **动态连线**：当处理新卡片时，从旧 GCD 节点向新 GCD 节点绘制箭头，显示代价变化。
- **音效反馈**：
  - `coin.wav`：每次更新更小代价时播放。
  - `win.wav`：当生成 GCD=1 时触发。

### 交互功能
- **步进控制**：空格键单步执行卡片处理，Enter 键自动播放。
- **状态面板**：右侧显示当前处理的卡片索引、已生成 GCD 数量、当前最小代价。

```javascript
// 示例：Canvas 绘制 GCD 节点
function drawNode(gcd, cost) {
    ctx.fillStyle = `hsl(${gcd % 360}, 70%, 50%)`;
    ctx.fillRect(x, y, 30, 30);
    ctx.fillText(`$${cost}`, x+5, y+20);
}
```

---

## 个人心得摘录
> "意识到问题可转化为 GCD 状态转移后，使用 map 代替数组是突破点。调试时发现初始化 `map[0]=0` 是关键，否则无法启动状态转移。" —— Kohakuwu

> "Dijkstra 方法中，优先队列的优先级设定为负代价，这样可以直接使用 STL 的默认大顶堆实现最小堆。" —— fanfansann

---
处理用时：100.76秒