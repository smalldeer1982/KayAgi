# [EC Final 2022] Rectangle

## 题目描述

庞教授有 $n$ 个矩形，第 $i$ 个矩形的左下角坐标是 $(x_{i,1}, y_{i,1})$，右上角坐标是 $(x_{i,2}, y_{i,2})$。矩形可以重叠。

你需要选择三条直线，使得：

- 每条直线应该与 $x$ 轴或 $y$ 轴平行，即其方程为 $x = a$ 或 $y = a$。
- 在方程 $x = a$ 或 $y = a$ 中，$a$ 应该是 $[1, 10^9]$ 区间内的整数。
- 这三条直线应该是不同的。
- 每个矩形至少被一条直线 $\textbf{触摸}$。如果一条直线与矩形的边界和/或内部相交，则称该直线触摸该矩形。

你需要计算选择三条直线的方法数。由于答案可能非常大，输出对 $998244353$ 取模的结果。如果两种方法只有三条直线的顺序不同，则认为它们是相同的。

## 样例 #1

### 输入

```
3
1
1 1 1000000000 1000000000
3
1 1 2 2
3 3 4 4
5 5 6 6
5
581574116 47617804 999010750 826131769
223840663 366320907 613364068 926991396
267630832 51913575 488301124 223957497
217461197 492085159 999485867 913732845
28144453 603781668 912516656 993160442```

### 输出

```
230616300
64
977066618```

# 题解

## 作者：yyyyxh (赞：2)

数据结构好题，写死我了 QwQ……

这个题是可以用 segbeats 做到 $O(n\log n)$ 的。

先离散化。我们只用考虑三条竖线和两竖一横的情况。三条竖线线性 DP 一下就行了。

两竖一横的情况可以考虑枚举更靠后的那条竖线，首先这条竖线后面还没有被覆盖的区间就只能用横线覆盖了，于是所有后面的区间另一维取个交，对于横线就是一个区间的限制。

从前往后扫更靠后的那条竖线，问题变成了每次加入一些矩形然后询问一条竖线一条横线的这种问题的答案。

开一颗线段树，维护对于每一种横线的位置竖线的区间限制。这样修改就变成了对于一个前缀/后缀与一个区间取交，求区间长度和。经典 segbeats 问题，由于没有区间加减所以复杂度是 $O(n\log n)$。

但是还有几个巨大的细节，首先你要保证新取的竖线在你枚举的竖线之前，这个限制不能被描述为区间取交因为这个限制不断在放宽。但是你发现只有没有被任何矩形限制也就是 $[1,10^9]$ 这种区间才会被这个限制影响，分讨一下没被影响的区间就行了。

然后还有注意处理区间交为空的情况，此时需要把这个位置从线段树中剔除，注意这个操作对于 segbeats 存储的信息的影响！我就是这里调了一亿年！

由于 segbeats 的优秀常数跑得比其它单 $\log$ 解法快点。

```cpp
#include <cstdio>
#include <algorithm>
#define lc (p<<1)
#define rc (p<<1|1)
using namespace std;
typedef long long ll;
typedef __int128 lll;
int read(){
	char c=getchar();int x=0;
	while(c<48||c>57) c=getchar();
	do x=x*10+(c^48),c=getchar();
	while(c>=48&&c<=57);
	return x;
}
const int N=100003,M=200003;
const int L=1e9,P=998244353;
const int T=M<<2;
inline void chmn(int &x,int v){if(x>v) x=v;}
inline void chmx(int &x,int v){if(x<v) x=v;}
inline void inc(int &x,int v){if((x+=v)>=P) x-=P;}
inline void dec(int &x,int v){if((x-=v)<0) x+=P;}
int n,res;
int bx[M],nx;
int by[M],ny;
int lx[N],rx[N];
int ly[N],ry[N];
int mn[M],s[M][4];
inline int coe(int i,int t){
	int x=bx[i]-bx[i-1];
	if(t==1) return x;
	if(t==2) return ((ll)x*(x-1)>>1)%P;
	return (((lll)x*(x-1)>>1)*(x-2)/3)%P;
}
int pl[N],pr[N],buc[M];
void sol1(){
	for(int i=0;i<=nx;++i) mn[i]=nx+1;
	for(int i=1;i<=n;++i) chmn(mn[lx[i]-1],rx[i]);
	for(int i=nx-1;~i;--i) chmn(mn[i],mn[i+1]);
	for(int i=1;i<=nx+2;++i)
		for(int c=0;c<=3;++c) s[i][c]=0;
	for(int i=1;i<=nx+1;++i) s[i][0]=1;
	for(int i=nx;i;--i)
		for(int c=1;c<=3;++c){
			s[i][c]=s[i+1][c];
			for(int w=0;w<c;++w)
				s[i][c]=((ll)(s[i+1][w]-s[mn[i]+1][w]+P)*coe(i,c-w)+s[i][c])%P;
		}
	inc(res,s[1][3]);dec(res,s[mn[0]+1][3]);
}
int wl[M],wr[M];
void sol2(){
	for(int i=nx,j=n,l=1,r=ny;i;--i){
		while(j&&lx[pl[j]]>i) chmx(l,ly[pl[j]]),chmn(r,ry[pl[j]]),--j;
		wl[i]=l;wr[i]=r;
	}
	for(int i=1,j=1,l=1,r=ny;i<=nx;++i){
		while(j<=n&&rx[pr[j]]<i) chmx(l,ly[pr[j]]),chmn(r,ry[pr[j]]),++j;
		int sl=l,sr=r;
		chmx(sl,wl[i]);chmn(sr,wr[i]);
		if(sl<=sr) res=(res+(ll)(by[sr]-by[sl-1])*coe(i,2))%P;
	}
}
int lmn[T],lmx[T],lsec[T],lnum[T],tgl[T];
int rmn[T],rmx[T],rsec[T],rnum[T],tgr[T];
int sum[T];bool ban[T],leaf[T];
void pushups(int p){sum[p]=sum[lc]+sum[rc];if(sum[p]>=P) sum[p]-=P;}
void pushupl(int p){
	ban[p]=ban[lc]&&ban[rc];
	lmn[p]=min(lmn[lc],lmn[rc]);
	lmx[p]=max(lmx[lc],lmx[rc]);
	pushups(p);
	if(!ban[p]){
		if(!ban[lc]&&(lmn[lc]<lmn[rc]||ban[rc])){
			lmn[p]=lmn[lc];lnum[p]=lnum[lc];lsec[p]=lsec[lc];
			if(!ban[rc]) chmn(lsec[p],lmn[rc]);
			return;
		}
		if(!ban[rc]&&(lmn[lc]>lmn[rc]||ban[lc])){
			lmn[p]=lmn[rc];lnum[p]=lnum[rc];lsec[p]=lsec[rc];
			if(!ban[lc]) chmn(lsec[p],lmn[lc]);
			return;
		}
		lnum[p]=lnum[lc]+lnum[rc];
		lsec[p]=min(lsec[lc],lsec[rc]);
	}
	else sum[p]=0;
}
void pushupr(int p){
	ban[p]=ban[lc]&&ban[rc];
	rmn[p]=min(rmn[lc],rmn[rc]);
	rmx[p]=max(rmx[lc],rmx[rc]);
	pushups(p);
	if(!ban[p]){
		if(!ban[lc]&&(rmx[lc]>rmx[rc]||ban[rc])){
			rmx[p]=rmx[lc];rnum[p]=rnum[lc];rsec[p]=rsec[lc];
			if(!ban[rc]) chmx(rsec[p],rmx[rc]);
			return;
		}
		if(!ban[rc]&&(rmx[lc]<rmx[rc]||ban[lc])){
			rmx[p]=rmx[rc];rnum[p]=rnum[rc];rsec[p]=rsec[rc];
			if(!ban[lc]) chmx(rsec[p],rmx[lc]);
			return;
		}
		rnum[p]=rnum[lc]+rnum[rc];
		rsec[p]=max(rsec[lc],rsec[rc]);
	}
	else sum[p]=0;
}
void pushup(int p){pushupl(p);pushupr(p);}
void fresh(int p){
	ban[p]=1;sum[p]=0;
	lmn[p]=lmx[p]=1;lsec[p]=nx+1;
	rmn[p]=rmx[p]=nx;rsec[p]=0;
}
void procl(int p,int v){
	if(ban[p]) return;
	inc(sum[p],(ll)lnum[p]*bx[lmn[p]-1]%P);
	if(lmn[p]==lmx[p]) lmx[p]+=v;
	lmn[p]+=v;tgl[p]+=v;
	dec(sum[p],(ll)lnum[p]*bx[lmn[p]-1]%P);
}
void procr(int p,int v){
	if(ban[p]) return;
	dec(sum[p],(ll)rnum[p]*bx[rmx[p]]%P);
	if(rmn[p]==rmx[p]) rmn[p]-=v;
	rmx[p]-=v;tgr[p]+=v;
	inc(sum[p],(ll)rnum[p]*bx[rmx[p]]%P);
}
void pushdown(int p){
	if(leaf[p]||ban[p]) return;
	if(tgl[p]){
		int lim=min(lmn[lc],lmn[rc]);
		if(lmn[lc]==lim||ban[rc]) procl(lc,tgl[p]);
		if(lmn[rc]==lim||ban[lc]) procl(rc,tgl[p]);
		tgl[p]=0;
	}
	if(tgr[p]){
		int lim=max(rmx[lc],rmx[rc]);
		if(rmx[lc]==lim||ban[rc]) procr(lc,tgr[p]);
		if(rmx[rc]==lim||ban[lc]) procr(rc,tgr[p]);
		tgr[p]=0;
	}
}
void gol(int p,int v){
	pushdown(p);
	if(ban[p]||v<=lmn[p]) return;
	if(v<lsec[p]) return procl(p,v-lmn[p]);
	gol(lc,v);gol(rc,v);pushupl(p);
}
void gor(int p,int v){
	pushdown(p);
	if(ban[p]||v>=rmx[p]) return;
	if(v>rsec[p]) return procr(p,rmx[p]-v);
	gor(lc,v);gor(rc,v);pushupr(p);
}
void build(int p=1,int l=1,int r=ny){
	leaf[p]=(l==r);
	tgl[p]=tgr[p]=0;ban[p]=0;
	lmn[p]=lmx[p]=1;lsec[p]=nx+1;
	rmn[p]=rmx[p]=nx;rsec[p]=0;
	lnum[p]=rnum[p]=by[r]-by[l-1];
	sum[p]=(ll)(by[r]-by[l-1])*L%P;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
}
void seqban(int vl,int vr,int p,int l,int r){
	pushdown(p);
	if(rmn[p]>=vl&&lmx[p]<=vr) return;
	if(l==r) return fresh(p);
	int mid=(l+r)>>1;
	seqban(vl,vr,lc,l,mid);
	seqban(vl,vr,rc,mid+1,r);
	pushup(p);
}
void update(int sl,int sr,int vl,int vr,int p=1,int l=1,int r=ny){
	pushdown(p);
	if(sl<=l&&r<=sr){
		seqban(vl,vr,p,l,r);
		gol(p,vl);gor(p,vr);
		return;
	}
	int mid=(l+r)>>1;
	if(sl<=mid) update(sl,sr,vl,vr,lc,l,mid);
	if(sr>mid) update(sl,sr,vl,vr,rc,mid+1,r);
	pushup(p);
}
int query(int sl,int sr,int p=1,int l=1,int r=ny){
	pushdown(p);
	if(ban[p]) return 0;
	if(sl<=l&&r<=sr) return sum[p];
	int mid=(l+r)>>1,res=0;
	if(sl<=mid) inc(res,query(sl,sr,lc,l,mid));
	if(sr>mid) inc(res,query(sl,sr,rc,mid+1,r));
	return res;
}
void sol3(){
	build();
	for(int i=1,j=1,cl=1,cr=ny;i<=nx;++i){
		while(j<=n&&rx[pr[j]]<i){
			int e=pr[j++];
			chmx(cl,ly[e]);chmn(cr,ry[e]);
			if(ly[e]>1) update(1,ly[e]-1,lx[e],rx[e]);
			if(ry[e]<ny) update(ry[e]+1,ny,lx[e],rx[e]);
		}
		int dl=max(wl[i],cl),dr=min(wr[i],cr),tmp=0;
		if(dl<=dr){
			if(wl[i]<cl) inc(tmp,query(wl[i],cl-1));
			if(wr[i]>cr) inc(tmp,query(cr+1,wr[i]));
			inc(tmp,(ll)(by[dr]-by[dl-1])*bx[i-1]%P);
		}
		else inc(tmp,query(wl[i],wr[i]));
		inc(res,(ll)tmp*(bx[i]-bx[i-1])%P);
	}
}
void calc(){
	for(int i=1;i<=nx;++i) buc[i]=0;
	for(int i=1;i<=n;++i) ++buc[lx[i]];
	for(int i=1;i<=nx;++i) buc[i]+=buc[i-1];
	for(int i=1;i<=n;++i) pl[buc[lx[i]]--]=i;
	for(int i=1;i<=nx;++i) buc[i]=0;
	for(int i=1;i<=n;++i) ++buc[rx[i]];
	for(int i=1;i<=nx;++i) buc[i]+=buc[i-1];
	for(int i=1;i<=n;++i) pr[buc[rx[i]]--]=i;
	sol1();sol2();sol3();
}
void solve(){
	n=read();nx=ny=0;res=0;
	for(int i=1;i<=n;++i){
		lx[i]=read();ly[i]=read();
		rx[i]=read();ry[i]=read();
		if(lx[i]>1) bx[++nx]=lx[i]-1;
		if(ly[i]>1) by[++ny]=ly[i]-1;
		bx[++nx]=rx[i];by[++ny]=ry[i];
	}
	bx[++nx]=L;by[++ny]=L;
	sort(bx+1,bx+nx+1);nx=unique(bx+1,bx+nx+1)-bx-1;
	sort(by+1,by+ny+1);ny=unique(by+1,by+ny+1)-by-1;
	for(int i=1;i<=n;++i){
		lx[i]=lower_bound(bx+1,bx+nx+1,lx[i])-bx;
		ly[i]=lower_bound(by+1,by+ny+1,ly[i])-by;
		rx[i]=lower_bound(bx+1,bx+nx+1,rx[i])-bx;
		ry[i]=lower_bound(by+1,by+ny+1,ry[i])-by;
	}
	calc();
	swap(nx,ny);
	for(int i=1;i<=nx||i<=ny;++i) swap(bx[i],by[i]);
	for(int i=1;i<=n;++i) swap(lx[i],ly[i]),swap(rx[i],ry[i]);
	calc();
	printf("%d\n",res);
}
int main(){
	int tc=read();
	while(tc--) solve();
	return 0;
}
```

---

## 作者：ppip (赞：2)

只讨论一竖两横因为三竖是平凡的。

先改为统计不合法的方案数。每个矩形会让每一束线所在维度的的一个前缀或后缀不能取。

考虑对竖线进行扫描线。令 $x=a,y=b,y=c,b<c$ 为三条线的位置，则在扫描的时候，对于每个矩形，若 $a<x_1$ 或者 $a>x_2$，则对 $b,c$ 有一些限制。具体地，有 $c<y_1$，或者 $b>y_2$，或者 $b<y_1$ 且 $c>y_2$。建立以 $b,c$ 取值分别为 $x,y$ 轴的平面直角坐标系，则第三类限制表现为平面上一个矩形，另外两类则是一个正方形被对角线切掉一部分（因为要求 $b<c$）。例如，若 $y_1=4,y_2=6$，则限制如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/fek5iwpu.png)

我们要求的答案为所有限制的并，并且我们需要在扫描线中动态维护这个东西。三角形部分是平凡的，因为只有包含关系。对于左上角的矩形，我们考虑离散化后用线段树维护每个横坐标下的矩形高度，每次减去和三角形相交的部分即可。

具体来说，根据上面的分析，可以发现每个限制的存在时间一定是一个前缀或后缀（存在时间 $<x_1$ 或 $>x_2$），称呼 存在时间为前缀的为 A 类矩形，时间为后缀的为 B 类矩形。首先倒着扫一遍，只加入 A 类矩形，并记录每个 A 类矩形的加入使得哪些 A 类矩形不再有贡献。以此建树后，线段树加入所有根处的 A 类矩形。同时，额外维护一棵线段树存储 B 类矩形的贡献，初始为空。

扫描的过程中，加入 B 类矩形时，往两个线段树里插入（前缀取 max，显然值是单调的所以这部分平凡）。删除 A 类矩形时，求出该 A 类矩形所贡献的区间，将 B 类线段树里的对应区间复制到 AB 类线段树（减去一个该区间的后缀，因为该区间之后的值对应的矩形可能更优），并将该 A 类矩形的儿子全部加入 AB 类线段树中。每次扫完后求和即可。

该维护的正确性是显然的。实现上，区间复制因为复制的是同下标区间，可以直接持久化线段树来方便复制，或者打标记复制。显然，打一个标记会导致子树内的标记失效，并且因为所有操作在两棵树上相同，在 AB 类树上执行操作时一定会先下传标记，然后在 B 类树上修改对应结点，所以这么打标记是正确的。

于是我们就以时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$ 完成了此题。

以下是神 @[b6e0](/user/150522) 提供的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int S1=1<<20;
char buf1[S1],*l1,*r1;
#define getchar() ((l1==r1&&(r1=(l1=buf1)+fread(buf1,1,S1,stdin)),l1!=r1)?*l1++:EOF)
template<typename T=int>inline T read()
{
	T x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
constexpr int S2=1<<20;
char buf2[S2],*l2=buf2;
#define putchar(c) (l2==buf2+S2&&(fwrite(buf2,1,S2,stdout),l2=buf2),*l2++=(c))
int _st[22];
template<typename T>inline void write(T x)
{
	int tp=0;
	do
		_st[++tp]=x%10;
	while(x/=10);
	while(tp)
		putchar(_st[tp--]+'0');
	putchar('\n');
}
constexpr long long mod=998244353;
constexpr int MN=100005;
struct node
{
	int x1,y1,x2,y2;
}a[MN];
struct range
{
	int l,r;
	inline friend range operator&(range x,range y)
	{
		return {max(x.l,y.l),min(x.r,y.r)};
	}
}pre[MN*2];
int A,n,m1,m2,b[MN*2],c[MN*2];
vector<int>v1[MN*2],v2[MN*2],vec[MN];
bool us[MN];
__int128 ans;
struct segt
{
	int l,r,mn[2],mx[2],tg[2];
	long long sum[2];
}T[MN*8];
inline void up(int i)
{
	T[i].mn[0]=T[i<<1].mn[0];
	T[i].mx[0]=T[i<<1|1].mx[0];
	T[i].sum[0]=T[i<<1].sum[0]+T[i<<1|1].sum[0];
	T[i].mn[1]=T[i<<1].mn[1];
	T[i].mx[1]=T[i<<1|1].mx[1];
	T[i].sum[1]=T[i<<1].sum[1]+T[i<<1|1].sum[1];
}
inline void fil(int k,int i,int y)
{
	T[i].mn[k]=T[i].mx[k]=y;
	T[i].sum[k]=(long long)(c[T[i].r+1]-c[T[i].l])*(c[m2]-c[y]);
	T[i].tg[k]=y;
}
inline void cop(int i)
{
	T[i].mn[0]=T[i].mn[1];
	T[i].mx[0]=T[i].mx[1];
	T[i].sum[0]=T[i].sum[1];
	T[i].tg[0]=-1;
}
inline void down(int i)
{
	if(T[i].tg[1])
	{
		fil(1,i<<1,T[i].tg[1]);
		fil(1,i<<1|1,T[i].tg[1]);
		T[i].tg[1]=0;
	}
	if(T[i].tg[0]==-1)
	{
		cop(i<<1);
		cop(i<<1|1);
		T[i].tg[0]=0;
	}
	else if(T[i].tg[0])
	{
		fil(0,i<<1,T[i].tg[0]);
		fil(0,i<<1|1,T[i].tg[0]);
		T[i].tg[0]=0;
	}
}
void build(int i,int l,int r)
{
	T[i]={l,r,{m2,m2},{m2,m2},{0,0},{0,0}};
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
}
void add(int k,int i,int x,int y)
{
	if(T[i].r<=x)
	{
		if(T[i].mx[k]<=y)
			return;
		if(T[i].mn[k]>=y)
		{
			if(k==1&&T[i].l<T[i].r)
				down(i);
			fil(k,i,y);
			return;
		}
		down(i);
		add(k,i<<1|1,x,y);
		add(k,i<<1,x,y);
		up(i);
		return;
	}
	down(i);
	add(k,i<<1,x,y);
	if(x>T[i<<1].r)
		add(k,i<<1|1,x,y);
	up(i);
}
void change(int i,int x,int y,int z)
{
	if(T[i].mx[0]<y)
		return;
	if(T[i].r>x)
	{
		down(i);
		change(i<<1,x,y,z);
		if(x>T[i<<1].r)
			change(i<<1|1,x,y,z);
		up(i);
		return;
	}
	if(T[i].mn[0]<y)
	{
		down(i);
		change(i<<1,x,y,z);
		change(i<<1|1,x,y,z);
		up(i);
		return;
	}
	if(T[i].mn[1]>=z)
	{
		fil(0,i,z);
		return;
	}
	if(T[i].mx[1]<=z)
	{
		cop(i);
		return;
	}
	down(i);
	change(i<<1,x,y,z);
	change(i<<1|1,x,y,z);
	up(i);
}
long long ask(int i,int l,int r)
{
	if(l<=T[i].l&&T[i].r<=r)
		return T[i].sum[0];
	down(i);
	long long ans=0;
	if(l<=T[i<<1].r)
		ans=ask(i<<1,l,r);
	if(r>T[i<<1].r)
		ans+=ask(i<<1|1,l,r);
	return ans;
}
int askv(int i,int x)
{
	if(T[i].l==T[i].r)
		return T[i].mn[0];
	down(i);
	if(x>T[i<<1].r)
		return askv(i<<1|1,x);
	return askv(i<<1,x);
}
int bins(int i,int x)
{
	if(T[i].mn[0]>x)
		return 0;
	if(T[i].l==T[i].r)
		return T[i].l;
	down(i);
	if(T[i<<1|1].mn[0]<=x)
		return bins(i<<1|1,x);
	return bins(i<<1,x);
}
inline void calc()
{
	sort(a+1,a+n+1,[](node x,node y){
		return x.x2<y.x2;
	});
	pre[0]={1,m1-1};
	for(int i=1,j=1;i<m1;i++)
	{
		pre[i]=pre[i-1];
		for(;j<=n&&a[j].x2<i;j++)
			pre[i]=pre[i]&(range){a[j].x1,a[j].x2};
	}
	sort(a+1,a+n+1,[](node x,node y){
		return x.x1>y.x1;
	});
	range now={1,m1-1};
	for(int i=m1-1,j=1;i;i--)
	{
		for(;j<=n&&a[j].x1>i;j++)
			now=now&(range){a[j].x1,a[j].x2};
		range p=pre[i]&(range){1,i-1},q=now&(range){i+1,m1-1};
		if(p.l<=p.r&&q.l<=q.r)
			ans+=(__int128)(b[i+1]-b[i])*(b[p.r+1]-b[p.l])*(b[q.r+1]-b[q.l]);
		if(pre[i].r==m1-1&&q.l<=q.r)
			ans+=(__int128)(b[i+1]-b[i])*(b[i+1]-b[i]-1)/2*(b[q.r+1]-b[q.l]);
		if(p.l<=p.r&&now.l==1)
			ans+=(__int128)(b[i+1]-b[i])*(b[p.r+1]-b[p.l])*(b[i+1]-b[i]-1)/2;
		if(pre[i].r==m1-1&&now.l==1)
			ans+=(__int128)(b[i+1]-b[i])*(b[i+1]-b[i]-1)*(b[i+1]-b[i]-2)/6;
	}
	ans+=(__int128)A*A*(A-1)/2;
	build(1,1,m2-1);
	multiset<int>st1,st2;
	st1.insert(0),st2.insert(m2);
	for(int i=1;i<=n;i++)
	{
		a[i].y1--,a[i].y2++;
		if(a[i].y1&&a[i].y2<m2)
			add(0,1,a[i].y1,a[i].y2);
		v1[a[i].x1].push_back(i);
		st1.insert(a[i].y1),st2.insert(a[i].y2);
		v2[a[i].x2+1].push_back(i);
	}
	map<int,pair<int,int>>mp;
	mp[m2]=make_pair(m2,0);
	for(int I=m1;I;I--)
		for(int J=(int)v1[I].size()-1;~J;J--)
		{
			int i=v1[I][J];
			if(!a[i].y1||a[i].y2==m2)
				continue;
			auto it=mp.lower_bound(a[i].y1);
			if(a[i].y2>=it->second.first)
			{
				us[i]=0;
				continue;
			}
			us[i]=1;
			if(it->first==a[i].y1)
				it++;
			if(it==mp.begin())
			{
				mp[a[i].y1]=make_pair(a[i].y2,i);
				continue;
			}
			auto p=prev(it);
			while(1)
			{
				if(p->second.first<a[i].y2)
				{
					p++;
					break;
				}
				vec[i].push_back(p->second.second);
				if(p==mp.begin())
					break;
				p--;
			}
			mp.erase(p,it);
			mp[a[i].y1]=make_pair(a[i].y2,i);
		}
	for(int i=1;i<m1;i++)
	{
		for(int x:v2[i])
		{
			st1.insert(a[x].y1),st2.insert(a[x].y2);
			if(a[x].y1&&a[x].y2<m2)
			{
				add(0,1,a[x].y1,a[x].y2);
				add(1,1,a[x].y1,a[x].y2);
			}
		}
		for(int x:v1[i])
		{
			st1.erase(st1.find(a[x].y1)),st2.erase(st2.find(a[x].y2));
			if(!us[x]||!a[x].y1||a[x].y2==m2)
				continue;
			change(1,a[x].y1,a[x].y2,askv(1,a[x].y1+1));
			for(int y:vec[x])
				add(0,1,a[y].y1,a[y].y2);
		}
		int p=*st1.rbegin(),q=*st2.begin(),r=bins(1,p);
		if(r>=q-1)
			ans-=(__int128)(b[i+1]-b[i])*A*(A-1)/2;
		else if(p+1<q)
			ans-=(__int128)(b[i+1]-b[i])*(ask(1,r+1,q-1)+(A-1ll+A-c[r+1]+1)*(c[r+1]-1)/2+(c[p+1]-c[r+1]-1ll)*(c[p+1]-c[r+1])/2+(c[m2]-c[q])*(c[m2]-c[q]-1ll)/2);
		else
			ans-=(__int128)(b[i+1]-b[i])*(ask(1,r+1,q-1)+(A-1ll+A-c[r+1]+1)*(c[r+1]-1)/2+(c[p+1]-c[r+1]-1ll+c[p+1]-c[q])*(c[q]-c[r+1])/2+(c[m2]-c[q])*(c[m2]-c[q]-1ll)/2);
	}
	for(int i=1;i<=m1;i++)
		v1[i].clear(),v2[i].clear();
	for(int i=1;i<=n;i++)
		vec[i].clear(),a[i].y1++,a[i].y2--;
}
inline void work()
{
	n=read();
	b[++m1]=1,b[++m1]=A+1;
	c[++m2]=1,c[++m2]=A+1;
	for(int i=1;i<=n;i++)
	{
		a[i].x1=read(),a[i].y1=read(),a[i].x2=read()+1,a[i].y2=read()+1;
		b[++m1]=a[i].x1,b[++m1]=a[i].x2;
		c[++m2]=a[i].y1,c[++m2]=a[i].y2;
	}
	sort(b+1,b+m1+1);
	m1=unique(b+1,b+m1+1)-b-1;
	sort(c+1,c+m2+1);
	m2=unique(c+1,c+m2+1)-c-1;
	for(int i=1;i<=n;i++)
	{
		a[i].x1=lower_bound(b+1,b+m1+1,a[i].x1)-b;
		a[i].x2=lower_bound(b+1,b+m1+1,a[i].x2)-b-1;
		a[i].y1=lower_bound(c+1,c+m2+1,a[i].y1)-c;
		a[i].y2=lower_bound(c+1,c+m2+1,a[i].y2)-c-1;
	}
	calc();
	for(int i=1;i<=n;i++)
		swap(a[i].x1,a[i].y1),swap(a[i].x2,a[i].y2);
	for(int i=1;i<=max(m1,m2);i++)
		swap(b[i],c[i]);
	swap(m1,m2);
	calc();
	write(ans%mod);
	ans=m1=m2=0;
}
int main()
{
	int T=read();
	A=1e9;
	while(T--)
		work();
	fwrite(buf2,1,l2-buf2,stdout);
	return 0;
}
```

---

## 作者：kyEEcccccc (赞：2)

有点营养的题。

很容易做三条竖线，接下来考虑两竖一横。直接枚举横线会变成支持加入区间删除区间维护有多少种方案选择两个点使得任何区间至少包含其一。当然一个想法是线段树分治，以一只 log 的代价转化为只有加入，这个先放着。胡乱离散化一下，又可以转化为点带权但值域只有 $2n$。当然这样会存在线段相同的问题，但是可以通过容斥解决掉。

考虑枚举左侧点算有多少合法的右侧点，首先如果有区间完全在左侧点的左边直接不合法，其次如果右边有俩不交区间那么也不合法。满足这俩的合法左侧点构成一个“左侧点区间”，这是很好求的。考虑其中的某个特定左侧点，发现此时所有合法右侧点也构成一个“右侧点区间”，且“右侧点区间”的左端点是始终不变的——左端点最右的区间的左端点。于是你只需要对于所有左侧点维护【它的“右侧点区间”的右端点】的区间和。考虑当你加入一个区间的时候这个东西会怎么变化，容易发现是前缀取 min。一个朴素想法是 `Segment Tree Beats!`，可惜它不支持撤销，不能套线段树分治，所以我们需要一个更厉害的东西。考虑单侧递归线段树。具体地，这里是支持单点修改，维护后缀 min 的区间和。我们发现它可以随便支持删除——对每个位置维护俩堆即可。于是我们不需要线段树分治。时间复杂度是 $\Theta(n\log^2 n)$。

---

