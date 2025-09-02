# GSS2 - Can you answer these queries II

## 题目描述

Being a completist and a simplist, kid Yang Zhe cannot solve but get Wrong Answer from most of the OI problems. And he refuse to write two program of same kind at all. So he always failes in contests.

When having a contest, Yang Zhe looks at the score of every problems first. For the problems of the same score, Yang Zhe will do only one of them. If he's lucky enough, he can get all the scores wanted.

Amber is going to hold a contest in SPOJ. She has made a list of _N_ candidate problems, which fit Yang Zhe very well. So Yang Zhe can solve any problem he want. Amber lined up the problems, began to select. She will select a subsequence of the list as the final problems. Being A girl of great compassion, she'd like to select such a subsequence (can be empty) that Yang Zhe will get the maximal score over all the possible subsequences.

Amber found the subsequence easily after a few minutes. To make things harder, Amber decided that, Yang Zhe can take this contest only if Yang Zhe can answer her _Q_ questions. The question is: if the final problems are limited to be a subsequence of _list_\[_X_.._Y_\] (1 <= _X_ <= _Y_ <= N), what's the maximal possible score Yang Zhe can get?

As we know, Yang Zhe is a bit idiot (so why did he solve the problem with a negative score?), he got Wrong Answer again... Tell him the correct answer!

## 样例 #1

### 输入

```
9
4 -2 -2 3 -1 -4 2 2 -6
3
1 2
1 5
4 9```

### 输出

```
4
5
3```

# 题解

## 作者：ErkkiErkko (赞：74)

题意不过只是比GSS1多了几个字而已，难度却把GSS1甩得望尘莫及。

给出n个数，q次询问，求最大子段和（可为空），相同的数只算一次。

说到相同的只算一次这一条件，有点像[SDOI2009]HH的项链，但是本题不再是简简单单的统计个数，而是求最大子段和。

由于题目条件，GSS1的合并Lmax，Midmax，Rmax的方法以不再适用，我们必须另辟蹊径。

做题经验告诉我们，要处理有关区间去重的问题时，我们常用到离线算法，本题亦是如此。

仍然是用线段树，只不过我们要把序列中的元素一个个添加进去。

将所有询问按r排序，在最终处理询问到以r为区间右边界时，将a[r]添加到线段树。

线段树每个节点维护4个值，sum,hismax,sumtag,hismaxtag。

假设现在处理到以y为区间右边界的询问了，那么，对于叶结点：

sum表示从这个叶结点所对应的原序列的下标x到y的所有元素和，及a[x]+a[x+1]+a[x+2]+...+a[y]，

hismax表示sum的历史最大值（最小为0）。

对于内部节点：

sum表示左右儿子的sum的最大值，

hismax表示左右儿子的hismax的最大值。

另外的，利用sumtag和hismaxtag作为延迟标记实现单次修改/询问O(logn)复杂度，具体意义参考代码。

如何向线段树添加元素？

记录序列中第i个元素上一个相同元素的位置pre[i]，添加元素是[pre[i]+1,i]区间加a[i]即可。

如何查询？

查询[l,r]的hismax。

要特别注意pushdown()函数的更新顺序，非常容易弄错。

还有各种实现细节，一定要特别注意。

线段树不可多得的好题。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
inline LL read(){
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN=100005;
struct Node{
    LL sum,hix,stag,htag;
    Node(){
        sum=hix=stag=htag=0;
    }
    friend Node operator + (Node lf,Node rt){
        Node res;
        res.sum=max(lf.sum,rt.sum);
        res.hix=max(lf.hix,rt.hix);
        return res;
    }
}b[MAXN*4];
struct Qst{
    int l,r,id;
}q[MAXN];
bool cmp(Qst x,Qst y){
    return x.r<y.r;
}
int n,m,cur[MAXN*2],pre[MAXN],ql,qr;LL a[MAXN],ans[MAXN],k;
#define mid ((l+r)>>1)
#define lc (o<<1)
#define rc ((o<<1)|1)
void pushup(int o){
    b[o]=b[lc]+b[rc];
}
void pushdown(int o){//注意更新先后顺序 
    b[lc].hix=max(b[lc].hix,b[lc].sum+b[o].htag);
    b[rc].hix=max(b[rc].hix,b[rc].sum+b[o].htag);
    b[lc].sum+=b[o].stag;
    b[rc].sum+=b[o].stag;
    b[lc].htag=max(b[lc].htag,b[lc].stag+b[o].htag);
    b[rc].htag=max(b[rc].htag,b[rc].stag+b[o].htag);
    b[lc].stag+=b[o].stag;
    b[rc].stag+=b[o].stag;
    b[o].stag=b[o].htag=0;
}
void upd(int o,int l,int r){
    if(ql<=l&&r<=qr){
        b[o].sum+=k;
        b[o].hix=max(b[o].hix,b[o].sum);
        b[o].stag+=k;
        b[o].htag=max(b[o].htag,b[o].stag);
        return;
    }
    pushdown(o);
    if(mid>=ql) upd(lc,l,mid);
    if(mid<qr) upd(rc,mid+1,r);
    pushup(o);
}
Node query(int o,int l,int r){
    if(ql<=l&&r<=qr) return b[o];
    pushdown(o);
    if(mid<ql) return query(rc,mid+1,r);
    else if(mid>=qr) return query(lc,l,mid);
    else return query(lc,l,mid)+query(rc,mid+1,r);
}
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        pre[i]=cur[a[i]+(int)1e5];
        cur[a[i]+(int)1e5]=i;
    }
    m=read();
    for(int i=1;i<=m;i++){
        q[i].l=read(),q[i].r=read();
        q[i].id=i;
    }
    sort(q+1,q+m+1,cmp);
    int j=1;
    for(int i=1;i<=n;i++){
        ql=pre[i]+1,qr=i,k=a[i];
        upd(1,1,n);
        for(;j<=m&&q[j].r<=i;j++){
            ql=q[j].l,qr=q[j].r;
            ans[q[j].id]=query(1,1,n).hix;
        }
    }
    for(int i=1;i<=m;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：x义x (赞：40)

[$$\color{green}\Large\texttt{『菜鸡的blog』}$$](https://www.luogu.org/blog/zyxxs/)

如果你觉得这篇题解还可以的话，也可以来看看我的其他博客qwq

------------

此题与[GSS1](https://www.luogu.org/problem/SP1043)的区别在于选出的子段中，两个重复元素只算一次。

对于GSS1，我们的线段树做法一般是对每个节点维护区间最大子段、区间和、区间最大前缀、区间最大后缀。显然这种方式很难判断有无重复的元素，所以我们必须另寻别的方法。

##### 我们先引入贡献这个东西

我们考虑对于每个$l$维护$[l,i]$的区间和$A[l]+A[l+1]+...+A[i]$去掉重复元素的影响之后的值。（$i$为最近一次插入的元素的位置，马上就会介绍）

这个称为$l$的贡献。

先别问这个东西有什么用……我们慢慢讲

------------

##### 如何保证重复元素只算入一次贡献

我们从前往后依次加元素，如果一个元素$A[i]$在前面的$pre[A[i]]$位置已经出现过了，那么就不让$A[i]$的加入对区间$[\ 1,pre[A[i]]\ ]$中元素的贡献产生影响。

那么如何让$A[i]$对$[\ pre[A[i]]+1,i-1\ ]$**产生**影响呢？

对于$pre[A[i]]<l<i$，我们都在$l$的原贡献序列$A[l]+A[l+1]+...+A[i-1]$后面接一个$A[i]$。

总结一下：其实我们是在进行**区间加**，把$A[i]$加到区间$[\ pre[A[i]]+1,i-1\ ]$上。

------------

##### 如何处理询问

对于询问$(j,i)$，我们就在**刚刚加入**$A[i]$之后查询$\max(A[l]+A[l+1]+...+A[r])\quad(j\le l\le r\le i)$。

注意到**如果$l$固定**，那么其实$\max(A[l]+A[l+1]+...+A[r])\quad(l\le r\le i)$就是$l$贡献的**历史最大值**。

（这样的$r$满足$r\le i$，所以肯定已经加入过了，$A[l]+A[l+1]+...+A[r]$就是**当时**$l$的贡献）。

总结一下：询问$(j,i)$就是在刚刚插入$A[i]$之后询问区间$[\ j,i\ ]$的历史贡献最大值。

------------

##### 可以加入线段树了

区间加，区间查询，显然这是线段树擅长的东西。

我们需要四个tag：

- **管辖的区间的贡献的最大值**``Max``

- **上一个tag的历史最大值（指的是从最开始到现在）**``HisMax``

- **区间加的lazytag**``Lzy``

- **lazytag的历史最大值（指的是从上次pushdown到现在）**``HisLzy``。

注意``Query()``的答案也要用类似``push_up()``的方式合并，所以建议写成结构体，``push_up()``我写成了重载的``+``。

``push_down()``细节较多，建议好好看一下。

然后是跑的慢死的代码。自我感觉上面已经讲得很清楚了所以就不注释了。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int N,M;
int A[100005];
int pre[2000005];

struct node{
	ll Max,HisMax,Lzy,HisLzy;
	node operator +(const node b)const{
		node c;c.Max=max(Max,b.Max);c.HisMax=max(HisMax,b.HisMax);
		c.HisLzy=c.Lzy=0;
		return c;
	}
}K[400005];

void push_down(int x){
	K[x<<1].HisMax=max(K[x<<1].HisMax,K[x<<1].Max+K[x].HisLzy);
	K[x<<1].HisLzy=max(K[x<<1].HisLzy,K[x<<1].Lzy+K[x].HisLzy);
	K[x<<1].Max+=K[x].Lzy;
	K[x<<1].Lzy+=K[x].Lzy;
	K[x<<1|1].HisMax=max(K[x<<1|1].HisMax,K[x<<1|1].Max+K[x].HisLzy);
	K[x<<1|1].HisLzy=max(K[x<<1|1].HisLzy,K[x<<1|1].Lzy+K[x].HisLzy);
	K[x<<1|1].Max+=K[x].Lzy;
	K[x<<1|1].Lzy+=K[x].Lzy;
	
	K[x].Lzy=K[x].HisLzy=0;
}

void Update(int x,int l,int r,int L,int R,ll k){
	if(L<=l&&r<=R){
		K[x].Max+=k;K[x].HisMax=max(K[x].HisMax,K[x].Max);
		K[x].Lzy+=k;K[x].HisLzy=max(K[x].HisLzy,K[x].Lzy);
		return;
	}
	push_down(x);
	int mid=(l+r)>>1;
	if(L<=mid) Update(x<<1,l,mid,L,R,k);
	if(R>mid) Update(x<<1|1,mid+1,r,L,R,k);
	K[x]=K[x<<1]+K[x<<1|1];
	return;
}

node Query(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return K[x];
	push_down(x);
	int mid=(l+r)>>1;
	if(R<=mid) return Query(x<<1,l,mid,L,R);
	if(L>mid) return Query(x<<1|1,mid+1,r,L,R);
	return Query(x<<1,l,mid,L,R)+Query(x<<1|1,mid+1,r,L,R);
}

int L[100005],R[100005],id[100005];
node Ans[100005];
bool cmp(int a,int b){
	return R[a]<R[b];
}

int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%d",&A[i]);
	scanf("%d",&M);
	for(int i=1;i<=M;i++) scanf("%d%d",&L[i],&R[i]),id[i]=i;
	sort(id+1,id+M+1,cmp);
	
	int j=1;
	for(int i=1;i<=N;i++){
		Update(1,1,N,pre[A[i]+100000]+1,i,A[i]);
		pre[A[i]+100000]=i;
		while(R[id[j]]==i&&j<=M) Ans[id[j]]=Query(1,1,N,L[id[j]],R[id[j]]),j++;
	}
	for(int i=1;i<=M;i++) printf("%lld\n",Ans[i].HisMax);
	
	return 0;
}

```


---

## 作者：Plozia (赞：17)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/111566557)

[GSS2](https://www.luogu.com.cn/problem/SP1557)

求最大子段和是件容易事。去重之后再求就不是件容易事了。

---

1. **我们需要维护什么？**

显然的， GSS1 中前后缀维护已经变得不可行，所以我们需要另行他法。 

而这类问题离线，又要去重的题目有一个固定的套路：离线询问，逐个击破。

啥意思？针对这道题，我们首先在 $n$ 上建立一棵空树（除了 $l(p),r(p)$ 啥都没有）。然后考虑去重。

为了去重，我们总需要知道在 $a_i$ 前面且与它相等的数在哪个位置吧？于是我们需要预先处理出 $pre_i$ 表示上一个与 $a_i$ 相同的数的位置。

然后我们将所有询问离线，以右端点为关键字升序排序（左端点无所谓）。

这样做有什么好处吗？我们在离线处理询问的时候，如果以 $i$ 为右端点的询问已经全部处理完了，那么我们后面就可以放心的去重了。

那么又如何处理答案呢？

首先，对于第 $i$ 个位置 $a_i$ ，我们针对 $[pre_i+1,a_i]$ 区间做一次区间加法。

比如现在有这样一个序列：`1 2 3 4 5 6 5 7`

那么前 6 个数加完之后线段树的区间变成了：`21 20 18 15 11 6 0 0`

此时 $pre_7 = 5$。

然后我们对 $[5 + 1, 7]$ 做一次区间加法之后有 `21 20 18 15 11 11 5 0`

此时你会惊奇的发现 **我们实际上是对序列进行了自动去重。**

然后我们又要维护什么呢？

四个值：$sum,maxn,lazy\_sum,lazy\_maxn$。（简写为 $s(p),m(p),ls(p),lm(p)$）

$s(p)$ 为这个序列的最大子段和。

$m(p)$ 为 $s(p)$ 出现过的最大和（历史最大和，注意这跟吉老师线段树没关系）。

$ls(p)$ 是 $s(p)$ 的 lazy_tag。

$lm(p)$ 是 $m(p)$ 的lazy_tag。

所以我们维护完了~

---

2. **线段树的每个叶子节点是什么？**

就是上文所述的区间

---

3. **需要 lazy_tag 吗？lazy_tag 又要维护什么呢？** 

需要一个加法 lazy_tag，一个最大子段和 lazy_tag。

---

4. **要不要重载运算符？**

不需要。

---

5. **最后又要怎么修改？怎么查询？**

重点！

先看 $s(p)$ 。

如果是加法，那么直接加即可。

**如果是合并左右两个区间，我们需要做的是求最大值而不是合并。**

为什么不需要跟 GSS1 一样弄 $a(p),p(p)$ ？原因很简单，**因为我们左右儿子的区间是连续的。**

$m(p)$ 好维护，同样求最大值。

$ls(p),lm(p)$ 在区间修改的时候维护，但是合并左右两个区间的时候不要动。

我们再看看怎么查询。

对于区间 $[l,r]$ 的询问，我们直接求 $[l,r]$ 的最大子段和即可。为什么不需要做处理？还是因为左右儿子的区间是连续的。

---

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5 + 10;
int n, m, a[MAXN], ans[MAXN], pre[MAXN], las[MAXN << 2];
struct node
{
	int l, r, sum, maxn, lazy_sum, lazy_maxn;
	#define l(p) tree[p].l
	#define r(p) tree[p].r
	#define s(p) tree[p].sum
	#define m(p) tree[p].maxn
	#define ls(p) tree[p].lazy_sum
	#define lm(p) tree[p].lazy_maxn
}tree[MAXN << 2];
struct query
{
	int l, r, id;
}q[MAXN];

int Max(int fir, int sec) {return (fir > sec) ? fir : sec;}

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

bool cmp(const query &fir, const query &sec)
{
	if (fir.r ^ sec.r) return fir.r < sec.r;
	return fir.l < sec.l;
}

void build(int p, int l, int r)
{
	l(p) = l, r(p) = r;
	if (l == r) return ;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
	return ;
}

void spread(int p)
{
	m(p << 1) = Max(m(p << 1), s(p << 1) + lm(p));
	s(p << 1) += ls(p);
	lm(p << 1) = Max(lm(p << 1), ls(p << 1) + lm(p));
	ls(p << 1) += ls(p);
	m(p << 1 | 1) = Max(m(p << 1 | 1), s(p << 1 | 1) + lm(p));
	s(p << 1 | 1) += ls(p);
	lm(p << 1 | 1) = Max(lm(p << 1 | 1), ls(p << 1 | 1) + lm(p));
	ls(p << 1 | 1) += ls(p);
	lm(p) = ls(p) = 0;
}

void change(int p, int l, int r, int k)
{
	if (l(p) >= l && r(p) <= r)
	{
		s(p) += k; m(p) = Max(m(p), s(p));
		ls(p) += k; lm(p) = Max(lm(p), ls(p));
		return ;
	}
	spread(p);
	int mid = (l(p) + r(p)) >> 1;
	if (l <= mid) change(p << 1, l, r, k);
	if (r > mid) change(p << 1 | 1, l, r, k);
	s(p) = Max(s(p << 1), s(p << 1 | 1));
	m(p) = Max(m(p << 1), m(p << 1 | 1));
}

int ask(int p, int l, int r)
{
	if (l(p) >= l && r(p) <= r) return m(p);
	spread(p);
	int mid = (l(p) + r(p)) >> 1; int val = -0x7f7f7f7f;
	if (l <= mid) val = Max(val, ask(p << 1, l, r));
	if (r > mid) val = Max(val, ask(p << 1 | 1, l, r));
	return val;
}

signed main()
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i)
	{
		pre[i] = las[a[i] + 100000];
		las[a[i] + 100000] = i;
	}
	build(1, 1, n);
	m = read();
	for (int i = 1; i <= m; ++i) {q[i].l = read(); q[i].r = read(); q[i].id = i;}
	sort(q + 1, q + m + 1, cmp);
	for (int i = 1, j = 1; i <= n; ++i)
	{
		change(1, pre[i] + 1, i, a[i]);
		for (; j <= m && q[j].r == i; ++j)
			ans[q[j].id] = ask(1, q[j].l, q[j].r);
	}
	for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：FlyInTheSky (赞：9)

线段树离线好题

考虑这题相同的数只算一次，也就是颜色问题，我们可以从颜色思考，可以发现能离线。

我们将询问**按右端点排序**，然后**从左到右扫描**到$i$，然后线段树每个节点$j$记录$\text{sum}(j)=\sum\limits_{j + 1 \leq k \leq i} a_k$，即我们维护的线段树每个节点都是区间$[j+1,i]$的值，我们维护的**线段树实际上是区间套上了区间**。

先不考虑颜色不同的情况，我们每次扫描到$i$更新，相当于是在线段树上$[1,i]$更新，然后处理$r=i$的询问，答案显然是$\max\limits_{l \leq j \leq r} (\text{sum}(j))$，但是好像不太正确，因为不一定右端点在$r$最优。所以我们要记录整个过程中的最大值 (历史最大值)。

考虑维护
- `max_now`, 当前区间$\max \text{sum}(j)$
- `lazy_now`,当前区间更新标记
- `max_old`, 当前区间历史最大值
- `lazy_old`,当前区间历史最大更新标记

`now`的就按照常规线段树维护最大值的方法来更新

然后`update`时
```c++
lazy_now[o] += v;
max_now[o] += v; // now 按照常规线段树维护最大值的方法来更新
chkmax(lazy_old[o], lazy_now[o]);
chkmax(max_old[o], max_now[o]); // 更新历史最优值
```
`pushdown`时
```c++
chkmax(max_old[lc], max_now[lc] + lazy_old[o]);
chkmax(max_old[rc], max_now[rc] + lazy_old[o]);
chkmax(lazy_old[lc], lazy_now[lc] + lazy_old[o]);
chkmax(lazy_old[rc], lazy_now[rc] + lazy_old[o]); // 更新历史最优值

max_now[lc] += lazy_now[o];
max_now[rc] += lazy_now[o];
lazy_now[lc] += lazy_now[o];
lazy_now[rc] += lazy_now[o];  // now 按照常规线段树维护最大值的方法来更新
		
lazy_now[o] = lazy_old[o] = 0;
```

值得注意的是，为什么我们用`lazy_now[rc] + lazy_old[o]`, `max_now[rc] + lazy_old[o]`而不是都用`old`。因为这样会导致最大字段和不连续。

如果考虑去重的话，那么每个数字记录他前一个出现在$\text{pre}_i$，然后每次更新$[\text{pre}_i + 1, i]$即可

```c++
#include<cstdio> 
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<queue>
#include<vector>
#include<set>
#define ms(i, j) memset(i, j, sizeof i)
#define LL long long
#define db double
#define fir first
#define sec second
#define mp make_pair
using namespace std;

namespace flyinthesky {
	
	const LL MAXN = 100000 + 5, BS = 100000;
	
	LL chkmax(LL &x, LL y) {return x = (x > y) ? x : y;}
	LL chkmin(LL &x, LL y) {return x = (x < y) ? x : y;}
	
	LL n, Q, a[MAXN], tax[MAXN * 2], pre[MAXN], ans[MAXN];
	struct qry {
		LL l, r, id;
		bool operator < (const qry &rhs) const {return r < rhs.r;}
	} xw[MAXN];
	
	#define M ((l + r) >> 1)
	#define lc (o << 1)
	#define rc (o << 1 | 1)
	#define ls lc, l, M
	#define rs rc, M + 1, r
	LL max_now[MAXN * 4], lazy_now[MAXN * 4], max_old[MAXN * 4], lazy_old[MAXN * 4];
	void pushup(LL o) {
		max_now[o] = max(max_now[lc], max_now[rc]);
		max_old[o] = max(max_old[lc], max_old[rc]);
	}
	void pushdown(LL o) {
		
		chkmax(max_old[lc], max_now[lc] + lazy_old[o]);
		chkmax(max_old[rc], max_now[rc] + lazy_old[o]);
		chkmax(lazy_old[lc], lazy_now[lc] + lazy_old[o]);
		chkmax(lazy_old[rc], lazy_now[rc] + lazy_old[o]); // 更新历史最优值
		
		max_now[lc] += lazy_now[o];
		max_now[rc] += lazy_now[o];
		lazy_now[lc] += lazy_now[o];
		lazy_now[rc] += lazy_now[o]; // now 按照常规线段树维护最大值的方法来更新
		
		lazy_now[o] = lazy_old[o] = 0;
	}
	void update(LL o, LL l, LL r, LL x, LL y, LL v) {
		if (x <= l && r <= y) {
			lazy_now[o] += v;
			max_now[o] += v; // now 按照常规线段树维护最大值的方法来更新
			chkmax(lazy_old[o], lazy_now[o]);
			chkmax(max_old[o], max_now[o]); // 更新历史最优值
			return ; 
		}
		pushdown(o);
		if (x <= M) update(ls, x, y, v); 
		if (M < y) update(rs, x, y, v);
		pushup(o);
	}
	LL query(LL o, LL l, LL r, LL x, LL y) {
		if (x <= l && r <= y) return max_old[o];
		pushdown(o);
		LL ret = 0;
		if (x <= M) chkmax(ret, query(ls, x, y)); 
		if (M < y) chkmax(ret, query(rs, x, y));
		return ret;
	}
	
    void clean() {
    }
    int solve() {
    	
    	clean();
    	cin >> n;
    	for (LL i = 1; i <= n; ++i) {
			scanf("%lld", &a[i]);
			pre[i] = tax[a[i] + BS], tax[a[i] + BS] = i;
		}
    	cin >> Q;
    	for (LL i = 1; i <= Q; ++i) scanf("%lld%lld", &xw[i].l, &xw[i].r), xw[i].id = i;
    	sort(xw + 1, xw + 1 + Q);
    	LL j = 1;
    	for (LL i = 1; i <= n; ++i) {
    		update(1, 1, n, pre[i] + 1, i, a[i]);
    		while (j <= Q && xw[j].r <= i) ans[xw[j].id] = query(1, 1, n, xw[j].l, xw[j].r), ++j;
		}
		for (LL i = 1; i <= Q; ++i) printf("%lld\n", ans[i]);
    	
        return 0;
    } 
}
int main() {
    flyinthesky::solve();
    return 0;
}
```

---

## 作者：Milthm (赞：4)

这题直接做肯定就寄了，所以考虑离线。

首先一个去重题常有的套路，先把每个 $a_i$ 的前面一个和它相同的数的下标记录下来，设为 $pre_i$。

我们假设不管这个去重，先按照右端点 $r$ 排序,然后从左到右扫描 $i$，此时令 $c_j$ 等于 $[j,i]$ 的 $a_i$ 之和，此时我们的答案就是 $\max(c_j,l\le j \le i)$……吗？

好像不是很对，这样把右端点限定在了 $i$，但是取到 $i$ 不一定是最优的，所以要维护历史最大值。

考虑用线段树来维护，每个节点维护最大值、历史最大值、懒标记、历史最大懒标记（指上次 pushdown 之后的），然后就可以合并区间信息了。

加上去重的话，只要每次扫描到 $i$ 的时候 `update` 一下就行了。具体实现看代码。

### AC code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int n,m,b[N],pre[N],l[N],r[N],id[N];
int cmp(int x,int y){
	return r[x]<r[y];
}
struct Seg{
	int max,hismax,z,hisz;
}a[N*4],an[N];
Seg merge(Seg A,Seg B){
	Seg ans;
	ans.max=max(A.max,B.max);
	ans.hismax=max(A.hismax,B.hismax);
	ans.z=ans.hisz=0;
	return ans;
}
void pushup(int x){
	a[x]=merge(a[x*2],a[x*2+1]);
}
void pushdown(int x){
	a[x*2].hismax=max(a[x*2].hismax,a[x*2].max+a[x].hisz);
	a[x*2].hisz=max(a[x*2].hisz,a[x*2].z+a[x].hisz);
	a[x*2].max+=a[x].z;a[x*2].z+=a[x].z;
	a[x*2+1].hismax=max(a[x*2+1].hismax,a[x*2+1].max+a[x].hisz);
	a[x*2+1].hisz=max(a[x*2+1].hisz,a[x*2+1].z+a[x].hisz);
	a[x*2+1].max+=a[x].z;a[x*2+1].z+=a[x].z;
	a[x].z=a[x].hisz=0;
}
void update(int x,int l,int r,int ql,int qr,int k){
	if(ql<=l&&r<=qr){
		a[x].max+=k;a[x].hismax=max(a[x].hismax,a[x].max);
		a[x].z+=k;a[x].hisz=max(a[x].hisz,a[x].z);
		return;
	}
	pushdown(x);
	int mid=(l+r)>>1;
	if(ql<=mid)update(x*2,l,mid,ql,qr,k);
	if(qr>mid)update(x*2+1,mid+1,r,ql,qr,k);
	pushup(x);
}
Seg query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return a[x];
	int mid=(l+r)>>1;
	pushdown(x);
	if(ql<=mid&&qr>mid)return merge(query(x*2,l,mid,ql,qr),query(x*2+1,mid+1,r,ql,qr));
	else if(ql<=mid)return query(x*2,l,mid,ql,qr);
	else return query(x*2+1,mid+1,r,ql,qr);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>b[i];
	cin>>m;
	for(int i=1;i<=m;++i)cin>>l[i]>>r[i],id[i]=i;
	sort(id+1,id+m+1,cmp);
	int j=1;
	for(int i=1;i<=n;++i){
		update(1,1,n,pre[b[i]+100000]+1,i,b[i]);
		pre[b[i]+100000]=i;
		while(r[id[j]]==i&&j<=m)an[id[j]]=query(1,1,n,l[id[j]],r[id[j]]),++j;
	}
	for(int i=1;i<=m;++i)cout<<an[i].hismax<<'\n';
	return 0;
}
```

这样的话 GSS 系列只剩一题了。

---

## 作者：zhenglier (赞：4)

## 线段树

这道题是线段树好题。因为相同的数字只能算一次，需要一些特殊的操作。可以用离线来操作。

维护一颗线段树，每个点记录两个值，一个是这个点到当前指针的和，一个是当前点的历史最大值（就是这个点为开头的最大子段和）。

这样就需要比较复杂的维护子树信息。线段树需要额外维护两个懒标记：当前懒标记，历史最大懒标记。然后用这种方式维护：

```cpp
void addtag(int rt,int now,int his){
	his_max[rt]=max(his_max[rt],now_max[rt]+his);
	his_tag[rt]=max(his_tag[rt],now_tag[rt]+his);
	now_tag[rt]+=now;
	now_max[rt]+=now;
}
void pushdown(int rt){
    addtag(lson,now_tag[rt],his_tag[rt]);
    addtag(rson,now_tag[rt],his_tag[rt]);
    now_tag[rt]=his_tag[rt]=0;
}
```

然后就可以把所有询问操作离线下来按右端点排序，然后维护每个数相同数的前继$pre$，这个数能更新的范围就是$pre+1$到当前点$pos$。

然后就可以做这道题了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
#define lson (rt<<1)
#define rson (rt<<1|1)
int now_tag[N<<2],his_tag[N<<2];
int now_max[N<<2],his_max[N<<2];
void pushup(int rt){
    now_max[rt]=max(now_max[lson],now_max[rson]);
    his_max[rt]=max(his_max[lson],his_max[rson]);
}
void addtag(int rt,int now,int his,int op=1){
	if(op){
	    his_max[rt]=max(his_max[rt],now_max[rt]+his);
	    his_tag[rt]=max(his_tag[rt],now_tag[rt]+his);
	    now_tag[rt]+=now;
	    now_max[rt]+=now;
	}else{
	    now_tag[rt]+=now;
	    now_max[rt]+=now;
	    his_max[rt]=max(his_max[rt],now_max[rt]+his);
	    his_tag[rt]=max(his_tag[rt],now_tag[rt]+his);
	}
}
void pushdown(int rt){
    addtag(lson,now_tag[rt],his_tag[rt]);
    addtag(rson,now_tag[rt],his_tag[rt]);
    now_tag[rt]=his_tag[rt]=0;
}
void updata(int rt,int l,int r,int x,int y,int z){
    if(x<=l&&r<=y){
        addtag(rt,z,0,0);
        return;
	}
	pushdown(rt);
	int mid=l+(r-l)/2;
	if(x<=mid)updata(lson,l,mid,x,y,z);
	if(y>mid)updata(rson,mid+1,r,x,y,z);
	pushup(rt);
}
int query(int rt,int l,int r,int x,int y){
    if(x<=l&&r<=y)return his_max[rt];
    pushdown(rt);
	int mid=l+(r-l)/2,ret=0;
    if(x<=mid)ret=max(ret,query(lson,l,mid,x,y));
    if(y>mid)ret=max(ret,query(rson,mid+1,r,x,y));
	pushup(rt);
    return ret;
}
int n,m;
int a[N],ot[N];
struct data{
    int l,r,id;
    data(int l=0,int r=0,int id=0):l(l),r(r),id(id){}
}q[N];
bool operator<(const data&a,const data&b){
	return a.r<b.r;
}
int pre[N],mp[N<<1];
int main(){
    cin>>n;
    for(int i=0;i<(N<<2);++i){
        his_max[i]=-1e8;
	}
    for(int i=1;i<=n;++i){
	    scanf("%d",a+i);
	    pre[i]=mp[a[i]+N]+1;
	    mp[a[i]+N]=i;
	}
    cin>>m;
    for(int i=1;i<=m;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        q[i]=data(x,y,i);
	}
	sort(q+1,q+m+1);
	for(int i=1,pos=1;i<=m;++i){
	    while(pos<=q[i].r&&pos<=n){
	        updata(1,1,n,pre[pos],pos,a[pos]);
		    pos++;
		}
		ot[q[i].id]=query(1,1,n,q[i].l,q[i].r);
	}
	for(int i=1;i<=m;++i){
	    printf("%d\n",ot[i]);
	}
}
```

---

## 作者：lfxxx (赞：2)

考虑仿照区间数颜色，给每个位置附上第二个权值 $pre_{i}$ 表示上一个相同的数的出现位置，那么现在变成了二维平面上有 $n$ 个带权点，每次给定一个 $[l,r]$ 求出子区间 $[l',r']$ 最大的权值和，一个区间 $[l,r]$ 的权值为所有在矩形 $(L_x=1,L_y=l,R_x=l-1,R_y=r)$ 内的点的权值之和。

考虑扫描线降维，对于每个 $r$ 维护所有 $l$ 的答案，具体来说我们维护当前 $l$ 的最大值与 **历史最大值** 接着你发现在 $r'$ 处查询 $l'$ 的答案就等于查询区间 $[l',l']$ 到区间 $[l',r']$ 的答案。那么把询问挂到右端点上，每次再查询一个区间历史最大值即可。 

考虑扫描线扫到点 $x$ 时，所有满足 $r \geq x$ 且 $l > pre_{x}$ 的区间会被贡献到，因此考虑维护一个区间 $[pre_x+1,x]$ 内的区间加法。

现在你需要维护区间最大值与区间历史最大值，还需要支持区间加法，考虑构造矩阵转移即可，这一部分可以看代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 1e13+114;
const int maxn = 1e5+114;
struct Matrix{
    int a[3][3],n,m;
    Matrix(int N=0,int M=0,int C=0){
        n=N,m=M;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++) a[i][j]=C;
    }
    Matrix operator*(const Matrix &x)const{
        Matrix res=Matrix(n,x.m,-inf);
        for(int i=1;i<=n;i++)
            for(int k=1;k<=m;k++)
                for(int j=1;j<=x.m;j++) res.a[i][j]=max(res.a[i][j],a[i][k]+x.a[k][j]);
        return res;
    }
}e;
Matrix tr[maxn<<2],tag[maxn<<2];
Matrix max(Matrix x,Matrix y){
    Matrix res=Matrix(1,2,-inf);
    res.a[1][1]=max(x.a[1][1],y.a[1][1]);
    res.a[1][2]=max(x.a[1][2],y.a[1][2]);
    return res;
}
void pushup(int cur){tr[cur]=max(tr[cur<<1],tr[cur<<1|1]);}
void pushdown(int cur){
    tr[cur<<1]=tr[cur<<1]*tag[cur];
    tag[cur<<1]=tag[cur<<1]*tag[cur];
    tr[cur<<1|1]=tr[cur<<1|1]*tag[cur];
    tag[cur<<1|1]=tag[cur<<1|1]*tag[cur];
    tag[cur]=e;
    return ;
}
void build(int cur,int lt,int rt){
    if(lt==rt){
        tr[cur]=Matrix(1,2);
        return ;
    }
    int mid=(lt+rt)>>1;
    build(cur<<1,lt,mid);
    build(cur<<1|1,mid+1,rt);
    pushup(cur);
}
void mul(int cur,int lt,int rt,int l,int r,Matrix c){
    if(r<lt||rt<l) return ;
    if(l<=lt&&rt<=r){
        tr[cur]=tr[cur]*c;
        tag[cur]=tag[cur]*c;
        return ;
    }
    pushdown(cur);
    int mid=(lt+rt)>>1;
    mul(cur<<1,lt,mid,l,r,c);
    mul(cur<<1|1,mid+1,rt,l,r,c);
    pushup(cur);
}
Matrix ask(int cur,int lt,int rt,int l,int r){
    if(r<lt||rt<l) return Matrix(1,2);
    if(l<=lt&&rt<=r) return tr[cur];
    pushdown(cur);
    int mid=(lt+rt)>>1;
    return max(ask(cur<<1,lt,mid,l,r),ask(cur<<1|1,mid+1,rt,l,r));
}
map<int,int> cnt;
int pre[maxn],a[maxn];
int n,q;
int answer[maxn];
vector< pair<int,int> >Query[maxn];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pre[i]=cnt[a[i]];
        cnt[a[i]]=i;
    }
    e=Matrix(2,2,-inf);
    e.a[1][1]=e.a[2][2]=0;
    for(int i=0;i<(maxn<<2);i++) tag[i]=e;
    build(1,1,n);
    cin>>q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        Query[r].push_back(make_pair(l,i));
    }
    for(int i=1;i<=n;i++){
        Matrix c=Matrix(2,2,0);
        c.a[1][1]=0,c.a[1][2]=-inf,c.a[2][1]=c.a[2][2]=a[i];
        mul(1,1,n,pre[i]+1,i,c);
        for(pair<int,int> now:Query[i]) answer[now.second]=max(ask(1,1,n,now.first,i),Matrix(1,2)).a[1][1];
    }
    for(int i=1;i<=q;i++) cout<<answer[i]<<'\n';
    return 0;
}

```



---

## 作者：shucai (赞：2)

# GSS2

### 题意

>给出 $n$ 个数，$q$ 次询问，求最大子段和，相同的数只算一次。

>$1 \le n,q \le 10^5,-10^5 \le a_i \le 10^5$

### 思路

既然相同数只算一次，那么就不能通过维护区间的前缀最大和，后缀最大和，区间总和来解决这个问题了。

注意到数据较小，考虑离线动态开点。

为了不重复算一个数的贡献，考虑将这个数分在不同的区间段，这个区间段如何划分？可以将数据离线记录下来，按右端点排序，这样做可以让数据有序。

我们在读入数据时，可以记录一下当前数据上一个出现的位置，这还是比较简单实现的。令第 $i$ 个数据上一个出现的位置为 $pre_i$，那么我们在插入第 $i$ 个数据时，把他插入区间 $[pre_i,i]$ 即可（即区间和加上 $a_i$），因为它们是有序的，所以 $a_i$ 的贡献只会算一次。

接下来考虑如何查询。由于我们插入的数据是连续的，所以我们可以直接对整个区间维护最大子段和，即维护它的历史区间和最大值即可。

考虑如何维护历史区间和最大值，维护一个区间和即可，而上面我们有一个区间加操作，所以我们还要对这两个数据再分别维护一个懒标记，最后输出历史区间和最大值即可。

## code

```cpp
#include <bits/stdc++.h>
#define int long long
#define _ 100005
using namespace std;
int n, m;
int a[_];
int pre[_], last[_ << 1];
int ans[_];
struct Question {
	int l, r, id;		
}q[_];
bool cmp(Question x, Question y) {
	return x.r < y.r;	
}
struct Node {
	int l, r;
	int sum, Hsmax;
	int Slazy, Hslazy;
	Node() {
		sum = Hsmax = Slazy = Hslazy = 0;	
	}
    /*const Node operator + (const Node x) const {
		Node res;
		res.sum = max(x.sum, sum);
		res.Hsmax = max(x.Hsmax, Hsmax);
		return res;
	}*/
	friend Node operator + (const Node x, const Node y) {
		Node res;
		res.sum = max(x.sum, y.sum);
		res.Hsmax = max(x.Hsmax, y.Hsmax);
		return res;
	}
}tree[_ << 2];
int lson(int root) {
	return root << 1;	
}
int rson(int root) {
	return root << 1 | 1;	
}
void Push_down(int root) {
	tree[lson(root)].Hsmax = max(tree[lson(root)].Hsmax, tree[root].Hslazy + tree[lson(root)].sum), tree[rson(root)].Hsmax = max(tree[rson(root)].Hsmax, tree[root].Hslazy + tree[rson(root)].sum);
	tree[lson(root)].sum += tree[root].Slazy, tree[rson(root)].sum += tree[root].Slazy;
	tree[lson(root)].Hslazy = max(tree[lson(root)].Hslazy, tree[lson(root)].Slazy + tree[root].Hslazy), tree[rson(root)].Hslazy = max(tree[rson(root)].Hslazy, tree[rson(root)].Slazy + tree[root].Hslazy);
	tree[lson(root)].Slazy += tree[root].Slazy, tree[rson(root)].Slazy += tree[root].Slazy;
	tree[root].Slazy = tree[root].Hslazy = 0;	 
}
void Push_up(int root) {
	tree[root] = tree[lson(root)] + tree[rson(root)];	
}
void Add(int L, int R, int l, int r, int root, int val) {
	if (L <= l and r <= R) {
		tree[root].sum += val;
		tree[root].Hsmax = max(tree[root].Hsmax, tree[root].sum);
		tree[root].Slazy += val, tree[root].Hslazy = max(tree[root].Hslazy, tree[root].Slazy);
		return ;
	}	
	Push_down(root);
	int mid = l + r >> 1;
	if (mid >= L) Add(L, R, l, mid, lson(root), val);
	if (mid < R) Add(L, R, mid + 1, r, rson(root), val);
	Push_up(root);
}
Node Query(int L, int R, int l, int r, int root) {
	if (L <= l and r <= R) return tree[root];
	Push_down(root);
	int mid = l + r >> 1;
	if (L > mid) return Query(L, R , mid + 1, r, rson(root));
	else if (R <= mid) return Query(L, R, l, mid, lson(root));
	else return Query(L, R, l, mid, lson(root)) + Query(L, R, mid + 1, r, rson(root));
}
void init() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%lld", &a[i]);
		pre[i] = last[a[i] + (int)1e5];
		last[a[i]+ (int)1e5] = i; 
	}
	scanf("%lld", &m);
	for (int i = 1; i <= m; ++ i) {
		scanf("%lld%lld", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	sort(q + 1, q + 1 + m, cmp);
}
void solve() {
	int Qcnt = 1;
	for (int i = 1; i <= n; ++ i) {
		Add(pre[i] + 1, i, 1, n, 1, a[i]);
		for (; Qcnt <= m and q[Qcnt].r <= i; ++ Qcnt)
			ans[q[Qcnt].id] = Query(q[Qcnt].l, q[Qcnt].r, 1, n, 1).Hsmax;
	}
}
void answer() {
	for (int i = 1; i <= m; ++ i)
	cout << ans[i] << endl;
}
signed main() {
	init();
	solve();
	answer();
	return 0;		
}
```

---

## 作者：AIskeleton (赞：2)

## GSS2

### 题意：

给出长度为 n 的序列 a， q 次询问，求最大子段和，**相同的数只算一次**。

### 题解：
因为相比于 GSS1 要求相同的数只算一次，所以 GSS1 中线段树直接维护区间最大子段和的操作不可取。

这道题其实类比 [P1972 [SDOI2009]HH 的项链](https://www.luogu.com.cn/problem/P1972),之间有很多相似之处，然后从中得出此题的解法。

* 首先，这两题都是询问一个区间，没有修改操作，所以考虑离线，将所有查询按照右区间排序。
* 然后，这两题都要求相同的只算一次，因此利用前缀和的思想，用一个 lst 数组，统计某个数值 $a_i$ 上一次在哪个位置出现过。如果未出现过，就修改之前的全部区间，否则修改 $lst_{a_i}+1$ 与 i 之间的区间。

但这道题和 HH 的项链有一个很大的改变， HH 的项链中每个值的贡献固定为 1，所以只需简单的单点修改和区间查询就行了；但这道题中每个值的贡献不同，所以只是维护区间和不足以解决此题，还需维护区间历史最值。这就又牵涉到另一题 [P4314 CPU 监控](https://www.luogu.com.cn/problem/P4314)，其中线段树维护区间历史最值的方法也可以套用到这道题上。

基本思路有了就可以继续想出具体的做法：

**线段树维护什么？**

参考 CPU 监控这道题，线段树维护 2 个值：
1. 区间最大值 ma。
2. 之前区间的历史最大值 hma。

比如说我们扫描到 i 时的更新，就是相当于更新线段树上的 $\left[lst_{a_i}+1,i\right]$ 之间的区间，然后处理 $q.r=i$ 的询问，答案必然是 $\max( x.ma \mid q.l \le x \le q.r)$,但在此题中我们维护的线段树实际上是区间套区间，如果只维护最大值相当于只能取到在右端点 r 的值，但最大值不一定在右端点 r,所以还要记录这个过程中的最大值。

**需要什么懒标记？**
1. 为维护区间最大值，需一个当前区间的加法懒标记 tag。
2. 为维护区间历史最大值，需一个当前区间的历史最大加法懒标记 htag。

**如何合并和维护？**

对于区间最大值 ma 和维护区间最大值的懒标记 tag,像普通线段树那样合并和更新即可。

区间历史最大值 hma 在合并时也取最大值，更新时取其与当前区间最大值与历史最大懒标记之和中的最大值。

更新左右子树的代码：
```
void pushup(int p)
{
    s[p].ma=max(s[lc].ma,s[rc].ma);
    s[p].hma=max(s[lc].hma,s[rc].hma);//区间最大和历史最大取左右儿子max
}
```
在懒标下传和区间修改时一定要注意更新顺序对结果的影响，本人就在这出锅了。

懒标下传的代码：
```
void pushdown(int p){
    if(s[p].tag||s[p].htag){
        s[lc].hma=max(s[lc].hma,s[lc].ma+s[p].htag);
        s[rc].hma=max(s[rc].hma,s[rc].ma+s[p].htag);
		s[lc].ma+=s[p].tag;
    	s[rc].ma+=s[p].tag;//先更新历史最大值，再更新区间最大值
		s[lc].htag=max(s[lc].htag,s[p].htag+s[lc].tag);
		s[rc].htag=max(s[rc].htag,s[p].htag+s[rc].tag);
		s[lc].tag+=s[p].tag;
		s[rc].tag+=s[p].tag;//对于懒标记也是先更历史最大懒标记
		s[p].tag=s[p].htag=0;//清空懒标记
    }
}
```
懒标下传的操作中 `s[lc].hma=max(s[lc].hma,s[lc].ma+s[p].htag);` 和 	`s[rc].hma=max(s[rc].hma,s[rc].ma+s[p].htag);` 没有都用历史最大值来更新的原因是这样会让连续子段和不连续。

区间修改的代码（核心部分）：
```
s[p].ma+=k;
s[p].hma=max(s[p].hma,s[p].ma);//注意这里因为s[p].ma已经更新过了，所以在更新s[p].hma时不要再把k加上
s[p].tag+=k;
s[p].htag=max(s[p].htag,s[p].tag);//懒标记同理
return ;
```

**主函数如何操作？**

首先，因为输入的序列 a 中有负数，所以初始预处理的代码如果写成这样：
```
for(int i=1;i<=n;i++){
    cin>>a[i];
    lst[i]=pre[a[i]];
    pre[a[i]]=i;
}
```
就会连样例过不去，因为用了负数作为数组下标。

解决方法很简单，就是 lst 和 pre 这两个数组开双倍空间，然后下标加上题目给出的界限即可。
```
for(int i=1;i<=n;i++){
    cin>>a[i];
    lst[i]=pre[a[i]+N];
    pre[a[i]+N]=i;
}
```
再用结构体存储询问，以 r 为关键字从小到大排序。
```
for(int i=1;i<=m;i++){
    cin>>q[i].l>>q[i].r;
    q[i].id=i;
}
sort(q+1,q+1+m,cmp);
```
在进行操作前先建一棵空树，里面什么都不存。

然后从左到右扫描 i,并更新 $\left[lst_{a_i}+1,i\right]$ 之间的节点，用 $a_i$ 的值。

同时更新满足 $q.r=i$ 的询问的答案，也就是查询 $\left[q.l,q.r\right]$ 区间的的历史最大值。

这个部分的代码：
```
int j=1;
for(int i=1;i<=n;i++){
    update(1,lst[i]+1,i,a[i]);
    for(j;j<=m&&q[j].r<=i;j++)
	ans[q[j].id]=query(1,q[j].l,q[j].r).hma;
}
```
最后按顺序输出答案即可。

[完整代码链接](https://www.luogu.com.cn/paste/ct3pj1uq)

---

## 作者：zjjws (赞：2)

## 题意

[题链](https://www.luogu.com.cn/problem/SP1557)

求区间最大子段和，相同元素只贡献一次。


---

## Solution


原先不加限制的最大子段和是这个东西：

$$\max_{L\le l\le r\le R}\sum_{i=l}^r a_i$$

因为具有可合并性，于是就可以用分治来预处理。

---

为了处理不重复出现，我们引入一个值 $b_i$ 表示 $a_i$ 这个值上一次出现的位置。

$$\max_{L\le l\le r\le R}\sum_{i=l}^r a_i\cdot [b_i<l]$$

会注意到既然式子里出现了 $l$ 这一项，朴素地用线段树维护最大子段和就不行了。

为什么呢？因为每个区间维护的最大前缀，最大子段，最大后缀，**无法进行合并**，原因就在于原式中出现了 $b$ 这一判定条件。


考虑这个式子中，$a_i\cdot [b_i<l]$ 实际只和 $l$ 有关。

如果把左端点固定掉，那么我们可以产生一个新序列 $c$，变成一个最大前缀问题。

画出每一个左端点对应的前缀和折线，会注意到：对于折线 $i$，实际就等于 $i-1$ 的版本全局上下平移，然后再进行一次后缀上下平移。

对于询问来说，查询的是 **一段区间的折线** $\le R$ 的最大值，并取 $\max$。

如果我们将点值转化成上三角矩阵（下三角设置为 $-\infty$），每次等于查询一个方阵的最大值。

会注意到每一行是基于上一行的修改而得到的。但是这样是区间版本查询最值，我们难以做到这点。

不过这个思路很有启发性，因为历史版本最值我们是可以做的。注意到如果倒着跑（枚举左端点顺序从右往左），那就是查询历史版本最值了。

区间加，区间历史最值查询。

那么这就是和 [cpu 监控](https://www.luogu.com.cn/problem/P4314) 一样的题，不过需要刚刚的一点题意转化。


---

## Code


```cpp
const int N=1e5+3;
const LL INF=1e18;
int n,q;
LL a[N];
int lst[N<<1];
namespace gyqtree
{
    #define ls (i<<1)
    #define rs ((i<<1)|1)
    struct node
    {
        LL maxx,maxh;
        LL add,addh;
        LL cor,corh;
        bool cot;
        inline void init(LL s){maxx=maxh=s;add=addh=cor=cot=0;corh=-INF;return;}
        inline void addtag(LL &s,LL &h)
        {
            maxh=max(maxh,maxx+h);maxx+=s;
            if(cot)corh=max(corh,cor+h),cor+=s;else addh=max(addh,add+h),add+=s;return;
        }
        inline void cortag(LL &s,LL &h){corh=max(corh,h);maxh=max(maxh,h);maxx=cor=s;cot=true;return;}
    }nod[N<<2];
    inline void up(int i){nod[i].maxx=max(nod[ls].maxx,nod[rs].maxx);nod[i].maxh=max(nod[ls].maxh,nod[rs].maxh);return;}
    inline void maketree(int l,int r,int i){nod[i].init(-INF);if(l==r)return;int mid=l+r>>1;maketree(l,mid,ls);maketree(mid+1,r,rs);return;}
    inline void down(int i)
    {
        if(nod[i].add||nod[i].addh)nod[ls].addtag(nod[i].add,nod[i].addh),nod[rs].addtag(nod[i].add,nod[i].addh),nod[i].add=nod[i].addh=0;
        if(nod[i].cot)nod[ls].cortag(nod[i].cor,nod[i].corh),nod[rs].cortag(nod[i].cor,nod[i].corh),nod[i].cor=nod[i].cot=0,nod[i].corh=-INF;
        return;
    }
    inline void add(int l,int r,int i,int ql,int qr,LL qk)
    {
        if(ql<=l&&r<=qr){nod[i].addtag(qk,qk);return;}
        int mid=l+r>>1;down(i);if(ql<=mid)add(l,mid,ls,ql,qr,qk);if(mid<qr)add(mid+1,r,rs,ql,qr,qk);up(i);return;
    }
    inline void cover(int l,int r,int i,int ql,int qr,LL qk)
    {
        if(ql<=l&&r<=qr){nod[i].cortag(qk,qk);return;}
        int mid=l+r>>1;down(i);if(ql<=mid)cover(l,mid,ls,ql,qr,qk);if(mid<qr)cover(mid+1,r,rs,ql,qr,qk);up(i);return;
    }
    inline LL checkhis(int l,int r,int i,int &ql,int &qr)
    {
        if(ql<=l&&r<=qr)return nod[i].maxh;
        int mid=l+r>>1;LL ans=-INF;down(i);if(ql<=mid)ans=max(ans,checkhis(l,mid,ls,ql,qr));if(mid<qr)ans=max(ans,checkhis(mid+1,r,rs,ql,qr));up(i);return ans;
    }
}
using namespace gyqtree;

struct zjj
{
    int l,r,num;
    inline void Read(int num_){rin>>l>>r;num=num_;return;}
    inline bool operator <(const zjj &ath)const{return l>ath.l;}
}z[N];
LL ans[N];
inline void work()
{
    int S=1e5;
    maketree(1,n,1);
    for(int i=1;i<=n;i++)lst[a[i]+S]=n+1;
    for(int i=n,j=1;i>=1;i--)
    {
        cover(1,n,1,i,i,0);add(1,n,1,i,lst[a[i]+S]-1,a[i]);lst[a[i]+S]=i;
        for(;j<=q&&z[j].l==i;j++)ans[z[j].num]=checkhis(1,n,1,z[j].l,z[j].r);
    }
    for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
    return;
}
int main()
{
    rin>>n;for(int i=1;i<=n;i++)rin>>a[i];
    rin>>q;for(int i=1;i<=q;i++)z[i].Read(i);sort(z+1,z+q+1);
    work();
    return 0;
}
```


---

## 作者：WrongAnswer_90 (赞：1)

[SP1557 GSS2 - Can you answer these queries II](https://www.luogu.com.cn/problem/SP1557)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17860263.html)

扫描线。把询问挂在右端点上，扫描右端点，纵轴仍为序列维。

对于这种出现多次的数只算一次的，记 $pre_i$ 表示 $i$ 这个值上一次的出现位置，套路化的可以强制让出现多次的在 $pre_i<l\wedge i$ 统计，用二维线段树状物维护，但是这道题可以做的更简单。

如果强制让选的右端点就是当前扫描到的右端点的话，设 $f_i$ 为 $i$ 到当前的 $r$ 的出现多次算一次最大子段和，则此时在最右边扩展一位的影响是将 $pre_{a_i}+1\sim i$ 的 $f_i$ 全部加 $a_i$。这样强制右端点在 $r$ 的答案即为 $\max_{i=l}^r f_i$。可以线段树维护。


但是我们需要求的是右端点 $l\leq i\leq r$ 的答案。这里的 $\geq l$，但是去掉这个限制也是无所谓的，因为我们已经限制了左端点的取值，只要把线段树上初值全部设成 $0$，不合法的区间答案正好是 $0$，也正好处理了题目中可以一个都不选的限制。这样线段树历史最值维护一下即可，复杂度 $\mathcal O(m\log n)$。

```cpp
	int n,m,ans[100010],a[100010],c[200010];
	vector<pii> ve[100010];
	namespace Segment
	{
		struct{int l,r,maxm,maxn,tag1,tag2;}t[400010];
		inline void update(int p){t[p].maxn=max(t[p*2].maxn,t[p*2+1].maxn),t[p].maxm=max(t[p*2].maxm,t[p*2+1].maxm);}
		inline void down(int p,int tag1,int tag2){t[p].maxm=max(t[p].maxm,t[p].maxn+tag2),t[p].maxn+=tag1,t[p].tag2=max(t[p].tag2,t[p].tag1+tag2),t[p].tag1+=tag1;}
		inline void spread(int p){down(p*2,t[p].tag1,t[p].tag2),down(p*2+1,t[p].tag1,t[p].tag2),t[p].tag1=t[p].tag2=0;}
		void build(int p,int l,int r)
		{
			t[p].l=l,t[p].r=r;
			if(l==r)return;
			int mid=l+((r-l)>>1);
			build(p*2,l,mid),build(p*2+1,mid+1,r);
		}
		void modify(int p,int l,int r,int k)
		{
			if(l<=t[p].l&&r>=t[p].r)return down(p,k,k);
			spread(p);
			if(l<=t[p*2].r)modify(p*2,l,r,k);
			if(r>t[p*2].r)modify(p*2+1,l,r,k);
			update(p);
		}
		int ask(int p,int l,int r)
		{
			if(l<=t[p].l&&r>=t[p].r)return t[p].maxm;
			spread(p);int s=-INF;
			if(l<=t[p*2].r)s=max(s,ask(p*2,l,r));
			if(r>t[p*2].r)s=max(s,ask(p*2+1,l,r));
			return s;
		}
		void print(int p)
		{
			write(t[p].l),write(t[p].r),write(t[p].maxn),write(t[p].maxm,'\n');
			if(t[p].l==t[p].r)return;
			spread(p);
			print(p*2),print(p*2+1);
		}
	}
	using namespace Segment;
	inline void mian()
	{
		read(n),build(1,1,n);int x,y;
		for(int i=1;i<=n;++i)read(a[i]);
		read(m);
		for(int i=1;i<=m;++i)read(x,y),ve[y].eb(mp(x,i));
		for(int i=1;i<=n;++i)
		{
			modify(1,c[a[i]+100000]+1,i,a[i]),c[a[i]+100000]=i;
			for(auto p:ve[i])ans[p.se]=ask(1,p.fi,i);
		}
		for(int i=1;i<=m;++i)write(ans[i],'\n');
	}
```

---

## 作者：Purslane (赞：1)

# Solution

典。考虑扫描右端点，很容易计算出对于每个 $1 \le l \le r$，$[l,r]$ 当前的在本题定义下子段和是多少。（具体来说，就是向左找到和当前右端点第一个相同的数）

于是每个询问 $[l,r]$ 其实就是询问区间 $[l,r]$ 在时刻 $[1,r]$ 上的历史最大值（注意，在时刻 $[1,l-1]$ 中，这些东西一直是 $0$，其实不影响答案）

这就是区间加区间历史最值的板子。代码很好写，也非常短。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100000+10;
int n,q,a[MAXN],ans[MAXN];
vector<pair<int,int>> qr[MAXN]; map<int,int> mp;
struct TAG {int tag,tagmx;}tag[MAXN<<2];
struct INFO {int mx,hmx;}t[MAXN<<2];
TAG operator +(TAG A,TAG B) {return {A.tag+B.tag,max(A.tagmx,A.tag+B.tagmx)};}
INFO operator +(INFO A,INFO B) {return {max(A.mx,B.mx),max(A.hmx,B.hmx)};}
INFO operator +(INFO A,TAG B) {return {A.mx+B.tag,max(A.hmx,A.mx+B.tagmx)};}
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void push_down(int k,int l,int r) {return t[lson]=t[lson]+tag[k],t[rson]=t[rson]+tag[k],tag[lson]=tag[lson]+tag[k],tag[rson]=tag[rson]+tag[k],tag[k]={0,0},void();}
void update(int k,int l,int r,int x,int y,TAG tg) {
	if(x<=l&&r<=y) return tag[k]=tag[k]+tg,t[k]=t[k]+tg,void();
	push_down(k,l,r);
	if(x<=mid) update(lson,l,mid,x,y,tg); if(y>mid) update(rson,mid+1,r,x,y,tg);
	return t[k]=t[lson]+t[rson],void();
}
INFO query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return t[k];
	push_down(k,l,r);
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return query(lson,l,mid,x,y)+query(rson,mid+1,r,x,y);	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) cin>>a[i];
	cin>>q; ffor(i,1,q) {int l,r; cin>>l>>r,qr[r].push_back({l,i});}
	ffor(i,1,n) {
		update(1,1,n,mp[a[i]]+1,i,{a[i],max(0ll,a[i])}),mp[a[i]]=i;
		for(auto pr:qr[i]) ans[pr.second]=query(1,1,n,pr.first,i).hmx;	
	}
	ffor(i,1,q) cout<<ans[i]<<'\n';
	return 0;
}
```

---

