# 题目信息

# Bakery

## 题目描述

Masha wants to open her own bakery and bake muffins in one of the $ n $ cities numbered from $ 1 $ to $ n $ . There are $ m $ bidirectional roads, each of whose connects some pair of cities.

To bake muffins in her bakery, Masha needs to establish flour supply from some storage. There are only $ k $ storages, located in different cities numbered $ a_{1},a_{2},...,a_{k} $ .

Unforunately the law of the country Masha lives in prohibits opening bakery in any of the cities which has storage located in it. She can open it only in one of another $ n-k $ cities, and, of course, flour delivery should be paid — for every kilometer of path between storage and bakery Masha should pay $ 1 $ ruble.

Formally, Masha will pay $ x $ roubles, if she will open the bakery in some city $ b $ ( $ a_{i}≠b $ for every $ 1<=i<=k $ ) and choose a storage in some city $ s $ ( $ s=a_{j} $ for some $ 1<=j<=k $ ) and $ b $ and $ s $ are connected by some path of roads of summary length $ x $ (if there are more than one path, Masha is able to choose which of them should be used).

Masha is very thrifty and rational. She is interested in a city, where she can open her bakery (and choose one of $ k $ storages and one of the paths between city with bakery and city with storage) and pay minimum possible amount of rubles for flour delivery. Please help Masha find this amount.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF707B/5363dd57fa93616f4ccd4cae1a9732744eeb0a9c.png)Image illustrates the first sample case. Cities with storage located in and the road representing the answer are darkened.

## 样例 #1

### 输入

```
5 4 2
1 2 5
1 2 3
2 3 4
1 4 10
1 5
```

### 输出

```
3```

## 样例 #2

### 输入

```
3 1 1
1 2 3
3
```

### 输出

```
-1```

# AI分析结果



# 中文题目重写

## 题目描述

玛莎想在自己的面包店中烘焙松饼，她计划在编号为1到n的n个城市中选择一个开设面包店。城市间有m条双向道路连接。

为了供应面粉，玛莎需要从某个仓库运输面粉。共有k个仓库，分别位于不同的城市a₁,a₂,...,a₋k。

国家法律规定，不能在设有仓库的城市开设面包店。玛莎只能在剩下的n-k个城市中选择开设地点，且面粉运输费用与路径长度（公里数）成正比。

形式化地说，若玛莎在非仓库城市b开设面包店，并选择仓库城市s进行供应，她需要支付等于两城市间最短路径长度的费用（当存在多条路径时，玛莎可以选择最短的那条）。

请帮助玛莎找到最低可能的面粉运输费用。

## 输入输出样例

### 样例1
输入：
5 4 2
1 2 5
1 2 3
2 3 4
1 4 10
1 5

输出：
3

### 样例2
输入：
3 1 1
1 2 3
3

输出：
-1

## 说明/提示
样例图示展示了第一个测试案例，深色标记的为仓库城市和答案涉及的路径。

---

**算法分类**：图论 / 最短路

---

## 题解综合分析与结论

### 核心思路
所有题解均基于以下关键观察：
1. 最优解必然存在于某条直接连接仓库与非仓库的边
2. 无需计算全局最短路，只需遍历所有边检查端点类型即可

### 正确性证明
假设存在非仓库城市b到仓库s的最短路径P，则P中必存在一条边u-v满足：
- u为仓库，v为非仓库（或相反）
- 该边权值≤路径P总长（因边权非负）

因此遍历所有边即可覆盖所有可能的最优解。

---

## 优质题解推荐

### 1. SqrtSecond（五星）
**关键亮点**：
- 提供严谨的数学证明
- 代码简洁高效（O(m)时间复杂度）
- 包含输入优化处理

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=2e9;
int n,m,k,ans=inf;
struct edge { int u,v,w; } e[200100];
bool b[100100]; // 仓库标记

int main() {
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    while(k--) { int x; scanf("%d",&x); b[x]=true; }
    
    for(int i=1;i<=m;i++) {
        if(b[e[i].u]^b[e[i].v]) // 两端类型不同
            ans = min(ans, e[i].w);
    }
    printf("%d", ans==inf ? -1 : ans);
}
```

### 2. Aisaka_Taiga（四星）
**关键亮点**：
- 最简代码实现
- 使用异或运算优化判断逻辑
- 适合快速理解核心思路

**代码片段**：
```cpp
int ans=INF;
for(int i=1;i<=m;i++)
    if(t[u[i]]^t[v[i]]) 
        ans=min(ans,w[i]);
```

### 3. Keroshi（四星）
**关键亮点**：
- 结构体数组存储边信息
- 包含边界条件处理
- 使用位运算优化判断

---

## 关键思路总结
1. **边枚举法**：直接遍历所有边，检查端点类型差异
2. **标记优化**：使用布尔数组快速判断仓库节点
3. **异或运算**：高效判断端点类型是否不同

---

## 拓展思考
类似问题可考虑：
- 边权有特殊性质时的最短路优化
- 二分答案验证型问题（如CF372C）
- 多源最短路的优化问题

---

## 推荐练习题
1. P1339 [USACO09OCT]Heat Wave G（最短路基础）
2. P1354 房间最短路问题（几何+图论）
3. P4568 [JLOI2011]飞行路线（分层图最短路）

---

## 个人心得摘录
SqrtSecond：
> "由于边权为正，可以证明最优方案在走的过程中至多只走一条边。通过分析路径结构，中间必然存在更优的直连边"

该见解揭示了图论问题中边权特性对算法选择的重要影响。

---
处理用时：150.34秒