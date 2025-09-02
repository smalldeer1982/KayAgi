# 『MdOI R5』Squares

## 题目背景

本题不是数据结构题，建议先做 F。

[![1.gif](https://i.postimg.cc/7ZV6xBX6/1.gif)](https://postimg.cc/HrrHz9qD)

## 题目描述

给定平面上的 $n$ 个点，定义平面上的一个区域是好的当且仅当它是一个**边与坐标轴平行的正方形**并且不存在任何一个给定的点被它**严格包含**。再给定 $m$ 次询问，每次给出一个点 $(x,y)$，求出**严格包含** $(x,y)$ 的最大的好区域的边长。如果可以无限大则输出 $-1$。

点 $A$ 被区域 $B$ **严格包含**当且仅当 $A$ 在 $B$ 的内部且不在边界上。

为了减少奇奇怪怪的细节，我们保证所有的 $n+m$ 个点都满足横坐标互不相同，纵坐标互不相同。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m\le 3\times 10^5$，$0\le x,y\le 10^8$。

$\operatorname{Subtask} 1(10\%)$：$n,m\le 10$。

$\operatorname{Subtask} 2(10\%)$：$n,m\le 100$。

$\operatorname{Subtask} 3(20\%)$：$n,m\le 10^3$。

$\operatorname{Subtask} 4(20\%)$：$n,m\le 5\times 10^4$。

$\operatorname{Subtask} 5(20\%)$：$n,m\le 10^5$。

$\operatorname{Subtask} 6(20\%)$：无特殊限制。

#### 样例说明 1

对于第一组询问，左下角为 $(0,0)$，边长为 $4$ 的正方形是严格包含 $(2,2)$ 的好区域中边长最大的。

对于第二组询问，左下角为 $(4,4)$，边长为 $+\infty$ 的正方形是严格包含 $(5,5)$ 的好区域中边长最大的。

## 样例 #1

### 输入

```
4 2
1 0
0 3
4 1
3 4
2 2
5 5```

### 输出

```
4
-1```

# 题解

## 作者：Kubic (赞：13)

称一个好区域是极大的当且仅当它的边界上至少有 $3$ 个点。有结论：一定存在一组最优解，使得它是一个极大好区域。不妨设是左，右，下边界上有点。

枚举下边界上的点，有结论：最多只有一个合法的极大好区域。

也就是说，可能成为答案的极大好区域只有 $O(n)$ 个。

考虑怎么找到一个点 $(x,y)$ 对应的极大好区域。

我们可以考虑钦定这个区域的边长 $l$，分别找到左右两边第一个纵坐标在 $(y,y+l)$ 内的点，设为 $(x_1,y_1),(x_2,y_2)$。

二分出最大的 $l$ 满足 $x_2-x_1\ge l$。如果 $x_2-x_1=l$ 则我们已经求出了极大好区域，否则要么不存在极大好区域，要么存在一个纵坐标为 $y+l$ 的点在极大好区域的角上，找到这个点即可求出极大好区域。可以在主席树上二分，时间复杂度 $O(n\log n)$。

这里有一个减小常数的方法：没有必要对四个方向各做一遍，只需要做 左右上 和 左右下 这两种情况即可，可以证明这样不会漏掉任何极大好区域。

求出这 $O(n)$ 个极大好区域之后，可以考虑用扫描线 + 线段树求出答案。一般的做法是对于每个节点维护一个 set，其中包含当前覆盖这个节点的所有正方形。这样做的时间复杂度是 $O(n\log^2 n)$。

但实际上我们可以利用正方形的性质进行优化。对于每个节点，如果其中有两个正方形 $S_1,S_2$ 满足 $|S_1|>|S_2|$ 且 $S_1$ 的右边界在 $S_2$ 的右边界的右侧，那么显然 $S_2$ 就没用了。

因此我们可以对于每个节点维护一个 deque，里面包含当前覆盖这个节点并且有用的正方形。这个 deque 中的所有正方形满足边长单调递减，且右边界的位置单调递增。加入一个新的正方形时边长比它小的正方形显然都没用了，直接从末尾弹出即可，然后再判断它本身是否有用即可。时间复杂度均摊 $O(n\log n)$。

因此总时间复杂度为 $O(n\log n)$，常数很大。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 300005
#define LIM 10000005
#define mid ((l+r)/2)
#define pb push_back
#define po pop_back
#define gc() (P1==P2 && (P2=(P1=buf)+fread(buf,1,LIM,stdin),P1==P2)?EOF:*P1++)
const int INF1=1e8,INF2=3e8,INF3=5e8;char buf[LIM],*P1=buf,*P2=buf;
int n,m,dsX[N],dsY[N],X[N],Y[N],o[N],ans[N];struct Node {int x,w;};
int tp;struct Sqr {int x,y,w;}z[N*4];vector<Sqr> vc[N];
int cntS,rt1[N],rt2[N];struct Seg {int vl,ch[2];}sg[N*40];
struct Seg1 {int hd;vector<Node> vc;}sg1[N*4];
bool cmp(Sqr x,Sqr y) {return x.x<y.x;}
int rd()
{
	int res=0;char c=0;while(!isdigit(c)) c=gc();
	while(isdigit(c)) res=res*10+(c-48),c=gc();return res;
}
void upd(int p,int &p1,int l,int r,int x,int vl)
{
	sg[p1=++cntS]=sg[p];sg[p1].vl=vl;if(l==r) return;
	if(x<=mid) upd(sg[p].ch[0],sg[p1].ch[0],l,mid,x,vl);
	else upd(sg[p].ch[1],sg[p1].ch[1],mid+1,r,x,vl);
}
int qry1(int p1,int p2,int l,int r,int x,int &vl1,int &vl2)
{
	if(l>=x)
	{
		int t,t1=min(vl1,sg[p1].vl),t2=min(vl2,sg[p2].vl);
		if(dsY[r]-dsY[x]<t1+t2) {vl1=t1;vl2=t2;return -1;}if(l==r) return l;
		t=qry1(sg[p1].ch[0],sg[p2].ch[0],l,mid,x,vl1,vl2);if(~t) return t;
		return qry1(sg[p1].ch[1],sg[p2].ch[1],mid+1,r,x,vl1,vl2);
	}int t=-1;if(x<=mid) t=qry1(sg[p1].ch[0],sg[p2].ch[0],l,mid,x,vl1,vl2);
	if(~t) return t;return qry1(sg[p1].ch[1],sg[p2].ch[1],mid+1,r,x,vl1,vl2); 
}
int qry2(int p1,int p2,int l,int r,int x,int &vl1,int &vl2)
{
	if(r<=x)
	{
		int t,t1=min(vl1,sg[p1].vl),t2=min(vl2,sg[p2].vl);
		if(dsY[x]-dsY[l]<t1+t2) {vl1=t1;vl2=t2;return -1;}if(l==r) return l;
		t=qry2(sg[p1].ch[1],sg[p2].ch[1],mid+1,r,x,vl1,vl2);if(~t) return t;
		return qry2(sg[p1].ch[0],sg[p2].ch[0],l,mid,x,vl1,vl2);
	}int t=-1;if(x>mid) t=qry2(sg[p1].ch[1],sg[p2].ch[1],mid+1,r,x,vl1,vl2); 
	if(~t) return t;return qry2(sg[p1].ch[0],sg[p2].ch[0],l,mid,x,vl1,vl2); 
}
void upd1(int p,int l,int r,int qL,int qR,Node vl)
{
	if(qL>qR) return;
	if(l>=qL && r<=qR)
	{
		while(sg1[p].vc.size()>sg1[p].hd && vl.w>=(--sg1[p].vc.end())->w)
			sg1[p].vc.po();
		if(sg1[p].vc.size()<=sg1[p].hd || vl.x>(--sg1[p].vc.end())->x)
			sg1[p].vc.pb(vl);return;
	}if(qL<=mid) upd1(p*2,l,mid,qL,qR,vl);if(qR>mid) upd1(p*2+1,mid+1,r,qL,qR,vl);
}
int qry(int p,int l,int r,int x,int o)
{
	while(sg1[p].vc.size()>sg1[p].hd && sg1[p].vc[sg1[p].hd].x<o) ++sg1[p].hd;
	int t=0;if(sg1[p].vc.size()>sg1[p].hd) t=sg1[p].vc[sg1[p].hd].w;
	if(l==r) return t;if(x<=mid) return max(t,qry(p*2,l,mid,x,o));
	return max(t,qry(p*2+1,mid+1,r,x,o));
}
int main()
{
	n=rd();m=rd();sg[0].vl=INF2;dsX[0]=dsY[0]=-INF3;
	for(int i=1;i<=n;++i) X[i]=rd(),Y[i]=rd(),dsX[i]=X[i],dsY[i]=Y[i];
	dsX[n+1]=dsY[n+1]=INF3;sort(dsX+1,dsX+n+1);sort(dsY+1,dsY+n+1);
	for(int i=1;i<=n;++i)
	{
		X[i]=lower_bound(dsX+1,dsX+n+1,X[i])-dsX;
		Y[i]=lower_bound(dsY+1,dsY+n+1,Y[i])-dsY;	
	}for(int i=1;i<=n;++i) o[X[i]]=Y[i];
	upd(rt1[0],rt1[0],0,n+1,0,-INF2);upd(rt2[n+1],rt2[n+1],0,n+1,0,-INF2);
	upd(rt1[0],rt1[0],0,n+1,n+1,-INF2);upd(rt2[n+1],rt2[n+1],0,n+1,n+1,-INF2);
	for(int i=1;i<=n;++i) upd(rt1[i-1],rt1[i],0,n+1,o[i],-dsX[i]);
	for(int i=n;i;--i) upd(rt2[i+1],rt2[i],0,n+1,o[i],dsX[i]);
	for(int i=1,vl1,vl2,t;i<=n;++i)
	{
		vl1=vl2=INF2;t=qry1(rt1[i-1],rt2[i+1],0,n+1,o[i],vl1,vl2);
		if(dsY[t]-dsY[o[i]]<vl1+vl2)
		{
			t=dsY[t]-dsY[o[i]];z[++tp]=(Sqr) {-vl1,dsY[o[i]],t};
			z[++tp]=(Sqr) {vl2-t,dsY[o[i]],t};
		}else z[++tp]=(Sqr) {-vl1,dsY[o[i]],vl1+vl2};
		vl1=vl2=INF2;t=qry2(rt1[i-1],rt2[i+1],0,n+1,o[i],vl1,vl2);
		if(dsY[o[i]]-dsY[t]<vl1+vl2)
		{
			t=dsY[o[i]]-dsY[t];z[++tp]=(Sqr) {-vl1,dsY[o[i]]-t,t};
			z[++tp]=(Sqr) {vl2-t,dsY[o[i]]-t,t};
		}else z[++tp]=(Sqr) {-vl1,dsY[o[i]]-vl1-vl2,vl1+vl2};
	}z[++tp]=(Sqr) {dsX[1]-INF2,-1,INF2};z[++tp]=(Sqr) {dsX[n],-1,INF2};
	for(int i=1;i<=m;++i) X[i]=rd(),Y[i]=rd(),dsX[i]=X[i],dsY[i]=Y[i];
	sort(dsX+1,dsX+m+1);sort(dsY+1,dsY+m+1);
	for(int i=1;i<=m;++i)
	{
		X[i]=lower_bound(dsX+1,dsX+m+1,X[i])-dsX;
		Y[i]=lower_bound(dsY+1,dsY+m+1,Y[i])-dsY;	
	}for(int i=1;i<=m;++i) o[X[i]]=Y[i];
	for(int i=1,x;i<=tp;++i)
		x=upper_bound(dsX+1,dsX+m+1,z[i].x)-dsX,vc[x].pb(z[i]);
	for(int i=1,l,r;i<=m;++i)
	{
		sort(vc[i].begin(),vc[i].end(),cmp);
		for(auto j:vc[i])
		{
			l=upper_bound(dsY+1,dsY+m+1,j.y)-dsY;
			r=lower_bound(dsY+1,dsY+m+1,j.y+j.w)-dsY-1;
			upd1(1,1,m,l,r,(Node) {j.x+j.w-1,j.w});
		}ans[i]=qry(1,1,m,o[i],dsX[i]);if(ans[i]>INF1) ans[i]=-1;
	}for(int i=1;i<=m;++i) printf("%d\n",ans[X[i]]);return 0;
}
```

---

## 作者：_maojun_ (赞：3)

这里有一个双 log 卡过去的做法。

---

首先一个极大的正方形左右至少有一边贴着一个点。枚举这个点 $(x_i,y_i)$，不妨假设正方形在右边，左边同理。

那么相当于要找到一个 $\min\limits_{x_i<x_j<x_i+L,y_j>y_i}y_j-\max\limits_{x_i<x_j<x_i+L,y_j<y_i}\ge L$ 的最大的 $L$。

这样的 $L$ 是一个前缀，可二分。按 $y$ 在 $x$ 维上建主席树，维护区间 $y$ 坐标的最大值或最小值，在 $<y_i$ 和 $>y_i$ 的线段树上区间查询，可以做到 $n\log V\log n$。

这里有一个细节是找出的正方形可能上下没有被点限制，这时候不能只保留某一个正方形，应该更新整一个矩形的答案，具体可以参考代码。

找出这 $O(n)$ 个矩形覆盖之后，树套树求答案可以做到 $O(n\log^2n)$。

但是两个东西常数都实在是太大了，本地测要跑 16s+，根本过不去一点。

那么分别优化一下。

前一部分，考虑按 $y$ 扫描线，记 $p_y$ 表示 $y$ 对应的 $x$。$y-1\to y$ 时，在 $<y$ 的线段树中加入 $(p_{y-1},y-1)$（单点修改 $p_{y-1}$ 为 $y-1$），并在 $>y$ 的线段树中删除 $(p_y,y)$（单点修改 $p_y$ 为极大值）。不再需要主席树，可以大大减小常数。使用 zkw 可以卡进 3s。

后面部分，推平非常不友好，于是整体二分，判定答案能否大于 $x$ 等价于大于 $x$ 的矩形是否覆盖到询问点。矩形加单点差可以扫描线做到 $n\log n$，加上整体二分的复杂度就是 $n\log^2n$，常数极小，可以卡进 1s。

于是总共就卡进 4s 的时限了，非常极限。

---

upd 10.19

但是这样还是太极限了一点，我在 luogu 上过的第一发最慢点 3.93s，后面再交几遍又过不了了。

想到了一个优化，前面二分+线段树的本质其实是求一个单调增数组（$x$ 的坐标差）和一个单调减数组（$y$ 的坐标差）较小值的最大值，二分的过程就是找交点。

那么直接在 $x$ 上二分，找到最后一个 $x$ 差不超过 $y$ 差的点，检验该点和下一个，取较大值。

这样把 $\log V$ 变成 $\log n$，跑起来就比较轻松了，最慢点只有 3.13s。

```cpp
const int N=3e5+5;
int n,m,ux[N],uy[N],qx[N],qy[N];

const int O=1e9;
vector<tuple<int,int,int,int,int>>UPD;
namespace PART1{		// 第一部分：找贡献矩形
	int dx[N],dy[N],p[N];
	const int S=N<<2;
	int M,mn[S],mx[S];
	inline void P(int p){mn[p]=min(mn[p<<1],mn[p<<1|1]);}
	inline void B(){
		for(M=1;M<=n;M<<=1);
		fill(mn,mn+S,n+1);
		for(int i=1;i<=n;i++)mn[p[i]+M]=i;
		for(int i=M;i;i--)P(i);
	}
	inline void U1(int p){for(mn[p+=M]=n+1;p>>=1;P(p));}
	inline void ckn(int&x,int y){x>y&&(x=y);}
	inline void ckx(int&x,int y){x<y&&(x=y);}
	inline int Q1(int l,int r){
		int x=n+1;if(l>r)return x;
		for(l+=M-1,r+=M+1;l^r^1;l>>=1,r>>=1){if(~l&1)ckn(x,mn[l^1]);if(r&1)ckn(x,mn[r^1]);}
		return x;
	}
	inline void U2(int p,int k){for(mx[p+=M]=k;p>>=1;ckx(mx[p],k));}
	inline int Q2(int l,int r){
		int x=0;if(l>r)return x;
		for(l+=M-1,r+=M+1;l^r^1;l>>=1,r>>=1){if(~l&1)ckx(x,mx[l^1]);if(r&1)ckx(x,mx[r^1]);}
		return x;
	}
	inline void slv(){
		memcpy(dx+1,ux+1,n<<2);sort(dx+1,dx+n+1);
		memcpy(dy+1,uy+1,n<<2);sort(dy+1,dy+n+1);
		for(int i=1;i<=n;i++)
			p[lower_bound(dy+1,dy+n+1,uy[i])-dy]=lower_bound(dx+1,dx+n+1,ux[i])-dx;
		B();dy[0]=-O;dx[n+1]=dy[n+1]=O;
		for(int i=1;i<=n;i++){
			U1(p[i]);
			int l=p[i],r=n,md,u,d,mx,mn;
			while(l<r){	// 点在左边
				md=l+r+1>>1;
				mn=Q1(p[i]+1,md-1);mx=Q2(p[i]+1,md-1);
				if(dy[mn]-dy[mx]>=dx[md]-dx[p[i]]){
					l=md;u=mn;d=mx;
				}else r=md-1;
			}
			mn=Q1(p[i]+1,l);mx=Q2(p[i]+1,l);
						// 上诉的细节：比如这里贡献矩形是 [pi,l]*[d,u]，贡献为它的较短边长度 l-pi
			if(dx[l]-dx[p[i]]>dy[mn]-dy[mx])
				UPD.emplace_back(dx[l]-dx[p[i]],dx[p[i]],dx[l],dy[d],dy[u]);
			else UPD.emplace_back(dy[mn]-dy[mx],dx[p[i]],dx[l+1],dy[mx],dy[mn]);
			l=1;r=p[i];
			while(l<r){	// 点在右边
				md=l+r>>1;
				mn=Q1(md+1,p[i]-1);mx=Q2(md+1,p[i]-1);
				if(dy[mn]-dy[mx]>=dx[p[i]]-dx[md]){
					r=md;u=mn;d=mx;
				}else l=md+1;
			}
			mn=Q1(l,p[i]-1);mx=Q2(l,p[i]-1);
			if(dx[p[i]]-dx[l]>dy[mn]-dy[mx])
				UPD.emplace_back(dx[p[i]]-dx[l],dx[l],dx[p[i]],dy[d],dy[u]);
			else UPD.emplace_back(dy[mn]-dy[mx],dx[l-1],dx[p[i]],dy[mx],dy[mn]);
			U2(p[i],i);
		}
	}
}
int as[N];
namespace PART2{		// 第二部分：统计答案
	int dx[N],dy[N];
	int ul[N*2],ur[N*2],ud[N*2],uu[N*2],uk[N*2],il[N*2],ir[N*2];
	int qq[N],tq[N],aq[N];
	int tr[N];
	inline void U(int l,int r,int k){for(l--;r>l;r&=r-1)tr[r]+=k;for(;l>r;l&=l-1)tr[l]-=k;}
	inline void D(int l,int r){for(l--;r>l;r&=r-1)tr[r]=0;for(;l>r;l&=l-1)tr[l]=0;}
	inline bool Q(int p){int x=0;for(;p<=m;p+=p&-p)x+=tr[p];return x;}
	void dvd(int l,int r,int ql,int qr){
		if(ql>qr)return;
		if(l==r){for(int i=ql;i<=qr;i++)as[qq[i]]=uk[l];return;}
		int md=l+r>>1,qm=ql;
		stable_partition(il+l,il+r+1,[&](int x){return x<=md;});
		stable_partition(ir+l,ir+r+1,[&](int x){return x<=md;});
		for(int i=ql,tt=0,j=md+1,k=md+1;i<=qr;i++){
			for(;j<=r&&qx[qq[i]]>=ul[il[j]];j++)U(ud[il[j]],uu[il[j]],1);
			for(;k<=r&&qx[qq[i]]>ur[ir[k]];k++)U(ud[ir[k]],uu[ir[k]],-1);
			(Q(qy[qq[i]])?tq[++tt]:qq[qm++])=qq[i];
		}
		for(int i=qm;i<=qr;i++)qq[i]=tq[i-qm+1];
		for(int i=md+1;i<=r;i++)D(ud[i],uu[i]);
		dvd(l,md,ql,qm-1);dvd(md+1,r,qm,qr);
	}
	inline void slv(){
		memcpy(dx+1,qx+1,m<<2);sort(dx+1,dx+m+1);
		memcpy(dy+1,qy+1,m<<2);sort(dy+1,dy+m+1);
		sort(UPD.begin(),UPD.end());
		int t=0;
		for(auto[k,l,r,d,u]:UPD){
			l=lower_bound(dx+1,dx+m+1,l)-dx;
			r=upper_bound(dx+1,dx+m+1,r)-dx-1;
			d=lower_bound(dy+1,dy+m+1,d)-dy;
			u=upper_bound(dy+1,dy+m+1,u)-dy-1;
			if(l<=r&&d<=u){ul[++t]=l;ur[t]=r;ud[t]=d;uu[t]=u;uk[t]=k;}
		}
		for(int i=1;i<=m;i++){
			qx[i]=lower_bound(dx+1,dx+m+1,qx[i])-dx;
			qy[i]=lower_bound(dy+1,dy+m+1,qy[i])-dy;
		}
		iota(qq+1,qq+m+1,1);sort(qq+1,qq+m+1,[&](int x,int y){return qx[x]<qx[y];});
		iota(il+1,il+t+1,1);sort(il+1,il+t+1,[&](int x,int y){return ul[x]<ul[y];});
		iota(ir+1,ir+t+1,1);sort(ir+1,ir+t+1,[&](int x,int y){return ur[x]<ur[y];});
		dvd(1,t,1,m);
	}
}
int main(){
	fread(__i,1,IN,stdin);
	n=rd();m=rd();
	for(int i=1;i<=n;i++){ux[i]=rd();uy[i]=rd();}
	for(int i=1;i<=m;i++){qx[i]=rd();qy[i]=rd();}
	PART1::slv();PART2::slv();
	for(int i=1;i<=m;i++,*__O++=0xa)wr(as[i]>1e8?-1:as[i]);
	fwrite(__o,1,__O-__o,stdout);
	return 0;
}
```

---

## 作者：tzc_wk (赞：3)

首先发现一个性质：对于一组询问，如果答案不是 $-1$，那么必然存在最优正方形满足，要么三个边界上存在给定的点，要么两个边界 + 一个对角上存在给定的点，这是因为如果一个正方形只顶住了两个边界，那么如果这两个边界是邻边的话正方形肯定可以继续扩大，如果是对边的话我们可以将正方形水平方向上移动直到其卡住另一个点或者这两个点之一处于对角位置。

这样我们考虑钦定一个点在边界上，不妨假设是下边界，那么考虑什么样的边长 $l$ 是合法的：考虑纵坐标在 $(y_i,y_i+l)$ 区间中的所有点，找到 $x_i$ 的前驱 $x_j$ 和后继 $x_k$，那么充要条件是 $x_k-x_j>l$。

显然这个 $l$ 满足可二分性，使用主席树上二分可以做到 $O(n\log n)$。具体来说，我们将所有点按 $x$ 从小到大排序，第 $i$ 棵主席树上 $[l,r]$ 区间位置上我们维护前 $i$ 个点中，$y_j\in[l,r]$ 的点里 $x_j$ 的最大值。对后缀也类似地建主席树。这样上文中提到的“前驱”和“后继”就可以表示为两棵主席树上的一段区间 $\min$ 和 $\max$，用类似线段树二分的手段解决即可。

这样二分出 $l$ 之后，这个正方形就唯一确定了，这是因为如果上述“前驱”和“后继”都存在并且差值刚好等于 $l$，那前驱和后继都在正方形边界上，正方形唯一确定。否则的话，正方形不能继续扩大的原因肯定是因为左上角或者右上角有一个点卡住了正方形，也可以确定正方形的位置。

这样相当于有 $O(n)$ 个正方形，每个正方形有个权值，求覆盖每个点的矩形中权值的最大值。使用线段树 + 扫描线可以做到 $O(n\log^2n)$，但是不够优秀。假设我们在 $x$ 方向上扫描线，那么我们发现，对于两个矩形 $A,B$，如果 $A$ 的右边界比 $B$ 靠右并且 $A$ 的边长比 $B$ 小，那么在 $B$ 加入之时 $A$ 就没用了，所以将线段树上每个节点的 set 替换为单调队列，然后每次区间插入时就仿照单调队列的插入即可做到 $O(n\log n)$。

```cpp
const int MAXN=3e5+5;
const int MAXP=MAXN<<6;
const int LIM=3e8;
const int INF=0x3f3f3f3f;
int n,qu,x[MAXN+5],y[MAXN+5],kx[MAXN+5],ky[MAXN+5],pos[MAXN+5];
int qx[MAXN+5],qy[MAXN+5],kqx[MAXN+5],kqy[MAXN+5];
struct HJTree{
	struct node{int ch[2],mn;}s[MAXP+5];
	int r1[MAXN+5],r2[MAXN+5],ncnt;
	void build(int &k,int l,int r){
		if(!k)k=++ncnt;s[k].mn=INF;if(l==r)return;int mid=l+r>>1;
		build(s[k].ch[0],l,mid);build(s[k].ch[1],mid+1,r);
	}
	int modify(int k,int l,int r,int p,int v){
		int z=++ncnt;s[z]=s[k];chkmin(s[z].mn,v);
		if(l==r)return z;int mid=l+r>>1;
		if(p<=mid)s[z].ch[0]=modify(s[k].ch[0],l,mid,p,v);
		else s[z].ch[1]=modify(s[k].ch[1],mid+1,r,p,v);
		return z;
	}
	int query(int k,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return s[k].mn;int mid=l+r>>1;
		if(qr<=mid)return query(s[k].ch[0],l,mid,ql,qr);
		else if(ql>mid)return query(s[k].ch[1],mid+1,r,ql,qr);
		else return min(query(s[k].ch[0],l,mid,ql,mid),query(s[k].ch[1],mid+1,r,mid+1,qr));
	}
	int walk_right(int k1,int k2,int l,int r,int p,int lmn1,int lmn2){
		if(min(s[k1].mn,lmn1)+min(s[k2].mn,lmn2)>=ky[r]-ky[p])return -1;
		if(l==r)return l;int mid=l+r>>1;
		if(p>mid)return walk_right(s[k1].ch[1],s[k2].ch[1],mid+1,r,p,lmn1,lmn2);
		else{
			int t=walk_right(s[k1].ch[0],s[k2].ch[0],l,mid,p,lmn1,lmn2);
			if(~t)return t;
			return walk_right(s[k1].ch[1],s[k2].ch[1],mid+1,r,p,
			min(lmn1,query(s[k1].ch[0],l,mid,max(p,l),mid)),
			min(lmn2,query(s[k2].ch[0],l,mid,max(p,l),mid)));
		}
	}
	int walk_left(int k1,int k2,int l,int r,int p,int rmn1,int rmn2){
		if(min(s[k1].mn,rmn1)+min(s[k2].mn,rmn2)>=ky[p]-ky[l])return -1;
		if(l==r)return l;int mid=l+r>>1;
		if(p<=mid)return walk_left(s[k1].ch[0],s[k2].ch[0],l,mid,p,rmn1,rmn2);
		else{
			int t=walk_left(s[k1].ch[1],s[k2].ch[1],mid+1,r,p,rmn1,rmn2);
			if(~t)return t;
			return walk_left(s[k1].ch[0],s[k2].ch[0],l,mid,p,
			min(rmn1,query(s[k1].ch[1],mid+1,r,mid+1,min(p,r))),
			min(rmn2,query(s[k2].ch[1],mid+1,r,mid+1,min(p,r))));
		}
	}
}T;
struct bar{
	int x,y,l;bar(){x=y=l=0;}
	bar(int _x,int _y,int _l){x=_x;y=_y;l=_l;}
}z[MAXN*4+5];int cnt=0;
int y_qx[MAXN+5],id_qx[MAXN+5],res[MAXN+5];
vector<tuple<int,int,int,int> >qv[MAXN+5];
struct segtree{
	struct node{int l,r,hd;vector<pii>q;}s[MAXN*4+5];
	void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;if(l==r)return;int mid=l+r>>1;
		build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	}
	void insert(int k,int l,int r,int lim,int v){
		if(l<=s[k].l&&s[k].r<=r){
			while(s[k].hd<s[k].q.size()&&s[k].q.back().se<=v)s[k].q.ppb();
			if(s[k].hd==s[k].q.size()||s[k].q.back().fi<=lim)s[k].q.push_back(mp(lim,v));
			return;
		}
		int mid=s[k].l+s[k].r>>1;
		if(r<=mid)insert(k<<1,l,r,lim,v);
		else if(l>mid)insert(k<<1|1,l,r,lim,v);
		else insert(k<<1,l,mid,lim,v),insert(k<<1|1,mid+1,r,lim,v);
	}
	int calc(int k,int x,int y){
		while(s[k].hd<s[k].q.size()&&s[k].q[s[k].hd].fi<x)s[k].hd++;
		return (s[k].hd==s[k].q.size())?0:s[k].q[s[k].hd].se;
	}
	int query(int k,int x,int y){
		if(s[k].l==s[k].r)return calc(k,x,y);int mid=s[k].l+s[k].r>>1;
		return max(calc(k,x,y),(y<=mid)?query(k<<1,x,y):query(k<<1|1,x,y));
	}
}S;
int main(){
	scanf("%d%d",&n,&qu);
	for(int i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
	x[++n]=LIM+1;y[n]=LIM+1;x[++n]=-LIM-1;y[n]=LIM+2;
	x[++n]=LIM+2;y[n]=-LIM-1;x[++n]=-LIM-2;y[n]=-LIM-2;
	for(int i=1;i<=n;i++)kx[i]=x[i],ky[i]=y[i];
	sort(kx+1,kx+n+1);sort(ky+1,ky+n+1);
	for(int i=1;i<=n;i++){
		x[i]=lower_bound(kx+1,kx+n+1,x[i])-kx;
		y[i]=lower_bound(ky+1,ky+n+1,y[i])-ky;
		pos[x[i]]=y[i];
	}
	T.build(T.r1[0],1,n);T.build(T.r2[n+1],1,n);
	for(int i=1;i<=n;i++)T.r1[i]=T.modify(T.r1[i-1],1,n,pos[i],-kx[i]);
	for(int i=n;i;i--)T.r2[i]=T.modify(T.r2[i+1],1,n,pos[i],kx[i]);
	for(int i=1;i<=n-4;i++){
		int p=T.walk_right(T.r1[x[i]-1],T.r2[x[i]+1],1,n,y[i],INF,INF);if(p==-1)p=n;
		int vl=T.query(T.r1[x[i]-1],1,n,y[i],p-1),vr=T.query(T.r2[x[i]+1],1,n,y[i],p-1);
		if(vl+vr<=ky[p]-ky[y[i]])z[++cnt]=bar(-vl,ky[y[i]],vl+vr);
		else z[++cnt]=bar(-vl,ky[y[i]],ky[p]-ky[y[i]]),z[++cnt]=bar(vr-(ky[p]-ky[y[i]]),ky[y[i]],ky[p]-ky[y[i]]);
		p=T.walk_left(T.r1[x[i]-1],T.r2[x[i]+1],1,n,y[i],INF,INF);if(p==-1)p=1;
		vl=T.query(T.r1[x[i]-1],1,n,p+1,y[i]),vr=T.query(T.r2[x[i]+1],1,n,p+1,y[i]);
		if(vl+vr<=ky[y[i]]-ky[p])z[++cnt]=bar(-vl,ky[y[i]]-(vl+vr),vl+vr);
		else z[++cnt]=bar(-vl,ky[y[i]]-(ky[y[i]]-ky[p]),(ky[y[i]]-ky[p])),z[++cnt]=bar(vr-(ky[y[i]]-ky[p]),ky[y[i]]-(ky[y[i]]-ky[p]),ky[y[i]]-ky[p]);
	}
	for(int i=1;i<=qu;i++)scanf("%d%d",&qx[i],&qy[i]),kqx[i]=qx[i],kqy[i]=qy[i];
	sort(kqx+1,kqx+qu+1);sort(kqy+1,kqy+qu+1);
	for(int i=1;i<=qu;i++){
		int _x=lower_bound(kqx+1,kqx+qu+1,qx[i])-kqx;
		int _y=lower_bound(kqy+1,kqy+qu+1,qy[i])-kqy;
		y_qx[_x]=_y;id_qx[_x]=i;
	}
	for(int i=1;i<=cnt;i++){
		int xl=upper_bound(kqx+1,kqx+qu+1,z[i].x)-kqx;
		int xr=lower_bound(kqx+1,kqx+qu+1,z[i].x+z[i].l)-kqx-1;
		int yl=upper_bound(kqy+1,kqy+qu+1,z[i].y)-kqy;
		int yr=lower_bound(kqy+1,kqy+qu+1,z[i].y+z[i].l)-kqy-1;
		if(xl>xr||yl>yr)continue;
		qv[xl].pb(mt(yl,yr,xr,z[i].l));
	}
	S.build(1,1,qu);
	for(int i=1;i<=qu;i++){
		sort(qv[i].begin(),qv[i].end(),[&](auto x,auto y){return get<2>(x)<get<2>(y);});
		for(auto t:qv[i])S.insert(1,get<0>(t),get<1>(t),get<2>(t),get<3>(t));
		res[id_qx[i]]=S.query(1,i,y_qx[i]);
	}
	for(int i=1;i<=qu;i++)printf("%d\n",(res[i]>1.5e8)?-1:res[i]);
	return 0;
}
/*
4 1
1 1
3 3
0 4
6 0
2 2
*/
```



---

