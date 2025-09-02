# 题目信息

# Lorenzo Von Matterhorn

## 题目描述

Barney lives in NYC. NYC has infinite number of intersections numbered with positive integers starting from 1. There exists a bidirectional road between intersections $ i $ and $ 2i $ and another road between $ i $ and $ 2i+1 $ for every positive integer $ i $ . You can clearly see that there exists a unique shortest path between any two intersections.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696A/61a3ff7e8c29b0fc174f08897786128f1c443049.png)Initially anyone can pass any road for free. But since SlapsGiving is ahead of us, there will $ q $ consecutive events happen soon. There are two types of events:

1\. Government makes a new rule. A rule can be denoted by integers $ v $ , $ u $ and $ w $ . As the result of this action, the passing fee of all roads on the shortest path from $ u $ to $ v $ increases by $ w $ dollars.

2\. Barney starts moving from some intersection $ v $ and goes to intersection $ u $ where there's a girl he wants to cuddle (using his fake name Lorenzo Von Matterhorn). He always uses the shortest path (visiting minimum number of intersections or roads) between two intersections.

Government needs your calculations. For each time Barney goes to cuddle a girl, you need to tell the government how much money he should pay (sum of passing fee of all roads he passes).

## 说明/提示

In the example testcase:

Here are the intersections used:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696A/fd9f1cc0cd9bb95a97335a4462bfd7b1491ad15a.png)1. Intersections on the path are $ 3 $ , $ 1 $ , $ 2 $ and $ 4 $ .
2. Intersections on the path are $ 4 $ , $ 2 $ and $ 1 $ .
3. Intersections on the path are only $ 3 $ and $ 6 $ .
4. Intersections on the path are $ 4 $ , $ 2 $ , $ 1 $ and $ 3 $ . Passing fee of roads on the path are $ 32 $ , $ 32 $ and $ 30 $ in order. So answer equals to $ 32+32+30=94 $ .
5. Intersections on the path are $ 6 $ , $ 3 $ and $ 1 $ .
6. Intersections on the path are $ 3 $ and $ 7 $ . Passing fee of the road between them is $ 0 $ .
7. Intersections on the path are $ 2 $ and $ 4 $ . Passing fee of the road between them is $ 32 $ (increased by $ 30 $ in the first event and by $ 2 $ in the second).

## 样例 #1

### 输入

```
7
1 3 4 30
1 4 1 2
1 3 6 8
2 4 3
1 6 1 40
2 3 7
2 2 4
```

### 输出

```
94
0
32
```

# AI分析结果

### 题目内容
# 洛伦佐·冯·马特洪峰

## 题目描述
巴尼住在纽约市。纽约市有无数个十字路口，从1开始用正整数编号。对于每个正整数 $i$，在十字路口 $i$ 与 $2i$ 之间，以及 $i$ 与 $2i + 1$ 之间都存在一条双向道路。显然，任意两个十字路口之间都存在唯一的最短路径。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696A/61a3ff7e8c29b0fc174f08897786128f1c443049.png)
最初，任何人都可以免费通过任何道路。但由于“耳光节”即将来临，很快会发生 $q$ 个连续事件。事件有两种类型：
1. 政府制定一项新规则。一条规则可以用整数 $v$、$u$ 和 $w$ 表示。此操作的结果是，从 $u$ 到 $v$ 的最短路径上所有道路的通行费增加 $w$ 美元。
2. 巴尼从某个十字路口 $v$ 出发，前往十字路口 $u$，那里有一个他想用假名洛伦佐·冯·马特洪峰去拥抱的女孩。他总是使用两个十字路口之间的最短路径（经过最少的十字路口或道路）。

政府需要你的计算结果。每次巴尼去拥抱女孩时，你需要告诉政府他应该支付多少钱（他经过的所有道路的通行费总和）。

## 说明/提示
在示例测试用例中：
以下是所使用的十字路口：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696A/fd9f1cc0cd9bb95a97335a4462bfd7b1491ad15a.png)
1. 路径上的十字路口是 $3$、$1$、$2$ 和 $4$。
2. 路径上的十字路口是 $4$、$2$ 和 $1$。
3. 路径上的十字路口只有 $3$ 和 $6$。
4. 路径上的十字路口是 $4$、$2$、$1$ 和 $3$。路径上道路的通行费依次是 $32$、$32$ 和 $30$。所以答案等于 $32 + 32 + 30 = 94$。
5. 路径上的十字路口是 $6$、$3$ 和 $1$。
6. 路径上的十字路口是 $3$ 和 $7$。它们之间道路的通行费是 $0$。
7. 路径上的十字路口是 $2$ 和 $4$。它们之间道路的通行费是 $32$（在第一个事件中增加了 $30$，在第二个事件中增加了 $2$）。

## 样例 #1
### 输入
```
7
1 3 4 30
1 4 1 2
1 3 6 8
2 4 3
1 6 1 40
2 3 7
2 2 4
```
### 输出
```
94
0
32
```

### 算法分类
模拟（基于满二叉树的性质对树上路径操作进行模拟）

### 综合分析与结论
所有题解均基于满二叉树的性质，利用树中节点与其父亲节点的关系（编号为 $i$ 的节点父亲为 $\lfloor\frac{i}{2}\rfloor$）来处理路径操作。由于树节点无限且 $u, v$ 数值大，都选择用 `map` 或 `unordered_map` 存储边权。对于路径加和路径求和操作，均采用让节点向上跳到公共祖先的方式，时间复杂度为 $O(\log n)$。不同之处在于判断节点是否在同一层以及向上跳的具体实现细节。

### 所选的题解
#### 作者：_xxxxx_ (5星)
- **关键亮点**：思路清晰，代码简洁明了。明确指出利用满二叉树性质，直接暴力向上跳，用 `map` 存储每个点及其父亲之间的边，操作直观。
- **重点代码 - 核心实现思想**：`add_way` 函数实现路径加操作，`query_way` 函数实现路径求和操作，每次选两个点中更深（更大）的点向上跳并修改或累加边权。
```cpp
void add_way(int u, int v, int w)
{
    while(u!= v)
    {
        if(u < v) swap(u, v);
        mp[u / 2][u] += w;
        mp[u][u / 2] += w;
        u /= 2;
    }
}
int query_way(int u, int v)
{
    int ans = 0;
    while(u!= v)
    {
        if(u < v) swap(u, v);
        ans += mp[u / 2][u];
        u /= 2;
    }
    return ans;
}
```
#### 作者：Cloud_Umbrella (4星)
- **关键亮点**：利用位运算判断节点是否在同一层，优化了向上跳的逻辑，代码较为简洁。
- **重点代码 - 核心实现思想**：在路径加和路径求和操作中，通过 `(u^v)>(u&v)` 判断 $u$ 和 $v$ 是否在同一层，然后分别或同时向上跳并修改或累加边权。
```cpp
if(opt==1){
    scanf("%lld",&w);
    for(;(u^v)>(u&v);v>>=1) mp[v]+=w;
    for(;u!=v;u>>=1,v>>=1) mp[u]+=w,mp[v]+=w;
}
else{
    long long ans=0;
    for(;(u^v)>(u&v);v>>=1) ans+=mp[v];
    for(;u!=v;u>>=1,v>>=1) ans+=mp[u],ans+=mp[v];
    printf("%lld\n",ans);
}
```
#### 作者：codeLJH114514 (4星)
- **关键亮点**：先求出节点深度和最近公共祖先（LCA），逻辑清晰，代码模块化程度高。
- **重点代码 - 核心实现思想**：`Depth` 函数求节点深度，`LCA` 函数求最近公共祖先，在路径加和路径求和操作中，通过与最近公共祖先比较，让节点向上跳并修改或累加边权。
```cpp
int Depth(int u) {
    int len = 0;
    while (u!= 1) {
        u >>= 1;
        len += 1;
    } return len;
}
int LCA(int x, int y) {
    if (Depth(x) > Depth(y)) std::swap(x, y);
    while (Depth(x) < Depth(y)) y >>= 1;
    if (x == y) return x;
    while (x!= y) {
        x >>= 1;
        y >>= 1;
    }
    return x;
}
if (opr == 1) {
    std::cin >> w;
    while (u!= lca) {
        W[u] += w;
        u >>= 1;
    }
    while (v!= lca) {
        W[v] += w;
        v >>= 1;
    }
} else {
    int ans = 0;
    while (u!= lca) {
        ans += W[u];
        u >>= 1;
    }
    while (v!= lca) {
        ans += W[v];
        v >>= 1;
    }
    std::cout << ans << std::endl;
}
```

### 最优关键思路或技巧
利用满二叉树节点编号与父子关系的性质，通过向上跳的方式处理路径操作。在实现上，可采用位运算优化判断节点是否在同一层，或者通过求深度和最近公共祖先使逻辑更清晰。同时，使用 `map` 或 `unordered_map` 存储边权以适应无限节点和大数据范围。

### 可拓展思路
此类题目属于树上路径操作问题，类似套路有：利用树的特殊结构（如完全二叉树、平衡二叉树等）简化路径查找；对于大规模数据，考虑更高效的数据结构优化存储和查询，如线段树优化区间操作。

### 洛谷相似题目
1. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
2. [P1852 跳跳棋](https://www.luogu.com.cn/problem/P1852)
3. [P2579 [ZJOI2005] 沼泽鳄鱼](https://www.luogu.com.cn/problem/P2579)

### 个人心得摘录与总结
多个题解提到“不开 `long long` 见祖宗”，强调在处理大数据范围时数据类型选择的重要性，避免因数据类型不当导致错误。同时部分题解在调试过程中尝试不同思路，如最初写多个 `dfs` 未通过样例后更换思路，体现了解题过程中灵活调整方法的重要性。 

---
处理用时：72.12秒