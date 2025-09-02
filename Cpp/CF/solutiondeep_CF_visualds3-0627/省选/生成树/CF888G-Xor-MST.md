# 题目信息

# Xor-MST

## 题目描述

You are given a complete undirected graph with $ n $ vertices. A number $ a_{i} $ is assigned to each vertex, and the weight of an edge between vertices $ i $ and $ j $ is equal to $ a_{i}xora_{j} $ .

Calculate the weight of the minimum spanning tree in this graph.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4
1 2 3 4
```

### 输出

```
8
```

# AI分析结果



### 唯一算法分类
**Trie树分治合并**

---

### 综合分析与结论
**核心思路**  
所有题解的核心均基于 Trie 树处理异或最小值特性，结合分治思想合并子树。其中最优解法为：  
1. **排序预处理**：将数组排序后构建 Trie，确保同一子树节点连续  
2. **分治合并**：对每个 Trie 节点，递归合并左右子树，并在合并时计算最小跨子树边权  
3. **启发式优化**：遍历较小的子树元素查询异或最小值，保证时间复杂度为 O(n log n log a)  

**可视化设计要点**  
- **Trie构建动画**：展示元素按二进制位插入 Trie 的过程，高亮当前处理位  
- **合并过程演示**：用不同颜色标记左右子树，动态显示遍历较小子树元素的过程  
- **边权计算**：在跨子树查询时显示异或运算的二进制位对比，实时更新当前最小边权  
- **复古像素风格**：  
  - **颜色方案**：使用 8 位绿色调（深绿表示高位，浅绿表示低位）  
  - **音效提示**：插入节点时播放“滴”声，找到最小边时播放上扬音效  

---

### 题解评分 (≥4星)
| 作者          | 评分 | 亮点                                                         |
|---------------|------|-------------------------------------------------------------|
| Nemlit        | ★★★★☆ | 清晰模拟 Kruskal 流程，区间连续处理简化实现                  |
| ButterflyDew   | ★★★★★ | 排序预处理+Trie分治，代码简洁高效，时间复杂度最优           |
| STUDENT0      | ★★★★☆ | 虚树优化降低节点数，理论复杂度最优                           |

---

### 核心代码实现（ButterflyDew 解法）
```cpp
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
const int N=2e5+10, L=30;

int n, a[N], ch[N*L][2], Lpos[N*L], Rpos[N*L], tot;
ll ans;

void insert(int x, int id, int dep, int &rt) {
    if (!rt) rt = ++tot, Lpos[rt] = n+1;
    Lpos[rt] = min(Lpos[rt], id);
    Rpos[rt] = max(Rpos[rt], id);
    if (dep < 0) return;
    int bit = (a[id] >> dep) & 1;
    insert(x-1, id, dep-1, ch[rt][bit]);
}

ll query(int rt, int val, int dep) {
    if (dep < 0) return 0;
    int bit = (val >> dep) & 1;
    if (ch[rt][bit]) return query(ch[rt][bit], val, dep-1);
    return query(ch[rt][bit^1], val, dep-1) + (1 << dep);
}

ll dfs(int rt, int dep) {
    if (dep < 0) return 0;
    if (ch[rt][0] && ch[rt][1]) {
        ll minEdge = 1e18;
        for (int i = Lpos[ch[rt][0]]; i <= Rpos[ch[rt][0]]; ++i)
            minEdge = min(minEdge, query(ch[rt][1], a[i], dep-1) + (1 << dep));
        return dfs(ch[rt][0], dep-1) + dfs(ch[rt][1], dep-1) + minEdge;
    }
    if (ch[rt][0]) return dfs(ch[rt][0], dep-1);
    return dfs(ch[rt][1], dep-1);
}

int main() {
    scanf("%d", &n);
    for (int i=1; i<=n; ++i) scanf("%d", a+i);
    sort(a+1, a+n+1);
    int root = 0;
    for (int i=1; i<=n; ++i) insert(30, i, 30, root);
    printf("%lld\n", dfs(root, 30));
    return 0;
}
```

---

### 同类型题推荐
1. **P4551 最长异或路径**（Trie处理树路径异或极值）  
2. **P3366 【模板】最小生成树**（基础MST算法对比）  
3. **P4592 异或序列**（区间异或特性+Trie应用）

---

### 可视化设计示例（Canvas伪代码）
```javascript
class TrieAnimation {
    constructor(canvas) {
        this.ctx = canvas.getContext('2d');
        this.nodes = new Map(); // 存储节点坐标
        this.highlight = null; // 当前高亮节点
    }

    drawNode(bit, level, x, isHighlight) {
        this.ctx.fillStyle = isHighlight ? '#8BC34A' : '#4CAF50';
        this.ctx.beginPath();
        this.ctx.arc(x, 50 + level*80, 15, 0, Math.PI*2);
        this.ctx.fill();
        this.ctx.fillStyle = '#fff';
        this.ctx.fillText(bit, x-3, 50 + level*80 +5);
    }

    updateMerge(leftRoot, rightRoot) {
        // 绘制左右子树合并动画
        this.highlight = leftRoot;
        setTimeout(() => {
            this.highlight = rightRoot;
            // 添加边权计算效果
        }, 500);
    }
}
```

---

### 个人心得摘录
> "排序后Trie的每个节点对应连续区间，这是避免启发式合并的关键" —— ButterflyDew  
> "虚树优化需要重新理解Trie结构，调试时通过打印每个节点的代表值来验证" —— STUDENT0

---

### 算法比较与选择
| 方法         | 时间复杂度       | 空间复杂度 | 实现难度 |
|--------------|------------------|------------|----------|
| Trie分治     | O(n log n log a) | O(n log a) | 易       |
| Boruvka+Trie | O(n log²a)      | O(n log a) | 中等     |
| 虚树优化     | O(n log a)      | O(n)       | 难       |

**推荐选择**：ButterflyDew 的排序分治法，在效率与实现复杂度间取得最佳平衡。

---
处理用时：79.19秒