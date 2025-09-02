# 「TFOI R1」Unknown Graph

## 题目背景

小 A 飘到了一个岛屿群里，这些岛屿都有单向桥相连接，没有两座桥连接的起始岛屿和终止岛屿都相同，更不会有桥连接一个岛屿。

但这里全是迷雾，小 A 在一个岛上只能看到这个岛与多少座桥相连。

小 A 想要知道整个岛屿群的形态，但是他并不会，所以找到了你。

如果有多种情况，你只需要告诉小 A 任意一种就行。

## 题目描述

有一张 $n$ 个节点的**无重边无自环的有向图**（可以不连通），每个节点的编号为 $1 \sim n$，你知道每个节点的入度和出度。

另外还有 $m$ 条限制，每条限制给定两个点 $x_{i}$ 和 $y_{i}$，表示图中不存在有向边 $(x_{i}, y_{i})$，请你求出一种满足要求的图的形态。

若有多种情况，输出任意一种即可，保证有解。

## 说明/提示

**本题采用捆绑测试**。

- Subtask 1（10 points）：$n \leqslant 10$。
- Subtask 2（10 points）：$n = 10^3$，$a_{i} = b_{i} = 1$，$m = 0$。
- Subtask 3（20 points）：$n \leqslant 100$。
- Subtask 4（60 points）：无特殊限制。

对于所有数据，$2 \leqslant n \leqslant 10^{3}$，$0 \leqslant a_{i}, b_{i} < n$，$1\leqslant \sum{a_i} \leqslant 10^{5}$，$0 \leqslant m \leqslant 5 \times 10^4$，$1 \leqslant x_i,y_i \leqslant n$。

## 样例 #1

### 输入

```
4
2 3 2 3
2 3 2 3
1
1 3```

### 输出

```
10
1 2
2 1
2 3
3 2
2 4
4 2
4 1
1 4
4 3
3 4```

# 题解

## 作者：keep_of_silence (赞：7)

## 思路

题目给出了每个点的初度和入度，由于图是**无重边无自环的有向图**。

要求满足限制的图有多少条边与建图方案。

我们可以考虑使用网络流中的**最大流**。

我们知道这是一道网络流后，题目的难点就转移到网络流的建模以及输出方案的办法。

### 网络流的建模：

题目所给的条件没有源点汇点并指出图可以**不连通**，所以考虑设立一个超级源点 $S$ 以及汇点 $T$。

由于有入度和初度的要求，图是**有向图**。

考虑**拆点**。

将每一个点拆成两个点，一个代表由其他点连向自己，即入度。

反之同理，另一个点代表自己连向其他点，即出度。

针对由有些边不能连，由于本题数据较小，我们可以使用一个邻接矩阵来存该边可不可以连。

注意：**没有自环**，所以自己不能连自己。

所以综上所述，本题的建模规则：

1：每个点的**入度连向汇点**，**流量为入度 $a _ {i}$**。

2：**源点连向**每个点的**出度**，**流量为出度 $b _ {i}$**。

3：可以连的边，**起点的出度点连向终点的入读点**，**流量为 1**（**没有重边**）。

保证有解，所以建模规则 1 和 2 中的连的边满流。

然后就可以跑一遍最大流 Dinic 板子。

### 输出方案：

连的边必然是建模规则 3 中连的边，当该边被选中时必然**满流**（因为流量只有 1）。

但这种边一定是由出度点连向入读点。

下面给出代码：

## 代码

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define inf 1e9
using namespace std;
int n,m,s,t;
int mapp[1005][1005]; 

int cnt=-1;
struct N{
    int from,to,next,val;
};N p[10000005];
int head[8005],cur[8005],d[8005];

inline void add(int a,int b,int c)
{
    ++cnt;
    p[cnt].from=a;
    p[cnt].next=head[a];
    head[a]=cnt;
    p[cnt].to=b;
    p[cnt].val=c;
    return ;
}

inline int bfs()
{
    queue<int> q;
    q.push(s);
    memset(d,-1,sizeof(d));
    d[s]=0;
    while(q.size()>0)
    {
        int u=q.front();
        q.pop();
        for(int i=head[u];i!=-1;i=p[i].next)
        {
            int v=p[i].to;
            if(d[v]==-1&&p[i].val>0)
            {
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
    if(d[t]==-1) return 0;
    else return 1;
}

inline int dfs(int u,int limit)
{
    if(u==t||!limit) return limit;
    int sum=0,flow=0;
    for(int i=cur[u];i!=-1;i=p[i].next)
    {
        int v=p[i].to;
        cur[u]=i;
        if(d[v]==d[u]+1&&p[i].val>0)
        {
            sum=dfs(v,min(p[i].val,limit));
            p[i].val-=sum;
            p[i^1].val+=sum;
            flow+=sum;
            limit-=sum;
            if(!limit) break;
        }
    }
    if(!flow) d[u]=-1;
    return flow;
}

inline void dinic()
{
    int ans=0;
    while(bfs())
    {
        for(int i=0;i<=t;i++) cur[i]=head[i];
        ans+=dfs(s,inf);
    }
    cout<<ans<<endl;
    return ;
}//板子 

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    memset(head,-1,sizeof(head));//s=0,memset head数组为-1 
    cin>>n;
    s=0,t=2*n+1;
    int a,b;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        add(i+n,t,a),add(t,i+n,0);//建模规则1 
    }
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        add(s,i,a),add(i,s,0);//建模规则2
    }
    //拆点：这里我们将出度点的编号设为1-n,入度点就是n+1-2*n,所以汇点t可设为2*n+1 
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        mapp[a][b]=1;//邻接矩阵
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(mapp[i][j]==0&&i!=j)//当此边没有被限制且不是自己连向自己时 
            {
                add(i,n+j,1),add(n+j,i,0);//连边 
            }
        }
    }
    dinic();
    for(int i=4*n-1;i<=cnt;i++)//建图规则3中连的边cnt值从4*n-1到cnt 
    {
        if(i%2==0&&p[i].val==0)//是从出度连向入度的边且满流了(val值为0) 
        {
            cout<<p[i].from<<" "<<p[i].to-n<<endl;//输出时入度点要记得减去n 
        }
    }
    return 0;
} 
```

---

## 作者：Astatinear (赞：1)

这里是出题人题解。

### $\text{Solution Of  \ Problem C : Unknown Graph.}$

题意还是很清晰的，这里就不再赘述题意了。

首先如果没有 $q$ 的限制，显然有一种贪心思想就是每个点每次选剩余入度最多的与之连边。但是因为限制，就无法保证贪心的正确性。

那该怎么办呢？

一个大提示：这题是一道网络流。（您都看到这里了不会还不会做吧。

感觉如果知道算法是网络流的话，这题应该挺版的。建模方法如下：

+ 源点与所有点 $i$ 建立容量为 $in_i$ 的边。

+ 所有点 $i+n$ 与汇点建立容量为 $out_i$ 的边。（$in,out$ 分别表是入度和出度）

+ 对于任意两个点 $i,j$ 如果 $i\not=j$ 且 $i,j$ 之间可以连边的话（即没有被限制），将 $i,j+n$ 建立一条容量为 $1$ 的边。

最后跑一遍最大流，由于保证了有解，所以跑完之后肯定是满流。

由于这个图是一个近似二分图，而完全优化的 Dinic 在二分图的复杂度是 $\Theta(m\sqrt n)$，此处，$m≈n^2$，故是可行的。

输出方案的话，就是如果建立的第三种边容量是 $1$，就说明 $i$ 向 $j$ 连了一条边。

总的来说，这题难点在于想到这题是一道网络流，其他部分还是比较好理解的，输出方案也并不难。

---

## 作者：luxiaomao (赞：0)

## [P9705](https://www.luogu.com.cn/problem/P9705#submit) 网络流题

赛时不会最大流乱糊了一个贪心，学会了最大流之后就很轻松 A 了。在任务计划里拖了几个月，才发现这题可以写题解，那就写一篇罢。

## Solution
 
 题意很好理解，不多说。
 
 我们先设置超级源点 $S$ 和超级汇点 $T$。
 
 鉴于有流量的限制，我们可以祭出网络流最经典的解法：拆点。将一个点 $i$ 拆为两个 $i_1$ 和 $i_2$，一个负责处理流进来的流量（入度），把这些流量流进 $T$；另一个负责从 $S$ 引来流量，并将这些流量流向别的点（出度）。
 
 至于 $m$ 组限制呢，我们可以开一个二维数组存一下没有被限制的所有边，然后把这些边建上，流量为 $1$（按照题意），此时注意不能连出自环（也是题目的要求）
 
 总结一下建模要求：
 
 - 对于每个 $a_i$，$i_2$ 向 $T$ 建边，流量为 $a_i$。
 
 - 对于每个 $b_i$，$S$ 向 $i_1$ 建边，流量为 $b_i$。
 
 - 对于每组符合要求的边，$u_1$ 向 $v_2$ 建边，流量为 $1$。
 
 输出方案时看看那些边被流满即可。
 
 ## Code
 
 ```cpp
#include<bits/stdc++.h>
#define N 2005
#define M 3000005
#define inf 1000000000
using namespace std;

int n,m,s,t,ans;
bool flag[1005][1005];
struct edge{int u,v,w,nex;}e[M];
int tot = 1,head[N];

void add(int u,int v,int w)
{
	e[++tot].u = u,e[tot].v = v,e[tot].w = w;
	e[tot].nex = head[u],head[u] = tot;
	e[++tot].u = v,e[tot].v = u,e[tot].w = 0;
	e[tot].nex = head[v],head[v] = tot;
}

int dis[N],now[N];

bool bfs()
{
	for(int i = s;i <= t;i++)dis[i] = inf;
	queue<int> q;
	dis[s] = 0;
	q.push(s),now[s] = head[s];
	while(!q.empty())
	{
		int u = q.front();q.pop();
		for(int i = head[u];i;i = e[i].nex)
		{
			int v = e[i].v;
			if(e[i].w == 0 || dis[v] != inf)continue;
			dis[v] = dis[u] + 1;
			q.push(v),now[v] = head[v];
			if(v == t)return 1;
		}
	}
	return 0;
}

int dfs(int u,int sum)
{
	if(u == t)return sum;
	int ret = 0,k;
	for(int i = now[u];i && ret < sum;i = e[i].nex)
	{
		now[u] = e[i].nex;
		int v = e[i].v;
		if(e[i].w == 0 || dis[u]+1 != dis[v])continue;
		k = dfs(v,min(sum,e[i].w));
		if(k == 0)dis[v] = inf;
		e[i].w -= k;
		e[i^1].w += k;
		sum -= k,ret += k;
	}
	return ret;
}

int main()
{
	scanf("%d",&n);
	s = 0,t = 2*n+1;
	for(int i = 1;i <= n;i++)
	{
		int a;
		scanf("%d",&a);
		add(i+n,t,a);
	}
	for(int i = 1;i <= n;i++)
	{
		int a;
		scanf("%d",&a);
		add(s,i,a);
	}
	scanf("%d",&m);
	while(m--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		flag[u][v] = 1;
	}
	for(int u = 1;u <= n;u++)
		for(int v = 1;v <= n;v++)
			if(u != v && !flag[u][v])add(u,v+n,1);
	while(bfs())ans += dfs(s,inf);
	printf("%d\n",ans);
	for(int u = 1;u <= n;u++)
		for(int i = head[u];i;i = e[i].nex)
		{
			int v = e[i].v;
			if(v && e[i].w==0)printf("%d %d\n",u,v-n);
		}
	return 0;
}
```

---

## 作者：rechenz (赞：0)

一道有趣简单的构造题。

阅读题面，发现这似乎很难找到完美的贪心策略，那么我们考虑网络流。

先说建模方式：

考虑拆点，把每个点拆成编号为 $i$ 和 $n+i$ 的两个点。

首先从超级源点 $s$ 向编号为 $1 \sim n$ 的每一个点连流量为这个点出度的边。

然后再从 $1 \sim n$ 的点向每一个编号为 $n+1$ 到 $2n$ 流量为 $1$ 的边，当然因为题中给出了 $m$ 条限制，那么不对这些限制的点进行连边就好了。

最后从编号为 $n+1$ 到 $2n$ 的点向超级汇点 $t$ 连一条流量为这个点入度的边就好了。

大概建了个这么个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/v1e0uaot.png)

那么边数就是这个网络的最大流（因为保证有解），至于怎么输出构造的边，我们去遍历这个网络的残余流量，如果第二步建的正向边的流量为 $0$ 那么就说明这条边被我们选择了，我们输出这条边的两个节点就好。

然后因为这是个二分图，那么我们的复杂度就是优秀的 $O(n\sqrt n)$。

这道题其实就是直接对着题意进行网络流模拟，是一道很好的板子题。

如果还没理解就看看代码，自认为很好看（

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
const int inf=1e9+7;
int n,m,in[N],out[N],head[2*N],cnt=1,s,t,mp[N][N],num=1;
struct Edge{
    int from;
    int to;
    int next;
    int wide;
}e[2*N*N+2*N];

void adding(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].from=u;
    e[cnt].wide=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}

int dis[2*N],now[2*N];

bool BFS(){
    for(int i=1;i<=2*n+1;i++){
        dis[i]=inf;
    }
    dis[s]=0;
    queue<int>q;
    q.push(s);
    now[s]=head[s];
    while(q.size()){
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=e[i].next){
            int v=e[i].to;
            // cout<<x<<" "<<v<<endl;
            if(dis[v]==inf&&e[i].wide){
                dis[v]=dis[x]+1;
                now[v]=head[v];
                q.push(v);
            }
        }
    }
    return dis[t]!=inf;
}

int DFS(int x,int sum){
    if(x==t) return sum;
    int k,res=0;
    for(int i=now[x];i&&sum;i=e[i].next){
        int v=e[i].to;
        now[x]=i;
        if(dis[v]==dis[x]+1&&e[i].wide){
            k=DFS(v,min(e[i].wide,sum));
            if(k==0){
                dis[v]=inf;
            }
            e[i].wide-=k;
            e[i^1].wide+=k;
            sum-=k;
            res+=k;
        }
    }
    return res;
}

int Dinic(){
    int res=0;
    while(BFS()){
        res+=DFS(s,inf);
    }
    return res;
}

void Debug(){
    for(int x=0;x<=2*n+1;x++){
        for(int i=head[x];i;i=e[i].next){
            int v=e[i].to;
            cout<<x<<" "<<v<<" "<<e[i].wide<<endl;
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&in[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&out[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int s1,s2;
        scanf("%d%d",&s1,&s2);
        mp[s1][s2]=1;
    }
    s=0,t=2*n+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            if(mp[i][j]) continue;
            adding(i,j+n,1);
            adding(j+n,i,0);
            num+=2;
        }
    }
    for(int i=1;i<=n;i++){
        adding(s,i,out[i]);
        adding(i,s,0);
    }
    for(int i=n+1;i<=2*n;i++){
        adding(i,t,in[i-n]);
        adding(t,i,0);
    }
    Debug();
    printf("%d\n",Dinic());
    for(int i=2;i<=num;i+=2){
        if(!e[i].wide){
            printf("%d %d\n",e[i].from,e[i].to-n);
        }
    }
    return 0;
}
```


---

