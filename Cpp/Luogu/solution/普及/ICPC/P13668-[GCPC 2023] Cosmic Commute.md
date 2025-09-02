# [GCPC 2023] Cosmic Commute

## 题目描述

很久很久以前，在一个遥远的星系中，星际通道公司（ICPC）运营着一个复杂的铁路系统，使用着“光速列车”。

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/8bjjmufd.png)

盖利弗雷上方的虫洞，图片来源：[mau\_king](https://pixabay.com/de/photos/milchstra\%c3\%9fe-wurmloch-5904640/)
:::

每个星球恰好有一个火车站，每列光速列车连接两个不同的星球，并在它们之间往返运行。
最近，星际通道公司建立了一个传送系统，目前正处于测试阶段。
一些火车站现在扩建了一个“虫洞”。
所有虫洞彼此相连，可以瞬间从一个虫洞传送到另一个虫洞。
为了不让新系统过载，每个星系公民每天最多只能使用一次传送。

查理住在盖利弗雷星球，在桑塔星球工作。
今天是她第一天上班，但她已经迟到了，因为她愚蠢的闹钟没有响。
更糟糕的是，今天偏偏传送系统还出现了故障，无法选择目的地虫洞。
现在，进入虫洞后，会被随机传送到所有其他虫洞中的某一个（每个虫洞被选中的概率相同）。
（不可能在传送后还停留在同一个火车站。）

尽管运气很差，查理还是决心按时到达公司。
由于所有光速列车都很慢，她希望乘坐尽可能少的光速列车。
如果她最多只能使用一次（故障的）传送系统，求她到达公司的最小期望乘坐光速列车次数。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 5 3
2 3 4
1 2
1 3
2 4
3 4
4 5```

### 输出

```
5/2```

## 样例 #2

### 输入

```
5 6 3
2 3 4
1 2
1 3
2 4
3 4
4 5
1 4```

### 输出

```
2/1```

# 题解

## 作者：__CuSO4__ (赞：1)

### 题意概述

给你一个 $n$ 个结点的无向连通图，边权都为 $1$，标记 $k$ 个虫洞结点，从一个虫洞结点进行传送操作会**随机**地跳转到另一个虫洞结点（最多只能进行**一次**）。

求从 $1$ 号结点到 $n$ 号结点最小的**期望**距离，用 `x/y` 的分数形式输出。

### 题解

记 $W$ 为虫洞结点的集合，$d(u,v)$ 表示 $u$ 到 $v$ 最小的距离。

首先，分是否进行传送操作两种情况。

如果不进行，距离就是 $d(1,n)$。

如果进行，考虑对于虫洞节点 $u$，从 $1$ 到 $u$ 最短距离为 $d(1,u)$，然后随机传送到另一个虫洞结点 $v$ 再到 $n$ 的最短距离为 $dis(v,n)$（概率 $\frac{1}{k-1}$）。

所以总**期望**距离为 $\min_{w \in W} \left( d(1,w) + \frac{1}{k-1} \sum_{w' \in W, w'\ne w} d(w',n) \right)$。

这个式子直接求肯定超时，但注意到，$\sum_{w' \in W, w'\ne w} d(w',n)=(\sum_{w' \in W} d(w',n))-d(w,n)$，其中 $\sum_{w' \in W} d(w',n)$ 可以预处理出来，$d(w,n)$ 是为 $n$ 到其它节点的距离，也可以预处理，那么就可做了。

最终先跑两遍 `bfs`，分别从 $1$ 和 $n$ 出发，计算出起点到所有点的距离，再枚举每个虫洞结点，按照上面的式子计算答案即可。

### 代码
``` cpp
#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a,long long b) { return b?gcd(b,a%b):a; }
struct frac { long long x,y; } ans;//为了方便重载了运算符
frac operator+(frac a, frac b)
{
    frac res={a.x*b.y+a.y*b.x, a.y*b.y};
    long long t=gcd(res.x, res.y);
    return {res.x/t,res.y/t};
}
bool operator<(frac a,frac b) { return a.x*b.y<b.x*a.y; }
int n,m,k;
int a[200005],vis[200005],dis1[200005],disn[200005];
long long sum;
vector<int> v[200005];
void bfs(int st,int dis[]) {//bfs板子
    queue<int>q;
    memset(vis,0,sizeof(vis));
    q.push(st),vis[st]=1,dis[st]=0;
    while (!q.empty()) {
        int x=q.front();q.pop();
        for(int y:v[x]) if(!vis[y]) dis[y]=dis[x]+1,vis[y]=1,q.push(y);
    }
}

int main() {
    memset(dis1,0x3f,sizeof(dis1)),memset(disn,0x3f,sizeof(disn));
    ios::sync_with_stdio(0),cin.tie(0);
    cin >>n>>m>>k;
    for (int i=1;i<=k;i++) cin>>a[i];
    for (int i=1,x,y;i<=m;i++) cin>>x>>y,v[x].push_back(y),v[y].push_back(x);
    bfs(1,dis1),bfs(n,disn);
    for (int i=1;i<=k;i++) sum+=disn[a[i]];
    ans={1000000000000,1};//初始化为极大值
    for(int i=1;i<=k;i++) ans=min(ans,frac{dis1[a[i]],1}+frac{sum-disn[a[i]],k-1});
    ans=min(ans,frac{dis1[n],1});//注意要考虑不走虫洞的方案
    cout<<ans.x<<'/'<<ans.y;
    return 0;
}
```

---

## 作者：枫原万叶 (赞：0)

附上一个中文题面：[题面链接](https://www.luogu.me/paste/umi4dksb#)

简单翻译一下，就是在一个无向图中有一些可以互相传送的结点，求结点一到结点 $n$ 的最小期望距离（如果选择在一个星球 $x$ 使用虫洞，期望就等于到星球 $x$ 的虫洞距离与传送到其它虫洞后到星球 $n$ 距离的平均值的和）。

可能还是有些难以理解，那我拿样例一解释一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/prbkvowz.png)

以上为样例一中表示的图，打红钩表示为有虫洞的星球。

先计算从一出发到每各虫洞的最短距离：

到星球二距离为 $1$，到星球三距离为 $1$，到星球四距离为 $2$（这里应该可以理解吧，就是每个边的边权为 $1$ 然后找最短距离）。

再计算每个虫洞到 $n$ 的最短距离，星球 $2$、$3$、$4$ 分别为 $3$、$2$、$1$。

最后即可得到各期望为：$2.5$、$3$、$4.5$。

那么最小期望即为 $\frac{5}{2}$。

这样解释之后相信你应该有思路了。

用 BFS 跑一遍从一出发到各星球的最短距离以及终点到每个星球的最短距离。

计算一下所有虫洞结点到终点 n 的距离之和 $S=\sum dis^n_w$。

期望 $=$ 从 $1$ 到 $w$ 的距离 $+$（其他虫洞到 $n$ 的距离平均值）$ = dist^1_w + \frac{S - dist^n_w}{k-1}$

最后比较一下不使用虫洞与最小期望中的较小值，并用分数表示。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;

vector<int> g[N];
int d1[N],dn[N],w[N],n,m,k,u,v,S;
queue<int> q;

void bfs(int s,int*d){
    for(int i=1;i<=n;i++)d[i]=-1;
    for(q.push(s),d[s]=0;!q.empty();){
        u=q.front();q.pop();
        for(int i=0;i<g[u].size();i++)
            if(d[v=g[u][i]]==-1)d[v]=d[u]+1,q.push(v);
    }
}

int gcd(int a,int b){return b?gcd(b,a%b):a;}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<k;i++)scanf("%d",&w[i]);
    while(m--)scanf("%d%d",&u,&v),g[u].push_back(v),g[v].push_back(u);
    
    bfs(1,d1);bfs(n,dn);
    
    for(int i=0;i<k;i++)S+=dn[w[i]];
    long long mn=1LL<<60,t;
    for(int i=0;i<k;i++)
        t=(k-1LL)*d1[w[i]]+S-dn[w[i]],mn=t<mn?t:mn;
    
    int a=d1[n]*(k-1)<=mn?d1[n]:mn,b=a==d1[n]?1:k-1,g=gcd(a,b);
    printf("%d/%d",a/g,b/g);
    return 0;
}
```

---

