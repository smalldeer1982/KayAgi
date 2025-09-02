# [USACO18FEB] Slingshot P

## 题目描述

Farmer John 最不喜欢的农活之一就是到处搬运牛粪。为了简化这一过程，他想出了一个有趣的主意：与其用拖拉机后面的拖车搬运牛粪，为什么不通过一个巨大的牛粪弹弓将其射到空中呢？（确实，可能会出什么问题呢……）

Farmer John 的农场建在一条笔直的长路上，因此农场上的任何位置都可以简单地用其在这条路上的位置来描述（实际上就是数轴上的一个点）。FJ 建造了 $N$ 个弹弓（$1 \leq N \leq 10^5$），其中第 $i$ 个弹弓由三个整数 $x_i$、$y_i$ 和 $t_i$ 描述，表示这个弹弓可以将牛粪从位置 $x_i$ 射到位置 $y_i$，仅需 $t_i$ 个单位时间。

FJ 有 $M$ 堆牛粪需要搬运（$1 \leq M \leq 10^5$）。第 $j$ 堆牛粪需要从位置 $a_j$ 搬运到位置 $b_j$。用拖拉机搬运牛粪，每移动距离 $d$ 需要 $d$ 个单位时间。FJ 希望通过允许每堆牛粪最多使用一次弹弓来减少搬运时间。FJ 在没有牛粪的情况下移动拖拉机的时间不计入搬运时间。

对于每堆牛粪，请帮助 FJ 确定在最多使用一次弹弓的情况下，搬运所需的最少时间。

## 说明/提示

在这里，第一堆牛粪需要从位置 $1$ 搬运到位置 $12$。如果不使用弹弓，这将花费 $11$ 个单位时间。然而，使用第一个弹弓，花费 $1$ 个单位时间将牛粪移动到位置 $0$（弹弓的起点），$1$ 个单位时间将牛粪射到位置 $10$（弹弓的终点），然后花费 $2$ 个单位时间将牛粪移动到位置 $12$。第二堆牛粪最好不使用弹弓搬运，而第三堆牛粪应使用第二个弹弓搬运。

题目来源：Brian Dean

## 样例 #1

### 输入

```
2 3
0 10 1
13 8 2
1 12
5 2
20 7```

### 输出

```
4
3
10```

# 题解

## 作者：foreverlasting (赞：5)

[题面](https://www.luogu.org/problemnew/show/P4088)

扫描线+线段树。

被楼上震惊了，树套树什么的完全不会啊，表示萌新只会线段树。

首先转换题目，将题目转换成：

一个平面上有$n$个点，坐标为$(xi,yi)$，且每个点有一个点值$ti$。现有$m$个点$(ai,bi)$，使这$m$个点每个点与其他$n$个点的曼哈顿距离加上点值最小。说白了，就是$|ai-xi|+|bi-yi|+ti$最小，这也正是题目所求。

为什么要转换题目呢？因为这样会变得更加直观。我们分类讨论$a$与$x$，$b$与$y$的关系，用线段树+扫描线维护一下就好了。

code:
```
//2018.9.27 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register LL
#define LL long long
#define inf 0x3f3f3f3f3f3f3f
#define eps 1e-15
inline LL read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline LL _abs(const res &x){
    return x>0?x:-x;
}
inline LL _max(const res &x,const res &y){
    return x>y?x:y;
}
inline LL _min(const res &x,const res &y){
    return x<y?x:y;
}
const LL N=2e5+10;
namespace MAIN{
    struct P{
        LL x,y,t,opt,id;
        P() {}
        P(res x,res y,res t,res opt,res id):x(x),y(y),t(t),opt(opt),id(id) {}
    }pos[N];
    LL X[N],Y[N],n,m,cnt,nw;
    inline bool cmp(const P &a,const P &b){
        return a.x!=b.x?a.x<b.x:a.y<b.y;
    }
    namespace Segtree{
        LL mn[N<<2];
        inline void init(){
            memset(mn,inf,sizeof(mn));
        }
        inline void pushup(const res &rt){
            mn[rt]=_min(mn[rt<<1],mn[rt<<1|1]);
        }
        void update(const res &rt,const res &l,const res &r,const res &p,const res &v){
            if(l==r){mn[rt]=_min(mn[rt],v);return;}
            res mid=(l+r)>>1;
            if(p<=mid)update(rt<<1,l,mid,p,v);
            else update(rt<<1|1,mid+1,r,p,v);
            pushup(rt);
        }
        LL query(const res &rt,const res &l,const res &r,const res &L,const res &R){
            if(L<=l&&r<=R)return mn[rt];
            res mid=(l+r)>>1,ret=inf;
            if(L<=mid)ret=_min(ret,query(rt<<1,l,mid,L,R));
            if(R>mid)ret=_min(ret,query(rt<<1|1,mid+1,r,L,R));
            return ret;
        }
    }
    using namespace Segtree;
    LL ans[N];
    inline void MAIN(){
        n=read(),m=read();
        for(res i=1;i<=n;i++){
            res x=read(),y=read(),t=read();
            pos[++cnt]=P(x,y,t,0,0);
            X[cnt]=x,Y[cnt]=y;
        }
        for(res i=1;i<=m;i++){
            res x=read(),y=read();
            pos[++cnt]=P(x,y,0,1,i);
            X[cnt]=x,Y[cnt]=y;
            ans[i]=_abs(x-y);
        }
        sort(X+1,X+cnt+1);
        nw=unique(X+1,X+cnt+1)-X-1;
        for(res i=1;i<=cnt;i++)pos[i].x=lower_bound(X+1,X+nw+1,pos[i].x)-X;
        sort(Y+1,Y+cnt+1);
        nw=unique(Y+1,Y+cnt+1)-Y-1;
        for(res i=1;i<=cnt;i++)pos[i].y=lower_bound(Y+1,Y+nw+1,pos[i].y)-Y;
        sort(pos+1,pos+cnt+1,cmp);
        init();
        for(res i=1;i<=cnt;i++){
            if(!pos[i].opt)update(1,1,cnt,pos[i].y,-X[pos[i].x]-Y[pos[i].y]+pos[i].t);
            else ans[pos[i].id]=_min(ans[pos[i].id],query(1,1,cnt,1,pos[i].y)+X[pos[i].x]+Y[pos[i].y]);
        }
        init();
        for(res i=cnt;i>=1;i--){
            if(!pos[i].opt)update(1,1,cnt,pos[i].y,X[pos[i].x]+Y[pos[i].y]+pos[i].t);
            else ans[pos[i].id]=_min(ans[pos[i].id],query(1,1,cnt,pos[i].y,cnt)-X[pos[i].x]-Y[pos[i].y]);
        }
        init();
        for(res i=1;i<=cnt;i++){
            if(!pos[i].opt)update(1,1,cnt,pos[i].y,-X[pos[i].x]+Y[pos[i].y]+pos[i].t);
            else ans[pos[i].id]=_min(ans[pos[i].id],query(1,1,cnt,pos[i].y,cnt)+X[pos[i].x]-Y[pos[i].y]);
        }
        init();
        for(res i=cnt;i>=1;i--){
            if(!pos[i].opt)update(1,1,cnt,pos[i].y,X[pos[i].x]-Y[pos[i].y]+pos[i].t);
            else ans[pos[i].id]=_min(ans[pos[i].id],query(1,1,cnt,1,pos[i].y)-X[pos[i].x]+Y[pos[i].y]);
        }
        for(res i=1;i<=m;i++)printf("%lld\n",ans[i]);
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：yangchenxiao (赞：4)

首先按照题意写出式子，对于 $(a,b)$ 的询问使用 $(x,y)$ 的弹弓，需要的花费是 $|a-x|-|b-y|+t$，那么此时把 $(a,b)$ 看成点，$(x,y)$ 也看成点，就变成了平面问题。    
按照套路将绝对值分类讨论拆开，以 $x\le a$ 且 $y\le b$ 为例，答案为 $a+b-(x+y-t)$，变成经典的二维偏序问题。此时按照 $x$ 排序后把后半部分插入树状数组，在 $(a,b)$ 出查询即可。   

一个小 $trick$ 是其实没有必要建出四棵不同的树状数组，只需要将坐标系旋转四次即可统计到全部的答案。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
const int inf=2e9;
int n,m,lshx[maxn],lshy[maxn],x[maxn],y[maxn],w[maxn],c[maxn],ans[maxn],nm;
int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct Node{
	int x,y,w,op,rx,ry;
}a[maxn];
void solve(int x[],int lsh[]){
	for(int i=1;i<=nm;i++)lsh[i]=x[i];
	sort(lsh+1,lsh+nm+1);int tot=unique(lsh+1,lsh+nm+1)-lsh-1;
	for(int i=1;i<=nm;i++)x[i]=lower_bound(lsh+1,lsh+tot+1,x[i])-lsh;
	return ;
}
void add(int x,int w){for(;x<=nm;x+=x&-x)c[x]=min(c[x],w);}
int ask(int x){int res=0;for(;x;x-=x&-x)res=min(res,c[x]);return res;}
void solve(){
	sort(a+1,a+nm+1,[](Node x,Node y){return x.x<y.x;});
	memset(c,0x3f,sizeof c);
	for(int i=1;i<=nm;i++){
		if(a[i].op)add(a[i].y,-a[i].rx-a[i].ry+a[i].w);
		else ans[a[i].w]=min(ans[a[i].w],ask(a[i].y)+a[i].rx+a[i].ry);
	}
	return ;
}
signed main(){
	n=read(),m=read();nm=n+m;
	for(int i=1;i<=n;i++)x[i]=read(),y[i]=read(),w[i]=read();
	for(int i=1;i<=m;i++)x[i+n]=read(),y[i+n]=read(),ans[i]=abs(x[i+n]-y[i+n]);
	solve(x,lshx),solve(y,lshy);
	for(int i=1;i<=nm;i++)a[i]={x[i],y[i],i<=n?w[i]:i-n,i<=n,lshx[x[i]],lshy[y[i]]};
	solve();for(int i=1;i<=nm;i++)a[i].x=nm-a[i].x+1,a[i].rx=inf-a[i].rx;
	solve();for(int i=1;i<=nm;i++)a[i].y=nm-a[i].y+1,a[i].ry=inf-a[i].ry;
	solve();for(int i=1;i<=nm;i++)a[i].x=nm-a[i].x+1,a[i].rx=inf-a[i].rx;
	solve();for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：忘怀星 (赞：3)

> 被我用暴力草过去了哈哈哈

就像是其他题解所说的一样，问题可以转化为找与给定点距离与权值和的最小值。我们考虑若所有点权均为 $0$ ，那么就是找平面与给定点最小距离，可以使用 KD 树解决。此题带有权值，不能直接二维的 KD 树解决。考虑将权值看做第三个维度，那么此题就转化为三维最近点对问题，依然可以使用 KD 树解决。

最终复杂度 $O(\text{玄学})$ 但是实测可以通过。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define ll long long
// #define  int long long
using namespace std;

int read()
{
	int a = 0,x = 1;char ch = getchar();
	while(ch > '9' || ch < '0') {if(ch == '-') x = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9') {a = a*10 + ch-'0';ch = getchar();}
	return a*x;
}
const int N=2e6+7;
ll inf = 2e18+7;
int n,m,rt,tot,WD;

struct Point{int p[3];}A[N];
bool operator < (Point a,Point b) {return a.p[WD] < b.p[WD];}
struct node{Point tp;int ls,rs,mi[3],mx[3];}tre[N];
void push_up(int root)
{
	int l = tre[root].ls,r = tre[root].rs;
	for(int i = 0;i < 3;i ++) {
		tre[root].mi[i] = tre[root].mx[i] = tre[root].tp.p[i];
		if(l) tre[root].mi[i] = min(tre[root].mi[i],tre[l].mi[i]),tre[root].mx[i] = max(tre[root].mx[i],tre[l].mx[i]);
		if(r) tre[root].mi[i] = min(tre[root].mi[i],tre[r].mi[i]),tre[root].mx[i] = max(tre[root].mx[i],tre[r].mx[i]);
	}
}
ll calc(Point x,node y)
{
	ll ret = 0;
	for(int i = 0;i < 3;i ++) {
		ret += max(0,y.mi[i]-x.p[i]) + max(0,x.p[i]-y.mx[i]);
	}
	return ret;
}
ll calc(Point a,Point b)
{
	ll ret = 0;
	for(int i = 0;i < 3;i ++) {
		ret += abs(a.p[i]-b.p[i]);
	}
	return ret;
}
void build(int &root,int l,int r,int wd)
{
	int mid = l+r>>1;WD = wd;
	nth_element(A+l,A+mid,A+r+1);
	root = ++tot;tre[root].tp = A[mid];
	if(l<=mid-1) build(tre[root].ls,l,mid-1,(wd+1)%3);
	if(r>=mid+1) build(tre[root].rs,mid+1,r,(wd+1)%3);
	push_up(root);
}
ll ans;
void dfs(int root,Point x)
{
	ans = min(ans,calc(x,tre[root].tp));
	ll tmp1 = inf,tmp2 = inf;int l = tre[root].ls,r = tre[root].rs;
	if(l) tmp1 = min(tmp1,calc(x,tre[l]));
	if(r) tmp2 = min(tmp2,calc(x,tre[r]));
	if(l<r) {
		if(l && ans > tmp1) dfs(l,x);
		if(r && ans > tmp2) dfs(r,x);
	} else {
		if(r && ans > tmp2) dfs(r,x);
		if(l && ans > tmp1) dfs(l,x);
	}
}
signed main()
{
	// freopen("random.in","r",stdin);
	// freopen("sol.out","w",stdout);
	n = read(),m = read();
	for(int i = 1;i <= n;i ++) {
		for(int j = 0;j < 3;j ++) A[i].p[j] = read();
	}
	// puts("!");
	build(rt,1,n,0);
	for(int i = 1;i <= m;i ++) {
		Point x;x.p[0] = read(),x.p[1] = read(),x.p[2] = 0;
		ans = abs(x.p[1]-x.p[0]);
		dfs(rt,x);printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：3)

[题目链接](https://www.luogu.com.cn/problem/P4088)

> 题意：有一个数轴，上面有 $n$ 个传送门，使用第 $i$ 个传送门，你可以从 $x_i$ 走到 $y_i$，花费的时间为 $t_i$ 秒。你的速度为 $1$ 格/秒，有 $m$ 次询问，每次你要从 $a_i$ 走到 $b_i$，最多使用一次传送门，问最少需要多少秒。

> $1 \leq n,m \leq 10^5$，$0 \leq a_i,b_i \leq 10^9$

我果然是要退役了，用未去重的数组离散化（

很显然对于第 $j$ 个询问使用第 $i$ 个传送门的情况，需要 $|x_i-a_j|+|y_i-b_j|+t_i$ 秒的时间。看那个绝对值有点像曼哈顿距离……这就启发我们将题目转换为：平面上有 $n$ 个点，第 $i$ 个点位于 $(x_i,y_i)$，有点权 $t_i$。有 $m$ 次询问，要求与 $(a_i,b_i)$ 的曼哈顿距离加上点的权值最小的点。

为什么要这么转化呢？看到平面，我们就想到二维数点。将这 $n+m$ 个点按 $x$ 坐标排序，暴力将绝对值拆开，分四种情况更新答案就可以了。

注意事项：对每个询问，记得赋初值 $|b_i-a_i|$

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int _abs(int x){
	return (x<0)?-x:x;
}
int n,m;
struct ycxakioi{
	int x,y,t;
	friend bool operator <(ycxakioi ycx,ycxakioi tzc){
		return ycx.x<tzc.x;
	}
} p[200005];
struct query{
	int x,y,id,ans;
	friend bool operator <(query x,query y){
		return x.x<y.x;
	}
} q[200005];
int keyx[200005],xc,yc,keyy[200005],hsx[200005],cx,hsy[200005],cy;
struct SegTree{
	struct node{
		int l,r,mn;
	} s[200005<<2];
	inline void init(){
		fz(i,0,(200005<<2)-1)	s[i].mn=0x3f3f3f3f3f3f3f3fll;
	}
	inline void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;
		if(l==r)	return;
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
	}
	inline void modify(int k,int ind,int x){
		if(s[k].l==s[k].r){
			s[k].mn=min(s[k].mn,x);
			return;
		}
		int mid=(s[k].l+s[k].r)>>1;
		if(ind<=mid)	modify(k<<1,ind,x);
		else			modify(k<<1|1,ind,x);
		s[k].mn=min(s[k<<1].mn,s[k<<1|1].mn);
	}
	inline int query(int k,int l,int r){
		if(l<=s[k].l&&s[k].r<=r){
			return s[k].mn;
		}
		int mid=(s[k].l+s[k].r)>>1;
		if(r<=mid)	return query(k<<1,l,r);
		else if(l>mid)	return query(k<<1|1,l,r);
		else		return min(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
	}
} s1,s2,s3,s4;
int anss[200005];
signed main(){
//	filei("P4088_5.in");
	n=read(),m=read();
	fz(i,1,n){
		p[i].x=read();
		p[i].y=read();
		p[i].t=read();
		keyx[++xc]=p[i].x;
		keyy[++yc]=p[i].y;
	}
	fz(i,1,m){
		q[i].x=read();
		q[i].y=read();
		q[i].id=i;
		q[i].ans=_abs(q[i].y-q[i].x);
		keyx[++xc]=q[i].x;
		keyy[++yc]=q[i].y;
	}
	sort(keyx+1,keyx+xc+1);sort(keyy+1,keyy+yc+1);
	keyx[0]=0x3f3f3f3f;keyy[0]=0x3f3f3f3f;
	fz(i,1,xc)	if(keyx[i]!=keyx[i-1])	hsx[++cx]=keyx[i];
	fz(i,1,yc)	if(keyy[i]!=keyy[i-1])	hsy[++cy]=keyy[i];
	fz(i,1,n)	p[i].x=lower_bound(hsx+1,hsx+cx+1,p[i].x)-hsx;
	fz(i,1,n)	p[i].y=lower_bound(hsy+1,hsy+cy+1,p[i].y)-hsy;
	fz(i,1,m)	q[i].x=lower_bound(hsx+1,hsx+cx+1,q[i].x)-hsx;
	fz(i,1,m)	q[i].y=lower_bound(hsy+1,hsy+cy+1,q[i].y)-hsy;
//	fz(i,1,n)	cout<<p[i].x<<" "<<p[i].y<<" "<<p[i].t<<endl;
//	fz(i,1,m)	cout<<q[i].x<<" "<<q[i].y<<endl;
	sort(p+1,p+n+1);
	sort(q+1,q+m+1);
	s1.build(1,1,cy);s2.build(1,1,cy);s3.build(1,1,cy);s4.build(1,1,cy);
	s1.init();s2.init();s3.init();s4.init();
	p[n+1].x=0x3f3f3f3f;
	int cur=1;
	fz(i,1,m){
//		if(i>=5000)	cerr<<i<<endl;
		while(p[cur].x<=q[i].x){
			s1.modify(1,p[cur].y,-hsy[p[cur].y]-hsx[p[cur].x]+p[cur].t);
			s2.modify(1,p[cur].y,hsy[p[cur].y]-hsx[p[cur].x]+p[cur].t);
			cur++;
		}
		q[i].ans=min(q[i].ans,s1.query(1,1,q[i].y)+hsx[q[i].x]+hsy[q[i].y]);
		q[i].ans=min(q[i].ans,s2.query(1,q[i].y,cy)+hsx[q[i].x]-hsy[q[i].y]);
	}
	cur=n;
	fd(i,m,1){
//		cerr<<i<<endl;
		while(p[cur].x>=q[i].x&&cur>=1){
			s3.modify(1,p[cur].y,hsy[p[cur].y]+hsx[p[cur].x]+p[cur].t);
			s4.modify(1,p[cur].y,-hsy[p[cur].y]+hsx[p[cur].x]+p[cur].t);
			cur--;
		}
		q[i].ans=min(q[i].ans,s4.query(1,1,q[i].y)-hsx[q[i].x]+hsy[q[i].y]);
		q[i].ans=min(q[i].ans,s3.query(1,q[i].y,cy)-hsx[q[i].x]-hsy[q[i].y]);
	}
	fz(i,1,m)	anss[q[i].id]=q[i].ans;
	fz(i,1,m)	cout<<anss[i]<<endl;
	return 0;
}
```

---

## 作者：Jμdge (赞：2)

树状数组（虽说楼上大佬写过了 QAQ）

# noteskey


这道题可以就只用一个树状数组的数据结构...

于是树套树就没有打过了...QWQ 我太c了

总之就是分四种情况更新答案：

![](https://ws4.sinaimg.cn/large/005S5cb6ly1g2bpyxz5aqj31500ist8x.jpg
)

最后对于每个询问每次取 min 输出即可

然后没有然后，注意精度问题就行了（实在不行就 $ \#define ~int~ long~ long$?）


# code

代码短但是丑，题解区码风++

```cpp
//by Judge
#include<bits/stdc++.h>
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(Rg int i=(a),I=(b)-1;i>I;--i)
#define ll long long
using namespace std;
const int M=2e5+3;
typedef int arr[M];
typedef ll ARR[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline bool cmin(ll& a,ll b){return a>b?a=b,1:0;}
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} char sr[1<<21],z[20];int CCF=-1,Z;
inline void Ot(){fwrite(sr,1,CCF+1,stdout),CCF=-1;}
inline void print(ll x,char chr='\n'){
	if(CCF>1<<20)Ot();if(x<0)sr[++CCF]=45,x=-x;
	while(z[++Z]=x%10+48,x/=10);
	while(sr[++CCF]=z[Z],--Z);sr[++CCF]=chr;
}
int n,m,nm,cnt; arr px,py; ARR c,ans;
struct node{ int x,y,v,id; node(){}
	node(int xx,int yy,int vv,int iid){x=xx,y=yy,v=vv,id=iid;}
}a[M];
inline bool cmp(node& a,node& b){return a.x^b.x?a.x<b.x:a.y<b.y;}
inline void update(int x,ll d){for(;x<=cnt;x+=x&-x) cmin(c[x],d);}
inline ll query(int x){ll s=2e9;for(;x;x^=x&-x) cmin(s,c[x]); return s;}
signed main(){ n=read(),m=read(); int x,y,t;
	fp(i,1,n) x=read(),y=read(),t=read(),
		a[++cnt]=node(x,y,t,0),px[cnt]=x,py[cnt]=y;
	fp(i,1,m) x=read(),y=read(),a[++cnt]=node(x,y,0,i),
		px[cnt]=x,py[cnt]=y,ans[i]=abs(y-x);
	sort(px+1,px+1+cnt),sort(py+1,py+1+cnt);
	sort(a+1,a+1+cnt,cmp);
	nm=unique(px+1,px+1+cnt)-1-px;
	fp(i,1,cnt) a[i].x=lower_bound(px+1,px+1+cnt,a[i].x)-px;
	nm=unique(py+1,py+1+cnt)-1-py;
	fp(i,1,cnt) a[i].y=lower_bound(py+1,py+1+cnt,a[i].y)-py;
	memset(c,0x3f,(cnt+2)<<3);
	fp(i,1,cnt) if(!a[i].id) update(a[i].y,1ll*-px[a[i].x]-py[a[i].y]+a[i].v);
		else cmin(ans[a[i].id],query(a[i].y)+px[a[i].x]+py[a[i].y]);
	memset(c,0x3f,(cnt+2)<<3);
	fp(i,1,cnt) if(!a[i].id) update(cnt-a[i].y+1,1ll*-px[a[i].x]+py[a[i].y]+a[i].v);
		else cmin(ans[a[i].id],query(cnt-a[i].y+1)+px[a[i].x]-py[a[i].y]);
	memset(c,0x3f,(cnt+2)<<3);
	fd(i,cnt,1) if(!a[i].id) update(a[i].y,1ll*px[a[i].x]-py[a[i].y]+a[i].v);
		else cmin(ans[a[i].id],query(a[i].y)-px[a[i].x]+py[a[i].y]);
	memset(c,0x3f,(cnt+2)<<3);
	fd(i,cnt,1) if(!a[i].id) update(cnt-a[i].y+1,1ll*px[a[i].x]+py[a[i].y]+a[i].v);
		else cmin(ans[a[i].id],query(cnt-a[i].y+1)-px[a[i].x]-py[a[i].y]);
	fp(i,1,m) print(ans[i]); return Ot(),0;
}
```

---

## 作者：大菜鸡fks (赞：2)

大概是树套树？

可以得到dp方程。然后发现有绝对值，很不优美。

考虑用数据结构去掉。我比较暴力。直接用了树套树。四种情况分四个树套树。每个做二维数点。

```cpp
// luogu-judger-enable-o2
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
inline int read(){int x=0,f=1; int ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int inf=1e18,maxn=2e5+5;
struct pp{
    int x,y,v;
}q[maxn],b[maxn];
int n,m,ha1[maxn],tot1,tot2,ha2[maxn];
struct node{
    int ls,rs,mn;
};
struct seg{
    int tot,root[530000];
    node a[maxn*12];
    inline int get(int x){
        if (!x) return inf; else return a[x].mn;
    }
    inline void pushup(int k){
        a[k].mn=min(get(a[k].ls),get(a[k].rs));
    }
    void update(int &k,int l,int r,int x,int v){
        if (!k){k=++tot; a[k].mn=inf;}
        if (l==r){
            a[k].mn=min(a[k].mn,v);
            return;
        }
        int mid=(l+r)>>1;
        if (mid>=x) update(a[k].ls,l,mid,x,v);
            else update(a[k].rs,mid+1,r,x,v);
        pushup(k);
    }
    void upd(int k,int l,int r,int x,int y,int v){
        update(root[k],1,tot2,y,v);
        if (l==r){
            return;
        }
        int mid=(l+r)>>1;
        if (mid>=x) upd(k<<1,l,mid,x,y,v);
            else upd(k<<1|1,mid+1,r,x,y,v);
    }
    int query(int &k,int l,int r,int x,int y){
        if (!k){k=++tot; a[k].mn=inf;}
        if (l==x&&r==y){
            return a[k].mn;
        }
        int mid=(l+r)>>1;
        if (mid>=y) return query(a[k].ls,l,mid,x,y);
            else if (mid<x) return query(a[k].rs,mid+1,r,x,y);
                else return min(query(a[k].ls,l,mid,x,mid),query(a[k].rs,mid+1,r,mid+1,y));
    }
    int qry(int k,int l,int r,int x,int y,int X,int Y){
        if (l==x&&r==y){
            return query(root[k],1,tot2,X,Y);
        }
        int mid=(l+r)>>1;
        if (mid>=y) return qry(k<<1,l,mid,x,y,X,Y);
            else if (mid<x) return qry(k<<1|1,mid+1,r,x,y,X,Y);
                else return min(qry(k<<1,l,mid,x,mid,X,Y),qry(k<<1|1,mid+1,r,mid+1,y,X,Y));
    }
}tree[4];
inline void init(){
    n=read(); m=read();
    for (int i=1;i<=n;i++){
        b[i]=(pp){read(),read(),read()};	
        ha1[++tot1]=b[i].x;
        ha2[++tot2]=b[i].y;
    }
    for (int i=1;i<=m;i++){
        q[i]=(pp){read(),read(),0};	
        ha1[++tot1]=q[i].x;
        ha2[++tot2]=q[i].y;	
    }
    sort(ha1+1,ha1+tot1+1);
    sort(ha2+1,ha2+tot2+1);
    int temp=tot1; tot1=1;
    for (int i=2;i<=temp;i++){
        if (ha1[i]!=ha1[tot1]){
            ha1[++tot1]=ha1[i];
        }
    }
    temp=tot2; tot2=1;
    for (int i=2;i<=temp;i++){
        if (ha2[i]!=ha2[tot2]){
            ha2[++tot2]=ha2[i];
        }
    }
}
inline void solve(){
    for (int i=1;i<=n;i++){
        int x=lower_bound(ha1+1,ha1+1+tot1,b[i].x)-ha1,y=lower_bound(ha2+1,ha2+1+tot2,b[i].y)-ha2;
        tree[0].upd(1,1,tot1,x,y,b[i].x+b[i].y+b[i].v);
        tree[1].upd(1,1,tot1,x,y,b[i].x-b[i].y+b[i].v);
        tree[2].upd(1,1,tot1,x,y,-b[i].x+b[i].y+b[i].v);
        tree[3].upd(1,1,tot1,x,y,-b[i].x-b[i].y+b[i].v);
    }
    for (int i=1;i<=m;i++){
        int x=lower_bound(ha1+1,ha1+1+tot1,q[i].x)-ha1,y=lower_bound(ha2+1,ha2+1+tot2,q[i].y)-ha2;
        int ans1,ans2,ans3,ans4,ans;
        ans1=tree[0].qry(1,1,tot1,x,tot1,y,tot2)-q[i].x-q[i].y;
        ans2=tree[1].qry(1,1,tot1,x,tot1,1,y)-q[i].x+q[i].y;
        ans3=tree[2].qry(1,1,tot1,1,x,y,tot2)+q[i].x-q[i].y;
        ans4=tree[3].qry(1,1,tot1,1,x,1,y)+q[i].x+q[i].y;
        ans=min(ans1,ans2);
        ans=min(ans3,ans4);
        ans=min(ans,abs(q[i].x-q[i].y));
        writeln(ans);
    }
}
signed main(){
//	freopen("slingshot.in","r",stdin);
//	freopen("slingshot.out","w",stdout);
    init();
    solve();
    return 0;
}
```

---

## 作者：DengDuck (赞：1)

死因：离线询问忘记排回去。

这题是一道很有意思的线段树题。

考虑在 $a\to b$ 的任务中使用弹弓 $(x,y,t)$，则代价为：
$$
|a-x|+|b-y|+t
$$
绝对值不好维护，考虑分讨拆式子更新答案，一共是四种情况，我们以 $x\leq a,y\leq b$ 的情况为例讲讲每种情况怎么维护。

显然此时一个 $a\to b$ 的代价必然有 $a+b$，这是不受弹弓影响的，弹弓的贡献是 $-x-y+t$，接下来重点是维护对于每个任务找到满足 $x\leq a,y\leq b$ 的弹弓。

简单思考之后，我们发现一维可以用双指针维护，一维可以用线段树维护。

首先任务以 $a$ 为关键字排序，弹弓以 $x$ 为关键字排序，然后我们按顺序处理任务，同时将 $x\leq a$ 的弹弓加入线段树，位置是 $y$ 值，权值是代价，然后线段树维护区间最小值。

每次查询只需要查询当前区间的 $[1,b]$ 的最小值即可，注意特判不存在的情况。

其他情况是类似的。

时间复杂度为 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
const LL inf=1e15;
const LL N=1e6+5;
//const LL M;
//const LL mod;
//const LF eps;
//const LL P;
vector<LL>hsh;
struct node
{
	LL x,y,t;
}a[N];
struct tree
{
	LL l,r,mn;
}t[N*4];
struct pt
{
	LL a,b,num,ans;
}b[N];
LL n,m;
void build(LL rt,LL l,LL r)
{
	t[rt]={l,r,inf};
	if(l==r)return;
	LL mid=(l+r)/2;
	build(rt*2,l,mid),build(rt*2+1,mid+1,r);
}
void ins(LL rt,LL x,LL k)
{
	if(t[rt].r<x||x<t[rt].l)return;
	t[rt].mn=min(t[rt].mn,k);
	if(t[rt].l==t[rt].r)return;
	ins(rt*2,x,k),ins(rt*2+1,x,k);
}
LL query(LL rt,LL l,LL r)
{
	if(t[rt].r<l||r<t[rt].l)return inf;
	if(l<=t[rt].l&&t[rt].r<=r)return t[rt].mn;
	return min(query(rt*2,l,r),query(rt*2+1,l,r));
}
LL find(LL x)
{
	return lower_bound(hsh.begin(),hsh.end(),x)-hsh.begin()+1;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].t);
		hsh.pb(a[i].y);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&b[i].a,&b[i].b);
		b[i].num=i;
		b[i].ans=fabs(b[i].a-b[i].b);
		hsh.pb(b[i].b);
	}
	sort(hsh.begin(),hsh.end());
	hsh.erase(unique(hsh.begin(),hsh.end()),hsh.end());
	sort(a+1,a+n+1,[](node x,node y){return x.x<y.x;});
	sort(b+1,b+m+1,[](pt x,pt y){return x.a<y.a;});
	build(1,1,hsh.size());
	LL t=1;
	for(int i=1;i<=m;i++)
	{
		while(a[t].x<=b[i].a&&t<=n)ins(1,find(a[t].y),-a[t].x-a[t].y+a[t].t),t++;
		LL gt=query(1,1,find(b[i].b));
		if(gt==inf)continue;
		b[i].ans=min(b[i].ans,b[i].a+b[i].b+gt);
	}
	build(1,1,hsh.size());
	t=1;
	for(int i=1;i<=m;i++)
	{
		while(a[t].x<=b[i].a&&t<=n)ins(1,find(a[t].y),-a[t].x+a[t].y+a[t].t),t++;
		LL gt=query(1,find(b[i].b),hsh.size());
		if(gt==inf)continue;	
		b[i].ans=min(b[i].ans,b[i].a-b[i].b+gt);
	}
	build(1,1,hsh.size());
	t=n;
	for(int i=m;i>=1;i--)
	{
		while(a[t].x>=b[i].a&&t)ins(1,find(a[t].y),a[t].x-a[t].y+a[t].t),t--;
		LL gt=query(1,1,find(b[i].b));
		if(gt==inf)continue;
		b[i].ans=min(b[i].ans,-b[i].a+b[i].b+gt);
	}
	build(1,1,hsh.size());
	t=n;
	for(int i=m;i>=1;i--)
	{
		while(a[t].x>=b[i].a&&t)ins(1,find(a[t].y),a[t].x+a[t].y+a[t].t),t--;
		LL gt=query(1,find(b[i].b),hsh.size());
		if(gt==inf)continue;
		b[i].ans=min(b[i].ans,-b[i].a-b[i].b+gt);
	}
	sort(b+1,b+m+1,[](pt x,pt y){return x.num<y.num;});
	for(int i=1;i<=m;i++)
	{ 
		printf("%lld\n",b[i].ans);
	}
	return 0;
}
//RP++
```

---

## 作者：PurpleWonder (赞：1)

首先对于一条路径a，假设任意一个弹弓都不使用，则时间为r[a]-l[a]的绝对值

假设需要使用弹弓d，所花费的时间是|l[a]-l[d]|+|r[a]-r[d]|+time[d];

假设l[a]>=l[d],r[a]>=r[d],则时间是l[a]+r[a]-l[d]-r[d]+time[d];

对于l[a]<=l[d],r[a]>=r[d],则时间是r[a]-l[a]+l[d]-r[d]+time[d];

对于l[a]>=l[d],r[a]<=r[d],则时间是l[a]-r[a]-l[d]+r[d]+time[d];

对于l[a]<=l[d],r[a]<=r[d],则时间是-l[a]-r[a]+l[d]+r[d]+time[d];

首先l[a]与r[a]都是定值，那么就分成四种情况，依次在四种情况下用后面和d有关的一个式子去更新答案即可。

那么就可以将问题转化为一个二维偏序问题，只有两个条件均满足的弹弓才能对答案产生贡献。

其实二位偏序并不需要树套树的……一维排序+一维线段树即可解决。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n,m;
struct node {
    int l,r,time,ans,id;
} nd[200010];
long long d[6000100];
int l[6000100],r[6000100],gs,rt;
bool cmp1(node a,node b) {
    return a.l==b.l?a.time>b.time:a.l<b.l;
}
bool cmp2(node a,node b) {
    return a.l==b.l?a.time>b.time:a.l>b.l;
}
bool cmp3(node a,node b) {
    return a.l==b.l?a.time>b.time:a.l<b.l;
}
bool cmp4(node a,node b) {
    return a.l==b.l?a.time>b.time:a.l>b.l;
}
bool cmp5(node a,node b) {
    return a.id<b.id;
}

void update(int &x,int li,int ri,int p,long long v) {
    if(!x) {
        x=++gs;
    }
    if(li==ri) {
        d[x]=min(d[x],v);
        return;
    }
    int mid=(li+ri)>>1;
    if(p<=mid)update(l[x],li,mid,p,v);
    else update(r[x],mid+1,ri,p,v);
    d[x]=min(d[l[x]],d[r[x]]);
}

long long query(int x,int li,int ri,int nl,int nr) {
    if(!x || li>nr || ri<nl)return 0x3f3f3f3f3f3f3f3fll;
    if(li>=nl && ri<=nr) {
        return d[x];
    }
    int mid=(li+ri)>>1;
    return min(query(l[x],li,mid,nl,nr),query(r[x],mid+1,ri,nl,nr));
}

int main() {
    scanf("%d %d",&n,&m);
    for(int i=1; i<=n; i++) {
        scanf("%d %d %d",&nd[i].l,&nd[i].r,&nd[i].time);
        nd[i].id=i;
    }
    for(int i=n+1; i<=n+m; i++) {
        scanf("%d %d",&nd[i].l,&nd[i].r);
        nd[i].time=-1;
        nd[i].id=i;
        nd[i].ans=nd[i].r-nd[i].l;
        if(nd[i].ans<0)nd[i].ans*=-1;
    }

    sort(nd+1,nd+n+m+1,cmp1);
    memset(d,0x3f,sizeof(d));
    for(int i=1; i<=n+m; i++) {
        if(~nd[i].time)update(rt,1,1000000000,nd[i].r,(long long)-nd[i].l-nd[i].r+nd[i].time);
        else nd[i].ans=min((long long)nd[i].ans,nd[i].l+nd[i].r+query(1,1,1000000000,1,nd[i].r));
    }
    memset(d,0x3f,sizeof(d));
    sort(nd+1,nd+n+m+1,cmp2);
    for(int i=1; i<=n+m; i++) {
        if(~nd[i].time)update(rt,1,1000000000,nd[i].r,(long long)nd[i].l-nd[i].r+nd[i].time);
        else nd[i].ans=min((long long)nd[i].ans,nd[i].r-nd[i].l+query(1,1,1000000000,1,nd[i].r));
    }
    memset(d,0x3f,sizeof(d));
    sort(nd+1,nd+n+m+1,cmp3);
    for(int i=1; i<=n+m; i++) {
        if(~nd[i].time)update(rt,1,1000000000,nd[i].r,(long long)-nd[i].l+nd[i].r+nd[i].time);
        else nd[i].ans=min((long long)nd[i].ans,nd[i].l-nd[i].r+query(1,1,1000000000,nd[i].r,1000000000));
    }
    memset(d,0x3f,sizeof(d));
    sort(nd+1,nd+n+m+1,cmp4);
    for(int i=1; i<=n+m; i++) {
        if(~nd[i].time)update(rt,1,1000000000,nd[i].r,(long long)nd[i].l+nd[i].r+nd[i].time);
        else nd[i].ans=min((long long)nd[i].ans,-nd[i].l-nd[i].r+query(1,1,1000000000,nd[i].r,1000000000));
    }
    sort(nd+1,nd+n+m+1,cmp5);
    for(int i=n+1;i<=n+m;i++)printf("%d\n",nd[i].ans);
}

```

---

