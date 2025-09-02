# [AGC011F] Train Service Planning

## 题目描述

在高桥王国中有一条铁路，这条铁路分为$n$个区间$1⋯n$和$n+1$个站台$0⋯n$，区间$i$连接站台$i-1$和$i$

一列火车经过区间$i$会消耗$A_i$的时间，每个区间的铁路是双向的或单向的，如果$B_i=1$那么区间$i$是单向的，否则它是双向的

现在すぬけ(snuke)君想要设计一个火车时间表，满足以下约定

所有的火车要么从站台$0$到站台$n$，要么从站台$n$到站台$0$

对任意终点为$n$的火车，如果它在$t$时刻离开站台$i−1$并开往站台$i$，那么它必须在$t+A_i$时刻到达$i$站台，对反方向要求相同

对任意终点为$n$的火车，如果它在$s$时刻到达站台$i$并在$t$时刻离开站台$i$，那么一列经过站台$i$的终点为$n$的火车必须在$s+K$时刻到达站台$i$并在$t+K$时刻离开站台$i$，对反方向要求相同

在任意时刻不能有两列相向而行的火车在单向区间内互相穿过

现在你要找出一个时间表，使得一列火车从$0$到$n$和从$n$到$0$的时间之和最短，观察样例$1$可以帮助你更好地理解题目

## 样例 #1

### 输入

```
3 10
4 1
3 1
4 1```

### 输出

```
26```

## 样例 #2

### 输入

```
1 10
10 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
6 4
1 1
1 1
1 1
1 1
1 1
1 1```

### 输出

```
12```

## 样例 #4

### 输入

```
20 987654321
129662684 2
162021979 1
458437539 1
319670097 2
202863355 1
112218745 1
348732033 1
323036578 1
382398703 1
55854389 1
283445191 1
151300613 1
693338042 2
191178308 2
386707193 1
204580036 1
335134457 1
122253639 1
824646518 2
902554792 2```

### 输出

```
14829091348```

# 题解

## 作者：FlashHu (赞：12)

神仙思维题还是要写点东西才好。

## 建立数学模型

这种很抽象的东西没有式子描述一下显然是下不了手的。

因为任何位置都以$k$为周期，所以我们只用关心一个周期，也就是以下数都在膜$k$意义下。

设$a_i$表示$i$号区间长度；

对于上行列车（$0\rightarrow n$）设$p_0$表示出发时刻，$p_i(i\ge1)$表示在$i$站停靠时间；

对于下行列车（$0\leftarrow n$）设$-q_0$表示到站时刻，$q_i(i\ge1)$表示在$i$站停靠时间；

（转化成$-q_0$是为了后面表示方便）

用大写字母$A,P,Q$分别表示它们的前缀和。

如果某区间$b_i=1$，则两列车的行驶时间区间不交，即
$$(P_{i-1}+A_{i-1},P_{i-1}+A_i)\cap(-Q_{i-1}-A_i,-Q_{i-1}-A_{i-1})=\emptyset$$

区间不交即端点不被包含，可以列出不等式（被取模了所以看着比较奇怪）
$$\begin{cases}P_{i-1}+A_i\le-Q_{i-1}-A_i\\P_{i-1}+A_{i-1}\ge-Q_{i-1}-A_{i-1}\end{cases}$$
记$x=P_{i-1}+Q_{i-1}$，移项，解得$x\in[-2A_{i-1},-2A_i]$

因为$P,Q$是递增的，所以我们的问题变成了：

有若干个限制区间$[l_i,r_i]$，你手头有一个数$x$，初值任选，每次可以加一个非负整数使它落在区间内，求最少总共加多少能满足限制。

## 优化求解

考虑这样一个贪心的决策过程：

假设我们知道当前的$x$，我们需要统计它最少总共被加了多少。我们看上一个限制区间。

如果$x$被上一个区间包含，那么我们看上上个区间。

如果$x$没有被上一个区间包含，则$x$从区间的右端点加过来的代价最小，我们继续对上上个区间的右端点进行决策。

发现我们决策的中间状态只和区间右端点有关，所以我们设$f_i$表示决策到第$i$个区间时，$x=r_i$的最小代价。

我们对于每个值维护最后一个没有包含这个值的区间编号，每次取出$r_i$对应的编号（记为$j$），用$f_j+r_i-r_j$更新$f_i$，并将$[r_i+1,l_i-1]$的编号全部设为$i$。

最后把所有的$l_i$丢进去查一下取个$\min$加上$2A_n$就是答案。

因为是区间设置所以可以珂朵莉树维护，不用离散化，因为随机数据的编号段数不会太大所以平均情况下跑得比线段树还快。

特判：如果$2a_i>k$那么`puts("-1")`
```cpp
#include<bits/stdc++.h>
#define LL long long
#define R register int
#define G if(++ip==ie)if(fread(ip=buf,1,SZ,stdin))
using namespace std;
const int SZ=1<<19,N=1e5+9;
char buf[SZ],*ie=buf+SZ,*ip=ie-1;
inline int in(){
	G;while(*ip<'-')G;
	R x=*ip&15;G;
	while(*ip>'-'){x*=10;x+=*ip&15;G;}
	return x;
}
int k,l[N],r[N];LL f[N];bool b[N];
struct Node{
	int r;mutable int v;
	inline Node(R a,R b=0):r(a),v(b){}
	inline bool operator<(const Node&a)const{return r<a.r;}
};
typedef set<Node>::iterator IT;
set<Node>s;
inline IT Split(R p){
	IT i=s.lower_bound(Node(p));
	return i->r!=p?s.insert(Node(p,i->v)).first:i;
}
inline void Set(R l,R r,R v){
	if(l>r)return;
	IT il=Split(l-1),ir=Split(r);
	ir->v=v;s.erase(++il,ir);
}
inline LL Calc(R p){
	R j=s.lower_bound(Node(p))->v;
	return j?f[j]+(p-r[j]+k)%k:0;
}
int main(){
	R n=in();LL k=::k=in(),a=0,a1=0,ans=1e18;
	s.insert(Node(-1));
	s.insert(Node(k-1));
	for(R i=1;i<=n;++i){
		a1=a;a+=in();
		if(!(b[i]=in()&1))continue;
		if(2*(a-a1)>k)return puts("-1"),0;
		l[i]=(-2*a1%k+k)%k;r[i]=(-2*a%k+k)%k;
		f[i]=Calc(r[i]);
		if(l[i]>r[i])Set(r[i]+1,l[i]-1,i);
		else Set(0,l[i]-1,i),Set(r[i]+1,k-1,i);
	}
	for(R i=1;i<=n;++i)
		if(b[i])ans=min(ans,Calc(l[i]));
	cout<<ans+2*a<<endl;
	return 0;
}
```

---

## 作者：Orion545 (赞：11)

# 广告

[蒟蒻のBlog,此处食用体验更佳](https://www.cnblogs.com/dedicatus545/p/9646722.html)

# 思路

## 模意义

这题真tm有意思
我上下楼梯了半天做出来的qwq

首先，考虑到每K分钟有一辆车，那么可以把所有的操作都放到模$K$意义下进行

这时，我们只需要考虑两边的两辆车就好了。

#### 定义一些称呼：

**上行：**从$0$~$n$的车

**下行：**从$n$~$0$的车

#### 定义数组：

$p[i](i=0...n)$表示上行车在站台$i$的停车时长

$q[i](i=0...n)$表示下行车在站台$i$的停车时长

$a[i](i=0...n-1)$表示第$i$的站台与第$i+1$个站台中间的行驶时间（也就是题目给定的数组）

我们再定义$S(a,i)$表示数组$a$从零开始到$i$的前缀和函数，即：

$S(a,i)=\sum_{j=0}^i a[j]$

## 区间不交

考虑两辆车合法的情况。显然，他们俩在每一段铁路上行驶的时间是一个区间。双向铁路不用管，一定合法，我们发现如果单向铁路上合法，那么上下行的车在某一段单向铁路上行驶的区间肯定不相交

我们把上下行车辆在铁路$k$上的行驶时间区间写出来：

**上行：**$(S(a,i-1)+S(p,i),S(a,i)+S(p,i))$

**下行：**$(-S(a,i-1)-S(q,i),-S(a,i)-S(q,i))$

注意这里的下行部分是一个很巧妙的转化：因为我们在模意义下运算，所以下行部分本来应该是用两个后缀和加在一起的，但是这样上下行式子不统一

所以，我们把后缀和看做总和减掉前缀和，那么总和可以调整为$K$的倍数，就没掉了，所以就是负的前缀和

这两段区间如果不交，那么显然**任意一个端点不在另外一个区间里面**

这样我们可以得到一批不等式，大概类似于这个形式：

$-2S(a,i-1)>S(p,i)+S(q,i)>-S(a,i-1)-S(a,i)$

最终化一下，可以得到这个结论：

$S(p,i)+S(q,i) \notin (-2\ast S(a,i),-2\ast S(a,i-1))$

可以看到对于每个$i$，**不可选的区间是固定的**

那么我们考虑在模$K$的意义下，右边这个区间的补集，我们设它为$[L[i],R[i]]$

$S(p,i)+S(q,i) \in [L[i],R[i]]$

## 问题变化

我们发现，本题的答案，实际上就是最小化的$S(p,n)+S(q,n)+2\ast S(a,n)$，等价于最小化$S(p,n)+S(q,n)$

这样，我们可以把问题转化为：

**给定$n$个区间，任选起点，走$n$步，第$i$步需要落在区间$i$中，求最小总路径长度**

注意这里的“走”实际上，从一个大的走向小的，是要走到$K$，然后从$0$再出来（因为我们是模$K$意义下的）

这样就可以变成一个$DP$问题了

## 线段树优化$DP$

我们现在考虑新的这个问题，显然可以使用$dp$来做

首先有一个贪心结论：如果起点已经确定了，那么每次需要走的时候，走到下一个区间的左端点肯定最优，证明显然

那么我们可以先预处理出来在每个起点出发后，一直走左端点直到走完，我需要的最小距离

### 预处理

定义$dp[i]$表示对于区间$[L[i],R[i]]$的左端点$L[i]$而言，一直走左端点到$n$的最短路径

那么我们倒着从$n$到$1$推这个$dp$

每推完一个$dp[i]$，我们就把区间$[L[i],R[i]]$的补集在线段树上的值，覆盖为$i$

然后推$dp[i]$时，每次查询$L[i]$位置的线段树上的值，设这个值是$j$

那么显然，**编号在区间$[i,j-1]$中的所有区间都覆盖了$L[i]$这个点**

所以直接在这里不动，就可以走完这些区间了

那么我们用$dp[j]+dis(L[i],L[j])$来更新$dp[i]$

然后再覆盖区间，就完成了$dp$预处理过程

### 统计答案！

最后一步，我们枚举所有出现的$L[i]$和$R[i]$，并把它们作为起点，求出答案。

显然如果不选这些端点的话，答案只会更劣

统计出的答案，就是原来问题中的$S(q,n)+$S(p,n)$，也就是我们要最小化的东西

加上$2S(a,n)$输出即可

### 做完啦~

# Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define ll long long
using namespace std;
inline ll read(){
    ll re=0,flag=1;char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-') flag=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') re=(re<<1)+(re<<3)+ch-'0',ch=getchar();
    return re*flag;
}
ll n,K,cnt,a[200010],b[200010],tmp[500010],seg[500010],L[200010],R[200010],dp[200010],sum[200010];
void push(ll num){
    if(!seg[num]) return;
    seg[num<<1]=seg[num<<1|1]=seg[num];
    seg[num]=0;
}
void change(ll l,ll r,ll ql,ll qr,ll num,ll val){
    if(ql>qr) return;
    if(l>=ql&&r<=qr){seg[num]=val;return;}
    push(num);
    ll mid=(l+r)>>1;
    if(mid>=ql) change(l,mid,ql,qr,num<<1,val);
    if(mid<qr) change(mid+1,r,ql,qr,num<<1|1,val);
}
ll query(ll l,ll r,ll num,ll pos){
    if(l==r) return seg[num];
    push(num);
    ll mid=(l+r)>>1;
    if(mid>=pos) return query(l,mid,num<<1,pos);
    else return query(mid+1,r,num<<1|1,pos);
}
ll ask(ll pos){
    ll choose=query(1,cnt,1,pos);
    if(!choose) return 0;
    return (dp[choose]+(tmp[L[choose]]-tmp[pos]+K)%K);
}
ll erfen(ll val){
    ll l=1,r=cnt,mid;
    while(l<r){
        mid=(l+r)>>1;
        if(tmp[mid]>=val) r=mid;
        else l=mid+1;
    }
    assert(val==tmp[l]);
    return l;
}
int main(){
    n=read();K=read();ll i;
    for(i=1;i<=n;i++) {
        a[i]=read();b[i]=read();
        sum[i]=(sum[i-1]+a[i]);
        if(b[i]==2) continue;
        if(2*a[i]>K){
            puts("-1");return 0;
        }
    }
    for(i=n;i>=1;i--){
        if(b[i]==1){
            L[i]=(-2ll*sum[i-1]%K+K)%K;
            R[i]=(-2ll*sum[i]%K+K)%K;
        }
        else L[i]=0,R[i]=K-1;
        tmp[++cnt]=L[i],tmp[++cnt]=R[i];
    }
    sort(tmp+1,tmp+cnt+1);
    cnt=unique(tmp+1,tmp+cnt+1)-tmp-1;
    for(i=n;i>=1;i--){
        L[i]=erfen(L[i]);
        R[i]=erfen(R[i]);
        dp[i]=ask(L[i]);
        if(L[i]>R[i]) change(1,cnt,R[i]+1,L[i]-1,1,i);
        else change(1,cnt,1,L[i]-1,1,i),change(1,cnt,R[i]+1,cnt,1,i);
    }
    ll ans=dp[1];
    for(i=cnt;i>=1;i--) ans=min(ans,ask(i));
    printf("%lld\n",ans+sum[n]*2ll);
}
```

---

## 作者：command_block (赞：8)

**题意** ： 有一条铁路，被 $n+1$ 个站台分为 $n$ 段。站台标号为  $0\sim n$ ，铁路标号为 $1\sim n$。

列车通过第 $i$ 段所需时间为 $t_i$ ，可能是双向的或单向的。

现在需要设计一张列车（循环）时刻表。

对于所有的列车，要么从站台 $0$ 前往站台 $n$ ，要么从站台 $n$ 前往站台 $0$ 。

在单向轨道内，不能有两辆相反方向的车互相穿过。列车只能在站点停车等待。

若有一辆开往 $n$ 的车在时刻 $s$ 到达站点 $i$ ，在时刻 $t$ 离开站点 $i$ ，则下一辆车恰好在时刻 $s+k$ 到达站点 $i$ ，在时刻 $t+k$ 离开站点 $i$ 。其中 $k$ 是给定常数。

需要使得时间表中 $0\rightarrow n$ 与 $n\rightarrow 0$ 的列车的所需时间和最短。回答这个最小值，或指出无解。

$n\leq 10^5$ ，时限$\texttt{2s}$。

------------

应用题啊……

当某个 $2t_i>k$ 则无解，否则必定有解。

记 $p_i$ 表示 $0\rightarrow n$ 的车在站点 $i$ 停靠等待的时间。

$q_i$ 表示 $n\rightarrow 0$ 的车在站点 $i$ 停靠等待的时间。

$St(i)=\sum_{j=1}^it_j,\quad Sp(i)=\sum_{j=0}^{i-1}p_j,\quad Sq(i)=\sum_{j=0}^{i-1}q_j$。

某个方向的车经过第 $i$ 段铁路的时间为一段区间，且每 $k$ 单位时间重复一次。

具体地，在模 $k$ 循环意义下 ：

上行车的区间为 $\big(St(i-1)+Sp(i),St(i)+Sp(i)\big)$

下行车的区间为 $\big(-St(i)-Sq(i),-St(i-1)-Sq(i)\big)$

实际上下行车的式子是全体减去前缀得到后缀，但是走一整次所需的时间是 $k$ 的倍数，所以在模 $k$ 意义下可以忽略。这样形式上会更统一。

若这是单向铁路，要求两个区间（在模 $k$ 意义下）不交。

$$\left\{
\begin{aligned}
St(i-1)+Sp(i)+ck&\notin \big(-St(i)-Sq(i),-St(i-1)-Sq(i)\big)\\
St(i)+Sp(i)+ck&\notin \big(-St(i)-Sq(i),-St(i-1)-Sq(i)\big)\\
-St(i)-Sq(i)+ck&\notin \big(St(i-1)+Sp(i),St(i)+Sp(i)\big)\\
-St(i-1)-Sq(i)+ck&\notin \big(St(i-1)+Sp(i),St(i)+Sp(i)\big)
\end{aligned}
\right.$$

$$\left\{
\begin{aligned}
Sp(i)+Sq(i)+ck&\notin \big(-St(i)-St(i-1),-2St(i-1)\big)\\
Sp(i)+Sq(i)+ck&\notin \big(-2St(i),-St(i)-St(i-1)\big)\\
-Sp(i)-Sp(i)+ck&\notin \big(St(i-1)+St(i),2St(i)\big)\\
-Sp(i)-Sq(i)+ck&\notin \big(2St(i-1),St(i)+St(i-1)\big)
\end{aligned}
\right.$$

记 $x_i=Sp(i)+Sq(i)$ ，上式可以统一为 ：

$$x_i+ck\notin \big(-2St(i-1),-2St(i)\big)$$

对 $x_{0\sim n}$ 的唯一约束是 ： 单调不减。

- 于是问题可以转化为 ：

  你有一个变量 $x$ ，初始值任意。
  
  每次会给出一个模 $k$ 意义下的区间，要求给 $x$ 加一定值，使得 $x$ 落在这个区间内。
  
  最小化加上的值的和。
  
  （在本题中，还需加上 $2St(n)$ 才是答案）
  
考虑 $\rm DP$。记 $dp_k[i]$ 为第 $k$ 次操作后使得 $x=i$ 所需的最小代价。

显然我们需要关心的 $i$ 一定为给出的某个端点。

边界 ： $dp_0[i]=0$。

每次操作时，设给出的模意义区间为 $[l,r]$ ，让 $[l,r]$ 以外的位置转移到 $l$ 上，然后将它们置为 $\inf$ ，其余不变。

维护 $dp_k[i]-i$ 的区间 $\min$ 即可。

复杂度 $O(n\log n)$。

```cpp
#include<algorithm>
#include<cstdio>
#define ll long long
#define MaxN 100500
using namespace std;
const ll INF=1ll<<60;
ll x[MaxN<<1];int tn;
struct Node{
  ll x;bool fl;
  inline void ladd(){x=INF;fl=1;}
}a[MaxN<<2];
inline void up(int u)
{a[u].x=min(a[u<<1].x,a[u<<1|1].x);}
void build(int l=1,int r=tn,int u=1)
{
  if (l==r){a[u].x=-x[l];return ;}
  int mid=(l+r)>>1;
  build(l,mid,u<<1);
  build(mid+1,r,u<<1|1);
  up(u);
}
inline void ladd(int u){
  if (a[u].fl){
    a[u<<1].ladd();
    a[u<<1|1].ladd();
    a[u].fl=0;
  }
}
int to,wfl,wfr;ll wfc,ret;
void qry(int l=1,int r=tn,int u=1)
{
  if (wfl<=l&&r<=wfr){
    ret=min(ret,a[u].x);
    return ;
  }int mid=(l+r)>>1;ladd(u);
  if (wfl<=mid)qry(l,mid,u<<1);
  if (mid<wfr)qry(mid+1,r,u<<1|1);
}
void clr(int l=1,int r=tn,int u=1)
{
  if (wfl<=l&&r<=wfr){a[u].ladd();return ;}
  int mid=(l+r)>>1;ladd(u);
  if (wfl<=mid)clr(l,mid,u<<1);
  if (mid<wfr)clr(mid+1,r,u<<1|1);
  up(u);
}
void chg(int l=1,int r=tn,int u=1)
{
  if (l==r){
    a[u].x=min(a[u].x,wfc-x[l]);
    return ;
  }int mid=(l+r)>>1;ladd(u);
  if (to<=mid)chg(l,mid,u<<1);
  else chg(mid+1,r,u<<1|1);
  up(u);
}
ll dfs(int l=1,int r=tn,int u=1)
{
  if (l==r)return a[u].x+x[l];
  int mid=(l+r)>>1;ladd(u);
  return min(dfs(mid+1,r,u<<1|1),dfs(l,mid,u<<1));
}
int n,m,k;
ll t[MaxN];
struct Data{ll l,r;}b[MaxN];
int main()
{
  scanf("%d%d",&n,&k);
  for (int i=1,op;i<=n;i++){
    scanf("%lld%d",&t[i],&op);
    if (op==1&&2*t[i]>k){puts("-1");return 0;}
    t[i]+=t[i-1];
    if (op==1)
      b[++m]=(Data){(k-2*t[i-1]%k)%k,(k-2*t[i]%k)%k};
  }
  for (int i=1;i<=m;i++){
    x[++tn]=b[i].l;
    x[++tn]=b[i].r;
  }x[++tn]=0;
  sort(x+1,x+tn+1);
  tn=unique(x+1,x+tn+1)-x-1;
  build();
  for (int i=1;i<=m;i++){
    int tl=lower_bound(x+1,x+tn+1,b[i].l)-x,
        tr=lower_bound(x+1,x+tn+1,b[i].r)-x;
    wfc=INF;
    if (tl<=tr){
      wfl=1;wfr=tl-1;
      if (wfl<=wfr){
        ret=INF;qry();clr();
        wfc=b[i].l+ret;
      }
      wfl=tr+1;wfr=tn;
      if (wfl<=wfr){
        ret=INF;qry();clr();
        wfc=min(wfc,b[i].l+k+ret);
      }
    }else {
      wfl=tr+1;wfr=tl-1;
      if (wfl<=wfr){
        ret=INF;qry();clr();
        wfc=b[i].l+ret;
      }
    }to=tl;chg();
  }printf("%lld",2*t[n]+dfs());
  return 0;
}
```

---

## 作者：myee (赞：4)

### 前言

想睡着了.jpg。醒了后就大概会了。

开始以为自己会 $O(n)$ 做法，后来发现读错题了……但是也简单。

### 思路

考虑到其实就是一个形如 $\searrow\rightarrow\searrow\rightarrow\searrow\rightarrow\nearrow\rightarrow\nearrow\rightarrow\nearrow$ 的曲线横向连续平移无限次，使得其在某些段无交，要求最小化水平距离（不包含中间的水平段）。

我们考虑从下往上扫描，然后容易发现，我们总可以将左半面的 $\rightarrow$ 加到右半部分去，从而减少讨论。

这样整个的形态就变成了 $\searrow\searrow\searrow\rightarrow\nearrow\rightarrow\nearrow\rightarrow\nearrow$。

显然每个 $\rightarrow$ 的长度可以不超过 $k-1$。

在扫描的过程中，我们计算出 $\rightarrow$ 总长模 $k$ 为 $0\sim k-1$ 时的最短总长，设为 $g_t$。

当此段允许双向时，我们总是不妨令此 $\rightarrow$ 长为 $0$，也即不用改变。

否则仅可单向，假设前面部分 $A$ 总和为 $s$，当前部分 $A$ 为 $a$，则有

$$g_t'=\begin{cases}+\infty&(-a,0)\cap(t+2s,t+2s+a)\neq\varnothing\text{ 在模意义下}\\g_t&\text{otherwise.}\end{cases}$$

$$g_t''=\begin{cases}\min_ss+g'_{(t+k-s)\bmod k}&g'_t=+\infty\\g'_t&\text{otherwise.}\end{cases}$$

考虑到非 $+\infty$ 的总是一段（模意义下的）区间，我们直接维护此段区间是怎样的分段函数即可。

我们先计算出不变的 $t$，容易发现，即为 $[-(2s\bmod k),k-2a-(2s\bmod k)]$；特别的，如果 $2a>k$，说明无解。

考虑暴力维护分段函数，初始 $g_t=0$。

每次操作为单点查询、区间修改为公差为 $1$ 的等差数列。最后全局取 $\min$。

因为数据规模较小，不用考虑什么线性做法了，直接 ODT 维护即可。

总复杂度 $O(n\log n)$。

### Code

ODT 维护算是一股清流了，核心代码蛮短的。

```cpp
struct node{
    uint l,r;llt k,b;node(uint l):l(l){}
    node(uint l,uint r,llt k,llt b):l(l),r(r),k(k),b(b){}
    friend bol operator<(node a,node b){return a.l<b.l;}
};
std::set<node>S;
std::set<node>::iterator split(uint p){
    auto iter=--S.upper_bound(node(p));if(iter->l==p)return iter;
    uint l=iter->l,r=iter->r;llt k=iter->k,b=iter->b;
    return S.erase(iter),S.insert(node(l,p,k,b)),S.insert(node(p,r,k,b)).first;
}
ullt find(uint p){auto iter=--S.upper_bound(node(p));return iter->k*p+iter->b;}
ullt A[100005];uint B[100005];
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    // freopen("QAQ.out","w",stdout);
#endif
    uint n;ullt k,s=0;scanf("%u%llu",&n,&k);
    for(uint i=0;i<n;i++)scanf("%llu%u",A+i,B+i);
    S.insert(node(0,k,0,0));
    for(uint i=n-1;~i;s+=A[i--])if(B[i]==1){
        if(A[i]*2>k)return puts("-1"),0;
        ullt l=(k-(2*s)%k)%k;ullt r=(l+k-2*A[i])%k;ullt w=find(r);
        if(l>r){
            auto iterr=split(l);auto iterl=split(r+1);
            S.erase(iterl,iterr),S.insert(node(r+1,l,1,w-r));
        }
        else{
            if(r!=k-1)S.erase(split(r+1),S.end()),S.insert(node(r+1,k,1,w-r));
            if(l)S.erase(S.begin(),split(l)),S.insert(node(0,l,1,w+k-r));
        }
    }
    ullt t=-1;
    for(auto s:S)_min(t,(ullt)(s.l*s.k+s.b));
    printf("%llu\n",t+s*2);
    return 0;
}
```


---

## 作者：Sky_Maths (赞：1)

我们尝试更加严谨的解决这道题，黑体是对一些没在其他题解上看到的内容的补充，或稍有不同，建议先看其他的题解了解一下。

首先，令 $0\to n$ 为上行，$n\to 0$ 为下行。

**假设已知下行到达 $0$ 处的时间为 $t$（相对于 $0$ 时上行从 $0$ 站出发而言），两车都不在 $0$ 站停留。**

上行为 $p$，下行为 $q$，路径长为 $a$。

**约定：$(L, R) + x = (L + x, R + x)$**

上行的时间区间为 $(Sp_{i - 1} + Sa_{i - 1}, Sp_{i - 1} + Sa_i) + dK, d\in \mathbb Z$。

下行的时间区间为 $(t - Sq_{i - 1} - Sa_{i}, t - Sq_{i - 1} - Sa_{i - 1}) + dK, d\in \mathbb Z$。

保证两者无交，可以求有交的集合的补集。

**考虑若相交**

**$t - Sq_{i - 1} - Sa_{i - 1}\in (Sp_{i - 1} + Sa_{i - 1}, Sp_{i - 1} + Sa_{i}] + dK$**

**$t - Sq_{i - 1} - Sa_{i} \in [Sp_{i - 1} + Sa_{i - 1}, Sp_{i - 1} + Sa_i) + dK$**

**即 $t - Sq_{i - 1} - Sp_{i - 1}\not\in (2Sa_{i - 1}, 2Sa_i) + dK$ 若右边单个长度 $\ge k$ 则为全集，此时无解**

**令 $dp_j$ 为当前第 $i$ 条边时 $Sp_i + Sp_i - t\equiv j \pmod k$ 时最小的 $Sp_i + Sq_i$。应是 $Sq_{i - 1} + Sp_{i - 1} - t \in [-2Sa_{i - 1}, -2Sa_i]$。** 线段树维护即可。

时间复杂度 $O(n\log n)$。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc011_f)

**题目大意**

> 给定 $n$ 段铁路连接站点 $0\sim n+1$，每隔 $k$ 时刻分别有一辆 $0\to n+1$ 和 $n+1\to 0$ 的列车发车，穿过第 $i$ 段铁路的时刻是 $t_i$。
>
> 安排两种列车在每个站点停靠的时间，使得对于若干条特殊铁路，两种列车穿过其的时间不交，最小化两种列车运行时间之和。
>
> 数据范围：$n\le 10^5$。

**思路分析**

在 $\bmod k$ 意义下考虑所有时间，那么从 $n+1\to 0$ 的列车等价于往时间轴负方向移动。

设 $x_i,y_i$ 表示两种方向的列车在第 $i$ 个站的停靠时间，对应的大写字母表示其数组前缀和。

那么我们要求就是 $[X_{i-1}+T_{i-1},X_{i-1}+T_i]$ 与 $[-Y_{i-1}-T_{i},-Y_{i-1}-T_{i-1}]$ 交集为空。

展开后可以得到这相当于 $X_{i-1}+Y_{i-1}\in[-2T_{i-1},-2T_i]$。

目标是最小化 $X_n+Y_n+2T_n$，直接 dp 设 $f_{i,j}$ 表示 $X_i+Y_i=j$ 的最小代价。

转移时 $f_{i,j}+x\to f_{i+1,(j+x)\bmod k}$，要求 $(j+x)\bmod k\in [l_i,r_i]$，发现每个 $j$ 都是某个 $l_i/r_i$，可以离散化。

直接把 $[l_i,r_i]$ 以外的 dp 值全部删除并插入到 $l_i$ 上即可，用 `map` 维护 dp 过程即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5;
const ll inf=1e18;
int n,m=0,p=0,K;
ll a[MAXN],L[MAXN],R[MAXN],w[MAXN*2];
map <int,ll> dp;
signed main() {
	scanf("%d%d",&n,&K);
	for(int i=1,op;i<=n;++i) {
		scanf("%lld%d",&a[i],&op);
		if(op==1&&2*a[i]>K) return puts("-1"),0;
		a[i]+=a[i-1];
		if(op==1) ++m,L[m]=(K-2*a[i-1]%K)%K,R[m]=(K-2*a[i]%K)%K,w[++p]=L[m],w[++p]=R[m];
	}
	sort(w,w+p+1),p=unique(w,w+p+1)-w;
	for(int i=0;i<=p;++i) dp[i]=0;
	for(int i=1;i<=m;++i) {
		int l=lower_bound(w,w+p,L[i])-w;
		int r=lower_bound(w,w+p,R[i])-w;
		ll z=inf;
		if(l<=r) {
			auto il=dp.begin(),ir=dp.lower_bound(l);
			for(auto it=il;it!=ir;++it) z=min(z,it->second+w[l]-w[it->first]);
			dp.erase(il,ir);
			il=dp.upper_bound(r),ir=dp.end();
			for(auto it=il;it!=ir;++it) z=min(z,it->second+w[l]-w[it->first]+K);
			dp.erase(il,ir);
		} else {
			auto il=dp.upper_bound(r),ir=dp.lower_bound(l);
			for(auto it=il;it!=ir;++it) z=min(z,it->second+w[l]-w[it->first]);
			dp.erase(il,ir);
		}
		if(dp.count(l)) dp[l]=min(dp[l],z);
		else dp[l]=z;
	}
	ll ans=inf;
	for(auto it:dp) ans=min(ans,it.second);
	printf("%lld\n",ans+2*a[n]);
	return 0;
}
```

---

