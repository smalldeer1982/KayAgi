# DerrickLo's Game (UBC002B)

## 题目描述

在 DerrickLo 的游戏中，他有 $n$ 个属性，第 $i$ 个属性的初始值为 $a_i$，接下来根据游戏进度变化，他会给你一些修改操作或者询问，形如：

- `1 k x`，将 $a_k$ 变为 $x$（修改操作）。
- `2 l r`，问仅通过以下操作（**但不真正执行**）使区间变为相同的数的最小代价（询问）。操作分别是：

1. 选择整数 $p$，将 $a_p$ 增加 $1$，代价为 $1$。
2. 选择整数区间 $x,y$，将 $a_x\dots a_y$ 全部变为 $\max\limits_{i=x}^y a_i$，代价为 $(y-x+1)^2$。

## 说明/提示

**样例说明**

第一次询问中，选择 $a_1$ 使其增加 $1$ 即可，代价为 $1$。

第二次询问中，由于区间大小为 $1$，所以不需要任何操作。

**数据范围**

对于 $100\%$ 的数据，保证输入数据全部为整数，且 $1\le n,q,a_i\le 2\times 10^5$，对于修改操作，$1\le k\le n$，$1\le x\le 2\times 10^5$；对于询问，$1\le l\le r\le n$。

## 样例 #1

### 输入

```
3 2
1 2 3
2 1 2
2 1 1```

### 输出

```
1
0```

# 题解

## 作者：suzhikz (赞：5)

首先，每次询问，操作后的序列显然是原序列中的最大值。比这个值大显然不会更优秀。

然后区间赋最大值显然是两个两个赋值比一大段的赋值更优秀，因为 $4(n-1)\le n^2$。

所以每个数赋值成最大值代价最多是 4。

考虑什么情况下代价小于 4，显然是这个数和最大值的差距小于 4。

现在我们可以把询问的序列中的数分成和最大值差距大于等于 4 和小于等于 4 的来考虑。

考虑如何快速计算小于等于 4 的个数，可以对每个值开一颗权值线段树，这样可以快速查询一个区间中某个数的出现次数。

然后查询最大值再开一颗线段树即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define db double
#define il inline
using namespace std;
void read(int &x){x=0;int f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=f;}
void read(ll &x){x=0;int f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=f;}
const int N=2e5+5;
int n,q,a[N];
struct node{
	int tree[N*4];
	void push_up(int x){
		tree[x]=max(tree[x<<1],tree[x<<1|1]);
	}
	void build(int x,int l,int r){
		if(l==r)tree[x]=a[l];
		else {
			int mid=(l+r)/2;build(x<<1,l,mid);build(x<<1|1,mid+1,r);
			push_up(x); 
		}
	}
	void update(int x,int l,int r,int q){
		if(l==r)tree[x]=a[l];
		else {
			int mid=(l+r)/2;
			if(q<=mid)update(x<<1,l,mid,q);
			else update(x<<1|1,mid+1,r,q);
			push_up(x); 
		}
	}
	int query(int x,int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r)return tree[x];
		int re=0,mid=(l+r)/2;
		if(ql<=mid)re=query(x<<1,l,mid,ql,qr);
		if(qr>mid)re=max(re,query(x<<1|1,mid+1,r,ql,qr));
		return re;
	}
}T;
int tree[N*50],ls[N*50],rs[N*50],tot;
int rt[N];
il void push_up(int x){
	tree[x]=tree[ls[x]]+tree[rs[x]];
}
void update(int x,int l,int r,int q,int w){
	if(l==r){
		tree[x]+=w;return ;
	}int mid=(l+r)/2;
	if(q<=mid){
		if(ls[x]==0)ls[x]=++tot;
		update(ls[x],l,mid,q,w);
	}else{
		if(rs[x]==0)rs[x]=++tot;
		update(rs[x],mid+1,r,q,w);
	}
	push_up(x);
}
int query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r)return tree[x];
	int re=0,mid=(l+r)/2;
	if(ql<=mid&&ls[x])re=query(ls[x],l,mid,ql,qr);
	if(qr>mid&&rs[x])re+=query(rs[x],mid+1,r,ql,qr);
	return re;
}
int main(){
	read(n);read(q);
	for(int i=1;i<=200000;i++){
		rt[i]=++tot;
	}
	for(int i=1;i<=n;i++){
		read(a[i]);
		update(rt[a[i]],1,n,i,1);
	}
	T.build(1,1,n);
	while(q--){
		int op,l,r;
		read(op);read(l);read(r);
		if(op==1){
			update(rt[a[l]],1,n,l,-1);
			a[l]=r;
			update(rt[a[l]],1,n,l,1);
			T.update(1,1,n,l);
		}else{
			int tmp=T.query(1,1,n,l,r),cnt=0,cnt2=0,ans=0;
			for(int i=tmp;i>=max(1,tmp-3);i--){
				cnt2=query(rt[i],1,n,l,r);
				ans+=(tmp-i)*cnt2;
				cnt+=cnt2;
			}
			ans+=(r-l+1-cnt)*4;
			printf("%d\n",ans);
		}
	}
	
	
	return 0;
}

```

---

## 作者：Dicer_L (赞：5)

## solution

首先观察一下题面，发现好像不是很可以合并，然后考虑一下根号算法，发现被卡了。

然后再读题，诶这个操作 $2$ 是不是有一个美妙的性质？

> 选择整数区间 $x,y$，将 $a_x\dots a_y$ 全部变为 $\max\limits_{i=x}^y a_i$，代价为 $(y-x+1)^2$。

这个东西在长度为 $2$ 的时候费用最小。于是这个操作就等价于选择两个数，花费 $4$ 的代价将较小的数变成另一个数。

然后这个观察一下这个操作 $1$ 好像又是要把一个数加到区间最大值，花费为区间最大值和它数值的差值。

然后计算答案的部分就很明显了：和区间最大值相等的数不用花费，比它小 $1$ 到 $3$ 的数用操作 $1$ 更优，其他每个数都是操作 $2$ 更优，花费都为 $4$。

那么我只要维护区间内最大值和与它相等、比它小 $1$、比它小 $2$、比它小 $3$ 的数的个数。还有一个比它小 $4$ 及以下的数的个数就可以了。

此时好像又变得可以合并了？？

于是开始线段树。每个节点维护上述值，合并时讨论左右两个线段的最大值的差值，从而进行数据的合并；查询时把所有 $[l,r]$ 在线段树上查到的线段记录下来，合并到一个空的节点上。于是就可以根据这个节点信息计算答案了。

## code

```cpp
#include<bits/stdc++.h>

namespace IO {
	inline int read() {
		int ret = 0, f = 1;char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			ret = (ret << 1) + (ret << 3) + (ch ^ 48);
			ch = getchar();
		}
		return ret * f;
	}
	void write(long long x) {
		if (x < 0) putchar('-'), x = -x;
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace IO;
using namespace std;

const int maxn = 2e5 + 5;

int n, q;
int a[maxn], b[maxn];

namespace seg {
	int L[maxn << 2], R[maxn << 2], Max[maxn << 2], s[maxn << 2][5], tot;
//注意 s[x][4] 是和 max 差值大于等于 4 的数的个数
	
	int len(int x) {
		return R[x] - L[x] + 1;
	}
	
	void upd(int x, int y) {//合并两个节点信息
		switch (Max[x] - Max[y]) {
			case 0 : {
				s[x][0] += s[y][0];
				s[x][1] += s[y][1];
				s[x][2] += s[y][2];
				s[x][3] += s[y][3];
				s[x][4] += s[y][4];
				break;
			}
			case 1 : {
				s[x][1] += s[y][0];
				s[x][2] += s[y][1];
				s[x][3] += s[y][2];
				s[x][4] += s[y][3] + s[y][4];
				break;
			}
			case 2 : {
				s[x][2] += s[y][0];
				s[x][3] += s[y][1];
				s[x][4] += s[y][2] + s[y][3] + s[y][4];
				break;
			}
			case 3 : {
				s[x][3] += s[y][0];
				s[x][4] += s[y][1] + s[y][2] + s[y][3] + s[y][4];
				break;
			}
			default : {
				s[x][4] += len(y);
				break;
			}
		}
	}
	
	void Clear(int x) {
		s[x][0] = s[x][1] = s[x][2] = s[x][3] = s[x][4] = Max[x] = 0;
	}
	
	void pushup(int x) {
		Clear(x);//Clear 位置错了调了 20min
		Max[x] = max(Max[x << 1], Max[x << 1 | 1]);
		upd(x, x << 1);
		upd(x, x << 1 | 1);
	}
	
	void build(int l, int r, int x) {
		L[x] = l, R[x] = r;
		if (l == r) {
			Max[x] = a[l];s[x][0] = 1;
			return;
		}
		int mid = l + r >> 1;
		build(l, mid, x << 1);
		build(mid + 1, r, x << 1 | 1);
		pushup(x);
	}
	
	void update(int p, int x, int d) {
		if (L[x] == R[x] && L[x] == p) {
			Max[x] = d;
			return;
		}
		int mid = L[x] + R[x] >> 1;
		if (p <= mid) update(p, x << 1, d);
		else update(p, x << 1 | 1, d);
		pushup(x);
	}
	
	int queryMax(int l, int r, int x) {
		if (L[x] >= l && R[x] <= r) {
			b[++tot] = x;
			return Max[x];
		}
		int mid = L[x] + R[x] >> 1, ans = 0;
		if (l <= mid) ans = max(ans, queryMax(l, r, x << 1));
		if (r > mid) ans = max(ans, queryMax(l, r, x << 1 | 1));
		return ans;
	}
	
	long long solve(int l, int r) {
		tot = 0;Clear((maxn << 2) - 1);
//可以不用(maxn << 2) - 1，用一个空节点就行
		int maxx = queryMax(l, r, 1);long long ans = 0ll;
		Max[(maxn << 2) - 1] = maxx;
		for (int i = 1;i <= tot;i++) upd((maxn << 2) - 1, b[i]);
		for (int i = 1;i <= 3;i++) ans += i * s[(maxn << 2) - 1][i];//和 max 差值小于 4 的数的花费
		ans += s[(maxn << 2) - 1][4] * 4;//使用操作 2 的花费
		return ans;
	}
}

using namespace seg;

int main() {
	n = read(), q = read();
	
	for (int i = 1;i <= n;i++) a[i] = read();
	
	build(1, n, 1);
	
	while (q--) {
		int op = read(), l = read(), r = read();
		if (op == 1) update(l, 1, r);
		else write(solve(l, r)), putchar(10);
	}
	
	return 0;
}
```

---

## 作者：Crazyouth (赞：4)

这里是官解。

### sol

挺诈骗的一题啊。

首先询问中我们的目标是把所有数变相等。不难看出实际上是把所有数变为最大值。

考虑变形询问中的操作 $2$。如果操作 $2$ 选择了区间 $[l,r]$ 且 $r-l+1>2$，那么你实际上可以通过 $r-l$ 次选择长度为 $2$ 的区间来达到完全等同的效果。比较一下两者代价大小？令 $k=r-l+1$，前者就是 $k^2$ 的代价，后者则是 $2^2\times (k-1)$。前者代价减后者代价为 $k^2-4k+4=(k-2)^2\ge 0$。因此选择长度为 $2$ 的区间一定更优。

此时不难想到，一个数需要变成最大值无非通过反复加一或者与旁边的数组成长为 $2$ 的区间然后进行一次操作 $2$。因此询问转化为给定 $l,r$，求 $\displaystyle\sum_{i=l}^r \min((\max\limits_{i=l}^ra_i)-a_i,4)$。

由于 $4$ 这个数太小了，考虑直接暴力找 $mx,mx-1,mx-2,mx-3$ 在区间的出现数量（当然也不是纯暴力），这样除了这些数以外的数全部都是花费 $4$ 的代价，而这些数分别花费 $0,1,2,3$ 的代价。对于区间找数的方法，容易想到在某种存有出现的下标的容器上二分。但由于有修改操作，所以我们这个容器还需要支持从中间删除数。那么符合这样条件的容器自然是 pbds 中的 tree。由于值域小，我们直接开 $2\times 10^5$ 个 tree，第 $i$ 个存的是 $i$ 在序列中的出现下标。每次查询就使用 `order_of_key()` 函数做个差分找区间某数的出现次数即可。修改的话，在原 tree 中删除下标 $k$，再在新 tree 中加入它就行了。

### std

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
const int N=200010;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> tr[N];
int mx[N<<2],a[N],mxcnt[4];
void build(int s,int t,int p)
{
	if(s==t)
	{
		mx[p]=a[s];
		return;
	}
	int m=s+t>>1;
	build(s,m,p<<1);build(m+1,t,p<<1|1);
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
}
void upd(int k,int s,int t,int p,int c)
{
	if(s==t)
	{
		mx[p]=c;
		return;
	}
	int m=s+t>>1;
	if(k<=m) upd(k,s,m,p<<1,c);
	else upd(k,m+1,t,p<<1|1,c);
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
}
int qry(int l,int r,int s,int t,int p)
{
	if(l<=s&&t<=r) return mx[p];
	int m=s+t>>1,ans=0;
	if(l<=m) ans=qry(l,r,s,m,p<<1);
	if(r>m) ans=max(ans,qry(l,r,m+1,t,p<<1|1));
	return ans;
}
int main()
{
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i],tr[a[i]].insert(i);
	build(1,n,1);
	while(q--)
	{
		int opt,x,y;
		cin>>opt>>x>>y;
		if(opt==1)
		{
			upd(x,1,n,1,y);
			tr[a[x]].erase(x);
			a[x]=y;
			tr[a[x]].insert(x);
		}
		else
		{
			int mx=qry(x,y,1,n,1);
			int ans=0;
			for(int i=0;i<4;i++)
			{
				if(mx-i>0&&tr[mx-i].size())
				mxcnt[i]=(tr[mx-i].order_of_key(y+1)-tr[mx-i].order_of_key(x));
				else
				mxcnt[i]=0;
				ans+=mxcnt[i]*i;
			}
			cout<<ans+(y-x+1-mxcnt[0]-mxcnt[1]-mxcnt[2]-mxcnt[3])*4<<'\n';
		}
	}
}
```

---

## 作者：xxseven (赞：3)

好玩！

先分析查询的性质。

由于没有使数字减小的操作，因此最终所有数不小于**原来的**最大值。显然使最终的数更大不会使答案变优，所以只需要将所有数变成区间内最大值即可。

注意到第二种操作的代价是区间长度的平方，这意味着**区间长度越大，扩展区间的花费越大**。但是实际上，如果我们想要将区间 $[l,r]$ 扩展到区间 $[l,r+1]$，可以先操作 $[l,r]$ 再操作 $[r,r+1]$，取得的效果是相同的。  
这可以看做在 $[r,r]$ 的基础上扩展了 $[r,r+1]$，显然花费更小。

依此归纳，可以得到我们只会操作长度为 $2$ 的区间，其代价为 $4$，可以将一个数变为区间内的最大值。

同时，我们还可以使用第一种操作使一个数变为区间内的最大值，代价为区间内最大值与该数的差。

对于每个数贪心选择使用的操作种类，那么只需要记录区间内与最大值的差值为 $0,1,2,3$ 的数的个数。

用线段树维护单点修改即可，时间复杂度 $O(q\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+6;
int n,q,a[N];
struct node{
	int mx,a,b,c,d;
	node(){mx=-1e9,a=b=c=d=0;}
	node operator + (node e){
		node r=*this;
		if(r.mx<e.mx) swap(r,e);
		if(r.mx==e.mx) r.a+=e.a,r.b+=e.b,r.c+=e.c,r.d+=e.d;
		if(r.mx==e.mx+1) r.b+=e.a,r.c+=e.b,r.d+=e.c;
		if(r.mx==e.mx+2) r.c+=e.a,r.d+=e.b;
		if(r.mx==e.mx+3) r.d+=e.a;
		return r;
	}
}t[N<<2];
#define mid (L+R>>1)
void build(int pos,int L,int R){
	if(L==R) return t[pos].mx=a[L],t[pos].a=1,void();
	build(pos<<1,L,mid); build(pos<<1|1,mid+1,R);
	t[pos]=t[pos<<1]+t[pos<<1|1];
}
void upd(int pos,int L,int R,int x,int y){
	if(L==R) return t[pos].mx=y,void();
	if(x<=mid) upd(pos<<1,L,mid,x,y);
	else upd(pos<<1|1,mid+1,R,x,y);
	t[pos]=t[pos<<1]+t[pos<<1|1];
}
node qry(int pos,int L,int R,int x,int y){
	if(x>R||y<L) return node();
	if(x<=L&&R<=y) return t[pos];
	return qry(pos<<1,L,mid,x,y)+qry(pos<<1|1,mid+1,R,x,y);
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;++i) cin>>a[i];
	build(1,1,n);
	for(int op,x,y,i=1;i<=q;++i) {
		cin>>op>>x>>y;
		if(op==1) upd(1,1,n,x,y);
		else {
			auto e=qry(1,1,n,x,y);
			cout<<e.b+e.c*2+e.d*3+((y-x+1)-(e.a+e.b+e.c+e.d))*4<<'\n';
		}
	}
	return 0;
}


```

希望这篇题解能够帮到你！

---

## 作者：zhoumurui (赞：3)

~~大家好，我非常喜欢暴力数据结构，因此我用分块过了这道题~~

### 题面展示

维护一个长度为 $n$ 的序列，接下来有 $q$ 次操作：

- 修改：将序列的第 $k$ 项修改为 $x$。

- 询问：**假如**对序列进行若干次改变，至少需要多少代价使得 $a_1 = a_2 = \dots = a_n$。**询问对原序列不做影响。**

询问中的两种改变分别为：

1. 指定整数 $k$，花费 $1$ 的代价，让序列的第 $k$ 项 $+1$。

2. 指定整数 $l,r$（$l<r$），花费 $(r-l+1)^2$ 的代价，让序列从第 $l$ 项到第 $r$ 项全部修改为 $\max\limits_{i=l}^{r} a_i$。

### 前置知识

分块。

### 解题思路

**结论** $1$：对于第二种改变，令 $r=l+1$ 一定不劣。

**证明** 假设有一种最优解，进行了一次满足 $r > l+1$ 的改变。假设 $\max\limits_{i=l}^{r} a_i = M$，那么这个操作将 $[l,r]$ 中的所有数都修改成了 $M$。

显然 $[l,r]$ 中至少有一个数是 $M$。令 $a_k = M$，其中 $l \le k \le r$。

那么我们可以考虑这样一个方式将 $[l,r]$ 中所有数变成 $M$：

1. 选择第二种改变，区间为 $[k-1,k]$。显然 $a_{k-1}$ 变为 $M$。

2. 选择第二种改变，区间为 $[k-2,k-1]$。显然 $a_{k-2}$ 变为 $M$。

3. $\dots$

以此类推，我们将 $[l,k]$ 中的所有数变成了 $M$。类似地可以将 $[k+1,r]$ 中的所有数变成 $M$。

比较一下两种方式的花费。如果一次解决，花费是 $(r-l+1)^2$，如果分多次解决，花费变为 $4(r-l)$。

令 $r-l = t$，那么只需证明 $4t \le (t+1)^2$ 即可。

将右边的式子拆开，就会发现这等价于 $2t \le t^2+1$，套一个均值不等式就证明了。

---

**结论** $2$ 令 $\max\limits_{i=l}^{r} a_i = M$，询问是求 $\sum\limits_{i=l}^{r} \min(4,M-a_i)$。

**直观理解** 令 $a_k = M$，考虑从 $k$ 向左右两边分别递推，该结论比较直观。

---

$\min(4,M-a_i)$ 这种东西，既可以用线段树维护，也可以用分块维护。

考虑用分块维护。令 $mx_{b}$ 表示块 $b$ 中的最大值，$s_{b,i}$ 表示块 $b$ 中 $mx_{b}-i$ 的数量。**特别地，$s_{b,4}$ 表示块 $b$ 中小于 $mx_{b}-4$ 的数的数量，因为再小就对答案没有影响了。**

对于修改，直接重新处理修改所在块的 $mx$ 数组和 $s$ 数组。

对于查询，不跨块的暴力处理。

跨块的，首先用和模版差不多的防止将区间最大值计算出来，然后将两边不完整的块暴力处理，那么只剩下中间的整块。

对于整块，我们能够计算出块内最大值与区间最大值之差，然后借此处理整块的贡献。具体地，我们看代码：

(代码中 `i` 是块的编号，`Mx` 是整个区间的最大值)

```cpp
switch(Mx-mx[i]){
    case 0:
    ans+=s[i][1]+2*s[i][2]+3*s[i][3]+4*s[i][4];
    break;
    case 1:
    ans+=s[i][0]+2*s[i][1]+3*s[i][2]+4*(s[i][3]+s[i][4]);
    break;
    case 2:
    ans+=2*s[i][0]+3*s[i][1]+4*(s[i][2]+s[i][3]+s[i][4]);
    break;
    case 3:
    ans+=3*s[i][0]+4*(s[i][1]+s[i][2]+s[i][3]+s[i][4]);
    break;
    default:
    ans+=4*(s[i][0]+s[i][1]+s[i][2]+s[i][3]+s[i][4]);
    break;
}
```

可以看出做法是利用 $M-mx[i]$ 的值，得出 $s_{i,j}$ 对于答案的贡献。

那么修改和查询都在 $O(\sqrt n)$ 的时间复杂度内完成了。整个代码的时间复杂度为 $O(n + q \sqrt n)$，可以通过本题。

### 核心代码展示

```cpp
int a[200005],L[2005],R[2005],bel[200005];
int mx[2005],s[2005][5];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;i++){
    	cin>>a[i];
	}
    int B=sqrt(n);
    R[0]=0;
    for (int i=1;i<=B;i++){
        L[i]=R[i-1]+1;
        R[i]=i*B;
    }
    R[B]=n;
    for (int i=1;i<=B;i++){
        mx[i]=s[i][0]=s[i][1]=s[i][2]=s[i][3]=s[i][4]=0;
        for (int j=L[i];j<=R[i];j++){
            bel[j]=i;
            mx[i]=max(mx[i],a[j]);
        }
        for (int j=L[i];j<=R[i];j++){
            s[i][min(4LL,mx[i]-a[j])]++;
        }
    }
    while (m--){
        int op,l,r;
		cin>>op>>l>>r;
        if (op==1){
            a[l]=r;
            int b=bel[l];mx[b]=0;
            for (int j=L[b];j<=R[b];j++){
                mx[b]=max(mx[b],a[j]);
            }
            s[b][0]=s[b][1]=s[b][2]=s[b][3]=s[b][4]=0;
            for (int j=L[b];j<=R[b];j++){
                s[b][min(4LL,mx[b]-a[j])]++;
            }
            continue;
        }
        int bl=bel[l],br=bel[r];
        if (bl==br){
            int mx=0,ans=0;
            for (int i=l;i<=r;i++){
                mx=max(mx,a[i]);
            }
            for (int i=l;i<=r;i++){
                ans+=min(4LL,mx-a[i]);
            }
            cout<<ans<<"\n";
            continue;
        }
        int Mx=0,ans=0;
        for (int i=l;i<=R[bl];i++){
            Mx=max(Mx,a[i]);
        }
        for (int i=L[br];i<=r;i++){
            Mx=max(Mx,a[i]);
        }
        for (int i=bl+1;i<br;i++){
            Mx=max(mx[i],Mx);
        }
        for (int i=l;i<=R[bl];i++){
            ans+=min(4LL,Mx-a[i]);
        }
        for (int i=L[br];i<=r;i++){
            ans+=min(4LL,Mx-a[i]);
        }
        for (int i=bl+1;i<br;i++){
            switch(Mx-mx[i]){
                case 0:ans+=s[i][1]+2*s[i][2]+3*s[i][3]+4*s[i][4];break;
                case 1:ans+=s[i][0]+2*s[i][1]+3*s[i][2]+4*(s[i][3]+s[i][4]);break;
                case 2:ans+=2*s[i][0]+3*s[i][1]+4*(s[i][2]+s[i][3]+s[i][4]);break;
                case 3:ans+=3*s[i][0]+4*(s[i][1]+s[i][2]+s[i][3]+s[i][4]);break;
                default:ans+=4*(s[i][0]+s[i][1]+s[i][2]+s[i][3]+s[i][4]);break;
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：2)

发现从最大值开始，向左和向右分别进行操作，每次操作选的相邻两个数，这样肯定最优。

考虑证明。令 $L$ 为区间长度，假设你每次操作相邻 $k$ 个数，那么花费为 $k^2$，相邻的数有 $L-1$ 个，因此花费 $k^2(L-k+1)=k^2(L+1)-k^3$。由于 $L+1\ge k$，感性理解一下，当 $k$ 增大时，前一项增长速度肯定大于后一项增长速度，因此让 $k$ 尽可能小，而 $k=1$ 是没有任何用的，因此 $k=2$ 最优。

$k=2$ 时我们会花费 $4$ 的代价对相邻两个数进行操作。如果当前序列最大值 $M$ 减去要操作的数的结果小于 $4$，那么选择操作 $1$ 更优。找到 $[l,r]$ 内有多少个数为 $M,M-1,M-2,M-3$，那么 $\le M-4$ 的个数用区间长度减去前三个就行，最后计算一下答案。

因此题目就变成了单点修改，区间查询有多少个数等于 $x$ 和区间查询最大值。由于我的线段树水平很差，所以这个东西直接分块做就行。每个块开一个 $maxx_i$ 表示第 $i$ 个块的最大值，$vis_{i,j}$ 表示第 $i$ 个块 $j$ 出现的次数。修改时就整个块重构，查询散块暴力搞，整块直接算。时间空间复杂度均为 $O(n\sqrt{n})$，还是可以过的。

```cpp
#include<bits/stdc++.h>
#define N 200005
#define M 450
using namespace std;
int n,q,block,tot,a[N],vis[M][N],f[N],L[M],R[M],maxx[M];
//f[i] 表示 i 属于的块，L[i] 和 R[i] 表示块的左右端点，vis[j][i] 表示第 j 个块中 i 出现的个数，maxx[i] 表示第 i 个块的最大值
void build()//分块初始化
{
	block=sqrt(n);
	tot=(n-1)/block+1;
	for(int i=1;i<=n;i++) f[i]=(i-1)/block+1;
	for(int i=1;i<=tot;i++) L[i]=(i-1)*block+1,R[i]=i*block;
	R[tot]=n;
	for(int i=1;i<=tot;i++) for(int j=L[i];j<=R[i];j++) vis[i][a[j]]++,maxx[i]=max(maxx[i],a[j]);
	return;
}
void update(int x,int y)//单点修改，维护 vis 和 maxx 数组
{
	maxx[f[x]]=0;
	vis[f[x]][a[x]]--;
	a[x]=y;
	vis[f[x]][a[x]]++;
	for(int i=L[f[x]];i<=R[f[x]];i++) maxx[f[x]]=max(maxx[f[x]],a[i]);
	return;
}
int query1(int x,int y,int z)//查询 [x,y] 中 z 的个数
{
	int res=0;
	if(f[x]==f[y])
	{
		for(int i=x;i<=y;i++) res+=(a[i]==z);
		return res;
	}
	for(int i=x;i<=R[f[x]];i++) res+=(a[i]==z);
	for(int i=f[x]+1;i<f[y];i++) res+=vis[i][z];
	for(int i=L[f[y]];i<=y;i++) res+=(a[i]==z);
	return res;
}
int query2(int x,int y)//查询 [x,y] 中的最大值
{
	int res=0;
	if(f[x]==f[y])
	{
		for(int i=x;i<=y;i++) res=max(res,a[i]);
		return res;
	}
	for(int i=x;i<=R[f[x]];i++) res=max(res,a[i]);
	for(int i=f[x]+1;i<f[y];i++) res=max(res,maxx[i]);
	for(int i=L[f[y]];i<=y;i++) res=max(res,a[i]);
	return res;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	build();
	while(q--)
	{
		int op,x,y,maxx,sum0,sum1,sum2,sum3;
		cin>>op>>x>>y;
		if(op==1) update(x,y);
		else
		{
			maxx=query2(x,y);
			sum0=query1(x,y,maxx),sum1=query1(x,y,maxx-1);
			sum2=query1(x,y,maxx-2),sum3=query1(x,y,maxx-3);
			cout<<sum0*0+sum1*1+sum2*2+sum3*3+(y-x+1-sum0-sum1-sum2-sum3)*4<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：szh_AK_all (赞：2)

首先，对于一个区间，我们在操作时肯定是想让所有数都变为该区间内数的最大值。那么考虑由最大值向左右扩展，对于二操作，我们每次对长度为 $2$ 的区间进行操作是最优的，因为对于 $i\ge 2$，始终满足 $4\times (i-1)\le i^2$。

那么初步的想法便出来了，我们需要任取一个最大值所在的位置 $k$，向左右扩展，使得 $a_{k-1},a_{k+1}$ 变为 $a_k$，在由 $a_{k-1},a_{k+1}$ 扩展，依此类推，最终使整个区间的值都为 $a_k$。而对于某个二操作，我们将它换成一操作更优当前仅当要区间内数的最大值与要操作的这个数的值的差不超过 $4$，那么维护区间内每个数出现的次数即可，这里使用的是分块。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005], id[200005], L[200005], R[200005], k[255][200005], maxn[255];
int B = 800;

void add(int x, int z) {
	int ii = id[x];
	k[ii][a[x]]--;
	a[x] = z;
	k[ii][a[x]]++;
	maxn[ii] = 0;
	for (int i = L[ii]; i <= R[ii]; i++)
		maxn[ii] = max(maxn[ii], a[i]);
}

int ask(int l, int r) {
	int ma = 0;
	int il = id[l], ir = id[r];
	if (il == ir) {
		int ans = 0;
		int ma = 0;
		for (int i = l; i <= r; i++)
			ma = max(ma, a[i]);
		for (int i = l; i <= r; i++) {
			if (a[i] >= ma - 4)
				ans += (ma - a[i]);
			else
				ans += 4;
		}
		return ans;
	}
	for (int i = l; i <= R[il]; i++)
		ma = max(ma, a[i]);
	for (int i = il + 1; i <= ir - 1; i++)
		ma = max(ma, maxn[i]);
	for (int i = L[ir]; i <= r; i++)
		ma = max(ma, a[i]);
	int ans = 0, tmp = 0, da = 0;
	for (int i = l; i <= R[il]; i++)
		ans += (a[i] >= ma - 4 && a[i] != ma), da += (a[i] >= ma - 4 && a[i] != ma) * (ma - a[i]), tmp += (a[i] == ma);
	for (int i = il + 1; i <= ir - 1; i++) {
		for (int j = max(1, ma - 4); j < ma; j++)
			ans += k[i][j], da += k[i][j] * (ma - j);
		tmp += k[i][ma];
	}
	for (int i = L[ir]; i <= r; i++)
		ans += (a[i] >= ma - 4 && a[i] != ma), da += (a[i] >= ma - 4 && a[i] != ma) * (ma - a[i]), tmp += (a[i] == ma);
	da += (r - l + 1 - ans - tmp) * 4;
	return da;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int kuai = n / B + 1;
	if (n % B == 0)
		kuai--;
	for (int i = 1; i <= kuai; i++) {
		L[i] = (i - 1) * B + 1;
		R[i] = min(n, i * B);
		for (int j = L[i]; j <= R[i]; j++)
			id[j] = i, k[i][a[j]]++, maxn[i] = max(maxn[i], a[j]);
	}
	while (q--) {
		int op, l, r;
		cin >> op >> l >> r;
		if (op == 1)
			add(l, r);
		else
			cout << ask(l, r) << "\n";
	}
}
```

---

## 作者：Milthm (赞：2)

我们发现这个询问操作，即使是静态序列单次问题也不是很好做，然后发现这道题放在了 B 题，猜测本题可能是诈骗题。

往这方面去想，你会发现一个性质：询问中的操作 $2$ 每次**只执行长度为 $2$ 的区间**一定不劣。证明：

> 首先长度为 $1$ 的区间肯定不需要，然后设你要操作长度为 $n$ 的区间，满足 $n\ge 3$，则代价为 $n^2$，如果把它拆成一个个长度为 $2$ 的区间，代价为 $4(n-1)$。做差可以发现 $n^2-4(n-1)=(n-2)^2\ge 0$，所以后者永远是不劣的。

所以考虑从序列中的最大值往两侧延展，那么如果这个位置和最大值的差大于等于 $4$，则使用操作 $2$，否则使用操作 $1$。于是我们就得到了答案的求法：设区间中最大值为 $V$，值为 $V-1,V-2,V-3$ 的数的个数分别为 $cnt_1,cnt_2,cnt_3$，值小于等于 $V-4$ 的数的个数为 $cnt_4$，则答案为 $cnt_1+2cnt_2+3cnt_3+4cnt_4$。

这个应该可以采用线段树维护，但是比较麻烦，于是我直接写了个分块上去，十分简单，时间复杂度 $O(n\sqrt n)$。


```cpp
#include<bits/stdc++.h>
#define lol long long
#define N 200005
using namespace std;
int n,q,B=500,len,a[N],maxn[N],id[N],l[N],r[N];
int qwq[501][N];
int read(){
	int f=1,ans=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')f=-1;c=getchar();
	}
	while(isdigit(c)){
		ans=(ans<<1)+(ans<<3)+(c^48);c=getchar();
	}  
	ans*=f;return ans;
}
void update(int x,int k,int op){
	int ll=id[x];maxn[ll]=0;
	if(op)qwq[ll][a[x]]--;a[x]=k;qwq[ll][a[x]]++;
	for(int i=l[ll];i<=r[ll];++i)maxn[ll]=max(maxn[ll],a[i]);
}
int mx(int x,int y){
	int ll=id[x],rr=id[y],ans=0;
	if(ll==rr){
		for(int i=x;i<=y;++i)ans=max(ans,a[i]);
		return ans;
	}
	for(int i=x;i<=r[ll];++i)ans=max(ans,a[i]);
	for(int i=ll+1;i<rr;++i)ans=max(ans,maxn[i]);
	for(int i=l[rr];i<=y;++i)ans=max(ans,a[i]);
	return ans;
}
int query(int x,int y,int k){
	int ll=id[x],rr=id[y],ans=0;
	if(ll==rr){
		for(int i=x;i<=y;++i)ans+=(a[i]==k);
		return ans;
	}
	for(int i=x;i<=r[ll];++i)ans+=(a[i]==k);
	for(int i=ll+1;i<rr;++i)ans+=qwq[i][k];
	for(int i=l[rr];i<=y;++i)ans+=(a[i]==k);
	return ans;
}
signed main(){
	n=read(),q=read();
	len=ceil(n*1.0/B);
	for(int i=1;i<=n;++i){
		a[i]=read();
		id[i]=(i-1)/B+1;
	}
	for(int i=1;i<=len;++i){
		l[i]=(i-1)*B+1;r[i]=i*B;
	}
	r[len]=n;
	for(int i=1;i<=n;++i)update(i,a[i],0);
	while(q--){
		int op=read(),x=read(),y=read();
		if(op==1)update(x,y,1);
		else{
			int V=mx(x,y);
			lol cnt=query(x,y,V),cnt_1=query(x,y,V-1),cnt_2=query(x,y,V-2),cnt_3=query(x,y,V-3);
			lol cnto=y-x+1-cnt-cnt_1-cnt_2-cnt_3;
			lol ans=cnt_1+cnt_2*2+cnt_3*3+cnto*4;
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：yhy2024 (赞：1)

先从询问操作的性质入手。

性质一：最后所有数会变成区间最大值。对于操作一如果给最大值加，显然不会更优。对于操作二，怎么取也不会超过最大值。

性质二：只用操作二，每个数只用 $4$，的代价即可变为最大值。例如数列：$[3,1,1]$，先变为：$[3,3,1]$，在变为：$[3,3,3]$，总代价是 $8$，一次全变代价是 $9$，说明一次一次变比一次全变更优，变一次代价为 $(i+1-i+1)^2=4$。

所以由以上两个性质得出只有在某个数与最大值差小于 $4$ 时用操作一。

记区间最大值为 $mx$，于是询问等价于求：

$$\sum_{i=l}^r \min(4,mx-a_i)$$

$4$ 非常小，直接维护与区间最大值差 $0,1,2,3$ 的数的数量即可。合并区间可以重载一下更方便。


```cpp
#include<bits/stdc++.h>
#define N 2000005 
#define rd read()
#define int long long
#define inf LONG_LONG_MAX
using namespace std;
int n,m,op,l,r;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x*f;
}
struct Node{
	int mx,s0,s1,s2,s3;
	inline Node operator + (Node r)const{
		Node l=*this;
		if(l.mx==r.mx) return {l.mx,l.s0+r.s0,l.s1+r.s1,l.s2+r.s2,l.s3+r.s3};
		else{
			if(l.mx<r.mx) swap(l,r);
			if(l.mx-r.mx==1) return {l.mx,l.s0,l.s1+r.s0,l.s2+r.s1,l.s3+r.s2};
			else if(l.mx-r.mx==2) return {l.mx,l.s0,l.s1,l.s2+r.s0,l.s3+r.s1};
			else if(l.mx-r.mx==3) return {l.mx,l.s0,l.s1,l.s2,l.s3+r.s0};
			else return l;
		}
	}
}tr[N<<2];
inline void pushup(int k){tr[k]=tr[k<<1]+tr[k<<1|1];}
inline void build(int k,int l,int r){
	if(l==r){return tr[k]={rd,1,0,0,0},void();}
	int mid=l+r>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
inline void change(int k,int l,int r,int x,int v){
	if(l==r){return tr[k]={v,1,0,0,0},void();}
	int mid=l+r>>1;
	if(x<=mid) change(k<<1,l,mid,x,v);
	else change(k<<1|1,mid+1,r,x,v);
	pushup(k);
}
inline Node query(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y) return tr[k];
	int mid=l+r>>1;
	Node res={-inf,0,0,0,0};
	if(x<=mid) res=res+query(k<<1,l,mid,x,y);
	if(y>mid) res=res+query(k<<1|1,mid+1,r,x,y);
	return res;
}
signed main(){
	n=rd,m=rd;
	build(1,1,n);
	for(int i=1;i<=m;i++){
		op=rd,l=rd,r=rd;
		if(op==1) change(1,1,n,l,r);
		else{
			auto [mx,s0,s1,s2,s3]=query(1,1,n,l,r);
			cout<<(r-l+1-s0-s1-s2-s3)*4+s1+s2*2+s3*3<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：1)

一篇不用主席树、分块和平衡树的题解。

显然最后所有数都要等于最大值。

有一种构造方案是，从最大值位置开始拓展，把两边的数变成最大值。设最大值为 $a$，旁边的数是 $b$，可以用操作 $1$ 做到 $a-b$ 步，也可以用操作 $2$ 做到 $4$ 步。如果差 $<4$ 就用操作 $1$，否则用操作 $2$。设最大值为 $mx$，$c(x)$ 表示 $x$ 的出现次数，步数是 $4(r-l+1)-4c(mx)-3c(mx-1)-2c(mx-2)-c(mx-3)$。

考虑用线段树维护 $c(mx),c(mx-1),c(mx-2),c(mx-3)$。修改查询是平凡的，考虑如何合并。为了描述方便，转换一下 $c$ 的定义，$c(i)$ 表示比当前区间最大值小 $i$ 的数的个数。

设左区间最大值当前区间最大值小 $s$，则比合并区间时对于左区间中比左区间最大值小 $i$ 的数，会对当前区间的 $c(s+i)$ 造成左区间的 $c(i)$ 的贡献。

我们只关心 $c(0)\sim c(3)$，所以时间复杂度 $O(n\log n)$。

```cpp
#define il inline
int n,m,a[N];
struct SGT {
	#define ls (id<<1)
	#define rs (id<<1|1)
	#define mid (l+r>>1)
	#define all 1,1,n
	#define Ls ls,l,mid
	#define Rs rs,mid+1,r
	#define mx(a) a.mx
	#define c(a,i) a.c[i]
	struct NODE {int mx,c[4];} tr[N*4];
	il friend NODE operator+(NODE a,NODE b) {
		NODE r; mx(r)=max(mx(a),mx(b)),mst(r.c,0);
		int s=mx(r)-mx(a),t=mx(r)-mx(b);
		for(int i=0;i<4;i++) {
			if(s+i<4) c(r,s+i)+=c(a,i);
			if(t+i<4) c(r,t+i)+=c(b,i);
		}
		return r;
	}
	void bld(int id,int l,int r) {
		if(l==r) return mx(tr[id])=a[l],c(tr[id],0)=1,void();
		bld(Ls),bld(Rs),tr[id]=tr[ls]+tr[rs];
	}
	void upd(int id,int l,int r,int x) {
		if(l==r) return mx(tr[id])=a[l],void();
		x<=mid?upd(Ls,x):upd(Rs,x),tr[id]=tr[ls]+tr[rs];
	}
	NODE qry(int id,int l,int r,int L,int R) {
		if(L<=l&&r<=R) return tr[id];
		return L<=mid&&R>mid?qry(Ls,L,R)+qry(Rs,L,R):L<=mid?qry(Ls,L,R):qry(Rs,L,R);
	}
} sgt;
void QwQ() {
	n=rd(),m=rd();
	for(int i=1;i<=n;i++) a[i]=rd();
	sgt.bld(all);
	for(int o,l,r;m--;) {
		o=rd(),l=rd(),r=rd();
		if(o==1) a[l]=r,sgt.upd(all,l);
		else {
			SGT::NODE nd=sgt.qry(all,l,r);
			wr(4*(r-l+1)-c(nd,0)*4-c(nd,1)*3-c(nd,2)*2-c(nd,3),"\n");
		}
	}
}
```

---

## 作者：ykzzldz (赞：1)

由于 $3^2\ge 2\times2^2$，所以操作 $2$ 一定只会对区间长度为 $2$ 的区间进行操作。设区间内的最大值为 $w$，答案为 $\sum_{i=l}^r \min(4,w-a_i)$。

于是我们的问题变为找到区间内 $w,w-1,w-2,w-3$ 的个数（代价分别为 $0,1,2,3$），其他的数代价均为 $4$，使用分块即可，复杂度 $O(n\sqrt n)$。下面给出代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5,M=500;
int n,q,a[N+10],block,tot,L[N+10],R[N+10],bl[N+10],num[M+10][N+10],mx[N+10];
void build(){
	block=sqrt(n);
	tot=n/block+(n%block!=0);
	for(int i=1;i<=tot;i++){
		L[i]=(i-1)*block+1;
		R[i]=i*block;
	}
	R[tot]=n;
	for(int i=1;i<=n;i++){
		bl[i]=(i-1)/block+1;
		num[bl[i]][a[i]]++;
		mx[bl[i]]=max(mx[bl[i]],a[i]);
	}
}
void change(int x,int y){
	mx[bl[x]]=0;
	num[bl[x]][a[x]]--;
	a[x]=y;
	num[bl[x]][a[x]]++;
	for(int i=L[bl[x]];i<=R[bl[x]];i++){
		mx[bl[x]]=max(mx[bl[x]],a[i]);
	}
}
int ask(int l,int r,int x){//询问 [l,r] 中 x 的个数 
	int ans=0;
	if(bl[l]==bl[r]){
		for(int i=l;i<=r;i++){
			if(a[i]==x)ans++;
		}
		return ans;
	}
	for(int i=l;i<=R[bl[l]];i++){
		if(a[i]==x)ans++;
	}
	for(int i=L[bl[r]];i<=r;i++){
		if(a[i]==x)ans++;
	}
	for(int i=bl[l]+1;i<bl[r];i++){
		ans+=num[i][x];
	}
	return ans;
}
int query(int l,int r){
	int w=0,num=r-l+1,num0,num1,num2,num3;
	if(bl[l]==bl[r]){
		for(int i=l;i<=r;i++){
			w=max(w,a[i]);
		}
	}
	else{
		for(int i=l;i<=R[bl[l]];i++){
			w=max(w,a[i]);
		}
		for(int i=L[bl[r]];i<=r;i++){
			w=max(w,a[i]);
		}
		for(int i=bl[l]+1;i<bl[r];i++){
			w=max(w,mx[i]);
		}
	}
	num0=ask(l,r,w);
	num1=ask(l,r,w-1);
	num2=ask(l,r,w-2);
	num3=ask(l,r,w-3);
	num=num-num0-num1-num2-num3;
	return num1+num2*2+num3*3+num*4;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build();
	while(q--){
		int x,y,z;
		cin>>x>>y>>z;
		if(x==1)change(y,z);
		else cout<<query(y,z)<<'\n';
	}
	return 0;
}
```

---

## 作者：UniGravity (赞：1)

诈骗题。

首先发现两个操作都不会把数变小，因此最后一定是把区间内所有数变成区间最大值。

然后考虑操作二代价是平方，所以发现选的区间越长反而代价越大。例如长度为 $a\ (a\ge3)$ 的区间，原来需要花费 $a^2=(a-1+1)^2=(a-1)^2+2a-1$ 的代价，将其拆成长度为 $2$ 和 $a-1$ 的区间（并大小为 $1$），则代价为 $4+(a-1)^2<2a-1+(a-1)^2$。

那么发现操作二等价于每次选择一个长度为 $2$ 的区间，花费代价 $4$。进一步发现由于操作顺序可以任意排列，因此操作二等价于选择一个数花费 $4$ 的代价变成整个区间的最大值。

那么就可以做了：考虑暴力找出区间内分别有多少个值与最大值相差小于 $4$ 的数，这些数做操作一，剩下的做操作二。找区间内多少个等于 $v$ 的数直接使用动态开点线段树维护即可。时间复杂度 $O(n\log n)$。

```cpp
const int N=200005,M=10000005;
int n,q,a[N];

struct SegT{
    int rt[N],cnt[M],lc[M],rc[M],tot=0;
    il void add(int &x,int l,int r,int p,int v){
        if(!x)x=++tot;if(l==r)return cnt[x]+=v,void();int mid=(l+r)>>1;
        p<=mid?add(lc[x],l,mid,p,v):add(rc[x],mid+1,r,p,v),cnt[x]=cnt[lc[x]]+cnt[rc[x]];
    }
    il int qry(int x,int l,int r,int bg,int ed){
        if(!x)return 0;else if(bg<=l&&r<=ed)return cnt[x];int mid=(l+r)>>1,a=0;
        if(bg<=mid)a=qry(lc[x],l,mid,bg,ed);if(mid<ed)a+=qry(rc[x],mid+1,r,bg,ed);return a;
    }
}ds;
struct MX{
    int mx[N*4];
    il void upd(int x,int l,int r,int p,int v){
        if(l==r)return mx[x]=v,void();int mid=(l+r)>>1;
        p<=mid?upd(x<<1,l,mid,p,v):upd(x<<1|1,mid+1,r,p,v),mx[x]=max(mx[x<<1],mx[x<<1|1]);
    }
    il int qry(int x,int l,int r,int bg,int ed){
        if(bg<=l&&r<=ed)return mx[x];int mid=(l+r)>>1,a=0;
        if(bg<=mid)a=qry(x<<1,l,mid,bg,ed);if(mid<ed)a=max(a,qry(x<<1|1,mid+1,r,bg,ed));return a;
    }
}mx;

signed main(){
    n=read(),q=read();
    forto(i,1,n)a[i]=read(),ds.add(ds.rt[a[i]],1,n,i,1),mx.upd(1,1,n,i,a[i]);
    int op,l,r;
    while(q--){
        op=read(),l=read(),r=read();
        if(op==1){
            ds.add(ds.rt[a[l]],1,n,l,-1),a[l]=r,ds.add(ds.rt[a[l]],1,n,l,1);
            mx.upd(1,1,n,l,r);
        }else{
            int x=mx.qry(1,1,n,l,r),c=r-l+1,ans=0;
            forbk(v,x,max(x-4,1)){
                int cnt=ds.qry(ds.rt[v],1,n,l,r);
                c-=cnt,ans+=cnt*(x-v);
            }
            ans+=4*c;
            printf("%d\n",ans);
        }
    }
    return 0;
}
```

---

## 作者：hyk2019 (赞：0)

先分析 `2 l r` 如何处理。

容易发现，我们永远不会对一个长度大于 $2$ 的区间 $[l,r]$ 进行第二种操作，因为可以用 $r-l$ 次第二种操作达到更小的代价。

设在区间 $[l,r]$ 中，一个最大值出现的位置是 $a_x$，那么可以对 $l\sim x-1$ 的每个 $[i,i+1]$ 执行第二种操作；对 $x\sim r-1$ 的每个 $[i,i+1]$ 执行第二种操作。这样代价是 $4(r-l)$，比直接对整个区间进行操作的代价 $(r-l+1)^2$ 小。

那么，是不是对所有长度为 $2$ 的区间 $[l,r]$ 进行第二种操作就可以了？并不是。如果 $a_i,a_{i+1}$ 的差值不到 $4$，那么完全可以把较小的数通过第一种操作加上来，比第二种操作的代价 $4$ 来得小。

因此，对于 `2 l r`，我们**求解的思路**是：
- 设一个最大值出现的位置是 $a_x$。
- 对 $l\sim x-1$ 的每个 $[i,i+1]$ 执行：
  - 如果 $a_i$ 和 $a_{i+1}$ 相差不超过 $4$，那么执行第一种操作。代价为 $|a_{i+1}-a_i|$。
  - 否则，利用第二种操作。代价为 $4$。
  - 即对这个区间操作的代价是 $\min\{|a_{i+1}-a_i|,4\}$。
- 对 $x\sim r-1$ 的每个 $[i,i+1]$ 执行上述操作。

发现只有和 $a_x$ 相差小于 $4$ 的才会对答案有影响，因此，设和 $a_x$ 相差 $y$ 的数（包括 $a_x$）有 $b_y$ 个，则**答案**为 $4(r-l)+\sum_{i=0}^3{(4-i)\times b_i}$。

现在再来考虑 `1 k x` 操作。显然要用线段树，维护信息时，只要维护区间最大值，以及区间内和最大值相差小于 $4$ 的数有多少个即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Info {
	int max, p[4];
	Info(int t=0, int a=1, int b=0, int c=0, int d=0) {
		max = t, p[0] = a, p[1] = b, p[2] = c, p[3] = d;
	}
	Info operator+(Info b) const {
		if(max < b.max)
			return b + *this;
		int tp[4] = {p[0], p[1], p[2], p[3]};
		for(int i = 0; i < 4; i ++)
			if(b.max - i >= max - 4)
				tp[max - b.max + i] += b.p[i];
			else
				break;
		return Info(max, tp[0], tp[1], tp[2], tp[3]);
	}
	void print() {
		printf("max = %d, ", max);
		for(int i = 0; i < 4; i ++)
			printf("p[%d] = %d, ", i, p[i]);
		printf("\n");
	}
};

struct Node {
	int l, r, L, R;
	Info i;
	Node(int a=0, int b=0, int c=0, int d=0) {
		l = a, r = b, L = c, R = d;
	}
} ns[400005];
int cnt = 1, N, Q, a[200005];

void pushup(int u) {
	ns[u].i = ns[ns[u].l].i + ns[ns[u].r].i;
}

void build(int L, int R, int u) {
	if(L == R) {
		ns[u] = Node(0, 0, L, R);
		ns[u].i = Info(a[L]);
		return;
	}
	int Mid = L + R >> 1;
	int l = ++cnt;
	build(L, Mid, l);
	int r = ++cnt;
	build(Mid + 1, R, r);
	ns[u] = Node(l, r, L, R);
	pushup(u);
}

void modify(int L, int x, int u) {
	if(ns[u].L == ns[u].R) {
		ns[u].i = Info(x);
		return;
	}
	int Mid = ns[u].L + ns[u].R >> 1;
	if(L <= Mid)
		modify(L, x, ns[u].l);
	else
		modify(L, x, ns[u].r);
	pushup(u);
}

Info query(int L, int R, int u) {
	if(L <= ns[u].L && ns[u].R <= R)
		return ns[u].i;
	int Mid = ns[u].L + ns[u].R >> 1;
	Info mer(0, 0);
	if(L <= Mid)
		mer = mer + query(L, R, ns[u].l);
	if(R > Mid)
		mer = mer + query(L, R, ns[u].r);
	return mer;
}

int main() {
	scanf("%d%d", &N, &Q);
	for(int i = 1; i <= N; i ++)
		scanf("%d", a + i);
	build(1, N, 1);
	while(Q --) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		if(x == 1) {
			modify(y, a[y] = z, 1);
		} else {
			Info w = query(y, z, 1);
			int ans = z - y + 1 << 2;
			for(int i = 0; i < 4; i ++)
				ans -= (4 - i) * w.p[i];
			printf("%d\n", ans);
		}
	}
	return 0;
}
```

---

## 作者：qwer6 (赞：0)

## 1.Descrption

[摘自洛谷题面](https://www.luogu.com.cn/problem/P12179)，有删改。

给定一个长度为 $n$ 的序列和 $m$ 个操作，形式如下：

- `1 k x`，将 $a_k$ 修改为 $x$。
- `2 l r`，问仅通过以下操作（**但不真正执行**）使区间变为相同的数的最小代价（询问）。操作分别是：

1. 选择整数 $p$，将 $a_p$ 增加 $1$，代价为 $1$。
2. 选择整数区间 $x,y$，将 $a_x\dots a_y$ 全部变为 $\max\limits_{i=x}^y a_i$，代价为 $(y-x+1)^2$

## 2.Solution

先不考虑修改操作，只考虑查询操作的做法。

我们首先发现，对于查询中整个区间变为相同的数，这个目标数一定是 $\max_{i=l}^r a_i$，也就是区间最大值，这个结论是显然的，因为经过修改之后的区间，所有值都不可能减小，只会增大。

然后我们来考虑操作二的代价 $(y-x+1)^2$，也就是区间长度的平方，而我们知道完全平方数的增长是十分快的，所以我们可以推测，如果我们需要对一个大区间使用操作二的话，或许少量多次的代价会比一次做完的代价小得多。

事实上的确如此，使用多次小范围的操作二将区间统一成一个数的代价比使用一次覆盖全部区间的操作二的代价小得多。

对于长度为 $2$ 的区间，最小代价显然为 $4$，也就是直接覆盖整个区间，对于长度为 $3$ 的区间，最小代价为先统一一个包含最大值的长度为 $2$ 的区间，代价为 $4$，然后再使用一次操作二，将最后一个值覆盖，代价同样为 $4$，总代价为 $8$。以此，我们发现，使用两个长度为 $2$ 的区间重叠得到一个长度为 $3$ 的区间，代价为 $8$，使用一个长度为 $3$ 的区间直接覆盖，代价为 $9$，显然更小。对于长度更大的区间同理。

所以我们发现，对于一个值，统一为最大值需要的代价最大为 $4$，如果这个值距离最大值只差 $1\sim 3$ 了，那么使用操作一即可。

具体可以如下操作：找到区间最大值的位置 $x$ 和值 $mx$，然后向两边拓展，如果 $val_i\ge mx-3$，那么使用操作一，否则，使用长度为 $2$ 的操作二，代价为 $4$。

那么我们只要查询区间内值为 $mx,mx-1,mx-2,mx-3$ 的数量 $cnt_0,cnt_1,cnt_2,cnt_3$，那么最后的答案就是 $(r-l+1-cnt_0)\times 4-cnt_1\times 3-cnt_2\times 2-cnt_3\times 1$。

如果没有修改，我们可以直接使用 vector 记录每个值出现的下标，然后二分查找。但是这里有修改操作，我们需要删除和插入，可以选择开 $2\times 10^5$ 棵平衡树，查询 $r+1$ 和 $l$ 的排名，然后相减即可。

至于待修改的区间最大值，可以使用线段树来维护。

注意判断 $mx-1$，$mx-2$，$mx-3$ 是不是小于等于 $0$！

## 3.Code

```c++
/*by qwer6*/
/*略去缺省源和快读快写*/
const int N=2e5+5;
int n,m;
int a[N],rt[N];
mt19937 ran(time(0));
struct Treap{
	int num;
	int val[N<<1],cnt[N<<1],siz[N<<1],ch[N<<1][2];
	unsigned int c[N<<1];	
	void New(int &p,int v){
		p=++num;
		val[p]=v,c[p]=ran();
		cnt[p]=siz[p]=1;
		ch[p][0]=ch[p][1]=0;
	}
	void pushup(int p){
		siz[p]=siz[ch[p][0]]+siz[ch[p][1]]+cnt[p];
	}
	void ratote(int &p,bool opt){
		int x=ch[p][opt];
		ch[p][opt]=ch[x][opt^1];
		ch[x][opt^1]=p;
		pushup(ch[p][opt]),pushup(ch[x][opt^1]);
		p=x;
	} 
	void insert(int &p,int v){
		if(!p)return New(p,v);
		if(val[p]==v)cnt[p]++;
		else if(v>val[p]){
			insert(ch[p][1],v);
			if(c[p]>c[ch[p][1]])ratote(p,1);
		}else{
			insert(ch[p][0],v);
			if(c[p]>c[ch[p][0]])ratote(p,0);
		}
		pushup(p);
	}
	void delet(int &p,int v){
		if(!p)return ;
		if(val[p]==v){
			cnt[p]--;
			siz[p]--;
			if(cnt[p])return ;
			if(ch[p][0]==0&&ch[p][1]==0)return void(p=0);
			if(ch[p][0]==0){
				p=ch[p][1];
				pushup(p);
				return ;
			}
			if(ch[p][1]==0){
				p=ch[p][0];
				pushup(p);
				return ;
			}
			int tmp=p;
			if(c[ch[p][0]]<c[ch[p][1]])
				ratote(p,0);
			else
				ratote(p,1);
			pushup(p);
			int now=tmp,pre=p;
			while(ch[now][0]&&ch[now][1]){
				if(c[ch[now][0]]<c[ch[now][1]])
					ratote(now,0);
				else
					ratote(now,1);
				pushup(now);
				if(val[ch[pre][0]]==v)ch[pre][0]=now;
				else ch[pre][1]=now;
				pre=now;
				now=tmp;
			}
			if(val[ch[pre][0]]==v)ch[pre][0]=ch[now][0]|ch[now][1];
			else ch[pre][1]=ch[now][0]|ch[now][1];
			pushup(pre);
		}else if(v>val[p]){
			delet(ch[p][1],v);
			pushup(p);
		}else{
			delet(ch[p][0],v);
			pushup(p);
		}	
	}
	int get_rank(int p,int v){
		if(!p)return 0;
		if(v>val[p])return get_rank(ch[p][1],v)+siz[ch[p][0]]+cnt[p];
		if(v==val[p])return siz[ch[p][0]];
		if(v<val[p])return get_rank(ch[p][0],v);
	}
	int get_num(int p,int rank){
		if(siz[ch[p][0]]<rank&&rank<=siz[ch[p][0]]+cnt[p])return val[p];
		if(siz[ch[p][0]]+cnt[p]<rank)return get_num(ch[p][1],rank-siz[ch[p][0]]-cnt[p]);
		return get_num(ch[p][0],rank);
	}
}treap;
struct Segment_tree{
	int mx[N<<2];
	#define ls p<<1
	#define rs p<<1|1
	#define mid (l+r>>1)
	void pushup(int p){
		mx[p]=max(mx[ls],mx[rs]);
	}
	void build(int p,int l,int r){
		if(l==r){
			mx[p]=a[l];
			return ;
		}
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(p);
	}
	void change(int p,int l,int r,int x,int v){
		if(l==r){
			mx[p]=v;
			return ;
		}
		if(mid>=x)change(ls,l,mid,x,v);
		else change(rs,mid+1,r,x,v);
		pushup(p);
	}
	int query(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return mx[p];
		if(mid>=L&&mid<R)return max(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
		if(mid>=L)return query(ls,l,mid,L,R);
		return query(rs,mid+1,r,L,R);
	}
}Set;
int query(int l,int r,int val){
	if(val<=0)return 0;
	return treap.get_rank(rt[val],r+1)-treap.get_rank(rt[val],l);
}
signed main(){
	read(n),read(m);
	for(int i=1;i<=n;i++){
		read(a[i]);
		treap.insert(rt[a[i]],i);
	}
	Set.build(1,1,n);
	for(int i=1,opt,l,r,ans,cnt,L,R,mx;i<=m;i++){
		read(opt),read(l),read(r);
		if(opt==1){
			Set.change(1,1,n,l,r);
			treap.delet(rt[a[l]],l);
			a[l]=r;
			treap.insert(rt[a[l]],l);
		}else{
			ans=4*(r-l+1);
			mx=Set.query(1,1,n,l,r);
			ans-=query(l,r,mx)*4;
			ans-=query(l,r,mx-1)*3;
			ans-=query(l,r,mx-2)*2;
			ans-=query(l,r,mx-3)*1;
			write(ans),Nxt;
		}
	}
}
```

---

## 作者：Priestess_SLG (赞：0)

看到代价为平方式，可以想到拆括号列一次函数然后扔到李超线段树中维护，但是这个题和李超线段树没有关系。

观察题目，发现给出的操作十分奇奇怪怪，因此考虑手玩小数据然后观察性质。

容易发现，$2$ 操作若操作的区间为 $[l,r]$，则必须满足 $r-l+1=2$，可以证明其他情况一定不优：

+ $r-l+1=1$，这样的 $2$ 操作显然没用。
+ $r-l+1>2$，则设 $[l,r]$ 区间中某一个最大值所在位置为 $p$，那么依次操作：
  + $[p-1,p],[p-2,p-1],\ldots,[l,l+1]$
  + $[p,p+1],[p+1,p+2],\ldots,[r-1,r]$
  + 上面的两组区间，可以得到和直接操作 $[l,r]$ 等价的效果。此时其代价为 $4(r-l)$，而原代价为 $(r-l+1)^2$。令 $t=r-l$，则两式分别为 $4t$ 和 $(t+1)^2$。做差得 $(t+1)^2-4t=(t-1)^2\ge 0$，因此必然这样转化不会更优。

此时问题就简单了。考虑一个位置 $x$，若其不为区间 $[l,r]$ 最大值，则其是会被 $1$ 操作单独更新还是被 $2$ 操作用相邻的元素更新。设区间最大值为 $M$，则：

+ $1$ 操作代价为 $M-a_x$。
+ $2$ 操作代价为 $4$。

因此若 $M-a_x<4$ 则使用 $1$ 操作更新，否则使用 $2$ 操作更新，一定是一组最优解。

先考虑不带修改怎么做。发现对于每一个区间 $[l,r]$ 只需要处理和其最大值的差 $<4$ 的数的数量即可（不关心其具体在什么位置）。在下标意义上对值域做处理是困难的，但考虑到这样的数的不同值数量不超过 $4$，因此线段树维护区间前 $4$ 大值以及其出现的次数然后一点点判即可。

带修改就是再加个修改操作，总时间复杂度为大常数 $O((n+Q)\log n)$，可以通过。

```cpp
// #pragma GCC optimize(3,"Ofast","inline","unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>
#define int long long
using namespace std;
const int N = 1000010;
const int inf = 2e9;
const int mod = 998244353;
using ull = unsigned long long;
template<class _T>
using treap = __gnu_pbds::tree<_T, __gnu_pbds::null_type, less_equal<_T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
int a[N];
struct Node {
    int l, r;
    int m[5] = {0}, c[5] = {0};
    void init(int p) {
        l = r = p;
        memset(m, 0, sizeof m);
        memset(c, 0, sizeof c);
        m[0] = a[p], c[0] = 1;
    }
} tree[N << 2];
Node operator+(const Node &l, const Node &r) {
    Node res;
    res.l = l.l, res.r = r.r;
    int p1 = 0, p2 = 0;
    for (int i = 0; i < 5; ++i) {
        if (l.m[p1] > r.m[p2]) {
            res.m[i] = l.m[p1];
            res.c[i] = l.c[p1];
            ++p1;
        } else if (l.m[p1] < r.m[p2]) {
            res.m[i] = r.m[p2];
            res.c[i] = r.c[p2];
            ++p2;
        } else {
            res.m[i] = l.m[p1];
            res.c[i] = l.c[p1] + r.c[p2];
            ++p1, ++p2;
        }
        // if (i) assert(res.m[i] != res.m[i - 1]);
    }
    return res;
}
void build(int l, int r, int rt) {
    if (l == r)return tree[rt].init(l);
    int mid = l + r >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
void modi(int rt, int p, int v) {
    int &l = tree[rt].l, &r = tree[rt].r;
    if (l == r) {
        tree[rt].m[0] = v;
        tree[rt].c[0] = 1;
        return;
    }
    int mid = l + r >> 1;
    if (p <= mid) modi(rt << 1, p, v);
    else modi(rt << 1 | 1, p, v);
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
Node query(int rt, int ll, int rr) {
    int &l = tree[rt].l, &r = tree[rt].r;
    if (ll <= l && r <= rr) return tree[rt];
    int mid = l + r >> 1;
    if (ll <= mid&&mid < rr) return query(rt << 1, ll, rr) + query(rt<<1|1, ll, rr);
    if (ll <= mid) return query(rt<<1, ll, rr);
    return query(rt<<1|1, ll, rr);
}
signed main() {
    // freopen("debug.err", "w", stderr);
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    srand(time(0));
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, n, 1);
    while (q--) {
        int o;
        cin >> o;
        if (o == 1) {
            int k, x;
            cin >> k >> x;
            a[k] = x;
            modi(1, k, x);
        } else {
            int l, r;
            cin >> l >> r;
            Node t = query(1, l, r);
            assert(t.c[0]);
            if (t.c[0] == r-l+1) cout << "0\n";
            else if (!t.c[1]) cout << "0\n";
            else {
                int len = r - l + 1 - t.c[0], sum = 0;
                for (int i = 1; i < 5; ++i) {
                    if (!t.c[i]) break;
                    assert(t.m[i] < t.m[i - 1]);
                    if (t.m[0] - t.m[i] < 4) sum += (t.m[0] - t.m[i]) * t.c[i], len -= t.c[i];
                }
                sum += len * 4;
                cout << sum << '\n';
            }
        }
    }
    return 0;
}
```

---

