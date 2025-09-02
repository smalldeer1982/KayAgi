# CPAIR - Counting pairs

## 题目描述

给出一个长度为 $N$ 的非负整数序列 $A$，回答 $Q$ 个询问。每个询问包含 $3$ 个数：$v,a,b$，回答序列 $A$ 中有多少个区间的最小值 $\ge v$，且区间的长度在 $[a,b]$ 范围内。

## 说明/提示

- $1 \le N,Q \le 10^5$
- $1 \le a \le b \le N$
- $0 \le v,A_i \le 10^9$

## 样例 #1

### 输入

```
5 3
5 3 2 7 4
3 2 3
2 2 5
4 1 1```

### 输出

```
2
10
3```

# 题解

## 作者：EuphoricStar (赞：1)

## 题意

给定 $N$ 个非负整数 $A_1,A_2,...,A_N$ 和 $Q$ 组询问 $(v_j,a_j,b_j)$，对于第 $j$ 组询问，你需要回答满足 $1 \le l \le r \le N$ 且 $a_j \le r - l + 1 \le b_j$ 且 $\sum\limits_{k=l}^r [A_k \ge v_j] = r - l + 1$ 的整数对 $(l,r)$ 的数量。

## 思路

考虑将询问离线，维护一个包含当前所有已经加进来的元素的极长连续区间的 `set`。每次加进来一个元素就在 `set` 中找到它的前驱和后继，右/左端点下标相差 $1$ 就合并。

如何计算每个极长区间的贡献？考虑一个长度为 $x$ 的极长区间，它包含 $x$ 个长度为 $1$ 的子区间，$x - 1$ 个长度为 $2$ 的子区间，……，$1$ 个长度为 $x$ 的子区间。设长度为 $i$ 的区间的答案为 $ans_i$，则加进长度为 $x$ 的极长区间就相当于 $i \in [1,x],\ ans_i \gets ans_i + x - i + 1$。将它拆成 $ans_i \gets ans_i + x + 1$ 和 $ans_i \gets ans_i - i$，树状数组/线段树维护区间和即可。若删除，则取相反数。

时间复杂度 $O(N \log N + Q \log N)$。

## 代码

[code](https://pastebin.ubuntu.com/p/9BSqMjy9vx/)

---

## 作者：xxseven (赞：0)

好题，怎么会没人做呢。

首先把权值离散化。

询问出现了对区间最小值的限制，这种情况我们通常可以选择离线处理，将限制逐步放宽，这样把满足限制的数看作 $1$，不满足的看作 $0$，最多只会引入 $n$ 次修改操作。

既然权值现在只有 $0,1$，那么我们就考虑值为 $1$ 即满足限制的连续段带来的影响。

很显然，长度为 $x$ 的连续段会带来 $x$ 个长为 $1$ 的区间，$x-1$ 个长为 $2$ 的区间，以此类推。

当我们将一个数的权值修改时，它会将左右两端的连续段合并成一个新连续段。使用并查集即可快速求出左右两边连续段的长度。

那么以区间长度作为下标，区间个数作为值，我们就需要实现区间加减等差数列，区间求和。

使用线段树维护，由于起点都为 $1$，等差数列加等差数列还是等差数列，打两个懒标记即可。

时间复杂度 $O(q \log(q+n)+n \log n)$，代码见下。


```cpp
#include<bits/stdc++.h>
using namespace std;
using i64=long long;
const int N=1e5+6;
struct ask{
	int v,l,r,id;
	bool operator < (ask b){
		return v>b.v;//逐步放宽最小值限制 
	}
}f[N];
vector<int> g[N];
int n,m,a[N],b[N<<1],bn,pre[N],val[N],add[N];
int find(int x){
	return x==pre[x]?x:pre[x]=find(pre[x]);
}
i64 ans[N],t[N<<2];
pair<i64,i64> lz[N<<2];//两个懒标记维护首项和公差 
#define mid (L+R>>1)
void Add(int pos,int L,int R,int k,int f){
	t[pos]+=1ll*(R-L+1)*(k-1ll*(L-1)*f+k-1ll*(R-1)*f)/2; 
	lz[pos].first+=k; lz[pos].second+=f;
}
void pushdown(int pos,int L,int R){
	if(L==R) return;
	Add(pos<<1,L,mid,lz[pos].first,lz[pos].second); 
	Add(pos<<1|1,mid+1,R,lz[pos].first,lz[pos].second);
	lz[pos]={0,0};
}
void update(int pos,int L,int R,int x,int y,int k,int f){
	if(x>R||y<L) return;
	if(x<=L&&R<=y) return Add(pos,L,R,k,f);
	pushdown(pos,L,R);
	update(pos<<1,L,mid,x,y,k,f);
	update(pos<<1|1,mid+1,R,x,y,k,f);
	t[pos]=t[pos<<1]+t[pos<<1|1];
}
i64 qry(int pos,int L,int R,int x,int y){
	if(x>R||y<L) return 0;
	if(x<=L&&R<=y) return t[pos];
	pushdown(pos,L,R);
	return qry(pos<<1,L,mid,x,y)+qry(pos<<1|1,mid+1,R,x,y);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>a[i]; b[i]=a[i];
		pre[i]=i;
	}
	for(int i=1;i<=m;++i){
		cin>>f[i].v>>f[i].l>>f[i].r;
		f[i].id=i;
		b[n+i]=f[i].v;
	}
	sort(b+1,b+n+m+1);
	sort(f+1,f+m+1);
	bn=unique(b+1,b+n+m+1)-b-1;
	for(int i=1;i<=n;++i){
		a[i]=lower_bound(b+1,b+bn+1,a[i])-b;
		g[a[i]].push_back(i);
	}
	// 以上为离散化 
	for(int lst=bn,i=1;i<=m;++i){
		f[i].v=lower_bound(b+1,b+bn+1,f[i].v)-b;
		while(lst>=f[i].v) {
			for(int v:g[lst]){ //合并两边的连续块 
				int x=0,y=0;
				if(add[v-1]) {
					int x=find(v-1);
					val[v]+=val[x];
					update(1,1,n,1,val[x],-val[x],-1);
					pre[x]=v;
				}
				if(add[v+1]) {
					int y=find(v+1);
					val[v]+=val[y];
					update(1,1,n,1,val[y],-val[y],-1);
					pre[y]=v;
				}
				val[v]++;
				update(1,1,n,1,val[v],val[v],1);
				add[v]=1;
			}
			lst--;
		}
		ans[f[i].id]=qry(1,1,n,f[i].l,f[i].r);
	}
	for(int i=1;i<=m;++i) cout<<ans[i]<<'\n';
	return 0;
}

```

希望这篇题解能够帮到你！

---

## 作者：zhr2021 (赞：0)

# [SP5542 CPAIR - Counting pairs](https://www.luogu.com.cn/problem/SP5542) 题解
## solution
考虑只有一个询问时怎样做。我们其实只需要考虑 $a_i\ge v$ 的数，此时这些数在序列上连成几段。开一棵线段树（其实分块要好写很多，本题数据较小，推荐分块），存储每种长度的区间分别有多少个（即维护一个数组，数组中下标为 $i$ 的位置存长度为 $i$ 的区间有多少个，原问题转化为区间求和问题）。这样就可以以 $O( \log N)$ 的时间复杂度解决单个问题。

每个段的贡献如何？我们发现，对于长度为 $len$ 的连续段，可以产生长度为 $1$ 的区间 $len$ 个，产生长度为 $2$ 的区间 $len-1$ 个，$\dots$，产生长度为 $len$ 的区间 $1$ 个，在线段树上相当于区间加等差数列。

回到原来的问题，我们只需要将询问和序列都离线下来，从大到小处理即可。时间复杂度 $O(N\log N+Q\log N)$。

## code
代码有详细注释：

```cpp
#include<bits/stdc++.h>
#define L long long
using namespace std;
inline L read(){
	L x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<3ll)+(x<<1ll)+(ch^48ll);ch=getchar();}
	return w?-x:x;
}
const L N=1e5+10;
struct Node{
	L l,r;
	L sum,a1,d;//维护区间和，区间加等差数列的首项与公差 
}tr[N<<2];
#define ls p<<1
#define rs p<<1|1
void pushdown(L p){//区间加等差数列的线段树 
	tr[ls].a1+=tr[p].a1;
	tr[ls].d+=tr[p].d;
	tr[ls].sum+=((tr[p].a1+
				  tr[p].a1+tr[p].d*(tr[ls].r-tr[ls].l))*
				(tr[ls].r-tr[ls].l+1)/2);
	tr[rs].a1+=(tr[p].a1+(tr[rs].l-tr[p].l)*tr[p].d);
	tr[rs].d+=tr[p].d;
	tr[rs].sum+=((tr[p].a1+(tr[rs].l-tr[p].l)*tr[p].d+
				  tr[p].a1+(tr[rs].r-tr[p].l)*tr[p].d)*
				  (tr[rs].r-tr[rs].l+1)/2);
	tr[p].a1=tr[p].d=0;
	return;
}
void pushup(L p){
	tr[p].sum=tr[ls].sum+tr[rs].sum;
	return;
}
void build(L p,L l,L r){
	tr[p].l=l,tr[p].r=r;
	if(l==r){
		tr[p].a1=tr[p].d=tr[p].sum=0;
		return;
	}
	L mid=(tr[p].l+tr[p].r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	return;
}
void add(L p,L l,L r,L st,L dd){
	if(l>r) return;
	if(l<=tr[p].l&&tr[p].r<=r){
		tr[p].a1+=(st+(tr[p].l-l)*dd);
		tr[p].sum+=(st+(tr[p].l-l)*dd+
					st+(tr[p].r-l)*dd)*
					(tr[p].r-tr[p].l+1)/2;
		tr[p].d+=dd;
		return;
	}
	pushdown(p);
	L mid=(tr[p].l+tr[p].r)>>1;
	if(l<=mid) add(ls,l,r,st,dd);
	if(mid<r)  add(rs,l,r,st,dd);
	pushup(p);
}
L qry(L p,L l,L r){//查询区间和
	if(l>r) return 0;
	if(l<=tr[p].l&&tr[p].r<=r) return tr[p].sum;
	pushdown(p);
	L res=0,mid=(tr[p].l+tr[p].r)>>1;
	if(l<=mid) res+=qry(ls,l,r);
	if(mid<r)  res+=qry(rs,l,r);
	return res;
}
#undef ls
#undef rs
struct qurr{
	L val,mil,mal,id;
	bool operator < (const qurr &x) const{return val>x.val;};
}q[N];
struct Arr{
	L pos,val;
	bool operator < (const Arr &x) const{return val>x.val;};
}a[N];
L len[N],ans[N];
int main(){
	L n=read(),m=read();
	build(1,1,n);
	for(L i=1;i<=n;i++){
		a[i].val=read();
		a[i].pos=i;
	}
	sort(a+1,a+n+1);
	for(L i=1;i<=m;i++)
	q[i].val=read(),q[i].mil=read(),q[i].mal=read(),q[i].id=i;
	sort(q+1,q+m+1);
	L fro=1;
	for(L i=1;i<=m;i++){
		while(a[fro].val>=q[i].val&&fro<=n){//把大于等于val的数加入 
			L lenl=len[a[fro].pos-1],lenr=len[a[fro].pos+1];
			//加入一个数会连接左右，小心计算贡献 
			add(1,1,lenl,-lenl,1);
			add(1,1,lenr,-lenr,1);//把以前的删掉 
			L nlen=lenl+lenr+1;
			add(1,1,nlen,nlen,-1);//加上合并后的 
			len[a[fro].pos-lenl]=nlen;
			len[a[fro].pos+lenr]=nlen;//维护段的长度 
			fro++; 
		}
		ans[q[i].id]=qry(1,q[i].mil,q[i].mal);
	}
	for(L i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

