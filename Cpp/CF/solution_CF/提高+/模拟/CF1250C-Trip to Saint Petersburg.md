# Trip to Saint Petersburg

## 题目描述

您正在准备一次去圣彼得堡的旅行！您估计了一下自己每天必然要花费 $k$ 元食宿费。

但您可以在圣彼得堡打工！那里共有 $n$ 份工作，每份工作从 $l_i$ 天开始到 $r_i$ 天结束，可获得报酬 $p_i$ 元，**迟到或早退**是不会有报酬的。因为您很强，所以一天之内您可以参加任意多的工作。注意：您在到达或返程的那天依然可以工作。

形式化地来说，您需要确定四项东西：$p$ 最大获利，$L,R$ 您旅行的到达和返程时间，$S$，一个集合，表示您参与的所有工作，必须满足：

- $R \ge L$
- 对于任意 $s \in S$ 有 $L\le l_s \le r_s \le R$
- $p=\sum\limits_{s\in S}p_s -k(R-L+1)$

## 样例 #1

### 输入

```
4 5
1 1 3
3 3 11
5 5 17
7 7 4
```

### 输出

```
13 3 5 2
3 2 
```

## 样例 #2

### 输入

```
1 3
1 2 5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 8
1 5 16
2 4 9
3 3 24
1 5 13
```

### 输出

```
22 1 5 4
3 2 1 4 
```

# 题解

## 作者：Soulist (赞：2)

~~最近CF上的评分越来越迷了...~~

假设去往时间为$[L,R]$，由于任意工作的工资均$>0$，所以我们选走的工作必然是所有满足$L\le l_i\le r_i\le R$的工作

于是我们可以考虑枚举$R$，然后对于$R$求解最优的$L$

类似于扫描线从$1\to R$扫过去，每次依次加入一条线段，考虑一条线段$[l_i,r_i]$可以贡献的$L$有那些，显然是$[1,L]$这段区间内的所有$L$，于是我们只需要支持区间修改即可。

然后再做一个区间查值就好了...

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define ls(x) ( x << 1 )
#define rs(x) ( x << 1 | 1 )
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 2e5 + 5 ; 
int n, m, Maxn, L, num, Ans, AL, AR, s[N], top ; 
struct node {
	int l, w, id ; 
} ;
struct Tree {
	int mx, tag, id ; 
} tr[N << 2] ;
vector<node> a[N] ; 
void pushmark( int x ) {
	if( tr[x].tag ) {
		tr[ls(x)].mx += tr[x].tag, tr[ls(x)].tag += tr[x].tag,
		tr[rs(x)].mx += tr[x].tag, tr[rs(x)].tag += tr[x].tag,
		tr[x].tag = 0 ;
	}
}
void Q( int x, int l, int r, int ql, int qr ) {
	if( qr < l || r < ql ) return ; 
	if( ql <= l && r <= qr ) { if( tr[x].mx > num ) L = tr[x].id, num = tr[x].mx ; return ; }
	int mid = ( l + r ) >> 1 ; pushmark(x) ; 
	Q( ls(x), l, mid, ql, qr ), Q( rs(x), mid + 1, r, ql, qr ) ;
	tr[x].mx = tr[ls(x)].mx, tr[x].id = tr[ls(x)].id ; 
	if( tr[rs(x)].mx > tr[x].mx ) tr[x].mx = tr[rs(x)].mx, tr[x].id = tr[rs(x)].id ; 
}
void Add( int x, int l, int r, int ql, int qr, int k ) {
	if( qr < l || r < ql ) return ; 
	if( ql <= l && r <= qr ) { tr[x].mx += k ; tr[x].tag += k; return ; }
	int mid = ( l + r ) >> 1 ; pushmark(x) ;
	Add( ls(x), l, mid, ql, qr, k ), Add( rs(x), mid + 1, r, ql, qr, k ) ;
	tr[x].mx = tr[ls(x)].mx, tr[x].id = tr[ls(x)].id ; 
	if( tr[rs(x)].mx > tr[x].mx ) tr[x].mx = tr[rs(x)].mx, tr[x].id = tr[rs(x)].id ; 
}
void build( int x, int l, int r ) {
	tr[x].id = l ; if( l == r ) return ; 
	int mid = ( l + r ) >> 1 ; 
	build( ls(x), l, mid ), build( rs(x), mid + 1, r ) ;
}
signed main()
{
	n = gi(), m = gi() ; int x, y, z ;
	rep( i, 1, n ) {
		x = gi(), y = gi(), z = gi(), Maxn = max( Maxn, y ),
		a[y].push_back((node){ x, z, i }) ;
	}  build( 1, 1, Maxn ) ; 
	rep( i, 1, Maxn ) {
		Add( 1, 1, Maxn, 1, i, -m ) ;
		for( re int j = 0; j < a[i].size(); ++ j ) {
			Add( 1, 1, Maxn, 1, a[i][j].l, a[i][j].w ) ;
		}
		num = 0, L = 0, Q( 1, 1, Maxn, 1, i ) ;
		if( num > Ans ) Ans = num, AL = L, AR = i ; 
	}
	if( Ans == 0 ) { puts("0") ; exit(0) ; }
	printf("%lld %lld %lld ", Ans, AL, AR ) ;
	rep( i, 1, AR )
		for( re int j = 0; j < a[i].size(); ++ j )
		if( a[i][j].l >= AL ) s[++ top] = a[i][j].id ; 
	printf("%lld\n", top ) ;
	rep( i, 1, top ) printf("%lld ", s[i] ) ;
	return 0 ;
}
```

---

## 作者：Miracle_1024 (赞：0)

### 思路：
由于奖励区间的范围比较小，所以很容易想到，枚举右端点 $r$，找到左端点 $l$，维护奖励值。从左到右，每读入一个点，首先将 $[1 , r ]$ 区间都 $-k$。然后再判断是否 $r$ 是一个奖励区间的右端点。如果有新加的奖励区间，则所有 $i<l$ 处的区间都 $+val$ ，表示前面的去缉拿都可以获得这个奖励值。然后区间查询最值就好了。

### 代码：
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> pi;
typedef tuple<ll,int,int> tp;
const int maxn=2e5+5;
int n;
ll k;

pi v[maxn<<2];
ll tag[maxn<<2];
void push_down(int x){
	if(tag[x]){
		tag[x<<1]+=tag[x]; tag[x<<1|1]+=tag[x];
		v[x<<1].first+=tag[x]; v[x<<1|1].first+=tag[x];
		tag[x]=0;	
	}
}
void build(int x,int l,int r){
	if(l==r){
		v[x]=make_pair(0LL,l);
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid); build(x<<1|1,mid+1,r);
	v[x]=max(v[x<<1],v[x<<1|1]);
}
void update(int x,int l,int r,int L,int R,ll val){
	if(l==L && r==R){
		tag[x]+=val;
		v[x].first+=val;
		return;
	}
	push_down(x);
	int mid=(l+r)>>1;
	if(R<=mid)update(x<<1,l,mid,L,R,val);
	else if(L>mid)update(x<<1|1,mid+1,r,L,R,val);
	else{
		update(x<<1,l,mid,L,mid,val);	
		update(x<<1|1,mid+1,r,mid+1,R,val);
	}
	v[x]=max(v[x<<1],v[x<<1|1]);
}
pi query(int x,int l,int r,int L,int R){
	if(l==L && r==R)return v[x];
	push_down(x);
	int mid=(l+r)>>1;
	if(R<=mid)return query(x<<1,l,mid,L,R);
	else if(L>mid)return query(x<<1|1,mid+1,r,L,R);
	return max(query(x<<1,l,mid,L,mid),query(x<<1|1,mid+1,r,mid+1,R));	
}

vector<tp>q[maxn];
vector<int>ans;
int main()
{
	scanf("%d %lld",&n,&k);
	int l,r; ll p;
	build(1,1,2e5);
	for(int i=1;i<=n;i++){
		scanf("%d %d %lld",&l,&r,&p);
		q[r].push_back(make_tuple(p,l,i));
	}
	p=0;int L,R;
	for(int i=1;i<=2e5;i++){
		update(1,1,2e5,1,i,-k);
		for(tp P:q[i])update(1,1,2e5,1,get<1>(P),get<0>(P));
		if(v[1].first>p){
			p=v[1].first; L=v[1].second; R=i;
		}
	}
	if(p<=0)printf("0\n");
	else{
		for(int i=L;i<=R;i++){
			for(tp P:q[i])if(get<1>(P)>=L)ans.push_back(get<2>(P));
		}
		printf("%lld %d %d %d\n",p,L,R,(int)ans.size());
		for(int id:ans)printf("%d ",id);
	}
	return 0;	
}
```


---

## 作者：Tx_Lcy (赞：0)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16809263.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1250C)
## 思路
线段树入门题。

不妨固定一个右端点 $r$，把所有右端点小于 $r$ 的区间都在 $1$ 至此区间的左端点处 $\verb!update!$ 一个 $p$，然后每次都给区间 $1$ 至 $i$ $\verb!update!$ 一个 $-k$，最后查询区间 $\max$ 即可。

## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e5+10;
struct answ{int first,second,id;};
struct node{int x,y;};
vector<answ>a[N];
vector<int>anss;
struct Segment_Tree{
    #define ls (x<<1)
    #define rs (x<<1|1)
    #define mid ((l+r)>>1)
    int c[N<<2],lazy[N<<2],pl[N<<2];
    inline void build(int x,int l,int r){
        if (l==r){pl[x]=l;return;}
        build(ls,l,mid);build(rs,mid+1,r);
        pl[x]=pl[ls];
    }
    inline void pushdown(int x){
        c[ls]+=lazy[x];c[rs]+=lazy[x];
        lazy[ls]+=lazy[x];lazy[rs]+=lazy[x];
        lazy[x]=0;
    }
    inline void pushup(int x){
        if (c[ls]>c[rs]) c[x]=c[ls],pl[x]=pl[ls];
        else c[x]=c[rs],pl[x]=pl[rs];
    }
    inline void update(int x,int l,int r,int ll,int rr,int v){
        if (l==r){pl[x]=l;}
        if (ll<=l && r<=rr){c[x]+=v,lazy[x]+=v;return;}
        pushdown(x);
        if (ll<=mid) update(ls,l,mid,ll,rr,v);
        if (mid<rr) update(rs,mid+1,r,ll,rr,v);
        pushup(x);
    }
    inline node query(int x,int l,int r,int ll,int rr){
        if (l==r) pl[x]=l;
        if (ll<=l && r<=rr) return {c[x],pl[x]};
        pushdown(x);node res;res.x=res.y=0;
        if (ll<=mid) res=query(ls,l,mid,ll,rr);
        if (mid<rr){
            node qq=query(rs,mid+1,r,ll,rr);
            if (qq.x>res.x) res=qq;
        }
        pushup(x);
        return res;
    }
}T;
signed main(){
    int n,k;cin>>n>>k;int maxr=0;
    for (int i=1;i<=n;++i){
        int l,r,p;cin>>l>>r>>p;
        a[r].push_back({l,p,i});maxr=max(maxr,r);
    }
    T.build(1,1,maxr);
    int ans=0,ansl=0,ansr=0;
    for (int i=1;i<=maxr;++i){
        T.update(1,1,maxr,1,i,-k);
        for (auto j:a[i]) T.update(1,1,maxr,1,j.first,j.second);
        node reply=T.query(1,1,maxr,1,i);
        if (reply.x>ans) ans=reply.x,ansl=reply.y,ansr=i;
    }
    //输出
    return 0;
}
```


---

