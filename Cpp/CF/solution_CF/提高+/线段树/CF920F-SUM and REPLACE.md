# SUM and REPLACE

## 题目描述

Let $ D(x) $ be the number of positive divisors of a positive integer $ x $ . For example, $ D(2)=2 $ ( $ 2 $ is divisible by $ 1 $ and $ 2 $ ), $ D(6)=4 $ ( $ 6 $ is divisible by $ 1 $ , $ 2 $ , $ 3 $ and $ 6 $ ).

You are given an array $ a $ of $ n $ integers. You have to process two types of queries:

1. REPLACE $ l $ $ r $ — for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920F/8c67e39bbb4a436ecb9bbf84b28c1b332f05ca94.png) replace $ a_{i} $ with $ D(a_{i}) $ ;
2. SUM $ l $ $ r $ — calculate ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920F/1deabb69ce88e0c9a5b8e5232e5782460ccfe87b.png).

Print the answer for each SUM query.

## 样例 #1

### 输入

```
7 6
6 4 1 10 3 2 4
2 1 7
2 4 5
1 3 5
2 4 4
1 5 7
2 1 7
```

### 输出

```
30
13
4
22
```

# 题解

## 作者：lhm_ (赞：19)

可以事先打表观察每个数的约数个数，观察到如果进行替换，若干次后这个数便会被替换成1。

所以我们可以直接暴力的进行区间修改，若这个数已经到达1或2，则以后就不再修改，用并查集和树状数组进行维护。

这个方法用了[P2391 白雪皑皑](https://www.luogu.org/problem/P2391)的思想处理，用并查集标记该点已经不再用替换。

code：
```cpp
#include<bits/stdc++.h>
#include<cctype>
#define maxn 300010
#define lowbit(x) (x&(-x))
typedef long long ll;
using namespace std;
ll n,m;
ll fa[maxn],k,l,r;
ll a[maxn],tree[maxn*4];
ll d[1000010];
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=x*10+(c^48);c=getchar();}
	if(flag)x=-x;
}
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void add(int x,ll d)
{
	while(x<=n)
	{
		tree[x]+=d;
		x+=lowbit(x);
	}
}
ll query(int x)
{
	ll sum=0;
	while(x)
	{
		sum+=tree[x];
		x-=lowbit(x);
	}
	return sum;
}
int main()
{
	for(register int i=1;i<=1000000;++i)
	{
		for(register int j=i;j<=1000000;j+=i)
		d[j]++;//将每个数的约数个数预处理出来，便于后面替换
	}
	read(n);
	read(m);
	for(register int i=1;i<=n;++i)
	{
		read(a[i]);
		add(i,a[i]);
		fa[i]=i;
	}
	fa[n+1]=n+1;
	while(m--)
	{
		
		read(k);
		read(l);
		read(r);
		if(l>r)
		swap(l,r);
		if(k==1)
		{
			for(register int i=l;i<=r;)
			{
				add(i,(ll)d[a[i]]-a[i]);
				a[i]=(ll)d[a[i]];
				if(a[i]<=2)
				fa[i]=i+1;//若这个数已经为1或2，这将其指向它下一个数
				if(i==find(i))
				i++;
				else
				i=fa[i];//进行跳转，忽略不再要替换的数
			}
		}
		else
		printf("%lld\n",query(r)-query(l-1));
	}
	return 0;
}
```


---

## 作者：Tethys (赞：10)

[题面](https://www.luogu.com.cn/problem/CF920F)

## 题意：
1：将  [l,r]区间内的所有数变为当前权值的正约数的个数,即：$a_i$=d(a_i)

2：求$\displaystyle \sum_{i=l}^{r}a_{i}$

## 前置芝士：
求$d(i)$的话，可以先康康这个题[P6810 「MCOI-02」Convex Hull 凸包](https://www.luogu.com.cn/problem/P6810)

这个题中就是线性筛处理出了每个数的约数的个数

这里安利一个同机房dalao的[博客](https://www.luogu.com.cn/blog/genshy/solution-p6810)

我们就可以发现每个数的约数的个数就可以处理出来了

```cpp
void make_d(){
    d[1] = f[1] = 1;
    for(int i = 2; i <= M - 5; i ++){
        if(!is_pri[i]){
            pri[++ cnt] = i;
            f[i] = 1;
            d[i] = 2;
        }
        for(int j = 1; j <= cnt && i * pri[j] <= M - 5; j ++){
            is_pri[i * pri[j]] = 1;
            if(i % pri[j] == 0){
                f[i * pri[j]] = f[i] + 1;
                d[i * pri[j]] = (d[i]) * (f[i * pri[j]] + 1) / (f[i] + 1);
                break;
            }
            f[i * pri[j]] = 1;
            d[i * pri[j]] = d[i] * d[pri[j]];
        }
    }
}
```

## 实现：

我们先用线性筛筛出每个数的约数的个数

然后维护一棵线段树，线段树维护一个区间$sum$和区间最大值

我们考虑当$i=1或2$的时候，$d(i)$是等于$i$的，所以不用修改

所以当区间最大值$<=2$的时候，我们就可以不对这个区间进行任何修改操作了（因为操作了也没有任何意义）

然后就是维护一棵普通的线段树就好了

但是这个题要注意开$long\ long $，不然会炸的

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls(o) (o << 1)
#define rs(o) (o << 1 | 1)
#define mid ((l + r) >> 1)
const int N = 3e5 + 5, M = 1e6 + 5;
int n, m, a[N], pri[N], cnt;
long long mx[N << 2], tr[N << 2], d[M], f[M];
bool is_pri[M];
void make_d(){
    d[1] = f[1] = 1;
    for(int i = 2; i <= M - 5; i ++){
        if(!is_pri[i]){
            pri[++ cnt] = i;
            f[i] = 1; d[i] = 2;
        }
        for(int j = 1; j <= cnt && i * pri[j] <= M - 5; j ++){
            is_pri[i * pri[j]] = 1;
            if(i % pri[j] == 0){
                f[i * pri[j]] = f[i] + 1;
                d[i * pri[j]] = (d[i]) * (f[i * pri[j]] + 1) / (f[i] + 1);
                break;
            }
            f[i * pri[j]] = 1;
            d[i * pri[j]] = d[i] * d[pri[j]];
        }
    }
}
void up(int o){
    tr[o] = tr[ls(o)] + tr[rs(o)];
    mx[o] = max(mx[ls(o)], mx[rs(o)]);
}
void build(int o, int l, int r){
    if(l == r){
        scanf("%d", &tr[o]);
        mx[o] = tr[o];
        return ;
    }
    build(ls(o), l, mid); build(rs(o), mid + 1, r);
    up(o);
}
void change(int o, int l, int r, int L, int R){
    if(mx[o] <= 2) return ;
    if(l == r){
        tr[o] = mx[o] = d[tr[o]];
        return ;
    }
    if(L <= mid) change(ls(o), l, mid, L, R);
    if(R > mid) change(rs(o), mid + 1, r, L, R);
    up(o);
}
long long query(int o, int l, int r, int L, int R){
    if(L <= l && r <= R) return tr[o];
    long long res = 0;
    if(L <= mid) res += query(ls(o), l, mid, L, R);
    if(R > mid) res += query(rs(o), mid + 1, r, L, R);
    return res; 
}
int main(){
    scanf("%d %d", &n, &m);
    make_d(); build(1, 1, n);
    for(int i = 1, opt, l, r; i <= m; i ++){
        scanf("%d %d %d", &opt, &l, &r);
        if(opt == 1) change(1, 1, n, l, r);
        else printf("%lld\n", query(1, 1, n, l, r));
    }
    return 0;
}
```
完美撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：Diaоsi (赞：5)

## 思路：

提供一个分块做法。

这题跟[CF438D](https://www.luogu.com.cn/problem/CF438D)很像，由于一个整数 $N$ 的约数个数的上界为 $2\sqrt{N}$ ，所以一个数最多被修改 $\log \log N$ 次，就会收敛到 $1/2$ 。

将数列分块，标记每个块内的最大值和块内数值的和。

修改时，边角块就暴力修改然后更新该块的信息。对于其他块，当最大值小于等于 $2$ 时就跳过此块，否则按照边角块的处理方法暴力修改，由于每个数最多被修改 $\log \log N$ 次，所以时间复杂度是可以接受的。

预处理出 $a_i$ 范围内每个数的约数个数 $d(a_i)$ ，修改的时候方便直接调用。

### 时间复杂度：

预处理约数的时间复杂度为调和级数求和的时间复杂度:

 $$ \mathcal{O(N \log N)} $$ 

分块的时间复杂度为:

 $$ \mathcal{O(K N\sqrt{N})} $$ 

其中 $\mathcal{K=\log \log N}$ 

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=300010,M=3000010,INF=0x3f3f3f3f;
long long n,m,t,a[N],L[N],R[N],pos[N],sum[N],mx[N],d[M];
inline long long Max(long long x,long long y){return x>y?x:y;}
inline long long Min(long long x,long long y){return x<y?x:y;}
inline void Swap(long long &x,long long &y){x^=y^=x^=y;}
inline long long read(){
	char c=getchar();long long x=0,f=1;
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
inline void pre(){
	for(register long long i=1;i<=1e6;++i)
		for(register long long j=i;j<=1e6;j+=i)++d[j];
}
inline void Cmax(long long l,long long r){
	long long p=pos[l];
	for(register long long i=l;i<=r;++i)
		if(a[i]>2)a[i]=d[a[i]];
	mx[p]=sum[p]=0;
	for(register long long i=L[p];i<=R[p];++i)
		mx[p]=Max(mx[p],a[i]),sum[p]+=a[i];
}
inline void Change(long long l,long long r){
	long long p=pos[l],q=pos[r];
	if(p==q){
		Cmax(l,r);
		return;
	}
	Cmax(l,R[p]);
	Cmax(L[q],r);
	for(register long long i=p+1;i<=q-1;++i)
		if(mx[i]>2)Cmax(L[i],R[i]);
}
inline long long Query(long long l,long long r){
	long long res=0;
	long long p=pos[l],q=pos[r];
	if(p==q){
		for(register long long i=l;i<=r;++i)
			res+=a[i];
		return res;
	}
	for(register long long i=l;i<=R[p];++i)res+=a[i];
	for(register long long i=p+1;i<=q-1;++i)res+=sum[i];
	for(register long long i=L[q];i<=r;++i)res+=a[i];
	return res;
}
int main(){
	n=read();m=read();
	t=(long long)sqrt(n);pre();
	for(register long long i=1;i<=n;++i)
		a[i]=read();
	for(register long long i=1;i<=t;++i){
		L[i]=(i-1)*t+1;
		R[i]=i*t;
	}
	if(R[t]<n)++t,L[t]=R[t-1]+1,R[t]=n;
	for(register long long i=1;i<=t;++i)
		for(register long long j=L[i];j<=R[i];++j)
			pos[j]=i,sum[i]+=a[j],mx[i]=Max(mx[i],a[j]);
	while(m--){
		long long opts=read();
		long long l=read(),r=read();
		if(opts&1)Change(l,r);
		else printf("%lld\n",Query(l,r));
	}
	return 0;
}
```


---

## 作者：SSerxhs (赞：5)

势能线段树板子题。

对于一个很大的数x，$d(x)$至多是$\frac{x}{2}$，所以每次操作都会使数字除以2，即只有$nlog_2n$次有效操作，可以直接线段树维护最大值、区间和并暴力修改。$d(x)$是一个积性函数，可以线性筛。总复杂度$O(max(a[i])+n*min(log_2n,m))$

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=3e5+2,M=1.2e6+2,O=1e6+2;
ll s[M],ans;
int l[M],r[M],d[O],p[O],ss[N],zd[M];
int n,m,q,i,j,x,y,z,c,gs;
bool ed[O];
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
void build(int x)
{
	if (l[x]==r[x]) {read(zd[x]);m=max(m,zd[x]);s[x]=zd[x];return;}
	l[c=x<<1]=l[x];r[c]=l[x]+r[x]>>1;
	l[c|1]=r[c]+1;r[c|1]=r[x];
	build(c);build(x<<1|1);
	c=x<<1;s[x]=s[c]+s[c|1];
	zd[x]=max(zd[c],zd[c|1]);
}
void mdf(int x)
{
	if (l[x]==r[x]) {s[x]=zd[x]=d[zd[x]];return;}
	int c=x<<1;
	if ((z<=r[c])&&(zd[c]>2)) mdf(c);
	if ((y>r[c])&&(zd[c|1]>2)) mdf(c|1);
	s[x]=s[c]+s[c|1];zd[x]=max(zd[c],zd[c|1]);
}
void sum(int x)
{
	if ((z<=l[x])&&(r[x]<=y)) {ans+=s[x];return;}
	if (z<=r[x<<1]) sum(x<<1);if (y>r[x<<1]) sum(x<<1|1);
}
int main()
{
	read(n);read(q);
	r[l[1]=1]=n;build(1);
	d[1]=1;
	for (i=2;i<=m;i++)
	{
		if (!ed[i])
		{
			d[ss[++gs]=i]=2;p[i]=i;
		}
		for (j=1;(j<=gs)&&((x=i*ss[j])<=m);j++)
		{
			ed[x]=1;
			if (i%ss[j]==0)
			{
				p[x]=p[i]*ss[j];
				if (p[i]==i) {p[x]=x;d[x]=d[i]+1;} else d[x]=d[i/p[i]]*d[p[i]*ss[j]];
				break;
			}
			d[x]=d[i]*d[ss[j]];
			p[x]=ss[j];
		}
	}
	while (q--)
	{
		read(x);read(z);read(y);
		if (x==1) {if (zd[1]>2) mdf(1);}else {ans=0;sum(1);printf("%lld\n",ans);}
	}
}
```


---

## 作者：Priori_Incantatem (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF920F)

本题是很典型的一道 线段树/分块与暴力结合的题  
与本题类似的还有如下几题：  
[SP2713 GSS4](https://www.luogu.com.cn/problem/SP2713)  
[P4145 上帝造题的七分钟2 / 花神游历各国](https://www.luogu.com.cn/problem/P4145)
[CF438D The Child and Sequence](https://www.luogu.com.cn/problem/CF438D)

个人本题是这几题中包装的最好的，~~也是唯一能交题解的一道~~

本题的修改操作非常不好处理，也不容易合并，比较难用传统的线段树方法结局。但是这里的修改操作有一个特点，就是有效的修改次数非常少

显然地，一个数 $n$ 最多有 $2\sqrt{n}$ 个因数，也就是说题目中的 $D(i)\le 2\sqrt i$  
那么，如果每次让 $a_i=D(a_i)$，就相当于让 $a_i$ 开了一个根号  
这样的话，$a_i$ 会快速地减小。假如 $a_i$ 等于 $10^6$（题目中的最大值），那么在不超过 $5$ 次操作后，$a_i$ 就变成 $2$ 了，并且以后无论修改多少次，$a_i$ 永远是 $2$。

那么，每次修改时我们可以暴力地在线段树中递归，如果当前递归到的区间的最大值 $\le 2$，就停止递归，否则就递归到边界进行单点修改。时间复杂度 $\mathcal O (n \log n)$

为了美观以及方便理解，这里只贴出未开long long的代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int Maxn=3e5+10;
const int Maxm=Maxn<<2;
int sum[Maxm],maxv[Maxm];
int a[Maxn],f[1000010];
int n,m;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
inline void push_up(int k)
{
	sum[k]=sum[k<<1]+sum[k<<1|1];
	maxv[k]=max(maxv[k<<1],maxv[k<<1|1]);
}
void modify(int k,int l,int r,int x,int y)
{
	if(maxv[k]<=2)return;
	if(l==r)
	{
		a[l]=f[a[l]];
		sum[k]=maxv[k]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)modify(k<<1,l,mid,x,y);
	if(mid<y)modify(k<<1|1,mid+1,r,x,y);
	push_up(k);
}
int query(int k,int l,int r,int x,int y)
{
	if(x<=l && r<=y)return sum[k];
	int mid=(l+r)>>1,ret=0;
	if(x<=mid)ret=query(k<<1,l,mid,x,y);
	if(mid<y)ret+=query(k<<1|1,mid+1,r,x,y);
	return ret;
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		sum[k]=maxv[k]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	push_up(k);
}
int main()
{
	// freopen("in.txt","r",stdin);
	n=read(),m=read();
	for(int i=1;i<=n;++i)
	a[i]=read();
	build(1,1,n);
	int cnt=1e6;
	for(int i=2;i<=cnt;++i)
	{
		for(int j=i;j<=cnt;j+=i)
		++f[j];
		++f[i];
	}
	while(m--)
	{
		int opt=read(),x=read(),y=read();
		if(opt==1)modify(1,1,n,x,y);
		else printf("%d\n",query(1,1,n,x,y));
	}
	return 0;
}
```

---

## 作者：Vanyun (赞：2)

## 题意：

给定 $n$ 个数的数组 $a$，$m$ 次操作。操作有两种：

1. 将 $i\in[l,r]$ 中的所有 $a_i$ 替换为 $d(a_i)$。$d(x)$ 表示 $x$ 的正约数的个数。
2. 求 $\displaystyle\sum_{i=l}^r a_i$。

## 观察：

我们假如一直对$1000000$进行操作$1$，我们可以发现过程是这样的：

$1000000$ 到 $49$ 到 $3$ 到 $2$。

然后就一直会是$2$。

无一例外。每个数都会经过多次操作要么会变成$1$要么会变成$2$。

而且在以后对这个数进行操作的时候是不会再发生改变的。

多次操作的次数最多为$6$次。

## 思路：

首先$d$是可以预处理出来的qwq。比如通过线性筛。

~~线性筛太麻烦了~~有这样一种预处理方式：

```c++
for(int i = 1; i <= 1000000; i ++){
	for(int j = i; j <= 1000000; j += i){
		d[j] ++;
	}
}
```

实践证明它是不会T的。

---

我们通过观察~~显然~~可以发现，在进行好多次操作之后，每个数会一直是$1$或$2$。

所以对于一个数我们直接暴力修改。毕竟最多的修改次数不会超过$6$次。

在维护区间和的同时维护一个区间最大值。

当修改过程中某个区间最大值小于等于$2$的时候，说明我们这次的操作是~~无能的~~无效的，直接返回即可。

注意要开long long，不然会爆掉orz。所以直接~~define int long long~~。

时间复杂度$O(mlogn)$。

## 代码：

```c++
#include <bits/stdc++.h>
#define ls (now << 1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;

const int maxn = 3e5+10;

int n, m, a[maxn], d[1000010];

struct seg_tree{
	struct nodes{
		int l, r, sum, max_num;
	}node[maxn<<2];
	void up(int now){return (void)(node[now].sum = node[ls].sum + node[rs].sum, node[now].max_num = max(node[ls].max_num, node[rs].max_num));}
	void build(int l, int r, int now){
		node[now].l = l, node[now].r = r;
		if(l == r) return (void)(node[now].sum = a[l], node[now].max_num = a[l]);
		build(l, mid, ls), build(mid+1, r, rs);
		return up(now);
	}
	void chenge(int l, int r, int now){
		if(r < node[now].l or node[now].r < l or node[now].max_num <= 2) return;
		if(node[now].l == node[now].r) return(void) (node[now].max_num = node[now].sum = d[node[now].sum]);
		chenge(l, r, ls), chenge(l, r, rs);
		return up(now);
	}
	void quary(int l, int r, int now, int &ans){
		if(r < node[now].l or node[now].r < l) return;
		if(l <= node[now].l and node[now].r <= r) return (void)(ans += node[now].sum);
		quary(l, r, ls, ans), quary(l, r, rs, ans);
		return up(now);
	}
}tree;

signed main(){
	for(int i = 1; i <= 1000000; i ++){
		for(int j = i; j <= 1000000; j += i){
			d[j] ++;
		}
	}
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
	tree.build(1, n, 1);
	for(int i = 1, x, y, z; i <= m; i ++){
		scanf("%lld%lld%lld", &x, &y, &z);
		if(x&1) tree.chenge(y, z, 1);
		else{
			int ans = 0;
			tree.quary(y, z, 1, ans);
			printf("%lld\n", ans);
		}
	}
	return 0;
}
```
[安利一下博客qwq](https://www.cnblogs.com/Vanyun/p/13679377.html)


---

## 作者：Plozia (赞：1)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/111894223)

线段树好题。

首先，如果做过 [P4145 上帝造题的七分钟2 / 花神游历各国](https://www.luogu.com.cn/problem/P4145) ，那么这道题还是十分好想的。

我们需要意识到一个问题：对于 $1,2$ 这两个数而言，我们对它们修改是没有意义的，$1$ 还是 $1$，$2$ 还是 $2$。

那么我们再想想，对于 $a_i$ 几次操作之后就会变成 $1,2$ 呢？

我们可以 ~~使用数学方法~~ 打一个暴力程序算一算，发现最多不超过 6 次。

于是这不就变成上面那道题了吗？

我们先预处理出 $d_i$，然后线段树维护两个值 $sum,max$，在修改操作的时候如果 $max$ 为 $1$ 或 $2$，那么跳过不修改；否则直接暴力修改即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL Max(LL fir, LL sec) {return (fir > sec) ? fir : sec;}

const int MAXN = 3e5 + 10, MAXA = 1e6 + 10;
int n, m, a[MAXN], cnt[MAXA];
struct node
{
	int l, r;
	LL sum, maxn;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define m(p) tree[p].maxn
}tree[MAXN << 2];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) {s(p) = m(p) = a[l]; return ;}
	int mid = (l(p) + r(p)) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	s(p) = s(p << 1) + s(p << 1 | 1);
	m(p) = Max(m(p << 1), m(p << 1 | 1));
}

void change(int p, int l, int r)
{
	if (l(p) == r(p)) {s(p) = m(p) = cnt[s(p)]; return ;}
	if (m(p) == 2 || m(p) == 1) return ;
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) change(p << 1, l, r);
	if (r > mid) change(p << 1 | 1, l, r);
	s(p) = s(p << 1) + s(p << 1 | 1);
	m(p) = Max(m(p << 1), m(p << 1 | 1));
}

LL ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return s(p);
	int mid = (l(p) + r(p)) >> 1; LL val = 0;
	if (l <= mid) val += ask(p << 1, l, r);
	if (r > mid) val += ask(p << 1 | 1, l, r);
	return val;
}

int main()
{
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	build(1, 1, n);
	for (int i = 1; i <= 1000000; ++i)
		for (int j = i; j <= 1000000; j += i)
			cnt[j]++;
	for (int i = 1; i <= m; ++i)
	{
		int opt = read(), l = read(), r = read();
		if (opt == 1) change(1, l, r);
		else printf("%lld\n", ask(1, l, r));
	}
	return 0;
}
```

---

## 作者：Ame__ (赞：1)

### 题目描述
维护一个长度为$n$序列，支持对一段区间将其所有元素换成其正约数个数，支持区间求和，$m$组询问

对于$1\le n,m\le 3\times 10^5$，对于序列元素$1\le a_{i}\le 10^6$

### 解题思路

一看维护区间修改区间求和想到线段树，区间求和很好办，但是第一个貌似很棘手，考虑正约数个数$\tau$是一个积性函数，数据范围$1\le a_{i}\le 10^6$，因此我们可以用线性筛将最大元素内的所有$\tau$值筛出来然后修改时候直接修改即可。

这样暴力修改部分点会$T$，但是卡卡常数貌似可过。

考虑我们什么操作是多余的，对于一段区间，若是全为$1$或$2$，我们在修改的时候可以直接跳过，因此再维护一个区间最大值，修改的时候若最大值小于$3$直接忽略就可以

### $\begin{aligned}\mathcal{Code}\end{aligned}$

```cpp
#include<bits/stdc++.h>
    
#define LL long long
    
#define _ 0
    
using namespace std;
    
/*Grievous Lady*/
    
const int BUF_SIZE = 1 << 12;
    
char buf[BUF_SIZE] , *buf_s = buf , *buf_t = buf + 1;
    
#define PTR_NEXT() \
{ \
    buf_s ++; \
    if(buf_s == buf_t) \
    { \
        buf_s = buf; \
        buf_t = buf + fread(buf , 1 , BUF_SIZE , stdin); \
    } \
}
    
template <typename _m_> void mian(_m_ & _n_){
    int _x_ = 0 , _nega_ = 0;
    while(*buf_s != '-' && !isdigit(*buf_s)) PTR_NEXT(); if(*buf_s == '-'){_nega_ = 1; PTR_NEXT();}
    while(isdigit(*buf_s)){_x_ = _x_ * 10 + *buf_s - '0'; PTR_NEXT();} if(_nega_) _x_ = -_x_; (_n_) = (_x_);
}
    
const int kato = 1e6 + 10;

int prime[kato] , tau[kato] , num[kato];

LL cnt , max_;

bool ispri[kato];

inline void pri(int n){
    for(int i = 2;i <= n;i ++){
        if(!ispri[i]){
            prime[++ cnt] = i;
            num[i] = 1;
            tau[i] = 2;
        }
        for(int j = 1;j <= cnt && i * prime[j] <= n;j ++){
            ispri[i * prime[j]] = 1;
            if(i % prime[j] == 0){
                num[i * prime[j]] = num[i] + 1;
                tau[i * prime[j]] = tau[i] / num[i * prime[j]] * (num[i * prime[j]] + 1);
                break;
            }
            num[i * prime[j]] = 1;
            tau[i * prime[j]] = tau[i] * tau[prime[j]];
        }
    }
}

struct tree{
    protected:

        struct node{
            node *ch[2];
            int l , r;
            LL sum , tag;
            node(int l = 0 , int r = 0 , LL sum = 0 , LL tag = 0): l(l) , r(r) , sum(sum) , tag(tag){
                ch[0] = ch[1] = NULL;
            }
            inline int mid(){
                return (l + r) >> 1;
            }
            inline void up(){
                sum = ch[0] -> sum + ch[1] -> sum;
                tag = max(ch[0] -> tag , ch[1] -> tag);
            }
        }*root;

        inline void build(node *&o , int l , int r){
            o = new node(l , r);
            if(l == r){
                mian(o -> sum);
                o -> tag = o -> sum;
                max_ = max(o -> sum , max_);
                return;
            }
            build(o -> ch[0] , l , o -> mid()); build(o -> ch[1] , o -> mid() + 1 , r);
            o -> up();
        }

        inline void Modify(node *o , int l , int r){
            if(o -> tag < 3) return;
            if(o -> l == o -> r){
                o -> tag = o -> sum = tau[o -> sum];
                return;
            }
            if(l <= o -> mid()){
                Modify(o -> ch[0] , l , r);
            }
            if(r > o -> mid()){
                Modify(o -> ch[1] , l , r);
            }
            o -> up();
        }

        inline LL ask(node *o , int l , int r){
            // if(o -> l > r || o -> r < l) return 0;
            if(l <= o -> l && o -> r <= r){
                return o -> sum;
            }
            LL res = 0;
            if(l <= o -> mid()){
                res += ask(o -> ch[0] , l , r);
            }
            if(r > o -> mid()){
                res += ask(o -> ch[1] , l , r);
            }
            return res;
        }
        
    public:

        inline void build(int n){
            build(root , 1 , n);
        }

        inline void Modify(int l , int r){
            Modify(root , l , r);
        }

        inline LL ask(int l , int r){
            return ask(root , l , r);
        }
}yuni;

int n , m , opt , l , r;

inline int Ame_(){
    mian(n) , mian(m);
    yuni.build(n);
    tau[1] = 1;
    pri(max_);
    for(; m --> 0 ;){
        mian(opt) , mian(l) , mian(r);
        if(opt == 1) yuni.Modify(l , r);
        if(opt == 2) printf("%lld\n" , yuni.ask(l , r));
    }
    return ~~(0^_^0);
}
    
int Ame__ = Ame_();
    
int main(){;}
```

-----$\begin{aligned}\mathcal{Ame}\end{aligned}$__

---

## 作者：Azazеl (赞：1)

>[题目传送门](https://www.luogu.com.cn/problem/CF920F)


------------
#### 题解
$\ \ \ \ \ \ \ $作为一个沉迷数据结构的蒟蒻，这道题真的挺不错的  

$\ \ \ \ \ \ \ $首先，题目要求我们找一个数的约数个数，这个我们预处理出来就可以了.  
~~理论上可以打表，但是太大了不能交。~~

预处理:  
```cpp
	for(int i=1;i<=1e6;i++)
    {
        for(int j=i;j<=1e6;j+=i) D[j]++;
    }
```
$\ \ \ \ \ \ \ $预处理后我们就可以开始正题了.    

$\ \ \ \ \ \ \ $其实这道题的解法和[$GSS4$](https://www.luogu.com.cn/problem/SP2713)的做法很像:**对于每一个$1$或$2$,它都是不用分解的**,所以我们在用线段树维护区间和的时候,顺便再维护一个区间最大值，**只有区间最大值大于$3$时才进行修改**

[$\mathcal{CODE}$](https://www.luogu.com.cn/paste/pqd7gyrc)  


------------
#### 题外话  
当初我的预处理写成了这个鬼样子  
```cpp
void ys(int n)
{
	for(int i=3;i<=n;i++)
	{
		ll tmp=n,ans=0;
		for(int j=1;j*j<=i;j++)
		{
			if(i%j==0)
			{
				ans++;
				if(i/j!=j) ans++;
				tmp/=j;
			}
		}
		D[i]=ans;
	}	
}
```
然后它卡出了$2min$的最劣解.

---

## 作者：KagurazakaLorna (赞：1)

首先应该看得出这是个线段树（或者分块等）...

考虑每个数都小于1e6... 它的约数个数是很小的...

（我写过程序，最多到240个）

并且我们可以预处理出来，复杂度接近于O(n * log n)

（枚举i，和i的倍数j，更新i * j）

因此对一个修改，它下降的速度是很快的...

当它下降到1 or 2的时侯，它的约数个数就是它本身...

这时就不需要修改了...

因此我们yy一下，暴力地去修改其实不会很慢...

所以可以再维护一下区间最大值...

当我们Modify到区间[head, tail]时，如果这一段区间的最大值小于3，那么就不需要再递归下去修改...

然后... 嗯... 这就是个线段树模板题...

最后... 嗯... 贴上代码：

Ps：由于本人有压行的~~好~~习惯，贴在Luogu上... 嗯...

```cpp
#include <bits/stdc++.h>
#define MAXA 1000010
#define MAXN 300010
using namespace std;
template <typename type> inline void Read(type &res) {
	res = 0; int f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) f = (ch == '-') ? (-1) : (f);
	for (; isdigit(ch); ch = getchar()) res = res * 10 + ch - '0';
	res *= f; return;
}
int cnt[MAXA], num[MAXN], n, Q;
inline int Max(int x, int y) { return (x > y) ? (x) : (y); }
inline long long Max(long long x, long long y) { return (x > y) ? (x) : (y); }
struct SegmentTree {
	long long sum[MAXN << 2]; int mx[MAXN << 2];
	inline void Build(int pos, int head, int tail) {
		if (head == tail) {	sum[pos] = mx[pos] = num[head]; return; }
		int mid = (head + tail) >> 1;
		Build(pos << 1, head, mid); Build((pos << 1) + 1, mid + 1, tail);
		sum[pos] = sum[pos << 1] + sum[(pos << 1) + 1], mx[pos] = Max(mx[pos << 1], mx[(pos << 1) + 1]);
		return;
	}
	inline void Modify(int pos, int head, int tail, int left, int right) {
		if (head == tail) { sum[pos] = mx[pos] = cnt[mx[pos]]; return; }
		int mid = (head + tail) >> 1;
		if ((left <= mid) && (mx[pos << 1] > 2)) Modify(pos << 1, head, mid, left, right);
		if ((mid < right) && (mx[(pos << 1) + 1] > 2)) Modify((pos << 1) + 1, mid + 1, tail, left, right);
		sum[pos] = sum[pos << 1] + sum[(pos << 1) + 1], mx[pos] = Max(mx[pos << 1], mx[(pos << 1) + 1]);
		return;
	}
	inline long long Query(int pos, int head, int tail, int left, int right) {
		if ((left <= head) && (tail <= right)) return sum[pos];
		int mid = (head + tail) >> 1;
		long long res = 0;
		if (left <= mid) res += Query(pos << 1, head, mid, left, right);
		if (mid < right) res += Query((pos << 1) + 1, mid + 1, tail, left, right);
		return res;
	}
} tree;
int main() {
	for (register int i = 1; i < MAXA; ++ i)
		for (register int j = 1; j * i < MAXA; ++ j) 
			++ cnt[i * j];
	Read(n), Read(Q);
	for (int i = 1; i <= n; ++ i) Read(num[i]);
	tree.Build(1, 1, n);
	while (Q --) {
		int opt, head, tail; Read(opt), Read(head), Read(tail);
		if (opt == 1) tree.Modify(1, 1, n, head, tail);
		else cout << tree.Query(1, 1, n, head, tail) << endl;
	}
	return 0;
}
```

---

## 作者：B_1168 (赞：0)

难得的A了一道紫题

容易发现，对$a_i\leq10^6$，在进行不多于$6$次$a_i=D(a_i)$操作后，$a_i$收敛到$1$或$2$。

如需实际证明，可运行以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int d[1000010],ans=0;

int query(int i,int cnt){
    if(i==1||i==2) return cnt;
    query(d[i],cnt+1);
}

int main(){
    const int maxn=1000005;
    for(int i=1;i<=maxn;i++){
        for(int j=i;j<=maxn;j+=i){
            d[j]++;
        }
    }
    for(int i=1;i<=maxn;i++){
        ans=max(ans,query(i,0));
    }
    printf("%d\n",ans);
    //ans=6
}
```

于是，可以预处理$10^6$以内$D(i)$的值，并参考[P4145 上帝造题的七分钟2 / 花神游历各国](https://www.luogu.com.cn/problem/P4145)的手段进行维护。

因为本蒟蒻不想写线段树和树状数组，便基于P4145的程序写了以下程序：

```cpp
//inspiration for the f[] array: https://www.luogu.com.cn/blog/cqbzljs/solution-cf920f
#include<bits/stdc++.h>
#define maxa 1000000
#define maxn 300005
#define maxs 600
using namespace std;

int n,m,len,f[maxs],be[maxn],pl[maxn],fa[maxn],d[maxa];

long long val_sum[maxs],val_max[maxs],a[maxn],maxx;

inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf; 
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++; 
}

inline int read(){
	int x=0,f=1;char ch=nc();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=nc();}
	while (isdigit(ch)){x=x*10+ch-48;ch=nc();}
	return x*f;
}

void upd(int from,int to){
    for(int i=from;i<=min(to,be[from]*len);i++) {
    	val_sum[be[from]]+=(d[a[i]]-a[i]),a[i]=d[a[i]];
    }
    if(be[from]!=be[to]){
        for(int i=(be[to]-1)*len+1;i<=to;i++) {
        	val_sum[be[to]]+=(d[a[i]]-a[i]),a[i]=d[a[i]];
        }
    }
    for(int i=be[from]+1;i<=be[to]-1;i++){
    	if(f[i]) continue;
    	f[i]=1;
    	for(int j=pl[i-1]+1;j<=pl[i];j++){
			val_sum[be[j]]+=(d[a[j]]-a[j]),a[j]=d[a[j]];
			if(a[j]>2) f[i]=0;
		}
    }
}

long long query_sum(int from,int to){
	long long cnt=0;
	for(int i=from;i<=min(to,be[from]*len);i++){
		cnt+=a[i];
	}
	if(be[from]!=be[to]){
        for(int i=(be[to]-1)*len+1;i<=to;i++) {
        	cnt+=a[i];
        }
    }
    for(int i=be[from]+1;i<=be[to]-1;i++) cnt+=val_sum[i];
    return cnt;
}

int main(){
	n=read(),m=read();
	len=sqrt(n);
	for(int i=1;i<=n;i++){
		be[i]=(i-1)/len+1;
		a[i]=read();
		val_sum[be[i]]+=a[i];
		val_max[be[i]]=max(val_max[be[i]],a[i]);
		maxx=max(maxx,a[i]);
		fa[i]=i;
	}
	maxx+=10;
	for(int i=1;i<=maxx;i++){
		for(int j=i;j<=maxx;j+=i){
			d[j]++;
		}
	}
	int temp=1;
	for(int i=1;i<=n;i++){
		if(be[i]!=be[i+1]){
			pl[temp]=i;
			temp++;
		}
	}
	temp--;
	while(m--){
		int op,l,r;
		op=read(),l=read(),r=read();
		if(op&1){
			upd(l,r);
		}
		else printf("%lld\n",query_sum(l,r));
	}
} 
```

虽然分块并不甚快，但胜在易写易改，也不失为一种方便的算法qwq

感谢管理审核，大佬们阅读！

---

## 作者：critnos (赞：0)

明天小学毕业考，今天改名，改名后颓一篇题解。

这篇题解主要研究时间复杂度。

这种题已经很套路了：对于每个数如果经过 $k$ 次修改就会不变，那么总时间复杂度为 $O(nk\log n)$。

现在求这个 $k$。

众所周知一个数的约数个数是 $\sqrt n$ 级别的。对于一个数 $x$，当 $x$ 充分大时 $d(x)\le \sqrt x$。

那么我们把求约数当作根号来计算。一个数经过 $\log \log n$ 次根号就会收敛。

感性理解一下：$\sqrt{a^b}=a^{\frac b 2}$。不妨把 $x$ 写成 $2^{\log x}$ 的形式，那么上面的 $\log x$ 经过 $\log \log x$ 次减半就会收敛。

然后说说自己的想法：在 $[1,n]$ 之间随机取一个数 $x$，$d(x)$ 期望是 $\log n$。结论简单请自证/doge

那么如果把 $d(x)=\log x$ 来计算，$k$ 就应当是 $\log^* x$ 了。这个函数一般 $\le 4$，可以当作常数。

但是或许随着 $x$ 变小，收敛速度会变慢？有兴趣的可以到 [这个帖子](https://www.luogu.com.cn/discuss/show/235773) 讨论。

---

## 作者：Spasmodic (赞：0)

今天时间太少，也就做了这么一道屑题/kk

### 1.题意
给你一个序列，要求支持这两种操作：

1. 区间 $a_i\rightarrow d(a_i)$
2. 区间求和

### 2.题解
首先，注意到$d(n)\le 2\sqrt n$，所以在$O(\log\log a)$次以内这个数会变为0/1。

因此我们可以在修改的时候用并查集跳过这些无用点，修改总复杂度应该是$O(n\log\log a\times f(n))$，$f(n)$代表你用的数据结构的单点修改的复杂度。

于是就转化为了一道单点修改，区间求和的数据结构题，直接使用树状数组即可。

它的双倍经验是[这题](https://www.luogu.com.cn/problem/P4145)，和本题几乎一模一样，如果看不懂也可以去看这题的题解哦。

### 3.代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=300005,S=1e6;
ll n,d[S+5],a[N],m,bit[N],id[N];
void update(ll id,ll v){for(;id<=n;id+=id&-id)bit[id]+=v;}
ll query(ll id){ll ret=0;for(;id;id-=id&-id)ret+=bit[id];return ret;}
ll find(ll x){return id[x]==x?x:id[x]=find(id[x]);}
int main(){
	for(int i=1;i<=S;i++)//这里你也可以用线性筛，不过考虑到这么做不会T，而且线性筛常数巨大，我就没用
		for(int j=i;j<=S;j+=i)
			d[j]++;
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)scanf("%lld",&a[i]),id[i]=i,update(i,a[i]);
	id[n+1]=n+1;
	for(ll k,l,r;m--;){
		scanf("%lld%lld%lld",&k,&l,&r);
		if(l>r)swap(l,r);
		if(k==2)printf("%lld\n",query(r)-query(l-1));
		else for(ll i=id[l],v;i<=r;i=id[i+1])
			v=d[a[i]],update(i,v-a[i]),a[i]=v,id[i]=(a[i]<=2?find(i+1):id[i]);
	}
	return 0;
}
```
最后求降蓝，这题就是P4145加上一个基础的d预处理而已。

---

## 作者：zsaskk (赞：0)

这道题用到了一个非常常见的$trick$

普通的线段树做法是，维护一个支持求和，求最大值的线段树，每次修改**暴力递归修改**，如果当前节点$maxn≤2$，不进行递归。

~~但由于一些原因，我没有这么写。~~



------------

这道题还可以用并查集来做。

~~众所周知~~，并查集可以用来**维护连通性**。[模板](https://www.luogu.com.cn/problem/P2391)

与链接里的那道题不同，这里我们用$fa[x]$表示要**从$x$点开始进行修改，第一个要改哪个点。**

然后在线段树上进行暴力修改。

下一个要操作的节点，就是$find(fa[x]+1)$。

注意要同步更改连通关系，当$x≤2$，就应当把$x$与$find(fa[x]+1)$合并。

------------


这道题目里的修改是将$x$改为$x$的约数个数，显然每次去求值不优，考虑**以空间换时间**，预处理出题目范围内的数的约数个数，做法类似埃氏筛。



------------

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define int long long
#define chk_digit(c) (c>='0'&&c<='9')
inline int read() {
	reg int x=0,f=1;reg char c=getchar();
	while(!chk_digit(c)) { if(c=='-') f=-1;c=getchar(); }
	while(chk_digit(c)) x=x*10+c-'0',c=getchar();
	return x*f;
} 
struct node{ int val,sum; }tr[3*100001*4];
int fa[3*100001],f[1000005],n,m,a[3*100001];
#define maxn 1000000
inline int szfind(int x) { return x==fa[x]?x:fa[x]=szfind(fa[x]); }
inline void szunion(int x,int y) { fa[y]=x; }
inline void pre() {//预处理
	fa[n+1]=n+1;
	for(reg int i=n;i>=1;--i) //并查集预处理
		if(a[i]>2) fa[i]=i;
		else fa[i]=szfind(i+1);
	for(reg int i=1;i<=maxn;++i) f[i]=1;
	for(reg int i=2;i<=maxn;++i) {//约数个数预处理
		++f[i];
		if(i*i<=maxn) ++f[i*i];//注意会爆int
		for(reg int j=i+1;j*i<=maxn;++j) f[i*j]+=2;
	}
}
#define mid (al+ar>>1)
#define lc rt<<1,al,mid
#define rc rt<<1|1,mid+1,ar 
inline void pushup(int rt) { tr[rt].sum=tr[rt<<1].sum+tr[rt<<1|1].sum; } 
inline void build(int rt,int al,int ar) {
	if(al==ar) { tr[rt].val=tr[rt].sum=a[al];return; }
	build(lc),build(rc),pushup(rt);
}
inline int update(int rt,int al,int ar,int x) {
	int y=0;
	if(al==ar) { y=tr[rt].val;tr[rt].val=tr[rt].sum=f[tr[rt].val];return y; }
	if(x>mid) y=update(rc,x);else y=update(lc,x);
	pushup(rt);return y;
}
inline int query(int rt,int al,int ar,int ql,int qr) {
	if(al>qr||ar<ql) return 0;
	if(al>=ql&&ar<=qr) return tr[rt].sum;
	return query(lc,ql,qr)+query(rc,ql,qr);
}//以上为线段树
signed main() {
	n=read(),m=read();
	for(reg int i=1;i<=n;++i) a[i]=read();
	pre();build(1,1,n);
	for(reg int i=1;i<=m;++i) {
		int opt=read(),x=read(),y=read();
		if(opt==1) {
			reg int j=szfind(x);
			for(;j<=y;j=szfind(j+1)) {
				int z=update(1,1,n,j);//返回更改后的值
				if(z<=2) fa[j]=szfind(j+1);//动态维护连通性
			}
		} 
		else printf("%lld\n",query(1,1,n,x,y));
	}
}
```



---

## 作者：Seanq (赞：0)

**文章总数90祭+CF920F SUM and REPLACE**    
%%%   
做不动的线段树   
就是要求：   
1.将l-r之间的每个数替换成它们的约数个数    
2.区间求和    
考虑暴力   
~~明显不行~~     
考虑数据结构   
线段树    
暴力单点修改即可    
可以证明时间复杂度≈MlogN    
std:   
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=330000;
ll D[1000005]={0};
int n,m; 
ll a[N];
ll t[N*4];
ll maxn[N*4];
void push(int num){
	t[num]=t[num<<1]+t[num<<1|1];
	maxn[num]=max(maxn[num<<1],maxn[num<<1|1]);
}
void build(int l,int r,int num){
	if(l==r){
		maxn[num]=a[l];
		t[num]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,num<<1);
	build(mid+1,r,num<<1|1);
	push(num);
}
void add(int l,int r,int num,int L,int R){
	if(l>R||r<L) return;
	if(maxn[num]<=2) return;
	if(l>=L&&r<=R&&l==r){
		t[num]=D[t[num]];
		maxn[num]=t[num];
		return;
	}
	int mid=(l+r)>>1;
	add(l,mid,num<<1,L,R);
	add(mid+1,r,num<<1|1,L,R);
	push(num);
}
ll serch(int l,int r,int num,int L,int R){
	if(l>R||r<L) return 0;
	if(l>=L&&r<=R) return t[num];
	int mid=(l+r)>>1;
	return serch(l,mid,num<<1,L,R)+serch(mid+1,r,num<<1|1,L,R);
}
int main(){/* 
	for(int i=1;i<=1000000;i++){//预处理D数组:法1，n*sqrt(n) 
		D[i]=1;
		if(check(i)) D[i]=2;
		else{
			fenjie(i);
		}
	}*/
	for(int i=1;i<=1000000;i++){
		for(int j=1;i*j<=1000000;j++)
			D[i*j]++;
	} 
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	build(1,n,1);
	while(m--){
		int opt=0;
		scanf("%d",&opt);
		if(opt==1){
			int L,R;
			scanf("%d%d",&L,&R); 
			add(1,n,1,L,R);
		}
		else{
			int L,R;
			scanf("%d%d",&L,&R); 
			printf("%lld\n",serch(1,n,1,L,R));
		}
	}
	return 0;
}
```

---

## 作者：XiaoX (赞：0)

### 分块大法好！！

和 [P4145 上帝造题的七分钟2 / 花神游历各国](https://www.luogu.org/problemnew/show/P4145)
类似，发现让一个数一直变成它的约数个数，几次之后就会变成
$2$（$1$除外），块内全为$2/1$后就不再操作该块，分块维护区间和即可。

这里再介绍一种$O(nlogn)$ 预处理约数个数的方法，用$d$的倍数$d,2d,3d...,[n/d]*d$更新约数个数的数组（个人感觉比较好写）

Code：（注意细节）
```
#include<iostream>
#include<cstdio>
#include<cmath>
#define maxnum 1000005
#define LL long long 
#define N 300005
using namespace std;
int n,m,blo;
int bl[N],l[1005],r[1005],tag[1005];//tag是统计原来就是1的个数
LL sum[1005],a[N];//大块和,原数组
bool flag[1005];//标记是否全为2/1
int rd()
{
	char ch=getchar();
	int res=0;
	for(;!isdigit(ch);ch=getchar());
	for(;isdigit(ch);ch=getchar())
		res=(res<<3)+(res<<1)+ch-'0';
	return res;
}
int d[maxnum+1];
void pre()
{
	for(int i=1;i<=maxnum;i++)
		for(int j=1;j<=maxnum/i;j++)
			d[i*j]++;
}//预处理
void change(int ll,int rr)
{
	if(bl[ll]==bl[rr]){
		if(flag[bl[ll]]) return;
		for(int i=ll;i<=rr;i++)
			sum[bl[ll]]-=a[i],a[i]=d[a[i]],sum[bl[ll]]+=a[i];
		if(sum[bl[ll]]==1ll*(r[bl[ll]]-l[bl[ll]]+1)*2-tag[bl[ll]])//sum如果等于 全是2 减去1的个数，说明全是2/1
			flag[bl[ll]]=1;
	}
	else {
		for(int i=ll;i<=r[bl[ll]];i++)
			sum[bl[ll]]-=a[i],a[i]=d[a[i]],sum[bl[ll]]+=a[i];
		if(sum[bl[ll]]==1ll*(r[bl[ll]]-l[bl[ll]]+1)*2-tag[bl[ll]])
			flag[bl[ll]]=1;	
		for(int i=l[bl[rr]];i<=rr;i++)
			sum[bl[rr]]-=a[i],a[i]=d[a[i]],sum[bl[rr]]+=a[i];
		if(sum[bl[rr]]==1ll*(r[bl[rr]]-l[bl[rr]]+1)*2-tag[bl[rr]])
			flag[bl[rr]]=1;	
		for(int i=bl[ll]+1;i<bl[rr];i++)
		{
			if(flag[i]) continue;
			for(int j=l[i];j<=r[i];j++) 
				sum[i]-=a[j],a[j]=d[a[j]],sum[i]+=a[j];
			if(sum[i]==1ll*(r[i]-l[i]+1)*2-(LL)tag[i])
				flag[i]=1;
		}
	}
}
LL query(int ll,int rr)
{
	LL res=0;
	if(bl[ll]==bl[rr]){
		for(int i=ll;i<=rr;i++)
			res+=a[i];
	}
	else {
		for(int i=ll;i<=r[bl[ll]];i++) res+=a[i];
		for(int i=l[bl[rr]];i<=rr;i++) res+=a[i];
		for(int i=bl[ll]+1;i<bl[rr];i++) 
			res+=sum[i];
	}
	return res;
}
int main ()
{
	n=rd();m=rd();
	blo=sqrt(n);
	pre();
	for(int i=1;i<=n;i++)	
	{
		a[i]=(LL)rd();
		bl[i]=(i-1)/blo+1;
		if(a[i]==1) tag[bl[i]]++;
		sum[bl[i]]+=a[i];
	}
	int num;
	if(n%blo) num=n/blo+1;
	else num=n/blo;
	for(int i=1;i<=num;i++)
	{
		l[i]=(i-1)*blo+1;
		r[i]=min(n,i*blo);
	}
	while(m--)
	{
		int k=rd(),ll=rd(),rr=rd();
		if(k==1){
			change(ll,rr);
		}
		else {
			printf("%I64d\n",query(ll,rr));
		}
	}
}
```
安利[Blog](https://www.luogu.org/blog/XiaoXkkk/#)

---

## 作者：yybyyb (赞：0)

既然要求$d(x)$，那就提前筛出来

发现$d(1)=1,d(2)=2$

所以维护区间最大值

如果区间最大值$<=2$就不要更新

否则暴力更新整个区间

因为每个数只会被修改$log$次（也许吧。。。）

总的复杂度就对了

[强行插入博客](http://www.cnblogs.com/cjyyb/p/8410033.html)
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define MAX 1000000
#define ll long long
#define lson (now<<1)
#define rson (now<<1|1)
inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
bool zs[MAX+1];
int pri[MAX],tot;
int d[MAX+1],pn[MAX+1];
int n,m;
void pre()
{
    zs[1]=true;d[1]=1;
    for(int i=2;i<=MAX;++i)
    {
        if(!zs[i])pri[++tot]=i,d[i]=2,pn[i]=1;
        for(int j=1;j<=tot&&i*pri[j]<=MAX;++j)
        {
            zs[i*pri[j]]=true;
            if(i%pri[j])d[i*pri[j]]=d[i]*2,pn[i*pri[j]]=1;
            else{d[i*pri[j]]=d[i]/(pn[i]+1)*(pn[i]+2);pn[i*pri[j]]=pn[i]+1;break;}
        }
    }
}
struct Node
{
    int ma;
    ll s;
}t[MAX<<2];
void Build(int now,int l,int r)
{
    if(l==r){t[now].ma=t[now].s=read();return;}
    int mid=(l+r)>>1;
    Build(lson,l,mid);Build(rson,mid+1,r);
    t[now].s=t[lson].s+t[rson].s;
    t[now].ma=max(t[lson].ma,t[rson].ma);
}
void Modify(int now,int l,int r,int L,int R)
{
    if(t[now].ma<=2)return;
    if(l==r){t[now].s=t[now].ma=d[t[now].ma];return;}
    int mid=(l+r)>>1;
    if(L<=mid)Modify(lson,l,mid,L,R);
    if(R>mid)Modify(rson,mid+1,r,L,R);
    t[now].s=t[lson].s+t[rson].s;
    t[now].ma=max(t[lson].ma,t[rson].ma);
}
ll Query(int now,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)return t[now].s;
    ll ret=0;
    int mid=(l+r)>>1;
    if(L<=mid)ret+=Query(lson,l,mid,L,R);
    if(R>mid)ret+=Query(rson,mid+1,r,L,R);
    return ret;
}
int main()
{
    n=read();m=read();pre();
    Build(1,1,n);
    while(m--)
    {
        int opt=read(),l=read(),r=read();
        if(opt==1)Modify(1,1,n,l,r);
        else printf("%I64d\n",Query(1,1,n,l,r));
    }
    return 0;
}
```

---

