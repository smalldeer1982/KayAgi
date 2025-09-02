# 题目信息

# [USACO21JAN] Dance Mooves S

## 题目描述

Farmer John 的奶牛们正在炫耀她们的最新舞步！

最初，所有的 $N$ 头奶牛（$2≤N≤10^5$）站成一行，奶牛 $i$ 排在其中第 $i$ 位。舞步序列给定为 $K$ （$1≤K≤2\times10^5$）个位置对 $(a_1,b_1),(a_2,b_2),…,(a_K,b_K)$。在舞蹈的第 $i=1…K$ 分钟，位置 $a_i$ 与 $b_i$ 上的奶牛交换位置。同样的 $K$ 次交换在第 $K+1…2K$ 分钟发生，在第 $2K+1…3K$ 分钟再次发生，以此类推，无限循环。换言之， 

 - 在第 $1$ 分钟，位置 $a_1$ 与 $b_1$ 上的奶牛交换位置。
 - 在第 $2$ 分钟，位置 $a_2$ 与 $b_2$ 上的奶牛交换位置。
 - ……
 - 在第 $K$ 分钟，位置 $a_K$ 与 $b_K$ 上的奶牛交换位置。
 - 在第 $K+1$ 分钟，位置 $a_1$ 与 $b_1$ 上的奶牛交换位置。
 - 在第 $K+2$ 分钟，位置 $a_2$ 与 $b_2$ 上的奶牛交换位置。
 - 以此类推……

对于每头奶牛，求她在队伍中会占据的不同的位置数量。

## 说明/提示

 - 奶牛 $1$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $2$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $3$ 可以到达位置 $\{1,2,3\}$。
 - 奶牛 $4$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $5$ 从未移动，所以她没有离开过位置 $5$。

#### 测试点性质：

 - 测试点 1-5 满足 $N≤100,K≤200$。
 - 测试点 6-10 满足 $N≤2000,K≤4000$。
 - 测试点 11-20 没有额外限制。

供题：Chris Zhang 

## 样例 #1

### 输入

```
5 4
1 3
1 2
2 3
2 4```

### 输出

```
4
4
3
4
1```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是先模拟一轮 $K$ 次交换，找出其中的环，因为环内的奶牛运动轨迹相同，经过的位置也相同，所以可以将环内的奶牛作为一个整体处理，最后统计每个环内奶牛经过的不同位置数量。

不同题解的主要区别在于实现方式，有的使用并查集维护环，有的使用深度优先搜索（DFS）来处理环，还有的通过模拟多轮操作来找出循环规律。在数据结构的使用上，大部分题解使用 `vector` 记录每个点途径的点，用 `set` 统计不同位置的数量。

### 所选题解
- **作者：Skies (赞：23)，4星**
  - **关键亮点**：思路清晰，语言生动易懂，详细阐述了如何利用并查集维护环，代码实现简洁明了。
- **作者：Zenith_Yeh (赞：8)，4星**
  - **关键亮点**：对样例进行详细分析，有助于理解思路，使用了快速读入输出模板，提高了代码效率。
- **作者：Lonely_NewYear (赞：0)，4星**
  - **关键亮点**：将问题转化为图论问题，把 $to$ 数组想象成一个图，每个点都在一个环上，通过 DFS 处理环，并且对数组的处理进行了优化，避免了每次都清空数组，降低了时间复杂度。

### 重点代码及核心实现思想
#### Skies 的题解
```cpp
// 并查集查找函数
int get(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=get(fa[x]);
}

int main()
{
    cin >> n >> k;
    init(); // 初始化并查集和数组
    for(int i = 1; i <= k; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        swap(a[x], a[y]);
        vc[a[x]].push_back(x); // 记录途径点
        vc[a[y]].push_back(y);
    }
    for(int i = 1; i <= n; i++)
    {
        vc[i].push_back(i); // 加上起点
    }
    for(int i = 1; i <= n; i++)
    {
        int x = get(i), y = get(a[i]);
        fa[x] = y; // 合并并查集
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j < vc[a[i]].size(); j++)
        {
            ans[get(a[i])].insert(vc[a[i]][j]); // 统计不同位置
        }
    }
    for(int i = 1; i <= n; i++)
    {
        printf("%d\n", ans[get(i)].size()); // 输出答案
    }
    return 0;
}
```
核心思想：先模拟一轮交换，记录每个点途径的点，然后用并查集将有相同运动轨迹的点合并到同一个集合中，最后用 `set` 统计每个集合中不同位置的数量。

#### Zenith_Yeh 的题解
```cpp
// 并查集查找函数
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main()
{
    n = read(), k = read();
    for(register int i = 1; i <= n; ++i)
        num[i] = i, fa[i] = i, lg[i].push_back(i);
    for(register int i = 1; i <= k; ++i)
    {
        int a = read(), b = read();
        lg[num[a]].push_back(b);
        lg[num[b]].push_back(a);
        swap(num[a], num[b]);
    }
    for(register int i = 1; i <= n; ++i)
    {
        int fx = find(i), fy = find(num[i]);
        if(fx != fy) fa[fy] = fx; // 合并并查集
    }
    for(register int i = 1; i <= n; ++i)
        for(register int j = 0; j < lg[i].size(); ++j)
            answer[find(i)].insert(lg[i][j]); // 统计不同位置
    for(register int i = 1; i <= n; ++i)
        Print(answer[i].size());
    io::flush();
    return 0;
}
```
核心思想：与 Skies 的题解类似，先模拟交换，记录途径点，再用并查集合并，最后统计不同位置数量。

#### Lonely_NewYear 的题解
```cpp
void dfs(int u)
{
    vis[u] = 1;
    q.push(u);
    int len = s[u].size();
    for(int i = 0; i < len; i++)
    {
        if(++cnt[s[u][i]] == 1) // 统计不同位置
        {
            tot++;
        }
    }
    if(!vis[to[u]])
    {
        dfs(to[u]);
    }
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
    {
        now[i] = i;
        s[i].push_back(i);
    }
    for(int i = 1; i <= k; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        s[now[a]].push_back(b);
        s[now[b]].push_back(a);
        swap(now[a], now[b]);
    }
    for(int i = 1; i <= n; i++)
    {
        to[now[i]] = i;
    }
    for(int i = 1; i <= n; i++)
    {
        if(!vis[i])
        {
            dfs(i);
            int res = tot;
            while(!q.empty()) // 遍历环上所有点
            {
                int u = q.front();
                q.pop();
                ans[u] = res;
                int len = s[u].size();
                for(int j = 0; j < len; j++)
                {
                    if(--cnt[s[u][j]] == 0) // 恢复计数
                    {
                        tot--;
                    }
                }
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}
```
核心思想：将问题转化为图论问题，通过 DFS 遍历环，利用 `cnt` 数组统计不同位置的数量，避免了每次都清空数组，提高了效率。

### 最优关键思路或技巧
- **利用环的性质**：发现经过 $K$ 次操作后会形成环，环内的奶牛运动轨迹相同，将环内的奶牛作为一个整体处理，减少了重复计算。
- **并查集的使用**：用并查集维护环，将有相同运动轨迹的点合并到同一个集合中，方便后续统计。
- **数据结构的选择**：使用 `vector` 记录每个点途径的点，用 `set` 统计不同位置的数量，避免了重复计数。
- **数组处理的优化**：如 Lonely_NewYear 的题解中，通过 `cnt` 数组的增减操作，避免了每次都清空数组，降低了时间复杂度。

### 可拓展之处
同类型题或类似算法套路：
- **循环节问题**：当问题中存在重复的操作或状态，且经过一定次数后会出现循环时，可以考虑找出循环节，利用循环节的性质简化计算。
- **图论中的环问题**：将问题转化为图论问题，找出图中的环，利用环的性质解决问题，如判断环的存在、计算环的长度等。

### 推荐题目
- [P1363 幻想迷宫](https://www.luogu.com.cn/problem/P1363)：涉及循环节和图的遍历。
- [P2661 信息传递](https://www.luogu.com.cn/problem/P2661)：与本题类似，需要找出图中的环。
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：可以通过模拟操作找出状态的循环规律。

### 个人心得摘录与总结
- **Lonely_NewYear**：赛时这题没弄出来，意识到自己的不足。最重要的优化是通过 `cnt` 数组的增减操作避免每次都清空数组，否则时间复杂度会提高，只能拿到 50 分。总结：在处理数组时要注意优化，避免不必要的重复操作，降低时间复杂度。

---
处理用时：54.21秒