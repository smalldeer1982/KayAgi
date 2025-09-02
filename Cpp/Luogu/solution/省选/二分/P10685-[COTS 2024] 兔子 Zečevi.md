# [COTS 2024] 兔子 Zečevi

## 题目背景

译自 [Izborne Pripreme 2024 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2024/) D2T3。$\texttt{8s,512M}$。

**请不要滥用本题评测。滥用本题评测将被封号。**

## 题目描述


数轴上有 $N$ 只兔子，第 $i$ 只兔子位于 $x_i$，起初，第 $i$ 只兔子的能量为 $p_i$。

每秒钟会发生如下的事件：

- 若存在至少一只兔子的能量为 $0$，则过程结束。
- 否则，每只兔子向右跳跃一个单位长度，同时能量减少 $1$。

数轴上分布着 $M$ 根胡萝卜，第 $i$ 根胡萝卜位于位置 $y_i$，质量为 $t_i$ 千克。当某只兔子的位置上有胡萝卜时，它可以选择吃 $a$ 千克的胡萝卜，其中 $a\in [0, y]$，其中 $y$ 为胡萝卜的质量。吃掉 $a$ 千克的胡萝卜后，兔子的能量增加 $a$，胡萝卜的质量减少 $a$。

显然兔子一旦停止跳跃，就再也不会跳跃了。在最优的情况下，兔子最多能跳跃多少秒？

## 说明/提示


#### 样例解释

样例 $1$ 解释：

我们用二元组 $(x_i,p_i)$ 表示兔子的位置和能量。

跳跃三次后，三只兔子的状态分别为 $(5,1),(10,0),(6,2)$。第二只兔子吃掉 $2$ 千克的胡萝卜，状态变为 $(5,1),(10,2),(6,2)$。

接下来一次跳跃之后，三只兔子的状态分别为 $(6,0),(11,1),(7,1)$。第一只兔子吃掉 $3$ 千克胡萝卜，状态变为 $(6,3),(11,1),(7,1)$。

接下来一次跳跃之后，三只兔子的状态分别为 $(7,2),(12,0),(8,0)$。由于第二只兔子吃不到胡萝卜，所以跳跃过程终止。

可以证明这是最优的答案。

#### 数据范围

对于 $100\%$ 的数据，保证： 

- $1\le N,M\le  10^5$；
- $0\le x_i,y_i\le 10^9$；
- $0\le p_i,t_i\le 10^9$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $9$  | $N=1$   |
| $2$  | $12$  | $M=1$  |
| $3$  | $26$  | $N,M\le 1\, 000$ |
| $4$  | $34$  | $N,Q\le 50\, 000$ |
| $5$  | $19$  | 无额外约束 |


## 样例 #1

### 输入

```
3 5
2 4
7 3
9 5
3 2
8 1
10 2
6 3
1 3```

### 输出

```
5```

## 样例 #2

### 输入

```
5 1
2 6
3 7
5 4
1 10
7 2
8 27```

### 输出

```
11```

# 题解

## 作者：oMin0 (赞：4)

## 分析

首先二分答案 $ans$，我们以下解决判定问题。

不妨假设兔子每次只能吃 $1$ 千克的胡萝卜，那么就要求第 $i$ 次兔子需要进食 $\max(0,ans-p_i)$ 次，且其第 $j$ 次进食时的位置必须在 $[x_i,x_i+p_i+j-1]$ 区间内。

这是左部点向右部点区间连边的二分图匹配问题，最近校内模拟赛里也出现过。记左部点的连边区间是 $[l_i,r_i]$，有一个正确性相当自然的贪心策略是“从小到大枚举右部点 $x$，将其与 $l_i\geq x$ 且 $r_i$ 最小的左部点匹配”，因为如果两右部点 $i<j$ 的匹配点 $x,y$ 满足 $l_{y}\leq i\leq r_{y}\leq r_{x}$ 的话可以交换它们。

那么对数轴从左到右扫描线，则以上策略的实现是：当扫到 $x_i$ 时加入右端点分别为 $x_i+p_i,x_i+p_i+1,\dots,x_i+ans-1$ 的若干个区间，当扫到 $y_i$ 时把右端点 $\geq y_i$ 的前 $t_i$ 小区间匹配掉，最终答案合法当且仅当所有的区间都被匹配。用线段树快速维护这几种操作即可（区间加，把区间置成 $0$，查区间和）。

时间复杂度 $O(n\log^2 V)$，可以通过本题。

## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <bitset>
#include <assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long

int n,m,flag,lim;
pair<int,int> x[100005],y[100005];

struct tree
{
	int ls,rs,tag,len,sum;
}tree[10000005];
int cntd,rt;

#define ls(x) tree[x].ls
#define rs(x) tree[x].rs
#define l(x) tree[x].len
#define n(x) tree[x].sum
#define tg(x) tree[x].tag
#define md(x,y) ((x+y)>>1)
#define push_up(x) n(x)=n(ls(x))+n(rs(x))
#define cz(k,p) tg(p)+=k,n(p)+=1ll*k*l(p)

void push_down(int p)
{
	if(tg(p))
	{
		if(!ls(p)) ls(p)=++cntd,l(ls(p))=(l(p)+1)/2; cz(tg(p),ls(p));
		if(!rs(p)) rs(p)=++cntd,l(rs(p))=l(p)/2; cz(tg(p),rs(p)); tg(p)=0;
	}
}
void cza(int l,int r,int x,int y,int k,int &p)
{
	if(!p) p=++cntd,l(p)=r-l+1; if(l>=x&&r<=y) return cz(k,p),void(); int mid=md(l,r); push_down(p);
	if(mid>=x) cza(l,mid,x,y,k,ls(p)); if(mid<y) cza(mid+1,r,x,y,k,rs(p)); push_up(p);
}
void czf(int l,int r,int k,int p)
{
	if(l==r) return n(p)-=k,void(); int mid=md(l,r); push_down(p);
	if(n(ls(p))<=k) czf(mid+1,r,k-n(ls(p)),rs(p)),ls(p)=0; else czf(l,mid,k,ls(p)); push_up(p);
}
int askm(int l,int r,int p)
{
	if(l==r) return l; int mid=md(l,r); push_down(p);
	if(n(ls(p))) return askm(l,mid,ls(p)); else return askm(mid+1,r,rs(p));
}

int sums=0;
void ins(pair<int,int> xx,int k)
{
	if(xx.se>=k) return;
	sums+=(k-1)-xx.se+1;
	cza(0,lim,xx.fi+xx.se,xx.fi+k-1,1,rt);
}
void del(pair<int,int> xx,int k)
{
	flag&=askm(0,lim,rt)>=xx.fi;
	if(n(rt)<=xx.se) rt=0; else czf(0,lim,xx.se,rt);
}

void clr()
{
	for(int i=1;i<=cntd;i++) ls(i)=rs(i)=n(i)=tg(i)=l(i)=0; cntd=rt=0;
}
int ck(int k)
{
	int nzl=1,nzr=1; flag=1;
	while(nzl<=n&&nzr<=m)
	{
		if(x[nzl].fi<=y[nzr].fi) ins(x[nzl++],k);
		else del(y[nzr++],k);
	}
	while(nzl<=n) ins(x[nzl++],k);
	while(nzr<=m) del(y[nzr++],k);
	flag&=askm(0,lim,rt)==lim; clr(); return flag;
}

signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>x[i].fi>>x[i].se;
	for(int i=1;i<=m;i++) cin>>y[i].fi>>y[i].se;
	sort(x+1,x+n+1); sort(y+1,y+m+1);
	int l=0,r=0;
	for(int i=1;i<=n;i++) r+=x[i].se;
	for(int i=1;i<=m;i++) r+=y[i].se; r/=n;
	lim=r+2000000000ll;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(ck(mid)) l=mid+1; else r=mid-1;
	}
	cout<<r<<endl;
}
```

---

## 作者：是青白呀 (赞：0)

首先可以二分答案，转为判断兔子是否能跳至少 $s$ 秒。

此时，对于兔子 $i$，它需要进食 $s-p_i$ 千克的胡萝卜。为了避免处理不同的胡萝卜重量，我们把所有进食需求和现有的胡萝卜都拆成 $1$ 千克每份。则对于兔子 $i$，它进食的第 $j$ 份胡萝卜，应当位于下标 $[x_i+p_i+j-1]$ 的位置。此时问题转变为一个二分图匹配问题：每一个限制都需要与区间内的某一份胡萝卜匹配。

这个东西显然可以贪心维护。不妨从小到大扫描每个位置，每一份胡萝卜都与当前合法的、右端点最靠前的限制匹配。

不妨用动态开点线段树配合扫描线解决，将每个扫到左端点的限制都挂在右端点上。每次遇到一个有胡萝卜的位置 $y_i$，就先考察 $y_i$ 之前是否有右端点未被匹配，有则无解；否则选择右端点最靠前的 $t_i$ 个右端点匹配掉即可。需要支持的操作是区间加、二分和为 $t_i$ 的前缀并作前缀推平、区间求和。

总时间复杂度 $O(n\log^2n)$，常数较大。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) lson[x]
#define rs(x) rson[x]
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=2e5+5,M=1e6+5,S=(1<<15)+5,inf=(ll)1e18+7,mo=998244353;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,m;
struct oper{
    int op,p,v;
    friend bool operator<(oper x,oper y){
        if(x.p!=y.p)return x.p<y.p;
        return x.op<y.op;
    }
}q[N];
int upp;
struct seg{
    int t[50*N],lson[50*N],rson[50*N],taga[50*N],cntp,rt;
    bool tagm[50*N];
    void pushup(int x){
        t[x]=0;
        if(ls(x))t[x]+=t[ls(x)];
        if(rs(x))t[x]+=t[rs(x)];
    }
    int addnode(){
        cntp++;
        t[cntp]=0,ls(cntp)=rs(cntp)=0,taga[cntp]=0,tagm[cntp]=0;
        return cntp;
    }
    void pushdown(int x,int le,int ri){
        if(!ls(x))ls(x)=addnode();
        if(!rs(x))rs(x)=addnode();
        if(tagm[x]){
            t[ls(x)]=t[rs(x)]=0,taga[ls(x)]=taga[rs(x)]=0,tagm[ls(x)]=tagm[rs(x)]=1;
            tagm[x]=0;
        }
        int mid=(le+ri)>>1;
        t[ls(x)]+=(mid-le+1)*taga[x],t[rs(x)]+=(ri-mid)*taga[x];
        taga[ls(x)]+=taga[x],taga[rs(x)]+=taga[x];
        taga[x]=0;
    }
    void add(int &x,int le,int ri,int ql,int qr,int v){
        if(ql>qr)return;
        if(!x)x=addnode();
        if(ql<=le&&qr>=ri){
            t[x]+=(ri-le+1)*v;
            taga[x]+=v;
            return;
        }
        pushdown(x,le,ri);
        int mid=(le+ri)>>1;
        if(ql<=mid)add(ls(x),le,mid,ql,qr,v);
        if(qr>mid)add(rs(x),mid+1,ri,ql,qr,v);
        pushup(x);
    }
    int querys(int x,int le,int ri,int ql,int qr){
        if(ql>qr)return 0;
        if(!x)return 0;
        if(ql<=le&&qr>=ri)return t[x];
        pushdown(x,le,ri);
        int mid=(le+ri)>>1,res=0;
        if(ql<=mid)res+=querys(ls(x),le,mid,ql,qr);
        if(qr>mid)res+=querys(rs(x),mid+1,ri,ql,qr);
        return res;
    }
    void modify(int x,int le,int ri,int v){
        if(!v)return;
        if(t[x]<=v){
            t[x]=0,taga[x]=0,tagm[x]=1;
            return;
        }
        if(le==ri){
            t[x]=max(0ll,t[x]-v);
            return;
        }
        pushdown(x,le,ri);
        int mid=(le+ri)>>1;
        if(t[ls(x)]<=v){
            modify(rs(x),mid+1,ri,v-t[ls(x)]);
            t[ls(x)]=0,tagm[ls(x)]=1,taga[ls(x)]=0;
        }
        else modify(ls(x),le,mid,v);
        pushup(x);
    }
}T;
bool check(int s){
    T.cntp=T.rt=0;
    rep(i,1,n+m){
        if(q[i].op==1)T.add(T.rt,0,upp,q[i].p+q[i].v,q[i].p+s-1,1);
        else{
            if(T.querys(T.rt,0,upp,0,q[i].p-1)>0)return 0;
            T.modify(T.rt,0,upp,q[i].v);
        }
    }
    if(T.t[T.rt])return 0;
    return 1;
}
int sump=0;
signed main(){
    read(n),read(m);
    rep(i,1,n){
        int x,y;
        read(x),read(y);
        q[i]=(oper){1,x,y},sump+=y;
    }
    rep(i,n+1,n+m){
        int x,y;
        read(x),read(y);
        q[i]=(oper){2,x,y},sump+=y;
    }
    sort(q+1,q+m+n+1);
    int le=0,ri=sump/n,ans=0;
    upp=q[n+m].p+ri;
    while(le<=ri){
        int mid=(le+ri)>>1;
        if(check(mid))ans=mid,le=mid+1;
        else ri=mid-1;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

