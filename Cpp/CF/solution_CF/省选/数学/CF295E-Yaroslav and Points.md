# Yaroslav and Points

## 题目描述

Yaroslav has $ n $ points that lie on the $ Ox $ axis. The coordinate of the first point is $ x_{1} $ , the coordinate of the second point is $ x_{2} $ , ..., the coordinate of the $ n $ -th point is — $ x_{n} $ . Now Yaroslav wants to execute $ m $ queries, each of them is of one of the two following types:

1. Move the $ p_{j} $ -th point from position $ x_{pj} $ to position $ x_{pj}+d_{j} $ . At that, it is guaranteed that after executing such query all coordinates of the points will be distinct.
2. Count the sum of distances between all pairs of points that lie on the segment $ [l_{j},r_{j}] $ $ (l_{j}<=r_{j}) $ . In other words, you should count the sum of: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF295E/38769b41287eaecf62f3c386e08a6ca65538ebf0.png).

Help Yaroslav.

## 样例 #1

### 输入

```
8
36 50 28 -75 40 -60 -95 -48
20
2 -61 29
1 5 -53
1 1 429
1 5 130
2 -101 -71
2 -69 53
1 1 404
1 5 518
2 -101 53
2 50 872
1 1 -207
2 -99 -40
1 7 -389
1 6 -171
1 2 464
1 7 -707
1 1 -730
1 1 560
2 635 644
1 7 -677
```

### 输出

```
176
20
406
1046
1638
156
0
```

# 题解

## 作者：eb0ycn (赞：4)

## 题意

翻译很清楚了，但是有个小锅。一句话就是查询一段区间内的所有点对距离之和，支持单点修改。

## 思路

如果我们知道了两个区间的一些信息，如何合并呢？

设左边区间的点集为 $S$，右边点集为 $T$，则两个区间合并以后对答案的贡献为：

$$\begin{aligned} &\sum_{i \in T} \sum_{j \in S} x_i-x_j \\ =&\sum_{i \in T} |S| \times x_i -(\sum_{j \in S}x_j) \\ =& |S| \times (\sum_{i \in T}x_i) - |T| \times (\sum_{j \in S}x_j) \end{aligned}$$

容易发现，只要维护每个**区间的点数**、**点的坐标之和**、**区间本身的答案**即可，一次合并的时间复杂度是 $O(1)$ 的。

既然如此，就可以上线段树了。因为值域很大，所以要动态开点，同时每个坐标要加上一个偏移量变成正数。

但这个值域就很幽默了。极限情况下，初始坐标是 $10^9$，以后每次修改都往右边移动 $1000$，坐标就是 $1.1 \times 10^9$，对于负数也同理。所以它的值域应该为 $[-1.1\times 10^9,1.1\times 10^9]$，再加上偏移量就要开 long long 了，所以我被卡了一次空间。

然后我把偏移量改成 $10^9$，它过了……

不清楚啊，大家知道吗？

但是写动态开点线段树非常牵强，我也是为了写而写的。

## 代码


```cpp
#include<cstdio>
using namespace std;
int n,m,ls[3200000],rs[3200000],cnt,rt,op,aa,bb,l[3200000],r[3200000],x[100001];
struct node{
	long long cnt,sum,ans;
	inline node operator+(const node&cwx)const{return{cnt+cwx.cnt,sum+cwx.sum,ans+cwx.ans+cnt*cwx.sum-sum*cwx.cnt};}
	//合并区间。
}t[3200000];
//线段树要开3200000，因为m*log(V)。
void update(int&rt,int L,int R,int pos,int val){
	if(!rt)rt=++cnt,l[rt]=L,r[rt]=R;
	if(L==R){t[rt].cnt+=val,t[rt].sum+=pos*val;return;}
	int mid=0ll+L+R>>1;
	if(mid<pos)update(rs[rt],mid+1,R,pos,val);
	else update(ls[rt],L,mid,pos,val);
	t[rt]=t[ls[rt]]+t[rs[rt]];
}
node query(int rt,int ql,int qr){
	if(ql<=l[rt]&&r[rt]<=qr){return t[rt];}
	int mid=0ll+l[rt]+r[rt]>>1;
	node ret={0,0,0};
	if(mid>=ql&&ls[rt])ret=query(ls[rt],ql,qr);
	if(mid<qr&&rs[rt])ret=ret+query(rs[rt],ql,qr);
	return ret;
}//查询的时候就不用开点了。
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",x+i),update(rt,1,2000000001,x[i]+1000000001,1);
	scanf("%d",&m);
	while(m--){
		scanf("%d%d%d",&op,&aa,&bb);
		if(op==1)update(rt,1,2000000001,x[aa]+1000000001,-1),update(rt,1,2000000001,1000000001+(x[aa]+=bb),1);
		else printf("%I64d\n",query(1,aa+1000000001,bb+1000000001).ans);
	}
	return 0;
}
```

---

## 作者：forest114514 (赞：4)

### CF295E Yaroslav and Points

一眼平衡树，毕竟求这个题肯定要让序列先有序

对于一个子树，考虑怎么算它的贡献：

记 $siz_u$ 为子树 $u$ 的大小，$sum_u$ 为子树内点值 $val$ 的和，$ans_u$ 为子树的答案值，$ls_u,rs_u$ 分别为 $u$ 的左右儿子。

所以：
$$
ans_u=ans_{ls_u}+ans_{rs_u}+(siz_{ls_u}+1)\times sum_{rs_u}-(siz_{rs_u}+1)\times sum_{ls_u}+(siz_{ls_u}-siz_{rs_u})\times val_u
$$
直接在 pushup 时更新即可。

查询 $l,r$ 时直接按值域分裂（我写的 fhq），单点修改直接记录每个点的点值一起更新

（其实还可以离线用值域线段树，~~但是在线的做法多好啊~~）

CODE：

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
#define re register
#define il inline
#define gc() getchar()
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define repp(i,a,b) for(re int i=a;i<b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define tep(i,x) for(re int i=head[x];~i;i=ne[i])
#define ls(x) tr[x].son[0]
#define rs(x) tr[x].son[1]
#define eps (1e-9)
#define inf 0x3f3f3f3f
#define INF 1e18+100
#define pii pair<int,int>
#define mp(i,j) make_pair(i,j)
#define pb push_back
#define fi first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
template<typename T> inline void read(T &x){
	bool f=1;x=0;char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	x=f?x:-x;
}
template<typename T> inline void write(T x){
	if(x<0) putchar('-'),x=-x;
   	if(x>9) write(x/10);
   	putchar(('0'+x%10));
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
template<typename T> inline void write(T x,char c){write(x),putchar(c);}
const int N=1e5+100;
int n,q,tot,rt,a[N];
struct fhq{
	int son[2],rd;
	LL sum,ans,val,siz;
}tr[N<<1];
void pushup(int x){
	tr[x].siz=tr[ls(x)].siz+tr[rs(x)].siz+1;
	tr[x].sum=tr[ls(x)].sum+tr[rs(x)].sum+tr[x].val;
	tr[x].ans=tr[ls(x)].ans+tr[rs(x)].ans+(tr[ls(x)].siz+1)*tr[rs(x)].sum-(tr[rs(x)].siz+1)*tr[ls(x)].sum+(tr[ls(x)].siz-tr[rs(x)].siz)*tr[x].val;
}
void split(int now,int &x,int &y,int k){
	if(!now) {
		x=y=0;return;
	}
	if(tr[now].val<=k){
		x=now;
		split(rs(now),rs(now),y,k);
	}
	else{
		y=now;
		split(ls(now),x,ls(now),k);
	}
	pushup(now);
}
int merge(int x,int y){
	if(!x||!y) return x+y;
	if(tr[x].rd<tr[y].rd){
		rs(x)=merge(rs(x),y);
		pushup(x);
		return x;
	}
	else{
		ls(y)=merge(x,ls(y));
		pushup(y);
		return y;
	}
}
int init(int x){
	tr[++tot].siz=1,tr[tot].val=tr[tot].sum=x,tr[tot].rd=rand(),tr[tot].ans=0;
	return tot;
}
signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n);	
	int x,y,z,l,r,opt;
	rep(i,1,n){
		read(a[i]);
		split(rt,x,y,a[i]);
		rt=merge(merge(x,init(a[i])),y);
	}
	read(q);
	while(q--){
		read(opt,l,r);
		if(opt==2){
			split(rt,x,z,r);
			split(x,x,y,l-1);
			write(tr[y].ans,'\n');
			rt=merge(merge(x,y),z);
		}else{
			split(rt,x,z,a[l]);
			split(x,x,y,a[l]-1);
			rt=merge(x,z);
			a[l]+=r;
			split(rt,x,y,a[l]);
			rt=merge(merge(x,init(a[l])),y);
		}
	}
	return 0;
}
```



---

## 作者：Yuno (赞：2)

因为这道题只有单点修改操作，所以如果区间信息可以合并，那么这题就做完了。

考虑已知 $[l,mid]$ 和 $[mid+1,r]$ 区间各自的答案，如何知道 $[l,r]$ 的答案

发现可以把答案分为三部分：

- 在 $[l,mid]$ 内的点对
- 在 $[mid+1,r]$ 内的点对
- 一个点在 $[l,mid]$，另一个在 $[mid+1,r]$ 的点对

第一种和第二种，显然是一个子问题，是已知的。

对于第三种，每一个 $[l,mid]$ 中的点都会与 $[mid+1,r]$ 中的点一一匹配，产生贡献

易知每个 $[l,mid]$ 中的点都会被计算 $r-mid$ 次，

设 $pos_i$ 表示每个点的位置， $sz_r=r-mid,s_l=\sum_{i=l}^{mid} pos_i$

则 $[l,mid]$ 的贡献为 $-sz_r\times s_l$（因为是被减去）

$[mid+1,r]$ 的贡献同理，为 $sz_l\times s_r$

然后用线段树维护即可，由于值域较大，要动态开点。

Code:
```cpp
#include <bits/stdc++.h>
inline int read( ) {
	int x = 0, f = 1;
	char c = getchar( );
	while ( !isdigit( c ) ) { if ( c == '-' ) f = -1; c = getchar( ); }
	while ( isdigit( c ) ) x = ( x << 3 ) + ( x << 1 ) + c - 48, c = getchar( );
	return x * f;
}

const int N = 1e5 + 7, M = 5e6 + 7;

int n, m, root, cnt, ls[ M ], rs[ M ];
long long pos[ N ];
struct node {
	int sz;
	long long s1, s2;
}tr[ M ];

void pushup( int rt ) {
	tr[ rt ].sz = tr[ ls[ rt ] ].sz + tr[ rs[ rt ] ].sz;
	tr[ rt ].s1 = tr[ ls[ rt ] ].s1 + tr[ rs[ rt ] ].s1;
	tr[ rt ].s2 = tr[ ls[ rt ] ].s2 + tr[ rs[ rt ] ].s2 + tr[ rs[ rt ] ].s1 * tr[ ls[ rt ] ].sz - tr[ ls[ rt ] ].s1 * tr[ rs[ rt ] ].sz;
}

void mdf( int &rt, int l, int r, int loc, int val, bool flag ) {
	if ( !rt ) rt = ++ cnt;
	if ( l == r ) {
		if ( flag == 0 ) tr[ rt ].s1 -= val;
		else tr[ rt ].s1 += val;
		if ( flag == 0 ) tr[ rt ].sz --;
		else tr[ rt ].sz ++;
		return;
	}
	int mid = ( 1ll * l + r ) >> 1;
	if ( loc <= mid ) mdf( ls[ rt ], l, mid, loc, val, flag );
	else mdf( rs[ rt ], mid + 1, r, loc, val, flag );
	pushup( rt );
}

node qry( int rt, int l, int r, int L, int R ) {
	if ( !rt ) return ( node ){ 0, 0, 0 };
	if ( L <= l && r <= R ) return tr[ rt ];
	int mid = ( 1ll * l + r ) >> 1;
	node lret = ( node ){ 0, 0, 0 }, rret = ( node ){ 0, 0, 0 };
	if ( L <= mid ) lret = qry( ls[ rt ], l, mid, L, R );
	if ( R > mid ) rret = qry( rs[ rt ], mid + 1, r, L, R );
	node ret;
	ret.sz = lret.sz + rret.sz;
	ret.s1 = lret.s1 + rret.s1;
	ret.s2 = lret.s2 + rret.s2 + rret.s1 * lret.sz - lret.s1 * rret.sz;
	return ret;
}

signed main( ) {
	n = read( );
	for ( int i = 1; i <= n; ++ i ) pos[ i ] = read( ), mdf( root, 1, 2e9 + 1, pos[ i ] + 1e9 + 1, pos[ i ], 1 );
	m = read( );
	while ( m --> 0 ) {
		int op = read( ), l = read( ), r = read( );
		if ( op == 2 ) printf( "%I64d\n", qry( root, 1, 2e9 + 1, l + 1e9 + 1, r + 1e9 + 1 ).s2 );
		else {
			if ( abs( pos[ l ] ) <= 1e9 )
			mdf( root, 1, 2e9 + 1, pos[ l ] + 1e9 + 1, pos[ l ], 0 );
			pos[ l ] += r;
			if ( abs( pos[ l ] ) <= 1e9 )
			mdf( root, 1, 2e9 + 1, pos[ l ] + 1e9 + 1, pos[ l ], 1 );
		}
	}
	return 0;
}
```


---

## 作者：xcxcli (赞：2)

看到增加坐标，以及求和过程中$l\le x_p\le x_q\le r$，可以想到用平衡树维护坐标。

设$v_i$为$i$节点的坐标，$sz_i$为$i$节点的子树大小，$s_i$为$i$节点字数的坐标和，$w_i$为子树区间的答案。

则$w_i=w_{ls}+w_{rs}+$左右子树间的答案$+$右子树和根的答案$+$左子树和根的答案。

即$w_i=(w_{ls}+w_{rs})+(sz_{ls}*s_{rs}+sz_{rs}*s_{ls})+(s_{rs}-sz_{rs}*v_i)+(sz_{ls}*v_i-s_{ls})$

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ll long long
int rd(){
	int k=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
const int N=200001;
int pn,n,m,o,x,y,z,b,c,rt,rnd[N],v[N],sz[N],ch[N][2],a[N];ll s[N],w[N];
#define ls ch[t][0]
#define rs ch[t][1]
void Up(int t){
	sz[t]=sz[ls]+sz[rs]+1,s[t]=s[ls]+s[rs]+v[t];
	w[t]=w[ls]+w[rs]+sz[ls]*s[rs]-sz[rs]*s[ls]+s[rs]-sz[rs]*v[t]+sz[ls]*v[t]-s[ls];
}
void Split(int t,int&a,int&b,int w){
	if(!t){a=b=0;return;}
	if(w>=v[t])a=t,Split(rs,rs,b,w);
	else b=t,Split(ls,a,ls,w);
	Up(t);
}
int Merge(int a,int b){
	if(!a||!b)return a|b;
	if(rnd[a]<rnd[b]){ch[a][1]=Merge(ch[a][1],b),Up(a);return a;}
	ch[b][0]=Merge(a,ch[b][0]),Up(b);return b;
}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	pn=n=rd();
	for(int i=1;i<=n;++i)Split(rt,x,y,s[i]=v[i]=a[i]=rd()),rnd[i]=rand(),sz[i]=1,rt=Merge(Merge(x,i),y);
	m=rd();
	while(m--){
		o=rd(),b=rd(),c=rd();
		if(o==1){
			Split(rt,x,y,a[b]-1),Split(y,y,z,a[b]),rt=Merge(Merge(x,Merge(ch[y][0],ch[y][1])),z);
			rnd[++pn]=rand(),v[pn]=s[pn]=c+a[b],sz[pn]=1,Split(rt,x,y,a[b]=v[pn]),rt=Merge(Merge(x,pn),y);
		}
		else Split(rt,x,y,b-1),Split(y,y,z,c),printf("%lld\n",w[y]),rt=Merge(Merge(x,y),z);
	}
	return 0;
}
```

---

## 作者：include13_fAKe (赞：0)

首先开一棵动态开点线段树，值域为 $[-1.1\times10^9,1.1\times 10^9]$。考虑将答案维护拆成三个部分：

- 两点均在左区间的。
- 两点均在右区间的。
- 一点在左区间、一点在右区间的。

假如前两种已讨论完，用线段树解决区间合并的思路搞定第三种。需要维护线段树各块的点数、点坐标之和，然后推出线段树块内点到块两侧的距离和。这里的组合思路类似于 [NOI2023 贸易](https://www.luogu.com.cn/problem/P9481)。

一个细节就是在查询时可能要对线段树开点。

[代码](https://codeforces.com/contest/295/submission/325031007)

---

## 作者：candy0014 (赞：0)

> 提供一种分块做法，跑得飞快。

>[洛谷传送门](https://www.luogu.com.cn/problem/CF295E)
>
>[CF 传送门](https://codeforces.com/problemset/problem/295/E)

# 题意

维护数轴上的 $n$ 个点，支持单点移动，以及查询一个值域区间内的所有点对距离和。

保证移动距离不超过 $1000$，且任意时刻任意两点不重合。

# 思路

对于查询，假设所有点已经排好序，则可以将值域区间转化成下标区间，显然可以拆贡献。

设值域区间转化成的下标区间为 $[l,r]$，则 $\sum\limits_{i=l}^{r} x_i\times (i-l) - \sum\limits_{i=l}^{r} x_i\times (r-i)$ 即为所求。

上面的式子还可以继续拆，$\sum\limits_{i=l}^{r} x_i\times (i-l) - \sum\limits_{i=l}^{r} x_i\times (r-i)=2\sum\limits_{i=l}^{r} x_i\times i - (l+r)\sum\limits_{i=l}^{r} x_i$，这启示我们可以使用数据结构维护 $x_i\times i$ 和 $x_i$ 的区间和。

这时候题意中的两点保证就有用了，他保证了在一次修改中，$x$ 数组被打乱的范围不会太大，只有 $1000$。我们完全可以对这个被打乱的区间内的所有数进行暴力修改。

统计一下修改次数和查询次数，发现共有 $10^5\times 1000$ 组单点修改，以及 $10^5$ 组区间查询，则 $O(1) - O(\sqrt{n})$ 的分块是一个很好的选择。

于是这题就做完了，代码非常好写。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int len=256;
int th[100005],st[100005],ed[100005];
struct node{ // O(1)-O(sqrt(n)) 的单点改区间和板子
	ll a[100005],sum[100005];
	void change(int x,ll k){
		k-=a[x],a[x]+=k,sum[th[x]]+=k;
	}
	ll query(int l,int r){
		ll ans=0;
		if(th[l]==th[r]){
			for(int i=l;i<=r;i++) ans+=a[i];
			return ans;
		}
		for(int i=l;i<=ed[th[l]];i++) ans+=a[i];
		for(int i=st[th[r]];i<=r;i++) ans+=a[i];
		for(int i=th[l]+1;i<th[r];i++) ans+=sum[i];
		return ans;
	}
}s1,s2; // s1 存 x[i] 的区间和，s2 存 x[i]*i 的区间和
int n,ca,a[100005],c[100005];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		th[i]=(i-1)/len+1,ed[th[i]]=i;
		if(th[i]!=th[i-1]) st[th[i]]=i;
	}
	for(int i=1;i<=n;i++) cin>>a[i],c[i]=a[i]; // 由于输入原因要存输入顺序的 c 数组
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) s1.change(i,a[i]),s2.change(i,1ll*a[i]*i); // 预处理
	cin>>ca;
	while(ca--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1){
			int id=lower_bound(a+1,a+n+1,c[x])-a; // 原数组下标转 x 数组下标
			c[x]+=y,x=id,a[x]+=y;
			int l=x,r=x;
			if(y>0) while(r<n&&a[r]>a[r+1]) swap(a[r],a[r+1]),r++; // 求出发生改变的区间
			else while(l>1&&a[l]<a[l-1]) swap(a[l],a[l-1]),l--;
			for(int i=l;i<=r;i++) s1.change(i,a[i]),s2.change(i,1ll*a[i]*i); // 暴力修改区间
		}
		else{
			x=lower_bound(a+1,a+n+1,x)-a,y=upper_bound(a+1,a+n+1,y)-a-1; // 值域区间转下标区间
			if(x>y){cout<<"0\n";continue;}
			ll ans1=s1.query(x,y),ans2=s2.query(x,y); // ans1 是 x[i] 的区间和，ans2 是 x[i]*i 的区间和
			cout<<2*ans2-(x+y)*ans1<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

### 题意
数轴上支持关键点平移，查询闭区间内所有关键点对坐标差之和。
### 分析
大家好我很喜欢暴力分块，所以我使用 $O(n\sqrt n)$ 的算法用时 `1530ms` 通过了此题。

考虑把所有修改扫一遍把所有有效位置拎出来离散化，把值域缩到 $O(n)$ 级别。

然后对一个闭区间求解，把坐标差的柿子拆一下，考虑一个点的正贡献和负贡献。两个贡献比较相似就只说正贡献了，显然是闭区间内这个点左边的点的个数乘上这个点的坐标。

然后直接对数轴分块，头尾的散块暴力扫一遍，中间的整块考虑如何处理。你发现每次修改的时候只有 $O(1)$ 个块被修改，所以 $O(\sqrt n)$ 暴力重构块内关键点个数，关键点坐标和以及贡献之和，查询的时候可以直接累加块内贡献，同时维护一个当前扫到的前缀有几个关键点，配合块内关键点坐标和转移，具体柿子比较好写可以见代码。

然后就做完了。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
mt19937 rnd(time(NULL));
const int maxn=2e5+5;
const int maxm=450;
int n,m,B;
int a[maxn],b[maxn];
int t[maxn],N;
struct opt{
	opt(int O=0,int X=0,int Y=0){op=O,x=X,y=Y;}
	int op,x,y;
}z[maxn];
int col[maxn],L[maxm],R[maxm];
int c[maxn],pre[maxm],suf[maxm],cnt[maxm],sm[maxm];
void rebuild(int x){
	cnt[x]=sm[x]=pre[x]=suf[x]=0;
	for(int i=L[x];i<=R[x];i++){
		if(!c[i]) continue;
		pre[x]+=cnt[x]*t[i];
		cnt[x]++,sm[x]+=t[i];
	}
	for(int i=R[x],k=0;i>=L[x];i--){
		if(!c[i]) continue;
		suf[x]+=k*t[i];
		k++;
	}
}
int calcpre(int l,int r){
	int res=0;
	if(col[l]==col[r]){
		for(int i=l,k=0;i<=r;i++){
			if(!c[i]) continue;
			res+=k*t[i];
			k++;
		}
		return res;
	}
	int k=0;
	for(int i=l;i<=R[col[l]];i++){
		if(!c[i]) continue;
		res+=k*t[i];
		k++;
	}
	for(int i=col[l]+1;i<col[r];i++){
		res+=k*sm[i]+pre[i];
		k+=cnt[i];
	}
	for(int i=L[col[r]];i<=r;i++){
		if(!c[i]) continue;
		res+=k*t[i];
		k++;
	}
	return res;
}
int calcsuf(int l,int r){
	int res=0;
	if(col[l]==col[r]){
		for(int i=r,k=0;i>=l;i--){
			if(!c[i]) continue;
			res+=k*t[i];
			k++;
		}
		return res;
	}
	int k=0;
	for(int i=r;i>=L[col[r]];i--){
		if(!c[i]) continue;
		res+=k*t[i];
		k++;
	}
	for(int i=col[r]-1;i>col[l];i--){
		res+=k*sm[i]+suf[i];
		k+=cnt[i];
	}
	for(int i=R[col[l]];i>=l;i--){
		if(!c[i]) continue;
		res+=k*t[i];
		k++;
	}
	return res;
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read();t[++N]=-inf,t[++N]=inf;
	for(int i=1;i<=n;i++) t[++N]=b[i]=a[i]=read();
	m=read();
	for(int i=1;i<=m;i++){
		int op=read();
		if(op&1){
			int x=read(),k=read();
			t[++N]=b[x]+k;
			z[i]=opt(op,b[x],b[x]+k);
			b[x]+=k;
		}else{
			int l=read(),r=read();
			z[i]=opt(op,l,r);
		}
	}
	sort(t+1,t+N+1),N=unique(t+1,t+N+1)-t-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(t+1,t+N+1,a[i])-t;
		c[a[i]]++;
	}
	B=sqrt(N);
	for(int i=1;i<=N;i++){
		col[i]=(i-1)/B+1;
		if(!L[col[i]]) L[col[i]]=i;
		R[col[i]]=i;
	}
	for(int i=1;i<=col[N];i++) rebuild(i);
	for(int i=1;i<=m;i++){
		if(z[i].op&1){
			int x=lower_bound(t+1,t+N+1,z[i].x)-t;
			int y=lower_bound(t+1,t+N+1,z[i].y)-t;
			c[x]--;rebuild(col[x]);
			c[y]++;rebuild(col[y]);
		}else{
			int l=lower_bound(t+1,t+N+1,z[i].x)-t;
			int r=upper_bound(t+1,t+N+1,z[i].y)-t-1;
			if(l>r) puts("0");
			else cout<<calcpre(l,r)-calcsuf(l,r)<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：Luzhuoyuan (赞：0)

### 题意

给定数轴上 $n$ 个点 $x_i$，有 $m$ 次两种操作：

- `1 p d`：令点 $p$ 的位置变为 $x_p+d$；
- `2 l r`：求 $\displaystyle\sum_{l\le x_i<x_j\le r}(x_j-x_i)$。

保证任意时刻 $n$ 个点的位置互不相同。

- $1\le n,m\le 10^5$；
- $1\le p\le n$；
- $|d|\le 1000$；
- $|x_i|,|l|,|r|\le 10^9$。

### 思路

首先我们考虑询问操作的性质。如果对每个 $x_i$ 计算贡献，我们可以发现将 $[l,r]$ 内的点按 $x_i$ 排序之后，每个点的贡献是一个公差为 $2$ 的等差数列，并且所有贡献值加和为零。也就是说，对于排序好的 $x_{l'},x_{l'+1},\dots,x_{r'}$，$x_i$ 的贡献为 $2i-(l'+r')$。这样我们只需要知道 $[l,r]$ 内的 $2ix_i$ 的和以及 $x_i$ 的和，就可以计算出询问的答案：$\displaystyle ans=\sum_{i=l'}^{r'} 2ix_i-(l'+r')\sum_{i=l'}^{r'} x_i$。其中 $l',r'$ 分别表示 $x$ 排序后最小的 $x_{l'}\ge l$ 和最大的 $x_{r'}\le r$。

考虑使用线段树维护 $2ix_i,x_i$ 的值。开始时先将 $x$ 排序并把对应的值塞进线段树，同时维护每个 $x_i$ 对应的 $i$ 值。对于修改操作，先删除 $x_p$，若 $d>0$，则将 $(x_p,x_p+d)$ 这一段对应的 $i$ 减小 $1$（同时维护 $2ix_i$），否则将 $(x_p+d,x_p)$ 的 $i$ 增加 $1$，最后再插入新的 $x_p$。对于询问操作，直接像上面所说计算答案即可。

由于值域较大，代码中为了实现方便，将值域离散化了，并另开了一个树状数组维护 $i$ 的值。复杂度 $O((m+n)\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define SZ(x) (int)((x).size())
using namespace std;
const int N=3e5+5;
int n,m,a[N],b[N],d[N],dn;
struct node{int op,x,y;}q[N];
struct Tree{// 线段树
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	int t[N<<2],s[N<<2],lz[N<<2];
	inline void tg(int rt,int v){lz[rt]+=v,t[rt]+=v*s[rt];}
	inline void psu(int rt){t[rt]=t[ls]+t[rs],s[rt]=s[ls]+s[rs];}
	inline void psd(int rt){if(lz[rt])tg(ls,lz[rt]),tg(rs,lz[rt]),lz[rt]=0;}
	void ins(int x,int v,int rt=1,int l=1,int r=dn){
		if(l==r){t[rt]=d[x]*v,s[rt]=d[x];return;}
		int mid=(l+r)>>1;psd(rt);
		x<=mid?ins(x,v,ls,l,mid):ins(x,v,rs,mid+1,r);
		psu(rt);
	}// 加入一个点
	void del(int x,int rt=1,int l=1,int r=dn){
		if(l==r){t[rt]=s[rt]=0;return;}
		int mid=(l+r)>>1;psd(rt);
		x<=mid?del(x,ls,l,mid):del(x,rs,mid+1,r);
		psu(rt);
	}// 删除一个点
	void upd(int L,int R,int v,int rt=1,int l=1,int r=dn){
		if(l>=L&&r<=R){tg(rt,v);return;}
		int mid=(l+r)>>1;psd(rt);
		if(L<=mid)upd(L,R,v,ls,l,mid);
		if(R>mid)upd(L,R,v,rs,mid+1,r);
		psu(rt);
	}// 区间修改 2ix_i 的值
	int qry(int L,int R,int c,int rt=1,int l=1,int r=dn){
		if(l>=L&&r<=R)return t[rt]-c*s[rt];
		int mid=(l+r)>>1,re=0;psd(rt);
		if(L<=mid)re=qry(L,R,c,ls,l,mid);
		if(R>mid)re+=qry(L,R,c,rs,mid+1,r);
		return re;
	}// 查询
}T;
struct BIT{
	int c[N];
	inline void add(int p,int x){for(;p<=dn;p+=p&-p)c[p]+=x;}
	inline int qry(int p){int s=0;for(;p;p&=p-1)s+=c[p];return s;}
}B;// 树状数组
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n;for(int i=1;i<=n;i++)cin>>a[i],d[++dn]=b[i]=a[i];
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>q[i].op>>q[i].x>>q[i].y;
		if(q[i].op==1)d[++dn]=(b[q[i].x]+=q[i].y);
		else d[++dn]=q[i].x,d[++dn]=q[i].y;
	}
	sort(d+1,d+dn+1),dn=unique(d+1,d+dn+1)-d-1;
	for(int i=1;i<=n;i++)b[i]=a[i]=lower_bound(d+1,d+dn+1,a[i])-d;
	sort(b+1,b+n+1);for(int i=1;i<=n;i++)B.add(b[i],1),T.ins(b[i],i*2);
	for(int i=1;i<=m;i++){
		int op=q[i].op,x=q[i].x,y=q[i].y;
		if(op==1){
			T.del(a[x]),B.add(a[x],-1);
			int t=lower_bound(d+1,d+dn+1,d[a[x]]+y)-d;
			t>a[x]?T.upd(a[x],t,-2):T.upd(t,a[x],2);
			B.add(a[x]=t,1),T.ins(t,B.qry(t)*2);
		}else{
			x=lower_bound(d+1,d+dn+1,x)-d,y=lower_bound(d+1,d+dn+1,y)-d;
			cout<<T.qry(x,y,B.qry(x-1)+1+B.qry(y))<<'\n';
		}
	}
	return 0;
}
```

（逃

---

## 作者：Little_Fox_Fairy (赞：0)

### 题意

题意挺简洁的，就是要注意洛谷的翻译写错了。

### Solution

我们令满足条件二的 $n$ 个数 $x$ 从小到大排序后为 $ x_1,x_2,x_3,\dots x_n $。

这里按洛谷上的题面来，最后答案取反即可。

把答案的贡献拆开：$(x_1 - x_1) + (x_1-x_2) + (x_1-x_3) + \dots + (x_n - x_n)$。

整理一下就得到：$ (n-1) x_1 + (n-3)x_2 + (n-5)x_3 + \dots + (1-n) x_n $。

注意到这是个等差数列，你可以把它写成和式：$ \sum\limits_{i=1}^n x_i(n-2i+1) $。

我们用权值线段树来维护这个东西。

那我们来看一下 $ pushup $ 怎么写。

左边有一段长度为 $ n_1 $ 的数，右边有一段长度为 $ n_2 $ 的数，且左边的数均小于右边的数。

那么对于左边那些的贡献，在和式中只有 $ n $ 的值改变了，增加了 $ n_2 $，所以左边新增加的贡献就为 $ sum_1 \times n_2 $。

右边同理，在和式中有 $ n $ 和 $ i $ 的值改变了，增加了 $ n_1 $，所以右边新增加的贡献就为 $ sum_2 \times n_1 - 2\times sum_2 \times n_1 = -sum_2 \times n_1 $。

最终的答案就是 $ val(x) = val(ls) + val(rs) + sum_1 \times n_2 -sum_2 \times n_1$。

然后就做完了，记得离散化。

### Code
```cpp
//Sa~ka~na~
#include<bits/stdc++.h>
#define int long long 
#define pii pair<int,int>
#define pb push_back 
#define eb emplace_back
#define rep(i,a,b) for (int i=(a);i<=(b);i++) 
#define Rep(i,a,b) for (int i=(a);i>=(b);i--)
#define grep(i,a,b) for (auto i : a[b]) 
using namespace std;
const int N=5e5+10;

int n,m,e[N],b[N],len,a[N];
struct Ques {
    int op,x,y;
}q[N];
struct node {
    int l,r,val,cnt,sum;//val:答案,cnt:[l,r]个数,sum:[l,r]和
    #define ls u<<1
    #define rs u<<1|1
    #define val(u) (t[u].val)
    #define cnt(u) (t[u].cnt)
    #define sum(u) (t[u].sum)
}t[N<<2];
inline void push_up(int u) {
    int cnt1=cnt(ls),cnt2=cnt(rs);
    int sum1=sum(ls),sum2=sum(rs);
    sum(u)=sum1+sum2,cnt(u)=cnt1+cnt2;
    val(u)=val(ls)+val(rs)+cnt2*sum1-cnt1*sum2;
    return ;
}
/*
val[u] = \sum[1~len] x_i * (len-2*i+1) 
val[u] = val[ls] + val[rs] + len2*sum1 - len1*sum2 
*/
inline void build(int u,int l,int r) {
    t[u].l=l,t[u].r=r,val(u)=0,cnt(u)=0,sum(u)=0;;
    if (l==r) return ;
    int mid=l+r>>1;
    build(ls,l,mid),build(rs,mid+1,r);
    return ;
}
inline void modify(int u,int p,int val,int op) {
    if (t[u].l==t[u].r) {
        if (op) cnt(u)=1,sum(u)=val,val(u)=0;
        else cnt(u)=0,sum(u)=0,val(u)=0;
        return ;
    }
    int mid=t[u].l+t[u].r>>1;
    if (p<=mid) modify(ls,p,val,op);
    else modify(rs,p,val,op);
    return push_up(u);
}
inline node query(int u,int l,int r) {
    if (t[u].l>=l and t[u].r<=r) return t[u];
    int mid=t[u].l+t[u].r>>1;
    if (r<=mid) return query(ls,l,r);
    else if (l>mid) return query(rs,l,r);
    else {
        node L=query(ls,l,r),R=query(rs,l,r);
        node res;
        int cnt1=L.cnt,cnt2=R.cnt;
        int sum1=L.sum,sum2=R.sum;
        res.sum=sum1+sum2,res.cnt=cnt1+cnt2;
        res.val=L.val+R.val+cnt2*sum1-cnt1*sum2;
        return res;
    }
}
inline void init() {
    sort(b+1,b+len+1);
    len=unique(b+1,b+len+1)-b-1;
    return ;
}
signed main() {
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
    rep(i,1,n) cin>>e[i],b[++len]=e[i],a[i]=e[i];
    cin>>m;
    rep(i,1,m) {
        cin>>q[i].op>>q[i].x>>q[i].y;
        if (q[i].op==1) a[q[i].x]+=q[i].y,b[++len]=a[q[i].x];
        else b[++len]=q[i].x,b[++len]=q[i].y;
    }
    init();build(1,1,len);
    rep(i,1,n) {
        int pos=lower_bound(b+1,b+len+1,e[i])-b;
        modify(1,pos,e[i],1);
    }
    rep(i,1,m) {
        if (q[i].op==1) {
            int x=lower_bound(b+1,b+len+1,e[q[i].x])-b;
            modify(1,x,0,0);
            e[q[i].x]+=q[i].y;
            x=lower_bound(b+1,b+len+1,e[q[i].x])-b;
            modify(1,x,e[q[i].x],1);
        } else {
            int l=lower_bound(b+1,b+len+1,q[i].x)-b,r=lower_bound(b+1,b+len+1,q[i].y)-b;
            cout<<(-query(1,l,r).val)<<endl;
        }
    }
	return (0-0);
} 
```

---

