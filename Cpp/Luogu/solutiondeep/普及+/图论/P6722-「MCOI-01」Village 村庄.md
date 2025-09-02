# 题目信息

# 「MCOI-01」Village 村庄

## 题目背景

今天，珂爱善良的0x3喵酱骑着一匹小马来到了一个村庄。

“诶，这个村庄的布局 ……”   
“好像之前我玩 Ciste 的地方啊 qwq”

0x3喵酱有一个地图，地图有着这个村庄的信息。

然后0x3喵酱要通过这张地图来判断 Ciste 有解无解啦 ~

注：Ciste 是《请问您今天要来点兔子吗》中的一种藏宝图游戏

## 题目描述

村庄被简化为一个 $n$ 个节点（编号为 $1$ 到 $n$）和 $n-1$ 条边构成的无向连通图。

0x3喵酱认为这个无向图里的信息跟满足以下条件的新图有关：

- 新图的点集与原图相同
- 在新图中 $u,v$ 之间有无向边 是 在原图中 $dis(u,v) \ge k$ 的**充分必要条件** （$k$ 为给定常量，$dis(u,v)$ 表示编号为 $u$ 的点到编号为 $v$ 的点最短路的长度）

0x3喵酱还认为这个"新图"如果为二分图，则 Ciste "有解"，如果"新图"不是二分图这个 Ciste "无解"。（如果您不知道二分图请翻到提示）

那么0x3喵酱想请您判断一下这个 Ciste 是否"有解"。

## 说明/提示

#### 样例解析

对于样例中的 **第一组** 数据：

原图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9f9zh4b2.png)
新图：

![](https://cdn.luogu.com.cn/upload/image_hosting/dg4es91e.png)

新图不为二分图，故输出 `Baka Chino`。

对于 **第三组** 数据：

原图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mku4v6uo.png)

新图：

![](https://cdn.luogu.com.cn/upload/image_hosting/15o3x3zz.png)

新图为二分图，故输出 `Yes`。

#### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 1（16 pts）$\ $ ：$n \le 10$。
- Subtask 2（24 pts）$\ $ ：$n \le 100$。
- Subtask 3（8 pts）$\ $ ：$n \le 1000$。
- Subtask 4（28 pts）：图退化成一条链。
- Subtask 5（24 pts）：无特殊限制。

对于 $100\%$ 的数据，$n \le 10^5$，$T \le 10$，$v \le 1000$，$k \le 1000000$。

本题数据使用 [CYaRon](https://www.luogu.org/discuss/show?postid=11410) 生成。

#### 提示


**二分图** 又称作二部图，是图论中的一种特殊模型。设 $G=(V,E)$ 是一个无向图，如果顶点 $V$ 可分割为两个互不相交的子集 $(A,B)$，并且图中的每条边 $(i,j)$ 所关联的两个顶点 $i$ 和 $j$ 分别属于这两个不同的顶点集 $(i \in A,j \in B)$，则称图 $G$ 为一个二分图。（摘自[百度百科](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E5%9B%BE/9089095?fr=aladdin)）

#### 说明

Minecraft OI Round 1 A

- Idea：0x3喵酱
- Solution/Std：0x3喵酱
- Data：0x3喵酱
- Tester：tarjin

## 样例 #1

### 输入

```
5
5 2
1 2 1
2 3 1
3 4 1
4 5 1
5 3
1 2 1
2 3 1
3 4 1
4 5 1
5 8
1 3 3
1 2 1
2 4 6
2 5 2
5 2
1 3 3
1 2 1
2 4 6
2 5 2
7 4
1 2 3
1 3 3
2 5 3
2 6 3
3 7 3
2 4 2```

### 输出

```
Baka Chino
Yes
Yes
Baka Chino
Baka Chino```

# AI分析结果

### 综合分析与结论
这些题解围绕判断新图是否为二分图展开，核心在于判断新图中是否存在奇环。不同题解采用了不同的方法：
- **暴力解法**：通过弗洛伊德算法或DFS求全源最短路，建立新图后用二分图染色或并查集判断是否为二分图，适用于小数据规模。
- **换根DP**：记录每个点子树离它最远的三个点的距离和父亲最远距离，通过两次DFS判断是否存在不满足二分图条件的情况。
- **树的直径性质**：证明若新图存在奇环，则一定存在三元环，且存在包含直径两个端点的三元环，通过求树的直径并判断是否存在一点到直径两端距离不小于k来判断新图是否为二分图。

### 所选题解
- **作者：一只书虫仔（5星）**
    - **关键亮点**：思路清晰，对每个测试点的解法进行了详细分析，包括算法选择和证明过程，代码简洁易懂。
    - **核心代码**：
```cpp
void dfs(int i, int fa, int* dis) {
    int p;
    for (p = V[i].eh; p; p = E[p].next) {
        if (E[p].to == fa) continue;
        dis[E[p].to] = dis[i] + E[p].v;
        dfs(E[p].to, i, dis);
    }
}

int main() {
    int n, i, T, x, y, v, k, flag;
    scanf("%d", &T);
    while (T--) {
        // 初始化
        memset(V, 0, sizeof(V));
        memset(E, 0, sizeof(E));
        tot = 0; flag = 1;
        scanf("%d%d", &n, &k);
        for (i = 0; i < n - 1; i++) {
            scanf("%d%d%d", &x, &y, &v);
            add_edge(x, y, v);
            add_edge(y, x, v);
        }
        dis1[1] = 0;
        dfs(1, 0, dis1); x = 1;
        for (i = 2; i <= n; i++) {
            if (dis1[i] > dis1[x]) x = i;
        }
        dis1[x] = 0;
        dfs(x, 0, dis1); y = x;
        for (i = 1; i <= n; i++) {
            if (dis1[i] > dis1[y]) y = i;
        }
        dis2[y] = 0;
        dfs(y, 0, dis2);
        for (i = 1; i <= n; i++) {
            if (dis1[i] >= k && dis2[i] >= k) flag = 0;
        }
        if (flag) printf("Yes\n");
        else printf("Baka Chino\n");
    }
    return 0;
}
```
    - **核心思想**：通过两次DFS求出树的直径的两个端点，再分别以这两个端点为起点进行DFS求出到各点的距离，最后判断是否存在一点到直径两端距离不小于k。

- **作者：青鸟_Blue_Bird（4星）**
    - **关键亮点**：对官方题解的数学证明进行了详细解读，通过画图和数学归纳法帮助理解，代码规范，有详细注释。
    - **核心代码**：
```cpp
void dfs(int now, int father, int* dis) {
    if (dis[now] > maxn) {
        maxn = dis[now];
        cur = now;
    }
    for (int i = f[now]; i; i = t[i].next) {
        if (v!= father) {
            dis[v] = dis[now] + t[i].w;
            dfs(v, now, dis);
        }
    }
}

inline void search(int x, int& y, int* dis) {
    maxn = -666;
    cur = 0;
    dis[x] = 0;
    dfs(x, 0, dis);
    y = cur;
}

int main() {
    int T;
    read(T);
    while (T--) {
        clean();
        int n, k;
        read(n), read(k);
        s1 = 0, s2 = 0;
        for (int i = 1; i < n; i++) {
            int x, y, w;
            read(x), read(y), read(w);
            add(x, y, w);
        }
        search(1, s1, dis);
        search(s1, s2, dis1);
        int temp = 0;
        search(s2, temp, dis2);
        bool flag = 0;
        for (int i = 1; i <= n; i++)
            if (dis1[i] >= k && dis2[i] >= k) {
                flag = 1;
                break;
            }
        if (flag) puts("Baka Chino");
        else puts("Yes");
    }
    return 0;
}
```
    - **核心思想**：通过封装的`search`函数和`dfs`函数求出树的直径的两个端点及到各点的距离，最后判断是否存在一点到直径两端距离不小于k。

### 最优关键思路或技巧
利用树的直径性质，将判断新图是否存在奇环的问题转化为判断是否存在一点到直径两端距离不小于k的问题，将时间复杂度优化到$O(n)$。

### 可拓展之处
同类型题可考虑在不同图结构（如带权图、有向图）中判断二分图，或结合其他图算法（如最小生成树、最短路径算法）进行求解。类似算法套路包括利用图的性质（如连通性、对称性）简化问题，通过数学证明找到关键判断条件。

### 推荐题目
1. [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：判断二分图并求最小染色点数。
2. [P2825 [HEOI2016/TJOI2016]游戏](https://www.luogu.com.cn/problem/P2825)：涉及二分图匹配和建图技巧。
3. [P3386 【模板】二分图最大匹配](https://www.luogu.com.cn/problem/P3386)：学习二分图最大匹配算法。

### 个人心得
- **青鸟_Blue_Bird**：强调数学归纳法部分要画图结合原图手摸，帮助理解证明过程。这提示我们在处理复杂的数学证明和逻辑推理时，通过画图和手动模拟可以更好地把握问题的本质。 

---
处理用时：41.43秒