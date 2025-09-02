# [OOI 2024] Evidence Board

## 题目描述

Volodya 梦想成为一名侦探。因此，Volodya 经常阅读讲述破案传奇的书籍。在研究下一个案件时，Volodya 发现了调查过程中的一些有趣细节。

本案共有 $n$ 名嫌疑人。证据板上包含了全部 $n$ 个人。最初，嫌疑人之间没有任何联系。

在调查过程中，嫌疑人之间逐渐出现了新的联系。每一条新联系都连接了此前尚未直接或间接（通过其他人）相连的两个人。

让我们来看一下当 $A$ 和 $B$ 之间出现一条联系时的情况。除了涉及的两个人名字外，每条联系还包含三个参数：$c_A$ —— 针对 $A$ 的证据强度，$c_B$ —— 针对 $B$ 的证据强度，$w_{AB}$ —— 这条联系的总证据强度。出于自然原因，联系的证据强度不能超过针对 $A$ 和 $B$ 的证据强度之和。也就是说，对于每一条联系，**一定**有 $w_{AB} \leq c_A + c_B$。侦探们在获得这样一条联系时，会在证据板上将 $A$ 和 $B$ 的照片之间画一条线，并将 $w_{AB}$ 标注在这条线上。同时，会在 $A$ 的照片上贴上写有 $c_A$ 的便签，在 $B$ 的照片上贴上写有 $c_B$ 的便签。如果照片上已经有其他便签，则新便签会贴在旧便签之上。

案件正是在所有嫌疑人通过 $n-1$ 条联系连通时被侦破的。破案后，证据板以原貌被陈列在博物馆中。

受到这种方式的启发，Volodya 参观了博物馆，并详细研究了这块证据板。Volodya 注意到，对于每个人 $v$，其照片上从上到下贴有编号为 $c_{v,1}, \ldots, c_{v,deg_v}$ 的便签。这里 $deg_v$ 表示与 $v$ 相关的联系数量。同时，Volodya 记得第 $i$ 条联系发生在 $a_i$ 和 $b_i$ 之间，证据强度为 $w_i$。不幸的是，这些联系的编号是随意的，并不一定与它们在调查中出现的先后顺序一致。

由于联系编号的混乱，证据板上的信息无法帮助还原调查过程。现在 Volodya 需要你帮助他还原一种可能的、侦探们获得这些联系的时间顺序。如果不存在符合条件的顺序，也有可能是博物馆伪造了信息。

## 说明/提示

### 说明

在第一个样例中，可能的顺序之一为 $[1, 4, 2, 3]$。按时间顺序，第 $1$ 条联系连接了 $A=1$ 和 $B=2$，$c_A=4, c_B=2, w_{AB}=3$，$3 \leq 2+4$，证据合理。第 $2$ 条联系连接了 $A=3$ 和 $B=5$，$c_A=3, c_B=3, w_{AB}=6$，$6 \leq 3+3$，证据合理。第 $3$ 条联系连接了 $A=1$ 和 $B=3$，$c_A=0, c_B=1, w_{AB}=1$，$1 \leq 0+1$，证据合理。第 $4$ 条联系连接了 $A=3$ 和 $B=4$，$c_A=6, c_B=8, w_{AB}=12$，$12 \leq 6+8$，证据合理。参见下图更易理解。

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/fyo2kfnk.png)
:::

### 计分方式

本题共九组测试。只有通过该组及其所有依赖组全部测试，才能获得该组分数。请注意，部分组无需通过样例测试。**Offline-evaluation** 表示该组的结果仅在比赛结束后可见。

| 组别 | 分值 | 额外约束 | < | 依赖组 | 备注 |
|:-----:|:------:|:----------------------:|:--:|:---------------:|:-------:|
|       |        | $n$ | $a_i, b_i, c_i, w_i$ | | |
| 0 | 0 | -- | -- | -- | 样例。 |
| 1 | 10 | $n \le 10$ | -- | 0 | -- |
| 2 | 15 | -- | $a_i = i, b_i = i+1$ 对所有 $i$ | -- | -- |
| 3 | 8 | -- | $a_i = 1, b_i = i+1$ 对所有 $i$ | -- | -- |
| 4 | 9 | -- | $a_i \leq 2, b_i = i+1$ 对所有 $i$ | 3 | -- |
| 5 | 7 | $n \le 1000$ | $c_{i,1} \leq c_{i,2} \leq \ldots \leq c_{i, deg_i}$ 对所有 $i$ | -- | -- |
| 6 | 7 | $n \le 1000$ | $c_{i, j} = 0$ 对所有 $1 \le i \le n$ 且 $j \geq 2$ | -- | -- |
| 7 | 17 | -- | $\displaystyle\sum_{v=1}^{n} \displaystyle\sum_{i=1}^{deg_v} c_{v,i} = \displaystyle\sum_{i=1}^{n-1} w_i$ | -- | -- |
| 8 | 16 | $n \le 1000$ | -- | 0, 1, 5, 6 | -- |
| 9 | 11 | -- | -- | 0 -- 8 | **Offline-evaluation** |

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
5 0
1 2 3
1 3 1
3 4 12
3 5 6
0 4
2
6 1 3
8
3```

### 输出

```
Yes
1 4 2 3```

## 样例 #2

### 输入

```
7 0
1 2 4
2 3 4
3 4 4
4 5 4
5 6 4
6 7 4
2
1 2
2 3
1 2
3 2
1 2
179```

### 输出

```
Yes
5 1 2 3 6 4```

## 样例 #3

### 输入

```
4 0
1 2 7
1 3 6
1 4 5
3 2 1
5
4
3```

### 输出

```
No```

# 题解

## 作者：nueryim (赞：2)

# 题解：P13503 [OOI 2024] Evidence Board

## 分析

这道题可以分为 2 步解决：

1. 对于每条边，确定其两端点对应的**便签**
2. 排出所有边的添加顺序

### Step 1：确定边对应的证据强度

>记一条边两端点为 $u$、$v$，边的证据强度为 $w$（其中 $u$ 的深度比 $v$ 小）
>
>记这条边对应的点的**便签的证据强度**为 $a_u$、$a_v$

以 1 号节点为根，将整棵树强制变为有根树。

注意到**连接叶子节点的边**和**叶子结点的证据强度**一定是对应的，那么我们就能确定这些边一端的证据强度（$a_v$）。

考虑找出**连接叶子节点的边**另一端的证据强度，有限制：

$$w\leq a_u+a_v$$

其中 $a_v$ 和 $w$ 是确定的，将式子变形：

$$a_v\geq w-a_u$$

我们每次可以贪心地找**最小的** $a_u$，将其确定为这条边的，显然不劣。**如果找不到，那么必然无解**。

确定完一条边后可以直接将其删去，那么后续就会出现其他的叶子节点，我们可以用同样的方式更新。

### Step 2：排出所有边的添加顺序

这时我们已经将每个点的每张便签与边一一对应了起来。

考虑建一张新图，把原来**树上的边**当成**新图的点**，使他们编号相同。

>记 $b_{u,i}$ 表示 $u$ 号点从上往下第 $i$ 张**便签**对应的**原树上的边**的编号。

在新图上，我们对每个 $b_{u,i}$ 向 $b_{u,i+1}$ 连边，这样新图一定是一个 $\operatorname{DAG}$，拓扑排序即可。

## 代码

总复杂度是 $O(n\log n)$ 的，瓶颈在 `Step1`。

读入写唐了，凑活看吧……

~~~cpp
// P13503 (AC)

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

#define str string
#define pii pair <int, int>

using namespace std;

const int N = 2e5 + 5;

int n, c;
int d[N];

struct edge
{
    int u, v, w;
} e[N];

vector <pii> g[N], h[N];
vector <int> f[N];

set <pii> p[N];
set <pii> ::iterator spiit;

inline void tag(int u, int v, int w) //找出与边对应的便签
{
    int t = p[v].begin()->second;
    spiit = p[u].lower_bound(make_pair(e[w].w - h[v][t].first, 0));
    if (spiit == p[u].end()) //找不到无解
    {
        cout << "No" << endl;
        exit(0);
    }
    int s = spiit->second;
    h[u][s].second = w;
    h[v][t].second = w;
    p[u].erase(make_pair(h[u][s].first, s));
    p[v].erase(make_pair(h[v][t].first, t));
}

void dfs(int u, int f)
{
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i].first;
        int w = g[u][i].second;
        if (v == f) continue;
        dfs(v, u);
        tag(u, v, w);
    }
}

queue <int> que;

inline void tup() //最后的拓扑排序
{
    for (int i = 1; i < n; i ++)
        if (d[i] == 0)
            que.push(i);
    while (!que.empty())
    {
        int u = que.front(); que.pop();
        cout << u << " ";
        for (int i = 0; i < f[u].size(); i ++)
        {
            int v = f[u][i];
            if (-- d[v] == 0)
                que.push(v);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> c;
    for (int i = 1; i <  n; i ++)
    {
        cin >> e[i].u >> e[i].v >> e[i].w;
        g[e[i].u].push_back(make_pair(e[i].v, i));
        g[e[i].v].push_back(make_pair(e[i].u, i));
    }
    int idx;
    str sss;
    getline(cin, sss);
    for (int i = 1; i <= n; i ++)
    {
        getline(cin, sss);
        istringstream sin(sss);
        while (sin >> idx)
        {
            h[i].push_back(make_pair(idx, 0));
            p[i].insert(make_pair(idx, h[i].size() - 1));
        }
    }
    dfs(1, 0);

    cout << "Yes" << endl;
    for (int i = 1; i <= n; i ++) //建一张新图
        for (int j = 1; j < h[i].size(); j ++)
        {
            int u = h[i][j - 1].second;
            int v = h[i][j].second;
            f[v].push_back(u);
            d[u] ++;
        }
    tup();

    return 0;
}
~~~

---

## 作者：FFTotoro (赞：1)

[XVIII Open Olympiad in Informatics - Final Stage, Day 1 T2](https://codeforces.com/contest/1939/problem/B) 非官方题解。

唯一场切的一个；很好的树上贪心题。

题目很长、条件很多，考虑先从菊花图的部分分出发；因为所有边都有一个端点是 $1$，所以条件 $w_{AB}\le c_A+c_B$ 可以转化为 $w_{1B}\le c_{1,i}+c_{B,1}\Rightarrow c_{1,i}\ge w_{1B}-c_{B,1}$，即给每个点安排一个对应的 $c_{1,i}$ 使其满足这个条件。又因为不等式右边是一个定值，考虑贪心，将所有 $c_{1,i}$ 和 $w_{1B}-c_{B,1}$ 分别排序，如果对应位置的 $c_{1,i}<w_{1B}-c_{B,1}$ 那么无解，否则对于每个结点 $B$ 安排对应位置的 $c_{1,i}$ 即可。

考虑拓展上述做法；对于一个结点 $U$ 考虑其所有儿子：如果一个儿子 $K$ 的所有后代都已经完成了安排，那么它必然会剩下一个 $c_{K,i}$（记为 $up_K$）上传给父亲。仍然考虑贪心，将所有从儿子传上来的 $up_K$ 按照 $w_{UK}-up_K$ 排序，再将自己的所有 $c_{U,i}$ 排序，判断对应位置是否满足 $c_{U,i}\ge w_{UK}-up_K$。只不过这一次如果有对应位置不满足，可以将该位置的 $c_{U,i}$ **上传给 $U$ 的父亲**，如果之后还是有不满足的就无解；如果不存在这样的 $c_{U,i}$，那么就把剩下来的那个最大的 $c_{U,i}$ 上传给父亲。显然这样的策略是正确的。**注意特判根结点的情况。**

最后确定了每个结点的所有边的顺序后跑一遍拓扑排序就能确定全局的顺序。

代码实现有一定细节。放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tpi;
int main(){
  ios::sync_with_stdio(false);
  int n,id; cin>>n>>id;
  vector<tpi> e(n-1);
  vector<vector<tpi> > g(n);
  vector<vector<int> > c(n);
  for(int i=0;i<n-1;i++){
    auto &[u,v,w]=e[i]; cin>>u>>v>>w;
    g[--u].emplace_back(--v,w,i);
    g[v].emplace_back(u,w,i);
  }
  for(int i=0;i<n;i++){
    c[i].resize(g[i].size());
    for(auto &j:c[i])cin>>j;
  }
  for(auto &i:c)reverse(i.begin(),i.end());
  vector<vector<int> > l(n);
  for(int i=0;i<n;i++)
    l[i].resize(c[i].size(),-1);
  vector<int> up(n),ps(n);
  function<void(int,int)> dfs=[&](int u,int f){
    for(auto [i,w,n]:g[u])
      if(i!=f)dfs(i,u);
    vector<pii> s(c[u].size()),o(c[u].size());
    for(int i=0;i<c[u].size();i++)
      o[i]=make_pair(c[u][i],i);
    sort(o.begin(),o.end());
    if(u){
      int p=0,d=0;
      for(auto [i,w,n]:g[u])
        if(i!=f)s[p++]=make_pair(w-up[i],n);
        else s[c[u].size()-1]=make_pair(0,n);
      sort(s.begin(),prev(s.end()));
      for(int i=0;i<c[u].size()-1;i++){
        if(o[i+d].first<s[i].first){
          if(d)cout<<"No\n",exit(0);
          d=1,up[u]=o[i].first,ps[u]=o[i].second;
          if(o[i+d].first<s[i].first)cout<<"No\n",exit(0);
        } // 存在不满足条件的 c[u][i]
        l[u][o[i+d].second]=s[i].second;
      }
      if(!d)up[u]=o.back().first,ps[u]=o.back().second;
      l[u][ps[u]]=s.back().second;
    } // 非根结点
    else{
      for(int i=0;i<c[u].size();i++){
        auto [v,w,n]=g[u][i];
        s[i]=make_pair(w-up[v],n);
      }
      sort(s.begin(),s.end());
      for(int i=0;i<c[u].size();i++){
        if(o[i].first<s[i].first)cout<<"No\n",exit(0);
        l[u][o[i].second]=s[i].second;
      }
    } // 根结点
  };
  dfs(0,0);
  vector<vector<int> > g2(n-1);
  vector<int> d(n);
  for(int i=0;i<n;i++)
    for(int j=1;j<c[i].size();j++)
      g2[l[i][j-1]].emplace_back(l[i][j]),d[l[i][j]]++;
      // 相邻边的顺序确定
  queue<int> q;
  for(int i=0;i<n-1;i++)
    if(!d[i])q.emplace(i);
  cout<<"Yes\n";
  while(!q.empty()){
    int u=q.front(); q.pop();
    cout<<u+1<<' ';
    for(int i:g2[u])
      if(!--d[i])q.emplace(i);
  } // 拓扑排序
  return 0;
}
```

---

## 作者：chen_zhe (赞：0)

**这是官方题解的 AI 中文翻译。**

一般说明：我们重新表述一下这个问题。与其“从零构建”这棵树，不如反过来，逐步从树上移除边。最终再将得到的答案逆序。在本教程中，我们将以“移除树边”的方式来解决问题。树上每个顶点的贴纸列表称为一个栈，栈顶元素永远是最先需要被移除的贴纸。

- **子任务 1**

本子任务可以通过完全暴力枚举解决。边的移除顺序共有 $(n-1)!$ 种可能。每种顺序都可以在 $\mathcal{O}(n)$ 的时间内直接判断。

复杂度：$\mathcal{O}(n!)$

- **子任务 2**

竹子（即链状树）。

对前缀进行动态规划。$dp[v][i]$ 表示一个布尔值：是否可以从顶点 $1$ 到 $v$ 移除竹子，但前提是顶点 $v$ 的栈中只剩下 $c_{v,i}$（$i \in \{0,1\}$）。

动态规划的初始状态：$dp[1][0] = dp[1][1] = \text{true}$

动态规划的转移：需要枚举所有四种可能的栈顶元素组合，判断是否可以移除 $v$ 与 $v-1$ 之间的边，如果可以，则通过 $dp[v-1][i]$ 转移。

若 $dp[n][0] = \text{true}$，则有解，否则无解。

恢复方案时，对于每条边，需要记录它是以哪一组 $i_1, i_2$ 被移除的。先移除所有 $i_1 = 0, i_2 = 0$ 的边，再依次是 $i_1 = 1, i_2 = 0$，$i_1 = 0, i_2 = 1$，$i_1 = 1, i_2 = 1$。

复杂度：$\mathcal{O}(n)$

- **子任务 3**

星形树。

从 $2$ 到 $n$ 依次处理所有叶子。假设当前考虑叶子 $v$。在数组 $c_1$ 中，找到最小的一个数，且满足 $\geq w_v - c_{v,1}$。可以证明，选择这个数来移除通向 $v$ 的边是最优的。然后，从 $c_1$ 中移除这个数。实现时，使用 $\text{std::multiset}$ 维护 $c_1$，并用 $\text{lower\_bound}$ 查找。

所需的边移除顺序就是 $c_1$ 原序列的顺序。

复杂度：$\mathcal{O}(n \log n)$

- **子任务 4**

两个星形树，基点之间有一条边相连。

分别按子任务 3 的方法处理两个星形树。此后，每个基点都只剩下一个数。如果这两个数允许移除基点之间的边，则有解，否则无解。合适的移除顺序是：先移除第一棵星形树基点之前的所有边，再移除第二棵星形树基点之前的所有边，然后移除基点之间的边，最后分别移除两棵星形树基点之后的所有边。

复杂度：$\mathcal{O}(n \log n)$

- **子任务 5**

顶点上的数值递增。

如果某一时刻某条边可以被移除，那么它在之后的任意时刻也都可以被移除。因此，任何时刻都可以移除任意一条可移除的边。解法为贪心算法：每次找到一条可以被移除的边，将其从树中移除，重复 $n-1$ 次。如果某一时刻没有可移除的边，则无解。

复杂度：$\mathcal{O}(n^2)$

- **子任务 6**

注意，对于任意一个测试，有如下事实：如果我们将原测试中所有栈反转，得到一个“新”测试，那么如果原测试无解，新测试也无解；如果原测试有解，新测试的答案就是原测试答案的逆序。由此，子任务 6 的解法可以直接由子任务 5 推出：只需将所有数组反转，以及最终答案反转即可。

复杂度：$\mathcal{O}(n^2)$

- **完整解法**

完整解法基于一个关键思想：“对于任意一种将相邻顶点的栈元素分配给每条边的方式（不重复），总存在一种边的移除顺序，使得每条边都能与分配给它的元素一起被移除。”

关键思想证明：考虑任意一种分配。每个顶点都指向一个相邻的边，并将栈顶元素分配给该边，视为“半准备好被移除”。由于有 $n$ 个顶点，$n-1$ 条边，必然存在一条边被它两端的顶点同时指向。这条边可以被移除。移除后，树被分成两个子树，对它们递归应用同样的推理。

基于这一关键思想，问题可以分为两部分：

1. 构造任意一种合法的边与栈元素的分配方式
2. 恢复边的移除顺序

分配方式的构造类似于子任务 3 的贪心算法。采用任意一种树的遍历顺序，将顶点按遍历逆序（从叶子到根）处理。设当前处理的顶点为 $v$，则从父节点的栈中选择最小的、满足 $\geq w_v - c_v$ 的数，分配给 $v$ 栈中唯一剩下的数。

实现时，每个顶点维护一个 $\texttt{std::multiset}$ 存储数值，利用 $\texttt{lower\_bound}$ 和 $\texttt{erase}$ 操作。

恢复顺序时，对于每条边，记录其准备被移除的状态（0/1/2）。所有准备好被移除的边存入栈。每次取出任意一条边，移除它，并将最多两条相关边的“准备移除”状态加一。如果这些边变为可移除，则加入栈。

最终复杂度：$\mathcal{O}(n \log n)$

---

