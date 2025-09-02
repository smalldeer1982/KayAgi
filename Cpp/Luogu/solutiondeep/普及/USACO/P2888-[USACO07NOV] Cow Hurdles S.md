# 题目信息

# [USACO07NOV] Cow Hurdles S

## 题目描述

Farmer John wants the cows to prepare for the county jumping competition, so Bessie and the gang are practicing jumping over hurdles. They are getting tired, though, so they want to be able to use as little energy as possible to jump over the hurdles.

Obviously, it is not very difficult for a cow to jump over several very short hurdles, but one tall hurdle can be very stressful. Thus, the cows are only concerned about the height of the tallest hurdle they have to jump over.

The cows' practice room has $N$ stations, conveniently labeled $1,\dots,N$. A set of $M$ one-way paths connects pairs of stations; the paths are also conveniently labeled $1,\dots,M$. Path $i$ travels from station $S_i$ to station $E_i$ and contains exactly one hurdle of height $H_i$. Cows must jump hurdles in any path they traverse.

The cows have $T$ tasks to complete. Task $i$ comprises two distinct numbers, $A_i$ and $B_i$, which connote that a cow has to travel from station $A_i$ to station $B_i$ (by traversing over one or more paths over some route). The cows want to take a path the minimizes the height of the tallest hurdle they jump over when traveling from $A_i$ to $B_i$ . Your job is to write a program that determines the path whose tallest hurdle is smallest and report that height.


Farmer John 想让她的奶牛准备郡级跳跃比赛，Bessie 和她的伙伴们正在练习跨栏。她们很累，所以她们想消耗最少的能量来跨栏。 显然，对于一头奶牛跳过几个矮栏是很容易的，但是高栏却很难。于是，奶牛们总是关心路径上最高的栏的高度。 

奶牛的训练场中有 $N$ 个站台，分别标记为 $1,\dots,N$。所有站台之间有 $M$ 条单向路径，第 $i$ 条路经是从站台 $S_i$ 开始，到站台 $E_i$，其中最高的栏的高度为 $H_i$。无论如何跑，奶牛们都要跨栏。 

奶牛们有 $T$ 个训练任务要完成。第 $i$ 个任务包含两个数字 $A_i$ 和 $B_i$，表示奶牛必须从站台 $A_i$ 跑到站台 $B_i$，可以路过别的站台。奶牛们想找一条路径从站台 $A_i$ 到站台 $B_i$，使路径上最高的栏的高度最小。 你的任务就是写一个程序，计算出路径上最高的栏的高度的最小值。


## 说明/提示

对于 $100\%$ 的数据，$1 \le N \le 300$，$1 \le M \le 2.5 \times 10^4$，$1 \le H_i \le 1 \times 10^6$，$1 \le T \le 4 \times 10^4$，$1 \le A_i,B_i \le N$。

感谢 @gaozhiyong @_Cppsteve_ 提供翻译


## 样例 #1

### 输入

```
5 6 3
1 2 12
3 2 8
1 3 5
2 5 3
3 4 4
2 4 8
3 4
1 2
5 1
```

### 输出

```
4
8
-1
```

# AI分析结果



### 综合分析与结论
本题要求求解两点间路径上的最大栏高最小值，核心在于将问题转化为图的松弛问题。由于数据规模中N=300，O(n³)的Floyd算法成为主流解法，而部分SPFA解法通过查询缓存优化也能通过。最优解法为Floyd的变形，通过状态转移方程`d[i][j] = min(d[i][j], max(d[i][k], d[k][j]))`实现路径最大高度的动态松弛。

---

### 精选题解（评分≥4星）

#### 1. 沉辰（4星）
**关键亮点**：  
- 正确应用Floyd算法变形，状态转移方程简洁清晰。  
- 代码结构紧凑，初始化与输入处理合理。  
**核心代码**：  
```cpp
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            d[i][j] = min(max(d[i][k], d[k][j]), d[i][j]);
```

#### 2. thoq（4星）
**关键亮点**：  
- 采用SPFA算法，通过缓存已处理的起点避免重复计算。  
- 针对多查询场景优化，减少冗余计算。  
**个人心得**：  
> "40000次查询最多涉及300个不同起点，缓存预处理避免重复SPFA是优化的关键。"  
**核心代码**：  
```cpp
void spfa(int s) {
    memset(d[s], inf, sizeof(d[s]));
    queue<int> q;
    q.push(s);
    d[s][s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (Edge e : adj[u]) {
            if (d[s][e.to] > max(d[s][u], e.w)) {
                d[s][e.to] = max(d[s][u], e.w);
                q.push(e.to);
            }
        }
    }
}
```

#### 3. Starlight237（5星）
**关键亮点**：  
- 在Floyd循环中增加短路优化，跳过无效中间节点。  
- 使用位掩码优化IO，显著提升代码运行效率。  
**核心代码**：  
```cpp
for (reg int k=1; k<=n; ++k)
    for (reg int i=1; i<=n; ++i)
        if (f[i][k] != 0x3f3f3f3f) // 跳过无效中间点
            for (reg int j=1; j<=n; ++j)
                f[i][j] = min(f[i][j], max(f[i][k], f[k][j]));
```

---

### 关键思路与技巧
1. **Floyd变形**：将传统最短路中的加法替换为取最大值，松弛目标为最小化路径最大高度。
2. **无效中间点跳过**：在Floyd的三重循环中，若`d[i][k]`无效（无穷大），直接跳过后续计算。
3. **查询缓存优化**：对SPFA等单源算法，记录每个起点的计算结果，避免重复处理相同起点。

---

### 同类题目推荐
1. **P2912 [USACO08OCT]Pasture Walking G**：Floyd求任意两点间路径最大边权最小值。
2. **P1119 灾后重建**：动态Floyd应用，结合时间约束更新中间节点。
3. **P2149 [SDOI2009]Elaxia的路线**：多条件约束下的最短路变形，考察复合松弛逻辑。

---
处理用时：60.15秒