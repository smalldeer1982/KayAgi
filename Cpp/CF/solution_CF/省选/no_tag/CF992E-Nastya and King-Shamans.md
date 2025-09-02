# Nastya and King-Shamans

## 题目描述

Nastya likes reading and even spends whole days in a library sometimes. Today she found a chronicle of Byteland in the library, and it stated that there lived shamans long time ago. It is known that at every moment there was exactly one shaman in Byteland, and there were $ n $ shamans in total enumerated with integers from $ 1 $ to $ n $ in the order they lived. Also, each shaman had a magic power which can now be expressed as an integer.

The chronicle includes a list of powers of the $ n $ shamans. Also, some shamans can be king-shamans, if they gathered all the power of their predecessors, i.e. their power is exactly the sum of powers of all previous shamans. Nastya is interested in whether there was at least one king-shaman in Byteland.

Unfortunately many of the powers are unreadable in the list, so Nastya is doing the following:

- Initially she supposes some power for each shaman.
- After that she changes the power of some shaman $ q $ times (the shamans can differ) and after that wants to check if there is at least one king-shaman in the list. If yes, she wants to know the index of any king-shaman.

Unfortunately the list is too large and Nastya wants you to help her.

## 说明/提示

In the first example powers of shamans after the first change are equal to $ (2,3) $ . The answer equals $ -1 $ , because the sum of powers of shamans before the first shaman is equal to $ 0 $ , and before the second is equal to $ 2 $ .

In the second example after the first change the powers are equal to $ (1,2,3) $ . The answer is equal to $ 3 $ , because the power of the third shaman is equal to $ 3 $ , and the sum of powers of the first and the second shaman is also $ 1+2=3 $ . After the second change the powers become equal to $ (2,2,3) $ , where the answer equals $ 2 $ . After the third change the powers become equal to $ (2,4,3) $ , where the answer equals $ -1 $ . After the fourth change the powers become equal to $ (2,4,6) $ , where the answer equals $ 3 $ .

## 样例 #1

### 输入

```
2 1
1 3
1 2
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
3 4
2 2 3
1 1
1 2
2 4
3 6
```

### 输出

```
3
2
-1
3
```

## 样例 #3

### 输入

```
10 7
0 3 1 4 6 2 7 8 10 1
2 5
1 3
9 36
4 10
4 9
1 2
1 0
```

### 输出

```
1
-1
9
-1
4
-1
1
```

# 题解

## 作者：MeowScore (赞：21)

[传送门 qwq](https://www.luogu.com.cn/problem/CF992E)

线段树题解。

思路还算可以，重要之处在于意识到一种看似暴力的做法由于某些性质而变得正确。

首先想最原始的暴力。直接维护原数组 $a$ 和前缀数组 $s$，每次修改的时候就暴力在 $a$ 的一个单点和 $s$ 的一个区间上改值。查询的时候暴力枚举所有的 $i$，判断 $a_i-s_{i-1}$ 是否为 $0$。

先考虑这样一件事：对于所有的 $i$，满足条件的一定不超过 $log s_n$ 个。为什么呢？若 $i$ 满足条件，即 $a_i-s_{i-1}\ge0$，可得 $s_i>=2s_{i-1}$。也就是说，每有一个 $i$ 满足条件，$s$ 值就会翻倍，那么总共的满足条件的 $i$ 的个数不超过 $log s_n$。先记住这条性质，后面会用。

考虑优化。由于涉及到大量区间的操作，我们不妨建立线段树维护 $a_i-s_{i-1}$ 的区间 $max$。为什么这么做？因为查询的时候我们只需要递归区间 $max$ 大于等于 $0$ 的区间，结合上面说的性质，我们一共找的的叶子总数不会超过 $log s_n$，复杂度正确。

再想如何进行修改操作。我们假设把 $a_x$ 增加了 $y$（注意题目说的是修改，这里说的是增加），首先 $x$ 位置单点加 $y$ 不必多说。再考虑哪些 $s$ 值受到了影响：应该是区间 $[x+1,n]$。又因为 $a_i-s_{i-1}$ 的 $s$ 前面带个减号，我们对区间 $[x+1,n]$ 进行区间加 $-y$。（注意 $x=n$ 造成越界）。

敲完题解了 rmj 还处于爆炸状态，但是在 CF 上已经通过，代码可以保证正确。

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int read(){
	int ss=0,ww=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			ww=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ss=ss*10+ch-'0';
		ch=getchar();
	}
	return ss*ww;
}
const int N=200010;
int a[N],s[N];
struct ST{
	int tag;
	int maxx;
}st[N*4];
void update(int root,int l,int r){
	st[root].maxx=max(st[root*2].maxx,st[root*2+1].maxx);
}
void push_down(int root,int l,int r){
	int k=st[root].tag;
	st[root].tag=0;
	int mid=(l+r)/2;
	st[root*2].tag+=k;
	st[root*2+1].tag+=k;
	st[root*2].maxx+=k;
	st[root*2+1].maxx+=k;
}
void build(int root,int l,int r){
	if(l==r){
		st[root].maxx=a[l]-s[l-1];
		return;
	}
	int mid=(l+r)/2;
	build(root*2,l,mid);
	build(root*2+1,mid+1,r);
	update(root,l,r);
}
void add(int root,int l,int r,int x,int y,int k){
	if(l>=x&&r<=y){
		st[root].maxx+=k;
		st[root].tag+=k;
		return;
	}
	int mid=(l+r)/2;
	if(st[root].tag)
		push_down(root,l,r);
	if(mid>=x)
		add(root*2,l,mid,x,y,k);
	if(mid+1<=y)
		add(root*2+1,mid+1,r,x,y,k);
	update(root,l,r);
}
int res;
void ask(int root,int l,int r){
	if(res!=-1)
		return;
	if(l==r){
		if(st[root].maxx==0)
			res=l;
		return;
	}
	int mid=(l+r)/2;
	if(st[root].tag)
		push_down(root,l,r);
	if(st[root*2].maxx>=0)
		ask(root*2,l,mid);
	if(st[root*2+1].maxx>=0)
		ask(root*2+1,mid+1,r);
}
signed main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		s[i]=a[i]+s[i-1];
	}
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int x,k;
		x=read();
		k=read();
		int y=k-a[x];
		a[x]=k;
		add(1,1,n,x,x,y);
		if(x!=n)
			add(1,1,n,x+1,n,-y);
		res=-1;
		ask(1,1,n);
		printf("%lld\n",res);
	}
	return 0;
}
```

---

## 作者：Piwry (赞：15)

## 解析

### 解法一

题意即让我们求 $a_i=s_{i-1}$ 的位置，其中 $s_i$ 表示前缀和

仅考虑**非零**位置，不难发现这样的位置不会超过 $\log a$ 个；因为若有一处满足要求的 $a_i$，那么 $s_i$ 相比 $s_{i-1}$ 必定翻倍

这里讲一种线段树的实现方式：

具体来说，维护区间最大的 $a_i-s_{i-1}$。查询时开始先和普通线段树一样 “切分” 区间；直到查询的区间和当前线段树结点管辖的区间一致时，直接暴力递归 $a_i-s_{i-1}\geq 0$ 的左右子树；一次查询的复杂度 $\Theta(\log n\log a)$。修改时就相当于区间修改

至于为零的位置的贡献，我们可以选择在 pushup 时忽略

接着考虑为零的位置什么时候能产生贡献。可以发现 $a_i=0$ 能成为答案当且仅当 $a_k=0, 0\leq k<i$。发现若零的位置能产生贡献，那么 $a_0$ 也一定能产生贡献；于是我们直接检查 $a_0$ 是否为 $0$ 即可

### 解法二

（即社论 $\texttt{Solution III}$）

考虑按每个数的最高二进制位对数字分组，共分成 $\log a$ 份，并且每组内按原序列的下标顺序排序

不难发现每组仅有两个数——且一定是开头的两个数——可以作为答案；因为这两个数的和一定大于该组内的所有其它数

因此有一个比较 naive 的做法：

每次询问时，检查每组开头的两个数是否满足要求；检查直接线段树查询前缀和即可；这样单次查询复杂度就是 $\Theta(\log a\log n)$。至于修改，直接用 `set` 维护每组元素的顺序即可；单次修改的复杂度就是 $\Theta(\log a+\log n)$ 的（其中的 $\log a$ 是因为要找到最高的二进制位）

发现每次询问时对每个可能成为答案的元素都查询一次前缀和很浪费

于是我们可以存下每组开头两个数的前缀和，这样就只在修改时可能需要重新计算（至多两个元素的）前缀和了。这样做的单次查询复杂度是 $\Theta(\log a)$ 的，单次修改复杂度是 $\Theta(\log a+\log n)$ 的

## CODE

### 解法一

实现可能有些烂，仅供参考 \kk

其中选择忽略为零的位置的贡献时，其实只用在叶结点的父亲处判断一次即可；不需要像下面的实现那样在所有线段树结点处都判断一次

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
using std::max;

const int MAXN =2e5+20, MAXT =1<<19;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

void write(const int &x){
	if(x/10)
		write(x/10);
	putchar('0'+x%10);
}

/*------------------------------Seg------------------------------*/

int N =1;
ll mx[MAXT], sum[MAXT];
ll tag_mx[MAXT], tag_sum[MAXT];

inline void pushdown(const int &x){
	if(tag_mx[x]){
		if(mx[x<<1] != -inf) mx[x<<1] +=tag_mx[x];
		if(mx[x<<1^1] != -inf) mx[x<<1^1] +=tag_mx[x];
		tag_mx[x<<1] +=tag_mx[x], tag_mx[x<<1^1] +=tag_mx[x];
		tag_mx[x] =0;
	}
	if(tag_sum[x]){
		sum[x<<1] +=tag_sum[x], sum[x<<1^1] +=tag_sum[x];
		tag_sum[x<<1] +=tag_sum[x]/2, tag_sum[x<<1^1] +=tag_sum[x]/2;
		tag_sum[x] =0;
	}
}

inline void pushup(const int &x){
	// 忽略 a_i=0 处的值 -V //
	mx[x] =max((sum[x<<1] == 0) ? -inf : mx[x<<1], (sum[x<<1^1] == 0) ? -inf : mx[x<<1^1]);
	sum[x] =sum[x<<1]+sum[x<<1^1];
}

void modify(const int &l, const int &r, const int &val1, const int &val2, const int &nl =1, const int &nr =N, const int &x =1){
	if(l == nl && r == nr){
		if(mx[x] != -inf) mx[x] +=val1;
		tag_mx[x] +=val1;
		sum[x] +=1ll*val2*(nr-nl+1);
		tag_sum[x] +=1ll*val2*(nr-nl+1);
		return;
	}
	pushdown(x);
	int mid =(nl+nr)>>1;
	if(r <= mid)
		modify(l, r, val1, val2, nl, mid, x<<1);
	else if(l >= mid+1)
		modify(l, r, val1, val2, mid+1, nr, x<<1^1);
	else
		modify(l, mid, val1, val2, nl, mid, x<<1), modify(mid+1, r, val1, val2, mid+1, nr, x<<1^1);
	pushup(x);
}

int query(const int &l, const int &r, const int &val, const int &nl =1, const int &nr =N, const int &x =1){
	if(nl == nr)
		return (sum[x] != 0 && mx[x] == val) ? nl : -1;
	else if(l == nl && r == nr){
		pushdown(x);
		int mid =(nl+nr)>>1;
		int ret =-1;
		if(sum[x<<1] > 0 && mx[x<<1] >= val)
			ret =max(ret, query(nl, mid, val, nl, mid, x<<1));
		if(sum[x<<1^1] > 0 && mx[x<<1^1] >= val)
			ret =max(ret, query(mid+1, nr, val, mid+1, nr, x<<1^1));
		return ret;
	}
	else{
		pushdown(x);
		int mid =(nl+nr)>>1;
		if(r <= mid)
			return query(l, r, val, nl, mid, x<<1);
		else if(l >= mid+1)
			return query(l, r, val, mid+1, nr, x<<1^1);
		else
			return max(query(l, mid, val, nl, mid, x<<1), query(mid+1, r, val, mid+1, nr, x<<1^1));
	}
}

int query0(const int *a){
	// 既然要求前缀都为 0 时 a_i=0 才可能成为贡献，那么找最左的位置就行了 //
	return (a[1] == 0) ? 1 : -1;
}

/*------------------------------Main------------------------------*/

int a[MAXN];
ll s[MAXN];

int main(){
	int n =read(), q =read();
	for(int i =1; i <= n; ++i)
		a[i] =read(), s[i] =s[i-1]+a[i];
	
	while(N < n)
		N <<=1;
	for(int i =N; i < N+n; ++i)
		mx[i] =a[i-N+1]-s[i-N+1 -1], sum[i] =a[i-N+1];
	for(int i =N+n; i < 2*N; ++i)
		mx[i] =-inf, sum[i] =0;
	for(int i =N-1; i; --i)
		pushup(i);
	
	for(int t =0; t < q; ++t){
		int p =read(), x =read();
		modify(p, p, x-a[p], x-a[p]);
		if(p+1 <= n) modify(p+1, n, -(x-a[p]), 0);
		a[p] =x;
		int ans =max(query(1, n, 0), query0(a));
		if(ans == -1)
			putchar('-'), putchar('1'), putchar('\n');
		else
			write(ans), putchar('\n');
	}
}
```

### 解法二

暂时咕咕 \kk

可参考 [这份](https://codeforces.com/contest/992/submission/39392321)

（不过感觉这种解法的实现细节其实不太多 \fad）

---

## 作者：大菜鸡fks (赞：9)

每次从p=1 跳起 每次跳到 sum[i]>=2*sum[p]的最小的i处

可以证明答案一定在跳过的i上（反证法）

理性的想一下，如果sum[i]<2*sum[p]

那么sum[i]-sum[p]<sum[p]

由于i>p所以一定不存在num[i]=sum[i-1]

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=2e5+5;
typedef long long ll;
int n,num[N],q;
ll sum[N],S;
inline void init(){
	n=read(); q=read();
	for (int i=1;i<=n;i++) num[i]=read(); 
}
struct node{
	ll mx,plu;
}a[N<<2];
void build(int k,int l,int r){
	a[k].mx=sum[r];
	if (l==r) return;
	int mid=(l+r)>>1; build(k<<1,l,mid); build(k<<1|1,mid+1,r);
}
inline void plus(int k,ll w){
	a[k].mx+=w; a[k].plu+=w;
}
inline void pushdown(int k){
	if (a[k].plu){
		plus(k<<1,a[k].plu);
		plus(k<<1|1,a[k].plu);
		a[k].plu=0;
	}
}
inline void pushup(int k){
	a[k].mx=max(a[k<<1].mx,a[k<<1|1].mx);
}
void upd(int k,int l,int r,int x,int y,int w){
	if (l==x&&r==y) {plus(k,w); return;}
	int mid=(l+r)>>1; pushdown(k);
	if (mid>=y) upd(k<<1,l,mid,x,y,w);
		else if (mid<x) upd(k<<1|1,mid+1,r,x,y,w);
			else upd(k<<1,l,mid,x,mid,w),upd(k<<1|1,mid+1,r,mid+1,y,w);
	pushup(k);
}
int qry(int k,int l,int r,ll x){
	if (a[k].mx<2ll*x) return 0;
	if (l==r) {S=a[k].mx; return r;}
	int mid=(l+r)>>1; pushdown(k);
	if (a[k<<1].mx>=2ll*x) return qry(k<<1,l,mid,x);
		else return qry(k<<1|1,mid+1,r,x);
}
inline void solve(){
	for (int i=1;i<=n;i++) sum[i]=sum[i-1]+num[i];
	build(1,1,n);
	for (int i=1;i<=q;i++){
		int x=read(),w=read();
		upd(1,1,n,x,n,w-num[x]);
		num[x]=w; S=num[1];
		if (S==0){
			puts("1");
			continue;
		}
		for (;;){
			int p=qry(1,1,n,S);
			if (!p) {
				puts("-1");
				break;
			}else{
				if (S==2ll*num[p]) {
					writeln(p);
					break;
				}
			}
		}
	}
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

## 作者：hater (赞：5)

分块

对于每一块，显然影响这个块答案的因素只有这个块之前的$a_{i}$和（废话）。

但是这启发我们可以存储**块前$a_{i}$和**为多少时，这个块会有答案。

具体的，设当前指向$i$，当 $S=a_{i}-Sblock_{i-1}$ 时，$i$是一个可行解。

（$S$就是上文提到的块前 $a_{i}$ 和， $Sblock_{i-1}$ 就是指块内的前缀和） 

把差值排序，每次询问块内二分即可。

时间复杂度 $O(q\sqrt{n}\log{\sqrt{n}})$ 。

但是有人说了啊你这个不行的啊，too slow too naive 。

做个小优化，这个$S$显然是非负的，也就是当差值为正的时候我们才把它放到序列里面，特判一手差值为$0$。

```cpp
if( a[i] >= ts && a[i] != ts ) b[++len] = (node){ a[i] - ts , i } ; 
ts += a[i] ; 
```

每当 $len$ 加一时，$ts$ 至少乘二，那么 $len$ 的大小将是 $\log{V}$ 。

好yeah！时间复杂度大概是$O(q\sqrt{n}\log{\log{V}})$了。

不过还是慢的要死/px。

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
#define i60 long long 
#define dou double 
#define ls k<<1 
#define rs k<<1|1 
using namespace std ; 
const int N = 2e5+10 , B = 450 ;  
int pos[N] , lef[N] , rig[N] , a[N] , n ;  
struct node { 
  i60 vl ; int id ; 
  friend bool operator < ( node A , node B ) { return A.vl < B.vl ; } 
} ; 			
struct block_ { 
  node b[40] ; int len , tp , v0 ; i60 ts ;  
  void build( int p ) { 
    len = 0 ; ts = 0 ; v0 = -1 ; 
    fp( i , lef[p] , rig[p] ) { 
      if( a[i] >= ts && a[i] != ts ) b[++len] = (node){ a[i] - ts , i } ; 
      if( a[i] == ts ) v0 = i ; 
	  ts += a[i] ; 
	} 
	sort( b+1 , b+1+len ) ; 
  } 
  int query( i60 nw ) { 
    if( nw == 0 ) return v0 ; 
    tp = lower_bound( b+1 , b+1+len , (node){nw,0} ) - b ; 
	return ( tp && tp <= len && b[tp].vl == nw ) ? b[tp].id : -1 ;   
  } 
} t[B] ;  
int ask( ) { 
  i60 nw = 0 ; int tp ; 
  fp( i , 1 , pos[n] ) { 
    tp = t[i].query( nw ) ; if( tp != -1 ) return tp ;  
    nw += t[i].ts ; 
  } return -1 ; 
} 
signed main( ) { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  int q , x , y ; cin >> n >> q ; int blo = sqrt(n) ;  
  fp( i , 1 , n ) cin >> a[i] , pos[i] = (i-1)/blo+1 ; 
  fp( i , 1 , n ) rig[pos[i]] = i ; 
  fq( i , 1 , n ) lef[pos[i]] = i ; 
  fp( i , 1 , pos[n] ) t[i].build( i ) ; 
  while( q -- ) { 
    cin >> x >> y ; a[x] = y ; t[pos[x]].build( pos[x] ) ; 
    cout << ask( ) << '\n' ; 
  } 
  return 0 ; 
}  
```


---

## 作者：zxh_mc (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF992E)

[更好的阅读体验](https://www.cnblogs.com/zxh-mc/p/16988408.html)

## 分析

由于满足 $a_i\ge0$，所以 $s_i$ 单调不减。

当我们找到一个 $i$ 时，不管 $i$ 是否满足，下一个可能的一定大于等于 $a_i+s_{i-1}$。

而且 $a_i+s_{i-1}=2a_i$ 或 $a_i+s_{i-1}=2s_{i-1}$。

也就是说，当找到一个 $i$ 后，下一个可能的 $i$ 和当前 $i$ 的值呈现**二倍关系**。

由此我们得出，如果我们按照这种方法查询，每一次都跳到后面所有 $i$ 中第一个 $a_i$ 大于等于 $a_{nowi}+s_{nowi-1}$ 的，最多能跳 $\log10^9$ 次。

然后需要解决快速找到区间中的大于等于 $x$ 的第一个数。

考虑二分，建立线段树求区间最值，复杂度 $O(\log^2n)$，总复杂度 $O(n\log^2n\log10^9)$，超时。

优化二分，线段树是天生的分治结构，考虑将查询的区间分成若干段，段的长度也是二倍关系，每一段对应线段树中的一个结点，再线段树上二分，最后合并结果，总复杂度 $\log n$。

总复杂度 $O(n\log n\log 10^9)$，足以通过此题。

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10;

int n, a[N], q;

struct node {
	int l, r, maxn;
	LL v;
}nodes[N << 2];

inline void push_up (int p) {
	nodes[p].v = nodes[p << 1].v + nodes[p << 1 | 1].v;
	if (nodes[p << 1].maxn > nodes[p << 1 | 1].maxn) nodes[p].maxn = nodes[p << 1].maxn;
	else nodes[p].maxn = nodes[p << 1 | 1].maxn;
}

void build (int p, int l, int r) {
	nodes[p].l = l; nodes[p].r = r;
	if (l == r) {
		nodes[p].v = nodes[p].maxn = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build (p << 1, l, mid); build (p << 1 | 1, mid + 1, r);
	push_up(p);
}

void add (int p, int idx, int x) {
	int tl = nodes[p].l, tr = nodes[p].r;
	if (tl == tr) {
		nodes[p].v = nodes[p].maxn = a[idx] = x;
		return;
	}
	int mid = (tl + tr) >> 1;
	if (idx <= mid) add(p << 1, idx, x);
	else add(p << 1 | 1, idx, x);
	push_up(p);
}

int get_max (int p, int l, int r) {
	if (l > r) return 0;
	int tl = nodes[p].l, tr = nodes[p].r;
	if (tl >= l && tr <= r) return nodes[p].maxn;
	int res = -1, mid = (tl + tr) >> 1;
	if (l <= mid) {
		int k = get_max(p << 1, l, r);
		if (k > res) res = k;
	}
	if (r > mid) {
		int k = get_max (p << 1 | 1, l, r);
		if (k > res) res = k;
	}
	return res;
}

LL get_s (int p, int l, int r) {
	if (l > r) return 0;
	int tl = nodes[p].l, tr = nodes[p].r;
	if (tl >= l && tr <= r) return nodes[p].v;
	int mid = (tl + tr) >> 1; LL res = 0;
	if (l <= mid) res += get_s (p << 1, l, r);
	if (r > mid) res += get_s (p << 1 | 1, l, r);
	return res;
}

int find (int p, LL x) {
	int tl = nodes[p].l, tr = nodes[p].r;
	if (tl == tr) if (a[tl] >= x) return tl; else return -1;
	int k1 = nodes[p << 1].maxn, k2 = nodes[p << 1 | 1].maxn;
	if (k1 >= x) return find (p << 1, x);
	else if (k2 >= x) return find(p << 1 | 1, x);
	return -1;
} 

int ask (int l, int r, LL x) {
	if (l > r) return -1;
	int p = 1, res = n + 1;
	while (nodes[p].l != nodes[p].r) {
		if (nodes[p << 1 | 1].l <= l) p = p << 1 | 1;
		else {
			int k = find(p << 1 | 1, x);
			if (k != -1) res = min(res, k);
			p = p << 1;
		}
	}
	if (nodes[p].maxn >= x) res = min(res, nodes[p].l);
	if (res > n) return -1;
	return res;
}

int main () {
	scanf("%d%d", &n, &q);
	for (int i = 1;i <= n;i++) scanf("%d", &a[i]);
	build(1, 1, n);
	while (q--) {
		int idx, k;
		scanf("%d%d", &idx, &k);
		add(1, idx, k);
		bool flag = 0;
		for (int i = 1;i <= n;) {
			LL x1 = get_s(1, 1, i - 1), x2 = a[i];
			if (x1 == x2) {
				printf("%d\n", i); flag = 1;
				break;
			}
			i = ask(i + 1, n, x1 + x2);
			if (i == -1) break;
		}
		if (!flag) printf("-1\n");
	}
	return 0;
}
```


---

## 作者：hxdts (赞：2)

小朋友分块

容易想到在每个块内维护一个 `hash` ，

这样可以每次 $O(1)$ 询问块内是否有满足条件的答案，

做到 $O(\sqrt n)$ 修改和询问。

$a[i]=s[i-1]\\
a[i]=s[st[bl[i]]-1]+s[i-1]-s[st[bl[i]]-1]\\
s[st[bl[i]]-1]=a[i]-s[i-1]+s[st[bl[i]]-1]
$

所以我们以 `a[i]-s[i-1]+s[st[bl[i]]-1]` 为下标， `i` 为值存进 `hash` 就可以了，

修改的时候直接重构整个块，

询问的时候暴力遍历块，算前缀和，用 `hash` 查询每个块。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5,len=300;
const long long mod=107;
int n,m,a[N+10],x,k,bl[N+10],st[N/len+10],ed[N/len+10],cnt,last;
long long s[N/len+10][N/len+10];
int read()
{
	char ch=getchar();
	int r=0,w=1;
	while(ch<'0'||ch>'9') w=ch=='-'?-1:w,ch=getchar();
	while(ch>='0'&&ch<='9') r=r*10+ch-'0',ch=getchar();
	return r*w;
}
struct hash
{
	int cnt,key[110];
	struct node
	{
		long long x;
		int v,next;
	}a[10010];
	void clear()
	{
		memset(key,0,sizeof(key));
		cnt=0;
	}
	void add(long long x,int k)
	{
		a[++cnt]={x,k,key[x%mod]};
		key[x%mod]=cnt;
	}
	int ask(long long x)
	{
		for(int i=key[x%mod];i;i=a[i].next)
		if(a[i].x==x)
		return a[i].v;
		return 0;
	}
}vis[N/len+10];
void build()
{
	for(int i=1;i<=n;i+=len)
	st[++cnt]=i,ed[cnt]=i+len-1;
	ed[cnt]=n;
	for(int i=1;i<=cnt;i++)
	for(int j=st[i];j<=ed[i];j++)
	bl[j]=i,s[i][j-st[i]+1]=s[i][j-st[i]]+a[j],vis[i].add(a[j]-s[i][j-st[i]],j);
}
int add(int x,int k)
{
	a[x]=k;
	vis[bl[x]].clear();
	for(int j=st[bl[x]];j<=ed[bl[x]];j++)
	s[bl[x]][j-st[bl[x]]+1]=s[bl[x]][j-st[bl[x]]]+a[j],s[bl[x]][j-st[bl[x]]+1]=s[bl[x]][j-st[bl[x]]]+a[j],vis[bl[x]].add(a[j]-s[bl[x]][j-st[bl[x]]],j);
	if(last>0&&x>last)
	return last;
	long long sum=0;
	for(int i=1;i<=cnt;i++)
	{
		int k=vis[i].ask(sum);
		if(k)
		return k;
		else
		sum+=s[i][ed[i]-st[i]+1];
	}
	return -1;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	a[i]=read();
	build();
	while(m--)
	{
		x=read(),k=read();
		printf("%d\n",last=add(x,k));
	}
}
```

---

## 作者：run_away (赞：1)

## 题意

给定一个序列 $a_i$ ，记其前缀和序列为 $s_i$ ，有 $q$ 个询问，每次单点修改，询问是否存在一个 $i$ 满足 $a_i=s_i−1$​ ，有多解输出任意一个，无解输出 $−1$ 。

## 分析

考虑一个很暴力的解法，每次修改都直接在原数组上改，然后再遍历一遍寻找答案，这样毫无疑问是 $O(nq)$ 的。

但是可以发现一个性质：由于合法的 $a_i$ 等于 $s_{i-1}+1$ 且为正数，所以每个符合条件的 $a_i$ 都会让前缀和倍增，所有数的总和是 $s_n$，那么最多也只会有 $\log s_n$ 个这样的 $a_i$。

用线段树维护 $a_i-s_{i-1}$ 的值，单次可以在最坏 $\log n\log V$ 的情况下完成查询。

题目里的单点修改在这颗线段树上就是给 $i$ 单点加，给 $[i+1,n]$ 区间减，用 lazy tag 就可以了，注意 $i=n$ 时需跳过后面的区间减。

时间复杂度降到了 $O(q\log n\log V)$，可以接受。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar('\n');return;}short top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar('\n');}
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((t[x].l+t[x].r)>>1)
const ll maxn=2e5+5;
ll n,q,res,a[maxn],s[maxn];
struct node{
    ll l,r,val,tag;
}t[maxn<<2];
inline void pushup(ll x){t[x].val=max(t[ls].val,t[rs].val);}
inline void pushdown(ll x){
    if(!t[x].tag)return;
    t[ls].tag+=t[x].tag,t[rs].tag+=t[x].tag;
    t[ls].val+=t[x].tag,t[rs].val+=t[x].tag;
    t[x].tag=0;
}
inline void build(ll x,ll l,ll r){
    t[x].l=l,t[x].r=r;
    if(l==r){
        t[x].val=a[l]-s[l-1];
        return;
    }
    build(ls,l,mid),build(rs,mid+1,r);
    pushup(x);
}
inline void update(ll x,ll l,ll r,ll k){
    if(l<=t[x].l&&t[x].r<=r){
        t[x].val+=k;t[x].tag+=k;
        return;
    }
    pushdown(x);
    if(l<=mid)update(ls,l,r,k);
    if(r>mid)update(rs,l,r,k);
    pushup(x);
}
inline void query(ll x){
    if(res!=-1)return;
    if(t[x].l==t[x].r){
        if(!t[x].val)res=t[x].l;
        return;
    }
    pushdown(x);
    if(t[ls].val>=0)query(ls);
    if(t[rs].val>=0)query(rs);
}
inline void solve(){
    n=read(),q=read();
    for(ll i=1;i<=n;++i)a[i]=read(),s[i]=s[i-1]+a[i];
    build(1,1,n);
    while(q--){
        ll pos=read(),k=read();
        update(1,pos,pos,k-a[pos]);
        if(pos<n)update(1,pos+1,n,a[pos]-k);
        a[pos]=k,res=-1;
        query(1);write(res);
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ll t=1;
    while(t--){
        solve();
    }
    fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```

---

## 作者：wizardMarshall (赞：1)

## 题意

每次单点修改之后找到任意一个 $i$ 使得 $a_i=\displaystyle \sum ^{i-1}_{j=1}a_j$。

## 思路

前置知识：线段树

定义 $s_i=\displaystyle \sum ^i_{j=1}a_j$，$a$ 为 $a_i$ 上界。

如果有 $i$ 满足 $a_i=s_{i-1}$，则 $s_i=s_{i-1}+a_i=2s_{i-1}$。由于 $a_i \ge 0$，$s_i$ 不降，所以增长速度是指数级的，即最多有 $\log a$ 个 $i$ 满足上述条件。

先不考虑这个优化，回顾暴力思路，就是单点修改后遍历每个 $i$ 判断是不是满足条件，即 $a_i=s_{i-1}$ 或 $a_i-s_{i-1}=0$。

在线段树上维护 $c_i=\displaystyle \max _{l \le i \le r}\{a_i-s_{i-1}\}$，寻找答案的时候只要递归寻找 $c \ge 0$ 的区间就好了。最终递归到叶子结点，如果 $c_i = 0$ 即满足答案返回。

考虑最坏情况，假如真的有 $\log a$ 个叶子结点，则每个节点最多递归 $\log n$ 次，总复杂度 $O(n \log n\log a)$。

对于单点修改将 $a_i$ 改为 $v$（下面默认 $a_i$ 先不改变，是原来的值），首先区间 $[i,i]$ 肯定要加上 $v-a_i$。然后因为影响了 $s_{j}(i \le j \le n)$，即 $c_j(i+1\le j \le n)$，所以要对 $[i+1,n]$ 减去 $v - a_i$。这一部分是区间修改，没什么好讲的。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 200005;
int a[N];
ll s[N];
ll tree[N << 2], lazy[N << 2];
void build(int x, int l, int r) {
	if (l == r) {
		tree[x] = a[l] - s[l - 1];
		return;
	}
	int m = (l + r) / 2;
	build(x << 1, l, m);
	build((x << 1) | 1, m + 1, r);
	tree[x] = max(tree[x << 1], tree[(x << 1) | 1]);
	return;
}
void pushdown(int x) {
	if (lazy[x]) {
		tree[x << 1] += lazy[x];
		tree[(x << 1) | 1] += lazy[x];
		lazy[x << 1] += lazy[x];
		lazy[(x << 1) | 1] += lazy[x];
		lazy[x] = 0;
	}
	return;
}
void change(int x, int l, int r, int L, int R, int v) {
	if (L <= l && r <= R) {
		tree[x] += v;
		lazy[x] += v;
		return;
	}pushdown(x);
	int m = (l + r) / 2;
	if (L <= m) {
		change(x << 1, l, m, L, R, v);
	}
	if (R > m) {
		change((x << 1) | 1, m + 1, r, L, R, v);
	}
	tree[x] = max(tree[x << 1], tree[(x << 1) | 1]);
	return;
}
int ask(int x, int l, int r) {
	if (l == r) {
		if (tree[x] == 0) {
			return l;
		}return -1;
	}
	pushdown(x);
	int m = (l + r) / 2;
	if (tree[x << 1] >= 0) {
		int v = ask(x << 1, l, m);
		if (v != -1)return v;
	}
	if (tree[(x << 1) | 1] >= 0) {
		int v = ask((x << 1) | 1, m + 1, r);
		if (v != -1)return v; 
	}return -1;
}
signed main() {
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		s[i] = s[i - 1] + a[i];
	}build(1, 1, n);
	while (q--) {
		int id, x;
		scanf("%d%d", &id, &x);
		int v = x - a[id];
		a[id] = x;
		change(1, 1, n, id, id, v);
		if (id != n)change(1, 1, n, id + 1, n, -v);
		printf("%d\n", ask(1, 1, n));
	}
	return 0;
}
```

---

## 作者：Z1qqurat (赞：1)

神！首先我们维护 $T_i=s_i-2a_i$ 这个东西，那么满足条件 $a_i=s_{i-1}$ 当且仅当 $T_i=0$。容易发现，在某一时刻，满足条件的位置不会超过 $\log V$ 个，因为每次需要 $s_i=2a_i$。所以我们想着怎样才能只往 $\log V$ 个位置上找。考虑先是用线段树维护这个 $T$，然后类似于 KDT 的剪枝方式，我们维护 $mx(l,r),mn(l,r)$ 表示 $[l,r]$ 内 $T$ 的极值，那么一个区间可能有答案当且仅当 $mx(l,r)\ge0, mn(l,r)\le0$，按照这样的剪枝方式，每次只往满足条件的区间递归，最终至多访问到 $\log V$ 个叶子节点（同时，在已经找到答案后就不再递归，也是一个小剪枝），这样就能保证复杂度 $\mathcal{O}(q\log n\log V)$。题解区的解法貌似是只维护 $mx(l,r)\ge 0$ 的，但是我认为这样是不太对，比如用 $a_1=1,a_{2\sim n}=0$ 的数据能使得它访问了每一个叶子节点但是没有找到答案导致复杂度退化为 $\mathcal{O}(nq)$（反正我试了一下这样是会 TLE on #8 的）。

```cpp
#include <bits/stdc++.h>
#define ALL(v) begin(v), end(v)
#define All(v, l, r) &v[l], &v[(r) + 1]
using i64 = int64_t;
using db = double;
using std::cin;
using std::cout;
constexpr int N = 2e5 + 5;

namespace Read {
   inline auto get() { return cin.rdbuf()->sbumpc(); }

   template <typename T>
   void read(T& x) {
      auto c = 0;
      do c = get();
      while (std::isspace(c));
      x = 0;
      for (; std::isdigit(c); c = get()) x = x * 10 + c - '0';
   }
} //namespace Read
using Read::read;

int n, q, res;
std::array<i64, N> a, s;

namespace Isagi {
   #define lc (p << 1)
   #define rc (p << 1 | 1)

   std::array<i64, N << 2> mn, mx, tag;

   auto pushup(int p) {
      mx[p] = std::max(mx[lc], mx[rc]), mn[p] = std::min(mn[lc], mn[rc]);
   }
   auto build(int p, int l, int r) {
      if (l == r) return mx[p] = mn[p] = s[l] - 2ll * a[l], void();
      auto mid = l + r >> 1;
      build(lc, l, mid), build(rc, mid + 1, r);
      pushup(p);
   }
   auto addtag(int p, i64 v) {
      tag[p] += v, mx[p] += v, mn[p] += v;
   }
   auto pushdown(int p) {
      if (tag[p] != 0) addtag(lc, tag[p]), addtag(rc, tag[p]), tag[p] = 0;
   }
   auto modify(int x, int y, i64 v) {
      auto modify { [&] (auto modify, int p, int l, int r) {
         if (x <= l && r <= y) return addtag(p, v), void();
         pushdown(p);
         auto mid = l + r >> 1;
         if (x <= mid) modify(modify, lc, l, mid);
         if (y > mid) modify(modify, rc, mid + 1, r);
         pushup(p);
      }};
      return modify(modify, 1, 1, n), void();
   }
   auto query() {
      auto query { [&] (auto query, int p, int l, int r) {
         if (res != -1 || l > r || l < 1 || r > n) return ;
         if (l == r) {
            if (mx[p] == 0) res = l;
            return ;
         }
         pushdown(p);
         auto mid = l + r >> 1;
         if (mx[lc] >= 0 && mn[lc] <= 0) query(query, lc, l, mid);
         if (mx[rc] >= 0 && mn[rc] <= 0 && res == -1) query(query, rc, mid + 1, r);
      }};
      return query(query, 1, 1, n), void();
   }

} //namespace Isagi

auto main() -> int {
   std::ios::sync_with_stdio(false);
   cin.tie(nullptr), cout.tie(nullptr);

   read(n), read(q);
   for (auto i = 1; i <= n; ++i) cin >> a[i], s[i] = s[i - 1] + a[i];
   Isagi::build(1, 1, n);
   for (auto i = 1, x = 0, y = 0; i <= q; ++i) {
      read(x), read(y);
      Isagi::modify(x, x, 2ll * (a[x] - y));
      Isagi::modify(x, n, y - a[x]);
      a[x] = y, res = -1;
      Isagi::query();
      cout << res << "\n";
   }
   return 0;
}

---

## 作者：Trafford1894 (赞：0)

NOIp 前写题解，RP ++。

注意到 $a_i=s_{i-1}$ 是一个较难满足的条件，可以想到合法 $a_i$ 的数量一定不多。具体地，如果 $a_i = s_{i-1}$，则 $s_i = 2 \times s_{i-1}$。则合法的 $i$ 只有 $O(\log n)$ 个。

考虑对于每一个 $i$，维护 $a_i-s_{i-1}$ 的区间最大值。在查询的时候如果最大值 $\geq 0$ 则可能有解。因为合法 $i$ 的数量只有 $O(\log n)$ 个，直接判断即可。

单点修改时会对 $i$ 产生 $a_i - x$ 的贡献，对于 $[i+1,n]$ 会产生 $x - a_i$ 的贡献。线段树维护区间加、区间最大值即可。

[CF 提交记录。](https://codeforces.com/contest/992/submission/293824238)

---

## 作者：Gapple (赞：0)

先说暴力。线段树维护 $a_i - s_{i - 1}$，每次暴力 $O(n \log n)$ 查找 $0$ 的位置。

这会超时，考虑加个优化：

- 维护一个区间 max，在查询到的区间的 max 小于 $0$ 时退出。
- 设 $p$ 为修改的位置，$x$ 为修改成的值。在修改时把区间 $[p, p]$ 加 $x - a_i$，把区间 $[p + 1, n]$ 加 $a_i - x$ 即可。注意 $p = n$ 时会越界。

这时你把优化后的代码交上去，发现它过了。为什么？

因为实际上满足条件的位置只有 $O(\log n)$ 个。若个数大于 $O(\log n)$，每个满足条件的位置都会翻倍，则满足不了 $1 \le p_i \le n$ 的值域。故此时查询到的叶子最多只有 $O(\log n)$ 个，可以通过。

[AC 记录](https://codeforces.com/contest/992/submission/286380679)。

---

## 作者：Xttttr (赞：0)

## CF992E 题解

[传送门](https://www.luogu.com.cn/problem/CF992E)  [更好的阅读体验](https://www.cnblogs.com/Xttttr/p/17627033.html)

简化题意：单点修改，设序列的前缀和序列是 $s_i$，查询是否存在一个 $i$ 满足 $a_i=s_{i-1}$。

### 思路：

观察满足条件的数的个数。在不考虑 $0$ 的情况下，如果一个 $a_i$ 满足条件，那么对于一个比他小的满足条件的数 $a_j$，一定会有 $a_j=s_{j-1}$，而 $s_{j-1}+a_j=s_j\leqslant s_{i-1}=a_i$，这就说明 $2\times a_j\leqslant a_i$，因此满足条件的数至多有 $O(\log V)$ 个。如果考虑 $0$，那么任意一个在全零前缀里的数都满足条件，随便选一个就可以了。

因此，我们就可以暴力来找可能满足条件的数，即不断地找区间内最大的满足 $s_{i-1}\leqslant a_i$ 的 $i$。每次最大的可能做贡献的 $i$ 需要满足 $s_{i-1}\leqslant a_i$，而又有 $s_{i-1}+a_i\leqslant\sum a$，因此有$2s_{i-1}\leqslant \sum a$，于是就每次二分找出最大的满足 $2s_{i-1}\leqslant \sum a$ 的 $i$，常规做法是线段树上二分。而在本题中这个区间是一段前缀，可以直接在树状数组上二分，非常好写。

复杂度 $O(n\log n\log V)$。

```
const int N=200501;
int n,Q;
int a[N],Lg;
ll c[N];
inline void add(int x,int y){for(;x<=n;x+=x&(-x))c[x]+=y;}
inline pair<int,int> query(int x){
    int k=0;
    ll sum=0;
    for(int i=Lg;~i;i--){
        int cur=k|(1<<i);
        if(cur<=n&&sum+c[cur]<=x)sum+=c[cur],k=cur;
    }
    return make_pair(k,sum);
}
inline int query(){
    if(a[1]==0)return 1;
    int cur=2e9;
    do{
        cur>>=1;
        pair<int,int> tmp=query(cur);
        if(tmp.second==a[tmp.first+1]){
            return tmp.first+1;
        }
    }while(cur);
    return -1;
}
int main(){
    n=read(),Q=read();
    Lg=log2(n);
    for(int i=1;i<=n;i++)a[i]=read(),add(i,a[i]);
    while(Q--){
        int p=read(),x=read();
        add(p,x-a[p]);
        a[p]=x;
        write(query());putchar('\n');
    }
    return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)

维护一个 $a_i-s_{i-1}$ 的序列，单点修改 $a_i$ 的值很容易用区间修改的线段树实现。查询呢？

考虑这样一个问题，最多有几个满足条件的位置呢？如果不考虑 $0$ 的影响，那么满足条件位置最多的应该是形如 `1 1 2 4 8 16` 这样一个数列，满足条件的位置只有 $\log V$ 级别个。

也就是说，满足 $a_i\ge s_{i-1}$ 的 $i$ 的个数，每满足一次时，$s_{i}$ 相比 $s_{i-1}$ 会翻倍，导致最多只有 $\log V$ 个满足条件的位置。此时线段树暴力查找的复杂度就是对的。

然后考虑一下 $0$，$0$ 对满足条件位置数量的影响仅当 $a_1=0$ 时会出现（一个形如 `0 0 0 0 0` 的序列），因此查到一个答案直接就 `return` 即可，单次查询复杂度依然是 $\log$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 

int n, m; 
int a[500005]; 
i64 T[2000005], s[500005], tag[2000005]; 

void build(int o, int l, int r) {
    if (l == r) return T[o] = a[l] - s[l - 1], void(); 
    int mid = l + r >> 1; build(o << 1, l, mid); build(o << 1 | 1, mid + 1, r); 
    T[o] = max(T[o << 1], T[o << 1 | 1]); 
}

inline void pushdown(int o) {
    if (!tag[o]) return;
    tag[o << 1] += tag[o]; tag[o << 1 | 1] += tag[o]; 
    T[o << 1] += tag[o]; T[o << 1 | 1] += tag[o]; 
    tag[o] = 0; 
}

void update(int o, int l, int r, int x, int y, int k) {
    if (x <= l && r <= y) return tag[o] += k, T[o] += k, void(); 
    pushdown(o); int mid = l + r >> 1; 
    if (x <= mid) update(o << 1, l, mid, x, y, k); 
    if (mid < y) update(o << 1 | 1, mid + 1, r, x, y, k); 
    T[o] = max(T[o << 1], T[o << 1 | 1]); 
}

int ans = -1; 
void query(int o, int l, int r, int x, int y) {
    if (T[o] < 0 || ans != -1) return; 
    if (l == r) {
        if (T[o] == 0) ans = l; 
        return; 
    }
    pushdown(o); int mid = l + r >> 1; 
    if (x <= mid) query(o << 1, l, mid, x, y); 
    if (mid < y) query(o << 1 | 1, mid + 1, r, x, y); 
}

int main(void) {
    scanf("%d%d", &n, &m); 
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), s[i] = s[i - 1] + a[i]; 
    build(1, 1, n); 
    while (m--) {
        int p, x; scanf("%d%d", &p, &x); 
        update(1, 1, n, p, p, x - a[p]); 
        if (p < n) update(1, 1, n, p + 1, n, a[p] - x); 
        ans = -1; query(1, 1, n, 1, n); 
        printf("%d\n", ans); a[p] = x; 
    }
    return 0; 
}
```

---

