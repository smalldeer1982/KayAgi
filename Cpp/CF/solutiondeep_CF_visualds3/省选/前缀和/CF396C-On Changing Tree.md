# 题目信息

# On Changing Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is a vertex number $ 1 $ .

Initially all vertices contain number $ 0 $ . Then come $ q $ queries, each query has one of the two types:

- The format of the query: $ 1 $ $ v $ $ x $ $ k $ . In response to the query, you need to add to the number at vertex $ v $ number $ x $ ; to the numbers at the descendants of vertex $ v $ at distance $ 1 $ , add $ x-k $ ; and so on, to the numbers written in the descendants of vertex $ v $ at distance $ i $ , you need to add $ x-(i·k) $ . The distance between two vertices is the number of edges in the shortest path between these vertices.
- The format of the query: $ 2 $ $ v $ . In reply to the query you should print the number written in vertex $ v $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

Process the queries given in the input.

## 说明/提示

You can read about a rooted tree here: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 样例 #1

### 输入

```
3
1 1
3
1 1 2 1
2 1
2 2
```

### 输出

```
2
1
```

# AI分析结果


# 💡 Kay的C++算法解析：On Changing Tree 深入学习指南 💡

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`DFS序与树状数组/线段树应用`

🗣️ **初步分析**：
> 解决这道题的关键在于将树形问题转化为线性问题。想象一下，树就像一座城市，DFS序就是给每个房子（节点）编上门牌号（时间戳），让相邻的房子在编号上连续。这样，处理一个社区（子树）就变成了处理一条街道（连续区间）。本题中，我们使用两个树状数组分别管理：
> - 常数部分（x + dep[v]*k）：就像给整个社区发固定补贴
> - 线性部分（k）：像按家庭人口数发放的补贴，需要结合每家深度计算
> 
> 可视化设计思路：
> - 用像素网格展示树的DFS遍历过程，每个节点变成彩色方块
> - 修改操作时，目标子树区域会闪烁黄光，同时显示两个树状数组的更新动画
> - 查询时，高亮目标节点并显示计算公式：(绿色方块值) - (蓝色方块值)×(深度)
> - 复古游戏元素：操作成功时播放8-bit音效，完成5次查询解锁新关卡

---

## 2. 精选优质题解参考

**题解一（nekko）**
* **点评**：此解法思路清晰直白，将修改操作拆解为`(x+dep[v]*k)`和`k`两个独立部分，用两个树状数组维护。代码中：
  - 变量命名规范（`l/r`数组存储DFS序）
  - 算法高效（O(qlogn)复杂度）
  - 边界处理严谨（取模操作全面）
  亮点在于用数学拆解规避了复杂数据结构，是竞赛实战的优秀参考

**题解二（pzc2004）**
* **点评**：虽然采用树链剖分但核心思路一致，亮点在于：
  - 完整展示了线段树实现细节
  - 包含调试数据生成器
  - 代码模块化（分离Update/Query）
  稍显复杂但教学价值高，特别适合想深入线段树的同学

**题解三（shadowice1984）**
* **点评**：创新性离线解法，亮点：
  - 通过DFS栈动态管理有效修改
  - 避免显式区间操作
  - 内存效率更优
  适合高阶学习者理解时间维度的处理技巧

---

## 3. 核心难点辨析与解题策略

1. **难点：子树到区间的映射**
   * **分析**：DFS遍历时记录每个节点的进入/离开时间，子树即对应`[in[v], out[v]]`的连续区间
   * 💡 学习笔记：DFS序是树形问题转线性的桥梁

2. **难点：线性修改的分解**
   * **分析**：将`x - (dep[u]-dep[v])*k`拆解为：
     - 常数项：`x + dep[v]*k`
     - 线性项：`-dep[u]*k`
   * 💡 学习笔记：复杂操作分解为独立变量维护

3. **难点：负数取模处理**
   * **分析**：计算结果可能为负，需`(ans%mod + mod)%mod`确保非负
   * 💡 学习笔记：模运算中负数要加模数校正

### ✨ 解题技巧总结
- **空间换清晰度**：用两个独立数据结构管理不同变量
- **树状数组优选**：区间加/单点查场景中比线段树更简洁
- **可视化调试**：小规模数据手工模拟DFS序建立过程

---

## 4. C++核心代码实现赏析

**本题通用核心实现**
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5+10, mod = 1e9+7;

int n, in[N], out[N], dep[N], cnt;
vector<int> g[N];

struct BIT {
    ll tree[N];
    void update(int x, ll v) {
        for(; x<=n; x+=x&-x) tree[x] = (tree[x]+v) % mod;
    }
    void add(int l, int r, ll v) {
        update(l, v); update(r+1, -v);
    }
    ll query(int x) {
        ll res = 0;
        for(; x; x-=x&-x) res = (res+tree[x]) % mod;
        return res;
    }
} T1, T2; // T1:常数部分 T2:k系数

void dfs(int u, int d) {
    in[u] = ++cnt;
    dep[u] = d;
    for(int v : g[u]) dfs(v, d+1);
    out[u] = cnt;
}

int main() {
    scanf("%d", &n);
    for(int i=2; i<=n; i++) {
        int f; scanf("%d", &f);
        g[f].push_back(i);
    }
    dfs(1, 1);
    
    int q; scanf("%d", &q);
    while(q--) {
        int op, v; scanf("%d%d", &op, &v);
        if(op == 1) {
            ll x, k; scanf("%lld%lld", &x, &k);
            T1.add(in[v], out[v], (x + dep[v]*k) % mod);
            T2.add(in[v], out[v], k);
        } else {
            ll res = (T1.query(in[v]) - dep[v]*T2.query(in[v]) % mod + mod) % mod;
            printf("%lld\n", res);
        }
    }
    return 0;
}
```

**代码解读概要**：
- `BIT`封装树状数组的区间加/单点查
- `dfs`预处理DFS序和深度
- 修改操作：分解为常数项和线性项更新
- 查询操作：组合两项结果并处理负数取模

---

## 5. 算法可视化：像素动画演示

### 像素探险家：树状数组的魔法森林
**设计理念**：用FC红白机风格呈现算法过程，让学习像闯关游戏

**核心演示流程**：
```mermaid
graph LR
A[开始] --> B[选择节点v]
B --> C[显示DFS序映射]
C --> D[黄光闪烁子树区域]
D --> E[显示T1 + x+dep*v*k]
D --> F[显示T2 + k]
E --> G[查询节点u]
F --> G
G --> H[高亮u位置]
H --> I[计算公式 T1[u] - dep*u*T2[u]]
I --> J[胜利音效+得分]
```

**交互控制面板**：
```plaintext
+---------------------------+
| [开始] [暂停] [重置]      |
| 速度：[- o +]             |
|                           |
| 当前操作：1 v x k         |
| 子树范围：[in_v, out_v]   |
+---------------------------+
```

**技术实现细节**：
1. 用16色调色板绘制像素树，每个节点为16x16方块
2. 树状数组更新时，对应区间产生"像素粒子流动"效果
3. 关键操作音效：
   - 修改：8-bit "滴"声（440Hz）
   - 查询成功：超级玛丽金币声
   - 错误：恶魔城受伤音效

---

## 6. 拓展练习与相似问题

**通用技巧迁移**：
1. 子树统计 → DFS序 + 前缀和
2. 路径查询 → 树链剖分/LCA
3. 动态修改 → 离线处理时间维

**洛谷推荐**：
1. **P3384 树链剖分**  
   → 巩固DFS序与路径处理的进阶应用
   
2. **P3178 树上操作**  
   → 练习子树修改与路径查询的组合操作
   
3. **P3368 树状数组2**  
   → 掌握一维区间操作的简化模型

---

## 7. 学习心得与经验分享

> **nekko的心得**：  
> "这不是套路题么...为什么是紫牌啊..."  
> → 反映DFS序+树状数组是经典组合

**Kay总结**：  
当遇到子树修改问题时，立即思考：
1. 能否DFS序转区间？
2. 修改项能否线性分解？
3. 是否需要离线处理时间轴？

掌握这三点，此类问题皆可迎刃而解。

---

掌握树形问题的核心在于转化与分解。通过本指南，相信大家已理解如何将树上操作转化为线性处理，并用数据结构高效实现。继续在算法世界中探险吧，少年！🚀

---
处理用时：186.35秒