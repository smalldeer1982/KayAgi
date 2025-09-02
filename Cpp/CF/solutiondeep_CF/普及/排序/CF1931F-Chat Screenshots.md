# 题目信息

# Chat Screenshots

## 题目描述

There are $ n $ people in the programming contest chat. Chat participants are ordered by activity, but each person sees himself at the top of the list.

For example, there are $ 4 $ participants in the chat, and their order is $ [2, 3, 1, 4] $ . Then

- $ 1 $ -st user sees the order $ [1, 2, 3, 4] $ .
- $ 2 $ -nd user sees the order $ [2, 3, 1, 4] $ .
- $ 3 $ -rd user sees the order $ [3, 2, 1, 4] $ .
- $ 4 $ -th user sees the order $ [4, 2, 3, 1] $ .

 $ k $ people posted screenshots in the chat, which show the order of participants shown to this user. The screenshots were taken within a short period of time, and the order of participants has not changed.

Your task is to determine whether there is a certain order that all screenshots correspond to.

## 样例 #1

### 输入

```
10
5 1
1 2 3 4 5
4 4
1 2 3 4
2 3 1 4
3 2 1 4
4 2 3 1
6 2
1 3 5 2 4 6
6 3 5 2 1 4
3 3
1 2 3
2 3 1
3 2 1
10 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
1 1
1
5 2
1 2 3 5 4
2 1 3 5 4
3 3
3 1 2
2 3 1
1 3 2
5 4
3 5 1 4 2
2 5 1 4 3
1 5 4 3 2
5 1 4 3 2
3 3
1 3 2
2 1 3
3 2 1```

### 输出

```
YES
YES
YES
YES
NO
YES
YES
YES
YES
NO```

# AI分析结果

### 题目中文重写
#### 题目描述
编程竞赛聊天室中有 $n$ 个人。聊天室参与者按活跃度排序，但每个人都将自己视为列表的顶部。

例如，聊天室中有 $4$ 名参与者，他们的顺序是 $[2, 3, 1, 4]$。那么：
- 第 $1$ 个用户看到的顺序是 $[1, 2, 3, 4]$。
- 第 $2$ 个用户看到的顺序是 $[2, 3, 1, 4]$。
- 第 $3$ 个用户看到的顺序是 $[3, 2, 1, 4]$。
- 第 $4$ 个用户看到的顺序是 $[4, 2, 3, 1]$。

有 $k$ 个人在聊天室中发布了截图，这些截图显示了该用户看到的参与者顺序。截图是在短时间内拍摄的，参与者的顺序没有改变。

你的任务是确定是否存在一个所有截图都对应的特定顺序。

#### 样例 #1
##### 输入
```
10
5 1
1 2 3 4 5
4 4
1 2 3 4
2 3 1 4
3 2 1 4
4 2 3 1
6 2
1 3 5 2 4 6
6 3 5 2 1 4
3 3
1 2 3
2 3 1
3 2 1
10 2
1 2 3 4 5 6 7 8 9 10
10 9 8 7 6 5 4 3 2 1
1 1
1
5 2
1 2 3 5 4
2 1 3 5 4
3 3
3 1 2
2 3 1
1 3 2
5 4
3 5 1 4 2
2 5 1 4 3
1 5 4 3 2
5 1 4 3 2
3 3
1 3 2
2 1 3
3 2 1
```
##### 输出
```
YES
YES
YES
YES
NO
YES
YES
YES
YES
NO
```

### 综合分析与结论
这些题解主要围绕将问题转化为图论问题，通过建图和拓扑排序来判断是否存在满足所有截图的顺序。大部分题解思路相似，即根据截图中除第一个元素外的顺序关系建图，若图中存在环则无解，否则有解。部分题解还提到了使用 tarjan 算法或 DFS 来判环。

### 所选题解
- **作者：yyrwlj (赞：3)，4星**
    - **关键亮点**：思路清晰，代码简洁，详细说明了建图和拓扑排序的过程，且对建边进行了优化，只连相邻点的边，避免了不必要的时间和空间浪费。
- **作者：SXqwq (赞：2)，4星**
    - **关键亮点**：同样使用拓扑排序，代码结构清晰，使用 `vector` 存储边，易于理解和实现。
- **作者：信息向阳花木 (赞：2)，4星**
    - **关键亮点**：思路明确，代码规范，使用邻接表存储图，实现了拓扑排序判环的功能。

### 重点代码
#### yyrwlj 的代码
```cpp
#include <iostream>
using namespace std;
const int N = 200005;
struct Edge{
    int to, nxt;
}g[N];
int h[N], d[N], idx;
int a[N], q[N];
void add(int a,int b)
{
    g[++idx].to = b, g[idx].nxt = h[a], h[a] = idx;
    d[b] ++;
}
void work()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i=1;i<=n;i++)
        h[i] = d[i] = 0;
    idx = 0;
    for (int i=1;i<=k;i++)
    {
        for (int j=1;j<=n;j++)
            scanf("%d", &a[j]);
        for (int j=2;j<n;j++)
            add(a[j], a[j + 1]);
    }
    int hh = 0, tt = -1;
    for (int i=1;i<=n;i++)
        if (d[i] == 0)
            q[++tt] = i;
    while (hh <= tt)
    {
        int t = q[hh ++];
        for (int i = h[t]; i; i = g[i].nxt)
        {
            int j = g[i].to;
            if (--d[j] == 0)
                q[++tt] = j;
        }
    }
    for (int i=1;i<=n;i++)
        if (d[i] > 0)
        {
            puts("NO");
            return;
        }
    puts("YES");
}
```
**核心实现思想**：首先根据输入的截图信息建图，对于每个截图中除第一个元素外的相邻元素，从前一个元素向后一个元素连边，并记录每个点的入度。然后将入度为 0 的点入队，进行拓扑排序。最后检查是否所有点都入队过，如果有入度不为 0 的点，则说明图中存在环，无解。

#### SXqwq 的代码
```cpp
#include <bits/stdc++.h> 
using namespace std;
const int N = 100010;
int n,k;
int last;
int T;
vector <int> Edge[N];
int d[N];
int vis[N];
bool flag = 1;
int cnt = 0;
queue <int> q;
void topsort()
{
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        cnt ++;
        for(auto v:Edge[u])
        {
            d[v] --;
            if(!d[v]) q.push(v);
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++) 
        {
            d[i] = 0;
            vis[i] = 0;
        }
        for(int i=1;i<=n;i++) Edge[i].clear();
        while(!q.empty()) q.pop();
        flag = 1;
        cnt = 0;
        for(int i=1;i<=k;i++)
        {
            for(int j=1;j<=n;j++)
            {
                int x;
                cin>>x;
                if(j > 2) 
                {
                    Edge[last].push_back(x);
                    d[x] ++;
                }
                last = x; 
            }
        }
        for(int i=1;i<=n;i++)
        {
            if(!d[i]) 
            {
                q.push(i);
            }
        }
        topsort();
        if(cnt == n) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
}
```
**核心实现思想**：使用 `vector` 存储图的边，根据截图信息建图并记录入度。将入度为 0 的点入队，进行拓扑排序，使用 `cnt` 记录入队的点的数量。最后比较 `cnt` 和 `n` 的大小，如果相等则说明图中无环，有解。

#### 信息向阳花木的代码
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 200010;

int t, k, n;
int a[N], h[N], e[N], ne[N], r[N], idx;

void add(int x, int y)
{
    e[idx] = y, ne[idx] = h[x], h[x] = idx ++;
}

int main()
{
    scanf("%d", &t);
    while (t -- )
    {
        memset(h, -1, sizeof h);
        memset(r, 0, sizeof r);
        idx = 0;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= k; i ++ )
            for (int j = 1; j <= n; j ++ )
            {
                scanf("%d", &a[j]);
                if(j <= 2) continue;
                add(a[j - 1], a[j]);
                r[a[j]] ++;
            }
        queue<int> q;
        int cnt = 0;
        for (int i = 1; i <= n; i ++ ) if(!r[i]) q.push(i);
        while (!q.empty())
        {
            int t = q.front(); cnt ++;
            q.pop();
            for (int i = h[t]; ~i; i = ne[i])
            {
                int j = e[i];
                r[j] --;
                if(r[j] == 0) q.push(j);
            }
        }
        if(cnt == n) puts("Yes");
        else puts("No");
    }
    return 0;
}
```
**核心实现思想**：使用邻接表存储图，根据截图信息建图并记录入度。将入度为 0 的点入队，进行拓扑排序，使用 `cnt` 记录入队的点的数量。最后比较 `cnt` 和 `n` 的大小，如果相等则说明图中无环，有解。

### 最优关键思路或技巧
- **图论建模**：将问题转化为图论问题，通过建图来表示元素之间的顺序关系，是解决此类问题的关键思路。
- **拓扑排序判环**：利用拓扑排序判断图中是否存在环，若存在环则说明顺序关系存在矛盾，无解；否则有解。
- **建边优化**：只连相邻点的边，避免了不必要的时间和空间浪费。

### 拓展思路
同类型题或类似算法套路：
- 任务调度问题：给定一系列任务和它们之间的依赖关系，判断是否可以完成所有任务。
- 课程安排问题：给定课程和它们之间的先修关系，判断是否可以完成所有课程。
- 食物链问题：给定生物之间的捕食关系，判断是否存在矛盾。

### 推荐洛谷题目
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)
- [P1347 排序](https://www.luogu.com.cn/problem/P1347)
- [P2853 [USACO06DEC]Cow Picnic S](https://www.luogu.com.cn/problem/P2853)

### 个人心得摘录与总结
- **I_will_AKIOI**：赛时因为多测没清空导致 TLE，提醒我们在多测试用例的题目中要注意清空相关变量。
- **Lele_Programmer**：赛时 18 分钟无伤 AC 此题，说明对拓扑排序等算法的熟练掌握可以快速解决此类问题。

---
处理用时：71.39秒