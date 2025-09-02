# 题目信息

# Frog Traveler

## 题目描述

青蛙在 $n$ 米深的井中。

对于每一个深度，有两个量 $a_i$ 和 $b_i$。

$a_i$ 表示在深度为 $i$ 米的时候可以往上跳的最高高度，就是说在深度为 $i$ 米的地方可以往上跳 $\left[0,a_i\right]$ 米。

$b_i$ 表示在深度为 $i$ 米的地方时会往下滑 $b_i$ 米。

青蛙每跳一次，就会下滑一次。

请求出青蛙最少跳几次可以跳出井（深度为 $0$ 米）。

## 说明/提示

$1\le n\le3\times10^5,0\le a_i\le i,0\le b_i\le n-i$。

## 样例 #1

### 输入

```
3
0 2 2
1 1 0```

### 输出

```
2
1 0```

## 样例 #2

### 输入

```
2
1 1
1 0```

### 输出

```
-1```

## 样例 #3

### 输入

```
10
0 1 2 3 5 5 6 7 8 5
9 8 7 1 5 4 3 2 0 0```

### 输出

```
3
9 4 0```

# AI分析结果

### 算法分类
搜索

### 综合分析与结论
各题解思路丰富多样，涵盖了贪心、动态规划、图论、搜索等多种算法思想。在解决青蛙跳井问题时，核心在于处理青蛙跳跃和下滑的规则，找到最少跳跃次数及路径。

部分题解通过贪心策略，每次选择实际深度最小的点跳跃；部分题解采用动态规划，维护从起点到各点的最少跳跃次数；还有题解利用图论建图，通过最短路算法求解；搜索类题解则通过 BFS 或优化的 BFS 来探索路径。

解决的难点在于如何高效处理青蛙跳跃和下滑的过程，避免重复计算，降低时间复杂度。不同题解采用了不同的数据结构和优化技巧，如线段树优化建图、维护历史最高访问区间、利用双端队列 BFS 等。

### 所选题解
- **GaryH（4星）**
    - **关键亮点**：提出 $O(n)$ 且易实现的做法，通过数学归纳法证明每次跳跃后滑落前可达位置集合是右端点为 $n$ 的区间，动态维护该区间，时间复杂度低。
- **little_sun（4星）**
    - **关键亮点**：将问题转化为图论问题，建立虚点表示跳跃未下滑状态，用线段树优化建图，再通过双端队列 BFS 求解，思路清晰，复杂度为 $O(n \log n)$。
- **kirky_wang（4星）**
    - **关键亮点**：使用广搜解决问题，维护已枚举到的最高位置，避免重复遍历，保证每个元素最多入队一次，时间复杂度为 $O(n)$，且通过类似链表的方法输出方案。

### 重点代码
#### GaryH 的核心代码
```cpp
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)

const int N (3e5 + 10);
int n, a[N], b[N], c[N], rs[N], mn[N];
vector < int > ans;
 
int main() {
    n = read(); rep (i, 1, n) a[i] = read();
    rep (i, 1, n) b[i] = read(), c[i] = max(0, i + b[i] - a[i + b[i]]);
    rep (i, 0, n + 1) mn[i] = rs[i] = 1e9;
    per (i, n, 1) mn[i] = min (mn[i + 1], min(i, c[i])),
                  rs[i] = min (i, c[i]) < mn[i + 1] ? i : rs[i + 1];
    int hi = n;
    rep (i, 1, n) {
        ans.pb(hi = rs[hi]);
        if (hi <= mn[hi]) break;
        hi = mn[hi]; if (!hi) break;
    }
    if (hi) return cout << -1, 0;
    int sz = ans.size(); cout << sz << endl;
    rep (i, 1, sz - 1) cout << ans[i] << ' ';
    return cout << 0, 0;
}
```
**核心实现思想**：先预处理 $c$ 数组，代表上一次滑落前到达位置 $i$ 这次能到达的最小位置，再对 $c$ 数组做前缀最小值及记录最小值位置，动态维护可达区间，直到到达井口或无解。

#### little_sun 的核心代码
```cpp
struct SegmentTree
{
    int cnt, idx[Max];
    void build(int id, int l, int r)
    {
        if(l == r) 
            return (void) (idx[id] = l + n + 1);
        idx[id] = ++cnt; int mid = (l + r) >> 1;
        build(id << 1, l, mid), build(id << 1 | 1, mid + 1, r);
        if(idx[id << 1]) add_edge(idx[id], idx[id << 1], 0);
        if(idx[id << 1 | 1]) add_edge(idx[id], idx[id << 1 | 1], 0);
    }
    void modify(int id, int l, int r, int ql, int qr, int u)
    {
        if(ql > r || l > qr) return;
        if(ql <= l && r <= qr) 
            return add_edge(u, idx[id], 1);
        int mid = (l + r) >> 1;
        modify(id << 1, l, mid, ql, qr, u);
        modify(id << 1 | 1, mid + 1, r, ql, qr, u);
    }
} T;

void bfs()
{
    std::deque<int> q;
    dis[n] = 0, q.push_back(n);
    while(!q.empty())
    {
        int u = q.front(); q.pop_front();
        if(vis[u]) continue; vis[u] = 1;
        for(int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].to;
            if(dis[v] > dis[u] + e[i].dis)
            {
                dis[v] = dis[u] + e[i].dis;
                if(!vis[v])
                {
                    if(e[i].dis) q.push_back(v);
                    else q.push_front(v); pre[v] = u;
                }
            }
        }
    }
}
```
**核心实现思想**：通过线段树优化建图，将青蛙跳跃和下滑过程拆分为边权为 1 和 0 的边，再用双端队列 BFS 求解最短路。

#### kirky_wang 的核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int qu[N*3],hea=1,tal=0;
int a[N],b[N],ans[N],pre[N],sp[N];
bool used[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int j=1;j<=n;j++)
        scanf("%d",&b[j]);
    used[n]=1;
    qu[++tal]=n;
    int mins=n;
    bool flag=0;
    while(hea<=tal){
        int j=qu[hea++];
        if(j-a[j]<=0){
            flag =1;
            printf("%d\n",ans[j]+1);
            vector<int> otp;
            int now=j;
            while(now!=n){
                otp.push_back(pre[now]);
                now=sp[now];
            }
            for(int i=otp.size()-1;i>=0;i--)
                printf("%d ",otp[i]);
            printf("%d\n",0);
            break;
        }
        for(int i=mins-1;i>=j-a[j];i--){
            if(used[i])
                continue;
            int dest=i+b[i];
            if(used[dest])
                continue;
            sp[dest]=j;
            used[dest]=1;
            pre[dest]=i;
            ans[dest]=ans[j]+1;
            qu[++tal]=dest;
        }
        mins=min(mins,j-a[j]);
    }
    if(!flag)
        cout<<"-1";
    return 0;
}
```
**核心实现思想**：使用广搜，维护已枚举到的最高位置 `mins`，每次从 `mins - 1` 开始扩展，避免重复遍历，同时记录路径信息。

### 关键思路或技巧
- **维护可达区间**：如 GaryH 和 kirky_wang 的题解，通过维护可达区间避免重复计算，降低时间复杂度。
- **线段树优化建图**：little_sun 的题解利用线段树优化建图，将跳跃和下滑过程转化为图的边，再用双端队列 BFS 求解最短路。
- **避免重复访问**：多个题解都采用了避免重复访问的策略，如使用 `used` 数组标记已访问的点，或维护历史最高访问区间。

### 拓展思路
同类型题或类似算法套路：
- 涉及状态转移和路径搜索的问题，如迷宫问题、状态机问题等，可采用搜索算法（BFS、DFS）解决。
- 图论中的最短路问题，可根据边权特点选择合适的算法，如边权为 0 和 1 时可使用双端队列 BFS。
- 区间操作问题，可考虑使用线段树、树状数组等数据结构优化。

### 推荐题目
- [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)：涉及状态转移和搜索，与青蛙跳井问题类似。
- [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)：经典的迷宫搜索问题，可练习 BFS 和 DFS 算法。
- [P3371 单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：考察最短路算法，可加深对图论和最短路的理解。

### 个人心得
- **Arghariza**：尝试用线段树优化建图直接建图会出错，因为原建图方式可能让青蛙一直下滑，应将跳跃和下滑过程分开建图，体现了对题目规则理解的重要性。
- **一Iris一**：普通图论做法复杂度瓶颈在于每个点扫全部出边，可借用树上冰茶姬覆盖的想法维护已扫过的区间，降低复杂度，提供了一种优化思路。 

---
处理用时：86.39秒