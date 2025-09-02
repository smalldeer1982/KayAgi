# [COTS 2017] 盗道 Krimošten

## 题目背景

译自 [Izborne Pripreme 2017 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2017/) D1T2。$\texttt{4s,0.5G}$。

库纳（Kuna）是克罗地亚的货币单位。

## 题目描述


海岸线上有一排房子，从西到东标号 $1\sim n$。第 $i$ 座房子内有 $a_i$ 库纳。

有 $m$ 个窃贼要行窃。第 $i$ 个窃贼初始囊中有 $c_i$ 库纳，他将依次对编号为 $l_i,l_i+1,\cdots, r_i$ 的房子行窃。

盗亦有道，窃贼们践行盗之道。当窃贼对编号为 $j$ 的房子行窃时，令他囊中有 $k$ 库纳：

- 若 $k\lt a_j$，则窃贼将 $1$ 库纳收入囊中，即 $k\gets k+1$；
- 若 $k=a_j$，无事发生；
- 若 $k\gt a_j$，则窃贼拿出 $1$ 库纳赠给房主，即 $k\gets k-1$。

对于每个窃贼，求出他最后囊中会有多少库纳。

需要注意的是，**每个窃贼的行窃是独立的，不互相影响**。换句话说，可以认为一个窃贼行窃结束后，（在下一个窃贼行窃前）房子会恢复到初始状态。

## 说明/提示



对于 $100\%$ 的数据，保证：

- $1\le n\le 5\times 10^5$；
- $0\le a_i,c_i\le 10^6$；
- $1\le l_i\le r_i\le n $。


| 子任务编号 | $n\le $ |  $m\le $ |得分 |  
| :--: | :--: | :--: | :--: |  
| $ 1 $    | $ 10^3 $    |  $10^3$ |  $ 7 $   |  
| $ 2 $    | $ 5\times 10^4 $   |  $10^5$ |  $ 48 $   |  
| $ 3 $    | $ 5\times 10^5 $ | $5\times 10^5$ | $ 45 $   |  

再次提醒，**每个窃贼的行窃是独立的，不互相影响**。

## 样例 #1

### 输入

```
10 3
3 5 5 4 3 6 10 0 4 7
2 10 9
6 6 2
2 8 4```

### 输出

```
6
3
4```

## 样例 #2

### 输入

```
8 5
2 3 0 9 2 6 0 6
5 6 8
3 4 7
3 8 8
8 8 7
6 7 9```

### 输出

```
6
7
6
6
7```

# 题解

## 作者：是青白呀 (赞：4)

提供一个比较直接，但是复杂度劣一点的在线做法：线段树维护分段函数。

一个比较显然的事情是：对于同一个区间 $[l,r]$，最终手上的钱数随着初始时的钱数的增加而单调不降。考虑设 $f_{l,r}(x)$ 表示初始以 $x$ 的钱数进行操作，最后钱数的变化量，不难发现这个函数形如若干段水平直线，整个函数是一个分段函数。

我们考虑暴力地在线段树上维护这些分段函数，合并两个函数时，由于上文中提到的单调性，左儿子的每一段在右儿子的对应段也是单调的。因此可以直接求出左儿子每一段对应的末状态钱数，双指针维护其对应的右儿子的段。对于一个长度为 $len$ 的区间，其段数为 $O(len)$ 的，合并时用双指针可以做到线性。因此 build 部分的复杂度是 $O(n\log n)$ 的。

接下来考虑区间查询。我们依次遍历每一个线段树上的区间，维护当前钱数 $v$，每次二分找到 $v$ 对应的那一段即可求出这个区间结束后的新的钱数，单次查询的复杂度是 $O(\log^2 n)$。

因此总复杂度是 $O(n\log^2 n)$，在 4s 的限制下不难通过。代码非常好写。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define lowbit(i) (i&-i)
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=5e5+5,M=32,inf=1e9+7,mo=1e9+7;
void read(int &p){
    int w=1,x=0;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    p=w*x;
}
int n,m,a[N];
struct seg{
    vector<pii>t[4*N];
    void pushup(int x){
        int targ=0;
        rep(i,0,(int)t[ls(x)].size()-1){
            int le=t[ls(x)][i].fir,ri=(i==(int)t[ls(x)].size()-1?inf:t[ls(x)][i+1].fir-1);
            int del=t[ls(x)][i].sec;
            int vl=le+del,vr=ri+del;
            while(targ<(int)t[rs(x)].size()-1&&t[rs(x)][targ+1].fir<=vr){
                t[x].push_back(mp(le,del+t[rs(x)][targ].sec)),le=t[rs(x)][targ+1].fir-del;
                targ++;
            }
            t[x].push_back(mp(le,del+t[rs(x)][targ].sec));
        }
    }
    void build(int x,int le,int ri){
        if(le==ri){
            if(a[le]>0)t[x].push_back(mp(0,1));
            t[x].push_back(mp(a[le],0));
            t[x].push_back(mp(a[le]+1,-1));
            return;
        }
        int mid=(le+ri)>>1;
        build(ls(x),le,mid),build(rs(x),mid+1,ri);
        pushup(x);
    }
    int query(int x,int le,int ri,int ql,int qr,int v){
        if(ql<=le&&qr>=ri){
            int targ=upper_bound(t[x].begin(),t[x].end(),mp(v,inf))-t[x].begin()-1;
            return v+t[x][targ].sec;
        }
        int mid=(le+ri)>>1,res=v;
        if(ql<=mid)res=query(ls(x),le,mid,ql,qr,v);
        if(qr>mid)res=query(rs(x),mid+1,ri,ql,qr,res);
        return res;
    }
}T;
signed main(){
    read(n),read(m);
    rep(i,1,n)
        read(a[i]);
    T.build(1,1,n);
    while(m--){
        int x,y,v;
        read(x),read(y),read(v);
        printf("%lld\n",T.query(1,1,n,x,y,v));
    }
    return 0;
}
```

---

## 作者：H3PO4 (赞：4)

首先我们考虑一个简化的问题：求出对于所有初始钱数，偷完**前 $x$ 座**房子后小偷会有多少钱。

从西到东扫描房子，扫描过程中维护一个序列，序列的第 $i$ 项表示若小偷初始有 $i$ 库纳，他现在会有多少钱。

例如，假设从西到东有三座房子，每座房子内部分别有 $5,2,8$ 库纳。
一开始，序列的值为：

$$1,2,3,4,5,6,7,8,9,10,\dots$$

偷完第一座房子（有 $5$ 库纳），序列变成：

$$2,3,4,5,5,5,6,7,8,9,\dots$$

偷完第二座房子（有 $2$ 库纳），序列变成：

$$2,2,3,4,4,4,5,6,7,8,\dots$$

偷完第三座房子（有 $8$ 库纳），序列变成

$$3,3,4,5,5,5,6,7,8,8,\dots$$

我们发现，这个序列一定是**单调不降**的。

为了维护这个序列，我们需要一个支持以下操作的数据结构：

1. 找到某个数在序列中第一次出现的位置；
2. 对序列上某个区间中的数全部 $+1/-1$。
3. 查询序列中某个位置上的数。

容易用树状数组实现。具体地，用树状数组维护序列的差分，那么操作 $2$ 转化为单点加，操作 $3$ 转化为查询前缀和。因为原序列单调不降，所以操作 $1$ 可以用树状数组上二分实现。

回到原问题。为了回答询问 $(l,r,c)$，在处理第 $l$ 座房子对答案的贡献之前，先找到序列中 $c$ 的位置 $p$。处理完第 $r$ 座房子之后，序列中位置 $p$ 上的数就是这个询问的答案。

最后，我们要保证每个询问的 $c$ 都能在序列中找到。显然，序列中每个数的变化量都不会超过 $n$，所以只需一开始往序列中填入 $-n$ 到 $V+n$ 之间的所有整数即可，其中 $V$ 是询问的 $c$ 的最大值。

时间复杂度 $O((n+m) \log(n+V))$。

```cpp
#include<bits/stdc++.h>
using I=int;
template<class T>using V=std::vector<T>;
template<class T,I N>using A=std::array<T,N>;
int main(){
  std::cin.tie(0)->sync_with_stdio(0);
  I n,m;std::cin>>n>>m;
  V<I>a(n);for(I&e:a)std::cin>>e;
  V<V<A<I,2>>>ql(n);V<V<I>>qr(n);I lim=0;
  for(I i=0;i<m;i++){
    I l,r,c;std::cin>>l>>r>>c;l--;r--;lim=std::max(lim,c);
    ql[l].push_back({i,c});qr[r].push_back(i);
  }
  V<I>fw(lim+2*n+2);
  auto add=[&](I p,I v){for(p++;p<fw.size();p+=p&-p)fw[p]+=v;};
  auto sum=[&](I p){I w=0;for(p++;p;p-=p&-p)w+=fw[p];return w;};
  auto lwb=[&](I v){
    I p=0,s=0;
    for(I i=31-__builtin_ctz(fw.size());i>=0;i--)
      if((p|1<<i)<fw.size()&&s+fw[p|1<<i]<v)s+=fw[p|=1<<i];
    return p;
  };
  add(0,-n);for(I i=1;i<=lim+2*n;i++)add(i,1);
  V<I>pos(m),ww(m);
  for(I i=0;i<n;i++){
    for(auto[i,c]:ql[i])pos[i]=lwb(c);
    I x=lwb(a[i]),y=lwb(a[i]+1);
    add(0,1);add(x,-1);add(y,-1);
    for(I x:qr[i])ww[x]=sum(pos[x]);
  }
  for(I e:ww)std::cout<<e<<'\n';
  return 0;
}
```

---

## 作者：EityDawn (赞：3)

# 思路

对于全局来讲，我们维护一个 $b_i$ 序列，其中初始时 $b_i=i$，表示盗贼初始有 $i$ 块钱经过操作后所拥有的钱数。

而每一个位置上的数 $a_i$，对应操作为将 $b$ 中 $b_j < a_i$ 的变成 $b_j+1$，$b_j>a_i$ 的变成 $b_j-1$，可以~~打表~~发现 $b_i$ 是单调不降的，这是一个很重要的性质。

再看区间怎么做。考虑扫描线，还是维护 $b_i$。

对于修改操作，$b_i$ 是单调不降的，可以拿线段树维护 $b_i$，转化为线段树上二分，区间加。

对于询问 $(l,r,k)$，现在假设我们已经扫完了 $[1,l-1]$ 的所有 $a_i$ 并进行了操作，那么在 $b$ 中找一个位置满足 $b_i=k$，可以线段树二分。这里可以看成是**找一个初始钱数为 $k$ 的位置**。再扫描到 $r$ 时，直接询问记录位置的值即可，等价于初始钱数为 $k$，操作完 $[l,r]$ 后的值。而为了让 $b_i$ 中 $[0,10^6]$ 的值都存在，可以让 $b_i=i,i\in[-10^6,2\times10^6]$。

时间复杂度是 $O(n\log V)$ 的。

## code

```cpp
#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define mset(x,y) memset((x),(y),sizeof((x)))
#define mcpy(x,y) memcpy((x),(y),sizeof((y)))
#define FileIn(x) freopen(""#x".in","r",stdin)
#define FileOut(x) freopen(""#x".out","w",stdout)
#define debug(x) cerr<<""#x" = "<<(x)<<'\n'
#define Assert(x) if(!(x)) cerr<<"Failed: "#x" at line "<<__LINE__,exit(1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 Int;
const int N=5e5+10;
const int V=1e6,M=3e6+10;
bool StM;
int n,m,c[N],pos[N];
vector<int>qr[N];
vector<pair<int,int>>ql[N];
int ma[M<<2],tag[M<<2],Ans[N];
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
void push_up(int x){ma[x]=max(ma[lc(x)],ma[rc(x)]);}
void addtag(int val,int x){ma[x]+=val,tag[x]+=val;}
void push_down(int x)
{
    if(!tag[x]) return;
    addtag(tag[x],lc(x)),addtag(tag[x],rc(x)),tag[x]=0;
}
void build(int l,int r,int x)
{
    if(l==r)
        return void(ma[x]=l);
    int mid=(l+r)>>1;
    build(l,mid,lc(x)),build(mid+1,r,rc(x));
    return push_up(x);
}
int query(int val,int l=-V,int r=2*V,int x=1)
{
    if(l==r) return l;
    push_down(x);
    int mid=(l+r)>>1;
    if(ma[lc(x)]>=val) return query(val,l,mid,lc(x));
    else return query(val,mid+1,r,rc(x));
}
int Query(int y,int l=-V,int r=2*V,int x=1)
{
    if(l==r)
        return ma[x];
    push_down(x);
    int mid=(l+r)>>1;
    if(y<=mid) return Query(y,l,mid,lc(x));
    else return Query(y,mid+1,r,rc(x));
}
void modify(int p,int q,int val,int l=-V,int r=2*V,int x=1)
{
    Assert(p<=q);
    if(p<=l&&q>=r)
        return addtag(val,x);
    push_down(x);
    int mid=(l+r)>>1;
    if(p<=mid) modify(p,q,val,l,mid,lc(x));
    if(q>mid) modify(p,q,val,mid+1,r,rc(x));
    return push_up(x);
}
void Main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>c[i];
    build(-V,2*V,1);
    for(int id=1,l,r,k;id<=m;id++)
    {
        cin>>l>>r>>k;
        ql[l].push_back({k,id});
        qr[r].push_back(id);
    }
    for(int i=1,x,y;i<=n;i++)
    {
        for(auto [val,id]:ql[i]) pos[id]=query(val);
        x=query(c[i]),y=query(c[i]+1);modify(-V,x-1,1),modify(y,2*V,-1);
        for(auto id:qr[i]) Ans[id]=Query(pos[id]);
    }
    for(int i=1;i<=m;i++) cout<<Ans[i]<<'\n';
}
bool EdM;
int main()
{
    cerr<<fabs(&StM-&EdM)/1024.0/1024.0<<" MB\n";
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int StT=clock();
    int T=1;
    while(T--) Main();
    int EdT=clock();
    cerr<<1e3*(EdT-StT)/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

## 作者：xixisuper (赞：3)

# P11286 [COTS 2017] 盗道 Krimošten 题解

小清新数据结构题，感觉没有紫。

## 思路

$O(nm)$ 的暴力很显然，按题意模拟即可，考虑正解。

先来想弱化版的情况：假设我每次询问的 $[l,r]$ 都是 $[1,n]$，但是 $c$ 不一样，怎么做？

一个比较显然的思路是我直接维护一个值域，位置 $j$ 上的数表示初始时盗贼有 $j$ 库纳，在当前情况下有多少库纳，初始化的时候位置 $j$ 上的数就等于 $j$。对于每一户人家 $i$，**找到当前情况下值小于 $a_i$ 的那些盗贼，给他们全部加 $1$**；**找到当前情况下值大于 $a_i$ 的那些盗贼，给他们全部减 $1$**。最后，第 $j$ 个位置上的数就是对应的解。

不难发现上述算法的时间复杂度瓶颈在于如何进行快速的加减 $1$ 操作。我们能够发现，**盗贼当前的库那个数随初始库那个数单调不降**。证明这个也很简单，你会发现对于 $x<y$ 来说，在经过若干次操作后只可能会达到 $x=y$ 的一个状态，往后的所有人家都会使 $x,y$ 同加同减，所以 $x$ 永远小于等于 $y$，单调性得证。

所以我们**在值域上加的盗贼一定是一段前缀，减的盗贼一定是一段后缀**，找 $a_i$ 的位置可以用线段树上二分解决，而加减 $1$ 的操作线段树也支持，所以能够做到 $O(n\log V)$ 解决该问题。

现在来想一般情况，不难发现我们只需要把上述问题进行一个拓展就行。我们考虑**把所有询问离线，套用扫描线的思路，在遍历到第 $i$ 户人家前，把所有左端点 $L=i$ 的那些询问记录下 $c$ 在值域中出现的位置；在计算完第 $i$ 户人家的贡献后，把所有 $R=i$ 的询问的答案记录下来，最后输出即可。**

注意在这种实现下，最开始时值域的范围是 $[-n,V+n]$，因为我们要保证在扫描线时，$[0,V]$ 以内的所有数都出现在值域里，而操作 $n$ 户人家至多使最小值增加 $n$，使最大值减小 $n$。

归到时间复杂度分析，瓶颈在于线段树扫描线，时间复杂度为 $O((n+m)\log (n+V))$。

## 代码

毫无聪明的实现，看看就好。

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define ll int
#define lc (x<<1)
#define rc ((x<<1)|1)
#define mid ((l+r)>>1)
using namespace std;
const ll V=1e6+10;
const ll N=5e5+10;
const ll MX=2*V-5;
ll tag[MX<<3],mx[MX<<3],a[N],chk[MX],n,m;
struct node{
	ll L,R,c,ans,id,pos;
	friend bool operator >(const node x,const node y){
		return x.R>y.R;
	}
}ask[N],ot[N];
priority_queue<node,vector<node>,greater<node> > qu;
bool cmp1(node x,node y){return x.L<y.L;}
bool cmp2(node x,node y){return x.id<y.id;}
void push_up(ll x){mx[x]=max(mx[lc],mx[rc]);}
void build(ll x,ll l,ll r){
	if(l==r){
		mx[x]=chk[l];
		return;
	}
	build(lc,l,mid);
	build(rc,mid+1,r);
	push_up(x);
}
void push_down(ll x){
	if(!tag[x]) return;
	tag[lc]+=tag[x],tag[rc]+=tag[x];
	mx[lc]+=tag[x],mx[rc]+=tag[x];
	tag[x]=0;
}
void add(ll x,ll l,ll r,ll L,ll R,ll p){
	if(L<=l&&r<=R){
		tag[x]+=p;
		mx[x]+=p;
		return;
	}
	push_down(x);
	if(L<=mid) add(lc,l,mid,L,R,p);
	if(R>mid) add(rc,mid+1,r,L,R,p);
	push_up(x);
}
ll gtpos(ll x,ll l,ll r,ll k){
	if(l==r) return l;
	push_down(x);
	if(mx[lc]>=k) return gtpos(lc,l,mid,k);
	return gtpos(rc,mid+1,r,k);
}
ll gtval(ll x,ll l,ll r,ll pos){
	if(l==r) return mx[x];
	push_down(x);
	if(pos<=mid) return gtval(lc,l,mid,pos);
	return gtval(rc,mid+1,r,pos);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll i=1;i<=m;i++){
		cin>>ask[i].L>>ask[i].R>>ask[i].c;
		ask[i].id=i;
	}
	sort(ask+1,ask+1+m,cmp1);
	for(ll i=1;i<=MX;i++) chk[i]=i-N;
	build(1,1,MX);
	ll top=1,as=1;
	for(ll i=1;i<=n;i++){
		while(top<=m&&ask[top].L==i){
			ask[top].pos=gtpos(1,1,MX,ask[top].c);
			qu.push(ask[top]);
			top++;
		}
		ll pls=gtpos(1,1,MX,a[i])-1,minu=gtpos(1,1,MX,a[i]+1);
		add(1,1,MX,1,pls,1),add(1,1,MX,minu,MX,-1);
		while(!qu.empty()&&qu.top().R==i){
			ot[as]=qu.top();
			qu.pop();
			ot[as].ans=gtval(1,1,MX,ot[as].pos);
			as++;
		}
	}
	sort(ot+1,ot+1+m,cmp2);
	for(ll i=1;i<=m;i++) cout<<ot[i].ans<<"\n";
	return 0;
}
```

---

## 作者：CQ_Bab (赞：2)

# 思路
感觉还是比较好想。

首先我们先考虑证明一个结论，如果初始的时候有 $x,y$ 满足 $x<y$ 那么无论 $a$ 数组长什么样子进行完所有操作之后的 $x,y$ 依旧满足 $x\leq y$ 及相对大小不改变，这个东西也很好证明，可以感性理解一下。

那么有了这个就很好做了，考虑离线，我们首先维护一棵线段树代表初始值为 $i$ 走到了 $x$ 这个点的值变成多少了，因为有单调性所以我们可以对于一个点的修改变为前缀和后缀加或减 $1$ 那么由于这题是走的区间 $l,r$ 我们该怎么搞呢，考虑在 $l$ 的时候找到一个值为 $c$ 的位置并记录下来那么我们在 $r$ 的时候只需要查询这个位置的值即可，由于这道题涉及到 $l,r$ 所以我们线段树的大小需要开到 $-10^6\sim 2\times 10^6$，但是我们还需要证明一个东西就是对于进行到每一个位置，我们都能在线段树上找到值等于 $0\sim 10^6$ 的位置，考虑递推，对于一个序列 $a$ 若满足条件那么我们在 $x$ 处进行修改，那么等于 $x$ 的一定不会变，大于 $x$ 的都减一，因为值域上限为两倍所以还是能覆盖 $x\sim 10^6$ 考虑比 $x$ 小的，因为都加一了，那么也一定能覆盖 $0\sim x-1$ 的所有值，所以证毕。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T;
const int N=5e5+10,M=2e6+10;
struct node{
	int l,r;
	int val,tag;
}tr[N<<4];
vector<pair<int,int>>qr[N];
vector<int>ql[N];
int ans[N];
int n,m,a[N],l[N],r[N],c[N];
int idx;
void modify(int &u,int ll,int rr,int l,int r,int k) {
	if(!u) {
		u=++idx;
	}
	if(ll>=l&&rr<=r) {
		tr[u].tag+=k;
		return;
	}
	int mid=ll+rr>>1;
	if(mid>=l) modify(tr[u].l,ll,mid,l,r,k);
	if(mid<r) modify(tr[u].r,mid+1,rr,l,r,k);
} 
int Ans(int &u,int l,int r,int k) {
	if(!u) return k;
	if(l==r) {
		return k+tr[u].tag;
	}
	int res=tr[u].tag;
	int mid=l+r>>1;
	if(mid>=k) res+=Ans(tr[u].l,l,mid,k);
	else res+=Ans(tr[u].r,mid+1,r,k);
	return res;
}
int rt;
void solve() {
	in(n),in(m);
	rep(i,1,n) in(a[i]);
	rep(i,1,m) {
		in(l[i]),in(r[i]),in(c[i]);
		ql[l[i]].pb(i);
	}
	rep(i,1,n) {
		for(auto to:ql[i]) {
			int rr=r[to];
			int l=-M,r=M,res=0;
			while(l<=r) {
				int mid=l+r>>1;
				if(Ans(rt,-M,M,mid)<=c[to]) l=mid+1,res=mid;
				else r=mid-1;
			}
			qr[rr].pb({to,res});
		}
		int l=-M,r=M,res1=0;
		while(l<=r) {
			int mid=l+r>>1;
			if(Ans(rt,-M,M,mid)<a[i]) l=mid+1,res1=mid;
			else r=mid-1;
		}
		l=-M,r=M;
		int res=0;
		while(l<=r) {
			int mid=l+r>>1;
			if(Ans(rt,-M,M,mid)>a[i]) r=mid-1,res=mid;
			else l=mid+1;
		}
		modify(rt,-M,M,-M,res1,1);
		modify(rt,-M,M,res,M,-1);
		for(auto to:qr[i]) {
			ans[to.first]=Ans(rt,-M,M,to.second); 
		}
	}
	rep(i,1,m) cout<<ans[i]<<endl;
}
fire main() {
	T=1;
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：Remarks (赞：1)

本题解（基本）思路来自于 https://www.luogu.com.cn/article/6kmsqopa ，但维护方法略有不同。

### part 1 本题思路

为了方便表述，我们认为所有盗贼同时进行盗窃（且房子的 $a_i$ 始终不变），时刻 $i$ 盗窃第 $i$ 个房子。

考虑对所有询问离线，那么本题等价 ：对于每个时刻，将所有小于 $a_i$ 的点加一，将所有大于 $a_i$ 的点减一，查询在 $l_i$ 时刻等于 $x_i$ 的点在 $r_i$ 时刻的值。

容易想到用平衡树维护。在时刻 $i$ 对于所有 $l_j = i$ 的询问 $j$ ，将 $x_j$ 加入平衡树，记录加入平衡树的节点编号 $p_j$。每次盗窃的时候将严格小于 $a_i$ 的部分全部减一，严格大于 $a_i$ 的部分全部加一。一个询问的答案即为其对应节点 $p_j$ 在 $r_j$ 时刻的值。

具体维护上需要注意：

如果平衡树写相同权值节点合并的话，可以使用并查集等数据结构维护一个节点最终指向的节点（即为，当在平衡树上合并两个节点 $x,y \rightarrow x$ 的时候，将 $y$ 向 $x$ 节点合并。

亦可以在打 tag 的时候只对严格小于和严格大于 $a_i$ 的部分打tag，实现也很方便。

复杂度 $O(m \log m+n\log m)$ ，可以通过此题。

本人平衡树代码过于丑陋，不予展示。

--------------------

updata on 2024/11/21 更新了一些实现上的细节。

---

## 作者：_AyachiNene (赞：1)

插入-标记-删除做法。
# 思路：
这个做法是之前听 lxl 讲的，做这种题直接秒杀。算法流程很简单，类似扫描线，先离线，在每个询问的端点打上标记，扫到左端点时把这个询问插进数据结构，在右端点查询答案并删掉。在往后扫时对数据结构中的询问进行修改。在这道题中直接套就行了。其他部分很简单，直接讲下数据结构的维护。题目的要求就是把人的钱按值域分成三段，对前缀加 $1$，后缀减 $1$。容易想到用平衡树，直接按 $a_i$ 分裂出来打标记就行了。注意到有交集的值域只有 $1$，不用写平衡树合并。时间复杂度 $O(n\log n)$。
# Code：
从另一道题搞的代码，写了平衡树合并，实际上并不需要。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,m;
int w[500005];
#define fi first
#define sc second
vector<pair<int,int> >q[500005];
namespace Nene
{
	struct fhqt
	{
		int l,r,f,rnd;
		pair<int,int> key;
		int tag;
	}t[500005];
	int rt,cnt;
	int pos[500005];
	inline int New(int v){++cnt;t[cnt]=(fhqt){0,0,0,rand(),{v,cnt},0};return cnt;}
	inline void update(int p)
	{
		if(t[p].l) t[t[p].l].f=p;
		if(t[p].r) t[t[p].r].f=p;
	}
	inline void pushr(int p,int v){if(!p)return;t[p].key.fi+=v;t[p].tag+=v;}
	inline void down(int p)
	{
		if(!t[p].tag) return;
		if(t[p].l) pushr(t[p].l,t[p].tag);
		if(t[p].r) pushr(t[p].r,t[p].tag);
		t[p].tag=0;
	}
	void split(int p,pair<int,int>k,int &x,int &y)
	{
		if(!p) return x=y=0,void();
		down(p);
		if(t[p].key<=k) x=p,split(t[p].r,k,t[p].r,y);
		else y=p,split(t[p].l,k,x,t[p].l);
		update(p);
	}
	int merget(int x,int y)
	{
		if(!x||!y) return x|y;
		down(x),down(y);
		if(t[x].rnd>t[y].rnd) swap(x,y);
		int a,b;
		split(y,t[x].key,a,b);
		t[x].l=merget(t[x].l,a);t[x].r=merget(t[x].r,b);
		update(x);return x;
	}
	int stk[500005],top;
	inline int query(int p)
	{
		top=0;
		stk[++top]=p;
		for(int i=p;t[i].f;i=t[i].f) stk[++top]=t[i].f;
		while(top) down(stk[top--]);
		return t[p].key.fi;
	}
}using namespace Nene;
int ans[500005];
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++) read(w[i]);
	for(int i=1;i<=m;i++)
	{
		int ql,qr,x;read(ql,qr,x);
		q[ql].push_back({i,x});q[qr].push_back({-i,x});
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<q[i].size();j++)
		{
			if(q[i][j].fi<0) continue;
			pos[q[i][j].fi]=New(q[i][j].sc);
			int a,b;split(rt,{q[i][j].sc,q[i][j].fi},a,b);
			rt=merget(a,merget(cnt,b));
			t[rt].f=0;
		}
		int a,b,c;split(rt,{w[i],1e9},b,c);
		split(b,{w[i]-1,1e9},a,b);
		pushr(a,1);pushr(c,-1);
		rt=merget(a,merget(b,c));
		t[rt].f=0;
		for(int j=0;j<q[i].size();j++)
		{
			if(q[i][j].fi>0) continue;
			ans[-q[i][j].fi]=query(pos[-q[i][j].fi]);
		}
	}
	for(int i=1;i<=m;i++) write(ans[i]),putch('\n');
	flush();
	return 0;
}
```

---

## 作者：CuFeO4 (赞：0)

听 lxl 在多校讲完函数复合这个科技，便想到这个题。

### 序列型函数复合

- 给定一个序列，第 $i$ 个位置是一个函数 $F_i(x)$。
- 对于每次询问，给定 $l,r,x$，求出 $F_r(\cdots F_{l+1}(F_{l}(x))\cdots)$。
- 允许离线。

这类题一般用如下套路解决。

- 将所有询问离线。
- 对序列进行扫描线，当扫到第 $i$ 个位置时，进行如下操作。
   1. 将所有询问中 $l=i$ 的 $x$ 插入平衡树中。
   2. 将所有符合函数条件的 $x$ 打上标记。
   3. 将所有询问中 $r=i$ 的 $x$ 取出来。

对于第三种操作，为了方便定位询问，可以在插入时记录询问被插入到的位置。

### 对于本题

显然每个位置是一个分段函数，然后套用上面的操作即可。注意这里的平衡树还需要维护一个 fa 来记录平衡树节点的父亲，以便查询时将节点祖先的标记 pushdown 下来。

时间复杂度 $O(n\log m)$，空间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t,p) for(int i = s;i <= t;i += p)
#define drep(i,s,t,p) for(int i = s;i >= t;i -= p)
#ifdef LOCAL
    auto I = freopen("in.in","r",stdin),O = freopen("out.out","w",stdout);
#else
    auto I = stdin,O = stdout;
#endif
using ll = long long;using ull = unsigned long long;
using db = long double;using ldb = long double;
const int N = 5e5 + 10;
int st[N],n,m,a[N];
int ans[N],tid[N];
vector<pair<int,int> > Ad[N],De[N];
struct FHQ_Treap{
    struct node{
        int ls,rs,siz,val,pri,lz,fa;
        node(int L,int R,int S,int V,int P,int Z,int F = 0)
            :ls(L),rs(R),siz(S),val(V),pri(P),lz(Z),fa(F){}
        #define ls(x) tree[x].ls
        #define rs(x) tree[x].rs
        #define siz(x) tree[x].siz
        #define val(x) tree[x].val
        #define pri(x) tree[x].pri
        #define lz(x) tree[x].lz
        #define fa(x) tree[x].fa
    };vector<node> tree;
    #define eb emplace_back
    int tot,rt;
    FHQ_Treap(){tree.eb(0,0,0,0,0,0);rt = 0;}
    int New(int val){tot++;tree.eb(0,0,1,val,rand(),0);return tot;}
    void P(int p){siz(p) = siz(ls(p)) + siz(rs(p)) + 1;fa(ls(p)) = fa(rs(p)) = p;}
    void mk(int p,int val){if(!p) return;lz(p) += val,val(p) += val;}
    void D(int p){if(lz(p)) mk(ls(p),lz(p)),mk(rs(p),lz(p)),lz(p) = 0;}
    void split(int p,int val,int &x,int &y){
        if(!p) return x = y = 0,void();
        D(p);
        if(val(p) <= val) x = p,split(rs(p),val,rs(x),y);
        else y = p,split(ls(p),val,x,ls(y));
        P(p);
    }
    int Merge(int x,int y){
        if(!x || !y) return x|y;
        if(pri(x) < pri(y)) return D(x),rs(x) = Merge(rs(x),y),P(x),x;
        else return D(y),ls(y) = Merge(x,ls(y)),P(y),y;
    }
    int insert(int val){
        int x,y;split(rt,val,x,y);
        int res = New(val);
        rt = Merge(Merge(x,res),y);
        return res;
    }
    void upd(int val){
        int x,y,z;
        split(rt,val,x,y);split(x,val-1,x,z);
        mk(x,1);mk(y,-1);rt = Merge(Merge(x,z),y);
    }
    int qry(int x){
        int k = 0;
        for(;st[++k] = x;x = fa(x));
        for(;k;D(st[k--]));return val(st[1]);
    }
}fhq;
signed main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    srand(24320);
    cin>>n>>m;
    rep(i,1,n,1) cin>>a[i];
    rep(i,1,m,1){
        int l,r,c;cin>>l>>r>>c;
        Ad[l].eb(c,i);De[r].eb(c,i);
    }
    rep(i,1,n,1){
        for(auto [val,id]:Ad[i]) tid[id] = fhq.insert(val);
        fhq.upd(a[i]);
        for(auto [val,id]:De[i]) ans[id] = fhq.qry(tid[id]);
    }
    rep(i,1,m,1) cout<<ans[i]<<'\n';
}
```

---

## 作者：末然Ender (赞：0)

~~我什么时候能口紫题了？~~

思路想出来的时候提交通过 $5:1$，写完代码两天后了 $47:20$，我真是太摆了。

## 题意

给定 $n$ 个数 $a_i$，$m$ 次询问，每次给定 $l,r,c$，令 $c$ 从 $a_l$ 操作到 $a_r$，对于每次操作，若 $c$ 大于 $a_i$，令 $c=c+1$；若 $c$ 小于 $a_i$，令 $c=c-1$ ，求 $c$ 的终值。

## 思路

观察到值域不大，我们考虑对于每次存下遍历到 $a_i$ 时每一个可能的初值会变成的值 $chg_i$ ，每一次操作我们**令所有小于 $a_i$ 的 $chg$ 的值加 $1$ ，所有大于 $a_i$ 的 $chg$ 值减 $1$**，每次对于询问，我们将其离线，然后从 $1$ 到 $n$ 遍历 $a_i$，遍历到询问的 $l$ 的时候找到 $l$ 对应 $chg$ 中的位置，当跑到 $r$ 的时候将对应位置的 $chg_i$ 作为答案取出，取出这一部分可以用优先队列来完成。

那我们现在需要满足快速地完成：

- 区间加/减 $1$；
- 查找某一个值在数组中的位置。

第一条不难想到用数据结构，线段树或者树状数组皆可；至于第二条，我们不难发现序列 $chg$ 无论如何操作，永远**单调不降**，所以考虑线段树或树状数组上二分，这里我采用的线段树上二分的操作。

然后这个题就做出来了。

~~要注意不要出现 UB，我因为某一行 UB 了调了好久。~~

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define hc putchar('\n')
#define kg putchar(' ')
template<typename T>
void read(T& x){x=0;char ch=getchar();long long f=1;while(!isdigit(ch)){if(ch=='-')f*=-1;ch=getchar();}while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}x*=f;}
template<typename T,typename... Args>
void read(T& first,Args&... args){read(first);read(args...);}
template<typename T>
void write(T arg){T x=arg;if (x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
template<typename T,typename... Args>
void write(T arg,Args... args){write(arg);if(sizeof...(args) !=0){putchar(' ');write(args...);}}
const int N=5e5+10,M=2e6+5;
struct segmentree{
	int l,r;
	ll val,lazy;
}tr[M<<2];
#define lc root<<1
#define rc (root<<1)|1
ll a[N],n,m;
void pushup(int root){
	tr[root].val=max(tr[lc].val,tr[rc].val);
}
void build(int root,int l,int r){
	tr[root].l=l,tr[root].r=r;
	if(l==r){
		tr[root].val=l-N;
		return;
	}
	int mid=l+(r-l>>1);
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(root);
}
void pushdown(int root){
	if(tr[root].lazy){
		tr[lc].val+=tr[root].lazy,tr[rc].val+=tr[root].lazy;
		tr[lc].lazy+=tr[root].lazy,tr[rc].lazy+=tr[root].lazy;
		tr[root].lazy=0;
	}
}
void update(int root,int l,int r,int val){
	if(l<=tr[root].l&&r>=tr[root].r){
		tr[root].lazy+=val;
		tr[root].val+=val;
		return;
	}
	pushdown(root);
	int mid=tr[root].l+(tr[root].r-tr[root].l>>1);
	if(l<=mid)update(lc,l,r,val);
	if(r>mid)update(rc,l,r,val);
	pushup(root);
}
ll findval(int root,ll pos){
	if(tr[root].l==tr[root].r)return tr[root].val;
	pushdown(root);
	ll mid=tr[root].l+tr[root].r>>1;
	if(pos<=mid)return findval(lc,pos);
	return findval(rc,pos);
}
ll findpos(int root,ll val){
	if(tr[root].l==tr[root].r)return tr[root].l;
	pushdown(root);
	if(val<=tr[lc].val)return findpos(lc,val);
	return findpos(rc,val);
}
struct asks{
	ll l,r,c,id;
	ll pos;
	friend bool operator >(asks a,asks b){
		return a.r>b.r;
	}
}ask[N];
ll ans[N];
priority_queue<asks,vector<asks>,greater<asks> > q;
bool cmp(asks a,asks b){
	return a.l<b.l;
}
int main(){
	read(n,m);
	for(int i=1;i<=n;i++){
		read(a[i]);
	}
	for(int i=1;i<=m;i++){
		read(ask[i].l,ask[i].r,ask[i].c);
		ask[i].id=i;
	}
	sort(ask+1,ask+1+m,cmp);
	build(1,1,M);
	ll idx=0;
	for(int i=1;i<=n;i++){
		while(idx<m&&ask[idx+1].l==i){
			++idx;
			ask[idx].pos=findpos(1,ask[idx].c);
			q.push(ask[idx]);
		}
		ll beg=findpos(1,a[i]),fin=findpos(1,a[i]+1)-1;
		update(1,1,beg-1,1),update(1,fin+1,M,-1);
		while(!q.empty()&&q.top().r==i){
			ans[q.top().id]=findval(1,q.top().pos);
			q.pop();
		}
	}
	for(int i=1;i<=m;i++)write(ans[i]),putchar('\n');
	return 0;
}
```
管理员大大如果再有问题能帮忙改一下吗我是真找不到格式哪有问题了。

---

## 作者：Luciylove (赞：0)

这不是我们的 PKUSC2024 D2T2 吗？

对右端点扫描线，考虑维护经过从开头扫到现在，开始是 $x$ 变成了 $f(x) = v$，感知可知，这个函数是单调不降且会形成若干**连续**的同色段的。

考虑使用线段树维护，对于 $a_i$ 的修改，每次只需要二分出区间加的断点即可。每次插入一个数，需要定位到那个 $f(x') = c_i$ 的 $x'$，将这个记下来，扫到 $r_i$ 再查询。

但是你会发现扫了一段前缀后，$[0, 10^6]$ 可能无法完整表示所有的数，因为颜色段可能会被合并。所以你考虑将边界开大一点到 $[-10^6, 2 \times 10^6]$ 即可。

复杂度 $O(n \log V)$，可以通过。


```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)
#define lc x << 1
#define rc x << 1 | 1
/*
使い切って声に出そう
*/
using namespace std;

typedef long long ll;
const int _ = 1e6 + 5, mod = 998244353, Vmax = 2e6;
int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}

int power (int x, int y) {
	int r = 1;
	for ( ; y; y >>= 1, x = 1ll * x * x % mod)
		if (y & 1) r = 1ll * r * x % mod;
	return r;
}
void add_mod (int &x, int y) { x += y; if (x >= mod) x -= mod; }
void del_mod (int &x, int y) { x -= y; if (x < 0) x += mod; }
void tim_mod (int &x, int y) { x = 1ll * x * y % mod; }
int n, q, pos[_], a[_], ans[_];
int t[Vmax << 4], add[Vmax << 4];
vector <array<int, 3> > cv[_], qv[_];

void apply(int x, int k) { t[x] += k, add[x] += k; }
void pushdown (int x) { if (add[x]) apply(lc, add[x]), apply(rc, add[x]), add[x] = 0; }
void build (int x, int l, int r) {
	t[x] = l;
	if (l == r) return ;
	int mid = (l + r) >> 1;
	build(lc, l, mid), build(rc, mid + 1, r);
}
void modify (int x, int l, int r, int ql, int qr, int k) {
	if (ql > qr) return ;
	if (ql <= l && r <= qr) return apply(x, k);
	int mid = (l + r) >> 1; pushdown(x);
	if (ql <= mid) modify(lc, l, mid, ql, qr, k);
	if (qr > mid) modify(rc, mid +1 , r, ql, qr, k);
	return t[x] = min(t[lc], t[rc]), void();
}
int find_pos (int x, int l, int r, int k) {
	if (t[x] > k) return mod;
	if (l == r) return l;
	int mid = (l + r) >> 1, re; pushdown(x);
	if ((re = find_pos(rc, mid + 1, r, k)) != mod) return re;
	return find_pos(lc, l, mid, k);
}
int qry_pos (int x, int l, int r, int v) {
	if (l == r) return t[x];
	int mid = (l + r) >> 1; pushdown(x);
	return v <= mid ? qry_pos(lc, l, mid, v) : qry_pos(rc, mid + 1, r, v);
}
int main () {
	n = read(), q = read();
	rep(i, 1, n) a[i] = read();
	rep(i, 1, q) {
		int l = read(), r = read(), c = read();
		cv[l].push_back({l, c, i});
		qv[r].push_back({l, c, i});
	}
	build(1, -Vmax, Vmax);
	rep(i, 1, n) {
		for (auto [l, c, id] : cv[i]) pos[id] = find_pos(1, -Vmax, Vmax, c);
		int vl = find_pos(1, -Vmax, Vmax, a[i] - 1),
			vr = find_pos(1, -Vmax, Vmax, a[i]);
		modify(1, -Vmax, Vmax, -Vmax, vl, 1);
		modify(1, -Vmax, Vmax, vr + 1, Vmax, -1);
		for (auto [l, c, id] : qv[i]) ans[id] = qry_pos(1, -Vmax, Vmax, pos[id]);
	}
	rep(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
```

---

