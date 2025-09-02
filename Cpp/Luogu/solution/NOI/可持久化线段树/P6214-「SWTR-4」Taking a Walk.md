# 「SWTR-4」Taking a Walk

## 题目背景

小 A 喜欢在广场上散步。

有一次在小 A 散步的时候，由于思考得过于投入，他不小心撞在了电线杆上。

于是就有了这道题目（当然是假的）。

## 题目描述

小 A 和 好友小 Y 站在一个平面上，他们的初始坐标分别是 $(Ax_0,Ay_0)$ 和 $(Bx_0,By_0)$。

当然，站着实在是太无聊了，所以他们会不停地移动。

准确来说，小 A 共有 $n$ 次移动，小 Y 共有 $m$ 次移动。

小 A 在第 $At_{i-1}$ 到第 $At_i$ 时刻会从 $(Ax_{i-1},Ay_{i-1})$ **匀速直线运动**到 $(Ax_i,Ay_i)$。

小 Y 在第 $Bt_{i-1}$ 到第 $Bt_i$ 时刻会从 $(Bx_{i-1},By_{i-1})$ **匀速直线运动**到 $(Bx_i,By_i)$。

- $At_0=Bt_0=0$。

小 A 还有 $q$ 次询问： 每次询问给出一个浮点数 $c$ 和一个整数 $f$，请求出他们第 $f$ 次相距 $c$ 的时刻。

- **特殊的，如果他们之间相距 $c$ 的时刻有无数个**，输出 `-2.33`。

- **特殊的，如果 $f$ 大于他们之间相距 $c$ 的次数**，输出 `-4.66`。

- 如果不满足上面两个条件，输出他们第 $f$ 次相距 $c$ 的时刻。


## 说明/提示

**「Special Judge」**

**本题使用 Special judge。**

如果你的输出与正确答案的**相对误差或绝对误差**不超过 $10^{-7}$，将会获得该测试点的满分，否则不得分。**建议输出至少 $8$ 位小数**。

请不要输出除了题目要求以外的数字，否则可能获得 UKE。

保证没有答案为 $0$ 的情况。

SPJ 如下：

```
#include "testlib.h"
#define double long double
const double eps=1e-7;
bool Equal(double x,double y){
	return abs(x-y)<=eps||abs((x-y)/y)<=eps;
}
int main(int argc, char* argv[]){
    registerTestlibCmd(argc, argv);
    int n=inf.readInt(),m=inf.readInt(),q=inf.readInt();
    for(int i=1;i<=q;i++){
    	double x=ouf.readDouble(),y=ans.readDouble();
    	if(!Equal(x,y))quitf(_wa,"On line %d the answer is wrong: expected = %.8LF, found = %.8LF",i,y,x);
	}
	quitf(_ok, "The answer is correct."); 
	return 0;
}
```

**「数据范围与约定」**

**本题使用捆绑测试。**

Subtask 编号 | $n,m\leq$ | $q\leq$ | 得分
:-: | :-: | :-: | :-:
$1$ | $5\times 10^2$ | $10^3$ | $10$
$2$ | $2\times 10^4$ | $2\times 10^4$ | $20$
$3$ | $4\times 10^4$ | $5\times 10^4$ | $30$
$4$ | $8\times 10^4$ | $3\times 10^5$ | $40$

对于 $100\%$ 的数据，有 $1\leq n,m\leq 8\times 10^4$，$1\leq q\leq 3\times 10^5$，$At_n=Bt_m\leq 6\times 10^4$，$1\leq f\leq m+n$，$0\leq c\leq 3\times 10^4$。

为保证极端数据下的精度，所有坐标的绝对值不大于 $10^4$。

保证 $At_i<At_{i+1}$，$Bt_i<Bt_{i+1}$，一次移动的时间不超过 $6\times 10^2$。**不保证**某次移动没有改变位置。

**请注意精度误差。**

**「时间 & 空间限制」**

对于第 $1$ 个子任务，时限 $\rm{1s}$；其余子任务时限 $\rm{2.5s}$。

对于第 $1$ 个子任务，空限 $\rm{128MB}$；其余子任务空限 $\rm{256MB}$。

**为了卡掉错解，出题人放短了时限，但时限仍在 std 的 $2$ 倍以上。**

**std 轻微卡常，请注意 I/O/常数优化。**

**本题开启自动 O2 优化。**

**「来源」**

[Sweet Round 04](https://www.luogu.com.cn/contest/26414) F。  
idea & std：[Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
3 3 10
0.00 0.00 0.00 1.00
-1.00 -1.00 0.20
10.00 10.00 0.41
-4.56 -1.23 1.00
-2.00 -1.00 0.40
-10.00 -10.00 0.41
9.87 6.54 1.00
0.00 1
1.00 1
5.00 1
5.00 3
5.00 4
10.00 2
10.00 6
28.28 1
28.28 2
28.29 1```

### 输出

```
-4.66
-2.33
0.26970954
0.83836048
-4.66
0.65792852
-4.66
0.40999665
0.41005730
-4.66```

# 题解

## 作者：Alex_Wei (赞：17)

$$\mathsf{Preface}$$

[题面传送门](https://www.luogu.com.cn/problem/P6214)。

感谢 @[$\color{black}\sf{c\color{red}henxia25}$](https://www.luogu.com.cn/user/138400) 在验题时的错误 idea 帮助我想到了复杂度更优的解法。

---

$$\mathsf{Solution}$$

$\sf{Subtask}\ 1$：$n\leq 5\times 10^2$，$q\leq 10^3$。

核心思想：“切割”。切割时间，使得每个时间段内小 A 和小 Y 都在做匀速直线运动（不改变方向和速度）。例如样例就可以切割成 $0.00\sim0.20$，$0.20\sim0.40$，$0.40\sim0.41$，$0.41\sim1.00$ 四个时间段。

不难发现，每个时间段内，小 A 和小 Y 的距离可能会：$(1)$ 不变。 $(2)$ 变小。 $(3)$ 变大。 $(4)$ 先变小再变大。

对于 $(1)$，我们特判一下。

对于 $(2,3)$，我们将其看做一个区间，有两个属性：距离 $[dl,dr]$ 和时间 $[tl,tr]$。

对于 $(4)$，我们可以三分找出其最小值，然后拆成两个区间。

最多会有 $n+m$ 个时间段，所以最多可能有 $2n+2m$ 个区间。计算区间可以设置 $eps$，也可以设置三分次数，**时间复杂度用 $\log D$ 代替。**

对于每个询问，特判后暴力算，找到区间后再二分 $[tl,tr]$ 找到时间。

时间复杂度 $O(n\log D+nq\log D)$**（下文中，假设 $n$ 的规模不小于 $m$）** 实现起来简单，代码量约为 $\sf{2\sim2.5k}$。

代码（为了验题写的暴力）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ld long double
const int N=5e2+5;
const ld eps=1e-9;
bool Equal(ld x,ld y){return abs(x-y)<=eps;}
struct move{
	ld x,y,t;
}A[N],B[N];
struct query{
	ld c; int f;
}Q[N<<1];
int n,m,q,cnt;
vector <ld> inf,dis;
void Read(){
	cin>>n>>m>>q;
	cin>>A[0].x>>A[0].y>>B[0].x>>B[0].y;
	for(int i=1;i<=n;i++)cin>>A[i].x>>A[i].y>>A[i].t;
	for(int i=1;i<=m;i++)cin>>B[i].x>>B[i].y>>B[i].t;
	for(int i=1;i<=q;i++)cin>>Q[i].c>>Q[i].f,dis.push_back(Q[i].c);
}
struct seg{
	int pa,pb;
	ld l,r,Dl,Dr;
}S[N<<2];
void add(int pa,int pb,ld l,ld r,ld Dl,ld Dr){
	dis.push_back(Dl);
	dis.push_back(Dr);
	S[++cnt]=(seg){pa,pb,l,r,Dl,Dr};
}
ld cal(int pa,int pb,ld t){
	ld ra=(t-A[pa].t)/(A[pa+1].t-A[pa].t),rb=(t-B[pb].t)/(B[pb+1].t-B[pb].t);
	ld xa=A[pa].x+ra*(A[pa+1].x-A[pa].x),xb=B[pb].x+rb*(B[pb+1].x-B[pb].x);
	ld ya=A[pa].y+ra*(A[pa+1].y-A[pa].y),yb=B[pb].y+rb*(B[pb+1].y-B[pb].y);
	return sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
}
void Break(){
	int pa=0,pb=0;
	while(pa<n){
		ld l=max(A[pa].t,B[pb].t),r=min(A[pa+1].t,B[pb+1].t);
		int Pa=pa,Pb=pb;
		if(r==A[pa+1].t)Pa++;
		if(r==B[pb+1].t)Pb++;
		ld Dl=cal(pa,pb,l),Dr=cal(pa,pb,r),Dm=cal(pa,pb,(l+r)/2);
		if(Equal(Dl,Dr)&&Equal(Dm,Dr)){
			inf.push_back(Dl);
			pa=Pa,pb=Pb;
			continue;
		}
		ld L=l,R=r;
		while(R-L>eps*3){
			ld ll=(L+R)/2,rr=ll+eps;
			ld Dll=cal(pa,pb,ll),Drr=cal(pa,pb,rr);
			if(Dll<Drr)R=rr;
			else L=ll;
		}
		if(Equal(l,L)||Equal(r,R))add(pa,pb,l,r,Dl,Dr);
		else{
			ld m=(L+R)/2; Dm=cal(pa,pb,m);
			add(pa,pb,l,m,Dl,Dm),add(pa,pb,m,r,Dm,Dr);
		}
		pa=Pa,pb=Pb;
	}
}
map <ld,int> mp;
void Discretize(){
	sort(dis.begin(),dis.end());
	int siz=unique(dis.begin(),dis.end())-dis.begin();
	for(int i=0;i<siz;i++)mp[dis[i]]=i;
}
void Answer(){
	for(int i=1;i<=q;i++){
		bool Inf=0;
		for(auto it:inf)if(Equal(it,Q[i].c))Inf=1;
		if(Inf){
			puts("-2.33");
			continue;
		}
		int ind=mp[Q[i].c];
		vector <ld> ans;
		for(int i=1;i<=cnt;i++){
			int L=mp[S[i].Dl],R=mp[S[i].Dr];
			if(i!=1)if(L>R)L--; else L++;
			if(L>R)swap(L,R);
			if(L<=ind&&ind<=R)ans.push_back(i);
		}
		if(ans.size()<Q[i].f){
			puts("-4.66");
			continue;
		}
		int pos=ans[Q[i].f-1],pa=S[pos].pa,pb=S[pos].pb,inc=S[pos].Dl<S[pos].Dr;
		ld L=S[pos].l,R=S[pos].r;
		while(R-L>eps*2){
			ld m=(L+R)/2,Dm=cal(pa,pb,m);
			if(inc&&Q[i].c<Dm||!inc&&Q[i].c>Dm)R=m;
			else L=m;
		}
		printf("%.8LF\n",L);
	}
}
int main(){
	Read();
	Break();
	Discretize();
	Answer();
	return 0;
}
```

---

$\sf{Subtask}\ 2$：$n\leq 2\times 10^4$，$q\leq 2\times 10^4$。

将所有区间的端点 $dl,dr$ 和询问距离离散化。询问时二分区间 $tl$，用树套树求出开始时间不大于二分的值且 $dl\leq c\leq dr$ 的区间个数并与 $f$ 比对，找到区间后像 $\sf{Subtask}\ 1$ 一样二分 $[tl,tr]$ 即可。需要注意区间边界的细节。

单次询问时间复杂度 $O(\log n^3+\log D)$，总时间复杂度 $O(n\log D+q\log^3n)$，常数较大，实现起来很麻烦，代码量约为 $\sf{5\sim6k}$。

其实一开始的 $\sf{std}$ 就是这个，但是 [$\color{black}\sf{c\color{red}henxia25}$](https://www.luogu.com.cn/user/138400) 的错误 $\sf{idea}$ 让我探索到了更简单，也更快的算法，那就是 $\sf{Subtask}\ 3$。

---

$\sf{Subtask}\ 3$：$n\leq 4\times 10^4$，$q\leq 5\times 10^4$。

将所有距离离散化，然后我们需要求出的就是：每次给下标落在 $[l,r]$ 的数 $+1$，多次询问下标为 $c$（离散化后） 的值在第几次操作后等于 $f$。

每次操作后更新显然无法承受，但是我们有可持久化数组。

区间加法显然无法承受，但是我们有标记永久化。

这个可以用主席树 + 标记永久化~~轻松~~实现，查询的时候二分操作编号，求出区间后二分时间即可。同 $\sf{Subtask}\ 2$ 一样，需要注意区间边界的细节。

单次询问 $O(\log n^2+\log D)$，总时间复杂度 $O(n\log D+q\log^2n)$。常数大，空间复杂度 $O(q\log n)$，代码量约为 $\sf{3.5\sim 4k}$。

- 另外，浮点数的读入很慢，建议手写 $\sf{read}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO{//手写 read 
	char buf[1<<23],*p1=buf,*p2=buf;
	#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
	inline void read(int &x){
		bool sign=0; char s=gc(); x=0;
		while(!isdigit(s))sign|=s=='-',s=gc();
		while(isdigit(s))x=(x<<1)+(x<<3)+s-'0',s=gc();
		if(sign)x=-x;
	}
	inline void read(double &x){
		bool sign=0; char s=gc(); x=0;
		while(!isdigit(s))sign|=s=='-',s=gc();
		while(isdigit(s))x=x*10+s-'0',s=gc();
		x+=(gc()-'0')*0.1,x+=(gc()-'0')*0.01;
		if(sign)x=-x;
	}
}
using namespace IO;
const int N=1e5+5; const double eps=1e-9;
struct move {double x,y,t; bool operator < (const move &v) const {return t<v.t;} } a[N],b[N];
struct query {double c; int f;} c[N<<2];
struct section {double l,r,tl,tr; int pa,pb;} s[N<<2];
int n,m,q,cs,cnt,cinf;
double p[N<<4],inf[N<<1];
void Init(){
	read(n),read(m),read(q),read(a[0].x),read(a[0].y),read(b[0].x),read(b[0].y);
	for(int i=1;i<=n;i++)read(a[i].x),read(a[i].y),read(a[i].t);
	for(int i=1;i<=m;i++)read(b[i].x),read(b[i].y),read(b[i].t);
	for(int i=1;i<=q;i++)read(c[i].c),read(c[i].f),p[++cnt]=c[i].c;
}
bool Equal(double x,double y) {return abs(x-y)<=eps;}//判断两个数是否相等 
double Gap(double a,double b,double c,double d) {return sqrt((a-c)*(a-c)+(b-d)*(b-d));}//欧几里得距离公式
double Calc(int pa,int pb,double t){//求出某一时刻的距离
	double ra=(t-a[pa-1].t)/(a[pa].t-a[pa-1].t),rb=(t-b[pb-1].t)/(b[pb].t-b[pb-1].t);
	double xa=a[pa-1].x+(a[pa].x-a[pa-1].x)*ra,ya=a[pa-1].y+(a[pa].y-a[pa-1].y)*ra;
	double xb=b[pb-1].x+(b[pb].x-b[pb-1].x)*rb,yb=b[pb-1].y+(b[pb].y-b[pb-1].y)*rb;
	return Gap(xa,ya,xb,yb);
}
void Add(double x,double y,double l,double r,int pa,int pb) {s[++cs]={x,y,l,r,pa,pb},p[++cnt]=x,p[++cnt]=y;}//添加区间
void Breakmove(){//顾名思义，打破运动（求区间）
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	int pa=1,pb=1;
	while(pa<=n&&pb<=m){
		double l=max(a[pa-1].t,b[pb-1].t),r=min(a[pa].t,b[pb].t),dl=Calc(pa,pb,l),dr=Calc(pa,pb,r);
		double m,d1,d2,ll=l,rr=r;
		int npa=pa+(r==a[pa].t),npb=pb+(r==b[pb].t);
		if(Equal(dl,dr)&&Equal(Calc(pa,pb,(l+r)/2),dr)) {inf[++cinf]=dl,pa=npa,pb=npb; continue;}//(1)，距离不变，infinity
		while(r-l>eps) {m=(l+r)/2,d1=Calc(pa,pb,m),d2=Calc(pa,pb,m+eps/3); d1<d2?r=m+eps/3:l=m;}//三分求最小值
		if(dl<d1||Equal(dl,d1)||Equal(d2,dr)||d2>dr)Add(dl,dr,ll,rr,pa,pb);//(2)(3) 
		else {m=(l+r)/2,d1=Calc(pa,pb,m); Add(dl,d1,ll,m,pa,pb),Add(d1,dr,m,rr,pa,pb);}//(4)
		pa=npa,pb=npb;
	}
}
int node,R[N<<2],laz[N<<8],ls[N<<8],rs[N<<8];
int Modify(int pre,int l,int r,int ql,int qr){//区间加+标记永久化 
	int id=++node,m=l+r>>1; laz[id]=laz[pre],ls[id]=ls[pre],rs[id]=rs[pre];
	if(ql<=l&&r<=qr) {laz[id]++; return id;}
	if(ql<=m)ls[id]=Modify(ls[pre],l,m,ql,qr);
	if(m<qr)rs[id]=Modify(rs[pre],m+1,r,ql,qr);
	return id;
}
int Query(int l,int r,int pos,int x){//查询某个版本的值
	if(l==r)return laz[x];
	int m=l+r>>1;
	return laz[x]+(pos<=m?Query(l,m,pos,ls[x]):Query(m+1,r,pos,rs[x]));
}
map <double,int> mp;
void Construct(){
	sort(p+1,p+cnt+1),sort(inf+1,inf+cinf+1); cnt=unique(p+1,p+cnt+1)-p-1;
	for(int i=1;i<=cnt;i++)mp[p[i]]=i;//离散化
	for(int i=1;i<=cs;i++){
		int l=mp[s[i].l],r=mp[s[i].r];
		if(i!=1) if(l<r)l++; else l--; if(l>r) swap(l,r);//注意区间边界 
		R[i]=Modify(R[i-1],1,cnt,l,r);
	}
}
int Binary_pos(query d){//二分区间位置
	int l=1,r=cs,dis=mp[d.c];
	while(l<r) {int m=l+r>>1,t=Query(1,cnt,dis,R[m]); if(t<d.f)l=m+1; else r=m;}
	return l;
}
double Binary_time(int pos,double dis){//二分时间
	section d=s[pos]; int pa=d.pa,pb=d.pb; bool down=d.l>d.r; double l=d.tl,r=d.tr;
	while(r-l>eps) {double m=(l+r)/2,dm=Calc(pa,pb,m); if(dm<dis&&down||dm>=dis&&!down)r=m; else l=m;}
	return (l+r)/2;
}
void Answer(){
	for(int i=1;i<=q;i++){
		int pos=lower_bound(inf+1,inf+cinf+1,c[i].c)-inf;
		if(pos<=cinf&&Equal(inf[pos],c[i].c)||pos>1&&Equal(inf[pos-1],c[i].c)) {puts("-2.33"); continue;}
		int tot=Query(1,cnt,mp[c[i].c],R[cs]);
		if(c[i].f>tot)puts("-4.66");//特判f>次数 
		else printf("%.8lf\n",Binary_time(Binary_pos(c[i]),c[i].c));
	}
}
int main() {Init(); Breakmove(); Construct(); Answer();}//后面三个主要函数的首字母重新排序后为 ABC（逃 
```

接下来的部分是写好题解 $\sf{1\ Day}$ 后才有的。出题人经过一晚上的苦思冥想，发现了复杂度更优的解法。

---

$\sf{Subtask\ 4}$：$n\leq 8\times 10^4,q\leq 3\times 10^5$。

用两只 $\log$ 水过去的神仙，我请您抽烟。~~两只 $\log$，两只 $\log$，跑得快，跑得快。~~

同 $\sf{Subtask\ 3}$ 一样，我们将区间离散化后用主席树维护，然后用前缀和 $\sf{plus}$ 优化查找，就可以将查找部分的时间复杂度优化到单次 $\log n$。

总时间复杂度 $O(n\log n+q\log n+q\log D)$，别看 $n$ 只有 $8\times 10^4$，实际上区间的个数为 $4n=3.2\times 10^5$，点的个数可以达到惊人的 $8n+q=9.4\times 10^5$，所以常数还是很大的。实现起来也较麻烦，代码量约为 $\sf{4\sim 5k}$。

注意事项 & 卡常技巧：

- 注意空间限制。

- 浮点数的读入/输出很慢，建议手写 $\sf{IO}$。

- 离散化尽量不要用 $\sf{map}$，很慢。

~~千疮百孔的~~代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pii pair <int,int>
namespace IO{//手写 IO
	char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
	#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
	#define pc(x) (*O++=x)
	#define flush() fwrite(obuf,O-obuf,1,stdout)
	inline void read(int &x){
		bool sign=0; char s=gc(); x=0;
		while(!isdigit(s))sign|=s=='-',s=gc();
		while(isdigit(s))x=(x<<1)+(x<<3)+s-'0',s=gc();
		if(sign)x=-x;
	}
	inline void read(double &x){
		bool sign=0; char s=gc(); x=0;
		while(!isdigit(s))sign|=s=='-',s=gc();
		while(isdigit(s))x=x*10+s-'0',s=gc();
		x+=(gc()-'0')*0.1,x+=(gc()-'0')*0.01;
		if(sign)x=-x;
	}
	inline void print(int x){
		if(x<10)pc(x+'0');
		else print(x/10),pc(x%10+'0');
	}
	inline void print(double x){
		if(x<0)pc('-'),x=-x;
		int d=x; print(d),x-=d;
		pc('.');
		for(int i=0;i<8;i++)x*=10.0,d=(int)x,pc(d+'0'),x-=d;
		pc('\n');
	}
	inline void print(string x){
		for(int i=0;i<x.size();i++)pc(x[i]);
		pc('\n');
	}
}
using namespace IO;
const int N=8e4+5,Q=3e5+5,P=1e6+5; const double eps=1e-9;
struct move {double x,y,t; bool operator < (const move &v) const {return t<v.t;} } a[N],b[N];
struct query {double c; int f;} c[Q];
struct section {double l,r,tl,tr; int pa,pb;} s[N<<2];
int n,m,q,cs,cnt,cinf;
double p[P],inf[P];
void Init(){
	read(n),read(m),read(q),read(a[0].x),read(a[0].y),read(b[0].x),read(b[0].y);
	for(int i=1;i<=n;i++)read(a[i].x),read(a[i].y),read(a[i].t);
	for(int i=1;i<=m;i++)read(b[i].x),read(b[i].y),read(b[i].t);
	for(int i=1;i<=q;i++)read(c[i].c),read(c[i].f),p[++cnt]=c[i].c;
}
bool Equal(double x,double y) {return abs(x-y)<=eps;}//判断两个数是否相等 
double Gap(double a,double b,double c,double d) {return sqrt((a-c)*(a-c)+(b-d)*(b-d));}//欧几里得距离公式
double Calc(int pa,int pb,double t){//求出某一时刻的距离
	double ra=(t-a[pa-1].t)/(a[pa].t-a[pa-1].t),rb=(t-b[pb-1].t)/(b[pb].t-b[pb-1].t);
	double xa=a[pa-1].x+(a[pa].x-a[pa-1].x)*ra,ya=a[pa-1].y+(a[pa].y-a[pa-1].y)*ra;
	double xb=b[pb-1].x+(b[pb].x-b[pb-1].x)*rb,yb=b[pb-1].y+(b[pb].y-b[pb-1].y)*rb;
	return Gap(xa,ya,xb,yb);
}
void Add(double x,double y,double l,double r,int pa,int pb) {s[++cs]={x,y,l,r,pa,pb},p[++cnt]=x,p[++cnt]=y;}//添加区间
void Breakmove(){//顾名思义，打破运动（求区间）
	int pa=1,pb=1;
	while(pa<=n&&pb<=m){
		double l=max(a[pa-1].t,b[pb-1].t),r=min(a[pa].t,b[pb].t),dl=Calc(pa,pb,l),dr=Calc(pa,pb,r);
		double m,d1,d2,L=l,R=r;
		int npa=pa+(r==a[pa].t),npb=pb+(r==b[pb].t);
		if(Equal(dl,dr)&&Equal(Calc(pa,pb,(l+r)/2),dr)) {inf[++cinf]=dl,pa=npa,pb=npb; continue;}//(1)，距离不变，infinity
		while(r-l>eps) {m=(l+r)/2,d1=Calc(pa,pb,m),d2=Calc(pa,pb,m+eps/3); d1<d2?r=m+eps/3:l=m;}//三分求最小值
		if(dl<d1||Equal(dl,d1)||Equal(d2,dr)||d2>dr)Add(dl,dr,L,R,pa,pb);//(2)(3)
		else {m=(l+r)/2,d1=Calc(pa,pb,m); Add(dl,d1,L,m,pa,pb),Add(d1,dr,m,R,pa,pb);}//(4)
		pa=npa,pb=npb;
	}
}
int node,R[N<<3];
struct data {int ls,rs,num;}d[P<<5];
int Modify(int pre,int l,int r,int pos,int v){
	int id=++node; d[id]=d[pre],d[id].num+=v;
	if(l==r)return id;
	int m=l+r>>1;
	if(pos<=m)d[id].ls=Modify(d[pre].ls,l,m,pos,v);
	else d[id].rs=Modify(d[pre].rs,m+1,r,pos,v);
	return id;
}
int Getpos(double x) {return lower_bound(p+1,p+cnt+1,x)-p;}
void Construct(){
	sort(p+1,p+cnt+1),sort(inf+1,inf+cinf+1); cnt=unique(p+1,p+cnt+1)-p-1;
	pii op[N<<3]; int cop=0,pos=1;
	for(int i=1;i<=cs;i++){
		int l=Getpos(s[i].l),r=Getpos(s[i].r);
		if(i!=1) if(l<r)l++; else l--; if(l>r) swap(l,r);//注意区间边界 
		op[++cop]={l,i},op[++cop]={r+1,-i};
	}
	sort(op+1,op+cop+1);
	for(int i=1;i<=cop;i++){
		while(pos<op[i].fi)R[pos+1]=R[pos],pos++;
		if(pos==cnt+1)break;
		R[pos]=Modify(R[pos],1,cs,abs(op[i].se),op[i].se>0?1:-1);
	}
}
int Query(int l,int r,int x,int k){//查找
	if(l==r)return l;
	int m=l+r>>1;
	return k<=d[d[x].ls].num?Query(l,m,d[x].ls,k):Query(m+1,r,d[x].rs,k-d[d[x].ls].num);
}
double Binary_time(int pos,double dis){//二分时间
	section d=s[pos]; int pa=d.pa,pb=d.pb; bool down=d.l>d.r; double l=d.tl,r=d.tr;
	while(r-l>eps) {double m=(l+r)/2,dm=Calc(pa,pb,m); if(dm<dis&&down||dm>=dis&&!down)r=m; else l=m;}
	return (l+r)/2;
}
void Answer(){
	for(int i=1;i<=q;i++){
		int pos=lower_bound(inf+1,inf+cinf+1,c[i].c)-inf;
		if(pos<=cinf&&Equal(inf[pos],c[i].c)||pos>1&&Equal(inf[pos-1],c[i].c)) {print("-2.33"); continue;}//特判infinity
		int p=Getpos(c[i].c);
		if(c[i].f>d[R[p]].num)print("-4.66");//特判f>次数
		else print(Binary_time(Query(1,cs,R[p],c[i].f),c[i].c));
	}
}
int main() {Init(); Breakmove(); Construct(); Answer(); flush();}//后面三个主要函数的首字母重新排序后为 ABC（逃 
```


---

$$\sf{Conclusion}$$

本文中可能会有一些不太严谨的地方，请见谅。

**希望大家能够通过这道题目对可持久化数组，标记永久化和前缀和优化有更进一步的理解，这也是我们出题的本意。**

再次感谢 [$\sf{\color{black}c\color{red}henxia25}$](https://www.luogu.com.cn/user/138400)（$\sf{STO}$，他真的很强）！

$\sf{Upd\ on\ 2020.2.29:}$ 另外，感谢 [$\color{gray}\sf{Alex\_Wei}$](https://www.luogu.com.cn/user/123294)（我自己）及时发现了复杂度更优的解法，才使得 $\sf{std}$ 不被吊打。


码字不易，点个赞呗 awa。另外，如果你发现了文章有错，及时告诉我哈，bye ~

---

## 作者：xtx1092515503 (赞：6)

应出题人要求，前来研究本题，然后发现出题人的写法一点也不美观。

![](https://cdn.luogu.com.cn/upload/image_hosting/v472k3bh.png)

------------

我们考虑任意时刻两人之间的向量 $\vec{s}$。在某一段时间内，两人之间向量的变化率会一直是 $\vec{v}$。于是，按照此种方式进行 $t$ 秒后，二人之间的向量会是 $\vec{s}+t\vec{v}$。

考虑两人间的距离，它为 $|\vec{s}+t\vec{v}|$。我们如果画出图来，就会发现它的几何意义是原点到直线上一点的距离。

![](https://cdn.luogu.com.cn/upload/image_hosting/vcpcwadx.png)

明显，点到直线距离是二次函数（考虑点到直线距离公式）。这就意味着，我们如果把每一时刻二人间距离画出来，它可能长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/lj9y035c.png)

如图，距离可能曲里拐弯，可能上下乱动，但是唯一不变的是，在每个区间内，距离要么是单调上升/下降的，要么是单峰的。

于是，我们可以再把每个单峰函数在峰值处切一刀，将其切成两半单调的函数。

![](https://cdn.luogu.com.cn/upload/image_hosting/5ihxxfuk.png)

于是现在，我们便得到了众多单调的连续函数。

我们现在再考虑询问距离为 $x$，则其就相当于用一条水平的直线去截上述图像，求出其某个交点。

![](https://cdn.luogu.com.cn/upload/image_hosting/o4jo7f0c.png)

明显，依据中值定理，对于一段函数 $(t_i,t_{i+1})$，如果其一端在该水平直线上，一端在该水平直线下，则二者必在此段区间内有且仅有一个交点。

于是我们便可以离线下所有询问，然后从小到大依次枚举每一段 $(t_i,t_{i+1})$，更新那些与其有交点的询问。

具体而言，我们可以将询问按照键值排序，关于询问建线段树，然后在线段树上维护区间 $\min$，表示此段区间里剩余出现次数最少的那个询问的出现次数。当我们有一段函数的时候，就把它执行区间 $-1$ 的操作。假如何时发现出现了 $0$，就证明出现 $0$ 的询问与此段函数的交点是该询问需要的交点，找出该交点即是此询问的答案。

说起来很轻巧，但是写起代码来却异常恶心。

首先，初始的函数可以通过对两个人进行归并得到。这时，我们便知道了每一段函数的分界点、函数在分界点处的取值，以及每段区间内部的速度（即上述的 $v$）。

然后，关于将二次函数切开的操作，可以使用三分——但我认为那是异端行为。更好的方法是采用计算几何求出原点到上述直线的垂线，然后在垂足处将二次函数分开。

然后建树什么的就不提了。注意，区间的端点要单独考虑，不然会出现奇怪的错误（因为端点会被左右两端的区间各计算一次）。

然后就是求询问与某段函数的交点了。可以使用二分——但那还是异端行为。更好的方法是直接上计算几何，计算出当直线上的某个点离原点的距离是询问的值时，其与垂足间的距离（可以直接上勾股定理算得），然后判断垂足两端距离它为上述距离的点中哪一个在区间内即可。

最后是两种特殊情况：$-2.33$，当且仅当函数中某一段是水平直线（这是有可能发生的，此时 $\vec{v}=0$），且该直线与询问直线重合；$-4.66$，当且仅当所有区间都加入线段树后，某些询问还有剩余的次数。

时间复杂度 $O(q\log q)$。

（所以，为什么还要用主席树呢？）

（虽然此代码一点都不比主席树短）

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-10;
struct Vector{
	double x,y;
	Vector(){x=y=0;}
	Vector(double X,double Y){x=X,y=Y;}
	friend Vector operator +(const Vector &u,const Vector &v){return Vector(u.x+v.x,u.y+v.y);}
	friend Vector operator -(const Vector &u,const Vector &v){return Vector(u.x-v.x,u.y-v.y);}
	friend Vector operator *(const Vector &u,const double &v){return Vector(u.x*v,u.y*v);}
	friend Vector operator /(const Vector &u,const double &v){return Vector(u.x/v,u.y/v);}
	friend double operator &(const Vector &u,const Vector &v){return u.x*v.y-u.y*v.x;}//cross times
	friend double operator |(const Vector &u,const Vector &v){return u.x*v.x+u.y*v.y;}//point times
	double operator ~()const{return sqrt(x*x+y*y);}//the modulo of a vector
	double operator !()const{return atan2(y,x);}//the angle of a vector
	void read(){scanf("%lf%lf",&x,&y);}
	void print(){printf("(%lf,%lf)",x,y);}
};
typedef Vector Point;
struct Line{
	Point x,y;
	Vector z;
	Line(){}
	Line(Point X,Point Y){x=X,y=Y,z=Y-X;}
	friend Point operator &(const Line &u,const Line &v){return u.x+u.z*((v.z&(u.x-v.x))/(u.z&v.z));}
};
typedef Line Segment;
namespace ini{//initialization part.
	int n,m,lim;
	Vector A[80100],B[80100],v[160100];
	double aa[80100],bb[80100],tim[160100];
	Point p[160100],tange[160100];
	double FindTangent(int i){
		if(~v[i+1]<eps||~p[i]<eps){tange[i]=p[i];return 0;}
		Line U=Line(p[i],p[i]+v[i+1]);
		Line V=Line(Point(),Point(v[i+1].y,-v[i+1].x));
		Point W=U&V;
		tange[i+1]=W;
		W=W-p[i];
		if((W|v[i+1])<0)return 0;//the inflection point is <0.
		return ~W/~v[i+1];
	}
}
namespace nin{//function part.
	int q,lim; 
	Vector v[320100];
	double tim[320100];
	Point p[320100],tange[320100];
	double FindConcide(int i,double req){
		double mini=~tange[i+1];
		double nedi=sqrt(req*req-mini*mini)/~v[i+1];
		Point W=tange[i+1]-p[i];
		double nowi=~W/~v[i+1];
		if((W|v[i+1])<0)nowi=-nowi;
		if(nowi+nedi>eps&&nowi+nedi<=tim[i+1]-tim[i])return nowi+nedi+tim[i];
		return nowi-nedi+tim[i];
	}
	struct Query{
		int num,id;
		double inq;
		friend bool operator <(const Query &x,const Query &y){return x.inq<y.inq;}
	}qq[301000];
	double qwq[301000];
	double res[301000];
	set<double>sp;
	bool findsp(double inq){
		auto it=sp.lower_bound(inq);
		if(it!=sp.end()&&fabs(*it-inq)<eps)return true;
		if(it==sp.begin())return false;
		it--;
		return fabs(*it-inq)<eps;
	}
	#define lson x<<1
	#define rson x<<1|1
	#define mid ((l+r)>>1)
	struct Segtree{
		int tag,mn;
	}seg[1201000];
	void ADD(int x,int y=1){seg[x].tag+=y,seg[x].mn-=y;}
	void pushdown(int x){ADD(lson,seg[x].tag),ADD(rson,seg[x].tag),seg[x].tag=0;}
	void pushup(int x){seg[x].mn=min(seg[lson].mn,seg[rson].mn);}
	void build(int x,int l,int r){
		if(l==r){
			if(findsp(qq[l].inq))res[qq[l].id]=-2.33,seg[x].mn=0x3f3f3f3f;
			else seg[x].mn=qq[l].num;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r),pushup(x);
	}
	void modify(int x,int l,int r,int L,int R){
		if(l>R||r<L)return;
		if(L<=l&&r<=R){ADD(x);return;}
		pushdown(x),modify(lson,l,mid,L,R),modify(rson,mid+1,r,L,R),pushup(x);
	}
	void getans(int x,int l,int r,int i){
		if(l==r){
			res[qq[l].id]=FindConcide(i,qq[l].inq);
			seg[x].mn=0x3f3f3f3f;
			return;
		}
		pushdown(x);
		if(seg[lson].mn==0)getans(lson,l,mid,i);
		if(seg[rson].mn==0)getans(rson,mid+1,r,i);
		pushup(x);
	}
	void setans(int x,int l,int r,double i){
		if(l==r){
			res[qq[l].id]=i;
			seg[x].mn=0x3f3f3f3f;
			return;
		}
		pushdown(x);
		if(seg[lson].mn==0)setans(lson,l,mid,i);
		if(seg[rson].mn==0)setans(rson,mid+1,r,i);
		pushup(x);
	}
}
namespace ini{
	void initialize(){
		scanf("%d%d%d",&n,&m,&nin::q);
		A[0].read(),B[0].read();
		for(int i=1;i<=n;i++)A[i].read(),scanf("%lf",&aa[i]);
		for(int i=n;i;i--)A[i]=(A[i]-A[i-1])/(aa[i]-aa[i-1]);
		for(int i=1;i<=m;i++)B[i].read(),scanf("%lf",&bb[i]);
		for(int i=m;i;i--)B[i]=(B[i]-B[i-1])/(bb[i]-bb[i-1]);
		for(int i=1,j=1;i<=n&&j<=m;){
			tim[++lim]=min(aa[i],bb[j]);
			v[lim]=A[i]-B[j];
			if(fabs(aa[i]-tim[lim])<eps)i++;
			if(fabs(bb[j]-tim[lim])<eps)j++;
		}
		p[0]=A[0]-B[0];
		for(int i=1;i<=lim;i++)p[i]=p[i-1]+v[i]*(tim[i]-tim[i-1]);
	}
}
namespace nin{
	void solution(){
//		p[0].print(),puts("");for(int i=1;i<=lim;i++)v[i].print(),printf("%lf\n",tim[i]),p[i].print(),puts("");
		for(int i=0;i<lim;i++)if(~v[i+1]<eps)sp.insert(~p[i]);
		for(int i=1;i<=q;i++)scanf("%lf%d",&qq[i].inq,&qq[i].num),qq[i].id=i;
		sort(qq+1,qq+q+1);
//		for(int i=1;i<=q;i++)printf("%lf %d %d\n",qq[i].inq,qq[i].num,qq[i].id);
		for(int i=1;i<=q;i++)qwq[i]=qq[i].inq;
		build(1,1,q);
		for(int i=0;i<lim;i++){
			if(~v[i+1]<eps)continue;
			double l=~p[i],r=~p[i+1];
			if(l>r)swap(l,r);
			l+=eps,r-=eps; 
//			printf("%lf %lf\n",l,r);
			int L=upper_bound(qwq+1,qwq+q+1,l)-qwq;
			int R=upper_bound(qwq+1,qwq+q+1,r)-qwq-1;
//			printf("%d %d\n",L,R);
			if(L<=R)modify(1,1,q,L,R);
//			printf("BEF:%d\n",seg[1].mn);
			if(seg[1].mn==0)getans(1,1,q,i);
//			printf("AFT:%d\n",seg[1].mn);
			double w=~p[i+1];
			L=lower_bound(qwq+1,qwq+q+1,w)-qwq;
			R=upper_bound(qwq+1,qwq+q+1,w)-qwq-1;
			if(L<=R)modify(1,1,q,L,R),printf("%d %d\n",L,R);
			if(seg[1].mn==0)setans(1,1,q,tim[i+1]);
		}
		for(int i=1;i<=q;i++)if(fabs(res[i])<eps)res[i]=-4.66;
		for(int i=1;i<=q;i++)printf("%.9lf\n",res[i]);
	}
}
int main(){
	ini::initialize();
	nin::p[0]=ini::p[0];
	for(int i=0;i<ini::lim;i++){
		double pos=ini::FindTangent(i);
		if(pos>eps&&(ini::tim[i+1]-ini::tim[i])-pos>eps){
			nin::lim++;
			nin::p[nin::lim]=ini::p[i]+ini::v[i+1]*pos;
			nin::v[nin::lim]=ini::v[i+1];
			nin::tim[nin::lim]=ini::tim[i]+pos;
			nin::tange[nin::lim]=ini::tange[i+1];
		}
		nin::lim++;
		nin::p[nin::lim]=ini::p[i+1];
		nin::v[nin::lim]=ini::v[i+1];
		nin::tim[nin::lim]=ini::tim[i+1];
		nin::tange[nin::lim]=ini::tange[i+1];
	}
	nin::solution();
	return 0;
}
```



---

## 作者：qiuzx (赞：1)

## 题意

有两个人在平面上分别做 $n,m$ 次匀速直线运动。$q$ 次询问，给定 $f,c$，求两人第 $f$ 次距离为 $c$ 的时刻。$n,m\le 8\times 10^4,q\le 3\times 10^5$。

## 思路

首先离散化所有时刻，形成 $O(n+m)$ 段区间，其中每一段区间中两人都在做匀速直线运动。对于匀速直线运动而言，一个人的坐标可以写成 $(k_xt+b_x,k_yt+b_y)$ 的形式，其中 $t$ 是时刻。那么两人之间距离的平方就形如 $at^2+bt+c$ 这样一个二次函数。特别地，若 $a=b=0$ 则这一段事件中两人距离为定值，记录一下这个值，若查询到这个值则输出 $-2.33$ 即可。由于二次函数是单峰的，所以求出对称轴之后可以拆分为至多两段单调的函数。现在假设我们需要查询一个 $c$，则首先给 $c$ 平方，然后就需要查询一个分段单调的函数中 $c$ 的第 $f$ 次出现位置。先定位到在哪一段中，再使用求根公式算出准确的时刻。由于现在只关心在哪一段中，而二次函数是连续的，所以只要两个端点处的值满足 $l\le c\le r$，就会出现一次。

先考虑怎么处理多次询问，离线询问，然后从下往上做扫描线，则扫到一个区间下端点时加入这个区间，扫到上端点时删除这个区间，处理查询时需要求第 $k$ 小的区间编号，使用任意数据结构维护即可。如果需要强制在线可以使用主席树可持久化一下。复杂度 $O((n+m+q)\log v)$。

下面需要处理一个值恰好在端点处取到的情况。这里钦定每个区间都是左开右闭的，那么分析一下在一个值处的所有插入、删除、查询应当如何进行。首先需要删除所有以当前值为左端点的区间，然后插入所有以当前值为右端点的区间，然后进行查询，最后将剩下的没有插入和删除的区间插入与删除即可。容易验证这样做是满足所有区间左开右闭的条件的。

最后是浮点数误差的处理。对于询问、坐标与时间带来的浮点数误差，可以将它们放大 $100$ 倍之后全部转化为整数。对于求二次函数带来的浮点误差，由于可能对答案有较大影响的误差本质上只有恰好等于端点时的处理，所以将距离整数 $<\epsilon$ 的值全部设为对应整数，其它值全部设为下取整 $+0.5$ 之后的结果。然后再将所有值乘 $2$，这样在处理区间的时候就全部是整数了。只有算二次函数时会用到浮点数，精度误差足够。

[代码](https://www.luogu.com.cn/paste/g3rvbz0m)

---

