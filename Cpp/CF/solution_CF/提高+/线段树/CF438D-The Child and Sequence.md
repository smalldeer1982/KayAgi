# The Child and Sequence

## 题目描述

有一个长度为 $n$ 的数列 $\{a_n\}$ 和 $m$ 次操作，操作内容如下：

1. 格式为 `1 l r`，表示求 $\sum \limits _{i=l}^{r} a_i$ 的值并输出。
2. 格式为 `2 l r x`，表示对区间 $[l,r]$ 内每个数取模，模数为 $x$。
3. 格式为 `3 k x`，表示将 $a_k$ 修改为 $x$。

$1 \le n,m \le 10^5$，$1\le l,r,k\le n$，$1\le x \le 10^9$。

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
2 3 5 4
3 3 5
1 2 5
2 1 3 3
1 1 3
```

### 输出

```
8
5
```

## 样例 #2

### 输入

```
10 10
6 9 6 7 6 1 10 10 9 5
1 3 9
2 7 10 9
2 5 10 8
1 4 7
3 3 7
2 7 9 9
1 2 4
1 6 6
1 5 9
3 1 10
```

### 输出

```
49
15
23
1
9
```

# 题解

## 作者：VenusM1nT (赞：54)

线段树。

建议可以去做一下 $\texttt{GSS4}$ 或者 `花神游历各国`，和这题的想法类似。

观察操作，其中的取模我们是没有见到过的，显然是一个不好处理的操作，因为它不方便打标记，更很难合并标记。一般遇到这种情况，我们可以考虑暴力修改，然后再优化这个暴力的过程。

如果是区间开方，那么我们开个 $7,8$ 次就能开到底，但是如果是取模呢？我们可以用一个结论：$x \mod p<\frac{x}{2}\ (\ p<x\ )$（证明略），所以取模也最多是 $\log x$ 次，我们不妨记录区间最大值，如果最大值 $<p$ 直接返回，就可以通过此题。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
#define reg register
#define inl inline
#define int long long
using namespace std;
int n,q,a[MAXN];
struct SegmentTree
{
	int t[MAXN<<2],maxn[MAXN<<2];
	inl void PushUp(reg int rt)
	{
		t[rt]=t[rt<<1]+t[rt<<1|1];
		maxn[rt]=max(maxn[rt<<1],maxn[rt<<1|1]);
	}
	void Build(reg int rt,reg int l,reg int r)
	{
		if(l==r)
		{
			t[rt]=maxn[rt]=a[l];
			return;
		}
		reg int mid=l+r>>1;
		Build(rt<<1,l,mid);
		Build(rt<<1|1,mid+1,r);
		PushUp(rt);
	}
	void ModifyMod(reg int rt,reg int l,reg int r,reg int tl,reg int tr,reg int p)
	{
		if(maxn[rt]<p) return;
		if(l==r)
		{
			t[rt]%=p;
			maxn[rt]%=p;
			return;
		}
		reg int mid=l+r>>1;
		if(tl<=mid) ModifyMod(rt<<1,l,mid,tl,tr,p);
		if(tr>mid) ModifyMod(rt<<1|1,mid+1,r,tl,tr,p);
		PushUp(rt);
	}
	void Modify(reg int rt,reg int l,reg int r,reg int pos,reg int val)
	{
		if(l==r)
		{
			t[rt]=maxn[rt]=val;
			return;
		}
		reg int mid=l+r>>1;
		if(pos<=mid) Modify(rt<<1,l,mid,pos,val);
		else Modify(rt<<1|1,mid+1,r,pos,val);
		PushUp(rt);
	}
	int Query(reg int rt,reg int l,reg int r,reg int tl,reg int tr)
	{
		if(tl<=l && r<=tr) return t[rt];
		reg int mid=l+r>>1,res=0;
		if(tl<=mid) res+=Query(rt<<1,l,mid,tl,tr);
		if(tr>mid) res+=Query(rt<<1|1,mid+1,r,tl,tr);
		return res;
	}
}T;
signed main()
{
	scanf("%lld %lld",&n,&q);
	for(reg int i=1;i<=n;i++) scanf("%lld",&a[i]);
	T.Build(1,1,n);
	while(q--)
	{
		reg int opt,x,y,z;
		scanf("%lld %lld %lld",&opt,&x,&y);
		if(opt==1) printf("%lld\n",T.Query(1,1,n,x,y));
		else if(opt==2)
		{
			scanf("%lld",&z);
			T.ModifyMod(1,1,n,x,y,z);
		}
		else T.Modify(1,1,n,x,y);
	}
	return 0;
}
```

---

## 作者：fls233666 (赞：17)

最近在学线段树，然后就发现了这道题。

**2020年2月18日更新：修正数学公式中的一些问题。**

-------

### 题意简述
给出一个长度为 $n$ 的序列 $a$ ，有 $m$ 个操作 $(1 \le n,m \le 10^5;1 \le a[i] \le 10^9)$ ，分为以下三种：
- 操作类型 $1$ ：输入格式为 $1 \  l \  r$，查询序列中区间 $[l,r]$ 的和。 $(1 \le l \le r \le n)$
- 操作类型 $2$ ：输入格式为 $2 \  l \  r \  x$，把序列中区间 $[l,r]$ 的所有数 $ \mod \ x$。 $(1 \le l \le r \le n;1 \le x \le 10^9)$
- 操作类型 $3$ ：输入格式为 $3 \  k \  x$，把序列中位置为 $k$ 的数改为 $x$。 $(1 \le k \le n;1 \le x \le 10^9)$

输出每个操作 $1$ 得到的答案。

--------

### 解题思路
操作中有两类是区间操作，显然会想到**用线段树维护**。

- 对于操作 $1$ ：线段树直接维护区间和并支持查询即可。
- 对于操作 $2$ ：这是比较难维护的操作，但是我们知道，对于 $x \mod p$，如果 $(x<p)$ ，那么有 $x \mod p = x$ 如果 $(x \ge p)$ ，那么有$x \  mod \  p < \frac{x}{2}$。也就是说，**当要取模的区间最大值比模数小时，给这个区间取模相当于没有取模；否则即使要取模，区间中的每个数都最多只会被操作 $O( \log(x))$ 次**。所以用线段树维护区间最大值，如果要取模就暴力对每个数操作即可。
- 对于操作 $3$ ：线段树单点修改即可。

那么这题就做完了，下面是代码。

--------

```cpp
#include<iostream>
#include<cstdio>
#define rgt register int
#define ll long long
using namespace std;

inline int rd(){
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	int x=(c^48);
	c=getchar();
	while(c<='9'&&c>='0'){
		x=x*10+(c^48);
		c=getchar();
	}
	return x;
}   //快速读入

inline void print(ll x){
	if(!x){
		putchar('0');
		return;
	}
	ll num[22],siz=0,px=x;
	while(px){
		siz++;
		num[siz]=px%10;
		px/=10;
	}
	while(siz){
		putchar(num[siz]+'0');
		siz--;
	}
}   //快速输出

const int mxn = 1e5+5;
int n,m,a[mxn];
struct tree{
	int l;
	int r;
	ll sum;   //区间和
	ll mx;   //区间最大值
    //由题意得，最后结果可能会爆int，开long long
}tr[mxn*4];   

inline void update(int p){   //节点更新
	tr[p].sum=tr[p*2].sum+tr[p*2+1].sum;
	tr[p].mx=max(tr[p*2].mx,tr[p*2+1].mx); 
}

void build(int dl,int dr,int p){   //建树
	tr[p].l=dl;
	tr[p].r=dr;
	if(dl==dr){
		tr[p].sum=tr[p].mx=a[dl];
		return;
	}
	int md=(dl+dr)/2;
	build(dl,md,p*2);
	build(md+1,dr,p*2+1);
	update(p);
}

void dchange(int dl,int dr,int p,ll x){   //单点修改
	if(dl==tr[p].l&&dr==tr[p].r){
		tr[p].sum=x;
		tr[p].mx=x;
		return;
	}
	int md=(tr[p].l+tr[p].r)/2;
	if(dl<=md)	dchange(dl,dr,p*2,x);
	if(md<dr)	dchange(dl,dr,p*2+1,x);
	update(p);
}

void modchange(int dl,int dr,int p,ll mod){  //区间取模
	if(dl<=tr[p].l&&dr>=tr[p].r&&tr[p].mx<mod)
		return;   //模数大于区间最大值，可以直接退出
	if(dl<=tr[p].l&&dr>=tr[p].r&&tr[p].l==tr[p].r){
		tr[p].mx%=mod;
		tr[p].sum%=mod;
		return;   //单点暴力取模
	}
	int md=(tr[p].l+tr[p].r)/2;
	if(dl<=md)	modchange(dl,dr,p*2,mod);
	if(md<dr)	modchange(dl,dr,p*2+1,mod);
	update(p);
}

ll answer(int dl,int dr,int p){   //查询区间和
	if(dl<=tr[p].l&&dr>=tr[p].r)
		return tr[p].sum;
	int md=(tr[p].l+tr[p].r)/2;
	ll ans=0;
	if(dl<=md)	ans+=answer(dl,dr,p*2);
	if(md<dr)	ans+=answer(dl,dr,p*2+1);
	return ans;
}

int main()
{
	n=rd();
	m=rd();
	for(rgt i=1;i<=n;i++)
		a[i]=rd();
	build(1,n,1);
    //读入并建树
                         
	for(rgt op,tl,tr,x,i=1;i<=m;i++){
		op=rd();
		switch(op){  //对应操作
			case 1:  //操作1
				tl=rd();
				tr=rd();
				print(answer(tl,tr,1));
				putchar('\n');
				break;
			case 2:  //操作2
				tl=rd();
				tr=rd();
				x=rd();
				modchange(tl,tr,1,x);
				break;
			case 3:  //操作3
				tl=tr=rd();
				x=rd();
				dchange(tl,tr,1,x);
				break;
		}
	}	
  
	return 0;
}
```


---

## 作者：FurippuWRY (赞：10)

鲜花：~~看这美丽的 4 秒时限，它在告诉我们这题用暴力做。~~

------------

**前置知识：巴雷特模乘、循环展开。**

巴雷特模乘就是比一般的取模更快，用公式表示就是：

$$a \bmod b=a-(\dfrac{ay}{2^{64}})\times b$$	

其中 $y=\dfrac{2^{64}}{b}$。

由于 `unsigned long long` 的最大值为 $2^{64}-1$，所以要用 `__int128`。

注意 $2^{64}$ 在代码里要用 `1 << 64` 来表示。

用代码表示为：

```cpp
long long mod(long long a, long long b) {
	__int128 y = ((__int128)1 << 64) / b;
	return a - ((__int128)a * y >> 64) * b;
}
```

用这种方法能减少取模所需的时间，在这题里能减少上百毫秒。

如果模数大于被模数，就不用巴雷特了。

------------

循环展开是一种牺牲程序的尺寸来加快程序的执行速度的优化方法，把循环次数减少，然后把多个操作放在一次循环里。举个例子，比如我们要求区间 $[1,10^9]$ 中的所有数的和，一般写法如下：

```cpp
long long ans = 0, MAX = 1e9;
for (long long i = 1; i <= MAX; ++i) {
	ans += i;
}
```

循环展开的写法如下：

```cpp
long long ans = 0, MAX = 1e18;
for (long long i = 1; i <= MAX; i += 5) {
	ans += i;
	ans += (i + 1);
	ans += (i + 2);
	ans += (i + 3);
	ans += (i + 4);
}
```

经过数次运行测试，一般写法的代码用时在 $[1.905,2.145]$ 秒之间，循环展开的代码用时在 $[1.28,1.289]$ 秒之间，可见循环展开的优化之大。

------------

总之做法就是，在第二个操作里加上巴雷特模乘和循环展开，然后打个快读快写和 Ofast，别的就是纯暴力了。

注意变量不要打太多，会拉时间。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

typedef long long ll;
typedef __int128 i128;

const ll N = 1e5 + 9;

//快读快写
char buf[1 << 21], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline ll read() {ll x = 0, f = 1;char ch = getchar();while (ch < '0' || ch > '9') {if (ch == '-')f = -1;ch = getchar();}while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();return x * f;}
inline void print(ll x, char ch = 0) {if (x < 0) putchar('-'), print(-x);else {if (x >= 10) print(x / 10);putchar(x % 10 + '0');}if (ch) putchar(ch);return;}

int n, m, l, r, x, opt;
ll a[N], ans;

int main() {
    
	n = read();
	m = read();
	for (ll i = 1; i <= n; ++i) {
		a[i] = read();
	}
	while (m--) {
		ans = 0;
		opt = read();
		l = read();
		r = read();
		if (opt == 1) {
			for (ll i = l; i <= r; ++i) {
				ans += a[i];
			}
			print(ans, '\n');
		}
		else
		if (opt == 2) {
			x = read();
			i128 y = ((i128)1 << 64) / x;
			ll i;
         //循环展开
			for (i = l; i + 4 <= r; i += 5) {
				//巴雷特模乘
                if (a[i] >= x) {
                    a[i] = a[i] - ((i128)a[i] * y >> 64) * x;
                    if (a[i] >= x) a[i] -= x;
                }
                if (a[i + 1] >= x)
                {
                    a[i + 1] = a[i + 1] - ((i128) a[i + 1] * y >> 64) * x;
                    if (a[i + 1] >= x) a[i + 1] -= x;
                }
                if (a[i + 2] >= x)
                {
                    a[i + 2] = a[i + 2] - ((i128) a[i + 2] * y >> 64) * x;
                    if (a[i + 2] >= x) a[i + 2] -= x;
                }
                if (a[i + 3] >= x)
                {
                    a[i + 3] = a[i + 3] - ((i128) a[i + 3] * y >> 64) * x;
                    if (a[i + 3] >= x) a[i + 3] -= x;
                }
                if (a[i + 4] >= x)
                {
                    a[i + 4] = a[i + 4] - ((i128) a[i + 4] * y >> 64) * x;
                    if (a[i + 4] >= x) a[i + 4] -= x;
                }
			}
			while (i <= r) {
				if (a[i] >= x) {
                    a[i] = a[i] - ((i128)a[i] * y >> 64) * x;
                    if (a[i] >= x) a[i] -= x;
                }
				++i;
			}
		}
		else {
			a[l] = r;
		}
	}
    return 0;
}
```

[此段代码用时 3432ms](https://codeforces.com/contest/438/submission/231436717)，完全暴力代码超时。

感谢 @[double_wings](https://www.luogu.com.cn/user/815710) 的指导。

---

## 作者：Bosun (赞：8)

大家好，我非常喜欢暴力数据结构，于是我用分块A了这题。

首先，想必你来看题解，是因为这道题的取模操作吧！
一个数不停被取模，肯定取不了几次就变成很小的数了（同一道区间开方的题目），而且如果区间最大值小于模数，那取模就没有意义了，所以我们分块，取模暴力，当然还得记录区间最大值，判断此操作是否有必要执行。（还得开O2才能过哦）

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
int a[1000001];
int l[1005],r[1005],bel[1000005];
ll sum[1005];
int mx[1005];
inline ll query(int L,int R){
	int i;
	ll ans=0;
	if(bel[L]==bel[R]){
		for(i=L;i<=R;++i)ans+=a[i];
	}else{
		for(i=L;i<=r[bel[L]];++i)ans+=a[i];
		for(i=l[bel[R]];i<=R;++i)ans+=a[i]; 
		for(i=bel[L]+1;i<=bel[R]-1;++i)ans+=sum[i]; 
	}
	return ans;
}
inline void change(int x,int v){
	sum[bel[x]]-=a[x],sum[bel[x]]+=v;
	a[x]=v;
	int i;
	mx[bel[x]]=0;
	for(i=l[bel[x]];i<=r[bel[x]];++i)mx[bel[x]]=max(mx[bel[x]],a[i]);
}
inline void reset(int L,int R,int p){
	for(int i=L;i<=R;i++)a[i]%=p;
	mx[bel[L]]=0,sum[bel[L]]=0;
	for(int i=l[bel[L]];i<=r[bel[L]];i++)mx[bel[L]]=max(mx[bel[L]],a[i]),sum[bel[L]]+=a[i];
}
inline void modifly(int L,int R,int p){
	int i;
	if(bel[L]==bel[R]){
		reset(L,R,p);
	}else{
		reset(L,r[bel[L]],p);
		reset(l[bel[R]],R,p); 
		for(i=bel[L]+1;i<=bel[R]-1;++i){
			if(mx[i]>=p)
			reset(l[i],r[i],p);	
		}
	}
}
int main(){;
	register int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)scanf("%d",&a[i]);
	int cnt=sqrt(n);
	for(i=1;i<=cnt;i++){
		l[i]=r[i-1]+1;
		r[i]=l[i]+cnt-1;
	}
	if(r[cnt]<n){
		cnt++;
		l[cnt]=r[cnt-1]+1;
		r[cnt]=n;
	}
	for(i=1;i<=cnt;++i){
		for(j=l[i];j<=r[i];++j){
			bel[j]=i;
			sum[i]+=a[j];	
			mx[i]=max(mx[i],a[j]);
		}
	}
	while(m--){
		int opt;
		scanf("%d",&opt);
		if(opt==1){//query
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",query(l,r));
		}
		if(opt==2){//modifly
			int l,r,p;
			scanf("%d%d%d",&l,&r,&p);
			modifly(l,r,p);
		}
		if(opt==3){//change
			int x,v;
			scanf("%d%d",&x,&v);
			change(x,v);
		}
	}
	return 0;
}
```


---

## 作者：HomuraCat (赞：5)

用线段树维护

问题是区间取膜怎么搞呀，取起来超级慢的QAQ

我们可以发现，每个数取模后如果它改变了，那么它必然缩小至少二分之一。

比如说一个$a\%b=c\quad(b<a)$，我们有$a=kb+c$且$b>c,k>1$，那么就有$a>2c$

有了这点就好办了，我们维护一个区间最大值，每次取膜的时候判断一下最大值如果小于膜数的话就不处理了。

这样每个数最多被膜$loga_i$次，总复杂度$O(nlognloga_i)$

代码：

```cpp
#include<bits/stdc++.h> 
#define fo(i, a, b) for (int i = (a); i <= (b); ++i)
#define fd(i, a, b) for (int i = (a); i >= (b); --i)
#define edge(i, u) for (int i = head[u], v = e[i].v; i; i = e[i].nxt, v = e[i].v)
#define N 100005
#define pb push_back
#define F first
#define S second
#define ll long long
#define inf 1000000007
#define mp std::make_pair
#define lowbit(x) (x & -x)
#define ls (k << 1)
#define rs (k << 1 | 1)
int n, m, a[N], x, y, pos, val, opt, tot, l, r;
struct node{
    ll sum, max, add;
}t[N << 2];
inline void pushdown (int k)
{
    if (t[k].add)
    {
        t[ls].add += t[k].add;
        t[rs].add += t[k].add;
        t[k].sum += t[k].add;
        t[k].add = 0;
    }
}
inline void build (int k, int l, int r)
{
    if (l == r) {t[k].max = t[k].sum = a[l]; return;}
    int mid = l + r >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    t[k].sum = t[ls].sum + t[rs].sum;
    t[k].max = std::max(t[ls].max, t[rs].max);
}
inline void modify (int k, int l, int r)
{
    if (l == r && l == pos) {t[k].max = t[k].sum = val; return;}
    pushdown(k);
    int mid = l + r >> 1;
    if (pos <= mid) modify(ls, l, mid);
        else modify(rs, mid + 1, r);
    t[k].sum = t[ls].sum + t[rs].sum;
    t[k].max = std::max(t[ls].max, t[rs].max);
}
inline ll query (int k, int l, int r, int x, int y)
{
    if (x <= l && r <= y) {return t[k].sum + t[k].add;}
    pushdown(k);
    int mid = l + r >> 1;
    if (y <= mid) return query(ls, l, mid, x, y);
    if (x > mid) return query(rs, mid + 1, r, x, y);
    return query(ls, l, mid, x, y) + query(rs, mid + 1, r, x, y);
}
inline void modulo (int k, int l, int r, int x, int y)
{
    if (x <= l && r <= y && t[k].max < val) return;
    if (l == r) {t[k].sum = t[k].max = t[k].sum % val; return;}
    pushdown(k);
    int mid = l + r >> 1;
    if (x <= mid) modulo(ls, l, mid, x, y);
    if (mid < y) modulo(rs, mid + 1, r, x, y);
    t[k].sum = t[ls].sum + t[rs].sum;
    t[k].max = std::max(t[ls].max, t[rs].max);
}
int main ()
{
    scanf("%d %d", &n, &m);
    fo (i, 1, n)
        scanf("%d", &a[i]);
    build(1, 1, n);
    fo (I, 1, m)
    {
        scanf("%d", &opt);
        if (opt == 1)
        {
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(1, 1, n, l, r));
        }
        else
        if (opt == 2)
        {
            scanf("%d %d %d", &l, &r, &val);
            modulo(1, 1, n, l, r);
        }
        else
        {
            scanf("%d %d", &pos, &val);
            modify(1, 1, n);
        }
    }
    return 0;
}
```

---

## 作者：灼眼的夏娜 (赞：4)

CSP还有四天，写篇题解攒攒RP

这个题和**花神游历各国**蛮像的，相信做过那题的同学这个题也不是问题，这个题单点就在与取模，注意到的是，直接对区间取模是不满足线段树维护的性质的，所以只能一$down$到底，递归到叶节点，那肯定有人会问：这不就$T$飞了吗？

但是考虑一下，对一个数取模，小模大得小，假如一段区间最大值都比这个模数小，那无论怎么改，其值都不会变，有了这个性质，我们可以去掉许多不必要的操作，由于一次取模至少会砍一半，所以在$log$的时间内就可以完成对一个数的所有取模操作，这样就可做了，而上面提到的那个题是开根号，思想是一样的，当开到$1$的时候就不用再开了，因此我们额外维护一个区间最大值即可

PS：其实这是我们今天的考试题，还加了树剖，其实和序列上没啥区别，所以会有些奇怪的的东西，忽略就好（个人喜欢结构体封装）

## code
```
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define ls (o << 1)
#define rs (o << 1 | 1)
/*
	我在时光斑驳的深处，
	聆听到花开的声音。
	君がくれたもの 
*/
using namespace std;
typedef long long LL;
const int N = 1e5 + 5;
int n, m, head[N], cnt, tot, v[N];
struct saber { int nxt, to; } rin[N << 1];
int fa[N], son[N], size[N], dep[N], top[N], dfn[N << 2], rev[N << 2];

inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return x * f;
}
/*以下是树剖部分，请自行跳过*/
struct Tree_Chain_cut {
	
	inline void add(int fr, int to) {
		rin[++cnt].to = to;
		rin[cnt].nxt = head[fr];
		head[fr] = cnt;
	}
	
	void dfs1(int x, int f) {
		dep[x] = dep[fa[x] = f] + (size[x] = 1);
		for (int i = head[x]; i ; i = rin[i].nxt) {
			int vc = rin[i].to;
			if (vc == f) continue;
			dfs1(vc, x);
			size[x] += size[vc];
			if (size[vc] > size[son[x]]) son[x] = vc;
		}
	}
	
	void dfs2(int x, int tp) {
		top[rev[dfn[x] = ++ tot] = x] = tp;
		if (son[x]) dfs2(son[x], tp);
		for (int i = head[x]; i ; i = rin[i].nxt) {
			int vc = rin[i].to;
			if (vc == fa[x] || vc == son[x]) continue;
			dfs2(vc, vc);
		}
	}
	
}Shana;
/*以上是树剖部分*/

/*以下是本题代码*/
struct Segment_Tree {
	
	struct Tree { LL maxn, sum; } T[N << 2];
	
	inline void update(int o) { 
		T[o].sum = T[ls].sum + T[rs].sum; 
		T[o].maxn = max(T[ls].maxn, T[rs].maxn);
	}
	
	void build(int o, int l, int r) {
		if (l == r) { T[o].sum = T[o].maxn = v[rev[l]]; return; }
		int mid = (l + r) >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
		update(o);
	}
	
	void Change_p(int o, int l, int r, int x, LL v) {
		if (l == r) {  T[o].sum = T[o].maxn = v; return; }
		int mid = (l + r) >> 1;
		if (x <= mid) Change_p(ls, l, mid, x, v);
		else Change_p(rs, mid + 1, r, x, v);
		update(o);
	}
	
	void Change(int o, int l, int r, int x, int y, LL v) {
    	//区间最大值的作用，小于模数直接return
		if (x <= l && y >= r && T[o].maxn < v) return; 
		if (l == r) { T[o].sum %= v, T[o].maxn = T[o].sum; return; }
		int mid = (l + r) >> 1;
		if (x <= mid) Change(ls, l, mid, x, y, v);
		if (y > mid) Change(rs, mid + 1, r, x, y, v);
		update(o);
	}
	
	LL query(int o, int l, int r, int x, int y) {
		if (l >= x && r <= y) return T[o].sum;
		int mid = (l + r) >> 1; LL res = 0;
		if (x <= mid) res += query(ls, l, mid, x, y);
		if (y > mid) res += query(rs, mid + 1, r, x, y);
		return res;
	}
	
} Violet;
/*以上是本题代码*/

/*树剖请忽略*/
struct QUERY {
	
	void Change_point(int x, int v) { Violet.Change_p(1, 1, n, dfn[x], v); }
	
	LL Ask(int x, int y) {
		LL res = 0;
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) swap(x, y);
			res += Violet.query(1, 1, n, dfn[top[x]], dfn[x]);
			x = fa[top[x]];
		}
		if (dep[x] > dep[y]) swap(x, y);
		res += Violet.query(1, 1, n, dfn[x], dfn[y]);
		return res;
	}

} Nymph;
/*树剖请忽略*/

int main() {
	freopen("flower.in", "r", stdin);
	freopen("flower.out", "w", stdout);

	cin >> n >> m;
	for (int i = 1, u, v; i < n; ++ i) {
		u = read(), v = read();
		Shana.add(u, v), Shana.add(v, u);
	} 
	for (int i = 1; i <= n; ++ i) v[i] = read();
	Shana.dfs1(1, 0), Shana.dfs2(1, 1), Violet.build(1, 1, n);
	for (int i = 1, op, x, y; i <= m; ++ i) {
		op = read(), x = read(), y = read();
        //这是考试代码，没改前的，操作顺序有点不一样，请注意
		if (op == 1) Violet.Change(1, 1, n, dfn[x], dfn[x] + size[x] - 1, y);
		if (op == 2) Nymph.Change_point(x, y);
		if (op == 3) printf("%lld\n", Nymph.Ask(x, y));
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
```


---

## 作者：Juan_feng (赞：2)

## 分块也可以通过此题qwq

~~跑的贼慢= =~~


咳咳，进入正题。

区间求和和单点修改都是基操，这里就不深入讲解了

看看区间取%

方法之前的dalao都说了，维护每一个块内的最大值，如果这个最大值小于膜数就直接跳过此块，散块暴力修改，因为每次修改至少让一个数减小一半，所以每个数最多修改次数为log级别的。 **然而分块怎么维护最大值呢= =？** 愚蠢如我自然只能用蠢办法了QAQ ：

用vector保存每个块内的数值大小， 修改的时候只要erase掉当前数值再insert修改后的数值就好了。 取最大值的时候就直接取出vector的最后一个值。

大概就是这样啊qaq 

**感觉还有优化的空间**，小蒟蒻的题解权当抛砖引玉了qwqwq 

如果还有什么问题或者意见建议的话不妨直接私信小蒟蒻qaq

**那么代码如下**

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#define maxn 100010
#define ll long long
#define re register
#define FOR(i, l, r) for(re ll i = l; i <= r; ++i)
using namespace std;

ll n, m, c, r, t, x, y, z, k; //小蒟蒻太懒就全开上long long了
ll sq;
ll a[maxn], b[maxn], maxx[maxn], ans[maxn];
vector<ll> ve[1001];

inline void in(re ll &x){ //快读
    x=0;ll f=1;char c=getchar();
    while(c<'0'||c>'9'){
        if(c==-1) return;
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0'){
        x=(x<<1)+(x<<3)+(c^'0');
        c=getchar();
    }
    x=x*f;
}

void out(re ll a){
    if(a<0){
        a*=-1;
        putchar('-');
    } 
    if(a>=10)out(a/10);
    putchar(a%10+'0');
}

ll query(ll x, ll y) { //求和
	ll anss = 0;
	FOR(i, x, min(y, b[x]*sq))
      anss += a[i];
    if(b[x] != b[y])
      FOR(i, (b[y]-1)*sq+1, y) 
        anss += a[i];
    FOR(i, b[x]+1, b[y]-1)
      anss += ans[i];
    return anss;
}

void change(ll x, ll y, ll p) { //区间取%
	FOR(i, x, min(y, b[x]*sq)) { //散块暴力修改
		if(a[i] >= p) {
			ans[b[x]] -= a[i];
			ve[b[x]].erase(lower_bound(ve[b[x]].begin(), ve[b[x]].end(), a[i]));
			a[i] %= p;
			ans[b[x]] += a[i];
			ve[b[x]].insert(lower_bound(ve[b[x]].begin(), ve[b[x]].end(), a[i]), a[i]);
		}
	}
	if(b[x] != b[y]) 
	  FOR(i, (b[y]-1)*sq+1, y) {
	  	if(a[i] >= p) {
	  		ans[b[y]] -= a[i];
	  		ve[b[y]].erase(lower_bound(ve[b[y]].begin(), ve[b[y]].end(), a[i]));
	  		a[i] %= p;
	  		ans[b[y]] += a[i];
	  		ve[b[y]].insert(lower_bound(ve[b[y]].begin(), ve[b[y]].end(), a[i]), a[i]);
		  }
	  }
	FOR(i, b[x]+1, b[y]-1) { //整块判断是否需要修改，是则暴力去找
		ll nc = ve[i].size();
		if(ve[i][nc-1] >= p)
		  FOR(j, (i-1)*sq+1, i*sq) {
		  	if(a[j] >= p) {
		  		ans[i] -= a[j];
	  			ve[i].erase(lower_bound(ve[i].begin(), ve[i].end(), a[j]));
	  			a[j] %= p;
	  			ans[i] += a[j];
	  			ve[i].insert(lower_bound(ve[i].begin(), ve[i].end(), a[j]), a[j]);
			}
		  }
	}
}

int main() {
	in(n), in(m);
	sq = sqrt(n);
	FOR(i, 1, n) { //预处理
		in(a[i]), b[i] = (i-1)/sq+1, ans[b[i]] += a[i];	
		ve[b[i]].insert(lower_bound(ve[b[i]].begin(), ve[b[i]].end(), a[i]), a[i]);
	} 
	FOR(i, 1, m) {
		in(t);
		if(t == 1) {
			in(x), in(y);
			out(query(x, y));
			putchar(10);
		}
		if(t == 2) {
			in(x), in(y), in(z);
			change(x, y, z);
		}
		if(t == 3) {
			in(x), in(k);
			ans[b[x]] -= a[x];
			ve[b[x]].erase(lower_bound(ve[b[x]].begin(), ve[b[x]].end(), a[x]));
			a[x] = k;
			ans[b[x]] += k;
			ve[b[x]].insert(lower_bound(ve[b[x]].begin(), ve[b[x]].end(), a[x]), a[x]);
		}
	}
    return 0; // 功德圆满
}
```

---

## 作者：King丨帝御威 (赞：1)

题目大意：给定数列，区间查询和，区间取模，单点修改。

$n,m$小于$10^5$

查询区间和和单点修改就不用说了吧，线段树基本操作，那？？对于这道题目的区间修改该怎么处理呢？？不难发现，一个数模两次同样的数时没有任何意义的，而且一个数模一个比它大的数也是没有意义的？！！！那么，我们便可以采用一种暴力的思想，去修改每一个位置，每次判断一下区间最大值是不是比模数大即可。因为是暴力修改，所以也无需$pushdown$，那么代码应该就很好写了吧，也不算太长。


下面是我的代码，仅供参考，~~毕竟太丑了~~：
```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#define maxn 100007
#define ls rt<<1
#define rs rt<<1|1
#define ll long long
using namespace std;
int n,m,maxx[maxn<<2];
ll sum[maxn<<2];
inline int qread() {
  char c=getchar();int num=0,f=1;
  for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
  for(;isdigit(c);c=getchar()) num=num*10+c-'0';
  return num*f;
}
inline void pushup(int rt) {
  sum[rt]=sum[ls]+sum[rs];
  maxx[rt]=max(maxx[ls],maxx[rs]);
}
void build(int rt, int l, int r) {
  if(l==r) {
    maxx[rt]=sum[rt]=qread();
    return;
  }
  int mid=(l+r)>>1;
  build(ls,l,mid);
  build(rs,mid+1,r);
  pushup(rt);
}
void add(int rt, int l, int r, int L, int val) {
  if(l==r) {
    maxx[rt]=sum[rt]=val;
    return;
  }
  int mid=(l+r)>>1;
  if(L<=mid) add(ls,l,mid,L,val);
  else add(rs,mid+1,r,L,val);
  pushup(rt);
}
ll csum(int rt, int l, int r, int L, int R) {
  if(L<=l&&r<=R) return sum[rt];
  int mid=(l+r)>>1;
  ll ans=0;
  if(L<=mid) ans+=csum(ls,l,mid,L,R);
  if(R>mid) ans+=csum(rs,mid+1,r,L,R);
  return ans;
}
void modify(int rt, int l, int r, int L, int R, int p) {
  if(maxx[rt]<p) return;
  if(l==r) {
    sum[rt]%=p;maxx[rt]%=p;
    return;
  }
  int mid=(l+r)>>1;
  if(L<=mid) modify(ls,l,mid,L,R,p);
  if(R>mid) modify(rs,mid+1,r,L,R,p);
  pushup(rt);
}
int main() {
  n=qread(),m=qread();
  build(1,1,n);
  for(int i=1,k,x,y,z;i<=m;++i) {
    k=qread(),x=qread(),y=qread();
    if(k==1) printf("%lld\n",csum(1,1,n,x,y));
    if(k==2) {
      z=qread();
      modify(1,1,n,x,y,z);
    }
    if(k==3) add(1,1,n,x,y);
  }
  return 0;
}
```

---

## 作者：xsI666 (赞：0)

### 题解
线段树基础题。

区间查询和、单点修改很简单，也很基础，这里就不在赘述。

重点来看一下区间取模。

首先，我们不难知道，当一个数$a \% b$时，如果$a < b$，那么这个取模是没有什么意义的（$*$）。

如果，我们执行区间取模时，一个一个数去取模，那么复杂度会非常高，达到$\Theta (n \times m)$，绝对会$TLE$。

因此考虑一种类似搜索“剪枝”的方式来优化区间取模。

这时，我们就要用到上面的（$*$）了。

用一个数组$mx[]$来记录区间内的最大值，如果这个最大值都小于我们要取模的那个数了，就直接$return$返回掉，因为对这个区间取模就已经没有意义了。

很容易就可以写出$AC$代码。

### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#define int long long

using namespace std;

inline int gi()
{
    int f = 1, x = 0; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar();}
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar();}
    return f * x;
}

int n/*数的个数*/, m/*操作个数*/, tr[100003 << 2]/*区间和*/, mx[100003 << 2]/*区间最大值*/, a[100003]/*每个数的值*/;

inline void pushup(int p)//上传节点操作
{
	mx[p] = max(mx[p << 1], mx[(p << 1) | 1]);//更新区间最大值
	tr[p] = tr[p << 1] + tr[(p << 1) | 1];//加上区间和
}

void build(int s, int t, int p)//建树操作
{
	if (s == t)//已经是叶子节点了
	{
		mx[p] = tr[p] = a[s];//更新节点的参数
		return;//返回
	}
	int mid = (s + t) >> 1;//计算中间值
	build(s, mid, p << 1); //递归左子树
	build(mid + 1, t, (p << 1) | 1);//递归右子树
	pushup(p);//上传当前节点
}

void modify(int l/*要修改的数的编号,即目标节点*/, int r/*要更新的值*/, int s, int t, int p)//单点修改操作
{
	if (s == t)//已经到了目标节点
	{
		mx[p] = tr[p] = r; //更新节点参数
		return;//直接返回
	}
	int mid = (s + t) >> 1;//计算中间值
	if (l <= mid) //目标节点在左区间
		modify(l, r, s, mid, p << 1);//递归左子树寻找
	else //目标节点在右区间
		modify(l, r, mid + 1, t, (p << 1) | 1);//递归右区间查找
	pushup(p);//上传当前节点
}

void getmod(int l/*区间左界*/, int r/*区间右界*/, int mod/*要取模的值*/, int s, int t, int p)//区间取模操作
{
	if (mx[p] < mod) return;//"剪枝"操作
	if (s == t)//已经到了叶子节点
	{
		tr[p] = tr[p] % mod; //取模
		mx[p] = tr[p];//更新最大值
		return;//返回
	}
	int mid = (s + t) >> 1;//计算中间值
	if (l <= mid) getmod(l, r, mod, s, mid, p << 1);//查找中点左边的区间进行取模
	if (r > mid) getmod(l, r, mod, mid + 1, t, (p << 1) | 1);//查找中点右边的区间进行取模
	pushup(p);//上传当前节点
}

int getans(int l, int r, int s, int t, int p)//查询区间和操作
{
	if (l <= s && t <= r) return tr[p];//当前区间完全包含于目标区间,就直接返回当前区间的和
	int mid = (s + t) >> 1, ans = 0;//计算中间值及初始化答案
	if (l <= mid) ans = ans + getans(l, r, s, mid, p << 1);//加上中点左边的区间进行求和
	if (r > mid) ans = ans + getans(l, r, mid + 1, t, (p << 1) | 1);//加上中点右边的区间进行求和
	return ans;//返回答案
}

signed main()
{
	n = gi(), m = gi();
	for (int i = 1; i <= n; i++) a[i] = gi();
	//以上为输入
	build(1, n, 1);//建树
	while (m--)
	{
		int fl = gi(), x = gi(), y = gi();
		if (fl == 1)//是输出区间和操作
		{
			printf("%lld\n", getans(x, y, 1, n, 1));//就输出区间和
		}
		else if (fl == 2)//区间取模操作
		{
			int md = gi();//输入模数
			getmod(x, y, md, 1, n, 1);//进行取模
		}
		else 
		{
			modify(x, y, 1, n, 1);//否则就进行单点修改,注意是把点x的值修改为y
		}
	}
	return 0;//结束
}
```

---

## 作者：moye到碗里来 (赞：0)

之前的题解只说到可以不打标记直接改，但是没说到点子上。。。为什么可以这样做？思考mod运算的方式，如果mod一次，若是模数大于被膜数，则不会有任何改变，可以维护最大值跳过，若是对数列有影响，那么这个数字一定至少会/2，肯定比原来的1/2小，所以一个数最多更改log次，这就是为什么可以这样做的原因。。

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
#define ll long long 
struct node{
    ll maxn,sum;
    node *ls,*rs;
    node(ll m,ll s,node *l,node *r) : maxn(m),sum(s),ls(l),rs(r){}
    node(){}
}pool[MAXN * 2];
node *NewNode(ll maxn,ll sum,node *ls,node *rs){
    static int cnt = 0;
    pool[cnt] = node(maxn,sum,ls,rs);
    return &pool[cnt++];
}
ll n,m,a[MAXN];
node *build(int l,int r){
    if(l > r)return NULL;
    node *rt = NewNode(0,0,NULL,NULL);
    if(l == r){
        rt->maxn = rt->sum = a[l];
        return rt;
    }
    int mid = l + r >> 1;
    rt->ls = build(l,mid);
    rt->rs = build(mid + 1,r);
    rt->maxn = max(rt->ls->maxn,rt->rs->maxn);
    rt->sum = rt->ls->sum + rt->rs->sum;
    return rt;
}
void change(node *rt,int l,int r,int place,ll x){
    if(l == r){
        rt->sum = x;
        rt->maxn = x;
        return ;
    }
    int mid = l + r >> 1;
    rt->maxn = max(rt->maxn,x);
    if(mid >= place)change(rt->ls,l,mid,place,x);
    else change(rt->rs,mid + 1,r,place,x);
    rt->sum = rt->ls->sum + rt->rs->sum;
}
void getmod(node *rt,int l,int r,int L,int R,ll x){
    if(l == r){
        rt->maxn %= x;
        rt->sum = rt->maxn;
        return ; 
    }
    int mid = l + r >> 1;
    if(L <= l && r <= R){
        if(rt->maxn < x)return ;
        getmod(rt->ls,l,mid,L,R,x);
        getmod(rt->rs,mid + 1,r,L,R,x);
        rt->maxn = max(rt->ls->maxn,rt->rs->maxn);
        rt->sum = rt->ls->sum + rt->rs->sum;
        return ;
    }
    if(mid >= L)getmod(rt->ls,l,mid,L,R,x);
    if(mid < R)getmod(rt->rs,mid + 1,r,L,R,x);
    rt->maxn = max(rt->ls->maxn,rt->rs->maxn);
    rt->sum = rt->ls->sum + rt->rs->sum;
    return ;
}
ll query(node *rt,int l,int r,int L,int R){
    if(L <= l && r <= R){
        return rt->sum;
    }
    int mid = l + r >> 1;ll ans = 0;
    if(mid >= L)ans += query(rt->ls,l,mid,L,R);
    if(mid < R)ans += query(rt->rs,mid + 1,r,L,R);
    return ans;
}
int main()
{
    scanf("%lld %lld",&n,&m);
    for(int i = 1; i <= n; ++i){
        scanf("%lld",&a[i]);  
    }
    node *rt =  build(1,n);
    int opt,l,r;ll x;
    for(int i = 1; i <= m; ++i){
        scanf("%d",&opt);
        if(opt == 1){
            scanf("%d %d",&l,&r);
            printf("%lld\n",query(rt,1,n,l,r));
        }
        if(opt == 2){
            scanf("%d %d %lld",&l,&r,&x);
            getmod(rt,1,n,l,r,x);
        }
        if(opt == 3){
            scanf("%d %lld",&l,&x);
            change(rt,1,n,l,x);
        }
    }
    return 0;
}
```

---

## 作者：ygsldr (赞：0)

这道题主要考察线段树emm...

刚开始觉得求模要懒标记，然后忽然发现没有正确性，显然(a[l] + a[l + 1] .... + a[r])%mod != a[l] % mod + a[l+1] % mod .... + a[r] % mod

那么只能眼睁睁看着一次求模遍历所有节点吗，所以要加优化。

什么时候我们不用模?当且仅当这个区间所有节点的值都比mod小。因此我们可以维护区间最大值，使得当我们便利到某个区间时，假如区间最大值都小于mod，我们就可已直接return

参考代码如下：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define k 32001
#define lson(x) (x << 1)
#define rson(x) ((x << 1) + 1)
typedef long long ll;

inline ll read()
{
	ll x(0), f(1);
	char ch = getchar();
	while (ch > '9' || ch < '0')
	{
		if (ch == '-')f = -1;
		ch = getchar();
	}
	while (ch <= '9' && ch >= '0')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
inline void write(ll x)
{
	int num(0);
	if (x == 0)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	char a[11];
	while (x > 0)
	{
		a[num] = x % 10 + '0';
		x /= 10;
		++num;
	}
	for (int i(num - 1); i >= 0; --i)putchar(a[i]);
	putchar('\n');
	return;
}

ll sum[4123456];
ll maxinum[4123456];//维护最大值

inline void pushup(int node)
{
	sum[node] = sum[node << 1] + sum[node << 1 | 1];
	maxinum[node] = max(maxinum[node << 1],maxinum[node << 1 | 1]);
}//被儿子更新 

void build(int l,int r,int node)
{
	if(l == r)
	{
		maxinum[node] = sum[node] = read();
		return;
	}
	int mid((l + r) >> 1);
	build(l, mid, node << 1);
	build(mid + 1, r, node << 1 | 1);
	pushup(node);
	return;
}

void update(int l,int r,int points,ll to,int node)
{
	if(l == r)
	{
		maxinum[node] = sum[node] = to;
		return;
	}
	int mid((l + r) >> 1);
	if(mid >= points)update(l, mid, points, to, node << 1);
	if(mid < points)update(mid + 1, r, points, to, node << 1 | 1);
	pushup(node);
}

void update(int l,int r,int L,int R,int mod,int node)
{
	if(maxinum[node] < mod)return;
	if(l == r)
	{
		sum[node] %= mod;
		maxinum[node] = sum[node];
		return;
	}
	int mid((l + r) >> 1);
	if(mid >= L)update(l, mid, L, R, mod, node << 1);
	if(mid < R)update(mid + 1, r, L, R, mod, node << 1 | 1);
	pushup(node);
}

ll Sum(int l,int r,int L,int R,int node)
{
	if(l >= L && r <= R)return sum[node];
	ll _sum(0);
	int mid((l + r) >> 1);
	if(mid >= L)_sum += Sum(l, mid, L, R, node << 1);
	if(mid < R)_sum += Sum(mid + 1, r, L, R, node << 1 | 1);
	return _sum;
}

int main()
{
	int n(read()),m(read());
	build(1,n,1);
	for(int i(1);i <= m;++i)
	{
		int cmd(read()),l(read()),r(read());
		if(cmd == 1)
		{
			write(Sum(1,n,l,r,1));
		}
		else if(cmd == 2)
		{
			int mod(read());
			update(1,n,l,r,mod,1);
		}
		else 
		{
			update(1,n,l,r,1);
		}
	}
	return 0;
}


```

从不用懒标记来看，这还是一道很水的线段树（逃）

---

