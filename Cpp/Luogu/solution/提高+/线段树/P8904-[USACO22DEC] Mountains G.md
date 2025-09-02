# [USACO22DEC] Mountains G

## 题目描述

沿着 Farmer John 的农场边缘有 $N(1 \le N \le 2000)$ 座排成一行等间隔分布的山。这些山可以用一个高度数组 $h_1,h_2, \cdots ,h_N$ 表示。对于山 $i$，如果没有一座山严格高于连接山 $j$ 和 $i$ 山顶的视线，则可以看到山 $j$。形式化地说，对于两座山 $i<j$，如果不存在 $k$ 使得 $i<k<j$ 并且 $(k,h_k)$ 高于连接 $(i,h_i)$ 和 $(j,h_j)$ 的线段，则这两座山之间互相可以看到对方。给定 $Q(1 \le Q \le 2000)$ 次更新操作，每次更新增加一座山的高度。求每次更新后可以互相看到的山的无序对数。 

## 说明/提示

### 样例 1 解释

初始时，以下的山之间可以互相看到：$(1,2)$，$(2,3)$，$(2,5)$，$(3,4)$，$(3,5)$，$(4,5)$，共 $6$ 对。

第一次更新后，山 $4$ 的高度为 $4$，这不会阻挡现有的可见性，但使得山 $4$ 现在可以看到山 $2$，从而使得答案变为 $7$。

第二次更新后，山 $1$ 的高度为 $5$，这不会阻挡现有的可见性，但使得山 $1$ 现在可以看到山 $3$，$4$ 和 $5$，从而使得答案变为 $10$。

第三次更新后，山 $3$ 的高度为 $5$，阻挡了山 $1$ 看到山 $4$，阻挡了山 $2$ 看到山 $4$ 和 $5$，同时由于该山本就可以看到其他所有山，所以并没有使得该山看到更多的山，从而使得答案变为 $7$。

### 测试点性质

 - 测试点 $2-5$ 满足 $N,Q \le 100$。
 - 测试点 $6-11$ 满足 $Q \le 10$。
 - 测试点 $12-21$ 没有额外性质。

## 样例 #1

### 输入

```
5
2 4 3 1 5
3
4 3
1 3
3 2```

### 输出

```
7
10
7```

# 题解

## 作者：Lonely_NewYear (赞：8)

# P8904 题解

模拟。

## 题目大意

有 $n$ 座山，每座山有高度 $h_i$，每次提高某个山的高度，同时询问有多少组山能互相看到（能互相看到指山峰连线上没有阻挡）。

## 题目分析

考虑暴力用 $n$ 个 set 维护每个山能看见的右边的山。

对于初始高度，枚举第 $i$ 个山峰，向右不断找能看见的山，同时计算视线斜率，复杂度 $O(n^2\log n)$。

每次提高第 $x$ 座山峰的高度时，枚举 $x$ 左边的山峰 $i$，先判断 $x$ 能不能被看见，能的话就向右依次删除被 $x$ 挡住的山峰，对于第 $x$ 座山，直接重构对应的 set。因为对于每个 $i<x$，每次修改最多使它能看见的山峰数加 1，所以最多删除 $n+q$ 次。对于 $x$，每次最多使它能看见的山峰数加 $n$，所有山加起来最多 $nq$ 次，复杂度 $O((n^2+nq)\log n)$。

总复杂度 $O((n^2+nq)\log n)$，常数非常大，不开 O2 过不去，开 O2 最慢的点 2.22s。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2001;
int n,q;
int h[MAXN];
double cal(int i,int j){
	return 1.0*(h[j]-h[i])/(j-i);
}
set<int> st[MAXN];
int lower(int i,int x){
	auto p=st[i].lower_bound(x);
	p--;
	return *p;
}
int upper(int i,int x){
	auto p=st[i].upper_bound(x);
	return *p;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>h[i];
	int ans=0;
	for(int i=1;i<=n;i++){
		st[i].insert(0);
		st[i].insert(n+1);
		double now=-1e9;
		for(int j=i+1;j<=n;j++)
			if(now<=cal(i,j))now=cal(i,j),st[i].insert(j),ans++;
	}
	cin>>q;
	while(q--){
		int x,y;
		cin>>x>>y;
		h[x]+=y;
		for(int i=1;i<x;i++){
			int y=lower(i,x);
			if(y&&cal(i,y)>cal(i,x))continue;
			if(st[i].find(x)==st[i].end())st[i].insert(x),ans++;
			y=upper(i,x);
			while(y<=n){
				if(cal(i,x)<=cal(i,y))break;
				st[i].erase(y),ans--;
				y=upper(i,y);
			}
		}
		ans-=st[x].size()-2;
		st[x].clear();
		st[x].insert(0);
		st[x].insert(n+1);
		double now=-1e9;
		for(int j=x+1;j<=n;j++)
			if(now<=cal(x,j))now=cal(x,j),st[x].insert(j),ans++;
		cout<<ans<<'\n';
	}
	return 0;
}
```

谢谢观看！

---

## 作者：vectorwyx (赞：8)

山的高度只可能升高，考虑对每个 $i$ 维护所有可行的二元组 $(i,j),i<j$。修改 $k$ 时，原本的 $i<k,j>k$ 的可行二元组 $(i,j)$ 可能变为不可行，条件是 $h_k> h_i+\frac{h_i-h_j}{i-j}(k-i)\iff \frac{h_i-h_j}{i-j}<\frac{h_i-h_k}{i-k}$。对每个 $i$ 开一棵序列上的线段树维护 $\min f(i,j>i)$，其中 $f(i,j)=\frac{h_i-h_j}{i-j}$，即斜率。然后暴力递归找出所有 $f(i,j>k)<f(i,k)$，删掉。对于新产生的可行二元组，暴力枚举另一个端点判断是否可行并处理。由于每次操作最多会增加 $n$ 个二元组，所以总复杂度为 $O((n^2+nq)\log n)$。

代码如下：
```cpp
#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

//14:50~15:20,15:20
const int N=2005,inf=1.1e9;
struct frac{
	int fz,fm;
	frac(){fz=0,fm=1;}
	frac(int x,int y){if(y<0) x=-x,y=-y;fz=x,fm=y;}
	bool operator<(const frac &x)const{re (ll)fz*x.fm<(ll)fm*x.fz;}
	bool operator>(const frac &x)const{re (ll)fz*x.fm>(ll)fm*x.fz;}
	bool operator<=(const frac &x)const{re (ll)fz*x.fm<=(ll)fm*x.fz;}
	bool operator>=(const frac &x)const{re (ll)fz*x.fm>=(ll)fm*x.fz;}
};
int h[N],n,q;
frac f(int i,int j){re frac(h[i]-h[j],i-j);}
struct Sgt{
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
struct Node{
	frac mn,mx;
	int cnt;
	Node(){mn=frac(inf,1);mx=frac(-inf,1);cnt=0;}
}tr[N<<2];
int od;
void ps(int x){
	tr[x].mn=min(tr[ls].mn,tr[rs].mn);
	tr[x].mx=max(tr[ls].mx,tr[rs].mx);
	tr[x].cnt=tr[ls].cnt+tr[rs].cnt;
}
void build(int x,int l,int r){
	if(l==r){
		tr[x].mn=tr[x].mx=f(od,l);
		tr[x].cnt=0;
		re;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	ps(x);
}
void upd(int x,int l,int r,int aim){
//	if(x==1) printf("upd(%d,%d)\n",od,aim);
	if(l==r){
		tr[x].cnt=1;
		re;
	}
	if(aim<=mid) upd(ls,l,mid,aim);
	else upd(rs,mid+1,r,aim);
	ps(x);
}
bool set(int x,int l,int r,int aim,frac v){
//	if(x==1) printf("%d:set(%d,(%d/%d))\n",od,aim,v.fz,v.fm);
	if(l==r) re tr[x].mn=tr[x].mx=v,1;
	if(aim<=mid){
		bool ret=set(ls,l,mid,aim,v);
		ps(x);
		re ret;
	}
	bool ret=tr[ls].mx<=v&&set(rs,mid+1,r,aim,v);
	ps(x);
	re ret;
}
void play(int x,int l,int r,int k,frac lim){
//	printf("%d:play(%d,%d,%d,%d,(%d/%d)) mn=(%d/%d)\n",od,x,l,r,k,lim.fz,lim.fm,tr[x].mn.fz,tr[x].mn.fm);
	if(tr[x].cnt==0||tr[x].mn>=lim||r<=k) re;
	if(l==r){
//		printf("(%d,%d) < %d/%d\n",od,l,lim.fz,lim.fm);
		tr[x].cnt=0;
		re;
	}
	play(ls,l,mid,k,lim);
	play(rs,mid+1,r,k,lim);
	ps(x);
}
#undef ls
#undef mid
#undef rs
}tr[N];

void build(int i){
//	printf("build(%d)!!!!!!!!!!!!!!!!!!!!!!!!!\n",i);
	if(i==n) re;
	tr[i].build(1,i+1,n);
	frac x=frac(-inf,1);
	fo(j,i+1,n) if(f(i,j)>=x){
//		printf("f(%d,%d)=(%d/%d) x=(%d/%d)\n",i,j,f(i,j).fz,f(i,j).fm,x.fz,x.fm);
		tr[i].upd(1,i+1,n,j);
		x=f(i,j);
	}
}

signed main(){
//	freopen("gen.txt","r",stdin);freopen("mine.txt","w",stdout);
	cin>>n;
	fo(i,1,n) h[i]=read(),tr[i].od=i;
	fo(i,1,n-1) build(i);
	cin>>q;
	while(q--){
		int k=read(),v=read();
		h[k]+=v;
		fo(i,1,k-1) tr[i].play(1,i+1,n,k,f(i,k));
		fo(i,1,k-1){
			if(tr[i].set(1,i+1,n,k,f(i,k))) tr[i].upd(1,i+1,n,k);
		}
		build(k);
		int ans=0;
		fo(i,1,n) ans+=tr[i].tr[1].cnt;
		cout<<ans<<'\n';
	}
	return 0;
}
}
/*
5
2 4 3 1 5
3
4 3
1 3
3 2
-------------------------------------------------
7
10
7
*/










signed main(){re vectorwyx::main();}
```

---

## 作者：LJ07 (赞：4)

一个暴力做法。

前置题目：[楼房重建](https://www.luogu.com.cn/problem/P4198)

发现就是搞 $n$ 个楼房重建，具体的我们对 $i$ 维护 $i+1\cdots n$ 的 楼房重建 线段树。每次修改只需要在 $1\cdots x-1$ 的线段树上修改，然后再重构第 $x$ 棵线段树即可（甚至直接暴力单点该代替重构也行）。

时间复杂度 $O(nq\log^2n)$。

还有大佬有 $O(nq\log n)$ 的 nb 做法，膜拜。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define U(i,a,b) for(int i(a),i##e(b);i<=i##e;++i)
#define D(i,b,a) for(int i(b),i##e(a);i>=i##e;--i)
using namespace std;
const int N(2000);
int n,ans,h[N+5],Q;
using pii=pair<int,int>;
#define fi first
#define se second
double calc(pii a,pii b)
{
	return 1.0*(a.se-b.se)/(a.fi-b.fi);
}
struct SegmentTree
{
	int l[N*4+5];
	double mx[N*4+5];
	#define mid (L+R>>1)
	#define Ls rt<<1,L,mid
	#define Rs rt<<1|1,mid+1,R
	int ask(double lim,int rt,int L,int R)
	{
		if(mx[rt]<lim) return 0;
		if(L==R) return mx[rt]>=lim;
		if(mx[rt<<1]<lim) return ask(lim,Rs);
		return ask(lim,Ls)+l[rt]-l[rt<<1];
	}
	void modify(int p,double K,int rt,int L,int R) 
	{
		if(L==R) return (void)(mx[rt]=K,l[rt]=1);
		(p<=mid)?modify(p,K,Ls):modify(p,K,Rs);
		mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
		l[rt]=l[rt<<1]+ask(mx[rt<<1],Rs);
	}
	void build(int st,int rt,int L,int R)
	{
		if (L==R) return (void)(mx[rt]=calc({st,h[st]},{L,h[L]}),l[rt]=1);
		build(st,Ls),build(st,Rs);
		mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
		l[rt]=l[rt<<1]+ask(mx[rt<<1],Rs);
	}
} sgt[N+5];
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin>>n;
	for (int i(1);i<=n;++i) cin>>h[i];
	for (int i(1);i<n;++i) sgt[i].build(i,1,i+1,n),ans+=sgt[i].l[1];
	for (cin>>Q;Q--;)
	{
		int x,y; cin>>x>>y;
		h[x]+=y;
		for (int i(1);i<x;++i)
		{
			ans-=sgt[i].l[1];
			sgt[i].modify(x,calc({i,h[i]},{x,h[x]}),1,i+1,n);
			ans+=sgt[i].l[1];
		}
		if (x<n)
		{
			ans-=sgt[x].l[1];
			sgt[x].build(x,1,x+1,n);
			ans+=sgt[x].l[1];
		}cout<<ans<<'\n';
	}return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

# P8904 题解



## 思路分析

线段树模拟。

首先解决静态版本：对于每个 $i$，统计出有多少个 $j>i$ 且 $i,j$ 能够互相看到，显然这等价于 $\forall i<k\le j: \operatorname{slope}(i,j)\ge \operatorname{slope}(i,k)$，因此我们对于每个 $i$，维护 $\operatorname{slope}(i,i+1)\sim\operatorname{slope}(i,n)$ 的前缀 $\max$ 值 $\max_{i,j}$，如果某个 $j$ 满足 $\operatorname{slope}(i,j)=\max_{i,j}$ 就统计 $(i,j)$ 到答案中。

接下来考虑每次增加山峰 $x$ 的高度，对于所有 $(x,j)$ 的对直接暴力重构 $\max_{x,j}$，重算答案即可，而对于 $(i,x)$ 的对，注意到修改完之后一定是增加了 $\operatorname{slope}(i,x)$ 的值，那么在 $\max_{i,j}$ 上，相当于增加了一段的值，假设修改 $x$ 后，改变了 $[x,k]$ 这一段的 $\max_{i,j}$ 值，那么 $(x,k]$ 中所有的 $j$ 都有 $\operatorname{slope}(i,j)<\operatorname{slope}(i,x)$，这样的 $(i,j)$ 会被 $x$ 挡住，对答案的贡献设为 $0$，而 $x$ 更新了 $\max_{i,x}$ 的值，$(i,x)$ 对答案的贡献变为 $1$，需要特别判断修改后 $\operatorname{slope}(i,x)$ 的恰好等于原本的 $\max_{i,x}$ 的值，此时不用更新 $\max_{i,x}$ 不过要添加贡献。

因此我们开 $2n$ 棵线段树，$n$ 棵维护 $\max_{i,j}$，支持线段树上二分和区间覆盖，$n$ 棵维护 $(i,j)$ 对答案的贡献，支持单点加区间清零和统计总和。

时间复杂度 $\Theta((n^2+nq)\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2022;
const double eps=1e-4,INF=1e9;
double sl[MAXN][MAXN],pre[MAXN][MAXN];
class SgtTr1 {
	private:
		struct node {
			double max,tag;
		}	tree[MAXN<<2];
		inline int left(int x) { return x<<1; }
		inline int right(int x) { return x<<1|1; }
		inline void pushup(int pos) { tree[pos].max=max(tree[left(pos)].max,tree[right(pos)].max); }
		inline void pushdown(int pos) {
			if(fabs(tree[pos].tag)<eps) return ;
			tree[left(pos)].max=tree[right(pos)].max=tree[pos].tag;
			tree[left(pos)].tag=tree[right(pos)].tag=tree[pos].tag;
			tree[pos].tag=0;
		}
	public:
		inline void Build(int id,int l,int r,int pos) {
			tree[pos].tag=0;
			if(l==r) {
				tree[pos].max=pre[id][l];
				return ;
			}
			int mid=(l+r)>>1;
			Build(id,l,mid,left(pos));
			Build(id,mid+1,r,right(pos));
			pushup(pos);
		}
		inline void Modify(int ul,int ur,double val,int l,int r,int pos) {
			if(ul<=l&&r<=ur) {
				tree[pos].max=tree[pos].tag=val;
				return ;
			}
			pushdown(pos);
			int mid=(l+r)>>1;
			if(ul<=mid) Modify(ul,ur,val,l,mid,left(pos));
			if(mid<ur) Modify(ul,ur,val,mid+1,r,right(pos));
			pushup(pos);
		}
		inline int Binary(double ther,int l,int r,int pos) {
			if(l==r) return l;
			int mid=(l+r)>>1;
			pushdown(pos);
			if(ther<=tree[left(pos)].max) return Binary(ther,l,mid,left(pos));	
			return Binary(ther,mid+1,r,right(pos));
		}
		inline double Query(int u,int l,int r,int pos) {
			if(l==r) return tree[pos].max;
			int mid=(l+r)>>1;
			pushdown(pos);
			if(u<=mid) return Query(u,l,mid,left(pos));
			return Query(u,mid+1,r,right(pos));
		}
}	S[MAXN];
class SgtTr2 {
	private:
		struct node {
			int sum,tag;
		}	tree[MAXN<<2];
		inline int left(int x) { return x<<1; }
		inline int right(int x) { return x<<1|1; }
		inline void pushup(int pos) { tree[pos].sum=tree[left(pos)].sum+tree[right(pos)].sum; }
		inline void pushdown(int pos,int l,int r) {
			if(tree[pos].tag==-1) return ;
			int mid=(l+r)>>1;
			tree[left(pos)].sum=tree[pos].tag*(mid-l+1);
			tree[right(pos)].sum=tree[pos].tag*(r-mid);
			tree[left(pos)].tag=tree[right(pos)].tag=tree[pos].tag;
			tree[pos].tag=-1;
			return ;
		}
	public:
		inline void Modify(int ul,int ur,int val,int l,int r,int pos) {
			if(ul<=l&&r<=ur) {
				tree[pos].sum=val*(r-l+1);
				tree[pos].tag=val;
				return ;
			}
			pushdown(pos,l,r);
			int mid=(l+r)>>1;
			if(ul<=mid) Modify(ul,ur,val,l,mid,left(pos));
			if(mid<ur) Modify(ul,ur,val,mid+1,r,right(pos));
			pushup(pos);
			return ;
		}
		inline int Query(int ul,int ur,int l,int r,int pos) {
			if(ul<=l&&r<=ur) return tree[pos].sum;
			pushdown(pos,l,r);
			int mid=(l+r)>>1,ret=0;
			if(ul<=mid) ret+=Query(ul,ur,l,mid,left(pos));
			if(mid<ur) ret+=Query(ul,ur,mid+1,r,right(pos));
			return ret;
		}
}	T[MAXN];
int a[MAXN];
inline double slope(int x,int y) {
	return (double)(a[x]-a[y])/(x-y);
}
signed main() {
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;++i) {
		pre[i][0]=-INF;
		for(int j=1;j<=n-i;++j) {
			sl[i][j]=slope(i,i+j);
			pre[i][j]=max(pre[i][j-1],sl[i][j]);
		}
		pre[i][n-i+1]=INF;
		S[i].Build(i,1,n-i+1,1);
		for(int j=1;j<=n-i;++j) {
			if(fabs(sl[i][j]-pre[i][j])<eps) {
				++ans;
				T[i].Modify(j,j,1,1,n-i,1);
			}
		}
	}
	int q;
	scanf("%d",&q);
	while(q--) {
		int x,y;
		scanf("%d%d",&x,&y);
		a[x]+=y;
		for(int i=1;i<x;++i) {
			double k=slope(i,x);
			sl[i][x-i]=k;
			int d=S[i].Binary(k,1,n-i+1,1)+i-1;
			if(d<=x) {
				double org=S[i].Query(x-i,1,n-i+1,1),bef=(double)(a[x]-y-a[i])/(x-i);
				S[i].Modify(x-i,x-i,max(k,org),1,n-i+1,1);
				if(bef<org&&org<=k) {
					++ans;
					T[i].Modify(x-i,x-i,1,1,n-i,1);
				}
				continue;
			} 
			S[i].Modify(x-i,d-i,k,1,n-i+1,1);
			ans-=T[i].Query(x-i,d-i,1,n-i,1);
			T[i].Modify(x-i,d-i,0,1,n-i,1);
			++ans;
			T[i].Modify(x-i,x-i,1,1,n-i,1);
		}
		for(int i=1;i<=n-x;++i) {
			sl[x][i]=slope(x,x+i);
			pre[x][i]=max(pre[x][i-1],sl[x][i]);
		}
		S[x].Build(x,1,n-x+1,1);
		ans-=T[x].Query(1,n-x,1,n-x,1);
		T[x].Modify(1,n-x,0,1,n-x,1);
		for(int i=1;i<=n-x;++i) {
			if(fabs(sl[x][i]<pre[x][i])<eps) {
				++ans;
				T[x].Modify(i,i,1,1,n-x,1);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：cff_0102 (赞：1)

做这道题能让你深刻领悟到以下几点：

- 现在的评测机运行速度比你想象中的快。
- 学校 OJ 的评测机除了 `endl` 要花上百倍的时间以外，其它操作的速度都比某些网站的快多了。
- 函数调用很慢，特别是如果你要调用上亿次的话。
- 在某些题目，即使你认为你的某个操作可以较大的优化代码的常数，建议还是把优化常数交给 O2 优化，说不定你自以为的“常数优化”让 O2 的优化空间更少了，导致超时。

---

注意到我们可以直接暴力修改暴力查询，时间复杂度 $O(N^2Q)$，可以通过。

具体的，直接枚举从 $i$ 开始右侧的所有点（左侧的点在此之前已经被计算过了），然后计算这两点的斜率，如果这个斜率大于点 $i$ 右侧当前的最大斜率就更新最大斜率和答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2003;
int h[N];
#define slope(xa,ya,xb,yb) (((double)yb-ya)/(xb-xa))
//double slope(double xa,double ya,double xb,double yb){
//	return (yb-ya)/(xb-xa);
//}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;for(int i=1;i<=n;i++)cin>>h[i];
	int q;cin>>q;while(q--){
		int x,y;cin>>x>>y;h[x]+=y;
		int ans=0;
		for(int i=1;i<=n;i++){
			double k=-1e9;
			for(int j=i+1;j<=n;j++){
				double tmp=slope(i,h[i],j,h[j]);
				ans+=(k<=tmp);
				k=max(k,tmp);
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

本题代码要注意的点在题解开头已经提到过了。

---

## 作者：初星逝者 (赞：1)

$O(n^2  \times q)$ 成功搞过去......

最简单的做法。

初中数学学过吧。

把每一个点抽象成 $(i,h_i)$ 的形式，那么可以算出每两个点相连的直线，记录一下最大值，如果更大那么就记录最大值，`ans++`。

史上最短代码！！！！

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,q;
long long h[20005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> h[i];
	}
	cin >> q;
	while(q--){
		long long x,y;
		cin >> x >> y;
		h[x]+=y;
		int l,r;
		int ans=0;
		double k=0;
		for(int i=1;i<=n;i++){
			double maxk=-1000000000;
			for(int j=i+1;j<=n;j++){
				k=(1.0*(h[j]*1.0-h[i]*1.0)/(j*1.0-i*1.0));
				if(k>=maxk){
					maxk=k;
					ans++;
					
				}                                                                          
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：VictorChen (赞：1)

首先我们考虑静态下如何 $O(n^2)$ 地查询本题的答案。

容易发现，对于一座山 $i$，如果它能看到山 $j$，则必然满足两点间不存在任何山，使得其到山 $i$ 的斜率高于 $j$ 到 $i$ 的斜率；

也就是说，如果 $k_{i,j}\geq k_{i,x}\{x\in (i,j)\}$；则 $i$ 与 $j$ 之间是相互可见的。

由此，我们可以想到 $O(n^2)$ 解决静态问题的方法：对于每座山 $i$，维护序列 $k_{i,i+1},k_{i,i+2},\cdots,k_{i,n}$；此时山 $i$ 对最终答案的贡献即为从 $k_{i, i+1}$ 开始的不降子序列的长度。显而易见，可见关系是相互的，所以我们只需要维护每座山可以见到几座后面的山即可；

此做法复杂度为 $O(n^2q)$，可以过前两个子任务；现在我们来考虑如何优化这个算法；

对于每次调整，我们观察到除去高度被改变的山，所有的山维护的序列最多只有一处修改；我们考虑用线段树来维护这个序列；

我们在线段树上存储斜率，线段树上每个节点 $(l,r)$ 记录从 $l$ 到 $r$ 中，从 $a_l$ 开始的不降子序列起始项 $\text{mn}$，结束项 $\text{mx}$，和长度 $\text{val}$。

其次我们来思考如何在线段树上对两个节点进行合并：

- 如果左子的 $\text{mx}$ 小于等于右子的 $\text{mn}$，则显然有当前节点的 $\text{val}$ 即为左右子的 $\text{val}$ 的和；
- 如果左子的 $\text{mx}$ 大于右子的 $\text{mx}$，则显然当前节点的 $\text{val}$ 等于左子的 $\text{val}$；
- 否则我们需要查询在右子中以左子的 $\text{mx}$ 开始的序列长度。

这部分的代码如下：

```cpp
void maintain(int x)
{
    if(p[lson].mx <= p[rson].mx)
    {
        p[x].mn = p[lson].mn;
        p[x].mx = p[rson].mx;

        if(p[lson].mx <= p[rson].mn)
            p[x].val = p[lson].val + p[rson].val;
        else
            p[x].val = p[lson].val + find(rson, p[lson].mx);
    }
    else
    {
        p[x].mx = p[lson].mx;
        p[x].mn = p[lson].mn;
        p[x].val = p[lson].val;
    }
}
```

现在我们的唯一问题是，如何在右子中查询左子的 $\text{mx}$ 开始的序列长度。

定义 $f(x,l)$ 表示在 $x$ 节点内至少以 $l$ 开始的不降序列长度，考虑递归查询：

- 如果当前节点的 $\text{mn}\leq l$，则显然答案为当前节点的 $\text{val}$；
- 如果当前节点的 $\text{mx}<l$，则显然答案为 0（因为不存在节点不小于 $l$）；
- 如果左子的 $\text{mx}<l$，则我们可以直接在右子查询（因为左子不存在节点不小于 $l$）；
- 否则我们的最终序列应该为左子以 $l$ 开始的序列长度，加上右子以左子的 $\text{mx}$ 开始的序列长度；

这部分的代码如下：

```cpp
int find(int x, double l)
{
    if(l <= p[x].mn)
        return p[x].val;
    else if(p[x].mx < l)
        return 0;
    else if(p[lson].mx < l)
        return find(rson, l);

    return find(lson, l) + find(rson, p[lson].mx);
}
```

在可以维护线段树后，我们可以简单地写出如何对线段树进行单点修改；

只需要先找到对应位置修改其 $\text{mx}$ 和 $\text{mn}$，随后像正常的线段树修改，不断更新到根节点路径上的点即可。

对于每次修改，我们只需要重构对应的山的线段树，同时修改所有先前的线段树。

此做法时间复杂度为 $O(nq\log^2 n)$，空间复杂度为 $O(n^2)$，可以通过本题。

附上本题线段树部分的完整代码：

```cpp
class SegTree
{
    private:
        struct Node
        {
            int l, r;
            double mn, mx;

            int val;
        }p[8010];

    public:
        int cent; // 用来记录这个线段树维护的山的编号

        // 树上存储从左到右的不减序列端点与长度
        void buildtree(int x, int l, int r)
        {
            p[x].l = l, p[x].r = r;
            if(p[x].l == p[x].r)
                return;

            int mid = (l+r)/2;
            buildtree(lson, l, mid);
            buildtree(rson, mid+1, r);
        }

        // 用于寻找x节点里以l开头的不减序列长度
        int find(int x, double l)
        {
            if(l <= p[x].mn)
                return p[x].val;
            else if(p[x].mx < l)
                return 0;
            else if(p[lson].mx < l)
                return find(rson, l);
            
            return find(lson, l) + find(rson, p[lson].mx);
        }

        // 用于维护线段树上x节点的值（保证子结点已经maintain过了）
        void maintain(int x)
        {
            if(p[lson].mx <= p[rson].mx)
            {
                p[x].mn = p[lson].mn;
                p[x].mx = p[rson].mx;

                if(p[lson].mx <= p[rson].mn)
                    p[x].val = p[lson].val + p[rson].val;
                else
                    p[x].val = p[lson].val + find(rson, p[lson].mx);
            }
            else
            {
                p[x].mx = p[lson].mx;
                p[x].mn = p[lson].mn;
                p[x].val = p[lson].val;
            }
        }

        // 用于完全重构当前线段树
        void setTree(int x)
        {
            if(p[x].l == p[x].r)
            {
                p[x].mn = p[x].mx = findK(cent, cent+p[x].l);
                p[x].val = 1;

                return;
            }

            setTree(lson); setTree(rson);
            maintain(x);
        }

        // 用于找到当前树对答案的贡献
        int query()
        {
            return p[1].val;
        }

        // 用于更改一个位置的值
        void modify(int x, int pos, double val)
        {
            if(p[x].l == p[x].r)
            {
                p[x].mn = p[x].mx = val;
                p[x].val = 1;

                return;
            }

            if(pos <= p[lson].r) modify(lson, pos, val);
            if(p[rson].l <= pos) modify(rson, pos, val);

            maintain(x);
        }
}tree[2010];
```

---

## 作者：DYYqwq (赞：0)

这是暴力题，你谷神机太强了。

把牛抽象为点 $i,a_i$，每次询问 $O(n^2)$ 扫一遍，记录一下目前斜率的最大值，如果有比最大值大的，就把答案 $+1$。

时间复杂度为 $O(q \times n^2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n , q , a[20010];
signed main()
{
	scanf("%lld" , &n);
	for(int i = 1 ; i <= n ; i ++) scanf("%lld" , &a[i]);
	scanf("%lld" , &q);
	while(q --)
	{
		int x , y , l , r , ans = 0;
		scanf("%lld%lld" , &x , &y);
		a[x] += y;
		for(int i = 1 ; i <= n ; i ++)
		{
			double mx = -1e18;
			for(int j = i + 1 ; j <= n ; j ++)
			{
				double qwq = 1.0 * (a[j] * 1.0 - a[i] * 1.0) / (j * 1.0 - i * 1.0);
				if(qwq >= mx) mx = qwq , ans ++;
			}
		}
		printf("%lld\n" , ans);
	}
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

预处理每个山向右能看到的所有山，用 set 存储。由题意，随着下标的增加，斜率也会增加。

考虑处理修改。让山 $x$ 变高，会导致前面的山视野被阻挡。对于下标 $i|i<x$ 的山，在其 set 上二分 $x$，由于斜率的单调性，可能连续的一段 $j|j>x$ 被挡住了，即 $\operatorname{slope}(i,x)>\operatorname{slope}(i,j)$，这些 $j$ 都要从 $i$ 的 set 中删去。$x$ 可能要加入 $i$ 的 set 中，`lower_bound` 时注意指针不要越界。

然后再预处理一遍 $x$ 的 set。

执行上述操作的同时统计答案。推荐完成本题后试一试[楼房重建](https://www.luogu.com.cn/problem/P4198)。

```cpp
// Title:  Mountains
// Source: USACO22DEC Gold
// Author: Jerrywang
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=2010, inf=1e9;
using namespace std;

int n, a[N]; set<int> S[N];
double slope(int i, int j) {return 1.*(a[j]-a[i])/(j-i);}
bool ok(int i, int x)
{
    auto j=S[i].lower_bound(x);
    if(j==S[i].begin() || *j==x) return 0;
    return 1;
}

int main()
{
    #ifdef Jerrywang
    freopen("in.txt", "r", stdin);
    #endif
    scanf("%d", &n);
    rep(i, 1, n) scanf("%d", a+i);
    ll res=0;
    rep(i, 1, n)
    {
        double mx=-inf;
        rep(j, i+1, n)
            if(slope(i, j)>=mx) // i可以看到j
                mx=slope(i, j), S[i].insert(j);
        res+=S[i].size();
    }
    int T; scanf("%d", &T);
    while(T--)
    {
        int x, y; scanf("%d%d", &x, &y); a[x]+=y;
        rep(i, 1, x-1)
        {
            set<int>::iterator j, nj;
            if(ok(i, x))
            {
                j=--S[i].lower_bound(x);
                if(slope(i, *j)<=slope(i, x))
                    S[i].insert(x), res++;
            }
            j=S[i].upper_bound(x);
            for(; j!=S[i].end(); j=nj)
            {
                if(slope(i, x)<=slope(i, *j)) break;
                nj=next(j), S[i].erase(j), res--;
            }
        }
        res-=S[x].size(); S[x].clear();
        double mx=-inf;
        rep(j, x+1, n)
            if(slope(x, j)>=mx)
                mx=slope(x, j), S[x].insert(j);
        res+=S[x].size();
        printf("%d\n", res);
    }
    
    return 0;
}
```

---

