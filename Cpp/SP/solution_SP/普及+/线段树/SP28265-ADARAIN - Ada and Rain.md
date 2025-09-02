# ADARAIN - Ada and Rain

## 题目描述

瓢虫 Ada 正在种植植物。她有一条非常长的种植沟，这条沟长到雨水通常只能落在它的一部分区域。为了不让植物枯萎，Ada 详细记录了每场雨的降水区域，以了解每颗植物得到了多少雨水。然而，雨下得太多，她一个人忙不过来！

起初，你会得到 $N$ 个查询，每个查询是一个区间 $[L,R]$。第 $i$ 个区间表示第 $i$ 场雨覆盖的范围。随后有 $M$ 个查询，每个查询要求知道在第 $i$ 株植物上落了多少场雨。

## 说明/提示

对于 $100\%$ 的数据，保证：

* $0 < N,M \le 10^5$

* $0 \le W \le 10^6$

* $0 \le L \le R < W$

* $0 \le a < W$

请注意序列起始位置。

# 题解

## 作者：fengzhaoyu (赞：4)

## 题意
有一个长为 $w$ 的数列，起初都为 $0$；有 $n$ 次操作，将 $l$ 到 $r$ 间的数都加上 $1$；然后又 $m$ 次询问，问第 $a$ 个数是多少。
## 思路
此题就是区间操作，线段树，树状数组都可以写。最近我刚学[分块](https://blog.csdn.net/ys_kylin__/article/details/141025974)，就用分块讲吧！~~不过分块确实好理解又好写~~

1. 初始化分块，将数列分为几块，每块的左右端点以及每个点在第几块都处理好。这里建议分为 $\sqrt{w}$ 块，对于尾部不足一块的，再组建一个块。
2. 修改时，如果 $l$ 和 $r$ 在一块内，就暴力修改；否则将没有覆盖一整块的部分暴力加，中间整块用 $add_i$ 存储表示第 $i$ 块整体加了多少。
3. 单点查询就求这个点的值再加上他所在块整体加上的 $add_i$ 即可。

由于使用了 $add_i$ 对整块的处理，所以复杂度为 $O(n\sqrt{n})$。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5;
int add[5000],L[5000],R[5000],a[N],pos[N];
int n,m,w;
int read()// 快读
{
	int t=1,x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') t=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return t*x;
}
void init()// 初始化
{
	int t=sqrt(w);
	for(int i=1;i<=t;i++)
	{
		L[i]=R[i-1]+1;
		R[i]=i*t;
	}
	if(R[t]<w)
	{
		t++;
		R[t]=w;
		L[t]=R[t-1]+1;
	}
	for(int i=1;i<=t;i++)
	{
		for(int j=L[i];j<=R[i];j++)
		{
			pos[j]=i;
		}
	}
}
void change(int l,int r)// 修改
{
	int p=pos[l],q=pos[r];
	if(p==q)// 在同一块
	{
		for(int i=l;i<=r;i++)
		{
			a[i]++;
		}
	}
	else
	{
		for(int i=l;i<=R[p];i++) a[i]++;
		for(int i=L[q];i<=r;i++) a[i]++;
		for(int i=p+1;i<=q-1;i++) add[i]++;
	}
}
signed main()
{
	n=read();
	m=read();
	w=read();
	init();
	for(int i=1;i<=n;i++)
	{
		int l=read();
		int r=read();
		change(l,r);
	}
	for(int i=1;i<=m;i++)
	{
		int x=read();
		printf("%lld\n",a[x]+add[pos[x]]);
	}
	return 0;
}
```
~~建议评绿或黄~~

---

## 作者：StarryRTX (赞：2)

## 题意：
有一数组 $[0,w-1]$，初始全为 $0$。现有 $n$ 次修改操作，每次操作将 $[l,r]$ 间的数 $+1$，后有 $m$ 次查询操作，每次操作输入一个 $a$，输出数组中的第 $a$ 个数。
## 解法：
这题不用写数据结构，差分就行（[OI wiki](https://oi-wiki.org/basic/prefix-sum/#%E5%B7%AE%E5%88%86)），差分处理 $O(n)$，构造前缀和 $O(w)$，查询 $O(m)$，总的时间复杂度 $O(n + w + m)$。

1. 差分标记：对于每次输入的 $l$ 和 $r$，将 $ans[l]$ 加 $1$，$ans[r+1]$ 减 $1$。

```cpp
for(int i=1;i<=n;i++) l=read(),r=read(),ans[l]++,ans[r+1]--;//差分。
```


2. 用前缀和，把 $ans$ 数组转换为记录每个植物淋雨次数的数组。此处给出一个例子，种植沟长度为 $5$，雨落在了 $[1,3]$ 和 $[2,4]$，$i=5$（即循环完后）时得出答案。


```cpp
for(int i=1;i<=w;i++) ans[i]+=ans[i-1];//每个植物淋雨次数。
```

![](https://cdn.luogu.com.cn/upload/image_hosting/kezyqlcf.png)

3. 输出答案：预处理完后可 $O(1)$ 输出对应的第 $a$ 个植物的淋雨次数。

```cpp
for(int i=1;i<=m;i++){
    a=read();
	printf("%d\n",ans[a]);//查询第 a 个植物的淋雨次数。
}
```

## AC Code：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<48||ch>57){
		if(ch==45) f=-1;
		ch=getchar();
	}
	while(ch>=48&&ch<=57) x=(x<<1)+(x<<3)+ch-48,ch=getchar();
	return x*f;
}//快读。
int n,m,w,l,r,ans[1000005],a;
signed main(){
	n=read(),m=read(),w=read();
	for(int i=1;i<=n;i++) l=read(),r=read(),ans[l]++,ans[r+1]--;//差分。
	for(int i=1;i<=w;i++) ans[i]+=ans[i-1];//每个植物淋雨次数。
	for(int i=1;i<=m;i++){
		a=read();
		printf("%d\n",ans[a]);//查询淋雨次数。
	}
	return 0;
}
```

---

## 作者：DX3906_ourstar (赞：2)

建议评绿。

## 分析

一句话题意：维护一个序列，使其支持区间加法与单点查询。

不难发现与 [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368) 无异。但蒟蒻更喜欢线段树，就拿线段树来说了。

对于区间加法，分两种情况讨论。若当前结点的区间完全包含在修改区间中，则直接更新区间和并打上懒标记；否则，将修改区间的左右端点与当前结点的区间中点作比较，递归处理左右子树。

对于单点查询，同样分两种情况讨论。若当前结点为叶结点，直接返回其值即可；否则下传懒标记，并将目标位置与当前结点的区间中点作比较，递归处理左右子树。

## 样例

你谷题面上没有样例，于是我把原站上的样例薅下来了。

**输入：**

```
6 7 10
0 9
3 5
4 6
4 8
1 8
5 5
1
5
9
4
9
6
7
```

**输出：**

```
2
6
1
5
1
4
3
```

## 代码

很板，就不写注释了。

另外，这题的序列起始位置是 $0$，注意处理。

还有，数据规模是假的。原站上是 $0 < W \le 10^6$，交给 AI 翻译就变成 $0 < W \le 10^5$ 了……

```
#include<iostream>
#define ll long long
using namespace std;

const int N=1e6+5;

int n,m,w;

namespace OIfast{
	
	inline ll read(){
		register ll n=0,f=1;
		register char c=getchar();
		while(c<'0'||c>'9'){
			if(c=='-')f=-1;
			c=getchar();
		}
		while(c<='9'&&c>='0'){
			n=(n<<1)+(n<<3)+(c^48);
			c=getchar();
		}
		return n*f;
	}
	
	inline void print(register ll n){
		if(n<0)putchar('-'),n=~n+1;
		if(n>=10)print(n/10);
		putchar(n%10^48);
		return ;
	}
	
	inline void write(register ll n,register char c){
		print(n),putchar(c);
		return ;
	}
	
}using namespace OIfast;

namespace segmentTree{
	
	#define ls u<<1
	#define rs u<<1|1
	
	struct node{
		int l,r;
		ll s,la;
	}t[N<<2];
	
	inline void pushup(int u){
		t[u].s=t[ls].s+t[rs].s;
		return ;
	}
	
	inline void pushdown(int u){
		t[ls].s+=(t[ls].r-t[ls].l+1)*t[u].la;
		t[rs].s+=(t[rs].r-t[rs].l+1)*t[u].la;
		t[ls].la+=t[u].la,t[rs].la+=t[u].la;
		t[u].la=0;
		return ;
	}
	
	inline void build(int u,int l,int r){
		t[u].l=l,t[u].r=r;
		if(l==r){
			t[u].s=t[u].la=0;
			return ;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(u);
		return ;
	}
	
	inline void update(int u,int l,int r,ll k=1){
		if(l<=t[u].l&&t[u].r<=r){
			t[u].s+=k;
			t[u].la+=k;
			return ;
		}
		pushdown(u);
		int mid=(t[u].l+t[u].r)>>1;
		if(l<=mid)update(ls,l,r,k);
		if(r>mid)update(rs,l,r,k);
		pushup(u);
		return ;
	}
	
	inline ll query(int u,int x){
		if(t[u].l==x&&t[u].r==x)return t[u].s;
		pushdown(u);
		int mid=(t[u].l+t[u].r)>>1;
		if(x<=mid)return query(ls,x);
		else return query(rs,x);
	}
	
}using namespace segmentTree;

signed main(){
	n=read(),m=read(),w=read();
	build(1,1,w);
	while(n--){
		int l=read()+1,r=read()+1;
		update(1,l,r);
	}
	while(m--){
		int a=read();
		write(query(1,a+1),'\n');
	}
	return 0;
}
```

---

## 作者：哈哈人生 (赞：2)

## 题目大意
有一个初始为 $0$、编号从 $0$ 开始到 $n-1$ 结束的序列，$n$ 次操作每次操作把序列中 $l_i$ 到 $r_i$ 的位置都加上 $1$，$m$ 次操作每次询问序列第 $x$ 个位置的值。

## 思路
这题有多种解法，看到其它题解的做法怎么都是带 $\log$ 的数据结构？这题用差分不就行了吗。先操作，再处理，每一部分的时间复杂度都是常数时间的，最后的时间复杂度就是 $O(n+w+m)$。

## 代码
差分模板。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,w,l,r,x,c[1000005];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>w;
	while(n--){
		cin>>l>>r;
		c[l]++,c[r+1]--;//差分
	}
	for(int i=0;i<w;i++)c[i]+=c[i-1];//算出结果
	while(m--){
		cin>>x;
		cout<<c[x]<<endl;//输出对应
	}
	return 0;
}
```
当然这题还可以用数据结构（只是有点小题大做了），例如，线段树：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct xd_tree {
#define trl tr[p].l
#define trr tr[p].r
#define MAXN 1000005
	int n,a[MAXN];
	struct A {
		int l,r;
		int sum;
		int lz;
	} tr[MAXN<<2];
	void build(int n2,int *a2=NULL) {
		n=n2;
		for(int i=1; i<=n2; i++){
			if(a2==NULL)a[i]=0;
			else a[i]=a2[i];
		}
		build(1,1,n);
	}
	void makelazy(int p,int x) {
		tr[p].lz+=x;
		tr[p].sum+=(trr-trl+1)*x;
	}
	void pushup(int p) {
		tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
	}
	void pushdown(int p) {
		makelazy(p<<1,tr[p].lz);
		makelazy(p<<1|1,tr[p].lz);
		tr[p].lz=0;
	}
	void build(int p,int l,int r) {
		trl=l,trr=r;
		if(l==r) {
			tr[p].sum=a[l];
			return;
		}
		int mid=l+r>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		pushup(p);
	}
	void change(int p,int l,int r,int k) {
		if(l<=trl&&trr<=r) {
			makelazy(p,k);
			return;
		}
		if(trl>r||trr<l)return;
		pushdown(p);
		change(p<<1,l,r,k);
		change(p<<1|1,l,r,k);
		pushup(p);
	}
	int search(int p,int l,int r) {
		if(trl==0)return 0;
		if(l<=trl&&trr<=r) {
			return tr[p].sum;
		}
		if(trl>r||trr<l)return 0;
		pushdown(p);
		return search(p<<1,l,r)+search(p<<1|1,l,r);
	}
} t;
int n,m,w,l,r,x;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>w;
	t.build(w-1);
	while(n--){
		cin>>l>>r;
		t.change(1,l,r,1);
	}
	while(m--){
		cin>>x;
		cout<<t.search(1,x,x)<<endl;
	}
	return 0;
}
```
都可以过，题目时限放的很宽（话说不卡常就是好啊）。

## 后记
站长曾经说过：不抄袭题解代码，只借鉴题解思路，另外还应该给看过的题解点个赞！

---

## 作者：wannacry_ (赞：0)

# 思路 1
题目大意是让我们进行区间修改以及单点查询，观察到数据范围为 $10^6$，但他开了 $3$ 秒的时限，于是我们可以用分块维护，用 `tag` 维护每一个区块加的数，散块暴力修改，查询就直接求当前值加上他所属块 `tag` 的值。
# AC code
```cpp
#include<cstdio>
#include<cmath>
#define int long long
using namespace std;
const int N=1e6+10,M=sqrt(N)+10;
int n,m,w,sum[N],st[M],ed[M],p[N],tag[M],l,r,cnt,size;
void init(){
	size=sqrt(w);
	cnt=(!(w/size)?w/size:w/size+1);
	for(int i=1;i<=cnt;i++) st[i]=(i-1)*size+1,ed[i]=i*size;ed[cnt]=w;
	for(int i=1;i<=w;i++) p[i]=(i-1)/size+1;
}
void update(int l,int r){
	int L=p[l],R=p[r];
	if(L==R) for(int i=l;i<=r;i++) sum[i]++;
	else{
		for(int i=l;i<=ed[L];i++) sum[i]++;
		for(int i=L+1;i<=R-1;i++) tag[i]++;
		for(int i=st[R];i<=r;i++) sum[i]++;
	}
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&w);
	init();
	for(int i=1;i<=n;i++) scanf("%lld%lld",&l,&r),update(l,r);
	for(int i=1;i<=m;i++) scanf("%lld",&l),printf("%lld\n",sum[l]+tag[p[l]]);
	return 0;
}
```
# 思路 2
什么，你说你觉得这样太暴力了，那你也可以用线段树取做这道题，因为初始值都为 $0$，所以不需要建树操作，也不需要 `pushup`。
# AC code
```cpp
#include<cstdio>
#define int long long
using namespace std;
const int N=1e6+5;
int n,m,w,sum[N*4],tree[N*4],tag[N*4],l,r;
void pushdown(int p){
	if(tag[p]){
		tag[p<<1]+=tag[p],tag[p<<1|1]+=tag[p];
		sum[p<<1]+=tag[p],sum[p<<1|1]+=tag[p];
		tag[p]=0;
	}
}
void update(int p,int pl,int pr,int L,int R){
	if(pl>=L&&pr<=R){
		tag[p]++;
		sum[p]++;
		return;
	}
	pushdown(p);
	int mid=pl+pr>>1;
	if(L<=mid) update(p<<1,pl,mid,L,R);
	if(mid<R) update(p<<1|1,mid+1,pr,L,R);
}
int qu(int p,int pl,int pr,int x){
	if(pl==x&&pr==x) return sum[p];
	pushdown(p);
	int mid=pl+pr>>1;
	if(x<=mid) return qu(p<<1,pl,mid,x);
	if(mid<x) return qu(p<<1|1,mid+1,pr,x);
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&w);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&l,&r),update(1,1,w+1,l+1,r+1);
	for(int i=1;i<=m;i++) scanf("%lld",&l),printf("%lld\n",qu(1,1,w+1,l+1));
	return 0;
} 
```
# 思路 3
什么，你不喜欢这些复杂的数据结构，没关系，你甚至可以用一个简单的差分去解决这个问题。
# AC code
```cpp
#include<cstdio>
#define int long long
using namespace std;
const int N=1e6+5;
int n,m,w,l,r,sum[N];
signed main(){
	scanf("%lld%lld%lld",&n,&m,&w);
	for(int i=1;i<=n;i++) scanf("%lld%ld",&l,&r),sum[l]++,sum[r+1]--;
	for(int i=1;i<=w;i++) sum[i]+=sum[i-1];
	for(int i=1;i<=m;i++) scanf("%lld",&l),printf("%lld\n",sum[l]);
	return 0;
}
```

---

## 作者：int233 (赞：0)

## 题意：

给定一段序列 $[0,w-1]$ 有 $n$ 次修改操作，每次操作将 $[l,r]$ 区间内的数 $+1$ ，接下来有 $m$ 次询问操作，每次操作给出一个 $x$ ，求序列的第 $x$ 个数。

## 解法：

因为此题 $0\le l,r,x$ 所以可将 $w,l,r,x$ 整体 $+1$。

树状数组可以维护单点查询，区间修改的问题。

而区间修改，单点查询可以用树状数组 + 差分解决。

Code：

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
ll tree[1000005],n,m,w,l,r,x;
void add(ll x,ll k){
	while(x<=w){
		tree[x]+=k;
		x+=x&-x; 
	}
}
ll query(ll x){
	ll ans=0;
	while(x){
		ans+=tree[x];
		x-=x&-x;
	}
	return ans;
}
int main(){
	cin>>n>>m>>w;
	w++;
	while(n--){
		cin>>l>>r;
		l++;r++;
		add(l,1);
		add(r+1,-1);
	}
	while(m--){
		cin>>x;
		x++;
		cout<<query(x)<<endl;
	}
	return 0;
} 
```


---

