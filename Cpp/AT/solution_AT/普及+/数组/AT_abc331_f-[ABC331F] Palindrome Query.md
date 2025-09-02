# [ABC331F] Palindrome Query

## 题目描述

给定一个由小写英文字母组成、长度为 $N$ 的字符串 $S$。  
请按给定顺序处理 $Q$ 个如下所述的查询。  
查询有以下两种类型之一：

- `1 x c` ：将 $S$ 的第 $x$ 个字符修改为小写英文字母 $c$。
- `2 L R` ：如果 $S$ 的第 $L$ 个字符到第 $R$ 个字符组成的子串是回文串，则输出 `Yes`，否则输出 `No`。

## 说明/提示

### 限制条件

- $1 \leq N \leq 10^6$
- $1 \leq Q \leq 10^5$
- $S$ 是由小写英文字母组成的长度为 $N$ 的字符串
- $1 \leq x \leq N$
- $c$ 是小写英文字母
- $1 \leq L \leq R \leq N$
- $N, Q, x, L, R$ 均为整数

### 样例解释 1

初始时，$S = $ `abcbacb`。  
对于第 $1$ 个查询，$S$ 的第 $1$ 到第 $5$ 个字符组成的字符串为 `abcba`，这是回文串，因此输出 `Yes`。  
对于第 $2$ 个查询，$S$ 的第 $4$ 到第 $7$ 个字符组成的字符串为 `bacb`，这不是回文串，因此输出 `No`。  
对于第 $3$ 个查询，$S$ 的第 $2$ 到第 $2$ 个字符组成的字符串为 `b`，这是回文串，因此输出 `Yes`。  
对于第 $4$ 个查询，将 $S$ 的第 $5$ 个字符修改为 `c`，$S$ 变为 `abcbccb`。  
对于第 $5$ 个查询，$S$ 的第 $1$ 到第 $5$ 个字符组成的字符串为 `abcbc`，这不是回文串，因此输出 `No`。  
对于第 $6$ 个查询，$S$ 的第 $4$ 到第 $7$ 个字符组成的字符串为 `bccb`，这是回文串，因此输出 `Yes`。  
对于第 $7$ 个查询，将 $S$ 的第 $4$ 个字符修改为 `c`，$S$ 变为 `abccccb`。  
对于第 $8$ 个查询，$S$ 的第 $3$ 到第 $6$ 个字符组成的字符串为 `cccc`，这是回文串，因此输出 `Yes`。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 8
abcbacb
2 1 5
2 4 7
2 2 2
1 5 c
2 1 5
2 4 7
1 4 c
2 3 6```

### 输出

```
Yes
No
Yes
No
Yes
Yes```

# 题解

## 作者：Register_int (赞：22)

我们平时是如何 $O(1)$ 判回文串的？使用字符串哈希。如果一个串正反的字符串哈希相等，就说明这是个回文串。

同样的，对于本题，我们只需要用线段树维护正反哈希即可。合并时，只要分为前半部分与后半部分，乘上对应系数。时间复杂度 $O(n\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int MAXN = 1e6 + 10;

ull p[MAXN];

struct node {
	int l, r; ull h1, h2;
	node operator + (const node &rhs) const {
		return { l, rhs.r, 
		h1 * p[rhs.r - rhs.l + 1] + rhs.h1, 
		h2 + rhs.h2 * p[r - l + 1] };
	}
} t[MAXN << 2], ans; char s[MAXN];

inline 
void pushup(int p) {
	t[p] = t[p << 1] + t[p << 1 | 1];
}

void build(int l, int r, int p) {
	t[p].l = l, t[p].r = r;
	if (l == r) return t[p].h1 = t[p].h2 = s[l], void();
	int mid = l + r >> 1;
	build(l, mid, p << 1), build(mid + 1, r, p << 1 | 1), pushup(p);
}

void modify(int k, int x, int p) {
	if (t[p].l == t[p].r) return t[p].h1 = t[p].h2 = x, void();
	int mid = t[p].l + t[p].r >> 1;
	modify(k, x, p << 1 | k > mid), pushup(p);
}

node query(int l, int r, int p) {
	if (l <= t[p].l && t[p].r <= r) return t[p];
	int mid = t[p].l + t[p].r >> 1;
	if (r <= mid) return query(l, r, p << 1);
	if (l > mid) return query(l, r, p << 1 | 1);
	return query(l, r, p << 1) + query(l, r, p << 1 | 1);
}

int n, m; char c[2];

int main() {
	scanf("%d%d%s", &n, &m, s + 1), *p = 1;
	for (int i = 1; i <= n; i++) p[i] = p[i - 1] * 131; build(1, n, 1);
	for (int op, x, y; m--;) {
		scanf("%d%d", &op, &x);
		if (op == 1) scanf("%s", c), modify(x, *c, 1);
		else scanf("%d", &y), ans = query(x, y, 1), puts(ans.h1 == ans.h2 ? "Yes" : "No");
	}
}
```

---

## 作者：SSER_ZRQ (赞：11)

在以往的学习中，我们所见到的哈希通常是这样的：

（以 $p$ 为哈希底数，模数采用自然溢出）

$$s_{i-j} = \sum_{k=i}^{j}s_k \times p^{j-k} $$
$$hash_i=s_{1-i}=\sum_{k=1}^{i}s_k \times p^{i-k}=hash_{i-1} \times p +s_i$$
询问 $s_{i-j}$ 的哈希值时，即为
$$s_{i-j}=hash_j-hash_{i-1} \times p^{j-i+1}$$

判回文串：维护顺着的和倒着的哈希值，判断是否相等。


------------

带入到[这道题](https://atcoder.jp/contests/abc331/tasks/abc331_f)时，即让我们维护哈希值，并动态查询。

考虑修改字符串的一个字符对于整个串哈希值的影响。

把第 $x$ 个字符从 $s_x$ 改成 $c$ 时，令 $cnt=c-s_x$，则对于 $i=x \dots n$，$hash_i = hash_i + cnt \times p^{i-x}$。

于是就将题意转化为：区间加等比数列，单点查询。

十分难实现。


------------

思考上述算法的弊端：对于 $i=x \dots n$，$hash_i$ 加上的是不同的值。

能不能让他们都加上一个相同的值呢？


------------

考虑一种新的哈希定义方式：
$$s_{i-j} = \sum_{k=i}^{j}s_k \times p^{k-i} $$
则有
$$hash_i = s_{1-i}=\sum_{k=1}^{i}s_k \times p^{k-1}=hash_{i-1} + s_i \times p^{i-1}$$
询问 $s_{i-j}$ 的哈希值时，即为
$$s_{i-j} = \frac{hash_j-hash_{i-1}}{p^{i-1}}$$

这种哈希函数的求值需要用到逆元，这也是为什么我们不常用这种哈希函数的原因。

逆元的求值方法参考[OI-WIKI](https://oi-wiki.org/math/number-theory/inverse/)，这里取 $p=13331$，在模 $2^{64}$ 情况下的逆元为 $INV=13718477289532405275$。

则求值函数转化为：
$$s_{i-j} = (hash_j-hash_{i-1}) \times INV^{i-1}$$

------------

回到这道题，考虑修改字符串的一个字符对于整个串新哈希值的影响。

把第 $x$ 个字符从 $s_x$ 改成 $c$ 时，令 $cnt=c-s_x$，则对于 $i=x \dots n$，$hash_i = hash_i + cnt \times p^{x-1}$。

于是就将题意转化为：区间加，单点查询。

不难维护，这里使用的是差分+树状数组。

时间复杂度为 $O(q \log n)$。

[code](https://atcoder.jp/contests/abc331/submissions/48186319)

---

## 作者：Genius_Star (赞：4)

### 题意：

维护两个操作：

- 单点修改某一位置。

- 查询区间 $[l,r]$ 是否是回文串。

### 思路：

场切了。

回文串的性质是：正着和倒着一样。

那我们就有了一个思路，维护 $S_{1,i}$ 表示 $1 \sim i$ 的哈希，$S_{2,i}$ 表示 $2 \sim i$ 的哈希。

那么我们只需要判断区间 $[l,r]$ 的正着的哈希值与倒着的哈希值是否相同，即判断：

$$\frac{S_{1,r}-S_{1,l-1}}{base^{l-1}}=\frac{S_{2,l}-S_{2,r+1}}{base^{r-1}}$$

这样每次查询只是 $O(1)$ 的，修改的复杂度会达到 $O(N)$。

所以现在可以进行两个优化：

- 树状数组优化，每次利用前缀和进行修改，可以使得修改和查询的复杂度为 $O(\log N)$。

- 线段树优化，维护区间内正着的哈希值和反着的哈希值，每次单点修改，区间查询，时间复杂度为 $O(\log N)$。（常数应该比树状数组大一些）

本篇题解采用线段树优化。

**区间合并：**

设左区间为 $L$，右区间为 $R$，当前区间为 $X$。（$K1$ 表示当前区间正着的哈希值，$K2$ 表示当前去就反着的哈希值，$len$ 表示该区间长度）

$$X \to K1=L \to K1 + base^{L \to len} \times R \to K1$$

$$X \to K2=R \to K2 + base^{R \to len} \times L \to K2$$

可以用快速幂或者提前预处理 $base$ 的幂。

时间复杂度：$O((n+q) \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=1000100,base=127,P=998244353;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,q,op,x,y;
char c[N];
char h;
struct Node{
	ll l,r;
	ll K1,K2;
	ll len;
}X[N<<2];
struct St{
	ll x,y;
	ll data;
};
ll qpow(ll a,ll b,ll mod){
	ll ans=1;
	while(b){
		if(b&1ll)
		  ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1ll;
	}
	return ans;
}
void pushup(ll k,ll mod){
	X[k].K1=(X[k<<1].K1+(qpow(base,X[k<<1].len,P)*X[k<<1|1].K1)%mod)%mod;
	X[k].K2=(X[k<<1|1].K2+(qpow(base,X[k<<1|1].len,P)*X[k<<1].K2)%mod)%mod;
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	X[k].len=r-l+1;
	if(l==r){
		X[k].K1=X[k].K2=(c[l-1]-'0');
		return ;
	}
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k,P);
}
void add(ll k,ll i,ll v){
	if(X[k].l==i&&i==X[k].r){
		X[k].K1=X[k].K2=v;
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	if(i<=mid)
	  add(k<<1,i,v);
	else
	  add(k<<1|1,i,v);
	pushup(k,P);
}
St qurey(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return {X[k].K1,X[k].K2,X[k].len};
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return qurey(k<<1,l,r);
	else if(l>mid)
	  return qurey(k<<1|1,l,r);
	else{
		St a,b,c;
		a=qurey(k<<1,l,mid);
		b=qurey(k<<1|1,mid+1,r);
		c.data=a.data+b.data;
		c.x=(a.x+(qpow(base,a.data,P)*b.x)%P)%P;
		c.y=(b.y+(qpow(base,b.data,P)*a.y)%P)%P;
		return c;
	}
}
int main(){
	n=read(),q=read();
	scanf("%s",c);
	build(1,1,n);
	while(q--){
		op=read();
		if(op==1){
			x=read();
			scanf("%c",&h);
			add(1,x,h-'0');
		}
		else{
			x=read(),y=read();
			St h=qurey(1,x,y);
			if(h.x==h.y)
			  puts("Yes");
			else
			  puts("No");
		}
	}
	return 0;
}
```


---

## 作者：SunsetLake (赞：3)

## 思路

判断一个字符串是否是回文串，可以从它的本质出发：正着读和倒着读是一样的。快速判断它正着和反着是否一样，用字符串哈希即可。又因为涉及单点修改，区间查询，那么使用线段树维护这两个值就行了。

这里讲一下如何 `pushup`。以正着的哈希值为例：我们要更新 $p$ 这个点的 $hash$ 值，已知 $p$ 的左右儿子的哈希值 $ls_{hash}$ 和 $rs_{hash}$，那么按照正常的 $hash$ 值更新右边的一坨式子应该要乘上一些 $base$，乘多少呢？因为我们是以左边为起点，当更新到 $rs$ 的左端点时左边已经乘了 $ls.r-ls.l$ 个 $base$，$rs$ 的左端点就应该乘上 $ls.r-ls.l+1$ 个 $base$。而 $rs$ 内部的值是已经算好了的，所以整体乘上 $ls.r-ls.l+1$ 个 $base$ 就好了。也就是 $base^{ls.r-ls.l+1}$。

此题也就没什么难度了。小清新线段树。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
int n,q;
const int mod=998244353;
const ll base=47;
ll pw[1000005];
char s[1000005];
struct Tree{
	int l,r;
	ll lnum,rnum;
}tr[4000005];
void pushup(int p){
	tr[p].lnum=(tr[ls].lnum+(pw[tr[ls].r-tr[ls].l+1]*tr[rs].lnum)%mod)%mod;//更新hash值
	tr[p].rnum=(tr[rs].rnum+(pw[tr[rs].r-tr[rs].l+1]*tr[ls].rnum)%mod)%mod;
}
void build(int p,int l,int r){
	tr[p].l=l;tr[p].r=r;
	if(l==r){
		tr[p].lnum=tr[p].rnum=(ll)(s[l]-'a'+1);
		return;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(p);
}
void update(int p,int x,char c){
	if(tr[p].l==tr[p].r){
		tr[p].lnum=tr[p].rnum=(ll)(c-'a'+1);
		return;
	}
	int mid=tr[p].l+tr[p].r>>1;
	if(x<=mid)update(ls,x,c);
	else update(rs,x,c);
	pushup(p);
}
Tree query(int p,int l,int r){
	if(tr[p].l>=l&&tr[p].r<=r)return tr[p];
	int mid=tr[p].l+tr[p].r>>1;
	if(r<=mid)return query(ls,l,r);
	if(l>mid)return query(rs,l,r);
	Tree ld=query(ls,l,r),rd=query(rs,l,r);//合并两段的hash值
	Tree res;
	res.l=ld.l;res.r=rd.r;
	res.lnum=(ld.lnum+(pw[ld.r-ld.l+1]*rd.lnum)%mod)%mod;
	res.rnum=(rd.rnum+(pw[rd.r-rd.l+1]*ld.rnum)%mod)%mod;
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;
	cin>>(s+1);
	pw[0]=1;
	for(int i=1;i<=n;++i)pw[i]=(pw[i-1]*base)%mod;//预处理base的次幂
	build(1,1,n);
	while(q--){
		int op,l,r,x;
		char c;
		cin>>op;
		if(op==1){
			cin>>x>>c;
			update(1,x,c);
		}
		else{
			cin>>l>>r;
			Tree now=query(1,l,r);
			if(now.lnum==now.rnum)cout<<"Yes\n";//正着读倒着读相同
			else cout<<"No\n";
		}
	}
	return 0;
}
```


---

## 作者：Coffee_zzz (赞：3)

首先我们都知道，对于一个字符串 $S$，设其正着哈希一遍得到的数是 $A$，反着哈希一遍得到的数是 $B$，那么如果 $A=B$，则 $S$ 是一个回文串。

那么这个问题就转化为了，单点修改，求区间哈希值（包括正着的和反着的）。这个东西预处理一下 $26$ 的幂然后随便用线段树维护一下即可。单模哈希可过。

```c++
#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
const int mod=998244853,N=2e6+5;
int n,q,val1[N<<2],val2[N<<2],siz[N<<2],ksm[N],num[N];
string s;
void upd(int g){
	val1[g]=(val1[g<<1]*ksm[siz[g<<1|1]]+val1[g<<1|1])%mod;
	val2[g]=(val2[g<<1|1]*ksm[siz[g<<1]]+val2[g<<1])%mod;
	siz[g]=siz[g<<1]+siz[g<<1|1];
}
void build(int g,int l,int r){
	if(l==r){
		val1[g]=num[l],val2[g]=num[r],siz[g]=1;
		return;
	}
	int m=l+r>>1;
	build(g<<1,l,m);
	build(g<<1|1,m+1,r);
	upd(g);
}
pair <int,int> ask1(int g,int l,int r,int x,int y){
	if(x<=l&&r<=y) return {val1[g],siz[g]};
	if(y<l||r<x) return {0,0};
	int m=l+r>>1;
	pair <int,int> lef=ask1(g<<1,l,m,x,y),rig=ask1(g<<1|1,m+1,r,x,y);
	return {(lef.fi*ksm[rig.se]+rig.fi)%mod,lef.se+rig.se};
}
pair <int,int> ask2(int g,int l,int r,int x,int y){
	if(x<=l&&r<=y) return {val2[g],siz[g]};
	if(y<l||r<x) return {0,0};
	int m=l+r>>1;
	pair <int,int> lef=ask2(g<<1,l,m,x,y),rig=ask2(g<<1|1,m+1,r,x,y);
	return {(rig.fi*ksm[lef.se]+lef.fi)%mod,lef.se+rig.se};
}
void solve(int g,int l,int r,int x,int v){
	if(x>r||x<l) return;
	if(x==l&&x==r){
		val1[g]=v;
		val2[g]=v;
		return;
	}
	int m=l+r>>1;
	solve(g<<1,l,m,x,v);
	solve(g<<1|1,m+1,r,x,v);
	upd(g);
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>q>>s;
	int op,l,r;
	char c;
	ksm[0]=1;
	for(int i=1;i<=n;i++) num[i]=(s[i-1]-'a'+1);
	for(int i=1;i<=n;i++) ksm[i]=ksm[i-1]*26%mod;
	build(1,1,n);
	for(int i=1;i<=q;i++){
		cin>>op;
		if(op==1){
			cin>>l>>c;
			solve(1,1,n,l,c-'a'+1);
		}
		else{
			cin>>l>>r;
			cout<<(ask1(1,1,n,l,r)==ask2(1,1,n,l,r)?"Yes":"No")<<endl;
		}
	}
	return 0;
}
```

---

## 作者：harmis_yz (赞：2)

## 分析

线段树。

每个节点维护两个值：$s[l\dots r]$ 和 $s[r \dots l]$。判断字串是否是回文直接就是询问的答案维护出来的两个值是否相同。

首先想到用线段树暴力维护。第一个值很显然是两个儿子的第一个值加起来，第二个值是反着加起来。得到很酷的代码：

```cpp
il void up(int now){
	tr[now].ls=tr[now<<1].ls+tr[now<<1|1].ls,
	tr[now].rs=tr[now<<1|1].rs+tr[now<<1].rs;
	return ;
}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(l==r) tr[now].ls=tr[now].rs=s[l-1];
	else build(now<<1,l,(l+r)>>1),build(now<<1|1,((l+r)>>1)+1,r),up(now);
	return ; 
}
il void insert(int now,int k,int c){
	if(tr[now].l==tr[now].r){tr[now].ls=tr[now].rs=c;}
	else{
		int mid=tr[now].l+tr[now].r>>1;
		if(k<=mid) insert(now<<1,k,c);
		else insert(now<<1|1,k,c);
		up(now);
	}
	return ;
}
il tree query(int now,int l,int r){
	tree ans={0,0,"",""};
	if(tr[now].l>=l&&tr[now].r<=r) return tr[now];
	int mid=tr[now].l+tr[now].r>>1;
	if(l<=mid) ans=query(now<<1,l,r);
	if(mid<r){
		tree ans1=query(now<<1|1,l,r);
		ans.ls=ans.ls+ans1.ls,ans.rs=ans1.rs+ans.rs;
	}
	return ans;
}
```
然后就 [TLE](https://atcoder.jp/contests/abc331/submissions/48189057) 了。原因是两个字符串相加复杂度太高。

考虑把字符串转化成数字。在字符串哈希中，第 $i$ 个字符的值可以被表示为 $s_i \times b^{len-i} \bmod k$。这里 $b$ 的值设一个大于 $128$ 的就行了（我记得是）。

然后就没了。改变上传的价值。定义那时候的 $len=r-l+1$，就可以把两个值算出来，即：$fa.x=lson.x \times b^{r-len}+rson.x,fa.y=rson.y\times b^{mid-l+1} +lson.y$。

询问的时候在节点右端点包含询问区间右端点时注意一下左右限制即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=1e6+10,p=1e9+7;
int n,q;
string s;
int b[N],bk=190;
struct tree{
	int l,r;
	int ls,rs;
}tr[N<<2];
il void up(int now){
	int mid=tr[now].l+tr[now].r>>1;
	tr[now].ls=(tr[now<<1].ls*b[tr[now].r-mid]%p+tr[now<<1|1].ls)%p,
	tr[now].rs=(tr[now<<1|1].rs*b[mid-tr[now].l+1]%p+tr[now<<1].rs)%p;
	return ;
}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(l==r) tr[now].ls=tr[now].rs=(s[l-1]+1-'a');
	else build(now<<1,l,(l+r)>>1),build(now<<1|1,((l+r)>>1)+1,r),up(now);
	return ; 
}
il void insert(int now,int k,int c){
	if(tr[now].l==tr[now].r){tr[now].ls=tr[now].rs=c;}
	else{
		int mid=tr[now].l+tr[now].r>>1;
		if(k<=mid) insert(now<<1,k,c);
		else insert(now<<1|1,k,c);
		up(now);
	}
	return ;
}
il tree query(int now,int l,int r){
	tree ans={0,0,0,0};
	if(tr[now].l>=l&&tr[now].r<=r) return tr[now];
	int mid=tr[now].l+tr[now].r>>1;
	if(l<=mid) ans=query(now<<1,l,r);
	if(mid<r){
		tree ans1=query(now<<1|1,l,r);
		if(l<=mid)
			ans.ls=(ans.ls*b[min(r,tr[now].r)-mid]%p+ans1.ls)%p,
			ans.rs=(ans1.rs*b[mid-max(tr[now].l,l)+1]%p+ans.rs)%p;
		else ans=ans1;
	}
	return ans;
}

il void solve(){
	cin>>n>>q>>s;
	b[0]=1;for(re int i=1;i<=n;++i) b[i]=b[i-1]*bk%p;
	build(1,1,n);
	for(re int i=1;i<=q;++i){
		int op;cin>>op;
		if(op==1){
			int k;char c;cin>>k>>c;
			insert(1,k,c+1-'a');
		}
		else{
			int l,r;cin>>l>>r;
			tree ans=query(1,l,r);
			if(ans.ls==ans.rs) cout<<"Yes\n";
			else cout<<"No\n";
		} 
	}
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：osfly (赞：2)

### some interesting things

线段树 `query` 的时候没 `return`，调了半小时。

### 正文

考虑回文串的性质，即正着读和反着读是一样的，也就是这两个字符串相等。

也就是，这两个字符串的 `hash` 值相等。

所以我们可以直接使用线段树维护正着的和反着的字符串的子串的 `hash` 值即可。

写了双哈希，`base` 值是专门设计的，这里也祝福祖国永远繁荣昌盛。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=2e6+10;

const ll m1=100000007;
const ll m2=998244353;
const ll b1=19491001;
const ll b2=19781221;

ll idx1[30],idx2[30];
void init()
{
	srand(time(0));
	mt19937 rnd(rand());
	for(int i=0;i<30;i++) idx1[i]=rnd(),idx2[i]=rnd();
}

int n,q;
int a[N];
int b[N];

struct seg
{
	struct node
	{
		int l,r,Len;
		ll v1,v2;
	}t[N<<2];
	#define ls (k<<1)
	#define rs (k<<1|1)
	#define L t[k].l
	#define R t[k].r
	#define len t[k].Len
	#define mid ((L+R)>>1)
	ll qpow(ll a,ll b,ll m)
	{
		ll res=1;
		while(b)
		{
			if(b&1) res=res*a%m;
			a=a*a%m;
			b>>=1; 
		}
		return res;
	}
	node merge(node l,node r)
	{
		node res;
		res.l=l.l,res.r=r.r;
		res.Len=res.r-res.l+1;
		res.v1=(l.v1*qpow(b1,r.Len,m1)%m1+r.v1)%m1;
		res.v2=(l.v2*qpow(b2,r.Len,m2)%m2+r.v2)%m2;
		return res;
	}
	void build(int k,int l,int r,int* p)
	{
		L=l,R=r,len=r-l+1;
		if(L==R)
		{
			t[k].v1=idx1[p[l]];
			t[k].v2=idx2[p[l]];
			return ;
		}
		build(ls,l,mid,p);
		build(rs,mid+1,r,p);
		t[k]=merge(t[ls],t[rs]);
	}
	void update(int k,int x,int num)
	{
		if(L==R)
		{
			t[k].v1=idx1[num];
			t[k].v2=idx2[num];
			return ;
		}
		if(x<=mid) update(ls,x,num);
		if(x>mid) update(rs,x,num);
		t[k]=merge(t[ls],t[rs]);
	}
	node query(int k,int l,int r)
	{
		if(l<=L&&R<=r) return t[k];
		if(r<=mid) return query(ls,l,r);
		if(l>mid) return query(rs,l,r);
		return merge(query(ls,l,mid),query(rs,mid+1,r));
	}
	#undef ls
	#undef rs
	#undef L
	#undef R
	#undef mid
};
seg tree1,tree2;

int main()
{
	init();
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		char ch;
		scanf(" %c",&ch);
		a[i]=ch-'a';
	}
	for(int i=1,j=n;i<=n;i++,j--) b[j]=a[i];
	tree1.build(1,1,n,a);
	tree2.build(1,1,n,b);
	while(q--)
	{
		int op,x,l,r;
		char ch;
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d %c",&x,&ch);
			tree1.update(1,x,ch-'a');
			tree2.update(1,n-x+1,ch-'a');
		}
		if(op==2)
		{
			scanf("%d%d",&l,&r);
			seg::node A=tree1.query(1,l,r);
			seg::node B=tree2.query(1,n-r+1,n-l+1);
			printf("%s\n",(A.v1==B.v1)&&(A.v2==B.v2)?"Yes":"No");
		}
	}
	return 0;
}
```

---

## 作者：ZnPdCo (赞：1)

这题要求动态维护字符串，结合数据范围，我们可以想到线段树，考虑线段树维护一个正向字符串和反向字符串，然后判断正向字符串是否等于反向字符串，如果是，就说明这是个回文串。

但是如果暴力储存字符串会爆空间，所以考虑直接用字符串滚动哈希来存储。

![](https://cdn.luogu.com.cn/upload/image_hosting/m750fav5.png)

```c++
#include <cstdio>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define ll long long
#define N 1000010
#define L 3
ll n, q;
char s[N];
ll base[N][L];
ll p[L] = {1145141923, 1145141969, 1145141999};
struct node {
	ll a[L];
	ll len;
} t[2][N*4];
void push_up(bool type, ll l, ll r, ll pos) {
	ll mid = (l + r) >> 1;
	for(ll i = 0; i < L; i++) {
		t[type][pos].a[i] = (t[type][ls(pos)].a[i] * base[t[type][rs(pos)].len][i] % p[i] + t[type][rs(pos)].a[i]) % p[i];
	}
	t[type][pos].len = t[type][ls(pos)].len + t[type][rs(pos)].len;
}
void build(bool type, ll l, ll r, ll pos) {
	if(l == r) {
		t[type][pos].len = 1;
		for(ll i = 0; i < L; i++) {
			if(type == 0) t[type][pos].a[i] = s[l] - 'a';
			else t[type][pos].a[i] = s[n-l+1] - 'a';
		}
		return;
	}
	ll mid = (l + r) >> 1;
	build(type, l, mid, ls(pos));
	build(type, mid+1, r, rs(pos));
	push_up(type, l, r, pos);
}
void update(bool type, ll x, ll l, ll r, ll pos, ll k) {
	if(l == r) {
		for(ll i = 0; i < L; i++) {
			t[type][pos].a[i] = k;
		}
		return;
	}
	ll mid = (l + r) >> 1;
	if(x <= mid)
		update(type, x, l, mid, ls(pos), k);
	if(mid < x)
		update(type, x, mid+1, r, rs(pos), k);
	push_up(type, l, r, pos);
}
node query(bool type, ll nl, ll nr, ll l, ll r, ll pos) {
	if(nl <= l && r <= nr) {
		return t[type][pos];
	}
	ll mid = (l + r) >> 1;
	
	node res = {0};
	
	if(nl <= mid) {
		node cnt = query(type, nl, nr, l, mid, ls(pos));
		for(ll i = 0; i < L; i++) {
			res.a[i] = (res.a[i] * base[cnt.len][i] % p[i] + cnt.a[i]) % p[i];
		}
		res.len += cnt.len;
	}	
	if(mid < nr) {
		node cnt = query(type, nl, nr, mid+1, r, rs(pos));
		for(ll i = 0; i < L; i++) {
			res.a[i] = (res.a[i] * base[cnt.len][i] % p[i] + cnt.a[i]) % p[i];
		}
		res.len += cnt.len;
	}
	return res;
}
int main() {
	scanf("%lld %lld", &n, &q);
	scanf("%s", s+1);
	
	base[0][0] = base[0][1] = base[0][2] = 1;
	for(ll i = 1; i <= n; i++) {
		for(ll j = 0; j < L; j++) {
			base[i][j] = base[i-1][j] * 26 % p[j];
		}
	}
	
	build(0, 1, n, 1);
	build(1, 1, n, 1);
	
	while(q--) {
		ll op;
		scanf("%lld", &op);
		if(op == 1) {
			ll x;
			char c[10];
			scanf("%lld %s", &x, c);
			update(0, x, 1, n, 1, c[0]-'a');
			update(1, n-x+1, 1, n, 1, c[0]-'a');
		} else {
			ll l, r;
			scanf("%lld %lld", &l, &r);
			node res1 = query(0, l, r, 1, n, 1);
			node res2 = query(1, n-r+1, n-l+1, 1, n, 1);
			bool flag = true;
			for(ll i = 0; i < L; i++) {
				if(res1.a[i] != res2.a[i]) {
					flag = false;
				}
			}
			if(flag) printf("Yes\n");
			else printf("No\n");
		}
	}
} 
```

---

同时这题没有卡内建函数（也卡不了），所以可以直接[用内建函数水过去](https://atcoder.jp/contests/abc331/submissions/48150433)。

---

## 作者：FireRain (赞：1)

# 思路

套路题，需要 $\Theta(1)$ 判断一个序列是否与另一个序列相同，通常来说需要考虑哈希。

只需要用线段树维护一下当前区间正着的哈希值与倒着的哈希值，然后判断两个数是否相等。

如果相等，说明此区间回文；否则不回文。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define ull unsigned long long

using namespace std;

const int N = 1e6 + 10;
int n,q;
ull base,pw[N];
string s;

inline void init(){
    base = 102401027;
    pw[0] = 1;
    for (re int i = 1;i <= 1e6;i++) pw[i] = pw[i - 1] * base;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        ull sum[2];
    }tr[N << 2];

    inline void pushup(int u){
        int mid = tr[u].l + tr[u].r >> 1;
        tr[u].sum[0] = tr[ls(u)].sum[0] * pw[tr[u].r - mid] + tr[rs(u)].sum[0];
        tr[u].sum[1] = tr[ls(u)].sum[1] + tr[rs(u)].sum[1] * pw[mid - tr[u].l + 1];
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r};
        if (l == r){
            tr[u].sum[0] = tr[u].sum[1] = s[l];
            return;
        }
        int mid = l + r >> 1;
        build(ls(u),l,mid);
        build(rs(u),mid + 1,r);
        pushup(u);
    }

    inline void modify(int u,int l,int r,int k){
        if (l <= tr[u].l && tr[u].r <= r){
            tr[u].sum[0] = tr[u].sum[1] = k;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(ls(u),l,r,k);
        if (r > mid) modify(rs(u),l,r,k);
        pushup(u);
    }

    inline node query(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u];
        node res;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid && r > mid){
            node a = query(ls(u),l,r);
            node b = query(rs(u),l,r);
            res.sum[0] = a.sum[0] * pw[min(r,tr[u].r) - mid] + b.sum[0];
            res.sum[1] = a.sum[1] + b.sum[1] * pw[mid - max(l,tr[u].l) + 1];
        }
        else if (l <= mid) res = query(ls(u),l,r);
        else return query(rs(u),l,r);
        return res;
    }

    #undef ls
    #undef rs
}T;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init();
    cin >> n >> q >> s;
    s = ' ' + s;
    T.build(1,1,n);
    while (q--){
        int op;
        cin >> op;
        if (op == 1){
            int x;
            char k[10];
            cin >> x >> k;
            T.modify(1,x,x,k[0]);
        }
        else{
            int l,r;
            cin >> l >> r;
            auto res = T.query(1,l,r);
            if (res.sum[0] == res.sum[1]) cout << "Yes\n";
            else cout << "No\n";
        }
    }
    return 0;
}
```

---

## 作者：Phartial (赞：1)

## F

考虑如何判断一个字符串是不是回文串：只需要将其和其翻转后的字符串比较即可，如果相同则代表该字符串是回文串，反之则不是回文串。

判断两个字符串是否相同可以使用字符串哈希，使用线段树维护 $S$ 和 $\operatorname{rev}(S)$ 的区间哈希即可。自然溢出能过。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using uLL = unsigned long long;

const int kN = 1e6 + 1;
const uLL kB = 131;
uLL kP[kN];
int I = []() {
  for (int i = kP[0] = 1; i < kN; ++i) {
    kP[i] = kP[i - 1] * kB;
  }
  return 0;
}();

struct H {
  int l;
  uLL v;

  H(int l = 0, uLL v = 0) : l(l), v(v) {}
  H(char ch) : l(1), v(ch) {}
  H operator+(const H &o) const { return H(l + o.l, v * kP[o.l] + o.v); }
} e[2][kN << 2];
int n, q;
string s[2];

void B(int o, int x, int l, int r) {
  if (l == r) {
    e[o][x] = H(s[o][l]);
    return;
  }
  int m = l + r >> 1;
  B(o, x * 2, l, m), B(o, x * 2 + 1, m + 1, r);
  e[o][x] = e[o][x * 2] + e[o][x * 2 + 1];
}
void U(int o, int x, int l, int r, int t, char c) {
  if (l == r) {
    e[o][x] = H(c);
    return;
  }
  int m = l + r >> 1;
  if (t <= m) {
    U(o, x * 2, l, m, t, c);
  } else {
    U(o, x * 2 + 1, m + 1, r, t, c);
  }
  e[o][x] = e[o][x * 2] + e[o][x * 2 + 1];
}
H Q(int o, int x, int l, int r, int tl, int tr) {
  if (l == tl && r == tr) {
    return e[o][x];
  }
  int m = l + r >> 1;
  H s;
  if (tl <= m) {
    s = s + Q(o, x * 2, l, m, tl, min(m, tr));
  }
  if (m < tr) {
    s = s + Q(o, x * 2 + 1, m + 1, r, max(m + 1, tl), tr);
  }
  return s;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q >> s[0];
  s[1] = s[0], reverse(s[1].begin(), s[1].end());
  s[0] = "#" + s[0], s[1] = "#" + s[1];
  B(0, 1, 1, n), B(1, 1, 1, n);
  for (int o; q--; ) {
    cin >> o;
    if (o == 1) {
      int x;
      char c;
      cin >> x >> c;
      U(0, 1, 1, n, x, c), U(1, 1, 1, n, n - x + 1, c);
    } else {
      int l, r;
      cin >> l >> r;
      cout << (Q(0, 1, 1, n, l, r).v == Q(1, 1, 1, n, n - r + 1, n - l + 1).v ? "Yes" : "No") << '\n';
    }
  }
  return 0;
}
```

---

## 作者：AlicX (赞：1)

## Solution 

如何快速判定回文？字符串哈希即可。

定义 $f1(s)=\sum_{i=1}^{n}s_i\times x^{i}$，$f2(s)=\sum_{i=1}^{n}s_i\times x^{n-i+1}$，则判定一个字符串相等的条件即为：$f1(s)=f2(s)$。

接下来的操作就是维护一个前缀和即可。注意在判定 $l\sim r$ 是否为回文串时，应做如下操作：令 $len$ 为区间长度的一半，$w1$ 为 $l \sim l+len-1$ 的 $f1$ 函数的和，$w2$ 为 $r-len+1\sim r$ 的 $f2$ 函数的和，然后 $w2 \gets w2 \times x^{l-1}$，$w1 \gets w1\times x^{n-r}$，也就是调整因为 $x^{l-1}$ 和 $x^{n-r}$ 不同产生的偏差。

```cpp
#include<bits/stdc++.h> 
#define int unsigned long long
#define x first 
#define y second 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=1e6+10,K=1917; 
int n,m; 
int a[N]; 
int Base[N]; 
struct Node{ 
	int l,r,w[2]; 
}tr[N<<2]; 
void pushup(int u){ 
	for(int i=0;i<=1;i++) tr[u].w[i]=tr[u<<1].w[i]+tr[u<<1|1].w[i]; 
} 
void build(int u,int l,int r){ 
	tr[u]={l,r,{0,0}}; 
	if(l==r) return ; int mid=l+r>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
	pushup(u); 
} 
void modify(int u,int x,int w,int k){ 
	if(tr[u].l==tr[u].r){ tr[u].w[k]+=w; return ; } 
	int mid=tr[u].l+tr[u].r>>1; 
	if(x<=mid) modify(u<<1,x,w,k); 
	else modify(u<<1|1,x,w,k); 
	pushup(u); 
} 
int query(int u,int l,int r,int k){ 
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u].w[k]; 
	int w=0,mid=tr[u].l+tr[u].r>>1; 
	if(l<=mid) w=query(u<<1,l,r,k); 
	if(r>mid) w+=query(u<<1|1,l,r,k); 
	return w; 
} 
signed main(){ char c; 
	cin>>n>>m; Base[0]=1; 
	for(int i=1;i<=n;i++) cin>>c,a[i]=c-'a'+1; 
	for(int i=1;i<=n;i++) Base[i]=Base[i-1]*K; build(1,1,n); 
	for(int i=1;i<=n;i++) modify(1,i,a[i]*Base[i],0),modify(1,i,a[i]*Base[n-i+1],1); 
//	for(int i=1;i<=n;i++) cout<<Base[i]<<" "; cout<<endl; 
//	for(int i=1;i<=n;i++) cout<<a[i]*Base[i]<<" "; cout<<endl; 
//	for(int i=1;i<=n;i++) cout<<a[i]*Base[n-i+1]<<" "; cout<<endl; 
	while(m--){ 
		int opt,x,y; 
		cin>>opt>>x; 
		if(opt==1){ 
			cin>>c; y=c-'a'+1; 
			int w1=Base[x]*(y-a[x]); 
			int w2=Base[n-x+1]*(y-a[x]); 
			modify(1,x,w1,0); modify(1,x,w2,1); a[x]=y; 
		} else{ 
			cin>>y; int len=(y-x+1)/2; 
			int w1=query(1,x,x+len-1,0),w2=query(1,y-len+1,y,1); 
			w1*=Base[n-(y+1)+1],w2*=Base[x-1]; 
			printf("%s\n",(w1==w2)?"Yes":"No"); 
		} 
	} return 0; 
} /*
7 1
abcbacb
2 1 5

*/
```


---

## 作者：xz001 (赞：0)

- 首先我们发现一个字符串是回文串，那么它的反串一定和它一样。反之，如果一个字符串正串和反串相同，那么它一定是回文串。
- 所以我们可以用线段树维护正串和反串的哈希值，判断其是否相同即可，修改时因为只有单点修改所以直接递归到线段树底修改，回溯时 ```push_up``` 即可。
- 时间复杂度 $O(q\log_2n)$，代码如下：

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define lowbit(x) ((x)&(-(x)))
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
using namespace std;
int n, q, c[3000005], sum1, sum2;
char s[3000005];
struct node {
	int l, r, sum;
};

node t[4000005], tt[4000005];

void push_up (int p) {
	t[p].sum = t[ls(p)].sum * c[t[rs(p)].r - t[rs(p)].l + 1] + t[rs(p)].sum;
	tt[p].sum = tt[rs(p)].sum * c[t[ls(p)].r - t[ls(p)].l + 1] + tt[ls(p)].sum;
	return;
}

void build (int l, int r, int p) {
	t[p].l = l, t[p].r = r;
	tt[p].l = l, tt[p].r = r;
	if (l == r) {
		t[p].sum = s[l];
		tt[p].sum = s[l];
		return;
	}
	int mid = (l + r) >> 1;
	build (l, mid, ls(p));
	build (mid + 1, r, rs(p));
	push_up(p);
	return;
}

void update (int x, int p, char ttt) {
	if (tt[p].l == tt[p].r) {
		t[p].sum = ttt;
		tt[p].sum = ttt;
		return;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	if (x <= mid) update (x, ls(p), ttt);
	else update (x, rs(p), ttt);
	push_up(p);
	return;
} 

void query1 (int l, int r, int p) {
	if (l <= t[p].l && t[p].r <= r) {
		sum1 = sum1 * c[t[p].r - t[p].l + 1] + t[p].sum;
		return;
	}
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) query1 (l, r, ls(p));
	if (r >  mid) query1 (l, r, rs(p));
	return;
}

void query2 (int l, int r, int p) {
	if (l <= tt[p].l && tt[p].r <= r) {
		sum2 = sum2 * c[tt[p].r - tt[p].l + 1] + tt[p].sum;
		return;
	}
	int mid = (tt[p].l + tt[p].r) >> 1;
	if (r >  mid) query2 (l, r, rs(p));
	if (l <= mid) query2 (l, r, ls(p));
	return;
}

signed main() {
	c[0] = 1;
	for (int i = 1; i <= 2e6; ++ i) c[i] = c[i - 1] * 1145141;
	scanf("%llu%llu%s", &n, &q, s + 1);
    build (1, n, 1);
    while (q -- ) {
    	int op;
    	scanf("%llu", &op);
    	if (op == 1) {
    		int x;
    		char d[2];
    		scanf("%llu%s", &x, d);
    		update (x, 1, d[0]);
		} else {
			int l, r;
			scanf("%llu%llu", &l, &r);
			if (l == r) {
				printf("Yes\n");
				continue;
			}
			if ((r - l + 1) & 1) {
				int mid = (l + r) >> 1;
				sum1 = sum2 = 0;
				query1 (l, r, 1);
				query2 (l, r, 1);
				if (sum1 == sum2) {
					printf("Yes\n");
				} else {
					printf("No\n");
				}
			} else {
				int mid = (l + r) >> 1;
				sum1 = sum2 = 0;
				query1 (l, r, 1);
				query2 (l, r, 1);
				if (sum1 == sum2) {
					printf("Yes\n");
				} else {
					printf("No\n");
				}
			}
		}
	}
    return 0;
}


```


---

## 作者：Drimpossible (赞：0)

## 题意
给一个长为 $N$ $(N \leq 10^6)$ 的字符串，$Q$ $(Q \leq 10^5)$ 次操作，每次操作修改一个位置的字符或查询某个区间是否为回文。

## 思路
首先看到回文，由于回文串的性质是正串等于反串。所以我们思考如何快速判断一个区间等于它的反串，发现可以将原串翻转，每次只需要判断一个区间在原串和新串的对应位置相同就可以了。

想到这里哈希的思路就显然了。具体地，维护一个正着的哈希，一个反着的哈希，每次判断区间和是否相等，注意一下要把前面多乘的 $base$ 除掉。

这里需要用一个支持单点修改，区间求和的数据结构，随便用 BIT 或 SGT 维护一下就行了

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define ull unsigned long long
const int N=1e6+5;
const int bse=131,mod=1e9+7;
int n,q;
char a[N];
int pw[N],h1[N],h2[N],inv[N];
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1)(res*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return res;
}
int lowbit(int x){return x&-x;}
struct BIT{
	int c[N];
	void add(int p,int x){
		while(p<=n)(c[p]+=x)%=mod,p+=lowbit(p);
		return;
	}
	int qry(int p){
		int res=0;
		while(p)(res+=c[p])%=mod,p-=lowbit(p);
		return res;
	}
}t1,t2;
signed main(){
	cin>>n>>q>>(a+1);
	pw[0]=inv[0]=1;
	for(int i=1;i<=n;i++)
		pw[i]=pw[i-1]*bse%mod,
		inv[i]=qpow(pw[i],mod-2);
	for(int i=1;i<=n;i++)
		h1[i]=(a[i]-'a'+1)*pw[i]%mod,
		h2[i]=(a[i]-'a'+1)*pw[n-i+1]%mod;
	for(int i=1;i<=n;i++)
		t1.add(i,h1[i]),t2.add(i,h2[i]);
	int opt,x,y;
	char c;
	while(q--){
		cin>>opt;
		if(opt==1){
			cin>>x>>c;
			t1.add(x,mod-h1[x]),t2.add(x,mod-h2[x]);
			h1[x]=(c-'a'+1)*pw[x]%mod,h2[x]=(c-'a'+1)*pw[n-x+1]%mod;
			t1.add(x,h1[x]),t2.add(x,h2[x]);
		}
		else {
			cin>>x>>y;
			int s1=(t1.qry(y)+mod-t1.qry(x-1))%mod*inv[x-1]%mod;//把前面多的base除掉
			int s2=(t2.qry(y)+mod-t2.qry(x-1))%mod*inv[n-y]%mod;
			if(s1==s2)puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
```


---

## 作者：wyyqwq (赞：0)

题意比较清晰，不解释了。

考虑线段树维护字符串的哈希值，若一个字符串的正着哈希值和反着的哈希值相等，那么这个字符串是回文的，这样可以 $O(1)$ 判断回文串。重载一下运算符做起来会比较简单。

竟然没卡哈希（
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 7;
const int P = 233;
typedef unsigned long long ull;
ull k[N];
struct tree{
    int l, r;
    ull sum1, sum2;
}T[N << 2];
string s;
tree operator + (tree a, tree b){
    return {a.l, b.r, a.sum1 * k[b.r - b.l + 1] + b.sum1, b.sum2 * k[a.r - a.l + 1] + a.sum2};
}
void pushup(int rt){
    T[rt] = T[rt << 1] + T[rt << 1 | 1];
}
void build(int l, int r, int rt = 1){
    T[rt].l = l, T[rt].r = r;
    if(l == r){
        T[rt].sum1 = T[rt].sum2 = s[l] - 'a' + 1;
        return;
    }
    int mid = l + r >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    pushup(rt);
}
void modify(int p, int x, int rt = 1){
    if(T[rt].l == T[rt].r){
        T[rt].sum1 = T[rt].sum2 = x;
        return;
    }
    int mid = T[rt].l + T[rt].r >> 1;
    if(p <= mid) modify(p, x, rt << 1);
    else modify(p, x, rt << 1 | 1);
    pushup(rt);
}
tree query(int l, int r, int rt = 1){
    if(l <= T[rt].l && r >= T[rt].r){
        return T[rt];
    }
    int mid = T[rt].l + T[rt].r >> 1;
    if(r <= mid) return query(l, r, rt << 1);
    if(l > mid) return query(l, r, rt << 1 | 1);
    return query(l, r, rt << 1) + query(l, r, rt << 1 | 1);
}
int main(){
    int n, q;
    cin >> n >> q;
    k[0] = 1;
    for(int i = 1; i <= n; i ++){
        k[i] = k[i - 1] * P;
    }

    cin >> s;
    s = ' ' + s;
    build(1, n);
    for(int i = 1; i <= q; i ++){
        int pos;
        cin >> pos;
        if(pos == 1){
            int x;
            string c;
            cin >> x >> c;
            modify(x, c[0] - 'a' + 1);
        }
        else{
            tree ans;
            int l, r;
            cin >> l >> r;
            ans = query(l, r);
            if(ans.sum1 == ans.sum2){
                cout << "Yes" << endl;
            }
            else cout << "No" << endl;
        }
    }

}
```


---

## 作者：naroanah (赞：0)

很典的题，判断某个字符串是否回文，可以采用字符串哈希，维护正反哈希值，判断正向哈希值和反向哈希值是否相等即可。哈希值可以使用线段树简单维护。


```cpp
#include<bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define req(i, r, l) for(int i = (r); i >= (l); i--)
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
constexpr int N = 1e6 + 10, inf = 0x3f3f3f3f, INF = 0x7f7f7f7f; constexpr double eps = 1e-9;
constexpr int b1 = 233333, b2 = 11145141, m1 = 1e9 + 9, m2 = 998244353;
ll p1[N], p2[N];
struct Hash {
    ll h1, h2; int len;
};
Hash operator + (const Hash &x, const Hash &y) {
    Hash res; res.len = x.len + y.len;
    res.h1 = (x.h1 + y.h1 * p1[x.len] % m1) % m1;
    res.h2 = (x.h2 + y.h2 * p2[x.len] % m2) % m2;
    return res;
}
bool operator == (const Hash &x, const Hash &y) {
    return x.len == y.len && x.h1 == y.h1 && x.h2 == y.h2;
}
Hash tr[N << 2], ty[N << 2];
int n, q;
string a;
#define ls (k << 1)
#define rs (k << 1 | 1)
void pp(int k) {tr[k] = tr[ls] + tr[rs]; ty[k] = ty[rs] + ty[ls];}
void build(int k = 1, int l = 1, int r = n) {
    if(l == r) return tr[k] = {a[l] * b1, a[l] * b2, 1}, ty[k] = tr[k], void();
    int mid = l + r >> 1; build(ls, l, mid); build(rs, mid + 1, r); pp(k);
}
void modify(int x, char c, int k = 1, int l = 1, int r = n) {
    if(l == r) return tr[k] = {c * b1, c * b2, 1}, ty[k] = tr[k], void();
    int mid = l + r >> 1; x <= mid ? modify(x, c, ls, l, mid) : modify(x, c, rs, mid + 1, r); pp(k);
}
Hash query1(int x, int y, int k = 1, int l = 1, int r = n) {
    if(x <= l && r <= y) return tr[k];
    int mid = l + r >> 1; Hash res = {0, 0, 0};
    if(x <= mid) res = res + query1(x, y, ls, l, mid);
    if(y > mid) res = res + query1(x, y, rs, mid + 1, r);
    return res;
}
Hash query2(int x, int y, int k = 1, int l = 1, int r = n) {
    if(x <= l && r <= y) return ty[k];
    int mid = l + r >> 1; Hash res = {0, 0, 0};
    if(x <= mid) res =  query2(x, y, ls, l, mid) + res;
    if(y > mid) res = query2(x, y, rs, mid + 1, r) + res;
    return res;
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> q;
    cin >> a; a = " " + a;
    p1[0] = p2[0] = 1;
    rep(i, 1, n) p1[i] = p1[i - 1] * b1 % m1, p2[i] = p2[i - 1] * b2 % m2;
    build();
    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            int x; char c; cin >> x >> c; modify(x, c);
        }
        else {
            int l, r; cin >> l >> r; 
            if(query1(l, r) == query2(l, r)) cout << "Yes\n";
            else cout << "No\n";
        }
    }
    return 0;
}
```

---

## 作者：sgl654321 (赞：0)

### 闲话
第一次打 atcoder ABC，有幸在简单场场切 $6$ 题。

### 题目大意
给定一个字符串，两种操作：
1. 修改某一位置的字符
2. 查询某一子串是否为回文串。

### 解题思路
判断一个串是否为回文串，等价于判断它正着读和倒着读是不是一样的。

判断两个字符串是否完全一致，可以近似等价于判断它的正哈希值和负哈希值是否一致。


哈希值是满足可加性的。具体的，我们假设有一个哈希函数 $\text{hash}(S)$，其进制为 $bs$。

设 $\text{hash}(S_1)=h_1,\text{hash}(S_2)=h_2$。我们有 $\text{hash}(S_1+S_2)=h_1\times bs^{\text{len}(S_2)}+h_2$，其中 $S_1+S_2$ 表示把这两个字符串拼接起来。

要维护有可加性的区间信息，第一步就想到的是线段树。

我们分别维护每个子串正着的哈希值和反着的哈希值，修改和查询都是 $O(\log n)$ 的。这样就可以判断一个子串是否是回文串了。

### 参考代码
我实现上使用了双哈希技巧。
```cpp
#include<bits/stdc++.h>
#define maxn 1000010
using namespace std;
typedef long long ll;
const ll base=2333;
const ll mod1=998244353;
const ll mod2=123456791;
struct xianduanshu{
	ll l,r,val1,val2;
}t[2][maxn<<2];
ll n,q,bas1[maxn],bas2[maxn],op,x,y;
ll ans1,ans2,zheng1,zheng2,fu1,fu2;
char a[maxn],c;
ll len(ll tg,ll i){
	return t[tg][i].r-t[tg][i].l+1;
}
void pushup(ll tg,ll i){
	t[tg][i].val1=(t[tg][i*2].val1*bas1[len(tg,i*2+1)]%mod1+
	t[tg][i*2+1].val1)%mod1;
	t[tg][i].val2=(t[tg][i*2].val2*bas2[len(tg,i*2+1)]%mod2+
	t[tg][i*2+1].val2)%mod2;
}
void build(ll tg,ll i,ll l,ll r){
	t[tg][i].l=l;t[tg][i].r=r;
	if(l==r){
		if(tg==0)t[tg][i].val1=t[tg][i].val2=a[l];
		else t[tg][i].val1=t[tg][i].val2=a[n+1-l];
		return;
	}
	ll mid=(l+r)>>1;
	build(tg,i*2,l,mid);build(tg,i*2+1,mid+1,r);
	pushup(tg,i);
}
void xiugai(ll tg,ll i,ll x,ll k){
	if(t[tg][i].l<=x&&t[tg][i].r>=x){
		if(t[tg][i].l==t[tg][i].r){
			t[tg][i].val1=t[tg][i].val2=k;
			return;
		}
		xiugai(tg,i*2,x,k);xiugai(tg,i*2+1,x,k);
		pushup(tg,i);
	}
} 
void chaxun(ll tg,ll i,ll x,ll y){
	if(x<=t[tg][i].r&y>=t[tg][i].l){
		if(x<=t[tg][i].l&&y>=t[tg][i].r){
			ans1=ans1*bas1[t[tg][i].r-t[tg][i].l+1]%mod1+
			t[tg][i].val1;
			ans1%=mod1;
			ans2=ans2*bas2[t[tg][i].r-t[tg][i].l+1]%mod2+
			t[tg][i].val2;
			ans2%=mod2;
			return;
		}
		chaxun(tg,i*2,x,y);chaxun(tg,i*2+1,x,y);
	}	
}
int main(){
	cin>>n>>q;
	bas1[0]=bas2[0]=1;
	for(int i=1;i<=n;i++)
		cin>>a[i],
		bas1[i]=bas1[i-1]*base%mod1,
		bas2[i]=bas2[i-1]*base%mod2;
	
	build(0,1,1,n);build(1,1,1,n);
	while(q--){
		cin>>op;
		if(op==1){
			cin>>x>>c;
			xiugai(0,1,x,c);xiugai(1,1,n+1-x,c);
		}else{
			cin>>x>>y;
			ans1=ans2=0;
			chaxun(0,1,x,y);
			zheng1=ans1;zheng2=ans2;
			
			ans1=ans2=0;
			chaxun(1,1,n+1-y,n+1-x);
			fu1=ans1;fu2=ans2;
			
		//	cout<<zheng1<<" "<<zheng2<<endl;
		//	cout<<fu1<<" "<<fu2<<endl;
			if(zheng1==fu1&&zheng2==fu2)
				cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
	return 0;
}
```


---

