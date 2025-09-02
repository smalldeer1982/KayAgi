# 题目信息

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# AI分析结果

### 题目内容
#### Fox And Jumping
1. **题目描述**：Fox Ciel正在玩一个游戏。在这个游戏中有一条无限长的纸带，上面的格子由整数（正整数、负整数和零）索引。一开始她站在0号格子。
这里还有$n$张卡片，每张卡片有两个属性：长度$l_{i}$和花费$c_{i}$。如果她支付$c_{i}$美元，那么就可以使用第$i$张卡片。使用第$i$张卡片后，她就能够进行长度为$l_{i}$的跳跃，即从格子$x$跳到格子$(x - l_{i})$或格子$(x + l_{i})$。
她希望能够跳到纸带上的任何格子（可能需要经过一些中间格子）。为了实现这个目标，她想购买一些卡片，并且尽可能少地花钱。
如果这是可能的，计算最小花费。
2. **说明/提示**：在第一个样例测试中，购买一张卡片是不够的：例如，如果你购买一张长度为100的卡片，你无法跳到任何索引不是100倍数的格子。最好的方法是购买第一张和第二张卡片，这样你就能够跳到任何格子。
在第二个样例测试中，即使你购买所有卡片，你也无法跳到任何索引不是10的倍数的格子，所以你应该输出 -1。
3. **样例 #1**
    - **输入**：
```
3
100 99 9900
1 1 1
```
    - **输出**：
```
2
```
4. **样例 #2**
    - **输入**：
```
5
10 20 30 40 50
1 1 1 1 1
```
    - **输出**：
```
-1
```
5. **样例 #3**
    - **输入**：
```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```
    - **输出**：
```
6
```
6. **样例 #4**
    - **输入**：
```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```
    - **输出**：
```
7237
```

### 题解综合分析与结论
所有题解都基于裴蜀定理将问题转化为选择若干个$l_i$使得其最大公因数为1的最小代价问题。不同点在于后续的解法：
 - **状压DP**：利用数的质因数个数有限（$10^9$范围内数最多9个质因数）进行状压DP，通过枚举数及其状态来更新最小代价。时间复杂度$O(n^22^9)$ ，空间上可优化。
 - **基于map的DP**：设$f_x$为$\gcd$为$x$的最小代价，通过map记录状态并转移，时间复杂度上界$O(n\sum d(x))$，实际运行离上界较远。
 - **Dijkstra算法**：将问题看作从0号节点出发，通过$\gcd$转移节点并更新代价，用Dijkstra求最小代价，时间复杂度$O(n^2\log n)$ ，使用`unordered_map`解决数据大无法开数组记录的问题。

### 所选的题解
1. **作者：ZYF_B（5星）**
    - **关键亮点**：巧妙利用数的质因数特性进行状压DP，思路独特且复杂度清晰，代码实现简洁明了，对状压DP的应用有很好的示范作用。
    - **核心代码实现思想**：通过预处理每个数的质因数，利用状压记录质因数集合，枚举数和其状态进行转移更新最小代价。
    - **重点代码**：
```c++
int a[305],cost[305];
int g[305][10],cnt[305];
int f[1<<9];

int main()
{
    int n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) cost[i]=read();
    for(int i=1;i<=n;i++)
    {
        int x=a[i];
        for(int j=2;j*j<=x;j++)
            if(x%j==0)
            {
                g[i][++cnt[i]]=j;
                while(x%j==0) x/=j;
            }
        if(x>1) g[i][++cnt[i]]=x;
    }
    int ans=INF;
    for(int i=1;i<=n;i++)
    {
        memset(f,0x3f,sizeof(f));
        int M=1<<cnt[i];
        f[M-1]=cost[i];
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            int s=0;
            for(int k=1;k<=cnt[i];k++)
            {
                int flag=0;
                for(int x=1;x<=cnt[j];x++)
                    if(g[i][k]==g[j][x])
                    {
                        flag=1;
                        break;
                    }
                if(flag) s|=(1<<(k-1));
            }
            for(int k=0;k<M;k++)
                f[k&s]=min(f[k&s],f[k]+cost[j]);
        } 
        ans=min(ans,f[0]);
    }
    if(ans==INF) puts("-1");
    else printf("%d\n",ans);
    return 0;
}
```
2. **作者：Kohakuwu（4星）**
    - **关键亮点**：思路直接基于裴蜀定理转化问题，利用map优化传统DP，避免复杂的状态处理，代码简洁易懂，对map优化DP有很好的展示。
    - **核心代码实现思想**：通过map记录$\gcd$为某值时的最小代价，遍历卡片和已记录状态进行转移更新。
    - **重点代码**：
```cpp
map<int,int> mp;
int a[1003],b[1003];
signed main(){
    int n=read();
    for(int i=1; i<=n; i++) a[i]=read();
    for(int i=1; i<=n; i++) b[i]=read();
    for(int i=1; i<=n; i++) 
    {
        for(pair<int,int> x:mp)
        {
            int num=__gcd(a[i],x.first),val=x.second+b[i];
            if(mp[num]==0) mp[num]=val; else mp[num]=min(mp[num],val);
        }
        if(mp[a[i]]==0) mp[a[i]]=b[i];
        else mp[a[i]]=min(mp[a[i]],b[i]);
    }
    if(mp[1]==0) puts("-1");
    else printf("%d\n",mp[1]);
    return 0;
}
```
3. **作者：fanfansann（4星）**
    - **关键亮点**：从动态规划本质联系到图论最短路，将问题转化为图论模型并用Dijkstra算法求解，思路新颖，对不同算法间的联系有深入理解和应用。
    - **核心代码实现思想**：以0号节点为起点，通过$\gcd$转移节点，用Dijkstra算法更新到各节点的最小代价，`unordered_map`记录访问状态和距离。
    - **重点代码**：
```cpp
unordered_map<int, bool> vis;
unordered_map<int, ll> dist;

int n, m;
int head[N], ver[N], nex[N], edge[M], tot;
int a[N], l[N], c[N];

int gcd(int a, int b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}
//gcd(0,x) = x;
void dijkstra()
{
    priority_queue<PII, vector<PII>, greater<PII> > q;
    q.push({0, 0});
    dist[0] = 0;

    while(q.size()) {
        int x = q.top().second;
        q.pop();
        if(x == 1) break;

        if(vis.find(x)!= vis.end()) continue;
        vis[x] = true;
        for(int i = 1; i <= n; ++ i) {
            int y = __gcd(x, l[i]), z = c[i];
            if(dist.find(y) == dist.end()) dist[y] = INF;
            if(dist[y] > dist[x] + z) {
                dist[y] = dist[x] + z;
                q.push({dist[y], y});
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++ i)
        scanf("%d", &l[i]);

    for(int i = 1; i <= n; ++ i)
        scanf("%d", &c[i]);
    dijkstra();

    if(dist.find(1) == dist.end()) puts("-1");
    else printf("%lld\n", dist[1]);
    return 0;
}
```

### 最优关键思路或技巧
1. **状态压缩技巧**：如ZYF_B的题解，利用数的质因数个数有限进行状压DP，有效减少状态维度，降低时间和空间复杂度。
2. **数据结构优化DP**：Kohakuwu等人利用map记录状态，避免传统DP因状态空间大导致的时空问题，简化状态转移过程。
3. **算法转化**：fanfansann将DP问题转化为图论最短路问题，拓宽解题思路，利用成熟的图论算法解决问题。

### 同类型题或类似算法套路拓展
同类型题常围绕数论与DP或图论结合，例如给定一些数及其权值，求满足特定数论关系（如互质、最大公因数为某值等）的最小权值和。类似算法套路包括利用数论性质简化问题，结合DP、图论等算法求解。如本题利用裴蜀定理转化问题，再选择合适算法。

### 洛谷相似题目推荐
1. **P2152 [SDOI2009]SuperGCD**：涉及大整数的最大公因数计算，强化数论操作能力。
2. **P1072 [NOIP2009 提高组]  Hankson 的趣味题**：通过求解最大公因数和最小公倍数的关系，考察数论知识与枚举技巧。
3. **P2613 【模板】有理数取余**：结合数论中的逆元知识与基本运算，加深对数论在计算中应用的理解。 

---
处理用时：53.74秒