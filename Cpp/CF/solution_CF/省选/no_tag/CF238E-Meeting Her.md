# Meeting Her

## 题目描述

Urpal lives in a big city. He has planned to meet his lover tonight.

The city has $ n $ junctions numbered from $ 1 $ to $ n $ . The junctions are connected by $ m $ directed streets, all the roads have equal length. Urpal lives in junction $ a $ and the date is planned in a restaurant in junction $ b $ . He wants to use public transportation to get to junction $ b $ . There are $ k $ bus transportation companies. At the beginning of every second, a bus from the $ i $ -th company chooses a random shortest path between junction $ s_{i} $ and junction $ t_{i} $ and passes through it. There might be no path from $ s_{i} $ to $ t_{i} $ . In that case no bus will leave from $ s_{i} $ to $ t_{i} $ . If a bus passes through a junction where Urpal stands, he can get on the bus. He can also get off the bus at any junction along the path.

Now Urpal wants to know if it's possible to go to the date using public transportation in a finite amount of time (the time of travel is the sum of length of the traveled roads) and what is the minimum number of buses he should take in the worst case.

At any moment Urpal knows only his own position and the place where the date will be. When he gets on the bus he knows only the index of the company of this bus. Of course Urpal knows the city map and the the pairs $ (s_{i},t_{i}) $ for each company.

Note that Urpal doesn't know buses velocity.

## 样例 #1

### 输入

```
7 8 1 7
1 2
1 3
2 4
3 4
4 6
4 5
6 7
5 7
3
2 7
1 4
5 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 4 1 2
1 2
1 3
2 4
3 4
1
1 4
```

### 输出

```
-1
```

# 题解

## 作者：约瑟夫用脑玩 (赞：20)

一道蓝题竟恐怖如斯，以至于整个机房被骗了一天直到晚上才终究探其根本。

## 第零层

读懂题，自认为点了要素察觉这个技能的可以跳过。

下面是一些要素，由于我英语翻译比较菜，有能力的尽量还是读英语原文qwq：

- > all the roads have equal length. 

  所有的路长度相同。
  
- > At the beginning of every second, a bus from the $i$ -th company chooses a random shortest path between junction $s_{i}$ and junction $t_{i}$ and passes through it.

  每一秒都 $k$ 辆车发车，第 $i$ 辆从 $s_i$ 到 $t_i$，选取的路线是某一随机的最短路。
  
- > If a bus passes through a junction where Urpal stands, he can get on the bus. He can also get off the bus at any junction along the path.

  只要有车在同一位置随时可上，且在车上随时可下。
  
- > At any moment Urpal knows only his own position and the place where the date will be. When he gets on the bus he knows only the index of the company of this bus.

  最重要的一句话：每次做出决策时只有当前的位置、目标位置和同一位置车的编号。
  
  注意：没有路线！也就是说就算你上了车也不知道它会怎么走，只知道它会往终点走最短路。
  
- > Note that Urpal doesn't know buses velocity.

  意译了一下：所有车的路线都未知，除非在同一位置则位置也未知。
  
- > what is the minimum number of buses he should take in the worst case.

  求最少换乘次数而不是最短时间。
  
- > Now Urpal wants to know if it's possible to go to the date using public transportation in a finite amount of time

  还有这一句后面用得到的话：在有限时间内到达目标地点，求最坏情况下次数。
  
## 第一层

手玩一下，发现路线极其复杂，不知道会到哪个点，也不知道能去哪个点。

再考虑公交就更离谱了，你不知道它往哪里走，你就更不知道在哪里下。

## 第二层

> 公交车永远不会往你想的那样走。
>
> ——机房著名人物Gina

注意到要素中的最后一句话，如果我们希望某辆车恰好经过起点，且恰好经过终点，那岂不是不用换乘就可以到达？

但这样等下去可能得无限多秒才会有这样的一趟车，这里就可以轻易的得到一个结论：

若位置 $x$ 不在 $s_i\to t_i$ 的必经点上，则在 $x$ 直接等到车 $i$ 就不是在有限秒内一定能发生的事，**那么就一定不能在 $x$ 等 $i$ 这辆车**。

那么我们必须在必经点才能上车，下车呢？同理有推论：

若当前在位置 $x$ 坐 $i$ 这辆车，且位置 $y$ 不在 $x\to t_i$ 的必经点上，则在 $x$ 直接坐车到位置 $y$ 就不是在有限秒内一定能发生的事，**那么就一定不能在 $x$ 用 $i$ 这辆车直接到 $y$**。

所以有一个 naive 的想法就是对于每条路线取出所有必经点，那么这条路线一定可以保证你在必经点之间可以转移，直接必经点连边重建图跑最短路。

精细实现可以做到 $O(n^3)$，看眼题解发现比他说的 $O(n^4)$ 不知道高明到哪里去了。

## 第三层

虽然没人写，但可以预见的是你肯定会错，没错来找我，我来手动 Hack。

~~玄机~~问题就出在这张图上：

![](https://cdn.luogu.com.cn/upload/image_hosting/a270guv7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在 $a=1,b=4$ 的情况下，虽然 $4$ 不是路线 $1$ 的必经点，但是你必定能换乘到路线 $2$ 从而到达 $4$ 号点。

那么**一些** naive 的想法就出现了，比如说 _枚举必经点和路线相交、枚举两必经点之间和路线相交、枚举必经点之间的路线和必经点相交_ （错误示范，血与泪的教训）等把没考虑到的转移情况通过在新图加边修复。

发现要么解决不了问题要么根本不可做。

## 第四层

> 请循其本。
>
> ——庄子

庄子：我真的说过真句话。

仔细思考发现其实本质上只有 $O(nk)$ 种状态，即在位置 $x$ 且在车 $y$ 上。

注意：以下均不考虑中途换乘等待时的状态，因为你只要你要换乘你必在必经点上，两秒内必有车来。

对于这 $O(nk)$ 种状态我们**直接考虑转移**，发现就两种情况：要不就是原地换乘，要不就是继续坐车。

第一种转移，由于公交车只会往最差的地方走，那么我们就得在所有可能的后继状态里取 $\max$。

而我们希望**通过决策**使得换乘次数最少，那么与第二种原地换乘的次数得取 $\min$。

这样对于所有本质不同的状态求出最优决策下的最少状态就是确实是考虑完全的最优决策了。

具体&形式化的说一下转移：设 $f_{x,y}$ 表示在位置 $x$ 做路线 $y$ 的车的最少换乘次数，初始值为 $f_{b,?}=0$，要求的是 $ans=\min{f_{a,i}}$，其中路线 $i$ 满足 $a$ 是其必经点。

转移为：$f_{x,y}=\min(\max\limits_{p\text{在}x\to t_y\text{的最短路上}}{f_{p,y}},1+\min\limits_{x\text{是路线}z\text{的必经点}}(f_{x,z}))$

全源最短路，找必经点，将 $n,k$ 看作同阶，精细实现一下都是 $O(n^3)$ 的。

具体地，跑 Floyd 的同时将最短路方案求出来就可以快速判断必经点了。

而最后的转移一次也至多是 $O(n)$，状态 $O(n^2)$，精细实现一下也可以做到 $O(n^3)$。

具体地，第一种转移是没有边权的，但必须后继状态的 $\max$ 取完后才可以转移，而第二种转移必定 $+1$，故可以用按 $f$ 的大小分层更新的办法实现。

每层取出所有当前层状态并且更新前驱，更新完的继续丢入队列更新，同时更新第二种转移，更新完当前层则进入下一层。

由于只会在某个点换乘才会 $+1$，最多在 $n$ 个点处都换乘，故总共可能的层数只有 $O(n)$ 层，而不是 $O(\text{状态数}=nk)$ 层，故这里只有 $O(n\times nk)$ 不是瓶颈。

~~同样是精细实现，同样是 $\sout{O(n^3)}$ 比 $\sout{O(n^4)}$ 不知道高明到哪里去了，你在第几层？~~

## FAQ

Q：CF 标解和拟古题解是什么？

A：都运用了分层的思想，CF 标解用的是 $O((nk)^2)$ 的暴力 Dijkstra，拟古的没细看，应该都是没精细实现的下场。（~~不排除是错的~~

Q：写的这么好怎么没人看？

A：这应该问你。

---

## 作者：是个汉子 (赞：7)

### Solution

通过最短路和 $n\leq 100$ 得知我们可以拿 $floyd$ 预处理全源最短路。然后因为要换车，所以我们可以考虑dp，设 $dp_i$ 为 $i$ 到终点 $b$ 的最坏换车次数，但是从起点开始可能会有后效性，所以从终点开始，即 $dp_b$ 为 $0$ 。

对于路线 $k$ ，不一定只有一条最短路，所以我们考虑 $k$ 必然经过的点。但是模拟一下发现只考虑必经点是不行的，某条最短路上的非必经点可能是别的路线的必经点。所以选择拿 $dfs$ 来搜索情况，并及时更新。

注意：可能会出现环，所以要判断。

时间复杂度 $O(n^4)$ 。还有一些注意点写在代码里了。

### 代码

```c++
#include<bits/stdc++.h>

using namespace std;
int vis[105],T,num[105],dp[105],f[105][105],n,m,K,DP[105],s[105],t[105];
bool b[105][105];

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int dfs(int u,int k){
//u是当前点，k是路线，计算u点只坐这条公交路线到达终点最坏情况的换乘次数
    if(vis[u]==T) return DP[u];
    int tmp=-1;vis[u]=T;
    for(int v=1;v<=n;v++)
        if(f[u][v]==1&f[u][t[k]]==f[v][t[k]]+1)
        //判断u和v是否有边   u->v是k这条路线最短路径上的边
            tmp=max(tmp,dfs(v,k));
    if(tmp==-1) tmp=1e9;
    if(tmp>dp[u]) tmp=dp[u];
    //dp[u]表示从u到终点的最小换乘次数(u为必经点)
    return DP[u]=tmp;//因为可能有环所以要记一个DP
}

int main(){
    scanf("%d%d%d%d",&n,&m,&s[0],&t[0]);
    for(int i=1;i<n;i++)    
        for(int j=i+1;j<=n;j++) f[i][j]=f[j][i]=1e9;
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);
        f[u][v]=1;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
    scanf("%d",&K);
    for(int i=1;i<=K;i++){
        scanf("%d%d",&s[i],&t[i]);
        if(f[s[i]][t[i]]==1e9) continue;
        for(int j=1;j<=n;j++)
            if(f[s[i]][j]+f[j][t[i]]==f[s[i]][t[i]])
                num[f[s[i]][j]]++;
        for(int j=1;j<=n;j++)
            if(f[s[i]][j]+f[j][t[i]]==f[s[i]][t[i]]){
                if(num[f[s[i]][j]]==1) b[i][j]=1;//i路线的最短路径上的某个点可能会经过多条边，所以要寻找必经点
                num[f[s[i]][j]]=0;
            }
    }
    for(int i=1;i<=n;i++) dp[i]=DP[i]=1e9;
    dp[t[0]]=0;
    bool flag=1;
    while(flag){
        flag=0;
        for(int i=1;i<=K;i++)
            for(int j=1;j<=n;j++)
                if(b[i][j]){
                    T++;//只是dfs来判环用的
                    int tmp=dfs(j,i)+1;//在此算上了一次车，所以+1
                    if(tmp<dp[j]){
                        flag=1;//如果更新了答案，那需要再枚举一遍必经点
                        dp[j]=tmp;//dp值只在这里更新，有意义的dp值为必经点
                    }
                }
    }
    if(dp[s[0]]==1e9) dp[s[0]]=-1;
    printf("%d\n",dp[s[0]]);
    return 0;
}
```



---

## 作者：Umbrella_Leaf (赞：2)

你谷翻译根本看不懂啊！

题面意思是，你要给出一个最优方案，满足最坏情况下这个方案从 $a$ 到 $b$ 的换乘次数最少。

方案应当形如：

1. 对于每个 $x$，你应当给出一个 $i$，表示在点 $x$ 下车后你会等第 $i$ 个公司的车。

2. 对于每个 $x,i$，你应当给出一个 $0/1$ 中的数，表示在你乘坐第 $i$ 个公司的车经过第 $x$ 个点时是否下车。

3. 你的方案需要保证无论 $m$ 个公司的车如何安排都能从 $a$ 到达 $b$。

如果不能构造这样的方案，输出 `-1`；否则输出最坏情况下的换乘次数。

这样就能清晰地看出，我们的状态应当记录当前在哪个点，以及当前在哪辆车上。

设 $dp_{x,i}$ 表示当前乘坐第 $i$ 辆车经过点 $x$，到达 $b$ 的换乘次数最小值。显然初值是 $dp_{b,i}=0$，答案是 $\max_{a\ \texttt{是}\ i\ \texttt{路径上的必经点}} dp_{a,i}$。

转移：

$$dp_{x,i}=\min(\max_{(x,p)\in E,i\ \texttt{可能经过}\ p}dp_{p,i},\min_{x\ \texttt{是}\ j\ \texttt{上的必经点}}dp_{x,j}+1)$$

前者表示继续乘坐第 $i$ 辆车再坐一站，后者表示换车。

因为换车不超过 $n$ 次，所以第二类转移最多只有 $n$ 次，也就是能把所有点分成 $n$ 层。

先用 Floyd 处理出每条路径的必经点，然后跑 $n$ 遍 `bfs` 即可。因为每个点只会转移 $1$ 次，单次转移 $O(n)$，所以总复杂度是 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,S,T;
int dis[105][105];
int ex[105],ey[105],isok[105];
int tot[105][105];
int ans[105][105],deg[105][105];
int main(){
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dis[i][j]=(i!=j)*0x3f3f3f3f;
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        dis[x][y]=1;
    }
    for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)scanf("%d%d",&ex[i],&ey[i]),isok[i]=(dis[ex[i]][ey[i]]<0x3f3f3f3f);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(isok[j]&&dis[ex[j]][i]+dis[i][ey[j]]==dis[ex[j]][ey[j]]){
        tot[j][dis[ex[j]][i]]++;
        for(int k=1;k<=n;k++)if(dis[i][k]==1&&dis[ex[j]][i]+1+dis[k][ey[j]]==dis[ex[j]][ey[j]])deg[i][j]++;
    }
    memset(ans,0x3f,sizeof(ans));
    for(int i=1;i<=m;i++)if(isok[i]&&dis[ex[i]][T]+dis[T][ey[i]]==dis[ex[i]][ey[i]])ans[T][i]=0;
    for(int _=0;_<n;_++){
        queue<pair<int,int>>que;
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(ans[i][j]==_)que.push(make_pair(i,j));
        while(!que.empty()){
            int x=que.front().first,i=que.front().second;que.pop();
            if(tot[i][dis[ex[i]][x]]==1){
                if(x==S)return printf("%d\n",ans[x][i]+1),0;
                for(int j=1;j<=m;j++)if(isok[j]&&dis[ex[j]][x]+dis[x][ey[j]]==dis[ex[j]][ey[j]])
                    ans[x][j]=min(ans[x][j],ans[x][i]+1);
            }
            for(int y=1;y<=n;y++)if(dis[y][x]==1&&dis[ex[i]][y]+1+dis[x][ey[i]]==dis[ex[i]][ey[i]])
                if(!--deg[y][i]&&ans[y][i]>ans[x][i]){
                    ans[y][i]=ans[x][i];
                    que.push(make_pair(y,i));
                }
        }
    }
    puts("-1");
    return 0;
}
```

---

## 作者：Baseplate27 (赞：1)

有趣图论题。

发现当我们在点 $i$ 从车 $u$ 上下来时，如果我们还想继续坐车，则点 $i$ 必须是某一个除 $u$ 这辆车以外的公车最短路径的必经点。

我们还可以发现每个公车在最优情况下最多坐一次，所以我们可以进行 $k$ 轮更新。第 $i$ 轮更新时需要求出所有满足最少乘坐 $i$ 次车即可到达终点的点并将其标记。

在更新第 $i$ 轮时，我们将前 $i-1$ 轮所有标记的点从原图删去，如果一个尚未被标记点 $j$ 满足在原图上是一个公车 $q$ 的最短路径的必经点且满足 $j$ 在当前的图上到达车 $q$ 的终点的距离发生改变，则点 $j$ 则为我们这一轮需要求的点，将其标记。

初始时标记上点 $t$（即终点）。

至于为什么不能从起点 $s$ 开始删，可以看文章开头写出的结论。

---

