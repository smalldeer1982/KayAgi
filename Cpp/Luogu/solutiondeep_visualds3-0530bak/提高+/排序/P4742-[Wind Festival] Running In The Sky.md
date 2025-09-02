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



## 唯一算法分类
图论-缩点与拓扑排序

## 综合分析与结论

### 核心算法流程
1. **Tarjan缩点**：通过DFS遍历识别强连通分量（SCC），每个SCC的点权和作为新节点权值，同时记录SCC内最大点权
2. **重构DAG**：将原图中的边映射到SCC节点之间，确保新图无环
3. **拓扑排序+DP**：
   - 维护两个状态数组：`dp_sum`（路径最大和）和`dp_max`（路径最大单点值）
   - 转移时优先比较路径和，若路径和相同则比较最大单点值
   - 使用队列处理入度为0的节点，动态更新相邻节点状态

### 可视化设计要点
- **像素风格展示**：用不同色块表示SCC（如红色块表示当前处理的SCC），蓝色箭头表示边
- **动画步骤**：
  1. Tarjan过程：DFS遍历时用黄色高亮当前节点，栈用灰色块表示
  2. 缩点阶段：将同一SCC的节点合并为一个大色块，显示sum/max值
  3. 拓扑排序：绿色标记入度0的节点，紫色线条表示DP状态传播
- **音效设计**：
  - 发现SCC时播放"ding"声
  - DP状态更新时播放"blip"声
  - 最终答案出现时播放胜利音效

## 题解清单（评分≥4星）

### 1. STrAduts（★★★★☆）
- **亮点**：完整推导Tarjan原理，双状态转移处理清晰
- **代码**：独立处理缩点后的sum/max计算，拓扑时分层更新状态

### 2. Cutest_Junior（★★★★☆）
- **亮点**：使用结构体封装状态，处理入度逻辑严谨
- **心得**："注意当路径和相同时要额外判断最大值"

### 3. Poetic_Rain（★★★★☆）
- **亮点**：使用链式前向星高效存图，状态转移条件判断简洁
- **优化**：预处理出度为0的节点加速最终答案比较

## 核心代码实现

```cpp
// Tarjan缩点核心代码
void tarjan(int u) {
    low[u] = dfn[u] = ++idx;
    stk[++top] = u; vis[u] = 1;
    for(int v : G[u]) {
        if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if(vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        scc_cnt++;
        int v; do {
            v = stk[top--];
            vis[v] = 0;
            scc_id[v] = scc_cnt;
            sum[scc_cnt] += a[v];
            maxv[scc_cnt] = max(maxv[scc_cnt], a[v]);
        } while(v != u);
    }
}

// 拓扑排序DP核心
void topo() {
    queue<int> q;
    for(int i=1; i<=scc_cnt; ++i) {
        dp[i] = {sum[i], maxv[i]};
        if(!in[i]) q.push(i);
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : newG[u]) {
            if(--in[v] == 0) q.push(v);
            if(dp[v].sum < dp[u].sum + sum[v]) {
                dp[v] = {dp[u].sum + sum[v], max(maxv[v], dp[u].max)};
            } else if(dp[v].sum == dp[u].sum + sum[v]) {
                dp[v].max = max(dp[v].max, max(dp[u].max, maxv[v]));
            }
        }
    }
}
```

## 同类型题目推荐
1. **P3387** 【模板】缩点 - 基础缩点应用
2. **P2002** 消息扩散 - 缩点后求入度为0的SCC数量 
3. **P1262** 间谍网络 - 结合缩点与贪心选择

## 可视化设计（复古像素版）

**实现方案**：
1. **Canvas绘制**：
   - 使用32x32像素的色块表示节点
   - 边用16px宽的箭头表示
   - 当前操作元素添加白色边框

2. **动画控制**：
```javascript
class TarjanViz {
    constructor(canvas) {
        this.ctx = canvas.getContext('2d');
        this.nodes = [/* 节点坐标数据 */];
        this.speed = 100; // 每步动画间隔(ms)
    }
    
    drawSCC(id, color) {
        // 用指定颜色绘制SCC区域
        this.ctx.fillStyle = color;
        this.nodes.filter(n => n.scc == id).forEach(n => {
            this.ctx.fillRect(n.x*40, n.y*40, 32, 32);
        });
    }
    
    async runTarjan() {
        // DFS过程动画
        for(let u of nodes) {
            this.highlight(u, YELLOW);
            await delay(this.speed);
            // ...递归过程
        }
    }
}
```

3. **音效触发**：
- `audioContext`播放8bit音效：
  - 发现SCC：方波440Hz短脉冲
  - 状态更新：噪声+正弦波混合
  - 错误操作：低频方波200Hz

## 个人心得摘录
> "调试时发现当两个SCC权值和相同时，必须同时比较历史最大值和当前SCC的最大值，这个边界条件卡了我两个小时" —— Cutest_Junior

> "拓扑排序一定要在入度减为0时才进行状态转移，否则会漏掉更优路径" —— Poetic_Rain

## 扩展思考
可尝试将DP状态扩展为：
- `dp[u][0]`: 最大路径和
- `dp[u][1]`: 对应的最大单点值
- `dp[u][2]`: 次大路径和（用于处理特定条件下的最优解）

适用于需要维护多状态最优解的场景，如求第K优路径等变种问题。

---
处理用时：71.56秒