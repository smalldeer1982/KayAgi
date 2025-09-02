# Performance Review

## 题目描述

### 题意
一个公司有 n 个员工，每个员工有一个能力值 $a_i$， 每个 $a_i$ 都不一样。公司采取末位淘汰制，我们考虑 m 年，每年年底都会补充 $r_i$ 个新员工，每个新员工的能力值被表示为 $b_{i_j}$, 即第 $i$ 年新加入的第 $j$ 个员工的能力值。每年，能力值最靠后的 $r_i$ 个员工会被炒鱿鱼，取而代之的是新加入的这 $r_i$ 个员工。你是第 1 号员工，你的能力值是 $a_1$ 。

还有 $q$ 次操作，每次操作的描述形如 $(x_i,y_i,z_i)$， 表示把第 $x_i$ 年加入的第 $y_i$ 个员工的能力值改为 $z_i$。 现在对于每个操作输出 $0$ 或 $1$，表示如果进行完这个操作，$m$ 年之后你会不会被炒鱿鱼。注意，操作是永久性的。

## 样例 #1

### 输入

```
5 3 3
50 40 30 20 10
4 1 2 3 100
1 4
2 6 7
1 3 300
2 1 400
2 1 5
```

### 输出

```
1
0
1
```

# 题解

## 作者：AladV (赞：1)

## 题意分析
目前这道题因为一些题目数据上的锅导致都是UKE，CF 上 A 了就行。
题目翻译我交了正在等待审核。
## 做法分析
我们分析一下这 $q$ 个操作如何影响你的生死。假设第 $x$ 年年底会死掉 $k$ 个人，结果，巧的很，第 $x-1$ 年新加入的那些员工中有一个的能力值被修改的特别大，排序后跑到你前面去了，好家伙，然后你就被淘汰了（笑死）。

所以我们维护一个数组 $sum$，$sum_i$ 表示第 $i$ 年之后有这么多的人的能力值小于你。也就是说，如果某个时刻 $sum_i<0$，恭喜你，游戏结束了，去上个厕所吧。

如何维护 $sum$？每次操作对 $sum$ 有什么影响？先回答第一个问题。

每年新加入员工，比如新加入了 $r$ 个员工其中有 $k$ 个的能力值比你低（嘿嘿~！），但是今年年底要淘汰 $num$ 个人，所以显然 $sum_i=sum_{i-1}+k-num$。这就是第一个问题的答案。

第二个问题，我们想，如果被修改的那个人，他被修改前比你强，好家伙，改完之后比你弱了，那么显然那一年的 $sum$ 就要加一。同理反之，减一。

最后的问题是怎么统计答案，显然如果这 $m$ 个 $sum_i$ 有任何一个小于 $0$ 就不行了，所以我们需要动态维护 $sum$ 数组的最小值，哗啦啦，线段树出场了。非常基本的一个线段树，维护 $sum$ 数组的最小值即可。

细节详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct SegTree
{
    int l,r;
    int minx,tag;
}t[N<<2];
int n,m,q,lst;
int sum[N],a[N];
vector<int> change[N];
int read()
{
    int x=0,f=1;
    char c=getchar();
    while (c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
void BuildTree(int p,int l,int r)
{
    t[p].l=l,t[p].r=r;
    if(l==r)
    {
        t[p].minx=sum[l];
        return ;
    }
    int mid=(l+r)>>1;
    BuildTree(p<<1,l,mid);
    BuildTree(p<<1|1,mid+1,r);
    t[p].minx=min(t[p<<1].minx,t[p<<1|1].minx);
}
void pushdown(int p)
{
    if(t[p].tag)
    {
        t[p<<1].tag+=t[p].tag;
        t[p<<1].minx+=t[p].tag;

        t[p<<1|1].tag+=t[p].tag;
        t[p<<1|1].minx+=t[p].tag;

        t[p].tag=0;
    }
}
void Modify(int p,int l,int r,int d)
{
    if(l>r || t[p].r<l || t[p].l>r) return ;
    if(l<=t[p].l && t[p].r<=r)
    {
        t[p].minx+=d;
        t[p].tag+=d;
        return ;
    }
    int mid=(t[p].l+t[p].r)>>1;
    pushdown(p);
    if(l<=mid) Modify(p<<1,l,r,d);
    if(mid<r) Modify(p<<1|1,l,r,d);
    t[p].minx=min(t[p<<1].minx,t[p<<1|1].minx);
}
int main()
{
    n=read(),m=read(),q=read();
    for(int i=1;i<=n;i++) 
    {
        a[i]=read();
        if(a[i]<a[1]) sum[0]++;
    }
    lst=0;
    for(int i=1;i<=m;i++)
    {
        int x=read();
        sum[i]=sum[i-1]+lst-x;
        lst=0;
        change[i].push_back(-1);
        for(int j=1;j<=x;j++) {int y=read();change[i].push_back(y);if(y<a[1]) lst++;}
    }
    BuildTree(1,1,m);
    while (q--)
    {
        int x=read(),y=read(),z=read();
        if(change[x][y]>a[1] && z<a[1]) Modify(1,x+1,m,1);
        if(change[x][y]<a[1] && z>a[1]) Modify(1,x+1,m,-1);
        change[x][y]=z;
        if(t[1].minx<0) cout<<0<<endl;
        else cout<<1<<endl;
    }
    return 0;
}
```
思路参考：https://blog.csdn.net/qq_45458915/article/details/108416662

---

## 作者：ran_qwq (赞：0)

2v2 duel 到了这道题，被 Cat_Mouse 带飞了，orz。

尝试找出一些性质。

- 性质 1：肯定是能力值低的比能力值高的先被炒鱿鱼。
- 性质 2：根据性质 1，能力值比自己高的人会越来越多。

设第 $i$ 年比自己高的人数（初始加上前 $i$ 年新加人的贡献）为 $c_i$。

综上，第 $i$ 年自己不会被炒鱿鱼，当且仅当 $n-r_i>c_{i-1}$。可以保留到最后，当且仅当 $\min\limits_{i=1}^mn-r_i-c_{i-1}>0$。为表述方便设 $f_i=n-r_i-c_{i-1}$。

考虑一次修改的影响，假设在第 $x$ 年新加入一个能力值比自己高的人，减去一个同理。

则 $\forall i\in[x,m],c_i\leftarrow c_i+1$，即 $\forall i\in[x+1,m],f_i\leftarrow f_i-1$。

用线段树维护 $f$ 的全局最小值即可。

```cpp
int n,m,q,b[N],c[N],a[N]; vi v[N];
struct SGT {
	#define ls (id<<1)
	#define rs (id<<1|1)
	#define mid (l+r>>1)
	#define all 1,1,m
	#define Ls ls,l,mid
	#define Rs rs,mid+1,r
	int mn[N*4],tg[N*4];
	il void pu(int id) {mn[id]=min(mn[ls],mn[rs]);}
	il void ad(int id,int k) {mn[id]+=k,tg[id]+=k;}
	il void pd(int id) {ad(ls,tg[id]),ad(rs,tg[id]),tg[id]=0;}
	void bld(int id,int l,int r) {
		if(l==r) return mn[id]=n-c[l-1]-b[l],void();
		bld(Ls),bld(Rs),pu(id);
	}
	void upd(int id,int l,int r,int L,int R,int k) {
		if(L>R) return; if(L<=l&&r<=R) return ad(id,k);
		pd(id),L<=mid?upd(Ls,L,R,k):void(),R>mid?upd(Rs,L,R,k):void(),pu(id);
	}
	int qry(int id,int l,int r,int L,int R) {
		if(L<=l&&r<=R) return mn[id];
		pd(id); return min(L<=mid?qry(Ls,L,R):INF,R>mid?qry(Rs,L,R):INF);
	}
} sgt;
void QwQ() {
	n=rd(),m=rd(),q=rd();
	for(int i=1;i<=n;i++) a[i]=rd(),c[0]+=a[i]>a[1];
	for(int i=1;i<=m;i++) {
		b[i]=rd(),v[i].resize(b[i]+1),c[i]=c[i-1];
		for(int j=1;j<=b[i];j++) v[i][j]=rd(),c[i]+=v[i][j]>a[1];
	}
	sgt.bld(all);
	for(int x,y,z;q--;) {
		x=rd(),y=rd(),z=rd();
		if(v[x][y]>a[1]&&z<a[1]) sgt.upd(all,x+1,m,1);
		else if(v[x][y]<a[1]&&z>a[1]) sgt.upd(all,x+1,m,-1);
		v[x][y]=z,wr(sgt.mn[1]>0,"\n");
	}
}
```

---

