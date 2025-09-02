# 题目信息

# Privatization

## 题目描述

There is a developed network of flights between Berland and Beerland. All of them belong to the Berland state company BerAvia. Each flight connects some Berland city with some Beerland city. For each flight airplanes fly in both directions.

Changes are coming to Berland — the state decided to privatize BerAvia, namely, to sell out all flights to $ t $ private companies. Each of these companies wants to get the maximal number of flights, so if the Berland flights are sold unevenly, Berland can be accused of partiality. Berland Government decided to sell the flights as evenly as possible between the $ t $ companies.

The unevenness of the distribution of flights between companies is calculated as follows. For each city $ i $ (both Berland and Beerland) we'll calculate the value of

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF212A/8cb4dc3a97b60ddf7de9158fd0e56414b7e627be.png) where $ a_{ij} $ is the number of flights from city $ i $ , which belong to company $ j $ . The sum of $ w_{i} $ for all cities in both countries is called the unevenness of the distribution. The distribution with the minimal unevenness is the most even one.Help the Berland government come up with the most even distribution plan of selling flights.

## 样例 #1

### 输入

```
3 5 8 2
1 4
1 3
3 3
1 2
1 1
2 1
1 5
2 2
```

### 输出

```
4
2 1 2 1 2 1 2 2 ```

# AI分析结果



### 综合分析与结论

**核心思路与难点**  
题目要求将二分图的边均匀分配给 $t$ 个公司，最小化各节点相邻边数量的极差总和。关键结论是：答案等于度数不整除 $t$ 的节点数量。这一结论的证明基于每个节点的极差至少为 $1$（当度数不整除 $t$ 时），否则为 $0$。构造方法通过贪心调整策略处理颜色冲突，确保每个块内的颜色均匀分配。

**贪心策略与可视化设计**  
贪心策略的核心是动态调整边的颜色分配：  
1. **颜色选择**：优先为当前边两端选择可用颜色。  
2. **冲突处理**：若两端颜色冲突，递归翻转已有边颜色（类似寻找增广路径）。  
3. **维护块结构**：将度数拆分为多个大小为 $t$ 的块，每个块内颜色均匀分布。  

**可视化演示设计**  
- **动画效果**：以像素风格展示边的分配过程，高亮当前处理的边及涉及的颜色翻转路径。  
- **交互功能**：步进执行、速度调节，音效提示颜色分配成功或冲突调整。  
- **复古风格**：使用 8-bit 颜色块表示不同公司，背景音乐增强沉浸感。

---

### 题解清单（≥4星）

1. **zghtyarecrenj（4.5星）**  
   - **亮点**：结论简洁，代码高效，贪心调整策略巧妙。  
   - **关键代码**：递归翻转颜色解决冲突，时间复杂度接近线性。  
   - **心得**：“通过递归翻转颜色链，确保每一步的局部最优性。”

2. **TianyiLemon（4星）**  
   - **亮点**：网络流方法理论严谨，正确性易证。  
   - **缺点**：实现复杂度较高，多次调用 Dinic 算法。  

---

### 最优思路与代码实现

**核心贪心逻辑**  
```cpp
void flip(int x, int s, int t) {
    int e = f[x][s], y = (x == u[e]) ? v[e] : u[e];
    f[x][s] = f[y][s] = 0;
    if (f[y][t]) flip(y, t, s); // 递归翻转路径
    f[x][t] = f[y][t] = e, res[e] = t;
}
```
**代码说明**：当颜色冲突时，递归翻转颜色链，确保新颜色可分配。

**完整代码**（zghtyarecrenj解法）  
```cpp
#include <bits/stdc++.h>
const int N = 405, M = 1e4 + 5;
int n, m, k, t, res[M], deg[N], id[N], tot, u[M], v[M], f[M*5][N];
int find(int x) {
    for(int i=1; i<=t; ++i) if(!f[x][i]) return i;
    return 0;
}
void flip(int x, int s, int t) { /* 同上 */ }
int main() {
    scanf("%d%d%d%d", &n, &m, &k, &t);
    for(int i=1; i<=k; ++i) {
        scanf("%d%d", u+i, v+i); v[i] += n;
        if(deg[u[i]]%t == 0) id[u[i]] = ++tot;
        if(deg[v[i]]%t == 0) id[v[i]] = ++tot;
        ++deg[u[i]], ++deg[v[i]];
        u[i] = id[u[i]], v[i] = id[v[i]];
        int t1 = find(u[i]), t2 = find(v[i]);
        if(t1 == t2) f[u[i]][t1] = f[v[i]][t1] = i, res[i] = t1;
        else {
            if(f[u[i]][t2]) flip(u[i], t2, t1);
            f[u[i]][t2] = f[v[i]][t2] = i, res[i] = t2;
        }
    }
    int ans = 0;
    for(int i=1; i<=n+m; ++i) if(deg[i]%t) ++ans;
    printf("%d\n", ans);
    for(int i=1; i<=k; ++i) printf("%d ", res[i]);
    return 0;
}
```

---

### 同类型题与推荐

**通用解法**  
- **度数分配问题**：通过模运算分析极差下界，贪心调整构造最优解。  
- **边染色问题**：利用增广路径思想解决冲突（如匈牙利算法变种）。  

**推荐题目**  
1. [P6062 边染色问题](https://www.luogu.com.cn/problem/P6062)  
2. [CF1103D Professional layer](https://www.luogu.com.cn/problem/CF1103D)  
3. [P2744 稳定婚姻问题](https://www.luogu.com.cn/problem/P2744)  

---

### 可视化与游戏化设计

**像素风格演示**  
- **颜色块**：用不同 8-bit 色块表示公司编号。  
- **动画流程**：  
  1. 高亮当前处理边，显示两端可用颜色。  
  2. 若冲突，显示翻转路径，伴随音效。  
- **音效设计**：成功分配时播放上升音调，冲突时短促提示音。

**AI自动演示**  
- **逻辑**：按输入顺序处理边，自动选择颜色或触发翻转。  
- **关卡模式**：每成功分配 10 条边解锁下一阶段，积分奖励。

---
处理用时：87.49秒