# コアラ (Koala)

## 题目描述

有一条数轴，你需要从点 $K$ 走到点 $M$。数轴上有 $N$ 个关键点，第 $i$ 个关键点是 $T_i$，当你**首次**走到这个位置的时候，愉悦度会增加 $B_i$。若你在点 $x$，那么你可以消耗 $A$ 的愉悦度，走到任意距离点 $x$ 不超过 $D$ 的点。求最终走到 $M$ 后的愉悦度最大值。

## 说明/提示

- $1\leq N\leq 10^5$；

- $0\leq K<T_1<T_2<\dots<T_n<M\leq 10^9$；

- $1\leq D,A,B_i\leq 10^9$。

## 输入输出样例

### 输入 #1
```
0 10 4 10 2
3 10
8 5
```

### 输出 #1

```
-20
```

### 输入 #2
```
3 42 9 10 8
10 5
12 9
26 7
27 2
30 8
34 6
36 8
40 1
```

### 输出 #2

```
-25
```

# 题解

## 作者：是青白呀 (赞：0)

## Translation

有一条数轴，你需要从点 $K$ 走到点 $M$。数轴上有 $N$ 个关键点，第 $i$ 个关键点是 $T_i$，你走到这个位置的时候，愉悦度会增加 $B_i$。当你在点 $x$ 的时候，你可以消耗 $A$ 的愉悦度，走到任意距离 $x$ 不超过 $D$ 的点。求最终走到 $M$ 后的愉悦度最大值。$N\leq 10^5$，$0\leq K<T_1<T_2<\dots<T_n<M\leq 10^9$，$1\leq B_i\leq 10^9$。

## Solution

不难发现，全过程中只会向数轴的正方向跳。

首先有一个朴素的暴力 dp：将 $K$ 看作第 $0$ 个关键点，$M$ 看作第 $N+1$ 个关键点，设 $dp_i$ 表示走到第 $i$ 个关键点的最大愉悦度，转移时枚举上一个经过的点，然后计算中间的距离需要跳几次即可。由于 $B_i$ 为正，不合法一定不优，故不用考虑跳的途中踩到了其它关键点的情况。

不妨套路地考虑线段树维护转移点。当当前考虑的关键点从 $i$ 变为 $i+1$ 时，前面所有的转移点需要跳的距离都会增加 $\Delta d=T_{i+1}-T_i$，因此跳跃次数会整体增加 $\lfloor \frac{\Delta d}{D}\rfloor$。但对于剩下的残余距离 $l=\Delta d\bmod D$，有的转移点需要额外增加一次跳跃，有的可以和跳到 $i$ 处的残余距离拼合到一起，不用额外增加跳跃次数。这是不好处理的。

进一步观察可以发现，所有到 $T_i$ 距离模 $D$ 同余的转移点，是否增加那一次跳跃是一致的，且不增加那一次跳跃的转移点在余数上是一段连续的区间：$[0+[l\bmod D\neq 0],d-l\bmod D]$。因此，若设 $md_i=T_i\bmod D$，则不增加那一次跳跃的转移点在 $md$ 上是 $O(1)$ 段连续的区间。我们求出 $O(n)$ 个有效的 $md$ 值，将每个转移点挂在其对应的 $md$ 值处，用线段树维护每个 $md$ 值对应的实际转移点的最大 $dp$ 值即可。

线段树上需要支持区间加、单点取 $\max$、全局求最大值。这是朴素的。总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e5+10,M=6,S=(1<<15)+5,inf=(ll)4e18+7,mo=1e9+7;
const double eps=1e-8;
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
int k,m,d,del,n;
int pos[N],mod[N],val[N];
int dp[N];
struct seg{
    int t[4*N],tag[4*N];
    void pushup(int x){
        t[x]=max(t[ls(x)],t[rs(x)]);
    }
    void pushdown(int x){
        t[ls(x)]+=tag[x],t[rs(x)]+=tag[x],tag[ls(x)]+=tag[x],tag[rs(x)]+=tag[x],tag[x]=0;
    }
    void build(int x,int le,int ri){
        if(le==ri){
            t[x]=-inf;
            return ;
        }
        int mid=(le+ri)>>1;
        build(ls(x),le,mid),build(rs(x),mid+1,ri);
        pushup(x);
    }
    void add(int x,int le,int ri,int ql,int qr,int v){
        if(ql>qr)return;
        if(ql<=le&&qr>=ri){
            t[x]+=v;
            tag[x]+=v;
            return;
        }
        pushdown(x);
        int mid=(le+ri)>>1;
        if(ql<=mid)add(ls(x),le,mid,ql,qr,v);
        if(qr>mid)add(rs(x),mid+1,ri,ql,qr,v);
        pushup(x);
    }
    void modify(int x,int le,int ri,int p,int v){
        if(le==ri){
            t[x]=max(t[x],v);
            return;
        }
        pushdown(x);
        int mid=(le+ri)>>1;
        if(p<=mid)modify(ls(x),le,mid,p,v);
        else modify(rs(x),mid+1,ri,p,v);
        pushup(x);
    }
}T;
int lsh[N],cntl=0;
void addrg(int le,int ri,int v){
    if(le>ri)return;
    le=lower_bound(lsh+1,lsh+cntl+1,le)-lsh;
    ri=upper_bound(lsh+1,lsh+cntl+1,ri)-lsh-1;
    T.add(1,1,cntl,le,ri,v);
}
signed main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    read(k),read(m),read(d),read(del),read(n);
    int ans=0;
    rep(i,1,n)
        read(pos[i]),read(val[i]),ans+=val[i];
    pos[0]=k,pos[n+1]=m;
    rep(i,0,n+1)
        mod[i]=pos[i]%d,lsh[++cntl]=mod[i];
    sort(lsh+1,lsh+cntl+1),cntl=unique(lsh+1,lsh+cntl+1)-lsh-1;
    rep(i,0,n+1)
        mod[i]=lower_bound(lsh+1,lsh+cntl+1,mod[i])-lsh;
    T.build(1,1,cntl);
    rep(i,1,n+1)
        dp[i]=-inf;
    T.modify(1,1,cntl,mod[0],0);
    rep(i,1,n+1){
        //1.modify the value.
        int ddel=pos[i]-pos[i-1],num=ddel/d,lst=ddel%d;
        T.add(1,1,cntl,1,cntl,-(num+1)*del);
        int le=lst?1:0,ri=min(d-lst,d-1),nl,nr;
        nl=max(0ll,lsh[mod[i-1]]-ri),nr=lsh[mod[i-1]]-le;
        addrg(nl,nr,del);
        nl=max(lsh[mod[i-1]]+1,lsh[mod[i-1]]-ri+d),nr=min(d-1,lsh[mod[i-1]]-le+d);
        addrg(nl,nr,del);
        //2.get the answer
        dp[i]=max(dp[i],T.t[1]+val[i]);
        //3.update the value.
        T.modify(1,1,cntl,mod[i],dp[i]);
    }
    printf("%lld\n",dp[n+1]);
    return 0;
}
```

---

