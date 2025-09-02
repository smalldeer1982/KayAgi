# 题目信息

# Social Network

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609D/bd782248ee184d971343d4489aa3f05723b81f9f.png)William arrived at a conference dedicated to cryptocurrencies. Networking, meeting new people, and using friends' connections are essential to stay up to date with the latest news from the world of cryptocurrencies.

The conference has $ n $ participants, who are initially unfamiliar with each other. William can introduce any two people, $ a $ and $ b $ , who were not familiar before, to each other.

William has $ d $ conditions, $ i $ 'th of which requires person $ x_i $ to have a connection to person $ y_i $ . Formally, two people $ x $ and $ y $ have a connection if there is such a chain $ p_1=x, p_2, p_3, \dots, p_k=y $ for which for all $ i $ from $ 1 $ to $ k - 1 $ it's true that two people with numbers $ p_i $ and $ p_{i + 1} $ know each other.

For every $ i $ ( $ 1 \le i \le d $ ) William wants you to calculate the maximal number of acquaintances one person can have, assuming that William satisfied all conditions from $ 1 $ and up to and including $ i $ and performed exactly $ i $ introductions. The conditions are being checked after William performed $ i $ introductions. The answer for each $ i $ must be calculated independently. It means that when you compute an answer for $ i $ , you should assume that no two people have been introduced to each other yet.

## 说明/提示

The explanation for the first test case:

In this explanation, the circles and the numbers in them denote a person with the corresponding number. The line denotes that William introduced two connected people. The person marked with red has the most acquaintances. These are not the only correct ways to introduce people.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609D/a4c52dc40d0c621cc37cb8aa412551d28349b4ab.png)

## 样例 #1

### 输入

```
7 6
1 2
3 4
2 4
7 6
6 5
1 7```

### 输出

```
1
1
3
3
3
6```

## 样例 #2

### 输入

```
10 8
1 2
2 3
3 4
1 4
6 7
8 9
8 10
1 4```

### 输出

```
1
2
3
4
5
5
6
8```

# AI分析结果

### 题目翻译
#### 社交网络

#### 题目描述
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609D/bd782248ee184d971343d4489aa3f05723b81f9f.png)威廉参加了一个关于加密货币的会议。社交、结识新朋友以及利用朋友的人脉对于了解加密货币世界的最新消息至关重要。

会议有 $n$ 名参与者，他们最初彼此不认识。威廉可以介绍任意两个之前不认识的人 $a$ 和 $b$ 互相认识。

威廉有 $d$ 个条件，第 $i$ 个条件要求第 $x_i$ 个人与第 $y_i$ 个人建立联系。形式上，如果存在一个序列 $p_1 = x, p_2, p_3, \dots, p_k = y$，使得对于所有 $i$ 从 $1$ 到 $k - 1$，编号为 $p_i$ 和 $p_{i + 1}$ 的两个人相互认识，那么两个人 $x$ 和 $y$ 就建立了联系。

对于每个 $i$（$1 \leq i \leq d$），威廉希望你计算在满足从 $1$ 到 $i$ 的所有条件并且恰好进行 $i$ 次介绍的情况下，一个人最多可以有多少个熟人。这些条件在威廉进行 $i$ 次介绍后进行检查。每个 $i$ 的答案必须独立计算。这意味着当你计算 $i$ 的答案时，应该假设还没有两个人被介绍认识。

#### 说明/提示
第一个测试用例的解释：

在这个解释中，圆圈和里面的数字表示相应编号的人。线表示威廉介绍了两个相连的人。标记为红色的人有最多的熟人。这些不是介绍人的唯一正确方式。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609D/a4c52dc40d0c621cc37cb8aa412551d28349b4ab.png)

#### 样例 #1
##### 输入
```
7 6
1 2
3 4
2 4
7 6
6 5
1 7
```
##### 输出
```
1
1
3
3
3
6
```

#### 样例 #2
##### 输入
```
10 8
1 2
2 3
3 4
1 4
6 7
8 9
8 10
1 4
```
##### 输出
```
1
2
3
4
5
5
6
8
```

### 综合分析与结论
- **思路总结**：各题解核心思路一致，均是用并查集维护连通块，遍历规定时，若两点已连通则记录为空闲边，统计空闲边数量 `cnt`。每次查询时，找出最大的 `cnt + 1` 个连通块，将其大小求和再减 1 即为答案。
- **算法要点**：并查集用于判断两点是否连通及合并连通块，同时维护连通块大小；对连通块大小排序或用堆找出前 `cnt + 1` 大的连通块。
- **解决难点**：正确理解题意，明确所求为最大连通块大小减 1；处理重复边，将其转化为连接更大连通块的机会。

### 高评分题解
1. **作者：智子 (赞：6)，5星**
    - **关键亮点**：思路清晰，代码注释详细，对重复边的处理解释明确，便于理解。
    - **核心代码**：
```cpp
int find(int k) {
    return k == f[k]? k : f[k] = find(f[k]);
}

void merge(int x, int y) {
    x = find(x); y = find(y);
    if(x == y) {
        cnt++;
        return;
    }
    f[x] = y;
    sum[y] += sum[x];
}

// 主函数部分
for(int i = 1; i <= d; i++) {
    vector<int> v;
    int x, y;
    scanf("%d%d", &x, &y);
    merge(x, y);
    for(int j = 1; j <= n; j++) {
        if(j == find(j)) {
            v.push_back(sum[j]);
        }
    }
    sort(v.begin(), v.end(), greater<int>());
    int ans = 0;
    for(int j = 0; j < v.size() && j <= cnt; j++) {
        ans += v[j];
    }
    ans--;
    printf("%d\n", ans);
}
```
核心实现思想：`find` 函数用于查找节点的根节点并进行路径压缩，`merge` 函数用于合并两个节点所在的连通块，若两点已连通则 `cnt` 加 1。每次读入规定后，将所有连通块大小存入向量 `v` 并排序，取前 `cnt + 1` 大的求和减 1 得到答案。

2. **作者：Fislett (赞：2)，4星**
    - **关键亮点**：思路简洁明了，贪心策略阐述清晰，代码结构清晰。
    - **核心代码**：
```cpp
int find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if(fx == fy)
    {
        cnt ++;
        return ;
    }
    fa[fx] = fy;
    size[fy] += size[fx];
    return ;
}

// 主函数部分
for (int i = 1; i <= m; i ++)
{
    int x, y;
    scanf("%d%d", &x, &y);
    merge(x, y);
    int ans = 0;
    vector<int> g;
    for (int i = 1; i <= n; i ++) if (find(i) == i) g.push_back(size[i]);
    sort(g.begin(), g.end(), greater<int>());
    for (int i = 0; i <= cnt; i ++) ans += g[i];
    printf("%d\n", ans - 1);
}
```
核心实现思想：与智子的题解类似，`find` 函数查找根节点，`merge` 函数合并连通块并处理重复边。每次操作后，将连通块大小存入向量 `g` 排序，取前 `cnt + 1` 大的求和减 1 输出。

3. **作者：0xFF (赞：2)，4星**
    - **关键亮点**：详细分析了题目翻译问题，对解题思路的步骤阐述清晰，代码有输入优化。
    - **核心代码**：
```cpp
int find(int x){
    if(fa[x] == x){
        return x;
    }
    else return fa[x] = find(fa[x]);
}

void merge(int x,int y){
    x = find(x), y = find(y);
    if(x == y){
        cnt++;
        return;
    }
    fa[x] = y;
    sum[y] += sum[x];
}

// 主函数部分
for(int i=1;i<=d;i++){
    vector<int> v;
    int x = read(),y = read();
    merge(x,y);
    for(int j=1;j<=n;j++){
        if(j == find(j)){
            v.push_back(sum[j]);
        }
    }
    sort(v.begin(),v.end(),greater<int>());
    int ans = 0;
    for(int j=0;j<v.size() && j <= cnt;j++){
        ans += v[j];
    }
    printf("%lld\n",ans-1);
}
```
核心实现思想：同样使用并查集，`find` 函数和 `merge` 函数功能一致。每次读入规定后，将连通块大小存入向量 `v` 排序，取前 `cnt + 1` 大的求和减 1 输出。

### 最优关键思路或技巧
- **并查集**：高效判断两点是否连通及合并连通块，同时维护连通块大小。
- **贪心策略**：将重复边用于连接更大的连通块，以获得最大的连通块。
- **排序或堆**：找出前 `cnt + 1` 大的连通块。

### 拓展思路
同类型题可拓展到带权并查集、动态连通性问题等。类似算法套路如 Kruskal 算法求最小生成树，也是通过并查集判断连通性并合并集合。

### 推荐题目
1. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
2. [P1197 [JSOI2008]星球大战](https://www.luogu.com.cn/problem/P1197)
3. [P1525 [NOIP2010 提高组] 关押罪犯](https://www.luogu.com.cn/problem/P1525)

### 个人心得摘录与总结
- **0xFF**：提交代码时因题目翻译问题导致错误，查看题解后发现要求的是度数最大的点的边数（最大连通块大小减 1），提醒做题时要准确理解题意。

---
处理用时：51.14秒