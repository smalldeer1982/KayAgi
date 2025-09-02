# Lucky Array

## 题目描述

Petya 喜欢幸运数，幸运数只包含 $4$ 和 $7$ 这两个数字。例如 $47$，$744$，$4$ 都是幸运数字，但 $5,16,467$ 不是。

Petya 有一个 $N$ 个数的数组，他想给这个数组执行 $M$ 个操作，可以分为两种操作：

1. `add l r d` 把第 $l$ 到第 $r$ 个数都加上 $d$；
2. `count l r` 统计第 $l$ 到第 $r$ 个数有多少个幸运数字。

保证所有数操作前后都不超过 $10^4$。

请你编一个程序来执行这些操作。

$1\leq N,M\leq 10^5$，$1\leq l\leq r\leq N$，$1\leq d \leq 10^4$。

## 说明/提示

对于第一个样例：

1. 执行了 `add 1 3 2` 操作之后变成：$[4, 5, 6]$；
2. 执行了 `add 2 3 3` 操作之后变成：$[4, 8, 9]$。

对于第二个样例：

1. 执行了 `add 1 4 3` 之后变成：$[7,7,7,7]$；
2. 执行了 `add 2 3 40` 之后变成：$[7,47,47,7]$。

## 样例 #1

### 输入

```
3 6
2 3 4
count 1 3
count 1 2
add 1 3 2
count 1 3
add 2 3 3
count 1 3
```

### 输出

```
1
0
1
1
```

## 样例 #2

### 输入

```
4 5
4 4 4 4
count 1 4
add 1 4 3
count 1 4
add 2 3 40
count 1 4
```

### 输出

```
4
4
4
```

# 题解

## 作者：Styx (赞：14)

**哇，这道题真是令人智熄，我们要相信树状数组的复杂度是几乎O(1)的QAQ**

**大概的具体做法就是先从每个数都不超过一万入手，每次操作加操作最少加一，所以最多一万次加操作，这并没有什么卵用，主要是我们可以用爆枚枚举出每一个幸运数，然后O(1)询问。**

**除此之外就是把区间修改换成树状数组型的单点修改，然后就莫名其妙的AC了……**

**我也很绝望啊，谁知道这道题的标算到底是什么啊QAQ**

**代码如下**

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int a[100010],f[100010],sum[100010],n,m;

void get(int now)
{
	if(now*10+7<=10000)
	{
		f[now*10+7]=1;
		get(now*10+7);
	}
	if(now*10+4<=10000)
	{
		f[now*10+4]=1;
		get(now*10+4);
	}
}

int lowbit(int x)
{
	return (-x)&x;
}

void add(int i,int val)
{
	while(i<=n)
	{
		sum[i]+=val;
		i+=lowbit(i);
	}
}

int count(int i)
{
	int ans=0;
	while(i>0)
	{
		ans+=sum[i];
		i-=lowbit(i);
	}
	return ans;
}

int main()
{
	scanf("%d%d",&n,&m);
	get(0);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(f[a[i]])
		{
			add(i,1);
		}
	}
	char c[10];
	int l,r,val;
	while(m--)
	{
		scanf("\n%s",c);
		if(c[0]=='c')
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",count(r)-count(l-1));
		}
		else
		{
			scanf("%d%d%d",&l,&r,&val);
			for(int i=l;i<=r;i++)
			{
				if(f[a[i]])
				{
					add(i,-1);
				}
				a[i]+=val;
				if(f[a[i]])
				{
					add(i,1);
				}
			}
		}
	}
}
```

---

## 作者：elijahqi (赞：9)

https://blog.csdn.net/elijahqi/article/details/80993829
http://www.elijahqi.win/archives/1838

蒟蒻我的做法应该是一个复杂度有保证的做法
题意 要求我们求一段区间内 幸运数字有多少个 对于幸运数字的定义是：只能包含十进制下的4&7而且题目保证这个他加的数最终不会超过1e4那么我们考虑这题是否和有一个开根号的那题相似呢 大概leoly说很像呢 所以做法就是 我对于线段树上每个点我去储存d[i]表示我的值到距离我最近的那个幸运数字的差是多少 然后维护一个这些值的最小值 维护一下这个最小值最早出现在哪里 再维护一下我最小值一共有几个 然后修改的时候我相当于是区间减法 然后如果这个整个所有1~n中出现了负数 那么我就定位到第一个负数出现在哪里把他改成距离下一个幸运数字的大小 然后重新更新上去 最后直到我1~n中不再有<0的数出现即可 询问的时候只需要询问我最小值为0的数有多少个即可
```
#include<queue> 
#include<cstdio>
#include<algorithm>
#define N 110000
#define inf 0x3f3f3f3f
#define pa pair<int,int>
using namespace std;
inline int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
struct node{
	int left,right,min,mp,mn,v,lazy;
}tree[N<<2];
int mp[]={0,4,7,44,47,74,77,444,447,474,744,477,747,774,777,4444,4447,4474,4744,7444,4477,4747,7447,4774,7474,7744,4777,7477,7747,7774,7777,999999999};
int n,m,a[N],num,root;char s[30];
inline void update(int x){
	 int l=tree[x].left,r=tree[x].right;
	 if (tree[l].min==tree[r].min){
	 	tree[x].mn=tree[l].mn+tree[r].mn;
	 	tree[x].min=tree[l].min;tree[x].mp=min(tree[l].mp,tree[r].mp);
	 }
	 if (tree[l].min<tree[r].min){
	 	tree[x].min=tree[l].min;tree[x].mn=tree[l].mn;tree[x].mp=tree[l].mp;
	 }
	 if (tree[r].min<tree[l].min){
	 	tree[x].min=tree[r].min;tree[x].mn=tree[r].mn;tree[x].mp=tree[r].mp;
	 }
}
inline void pushdown(int x){
	if (!tree[x].lazy) return;
	int l=tree[x].left,r=tree[x].right;
	tree[l].lazy+=tree[x].lazy;tree[r].lazy+=tree[x].lazy;
	tree[l].min-=tree[x].lazy;tree[r].min-=tree[x].lazy;
	tree[x].lazy=0;
}
void build(int &x,int l,int r){
	x=++num;
	if (l==r){
		int pos=lower_bound(mp+1,mp+32,a[l])-mp;
		tree[x].v=mp[pos];tree[x].min=mp[pos]-a[l];tree[x].mp=l;tree[x].mn=1;return;
	}
	int mid=l+r>>1;
	build(tree[x].left,l,mid);build(tree[x].right,mid+1,r);update(x);
}
inline void change(int x,int l,int r,int p){
	if(l==r){
		int now=tree[x].v-tree[x].min,pos=lower_bound(mp+1,mp+32,now)-mp;
		tree[x].v=mp[pos];tree[x].min=mp[pos]-now;return;
	}
	int mid=l+r>>1;pushdown(x);
	if(p<=mid) change(tree[x].left,l,mid,p);else change(tree[x].right,mid+1,r,p);update(x);
}
inline pa update1(pa p1,pa p2){
	int fi,se;
	if(p1.first<p2.first) fi=p1.first,se=p1.second;
	if(p1.first==p2.first) fi=p1.first,se=p1.second+p2.second;
	if(p1.first>p2.first) fi=p2.first,se=p2.second;return make_pair(fi,se);
}
inline pa qr(int x,int l,int r,int l1,int r1){
	if(l1<=l&&r1>=r){pa pp;pp=make_pair(tree[x].min,tree[x].mn);return pp;}
	int mid=l+r>>1;pa tmp;tmp=make_pair(inf,99);pushdown(x);
	if(l1<=mid) tmp=update1(tmp,qr(tree[x].left,l,mid,l1,r1));
	if(r1>mid) tmp=update1(tmp,qr(tree[x].right,mid+1,r,l1,r1));return tmp;
}
inline void insert1(int x,int l,int r,int l1,int r1,int v){
	if(l1<=l&&r1>=r){tree[x].lazy+=v;tree[x].min-=v;return;}
	int mid=l+r>>1;pushdown(x);
	if(l1<=mid) insert1(tree[x].left,l,mid,l1,r1,v);
	if(r1>mid) insert1(tree[x].right,mid+1,r,l1,r1,v);update(x);
}
int main(){
	freopen("cf.in","r",stdin);
	n=read();m=read();sort(mp+1,mp+32);
	//for (int i=1;i<=31;++i) printf("%d\n",mp[i]);
	for (int i=1;i<=n;++i) a[i]=read();build(root,1,n);
	for (int i=1;i<=m;++i){
		scanf("%s",s+1);if (s[1]=='c'){
			int l=read(),r=read();pa pp=qr(root,1,n,l,r);
			if(pp.first==0) printf("%d\n",pp.second);else printf("0\n");
		} else{
			int l=read(),r=read(),v=read();insert1(root,1,n,l,r,v);
			while(tree[root].min<0) change(root,1,n,tree[root].mp);
		}
	}
	return 0;
}
```

---

## 作者：Arghariza (赞：7)

因为水平不够，所以想到暴力。

~~暴力数据结构是啥？分块呗。~~

把数列分成 $\sqrt n$ 个块，对每个块维护里面每个数的出现次数。

哦对了，这个缺德的翻译没有说，每个数在操作前后都不会大于 $10^4$，所以上面那个数组是 $O(b\sqrt n)$ 的，$b$ 为值域。

然后再对每个块维护一个 $tag$，表示给块内的数加上的标记。然后修改的时候散块直接暴力，块内打标记即可，查询遍历 $30$ 个 幸运数字，散块暴力查询，块内直接用维护的出现次数即可，复杂度 $O(30n\sqrt n)$。

但是这样你大概率会在第 $70$ 个点 $\mathtt{TLE}$，于是考虑大力优化。

首先那个 $30$ 的常数是能不卡满的，维护一个 $01$ 数列（值域上），表示 $i$ 这个数是否是幸运数字。然后散块查询的时候这个 $30$ 的常数就没了，当整块查询的时候可以从大到小枚举每个幸运数字，当这个数字小于标记的时候直接结束枚举即可。注意的是整块查询还是带有小于等于 $30$ 的常数。

加上上述优化即可通过本题。

```cpp
#include <bits/stdc++.h>
namespace mystd {
	inline int read() {
		int w = 1, q = 0;
		char ch = ' ';
		while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
		if (ch == '-') w = -1, ch = getchar();
		while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
		return w * q;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 1e5 + 100;
const int maxa = 1e4 + 100;
const int maxb = 400;
int n, m, b, lz[maxb], ct[maxb][maxa], lp[maxb], rp[maxb], pos[maxn], num[35], cnt, a[maxn], mp[maxa];

void add(int l, int r, int d) {
	int pl = pos[l], pr = pos[r];
	if (pl == pr) {
		for (int i = l; i <= r; i++) {
			ct[pl][a[i]]--, a[i] += d, ct[pl][a[i]]++;
		}
	} else {
		for (int i = pl + 1; i <= pr - 1; i++) lz[i] += d;
		for (int i = l; i <= rp[pl]; i++) ct[pl][a[i]]--, a[i] += d, ct[pl][a[i]]++;
		for (int i = lp[pr]; i <= r; i++) ct[pr][a[i]]--, a[i] += d, ct[pr][a[i]]++;
	}
}

int query(int l, int r) {
	int pl = pos[l], pr = pos[r], ans = 0;
	if (pl == pr) {
		for (int i = l; i <= r; i++) {
			ans += mp[a[i] + lz[pl]];
		}
	} else {
		for (int i = pl + 1; i <= pr - 1; i++) {
			for (int j = cnt; j && (num[j] - lz[i] >= 0); j--) {
				ans += ct[i][num[j] - lz[i]];
			}
		}
		for (int i = l; i <= rp[pl]; i++) ans += mp[a[i] + lz[pl]];
		for (int i = lp[pr]; i <= r; i++) ans += mp[a[i] + lz[pr]];
	}
	return ans;
}

int main() {
	n = read(), m = read(), b = sqrt(n);
	for (int i = 1; i <= b; i++) lp[i] = (i - 1) * b + 1, rp[i] = b * i;
	if (rp[b] < n) rp[++b] = n, lp[b] = rp[b - 1] + 1;
	for (int i = 1; i <= b; i++) {
		for (int j = lp[i]; j <= rp[i]; j++) {
			pos[j] = i;
		}
	}
	for (int i = 1; i <= 4; i++) {
		for (int j = 0; j <= (1 << i) - 1; j++) {
			int tp = i, t = j;
			cnt++;
			while (tp) {
				if (t & 1) num[cnt] = (num[cnt] + 4) * 10;
				else num[cnt] = (num[cnt] + 7) * 10;
				t >>= 1, tp--;
			}
			num[cnt] /= 10, mp[num[cnt]] = 1;
		}
	}
	sort(num + 1, num + cnt + 1);
	for (int i = 1; i <= n; i++) a[i] = read(), ct[pos[i]][a[i]]++;
	while (m--) {
		char op[10]; int l, r, d;
		scanf("%s", op + 1), l = read(), r = read();
		if (op[1] == 'a') {
			d = read();
			add(l, r, d);
		} else write(query(l, r)), puts("");
	}
	return 0;
}
```

---

## 作者：Celtic (赞：5)

这是一道线段树的好题。

这个题的翻译有一点没翻译出来，就是**无论怎么加序列中的数不会超过$10^4$**。

那么在这个数据范围内可以发现由$4$和$7$组成的数**只有$30$个**。

所以我们可以打一个小小的表。

为了防抄袭我的表打的是$2,3$组成的数。

可以看到我的表最后插入了一个极大值，这个原因请自行思考，不再赘述。

有了这个表之后我们可以**维护每个数与最小的比它大的由$4$和$7$组成的数的差，每次区间加用线段树维护，把差值减去$d$**。

线段树**维护一下这个区间的最小值以及最小值出现的次数**，每次询问我们看如果最小值是$0$的话就直接返回最小值出现的次数即可，因为它一定是由$4$和$7$组成的。

**当差值减小到比$0$还小的时候，我们就要对$x$维护下一个小于$x$且里$x$最近的$4,7$ 组成的数的差值**。这个维护的时候暴力维护，重新建树，每个数最多被修改$31$次，所以不会超时。

复杂度$O(31m\log n)$。

代码
```cpp
#include<bits/stdc++.h>
#define eps 1e-7
#define re register
#define N 2001001
#define MAX 2011
#define PI 3.1415927
#define inf 1e18
using namespace std;
typedef long long ll;
typedef double db;
const ll mod=1000000007;
inline void read(re ll &ret)
{
    ret=0;re ll pd=0;re char c=getchar();
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c^48);c=getchar();}
    ret=pd?-ret:ret;
}
ll n,m,a[N],b[N],x,y,tmp;
struct node
{
	ll l,r,mid,val,minn,sum;
}seg[N];
ll num[32]={0,2,3,22,23,32,33,222,223,232,233,322,323,332,333,2222,2223,2232,2233,2322,2323,2332,2333,3222,3223,3232,3233,3322,3323,3332,3333,200001}; 
char s[N];
inline void pushup(re ll pos)
{
	seg[pos].minn=min(seg[pos<<1].minn,seg[pos<<1|1].minn);
	if(seg[pos].minn==seg[pos<<1].minn&&seg[pos].minn==seg[pos<<1|1].minn)
		seg[pos].val=seg[pos<<1].val+seg[pos<<1|1].val;
	else if(seg[pos].minn==seg[pos<<1].minn)
		seg[pos].val=seg[pos<<1].val;
	else
		seg[pos].val=seg[pos<<1|1].val;
	return;
}
inline void build(re ll pos,re ll l,re ll r)
{
	seg[pos].l=l;
	seg[pos].r=r;
	seg[pos].mid=l+r>>1;
	if(l==r)
	{
		seg[pos].val=1;
		for(re int i=1;i<=31;i++)
		{
			seg[pos].minn=num[i]-a[l];
			b[l]=i;
			if(num[i]>=a[l])
				break;
		}
	}
	else
	{
		build(pos<<1,l,seg[pos].mid);
		build(pos<<1|1,seg[pos].mid+1,r);
		pushup(pos);
	}
	return;
}
inline void rebuild(re ll pos)
{
	if(seg[pos].minn>=0)
		return;
	if(seg[pos].l==seg[pos].r)
	{
		a[seg[pos].l]=num[b[seg[pos].l]]-seg[pos].minn;
		for(re int i=1;i<=31;i++)
		{
			seg[pos].minn=num[i]-a[seg[pos].l];
			b[seg[pos].l]=i;
			if(num[i]>=a[seg[pos].l])
				break;
		}
	}
	else
	{
		seg[pos<<1].minn-=seg[pos].sum;
		seg[pos<<1].sum+=seg[pos].sum;
		seg[pos<<1|1].minn-=seg[pos].sum;
		seg[pos<<1|1].sum+=seg[pos].sum;
		seg[pos].sum=0;
		rebuild(pos<<1);
		rebuild(pos<<1|1);
		pushup(pos);
	}
}
inline void add(re ll pos,re ll num)
{
	seg[pos].sum+=num;
	seg[pos].minn-=num;
	if(seg[pos].minn<0)
		rebuild(pos);
	return;
}
inline void pushdown(re ll pos)
{
	add(pos<<1,seg[pos].sum);
	add(pos<<1|1,seg[pos].sum);
	seg[pos].sum=0;
	return;
}
inline void upgrade(re ll pos,re ll l,re ll r,re ll num)
{
	if(seg[pos].l>r||seg[pos].r<l)
		return;
	else if(seg[pos].l>=l&&seg[pos].r<=r)
		return add(pos,num);
	pushdown(pos);
	upgrade(pos<<1,l,r,num);
	upgrade(pos<<1|1,l,r,num);
	pushup(pos);
	return;
}
inline pair<ll,ll> query(re ll pos,re ll l,re ll r)
{
	if(seg[pos].l>=l&&seg[pos].r<=r)
		return make_pair(seg[pos].val,seg[pos].minn);
	else if(seg[pos].l>r||seg[pos].r<l)
		return make_pair(0,inf);
	pushdown(pos);
	re pair<ll,ll> x=query(pos<<1,l,r),y=query(pos<<1|1,l,r);
	re ll ans=0;
	if(x.second==y.second)
		ans+=x.first+y.first;
	else if(x.second>y.second)
		ans+=y.first;
	else if(x.second<y.second)
		ans+=x.first;
	return make_pair(ans,min(x.second,y.second));
}
int main()
{
	read(n);
	read(m);
	for(re int i=1;i<=n;i++)
		read(a[i]);
	build(1,1,n);
	for(re int i=1;i<=m;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='c')
		{
			read(x);
			read(y);
			re pair<ll,ll>temp=query(1,x,y);
			if(!temp.second)
				printf("%lld\n",temp.first);
			else
				puts("0"); 
		}
		else if(s[1]=='a')
		{
			read(x);
			read(y);
			read(tmp);
			upgrade(1,x,y,tmp);
		}
	}
	exit(0);
}

```


---

## 作者：Yuno (赞：2)

此题翻译漏了一个重要条件，每个数在任意时刻不超过1e4  
容易发现1~1e4中只有30个幸运数。  
于是考虑把1~1e4这个区间按每个幸运数的位置分段，  
用线段树维护区间中每个数到离它最近且比它大的幸运数的距离的最小值，及这个最小值的个数。   
每次区间加当成区间减来做。  
若区间减后最小值小于0，则暴力跳段。  
查询时，如果一个区间中距离的最小值为0，则返回这个区间最小值个数，否则这个区间中就没有幸运数。
![](https://cdn.luogu.com.cn/upload/pic/64840.png)
如样例， 可以分成这样的几段。  
此时2、3、4对应得值分别为 2、1、0。  
查询区间1~3，  
距离最小值为0，返回最小值个数1，答案就是1。  
复杂度O(30nlogn)  
~~跑得还没有分块快是怎么回事？~~  
Code：  
```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define N 100007
#define pa pair <int, int>
using namespace std;

int a[N], f[N], cnt, num, root;
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))
    ch = getchar();
    while (isdigit(ch))
    {
        x = (x << 3) + (x << 1) + ch - 48;
        ch = getchar();
    }
    return x;
}

struct node
{
    int l, r, mn, sum, v, tag, f;
}tr[N << 2];

void push_up(int p)
{
    int l = tr[p].l, r = tr[p].r;
    if (tr[l].mn == tr[r].mn)
    {
        tr[p].mn = tr[l].mn;
        tr[p].sum = tr[l].sum + tr[r].sum;
        tr[p].f = min(tr[l].f, tr[r].f);
    }
    if (tr[l].mn < tr[r].mn)
    {
        tr[p].mn = tr[l].mn;
        tr[p].sum = tr[l].sum;
        tr[p].f = tr[l].f;
    }
    if (tr[l].mn > tr[r].mn)
    {
        tr[p].mn = tr[r].mn;
        tr[p].sum = tr[r].sum;	
        tr[p].f = tr[r].f;	
    }
}

inline void build(int &p, int l, int r)
{
    p = ++ num;
    if (l == r)
    {
        int q = lower_bound(f + 1, f + 1 + cnt, a[l]) - f;
        tr[p].sum = 1;
        tr[p].mn = f[q] - a[l];
        tr[p].v = f[q];
        tr[p].f = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(tr[p].l, l, mid);
    build(tr[p].r, mid + 1, r);
    push_up(p);
}

inline void push_down(int p)
{
    if (tr[p].tag)
    {
        int l = tr[p].l, r = tr[p].r;
        tr[l].mn -= tr[p].tag;
        tr[l].tag += tr[p].tag;
        tr[r].mn -= tr[p].tag;
        tr[r].tag += tr[p].tag;
        tr[p].tag = 0;
    }
}

inline pa comp(pa x, pa y)
{
    int st, nd;
    if (x.first > y.first)
    st = y.first, nd = y.second;
    if (x.first == y.first)
    st = x.first, nd = x.second + y.second;
    if (x.first < y.first)
    st = x.first, nd = x.second;
    return make_pair(st, nd);
}

inline void update(int p, int l, int r, int l1, int r1, int v)
{
    if (l1 <= l && r1 >= r)
    {
        tr[p].tag += v;
        tr[p].mn -= v;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(p);
    if (l1 <= mid) update(tr[p].l, l, mid, l1, r1, v);
    if (r1 > mid) update(tr[p].r, mid + 1, r, l1, r1, v);
    push_up(p);
}//修改

inline pa query(int p, int l, int r, int l1, int r1)
{
    if (l1 <= l && r1 >= r)
    {
        pa pp = make_pair(tr[p].mn, tr[p].sum);
        return pp;
    }
    int mid = (l + r) >> 1;
    pa tmp = make_pair(0x3f3f3f3f, 99);
    push_down(p);
    if (l1 <= mid)
    tmp = comp(tmp, query(tr[p].l, l ,mid, l1, r1));
    if (r1 > mid)
    tmp = comp(tmp, query(tr[p].r, mid + 1, r, l1, r1));
    return tmp;
}//查询

inline void change(int p ,int l, int r, int x)
{
    if(l == r)
    {
        int now = tr[p].v - tr[p].mn;
        int pos = lower_bound(f + 1, f + 1 + cnt, now) - f;
        tr[p].v = f[pos];
        tr[p].mn = f[pos] - now;
        return;
    }
    int mid=(l + r) >> 1;
    push_down(p);
    if(x <= mid)
    change(tr[p].l, l, mid, x);
    else
    change(tr[p].r, mid + 1, r, x);
    push_up(p);
}

int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= 10000; i++)
    {
        int x = i;
        bool flag = 1;
        while (x)
        {
            if (x % 10 != 4 && x % 10 != 7)
            {
                flag = 0;
                break;
            }
            x = x / 10;
        }
        if (flag)
        f[++cnt] = i;
    }
    f[++cnt] = 9999999999;
    sort(f + 1, f + 1 + cnt);
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    build(root, 1, n);
    for (int i = 1; i <= m; i++)
    {
        char s[301];
        scanf("%s",s+1);
        if (s[1] == 'a')
        {
            int x = read(), y = read(), w = read();
            update(root, 1, n, x, y, w);
            while (tr[root].mn < 0) change(root, 1, n, tr[root].f);//暴力跳段
        }
        else
        {
            int x = read(), y = read();
            pa ans = query(root, 1, n, x, y);
            if (ans.first == 0)
            printf("%d\n", ans.second);
            else printf("0\n");
        }
    }
    return 0;
 } 
```


---

## 作者：lzyqwq (赞：1)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/p/17829247.html)**

sqrt technology, sqrt faith.



**[洛谷](https://www.luogu.com.cn/problem/CF121E) [CF](https://codeforces.com/problemset/problem/121/E)**

> - 定义一个数为幸运数字，当且仅当其十进制数位中仅有 $4$ 和 $7$ 组成。
>
> - 给出长度为 $n$ 的序列 $p_1\sim p_n$，有 $q$ 次操作，分为两种类型：
>
>     - $\texttt{add }l\texttt{ }r\texttt{ }x$，将 $p_l\sim p_r$ 加上 $x$。
>
>     - $\texttt{count }l\texttt{ }r$，查询当前 $p_l\sim p_r$ 中有多少个幸运数字。
>
> - $n,q\le 10^5$。设 $V$ 为序列 $p$ 的值域，保证**任意时刻 $\boldsymbol{|V|\le 10^4}$**。
>
> - $\text{4.00\,ms\,/\,250.00\,MB}$。

tags：

- $\text{data structures}$

- $\color{red}*2400$

首先，任意时刻 $|V|\le 10^4$ 意味着整个问题只会涉及四位及以下的幸运数字。

考虑计算每一位的幸运数字有多少个，每位可以选 $4$ 或 $7$，可以计算出这个范围内的幸运数字总数 $k=2+2^2+2^3+2^4=30$。

发现 $k$ 很小，肯定有用，考虑先把所有幸运数字存放到一个容器里。因为叫“幸运数字”，所以代码中存放的容器名称使用了 maze 的名字首拼缩写。

考虑序列分块，设块长为 $B$。记 $i$ 所在块为 $bel_i$，第 $i$ 块的范围为 $[bl_i,br_i]$。

对于每个块，维护加标记 $tag_i$。再维护一个数组 $a_i$，其值为**使得 $\boldsymbol{x+tag_{bel_i}}$ 等于当前 $\boldsymbol{p_i}$ 的数 $\boldsymbol{x}$**。简单来说就是任意时刻 $a_i+tag_{bel_i}=p_i$。对于整块再维护桶 $cnt_{i,j}$ 表示块 $i$ 内有多少个位置的 $\boldsymbol{a}$ **值**为 $j$ 。

修改的时候整块标记修改，散块 $a$ 数组修改，维护好 $a_i+tag_{bel_i}=p_i$。

查询的时候，散块暴力遍历判断每个位置的**真实值**是否是幸运数字。整块则枚举 $k$ 个幸运数字 $y$，若当前块 $i$ 内有一个位置 $j$ 满足 $p_j=y$，则 $a_j=y-tag_i$。即查询块内有多少个位置的 $a$ 值等于 $y-tag_i$，贡献为 $cnt_{i,y-tag_i}$。

接下来分析时间复杂度。因为空间复杂度显然为 $\mathcal{O}\left(n+\dfrac{n|V|}{B}\right)$。

> - 单次修改：
>
>    整块 $\mathcal{O}\left(\dfrac{n}{B}\right)$ 个，单个修改的时间复杂度为 $\mathcal{O}(1)$；散块 $\mathcal{O}(1)$ 个，单个修改的时间复杂度为 $\mathcal{O}(B)$。总时间复杂度为 $\mathcal{O}\left(\dfrac{n}{B}+B\right)$。
>
> - 单次查询：
>
>   整块 $\mathcal{O}\left(\dfrac{n}{B}\right)$ 个，单个查询的时间复杂度为 $\mathcal{O}(k)$；散块 $\mathcal{O}(1)$ 个，单个查询的时间复杂度为 $\mathcal{O}(B)$。总时间复杂度为 $\mathcal{O}\left(\dfrac{nk}{B}+B\right)$。

综上，该算法的时间复杂度为 $\mathcal{O}\left(n+q\left(  \dfrac{nk}{B}+B   \right)\right)$。

取 $B=\mathcal{O}\left(\sqrt{nk}\right)$ 时，时间复杂度为 $\mathcal{O}\left(n+q\sqrt{nk}\right)$，空间复杂度为 $\mathcal{O}\left(n+|V|\cdot \sqrt{\dfrac{n}{k}}\right)$。可以接受。

**[提交记录（$\color{limegreen}\bf{Accepted}$ $\bold{780\, ms\,/\,3.46\,MB}$，含代码）](https://codeforces.com/contest/121/submission/232583665)**

---

## 作者：TKXZ133 (赞：1)

[Lucky Array](https://www.luogu.com.cn/problem/CF121E)

### 题目大意

维护一个序列，支持以下操作：

- 区间加一个大于 $0$ 的数。

- 区间查询有多少个数位上只包含 $4$ 或 $7$ 的数。

### 思路分析

看起来很不可做，但考虑到题目给了一个特殊性质：

**保证所有数操作前后都不超过 $10^4$**。

那么如果暴力进行区间加，最坏情况会加 $10^9$ 次，考虑到 $4\text{s}$ 的时限，复杂度是正确的。

区间查询的话，容易发现 $10^4$ 范围内满足条件的数只有 $30$ 个，打一个表出来就行了。

再随便套一个数据结构用来求和就可以了。

时间复杂度为 $O(nV+f(n))$，其中 $f(n)$ 为用于求和的数据结构的时间复杂度。

### 代码

线段树被不知道为什么卡常了，因此这里写的是分块。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=100100;
#define mid ((l+r)>>1)

int num[]={4,7,44,47,77,74,444,447,477,474,744,747,774,777,4444,4447,4474,4477,4744,4747,4774,4777,7444,7447,7474,7477,7744,7747,7774,7777};
//表不要打错了
int n,m,in1,in2,in3,B;
int vis[N],inp[N],sum[N],pos[N],L[N],R[N];

char op[7];

int ask(int l,int r){
    int res=0;
    if(pos[l]==pos[r]){for(int i=in1;i<=in2;i++) res+=vis[inp[i]];return res;}
    for(int i=in1;i<=R[pos[in1]];i++) res+=vis[inp[i]];
    for(int i=pos[in1]+1;i<=pos[in2]-1;i++) res+=sum[i];
    for(int i=L[pos[in2]];i<=in2;i++) res+=vis[inp[i]];
    return res;
}

int main(){
    memset(L,0x3f,sizeof L);
    for(int i=0;i<30;i++) vis[num[i]]=1;
    scanf("%d%d",&n,&m);
    B=sqrt(n);
    for(int i=1;i<=n;i++){
        scanf("%d",&inp[i]);
        pos[i]=i/B+1;
        sum[pos[i]]+=vis[inp[i]];
        L[pos[i]]=min(L[pos[i]],i);
        R[pos[i]]=max(R[pos[i]],i);
    }
    while(m--){
        scanf("%s",op+1);
        if(op[1]=='a'){
            scanf("%d%d%d",&in1,&in2,&in3);
            for(int i=in1;i<=in2;i++){
                sum[pos[i]]-=vis[inp[i]];
                inp[i]+=in3;
                sum[pos[i]]+=vis[inp[i]];
                //对于每个数暴力加
            }
        }
        if(op[1]=='c'){
            scanf("%d%d",&in1,&in2);
            cout<<ask(in1,in2)<<'\n';//区间查询
        }
    }
    return 0;
}
```

---

## 作者：听取MLE声一片 (赞：1)

打表发现范围内幸运数只有 $k=30$ 个，先预处理出来。

因为总值域很小，所以考虑从这里入手。

考虑分块，设块长为 $B$，每个块都开一个值域数组，数组下标为 $x$ 的数表示块内元素全部加 $x$ 的幸运数个数。这个如果计算出来了那么查询就是好做的。

肯定不能直接遍历值域。发现可以枚举幸运数 $y$，然后在枚举块内元素 $z$。如果 $z\leq y$ 那么就说明可以往上加数来成为这个幸运数，直接把数组下标为 $y-z$ 的数加一即可。

重构块的时候要把之前的数组清空，直接清是不行的。考虑在加数的时候把加的位置给存起来，等需要的时候直接对应位置清空。

而这样做完了之后，整块修改就直接增加标记，查询就加上块的值域数组下标为标记的数即可。

散块直接暴力就行，剩下的就是分块的基本操作了。

对于每次修改，修改整块的时间复杂度为 $O(\frac{n}{B})$，暴力做散块的时间复杂度为 $O(Bk)$。平衡一下，$B=\sqrt {\frac{n}{k}}$ 时最优。总时间复杂度即为 $O(n\sqrt{nk})$，可以通过本题。

我是取 $B=60$，代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e5+10;
const int M=1e4;
const int B=60;
const int T=1710;
const int K=40;
int n,m,a[N];
int L[N],R[N],pos[N],tag[N],sum[T][M];
int b[K],vis[N],cnt;
vector<int>e[T];
int check(int x){
	while(x){
		int y=x%10;
		if(y!=4&&y!=7)
			return 0;
		x/=10;
	}
	return 1;
} 
void init(){
	for(int i=1;i<M;i++)
		if(check(i)){
			b[++cnt]=i;
			vis[i]=1;
		}
}
void push(int p){
	for(int u:e[p])
		sum[p][u]=0;
	e[p].clear();
	int l=L[p],r=R[p],minn=M;
	for(int i=l;i<=r;i++){
		a[i]+=tag[p];
		minn=min(minn,a[i]);
	}
	for(int k=1;k<=cnt;k++){
		int x=b[k];
		if(minn>x)continue;
		for(int i=l;i<=r;i++){
			if(a[i]>x)continue;
			sum[p][x-a[i]]++;
			e[p].push_back(x-a[i]);
		}
	}
	tag[p]=0;
}
void update(int l,int r,int x){
	int p=pos[l],q=pos[r];
	if(p==q){
		for(int i=l;i<=r;i++)
			a[i]+=x;
		push(p);
		return;
	}
	for(int i=p+1;i<=q-1;i++)
		tag[i]+=x;
	for(int i=l;i<=R[p];i++)
		a[i]+=x;
	push(p);
	for(int i=L[q];i<=r;i++)
		a[i]+=x;
	push(q);
}
int query(int l,int r){
	int p=pos[l],q=pos[r],res=0;
	if(p==q){
		for(int i=l;i<=r;i++)
			res+=vis[a[i]+tag[p]];
		return res;
	}
	for(int i=p+1;i<=q-1;i++)
		res+=sum[i][tag[i]];
	for(int i=l;i<=R[p];i++)
		res+=vis[a[i]+tag[p]];
	for(int i=L[q];i<=r;i++)
		res+=vis[a[i]+tag[q]];
	return res;
}
int main()
{
	init();
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	int t=n/B;
	for(int i=1;i<=t;i++){
		L[i]=R[i-1]+1;
		R[i]=R[i-1]+B;
	}
	if(R[t]<n){
		t++;
		L[t]=R[t-1]+1;
		R[t]=n;
	}
	for(int i=1;i<=t;i++){
		for(int j=L[i];j<=R[i];j++)
			pos[j]=i;
		push(i);
	} 
	while(m--){
		char opt[6];
		scanf("%s",opt);
		if(opt[0]=='a'){
			int l=read(),r=read(),x=read();
			update(l,r,x);
		}
		if(opt[0]=='c'){
			int l=read(),r=read();
			printf("%d",query(l,r));
			putchar('\n');
		}
	}
	return 0;
}

```

---

## 作者：ForgotDream_CHN (赞：1)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17472704.html)

## 思路

正解是线段树？然而我太菜了不会啊。。。

题目的数据范围是 $10 ^ 5$，于是我们可以从分块的角度去思考这个问题。

打个表可以发现在题目给定的值域（$10 ^ 4$）内满足条件的数一共只有三十个，于是这道题就简单了。先把数列分个块，然后对于每一块，维护一个区间加的标记和一个值域的标记，表示该块内每个数字的个数。对于区间加的操作，对散块就直接暴力累加，对整块就维护标记。对于查询的操作，对散块就暴力的验证其是否符合要求，而对整块就查询块内这三十个数的个数即可，还有就是记得查询时带上区间加的标记。

时间复杂度为 $O(n \sqrt n)$，空间复杂度的话，由于对每一块都开了一个值域数组，记值域大小为 $D$，所以是 $O(D \sqrt n)$。

## 代码

```cpp
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::unordered_set<int> encode;
  std::vector<int> decode;
  [&]() {
    for (int i = 1; i <= 10000; i++) {
      auto check = [](int num) -> bool {
        while (num) {
          if (num % 10 != 4 && num % 10 != 7) { return false; }
          num /= 10;
        }
        return true;
      };
      if (check(i)) { encode.insert(i), decode.push_back(i); }
    }
  }();

  int n, m;
  std::cin >> n >> m;

  int blk = std::sqrt(n + 0.5), cnt = n / blk + !!(n % blk);
  std::vector<int> st(cnt), ed(cnt), bln(n);
  for (int i = 0; i < cnt; i++) { st[i] = i * blk, ed[i] = (i + 1) * blk - 1; }
  ed[cnt - 1] = n - 1;
  for (int i = 0; i < n; i++) { bln[i] = i / blk; }

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i]; }

  std::vector<std::vector<int>> f(cnt, std::vector<int>(1e4 + 1));
  std::vector<int> add(cnt);
  for (int i = 0; i < n; i++) { f[bln[i]][a[i]]++; }

  while (m--) {
    std::string opt;
    int l, r;
    std::cin >> opt >> l >> r;
    l--, r--;
    if (opt == "add") {
      int val;
      std::cin >> val;
      if (bln[l] == bln[r]) {
        for (int i = l; i <= r; i++) {
          f[bln[l]][a[i]]--, a[i] += val, f[bln[l]][a[i]]++;
        }
      } else {
        for (int i = l; i <= ed[bln[l]]; i++) {
          f[bln[l]][a[i]]--, a[i] += val, f[bln[l]][a[i]]++;
        }
        for (int i = st[bln[r]]; i <= r; i++) {
          f[bln[r]][a[i]]--, a[i] += val, f[bln[r]][a[i]]++;
        }
        for (int i = bln[l] + 1; i < bln[r]; i++) { add[i] += val; }
      }
    } else {
      int ans = 0;
      if (bln[l] == bln[r]) {
        for (int i = l; i <= r; i++) {
          if (encode.count(a[i] + add[bln[l]])) { ans++; }
        }
      } else {
        for (int i = l; i <= ed[bln[l]]; i++) {
          if (encode.count(a[i] + add[bln[l]])) { ans++; }
        }
        for (int i = st[bln[r]]; i <= r; i++) {
          if (encode.count(a[i] + add[bln[r]])) { ans++; }
        }
        for (int i = bln[l] + 1; i < bln[r]; i++) {
          for (auto j : decode) { 
            if (j < add[i]) { continue; }
            ans += f[i][j - add[i]]; 
          }
        }
      }
      std::cout << ans << "\n";
    }
  }

  return 0;
}
```

---

## 作者：__stick (赞：1)

## 题意

维护数列，支持询问区间加，区间询问仅由 $4,7$ 组成数的个数，**任何时刻每个数大小不会超过 $10^4$**。

## 思路

由于每个数有上限，显然每个数最多被加 $10^4$ 次，总次数就是 $10^9$ 级别，所以我们预处理每个数是否合法，对于修改就暴力维护当前数对答案的贡献。

这里修改与询问次数不同级，使用根号做到 $O(1)$ 加法，$O(\sqrt{n})$ 区间询问，总复杂度就是比较合理的 $O(nV+n\sqrt{n})$ 。

## code
```cpp
int n;
inline int get(int x){return (x-1)/B+1;}
inline int L(int x){return (x-1)*B+1;}
inline int R(int x){return min(n,x*B);}
bool is[MAXN];
int sum[MAXN],c[MAXN];
int a[MAXN];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int m;cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    const int N=1e4;
    for(int i=1;i<=N;i++)
    {
        string s=to_string(i);
        if(count(all(s),'4')+count(all(s),'7')==s.size())is[i]=1;
    }
    for(int i=1;i<=n;i++)if(is[a[i]])sum[get(i)]++,c[i]++;
    while(m--)
    {
        string s;cin>>s;
        int l,r;cin>>l>>r;
        if(s=="add")
        {
            int d;cin>>d;
            for(int i=l;i<=r;i++)
            {
                if(is[a[i]])sum[get(i)]--,c[i]--;
                if(is[a[i]+=d])sum[get(i)]++,c[i]++;
            }
        }
        else
        {
            int ans=0;
            int p=get(l),q=get(r);
            if(p==q)
            {
                for(int i=l;i<=r;i++)ans+=c[i];
                cout<<ans<<'\n';
                continue;
            }
            for(int i=l;i<=R(p);i++)ans+=c[i];
            for(int i=L(q);i<=r;i++)ans+=c[i];
            for(int i=p+1;i<q;i++)ans+=sum[i];
            cout<<ans<<'\n';
        }
    }
	return 0;
}
```


---

## 作者：RainFestival (赞：1)

此题考数据结构，我选择分块

题目要求的数并不多，达标（打表）就行啦

其中pp既是块数，也是每块大小  偷懒

也就是说，我们每次统计每一块中的lucky number的个数，可以打标记





下面代码：

```pascal
var
  b:array[0..10005] of boolean;
  pp,n,m,x,y,v,i,j,s,x1,y1,k,ans:longint;
  a,c,l,ss,xx:array[0..1000005] of longint;
  s1:array[0..1005,-20005..10005] of longint;
  ch:char;
begin
  readln(n,m);
  pp:=trunc(sqrt(n))+1;
  for i:=1 to n do
    if (i-1) mod pp=0 then l[i]:=l[i-1]+1
                      else l[i]:=l[i-1];
  b[4]:=true;b[7]:=true;
  b[44]:=true;b[47]:=true;b[74]:=true;b[77]:=true;
  b[444]:=true;b[447]:=true;b[474]:=true;b[477]:=true;
  b[744]:=true;b[747]:=true;b[774]:=true;b[777]:=true;
  b[4444]:=true;b[4447]:=true;b[4474]:=true;b[4477]:=true;
  b[4744]:=true;b[4747]:=true;b[4774]:=true;b[4777]:=true;
  b[7444]:=true;b[7447]:=true;b[7474]:=true;b[7477]:=true;
  b[7744]:=true;b[7747]:=true;b[7774]:=true;b[7777]:=true;
  xx[1]:=4;xx[2]:=7;xx[3]:=44;xx[4]:=47;xx[5]:=74;
  xx[6]:=77;xx[7]:=444;xx[8]:=447;xx[9]:=474;
  xx[10]:=477;xx[11]:=744;xx[12]:=747;xx[13]:=774;
  xx[14]:=777;xx[15]:=4444;xx[16]:=4447;xx[17]:=4474;
  xx[18]:=4477;xx[19]:=4744;xx[20]:=4747;
  xx[21]:=4774;xx[22]:=4777;xx[23]:=7444;
  xx[24]:=7447;xx[25]:=7474;xx[26]:=7477;
  xx[27]:=7744;xx[28]:=7747;xx[29]:=7774;
  xx[30]:=7777;
  for i:=1 to n do
    read(a[i]);
  readln;
  //for i:=1 to n do
    //if b[a[i]+c[l[i]]] then inc(ss[l[i]]);
  for i:=1 to pp do
    for j:=1 to pp do
      begin
        if (i-1)*pp+j>n then break;
        for k:=1 to 30 do
          inc(s1[i][xx[k]-a[(i-1)*pp+j]]);
      end;
  for i:=1 to m do
    begin
      //for j:=1 to pp do
        //begin
          //for k:=1 to 10 do
            //write(s1[j][k],' ');
          //writeln;
        //end;
          //for j:=1 to n do
            //writeln(a[j]+c[l[j]],' ');
      //writeln;
      //writeln(i);
      read(ch);
      if ch='c' then
        begin
          while ch<>' ' do
            read(ch);
          readln(x,y);
          //writeln(x,' ',y);
          //s:=0;
          ans:=0;
          if y-x<pp*2 then
            begin
              for j:=x to y do
                if b[a[j]+c[l[j]]] then
                  begin
                    //inc(s);
                    inc(ans);
                  end;
              //writeln(s);
              writeln(ans);
              continue;
            end;
          x1:=l[x];
          y1:=l[y];
          inc(x1);
          dec(y1);
          for j:=x1 to y1 do
            begin
              //s:=s+ss[j];
              ans:=ans+s1[j][c[j]];
            end;
          for j:=x to l[x]*pp do
            if b[a[j]+c[l[j]]] then
              begin
                //inc(s);
                inc(ans);
              end;
          for j:=(l[y]-1)*pp+1 to y do
            if b[a[j]+c[l[j]]] then
              begin
                //inc(s);
                inc(ans);
              end;
          //writeln(s);
          writeln(ans);
        end;
      if ch='a' then
        begin
          read(ch);
          while ch<>' ' do
            read(ch);
          readln(x,y,v);
          //writeln(x,' ',y,' ',v);
          if y-x<pp*2 then
            begin
              for j:=x to y do
                begin
                  //if b[a[j]+c[l[j]]] then dec(ss[l[j]]);
                  if j>n then break;
                  for k:=1 to 30 do
                    begin
                      dec(s1[l[j]][xx[k]-a[j]]);
                      inc(s1[l[j]][xx[k]-(a[j]+v)]);
                    end;
                  a[j]:=a[j]+v;
                  //if b[a[j]+c[l[j]]] then inc(ss[l[j]]);
                end;
              continue;
            end;
          x1:=l[x];
          y1:=l[y];
          inc(x1);
          dec(y1);
          for j:=x1 to y1 do
            begin
              c[j]:=c[j]+v;
              //ss[j]:=0;
            end;
          //for j:=(x1-1)*pp+1 to y1*pp do
            //if b[a[j]+c[l[j]]] then inc(ss[l[j]]);
          for j:=x to l[x]*pp do
            begin
              if j>n then break;
              for k:=1 to 30 do
                begin
                  dec(s1[l[j]][xx[k]-a[j]]);
                  inc(s1[l[j]][xx[k]-(a[j]+v)]);
                end;
              //if b[a[j]+c[l[j]]] then dec(ss[l[j]]);
              a[j]:=a[j]+v;
              //if b[a[j]+c[l[j]]] then inc(ss[l[j]]);
            end;
          for j:=(l[y]-1)*pp+1 to y do
            begin
              if j>n then break;
              for k:=1 to 30 do
                begin
                  dec(s1[l[j]][xx[k]-a[j]]);
                  inc(s1[l[j]][xx[k]-(a[j]+v)]);
                end;
              //if b[a[j]+c[l[j]]] then dec(ss[l[j]]);
              a[j]:=a[j]+v;
              //if b[a[j]+c[l[j]]] then inc(ss[l[j]]);

            end;
        end;

      //writeln('==');
      //for j:=1 to n do
        //writeln(a[j]+c[l[j]]);
      //writeln;
      //for j:=1 to n do

        //writeln(ss[i]);
      //writeln('==');
    end;
  //for i:=1 to n do
    //writeln(a[i]+c[l[i]]);
end.
```
时间73746ms,空间133836KB，代码长度4.77KB 我太蒟啦

谢谢大佬巨佬神犇神牛们的观赏


---

## 作者：HCY55 (赞：1)

Hello!Every body,我想你们此时都在为一道难题而堪忧吧！没关系，相信我，让我来上交一道关于Lucky Array的代码吧！ 其实此题只是一道暴力题，但许多人都会发现，用暴力的方法是会TLE一个点，所以我们要采用一些简单的思维。 下面我为大家介绍一种算法叫做分块，分块是什么？其实就是将数据分成一段有一段的线段树，有搜索去搜，就可以。 废话不多说，下面请看我的代码：
```cpp
#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
int b[100005];
int n,m,l,r,d;
int a[100001],f[100005];
string s;
void add(int i,int j) {
	while(i<=n) {
		b[i]+=j;
		i+=(-i)&i;
	}
}
int count(int i) {
	int ans=0;
	while(i>0) {
		ans+=b[i];
		i-=(-i)&i;
	}
	return ans;
}
int main() {
	scanf("%d%d",&n,&m);
	f[4]=1;
	f[7]=1;
	f[44]=1;
	f[47]=1;
	f[74]=1;
	f[77]=1;
	f[444]=1;
	f[447]=1;
	f[474]=1;
	f[477]=1;
	f[744]=1;
	f[747]=1;
	f[774]=1;
	f[777]=1;
	f[4444]=1;
	f[4447]=1;
	f[4474]=1;
	f[4477]=1;
	f[4744]=1;
	f[4747]=1;
	f[4774]=1;
	f[4777]=1;
	f[7444]=1;
	f[7447]=1;
	f[7477]=1;
	f[7474]=1;
	f[7744]=1;
	f[7747]=1;
	f[7774]=1;
	f[7777]=1;
	for(int i=1; i<=n; i++) {
		scanf("%d",&a[i]);
		if(f[a[i]]) {
			add(i,1);
		}
	}
	char c[10];
	int l,r,val;
	for(int j=1; j<=m; j++) {
		scanf("\n%s",c);
		if(c[0]=='c') {
			scanf("%d%d",&l,&r);
			printf("%d\n",count(r)-count(l-1));
		} else {
			scanf("%d%d%d",&l,&r,&val);
			for(int i=l; i<=r; i++) {
				if(f[a[i]]) {
					add(i,-1);
				}
				a[i]+=val;
				if(f[a[i]]) {
					add(i,1);
				}
			}
		}
	}
	return 0;
}
```
这就是我的代码，虽然没有用分块，但是足够了为各位解答，这是一道暴力代码！

---

## 作者：LIUYC_C (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF121E)。

## 大体思路：

首先看到这题，很明显是一道数据结构，再一看，很明显的线段树，维护两个操作，区间查询，区间修改，可以维护两个值，一个是加上一个数后的本身的值，一个是是否满足是幸运数字，怎么判断幸运数字呢，当然可以打表了，暴力打表之后欣喜的发现只有 30 个幸运数，具体也很好实现。

但是，有没有更简单的做法呢，当然是树状数组啦。

但是要区间加怎么办，好办，暴力枚举要加的区间就好了。

#### Q：

**为什么这样的复杂度是正确的？**

#### A:

观察题面，不难得到一个性质。“保证所有数操作前后都不超过 $1\times10^4$。“ 

这就意味着一个很重要的性质，每个数最多就只会被加 $1\times10^4$ 次，也就是说我们的 add 操作在最坏情况下最多只会做 $1\times10^4$ 次，就算每次给整个区间的值加，也只会达到 $1\times10^9$ 的级别，在四秒的时限下，是可以跑过的，至于查询操作，则是 $n\log n$ 级别，忽略不计了，又如循环内的 add 函数查找，是 $\log30$ 级别，可以忽略不计，常数大小。 

（注意，我这里把加小区间的时间忽略了，并且，add 操作可能会进行更多次，但是这也就意味着枚举的区间变小了，整体复杂度均摊下来，最坏 $1\times10^9$ 的级别。）

因此，这里用树状数组是可以很完美的冲过去的，并不存在什么数据水。

## 代码实现：

~~自认为马蜂刻毒。~~

```	cpp
#include <bits/stdc++.h>
using namespace std;
const int N=101010;
int n,m;

int check[100]={0,4,7,44,47,74,77,444,447,474,477,744,747,774,777,4444,4447,4474,4477,4744,4747,4774,4777,7444,7447,7474,7477,7744,7747,7774,7777};
int check2[N];

int tr[N];
int sum[N];
int a[N];
//常规
int lobit(int x){
  return x&-x;
}

int query(int x){
  int res=0;
  while(x){
    res+=tr[x];
    x-=lobit(x);
  }
  return res;
}

void update(int x,int c){
    while(x<=n){
      tr[x]+=c;
      x+=lobit(x);
    }
}
//常规

int main(){
  ios::sync_with_stdio(false);
    cin>>n>>m;

    for(int i=1;i<=30;i++){
      check2[check[i]]=true;
    }//预处理打表数组
    

    for(int i=1;i<=n;i++){
      cin>>a[i];
      if(check2[a[i]]){
        update(i,1);
      }
    }//如果是幸运数，就加上。
    
    for(int i=1;i<=m;i++){
      string op;
      cin>>op;
      if(op=="count"){
        int l,r;
        cin>>l>>r;
        cout<<query(r)-query(l-1)<<endl;//直接求区间的前缀和之差就好了
      }
      else{
        int l,r,d;
        cin>>l>>r>>d;
        for(int i=l;i<=r;i++){
          int x=a[i]+d;
          if(check2[a[i]]){//之前有的消去，加上一个数后原数不一定是幸运数
            update(i,-1);
          }
          a[i]+=d;
          if(check2[x]){//是就加上
            update(i,1);  
          }
        }
      }
    }
    return 0;
}
    
 ```

---

## 作者：gyyyyx (赞：0)

我恨分块！

首先说明题目中没有翻译一点：

none of which exceeds $10^4$—those are the array numbers.

意思大概是，无论如何操作，数组中元素都不会超过 $10^4$。

（这么重要的条件竟然没有翻译！）

并且幸运数字只包含 $4$ 和 $7$，如果元素不超过 $10^4$，说明出现的幸运数字也不会超过 $10^4$，简单算一算就知道只有 $30$ 个数。

我们可以先把这 $30$ 个数列出来，存入数组 $S$。

询问的时候，我们就可以一个一个枚举 $S_t$，然后就是要找出 $[l,r]$ 中 $S_t$ 出现的次数。

值域不大，可以用桶。我用的是分块套桶，$cnt_{i,j}$ 记录第 $i$ 个块中有多少个 $j$。

修改：中间完整块打上永久化标记 $tag$，头尾不完整块暴力修改，时间 $O(n\sqrt{n})$。

询问：中间完整块直接用桶，因为有标记的原因，因此第 $i$ 块中 $S_t$ 出现的次数就是 $cnt_{i,S_t-tag_i}$。头尾不完整块暴力查询。

最后提醒一句：用分块套桶时间有点勉强，尽量优化时间复杂度。

代码：

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int S[30]={4,7,44,47,74,77,444,447,474,477,744,747,774,777,4444,4447,4474,4477,4744,4747,4774,4777,7444,7447,7474,7477,7744,7747,7774,7777};
int OK[10005];
int n,m,block,tot,a[N],L[320],R[320],blng[N];
int cnt[320][10005],tag[320];
inline void Update(int l,int r,int d){
    int x(blng[l]),y(blng[r]);
    for(int i(l);i<=min(R[x],r);++i){
        --cnt[x][a[i]];
        a[i]+=d;
        ++cnt[x][a[i]];
    }
    if(x^y){
        for(int i(x+1);i<y;++i) tag[i]+=d;
        for(int i(L[y]);i<=r;++i){
            --cnt[y][a[i]];
            a[i]+=d;
            ++cnt[y][a[i]];
        }
    }
}
inline int Query(int l,int r){
    int x(blng[l]),y(blng[r]),res(0);
    for(int i(l);i<=min(R[x],r);++i) res+=OK[a[i]+tag[x]];
    if(x^y){
        for(int i(x+1);i<y;++i)
            for(int t(29);t>=0;--t){
                if(S[t]<=tag[i]) break;
                res+=cnt[i][S[t]-tag[i]];
            }
        for(int i(L[y]);i<=r;++i) res+=OK[a[i]+tag[y]];
    }
    return res;
}
int main(){
    for(int t(0);t<30;++t) OK[S[t]]=1;
    scanf("%d%d",&n,&m);
    for(int i(1);i<=n;++i) scanf("%d",&a[i]);
    block=sqrt(n);tot=(n-1)/block+1;
    for(int i(1);i<=tot;++i){
        L[i]=R[i-1]+1;R[i]=min(R[i-1]+block,n);
        for(int j(L[i]);j<=R[i];++j) blng[j]=i,++cnt[i][a[j]];
    }
    while(m--){
        string op;cin>>op;
        int l,r,d;
        if(op=="add"){
            scanf("%d%d%d",&l,&r,&d);
            Update(l,r,d);
        }
        else{
            scanf("%d%d",&l,&r);
            printf("%d\n",Query(l,r));
        }
    }
    return 0;
}
```

撒花撒花~

---

## 作者：happybob (赞：0)

## 题意

给定序列 $a$，定义幸运数为各位数字只含有 $4, 7$ 的数字，例如 $4474$ 是幸运数，而 $4177$ 则不是。现在有 $m$ 次操作，每次可能是将 $a_l, a_{l+1}, \cdots, a_r$ 全部加上 $d$，或者询问 $a_l, a_{l+1}, \cdots, a_r$ 中有几个幸运数。

## 解法

考虑可以分块解决。

但是分块的难点在于操作 $1$，也就是区间加法。

显然如果我们暴力对 $a_l, a_{l+1}, \cdots, a_r$ 全部暴力加上 $d$ 并且更新块的信息，复杂度是 $O(n)$ 的，那么极限复杂度 $O(n \cdot m)$，显然无法通过。

那么我们考虑对所有整块都记录一个 $plus_i$ 表示这个块曾经被加上了 $plus_i$，类似线段树上的懒标记。然后每一个快不再记录幸运数数量，而是对于每个块 $f_{i,j}$ 记录的是块 $i$ 中 $j$ 出现次数，幸运数预处理打表即可。

代码：

```cpp
// 省略火车头
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

constexpr int N = 1e5 + 5, M = 705, Q = 1e4 + 5;
int a[N], len;
int plusb[N];
int f[M][Q];

inline int get(register const int& x)
{
	return (x - 1) / len;
}

inline int lplace(register const int& x)
{
	return x * len + 1;
}

inline int rplace(register const int& x)
{
	return lplace(x + 1) - 1;
}

int p[] = { 4, 7, 44, 47, 74, 77, 444, 447, 474, 477, 744, 747, 774, 777, 4444, 4447, 4474, 4477, 4744, 4747, 4774, 4777, 7444, 7447, 7474, 7477, 7744, 7747, 7774, 7777 };
bool flag[N];

int main()
{
	register int n, m;
	scanf("%d%d", &n, &m);
	len = sqrt(n);
	for (register int i(0); i < 30; i = -~i) flag[p[i]] = true;
	for (register int i(1); i <= n; i = -~i) scanf("%d", &a[i]);
	for (register int i(0); i <= len; i = -~i)
	{
		register int lp(lplace(i)), rp(rplace(i));
		for (register int j(lp); j <= rp; j = -~j)
		{
			f[i][a[j]]++;
		}
	}
	while (m--)
	{
		string ch;
		cin >> ch;
		if (ch[0] == 'a')
		{
			register int l, r, d;
			scanf("%d%d%d", &l, &r, &d);
			register int ls(get(l)), rs(get(r));
			if (ls == rs)
			{
				for (register int i(l); i <= r; i = -~i)
				{
					f[get(i)][a[i]]--;
					a[i] += d;
					f[get(i)][a[i]]++;
				}
			}
			else
			{
				register int lp = lplace(ls + 1), rp = rplace(rs - 1);
				for (register int i(l); i < lp; i = -~i)
				{
					f[get(i)][a[i]]--;
					a[i] += d;
					f[get(i)][a[i]]++;
				}
				for (register int i(rp + 1); i <= r; i = -~i)
				{
					f[get(i)][a[i]]--;
					a[i] += d;
					f[get(i)][a[i]]++;
				}
				register int nl(get(lp)), nr(get(rp));
				for (register int i(nl); i <= nr; i++)
				{
					plusb[i] += d;
				}
			}
		}
		else
		{
			register int sum = 0, l, r;
			scanf("%d%d", &l, &r);
			register int ls(get(l)), rs(get(r));
			if (ls == rs)
			{
				for (register int i(l); i <= r; i = -~i)
				{
					sum += flag[a[i] + plusb[get(i)]];
				}
			}
			else
			{
				register int lp = lplace(ls + 1), rp = rplace(rs - 1);
				for (register int i(l); i < lp; i = -~i) sum += flag[a[i] + plusb[get(i)]];
				for (register int i(rp + 1); i <= r; i = -~i) sum += flag[a[i] + plusb[get(i)]];
				register int nl(get(lp)), nr(get(rp));
				for (register int i(nl); i <= nr; i = -~i)
				{
					for (register int j(0); j < 30; j = -~j)
					{
						if (plusb[i] > p[j]) continue;
						sum += f[i][p[j] - plusb[i]];
					}
				}
			}
			printf("%d\n", sum);
		}
	}
	return 0;
}
```

限时 $4$ 秒，我的跑了 $3962$ 毫秒，如果把火车头删了的话那就可能要超时。

[AC 记录。](https://codeforces.com/problemset/submission/121/148986988)


---

## 作者：Daniel_7216 (赞：0)

题意概要：要求统计一段区间内的“幸运数字”个数，并且区间支持加减。

由于幸运数字只能由两种数字构成，且操作中任何数字不超过 $10^4$，所以，凭借着理科人的直觉可以知道，幸运数字的个数是非常有限的。于是通过打表，我们提前得出了那三十个幸运数字。

可以看出这些数字的个数非常少，几乎是常数级别的，所以每次查询就分解成了：给定一段区间，求出这个区间中第一个幸运数字、第二个幸运数字……第三十个幸运数字出现的次数的总和。

我们可以通过分块来实现。这道题就是单纯的区间加和区间查询操作，因此每个块的大小可以用传统的 $\sqrt{n}$。

显然，依据“整块维护，散块暴力”的原则，我们在给一个散块整体加某一个数时应直接给每个数都加上，而给整块加的时候则应该用一个数组标记这个块整体要加上多少。此外，每个块应该都需要一个数组统计每个数字出现次数。

进行查询的时候，散块直接一个个判断是否为幸运数字（要提前用一个布尔数组存下来每个数是或不是幸运数字而不是在查询时一个个暴力判断！！！），对于整块，则计算每个幸运数字在该块中出现次数，最后把这些数字相加即为该次查询答案。复杂度是 $O(n\sqrt{n})$，再乘三十的常数，复杂度可以接受，第七十个点是全部查询且所有数都是幸运数字的卡常点，注意处理散块查询时的优化问题。

好了上代码：
```cpp
#include <cstdio>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;
int lucky_num[35] = {0, 4, 7, 44, 47, 74, 77, 444, 447, 474, 477, 744, 747, 774, 777, 4444, 4447, 4474, 4477, 4744, 4747, 4774, 4777, 7444, 7447, 7474, 7477, 7744, 7747, 7774, 7777};
bool check(int x){
	while (x){
		if (x % 10 != 4 && x % 10 != 7) return false;
		x = (x - x % 10) / 10;
	}
	return true;
}
void shengchen(){ 
	int _count = 0;
	printf("int lucky_num[35] = {");
	for (int i = 1; i <= 10000; i++){
		if (check(i)) printf("%d, ", i);
		
	}
	printf("};");
}
int n, m, len, sum, bl_l, bl_r;
int belong[100001], a[100001], b[100001];
int cnt[401][10001], L[401], R[401], add[401];
char opt[10];
bool is_lucky[10001]; 
void _plus(int l, int r, int v){
	bl_l = belong[l];
	bl_r = belong[r];
	if (bl_l == bl_r){
		for (int i = l; i <= r; i++){
			cnt[bl_l][b[i]]--;
			b[i] += v;
			cnt[bl_l][b[i]]++;
		}
		return;
	}
	for (int i = l; i <= R[bl_l]; i++){
		cnt[bl_l][b[i]]--;
		b[i] += v;
		cnt[bl_l][b[i]]++;
	}
	for (int i = bl_l + 1; i <= bl_r - 1; i++){
		add[i] += v;
	}
	for (int i = L[bl_r]; i <= r; i++){
		cnt[bl_r][b[i]]--;
		b[i] += v;
		cnt[bl_r][b[i]]++;
	}
}
int count(int idx, int l, int r){
	bl_l = belong[l];
	bl_r = belong[r];
	int l_num = lucky_num[idx];
	int _count = 0;
	if (bl_l == bl_r){
		for (int i = l; i <= r; i++){
			if (b[i] + add[bl_l] == l_num) _count++;
		}
		return _count;
	}
	for (int i = bl_l + 1; i <= bl_r - 1; i++){
		if (l_num >= add[i]) _count += cnt[i][l_num - add[i]];
	}
	return _count;
}
void init(){
	len = sqrt(n);
	sum = len;
	for (int i = 1; i <= sum; i++){
		L[i] = R[i - 1] + 1;
		R[i] = L[i] + len - 1;
		for (int j = L[i]; j <= R[i]; j++){
			belong[j] = i;
			cnt[i][a[j]]++;
		}
	}
	if (R[sum] < n){
		sum++;
		L[sum] = R[sum - 1] + 1;
		R[sum] = n;
		for (int i = R[sum - 1] + 1; i <= n; i++){
			belong[i] = sum;
			cnt[sum][a[i]]++;
		}
	} 
}
int cnt_luck(int l, int r){
	int ans = 0;
	for (int i = 1; i <= 30; i++){
		ans += count(i, l, r);
	}
	if (belong[l] != belong[r]){
		for (int i = l; i <= R[belong[l]]; i++){
			if (is_lucky[b[i] + add[belong[l]]]) ans++;
		}
		for (int i = L[belong[r]]; i <= r; i++){
			if (is_lucky[b[i] + add[belong[r]]]) ans++;
		}	
	}
	return ans;
}
int main(){
	for (int i = 1; i <= 30; i++){
		is_lucky[lucky_num[i]] = true;
	}
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	init();
	int l, r, d;
	while (m--){
		scanf("%s%d%d", opt, &l, &r);
		if (opt[0] == 'a'){
			scanf("%d", &d);
			_plus(l, r, d);
		}else{
			printf("%d\n", cnt_luck(l, r));
		}
	}
	return 0;
} 
```

---

## 作者：DPair (赞：0)

大家好，我非常喜欢暴力数据结构，所以我用分块过了这道题。

而且是 C++ 版本的，请放心食用。

## 【思路】

首先题目中有一个没翻译出来的条件：保证任何时候数列中的元素不超过 $10^4$。

会做了的可以自行离开了。

什么？你还不会做？那就接着看下去好了。

不难发现此时可能的幸运数个数其实只有 $2^4+2^3+2^2+2^1=30$ 个。

那么我们暴力判断这 $30$ 个数出现次数即可。

这个显然可以用分块维护。

这里不多赘述分块这个东西了，只讲怎么维护。

首先，对于每一个整块记录区间内每一个数出现的次数。

那么如何维护这个次数呢？

显然在散块上加的时候可以直接暴力更新。

然后整块加和的时候采用打标记的方法即可。

也就是记录 **“本区间实际上被加了多少”** 。然而这个是没有在数组中体现出来的。

最后查询的时候散块直接暴力扫，整块利用每一个数出现的次数和打好的标记对于每一个幸运数 **分别计算** 出现次数即可。

复杂度是 $O(n\sqrt n)$ 的，乘一个 $30$ 的常数（应该是这么表述没错吧）。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() printf("I am a cheater!I AK IOI!%c", 10)
template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
inline char next_char(){
    char ch = getchar();
    while(ch == 9 || ch == 10 || ch == 32) ch = getchar();
    return ch;
}
template <typename T>
inline T mn(T x, T y) {return x < y ? x : y;}
template <typename T>
inline T mx(T x, T y) {return x > y ? x : y;}
template <typename T>
inline void chmin(T &x, T y) {(x > y) && (x = y);}
template <typename T>
inline void chmax(T &x, T y) {(x < y) && (x = y);}
#define MAXN 100005
int n, m;
const int block = 405;
inline int lst(int x){return mn(x * block, n);}
inline int fst(int x){return lst(x - 1) + 1;}
inline int idb(int x){return (x - 1) / block + 1;}
inline bool LST(int x){return x == lst(idb(x));}

int a[MAXN], cnt[(MAXN / block) + 5][10005], tag[(MAXN / block) + 5];
int lucky[35], tt;
bool b[100005];
inline void init(){
    for (register int i = 1;i <= 10000;i ++){
        bool ck = 1;int tmp = i, num;
        while(tmp){
            num = tmp % 10;
            if(num != 4 && num != 7){
                ck = 0;
                break;
            }
            tmp /= 10;
        }
        if(ck) lucky[++ tt] = i, b[i] = 1;
    }
}

int main(){
    init();//预处理幸运数
    read(n);read(m);
    for (register int i = 1;i <= n;i ++) read(a[i]);
    const int tot = idb(n);//总块数
    for (register int i = 1;i <= tot;i ++){
        for (register int j = fst(i);j <= lst(i);j ++){
            cnt[i][a[j]] ++;
        }
    }
    char opt[10];
    int l, r, L, R;
    while(m --){
        scanf("%s", opt);read(l);read(r);
        L = idb(l);R = idb(r);
        if(opt[0] == 'c'){
            int ans = 0;
            if(L == R){
                for (register int i = l;i <= r;i ++) ans += b[a[i] + tag[L]];
                fprint(ans, 10);
            }
            else{
                for (register int i = l;i <= lst(L);i ++) ans += b[a[i] + tag[L]];
                for (register int i = r;i >= fst(R);i --) ans += b[a[i] + tag[R]];
                for (register int i = L + 1;i < R;i ++) {
                    for (register int j = 1;j <= tt;j ++){
                        if(lucky[j] < tag[i]) continue;//其实这里如果逆着来可以稍微剪一剪枝减小常数，不过我懒得写
                        ans += cnt[i][lucky[j] - tag[i]];
                    }
                }
                fprint(ans, 10);
            }
        }
        else{
            int x;read(x);
            if(L == R){
                for (register int i = l;i <= r;i ++) {
                    cnt[L][a[i]] --;
                    a[i] += x;
                    cnt[L][a[i]] ++;
                }
            }
            else{
                for (register int i = l;i <= lst(L);i ++) {
                    cnt[L][a[i]] --;
                    a[i] += x;
                    cnt[L][a[i]] ++;
                }
                for (register int i = r;i >= fst(R);i --){
                    cnt[R][a[i]] --;
                    a[i] += x;
                    cnt[R][a[i]] ++;
                }
                for (register int i = L + 1;i < R;i ++) tag[i] += x;
            }
        }
    }
}
```

---

