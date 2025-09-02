# Function

## 题目描述

Serega and Fedor play with functions. One day they came across a very interesting function. It looks like that:

- $ f(1,j)=a[j] $ , $ 1<=j<=n $ .
- $ f(i,j)=min(f(i-1,j),f(i-1,j-1))+a[j] $ , $ 2<=i<=n $ ,  $ i<=j<=n $ .

Here $ a $ is an integer array of length $ n $ .

Serega and Fedya want to know what values this function takes at some points. But they don't want to calculate the values manually. So they ask you to help them.

## 样例 #1

### 输入

```
6
2 2 3 4 3 4
4
4 5
3 4
3 4
2 3
```

### 输出

```
12
9
9
5
```

## 样例 #2

### 输入

```
7
1 3 2 3 4 0 2
4
4 5
2 3
1 4
4 6
```

### 输出

```
11
4
3
0
```

# 题解

## 作者：shiroi (赞：4)

### Description

给定一个DP式子：
$$
f(1,j)=a[j]  (1 \le j \le n)
$$

$$
f(i,j)=min(f(i-1,j),f(i-1,j-1))+a[j] (2 \le i \le n , i \le j \le n)
$$

其中 $a$ 是一个长度为 $n$ 的数组。现在有若干个询问，输入 $x,y$，求 $f(x,y)$ 。



### Solution

观察题目可以发现，$f(i,j)$ 仅可以由 $f(i-1,j)$ 和 $f(i-1,j-1)$ 转移过来。我们可以将其的转移路径画图表示出来，就可以发现这条转移路径必定是由点 $(1,i)$ 开始，先竖直向下转移到 $(x-y+i,i)$  ，之后再沿一条直线转移到 $(x,y)$ 。这里借用下神仙 [LuitaryiJack](https://www.luogu.com.cn/user/115086) 的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/i4mbhy28.png)



现在对此进行感性证明。对于一次询问 $(x,y)$ ，可以发现其相当于从所有合法区间中取 $x$ 个数求和使得结果最小。每个数可以取多次，同时在取到第一个数 $a[i]$ 之后就必须要取所有 $[i,y]$ 之间的数。所以问题就可以被转化为求一个转移的起点 $(1,i)$  来最小化 $f(x,y)$ 的取值。

观察上图可以发现，询问 $(l,r)$ 取数的合法区间为 $[r-l,r]$ 。设 $s[i]$ 表示 $a$ 的前缀和，显然转移起点 $i$ 的贡献为 $s[r] - s[i] + (l - r + i) a[i]$ 。我们可以发现如下两个性质：

- $a[i]$ 一定是 $[r-l,r]$ 区间中的最小值。如果存在一个 $j$ 使得 $i \le j \le r , a[j] \le a[i]$ ，那么 $[j,r]$ 的共同区间贡献完全一致，其他区间都可以全取 $a[j]$ ，结果显然更优。
- $[i+1,r]$ 区间各取一个，其他数全取 $a[i]$ 。根据第一条显然。

基于这两条显然性质，我们就可以构建出一个记录前缀和之后 $O(n^2)$ 对点 $i$ 进行枚举的暴力，然后发现会T，可以考虑优化方法。

对于一个询问 $(x,y)$ ，我们设决策 $k<j$ ,并且 $k$ 结果更优。那么：
$$
s[y]-s[k]+(x-y+k) \cdot a[k] \le  s[y]-s[j]+(x-y+j) \cdot a[j]
$$
化简之后可得：
$$
\frac{(s[k]-a[k]*k)-(s[j]-a[j]*j)}{a[k]-a[j]}<x-y
$$
显然这是一个斜率的式子，斜率优化即可。注意到 $s$ 不单调所以不能直接用单调队列暴力弹队首维护，所以需要用单调栈维护凸包，先二分找到左边界之后在凸包上二分求解满足条件的斜率。具体实现见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

char buf[10000001],*ptr=buf-1;

inline int read()
{
	int x=0,c=*++ptr;
	while(c<48) c=*++ptr;
	while(c>47) x=x*10+c-'0',c=*++ptr;
	return x;
}

const int MAXN = 200005;
struct Query {int x,y,id;} q[MAXN];
int a[MAXN],s[MAXN],st[MAXN],ans[MAXN];
int n,m,tp;

bool operator < (Query a,Query b)
{return a.y<b.y;}

inline double slp(int k,int j)
{
	return ((double)(s[k]-a[k]*k)-
	        (double)(s[j]-a[j]*j))/(double)(a[k]-a[j]);
}

inline int find(int x)
{
	int l=1,r=tp;
	while(l<r)
	{
		int mid=l+r>>1;
		if(st[mid]<x) l=mid+1;
		else r=mid;
	}
	return l;
}

int main(int argc, char const *argv[])
{
	fread(buf,1,sizeof(buf),stdin)[buf]=0;
	n=read();
	for(int i=1; i<=n; ++i)
		s[i]=s[i-1]+(a[i]=read());
	m=read();
	for(int i=1; i<=m; ++i)
		q[i].x=read(),q[i].y=read(),q[i].id=i;
	sort(q+1,q+m+1);
	for(int i=1,j=1; i<=n; i++)
	{
		while(tp && a[st[tp]]>=a[i]) tp--;
		while(tp>1 && slp(st[tp],i)>=slp(st[tp-1],i)) tp--;
		st[++tp]=i;
		while(q[j].y==i && j<=m)
		{
			int l=find(q[j].y-q[j].x),r=tp;
			while(l<r)
			{
				int mid=l+r>>1;
				if(slp(st[mid],st[mid+1])<q[j].x-q[j].y) r=mid;
				else l=mid+1;
			}
			l=st[l],r=q[j].y; ans[q[j].id]=
			    s[r]-s[l]+(q[j].x-(r-l))*a[l]; j++;
		}
	}
	for(int i=1; i<=m; ++i)
		printf("%d\n",ans[i]);
	return 0;
}
```





---

## 作者：李至擎 (赞：3)

感觉不难啊，为什么是 *2900 捏。

发现这个玩意的本质是最初在 $r$，每次不动或向左移动一步，进行 $l$ 次操作，求每次停留的格子权值之和的最小值。显然我们只会停留在至多一个格子上，假设停留在 $i$，那么权值之和就是 $\left(l-r+i\right)a_i+\sum\limits_{j=i+1}^ra_j$，且 $i\in[r-l+1,r]$。

小推一下柿子：$\left(l-r+i\right)a_i+\sum\limits_{j=i+1}^ra_j=\left[\left(l-r\right)a_i+\left(i\cdot a_i+\sum\limits_{j=i+1}^na_j\right)\right]-\sum\limits_{j=r+1}^na_j$。发现中括号外的是定值，中括号里是一个形如 $kx+b$ 这样的直线。我们考虑用李超线段树来求最小值。

但是 $i$ 的范围限制怎么办？因为李超是不支持删除的，我们联想到回滚莫队的处理方式。假设我们现在正在处理左端点在 $[L_i,R_i]$ 范围内的询问，查询区间为 $[l_j,r_j]$，那么在 $[l_j,R_i]$ 范围内的直线我们可以暴力求出结果比较，在 $[R_i+1,r_j]$ 范围内的直线我们用李超树解决。时间复杂度 $O(nB+\left(\dfrac{n}{B}\right)^2\log n)$，其中 $B$ 是块长，平衡后可以做到 $O(n\sqrt{n\log n})$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
using namespace std;
const int inf=1e18,eps=0;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct seg{
	int k,b;
	int calc(int x){
		return k*x+b;
	}
}s[100005];
db cross(int i,int j){
	return 1.0*(s[j].b-s[i].b)/(s[i].k-s[j].k);
}
int chmin(int i,int j,int x){
	int vi=s[i].calc(x),vj=s[j].calc(x);
	if(abs(vi-vj)>eps)return ((vi<vj)?i:j);
	return min(i,j);
}
struct segtree{
	#define ls p<<1
	#define rs p<<1|1
	#define lson l,mid,ls
	#define rson mid+1,r,rs
	struct Node{
		int flag,id;
		Node():flag(0),id(0){}
	}c[800015];
	void build(int l,int r,int p){
		c[p].flag=0,c[p].id=0;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(lson),build(rson);
	}
	void update(int l,int r,int p,int id){
		if(c[p].flag==0){c[p].flag=1;c[p].id=id;return;}
		int& ID=c[p].id;
		if(l==r){
			if(s[ID].calc(l)>s[id].calc(l))ID=id;
			return;
		}
		int l1=s[ID].calc(l),r1=s[ID].calc(r);
		int l2=s[id].calc(l),r2=s[id].calc(r);
		if(l1<=l2&&r1<=r2)return;
		if(l1>l2&&r1>r2){ID=id;return;}
		int mid=(l+r)>>1;db pos=cross(ID,id);
		if(pos<=mid){
			if(l1<l2)swap(ID,id);
			update(lson,id);
		}
		else{
			if(r1<r2)swap(ID,id);
			update(rson,id);
		}
	}
	void insert(int l,int r,int p,int L,int R,int id){
		if(L<=l&&r<=R){
			update(l,r,p,id);
			return;
		}
		int mid=(l+r)>>1;
		if(L<=mid)insert(lson,L,R,id);
		if(R>mid)insert(rson,L,R,id); 
	}
	int query(int l,int r,int p,int x){
		if(l==r)return c[p].id;
		int mid=(l+r)>>1,id;int ID=c[p].id;
		if(x<=mid)id=query(lson,x);
		else id=query(rson,x);
		return chmin(ID,id,x);
	}
	#undef ls
	#undef rs
	#undef lson
	#undef rson
}Tr;
int ask(int l,int r,int x){
	int res=inf;
	for(int i=l;i<=r;i++)res=min(res,s[i].k*x+s[i].b);
	return res;
}
int bel[100005],bl[505],br[505];
struct Que{
	int l,r,id,ql,qr;
}q[100005];
int cmp(Que x,Que y){
	if(bel[x.ql]^bel[y.ql])return bel[x.ql]<bel[y.ql];
	return x.r<y.r;
}
int a[100005],suf[100005],ans[100005];
signed main(){
	int n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	suf[n+1]=0;
	for(int i=n;i>=1;i--){
		suf[i]=suf[i+1]+a[i];
	}
	s[0]=(seg){0,inf};
	for(int i=1;i<=n;i++){
		s[i]=(seg){a[i],i*a[i]+suf[i+1]};
	}
	int siz=(int)sqrt(n*(int)log2(n)),num=(n+siz-1)/siz;
	for(int i=1;i<=n;i++){
		bel[i]=(i-1)/siz+1;
	}
	for(int i=1;i<=num;i++){
		bl[i]=(i-1)*siz+1,br[i]=i*siz;
	}
	br[num]=n;
	int m=read();
	for(int i=1,l,r;i<=m;i++){
		l=read(),r=read();
		q[i]=(Que){l,r,i,r-l+1,r};
	}
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;i++){
		if(bel[q[i].ql]==bel[q[i].qr]){
			ans[q[i].id]=ask(q[i].ql,q[i].qr,q[i].l-q[i].r)-suf[q[i].r+1];
		}
	}
	for(int i=1,j=1;i<=num;i++){
		int L=br[i]+1,R=br[i];
		Tr.build(-n,n,1);
		while(j<=m){
			int l=q[j].l,r=q[j].r,ql=q[j].ql,qr=q[j].qr,id=q[j].id;
			if(bel[ql]!=i)break;
			if(bel[qr]==i){j++;continue;}
			while(R<qr)R++,Tr.insert(-n,n,1,-n,n,R);
			ans[id]=min(ask(ql,br[i],l-r),s[Tr.query(-n,n,1,l-r)].calc(l-r))-suf[r+1];
			j++;
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Reunite (赞：1)

# 一
---

十分不错的一道题，首先先证明一个重要结论：如果把最优转移的 $j$ 看成一个数列的话，那么单调不升的 $j$ 一定是先一段递减，最后一段全部保持不变的。

这是本题的关键，考虑反证：如果在数列中间出现了一段不变的 $j$ 值，既然后面还会往前取，那么至少前面能取到的值里存在一个比 $a_j$ 小的值，否则会一直停留在 $j$，矛盾。那么既然前面在多选了几次 $j$ 的情况下，还能取到一个比 $a_j$ 小的值，那最优情况一定是只保留一次 $j$，把更多的步数留给那个更小值。证毕。

把询问记为 $(l,r)$，我们记一直往前选能选到的最靠前的 $j$ 的为 $lmx=l-r$，$s_j$ 为 $a_j$ 的前缀和，枚举最后停在 $j$ 上，则最终答案为：

$$\large \min_{j=lmx}^{r} (l-r+j)a_j+s_r-s_j$$

即为

$$\large \min_{j=lmx}^{r} (l-r)a_j+(ja_j-s_j)+s_r$$

我们发现这前面是一个形如 $kx+b$ 的形式，后面是只和 $r$ 有关的无关量，那这不就是李超线段树模板吗！然后发现，不对劲，这里的询问是诸如保留一段区间的直线，单点查询，李超树虽然可以可持久化，但是不满足区间可减性，因此不能像主席树那样简单解决。

# 二
---

既然不能区间信息相减，不妨大力分块，设块长为 $B$，写一个可持久化李超线段树维护大块编号在 $[L,R]$ 内的所有直线。大块直接对应查询，散块用上面的式子直接算。预处理的复杂度是 $O(\frac{n^2\log_2n}{B})$，小块查询复杂度是 $O(B)$ 级别的，大块查询反而更小，是 $O(\log_2n)$ 的。理论上我们可以调块长做到较优复杂度，大概是 $O(n \sqrt{n\log_2n})$ 的，但是这里卡空间了，为了节省空间，我需要把 $B$ 调到 $700$ 左右，是可以通过的。

# 三
---
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

bool _;
int n,mm,m,bl,tot;
ll s[100005];
int a[100005];
int lf[550];
int rt[550];
int bel[100005];
int root[550][550];
int t[21000005];
int lc[21000005];
int rc[21000005];
struct Line{ll k,b;}lin[100005];
bool __;

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline ll get(ll x,int i){return lin[i].k*x+lin[i].b;}

inline int clone(int u){
	tot++;
	lc[tot]=lc[u],rc[tot]=rc[u],t[tot]=t[u];
	return tot;
}

int insert(int u,int l,int r,int k){
	u=clone(u);
	if(l==r){
		if(get(l,t[u])>get(l,k)) t[u]=k;
		return u;
	}
	int mid=(l+r)>>1;
	if(get(mid,t[u])>get(mid,k)) swap(t[u],k);
	if(get(l,k)<get(l,t[u])) lc[u]=insert(lc[u],l,mid,k);
	else if(get(r,k)<get(r,t[u])) rc[u]=insert(rc[u],mid+1,r,k);
	return u;
}

ll query(int u,int l,int r,int x){
	if(!u) return 1e18;
	int mid=(l+r)>>1;
	ll mn=get(x,t[u]);
	if(x<=mid) mn=min(mn,query(lc[u],l,mid,x));
	else mn=min(mn,query(rc[u],mid+1,r,x));
	return mn;
}

int main(){
	// printf("%d\n",(&_-&__)/1024/1024);
	lin[0]=(Line){0,10000000000000000};
	in(n);
	bl=700;
	for(int i=1;i<=n;i++){
		in(a[i]);
		s[i]=s[i-1]+a[i];
		bel[i]=(i+bl-1)/bl;
		lin[i]=(Line){a[i],1ll*a[i]*i-s[i]};
	}
	mm=bel[n];
	for(int i=1;i<=n;i++) rt[bel[i]]=i;
	for(int i=n;i>=1;i--) lf[bel[i]]=i;
	for(int l=1;l<=mm;l++){
		for(int r=l;r<=mm;r++){
			root[l][r]=root[l][r-1];
			for(int i=lf[r];i<=rt[r];i++) root[l][r]=insert(root[l][r],-n,0,i);
		}
	}
	in(m);
	int l,r,lmx;
	while(m--){
		in(l),in(r);
		lmx=r-l+1;
		if(bel[r]-bel[lmx]<=1){
			ll ans=1e18;
			for(int i=lmx;i<=r;i++) ans=min(ans,1ll*(l-r+i)*a[i]+s[r]-s[i]);
			printf("%lld\n",ans);
			continue;
		}
		ll ans=query(root[bel[lmx]+1][bel[r]-1],-n,0,l-r)+s[r];
		for(int i=lmx;i<=rt[bel[lmx]];i++) ans=min(ans,1ll*(l-r+i)*a[i]+s[r]-s[i]);
		for(int i=lf[bel[r]];i<=r;i++) ans=min(ans,1ll*(l-r+i)*a[i]+s[r]-s[i]);
		printf("%lld\n",ans);
	}

	return 0;
}
```

---

## 作者：Caiest_Oier (赞：1)

## [CF455E](https://www.luogu.com.cn/problem/CF455E)

对这个 $f(i,j)$ 的转移感性理解一下，就是在点 $j$，每次可以不动或向左走一步，把每个时刻所在的点权加起来，最小化这个和。  

有一个很明显的贪心，如果途经 $[k,j]$，则尽可能多在最小值点上停留，不要停留在其他的点。同时又发现，到达预定最小值后，可以直接在这个点不动了。所以说枚举终点 $k$，则价值为 $a_k\times (i-(j-k))+pre_j-pre_k$，即直接赶到终点，在终点一直停留。这里 $k\in[j-i+1,j]$。于是我们就有了一个 $\Theta(n^2)$ 的在线做法。     

考虑拆分贡献的计算式。    

$a_k\times (i-(j-k))+pre_j-pre_k=pre_j+a_k\times(i-j)+(a_k\times k-pre_k)$。于是分成了三段，第一段可以最后直接加，先忽略，第三段只依赖于 $k$，可以计算出对于每个 $k$ 的 $g_k=(a_k\times k-pre_k)$，于是就变成了求 $g_k+a_k\times (i-j)$ 的最小值，其中 $k\in[j-i+1,j]$。如果 $k$ 没有限制，可以斜率优化做。考虑把询问中 $k$ 的区间限制用线段树分治离线下来，对于每一个区间维护凸包，凸包上二分就可以做了，复杂度 $\Theta(n\log^2 n)$。    

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,a[100003],g[100003],pre[100003],ans[100003],que[100003],v[100003],k1,k2,k3,k4,k5,k6,k7,k8,k9;
int lft,rgt,mid;
struct SegmentTree{
	int st;
	int ed;
	vector<int>lst;
}T[2200003];
void add(int now,int l,int r,int v){
	if(T[now].st>r||T[now].ed<l)return;
	if(T[now].st>=l&&T[now].ed<=r){
		T[now].lst.emplace_back(v);
		return;
	}
	add(now*2,l,r,v);
	add(now*2+1,l,r,v);
}
void build(int now,int st,int ed){
	T[now].st=st;
	T[now].ed=ed;
	if(st==ed)return;
	build(now*2,st,((st+ed)>>1));
	build(now*2+1,((st+ed)>>1)+1,ed);
	return;
}
int stk[100003][2],tot;
int stk2[100003][2],tot2;
void get_dp(int now){
	if(T[now].st==T[now].ed){
		for(auto i:T[now].lst)ans[i]=min(ans[i],g[T[now].st]-que[i]*a[T[now].st]);
		return;
	} 
	get_dp(now*2);
	get_dp(now*2+1);
	k1=T[now].st;
	k2=T[now*2+1].st;
	k3=T[now*2].ed;
	tot=0;
	while(1){
		while(k1<=k3&&a[k1]<=a[k2])stk[++tot][0]=a[k1],stk[tot][1]=g[k1++];
		if(k1>k3)break;
		while(k2<=T[now].ed&&a[k2]<a[k1])stk[++tot][0]=a[k2],stk[tot][1]=g[k2++];
		if(k2>T[now].ed)break;
	}
	while(k1<=k3)stk[++tot][0]=a[k1],stk[tot][1]=g[k1++];;
	while(k2<=T[now].ed)stk[++tot][0]=a[k2],stk[tot][1]=g[k2++];
	for(int i=T[now].st;i<=T[now].ed;i++)a[i]=stk[i-T[now].st+1][0],g[i]=stk[i-T[now].st+1][1];
	tot2=0;
	for(int i=T[now].st;i<=T[now].ed;i++){
		while(tot2>1&&(g[i]-stk2[tot2][1])*(stk2[tot2][0]-stk2[tot2-1][0])<=(stk2[tot2][1]-stk2[tot2-1][1])*(a[i]-stk2[tot2][0]))tot2--;
		stk2[++tot2][0]=a[i];
		stk2[tot2][1]=g[i];
	}
	for(auto i:T[now].lst){
		lft=1;
		rgt=tot2;
		while(lft<rgt){
			mid=(lft+rgt)>>1;
			if((stk2[mid+1][1]-stk2[mid][1])>=que[i]*(stk2[mid+1][0]-stk2[mid][0]))rgt=mid;
			else lft=mid+1;
		}
		ans[i]=min(ans[i],stk2[lft][1]-que[i]*stk2[lft][0]);
	}
	return;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		pre[i]=pre[i-1]+a[i];
		g[i]=a[i]*i-pre[i];
	}
	scanf("%lld",&q);
	build(1,1,n);
	for(int i=1;i<=q;i++){
		ans[i]=1145141919810000;
		scanf("%lld%lld",&k1,&k2);
		v[i]=pre[k2];
		add(1,max(k2-k1+1,1ll),k2,i);
		que[i]=k2-k1;
	}
	get_dp(1);
	for(int i=1;i<=q;i++)printf("%lld\n",v[i]+ans[i]);
	return 0;
}
```


---

