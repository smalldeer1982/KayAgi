# Replace Digits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abl/tasks/abl_e

長さ $ N $ の文字列 $ S $ があります。 最初は $ S $ のすべての文字が `1` です。

クエリを $ Q $ 回処理します。 $ i $ 番目のクエリでは、整数 $ L_i,\ R_i $ と文字 (数字) $ D_i $ が与えられます。 $ L_i $ 番目から $ R_i $ 番目までの全ての文字を $ D_i $ に書き換えてください。

各クエリの後、$ S $ を十進法で書かれた整数とみなし、その値を $ 998,244,353 $ でわった余りを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ Q\ \leq\ 200,000 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- $ 1\ \leq\ D_i\ \leq\ 9 $
- 入力は全て整数である。

### Sample Explanation 2

あまりをとるのを忘れないでください。

## 样例 #1

### 输入

```
8 5
3 6 2
1 4 7
3 8 3
2 2 2
4 5 1```

### 输出

```
11222211
77772211
77333333
72333333
72311333```

## 样例 #2

### 输入

```
200000 1
123 456 7```

### 输出

```
641437905```

# 题解

## 作者：Rigel (赞：15)

## 思路

对于一个 $n$ 位的十进制数，从左往右数第 $i$ 位的位权为 $10^{n-i}$。

推而广之，我们可以求得某些数位区间的权值。一般地，数位区间 $[l,r]$ 的权值为 $\sum\limits_{i=l}^{r}10^{n-i}$。

考虑使用线段树维护。我们应预处理出线段树上每个区间的权值。若将数位 $[l,r]$ 均改为 $x$，$[l,r]$ 对答案贡献的实际值将改为 $[l,r]$ 的权值乘以 $x$。

懒标记存储当前区间最新一次被修改时的 $x$ 值。下传懒标记后，清空当前懒标记。

需要注意的是 $n$ 个数初始时均为 $1$，在开始前须执行一次将数位 $[1,n]$ 均修改为 $1$ 的操作。

每次修改后，查询 $[1,n]$ 的实际值。

注意取模。

时间复杂度为 $\mathcal{O}(q\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 200010
#define TT 998244353
using namespace std;
int n,q,w[maxn],t[maxn<<2],tw[maxn<<2],tag[maxn<<2];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}
void push_up(int now){
	t[now]=(t[now<<1]+t[(now<<1)|1])%TT;
}
void push_down(int now){
	if(!tag[now])return;
	int lson=now<<1,rson=(now<<1)|1;
	tag[lson]=tag[now],tag[rson]=tag[now];
	t[lson]=tag[now]*tw[lson]%TT,t[rson]=tag[now]*tw[rson]%TT;
	tag[now]=0;
}
void Build(int now,int l,int r){ // 预处理区间权值
	if(l==r){
		tw[now]=w[l];
		return;
	}
	int lson=now<<1,rson=(now<<1)|1,mid=(l+r)>>1;
	Build(lson,l,mid),Build(rson,mid+1,r);
	tw[now]=(tw[lson]+tw[rson])%TT;
}
int Query(int x,int y,int now,int l,int r){
	if(x<=l&&r<=y)return t[now];
	int lson=now<<1,rson=(now<<1)|1,mid=(l+r)>>1,ret=0;
	push_down(now);
	if(x<=mid)ret=(ret+Query(x,y,lson,l,mid))%TT;
	if(mid+1<=y)ret=(ret+Query(x,y,rson,mid+1,r))%TT;
	return ret;
}
void Update(int x,int y,int k,int now,int l,int r){
	if(x<=l&&r<=y){
		t[now]=k*tw[now]%TT;
		tag[now]=k;
		return;
	}
	int lson=now<<1,rson=(now<<1)|1,mid=(l+r)>>1;
	push_down(now);
	if(x<=mid)Update(x,y,k,lson,l,mid);
	if(mid+1<=y)Update(x,y,k,rson,mid+1,r);
	push_up(now);
}
signed main(){
	n=read(),q=read();
	w[n]=1;
	for(int i=n-1;i>=1;i--)w[i]=w[i+1]*10%TT; // 预处理位权
	Build(1,1,n);
	Update(1,n,1,1,1,n);
	while(q--){
		int l=read(),r=read(),x=read();
		Update(l,r,x,1,1,n);
		printf("%lld\n",Query(1,n,1,1,n));
	}
	return 0;
}
```

---

## 作者：Bamboo_Day (赞：3)

看到区间查询区间修改，第一反应线段树。

线段树灵魂三问：
1. 每个节点存什么？
	- 当前这段区间表示的十进制数。
2. 如何 push\_up ？
	- `左儿子` 乘上 十的`右儿子的区间长度`次方 加 `右儿子`
3. 要不要懒标记？要的话如何 push\_down ？
	- 显然是要的。
   - 更改左右儿子的值然后懒标记下传，当前位置懒标记清空。
   
思维点：在 push\_downn 的时候左右儿子值更改复杂度似乎是 $O(n)$ 的。可以预处理出 $1\sim 9$ 分别一长串串起来表示的十进制数。

注意点：记得取模。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 2e5+10;
const int mod = 998244353;
#define ls (pos<<1)
#define rs (pos<<1|1) 
#define mid ((l+r)>>1)

using namespace std;
int Node[N<<2],tag[N<<2];
int pw[N];
int num[15][N];
void push_up(int pos, int l ,int r){
	Node[pos] = (Node[ls]*pw[r-mid]%mod+Node[rs])%mod;
}
void build(int pos, int l, int r){
	if(l == r){
		Node[pos] = 1;
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(pos,l,r);
}
void ksc(int a, int b){
}
void push_down(int pos, int l, int r){
	if(!tag[pos]) return;
	tag[ls] = tag[rs] = tag[pos];
	Node[ls] = num[tag[pos]][mid-l+1];
	Node[rs] = num[tag[pos]][r-mid];
	tag[pos] = 0;
}
void update(int pos, int l, int r, int x, int y, int z){
	if(x <= l && r <= y){
		Node[pos] = num[z][r-l+1];
		tag[pos] = z;
		return;
	}
	push_down(pos,l,r);
	if(x <= mid) update(ls,l,mid,x,y,z);
	if(y > mid) update(rs,mid+1,r,x,y,z);
	push_up(pos,l,r); 
}
int n,q;

signed main(){
	cin >> n >> q;
	pw[0] = 1;
	for(int i = 1; i <= N-5; i++) pw[i] = pw[i-1]*10%mod; //预处理10的次方
	for(int i = 1; i <= 9; i++){
		num[i][0] = 0;
		for(int j = 1; j <= N-5; j++){
			num[i][j] = (num[i][j-1]*10%mod+i)%mod;
		}
	}// 思维点所言预处理
	build(1,1,n);
	while(q--){
		int l,r,x;
		cin >> l >> r >> x;
		update(1,1,n,l,r,x);
		cout << Node[1] << "\n";
	} 
	return 0;
}
````

---

## 作者：xiaoPanda (赞：2)

## Solution
简单的线段树题，看到题目要求维护区间，首先想到线段树。

先考虑向上合并信息，有 $sum_p=sum_{ls}\times 10^{r-mid}+sum_{rs}$。

再考虑修改操作，直接打标记即可，注意到标记时要将区间加上 $\overline{xxx...}$，变成 $\overline{111...}\times x$，预处理 $\overline{111...}$ 即可，标记为 $0$ 时代表没有操作，具体代码如下：

```cpp
//s[] is 1111...
void addlazy(int p,int x)
{
    sum[p]=s[sz[p]-1]*x%mod;
    lazy[p]=x;
}
void pushdown(int p)
{
    if(!lazy[p])return;
    addlazy(ls,lazy[p]);
    addlazy(rs,lazy[p]);
    lazy[p]=0;
}
```
所有的修改操作代码如下：

```cpp
//g[] is 10^x
void add(int p,int l,int r,int L,int R,int x)
{
    if(L<=l&&r<=R)
    {
        addlazy(p,x);
        return;
    }
    pushdown(p);
    int mid=(l+r)/2;
    if(L<=mid)add(ls,l,mid,L,R,x);
    if(R>mid)add(rs,mid+1,r,L,R,x);
    sum[p]=(sum[ls]*g[r-mid]+sum[rs])%mod;
}
```

最后的查询操作，注意到查询时要记录当前组成数字的长度，和向上合并信息类似，因为要记两个值，可以直接使用 STL-map。

查询操作代码如下：

```cpp
pii query(int p,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)return mp(sum[p],sz[p]);
    pushdown(p);
    int mid=(l+r)/2;
    pii x=mp(0,0),y=mp(0,0);
    if(L<=mid)x=query(ls,l,mid,L,R);
    if(R>mid)y=query(rs,mid+1,r,L,R);
    return mp((x.ft*g[y.sd]+y.ft)%mod,x.sd+y.sd);
}
```

综上所述，在 $O(q\log n)$ 的时间复杂度内解决了这个问题。

---

## 作者：封禁用户 (赞：1)

## 分析
显然线段树。

**【建树】**

对于每一位，我们都可以将它的值维护起来，建一棵树。但是我们维护的东西显然不是每一位的值，而是单独将其提出时的值。举个例子，有一个序列为 $11111$，那么对于从左往右数第三位的值，就是 $100$。那么我们就可以将建树的函数写成：
```cpp
void get(int now,int n)//求这一位的值
{
	for(int i=tr[now].l;i<=tr[now].r;i++)//因为有可能有多个一（一开始每一位都是一），所以要循环一下
		tr[now].sum=(tr[now].sum+qmi(10,i-tr[now].l))%p;tr[now].sum=(tr[now].sum*qmi(10,n-tr[now].r))%p;
}
void build(int now,int l,int r,int c,int n)
{
	tr[now].l=l,tr[now].r=r,tr[now].c=c;
	tr[now].lz=tr[now].s=0;
	if(l==r) get(now,n);
	else
	{
		int mid=l+r>>1;
		build(now*2,l,mid,c+1,n),build(now*2+1,mid+1,r,c+1,n);		
		tr[now].sum=(tr[now*2].sum+tr[now*2+1].sum)%p;//tr[i].sum是这一位的初始值，因为在这样我们可以在修改的时候当做模板直接乘上它，更方便	
	}
	tr[now].s=tr[now].sum;//记得一开始的tr[i].s也是要有值的，也是11...00...
}
```
**【修改】**

由于数据范围有一点大，所以每次修改遍历到叶节点肯定是不行的。所以我们要加一个懒标记。和模板一样，当当前节点完全在修改范围内时，直接将它的值修改，即模板乘上修改值。然后将懒标记修改即可。若这个节点有一部分在目标区间，则我们要先将懒标记发放下去，再修改满足要求的子节点，发放的思路和上述操作类似。代码如下：
```cpp
void pushdown(int now,int n)
{
	if(tr[now].lz)
	{
		tr[now*2].lz=tr[now].lz;//复制给两个子节点的懒标记
		tr[now*2+1].lz=tr[now].lz;
		tr[now*2].s=tr[now*2].sum*tr[now*2].lz%p;//子节点的值套模板乘
		tr[now*2+1].s=tr[now*2+1].sum*tr[now*2+1].lz%p;
		tr[now].lz=0;//清空
	}
}
void insert(int now,int l,int r,int k)
{
	if(tr[now].l>=l&&tr[now].r<=r) tr[now].s=tr[now].sum*k%p,tr[now].lz=k;	
	else
	{
		pushdown(now,n);
		int mid=tr[now].l+tr[now].r>>1;
		if(l<=mid) insert(now*2,l,r,k);
		if(mid<r) insert(now*2+1,l,r,k);
		tr[now].s=(tr[now*2].s+tr[now*2+1].s)%p;//记得还要加一下
	}
}
```
**【其他】**

首先，在上面的代码中，出现了一个叫 `qmi` 的函数，这是快速幂。其次，在每次修改后，我们都是要输出一遍的，输出什么呢？就是 `tr[1].s` 啦。因为只有这个节点包含了序列的全部信息。完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
const int p=998244353;
const int N=2e5+10;
struct aa{
	int l,r,s,lz,sum;
}tr[N*4];
int qmi(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%p;
		a=a*a%p,b>>=1;
	}
	return ans;
}
void get(int now,int n)
{
	for(int i=tr[now].l;i<=tr[now].r;i++) 
		tr[now].sum=(tr[now].sum+qmi(10,i-tr[now].l))%p;tr[now].sum=(tr[now].sum*qmi(10,n-tr[now].r))%p;
}
void build(int now,int l,int r,int n)
{
	tr[now].l=l,tr[now].r=r;
	tr[now].lz=tr[now].s=0;
	if(l==r) get(now,n);
	else
	{
		int mid=l+r>>1;
		build(now*2,l,mid,n),build(now*2+1,mid+1,r,n);		
		tr[now].sum=(tr[now*2].sum+tr[now*2+1].sum)%p;	
	}
	tr[now].s=tr[now].sum;
}
void pushdown(int now,int n)
{
	if(tr[now].lz)
	{
		tr[now*2].lz=tr[now].lz;
		tr[now*2+1].lz=tr[now].lz;
		tr[now*2].s=tr[now*2].sum*tr[now*2].lz%p;
		tr[now*2+1].s=tr[now*2+1].sum*tr[now*2+1].lz%p;
		tr[now].lz=0;
	}
}
void insert(int now,int l,int r,int k)
{
	if(tr[now].l>=l&&tr[now].r<=r) tr[now].s=tr[now].sum*k%p,tr[now].lz=k;	
	else
	{
		pushdown(now,n);
		int mid=tr[now].l+tr[now].r>>1;
		if(l<=mid) insert(now*2,l,r,k);
		if(mid<r) insert(now*2+1,l,r,k);
		tr[now].s=(tr[now*2].s+tr[now*2+1].s)%p;
	}
}
signed main()
{
	cin>>n>>m;
	build(1,1,n,n);
	for(int i=1;i<=m;i++)
	{
		int l,r,k;cin>>l>>r>>k;
		insert(1,l,r,k);
		cout<<tr[1].s<<endl;
	}	
	return 0;
}
```


---

## 作者：wfc284 (赞：0)

非常 naive 的线段树，为何我写了 30+ min？  

首先我们瞅见区间修改、区间（全局）查询，第一反应是线段树。每个结点显然存当前区间代表的十进制数（模 $P$）。  

如何 push_up 呢？
我们想一想两个十进制数是怎么拼到一起的。记 $x$ 的位数为 ${\operatorname {len}}(b)$，那么有 $\overline{ab} = \overline{a00...0} + b = a \times 10^{{\operatorname {len}}(b) } + b$。  
于是我们明白了，我们需要维护每个区间的长度，push_up 时按照上面做一下就行。

时间复杂度 $O(q \log n)$。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define int long long
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)
//#define multi_cases 1

namespace Traveller {
	const int N = 2e5+2, P = 998244353;
	
	int n, q;
	int POW10[N];
	
	struct SegmentTree {
		struct data {
			int val, len;
			data() { }
			data(int a, int b) : val(a), len(b) { }
		};
		friend data operator + (data a, data b) {
			a.len += b.len;
			a.val = (a.val * POW10[b.len] + b.val) % P;
			return a;
		}
		
		struct node {
			node *l, *r;
			data d;
			int tag;
			void up() { d = l->d + r->d; }
			void upd(int v) { tag = v, d.val = (POW10[d.len]-1) * 443664157 % P * v % P; }
			void down() { if(tag) l->upd(tag), r->upd(tag), tag = 0; }
		} pool[N << 1], *tmp = pool, *root;
		
		node *newnode() {
			tmp->l = tmp->r = NULL;
			tmp->d = data(0, 1), tmp->tag = 0;
			return tmp++;
		}
		
		int l, r;
		
		void build(node *&p, int l, int r) {
			p = newnode();
			if(l == r) return p->d = data(1, 1), void();
			int mid = l + r >> 1;
			build(p->l, l, mid);
			build(p->r, mid+1, r);
			p->up();
		}
		void update(node *p, int l, int r, int ql, int qr, int v) {
			if(l == ql && r == qr) return p->upd(v), void();
			p->down();
			int mid = l + r >> 1;
			if(mid >= qr) update(p->l, l, mid, ql, qr, v);
			else if(mid < ql) update(p->r, mid+1, r, ql, qr, v);
			else {
				update(p->l, l, mid, ql, mid, v);
				update(p->r, mid+1, r, mid+1, qr, v);
			}
			p->up();
		}
		int query() { return root->d.val % P; }
		
		void build(int ql, int qr) {
			l = ql, r = qr, root = NULL;
			build(root, l, r);
		}
		void update(int ql, int qr, int v) { update(root, l, r, ql, qr, v); }
	} tr;
	
	void main() {
		cin >> n >> q;
		POW10[0] = 1;
		for(int i = 1; i <= n; ++i) POW10[i] = POW10[i-1] * 10 % P;
		
		tr.build(1, n);
		for(int i = 1, l, r, v; i <= q; ++i) {
			scanf("%lld%lld%lld", &l, &r, &v);
			tr.update(l, r, v);
			printf("%lld\n", tr.query());
		}
	}
}

signed main() {
#ifdef filename
	FileOperations();
#endif
	
	signed _ = 1;
#ifdef multi_cases
	scanf("%d", &_);
#endif
	while(_--) Traveller::main();
	return 0;
}


```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abl_e)

# 前置知识

[线段树](https://oi-wiki.org//ds/seg/)

# 解法

需要维护区间信息，考虑使用线段树维护。

预处理出 $\overline{xx \dots x}$，其中 $x \in \{1,2,3,4,5,6,7,8,9 \}$，便于区间赋值。

然后就是普通的线段树板子了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll p=998244353;
ll mi[200010],num[12][200010];
struct SMT
{
    struct SegmentTree
    {
        ll l,r,len,sum,lazy;
    }tree[800010];
    ll lson(ll x)
    {
        return x*2;
    }
    ll rson(ll x)
    {
        return x*2+1;
    }
    void pushup(ll rt)
    {
        tree[rt].len=tree[lson(rt)].len+tree[rson(rt)].len;
        tree[rt].sum=(tree[lson(rt)].sum*mi[tree[rson(rt)].len]+tree[rson(rt)].sum)%p;
    }
    void build(ll rt,ll l,ll r)
    {
        tree[rt].l=l;
        tree[rt].r=r;
        tree[rt].lazy=0;
        if(l==r)
        {
            tree[rt].len=tree[rt].sum=1;
            return;
        }
        ll mid=(tree[rt].l+tree[rt].r)/2;
        build(lson(rt),l,mid);
        build(rson(rt),mid+1,r);
        pushup(rt);
    }
    void pushdown(ll rt)
    {
        if(tree[rt].lazy!=0)
        {
            tree[lson(rt)].lazy=tree[rt].lazy;
            tree[lson(rt)].sum=num[tree[rt].lazy][tree[lson(rt)].len];
            tree[rson(rt)].lazy=tree[rt].lazy;
            tree[rson(rt)].sum=num[tree[rt].lazy][tree[rson(rt)].len];
            tree[rt].lazy=0;
        }
    }
    void update(ll rt,ll x,ll y,ll val)
    {
        if(x<=tree[rt].l&&tree[rt].r<=y)
        {
            tree[rt].lazy=val;
            tree[rt].sum=num[val][tree[rt].len];
            return;
        }
        pushdown(rt);
        ll mid=(tree[rt].l+tree[rt].r)/2;
        if(x<=mid)
        {
            update(lson(rt),x,y,val);
        }
        if(y>mid)
        {
            update(rson(rt),x,y,val);
        }
        pushup(rt);
    }
    pair<ll,ll> query(ll rt,ll x,ll y)
    {
        if(x<=tree[rt].l&&tree[rt].r<=y)
        {
            return make_pair(tree[rt].sum,tree[rt].len);
        }
        pushdown(rt);//以下部分在本题中显多此一举
        ll mid=(tree[rt].l+tree[rt].r)/2;
        pair<ll,ll>lp=make_pair(0,0),rq=make_pair(0,0);
        if(x<=mid)
        {
            lp=query(lson(rt),x,y);
        }
        if(y>mid)
        {
            rq=query(rson(rt),x,y);
        }
        return make_pair((lp.first*mi[rq.second]%p+rq.first)%p,lp.second+rq.second);
    }
}T;
int main()
{       
    ll n,q,l,r,x,i,j;
    cin>>n>>q;
    mi[0]=1;
    for(i=1;i<=n;i++)
    {
        mi[i]=mi[i-1]*10%p;
        for(j=1;j<=9;j++)
        {
            num[j][i]=(num[j][i-1]*10+j)%p;
        }
    }
    T.build(1,1,n);
    for(i=1;i<=q;i++)
    {
        cin>>l>>r>>x;
        T.update(1,l,r,x);
        cout<<T.query(1,1,n).first<<endl;
    }
    return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

[博客食用更佳。](https://www.cnblogs.com/Jh763878/p/18331354)

线段树裸题。

可以开两个辅助数组，分别表示 $10^i$ 和 $\sum_{j=0}^{i}10^j$。

线段树上每一个节点表示该区间的值，可用第一个数组进行拼合。

区间覆盖可以用懒标记和第二个数组处理。

（二）

记得开 long long。

AC 代码。

```cpp
#include<bits/stdc++.h>
#define db double
#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define pii pair<int,int>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f; 
}
const int mxn=3e5+10,md=998244353;
int s0[mxn],s1[mxn],tree[mxn<<2],tag[mxn<<2];
void build(int o,int l,int r){
	tree[o]=s1[r-l+1];
	tag[o]=-1;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(o*2,l,mid);
	build(o*2+1,mid+1,r);
}
void change(int o,int l,int r,int val){
	tree[o]=s1[r-l+1]*val%md;
	tag[o]=val;
}
void pushdown(int o,int l,int r){
	if(tag[o]==-1)return;
	int mid=(l+r)>>1;
	change(o*2,l,mid,tag[o]);
	change(o*2+1,mid+1,r,tag[o]);
	tag[o]=-1;
}
void update(int o,int l,int r,int L,int R,int val){
	if(L<=l&&r<=R){
		change(o,l,r,val);
		return;
	}
	pushdown(o,l,r);
	int mid=(l+r)>>1;
	if(L<=mid)update(o*2,l,mid,L,R,val);
	if(R>mid)update(o*2+1,mid+1,r,L,R,val);
	tree[o]=(tree[o*2]*s0[r-mid]%md+tree[o*2+1])%md;
}
signed main(){
	int n=read(),q=read();
	s0[0]=1;
	for(int i=1;i<=n;i++)
		s0[i]=s0[i-1]*10%md;
	s1[1]=1;
	for(int i=2;i<=n;i++)
		s1[i]=(s1[i-1]*10%md+1)%md;
	build(1,1,n);
	while(q--){
		int l=read(),r=read(),v=read();
		update(1,1,n,l,r,v);
		printf("%lld\n",tree[1]);
	}
    return 0;
}
```

---

## 作者：cosf (赞：0)

本题可以转化为区间赋值和全局加权和。

具体的，令权值 $w_1, \dots, w_n = 10^{n - 1}, \dots, 100, 10$，以及初始值 $a_1 = a_2 = \dots a_n = 1$，每次操作将 $a_{l\dots r}$ 修改为 $d_i$，问 $\sum a_iw_i$ 的值是多少。

显然，可以使用线段树解决。

线段树需要维护的东西：$\sum w_i, \sum a_iw_i$。懒标记维护区间最后一次修改的 $d_j$。修改一个区间的时候直接令 $\sum a_iw_i \gets d_j \times \sum w_i$ 即可。

---

```cpp
#include <iostream>
using namespace std;

#define MAXN 200005
#define MOD 998244353ll

using ll = long long;

struct Tree
{
    ll b, s, t;
} t[MAXN << 2];

ll pt[MAXN];

void pushup(int p)
{
    t[p].s = (t[p << 1].s + t[p << 1 | 1].s) % MOD;
}

void pushdown(int p)
{
    if (t[p].t)
    {
        t[p << 1].s = t[p << 1].b * t[p].t % MOD;
        t[p << 1].t = t[p].t;
        t[p << 1 | 1].s = t[p << 1 | 1].b * t[p].t % MOD;
        t[p << 1 | 1].t = t[p].t;
        t[p].t = 0;
    }
}

void build(int p, int l, int r)
{
    if (l == r)
    {
        t[p].b = t[p].s = pt[l];
        t[p].t = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
    t[p].b = (t[p << 1].b + t[p << 1 | 1].b) % MOD;
}

void set(int p, int l, int r, int ql, int qr, ll v)
{
    if (ql <= l && r <= qr)
    {
        t[p].s = t[p].b * v % MOD;
        t[p].t = v;
        return;
    }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (mid >= ql)
    {
        set(p << 1, l, mid, ql, qr, v);
    }
    if (mid < qr)
    {
        set(p << 1 | 1, mid + 1, r, ql, qr, v);
    }
    pushup(p);
}

int n, q;

int main()
{
    cin >> n >> q;
    pt[n] = 1;
    for (int i = n - 1; i; i--)
    {
        pt[i] = pt[i + 1] * 10 % MOD;
    }
    build(1, 1, n);
    while (q--)
    {
        int l, r, v;
        cin >> l >> r >> v;
        set(1, 1, n, l, r, v);
        cout << t[1].s << '\n';
    }
    cout.flush();
    return 0;
}

```

---

## 作者：xiaomuyun (赞：0)

- [洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abl_e)
- [AtCoder 题目传送门](https://atcoder.jp/contests/abl/tasks/abl_e)

## 分析

非常有趣的一道数据结构题。

看到这种区间修改，不难想到带懒标记的线段树。

如果不用取模而是直接输出的话，我们直接在每个节点以字符串的形式存一下数，然后在合并时字符串连接即可。

但是如果要取模的话，我们就要以整数而不是以字符串的形式存每个节点的数了（除非你喜欢用高精）。因此我们要在刚才的线段树上做一些修改。

## 实现

以下是几个在实现这个线段树时会遇到的问题。

### 一、如何初始化？

线段树中所有节点维护的值一开始都是若干个 $1$，而且 $1$ 的数量取决于节点所维护区间的长度（这是题意，应该不难理解）。

在实现方面，我们可以先让每个叶子节点维护的值为 $1$，然后向上更新。

在更新的过程中，设右儿子维护区间的长度为 $l_r$，则当前节点维护的值为左儿子节点维护的值乘 $10^{l_r}$ 再加上右儿子节点维护的值，最后对 $998244353$ 取模。这样就可以达到连接并取模的目的，大家可以在纸上手推以下加深理解。对于求 $10^{l_r}$，我们没有必要每次都拿一个快速幂来加大常数，可以直接拿一个数组预处理一下 $10$ 的若干次方对 $998244353$ 取模后的值。

这样初始化的时间复杂度仍是 $\mathcal{O}(n\log_2n)$。

代码可以翻到下面去看，不过建议先把其他内容看完。

### 二、区间修改的时候如何快速对一个区间赋值？

假设 **当前节点** 维护的区间为 $[l,r]$，而且我们需要让这个区间的每个位置都修改为 $x$，也就是让区间的值修改为 $r-l+1$ 个 $x$ 相连。当然我们也不可能暴力连接增加复杂度，所以可以再用一个数组预处理一下若干个 $1$ 相连对 $998244353$ 取模后的值。这样的话这个节点维护的区间的值就是 $r-l+1$ 个 $1$ 相连在模 $998244353$ 之后乘 $x$。这个也建议手推一下，光看看不懂的。

有了这两个数组，懒标记下传什么的也就迎刃而解了。

## 代码

```cpp
// Problem: E - Replace Digits
// URL: https://atcoder.jp/contests/abl/tasks/abl_e
// Start Time: 2023-10-08 20:50:03
// 
// Powered by CP Editor (https://cpeditor.org)

#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
using namespace std;
#define inf 0x3f3f3f3f
#define inff 0x3f3f3f3f3f3f3f3f
#define mod 998244353
#define mod2 1000000007
#define int long long
const int maxn=2e5+2;
int n,q,a[maxn*4],t[maxn*4],p[maxn],num[maxn];
//a 中存的是每个节点维护的区间的值
//t 中存的是懒标记
void build(int o,int l,int r){//见实现问题一
	if(l==r){
		a[o]=1;
		return ;
	}
	int mid=l+(r-l)/2;
	build(o*2,l,mid);
	build(o*2+1,mid+1,r);
	a[o]=(a[o*2]*p[r-mid]+a[o*2+1])%mod;//不要忘记更新！！！
}
inline void pushdown(int o,int l,int r,int mid){
	if(!t[o]) return ;
	t[o*2]=t[o*2+1]=t[o];
	a[o*2]=num[mid-l+1]*t[o]%mod;
	a[o*2+1]=num[r-mid]*t[o]%mod;
	t[o]=0;
}
void update(int o,int l,int r,int x,int y,int v){
	if(y<l||r<x) return ;
	if(x<=l&&r<=y){//见实现问题二
		a[o]=num[r-l+1]*v%mod;
		t[o]=v;
		return ;
	}
	int mid=l+(r-l)/2;
	pushdown(o,l,r,mid);
	update(o*2,l,mid,x,y,v);
	update(o*2+1,mid+1,r,x,y,v);
	a[o]=(a[o*2]*p[r-mid]+a[o*2+1])%mod;
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	p[0]=1;//预处理 10 的幂次方（p 数组）和若干个 1 相连并取模后的值（num 数组）
	for(int i=1;i<=n;++i) p[i]=p[i-1]*10%mod;
	for(int i=1;i<=n;++i) num[i]=(num[i-1]*10+1)%mod;
	build(1,1,n);
	for(int i=1,l,r,x;i<=q;++i){
		cin>>l>>r>>x;
		update(1,1,n,l,r,x);
		cout<<a[1]<<'\n';//直接输出线段树根节点的值即可
	}
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

线段树模板题。

维护一个区间 $[l,r]$ 中 $\sum\limits_{i=l}^r 10^{n-i}$ 的答案。将某个区间 $[l,r]$ 全部修改成 $x$ 之后的表示的数就是 $x \times(\sum\limits_{i=l}^r 10^{n-i})$。区间修改可以用线段树，用快速幂或者预处理弄出来 $10^x$，建树的时候就能把每个 $[l,r]$ 对应的 $\sum\limits_{i=l}^r 10^{n-i}$ 求出来。

唯一的细节就是取模，尽量在每个加法或乘法中都进行一次取模。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

const int N=2e5+10,p=998244353;
int n,m;
struct node{
	int l,r,_10,s,lz;
}tr[N<<2];

il int qmi(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%p;
		a=a*a%p,b>>=1;
	}
	return ans;
}

il void up(int now){tr[now].s=(tr[now<<1].s+tr[now<<1|1].s)%p;}
il void down(int now){
	if(tr[now].lz){
		tr[now<<1].lz=tr[now].lz,tr[now<<1|1].lz=tr[now].lz;
		tr[now<<1].s=tr[now<<1].lz*tr[now<<1]._10%p;
		tr[now<<1|1].s=tr[now<<1|1].lz*tr[now<<1|1]._10%p;
		tr[now].lz=0;
	}
}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(l==r){
		tr[now].lz=1,tr[now]._10=qmi(10,n-l),tr[now].s=tr[now].lz*tr[now]._10%p;
		return ;
	}
	int mid=l+r>>1;
	build(now<<1,l,mid),build(now<<1|1,mid+1,r);
	up(now),tr[now]._10=(tr[now<<1]._10+tr[now<<1|1]._10)%p;
}
il void insert(int now,int l,int r,int k){
	if(tr[now].l>=l&&tr[now].r<=r){
		tr[now].lz=k,tr[now].s=tr[now].lz*tr[now]._10%p;
		return ;
	}
	int mid=tr[now].l+tr[now].r>>1;
	down(now);
	if(l<=mid) insert(now<<1,l,r,k);
	if(mid<r) insert(now<<1|1,l,r,k);
	up(now);
}
il int query(int now,int l,int r){
	if(tr[now].l>=l&&tr[now].r<=r) return tr[now].s;
	int mid=tr[now].l+tr[now].r>>1,ans=0;
	down(now);
	if(l<=mid) ans=(ans+query(now<<1,l,r))%p;
	if(mid<r) ans=(ans+query(now<<1|1,l,r))%p;
	up(now);
	return ans;
}

il void solve(){
	cin>>n>>m;
	build(1,1,n);
	for(re int i=1;i<=m;++i){
		int l,r,x;cin>>l>>r>>x;
		insert(1,l,r,x);cout<<query(1,1,n)<<"\n";
	}
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：int_R (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_abl_e)

已经有线段树的题解了，那我写一篇 ODT 的吧。

最近在学 ODT ，然后找到这道题，小题大做用了 ODT。[推荐一篇关于 ODT 的博客](https://zhuanlan.zhihu.com/p/106353082)。

众所周知 ODT 适用于有**区间赋值**的题目，而这道题全是区间赋值。所以基本的分裂和推平操作来维护就行。

```cpp
//ODT 的基本操作
struct node
{
	int l,r;
	mutable int v;
	node(int l,int r,int v):l(l),r(r),v(v){}
	bool operator <(const node &o) const{return l<o.l;}
};
set <node> tree;
//分裂出一个 l 为 pos 的三元组，返回其迭代器
inline auto split(int pos)
{
	auto it=tree.lower_bound(node(pos,0,0));
	if(it!=tree.end()&&it->l==pos) return it;
	--it;
	int l=it->l,r=it->r,v=it->v;
	tree.erase(it);
	tree.insert(node(l,pos-1,v));
	return tree.insert(node(pos,r,v)).first;
}
//将 l 到 r 全更改为 v（推平操作）
inline void assign(int l,int r,int v)
{
	auto end=split(r+1),begin=split(l);
	tree.erase(begin,end);
	tree.insert(node(l,r,v));return ;
}
```


对于一个三元组 $\langle l,r,v\rangle$，相当于是有连续 $r-l+1$ 个 $v$ 在第 $l$ 到 $r$ 位上，所以它对答案的贡献（用 $p_i$ 表示连续 $i$ 个 $1$ 的值 ）应当是 $v\times p_{r-l+1}\times 10^{n-r}$，$p$ 和 $10$ 的次方预处理一下。

```cpp
int main()
{
	scanf("%d%d",&n,&m);
	tree.insert({1,n,1});q[0]=1;//q[0] 先赋值 0 次方为 1
	for(register int i=1;i<=n;++i) p[i]=((long long)p[i-1]*10%MOD+1)%MOD;
	for(register int i=1;i<=n;++i) q[i]=(long long)q[i-1]*10%MOD;//q[i] 表示 10 的 i 次方
	while(m--)
	{
		int l,r,k,ans=0;
		scanf("%d%d%d",&l,&r,&k);
		assign(l,r,k);//区间赋值操作
		for(auto it=tree.begin();it!=tree.end();++it)//每次遍历求答案
		{
			ans=(ans+(long long)it->v*p[it->r-it->l+1]%MOD*q[n-it->r]%MOD)%MOD;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

然后你就发现 TLE 了，我们想到每次全都重新计算太耗费时间了，类比[这道题](https://www.luogu.com.cn/problem/CF915E)的 ODT 做法，我们在每次区间赋值的时候实时更新答案，减掉删去的，加上更新的，就可以保证时间复杂度正确。然后就结束了。

```cpp
inline void assign(int l,int r,int v)
{
	auto end=split(r+1),begin=split(l);
	for(auto it=begin;it!=end;++it)//每次减去删掉的对答案的贡献，可能出现负数，取模要注意
		sum=((sum-it->v*p[it->r-it->l+1]%MOD*q[n-it->r]%MOD)%MOD+MOD)%MOD;
	tree.erase(begin,end);
	sum=(sum+v*p[r-l+1]%MOD*q[n-r]%MOD)%MOD;//加上区间赋值的贡献
	tree.insert(node(l,r,v));return ;
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	tree.insert({1,n,1});q[0]=1;
	for(register int i=1;i<=n;++i) p[i]=((long long)p[i-1]*10%MOD+1)%MOD;
	for(register int i=1;i<=n;++i) q[i]=(long long)q[i-1]*10%MOD;
	sum=p[n];//一开始是 n 个 1，所以答案就是 p[n]
	while(m--)
	{
		int l,r,k;
		scanf("%lld%lld%lld",&l,&r,&k);
		assign(l,r,k);
		printf("%lld\n",sum);
	}
	return 0;
}
```



---

