# 题目信息

# Graph Cost

## 题目描述

You are given an initially empty undirected graph with $ n $ nodes, numbered from $ 1 $ to $ n $ (i. e. $ n $ nodes and $ 0 $ edges). You want to add $ m $ edges to the graph, so the graph won't contain any self-loop or multiple edges.

If an edge connecting two nodes $ u $ and $ v $ is added, its weight must be equal to the greatest common divisor of $ u $ and $ v $ , i. e. $ \gcd(u, v) $ .

In order to add edges to the graph, you can repeat the following process any number of times (possibly zero):

- choose an integer $ k \ge 1 $ ;
- add exactly $ k $ edges to the graph, each having a weight equal to $ k + 1 $ . Adding these $ k $ edges costs $ k + 1 $ in total.

 Note that you can't create self-loops or multiple edges. Also, if you can't add $ k $ edges of weight $ k + 1 $ , you can't choose such $ k $ .For example, if you can add $ 5 $ more edges to the graph of weight $ 6 $ , you may add them, and it will cost $ 6 $ for the whole pack of $ 5 $ edges. But if you can only add $ 4 $ edges of weight $ 6 $ to the graph, you can't perform this operation for $ k = 5 $ .

Given two integers $ n $ and $ m $ , find the minimum total cost to form a graph of $ n $ vertices and exactly $ m $ edges using the operation above. If such a graph can't be constructed, output $ -1 $ .

Note that the final graph may consist of several connected components.

## 说明/提示

In the first test case, we can add an edge between the vertices $ 2 $ and $ 4 $ with $ \gcd = 2 $ . This is the only possible way to add $ 1 $ edge that will cost $ 2 $ .

In the second test case, there is no way to add $ 10 $ edges, so the answer is $ -1 $ .

In the third test case, we can add the following edges:

- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 2 $ and $ 4 $ ( $ \gcd(2, 4) = 2 $ ). Cost: $ 2 $ ;
- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 4 $ and $ 6 $ ( $ \gcd(4, 6) = 2 $ ). Cost: $ 2 $ ;
- $ k = 2 $ : edges of weight $ 3 $ : $ (3, 6) $ and $ (3, 9) $ ( $ \gcd(3, 6) = \gcd(3, 9) = 3 $ ). Cost: $ 3 $ .

 As a result, we added $ 1 + 1 + 2 = 4 $ edges with total cost $ 2 + 2 + 3 = 7 $ , which is the minimal possible cost.

## 样例 #1

### 输入

```
4
4 1
6 10
9 4
10 11```

### 输出

```
2
-1
7
21```

# AI分析结果



---

**算法分类**：数论与贪心

---

### **题解思路与核心难点**

1. **核心思路**  
   - **数学建模**：将边权为 $k+1$ 的边转化为 $\gcd(u,v)=k+1$ 的条件，通过欧拉函数计算符合条件的边数。  
   - **贪心策略**：优先选择较大的 $k$ 值，使得每次操作的成本效率最高。  
   - **预处理优化**：利用线性筛预处理欧拉函数，并计算前缀和以快速查询可用边数。

2. **关键步骤**  
   - **欧拉函数预处理**：计算 $1$ 到 $n$ 的欧拉函数值 $\varphi(i)$，并记录前缀和 $sum[i]$。  
   - **逆序枚举 $k$**：从大到小枚举 $k$，每次尽可能多地选择边权为 $k+1$ 的边，直到满足 $m$ 条边或无法继续操作。

3. **解决难点**  
   - **边数计算**：通过 $\sum_{i=1}^{\lfloor n/(k+1) \rfloor} \varphi(i)$ 快速得到当前 $k$ 能添加的边数。  
   - **贪心正确性证明**：较大的 $k$ 对应的边权更高但成本更低（每边成本为 $\frac{k+1}{k}$），优先选择能更快减少总成本。

---

### **最优题解评分**

1. **Inui_Sana (★★★★☆)**  
   - **亮点**：线性筛预处理+前缀和，时间复杂度 $O(n)$，代码简洁高效。  
   - **改进点**：缺乏对贪心策略的详细证明。

2. **MortisM (★★★★☆)**  
   - **亮点**：补充了贪心策略的数学证明，代码与思路高度匹配。  
   - **改进点**：代码实现细节未完全展示。

---

### **最优思路提炼**

1. **核心技巧**  
   - **欧拉函数前缀和**：预处理 $\varphi(i)$ 的前缀和，快速查询 $1$ 到 $x$ 的互质对数。  
   - **贪心枚举顺序**：从大到小枚举 $k$，每次取最大可能的边数。  
   - **边数计算优化**：利用 $\lfloor \frac{n}{k+1} \rfloor$ 和前缀和 $sum[\cdot]$ 直接计算可用边数。

2. **代码实现要点**  
   ```cpp
   // 预处理欧拉函数与前缀和
   const int mx = 1e6;
   for (int i = 2; i <= mx; i++) {
       if (!vis[i]) { // 线性筛
           pm[++k] = i;
           ph[i] = i - 1;
       }
       for (int j = 1; j <= k && i*pm[j] <= mx; j++) {
           vis[i*pm[j]] = true;
           if (i % pm[j] == 0) {
               ph[i*pm[j]] = ph[i] * pm[j];
               break;
           }
           ph[i*pm[j]] = ph[i] * (pm[j] - 1);
       }
       sum[i] = sum[i-1] + ph[i]; // 前缀和
   }
   ```

---

### **可视化算法演示**

1. **动画设计**  
   - **像素风格界面**：用网格表示不同 $k$ 值，颜色区分已处理/未处理的 $k$。  
   - **动态更新**：  
     - **当前 $k$ 值**：高亮显示正在处理的 $k$。  
     - **剩余边数 $m$**：实时显示剩余需添加的边数。  
     - **累计成本**：显示当前总成本。  
   - **音效反馈**：  
     - 成功添加边时播放短促“滴”声；  
     - $m=0$ 时播放胜利音效；失败时播放低沉音效。

2. **交互设计**  
   - **步进控制**：允许单步执行观察每个 $k$ 的处理过程。  
   - **自动演示**：AI 模式自动选择最优 $k$，动态展示贪心策略。

---

### **相似题目推荐**

1. **CF 1731E**：同题不同难度版本。  
2. **洛谷 P2568**：利用欧拉函数统计互质对数。  
3. **洛谷 P1447**：需要计算 $\gcd$ 相关性质的应用题。

---

### **个人心得摘录**

> “贪心策略的证明是关键，较大的 $k$ 看似成本高，但均摊到每边更低。” —— MortisM  
> “线性筛预处理是数论题的核心优化手段。” —— Inui_Sana

---

### **代码实现（核心逻辑）**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
ll sum[N];
int ph[N], pm[N], cnt;
bool vis[N];

void init() {
    ph[1] = 1;
    for (int i = 2; i <= 1e6; i++) {
        if (!vis[i]) {
            pm[++cnt] = i;
            ph[i] = i - 1;
        }
        for (int j = 1; j <= cnt && i * pm[j] <= 1e6; j++) {
            vis[i * pm[j]] = true;
            if (i % pm[j] == 0) {
                ph[i * pm[j]] = ph[i] * pm[j];
                break;
            }
            ph[i * pm[j]] = ph[i] * (pm[j] - 1);
        }
        sum[i] = sum[i - 1] + ph[i];
    }
}

void solve() {
    int n; ll m;
    scanf("%d%lld", &n, &m);
    ll ans = 0;
    for (int k = n - 1; k >= 1 && m > 0; k--) {
        int w = k + 1;
        int max_u = n / w;
        ll edges = sum[max_u];
        ll take = min(edges / k, m / k);
        if (take > 0) {
            ans += take * w;
            m -= take * k;
        }
    }
    printf("%lld\n", m == 0 ? ans : -1);
}

int main() {
    init();
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}
```

---
处理用时：93.08秒