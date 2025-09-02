# [GCJ 2021 #3] Square Free

## 题目描述

我们有一个由正方形单元格组成的矩阵，包含 $\mathbf{R}$ 行和 $\mathbf{C}$ 列。我们需要在每个单元格中绘制一条对角线。每个单元格必须且只能绘制两种对角线之一：**正斜杠对角线（/）**（连接单元格的左下角和右上角）或 **反斜杠对角线（\）**（连接单元格的左上角和右下角）。

对于每一行和每一列，我们需要绘制特定数量的正斜杠对角线。此外，在所有对角线绘制完成后，矩阵必须满足**无方格**条件。即，不能存在由所绘制的对角线构成的正方形。

例如，假设我们有一个 4 行 4 列的矩阵。每行旁边的数字表示该行必须绘制的正斜杠对角线的确切数量，每列下方的数字表示该列必须绘制的正斜杠对角线的确切数量。

![](https://cdn.luogu.com.cn/upload/image_hosting/xc6yu1qy.png)

存在多种方式填充该矩阵以满足每行和每列的要求。以下是三种可能的填充方式：

![](https://cdn.luogu.com.cn/upload/image_hosting/1gul8pxa.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/xip3jkqs.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/o3qbkh80.png)

前两个矩阵**不满足无方格条件**，而第三个矩阵满足。在第一个矩阵中，存在一个边长为 2 的对角线组成的正方形，其顶点位于矩阵各边的中点；在第二个矩阵中，右下角存在一个边长为 1 的对角线组成的正方形；第三个矩阵则不存在任何此类正方形。因此，第三个矩阵是符合所有规则的合法填充方案。

给定矩阵的大小以及每行和每列必须绘制的正斜杠对角线的数量，请构造一个满足行和列约束的无方格矩阵，或者判断这样的矩阵不存在。


## 说明/提示

**样例解释**

样例 #1 是题目描述中提到的示例。

在样例 #2 中，根据行的总和，需要绘制 2 条正斜杠对角线，但根据列的总和，需要绘制 3 条。因此无法满足所有规则。

样例 #3 中唯一满足行和列约束的矩阵如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/qrbza4hc.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/439fpaug.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/ib6vqil8.png)

由于前两个矩阵包含正方形，第三个矩阵是唯一合法的输出。

在样例 #4 中，只有一种填充方式满足行和列约束（如下图所示）。注意，它产生了一个矩形（图中蓝色部分），但由于该矩形不是正方形，因此矩阵满足无方格条件。

![](https://cdn.luogu.com.cn/upload/image_hosting/ljxlouhx.png)

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- 对于所有 $i$，$0 \leq \mathbf{S}_i \leq \mathbf{C}$。
- 对于所有 $i$，$0 \leq \mathbf{D}_i \leq \mathbf{R}$。

**测试集 1（7 分，可见判定）**

- $2 \leq \mathbf{R} \leq 6$。
- $2 \leq \mathbf{C} \leq 6$。

**测试集 2（13 分，隐藏判定）**

- $2 \leq \mathbf{R} \leq 20$。
- $2 \leq \mathbf{C} \leq 20$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4 4
3 2 3 3
3 3 2 3
2 3
1 1
1 1 1
2 3
1 2
1 1 1
3 3
2 0 2
2 0 2```

### 输出

```
Case #1: POSSIBLE
//\/
\/\/
///\
/\//
Case #2: IMPOSSIBLE
Case #3: POSSIBLE
\\/
//\
Case #4: POSSIBLE
/\/
\\\
/\/```

# 题解

## 作者：FFTotoro (赞：1)

网络流题。看到这种限制行和与列和的题目，考虑网络流建模：对于每一行、每一列建立一个点，源点向行对应的点连流量为行和的边，列对应的点向汇点连流量为列和的边，行列之间连流量为 $1$ 的边，跑最大流就可以得出一组不考虑“正方形”的方案。判断无解很容易，只需要检查一下最大流是否等于整个网格需要的 `/` 的个数即可。

剩下情况均为有解，因为可以通过如下的方式将让所有“正方形”消失：考虑把一对相邻行出现的 `/...\`（上一行）`\.../`（下一行）全部变成 `\.../`（上一行）`/...\`（下一行），就能拆掉一个可能的正方形，并且不会影响行列和的条件。但是可能会出现新的正方形，于是每次就暴力找可以拆的——最多会拆 $O((RC)^2)$ 次（而且常数极小），直接模拟时间复杂度就是对的。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IAOI_lib{
  template<typename C> class mf_graph{
    private:
      typedef pair<int,int> pii;
      int n;
      vector<vector<pii> > g;
      inline void add(int u,int v,C w){
        g[u].emplace_back(v,e.size());
        e.emplace_back(u,v,w,0);
      }
    public:
      struct edge{
        int u,v; C c,f;
        edge(int u,int v,C c,C f):u(u),v(v),c(c),f(f){}
      };
      vector<edge> e;
      mf_graph(int n):n(n),g(n){}
      inline void add_edge(int u,int v,C w){
        add(u,v,w),add(v,u,0);
      }
      edge get_edge(int x){return e[x<<1];}
      vector<edge> edges(){
        vector<edge> r;
        for(int i=0;i<e.size();i+=2)
          r.emplace_back(e[i]);
        return r;
      }
      C flow(int s,int t,C l=numeric_limits<C>::max()){
        C r=0;
        vector<int> d(n),p(n);
        auto dfs=[&](auto &&self,int u,C l)->C{
          if(u==t)return l;
          C r=0;
          for(int &i=p[u];i<g[u].size();i++){
            auto [v,x]=g[u][i];
            if(d[v]==d[u]+1&&e[x].c>e[x].f){
              C f=self(self,v,min(l-r,e[x].c-e[x].f));
              if(f){
                e[x].f+=f,e[x^1].f-=f,r+=f;
                if(l==r)return r;
              }
            }
          }
          return d[u]=-1,r;
        };
        while(1){
          fill(d.begin(),d.end(),-1),d[s]=0;
          queue<int> q; q.emplace(s);
          while(!q.empty()){
            int u=q.front(); q.pop();
            for(auto [i,x]:g[u])
              if(d[i]<0&&e[x].c>e[x].f)
                d[i]=d[u]+1,q.emplace(i);
          }
          if(d[t]<0)break;
          fill(p.begin(),p.end(),0);
          C f=dfs(dfs,s,l-r);
          if(!f)break;
          r+=f;
        }
        return r;
      }
  }; // 网络最大流模板
}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int tt; cin>>tt;
  for(int t=1;t<=tt;t++){
    int n,m; cin>>n>>m;
    IAOI_lib::mf_graph<int> g(n+m+2);
    vector<int> a(n),b(m);
    for(int i=0;i<n;i++)
      for(int j=0;j<m;j++)
        g.add_edge(i,j+n,1);
    for(int i=0;i<n;i++)
      cin>>a[i],g.add_edge(n+m,i,a[i]);
    for(int i=0;i<m;i++)
      cin>>b[i],g.add_edge(i+n,n+m+1,b[i]);
    int f=g.flow(n+m,n+m+1); // 跑最大流
    cout<<"Case #"<<t<<": ";
    if(f!=accumulate(a.begin(),a.end(),0)
      ||f!=accumulate(b.begin(),b.end(),0)){
      cout<<"IMPOSSIBLE\n"; continue;
    } // 无解情况
    auto e=g.edges();
    vector<string> s(n,string(m,'\\'));
    for(int i=0;i<n;i++)
      for(int j=0;j<m;j++)
        if(e[i*m+j].f)s[i][j]='/';
    while(1){
      bool f=true;
      for(int xa=0;xa<n-1;xa++)
        for(int ya=0;ya<m;ya++){
          int xb=xa+1;
          for(int yb=ya+1;yb<m&&f;yb++)
            if(s[xa][ya]=='/'&&s[xa][yb]=='\\'&&s[xb][ya]=='\\'&&s[xb][yb]=='/')
              swap(s[xa][ya],s[xa][yb]),swap(s[xb][ya],s[xb][yb]),f=false;
        }
      if(f)break;
    } // 暴力模拟拆正方形
    cout<<"POSSIBLE\n";
    for(auto i:s)cout<<i<<'\n';
  }
  return 0;
}
```

---

## 作者：Jorisy (赞：0)

首先一个必要条件是，忽略正方形这个要求，我们有一个符合个数要求的方案。

对于行列上的这类东西，一个经典 trick 是对每行每列各开一个点建图跑网络流。

假设行上的点 $i$ 连向了列上的点 $j$，边权为 $1$，如果被流了，则表示选择将 $(i,j)$ 的格子画上正斜杠。

那么将源点连向每个行上的点，边权为 $S_i$，将每个列上的点连向汇点，边权为 $D_i$。

如果存在合法方案，那么该图的最大流就恰好是 $\sum S_i=\sum D_i$。

那么假设现在已经填了一种方案，其中可能存在正方形。

考虑一个正方形，其左右两侧是 $\begin{aligned}\tt/\\[-6px]\tt\backslash\end{aligned}$ 和 $\begin{aligned}\tt\backslash\\[-6px]\tt/\end{aligned}$。也就是说，如果图内存在四个点是这种情形，那么就有可能存在正方形。我们将其变为 $\begin{aligned}\tt\backslash\\[-6px]\tt/\end{aligned}$ 和 $\begin{aligned}\tt/\\[-6px]\tt\backslash\end{aligned}$ 就好了。

数据范围很小，每次暴力找即可。

单个测试数据时间复杂度 $O(\text{MaxFlow}+R^2C^2)$。

```cpp
#include<bits/stdc++.h>
#define N 405
#define M 1005
#define ll long long
#define mod 
using namespace std;

struct edge{
    int fr,to,nxt,w;
}e[M];
int hd[N],tot=1;
void add(int u,int v,int w){e[++tot]={u,v,hd[u],w};hd[u]=tot;}
struct flows{
    int n,m,st,ed,hd[N],cur[N],dep[N];
    edge e[M];

    auto edges()
    {
        vector<edge>vec;
        for(int i=2;i<=m;i+=2) vec.push_back({e[i]});
        return vec;
    }

    void init(int p,int q,int x,int *a,int y,edge *b)
    {
        st=p,ed=q,n=x,m=y;
        for(int i=1;i<=x;i++) hd[i]=a[i];
        for(int i=1;i<=y;i++) e[i]=b[i];
    }

    bool bfs()
    {
        memset(dep,0,sizeof(dep));
        queue<int>q;
        dep[st]=1;
        q.push(st);
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            for(int i=hd[x];i;i=e[i].nxt)
            {
                auto [fr,y,nxt,w]=e[i];
                if(dep[y]||!w) continue;
                dep[y]=dep[x]+1;
                q.push(y);
                if(y==ed) return 1;
            }
        }
        return 0;
    }

    int dinic(int x,int flow)
    {
        if(x==ed||!flow) return flow;
        int rst=flow;
        for(int &i=cur[x];i;i=e[i].nxt)
        {
            auto [fr,y,nxt,w]=e[i];
            if(w&&dep[x]+1==dep[y])
            {
                int k=dinic(y,min(rst,w));
                if(!k) dep[y]=0;
                e[i].w-=k;
                e[i^1].w+=k;
                rst-=k;
            }
            if(!rst) break;
        }
        return flow-rst;
    }

    int flow()
    {
        int res=0,flow;
        while(bfs())
        {
            for(int i=1;i<=n;i++) cur[i]=hd[i];
            while(flow=dinic(st,1e9)) res+=flow;
        }
        return res;
    }
}flow;
int n,m,a[N],b[N];
char ans[N][N];

void sol()
{
    static int cas=0;
    cout<<"Case #"<<++cas<<": ";
    cin>>n>>m;
    tot=1;
    memset(hd,0,sizeof(hd));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            add(i,j+n,1);
            add(j+n,i,0);
        }
    }
    int st=n+m+1,ed=n+m+2,sa=0,sb=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sa+=a[i];
        add(st,i,a[i]);
        add(i,st,0);
    }
    for(int i=1;i<=m;i++)
    {
        cin>>b[i];
        sb+=b[i];
        add(i+n,ed,b[i]);
        add(ed,i+n,0);
    }
    flow.init(st,ed,n+m+2,hd,tot,e);
    int flw=flow.flow();
    // cerr<<"Flow = "<<flw<<'\n';
    if(flw!=sa||flw!=sb)
    {
        cout<<"IMPOSSIBLE\n";
        return;
    }
    auto e=flow.edges();
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            ans[i][j]="/\\"[e[(i-1)*m+j-1].w>0];
        }
    }
    while(1)
    {
        for(int i=1;i<n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                int k=i+1;
                for(int l=j+1;l<=m;l++)
                {
                    if(ans[i][j]=='/'&&ans[i][l]=='\\'&&ans[k][j]=='\\'&&ans[k][l]=='/')
                    {
                        ans[i][j]='\\';
                        ans[i][l]='/';
                        ans[k][j]='/';
                        ans[k][l]='\\';
                        goto lab;
                    }
                }
            }
        }
        break;
        lab:;
    }
    cout<<"POSSIBLE\n";
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cout<<ans[i][j];
        }
        cout<<'\n';
    }
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--) sol();
    return 0;
}
```

---

