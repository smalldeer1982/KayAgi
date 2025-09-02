# Welfare State

## 题目描述

There is a country with $ n $ citizens. The $ i $ -th of them initially has $ a_{i} $ money. The government strictly controls the wealth of its citizens. Whenever a citizen makes a purchase or earns some money, they must send a receipt to the social services mentioning the amount of money they currently have.

Sometimes the government makes payouts to the poor: all citizens who have strictly less money than $ x $ are paid accordingly so that after the payout they have exactly $ x $ money. In this case the citizens don't send a receipt.

You know the initial wealth of every citizen and the log of all events: receipts and payouts. Restore the amount of money each citizen has after all events.

## 说明/提示

In the first example the balances change as follows: 1 2 3 4 $ \rightarrow $ 3 3 3 4 $ \rightarrow $ 3 2 3 4 $ \rightarrow $ 3 2 3 4

In the second example the balances change as follows: 3 50 2 1 10 $ \rightarrow $ 3 0 2 1 10 $ \rightarrow $ 8 8 8 8 10 $ \rightarrow $ 8 8 20 8 10

## 样例 #1

### 输入

```
4
1 2 3 4
3
2 3
1 2 2
2 1
```

### 输出

```
3 2 3 4 
```

## 样例 #2

### 输入

```
5
3 50 2 1 10
3
1 2 0
2 8
1 3 20
```

### 输出

```
8 8 20 8 10 
```

# 题解

## 作者：Bai_R_X (赞：7)

## 思路
对于操作 $1$：我们只需要记录每个点最后的一次修改，因为最后前的都会被最后一次所覆盖。

对于操作 $2$：我们也只需要最后且最大的一个 $x$ ，因为前面会被覆盖，比最大小会因为最大让所有值都不低于 $x$ ，再小不会有任何效果。

另外，由于操作 $1$ 是单点修改，其优先级大于操作 $2$ 。我们只需要记录每个点最后单点操作的时间，再与此时最大的操作 $2$ 相比较即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005],i,q,op,p,x,op1[200005],op2[200005],t[200005];
signed main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		op1[i]=-1;
	}
	cin>>q;
	for(i=1;i<=q;i++)
	{
		cin>>op;
		if(op==1)
		{
			cin>>p>>x;
			op1[p]=x;
			t[p]=i;
		}
		else
		{
			cin>>x;
			op2[i]=x;
		}
	}
	for(i=q;i>=0;i--)op2[i]=max(op2[i],op2[i+1]);
	for(i=1;i<=n;i++)
	{
		if(op1[i]>=0)a[i]=op1[i];
	}
	for(i=1;i<=n;i++)
	{
		if(a[i]<op2[t[i]])a[i]=op2[t[i]];
	}
	for(i=1;i<=n;i++)cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：skydogli (赞：4)

题意：支持2种操作：单点修改，把全部小于x的数全部改成x

观察题面，连区间修改都没有，全局修改，所以应该不需要数据结构。

按照题面要求，如果没有单点修改，就应该取最大的x，但是碰到单点修改是强制修改的，所以对于每个点，我们要取最后一次单点修改后区间操作的最大值与最后一次单点修改的值相比较，取较大的。我们可以记录每个点最后一次单点修改的时间，在预处理所有时间点之后里区间操作的值后缀中最大的值。

总的时间复杂度$O(n)$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 1e9+1
#define MN 400005
int n,q,a[MN],cnt,ans,last[MN],Max[MN];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;++i){
		int op,loc,v;
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&loc,&v);
			a[loc]=v;
			last[loc]=i;//最后一次单点修改的时间
		}
		else{
			scanf("%d",&v);
			Max[i]=v;
		}
	}
	for(int i=q;i>=0;--i)Max[i]=max(Max[i],Max[i+1]);//求后缀中最大的
	for(int i=1;i<=n;++i)
		printf("%d ",max(a[i],Max[last[i]]));
	return 0;
}
```

---

## 作者：tzc_wk (赞：3)

~~好像还没有人发线段树的题解，我来水一波。~~

线段树，操作1可以转化为线段树上单点修改，操作2本质上是对于所有的$ 1 \leq i \leq n $，$ a_i=max(a_i,n) $，因此我们可以将它转化为区间修改$ [1,n] $。最后的输出$ a $数组中的每一个元素其实就是单点查询。

代码实现难度不大，细节见注释：
```
#include <bits/stdc++.h>
using namespace std;
int n,a[200005];
struct node{
	int l,r,lazy;//lazy表示当前区间被哪个x值更新，叶子节点的懒标记也可以表示a数组的值
} s[800020];
void build(int k,int l,int r){//递归建树
	s[k].l=l;s[k].r=r;s[k].lazy=0;
	if(l==r){
		s[k].lazy=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
void change(int x){
	s[1].lazy=max(s[1].lazy,x);//区间修改，因为修改的是[1,n]所以我们只用更新根节点的懒标记
}
void pushdown(int k){//懒标记下传
	s[k<<1].lazy=max(s[k<<1].lazy,s[k].lazy);
	s[k<<1|1].lazy=max(s[k<<1|1].lazy,s[k].lazy);
	s[k].lazy=0;
}
void modify(int k,int ind,int x){//单点修改
	if(s[k].l==s[k].r){
		s[k].lazy=x;
		return;
	}
	pushdown(k);
	int mid=(s[k].l+s[k].r)>>1;
	if(ind<=mid)	modify(k<<1,ind,x);
	else			modify(k<<1|1,ind,x);
}
int ask(int k,int ind){//单点查询
	if(s[k].l==s[k].r){
		return s[k].lazy;
	}
	pushdown(k);
	int mid=(s[k].l+s[k].r)>>1;
	if(ind<=mid)	return ask(k<<1,ind);
	else			return ask(k<<1|1,ind);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	build(1,1,n);
	int T;cin>>T;
	while(T--){
		int type;cin>>type;
		if(type==1){
			int p,x;cin>>p>>x;
			modify(1,p,x);
		}
		else{
			int x;cin>>x;
			change(x);
		}
	}
	for(int i=1;i<=n;i++)	cout<<ask(1,i)<<" ";
}
```


---

## 作者：toolong114514 (赞：2)

# CF1198B Welfare State 题解
说句闲话：这题搬到 GZFLS 的一场模拟赛中当了 T1，但是有人调了 1.5h 的错解……
## 题面大意
有 $n$ 个数，$q$ 个操作。 

操作有两种：

``1 p x``：将 $p$ 位置上的数变为 $x$。  

``2 x``：将所有小于 $x$ 的数变为 $x$。

输出经过 $q$ 次操作后的这 $n$ 个数。
## 解题思路
看到操作 ``2 x``，可能会想到平衡树的做法，不过我们同时做 ``1 p x`` 的话维护起来会很麻烦，所以平衡树大概会假。

可以构建一颗线段树：
```cpp
struct node{
	int l,r,laz,minn;
	bool have_laz;
}tree[4*N];
```
``minn`` 是区间最小值，``laz`` 是修改懒标记。

对于操作 ``2 x``，相当于做一次从 $1$ 到 $n$ 的区间修改，把最小值改为 $x$，可以打懒标记，需要时就下传。

对于操作 ``1 p x``，相当于做一次单点修改，把 $p$ 的值（也是从 $p$ 到 $p$ 的最小值）改为 $x$。

最后输出改完的序列时，直接从 $1$ 到 $n$ 做 $n$ 次单点查询即可。

不写动态开点的话，时间复杂度约为 $O(n+q\log{n}+n\log{n})$，由于 $n$、$q$ 数量级相当，所以可写作 $O(n+n\log{n})$。
## 参考代码
```cpp
#include<iostream>
using namespace std;
#define bulib build
const int INF=0x7fffffff;
const int N=1e6+10;
struct node{
	int l,r,laz,minn;
	bool have_laz;
}tree[4*N];
int a[N];
void build(int pos,int lft,int rgt){
	tree[pos].l=lft;
	tree[pos].r=rgt;
	if(lft==rgt){
		tree[pos].minn=a[lft];
		return;
	}
	int mid=(lft+rgt)/2;
	build(pos*2,lft,mid);
	build(pos*2+1,mid+1,rgt);
	tree[pos].minn=min(tree[pos*2].minn,tree[pos*2+1].minn);
}
void push_down(int pos){
	if(!tree[pos].have_laz) return;
	if(tree[pos*2].minn<tree[pos].laz){
		tree[pos*2].minn=tree[pos].laz;
		tree[pos*2].laz=tree[pos].laz;
		tree[pos*2].have_laz=true;
	}
	if(tree[pos*2+1].minn<tree[pos].laz){
		tree[pos*2+1].minn=tree[pos].laz;
		tree[pos*2+1].laz=tree[pos].laz;
		tree[pos*2+1].have_laz=true;
	}
	tree[pos].laz=0;
	tree[pos].have_laz=false;
}
void upd1(int pos,int dot,int x){
	if(dot<tree[pos].l||tree[pos].r<dot) return;
	if(tree[pos].l==tree[pos].r){
		tree[pos].minn=x;
		return;
	}
	push_down(pos);
	upd1(pos*2,dot,x);
	upd1(pos*2+1,dot,x);
	tree[pos].minn=min(tree[pos*2].minn,tree[pos*2+1].minn);
}
void upd2(int pos,int lft,int rgt,int x){
	if(lft<=tree[pos].l&&tree[pos].r<=rgt){
		if(x>tree[pos].minn){
			tree[pos].minn=x;
			tree[pos].laz=x;
			tree[pos].have_laz=true;
		}
		return;
	}
	if(tree[pos].minn>x) return;
	if(rgt<tree[pos].l||tree[pos].r<lft) return;
	push_down(pos);
	upd2(pos*2,lft,rgt,x);
	upd2(pos*2+1,lft,rgt,x);
}
int ask(int pos,int dot){
	if(dot<tree[pos].l||tree[pos].r<dot) return INF;
	if(tree[pos].l==tree[pos].r) return tree[pos].minn;
	push_down(pos);
	return min(ask(pos*2,dot),ask(pos*2+1,dot));
}
int n,q;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	cin>>q;
	while(q--){
		int op,xx,pp;
		cin>>op;
		if(op==1){
			cin>>pp>>xx;
			upd1(1,pp,xx);
		}else{
			cin>>xx;
			upd2(1,1,n,xx);
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ask(1,i)<<" ";
	}
	return 0;
}
```
[本代码可以通过 CF 的评测](https://www.luogu.com.cn/record/144356762)

需要注意的是，最近 CF 有些小问题，用某些 C++ 语言版本提交会无法编译，实测用 C++20 提交是不会出问题的。

另外，~~这个蒟蒻写的是大常数答辩~~，本代码在提交时不开 O2 可能会 TLE。

2024.1.25 written by [toolong114514](https://www.luogu.com.cn/user/477821).

（觉得还行，就点个赞吧）

---

## 作者：LJB00131 (赞：2)

**题意简述**

给你一个数列，有一些操作：

$1 \ p \ x$ 表示将数列第p个数修改为x

$2 \ x$ 表示将数列中所有数 $a_i = max(a_i, x)$

**思路**：

我们发现1操作是强制修改，影响到最大值（会强制改掉）
但我们不能在每一次2操作时修改所有数，那么自然想到分块。

每次做1修改时暴力改整块即可


**下面给出代码**

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
#define N 2005005
 
int n, m, a[N], atag[N], bl[N], blo;
 
void modify(int x, int y)
{
	for(int i = blo * (bl[x] - 1) + 1; i <= blo * bl[x]; i++)
	{
		if(i != x)
		{
			a[i] = max(atag[bl[i]], a[i]);
		}
		else a[i] = y;
	}
	atag[bl[x]] = 0;
}
 
void updata(int x)
{
	for(int i = bl[1]; i <= bl[n]; i++)
		atag[i] = max(atag[i], x);
}
 
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	blo = sqrt(n);
	for(int i = 1; i <= n; i++) bl[i] = (i - 1) / blo + 1;
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int opt, x, y;
		scanf("%d", &opt);
		if(opt == 1)
		{
			scanf("%d%d", &x, &y);
			modify(x, y);
		}
		else
		{
			scanf("%d", &x);
			updata(x);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		// ifcout << max(a[i], atag[bl[i]]) << ' ';
		// else cout << a[i] << ' ';
		cout << max(atag[bl[i]], a[i]) << ' ';
	}
	cout << endl;
	return 0;
}
```

---

## 作者：Zechariah (赞：1)

题意简单明了，一个区间$[1,n]$上有$n$个数，有以下操作：  
1. 将某个位置$p$的值改为$x$（修改操作）
2. 将整个区间中小于$x$的值改为$x$（覆盖操作，emmm姑且这样叫吧）

这个题有两种解法（我会的）：线段树模拟和一种巧妙些的方法  
首先说说简单粗暴点的线段树  
每个节点上需要存储一个$tag$标记以及区间的$max,min$值  
修改操作不必多说，标记下传不必多说  
对于覆盖操作，很容易想到，根据区间的$max,min$值决定是否打上标记或者是否往下递归  
最终查询答案，直接遍历整棵线段树到底把单点查出来  
这样似乎就做完了？提交一波......TLE  
上CF一看，数据呈现这样的规律  
小大小大小大小大小大小大小大......  
那么这样的话，我们的覆盖操作就需要一直往下进行，这样就有很大的时间开销  
所以开始的时候，我们把区间的值先排序，记录下原来的位置，这样就能避免上述情况  

上代码


```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 4e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int ans[N], pos[N];
struct Node {
	int left, right;
	int tag = -1, money, max, min;
}tree[N << 1];
struct Person {
	int id, a;
	bool operator <(const rg Person &s)const { return a < s.a; }
}p[N];
inl void pushup(rg int x) {
	tree[x].min = fast_IO::min(tree[x << 1].min, tree[x << 1 | 1].min);
	tree[x].max = fast_IO::max(tree[x << 1].max, tree[x << 1 | 1].max);
}
void build(rg int x, rg int l, rg int r) {
	tree[x].left = l; tree[x].right = r;
	if (l == r) { tree[x].min = tree[x].max = tree[x].money = p[l].a; return; }
	rg int mid = l + r >> 1;
	build(x << 1, l, mid); build(x << 1 | 1, mid + 1, r);
	pushup(x);
}
inl void pushdown(rg int x) {
	if (tree[x].tag == -1)return;
	tree[x << 1].tag = tree[x << 1 | 1].tag = tree[x].tag;
	tree[x << 1].max = tree[x << 1 | 1].max = tree[x].tag;
	tree[x << 1].min = tree[x << 1 | 1].min = tree[x].tag;
	tree[x].tag = -1;
}
void change(rg int x, rg int p, rg int data) {
	if (tree[x].left == tree[x].right) {
		tree[x].min = tree[x].max = tree[x].money = data;
		tree[x].tag = -1;
		return;
	}
	pushdown(x);
	rg int mid = tree[x].left + tree[x].right >> 1;
	if (p <= mid)change(x << 1, p, data);
	else change(x << 1 | 1, p, data);
	pushup(x);
}
void mark(rg int x, rg int data) {
	if (((~tree[x].tag) && (tree[x].tag >= data)))return;
	if (tree[x].tag == -1 && tree[x].min >= data)return;
	if (((~tree[x].tag) && (tree[x].tag < data)) || (tree[x].tag == -1 && tree[x].max <= data)) {
		tree[x].min = tree[x].tag = tree[x].max = data;
		return;
	}
	if (tree[x].left == tree[x].right)return;
	pushdown(x);
	mark(x << 1, data); mark(x << 1 | 1, data);
	pushup(x);
}
void getans(rg int x) {
	if (tree[x].left == tree[x].right) {
		if (~tree[x].tag)ans[p[tree[x].left].id] = tree[x].tag;
		else ans[p[tree[x].left].id] = tree[x].money;
		return;
	}
	pushdown(x); getans(x << 1); getans(x << 1 | 1);
}

int main() {
	rg int n = fast_IO::read();
	for (rg int i = 1; i <= n; ++i)p[i].a = fast_IO::read(), p[i].id = i;
	sort(p + 1, p + n + 1);
	for (rg int i = 1; i <= n; ++i)pos[p[i].id] = i;
	build(1, 1, n);
	rg int q = fast_IO::read();
	while (q--) {
		rg int tp = fast_IO::read();
		if (tp == 1) {
			rg int p = fast_IO::read(), x = fast_IO::read();
			change(1, pos[p], x);
		}
		else mark(1, fast_IO::read());
	}
	getans(1);
	for (rg int i = 1; i <= n; ++i)fast_IO::write(ans[i]), putchar(' ');
	return 0;
}

```

再说说较巧妙的方法  
我们很容易想到：对一个位置如果进行了修改操作，那么之前的所有覆盖操作都是无效的，并且如果有多个覆盖操作，这个位置最终只可能被改成覆盖操作中$x$最大的那一个  
因此就有了这样的解法：  
记录每个位置$[i]$的最后一次修改操作是哪一次操作$last[i]$，在操作方案的区间上求出覆盖操作的后缀最大值$cover[j]$（在这里修改操作相当于是$x=0$的覆盖操作），那么每个位置最后的值就应该是$max(a[i],cover[last[i]+1])$，其中$a$执行了所有的修改操作  

上代码
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 2e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int a[N], last[N], cover[N];

int main() {
	rg int n = fast_IO::read();
	for (rg int i = 1; i <= n; ++i)a[i] = fast_IO::read();
	rg int q = fast_IO::read();
	for (rg int i = 1; i <= q; ++i) {
		if ((fast_IO::read()) == 1) {
			rg int p = fast_IO::read();
			a[p] = fast_IO::read(); last[p] = i;
		}
		else cover[i] = fast_IO::read();
	}
	for (rg int i = q; i; --i)cover[i] = fast_IO::max(cover[i], cover[i + 1]);
	for (rg int i = 1; i <= n; ++i)fast_IO::write(fast_IO::max(a[i], cover[last[i] + 1])), putchar(' ');
	return 0;
}

```


---

## 作者：OIerZhao_1025 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1198B)

## 题意
有一个长度为 $n$ 的数列 $a_1,a_2,\dots,a_n$，对它进行 $q$ 次操作，每次操作都是下列两种类型一：
- $1\ p\ x$（$1\le p\le n,0\le x\le10^9$）：将数列中第 $p$ 个元素替换为 $x$；
- $2\ x$（$0\le x\le 10^9$）：表示将数列中所有小于 $x$ 的元素全部替换为 $x$。
你的任务是确定完成 $q$ 次操作之后，数列中每个元素各是多少。

## 思路
暴力以后直接 TLE 了。\
发现这道不能直接暴力，我们可以通过样例发现，操作 $2$ 的最后一次的最大操作会对所有的操作 $2$ 产生影响，也就是其他的执行并没有用处，所以会省下很多时间，不至于再次 TLE。但再次提交时又再次 WA 掉了。\
后来发现，第一个样例就不对，这才发现先执行前面的操作 $1$ 最后再执行那个操作 $2$ 是不行的，最后得出了一个结论，在那个操作 $2$ 之后的所有在执行那个操作 $1$ 还需要执行，不能提前，要放在最后。\
最后，总结一下要点：
- 不能直接暴力，要节省在执行操作 $2$ 上面；
- 最后的操作 $1$ 是不能提前的，要放在后面。

## code
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
const int maxn=4e5+10; 
int n,q,a[maxn],cnt,ans,s[maxn],Max[maxn],op,len,v;//全局变量 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];//输入 
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		cin>>op;
		if(op==1)
		{
			cin>>len>>v;
			a[len]=v,s[len]=i;
		}
		else
		{
			cin>>v;
			Max[i]=v;
		}
	}
	for(int i=q;i>=0;i--)
		Max[i]=max(Max[i],Max[i+1]);//操作2 
	for(int i=1;i<=n;++i)
		cout<<max(a[i],Max[s[i]])<<" ";//最后输出结果 
	return 0;
}
```

---

## 作者：Kawaii_qiuw (赞：0)

### 题意

给出 $n$ 个数，$q$ 次操作，如果 $op \to 1$，则输入数字的下标（从 $1$ 开始），将该值改修为给定的数；如果是 $2$，则将所有区间内的小于等于给定数全部换为给出的数，即一个单点修改加一个区间修改。

### 思路

线段树进行操作，先记录每个节点的数据，用一个懒惰标记进行单点修改和区间修改标记，区间修改的话，考虑到是整个区间内数据的修改，对于每次的区间修改操作先记录下来，记录最大给出值，最后进行标记传输，输出最后结果。

### 代码

注：由于 RemoteJudge 暂不可用，所以没有 AC 记录。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
struct node {
	int l, r, minn, f;
}g[N<<2];
void up(int rt) {
	g[rt].minn = min(g[rt<<1].minn, g[rt<<1|1].minn); //记录左右孩子的最小值 
}

void down(int rt) {
	if (g[rt].f) {
		// 如果当前节点要更改的值比当前区间的最小值还小，就不需要覆盖，否则覆盖 
		int f = g[rt].f;
		g[rt<<1].f = max(g[rt<<1].f, f); // 标记最大值 
		g[rt<<1|1].f = max(g[rt<<1|1].f, f);
		g[rt<<1].minn = max(g[rt<<1].minn, f);
		g[rt<<1|1].minn = max(g[rt<<1|1].minn, f);
		g[rt].f = 0;
	}
}

void build(int l, int r, int rt) {
	g[rt].l = l;
	g[rt].r = r;
	g[rt].f = 0;
	if (l == r) {
		scanf("%d", &g[rt].minn);
		return ;
	} 
	int m = (l + r) >> 1;
	build(l, m, rt<<1);
	build(m + 1, r, rt<<1|1);
	up(rt);
}

void update1(int l, int r, int val, int rt) { // 单点修改 
	if (g[rt].l == g[rt].r) {
		g[rt].minn = val;
		return ;
	}
	down(rt);
	int m = (g[rt].l + g[rt].r) >> 1;
	if (l <= m) update1(l, r, val, rt<<1);
	if (m < r) update1(l, r, val, rt<<1|1);
	up(rt);
}

void update2(int val, int rt) { // 区间修改 
	g[rt].minn = max(g[rt].minn, val);
	g[rt].f = max(g[rt].f, val);
	return ;	
}

int query(int l, int r, int rt) { // 查询 
	if (g[rt].l == g[rt].r) {
		return g[rt].minn;
	}
	down(rt);
	int m = (g[rt].l + g[rt].r) >> 1;
	if (l <= m) return query(l, r, rt<<1);
	if (m < r) return query(l, r, rt<<1|1);
} 

int main() {
	int n, t, a, b, c;
	scanf("%d", &n);
	build(1, n, 1);
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &a);
		if (a == 1) {
			scanf("%d%d", &b, &c);
			update1(b, b, c, 1);
		} else {
			scanf("%d", &b);
			update2(b, 1);
		}
	}
	for (int i = 1; i <= n; i++) {
		int ans = query(i, i, 1);
		printf("%d", ans);
		if (i < n) printf(" ");
	}
	return 0;
}
```

完结撒花。

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1198B)

## 思路
对于一个元素来说，对其进行的一些**连续**（中间没有操作 $1$）的操作 $2$ 中，只有 $x$ 最大的一次才真正有效。而对其进行的操作 $1$ 只有最后一次才可能有效，且会覆盖掉之前的所有操作 $2$。那么就可以记录下最后一次操作 $1$（没有操作则是原值）与其后执行的 $x$ 最大的操作 $2$，并进行比较，而求“其后执行的 $x$ 最大的操作 $2$”很容易想到使用后缀最大值来完成。

## 具体做法
对于两种操作，分别执行以下内容：
1. 将 $a_{p}$ 覆盖成 $x$，并记录下操作时间。
2. 令 $op2_{i} = x$。

然后从后往前循环每个 $i \in [1, q]$，执行以下操作：
* 令 $op2_{i} = \max(op2_{i}, op2_{i + 1})$。

循环每个 $i \in [1, n]$，执行以下操作：
* 令 $a_{i} = \max(a_{i}, op2_{t_{i}})$。

## AC Code
```cpp
/*
from:CF-1198B
difficulty:1600
*/
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;

const int maxn = 2e5 + 10;
const int maxq = 2e5 + 10;

int n;
int a[maxn];
int q;
	int op, p, x;

int t1[maxn], op2[maxq];

int main () {
	scanf("%i", &n);
	FOR (1, n, i) {scanf("%i", &a[i]);}
	scanf("%i", &q);
	FOR (1, q, i) {
		scanf("%i", &op);
		if (op == 1) {
			scanf("%i%i", &p, &x);
			
			a[p] = x;
			t1[p] = i;
		}else {
			scanf("%i", &x);
			
			op2[i] = x;
		}
	}
	
	RFOR(0, q - 1, i) {op2[i] = MAX(op2[i], op2[i + 1]);}
	
	FOR (1, n, i) {printf("%i ", MAX(a[i], op2[t1[i]]));}
	printf("\n");
	return 0;
}
```

---

## 作者：ljc20020730 (赞：0)

# 我会线段树!!!

显然我们只需要使用一个懒标记维护当前值即可。

后来的标记和旧标记求max就好了。

# 如果只有$1$个人不要忘记更新$1$号点哦。

```cpp
# include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n;
int val[N];
struct Segment_Tree{
	int tag,ret;
	Segment_Tree() { tag=ret=-1;}
}tr[N<<2];
# define ls (x<<1)
# define rs (x<<1|1)
# define lson x<<1,l,mid
# define rson x<<1|1,mid+1,r
# define mid (l+r>>1)
void build(int x,int l,int r)
{
	if (l==r) { tr[x].ret = val[l]; return; }
	build(lson); build(rson);
}
void down(int x)
{
	if (tr[x].tag==-1) return;
	if (tr[ls].ret!=-1) tr[ls].ret=max(tr[ls].ret,tr[x].tag);
	if (tr[rs].ret!=-1) tr[rs].ret=max(tr[rs].ret,tr[x].tag);
	tr[ls].tag = (tr[ls].tag == -1)?tr[x].tag:max(tr[x].tag,tr[ls].tag);
	tr[rs].tag = (tr[rs].tag == -1)?tr[x].tag:max(tr[x].tag,tr[rs].tag);
	tr[x].tag=-1;
}
void update(int x,int l,int r,int pos,int val)
{
	if (l==r) { tr[x].ret=val; return;}
	down(x);
	if (pos<=mid) update(lson,pos,val);
	else update(rson,pos,val);
}
int query(int x,int l,int r,int pos)
{
	if (l==r) return tr[x].ret;
	down(x);
	if (pos<=mid) return query(lson,pos);
	else return query(rson,pos);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&val[i]);
	build(1,1,n);
	int q; scanf("%d",&q);
	while (q--) {
		int p,x,y; scanf("%d%d",&p,&x);
		if (p==1) scanf("%d",&y),update(1,1,n,x,y);
		else {
			tr[1].tag = (tr[1].tag==-1)?x:max(tr[1].tag,x);
			if (tr[1].ret != -1) tr[1].ret=max(tr[1].ret,tr[1].tag);
		}
	}
	for (int i=1;i<=n;i++)
	 printf("%d ",query(1,1,n,i));
	puts("");
	return 0;
}

```

---

## 作者：LinkinPony (赞：0)

思路~~抄~~来自官方题解

观察每位市民,可以发现影响其工资的因素仅有最后一次事件1以及**最后一次事件1后** **最大的** 事件2.比较自然的想法是记录并比对时间戳,但这样复杂度难以保证.

此时可以将所有事件读入后**倒序处理**,这样每个最大的事件2必定位于每位市民最后一次事件1后

附代码:

```cpp
//CF1198B
#include <bits/stdc++.H>
using namespace std;
const int maxn = 200005;
int ans[maxn],q2 = -1;
bool vis[maxn];
struct Order{
	bool typ;//0 = 2;1 = 1
	int a,b;
}order[maxn]; 
int main(){
	int n;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)scanf("%d",&ans[i]);
	int q;
	scanf("%d",&q);
	for(int i = 1;i <= q;i++){
		int ord;
		scanf("%d",&ord);
		if(ord == 1){
			order[i].typ = 1;
			scanf("%d%d",&order[i].a,&order[i].b);
		}
		else if(ord == 2){
			order[i].typ = 0;
			scanf("%d",&order[i].a);
		}
	}
	for(int i = q;i;i--){
		if(order[i].typ){
			int tar = order[i].a;
			if(!vis[tar]){
				vis[tar] = 1;
				ans[tar] = max(q2,order[i].b);
			}
		}
		else q2 = max(q2,order[i].a);
	}
	
	for(int i = 1;i <= n;i++){
		if(!vis[i])ans[i] = max(q2,ans[i]);
		printf("%d ",ans[i]);
	}
	return 0; 
}

```


---

## 作者：世末OIer (赞：0)

这题其实可以水过去，线段树好想啊。

用个懒标记就可以了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
int n,q,tp,x,y;
int tr[1600005];
int laz[1600005];
inline void build(int x,int l,int r){  //造树
	if(l==r){
		cin>>tr[x];
		return;
	}
	int md=l+r>>1;
	build(x*2,l,md);
	build(x*2+1,md+1,r);
}
inline void pushd(int x){
	if(laz[x]==-1)return;
	tr[x]=max(tr[x],laz[x]);
	laz[x*2]=max(laz[x*2],laz[x]);
	laz[x*2+1]=max(laz[x*2+1],laz[x]);
	laz[x]=-1;
}
inline void upd1(int x,int l,int r,int a,int b){//单点更改
	pushd(x);
	if(l==r){
		tr[x]=b;
		return;
	}
	int md=l+r>>1;
	if(a<=md)upd1(x*2,l,md,a,b);
	else upd1(x*2+1,md+1,r,a,b);
}
inline int ask(int x,int l,int r,int id){//单点查询
	pushd(x);
	if(l==r)return tr[x];
	int md=l+r>>1;
	if(id<=md)return ask(x*2,l,md,id);
	else return ask(x*2+1,md+1,r,id);
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	memset(laz,-1,sizeof(laz));
	build(1,1,n);
	cin>>q;
	while(q--){
		cin>>tp;
		if(tp==1){
			int x,y;
			cin>>x>>y;
			upd1(1,1,n,x,y);   //单点更改
		}else{
			cin>>x;
			laz[1]=max(laz[1],x);//整体更改
		}
	}
	for(int i=1;i<=n;++i) cout<<ask(1,1,n,i)<<' ';
	cout<<endl;
}
```

---

## 作者：逃课小姐MS (赞：0)

其实这个题目是一个简单的分块

看到2s的时间限制和2*1e5的数据就发现可以在1s左右跑完n*sqrt(n)

思路其实简单粗暴：

操作1:更改一个值 

这个就是暴力sqrt(n),把那一块的所有数与lazy取一个最大值,然后暴力修改那个点的值 

操作2:全体变成他们和x的最大值 

更新每一个lazy,lazy[i]=max(lazy[i],x); 

代码如下，简单易懂的呢 

``` 
#include<bits/stdc++.h>
#define N 2000010
using namespace std;
int n,m,opt;
int a[N],block[N],lazy[N];
void update(int x,int k){
	if(lazy[block[x]]!=0){
		for(int i=(block[x]-1)*m+1;i<=block[x]*m;i++){
			a[i]=max(lazy[block[x]],a[i]);
		}
		lazy[block[x]]=0;
	}
	a[x]=k;
}
void minner(int k){
	for(int i=1;i<=block[n];i++){
		lazy[i]=max(lazy[i],k);
	}
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    m=sqrt(n);
    for(int i=1;i<=n;i++) block[i]=(i-1)/m+1;
    int q;
    cin>>q;
    for(int i=1;i<=q;i++){
    	int x,k;
        scanf("%d%d",&opt,&x);
        if(opt==1) scanf("%d",&k),update(x,k);
        else minner(x);
    }
	for(int i=1;i<=n;i++) cout<<max(lazy[block[i]],a[i])<<" ";
    return 0;
}
``` 

---

