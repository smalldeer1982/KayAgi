# 题目信息

# [ABC277C] Ladder Takahashi

## 题目描述

【题面翻译】

有一座很高的楼，你现在在第一层。

有 $n$ 个传送门，每个传送门连接第 $a_i$ 层与 $b_i$ 层。传送门是双向的。

请你求出你能到达的最高楼层。

translated by @[liangbowen](https://www.luogu.com.cn/user/367488).

## 说明/提示

$1 \le n \le 2 \times 10^5$

$1 \le a_i, b_i \le 10^9$

保证 $a_i \ne b_i$。

## 样例 #1

### 输入

```
4

1 4

4 3

4 10

8 3```

### 输出

```
10```

## 样例 #2

### 输入

```
6

1 3

1 5

1 12

3 5

3 12

5 12```

### 输出

```
12```

## 样例 #3

### 输入

```
3

500000000 600000000

600000000 700000000

700000000 800000000```

### 输出

```
1```

# AI分析结果

### 题目重写
【题目内容】
# [ABC277C] Ladder Takahashi

## 题目描述

有一座很高的楼，你现在在第一层。

有 $n$ 个传送门，每个传送门连接第 $a_i$ 层与第 $b_i$ 层。传送门是双向的。

请你求出你能到达的最高楼层。

## 说明/提示

$1 \le n \le 2 \times 10^5$

$1 \le a_i, b_i \le 10^9$

保证 $a_i \ne b_i$。

## 样例 #1

### 输入

```
4

1 4

4 3

4 10

8 3```

### 输出

```
10```

## 样例 #2

### 输入

```
6

1 3

1 5

1 12

3 5

3 12

5 12```

### 输出

```
12```

## 样例 #3

### 输入

```
3

500000000 600000000

600000000 700000000

700000000 800000000```

### 输出

```
1```

### 算法分类
图论、广度优先搜索（BFS）、离散化

### 题解分析与结论
本题的核心是找到从第1层出发，通过传送门能够到达的最高楼层。由于楼层数可能非常大（$10^9$），直接使用数组存储会超出内存限制，因此需要使用离散化或映射来减少存储空间。大多数题解采用了广度优先搜索（BFS）或深度优先搜索（DFS）来遍历所有可达的楼层，并使用`map`或离散化来处理大范围的楼层编号。

### 高星题解推荐
1. **作者：Strelitzia_ (4星)**
   - **关键亮点**：使用`map`进行楼层编号的映射，避免了直接存储大范围楼层编号的问题。采用BFS进行遍历，代码简洁且易于理解。
   - **核心代码**：
     ```cpp
     map<int, int> id, val;
     int idd;
     struct T {
         int to, nxt;
     } e[N];
     int head[N], hop, n, m, ans;
     bool vis[N];
     void addd(int to, int nxt) {
         e[++hop].to = nxt;
         e[hop].nxt = head[to];
         head[to] = hop;
     }
     queue<int> q;
     signed main() {
         n = read();
         for (int i = 1; i <= n; i++) {
             int to = read(), nxt = read();
             if (!id.count(to)) id[to] = ++idd, val[idd] = to;
             if (!id.count(nxt)) id[nxt] = ++idd, val[idd] = nxt;
             addd(id[to], id[nxt]);
             addd(id[nxt], id[to]);
         }
         if (!id.count(1)) return puts("1"), Strelitzia_H;
         q.push(id[1]);
         while (!q.empty()) {
             int u = q.front();
             q.pop();
             if (vis[u]) continue;
             vis[u] = 1;
             for (int i = head[u]; i; i = e[i].nxt)
                 if (!vis[e[i].to]) q.push(e[i].to);
         }
         for (int i = 1; i <= idd; i++) {
             if (vis[i]) ans = max(ans, val[i]);
         }
         printf("%lld", ans);
         return Strelitzia_H;
     }
     ```

2. **作者：RainSpark (4星)**
   - **关键亮点**：使用链式前向星建图，并结合`map`进行楼层编号的映射。采用DFS进行遍历，代码结构清晰，时间复杂度为$O(N \log{N})$。
   - **核心代码**：
     ```cpp
     map<int,int> head;
     int num_edge;
     void add(int from,int to){
         num_edge++;
         edge[num_edge].nxt=head[from];
         edge[num_edge].to=to;
         head[from]=num_edge;
     }
     int n,ans=1;
     map<int,bool> vis;
     void dfs(int x){
         ans=max(ans,x);
         for(int i=head[x];i;i=edge[i].nxt){
             int j=edge[i].to;
             if(!vis[j]){ vis[j]=1; dfs(j);}
         }
     }
     int main(){
         scanf("%d",&n);
         for(int i=1,a,b;i<=n;i++){
             scanf("%d %d",&a,&b);
             add(a,b);add(b,a);
         }
         dfs(1);
         printf("%d\n",ans);
         return 0;
     }
     ```

3. **作者：LaDeX (4星)**
   - **关键亮点**：采用离散化处理大范围楼层编号，结合BFS进行遍历。代码结构清晰，且离散化处理得当，适合处理大范围数据。
   - **核心代码**：
     ```cpp
     map<LL, LL> mp1, mp2;
     vector<LL> g[N * 10];
     set<LL> vis;
     queue<LL> q;
     int main(){
         Fcin;
         cin >> n;
         LL v, w;
         mp1[1] = 1;
         mp2[1] = 1;
         for (LL i = 1; i <= n; i ++){
             cin >> input[i][1] >> input[i][2];
             tmp[++ len].x = input[i][1];
             tmp[len].k = input[i][1];
             tmp[++ len].x = input[i][2];
             tmp[len].k = input[i][2];
         }
         sort(tmp + 1, tmp + 1 + len);
         for (LL i = 1; i <= len; i ++){
             if (!mp1.count(tmp[i].k)){
                 mp1[tmp[i].k] = i + 1;
                 mp2[i + 1] = tmp[i].k;
             }
         }
         for (LL i = 1; i <= n; i ++){
             v = mp1[input[i][1]], w = mp1[input[i][2]];
             g[v].emplace_back(w);
             g[w].emplace_back(v);
         }
         q.push(1);
         vis.insert(1);
         while (!q.empty()){
             LL now = q.front(); q.pop();
             ans = max(ans, now);
             for (LL to : g[now]){
                 if (!vis.count(to)){
                     vis.insert(to);
                     q.push(to);
                 }
             }
         }
         cout << mp2[ans];
         return 0;
     }
     ```

### 最优关键思路与技巧
1. **离散化**：由于楼层编号范围极大，使用离散化或`map`进行映射，减少存储空间。
2. **BFS/DFS**：通过广度优先搜索或深度优先搜索遍历所有可达的楼层，记录最大值。
3. **链式前向星**：使用链式前向星建图，适合处理稀疏图，节省空间。

### 可拓展之处
- **类似题目**：可以扩展到其他需要处理大范围数据的图论问题，如最短路径、连通性问题等。
- **优化思路**：在处理大范围数据时，可以考虑使用更高效的数据结构，如哈希表、并查集等。

### 推荐题目
1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
2. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)
3. [P3916 图的遍历](https://www.luogu.com.cn/problem/P3916)

---
处理用时：51.55秒