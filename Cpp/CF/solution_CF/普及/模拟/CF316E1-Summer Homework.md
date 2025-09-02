# Summer Homework

## 题目描述

By the age of three Smart Beaver mastered all arithmetic operations and got this summer homework from the amazed teacher:

You are given a sequence of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to perform on it $ m $ consecutive operations of the following type:

1. For given numbers $ x_{i} $ and $ v_{i} $ assign value $ v_{i} $ to element $ a_{xi} $ .
2. For given numbers $ l_{i} $ and $ r_{i} $ you've got to calculate sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316E1/095e734be6677a366eba0d190d121c644f5bca60.png), where $ f_{0}=f_{1}=1 $ and at $ i>=2 $ : $ f_{i}=f_{i-1}+f_{i-2} $ .
3. For a group of three numbers $ l_{i} $ $ r_{i} $ $ d_{i} $ you should increase value $ a_{x} $ by $ d_{i} $ for all $ x $ $ (l_{i}<=x<=r_{i}) $ .

Smart Beaver planned a tour around great Canadian lakes, so he asked you to help him solve the given problem.

## 样例 #1

### 输入

```
5 5
1 3 1 2 4
2 1 4
2 1 5
2 2 4
1 3 10
2 1 5
```

### 输出

```
12
32
8
50
```

## 样例 #2

### 输入

```
5 4
1 3 1 2 4
3 1 4 1
2 2 4
1 2 10
2 1 5
```

### 输出

```
12
45
```

# 题解

## 作者：SSqwq_ (赞：3)

## 题意

三种操作：

- 单点修改

- 区间加

- 求 $\sum\limits_{i=0}^{r-l}f_i\times a_{l+i}$，其中 $f_i$ 表示斐波那契数列的第 $i$ 位。

## 分析

注意到本题 $n\leq 100$，$m\leq 10000$，直接模拟即可。

时间复杂度 $O(nm)$，足以通过本题。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=1000000000;
int f[200001],a[200001];
int n,q,op,l,r,d;
signed main(){
//	freopen("data.in"."r",stdin);
//	freopen("data.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	f[0]=1,f[1]=1;
	for(int i=2;i<=n;++i){
		f[i]=f[i-1]+f[i-2];
		if(f[i]>=p)f[i]-=p;
	}
	while(q--){
		cin>>op>>l>>r;
		if(op==1){
			a[l]=r;
		}
		if(op==2){
			int ans=0;
			for(int i=0;i<=r-l;++i){
				ans+=f[i]*a[l+i];
				ans%=p;
			}
			cout<<ans<<"\n";
		}
		if(op==3){
			cin>>d;
			for(int i=l;i<=r;++i){
				a[i]+=d;
			}
		}
	} 
	return 0;
}

```

---

## 作者：wangzhuoyue2021 (赞：1)

### 推导公式
线段树每一个节点当中维护的是s0、s1，用于后续的公式推导！其中f为斐波那契数列；其中l-r为线段树每段所维护的左右区间！
```
s[0] = a[l]*f[0] + a[l+1]*f[1] + a[l+2]*f[2] + ... + a[r]*f[r-l];
s[1] = a[l]*f[1] + a[l+1]*f[2] + a[l+2]*f[3] + ... + a[r]*f[r-l+1];
s[2] = a[l]*f[2] + a[l+1]*f[3] + a[l+2]*f[4] + ... + a[r]*f[r-l+2];
s[3] = a[l]*f[3] + a[l+1]*f[4] + a[l+2]*f[5] + ... + a[r]*f[r-l+3];
...
s[x] = a[l]*f[x] + a[l+1]*f[x+1] + a[l+2]*f[x+2] + ... + a[r]*f[r-l+x];
```
由上述公式可以推导得到：
```
s[2] = s[1]+s[0], s[3] = s[2]+s[1] = 2*s[1]+s[0], s[4] = s[3]+s[2] = 3*s[1]+2*s[0];
```
由斐波那契数列性质以及以上推导得到：
```
s[x] = f[x-1]*s[1] + f[x-2]*s[0]; 
```
维护线段树当中的每一段的s0、s1;

### 两段合并：

因为左子树段下标始终在右子树段前面，所以合并时左段的子树 (s[0] + 右段对应的s[x],左子树段有多少个值，右子树段就从值的个数开始!)
例如左段有k个值那么右段合并时，右段值就为s[k],即需要满足第二个条件；
对于第三个条件就是用懒标记，推导公式：

带入s[0] 得到 
```
ans = (a[l]+d)*f[0] + (a[l+1]+d)*f[1] + (a[l+2]+d)*f[2] + ... + (a[r]+d)*f[r-l];
```
化简得到 
```
ans = a[l]*f[0] + a[l+1]*f[1] + a[l+2]*f[2] + ... + a[r]*f[r-l] +   d(f[0]+f[1]+f[2]..+f[r-l]) = s[0] + d(f[0]+f[1]+f[2]..+f[r-l]);
```
所以修改线段树每一段保留值：
```
s[0] = s[0] + d(f[0]+f[1]+f[2]..+f[r-l]); 
s[1] = s[1] + d(f[1]+f[2]+f[3]..+f[r-l+1]);  s[1]同理 
```

---

## 作者：Regimes (赞：1)

题目翻译：

有$n$个数，支持$m$次操作。

$1$ $x$ $y$ 将第$x$个数修改为$y$

$2$ $l$ $r$ 对这个区间求出$\sum_{i=0}^{r-l}f_{i}a_{i+l}$的和

$3$ $l$ $r$ $d$ 给区间的每个$a_i$加上一个$d$

其中$f_i$是斐波拉契数列。这里$f_0=1,f_1=1$

$1<=n,m<=200000$


-----

----
----


我们首先要知道一个知识：

$f_n= f_{n-m}f_{m+1}+f_{n-m-1}f_m$

但是在这个地方我们要注意，他的$f_0=1$，在一般的上述式子只可以用于

$f_0=0,f_1=1$

其实也就是往后推一项

所以这里$f_{n-1}=f_{n-m-1}f_{m}+f_{n-m-2}f_{m-1}$

这里对于一个$f_n=f_{n-m}f_m+f_{n-m-1}f_{m-1}$

我们考虑线段树每个节点记录

$$Sum1=\sum_{x=0}^{r-l}f_xa_{l+x}$$

$$Sum2=\sum_{x=0}^{r-l}f_{x+1}a_{l+x}$$

于是考虑合并，

$$Sum1[x]=Sum1[lson]+f_{size[lson]-1}Sum2[rson]+f_{size[lson]-2}Sum1[rson]$$

$$Sum2[x]=Sum2[lson]+f_{size[lson]}Sum2[rson]+f_{size[lson]-1}Sum1[rson]$$

```cpp
#include<bits/stdc++.h>

using namespace std ;

#define ls (x<<1)
#define rs (x<<1|1)
#define N 300000
#define Mod 1000000000

int n , m ;
int f[N] , sum[N] , a[N] , lazy[4*N] ;

struct node{
    int Sum1 , Sum2 , siz ;
}W[4*N];

node operator + (node a , node b){
    node c ;
    c.Sum1 = ( a.Sum1 + 1ll * f[a.siz - 1] * b.Sum2 % Mod + 1ll * (a.siz >= 2 ) * f[max( a.siz - 2 , 0 )] * b.Sum1 % Mod ) % Mod ;
    c.Sum2 = ( a.Sum2 + 1ll * f[a.siz] * b.Sum2 % Mod + 1ll * f[a.siz - 1] * b.Sum1 % Mod ) % Mod ;
    c.siz = a.siz + b.siz ;
    return c ;
}

void Init(){
    f[0] = 1 , f[1] = 1 ; sum[0] = 1 ;
    for(int i = 2 ; i <= N - 5 ; i++ ) f[i] = ( f[i - 1] + f[i - 2] ) % Mod ;
    for(int i = 1 ; i <= N - 5 ; i++ ) sum[i] = ( sum[i - 1] + f[i] ) % Mod ;
    return ;
}

void pushdown(int x){
    if( lazy[x] ){
        lazy[ls] = ( lazy[ls] + lazy[x] ) % Mod ;
        lazy[rs] = ( lazy[rs] + lazy[x] ) % Mod ;
        if( W[ls].siz ) W[ls].Sum1 = ( W[ls].Sum1 + 1ll * lazy[x] * ( sum[W[ls].siz - 1] ) % Mod ) % Mod ;
        W[ls].Sum2 = ( W[ls].Sum2 + 1ll * lazy[x] * ( sum[W[ls].siz] - sum[0] ) % Mod ) % Mod ;
        if( W[rs].siz ) W[rs].Sum1 = ( W[rs].Sum1 + 1ll * lazy[x] * ( sum[W[rs].siz - 1] ) % Mod ) % Mod ;
        W[rs].Sum2 = ( W[rs].Sum2 + 1ll * lazy[x] * ( sum[W[rs].siz] - sum[0] ) % Mod ) % Mod ;
        lazy[x] = 0 ;
        return ;
    }
}

void build(int x , int l , int r ){
    W[x].siz = ( r - l + 1 ) ;
    if( l == r ){
        W[x].Sum1 = a[l] * f[0] % Mod ;
        W[x].Sum2 = a[l] * f[1] % Mod ;
        return ;
    }
    int mid = ( l + r ) >> 1 ;
    build( ls , l , mid ) ; build( rs , mid + 1 , r ) ;
    W[x] = W[ls] + W[rs] ;
    return ;
}

void update(int x , int l , int r , int pos , int k ){
    if( l == r ){
        W[x].Sum1 = k * f[0] % Mod ;
        W[x].Sum2 = k * f[1] % Mod ;
        return ;
    }
    pushdown( x ) ;
    int mid = ( l + r ) >> 1 ;
    if( pos <= mid ) update( ls , l , mid , pos , k ) ;
    else update( rs , mid + 1 , r , pos , k ) ;
    W[x] = W[ls] + W[rs] ;
    return ;
}

void modify(int x , int l , int r , int ll , int rr , int k ){
    if( l == ll && r == rr ){
        lazy[x] = ( lazy[x] + k ) % Mod ;
        W[x].Sum1 = ( W[x].Sum1 + lazy[x] * ( sum[W[x].siz - 1] ) % Mod ) % Mod ;
        W[x].Sum2 = ( W[x].Sum2 + lazy[x] * ( sum[W[x].siz] - sum[0] ) % Mod ) % Mod ;
        return ;
    }
    pushdown( x ) ;
    int mid = ( l + r ) >> 1 ;
    if( rr <= mid ) modify( ls , l , mid , ll , rr , k ) ;
    else if( ll > mid ) modify( rs , mid + 1 , r , ll , rr , k ) ;
    else modify( ls , l , mid , ll , mid , k ) , modify( rs , mid + 1 , r , mid + 1 , rr , k ) ;
    W[x] = W[ls] + W[rs] ;
}

node query(int x , int l , int r , int ll , int rr ){
    if( l == ll && r == rr ) return W[x] ;
    pushdown( x ) ;
    int mid = ( l + r ) >> 1 ;
    if( rr <= mid ) return query( ls , l , mid , ll , rr ) ;
    else if( ll > mid ) return query( rs , mid + 1 , r , ll , rr ) ;
    else return query( ls , l , mid , ll , mid ) + query( rs , mid + 1 , r , mid + 1 , rr ) ;
}

int main()
{
    scanf("%d%d" , &n , &m ) ;

    Init() ;
    for(int i = 1 ; i <= n ; i++ ) scanf("%d" , &a[i] ) ;
    build( 1 , 1 , n ) ;
    for(int i = 1 ; i <= m ; i++ ){
        int op , l , r , d ;
        scanf("%d%d%d" , &op , &l , &r ) ;
        if( op == 1 ) update( 1 , 1 , n , l , r ) ;
        if( op == 2 ) printf("%d\n" , query( 1 , 1 , n , l , r ).Sum1 % Mod ) ;
        if( op == 3 ){
            scanf("%d" , &d ) ;
            modify( 1 , 1 , n , l , r , d ) ;
        }
    }
    return 0 ;
}
```


---

## 作者：liujiaxi123456 (赞：0)

#### 思路：
区修区查，考虑线段树，先不考虑修改，考虑查询。

发现 pushup 时左儿子的答案可以直接继承。

但右儿子的系数不对，考虑推式子：
- 应该的答案：$\sum_{i=mid+1}^{r} = f_{i-l}\cdot a_i$

有边界不好推式子，考虑先退去掉边界的情况：
- 设 $g_i = \sum_{j=0}^{n-1}f_{i+j}\cdot a_{j+1}$
- 则有 $g_{i-1}+g_{i-2}=\sum_{j=0}^{n-1}(f_{i+j-1}+f_{i+j-2})\cdot a_{j+1} = \sum_{j=0}^{n-1}f_{i+j}\cdot a_{j+1} = g_i$
- $g_i = g_{i-1}+g_{i-2}=2g_{i-2}+g_{i-3}=3g_{i-3}+2g_{i-4}=\cdots=f_{i-j}\cdot g_{j}+f_{i-j-1}\cdot g_{j-1}=f_{i-1}\cdot g_1+f_{i-2}\cdot g_0$

考虑把式子带入线段树中维护：
- 相当于对线段树上的每个节点维护它的 $g_0,g_1$。
- pushup 时：
  + $g_{0, t} = g_{0, ls} + g_{mid-l+1, rs}$
  + $g_{1, t} = g_{1, ls} + g_{mid-l+2, res}$

现在考虑区间加：
- 写式子，设区间加 $d$：
  + $ \Delta_{g_0} = f_0\cdot d + f_1\cdot d + \cdots + f_{r-l}\cdot d = sumf_{r-l}\cdot d $
  + $\Delta_{g_1} = f_1\cdot d + f_2\cdot d + \cdots + f_{r-l+1}\cdot d = (sumf_{r-l+1}-f_0)\cdot d$
- 预处理 $f$ 的前缀和即可。
#### Code：
~~这是一个比次优解快了近两倍的代码。~~
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 2e5+5, MOD = 1e9;
int N;

class SegmentTree {
private:
	ll f[Maxn], sumf[Maxn];
	struct Segment { int tag; ll g0, g1; } seg[Maxn*4];
	inline int calc(int t, int k) {
		return (!k ?seg[t].g0 :(k==1 ?seg[t].g1 :(f[k-1]*seg[t].g1 + f[k-2]*seg[t].g0)%MOD));
	}
	inline void pushup(int t, int llen) {
		seg[t].g0 = (seg[t<<1].g0 + calc(t<<1|1, llen)) %MOD;
		seg[t].g1 = (seg[t<<1].g1 + calc(t<<1|1, llen+1)) %MOD;
	}
	inline void Add(int t, int len, int d) {
		seg[t].tag = (seg[t].tag + d) %MOD;
		seg[t].g0 = (seg[t].g0 + sumf[len-1]*d) %MOD;
		seg[t].g1 = (seg[t].g1 + sumf[len]*d-d) %MOD; // 差分掉 f[0]
	}
	inline void pushdown(int t, int l, int r) {
		if(seg[t].tag) {
			int mid = (l+r)>>1;
			Add(t<<1, mid-l+1, seg[t].tag);
			Add(t<<1|1, r-mid, seg[t].tag);
			seg[t].tag = 0;
		}
	}
	inline void Change(int t, int l, int r, int pos, int k) {
		if(l == r)	return seg[t].g0 = seg[t].g1 = k, void();
		int mid = (l+r)>>1; pushdown(t, l, r);
		if(pos <= mid)	Change(t<<1, l, mid, pos, k);
		else	Change(t<<1|1, mid+1, r, pos, k);
		pushup(t, mid-l+1);
	}
	inline ll Query(int t, int l, int r, int L, int R) {
		if(r<L || R<l)	return 0;
		if(L<=l && r<=R)	return calc(t, l-L);
		int mid = (l+r)>>1; pushdown(t, l, r);
		return Query(t<<1, l, mid, L, R) + Query(t<<1|1, mid+1, r, L, R);
	} 
	inline void Modify(int t, int l, int r, int L, int R, int d) {
		if(r<L || R<l)	return ;
		if(L<=l && r<=R)	return Add(t, r-l+1, d);
		int mid = (l+r)>>1; pushdown(t, l, r);
		Modify(t<<1, l, mid, L, R, d), Modify(t<<1|1, mid+1, r, L, R, d);
		pushup(t, mid-l+1);
	}
	inline void Build(int t, int l, int r, int *a) {
		if(l == r)	return seg[t].g0 = seg[t].g1 = a[l], void();
		int mid = (l+r)>>1; 
		Build(t<<1, l, mid, a), Build(t<<1|1, mid+1, r, a);
		pushup(t, mid-l+1);
	}
public:
	inline void init(int *a, int N) {
		f[0] = f[1] = 1, sumf[0] = 1, sumf[1] = 2;
		for(int i=2; i<=N; i++) {
			f[i] = (f[i-1] + f[i-2]) %MOD;
			sumf[i] = (sumf[i-1] + f[i]) %MOD;
		}
		Build(1, 1, N, a);
	}
	inline void Change(int pos, int y) { Change(1, 1, N, pos, y); }
	inline int Query(int l, int r) { return Query(1, 1, N, l, r) %MOD; }
	inline void Modify(int l, int r, int d) { Modify(1, 1, N, l, r, d); }
} seg;

namespace Josh_zmf {
	
	int Q, a[Maxn];

	inline int main() {
		cin>> N>> Q;
		for(int i=1; i<=N; i++)	cin>> a[i];
		seg.init(a, N);
		for(int opt, l, r, x, y; Q--; ) {
			cin>> opt;
			if(opt == 1) {
				cin>> x>> y;
				seg.Change(x, y);
			} else if(opt == 2) {
				cin>> l>> r;
				cout<< seg.Query(l, r)<< '\n';
			} else {
				cin>> l>> r>> x;
				seg.Modify(l, r, x);
			}
		}
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```

---

