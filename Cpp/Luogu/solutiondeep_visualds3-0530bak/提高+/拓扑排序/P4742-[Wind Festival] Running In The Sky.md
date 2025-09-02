# 题目信息

# [Wind Festival] Running In The Sky

## 题目背景

$[Night - 20:02$ $P.M.]$

夜空真美啊……但是……快要结束了呢……

## 题目描述

一天的活动过后，所有学生都停下来欣赏夜空下点亮的风筝。$Curtis$ $Nishikino$想要以更近的视角感受一下，所以她跑到空中的风筝上去了(这对于一个妹子来说有点匪夷所思)! 每只风筝上的灯光都有一个亮度 $k_i$. 由于风的作用，一些风筝缠在了一起。但是这并不会破坏美妙的气氛，缠在一起的风筝会将灯光汇聚起来，形成更亮的光源！

$Curtis$ $Nishikino$已经知道了一些风筝间的关系，比如给出一对风筝$(a,b)$, 这意味着她可以从 $a$ 跑到 $b$ 上去，但是不能返回。

现在，请帮她找到一条路径(她可以到达一只风筝多次，但只在第一次到达时她会去感受上面的灯光), 使得她可以感受到最多的光亮。同时请告诉她这条路径上单只风筝的最大亮度，如果有多条符合条件的路径，输出能产生最大单只风筝亮度的答案。

## 说明/提示

对于 $20\%$ 的数据, $0<n \le 5\times10^3, \ 0 < m \le 10^4$.

对于 $80\%$ 的数据, $0 < n \le 10^5, \ 0 < m \le 3\times10^5$.

对于 $100\%$ 的数据, $0<n\le2\times10^5,\ 0<m\le5\times10^5,\ 0<k\le200$.


## 样例 #1

### 输入

```
5 5
8 9 11 6 7
1 2
2 3
2 4
4 5
5 2```

### 输出

```
41 11```

# AI分析结果



## 算法分类
Tarjan缩点 + 拓扑排序 + 动态规划

---

## 综合分析与结论
### 核心思路
1. **强连通分量处理**：通过Tarjan算法将环状结构缩为超级节点，预处理每个SCC的权值和（sum）与内部最大值（max_val）
2. **DAG重构**：建立缩点后的有向无环图，记录各节点入度
3. **拓扑排序DP**：沿拓扑序维护两个状态：
   - dp_sum[i]：到达节点i的最大路径和
   - dp_max[i]：对应路径中的最大单点值
4. **状态转移策略**：
   - 优先保证路径和最大
   - 路径和相同时选择最大单点值

### 可视化设计要点
1. **Tarjan过程**：用不同颜色标记搜索树节点，动态显示栈内元素变化，红框高亮当前处理的SCC
2. **缩点动画**：将SCC收缩为圆形节点，内部显示sum和max_val，边动态重连
3. **拓扑排序演示**：
   - 入度为0的节点标记绿色
   - 节点状态更新时显示数值变化动画
   - 边消隐时显示入度减少过程
4. **DP状态面板**：每个节点旁悬浮显示dp_sum和dp_max的实时值
5. **复古像素风格**：
   - 节点用16x16像素方块表示
   - 数值变化时触发8-bit音效
   - 完成拓扑排序时播放FC游戏通关音效

---

## 题解清单（评分≥4星）

### 1. STrAduts（★★★★☆）
- **亮点**：详细推导Tarjan数学原理，完整注释缩点过程，拓扑排序时双状态同步维护
- **核心代码**：
```cpp
void tarjan(int x) {
    // 维护回溯值与栈状态
    if(dfn[x] == low[x]) {
        // 处理SCC的sum和max_val
    }
}
void T_Sort() {
    // 拓扑排序时的双状态转移
    if(dp[v][0] < dp[x][0] + scc[v].sum) {
        // 更新路径和与最大值
    }
}
```

### 2. Cutest_Junior（★★★★☆）
- **亮点**：独立设计DFS记忆化方案，创新性地在缩点后反向建图
- **关键技巧**：使用`dfs(u)`递归处理路径，维护全局最大值而非逐个节点比较

### 3. Poetic_Rain（★★★★☆）
- **亮点**：精简状态转移逻辑，使用结构体封装SCC信息
- **优化点**：预处理出度为0的节点，减少最终答案遍历次数

---

## 最优思路与技巧
1. **缩点预处理**  
   ```cpp
   // Tarjan处理时同步计算SCC属性
   scc[cnt].sum += val[now];
   scc[cnt].ma = max(scc[cnt].ma, val[now]);
   ```
   
2. **拓扑排序双状态转移**  
   ```cpp
   if(dp[v][0] < dp[u][0] + scc[v].sum) {
       dp[v][0] = dp[u][0] + scc[v].sum;
       dp[v][1] = max(dp[u][1], scc[v].ma);
   } else if(dp[v][0] == dp[u][0] + scc[v].sum) {
       dp[v][1] = max(dp[v][1], dp[u][1]);
   }
   ```

3. **终点快速定位**  
   预处理出度为0的节点集合，最终答案只需在这些节点中寻找最大值

---

## 相似题目推荐
1. [P3387 缩点](https://www.luogu.com.cn/problem/P3387)  
   （同模型基础题，单状态DP）
2. [P2002 消息扩散](https://www.luogu.com.cn/problem/P2002)  
   （缩点+入度分析）
3. [P2741 [USACO4.4] 重叠的图像](https://www.luogu.com.cn/problem/P2741)  
   （DAG拓扑排序应用）

---

## 调试心得摘录
> "在状态转移时，发现当路径和相同时没有及时更新最大值，导致第二个样例错误。通过添加`else if`分支比较历史最大值解决" —— STrAduts  
> "缩点后重建图时忘记过滤同SCC的边，导致拓扑排序死循环，添加`if(key[i]==key[v]) continue`后修复" —— 米奇奇米

---

## 核心算法演示（JS伪代码）
```javascript
// 像素风格可视化初始化
const canvas = new PixelCanvas({
    width: 800,
    palette: ['#2C3E50', '#E74C3C', '#3498DB'] // 暗蓝、警示红、主题蓝
});

class SCCAnimation {
    constructor(graph) {
        this.stack = []; // Tarjan栈
        this.dfn = new Array(n).fill(0);
        this.low = new Array(n).fill(0);
        this.sccColors = new Map(); // SCC颜色映射
    }

    drawNode(node, state) {
        // 绘制16x16像素节点，state包含dfn/low/color等属性
        canvas.fillStyle = this.sccColors.get(node.sccId);
        canvas.fillRect(node.x, node.y, 16, 16);
        
        // 显示dfn/low数值
        canvas.drawText(`${node.dfn}/${node.low}`, node.x+20, node.y);
    }

    tarjanStep(u) {
        // 高亮当前节点为红色
        this.drawNode(u, {color: '#E74C3C'});
        playSound('select'); // 触发音效
        
        // 模拟递归过程
        for(let v of graph.edges[u]) {
            if(!this.dfn[v]) this.tarjanStep(v);
            if(this.inStack[v]) {
                this.low[u] = Math.min(this.low[u], this.dfn[v]);
                this.drawEdge(u, v, 'highlight'); // 高亮后向边
            }
        }
        
        // 缩点完成时播放特效
        if(this.dfn[u] === this.low[u]) {
            playSound('scc_formed');
            const color = randomColor();
            while(/* 弹栈 */) {
                node.sccId = currentSCC;
                this.sccColors.set(currentSCC, color);
            }
        }
    }
}
```

---

## 关键代码实现
```cpp
// Tarjan缩点核心逻辑
void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    stk[++top] = u, in_stk[u] = true;
    for(int v : G[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(in_stk[v]) 
            low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        ++scc_cnt;
        int v;
        do {
            v = stk[top--];
            in_stk[v] = false;
            scc_id[v] = scc_cnt;
            scc_sum[scc_cnt] += val[v];
            scc_max[scc_cnt] = max(scc_max[scc_cnt], val[v]);
        } while(v != u);
    }
}

// 拓扑排序DP
void topo() {
    queue<int> q;
    for(int i=1; i<=scc_cnt; ++i) {
        dp_sum[i] = scc_sum[i];
        dp_max[i] = scc_max[i];
        if(!in_deg[i]) q.push(i);
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : newG[u]) {
            if(dp_sum[u] + scc_sum[v] > dp_sum[v]) {
                dp_sum[v] = dp_sum[u] + scc_sum[v];
                dp_max[v] = max(dp_max[u], scc_max[v]);
            } else if(dp_sum[v] == dp_sum[u] + scc_sum[v]) {
                dp_max[v] = max(dp_max[v], dp_max[u]);
            }
            if(--in_deg[v] == 0) q.push(v);
        }
    }
}
```

---
处理用时：102.36秒