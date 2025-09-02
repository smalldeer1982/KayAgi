# [CEOI 2012] Printed Circuit Board

## 题目描述

给出一个 $n$ 个顶点的简单多边形，对于每个顶点，假如它和原点连成的线段只在这个顶点处和多边形相交，就称为满足要求的顶点。你的任务是输出所有满足要求的顶点编号。

![](https://cdn.luogu.com.cn/upload/image_hosting/beasw2yx.png)



## 说明/提示

对于 $100\%$ 的数据，满足 $1 \le n \le 2 \times 10^5$。

## 样例 #1

### 输入

```
11
7 6
4 4
3 2
1 3
9 9
13 4
8 1
6 4
9 5
8 3
11 5```

### 输出

```
3
3 4 7```

# 题解

## 作者：Seauy (赞：3)

[题目链接](https://www.luogu.com.cn/problem/P6237)

## 题目大意

- $n$ 个点的多边形，求出所有与原点连线段跟多边形交点不超过 $2$ 的顶点。

- $n \leq 2\times 10^5$，坐标为不超过 $10^6$ 的自然数。

# Solution

考虑求出 $O$ 与顶点 $i$ 的连线段与多边形有交点的边中，交点模长最小的那个。

这个东西可以直接上极坐标李超线段树，但注意到每条边两端点的极角形成区间 $[\theta_L,\theta _R]$，我们按极角做扫描线，$\theta_L$ 处插入线段 $\theta_R$ 处再删除，发现对于同时存在的两条线段，他们的与过 $  O$ 且倾斜角为 $\theta$ 的直线交点，到 $O$ 的距离相对大小不变。

因此按极角离散化后用堆维护扫描线即可，复杂度 $O(n \log n)$。

# Code

```cpp
#include<bits/stdc++.h>
#define Lson (now<<1)
#define Rson (now<<1|1)
using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN=2e5;

inline int Read()
{
	int res;char c;
	while(1) {c=getchar();if('0'<=c && c<='9') {res=c-'0';break;}}
	while(1) {c=getchar();if('0'<=c && c<='9') res=res*10+c-'0';else break;}
	return res;
}

inline ld Mold(ld x,ld y) {return sqrt(x*x+y*y);}

struct Point
{
	ld x,y,rho,dis;
	int ID,loc;
	inline void Scan() {x=Read(),y=Read(),rho=y/x,dis=Mold(x,y);}
}ver[MAXN+5];
bool cmp(Point a,Point b)
{return a.loc==b.loc ? a.dis<b.dis : a.loc<b.loc;}

int n;ld K;//当前斜率
ld dsc[MAXN+5];int dnum;
vector<int> ope[MAXN+5];
int ans[MAXN+5],tot;

inline int Search(ld x)
{
	for(int L=1,R=dnum,mid;1;)
	{
		mid=(L+R)>>1;
		if(x==dsc[mid]) return mid;
		if(dsc[mid]<x) L=mid+1;
		else R=mid-1;
	}
	return 0;
}

struct Segment
{
	ld k,b,cls;
	inline ld dis()
	{
		ld x,y;
		if(k<0 && b<0) x=-k,y=K*x;
		else {if(k==K) return cls; x=b/(K-k),y=K*x;}
		return Mold(x,y);
	}
}seg[MAXN+5];

//------------- Heap -------------
int data[MAXN+5],Tail,inv[MAXN+5];
inline void Insert(int x)
{
	ld v=seg[x].dis();
	int now=++Tail; data[now]=x,inv[x]=now;
	for(;now>1;now>>=1)
		if(v<seg[data[now>>1]].dis())
		{
			swap(data[now],data[now>>1]);
			swap(inv[data[now]],inv[data[now>>1]]); 
		}
		else break;
}
inline void Delete(int x)
{
	int now=inv[x];
	data[now]=data[Tail];
	inv[data[Tail]]=now;
	data[Tail--]=0;
	while(Lson<=Tail)
		if(Rson<=Tail)
		{
			if(seg[data[Lson]].dis()<seg[data[Rson]].dis())
			{
				swap(data[now],data[Lson]);
				swap(inv[data[now]],inv[data[Lson]]);
				now=Lson;
			}
			else
			{
				swap(data[now],data[Rson]);
				swap(inv[data[now]],inv[data[Rson]]);
				now=Rson;
			}
		}
		else
		{
			swap(data[now],data[Lson]);
			swap(inv[data[now]],inv[data[Lson]]);
			now=Lson;
		}
}

inline bool Judge(int a,int b)
{
	if(!b) return 1;
	return ver[a].dis<seg[b].dis();
}

int main()
{
	//freopen("3.in","r",stdin);
	//freopen("mine.txt","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		ver[i].Scan();
		dsc[++dnum]=ver[i].rho;
		ver[i].ID=i;
	}
	sort(dsc+1,dsc+dnum+1),dnum=unique(dsc+1,dsc+dnum+1)-dsc-1;
	for(int i=1;i<=n;i++) ver[i].loc=Search(ver[i].rho);
	ver[n+1]=ver[1];
	for(int i=1;i<=n;i++)
	{
		if(ver[i].x==ver[i+1].x) seg[i]=Segment{-ver[i].x,-1};
		else
		{
			seg[i].k=(ver[i].y-ver[i+1].y)/(ver[i].x-ver[i+1].x);
			seg[i].b=ver[i].y-seg[i].k*ver[i].x;
		}
		seg[i].cls=min(ver[i].dis,ver[i+1].dis);//获取每条线段 
		int L=ver[i].loc,R=ver[i+1].loc; if(L>R) swap(L,R);
		if(L==R) continue;
		ope[L+1].push_back(i);
		ope[R].push_back(-i);
	}
	sort(ver+1,ver+n+1,cmp);
	
	for(int i=1,j=1;i<=dnum && j<=n;i++)
	{
		K=dsc[i];
		for(int k=0;k<ope[i].size();k++)
			if(ope[i][k]>0) Insert(ope[i][k]);
			else Delete(-ope[i][k]);
		if(Judge(j,data[1])) ans[++tot]=ver[j].ID;
		while(ver[j].loc==i && j<=n) ++j;
	}
	sort(ans+1,ans+tot+1);
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：Union_of_Britain (赞：1)

似乎是 cdqz 暑假的一次 noip 联考搬过的（这个时候我还在学中考，蛤蛤蛤）

首先注意到两条直线从原点出发，倾角旋转一周，谁先被扫到只会改变一次：据此，可以使用李超线段树解决。但是由于会使用三角函数或者开根，会被卡精度到 80pts。

李超线段树代码：

```cpp
// Problem: P6237 [CEOI2012] Printed Circuit Board
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6237
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// UOB Koala
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
double x[maxn],y[maxn];
int n,rev[maxn],L[maxn],R[maxn];
int Get(int x){
	if(x==n+1)return 1;
	if(x==0)return n;
	return x;
}
struct line{
	double a,b,c;int id;
	line(double x,double y,double z){
		a=x,b=y,c=z;
	}
	line(){
		id=0;
	}
	double operator ()(const double &th)const{
		if(!id)return 1e10;
		if(fabs(a*cos(th)+b*sin(th))<1e-3){
			if(x[id]<x[Get(id+1)])return sqrt(x[id]*x[id]+y[id]*y[id]);
			return sqrt(x[Get(id+1)]*x[Get(id+1)]+y[Get(id+1)]*y[Get(id+1)]);
		}
		return c/(a*cos(th)+b*sin(th));
	}
}a[maxn];
#define pdi pair<double,int>
pdi th[maxn];
double ang[maxn];
int s[maxn<<2];
#define ls (k<<1)
#define rs (k<<1|1)
#define mid ((l+r)>>1)
void ins(int k,int l,int r,int u){
	int &v=s[k];
	if(a[u](ang[mid])<a[v](ang[mid]))swap(u,v);
	if(a[u](ang[l])<a[v](ang[l]))ins(ls,l,mid,u);
	if(a[u](ang[r])<a[v](ang[r]))ins(rs,mid+1,r,u);
}
void modify(int k,int l,int r,int x,int y,int u){
	if(x<=l&&r<=y)return ins(k,l,r,u);
	if(x<=mid)modify(ls,l,mid,x,y,u);
	if(mid<y)modify(rs,mid+1,r,x,y,u);
}
pdi query(int k,int l,int r,int x){
	pdi res={a[s[k]](ang[x]),s[k]};
	if(l==r)return res;
	if(x<=mid)res=min(res,query(ls,l,mid,x));
	else res=min(res,query(rs,mid+1,r,x));
	return res;
}
struct DSU{
	int fa[maxn];
	int Find(int x){
		return fa[x]==x?x:fa[x]=Find(fa[x]);
	}
}Lf,Rf;
signed main()
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
	x[n+1]=x[1],y[n+1]=y[1];
	for(int i=2;i<=n+1;i++){
		a[i-1]=line(y[i]-y[i-1],x[i-1]-x[i],-y[i]*(x[i]-x[i-1])+(y[i]-y[i-1])*x[i]);
		a[i-1].id=i-1;
	}
	for(int i=1;i<=n;i++)th[i]={atan2(y[i],x[i]),i};
	sort(th+1,th+n+1);
	for(int i=1;i<=n;i++)ang[i]=th[i].first,rev[th[i].second]=i;
	for(int i=1;i<=n;i++)Lf.fa[i]=i,Rf.fa[i]=i;
	for(int i=2;i<=n;i++)if(fabs(ang[i]-ang[i-1])<1e-6)Lf.fa[i]=Lf.Find(Lf.fa[i-1]);
	for(int i=n-1;i>=1;i--)if(fabs(ang[i]-ang[i+1])<1e-6)Rf.fa[i]=Rf.Find(Rf.fa[i+1]);
	for(int i=1;i<=n;i++){
		L[i]=Lf.Find(rev[i]),R[i]=Rf.Find(rev[Get(i+1)]);
		if(L[i]>R[i])swap(L[i],R[i]);
		modify(1,1,n,L[i],R[i],i);
	}
	vector<int> ans;
	for(int i=1;i<=n;i++){
		auto t=query(1,1,n,rev[i]);
		double val=t.first;int id=t.second;
		if(fabs(x[i]*x[i]+y[i]*y[i]-val*val)<10)ans.push_back(i);
	}
	cout<<ans.size()<<endl;
	for(auto u:ans)cout<<u<<" ";
	cout<<endl;
	return 0;
}
```

时间复杂度 $O(n\log^2 n)$。

但是还有一种想法：

注意到多边形的若干线段相交当且仅当他们相邻，并且相交在相邻的这个顶点位置。所以他们的相对“谁在前面”在两个线段的合法位置是不会改变的。

据此，可以对极角扫描线然后采用一种数据结构维护。它支持：取最小值，加入删除一个数。使用 `set` 解决。

在这个实现时有一些细节。比方说，需要考虑极角相等的点的情况（用 ban 表示因为这个被另一个点挡住的点，用 DSU 找出左右极角相等的极左/右位置）；线段和原点共线时的计算；定顺序的时候如果相等（差的绝对值 $<eps$）要在下一个位置比较（此时还要考虑超出线段范围）。eps 要设大一点，否则可能一些点不会被统计。

```cpp
// Problem: P6237 [CEOI2012] Printed Circuit Board
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6237
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// UOB Koala
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
const double eps=1e-3;
int n,rev[maxn],L[maxn],R[maxn];
struct pt{
	int x,y,id;
	bool operator <(const pt &b)const{return y*b.x==x*b.y?x<b.x:y*b.x<x*b.y;}
}p[maxn];
vector<int> revl[maxn],revr[maxn];
int G(int x){
	if(x==n+1)return 1;
	if(x==0)return n;
	return x;
}
struct DSU{
	int fa[maxn];
	int Find(int x){
		return fa[x]==x?x:fa[x]=Find(fa[x]);
	}
}Lf,Rf;
int now;
double getr(int id,int a,int b){//y=a/b x
	int x=rev[id],y=rev[G(id+1)];
	if(p[x].x>p[y].x)swap(x,y);
	int B=p[y].x-p[x].x,A=p[x].y-p[y].y,C=A*p[x].x+B*p[x].y;
	if(A*b+a*B==0)return p[x].x*p[x].x+p[x].y*p[x].y;
	double X=1.0*C*b/(A*b+a*B),Y=X*a/b;
	double l=p[rev[id]].x,r=p[rev[G(id+1)]].x;
	if(l>r)swap(l,r);
	if(X<l-eps||X>r+eps)return 1e10;
	return X*X+Y*Y;
}
struct cmp{
	bool operator ()(const int &a,const int &b)const{
		double A=getr(a,p[now].y,p[now].x),B=getr(b,p[now].y,p[now].x);
		if(fabs(A-B)<eps)return getr(a,p[G(R[now]+1)].y,p[G(R[now]+1)].x)<getr(b,p[G(now+1)].y,p[G(now+1)].x);
		else return A<B;
	}
}T;
set<int,cmp> st;
bool ban[maxn];
int Ans[maxn];
signed main(){
    ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i].x>>p[i].y,p[i].id=i;
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)rev[p[i].id]=i;
	for(int i=1;i<=n;i++)L[i]=R[i]=Lf.fa[i]=Rf.fa[i]=i;
	for(int i=2;i<=n;i++)
		if(p[i].y*p[i-1].x==p[i].x*p[i-1].y)
			L[i]=Lf.fa[i]=Lf.Find(i-1),ban[i]=1;
	for(int i=n-1;i>=1;i--)
		if(p[i].y*p[i+1].x==p[i].x*p[i+1].y)
			R[i]=Rf.fa[i]=Rf.Find(i+1);
	for(int i=1;i<=n;i++){
		int x=rev[i],y=rev[G(i+1)];
		if(x>y)swap(x,y);
		revl[L[x]].push_back(i),revr[R[y]].push_back(i);
	}
	vector<int> ans;
	for(int i=1;i<=n;i++){
		now=i;
		for(auto u:revl[i])st.insert(u);
		Ans[i]=*st.begin();
		for(auto u:revr[i])st.erase(u);
	}
	for(int i=1;i<=n;i++){
		if((Ans[rev[i]]==i||Ans[rev[i]]==G(i-1))&&!ban[rev[i]]){
			ans.push_back(i);
		}
	}
	cout<<ans.size()<<endl;
	for(auto u:ans)cout<<u<<" ";
	return 0;
}
```

---

