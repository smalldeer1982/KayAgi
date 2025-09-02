# k-Maximum Subsequence Sum

## 题目描述

Consider integer sequence $ a_{1},a_{2},...,a_{n} $ . You should run queries of two types:

- The query format is " $ 0 $ $ i $ $ val $ ". In reply to this query you should make the following assignment: $ a_{i}=val $ .
- The query format is " $ 1 $ $ l $ $ r $ $ k $ ". In reply to this query you should print the maximum sum of at most $ k $ non-intersecting subsegments of sequence $ a_{l},a_{l+1},...,a_{r} $ . Formally, you should choose at most $ k $ pairs of integers $ (x_{1},y_{1}),(x_{2},y_{2}),...,(x_{t},y_{t}) $ $ (l<=x_{1}<=y_{1}<x_{2}<=y_{2}<...<x_{t}<=y_{t}<=r; t<=k) $ such that the sum $ a_{x1}+a_{x1}+1+...+a_{y1}+a_{x2}+a_{x2}+1+...+a_{y2}+...+a_{xt}+a_{xt}+1+...+a_{yt} $ is as large as possible. Note that you should choose at most $ k $ subsegments. Particularly, you can choose 0 subsegments. In this case the described sum considered equal to zero.

## 说明/提示

In the first query of the first example you can select a single pair $ (1,9) $ . So the described sum will be 17.

Look at the second query of the first example. How to choose two subsegments? (1, 3) and (7, 9)? Definitely not, the sum we could get from (1, 3) and (7, 9) is 20, against the optimal configuration (1, 7) and (9, 9) with 25.

The answer to the third query is 0, we prefer select nothing if all of the numbers in the given interval are negative.

## 样例 #1

### 输入

```
9
9 -8 9 -1 -1 -1 9 -8 9
3
1 1 9 1
1 1 9 2
1 4 6 3
```

### 输出

```
17
25
0
```

## 样例 #2

### 输入

```
15
-4 8 -3 -10 10 4 -7 -7 0 -6 3 8 -10 7 2
15
1 3 9 2
1 6 12 1
0 6 5
0 10 -7
1 4 9 1
1 7 9 1
0 10 -3
1 4 10 2
1 3 13 2
1 4 11 2
0 15 -9
0 13 -9
0 11 -10
1 5 14 2
1 6 12 1
```

### 输出

```
14
11
15
0
15
26
18
23
8
```

# 题解

## 作者：liangzihao (赞：34)

因为$k$比较小，可以考虑使用费用流的模型。源点$S$向每个点$i$连一条流量为$1$，费用为$0$的边；$i$向$i+1$连一条费用为$a_i$，流量为$1$的边；$i$向汇点$T$连流量为$1$，费用为$0$的边。那么，一滴从$S>i>j>T$的流，代表选取区间$[i,j-1]$。可以发现的是，每多流一滴流量，就多一个区间。问题就变成了使用不多于$k$滴流量，能得到的最大费用。因为每次增广只会多一点流量，而每次要查询的最长路就是每次增广的贡献，这个贡献是由一段区间构成。

**所以，每次增广相当于找到询问区间的最大子区间和，然后再把该区间取反（反向弧的费用是正向弧的相反数）。**举个例子，如果第一次选了区间$[1,4]$，然后取反后取了区间$[3,6]$，此时相当于取了区间$[1,2]$和$[5,6]$。**增广完$k$次，或者增广贡献小于$0$时，就得到了答案。**

因为不可能同时选共起点或共终点的区间，假如我们第一次取了$[1,4]$，那么一定不可能取反第二次后会取$[1,5]$，这样得到的区间是$[4,5]$，因为我们保证每次增广的贡献大于等于$0$，这个区间是比$[1,4]$大的，与一开始就取最大子区间矛盾。所以每次增广必然会增加一个区间。

现在就可以用线段树维护了，相当于维护一个最大子区间值，当然，同时肯定要维护最大左区间和与最大右区间和区间和，单点修改就不用$lazy$了，不然真的太毒瘤了。当然，由于有反转操作，还需要维护最小的子区间和，反转时$swap$一下就好，打上反转标记。
定义一个区间类型及使用重载运算符来处理区间加可以减少代码量。

代码：
```
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>

const int maxn=1e5+7;

using namespace std;

int n,m,x,op,y,k;

struct rec{
    int l,r,s;
};

rec operator + (rec x,rec y)
{
    return (rec){x.l,y.r,x.s+y.s};
}

bool operator < (rec x,rec y)
{
    return x.s<y.s;
}

struct node{
    rec smax,smin,lmax,rmax,lmin,rmin,sum;
    int rev;
}t[maxn*4];

queue <node> q;

void neww(int p,int l,int k)
{
    t[p].smax=(rec){l,l,k};
    t[p].lmax=(rec){l,l,k};
    t[p].rmax=(rec){l,l,k};
    t[p].smin=(rec){l,l,k};
    t[p].lmin=(rec){l,l,k};
    t[p].rmin=(rec){l,l,k};
    t[p].sum=(rec){l,l,k};
}

node merge(node x,node y)
{
    node z;
    z.smax=max(x.smax,y.smax);
    z.smax=max(z.smax,x.rmax+y.lmax);
    z.smin=min(x.smin,y.smin);
    z.smin=min(z.smin,x.rmin+y.lmin);
    z.lmax=max(x.lmax,x.sum+y.lmax);
    z.rmax=max(y.rmax,x.rmax+y.sum);
    z.lmin=min(x.lmin,x.sum+y.lmin);
    z.rmin=min(y.rmin,x.rmin+y.sum);
    z.sum=x.sum+y.sum;
    z.rev=0;
    return z;
}

void clean(int p)
{
    swap(t[p].smax,t[p].smin);
    swap(t[p].lmax,t[p].lmin);
    swap(t[p].rmax,t[p].rmin);
    t[p].smax.s*=-1;
    t[p].smin.s*=-1;
    t[p].lmax.s*=-1;
    t[p].lmin.s*=-1;
    t[p].rmax.s*=-1;
    t[p].rmin.s*=-1;
    t[p].sum.s*=-1;
    t[p].rev^=1;
}

void change(int p,int l,int r,int x,int k)
{	
    if (l==r)
    {
        neww(p,l,k);
        return;
    }
    int mid=(l+r)/2;
    if (t[p].rev)
    {
        clean(p*2);
        clean(p*2+1);
        t[p].rev^=1;
    }
    if (x<=mid) change(p*2,l,mid,x,k);
           else change(p*2+1,mid+1,r,x,k);
    t[p]=merge(t[p*2],t[p*2+1]);
}

void rev(int p,int l,int r,int x,int y)
{
    if ((l==x) && (r==y))
    {
        clean(p);
        return;
    }
    int mid=(l+r)/2;
    if (t[p].rev)
    {
        clean(p*2);
        clean(p*2+1);
        t[p].rev^=1;
    }
    if (y<=mid) rev(p*2,l,mid,x,y);
    else if (x>mid) rev(p*2+1,mid+1,r,x,y);
    else
    {
        rev(p*2,l,mid,x,mid);
        rev(p*2+1,mid+1,r,mid+1,y);
    }
    t[p]=merge(t[p*2],t[p*2+1]);
}

node query(int p,int l,int r,int x,int y)
{
    if ((l==x) && (r==y)) return t[p];
    int mid=(l+r)/2;
    if (t[p].rev)
    {
        clean(p*2);
        clean(p*2+1);
        t[p].rev^=1;
    }
    if (y<=mid) return query(p*2,l,mid,x,y);
    else if (x>mid) return query(p*2+1,mid+1,r,x,y);
    else
    {
        return merge(query(p*2,l,mid,x,mid),query(p*2+1,mid+1,r,mid+1,y));
    }
}

int main()
{
    scanf("%d",&n);		
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        change(1,1,n,i,x);
    }	
    scanf("%d",&m);		
    for (int i=1;i<=m;i++)
    {
        scanf("%d",&op);		
        if (op==0)
        {
            scanf("%d%d",&x,&k);
            change(1,1,n,x,k);
        }
        else
        {
            scanf("%d%d%d",&x,&y,&k);			
            int ans=0;			
            while (k--)
            {			
                node d=query(1,1,n,x,y);
                if (d.smax.s<0) break;
                ans+=d.smax.s;
                rev(1,1,n,d.smax.l,d.smax.r);
                q.push(d);
            }
            printf("%d\n",ans);
            while (!q.empty())
            {
                node d=q.front();
                q.pop();
                rev(1,1,n,d.smax.l,d.smax.r);
            }
        }
    }
} 
```

---

## 作者：云浅知处 (赞：24)

发一个题解区暂时没有的做法！

考虑线段树，每个节点维护 $f_{x,0/1,0/1}$ 表示这个区间取了至多 $x$ 段，左右端点是否钦定要取，的最大权值。

合并的时候，设 $\circ$ 为 max+ 卷积，两侧分别为 $f,g$，合并起来为 $h$，经过讨论发现只需要做：

$$
h_{0,0}\leftarrow f_{0,0}\circ g_{0,0},h_{0,0}\leftarrow \text{Shift}(f_{0,1}\circ g_{1,0})\\
h_{0,1}\leftarrow f_{0,0}\circ g_{0,1},h_{0,1}\leftarrow \text{Shift}(f_{0,1}\circ g_{1,1})\\
h_{1,0}\leftarrow f_{1,0}\circ g_{0,0},h_{1,0}\leftarrow \text{Shift}(f_{1,1}\circ g_{1,0})\\
h_{1,1}\leftarrow f_{1,0}\circ g_{0,1},h_{1,1}\leftarrow \text{Shift}(f_{1,1}\circ g_{1,1})\\
$$

其中 $\text{Shift}(f)$ 表示将 $f$ 整体左移，即 $f_x\leftarrow f_{x+1}$；$a\leftarrow b$ 表示 $a$ 对 $b$ 取 max。

如果直接做 max+ 卷积需要 $O(k^2)$ 合并，不过众所周知 $f$ 关于 $x$ 是凸的，所以可以用闵可夫斯基和来 $O(k)$ 合并！于是就可以做到 $O(nk+qk\log n)$ 了。

```cpp
#include<bits/stdc++.h>

#define ll long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

void cmax(int &x,int v){x=max(x,v);}
void cmin(int &x,int v){x=min(x,v);}

const int N=1e5+5;
const int K=21;
const int INF=1e9;

#define vi vector<int>
#define vvi vector<vector<int> >

vvi d[N<<2];//00,01,10,11

vi operator+(vi &A,vi &B){
	vi res(K+1);
	res[0]=A[0]+B[0];int p=1,q=1;
	for(int i=1;i<=K;i++){
		if(p==K+1){res[i]=res[i-1]+B[q]-B[q-1];q++;continue;}
		if(q==K+1){res[i]=res[i-1]+A[p]-A[p-1];p++;continue;}
		if(A[p]-A[p-1]>B[q]-B[q-1])res[i]=res[i-1]+A[p]-A[p-1],p++;
		else res[i]=res[i-1]+B[q]-B[q-1],q++;
	}
	return res;
}

void Cmax(vi &A,vi B){for(int i=0;i<=K;i++)cmax(A[i],B[i]);}
void Smax(vi &A,vi B){for(int i=0;i<K;i++)cmax(A[i],B[i+1]);}

vvi op(vvi &f,vvi &g){
	vvi h;h.resize(4);
	for(auto &x:h)x.resize(K+1,-INF);
	Cmax(h[0],f[0]+g[0]),Smax(h[0],f[1]+g[2]);
	Cmax(h[1],f[0]+g[1]),Smax(h[1],f[1]+g[3]);
	Cmax(h[2],f[2]+g[0]),Smax(h[2],f[3]+g[2]);
	Cmax(h[3],f[2]+g[1]),Smax(h[3],f[3]+g[3]);
	return h;
}

#define ls(p) (p<<1)
#define rs(p) (p<<1|1)

void pushup(int p){d[p]=op(d[ls(p)],d[rs(p)]);}
int a[N];

void Set(int p,int c){
	d[p].clear(),d[p].resize(4);
	for(auto &x:d[p])x.resize(K+1,c);
	d[p][0][0]=0,d[p][1][0]=d[p][2][0]=d[p][3][0]=-INF;
}
void build(int l,int r,int p){
	if(l==r)return Set(p,a[l]),void();
	int mid=(l+r)>>1;
	build(l,mid,ls(p)),build(mid+1,r,rs(p)),pushup(p);
}

void modify(int x,int v,int ql,int qr,int p){
	if(ql==qr)return Set(p,v),void();
	int mid=(ql+qr)>>1;
	if(x<=mid)modify(x,v,ql,mid,ls(p));
	else modify(x,v,mid+1,qr,rs(p));
	pushup(p);
}

vvi res;
void query(int l,int r,int ql,int qr,int p){
	if(l<=ql&&qr<=r)return res=op(res,d[p]),void();
	int mid=(ql+qr)>>1;
	if(l<=mid)query(l,r,ql,mid,ls(p));
	if(r>mid)query(l,r,mid+1,qr,rs(p));
}

int n,q;

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,n,1);
	q=read();
	while(q--){
		int op=read();
		if(op==0){int p=read(),v=read();modify(p,v,1,n,1);}
		else{
			int l=read(),r=read(),k=read();
			res.clear();res.resize(4);res[0].resize(K+1,0);
			for(int c=1;c<4;c++)res[c].resize(K+1,-INF);
			query(l,r,1,n,1);cout<<res[0][k]<<'\n';
		}
	}

	return 0;
}
```

---

## 作者：AThousandSuns (赞：17)

作为本题rk2水一波题解……%%%stO AThousandMoon Orz%%%

为什么大佬们会认为这是模拟费用流啊……正解看起来跟费用流完全没关系好吗……

这取反不就相当于撤销选这段吗……~~（此时正在被旁边的AThousandMoon嘲讽这就是费用流，好像真的可以这么说……）~~

随便随便，这里只是给像我这样的蒟蒻一些信心，不要被dalao们说是模拟费用流就吓退了。

---
考虑贪心，每次都选择最大子段和。然而可能已经选的一些数中一部分不属于最优解，于是就有了个类似网络流的“撤销”操作。

容易发现加上相反数就是撤销了选这些数。那么每次把最大子段和中的数取反即可。之后求的最大子段和如果包括这些被取反的数，就相当于撤销了这些方案。那么这样的得到的一定是最优解。

画个图容易知道，进行 $k$ 次操作会取到所有段数 $\le k$ 的方案的最大值，那么直接 $k$ 次操作即可。

~~AThousandMoon：这tm不就是费用流……~~

具体实现，由于需要取反一个具体区间，所以要记录下最大子段和的左右端点。然后取反后最大值会变成原来最小值的相反数，所以还要有最小子段和。

具体见代码。鬼知道我打了多久……由于想象力匮乏导致的变量名难看，请见谅。

时间复杂度 $O(mk\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010,mod=998244353;
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,m,a[maxn],ls[maxn],rs[maxn],tp;
inline bool chkmax(int &x,int y){
	if(y>x) return x=y,true;
	return false;
}
inline bool chkmin(int &x,int y){
	if(y<x) return x=y,true;
	return false;
}
struct node{
	int l,r,sum,lmax,rmax,amax,lx,rx,llx,rrx,lmin,rmin,amin,ln,rn,lln,rrn;
	node operator+(const node &nd)const{
		node ans;
		ans.l=l;ans.r=nd.r;
		ans.sum=sum+nd.sum;
		ans.lmax=lmax;ans.llx=llx;
		if(chkmax(ans.lmax,sum+nd.lmax)) ans.llx=nd.llx;
		ans.rmax=nd.rmax;ans.rrx=nd.rrx;
		if(chkmax(ans.rmax,nd.sum+rmax)) ans.rrx=rrx;
		ans.amax=amax;ans.lx=lx;ans.rx=rx;
		if(chkmax(ans.amax,nd.amax)) ans.lx=nd.lx,ans.rx=nd.rx;
		if(chkmax(ans.amax,rmax+nd.lmax)) ans.lx=rrx,ans.rx=nd.llx;
		ans.lmin=lmin;ans.lln=lln;
		if(chkmin(ans.lmin,sum+nd.lmin)) ans.lln=nd.lln;
		ans.rmin=nd.rmin;ans.rrn=nd.rrn;
		if(chkmin(ans.rmin,nd.sum+rmin)) ans.rrn=rrn;
		ans.amin=amin;ans.ln=ln;ans.rn=rn;
		if(chkmin(ans.amin,nd.amin)) ans.ln=nd.ln,ans.rn=nd.rn;
		if(chkmin(ans.amin,rmin+nd.lmin)) ans.ln=rrn,ans.rn=nd.lln;
		return ans;
	}
}seg[maxn*4];
bool rev[maxn*4];
inline void setrev(int o){
	rev[o]^=1;
	seg[o].sum*=-1;
	int tlmax=seg[o].lmax,trmax=seg[o].rmax,tamax=seg[o].amax;
	int tlx=seg[o].lx,trx=seg[o].rx,tllx=seg[o].llx,trrx=seg[o].rrx;
	seg[o].lmax=-seg[o].lmin;seg[o].rmax=-seg[o].rmin;seg[o].amax=-seg[o].amin;
	seg[o].lmin=-tlmax;seg[o].rmin=-trmax;seg[o].amin=-tamax;
	swap(seg[o].lx,seg[o].ln);swap(seg[o].rx,seg[o].rn);
	swap(seg[o].llx,seg[o].lln);swap(seg[o].rrx,seg[o].rrn);
}
inline void pushdown(int o){
	if(rev[o]){
		setrev(o<<1);
		setrev(o<<1|1);
		rev[o]=0;
	}
}
void build(int o,int l,int r){
	if(l==r) return void(seg[o]=(node){l,l,a[l],a[l],a[l],a[l],l,l,l,l,a[l],a[l],a[l],l,l,l,l});
	int mid=(l+r)>>1;
	build(lson);build(rson);
	seg[o]=seg[o<<1]+seg[o<<1|1];
}
void update(int o,int l,int r,int p,int v){
	if(l==r) return void(seg[o]=(node){l,l,v,v,v,v,l,l,l,l,v,v,v,l,l,l,l});
	pushdown(o);
	int mid=(l+r)>>1;
	if(mid>=p) update(lson,p,v);
	else update(rson,p,v);
	seg[o]=seg[o<<1]+seg[o<<1|1];
}
void reverse(int o,int l,int r,int ql,int qr){
	if(l>=ql && r<=qr) return setrev(o);
	pushdown(o);
	int mid=(l+r)>>1;
	if(mid>=ql) reverse(lson,ql,qr);
	if(mid<qr) reverse(rson,ql,qr);
	seg[o]=seg[o<<1]+seg[o<<1|1];
}
node query(int o,int l,int r,int ql,int qr){
	if(l>=ql && r<=qr) return seg[o];
	pushdown(o);
	int mid=(l+r)>>1;
	if(mid<ql) return query(rson,ql,qr);
	if(mid>=qr) return query(lson,ql,qr);
	return query(lson,ql,qr)+query(rson,ql,qr);
}
int main(){
	n=read();
	FOR(i,1,n) a[i]=read();
	build(1,1,n);
	m=read();
	while(m--){
		int op=read(),x=read(),y=read();
		if(op){
			int k=read(),s=0,ans=0;
			tp=0;
			while(k--){
				node nd=query(1,1,n,x,y);
				ls[++tp]=nd.lx;rs[tp]=nd.rx;
				chkmax(ans,s+=nd.amax);
				reverse(1,1,n,nd.lx,nd.rx);
			}
			while(tp) reverse(1,1,n,ls[tp],rs[tp]),tp--;
			printf("%d\n",ans);
		}
		else update(1,1,n,x,y);
	}
}
```

---

## 作者：zhiyangfan (赞：13)

~~开始之前吐槽一句，这题思维难度可能紫，但码量是真滴黑啊~~


------------

## 题意简述
给定一个长为 $n$ 的序列 {$a_i$} ，有 $Q$ 次操作：
- 单点修改。
- 给定一个区间 $[l,r]$ ，在 $[l,r]$ 内选择至多 $k$ 个不相交的连续子段让其和最大。
- $n,Q\leq10^5,k\leq20$

------------
## 基本思路
首先考虑 $k=1$ 的特殊情况：维护某一区间的最大子段和。这是经典的线段树维护的问题了，即维护一个区间 $[l,r]$ 的最大子段和 $ms$，$l$ 开头的最大子段和 $ls$，$r$ 结尾的最大子段和 $rs$ ，和区间和 $sum$。敢点开这个题的神应该都知道 pushup 和 pushdown 的写法，~~所以就略过~~（在代码里提一下）。

接下来考虑 $k>1$ 的情况，注意到 $k$ 的范围本身不大，再加上每次**增广**一个子段和的询问，可以~~很自然~~联想到与EK算法类似的思路，即迭代 $k$ 次，每次多寻找一个子段和。

可以参考最大流/费用流的实现方式之一——引入反流，即保留反悔的可能。处理完 $k=1$ 的询问后，将和最大的子段 $[l,r]$ 全部乘上 $-1$ 。这样，在处理下一次询问时，如果所得的子段 $[x,y]$ 与 $[l,r]$ 无交集，自然符合题意；如果有交集，但不完全覆盖，说明覆盖的部分被反悔掉了，我们得到了一个新的不想交的最大子段和（因为这俩都是求的最大子段和，所以可以保证是**当前**k值的最大值）；易得 $[l,r]$，$[x,y]$ 不可能完全相交。所以按照上述过程迭代 $k$ 次即得 $k$ 个最大子段。\
**注意题目说至多 $k$ 个，所以应取 $k=0,1..k$ 时的最大子段和中的最大值。**

为了实现上述过程，考虑我们需要维护什么 。
- 原来就需要维护的区间 $[l,r]$ 的最大子段和 $ms$，$l$ 开头的最大子段和 $ls$， $r$ 结尾的最大子段和 $rs$ ，和区间和 $sum$。
- 为了乘 $-1$ 时能正确维护上述信息，我们还需要维护区间 $[l,r]$ 的最小子段和 $as$ ， $l$ 开头的最小子段和 $ml$，$r$ 结尾的最小子段和 $mr$。（乘 $-1$ 后最大最小交换即可）。
- 为了执行乘 $-1$ 的操作，我们需要维护懒标记 $lazy$。
- 为了了解在哪里乘 $-1$，我们需要维护区间 $[l,r]$ 的最大子段和的开头结尾 $li,ri$，最小子段和的开头结尾 $u,v$，$l$ 开头的最大子段和的结尾 $rr$，$r$ 结尾的最大子段和的开头$ll$，$l$开头的最小子段和的结尾 $vv$，$r$ 结尾的最小子段和的开头 $uu$。

看起来就很麻烦qwq，具体细节看代码吧，鬼知道我调了多久（ps. 封装一些结构体会更好看）qwq。
## 代码
```cpp
#include <cstdio>
#define Ls(x) (x << 1)
#define Rs(x) (x << 1 | 1)
inline void swap(int& a1, int& a2) { int t = a1; a1 = a2; a2 = t; }
inline int max(const int& a1, const int& a2) { return a1 > a2 ? a1 : a2; }
const int N = 1e5 + 10, inf = 2e9; int a[N]; int L[30], R[30];
struct segTree{ int ms, ls, rs, sum, li, ri, lazy, rr, ll, as, u, v, ml, mr, uu, vv; }h[N << 2];
inline void pushup(int k)
{
	//左 右还是横跨
	if (h[Ls(k)].ms > h[Rs(k)].ms) h[k].ms = h[Ls(k)].ms, h[k].li = h[Ls(k)].li, h[k].ri = h[Ls(k)].ri;
	else h[k].ms = h[Rs(k)].ms, h[k].li = h[Rs(k)].li, h[k].ri = h[Rs(k)].ri;
	if (h[Ls(k)].rs + h[Rs(k)].ls > h[k].ms) h[k].ms = h[Ls(k)].rs + h[Rs(k)].ls, h[k].li = h[Ls(k)].ll, h[k].ri = h[Rs(k)].rr;
	
	//左 还是横跨 
	if (h[Ls(k)].ls > h[Ls(k)].sum + h[Rs(k)].ls) h[k].ls = h[Ls(k)].ls, h[k].rr = h[Ls(k)].rr;
	else h[k].ls = h[Ls(k)].sum + h[Rs(k)].ls, h[k].rr = h[Rs(k)].rr;
	
	//右 还是横跨
	if (h[Rs(k)].rs > h[Rs(k)].sum + h[Ls(k)].rs) h[k].rs = h[Rs(k)].rs, h[k].ll = h[Rs(k)].ll;
	else h[k].rs = h[Rs(k)].sum + h[Ls(k)].rs, h[k].ll = h[Ls(k)].ll;
	
	h[k].sum = h[Ls(k)].sum + h[Rs(k)].sum;
	
	
	//类似最大值操作
	if (h[Ls(k)].as < h[Rs(k)].as) h[k].as = h[Ls(k)].as, h[k].u = h[Ls(k)].u, h[k].v = h[Ls(k)].v;
	else h[k].as = h[Rs(k)].as, h[k].u = h[Rs(k)].u, h[k].v = h[Rs(k)].v;
	if (h[Ls(k)].mr + h[Rs(k)].ml < h[k].as) h[k].as = h[Ls(k)].mr + h[Rs(k)].ml, h[k].u = h[Ls(k)].uu, h[k].v = h[Rs(k)].vv;
	
	if (h[Ls(k)].ml < h[Ls(k)].sum + h[Rs(k)].ml) h[k].ml = h[Ls(k)].ml, h[k].vv = h[Ls(k)].vv;
	else h[k].ml = h[Ls(k)].sum + h[Rs(k)].ml, h[k].vv = h[Rs(k)].vv;
	
	if (h[Rs(k)].mr < h[Rs(k)].sum + h[Ls(k)].mr) h[k].mr = h[Rs(k)].mr, h[k].uu = h[Rs(k)].uu;
	else h[k].mr = h[Rs(k)].sum + h[Ls(k)].mr, h[k].uu = h[Ls(k)].uu;
}
inline void pushdown(int k, int l, int r, int mid)
{
	if (h[k].lazy)
	{
		//交换最大值与最小值的所有信息（可以封装结构体，这样直接swap结构体）
		swap(h[Ls(k)].u, h[Ls(k)].li); swap(h[Ls(k)].v, h[Ls(k)].ri); swap(h[Ls(k)].ms, h[Ls(k)].as);
		swap(h[Ls(k)].ml, h[Ls(k)].ls); swap(h[Ls(k)].mr, h[Ls(k)].rs); swap(h[Ls(k)].ll, h[Ls(k)].uu); swap(h[Ls(k)].rr, h[Ls(k)].vv);
		h[Ls(k)].ms *= -1; h[Ls(k)].as *= -1; h[Ls(k)].ls *= -1; h[Ls(k)].rs *= -1; h[Ls(k)].ml *= -1; h[Ls(k)].mr *= -1; h[Ls(k)].sum *= -1;
		
		swap(h[Rs(k)].u, h[Rs(k)].li); swap(h[Rs(k)].v, h[Rs(k)].ri); swap(h[Rs(k)].ms, h[Rs(k)].as);
		swap(h[Rs(k)].ml, h[Rs(k)].ls); swap(h[Rs(k)].mr, h[Rs(k)].rs); swap(h[Rs(k)].ll, h[Rs(k)].uu); swap(h[Rs(k)].rr, h[Rs(k)].vv);
		h[Rs(k)].ms *= -1; h[Rs(k)].as *= -1; h[Rs(k)].ls *= -1; h[Rs(k)].rs *= -1; h[Rs(k)].ml *= -1; h[Rs(k)].mr *= -1; h[Rs(k)].sum *= -1;
		
		//类似区间翻转，*-1的操作也为异或合并
		h[Ls(k)].lazy ^= 1; h[Rs(k)].lazy ^= 1; h[k].lazy = 0;
	}
}
void build(int k, int l, int r)
{
	if (l == r) { h[k].as = h[k].sum = h[k].ml = h[k].mr = h[k].rs = h[k].ls = h[k].ms = a[l]; h[k].u = h[k].v = h[k].li = h[k].ll = h[k].ri = h[k].rr = h[k].uu = h[k].vv = l; return ; }
	int mid = l + r >> 1; 
	build(Ls(k), l, mid); build(Rs(k), mid + 1, r);
	pushup(k);
}
void change(int k, int l, int r, int x, int v)
{
	if (l == r) { h[k].as = h[k].sum = h[k].ml = h[k].mr = h[k].rs = h[k].ls = h[k].ms = a[l]; return ; }
	int mid = l + r >> 1; pushdown(k, l, r, mid);
	if (x <= mid) change(Ls(k), l, mid, x, v);
	else change(Rs(k), mid + 1, r, x, v);
	pushup(k);
}
void mul(int k, int l, int r, int x, int y)
{
	if (x <= l && r <= y)
	{
		//类似pushdown的操作
		swap(h[k].u, h[k].li); swap(h[k].v, h[k].ri); swap(h[k].ms, h[k].as);
		swap(h[k].ml, h[k].ls); swap(h[k].mr, h[k].rs); swap(h[k].ll, h[k].uu); swap(h[k].rr, h[k].vv);
		h[k].ms *= -1; h[k].as *= -1; h[k].ls *= -1; h[k].rs *= -1; h[k].ml *= -1; h[k].mr *= -1; h[k].sum *= -1;
		h[k].lazy ^= 1; return ;
	}
	int mid = l + r >> 1; pushdown(k, l, r, mid);
	if (x <= mid) mul(Ls(k), l, mid, x, y);
	if (mid < y) mul(Rs(k), mid + 1, r, x, y);
	pushup(k);
}
//因为需要用到的信息较多，所以直接返回一个节点
segTree query(int k, int l, int r, int x, int y)
{
	if (x <= l && r <= y) return h[k];
	int mid = l + r >> 1; pushdown(k, l, r, mid); segTree ret, lef, rig;
	//横跨就合并
	if (x <= mid && mid < y)
	{
		lef = query(Ls(k), l, mid, x, y); rig = query(Rs(k), mid + 1, r, x, y);
		//类似pushup的操作
		if (lef.ms > rig.ms) ret.ms = lef.ms, ret.li = lef.li, ret.ri = lef.ri;
		else ret.ms = rig.ms, ret.li = rig.li, ret.ri = rig.ri;
		if (lef.rs + rig.ls > ret.ms) ret.ms = lef.rs + rig.ls, ret.li = lef.ll, ret.ri = rig.rr;
		
		if (lef.ls > lef.sum + rig.ls) ret.ls = lef.ls, ret.rr = lef.rr;
		else ret.ls = lef.sum + rig.ls, ret.rr = rig.rr;
		
		if (rig.rs > rig.sum + lef.rs) ret.rs = rig.rs, ret.ll = rig.ll;
		else ret.rs = rig.sum + lef.rs, ret.ll = lef.ll;
		
		ret.sum = lef.sum + rig.sum;
		return ret;
	}
	//否则直接返回左或右
	if (x <= mid) return query(Ls(k), l, mid, x, y);
	if (mid < y) return query(Rs(k), mid + 1, r, x, y);
}
int main()
{
	int n, m; scanf("%d", &n); segTree t;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	build(1, 1, n); scanf("%d", &m);
	for (int i = 1, opt, l, r, k, ret = 0, tt, ans = 0/*ans这里代表k=0的情况*/; i <= m; i++)
	{
		scanf("%d%d%d", &opt, &l, &r);
		if (opt == 0) a[l] = r, change(1, 1, n, l, r);
		else
		{
			scanf("%d", &k); tt = k;
			while (k)
			{
				t = query(1, 1, n, l, r);
				ret += t.ms; ans = max(ans, ret);
				mul(1, 1, n, t.li, t.ri);
				//记录一下每次*-1的情况，方便以后乘回来
				L[k] = t.li; R[k] = t.ri; k--;
			}
			for (int j = 1; j <= tt; j++) mul(1, 1, n, L[j], R[j]);
			printf("%d\n", ans);
			ret = 0; ans = 0;
		}
	}
	return 0;
}
```



---

## 作者：米奇 (赞：12)

## 题意：
长度为$n$的数列，支持两种操作：

1.修改某个位置的值

2.询问区间$[l,r]$里选出至多$k$个不相交的
子段和的最大值。

一共有$m$个操作

## 题解：线段树+堆

当k=1是答案就是最大子段和

当k=2是答案就有两种情况了：

1:最大子段和+不相交的次大子段和

2:最大子段和-最大子段和区间的最小子段和
（其实就是把最大子段和分成两部分）

我们就想到像超级钢琴一样，选出一段$[l,r]$,就加入$[L,l-1]$,$[r+1,R]$

比如我们在区间$[L,R]$中找到最大子段和$[l,r]$,那么我们就要把$[L,l-1]$,$[r+1,R]$的最大子段和已以及$[l,r]$的最小子段和加入堆中

如果是最小子段和也差不多。在区间$[L,R]$中找到最小子段和$[l,r]$,那么我们就要把$[L,l-1]$,$[r+1,R]$的最小子段和已以及$[l,r]$的最大子段和加入堆中

## 代码：
```cpp
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define next Next
//#define int long long
char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
inline int read()
{
    int ret=0,f=0;char c=gc();
    while(!isdigit(c)){if(c=='-')f=1;c=gc();}
    while(isdigit(c)){ret=ret*10+c-48;c=gc();}
    if(f)return -ret;return ret;
}
void write(int x)
{
    if(x<10)
    {
        putchar('0'+x);
        return;
    }
    write(x/10);
    putchar('0'+x%10);
}
#define mid (l+r)/2
const int N=1e5+5;
int n,m,opt,x,y,a[N]; 
struct node{
    int sum,ans,l,r,ansl,ansr,ql,qr;
}tree[N*4],tree2[N*4];
struct Node{
    int val,l,r,ql,qr,opt;
};
bool operator < (Node a,Node b)
{
    return a.val<b.val;
}
void pushup(int nod,int l,int r)
{
    tree[nod].sum=tree[nod*2].sum+tree[nod*2+1].sum;
    if(tree[nod*2].sum+tree[nod*2+1].l>tree[nod*2].l)
    {
        tree[nod].l=tree[nod*2].sum+tree[nod*2+1].l;
        tree[nod].qr=tree[nod*2+1].qr;
    }
    else{
        tree[nod].l=tree[nod*2].l;
        tree[nod].qr=tree[nod*2].qr;
    }
    if(tree[nod*2+1].sum+tree[nod*2].r>tree[nod*2+1].r)
    {
        tree[nod].r=tree[nod*2+1].sum+tree[nod*2].r;
        tree[nod].ql=tree[nod*2].ql;
    }
    else{
        tree[nod].r=tree[nod*2+1].r;
        tree[nod].ql=tree[nod*2+1].ql;
    }
    tree[nod].ans=tree[nod*2].ans;
    tree[nod].ansl=tree[nod*2].ansl;
    tree[nod].ansr=tree[nod*2].ansr;
    if(tree[nod*2+1].ans>tree[nod].ans)
    {
        tree[nod].ans=tree[nod*2+1].ans;
        tree[nod].ansl=tree[nod*2+1].ansl;
        tree[nod].ansr=tree[nod*2+1].ansr;	
    }
    if(tree[nod*2].r+tree[nod*2+1].l>tree[nod].ans)
    {
        tree[nod].ans=tree[nod*2].r+tree[nod*2+1].l;
        tree[nod].ansl=tree[nod*2].ql;
        tree[nod].ansr=tree[nod*2+1].qr;			
    }
}
void build(int nod,int l,int r)
{
    if(l==r)
    {
        tree[nod]=(node){a[l],a[l],a[l],a[l],l,r,l,r};
        return;
    }
    build(nod*2,l,mid);
    build(nod*2+1,mid+1,r);
    pushup(nod,l,r);
}
void change(int nod,int l,int r,int x,int y)
{
    if(l==r)
    {
        tree[nod]=(node){y,y,y,y,l,r,l,r};
        return;
    }
    if(x<=mid)change(nod*2,l,mid,x,y);
    else change(nod*2+1,mid+1,r,x,y);
    pushup(nod,l,r);
}
node find(int nod,int l,int r,int L,int R)
{
    if(l==L&&r==R)return tree[nod];
    if(R<=mid)return find(nod*2,l,mid,L,R);
    else if(L>mid)return find(nod*2+1,mid+1,r,L,R);
    node x=find(nod*2,l,mid,L,mid),y=find(nod*2+1,mid+1,r,mid+1,R),res;
    res.sum=x.sum+y.sum;
    if(x.sum+y.l>x.l)
    {
        res.l=x.sum+y.l;
        res.qr=y.qr;
    }
    else{
        res.l=x.l;
        res.qr=x.qr;
    }
    if(y.sum+x.r>y.r)
    {
        res.r=y.sum+x.r;
        res.ql=x.ql;
    }
    else{
        res.r=y.r;
        res.ql=y.ql;
    }
    res.ans=x.ans;
    res.ansl=x.ansl;
    res.ansr=x.ansr;
    if(y.ans>res.ans)
    {
        res.ans=y.ans;
        res.ansl=y.ansl;
        res.ansr=y.ansr;	
    }
    if(x.r+y.l>res.ans)
    {
        res.ans=x.r+y.l;
        res.ansl=x.ql;
        res.ansr=y.qr;			
    }
    return res;
}

void pushup2(int nod,int l,int r)
{
    tree2[nod].sum=tree2[nod*2].sum+tree2[nod*2+1].sum;
    if(tree2[nod*2].sum+tree2[nod*2+1].l>tree2[nod*2].l)
    {
        tree2[nod].l=tree2[nod*2].sum+tree2[nod*2+1].l;
        tree2[nod].qr=tree2[nod*2+1].qr;
    }
    else{
        tree2[nod].l=tree2[nod*2].l;
        tree2[nod].qr=tree2[nod*2].qr;
    }
    if(tree2[nod*2+1].sum+tree2[nod*2].r>tree2[nod*2+1].r)
    {
        tree2[nod].r=tree2[nod*2+1].sum+tree2[nod*2].r;
        tree2[nod].ql=tree2[nod*2].ql;
    }
    else{
        tree2[nod].r=tree2[nod*2+1].r;
        tree2[nod].ql=tree2[nod*2+1].ql;
    }
    tree2[nod].ans=tree2[nod*2].ans;
    tree2[nod].ansl=tree2[nod*2].ansl;
    tree2[nod].ansr=tree2[nod*2].ansr;
    if(tree2[nod*2+1].ans>tree2[nod].ans)
    {
        tree2[nod].ans=tree2[nod*2+1].ans;
        tree2[nod].ansl=tree2[nod*2+1].ansl;
        tree2[nod].ansr=tree2[nod*2+1].ansr;	
    }
    if(tree2[nod*2].r+tree2[nod*2+1].l>tree2[nod].ans)
    {
        tree2[nod].ans=tree2[nod*2].r+tree2[nod*2+1].l;
        tree2[nod].ansl=tree2[nod*2].ql;
        tree2[nod].ansr=tree2[nod*2+1].qr;			
    }
}
void build2(int nod,int l,int r)
{
    if(l==r)
    {
        tree2[nod]=(node){-a[l],-a[l],-a[l],-a[l],l,r,l,r};
        return;
    }
    build2(nod*2,l,mid);
    build2(nod*2+1,mid+1,r);
    pushup2(nod,l,r);
}
void change2(int nod,int l,int r,int x,int y)
{
    if(l==r)
    {
        tree2[nod]=(node){-y,-y,-y,-y,l,r,l,r};
        return;
    }
    if(x<=mid)change2(nod*2,l,mid,x,y);
    else change2(nod*2+1,mid+1,r,x,y);
    pushup2(nod,l,r);
}
node find2(int nod,int l,int r,int L,int R)
{
    if(l==L&&r==R)return tree2[nod];
    if(R<=mid)return find2(nod*2,l,mid,L,R);
    else if(L>mid)return find2(nod*2+1,mid+1,r,L,R);
    node x=find2(nod*2,l,mid,L,mid),y=find2(nod*2+1,mid+1,r,mid+1,R),res;
    res.sum=x.sum+y.sum;
    if(x.sum+y.l>x.l)
    {
        res.l=x.sum+y.l;
        res.qr=y.qr;
    }
    else{
        res.l=x.l;
        res.qr=x.qr;
    }
    if(y.sum+x.r>y.r)
    {
        res.r=y.sum+x.r;
        res.ql=x.ql;
    }
    else{
        res.r=y.r;
        res.ql=y.ql;
    }
    res.ans=x.ans;
    res.ansl=x.ansl;
    res.ansr=x.ansr;
    if(y.ans>res.ans)
    {
        res.ans=y.ans;
        res.ansl=y.ansl;
        res.ansr=y.ansr;	
    }
    if(x.r+y.l>res.ans)
    {
        res.ans=x.r+y.l;
        res.ansl=x.ql;
        res.ansr=y.qr;			
    }
    return res;
}
signed main()
{
// 	freopen("easy.in","r",stdin);
// 	freopen("easy.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    build(1,1,n);
    build2(1,1,n);
    m=read();
    for(int i=1;i<=m;i++)
    {
        int opt=read();
        if(opt==0)
        {
            int x=read(),y=read();
            a[x]=y;
            change(1,1,n,x,y);
            change2(1,1,n,x,y);
        }
        else{
            int l=read(),r=read(),k=read(),ma=0;
            priority_queue<Node>q;
            node xu=find(1,1,n,l,r);
            q.push((Node){xu.ans,l,r,xu.ansl,xu.ansr,1});
            for(int i=1;i<=k;i++)
            {
                Node u=q.top();q.pop();
                if(u.val<0)break;
                ma+=u.val;
                if(u.opt==1)
                {
                    node xu=find2(1,1,n,u.ql,u.qr);
                    if(xu.ans>0)
                    {
                        q.push((Node){xu.ans,u.ql,u.qr,xu.ansl,xu.ansr,0});
                    }
                    if(u.ql>u.l)
                    {
                        node xu=find(1,1,n,u.l,u.ql-1);
                        if(xu.ans>0)
                        {
                            q.push((Node){xu.ans,u.l,u.ql-1,xu.ansl,xu.ansr,1});
                        }
                    }
                    if(u.qr<u.r)
                    {
                        node xu=find(1,1,n,u.qr+1,u.r);
                        if(xu.ans>0)
                        {
                            q.push((Node){xu.ans,u.qr+1,u.r,xu.ansl,xu.ansr,1});
                        }
                    }
                }
                else{
                    node xu=find(1,1,n,u.ql,u.qr);
                    if(xu.ans>0)
                    {
                        q.push((Node){xu.ans,u.ql,u.qr,xu.ansl,xu.ansr,1});
                    }
                    if(u.ql>u.l)
                    {
                        node xu=find2(1,1,n,u.l,u.ql-1);
                        if(xu.ans>0)
                        {
                            q.push((Node){xu.ans,u.l,u.ql-1,xu.ansl,xu.ansr,0});
                        }
                    }
                    if(u.qr<u.r)
                    {
                        node xu=find2(1,1,n,u.qr+1,u.r);
                        if(xu.ans>0)
                        {
                            q.push((Node){xu.ans,u.qr+1,u.r,xu.ansl,xu.ansr,0});
                        }
                    }		
                }
                if(q.empty())break;
            }
            write(ma);
            putchar('\n');
        }
    }
    return 0;
}
/*
15
-4 8 -3 -10 10 4 -7 -7 0 -6 3 8 -10 7 2
1
1 3 9 2
*/
```


---

## 作者：MyukiyoMekya (赞：4)

怎么做相信大家都会（可以看其他题解），这里提供一种更好写的实现方法：

这题比较恶心的是区间乘上 $-1$，我们可以考虑维护两颗 `fhq-treap`，一棵是正的一棵是负的，然后分别维护最大子段和信息，然后区间乘上 $-1$ 的时候直接把两棵树的区间 `split` 出来交换后 `merge` 回去就好了，超级好写。

```cpp
// This code wrote by chtholly_micromaker(Myukiyomekya)
#include <bits/stdc++.h>
#define int long long 
#define ALL(x) (x).begin(),(x).end()
#define ln putchar('\n')
#define pb push_back
#define MP std::make_pair
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef std::pair<int,int> pii;
template <class t> inline void read(t &s){s=0;
signed f=1;char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();;s*=f;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
static int buf[50],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');}
template <class t>inline bool ckmax(t&x,t y){if(x<y){x=y;return 1;}return 0;}
const int MaxN=2e5+50;
const int inf=1e18L+114514;
struct Node
{
	int ans,sum,lmx,rmx,vl,vr,dl,dr;
	Node(){ans=sum=lmx=rmx=-inf;}
	Node(int x,int y){sum=ans=lmx=rmx=y,vl=vr=dl=dr=x;}
	inline Node operator + (const Node &nt) const
	{
		if(ans==-inf)return nt;
		if(nt.ans==-inf)return *this;
		Node ret;ret.sum=sum+nt.sum;
		ret.ans=ans,ret.vl=vl,ret.vr=vr;
		if(ckmax(ret.ans,nt.ans))ret.vl=nt.vl,ret.vr=nt.vr;
		ret.lmx=lmx,ret.dl=dl;
		if(ckmax(ret.lmx,sum+nt.lmx))ret.dl=nt.dl;
		ret.rmx=nt.rmx,ret.dr=nt.dr;
		if(ckmax(ret.rmx,nt.sum+rmx))ret.dr=dr;
		if(ckmax(ret.ans,rmx+nt.lmx))ret.vl=dr,ret.vr=nt.dl;
		return ret;
	}
}v[MaxN],s[MaxN];
#define lson ch[u][0]
#define rson ch[u][1]
std::mt19937 rnd(time(0));
int ch[MaxN][2],siz[MaxN],A[MaxN],ndn,rt1,rt2;
inline void pushup(int u)
{s[u]=s[lson]+v[u]+s[rson],siz[u]=siz[lson]+siz[rson]+1;}
inline void split(int u,int &x,int &y,int k)
{
	if(!u)return x=y=0,void();
	if(k>siz[lson])x=u,split(rson,rson,y,k-siz[lson]-1);
	else y=u,split(lson,x,lson,k);
	pushup(u);
}
inline int merge(int u,int v)
{
	if(!u||!v)return u|v;
	if(rnd()%(siz[u]+siz[v])<siz[u])return rson=merge(rson,v),pushup(u),u;
	return ch[v][0]=merge(u,ch[v][0]),pushup(v),v;
}
inline void Swap(int &rt1,int &rt2,int x,int y)
{
	int l1,mid1,r1,l2,mid2,r2;
	split(rt1,mid1,r1,y),split(mid1,l1,mid1,x-1);
	split(rt2,mid2,r2,y),split(mid2,l2,mid2,x-1);
	rt1=merge(merge(l1,mid2),r1),rt2=merge(merge(l2,mid1),r2);
}
inline void upd(int x,int y)
{
	int l,mid,r;
	split(rt1,mid,r,x+1),split(mid,l,mid,x);
	v[mid]=Node(x,y),pushup(mid),rt1=merge(merge(l,mid),r);
	split(rt2,mid,r,x+1),split(mid,l,mid,x);
	v[mid]=Node(x,-y),pushup(mid),rt2=merge(merge(l,mid),r);
}
inline int buildtr(int l,int r)
{
	if(l>r)return 0;
	int u=++ndn,mid=(l+r)>>1;v[u]=Node(mid,A[mid]),pushup(u);
	return lson=buildtr(l,mid-1),rson=buildtr(mid+1,r),pushup(u),u;
}
signed main(void)
{
	int n;read(n);
	rep(i,1,n)read(A[i]);
	rt1=buildtr(0,n+1);
	rep(i,1,n)A[i]=-A[i];
	rt2=buildtr(0,n+1);
	int opt,x,y,z,q;read(q);
	while(q--)
	{
		read(opt,x,y);
		if(!opt)upd(x,y);
		else
		{
			int l1,mid1,r1,l2,mid2,r2;
			split(rt1,mid1,r1,y+1),split(mid1,l1,mid1,x);
			split(rt2,mid2,r2,y+1),split(mid2,l2,mid2,x);
			read(z);
			int ret=0;
			std::vector<pii > dr;
			while(z--&&s[mid1].ans>0)
			{
				int l=s[mid1].vl-x+1,r=s[mid1].vr-x+1;
				ret+=s[mid1].ans;
				dr.pb(MP(l,r)),Swap(mid1,mid2,l,r);
			}
			write(ret),ln;
			std::reverse(ALL(dr));
			for(auto i:dr)Swap(mid1,mid2,i.first,i.second);
			rt1=merge(merge(l1,mid1),r1);
			rt2=merge(merge(l2,mid2),r2);
		}
	}
	return 0;
}


```



---

## 作者：tommymio (赞：4)

这题有两个切入点：

- 经典的网络流模型

- 反悔贪心

但我们最终会发现这两个切入点殊途同归。

对于经典的网络流模型，我们想到取不超过 $k$ 个子段，这一限制是流量的限制，而总和最大，则是令费用最大，所以建图跑最大费用最大流。$\forall i$，从 $S\to i$ 连一条流量为 $1$，费用为 $0$ 的边，从 $i\to i+1$ 连一条流量为 $0$，费用为 $a_i$ 的边，从 $i\to T$ 连一条流量为 $1$，费用为 $0$ 的边。将 $S$ 的初始流量设为 $k$。这样很明显会 $\text{TLE}$。于是考虑模拟费用流。我们观察到每次增广出的一条路径 $S\to L\to R\to T$，都是在序列上取 $[L,R-1]$ 这一段，然后将这一段在网络上建对应的反向弧。事实上就是取出当前的最大子段和，然后将这一段 $\times -1$。

而反悔贪心，则是先考虑取当前最优，然后将取过的 $\times -1$，如果后续取到了这些 $\times -1$ 的点则意味着我们反悔了，不再取这些点。通过设置了一个反悔的操作，以确保贪心的正确性。

为什么这两个切入点的最终解决方案都是一样的呢？原来是因为网络流求解最大费用最大流时，本质遵循的就是一个反悔贪心策略：取当前增广路，并将增广过的边建反向弧。这也就揭示了，模拟网络流与反悔贪心的一些共通之处。

那么我们需要实现一个数据结构，支持区间取反，单点修改，区间最大子段和，维护区间最大子段和，区间最小子段和的对应信息即可。注意下放标记。

最后线段树的实现反倒没有那么重要，大力码代码就是了，反正也就才 $\text{180}$ 行是吧（光速逃

$\text{tips}$：墙裂推荐写码农题时使用带代码补全的编辑器，像 $\text{VSCode}$ 之类的。变量名一定要想好，缺乏想象力会导致你没有足够的变量名来描述结构体中多达至少 $14$ 个量（划掉

```cpp
/*
Editor:VSCode- for more quickly coding.
Writer:tommy0103
Motto:Karry5307 yyds!
*/
#include<cstdio>
#include<functional>
#define ls p<<1
#define rs p<<1|1
typedef long long ll;
int a[100005];
std::pair<int,int> st[35];
struct Segment {
    int rev,sum,l,r;
    int maxLen,maxLval,maxRval,maxL,maxR,maxLenL,maxLenR;
    int minLen,minLval,minRval,minL,minR,minLenL,minLenR;
}t[400005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline void swap(int &x,int &y) {int tmp=x;x=y;y=tmp;}
inline void work(Segment &x,int v1,int v2) {//v1=pos,v2=val
    x.sum=v2; x.rev=0;
    x.maxLen=x.maxLval=x.maxRval=v2;
    x.maxL=x.maxR=x.maxLenL=x.maxLenR=v1;
    x.minLen=x.minLval=x.minRval=v2;
    x.minL=x.minR=x.minLenL=x.minLenR=v1;
}
inline void work(Segment &x) {
    x.sum*=-1;
    swap(x.maxLen,x.minLen); x.minLen*=-1; x.maxLen*=-1;
    swap(x.maxLval,x.minLval); x.maxLval*=-1; x.minLval*=-1;
    swap(x.maxRval,x.minRval); x.maxRval*=-1; x.minRval*=-1;
    swap(x.maxL,x.minL); swap(x.maxR,x.minR);
    swap(x.maxLenL,x.minLenL); swap(x.maxLenR,x.minLenR);
}
inline void spread(int p) {
    if(t[p].rev) {
        t[ls].rev^=1; work(t[ls]);
        t[rs].rev^=1; work(t[rs]);
        t[p].rev=0;
    }
}
inline Segment merge(const Segment &x,const Segment &y) {
    Segment res=(Segment){0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int l=x.l,r=y.r; res.sum=x.sum+y.sum; res.l=l; res.r=r;
    if(x.maxLval<y.maxLval+x.sum) {
        res.maxLval=y.maxLval+x.sum;
        res.maxL=y.maxL; 
    }
    else {
        res.maxLval=x.maxLval;
        res.maxL=x.maxL;
    }
    if(y.maxRval<x.maxRval+y.sum) {
        res.maxRval=x.maxRval+y.sum;
        res.maxR=x.maxR;
    }
    else {
        res.maxRval=y.maxRval;
        res.maxR=y.maxR;
    }

    if(x.maxLen>y.maxLen) {
        res.maxLen=x.maxLen;
        res.maxLenL=x.maxLenL;
        res.maxLenR=x.maxLenR;
    }
    else {
        res.maxLen=y.maxLen;
        res.maxLenL=y.maxLenL;
        res.maxLenR=y.maxLenR;
    }
    if(x.maxRval+y.maxLval>res.maxLen) {
        res.maxLen=x.maxRval+y.maxLval;
        res.maxLenL=x.maxR; 
        res.maxLenR=y.maxL;
    }
    if(res.maxRval>res.maxLen) {
        res.maxLen=res.maxRval;
        res.maxLenL=res.maxR;
        res.maxLenR=r;
    }
    if(res.maxLval>res.maxLen) {
        res.maxLen=res.maxLval;
        res.maxLenL=l;
        res.maxLenR=res.maxL;
    }

    if(x.minLval>y.minLval+x.sum) {
        res.minLval=y.minLval+x.sum;
        res.minL=y.minL; 
    }
    else {
        res.minLval=x.minLval;
        res.minL=x.minL;
    }
    if(y.minRval>x.minRval+y.sum) {
        res.minRval=x.minRval+y.sum;
        res.minR=x.minR;
    }
    else {
        res.minRval=y.minRval;
        res.minR=y.minR;
    }

    if(x.minLen<y.minLen) {
        res.minLen=x.minLen;
        res.minLenL=x.minLenL;
        res.minLenR=x.minLenR;
    }
    else {
        res.minLen=y.minLen;
        res.minLenL=y.minLenL;
        res.minLenR=y.minLenR;
    }
    if(x.minRval+y.minLval<res.minLen) {
        res.minLen=x.minRval+y.minLval;
        res.minLenL=x.minR; 
        res.minLenR=y.minL;
    }
    if(res.minRval<res.minLen) {
        res.minLen=res.minRval;
        res.minLenL=res.minR;
        res.minLenR=r;
    }
    if(res.minLval<res.minLen) {
        res.minLen=res.minLval;
        res.minLenL=l;
        res.minLenR=res.minL;
    }
    return res;
}
inline void pushup(int p) {t[p]=merge(t[ls],t[rs]);}
inline void build(int p,int l,int r) {
    t[p].l=l; t[p].r=r;
    if(l==r) {work(t[p],l,a[l]); return;}
    int mid=l+r>>1; build(ls,l,mid); build(rs,mid+1,r);
    pushup(p);
}
inline void change_cov(int p,int l,int r,int x,int val) {
    if(l==r) {work(t[p],l,val); return;}
    int mid=l+r>>1; spread(p);
    if(x<=mid) change_cov(ls,l,mid,x,val);
    else change_cov(rs,mid+1,r,x,val);
    pushup(p);
}
inline void change_rev(int p,int l,int r,int L,int R) {
    if(L<=l&&r<=R) {t[p].rev^=1; work(t[p]); return;}
    int mid=l+r>>1; spread(p);
    if(L<=mid) change_rev(ls,l,mid,L,R);
    if(R>mid) change_rev(rs,mid+1,r,L,R);
    pushup(p);
} 
inline Segment ask(int p,int l,int r,int L,int R) {
    if(L<=l&&r<=R) return t[p];
    int mid=l+r>>1; spread(p);
    if(L>mid) return ask(rs,mid+1,r,L,R);
    if(R<=mid) return ask(ls,l,mid,L,R);
    return merge(ask(ls,l,mid,L,mid),ask(rs,mid+1,r,mid+1,R));//L<=mid&&R>mid
}
int main() {
    int n=read();
    for(register int i=1;i<=n;++i) a[i]=read();
    build(1,1,n); int Q=read();
    while(Q--) {
        int op=read();
        if(op==0) {int x=read(),val=read();change_cov(1,1,n,x,val);}
        else {
            int l=read(),r=read(),k=read(),top=0; ll ans=0;
            for(register int round=1;round<=k;++round) {
                Segment res=ask(1,1,n,l,r); if(res.maxLen<=0) break; ans+=res.maxLen;  
                change_rev(1,1,n,res.maxLenL,res.maxLenR); 
                st[++top]=std::make_pair(res.maxLenL,res.maxLenR);
            }
            while(top) {change_rev(1,1,n,st[top].first,st[top].second); --top;}
            printf("%lld\n",ans);
        }
    }
    return 0;
}
```

---

## 作者：bradfordzhang (赞：4)

# 题目大概的意思
> 给一列数，要求支持操作： 
>
> 1.修改某个数的值 
>
> 2.读入l,r,k，询问在[l,r]内选不相交的不超过k个子段，最大的和是多少。

# 解法
我是求最大字段和，再用上线段树维护。

有两种情况：

1. 求最大字段和 
1. ①求最大字段和+另一部分的第二大的字段和

	② 最大字段和-最大字段和里面的最大字段和

# 上代码
PS:管理大大，namespace是快读和typedef，不要认为是预处理啊QwQ

```cpp
//#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>

namespace tydef {
	typedef double db;
	typedef long long LL;
	typedef unsigned long long ULL;
}

namespace io {//快读
#define gc() (iS == iT ? (iT = (iS = ibuff) + fread(ibuff, 1, SIZ, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
	const int SIZ = 1 << 21 | 1;
	char* iS, * iT, ibuff[SIZ], obuff[SIZ], * oS = obuff, * oT = oS + SIZ - 1, fu[110], c;
	int fr;
	inline void out() {
		fwrite(obuff, 1, oS - obuff, stdout);
		oS = obuff;
	}
	template<class Type>
	inline void read(Type& x) {
		x = 0;
		Type y = 1;
		for (c = gc(); (c > '9' || c < '0') && c != '-'; c = gc());
		c == '-' ? y = -1 : x = (c & 15);
		for (c = gc(); c >= '0' && c <= '9'; c = gc())
			x = x * 10 + (c & 15);
		x *= y;
	}
}

using namespace tydef;
using namespace io;
using namespace std;

//为了方便，把for写到define里了
#define rep(q,a,b) for(int q=a,q##_end_=b;q<=q##_end_;++q)
#define dep(q,a,b) for(int q=a,q##_end_=b;q>=q##_end_;--q)
#define mem(a,b) memset(a,b,sizeof a )

const int mn = 100005;
int val[mn];
bool mark[mn << 2];
struct node {
	int Max_l, l, Max_r, r, Max, L, R, Sum;
}Mx[mn << 2];
node meg(node l, node r) {
	node now = { l.Max_l,l.l,r.Max_r,r.r };
	if (l.Max > r.Max)now.Max = l.Max, now.L = l.L, now.R = l.R;
	else now.Max = r.Max, now.L = r.L, now.R = r.R;
	if (l.Sum + r.Max_l > now.Max_l) {
		now.Max_l = l.Sum + r.Max_l;
		now.l = r.l;
	}
	if (r.Sum + l.Max_r > now.Max_r) {
		now.Max_r = r.Sum + l.Max_r;
		now.r = l.r;
	}
	if (l.Max_r + r.Max_l > now.Max) {
		now.Max = l.Max_r + r.Max_l;
		now.L = l.r, now.R = r.l;
	}
	now.Sum = l.Sum + r.Sum;
	return now;
}
//线段树的一系列操作
struct node1 {
	int Min_l, l, Min_r, r, Min, L, R, Sum;
}Mi[mn << 2];
node res(node1 a) {
	return { -a.Min_l,a.l,-a.Min_r,a.r,-a.Min,a.L,a.R,-a.Sum };
}
node1 res(node a) {
	return { -a.Max_l,a.l,-a.Max_r,a.r,-a.Max,a.L,a.R,-a.Sum };
}

void max_up(int o) {
	node l = mark[o << 1] ? res(Mi[o << 1]) : Mx[o << 1];
	node r = mark[o << 1 | 1] ? res(Mi[o << 1 | 1]) : Mx[o << 1 | 1];
	Mx[o] = meg(l, r);
}
node1 meg(node1 l, node1 r) {
	node1 now = { l.Min_l,l.l,r.Min_r,r.r };
	if (l.Min < r.Min)now.Min = l.Min, now.L = l.L, now.R = l.R;
	else now.Min = r.Min, now.L = r.L, now.R = r.R;
	if (l.Sum + r.Min_l < now.Min_l) {
		now.Min_l = r.Min_l + l.Sum;
		now.l = r.l;
	}
	if (r.Sum + l.Min_r < now.Min_r) {
		now.Min_r = l.Min_r + r.Sum;
		now.r = l.r;
	}
	if (r.Min_l + l.Min_r < now.Min) {
		now.Min = l.Min_r + r.Min_l;
		now.L = l.r, now.R = r.l;
	}
	now.Sum = l.Sum + r.Sum;
	return now;
}
void min_up(int o) {
	node1 l = mark[o << 1] ? res(Mx[o << 1]) : Mi[o << 1];
	node1 r = mark[o << 1 | 1] ? res(Mx[o << 1 | 1]) : Mi[o << 1 | 1];
	Mi[o] = meg(l, r);
}
void up(int o) {
	min_up(o);
	max_up(o);
}
void build(int o, int l, int r) {
	if (l == r) {
		Mx[o] = { val[l],l,val[l],l,val[l],l,l,val[l] };
		Mi[o] = { val[l],l,val[l],l,val[l],l,l,val[l] };
		return;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	up(o);
}

int y_1, y_2, ad_v;
void change(int o, int l, int r) {
	if (l == r) {
		Mx[o] = { ad_v,l,ad_v,l,ad_v,l,l,ad_v };
		Mi[o] = { ad_v,l,ad_v,l,ad_v,l,l,ad_v };
		return;
	}
	int mid = l + r >> 1;
	if (y_1 <= mid)change(o << 1, l, mid);
	else change(o << 1 | 1, mid + 1, r);
	up(o);
}
void Mark(int o, int l, int r) {
	if (y_1 <= l && r <= y_2)mark[o] ^= 1;
	else {
		int mid = l + r >> 1;
		if (y_1 <= mid)Mark(o << 1, l, mid);
		if (y_2 > mid)Mark(o << 1 | 1, mid + 1, r);
		up(o);
	}
}
node query(int o, int l, int r, bool mk) {
	mk ^= mark[o];
	if (y_1 <= l && r <= y_2)return mk ? res(Mi[o]) : Mx[o];
	else {
		int mid = l + r >> 1;
		if (y_2 <= mid)return query(o << 1, l, mid, mk);
		if (y_1 > mid)return query(o << 1 | 1, mid + 1, r, mk);
		return meg(query(o << 1, l, mid, mk), query(o << 1 | 1, mid + 1, r, mk));
	}
}
int n, m;
void change(int x, int k) {
	y_1 = x, ad_v = k;
	change(1, 1, n);
}


pair<int, int> que[100];
int ask(int l, int r, int k) {
	int td = 0, ans = 0;
	while (k--) {
		y_1 = l, y_2 = r;
		node now = query(1, 1, n, 0);
		if (now.Max < 0)break;
		ans += now.Max;
		y_1 = now.L, y_2 = now.R;
		Mark(1, 1, n);
		que[++td] = { now.L,now.R };
	}
	dep(q, td, 1) {
		y_1 = que[q].first, y_2 = que[q].second;
		Mark(1, 1, n);
	}
	return ans;
}
int main() {
	read(n);
	rep(q, 1, n) read(val[q]);
	build(1, 1, n);
	read(m);
	int ty, l, r, k;
	while (m--) {
		read(ty);
		if (!ty) {
			read(l), read(k);
			change(l, k);
		}
		else {
			read(l), read(r), read(k);
			printf("%d\n", ask(l, r, k));
		}
	}
	return 0;
}
```

---

## 作者：徐致远 (赞：4)

[本蒟蒻的Blog](https://www.chnxuzhiyuan.cn/2019/07/10/%E3%80%8CCF280D%E3%80%8Dk-Maximum-Subsequence-Sum-Solution/)

### 题解

首先可以考虑一个贪心，每次取询问区间内权值和最大的子段，然后把这个子段标记上，该次询问中不能再取。

但是这个想法并不对，比如序列$3,-1,3$，可以取至多2个子段。由于第一次会取权值最大的子段$[1,3]$，然后就没有子段可以取了。而实际上取$[1,1]$和$[3,3]$的话答案会更优。

然后不难联想到，在求最大流的时候，我们通过建反向弧的方式来保证了正确性。

所以对于这题，可以在取了一个子段之后，将改子段取反，之后还能再取，来保证正确性。

而取反和取最大值的操作都可以通过线段树来维护。

时间复杂度$O(n\log n+mk\log n)$。

### 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100005;
int n,Q,A[maxn];
inline int read()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
struct Range
{
	int L,R,Sum;
	inline bool operator < (const Range& b)const{return Sum<b.Sum;}
	inline Range operator + (const Range& b)const{return (Range){L,b.R,Sum+b.Sum};}
}Ra[25];
struct SegmentTree
{
	struct Node{Range Lmax,Rmax,Max,Lmin,Rmin,Min,All;bool Tag;}Tree[maxn*4];
	inline void Merge(Node& a,Node b,Node c)
	{
		a.All=b.All+c.All;
		a.Lmin=min(b.Lmin,b.All+c.Lmin);a.Rmin=min(c.Rmin,b.Rmin+c.All);
		a.Lmax=max(b.Lmax,b.All+c.Lmax);a.Rmax=max(c.Rmax,b.Rmax+c.All);
		a.Max=max(max(b.Max,c.Max),b.Rmax+c.Lmax);a.Min=min(min(b.Min,c.Min),b.Rmin+c.Lmin);
	}
	inline void PushUp(int rt){Merge(Tree[rt],Tree[rt*2],Tree[rt*2+1]);}
	inline void Reverse(int rt)
	{
		Tree[rt].Lmin.Sum*=-1;Tree[rt].Lmax.Sum*=-1;
		Tree[rt].Rmin.Sum*=-1;Tree[rt].Rmax.Sum*=-1;
		Tree[rt].Min.Sum*=-1;Tree[rt].Max.Sum*=-1;Tree[rt].All.Sum*=-1;
		swap(Tree[rt].Min,Tree[rt].Max);swap(Tree[rt].Lmax,Tree[rt].Lmin);swap(Tree[rt].Rmax,Tree[rt].Rmin);
	}
	inline void PushDown(int rt)
	{
		if(Tree[rt].Tag)
		{
			Reverse(rt*2);Reverse(rt*2+1);
			Tree[rt*2].Tag^=1;Tree[rt*2+1].Tag^=1;Tree[rt].Tag^=1;
		}
	}
	inline void Build(int L=1,int R=n,int rt=1)
	{ 
		if(L==R){Tree[rt].All=Tree[rt].Lmax=Tree[rt].Lmin=Tree[rt].Max=Tree[rt].Min=Tree[rt].Rmax=Tree[rt].Rmin=(Range){L,R,A[L]};return;}
		int M=(L+R)>>1;
		Build(L,M,rt*2);
		Build(M+1,R,rt*2+1);
		PushUp(rt);
	}
	inline void UpdatePoint(int P,int V,int L=1,int R=n,int rt=1)
	{
		if(L==R){Tree[rt].All.Sum=Tree[rt].Lmax.Sum=Tree[rt].Lmin.Sum=Tree[rt].Max.Sum=Tree[rt].Min.Sum=Tree[rt].Rmax.Sum=Tree[rt].Rmin.Sum=V;return;}
		int M=(L+R)>>1;PushDown(rt);
		if(P<=M) UpdatePoint(P,V,L,M,rt*2);
		if(M<P) UpdatePoint(P,V,M+1,R,rt*2+1);
		PushUp(rt);
	}
	inline Node QueryMax(int LL,int RR,int L=1,int R=n,int rt=1)
	{
		if(LL<=L&&R<=RR) return Tree[rt];
		int M=(L+R)>>1;Node ret;PushDown(rt);
		if(LL<=M) ret=QueryMax(LL,RR,L,M,rt*2);
		if(M<RR)
		{
			if(LL>M) ret=QueryMax(LL,RR,M+1,R,rt*2+1);
			else Merge(ret,ret,QueryMax(LL,RR,M+1,R,rt*2+1));
		}
		return ret;
	}
	inline void UpdateRange(int LL,int RR,int L=1,int R=n,int rt=1)
	{
		if(LL<=L&&R<=RR){Reverse(rt);Tree[rt].Tag^=1;return;}
		int M=(L+R)>>1;PushDown(rt);
		if(LL<=M) UpdateRange(LL,RR,L,M,rt*2);
		if(M<RR) UpdateRange(LL,RR,M+1,R,rt*2+1);
		PushUp(rt);
	}
}S;
int main()
{
	n=read();
	for(int i=1;i<=n;i++) A[i]=read();
	Q=read();S.Build();
	while(Q--)
	{
		if(read()==0)
		{
			int P=read(),V=read();
			S.UpdatePoint(P,V);
		}
		else
		{
			int L=read(),R=read(),K=read(),cnt,ans=0;
			for(cnt=0;cnt<K;cnt++)
			{
				SegmentTree::Node tep=S.QueryMax(L,R);
				if(tep.Max.Sum<=0) break;
				ans+=tep.Max.Sum;
				S.UpdateRange(tep.Max.L,tep.Max.R);
				Ra[cnt]=tep.Max;
			}
			for(int i=0;i<cnt;i++)
				S.UpdateRange(Ra[i].L,Ra[i].R);
			printf("%d\n",ans);
		}
	}
	return 0;
}
```



---

## 作者：yummy (赞：3)

~~这哪有黑啊~~

考虑到本题已经有诸多题解，我主要讲讲实现，希望对大家 NOIP 备考有所帮助，让大家考场上更快地写出准确的代码，并能更快地调试。

## 数据组织

维护区间最大子段和，经典做法是开一棵线段树，维护区间前缀和、区间后缀和、区间最大子段和、区间总和。但是这题我们还需要知道这些和来自哪里。

我们注意到，每个数的来源和值总是捆绑在一起的，因此我们可以写一个 `struct`。同时，由于我们有区间取相反数操作，我们还要维护另一个 `struct`。

我们发现这构成了两级 `struct`。我们写某一级 `struct` 时总是希望上一级 `struct` 已经封装完成，可以方便地调用各类函数。

## 类型检查

有的时候，我们会不自觉地写错一些东西，例如将区间前缀和和另一侧区间前缀和相加，或者区间前缀和和区间后缀和求 `max` 等。为了避免这种问题，我直接将前缀和与后缀和定义为两种不同的结构体，就可以自动完成类型检查。

实际上我的代码有一处不太好的地方——`Rmax` 和 `Rmin` 使用 `auto` 作参数，这导致我后来有一次将两个 `node` 求 `Rmax`（`node` 的合并应写成 `+`）了我却没发现。

更好的写法应该是 `template<typename T> T Rmax(T x,T y)`，然后手动把 `node` 析构掉，或者 `node` 的全局和换个名字。

## 部分输出

如果要输出整棵线段树，哪怕是题目给的小样例，由于每个结点要存储 $15$ 个数，对应的输出也是相当巨大，不方便调试的。

**再次提醒：你觉得容易错的地方，可能还真不是你错的地方。**

当我们发现 RE 或 WA 时，我们可以**先检查好检查的**，再深入程序内部检查各个部分是否符合预期。例如，对于本题，你对于询问 2 WA 可以考虑如下步骤：
- 先观察每一步求出的最大子段和及来源是否正确。
- 观察合并是否正确。
- 对于每次递归，观察 lazytag 和根，可以粗查上一次取相反数是否正确。
- 确认 lazytag 下放正确。

注意，如果你第一次求最大子段和就错，你输出时只要输出最大和，并不用管最小以及最大和的来源，因为它们不影响你第一次求最大子段和。其他情况同理。

## 参考实现

3KB，在本题代码中算中等偏短。

```cpp
#include<bits/stdc++.h>
using namespace std;
int occupy(int n){int y=1;for(n--;n;n>>=1)y<<=1;return y;}
struct lR{long long sum;int l;};//后缀和
struct rR{long long sum;int r;};//前缀和
struct R{long long sum;int l,r;};//最大子段和
lR operator + (lR x,long long y){return {x.sum+y,x.l};}//因为后缀和在一个区间的前面，所以将它写在加号前面。
rR operator + (long long x,rR y){return {x+y.sum,y.r};}//同理，同时这里也可以类型检查。
R  operator + (lR x,rR y){return {x.sum+y.sum,x.l,y.r};}
auto Rmax(auto x,auto y){if(x.sum>y.sum)return x;return y;}//刚提到的一点瑕疵，没有类型检查
auto Rmin(auto x,auto y){if(x.sum<y.sum)return x;return y;}
auto _n(auto x){x.sum=-x.sum;return x;}//区间求反，是内部函数，用下划线
struct node{long long sum;lR lmx,lmn;rR rmx,rmn;R mx,mn;};
node operator - (node x){return {-x.sum,_n(x.lmn),_n(x.lmx),_n(x.rmn),_n(x.rmx),_n(x.mn),_n(x.mx)};}//节点求反
node make_node(int x,int id)
{
	if(x>=0)return {x,{x,id},{0,id+1},{x,id},{0,id-1},{x,id,id},{0,id+1,id-1}};
	return -make_node(-x,id);
}//将实数转化成 node，这里负数我可以直接调用，不重复造轮子
node operator + (node x,node y)//合并两个 node
{
	node res;res.sum=x.sum+y.sum;
	res.lmx=Rmax(x.lmx+y.sum,y.lmx);
	res.lmn=Rmin(x.lmn+y.sum,y.lmn);
	res.rmx=Rmax(x.sum+y.rmx,x.rmx);
	res.rmn=Rmin(x.sum+y.rmn,x.rmn);
	res.mx=Rmax(Rmax(x.mx,y.mx),x.lmx+y.rmx);
	res.mn=Rmin(Rmin(x.mn,y.mn),x.lmn+y.rmn);
	return res;
}
int n,m,rn;
bool rev[262144];
node tr[262144];//因为我一般 lazytag 不写进结构体，因此这里也不写进去
void psdn(int rt)//push_down
{
	rev[rt]=0;
	rev[rt*2]^=1;tr[rt*2]=-tr[rt*2];
	rev[rt*2+1]^=1;tr[rt*2+1]=-tr[rt*2+1];
	tr[rt]=tr[rt*2]+tr[rt*2+1];
}
//全部定义好后，下面的东西和线段树完全一致
node query(int x,int y,int l,int r,int rt)
{
	if(x==l and y==r){return tr[rt];}
	int mid=(l+r)/2;
	node res=make_node(-0x3f3f3f3f,-1);
	if(rev[rt])psdn(rt);
	if(x<=mid)res=query(x,min(y,mid),l,mid,rt*2);
	if(y>mid)res=res+query(max(x,mid+1),y,mid+1,r,rt*2+1);
	return res;
}
void neg(int x,int y,int l,int r,int rt)
{
	if(x==l and y==r){rev[rt]^=1;tr[rt]=-tr[rt];return;}
	int mid=(l+r)/2;
	if(rev[rt])psdn(rt);
	if(x<=mid)neg(x,min(y,mid),l,mid,rt*2);
	if(y>mid)neg(max(x,mid+1),y,mid+1,r,rt*2+1);
	tr[rt]=tr[rt*2]+tr[rt*2+1];
}
void update(int x,int l,int r,int rt,int up)
{
	if(l==r){tr[rt]=make_node(up,x);return;}
	if(rev[rt])psdn(rt);
	int mid=(l+r)/2;
	if(x<=mid)update(x,l,mid,rt*2,up);
	else update(x,mid+1,r,rt*2+1,up);
	tr[rt]=tr[rt*2]+tr[rt*2+1];
}
int main()
{
	scanf("%d",&n);
	rn=occupy(n);
	int op,l,r,k;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&op);
		tr[rn+i]=make_node(op,i+1);
	}
	for(int i=rn-1;i;i--)
	{
		tr[i]=tr[i*2]+tr[i*2+1];
        //因为当时第一个就出错，因此我们只检查 sum，然后发现写成了 tr[i]=Rmax(tr[i*2],tr[i*2+1]);
		//printf("i=%d (%d,%d,%d,%d)\n",i,tr[i].sum,tr[i].lmx.sum,tr[i].rmx.sum,tr[i].mx.sum);
	}
	for(scanf("%d",&m);m;m--)
	{
		scanf("%d",&op);
		if(op==0)
		{
			scanf("%d%d",&l,&k);
			update(l,1,rn,1,k);
		}
		else
		{
			scanf("%d%d%d",&l,&r,&k);
			long long tot=0;
			vector<pair<int,int> > rgs;
			for(int i=1;i<=k;i++)
			{
				R tmp=query(l,r,1,rn,1).mx;
				if(tmp.l<1)tmp.l=1;//样例 2 RE 之后我发现前缀有可能到 0
				if(tmp.r>rn)tmp.r=rn;
				//printf("%d from [%d,%d]\n",tmp.sum,tmp.l,tmp.r);
				if(tmp.sum<=0)break;
				tot+=tmp.sum;
				rgs.push_back({tmp.l,tmp.r});
				neg(tmp.l,tmp.r,1,rn,1);
			}
			printf("%lld\n",tot);
			for(auto i:rgs)
				neg(i.first,i.second,1,rn,1);
		}
	}
	return 0;
}
```

---

## 作者：Mobius127 (赞：3)

[题传](https://www.luogu.com.cn/problem/CF280D)

发现 $k$ 很小，在上面做文章。

如果 $k=1$，那么就是一线段树板子，顺带能资瓷单点修改。

考虑反悔贪心，当我们选了一段极长的段，它不一定是最优的，我们可能不需要其中的一部分，但其本质上是新加的一段选取了这一部分，同时丢掉了某一部分，相当于“借”一段给新的，需要消掉这一部分在原串的贡献，于是想到将选取的一段乘上 -1，再取最大连续段。


那么我们在线段树上只需要维护区间取反的操作，相当于这一整段的大值变小，小值变大，所以再维护一个全局最小子段和，取反时将 最大/最小 的互换即可。

注意每个询问互不影响，所以记得将所有取过的都消回去。~~然后导致码量大幅增加~~

复杂度 $O(nk \log n)$，挺好写的。

### Code：

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cctype>
#include <cmath>
#include <cstdlib>
using namespace std;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)) f=(ch=='-'?-1:f), ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0', ch=getchar();
	return x*f;
}
inline void Swp(int &a, int &b){int t=a;a=b, b=t;return ;}
const int N=1e5+5;
struct node{
	int L, R, sum, tag;
	int lmax, rmax, Mx, Rx, Lx, LXans, RXans;
	int lmin, rmin, Mn, Rn, Ln, LNans, RNans;
	void spread(){
		sum=-sum;tag^=1;
		swap(lmax, lmin), swap(rmax, rmin), swap(Mx, Mn);
		swap(Rx, Rn), swap(Lx, Ln), swap(LXans, LNans), swap(RXans, RNans);
		lmax=-lmax, lmin=-lmin;
		rmax=-rmax, rmin=-rmin;
		Mx=-Mx, Mn=-Mn;
		return ;
	}
}tree[N*4];
node Newnode(int pos, int val){
	return (node){pos, pos, val, 0, val, val, val, pos, pos, pos, pos, val, val, val, pos, pos, pos, pos};
}
node operator + (node A, node B){
	node C;C.sum=A.sum+B.sum, C.L=A.L, C.R=B.R;C.tag=0;
	
	if(A.sum+B.lmax>A.lmax) C.lmax=A.sum+B.lmax, C.Rx=B.Rx;
	else C.lmax=A.lmax, C.Rx=A.Rx;
	if(B.sum+A.rmax>B.rmax) C.rmax=B.sum+A.rmax, C.Lx=A.Lx;
	else C.rmax=B.rmax, C.Lx=B.Lx;
	if(A.sum+B.lmin<A.lmin) C.lmin=A.sum+B.lmin, C.Rn=B.Rn;
	else C.lmin=A.lmin, C.Rn=A.Rn;
	if(B.sum+A.rmin<B.rmin) C.rmin=B.sum+A.rmin, C.Ln=A.Ln;
	else C.rmin=B.rmin, C.Ln=B.Ln;
	
	int Maxi=max(max(max(C.lmax, C.rmax), A.rmax+B.lmax), max(A.Mx, B.Mx));
	if(Maxi==C.lmax) C.LXans=C.L, C.RXans=C.Rx;
	else if(Maxi==C.rmax) C.LXans=C.Lx, C.RXans=C.R;
	else if(Maxi==A.rmax+B.lmax) C.LXans=A.Lx, C.RXans=B.Rx;
	else if(Maxi==A.Mx) C.LXans=A.LXans, C.RXans=A.RXans;
	else if(Maxi==B.Mx) C.LXans=B.LXans, C.RXans=B.RXans;
	C.Mx=Maxi;
	
	int Mini=min(min(min(C.lmin, C.rmin), A.rmin+B.lmin), min(A.Mn, B.Mn));
	if(Mini==C.lmin) C.LNans=C.L, C.RNans=C.Rn;
	else if(Mini==C.rmin) C.LNans=C.Ln, C.RNans=C.R;
	else if(Mini==A.rmin+B.lmin) C.LNans=A.Ln, C.RNans=B.Rn;
	else if(Mini==A.Mn) C.LNans=A.LNans, C.RNans=A.RNans;
	else if(Mini==B.Mn) C.LNans=B.LNans, C.RNans=B.RNans;
	C.Mn=Mini;
	
	return C;
}
int n, m, a[N];
#define ls k<<1
#define rs k<<1|1
#define mid (tree[k].L+tree[k].R>>1)
void pushup(int k){tree[k]=tree[ls]+tree[rs];}
void pushdown(int k){
	if(!tree[k].tag) return ;
	tree[ls].spread(), tree[rs].spread();tree[k].tag=0;
	return ;
}
void build(int k, int l, int r){
	tree[k].L=l, tree[k].R=r, tree[k].tag=0;
	if(l==r){tree[k]=Newnode(l&r, a[l&r]);return;}
	build(ls, l, mid), build(rs, mid+1, r);
	pushup(k);
}
void modify(int k, int x, int v){
	if(tree[k].L==tree[k].R){tree[k]=Newnode(x, v);return ;}pushdown(k);
	if(x<=mid) modify(ls, x, v);
	else modify(rs, x, v);
	return pushup(k);
}
void change(int k, int x, int y){
	if(x<=tree[k].L&&tree[k].R<=y) return tree[k].spread();pushdown(k);
	if(x<=mid) change(ls, x, y);
	if(mid<y) change(rs, x, y);
	return pushup(k);
}
node query(int k, int x, int y){
	if(x<=tree[k].L&&tree[k].R<=y) return tree[k];pushdown(k);
	if(y<=mid) return query(ls, x, y);
	if(x>mid) return query(rs, x, y);
	node Ll=query(ls, x, y);node Rr=query(rs, x, y);
	return Ll+Rr; 
}
#undef ls
#undef rs 
#undef mid
void doit(int dep, int sum, int &res, int x, int y){
	if(!dep) return ;
	node ans=query(1, x, y);
	res=max(res, sum+=ans.Mx);
	change(1, ans.LXans, ans.RXans);
	doit(dep-1, sum, res, x, y);
	change(1, ans.LXans, ans.RXans);
	return ;
}
signed main(){
	n=read();
	for(int i=1; i<=n; i++) a[i]=read();
	build(1, 1, n);
	m=read();
	for(int i=1, opt, x, y, k; i<=m; i++){
		opt=read();
		if(!opt) x=read(), y=read(), modify(1, x, y);
		else{
			x=read(), y=read(), k=read();
			int ans=0;
			doit(k, 0, ans, x, y);
			printf("%d\n", ans);
		}
	}
	return 0;
}
```


---

## 作者：partychicken (赞：3)

# 模拟费用流（线段树维护）

## Part I

先考虑一个费用流做法：

- 原点向每个点连流量为$1$费用为$0$的边

- 每个点向下一个点连流量为点值的边

- 每个点向汇点连流量为$1$费用为$0$的边

然后跑一个流量为$k$的费用流即可。

## Part II

看一眼数据范围。。。what the f\*\*k!!!

费用流TLE至死。于是，我们考虑优化这个过程。

可以发现，每次费用流增广的过程就是找到最长的路径一条路径，然后把答案加上这个值，然后把边反向。

我们又发现这些路径是一条链的形式，于是每次找到的路径就是最大子段和。

用线段树维护数列来模拟这个过程，需要支持的操作有：

- 单点修改

- 区间取相反数

- 询问区间最大子段和

每次对于一个询问，我们查询$k$次最大子段和并将这一段子段取相反数。然后统计所有最大子段和相加的和就是单次询问的答案。

要注意可以不选，所以当最大子段和$s\le0$时就退出。

另外，每次询问需要知道最大子段和对应的具体区间，因此需要维护每个值的$l,r$。

具体实现可以看代码了，自我感觉我的实现挺简洁的。

祝编码愉快。


```
#include<bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;

struct Node
{
    struct Tuple
    {
        int l,r,val;

        Tuple(int val):l(inf),r(-inf),val(val){}
        Tuple(int l,int r,int val):l(l),r(r),val(val){}

        Tuple operator+(const Tuple &other)const
        {
            return Tuple(min(l,other.l),max(r,other.r),val+other.val);
        }

        bool operator<(const Tuple &other)const
        {
            return val<other.val;
        }
    };
    Tuple maxright,maxleft,maxmid;
    Tuple minright,minleft,minmid;
    Tuple sum;
    bool rev;

    Node():
        maxright(-inf),
        maxleft(-inf),
        maxmid(-inf),
        minright(inf),
        minleft(inf),
        minmid(inf),
        sum(0),
        rev(0){}

    Node operator+(const Node &other)const
    {
        Node res;
        
        res.sum=sum+other.sum;

        res.maxright=max(other.maxright,maxright+other.sum);
        res.maxleft=max(maxleft,sum+other.maxleft);
        res.maxmid=max(maxmid,max(other.maxmid,maxright+other.maxleft));

        res.minright=min(other.minright,minright+other.sum);
        res.minleft=min(minleft,sum+other.minleft);
        res.minmid=min(minmid,min(other.minmid,minright+other.minleft));

        return res;
    }
};


struct SEG
{
    Node nd[100010<<2];

    void update(int x)
    {
        nd[x]=nd[x<<1]+nd[x<<1|1];
    }

    void reverse(int x)
    {
        swap(nd[x].maxright,nd[x].minright);
        swap(nd[x].maxleft,nd[x].minleft);
        swap(nd[x].maxmid,nd[x].minmid);
        nd[x].maxright.val*=-1;
        nd[x].maxleft.val*=-1;
        nd[x].maxmid.val*=-1;
        nd[x].minright.val*=-1;
        nd[x].minleft.val*=-1;
        nd[x].minmid.val*=-1;
        nd[x].sum.val*=-1;
    }

    void pushdown(int x)
    {
        if(nd[x].rev)
        {
            nd[x<<1].rev^=1;
            reverse(x<<1);
            nd[x<<1|1].rev^=1;
            reverse(x<<1|1);
            nd[x].rev=0;
        }
    }

    void modifynode(int now,int nl,int nr,int pos,int val)
    {
        if(nl==nr)
        {
            nd[now].sum=Node::Tuple(nl,nr,val);
            nd[now].maxright=nd[now].maxleft=nd[now].maxmid=Node::Tuple(nl,nr,val);
            nd[now].minright=nd[now].minleft=nd[now].minmid=Node::Tuple(nl,nr,val);
            return;
        }
        pushdown(now);
        int mid=nl+nr>>1;
        if(pos<=mid) modifynode(now<<1,nl,mid,pos,val);
        else modifynode(now<<1|1,mid+1,nr,pos,val);
        update(now);
    }

    void modifyrange(int now,int nl,int nr,int ql,int qr)
    {
        if(nl>qr||nr<ql) return;
        if(nl>=ql&&nr<=qr) 
        {
            reverse(now);
            nd[now].rev^=1;
            return;
        }
        pushdown(now);
        int mid=nl+nr>>1;
        modifyrange(now<<1,nl,mid,ql,qr);
        modifyrange(now<<1|1,mid+1,nr,ql,qr);
        update(now);
    }

//    Node queryrangemax(int now,int nl,int nr,int ql,int qr)
//    {
//        if(nl>qr||nr<ql) return Node();
//        if(nl>=ql&&nr<=qr) return nd[now];
//        pushdown(now);
//        int mid=nl+nr>>1;
//        return queryrangemax(now<<1,nl,mid,ql,qr)+queryrangemax(now<<1|1,mid+1,nr,ql,qr);
//    }
    Node queryrangemax(int now,int nl,int nr,int ql,int qr)
    {
        if(nl>=ql&&nr<=qr)
        {
            return nd[now];
        }
        pushdown(now);
        int mid=nl+nr>>1;
        if(ql>mid) return queryrangemax(now<<1|1,mid+1,nr,ql,qr);
        else if(qr<=mid) return queryrangemax(now<<1,nl,mid,ql,qr);
        else return queryrangemax(now<<1,nl,mid,ql,mid)+queryrangemax(now<<1|1,mid+1,nr,mid+1,qr);
    }
}seg;

queue<Node>q;

int main()
{
    int n,m;
    cin>>n;
    for(int i=1;i<=n;i++) 
    {
        int tmp;
        cin>>tmp;
        seg.modifynode(1,1,n,i,tmp);
    }
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        int opt,x,y;
        cin>>opt>>x>>y;
        if(opt)
        {
            int ans=0;
            int k;
            cin>>k;
            while(k--)
            {
                Node tmp=seg.queryrangemax(1,1,n,x,y);
                if(tmp.maxmid.val>0)
                {
                    ans+=tmp.maxmid.val;
                    seg.modifyrange(1,1,n,tmp.maxmid.l,tmp.maxmid.r);
                    q.push(tmp);
                }
                else break;
            }
            cout<<ans<<'\n';
            while(!q.empty())
            {
                seg.modifyrange(1,1,n,q.front().maxmid.l,q.front().maxmid.r);
                q.pop();
            }
        }
        else
        {
            seg.modifynode(1,1,n,x,y);
        }
    }
}
```

---

## 作者：FjswYuzu (赞：2)

对于这样的问题，分操作考虑。第一个操作，显然可以直接单点修改，修改的过程与我们需要维护的信息有关，暂先不管；注意到问题的核心在于第二个操作怎么解决。

首先将这个询问拆出来，简化成为这样一个问题：

> 对于一个序列 $a$，选 $k$ 个不相交的子段和的最大值是多少？

假设现在我们贪心选了最大的子段，这一段需要被拿出去。但是显然我们可以不选两个正数段里面的负数算，这样的贪心显然是错误的。

考虑反悔贪心。我们需要一个方法将这个取走的数的贡献通过另一种方法去掉。既然之前是正贡献，那么显然这里就要变成负贡献。于是这里选出来的子段和全部乘上 $-1$，然后继续找。发现这样如果再选到取负的值，相当于没有选，每次拓展还可以使选出来的段数增加 $1$（如果选相交了，发现刚好可以拆开成为两段；否则不相交使直接两段）。对于这个问题只需要拓展 $k$ 次即可。注意可以不选，所以说当已经不能使贡献增加时就可以不选了。

需要维护区间最大最小子段和（最小子段和可以理解成乘 $-1$ 之后两者交换），显然可以用线段树去维护。当这个段被选掉之后乘上 $-1$ 可以将最大最小子段和取负交换即可。操作的时候还需要额外维护最大最小子段和，左边界最大最小子段和，右边界最大最小子段和的区间编号信息。

至于将线段树还原，可以记录修改了哪些段，再暴力修改回来即可。时间复杂度 $O(mk \log n)$。细节很多。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define lc(x) (x<<1)
#define rc(x) ((x<<1)|1)
#define Mm int mid=(l+r)>>1
int n;
LL a[100005];
struct node{
	LL lmax,rmax,maxn,sum;
	int l,r,ll,lr,rl,rr;
	node(LL LM=0,LL RM=0,LL M=0,LL S=0,int L=0,int R=0,int Ll=0,int LR=0,int RL=0,int RR=0){lmax=LM,rmax=RM,maxn=M,sum=S,l=L,r=R,ll=Ll,lr=LR,rl=RL,rr=RR;}
}tr[400005],minn[400005];
bool tag[400005];
LL read()
{
	LL x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}
void push_up(int now)
{
	tr[now].sum=tr[lc(now)].sum+tr[rc(now)].sum;
	tr[now].lmax=max(tr[lc(now)].lmax,tr[lc(now)].sum+tr[rc(now)].lmax);
	if(tr[now].lmax==tr[lc(now)].lmax)	tr[now].ll=tr[lc(now)].ll,tr[now].lr=tr[lc(now)].lr;
	else	tr[now].ll=tr[lc(now)].ll,tr[now].lr=tr[rc(now)].lr;
	tr[now].rmax=max(tr[rc(now)].rmax,tr[rc(now)].sum+tr[lc(now)].rmax);
	if(tr[now].rmax==tr[rc(now)].rmax)	tr[now].rl=tr[rc(now)].rl,tr[now].rr=tr[rc(now)].rr;
	else	tr[now].rl=tr[lc(now)].rl,tr[now].rr=tr[rc(now)].rr;
	tr[now].maxn=max(max(tr[lc(now)].maxn,tr[rc(now)].maxn),tr[lc(now)].rmax+tr[rc(now)].lmax);
	if(tr[now].maxn==tr[lc(now)].maxn)	tr[now].l=tr[lc(now)].l,tr[now].r=tr[lc(now)].r;
	else if(tr[now].maxn==tr[rc(now)].maxn)	tr[now].l=tr[rc(now)].l,tr[now].r=tr[rc(now)].r;
	else	tr[now].l=tr[lc(now)].rl,tr[now].r=tr[rc(now)].lr;
	minn[now].sum=minn[lc(now)].sum+minn[rc(now)].sum;
	minn[now].lmax=min(minn[lc(now)].lmax,minn[lc(now)].sum+minn[rc(now)].lmax);
	if(minn[now].lmax==minn[lc(now)].lmax)	minn[now].ll=minn[lc(now)].ll,minn[now].lr=minn[lc(now)].lr;
	else	minn[now].ll=minn[lc(now)].ll,minn[now].lr=minn[rc(now)].lr;
	minn[now].rmax=min(minn[rc(now)].rmax,minn[rc(now)].sum+minn[lc(now)].rmax);
	if(minn[now].rmax==minn[rc(now)].rmax)	minn[now].rl=minn[rc(now)].rl,minn[now].rr=minn[rc(now)].rr;
	else	minn[now].rl=minn[lc(now)].rl,minn[now].rr=minn[rc(now)].rr;
	minn[now].maxn=min(min(minn[lc(now)].maxn,minn[rc(now)].maxn),minn[lc(now)].rmax+minn[rc(now)].lmax);
	if(minn[now].maxn==minn[lc(now)].maxn)	minn[now].l=minn[lc(now)].l,minn[now].r=minn[lc(now)].r;
	else if(minn[now].maxn==minn[rc(now)].maxn)	minn[now].l=minn[rc(now)].l,minn[now].r=minn[rc(now)].r;
	else	minn[now].l=minn[lc(now)].rl,minn[now].r=minn[rc(now)].lr;
}
void build(int l,int r,int now)
{
	if(l==r)
	{
		minn[now]=tr[now]=node(a[l],a[l],a[l],a[l],l,l,l,l,l,l);
		return ;
	}
	Mm;
	build(l,mid,lc(now));
	build(mid+1,r,rc(now));
	push_up(now);
}
void changeNode(int now)
{
	tr[now].lmax=-tr[now].lmax;
	tr[now].rmax=-tr[now].rmax;
	tr[now].maxn=-tr[now].maxn;
	tr[now].sum=-tr[now].sum;
	minn[now].lmax=-minn[now].lmax;
	minn[now].rmax=-minn[now].rmax;
	minn[now].maxn=-minn[now].maxn;
	minn[now].sum=-minn[now].sum;
	swap(tr[now],minn[now]);
}
void push_down(int now)
{
	if(tag[now])
	{
		tag[lc(now)]=!tag[lc(now)];
		tag[rc(now)]=!tag[rc(now)];
		changeNode(lc(now));
		changeNode(rc(now));
		tag[now]=false;
	}
}
void modify(int l,int r,int x,int y,int now)
{
	if(x<=l && r<=y)
	{
		tag[now]=!tag[now];
		changeNode(now);
		return ;
	}
	push_down(now);
	Mm;
	if(x<=mid)	modify(l,mid,x,y,lc(now));
	if(mid<y)	modify(mid+1,r,x,y,rc(now));
	push_up(now);
}
void modifyPoint(int l,int r,int x,int now,int val)
{
	if(l==r)
	{
		minn[now]=tr[now]=node(val,val,val,val,l,l,l,l,l,l);
		return ;
	}
	push_down(now);
	Mm;
	if(x<=mid)	modifyPoint(l,mid,x,lc(now),val);
	else	modifyPoint(mid+1,r,x,rc(now),val);
	push_up(now);
}
node query(int l,int r,int now,int x,int y)
{
	if(x<=l && r<=y)	return tr[now];
	Mm;
	push_down(now);
	if(x<=mid && mid>=y)	return query(l,mid,lc(now),x,y);
	if(mid<y && x>mid)	return query(mid+1,r,rc(now),x,y);
	node que1=query(l,mid,lc(now),x,y),que2=query(mid+1,r,rc(now),x,y),que3;
	que3.sum=que1.sum+que2.sum;
	que3.lmax=max(que1.lmax,que1.sum+que2.lmax);
	que3.rmax=max(que2.rmax,que2.sum+que1.rmax);
	que3.maxn=max(max(que1.maxn,que2.maxn),que1.rmax+que2.lmax);
	if(que3.lmax==que1.lmax)	que3.ll=que1.ll,que3.lr=que1.lr;
	else	que3.ll=que1.ll,que3.lr=que2.lr;
	if(que3.rmax==que2.rmax)	que3.rl=que2.rl,que3.rr=que2.rr;
	else	que3.rl=que1.rl,que3.rr=que2.rr;
	if(que3.maxn==que1.maxn)	que3.l=que1.l,que3.r=que1.r;
	else if(que3.maxn==que2.maxn)	que3.l=que2.l,que3.r=que2.r;
	else	que3.l=que1.rl,que3.r=que2.lr;
	return que3;
}
int st[25],su[25],top;
int main(){
	n=read();
	for(int i=1;i<=n;++i)	a[i]=read();
	build(1,n,1);
	int m=read();
	while(m-->0)
	{
		int op=read();
		if(!op)
		{
			int x=read(),val=read();
			modifyPoint(1,n,x,1,val);
		}
		else
		{
			int l=read(),r=read(),k=read();
			LL ans=0;
			for(int i=1;i<=k;++i)
			{
				node s=query(1,n,1,l,r);
				if(s.maxn<=0)	break;
				ans+=s.maxn;
				++top;
				st[top]=s.l;
				su[top]=s.r;
				modify(1,n,s.l,s.r,1);
			}
			printf("%lld\n",ans);
			while(top)	modify(1,n,st[top],su[top],1),--top;
		}
	}
	return 0;
}
```

---

## 作者：LinkyChristian (赞：1)

模拟费用流的入门好题。

所谓 **模拟费用流** ，就是在问题可以用费用流的思想解决，但却不适用费用流的复杂度的时候，我们用一些方法（大部分时候是数据结构）来模拟费用流进行的过程，从而降低复杂度，通过题目的算法。

考虑先对题目构建费用流模型，将点的权值转换到边上，即构造 $n+1$ 个点，点 $i$ 和点 $i+1$ 之间的边的权值为 $a_i$ ，从源点向每个点连边，从每个点向汇点连边，从 $i$ 点流到 $j$ 点说明取了 $a_i \sim a_{j-1}$ 这一段的值，求最大费用流。

考虑直接模拟费用流的过程，最大费用流每次选择费用最大的一条路径增广，由于我们连边的限制，最大路径一定是序列里的一个区间。由于是一个区间，我们可以使用线段树直接维护最大的区间，直接加上这个区间的贡献，然后再按照费用流的步骤将区间内的费用取反。

每一次流动如果流的位置没取过则相当于取了这一段区间，如果取过了则相当于将这一段区间消除（即反悔）。每次流之后实质上取到的区间一定会增加一个，否则相当于它将一次取得区间完全消除，而增广的每一次都是有意义的，不可能被完全消除贡献。

因此我们用线段树每次取最大区间，取完后取反，这个过程进行 $k$ 次，取到的最大权值就是答案。

费用流的本质就是可以反悔的贪心，模拟费用流也继承了这一点。

其他例题：

[P6122 [NEERC2016]Mole Tunnels](https://www.luogu.com.cn/problem/P6122)

[【UER #8】雪灾与外卖](https://uoj.ac/problem/455)

[P5470 [NOI2019] 序列](https://www.luogu.com.cn/problem/P5470)

[P6943 [ICPC2018 WF]Conquer The World](https://www.luogu.com.cn/problem/P6943)

---

