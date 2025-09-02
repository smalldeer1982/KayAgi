# [NERC2024] Managing Cluster

## 题目描述

你打算开发一个集群管理扩展，以提升产品性能。你的产品包含 $n$ 个服务（编号从 $1$ 到 $n$），运行在一个拥有 $2n$ 台机器（编号从 $1$ 到 $2n$）的集群上。每个服务运行恰好两个副本，每个副本部署在某台机器上。每台机器恰好运行一个服务的副本。

这个集群性能的关键因素之一是网络结构。一些机器之间存在直接连接，能够高效传输数据。一共存在 $2n - 1$ 条直接连接，并且任意两台机器之间都可以通过这些连接实现通信。换句话说，这些直接连接构成了一棵树。

部署过程中，$2n$ 个副本已分配到机器。你的扩展程序将获取所有直接连接的信息，以及一个长度为 $2n$ 的序列 $a_1,a_2,\ldots,a_{2n}$，其中 $a_i$ 表示第 $i$ 台机器上运行的服务编号。

你的程序可以对副本进行交换操作。一次交换操作选定两台机器 $i$ 和 $j$，交换 $a_i$ 和 $a_j$ 的值。每台机器最多参与一次交换操作。

你需要设计一组交换操作，以使集群性能最大化。

由于同一服务的两个副本之间的数据交换最为频繁，集群性能定义为：有多少个服务的两个副本位于一对直接连接的机器上。

请你编写程序，输出一组交换操作，使得集群性能最大。

## 说明/提示

在第一个测试用例中，只有服务 $2$ 的两个副本处于相邻的机器上，因此性能为 $1$。通过交换机器 $1$ 和 $3$ 上的副本，可以使服务 $1$ 和服务 $2$ 的副本都位于相邻机器上，性能提升至 $2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/6cp342uy.png)

在第二个测试用例中，没有任何服务的副本处于相邻机器上，初始性能为 $0$。通过交换 $(1,5)$，$(8,3)$ 和 $(4,7)$ 三对机器，可以让服务 $2$、$3$ 和 $4$ 的副本分别配对，从而性能提升到 $3$。可以证明此时无法再提升至 $4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ljhz2pf2.png)

在第三个测试用例中，只有服务 $1$ 的两个副本在相邻机器上，性能为 $1$，且无法进一步提升。

![](https://cdn.luogu.com.cn/upload/image_hosting/ss4oj9ok.png)

## 样例 #1

### 输入

```
3
2
1 2 2 1
1 2
2 3
3 4
4
4 3 1 3 2 4 1 2
1 2
3 1
3 4
5 1
5 6
2 7
2 8
3
1 1 2 2 3 3
1 2
1 3
1 4
1 5
1 6```

### 输出

```
1
1 3
3
1 5
8 3
4 7
0```

# 题解

## 作者：FFTotoro (赞：7)

使用贪心或者 DP 求解一个树上的最大匹配 $M=\{(u_1,v_1),(u_2,v_2),\ldots,(u_k,v_k)\}$，则答案不会超过 $k$。

大胆猜测答案一定可以取到 $k$，以下是构造方法：

对于上面的最大匹配 $M$，构造一个有 $n$ 个结点的无向图 $G$，连边 $a_{u_i}\leftrightarrow a_{v_i}(1\le i\le k)$。由于原树上每个结点在最大匹配中最多出现一次，而 $a_i$ 在 $a$ 中恰好出现两次，所以该图中结点度数不超过 $2$。

我们先引入一个叫做“缩二度点”的操作：假设在 $G$ 中，对于结点 $x$ 有边 $x\leftrightarrow y$ 和 $x\leftrightarrow z$，那么意味着在最大匹配中有两条边满足 $a_{u_i}=x,a_{v_i}=y$ 和 $a_{u_j}=x,a_{v_j}=z$；此时交换 $v_i,u_j$，即可以将匹配中的边调整为 $a_{u_i}=a_{v_i}=x$ 和 $a_{u_j}=y,a_{v_j}=z$——对应到 $G$ 中，相当于删除了边 $x\leftrightarrow y$ 和 $x\leftrightarrow z$（$x$ 直接满足条件，可以不管了），加入了一条新边 $y\leftrightarrow z$，十分类似广义串并联图中的“缩二度点”操作。

考察 $G$ 的性质，由于结点度数不超过 $2$，所以 $G$ 中的每个连通块要么是一个环，要么是一条链：使用上面的“缩二度点”操作，一个环可以被缩成一个单点（即环上所有结点全部调整完毕），而一条链最后必然被缩成 $x\leftrightarrow y$ 的形态：思考造成这种现象的本质，由于这两个结点度数都为 $1$，那么满足 $a_i=x$ 的某个 $i$ 必然没有被选入最大匹配中！此时只需要将 $y$ 在匹配中对应的结点和那个没被选入的 $i$ 交换即可。

根据不同实现，时间复杂度为 $O(n\log n)$ 或 $O(n)$。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
vector<pii> matching(vector<vector<int> > g){
  vector<bool> b(g.size());
  vector<pii> r;
  function<void(int,int)> dfs=[&](int u,int f){
    for(int i:g[u])
      if(i!=f)dfs(i,u);
    if(u&&!b[u]&&!b[f])
      r.emplace_back(u,f),b[u]=b[f]=true;
  };
  return dfs(0,0),r;
} // 求最大匹配
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t; cin>>t;
  while(t--){
    int n; cin>>n;
    vector<int> a(n<<1);
    for(auto &i:a)cin>>i,i--;
    vector<vector<int> > g(n<<1),c(n);
    for(int i=1;i<n<<1;i++){
      int u,v; cin>>u>>v;
      g[--u].emplace_back(--v);
      g[v].emplace_back(u);
    }
    auto m=matching(g);
    vector<set<int> > s(n);
    vector<int> p(n<<1,-1);
    for(int i=0;i<n<<1;i++)
      s[a[i]].emplace(i);
    for(auto [x,y]:m){
      p[x]=y,p[y]=x;
      c[a[x]].emplace_back(a[y]);
      c[a[y]].emplace_back(a[x]);
    } // 基于最大匹配建图
    vector<bool> b(n),b2(n<<1);
    vector<pii> r;
    auto solve=[&](int x){
      vector<int> v;
      function<void(int)> dfs=[&](int u){
        b[u]=true,v.emplace_back(u);
        for(int i:c[u])
          if(!b[i])dfs(i);
      };
      dfs(x); // 找环 / 链
      auto op=[&](int u,int v){
        int w=0,x=-1,y=-1;
        for(int i:s[u])w^=i;
        for(int i:s[u])
          for(int j:s[v])
            if(p[i]==j&&!b2[w^i])x=w^i,y=j;
        r.emplace_back(x,y),b2[x]=b2[y]=true;
        s[v].erase(y),s[v].emplace(x);
      }; // “缩二度点”操作
      for(int l=v.size()-1>>1,r=l+1,f=1;0<=l&&r<v.size();(f=!f)?r++:l--)
        f?op(v[l],v[r]):op(v[r],v[l]); // 在链 / 环上缩点
    };
    for(int i=0;i<n;i++)
      if(c[i].size()==1&&!b[i])solve(i); // 链
    for(int i=0;i<n;i++)
      if(c[i].size()==2&&!b[i])solve(i); // 环
    cout<<r.size()<<'\n';
    for(auto [x,y]:r)
      cout<<x+1<<' '<<y+1<<'\n';
  }
  return 0;
}
```

---

