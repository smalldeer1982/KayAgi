# 题目信息

# Party

## 题目描述

A club plans to hold a party and will invite some of its $ n $ members. The $ n $ members are identified by the numbers $ 1, 2, \dots, n $ . If member $ i $ is not invited, the party will gain an unhappiness value of $ a_i $ .

There are $ m $ pairs of friends among the $ n $ members. As per tradition, if both people from a friend pair are invited, they will share a cake at the party. The total number of cakes eaten will be equal to the number of pairs of friends such that both members have been invited.

However, the club's oven can only cook two cakes at a time. So, the club demands that the total number of cakes eaten is an even number.

What is the minimum possible total unhappiness value of the party, respecting the constraint that the total number of cakes eaten is even?

## 说明/提示

In the first test case, all members can be invited. So the unhappiness value is $ 0 $ .

In the second test case, the following options are possible:

- invite $ 1 $ and $ 2 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 3 $ );
- invite $ 2 $ and $ 3 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 2 $ );
- invite only $ 1 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 4 $ );
- invite only $ 2 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 5 $ );
- invite only $ 3 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 3 $ );
- invite nobody ( $ 0 $ cakes eaten, unhappiness value equal to $ 6 $ ).

 The minimum unhappiness value is achieved by inviting $ 2 $ and $ 3 $ .In the third test case, inviting members $ 3,4,5 $ generates a valid party with the minimum possible unhappiness value.

## 样例 #1

### 输入

```
4
1 0
1
3 1
2 1 3
1 3
5 5
1 2 3 4 5
1 2
1 3
1 4
1 5
2 3
5 5
1 1 1 1 1
1 2
2 3
3 4
4 5
5 1```

### 输出

```
0
2
3
2```

# AI分析结果

### 题目中文重写
# 派对

## 题目描述
一个俱乐部计划举办一场派对，并将邀请其 $n$ 名成员中的一部分。这 $n$ 名成员用数字 $1, 2, \dots, n$ 来标识。如果成员 $i$ 未被邀请，派对将产生一个不开心值 $a_i$。

在这 $n$ 名成员中有 $m$ 对朋友关系。按照传统，如果一对朋友都被邀请，他们将在派对上共享一块蛋糕。吃掉的蛋糕总数将等于被邀请的朋友对数。

然而，俱乐部的烤箱一次只能烤两块蛋糕。因此，俱乐部要求吃掉的蛋糕总数为偶数。

在满足吃掉的蛋糕总数为偶数这一约束条件下，派对的最小可能总不开心值是多少？

## 说明/提示
在第一个测试用例中，可以邀请所有成员。因此不开心值为 $0$。

在第二个测试用例中，有以下几种可能的选择：
- 邀请 $1$ 和 $2$（吃掉 $0$ 块蛋糕，不开心值等于 $3$）；
- 邀请 $2$ 和 $3$（吃掉 $0$ 块蛋糕，不开心值等于 $2$）；
- 只邀请 $1$（吃掉 $0$ 块蛋糕，不开心值等于 $4$）；
- 只邀请 $2$（吃掉 $0$ 块蛋糕，不开心值等于 $5$）；
- 只邀请 $3$（吃掉 $0$ 块蛋糕，不开心值等于 $3$）；
- 不邀请任何人（吃掉 $0$ 块蛋糕，不开心值等于 $6$）。

通过邀请 $2$ 和 $3$ 可以达到最小不开心值。在第三个测试用例中，邀请成员 $3$、$4$、$5$ 可以举办一个有效的派对，并达到最小可能的不开心值。

## 样例 #1
### 输入
```
4
1 0
1
3 1
2 1 3
1 3
5 5
1 2 3 4 5
1 2
1 3
1 4
1 5
2 3
5 5
1 1 1 1 1
1 2
2 3
3 4
4 5
5 1
```
### 输出
```
0
2
3
2
```

### 综合分析与结论
这些题解的核心思路都是将问题转化为图论问题，通过分类讨论边数的奇偶性来求解最小不开心值。当边数 $m$ 为偶数时，直接邀请所有成员，不开心值为 $0$；当 $m$ 为奇数时，考虑删除一个或两个点来使剩余边数为偶数，通过枚举点和边来找到最小的点权和。

|作者|思路|算法要点|解决难点|评分|
|----|----|----|----|----|
|Hovery|根据边数奇偶分类讨论，奇数时枚举度为奇数的点和相邻度和为偶数的点|记录点的度，枚举点和边|分析删除点对边数的影响|4星|
|IGJHL|将问题转化为图论问题，分类讨论删除点的情况|记录点的度数，枚举点和边|分析不同删除情况的优劣|4星|
|zhicheng|正难则反，考虑破坏奇数个无序对|记录包含元素的无序对数量，枚举无序对|分析删除元素对无序对数量的影响|3星|
|CheemsaDoge|分类讨论边数奇偶，奇数时考虑删除单点和有公共边的双点|记录点的边数，枚举边|判断删除双点的条件|3星|
|Bai_Kking|通过穷举、贪心和分类讨论得出正解|枚举点和边，判断度数和边数关系|分析删除偶数点的情况|3星|
|IYSY2009I|分类讨论不邀请一个和两个人的情况|枚举点和边，判断度数和边数关系|证明不邀请大于等于3个人不是最优解|3星|
|codemap|将问题转化为找最大子图，证明最多去掉两个人|枚举奇节点和偶节点连边的偶节点|证明最多去掉两个人的结论|3星|
|Shimotsuki|将成员关系看成无向图，根据度数情况删除点|枚举点和相邻点|考虑不同度数点的删除情况|3星|
|13802919466djh|分类讨论边数奇偶，奇数时枚举点和边|记录点的度数，枚举点和边|分析删除两个点的条件|3星|
|shyr|根据边数奇偶分类，利用子图连边公式得出推论并分类讨论|记录点的度数和相邻点最小点权，枚举点|证明不选两个及以上互不连边的点不优秀|3星|

### 所选题解
- **Hovery（4星）**
    - 关键亮点：思路清晰，代码简洁，详细分析了删除点对边数的影响。
    - 核心代码：
```cpp
void solve()
{
    cin >> n >> m;
    for (int i = 1;i <= n;i++)
    {
        cin >> a[i];
        G[i].clear();
    }
    for (int i = 1;i <= m;i++)
    {
        cin >> x[i] >> y[i];
        G[x[i]].pb(y[i]);
        G[y[i]].pb(x[i]);
    }
    if (m % 2 == 0)
    {
        cout << "0\n";
        return;
    }
    ans = 1000000000000;
    for (int i = 1;i <= n;i++)
        if (G[i].size() % 2 == 1)
            ans = min(ans, a[i]);
    for (int i = 1;i <= m;i++)
    {
        if ((G[x[i]].size() + G[y[i]].size()) % 2 == 0)
        {
            ans = min(ans, a[x[i]] + a[y[i]]);
        }
    }
    cout << ans << endl;
}
```
核心实现思想：先读取输入，构建图。若边数为偶数，直接输出 $0$。否则，枚举度为奇数的点和相邻度和为偶数的点，取最小点权和输出。

- **IGJHL（4星）**
    - 关键亮点：将问题转化为图论问题，详细分类讨论删除点的情况，代码可读性高。
    - 核心代码：
```cpp
while (t --) {
    cin >> n >> m;
    ans = INT_MAX;
    for (int i = 1; i <= n; ++ i)
        cin >> a[i], d[i] = 0;
    for (int i = 1; i <= m; ++ i) {
        cin >> u[i] >> v[i];
        ++ d[u[i]], ++ d[v[i]];
    }
    if (m % 2 == 0) {
        cout << "0\n";
        continue;
    }
    for (int i = 1; i <= n; ++ i)
        if (d[i] % 2 == 1)
            ans = min(ans, a[i]);
    for (int i = 1; i <= m; ++ i)
        if ((d[u[i]] + d[v[i]]) % 2 == 0)
            ans = min(ans, a[u[i]] + a[v[i]]);
    cout << ans << "\n";
}
```
核心实现思想：读取输入，记录点的度数。若边数为偶数，输出 $0$。否则，枚举度为奇数的点和相邻度和为偶数的点，取最小点权和输出。

### 最优关键思路或技巧
- **分类讨论**：根据边数的奇偶性进行分类讨论，简化问题。
- **贪心思想**：在删除点时，优先选择点权小的点。
- **图论转化**：将成员关系转化为图论问题，利用图的性质进行分析。

### 拓展思路
同类型题可以考虑增加更多的约束条件，如限制删除点的数量、增加边的权重等。类似算法套路可以应用于其他图论问题，如最小生成树、最短路径等。

### 推荐题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)：拓扑排序相关问题。
- [P1346 电车](https://www.luogu.com.cn/problem/P1346)：图的最短路问题。
- [P2820 局域网](https://www.luogu.com.cn/problem/P2820)：最小生成树问题。

### 个人心得摘录与总结
- **zhicheng**：“比赛的时候看了10min才把题看懂，我太弱了”，总结：读题很重要，要仔细理解题意。
- **Bai_Kking**：尝试穷举法但复杂度高，通过反例发现只删奇数点不是最优解，引出分类讨论的正解。总结：遇到复杂问题可以先尝试简单方法，通过反例不断优化思路。 

---
处理用时：49.80秒