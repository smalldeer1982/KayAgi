# [ABC153F] Silver Fox vs Monster

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc153/tasks/abc153_f

ギンギツネは $ N $ 体のモンスターと戦っています。

モンスターは $ 1 $ 列に並んでおり、数直線上にいるとみなすことができます。$ i $ 番目のモンスターは座標 $ X_i $ にいて、体力は $ H_i $ です。

ギンギツネは爆弾を使ってモンスターを攻撃することができます。 座標 $ x $ で爆弾を使うと、座標が $ x-D $ 以上 $ x+D $ 以下の範囲にいる全てのモンスターの体力を $ A $ 減らすことができます。 爆弾を使う以外の方法でモンスターの体力を減らすことはできません。

全てのモンスターの体力を $ 0 $ 以下にすればギンギツネの勝ちです。

ギンギツネがモンスターに勝つまでに爆弾を使う回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ D\ \leq\ 10^9 $
- $ 1\ \leq\ A\ \leq\ 10^9 $
- $ 0\ \leq\ X_i\ \leq\ 10^9 $
- $ 1\ \leq\ H_i\ \leq\ 10^9 $
- $ X_i $ は相異なる。
- 入力中のすべての値は整数である。

### Sample Explanation 1

最初に座標 $ 4 $ で爆弾を使うことで、$ 1 $ 番目と $ 2 $ 番目のモンスターの体力を $ 2 $ 減らせます。 次に座標 $ 6 $ で爆弾を使うことで、$ 2 $ 番目と $ 3 $ 番目のモンスターの体力を $ 2 $ 減らせます。 この $ 2 $ 回で全てのモンスターの体力を $ 0 $ にできました。$ 1 $ 回で全てのモンスターの体力を $ 0 $ 以下にすることはできません。

### Sample Explanation 2

座標 $ 5 $ で爆弾を $ 5 $ 回使います。

### Sample Explanation 3

オーバーフローに注意してください。

## 样例 #1

### 输入

```
3 3 2
1 2
5 4
9 2```

### 输出

```
2```

## 样例 #2

### 输入

```
9 4 1
1 5
2 4
3 3
4 2
5 1
6 2
7 3
8 4
9 5```

### 输出

```
5```

## 样例 #3

### 输入

```
3 0 1
300000000 1000000000
100000000 1000000000
200000000 1000000000```

### 输出

```
3000000000```

# 题解

## 作者：Otomachi_Una_ (赞：6)

实际上这题的炸弹的爆炸范围为 $2d$  。

很容易想到从左到右一个个用炸弹的最左边炸最好，然后直接贪心即可。

## TLE Code
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=2e5+5;
int n,d,a;
long long ans=0;//十年OI一场空
struct monster{
	int x;
	int h;
}m[MAXN];
bool cmp(monster x,monster y){
	return x.x<y.x;
}
int c(int p,int q){
	return p/q+(p%q!=0);
}
int main(){
	cin>>n>>d>>a;
	for(int i=1;i<=n;i++)
		cin>>m[i].x>>m[i].h;
	sort(m+1,m+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(m[i].h>0){
			int used=c(m[i].h,a);
			for(int j=i;j<=n&&m[j].x-m[i].x<=2*d;j++)
				m[j].h-=used*a;
			ans+=used;
		}
	}
	cout<<ans;
	return 0;
}
```

结果 3TLE...

然后只能考虑优化了。

可以考虑为因为在炸弹范围内的怪物血量都会减去一个相同的数，然后很容易考虑到差分。

同时枚举炸弹最后炸到的怪兽计算量还是比较大的，但是二分能优化。

有了这两个优化这题就AC了

## AC Code
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN=2e5+5;
int n,D,a;
long long ans=0;
struct monster{
	int x;
	int h;
}m[MAXN];

long long d[MAXN];

bool cmp(monster x,monster y){
	return x.x<y.x;
}
int c(int p,int q){
	return p/q+(p%q!=0);
}
int main(){
	cin>>n>>D>>a;
	for(int i=1;i<=n;i++)
		cin>>m[i].x>>m[i].h;
	sort(m+1,m+n+1,cmp);
	m[0].h=m[1].h;
	for(int i=1;i<=n;i++)
		d[i]=m[i].h-m[i-1].h;
	for(int i=1;i<=n;i++){
		m[i].h=m[i-1].h+d[i];
	//	cout<<m[i].h<<" ";
		if(m[i].h>0){
			int used=c(m[i].h,a);
			int l=i,r=n,mid;
			while(l<r){
				mid=(l+r+1)/2;
				if(m[mid].x-m[i].x<=2*D)
					l=mid;
				else
					r=mid-1;
			}
		//	cout<<l<<" "<<used<<" ";
			d[l+1]+=a*used;
			m[i].h-=a*used;
			ans+=used;
		//	cout<<m[i].h<<" "<<d[l+1]<<endl;
		}
	}
	cout<<ans;
	return 0;
}
	
```

祝：早日AC

---

## 作者：WaterSun (赞：3)

模拟赛最后 $15$ 分钟想到的做法。

# 思路

首先有一个显然的贪心策略：我们放炸弹的地方要尽可能的使这个炸弹能影响到更多的怪上。

那么我们可以将对于一个怪 $i$ 能够影响到它的区间表示出来 $[\max(1,l_i - d),a_i + r]$。

然后将这些区间排个序，可以粗略画出这样的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/bzy54t52.png)

根据上文提到的贪心策略，发现在红线处放炸弹最优。大胆猜测如果对于当前枚举到的怪还需要用炸弹，一定用在能够影响它的区间的右端点。

不难发现这样做是正确的，因为当你处理 $i$ 时，$1 \sim (i - 1)$ 都已经处理完毕，而你已经对区间排序了，所以 $i \sim n$ 的区间一定在 $i$ 之后，放在右端点一定最优。

那么，如何处理 $i$ 还需要用几个炸弹。

首先刚开始时，显然要用 $\lceil \frac{h_i}{a} \rceil$ 个。

在处理了 $1 \sim (i - 1)$ 之后，$i$ 还需要用 $\max(0,\lceil \frac{h_i}{a} \rceil - \Delta)$ 个炸弹，其中 $\Delta$ 表示在处理 $1 \sim (i - 1)$ 时，在能影响当前怪的区间中的炸弹数量。

发现单点修改，区间查询，直接用树状数组维护即可。因为 $x_i$ 较大，需要离散化。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 4e5 + 10;
int n,d,k,m,idx,ans;
vector<int> p;
unordered_map<int,int> mp;

struct point{
	int x;
	int num;
	
	friend bool operator <(const point &a,const point &b){
		return a.x < b.x;
	}
}arr[N];

struct sec{
	int l;
	int r;
	int num;
	
	friend bool operator <(const sec &a,const sec &b){
		if (a.l != b.l) return a.l < b.l;
		return a.r < b.r;
	}
}s[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int up(int a,int b){
	if (a % b == 0) return a / b;
	return a / b + 1;
}

struct BIT{
	int tr[N];
	
	inline int lowbit(int x){
		return x & -x;
	}
	
	inline void modify(int x,int k){
		if (!x) return;
		for (re int i = x;i <= m;i += lowbit(i)) tr[i] += k;
	}
	
	inline int query(int x){
		int res = 0;
		for (re int i = x;i;i -= lowbit(i)) res += tr[i];
		return res;
	}
}tree;

signed main(){
	n = read();
	d = read();
	k = read();
	for (re int i = 1;i <= n;i++){
		int h;
		arr[i].x = read();
		h = read();
		arr[i].num = up(h,k);
	}
	sort(arr + 1,arr + n + 1);
	for (re int i = 1;i <= n;i++){
		p.push_back(max(1ll,arr[i].x - d));
		p.push_back(arr[i].x + d);
		s[i] = {max(1ll,arr[i].x - d),arr[i].x + d,arr[i].num};
	}
	sort(p.begin(),p.end());
	unique(p.begin(),p.end());
	for (auto x:p) mp[x] = ++idx;
	for (re int i = 1;i <= n;i++){
		s[i] = {mp[s[i].l],mp[s[i].r],s[i].num};
		m = max(m,s[i].r);
	}
	sort(s + 1,s + n + 1);
	for (re int i = 1;i <= n;i++){
		int cnt = s[i].num - tree.query(s[i].r) + tree.query(s[i].l - 1);
		if (cnt <= 0) continue;
		ans += cnt;
		tree.modify(s[i].r,cnt);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：2)

边打模拟赛边发题解（               

刚开始读错题意，以为只能打在怪兽上面，实际上是可以在数轴上任意投掷。          

我们考虑先将所有点排好序，然后从左到右做。             

我们考虑对于第一个点打在哪里最好，很明显我们打在离第一个点最远且能打到第一个点的位置最好，也就是 $x_1 + d$ ，因为这样才可以多打到后面的点。                      

然后我们在这里尽量多打直到把第一个点打死，然后去考虑第二个点。因为我们每一步都是最优的，所以贪心成立。              

实现过程中注意要 upperbound ，然后区间减法可以通过差分做成 $O(1)$ ，这里用线段树实现。               

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
#define int long long
int n,m,d,IDX[Len];
struct node
{
	int x,h;
}P[Len];
bool cmp(node x,node y){return x.x < y.x;}
long long ans[Len << 2],tag[Len << 2];
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
void push_up(int x){ans[x] = ans[ls(x)] + ans[rs(x)];}
void push_down(int p,int l,int r)
{
	if(tag[p])
	{
		tag[ls(p)] += tag[p] , tag[rs(p)] += tag[p];
		int mid = (l + r) >> 1;
		ans[ls(p)] += (mid - l + 1) * tag[p] , ans[rs(p)] += (r - mid) * tag[p];
	} 
	tag[p] = 0;
}
void build(int p,int l,int r)
{
	ans[p] = 0;
	if(l == r){ans[p] = P[l].h;return;}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
}
void update(int p,int l,int r,int nl,int nr,int v)
{
	if(nl <= l && nr >= r){tag[p] += v , ans[p] += v * (r - l + 1) ; return;}
	push_down(p , l , r);
	int mid = (l + r) >> 1;	
	if(nl <= mid) update(ls(p) , l , mid , nl , nr , v);
	if(nr > mid) update(rs(p) , mid + 1 , r , nl , nr , v);
	push_up(p);
}
int query(int p,int l,int r,int idx)
{
	if(l == r) return ans[p];
	push_down(p , l , r);
	int mid = (l + r) >> 1;
	if(idx <= mid) return query(ls(p) , l , mid , idx);
	return query(rs(p) , mid + 1 , r , idx); 
} 
int Ceil(int a,int b)
{
	if(a % b == 0) return a / b;
	return a / b + 1;
}
signed main()
{
	scanf("%lld %lld %lld",&n,&d,&m);
	for(int i = 1 ; i <= n ; i ++) scanf("%lld %lld",&P[i].x,&P[i].h);
	sort(P + 1 , P + 1 + n , cmp);
	for(int i = 1 ; i <= n ; i ++) IDX[i] = P[i].x;
	build(1 , 1 , n);int ans = 0;
	for(int i = 1 ; i <= n ; i ++) 
	{
		int to = P[i].x + d + d , val = query(1 , 1 , n , i);
		if(val <= 0) continue;
		int idx = upper_bound(IDX + 1 , IDX + 1 + n , to) - IDX;idx --;
		int nums = Ceil(val , m);ans += nums; 
		update(1 , 1 , n , i , idx , -nums * m);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：STARSczy (赞：1)

# 思路：
炸弹爆炸范围为 $l$ 到 $l+2d$，容易想到最好是从左到右挨个爆破，但是这样范围太大了，当 $d$ 稍微大一点，就可能要 T，所以想到把在这段区间的怪物二分出来，得到这些数的下标，再使用线段树维护区间减（打虚拟赛时，没有线段树板子，就用无旋 treap 了）。时间复杂度 $\Theta(n \log n)$。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10,mod=1e9+7;
inline int read(){
	int c,w=0,n=0;
	while((c=getchar())<'0'||'9'<c) w=c=='-';
	do n=n*10+c-'0';while('0'<=(c=getchar())&&c<='9');
	return w?-n:n;
}
inline int write(int n){
	if(n<0) putchar('-'),n=-n;
	if(n>9) write(n/10);
	putchar(n%10+'0');
	return n;
}
struct sgtree{
	struct node{
		int data,size,sum,lazy,vis,turn;
		node *l,*r;
	}*root;
	node* newnode(int n){
		node *p=new node;
		p->data=n,p->size=1,p->sum=p->lazy=0,p->vis=rand(),p->l=p->r=0;
		return p;
	}
	void down(node *p){
		if(p->turn==1) swap(p->l,p->r),p->turn=0,p->l->turn^=1,p->r->turn^=1;
		p->data+=p->lazy,p->sum+=(p->size)*(p->lazy);
		if(p->l) p->l->lazy+=p->lazy;
		if(p->r) p->r->lazy+=p->lazy;
		p->lazy=0;
	}
	void pushup(node *p){
		p->sum=p->data,p->size=1;
		down(p);
		if(p->l){
			down(p->l);
			p->sum+=p->l->sum,p->size+=p->l->size;
		}
		if(p->r){
			down(p->r);
			p->sum+=p->r->sum,p->size+=p->r->size;
		}
	}
	void split(node *id,int val,node *&l,node *&r){
		if(!id){
			l=r=0;
			return;
		}
		down(id);
		int ls=0;
		if(id->l) ls=id->l->size;
		if(val<=ls){
			r=id;
			split(id->l,val,l,id->l);
		}
		else{
			l=id;
			split(id->r,val-(ls+1),id->r,r);
		}
		pushup(id);
	}
	node* merge(node *l,node *r){
		if(!l||!r) return l?l:r;
		if(l->vis<r->vis){
			down(l);
			l->r=merge(l->r,r);
			pushup(l);
			return l;
		}
		down(r);
		r->l=merge(l,r->l);
		pushup(r);
		return r;
	}
	void ins(int id,int x){
		node *a=0,*b=0,*c=newnode(x);
		split(root,id-1,a,b);
		b=merge(c,b),root=merge(a,b);
	}
	void del(int id){
		node *a=0,*b=0,*c=0;
		split(root,id-1,a,b);
		split(b,id,b,c);
		root=merge(a,c);
	}
	int sum(int l,int r){
		int ans;
		node *a=0,*b=0,*c=0;
		split(root,r,b,c);
		split(b,l-1,a,b);
		if(b) ans=b->sum;
		root=merge(a,merge(b,c));
		return ans;
	}
	int get(int id){return sum(id,id);}
	void add(int l,int r,int x){
		node *a=0,*b=0,*c=0;
		split(root,r,b,c);
		split(b,l-1,a,b);
		if(b) b->lazy+=x;
		root=merge(a,merge(b,c));
	}
	int size(){
		if(root) return root->size;
		return 0;
	}
	void rot(int l,int r){
		node *a=0,*b=0,*c=0;
		split(root,r,b,c);
		split(b,l-1,a,b);
		if(b) b->turn^=1;
		root=merge(a,merge(b,c));
	}
	void clear(){root=NULL;}
}t;//模板

int n=read(),d=read(),k=read(),ans,a[maxn],b[maxn];
pair<int,int> h[maxn];

signed main(){
	for(int i=1;i<=n;++i) h[i].first=read(),h[i].second=read();
	sort(h+1,h+n+1);//按坐标排序
	for(int i=1;i<=n;++i)
		a[i]=h[i].first,b[i]=h[i].second,t.ins(i,b[i])/*插入操作*/;
	a[n+1]=INT_MAX;
	for(int i=1;i<=n;++i) if(t.get(i)/*单点查询*/>0){
		int l=i/*左端点*/,x=t.get(i),cnt=(x-1)/k+1/*要减多少次*/;
        int r=lower_bound(a+1,a+n+1,a[i]+2*d)-a/*右端点*/;
		if(a[r]>a[i]+2*d) r--;/*
由于lower_bound的返回值是大于等于的最小数，可能存在大于的情况，
所以出现大于的情况右端点下标要减1
*/
		t.add(l,r,-cnt*k),ans+=cnt;//区间加
	}
	write(ans);
	return 0;
}
```

---

## 作者：_AyachiNene (赞：1)

# 思路：
很明显是贪心。我们想让炸的次数尽量小，很明显，当前面的所有点都处理完时，用炸弹的左端点去炸这个点是最优的。很容易就能想到用线段树来维护每个坐标受到的伤害。但是 $0\leq x_i\leq10^9$，显然不行。因为坐标是有单调性的，所以可以直接二分查找，再用线段树维护就行了。
# Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define ls root*2
#define rs root*2+1
using namespace std;
struct node1
{
	int x,h;
}a[114514*2];
bool cmp(node1 x,node1 y)
{
	return x.x<y.x;
}
//以下为线段树 
struct node
{
	int l,r,val,f; 
}t[1145141];
void bld(int l,int r,int root)
{
    t[root].l=l;
    t[root].r=r;
    if(l==r)
        return;
    int mid=(l+r)/2;
    bld(l,mid,root*2);
    bld(mid+1,r,root*2+1);
    t[root].val=(t[ls].val+t[rs].val);
}
void down(int root)
{
    t[ls].f+=t[root].f;
    t[rs].f+=t[root].f;
    t[ls].val=t[ls].val+(t[ls].r-t[ls].l+1)*t[root].f;
    t[rs].val=t[rs].val+(t[rs].r-t[rs].l+1)*t[root].f;
    t[root].f=0;
}
void add(int x,int y,int root,int k)
{
	if(x<=t[root].l&&y>=t[root].r)
	{
		t[root].val+=(t[root].r-t[root].l+1)*k;
		t[root].f+=k;
		return;
	}
	if(t[root].f)
		down(root);
    int mid=(t[root].l+t[root].r)/2;
	if(x<=mid)
		add(x,y,ls,k);
	if(y>mid)
		add(x,y,rs,k);
	t[root].val=t[ls].val+t[rs].val;
}
int query(int x,int y,int root)
{
    int ret=0;
    if(t[root].l>=x&&t[root].r<=y)
        return t[root].val;
    if(t[root].f)
        down(root);
    int mid=(t[root].l+t[root].r)/2;
    if(x<=mid)
        ret=ret+query(x,y,ls);
    if(y>mid)
        ret=ret+query(x,y,rs);
    return ret;
}
//以上为线段树 
int ans;
int n,d,A;
int x[1145141];
signed main()
{
	cin>>n>>d>>A;
	bld(1,n,1);
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].h,x[i]=a[i].x;
	sort(a+1,a+n+1,cmp);
	sort(x+1,x+n+1);
	for(int i=1;i<=n;i++)
		add(i,i,1,a[i].h);
	x[n+1]=2e5;
	for(int i=1;i<=n;i++)
	{
		if(query(i,i,1)<=0)
			continue;
		int k=ceil(query(i,i,1)*1.0/A);
		ans+=k;
		int nxt=upper_bound(1+x,1+x+n,x[i]+2*d)-x-1;
		add(i,nxt,1,-k*A);
	}
	cout<<ans;
}
```


---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc153_f)


#### 思路

考虑到每一个怪物都必须死，于是考虑贪心，先按坐标排序，如果当前这个怪没死，且位置为 $x_i$，那么炸弹肯定放在 $x_i + d$ 最优，能炸到更多的怪物，用二分找到第一个**不在**爆炸范围的怪物位置，用差分将这里标记即可。

code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,d,a,bj,ans,l,r,mid,pp,oo,b[200010];
struct w
{
	long long x,h;
}c[200010];
bool cmp(w xx,w yy)
{
	return xx.x < yy.x;
}
int main()
{
	scanf("%lld%lld%lld",&n,&d,&a);
	for(int i = 1;i <= n;i++) scanf("%lld%lld",&c[i].x,&c[i].h);
	sort(c + 1,c + 1 + n,cmp);
	for(int i = 1;i <= n;i++) 
	{
		bj -= b[i];//经典差分 
		if(c[i].h - bj * a > 0)
		{
			l = i,r = n; oo = n + 1;//有可能全部在炸弹范围内，一定要注意这里 
			while(l <= r)
			{
				mid = (l + r) / 2;
				if(c[mid].x > c[i].x + 2 * d) r = mid - 1,oo = mid;
				else l = mid + 1;
			}
			b[oo] += ((c[i].h - bj * a + a - 1) / a);//差分，是 +=，不是等于
			ans += (c[i].h - bj * a + a - 1) / a;
			bj += (c[i].h - bj * a + a - 1) / a;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：__Chx__ (赞：1)

## 思路
考虑贪心，从左往右进行模拟。当需要消灭坐标位置为 $x$ 的怪物时，考虑用二分求出 $x-2D$ 到 $x$ 范围内对 $x$ 有影响的怪物坐标点，再用树状数组维护每个怪物坐标对后面的影响的前缀和（~~差分也可以~~），就可以算出每个坐标点实际需要被处理的怪物血量，最后对此进行处理并记录在树状数组中便完成了。

具体细节代码会有注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int N,D,A,tr[200005],ans;
struct node{
	int x,h;
}a[200005];
int lb(int x){return x&(-x);}//lowbit
void add(int x,int k){//统计坐标影响 
	for(int i=x;i<=N;i=i+lb(i)) tr[i]+=k;
	return;
}
int sum(int x){//计算坐标影响的前缀和 
	int res=0;
	for(int i=x;i;i=i-lb(i)) res+=tr[i];
	return res;
}
bool cmp(node l,node r){return l.x<r.x;}//按照坐标从小到大排序 
int f(int x){//二分查找在x之前最远可以对它产生影响的坐标 
	int l=1,r=N,ans;
	while(l<=r){
		int mid=(l+r)/2;
		if(a[mid].x>=x-2*D) r=mid-1,ans=mid;
		else l=mid+1;
	}
	return ans;
}
void slove(int x){//处理坐标贡献 
	int res=max(a[x].h-sum(x)+sum(f(a[x].x)-1),0ll);
	ans=ans+res/A+bool(res%A);
	res=(res/A+bool(res%A))*A,add(x,res);
	return;
}
signed main(){
	cin>>N>>D>>A;
	for(int i=1;i<=N;i++) cin>>a[i].x>>a[i].h;
	sort(a+1,a+1+N,cmp);//排序 
	for(int i=1;i<=N;i++) slove(i);//计算每个坐标的贡献 
	cout<<ans<<endl;//完结 
	return 0;
} 
```



---

## 作者：YclarHIM0302 (赞：1)

# 基本思路
这题主要运用贪心+差分的方法。

首先，我们需要将“投放炸弹，计算伤害”的思维改为“已知伤害，计算炸弹数量”：
既然每个怪兽最终都会被炸死，那么每只怪兽就至少会受到$\left\lceil\dfrac{H_i}{h}\right\rceil$个炸弹的攻击。

既然要求最小值，那么就应该考虑炸弹的**最大利用性
~~（瞎编的www）~~**。
举个例子：

有两个怪兽， $x_1=1, x_2=9, d=4,$

若是把炸弹放在 $x=1$ 的位置，就只能炸到一号怪兽。

（因为还有一半位置在负轴上 $(x<0)$ ，浪费掉了)

但是，要是把炸弹的位置右移，一直到 $x=5$ 的位置，它就可以炸到两个怪兽。

也就是说，在此时，炸弹的利用性最大。

------------
根据以上推论，我们发现可以将炸弹的范围 $(x-d,x+d)$ 转化为 $(x_i,x_i+2d)$ ，这样就能够更好算一点。

在每次操作时，我们将 $(x_i,x_i+2d)$ 的范围扣在第 $i$ 个怪兽的头上，然后看在此范围内被炸掉的怪兽有哪些并**记录**下它们所受的伤害。

以例1举例的话就是：
![eg](https://cdn.luogu.com.cn/upload/image_hosting/iz4bija5.png)


**注意：每次轰炸时，应将所选择的怪兽炸到死为止！**
# 关于差分的问题
注：其解释搬运自[我的博客](https://www.luogu.com.cn/blog/narokoda-yclar/ge-ge-suan-fa-mu-ban-da-quan)

![差分1](https://cdn.luogu.com.cn/upload/image_hosting/n0yy6qgd.png)
如图所示，差分数组b每项的值是数组a连续每项之间的差值。其公式为：

$b_i=a_i-a_{i-1}(1\leqslant i \leqslant n)$

在修改一个区间的结点值时，就可以使用差分数组进行运算。
#### e.g.

| 下标 | 0 | 1 | 2 | 3 | 4 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :---------: |
| a | 0 | 1 | 2 | 4 | 1 |
| b | 0 | 1 | 1 | 2 | -3 |

要求 `[1,3]` 区间数值加一：

| 下标 | 0 | 1 | 2 | 3 | 4 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :---------: |
| a | 0 | 1+1 | 2+1 | 4+1 | 1 |
| b | 0 | 1+1 | 1 | 2 | -3-1 |

发现了吗？只有 `b[1]` 与 `b[4]` 的值变化了。

结论：当区间 `[l,r]` 加上一个值 `k` 时：

$b_l+=k,b_{r+1}-=k(1 \leqslant l \leqslant r < n)$

在计算 `a[i]` 的每一项时，就用前缀和叠加：

$a_i=\sum\limits_{k=0}^n b[k] $

这就是差分以及差分数组的运用。

在此题中，我们可以将其运用于伤害的记录。

# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,d,h;
long long tot; //不开long long的话...（RE+1WA）
pair<int,int> a[200005]; //这里推荐使用pair而非struct,因为计算似乎更快一些
int b[200005];
bool cmp(pair<int,int> x,pair<int,int> y)
{
	return x.first<y.first;
}
int main()
{
	scanf("%d %d %d",&n,&d,&h);
	for(int i=1;i<=n;i++)
	scanf("%d %d",&a[i].first,&a[i].second);
	sort(a+1,a+n+1,cmp);
	d*=2; //tip:提前×2便于计算（没必要）
	for(int i=1;i<=n;i++)
	{
		b[i]+=b[i-1];
		int value=a[i].second-b[i]*h;
		if(value<=0) continue;
		int p=(value+h-1)/h; //此处p为炸弹的数量
		tot+=p;
		b[i+1]+=p;
		int l=i,r=n; //二分计算出第一个不在范围内的怪兽
		while(l<=r) //一定要二分！for算的过慢，尤其是在2*d的范围内怪兽数量过多的时候！
		{
			int mid=(l+r)>>1;
			if(a[mid].first<=a[i].first+d) l=mid+1;
			else r=mid-1;
		}
		b[r+1]-=p; //差分右限
	}
	printf("%lld",tot);
	return 0;
} 
```


---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

考虑贪心。从左往右遍历鬼，如果遍历到的鬼在第 $i$ 个位置并且没有死，放正好足够的炸弹在位置 $i+D$ 上。使用一个堆或者一个BIT来维护鬼的 HP。（BIT维护差分）

这个贪心策略肯定是最优，应为如果在一个不同的顺序放炸弹，可能会重叠或者忽略一个鬼。这个方法保证所有鬼都在最小动作下杀了。

注意不能直接离散化，应为D是固定的；必须二分来找到对应的BIT位置如果使用BIT或者线段树。

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
#define int ll
const int MOD = 1000000007;

int bit[200005]; int N;

void upd(int x, int v) { x++; while(x <= N) { bit[x] += v; x += (-x&(x)); } }
int get(int x) { x++; int ans = 0; while(x) { ans += bit[x]; x -= (-x&(x)); } return ans; }

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
	int dia, A; cin >> N >> dia >> A;
	vector<pii> v;
	rep(i, N) {
		int loc, ne; cin >> loc >> ne;
		ne = (ne + A - 1) / A;
		v.pb({loc, ne});
	}
	sort(all(v));
	int ans = 0;
	rep(i, N) {
		if(get(i) >= v[i].se) continue;
		// bin search for last index <= than v[i].fi+2*dia
		int targ = v[i].fi+2*dia;
		int lef = i, rig = N-1, ban = i;
		while(lef <= rig) {
			int mid = (lef+rig)/2;
			if(v[mid].fi > targ) rig = mid-1;
			else { lef = mid+1; ban = mid; }
		}
		int dt = v[i].se-get(i);
		ans += dt;
		upd(i, dt); upd(ban+1, -dt);
	}
	cout << ans << endl;	
}


```


---

## 作者：SilverLi (赞：0)

[Silver Fox vs Monster の 传送门](https://www.luogu.com.cn/problem/AT_abc153_f)

题目要求需要投放的炸弹**最少有多少个**。

考虑贪心，先对 $X_i$ 排序。

### 基本做法

再从第一个开始，如果 $H_i>0$，那么循环枚举距离没超过 $2\times D$ 的最大的 $j$（为什么是 $2\times D$，因为可以在 $i$ 和 $j$ 中间投放炸弹），然后将 $i$ 到 $j$ 的所有 $H$ 减去 $\left \lceil \frac{H_i}{A}  \right \rceil $。

### 优化

发现 $1\leq N\leq 2\times 10^5$，所以我们的 $N^2$ 做法会 [TLE](https://atcoder.jp/contests/abc153/submissions/40169680)。

再看一下我们的做法，枚举 $j$，对 $H_j$ 做修改。

因为我们对 $X_i$ 排了序，所以满足单调性，考虑**二分**。

修改可以使用 `BIT` 或差分，~~我自认为~~差分更好写。

#### 差分的写法

我用的是 `pair` 排序，所以要差分需要用另一个数组 $d$。

差分时，将 $H_i$ 减去 $\left \lceil \frac{H_i}{A}  \right \rceil\times A$，并将 $d_j$ 加上 $\left \lceil \frac{H_i}{A}  \right \rceil\times A$。

$d_i$ 的初值设为 $H_i-H_{i-1}$，然后每次循环开始时让 $H_i=H_{i-1}+d_i$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define x first
#define h second
const int N=2e5+5;
int n,D,A,ans,d[N];
pair<int,int> a[N];
signed main() {
	cin>>n>>D>>A;
	for(int i=1;i<=n;++i)	cin>>a[i].x>>a[i].h;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)	d[i]=a[i].h-a[i-1].h;
	for(int i=1;i<=n;++i) {
		a[i].h=a[i-1].h+d[i];
		if(a[i].h<=0)	continue;
		int used=a[i].h/A+(a[i].h%A!=0);
		int l=i,r=n,res=i;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(a[mid].x-a[i].x<=D*2)	l=mid+1,res=mid;
			else	r=mid-1;
		}
		a[i].h-=used*A,d[res+1]+=used*A;
		//for(int j=i;j<=n&&a[j].x-a[i].x<=d*2;++j)	a[j].h-=used*A;
		ans+=used;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Federico2903 (赞：0)

考试的时候翻译出锅了，以为只包含 $x-D$，看了一眼原文，不包含是打在最后面的...  
首先要按照 $x$ 排序，考虑单调队列来存储炸弹影响到的区间。  
用一个 $sum$ 来记录当前位置的怪物会被炸弹炸掉多少的伤害，如果怪物的血量比这个伤害还要大，那么使用贪心的思想以这里作为左端点放炸弹把这个怪物炸死，然后将这个伤害区间放进单调队列，并且把答案加上个数。  
代码中的 area 队列存储了炸弹的右端点，boom 存储了在这个位置放下的炸弹的个数。
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	long long int x,h;
}e[200005];
queue<long long int> area,boom;
signed main(){
	long long int n,d,a;
	cin >> n >> d >> a;
	for(long long int i=0;i<n;i++){
		cin >> e[i].x >> e[i].h;
	}
	sort(e,e+n,[](node a,node b)->bool{return a.x<b.x;});
	long long int ans=0,sum=0;
	for(long long int i=0;i<n;i++){
		while(!area.empty() && area.front()<e[i].x){
			sum-=boom.front()*a;
			area.pop();
			boom.pop();
		}e[i].h-=sum;
		if(e[i].h>0){
			ans+=(e[i].h+a-1)/a;area.push(e[i].x+2*d);
			sum+=((e[i].h+a-1)/a)*a;boom.push((e[i].h+a-1)/a);
		}
	}
	cout << ans;
}
```

---

## 作者：smilke (赞：0)

考虑贪心。

因为要保证每个怪都要被消灭，所以从左往右一个个消灭必然可以满足条件，那么如何保证次数最少呢？

假设你从第二个怪或者以后的怪开始消灭，那么最后回头还是要重新消灭前面的怪，也等同于从最左边的第一个怪开始消灭，这就表明从左往右一个个消灭怪物必然是最优的。

那么做法就显然了。

首先将怪物按照坐标从左往右排序。先施魔法将最左边的怪灭了，标记一下施法对后面怪的伤害，用差分标记就可以了。按照这种方法从左往右扫一遍，时间复杂度可以做到$O(nlogn)$.

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=1e6+50;
int n,d,A,ans=0,r=1,v[N];
struct node{ int x,z; }a[N];
bool mycmp(node a,node b){ return a.x<b.x; }
int solv(int x){
	if(x%A==0) return x/A;
	else return x/A+1;
}
signed main(){
	scanf("%lld%lld%lld",&n,&d,&A);
	rep(i,1,n) scanf("%lld%lld",&a[i].x,&a[i].z);
	sort(a+1,a+n+1,mycmp);
	rep(i,1,n){
		v[i]+=v[i-1]; a[i].z-=v[i];
		if(a[i].z<=0) continue;
		while(a[r].x-a[i].x<=2*d&&r<=n) r++;
		int t=solv(a[i].z);
		v[i]+=t*A; v[r]-=t*A;
		ans+=t;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Mu_leaf (赞：0)

## [思路]

很明显我们可以将题目中所提及的爆炸范围为 $x-D$ 和 $x+D$ 改为 $x+2\times D$。这样我们修改一个怪物的血量就只会影响到坐标大于等于此怪物的怪物了。

因为我们需要修改 $x$ 到 $x+2 \times D$ 的这段区间，且这段区间每次修改的值都是一个定值，可以考虑差分。

说到差分，应该立刻想到树状数组。不懂树状数组[这边走](https://www.luogu.com.cn/blog/TJor/xian-duan-shu-yu-shu-zhuang-shuo-zu)。

现在考虑树状数组里面保存什么，很明显有两个方案。

- $tr_i$ 表示坐标小于等于 $i$ 的怪物的血量和。
- $tr_i$ 表示**下标小于**等于第 $i$ 个怪物的受到的伤害总和。

由于第一个方案可能将没有怪物的格子变为负数，从而影响后面的计算所以采用的二个方法。

将数组 $a$ 以怪物的坐标为第一关键字排序。则我们可以使用指针维护距离当前点向右距离在 $2 \times D$ 内的点。

然后即可用 $r$ 指针维护若在这个位置放下炸弹会影响到那个怪物。

## 注意：
- 记得开 ```long long```。
- 在每个怪物的血量减完前面炸怪物所产生伤害后判断是否大于 $0$，否则它是对答案没有贡献的。

# 代码:
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,d,x,ans;
map<int,int> tr;
struct node{
	int x,h;
}a[200005];
ll lowbit(ll x){
	return x&(-x);
}
ll query(int x){
	int ans=0;
	for(;x;x-=lowbit(x)) ans+=tr[x];
	return ans;
}
void add(ll x,ll d){
	for(;x<=n;x+=lowbit(x)) tr[x]+=d;
}
bool cmp(node a,node b){
	return a.x<b.x; 
}
int main(){
	cin>> n >> d >>x;
	for(int i=1;i<=n;i++) cin >> a[i].x >> a[i].h;
	sort(a+1,a+n+1,cmp);
	for(int i=1,r=1;i<=n;i++){
		while(r<=n && a[r+1].x-a[i].x<=2*d) r++;
		a[i].h-=query(i);
		if(a[i].h>0){
			int c=(a[i].h)/x+(a[i].h%x!=0); 
			ans+=c;
			add(i,c*x);
			add(r+1,-c*x);
		}
	}cout << ans;
	return 0;
}

```


---

