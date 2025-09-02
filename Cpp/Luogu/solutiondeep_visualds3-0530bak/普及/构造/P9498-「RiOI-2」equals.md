# 题目信息

# 「RiOI-2」equals

## 题目背景

在小树上坐落着一个幻想的城堡。这里是 E 国的领地，而小 E，则是 E 国之王。

为了打造一个完美的 E 国，他需要明辨是非，走向正义。

但是，他似乎有些太理想了。有时并没有一个完美的准则。是黑是白，谁能分辨？

## 题目描述

给定一棵 $n$ 个结点，以 $1$ 为根的树，定义一个结点的深度 $d_i$ 表示它到根结点的简单路径上的结点个数。

你需要给每个结点黑白染色，满足黑色结点的深度和等于白色结点的深度和。设 $c_i = \{0, 1\}$ 分别代表编号为 $i$ 的结点为黑色或白色，那么这即 $\displaystyle\sum_{c_i=0}d_i=\sum_{c_i=1}d_i$。

若无解，仅输出一行一个整数 $-1$。

## 说明/提示

### 样例解释

对于第一组数据，每个结点的深度分别是 $d=[1,2,2,3,3,3]$。黑色结点的深度和为 $d_1+d_5+d_6=1+3+3=7$，白色结点的深度和为 $d_2+d_3+d_4=2+2+3=7$。它们相等，所以样例输出是正确的。可能的正确输出包括但不限于样例输出、`0 1 1 0 0 1`，`1 0 0 1 0 1` 等。

### 数据规模与约定

**本题采用捆绑测试。**

| $\rm Subtask$ | 分值 | $n\le $ | 特殊性质 |
| :-----------: | :--: | :-----: | :------: |
| $0$ | $5$ | $20$ | / |
| $1$ | $15$ | $500$ | / |
| $2$ | $20$ | $5\times 10^3$ | / |
| $3$ | $10$ | / | $n$ 为偶数 |
| $4$ | $5$ | / | 树为菊花图（不保证根为菊花中心） |
| $5$ | $5$ | / | 树为一条链（不保证根为链的端点） |
| $6$ | $40$ | / | / |

斜杠表示这一栏无特殊限制。

对于 $100\%$ 的数据，$1\le n\le 10^6$，$1\le u_i,v_i\le n$，输入数据构成一棵树。

## 样例 #1

### 输入

```
6
1 2
1 3
2 4
2 5
2 6```

### 输出

```
0 1 1 1 0 0```

## 样例 #2

### 输入

```
5
1 2
1 3
2 4
2 5```

### 输出

```
-1```

# AI分析结果



# 算法分类  
**贪心算法**

---

## 综合分析与结论  
### 核心思路  
1. **必要条件**：深度总和必须为偶数，否则无解  
2. **关键性质**：树节点的深度值域连续（若存在深度为 k 的节点，则存在深度为 1~k-1 的节点）  
3. **贪心策略**：将节点按深度从大到小排序，依次选择节点并累加深度，直到总和达到总深度的一半  

### 实现难点  
1. **排序与回溯**：需在排序后通过线性扫描快速找到满足条件的节点组合  
2. **颜色标记调整**：当累加值超过目标时，需反向查找可移除的节点  
3. **复杂度控制**：必须使用 O(n log n) 的排序算法以适应 1e6 的数据规模  

### 可视化设计  
**核心动画流程**：  
1. **树形结构**：用像素风格绘制树形结构，根节点在顶部，不同颜色表示深度层级  
2. **深度列表**：在右侧显示排序后的深度序列，用动态高亮标记当前扫描的节点  
3. **累加过程**：  
   - 选中节点时显示绿色方块，未选中显示红色  
   - 顶部进度条显示当前累加值与目标值的比例  
4. **回溯调整**：当累加值超过目标时，触发红色闪烁特效，并自动反向查找可移除节点  
5. **音效设计**：  
   - `pick.wav`：选中节点时的 8-bit 音效  
   - `overflow.wav`：累加超限时的警示音  
   - `success.wav`：成功找到解时的胜利音效  

---

## 题解清单（≥4星）  
### 1. GaCGe（5星）  
**亮点**：  
- 简洁的贪心实现，代码仅 30 行  
- 明确证明了排序后贪心的正确性  
```cpp
sort(dep + 1, dep + 1 + n);
for(int i = n; i >= 1; i--)
    if(sum - 2 * dep[i] >= 0)
        sum -= 2 * dep[i], ans[dep[i].second] = 1;
```

### 2. Convergent_Series（4星）  
**亮点**：  
- 使用哈希表记录深度出现次数  
- 分层处理深度，优化查找效率  
```cpp
for(int i = mx; i >= 1; i--)
    for(int j = 1; j <= hav[i] && i <= sum; j++)
        ned[i]++, sum -= i;
```

### 3. sane1981（4星）  
**亮点**：  
- 动态调整标记的逻辑清晰  
- 包含完整的错误处理流程  
```cpp
if(temp >= need/2){
    cut = temp - need/2;
    for(int j = 1; j <= n; j++)
        if(cut == (long long)c[j].num){
            ans[c[j].id] = 0;
            break;
        }
}
```

---

## 最优思路提炼  
### 关键技巧  
**贪心 + 深度连续性**  
1. 排序后从大到小扫描，确保优先处理大数值  
2. 利用深度连续性保证可回溯性：  
   - 若累加值超过目标，差值必定存在于已选节点中  

### 代码实现  
```cpp
// 核心逻辑（GaCGe 解法优化版）
vector<pii> dep(n);
for(int i=1; i<=n; i++) dep[i] = {depth[i], i};
sort(dep.begin(), dep.end(), greater<pii>());

int target = total_depth / 2;
vector<bool> color(n+1, false);
for(auto [d, id] : dep){
    if(target >= d){
        target -= d;
        color[id] = true;
    }
    if(target == 0) break;
}
```

---

## 相似题目推荐  
1. **P1048 采药**（背包问题的经典变形）  
2. **P1064 金明的预算方案**（分组背包与树形依赖结合）  
3. **P1273 有线电视网**（树形DP与价值平衡）  

---

## 可视化代码片段  
```javascript
// Canvas 绘制核心逻辑（伪代码）
class DepthVisualizer {
  constructor(canvas) {
    this.ctx = canvas.getContext('2d');
    this.nodes = []; // 排序后的节点数据 {depth, x, y}
    this.target = total_depth / 2;
    this.currentSum = 0;
  }

  drawNode(node, isSelected) {
    const color = isSelected ? '#00FF88' : '#FF3344';
    this.ctx.fillStyle = color;
    this.ctx.fillRect(node.x, node.y, 16, 16); // 16x16 像素方块
  }

  animateSelection() {
    let i = 0;
    const animate = () => {
      if(i >= this.nodes.length) return;
      
      const node = this.nodes[i];
      if(this.currentSum + node.depth <= this.target) {
        this.currentSum += node.depth;
        this.drawNode(node, true);
        playSound('pick.wav');
      } else {
        this.backtrackAdjust(node);
      }
      
      i++;
      requestAnimationFrame(animate);
    };
    animate();
  }

  backtrackAdjust() {
    // 反向查找可移除节点的像素动画
  }
}
```

---
处理用时：77.75秒