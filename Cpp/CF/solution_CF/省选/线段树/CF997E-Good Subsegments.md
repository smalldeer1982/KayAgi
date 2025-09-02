# Good Subsegments

## 题目描述

A permutation $ p $ of length $ n $ is a sequence $ p_1, p_2, \ldots, p_n $ consisting of $ n $ distinct integers, each of which from $ 1 $ to $ n $ ( $ 1 \leq p_i \leq n $ ) .

Let's call the subsegment $ [l,r] $ of the permutation good if all numbers from the minimum on it to the maximum on this subsegment occur among the numbers $ p_l, p_{l+1}, \dots, p_r $ .

For example, good segments of permutation $ [1, 3, 2, 5, 4] $ are:

- $ [1, 1] $ ,
- $ [1, 3] $ ,
- $ [1, 5] $ ,
- $ [2, 2] $ ,
- $ [2, 3] $ ,
- $ [2, 5] $ ,
- $ [3, 3] $ ,
- $ [4, 4] $ ,
- $ [4, 5] $ ,
- $ [5, 5] $ .

You are given a permutation $ p_1, p_2, \ldots, p_n $ .

You need to answer $ q $ queries of the form: find the number of good subsegments of the given segment of permutation.

In other words, to answer one query, you need to calculate the number of good subsegments $ [x \dots y] $ for some given segment $ [l \dots r] $ , such that $ l \leq x \leq y \leq r $ .

## 样例 #1

### 输入

```
5
1 3 2 5 4
15
1 1
1 2
1 3
1 4
1 5
2 2
2 3
2 4
2 5
3 3
3 4
3 5
4 4
4 5
5 5
```

### 输出

```
1
2
5
6
10
1
3
4
7
1
2
4
1
3
1
```

# 题解

## 作者：litble (赞：41)

[安利个人博客](https://blog.csdn.net/litble/article/details/80939776)

我除了[WXH天下第一](https://blog.csdn.net/wxh010910/article/details/80885802)还能说什么呢......

所谓好区间，就是$(max-min)-(r-l)=0$的区间。

我们将所有询问离线，按照右端点从小到大排序。然后从左到右处理每一个右端点，每次处理时，线段树里维护一下对于每个左端点（这个只需要用单调栈来处理最小值和最大值的更新即可），$(max-min)-(r-l)$的最小值，那么如果一个区间的最小值为0，最小值个数就是右端点固定，左端点取在这个区间内的时候，好区间的个数。

但是我们要维护的是一个区间内所有子区间，不仅仅是右端点是$r$的区间。

引入一个新标记$time$，表示当前这个最小值个数的贡献，要添加到答案里多少次。我们每次移动右端点的时候，要先把整个线段树的time加1，表示还没移动之前的右端点造成的贡献要添加到答案里一次，这样我们就可以维护对于每个左端点，右端点小于等于当前处理的右端点时，好区间个数。那么每次更新询问的答案，只要区间查询即可。

有几个要注意的实现细节，写在代码里了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
typedef long long LL;
const int N=120005;
int n,Q,top1,top2;
int a[N],mi[N<<2],js[N<<2],laz[N<<2],ti[N<<2],st1[N],st2[N];
//mi:最小值 js:最小值个数 laz:最小值的加减标记 ti:答案更新标记 ans:区间答案
LL ans[N<<2],res[N];
struct node{int l,r,id;}q[N];
int cmp(node x,node y) {return x.r<y.r;}

void addmi(int i,int num) {mi[i]+=num,laz[i]+=num;}
void addti(int i,int num) {ans[i]+=1LL*js[i]*num,ti[i]+=num;}
void pd(int i) {
	int l=i<<1,r=(i<<1)|1;
	if(laz[i]) addmi(l,laz[i]),addmi(r,laz[i]),laz[i]=0;//先下放laz，再下放ti
	if(ti[i]) {//右端点取r时，[r,r]肯定是0，所以整棵线段树的最小值是0
		if(mi[l]==mi[i]) addti(l,ti[i]);
		if(mi[r]==mi[i]) addti(r,ti[i]);
		//在做这个过程时，可能一次移动右端点更新还没有完成，又已经下放了laz，所以不能写成mi[l]==0
		ti[i]=0;
	}
}
void up(int i) {
	int l=i<<1,r=(i<<1)|1;
	mi[i]=min(mi[l],mi[r]),js[i]=0;
	if(mi[l]==mi[i]) js[i]+=js[l];
	if(mi[r]==mi[i]) js[i]+=js[r];
	ans[i]=ans[l]+ans[r];
}
void build(int s,int t,int i) {
	mi[i]=s,js[i]=1;//一开始将mi[i]=s，最小值个数的计算才是对的。
	if(s==t) return;
	int mid=(s+t)>>1;
	build(s,mid,i<<1),build(mid+1,t,(i<<1)|1);
}
void add(int l,int r,int s,int t,int i,int num) {
	if(l<=s&&t<=r) {addmi(i,num);return;}
	int mid=(s+t)>>1;pd(i);
	if(l<=mid) add(l,r,s,mid,i<<1,num);
	if(mid+1<=r) add(l,r,mid+1,t,(i<<1)|1,num);
	up(i);
}
LL query(int l,int r,int s,int t,int i) {
	if(l<=s&&t<=r) return ans[i];
	int mid=(s+t)>>1;LL re=0;pd(i);
	if(l<=mid) re=query(l,r,s,mid,i<<1);
	if(mid+1<=r) re+=query(l,r,mid+1,t,(i<<1)|1);
	return re;
}
int main()
{
    int x,y;
    n=read();
    for(RI i=1;i<=n;++i) a[i]=read();
    Q=read();
    for(RI i=1;i<=Q;++i) q[i].l=read(),q[i].r=read(),q[i].id=i;
    sort(q+1,q+1+Q,cmp);
    build(1,n,1);
    for(RI i=1,j=1;i<=n;++i) {
    	addmi(1,-1);
    	while(top1&&a[i]>a[st1[top1]]) {
    		add(st1[top1-1]+1,st1[top1],1,n,1,a[i]-a[st1[top1]]);
    		--top1;
    	}
    	st1[++top1]=i;
    	while(top2&&a[i]<a[st2[top2]]) {
    		add(st2[top2-1]+1,st2[top2],1,n,1,a[st2[top2]]-a[i]);
    		--top2;
    	}
    	st2[++top2]=i;
    	addti(1,1);//打一个time标记，把当前右端点造成的贡献下放
    	while(j<=Q&&q[j].r==i) res[q[j].id]=query(q[j].l,q[j].r,1,n,1),++j;
    }
    for(RI i=1;i<=Q;++i) printf("%lld\n",res[i]);
    return 0;
}
//stone 0
```


---

## 作者：红色OI再临 (赞：28)

我不会，我来理一下思路

1. 好区间的性质：

区间内`(max-min)-(r-l)=0`这样的区间就是好区间

2. 怎么做

网上看的一个套路： 对于询问区间子序列的信息，可以离线移动右指针，类似扫描线一样计算贡献

之前CF好像也有一个这样的题，是求最长的好区间，思路跟这道题目差不多，只是维护的东西不一样（没找到别说我无中生题.jpg）

于是在当前指针`r`下维护一个`(max−min)−(r−l)`的最小值以及最小值个数，将询问离线（因为要用到当前的指针`r`，对于`max`和`min`，我们可以用一个单调栈维护，就可以很方便的更新区间的上述柿子的`max`，`min`


然后线段树内维护一个答案`ans`，代表某个区间上述柿子最小值的贡献，因为树根一定是`0`，所以判断每次下放标记的时候只要判断儿子的最小值是否与父亲相等即可。

但是发现这样不行，我们只是维护了一个右端点为`r`的区间的贡献，题目我们还要求我们求子区间的好区间的个数，于是维护一个`lazy2`贡献数组，维护历史出现的最小值的贡献。

3. 算法流程：

每次r向右边移动的流程：


1. 树根维护的上述柿子最小值减小1

2. 单调栈更新，维护最大值与最小值变化，每次弹栈的时候将上个栈顶+1到当前栈顶的这一段区间的上述柿子最小值`+abs(a[r]-a[top])再弹栈

3. 给当前区间打上贡献数组的`tag`

4. 处理右段端点为`r`的询问

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<stack>
#define re register ll
#define ll long long
#define int long long
#define maxn 200050
using namespace std;
struct tree{
	int l,r,mmin,num,lazy,lazy2,ans;
	//最小值，最小值个数，最小值加减标记，答案标记，答案
}t[maxn<<2];
struct node{
	int l,r,id;
}q[maxn];
bool comp(node aa,node bb){
	return aa.r<bb.r;
}	
void addmmin(int now,int num){
	t[now].mmin+=num;
	t[now].lazy+=num;
}
void addans(int now,int num){
	t[now].ans+=t[now].num*num;
	t[now].lazy2+=num;
}
void pushdown(int now){
	if(t[now].lazy){
		addmmin(now<<1,t[now].lazy);
		addmmin(now<<1|1,t[now].lazy);
		t[now].lazy=0;
	}
	if(t[now].lazy2){
	if(t[now<<1].mmin==t[now].mmin)addans(now<<1,t[now].lazy2);
	if(t[now<<1|1].mmin==t[now].mmin)addans(now<<1|1,t[now].lazy2);			
//下放标记的时候更新答案看是不是跟自己一样，如果子区间最小值跟自己一样才进行更新。
//因为树根为0,我实际上是在判断0
	t[now].lazy2=0;
	}
}
void pushup(int now){
	t[now].mmin=min(t[now<<1].mmin,t[now<<1|1].mmin);
	t[now].num=0;
	if(t[now<<1].mmin==t[now].mmin)t[now].num+=t[now<<1].num;
	if(t[now<<1|1].mmin==t[now].mmin)t[now].num+=t[now<<1|1].num;
	t[now].ans=t[now<<1].ans+t[now<<1|1].ans;
}
void build(int now,int l,int r){
	t[now].l=l;
	t[now].r=r;
	t[now].mmin=l;//初始时每个区间的????????是它自己的左端点，因为每次是对整颗树的区间打的标记，会减去很多次1
	t[now].num=1;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
}
void change(int now,int l,int r,int val){
	if(l<=t[now].l&&t[now].r<=r){
		addmmin(now,val);
		return;
	}
	pushdown(now);
	int mid=(t[now].l+t[now].r)>>1;
	if(l<=mid)change(now<<1,l,r,val);
	if(r>mid)change(now<<1|1,l,r,val);
	pushup(now);
}
int ask(int now,int l,int r){
	if(l<=t[now].l&&t[now].r<=r)return t[now].ans;
	pushdown(now);
	int mid=(t[now].l+t[now].r)>>1;
	int anss=0;
	if(l<=mid)anss+=ask(now<<1,l,r);
	if(r>mid)anss+=ask(now<<1|1,l,r);
	return anss;
}
int n,m;
//stack<int>smax,smin;
int smax[maxn],smin[maxn];
int top1,top2=0;
int a[maxn],ans[maxn];
signed main(){
//	freopen("large.in","r",stdin);
//	freopen("large.out","w",stdout);
	scanf("%lld",&n);
	for(re i=1;i<=n;i++)
	scanf("%lld",&a[i]);
	scanf("%lld",&m);
	for(re i=1;i<=m;i++){
		scanf("%lld%lld",&q[i].l,&q[i].r),q[i].id=i;
	}
	sort(q+1,q+1+m,comp);
	build(1,1,n);
	//a[0]=1000000000000000000;
	//smax.push(0);
	//a[n+1]=-1000000000000000000;
	//smin.push(n+1);
	for(re i=1,j=1;i<=n;i++){
		addmmin(1,-1);
		
		//每次将区间r右移
		while(top1&&a[smax[top1]]<a[i]){
			/*int now2=smax.top()\
			smax.pop();
			int now=smax.top();
			
			change(1,now+1,now2,a[i]-a[now2]);*/
			change(1,smax[top1-1]+1,smax[top1],a[i]-a[smax[top1]]);
			top1--;
	//这个区间内now+1——now2 整体加上a[i]-a[smax.top()]
	//因为我更新了最大值	
	//下面的单调栈同理	
		}
		//smax.push(i);
		smax[++top1]=i;
		/*while(!smin.empty()&&a[smin.top()]>a[i]){
			int now2=smin.top();
			smin.pop();
			int now=smin.top();
			//printf("%d %d\n",now,now2);
			change(1,now+1,now2,a[now2]-a[i]);
		}	
		smin.push(i);*/
		while(top2&&a[i]<a[smin[top2]]) {
            change(1,smin[top2-1]+1,smin[top2],a[smin[top2]]-a[i]);
            --top2;
        }
        smin[++top2]=i;
		addans(1,1);
		while(q[j].r==i&&j<=m)ans[q[j].id]=ask(1,q[j].l,q[j].r),j++;
	}
	for(re i=1;i<=m;i++){
		printf("%lld\n",ans[i]);
	}
//(max-min)-(r-l);
	

	return 0;
}
```



---

## 作者：Social_Zhao (赞：20)

本题的析合树在线解法，并不是 @Time_tears 椰叶所说的把树状数组换成主席树那种（

首先建出析合树，实际上本题我们要求的就是析合树上所有被查询区间完全包含的节点的内部贡献和他们之间的贡献。

先考虑一个弱化版的问题，即全局查询，设

$$
val_u=
\begin{cases}
	\begin{aligned}
		&1& \text{u 是析点}\\
		&C_{|son_u|}^{2}& \text{u 是合点}
	\end{aligned}
\end{cases}
$$

那么答案就是 $\sum\limits_{i=1}^{cnt}val_i$，$cnt$ 是析合树的节点数。

于是现在的问题是如何求出被查询区间完全包含的节点，我们找到这些点并加上他们的子树和即可，但这样可能存在一个合点没有被完全包含，而其儿子序列的一个子段被完全包含，我们还需加上这些被包含的子段中儿子之间的贡献。

那么我们对于每个点维护下面两个值：

- $pre_u$，表示 $u$ 在其父亲的儿子序列（下面简称兄弟序列）上对应的后缀（不包含本身）的子树和，如果其父亲是合点，还要加上这个后缀相互之间的贡献。
- $suf_u$，同理。
- $rk_u$，$u$ 在兄弟序列上的排名

显然包含 $l-1$ 和 $r+1$ 的节点不应该被统计进答案，那么我们可以从 $l-1$ 开始向上跳，在每个节点处加上 $suf_u$，以及从 $r+1$ 开始向上跳，加上 $pre_u$。最后在 $lca$ 的儿子（假设是 $x$ 和 $y$）处，如果 $lca$ 是合点，那么加上 $[x+1, y-1]$ 的子树和加 $C_{y-x-1}^{2}$，否则只加上 $[x+1, y-1]$ 的子树和。

显然上述过程可以用倍增来优化。也许可以通过各种科技优化到 $O(n)$ 预处理，$O(1)$ 回答某组询问。

具体细节见代码：

因为写了 1h+ 降智严重，所以代码很丑（

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int get() {
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) { if(c == '-') f = -1; c = getchar(); }
	while(isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
	return x * f;
}

const int N = 5e5 + 5;
int n, a[N], m;
vector<int> son[N];
int st1[N], tp1, st2[N], tp2, st[N], tp, id[N], cnt, L[N], R[N], M[N], typ[N], rt;
int dep[N], f[N][20];
int pre[N], suf[N], sze[N], sum[N], rk[N];

void add(int u, int v) { son[u].push_back(v); }

namespace RMQ {
	int lg[N];
	struct Node {
		int mn, mx;
		Node(int x = 0, int y = 0) { mn = x, mx = y; }
		Node operator +(Node b) const { return Node(min(mn, b.mn), max(mx, b.mx)); }
	} t[N][20];
	void init() {
		lg[0] = -1; for(int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1, t[i][0] = Node(a[i], a[i]);
		for(int j = 1; j <= 19; j++)
			for(int i = 1; i + (1 << j) - 1 <= n; i++)
				t[i][j] = t[i][j - 1] + t[i + (1 << j - 1)][j - 1];
	}
	Node ask(int l, int r) {
		int len = lg[r - l + 1];
		return t[l][len] + t[r - (1 << len) + 1][len];
	}
}

namespace SMT {
	#define lc (u << 1)
	#define rc (u << 1 | 1)
	#define mid (l + r >> 1)
	int mx[N << 2], tag[N << 2];
	void pushup(int u) { mx[u] = min(mx[lc], mx[rc]); }
	void pusha(int u, int v) { mx[u] += v, tag[u] += v; }
	void pushdown(int u) { if(tag[u]) pusha(lc, tag[u]), pusha(rc, tag[u]), tag[u] = 0; }
	void update(int u, int l, int r, int a, int b, int v) {
		if(a == l && r == b) return pusha(u, v);
		pushdown(u);
		if(b <= mid) update(lc, l, mid, a, b, v);
		else if(a > mid) update(rc, mid + 1, r, a, b, v);
		else update(lc, l, mid, a, mid, v), update(rc, mid + 1, r, mid + 1, b, v);
		pushup(u);
	}
	int query(int u, int l, int r) {
		if(l == r) return l;
		pushdown(u);
		if(!mx[lc]) return query(lc, l, mid);
		else return query(rc, mid + 1, r);
	}
}

int judge(int l, int r) { return (RMQ::ask(l, r).mx - RMQ::ask(l, r).mn == r - l); }
int S(int n) { return n * (n - 1) / 2; }

void build() {
	for(int i = 1; i <= n; i++) {
		while(tp1 && a[i] <= a[st1[tp1]]) SMT::update(1, 1, n, st1[tp1 - 1] + 1, st1[tp1], a[st1[tp1]]), tp1--;
		while(tp2 && a[i] >= a[st2[tp2]]) SMT::update(1, 1, n, st2[tp2 - 1] + 1, st2[tp2], -a[st2[tp2]]), tp2--;
		SMT::update(1, 1, n, st1[tp1] + 1, i, -a[i]), st1[++tp1] = i;
		SMT::update(1, 1, n, st2[tp2] + 1, i, a[i]), st2[++tp2] = i;
		id[i] = ++cnt, L[cnt] = R[cnt] = i;
		int lst = SMT::query(1, 1, n), now = cnt;
		while(tp && L[st[tp]] >= lst) {
			if(typ[st[tp]] && judge(M[st[tp]], i)) R[st[tp]] = i, add(st[tp], now), now = st[tp--];
			else if(judge(L[st[tp]], i)) typ[++cnt] = 1, L[cnt] = L[st[tp]], R[cnt] = i, M[cnt] = L[now], add(cnt, st[tp--]), add(cnt, now), now = cnt;
			else {
				add(++cnt, now);
				do {
					add(cnt, st[tp--]);
				} while(tp && !judge(L[st[tp]], i));
				L[cnt] = L[st[tp]], R[cnt] = i, add(cnt, st[tp--]), now = cnt;
			}
		}
		st[++tp] = now, SMT::update(1, 1, n, 1, i, -1);
	}
	rt = st[tp];
}

// 上面是析合树建树部分。

// 预处理倍增数组 f，子树和 size，前缀后缀和 pre，suf。
void dfs(int u, int fa) {
	f[u][0] = fa, dep[u] = dep[fa] + 1;
	sze[u] = typ[u]? ((int)son[u].size() * ((int)son[u].size() - 1) / 2) : (1);
	for(int i = 1; i <= 19; i++) f[u][i] = f[f[u][i - 1]][i - 1];
	int tmp = 0;
	for(int i = 0; i < son[u].size(); i++) {
		int v = son[u][i];
		dfs(v, u), sze[u] += sze[v], pre[v] = tmp + (typ[u]? S(i) : 0), tmp += sze[v], sum[v] = tmp, rk[v] = i + 1;
	}
	tmp = 0;
	for(int i = (int)son[u].size() - 1; i >= 0; i--) { 
		int v = son[u][i]; suf[v] = tmp + (typ[u]? S((int)son[u].size() - 1 - i) : 0), tmp += sze[v];
	}
}

// 树上前缀和
void df5(int u, int fa) {
	pre[u] += pre[fa], suf[u] += suf[fa];
	for(int i = 0; i < son[u].size(); i++) { int v = son[u][i]; df5(v, u); }
}

int GetLCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 19; i >= 0; i--) if(dep[f[x][i]] >= dep[y]) x = f[x][i];
	if(x == y) return x;
	for(int i = 19; i >= 0; i--) if(f[x][i] ^ f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}

int jump(int x, int y) {
	for(int i = 19; i >= 0; i--) if(dep[f[x][i]] > dep[y]) x = f[x][i];
	return x;
}

// 查询左右端点都平凡的情况
int query(int l, int r) {
	int lca = GetLCA(id[l - 1], id[r + 1]), x = jump(id[l - 1], lca), y = jump(id[r + 1], lca);
	int res = suf[id[l - 1]] - suf[x] + pre[id[r + 1]] - pre[y] + sum[y] - sum[x] - sze[y];
	if(typ[lca] == 1) res += S(rk[y] - rk[x] - 1);
	return res;
}

// 查询两种特殊情况
int queryPre(int r) {
	int x = jump(id[r + 1], rt);
	return pre[id[r + 1]] - pre[x] + sum[x] - sze[x] + (typ[rt]? S(rk[x] - 1) : 0);
}

int querySuf(int l) {
	int x = jump(id[l - 1], rt);
	return suf[id[l - 1]] - suf[x] + sum[(int)son[rt][son[rt].size() - 1]] - sum[x] + (typ[rt]? S(son[rt].size() - rk[x]) : 0);
}

signed main() {
	n = get();
	for(int i = 1; i <= n; i++) a[i] = get();
	RMQ::init(), build();
	for(int i = 1; i <= cnt; i++) sort(son[i].begin(), son[i].end(), [](int x, int y) { return L[x] < L[y]; });
	dfs(rt, 0);
	df5(rt, 0);
	m = get();
	while(m--) {
		int l = get(), r = get();
		if(l == 1 && r == n) printf("%lld\n", sze[rt]); // 因为懒得加哨兵所以加了一堆分类讨论
		else if(l != 1 && r == n) printf("%lld\n", querySuf(l));
		else if(l == 1 && r != n) printf("%lld\n", queryPre(r));
		else printf("%lld\n", query(l, r));
	}
	return 0;
}
```

---

## 作者：jiazhaopeng (赞：17)

可以先做一下弱化版：[CF526F Pudding Monsters](https://www.luogu.com.cn/problem/CF526F)，那道题是本题的基础。

由于这是个排列，因此好区间可以转化为满足 $max - min = r - l$ 的区间。其中 $max,min$ 分别表示区间最大值和最小值，$l,r$ 分别表示区间左右端点。我们可以枚举 $r$，那么限制变为 $max - min + l = r$。又因为对于所有区间，都有 $max - min >= r - l$，所以好区间可以转化为“以 $r$ 为右端点，且 $max - min + l$ 最小左端点的个数”。

我们从左往右扫一遍，用单调栈和线段树维护最值，扫的时候顺便统计一下全局最小值个数，这就是前面那道题的做法。

对于这道题，我们可以离线，将询问挂到右端点，“子区间”转化为“前缀的后缀”。如果只考虑一个前缀的所有后缀的答案，这题只不过多限制左端点的范围，不能小于 $L$，这个好说，查全局最小值个数改为查区间最小值个数即可。再考虑所有前缀的贡献，这个可以直接在线段树上打“历史贡献”的标记，查询就把节点的“历史贡献”加和即可。

总结一下，我们需要一棵线段树，支持区间加，单点修改，区间查历史贡献。还需要俩单调栈，维护最大最小值，并在线段树上进行操作。

细节看代码吧。

$Code:$

```cpp
#define N 201000
#define NN 801000
#define int long long
template <typename T> inline void read(T &x) {
	x = 0; char c = getchar(); bool flag = false;
	while (!isdigit(c)) { if (c == '-')	flag = true; c = getchar(); }
	while (isdigit(c)) { x = (x << 1) + (x << 3) + (c ^ 48); c = getchar(); }
	if (flag)	x = -x;
}
using namespace std;
const int inf = 987654321;
int n;
int h[N];
struct edge{
	int nxt, to, id;
}e[N];
int head[N], ecnt;
inline void addedge(int from, int to, int id) {//邻接表挂询问
	e[++ecnt] = (edge){head[from], to, id};
	head[from] = ecnt;
}
int ans[N];

struct node {
	int mn, cnt;
	node(int mnn = inf, int cntt = 0) { mn = mnn, cnt = cntt; }
	node operator +(const node a) const {
		return node(min(mn, a.mn), mn == a.mn ? cnt + a.cnt : (mn < a.mn ? cnt : a.cnt));
	}
}nd[NN];
int ls[NN], rs[NN], atag[NN], ctag[NN], res[NN], root, ttot;
void build(int L, int R, int &cur) {
	cur = ++ttot;
	if (L == R)	return ;
	int mid = (L + R) >> 1;
	build(L, mid, ls[cur]);
	build(mid + 1, R, rs[cur]);
}
inline void pushup(int cur) {
	nd[cur] = nd[ls[cur]] + nd[rs[cur]];
}
inline void pusha(int cur, int v) {//打加法标记
	if (!cur)	return ;
	nd[cur].mn += v;
	atag[cur] += v;
}
inline void pushc(int cur, int mn, int c) {//打历史标记
	if (!cur || nd[cur].mn != mn)	return ;
    //只有儿子最小值和父亲相同时才能继承贡献
	res[cur] += nd[cur].cnt * c;
	ctag[cur] += c;
}
inline void pushdown(int cur) {//下放标记。注意顺序
	if (atag[cur])
		pusha(ls[cur], atag[cur]), pusha(rs[cur], atag[cur]), atag[cur] = 0;
	if (ctag[cur])
		pushc(ls[cur], nd[cur].mn, ctag[cur]), 
		pushc(rs[cur], nd[cur].mn, ctag[cur]), 
		ctag[cur] = 0;
}
void modify(int L, int R, int l, int r, int v, int cur) {//区间加
	if (l <= L && R <= r) {
		pusha(cur, v);
		return ;
	}
	pushdown(cur);
	int mid = (L + R) >> 1;
	if (l <= mid)	modify(L, mid, l, r, v, ls[cur]);
	if (r > mid)	modify(mid + 1, R, l, r, v, rs[cur]);
	pushup(cur);
}
void modify(int L, int R, int pos, int v, int cur) {//单点修改
	if (L == R)	return nd[cur] = (node){v, 1}, void();
	pushdown(cur);
	int mid = (L + R) >> 1;
	if (pos <= mid)	modify(L, mid, pos, v, ls[cur]);
	else	modify(mid + 1, R, pos, v, rs[cur]);
	pushup(cur);
}
int query(int L, int R, int l, int r, int cur) {
	if (l <= L && R <= r)	return res[cur];
	pushdown(cur);
	int mid = (L + R) >> 1, tmp = 0;
	if (l <= mid)	tmp = query(L, mid, l, r, ls[cur]);
	if (r > mid)	tmp += query(mid + 1, R, l, r, rs[cur]);
	return tmp;
}

struct Seg {//单调栈
	int l, r, v;//l ~ r 的最值都是 v
	Seg(int ll = 0, int rr = 0, int vv = 0) { l = ll, r = rr, v = vv; }
	bool operator <(const Seg a) const {
		return v < a.v;
	}
	bool operator >(const Seg a) const {
		return v > a.v;
	}
}smx[N], smn[N];
int mxtop, mntop;

signed main() {
	read(n);
	for (register int i = 1; i <= n; ++i)	read(h[i]);
	int q; read(q);
	for (register int i = 1; i <= q; ++i) {
		int l, r; read(l), read(r);
		addedge(r, l, i);
	}
	build(1, n, root);
	for (register int i = 1; i <= n; ++i) {
    	//维护最值
		Seg s(i, i, h[i]);
		while (mxtop && s > smx[mxtop])
			modify(1, n, smx[mxtop].l, smx[mxtop].r, h[i] - smx[mxtop].v, root),
			s.l = smx[mxtop].l, --mxtop;
		smx[++mxtop] = s;
		
		s = Seg(i, i, h[i]);
		while (mntop && s < smn[mntop])
			modify(1, n, smn[mntop].l, smn[mntop].r, -h[i] + smn[mntop].v, root),
			s.l = smn[mntop].l, --mntop;
		smn[++mntop] = s;
		
		modify(1, n, i, i, root);//插入新点
		
		pushc(root, i, 1);//将当前的合法区间计入贡献
		for (register int j = head[i]; j; j = e[j].nxt) {
			int l = e[j].to, id = e[j].id;
			ans[id] = query(1, n, l, i, root);
		}
	}
	for (register int i = 1; i <= q; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：chenxia25 (赞：14)

### 歪解

一个显然的 observation 是区间 $l,r$ 合法当且仅当 $mx_r-mx_l=r-l$。一开始想这题的时候感觉这东西根本不可维护好吧……那就开始想一些奇怪的数据结构题的算法（比如离线分治或者根号算法或者数据分治），然后想到了分块。就~~愉快地~~开始用分块做啦（1.2e5 7s 感觉很可行）！

设每块大小 $S$。那么分成左边零散的、右边零散的、中间整块三段，分别记为 L、R、M。设 XY（不是染色体啦）表示左端点在 X，右端点在 Y，则总共分成 6 种贡献：LL、LM、LR、MM、MR、RR。然后还有询问中的 $l,r$ 在同一块的特殊情况。以及 MM 的贡献又分成同块和不同块。

LL 是某一块的后缀，RR 是某一块的前缀，$l,r$ 在同一块是某一块的子区间，MM 的第一部分是整块。这四者中第三者最强，解决它就解决所有的了。这其实很容易预处理：有 $n$ 个位置，每个位置往右边最多去 $S$ 格，所以只有 $\mathrm O(nS)$ 个值要预处理，需要均摊常数。那对于每块暴力枚举出来所有合法区间（如何 $\mathrm O(1)$ 判？ST 表维护 rmq 即可），然后计算该块内的子区间内有多少个合法子区间，就是个二维前缀和的事情了。复杂度 $\mathrm O\!\left(\dfrac nSS^2\right)=\mathrm O(nS)$。

剩下中的 LM、MR 是不完整的块对整块的贡献，MM 的第二部分是完整的块对完整的块的贡献，貌似前者要强一点。考虑到一般分块对不完整块的处理办法都是暴力枚举，我们这里也尝试这样，那么只需要预处理出每个点对每个块的贡献（然后对块的那一维求前缀和，这 extremely easy）即可，这只有 $\mathrm O\!\left(n\dfrac nS\right)=\mathrm O\!\left(\dfrac{n^2}S\right)$ 个值要计算（同样需要均摊常数（或 log？）╮(╯▽╰)╭）。如果这个能解决，那么对于 MM 的第二部分，只需要根据预处理出来的东西再预处理块对块的贡献的前缀和即可，这是 easy 的；以及对 LR 可以用类似的方法现场搞。所以接下来的任务就是全心全意想办法预处理这个东西。

考虑枚举两个块，计算左边块的元素对右边整块的贡献（当然反过来也要计算，与前者过程类似，这里以前者举例）。这东西其实很像 cdq 分治的处理的核心部分，从中间切了一刀，只能左边向右边贡献，就很舒适。那么把两块中间一部分的 max / min 搞出来混到两边，两块中的元素的 $mx_i$ 表示该位置到中间的 max，$mn_i$ 类似，那么易证两者在两块不同方向的单调性。那么左边的 $i$ 和右边的 $j$ 满足条件当且仅当 $\max(mx_i,mx_j)-\min(mn_i,mn_j)=j-i$。

由于左块要细化到每个元素，所以肯定从中间往左边枚举左块的元素。这时候对上式的处理，可以分成 $mx_i?mx_j,mn_i?mn_j$ 四类，分别可以列出 $f(j)=g(i)$ 的式子。那就把四类分别对应的 $f(j)$ 全部装在桶里。又根据单调性，可以 two-pointers 好吧。但是这一部分常数真的很大很大（你想想，四类，还 `vector`）（但是可以调参不是么，而且 TL = 7s，方个 hammer class），也很难写很难写，能把人搞崩溃的好吧（虽然我没崩溃）。

复杂度 $\mathrm O\!\left(nS+\dfrac{n^2}S+qS\right)$（$qS$ 是因为 LR 仿照上面预处理的方式现场搞），先设个 $S=\sqrt n$ 再说。然后考虑实现细节。首先上面预处理了两个 $\mathrm O(n\sqrt n)$ 的数组是吧，就算开了 `int` instead of `long long`，也 540MB 左右，超过了 ML = 512MB。但是你发现第一个数组其实只用了 1/2（因为区间有 $l\leq r$ 的限制对吧），那就映射一下，今后空间不成问题。然后卡常。注意到上面这个常数很大的部分要算两遍（左对右 and vice versa），而现场搞只需要搞一遍，那么 $S$ 应该稍大一点（此处认为 $n=q$（？）），大概是翻个 $\sqrt 2$ 倍的样子吧。经过不懈的尝试，在 $S=1.618\sqrt n$ 开 Ofast（O3 都不行 hh）的情况下以 6988ms 的运行时间 A 掉了。

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=150000,LOG_N=20,SZ=800,SZ0=250;
int n,qu,sz,sz1;
int a[N];
struct stable{
	signed mn[N][LOG_N],mx[N][LOG_N],_log[N];
	void init(){
		for(int i=2;i<=n;i++)_log[i]=_log[i-1]+(i==1<<_log[i-1]+1);
		for(int i=1;i<=n;i++)mn[i][0]=mx[i][0]=a[i];
		for(int j=1;j<LOG_N;j++)for(int i=1;i+(1<<j)-1<=n;i++)
			mn[i][j]=min(mn[i][j-1],mn[i+(1<<j-1)][j-1]),mx[i][j]=max(mx[i][j-1],mx[i+(1<<j-1)][j-1]);
	}
	int _mn(int l,int r){
		if(l>r)return inf;
		int log0=_log[r-l+1];
		return min(mn[l][log0],mn[r-(1<<log0)+1][log0]);
	}
	int _mx(int l,int r){
		if(l>r)return -inf;
		int log0=_log[r-l+1];
		return max(mx[l][log0],mx[r-(1<<log0)+1][log0]);
	}
}st;
signed inside[N][SZ/2];
int Sum[SZ][SZ];
signed cnt[N][SZ0];
int mn[N],mx[N];
vector<signed> xnl[3*N],nl[3*N],xl[3*N];
short xnl0[3*N],nl0[3*N],xl0[3*N];
short xnl1[3*N],nl1[3*N],xl1[3*N];
int eqrg(vector<signed> ll[],short l0[],short l1[],int l,int r,int v){
	while(l0[v]+1<ll[v].size()&&ll[v][l0[v]+1]<l)l0[v]++;
	while(l1[v]+1<ll[v].size()&&ll[v][l1[v]+1]<=r)l1[v]++;
	return max(0,l1[v]-l0[v]);
}
int eqrg0(vector<signed> ll[],short l0[],short l1[],int l,int r,int v){
	while(l0[v]+1<ll[v].size()&&ll[v][l0[v]+1]>l)l0[v]++;
	while(l1[v]+1<ll[v].size()&&ll[v][l1[v]+1]>=r)l1[v]++;
	return max(0,l1[v]-l0[v]);
}
int rgcnt[SZ][SZ];
signed &id(int x,int len){
	int p=(x+sz1-1)/sz1;
	int l=sz1*(p-1)+1;
	x=x-l+1;
	return inside[l][(sz1+sz1-x+2)*(x-1)/2+len];
}
signed main(){
//	cout<<(sizeof(inside)+sizeof(cnt)+sizeof(st)+2*sizeof(Sum)+4*sizeof(xnl)+8*sizeof(xnl0))/1024/1024;
//	freopen("read.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
//	cout<<clock()<<"!\n";
	st.init();
	sz1=1.618*sqrt(n),sz=(n+sz1-1)/sz1;
	for(int i=1;i<=sz;i++){
		memset(Sum,0,sizeof(Sum));
		int l=sz1*(i-1)+1,r=min(n,sz1*i);
		for(int j=l;j<=r;j++)for(int k=j;k<=r;k++)if(st._mx(j,k)-st._mn(j,k)==k-j)Sum[j-l+1][k-l+1]=1;
		for(int j=1;j<=r-l+1;j++)for(int k=1;k<=r-l+1;k++)Sum[j][k]+=Sum[j-1][k]+Sum[j][k-1]-Sum[j-1][k-1];
		for(int j=l;j<=r;j++)for(int k=j;k<=r;k++)id(j,k-j+1)=Sum[r-l+1][k-l+1]-Sum[j-l][k-l+1];
	}
//	for(int i=1;i<=n;i++)for(int j=1;j<=sz1;j++)printf("inside[%lld][%lld]=%lld\n",i,j,inside[i][j]);
	#define mem(x) memset(x,-1,sizeof(x))
	mem(xnl0),mem(nl0),mem(xl0),mem(xnl1),mem(nl1),mem(xl1);
	for(int i=1;i<=sz;i++)for(int j=i+1;j<=sz;j++){//remember to make it first
		int l1=sz1*(i-1)+1,r1=min(n,sz1*i),l2=sz1*(j-1)+1,r2=min(n,sz1*j);
		for(int k=l1;k<=r1;k++)mn[k]=st._mn(k,l2-1),mx[k]=st._mx(k,l2-1);
		for(int k=l2;k<=r2;k++)mn[k]=st._mn(r1+1,k),mx[k]=st._mx(r1+1,k);
		for(int k=l2;k<=r2;k++)xnl[mx[k]-mn[k]-k+2*N].pb(k),nl[-mn[k]-k+2*N].pb(k),xl[mx[k]-k+2*N].pb(k);
		int now1=l2-1,now2=l2-1;
		for(int k=r1;k>=l1;k--){
			while(now1<r2&&mn[now1+1]>=mn[k])now1++;while(now2<r2&&mx[now2+1]<=mx[k])now2++;
			cnt[k][j]+=eqrg(xnl,xnl0,xnl1,max(now1+1,now2+1),inf,-k+2*N);
			cnt[k][j]+=eqrg(nl,nl0,nl1,now1+1,now2,-k-mx[k]+2*N);
			cnt[k][j]+=eqrg(xl,xl0,xl1,now2+1,now1,-k+mn[k]+2*N);
			cnt[k][j]+=l2<=k+mx[k]-mn[k]&&k+mx[k]-mn[k]<=min(min(now1,now2),r2);
		}
		for(int k=l2;k<=r2;k++)xnl[mx[k]-mn[k]-k+2*N].clear(),nl[-mn[k]-k+2*N].clear(),xl[mx[k]-k+2*N].clear(),xnl0[mx[k]-mn[k]-k+2*N]=nl0[-mn[k]-k+2*N]=xl0[mx[k]-k+2*N]=xnl1[mx[k]-mn[k]-k+2*N]=nl1[-mn[k]-k+2*N]=xl1[mx[k]-k+2*N]=-1;
	}
	for(int i=1;i<=sz;i++)for(int j=i+1;j<=sz;j++){//remember to make it first
		int l1=sz1*(i-1)+1,r1=min(n,sz1*i),l2=sz1*(j-1)+1,r2=min(n,sz1*j);
		for(int k=l1;k<=r1;k++)mn[k]=st._mn(k,l2-1),mx[k]=st._mx(k,l2-1);
		for(int k=l2;k<=r2;k++)mn[k]=st._mn(r1+1,k),mx[k]=st._mx(r1+1,k);
		for(int k=r1;k>=l1;k--)xnl[mx[k]-mn[k]+k+N].pb(k),nl[-mn[k]+k+N].pb(k),xl[mx[k]+k+N].pb(k);
		int now1=r1+1,now2=r1+1;
		for(int k=l2;k<=r2;k++){
			while(now1>l1&&mn[now1-1]>=mn[k])now1--;while(now2>l1&&mx[now2-1]<=mx[k])now2--;
			cnt[k][i]+=eqrg0(xnl,xnl0,xnl1,min(now1-1,now2-1),0,k+N);
			cnt[k][i]+=eqrg0(nl,nl0,nl1,now1-1,now2,k-mx[k]+N);
			cnt[k][i]+=eqrg0(xl,xl0,xl1,now2-1,now1,k+mn[k]+N);
			cnt[k][i]+=max(l1,max(now1,now2))<=k-mx[k]+mn[k]&&k-mx[k]+mn[k]<=r1;
		}
		for(int k=l1;k<=r1;k++)xnl[mx[k]-mn[k]+k+N].clear(),nl[-mn[k]+k+N].clear(),xl[mx[k]+k+N].clear(),xnl0[mx[k]-mn[k]+k+N]=nl0[-mn[k]+k+N]=xl0[mx[k]+k+N]=xnl1[mx[k]-mn[k]+k+N]=nl1[-mn[k]+k+N]=xl1[mx[k]+k+N]=-1;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=sz+1;j++)cnt[i][j]+=cnt[i][j-1];
//	cout<<cnt[1][3]<<"!\n";
	for(int i=1;i<=sz;i++)for(int j=1;j<=sz+1;j++){
		int l1=sz1*(i-1)+1,r1=min(n,sz1*i);
		for(int k=l1;k<=r1;k++)rgcnt[i][j]+=cnt[k][j];
	}
	cin>>qu;
	while(qu--){
		int l,r;
		scanf("%lld%lld",&l,&r);
		int pl=(l+sz1-1)/sz1,pr=(r+sz1-1)/sz1;
		if(pl==pr){printf("%d\n",id(l,r-l+1));continue;}
		int res=id(l,sz1*pl-l+1)+id(sz1*(pr-1)+1,r-sz1*(pr-1));
		for(int i=pl+1;i<pr;i++)res+=id(sz1*(i-1)+1,sz1);
		for(int i=pl+1;i<pr;i++)res+=rgcnt[i][pr-1]-rgcnt[i][i];
		for(int i=l;i<=sz1*pl;i++)res+=cnt[i][pr-1]-cnt[i][pl];
		for(int i=sz1*(pr-1)+1;i<=r;i++)res+=cnt[i][pr-1]-cnt[i][pl];
		
		int i=pl,j=pr,l1=l,r1=min(n,sz1*i),l2=sz1*(j-1)+1,r2=r;
		for(int k=l1;k<=r1;k++)mn[k]=st._mn(k,l2-1),mx[k]=st._mx(k,l2-1);
		for(int k=l2;k<=r2;k++)mn[k]=st._mn(r1+1,k),mx[k]=st._mx(r1+1,k);
		for(int k=l2;k<=r2;k++)xnl[mx[k]-mn[k]-k+2*N].pb(k),nl[-mn[k]-k+2*N].pb(k),xl[mx[k]-k+2*N].pb(k);
		int now1=l2-1,now2=l2-1;
		for(int k=r1;k>=l1;k--){
			while(now1<r2&&mn[now1+1]>=mn[k])now1++;while(now2<r2&&mx[now2+1]<=mx[k])now2++;
			res+=eqrg(xnl,xnl0,xnl1,max(now1+1,now2+1),inf,-k+2*N);
			res+=eqrg(nl,nl0,nl1,now1+1,now2,-k-mx[k]+2*N);
			res+=eqrg(xl,xl0,xl1,now2+1,now1,-k+mn[k]+2*N);
			res+=l2<=k+mx[k]-mn[k]&&k+mx[k]-mn[k]<=min(min(now1,now2),r2);
		}
		for(int k=l2;k<=r2;k++)xnl[mx[k]-mn[k]-k+2*N].clear(),nl[-mn[k]-k+2*N].clear(),xl[mx[k]-k+2*N].clear(),xnl0[mx[k]-mn[k]-k+2*N]=nl0[-mn[k]-k+2*N]=xl0[mx[k]-k+2*N]=xnl1[mx[k]-mn[k]-k+2*N]=nl1[-mn[k]-k+2*N]=xl1[mx[k]-k+2*N]=-1;
	
		printf("%lld\n",res);
	}
	return 0;
}
```

### 正解

学了一下正解啦。上面我的歪解是在线的。考虑离线下来，那对这个区间查询的问题就很自然的想到扫描线啦——右端点递增，实时维护左端点们处的答案。

首先一路上，$mx_{l,r},mn_{l,r}$ 可以分别用单调栈维护相等段。注意一个事实：直接用单调栈维护二元组 $(mx_{l,r},mn_{l,r})$ 的相等段复杂度是错的！这是做不到的。

反正可以做到对 $(mx_{l,r}-mn_{l,r})-(r-l)$ 这个式子的值关于 $l$ 实时维护啦：前两者单调栈 + 区间增加，第三者区间 -1，第四者不动对吧。先考虑只求右端点为 $r$，左端点为 $l\sim r$ 的合法区间个数，就归约到一个经典问题：区间增加、区间查询 $0$ 的个数。如果没有特殊条件，这个**大概**只能分块做了吧。但是有个很 immortal 的 observation：$(mx_{l,r}-mn_{l,r})-(r-l)$ 这个式子永远大于等于 $0$。证明显然，但是很难观察到。那有了这个 observation，$0$ 由平平无奇的值变成了可能的最小值，那只需要按照 little elephant 那题的 rng 的套路，线段树维护区间最小值以及最小值出现次数即可。

但现在要求的是 $[l,r]$ 内合法子区间的个数啊。如果想让之前的思考派上用场，可以发现这其实就是有史以来（即右端点从 $l$ 到 $r$ 递增的这段时间里），$[l,r]$ 区间中每次查询得到的答案的总和。哟吼，维护历史问题我可来劲了，要知道这也是线段树懒标记擅长维护的东西。我们考虑维护线段树上每个节点区间内的**出现过的历史最小值，以及该历史最小值出现过的历史总次数**。

你用线段树维护这东西得满足：可合并，区间修改的时候分到底可以快速更新，能够设计出可压缩的懒标记并且可以快速下传。维护**当前最小值，当前最小值出现次数，出现过的历史最小值，以及该历史最小值出现过的历史总次数**，第一者和第二者实在是很容易好吧。考虑第三者，思考一般情况：如果一个点处，多次修改都以它为分到底的区间之一，留下了多个懒标记痕迹；有一天我要下传它的懒标记了，我该如何设计**可压缩**的**可下传的**懒标记？

考虑一般情况下，任意时刻需要下传的是一系列区间加的操作（但是操作序列太大了），显然只有加的值是重要的，考虑这个加的值的序列。注意到任意时刻，线段树内的任意处的最小值永远 $\geq 0$ 的这个 observation，那么我这个序列的某一处前缀和如果不是最小，那此时必定整个区间没有 $0$，那就没有用了。也就是我们只需要关心那些前缀和最小的地方。于是我们需要记录，从上一次懒标记被下传到现在的懒标记序列的前缀和中最小的是多少，以及这个最小值出现了多少遍。懒标记设计出来后，一切都 easy 了。

复杂度线对。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define X first
#define Y second
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=150000;
int n,qu;
int a[N];
pair<pair<int,int>,int> qry[N];
bool cmp(pair<pair<int,int>,int> x,pair<pair<int,int>,int> y){return x.X.Y<y.X.Y;}
int ans[N];
struct segtree{
	struct node{int mn,tm,hmn,htm,lz,hlz,hlztm;}nd[N<<2];
	#define mn(p) nd[p].mn
	#define tm(p) nd[p].tm
	#define hmn(p) nd[p].hmn
	#define htm(p) nd[p].htm
	#define lz(p) nd[p].lz
	#define hlz(p) nd[p].hlz
	#define hlztm(p) nd[p].hlztm
	void bld(int l=1,int r=n,int p=1){
		mn(p)=hmn(p)=inf,tm(p)=htm(p)=r-l+1,lz(p)=hlz(p)=hlztm(p)=0;
		if(l==r)return;
		int mid=l+r>>1;
		bld(l,mid,p<<1),bld(mid+1,r,p<<1|1);
	}
	void init(){bld();}
	void sprup(int p){
		if(mn(p<<1)<mn(p<<1|1))mn(p)=mn(p<<1),tm(p)=tm(p<<1);
		else if(mn(p<<1)>mn(p<<1|1))mn(p)=mn(p<<1|1),tm(p)=tm(p<<1|1);
		else mn(p)=mn(p<<1),tm(p)=tm(p<<1)+tm(p<<1|1);
		if(hmn(p<<1)<hmn(p<<1|1))hmn(p)=hmn(p<<1),htm(p)=htm(p<<1);
		else if(hmn(p<<1)>hmn(p<<1|1))hmn(p)=hmn(p<<1|1),htm(p)=htm(p<<1|1);
		else hmn(p)=hmn(p<<1),htm(p)=htm(p<<1)+htm(p<<1|1);
	}
	void tag(int p,int v,int hv,int hvtm){
		if(mn(p)+hv<hmn(p))hmn(p)=mn(p)+hv,htm(p)=tm(p)*hvtm;
		else if(mn(p)+hv==hmn(p))htm(p)+=tm(p)*hvtm;
		mn(p)+=v;
		if(lz(p)+hv<hlz(p))hlz(p)=lz(p)+hv,hlztm(p)=hvtm;
		else if(lz(p)+hv==hlz(p))hlztm(p)+=hvtm;
		lz(p)+=v;
	}
	void sprdwn(int p){
		tag(p<<1,lz(p),hlz(p),hlztm(p)),tag(p<<1|1,lz(p),hlz(p),hlztm(p));
		lz(p)=hlz(p)=hlztm(p)=0;
	}
	void add(int l,int r,int v,int p=1,int tl=1,int tr=n){
		if(l<=tl&&r>=tr)return tag(p,v,v,1);
		sprdwn(p);
		int mid=tl+tr>>1;
		if(l<=mid)add(l,r,v,p<<1,tl,mid);
		if(r>mid)add(l,r,v,p<<1|1,mid+1,tr);
		sprup(p);
	}
	int h0(int l,int r,int p=1,int tl=1,int tr=n){
		if(l<=tl&&r>=tr)return hmn(p)==0?htm(p):0;
		sprdwn(p);
		int mid=tl+tr>>1,res=0;
		if(l<=mid)res+=h0(l,r,p<<1,tl,mid);
		if(r>mid)res+=h0(l,r,p<<1|1,mid+1,tr);
		return res;
	}
}segt;
stack<pair<int,int> > mn,mx;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	cin>>qu;
	for(int i=1;i<=qu;i++)scanf("%lld%lld",&qry[i].X.X,&qry[i].X.Y),qry[i].Y=i;
	sort(qry+1,qry+qu+1,cmp);
	segt.init();
//	puts("ok");
	mn.push(mp(0,0)),mx.push(mp(0,n+1));
	int now=0;
	for(int i=1;i<=n;i++){
		while(a[i]<mn.top().Y){
			int r=mn.top().X,v=mn.top().Y;mn.pop();int l=mn.top().X+1;
			segt.add(l,r,abs(v-a[i]));
		}
		while(a[i]>mx.top().Y){
			int r=mx.top().X,v=mx.top().Y;mx.pop();int l=mx.top().X+1;
			segt.add(l,r,abs(v-a[i]));
		}
		segt.add(i,i,-inf+1);
		mn.push(mp(i,a[i])),mx.push(mp(i,a[i]));
		segt.add(1,i,-1);
		while(now<qu&&qry[now+1].X.Y==i){
			now++;
			ans[qry[now].Y]=segt.h0(qry[now].X.X,qry[now].X.Y);
		}
	}
	for(int i=1;i<=qu;i++)printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：81179332_ (赞：9)

给定一个排列 $a$，定义好区间 $[l,r]$ 为：$(\max\limits_{i=l}^r a_i-\min\limits_{i=l}^ra_i)-(r-l)=0$

多次询问，每次给定一个区间，询问它有多少区间是好区间

---

容易想到枚举右端点，计算左端点贡献，设 $f_l=(\max\limits_{i=l}^r a_i-\min\limits_{i=l}^ra_i)-(r-l)$

因为给定的 $a$ 是一个排列，没有重复元素，所以 $f_l\ge0$

对于一个右端点，$f_r=0$（即取左端点与右端点重合）

所以我们只需要维护区间最小值，而包含右端点的最小值必定等于 $0$，所以我们再维护一下区间最小值的个数，就可以对于一个固定右端点统计答案了

$\max-\min$ 可以用单调栈维护，而 $r-l$ 中，$l$ 是固定的， $r$ 每次加一，所以我们只需要区间减一即可

但是我们要求的是子区间个数，也就是 $r\in[L,R]$ 的答案，所以我们再维护一个标记，来累加历史答案

为什么这个标记下放的时候最小值还是原来的最小值？因为我们在修改最小值的时候一定会先下放标记的

```cpp
//timeuse:40min
const int N = 300010;
int n,q;
struct query { int l,id; };
vector<query> v[N];ll ans[N];
int a[N],st1[N],st2[N],top1,top2;
struct tree { int l,r,minn,lz1,lz2;ll num,sum; }t[N << 2];
#define ls now << 1
#define rs now << 1 | 1
void pushup(int now)
{
	t[now].minn = min(t[ls].minn,t[rs].minn),t[now].num = 0;
	t[now].num += (t[ls].minn == t[now].minn) * t[ls].num;
	t[now].num += (t[rs].minn == t[now].minn) * t[rs].num;
	t[now].sum = t[ls].sum + t[rs].sum;
}
void build(int now,int l,int r)
{
	t[now].l = l,t[now].r = r;
	if(l == r) { t[now].minn = l,t[now].num = 1;return; }
	int mid = l + r >> 1;build(ls,l,mid),build(rs,mid + 1,r);
	pushup(now);
}
void push1(int now,ll v) { t[now].minn += v,t[now].lz1 += v; }
void push2(int now,ll v) { t[now].sum += t[now].num * v,t[now].lz2 += v; }
void pushdown(int now)
{
	if(t[now].lz1) push1(ls,t[now].lz1),push1(rs,t[now].lz1),t[now].lz1 = 0;
	if(t[now].lz2)
	{
		if(t[ls].minn == t[now].minn) push2(ls,t[now].lz2);
		if(t[rs].minn == t[now].minn) push2(rs,t[now].lz2);
		t[now].lz2 = 0;
	}
}
void add(int now,int l,int r,ll v)
{
	if(t[now].l == l && t[now].r == r) { push1(now,v);return; }
	pushdown(now);int mid = t[now].l + t[now].r >> 1;
	if(r <= mid) add(ls,l,r,v);
	else if(l > mid) add(rs,l,r,v);
	else add(ls,l,mid,v),add(rs,mid + 1,r,v);
	pushup(now);
}
ll query(int now,int l,int r)
{
	if(t[now].l == l && t[now].r == r) return t[now].sum;
	pushdown(now);int mid = t[now].l + t[now].r >> 1;
	if(r <= mid) return query(ls,l,r);
	if(l > mid) return query(rs,l,r);
	return query(ls,l,mid) + query(rs,mid + 1,r);
}

int main()
{
	n = read();for(int i = 1;i <= n;i++) a[i] = read();
	q = read();
	for(int i = 1;i <= q;i++) { int l = read();v[read()].push_back({l,i}); }
	build(1,1,n);
	for(int i = 1;i <= n;i++)
	{
		while(top1 && a[st1[top1]] <= a[i])
			add(1,st1[top1 - 1] + 1,st1[top1],a[i] - a[st1[top1]]),top1--;
		while(top2 && a[st2[top2]] >= a[i])
			add(1,st2[top2 - 1] + 1,st2[top2],a[st2[top2]] - a[i]),top2--;
		st1[++top1] = st2[++top2] = i;
		push1(1,-1),push2(1,1);
		for(auto j:v[i]) ans[j.id]= query(1,j.l,i);
	}for(int i = 1;i <= q;i++) fprint(ans[i]);
	return 0;
}
```

---

## 作者：lkytxdy (赞：8)

## CF997E Good Subsegments

> 给出一个 $1\sim n$ 的排列，$m$ 次询问，每次询问 $[l,r]$ 有多少子区间的数是连续的。
>
> $1\leq n,m\leq 1.2\times 10^5$。

区间连续等价于 $(\max-\min)-(r-l)=0$。

对 $r$ 扫描线，线段树每个位置 $l$ 维护当前 $r$ 对应的 $(\max-\min)-(r-l)$。$\max,\min$ 的变化用单调栈维护，比如维护 $\min$ 的变化：维护一个单调递增的栈，如果 $a_{s_{top}}>a_i$，那么左端点在 $[s_{top-1}+1,s_{top}]$ 中的 $\min$ 将从 $a_{s_{top}}$ 变成 $a_{i}$，但由于维护的是 $(\max-\min)-(r-l)$，所以线段树这个区间的位置要 $-(a_i-a_{s_{top}})$。$-(r-l)$ 可以随便维护。

我们要维护线段树区间最小值 `mn` 及个数 `cnt`，从而维护 $0$ 的个数。

上述过程是针对 $r$ 固定的，线段树上每个位置是以它为左端点，以当前枚举的 $r$ 为右端点时的 `mn,cnt`，但没有考虑右端点在 $r$ 之前的（由于是子区间），所以还需记录历史最小值个数 `sum`。每次对 $r$ 维护好之后，要累计 $r$ 对答案的贡献，贡献给之后的 $r$（当前的 $r$ 作为一个子区间的右端点）。

对于当前的 $r$，$\forall l\in[1,r]$，`cnt` 都会累加到 $[l,r]$ 的 `sum`。可以看成是，我们给 $[l,r]$ 的贡献系数 $+1$，算的时候 `cnt` $\times $ 贡献系数累加到 `sum`，所以等价于区间加，用打 `tag` 维护。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+5,M=N<<2;
int n,m,l,r,a[N],mn[M],cnt[M],tg[M],tgc[M],t1,t2,s1[N],s2[N];
ll sum[M],ans[N];
vector<pair<int,int> >q[N];
void push(int p){
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
	cnt[p]=cnt[p<<1]*(mn[p<<1]==mn[p])+cnt[p<<1|1]*(mn[p<<1|1]==mn[p]);
	sum[p]=sum[p<<1]+sum[p<<1|1];
}
void build(int p,int l,int r){
	if(l==r){mn[p]=l,cnt[p]=1;return ;}	//r=0 时，(max-min)-(r-l)=l
	int mid=(l+r)/2;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push(p); 
}
void tag(int p,int v){tg[p]+=v,mn[p]+=v;}
void tagc(int p,int v){tgc[p]+=v,sum[p]+=v*cnt[p];} 
void down(int p){
	tag(p<<1,tg[p]),tag(p<<1|1,tg[p]),tg[p]=0;
	if(mn[p<<1]==mn[p]) tagc(p<<1,tgc[p]);
	if(mn[p<<1|1]==mn[p]) tagc(p<<1|1,tgc[p]);
	tgc[p]=0;
}
void modify(int p,int l,int r,int lx,int rx,int v){
	if(l>=lx&&r<=rx) return tag(p,v);
	int mid=(l+r)/2;
	down(p);
	if(lx<=mid) modify(p<<1,l,mid,lx,rx,v);
	if(rx>mid) modify(p<<1|1,mid+1,r,lx,rx,v);
	push(p); 
}
ll query(int p,int l,int r,int lx,int rx){
	if(l>=lx&&r<=rx) return sum[p];
	int mid=(l+r)/2; ll ans=0;
	down(p);
	if(lx<=mid) ans=query(p<<1,l,mid,lx,rx);
	if(rx>mid) ans+=query(p<<1|1,mid+1,r,lx,rx);
	return ans;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&l,&r),q[r].push_back({l,i}); 
	build(1,1,n);
	for(int i=1;i<=n;i++){
		while(t1&&a[s1[t1]]>a[i]) modify(1,1,n,s1[t1-1]+1,s1[t1],a[s1[t1]]-a[i]),t1--;	//min
		while(t2&&a[s2[t2]]<a[i]) modify(1,1,n,s2[t2-1]+1,s2[t2],a[i]-a[s2[t2]]),t2--;	//max
		s1[++t1]=s2[++t2]=i;
		tag(1,-1),tagc(1,1);
		for(auto p:q[i]) ans[p.second]=query(1,1,n,p.first,i);
	}
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：tzc_wk (赞：7)

[Portal](https://codeforces.ml/contest/997/problem/E)

题意：

给出排列 $p_1,p_2,p_3,\dots,p_n$，定义一个区间 $[l,r]$ 是好的当且仅当 $p_l,p_{l+1},p_{l+2},\dots,p_r$ 包含了连续的 $r-l+1$ 个数。

$q$ 次询问，每次询问给出两个数 $l,r$，求满足 $l\leq x\leq y\leq r$ 且 $[x,y]$ 为好区间的 $(x,y)$ 的个数。

$n,q\leq 1.2\times 10^5$

首先把“好区间”的定义翻译成人话就是 $(mx-mn)-(r-l)=0$

不难想到将询问离线下来，记录到右端点上，然后用类似扫描线的方法求解。

动态地枚举右端点 $r$，建一棵线段树，线段树上下标为 $l$ 的位置记录区间 $[l,r]$ 的 $(mx-mn)-(r-l)$ 的值。

当右端点从 $r-1$ 变为 $r$ 的时候，单调栈（sb 了*1）维护区间最大值和最小值的变化。同时在线段树上下标在 $[1,r-1]$ 中的位置全部减 $1$：$-(r-1-l)$ 变为 $-(r-l)$。以 $r$ 为右端点的“好区间”的个数就是线段树上值为 $0$ 的个数。注意到 线段树上位置为 $r$ 的数总是 $0$（即区间 $[r,r]$ 永远是好区间），所以最小值的个数就是线段树上值为 $0$ 的个数。

但此题要求的是右端点在 $[l,r]$ 之间的好区间的个数，而不仅仅是右端点为 $r$ 的好区间个数。（sb 了*2）所以我们线段树上新维护两个值：$sum$ 和 $cnt$。$sum$ 表示线段树上 $[l,r]$ 这个区间历史上出现了多少次 $0$，$cnt$ 表示当前区间的 $0$ 的个数要累加进答案多少次，i.e.，如果当前区间有 $x$ 个 $0$，那么就要令 $sum+=x\times cnt$。当我们 ```pushdown``` 的时候，如果它左儿子的最小值等于当前区间的最小值，就把这个 $cnt$ 标记传给它的左儿子。右儿子也同理。每次移动右端点的时候将整颗线段树的 $cnt$ 值加 $1$。然后查询区间 $[l,r]$ 的 $sum$ 值之和就可以了。 注意到我们修改一个区间的时候是一路 ```pushdown``` 下来的，这意味着没有访问到的区间中 $0$ 的个数不会发生变化，故其满足可乘性，所以这样搞没有问题。

时间复杂度线性对数。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=1.2e5;
int n,qu,a[MAXN+5];ll ans[MAXN+5];
struct Query{int l,r;} q[MAXN+5];
vector<int> qv[MAXN+5];
struct node{
	int l,r,mn,num,add_lz;
	ll sum,cnt_lz;
} s[MAXN*4+5];
void pushup(int k){
	s[k].mn=min(s[k<<1].mn,s[k<<1|1].mn);
	s[k].num=(s[k<<1].num)*(s[k<<1].mn==s[k].mn)+(s[k<<1|1].num)*(s[k<<1|1].mn==s[k].mn);
	s[k].sum=s[k<<1].sum+s[k<<1|1].sum;
}
void pushdown(int k){
	if(s[k].add_lz){
		s[k<<1].add_lz+=s[k].add_lz;s[k<<1].mn+=s[k].add_lz;
		s[k<<1|1].add_lz+=s[k].add_lz;s[k<<1|1].mn+=s[k].add_lz;
		s[k].add_lz=0;
	}
	if(s[k].cnt_lz){
		if(s[k<<1].mn==s[k].mn) s[k<<1].cnt_lz+=s[k].cnt_lz,s[k<<1].sum+=s[k].cnt_lz*s[k<<1].num;
		if(s[k<<1|1].mn==s[k].mn) s[k<<1|1].cnt_lz+=s[k].cnt_lz,s[k<<1|1].sum+=s[k].cnt_lz*s[k<<1|1].num;
		s[k].cnt_lz=0;
	}
}
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;if(l==r){s[k].num=1;return;}
	int mid=(l+r)>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	pushup(k);
}
void modify(int k,int l,int r,int x){
	if(l>r) return;
	if(l<=s[k].l&&s[k].r<=r){s[k].mn+=x;s[k].add_lz+=x;return;}
	pushdown(k);int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	pushup(k);
}
void addcnt(int k,int l,int r,int x){
	if(l>r) return;
	if(l<=s[k].l&&s[k].r<=r){
		if(!s[k].mn) s[k].cnt_lz+=x,s[k].sum+=s[k].num;
		return;
	} pushdown(k);int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) addcnt(k<<1,l,r,x);
	else if(l>mid) addcnt(k<<1|1,l,r,x);
	else addcnt(k<<1,l,mid,x),addcnt(k<<1|1,mid+1,r,x);
	pushup(k);
}
int querynum(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return (!s[k].mn)*s[k].num;
	pushdown(k);int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) return querynum(k<<1,l,r);
	else if(l>mid) return querynum(k<<1|1,l,r);
	else return querynum(k<<1,l,mid)+querynum(k<<1|1,mid+1,r);
}
ll query(int k,int l,int r){
	if(l<=s[k].l&&s[k].r<=r) return s[k].sum;
	pushdown(k);int mid=(s[k].l+s[k].r)>>1;
	if(r<=mid) return query(k<<1,l,r);
	else if(l>mid) return query(k<<1|1,l,r);
	else return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
}
int mx[MAXN+5],mxtp=0,mn[MAXN+5],mntp=0;
int main(){
	scanf("%d",&n);for(int i=1;i<=n;i++) scanf("%d",&a[i]);scanf("%d",&qu);
	for(int i=1;i<=qu;i++) scanf("%d%d",&q[i].l,&q[i].r),qv[q[i].r].pb(i);
	build(1,1,n);
	for(int i=1;i<=n;i++){
		while(mntp&&a[mn[mntp]]>a[i]) modify(1,mn[mntp-1]+1,mn[mntp],a[mn[mntp]]-a[i]),mntp--;mn[++mntp]=i;
		while(mxtp&&a[mx[mxtp]]<a[i]) modify(1,mx[mxtp-1]+1,mx[mxtp],a[i]-a[mx[mxtp]]),mxtp--;mx[++mxtp]=i;
		modify(1,1,i-1,-1);addcnt(1,1,i,1);ffe(it,qv[i]) ans[*it]=query(1,q[*it].l,q[*it].r);
//		for(int j=1;j<=i;j++) printf("%d %d %d\n",j,i,querynum(1,j,i));
	}
	for(int i=1;i<=qu;i++) printf("%lld\n",ans[i]);
	return 0;
}
```



---

## 作者：Time_tears (赞：6)

在[博客](https://www.luogu.com.cn/blog/wlx050125/solution-cf997e)食用效果更加。

万物皆可析合树！！！~~滑稽~~

说实话这种如此析合树模板的题目当然要用析合树来做了，既然一群大佬都用了线段树，那么我就来发一篇析合树。

析合树板子就不讲了，大家可以去 [oi-wiki](https://oi-wiki.org/ds/divide-combine/) 自行翻阅。

析合树有一个非常强大的性质，所有的好区间一定是析合树上的点或者是析合树上合点的一段儿子的连续区间。

到了这道题我们就可以用容斥的思想，记 $l,r$ 在析合树上的 $lca$ 为 $x$。

答案就是 $x$ 子树的贡献 $-$ $x$ 子树中左端点在 $l$ 左边的贡献 $-$ $x$ 子树中右端点在 $r$ 右边的贡献 $+$ $x$ 子树中左端点在 $l$ 左边且右端点在 $r$ 右边的贡献的贡献。

第一部分直接在析合树上维护，很简单。

第二部分维护以每个 $l$ 为左端点的 $ans$，树状数组。

第三部分维护以每个 $r$ 为右端点的 $ans$，树状数组。

第四部分你会发现在析点时，只有可能多算 $[L_x,R_x]$ 这一对贡献，
在合点时也只会在最后一层对答案有贡献，直接计算即可。

代码就是析合树板子在加一点点就完了。


```cpp
#include<bits/stdc++.h>
#define N 240005
#define ll long long
using namespace std;
int n,m,a[N];
ll ans[N],sum[N];
struct node {
	int l,r,id;
	node(int _l=0,int _r=0,int _id=0) {
		l=_l,r=_r,id=_id;
	}
};
vector<node>q[N];
inline int read() {
	int s=0,f=0;
	char ch=getchar();
	while(ch<48||ch>57)f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58)s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
namespace SGT {
	int mn[N<<2],tag[N<<2];
	void Pushtag(int p,int x) {
		mn[p]+=x,tag[p]+=x;
	}
	void Pushdown(int p) {
		if(tag[p])Pushtag(p<<1,tag[p]),Pushtag(p<<1|1,tag[p]),tag[p]=0;
	}
	void Change(int p,int l,int r,int cl,int cr,int x) {
		if(cl<=l&&r<=cr)return Pushtag(p,x);
		int mid=(l+r)>>1;
		if(Pushdown(p),cl<=mid)Change(p<<1,l,mid,cl,cr,x);
		if(cr>mid)Change(p<<1|1,mid+1,r,cl,cr,x);
		mn[p]=min(mn[p<<1],mn[p<<1|1]);
	}
	int Getmnl(int p,int l,int r) {
		if(l==r)return l;
		int mid=(l+r)>>1;
		if(Pushdown(p),mn[p<<1]==-1)return Getmnl(p<<1,l,mid);
		return Getmnl(p<<1|1,mid+1,r);
	}
	int Askmn(int p,int l,int r,int x) {
		if(l==r)return mn[p];
		int mid=(l+r)>>1;
		if(Pushdown(p),x<=mid)return Askmn(p<<1,l,mid,x);
		return Askmn(p<<1|1,mid+1,r,x);
	}
}
using namespace SGT;
struct BIT {
	ll c[N];
	void Add(int x,int y) {
		for(; x<=n; x+=x&-x)c[x]+=y;
	}
	ll Ask(int x,ll ans=0) {
		for(; x; x-=x&-x)ans+=c[x];
		return ans;
	}
} Tl,Tr;
namespace XHTree {
	int rt,cnt,dep[N],son[N],id[N],L[N],R[N],M[N],fa[N][19];
	vector<int>g[N];
	void Addedge(int x,int y) {
		g[x].push_back(y);
	}
	void Dfs(int x) {
		for(int i=1; fa[x][i-1]; ++i)fa[x][i]=fa[fa[x][i-1]][i-1];
		for(int y:g[x])dep[y]=dep[fa[y][0]=x]+1,Dfs(y);
	}
	int Lca(int x,int y) {
		if(dep[x]<dep[y])swap(x,y);
		for(int i=16; ~i; --i)if(dep[x]-(1<<i)>=dep[y])x=fa[x][i];
		if(x==y)return x;
		for(int i=16; ~i; --i)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	int Find(int x,int k) {
		for(int i=16; ~i; --i)if(dep[x]-(1<<i)>k)x=fa[x][i];
		return x;
	}
	int smx[N],tmx,smn[N],tmn,stk[N],top,typ[N];
	void Build() {
		for(int i=1,Lef,now; i<=n; stk[++top]=now,++i) {
			while(tmx&&a[smx[tmx]]<=a[i])Change(1,1,n,smx[tmx-1]+1,smx[tmx],-a[smx[tmx]]),--tmx;
			while(tmn&&a[smn[tmn]]>=a[i])Change(1,1,n,smn[tmn-1]+1,smn[tmn],+a[smn[tmn]]),--tmn;
			Change(1,1,n,smx[tmx]+1,i,a[i]),Change(1,1,n,smn[tmn]+1,i,-a[i]),Change(1,1,n,1,i,-1);
			smx[++tmx]=smn[++tmn]=i,id[i]=++cnt,L[cnt]=R[cnt]=i,Lef=Getmnl(1,1,n),now=cnt;
			while(top&&L[stk[top]]>=Lef) {
				if(typ[stk[top]]&&Askmn(1,1,n,M[stk[top]])==-1)R[stk[top]]=i,Addedge(stk[top],now),now=stk[top--];
				else if(Askmn(1,1,n,L[stk[top]])==-1) {
					typ[++cnt]=1,L[cnt]=L[stk[top]],R[cnt]=i,M[cnt]=L[now];
					Addedge(cnt,stk[top--]),Addedge(cnt,now),now=cnt;
				} else {
					Addedge(++cnt,now);
					do Addedge(cnt,stk[top--]);
					while(top&&Askmn(1,1,n,L[stk[top]])>-1);
					L[cnt]=L[stk[top]],R[cnt]=i,Addedge(cnt,stk[top--]),now=cnt;
				}
			}
		}
		rt=stk[top];
	}
	void Solve(int x) {
		for(int i=0,sz=g[x].size(); i<sz; ++i)son[g[x][i]]=i,Solve(g[x][i]),sum[x]+=sum[g[x][i]];
		if(typ[x]) {
			for(int i=1,sz=g[x].size(); i<sz; ++i)Tr.Add(R[g[x][i]],i),sum[x]+=i;
			for(int sz=g[x].size(),i=sz-2; ~i; --i)Tl.Add(L[g[x][i]],sz-i-1);
			for(node i:q[x]) {
				int l=Find(id[i.l],dep[x]),r=Find(id[i.r],dep[x]);
				ans[i.id]=sum[x]-Tl.Ask(i.l-1)+Tl.Ask(L[x]-1)-Tr.Ask(R[x])+Tr.Ask(i.r)+(son[l]+1ll-(i.l==L[l]))*(g[x].size()-son[r]-(i.r==R[r]));
			}
		} else {
			Tl.Add(L[x],1),Tr.Add(R[x],1),++sum[x];
			for(node i:q[x])ans[i.id]=sum[x]-Tl.Ask(i.l-1)+Tl.Ask(L[x]-1)-Tr.Ask(R[x])+Tr.Ask(i.r)+(i.l!=L[x]&&i.r!=R[x]);
		}
	}
}
using namespace XHTree;
int main() {
	n=read();
	for(int i=1; i<=n; ++i)a[i]=read();
	Build(),Dfs(rt),m=read();
	for(int i=1,l,r,lca; i<=m; ++i) {
		l=read(),r=read(),lca=Lca(id[l],id[r]);
		q[lca].push_back(node(l,r,i));
	}
	Solve(rt);
	for(int i=1; i<=m; ++i)cout<<ans[i]<<"\n";
	return 0;
}
```


顺带说一句，这个算法是可以在线的，直接用主席树替换树状数组即可，代码难些很多，不过可以加强一下题目。


---

## 作者：YLWang (赞：5)


我们发现这是一个不强制在线的区间询问问题。那么常见的思路莫非就两种。

- 莫队。不大可做。

- 优化暴力。（从全局查询入手）

我们发现区间连续这个条件不大好搞。那么就把它转变成几个好求的量。那么对于一个全局查询，等价于求$\sum\limits_{l=1}^{n}\sum\limits_{r=l}^{n}[\max(l,r)-\min(l,r)-(r-l)=0]$

然后对于这种求每个区间的某性质的和的题有一个很套路的思想就是枚举右端点，通过数据结构维护所有左端点的贡献。

容易发现可以用一个数据结构维护出、 $\max(l,r)-\min(l,r)-(r-l)$ 的值。但是线段树不支持维护值域，所以我们发掘一下性质。我们只需要维护区间最小值以及最小值出现次数就可以了。

修改时需要使用单调栈维护一下。

最后是把全局查询扩展到区间询问。

我们发现全局查询就是 $nlogn$ 级别的了。怎么办？

考虑维护这个对之后的贡献就行了。相当于是把区间有$0$的位置+1。维护起来还是很方便的。


```cpp
const int MAXN = 240005;
int n, m, a[MAXN], ql[MAXN], res[MAXN];
struct Node {int x, y;};
vector < Node > q[MAXN];
struct Segment_tree {
	int mn[MAXN<<2], cnt[MAXN<<2], am[MAXN<<2], sum[MAXN << 2], as[MAXN<<2];
	#define ls (k << 1)
	#define rs (k << 1 | 1)
	#define mid ((l + r)>>1)
	void pushdown(int k)  {
		if(am[k]) {
			mn[ls] += am[k], am[ls] += am[k];
			mn[rs] += am[k], am[rs] += am[k];
			am[k] = 0;
		}
		if(as[k]) {
			if(mn[ls] == mn[k]) sum[ls] += as[k] * cnt[ls], as[ls] += as[k];
			if(mn[rs] == mn[k]) sum[rs] += as[k] * cnt[rs], as[rs] += as[k];
			as[k] = 0;
		}
		
	}
	void pushup(int k) {
		mn[k] = min(mn[ls], mn[rs]);
		if(mn[ls] == mn[rs]) cnt[k] = cnt[ls] + cnt[rs];
		else cnt[k] = mn[ls] < mn[rs] ? cnt[ls] : cnt[rs];
		sum[k] = sum[ls] + sum[rs];
	}
	void build(int k, int l, int r) {
		mn[k] = l; cnt[k] = 1;
		if(l == r) {return;}
		build(ls, l, mid); build(rs, mid+1, r);
	}
	inline void update(int k, int l, int r, int ql, int qr, int val) {
		if(l == ql && r == qr) {mn[k] += val, am[k] += val; return;}
		pushdown(k);
		if(qr <= mid) update(ls, l, mid, ql, qr, val);
		else if(mid < ql) update(rs, mid+1, r, ql, qr, val);
		else { update(ls, l, mid, ql, mid, val), update(rs, mid+1, r, mid+1, qr, val);}
		pushup(k);
	}
	inline int query(int k, int l, int r, int ql, int qr) {
		if(l == ql && r == qr) return sum[k]; pushdown(k);
		if(qr <= mid) return query(ls, l, mid, ql, qr);
		else if(mid < ql) return query(rs, mid+1, r, ql, qr);
		else return query(ls, l, mid, ql, mid) + query(rs, mid+1, r, mid+1, qr);
	}
}t;
stack < int > s1, s2;
signed main()
{
	cin >> n;
	For(i, 1, n) a[i] = read();
	cin >> m;
	For(i, 1, m) {
		int l = read(), r = read();
		q[r].pb((Node) {i, l});
	}
	t.build(1, 1, n);
	s1.push(0); s2.push(0);
	For(i, 1, n) {
		t.mn[1]--, t.am[1]--;
		while(s1.size() > 1 && a[s1.top()] < a[i]) {
			int tt = s1.top(); s1.pop();
			
			t.update(1, 1, n, s1.top() + 1, tt, a[i] - a[tt]);
		}
		s1.push(i);
		while(s2.size() > 1 && a[s2.top()] > a[i]) {
			int tt = s2.top(); s2.pop();
			t.update(1, 1, n, s2.top() + 1, tt, a[tt] - a[i]);
		}
		s2.push(i);
		
		t.sum[1] += t.cnt[1], t.as[1]++;
		
		for(auto v : q[i]) {
			int id = v.x, l = v.y;
			res[id] = t.query(1, 1, n, l, i);
		}
	}
	For(i, 1, m) {
		printf("%lld\n", res[i]);
	}
    return 0;
}

```

---

## 作者：DPair (赞：3)

其实就是求：

$$
ans(l, r)=\sum_{i=l}^r\sum_{j=i}^r[\max(i, j)-\min(i,j)=j-i]
$$

考虑扫描线

对于一个右节点，它到上一个比它大的节点之间的所有节点最大值变成它，最小值类似

注意到剩余点不变，然后右端点 +1

注意到移动右端点的时候我们需要处理贡献

考虑每一个点的贡献是它能与右边多少个节点产生贡献

考虑这东西其实并不好修改

他完全可以出这种 `2 1 4 3 6 5` 的数据恶心死你

不过其实线段树是支持计算区间某个特定数的个数的

没错这个数就是 $0$ 

考虑对于每一个左端点，维护有多少个右端点和他满足 $\max - \min - (j-i) = 0$

考虑对于一个点 $\max \min$ 修改次数都是 $O(1)$ 的

考虑 $j$  每一次移动就是区间减

因此其实右端点贡献个数可以维护。。。就是值为 $0$ 的点数。。。

考虑它还有区间修改什么的

因此还要维护一个区间最小值和最小值个数

然后还有一个问题就是要记录历史答案

考虑每一次修改前打个 tag 就做完了

注意一下这个 tag 只能打给符合条件的点

复杂度 $O(n\log n)$

---

## 作者：lhm_ (赞：3)

先将问题进行转化，发现满足$(max-min)-(r-l)=0$的区间即为好区间。

对于本题这样的统计子区间的问题，先将询问离线，按右端点排序一个一个解决，固定右端点，然后通过数据结构来处理出区间信息，询问直接查询区间合法的贡献即可，扫一遍就能解决所有询问。

继续看这个式子$(max-min)-(r-l)=0$，发现如果去维护这个式子的值，对于固定的右端点，可以统计出其之前的左端点与该右端点的区间最小值及其个数，最小值个数即为在这个区间内可以对这个固定的右端点有贡献的左端点。

但这只能记录右端点固定的答案，无法处理子区间的问题，可以记录下历史最小值个数和，再进行询问即为这段区间的所有子区间的答案了。

具体实现时，维护$max-min$的变化可以通过单调栈来实现，$r-l$的变化直接对整个区间减一即可，历史最小值个数和需要通过打标记来看该区间是否能产生贡献，细节就看代码吧。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 500010
#define ls (cur<<1)
#define rs (cur<<1|1)
#define mid ((l+r)>>1)
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,q,t1,t2,root=1;
int a[maxn],s1[maxn],s2[maxn];
ll ans[maxn],mi[maxn],cnt[maxn],sum[maxn],add[maxn],tag[maxn];
struct Query
{
    int l,id;
};
vector<Query> ve[maxn];
void pushup(int cur)
{
    ll lm=mi[ls],rm=mi[rs],lc=cnt[ls],rc=cnt[rs];
    if(lm==rm) mi[cur]=lm,cnt[cur]=lc+rc;
    if(lm<rm) mi[cur]=lm,cnt[cur]=lc;
    if(lm>rm) mi[cur]=rm,cnt[cur]=rc;
    sum[cur]=sum[ls]+sum[rs];
}
void pushadd(int cur,ll v)
{
    mi[cur]+=v,add[cur]+=v;
}
void pushtag(int cur,ll v)
{
    sum[cur]+=cnt[cur]*v,tag[cur]+=v;
}
void pushdown(int cur)
{
    if(add[cur])
        pushadd(ls,add[cur]),pushadd(rs,add[cur]),add[cur]=0;
    if(tag[cur])
    {
        if(mi[cur]==mi[ls]) pushtag(ls,tag[cur]);
        if(mi[cur]==mi[rs]) pushtag(rs,tag[cur]);
        tag[cur]=0;
    }
}
void build(int l,int r,int cur)
{
    if(l==r)
    {
        mi[cur]=l,cnt[cur]=1;
        return;
    }
    build(l,mid,ls),build(mid+1,r,rs);
    pushup(cur);
}
void modify(int L,int R,int l,int r,ll v,int cur)
{
    if(L<=l&&R>=r)
    {
        pushadd(cur,v);
        return;
    }
    pushdown(cur);
    if(L<=mid) modify(L,R,l,mid,v,ls);
    if(R>mid) modify(L,R,mid+1,r,v,rs);
    pushup(cur);
}
ll query(int L,int R,int l,int r,int cur)
{
    if(L<=l&&R>=r) return sum[cur];
    pushdown(cur);
    ll ans=0;
    if(L<=mid) ans+=query(L,R,l,mid,ls);
    if(R>mid) ans+=query(L,R,mid+1,r,rs);
    return ans;
}
int main()
{
    read(n),build(1,n,root);
    for(int i=1;i<=n;++i) read(a[i]);
    read(q);
    for(int i=1;i<=q;++i)
    {
        int l,r;
        read(l),read(r);
        ve[r].push_back((Query){l,i});
    }
    for(int i=1;i<=n;++i)
    {
        while(t1&&a[s1[t1]]<=a[i])
        {
            modify(s1[t1-1]+1,s1[t1],1,n,a[i]-a[s1[t1]],root);
            t1--;
        }
        while(t2&&a[s2[t2]]>=a[i])
        {
            modify(s2[t2-1]+1,s2[t2],1,n,a[s2[t2]]-a[i],root);
            t2--;
        }
        s1[++t1]=s2[++t2]=i,pushadd(root,-1),pushtag(root,1);
        int size=ve[i].size();
        for(int j=0;j<size;++j)
            ans[ve[i][j].id]=query(ve[i][j].l,i,1,n,root);
    }
    for(int i=1;i<=q;++i) printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：murder_drones (赞：2)

本文节选自笔者的另一篇文章：[关于一类子区间计和问题](https://www.luogu.com.cn/article/jow97i6z)

**这个做法不需要历史和。**

先以子区间最大子段和之和为例讲解具体算法流程。**内容有关联，请务必阅读完例题再继续**。

### 单组询问

$solve(l,r)$ 先求解跨过 $mid$ 的区间权值计和，再递归 $solve(l,mid)$ 和 $solve(mid+1,r)$ 即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/jvck0c27.png)

先写出区间最大子段和的式子表达：
$$w(L,R)=\max(\max(ans_L,ans_R),maxsuf_L+maxpre_R)$$
其中 $ans_L$ 表示在 $[L,mid]$ 中的最大子段和，$ans_R$ 类似，$maxsuf_L$ 表示以 $mid$ 为右端点的最大后缀，$maxpre_R$ 类似。

容易发现上述4种变量都有单调性。考虑对 $ans_L$ 和 $ans_R$ 进行归并，假设当前有 $ans_L \le ans_R$，那么我们就计算以 $L$ 为左端点，$[mid+1,R-1]$ 为右端点的所有区间（例如 $[L,mid+1]$，$[L,mid+2]\dots$）的贡献。

由于已经归并，所以可知 $ans_L\ge ans_{R-1}$，那么 $w(L,R')$ 一定不会取 $ans_{R'}$ 那一项（$R'\in [mid+1,R-1]$）。式子化为：
$$\max(ans_L,maxsuf_L+maxpre_{R'})$$
考虑何时右边取答案，有：
$$ans_L\le maxsuf_L+maxpre_{R'}$$
$$ans_L-maxsuf_L\le maxpre_{R'}$$
于是设第一个满足条件的位置为 $p$，右端点在 $[mid+1,p-1]$ 的答案全是 $ans_L$，在 $[p,R-1]$ 的答案全是 $maxsuf_L+maxpre_{R'}$。求和简易。

事实上，$p$ 随着 $L$ 的移动亦有单调性。此处略证。（由这个性质可以得到 $O(n\log n)$ 的解法）

归并在右边可以对称地写出式子维护，不再赘述。

如果 $p$ 的求取使用 lower_bound 进行，时间复杂度是 $O(n\log^2 n)$ 的。

区间贡献不会算重的简证：一个区间 $[L,R]$ 只会被更晚归并弹出的那个端点计算一次。

### 多组询问

我们依旧进行归并，但实时地使用线段树（普通的，不需要历史和）维护——截止到目前归并的这个左端点，以某个右端点为下标的贡献总和。

也即给线段树的 $[mid+1,p-1]$ 区间加 $ans_L$，给 $[p,R-1]$ 加上 $maxsuf_L+maxpre_{R'}$。右侧对左侧贡献同理。所以要维护两棵这样的线段树，左右各一棵。

所以线段树要支持区间 $a_i$ 加 $v$，区间 $a_i$ 加上 $b_i$（$maxpre_{R'}$），以及区间求 $a_i$ 的和。

如何回答询问？我们将询问也分治，如果询问在一边直接递归不计算；如果包含了整个区间就不递归等底下分治回来了再回答。

跨过了中点且不包含整个区间的将贡献分四部分：左递归，右递归，左归并，右归并。其中左右递归直接扔下去就可以，左归并指的是当 $L$ 归并到 $query_l$ 后，去线段树上查询 $[mid+1,query_r]$ 的区间和。$query_l$ 指的就是询问的左端点。右同理。（此处是 $L$ 与 $query_l$ 的双指针）

正确性简证：假设一个区间 $[L,R]$ 是由 $L$ 晚归并，那么它的贡献就会算进左归并线段树的下标 $R$ 处。这本质上确实是满足了子区间二维偏序。

询问带来的复杂度可以用类似线段树的复杂度分析得到。总共是 $O((n+q)\log^2 n)$

#### 连续子区间计数 （Good Subsegments）
也就是本题。

这题单组询问有一种较为奇妙的转化：考虑将 $(i,i+1)$ 这个数对选不选抽象成一个点。如果原序列上的 $i$ 和 $i+1$ 之间的最值为 $mx$ 和 $mn$，那么你选了 $(i,i+1)$ 就要选 $(mn,mn+1)\dots(mx-1,mx)$。于是转化后问题为：每个点对应一条线段，你要计数有多少区间 $[L,R]$ 满足封闭，也即在该区间里的点所对应的所有线段都被这个区间包含。最后还要给答案加 $n$，因为 $i$ 本身也合法。读者有兴趣可以尝试这个推一推这个做法，但很可惜它难以支持多组询问。

这题套路的做法也要用到结论：区间合法当且仅当 $max-min=r-l$。我们考虑对前缀最大值归并，然后再 lower_bound 前缀最小值。

设当前归并到 $[L,R]$，$sufmax_L\le premax_R$，第一个满足 $sufmin_L\ge premin_p$ 的位置是 $p$。

对于右端点在 $[mid+1,p-1]$ 的区间，$max$，$min$，$l$ 都已知，可以推算出 $r$ 进行单点加。

对于右端点在 $[p,R-1]$ 的区间，$max$，$l$ 已知，我们要给那些在 $[p,R-1]$ 且 $max+l=min+r$ 的位置进行加一。再次利用结论，我们可以知道这样的位置只可能是 $min+r$ 的最大值所在位（不取等也只能取大于）。所以需要线段树维护 $a_i$ 最大值，$a_i$ 最大值个数，区间 $a_i$ 最大值位置的 $b_i$ 加一（如果为给定的 $max+l$），区间求 $b_i$ 的和。

反向同理。

提交记录：https://mirror.codeforces.com/problemset/submission/997/301081018


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int INF=1e9+10;

int prec[2][maxn],sufc[2][maxn];
struct SGT{
	int op;
	struct node{
		int l,r;
		long long addv,addw;
		long long sumv;
		int maxv,maxcnt;
	}tr[maxn<<2];
	void pushup(int p){
		tr[p].sumv=tr[p<<1].sumv+tr[p<<1|1].sumv;
		tr[p].maxv=max(tr[p<<1].maxv,tr[p<<1|1].maxv);
		tr[p].maxcnt=0;
		if(tr[p<<1].maxv==tr[p].maxv) tr[p].maxcnt+=tr[p<<1].maxcnt;
		if(tr[p<<1|1].maxv==tr[p].maxv) tr[p].maxcnt+=tr[p<<1|1].maxcnt;
	}
	void addf(int p,long long v,long long w){
		if(tr[p].maxv!=v) return ;
		tr[p].addv=v;tr[p].addw+=w;
		tr[p].sumv+=w*tr[p].maxcnt;
	}
	void pushdown(int p){
		if(tr[p].addw){
			addf(p<<1,tr[p].addv,tr[p].addw);
			addf(p<<1|1,tr[p].addv,tr[p].addw);
			tr[p].addw=0;
		}
	}
	void build(int p,int l,int r){
		tr[p].l=l,tr[p].r=r;tr[p].addw=0;
		if(l==r){
			tr[p].sumv=0;tr[p].maxcnt=1;
			if(op==0) tr[p].maxv=prec[0][tr[p].l];
			else tr[p].maxv=sufc[1][tr[p].l];
			return ;
		}int mid=(tr[p].l+tr[p].r)>>1;
		build(p<<1,l,mid);build(p<<1|1,mid+1,r);pushup(p);
	}
	void add(int p,int l,int r,long long v,long long w){
		if(r<l) return ;
		if(l<=tr[p].l&&tr[p].r<=r) return addf(p,v,w);
		int mid=(tr[p].l+tr[p].r)>>1;pushdown(p);
		if(l<=mid) add(p<<1,l,r,v,w);
		if(mid<r) add(p<<1|1,l,r,v,w);pushup(p);
	}
	void add(int p,int pos,long long v){
		if(tr[p].l==tr[p].r) return void(tr[p].sumv+=v);
		int mid=(tr[p].l+tr[p].r)>>1;pushdown(p);
		if(pos<=mid) add(p<<1,pos,v);
		else add(p<<1|1,pos,v);pushup(p);
	}
	long long query(int p,int l,int r){
		if(r<l) return 0ll;
		if(l<=tr[p].l&&tr[p].r<=r) return tr[p].sumv;
		int mid=(tr[p].l+tr[p].r)>>1;pushdown(p);
		if(r<=mid) return query(p<<1,l,r);
		if(mid<l) return query(p<<1|1,l,r);
		return query(p<<1,l,r)+query(p<<1|1,l,r);
	}
}tr[2];

struct qry{
	int l,r,id;
};long long ans[maxn];
int n,m;
int a[maxn];
int premax[maxn],sufmax[maxn];
int premin[maxn],sufmin[maxn];
long long cdq(int l,int r,vector<qry> q){
	if(l==r){
		for(qry p:q) ans[p.id]++;
		return 1;
	}int mid=(l+r)>>1;
	for(qry &p:q) p.l=max(p.l,l),p.r=min(p.r,r);//!!!
	
//	printf("cdq in:%d %d\n",l,r);
//	for(qry p:q) printf("q:%d %d %d\n",p.l,p.r,p.id);
	
	premax[mid]=0;premin[mid]=INF;
	for(int i=mid+1;i<=r;i++){
		premax[i]=max(premax[i-1],a[i]);
		premin[i]=min(premin[i-1],a[i]);
		prec[0][i]=premin[i]+i;
		prec[1][i]=premax[i]-i;
	}
	sufmax[mid+1]=0;sufmin[mid+1]=INF;
	for(int i=mid;i>=l;i--){
		sufmax[i]=max(sufmax[i+1],a[i]);
		sufmin[i]=min(sufmin[i+1],a[i]);
		sufc[0][i]=sufmax[i]+i;
		sufc[1][i]=sufmin[i]-i;
	}
	
	tr[0].build(1,mid+1,r);
	tr[1].build(1,l,mid);
	vector<qry> lq,rq;
	for(qry p:q){
		if(p.l<=l&&r<=p.r) continue;
		if(p.l<=mid&&mid<p.r) lq.push_back(p),rq.push_back(p);
	}
	sort(lq.begin(),lq.end(),[](qry x,qry y){return x.l>y.l;});
	sort(rq.begin(),rq.end(),[](qry x,qry y){return x.r<y.r;});
	
	int p1=mid,p2=mid+1;
	int lp=0,rp=0;
	while(p1>=l&&p2<=r){
		if(sufmax[p1]<=premax[p2]){
			int p=lower_bound(premin+mid+1,premin+(p2-1)+1,sufmin[p1],greater<int>())-premin;
			int np=sufc[0][p1]-sufmin[p1];
			if(mid+1<=np&&np<p) tr[0].add(1,np,1);
			tr[0].add(1,p,p2-1,sufc[0][p1],1);
			while(lp<(int)lq.size()&&lq[lp].l>=p1){
				ans[lq[lp].id]+=tr[0].query(1,mid+1,lq[lp].r);
				lp++;
			}p1--;
		}else{
			int p=upper_bound(sufmin+(p1+1),sufmin+mid+1,premin[p2])-sufmin-1;
			int np=premin[p2]-prec[1][p2];
			if(p<np&&np<=mid) tr[1].add(1,np,1);
			tr[1].add(1,p1+1,p,prec[1][p2],1);
			while(rp<(int)rq.size()&&rq[rp].r<=p2){
				ans[rq[rp].id]+=tr[1].query(1,rq[rp].l,mid);
				rp++;
			}p2++;
		}
	}
	while(p1>=l){
		int p=lower_bound(premin+mid+1,premin+p2,sufmin[p1],greater<int>())-premin;
		int np=sufc[0][p1]-sufmin[p1];
		if(mid+1<=np&&np<p) tr[0].add(1,np,1);
		tr[0].add(1,p,p2-1,sufc[0][p1],1);
		while(lp<(int)lq.size()&&lq[lp].l>=p1){
			ans[lq[lp].id]+=tr[0].query(1,mid+1,lq[lp].r);
			lp++;
		}p1--;
	}
	while(p2<=r){
		int p=upper_bound(sufmin+(p1+1),sufmin+mid+1,premin[p2])-sufmin-1;
		int np=premin[p2]-prec[1][p2];
		if(p<np&&np<=mid) tr[1].add(1,np,1);
		tr[1].add(1,p1+1,p,prec[1][p2],1);
		while(rp<(int)rq.size()&&rq[rp].r<=p2){
			ans[rq[rp].id]+=tr[1].query(1,rq[rp].l,mid);
			rp++;
		}p2++;
	}
	long long nowv=tr[0].query(1,mid+1,r)+tr[1].query(1,l,mid);
	
	lq.clear(),rq.clear();
	for(qry p:q){
		int L=p.l,R=p.r;
		if(L<=l&&r<=R) continue;
		if(L<=mid) lq.push_back(p);
		if(mid<R) rq.push_back(p);
	}long long res=cdq(l,mid,lq)+cdq(mid+1,r,rq)+nowv;
	for(qry p:q) if(p.l<=l&&r<=p.r) ans[p.id]+=res;
//	printf("cdq out:%d %d\n",l,r);
//	printf("res:%lld\n",res);
	return res;
}
vector<qry> qr;
int main(){
	scanf("%d",&n);tr[0].op=0;tr[1].op=1;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1,l,r;i<=m;i++) scanf("%d%d",&l,&r),qr.push_back({l,r,i});
	cdq(1,n,qr);
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：1saunoya (赞：1)

挺套路的一个题吧…尤其是下放标记的方式。

其实是 [526F](https://www.luogu.com.cn/problem/CF526F) 的加强版。

变成区间询问。

我们想一下怎么区间询问呢。

扫描线，毋庸置疑。

枚举右端点。

找 $[i,r]$ 的贡献。

但是$[i,r-1]$ 也是符合条件的。

所以我们需要用一个技巧性的东西来下放这个标记，线段树显然是可以下放的。

然后只需要注意一点细节。

先push掉懒标记，然后再把前面的贡献加上去。就做完了。


```cpp
/*
 _      _  _ _ _ _ _   _      _
\_\   /_/ \_\_\_\_\_\ \_\   /_/
 \_\ /_/      \_\      \_\ /_/
  \_\_/       \_\       \_\_/
   \_\         \_\       \_\
   \_\     \_\ \_\       \_\
   \_\      \_\\_\       \_\
*/
#include <bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define sz(v) (int)v.size()
#define int long long
using namespace std;
template<class T>
void read(T&x) {
	static int c,neg;
	x=neg=0;c=getchar();
	while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}if(neg)x=-x;
}
template<class T>
void print(T x,char c='\n'){
	static int st[233],top;
	if(x<0)putchar('-'),x=-x;
	do{st[++top]=x%10;x/=10;}while(x);
	while(top)putchar(st[top--]+48);putchar(c);
}
template<class T>
void cmax(T&x,const T&y){
	x=(x>y)?x:y;
}
template<class T>
void cmin(T&x,const T&y){
	x=(x<y)?x:y;
}
int n,q;
const int N=262144;
int a[N];
vector<int>v[N],vv[N];
int s[N<<2];
int mn[N<<2];
int t[N<<2];
int tt[N<<2];
int ans[N<<2];
void pushv(int p,int v){
	t[p]+=v;
	mn[p]+=v;
}
void pushans(int p,int v){
	tt[p]+=v;
	ans[p]+=s[p]*v;
}
void down(int p){
	if(t[p]){
		pushv(p<<1,t[p]);
		pushv(p<<1|1,t[p]);
		t[p]=0;
	}
	if(tt[p]){
//		pushans(p<<1,tt[p]);
//		pushans(p<<1|1,tt[p]);
		if(mn[p<<1]==mn[p]){
			pushans(p<<1,tt[p]);
		}
		if(mn[p<<1|1]==mn[p]){
			pushans(p<<1|1,tt[p]);
		}
		tt[p]=0;
	}
}
void up(int p){
	cmin(mn[p]=mn[p<<1],mn[p<<1|1]);
	s[p]=0;
	if(mn[p]==mn[p<<1]){
		s[p]+=s[p<<1];
	}
	if(mn[p]==mn[p<<1|1]){
		s[p]+=s[p<<1|1];
	}
	ans[p]=ans[p<<1]+ans[p<<1|1];
}
void build(int l,int r,int p){
	mn[p]=l;
	s[p]=1;
	if(l==r){
		return;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
}
void update(int ql,int qr,int l,int r,int p,int v){
	if(ql<=l&&r<=qr){
		pushv(p,v);
		return;
	}
	down(p);
	int mid=l+r>>1;
	if(ql<=mid){
		update(ql,qr,l,mid,p<<1,v);
	}
	if(qr>mid){
		update(ql,qr,mid+1,r,p<<1|1,v);
	}
	up(p);
}
int query(int ql,int qr,int l,int r,int p){
	if(ql<=l&&r<=qr){
		return ans[p];
	}
	int mid=l+r>>1;
	down(p);
	int Ans=0;
	if(ql<=mid){
		Ans+=query(ql,qr,l,mid,p<<1);
	}
	if(qr>mid){
		Ans+=query(ql,qr,mid+1,r,p<<1|1);
	}
	return Ans;
}
int st1[N],t1=0;
int st2[N],t2=0;
int answer[N];
signed main(){
	read(n);
	rep(i,1,n){
		read(a[i]);
	}
	read(q);
	rep(i,1,q){
		int l,r;
		read(l);
		read(r);
		v[r].push_back(l);
		vv[r].push_back(i);
	}
	build(1,n,1);
	rep(i,1,n){
		pushv(1,-1);
		while(t1&&a[st1[t1]]<a[i]){
			update(st1[t1-1]+1,st1[t1],1,n,1,a[i]-a[st1[t1]]);
			--t1;
		}
		st1[++t1]=i;
		while(t2&&a[st2[t2]]>a[i]){
			update(st2[t2-1]+1,st2[t2],1,n,1,a[st2[t2]]-a[i]);
			--t2;
		}
		st2[++t2]=i;
		pushans(1,1);
		int sz=sz(v[i]);
		rep(j,0,sz-1){
			int l=v[i][j];
			int id=vv[i][j];
			answer[id]=query(l,i,1,n,1);
		}
	}
	rep(i,1,q){
		print(answer[i]);
	}
	return 0;
}
```

---

## 作者：WeLikeStudying (赞：0)

- [例题](https://www.luogu.com.cn/problem/CF526F)。
- $n\times n$ 的棋盘，每行每列各有一个棋子，问连续 $k$ 行 $k$ 列有 $k$ 个棋子的子棋盘数量。
- $n\le 3\times 10^5$。
- 显然有那个特殊性质，所以不能直接拿棋盘来考虑，考虑序列，容易发现要求区间最大值与区间最小值之差加一恰好是区间长度的区间。
- 朴素的做法是 $O(n^2)$ 的，考虑扫描线的做法。
- 我们会发现区间最大值与区间最小值之差加一怎么也不可能小于区间长度，所以我们要统计的就是区间最大值减区间最小值减区间长度的最小值 $\max-\min-\text{len}$（其实只要统计最小值的个数即可不需要判断是不是 $-1$，因为它的最小值一定有 $-1$）。
- 我们考虑维护这个最小值，可是怎么维护呢？
![](https://cdn.luogu.com.cn/upload/image_hosting/93dpz8z0.png)
- 所以可以搞两个单调栈，一棵线段树，复杂度 $O(n\log n)$。
- [代码实现](https://www.luogu.com.cn/paste/ips9exki)。
- 如果有重复元素记录的就是不重复元素的情况，区间不重复元素的话，记录每个点的前驱分别讨论就行了，复杂度同本做法。
- [类题](https://www.luogu.com.cn/problem/CF997E)。
- 动态更新每个区间的贡献该怎么弄？朴素的办法只能应对以该区间右端点为右端点的区间，需要在线段树上动态维护以 $i$ 为左端点的好区间个数。
- 所以我们要维护一个作为累加和的东西，每次枚举端点都要做一个全局修改，也就是对最小值（$-1$）的位置（的答案或者也可以理解成贡献）加一。
- 而这个直接下传，下传的时候比较一下，就可以做了。
- [代码实现](https://www.luogu.com.cn/paste/ocj7akqe)。

---

## 作者：_HL_ (赞：0)

## 扫描线子区间问题模板题

通过矩形加实现

考虑一个二维平面 两个坐标轴分别表示区间 $l$ 和 $r$ ，横轴 $l$ 纵轴 $r$

若连续必有 $maxn-minn - r + l = 0$

二维平面上的点 $p ( l , r )$ 表示 $maxn - minn - r + l$ 即用来维护答案

考虑批量处理此平面上点

考虑将问题转换为矩形加

$r$ 和 $l$ 可以平凡地矩形加掉 考虑 $maxn$ 和 $minn$ 

需要通过最值分治找到每个原序列的元素 $maxn$ 和 $minn$ 管辖区域 以 $ maxn $ 为例 由于纵轴为 $ r $ ，所以若此区间内 $ maxn $ 值为此元素 则此区间 $ r $ 比需比下一个比此元素大的元素的标号靠前 且区间 $ r $ 必须大于等于此元素的标号

所以纵坐标若 $ maxn $ 为 $ a_i $ ，此矩形上界必为下一个比 $ a_i $ 大的元素的标号 下界为 $ i$ 

区间 $ l $ 确定横轴 左右界同理 可以像 $ r $ 一样做出矩形

考虑具体实现 即找前一个和后一个比 $a_i$ 大的元素的标号 单调栈可平凡地维护

由于此平面表示区间 所以有一个显然的性质是下半边三角不可能出 $0$ 所以维护 2 side 矩形即可 需要反向扫扫描线
 
但我太蒟了 忘了反向扫了 正向扫询问 $ [ l , r ] $ 区间分别在 $ l - 1 $ 和 $ r $ 记录以前的  0 的个数做差即为答案也彳亍

考虑如何维护 $ 0 $ 的个数 显然平面上任意一点维护的答案值必大于 $0$ 所以维护 $min$ 值和个数即可 线段树可以平凡的维护

但由于维护的是所有之前的 $0$ 的个数 需要打一个历史标记 需要仔细讨论一下 不过可以平凡的维护 注意细节

由于我太蒟了 所以就真的是按矩形加去做的 时间和空间稳稳倒一 不过这是一个子区间问题比较常见的套路 所以海星吧就

```cpp
#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const int N=120005;
int a[N];
int cnt;
struct node_q
{
    int pos,id;
    int l,r;
    ll ans;
    bool friend operator < (const node_q a,const node_q b)
    {
        return a.pos<b.pos;
    }
}q[N<<1];
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c<='9'&&c>='0')
    {
        x=(x<<1)+(x<<3)+c-'0';
        c=getchar();
    }
    return x;
}

struct node
{
    int r_l,r_r,l,opt; 
    bool friend operator < (const node a,const node b)
    {
        return a.l==b.l?a.opt>b.opt:a.l<b.l;
    }
}line[N<<3];
struct node_stc
{
    int key;
    int id;
}stc[N];
struct node_lim
{
    int l;
    int r;
}lim_max[N],lim_min[N];

struct seg
{
    int key_min;
    ll num_min;
    ll tag;
    ll his;
    ll his_tag;
    int from;
}t[N<<6];
#define ls p<<1
#define rs p<<1|1
inline void update(int p)
{
    t[p].his=t[ls].his+t[rs].his;
    if(t[ls].key_min<t[rs].key_min)
    {
        t[p].key_min=t[ls].key_min;
        t[p].num_min=t[ls].num_min;
        t[p].from=1;
        return;
    }
    if(t[rs].key_min<t[ls].key_min)
    {
        t[p].key_min=t[rs].key_min;
        t[p].num_min=t[rs].num_min;
        t[p].from=2;
        return;
    }
    t[p].key_min=t[ls].key_min;
    t[p].num_min=t[ls].num_min+t[rs].num_min;   
    t[p].from=3;    
    //if(t[p].key_min==0)
    
}

void build(int l,int r,int p)
{
    if(l==r)
    {
        t[p].num_min=1;
        return;
    }
    int mid=l+r>>1;
    build(l,mid,ls);
    build(mid+1,r,rs);
}

inline void pushdown(int p)
{
    if(t[p].tag!=0)
    {
        t[ls].key_min+=t[p].tag;
        t[ls].tag+=t[p].tag;
        t[rs].key_min+=t[p].tag;
        t[rs].tag+=t[p].tag;
        t[p].tag=0;
    }
    if(t[p].his_tag!=0)
    {
        if(t[p].from==3)
        {
            t[ls].his+=t[p].his_tag*t[ls].num_min;
            t[ls].his_tag+=t[p].his_tag;
            t[rs].his+=t[p].his_tag*t[rs].num_min;
            t[rs].his_tag+=t[p].his_tag;
            t[p].his_tag=0;    
            return;
        }
        if(t[p].from==1)
        {
            t[ls].his+=t[p].his_tag*t[ls].num_min;
            t[ls].his_tag+=t[p].his_tag;
            t[p].his_tag=0;    
            return;        
        }
        if(t[p].from==2)
        {
            t[rs].his+=t[p].his_tag*t[rs].num_min;
            t[rs].his_tag+=t[p].his_tag;
            t[p].his_tag=0;    
            return;        
        }
    }
}

void modify(int l,int r,int ql,int qr,ll dx,int p)
{    
    if(ql<=l&&r<=qr)
    {
        t[p].key_min+=dx;
        t[p].tag+=dx;
        if(t[p].key_min==0)
        {
            t[p].his+=t[p].num_min;
            t[p].his_tag++;
        }
        return;
    }
    pushdown(p);
    int mid=l+r>>1;
    if(ql<=mid)modify(l,mid,ql,qr,dx,ls);
    if(qr>mid)modify(mid+1,r,ql,qr,dx,rs);
    update(p);
}

ll query(int l,int r,int ql,int qr,int p)
{
    if(ql<=l&&r<=qr)
    {
        return t[p].his;
    }
    pushdown(p);
    ll res=0;
    int mid=l+r>>1;
    if(ql<=mid)res+=query(l,mid,ql,qr,ls);
    if(qr>mid)res+=query(mid+1,r,ql,qr,rs);
    return res;
}

bool cmp(node_q a,node_q b)
{
    return a.id==b.id?a.ans<b.ans:a.id<b.id;
}

signed main()
{
    int n;
    n=read();
    for(int i=1;i<=n;i++)
    a[i]=read();
    int qn=read();
    for(int i=1;i<=qn;i++)
    {
        q[i*2-1].id=q[i*2].id=i;
        q[i*2-1].l=q[i*2].l=q[i*2-1].pos=read();
        q[i*2-1].pos--;
        q[i*2-1].r=q[i*2].r=q[i*2].pos=read();
    }
    sort(q+1,q+qn*2+1);
    for(int i=1;i<=n;i++)
    {
        line[++cnt]={i,i,1,-i};
        line[++cnt]={1,n,i,i};
        line[++cnt]={1,n,i+1,-i};
    }
    build(1,n,1);
    int top=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]<stc[top].key)
        {
            lim_max[i].l=stc[top].id;
            stc[++top]={a[i],i};
        }
        else
        {
            while(stc[top].key<a[i]&&top)
            {
                lim_max[stc[top].id].r=i;
                top--;
            }
            lim_max[i].l=stc[top].id;
            stc[++top]={a[i],i};
        }
    }
    while(top)
    {
        lim_max[stc[top].id].r=n+1;
        top--;
    }
    for(int i=1;i<=n;i++)
    {
        if(a[i]>stc[top].key)
        {
            lim_min[i].l=stc[top].id; 
            stc[++top]={a[i],i}; 
        }
        else
        {
            while(stc[top].key>a[i]&&top)
            {
                lim_min[stc[top].id].r=i;
                top--;
            }
            lim_min[i].l=stc[top].id;
            stc[++top]={a[i],i};
        }
    }
    while(top)
    {
        lim_min[stc[top].id].r=n+1;
        top--;
    }
    for(int i=1;i<=n;i++)
    {
        line[++cnt]={i,lim_max[i].r-1,lim_max[i].l+1,a[i]};
        line[++cnt]={i,lim_max[i].r-1,i+1,-a[i]};
        line[++cnt]={i,lim_min[i].r-1,lim_min[i].l+1,-a[i]};
        line[++cnt]={i,lim_min[i].r-1,i+1,a[i]};
    }
    sort(line+1,line+cnt+1);
    int cntl=1;
    int cntq=1;
    while(!q[cntq].pos)cntq++;
    for(int i=1;i<=n;i++)
    {
        while(line[cntl].l==i)
        {
            modify(1,n,line[cntl].r_l,line[cntl].r_r,line[cntl].opt,1);
            cntl++;
        }
        while(q[cntq].pos==i&&cntq<=qn*2)
        {
            q[cntq].ans=query(1,n,q[cntq].l,q[cntq].r,1);
            cntq++;
        }
    }
    sort(q+1,q+qn*2+1,cmp);
    for(int i=1;i<=qn;i++)
    {
        ll temp=q[i*2].ans-q[i*2-1].ans;
        printf("%lld\n",temp);
    }
    return 0;
}
```




---

