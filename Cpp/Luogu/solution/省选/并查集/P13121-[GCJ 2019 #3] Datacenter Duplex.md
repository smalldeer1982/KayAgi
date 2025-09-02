# [GCJ 2019 #3] Datacenter Duplex

## 题目描述

两家公司，Apricot Rules LLC 和 Banana Rocks Inc.，共用同一个数据中心。数据中心是一个 $\mathbf{R}$ 行 $\mathbf{C}$ 列的矩阵，每个格子里有一台服务器塔。每台服务器塔只属于其中一家公司。

最初，他们在分配给不同公司的格子之间的边上建造了墙。这样，属于同一公司的正交相邻格子依然是连通的。同时，如果格子 $\mathbf{x}$ 与格子 $\mathbf{y}$ 之间存在直接或间接的连通路径，则认为 $\mathbf{x}$ 和 $\mathbf{y}$ 是连通的。根据这个定义，可能会出现同一公司分配的两个格子不连通的情况，这是不可接受的。

两家公司同意在格子的顶点处修建狭窄的走廊，使得两个对角相邻的格子可以直接连通。我们用 $(\mathbf{i}, \mathbf{j})$ 表示第 $\mathbf{i}$ 行第 $\mathbf{j}$ 列的格子。每个顶点最多只能建一条狭窄的走廊，这意味着要么连接 $(\mathbf{i}, \mathbf{j})$ 和 $(\mathbf{i} + 1, \mathbf{j} + 1)$，要么连接 $(\mathbf{i} + 1, \mathbf{j})$ 和 $(\mathbf{i}, \mathbf{j} + 1)$，要么两者都不连，但不能同时连。当然，只有分配给同一公司的格子之间才能建走廊。

给定一个矩阵，每个格子用 $\mathbf{A}$ 或 $\mathbf{B}$ 标记，表示分配给哪家公司。请你为每个测试用例设计一种对角连通方案，使得所有 $\mathbf{A}$ 格子连通，所有 $\mathbf{B}$ 格子连通。

## 说明/提示

**样例解释**

在样例 1 中，A 格子和 B 格子都需要连通，但由于两条连通路径会交叉在同一个顶点，最多只能连通一对。

在样例 2 中，输入中的格子已经满足连通要求，无需额外连通。注意你可以添加多余但合法的连通方案，因此 `//` 也是合法答案，但 `\.` 就不合法。

在样例 3 中，也有多种合法方案，样例给出其中一种。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $2 \leq \mathbf{C} \leq 100$。
- 对所有 $\mathbf{i}, \mathbf{j}$，$\mathbf{M}_{\mathbf{i}, \mathbf{j}}$ 仅为大写字母 A 或 B。
- 至少有一个格子为 A，至少有一个格子为 B。

**测试点 1（10 分，公开）**

- $2 \leq \mathbf{R} \leq 4$。

**测试点 2（13 分，隐藏）**

- $2 \leq \mathbf{R} \leq 100$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 2
AB
BA
2 3
AAB
ABB
3 4
BBAA
BABA
BBAA```

### 输出

```
Case #1: IMPOSSIBLE
Case #2: POSSIBLE
..
Case #3: POSSIBLE
//\
.//```

# 题解

## 作者：FFTotoro (赞：1)

这题很 6。

以下定义“边界”为满足 $i=1\lor i=R\lor j=1\lor j=C$ 的格子 $(i,j)$，即四边上的格子。

考虑如果最终某个颜色没有连通（不妨设为颜色 $\text{A}$），只可能是如下的情况：

- 一个颜色 $\text{B}$ 的环把 $\text{A}$ 分成了里面和外面，称为情况 $1$；
- 一个颜色 $\text{B}$ 的路径把 $\text{A}$ 分成了两边（可以得出这条路径的两个端点均在边界上，并且路径上存在一些点不经过边界），称为情况 $2$。

注意到一个事情：如果用新建的走廊把两个已经连通的格子连起来必然没用；在之后的构造中不会去做这样的事情。这样就解决了情况 $1$，即除非一开始就存在这样的环（此时必然无解），不然在之后的连边中不可能造出一个新的环。

对于情况 $2$，考虑开始时边界上一圈的颜色分布情况。直接摆出结论：特判完情况 $1$ 后，有解当且仅当边界上所有颜色 $\text{A}$ 连通且所有颜色 $\text{B}$ 连通。证明：不妨认为若干个 $\text{B}$ 在两段 $\text{A}$ 的中间，要想让两个 $\text{A}$ 连通就必然会把这些 $\text{B}$ 和另外的 $\text{B}$ 隔开（连接两段 $\text{A}$ 的路径会把这一段 $\text{B}$“包住”），必然无解；否则无解只可能是情况 $2$，然而前面提到了“不会连通两个已经连通的格子”，所以若要产生一条情况 $2$ 所述的路径，必然要产生一个新的环（这条路径让两个边界上连通的点“再次”连通，故产生了环），矛盾，所以必然有解。

于是考虑对于每个 $2\times 2$ 方格考虑，依次考虑正副两条对角线上的两对格子，若存在一对未连通的就连起来，若存在两对未连通的就随便选一对（上面的证明已经说明了这里的不同选择不会导致有无解的结果不同），用并查集维护最后检查一下是否满足条件即可。时间复杂度 $O(RC\alpha(RC))$。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
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
    int n,m,c=0; cin>>n>>m;
    vector<string> a(n);
    for(auto &i:a)cin>>i;
    IAOI_lib::dsu<int> d(n*m);
    for(int i=0;i<n;i++)
      for(int j=0;j<m;j++){
        if(i&&a[i-1][j]==a[i][j])d.merge((i-1)*m+j,i*m+j);
        if(j&&a[i][j-1]==a[i][j])d.merge(i*m+j-1,i*m+j);
      } // 先把四联通的连起来
    vector r(n-1,string(m-1,'.'));
    for(int i=1;i<n;i++)
      for(int j=1;j<m;j++){
        if(a[i-1][j-1]==a[i][j]&&!d.same((i-1)*m+j-1,i*m+j))
          d.merge((i-1)*m+j-1,i*m+j),r[i-1][j-1]='\\';
        else if(a[i-1][j]==a[i][j-1]&&!d.same((i-1)*m+j,i*m+j-1))
          d.merge((i-1)*m+j,i*m+j-1),r[i-1][j-1]='/';
      } // 只要找到未连通的就连
    for(int i=0;i<n*m;i++)
      c+=d.leader(i)==i; // 计算连通块个数，判断是否合法
    if(cout<<"Case #"<<t<<": ";c==2){
      cout<<"POSSIBLE\n";
      for(auto i:r)cout<<i<<'\n';
    }
    else cout<<"IMPOSSIBLE\n";
  }
  return 0;
}
```

---

