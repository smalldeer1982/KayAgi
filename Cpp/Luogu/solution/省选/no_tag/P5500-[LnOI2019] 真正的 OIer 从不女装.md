# [LnOI2019] 真正的 OIer 从不女装

## 题目背景

题目提供者：朝田诗乃

众所周知，女装只有零次和无数次。

## 题目描述

给定一个长度为 $n$ 的序列 $a$。

有如下定义：若一个序列中所有数字都一样，那么这个序列被称作“诗乃序列”。

对于每次询问，给定 $l$ 和 $r$，求序列 $a$ 中**左右端点都在 $[l,r]$ 中**的最长“诗乃序列”长度。

这题难倒了 Abbi。Abbi 决定女装。当 Abbi 女装时，序列会出现神奇的变化：它可以**在询问的区间 $[l,r]$ 中**挑一个它喜欢的位置 $p$，将区间 $[l,p]$ 和 $(p,r]$ **分别**翻转。

Abbi 想知道，**最多**进行 $k$ 次女装后（可选择进行不足 $k$ 次或不进行女装），能得到的最长的“诗乃序列”的长度是多少？

## 说明/提示

**时空限制**：1s/512MB。

**数据范围：**

- 对于 $20\%$ 的数据，$1 ≤ n,m ≤ 100$。
- 对于另外 $10\%$ 数据，所有询问的 $k=0$。
- 对于另外 $10\%$ 数据，没有 R 操作。
- 对于 $100\%$ 的数据，$1≤n,m≤200000$，$0≤k≤1000$，$1≤a_i,x≤10^9$，$1≤l≤r≤n$。

特殊限制：对于后 $80\%$ 的数据，保证能卡飞 ODT。

**样例解释：**

对于第一次询问，询问的区间为：

```
3 3 3 3 2 3
```

女装 $1$ 次，将区间 $[1,4]$ 和 $[5,6]$ 分别翻转，得到：

```
3 3 3 3 3 2
```

此时可得到最长“诗乃序列”，长度为 $5$。可以证明没有别的女装方法能得到更长的“诗乃序列”。

此后询问以此类推。

**建议使用读入优化。**

## 样例 #1

### 输入

```
10 4
3 3 3 3 2 3 3 3 2 2
Q 1 6 1
Q 1 6 0
R 8 8 2
Q 5 10 1```

### 输出

```
5
4
4```

# 题解

## 作者：诗乃 (赞：13)

我们发现，$\forall k>0, Ans_{k} = Ans_{1}$，其中 $Ans_{j}$表示正好反转$j$次的最大答案。所以对于本题，$k=0$和$k\neq 0$分开讨论即可。

为什么$\forall k>0, Ans_{k} = Ans_{1}$呢？

假设序列为 $\underrightarrow{1}\underrightarrow{2}\underrightarrow{3}$；


从某个位置翻转后变成： $\underleftarrow{2}\underleftarrow{1}\underleftarrow{3}$；

将序列整个翻转对答案没有影响，即： $\underrightarrow{3}\underrightarrow{1}\underrightarrow{2}$；

即一次翻转与把序列开头的某一段接到序列后面等效。因此， $\forall k>0, Ans_{k} = Ans_{1}$

我们发现翻转两次等于翻转一次，那么这样推出翻转多次等于翻转一次。

使用线段树来维护区间最长颜色段。对于所有$k \neq 0$且询问区间左右端点颜色相同的询问，将区间最长颜色段与询问区间左右最长颜色段长度的和取max即可。

代码（很丑）：

```cpp
#include <bits/stdc++.h>
#define L(u) (u<<1)
#define R(u) (u<<1|1)
using namespace std;

const int MAXN = 200050;
void read(int &x) {
	char ch; while(ch = getchar(), ch < '!'); x = ch - 48;
	while(ch = getchar(), ch > '!') x = (x << 3) + (x << 1) + ch - 48;
}

struct Segment_Tree {
	int lcol, rcol, col, lmax, rmax, v;
} t[MAXN << 2];
int n, m, a[MAXN];

void pushup(int u, int l, int r) {
	int mid = (l + r) >> 1;
	if(t[L(u)].col != t[R(u)].col || t[L(u)].col == -1 || t[R(u)].col == -1) t[u].col = -1;
	else t[u].col = t[L(u)].col;
	t[u].lcol = t[L(u)].lcol; t[u].rcol = t[R(u)].rcol;
	if(t[L(u)].col != -1 && t[L(u)].col == t[R(u)].lcol) t[u].lmax = (mid-l+1)+t[R(u)].lmax;
	else t[u].lmax = t[L(u)].lmax;
	if(t[R(u)].col != -1 && t[R(u)].col == t[L(u)].rcol) t[u].rmax = (r-mid)+t[L(u)].rmax;
	else t[u].rmax = t[R(u)].rmax;
	t[u].v = max(t[L(u)].v, t[R(u)].v);
	if(t[L(u)].rcol == t[R(u)].lcol) t[u].v = max(t[u].v, t[L(u)].rmax + t[R(u)].lmax);
}

void cover(int u, int l, int r, int c) {
	//cout << l << " " << r << " " << c << endl;
	t[u].col = t[u].lcol = t[u].rcol = c;
	t[u].v = t[u].lmax = t[u].rmax = r-l+1;
}

void pushdown(int u, int l, int r) {
	if(t[u].col != -1) {
		int mid = (l + r) >> 1;
		cover(L(u), l, mid, t[u].col);
		cover(R(u), mid+1, r, t[u].col);
	}
}

void build(int u, int l, int r) {
	if(l == r) {
		t[u].lcol = t[u].rcol = t[u].col = a[l];
		t[u].lmax = t[u].rmax = 1; t[u].v = 1;
		//cout << l << " " << r << " " << t[u].v << " " << t[u].lcol << " " << t[u].rcol << " " << t[u].lmax << " " << t[u].rmax << endl; 
		return;
	}
	int mid = (l + r) >> 1;
	build(L(u), l, mid); build(R(u), mid+1, r);
	pushup(u, l, r);
	//cout << l << " " << r << " " << t[u].v << " " << t[u].lcol << " " << t[u].rcol << " " << t[u].lmax << " " << t[u].rmax << endl; 
}

void print(int u, int l, int r) {
	if(l == r) {
		cout << l << " " << r << " " << t[u].v << " " << t[u].lcol << " " << t[u].rcol << " " << t[u].lmax << " " << t[u].rmax << endl; 
		return;
	}
	int mid = (l + r) >> 1;
	print(L(u), l, mid); print(R(u), mid+1, r);
	cout << l << " " << r << " " << t[u].v << " " << t[u].lcol << " " << t[u].rcol << " " << t[u].lmax << " " << t[u].rmax << endl; 
}

void update(int u, int l, int r, int tl, int tr, int c) {
	if(tr < l || tl > r) return;
	if(tl <= l && r <= tr) {
		cover(u, l, r, c);
		return;
	}
	pushdown(u, l, r);
	int mid = (l + r) >> 1;
	update(L(u), l, mid, tl, tr, c); update(R(u), mid+1, r, tl, tr, c);
	pushup(u, l, r);
}

int query(int u, int l, int r, int tl, int tr) {
	if(tl <= l && r <= tr) return t[u].v;
	pushdown(u, l, r);
	int mid = (l + r) >> 1;
	if(tr <= mid) return query(L(u), l, mid, tl, tr);
	else if(tl > mid) return query(R(u), mid+1, r, tl, tr);
	else {
		int res = max(query(L(u), l, mid, tl, tr), query(R(u), mid+1, r, tl, tr));
		if(t[L(u)].rcol == t[R(u)].lcol) {
			int rm = min(mid-tl+1, t[L(u)].rmax), lm = min(tr-mid, t[R(u)].lmax);
			res = max(res, rm + lm);
		}
		return res;
	}
}

int Qcol(int u, int l, int r, int x) {
	if(l == r) return t[u].col;
	if(l <= x && x <= r && t[u].col != -1) return t[u].col;
	pushdown(u, l, r);
	int mid = (l + r) >> 1;
	if(x <= mid) return Qcol(L(u), l, mid, x);
	else return Qcol(R(u), mid+1, r, x);
}

int Qlmax(int u, int l, int r, int tl, int tr) {
	//cout << l << " " << r << " " << t[u].v << " " << t[u].lcol << " " << t[u].rcol << " " << t[u].lmax << " " << t[u].rmax << endl; 
	if(l <= tl && tr <= r && l + t[u].lmax - 1 >= tl) return l+t[u].lmax-tl;
	pushdown(u, l, r);
	int mid = (l + r) >> 1;
	if(tl > mid) return Qlmax(R(u), mid+1, r, tl, tr);
	else if(tr <= mid) return Qlmax(L(u), l, mid, tl, tr);
	else if(t[L(u)].rcol == t[R(u)].lcol && mid-t[L(u)].rmax+1 <= tl) return Qlmax(L(u), l, mid, tl, mid) + Qlmax(R(u), mid+1, r, mid+1, tr);
	else return Qlmax(L(u), l, mid, tl, mid);
	/*{
		if(t[L(u)].col != -1) {
			if(t[L(u)].col != t[R(u)].lcol) return mid-tl+1;
			else return mid-tl+1+Qlmax(R(u), mid+1, r, mid+1, tr);
		} else return Qlmax(L(u), l, mid, tl, mid);
	}*/
}

int Qrmax(int u, int l, int r, int tl, int tr) {
	//cout << u << " " << l << " " << r << " " << t[u].v << " " << t[u].lcol << " " << t[u].rcol << " " << t[u].lmax << " " << t[u].rmax << " " << t[u].col << endl; 
	if(l <= tl && tr <= r && r - t[u].rmax + 1 <= tr) return tr - r + t[u].rmax;
	pushdown(u, l, r);
	int mid = (l + r) >> 1;
	//cout << R(u) << " " << L(u) << " " << t[R(u)].col << " " << t[L(u)].rcol << endl;
	if(tl > mid) return Qrmax(R(u), mid+1, r, tl, tr);
	else if(tr <= mid) return Qrmax(L(u), l, mid, tl, tr);
	else if(t[R(u)].lcol == t[L(u)].rcol && mid+1+t[R(u)].lmax-1 >= tr) return Qrmax(L(u), l, mid, tl, mid) + Qrmax(R(u), mid+1, r, mid+1, tr);
	else return Qrmax(R(u), mid+1, r, mid+1, tr);
	/*{
		if(t[R(u)].col != -1) {
			if(t[R(u)].col != t[L(u)].rcol) return tr-mid;
			else return tr-mid+Qrmax(L(u), l, mid+1, tl, mid);
		} else return Qrmax(R(u), mid+1, r, mid+1, tr);
	}*/
}

int main() {
	read(n); read(m);
	for(int i = 1; i <= n; ++i) read(a[i]);
	build(1, 1, n);
	int l, r, x; char opt;
	while(m--) {
		while(opt = getchar(), opt != 'R' && opt != 'Q');
		read(l); read(r); read(x);
		if(opt == 'R') update(1, 1, n, l, r, x);
		else {
			if(x) {
				int lc = Qcol(1, 1, n, l), rc = Qcol(1, 1, n, r);
				if(lc == rc) {
					int lm = Qlmax(1, 1, n, l, r), rm = Qrmax(1, 1, n, l, r);
					//cout << lm << " " << rm << endl;
					printf("%d\n", max(query(1, 1, n, l, r), min(lm + rm, r-l+1)));
				} else printf("%d\n", query(1, 1, n, l, r));
				//print(1, 1, n);
			} else printf("%d\n", query(1, 1, n, l, r));
		}
	}
}

```

---

## 作者：Spasmodic (赞：12)

~~题名是假的！题名是假的！题名是假的！~~

非常有趣的结论题。

考虑一次女装可能造成的影响

若原区间为

$$
a_1,a_2,\dots,a_p,a_{p+1},\dots,a_n
$$

在一次女装后会变为

$$
a_p,a_{p-1},\dots,a_1,a_n,\dots,a_{p+1}
$$

由于整个翻转不会影响答案，我们可以将整个区间翻转

$$
a_{p+1},a_{p+2},\dots,a_n,a_1,a_2,\dots,a_p
$$

可以发现相当于把前 $p$ 项移到了最后。

如果把这个区间放在环上，则一次女装相当于把这个环旋转了。

因此，多次女装和一次女装没有区别。

~~这就解释了为什么女装只有零次和无限次，因为任意多次女装相当于无限次女装~~

那么我们考虑维护区间最长颜色块长度 $ma$，从左端点开始的最长颜色块长度 $lmax$，从右端点开始的最长颜色块长度 $rmax$，可以用线段树维护。

查询时如果 $k>0$ 且 $a_l=a_r$ 就用 $\min\{r-l+1,lmax+rmax\}$ 更新答案。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200005;
ll n,m,a[N],tag[N];
struct data{
	ll lcol,rcol,col,lmax,rmax,ma;
	data(ll lcol_=0,ll rcol_=0,ll col_=0,ll lmax_=0,ll rmax_=0,ll ma_=0){
		lcol=lcol_,rcol=rcol_,col=col_,lmax=lmax_,rmax=rmax_,ma=ma_;
	}
}sum[N<<2];
data operator+(const data&x,const data&y){
	data ret(x.lcol,y.rcol);
	if(x.col==y.col&&x.col!=-1)ret.col=x.col;
	else ret.col=-1;
	if(x.col==-1||x.col!=y.lcol)ret.lmax=x.lmax;
	else ret.lmax=x.lmax+y.lmax;
	if(y.col==-1||y.col!=x.rcol)ret.rmax=y.rmax;
	else ret.rmax=x.rmax+y.rmax;
	ret.ma=max(x.ma,y.ma);
	if(x.rcol==y.lcol)ret.ma=max(ret.ma,x.rmax+y.lmax);
	return ret;
}
void pushup(ll k){sum[k]=sum[k<<1]+sum[k<<1|1];}
void build(ll k,ll l,ll r){
	if(l==r){
		sum[k]=data(a[l],a[l],a[l],1,1,1);
		return;
	}
	ll mid=l+r>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
} 
void Add(ll k,ll l,ll r,ll col){
	sum[k]=data(col,col,col,r-l+1,r-l+1,r-l+1);
	tag[k]=col;
}
void pushdown(ll k,ll l,ll r,ll mid){
	if(!tag[k])return;
	Add(k<<1,l,mid,tag[k]);
	Add(k<<1|1,mid+1,r,tag[k]);
	tag[k]=0;
}
void modify(ll k,ll l,ll r,ll x,ll y,ll v){
	if(x<=l&&r<=y){
		Add(k,l,r,v);
		return;
	}
	ll mid=l+r>>1;
	pushdown(k,l,r,mid);
	if(x<=mid)modify(k<<1,l,mid,x,y,v);
	if(mid<y)modify(k<<1|1,mid+1,r,x,y,v);
	pushup(k);
}
data query(ll k,ll l,ll r,ll x,ll y){
	if(x<=l&&r<=y)return sum[k];
	ll mid=l+r>>1;
	pushdown(k,l,r,mid);
	if(mid>=y)return query(k<<1,l,mid,x,y);
	if(x>mid)return query(k<<1|1,mid+1,r,x,y);
	return query(k<<1,l,mid,x,y)+query(k<<1|1,mid+1,r,x,y);
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)scanf("%lld",&a[i]);
	build(1,1,n); 
	while(m--){
		char op[2];
		scanf("%s",op);
		if(op[0]=='Q'){
			ll l,r,k,ans;
			scanf("%lld%lld%lld",&l,&r,&k);
			data res=query(1,1,n,l,r);
			ans=res.ma;
			if(k&&res.lcol==res.rcol)ans=max(ans,min(res.lmax+res.rmax,r-l+1));
			printf("%lld\n",ans);
		}else{
			ll l,r,v;
			scanf("%lld%lld%lld",&l,&r,&v);
			modify(1,1,n,l,r,v);
		}
	}
	return 0;
} 
```

---

## 作者：liheyang123 (赞：1)

~~题目名是假的！~~

## solution
- 不翻转（$k=0$）：显然是一个线段树区间问题。
- 翻转（$k\ne 0$）：

这是一个显然的结论，现在取出一个长度为 $k$ 的区间：
$$
a_p,a_{p+1},\cdots,a_{p+k-1}
$$
假设在位置 $d$ 翻转，那么新序列为：
$$
a_d,a_{d-1},\cdots,a_{p-1},a_p,a_{p+k-1},a_{p+k-2},\cdots,a_{d+2},a_{d+1}
$$
可以观察到，实际上是相似于在一个环上找一个极大的 $res$，使得 $\exists x,\forall x\le i\le x+res-1,c_i = c_x$，此处 $c$ 表示一个环且 $\forall p\leq i \leq p+k-1,c_i=a_i$，所以**多次翻转的最大收益等同于一次翻转最大收益**，因此~~女装只有零次和无数次~~。

可以使用线段树维护长度，左侧最长的连续相同的颜色数，左侧颜色，右侧最长的连续相同的颜色数，右侧颜色，不翻转的最优解，区间修改懒标记，剩下的就仅仅是代码难度了。

[code](https://www.luogu.com.cn/paste/2bc3gkap)

---

## 作者：yhy2024 (赞：1)

考虑女装之后的变化：

$a_l,a_{l+1},\ldots,a_p,a_{p+1},\ldots,a_{r-1},a_r$

变成：

$a_p,\ldots,a_{l+1},a_l,a_r,a_{r-1},\ldots,a_{p+1}$

注意到把整个区间反转不影响答案，所以女装之后变成：

$a_{p+1},\ldots,a_{r-1},a_r,a_l,a_{l+1},\ldots,a_p$

如果把 $[l,r]$ 看作一个环，那么一次女装就是把环从 $p$ 处断开，展平成一个序列。多次女装等价于一次女装。

所以用线段树维护，$lmx$ 为 $l$ 开始最长的颜色段，$rmx$ 为 $r$ 开始最长的颜色段，$mx$ 为 $[l,r]$ 最长的颜色。

女装次数大于 0，且 $a_l=a_r$ 最后答案为 $\max(mx, \min (lmx+rmx,r-l+1))$。

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int lazy[N<<2],c[N],n,m,l,r,k;
char op;
struct Node{
	int c,lc,rc,mx,lmx,rmx;
	Node operator + (const Node &x) const{
		Node res;res.lc=lc;res.rc=x.rc;
		if(c&&x.c&&c==x.c) res.c=c;
		else res.c=0;
		if(c&&x.lc==c) res.lmx=lmx+x.lmx;
		else res.lmx=lmx;
		if(x.c&&rc==x.c) res.rmx=rmx+x.rmx;
		else res.rmx=x.rmx;
		res.mx=max(mx,x.mx);
		if(rc==x.lc) res.mx=max(rmx+x.lmx,res.mx);
		return res;
	}
}tr[N<<2];
void pushup(int k){tr[k]=tr[k<<1]+tr[k<<1|1];}
void add(int k,int l,int r,int v){
	tr[k].mx=tr[k].lmx=tr[k].rmx=(r-l+1);
	tr[k].c=tr[k].rc=tr[k].lc=v;
	lazy[k]=v;
}
void pushdown(int k,int l,int r){
	if(lazy[k]){
		int mid=l+r>>1;
		add(k<<1,l,mid,lazy[k]);
		add(k<<1|1,mid+1,r,lazy[k]);
		lazy[k]=0;
	}
}
void build(int k,int l,int r){
	if(l==r){
		tr[k].lmx=tr[k].rmx=tr[k].mx=1;
		tr[k].c=tr[k].rc=tr[k].lc=c[l];
		return;
	}
	int mid=l+r>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k); 
}
void modify(int k,int l,int r,int x,int y,int v){
	if(x<=l&&r<=y){
		add(k,l,r,v);	
		return;
	}
	int mid=l+r>>1;
	pushdown(k,l,r);
	if(x<=mid) modify(k<<1,l,mid,x,y,v);
	if(y>mid) modify(k<<1|1,mid+1,r,x,y,v);
	pushup(k);
}
Node query(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y) return tr[k];
	int mid=l+r>>1;
	Node ans;
	pushdown(k,l,r);
	if(x<=mid) ans=query(k<<1,l,mid,x,y);
	if(mid<y){
		if(x<=mid) ans=ans+query(k<<1|1,mid+1,r,x,y);		
		else ans=query(k<<1|1,mid+1,r,x,y);
	}
	return ans;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>c[i];
	build(1,1,n);
	for(int i=1;i<=m;i++){
		cin>>op>>l>>r>>k;
		if(op=='R') modify(1,1,n,l,r,k);
		else{
			Node ans=query(1,1,n,l,r);
			int res=ans.mx;
			if(k>0) if(ans.lc==ans.rc) res=max(res,min(r-l+1,ans.lmx+ans.rmx));
			cout<<res<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：qnqfff (赞：1)

### 思路

容易发现做多次翻转操作是没有意义的，因为操作后将原序列整个翻转过来发现等同于将前 $p$ 个数移到末尾，因此只要考虑做一次翻转操作。

显然翻转后的答案是最长相同的前缀加后缀的和，要保证区间第一个数和最后一个数相等。

那么直接线段树维护一下最长相同前缀，最长相同后缀，最长相同字串，左端点颜色和右端点颜色即可。

注意，翻转后的答案要和区间长度取 $\min$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m;struct node{int pre,suf,res,lc,rc,len;};struct seg{int l,r,tag;node x;}t[800010];
#define lson now<<1
#define rson now<<1|1
node merge(node a,node b){node c;c.lc=a.lc;c.rc=b.rc;c.pre=a.pre+(a.pre==a.len&&a.rc==b.lc)*b.pre;c.suf=b.suf+(b.suf==b.len&&b.lc==a.rc)*a.suf;c.res=max({a.res,b.res,(a.rc==b.lc)*(a.suf+b.pre)});c.len=a.len+b.len;return c;}
void build(int now,int l,int r){
	t[now].l=l;t[now].r=r;if(l==r){int v=read();t[now].x={1,1,1,v,v,1};return ;}
	int mid=(l+r)>>1;build(lson,l,mid);build(rson,mid+1,r);t[now].x=merge(t[lson].x,t[rson].x);
}
void puttag(int now,int v){t[now].tag=v;t[now].x={t[now].x.len,t[now].x.len,t[now].x.len,v,v,t[now].x.len};}
void pushdown(int now){if(!t[now].tag) return ;puttag(lson,t[now].tag);puttag(rson,t[now].tag);t[now].tag=0;}
void modify(int now,int l,int r,int v){
	if(l<=t[now].l&&t[now].r<=r){puttag(now,v);return ;}
	pushdown(now);int mid=(t[now].l+t[now].r)>>1;if(l<=mid) modify(lson,l,r,v);if(mid<r) modify(rson,l,r,v);t[now].x=merge(t[lson].x,t[rson].x);
}
node query(int now,int l,int r){
	if(l<=t[now].l&&t[now].r<=r) return t[now].x;
	pushdown(now);int mid=(t[now].l+t[now].r)>>1;if(r<=mid) return query(lson,l,r);else if(mid<l) return query(rson,l,r);else return merge(query(lson,l,r),query(rson,l,r));
}
signed main(){
	n=read();m=read();build(1,1,n);while(m--){char opt;cin>>opt;int l=read(),r=read(),k=read();if(opt=='R') modify(1,l,r,k);else{auto tmp=query(1,l,r);if(!k||tmp.lc!=tmp.rc) cout<<tmp.res<<'\n';else cout<<max(tmp.res,min(tmp.len,tmp.pre+tmp.suf))<<'\n';}}
	return 0;
}
```

---

## 作者：AtomAlpaca (赞：1)

## 题意

给定一个长度为 $n$ 的序列 $a$。支持以下两种操作：

1. 区间覆盖；
2. 询问区间进行不超过 $k$ 次女装操作后，每个元素都相等的子串长度最大值。

其中一次区间女装操作指在区间 $[l,r]$ 内任选位置 $p$，将区间 $[l,p]$ 和 $(p,r]$ 分别翻转。

$1 \le n,m \le 200000$

## 题解

首先我们考虑每次“女装”操作其实就是把当前区间首尾相接成一个环，然后选一个地方把它断掉再展平成一个序列。因此多次“女装”其实答案不会更优。因此只有女装和不女装的区别。

没有女装操作是简单的，考虑有女装操作怎么做。

我们发现把区间接成一个环之后，只会在原来右侧值和左侧值相等时，多出一个原来的右侧相等连续段和左侧极长相等段拼出来的一个子串，可能比原来的答案更优。因此我们考虑用线段树维护区间左、右侧极长相等段和区间极长相等段即可。

## 代码

记得注意左、右侧极长相等段可能重合，要和询问区间长度取 $\min$。

```cpp
#include <bits/stdc++.h>

const int MAX = 2e5 + 5;
char op;
int l, r, c, k, n, m, a[MAX];

struct N
{
  int l, r, lv, rv, lm, rm, mx, tg = 0;
  void pu(N l, N r)
  {
    this -> l = l.l; this -> r = r.r; lm = l.lm; rm = r.rm; lv = l.lv; rv = r.rv; mx = std::max(l.mx, r.mx);
    if (l.rv == r.lv)
    { 
      mx = std::max(mx, l.rm + r.lm);
      if (l.lm == l.r - l.l + 1) { lm = std::max(lm, l.lm + r.lm); }
      if (r.rm == r.r - r.l + 1) { rm = std::max(rm, r.rm + l.rm); }
    }
  }

  void mdf(int x) { lm = rm = mx = r - l + 1; lv = rv = tg = x; }
  
  void pd(N & l, N & r)
  {
    l.mdf(tg); r.mdf(tg);
    tg = 0;
  }
} st[MAX << 2];

void build(int l, int r, int x)
{
  st[x].l = l; st[x].r = r;
  if (l == r) { st[x].lv = st[x].rv = a[l]; st[x].lm = st[x].rm = st[x].mx = 1; return ; }
  int k = l + ((r - l) >> 1);
  build(l, k, x << 1); build(k + 1, r, x << 1 | 1);
  st[x].pu(st[x << 1], st[x << 1 | 1]);
}

void mdf(int l, int r, int s, int t, int c, int x)
{
  if (l >= s and r <= t) { st[x].mdf(c); return ; }
  if (st[x].tg) { st[x].pd(st[x << 1], st[x << 1 | 1]); };
  int k = l + ((r - l) >> 1);
  if (s <= k) { mdf(l, k, s, t, c, x << 1); }
  if (t >  k) { mdf(k + 1, r, s, t, c, x << 1 | 1); }
  st[x].pu(st[x << 1], st[x << 1 | 1]);
}

N qry(int l, int r, int s, int t, int x)
{
  if (l >= s and r <= t) { return st[x]; }
  if (st[x].tg) { st[x].pd(st[x << 1], st[x << 1 | 1]); };
  N res; int k = l + ((r - l) >> 1);
  if (s <= k and t > k) { res.pu(qry(l, k, s, t, x << 1), qry(k + 1, r, s, t, x << 1 | 1)); return res; }
  if (s <= k) { return qry(l, k, s, t, x << 1); }
  if (t >  k) { return qry(k + 1, r, s, t, x << 1 | 1); }
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) { scanf("%d", &a[i]); }
  build(1, n, 1);
  for (int i = 1; i <= m; ++i)
  {
    scanf("\n%c", &op);
    if (op == 'Q')
    {
      scanf("%d%d%d", &l, &r, &k);
      N res = qry(1, n, l, r, 1);
      if (k and res.lv == res.rv) { printf("%d\n", std::max(res.mx, std::min(res.lm + res.rm, r - l + 1))); }
      else { printf("%d\n", res.mx); }
    }
    else { scanf("%d%d%d", &l, &r, &c); mdf(1, n, l, r, c, 1); }
  }
}


```

---

