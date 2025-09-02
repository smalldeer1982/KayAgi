# [COTS 2018] 直方图 Histogram

## 题目背景


译自 [Izborne Pripreme 2018 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2018/) D1T1。$\texttt{1s,1G}$。

## 题目描述



给定笛卡尔坐标系中的直方图，宽度为 $n$，第 $i$ 格的高度为 $h_i$。也就是说，对于 $\forall 1\le i\le n$，第 $i$ 格所占矩形的顶点坐标分别为 $(i-1,0),(i,0),(i-1,h_i),(i,h_i)$。

给定正整数 $p$，求出满足以下条件的矩形的数量：

- 矩形的四个顶点的坐标均为整数；
- 矩形有一条边在 $x$ 轴上；
- 矩形完全位于直方图内部（可以与边界相切）；
- 矩形的面积至少为 $p$。

## 说明/提示

#### 样例解释

样例一解释：
![](https://cdn.luogu.com.cn/upload/image_hosting/mzxlfq5x.png)

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le n\le 10^5$；
- $1\le p\le 10^{14}$；
- $1\le h_i\le 10^{9}$。


| 子任务编号 | $n\le $ |  $p$ | $h_i\le$   | 得分 |  
| :--: | :--: | :--: | :--: |  :--: |    
| $ 1 $    | $ 3\, 000 $    |  $\le 10^{12}$ | $ 10^9$ | $ 10 $   |  
| $ 2 $    | $ 10^5 $   |  $\le 10^8$ | $1\, 000$ | $ 15 $   |  
| $ 3 $    | $ 10^5$ | $=1$ | $10^9$  | $ 15 $   |  
| $ 4 $    | $ 10^5$ | $\le 10^5$ | $10^9$ | $  25 $   |  
| $ 5 $    | $ 10^5$  |  $\le 10^{14}$ | $10^9$ | $ 35 $   |  


## 样例 #1

### 输入

```
6 9
1 4 4 5 2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
10 5
3 6 1 3 2 1 5 3 4 2```

### 输出

```
31```

# 题解

## 作者：OrinLoong (赞：5)

[更好的阅读体验？](https://www.cnblogs.com/OrinLoong/p/18718384)

码字不易，帮到你的话点个关注谢谢

## LGP11261 [COTS 2018] 直方图 学习笔记
[Luogu Link](https://www.luogu.com.cn/problem/P11261)

### 前言
参考了[这篇题解](https://www.luogu.com.cn/article/h8oypt9l)。算是对其更详细的一个解释。

### 题意简述
给定一宽为 $n$ 的直方图，第 $i$ 格的高度为 $h_i$。也就是说，对于 $\forall 1\le i\le n$，第 $i$ 格矩形的四个顶点分别为 $(i-1,0),(i,0),(i-1,h_i),(i,h_i)$。

![pEKIR3j.md.png](https://s21.ax1x.com/2025/02/16/pEKIR3j.md.png)

给定正整数 $p$，求出满足以下条件的网格矩形的数量：
- 有一条边在 $x$ 轴上。
- 完全位于直方图内部。
- 面积至少为 $p$。

### 做法解析
首先想一想当一个矩形面积至少为 $p$ 时意味着什么——$ab>p$。换句话说，当我们确定了矩形的高 $b$ 的时候，我们就随之确定了 $a\ge \lceil \frac{p}{b} \rceil$。

我们发现，当矩形的 $lx,rx$ 确定之后，限制 $ry$ 范围的正是 $\min_{i=lx}^{rx} h_i$。此时套路来了：我们以 $i$ 为键，$h_i$ 为值建一棵小根笛卡尔树，并考虑横跨每个最小值的贡献。具体来说我们对这棵笛卡尔树做一遍 $dfs$，每搜到一个结点 $(i,h_i)$，我们就统计所有 $lc\le lx\le i,i\le rx\le rc$ 的合法矩形的数量，其中 $lc,rc$ 分别为当前结点子树里横坐标的最小值和最大值。这么做的道理在于可以不重不漏地计数。

![pEKIWgs.md.png](https://s21.ax1x.com/2025/02/16/pEKIWgs.md.png)

令当前结点 $u$ 的左子树大小为 $L$，右子树大小为 $R$（实际上，$L=u-lc,R=rc-u$）。现在问题变成了计算所有结点的 $\sum_{i=0}^L\sum_{j=0}^{R} \max(h_u-\lceil\frac{p}{i+j+1}\rceil+1,0)$，其中的 $\lceil\frac{p}{i+j+1}\rceil$ 代表着 $i,j$ 确定后合法矩形高度的最小值，$h_u-\lceil\frac{p}{i+j+1}\rceil+1$ 则自然是 $i,j$ 确定后合法高度的种类。

![pEKIfvn.md.png](https://s21.ax1x.com/2025/02/16/pEKIfvn.md.png)

考虑枚举较小的那一侧子树的 $i$（这里是启发式合并思想，保证复杂度 $O(N\log N)$）。不妨设 $L<R$，问题变为如何快速计算 $\sum_{i=0}^{L}\sum_{k=i+1}^{i+R+1}\max(h_u-\lceil\frac{p}{k}\rceil+1,0)$。  
显然最小的满足 $h_u-\lceil\frac{p}{k}\rceil\ge 0$ 的 $k$ 就是 $\lceil\frac{p}{h_u}\rceil$，  
所以上式等价于算 $\sum_{i=0}^{L}\sum_{k=\max(i+1,\lceil\frac{p}{h_u}\rceil)}^{i+R+1} h_u-\lceil\frac{p}{k}\rceil+1$，  
也即等价于 $\sum_{i=0}^L (i+R+1-\max(i+1,\lceil\frac{p}{h_u}\rceil))\times h_u-\sum_{k=\max(i+1,\lceil\frac{p}{h_u}\rceil)}^{i+R+1} \lceil \frac{p}{i} \rceil$。  
注意到我们减去的那玩意就是个 $\lceil \frac{p}{i} \rceil$ 的前缀和，预处理之即可。这道题就做完了！  

时间复杂度 $O(N\log N)$。

### 代码实现
代码很简单!
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace obasic{
    typedef long long lolo;
    template <typename _T>
    void readi(_T &x){
        _T k=1;x=0;char ch=getchar();
        for(;!isdigit(ch);ch=getchar())if(ch=='-')k=-1;
        for(;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+ch-'0';
        x*=k;return;
    }
    template <typename _T>
    void writi(_T x){
        if(x<0)putchar('-'),x=-x;
        if(x>9)writi(x/10);
        putchar(x%10+'0');
    }
    template <typename _T>
    void maxxer(_T &x,_T y){x=max(x,y);}
    template <typename _T>
    _T pcedi(_T x,_T y){return (x-1)/y+1;}
};
using namespace obasic;
const int MaxN=1e5+5;
int N,H[MaxN],stk[MaxN],ktp;
int ls[MaxN],rs[MaxN];lolo P,pre[MaxN],ans;
lolo calc(lolo l,lolo r,lolo h){
    maxxer(l,pcedi(P,h));if(l>r)return 0;
    return 1ll*(h+1)*(r-l+1)-(pre[r]-pre[l-1]);
}
lolo solve(int u,int cl,int cr){
    lolo res=0;int lsiz=u-cl,rsiz=cr-u;
    if(lsiz>rsiz)swap(lsiz,rsiz);
    lsiz++;for(int i=1;i<=lsiz;i++)res+=calc(i,i+rsiz,H[u]);
    if(ls[u])res+=solve(ls[u],cl,u-1);
    if(rs[u])res+=solve(rs[u],u+1,cr);
    return res;
}
signed main(){
    readi(N),readi(P);
    for(int i=1;i<=N;i++)pre[i]=pre[i-1]+pcedi(P,(lolo)i);
    for(int i=1;i<=N;i++)readi(H[i]);
    for(int i=1;i<=N;i++){
        int k=ktp;
        while(k&&H[stk[k]]>H[i])k--;
        if(k)rs[stk[k]]=i;
        if(k<ktp)ls[i]=stk[k+1];
        stk[++k]=i,ktp=k;
    }
    ans=solve(stk[1],1,N);writi(ans);
    return 0;
}
```

### 反思总结
我们考虑有顺序地枚举限制矩形高度的 $h_i$，于是把问题搬到了笛卡尔树上！大概是一种套路。  
更深刻的东西暂时想不出来/ll

---

## 作者：_Ch1F4N_ (赞：5)

考虑到确定了 $x$ 轴上的范围后，限制 $y$ 轴范围的是区间中 $h$ 的最小值，于是对原序列建立出小根笛卡尔树，我们考虑横跨每个最小值的贡献。

假设当前点左子树大小为 $L$ 右子树大小为 $R$，其贡献就是 $\sum_{i=0}^L \sum_{j=0}^R \max(h - \left\lceil\dfrac{p}{i+j+1}\right\rceil + 1,0)$。

考虑枚举 $L,R$ 中较小的那个也就是去做启发式合并，我们需要快速计算 $\sum_{i=l}^r \max(h - \left\lceil\dfrac{p}{i}\right\rceil,0)$。

根据数论知识注意到满足 $h - \left\lceil\dfrac{p}{i}\right\rceil \geq 0$ 的最小 $i$ 刚好是 $\left\lceil\dfrac{p}{h}\right\rceil$，于是外面的 $\max$ 就被我们拆掉了，我们要处理的只剩下 $\left\lceil\dfrac{p}{i}\right\rceil$ 的前缀和，$O(n)$ 预处理下即可。

总时间复杂度 $O(n \log n)$，常数小并且非常好写。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5+114;
int stk[maxn],tp;
int n,h[maxn],p;
int ls[maxn],rs[maxn];
int pre[maxn];
int calc(int l,int r,int c){
	c++;
	l=max(l,(p+c-1)/c);
	if(l<=r) return c*(r-l+1)-pre[r]+pre[l-1];
	else return 0;
}
int ans;
void solve(int cur,int l,int r){
	if(cur==0) return ;
	solve(ls[cur],l,cur-1);
	solve(rs[cur],cur+1,r);
	int L=cur-l+1,R=r-cur+1;
	if(L>R) swap(L,R);
	for(int i=1;i<=L;i++) ans+=calc(i,i+R-1,h[cur]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    cin>>n>>p;
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+(p+i-1)/i;
    for(int i=1;i<=n;i++){
        cin>>h[i];
        int k=tp;
        while(k>0&&h[stk[k]]>h[i]) k--;
        if(k!=0) rs[stk[k]]=i;
        if(k<tp) ls[i]=stk[k+1];
        tp=k;
        stk[++tp]=i;
    }
    solve(stk[1],1,n);
    cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：FFTotoro (赞：3)

从部分分 $h_i\le 1000$ 出发，枚举合法矩形的高度 $h$：从上往下做扫描线，考虑维护所有高度 $\ge h$ 的矩形构成的横向“连续段”，就可以对于 $w=1,2,\ldots,n$ 计算出底边长为 $w$、高度为 $h$ 的矩形的个数 $c_w$（对于一个长度为 $k$ 的连续段，底边长为 $w(1\le w\le k)$ 的矩形有 $k-w+1$ 个）。

对于每个高度 $h$，可以求出矩形底边边长的**最小值** $w_{\min}$ 使得 $h\cdot w_{\min}\ge p$，答案即为 $r_h=\sum\limits_{w=w_{\min}}^n c_w$。

接下来考虑 $h_i$ 比较大的时候怎么做。考虑扫描线时，从 $h'+1$ 扫描到 $h'$ 时，$r_{h'}\ne r_{h'+1}$ 只可能有两种情况：（1）两者对应的 $w_{\min}$ 不相等；（2）两者对应的连续段形态不相等，此时必然存在 $h_i=h'$，这样连续段形态才会发生变化。前者仅有不超过 $n$ 种情况，因为 $w_{\min}$ 只有 $n$ 种；后者也不超过 $n$ 种情况，因为 $h_i$ 也最多只有 $n$ 种。于是只有最多 $2n$ 个分界点，这些分界点之间所有 $h'$ 对应的 $r_{h'}$ 都是相等的。

于是考虑开一个线段树，对于每个 $w=1,2,\ldots,n$，在扫描的过程中实时维护底边长为 $w$ 的矩形的答案。我们要做的事情有如下两种：

- 对于上述情况（1），需要查询 $\sum\limits_{w=w_{\min}}^n c_w$，即区间和；
- 对于上述情况（2），需要更新连续段形态：加入 / 删除一个长度为 $k$ 的区间，有 $k-w+1(1\le w\le k)$ 个底边长为 $w$ 的矩形被加入 / 删除，即区间加一个等差数列。

上面两个操作可以使用树状数组维护：具体维护方法可以参照[该教程](https://www.cnblogs.com/wushansinger/p/18010870)；而连续段形态可以使用 `std::set` 维护。时间复杂度 $O(n\log n)$。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
namespace IAOI_lib{
  template<typename T> class fenwick_tree{
    private:
      vector<T> t;
    public:
      fenwick_tree(){}
      void resize(int n){
        t.resize(n);
      }
      fenwick_tree(int n){
        resize(n);
      }
      inline int lowbit(int x){
        return x&-x;
      }
      inline void add(int p,T d){
        if(p<0||p>=t.size())return;
        t[p++]+=d;
        while((p+=lowbit(p))<=t.size())t[p-1]+=d;
      }
      inline T sum(int p){
        if(p<0||p>=t.size())return 0;
        T s=t[p++];
        while((p-=lowbit(p))>0)s+=t[p-1];
        return s;
      }
  };
}
template<typename T> class arithmetic_fenwick_tree{
  private:
    IAOI_lib::fenwick_tree<T> c,c1,c2;
    inline void add(int p,T x){
      c.add(p,x),c1.add(p,x*p),c2.add(p,x*p*p);
    }
  public:
    arithmetic_fenwick_tree(int n){
      c.resize(n),c1.resize(n),c2.resize(n);
    }
    inline void upd(int l,int r,T a,T d){
      if(l>r)return;
      add(l,a),add(l+1,d-a);
      add(r+1,-(a+d*(r-l+1)));
      add(r+2,a+d*(r-l));
    }
    inline T sum(int n){
      if(n<0)return 0;
      T s=c.sum(n)*(n+1)*(n+2);
      s-=(n*2+3)*c1.sum(n),s+=c2.sum(n);
      return s/2;
    }
}; // 维护区间加等差数列 & 区间和
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,p,c=0; cin>>n>>p;
  vector<int> h(n),w(n),v={0};
  for(auto &i:h)cin>>i,v.emplace_back(i);
  iota(w.begin(),w.end(),0);
  sort(w.begin(),w.end(),[&](int x,int y){
    return h[x]>h[y];
  });
  for(int i=1;i<=n;i++)
    v.emplace_back(p/i+!!(p%i)-1);
  sort(v.begin(),v.end(),greater<>());
  v.erase(unique(v.begin(),v.end()),v.end());
  // 预处理出所有分界点，存储在 v 中并去重
  set<pii> s; // 维护连续段
  arithmetic_fenwick_tree<int> t(n);
  auto add=[&](int k){t.upd(0,k-1,k,-1);};
  auto del=[&](int k){t.upd(0,k-1,-k,1);};
  for(int i=0,l=1,x=0;i+1<v.size();i++){
    while(l<=n&&l*v[i]<p)l++;
    while(x<n&&h[w[x]]>v[i+1]){
      auto it=s.lower_bound(make_pair(w[x],0));
      if(it!=s.end()&&it->first==w[x]+1){
        auto [l,r]=*it;
        del(r-l+1),add(r-l+2);
        s.erase(it),s.emplace(w[x],r);
      }
      else s.emplace(w[x],w[x]),add(1);
      it=s.lower_bound(make_pair(w[x],0));
      if(it!=s.begin()&&prev(it)->second==w[x]-1){
        auto [l1,r1]=*prev(it); auto [l2,r2]=*it;
        del(r1-l1+1),del(r2-l2+1),add(r2-l1+1);
        it=s.erase(--it),s.erase(it),s.emplace(l1,r2);
      }
      x++;
    }
    c+=(v[i]-v[i+1])*(t.sum(n-1)-t.sum(l-2));
  }
  cout<<c<<endl;
  return 0;
}
```

---

## 作者：Shunpower (赞：3)

来一发线性做法。

------------

首先考虑枚举区间如何计算这个区间的答案，可以发现对于区间 $[l,r]$ 至少需要建立一个高度为 $\left\lceil\frac{p}{r-l+1}\right\rceil$ 的矩形，而矩形高度又受到区间 $h$ 最小值限制，不能超过这个值。所以答案实际上就是：

$$
\sum\limits_{l=1}^{n}\sum\limits_{r=l}^n \max(\min\limits_{i=l}^r h_i-\left\lceil\frac{p}{r-l+1}\right\rceil+1,0)
$$

考虑枚举 $r$ 或者其他东西没有什么好的做法，容易想到枚举 $\min\limits_{i=l}^r h_i$，考虑每个位置做**第一个最小值**的区间产生的贡献。

考虑每个位置 $i$ 前面第一个小于等于自己的数的位置 $l_i$（没有设置为 $0$）和后面第一个小于自己的数的位置 $r_i$（没有设置为 $n+1$），则它做第一个最小值的区间为 $(l_i,r_i)$，其中左端点在 $(l_i,i]$ 之间，右端点在 $[i,r_i)$ 之间。

我们现在确定了 $\min$ 的值，不妨记为 $v$，为了让我们答案中的 $\max$ 有效（不为 $0$），我们需要让区间长度大于等于 $lim=\left\lceil\frac{p}{v}\right\rceil$。

考虑怎么统计所有长度大于等于 $lim$ 的区间产生的 $v-\left\lceil\frac{p}{len}\right\rceil+1$ 的和。可以发现事实上只有三类区间。

下面不妨记左端点可取值有 $L$ 个（$L=i-l_i$），右端点可取值有 $R$ 个（$R=r_i-i$）。

- $len\le \min(L,R)$，这类区间都有恰好长度种方式跨过 $i$。所以我们只需计算一个区间的 $\sum\limits_{x} x(v-\left\lceil\frac{p}{x}\right\rceil+1)$，对 $x\left\lceil\frac{p}{x}\right\rceil$ 前缀和即可。
- $\min(L,R)<len\le \max(L,R)$，这类区间都恰好有 $\min(L,R)$ 种方式跨过 $i$。所以我们只需计算一个区间的 $\sum\limits_{x} \min(L,R)(v-\left\lceil\frac{p}{x}\right\rceil+1)$，对 $\left\lceil\frac{p}{x}\right\rceil$ 前缀和即可。
- $\max(L,R)<len\le L+R-1$，右界事实上就是 $i$ 做第一个最小值的区间的最长长度。不妨记这个长度为 $k$，那么这类区间都有 $k$ 减长度种方式跨过 $i$。所以我们只需计算一个区间的 $\sum\limits_{x} (k-x)(v-\left\lceil\frac{p}{x}\right\rceil+1)$。使用前面累的两个前缀和即可。

注意上方对区间计算和式时下界需要和 $lim$ 取 $\max$。

运算过程中可能会爆 `long long`，但答案不会爆。所以 `unsigned long long` 自然溢出即可。

时间复杂度为 $\mathcal O(n)$。

-------------------

代码里面我写成了笛卡尔树。实际上是不用的。

```cpp
int n;
ll p;
int h[N];
int minn[N][17],idx[N][17];
int tot;
int ls[N],rs[N];
int L[N],R[N];
ull val[N];
int cut[N];
int rt;
pii merge(pii x,pii y){
    if(x.fi==y.fi) return mp(x.fi,min(x.se,y.se));
    return min(x,y);
}
pii query(int l,int r){
    int len=__lg(r-l+1);
    return merge(mp(minn[l][len],idx[l][len]),mp(minn[r-(1<<len)+1][len],idx[r-(1<<len)+1][len]));
}
void build(int &x,int l,int r){
    tot++,x=tot;
    L[tot]=l,R[tot]=r;
    if(l>r) return void();
    tie(val[x],cut[x])=query(l,r);
    build(ls[x],l,cut[x]-1);
    build(rs[x],cut[x]+1,r);
}
ull pres[N];
ull press[N];
ull ans;
ull sum(int l,int r){
    return 1ull*(l+r)*(r-l+1)/2;
}
void calc(int x){
    if(L[x]>R[x]) return;
    ull lim=(p+val[x]-1)/val[x];
    int lef=cut[x]-L[x]+1;
    int rig=R[x]-cut[x]+1;
    {
        ull le=max(lim,1ull),re=min(lef,rig);
        if(le<=re){
            ans-=pres[re]-pres[le-1];
            ans+=sum(le,re)*(val[x]+1);
        }
    }
    {
        ull le=max(lim,min(lef,rig)+1ull),re=max(lef,rig);
        if(le<=re){
            ull coef=min(lef,rig);
            ans-=coef*(press[re]-press[le-1]);
            ans+=coef*(re-le+1)*(val[x]+1);
        }
    }
    {
        ull le=max(lim,max(lef,rig)+1ull),re=R[x]-L[x]+1;
        if(le<=re){
            ans-=(re+1)*(press[re]-press[le-1]);
            ans-=sum(le,re)*(val[x]+1);
            ans+=(re+1)*(re-le+1)*(val[x]+1);
            ans+=pres[re]-pres[le-1];
        }
    }
    calc(ls[x]);
    calc(rs[x]);
}
// #define Shun cute
int main(){
#ifdef Shun
    freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n>>p;
    fr1(i,1,n) pres[i]=pres[i-1]+1ull*i*((p+i-1)/i);
    fr1(i,1,n) press[i]=press[i-1]+1ull*(p+i-1)/i;
    fr1(i,1,n) cin>>h[i];
    fr1(i,1,n) minn[i][0]=h[i],idx[i][0]=i;
    fr1(j,1,16){
        fr1(i,1,n-(1<<j-1)){
            tie(minn[i][j],idx[i][j])=merge(mp(minn[i][j-1],idx[i][j-1]),mp(minn[i+(1<<j-1)][j-1],idx[i+(1<<j-1)][j-1]));
        }
    }
    build(rt,1,n);
    calc(rt);
    cout<<ans<<'\n';
    ET;
}
```

---

## 作者：mayike (赞：3)

what can I say.

三篇题解撤了两篇，怎么说？

但看在没有简单暴力的二阶差分做法下，还是写一篇罢。不懂二阶差分的可以左转 bdfs。

## 思路

发现 $h_i\le10^9$，很大，但由于只有 $n$ 个高，所以难免重复的答案。考虑一个常见套路，对于一个高度 $h_i$，找到最大的 $l$ 满足 $l<i$ 且 $h_l<h_i$ 和最小的 $r$ 满足 $i<r$ 且 $h_i>h_r$，那么底边在区间 $(l,r)$ 内，高度在 $(\max(h_l,h_r),h_i]$ 之间的矩形是可能可以快速计算个数的，因为满足合法，且高度有单调性。并且全都按此方案计算的话是不会算重的，因为在 $(l,r)$ 区间中，$h_j>h_i$ 的显然有 $\max(h_{l'},h_{r'})\ge h_i$，不会算重；而 $h_j=h_i$ 的直接不算；$h_j<h_i$ 的最近也是 $h_l$ 和 $h_r$ 了，而高度 $H>\max(h_l,h_r)$ 的矩形显然也不会影响它们。给出这部分代码：

```cpp
scanf("%d%lld",&n,&p);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	m=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+1+m,a[i])-b;
		while(top&&a[stk[top]]>=a[i])top--;//h[l]<h[i]
		L[i]=stk[top];
		stk[++top]=i;
	}
	stk[top=0]=n+1;
	for(int i=n;i;i--){
		while(top&&a[stk[top]]>a[i])top--;//h[r]<=h[i]
		R[i]=stk[top];
		stk[++top]=i;
		if(a[R[i]]!=a[i]){//当h[r]=h[i]直接不算
            /*计算答案*/
        }
    }
```

那么知道 $(l,r)$ 了也知道高度范围了，那该怎么算答案呢？我们都知道，一个底边为 $len$ 的矩形，如果面积想要至少为 $p$ 那么 $h\ge\lceil \frac{p}{len} \rceil$，对于每一个底边为 $len$ 的且 $\max(h_l,h_r)<h\le h_i$ 的，答案是 $(h_i-h+1)\times(r-l+1-len+1)$，拆一下柿子是 $h_i\times(r-l+1-len+1)-(h-1)\times(r-l+1-len+1)$，显然是可以分别维护的。在求取 $\min len$ 满足至少高度 $\lceil \frac{p}{\min len} \rceil\le h_i$，$\max len$ 满足至少高度 $\lceil \frac{p}{\max len} \rceil>\max(h_l,h_r)$ 的情况下，$\min len$ 到 $\max len$ 中的 $r-l+1-len+1$ 这一贡献形成了等差数列，直接**二阶差分**跑路。而 $\lceil \frac{p}{len} \rceil\le\max(h_l,h_r)$ 这一部分的答案是 $(h_i-\max(h_l,h_r))\times (r-l+1-len+1)$，也可以二阶差分维护。给出代码，其中差分数组我开了两个，分别存值和个数。

```cpp
if(a[R[i]]!=a[i]){
			int len=R[i]-1-L[i];
			long long l=max(1ll,p/b[a[i]]+(p%b[a[i]]!=0)),r=(!max(b[a[L[i]]],b[a[R[i]]])?len:min(1ll*len,p/max(b[a[L[i]]],b[a[R[i]]])-(p%max(b[a[L[i]]],b[a[R[i]]])==0)));
			if(l<=r){
				c[l]+=(__int128)(len-l+1)*b[a[i]];
				c[l+1]+=(__int128)(-1-(len-l+1))*b[a[i]];
				c[r+1]+=(__int128)(1-(len-r+1))*b[a[i]];
				c[r+2]+=(__int128)(len-r+1)*b[a[i]];
				d[l]+=len-l+1;
				d[l+1]+=-1-(len-l+1);
				d[r+1]+=1-(len-r+1);
				d[r+2]+=len-r+1;
			}
			if(++r<=len){
				int x=b[a[i]]-max(b[a[L[i]]],b[a[R[i]]]);
				c[r]+=(__int128)(len-r+1)*x;
				c[r+1]+=(__int128)(-1-(len-r+1))*x;
				c[len+2]+=x;
			}
		}
```

然后就没了，注意可能会爆 `long long`。附上结尾部分的代码：

```cpp
    for(int i=1;i<=n;i++){
		c[i]+=c[i-1];
		d[i]+=d[i-1];
	}
	for(int i=1;i<=n;i++){
		c[i]+=c[i-1];
		d[i]+=d[i-1];
		long long h=p/i+(p%i!=0);
		ans+=c[i]-d[i]*(h-1);
	}
	print(ans);
```

---

## 作者：tyr_04 (赞：2)

upd：2025-02-28 添加了分析复杂度时遗漏的算法

[传送门](https://www.luogu.com.cn/problem/P11261)

首先，膜拜其他几位大佬提供的线性与单 $\log$ 做法，我在这里提供一个双 $\log$ 做法。

### 题意

在一个宽度为 $n$（共 $n$ 列）的二维平面上，每一列有 $h$ 个相连的格子，高度为 $h$（$x$ 轴高度为 $0$），问你在这个二维平面中有多少个面积大于 $p$ 且底边为 $x$ 轴的矩形。

### 思路

先按 $h$ 从大到小排序，依次加入列。可以发现每到一个高度，比这个高度的值低的高度可以任选（在目前加入的列中）。

考虑用 set 维护每一段连接的列，共以下几种情况：

* 如果新加入的列的相邻列都没有加过，则新增一个段。

* 如果新加入的列的相邻列的其中一个被加过，则将新增的列与它所在的段连接（即长度加一）。

* 如果新加入的列的相邻列都被加过，则将两个列所在的段合并，且长度再加一。

这样，我们就能快速的了解处于当前高度时可用列相连形成的段的情况。

接下来考虑段长确定时取某个长度的方案数，设某一段段长为 $5$，则：



|选择的段长|方案数|
|:-:|:-:|
|1|5|
|2|4|
|3|3|
|4|2|
|5|1|

不难发现方案数是一个等差数列，合并时又分为以下情况：

* 如果新加入的列的相邻列都没有加过，则长度为 $1$ 的方案数加一。

* 如果新加入的列的相邻列的其中一个被加过，设其段长为 $k$，则 $1 \sim k$ 的方案数全部加一。

* 如果新加入的列的相邻列都被加过，设其段长分别为 $k1,k2$，则将 $l \sim r$ 的方案数全都加一，满足 $1 \le l \le \min(k1,k2),r=l+\max(k1,k2)$，并将 $k1+k2+1$ 的方案数加一。

可以发现第三种情况每次只需枚举 $1 \sim \min(k1,k2)$，使用线段树区间加与区间求和，再根据启发式合并的复杂度，总复杂度为 $O(n\log^2n)$。

统计答案细节有点多，代码比较构式，见谅。

### Code

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
int n,p,h[200005],ans=0;
set<pair<int,int> > st;
struct node
{
	int sum,wz;
}s[200005];
struct sgt
{
	int l,r,sum,tag;
}t[1600005];
bool cmp(node x,node y)
{
	return x.sum>y.sum;
}
void push_up(int x)
{
	t[x].sum=t[x*2].sum+t[x*2+1].sum;
	return;
}
void push_down(int x)
{
	t[x*2].sum+=t[x].tag*(t[x*2].r-t[x*2].l+1);
	t[x*2].tag+=t[x].tag;
	t[x*2+1].sum+=t[x].tag*(t[x*2+1].r-t[x*2+1].l+1);
	t[x*2+1].tag+=t[x].tag;
	t[x].tag=0;
	return;
}
void build(int x,int l,int r)
{
	t[x].l=l;
	t[x].r=r;
	if(l==r)
	{
		t[x].sum=0;
		t[x].tag=0;
		return;
	}
	int mid=(l+r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	push_up(x);
	return;
}
void become(int x,int l,int r,int nl,int nr,int k)
{
	push_down(x);
	if(nl<=l&&r<=nr)
	{
		t[x].sum+=k*(r-l+1);
		t[x].tag+=k;
		return;
	}
	if(l>nr||r<nl)
	{
		return;
	}
	int mid=(l+r)/2;
	become(x*2,l,mid,nl,nr,k);
	become(x*2+1,mid+1,r,nl,nr,k);
	push_up(x);
	return;
}
int ask(int x,int l,int r,int nl,int nr)
{
	push_down(x);
	if(nl<=l&&r<=nr)
	{
		return t[x].sum;
	}
	if(l>nr||r<nl)
	{
		return 0;
	}
	int mid=(l+r)/2;
	return ask(x*2,l,mid,nl,nr)+ask(x*2+1,mid+1,r,nl,nr);
}
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
	{
		write(x/10);
	}
	putchar(x%10+'0');
    return;
}
signed main()
{
	n=read();
	p=read();
	for(int i=1;i<=n;i++)
	{
		h[i]=read();
		s[i].sum=h[i];
		s[i].wz=i;
	}
	sort(s+1,s+n+1,cmp);
	int d=0,last=s[1].sum;
	build(1,1,n);
	st.insert({-1,-1});
	st.insert({n+2,n+2});
	for(int now=1;now<=n;now++)
	{
		if(now*s[d+1].sum>=p)
		{
			ans+=(last-s[d+1].sum)*ask(1,1,n,now,n);
			last=s[d+1].sum;
		}
		while(d<n&&now*s[d+1].sum>=p)
		{
			d++;
			auto o1=st.upper_bound({s[d].wz,0}),o2=st.upper_bound({s[d].wz,0});
			o2--;
			pair<int,int> now1=*o1,now2=*o2;
			if(s[d].wz==now1.first-1&&s[d].wz==now2.second+1)
			{
				st.erase(o1);
				st.erase(o2);
				st.insert({now2.first,now1.second});
				int l1=now1.second-now1.first+1,l2=now2.second-now2.first+1;
				if(l1>l2)
				{
					swap(l1,l2);
				}
				for(int i=1;i<=l1;i++)
				{
					become(1,1,n,i+1,i+l2,1);
				}
				become(1,1,n,1,l1+l2+1,1);
			}
			else if(s[d].wz==now1.first-1)
			{
				st.erase(o1);
				st.insert({s[d].wz,now1.second});
				become(1,1,n,1,now1.second-s[d].wz+1,1);
			}
			else if(s[d].wz==now2.second+1)
			{
				st.erase(o2);
				st.insert({now2.first,s[d].wz});
				become(1,1,n,1,s[d].wz-now2.first+1,1);
			}
			else
			{
				st.insert({s[d].wz,s[d].wz});
				become(1,1,n,1,1,1);
			}
			if(s[d+1].sum*now>=p)
			{
				ans+=(s[d].sum-s[d+1].sum)*ask(1,1,n,now,n);
				last=s[d+1].sum;
			}
		}
		ans+=(last-(p+now-1)/now+1)*ask(1,1,n,now,n);
		last=(p+now-1)/now-1;
	}
	write(ans);
	return 0;
}
```

---

