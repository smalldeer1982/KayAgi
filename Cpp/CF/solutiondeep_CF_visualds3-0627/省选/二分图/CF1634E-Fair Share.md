# 题目信息

# Fair Share

## 题目描述

Even a cat has things it can do that AI cannot.

— Fei-Fei Li



You are given $ m $ arrays of positive integers. Each array is of even length.

You need to split all these integers into two equal multisets $ L $ and $ R $ , that is, each element of each array should go into one of two multisets (but not both). Additionally, for each of the $ m $ arrays, exactly half of its elements should go into $ L $ , and the rest should go into $ R $ .

Give an example of such a division or determine that no such division exists.

## 说明/提示

In the first array, we add the first element to $ R $ and the second to $ L $ . Now $ L = \{2\} $ , and $ R = \{1\} $ .

In the second array, we add the first and third elements to $ L $ and the rest to $ R $ . Now $ L = \{1, 2, 3\} $ and $ R = \{1, 2, 3\} $ .

In the third array, we add elements 2, 3, and 6 to $ L $ , and others — to $ R $ . As a result, $ L = R = \{1, 1, 2, 2, 3, 3\} $ .

## 样例 #1

### 输入

```
3
2
1 2
4
1 2 3 3
6
1 1 2 2 3 3```

### 输出

```
YES
RL
LRLR
RLLRRL```

# AI分析结果



**唯一算法分类**：图论建模 + 二分图染色

---

### **综合分析与结论**

**核心思路**：  
1. **必要条件检查**：所有数值出现次数必须为偶数，否则无法均分到两个集合，直接无解。  
2. **图论建模**：  
   - **数值边**：每个数值的奇数次出现位置与偶数次出现位置连边，强制二者分配到不同集合。  
   - **位置边**：同一数组中相邻元素连边，确保每个数组恰好一半元素进入每个集合。  
3. **偶环性质**：每个点度数为2（一条数值边，一条位置边），形成的环必为偶环，可二分图染色。  
4. **染色构造解**：DFS或BFS遍历每个连通块，交替染色为L/R，最终输出结果。

**难点与解决**：  
- **正确建边**：需同时处理数值边和位置边，确保每个点有且仅有两条边。  
- **高效性**：离散化或`map`管理数值出现次数，避免重复配对。  
- **环的性质保证**：通过数学证明环长为偶数，确保二分图存在。

**可视化设计**：  
1. **动画步骤**：  
   - **数值配对**：高亮当前处理的数值，动态显示奇数次与偶数次位置连边。  
   - **相邻连边**：数组内相邻元素以不同颜色（如绿色）连边。  
   - **染色过程**：DFS遍历时，用红/蓝交替染色当前节点，突出递归路径。  
2. **复古像素风格**：  
   - 数值节点显示为8位像素方块，数值边用黄色，位置边用青色。  
   - 背景音乐为8位电子音效，染色时播放短促“滴”声，无解时播放低沉音效。  
3. **交互控制**：  
   - 步进按钮单步执行建边和染色过程，速度可调。  
   - 自动演示模式下，AI自动完成所有操作，类似贪吃蛇移动。

---

### **题解清单 (≥4星)**

1. **dingcx (5星)**  
   - **亮点**：建边逻辑清晰，代码简洁高效，利用`map`跟踪数值配对，DFS染色直观。  
   - **个人心得**：提到贪心陷阱样例，强调偶环必要性，帮助理解算法正确性。  
2. **I_am_Accepted的Algorithm 2 (4星)**  
   - **亮点**：将数值和位置边视为二分图，严格数学证明环的偶性，代码模块化。  
3. **ethan0328 (4星)**  
   - **亮点**：离散化处理数值，使用`pair`管理数组位置，代码结构清晰易扩展。

---

### **核心代码实现**

**dingcx的代码关键逻辑**：  
```cpp
map<int, int> mp; // 记录数值的最近出现位置
vector<int> e[MAXN << 1]; // 邻接表

// 建边逻辑（部分）
for (int i = 1; i <= m; i++) {
    n[i] = read();
    for (int j = 1; j <= n[i]; j++) {
        tot++;
        int x = read();
        // 处理数组内相邻元素连边
        if (j % 2 == 0) {
            e[tot].push_back(tot - 1);
            e[tot - 1].push_back(tot);
        }
        // 处理数值配对连边
        if (mp.count(x)) {
            e[tot].push_back(mp[x]);
            e[mp[x]].push_back(tot);
            mp.erase(x);
        } else {
            mp[x] = tot;
        }
    }
}

// DFS染色
void dfs(int u, int num) {
    ans[u] = num, vis[u] = true;
    for (int v : e[u]) {
        if (!vis[v]) dfs(v, num ^ 1);
    }
}
```

---

### **同类型题与拓展**

1. **洛谷P3386 二分图最大匹配**：匈牙利算法或网络流。  
2. **Codeforces 862B (树的最大二分图边数)**：DFS染色统计两类节点数。  
3. **LeetCode 785. Is Graph Bipartite?**：直接应用二分图染色。

---

### **个人心得摘录**

- **dingcx**：强调“贪心策略易错”，需通过严格建图保证正确性。  
- **lfxxx**：调试中发现未离散化导致哈希冲突，提醒注意数据范围。

---

### **复古游戏化动画实现**

```javascript
// 示例：Canvas绘制数值节点和边（伪代码）
class PixelGraph {
    constructor(data) {
        this.nodes = []; // {x, y, value, color}
        this.edges = []; // {from, to, type}
        // 初始化数值边和位置边
        data.forEach((arr, i) => {
            arr.forEach((num, j) => {
                const node = {x: i*50, y: j*50, value: num, color: 0xFFFFFF};
                this.nodes.push(node);
                if (j % 2 === 1) this.edges.push({from: node.id-1, to: node.id, type: 'pos'});
                if (lastNumPos[num]) {
                    this.edges.push({from: lastNumPos[num], to: node.id, type: 'val'});
                    delete lastNumPos[num];
                } else lastNumPos[num] = node.id;
            });
        });
    }

    draw(ctx) {
        this.edges.forEach(edge => {
            ctx.strokeStyle = edge.type === 'val' ? '#FFFF00' : '#00FFFF';
            drawLine(edge.from, edge.to);
        });
        this.nodes.forEach(node => {
            ctx.fillStyle = node.color === 'L' ? '#FF0000' : '#0000FF';
            fillRect(node.x, node.y, 20, 20);
        });
    }
}
```

**音效设计**：  
- 建边时播放“哔”声，染色时播放“嘟”声，错误时播放爆炸音效。  
- 背景音乐为8位循环旋律，增强复古游戏氛围。

---
处理用时：88.08秒