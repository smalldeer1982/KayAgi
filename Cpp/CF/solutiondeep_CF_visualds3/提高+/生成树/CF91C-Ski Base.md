# 题目信息

# Ski Base

## 题目描述

A ski base is planned to be built in Walrusland. Recently, however, the project is still in the constructing phase. A large land lot was chosen for the construction. It contains $ n $ ski junctions, numbered from $ 1 $ to $ n $ . Initially the junctions aren't connected in any way.

In the constructing process $ m $ bidirectional ski roads will be built. The roads are built one after another: first the road number $ 1 $ will be built, then the road number $ 2 $ , and so on. The $ i $ -th road connects the junctions with numbers $ a_{i} $ and $ b_{i} $ .

Track is the route with the following properties:

- The route is closed, that is, it begins and ends in one and the same junction.
- The route contains at least one road.
- The route doesn't go on one road more than once, however it can visit any junction any number of times.

Let's consider the ski base as a non-empty set of roads that can be divided into one or more tracks so that exactly one track went along each road of the chosen set. Besides, each track can consist only of roads from the chosen set. Ski base doesn't have to be connected.

Two ski bases are considered different if they consist of different road sets.

After building each new road the Walrusland government wants to know the number of variants of choosing a ski base based on some subset of the already built roads. The government asks you to help them solve the given problem.

## 说明/提示

Let us have 3 junctions and 4 roads between the junctions have already been built (as after building all the roads in the sample): 1 and 3, 2 and 3, 2 roads between junctions 1 and 2. The land lot for the construction will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF91C/28b4727aa73cce1da2aeb595e550d496be82b411.png)The land lot for the construction will look in the following way:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF91C/28b4727aa73cce1da2aeb595e550d496be82b411.png)We can choose a subset of roads in three ways:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF91C/f9fe4e0ad2052df89d1d0881cb2113925e271782.png)In the first and the second ways you can choose one path, for example, 1 - 2 - 3 - 1. In the first case you can choose one path 1 - 2 - 1.

## 样例 #1

### 输入

```
3 4
1 3
2 3
1 2
1 2
```

### 输出

```
0
0
1
3
```

# AI分析结果


### Kay的C++算法解析：Ski Base 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`图论与动态计数`  
🗣️ **初步分析**：  
> 解决"Ski Base"关键在于理解**图论中树边与非树边的性质**及**动态计数原理**。想象滑雪基地是节点间的路径网络：树边（连接不同连通块）构成骨架，非树边（同连通块内）则添加可选环路。每加入一条边时：  
> - 若为树边（减少连通块），不影响答案  
> - 若为非树边（形成新环），答案变为 \(2^{\text{非树边数}} - 1\)  
> **可视化设计**：采用8位像素网格展示节点（像素方块），树边用绿色实线，非树边用黄色虚线。添加边时：  
> - 树边：播放"连接"音效，连通块合并动画（像素块融合）  
> - 非树边：播放"叮"音效，显示环路形成（闪烁黄色路径），右侧计数器 \(2^k-1\) 动态更新  

---

#### 2. 精选优质题解参考
**题解一（来源：隔壁泞2的如心）**  
* **点评**：  
  思路直击本质——将滑雪基地方案转化为**非树边子集计数**（\(2^{\text{非树边数}}-1\)）。代码用并查集判连通性，动态维护非树边数，逻辑清晰。亮点在于跳过复杂数学推导，直接利用图论性质优化，时间复杂度 \(O(m \alpha(n))\)。变量名`cnt`（非树边数）简洁准确，边界处理完整（模 \(10^9+9\)）。

---

#### 3. 核心难点辨析与解题策略
1. **难点：动态维护连通性**  
   * **分析**：每加边需快速判断是否连接同一连通块。并查集的路径压缩+按秩合并使操作均摊 \(O(\alpha(n))\)。  
   * 💡 **学习笔记**：并查集是动态连通性问题的黄金标准。

2. **难点：非树边与答案的映射**  
   * **分析**：非树边形成环路，每个环路可选/不选，独立贡献方案数。树边仅维持连通性，不增加选择自由度。  
   * 💡 **学习笔记**：答案仅依赖非树边数 \(k\)，即 \(2^k-1\)。

3. **难点：大数幂运算优化**  
   * **分析**：需快速计算 \(2^k \mod 10^9+9\)。预处理幂数组避免重复计算，空间换时间。  
   * 💡 **学习笔记**：固定模数时，预处理幂是通用优化技巧。

✨ **解题技巧总结**  
- **技巧1：并查集优化**：路径压缩+按秩合并提升性能  
- **技巧2：问题等价转换**：将复杂方案计数转化为非树边子集计数  
- **技巧3：预处理幂**：加速模意义下的指数运算  

---

#### 4. C++核心代码实现赏析
**通用核心实现**  
```cpp
#include <iostream>
#include <vector>
using namespace std;
const int MOD = 1000000009;

struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n+1);
        rank.resize(n+1, 0);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool union_set(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
};

int main() {
    int n, m, cnt = 0;
    cin >> n >> m;
    vector<int> pow2(m+1, 1);
    for (int i = 1; i <= m; ++i) 
        pow2[i] = (pow2[i-1] * 2) % MOD;

    DSU dsu(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        if (dsu.find(u) != dsu.find(v)) 
            dsu.union_set(u, v);
        else 
            cnt++;
        cout << (pow2[cnt] - 1 + MOD) % MOD << '\n';
    }
}
```

**题解一核心片段**  
```cpp
if (dsu.find(u) != dsu.find(v)) 
    dsu.union_set(u, v);
else 
    cnt++;
cout << (pow2[cnt] - 1 + MOD) % MOD << '\n';
```
* **代码解读**：  
  - `find(u) != find(v)`：判断是否同连通块（树边）  
  - `else cnt++`：非树边计数增加  
  - `pow2[cnt]-1`：即时计算当前方案数  
* 💡 **学习笔记**：并查集操作与计数分离，逻辑分治清晰。

---

#### 5. 算法可视化：像素动画演示
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF91C/28b4727aa73cce1da2aeb595e550d496be82b411.png)  
* **主题**：8位像素滑雪场建设模拟  
* **核心交互**：  
  1. **节点**：像素方块（不同颜色表不同连通块）  
  2. **树边**：绿色实线，连接时播放"咔嚓"音效，方块合并  
  3. **非树边**：黄色虚线，添加时：  
     - 播放"叮！"音效  
     - 显示黄色环路动画（如贪吃蛇绕圈）  
     - 右侧 \(2^k-1\) 计数器跳增  
  4. **控制面板**：  
     - 步进/暂停/重置按钮  
     - 速度滑块（调速动画）  
     - 实时显示当前非树边数 \(k\)  

---

#### 6. 拓展练习与相似问题思考
* **通用技巧迁移**：  
  图论中树边/非树边性质可用于：  
  1. 动态最小生成树维护  
  2. 环基空间计数  
  3. 连通性动态查询优化  

* **洛谷推荐**：  
  1. **P3367** 并查集模板 → 掌握连通性基础  
  2. **P1991** 最小生成树 → 理解树边核心作用  
  3. **P4513** 动态环计数 → 拓展非树边应用  

---

#### 7. 学习心得与经验分享
> **经验摘录**：  
> “本题关键在于发现方案数仅与非树边相关，避免陷入复杂数学推导。”  
>   
> **Kay点评**：  
> 经验直击本质——先抽象问题再选择工具，避免过度设计。调试时可画小样例验证树边/非树边影响。

--- 
通过像素动画观察非树边如何逐步增加方案选择，能直观理解 \(2^k-1\) 的由来！下次遇到图论计数时，记得先问：**树边和非树边分别贡献什么？** 🎿

---
处理用时：296.64秒