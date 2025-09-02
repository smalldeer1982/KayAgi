# Anonymity Is Important

## 题目描述

In the work of a doctor, it is important to maintain the anonymity of clients and the results of tests. The test results are sent to everyone personally by email, but people are very impatient and they want to know the results right away.

That's why in the testing lab "De-vitro" doctors came up with an experimental way to report the results. Let's assume that $ n $ people took the tests in the order of the queue. Then the chief doctor Sam can make several statements, in each telling if there is a sick person among the people in the queue from $ l $ -th to $ r $ -th (inclusive), for some values $ l $ and $ r $ .

During the process, Sam will check how well this scheme works and will be interested in whether it is possible to find out the test result of $ i $ -th person from the information he announced. And if it can be done, then is that patient sick or not.

Help Sam to test his scheme.

## 说明/提示

In the first test for the five first queries:

1. Initially Sam tells that people $ 4 $ , $ 5 $ are not sick.
2. In the next query Sam asks the status of the patient $ 5 $ . From the previous query, we know that the patient is definitely not sick.
3. In the next query Sam asks the status of the patient $ 6 $ . We don't know any information about that patient now.
4. After that Sam tells that there exists a sick patient among $ 4 $ , $ 5 $ , $ 6 $ .
5. In the next query Sam asks the status of the patient $ 6 $ . Now we can tell that this patient is definitely sick.

## 样例 #1

### 输入

```
6 9
0 4 5 0
1 5
1 6
0 4 6 1
1 6
0 2 5 1
0 2 2 0
1 3
1 2```

### 输出

```
NO
N/A
YES
YES
NO```

# 题解

## 作者：Francais_Drake (赞：30)

### 题意
有 $n$ 个人。现在依次处理以下 $q$ 个内容：
1. 得知第 $l$ 个到第 $r$ 个人都没有患病或其中有患病者。
2. 询问第 $i$ 个人是否明确患病/不患病。若明确，则其是否患病。

$n,q\le 2\cdot 10^5$。

### 解法
如果一个人确认是患病，则一定存在一个包含它的有患病者的区间，同时其中除了他之外的人必定确定为不患病。很多思路就是这么来的。

考虑使用并查集维护连通块。对于一个保证为无病的区间 $[l,r]$，可以在并查集中把 $[l,r+1]$ 合并，同时将 $r+1$ 作集合代表元素，把编号小者合并到编号大者集合内；同时维护 $\forall i\in[l,r+1]$，若 $i$ 为一个有病者区间的左端点，则右端点的最小值，此值在连通块最右端（集合代表元素）处更新。

然后对 $i$ 是否有病进行判断：若无病，则其一定非集合代表元素；若有病，则其一定是集合代表元素，且包括与其同一集合的元素右端点最小值一定小于其右边连通块代表元素（也就是有包括他的有病者所在的区间，且区间内此人之前和之后的人全部没有病）。（若不小于，则证明没有满足上述要求的区间，此人不能明确是否患病。）

具体实现见代码。

p.s. 此思路为 [CWOI MJC](https://www.luogu.com.cn/user/177533) 原创，感谢大佬的思路！ 

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=200010;
int n,q,o,l,r,a,b,i;
int rt[maxn],lt[maxn];
int Find(const int p){
	if(p==rt[p]) return p;
	return rt[p]=Find(rt[p]);
}
int main(){
	scanf("%d%d",&n,&q);++n;
	for(i=1;i<=n;++i){
		rt[i]=i;
		lt[i]=1145141919;
	}
	while(q--){
		scanf("%d%d",&o,&l);
		if(o){
			if(Find(l)!=l) printf("NO\n");
			else{
				if(lt[l]<Find(l+1)) printf("YES\n");
				else printf("N/A\n");
			}
		}
		else{
			scanf("%d%d",&r,&o);
			if(o){
				a=Find(l);
				lt[a]=min(lt[a],r);
			}
			else{
				while(l<=r){
					a=Find(l);b=Find(l+1);rt[a]=b;
					lt[b]=min(lt[a],lt[b]);l=b;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：CGDGAD (赞：17)

## 题解 CF1641C (1642E)

----

### 算法

「1」型区间为至少包含一个病人的区间，「0」型区间为不包含病人的区间。

- 回答 `NO`：$x$ 号病人包含在任意一个「0」区间中。
- 回答 `YES`：$x$ 号病人包含且仅包含在「1」区间中，且**存在一个包含它的「1」区间，使得除了它以外的所有病人都在「0」区间**。
- 回答 `N/A`：不属于以上两种情况。

接下来我们用 C 表示确定不是病人，U 表示不确定是否是病人的人。

一开始的数列一定是 `UUUU...UUU`。当报告一个区间内没有病人时，数列会变成类似这样：`UUCC...CCUUUU`。

接下来考虑 `YES` 情况的维护。通俗一点来讲，显然当一个 U 周围也是 U 的时候，就很难确定它；当一个 U 左右都是 C 时，确定它是否是病人就更容易一些。进一步思考，可以发现：

```
...UUUCCCCCCUCCCCCUUU....
      o     ^    o
```

假设被 `^` 标记的 U 是我们的研究对象。当且仅当在**它以及它左右 C 的连续段（两个 `o` 标记中间）中**，存在一个包含这个 U 的「1」区间，U 才可以被确定为病人。

如果将所有的 U 用 `std::set` 维护，那么这就很简单了，直接就找中间那个 U（设其下标为 $x$）的前驱后继（设它们的下标为 $l,r$）即可。接下来，需要判定上述的区间是否存在。可以发现区间的左端点一定是在 U 左边那个 C 的连续段，因此**只要存在一个以 $(l,x]$ 为起点的「1」区间，其右端点在 $[x, r)$，那么 $x$ 就确定是病人**。

这部分可以使用一个单点修改、区间查询最小值的线段树 $t$ 来维护。当输入一个「1」区间时，将 $t_l$ 单点赋值为 $\min\{t_l, r\}$ 即可。查询时判断 $\operatorname{query}(l+1,x)$ 与 $r$ 的大小关系就行了。

### 实现

```cpp
#include <cstdio>
#include <algorithm>
#include <set>

#define lt(x) ((x) << 1)
#define rt(x) (lt(x) + 1)

int n, m;

int read() {
    int ans = 0, neg = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') neg = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { ans *= 10; ans += (ch - '0'); ch = getchar(); }
    return ans * neg;
}

namespace SegTree {
    int t[1000001];

    void build(int x = 1, int l = 1, int r = n) {
        t[x] = n + 1;
        if (l == r)
            return;
        const int mid = (l + r) >> 1;
        build(lt(x), l, mid);
        build(rt(x), mid + 1, r);
    }

    void modify(int p, int a, int x = 1, int _l = 1, int _r = n) {
        if (_l == _r) {
            t[x] = std::min(t[x], a);
            return;
        }
        const int mid = (_l + _r) >> 1;
        if (p <= mid)
            modify(p, a, lt(x), _l, mid);
        else
            modify(p, a, rt(x), mid + 1, _r);
        t[x] = std::min(t[lt(x)], t[rt(x)]);
    }

    int query(int l, int r, int x = 1, int _l = 1, int _r = n) {
        if (l <= _l && _r <= r)
            return t[x];
        const int mid = (_l + _r) >> 1;
        int ans = n + 1;
        if (l <= mid)
            ans = std::min(ans, query(l, r, lt(x), _l, mid));
        if (r > mid)
            ans = std::min(ans, query(l, r, rt(x), mid + 1, _r));
        return ans;
    }
};

std::set<int> s;

int main() {
    n = read(), m = read();
    SegTree::build();
    for (int i = 0; i <= n + 1; ++i)
        s.insert(i);
    while (m--) {
        int t = read();
        if (!t) {
            int l = read(), r = read(), op = read();
            if (!op) {
                while (!s.empty()) {
                    int pos = *s.lower_bound(l);
                    if (pos <= r)
                        s.erase(pos);
                    else
                        break;
                }
            } else {
                SegTree::modify(l, r);
            }
        } else {
            int x = read();
            if (!s.count(x))
                puts("NO");
            else {
                auto i = s.lower_bound(x), j = s.upper_bound(x);
                --i;
                if (SegTree::query((*i) + 1, x) < *j)
                    puts("YES");
                else
                    puts("N/A");
            }
        }
    }
    return 0;
}
```

---

## 作者：周子衡 (赞：8)

下面用 $0$ 区间和 $1$ 区间分别表示题述的无病人、有病人的区间。可以知道，我们能判断一个人是否是病人的方法仅限于：

- 如果某个人被包含在某个 $0$ 区间里那么他一定不是病人。
- 如果某个人被包含在某个 $1$ 区间里且这个区间里其他人都由上一条确定不是病人，那么他一定是病人。

考虑将整个输入序列离线。我们可以先一次性计算出在给出所有区间后，每个人的状态（有病/无病/未知）。接下来，我们只要对每个有病/无病的人，计算出最早在什么时候能确定这条信息即可。

无病人的时间计算较为简单，取所有覆盖其的 $0$ 区间的出现时间最小值即可，可以利用数据结构（线段树/并查集）高效解决。有病人的时间可以对每个覆盖其的 $1$ 区间分别考虑，由于每个有效的 $1$ 区间最多覆盖 $1$ 个有病的人，时间复杂度是有保证的。

总时间复杂度 $O(n\log n)$ 或 $O(n\alpha(n))$。

---

## 作者：Nightingale_OI (赞：5)

## CF1641C Anonymity Is Important

### 大意

`0 l r 0` 表示区间 $ [l,r] $ 内没有病人。

`0 l r 1` 表示区间 $ [l,r] $ 内有病人（数量未知）。

`1 x` 表示讯问第 $ x $ 个人有没有病，不确定输出 `N/A` 。

### 思路

我们把 `0 l r 0` 记为 $ [l_{0,i},r_{0,i}] $，把 `0 l r 1` 记为 $ [l_{1,i},r_{1,i}] $。

考虑如果讯问的人在任意 $ [l_{0,i},r_{0,i}] $ 内，就确定没病。

可以开个支持区间赋值或区间加的数据结构，看该位置是否大于 $ 0 $。

考虑如果讯问的人在任意区间 $ [l_{1,i},r_{1,i}] $ 内且该区间内其他病人确定没有病，就确定没病，否则该人不确定。

那么我们可以用类似链表的数据结构来处理一个点 $ x $ 最左、最右连续非 $ 0 $ 的段可以到达哪里（当然这个点为 $ 0 $ ），我们称它为 $ x $ 的延展区间 $ [le_x,ri_x] $ 。

比如一个序列 $ 011101101 $ （下标从 $ 1 $ 开始）：

对于第 $ 2 $ 个人，不存在延展区间。

对于第 $ 5 $ 个人，我们说他的延展区间 $ [le_5,ri_5] $ 为 $ [2,7] $ 。

我们只需要看有没有区间 $ [l_{1,i},r_{1,i}] $ 在区间 $ [le_x,ri_x] $ 内即可。

由于是在线操作，建立一棵单点修改和区间最小线段树。

每个点表示以其为 $ l_{1,i} $ 可以达到的最近右端点，判断 $ [le_x,ri_x] $ 有没有值小于等于 $ ri_x $ 即可。 

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
struct xds{
    int l,r,c;
}a[808080];
int c[202020];
int le[202020];
int ri[202020];
int Min(int x,int y){return x<y?x:y;}
void add(int x,int v){
    for(register int i=x;i<=n;i+=-i&i)c[i]+=v;
}
int sum(int x){
    int re=0;
    for(register int i=x;i;i-=-i&i)re+=c[i];
    return re;
}
void bt(int id,int l,int r){
    a[id]={l,r,n+1};
    if(l<r){
        int mid=(l+r)>>1;
        bt(id*2,l,mid);
        bt(id*2+1,mid+1,r);
    }
}
void change(int id,int x,int v){
    if(a[id].l==a[id].r){
        a[id].c=Min(a[id].c,v);
        return;
    }
    int mid=(a[id].l+a[id].r)>>1;
    if(x<=mid)change(id*2,x,v);
    else change(id*2+1,x,v);
    a[id].c=Min(a[id*2].c,a[id*2+1].c);
}
int ask(int id,int l,int r){
    if(a[id].l==l && r==a[id].r)return a[id].c;
    int mid=(a[id].l+a[id].r)>>1;
    if(r<=mid)return ask(id*2,l,r);
    else if(mid<l)return ask(id*2+1,l,r);
    return Min(ask(id*2,l,mid),ask(id*2+1,mid+1,r));
}
int file(int x){return x==le[x]?x:le[x]=file(le[x]);}
int firi(int x){return x==ri[x]?x:ri[x]=firi(ri[x]);}
int main(){
    int p,q;
    cin>>n>>m;
    bt(1,1,n);
    f(i,0,n+1)le[i]=ri[i]=i;
    f(i,1,m){
        scanf("%d",&p);
        if(p){
            scanf("%d",&q);
            if(sum(q)){
                printf("NO\n");
            }else{
                s=file(q-1)+1;l=firi(q+1)-1;
                if(ask(1,s,q)<=l)printf("YES\n");
                else printf("N/A\n");
            }
        }else{
            scanf("%d %d %d",&s,&l,&q);
            if(q){
                change(1,s,l);
            }else{
                add(s,1);add(l+1,-1);
                while(s<=l){
                    le[s]=s-1;
                    ri[s]=s+1;
                    s=firi(s);
                }
                s=file(s-1);l=firi(l+1);
            }
        }
    }
    return 0;
}
```

---

## 作者：ExplodingKonjac (赞：3)

### [【原题链接】](https://0vu.cn/iwrzjr)

## 题目分析

我们称一次 $x=1$ 的修改的区间为一个“$1$ 区间”，称一次 $x=0$ 的修改为一次“覆盖”。然后对一个人单独考虑：

* 如果这个人被确认没病，那么直接输出 `NO` 即可；

* 如果能够找到一个 $1$ 区间使得这个区间内有且仅有这个人是没有被覆盖的，那么答案就是 `YES`；

* 其它情况答案都是 `N/A`。

`NO` 的情况容易判断，现在我们想想怎么判断 `YES`。

假设我们要查询位置 $x$，考虑找出其左边离他最近的没被覆盖的人，以及右边离他最近的没被覆盖的人，设这两个位置为 $l',\ r'$。那么 `YES` 的条件等价于存在一个 $1$ 区间 $[l,r]$，使得 $l\in(l',x],\ r\in[x,r')$。

怎么维护这个东西呢？用 `set` 维护所有未被覆盖的位置，这样就可以找到 $l',\ r'$，每次覆盖时暴力删除。因为每个元素只会被删一次，复杂度是 $O(n\log n)$ 的。

至于判断区间存在性，以区间左端点为下标建立线段树，每个节点开一个 `set` 维护右端点。修改时直接插入即可。查询的时候对于一个被完全包含的节点，我们在它的 `set` 上查找 $x$ 的后继，判断是否小于 $r'$ 即可。

时间复杂度 $O(n\log^2 n)$。具体实现可以看代码。

## 代码实现

这份代码在比赛刚结束第二天的时候提交，可以通过。但是刚刚我又交了一遍，貌似被一组新的数据卡 TLE 了（（（相信大家都有更优秀的实现。

**2022.3.7 UPD：被卡的点是一个全为修改的点，采用将修改存进队列，查询时再执行的方法可以通过。**

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define OPENIOBUF

/*
省略100多行的快读快写模板。
即下文中的qin、qout。
*/

using namespace FastIO;
int n,m;
set<int> s;

struct TreeNode{ set<int> s;int lc,rc; }t[400005];
int rt,cnt;
#define LC t[i].lc
#define RC t[i].rc
void build(int l,int r,int &i=rt)
{
	i=++cnt;
	if(l!=r)
	{
		int mid=(l+r)>>1;
		build(l,mid,LC),build(mid+1,r,RC);
	}
}
void modify(int px,int py,int &i=rt,int l=1,int r=n)
{
	t[i].s.insert(py);
	if(l!=r)	
	{
		int mid=(l+r)>>1;
		if(mid>=px)	modify(px,py,LC,l,mid);
		else	modify(px,py,RC,mid+1,r);
	}
}
bool query(int lq,int rq,int uq,int dq,int &i=rt,int l=1,int r=n)
{
	if(l>=lq && r<=rq)
	{
		auto it=t[i].s.lower_bound(uq);
		return it!=t[i].s.end() && (*it)<=dq;
	}
	int mid=(l+r)>>1,res=0;
	if(mid>=lq)	res|=query(lq,rq,uq,dq,LC,l,mid);
	if(mid<rq)	res|=query(lq,rq,uq,dq,RC,mid+1,r);
	return res;
}

struct Oper
{
	int l,r,x;
	Oper()=default;
	Oper(int _l,int _r,int _x): l(_l),r(_r),x(_x){}
	inline void process()
	{
		if(x)	modify(l,r);
		else
		{
			auto itl=s.lower_bound(l);
			auto itr=s.upper_bound(r);
			if(itl!=itr)	s.erase(itl,itr);
		}
	}
};
queue<Oper> q;
int main()
{
	int opt,l,r,x,ll,rr;
	qin>>n>>m;
	build(1,n);
	for(int i=1;i<=n;i++)	s.insert(i);
	while(m--)
	{
		qin>>opt;
		if(opt==0)
			qin>>l>>r>>x,q.push(Oper(l,r,x));
		else
		{
			qin>>x;
			while(!q.empty())
				q.front().process(),q.pop();
			auto it=s.find(x);
			if(it==s.end())	qout.writeln("NO");
			else
			{
				ll=(it==s.begin())?1:(*prev(it)+1);
				rr=(it==--s.end())?n:(*next(it)-1);
				qout.writeln(query(ll,x,x,rr)?"YES":"N/A");
			}
		}
	}
//	return qout.flush(),0;
}

```


---

## 作者：louhao088 (赞：2)


主席树+二分



------------


考虑将询问离线。用主席树记录每个时刻已知未感染者情况。

对每个 $t=0,x=0$ 的操作我们在主席树上进行修改。

我们很容易发现，一个人能被感染当且仅当存在一个  $ t=0,x=1$ 的信息，使得这一段 $l,r$ 中只有他一个不是已经确定的未被感染的人。

我们可以对 $ t=0,x=1$ 的信息二分其最小能确定感染者的时间，判断用主席树即可，然后对那个感染者记录最早知道其感染的时间。

最后处理询问即可。

注意：可以不推 tag 但是要标记已经完整为 1 的一段。

时间复杂度 $O(n \log^2 n)$。


------------
代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define mid (l+r>>1)
#define lowbit(x) (x&-x)
const int maxn=2e5+5,M=34005;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,x,u[maxn],v[maxn],w[maxn],op[maxn],c[maxn],sz,rt[maxn],a[maxn];
int sum[maxn<<5],ls[maxn<<5],rs[maxn<<5];
set<int>s;
void updata(int &rt,int rt1,int l,int r,int L,int R)
{
	if(l>R||r<L)return;if(sum[rt]==r-l+1)return;
	rt=++sz;ls[rt]=ls[rt1],rs[rt]=rs[rt1];sum[rt]=sum[rt1];
	if(l>=L&&r<=R){sum[rt]=r-l+1;return;}
	updata(ls[rt],ls[rt1],l,mid,L,R),updata(rs[rt],rs[rt1],mid+1,r,L,R);
	sum[rt]=sum[ls[rt]]+sum[rs[rt]];
}
int query(int rt,int l,int r,int L,int R)
{
	if(l>R||r<L)return 0;if(!rt)return 0;
	if(sum[rt]==r-l+1)return min(R,r)-max(L,l)+1;
	if(l>=L&&r<=R){return sum[rt];}
	return query(ls[rt],l,mid,L,R)+query(rs[rt],mid+1,r,L,R);
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();memset(a,0x3f,sizeof a);
	for(int i=1;i<=m;i++)
	{
		op[i]=read();
		if(op[i]==0)u[i]=read(),v[i]=read(),w[i]=read();
		else w[i]=read();
	}
	for(int i=1;i<=m;i++)
	{
		rt[i]=rt[i-1];
		if(op[i]==0&&w[i]==0)updata(rt[i],rt[i],1,n,u[i],v[i]);
	}
	for(int i=1;i<=n;i++)
		if(!query(rt[m],1,n,i,i))s.insert(i);
	for(int i=1;i<=m;i++)
	{
		if(op[i]==0&&w[i]==1)
		{
			if(query(rt[m],1,n,u[i],v[i])!=v[i]-u[i])continue;
			int l=i,r=m,ans=m;
			while(l<=r)
			{
				if(query(rt[mid],1,n,u[i],v[i])==v[i]-u[i])ans=mid,r=mid-1;
				else l=mid+1;
			}
			int id=*s.lower_bound(u[i]);
			a[id]=min(a[id],ans);
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(op[i]==1)
		{
			if(query(rt[i],1,n,w[i],w[i]))puts("NO");
			else if(a[w[i]]<i)puts("YES");
			else puts("N/A");
		}
	}
 	return 0;
}


/*********************************************************************
    作者:louhao088
    日期: 2022-02-23 18:52
*********************************************************************/
```


---

## 作者：2018ty43 (赞：2)

### 题意简述：
- 有一个长 $n$ 的 $01$ 数列
- 操作 : 告诉你一个区间的 or 值  
- 询问 : 查询一个位置必定为 $0$ 、$1$ 还是无法确定

### 思路：  
如果查询位置未被任何操作区间包含，则无法确定。  
如果被或值为 $0$ 的区间包含，则只能为 $0$。  
因为只要或值为 $1$ 的区间中有任何一个 $1$ 剩下的就无需确定了。所以当且仅当这个区间只有一个未确定为 $0$ 的位置时，该位置确定为 $1$。  
即对于位置 $x$，设与其相连最靠左的 $0$ 的位置为 $l_x$，最靠右的 $0$ 的位置为 $r_x$，当 $[l,r]$ 包含区间 or 值为 $1$ 时该位置确定为 $1$。  
可用 set、并查集与线段树维护。

### AC代码
```cpp
#include<cstdio>
#include<cstring>
#include<set>
int n,q;
int w[4*300009];
int min(int u,int v)
{
	return (u<v)?u:v;
}
int max(int u,int v)
{
	return (u>v)?u:v;
}
void change(int u,int l,int r,int x,int y)
{
	if(l==r)
	{
		w[u]=min(y,w[u]);
		return;
	}
	int mid(l+r>>1);
	if(x<=mid)change(u<<1,l,mid,x,y);
	else change(u<<1|1,mid+1,r,x,y);
	w[u]=min(w[u<<1],w[u<<1|1]);
}
std::set<int>ak;
int query(int u,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)return w[u];
	int mid(l+r>>1),og(0x7f7f7f);
	if(x<=mid)og=min(og,query(u<<1,l,mid,x,y));
	if(mid<y)og=min(og,query(u<<1|1,mid+1,r,x,y));
	return og;
}
bool oo[300009];
int main()
{
	memset(w,0x7f,sizeof(w));
	scanf("%d%d",&n,&q);
	ak.insert(0),ak.insert(n+1);
	for(int i(1);i<=n;++i)ak.insert(i);
	while(q--)
	{
		int t;
		scanf("%d",&t);
		if(t==0)
		{
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			if(x==0)
			{
				if(!ak.empty())
				for(auto q(ak.lower_bound(l));q!=ak.end()&&*q<=r;q=ak.lower_bound(l))
				{
					l=*q;
					oo[l]=1;
					ak.erase(q);
					if(ak.empty())break;
				}
			}
			else change(1,1,n,l,r);
		}
		else
		{
			int l;
			scanf("%d",&l);
			if(oo[l])puts("NO");
			else
			{
				auto g(ak.find(l)),gg(g);
				--g;
				int oc(*g+1);
				++gg;
				int oe(*gg-1);
				int qq(query(1,1,n,oc,l));
				if(qq<=oe)puts("YES");
				else puts("N/A");
			}
		}
	}
}
```


---

## 作者：I_am_Accepted (赞：1)

### Preface

感谢这道题成功阻止了我灰号上大分。

### Analysis

为方便，设至少有一个病人的区间为 A 区间，没有病人的为 B 区间。

结论：只有当一段覆盖点 $a$ 的 A 区间中除了 $a$ 其他确定为没病时，$a$ 才能确定有病。

**Proof**

如果 $a$ 不在任意上述类型的 A 区间内，那对于任何覆盖 $a$ 的 A 区间，设定除了已确定没病的人和 $a$ 之外的人全都得病，这样就构造了一个所有条件都满足且 $a$ 没得病的情况（反例），原命题得证。$\blacksquare$

这样的话，若询问 $x$ 的得病状况：

若 $x$ 被 B 区间覆盖（Algorithm 1），输出 NO。

否则，求出最小的 $L$ 使得 $[L,x-1]$ 之间所有人绝对没有得病的，同理求出 $x$ 右边最大的 $R$。（Algorithm 1）

只要判断是否有 A 区间被包含在 $[L,R]$ 即可，因为若有，A 区间必然包含 $x$。（Algorithm 2）

### Algorithm 1

可以 $O(n\log n)$ 用线段树或 `std::set` 维护，但我用了线性均摊做法。（详见代码，类似链表或并查集）

### Algorithm 2

用线段树维护区间最小值。对于每一个 A 区间 $[l,r]$，在 $l$ 位置上标记 $r$。（若同一个 $l$ 有多个 $r$，取最小的）

### Code

[Link](https://codeforces.com/contest/1642/submission/147562428)

---

## 作者：Rushroom (赞：1)

首先，很容易想到：

- 对于区间 0 的操作，直接将整个区间都赋成 0 即可。

- 对于区间 1 的操作，如果这个区间只剩一个不是 0 的，那么可以确定，它的值就是 1。

虽然但是，它有一个 bug：

比如这样一组数据：

```
Input

3 3
0 1 3 1
0 1 2 0
1 3

Output

YES
```

因为上述做法只会在区间 1 的操作时确定某个数的值为 1，但如果条件交换一下顺序，就不行了。

### 深入

什么情况可以确定某个数的值为 1 呢？

比如这样：

```
1 1 0 0 0 1 0 1
```

（`0` 表示已经确定为 0，`1` 表示其他）

操作:

```
0 4 7 1
```

那么，我们就能确定第 $6$ 个数为 1。

发现：

一个区间内只有一个未确定为 0 的数，且有一个区间 1 的操作刚好包含在这个区间内，那么我们就能确定这个数为 1。

那：什么时候能 **产生** ”一个区间内只有一个未确定为 0 的数” 这种情况呢？

一定是原来一段连续的 1，然后有一个区间 0 的操作，把这段连续的 1  **截断** 了。

注意到，这种情况只可能出现在区间 1 操作的区间紧靠两边的数。

### 做法

用 `std::set` 维护还未确定为 0 的位置。

对于操作，首先像上述的 **基础** 方法操作。

另外：

用线段树维护：左端点为 $i$ 的区间 1 操作中，右端点最小是多少。

对于区间 0 操作，我们还要处理左右两个点（如果存在）：

处理出它左右两边的 **连续 0** 有多长，然后用线段树查询有没有区间 1 操作在这个区间内，如果有，那么把这个点确定为 1。

具体可以看上面那个例子。

### Code

```cpp
/*
 * @Description: I want to be the weakest vegetable in the world!
 * @Author: CGBoy
 * @Date: 2022-02-23 19:14:50
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i,a,n) for(int i=a;i<=n;i++)
#define rep(i,n) forr(i,0,n-1)
#define repp(i,n) forr(i,1,n)
#define pb push_back
#define mp make_pair
#define init(a,i) memset(a,i,sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T_, case_;
int n, q, op, l, r;
int f;
set<int>s;
set<int>::iterator it1, it2;
bool sick[200005];
int tree[800005];
void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        tree[node] = min(tree[node], val);
        return;
    }
    int mid = l + r >> 1;
    if (mid >= ind)update(node * 2 + 1, l, mid, ind, val);
    else update(node * 2 + 2, mid + 1, r, ind, val);
    tree[node] = min(tree[node * 2 + 1], tree[node * 2 + 2]);
}
int query(int node, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[node];
    int mid = l + r >> 1, mn = MAXN;
    if (mid >= L)mn = min(mn, query(node * 2 + 1, l, mid, L, R));
    if (mid < R) mn = min(mn, query(node * 2 + 2, mid + 1, r, L, R));
    return mn;
}
void judge() {
    int L, R;
    if (it1 != s.begin()) {
        it1--;
        L = *it1;
        L++;
        it1++;
    }
    else L = 0;
    it1++;
    if (it1 != s.end()) {
        R = *it1;
        R--;
    }
    else R = n - 1;
    it1--;
    if (query(0, 0, n - 1, L, R) <= R)sick[*it1] = 1;
}
void solve() {
    init(tree, 63);
    scanf("%d%d", &n, &q);
    rep(i, n)s.insert(i);
    rep(i, q) {
        scanf("%d", &op);
        if (op == 0) {
            scanf("%d%d%d", &l, &r, &f);
            l--, r--;
            if (!f) {
                it1 = s.lower_bound(l);
                it2 = s.upper_bound(r);
                s.erase(it1, it2);
                it1 = s.lower_bound(l);
                if (it1 != s.begin()) {
                    it1--;
                    judge();
                    it1++;
                }
                if (it1 != s.end()) judge();
            }
            else {
                it1 = s.lower_bound(l);
                it2 = s.upper_bound(r);
                if (it1 != it2) {
                    int tmp = *it1;
                    it1++;
                    if (it1 == it2)sick[tmp] = 1;
                }
                update(0, 0, n - 1, l, r);
            }
        }
        else {
            scanf("%d", &l);
            l--;
            if (sick[l])printf("YES\n");
            else {
                it1 = s.lower_bound(l);
                if (it1 != s.end() && *it1 == l)printf("N/A\n");
                else printf("NO\n");
            }
        }
    }
}
int main() {
    T_ = 1;

    for (case_ = 1;case_ <= T_;case_++)solve();
    return 0;
}
```

---

