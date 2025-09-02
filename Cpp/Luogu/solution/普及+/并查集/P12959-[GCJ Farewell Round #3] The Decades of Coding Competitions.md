# [GCJ Farewell Round #3] The Decades of Coding Competitions

## 题目描述

自 **Sphinny** 通过掌握竞赛排程的艺术成为顶尖编程选手以来，已经过去了近 15 年。她与 **Coding Competitions** 一同成长，并转型为一名编程竞赛组织者，而她创立的 **Programming Club League (PCL)** 已成为她所在城市最受欢迎的运动。

**Sphinny** 的城市中有 $\mathbf{N}$ 个公交站点和 $\mathbf{M}$ 条快速公交线路。每条线路双向连接两个不同的公交站点（称为端点）。由于 **PCL** 的流行，每条公交线路的司机恰好为一个俱乐部加油。

**Sphinny** 需要在第 $j$ 场比赛前从公交站点 $\mathbf{P}_j$ 取比赛材料，然后在公交站点 $\mathbf{C}_j$ 举办比赛。她只能使用给定的公交线路在两者之间通行。形式上，**Sphinny** 从 $\mathbf{P}_j$ 到 $\mathbf{C}_j$ 的路径是一个公交线路列表，其中每两条相邻线路有一个共同的端点，且第一条线路的端点为 $\mathbf{P}_j$，最后一条线路的端点为 $\mathbf{C}_j$。注意，同一条公交线路可以在路径中多次使用。如果 **Sphinny** 从 $\mathbf{P}_j$ 到 $\mathbf{C}_j$ 的路径中包含一条或多条司机为俱乐部 $c$ 加油的公交线路，则俱乐部 $c$ 会参加比赛；否则，俱乐部 $c$ 不会参加比赛。出于组织原因，**Sphinny** 需要每场比赛参加的俱乐部数量为奇数。

给定 **Sphinny** 所在城市的公交线路布局和比赛详情，计算有多少场比赛存在一条路径，使得参加的俱乐部数量为奇数。

## 说明/提示

**样例解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/axkzo8s5.png)

样例 #1 如上图所示。在前两场比赛中，无论选择哪条路径，两个俱乐部（绿色和蓝色）都必须参加。对于最后一场比赛，可以通过路径 $1, 2, 4, 5$ 仅让绿色俱乐部参加。

对于样例 #2，第一场比赛无法进行，因为没有从公交站点 $1$ 到 $2$ 的路径。第二场比赛有一条路径包含从公交站点 $1$ 到 $3$ 的唯一公交线路，因此恰好有 $1$ 个俱乐部参加，这是一个可接受的奇数。

以下附加样例（样例组 #2）符合测试集 2 的限制，但不会用于测试您的提交。

![](https://cdn.luogu.com.cn/upload/image_hosting/ycyh0jsk.png)

此附加样例如上图所示。在这种情况下，两场比赛均可通过奇数个俱乐部完成。图中展示了一条满足条件的路径。

**限制**

- $1 \leq \mathbf{T} \leq 100$。
- 对于所有 $i$，$1 \leq \mathbf{U}_i \leq \mathbf{N}$。
- 对于所有 $i$，$1 \leq \mathbf{V}_i \leq \mathbf{N}$。
- 对于所有 $i$，$\mathbf{U}_i \neq \mathbf{V}_i$。
- 对于所有 $i \neq j$，$(\mathbf{U}_i, \mathbf{V}_i) \neq (\mathbf{U}_j, \mathbf{V}_j)$ 且 $(\mathbf{U}_i, \mathbf{V}_i) \neq (\mathbf{V}_j, \mathbf{U}_j)$。（没有两条公交线路具有相同的端点对。）
- 对于所有 $j$，$1 \leq \mathbf{P}_j \leq \mathbf{N}$。
- 对于所有 $j$，$1 \leq \mathbf{C}_j \leq \mathbf{N}$。
- 对于所有 $j$，$\mathbf{P}_j \neq \mathbf{C}_j$。

**测试集 1（7 分，可见评测结果）**

- 时间限制：20 秒。
- $2 \leq \mathbf{N} \leq 500$。
- $1 \leq \mathbf{M} \leq 500$。
- $1 \leq \mathbf{Q} \leq 500$。
- 对于所有 $j$，$1 \leq \mathbf{K}_j \leq 2$。

**测试集 2（6 分，可见评测结果）**

- 时间限制：40 秒。
- $2 \leq \mathbf{N} \leq 500$。
- $1 \leq \mathbf{M} \leq 500$。
- $1 \leq \mathbf{Q} \leq 500$。
- 对于所有 $j$，$1 \leq \mathbf{K}_j \leq 100$。

**测试集 3（10 分，隐藏评测结果）**

- 时间限制：120 秒。
- $2 \leq \mathbf{N} \leq 10000$。
- $1 \leq \mathbf{M} \leq 10000$。
- $1 \leq \mathbf{Q} \leq 10000$。
- 对于所有 $j$，$1 \leq \mathbf{K}_j \leq 100$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5 5 3
1 2 1
2 3 2
2 4 1
2 5 1
4 5 1
1 3
3 4
5 1
3 1 2
1 3 1
1 2
1 3```

### 输出

```
Case #1: 1
Case #2: 1```

## 样例 #2

### 输入

```
1
4 5 2
1 2 3
1 3 3
3 4 7
2 3 3
2 4 6
1 2
1 4```

### 输出

```
Case #1: 2```

# 题解

## 作者：FFTotoro (赞：1)

考虑一个 $s\to t$ 怎样能走奇数种颜色，首先考虑整个连通块里面的颜色种类数，如果为奇数整个遍历一遍即可取到——故必然有解，如果为偶数判断是否存在一个连通块内存在的颜色使得删掉这个颜色的边 $s,t$ 仍然连通（对于每个颜色开一个并查集维护），有解当且仅当存在。

证明：考虑一个不必经过的颜色 $c$，如果不经过它可以遍历连通块内的其他所有颜色，那么遍历其他所有颜色即可；否则必然存在一个颜色 $c'$ 被它“隔开”了，此时 $c\gets c'$，继续返回去判断上面的条件……这个过程一定会结束，所以一定存在一组解。

视 $N,M,Q$ 同阶，令颜色数为 $C$，时间复杂度 $O(CN\alpha(N))$。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef tuple<int,int,int> tpi;
const int C=100;
namespace IAOI_lib{
  template<typename T> class dsu{
    private:
      vector<T> a;
      vector<int> s;
    public:
      dsu(int n=2e5){
        a.resize(n),s.resize(n,1);
        iota(a.begin(),a.end(),0);
      }
      T leader(T x){
        return a[x]==x?x:a[x]=leader(a[x]);
      }
      inline int size(T x){
        return s[leader(x)];
      }
      inline void merge(T x,T y){
        x=leader(x),y=leader(y);
        if(x==y)return;
        if(s[x]>s[y])swap(x,y);
        s[y]+=s[x],a[x]=y;
      }
      inline bool same(T x,T y){
        return leader(x)==leader(y);
      }
  }; // 并查集模板
}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int tt; cin>>tt;
  for(int t=1;t<=tt;t++){
    int n,m,q,c=0; cin>>n>>m>>q;
    vector<tpi> e(m);
    vector<vector<pii> > g(n);
    for(auto &[u,v,c]:e){
      cin>>u>>v>>c,u--,v--,c--;
      g[u].emplace_back(v,c);
      g[v].emplace_back(u,c);
    }
    vector d(C,IAOI_lib::dsu<int>(n));
    // 每个颜色开一个并查集维护
    for(int i=0;i<C;i++)
      for(auto [u,v,c]:e)
        if(c!=i)d[i].merge(u,v);
    vector<int> p(n,-1);
    vector h(n,vector<bool>(C));
    for(int s=0;s<n;s++)
      if(p[s]<0){
        queue<int> q; q.emplace(p[s]=s);
        while(!q.empty()){
          int u=q.front(); q.pop();
          for(auto [i,w]:g[u]){
            if(p[i]<0)q.emplace(i);
            h[p[i]=s][w]=true;
          }
        }
      } // 搜连通块，顺带得出其中有哪几种颜色
    while(q--){
      int u,v,w=0; cin>>u>>v,u--,v--;
      if(p[u]!=p[v])continue;
      for(int i=0;i<C;i++)
        w^=h[p[u]][i];
      if(w){c++; continue;}
      for(int i=0;i<C;i++)
        if(h[p[u]][i]&&d[i].same(u,v)){c++; break;}
      // 判断是否有不必经过的颜色存在
    }
    cout<<"Case #"<<t<<": "<<c<<'\n';
  }
  return 0;
}
```

---

