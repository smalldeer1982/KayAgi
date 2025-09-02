# [ICPC 2020 WF] Sweep Stakes

## 题目描述

你可能已经赢了！事实上，你确实赢了！你赢得了属于你自己的岛屿，位于未被探索的海洋最深处！嗯，几乎未被探索。事实是，在你之前那里有一个小型军事基地，当他们打包飞走时，留下了一些废料、弹药、隧道，等等，当然还有未爆炸的防御军火。没错：你现在拥有了你自己的雷区。

雷区由一个 $m \times n$ 的网格组成，网格的任意方格上可能有 0 或 1 个地雷。幸运的是，你找到了工程师们布雷时的计划。不幸的是，地雷的具体位置从未被记录下来：工程师们在每个方格上布雷的概率是预先独立选择的。然而，你知道总共放置了多少个地雷。

你想估计你岛屿各个部分的安全性。编写一个程序来计算雷区各个子集上的地雷数量的概率。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2 2 1 2
0.05 0.05
0.05 0.05
1 1 1
2 2 1 1 2```

### 输出

```
0.75 0.25
0.5 0.5 0```

## 样例 #2

### 输入

```
3 4 3 4
0.02 0.04 0.06
0.005 0.07 0.035 0.09
1 3 2
3 1 4 2 4 3 4
4 1 2 2 3 3 1 1 4
8 1 1 1 2 1 3 2 1 2 3 3 1 3 2 3 3```

### 输出

```
0.649469772 0.350530228
0.219607636 0.527423751 0.237646792 0.015321822
0.267615440 0.516222318 0.201611812 0.014550429 0
0.054047935 0.364731941 0.461044157 0.120175967 0 0 0 0 0```

# 题解

## 作者：ZhongYuLin (赞：2)

考虑条件概率。具体地，设事件 $A$ 表示所有点中一共有 $t$ 个地雷，事件 $B_i$ 表示所选点集中有 $i$ 个地雷。根据条件概率的定义，我们要求的即为：

$$P(B_i\mid A)=\dfrac{P(AB_i)}{P(A)}$$

对于点 $(i,j)$，设其为地雷的概率为 $p_{i,j}$，构造生成函数 $\left [p_{i,j}x+(1-p_{i,j})\right]$。容易用分治 FFT 求出 $P(A)$。要求出 $P(AB_i)$，实际上就是要维护下面的多项式：

$$\prod_{i=1}^n\prod_{j=1}^m\left [p_{i,j}x+(1-p_{i,j})\right]$$

我们用线段树暴力维护区间卷积，合并时暴力 FFT，复杂度应该是 $O(n^3\log^2n)$，理论可以通过，实际上无法通过。

注意到 $p_{i,j}\leq 0.2$，考虑精度损失。发现**有效信息**越来越少，可以直接忽略低于某一精度的值。使用线段树分治并暴力撤销而不进行多项式除法，只维护有效段并暴力卷积，可以通过本题。具体地，维护两个多项式，分别存储询问子集内的点的卷积与子集外的点的卷积。

分析复杂度。打表发现，当精度取 $10^{-14}$ 时，多项式内元素上界为 $O(n^2)$ 个，但远远达不到，可以通过。


```cpp
#include<bits/stdc++.h>
using namespace std;
using ld=double;
const int N=5e2+3;
const ld eps=1e-14;
struct Poly{
    int l,r;
    deque<ld>q;
    Poly(){l=r=0;q.push_back(1);}
    void ins(ld p){
        q.push_back(0);++r;
        for(auto it=--q.end();;--it){
            *it*=1-p;
            if(it==q.begin())break;
            *it+=*prev(it)*p;
        }
        while(l<r&&q.front()<eps)q.pop_front(),++l;
        while(l<r&&q.back()<eps)q.pop_back(),--r;
    }
    ld operator[](int i){
        if(i<l||i>r)return eps;
        return q[i-l];
    }
}now;
#define id(x,y) ((x-1)*m+y)
#define ls mid<<1
#define rs mid<<1|1
int n,m,K,q;
ld a[N*N],b[N],c[N];
ld PA;
set<int>t[N<<1];
void build(int l=1,int r=q,int p=1){
    if(l==r){
        int k,x,y;
        for(cin>>k;k--;){
            cin>>x>>y;
            t[p].insert(id(x,y));
        }
        return;
    }
    int mid=l+r>>1;
    build(l,mid,ls);
    build(mid+1,r,rs);
    for(auto x:t[ls])t[p].insert(x);
    for(auto x:t[rs])t[p].insert(x);
}
void solve(int l=1,int r=q,int p=1){
    if(l==r){
        Poly res;
        for(auto x:t[p])res.ins(a[x]);
        int len=t[p].size(),lim=min(K,len);
        if(!PA)for(int i=0;i<=lim;++i)PA+=res[i]*now[K-i];
        for(int i=0;i<=lim;++i)printf("%.10lf ",res[i]*now[K-i]/PA);
        for(int i=K+1;i<=len;++i)printf("0 ");puts("");
        return;
    }
    int mid=l+r>>1;Poly old=now;
    for(auto x:t[p])if(!t[ls].count(x))now.ins(a[x]);
    solve(l,mid,ls);now=old;
    for(auto x:t[p])if(!t[rs].count(x))now.ins(a[x]);
    solve(mid+1,r,rs);now=old;
}
int main(){
    int u,v,w,x,y,z;
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>K>>q;if(!q)return 0;
    for(int i=1;i<=n;++i)cin>>b[i];
    for(int i=1;i<=m;++i)cin>>c[i];
    build();
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j){
            a[id(i,j)]=b[i]+c[j];
            if(!t[1].count(id(i,j)))
                now.ins(b[i]+c[j]);
        }
    solve();
    return 0;
}
```

---

## 作者：win114514 (赞：0)

### 思路

容易发现，题目要求我们动态维护这样一个多项式。

$$
\prod_{i}(1-p_i+p_ix)
$$

如何维护。

由于精度问题，我们很难去进行一个多项式除法将其暴力求出。

考虑 $p_i\le 0.2$。

可以得知，我们的多项式的数的增减是比较大的。

那么在一定数量后，一些可能有值的系数在当前精度下是可以认为是零的。

这样就对多项式长度有了保障。

我们可以将所有询问丢到线段树上。

暴力维护两个多项式。

在多项式乘法的时候。

我们仅维护有值的位置。

就可以以较快的速度通过此题。

复杂度不会算。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int m, n, t, q, ln[1010];
double a[510];
double b[510];
set<pair<int, int>> v[1010];

struct Poly {
  int l, r;
  double f[300000]{};
  Poly() { l = 0, r = 0, f[0] = 1; }
  inline void add(int x, int y) {
    double p = a[x] + b[y];
    double q = 1 - p;
    r++;
    for (int i = r; i >= l; i--) {
      f[i] = f[i] * q;
      if (i != l) f[i] += f[i - 1] * p;
    }
    while (l < r && f[l] < 1e-12) l++;
    while (l < r && f[r] < 1e-12) r--;
  }
};

Poly cur;

inline void build(int p, int l, int r) {
  if (l == r) {
    cin >> ln[p];
    for (int i = 1; i <= ln[p]; i++) {
      int x, y;
      cin >> x >> y, v[p].emplace(x, y);
    }
  } else {
    int mid = (l + r) >> 1;
    build(mid<<1, l, mid);
    build(mid<<1|1, mid + 1, r);
    for (auto i : v[mid<<1]) v[p].insert(i);
    for (auto i : v[mid<<1|1]) v[p].insert(i);
  }
}
inline void solve(int p, int l, int r) {
  if (l == r) {
    Poly res;
    for (auto i : v[p])
      res.add(i.first, i.second);
    double pos = 0;
    for (int i = 0; i <= ln[p]; i++) {
      if (t - i >= 0) pos += res.f[i] * cur.f[t - i];
    }
    for (int i = 0; i <= ln[p]; i++) {
      if (t - i >= 0) printf("%.9lf ", res.f[i] * cur.f[t - i] / pos); else printf("0 ");
    }
    printf("\n");
  } else {
    int mid = (l + r) >> 1;
    Poly back = cur;
    for (auto i : v[p]) if (!v[mid<<1].count(i)) cur.add(i.first, i.second);
    solve(mid<<1, l, mid);
    cur = back;
    for (auto i : v[p]) if (!v[mid<<1|1].count(i)) cur.add(i.first, i.second);
    solve(mid<<1|1, mid + 1, r);
    cur = back;
  }
}

int main() {
  cin >> m >> n >> t >> q;
  if (!q) return 0;
  for (int i = 1; i <= m; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  build(1, 1, q);
  for (int i = 1; i <= m; i++) for (int j = 1; j <= n; j++) if (!v[1].count({i, j})) cur.add(i, j);
  solve(1, 1, q);
}
```

---

