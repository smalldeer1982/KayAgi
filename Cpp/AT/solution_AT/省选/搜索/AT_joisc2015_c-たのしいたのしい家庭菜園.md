# たのしいたのしい家庭菜園

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2015/tasks/joisc2015_c



# 题解

## 作者：是个汉子 (赞：8)

注意！！！ $1-h_{i-1}$ 和 $h_{i+1}-n$ 是可以有等于 $h_i$ 的，翻译错了

[洛谷传送门](https://www.luogu.com.cn/problem/AT1251)	[AT传送门](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/1251)

~~为什么会有两个たのしい~~

### Solution

考虑最后**能够获得收入**的位置，这些位置构成一个先上升再下降的序列。

那么我们可以枚举那个最高点，然后算出这个点左边递增的最大收入和右边递减的最大收入。

那么只考虑左边，右边同理即可。

我们设 $f_i$ 表示**拔完某些草**（也就是已经减去 $c$ ）之后，没有比 $i$ 更高的草，剩余这些草的最大总收益。

那么可以得到转移方程：
$$
f_i=\max\limits_{1\leq j <i \And h_j\leq h_i}\{f_j-\sum_{j<k<i\And h_k>h_i} c_k\}+p_i
$$
 $\sum\limits_{j<k<i\And h_k>h_i}c_k$ 表示 $j$ 到 $i$ 这段中，只需要删去 $h_k>h_i$ 的那一部分。 

这样的时间复杂度是 $O(n^3)$ 的，所以需要优化。

---

因为 $h_j\leq h_i<h_k$ ，所以可以看作 $h_k$ 对 $h_j$ 有一个 $-c_k$ 的贡献，进而 $h_k$ 对所有 $h_j<h_k$ 的 $j$ 的都有一份贡献，所以考虑以高度为下标开一颗线段树，维护区间最大值。

具体操作：对于 $i$ ，每次查询 $\max[0,h_i]$ ，可得 $f_i=\max[0,h_i]+p_i$ ，然后拿 $f_i$ 更新 $h_i$ 位置，并对于 $[0,h_i-1]$ 减去 $c_i$ 。

可以看出 $\max[0,h_i]$ 就是转移方程中的 $\max\limits_{1\leq j <i\And h_j\leq h_i}\{f_j-\sum\limits_{j<k<i\And h_k>h_i} c_k\}$ 。因为当我们在操作 $j$ 之后，每一个 $c_k(h_k>h_j)$ 我们都已经减去。那么到了 $i$ 的时候， $[0,h_i]$ 上的点就是我们要求的，这个时候查询 $\max$ 即可。

那这个题的大体思路就没了。

小细节：因为 $h_i\leq 10^9,n\leq 10^5$ ，所以如果以高度为下标建树是不行的，记得离散化。

### Code

```c++
#include<bits/stdc++.h>
#define ll long long
#define ls rt<<1
#define rs rt<<1|1

using namespace std;
const int N=1e5+10;
const ll INF=1e18;
int n,h[N],p[N],c[N],buk[N],lsh;
ll f[N],g[N],mx[N<<2],lz[N<<2],ans;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

void build(int rt,int l,int r){
    mx[rt]=-INF; lz[rt]=0;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(ls,l,mid); build(rs,mid+1,r);
}

inline void pushdown(int rt){
    if(!lz[rt]) return ;
    mx[ls]+=lz[rt]; lz[ls]+=lz[rt];
    mx[rs]+=lz[rt]; lz[rs]+=lz[rt];
    lz[rt]=0;
}

void update(int rt,int l,int r,int L,int R,ll v){
    if(L<=l&&r<=R){
        mx[rt]+=v; lz[rt]+=v;
        return ;
    }
    pushdown(rt);
    int mid=(l+r)>>1;
    if(L<=mid) update(ls,l,mid,L,R,v);
    if(R>mid) update(rs,mid+1,r,L,R,v);
    mx[rt]=max(mx[ls],mx[rs]);
}

ll query(int rt,int l,int r,int L,int R){
    if(L<=l&&r<=R) return mx[rt];
    pushdown(rt);
    int mid=(l+r)>>1;
    ll res=-INF;
    if(L<=mid) res=max(res,query(ls,l,mid,L,R));
    if(R>mid) res=max(res,query(rs,mid+1,r,L,R));
    return res;
}

void insert(int rt,int l,int r,int p,ll v){
    if(l==r){
        mx[rt]=max(v,mx[rt]);
        return ;
    }
    pushdown(rt);
    int mid=(l+r)>>1;
    if(p<=mid) insert(ls,l,mid,p,v);
    else insert(rs,mid+1,r,p,v);
    mx[rt]=max(mx[ls],mx[rs]);
}

inline void work(ll *f){
    build(1,0,lsh); insert(1,0,lsh,0,0);
    for(int i=1;i<=n;i++){
        f[i]=query(1,0,lsh,0,h[i])+p[i];
        insert(1,0,lsh,h[i],f[i]);
        update(1,0,lsh,0,h[i]-1,-c[i]);
    }
}

int main(){
    n=read();
    for(int i=1;i<=n;i++)
        h[i]=read(),p[i]=read(),c[i]=read(),buk[++lsh]=h[i];
    sort(buk+1,buk+lsh+1);
    lsh=unique(buk+1,buk+lsh+1)-buk-1;
    for(int i=1;i<=n;i++)
        h[i]=lower_bound(buk+1,buk+lsh+1,h[i])-buk;
    work(f);
    reverse(h+1,h+n+1); reverse(p+1,p+n+1); reverse(c+1,c+n+1);
    work(g);
    reverse(g+1,g+n+1); reverse(p+1,p+n+1);
    for(int i=1;i<=n;i++)
        ans=max(ans,f[i]+g[i]-p[i]);
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：da32s1da (赞：3)

```
T3有趣的有趣的家庭菜园题解
算法一：
搜索所有的状态，也就是每个IOI草拔or不拔，然后累加花费与收益，更新答案；
时间复杂度O(2^n*n)，可以拿到30分；
算法二：
直接正解吧，知道了正解之后O(n^3),O(n^2)随便写烂一点就是啦！
设状态f[i]表示i这个IOI草前面没有比它更高的草时，1-i这些草的收益  (以下的收益都是指减去花费之后的纯收益))；
转移为
```
![](https://cdn.luogu.com.cn/upload/pic/18243.png)

```
为了方便设一颗比收益草都低的0号草，f[0]=0；
右面按照同样的方法处理，那么答案就是以某个草及其左面草的收益，和它严格右侧草的收益了(严格右侧是防止其价值被累加两遍)；
这个东西似乎是O(n^3)的，我们需要一些优化；
对于所有草的高度做一个离散化，然后对高度开一个线段树，记录某个高度在这之前的
```
![](https://cdn.luogu.com.cn/upload/pic/18244.png)
```
最大值；
维护的时候就是将线段树中比它小或等于的部分的值全部减去cost[i]，然后将当前草的f[i]插入线段树的h[i]处；
每次查询比它的h[i]小或等于的最大值就可以了；
时间复杂度O(nlogn)；
```

---

## 作者：Otue (赞：1)

考虑最后剩下的最高的树，往左边走单调递减，往右边走单调递减。也就是最后剩下了一个上升子序列和下降子序列。

考虑 dp。定义 $f_i$ 表示前 $i$ 颗树，第 $i$ 颗树保留的最大收益。

则 $f_i=f_j+p_i-\sum_{k=j+1}^{i-1} [h_k>h_j] \times c_k$，且 $h_j<h_i$。

仿照 LIS 的线段树优化思路，难以操作的是后面的一堆 sum。可以看出，每个 $h_k$ 都对之后的 $h_j<h_k$ 有 $-c_k$ 的贡献，进而对于 $[1,h_k-1]$ 减去 $c_k$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ls p << 1
#define rs p << 1 | 1
#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 3e5 + 5, INF = -2e18;

int n, b[N], tot, ans = -2e18, f[N], g[N];

struct edge {
	int H, P, C;
}ed[N]; 

struct ss {
	struct stu {
		int l, r, maxn, lazy;
	}tree[N * 4];
	
	void push_up(int p) {
		tree[p].maxn = max(tree[ls].maxn, tree[rs].maxn);
	}
	
	void push_down(int p) {
		if (tree[p].lazy) {
			tree[ls].maxn += tree[p].lazy;
			tree[rs].maxn += tree[p].lazy;
			tree[ls].lazy += tree[p].lazy;
			tree[rs].lazy += tree[p].lazy;
			tree[p].lazy = 0;
		}
	}	
	
	void build(int p, int l, int r) {
		tree[p].lazy = 0; tree[p].maxn = INF; tree[p].l = l, tree[p].r = r;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(ls, l, mid);
		build(rs, mid + 1, r);
	}
	
	void modify(int p, int l, int r, int val) {
		if (l <= tree[p].l && tree[p].r <= r) {
			tree[p].maxn += val;
			tree[p].lazy += val;
			return;
		}
		push_down(p);
		int mid = (tree[p].l + tree[p].r) >> 1;
		if (l <= mid) modify(ls, l, r, val);
		if (r > mid) modify(rs, l, r, val);
		push_up(p);
	}
	
	void modify_max(int p, int x, int val) {
		if (tree[p].l == tree[p].r) {
			tree[p].maxn = max(tree[p].maxn, val);
			return;
		}
		push_down(p);
		int mid = (tree[p].l + tree[p].r) >> 1;
		if (x <= mid) modify_max(ls, x, val);
		else modify_max(rs, x, val);
		push_up(p);
	}
	
	int query(int p, int l, int r) {
		if (l <= tree[p].l && tree[p].r <= r) return tree[p].maxn;
		int mid = (tree[p].l + tree[p].r) >> 1, res = INF;
		push_down(p);
		if (l <= mid) res = max(res, query(ls, l, r));
		if (r > mid) res = max(res, query(rs, l, r));
		return res;
	}
}tr;

signed main() {
	cin >> n;
	_for(i, 1, n) cin >> ed[i].H >> ed[i].P >> ed[i].C, b[++tot] = ed[i].H;
	sort(b + 1, b + tot + 1);
	tot = unique(b + 1, b + tot + 1) - b - 1;
	_for(i, 1, n) ed[i].H = lower_bound(b + 1, b + tot + 1, ed[i].H) - b;
	tr.build(1, 0, tot);
	tr.modify_max(1, 0, 0);
	_for(i, 1, n) {
		f[i] = tr.query(1, 0, ed[i].H) + ed[i].P;
		tr.modify_max(1, ed[i].H, f[i]);
		tr.modify(1, 0, ed[i].H - 1, -ed[i].C);
	}
	tr.build(1, 0, tot);
	tr.modify_max(1, 0, 0);
	_pfor(i, n, 1) {
		g[i] = tr.query(1, 0, ed[i].H) + ed[i].P;
		tr.modify_max(1, ed[i].H, g[i]);
		tr.modify(1, 0, ed[i].H - 1, -ed[i].C);
	}
	_for(i, 1, n) ans = max(ans, f[i] + g[i] - ed[i].P);
	cout << ans << endl;
}
```

---

## 作者：Red_river (赞：1)

### 题目大意
有个人种菜，可以选择种或不种。但是种了的话，只有它当前位置的左边或右边就得都小于等于它的高，也就是说你可以种它，它能不能活就看它造化了，即它**不产生贡献时不一定就需要付出代价**。同时也要付出需要的代价。求最大收益，但是**可能为负**。
### 题意分析
看到数据范围，也是比较大的，所以优先考虑以 $O(n \log n)$ 的时间复杂度来做。于是这道题就是一道典型拿线段树优化的的 `DP` 问题。原本的话是要 $O(n^3)$ 的，但是在加上前缀和就会是 $O(n^2)$ 的。

- 设 $F_i$ 表示在种下第 $i$ 棵菜并且只考虑左边的前提下所获得的最大收益。而设 $G_i$ 表示在种下第 $i$ 棵菜并且只考虑右边的前提下所获得的最大收益。。
- 因为取同一个点会重复贡献，所以还要减去本身的一份，即答案为 $ans=\max(\sum\limits_{i=1}^{n}F_i+G_i-val_i)$。

但是我们直接转移甚至加上前缀和优化也不能过，就意味着要拿数据结构，看到这求区间最大值想到了什么？没错，就是线段树，每次拿线段树维护即可通过此题。时间复杂度是 $O(n \log n)$ 的。具体思路可以参照代码及注释。
### CODE
时间复杂度为 $O(n^2)$ 的部分分 `DP` 代码如下，其实本来是 $O(n^2)$ 的，但是加上前缀和优化就行了。

```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define int long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 5005
#define NO printf("No\n")
#define YES printf("Yes\n")
#define f(x,k,y) for(int x=k;x<=y;x++)
using namespace std;
int n,m,ans,sum,num,cnt,tot;
int dis[N],vis[N],f[N],g[N];
int wis[N][N];

inline void read(int &x){
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

inline void write(int x){
	if(x<0){
		x=-x;putchar('-');
	}if(x>=10) write(x/10);
	putchar('0'+x%10);
	return;
}

struct P{
	int h,val,w;
}v[N];

signed main()
{
	freopen("herbary.in","r",stdin);
	freopen("herbary.out","w",stdout);
	read(n);ans=-1e18;
	for(int i=1;i<=n;i++) read(v[i].h),read(v[i].val),read(v[i].w);
	for(int i=1;i<=n+1;i++) f[i]=g[i]=-1e18;
	g[n+1]=0;g[0]=-1e18;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){wis[i][j]=wis[i][j-1];
			if(v[i].h<v[j].h) wis[i][j]+=v[j].w;
		}
	}//前缀和优化。
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++){sum=0;
			sum=wis[i][i-1]-wis[i][j];
			if(v[i].h>=v[j].h) f[i]=max(f[j]-sum+v[i].val,f[i]);
		}//记录左边的最大值。
	for(int i=n;i>=1;i--)
		for(int j=n+1;j>i;j--){
			sum=wis[i][j-1]-wis[i][i];
			if(v[i].h>=v[j].h) g[i]=max(g[j]-sum+v[i].val,g[i]);
		}同理可得（或易得或可知或易知）。
	for(int i=1;i<=n;i++) ans=max(f[i]+g[i]-v[i].val,ans);//其中为了避免重复计算，一定要减去一份自身的贡献。
	wh(ans);
	return 0;
}
```

下面是正解，时间复杂度为 $O(n \log n)$ 的，因为加了线段树。

```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define int long long
#define lx (k<<1)
#define rx ((k<<1)|1)
#define N 100005
using namespace std;
int n,m,ans,sum,num,cnt,tot;
int dis[N],vis[N],f[N],g[N],V[N];

inline void read(int &x){
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

inline void write(int x){
	if(x<0){
		x=-x;putchar('-');
	}if(x>=10) write(x/10);
	putchar('0'+x%10);
	return;
}

struct P{
	int h,val,w;
}v[N];

struct TREE{
	int tag,maxn;
}T[N<<3];

struct XDS{
	void pushdown(int k, int l, int r) {
		if(!T[k].tag) return;
		int val=T[k].tag;
		T[lx].tag+=val;T[rx].tag+=val;
		T[lx].maxn+=val;T[rx].maxn+=val;
		T[k].tag=0;
	}
	
	void build(int k, int l, int r) {
		T[k].maxn=-1e18;T[k].tag=0;
		if(l==r) return;int mid=(l+r)>>1;
		build(lx,l,mid);build(rx,mid+1,r);
	}
	
	void update1(int k,int l,int r,int L,int R,int val) {
		if(L<=l&&r<=R){
			T[k].maxn+=val;
			T[k].tag+=val;
			return;
		}pushdown(k,l,r);int mid=(l+r)>>1;
		if(mid>=L) update1(lx,l,mid,L,R,val);
		if(mid<R) update1(rx,mid+1,r,L,R,val);
		T[k].maxn=max(T[lx].maxn,T[rx].maxn);
	}
	
	void update2(int k,int l,int r,int x,int val) {
		if(l==r){
			T[k].maxn=max(T[k].maxn,val);
			return;
		}pushdown(k,l,r);int mid=(l+r)>>1;
		if(mid>=x) update2(lx,l,mid,x,val);
		else update2(rx,mid+1,r,x,val);
		T[k].maxn=max(T[lx].maxn,T[rx].maxn);
	}
	
	int query(int k,int l,int r,int L,int R) {
		if (L<=l&&r<=R) return T[k].maxn;
		pushdown(k,l,r);int maxn=-1e18,mid=(l+r)>>1;
		if(mid>=L) maxn=max(maxn,query(lx,l,mid,L,R));
		if(mid<R) maxn=max(maxn,query(rx,mid+1,r,L,R));
		return maxn;
	}

}X;

signed main()
{
	freopen("herbary.in","r",stdin);
	freopen("herbary.out","w",stdout);
	read(n);ans=-1e18;m=n;
	for(int i=1;i<=n;i++)
		read(v[i].h),read(v[i].val),read(v[i].w),V[i]=v[i].h;
	sort(V+1,V+1+n);
	m=unique(V+1,V+n+1)-V-1;//去重
	for(int i=1;i<=n;i++) v[i].h=lower_bound(V+1,V+m+1,v[i].h)-V;//离散化
	X.build(1,0,m);
	X.update2(1,0,m,0,0);//建树
	for(int i=1;i<=n;i++){
		f[i]=X.query(1,0,m,0,v[i].h)+v[i].val;
		X.update2(1,0,m,v[i].h,f[i]);
		X.update1(1,0,m,0,v[i].h-1,-v[i].w);
	}
	X.build(1,0,m);
	X.update2(1,0,m,0,0);
	for(int i=n;i>=1;i--){
		g[i]=X.query(1,0,m,0,v[i].h)+v[i].val;
		X.update2(1,0,m,v[i].h,g[i]);
		X.update1(1,0,m,0,v[i].h-1,-v[i].w);
	}//同理转移答案。
	for(int i=1;i<=n;i++) ans=max(f[i]+g[i]-v[i].val,ans);
	wh(ans);
	return 0;
}
```

---

## 作者：Leeb (赞：0)

可以发现，$i$ 能收获的条件为它是其中一侧的最大值。

设 $f_i$ 表示 $1\dots i$ 中必选 $i$ 的答案，$g_i$ 表示 $i\dots n$ 中必选 $i$ 的答案。

那么答案就是 $\max\limits_{i = 1}^n f_i+g_i-p_i$。

$f$ 和 $g$ 一个顺着，一个倒着，不妨讨论 $f$，$g$ 同理即可。

显然 $f_i = \max(f_j - \sum\limits_{k = j + 1}^{i - 1} c_k\cdot[h_k\gt h_i])(0\le j \lt i)$。

但这显然过不了，因为 $\Theta(n^3)$。进行优化。

可以发现从左一次往右时 $h_i$ 会影响比他矮的节点，$f_j - \sum\limits_{k = j + 1}^{i - 1} c_k \cdot [h_k \gt h_i]$ 就是开区间 $(i, j)$ 中比 $j$ 高的所有草的费用之和，即遇到一个 $h_i$ 时就算它的影响。

可以用线段树维护，对 $h$ 离散化，再对高度建一棵线段树（这里的 $h$ 指草的高度数组）。

对于当前点 $i$，先找线段树 $[1, h_i]$ 中权值最大的点更新 $f_i$（这里的 $h_i$ 指离散化后的编号数组，后面也是）。

然后让线段树中 $[1, h_i)$ 的值减去 $c_i$，最后把 $f_i$ 插入线段树中 $h_i$ 的位置。

参考代码：
```cpp
// Code by Leeb
// Powered by Visual Studio Code
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
#include <bits/stdc++.h>
// #include <cstdio>
// #include <cstring>
// #include <algorithm>
#define N 100005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
#define int long long 
#define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define PII pair<int, int>
#define fir first
#define sec second
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, cnt; ll ans, f[N], g[N];
struct Node {
	int h, id, c, p, hh;
} a[N];
inline bool cmp1(Node a, Node b) {
	return a.hh < b.hh;
}
inline bool cmp2(Node a, Node b) {
	return a.id < b.id;
}
inline int in() {
	int a = 0; bool f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = 1; ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
	if (f) return ~a + 1;
	return a;
}
inline void print(int x) {
	if (x < 0) putchar('-'), x = ~x + 1;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
	print(x);
	putchar(ch);
}
namespace Segment {
	struct Tree {
		ll val, tag;
	} tree[N << 2];	
	inline void initialize() { mem(tree, 0); }
	inline void push_up(int x) {
		tree[x].val = max(tree[ls].val, tree[rs].val);
	}
	inline void push_down(int x) {
		if (tree[x].tag) {
			tree[ls].val += tree[x].tag, tree[ls].tag += tree[x].tag;
			tree[rs].val += tree[x].tag, tree[rs].tag += tree[x].tag;
			tree[x].tag = 0;
		}
	}
	inline void update(int x, int l, int r, int L, int R) {
		if (l == r && l == L) { tree[x].val = max(R, tree[x].val); return ; }
		push_down(x); int mid = l + r >> 1;
		if (L <= mid) update(ls, l, mid, L, R);
		else update(rs, mid + 1, r, L, R);
		push_up(x);
	}
	inline void modify(int x, int l, int r, int L, int R, ll v) {
		if (L <= l && r <= R) { tree[x].tag += v, tree[x].val += v; return ; }
		push_down(x); int mid = l + r >> 1;
		if (L <= mid) modify(ls, l, mid, L, R, v);
		if (R > mid) modify(rs, mid + 1, r, L, R, v);
		push_up(x);
	}
	inline ll query(int x, int l, int r, int L, int R) {
		if (L <= l && r <= R) return tree[x].val;
		push_down(x); ll ans = -1e18; int mid = l + r >> 1;
		if (L <= mid) ans = max(ans, query(ls, l, mid, L, R));
		if (R > mid) ans = max(ans, query(rs, mid + 1, r, L, R));
		return ans;
	}
}
using namespace Segment;
inline void init() {
	n = in();
	for (int i = 1; i <= n; ++i)
		a[i].hh = in(), a[i].p = in(), a[i].c = in(), a[i].id = i;
}
inline void work() {
	sort(a + 1, a + 1 + n, cmp1); a[1].h = 1;	
	for (int i = 2; i <= n; ++i) {
		if (a[i].hh == a[i - 1].hh) a[i].h = a[i - 1].h;
		else a[i].h = a[i - 1].h + 1;
	}
	cnt = a[n].h;
	sort(a + 1, a + 1 + n, cmp2); initialize();
	for (int i = 1; i <= n; i++) {
		f[i] = query(1, 1, cnt, 1, a[i].h) + a[i].p;
		update(1, 1, cnt, a[i].h, f[i]);
		if (a[i].h > 1) modify(1, 1, cnt, 1, a[i].h - 1, -a[i].c);
	}
	initialize();
	for (int i = n; i; i--) {
		g[i] = query(1, 1, cnt, 1, a[i].h) + a[i].p;
		update(1, 1, cnt, a[i].h, g[i]);
		if (a[i].h > 1) modify(1, 1, cnt, 1, a[i].h - 1, -a[i].c);
	}
	for (int i = 1; i <= n; i++) ans = max(ans, f[i] + g[i] - a[i].p);
	out(ans, endl);
}
signed main() {
	// freopen(".in", "r", stdin);
	// freopen(".out", "w", stdout);
	// ios::sync_with_stdio(0);
	// cin.tie(0), cout.tie(0);
	int t = 1;
	while (t--) {
		init();
		work();
	}
	return 0;
}
```

---

