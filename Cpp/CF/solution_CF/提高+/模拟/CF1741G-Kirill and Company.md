# Kirill and Company

## 题目描述

Kirill lives on a connected undirected graph of $ n $ vertices and $ m $ edges at vertex $ 1 $ . One fine evening he gathered $ f $ friends, the $ i $ -th friend lives at the vertex $ h_i $ . So all friends are now in the vertex $ 1 $ , the $ i $ -th friend must get to his home to the vertex $ h_i $ .

The evening is about to end and it is time to leave. It turned out that $ k $ ( $ k \le 6 $ ) of his friends have no cars, and they would have to walk if no one gives them a ride. One friend with a car can give a ride to any number of friends without cars, but only if he can give them a ride by driving along one of the shortest paths to his house.

For example, in the graph below, a friend from vertex $ h_i=5 $ can give a ride to friends from the following sets of vertices: $ [2, 3] $ , $ [2, 4] $ , $ [2] $ , $ [3] $ , $ [4] $ , but can't give a ride to friend from vertex $ 6 $ or a set $ [3, 4] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1741G/5ddc6bf49e943e05aabc1f2d501a63e46c175460.png)The vertices where friends without cars live are highlighted in green, and with cars — in red.Kirill wants as few friends as possible to have to walk. Help him find the minimum possible number.

## 说明/提示

The first test case of the first example is explained in the statement.

In the second test case of the first example, two friends with cars live at vertex $ 5 $ , one can give a ride to friends from vertices $ 2 $ and $ 3 $ , and the second from vertex $ 4 $ , only a friend from vertex $ 6 $ will have to walk.

## 样例 #1

### 输入

```
3
6 7
1 2
2 3
2 4
3 5
4 5
3 6
6 5
5
2 3 4 5 6
4
1 2 3 5
6 7
1 2
2 3
2 4
3 5
4 5
3 6
6 5
6
2 3 4 5 6 5
4
1 2 3 5
4 4
1 2
1 3
2 3
3 4
3
3 4 2
2
1 3```

### 输出

```
2
1
1```

## 样例 #2

### 输入

```
3
2 1
1 2
3
2 2 2
3
1 2 3
3 3
1 2
1 3
2 3
4
2 2 2 3
3
1 2 4
4 4
3 1
3 2
1 4
2 4
5
3 2 2 4 2
3
1 3 4```

### 输出

```
3
1
0```

# 题解

## 作者：Moya_Rao (赞：17)

# 前言

被这个题目硬控太久太久了，正好看到题解通道还开着，本来咕值也不大行了，于是过来写了篇题解，给自己梳理梳理思路，也帮助其他人，顺便还可以涨点社贡，嘿嘿。

# 题目大意

给定一张有 $n$ 个顶点 $m$ 条边的无向图，其中有 $w$ 个位置住了人，第 $i$ 个位置是 $h_i$，注意有可能一个位置上居住多人。

所有人之前都在节点 $1$ 开派对，现在他们都要回家了，需要回到自己居住的点上。结果发现其中有 $k$ 个人没有车，第 $i$ 个没有车的人的索引为 $p_i$，即代表位置在 $h_{p_i}$ 的人没车。如果没有人能给他们搭乘顺风车的话，他们就只能步行回家。每个有车的朋友都可以接待任意数量的没车的朋友，只要是顺风车即可。

顺风车的定义：如果家位于节点 $i$ 的人要乘坐家位于节点 $j$ 的人的顺风车，需要满足 $1$ 到 $j$ 的最短路径中包含节点 $i$。

现需要你求出最少有多少人必须步行回家。注意本题有 $T$ 组数据，你需要针对每组数据进行回答。

$1 \le T \le 10^3$；  
$1 \le n,w \le 10^4$，$n-1 \le m \le \min(10^4,n \times (n-1) \div 2)$；  
$1 \le h_i \le n$，$1 \le k \le \min(w,6)$，$1 \le p_i \le w$。

# 思路

看见这个 $k$ 的数据范围就能知道，这道题目，或多或少会跟状压沾点儿边。没错，这道题就是状压！

我们首先可以进行一个 BFS 预处理，弄出来一个 $f$ 数组，存储居住在每个点的人能带哪些集合的人做顺风车。  
具体来说，我们令 $f_{i,j}$ 表示居住在节点 $i$ 的人能不能（$1$ 表示能，$0$ 表示不能）带集合 $j$ 的人做顺风车。$j$ 是用二进制表示的，在二进制下 $j$ 的第 $u$ 位表示我们的第 $u$ 个没有车的朋友，按照输入顺序编号。

处理完这个东西，接下来我们就得开始动态规划了。这个动态规划可有点儿奇怪，它有点像背包，但又像个状压。

先定义状态，设 $dp_{i,j}$ 表示前 $i$ 个朋友能不能（$1$ 表示能，$0$ 表示不能）带集合 $j$ 的人做顺风车。这个状态中的 $j$ 的含义与 $f$ 数组中的一样，在此不多赘述。

接下来就是转移啦，这里用的是扩散型转移。  
我们在转移之前可以先跳过 $dp_{i,j}$ 为 $0$ 的，因为这种不满足的是没办法扩散出什么的。

转移的时候需要分情况讨论：
- 如果第 $i+1$ 个人是没有车的，那么直接让 $dp_{i+1,j}=1$ 即可；
- 如果第 $i+1$ 个人有车，枚举所有 $t$ 满足 $f_{i+1,t}=1$，设 $s$ 为 $j$ 和 $t$ 的并集，都有 $dp_{i+1.s}=1$。

如何计算这个并集 $s$ 呢？其实上，在编写代码时直接计算 `s=j|t` 就可以啦。

最终的答案是什么呢？嘿嘿，我们还不能快速得出答案呢，需要枚举所有顺风车集合 $i$，对于所有满足 $dp_{w,i}=1$ 的集合，求出 $i$ 在二进制表示下有多少位是 $1$，统计出这个的最大值 $ans$，最后输出 $k-ans$ 即可！  
如何求解 $i$ 在二进制表示下有多少位是 $1$ 呀？很简单，可以利用 `lowbit` 来一位一位计算，也可以把数值分解成二进制再统计。由于前者较为好写，因为我是利用 `lowbit` 来计算的。  
诶，为什么最后不是直接输出 $ans$，而是输出 $k-ans$ 呢？因为我们的 $ans$ 表示的是最多有多少没车的人可以搭乘顺风车，而题目要的是最少有多少没车的人必须得步行回家，因此 $k-ans$ 才是真正的答案！

到此，此题就结束啦！思路并不难，但是细节挺多的，本人调了两个多小时，大家也可要注意啦！

# 代码

这里给出一份带有详细注释的代码，保证可以过，不信的话看这个[提交记录](https://codeforces.com/contest/1741/submission/315231688)。最后，我劝你们不要抄我的代码，感谢！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4+5 , K = 105;
int T,n,m,w,k,h[N],p[N],dis[N],ans;
bool v[N],f[N][K],dp[N][K];
vector<int> g[N];queue<int> q;
int Count(int x){
    int cnt=0;
    while(x)cnt++,x-=(x&-x);
    return cnt;
}
//使用 lowbit 的方法计算一个数在二进制表示下有多少位是 1
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m;ans=0;//初始化 ans 的值为 0
        for(int i=1;i<=n;i++)
            g[i].clear(),p[i]=0,dis[i]=0x3f3f3f3f;
        //多测不清空，爆零泪两行，一定要记得清空数组哟
        for(int i=1;i<=m;i++){
            int x,y;cin>>x>>y;
            g[x].push_back(y),g[y].push_back(x);
        }
        //输入这张图的每条边并用邻接矩阵存下来
        cin>>w;
        //输入朋友的个数
        for(int i=1;i<=w;i++)v[i]=0;//记得清空
        for(int i=1;i<=w;i++)cin>>h[i];
        //输入有朋友的顶点，可能有多个朋友居住在同一顶点
        cin>>k;
        //输入没有车的朋友的个数
        for(int i=1;i<=k;i++){
            int x;cin>>x;
            //输入这个没车的朋友的索引（对应 h[x]）
            v[x]=1;p[h[x]]+=(1<<(i-1));
            //标记这个位置的朋友没车并且用 p 记录
            //可能有多个位于这个顶点的朋友没车，因此 p 会累加
        }
        while(!q.empty())q.pop();q.push(1);
        //准备开始 BFS，首先清空队列接下来把顶点 1 塞进去
        for(int i=1;i<=n;i++)
            for(int j=0;j<(1<<k);j++)f[i][j]=0;
        //清空标记顺风车集合数组 f
        dis[1]=0,f[1][0]=1;
        //记录初始路径长度并给集合数组 f 赋初值
        while(!q.empty()){
            int u=q.front();q.pop();
            //取出队首并弹出
            for(int v:g[u]){
                //遍历所有可以到达的点
                if(dis[u]+1>dis[v])continue;
                //如果这条路径比之前最短路径要长就没用了，直接跳过
                if(dis[u]+1<dis[v]){dis[v]=dis[u]+1;q.push(v);}
                //如果这条路径比之前最短路径还要短的话
                //将路径长度记录进数组并将其塞进队列里
                for(int st=0;st<(1<<k);st++)
                    f[v][st]|=f[u][st],f[v][st|p[v]]|=f[u][st];
                //更新顺风车集合数组 f
                //其中一种更新是继承之前的
                //还有一种更新就是带上当前这个可以到达的点
            }
        }
        for(int i=1;i<=w;i++)
            for(int j=0;j<(1<<k);j++)dp[i][j]=0;
        //清空 dp 数组，一开始啥都不行
        dp[0][0]=1;
        //赋初值，不然啥也干不动
        for(int i=0;i<w;i++){
            //遍历每个住了朋友的顶点
            //注意这里用的是扩散型转移，因此枚举的是 0 到 w-1
            for(int st=0;st<(1<<k);st++){
                //枚举顺风车状态，用二进制表示
                if(!dp[i][st])continue;
                //如果原先的状态就不行，那不用扩散了，直接跳过就好
                if(v[i+1]){dp[i+1][st]=1;continue;}
                //如果这个位置的朋友没车，继承之前的就行了，扩散不了
                for(int nw=0;nw<(1<<k);nw++)
                //枚举位置 i+1 可以带上的顺风车集合，用二进制表示
                    if(f[h[i+1]][nw])dp[i+1][st|nw]=1;
                    //如果位置 i+1 真的可以带上这个顺风车集合 nw 的话
                    //就更新一下这个位置在两个状态 st 与 nw 合并后状态下的数值
            }
        }
        for(int st=0;st<(1<<k);st++)
        //遍历最终顺风车集合的状态，用二进制表示
            if(dp[w][st])ans=max(ans,Count(st));
            //如果这种情况可行，就计算一下最大能有多少个朋友搭乘顺风车
        cout<<k-ans<<"\n";
        //由于我们计算的是最大能有多少个朋友搭乘顺风车
        //而题目要求算的是最少得有多少个朋友要步行回家
        //因此我们计算的答案需要用 k 去减一下才是真正的答案
    }
    return 0;
}
```

如果觉得本篇题解对你有帮助的话，烦请你点一个小小的赞，多谢多谢！

---

## 作者：GalwayGirl (赞：12)

## 闲话
~~这道题深刻地教会了我什么叫做码题五分钟，调题两小时。~~

打 VP 时没有太多的看题，直接打了个状压，后面看到第一个样例的 test case 2 才发现原来不同的人可以住在一个地方，然后就考虑了 01 背包，结果忘记要倒序枚举了，调了一下午。

## Solution
看到 $k$ 的数据范围，很状压的亚子，设 $f_{i,j}$ 为在第 $i$ 个点的时候，朋友搭顺风车的状态为 $j$ 时，是否可以满足，所以数组可以为 bool 类型。主要考虑怎么转移，可以发现边权为 1，在用 bfs 求解最短路径时，bfs 搜索树的深度就等于最短路径，所以当第一次搜到该点时，就一定是最短路径，所以在这个地方可以直接转移，如果该点为没车朋友的家，就可以把他添加进状态。

题目问的是有车朋友可以搭的人数，而不是每一个点，所以再来一次状压，统计答案，可以采取 01 背包的方式。

## Detail
1. 因为图中点可能有多个最短路径，所以要改动一下普通的 bfs，看此处代码。
```cpp
    while(!q.empty()){
        int now=q.front();q.pop();
        for(int i=head[now];i;i=edge[i].next){
            int v=edge[i].to;
            if(dis[now]+1<=dis[v]){
                for(int j=0;j<(1<<k);j++)f[v][j]|=f[now][j],f[v][j|bit[v]]|=f[now][j];
                if(dis[now]+1<dis[v])q.push(v);
                dis[v]=dis[now]+1;
            }
        }
    }
```
2. 01 背包要倒序枚举。
```cpp
    for(int i=1;i<=fl;i++){
        if(vis[i])continue;
        for(int j=(1<<k);j>=0;j--)
            for(int l=0;l<(1<<k);l++)
                if(f[pos[i]][l])ff[j|l]|=ff[j];
    }
```
3. 多组测试，一定要清空。

最后贴上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+100;
int t,n,m,fl,k,pos[N],head[N],dis[N],max_,tot,c,bit[N],nocar;
bool f[N][1<<7],vis[N],ff[1<<7];
struct xzh{
    int next,to;
}edge[2*N];
void add(int u,int v){
    c++;
    edge[c].next=head[u];
    edge[c].to=v;
    head[u]=c;
}
void bfs(){
    f[1][0]=true;
    for(int i=1;i<=n;i++)dis[i]=1e9;
    queue<int>q;
    q.push(1);
    dis[1]=0;
    while(!q.empty()){
        int now=q.front();q.pop();
        for(int i=head[now];i;i=edge[i].next){
            int v=edge[i].to;
            if(dis[now]+1<=dis[v]){
                for(int j=0;j<(1<<k);j++)f[v][j]|=f[now][j],f[v][j|bit[v]]|=f[now][j];
                if(dis[now]+1<dis[v])q.push(v);
                dis[v]=dis[now]+1;
            }
        }
    }
}
void solve(){
    max_=0;c=0;
    memset(f,false,sizeof(f));
    memset(ff,false,sizeof(ff));
    memset(vis,false,sizeof(vis));
    memset(bit,0,sizeof(bit));
    memset(head,0,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    scanf("%d",&fl);
    for(int i=1;i<=fl;i++)scanf("%d",&pos[i]);
    scanf("%d",&k);
    for(int i=1;i<=k;i++)scanf("%d",&nocar),vis[nocar]=true,bit[pos[nocar]]|=(1<<(i-1));
    bfs();
    ff[0]=true;
    for(int i=1;i<=fl;i++){
        if(vis[i])continue;
        for(int j=(1<<k);j>=0;j--)
            for(int l=0;l<(1<<k);l++)
                if(f[pos[i]][l])ff[j|l]|=ff[j];
    }
    for(int i=0;i<(1<<k);i++){
        if(ff[i]){
            int cnt=0;
            for(int j=0;j<k;j++)if(i&(1<<j))cnt++;
            max_=max(max_,cnt);
        }
    }
    printf("%d\n",k-max_);
}
int main(){
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
```


---

## 作者：Chenyanxi0829 (赞：6)

## 思路
### 预处理
因为 $k$ 很小，所以可以先 bfs 预处理出家在 $i(2\le i\le n)$ 的人能捎带上哪些集合的人，在表示集合时用一个 $0$ 到  $2^k-1$ 的整数 $j$ 表示，若 $j$ 在二进质下的从小到大第 $l$ 位是 $1$，那么这个集合就包含第 $l$ 的没车的人。

在 bfs 从 $i$ 转移到 $j$ 时，如果 $i$ 能成为 $1$ 到 $j$ 的最短路上的点，那么家在 $i$ 的人能捎带上的人的集合家在 $j$ 的人也能捎带上，注意集合里还要加上家在 $j$ 点且没车的人。

### 预处理完后做 dp ：
- 设 $dp_{i,j}$ 表示前 $i$ 个人是否能捎带上 $j$ 集合里的所有人。
- 转移（扩散型）：
    - 如果第 $i+1$ 个人没车，那么如果 $dp_{i,j}=1$ 则 $dp_{i+1,j}=1$ 否则 $dp_{i+1,j}=0$。
    - 如果第 $i+1$ 个人有车，那么如果 $dp_{i,j}=1$ 且第 $i+1$ 个人回家的路上能捎带上集合 $l$ 的人，则对于 $j$ 和 $l$ 的并集 $q$，$dp_{i+1,q}=1$。
- 在表示集合的时候，可以用预处理时的方法，那么 $j$ 和 $l$ 的并集就是 $j|l$。


### 答案
对于 $dp_{f,j}=1$ 的 $j$，输出 $k$ 减去集合大小最大的 $j$ 的集合大小。
### 注意
本题为多测，注意要清空。
## 时间复杂度
### 对于每个测试点
#### bfs
$O((n+m)\cdot 2^k)$
#### dp
$O(f\cdot 2^{2k})$
#### 总共
$O((n+m)\cdot 2^k+f\cdot 2^{2k})$
## 空间复杂度
### 对于每个测试点
$O(n\cdot 2^k+f\cdot 2^k)$
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e4 + 1, kMaxS = 1 << 6;

int t, n, m, p[kMaxN], o, h[kMaxN], k, c[kMaxN], dp[kMaxN][kMaxS], ma;
bool a[kMaxN][kMaxS], f[kMaxN];
vector<int> b[kMaxN];
queue<int> q;

void R(int x, int l, int j) {
  if (j <= c[x]) {
    if (j < c[x]) {
      c[x] = j;
      q.push(x);
    }
    for (int i = 0; i < (1 << k); i++) {
      a[x][(i | p[x])] |= a[l][i];
    }
  }
}

int S(int x) {
  int ans = 0;
  for (; x; ans++, x -= (x & (-x))) {
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
      cin >> u >> v;
      b[u].push_back(v), b[v].push_back(u);
    }
    cin >> o;
    for (int i = 1; i <= o; i++) {
      cin >> h[i];
    }
    cin >> k;
    fill(p + 1, p + n + 1, 0);
    fill(f + 1, f + o + 1, 0);
    for (int i = 1, a; i <= k; i++) {
      cin >> a;
      f[a] = 1;
      p[h[a]] += (1 << (i - 1));
    }
    fill(a[1], a[n] + kMaxS, 0);
    a[1][0] = 1;
    fill(c + 1, c + n + 1, n + 1);
    for (R(1, 0, 0); q.size(); q.pop()) {
      for (int i : b[q.front()]) {
        R(i, q.front(), c[q.front()] + 1);
      }
    }
    fill(dp[0], dp[o] + kMaxS, 0);
    dp[0][0] = 1;
    for (int i = 0; i < o; i++) {
      for (int j = 0; j < (1 << k); j++) {
        if (dp[i][j]) {
          if (!f[i + 1]) {
            for (int l = 0; l < (1 << k); l++) {
              if (a[h[i + 1]][l]) {
                dp[i + 1][j | l] = 1;
              }
            }
          } else {
            dp[i + 1][j] = 1;
          }
        }
      }
    }
    ma = 0;
    for (int i = 0; i < (1 << k); i++) {
      ma = max(ma, S(i) * dp[o][i]);
    }
    cout << k - ma << "\n";
    for (int i = 1; i <= n; i++) {
      b[i].clear();
    }
  }
  return 0;
}
```

---

## 作者：RuntimeErr (赞：5)

有意思的题。

一个人可以载的人的家在其到 $1$ 号节点的最短路径上（可以有多条）。注意到 $k$ 很小，可以用状压来表示当前点可以载的人（可能有**多组**）。预处理用 bfs 就好了。

我们要载尽可能多的人，相当于将这些可以载人的点的状态拼出尽可能多的 $1$，可以用 $f_i$ 表示状态 $i$ 能否被拼出，做分组 01 背包就是了。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
template <typename T>
inline void read(T& r) {
    r=0;bool w=0; 
    char ch=getchar();
    while(ch<'0'||ch>'9') w=ch=='-'?1:0,ch=getchar();
    while(ch>='0'&&ch<='9') r=(r<<3)+(r<<1)+(ch^48), ch=getchar();
    r=w?-r:r;
}
 
const int N=1e4+10,M=10;
 
int n,m,f,k,h[N],bit[N],ans;
vector<int>e[N];
bool dp[1<<M],car[N],flag[N][1<<M];//flag[i][j]:第 $i$ 个节点是否能载状态为 $j$
 
queue<int>q;
int dis[N];
void bfs(){
    for(int i=1;i<=n;++i)dis[i]=-1;
    dis[1]=0;q.push(1);flag[1][0]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:e[u]){
            if(dis[v]==-1||dis[v]==dis[u]+1){//最短路径上都可以载
                for(int i=0;i<(1<<k);++i){
                    if(flag[u][i])flag[v][i]=flag[v][i|bit[v]]=1;//记得算上当前点的状态
                }
                if(dis[v]==-1){
                    dis[v]=dis[u]+1;
                    q.push(v);
                }
            }
        }
    }
}
 
inline int count(int x){int res=0;while(x)++res,x-=(x&-x);return res;}
 
void init(){
    for(int i=1;i<=n;++i)e[i].clear();
    memset(flag,0,sizeof flag);
    memset(bit,0,sizeof bit);memset(car,0,sizeof car);
}
 
void solve(){
    read(n),read(m);init();
    for(int i=1,u,v;i<=m;++i){
        read(u),read(v);
        e[u].push_back(v),e[v].push_back(u);
    }read(f);
    for(int i=1;i<=f;++i)read(h[i]),car[i]=1;
    read(k);
    for(int i=0,p;i<k;++i)read(p),bit[h[p]]|=(1<<i),car[p]=0;//计算当前点的状态

    bfs();
    memset(dp,0,sizeof dp);dp[0]=1;ans=0;
    for(int i=1;i<=f;++i){
        if(!car[i])continue;
        for(int j=(1<<k);j>=0;--j){
            for(int v=0;v<(1<<k);++v){
                if(flag[h[i]][v])dp[j|v]|=dp[j];
            }
        }
    }
    for(int i=1;i<=(1<<k);++i)if(dp[i])ans=max(ans,count(i));
    printf("%hd\n",k-ans);
}
 
int main(){
    #ifdef LOCAL
        freopen("std.in","r",stdin);
        freopen("my.out","w",stdout);
    #endif
    int t;read(t);
    while(t--)solve();
    return 0;
}
```

---

## 作者：王熙文 (赞：5)

这题思路挺好想的，就是有很多细节。

## 思路

首先，注意到 $k$ 比较小，可以想到状压。

设 $go_{i,j}$ 表示第 $i$ 个点处的任意一个带车的人是否能带状态为 $j$（没带车的人）的一些人。

在 bfs 上转移。一个点可以从所有它的最短路径来源点过来，也就是说最短路径来源点可以带的一些人这个点也可以带。

这样就可以转移了。首先枚举转移点，然后枚举状态 $S$，此时如果转移点可以带这个状态，那么当前点也可以带这个状态。但是当前点也可以带当前点没有带车的人，所以枚举一下当前点没有带车的人带哪一些（再次枚举状态），然后将 $S$ 减去这些点转移即可。

需要注意一点：一个点能带一个状态 $S$，也能带另一个状态 $T$，但不一定都能带。所以最后求答案的时候不能把每一个点都合并起来，而是再次用状压 dp 求。设 $dp_{i,j}$ 表示前 $i$ 个人是否能带状态为 $j$ 的人。此时 $i$ 这个人必须带车。找到上一次能带车的人 $k$，枚举 $i$ 这个人带哪一些人（枚举 $j$ 的子集降低复杂度）（可以通过 $i$ 所在的点的 $go$ 值判断），然后转移即可。

复杂度：bfs 部分虽然要枚举当前点没带车的人的状态，但是总共没带车的人个数就只有 $k$，所以这个东西总和最多为 $2^k\times k$。所有点最短路径来源点总和一定小于等于 $m$。所以这一部分复杂度为 $\mathcal O((m+2^k \times k) \times 2^k)$。dp 部分首先需要枚举人，然后枚举状态和子集，所以复杂度为 $\mathcal O(f \times 3^k)$。总复杂度为 $\mathcal O(m \times 2^k + f\times 3^k)$。能过。

## 代码

好难写:(

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f,k;
vector<int> e[10010];
int a[10010],p[10010]; vector<int> lst[10010]; // lst[i] 表示点在 i 的位置是否没带车，没带车的编号 
int dis[10010]; vector<int> zy[10010]; // 转移点
queue<int> q;
bool ifgo[10010][1<<6]; // 是否可以带这些人 
bool dp[10010][1<<6];
bool vis[10010];
int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	int t; cin>>t; while(t--)
	{
		cin>>n>>m;
		for(int i=1; i<=n; ++i) e[i].clear();
		for(int i=1; i<=m; ++i)
		{
			int u,v; cin>>u>>v;
			e[u].push_back(v),e[v].push_back(u);
		}
		cin>>f;
		for(int i=1; i<=f; ++i) cin>>a[i];
		for(int i=1; i<=n; ++i) lst[i].clear();
		cin>>k;
		memset(vis,0,sizeof(vis));
		for(int i=1; i<=k; ++i) cin>>p[i],lst[a[p[i]]].push_back(i),vis[p[i]]=1;
		memset(dis,0x3f,sizeof(dis)); dis[1]=0; q.push(1);
		for(int i=0; i<=n; ++i) for(int j=0; j<(1<<k); ++j) ifgo[i][j]=0;
		for(int i=0; i<=f; ++i) for(int j=0; j<(1<<k); ++j) dp[i][j]=0;
		ifgo[1][0]=1;
		while(!q.empty())
		{
			int frn=q.front(); q.pop();
			for(int i:zy[frn])
			{
				for(int j=0; j<(1<<k); ++j)
				{
					ifgo[frn][j]|=ifgo[i][j];
					if(lst[frn].size())
					{
						for(int ll=0; ll<(1<<lst[frn].size()); ++ll)
						{
							int nowzt=0; bool flag=1;
							for(int kk=0; kk<lst[frn].size(); ++kk)
							{
								if(ll>>kk&1)
								{
									if(!(j>>(lst[frn][kk]-1)&1)) { flag=0; break; }
									nowzt+=(1<<lst[frn][kk]-1);
								}
							}
							if(!flag) continue;
							ifgo[frn][j]|=ifgo[i][j^nowzt];
						}
					}
				}
			}
			for(int v:e[frn])
			{
				if(dis[v]>dis[frn]+1)
				{
					zy[v].clear(); zy[v].push_back(frn);
					dis[v]=dis[frn]+1;
					q.push(v);
				}
				else if(dis[v]==dis[frn]+1) zy[v].push_back(frn);
			}
		}
		dp[0][0]=1; int ans=0,llst=0;
		for(int i=1; i<=f; ++i)
		{
			if(vis[i]) continue;
			for(int j=0; j<(1<<k); ++j)
			{
				// dp[i][j], f[i]
				for(int k=j; ; k=(k-1)&j)
				{
					if(ifgo[a[i]][k]) dp[i][j]|=dp[llst][j^k];
					if(!k) break;
				}
				if(dp[i][j]) ans=max(ans,__builtin_popcount(j));
			}
			llst=i;
		}
		cout<<k-ans<<'\n';
	}
	return 0;
}
```

---

## 作者：__Deng_Rui_Song__ (赞：1)

# preface

什么题啊！硬控我一天！

# problem

[题目传送门](/problem/CF1741G)

题目简述：给你一个 $n$ 个点 $m$ 条边的连通无向图，有 $f$ 个人在点 $1$，其中有 $k$ 个没有车的朋友，其他人都是有车的朋友，第 $i$ 个人住在点 $a_i$，有车的朋友会开着车沿着最短路径回家，车内可以容纳无限个人，可以让没有车的朋友蹭顺风车，如果没有蹭到顺风车就只能徒步回家，求最少有多少个没有车的朋友得徒步回家。

# solution

看到 $k$ 的范围，可以想到状压 dp，结果它还真是：

设 $dp_{i,j}$，表示前 $i$ 个朋友且没有车的朋友有没有搭上顺风车的状态为 $j$ 可不可行。

你：答案就是 $\max_{i=0}^{2^k-1}\operatorname{popcount}(i)$（$\operatorname{popcount}(i)$ 为 $i$ 在二进制下一的个数）

没错，接下来，本题一大难点：状态转移方程。由于按位或运算不可逆，所以使用扩散性转移。

你：枚举第 $i+1$ 个有车的朋友回家的最短路径，然后在最短路径上的没有车的朋友都可以蹭顺风车！跟 $j$ 取按位或！

接下来，本题二大难点，求最短路径。

你：bfs！

但是你还要把它存下来，我们设 $f_{i,j}$ 表示从 $1$ 到 $i$ 的路径上，没有车的朋友有没有蹭顺风车的状态为 $j$ 可不可行。

你：设 $a_i$ 表示居住在 $i$ 的没有车的朋友，同样状压，然后状态转移方程为 $dp_{nxt,j|a_{nxt}}|=dp_{i,j}(i-nxt)$（这里 $-$ 指有连边）

是的，接下来回首掏，怎么初始化？

你：$dp_{0,0}=1$，其它的都是 $0$！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,w,k,a[10005],b[10005],dis[10005];
vector<int> g[10005];
bool f[10005][65],car[10005],dp[10005][65];
void solve(){
  cin >> n >> m;
  for (int i = 1; i <= n; i++){
    g[i].clear();
    b[i] = 0;
    dis[i] = 1e18;
  }// 多测不清空，爆零两行泪
  for (int i = 1,x,y; i <= m; i++){
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }// 建图
  cin >> w;
  for (int i = 1; i <= w; i++){
    cin >> a[i];
    car[i] = 0;// 有车为 0，没车为 1
  }
  cin >> k;
  for (int i = 0,x; i < k; i++){
    cin >> x;
    b[a[x]] += 1 << i;// 统计住在 a[x] 的没车的朋友
    car[x] = 1;
  }
  queue<int> q;
  q.push(1);
  for (int i = 1; i <= n; i++) for (int j = 0; j < 1 << k; j++) f[i][j] = 0;// 多测不清空，爆零两行泪
  f[1][0] = 1;
  dis[1] = 0;
  while (!q.empty()){
    int x = q.front();
    q.pop();
    for (int i = 0; i < g[x].size(); i++){
      int nxt = g[x][i];
      if (dis[x] + 1 > dis[nxt]) continue;
      if (dis[x] + 1 < dis[nxt]){
        dis[nxt] = dis[x] + 1;
        q.push(nxt);
      }
      for (int j = 0; j < 1 << k; j++) f[nxt][j | b[nxt]] |= f[x][j];// 转移
    }
  }// bfs 板子
  for (int i = 1; i <= w; i++) for (int j = 0; j < 1 << k; j++) dp[i][j] = 0;// 多测不清空，爆零两行泪
  dp[0][0] = 1;
  for (int i = 0; i < w; i++) for (int j = 0; j < 1 << k; j++){
    if (!dp[i][j]) continue;// 本来就不可行你不就炸了吗
    if (car[i + 1]){
      dp[i + 1][j] = 1;
      continue;
    }// 没车还无中生有一辆车你不就炸了吗
    for (int x = 0; x < 1 << k; x++) if (f[a[i + 1]][x]) dp[i + 1][j | x] = 1;// 转移
  }
  int ans = 0;
  for (int i = 0; i < 1 << k; i++) if (dp[w][i]) ans = max(ans,(int)(__builtin_popcount(i)));// 统计答案
  cout << k - ans << '\n';
}
signed main(){
  for (cin >> t; t--; solve());
  return 0;
}
```

# postscript

热血奋战终于找 CF 要了组 hack 数据，AC 此题。

---

## 作者：ChrysanthBlossom (赞：0)

首先，观察题面，注意到 $k \le 6$ ，显然要对这 $k$ 个人状压。

然后你考虑什么叫“顺路”。题目中说一个人顺路指他的家在有车朋友回家的最短路上，我们可以换一种方式理解，即**一个人以一定策略将一群人送回家之后再回家与自己直接回家路程一样**。

于是，问题转化为求 $dis_{u,S}$，即送完 $S$ 中所有人之后到 $u$ 的最短距离。

这玩意和最小斯坦纳树太像了，因此可以考虑分成点内转移与点外转移。对于点外的显然就是最短路，点内显然是 $\forall h_x=u,dis_{u,S} \to dis_{u,S \cup x}$（可以理解为一开始你把所有人都放到了你的车上，然后走到一个人家里就丢下一个），像最小斯坦纳树那样外层枚举 $S$，内层转移即可。至于这里的最短路，虽然由于他近似“多源”（即转移时会利用多个 $dis$）而不能 bfs，但观察到 $dis$ 的最大值是 $O(n)$ 的，因此可以用桶维护堆，然后跑 dij，这样就把 dij 的 $\log$ 去掉了（写题解的人懒到极点了，选择了已死的 spfa ~~反正能过~~）。

求完 $dis$ 之后就可以求出对于每个点是否可以送 $S$ 这些人，把这些信息对应到人上即可。

最后再对人跑一遍子集 dp 就做完了。

视 $n,m,f$ 同阶，时间复杂度 $O(n \times 3^k + n \times 2^k)$。

一个细节：在后面子集 dp 的时候要把那些没车的排除掉，不然就无中生有了。

```cpp
#include<bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;
const int maxn=3e4+7;
int dis[maxn][1<<6];
bool vis[maxn];
int n,m;
int f,k;
int cnt,head[maxn],to[maxn],nxt[maxn];
int h[maxn];
vector<int>pnt[maxn];
bool ok[maxn][1<<6];
int car[maxn];
const int inf=1e9;
void add(int u,int v){
	++cnt;
	to[cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void spfa(int S){
	queue<int>q;
	for(ri i=1;i<=n;i++)vis[i]=0;
	for(ri i=1;i<=n;i++){
		if(dis[i][S]!=inf){
			q.push(i);
			vis[i]=1;
		}
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(ri e=head[u];e;e=nxt[e]){
			int v=to[e];
			if(dis[u][S]+1<dis[v][S]){
				dis[v][S]=dis[u][S]+1;
				if(!vis[v]){
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
}
void solve(){
	cin>>n>>m;
	for(ri i=1;i<=n;i++){
		pnt[i].clear();
	}
	cnt=0;
	for(ri i=1;i<=n;i++)head[i]=0;
	for(ri i=1;i<=2*m;i++)nxt[i]=to[i]=0;
	for(ri i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	cin>>f;
	for(ri i=1;i<=f;i++)car[i]=0;
	for(ri i=1;i<=f;i++){
		cin>>h[i];
		pnt[h[i]].emplace_back(i);
	}
	cin>>k;
	for(ri i=1;i<=f;i++){
		for(ri S=0;S<1<<k;S++){
			ok[i][S]=0;
		}
	}
	for(ri i=1;i<=k;i++){
		int t;cin>>t;
		car[t]=i;
	}
	for(ri i=1;i<=n;i++){
		for(ri S=0;S<1<<k;S++){
			dis[i][S]=inf;
		} 
	}
	dis[1][0]=0;
	for(ri S=0;S<1<<k;S++){
		for(ri i=1;i<=n;i++){
			int T=0;
			for(auto x:pnt[i]){
				if(car[x])T|=(1<<car[x]-1);
			}
			dis[i][S]=min(dis[i][S],dis[i][S&(((1<<k)-1)^T)]);
		}
		spfa(S);
	}
	for(ri i=1;i<=f;i++){
		for(ri S=0;S<1<<k;S++){
			if(!car[i]&&dis[h[i]][S]==dis[h[i]][0]){
				ok[i][S]=1;
			}
		}
	}
	int ans[1<<6]={};
	ans[0]=1;
	for(ri i=1;i<=f;i++){
		for(ri S=(1<<k)-1;S;S--){
			for(ri T=S;T;T=(T-1)&S){
				if(ok[i][T])ans[S]|=ans[S^T];
			}
		}
	}
	int res=k;
	for(ri S=0;S<1<<k;S++){
		if(ans[S]){
			res=min(res,k-__builtin_popcount(S));
		}
	}
	cout<<res<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

