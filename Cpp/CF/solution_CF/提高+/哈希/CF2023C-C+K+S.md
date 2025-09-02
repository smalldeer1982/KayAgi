# C+K+S

## 题目描述

# 题面
给您两个强连接 $^{1}$ 有向图，每个图都有恰好 $n$ 个顶点，但可能有不同数量的边。仔细观察后，您发现了一个重要特征--这两个图中任何一个循环的长度都能被 $k$ 整除。

每个 $2n$ 顶点都属于两种类型中的一种：传入或传出。每个顶点的类型都是已知的。

您需要确定是否有可能在源图之间绘制恰好 $n$ 条有向边，从而满足以下四个条件：

- 任何添加的边的两端都位于不同的图中。
- 从每个传出顶点，正好有一条新增边产生。
- 在每个进入的顶点中，正好有一条添加边进入。
- 在生成的图中，任何循环的长度都能被 $k$ 整除。

$^{1}$强连接图是指从每个顶点到其他顶点都有一条路径的图。

## 样例 #1

### 输入

```
3
4 2
1 0 0 1
4
1 2
2 3
3 4
4 1
1 0 0 1
4
1 3
3 2
2 4
4 1
3 3
0 0 0
3
1 2
2 3
3 1
1 1 0
3
1 2
2 3
3 1
4 2
1 1 1 1
4
1 2
2 3
3 4
4 1
0 0 0 0
6
1 2
2 1
1 3
3 1
1 4
4 1```

### 输出

```
YES
NO
YES```

# 题解

## 作者：MarSer020 (赞：6)

![](https://pic.imgdb.cn/item/6717a043d29ded1a8c8b18d4.png)

![](https://pic.imgdb.cn/item/671a2c6bd29ded1a8c020098.png)

>yimuhua: 比我还唐的人出现了！

$\Large\text{Solution}$

题意：给定两张点数为 $n$ 的有向无权强连通图，保证两张图中每个环长度都是给定正整数 $k$ 的倍数。现在每个点被定义为入点或出点，要求在两张图**之间**由入点向出点连 $n$ 条有向边，使得每个环长仍然是 $k$ 的倍数，且每个点恰好连了一条新边。

一看感觉是神秘不可做题，考虑找性质。

首先发现原图中每个环长都是 $k$ 的倍数，说明原图中任意两点之间所有路径长度模 $k$ 为定值。这是显而易见的。

进一步发现若 $1\to u$ 距离 $\bmod\ k=a$，$1\to v$ 距离 $\bmod\ k=b$，则有 $u\to v$ 距离 $\bmod\ k=a-b$。

那么考虑定义一个点 $i$ 的特征值定义为 $1\to i$ 的距离 $\bmod\ k$ 的值，记为 $tp_i$。

考虑对于两张图之间有连边 $a\to b,c\to d$，其中 $a,d$ 为同一张图的点，$b,c$ 为另一张图的点，则有 $(tp_b-tp_c)+(tp_d-tp_a)+2\equiv0\pmod k$。拆一下，变为 $(tp_b-tp_a)+(tp_d-tp_c)+2\equiv0\pmod k$。

注意到两个括号中式子均为新边出点减新边入点的形式，故对于 $\forall u,v$ 使得图甲中 $u$ 与图乙中 $v$ 有连边，有 $(tp_u-tp_v)\bmod k$ 相等。

记 $cnt_{0,0,i}$ 表示图甲中 $tp_u=i$ 的入点 $u$ 的数量，$cnt_{0,1,i}$ 表示图甲出点的，$cnt_{1,0,i},cnt_{1,1,i}$ 同理，则上式等价于将 $cnt_{0,1,i},cnt_{1,1,i}$ 分别循环移动若干位后有 $cnt_{1,0,i}=cnt_{0,1,i},cnt_{0,0,i}=cnt_{1,1,i}$。具体循环移动位数由于有 $(tp_b-tp_a)+(tp_d-tp_c)+2\equiv0\pmod k$，满足特定规律，故共只有 $k$ 种。暴力哈希判断即可。注意不要把符号弄反了。

[submission](https://codeforces.com/contest/2023/submission/287369079)

upd：【】 ed 把我 skip 了

---

## 作者：MrPython (赞：3)

这个题还真挺不错的，值得补出来！

我们可以钦定任意一点的颜色（取值为 $[0,k)$），然后沿着边的方向对其他点染色。具体地，第设 $u$ 个点的颜色为 $c_u$，且有一条边 $u\rightarrow v$，则 $c_v=(c_u+1)\bmod k$。这个图上的所有环长度都是 $k$ 的倍数，因此一定可以按照上述规则对该图染色。

一个图有且仅有 $k$ 种染色方式，构造出一组 $c_0,c_1,\dots,c_{n-1}$ 后可以通过 $(c_1+x)\bmod k,(c_2+x)\bmod k,\dots,(c_{n-1}+x)\bmod k$ 构造出来所有其他的染色方式。

我们在加边的时候遵循相同的规则，从颜色 $x$ 连接到 $(x+1)\bmod k$，这样构造出来的图肯定也能满足所有的环为 $k$ 的倍数。

一种暴力做法是，枚举两个图的所有染色形式，检查：对于每种颜色 $i$，图一中颜色为 $i$ 的 outgoing 点数量是否等于图二颜色为 $(i+1)\bmod k$ 的 incoming 点数量，且图而中颜色为 $i$ 的 outgoing 点数量是否等于图一颜色为 $(i+1)\bmod k$ 的 incoming 点数量。其时间复杂度为 $O(n^3)$。两个图同时偏移相同的数时，效果相同。所以，我们只需要枚举某一个图的染色方式即可。这样的复杂度为 $O(n^2)$。

观察一下统计每种颜色 incoming 点数量与 outgoing 点数量的数组，所有点颜色增加 $1$ 相当于数组循环移位一次。而我们只需要判两个数组是否相等，上哈希搞一下就好了。

```cpp
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <queue>
#include <random>
#include <ranges>
#include <vector>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using ulli = __uint128_t;
const ui W = [] {
  random_device rd;
  return uniform_int_distribution<ui>{(ui)2e5, (ui)2e6}(rd);
}();
constexpr uli P = 1000000000000001771;
auto const H = []() {
  array<uli, (size_t)2e5 + 1> h;
  h[0] = 1;
  for (size_t i = 1; i < h.size(); ++i) h[i] = h[i - 1] * (ulli)W % P;
  return h;
}();
vector<size_t> color(size_t k, vector<vector<size_t>>& mp, size_t s = 0,
                     size_t c = 0) {
  vector<size_t> a(mp.size(), ~0);
  a[s] = c;
  queue<size_t> q{{s}};
  while (!q.empty()) {
    size_t p = q.front();
    q.pop();
    ui t = (a[p] + 1) % k;
    for (size_t i : mp[p])
      if (~a[i])
        assert(a[i] == t);
      else
        a[i] = t, q.push(i);
  }
  return a;
}
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    size_t n, k, m0, m1;
    fin >> n >> k;
    vector<bool> a0(n), a1(n);
    vector<vector<size_t>> g0(n), g1(n);
    for (auto i : a0) {
      char c;
      fin >> c;
      i = c == '1';
    }
    fin >> m0;
    while (m0--) {
      size_t x, y;
      fin >> x >> y;
      g0[--x].emplace_back(--y);
    }
    for (auto i : a1) {
      char c;
      fin >> c;
      i = c == '1';
    }
    fin >> m1;
    while (m1--) {
      size_t x, y;
      fin >> x >> y;
      g1[--x].emplace_back(--y);
    }
    if ((count(a0.begin(), a0.end(), true) == n &&
         count(a1.begin(), a1.end(), false) == n) ||
        (count(a0.begin(), a0.end(), true) == 0 &&
         count(a1.begin(), a1.end(), false) == 0)) {
      fout << "YES\n";
      continue;
    }
    auto t0 = color(k, g0), t1 = color(k, g1);
    vector<size_t> c0i(k), c0o(k), c1i(k), c1o(k);
    for (size_t i : ranges::views::iota((size_t)0, n))
      ++(!a0[i] ? c0i : c0o)[t0[i]], ++(!a1[i] ? c1i : c1o)[t1[i]];
    uli h0i = 0, h0o = 0, h1i = 0, h1o = 0;
    for (size_t i : ranges::views::iota((size_t)0, k))
      h0i = (h0i + (ulli)c0i[i] * H[k - i - 1]) % P,
      h0o = (h0o + (ulli)c0o[i] * H[k - i - 1]) % P,
      h1i = (h1i + (ulli)c1i[i] * H[k - i - 1]) % P,
      h1o = (h1o + (ulli)c1o[i] * H[k - i - 1]) % P;
    auto shift = [k](uli v, size_t c) -> uli {
      return ((v + P - (ulli)c * H[k - 1] % P) * W + (ulli)c * H[0]) % P;
    };
    for (size_t i : ranges::views::iota((size_t)0, k)) {
      if (h0o == shift(h1i, c1i[i]) && h1o == shift(h0i, c0i[0])) {
        fout << "YES\n";
        goto end;
      }
      h1i = shift(h1i, c1i[i]), h1o = shift(h1o, c1o[i]);
    }
    fout << "NO\n";
  end:;
  }
  return 0;
}
```

---

## 作者：lfxxx (赞：2)

首先特判掉连边后不会产生横跨两个图的环的情况。

然后我们注意到，连边后两个图强连通，且每个环长度均是 $k$ 的倍数，这说明这个新图可以被 $k$ 分图染色，那么先给一个图 $k$ 分图染色后即可求得另一个图一种可能的合法 $k$ 分图染色方案（这里的方案形如颜色为 $i$ 的点中有 $a_i$ 个连入的点，$b_i$ 个连出的点），注意到另一个图的所有合法方案为我们构造出的方案的一个循环，也就是 $i \to (i+v) \bmod k$，所以我们对另一个图求出任意一个真实的染色方案，只需要看两个方案代表的 $a_i,b_i$ 数组是否循环同构即可，于是构造 $c_i = {Hash1}(a_i,b_i)$ 再构造 $val_i = {Hash}2(c_{i-1},c_i,c_{i+1})$ 最后判断下两个数组的 $val_i$ 构成的集合是否相同即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
int a[maxn],b[maxn],A[maxn],B[maxn];
vector<int> e[maxn],E[maxn];
int vis[maxn];
int Vis[maxn];
int c[maxn],C[maxn];
mt19937 rd(time(0));
int C1,C2;
int mod;
int Hash1(int x,int y){
    return (x+C1)^(y+C2)+1ll*(x%mod)*(C1%mod)%mod+1ll*(y%mod)*(C2%mod)%mod;
}
int C3;
int Hash2(int x,int y,int z){
    return (x+C1)^(y+C2)^(z+C3)+1ll*(x%mod)*(C1%mod)%mod+1ll*(y%mod)*(C2%mod)%mod+1ll*(z%mod)*(C3%mod);
}
int val[maxn],Val[maxn];
int n,k;
int m1,m2;
int ty[maxn],Ty[maxn];
void col1(int u,int cl){
    vis[u]=1;
    //cout<<"1 "<<u<<' '<<cl<<'\n';
    if(ty[u]==0) b[(cl+k-1)%k]++;
    else a[(cl+1)%k]++;
    for(int v:e[u]){
        if(vis[v]==0) col1(v,(cl+1)%k);
    }
}
void col2(int u,int cl){
    Vis[u]=1;
    //cout<<"2 "<<u<<' '<<cl<<'\n';
    if(Ty[u]==0) A[cl]++;
    else B[cl]++;
    for(int v:E[u]){
        if(Vis[v]==0) col2(v,(cl+1)%k);
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n>>k;
        C1=rd(),C2=rd(),C3=rd();
        mod=rd()+1;
        int s=0,S=0;
        for(int i=1;i<=n;i++) cin>>ty[i],s+=ty[i];
        cin>>m1;
        for(int i=1;i<=m1;i++){
            int u,v;
            cin>>u>>v;
            e[u].push_back(v);
        }
        col1(1,0);
        for(int i=1;i<=n;i++) cin>>Ty[i],S+=Ty[i];
        cin>>m2;
        for(int i=1;i<=m2;i++){
            int u,v;
            cin>>u>>v;
            E[u].push_back(v);
        }
        col2(1,0);
        for(int i=0;i<k;i++) c[i]=Hash1(a[i],b[i]);
        for(int i=0;i<k;i++) C[i]=Hash1(A[i],B[i]);
        //cout<<C1<<' '<<C2<<'\n';
        //for(int i=0;i<k;i++) cout<<a[i]<<' '<<b[i]<<' '<<Hash1(a[i],b[i])<<' '<<A[i]<<' '<<B[i]<<' '<<Hash1(A[i],B[i])<<'\n';
        for(int i=0;i<k;i++) val[i]=Hash2(c[i],c[(i+k-1)%k],c[(i+1)%k]);
        for(int i=0;i<k;i++) Val[i]=Hash2(C[i],C[(i+k-1)%k],C[(i+1)%k]);
        //for(int i=0;i<k;i++) cout<<val[i]<<' '<<Val[i]<<'\n';
        sort(val,val+k);
        sort(Val,Val+k);
        bool flag=true;
        for(int i=0;i<k;i++){
            //cout<<val[i]<<' '<<Val[i]<<'\n';
            if(val[i]!=Val[i]) flag=false;
        }
        if(s==n&&S==0) flag=true;
        if(s==0&&S==n) flag=true;
        cout<<(flag==true?"YES\n":"NO\n");
        for(int i=0;i<k;i++) a[i]=b[i]=A[i]=B[i]=0;
        for(int i=1;i<=n;i++) E[i].clear(),e[i].clear(),vis[i]=Vis[i]=0;
    }
    return 0;
}
/*
1
2 2
0 0
2
1 2
2 1
0 0
2
1 2
2 1
*/
```

---

## 作者：ForgotMe (赞：1)

被这题狠狠地创死了。

首先得知道如何利用每个环的长度都是 $k$ 的倍数的条件。
这里直接给出结论，一个图满足每个环的长度都是 $k$ 的倍数的**充要条件**是存在一种 $k$ 染色（设第 $i$ 个点的颜色是 $c_i(c_i\in [0,k-1])$）使得对于任意一条边 $u\rightarrow v$ 有 $c_v=(c_u+1)\mod k$。证明比较简单，就不提了。

知道这个结论这题就好做了，题意就可以转化为先分别对图 $G_1,G_2$ 进行 $k$ 染色，然后两个图的点按要求进行匹配（既要满足 $a,b$ 的要求，也要满足颜色的要求）。另一个显然的结论是 $G_1$ 只有 $k$ 种不同的染色方式（让 $c_1$ 分别从 $0$ 取到 $k-1$），然后对于每一种染色方式都要与 $G_2$ 进行匹配。判断是否存在一个完美匹配是容易的，直接把点按照颜色分类统计其数量。对于 $G_2$ 中颜色为 $c$，$b_i=0$ 的点，应该与 $G_1$ 中颜色为 $(c+k-1)\bmod k$，$a_i=1$ 的点匹配，要存在完美匹配就等价于两种颜色对应的点的个数应该一样。剩下的情况类似。对于 $k$ 种不同的染色方式，发现其按颜色分类后的数组就是在不断的循环移位，倍长后 kmp/hash 匹配即可。时间复杂度线性。

代码：https://www.luogu.com.cn/paste/olrrej6m

---

