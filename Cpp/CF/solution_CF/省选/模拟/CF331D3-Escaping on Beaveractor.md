# Escaping on Beaveractor

## 题目描述

Don't put up with what you're sick of! The Smart Beaver decided to escape from the campus of Beaver Science Academy (BSA). BSA is a $ b×b $ square on a plane. Each point $ x,y $ $ (0<=x,y<=b) $ belongs to BSA. To make the path quick and funny, the Beaver constructed a Beaveractor, an effective and comfortable types of transport.

The campus obeys traffic rules: there are $ n $ arrows, parallel to the coordinate axes. The arrows do not intersect and do not touch each other. When the Beaveractor reaches some arrow, it turns in the arrow's direction and moves on until it either reaches the next arrow or gets outside the campus. The Beaveractor covers exactly one unit of space per one unit of time. You can assume that there are no obstacles to the Beaveractor.

The BSA scientists want to transport the brand new Beaveractor to the "Academic Tractor" research institute and send the Smart Beaver to do his postgraduate studies and sharpen pencils. They have $ q $ plans, representing the Beaveractor's initial position $ (x_{i},y_{i}) $ , the initial motion vector $ w_{i} $ and the time $ t_{i} $ that have passed after the escape started.

Your task is for each of the $ q $ plans to determine the Smart Beaver's position after the given time.

## 样例 #1

### 输入

```
3 3
0 0 0 1
0 2 2 2
3 3 2 3
12
0 0 L 0
0 0 L 1
0 0 L 2
0 0 L 3
0 0 L 4
0 0 L 5
0 0 L 6
2 0 U 2
2 0 U 3
3 0 U 5
1 3 D 2
1 3 R 2
```

### 输出

```
0 0
0 1
0 2
1 2
2 2
3 2
3 2
2 2
3 2
1 3
2 2
1 3
```

# 题解

## 作者：AtomAlpaca (赞：2)

## 题意

[link](https://codeforces.com/contest/331/problem/D3)

题意简述：在坐标系中给定边界和若干有向线段，每次询问从一个点沿某个方向走 $t$ 时间，碰到有向线段就把前进方向改为这个有向线段的方向，时间耗尽或者碰到边界就停，最终会停在哪个位置。

## 题解

首先一个朴素的想法是，维护每个格子开始往左/右/上/下跳 $2^k$ 步，会跳到那个点上，然后倍增，维护的时候暴力跳，然后查这个点是否在某个有向线段上。

然后我们发现跳到两条线段的交叉点没法判断往哪边走，于是还要维护每个状态是从哪个方向转移来的；然后我们又发现这个办法的复杂度是 $O(b^2 \log t \log n)$ 的，只能通过弱化版，于是考虑优化。

然后我们发现，对于每个点维护是不必要的，因为一条有向线段上的所有点的轨迹是相同的，于是我们考虑转而维护线段。

不妨把每个询问点看作一个长度为 $0$ 的有向线段。维护 $f_{x, y}$ 表示从线段 $x$ 开始，走了除自己之外 $2^y$ 条线段，最后到达了哪个线段；$g_{x,y}$ 表示从线段 $x$ 开始，走完了 $f_{x, y}$ 条线段的路程。

对于 $y \ge 1$ 的情况，我们可以很容易地倍增求出；对于 $y = 0$ 的情况，我们实际上是要求沿着每条线段走，第一个碰到的线段是哪一个。

我们把四个方向上的线段分别求，以向上的线段为例：我们先将所有线段按照两个端点中较小的纵坐标升序排序，依次将每个线段纳入考虑，设这个线段的横坐标范围是 $l\sim r$，则已经纳入考虑的线段中，所有横坐标在此范围内，方向为上，且还没确定答案的线段，碰到的第一个线段一定是当前的这个线段。其余的方向也是类似的求法。

于是我们对每个询问的“线段”不断跳倍增数组，直至没法继续跳。这时还有两种情况：

1. 沿着最后的线段方向一直走，直到时间耗尽；
2. 沿着最后的线段方向一直走，走到另一条线段上，但是剩余时间不够走到这条线段的末尾，所以倍增时没有跳到这条线段上。

对于第二种情况，我们判断出来之后“透支”时间，强制跳到另一条线段上，然后再沿着反方向把时间“补回来”即可。

时间复杂度 $O((n + q)\log t)$，代码写起来略显繁琐。

## 代码

```c++
#include <bits/stdc++.h>
 
typedef long long ll;
const int MAX = 2e5 + 5;
const int MAXX = 51;
const ll INF = 1e15 + 5;
using std::min;
using std::max;
typedef std::multimap <ll, ll> MP;
typedef MP::iterator IT;
 
struct N
{
  ll sx, sy, tx, ty, dx = 0, dy = 0;
} a[MAX];
 
bool cmpx0(ll x, ll y) { return min(a[x].sx, a[x].tx) == min(a[y].sx, a[y].tx) ? x > y : min(a[x].sx, a[x].tx) > min(a[y].sx, a[y].tx); }
bool cmpx1(ll x, ll y) { return max(a[x].sx, a[x].tx) == max(a[y].sx, a[y].tx) ? x > y : max(a[x].sx, a[x].tx) < max(a[y].sx, a[y].tx); }
bool cmpy0(ll x, ll y) { return min(a[x].sy, a[x].ty) == min(a[y].sy, a[y].ty) ? x > y : min(a[x].sy, a[x].ty) > min(a[y].sy, a[y].ty); }
bool cmpy1(ll x, ll y) { return max(a[x].sy, a[x].ty) == max(a[y].sy, a[y].ty) ? x > y : max(a[x].sy, a[x].ty) < max(a[y].sy, a[y].ty); }
 
ll n, b, q;
char op;
ll tm[MAX], h[MAX];
ll f[MAX][MAXX], g[MAX][MAXX];
 
void solve(ll dx, ll dy, bool (*cmp)(ll, ll))
{
  for (int i = 1; i <= n + q; ++i) { h[i] = i; }
  std::sort(h + 1, h + n + q + 1, cmp);
  MP mp; mp.clear();
  for (int i = 1; i <= n + q; ++i)
  {
    if (h[i] <= n)
    {
      ll t1, t2;
      if (dx != 0) { t1 = a[h[i]].sy, t2 = a[h[i]].ty; } else { t1 = a[h[i]].sx, t2 = a[h[i]].tx; }
      if (t1 > t2) { std::swap(t1, t2); }
      IT i1 = mp.lower_bound(t1), i2 = mp.upper_bound(t2);
      for (IT j = i1; j != i2; mp.erase(j++))
      {  
        ll p = j -> second;
        f[p][0] = h[i]; g[p][0] = abs(a[p].tx - a[h[i]].tx) + abs(a[p].ty - a[h[i]].ty);
      }
    }
    if (a[h[i]].dx == dx and a[h[i]].dy == dy)
    {
      mp.insert({dx != 0 ? a[h[i]].ty : a[h[i]].tx, h[i]});
    }
  }
}
 
int main()
{
  scanf("%lld%lld", &n, &b);
  for (int i = 1; i <= n; ++i)
  {
    scanf("%lld%lld%lld%lld", &a[i].sx, &a[i].sy, &a[i].tx, &a[i].ty); 
    a[i].dx = a[i].tx - a[i].sx == 0 ? 0 : a[i].tx - a[i].sx > 0 ? 1 : -1; 
    a[i].dy = a[i].ty - a[i].sy == 0 ? 0 : a[i].ty - a[i].sy > 0 ? 1 : -1;
  }
  scanf("%lld", &q);
  for (int i = n + 1; i <= n + q; ++i)
  {
    scanf("%lld%lld %c %lld", &a[i].sx, &a[i].sy, &op, &tm[i]); a[i].tx = a[i].sx; a[i].ty = a[i].sy;
    if (op == 'L') { --a[i].dx; } if (op == 'R') { ++a[i].dx; } if (op == 'U') { ++a[i].dy; } if (op == 'D') { --a[i].dy; }
  }
  solve(-1, 0, cmpx0); solve(1, 0, cmpx1); solve(0, -1, cmpy0); solve(0, 1, cmpy1);
  for (int i = 1; i <= MAXX - 1; ++i)
  {
    for (int j = 1; j <= n + q; ++j)
    {
      f[j][i] = f[f[j][i - 1]][i - 1];
      g[j][i] = std::min(INF, g[j][i - 1] + g[f[j][i - 1]][i - 1]);
    }
  }
  for (int i = n + 1; i <= n + q; ++i)
  {
    int p = i;
    for (int j = MAXX - 1; j >= 0; --j)
    {
      if (!f[p][j]) { continue; }
      if (g[p][j] <= tm[i]) { tm[i] -= g[p][j]; p = f[p][j]; }
    }
    if (f[p][0] and tm[i] >= a[p].dx * (a[f[p][0]].tx - a[p].tx) + a[p].dy * (a[f[p][0]].ty - a[p].ty))
    {
      tm[i] -= g[p][0]; p = f[p][0];
    }
    printf("%lld %lld\n", std::min(std::max(a[p].tx + a[p].dx * tm[i], 0ll), b),
                          std::min(std::max(a[p].ty + a[p].dy * tm[i], 0ll), b));
  }
  return 0;
}
```



---

## 作者：MyukiyoMekya (赞：2)

思路应该很显然，只要到达一个箭头上后接下来的路径都确定了。

所以可以直接倍增预处理出每个箭头的尾巴位置开始起飞经过 $2^j$ 个箭头后到达的哪个箭头以及距离时间和。

当然，边界就只能到边界，特殊处理一下。

难点在于怎么处理出某个箭头到达的第一个箭头是哪个箭头，这个可以用 `std::set` 维护扫描线，所有横着的箭头的终点处理一遍，竖着的处理一遍。注意这里横着的也可能到达横着的，竖着的同理。

然后就是对于每个询问找出他第一个到达的箭头是哪个，这个可以在上面扫描线的同时处理。

然后就先倍增跳箭头，直到没时间了或者到边界了然后就讨论：

1. 到了边界
2. 还能跳到下一个箭头上
3. 在前往下一个箭头的中途就没时间了。

总时间复杂度 $\mathcal O((n+q)\log t_i)$ ，代码实现精细一点的话应该不长，~~我的实现就无脑一点~~

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define int long long
#define ALL(x) (x).begin(),(x).end()
#define ln std::puts("")
#define lsp std::putchar(32)
#define pb push_back
#define MP std::make_pair
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
template <class t>inline bool ckmin(t&x,t y){if(x>y){x=y;return 1;}return 0;}
template <class t>inline bool ckmax(t&x,t y){if(x<y){x=y;return 1;}return 0;}
const int MaxN=1e5+50;
const int Lim=1e16;
struct Node{int u,v,x,y,dir;}R[MaxN],C[MaxN],A[MaxN];
struct Edge{int x,l,r,opt,idx;inline bool operator < (const Edge &nt) const
{return x<nt.x;}};
int ansx[MaxN],ansy[MaxN];
struct Query{int x,y,tm,opt,idx,to,dir;}Rq[MaxN],Cq[MaxN],Bq[MaxN];
inline bool cmpR(Node a,Node b){return a.y<b.y;}
inline bool cmpC(Node a,Node b){return a.x<b.x;}
inline bool cmpRq(Query a,Query b){return a.y<b.y;}
inline bool cmpCq(Query a,Query b){return a.x<b.x;}
int n,m,B,q,N,nq,mq,bn;
int nxt[MaxN];
#define fi first
#define se second
#define IT std::set<std::pair<int,int> >::iterator
int up[MaxN][62],s[MaxN][62];
inline int Add(int x,int y){return (x+y)>=Lim?Lim:(x+y);}
inline int dis(int x,int y)
{
	if(x>n+m&&y>n+m)return 0;
	if(x<=n+m&&y<=n+m)return std::abs(A[x].x-A[y].x)+std::abs(A[x].y-A[y].y);
	if(y==n+m+1)return A[x].x-1;
	if(y==n+m+2)return B-A[x].x;
	if(y==n+m+4)return A[x].y-1;
	return B-A[x].y;
}
inline void go(int x,int sx,int sy,int z,int &ex,int &ey)
{
	if(x<=n)
	{
		if(A[x].u<A[x].x)ex=sx+z;
		else ex=sx-z;
		ey=sy;
	}
	else
	{
		if(A[x].v<A[x].y)ey=sy+z;
		else ey=sy-z;
		ex=sx;
	}
	ckmin(ex,B),ckmax(ex,1LL),ckmin(ey,B),ckmax(ey,1LL);
}
inline void goout(int x,int sx,int sy,int z,int &ex,int &ey)
{
	if(x==n+m+1)ex=std::max(1LL,sx-z),ey=sy;
	else if(x==n+m+2)ex=std::min(B,sx+z),ey=sy;
	else if(x==n+m+4)ey=std::max(1LL,sy-z),ex=sx;
	else ey=std::min(B,sy+z),ex=sx;
}
signed main(void)
{
	read(q,B),++B;
	for(int i=1;i<=q;++i)
	{
		Node X;read(X.u,X.v,X.x,X.y),++X.u,++X.v,++X.x,++X.y;
		if(X.v==X.y)R[++n]=X;else C[++m]=X;
	}
	std::sort(R+1,R+n+1,cmpR),std::sort(C+1,C+m+1,cmpC);
	N=n+m+4; // 1 left 2 right 3 up 4 down
	nxt[n+m+1]=n+m+1,nxt[n+m+2]=n+m+2,nxt[n+m+3]=n+m+3,nxt[n+m+4]=n+m+4;
	for(int i=1;i<=n;++i)R[i].dir=R[i].u<R[i].x?2:1;
	for(int i=1;i<=m;++i)C[i].dir=C[i].v<C[i].y?3:4;
	{int T=0;for(int i=1;i<=n;++i)A[++T]=R[i];
	for(int i=1;i<=m;++i)A[++T]=C[i];}
	int Q;read(Q);
	for(int i=1;i<=Q;++i)
	{
		char opt[5];
		Query cu;read(cu.x,cu.y);std::scanf("%s",opt);read(cu.tm),cu.idx=i;
		cu.to=-1,++cu.x,++cu.y;
		if(*opt=='L'||*opt=='R')
		{
			if(*opt=='L')cu.opt=-1;
			else cu.opt=+1;
			Rq[++nq]=cu;
		}
		else
		{
			if(*opt=='U')cu.opt=+1;
			else cu.opt=-1;
			Cq[++mq]=cu;
		}
	}
	std::sort(Rq+1,Rq+nq+1,cmpRq),std::sort(Cq+1,Cq+mq+1,cmpCq);
	for(int i=1;i<=nq;++i)Rq[i].dir=Rq[i].opt>0?2:1;
	for(int i=1;i<=mq;++i)Cq[i].dir=Cq[i].opt>0?3:4;
	{// Edged Row
		std::set<std::pair<int,int> > S;
		std::vector<Edge> dr;
		for(int i=1;i<=n;++i)
			dr.pb((Edge){R[i].y,R[i].u,R[i].x,+1,i}),
			dr.pb((Edge){R[i].y+1,R[i].u,R[i].x,-1,i});
		for(int i=1;i<=m;++i)
			dr.pb((Edge){std::min(C[i].v,C[i].y),C[i].u,C[i].x,+1,i+n}),
			dr.pb((Edge){std::max(C[i].v,C[i].y)+1,C[i].u,C[i].x,-1,i+n});
		for(auto &i:dr)if(i.l>i.r)std::swap(i.l,i.r);
		std::sort(ALL(dr));
		reg int pos=-1;
		for(int i=1;i<=n;++i)
		{
			while(pos+1<(int)dr.size()&&dr[pos+1].x<=R[i].y)
			{
				++pos;
				if(dr[pos].opt>0)
				{
					S.insert(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.insert(MP(dr[pos].r,dr[pos].idx));
				}
				else
				{
					S.erase(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.erase(MP(dr[pos].r,dr[pos].idx));
				}
			}
			if(R[i].u<R[i].x)
			{
				IT it=S.upper_bound(MP(R[i].x,1e9));
				if(it==S.end())nxt[i]=n+m+2;
				else nxt[i]=it->se;
			}
			else
			{
				IT it=S.lower_bound(MP(R[i].x,0));
				if(it==S.begin())nxt[i]=n+m+1;
				else nxt[i]=(--it)->se;
			}
		}
		pos=-1,S.clear();
		for(int i=1;i<=nq;++i)
		{
			while(pos+1<(int)dr.size()&&dr[pos+1].x<=Rq[i].y)
			{
				++pos;
				if(dr[pos].opt>0)
				{
					S.insert(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.insert(MP(dr[pos].r,dr[pos].idx));
				}
				else
				{
					S.erase(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.erase(MP(dr[pos].r,dr[pos].idx));
				}
			}
			if(Rq[i].opt>0)
			{
				IT it=S.lower_bound(MP(Rq[i].x,0));
				if(it==S.end())Rq[i].to=n+m+2;
				else Rq[i].to=it->se;
			}
			else
			{
				IT it=S.upper_bound(MP(Rq[i].x,1e9));
				if(it==S.begin())Rq[i].to=n+m+1;
				else Rq[i].to=(--it)->se;
			}
		}
	}
	{// Edged Col
		std::set<std::pair<int,int> > S;
		std::vector<Edge> dr;
		for(int i=1;i<=n;++i)
			dr.pb((Edge){std::min(R[i].u,R[i].x),R[i].v,R[i].y,+1,i}),
			dr.pb((Edge){std::max(R[i].u,R[i].x)+1,R[i].v,R[i].y,-1,i});
		for(int i=1;i<=m;++i)
			dr.pb((Edge){C[i].x,C[i].v,C[i].y,+1,i+n}),
			dr.pb((Edge){C[i].x+1,C[i].v,C[i].y,-1,i+n});
		for(auto &i:dr)if(i.l>i.r)std::swap(i.l,i.r);
		std::sort(ALL(dr));
		reg int pos=-1;
		for(int i=1;i<=m;++i)
		{
			while(pos+1<(int)dr.size()&&dr[pos+1].x<=C[i].x)
			{
				++pos;
				if(dr[pos].opt>0)
				{
					S.insert(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.insert(MP(dr[pos].r,dr[pos].idx));
				}
				else
				{
					S.erase(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.erase(MP(dr[pos].r,dr[pos].idx));
				}
			}
			if(C[i].v<C[i].y)
			{
				IT it=S.upper_bound(MP(C[i].y,1e9));
				if(it==S.end())nxt[i+n]=n+m+3;
				else nxt[i+n]=it->se;
			}
			else
			{
				IT it=S.lower_bound(MP(C[i].y,0));
				if(it==S.begin())nxt[i+n]=n+m+4;
				else nxt[i+n]=(--it)->se;
			}
		}
		pos=-1,S.clear();
		for(int i=1;i<=mq;++i)
		{
			while(pos+1<(int)dr.size()&&dr[pos+1].x<=Cq[i].x)
			{
				++pos;
				if(dr[pos].opt>0)
				{
					S.insert(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.insert(MP(dr[pos].r,dr[pos].idx));
				}
				else
				{
					S.erase(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.erase(MP(dr[pos].r,dr[pos].idx));
				}
			}
			if(Cq[i].opt>0)
			{
				IT it=S.lower_bound(MP(Cq[i].y,0));
				if(it==S.end())Cq[i].to=n+m+3;
				else Cq[i].to=it->se;
			}
			else
			{
				IT it=S.upper_bound(MP(Cq[i].y,1e9));
				if(it==S.begin())Cq[i].to=n+m+4;
				else Cq[i].to=(--it)->se;
			}
		}
	}
	for(int i=1;i<=nq;++i)Bq[++bn]=Rq[i];
	for(int i=1;i<=mq;++i)Bq[++bn]=Cq[i];
	for(int i=1;i<=N;++i)up[i][0]=nxt[i],s[i][0]=dis(i,nxt[i]);
	for(int k=1;k<62;++k)for(int i=1;i<=N;++i)
		up[i][k]=up[up[i][k-1]][k-1],s[i][k]=Add(s[i][k-1],s[up[i][k-1]][k-1]);
	for(int i=1;i<=bn;++i)
	{
		if(!Bq[i].tm)
		{
			ansx[Bq[i].idx]=Bq[i].x,ansy[Bq[i].idx]=Bq[i].y;
			continue;
		}
		reg int w=Bq[i].tm,to=Bq[i].to,x=Bq[i].x,y=Bq[i].y,I=Bq[i].idx;
		reg int dir=Bq[i].dir;
		if(to<=n+m&&w>std::abs(x-A[to].x)+std::abs(y-A[to].y))
		{
			w-=std::abs(x-A[to].x)+std::abs(y-A[to].y);
			x=A[to].x,y=A[to].y,dir=A[to].dir;
			for(int k=61;to<=n+m&&~k;--k)
				if(up[to][k]<=n+m&&w>s[to][k])
					w-=s[to][k],to=up[to][k],
					x=A[to].x,y=A[to].y,dir=A[to].dir;
			to=nxt[to];
		}
		if(to>n+m)
		{
			goout(to,x,y,w,ansx[I],ansy[I]);
			continue;
		}
		if(dir==1)
		{
			int tp=std::max(A[to].u,A[to].x);ckmin(tp,x);
			if(w<=x-tp)ansx[I]=x-w,ansy[I]=y;
			else go(to,tp,y,w-(x-tp),ansx[I],ansy[I]);
		}
		else if(dir==2)
		{
			int tp=std::min(A[to].u,A[to].x);ckmax(tp,x);
			if(w<=tp-x)ansx[I]=x+w,ansy[I]=y;
			else go(to,tp,y,w-(tp-x),ansx[I],ansy[I]);
		}
		else if(dir==4)
		{
			int tp=std::max(A[to].v,A[to].y);ckmin(tp,y);
			if(w<=y-tp)ansy[I]=y-w,ansx[I]=x;
			else go(to,x,tp,w-(y-tp),ansx[I],ansy[I]);
		}
		else
		{
			int tp=std::min(A[to].v,A[to].y);ckmax(tp,y);
			if(w<=tp-y)ansy[I]=y+w,ansx[I]=x;
			else go(to,x,tp,w-(tp-y),ansx[I],ansy[I]);
		}
	}
	for(int i=1;i<=Q;++i)write(ansx[i]-1),lsp,write(ansy[i]-1),ln;
	return 0;
}
```



---

## 作者：_SeeleVollerei_ (赞：1)

*3000 独立做出。

显然从一个点出发，肯定是一开始一直直线走，直到碰到一个箭头后面的路径就固定了。

考虑对每个箭头预处理它的路径。

首先是每个箭头走出去碰到的第一个其他的箭头。

一种暴力的想法是直接上主席树，然后每次二分一下去扫，复杂度 $O(n\log^2n)$ 。

还有一种想法是，比如处理 x 坐标从小到大的箭头，跑一遍扫描线，按照 x 坐标从大王小枚举，然后线段树维护每个 y 坐标上一个出现的箭头是哪个，复杂度 $O(n\log n)$ 。

因为我写了第二种都跑了 2.7s ，所以第一种理论上无法通过此题。

注意每个查询也要求第一个箭头的位置，离线下来一起扫描线即可。

那么就可以求出这个路径了，暴力的话就每次跳下一个箭头。

注意到 $t\le 10^{15}$ ，考虑优化。

这种暴力跳的东西通常可以考虑倍增。

一种想法是直接倍增每个箭头的末端走 $2^i$ 到的地方，但是这个东西不好转移因为会涉及到不在箭头的结点。

考虑预处理每个箭头末端往后走 $2^i$ 个箭头后，到哪个箭头，以及路程总长，然后暴力跳就好了。

总码长 8.28k ，可能是我写丑了。

https://codeforces.ml/contest/331/submission/157524171

---

## 作者：sunkuangzheng (赞：0)

$\textbf{CF331D *3000}$

> - $m \times m$ 平面上有 $n$ 条**不交**的有向线段。一个点有自己的位置 $(x,y)$ 和方向 $v$ 两个属性。单位时间内点的移动规则：
>   > - 如果 $(x,y)$ 在有向线段上，则向该方向移动一个单位，并把 $v$ 改为为该方向。
>   > - 否则，向 $v$ 方向移动一个单位。
>   > - 如果该移动会导致点走出 $m \times m$ 平面，则不移动。
> - 有 $q$ 次查询，每次给定 $x,y,v,t$，询问点 $((x,y),v)$ 在 $t$ 个单位时间后的位置。
> - $1 \le n,q,m \le 10^5,1 \le t \le 10^{\color{red}15}$。

注意到从一条有向线段的任意一个点出发，都会到达同一条线段。如果我们把一条线段看作一个点，把它向沿这个线段走到的终到点连边，由于每个点出边唯一，会得到一棵基环森林。

当然我们还需要处理时间问题，即怎么设置基环森林的边权。由于从两条不同线段 $a,b$ 出发可能会到达同一条线段 $c$ 的不同位置，我们需要给一个线段找一个代表点，并让边权包含走到这个代表点的代价。很显然线段结尾是这个代表点的最佳选择位置，即，$x \to y$ 边权 $z$ 表示从 $x$ 的末尾走到 $y$ 的末尾需要 $z$ 的时间。


考虑有了这个基环森林怎么求解，这个问题很经典。维护从 $u$ 出发前跳 $2^k$ 步需要的时间 $to_{u,k}$（注意由于 $2^k \le 10^{15}$，这个值会爆 long long，需要开 __int128 或者对 $10^{18}$ 取 $\min$。），然后倍增求解，最终到达一个点 $v$ 满足剩余时间 $t \le to_{v,0}$，然后简单分讨即可得到答案。

对于往前走走到边界的线段，解决方法很简单：向自己连一条边权为 $\infty$ 的边，这样就可以在这里停住了。

最后的问题是怎么求出每条线段会走到哪里，可以扫描线解决。由于线段有四个方向，需要扫描四遍。

时间复杂度 $\mathcal O((n+q) \log n)$。

代码写起来很精神污染而且细节非常多，感觉 $^*3000$ 的难度主要给到代码上了。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 07.05.2024 18:16:44
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 2e5+5; 
const ll inf = 1e16;
using namespace std;
int T,n,m,tot,to[60][N],q,x,y; vector<pair<int,ll>> g[N];
struct pt{int x,y;}a[N],b[N]; char c,rc[N];
ll sm[60][N],ak[N]; vector<tuple<int,int,int,int>> fx[N],fy[N];
struct seg{
    int t[N*4],tg[N*4];
    void cg(int s,int k){t[s] = tg[s] = k;}
    void pd(int s){if(tg[s] != -1) cg(s*2,tg[s]),cg(s*2+1,tg[s]),tg[s] = -1;}
    void upd(int s,int l,int r,int ql,int qr,int k){
        if(ql <= l && r <= qr) return cg(s,k);
        int mid = (l + r) / 2; pd(s);
        if(ql <= mid) upd(s*2,l,mid,ql,qr,k); if(qr > mid) upd(s*2+1,mid+1,r,ql,qr,k);
    }int get(int s,int l,int r,int x){
        if(l == r) return t[s];
        int mid = (l + r) / 2; pd(s);
        if(x <= mid) return get(s*2,l,mid,x); else return get(s*2+1,mid+1,r,x);
    }void clr(){memset(t,0,sizeof(t)),memset(tg,-1,sizeof(tg));}
}t;
pair<ll,ll> dis(int i,int j){
    ll w = 0,pw = 0;
    if(!j) return {inf,inf};
    if(rc[i] == 'U' || rc[i] == 'D'){
        w = min(abs(b[i].y - a[j].y),abs(b[i].y - b[j].y));  
        if(a[i].x == a[j].x && min(a[j].y,b[j].y) <= b[i].y && b[i].y <= max(a[j].y,b[j].y)) w = 0; 
    }
    else{
        w = min(abs(b[i].x - a[j].x),abs(b[i].x - b[j].x));   
        if(a[i].y == a[j].y && min(a[j].x,b[j].x) <= b[i].x && b[i].x <= max(a[j].x,b[j].x)) w = 0; 
    }
    return {abs(b[i].y - b[j].y) + abs(b[i].x - b[j].x),w};
}void add(int i,int j){to[0][i] = (j ? j : i),sm[0][i] = dis(i,j).first;}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= n;i ++){
        cin >> a[i].x >> a[i].y >> b[i].x >> b[i].y;
        if(a[i].x == b[i].x)
            fx[a[i].x].emplace_back(1,min(a[i].y,b[i].y),max(a[i].y,b[i].y),i),
            fy[b[i].y].emplace_back(0,a[i].x,a[i].x,i),fy[a[i].y].emplace_back(1,a[i].x,a[i].x,i),
            rc[i] = (b[i].y < a[i].y ? 'D' : 'U');
        else 
            fy[a[i].y].emplace_back(1,min(a[i].x,b[i].x),max(a[i].x,b[i].x),i),
            fx[b[i].x].emplace_back(0,a[i].y,a[i].y,i),fx[a[i].x].emplace_back(1,a[i].y,a[i].y,i),
            rc[i] = (b[i].x < a[i].x ? 'L' : 'R');
    }cin >> q;
    for(int i = 1;i <= q;i ++){
        cin >> x >> y >> c >> ak[i]; int p = i + n;
        a[p].x = b[p].x = x,a[p].y = b[p].y = y,rc[p] = c;
        if(c == 'L') fx[x].emplace_back(0,y,-1,p);
        if(c == 'R') fx[x].emplace_back(0,y,-1,p);
        if(c == 'D') fy[y].emplace_back(0,x,-1,p);
        if(c == 'U') fy[y].emplace_back(0,x,-1,p);
    }
    //left
    t.clr();
    for(int i = 0;i <= m;i ++)
        for(auto [tp,l,r,x] : fx[i]){
            if(!tp && rc[x] == 'L') add(x,t.get(1,0,m,l));
            if(r != -1) t.upd(1,0,m,l,r,x);
        }
    //right
    t.clr();
    for(int i = m;i >= 0;i --)
        for(auto [tp,l,r,x] : fx[i]){
            if(!tp && rc[x] == 'R') add(x,t.get(1,0,m,l));
            if(r != -1) t.upd(1,0,m,l,r,x);
        }
    //down
    t.clr();
    for(int i = 0;i <= m;i ++)
        for(auto [tp,l,r,x] : fy[i]){
            if(!tp && rc[x] == 'D') add(x,t.get(1,0,m,l));
            if(r != -1) t.upd(1,0,m,l,r,x);
        }
    //up
    t.clr();
    for(int i = m;i >= 0;i --)
        for(auto [tp,l,r,x] : fy[i]){
            if(!tp && rc[x] == 'U') add(x,t.get(1,0,m,l));
            if(r != -1) t.upd(1,0,m,l,r,x);
        }
    for(int j = 1;j <= 59;j ++) for(int i = 1;i <= n + q;i ++)
        sm[j][i] = min(inf,sm[j-1][i] + sm[j-1][to[j-1][i]]),to[j][i] = to[j-1][to[j-1][i]];
    for(int i = 1;i <= q;i ++){
        int p = i + n; 
        auto ed = [&](int p,ll k){
            auto [x,y] = dis(p,to[0][p]); 
            auto fk = [&](int a,int x,int y,ll k){
                if(rc[a] == 'L') return pt{(int)max(0ll,x - k),y};
                if(rc[a] == 'R') return pt{(int)min((ll)m,x + k),y};
                if(rc[a] == 'D') return pt{x,(int)max(0ll,y - k)};
                if(rc[a] == 'U') return pt{x,(int)min((ll)m,y + k)};
                return assert(0),pt{-1,-1};
            }; 
            if(k <= y) return fk(p,b[p].x,b[p].y,k);
            else{
                auto [w,v] = fk(p,b[p].x,b[p].y,y);
                return fk(to[0][p],w,v,k - y);
            }
        };
        for(int j = 59;j >= 0;j --) if(sm[j][p] <= ak[i]) ak[i] -= sm[j][p],p = to[j][p];
        auto [fx,fy] = ed(p,ak[i]); 
        cout << fx << " " << fy << "\n";
    }
}

```

---

## 作者：skyskyCCC (赞：0)

## 前言。
怪不得 $D1$ 和 $D2$ 的题解这么少，原来大部分人都是直接干掉 $D3$ 然后顺带着过了弱化版啊。事实上前面的弱化版对于这道终极版本没有什么大的启发，所以可以忽略，有兴趣的可以翻翻我的博客找到那两个弱化版。

这道题的主要思路是：基环树、倍增、线段树、扫描线。额，这么多东西叠在一起就不简单了。
## 分析。
通过对于前两道题的发现，我们这个题要在对数的数据结构中解决。所以一个自然的想法是：离线询问，考虑计算从每条路径的终点以及每组询问的起点出发，找到下一次需要转移路径的地点。

具体来说，我们可以将题目中的 $4$ 个方向分开做，对于任意一个方向，我们把所有路径及询问按照这个方向进行排序，关键字为 $x$ 坐标或 $y$ 坐标，这样就可以直接用扫描线进行处理。如果扫到一条线段，则将它所覆盖的区间插入到这个方向建出来的线段树，计算答案时直接查询这个子树即可。那么如果走到边界，可以离开，那么我们考虑将边界这一个特殊情况单独开出来，就是将这个点进行“自我建边”。就是在离开网格的地方建一个点，并把它的出边指向自己。这样每个点的出度都是 $1$ 显然就是一个很明显的内向基环树森林，这样倍增的思路就很明显了。我们令 $dis\left[x\right]\left[y\right]$ 表示从 $x$ 出发走 $2^y$ 点的距离，那么就类似于我们之前的两个弱化版的思路，我们将它看做一个“伪循环节”，询问的时候如果走到环上，那么相当于进入循环节，所以直接用时间对环的长度取模，然后继续倍增即可。

当然我们思路有了，但是实现还是有问题的。

首先是维护的问题，显然如果我们直接按照最基本的方式进行维护，我们很难写出一个比较简单的代码，调试起来也相当复杂。那么我们直接暴力跳，用一个可以推出 $b$ 的 $a$ 去建出这个树即可。

其次，怎么处理路径相交从而使得需要在路径中进行转向到另一个树上呢？这里我们可以采用在这个交点处插入一个新节点。这个节点相当于一个中转站。

最后特判一下在路径上的点进行询问的情况即可。

代码如下，仅供参考：
```
#include<cmath>
#include<iostream>
#include<algorithm> 
using namespace std;
int n,b,x,y,q;
long long t[100005];
int tot,to[500005],val[500005];
char s[5];
int sum1[500005][65];
long long sum2[500005][65];
int ansx[500005],ansy[500005];
int dx[5]={0,1,-1,0,0};
int dy[5]={0,0,0,-1,1};
struct node{
	int x1,y1,x2,y2;
	int num,id;
	int maxx,minx,maxy,miny;
	bool flag;
	void get(){
		maxx=max(x1,x2);
		minx=min(x1,x2);
		maxy=max(y1,y2);
		miny=min(y1,y2);
	}
}a[500005],a2[500005];//1R 2L 3D 4U 
struct tree{
	int l,r,tag,v;
}tre[800005];
void build(int i,int l,int r){
	tre[i].tag=-1;
	tre[i].l=l;
	tre[i].r=r;
	tre[i].v=-1;
	if(l==r){
	    return;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
}
void give(int i){
	if (tre[i].tag!=-1){
		if(tre[i].l==tre[i].r){
		    tre[i].v=tre[i].tag;
		}
		else{
		    tre[i<<1].tag=tre[i].tag;
			tre[i<<1|1].tag=tre[i].tag;
		}
		tre[i].tag=-1;
	}
}
void cheak(int i,int l,int r,int v){
	int L=tre[i].l,R=tre[i].r;
	if (l>R||L>r){
	    return;
	}
	give(i);
	if (l<=L&&R<=r){
	    if (L==R){
		    tre[i].v=v;
		}
		else tre[i].tag=v;
		return;
	}
	cheak(i<<1,l,r,v);
	cheak(i<<1|1,l,r,v);
}
int query(int i,int pos){
	int L=tre[i].l,R=tre[i].r;
	give(i);
	if(L==R){
	    return tre[i].v;
	}
	int mid=L+R>>1;
	if (mid>=pos){
	    return query(i<<1,pos);
	}
	else return query(i<<1|1,pos);
}
void addedg(int x,int y,int v){
    to[x]=y;
	val[x]=v;
}
bool cmp1(node a,node b){
    return (a.maxx==b.maxx)?a.flag<b.flag:a.maxx>b.maxx;
}
bool cmp2(node a,node b){
    return (a.minx==b.minx)?a.flag<b.flag:a.minx<b.minx;
}
bool cmp3(node a,node b){
    return (a.miny==b.miny)?a.flag<b.flag:a.miny<b.miny;
}
bool cmp4(node a,node b){
    return (a.maxy==b.maxy)?a.flag<b.flag:a.maxy>b.maxy;
}
int main(){
	cin>>n>>b;
	for (int i=1;i<=n;i++){
		cin>>a[i].x1>>a[i].y1>>a[i].x2>>a[i].y2;
		if (a[i].x2==a[i].x1&&a[i].y1==a[i].y2){
		    n--;
			i--;
			continue;
		}
		if(a[i].x1<a[i].x2){
		    a[i].num=1;
		}
		else if(a[i].x1>a[i].x2){
		    a[i].num=2;
		}
		else if(a[i].y1<a[i].y2){
		    a[i].num=4;
		}
		else if(a[i].y1>a[i].y2){
		    a[i].num=3;
		}
		a[i].flag=0;
		a[i].id=i;
	}
	cin>>q;
	for (int i=1;i<=q;i++){
		cin>>x>>y>>s>>t[i];
		a[i+n].x1=x;
		a[i+n].x2=x;
		a[i+n].y1=y;
		a[i+n].y2=y;
		a[i+n].flag=1;
		a[i+n].id=i+n;
		if(s[0]=='R'){
		    a[i+n].num=1;
		}
		else if(s[0]=='L'){
		    a[i+n].num=2;
		}
		else if(s[0]=='D'){
		    a[i+n].num=3;
		}
		else a[i+n].num=4;
	}
	tot=n+q;
	for (int i=1;i<=n+q;i++){
	    a[i].get();
	}
	//R
	sort(a+1,a+1+n+q,cmp1);
	build(1,0,b);
	for (int i=1;i<=n+q;i++){
		if(a[i].flag==0){
			if(a[i].num==2){
			    cheak(1,a[i].y1,a[i].y2,i);
			}
			else if(a[i].num==4){
			    cheak(1,a[i].y1,a[i].y2,i);
			}
			else if(a[i].num==3){
			    cheak(1,a[i].y2,a[i].y1,i);
			}
		}
		if (a[i].num==1){
			int u=query(1,a[i].y1);	
			tot++;
			a[tot].id=tot;
			a[tot].y1=a[i].y1;
			if (u!=-1){
				if(a[u].num==2){
				    addedg(tot,a[u].id,max(0,a[i].x2-a[u].x2)),a[tot].x1=max(a[i].x2,a[u].x2);
				}
				else addedg(tot,a[u].id,abs(a[u].y2-a[i].y2)),a[tot].x1=a[u].x1;
				addedg(a[i].id,tot,max(0,a[u].x2-a[i].x2));
			}
			else{
				a[tot].x1=b;
				addedg(a[i].id,tot,b-a[i].x2);
				addedg(tot,tot,1);
			}
		
		}
	}
	//L
	sort(a+1,a+1+n+q,cmp2);
	build(1,0,b);
	for (int i=1;i<=n+q;i++){
		if(a[i].flag==0){
			if(a[i].num==1){
			    cheak(1,a[i].y1,a[i].y2,i);
			}
			else if(a[i].num==4){
			    cheak(1,a[i].y1,a[i].y2,i);
			}
			else if(a[i].num==3){
			    cheak(1,a[i].y2,a[i].y1,i);
			}
		}
		if (a[i].num==2){
			int u=query(1,a[i].y1);
			tot++;
			a[tot].id=tot;
			a[tot].y1=a[i].y1;
			if (u!=-1){
				if(a[u].num==1){
				    addedg(tot,a[u].id,max(0,a[u].x2-a[i].x2)),a[tot].x1=min(a[i].x2,a[u].x2);
				}
				else addedg(tot,a[u].id,abs(a[u].y2-a[i].y2)),a[tot].x1=a[u].x1;
				addedg(a[i].id,tot,max(0,a[i].x2-a[u].x2));
			}
			else{
				a[tot].x1=0;
				addedg(a[i].id,tot,a[i].x2);
				addedg(tot,tot,1);
			}
			
		}
	}
	//D
	sort(a+1,a+1+n+q,cmp3);
	build(1,0,b);
	for (int i=1;i<=n+q;i++){
		if(a[i].flag==0){
			if(a[i].num==2){
			    cheak(1,a[i].x2,a[i].x1,i);
			}
			else if(a[i].num==4){
			    cheak(1,a[i].x1,a[i].x2,i);
			}
			else if(a[i].num==1){
			    cheak(1,a[i].x1,a[i].x2,i);
			}
		}
		if (a[i].num==3){
			int u=query(1,a[i].x1);
			tot++;
			a[tot].id=tot;
			a[tot].x1=a[i].x1;
			if (u!=-1){
				if(a[u].num==4){
				    addedg(tot,a[u].id,max(0,a[u].y2-a[i].y2)),a[tot].y1=min(a[i].y2,a[u].y2);
				}
				else addedg(tot,a[u].id,abs(a[u].x2-a[i].x2)),a[tot].y1=a[u].y1;
				addedg(a[i].id,tot,max(0,a[i].y2-a[u].y2));
			}
			else{
				a[tot].y1=0;
				addedg(a[i].id,tot,a[i].y2);
				addedg(tot,tot,1);
			}
		}
	}
	//U
	sort(a+1,a+1+n+q,cmp4);
	build(1,0,b);
	for (int i=1;i<=n+q;i++){
		if (a[i].flag==0){
			if(a[i].num==2){
			    cheak(1,a[i].x2,a[i].x1,i);
			}
			else if(a[i].num==3){
			    cheak(1,a[i].x1,a[i].x2,i);
			}
			else if(a[i].num==1){
			    cheak(1,a[i].x1,a[i].x2,i);
			}
		}
		if (a[i].num==4){
			int u=query(1,a[i].x1);
			tot++;
			a[tot].id=tot;
			a[tot].x1=a[i].x1;
			if (u!=-1){
				if(a[u].num==3){
				    addedg(tot,a[u].id,max(0,a[i].y2-a[u].y2)),a[tot].y1=max(a[i].y2,a[u].y2);
				}
				else addedg(tot,a[u].id,abs(a[u].x2-a[i].x2)),a[tot].y1=a[u].y1;
				addedg(a[i].id,tot,max(0,a[u].y2-a[i].y2));
			}
			else{
				a[tot].y1=b;
				addedg(a[i].id,tot,b-a[i].y2);
				addedg(tot,tot,1);
			}
			
		}
	}
	for (int i=n+q+1;i<=tot;i++){
	    a[i].x2=a[i].x1;
		a[i].y2=a[i].y1;
	}
	for (int i=1;i<=tot;i++){
	    a2[a[i].id]=a[i];
	}
	for (int i=1;i<=tot;i++){
	    sum2[i][0]=val[i];
		sum1[i][0]=to[i];
	}
	for (int i=1;i<=60;i++){
		for (int j=1;j<=tot;j++){
			sum1[j][i]=sum1[sum1[j][i-1]][i-1];
			sum2[j][i]=sum2[j][i-1]+sum2[sum1[j][i-1]][i-1];
			if(sum2[j][i]>1e18){
			    sum2[j][i]=2e18;
			}
		}
	}
	for (int i=1;i<=tot;i++){
		if(a[i].flag==1){
			int pos=a[i].id,dis;
			long long iidd=t[a[i].id-n];
			for (int i=60;i>=0;i--){
				if (iidd-sum2[pos][i]>=0){
					iidd-=sum2[pos][i];
					pos=sum1[pos][i];
				}
			}
			if (a2[pos].x1<a2[to[pos]].x2) dis=1;
			else if (a2[pos].x1>a2[to[pos]].x2) dis=2;
			else if (a2[pos].y1<a2[to[pos]].y2) dis=4;
			else if (a2[pos].y1>a2[to[pos]].y2) dis=3;
			ansx[a[i].id-n]=a2[pos].x2+dx[dis]*iidd; 
			ansy[a[i].id-n]=a2[pos].y2+dy[dis]*iidd;
			
		}
	}
	for (int i=1;i<=q;i++){
		cout<<ansx[i]<<" "<<ansy[i]<<"\n";
	}
	return 0;
}
```
## 后记。
调了 $2$ 天，真的是一道练习重构代码的好题。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

