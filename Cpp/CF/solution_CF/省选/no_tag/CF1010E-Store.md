# Store

## 题目描述

Natasha想起来她要给朋友们买火星纪念品。但她马上要回地球了。

众所周知，火星一年$ x_{max} $有个月，一个月有$ y_{max} $天， 一天有$ z_{max} $ 秒。Natasha还知道商店工作的规律。

首先，商店会选择一年中的两个月: $ x_l $ 和 $ x_r $ ( $ 1\le x_l\le x_r\le x_{max} $ )，然后是一个月里的两天： $ y_l $ 和 $ y_r $ ( $ 1\le y_l\le y_r\le y_{max} $ ) ，还有一天里的两秒$ z_l $ 和 $ z_r $ ( $ 1\le z_l\le z_r\le z_{max} $ )。所有满足$ x_l\le x\le x_r $ , $ y_l\le y\le y_r $ and $ z_l\le z\le z_r $的时刻($ x , y , z $分别代表这个时刻的月、日、秒）商店都开放。

不幸的是， Natasha 并不知道 $ x_l,x_r,y_l,y_r,z_l,z_r $具体是多少 。

一个火星人告诉Natasha：“我去了这家商店 $ (n+m) $ 次。其中有 $ n $ 次我去的时候它是开着的 ，另外 $ m $次去的时候它是关闭的”他还描述了每次他去商店的时间：即他去的时候的月、日、秒（无论当时商店开没开）。

Natasha要去 $ k $次商店。给出每次去的时刻，请你根据火星人的话以及商店的开放规律回答当时商店是一定开放，一定关闭，还是不确定开不开放。

## 样例 #1

### 输入

```
10 10 10 3 1 3
2 6 2
4 2 4
6 4 6
9 9 9
3 3 3
10 10 10
8 8 8
```

### 输出

```
CORRECT
OPEN
CLOSED
UNKNOWN
```

## 样例 #2

### 输入

```
10 10 10 1 1 1
2 5 7
2 5 7
8 9 10
```

### 输出

```
INCORRECT
```

# 题解

## 作者：meyi (赞：2)

~~大概是退役前的最后一篇题解了吧。~~

题意：给定 $n$ 个在长方体内的点和 $m$ 个不在长方体内的点，$k$ 次查询一个点 是/否/不确定 在长方体内。

首先算出 $n$ 个点的 $x_{\max}$，$x_{\min}$，$y_{\max}$，$y_{\min}$，$z_{\max}$，$z_{\min}$。那么一个点确定在长方体内的条件是 $x_{\max}\le x\le x_{\min}$，$y_{\max}\le y\le y_{\min}$，$z_{\max}\le z\le z_{\min}$，此时输出 `OPEN`。

然后对于询问点，假设它在长方体内，那么可以计算出新的 $x_{\max}$，$x_{\min}$，$y_{\max}$，$y_{\min}$，$z_{\max}$，$z_{\min}$，此时如果 $m$ 个不在原长方体内的点出现在了新的长方体内，那么显然矛盾，说明询问点不在长方体内，输出 `CLOSED`，否则询问点不确定是否在长方体内，输出 `UNKNOWN`。

于是这题就被转化成了三维数点板子，使用合适的数据结构维护即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri int
typedef long long ll;
const int maxd=3,maxn=1e5+10;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
template<class T>inline void clear(T *arr,int siz,int val=0){memset(arr,val,sizeof(T)*(siz+1));}
struct point{
	int v[maxd];
	inline int operator[](int k)const{return v[k];}
	inline int& operator[](int k){return v[k];}
}a[maxn],tmp[2],_tmp[2];
struct node{
	int ls,rs;
	point mn,mx,v;
}t[maxn];
inline void push_up(int p){
	t[p].mn=t[p].mx=t[p].v;
	for(ri i=0;i<maxd;++i){
		if(t[p].ls)ckmin(t[p].mn[i],t[t[p].ls].mn[i]),ckmax(t[p].mx[i],t[t[p].ls].mx[i]);
		if(t[p].rs)ckmin(t[p].mn[i],t[t[p].rs].mn[i]),ckmax(t[p].mx[i],t[t[p].rs].mx[i]);
	}
}
int cnt;
#define nxt(d) (d+1==maxd?0:d+1)
void build(int &p,int l,int r,int d){
	if(l>r)return;
	ri mid=l+r>>1;
	nth_element(a+l,a+mid+1,a+r,[&](const auto &x,const auto &y){return x[d]<y[d];});
	t[p=++cnt].v=a[mid];
	build(t[p].ls,l,mid-1,nxt(d));
	build(t[p].rs,mid+1,r,nxt(d));
	push_up(p);
}
inline bool est(int p){
	if(!p)return false;
	for(ri i=0;i<maxd;++i)
		if(t[p].mx[i]<tmp[0][i]||tmp[1][i]<t[p].mn[i])
			return false;
	return true;
}
inline bool in(int p){
	for(ri i=0;i<maxd;++i)
		if(t[p].v[i]<tmp[0][i]||tmp[1][i]<t[p].v[i])
			return false;
	return true;
}
bool query(int p){
	return est(p)&&(in(p)||query(t[p].ls)||query(t[p].rs));
}
int m,n,q,rt;
int main(){
	scanf("%*d%*d%*d%d%d%d",&n,&m,&q);
	for(ri i=0;i<maxd;++i)tmp[0][i]=114514;
	while(n--)
		for(ri i=0,x;i<maxd;++i){
			scanf("%d",&x);
			ckmin(tmp[0][i],x);
			ckmax(tmp[1][i],x);
		}
	for(ri i=1;i<=m;++i)
		for(ri j=0;j<maxd;++j)
			scanf("%d",&a[i][j]);
	build(rt,1,m,0);
	if(query(rt))return puts("INCORRECT"),0;
	puts("CORRECT");
	while(q--){
		for(ri i=0;i<maxd;++i)scanf("%d",&t[m+1].v[i]);
		if(in(m+1))puts("OPEN");
		else{
			memcpy(_tmp,tmp,sizeof tmp);
			for(ri i=0;i<maxd;++i)ckmin(tmp[0][i],t[m+1].v[i]),ckmax(tmp[1][i],t[m+1].v[i]);
			puts(query(rt)?"CLOSED":"UNKNOWN");
			memcpy(tmp,_tmp,sizeof tmp);
		}
	}
	return 0;
}
```


---

## 作者：yingkeqian9217 (赞：0)

提供一种 $O(n\log n)$ 的做法。

注意到题目等价于找一个有限空间内的三维长方体，所以第一类点（即第一次输入的点，下同）能够框定该长方体的最小形状，而第二类则要求其不覆盖某些位置，前者是好利用的，求出长方体最小形状之后可以通过判断第二类点和查询点是否在内部判断无解或必然可行。

而必然不可行等价于最小形状并上查询点之后内部存在第二类点，这个东西可以直接静态三维数点维护，这里主要讲一下怎么优化。

注意到我们不在意内部的点的个数，只在意是否存在。而查询一个三维前缀内是否存在数点，等价于二维数点的最值，从而做到 $O(n\log n)$。具体的，注意到新长方体一定有一个顶点没有变化，枚举这个顶点，将其作为坐标原点，此时构成了 $O(1)$ 种（具体而言，8 种）前缀。对于第二类点，也可以类似地加入这些前缀中。

更进一步的，如果我们对于数点所在的方位进行分讨，可以使修改常数降至 1，进一步优化算法。

这里给出的是前一种实现，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define maxn 370005
#define fi first
#define se second
inline int max(int x,int y){return x<y?y:x;}
using namespace std;
const int inf=1e9+7;

int X,Y,Z,n,m,k,ans[maxn];
struct node{
	int x,y,z;
	node():x(0),y(0),z(0){}
	node(int _x,int _y,int _z):x(_x),y(_y),z(_z){}
	bool operator ==(node d){return x==d.x&&y==d.y&&z==d.z;}
	node operator +(node d){return node(max(x,d.x),max(y,d.y),max(z,d.z));}
	int operator [](int p){return (p==0?x:(p==1?y:z));}
}r[2],cur[2];
vector<pair<node,int> >t[8];
struct BIT{
	int t[maxn];
	void update(int x,int k){for(int i=x;i<=Y;i+=i&-i) t[i]=min(t[i],k);}
	int query(int x){
		int res=inf;
		for(int i=x;i;i-=i&-i) res=min(res,t[i]);
		return res;
	}
	void clear(){for(int i=1;i<=Y;i++) t[i]=inf;}
}T;
void solve(vector<pair<node,int> >vec){
	T.clear();
	sort(vec.begin(),vec.end(),[](pair<node,int> p1,pair<node,int> p2){
		return (p1.fi.x==p2.fi.x?p1.se<p2.se:p1.fi.x<p2.fi.x);
	});
	for(auto i:vec){
		node cur=i.fi;
		int id=i.se;
		if(!id)	T.update(cur.y,cur.z);
		else ans[id]=T.query(cur.y)<=cur.z;
	}
}
inline void solve(){
	r[0]=r[1]=node(-inf,-inf,-inf);
	scanf("%d%d%d%d%d%d",&X,&Y,&Z,&n,&m,&k);
	for(int i=1,x,y,z;i<=n;i++){
		scanf("%d%d%d",&x,&y,&z);
		r[0]=r[0]+node(X+1-x,Y+1-y,Z+1-z);
		r[1]=r[1]+node(x,y,z);
	}
	for(int i=1,x,y,z;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		cur[0]=r[0]+node(X+1-x,Y+1-y,Z+1-z),cur[1]=r[1]+node(x,y,z);
		if(cur[0]==r[0]&&cur[1]==r[1]) return puts("INCORRECT"),void();
		for(int j=0;j<8;j++){
			node tmp=node(cur[j&1][0],cur[(j>>1)&1][1],cur[(j>>2)&1][2]);
			if(tmp==node(r[j&1][0],r[(j>>1)&1][1],r[(j>>2)&1][2])) t[j].emplace_back(node(cur[~j&1][0],cur[(~j>>1)&1][1],cur[(~j>>2)&1][2]),0);
		}
	}
	puts("CORRECT");
	for(int i=1,x,y,z;i<=k;i++){
		scanf("%d%d%d",&x,&y,&z);
		cur[0]=r[0]+node(X+1-x,Y+1-y,Z+1-z),cur[1]=r[1]+node(x,y,z);
		if(cur[0]==r[0]&&cur[1]==r[1]){
			ans[i]=-1;
			continue;
		}
		for(int j=0;j<8;j++){
			node tmp=node(cur[j&1][0],cur[(j>>1)&1][1],cur[(j>>2)&1][2]);
			if(tmp==node(r[j&1][0],r[(j>>1)&1][1],r[(j>>2)&1][2])){
				t[j].emplace_back(node(cur[~j&1][0],cur[(~j>>1)&1][1],cur[(~j>>2)&1][2]),i);
				break;
			}
		}
	}
	for(int i=0;i<8;i++) solve(t[i]);
	for(int i=1;i<=k;i++)
	 if(ans[i]==-1) puts("OPEN");
	 else puts(ans[i]?"CLOSED":"UNKNOWN");
}
signed main(){
	signed T=1;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

这种憨憨题是咋被评为 `*2700` 的。

考虑合法时间是三维空间中的一个立方体。我们可以求出最小的正方体，他包含的所有点都是一定打开的（同时可以判矛盾）

现在判断另一点是否可能在立方体中。考虑加入一个点，会拓展新的最小立方体的边界。三维数点计算立方体中有无倒闭的时间点即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int k,l1,l2,l3,q,n,m,xmn,xmx,ymn,ymx,zmn,zmx,op[MAXN],ans[MAXN];
struct INFO {int op,x,y,z,id,rnk;}t[MAXN*10];
int tr[MAXN];
void update(int pos,int v) {
	while(pos<=l3) tr[pos]+=v,pos+=pos&-pos;
	return ;	
}
int query(int pos) {
	int ans=0;
	while(pos) ans+=tr[pos],pos-=pos&-pos;
	return ans;	
}
void cdq(int l,int r) {
	if(l==r) return ;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	sort(t+l,t+r+1,[](INFO A,INFO B) {
		if(A.y!=B.y) return A.y<B.y;
		return A.rnk<B.rnk;
	});
	ffor(i,l,r) {
		if(t[i].op==1&&t[i].rnk<=mid) update(t[i].z,1);
		if(t[i].op==2&&t[i].rnk>mid) {
			if(t[i].id>0) ans[t[i].id]+=query(t[i].z);
			else ans[-t[i].id]-=query(t[i].z);	
		}
	}
	ffor(i,l,r) if(t[i].op==1&&t[i].rnk<=mid) update(t[i].z,-1);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>l1>>l2>>l3>>n>>m>>q;
	xmn=l1+1,xmx=0;
	ymn=l2+1,ymx=0;
	zmn=l3+1,zmx=0;
	ffor(i,1,n) {
		int x,y,z;
		cin>>x>>y>>z;
		xmn=min(xmn,x),xmx=max(xmx,x);
		ymn=min(ymn,y),ymx=max(ymx,y);
		zmn=min(zmn,z),zmx=max(zmx,z);	
	}
	ffor(i,1,m) {
		int x,y,z;
		cin>>x>>y>>z;
		if(xmn<=x&&x<=xmx&&ymn<=y&&y<=ymx&&zmn<=z&&z<=zmx) return cout<<"INCORRECT",0;
		t[i]={1,x,y,z,i};
	}
	k=m;
	ffor(i,1,q) {
		int x,y,z;
		cin>>x>>y>>z;
		if(xmn<=x&&x<=xmx&&ymn<=y&&y<=ymx&&zmn<=z&&z<=zmx) op[i]=1;
		else {
			int Xmn=min(xmn,x),Xmx=max(xmx,x);
			int Ymn=min(ymn,y),Ymx=max(ymx,y);
			int Zmn=min(zmn,z),Zmx=max(zmx,z);
			t[++k]={2,Xmx,Ymx,Zmx,i};
			t[++k]={2,Xmn-1,Ymx,Zmx,-i};
			t[++k]={2,Xmx,Ymn-1,Zmx,-i};
			t[++k]={2,Xmx,Ymx,Zmn-1,-i};
			t[++k]={2,Xmn-1,Ymn-1,Zmx,i};
			t[++k]={2,Xmn-1,Ymx,Zmn-1,i};
			t[++k]={2,Xmx,Ymn-1,Zmn-1,i};
			t[++k]={2,Xmn-1,Ymn-1,Zmn-1,-i};
		}
	}
	sort(t+1,t+k+1,[](INFO A,INFO B) {
		if(A.x!=B.x) return A.x<B.x;
		return A.op<B.op;	
	});
	ffor(i,1,k) t[i].rnk=i;
	if(k) cdq(1,k);
	cout<<"CORRECT\n";
	ffor(i,1,q) if(op[i]) cout<<"OPEN\n";
	else if(!ans[i]) cout<<"UNKNOWN\n";
	else cout<<"CLOSED\n";
	return 0;
}
```

---

