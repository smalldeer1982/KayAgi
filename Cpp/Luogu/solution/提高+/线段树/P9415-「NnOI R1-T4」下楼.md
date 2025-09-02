# 「NnOI R1-T4」下楼

## 题目背景

引入一个简单的问题作为铺垫。

![](https://cdn.luogu.com.cn/upload/image_hosting/3a1iicbb.png)

假如你现在站在一栋高为 $200m$ 的楼上，人的大小忽略不计。

楼的 $100m$ 和 $200m$ 处分别突出一根无限长的钢管，人默认可以安全地站在上面。

你的手中有一把剪刀和一条长为 $150m$ 且极细的绳子，你可以打死结，不能打活结，且结的大小忽略不计。问你怎么安全下到地面。

解法：

$150m$ 长的绳子不足以让我们直接下去，所以必然需要借助第二根钢管。于是我们考虑将绳子弄成这样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/0pbb5lun.png)

即将绳子剪成 $50m$ 和 $100m$ 两段，$50m$ 长的绳子的末端打一个小环，然后将 $100m$ 长的绳子穿入小环并首尾连接。这样就凑出了 $100m$ 的绳子。

把 $50m$ 绳子的另一端系在第一根钢管上，借助它下到第二根钢管，用剪刀剪断环，抽出 $100m$ 长的绳子，即可顺利下到地面。我们称这种方法为“环套”法。

以下是整个过程示意图。

![](https://s1.ax1x.com/2023/06/01/p9zy3qI.jpg)

注意：图中的圆圈代表绳两端系着的小环，实际大小忽略不计。

“环套法”中，我们把绳子分为两部分：环和链。其中环可以回收利用。

在接下来的题目场景中，我们默认只有“环套法”和“简化的环套法”两种方式可用。其中“简化的环套法”为环的长度为 $0$ 或链的长度为 $0$。

（感谢 huzheng20 提供的图 Orz）

## 题目描述

在一栋楼上有 $n$ 个钢管，其中第 $i$ 个钢管高度为 $h_i$，权值为 $v_i$，你处在最高的某个钢管上，手中有一把剪刀和一条绳子，要求所经过的钢管权值必须组成单调**不减**序列。

某些钢管的高度可能相同，这意味着你在这个高度可以选择不同权值的钢管落脚。

你的绳子的初始长度必须为**正整数**，但你可以在使用环套法后回收得到一根非整数长度的绳子。

问最少需要多长的绳子才能下到地面。

## 说明/提示

**本题开启捆绑测试**。

对于 $10\%$ 的数据，保证从高到低来看，钢管权值组成单调**不增**序列。

对于另外 $10\%$ 的数据，保证 $n\le 10^4$。

对于另外 $40\%$ 的数据，保证 $n\le 10^5$ 且不存在下标 $i,j$ 满足 $h_i=h_j$ 或 $v_i=v_j$。

对于所有数据，保证 $1\le n\le 5\times 10^5$，$1\le h,v\le 10^{18}$。

## 样例 #1

### 输入

```
3
100 7
63 9
25 8```

### 输出

```
69```

## 样例 #2

### 输入

```
10
99 191
30 82
144 52
11 0
149 70
65 117
73 37
39 101
135 92
43 33```

### 输出

```
99```

# 题解

## 作者：NaN_HQJ2007_NaN (赞：3)

不难推理出当初始绳长为 $len$，需要下降的距离为 $d$，并且满足 $d\le len<2d$ 时，最优的环套法可以只损失 $2d-len$ 长度的绳子，留下 $2(len-d)$ 的绳子。

![](https://s1.ax1x.com/2023/06/01/p9z2V6e.jpg)

当 $2d\le len$ 时存在一种不损耗绳长的方法可以下到下一根钢管，即把整根绳子系成一个环，到达下面再剪断。

![](https://s1.ax1x.com/2023/06/01/p9z2qHA.jpg)

## 正文：

线段树优化 DP。

我们先将所有钢管按高度从大到小排序，如果高度相同则按权值从小到大排序。

然后将权值离散化，对于相同的 $v$，给 $h$ 更大的赋更小的值。

考虑从低往高 DP。

定义 $f_i$ 表示最初站在 $i$ 号钢管，至少需要多长的绳子才能下到地面。

转移方程如下：

$$f_{i}=\begin{cases}f_j&2(h_i-h_j)\le f_j\land v_j\ge v_i\\h_i-h_j+\frac{f_j}{2}&2(h_i-h_j)>f_j\land v_j\ge v_i\end{cases}$$

开两棵线段树，第一棵 $t_1$ 维护 $\min(f_j)(h_j+\frac{f_j}{2}\ge h_i)$，第二棵 $t_2$ 维护 $\min(-h_j+\frac{f_j}{2})(h_j+\frac{f_j}{2}<h_i)$，每次分别在两棵线段树上查询 $[v_i+1,n]$ 内的最小值，记为 $m_1,m_2$。那么 $f_{i}=\min(m_1,m_2+h_i)$。

容易发现，一根钢管的贡献是有范围的。

对于钢管 $j$，我们二分出离它最远的 $i$，满足 $h_i\le h_j+\frac{f_j}{2}$，那么 $[i,j)$ 这些位置都可以通过第一种转移被 $f_j$ 贡献到，$[1,i)$ 这些位置可以通过第二种转移被 $h_i-h_j+\frac{f_j}{2}$ 贡献到。

具体的，我们假设二分到的位置为 $w$，那么在 $w-1$ 处标记编号 $j$，遍历到这里时，将 $t_1$ 对应位置改为 $\inf$，$t_2$ 对应位置改为 $-h_j+\frac{f_j}{2}$，更新一下线段树即可。

这里之所以可以通过赋值 $\inf$ 来撤销，是因为离散化后已经保证 $v_i$ 互不相同了。

注意，由于 $h$ 在 $10^{18}$ 级别，如果用 double 会爆精度并喜提 $0$ 分，所以要用 long double。

如果你还不放心，可以在每次除以 $2$ 后向上取整，至于为什么对，[这里](https://www.luogu.com.cn/paste/rpomuntz)有具体证明。

我们之所以不考虑正着推（从上往下），是因为多一个二分带来的 $\log$，而且转移时分三段，写起来极其麻烦。

综上，复杂度 $O(n\log n)$，代码很短。

code:

```cpp
#include<bits/stdc++.h>
#define ls (id*2)
#define rs (id*2+1)
using namespace std;
typedef long long ll;
const ll N=5e5+5,inf=LLONG_MAX>>2;
ll n,f[N],p;
vector<int>vec[N];
struct node{ll h,v;}a[N];
bool cmph(node x,node y){return x.h!=y.h?x.h>y.h:x.v<y.v;}
bool cmpv(node x,node y){return x.v!=y.v?x.v<y.v:x.h>y.h;}
struct tree{
  ll mi[4*N];
  void change(int id,int l,int r,int x,ll k){
    if(l==r){mi[id]=k;return;}
    int mid=(l+r)>>1;
    if(x<=mid)change(ls,l,mid,x,k);
    else change(rs,mid+1,r,x,k);
    mi[id]=min(mi[ls],mi[rs]);
  }
  ll query(int id,int l,int r,int L,int R){
    if(l==L&&r==R)return mi[id];
    int mid=(l+r)>>1;
    if(R<=mid)return query(ls,l,mid,L,R);
    else if(L>mid)return query(rs,mid+1,r,L,R);
    else return min(query(ls,l,mid,L,mid),query(rs,mid+1,r,mid+1,R));
  }
}t,t2;
inline void get(int id){
  int l=1,r=id,ans;
  while(l<=r){
    int mid=(l+r)>>1;
    if(a[mid].h<=a[id].h+(f[id]>>1))ans=mid,r=mid-1;
    else l=mid+1;
  }
  t.change(1,1,p,a[id].v,f[id]);
  vec[ans-1].push_back(id);
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n;p=n;
  for(int i=1;i<=n;++i)cin>>a[i].h>>a[i].v;
  sort(a+1,a+n+1,cmpv);
  for(int i=1;i<=n;++i)a[i].v=i;
  sort(a+1,a+n+1,cmph);a[n+1].v=++p;
  for(int i=1;i<=4*p;++i)t.mi[i]=t2.mi[i]=inf;
  get(n+1);
  for(int i=n;i>=1;--i){
    for(int j=0;j<vec[i].size();++j){
      int id=vec[i][j];
      t.change(1,1,p,a[id].v,inf);
      t2.change(1,1,p,a[id].v,-a[id].h+((f[id]+1)>>1));
    }
    f[i]=inf;
    f[i]=min(f[i],min(t.query(1,1,p,a[i].v+1,p),t2.query(1,1,p,a[i].v+1,p)+a[i].h));
    get(i);
  }
  cout<<f[1]<<endl;
  return 0;
}

```


---

