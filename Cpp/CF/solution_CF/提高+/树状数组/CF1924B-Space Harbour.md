# Space Harbour

## 题目描述

There are $ n $ points numbered $ 1 $ to $ n $ on a straight line. Initially, there are $ m $ harbours. The $ i $ -th harbour is at point $ X_i $ and has a value $ V_i $ . It is guaranteed that there are harbours at the points $ 1 $ and $ n $ . There is exactly one ship on each of the $ n $ points. The cost of moving a ship from its current location to the next harbour is the product of the value of the nearest harbour to its left and the distance from the nearest harbour to its right. Specifically, if a ship is already at a harbour, the cost of moving it to the next harbour is $ 0 $ .

Additionally, there are $ q $ queries, each of which is either of the following $ 2 $ types:

- $ 1 $ $ x $ $ v $ — Add a harbour at point $ x $ with value $ v $ . It is guaranteed that before adding the harbour, there is no harbour at point $ x $ .
- $ 2 $ $ l $ $ r $ — Print the sum of the cost of moving all ships at points from $ l $ to $ r $ to their next harbours. Note that you just need to calculate the cost of moving the ships but not actually move them.

## 说明/提示

For the first type $ 2 $ query, the cost for ships at positions $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ are $ 3(3 \times 1) $ , $ 0 $ , $ 96(24 \times 4) $ and $ 72(24 \times 3) $ respectively.

For the second type $ 2 $ query, since the ship at position $ 5 $ is already at a harbour, so the cost is $ 0 $ .

For the third type $ 2 $ query, the cost for ships at position $ 7 $ and $ 8 $ are $ 15(15 \times 1) $ and $ 0 $ respectively.

## 样例 #1

### 输入

```
8 3 4
1 3 8
3 24 10
2 2 5
1 5 15
2 5 5
2 7 8```

### 输出

```
171
0
15```

# 题解

## 作者：EuphoricStar (赞：11)

不知道为什么好像大家在这题上花了挺久的。

发现对于一对相邻的港口 $(x_i, x_{i + 1})$，$x \in (x_i, x_{i + 1})$ 的花费是 $y_i (x_{i + 1} - x)$。拆开得 $y_i x_{i + 1} - y_i x$。

考虑用 set 维护所有港口，这样可以知道一个港口左边和右边的港口的坐标和价值。那么前一项 $y_i x_{i + 1}$ 可以线段树区间覆盖，后一项 $-y_i x$ 也可以线段树区间覆盖处理，相当于让一个代表 $[l, r]$ 区间的线段树结点的和变成 $- y_i \frac{(l + r)(r - l + 1)}{2}$。这个标记是可以下传的。

总时间复杂度为 $O((m + q) \log n)$。

[code](https://codeforces.com/problemset/submission/1924/243582923)

---

## 作者：Rain_chr (赞：9)

来一发不一样的，是考场做法，结果赛后五分钟写完，又被卡常，在学长的帮助下才终于卡过去。

每个点的到右边第一个港口的代价是“左边第一个港口的权重”乘以“右边第一个港口的距离”，我们可以尝试直接维护这一信息，那查询操作就是个区间加。

线段树初始化很好操作，随便用一个数据结构维护前面的港口和后面的港口，直接乘起来就好了。

再来看修改操作，设当前插入的港口是 $x$，他左边和右边的港口分别为 $l,r$，权重数组为 $w$，那么他会影响 $[l+1,x-1]$ 中船的距离，$[x+1,r]$ 中船的权重。

1.影响距离，即减去 $(r-x) \times w_l$。

2.影响权重，即乘以 $\frac{w_x}{w_l}$。

显而易见，这就是一个乘加线段树。但是你真这么写，肯定过不了。二操作涉及浮点操作，一定会掉精度。

可以发现最后所有点的点权之和不会大于 $10^5 \times 10^7 \times 10^5 = 10^{17}$，只是中间变量可能会爆。

那这样我们用一个技巧，所有数都对一个 $10^{18}$ 级别的大质数取模，那么这样对最终答案没有影响，中间变量也不会溢出了。

只是常数较大，稍稍卡常即可通过。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define i128 __int128
using namespace std;
const ll mod=1000000000000000003ll;
const int N=3e5+10;
set<int> st;
signed val[N];
inline void Add(ll& x,ll y){x=x+y>=mod?x+y-mod:x+y;}
inline void Pro(ll& x,ll y){x=(i128)x*y%mod;}
struct Segment
{
	ll t[N<<2];
	ll plu[N<<2],pro[N<<2];
	void build(int x,int l,int r)
	{
		pro[x]=1;
		if(l==r) t[x]=1ll*val[*(--st.lower_bound(l))]*(*st.lower_bound(l)-l);
		else
		{
			int mid=(l+r)>>1;
			build(x<<1,l,mid);
			build(x<<1|1,mid+1,r);
			t[x]=t[x<<1]+t[x<<1|1];
		}
	}
	inline void pushdown(int x,int l,int r)
	{
		int mid=(l+r)>>1;
		
		if(pro[x]!=1)
		{
			Pro(pro[x<<1],pro[x]);
			Pro(pro[x<<1|1],pro[x]);
			Pro(t[x<<1],pro[x]);
			Pro(t[x<<1|1],pro[x]);	
		}
		if(pro[x]!=1||plu[x])
		{
			plu[x<<1]=(plu[x]+(__int128) plu[x<<1]*pro[x])%mod;
			plu[x<<1|1]=(plu[x]+(__int128) plu[x<<1|1]*pro[x])%mod;
			Add(t[x<<1],(__int128)(mid-l+1)*plu[x]%mod);
			Add(t[x<<1|1],(__int128)(r-mid)*plu[x]%mod);
		}
		
		pro[x]=1;
		plu[x]=0;
	} 
	void prod(int x,int l,int r,int L,int R,ll k)
	{
		if(L<=l&&r<=R)
		{
			Pro(t[x],k);
			Pro(plu[x],k);
			Pro(pro[x],k);
		}
		else
		{
			pushdown(x,l,r);
			int mid=(l+r)>>1;
			if(L<=mid) prod(x<<1,l,mid,L,R,k);
			if(mid+1<=R) prod(x<<1|1,mid+1,r,L,R,k);
			t[x]=(t[x<<1]+t[x<<1|1])%mod;
		}
	}
	void add(int x,int l,int r,int L,int R,ll k)
	{
		if(L<=l&&r<=R)
		{
			Add(t[x],(__int128)k*(r-l+1)%mod);
			Add(plu[x],k);
		}
		else
		{
			pushdown(x,l,r);
			int mid=(l+r)>>1;
			if(L<=mid) add(x<<1,l,mid,L,R,k);
			if(mid+1<=R) add(x<<1|1,mid+1,r,L,R,k);
			t[x]=(t[x<<1]+t[x<<1|1])%mod;
		}
	}
	ll query(int x,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R) return t[x];
		pushdown(x,l,r);
		ll k=0,mid=(l+r)>>1;
		if(L<=mid) k+=query(x<<1,l,mid,L,R);
		if(mid+1<=R) k+=query(x<<1|1,mid+1,r,L,R);
		return k>=mod?k-mod:k;
	}
}T;
ll ksm(ll a,ll b)
{
	ll ans=1;
	while(b)
	{
		if(b&1) Pro(ans,a);
		Pro(a,a);
		b>>=1;
	}
	return ans;
}
int a[N];
namespace IO {
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)

inline int rd() {
  int x = 0, f = 1;
  char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = -1;
    c = gc();
  }
  while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
  return x * f;
}

char pbuf[1 << 20], *pp = pbuf;

inline void push(const char &c) {
  if (pp - pbuf == 1 << 20) fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
  *pp++ = c;
}

inline void write(ll x) {
  if(x==0)
  {
    push('0');
  	return ;  
  } 
  static int sta[70];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) push(sta[--top] + '0');
}
}  // namespace IO
using namespace IO;
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
//	ios::sync_with_stdio(0);
//	cin.tie(0),cout.tie(0);
	int n=rd(),m=rd(),q=rd();
	for(int i=1;i<=m;i++)
	{
		a[i]=rd();
		st.insert(a[i]);
	}
	for(int i=1;i<=m;i++) val[a[i]]=rd();
	T.build(1,1,n);
	while(q--)
	{
		signed op=rd();
		if(op==1)
		{
			int pos=rd(),v=rd();
			val[pos]=v;
			T.prod(1,1,n,pos,pos,0);
			st.insert(pos);
			int l=*(--st.lower_bound(pos)),r=*st.upper_bound(pos);
			if(l<pos-1) T.add(1,1,n,l+1,pos-1,-1ll*(r-pos)*val[l]+mod);
			if(pos+1<r) T.prod(1,1,n,pos+1,r-1,(__int128) ksm(val[l],mod-2)*v%mod); 
		}
		else
		{
			int l=rd(),r=rd();
			write(T.query(1,1,n,l,r));
			push('\n');
		}
	}
	fwrite(pbuf,1,pp - pbuf, stdout);
}
//Yes
```


---

## 作者：OldDriverTree (赞：9)

手切 E 题祭。

# Solution
看到区间求和，考虑以船的位置为下标建一棵线段树。

对于操作 $1$，可以发现：如果 $x$ 左边最近的海港为 $l$，右边最近的海港为 $r$，那么这次操作就只会把 $[l+1,x-1]$ 覆盖为一个首项为 $a_l\times (x-l-1)$，公差为 $-a_l$ 的等差数列，$[x+1,r-1]$ 覆盖为一个一个首项为 $a_x\times (r-x-1)$，公差为 $-a_x$ 的等差数列，$x$ 位置修改为 $0$。

对于区间覆盖等差数列的操作，线段树上的每个节点都维护一个首项和公差的懒标记即可。

对于找左边和右边最近的海港，用个 $\texttt{set}$ 维护，时间复杂度 $O((n+q)\log n)$。

# Code
```c++
#include<bits/stdc++.h>
#define int long long
#define mid (l+r>>1)
using namespace std;
const int N=3e5+1;
int T[N<<2],b[N<<2],k[N<<2];
int n,m,q,a[N],pos[N];
set<int> S;

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
void pushup(int rt) {
	T[rt]=T[rt<<1]+T[rt<<1|1];
}
int f(int x,int y,int l) {
	if ( (x+y)%2) return l/2*(x+y);
	else return (x+y)/2*l;
}
void pushdown(int rt,int l,int r)
{
	if (k[rt]) {
		k[rt<<1]=k[rt],b[rt<<1]=b[rt],T[rt<<1]=f(b[rt],b[rt]+(mid-l)*k[rt],mid-l+1);
		k[rt<<1|1]=k[rt],b[rt<<1|1]=b[rt]+(mid-l+1)*k[rt],T[rt<<1|1]=f(b[rt<<1|1],b[rt]+(r-l)*k[rt],r-mid);
		k[rt]=0;
	}
}
void build(int rt,int l,int r)
{
	if (l==r) {
		if (a[l]) T[rt]=0;
		else {
			auto it=S.lower_bound(l);
			T[rt]=(*it)-l,it--,T[rt]*=a[*it];
		}
		return;
	}
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	pushup(rt);
}
void modify(int rt,int l,int r,int s,int t,int x,int y)
{
	if (s>t) return;
	if (s==l&&r==t) return T[rt]=f(x,x+(r-l)*y,r-l+1),b[rt]=x,k[rt]=y,void();
	pushdown(rt,l,r);
	if (t<=mid) modify(rt<<1,l,mid,s,t,x,y);
	else if (mid<s) modify(rt<<1|1,mid+1,r,s,t,x,y);
	else {
		modify(rt<<1,l,mid,s,mid,x,y);
		modify(rt<<1|1,mid+1,r,mid+1,t,x+(mid-s+1)*y,y);
	}
	pushup(rt);
}
int query(int rt,int l,int r,int s,int t)
{
	if (s<=l&&r<=t) return T[rt];
	pushdown(rt,l,r);
	if (t<=mid) return query(rt<<1,l,mid,s,t);
	if (mid<s) return query(rt<<1|1,mid+1,r,s,t);
	return query(rt<<1,l,mid,s,t)+query(rt<<1|1,mid+1,r,s,t);
}
main()
{
	memset(k,0,sizeof k);
	n=read(),m=read(),q=read();
	for (int i=0,x;i<m;i++) S.insert(pos[i]=read() );
	for (int i=0;i<m;i++) a[pos[i] ]=read();
	build(1,1,n);
	while (q--)
	{
		int o=read(),x=read(),y=read();
		if (o==1) {
			S.insert(x),a[x]=y;
			auto it=S.lower_bound(x),l=it,r=it;
			l--,r++; int L=*l,R=*r;
			modify(1,1,n,L+1,x-1,a[L]*(x-L-1),-a[L]);
			modify(1,1,n,x+1,R-1,a[x]*(R-x-1),-a[x]);
			modify(1,1,n,x,x,0,0);
		}
		else printf("%lld\n",query(1,1,n,x,y) );
	}
	return 0;
}
```

---

## 作者：MaxBlazeResFire (赞：9)

update on 2024.2.21：之前的代码无法通过，已更改。

考虑把每两个码头 $l,r$ 之间的所有代价看作这个连续段单元 $[l,r]$ 的代价，因为知道了 $l,r,v_l$ 之后代价是好计算的，用 $\rm set$ 维护。

但我们发现虽然可以直接解决插入的问题，但是区间和却不太好做。考虑时光倒流，先把最终状态下的连续段和每段的代价搞出来并给它们编号，查询的时候考虑在 $\rm set$ 上找出端点所在的连续段然后查用树状数组区间和，顺便处理一些边角料。

这样的好处在于，撤销一个点 $v$ 时，设原来包含它的两个连续段为 $[l,v,id_1],[v,r,id_2]$，只需要先在树状数组上将 $id_1,id_2$ 处的贡献减掉，然后计算 $[l,r]$ 的贡献重新统计进 $id_1$ 的贡献，我们发现连续段的相对位置关系不变，就可以维护了。

复杂度 $O(q\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
#define MAXN 300005
 
int n,m,q,X[MAXN],V[MAXN],opt[MAXN],qx[MAXN],qv[MAXN],ql[MAXN],qr[MAXN];
int tr[MAXN + 5],Ans[MAXN];
 
inline void add( int x , int k ){ for( ; x <= MAXN ; x += x & -x ) tr[x] += k; }
inline int sum( int x ){ int ret = 0; for( ; x ; x -= x & -x ) ret += tr[x]; return ret; }
 
struct node{
	int l,r,id,cost;
	inline bool operator <( node B ) const{ return r < B.r; }
};
 
inline int Sp( int x ){ return x * ( x + 1 ) / 2; }
 
signed main(){
	scanf("%lld%lld%lld",&n,&m,&q);
	multiset<node> S; S.insert( node{ 1 , n , 0 , 0 } );
	for( int i = 1 ; i <= m ; i ++ ) scanf("%lld",&X[i]);
	for( int i = 1 ; i <= m ; i ++ ) scanf("%lld",&V[X[i]]);
	for( int i = 1 ; i <= m ; i ++ ){
		if( X[i] == 1 || X[i] == n ) continue;
		set<node>::iterator it = S.lower_bound( node{ X[i] , X[i] , 0 , 0 } );
		S.insert( node{ it -> l , X[i] , 0 , 0 } );
		S.insert( node{ X[i] , it -> r , 0 , 0 } );
		S.erase( it );
	}
	for( int i = 1 ; i <= q ; i ++ ){
		scanf("%lld",&opt[i]);
		if( opt[i] == 1 ){
			scanf("%lld%lld",&qx[i],&qv[i]); V[qx[i]] = qv[i];
			set<node>::iterator it = S.lower_bound( node{ qx[i] , qx[i] , 0 , 0 } );
			S.insert( node{ it -> l , qx[i] , 0 , 0 } );
			S.insert( node{ qx[i] , it -> r , 0 , 0 } );
			S.erase( it );
		}
		else scanf("%lld%lld",&ql[i],&qr[i]);
	}
	int cnt = 0;
	multiset<node> S2;
	for( node N : S ){
		int l = N.l,r = N.r;
		N.id = ++cnt,N.cost = V[l] * Sp( r - l - 1 );
		add( N.id , N.cost );
		S2.insert( N );
	} S = S2;
	for( int i = q ; i >= 1 ; i -- ){
		if( opt[i] == 2 ){
			int L = ql[i],R = qr[i];
			multiset<node>::iterator it2 = S.lower_bound( node{ R , R , 0 , 0 } );
			multiset<node>::iterator it = S.lower_bound( node{ L , L , 0 , 0 } );
			if( it -> l == it2 -> l ){
				if( L == it -> l ) L ++;
				Ans[i] = V[it -> l] * ( Sp( R - L ) + ( R - L + 1 ) * ( it -> r - R ) );
			}
			else{
				int idl = it -> id,idr = it2 -> id;
				Ans[i] = sum( idr - 1 ) - sum( idl );
				int l1 = it -> l,l2 = it2 -> l,r1 = it -> r,r2 = it2 -> r;
				Ans[i] += V[l2] * ( Sp( R - l2 - 1 ) + ( R - l2 ) * ( r2 - R ) );
				if( L == l1 ) L ++;
				Ans[i] += V[l1] * Sp( r1 - L );
			}
		}
		else{
			int x = qx[i];
			multiset<node>::iterator it = S.lower_bound( node{ x , x , 0 , 0 } ),it2 = it;
			it2 ++; int idl = it -> id,idr = it2 -> id;
			add( idl , -( it -> cost ) ),add( idr , -( it2 -> cost ) );
			node New; New.l = it -> l,New.r = it2 -> r,New.id = idl,New.cost = V[New.l] * Sp( New.r - New.l - 1 );
			add( New.id , New.cost );
			S.erase( it ),S.erase( it2 );
			S.insert( New );
		}
	}
	for( int i = 1 ; i <= q ; i ++ ) if( opt[i] == 2 ) printf("%lld\n",Ans[i]);
	return 0;
}
```

---

## 作者：SunsetLake (赞：6)

## 思路

可以观察到一件事情：在两个港口之间的船他们对应的价值都是一样的，都为左边港口的权值。因此对于这段区间的价值和就可以写成 $val \times \sum dis$ 的形式，$\sum dis$ 便为这些船到右边港口的距离和。那么我们就可以按照港口把序列分成很多个区间来考虑。

港口用一个 set 维护，这样能很方便的插入以及找前驱后继。每次插入一个新港口时，设它左边第一个港口在 $l$，右边第一个在 $r$，他自己在 $now$。$now$ 就把 $l,r$ 分成了两个新的区间，我们就需要进行区间修改，不难想到用线段树维护，维护的值就是一段区间的 $val,\sum dis$ 以及整个区间的答案。对于 $(now,r]$ 这个区间，他们的 $\sum dis$ 没有改变，只是 $val$ 变成了新输入的 $v$，用懒标记区间赋值 $val$ 即可。对于 $[l,now)$ 改变的就是 $\sum dis$，但是因为有一个 $\sum$，不能区间推平了，必须换个角度思考。把 $\sum dis$ 拆成每个点单独的 $dis$，一开始是每个点到 $r$ 的距离，现在变成了每个点到 $now$ 的距离，减少的就是 $r-now$！于是把区间中的所有点都减去一个 $r-now$，相当于 $\sum dis$ 减去了 $len \times (r-now)$，把 $r-now$ 用懒标记记录下来，这是可以下传的，就维护好了。至于 $[now,now]$ 这个点，全部变成 $0$ 即可。

pushup 把左右儿子的 $dis$ 都加起来，$val$ 赋为左儿子的 $val$，区间答案直接 $\sum dis \times val$（我们只考虑每两个港口间的区间，不考虑跨区间的东西，因此可以直接用这个式子算答案）。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ls p<<1
#define rs p<<1|1
using namespace std;
int t;
const int N=3e5+5;
int n,m,q;
ll val[N],x[N];
set<ll>s;//维护港口
struct Tree{
	int l,r;
	ll sum;
	ll dis,val;
	ll ad,vl; //ad dis的懒标记，vl val的懒标记
}tr[N<<4];
inline void pushup(int p){
	tr[p].dis=tr[ls].dis+tr[rs].dis;
	tr[p].val=tr[ls].val;
	tr[p].sum=tr[ls].sum+tr[rs].sum;
}
inline void pushdown(int p){
	if(!tr[p].ad && !tr[p].vl)return;
	ll ds=tr[p].ad,vl=tr[p].vl;
	if(vl)tr[ls].val=vl,tr[rs].val=vl;
	tr[ls].dis-=(tr[ls].r-tr[ls].l+1)*ds;
	tr[rs].dis-=(tr[rs].r-tr[rs].l+1)*ds;
	tr[ls].sum=tr[ls].val*tr[ls].dis;
	tr[rs].sum=tr[rs].val*tr[rs].dis;
	tr[ls].ad+=ds;tr[rs].ad+=ds;
	if(vl)tr[ls].vl=vl,tr[rs].vl=vl;
	tr[p].ad=0;tr[p].vl=0;
	
}
void build(int p,int l,int r){
	tr[p].l=l;tr[p].r=r;
	if(l==r){
		auto nxt=s.lower_bound(l);//后继
		if((*nxt)==l)return;
		auto now=nxt;
		now--;
		tr[p].val=val[*now];
		tr[p].dis=(*nxt)-l;
		tr[p].sum=tr[p].val*tr[p].dis;
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(p);
}
void updatedis(int p,int l,int r,ll d){
	if(tr[p].l>=l&&tr[p].r<=r){
		tr[p].dis-=(tr[p].r-tr[p].l+1)*d;
		tr[p].sum=tr[p].dis*tr[p].val;
		tr[p].ad+=d;
		return;
	}
	pushdown(p);
	int mid=tr[p].l+tr[p].r>>1;
	if(l<=mid)updatedis(ls,l,r,d);
	if(r>mid)updatedis(rs,l,r,d);
	pushup(p);
}
void updateval(int p,int l,int r,ll d){
	if(tr[p].l>=l&&tr[p].r<=r){
		tr[p].val=d;
		tr[p].vl=d;
		tr[p].sum=tr[p].dis*tr[p].val;
		return;
	}
	pushdown(p);
	int mid=tr[p].l+tr[p].r>>1;
	if(l<=mid)updateval(ls,l,r,d);
	if(r>mid)updateval(rs,l,r,d);
	pushup(p);
}
ll query(int p,int l,int r){
	if(tr[p].l>=l&&tr[p].r<=r)return tr[p].sum;
	pushdown(p);
	int mid=tr[p].l+tr[p].r>>1;
	ll res=0;
	if(l<=mid)res+=query(ls,l,r);
	if(r>mid)res+=query(rs,l,r);
	return res;
}
void modify(int p,int x){
	if(tr[p].l==tr[p].r){
		tr[p].dis=tr[p].val=tr[p].ad=tr[p].vl=tr[p].sum=tr[p].val=0;
		return;
	}
	int mid=tr[p].l+tr[p].r>>1;
	if(x<=mid)modify(ls,x);
	else modify(rs,x);
	pushup(p);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=m;++i)cin>>x[i],s.insert(x[i]);
	for(int i=1;i<=m;++i)cin>>val[x[i]];
	build(1,1,n);
	while(q--){
		int op;
		ll l,r;
		cin>>op>>l>>r;
		if(op==1){
			s.insert(l);val[l]=r;
			auto pos=s.find(l);
			auto pre=pos,nxt=pos;
			pre--;nxt++; 
			ll prex=*pre;
			ll nxtx=*nxt;
			if(prex+1<l)updatedis(1,prex+1,l-1,(nxtx-l)); //更新左区间的dis
			if(l+1<nxtx)updateval(1,l+1,nxtx-1,r);//右区间的val
			modify(1,l);
		}
		else cout<<query(1,l,r)<<endl;
	}
	return 0;
}
```


---

## 作者：Svemit (赞：3)

# Solution

考虑维护任意两个相邻码头之间的费用总和，设 $val_i$ 表示第 $i$ 个码头与第 $i + 1$ 个码头之间所有船到达下一个码头的费用之和。

此时计算 $val$ 数组在初始时，与修改时都能够做到 $O(1)$。

用 set 来维护码头的位置，方便在新建码头时快速找到前驱和后继的位置。

每次新建一个码头，$val$ 要改变的只有前驱和当前的码头。

对于查询造作：我们不妨先把答案记录成 $[l, r]$ 中码头的 $val$ 值总和，发现有两段是需要我们额外去处理的。

在左边，我们是没有处理从 $l$ 到了后第一个码头的价值，把答案加上这一部分。

而在右边，我们多算了从 $r+1$ 开始到 $r$ 右边第一个码头价值，于是答案减去这一部分。

这样查询和修改我们都做到了 $\log n$，瓶颈在于区间求和与 set。

总复杂度 $O((n + q) \log n)$。

写法较丑。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
const int N = 3e5 + 5, INF = 0x3f3f3f3f;
const LL mod = 998244353;
int n, m, q;
set<int> s;
int val[N], w[N], g[N];
struct BIT {
    int N;
    vector<LL> c;
    #define lbt(x) x & -x
    BIT(int n) {
        N = n;
        c.resize(n + 1);
    }
    void modify(int x, LL v) {
        for(; x <= N; x += lbt(x)) c[x] += v;
    }
    LL query(int x) {
        LL res = 0;
        for(; x; x -= lbt(x)) res += c[x];
        return res;
    }
    LL query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m >> q;
    BIT bit(n);
   	for(int i = 1; i <= m; i ++) {
   		int x;
   		cin >> x;
        g[i] = x;
   		s.insert(x);
   	}
   	for(int i = 1; i <= m; i ++) {
        int v;
        cin >> v;
        w[g[i]] = v;
    }
   	for(auto it = s.begin(); it != s.end(); it ++) {
		auto it2 = it;
		it2 ++;
		int p = *it, nxt = *it2;
        if(p == n) continue;
		int d = nxt - p - 1;
		val[p] = d * (d + 1ll) / 2ll * w[p];
		bit.modify(p, val[p]);
   	}
   	while(q --) {
   		int op, x, y;
   		cin >> op >> x >> y;
   		if(op == 1) {
   			w[x] = y;
   			auto it = s.lower_bound(x);
   			int nxt = *it;
   			it --;
   			int pre = *it;
   			bit.modify(pre, -val[pre]);
   			int d = x - pre - 1;
   			val[pre] = d * (d + 1ll) / 2ll * w[pre];
   			bit.modify(pre, val[pre]);
   			d = nxt - x - 1;
   			val[x] = d * (d + 1ll) / 2ll * w[x];
   			bit.modify(x, val[x]);
   			s.insert(x);
   		}
   		else {
   			int ans = bit.query(x, y);
   			int l = *--s.upper_bound(x), ll = *s.lower_bound(x), r = *s.upper_bound(y), rr = *--s.upper_bound(y);
   			int d = ll - x;
   			ans += d * (d + 1ll) / 2ll * w[l];
   			if(y != r && y != n) {
   				d = r - y - 1;
   				ans -= d * (d + 1ll) / 2ll * w[rr];
   			}
   			cout << ans << '\n';
   		}
   	}
    return 0;
}
```

---

## 作者：2020kanade (赞：1)

直接介绍一种最简单粗暴（指不用动脑子）的做法。

设第 $i$ 个位置右侧最近的港口坐标为 $b_i$ （显然有 $b_i\ge i$），其左侧最近的港口价值为 $a_i$，把题目要求的式子 $\sum{a_i\times(b_i-i)}$ 拆开可得 $\sum a_ib_i-\sum ia_i$，形如 $\sum a_ib_i$ 的部分视为两个等长二维向量的点积，可以用线段树维护，具体实现请参考下面的代码。

然后，考虑相邻两个港口中间的所有位置，设包含两个港口在内的这个区间为 $[l,r]$，那么显然，$[l,r-1]$ 之间所有位置的 $a_i$ 值都是 $V_l$，$[l+1,r]$ 之间所有位置的 $b_i$ 值都是 $r$。

使用 ```std::set``` 按位置坐标升序为关键字维护所有港口，在插入新港口时辅助线段树进行 $a_i,b_i$ 的区间推平修改即可。

时间复杂度 $\Theta((n+m+q)\log n)$。

```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
struct info
{
	ll a,b,x,sa,sb,sx,x2,sab,sxa,len;
	info() {sxa=a=b=x=sa=sb=sx=sab=0,len=1;};
	info(ll x,ll sx,ll len):x(x),sx(sx),len(len) {sxa=sab=a=b=sa=sb=0;};
};
struct tag
{
	bool sa,sb;
	ll ta,tb;
	tag(){ta=tb=sa=sb=0;}
	tag(ll x,bool p):ta(0),sa(0),sb(0),tb(0)
	{
		if(p) sb=1,tb=x;else sa=1,ta=x;
	}
	tag(ll a,ll b):ta(a),sa(1),sb(1),tb(b) {}
	bool ept(){return (!sa)&&(!sb);}
	void clr() {ta=tb=sa=sb=0;}
	void chkinfo(bool edl=0)
	{
		cout<<"TAG:"<<ta<<' '<<sa<<' '<<tb<<' '<<sb<<' ';
		if(edl) cout<<endl;
	}
};
tag operator + (tag a,tag b)
{
	tag ret;
	if(a.ept()) return b;
	if(b.ept()) return a;
	ret=b;if(a.sa&&(!b.sa)) ret.sa=1,ret.ta=a.ta;
	if(a.sb&&(!b.sb)) ret.sb=1,ret.tb=a.tb;
	return ret;
}
info operator + (const info& a,tag& b)
{
	if(b.ept()) return a;
	info c(a.x,a.sx,a.len);
	if(b.sa&&b.sb)
	{
		c.sab=c.len*b.ta*b.tb,c.a=b.ta,c.b=b.tb;
		c.sa=c.a*c.len,c.sb=c.b*c.len;
		c.sxa=c.sx*c.a;return c;
	}
	else if(b.sa)
	{
		c.a=b.ta,c.b=a.b;
		c.sa=c.len*c.a,c.sb=a.sb,c.sab=c.a*c.sb;
		c.sxa=c.sx*c.a;return c;
	}
	else if(b.sb)
	{
		c.a=a.a,c.b=b.tb;
		c.sb=c.len*c.b,c.sa=a.sa,c.sab=c.b*c.sa;
		c.sxa=a.sxa;return c;
	}
	else return a;
}
info operator + (const info& a,const info& b)
{
	info c(a.x,a.sx+b.sx,a.len+b.len);
	c.a=a.a,c.b=a.b;c.sa=a.sa+b.sa,c.sb=a.sb+b.sb;
	c.sab=a.sab+b.sab,c.sxa=a.sxa+b.sxa;return c;
}
struct segtree
{
	int sz,rt,ct;
	vector<info> v;vector<tag> tg;
	vector<int> ls,rs;
	segtree(int sz):sz(sz),v(sz*2+3),tg(sz*2+3),ls(sz*2+3,0),rs(sz*2+3,0),rt(0),ct(0) {}
	void down(int x)
	{
		if(tg[x].ept()) return;
		v[ls[x]]=v[ls[x]]+tg[x],tg[ls[x]]=tg[ls[x]]+tg[x];
		v[rs[x]]=v[rs[x]]+tg[x],tg[rs[x]]=tg[rs[x]]+tg[x];
		tg[x].clr();
	}
	void up(int x)
	{
		v[x]=v[ls[x]]+v[rs[x]];
	}
	void change1(int x,int l,int r,int sl,int sr,tag _v)
	{
		//cout<<"IN:"<<x<<' '<<l<<' '<<r<<' '<<v[x].a<<' '<<v[x].b<<' '<<v[x].sa<<' '<<v[x].sb,tg[x].chkinfo(1);
		if(sl<=l&&r<=sr)
		{
			tg[x]=tg[x]+_v,v[x]=v[x]+_v;
			//cout<<"OUT:"<<x<<' '<<l<<' '<<r<<' '<<v[x].a<<' '<<v[x].b<<' '<<v[x].sa<<' '<<v[x].sb,tg[x].chkinfo(1);
			return;
		}down(x);int mid=(l+r)/2;
		if(sl<=mid) change1(ls[x],l,mid,sl,sr,_v);
		if(mid+1<=sr) change1(rs[x],mid+1,r,sl,sr,_v);
		up(x);//cout<<"OUT:"<<x<<' '<<l<<' '<<r<<' '<<v[x].a<<' '<<v[x].b<<' '<<v[x].sa<<' '<<v[x].sb,tg[x].chkinfo(1);
	}
	info ask(int x,int l,int r,int ql,int qr)
	{
		//cout<<"QIN:"<<x<<' '<<l<<' '<<r<<' '<<v[x].a<<' '<<v[x].b<<' '<<v[x].sa<<' '<<v[x].sb,tg[x].chkinfo();
		if(ql<=l&&r<=qr) return v[x];
		down(x);int mid=(l+r)/2;
		if(ql<=mid&&mid+1<=qr) return ask(ls[x],l,mid,ql,qr)+ask(rs[x],mid+1,r,ql,qr);
		else if(ql<=mid) return ask(ls[x],l,mid,ql,qr);
		else return ask(rs[x],mid+1,r,ql,qr);
	}
	void c0nst(int &x,int l,int r)
	{
		if(!x) x=++ct;
		if(l==r)
		{
			v[x]=info(l,l,1);
			return;
		}
		int mid=(l+r)/2;
		c0nst(ls[x],l,mid),c0nst(rs[x],mid+1,r);
		return up(x);
	}
	void change(int l,int r,tag _v)
	{
		change1(rt,0,sz,l,r,_v);
	}
	info ask(int l,int r)
	{
		return ask(rt,0,sz,l,r);
	}
	void _init()
	{
		c0nst(rt,0,sz);
	}
};
set<pair<int,int> > harbs;
void solve()
{
	cin>>n>>m>>q;harbs.clear();
	vector<pair<int,int> > hajime(m+1,{0,0});
	for(int i=1;i<=m;++i) cin>>hajime[i].first;
	for(int i=1;i<=m;++i) cin>>hajime[i].second;
	sort(hajime.begin()+1,hajime.end());
	for(int i=1;i<=m;++i)
	{
		harbs.insert(hajime[i]);
	}
	segtree sgt(n+2);sgt._init();
	for(int i=1;i<=m;++i)
	{
		int l=hajime[i].first,r;
		if(i==m) r=hajime[i].first;
		else r=hajime[i+1].first-1;//cout<<l<<' '<<r<<' '<<hajime[i].second<<endl;
		sgt.change(l,r,tag(hajime[i].second,false));
	}
	for(int i=m;i;--i)
	{
		int r=hajime[i].first,l;
		if(i==1) l=hajime[i].first;
		else l=hajime[i-1].first+1;//cout<<l<<' '<<r<<' '<<hajime[i].first<<endl;
		sgt.change(l,r,tag(hajime[i].first,true));
	}
	for(int i=1;i<=q;++i)
	{
		int opt,x,v;
		cin>>opt>>x>>v;
		if(opt==1)
		{
			auto it1=harbs.lower_bound({x,v}),it2=it1;--it2;
			int l1=(*it2).first+1,r1=x,l2=x,r2=(*it1).first-1;
			sgt.change(l1,r1,tag(x,true));
			sgt.change(l2,r2,tag(v,false));
			harbs.insert({x,v});
		}
		else
		{
			info ans=sgt.ask(x,v);
			//cout<<ans.a<<' '<<ans.b<<' '<<ans.x<<endl;
			cout<<ans.sab-ans.sxa<<endl;
		}
	}
}
int main()
{
   syncoff();
	solve();
	return 0;
}
```


---

## 作者：ダ月 (赞：1)

首先我们考虑每加入一个港口，位于 $x$ 带来的影响。我们即 $pre_x$ 表示 $x$ 这个位置左边最接近的港口，$suf_x$ 表示 $x$ 这个位置右边最接近的港口。我们下面称呼距离带来的贡献为距离贡献，权值带来的贡献为权值贡献。

首先，$(pre_x+1)\sim x$ 这些点到靠右边的港口距离应当变小，距离贡献减小了 $suf_x-x$。$x\sim suf_x$ 这些点的权值贡献从原本 $pre_x$ 的贡献变成了 $x$ 这个新港口的贡献。记 $val_i$ 表示 $i$ 这个港口的权值。只要 $x\sim suf_x$ 节点的权值贡献加上 $val_{x}-val_{suf_x}$ 即可。$pre_x$ 和 $suf_x$ 可以用 `std::set` 来维护。但是注意一些细节。$i$ 位置的距离贡献初始为 $n-i+1$，这里初始贡献指没有加入任何一个港口的时候。

答案显然是距离贡献乘上权值贡献。我们不妨记作两种信息。我们需要支持一个数据结构，能够满足两种信息分别区间加，两种信息乘积的和即可。显然可以线段树。这是一个很套路的问题，就是维护一个矩阵，这里不赘述。

上述时间复杂度：$O(n\log n)$。

```
const int N=3e5+10;
struct Mes{ll SA,SB;ll S;};//A 信息表示距离贡献，B 信息表示权值贡献，SA 表示区间 A 信息的和，SB 同理。S 表示区间 A 信息乘上 B 信息的乘积的和。
Mes operator + (Mes x,Mes y){
	Mes ans;
	ans.SA=x.SA+y.SA;
	ans.SB=x.SB+y.SB;
	ans.S=x.S+y.S;
	return ans;
}
int u;
struct sg_tree{
	struct node{
		Mes x;
		ll tagA,tagB;
		ll len;
	}tr[N<<2];
	void pushup(int rt){tr[rt].x=tr[rt<<1].x+tr[rt<<1|1].x;}
	void addA(int rt,ll x){tr[rt].x.SA+=x*tr[rt].len;tr[rt].x.S+=x*tr[rt].x.SB;tr[rt].tagA+=x;}
	void addB(int rt,ll x){tr[rt].x.SB+=x*tr[rt].len;tr[rt].x.S+=x*tr[rt].x.SA;tr[rt].tagB+=x;}
	void pushdown(int rt){
		if(tr[rt].tagA){
			addA(rt<<1,tr[rt].tagA);
			addA(rt<<1|1,tr[rt].tagA);
			tr[rt].tagA=0;
		}
		if(tr[rt].tagB){
			addB(rt<<1,tr[rt].tagB);
			addB(rt<<1|1,tr[rt].tagB);
			tr[rt].tagB=0;
		}
	}
	void build(int rt,int l,int r){
		tr[rt].len=r-l+1;
		if(l==r)return tr[rt].x.SA=u-l+1,void();
		auto mid=l+r>>1;
		build(rt<<1,l,mid);build(rt<<1|1,mid+1,r);
		pushup(rt);
	}
	void changeA(int rt,int l,int r,int x,int y,ll z){
		if(x>y)return;
		if(x<=l&&r<=y)return addA(rt,z),void();
		auto mid=l+r>>1;pushdown(rt);
		if(x<=mid)changeA(rt<<1,l,mid,x,y,z);
		if(y>mid)changeA(rt<<1|1,mid+1,r,x,y,z);
		pushup(rt);
	}void changeB(int rt,int l,int r,int x,int y,ll z){
		if(x>y)return;
		if(x<=l&&r<=y)return addB(rt,z),void();
		auto mid=l+r>>1;pushdown(rt);
		if(x<=mid)changeB(rt<<1,l,mid,x,y,z);
		if(y>mid)changeB(rt<<1|1,mid+1,r,x,y,z);
		pushup(rt);
	}Mes query(int rt,int l,int r,int x,int y){
		if(x<=l&&r<=y)return tr[rt].x;
		auto mid=l+r>>1;pushdown(rt);
		if(x<=mid&&y>mid)return query(rt<<1,l,mid,x,y)+query(rt<<1|1,mid+1,r,x,y);
		if(x<=mid)return query(rt<<1,l,mid,x,y);
		if(y>mid)return query(rt<<1|1,mid+1,r,x,y); 
	}
}Tr;
void solve(){
	//don't forget to open long long
	int n,m,q;IO::cin>>n>>m>>q;u=n;
	Tr.build(1,1,n);
	std::set<int>st;
	std::vector<ll>pval(n+1,0);
	auto insert=[&](int x,ll val)->void{
		auto p=st.lb(x);pval[x]=val;
		if(p==st.end()){
			if(st.size()==0){
				Tr.changeA(1,1,n,1,x,-n);Tr.changeB(1,1,n,x,n,val);st.insert(x);return;}
			else{
				p--;
				int L=*p;
				Tr.changeB(1,1,n,x,n,-pval[L]);
				Tr.changeA(1,1,n,L+1,x,-(n-x+1));Tr.changeB(1,1,n,x,n,val);st.insert(x);
				return;
			}
		}
		int R=*p;
		if(p==st.begin()){Tr.changeB(1,1,n,x,R,val);Tr.changeA(1,1,n,1,x,-(R-x));st.insert(x);return;}
		p--;int L=*p;
		Tr.changeA(1,1,n,L+1,x,-(R-x));Tr.changeB(1,1,n,x,R,-pval[L]);Tr.changeB(1,1,n,x,R,val);
		st.insert(x);
	};
	std::vector<std::pair<int,int>>pl(m+1);
	for(int i=1;i<=m;i++)IO::cin>>pl[i].first;
	for(int i=1;i<=m;i++)IO::cin>>pl[i].second;
	sort(all(pl));//抽象之初始不升序。
	for(int i=1;i<=m;i++)insert(pl[i].first,pl[i].second);
	while(q--){
		ll opt,x,y;IO::cin>>opt>>x>>y;
		if(opt==1)insert(x,y);
		else IO::cout<<Tr.query(1,1,n,x,y).S<<'\n';
	}
}
```

---

## 作者：UnyieldingTrilobite (赞：1)

不难发现这个形式长得一脸 segment tree。所以我们直接考虑怎么维护 $[l,r]$ 的信息并支持合并。不难发现最左边和最右边的没有港口的两批船应当被拉出来维护，据此启发，我们可以简单设计出我们的信息结构体：

```cpp
struct info {
  int lv, rv, lc, rc, ans;
};
```

几个元素的含义是：区间最左边的港口权值（不存在则设为 0，下同），区间最右边的港口权值，区间从左起连着多少个点没有港口，区间从右起连着多少个点没有港口，区间最左最右港口间所有点的答案。那么合并两个区间的信息时，有至少一个区间内无港口的情况是平凡的；对于两个区间内均有港口的情况，我们要算的无非是左区间最右边的港口和右区间最左边的港口之间点的贡献，写个等差数列求和就行。

然后查询的时候，我们除了要知道 $[l,r]$ 的信息外，还需要知道 $[1,l]$ 最右边的港口和 $[r,n]$ 最左边的港口。这看起来需要用链表之类的东西维护一下，但实际上我们复用同一棵线段树把 $[1,l]$ 和 $[r,n]$ 全都查出来就行。

代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 3e5 + 9, T = 1 << 19;
inline int getsum(int a, int n) { return n * (n + a + a - 1) >> 1; }
struct info {
  int lv, rv, lc, rc, ans;
  info(int lv, int rv, int lc, int rc, int ans)
      : lv(lv), rv(rv), lc(lc), rc(rc), ans(ans) {}
  info() : info(0, 0, 0, 0, 0) {}
  info(int v) : info(v, v, !v, !v, 0) {}
  friend info operator+(info a, info b) {
    if (!a.lv && !b.rv) return {0, 0, a.lc + b.lc, a.rc + b.rc, 0};
    if (!a.lv) return b.lc += a.lc, b;
    if (!b.rv) return a.rc += b.rc, a;
    return {a.lv, b.rv, a.lc, b.rc,
            a.ans + b.ans + getsum(1, a.rc + b.lc) * a.rv};
  }
} zkw[T << 1];
int n, m, q, M;
inline void pushup(int x) { zkw[x] = zkw[x << 1] + zkw[x << 1 | 1]; }
inline void update(int x, int v) {
  zkw[x += M] = v;
  while (x >>= 1) pushup(x);
}
inline info qinfo(int l, int r) {
  info L, R;
  for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
    if (~l & 1) L = L + zkw[l ^ 1];
    if (r & 1) R = zkw[r ^ 1] + R;
  }
  return L + R;
}
inline int query(int l, int r) {
  info L = qinfo(1, l).rv + qinfo(l, r);
  return L.ans + getsum(qinfo(r, n).lc, L.rc) * L.rv;
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m >> q, M = 1 << (__lg(n) + 1);
  int x[m], v[m];
  for (int i = 0; i < m; ++i) cin >> x[i];
  for (int i = 0; i < m; ++i) cin >> v[i];
  for (int i = 1; i <= n; ++i) zkw[i + M] = 0;
  for (int i = 0; i < m; ++i) zkw[x[i] + M] = v[i];
  for (int i = M - 1; i; --i) pushup(i);
  for (int op, x, y; q; --q)
    if (cin >> op >> x >> y, op == 1)
      update(x, y);
    else
      cout << query(x, y) << '\n';
  return cout << flush, 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：1)

场上第一个思路是线段树直接做区间推平等差数列、区间求和，但是仔细一想发现我不会（雾

考虑对于每两个相邻的 $1$ 的位置 $x,y$，在左端点 $x$ 处统计贡献 $a_x \sum \limits_{i=1}^{y-x-1}i$。

用 set 维护 $1$ 的位置，对每次询问区间，找到五个 $1$ 的位置 $pl,ql,tr,pr,qr$，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/n6rr0gva.png)

发现对于 $ql \sim tr$ 之间的关键点，它们的贡献区间被 $[l,r]$ 完整包含，可以直接加上。对于 $pr \sim r$ 和 $l \sim ql$ 两段区间，它们对答案的贡献是一个等差数列，可以直接加上。

修改操作不会影响我们对两边散区间的单独计算，只会影响中间段的贡献，我们找到新增位置 $x$ 的前驱 $k$，更改 $k,x$ 两处的值。

综上，我们还需要一个单点改区间求和的数据结构，树状数组即可。总时间复杂度 $\mathcal O(n \log n)$。

注意如果区间内不存在 $ql,tr,pr$，需要一些特判。

[赛时代码](https://codeforces.com/contest/1925/submission/243644751)，写的很乱，还有一些可省略的特判。把线段树改成树状数组再稍微优化一下代码码长应该能到 1.5k 左右吧。






---

## 作者：Z1qqurat (赞：0)

大型连续剧《我是 sb》将持续为您播出。

首先容易发现在两个相邻的关键点 $l,r$ 之间的一段权值是等差数列，设 $len=r-l-1$，那么这中间 $len$ 个点的权值依次为 $len\times v_l,(len-1)v_l,\dots,2v_l,v_l$。

那么考虑在线段树上维护每个位置的权值，分析插入一个新关键点的影响：（丑陋的手写）

![](https://pic.imgdb.cn/item/65c7888a9f345e8d033faaee.jpg)

然后就直接维护区间加乘线段树。不过发现这个乘法 $tag$ 的分母实际上不会超过 $10^7$ 因为每次乘都会抵消掉原先的分母，所以直接对乘法 $tag$ 维护一个分数类，加法 $tag$ 以及区间和一定会是整数所以直接用 `int64_t` 维护就好了。分数乘法涉及到约分可能常数比较大，只开个快读然后等编译器心情好的时候就可以 1996ms 卡过了（

也可以类似于 Rain_chr 的那种做法，模一个大质数，但是要注意的就是 `int64_t` 貌似不支持 `constexpr i64 P = 1e18 + 3` 这一类的赋值，如果这么赋会直接变成 `1e18`，导致模数是合数……

[Submission](https://codeforces.com/contest/1924/submission/245725366)

---

## 作者：BYR_KKK (赞：0)

[link](https://codeforces.com/contest/1924/problem/B)

题解区感觉都好麻烦啊。

发现对于一个没有船的点 $x_i$，代价是 $V_l\times (r-x_i)$。

所以对于一段没有船的区间 $[L,R]$，代价是 $\sum\limits_L^RV_l\times (r-x_i)$。

由于 $V_l$ 和 $r$ 都是定值，所以可以变为 $V_l\times (R-L+1)\times r-V_l\times\sum\limits_L^Rx_i$。

这个东西可以通过等差数列快速求出来，相当于我们可以快速求出来一段没有船的区间的代价。

所以我们想到用线段树来维护区间的代价。

如果要插入一艘船，设插入位置为 $p$，插入之前最靠近 $p$ 的船为 $l$ 和 $r$，我们只需要修改三段区间：

- $[l+1,x-1]$

- $[x+1,r-1]$

- $[x,x]$，将代价改为 $0$。

至于找插入之前最靠近的船，可以用 set 来维护。

时间复杂度 $O((m+q)\log n)$。

```cpp

#include<bits/stdc++.h>

typedef long long LL;
//typedef int long long;
typedef std::pair<int,int> pii;

#define ok putstrln("OrzFinderHT")
#define int long long
//#define check_time printf("%.8f\n",clocks()/CLOCK_PER_SEC)

template<typename T>
void abs(T &N){
	if(N>=0) N=N;
	else N=-N;
}

namespace G_{
	template<typename T>
	inline void read(T &a){
		a=0;
		int f=1;
		char c=getchar();
		while(c<'0'||c>'9'){
			if(c=='-') f=-1;
			c=getchar();
		}
		while(c>='0'&&c<='9') a=a*10+(int)(c-'0'),c=getchar();
		a*=f;
	}
	inline void get_enter(){
		getchar();
	}
	inline void get_str(std::string &str){
		char c=getchar();
		while(c!=' '&&c!='\n') str+=c,c=getchar();
	}
	template<typename T>
	inline void putN(T N){
		char stk[70];
		short top=0;
		if(N<0) putchar('-'),abs(N);
		do{
			stk[++top]=N%10+48;
			N/=10;
		}while(N);
		while(top) putchar(stk[top--]);
	}
	template<typename T>
	inline void putsp(T N){
		putN(N);
		putchar(' ');
	}
	template<typename T>
	inline void putln(T N){
		putN(N);
		putchar('\n');
	}
	inline void putstr(std::string str){
		int sz=str.size()-1;
		for(int i=0;i<=sz;i++) putchar(str[i]);
	}
	inline void putstrln(std::string str){
		putstr(str);
		putchar('\n');
	}
	inline void Yes(){
		putstrln("Yes");
	}
	inline void No(){
		putstrln("No");
	}
}

//using namespace get_give;

using namespace G_;

const int maxn=3e5+10;

struct tree{
	LL l,r,ls,rs,lz,sum,vl,Rr;
}s[maxn*2];

int tot=0,n,m,q,X[maxn],V[maxn];

std::set<int>st;

int f(LL sx,LL wx,LL xs){
	return (sx+wx)*xs/2;
}

void push_up(int p){
	int ls=s[p].ls,rs=s[p].rs;
	s[p].sum=s[ls].sum+s[rs].sum;
}

int build(int l,int r){
	int p=++tot;
	s[p].l=l,s[p].r=r;
	if(l==r) return p;
	int mid=(l+r)>>1;
	s[p].ls=build(l,mid);
	s[p].rs=build(mid+1,r);
//	if(l==5&&r==8) printf("#####%lld\n",p);
//	if(p==17) printf("@@@@@%lld %lld\n",s[p].l,s[p].r);
	push_up(p);
	return p;
}

void push_down(int p){
	if(s[p].lz){
		LL ls=s[p].ls,rs=s[p].rs,vl=s[p].vl,Rr=s[p].Rr;
		s[ls].lz=s[rs].lz=1;
		s[p].lz=0;
		s[ls].sum=(s[ls].r-s[ls].l+1)*vl*Rr-vl*f(s[ls].l,s[ls].r,s[ls].r-s[ls].l+1);
		s[rs].sum=(s[rs].r-s[rs].l+1)*vl*Rr-vl*f(s[rs].l,s[rs].r,s[rs].r-s[rs].l+1);
//		if(p==16) ok;
		s[ls].vl=s[rs].vl=vl;
		s[ls].Rr=s[rs].Rr=Rr;
	}
	return ;
}

void update(int p,int L,int R,int vl,int Rr){
	int l=s[p].l,r=s[p].r;
	if(l>=L&&r<=R){
		s[p].lz=1;
		s[p].sum=(r-l+1)*vl*Rr-vl*f(l,r,r-l+1);
		s[p].vl=vl,s[p].Rr=Rr;
		return ;
	}
	push_down(p);
	int mid=(l+r)>>1;
	if(mid>=L) update(s[p].ls,L,R,vl,Rr);
	if(R>mid) update(s[p].rs,L,R,vl,Rr);
	push_up(p);
	return ;
}

int query(int p,int L,int R){
	int l=s[p].l,r=s[p].r;
	if(l>=L&&r<=R) return s[p].sum;
	push_down(p);
	int mid=(l+r)>>1,ret=0;
	if(mid>=L) ret+=query(s[p].ls,L,R);
	if(R>mid) ret+=query(s[p].rs,L,R);
	return ret;
}

signed main(){
//	std::ios::sync_with_stdio(false);
//	std::cin.tie(0);
	read(n),read(m),read(q);
	build(1,n);
	for(int i=1;i<=m;i++) {
		int loc;
		read(loc);
		st.insert(loc);
		X[i]=loc;
	}
//	std::sort(X+1,X+m+1);
	for(int i=1;i<=m;i++) read(V[X[i]]);
	std::sort(X+1,X+m+1);
	for(int i=1;i<m;i++) update(1,X[i]+1,X[i+1]-1,V[X[i]],X[i+1]);//,printf("%lld\n",query(1,2,7));
//	ok;
//	printf("%lld\n",query(1,3,8));
//	ok;
	int cnt=m;
	while(q--){
		int opt;
		read(opt);
		if(opt==1){
			int x,v;
			read(x),read(v);
			st.insert(x);
			auto it=st.lower_bound(x),l=it,r=it;
			l--,r++;
			int rn=*r,ln=*l;
			update(1,ln+1,x-1,V[ln],x);
			update(1,x+1,rn-1,v,rn);
			update(1,x,x,0,0);
			V[x]=v;
		}else {
			int l,r;
			read(l),read(r);
			printf("%lld\n",query(1,l,r));
		}
	}
	return 0;
}
/*
-读入字符一定检查回车
- 能不能搜索？
-函数要有返回值！
-想好了再写！
*/

/*
1000 3 1
1 1000 318
2704361 9570636 1106813
2
*/

```

---

## 作者：SamHJD (赞：0)

## [Space Harbour](https://www.luogu.com.cn/problem/CF1924B)

### 题意

长为 $n$ 的数轴上有 $m$ 个关键点，每个关键点有一个权值 $v$。

$q$ 次操作，每次可以加一个关键点，或求出 $[l,r]$ 中每个点**左边第一个关键点的权值 $val$ 乘与右边第一个关键点的距离** $dis$ 的和。

### 解法

添加一个关键点 $i$，其位置为 $x_i$，设其左边第一个关键点为 $a$，右边第一个关键点为 $b$。观察对哪些点有影响。

对于 $[x_a+1,x_i-1]$ 中的点，其右边第一个关键点从 $b$ 变为 $i$，因此距离都会减少 $x_b-x_i$，此区间答案减少 $(x_b-x_i)\times\sum\limits_{j=x_a+1}^{x_i-1}{val}_j$。

对于 $[x_i,x_b-1]$ 中的点，其左边第一个关键点的权值变为 $v_i$，此区间答案变为 $v_i\times\sum\limits_{j=x_i}^{x_b-1}{dis}_j$。

我们可以用线段树支持区间修改推平，并维护 $val,dis$ 和答案的区间和。

### [代码](https://www.luogu.com.cn/paste/flaw7ozh)

---

## 作者：Struct_Sec (赞：0)

给一个不太一样的做法。

考虑用set维护两个相邻港口之间的线段，线段树维护某个港口到上一个港口之间的点答案和。

每次修改将一个线段分成两个线段，单点修改原线段的右端点和新加入的点在线段树上的权值。

查询的话先算其中所有整段的答案，两边多出来的残段特殊处理即可。

线段树维护单点修改和区间求和即可，时空复杂度 $O(Q\log N)$。

[code](https://codeforces.com/contest/1925/submission/243875315)

---

## 作者：Iniaugoty (赞：0)

来个赛时没写完的无脑 DS 做法。

首先你要保证你要会写这两种线段树：

- 区间赋值，单点查询。

- 区间赋值，区间加等差数列，区间求和。

然后就可以看这篇题解了。

显然我们需要维护每个点左边和右边最近的关键点。发现每次 `1` 操作相当于一个区间赋值，那么线段树直接上。

```cpp
struct Tree {
    int t[N << 2]; // 区间赋值的标记
    void Pushdown(int u) { if (t[u]) t[u << 1] = t[u << 1 | 1] = t[u], t[u] = 0; } // 标记下传
    void Update(int L, int R, int x, int l, int r, int u) { // 区间赋值操作
        if (L > R) return ;
        if (L <= l && r <= R) return t[u] = x, void();
        Pushdown(u); int mid = l + r >> 1;
        if (L <= mid) Update(L, R, x, l, mid, u << 1);
        if (R > mid) Update(L, R, x, mid + 1, r, u << 1 | 1);
    }
    int Query(int x, int l, int r, int u) { // 单点查询操作
        if (l == r) return t[u];
        Pushdown(u); int mid = l + r >> 1;
        if (x <= mid) return Query(x, l, mid, u << 1);
        else return Query(x, mid + 1, r, u << 1 | 1);
    }
} lt, rt; // 两棵树，一个维护左边最近的，一个维护右边最近的
```

不难想到，两个最近的关键点之间，权值应该呈现一个等差数列。`1` 操作如果在原权值基础上修改的话，比较麻烦，不妨先清零然后重新算一遍。那么一个维护区间赋值、区间加等差数列、区间求和的线段树就好了。

```cpp
LL a[N << 2], d[N << 2], s[N << 2]; bool tag[N << 2];
// a 是等差数列的第 0 项标记，d 是公差标记
// tag 是赋值标记，s 是区间和
void Maketag1(int u) { a[u] = d[u] = s[u] = 0, tag[u] = 1; } // 打上赋值标记
LL Getlast(LL a, LL d, LL k) { return a + d * k; } // 等差数列通项
LL Getsum(LL a, LL d, LL k) { return (Getlast(a, d, 1) + Getlast(a, d, k)) * k >> 1ll; } // 等差数列求和
void Maketag2(int u, LL b, LL t, LL k) { a[u] += b, d[u] += t, s[u] += Getsum(b, t, k); } // 打上加等差数列标记
void Pushdown(int u, int l, int r) { // 标记下传，注意顺序
    int mid = l + r >> 1;
    if (tag[u])
        Maketag1(u << 1),
        Maketag1(u << 1 | 1),
        tag[u] = 0;
    if (a[u] || d[u])
        Maketag2(u << 1, a[u], d[u], mid - l + 1),
        Maketag2(u << 1 | 1, Getlast(a[u], d[u], mid - l + 1), d[u], r - mid),
        a[u] = d[u] = 0;
}
void Pushup(int u) { s[u] = s[u << 1] + s[u << 1 | 1]; } // 合并子节点信息，更新区间和
void Modify(int L, int R, int l, int r, int u) { // 区间赋值（特别地，这里只包括赋值为 0）
    if (L <= l && r <= R) return Maketag1(u);
    Pushdown(u, l, r); int mid = l + r >> 1;
    if (L <= mid) Modify(L, R, l, mid, u << 1);
    if (R > mid) Modify(L, R, mid + 1, r, u << 1 | 1);
    Pushup(u);
}
void Update(int L, int R, LL a, LL d, int l, int r, int u) { // 区间加等差数列
    if (L > R) return ;
    if (L <= l && r <= R) return Maketag2(u, Getlast(a, d, l - L), d, r - l + 1);
    Pushdown(u, l, r); int mid = l + r >> 1;
    if (L <= mid) Update(L, R, a, d, l, mid, u << 1);
    if (R > mid) Update(L, R, a, d, mid + 1, r, u << 1 | 1);
    Pushup(u);
}
LL Query(int L, int R, int l, int r, int u) { // 区间求和
    if (L <= l && r <= R) return s[u];
    Pushdown(u, l, r); int mid = l + r >> 1; LL res = 0;
    if (L <= mid) res += Query(L, R, l, mid, u << 1);
    if (R > mid) res += Query(L, R, mid + 1, r, u << 1 | 1);
    return res;
}
```

然后……然后就做出来了。

注意输入的 $x$ 可能不按大小顺序，一些写法中要排序一下。

```cpp
#include <bits/stdc++.h>

#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 3e5 + 5;

int n, m, q, x[N]; LL w[N];

void Update(int l, int r) {
    Modify(l, r, 1, n, 1);
    Update(l + 1, r - 1, (LL) (r - l) * w[l], -w[l], 1, n, 1);
}

int main() {
    freopen("wmyr.in", "r", stdin);
    freopen("wmyr.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> q;
    F(i, 1, m) cin >> x[i];
    F(i, 1, m) cin >> w[x[i]];
    sort(x + 1, x + m + 1);
    F(i, 1, m - 1)
        lt.Update(x[i] + 1, x[i + 1] - 1, x[i], 1, n, 1),
        rt.Update(x[i] + 1, x[i + 1] - 1, x[i + 1], 1, n, 1);
    F(i, 1, m - 1) Update(x[i], x[i + 1]);
    while (q--) {
        int op, x, y; cin >> op >> x >> y;
        if (op == 1) { w[x] = y;
            int l = lt.Query(x, 1, n, 1); 
            int r = rt.Query(x, 1, n, 1);
            rt.Update(l + 1, x, x, 1, n, 1);
            lt.Update(x, r - 1, x, 1, n, 1);
            Update(l, x), Update(x, r);
        } else cout << Query(x, y, 1, n, 1) << "\n";
    }
    return 0;
}
```

---

## 作者：happybob (赞：0)

挺典的题。

考虑添加一个海港的贡献。用 `set` 维护目前的全部海港，显然只有在这个点前驱后继这一段区间会被修改。

注意到修改总是区间加等差数列。询问是区间和。线段树维护差分即可。复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 5e5 + 5, MOD = 1e9 + 7, HSMOD = 1610612741, HSMOD2 = 998244353; // Remember to change

int n, m, q, t, a[N];

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

template<typename T>
class Bit
{
public:
	T lowbit(T x)
	{
		return x & -x;
	}
	T tr[N];
	void add(T x, T y)
	{
		while (x < N)
		{
			tr[x] += y;
			x += lowbit(x);
		}
	}
	T query(T x)
	{
		T sum = 0;
		while (x)
		{
			sum += tr[x];
			x -= lowbit(x);
		}
		return sum;
	}
};

int res[N];

int dcsl(int sx, int mx, int gc)
{
	int xs = (mx - sx) / gc + 1;
	return (sx + mx) * xs / 2ll;
}

class SegmentTree
{
public:
	struct Node
	{
		int l, r, sum, tag, tsum;
		friend Node operator+(const Node& x, const Node& y)
		{
			if(x.l==-1) return y;
			if(y.l==-1) return x;
			Node z;
			z.l=x.l,z.r=y.r;
			z.tag=0;
			z.sum=x.sum+y.sum;
			z.tsum=x.tsum+y.tsum+x.sum*(y.r-y.l+1);
			return z;
		}
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u]=tr[u<<1]+tr[u<<1|1];
	}
	void pushtag(int u,int v)
	{
		tr[u].tag+=v;
		tr[u].sum+=(tr[u].r-tr[u].l+1)*v;
		tr[u].tsum+=v*dcsl(1,tr[u].r-tr[u].l+1,1);
	}
	void pushdown(int u)
	{
		if(tr[u].tag)
		{
			pushtag(u<<1,tr[u].tag);
			pushtag(u<<1|1,tr[u].tag);
			tr[u].tag=0;
		}
	}
	void build(int u, int l, int r, int *a)
	{
		tr[u]={l,r,a[l],0ll,a[l]};
		if(l==r) return;
		int mid=l+r>>1;
		build(u<<1,l,mid,a);
		build(u<<1|1,mid+1,r,a);
		pushup(u);
	}
	void update(int u, int l, int r, int c)
	{
		if(l>r) return;
		if(l>n||r>n||l<1||r<1) return;
		if(tr[u].l>=l and tr[u].r<=r)
		{
			pushtag(u,c);
			return;
		}
		pushdown(u);
		int mid=tr[u].l+tr[u].r>>1;
		if(l<=mid) update(u<<1,l,r,c);
		if(r>mid) update(u<<1|1,l,r,c);
		pushup(u); 
	}
	Node query(int u, int l, int r)
	{
		if(tr[u].l>=l and tr[u].r<=r) return tr[u];
		pushdown(u);
		int mid=tr[u].l+tr[u].r>>1;
		Node res;
		res.l=-1;
		if(l<=mid) res=query(u<<1,l,r);
		if(r>mid) res=res+query(u<<1|1,l,r);
		return res;
	}
}sgt;

set<pair<int, int>> st;
int loc[N], val[N];
bool v[N];
int cf[N];

signed main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++)
	{
		cin>>loc[i];
		v[loc[i]]=1;
	}
	for(int i=1;i<=m;i++) cin>>val[i],st.insert(make_pair(loc[i],val[i]));
	for(int i=1;i<=n;i++)
	{
		if(v[i])
		{
			res[i]=0ll;
			continue;
		}
		auto it=st.lower_bound(make_pair(i,(int)-1e18));
		auto i2=it;
		--i2;
		res[i]=(*i2).second*((*it).first-i);
	}
	for(int i=1;i<=n;i++) 
	{
		cf[i]=res[i]-res[i-1];
	}
	sgt.build(1,1,n,cf);
	while(q--)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int x, v;
			cin>>x>>v;
			auto it=st.lower_bound(make_pair(x,(int)-1e18));
			auto i2=it;
			--i2;
			int l=(*i2).first,r=(*it).first;
			sgt.update(1,l+1,r,(*i2).second);
			sgt.update(1,l+1,l+1,-(*i2).second*(r-l));
			// up ok
			sgt.update(1,l+1,x,-(*i2).second);
			sgt.update(1,l+1,l+1,(x-l)*(((*i2).second)));
			sgt.update(1,x+1,r,-v);
			sgt.update(1,x+1,x+1,(r-(x+1)+1)*v); 
			st.insert(make_pair(x,v));
		}
		else
		{
			int l,r;
			cin>>l>>r;
			cout<<(sgt.query(1,1,r).tsum)-(l==1?0ll:sgt.query(1,1,l-1).tsum)<<"\n";
		}
	}
	return 0;
}

```


---

## 作者：weitianyi (赞：0)

看到这道题，很明显可以先考虑两个海港之间每个位置对应的权值。

考虑两个相邻的海港分别为 $i$ 和 $i+1$，那么在 $\left(X_i + 1, X_{i +1}\right]$ 中的每一个位置 $x$ 对应的权值为 $V_i\times(X_{i+1} - x)$。

将这个式子变形一下，得到 $-V_i\times x + V_i \times X_{i+1}$, 很明显这是一个一次函数，我们用线段树维护每个位置的权值就可以了，具体维护可以参考代码。

另外，每次插入一个新的海港，要求出这个位置左右侧最近的港口，用 `set` 维护一下，`lower_bound` 一下即可。

注意，刚开始 $X_i$ 并不保证从小到大排列，因此不要忘记排序。

AC代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, q;
int x[300005], v[300005];
int d[300005 * 4], tagk[300005 * 4], tagb[300005 * 4];
void maketag(int cur, int l, int r, int k, int b) {
    d[cur] = k * (l + r) * (r - l + 1) / 2 + b * (r - l + 1);
}
void pushdown(int cur, int l, int r) {
    int mid = (l + r) >> 1;
    maketag(cur * 2, l, mid, tagk[cur], tagb[cur]);
    maketag(cur * 2 + 1, mid + 1, r, tagk[cur], tagb[cur]);
    tagk[cur * 2] = tagk[cur * 2 + 1] = tagk[cur];
    tagb[cur * 2] = tagb[cur * 2 + 1] = tagb[cur];
    tagk[cur] = tagb[cur] = 0;
}
void update(int cur, int l, int r, int L, int R, int k, int b) {
    if (L <= l && r <= R) {
        maketag(cur, l, r, k, b);
        tagk[cur] = k, tagb[cur] = b;
        return;
    }
    if (tagk[cur] || tagb[cur]) pushdown(cur, l, r);
    int mid = (l + r) >> 1;
    if (L <= mid) update(cur * 2, l, mid, L, R, k, b);
    if (R > mid) update(cur * 2 + 1, mid + 1, r, L, R, k, b);
    d[cur] = d[cur * 2] + d[cur * 2 + 1];
}
int query(int cur, int l, int r, int L, int R) {
    if (L <= l && r <= R) return d[cur];
    if (tagk[cur] || tagb[cur]) pushdown(cur, l, r);
    int mid = (l + r) >> 1;
    int ans = 0;
    if (L <= mid) ans += query(cur * 2, l, mid, L, R);
    if (R > mid) ans += query(cur * 2 + 1, mid + 1, r, L, R);
    return ans;
}
set<int> st;
int val[300005];
pair<int, int> tmp[300005];
signed main() {
    ios :: sync_with_stdio(false);
    cin >> n >> m >> q;
    
    for(int i = 1; i <= m; i++) cin >> tmp[i].first;
    for (int i = 1; i <= m; i++) cin >> tmp[i].second;
    sort(tmp + 1, tmp + m + 1);
    for (int i = 1; i <= m; i++) {
        x[i] = tmp[i].first;
        v[i] = tmp[i].second;
    }
    for (int i = 1; i <= m; i++) {
        st.insert(x[i]);
        val[x[i]] = v[i];
    }
    for (int i = 2; i <= m; i++) update(1, 1, n, x[i - 1] + 1, x[i], -v[i - 1], x[i] * v[i - 1]);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int pos, v;
            cin >> pos >> v;
            auto it = st.lower_bound(pos);
            val[pos] = v;
            update(1, 1, n, pos + 1, *it, -val[pos], val[pos] * (*it));
            it--;
            update(1, 1, n, (*it) + 1, pos, -val[*it], val[*it] * pos);
            st.insert(pos);
        } else if (op == 2) {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << endl;
        }
    }
    return 0;
}
```

---

