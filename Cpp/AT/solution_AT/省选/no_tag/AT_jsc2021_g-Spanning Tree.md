# Spanning Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jsc2021/tasks/jsc2021_g

$ N $ 頂点のグラフ $ G $ があり、頂点には $ 1,\ 2,\ \dots,\ N $ の番号がついています。はじめ、$ G $ には辺がありません。  
 これから $ G $ に何本か無向辺を追加します。ただし、辺を追加し終わった後、任意の $ i,\ j\,(i\ ≠\ j) $ について以下の条件を満たす必要があります。

- $ A_{i,\ j}\ =\ 1 $ のとき、頂点 $ i $ と頂点 $ j $ を直接結ぶ辺が存在する。
- $ A_{i,\ j}\ =\ 0 $ のとき、頂点 $ i $ と頂点 $ j $ を直接結ぶ辺が存在しない。
- $ A_{i,\ j}\ =\ -1 $ のとき、どちらでもよい。

辺を追加し終わった後の $ G $ としてあり得るもののうち、木であるものはいくつあるでしょうか？  
 ただし、答えは非常に大きくなることがあるので、答えを $ (10^9\ +\ 7) $ で割った余りを求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ <\ =\ N\ <\ =\ 300 $
- $ -1\ <\ =\ A_{i,\ j}\ =\ A_{j,\ i}\ <\ =\ 1 $
- $ A_{i,\ i}\ =\ 0 $

### Sample Explanation 1

頂点 $ 1 $ と頂点 $ 2 $ の間には辺が必要で、頂点 $ 1 $ と頂点 $ 4 $ の間、頂点 $ 3 $ と頂点 $ 4 $ の間には辺を追加してはいけません。 したがって、以下の $ 2 $ 個が条件を満たします。 !\[\](https://img.atcoder.jp/ghi/0f55bf9e7a13aef4bddde12f87a23d5d.png)

### Sample Explanation 4

頂点を区別するとき、$ 11 $ 頂点の木は全部で $ 11^9 $ 個あります。

## 样例 #1

### 输入

```
4
0 1 -1 0
1 0 -1 -1
-1 -1 0 0
0 -1 0 0```

### 输出

```
2```

## 样例 #2

### 输入

```
3
0 1 1
1 0 1
1 1 0```

### 输出

```
0```

## 样例 #3

### 输入

```
3
0 0 0
0 0 0
0 0 0```

### 输出

```
0```

## 样例 #4

### 输入

```
11
0 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1
-1 0 -1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 0 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 0 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 0 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 0 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 0 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 0 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 0 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1 0 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1 0```

### 输出

```
357947677```

# 题解

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_jsc2021_g)

## 思路

本题其实为：【模板】矩阵树定理。

考虑对于 $a_{i,j}=1$ 的 $i,j$，我们直接在并查集中把它们 $\rm merge$ 起来，如果说本来就在一个连通块内了，显然无解。

我们把一个连通块视为一个点，接下来就等于我们就等于在这些点中可以乱连一些边，不能连一些边，求生成树个数。

经典的矩阵树定理，矩阵树定理原本是求 $\sum_T \prod_{(u,v) ∈ T} w_{u,v}$ 的，我们把所有边的边权置为 $1$，就变成生成树个数了。

我们把第一行第一列删掉，然后求一个 Kirchhoff 矩阵，最后求个行列式就行了。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
int const N=3e2+10;
int fa[N],a[N][N];
vector<int>b[N];
inline int find(int x){return (x==fa[x])?x:fa[x]=find(fa[x]);}
mint d[N][N],s[N][N],k[N][N];
inline mint hls(int n){
    mint res=1;
    for (int i=1;i<=n;++i)
        for (int j=i+1;j<=n;++j){
            while (k[i][i].d){
                mint div=k[j][i]/k[i][i];
                for (int K=i;K<=n;++K) k[j][K]-=k[i][K]*div;
                swap(k[i],k[j]),res=-res;
            }
            swap(k[i],k[j]),res=-res;
        }
    for (int i=1;i<=n;++i) res*=k[i][i];
    return res;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for (int i=1;i<=n;++i) fa[i]=i;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j) cin>>a[i][j];
    for (int i=1;i<=n;++i)
        for (int j=i+1;j<=n;++j)
            if (a[i][j]==1){
                if (find(i)==find(j)) return cout<<"0\n",0;
                fa[find(i)]=find(j);
            }
    map<int,int>mp;int cnt=0;
    for (int i=1;i<=n;++i)
        if (find(i)==i) mp[i]=++cnt;
    for (int i=1;i<=n;++i)
        for (int j=i+1;j<=n;++j)
            if (a[i][j]==-1){
                if (find(i)==find(j)) continue;
                int lai=i,laj=j;
                i=mp[find(i)],j=mp[find(j)];
                --i,--j;
                d[i][i]+=1,d[j][j]+=1;
                s[i][j]+=1,s[j][i]+=1;
                i=lai,j=laj;
            }
    n=cnt;
    for (int i=1;i<n;++i)
        for (int j=1;j<n;++j)
            k[i][j]=d[i][j]-s[i][j];
    cout<<hls(n-1)<<'\n';
    return 0;
}
```

---

## 作者：FFTotoro (赞：1)

复习了矩阵树定理，再来试试水。

考虑如何将原问题转换为生成树计数：首先 $A_{i,j}=1$ 的边连接的两个点可以缩成一个点（可以用并查集维护；注意判连通块内的连边，这样是无解的）；然后对于 $A_{i,j}=-1$ 的边（在缩点之后），连接的两个点（实际上是原来的连通块）之间的边有选 / 不选两种选择，于是构造出基尔霍夫矩阵，就是板题了。

可以借助 AtCoder Library 中的 `dsu` 和 `modint` 实现。

放代码：

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
#define int long long
using namespace std;
using namespace atcoder;
using mint=modint1000000007;
mint det(vector<vector<mint> > &a){
  mint s=1,f=1;
  for(int i=0;i<a.size()-1;i++)
    for(int j=i+1;j<a.size()-1;j++){
      while(a[i][i].val()){
        mint d=a[j][i]/a[i][i];
        for(int k=i;k<a.size()-1;k++)
          a[j][k]-=a[i][k]*d;
        swap(a[i],a[j]),f=-f;
      }
      swap(a[i],a[j]),f=-f;
    }
  for(int i=0;i<a.size()-1;i++)
    s*=a[i][i];
  return s*f;
} // 求行列式
main(){
  ios::sync_with_stdio(false);
  int n,c=0; cin>>n;
  vector a(n,vector<int>(n));
  for(auto &i:a)for(auto &j:i)cin>>j;
  dsu d(n);
  for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
      if(a[i][j]>0){
        if(d.same(i,j))cout<<"0\n",exit(0);
        else d.merge(i,j);
      } // 并查集维护连通块
  vector<int> m(n);
  for(int i=0;i<n;i++)
    if(i==d.leader(i))m[i]=c++;
  vector f(c,vector<mint>(c));
  for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
      if(a[i][j]<0&&!d.same(i,j)){
        int x=m[d.leader(i)],y=m[d.leader(j)];
        f[x][x]++,f[y][y]++,f[x][y]--,f[y][x]--;
      } // 构造基尔霍夫矩阵
  cout<<det(f).val()<<endl;
  return 0;
}
```

---

## 作者：win114514 (赞：0)

感觉自己稍微有一点唐了。

### 思路

我们首先可以把一定要连的边连起来。

这样就变成了一个无向图生成树计数问题。

如何求解。

使用矩阵树定理！

我们可以求出基尔霍夫矩阵，然后跑一遍行列式就可以了。

时间复杂度：$O(n^3)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int n, m;
int fa[310];
int id[310];
int a[310][310];
int f[310][310];

inline int gf(int x) { return (x == fa[x] ? x : fa[x] = gf(fa[x])); }
inline long long power(long long x, long long y) {
  long long res = 1;
  while (y) { if (y & 1) res = res * x % mod; x = x * x % mod, y /= 2; }
  return res;
}

int main() {
  cin >> n;
  iota(fa + 1, fa + n + 1, 1);
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> a[i][j];
  for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++)
    if (a[i][j] == 1) {
      if (gf(i) == gf(j)) cout << 0 << "\n", exit(0);
      fa[gf(i)] = gf(j);
    }
  for (int i = 1; i <= n; i++) if (fa[i] == i) id[i] = ++m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (a[i][j] == -1) {
        f[id[gf(i)]][id[gf(j)]]--;
        f[id[gf(i)]][id[gf(i)]]++;
      }
  int ans = 1;
  for (int i = 1; i < m; i++) {
    int p = i;
    for (int j = i; j < m; j++) if (f[j][i]) p = i;
    if (p != i) ans = ans * -1, swap(f[p], f[i]);
    int q = power(f[i][i], mod - 2);
    for (int j = i + 1; j < m; j++) {
      int z = 1ll * f[j][i] * q % mod;
      for (int k = 1; k <= m; k++) {
        f[j][k] = (f[j][k] - 1ll * z * f[i][k]) % mod;
      }
    }
  }
  for (int i = 1; i < m; i++) ans = 1ll * ans * f[i][i] % mod;
  cout << (ans + mod) % mod << "\n";
}
```

---

