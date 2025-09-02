# [ICPC 2015 WF] Window Manager

## 题目描述

过去几年，用户界面技术发生了一场革命。多年来，键盘和鼠标一直是与计算机交互的工具。但随着智能手机和平板电脑的推出，人们越来越多地通过在屏幕上敲击和移动手指来使用电脑。这自然导致了用户界面设计的新范式。一个重要的原则是显示器上的对象遵守“物理”定律。在这个问题中，您将看到一个例子。

您已被聘请为 window manager 构建一个模拟器，用于高级手机制造商（Advanced Cellular Manufacturers，ACM）的下一代智能手机。他们生产的每款手机都有一个矩形屏幕，可以完全显示零个或多个矩形窗口。也就是说，没有窗口超出屏幕边界或与任何其他窗口重叠。模拟器必须支持以下命令。

`OPEN x y w h` —— 打开一个具有左上角坐标 $(x,y)$、宽度 $w$ 像素和高度 $h$ 像素的新窗口。

`CLOSE x y` —— 关闭一个打开的窗口，其中包括 $(x,y)$ 处的像素。这允许用户点击窗口上的任意位置以关闭窗口。

`RESIZE x y w h` —— 将包含 $(x,y)$ 处像素的窗口尺寸设置为宽度 $w$  像素和高度 $h$  像素。窗口的左上角不移动。

`MOVE x y dx dy` —— 移动包含 $(x,y)$ 处像素的窗口。移动是水平方向上的 $dx$ 像素或垂直方向上的 $dy$ 像素。$dx$ 和 $dy$ 中最多有一个为非零。

![](https://cdn.luogu.com.cn/upload/image_hosting/3zw4uj2x.png)

 _（图 1：移动示例）_ 

ACM 对 `MOVE` 命令特别自豪。正在移动的窗口可能会“撞上”另一个窗口。在这种情况下，第一个窗口将以相同的方向尽可能远地推动第二个窗口，就像这些窗口是物理对象一样。此行为可能会层叠 —— 移动的窗口可能会遇到其他窗口，这些窗口也会根据需要被推送。图 $1$ 显示了一个有三个窗口的示例，其中窗口 A 向右移动，推动其他两个窗口。

## 说明/提示

时间限制：1000 毫秒，内存限制：1048576 kB。

该题出自：2015 年国际大学生编程大赛（ACM-ICPC）世界总决赛。

## 样例 #1

### 输入

```
320 200
OPEN 50 50 10 10
OPEN 70 55 10 10
OPEN 90 50 10 10
RESIZE 55 55 40 40
RESIZE 55 55 15 15
MOVE 55 55 40 0
CLOSE 55 55
CLOSE 110 60
MOVE 95 55 0 -100
```

### 输出

```
Command 4: RESIZE - window does not fit
Command 7: CLOSE - no window at given position
Command 9: MOVE - moved 50 instead of 100
2 window(s):
90 0 15 15
115 50 10 10
```

# 题解

## 作者：nullqtr_pwp (赞：2)

笔者正在准备中考，同时被一些高中物理卷子污染了，所以《运动与力》含量较高，但是极不标准。

注意到 $q$ 很小，每次都可以暴力扫与之前存活矩形的情况，操作一二三直接模拟即可。move 操作难点在于读懂。我们这样考虑：给予初始矩形在某个方向的动能。我们要模拟的是转化为机械能的距离。

在运动的部分一定是初始矩形向右黏上的一堆矩形，它们构成了连通块，第一次碰撞时只要在另一个维度上的坐标区间有交集就会黏上。

考虑暴力维护每一次碰撞，维护当前剩余动能。我们希望求出在一次碰撞内可以释放的动能 $nxt$。初始 $nxt$ 等于剩余动能的最大值。对于当前连通块中已有的矩形，对 $nxt$ 的更新就是在该运动方向上到达边界的距离，$nxt$ 要对此取 $\min$。

那么先将这些连通块中的所有矩形移动 $nxt$，可以黏上的就是在该运动方向上坐标相邻的，但是黏上一个新的之后可能又会由这个新的黏上更多相邻的。具体考虑黏上就是在另一个维度上的坐标区间有交集。这是一个图论问题，$u\to v$ 表示 $u$ 进入连通块后会把 $v$ 黏上，这是一个 dag，直接跑一遍拓扑排序就可以得出新加上的点。

如果没有新黏上的点，就终止过程，因为动能释放不出去了。否则继续这个循环。

由于最多 $256$ 次操作，所以这样的过程时间是可以接受的。
```cpp
// 私は猫です

#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define inf 1000000000
#define infll 1000000000000000000ll
#define pii pair<int,int>
#define rep(i,a,b,c) for(int i=(a);i<=(b);i+=(c))
#define per(i,a,b,c) for(int i=(a);i>=(b);i-=(c))
#define F(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define dF(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define cmh(sjy) while(sjy--)
#define lowbit(x) (x&(-x))
#define HH printf("\n")
#define eb emplace_back
#define poly vector<int>
using namespace std;
ll read(){
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
template<typename T>inline void chkmax(T &x,const T &y){ x=std::max(x,y); }
template<typename T>inline void chkmin(T &x,const T &y){ x=std::min(x,y); }
const int mod=998244353,maxn=500005;
int tot,n;
int xmx,ymx,nowtim;
struct node{
	int x,y,l,r,del=0;
	bool bound(){ return x>=0&&x+l-1<=xmx-1&&y>=0&&y+r-1<=ymx-1; }
	bool check(int p,int q){ return x<=p&&p<x+l&&y<=q&&q<y+r; }
};
inline bool chkx(node a,node b){ return max(a.x,b.x)<min(a.x+a.l,b.x+b.l); }
inline bool chky(node a,node b){ return max(a.y,b.y)<min(a.y+a.r,b.y+b.r); }
inline bool chk(node a,node b){ return (chkx(a,b)&&chky(a,b)); }
node a[305];
set<int>surv;
int find(int x,int y){
	for(int id:surv)if(a[id].check(x,y))return id;
	return -1;
}
void Open(){
	int x=read(),y=read(),l=read(),r=read();
	node tmp={x,y,l,r,0};
	for(int id:surv)if(chk(tmp,a[id]))return printf("Command %d: OPEN - window does not fit\n",nowtim),void();
	if(!tmp.bound())return printf("Command %d: OPEN - window does not fit\n",nowtim),void();
	a[++tot]=tmp;
	surv.insert(tot);
}
void Resize(){
	int x=read(),y=read(),l=read(),r=read(),qwq=find(x,y);
	if(qwq<0)return printf("Command %d: RESIZE - no window at given position\n",nowtim),void();
	node nxt={a[qwq].x,a[qwq].y,l,r};
	if(!nxt.bound())return printf("Command %d: RESIZE - window does not fit\n",nowtim),void();
	for(int id:surv)if(id!=qwq&&chk(nxt,a[id]))return printf("Command %d: RESIZE - window does not fit\n",nowtim),void();
	a[qwq]=nxt;
}
void Close(){
	int x=read(),y=read(),qwq=find(x,y);
	if(qwq<0)return printf("Command %d: CLOSE - no window at given position\n",nowtim),void();
	surv.erase(qwq),a[qwq].del=1;
}
void Output(){
	printf("%d window(s):\n",(int)surv.size());
	for(int i:surv)printf("%d %d %d %d\n",a[i].x,a[i].y,a[i].l,a[i].r);
}
int ins[305],q[505];
void Move(){
	int x=read(),y=read(),dx=read(),dy=read(),qwq=find(x,y);
	if(qwq<0)return printf("Command %d: MOVE - no window at given position\n",nowtim),void();
	x=dx,y=dy,memset(ins,0,sizeof ins),ins[qwq]=1;
	for(;;){
		if(!x&&!y)break;
		int nxt=abs(x^y);
		for(int i:surv)if(ins[i]){
			if(x<0)chkmin(nxt,abs(a[i].x));
			if(x>0)chkmin(nxt,abs(xmx-1-(a[i].x+a[i].l-1)));
			if(y<0)chkmin(nxt,abs(a[i].y));
			if(y>0)chkmin(nxt,abs(ymx-1-(a[i].y+a[i].r-1)));
		}
		for(int i:surv)if(ins[i])for(int j:surv)if(!ins[j]){
			if(x>0&&chky(a[i],a[j])&&a[j].x>(a[i].x+a[i].l-1))chkmin(nxt,abs(a[j].x-(a[i].x+a[i].l-1)-1));
			if(x<0&&chky(a[i],a[j])&&(a[j].x+a[j].l-1)<a[i].x)chkmin(nxt,abs(a[i].x-(a[j].x+a[j].l-1)-1));
			if(y>0&&chkx(a[i],a[j])&&a[j].y>(a[i].y+a[i].r-1))chkmin(nxt,abs(a[j].y-(a[i].y+a[i].r-1)-1));
			if(y<0&&chkx(a[i],a[j])&&(a[j].y+a[j].r-1)<a[i].y)chkmin(nxt,abs(a[i].y-(a[j].y+a[j].r-1)-1));
		}
		if(x<0){
			for(int i:surv)if(ins[i])a[i].x-=nxt;
		}
		if(x>0){
			for(int i:surv)if(ins[i])a[i].x+=nxt;
		}
		if(y<0){
			for(int i:surv)if(ins[i])a[i].y-=nxt;
		}
		if(y>0){
			for(int i:surv)if(ins[i])a[i].y+=nxt;
		}
		int flag=0,qL=1,qR=0;
		for(int i:surv)if(ins[i])q[++qR]=i;
		while(qL<=qR){
			const int u=q[qL++];
			for(int v:surv)if(!ins[v]){
				if(x>0&&chky(a[u],a[v])&&a[u].x+a[u].l==a[v].x)ins[v]=1,q[++qR]=v,flag=1;
				if(x<0&&chky(a[u],a[v])&&a[v].x+a[v].l==a[u].x)ins[v]=1,q[++qR]=v,flag=1;
				if(y>0&&chkx(a[u],a[v])&&a[u].y+a[u].r==a[v].y)ins[v]=1,q[++qR]=v,flag=1;
				if(y<0&&chkx(a[u],a[v])&&a[v].y+a[v].r==a[u].y)ins[v]=1,q[++qR]=v,flag=1;
			}
		}
		if(x>0)x-=nxt;
		if(x<0)x+=nxt;
		if(y>0)y-=nxt;
		if(y<0)y+=nxt;
		if(!flag)break;
	}
    if(!x&&!y)return;
	printf("Command %d: MOVE - moved %d instead of %d\n",nowtim,abs(dx+dy-x-y),abs(dx+dy));
}
void solve(){
	xmx=read(),ymx=read();
	string op;
	while(cin>>op){
		++nowtim;
		if(op=="OPEN")Open();
		if(op=="RESIZE")Resize();
		if(op=="CLOSE")Close();
		if(op=="MOVE")Move();
	}
	Output();
}
signed main(){
	const int zsy=1;
	F(____,1,zsy)solve();
}
```

---

## 作者：极寒神冰 (赞：1)

`OPEN`，`CLOSE`，`RESIZE` 操作都是直接模拟。下面只考虑 `MOVE`。

为了方便，假设 $d_y=0$。（如果是 $d_x=0$ 可以将整个坐标轴翻转变成 $d_y=0$）

一种比较直接的想法是，令 $f_i$ 表示第 $i$ 个矩形移动后的坐标。先无视边界正着 $dp$ 出每个矩形的坐标。再根据边界倒着 DP 求出每个矩形的真实移动距离，然后再正着一次 DP。

具体地：

每次向右移动，对于两个窗口 $A,B$，如果 $A$ 和 $B$ 占据的 $y$ 轴区间有交，且 $A$ 在 $B$ 的左边，那么 $A$ 的移动将会使 $B$ 一起运动，考虑连一条 $A\to B$ 的边。

于是这样可以得到一张有向图 $G$，根据定义，这张图 $G$ 显然是个 DAG。

于是先对每个窗口求出 $\lim_i$ 表示左端点最大能移动多少。

然后按照拓扑逆序（横坐标从大到小）进行 DP。

假设 $A$ 的宽度为 $w_A$，则 $\lim_A=W-w_A$，对于所有 $A$ 连向的顶点 $B$ 更新 $\lim_A=\min(\lim_A,\lim_B-w_A)$。

而目标窗口 $P$ 实际的移动距离 $d'=\min(d,\lim_P-x_P)$ （$x_P$ 为 $P$ 点左端位置）

确定了 $d'$ 之后就可以直接正着求出每个窗口的真实位置。

具体地：$x_P=x_P+d'$，然后对于所有的 $A$ 连向的顶点 $B$ 更新 $x_A=\max(x_A,x_B+w_B)$。

`Move` 的时间复杂度为 $\mathcal O(n^2)$。

总时间复杂度为 $\mathcal O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--) 
using namespace std;
struct node
{
	int x,y,xx,yy,id;
	inline node (int X=0,int Y=0,int XX=0,int YY=0,int I=0):x(X),y(Y),xx(XX),yy(YY),id(I) {}
	inline int operator <(const node &A)const
	{
		return id<A.id;
	}
	inline int checkin(const node &A)
	{
		return x<=A.x&&A.x+A.xx<=x+xx&&y<=A.y&&A.y+A.yy<=y+yy;
	}
	inline int checkint(const node &A)
	{
		return x<A.x+A.xx&&A.x<x+xx&&y<A.y+A.yy&&A.y<y+yy;
	}
}all,pt[1111];
int n,tim;
inline int find_id(int x,int y)
{
	R(i,1,n) if(pt[i].checkin(node(x,y,1,1,0))) return i;
	return -1;
}
inline int Open(const node &A)
{
	if(!all.checkin(A)) return 0;
	R(i,1,n) if(pt[i].checkint(A)) return 0;
	pt[++n]=A;
	return 1;
}
inline void Close(int id)
{
	pt[id]=pt[n--];
}
inline int Resize(int id,int xx,int yy)
{
	node t(pt[id].x,pt[id].y,xx,yy,pt[id].id);
	if(!all.checkin(t)) return 0;
	R(i,1,n) if(i!=id&&pt[i].checkint(t)) return 0;
	pt[id]=t;
	return 1;
}
inline int ckmin(int &x,const int y)
{
	return x>y?x=y,1:0;
}
inline int ckmax(int &x,const int y)
{
	return x<y?x=y,1:0;
}
vector<int>e[266];

inline void transx()
{
	R(i,1,n) pt[i].x=all.xx-pt[i].x-pt[i].xx;
}
inline void transxy()
{
	swap(all.xx,all.yy);
	R(i,1,n) swap(pt[i].x,pt[i].y),swap(pt[i].xx,pt[i].yy);
}
int dd;

inline void solve(int id,int d)
{
	static int in[266],lim[266];
	R(i,1,n) e[i].clear(),in[i]=0;
	deque<int>q;
	vector<int>v;
	R(i,1,n) R(j,1,n) if(pt[i].x<pt[j].x&&pt[i].y<pt[j].y+pt[j].yy&&pt[j].y<pt[i].y+pt[i].yy) e[i].emplace_back(j),++in[j];
	R(i,1,n) if(!in[i]) q.emplace_back(i);
	while(q.size())
	{
		int u=q.front();
		v.emplace_back(u);
		q.pop_front();
		for(int v:e[u]) if(!--in[v]) q.emplace_back(v);
	}
	L(i,0,n-1) 
	{
		int u=v[i];
		lim[u]=all.xx;
		for(int v:e[u]) ckmin(lim[u],lim[v]);
		lim[u]-=pt[u].xx;
	}
	dd=min(d,lim[id]-pt[id].x);
	pt[id].x+=dd;
	for(int u:v)
		for(int v:e[u]) ckmax(pt[v].x,pt[u].x+pt[u].xx);
}
inline void Move(int id,int dx,int dy)
{
	if(dx>0) solve(id,dx);
	if(dx<0) 
	{
		transx();
		solve(id,-dx);
		transx();
	}
	if(dy>0)
	{
		transxy();
		solve(id,dy);
		transxy();
	}
	if(dy<0)
	{
		transxy();
		transx();
		solve(id,-dy);
		transx();
		transxy();
	}
}
inline void print()
{
	cout<<n<<" window(s):\n";
	sort(pt+1,pt+n+1);
	R(i,1,n) cout<<pt[i].x<<" "<<pt[i].y<<" "<<pt[i].xx<<" "<<pt[i].yy<<'\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>all.xx>>all.yy;
	int cnt=0;
	string opt;		
	int x,y,xx,yy;
	while(cin>>opt)
	{
		++cnt;
		if(opt[0]=='O')
		{
			cin>>x>>y>>xx>>yy;
			if(!Open(node(x,y,xx,yy,++tim)))
			{
				cout<<"Command "<<cnt<<": "<<opt<<" - "<<"window does not fit"<<'\n';
			}
		}
		if(opt[0]=='C')
		{
			cin>>x>>y;
			int t=find_id(x,y);
			if(~t) Close(t);
			else 
			{
				cout<<"Command "<<cnt<<": "<<opt<<" - "<<"no window at given position"<<'\n';
			}
		}
		if(opt[0]=='R')
		{
			cin>>x>>y>>xx>>yy;
			int t=find_id(x,y);
			if(~t) 
			{
				if(!Resize(t,xx,yy)) 
				{
					cout<<"Command "<<cnt<<": "<<opt<<" - "<<"window does not fit"<<'\n';
				}
			}
			else
			{
				cout<<"Command "<<cnt<<": "<<opt<<" - "<<"no window at given position"<<'\n';
			}
		}
		if(opt[0]=='M')
		{
			cin>>x>>y>>xx>>yy;
			int t=find_id(x,y);
			if(~t)
			{
				int d=xx+yy;
				d=abs(d);
				if(d)
				{
					Move(t,xx,yy);
					if(d!=dd) 
					{
						cout<<"Command "<<cnt<<": "<<opt<<" - "<<"moved "<<dd<<" instead of "<<d<<'\n';
					}
				}
			}
			else
			{
				cout<<"Command "<<cnt<<": "<<opt<<" - "<<"no window at given position"<<'\n';
			}
		}
	}
	print();
}
```

---

