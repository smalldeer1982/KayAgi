# Greg and Array

## 题目描述

Greg 有一个数列 a{a1，a2，a3...an}和m个操作（不立即执行）
每个操作将以以下形式给出，如 li ri di，
（1<=li<=ri<=n）.每个操作的意思是 给区间[ali,ari]中每个数加上di；

Greg在纸上写下了K个问题，每个问题将以以下形式给出 如 xi，yi；
(1<=xi<=yi<=m)这意味着你应该对数组执行第xi.第xi+1.第xi+2...第yi个操作

现在Greg想知道，当操作执行之后数组a将会变得怎样，请帮帮他；

## 样例 #1

### 输入

```
3 3 3
1 2 3
1 2 1
1 3 2
2 3 4
1 2
1 3
2 3
```

### 输出

```
9 18 17
```

## 样例 #2

### 输入

```
1 1 1
1
1 1 1
1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 3 6
1 2 3 4
1 2 1
2 3 2
3 4 4
1 2
1 3
2 3
1 2
1 3
2 3
```

### 输出

```
5 18 31 20
```

# 题解

## 作者：William_Fangs (赞：4)

## 这道题其实很简单
~~（虽然我UKE了两次）~~  
要注意几点  
第一个，题目中给出的m个操作不是立即执行的，你可以把它们理解成m个函数，预设好但不一定会调用。  
第二个，数据范围很大，不使用一定技巧可能会超时~~（试试线段树）~~  
因此本道题可以使用**差分技巧**。  
主要有两种方式差分：  
#### 1. 对数组进行差分  
```cpp
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d",&x,&y);
        for(int j=x;j<=y;j++)
        {
            delta[opt[j].l]+=opt[j].val;
            delta[opt[j].r+1]-=opt[j].val;
        }
    }
```
#### 2.针对操作（函数）进行差分
```cpp
for(int i=1;i<=k;i++)
    {
        read(x);
        read(y);
        cnt[x]++;//cnt[i]表示第i个函数的执行次数
        cnt[y+1]--;
    }
```  
这里很明显第二种方式更优  
当然你也可以使用第一种方式 ~~（[血淋淋的教训](https://www.luogu.org/recordnew/show/19398903)）~~  
  
上代码
```cpp
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;
inline void read( ll &x ) {
    x = 0; char ch = getchar();
    for( ; ch < '0' || ch > '9'; ch = getchar() );
    for( ; ch >= '0' && ch <= '9'; ch = getchar() )
        x = x * 10 + ch - '0';
    return;
}
const int N=1e5+10;
ll a[N];
ll delta[N];
ll cnt[N];
ll d;
struct node
{
	ll l;
	ll r;
	ll val;
};
node opt[N];
int n,m,k;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		delta[i]=a[i]-a[i-1];
	}
	for(int i=1;i<=m;i++)
	{
		read(opt[i].l);
		read(opt[i].r);
		read(opt[i].val);
	}
	ll x,y;
	for(int i=1;i<=k;i++)
	{
		read(x);
		read(y);
		cnt[x]++;
		cnt[y+1]--;
	}
	for(int i=1;i<=m;i++)
	{
		cnt[i]+=cnt[i-1];
	}
	for(int i=1;i<=m;i++)
	{
		 delta[opt[i].l]+=opt[i].val*cnt[i];
		 delta[opt[i].r+1]-=opt[i].val*cnt[i];
	}
	for(int i=1;i<=n;i++)
	{
		delta[i]+=delta[i-1];
		cout<<delta[i]<<' ';
	}
	return 0;
}
```
  
谢谢观看，谢谢。

---

## 作者：Sincerin (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF295A)

## 题意

给定一个数字 $n$ 表示序列长度，$m$ 表示候选操作的种类数，并且这 $m$ 次操作都是**非在线**的（即不需要在操作时即时回答，只在最后统计答案），$k$ 表示执行操作个数。

第二行给定 $n$ 个数，即序列 $a$。

接下来 $m$ 行每行给定 $3$ 个数 $l_i \ r_i \ d_i$ 表示把 $a_i \ ( i \in [l_i \ , r_i ])$ 都加上 $d_i$。

最后 $k$ 行每行 $2$ 个数 $x_j \ y_j$ 表示执行所有的操作 $i \in [x_j \ , \ y_j]$。要求输出最后操作完的序列。

- $1 \leq n,m,k,a_i,d_i \leq 10^5$
- $1 \leq l_i \leq r_i \leq n$
- $1 \leq x_j \leq y_j \leq n$

## 解析

首先我相信在看到这道题的时候大家应该都想到了写线段树吧，我也确实写了线段树。但是 $\dots$ 当我写完代码后才看到了数据范围。这个  $\Theta(km \log n)$ 的时间复杂度真的让我流泪了（所以大家不要学我的这个坏习惯啊啊！）。


回归正题，不仅是限于普通离线查询，在线做法的树状数组处理区间修改的时候也会经常用到一个很基础的线性数据结构——差分！

顾名思义，对于一个序列 $A$，它的差分序列 $C$ 就是由序列 $A$ 相邻两项的差构成的。

即：

$$C_i=A_i-A_{i-1}$$

例如：

$$A=\{ 1,4,6,7,9,11,17 \}$$

则可递推出它的差分序列 $C$：

$$C=\{ 1,3,2,1,2,2,6 \}$$

这个时候我们再去求一下差分序列 $C$ 的[前缀和](https://blog.csdn.net/qq_45914558/article/details/107385862?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-107385862-blog-121739364.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-107385862-blog-121739364.pc_relevant_default&utm_relevant_index=1)序列 $S$：

$$S=\{ 1,4,6,7,9,11,17 \}$$

然后你就会发现，对一个序列的差分序列做前缀和，就可以得到原序列。有了这个思想，我们在进行区间修改的时候就可以把时间复杂度降低到 $\Theta(1)$。

即把区间 $A_i (i \in [l,r])$ 都加一个数 $d$ 时，只需要维护一个全零数组 $C$ 作为差分数组，对于 $C_{l}$ 处加 $d$，对于 $C_{r+1}$ 处减 $d$，让 $d$ 产生的影响从 $l$ 处开始，在 $r+1$ 处消除，影响范围为区间 $ [l,r]$。

最后在维护数组 $C$ 前缀和的时候你就会发现区间 $[l,r]$ 的所有数 $S_i (i \in [l,r])$ 都变成了 $d$。


有了这个思想，不难写出下面的代码。

```cpp
cin>>x>>y; 
for(int i=x;i<=y;++i)
{
	c[l[i]]+=d[i];
	c[r[i]+1]-=d[i];
}
```
但是这样的操作一共有 $k$ 次，这段代码的时间复杂度已经来到了 $\Theta(km)$。我甚至抱有一丝侥幸心理地写了快读快写然后加了火车头，但毫无意外地[T飞了](https://www.luogu.com.cn/record/98008641)。

----------

既然时间复杂度不正确，那我们就来考虑一下别的写法。对于每次选择操作区间 $[l,r]$，我们也可以再进行一次差分，是对于操作序号对应的操作次数的差分，到最后做前缀和再统计进行的操作，相当于一次延迟操作。

这样上一个写法的 $\Theta(km)$ 就可以被毫无疑问地干到 $\Theta(k)$ ,整份代码的时间复杂度为 $\Theta(n)$ 级别，完全可以过。

到这里本篇题解已经接近尾声了，我贴个完整代码吧。

## AC Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
#include<map> 
using namespace std;
#define int long long//要开long long!!! 
const int N=100005;
int n,m,k,x,y;
int a[N],c[N],tag[N];
struct node{//结构体更方便 
	int l,r;
	int dat;
}t[N];
map<int,int>existed;
signed main()
{
	cin.tie(0)->ios::sync_with_stdio(false);
	cout.tie(0); //cin,cout优化 
	cin>>n>>m>>k;
	for(register int i=1;i<=n;++i) cin>>a[i];
	for(register int i=1;i<=m;++i) 
	{
		cin>>t[i].l>>t[i].r>>t[i].dat;
	} 
	for(register int i=1;i<=k;++i)
	{
		cin>>x>>y; 
		tag[x]++;//差分记录操作次数 
		tag[y+1]--;
	}
	for(register int i=1;i<=m;++i) tag[i]+=tag[i-1];
	for(register int i=1;i<=m;++i)
	{
		c[t[i].l]+=t[i].dat*tag[i];//二次差分把tag[i]次操作补上 
		c[t[i].r+1]-=t[i].dat*tag[i];
	}
	for(register int i=1;i<=n;++i)
	{
		c[i]+=c[i-1];//前缀和 
		a[i]+=c[i];//加上差分数组 
	}
	for(register int i=1;i<=n;++i) cout<<a[i]<<' '; //输出 
	return 0;//完结撒花！ 
}

```
[AC Record](https://www.luogu.com.cn/record/98010165)


---

## 作者：Sata_moto (赞：2)

#### 看了题解里dalao代码后...蒟蒻表示很好奇0.0
#### 这题线段树好想好写，为什么不用线段树呢？
线段树不熟请自行跳转：[P3372 【模板】线段树 1](https://www.luogu.org/problemnew/show/P3372)

---
### 蒟蒻线段树题解奉上
---
首先我们看一看数据规模：(1<=n,m,k<=10^5)

似乎线段树可以直接过是不是?

于是我们上我们的线段树模板：
```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=100010;
typedef long long ll;//为防止出现意外，我将所有int换为了long long
struct node
{
    ll l,r;
    ll add;
} cz[N];//存储操作
ll n,m,K;
ll d[N];
ll tot_root;//线段树根节点
struct node0
{
    ll l,r;//管辖范围
    ll lc,rc;//左右儿子
    ll sum,delay;//块标记和懒惰标记
} tree[N*2];//我用的是动态存储，二倍空间即可
ll tot;
void push_up(ll root)//请不要纠结我奇葩的线段树写法
{
    ll lc=tree[root].lc,rc=tree[root].rc;
    tree[root].sum=tree[lc].sum+tree[rc].sum+tree[lc].delay*(tree[lc].r-tree[lc].l+1)+tree[rc].delay*(tree[rc].r-tree[rc].l+1);
}
void push_down(ll root)//请不要纠结我奇葩的线段树写法
{
    ll lc=tree[root].lc,rc=tree[root].rc;
    tree[lc].delay+=tree[root].delay;
    tree[rc].delay+=tree[root].delay;
    tree[root].delay=0;
}
void creat(ll & root,ll l,ll r)//请不要纠结我奇葩的线段树写法
{
    root=++tot,tree[root].l=l,tree[root].r=r;
    tree[root].lc=tree[root].rc=-1,tree[root].delay=0;
    if(l==r)
        tree[root].sum=d[l];
    else
    {
        ll mid=(l+r)/2;
        creat(tree[root].lc,l,mid),creat(tree[root].rc,mid+1,r);
        push_up(root);
    }
}
void add(ll root,ll l,ll r,ll zhi)//请不要纠结我奇葩的线段树写法
{
    if(tree[root].l>=l && tree[root].r<=r)
    {
        tree[root].delay+=zhi;
        return ;
    }
    push_down(root);
    ll mid=(tree[root].r+tree[root].l)/2;
    if(l>mid)
        add(tree[root].rc,l,r,zhi);
    else if(r<=mid)
        add(tree[root].lc,l,r,zhi);
    else
        add(tree[root].lc,l,mid,zhi),add(tree[root].rc,mid+1,r,zhi);
    push_up(root);
}
void dfs(ll root,ll l,ll r)//请不要纠结我奇葩的线段树写法
{
    if(l==r)
    {
        d[l]=tree[root].sum+tree[root].delay;
        return ;
    }
    push_down(root);
    ll mid=(tree[root].r+tree[root].l)/2;
    if(l>mid)
        dfs(tree[root].rc,l,r);
    else if(r<=mid)
        dfs(tree[root].lc,l,r);
    else
        dfs(tree[root].lc,l,mid),dfs(tree[root].rc,mid+1,r);
}
int main()
{
    scanf("%lld %lld %lld",&n,&m,&K);
    for(ll k=1; k<=n; k++)
        scanf("%lld",&d[k]);
    for(ll k=1; k<=m; k++)
        scanf("%lld %lld %lld",&cz[k].l,&cz[k].r,&cz[k].add);//读入操作
    creat(tot_root,1,n);
    for(ll k=1; k<=K; k++)
    {
        ll a,b;
        scanf("%lld %lld",&a,&b);
        for(int i=a;i<=b;i++)//对于每一次询问做出修改
            add(tot_root,cz[i].l,cz[i].r,cz[i].add);
    }
    dfs(tot_root,1,n);
    for(ll k=1;k<=n;k++)
        printf("%lld ",d[k]);
    return 0;
}
```
然后我们发现，我们愉快的超时了...

---

为什么超时？

我们算一下我们的复杂度...

K次询问...

一次询问可以执行最多m次修改...

一次修改消耗O（logN）...

复杂度大概是O (mklogN)...

那么我们可否就此进行一定优化？

首先，修改所需复杂度是变不了的

那我们就只能从修改次数上入手...

明显，对同一段区间进行k次增加add的修改等价于一次增加k*add的修改

那么我们完全可以把每种修改的执行次数记下来，然后对它们分别进行一次修改嘛

---
上代码

```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=100010;
typedef long long ll;
struct node
{
    ll l,r;
    ll add;
} cz[N];
ll cl[N];//记录每次修改的次数
ll n,m,K;
ll d[N];
ll tot_root;
struct node0
{
    ll l,r;
    ll lc,rc;
    ll sum,delay;
} tree[N*2];
ll tot;
void push_up(ll root)
{
    ll lc=tree[root].lc,rc=tree[root].rc;
    tree[root].sum=tree[lc].sum+tree[rc].sum+tree[lc].delay*(tree[lc].r-tree[lc].l+1)+tree[rc].delay*(tree[rc].r-tree[rc].l+1);
}
void push_down(ll root)
{
    ll lc=tree[root].lc,rc=tree[root].rc;
    tree[lc].delay+=tree[root].delay;
    tree[rc].delay+=tree[root].delay;
    tree[root].delay=0;
}
void creat(ll & root,ll l,ll r)
{
    root=++tot,tree[root].l=l,tree[root].r=r;
    tree[root].lc=tree[root].rc=-1,tree[root].delay=0;
    if(l==r)
        tree[root].sum=d[l];
    else
    {
        ll mid=(l+r)/2;
        creat(tree[root].lc,l,mid),creat(tree[root].rc,mid+1,r);
        push_up(root);
    }
}
void add(ll root,ll l,ll r,ll zhi)
{
    if(tree[root].l>=l && tree[root].r<=r)
    {
        tree[root].delay+=zhi;
        return ;
    }
    push_down(root);
    ll mid=(tree[root].r+tree[root].l)/2;
    if(l>mid)
        add(tree[root].rc,l,r,zhi);
    else if(r<=mid)
        add(tree[root].lc,l,r,zhi);
    else
        add(tree[root].lc,l,mid,zhi),add(tree[root].rc,mid+1,r,zhi);
    push_up(root);
}
void dfs(ll root,ll l,ll r)
{
    if(l==r)
    {
        d[l]=tree[root].sum+tree[root].delay;
        return ;
    }
    push_down(root);
    ll mid=(tree[root].r+tree[root].l)/2;
    if(l>mid)
        dfs(tree[root].rc,l,r);
    else if(r<=mid)
        dfs(tree[root].lc,l,r);
    else
        dfs(tree[root].lc,l,mid),dfs(tree[root].rc,mid+1,r);
}
int main()
{
    scanf("%lld %lld %lld",&n,&m,&K);
    for(ll k=1; k<=n; k++)
        scanf("%lld",&d[k]);
    for(ll k=1; k<=m; k++)
        scanf("%lld %lld %lld",&cz[k].l,&cz[k].r,&cz[k].add);
    for(ll k=1; k<=K; k++)
    {
        ll a,b;
        scanf("%lld %lld",&a,&b);
        for(int i=a;i<=b;i++)
        	cl[i]++;//表示从a到b的修改操作均应该多执行一次
    }
    creat(tot_root,1,n);
    for(ll k=1; k<=m; k++)
        if(cl[k]!=0)//如果没有该操作，就不需要修改了
            add(tot_root,cz[k].l,cz[k].r,cz[k].add*cl[k]);//对同一段区间进行cl[k]次增加add的修改等价于一次增加cl[k]*add的修改
    dfs(tot_root,1,n);
    for(ll k=1;k<=n;k++)
        printf("%lld ",d[k]);
    return 0;
}
```

---

然而我们会发现，还是有点过不去...

当然...你要是快读，inline，o1o2o3ofast之类的...

又或者你能拿出什么线段树dalao级优化的话...

A了当我没说...

---

那么，假如我们不用上述优化的话...我们应该怎么办呢？

让我们看看这段代码

```cpp
    for(ll k=1; k<=K; k++)
    {
        ll a,b;
        scanf("%lld %lld",&a,&b);
        for(int i=a;i<=b;i++)
        	cl[i]++;
    }
```
其实很明显，这里可以有一个差分优化的操作...

~~（说好的不用差分优化呢）~~

变成这样

```cpp
    for(ll k=1; k<=K; k++)
    {
        ll a,b;
        scanf("%lld %lld",&a,&b);
        cl[a]++,cl[b+1]--;//cl 表示差分数组 
    }
```
这样我们就少了一个循环，预处理复杂度从O(km)变成了O(k)...

然后就可以AC了...

---
AC代码：
```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=100010;
typedef long long ll;
struct node
{
    ll l,r;
    ll add;
} cz[N];
ll cl[N];
ll n,m,K;
ll d[N];
ll tot_root;
struct node0
{
    ll l,r;
    ll lc,rc;
    ll sum,delay;
} tree[N*2];
ll tot;
void push_up(ll root)
{
    ll lc=tree[root].lc,rc=tree[root].rc;
    tree[root].sum=tree[lc].sum+tree[rc].sum+tree[lc].delay*(tree[lc].r-tree[lc].l+1)+tree[rc].delay*(tree[rc].r-tree[rc].l+1);
}
void push_down(ll root)
{
    ll lc=tree[root].lc,rc=tree[root].rc;
    tree[lc].delay+=tree[root].delay;
    tree[rc].delay+=tree[root].delay;
    tree[root].delay=0;
}
void creat(ll & root,ll l,ll r)
{
    root=++tot,tree[root].l=l,tree[root].r=r;
    tree[root].lc=tree[root].rc=-1,tree[root].delay=0;
    if(l==r)
        tree[root].sum=d[l];
    else
    {
        ll mid=(l+r)/2;
        creat(tree[root].lc,l,mid),creat(tree[root].rc,mid+1,r);
        push_up(root);
    }
}
void add(ll root,ll l,ll r,ll zhi)
{
    if(tree[root].l>=l && tree[root].r<=r)
    {
        tree[root].delay+=zhi;
        return ;
    }
    push_down(root);
    ll mid=(tree[root].r+tree[root].l)/2;
    if(l>mid)
        add(tree[root].rc,l,r,zhi);
    else if(r<=mid)
        add(tree[root].lc,l,r,zhi);
    else
        add(tree[root].lc,l,mid,zhi),add(tree[root].rc,mid+1,r,zhi);
    push_up(root);
}
void dfs(ll root,ll l,ll r)
{
    if(l==r)
    {
        d[l]=tree[root].sum+tree[root].delay;
        return ;
    }
    push_down(root);
    ll mid=(tree[root].r+tree[root].l)/2;
    if(l>mid)
        dfs(tree[root].rc,l,r);
    else if(r<=mid)
        dfs(tree[root].lc,l,r);
    else
        dfs(tree[root].lc,l,mid),dfs(tree[root].rc,mid+1,r);
}
int main()
{
    scanf("%lld %lld %lld",&n,&m,&K);
    for(ll k=1; k<=n; k++)
        scanf("%lld",&d[k]);
    for(ll k=1; k<=m; k++)
        scanf("%lld %lld %lld",&cz[k].l,&cz[k].r,&cz[k].add);
    for(ll k=1; k<=K; k++)
    {
        ll a,b;
        scanf("%lld %lld",&a,&b);
        cl[a]++,cl[b+1]--;//cl 表示差分数组 
    }
    ll times=0;//根据差分特性，记录当前修改需要执行多少次
    creat(tot_root,1,n);
    for(ll k=1; k<=m; k++)
    {
        times+=cl[k];
        if(times!=0)
            add(tot_root,cz[k].l,cz[k].r,cz[k].add*times);
    }
    dfs(tot_root,1,n);
    for(ll k=1;k<=n;k++)
        printf("%lld ",d[k]);
    return 0;
}
```
---

### END

---


---

## 作者：ueettttuj (赞：2)

### 解法：两次差分

这题比较简单 ~~(难度评不上紫)~~ 。

首先，定义一个数组$num[i]$表示第$i$个操作被调用的次数。则对于$Greg$写下的第$i$个问题，$num[x_i]+1$ ，$num[y_i+1]-1$ ，最后求一遍前缀和，便可以算出每一个操作调用的次数。

然后，在定义一个数组$add[i]$表示第$i$个数在经过多次操作后**加的数**的值。对于第$i$操作，$add[l_i]+num[i]*d_i$ ，$add[r_i+1]-num[i]*d_i$ 。最后求一遍前缀和，便可以算出每个数增加的量，再加上初始的值，就可以算出操作后的值。

~~如果前面看不懂,可以看代码~~

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long maxn=100010;
long long n,m,k;
long long a[maxn];//初始值 
long long add[maxn];//每个数的增加量 
struct node{
	long long x,y,z;
};
node emm[maxn];  //操作 
long long num[maxn];//每个操作的调用数 
int main(){
	scanf("%lld %lld %lld",&n,&m,&k);
	for(long long i=1;i<=n;i++)
		scanf("%lld",&a[i]);  //读入初始值 
	for(long long i=1;i<=m;i++){
		scanf("%lld %lld %lld",&emm[i].x,&emm[i].y,&emm[i].z); //读入操作数 
	}
	for(long long i=1;i<=k;i++){
		long long b,c;
		scanf("%lld %lld",&b,&c);
		num[b]++;  //差分，为了求每个操作的次数 
		num[c+1]--;
	}
	for(long long i=1;i<=m;i++){
		num[i]+=num[i-1]; //前缀和，求出每个操作的次数 
		add[emm[i].x]+=emm[i].z*num[i];  //差分，为了求每个数的增加量 
		add[emm[i].y+1]-=emm[i].z*num[i];
	}
	for(long long i=1;i<=n;i++){
		add[i]+=add[i-1];  //前缀和，求出每个数的增加量 
		printf("%lld ",a[i]+add[i]);//增加量加上初始值，并输出 
	}
	printf("\n");
	return 0;
}
```

---

## 作者：Starmoon_dhw (赞：1)

(这是本篇题解第$n$次提交。。。)

刷老师给的线段树题单刷到的，~~个人感觉难度还好啦~~
## 题意简述
给定序列 $a$ 与 $m$ 个操作 $(l,r,d)$ 操作为给 $l-r$ 这段区间中的所有数加上 $d$ 然后有 $k$ 个操作 $(x,y)$ ,操作为执行第 $x$ 到 $y$ 这几个操作。求最终序列。
## 简要分析
题目中说，要给一个区间中的数加上同一个数，很明显，差分跑不了。如果不知道什么是差分请见:[差分及其用法](https://blog.csdn.net/m0_58667776/article/details/121208505?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522171481923516800182174410%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=171481923516800182174410&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-121208505-null-null.142^v100^pc_search_result_base4&utm_term=%E4%BB%80%E4%B9%88%E6%98%AF%E5%B7%AE%E5%88%86&spm=1018.2226.3001.4187)

假定需要操作的区间为  $ u-v $。
要给这其中的每个数加上 $ d $。
那么操作就显而易见了如下 
$$ 

 a _ {u} + d, a_ {v} - d$$
然后进行累加就会发现这个区间中的所有数都加了 $d$ ，并且区间外的数没有改变。
会了差分，那这道题该如何使用差分呢？
我们可以用差分来计算一个操作做了几次。
差分:
```c
	for(int i=1;i<=kk;i++)
	{
		cin>>ll>>rr;//ll,rr表示执行第ll到rr这些操作
		cl[ll]++,cl[rr+1]--;//记录操作次数
	}
```
接着就需要用到强大的线段树了！这题需要求和所以需要使用到延迟标记。

标记函数:（不知道延迟标记和线段树请看：[线段树&延迟标记介绍](https://blog.csdn.net/qq_31964727/article/details/80798109?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522171481982216800226545721%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=171481982216800226545721&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-80798109-null-null.142^v100^pc_search_result_base4&utm_term=%E7%BA%BF%E6%AE%B5%E6%A0%91%E5%BB%B6%E8%BF%9F%E6%A0%87%E8%AE%B0&spm=1018.2226.3001.4187)）
```c
void spread(int p)
{
	if(t[p].f)//判断节点p有没有标记
	{
		t[p*2].s+=t[p].f*(t[p*2].r-t[p*2].l+1);//更新左节点
		t[p*2+1].s+=t[p].f*(t[p*2+1].r-t[p*2+1].l+1);//更新右节点
		t[p*2].f+=t[p].f;//给左节点打上延迟标记
		t[p*2+1].f+=t[p].f;//给有节点打上延迟标记
		t[p].f=0;//去掉节点p的延迟标记
	}
}
```

操作函数(其实就是执行操作)
```c
void change(int p,/*当前节点*/int l,int r,int d)
{
	if(l<=t[p].l&&t[p].r<=r)//完全覆盖
	{
		t[p].s+=d*(t[p].r-t[p].l+1);//更新节点信息
		t[p].f+=d;//给节点打上延迟标记
		return;
	}
	spread(p);//下传延迟标记
	int mid=(t[p].l+t[p].r)>>1;
	if(l<=mid)
		change(p*2,l,r,d);
	if(r>mid)
		change(p*2+1,l,r,d);
	t[p].s=t[p*2].s+t[p*2+1].s;
}
```
 构造函数（构造线段树）
```c
void build(int p,int l,int r)
{
	t[p].l=l;
	t[p].r=r;
	if(l==r)
	{
		t[p].s=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);//l
	build(p*2+1,mid+1,r);//r
	t[p].s=t[p*2].s+t[p*2+1].s;//传递信息
}
```
询问函数（属于模板，便于大家理解，）
```c
int ask(int p,int l,int r)
{
	if(l<=t[p].l&&t[p].r<=r)
	{
		return t[p].s;
	}
	spread(p);//传递标记
	int mid=(t[p].l+t[p].r)>>1;
	int ans=0;
	if(l<=mid)
		ans+=ask(p*2,l,r);
	if(r>mid)
		ans+=ask(p*2+1,l,r);
	return ans;//(这个返回值是 l-r 这个区间的和)
}
```
以上便是线段树的函数，若大家仔细阅读，可以发现，我们的差分数组并未使用，接下来便是**核心**了
$ tt$  是记录操作次数的，
```c
	tt=0;
	for(int i=1;i<=m;i++)
	{
		tt+=cl[i];
		if(tt>0)
			change(1,x[i],y[i],k[i]*tt);//k[i]指第i个操作要加的数，如果要做n次操作，自然就等同于一次加上k[i]*n
	}
```

## 总结:
所有核心代码都已经给出了，剩下的大家应该可以搞定。
本题主要考察对线段树区间求和的运用，难度适中，希望本蒟蒻的首篇题解对大家有帮助。

---

## 作者：XiaoQuQu (赞：1)

刷线段树题单找到的，然后发现并没有用线段树。

首先就是发现这个东西只询问一次，于是考虑有什么离线的东西可以去做。发现，对于每个操作，我们可以用一个数组 $t$ 来记录它被执行了 $t_i$ 次，最后对原先的序列的贡献就是 $t_i\times d_i$。

然后你发现，这个题目就变成了只有区间修改 与 一次查询，可以差分解决，也就是对于原先的数组 $a$ 与这个操作次数数组 $t$ 都差分维护，最后复杂度是 $O(n)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid (l + r) >> 1
#define endl '\n'

const int MAXN = 1e5 + 5;
int a[MAXN], d[MAXN], t[MAXN], n, m, k, l[MAXN], r[MAXN], x[MAXN];

signed main(void) {
    ios::sync_with_stdio(false), cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
    	cin >> a[i];
    	d[i] = a[i] - a[i - 1];
    }
    for (int i = 1; i <= m; ++i) {
    	cin >> l[i] >> r[i] >> x[i];
    }
    for (int i = 1; i <= k; ++i) {
    	int u, v;
    	cin >> u >> v;
    	t[u]++; t[v + 1]--;
    }
    for (int i = 1; i <= m; ++i) {
    	t[i] += t[i - 1];
    	d[l[i]] += x[i] * t[i]; 
    	d[r[i] + 1] -= x[i] * t[i]; 
    }
    for (int i = 1; i <= n; ++i) {
    	d[i] += d[i - 1];
    	cout << d[i] << ' ';
    }
    return 0;
}



---

## 作者：OcTar (赞：0)

当时老师在讲权值线段树的时候把这道题当做例题（把执行一次改成了 $p$ 次），当我们都在埋头打线段树的时候，老师说这题直接用差分就行了啊。。。~~气死我了~~

## 题意简述

给定序列 $a$ 和 $m$ 种操作 $[l_i,r_i,d_i]$，表示 $[l_i,r_i]$ 区间内所有数加上 $d_i$。现在又有了 $k$ 个事件，每个事件要把 $[i,j]$ 范围内的**操作**执行一遍。求出最后的序列。

## 题目分析

~~一眼线段树~~。~~上面都这么说了那肯定用差分啊~~！首先是对于 $k$ 个事件的差分处理，非常简单，大家应该都会吧。我们维护一个差分数组 $d$，对于每个事件，按照正常差分处理即可。这部分的代码如下：

```cpp
for (int i = 1; i <= k; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    d[x]++;
    d[y + 1]--;
}
```


重点是这部分的处理，做完后再返回到操作中再做一遍差分。作者在这里直接用原数组当差分数组，不过要乘上操作次数，这部分的代码如下：

```cpp
struct node {
    ll l, r, d;//十年OI一场空，不开long long见祖宗
} op[maxn];
ll d[maxn];

......

for (int i = 1; i <= m; i++) {
    d[i] += d[i - 1];
    a[op[i].l] += op[i].d * d[i];
    a[op[i].r + 1] -= op[i].d * d[i];
}
```
两个核心部分代码已经给出了，完整代码请读者自行完成。

线段树解法已经有 dalao 发了，建议大家去学习一下。

**谢谢观看**

---

