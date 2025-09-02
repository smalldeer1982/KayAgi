# Set To Max (Hard Version)

## 题目描述

This is the hard version of the problem. The only differences between the two versions of this problem are the constraints on $ n $ and the time limit. You can make hacks only if all versions of the problem are solved.

You are given two arrays $ a $ and $ b $ of length $ n $ .

You can perform the following operation some (possibly zero) times:

1. choose $ l $ and $ r $ such that $ 1 \leq l \leq r \leq n $ .
2. let $ x=\max(a_l,a_{l+1},\ldots,a_r) $ .
3. for all $ l \leq i \leq r $ , set $ a_i := x $ .

Determine if you can make array $ a $ equal to array $ b $ .

## 说明/提示

In the first test case, we can achieve array $ b $ by applying a single operation: $ (l,r)=(2,3) $ .

In the second test case, it can be shown we cannot achieve array $ b $ in any amount of operations.

In the third test case, we can achieve array $ b $ by applying two operations: $ (l,r)=(2,5) $ . followed by $ (l,r)=(1,3) $ .

In the fourth and fifth test cases, it can be shown we cannot achieve array $ b $ in any amount of operations.

## 样例 #1

### 输入

```
5
5
1 2 3 2 4
1 3 3 2 4
5
3 4 2 2 4
3 4 3 4 4
5
3 2 1 1 1
3 3 3 2 2
2
1 1
1 2
3
1 1 2
2 1 2```

### 输出

```
YES
NO
YES
NO
NO```

# 题解

## 作者：huangrenheluogu (赞：21)

并不会针对 Easy Version 的题解，就写 Hard Version 吧。感觉同一份交两个地方不是很好。

如果 $a_i=b_i$，那么很好，跳过。

发现 $\{a_n\}$ 进行一次操作，所有的数字是不减的。

所以当 $a_i\ne b_i$ 的时候，我们可以考虑从左边/右边的更大的数拿过来覆盖。

当然，可以特判 $a_i>b_i$ 的情况，但不需要。

发现数的值域是 $1\sim n$，其实不管怎样都可以离散成 $1\sim n$，但是算是一个提示。

如果我们从左边更新，记录离 $i$ 最近的值为 $b_i$ 在 $a$ 数组的位置，如果没有显然不可行。记这个位置为 $pos$。然后我们检查 $pos\le j\le i$ 是否有比 $b_j<b_i$，如果有，显然不可行，因为会覆盖到。而且需要检查 $a_j$ 的最大值，防止被别的数覆盖。

上面查询 $\max,\min$ 的操作用线段树维护即可。

左边做完了，右边同理。

如果有一个数不可行，返回 `NO`，否则 `YES`。

复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ls p << 1
#define rs p << 1 | 1
using namespace std;
const int N = 5e5 + 5;
int T, n, a[N], b[N], minn[N << 2], maxn[N << 2], l, r, mid, las[N];
bool ans[N];
inline void push_up(int p){
	maxn[p] = max(maxn[ls], maxn[rs]);
	minn[p] = min(minn[ls], minn[rs]);
}
inline void build(int p, int l, int r){
	if(l == r){
		minn[p] = b[l];
		maxn[p] = a[l];
		return ;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	push_up(p);
}
inline int querymax(int p, int l, int r, int x, int y){
	if(x <= l && r <= y) return maxn[p];
	int mid = l + r >> 1, res = 0;
	if(mid >= x) res = max(res, querymax(ls, l, mid, x, y));
	if(mid < y) res = max(res, querymax(rs, mid + 1, r, x, y));
	return res;
}
inline int querymin(int p, int l, int r, int x, int y){
	if(x <= l && r <= y) return minn[p];
	int mid = l + r >> 1, res = n + 1;
	if(mid >= x) res = min(res, querymin(ls, l, mid, x, y));
	if(mid < y) res = min(res, querymin(rs, mid + 1, r, x, y));
	return res;
}
inline void solve(){
	for(int i = 1; i <= n; i++) las[i] = ans[i] = 0;
	for(int i = 1; i <= n; i++){
		las[a[i]] = i;
		if(!las[b[i]]) continue ;
		if(querymin(1, 1, n, las[b[i]], i) < b[i] || querymax(1, 1, n, las[b[i]], i) > b[i]) continue ;
		ans[i] = 1;
	}
	for(int i = 1; i <= n; i++) las[i] = 0;
	for(int i = n; i >= 1; i--){
		las[a[i]] = i;
		if(!las[b[i]]) continue ;
		if(querymin(1, 1, n, i, las[b[i]]) < b[i] || querymax(1, 1, n, i, las[b[i]]) > b[i]) continue ;
		ans[i] = 1;
	}
	for(int i = 1; i <= n; i++){
		if(ans[i]) continue ;
		printf("NO\n");
		return ;
	}
	printf("YES\n");
	return ;
}
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
		}
		for(int i = 1; i <= n; i++){
			scanf("%d", &b[i]);
		}
		build(1, 1, n);
		solve();
	}
	return 0;
}
/*
1
3
1 1 2
2 1 2
*/
```

[评测链接](https://codeforces.com/contest/1904/submission/236980435)

会了 Hard Version 的做法，我们可以返回，把线段树换成暴力判断就是 Easy Version 了。

但是我感觉这种想法不是很直接，就不~~水~~写题解了。

---

## 作者：wangshi (赞：4)

我们找到每个 $b_i$ 左右两个最近的相等的 $a_j$。

首先 $a_i>b_i$ 显然时无解的。

并且需要满足以下两个条件：

1. $\forall i<k<j, a_k \le b_i$ 显然如果不满足的话，修改时就会修改为这个更大的值，从而影响答案。

2. $\forall i<k<j, b_k \ge b_i$ 如果 $b_k<b_i$ 在修改时，这个位置的值也会被修改，导致 $a_k>b_k$，进而无解。

显然这两个都可以用 ST 表来求。

```cpp
#include<bits/stdc++.h> 
#define ll long long
using namespace std;
const int N=2e5+10;
typedef pair<int,int> PII;
int Max[N][19],Min[N][19],lg[N];
int queryMax(int l,int r)
{
	int s=lg[r-l+1];
	return max(Max[l][s],Max[r-(1<<s)+1][s]);
}
int queryMin(int l,int r)
{
	int s=lg[r-l+1];
	return min(Min[l][s],Min[r-(1<<s)+1][s]);
}
void solve()
{
	int n; cin>>n;
	vector<int> a(n+1),b(n+1),nxt(n+1),pre(n+1);
	for(int i=1;i<=n;i++) 
		cin>>a[i],Max[i][0]=a[i];
	for(int i=1;i<=n;i++) 
		cin>>b[i],Min[i][0]=b[i];
	for(int j=1;j<=lg[n];j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);
			Min[i][j]=min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
		}
	map<int,vector<int>> q;
	for(int i=1;i<=n;i++)
	{
		q[b[i]].push_back(i);
		if(q[a[i]].size())
		{
			for(auto k:q[a[i]])
				nxt[k]=i;
			q[a[i]].clear();
		}
	}
	q.clear();
	for(int i=n;i>=1;i--)
	{
		q[b[i]].push_back(i);
		if(q[a[i]].size())
		{
			for(auto k:q[a[i]])
				pre[k]=i;
			q[a[i]].clear();
		}
	}
	for(int i=1;i<=n;i++)
	{
		bool vis=0;
		if(a[i]==b[i]) continue;
		if(a[i]>b[i])
		{
			cout<<"NO\n";
			return;
		}
		if(pre[i])
		{
			int w=pre[i]+1;
			if(queryMax(w,i)<=b[i]&&queryMin(w,i)>=b[i]) vis=1;
		}
		if(nxt[i])
		{
			int w=nxt[i]-1;
			if(queryMax(i,w)<=b[i]&&queryMin(i,w)>=b[i]) vis=1;
		}
		if(!vis)
		{
			cout<<"NO\n";
			return;
		}
	} 
	cout<<"YES\n";
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	for(int i=2;i<=2e5;i++) lg[i]=lg[i>>1]+1;
	int t; cin>>t;
	while(t--) solve();
	return 0;
}



```

---

## 作者：sordio (赞：4)

**由于这道题是[Set To Max (Easy Version)](https://www.luogu.com.cn/problem/CF1904D1)的加强版，我是对于简单版的优化，所以可以先看一下[我对于简单版的题解](https://www.luogu.com.cn/blog/woshishabiaaaaa/solution-cf1904d1)。**

对于简单版的做法，其实可以总结归纳为以下几步：

1. 逐个枚举 $a$ 中的数字，判断是否需要变化。
2. 如需变化，则分别向左向右搜索距离 $a_i$ 最近，且 $a_j=b_i$ 的两个 $a_j$。
3. 判断 $a_j$ 是否满足：在 $[i,j]$ 中，不存在 $k$ 满足 $a_j>b_i$ 且 $b_j<b_i$。
4. 如果有任意一个 $a_i$ 不合法，那么输出“NO”；如果全部合法，输出“YES”。

可以发现，步骤二可以用一个数组 $mp$ 来存下每一个 $a_i$ 在数组 $a$ 中的位置，然后在需要时进行二分查找，就可以用 $O(\log n)$ 的复杂度完成步骤二（原来是 $O(n)$）。

而步骤三实则就是一个分别取 $a$ 和 $b$ 区间最大最小值再与 $b_i$ 进行比较的问题，可以用一个线段树存下数组 $a$ 和 $b$，再去取区间最值，时间复杂度 $O(\log n)$。

再算上步骤一的 $O(n)$ 枚举，总时间复杂度 $O(n \log n)$，符合要求。

最后献上我的代码（有点小乱，但码风优良）：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,ans,ma,mb;
int a[N],b[N],tra[N*4],trb[N*4];
struct node{
	vector<int> v;
}mp[N];

void mktra(int x,int y,int s){
	if(x==y){
		tra[s]=a[x];
		return;
	}
	int mid=(x+y)>>1;
	mktra(x,mid,s*2);
	mktra(mid+1,y,s*2+1);
	tra[s]=max(tra[s*2],tra[s*2+1]);
	return;
}

void mktrb(int x,int y,int s){
	if(x==y){
		trb[s]=b[x];
		return;
	}
	int mid=(x+y)>>1;
	mktrb(x,mid,s*2);
	mktrb(mid+1,y,s*2+1);
	trb[s]=min(trb[s*2],trb[s*2+1]);
	return;
}

int mxa(int l,int r,int s,int L,int R){
	if(L<=l&&r<=R) return tra[s];
	int mid=(l+r)>>1,mx=0;
	if(mid>=L) mx=mxa(l,mid,s*2,L,R);
	if(mid<R) mx=max(mx,mxa(mid+1,r,s*2+1,L,R));
	return mx;
}

int mnb(int l,int r,int s,int L,int R){
	if(L<=l&&r<=R) return trb[s];
	int mid=(l+r)>>1,mn=1e9;
	if(mid>=L) mn=mnb(l,mid,s*2,L,R);
	if(mid<R) mn=min(mn,mnb(mid+1,r,s*2+1,L,R));
	return mn;
}//线段树取最值

bool solve(){
	for(int i=1;i<=n;i++){
		if(a[i]==b[i]) continue;
		if(a[i]>b[i]) return 0; 
		if(mp[b[i]].v.empty()) return 0;
		int ne=lower_bound(mp[b[i]].v.begin(),mp[b[i]].v.end(),i)-mp[b[i]].v.begin(),pr;
		if(ne==mp[b[i]].v.size()) pr=mp[b[i]].v.size()-1;
		else pr=ne-1; //二分查找前一个和后一个
		if(ne!=0){ //判断前一个是否合法
			pr=mp[b[i]].v[pr];
			ma=mxa(1,n,1,pr,i),mb=mnb(1,n,1,pr,i);
			if(ma<=b[i]&&mb>=b[i]) continue;
		}
		if(ne!=mp[b[i]].v.size()){ //后一个
			ne=mp[b[i]].v[ne];
			ma=mxa(1,n,1,i,ne),mb=mnb(1,n,1,i,ne);
			if(ma<=b[i]&&mb>=b[i]) continue; 
		}
		return 0;
	}
	return 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			mp[a[i]].v.push_back(i);
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
		}
		mktra(1,n,1),mktrb(1,n,1); //建树
		if(solve()) puts("YES");
		else puts("NO");
		for(int i=1;i<=n;i++){ //清空
			mp[a[i]].v.clear();
		}
	}
	return 0;
}
```
完结撒花！

---

## 作者：Diaоsi (赞：3)

[Set To Max (Hard Version)](https://www.luogu.com.cn/problem/CF1904D2)

不想写线段树。

首先特判掉 $b_i<a_i$ 的情况，由于在操作的过程中 $a_i$ 只会增大，所以出现 $b_i<a_i$ 是一定无解的。

然后对每个 $a_i$ 找到最大的能成为最值进行操作的一个区间，记为 $[L,R]$，这个区间要满足两个条件：$a_{L\sim R}\leq a_i$ 和 $b_{L\sim R}\geq a_i$。

在序列 $a$ 上往左找到第一个满足 $a_l>a_i$ 的 $l$，再往右找到第一个满足 $a_r>a_i$ 的 $r$，显然 $[l+1,r-1]$ 满足条件一。
同理，在序列 $b$ 上找到往左第一个满足 $b_{l^\prime}<a_i$ 的 $l^\prime$ 和往右第一个满足  $b_{r^\prime}<a_i$ 的 $r^\prime$。$[l^\prime+1,r^\prime-1]$ 满足条件二。

将这两个区间取交就能得到 $[L,R]$，将 $a$ 按照升序排序，按顺序对每个 $a_i$ 对应的 $[L,R]$ 进行区间推平为 $a_i$ 的操作，判断最终序列和 $b$ 序列是否相同即可。

至于这个做法的正确性，可以感性理解一下。由于 $a_i$ 不会覆盖 $b$ 上比它小的数，而过多覆盖的位置会在后续的处理中被更大的数给覆盖，所以这样操作是更优的。



------------


找极大区间可以用值域树状数组实现。以找 $a_l$ 为例，按照 $i=1\sim n$ 的顺序扫描 $a_i$，在 $v$ 上记录最后一个出现的值为 $v$ 的数对应的下标。求 $l$ 就变成了在区间 $[1,a_i)$ 上查询最大值。

区间推平操作可以用 ODT 实现（因为好写），注意在这题中 ODT 的时间复杂度是依赖于均摊的（而不是随机）。

时间复杂度 $\mathcal{O}(n\log n)$。

Code:
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=200010,M=2000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int T,n,a[N],b[N];
struct rec{
	int s,l,r;
	bool operator <(const rec &x)const{
		return s<x.s;
	}
}p[N];
namespace B1{

int c[N];
void add(int x,int y){
	for(;x<=n;x+=x&-x)c[x]=max(c[x],y);
}
int ask(int x){
	int res=0;
	for(;x;x-=x&-x)res=max(res,c[x]);
	return res;
}
void upd(int x,int y){
	for(;x<=n;x+=x&-x)c[x]=min(c[x],y);
}
int qry(int x){
	int res=n+1;
	for(;x;x-=x&-x)res=min(res,c[x]);
	return res;
}

}
namespace B2{

int c[N];
void add(int x,int y){
	for(;x;x-=x&-x)c[x]=max(c[x],y);
}
int ask(int x){
	int res=0;
	for(;x<=n;x+=x&-x)res=max(res,c[x]);
	return res;
}
void upd(int x,int y){
	for(;x;x-=x&-x)c[x]=min(c[x],y);
}
int qry(int x){
	int res=n+1;
	for(;x<=n;x+=x&-x)res=min(res,c[x]);
	return res;
}

}
struct node{
	int l,r;
	mutable int v;
	node(const int &il,const int &ir,const int &iv):l(il),r(ir),v(iv){}
	bool operator <(const node &x)const{return l<x.l;}
};
struct ODT{
	set<node> odt;
	auto split(int x){
		if(x>n)return odt.end();
		auto it=--odt.upper_bound(node{x,0,0});
		if(it->l==x)return it;
		int l=it->l,r=it->r,v=it->v;
		odt.erase(it);
		odt.insert(node(l,x-1,v));
		return odt.insert(node(x,r,v)).first;
	}
	void assign(int l,int r,int v){
		auto ir=split(r+1),il=split(l);
		odt.erase(il,ir);
		odt.insert(node(l,r,v));
	}
	void query(int l,int r){
		auto ir=split(r+1),il=split(l);
		for(;il!=ir;il++)
			for(int i=il->l;i<=il->r;i++)
				a[i]=il->v;
	}
}tree;
void solve(){
	scanf("%d",&n);
	tree.odt.clear();
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i].s);
		tree.odt.insert(node(i,i,a[i]));
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)
		if(b[i]<p[i].s){puts("NO");return;}
	for(int i=1;i<=n;i++)
		B1::c[i]=B2::c[i]=0;
	for(int i=1;i<=n;i++){
		p[i].l=max(B1::ask(p[i].s-1),B2::ask(p[i].s+1))+1;
		B1::add(b[i],i);B2::add(p[i].s,i);
	}
	for(int i=1;i<=n;i++)
		B1::c[i]=B2::c[i]=n+1;
	for(int i=n;i>=1;i--){
		p[i].r=min(B1::qry(p[i].s-1),B2::qry(p[i].s+1))-1;
		B1::upd(b[i],i);B2::upd(p[i].s,i);
	}
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)
		tree.assign(p[i].l,p[i].r,p[i].s);
	tree.query(1,n);
	for(int i=1;i<=n;i++)
		if(a[i]!=b[i]){puts("NO");return;}
	puts("YES");
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```


---

## 作者：Natori (赞：3)

简单版：[CF1904D1 Set To Max (Easy Version)](https://www.luogu.com.cn/problem/CF1904D1)

困难版：[CF1904D2 Set To Max (Hard Version)](https://www.luogu.com.cn/problem/CF1904D2)

读完题之后，我们可以对这个修改操作有一种形象的把握：每一个数相当于一种“势力”，每种“势力”可以向两边较“弱”的势力进行“扩张”，每次只能“扩张”连续的一段。

考虑将全局合法分解到每个位置合法，即判断每个 $a_i$ 是否能变成 $b_i$。显然，若一开始就有 $a_i=b_i$，那么这个 $a_i$ 是不必被扩张的。因此不妨设 $a_i\not=b_i$。

$a_i$ 要想被扩张变成 $b_i$，则必须要从另一个 $a_j=b_i$ 的 $j$ 处扩展而来，并且此时应该满足 $\forall k\in [i,j),a_k<a_j$。不取等的原因是没必要，如果取等，要么是 $a_i=a_j$，要么是 $\exists k\in(i,j),a_k=a_j$。前一种情况直接让 $i$ 自增 $1$ 就能满足要求，同时还能让要考虑的区间变小；后一种情况直接令 $j\leftarrow k$ 即可。综上，对于每一个 $i$，我们只需要考虑左边或右边最近的 $j$ 使得 $a_j=b_i$。

现在考虑如何判断每个位置是否合法。每次扩张都不会使一个数变小，所以必然不能存在 $a_i>b_i$ 的情况。同时，能进行扩张的区间一定是单调（非严格）的。由于 $a$ 会被我们改变，所以把这条单调性用到 $a$ 上所产生的价值不大；但是我们最终要让 $a$ 变成 $b$，而 $b$ 是不变的，所以可以用在 $b$ 上。

注意到每次操作一定可以被分成若干次向左、向右扩张，因此可以先钦定向右扩张，然后将 $a,b$ 都翻转一次，重复之前的过程（这里借鉴了一下官方题解）。用单调栈处理出 $pa_i$ 表示 $i$ 右侧第一个大于 $a_i$ 的数的位置，$pb_i$ 表示 $i$ 左侧第一个小于 $b_i$ 的位置，再动态维护到现在 $a$ 中每个数最后一次出现的位置，即可快速判断每个位置是否合法。总复杂度是 $\mathcal{O}(n)$ 的。

```
#include<bits/stdc++.h>
using namespace std;
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
typedef pair<int,int> pii;
const int N=2e5+8;
int n,a[N],b[N];
int pa[N],pb[N],posa[N];
pii stc[N];
int top;
bool ans[N];
void solve(){
	for(int i=1;i<=n;i++)
		pa[i]=pb[i]=posa[i]=0;
	top=0;
	stc[++top]={n+1,n+1};
	for(int i=n;i>=1;i--){
		while(stc[top].first<=a[i])
			top--;
		pa[i]=stc[top].second;
		stc[++top]={a[i],i};
	}
	top=0;
	stc[++top]={0,0};
	for(int i=1;i<=n;i++){
		while(b[i]<=stc[top].first)
			top--;
		pb[i]=stc[top].second;
		stc[++top]={b[i],i};
	}
	for(int i=1;i<=n;i++){
		posa[a[i]]=i;
		if(a[i]<=b[i]&&posa[b[i]]!=0)
			ans[i]|=(i<pa[posa[b[i]]]&&pb[i]<posa[b[i]]);
	}
}
void mian(){
	for(int i=1;i<=n;i++)
		a[i]=b[i]=ans[i]=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	solve();
	reverse(a+1,a+n+1);
	reverse(b+1,b+n+1);
	reverse(ans+1,ans+n+1);
	solve();
	bool anss=1;
	for(int i=1;i<=n;i++)
		anss&=ans[i];
	cout<<(anss==1?"YES":"NO")<<'\n';
}
bool Mend;
int main(){
//	File_Work();
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cerr<<fixed<<setprecision(3)<<(&Mbegin-&Mend)/1048576.0<<" MB\n\n\n";
	int testnum=1;
	cin>>testnum;
	while(testnum--)
		mian();
	cerr<<"\n\n\n"<<fixed<<setprecision(0)<<1e3*clock()/CLOCKS_PER_SEC<<" ms";
	return 0;
}
```

---

## 作者：MiniLong (赞：3)

先分别将 $a$ 中每个值所出现的位置记录下来。

然后考虑每个 $a_i$ 是否可以变成 $b_i$。

如果 $a_i \neq b_i$，那么就要在 $a$ 中的其他位置去找到一个 $b_i$，然后把这段区间全部变为 $b_i$。根据贪心的思想，这个位置肯定离 $i$ 越近越好。考虑 $i<j<k$，$a_i \neq b_i, a_j=a_k=b_i$，如果选择 $k$ 而不选择 $j$，那么额外的 $[j+1,k]$ 这段区间就都要变为 $b_i$ 了，如果存在 $p \in [j+1,k]$ 且 $b_p <b_i$，那么这个 $p$ 就无法满足了，所以选择 $j$ 肯定比选择 $k$ 出现上述情况要少。

所以直接考虑最靠近 $i$ 的左右两点 $j<i<k$。

然后判断这两点中是否有一点可行。如果 $a$ 在 $[j,i]$ 中的最大值大于 $b_i$，那就不可行，如果 $b$ 在 $[j,i]$ 中的最小值小于 $b_i$，也不可行。因为如果最小值在 $p,j<p<i$，且 $b_p < b_i$，那么将 $a_p$ 更新为 $b_i$ 后，就不可能再变小了。

右边的 $k$ 也同理。

复杂度 $O(n\log{n})$。

---

## 作者：MaxBlazeResFire (赞：3)

注意到题目的条件可以强化成仅操作长度为 $2$ 的区间，不难证明此时有解性与之前相同。先判掉所有 $a_i=b_i$。

这样其实就一目了然了：对于每一个 $i$，记 $j>i$ 为最小的 $a_j=b_i$ 的位置，若 $\max\{a[i,j]\}=a_j$ 且 $\min\{b[i,j]\}\leq b_i$ 则 $a_i$ 可以通过右侧的 $a_j$ 变为目标值。

同样可以判断对于 $i$ 是否存在一个左侧的数使其变为目标值。如果存在一个 $i$ 两侧都无法使其变为目标值则无解。

用 `set` 和 $\rm ST$ 表实现，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005
int n,a[MAXN],b[MAXN],st[MAXN][18],st2[MAXN][18],lg2[MAXN];
set<int> pos[MAXN];

inline int Query( int l , int r ){
	int len = lg2[r - l + 1];
	return min( st[l][len] , st[r - ( 1 << len ) + 1][len] );
}

inline int Query2( int l , int r ){
	int len = lg2[r - l + 1];
	return max( st2[l][len] , st2[r - ( 1 << len ) + 1][len] );
}

inline void solve(){
	scanf("%d",&n);
	for( int i = 1 ; i <= n ; i ++ ) pos[i].clear();
	for( int i = 1 ; i <= n ; i ++ ) scanf("%d",&a[i]),pos[a[i]].insert( i ),st2[i][0] = a[i];
	for( int i = 1 ; i <= n ; i ++ ) scanf("%d",&b[i]),st[i][0] = b[i];
	for( int j = 1 ; j <= 17 ; j ++ )
		for( int i = 1 ; i + ( 1 << j ) - 1 <= n ; i ++ )
			st[i][j] = min( st[i][j - 1] , st[i + ( 1 << ( j - 1 ) )][j - 1] ),
			st2[i][j] = max( st2[i][j - 1] , st2[i + ( 1 << ( j - 1 ) )][j - 1] );
	for( int i = 1 ; i <= n ; i ++ ){
		if( a[i] == b[i] ) continue;
		int exl = 0,exr = 0; set<int>::iterator it;
		it = pos[b[i]].upper_bound( i );
		if( it != pos[b[i]].end() && Query2( i , *it ) == a[*it] && Query( i , *it ) >= b[i] ) exr = 1;
		it = pos[b[i]].lower_bound( i );
		if( it != pos[b[i]].begin() ){
			it --;
			if( Query2( *it , i ) == a[*it] && Query( *it , i ) >= b[i] ) exl = 1;
		}
		if( !exl && !exr ){ puts("NO"); return; }
	}
	puts("YES");
}

signed main(){
	for( int i = 2 ; i <= MAXN - 5 ; i ++ ) lg2[i] = lg2[i >> 1] + 1;
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：ARIS2_0 (赞：2)

### 思路

考虑一个 $a_i$ 何时可以变为 $b_i$。

首先 $a_i>b_i$ 时显然无解。

对于一个 $i$，记 $j_1$ 为左边离 $i$ 最近的，满足 $a_{j_1}=b_i$ 的数；$j_2$ 为右边离 $i$ 最近的，满足 $a_{j_2}=b_i$ 的数。

显然，要将 $a_i$ 变为 $b_i$，对于区间 $[j_1,i]$ 和 $[i,j_2]$ 中的一个区间操作，一定是最优的。

区间 $[j_1,i]$ 能进行操作，当且仅当 $\forall k\in[j_1,i],a_k\le a_{j_1},b_k\ge a_{j_1}$，即 $a$ 在 $[j_1,i]$ 中的最大值是 $a_{j_1}$ 且 $b$ 在 $[j_1,i]$ 中的最小值是 $a_{j_1}$，因为只有这样才能保证修改到而且不会影响其他位置的操作。显然可以用 ST 表维护。$j_2$ 同理。

那么对于每个 $i$，判断区间 $[j_1,i]$ 和 $[i,j_2]$ 中有没有至少一个可以进行操作（若 $j_1$ 不存在则区间 $[j_1,i]$ 无法操作，$j_2$ 同理），若可以，这个数就是可操作的。若 $a$ 中所有数都是可操作的，则 $a$ 可以变为 $b$。于是就做完了。

单组数据时间复杂度 $O(n\log n)$。

### Code

```cpp
#include<algorithm>
#include<bitset>
#include<deque>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector> 
#include<chrono>
#include<random>
#include<tuple>
#include<unordered_map>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"\n"
const int inf=1e16,maxn=2e5+10;
int f1[maxn][19],f2[maxn][19];
void st(int *a,int f[][19],int n,bool maxs){
	for(int i=1;i<=n;i++)f[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			if(maxs)f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
			else f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}
}
int check(int f[][19],bool maxs,int l,int r){
	int p=log2(r-l+1);
	if(maxs)return max(f[l][p],f[r-(1<<p)+1][p]);
	return min(f[l][p],f[r-(1<<p)+1][p]);
}
int a[maxn],b[maxn];
vector<int>v[maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++)v[i].clear();
		for(int i=1;i<=n;i++)cin>>a[i],v[a[i]].push_back(i);
		for(int i=1;i<=n;i++)cin>>b[i];
		st(a,f1,n,1);
		st(b,f2,n,0);
		bool g=1;
		for(int i=1;i<=n;i++){
			int p2=lower_bound(v[b[i]].begin(),v[b[i]].end(),i)-v[b[i]].begin(),p1=p2-1;
			bool pos=0;
			if(p1>=0){
				p1=v[b[i]][p1];
				if(check(f1,1,p1,i)==a[p1] and check(f2,0,p1,i)==a[p1])pos=1;
			}
			if(p2<v[b[i]].size()){
				p2=v[b[i]][p2];
				if(check(f1,1,i,p2)==a[p2] and check(f2,0,i,p2)==a[p2])pos=1;
			}
			if(!pos){g=0;break;}
		}
		cout<<(g?"YES":"NO")<<"\n";
	}
	return 0;
}
/*
clang++ -std=c++14 -Wall -Wextra -Wshadow -Wconversion -Wl,-stack_size -Wl,512000000
*/
```

---

## 作者：Genius_Star (赞：0)

### 思路：

注意到每次都是赋值为较大值，故 $a_i$ 的变化一定是单调不降的；故若 $a_i > b_i$ 肯定无解。

若 $a_i \ne b_i$，要使得 $a_i = b_i$，首先要找到一个 $j$ 使得 $a_j = b_i$，可以选择 $[i, j]$ 这个区间。

那么若 $[i, j]$ 合法当且仅当：

- 在 $(i, j)$ 中不存在一个 $k$ 使得 $a_k > a_j$，因为此时 $[i, j]$ 中的最大值就不一定是 $a_j$ 了。

- 同时对于任意的 $k \in (i, j)$ 都需要满足 $b_k > b_i$，因为将 $a_k \gets b_i$ 后若 $a_k > b_k$ 是无解的。

总结一下无解：

- 若不存在 $j$，无解。

- 若 $\max\limits_{k = i}^j a_k > a_j$，无解。

- 若 $\min\limits_{k = i}^j b_k < a_j$，无解。

直接找左边和右边的第一个满足 $a_j = b_i$ 的 $k$ 判断即可；可以使用 ST 表维护最大最小值。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10, M = 19; 
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int T, n;
int a[N], b[N], lst[N];
int F[2][M][N];
bool f[N];
inline int askmax(int l, int r){
	int k = log2(r - l + 1);
	return max(F[0][k][l], F[0][k][r - (1 << k) + 1]);
}
inline int askmin(int l, int r){
	int k = log2(r - l + 1);
	return min(F[1][k][l], F[1][k][r - (1 << k) + 1]);
}
inline void solve(){
	n = read();
	for(int i = 1; i <= n; ++i)
	  F[0][0][i] = a[i] = read();
	for(int i = 1; i <= n; ++i)
	  F[1][0][i] = b[i] = read();
	for(int j = 1; j < M; ++j){
		for(int i = 1; i <= n && i + (1 << j) - 1 <= n; ++i){
			F[0][j][i] = max(F[0][j - 1][i], F[0][j - 1][i + (1 << (j - 1))]);
			F[1][j][i] = min(F[1][j - 1][i], F[1][j - 1][i + (1 << (j - 1))]);
		}
	}
	for(int i = 1; i <= n; ++i){
		if(a[i] == b[i])
		  f[i] = 1;
		else
		  f[i] = 0;
	}
	for(int i = 1; i <= n; ++i)
	  lst[i] = 0;
	for(int i = 1; i <= n; ++i){
		if(f[i] || !lst[b[i]]){
			lst[a[i]] = i;
			continue;
		}
		int j = lst[b[i]];
		if(askmax(j, i) > a[j]){
			lst[a[i]] = i;
			continue;
		}
		if(askmin(j, i) < a[j]){
			lst[a[i]] = i;
			continue;
		}
		f[i] = 1;
		lst[a[i]] = i;
	}
	for(int i = 1; i <= n; ++i)
	  lst[i] = 0;
	for(int i = n; i >= 1; --i){
		if(f[i] || !lst[b[i]]){
			lst[a[i]] = i;
			continue;
		}
		int j = lst[b[i]];
		if(askmax(i, j) > a[j]){
			lst[a[i]] = i;
			continue;
		}
		if(askmin(i, j) < a[j]){
			lst[a[i]] = i;
			continue;
		}
		f[i] = 1;
		lst[a[i]] = i;
	}
	for(int i = 1; i <= n; ++i){
		if(!f[i]){
			puts("NO");
			return ;
		}
	}
	puts("YES");
}
bool End;
int main(){
	T = read();
	while(T--)
	  solve();
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：dlhham (赞：0)

好像我的做法跟大家挺不一样的，写一下吧。

首先特判一下 $a_i>b_i$ 的情况，后续的过程就是一个搬运值的过程，也就是每次把 $a_i$ 搬运到位置 $j$ 去，只要对所有的位置 $j$，都有一个位置 $i$ 满足 $a_i=b_j$ 且能把 $a_i$ 搬运到 $j$，那么就一定是合法的。正确性的证明很简单，我们考虑每次搬运那个目标最小的值，这样目标更大的值一定还是能搬运成功的。

这时候稍微考虑一下就能想到一个结论：对于 $a_i=b_i$ 的位置，我们没法越过他们左右搬值了，所以每次考虑一个区间 $[L,R]$ 能否成功搬运。

对于当前的 $[L,R]$，我们记录两个 `set` $S_1,S_2$，分别表示左侧，右侧能够有哪些值被搬运到 $L$ 或者 $R$。

那么，对于当前的 $[L,R]$ 来说，如果 $S_1$ ($S_2$) 中恰好有 $b_L$ ($b_R$)，那就说明我们是可以搬运满足 $L$ ($R$) 的，我们先记录一下它可以被满足，然后考虑哪些值可以被它继续搬运出去。

首先：原先 `set` 中，比 $a_i$ 小的，一定搬运不出去了，原因是我没可能让 $a_i$ 在过程中变小。

其次：原先 `set` 中，比 $b_i$ 大的，一定搬运不出去了，原因是我不可能在过程中让 $a_i$ 变得比 $b_i$ 还大。

那我们直接把这些数字从 `set` 中删掉，然后把 $a_i$ 加到 `set` 中。

模拟这个过程，直到区间为空，或者是无法消除任何一个端点即可。复杂度 $O(nlogn)$。

```c++
#include<bits/stdc++.h>
#define ll long long
#define maxn 200005
#define mod 998244353
using namespace std;
int n;
int a[maxn],b[maxn];
set<int> L,R;
int check(int l,int r)
{
	L.clear(); R.clear();
	L.insert(a[l]); R.insert(a[r]); l++; r--;
	while (l<=r)
	{
		if (L.find(b[l])!=L.end()) //左侧找到了 
		{
			while (!L.empty() && *--L.end()>b[l]) L.erase(--L.end()); 
			while (!L.empty() && *L.begin()<a[l]) L.erase(L.begin()); 
			L.insert(a[l++]);
		} 
		else
		if (R.find(b[r])!=R.end())
		{
			while (!R.empty() && *--R.end()>b[r]) R.erase(--R.end());
			while (!R.empty() && *R.begin()<a[r]) R.erase(R.begin());
			R.insert(a[r--]);
		}
		else return 0;
	} 
	return 1;
}
void work(int T,int cas)
{
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++) cin>>b[i];
	a[n+1]=b[n+1]=0;
	for (int i=1;i<=n;i++) if (a[i]>b[i]) {cout<<"NO"<<endl; return;}
	int pre=0;
	for (int i=1;i<=n;i++)
	if (a[i]==b[i])
	{
		if (!check(pre,i)) {cout<<"NO"<<endl; return;}
		pre=i;
	}
	if (!check(pre,n+1)) {cout<<"NO"<<endl; return;}
	cout<<"YES"<<endl;
}

int main()
{
	int T,cas=0;
	cin>>T;
	for (int i=1;i<=T;i++) work(T,++cas);
} 
```

---

## 作者：taojinchen (赞：0)

# 思路
很明显，基于一种贪心的思想，肯定是通过等于 $b_i$ 的 $a_j$ 将 $a_i$ 变成 $b_i$ 最优，其中 $j \le i$ 并且 $i-j$ 最小，或者 $i \lt j$ 且 $j-i$ 最小。

通过 $a_j$ 将 $a_i$ 变成 $b_i$ 的时候要注意。$a_j$ 一定是 $a$ 数组中这一段区间内最大的数，不然就会变成别的数。$b_i$ 一定是 $b$ 数组中这一段区间内最小的数，否则这个区间内的某些数就无法变成对应的数。
# code
```cpp
// 特意拿去格式化了一下,本来的码风比较差
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int kM = 2e5 + 5;
ll n, j, a[kM], b[kM], p[kM], to[kM], st[kM][20], st_2[kM][20], q, i, t;
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> q;
  while (q--) {
    cin >> n;
    t = 0;
    for (i = 1; i <= n; i++) {
      cin >> a[i];
      p[i] = to[i] = 0;
    }
    for (i = 1; i <= n; i++) {
      cin >> b[i];
      p[a[i]] = i;
      to[i] = p[b[i]];
    }
    for (i = 1; i <= n; i++) {
      if (!p[b[i]] || b[i] < a[i]) {  // 1.   b_i在a数组必须出现过   2.   a_i不可能变小
        t = 1;
        break;
      }
    }
    if (t) {
      cout << "NO\n";
      continue;
    }
    for (i = 1; i <= n; i++) p[i] = 0;
    for (i = 1; i <= n; i++) {
      p[a[i]] = i;
      st[i][0] = a[i];    //$a_j$ 一定是 $a$ 数组中这一段区间内最大的数，不然就会变成别的数
      st_2[i][0] = b[i];  //$b_i$ 一定是 $b$ 数组中这一段区间内最小的数，否则这个区间内的某些数就无法变成对应的数
      to[i] = p[b[i]];
    }
    for (j = 1; j <= 18; j++) {
      for (i = 1; i <= n - (1 << (j - 1)) + 1; i++) {
        st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);  //$a_j$ 一定是 $a$ 数组中这一段区间内最大的数，不然就会变成别的数
      }
      for (i = 1; i <= n - (1 << (j - 1)) + 1; i++) {
        st_2[i][j] = min(st_2[i][j - 1], st_2[i + (1 << (j - 1))][j - 1]);  //$b_i$ 一定是 $b$ 数组中这一段区间内最小的数，否则这个区间内的某些数就无法变成对应的数
      }
    }
    a[n + 1] = 1e9;
    for (i = 1; i <= n; i++) p[i] = 0;
    for (i = n; i && !t; i--) {
      p[a[i]] = i;
      if (a[i] == b[i]) continue;
      if (to[i] == 0) to[i] = n + 1;
      ll ma = 0, x = to[i], mi = 1e18;
      for (j = 18; ~j; j--) {
        if (x + (1 << j) <= i + 1) {
          ma = max(ma, st[x][j]);    //$a_j$ 一定是 $a$ 数组中这一段区间内最大的数
          mi = min(mi, st_2[x][j]);  //$b_i$ 一定是 $b$ 数组中这一段区间内最小的数
          x += (1 << j);
        }
      }
      if (ma != a[to[i]] || mi < b[i]) {
        if (p[b[i]] == 0) {
          t = 1;
          break;
        }
        ll ma = 0, x = i, mi = 1e18;
        for (j = 18; ~j; j--) {
          if (x + (1 << j) <= p[b[i]] + 1) {
            ma = max(ma, st[x][j]);    //$a_j$ 一定是 $a$ 数组中这一段区间内最大的数
            mi = min(mi, st_2[x][j]);  //$b_i$ 一定是 $b$ 数组中这一段区间内最小的数
            x += (1 << j);
          }
        }
        if (ma != a[p[b[i]]] || mi < b[i]) {
          t = 1;
          break;
        }
      }
    }
    if (t)
      cout << "NO\n";
    else
      cout << "YES\n";
  }
  return 0;
}
```


---

## 作者：COsm0s (赞：0)

有一个重要的性质：**对于第 $p$ 次操作的 $a_{p, i}$，必有 $a_{p,i}\geq a_{p-1,i}$**。

证明显然，一次操作只能让 $a_i$ 变成其区间内的最大值，那么这个 $\max\geq a_i$。

那么，对于每一个 $a_i$，我们只能寻找一个 $a_j > a_i$ 来更新它，这也就意味着 $\forall i,a_i\leq b_i$。

那就分讨。

对于 $1\leq j<i$，我们需要找到一个 $j$ 使得 $a_j = b_i$，并且 $\max\limits^{i-1}_{k=j+1} < b_i$。找到最近的显然是最优的。

对于 $i < j \leq n$，同理。

显然这个东西可以用线段树维护最大或最小值。

复杂度 $\Theta(n\log n)$。

---

## 作者：kczw (赞：0)

# 题意
共 $t$ 组数据，对于每组数据给定两个长 $n$ 数列 $a,b$。对于 $a_i$，如果与相邻的数比它小，那么这个数可以被赋值为 $a_i$。问最后能否将 $a$ 修改成 $b$。
# 思路
维护一个单调队列，存储当前可以替换的数。遍历 $a$，判断当有 $a_i\ne b_i$ 时，是否能够将 $a_i$ 替换成 $b_i$。

关于为什么维护的是单调队列其实很好理解，因为修改时只能让大数覆盖小数。

举个例吧。
```
a:4 3 2 1 5 4 3 2 1 
b:4 3 3 3 5 1 3 2 2 
```
单看在第一次遍历 $a$。

- $a_1$ 时，无可替换。
- $a_2$ 时，可替换 $4$。
- $a_3$ 时，可替换 $3,4$。
- $a_4$ 时，可替换 $2,3,4$。
- $a_5$ 时，队列中有数比 $5$ 小，所以要弹出这些数，因为它们无法覆盖 $a_5$ 及其后面的数。
- $a_6$ 时，可以替换 $5$。
- $a_7$ 时，发现 $a_7=b_7$ 所以 $a_7$ 不可以被覆盖，否则会导致 $a_7\ne b_7$，因为只能大数覆盖小数，也就是只能由小到大，不能由大到小。所以清空队列。
- ……

这里其实已经涵盖了绝大多数的情况了，就不再举例。

但是问题又来了，怎么确定可以修改的数在队列中呢。这里直接开个数组维护就可以了，毕竟 $1\le a_i\le n\le 2\times10^5$，空间是够的。

最后就正反各遍历一遍，看对于每个 $a_i\ne b_i$ 是否可以达到 $a_i=b_i$ 就可以了。
# 实现
```cpp
#include<iostream>
#include<deque>
#define N 200005
using namespace std;
int t,n,ned,a[N],b[N],vist[N],use[N];
int main(){
	scanf("%d",&t);
	while(t--){
		ned=0;
		deque<int> q;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
			vist[i]=(a[i]==b[i]?0:1);
			ned+=vist[i];
			use[i]=0;
		}for(int i=1;i<=n;i++){
			if(a[i]==b[i])while(!q.empty())use[q.back()]--,q.pop_back();
			while(!q.empty()&&a[i]>q.back())use[q.back()]--,q.pop_back();
			while(!q.empty()&&q.front()>b[i])use[q.front()]--,q.pop_front();
			if(vist[i]&&use[b[i]]>0)vist[i]=0,ned--;
			q.push_back(a[i]);use[a[i]]++;
		}while(!q.empty())use[q.back()]--,q.pop_back();
		for(int i=n;i>=1;i--){
			if(a[i]==b[i])while(!q.empty())use[q.back()]--,q.pop_back();
			while(!q.empty()&&a[i]>q.back())use[q.back()]--,q.pop_back();
			while(!q.empty()&&q.front()>b[i])use[q.front()]--,q.pop_front();
			if(vist[i]&&use[b[i]]>0)vist[i]=0,ned--;
			q.push_back(a[i]);use[a[i]]++;
		}printf(ned?"NO\n":"YES\n");
	}
	return 0;
}
```

---

## 作者：Kniqht (赞：0)

这个方法是使用数据结构将简单版的做法优化。

## Easy Version

考虑区间操作重叠，一定是值大的区间覆盖值小的区间。那么我们应该按照值从小到大的顺序进行操作。容易发现，我们一定是能扩展就扩展，而扩展的左右最大范围必须有如下条件（$val$ 为当前值的大小）

1. 当前修改后的所有 $a_i<val$
2. 最终的所有 $b_i\geq val$ 

解释：第一条就是因为当前 $val$ 必须是区间 $[l,r]$ 的最大值才能覆盖。第二条则是因为我们不能覆盖 $b_i$ 更小的位置，**因为我们从小到大操作**，若覆盖了以后一定覆盖不回去。

然后找到左右最大能扩展的区间，将所有下标在 $[l,r]$ 范围内的 $a_i$ 赋值为 $val$ 即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1010;
int n,T;
int a[N],b[N]; 
vector<int> v[N];
int main(){
    scanf("%d",&T);
    while(T--){
    	scanf("%d",&n);
    	for(int i=1;i<=n;i++) v[i].clear();
    	for(int i=1;i<=n;i++) scanf("%d",&a[i]),v[a[i]].push_back(i);
    	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    	for(int i=1;i<=n;i++){
    		for(int j=0;j<v[i].size();j++){
    			int p=v[i][j];
    			for(int k=p-1;k;k--){
    				if(b[k]<i||a[k]>=i) break;
    				a[k]=i;
    			}
    			for(int k=p+1;k<=n;k++){
    				if(b[k]<i||a[k]>=i) break;
    				a[k]=i;
				}
			}
		}
		bool flag=1;
		for(int i=1;i<=n;i++)
			if(a[i]!=b[i]){
				flag=0;
				break;
			}
		
		printf(flag?"YES":"NO");putchar('\n');
	}
	return 0;
}

```

## Hard Version

发现左右扩展的区间一定具有单调性，所以我们用两次二分找出最左能扩展的区间，最右能扩展的区间。而二分的判断函数可以发现就是一个区间最值问题，由于 $\{a\}$ 会发生变化，所以我们需要一个能维护区间推平，区间最大值的线段树。而 $\{b\}$ 不会发生变化，我们只需要一个 ST 表即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10,M=19,inf=0x3f3f3f3f;
int n,T;
int a[N],b[N]; 
vector<int> v[N];
int f[N][M];
void init(){
    for(int j=0;j<M;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            if(!j) f[i][j]=b[i];
            else f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
}
int query(int l,int r){
    int len=r-l+1;
    int k=log(len)/log(2);
    return min(f[l][k],f[r-(1<<k)+1][k]);
}
struct Nd{
	int l,r,mx,add;
}tr[N*4];
void pushup(int u){
	tr[u].mx=max(tr[u<<1].mx,tr[u<<1|1].mx);
}
void pushdown(int u){
	if(tr[u].add==inf) return;
	tr[u<<1].mx=tr[u<<1|1].mx=tr[u].add;
	tr[u<<1].add=tr[u<<1|1].add=tr[u].add;
	tr[u].add=inf;
}
void build(int u,int l,int r){
	tr[u]={l,r,0,inf}; 
	if(tr[u].l==tr[u].r){
		tr[u].mx=a[l];
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid);build(u<<1|1,mid+1,r);
	pushup(u);
}
int Query(int u,int l,int r){
	if(tr[u].l>r||tr[u].r<l) return -inf;
	if(tr[u].l>=l&&tr[u].r<=r)
		return tr[u].mx;
	pushdown(u);
	return max(Query(u<<1,l,r),Query(u<<1|1,l,r));
}
void modify(int u,int l,int r,int k){
	if(tr[u].l>r||tr[u].r<l) return;
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].add=k;
		tr[u].mx=k;
		return;
	}
	pushdown(u);
	modify(u<<1,l,r,k);modify(u<<1|1,l,r,k);
	pushup(u);
}
int main(){
    scanf("%d",&T);
    while(T--){
    	scanf("%d",&n);
    	for(int i=1;i<=n;i++) v[i].clear();
    	for(int i=1;i<=n;i++) scanf("%d",&a[i]),v[a[i]].push_back(i);
    	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    	init();build(1,1,n); 
    	for(int i=1;i<=n;i++){
    		for(int j=0;j<v[i].size();j++){
    			int p=v[i][j];
    			int L=1,R=p-1,ans=inf;
    			while(L<=R){
    				int mid=L+R>>1;
    				if(query(mid,p)>=i&&Query(1,mid,p-1)<i) R=mid-1,ans=mid;
    				else L=mid+1;
				}
				if(ans!=inf) modify(1,ans,p,i);
				L=p+1,R=n,ans=inf;
    			while(L<=R){
    				int mid=L+R>>1;
    				if(query(p,mid)>=i&&Query(1,p+1,mid)<i) L=mid+1,ans=mid;
    				else R=mid-1;
				}
				if(ans!=inf) modify(1,p,ans,i);
			}
		}
		bool flag=1;
		for(int i=1;i<=n;i++)
			if(Query(1,i,i)!=b[i]){
				flag=0;
				break;
			}
		printf(flag?"YES":"NO");putchar('\n');
	}
	return 0;
}
```

---

