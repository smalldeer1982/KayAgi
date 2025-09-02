# [COTS 2020] 定序 Redoslijed

## 题目背景

译自 [Izborne Pripreme 2020 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2020/) D1T2。$\texttt{4s,0.5G}$。

鸣谢：SPJ by @[mygr](https://www.luogu.com.cn/user/739552)

## 题目描述

在一块长 $N\,\mathrm{m}$ 的木板上画画。木板被从左往右划分成 $N$ 个格子，每个格子长 $1\,\mathrm{m}$。

现在已知在木板上涂了 $M$ 笔，第 $i$ 笔将第 $l_i\sim r_i$ 个格子涂成颜色 $c_i$。

给定最后涂色后木板的状态，试构造一种操作顺序使得一次操作后木板的状态为给定状态，或报告无解。


## 说明/提示


对于 $100\%$ 的数据，保证：

- $1\le N,M\le 5\times 10^5$；
- $1\le l_i\le r_i\le N$；
- $1\le c_i\le 5\times 10^5$；
- $0\le b_i\le 5\times 10^5$。


| 子任务编号 | $N\le $ | 特殊性质 | 得分 |  
| :--: | :--: | :--: | :--: |
| $ 1 $    | $9$ |  |$ 5 $   | 
| $ 2 $    | $5\,000$ | A |$ 10 $   |  
| $ 3 $    | $5\times 10^5$ | A |$ 25 $   |  
| $ 4 $    | $5\, 000$ || $ 12 $   |
| $ 5 $    | $5\times 10^5$ | B| $ 16 $   |
| $ 6 $    | $5\times 10^5$ || $ 32 $   |

- 特殊性质 A：$c_i$ 两两不同。
- 特殊性质 B：$1\le c_i\le 5$。

## 样例 #1

### 输入

```
6 5
3 5 5
1 1 6
1 3 2
1 4 7
4 6 6
6 2 5 5 5 6```

### 输出

```
DA
4 5 3 1 2
```

## 样例 #2

### 输入

```
14 6
6 9 4
12 13 6
2 3 5
1 14 3
5 6 9
9 12 8
3 5 5 3 9 4 4 4 8 8 8 6 6 3```

### 输出

```
DA
4 5 1 6 2 3```

## 样例 #3

### 输入

```
15 5
7 8 3
10 14 5
4 7 2
3 12 1
5 9 4
0 0 1 2 4 4 3 3 4 5 1 1 5 5 0```

### 输出

```
NE```

# 题解

## 作者：VainSylphid (赞：7)

有意思的题。

正着考虑非常困难！这样我没法知道该用哪次染色操作。但是如果我们考虑最后一次染色 $(l,r,c)$，假装有解，那么最终的 $b_l\sim b_r$ 的颜色必须是 $c$。

类似地从后往前考虑，我们能做某次染色 $(l,r,c)$ 当且仅当区间 $b_l\sim b_r$ 中颜色与 $c$ 不同的位置在之后又被正确地染过了，因为只有这些位置是可以任意染色的，不管染的对不对之后都会覆盖掉。

并且，可以发现，如果有多个操作可以同时放在这个位置，那么任选一个操作不会使有解的情况变成无解，因为已经被染过的位置只会越来越多，可以用的操作也会越来越多，原本可以用的操作还是可以用。

那么现在我们就得到了这样一个构造方法：从最后一次操作往前考虑，每次找到一个操作 $(l,r,c)$ 使得 $b_l\sim b_r$ 的每个位置要么是 $c$，要么被标记了，如果没有合法的操作直接报告无解。把这个操作加到答案序列里，然后把 $b_l\sim b_r$ 全部打上标记，也就是这些位置在之后会被覆盖。

显然这样的构造一定合法，并且只要有解，一定能通过这样的构造找到一个解。

但是这怎么和暴力同分！我们发现这个过程和拓扑排序有点像，不如看看能不能快速维护有哪些合法的操作 $(l,r,c)$。这是一个常见的套路：把 $(l,r,c)$ 拆成线段树上的若干个区间。

我们发现，对于线段树上的一个区间 $[L,R]$，如果这个区间里有两个颜色不同的位置都没标记，那包含 $[L,R]$ 的操作肯定都不合法。如果这个区间里只有一个颜色的位置没标记，那么只有同一个颜色的操作可能合法。

如果一个操作 $(l,r,c)$ 拆出来的所有区间都合法了，那这个操作也就合法了。因此，我们把每个操作挂到线段树上，类似拓扑排序记录每个操作拆成了多少个区间，记为 $cnt_i$，用一个队列记录未使用的合法操作，然后在线段树上维护以下过程：

* 取出队头的一个操作 $(l,r,c)$，如果没有这样的操作就报告无解。

* 把 $b_l\sim b_r$ 全部改成一个你喜欢的标记，比如 $-1$。因为不能用懒标记，所以要暴力递归找到区间中所有没标记过的位置。

* pushup 的时候，如果当前区间首次只剩下一种没标记的颜色，那么把这个区间上挂着的相同颜色的操作的 $cnt$ 减一。

* 如果当前区间全部被标记了，那么把这个区间上挂着的所有操作的 $cnt$ 减一，但是之前就已经同色的那些区间不能减，需要记录下首次只剩下一种没标记的颜色编号，这次减的时候就跳过了。

* 如果一个操作的 $cnt$ 被减到 $0$，让它入队。

这样一来，每个操作被拆成 $\log N$ 个区间，线段树上的每个区间至多遍历两次挂在上面的操作，总时间复杂度 $O((N+M)\log N)$。

代码并不难写。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,xl[500005],xr[500005],c[500005],b[500005];
int d[2000005],cnt[500005];
int vis[2000005],cl[2000005];
vector<int> v[2000005];
queue<int> q;
int ans[500005],pos;
void insert(int p,int l,int r,int id)
{
	if(xl[id] <= l && r <= xr[id])
	{
		v[p].push_back(id),cnt[id]++;
		return;
	}
	int mid = l + r >> 1;
	if(xl[id] <= mid)
		insert(p << 1,l,mid,id);
	if(xr[id] > mid)
		insert(p << 1 | 1,mid + 1,r,id);
}
void update(int p)
{
	if(d[p] == -2 && vis[p] < 2)
	{
		vis[p] = 2;
		for(auto i : v[p])
			if(cl[p] != c[i])
			{
				if(!(--cnt[i]))
					q.push(i);
			}
	}
	if(d[p] != -1 && vis[p] < 1)
	{
		cl[p] = d[p],vis[p] = 1;
		for(auto i : v[p])
			if(cl[p] == c[i])
			{
				if(!(--cnt[i]))
					q.push(i);
			}
	}
}
void pushup(int p)
{
	if(d[p << 1] == -1 || d[p << 1 | 1] == -1)
		d[p] = -1;
	else if(d[p << 1] == -2)
		d[p] = d[p << 1 | 1];
	else if(d[p << 1 | 1] == -2)
		d[p] = d[p << 1];
	else
		d[p] = (d[p << 1] == d[p << 1 | 1] ? d[p << 1] : -1);
	update(p);
}
void build(int p,int l,int r)
{
	if(l == r)
	{
		d[p] = b[l];
		update(p);
		return;
	}
	int mid = l + r >> 1;
	build(p << 1,l,mid);
	build(p << 1 | 1,mid + 1,r);
	pushup(p);
}
void modify(int p,int l,int r,int x,int y)
{
	if(x <= l && r <= y && d[p] == -2)
		return;
	if(l == r)
	{
		d[p] = -2;
		update(p);
		return;
	}
	int mid = l + r >> 1;
	if(x <= mid)
		modify(p << 1,l,mid,x,y);
	if(y > mid)
		modify(p << 1 | 1,mid + 1,r,x,y);
	pushup(p);
}
int query(int p,int l,int r,int x)
{
	if(l == r) return d[p];
	int mid = l + r >> 1;
	if(x <= mid) return query(p << 1,l,mid,x);
	return query(p << 1 | 1,mid + 1,r,x);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++)
		scanf("%d%d%d",&xl[i],&xr[i],&c[i]),insert(1,1,n,i);
	for(int i = 1;i <= n;i++)
		scanf("%d",&b[i]);
	build(1,1,n);
	while(!q.empty())
	{
		int tmp = q.front();
		q.pop();
		ans[++pos] = tmp;
		modify(1,1,n,xl[tmp],xr[tmp]);
	}
	for(int i = 1;i <= n;i++)
		if(query(1,1,n,i) != -2 && query(1,1,n,i) != 0)
		{
			printf("NE\n");
			return 0;
		}
	if(pos != m)
		printf("NE\n");
	else
	{
		printf("DA\n");
		for(int i = m;i >= 1;i--)
			printf("%d%c",ans[i]," \n"[i == 1]);
	}
	return 0;
}
```

---

## 作者：drowsylve (赞：2)

感觉像是见过的题，有意思，但是不会，所以学了一下官解。

- hint：类似的染色问题，很套路的从后往前考虑问题；类似的构造问题，可以往建图的方向思考。

构造题先考虑不合法，由于某些位置可能无色，所以可以用前缀和维护一下染过色的地方筛掉一部分不合法。

至此我们先假设当前有解，从最后一次染色开始向前考虑。有一个比较显然的贪心是找到一次操作 $i$，使得 $b_{l_i}$ 到 $b_{r_i}$ 都为 $c_i$，则此次操作所覆盖的部分在此前可以任意进行操作，把这部分颜色记为**任意色**，意味在之后的过程中可以匹配任意的 $c$。

于是我们有了一个 $O(NM)$ 的做法，如果当前找不到合法的操作说明无解，否则贪心的继续向前考虑。由于每次可匹配的颜色集合是不减的，易证此做法是不劣的。

接下来我们先考虑特殊性质 A，此时我们可以认为操作和颜色是一一对应的。可以构建一个线段树结构，把每操作都拆分为线段树上的 $\log$ 个区间并与这些区间建边，对于每个 $b_i$ 找到在线段树上的 $\log$ 个祖先并建立关系。**注意：这里的建边只是大概描述，实现时因为若干细节不一定准确。**

先从每个操作点出发，跑一个拓扑排序。意会一下，相当于先找到没有任何限制的点，即入度为 0 的线段树上的点，并且解放这些子树中点的限制，对应了最开始做法中记为任意色的操作，这样可以接着找到下一个入度都为 0 的颜色（操作）并继续找答案。

此图边数大概是 $O((N+M)\log N)$ 级别的，若跑出了 $m$ 个点的拓扑序，则找到了合法的解，否则无解。

尝试扩展此做法，我们可以沿用线段树上的类似思想。

我们对于线段树上的每个节点维护最小最大颜色，记为 $minc$ 与 $maxc$。尝试对 $minc>maxc$，$minc=maxc$，$minc<maxc$ 进行分讨，分别对应任意色，一种颜色，至少两种颜色。

类似 sub3 的解决方案，首先将操作拆分为若干区间，维护计数器 $d$ 记录这些区间中有多少个区间满足至少两种颜色或者一种颜色但不等于此步骤的颜色（$minc=maxc \ne c_i$），发现当 $d$ 归 0 时，相当于拓扑过程中没有入度了，当前操作已经合法，计入队列 $q$，同时更新包含区间的 $minc$，$maxc$，以及产生的后续影响。

时间复杂度 $O((N+M)\log N)$。有关实现细节，可以参考代码以及注释。


```cpp
bool M1;
#include<bits/stdc++.h>
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<'\n'
//#define int long long
//#define double long double
#define ll long long
#define db double
#define pb push_back
#define pii pair<int,int>
#define mkp make_pair
#define fr first
#define sc second
using namespace std;
template<typename T> void ckmin(T &x,T y){x=min(x,y);}
template<typename T> void ckmax(T &x,T y){x=max(x,y);}
const int N=500005;
const int inf=1e9;
const int mod=1000000007;
int n,m;
pii a[N];
int b[N],col[N],d[N];
int pre[N];
queue<int> q;
struct Sgt{
	struct node{
		int mi,mx;
		vector<int> cov;
		node(){mi=inf,mx=-inf;}
	}c[N<<2];
	int vis[N<<2];
	void pu(int p){
		c[p].mi=min(c[p<<1].mi,c[p<<1|1].mi);
		c[p].mx=max(c[p<<1].mx,c[p<<1|1].mx);
	}
	void build1(int l,int r,int p,int ql,int qr,int x){
		if(ql<=l&&r<=qr){
			c[p].cov.pb(x);
			d[x]++;
			return;
		}
		int mid=l+r>>1;
		if(ql<=mid) build1(l,mid,p<<1,ql,qr,x);
		if(qr>mid) build1(mid+1,r,p<<1|1,ql,qr,x);
	}
	void build2(int l,int r,int p){
		if(l==r){//注意无色的地方不应该计入。 
			if(b[l]) c[p].mi=c[p].mx=b[l];
			return;
		}
		int mid=l+r>>1;
		build2(l,mid,p<<1);
		build2(mid+1,r,p<<1|1);
		pu(p);
	}
	void check(int p){
		if(c[p].mi<c[p].mx) return;
		if(c[p].mi==c[p].mx&&vis[p]) return;
		if(c[p].mi>c[p].mx){
			for(int x:c[p].cov) if(--d[x]==0) q.push(x);
			c[p].cov.clear();//这里清空是避免后续重复操作。 
			return;
		}
		vector<int> cur;
		for(int x:c[p].cov){
			if(col[x]==c[p].mi){
				if(--d[x]==0) q.push(x);
			}else{
				cur.pb(x);
			}
		}
		c[p].cov=cur;//如果颜色与目标颜色不相同的话要保留，否则清空避免重复。 
		vis[p]=1;//被释放的区间不用再操作了，不记的话会T一些点。 
	}
	void dfs(int l,int r,int p){
		check(p);
		if(l==r) return;
		int mid=l+r>>1;
		dfs(l,mid,p<<1),dfs(mid+1,r,p<<1|1);
	}
	void mdf(int l,int r,int p,int ql,int qr){
		if(c[p].mx<c[p].mi) return;//已经操作过，则子树中都应该操作过了。 
		if(ql<=l&&r<=qr){
			c[p].mi=inf,c[p].mx=-inf;
			check(p);
			//此处不同于一般线段树，无需return，原因是需要对于子树中的每个点都进行更改。 
			//由于每个点改为任意色后只会操作一次，所以复杂度是对的。 
		}
		if(l==r) return;
		int mid=l+r>>1;
		if(ql<=mid) mdf(l,mid,p<<1,ql,qr);
		if(qr>mid) mdf(mid+1,r,p<<1|1,ql,qr);
		pu(p);
		check(p);
	}
}sgt;
bool M2;
signed main(){
//	look_memory;
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i].fr>>a[i].sc>>col[i];
		sgt.build1(1,n,1,a[i].fr,a[i].sc,i);//拆分区间，维护d 
		pre[a[i].fr]++,pre[a[i].sc+1]--;
	}
	for(int i=1;i<=n;i++) cin>>b[i];
	sgt.build2(1,n,1);//颜色 
	for(int i=1,sum=0;i<=n;i++){//判掉一些无解。
		sum+=pre[i];
		if((sum&&!b[i]) || (!sum&&b[i])){cout<<"NE";return 0;}
	}
	sgt.dfs(1,n,1);//类似拓扑中先找出入度为0的点。 
	vector<int> ans;
	while(!q.empty()){
		int u=q.front();q.pop();
		sgt.mdf(1,n,1,a[u].fr,a[u].sc);//更新这部分为任意色。 
		ans.pb(u);
	}
	if(ans.size()<m){cout<<"NE";return 0;}
	reverse(ans.begin(),ans.end());//倒序输出 
	cout<<"DA\n";
	for(int x:ans) cout<<x<<" ";
	cout<<"\n";
	return 0;
}

```
若有疏漏，欢迎评论私信指出！

---

## 作者：zifanwang (赞：1)

先把是否有色的约束处理掉。累一个前缀和，对每个位置判一下即可。

考察区间覆盖的性质，显然最后一个操作的区间内的颜色一定与其覆盖的颜色相同。考虑从后往前确定操作的顺序，一个操作只要满足这个条件就可以作为当前的最后一个操作，如果有多个满足条件的操作，随便取一个都合法。

考虑维护满足条件的操作，每次取出一个操作将其区间内的位置标记掉，将所有从不合法变为合法的操作加入集合。

如何快速求出从不合法变为合法的操作？有个经典的套路就是用线段树将每个区间拆成若干段，对每个操作记录不合法的段数 $\text{cnt}_i$。每次区间标记在线段树上递归找到所有需要标记的点，因为每个点只会被标记一次，所以时间复杂度是一个 $\log$。

观察什么时候需要将一些操作的 $\text{cnt}$ 减一。发现当线段树上的一个点对应区间内的颜色数从 $>1$ 变成 $1$ 时，需要将含有这个点且颜色与剩下的这个颜色相同的操作的 $\text{cnt}$ 减一，对每个点记录颜色 $\min,\max$ 即可判断。当一个点被完全标记掉时将包含它的剩下操作的 $\text{cnt}$ 减一。$\text{cnt}$ 减到 $0$ 时加入集合即可。

然后就做完了，时间复杂度 $\mathcal O((N+M)
\log N)$，参考代码：
```cpp
#include<bits/stdc++.h>
#define mxn 500003
#define pb push_back
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define rept(i,a,b) for(int i=(a);i<(b);++i)
#define drep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
struct node{
	int l,r,c;
}d[mxn];
int n,m,tt,tot,a[mxn],c[mxn],ct[mxn],st[mxn],ans[mxn],t1[mxn<<2],t2[mxn<<2],cl[mxn<<2];
vector<int>t[mxn<<2];
bool b[mxn<<2],b1[mxn<<2];
void build(int p,int l,int r){
	if(l==r){
		if(a[l])t1[p]=t2[p]=a[l],b1[p]=1;
		else t1[p]=1e9,t2[p]=-1e9,b[p]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	t1[p]=min(t1[p<<1],t1[p<<1|1]);
	t2[p]=max(t2[p<<1],t2[p<<1|1]);
	b1[p]=t1[p]==t2[p],b[p]=t2[p]<0;
}
void add(int p,int l,int r,int x,int L,int R){
	if(l<=L&&R<=r){
		if(b1[p]&&t1[p]==d[x].c)return;
		ct[x]++,t[p].pb(x);
		return;
	}
	int mid=(L+R)>>1;
	if(l<=mid)add(p<<1,l,r,x,L,mid);
	if(r>mid)add(p<<1|1,l,r,x,mid+1,R);
}
void upd(int p,int l,int r,int L,int R){
	if(b[p])return;
	if(L==R){
		b[p]=1,t1[p]=1e9,t2[p]=-1e9;
		for(int i:t[p])if(d[i].c!=cl[p]){
			if(!(--ct[i]))st[++tot]=i;
		}
		return;
	}
	int mid=(L+R)>>1;
	if(l<=mid)upd(p<<1,l,r,L,mid);
	if(r>mid)upd(p<<1|1,l,r,mid+1,R);
	t1[p]=min(t1[p<<1],t1[p<<1|1]);
	t2[p]=max(t2[p<<1],t2[p<<1|1]);
	if(t2[p]<0&&!b[p]){
		b[p]=1;
		for(int i:t[p])if(d[i].c!=cl[p]){
			if(!(--ct[i]))st[++tot]=i;
		}
	}else if(t1[p]==t2[p]&&!b1[p]){
		cl[p]=t1[p],b1[p]=1;
		for(int i:t[p])if(d[i].c==cl[p]){
			if(!(--ct[i]))st[++tot]=i;
		}
	}
}
signed main(){
	n=read(),m=read();
	rep(i,1,m)d[i].l=read(),d[i].r=read(),d[i].c=read(),c[d[i].l]++,c[d[i].r+1]--;
	rep(i,1,n){
		a[i]=read();
		c[i]+=c[i-1];
		if((c[i]&&!a[i])||(!c[i]&&a[i])){
			puts("NE");
			return 0;
		}
	}
	build(1,1,n);
	rep(i,1,m)add(1,d[i].l,d[i].r,i,1,n);
	rep(i,1,m)if(!ct[i])st[++tot]=i;
	while(tot){
		int x=st[tot--];ans[++tt]=x;
		upd(1,d[x].l,d[x].r,1,n);
	}
	if(tt!=m)puts("NE");
	else{
		puts("DA");
		drep(i,m,1)cout<<ans[i]<<" ";
	}
	return 0;
}
```

---

## 作者：masterhuang (赞：0)

> 一块有 $n$ 个格子的板，现在已知在板上涂了 $m$ 笔，第 $i$ 笔将第 $l_i\sim r_i$ 个格子涂成颜色 $c_i$​。
>
> 给定一个乱序的 $(l_i,r_i,c_i)$ 序列。
>
> 给定最后涂色后木板的状态 $b_{1},b_2,\cdots ,b_n$​，试构造一种操作顺序，使得依次操作后木板的状态为给定状态，或报告无解。
>
> - 特别的 $b_i=0$ 表示未被着色。
>
> $1\le n,m,b_i,c_i\le 5\times 10^5$​。

这种覆盖式着色，经典套路是**从后往前考虑**。找不到其他题了，给个类似的[水题](https://www.luogu.com.cn/problem/AT_arc191_a)。

然后再考虑**精准覆盖**，相当于变成总过 $n$​ 次单个位置着色。

每次从合法队列里拎出一个区间，着色完要找出所有**恰好此时合法的区间**（并判断是否矛盾无解了），再扔到队列里。

然后不断操作下去，直到所有区间都被操作过了，就构造完了。

---

于是问题转化为：$n$ 次删除单个格子，每次维护出所有 $(l,r,c)$ 满足：$(l,r)$ 未被删除的点颜色均为 $c$​。

这种算单点对区间影响的问题，有**经典套路**：

把区间 $[l,r]$ 挂到线段树 $\log$ 个区间上，这样一个区间合法转换为了 $\log$ 个区间均合法。

线段树维护：单点修改，区间是否只剩一个颜色（颜色是多少）即可。

复杂度 $O(n\log n)$。

---

## 作者：xxxxxzy (赞：0)

还挺有意思的。

考虑倒着维护操作，每次可以选一个操作的条件是这个区间 $[l_i,r_i]$ 的每个数要不被覆盖过要不为 $c_i$，发现每次选一个可以拍上去的操作一定不会变劣。

这样得到了一个 $O(nm)$ 的暴力做法。

考虑优化：

+ 把每个操作拆到线段树区间上，记拆了 $cnt_i$ 个区间。
+ 如果一个区间有颜色的地方经一次操作后（或是初始状态）全是同一种颜色，把当前区间的所有颜色为 $c_i$ 的 $cnt_i$ 减一。
+ 如果一个区间经操作后全部被以后的操作覆盖，就把当前区间的所有 $cnt_i$ 减一，但是要除去上一种已经减过的 $c_i$ 不减。
+ 如果 $cnt_i$ 变为 $0$，塞到队列里面，然后取出后把 $[l_i,r_i]$ 覆盖。

这样复杂度是对的，因为每个节点最多只会遍历两次挂在上面的操作，总复杂度 $O(n \log n)$，空间线性。

---

