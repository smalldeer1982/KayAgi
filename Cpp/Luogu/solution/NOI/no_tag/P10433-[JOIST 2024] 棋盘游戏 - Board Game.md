# [JOIST 2024] 棋盘游戏 / Board Game

## 题目描述

有一个供 $K$ 个玩家玩的棋盘游戏。该游戏的棋盘由 $N$ 个编号从 1 到 $N$ 的单元格和 $M$ 条编号从 1 到 $M$ 的路径组成，其中路径 $j$（$1 ≤ j ≤ M$）双向连接着单元格 $U_j$ 和 $V_j$。

棋盘上有两种类型的单元格：重新激活单元格和停止单元格。

这些信息由长度为 $N$ 的字符串 $S$ 给出，$S$ 由 $0$ 和 $1$ 组成，其中 $S$ 的第 $i$ 个字符（$1 ≤ i ≤ N$）是 '0' 表示单元格 $i$ 是重新激活单元格，是 '1' 表示单元格 $i$ 是停止单元格。

这个棋盘游戏由编号从 $1$ 到 $K$ 的 $K$ 个玩家进行。每个玩家都有自己的棋子，游戏从每个玩家将其棋子放在特定的单元格上开始。一开始，玩家 $p$（$1 \leq p \leq K$）将其棋子放在单元格 $X_p$ 上。注意，多个玩家的棋子可以放在同一个单元格上。

游戏随着每个玩家轮流进行而进行，从玩家 1 开始，按数字顺序进行。在玩家 $p$ 完成其回合后，玩家 $p + 1$ 开始回合（如果 $p = K$，则玩家 1 开始回合）。每个玩家在其回合上执行以下操作：

1. 选择与其棋子所在的单元格通过一条路径相连的一个单元格，并将其棋子移动到所选择的单元格上。
2. 如果目标单元格是重新激活单元格，则重复步骤 1 并继续其回合。如果目标单元格是停止单元格，则结束其回合。

代表日本参加这个棋盘游戏的包括 JOI 君在内的由 $K$ 名成员组成的团队，正在研究协作策略，以快速征服这个游戏。他们目前正在研究以下问题：

为了将玩家 1 的棋子放置在单元格 $T$ 上，$K$ 名玩家需要的最小总移动次数是多少？即使在回合中途，如果玩家 1 的棋子被放置在单元格 $T$ 上，也认为满足条件。

给定关于游戏棋盘和每个玩家棋子的初始放置位置的信息，编写一个程序来计算每个 $T = 1, 2, \ldots, N$ 对应的问题的答案。

## 说明/提示

#### 样例解释 1

由于玩家 $1$ 的棋子从单元格 $1$ 开始，所以 $T = 1$ 的答案是 $0$。

对于 $T = 2$，在第一步中，玩家 $1$ 可以将他的棋子从单元格 $1$ 移动到单元格 $2$。因此，$T = 2$ 的答案是 $1$。

对于 $T = 3$，他们可以通过以下 $2$ 步将玩家 $1$ 的棋子放置在单元格 $3$ 上：

- 在第一步中，玩家 $1$ 将他的棋子从单元格 $1$ 移动到单元格 $2$。由于单元格 $2$ 是一个激活单元格，因此玩家 $1$ 的回合继续。
- 在第二步中，玩家 $1$ 将他的棋子从单元格 $2$ 移动到单元格 $3$。

由于他们无法在 $1$ 步或更少的步骤中将玩家 $1$ 的棋子放置在单元格 $3$ 上，所以 $T = 3$ 的答案是 $2$。

类似地，可以验证 $T = 4$ 的答案为 $2$，$T = 5$ 的答案为 $3$。

这个样例输入满足子任务 $1,4,5,6,7,8$ 的约束。



#### 样例解释 2

对于 $T = 3$，他们可以通过以下 4 步将玩家 $1$ 的棋子放置在单元格 $3$ 上：

- 在第一步中，玩家 $1$ 将他的棋子从单元格 $1$ 移动到单元格 $2$。由于单元格 $2$ 是一个停止单元格，接下来轮到玩家 $2$。
- 在第二步中，玩家 $2$ 将他的棋子从单元格 $5$ 移动到单元格 $3$。由于单元格 $3$ 是一个激活单元格，玩家 $2$ 的回合继续。
- 在第三步中，玩家 $2$ 将他的棋子从单元格 $3$ 移动到单元格 $2$。由于单元格 $2$ 是一个停止单元格，接下来轮到玩家 $1$。
- 在第四步中，玩家 $1$ 将他的棋子从单元格 $2$ 移动到单元格 $3$。

由于他们无法在 $3$ 步或更少的步骤中将玩家 $1$ 的棋子放置在单元格 $3$ 上，所以 $T = 3$ 的答案是 $4$。

这个样例输入满足子任务 $2,4,5,6,7,8$ 的约束。

#### 样例解释 3

这个样例输入满足子任务 $3, 4, 5, 6, 7,8$ 的约束。

#### 样例解释 4

这个样例输入满足子任务 $4, 6, 7,8$ 的约束。

#### 样例解释 5

这个样例输入满足子任务 $4, 6, 7,8$ 的约束。

### 约束条件

- $2 \leq N \leq 50,000$
- $1 \leq M \leq 50,000$
- $2 \leq K \leq 50,000$
- $1 \leq U_j < V_j \leq N$（$1 \leq j \leq M$）
- $(U_j, V_j)$，$(U_k, V_k)$（$1 \leq j < k \leq M$）
- 可以通过经过多条路径从任何单元格到达任何其他单元格。
- $S$ 是长度为 $N$ 的由 '0' 和 '1' 组成的字符串。
- $1 \leq X_p \leq N$（$1 \leq p \leq K$）
- $N$、$M$ 和 $K$ 都是整数。
- $U_j$ 和 $V_j$ 是整数（$1 \leq j \leq M$）。
- $X_p$ 是整数（$1 \leq p \leq K$）。

### 子任务

1. (3 分) 没有终止单元格。
2. (7 分) 恰好有一个终止单元格。
3. (7 分) 恰好有两个终止单元格。
4. (19 分) $N \leq 3,000$，$M \leq 3,000$，$K \leq 3,000$
5. (23 分) $K = 2$
6. (9 分) $K \leq 100$
7. (23 分) $N \leq 30,000$，$M \leq 30,000$，$K \leq 30,000$
8. (9 分) 没有额外的约束。



## 样例 #1

### 输入

```
5 5 2
1 2
2 3
2 4
3 5
4 5
00000
1 5```

### 输出

```
0
1
2
2
3```

## 样例 #2

### 输入

```
5 5 2
1 2
2 3
2 4
3 5
4 5
01000
1 5```

### 输出

```
0
1
4
4
5```

## 样例 #3

### 输入

```
5 5 2
1 2
2 3
2 4
3 5
4 5
01100
1 5
```

### 输出

```
0
1
3
3
4```

## 样例 #4

### 输入

```
8 7 5
1 3
5 7
4 6
2 6
2 3
7 8
1 5
10011010
4 6 4 7 1```

### 输出

```
4
2
3
0
10
1
17
24```

## 样例 #5

### 输入

```
12 13 3
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
1 10
2 9
7 12
11 12
110000011101
1 9 11
```

### 输出

```
0
1
4
5
6
7
8
8
4
1
13
9```

# 题解

## 作者：Petit_Souris (赞：13)

这个题太难了。思考时间至少得有 1.5h，代码和 debug 难度也很高。放到正式比赛场上我不可能通过。

### 最初的观察

我们现在需要最小化棋子 $1$ 走到点 $T$ 的时间，假设棋子 $1$ 经过了 $c$ 个终止节点，那么 $2\sim K$ 号棋子分别需要走 $c$ 次。这时候我们容易发现剩下的棋子是独立的，我们只需要分别最小化他们的步数。

由于这是一张无向图，我们容易发现可以有一种很好的策略：先走到一个终止节点，从第二次开始每次走出一步再走回来，这样除了第一回合以外，每个回合对答案的贡献为固定的 $2$。

但是我们发现这样不一定是最优的：我们可能可以走到两个相邻的终止节点中的一个，并在两个终止节点之间反复横跳，这样除了第一回合以外每个回合只贡献 $1$ 的答案。那么很容易想到走到最近的终止节点 / 相邻的一组终止节点并反复横跳。很可惜，这样并非完全正确——走到相邻的终止节点的路径上可能有其他的终止节点。

### 巧妙的补丁

我们分析一下走到一组相邻终止节点的路径情况：假设路径上经过了 $c_1$ 个终止节点，路径长度为 $d$，而棋子 $1$ 总共经过了 $c$ 个终止节点，那么实际上贡献为 $d+c-c_1$。那么有个很简单的修补方式：将终止节点赋上 $-1$ 的权值，给边赋上 $1$ 的权值，这样跑 01 bfs。

你可能会好奇，这样为什么是对的？难道不会出现 $c_1>c$ 的路径被计算的情况吗？很容易分析出这种情况下，如果前 $c$ 个点中就已经有一对相邻点的，那么停在那个位置是更优的，否则如果不存在，每走一步，$d$ 增加至少 $2$，而 $c_1$ 只会增加 $1$，因此只会更劣。

### 问题的开端

现在 $2\sim K$ 每个棋子的代价可以被表示为 $\min(c+f_1,2c+f_2)$ 的形式。那么对于每个 $c$，剩下棋子的代价容易被计算出来（找出分段点，使用前缀和计算），是一个关于 $c$ 的函数 $F(c)$。

现在我们的问题清晰许多了：对于一条 $X_1\to T$ 的路径，如果长度为 $D$，经过了 $c$ 个终止节点，那么答案为 $\min(D+F(c))$。

在繁琐的分析之后我们之后得出了多项式时间复杂度的做法：记录当前的 $c$ 跑最短路，时间复杂度为 $\mathcal O(n^2)$。

### 最终的一击

考虑优化。我们发现当 $K$ 比较大的时候，我们肯定倾向于控制 $c$ 不要太大，因为 $c$ 一旦增加 $1$，代价至少会增加 $K-1$。我们容易分析得到，设 $X_1\to T$ 最少需要经过 $x$ 个终止节点，最优解经过了 $y$ 个终止节点，那么 $y-x$ 是 $\mathcal O(\frac{n}{K})$ 级别的。我们轻松把上面的做法优化到了 $\mathcal O(\frac{n^2}{K})$。

既然除以 $K$ 的字眼都出来了，再结合上部分分，最后一击只能是根号分治了。最后的最后，我们思考一下如何解决 $K$ 较小的情况。

容易发现 $F$ 这个函数是上凸的，且段数是 $\mathcal O(K)$ 级别的，因此我们可以取出这 $\mathcal O(K)$ 段线段并求解。如果我们将这条线段延申成直线，那么问题就好做了：把贡献拆到转移点上直接跑最短路。稍微分析一下就容易发现这样不可能把答案算小，且要算的答案肯定已经计算进去了。于是这部分是时间复杂度为 $\mathcal O(nK\log n)$。

平衡两边复杂度，取 $K=\mathcal O(\frac{\sqrt{n\log n}}{\log n})$，得到时间复杂度为 $\mathcal O(n\sqrt {n\log n})$。

代码细节相当繁琐。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=5e4+9,INF=1e12;
ll n,m,K,X[N],tod[2][N],tag[N],md[N],cst[N];
vector<ll>to[N];
char s[N];
void run1(){
    queue<ll>q;
    rep(i,0,n)tod[0][i]=-1;
    rep(i,1,n){
        if(s[i]=='1'){
            for(ll j:to[i])q.push(j),tod[0][j]=1;
        }
    }
    rep(i,1,n){
        if(~tod[0][i])q.push(i);
    }
    while(!q.empty()){
        ll u=q.front();q.pop();
        for(ll v:to[u]){
            if(!~tod[0][v]){
                tod[0][v]=tod[0][u]+1;
                q.push(v);
            }
        }
    }
}
void run2(){
    deque<ll>q;
    rep(i,0,n)tod[1][i]=-1;
    rep(i,1,n){
        if(tag[i]){
            for(ll j:to[i])tod[1][j]=1;
        }
    }
    rep(i,1,n){
        if(~tod[1][i])q.push_back(i);
    }
    while(!q.empty()){
        ll u=q.front();q.pop_front();
        for(ll v:to[u]){
            if(s[u]=='1'){
                if(!~tod[1][v]||tod[1][v]>tod[1][u])tod[1][v]=tod[1][u],q.push_front(v);
            }
            else {
                if(!~tod[1][v]||tod[1][v]>tod[1][u]+1)tod[1][v]=tod[1][u]+1,q.push_back(v);
            }
        }
    }
}
void run3(){
    rep(i,0,n)md[i]=INF;
    md[X[1]]=0;
    queue<ll>q;
    q.push(X[1]);
    while(!q.empty()){
        ll u=q.front();q.pop();
        if(u!=X[1]&&s[u]=='1')continue;
        for(ll v:to[u]){
            if(md[v]>md[u]+1){
                md[v]=md[u]+1;
                q.push(v);
            }
        }
    }
}
namespace S1{
    ll minc[N],f[N][505];
    void solve(){
        rep(i,1,n)minc[i]=INF;
        deque<ll>q;
        q.push_back(X[1]);
        minc[X[1]]=0;
        while(!q.empty()){
            ll u=q.front();q.pop_front();
            for(ll v:to[u]){
                ll w=(s[u]=='1'&&u!=X[1]);
                if(minc[v]>minc[u]+w){
                    minc[v]=minc[u]+w;
                    if(!w)q.push_front(v);
                    else q.push_back(v);
                }
            }
        }
        rep(i,0,n){
            rep(j,0,min(500ll,n/K))f[i][j]=INF;
        }
        queue<pii>q1;
        f[X[1]][0]=0;
        q1.push({X[1],0});
        while(!q1.empty()){
            pii now=q1.front();q1.pop();
            ll u=now.first,i=now.second;
            for(ll v:to[u]){
                ll j=minc[u]+i-minc[v]+(u!=X[1]&&s[u]=='1');
                if(j<=min(500ll,n/K)){
                    if(f[v][j]>f[u][i]+1)f[v][j]=f[u][i]+1,q1.push({v,j});
                }
            }
        }
        rep(i,1,n){
            ll ans=md[i];
            rep(j,0,min(500ll,n/K))ans=min(ans,f[i][j]+cst[minc[i]+j]);
            write(ans),putchar('\n');
        }
    }
}
namespace S2{
    ll dis[N][2],ans[N];
    bool ok[N][2];
    struct Node{
        ll u,tp,d;
        bool operator<(const Node&a)const{return d>a.d;}
    };
    void dijk(ll k,ll sp){
        priority_queue<Node>q;
        rep(i,0,n+1){
            rep(j,0,1)dis[i][j]=INF,ok[i][j]=0;
        }
        dis[X[1]][0]=0;
        q.push({X[1],0,0});
        while(!q.empty()){
            Node now=q.top();q.pop();
            ll u=now.u,tp=now.tp;
            if(ok[u][tp])continue;
            ok[u][tp]=1;
            for(ll v:to[u]){
                ll w=1+k*(u!=X[1]&&s[u]=='1');
                ll ntp=tp||(u!=X[1]&&s[u]=='1');
                if(dis[v][ntp]>dis[u][tp]+w){
                    dis[v][ntp]=dis[u][tp]+w;
                    q.push({v,ntp,dis[v][ntp]});
                }
            }
        }
        rep(i,1,n)ans[i]=min(ans[i],sp+dis[i][1]);
    }
    void solve(){
        rep(i,1,n)ans[i]=md[i];
        rep(i,2,n){
            if(i==n||cst[i]*2!=cst[i-1]+cst[i+1])dijk(cst[i]-cst[i-1],cst[i]-(cst[i]-cst[i-1])*i);
        }
        rep(i,1,n)write(ans[i]),putchar('\n');
    }
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),m=read(),K=read();
    rep(i,1,m){
        ll x=read(),y=read();
        to[x].push_back(y);
        to[y].push_back(x);
    }
    scanf("%s",s+1);
    rep(i,1,K)X[i]=read();
    rep(i,1,n){
        if(s[i]=='1'){
            for(ll j:to[i]){
                if(s[j]=='1')tag[i]=1;
            }
        }
    }
    run1(),run2(),run3();
    if(!count(s+1,s+n+1,'1')){
        rep(i,1,n)write(md[i]),putchar('\n');
        return 0;
    }
    rep(i,2,K){
        cst[2]+=2;
        if(~tod[1][X[i]])cst[tod[1][X[i]]-tod[0][X[i]]+2]--;
    }
    rep(i,2,n)cst[i]+=cst[i-1];
    rep(i,2,K)cst[1]+=tod[0][X[i]];
    rep(i,2,n)cst[i]+=cst[i-1];
    if(K>=100)S1::solve();
    else S2::solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：7)

[Problem Link](https://www.luogu.com.cn/problem/P10433)

**题目大意**

> 给定 $n$ 个点 $m$ 条边的无向图，有一些节点是“停止节点”，现在有 $k$ 枚棋子初始放在 $a_1\sim a_k$。
>
> 游戏会进行若干轮，每轮依次考虑第 $1\sim k$ 枚棋子，并将其在图上移动到某个“停止节点”停下（不能不动）。
>
> 对于每个 $u\in[1,n]$，求把第 $1$ 枚棋子移动到 $u$ 上，所有棋子移动距离和的最小值。
>
> 数据范围：$n,m,k\le 5\times 10^5$。

**思路分析**

我们发现第 $2\sim k$ 枚棋子对答案的影响很小，且他们相互独立，这些棋子只要分别最小化移动距离即可。

假设我们钦定进行了 $x$ 轮移动，我们就要求出每个棋子最小移动距离关于 $x$ 的函数 $f(x)$。

注意到这个棋子第一轮移动到某个“停止节点”后，接下来的每一轮都可以直接走到某个邻居再走回来，因此每轮至多走 $2$ 步。

设这个棋子第一轮至少移动 $d$ 步到“停止节点”，那么进行 $x$ 轮移动的代价不超过 $2x+d-2$。

如果想要更优，那就必须要做到每轮移动只走一步，也就是走到两个相邻的“停止节点”上。

对于所有的走到相邻“停止节点”的路径，我们关心其长度 $w$ 和轮数 $t$，那么 $x\ge t$ 时存在一种代价为 $x-t+w$ 的路径。

我们发现 $x<t$ 的时候 $x-t+w$ 不可能小于 $2x+d-2$，因此我们只关心 $w-t$ 最小的路径即可。

>证明：只需要证明 $w-1\ge 2t+d-4$，即 $w-2t\ge d-3$。
>
>考虑 $(w,t)$ 对应路径，由于其终点是第一对相邻的“停止节点”，因此此前路径上的的每个“停止节点”的邻域都没有“停止节点”。
>
>那么路径上这 $t$ 个“停止节点”，在路径上经过的下一个点肯定不是停止节点，因此可以将这 $2t$ 个点取出。
>
>并且考虑 $d'$ 表示这条路径上第一次到达“停止节点”前的长度，那么我们在这条长度为 $w$ 的路径上删去 $2t$ 个点的贡献，并不影响 $d'$ 中点的贡献。
>
>因此我们知道 $d'\le w-2t$，且 $d'$ 也对应一条走到“停止节点”的路径，故 $d'\ge d$，因此 $w-2t\ge d$。

求出 $w-t$ 最小的路径，可以看成给终止节点的权值设为 $0$，其他点权值设为 $1$ 时的最短路，可以 01bfs。

容易发现其他时候肯定不优，此时我们表示出了 $f(x)=\min(2x+d-2,x-t+w)$，可以看成一个分两段的上凸壳。

因此对于每个 $x$，所有棋子的贡献总和是一个分段函数 $F(x)$，且其段数 $\le k$，而且是上凸壳。

那么一个朴素的想法就是对于每个 $u,x$，求出 $a_1$ 走到 $u$ 恰好经过 $x$ 轮的最短路 $d_{u,x}$，用 $d_{u,x}+F(x)$ 更新答案。

但这样做的复杂度难以接受，根据贪心的思想，我们自然想到求出经过轮数最小的一条路径，但这不对，因为我们可以略微增加经过的轮数，但使得路径长度减小。

但是这样路径长度减小量肯定是 $\le n$ 的，因为原路径长度肯定不超过 $n$。

那么我们发现轮数很大的情况并不优，因为每多走一轮，其他的 $k-1$ 个棋子至少都要动一步，因此每增加一轮，$F(x)$ 至少增加 $k-1$。

 那么 $\dfrac{n}{k-1}$ 轮后，我们就不可能获得比最小轮数路径更优的决策。

因此我们可以分层图 bfs，时间复杂度 $\mathcal O\left(\dfrac{nm}k\right)$。

那么 $k$ 很大的情况得到解决，我们只要考虑 $k$ 较小的情况。

我们枚举凸壳上的每条边，设其在 $x\in[l,r]$ 时 $F(x)=px+b$，那么这条边的斜率 $p$ 就相当于：如果轮数落在这条边的横坐标区间内，那么可以把移动 $x$ 轮的代价看成 $p\times x$。

我们枚举 $p$，然后把增加一轮（棋子经过“停止节点”）的代价额外 $+p$，在这种情况下求出最短路 $d_u$。

观察最短路径此时经过的轮数，如果这个轮数恰好落在 $[l,r]$ 内，那么这显然就是答案，用 $d_u+b$ 更新 $u$ 的答案即可。

如果这个轮数落在 $[l,r]$ 外，那么很显然，$d_u+b$ 不可能成为答案，因为此时 $px+b>F(x)$，所以取 $F(x)$ 实际对应的决策一定更优。

因此我们知道答案就是所有 $p$ 对应的 $d_u+b$ 的最小值。

由于凸包只有 $\mathcal O(k)$ 段，对每段跑 Dijkstra，可以做到 $\mathcal O(km\log m)$ 的复杂度。

对 $k$ 进行根号平衡即可。

时间复杂度 $\mathcal O(m\sqrt{n\log m})$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=5e4+5,inf=1e9,LIM=225;
int n,m,st[MAXN],cl[MAXN];
vector <int> G[MAXN];
int w1[MAXN],w2[MAXN];
ll ans[MAXN];
void bfs1() { //ans from x[1] without stop
	memset(ans,0x3f,sizeof(ans));
	queue <int> q; q.push(st[1]),ans[st[1]]=0;
	while(q.size()) {
		int u=q.front(); q.pop();
		if(u!=st[1]&&cl[u]) continue;
		for(int v:G[u]) if(ans[v]>n) ans[v]=ans[u]+1,q.push(v);
	}
}
void bfs2() { //min dis to first stop
	fill(w2+1,w2+n+1,inf);
	queue <int> q;
	for(int i=1;i<=n;++i) if(cl[i]) {
		for(int j:G[i]) if(w2[j]==inf) w2[j]=1,q.push(j);
	}
	while(q.size()) {
		int u=q.front(); q.pop();
		for(int v:G[u]) if(w2[v]==inf) w2[v]=w2[u]+1,q.push(v);
	}
}
void bfs3() { //min dis to 2 connected stops
	deque <int> q;
	fill(w1+1,w1+n+1,inf);
	for(int i=1;i<=n;++i) if(cl[i]&&w2[i]==1) w1[i]=0,q.push_back(i);
	static bool vis[MAXN];
	fill(vis+1,vis+n+1,false);
	while(q.size()) {
		int u=q.front(); q.pop_front();
		if(vis[u]) continue; vis[u]=true;
		int d=w1[u]+1-cl[u];
		for(int v:G[u]) if(w1[v]>d) {
			w1[v]=d;
			if(cl[u]) q.push_front(v);
			else q.push_back(v);
		}
	}
}
namespace A {
int lim,rd[MAXN],d[MAXN][MAXN/LIM+5];
ll f[MAXN],sum=0;
void bfs4() { //min rounds to every vertex
	fill(rd+1,rd+n+1,inf);
	deque <int> q;
	q.push_back(st[1]),rd[st[1]]=0;
	static bool vis[MAXN];
	fill(vis+1,vis+n+1,false);
	while(q.size()) {
		int u=q.front(); q.pop_front();
		if(vis[u]) continue; vis[u]=true;
		int z=cl[u]&&u!=st[1];
		for(int v:G[u]) if(rd[v]>rd[u]+z) {
			rd[v]=rd[u]+z;
			z?q.push_back(v):q.push_front(v);
		}
	}
}
void bfs5() { //shortest path to vertex at round d0[u]+i
	for(int i=1;i<=n;++i) fill(d[i],d[i]+lim+5,inf);
	queue <array<int,2>> q;
	q.push({st[1],0}),d[st[1]][0]=0;
	while(q.size()) {
		int u=q.front()[0],i=q.front()[1]; q.pop();
		int z=cl[u]&&d[u][i]>0;
		for(int v:G[u]) {
			int j=i+rd[u]+z-rd[v];
			if(j<=lim&&d[v][j]==inf) d[v][j]=d[u][i]+1,q.push({v,j});
		}
	}
}
void main() {
	lim=n/(m-1),f[1]=2*m-2;
	for(int i=2;i<=m;++i) {
		ll s=w1[st[i]],t=w2[st[i]]-2; //x+s or 2x+t
		if(s!=inf) --f[s-t+1];
		sum+=t;
	}
	for(int i=1;i<=n;++i) f[i]+=f[i-1];
	for(int i=1;i<=n;++i) f[i]+=f[i-1];
	bfs4(),bfs5(),f[0]=-sum;
	for(int i=1;i<=n;++i) for(int j=0;j<=lim;++j) if(d[i][j]!=inf&&j+rd[i]<=n) {
		ans[i]=min(ans[i],d[i][j]+f[j+rd[i]]+sum);
	}
}
}
namespace B {
int x[MAXN]; //change slope
bool vis[MAXN],chk[MAXN]; //round>1
ll dis[MAXN];
void dijk(int k) {
	memset(dis,0x3f,sizeof(dis));
	memset(vis,false,sizeof(vis));
	memset(chk,false,sizeof(chk));
	priority_queue <array<ll,2>,vector<array<ll,2>>,greater<array<ll,2>>> q;
	q.push({dis[st[1]]=0,st[1]});
	while(q.size()) {
		int u=q.top()[1]; q.pop();
		if(vis[u]) continue; vis[u]=true;
		int z=(cl[u]&&u!=st[1])?k+1:1;
		for(int v:G[u]) if(dis[v]>dis[u]+z) {
			q.push({dis[v]=dis[u]+z,v});
			chk[v]=chk[u]|(z>1);
		}
	}
}
void main() {
	ll sum=0;
	for(int i=2;i<=m;++i) {
		int s=w1[st[i]],t=w2[st[i]]-2;
		x[i-1]=s-t+1,sum+=t;
	}
	x[0]=0,x[m]=n,sort(x,x+m+1);
	for(int i=0;i<m&&x[i]<n;++i) {
		if(i) sum+=x[i]-1;
		if(x[i+1]==x[i]) continue;
		dijk(2*m-2-i);
		for(int u=1;u<=n;++u) if(vis[u]&&chk[u]) ans[u]=min(ans[u],dis[u]+sum);
	}
}
}
signed main() {
	int E;
	scanf("%d%d%d",&n,&E,&m);
	for(int u,v;E--;) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	for(int i=1;i<=n;++i) scanf("%1d",&cl[i]);
	for(int i=1;i<=m;++i) scanf("%d",&st[i]);
	bfs1(),bfs2(),bfs3();
	if(m>LIM) A::main();
	else B::main();
	for(int i=1;i<=n;++i) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：basince (赞：2)

$\color{red}\tt\text{orz qbf!!!}$

下文的游戏轮数指的是棋子 $2\sim K$ 进行的游戏轮数。

首先将棋 $1$ 与棋 $2\sim K$ 分开考虑。

棋 $1$ 的贡献是简单的，关键在于怎么计算棋 $2\sim K$ 的贡献。

容易发现棋子 $2\sim K$ 在经过第 $1$ 轮后就可以每轮只花费 $2$ 步（跳向激活点再跳回来）或 $1$ 步（跳向停止点）。

所以说我们需要关心：

1. 游戏轮数。
2. 棋 $2\sim K$ 是否去到存在相邻点为停止点的停止点。

容易得到一个 $O(n(m+K))$ 的解法。即在最短路过程中记录轮数 $j$。统计答案时枚举游戏轮数，看棋 $2\sim K$ 去到相邻的停止点是否更优，依次贡献答案。

上面这个解法的弊病就在于，我们需要判断一个棋到相邻的停止点的轮数是否 $\ge$ 当前枚举的轮数，这意味着我们在求棋 $1$ 到其他点最短路时**必须记录轮数**，这样复杂度总会带一个 $O(nm)$，我们要尝试让棋 $2\sim K$ 的贡献不依赖轮数的比较。

观察到棋 $2\sim K$ 的贡献类似一个分段函数 $\min(d_0+2x,d_1-c+x)$，不难想到在跑到相邻的停止点的最短路时每遇到一个停止点就将贡献 $-1$，这样到最后就可以表示成一次函数。易证当 $x<c$ 时总有 $d_1-x+1\ge d_0+2x$，所以我们可以直接把贡献看成一个分段函数。

数据范围很好的提示了我们可以根号分治。发现当 $K$ 比较大时，游戏每多进行一轮，棋 $2\sim K$ 就至少贡献 $K-1$，这样很不划算。设游戏至少进行 $x$ 轮，则容易得到最优轮数应该在 $x\sim x+O(\frac nk)$。

那么此时直接跑暴力就可以了，这样我们就得到了一个 $O(\frac{n^2}{K})$ 的算法。

对于 $K$ 比较小的情况，我们发现如果把棋 $2\sim K$ 的贡献函数加起来得到的分段函数只有 $O(K)$ 段。由于它是上凸的，所以我们可以枚举每一段，强制棋 $2\sim K$ 的贡献的斜率都和这段一样，就可以把棋 $2\sim K$ 的贡献放到棋 $1$ 跑最短路的过程中，不难发现最优解一定被涵盖了。这部分时间复杂度 $O(nK\log n)$。

平衡后的复杂度即为 $O(n\sqrt{n\log n})$。

---

## 作者：KingPowers (赞：1)

给一个复杂度稍劣，但是代码无敌好写而且实际运行效率非常优秀的做法。

事实上思路来自 Alan_Zhao 老师的讲课课件，但我还并没有在别的地方看到这个做法。

下文中称黑点为停止点，其它点为白点。前面的分析其实和其它题解做法都一样，想省流可以直接跳到最后求所有 $F(u)$ 的部分。

首先进行一点简单的分析，每个玩家的移动策略是完全独立的，也就是说除了第一个玩家其它人只需要最小化自己每轮的移动步数之和就可以了。容易发现策略其实只有两种：

- 移动到最近的一个黑点上去，以后每轮花费两步选一个邻居走过去再回来。
- 移动到一个邻居有黑点且自己是黑点的点上去，以后每轮在这两个黑点之间移动，每轮花费一步。

将从 $u$ 出发走 $x$ 轮的最小步数记为一个函数 $f_u(x)$，可以发现我们肯定是轮数小的时候用第一种策略，轮数大的时候用第二种策略。所以 $f_u(x)$ 的图像长成两段一次函数，第一段斜率为 $2$，第二段斜率为 $1$。

那是不是求出离每个点最近的黑点/一对相邻黑点，就能求出每个点对应的分段函数具体是啥了？并不是，注意使用第二种策略时路径上可能会有其它黑点，那咋办。再冷静分析一下，假如一条这种路径长度为 $d$，上面的黑点个数为 $c$，我们可以直接认为轮数为 $t$ 时这条路径的步数为 $d+t-c$。

为什么呢？如果 $t\ge c$ 这么算没问题，但是 $t<c$ 呢？由于此时路径上一定没有其它相邻黑点，发现这个式子只会把距离算大，那这时候用第一种策略的式子计算就能保证不会算错了。所以对第二种策略，我们只需要找到一条到某对相邻黑点的路径使得 $d-c$ 最小，可以把边权设为 $1$ 并给黑点带上 $-1$ 的点权 BFS 得到。

现在我们可以表示出 $f_u(x)=\min(x+b_1,2x+b_2)$。考虑设 $g(x)=\sum f_u(x)$（对除了第一个玩家外每个玩家的起始点 $u$ 求和），由于凸函数相加还是凸函数，所以 $g(x)$ 的图像会是上凸的。容易提前使用二阶差分快速预处理出来每个 $g(x)$ 的值。如果我们记 $d(u,k)$ 表示从第一个玩家的起始点出发，走到过 $k$ 个黑点时到 $u$ 的最短路，则答案 $F(u)=\min_{k=0}^n(d(u,k)+g(k))$。

为了求出所有的 $F(u)$，考虑从第一个玩家的起始点出发，执行一个类似 SPFA 的过程。具体来说开一个队列，队列内存储若干状态 $(u,k,d)$ 表示当前走到了 $u$，走到过 $k$ 个黑点，路径长度为 $d$。取出一个状态时，枚举 $u$ 的一个邻居 $v$ 并尝试用 $d+1+g(k)$ 去更新 $F(v)$，如果更新成功了就把新的状态加入队列。

看上去非常暴力，但是提交上去发现直接通过了本题，而且跑得飞快，这里是[提交记录](https://www.luogu.com.cn/record/229653952)。

这样做的复杂度也许确实是对的。观察 $F(u)$ 的表达式，发现对于用来更新它的若干 $(k,d)$，只有在下凸壳上的点才可能更新成功。坐标系大小是 $O(n)$ 的，所以凸壳上的点数也就只有 $O(n^{\frac{2}{3}})$，那每个点在 SPFA 中应该也只会被松弛这么多次，所以理论上这个做法的复杂度是 $O(n^{\frac{5}{3}})$？

代码显然非常好写。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
template<typename T>void cmax(T &x, T y){x = max(x, y);}
template<typename T>void cmin(T &x, T y){x = min(x, y);}
const int N = 1e5 + 5, inf = 1e18;
int n, m, k, c[N], st[N], ans[N];
int dis1[N], dis2[N], dif[N][2], f[N];
bool vis[N], inq[N], tag[N];
vector<int> e[N]; string s;
void bfs1(){
	fill(dis1 + 1, dis1 + n + 1, inf);
	queue<int> q;
	For(i, 1, n) if(c[i]) q.push(i), dis1[i] = 0;
	while(!q.empty()){
		int now = q.front(); q.pop();
		for(int to : e[now]){
			if(dis1[to] <= dis1[now] + 1) continue;
			dis1[to] = dis1[now] + 1;
			q.push(to);
		}
	}
}
void bfs2(){
	fill(dis2 + 1, dis2 + n + 1, inf);
	deque<int> q;
	For(i, 1, n) if(c[i]) for(int j : e[i]) tag[i] |= c[j];
	For(i, 1, n) if(tag[i]) dis2[i] = 0, q.push_back(i);
	while(!q.empty()){
		int now = q.front(); q.pop_front();
		if(vis[now]) continue;
		vis[now] = 1;
		for(int to : e[now]){
			int w = c[now] ? 0 : 1;
			if(dis2[to] <= dis2[now] + w) continue;
			dis2[to] = dis2[now] + w;
			if(!w) q.push_front(to);
			else q.push_back(to);
		}
	}
}
struct node{int u, k, d;};
void SPFA(){
	fill(ans + 1, ans + n + 1, inf);
	queue<node> q; ans[st[1]] = 0;
	q.push({st[1], 0, 0});
	while(!q.empty()){
		auto [u, k, d] = q.front();
		inq[u] = 0; q.pop();
		for(int v : e[u]){
			int cost = d + 1 + f[k];
			if(cost < ans[v]){
				ans[v] = cost;
				q.push({v, k + c[v], d + 1});
			}
		}
	}
}
void Solve(){
	cin >> n >> m >> k;
	For(i, 1, m){
		int u, v; cin >> u >> v;
		e[u].push_back(v); e[v].push_back(u);
	}
	cin >> s; s = ' ' + s;
	For(i, 1, n) c[i] = s[i] - '0';
	For(i, 1, k) cin >> st[i];
	bfs1(); bfs2();
	auto modify = [&](int l, int r, int k, int b){
		if(l > r) return; cmax(l, 0ll);
		dif[l][0] += b; dif[r + 1][0] -= b + k * (r - l + 1);
		dif[l][1] += k; dif[r + 1][1] -= k;
	};
	For(i, 2, k){
		int d1 = dis1[st[i]], d2 = dis2[st[i]];
		if(c[st[i]]) d1 = 2; int pos = d2 - d1 + 1;
		modify(1, min(pos, n), 2, d1 - 2);
		modify(pos + 1, n, 1, pos + d2);
	}
	For(i, 1, n) dif[i][0] += dif[i - 1][0], dif[i][1] += dif[i - 1][1];
	For(i, 1, n) dif[i][1] += dif[i - 1][1];
	For(i, 1, n) f[i] = dif[i][0] + dif[i][1];
	SPFA();
	For(i, 1, n) cout << ans[i] << '\n';
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int T = 1; //cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

