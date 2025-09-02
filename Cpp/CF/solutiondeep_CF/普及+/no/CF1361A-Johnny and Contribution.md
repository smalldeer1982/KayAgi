# 题目信息

# Johnny and Contribution

## 题目描述

Today Johnny wants to increase his contribution. His plan assumes writing $ n $ blogs. One blog covers one topic, but one topic can be covered by many blogs. Moreover, some blogs have references to each other. Each pair of blogs that are connected by a reference has to cover different topics because otherwise, the readers can notice that they are split just for more contribution. Set of blogs and bidirectional references between some pairs of them is called blogs network.

There are $ n $ different topics, numbered from $ 1 $ to $ n $ sorted by Johnny's knowledge. The structure of the blogs network is already prepared. Now Johnny has to write the blogs in some order. He is lazy, so each time before writing a blog, he looks at it's already written neighbors (the blogs referenced to current one) and chooses the topic with the smallest number which is not covered by neighbors. It's easy to see that this strategy will always allow him to choose a topic because there are at most $ n - 1 $ neighbors.

For example, if already written neighbors of the current blog have topics number $ 1 $ , $ 3 $ , $ 1 $ , $ 5 $ , and $ 2 $ , Johnny will choose the topic number $ 4 $ for the current blog, because topics number $ 1 $ , $ 2 $ and $ 3 $ are already covered by neighbors and topic number $ 4 $ isn't covered.

As a good friend, you have done some research and predicted the best topic for each blog. Can you tell Johnny, in which order he has to write the blogs, so that his strategy produces the topic assignment chosen by you?

## 说明/提示

In the first example, Johnny starts with writing blog number $ 2 $ , there are no already written neighbors yet, so it receives the first topic. Later he writes blog number $ 1 $ , it has reference to the already written second blog, so it receives the second topic. In the end, he writes blog number $ 3 $ , it has references to blogs number $ 1 $ and $ 2 $ so it receives the third topic.

Second example: There does not exist any permutation fulfilling given conditions.

Third example: First Johnny writes blog $ 2 $ , it receives the topic $ 1 $ . Then he writes blog $ 5 $ , it receives the topic $ 1 $ too because it doesn't have reference to single already written blog $ 2 $ . Then he writes blog number $ 1 $ , it has reference to blog number $ 2 $ with topic $ 1 $ , so it receives the topic $ 2 $ . Then he writes blog number $ 3 $ which has reference to blog $ 2 $ , so it receives the topic $ 2 $ . Then he ends with writing blog number $ 4 $ which has reference to blog $ 5 $ and receives the topic $ 2 $ .

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
2 1 3```

### 输出

```
2 1 3```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1
1 1 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 3
1 2
2 3
4 5
2 1 2 2 1```

### 输出

```
2 5 1 3 4```

# AI分析结果

### 题目中文重写
#### Johnny and Contribution

##### 题目描述
今天，Johnny 想要提高他的贡献值。他的计划是写 $n$ 篇博客。一篇博客涵盖一个主题，但一个主题可以被多篇博客涵盖。此外，一些博客之间存在相互引用。每一对通过引用相连的博客必须涵盖不同的主题，否则读者会发现这些博客只是为了增加贡献而被拆分的。博客集合以及它们之间的双向引用关系被称为博客网络。

有 $n$ 个不同的主题，编号从 $1$ 到 $n$，按照 Johnny 的知识水平排序。博客网络的结构已经确定。现在，Johnny 必须按照一定的顺序撰写博客。他很懒，所以每次在撰写一篇博客之前，他会查看与该博客已经撰写好的相邻博客（即引用当前博客的博客），并选择一个未被相邻博客涵盖的编号最小的主题。很容易看出，这种策略总能让他选择一个主题，因为最多只有 $n - 1$ 个相邻博客。

例如，如果当前博客已经撰写好的相邻博客的主题编号为 $1$、$3$、$1$、$5$ 和 $2$，Johnny 会为当前博客选择主题编号 $4$，因为主题编号 $1$、$2$ 和 $3$ 已经被相邻博客涵盖，而主题编号 $4$ 未被涵盖。

作为好朋友，你进行了一些研究并预测了每篇博客的最佳主题。你能告诉 Johnny 他应该按照什么顺序撰写博客，以便他的策略能够产生你所选择的主题分配吗？

##### 说明/提示
在第一个样例中，Johnny 先撰写编号为 $2$ 的博客，此时还没有已经撰写好的相邻博客，所以它被分配到第一个主题。之后，他撰写编号为 $1$ 的博客，它引用了已经撰写好的第二篇博客，所以它被分配到第二个主题。最后，他撰写编号为 $3$ 的博客，它引用了编号为 $1$ 和 $2$ 的博客，所以它被分配到第三个主题。

第二个样例：不存在满足给定条件的排列。

第三个样例：首先，Johnny 撰写博客 $2$，它被分配到主题 $1$。然后，他撰写博客 $5$，它也被分配到主题 $1$，因为它没有引用唯一已经撰写好的博客 $2$。接着，他撰写编号为 $1$ 的博客，它引用了主题编号为 $1$ 的博客 $2$，所以它被分配到主题 $2$。然后，他撰写编号为 $3$ 的博客，它引用了博客 $2$，所以它被分配到主题 $2$。最后，他撰写编号为 $4$ 的博客，它引用了博客 $5$，并被分配到主题 $2$。

##### 样例 #1
###### 输入
```
3 3
1 2
2 3
3 1
2 1 3
```
###### 输出
```
2 1 3
```

##### 样例 #2
###### 输入
```
3 3
1 2
2 3
3 1
1 1 1
```
###### 输出
```
-1
```

##### 样例 #3
###### 输入
```
5 3
1 2
2 3
4 5
2 1 2 2 1
```
###### 输出
```
2 5 1 3 4
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是先判断题目是否有解，若有解则按照一定顺序输出点的编号。判断无解的条件基本一致：一是相邻点的目标数字不能相同；二是对于每个点，其相邻点的目标数字必须包含 $1$ 到 $t_i - 1$ 的所有数字。在有解的情况下，多数题解采用按照 $t_i$ 从小到大的顺序输出点编号的策略。不同题解的实现方式有所不同，包括直接排序判断、拓扑排序、队列维护等。

### 所选题解
- **作者：Alex_Wei (赞：13)，4星**
  - 关键亮点：思路清晰，代码简洁，直接按照 $t_i$ 从小到大排序，然后判断是否满足无解条件，若满足则输出 $-1$，否则输出排序后的点编号。
- **作者：LoserKugua (赞：3)，4星**
  - 关键亮点：使用拓扑排序，将题目转化为“某件事必须先于某件事干”的问题，通过建立新图和维护当前标数值，处理特殊情况，最终得到满足条件的顺序。
- **作者：Floating_Trees (赞：1)，4星**
  - 关键亮点：思路简洁，先判断是否有解，若有解则将点按照 $t_i$ 排序后输出点的编号。

### 重点代码
#### Alex_Wei 的代码
```cpp
const int N=5e5+5;

int n,m,pd[N];
vector <int> e[N];
struct pos{
    int id,val;
    bool operator < (const pos &v) const {return val<v.val;}
}c[N];

int main(){
    n=read(),m=read();
    for(int i=1;i<=m;i++){int u=read(),v=read(); e[u].pb(v),e[v].pb(u);}
    for(int i=1;i<=n;i++)c[i].val=read(),c[i].id=i;
    for(int i=1;i<=n;i++){
        map <int,int> mp;
        for(int it:e[i])mp[c[it].val]=1;
        for(int j=1;j<c[i].val;j++)if(!mp[j])puts("-1"),exit(0);
        if(mp[c[i].val])puts("-1"),exit(0);
    }
    sort(c+1,c+n+1);
    for(int i=1;i<=n;i++)cout<<c[i].id<<" ";
    return 0;
}
```
核心实现思想：先读取图的信息和每个点的目标数字，然后对于每个点，用 `map` 标记其相邻点的目标数字，判断是否满足无解条件，最后将点按照目标数字从小到大排序并输出点的编号。

#### LoserKugua 的代码
```cpp
#include<cstdio>
using namespace std;
const int maxn = 500005;
int n,m,u[maxn],v[maxn],t[maxn],head[maxn],deg[maxn],tot,q[maxn],qh,qt,ans[maxn],atop;
int nw[maxn];
struct edge {
    int to,next;
}e[maxn << 1];
void addedge(int u1, int v1) {
    e[++tot].to = v1;
    e[tot].next = head[u1];
    head[u1] = tot;
}
int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; ++i) scanf("%d %d", u + i, v + i);
    for(int i = 1; i <= n; ++i) scanf("%d", t + i);
    for(int i = 1; i <= m; ++i) {
        if(t[u[i]] == t[v[i]]) {
            printf("-1");
            return 0;
        }
        if(t[u[i]] < t[v[i]]) {
            addedge(u[i], v[i]);
            ++deg[v[i]];
        }
        else {
            addedge(v[i], u[i]);
            ++deg[u[i]];
        }
    }
    qh = 1;
    for(int i = 1; i <= n; ++i) 
        if(t[i] == 1) q[++qt] = i;
    while(qt >= qh) {
        int p = q[qh++];
        ans[++atop] = p;
        if(nw[p] + 1 != t[p]) {
            printf("-1");
            return 0;
        }
        for(int i = head[p]; i; i = e[i].next) {
            int v1 = e[i].to;
            if(nw[p] == nw[v1]) ++nw[v1];
            if(--deg[v1] == 0) q[++qt] = v1;
        }
    }
    if(atop != n) printf("-1");
    else for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
    return 0;
} 
```
核心实现思想：先读取图的信息和每个点的目标数字，对于每条边，根据目标数字大小建立有向边并统计入度，若相邻点目标数字相同则无解。将目标数字为 $1$ 的点入队，进行拓扑排序，在排序过程中维护当前标数值，判断是否满足条件，最后判断是否所有点都被访问到，若不是则无解，否则输出排序结果。

#### Floating_Trees 的代码
```cpp
#include <bits/stdc++.h>
#define i64 long long
#define endl '\n'

using namespace std;

const int N = 5e5 + 10;
int n, m;
vector<int> v[N];
struct node
{
    int id, t;
    bool operator < (const node & cmp) const 
    {
        return t < cmp.t;
    }
} u[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n >> m;
    while (m--)
    {
        int a, b; cin >> a >> b;
        v[a].push_back(b), v[b].push_back(a);
    }
    for (int i = 1;i <= n;i++)
        cin >> u[i].t, u[i].id = i;
    for (int i = 1;i <= n;i++)
    {
        map<int,int> mp;
        for (auto e : v[i])
            mp[u[e].t] = 1;
        for (int j = 1;j < u[i].t;j++)
            if (!mp[j])
                cout << -1 << endl, exit(0);
        if (mp[u[i].t]) cout << -1 << endl, exit(0);
    }
    sort(u + 1, u + 1 + n);
    for (int i = 1;i <= n;i++)
        cout << u[i].id << " \n"[i == n];

    return 0;
}
```
核心实现思想：先读取图的信息和每个点的目标数字，对于每个点，用 `map` 标记其相邻点的目标数字，判断是否满足无解条件，最后将点按照目标数字从小到大排序并输出点的编号。

### 最优关键思路或技巧
- **排序**：按照 $t_i$ 从小到大的顺序处理点，保证在处理每个点时，其相邻的较小 $t_i$ 的点已经处理完毕，便于判断是否满足条件。
- **无解判断**：通过判断相邻点的目标数字是否相同以及相邻点的目标数字是否包含 $1$ 到 $t_i - 1$ 的所有数字，来确定是否无解。

### 拓展思路
同类型题或类似算法套路：
- 图的染色问题：给定一个图和一些染色规则，要求找到一种合法的染色方案。
- 拓扑排序的应用：解决一些有先后顺序要求的问题，如任务调度、课程安排等。

### 推荐题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)：涉及拓扑排序和任务先后顺序的问题。
- [P1347 排序](https://www.luogu.com.cn/problem/P1347)：通过给定的关系进行拓扑排序判断是否有解。
- [P2853 [USACO06DEC]Cow Picnic S](https://www.luogu.com.cn/problem/P2853)：图论相关问题，需要对图进行遍历和处理。

### 个人心得
- **流绪**：比赛时错误地认为是找到一个起点然后从这个点向外填，导致思路错误。这提醒我们在解题时要准确理解题意，避免陷入错误的思维模式。

---
处理用时：78.36秒