# 「StOI-1」小Z的旅行

## 题目描述

一块空地，有$n$座山，每座山有一个高度值$h$。小Z在最高的山上，要去最低的山。

他有如下移动方案：

$1.$ 移动到一座比当前山低的山；

$2.$ 移动到和当前山一样高的山（不可停留在当前山），对于每一高度只能执行一次该方案（即不可以连续 $3$ 次或以上到达同一高度的山）。

每次移动都会耗费体力值，耗费的体力值为两座山的水平距离（若从第 $i$ 座山移动到第 $j$ 座山，则耗费 |$i-j$| 点体力值）。

小Z**每次**若有多种方案移动，则会**等概率**选择任意一种，求耗费体力值的期望对 $998,244,353$ 取余后的结果。

## 说明/提示

---

#### 样例1解释

取模前值为 $\frac{10}{3}$。

有如下方案（数字代表山的编号）：

1. $(4,1)$ 概率 $\frac{1}{3}$ ， 耗费体力值 $3$ ；

2. $(4,3,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $3$ ；

3. $(4,2,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $3$ ；

4. $(4,3,2,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $3$ ； 

5. $(4,2,3,1)$ 概率 $\frac{1}{3}$ $\times$ $\frac{1}{2}$ ，耗费体力值 $5$ 。

---

#### 数据范围

对于 $50$% 的数据：$1 ≤ n ≤ 1000$，$1 ≤ h ≤ 10^{9}$；  
对于 $100$% 的数据：$1 ≤ n ≤ 500000$，$1 ≤ h ≤ 10^{9}$。

所有数据：最低和最高的山高度唯一。

## 样例 #1

### 输入

```
4
1 3 3 7
```

### 输出

```
332748121```

## 样例 #2

### 输入

```
3
1 3 2```

### 输出

```
2```

## 样例 #3

### 输入

```
10
1 2 2 2 4 3 2 6 5 9```

### 输出

```
384244861```

# 题解

## 作者：1kri (赞：6)

#### ~~GF~~官方题解

首先爆切50pts，依照题意模拟然后加上记忆化就行了。

从最高点dfs，记录当前位置与是否进行过 $2$ 操作，每次先枚举可能情况然后转移就行了。

50pts代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define int long long
#define mod 998244353
using namespace std;
int n,a[1005],mx,mn=2e9;
int f[1005][2];
inline int pw(int a,int p){
    if (p==0)return 1;
    int t=pw(a,p/2);
    t=t*t%mod;
    if (p%2==1)t=t*a%mod;
    return t;
}
inline int inv(int a){
    return pw(a,mod-2);
}
inline int dfs(int now,int flag){
    if (a[now]==mn)return 0;
    if (f[now][flag]!=-1)return f[now][flag];
    int tot=0,s=0;
    for (int i=1;i<=n;i++){
        if (i==now)continue;
        if (a[i]<a[now])tot++;
        else if (a[i]==a[now]&&flag==0)tot++;
    }
    int _inv=inv(tot);
    for (int i=1;i<=n;i++){
        if (i==now)continue;
        if (a[i]<a[now])s+=_inv*(dfs(i,0)+abs(now-i)),s%=mod;
        else if (a[i]==a[now]&&flag==0)s+=_inv*(dfs(i,1)+abs(now-i)),s%=mod;
    }
    return f[now][flag]=s;
}
signed main(){
    cin>>n;
    for (int i=1;i<=n;i++)cin>>a[i],mx=max(mx,a[i]),mn=min(mn,a[i]);
    memset(f,-1,sizeof(f));
    for (int i=1;i<=n;i++){
        if (a[i]==mx){
            cout<<dfs(i,0)<<endl;
            return 0;
        }
    }
    return 0;
}

```

然后考虑满分dp，先按高度排序，然后相同高度一起转移。

有两种转移情况：相同高度与不同高度。

设 $g_{i}$ 表示由不同高度转移，$f_{i}$ 表示两种转移均可。

$g_{i}$ 直接由 之前的前缀和 与 当前点到之前点的距离和 求出。

第二种转移情况则由 $g_{i}$ 之和 与 当前点到相同高度点的距离和求出（使用容斥原理算出：用当前点到所有点的距离和减去当前点到之前点的距离和）。

$f_{i}$ 直接用两种转移乘上相应概率求出。

对于距离和的求法，可以参考[这题](https://www.luogu.com.cn/problem/P2345)。

详见代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
#define mod 998244353
using namespace std;
int n,g[500005],f[500005],dis[500005];
int ans,sum;
struct node{
    int pos,h;
}a[500005];
bool cmp(node a,node b){
    return a.h<b.h;
}
inline int pw(register int a,register int p){
    if (p==0)return 1;
    register int t=pw(a,p/2);
    t=t*t%mod;
    if (p%2==1)t=t*a%mod;
    return t;
}
inline int inv(register int a){
    return pw(a,mod-2);
}
inline void getmod(register int &a){
    a=(a%mod+mod)%mod;
    return;
}
struct BIT{
    int tree[1000005];
    inline void mem(){
        memset(tree,0,sizeof(tree));
        return;
    }
    inline int lowbit(register int &x){
        return x&(-x);
    }
    inline int query(register int pos){
        int ans=0;
        while(pos)ans+=tree[pos],getmod(ans),pos-=lowbit(pos);
        return ans;
    }
    inline void add(register int pos,register int val){
        while(pos<=n)tree[pos]+=val,getmod(tree[pos]),pos+=lowbit(pos);
        return;
    }
}bit1,bit2;
inline void add(int pos){
    bit1.add(pos,1);
    bit2.add(pos,pos);
    return;
}
inline void del(int pos){
    bit1.add(pos,-1);
    bit2.add(pos,-pos);
}
inline int ask(int pos){
    register int ans=bit1.query(pos-1)*pos-bit2.query(pos-1);
    getmod(ans);
    ans+=(bit2.query(n)-bit2.query(pos))-(bit1.query(n)-bit1.query(pos))*pos;
    getmod(ans);
    return ans;
}
signed main(){
    cin>>n;
    for (int i=1;i<=n;i++)scanf("%lld",&a[i].h),a[i].pos=i;
    sort(a+1,a+1+n,cmp);
    bit1.mem();
    bit2.mem();
    for (int i=1;i<=n;){
        register int j=i,nowsum=0;
        while(a[j].h==a[i].h)j++;
        for (register int k=i;k<j;k++){
            dis[k]=ask(a[k].pos);
            getmod(dis[k]);
            g[k]=sum+dis[k];
            getmod(g[k]);
            g[k]*=inv(i-1);
            getmod(g[k]);
            nowsum+=g[k];
            getmod(nowsum);
        }
        for (register int k=i;k<j;k++)add(a[k].pos);
        for (register int k=i;k<j;k++){
            register int now=nowsum+ask(a[k].pos)-dis[k]-g[k];
            now*=inv(j-i-1);
            getmod(now);
            f[k]=(inv(j-2)*(i-1)%mod)*g[k]%mod+(inv(j-2)*(j-i-1)%mod)*now%mod;
            getmod(f[k]);
        }
        for (register int k=i;k<j;k++){
            sum+=f[k];
            getmod(sum);
        }
        i=j;
    }
    cout<<f[n]<<endl;    
    return 0;
}
```

考场上JK用严格线性的算法吊打了std...

---

## 作者：all_for_god (赞：3)

题意：[P6375 「StOI-1」小 Z 的旅行](https://www.luogu.com.cn/problem/P6375)

给定一座山，每座山有一个高度，只能向更低的山走或者向高度相同的山走，要求不能向高度相同的山连续走两次，不能原地不动。
每次走的权值都是两座山之间的坐标差的绝对值。走的山会从所有可以走的山中等概率随机选。求从最高的山到最低的山的期望权值。保证最高与最低的山唯一。

## 思路

看到期望，显然考虑 DP。
发现从高到低不好弄，因此考虑从最低的山依次向最高的山转移。这样我们显然先将点按山的高度从小到大排序，然后按顺序依次考虑。

由于有不能连续走的要求，因此我们设 $f_{i,0/1}$ 表示从第 $i$ 个点开始，能否再连续走高度相同的山，走到高度最低的山的期望权值。其中 $f_{i,0}$ 表示不能再连续走，$f_{i,1}$ 反之。

然后发现 $f_{i,0}$ 只能从比其低的山转移而来，而转移后就一定可以再连续走，因此有转移：

$$
f_{i,0}=\frac{\sum_{h_j<h_i} f_{j,1}+|x_i-x_j|}{\sum_j [h_j<h_i]}
$$

其中 $x_i$ 表示排完序后第 $i$ 个点在序列中的原坐标
由于我们已经按高度排序，因此发现这就是一个前缀和而已，高度比 $h_i$ 小的点数也是好求的。因此我们设 $num0_i$ 表示高度低于 $h_i$ 的点数。

然后对于 $f_{i,1}$，其有概率走到高度比 $h_i$ 低的点，这时同样也是从 $f_{j,1}$ 转移而来，也有概率走到比 $h_i$ 高的点，这时由于不能连续走因此就要从 $f_{j,0}$ 转移而来。
注意还要除以总的方案数。我们同样定义一个 $num1_i$ 表示高度小于等于 $h_i$ 的点数。综上，有转移：

$$
f_{i,1}=\frac{(\sum_{h_j<h_i} f_{j,1}+|x_i-x_j|) + (\sum_{h_j=h_i}f_{j,0}+|x_i-x_j|)}{num1_i}
$$

可以发现分子上第一个括号的形式与 $f_{i,0}$ 是一样的，因此可以化简一下。注意要将选到比 $h_i$ 低的情况数乘上。化简后有转移：

$$
f_{i,1}=\frac{f_{i,0}\times num0_i + (\sum_{h_j=h_i}f_{j,0}+|x_i-x_j|)}{num1_i}
$$

可以发现对于两个转移，我们都可以将 $f_j,0/1$ 与绝对值的计算分开处理。显然排序后对于 $f$ 的求和仍然是前缀和就可以解决的。
然后我们就只需要处理距离的绝对值了。由于整个序列都不会变，因此我们可以将这个距离预处理出来。

我们可以通过树状数组从左到右扫一遍来做。具体而言，应另一篇题解的提醒，可以去做这种处理绝对值的 [模板题](https://www.luogu.com.cn/problem/P5094)。
需要注意的是，我么需要处理两种权值，一种是到所有 $h_j<h_i$ 的 $j$ 的权值，另一种是到所有 $h_j=h_i$ 的 $j$ 的权值，我们分别记为 $dis0_i$ 和 $dis1_i$。

## code

实现的话我没有用离散化，而是将所有 $h$ 相同的点一起转移。个人感觉这样思路比较清晰。
具体看代码吧。代码略有压行。（？）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int p=998244353,N=5e5+7;
int n,dis0[N],dis1[N],num0[N],num1[N],f[N][2],tmpsum[N],tmpcnt[N];
struct node{int x,h;}a[N];
struct edge{  //树状数组 
	int tr[N];
	void modify(int x,int w){while(x<=N-5)(tr[x]+=w)%=p,x+=x&(-x);}
	int query(int x){int res=0;while(x) (res+=tr[x])%=p,x-=x&-x;return res;}
}sum,cnt;  //分别记前缀坐标的和以及前缀坐标的个数 
bool cmp(node x,node y){return x.h<y.h;}
int ksm(int x,int k){
	int res=1;x%=p;
	while(k){if(k&1) res=res*x%p;x=x*x%p,k>>=1;}
	return res;
}
#define inv(x) (ksm(x,p-2))
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;for(int i=1,h;i<=n;i++) cin>>h,a[i]={i,h};
	sort(a+1,a+n+1,cmp);int tmp=0;
	for(int l=1;l<=n;){
		int r=l,z=0;
		while(a[r].h==a[r+1].h) ++r; //注意到高度小于的点数就是 l-1，等于的点数就是 r-l。（注意不能走到自己） 
		for(int i=l;i<=r;i++){
			int sum0=sum.query(a[i].x)%p,cnt0=cnt.query(a[i].x);tmpsum[i]=sum0,tmpcnt[i]=cnt0;
			num0[i]=l-1;dis0[i]=(cnt0*a[i].x%p-sum0 + (tmp-sum0-(l-1-cnt0)*a[i].x%p)+p)%p;//坐标小的与大的分开计算 
		}
		for(int i=l;i<=r;i++) sum.modify(a[i].x,a[i].x),cnt.modify(a[i].x,1),z+=a[i].x;  
		//先求出严格小于的再将权值相同的插入进树状数组，同时统计权值相同的权值和 
		for(int i=l;i<=r;i++){
			int sum1=(sum.query(a[i].x-1)%p-tmpsum[i]+p)%p,cnt1=(cnt.query(a[i].x-1)-tmpcnt[i]+p)%p;//这里将总的减去之前记录的高度小于的就是高度等于的信息 
			num1[i]=r-1;dis1[i]=(cnt1*a[i].x%p-sum1 + z-a[i].x-sum1-(r-l-cnt1)*a[i].x+p)%p;
		}
		l=r+1;tmp+=z;
	}
	f[1][0]=f[1][1]=0;int tmp0=0,tmp1=0;
	for(int l=2;l<=n;){
		int r=l,z=0,y=0;while(a[r].h==a[r+1].h) ++r;
		for(int i=l;i<=r;i++) f[i][0]=(tmp1+dis0[i])%p*inv(l-1)%p,z=(z+f[i][0])%p; 
		for(int i=l;i<=r;i++) f[i][1]=(f[i][0]*(l-1)%p*inv(r-1)%p+(z-f[i][0]+dis1[i]+p)%p*inv(r-1)%p)%p,y=(y+f[i][1])%p;
		(tmp0+=z)%=p,(tmp1+=y)%=p;
		l=r+1;
	}
	cout<<f[n][0]<<'\n';return 0;
	return 0;
}
```

---

## 作者：Chielo (赞：2)

山 $i$ 的高度为 $h_i$，横坐标是 $x_i$。

需要计算的有：
- 刚到达山 i，且到达山 i 前没有去过相同高度的山，所有这种方案的概率和 $p_{i}$
- 刚到达山 i，且到达山 i 前没有去过相同高度的山，的期望体力消耗 $d_{i}$

容易发现，如果 $h_i = h_j$，会有 $p_i = p_j$，因为只要有一个到达 $i$ 的方案，相应的也会有一个到达 $j$ 的方案，但是由于 $x_i \ne x_j$ 所以 $d_i \ne d_j$。

记 $c_i$ 为高度**小于或等于**山 $i$ 高度的山的数量，
记 $c'_i$ 为高度**小于**山 $i$ 高度的山的数量。

再记 $u_h$ 为刚到达高度为 $h$ 所有山 $i$ 的概率和（$\sum_{i, h_i = h}{p_i}$）；
再记 $v_h$ 为刚到达高度为 $h$ 的山的期望体力消耗（$\sum_{i, h_i = h}{d_i}$）。
这两个用来做在同一个高度上再跑一次的转移。

对于已经算完的山 $i$，考虑高度严格小于山 $i$ 的山 $j$。

一类转移是不走和 $i$ 高度相同的山，$p_j$ 会增加 $p_i / (c_i - 1)$，$d_j$ 会增加 $d_i / (c_i - 1) + p_i / (c_i - 1) \left|x_i - x_j\right|$。

另一类转移是走了一步和 $i$ 高度相同的山，我们将山 $i$ 看做是第二次到达的高度为 $h_i$ 的山，那么第二次到达山 $i$ 的概率是 $p'_i = (u_{h_i} - p_i) / (c_i - 1)$，期望体力消耗是：
$$d'_i = (v_{h_i} - d_i) / (c_i - 1) + \sum_{j, h_j = h_i, i \ne j}{p_j / (c_j - 1)  \left|x_i - x_j\right|}$$
式子里山 $i$, $j$ 高度相同，所以有：
$$d'_i = (v_{h_i} - d_i) / (c_i - 1) + p_i / (c_i - 1) \sum_{j, h_j = h_i, i \ne j}{ \left|x_i - x_j\right|}$$
显然，一个高度算完之后可以按横坐标 $x_i$ 的顺序求个前缀和。$\sum_{j, h_j = h_i, i \ne j}{ \left|x_i - x_j\right|}$ 就可以拆一下绝对值，用前缀和来求，记这个东西是 $w_i$。那么：
$$d'_i = (v_{h_i} - d_i) / (c_i - 1) + w_i p_i / (c_i - 1)$$

最终，另一类转移是，$p_j$ 会增加 $p'_i / c'_i$，$d_j$ 会增加 $d'_i / c'_i + p'_i / c'_i \left|x_i - x_j\right|$。

两类转移中的绝对值不好弄，想办法拆，考虑分治高度，也即 `cdq(l, r)` 之后，应当计算完高度在 $[l, r)$ 内所有山的信息。

首先肯定是递归地处理 `cdq(mid, r)`。然后考虑高度在 $[mid, r)$ 所有山给高度在 $[l, mid)$ 所有山算贡献。

我们把高度在 $[l, r)$ 所有的山按横坐标排序，然后类似前面的玩法维护一下 $p_i / (c_i - 1) x_i$ 的前缀和，以及 $p_i / (c_i - 1)$ 的前缀和，就可以推出来对于 $j$ 所有的转移值了。

写的话 cdq 里面可能会套个 `partition` 和 `sort`，每个元素在第 $i$ 层递归只会被某个递归处理到，每层是 $\mathcal{O}(n \log n)$ 的。离散化高度后，总的时间复杂度是 $\mathcal{O}(n \log^2 n)$。

---

## 作者：Lyrella (赞：1)

# 前言

看到机房的同学都在水题解于是跟着混一篇，~~虽然这题是我帮他调的。~~

# 简要题意

初始有一个人在**唯一最高**的点，每次可选择走向一个高度更低的点，也可以选择走向一个高度相同的点。但是只能在同一高度停留最多两次。每次移动有代价，假设从 $i$ 到 $j$，代价为 $|i-j|$，求到**唯一最低**点的期望代价。

# 题解

考虑倒着 dp。考虑每次可以从哪些地方转移。这道题状态其实挺明显的，我们设 $f_{i,0/1}$ 表示在 $i$ 点，并且之前没有/有在此高度停留时的代价。

如果不能从相同高度转移，就有：

$$
f_{i,1}={\sum\limits_{h_j<h_i}f_{j,0}+|i-j|\over cnt_{h_i-1}}
$$

否则，有：

$$
f_{i,0}={\sum\limits_{h_j<h_i}\left(f_{j,0}+|i-j|\right)\sum\limits_{h_j=h_i,i\neq j}\left(f_{j,1}+|i-j|\right)\over cnt_{h_i}-1}
$$

其中 $cnt_{i}$ 表示高度小于等于 $i$ 的点个数。下面解释式子，考虑一个点所在高度之前没有走过，现在第一次到就可以选择向下走或者在此高度停留，于是就有两种情况；否则只能向下走。

于是按高度从低到高 dp 即可。但是暴力转移显然过不去，所以你需要将点分类，对于左边和右边的点分别转移。把式子写开后你会发现需要支持快速维护区间点个数以及区间和，于是树状数组启动！

# 代码实现技巧

作为一发过并且最优解（目前）比第二名快 0.5s 我还是有发言权的。~~现在 rk2是机房同学看的我的代码写的/fn~~

首先就是对于需要处理的偏序关系通常用 ```vector``` 桶排序然后枚举 ```vector``` 里面的东西比较方便，并且能少一只 $\log$。


然后每次考虑先转移 $f_{i,1}$ 因为转移 $f_{i,0}$ 需要用它。对于树状数组我直接开的两棵，一棵维护点数一棵维护区间和。

差不多就这样了，具体可见代码。

# 代码

```cpp
int n, a[N], b[N], tot;
int f[N][2];
vector < int > h[N];
int sum, cnt;
struct tree{
    int t[N];
    inline void upd(int x, int y){for(; x <= n; x += x & - x)t[x] = Add(t[x], y);}
    inline int qry(int x){int s = 0; for(; x; x -= x & - x)s = Add(s, t[x]); return s;}
    inline int ask(int l, int r){return l > r ? 0 : Sub(qry(r), qry(l - 1));}
}ts, tc;

const string FileName = "";
signed main(){
    n = rd(); for(int i = 1; i <= n; ++i)a[i] = b[i] = rd();
    sort(b + 1, b + 1 + n); tot = unique(b + 1, b + 1 + n) - b - 1;
    for(int i = 1; i <= n; ++i)a[i] = lower_bound(b + 1, b + 1 + tot, a[i]) - b, h[a[i]].push_back(i);
    cnt = h[1].size(); for(int i : h[1])ts.upd(i, i), tc.upd(i, 1);
    for(int ht = 2; ht <= tot; ++ht){
        int tmp = 0;
        for(int i : h[ht]){
            int tl = Sub(Mul(i, tc.ask(1, i)), ts.ask(1, i)), tr = Sub(ts.ask(i, n), Mul(i, tc.ask(i, n)));
            f[i][1] = Mul(Add(Add(tl, tr), sum), Inv(cnt)); tmp = Add(tmp, f[i][1]);
        }
        for(int i : h[ht])ts.upd(i, i), tc.upd(i, 1); cnt += h[ht].size();
        for(int i : h[ht]){
            int tl = Sub(Mul(i, tc.ask(1, i - 1)), ts.ask(1, i - 1)), tr = Sub(ts.ask(i + 1, n), Mul(i, tc.ask(i + 1, n)));
            f[i][0] = Mul(Add(Add(tl, tr), Add(sum, Sub(tmp, f[i][1]))), Inv(cnt - 1));
        }
        for(int i : h[ht])sum = Add(sum, f[i][0]);
    }
    cout << f[h[tot][0]][0];
    return 0;
}
```

---

## 作者：GIFBMP (赞：0)

首先我们看到这题就容易想到 DP。

设 $f_{x,0}$ 表示从第一次到达高度为 $h_x$ 的山时从编号为 $x$ 的山走到最低点的期望步数，$f_{x,1}$ 表示第二次到达高度为 $h_x$ 的山时从编号为 $x$ 的山走到最低点的期望步数。

我们记最低点的编号为 $p$，显然有 $f_{p,0}=0$。

然后我们考虑转移，记高度不超过 $i$ 的山的个数为 $t_i$，易得：

$$f_{x,1}=\dfrac{1}{t_{h_x-1}}\sum_{h_i<h_x}(|x-i|+f_{i,0})$$

$$f_{x,0}=\dfrac{1}{t_{h_x}-1}(\sum_{h_i<h_x}(|x-i|+f_{i,0})+\sum_{h_i=h_x}[i\ne x](f_{i,1}+|x-i|)$$

然后我们发现这个 $|x-i|$ 不太好处理，但我们发现 $|x-i|$ 可以被很容易提出来，于是我们维护一座山左边比自己低的山的个数，比自己低的山的编号和，高度不大于自己的山的个数，高度不大于自己的山的编号和。对于右边同样处理，转移即可被优化到 $\Theta(1)$。于是我们将 $h_i$ 离散化，再用两个树状数组维护即可。

至于如何处理后效性，我们离散化之后，对于从小到大的每个高度，先处理这个高度上的 $f_{x,1}$ 再处理这个高度上的 $f_{x,0}$，然后再去处理下一个高度即可。

总时间复杂度：$\Theta(n\log n)$。

Code:

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std ;
const int MAXN = 5e5 + 10 , mod = 998244353 ;
int n , h[MAXN] , t[MAXN] ;
typedef long long ll ;
ll f[MAXN][2] , c1[MAXN] , c2[MAXN] , g[MAXN][8] , s[MAXN] ;
void upd (ll *c , int x , ll k) {
	for (; x <= n ; x += (x & -x)) c[x] = (c[x] + k) % mod ;
}
ll query (ll *c , int x) {
	ll ret = 0 ;
	for (; x ; x -= (x & -x)) ret = (ret + c[x]) % mod ;
	return ret ;
}
ll qpow (ll x , ll p = mod - 2) {
	ll ret = 1 ;
	for (; p ; p >>= 1 , x = x * x % mod)
		if (p & 1) ret = ret * x % mod ;
	return ret ;
}
vector <int> G[MAXN] ;
int main () {
	scanf ("%d" , &n) ;
	for (int i = 1 ; i <= n ; i++) scanf ("%d" , &h[i]) , t[i] = h[i] ;
	sort (t + 1 , t + n + 1) ;
	int m = unique (t + 1 , t + n + 1) - t - 1 ;
	for (int i = 1 ; i <= n ; i++)
		h[i] = lower_bound (t + 1 , t + m + 1 , h[i]) - t , G[h[i]].push_back (i) ; 
	memset (t , 0 , sizeof (t)) ;
	for (int i = 1 ; i <= n ; i++) t[h[i]]++ ;
	for (int i = 1 ; i <= m ; i++) t[i] += t[i - 1] ;
	for (int i = 1 ; i <= n ; i++) {
		g[i][0] = query (c1 , h[i] - 1) ; g[i][1] = query (c2 , h[i] - 1) ;
		g[i][4] = query (c1 , h[i]) , g[i][5] = query (c2 , h[i]) ;
		upd (c1 , h[i] , i) , upd (c2 , h[i] , 1) ;
	}
	memset (c1 , 0 , sizeof (c1)) , memset (c2 , 0 , sizeof (c2)) ;
	for (int i = n ; i ; i--) {
		g[i][2] = query (c1 , h[i] - 1) , g[i][3] = query (c2 , h[i] - 1) ;
		g[i][6] = query (c1 , h[i]) , g[i][7] = query (c2 , h[i]) ; 
		upd (c1 , h[i] , i) , upd (c2 , h[i] , 1) ;
	}
	f[G[1][0]][0] = 0 ;
	for (int i = 2 ; i <= m ; i++) {
		s[i] = s[i - 1] ;
		ll ret = 0 ;
		for (int j = 0 ; j < G[i].size () ; j++) {
			int x = G[i][j] ;
			ll tmp = qpow (t[i - 1]) * ((g[x][2] - g[x][0] + mod) % mod + (g[x][1] - g[x][3] + mod) % mod * x % mod) % mod ;
			f[x][1] = (tmp + s[i - 1] * qpow (t[i - 1]) % mod) % mod ;
			ret = (ret + f[x][1]) % mod ; 
		}
		for (int j = 0 ; j < G[i].size () ; j++) {
			int x = G[i][j] , cnt = t[i] - 1 ;
			ll tmp = qpow (cnt) * ((g[x][6] - g[x][4] + mod) % mod + (g[x][5] - g[x][7] + mod) % mod * x % mod) % mod ;
			f[x][0] = (tmp + s[i - 1] * qpow (cnt) % mod + (ret - f[x][1] + mod) % mod * qpow (cnt) % mod) % mod ;
			s[i] = (s[i] + f[x][0]) % mod ;
		}
	}
	printf ("%lld\n" , f[G[m][0]][0]) ;
	return 0 ;
} 
```

---

