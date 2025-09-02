# Blood Cousins Return

## 题目描述

Polycarpus got hold of a family tree. The found tree describes the family relations of $ n $ people, numbered from $1$ to $ n $ . Every person in this tree has at most one direct ancestor. Also, each person in the tree has a name, the names are not necessarily unique.

We call the man with a number $ a $ a 1-ancestor of the man with a number $ b $ , if the man with a number $ a $ is a direct ancestor of the man with a number $ b $ .

We call the man with a number $ a $ a $ k $ -ancestor $ (k \gt 1) $ of the man with a number $ b $ , if the man with a number $ b $ has a 1-ancestor, and the man with a number $ a $ is a $ (k-1) $ -ancestor of the 1-ancestor of the man with a number $ b $ .

In the tree the family ties do not form cycles. In other words there isn't a person who is his own direct or indirect ancestor (that is, who is an $ x $ -ancestor of himself, for some $ x $ , $ x \gt 0 $ ).

We call a man with a number $ a $ the $ k $ -son of the man with a number $ b $ , if the man with a number $ b $ is a $ k $ -ancestor of the man with a number $ a $ .

Polycarpus is very much interested in how many sons and which sons each person has. He took a piece of paper and wrote $ m $ pairs of numbers $ v_{i} $ , $ k_{i} $ . Help him to learn for each pair $ v_{i} $ , $ k_{i} $ the number of distinct names among all names of the $ k_{i} $ -sons of the man with number $ v_{i} $ .

## 样例 #1

### 输入

```
6
pasha 0
gerald 1
gerald 1
valera 2
igor 3
olesya 1
5
1 1
1 2
1 3
3 1
6 1
```

### 输出

```
2
2
0
1
0
```

## 样例 #2

### 输入

```
6
valera 0
valera 1
valera 1
gerald 0
valera 4
kolya 4
7
1 1
1 2
2 1
2 2
4 1
5 1
6 1
```

### 输出

```
1
0
0
0
2
0
0
```

# 题解

## 作者：Guess00 (赞：14)

## 题解 CF246E Blood Cousins Return

#### 本题思路:dfs序+树状数组

先考虑这题在序列上怎么做，明显在序列上就是[HH的项链](https://www.luogu.com.cn/problem/P1972)了。

然后考虑怎么把它放在树上，那不就是[CF208E](https://www.luogu.com.cn/problem/CF208E)了吗。

所以CF246E=CF208E+P1972(smg$\quad$~~(紫题=紫题+蓝题,所以蓝题=0)~~

下面简述这两题。

CF208E:森林中求一个的节点的$K-son$个数。对每个深度用$\text{vector}$维护本层的dfs序。对每个查询二分出$K-son$个数。详见[这里](https://www.luogu.com.cn/blog/Guess00/solution-CF208E)。

HH的项链:求区间颜色个数。将查询离线，按右端点排序。从左到右枚举，将这个点+1,这个点颜色的上一个位置-1.到了一个查询的右端点时计算答案($s_r-s_{l-1}$).用树状数组维护。详见[原题](https://www.luogu.com.cn/problem/P1972)。

本题同理，将查询离线，求出其$K-son$的深度、最左边和最右边，按优先深度其次右端点排序，之后就与HH的项链一模一样了。

注意事项:
1. 每处理完一层后时注意清零。
2. 虽然这是一个森林但不同树的同一深度可以放一起处理。

时间复杂度:$\Theta(n)$~$\Theta(n\log n)$

$\mathbb{CODE:}$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=110005;
struct que{int id,d,l,r;}a[MAXN];
int n,q,i,j,x,y,z,l,r,maxd,cnt,c[MAXN],f[MAXN],pre[MAXN],col[MAXN],dep[MAXN],in[MAXN],out[MAXN],ans[MAXN];
string s;
map<string,int> m;
vector<int> G[MAXN],inn[MAXN],t[MAXN];
inline void read(int &x)    //快读 
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
    	if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)   //快输 
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
inline int lowbit(int x){return x&(-x);}
inline void add(int x,int y,int n)
{
	while (x<=n)
		c[x]+=y,x+=lowbit(x);
}
inline int query(int x)
{
	int ans=0;
	while (x)
		ans+=c[x],x-=lowbit(x);
	return ans;
}
inline void dfs(int u)
{
	dep[u]=dep[f[u]]+1;
	maxd=max(maxd,dep[u]);
	in[u]=++cnt;
	if (!inn[dep[u]].size())//在每层前面多发一个数,又不然树状数组会锅 (lowbit(0)=0)
		inn[dep[u]].push_back(-1),t[dep[u]].push_back(-1);
	inn[dep[u]].push_back(in[u]);
	t[dep[u]].push_back(u);
	for (int i=0;i<G[u].size();i++)
		dfs(G[u][i]);
	out[u]=cnt;
}
inline bool cmp(que a,que b)
{
	if (a.d==b.d)
		return a.r<b.r;  //深度相同按右端点排序 
	return a.d<b.d;   //优先深度 
}
signed main(void)
{
	read(n);
	for (i=1;i<=n;i++)
	{
		cin>>s;
		read(f[i]);
		G[f[i]].push_back(i);
		if (!m[s])  //用map把名字变成颜色，方便之后计算 
			m[s]=++cnt;
		col[i]=m[s];
	}
	cnt=0,dep[0]=-1;   //我只是想让0号点深度为0而已 
	dfs(0);
	read(q);
	for (i=1;i<=q;i++)
	{
		read(x),read(y);
		z=dep[x]+y;  //
		l=lower_bound(inn[z].begin()+1,inn[z].end(),in[x])-inn[z].begin();
		r=upper_bound(inn[z].begin()+1,inn[z].end(),out[x])-inn[z].begin()-1;
		//二分求出k-son的最左边与最右边 
		a[i]=que{i,z,l,r};  //将查询离线 
	}
	sort(a+1,a+q+1,cmp);  //排序 
	for (x=i=1;i<=q;i++)
	{
		if (a[i].d>maxd)  //由于数据的特异性,需要特判其是否超过最大深度 
			continue;
		for (j=x;j<=a[i].r;j++)
		{
			y=col[t[a[i].d][j]];
			if (pre[y])
				add(pre[y],-1,t[a[i].d].size());
			add(j,1,t[a[i].d].size());
			pre[y]=j;
		}
		x=a[i].r+1;
		ans[a[i].id]=query(a[i].r)-query(a[i].l-1);
		if (i!=q && a[i].d!=a[i+1].d)  //换了一个深度,清空数组 
		{
			for (j=0;j<=a[i].r;j++)
				pre[col[t[a[i].d][j]]]=0;
			for (j=0;j<=t[a[i].d].size();j++)
				c[j]=0;
			x=1;
		}
	}
	for (i=1;i<=q;i++)
		print(ans[i]),putchar('\n');
	return 0;
} 
```

---

## 作者：feecle6418 (赞：11)

线段树合并在处理关于深度的信息上几乎无所不能。

对于这道题，我们以深度为下标建立线段树，在每个叶子上维护一个 set 表示深度为 $x$ 的名字构成的集合。合并线段树的时候对叶子的 set 启发式合并即可，复杂度是 $O(n\log^2 n)\sim O(n\log n)$（前面是时间，后面是空间）。假如用 https://www.luogu.com.cn/blog/feecle6418/solution-p5384 里面的办法优化空间，并且将 `set` 换为有序插入均摊 $O(1)$ 的 `splay`，可以做到 $O(n\log n)\sim O(n)$。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
int n,cnt,cntt,h[100005],root[100005],ans[100005],d[100005],q,val[100005],cnttt,cntttt;
set<int> s[2000005];
map<string,int> mp;
struct TreeNode{
	int ls,rs,id;
}t[2000005];
struct Edge{
	int to,next;
}e[100005];
struct Que{
	int k,id;
};
vector<Que> vec[100005];
int NewNode(){
	return ++cntt;
}
void Add_Edge(int x,int y){
	e[++cnt].to=y;
	e[cnt].next=h[x];
	h[x]=cnt;
}
void Update(int &p,int l,int r,int x,int y){
	if(!p)p=NewNode();
	if(l==r){
		if(!t[p].id)t[p].id=++cntttt;
		s[t[p].id].insert(y);
		return ;
	}
	int mid=(l+r)/2;
	if(x<=mid)Update(t[p].ls,l,mid,x,y);
	else Update(t[p].rs,mid+1,r,x,y);
}
void Merge(int &p,int q,int l,int r){
	if(!p||!q){
		p=p+q;
		return ;
	}
	if(l==r){
		if(!t[p].id)t[p].id=t[q].id;
		else {
			if(s[t[p].id].size()<s[t[q].id].size())swap(t[p].id,t[q].id);
			for(set<int>::iterator it=s[t[q].id].begin();it!=s[t[q].id].end();it++)s[t[p].id].insert(*it);
			s[t[q].id].clear();
		}
		return ;
	}
	int mid=(l+r)/2;
	Merge(t[p].ls,t[q].ls,l,mid);
	Merge(t[p].rs,t[q].rs,mid+1,r);
}
int Query(int p,int l,int r,int x){
	if(l==r)return s[t[p].id].size();
	int mid=(l+r)/2;
	if(x<=mid)return Query(t[p].ls,l,mid,x);
	else return Query(t[p].rs,mid+1,r,x);
}
void Solve(int now,int fa){
	Update(root[now],1,n,d[now],val[now]);
	for(int i=h[now];i;i=e[i].next){
		int y=e[i].to;
		if(y==fa)continue;
		Solve(y,now);
		Merge(root[now],root[y],1,n);
	}
	for(Que y:vec[now])ans[y.id]=Query(root[now],1,n,y.k);
}
void DFS(int now,int dep){
	d[now]=dep;
	for(int i=h[now];i;i=e[i].next){
		int y=e[i].to;
		DFS(y,dep+1);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++){
		string str;
		cin>>str;
		if(!mp[str])val[i]=mp[str]=++cnttt;
		else val[i]=mp[str];
		scanf("%d",&x);
		Add_Edge(x,i);
	}
	scanf("%d",&q);
	DFS(0,0);
	for(int i=1,x,k;i<=q;i++){
		scanf("%d%d",&x,&k);
		if(d[x]+k<=n)vec[x].push_back({d[x]+k,i});
	}
	Solve(0,0);
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：peterwuyihong (赞：7)

题意：给定一片森林，每个点有一个字符串，每次询问一个 $x$ 点，计算 $dep$ 是  $dep_x+y$ 的点上的不同字符串个数。

尝试跑树上 $\text{dsu}$。

你用 $n$ 个 $\text{vector}$，塞入所有询问的 $y$。$\text{dsu}$ 时，开 $n$ 个 $\text{set}$，表示深度为 $i$ 的当前节点的状态。（

可能说的有点迷惑，就简要说一下流程。

```
扩展(x)：
  if(set[dep[x]].count(a[x]))return
  set[dep[x]].insert(a[x]);
增加贡献(x):
  扩展(x)
  增加贡献(所有儿子）
清空(x):
  set[dep[x]].clear()
  清空(所有儿子)
蒂艾斯油(x):
  处理轻儿子
  清空轻儿子
  处理重儿子
  增加轻儿子的贡献
  增加自己的贡献
  回答问题:
    第i个问题答案是set[dep].size()
```

我觉得挺好写啊！

```cpp
#define maxn 100010
int n,x,y,m;
string a[maxn];
vector<pair<int,int>>v[maxn];
int head[maxn],Next[maxn],ver[maxn],tot;
void add(int x,int y){
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}
int dep[maxn],son[maxn],siz[maxn];
void dfs(int x){
	siz[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		dep[y]=dep[x]+1;
		dfs(y);
		siz[x]+=siz[y];
		if(siz[son[x]]<siz[y])son[x]=y;
	}
}
set<string>S[maxn*2];
int Ans[maxn];
void del(int x){
	S[dep[x]].clear();
	for(int i=head[x];i;i=Next[i])del(ver[i]);
}
void upd(int x){
	S[dep[x]].insert(a[x]);
}
void add(int x){
	upd(x);
	for(int i=head[x];i;i=Next[i])add(ver[i]);
}
int vis[maxn];
void dsu(int x){
	vis[x]=1;
	for(int i=head[x];i;i=Next[i])
	if(ver[i]!=son[x])dsu(ver[i]),del(ver[i]);
	if(son[x])dsu(son[x]);
	for(int i=head[x];i;i=Next[i])
	if(ver[i]!=son[x])add(ver[i]);
	upd(x);
	for(auto i:v[x])Ans[i.second]=S[i.first].size();
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>x;
		if(x)add(x,i);
	}
	for(int i=1;i<=n;i++)
		if(!dep[i])dep[i]=1,dfs(i);
	cin>>m;
	for(int i=1;i<=m;i++)cin>>x>>y,v[x].push_back(make_pair(y+dep[x],i));
	for(int i=1;i<=n;i++)if(!vis[i])dsu(i),del(i);
	for(int i=1;i<=m;i++)cout<<Ans[i]<<endl;
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
我去，被埋伏到了，居然是个森林。。

---

## 作者：JK_LOVER (赞：5)

# 分析
考虑如何维护一个节点的 $\text{K-son}$ ，这里采用树上启发式合并来维护一个节点的子树。然后对于相同深度的节点，我们维护一个 $\text{set}$ ，这样就免去了去重。而树上启发式合并的时间复杂度为 $O(n\log n)$ 。加上 $\text{set}$ 总的复杂度就为 $O(n\log^2n)$ 。所以要记得关闭流同步。[$QAQ$](https://www.luogu.com.cn/blog/xzc/solution-cf246e)
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 100;
int son[N],dep[N],L[N],id[N],R[N],Id,si[N];
int val[N],fa[N],MaxDep,n,m,top,ans[N];
unordered_map<string,int> Map;
vector<int> G[N];
set<int> cnt[N];
struct query{int id,k;};
vector<query> Q[N];
void dfs(int x,int Dep) {
	dep[x] = Dep;si[x] = 1;;id[L[x] = ++Id] = x;
	MaxDep = max(MaxDep,Dep);
	for(auto y:G[x]) {
		if(y == fa[x]) continue;
		dfs(y,Dep+1);
		si[x] += si[y];if(si[son[x]] < si[y]) son[x] = y;
	}
	R[x] = Id;
}
void solve(int x,int keep) {
	for(auto y:G[x]) {if(y == fa[x] || y == son[x]) continue;solve(y,0);}
	if(son[x]) solve(son[x],1);
	for(auto y:G[x]) {
		if(y == fa[x] || y == son[x]) continue;
		for(int i = L[y];i <= R[y];i++) {
//			cout << i <<" "<<id[i] <<endl;
			int u = id[i];
//			cout <<"insert:: "<<u<<"  "<<val[u] << endl;
			cnt[dep[u]].insert(val[u]);
		}
	}
	cnt[dep[x]].insert(val[x]);
	for(auto Ans:Q[x]) {
		int nxt = Ans.k + dep[x];
		ans[Ans.id] = cnt[nxt].size();
	}
	if(keep) return;
	for(int i = 1;i <= MaxDep;i++) cnt[i].clear();
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for(int i = 1;i <= n;i++) {
		string A;cin >> A >> fa[i];
		if(!Map[A]) Map[A] = ++top;
		val[i] = Map[A];//cout << val[i] << endl;
		if(fa[i]) G[fa[i]].push_back(i);
		if(fa[i]) G[i].push_back(fa[i]);
	}
	for(int i = 1;i <= n;i++) {if(!fa[i]) dfs(i,1);}
	cin >> m;
	for(int i = 1,x,y;i <= m;i++) {
		cin >> x >> y;
		Q[x].push_back((query){i,y});
	}
	for(int i = 1;i <= n;i++) {if(!fa[i]) solve(i,0);}
	for(int i = 1;i <= m;i++) cout << ans[i] << endl;
	return 0;
}
```


---

## 作者：封禁用户 (赞：4)

## 前言

感谢 @zhengdongwen 大佬给予我的非常关键的帮助（拜谢）。

## 分析

考虑莫队。

对于这道题，我们可以想到 DFS 序。定义 $\mathit{siz}_{i}$ 表示在以 $i$ 为根的子树中的节点数量。若有节点 $x$ 在 DFS 序的位置为 $\mathit{where}_{x}$，则其子树中的节点将会完全分布在 $\mathit{where}_{x}$ 到 $\mathit{where}_{x}+\mathit{siz}_{x}-1$ 中。这样，对于一个问题：求以 $x$ 为根的子树中深度比 $x$ 大 $y$ 的所有节点不同名字的数量。就变成了：在 DFS 序中，求区间 $[\mathit{where}_{x},\mathit{where}_{x}+\mathit{siz}_{x}-1]$ 里所有对应节点的深度比 $x$ 大 $y$ 的不同名字数量。

这是一个区间问题，直接用莫队维护。定义 $\mathit{cnt}_{i,j}$ 表示在当前指针范围内，深度为 $i$，名字为 $j$ 的节点数量。和 P1972 相同，统计一下每一个深度的名字不同数量，记为 $\mathit{many}_{i}$。则答案就是 $\mathit{many}_{depth_x+y}$。

注：我们需要使用类似于 map 的容器存放 $\mathit{cnt}_{i,j}$，以确保不会 MLE。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
#define re register
#define il inline 
const int N=1e6+10;
int n,q;
string name[N];

//dfs序 ↓ 
int ne[N],e[N],h[N],idx;
int fi[N],dfsx[N],cnt,dep[N];//fi[i]：节点i在dfs序中出现的下标 
int siz[N];
il void add(int a,int b){
	ne[++idx]=h[a],e[idx]=b,h[a]=idx;
    return ;
}
il void dfs(int now,int fa){
	dep[now]=dep[fa]+1,dfsx[++cnt]=now,fi[now]=cnt;
	siz[now]=1;
	for(int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dfs(j,now),siz[now]+=siz[j];
	}
    return ;
}
//dfs序 ↑ 

//输入 ↓
struct node{
	int l,r,dep,id;//dep存放dep[x]+y 
}Q[N];
il void read(){	
	scanf("%lld",&n); 
	int idex=0;
	for(int i=1;i<=n;i++){ 
		int x; cin>>name[i];scanf("%lld",&x);
		add(x,i),add(i,x);
	}
	dfs(0,-1); scanf("%lld",&q); 
	for(int i=1;i<=q;i++){
		int x,y;scanf("%lld%lld",&x,&y);
		Q[i]={fi[x],fi[x]+siz[x]-1,dep[x]+y,i};
	}
    return ;	
}
//输入 ↑ 

//莫队 ↓ 
int len,ANS[N];
int many[N];
unordered_map<int,unordered_map<string,int>> h_m;
bool cmp(node a,node b){
	if(a.l/len!=b.l/len) return a.l<b.l;
	if((a.l/len)&1) return a.r<b.r;
	return a.r>b.r;
}
void add1(int x){
	h_m[dep[x]][name[x]]++;
	if(h_m[dep[x]][name[x]]==1) 
		many[dep[x]]++;
	return ;
}
void del1(int x){
	h_m[dep[x]][name[x]]--;
	if(h_m[dep[x]][name[x]]==0)
		many[dep[x]]--;
	return ;
}
void solve(){
	len=sqrt(n),sort(Q+1,Q+q+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=q;i++){
		while(l>Q[i].l) add1(dfsx[--l]);
		while(r<Q[i].r) add1(dfsx[++r]);
		while(l<Q[i].l) del1(dfsx[l++]);
		while(r>Q[i].r) del1(dfsx[r--]);
		ANS[Q[i].id]=many[Q[i].dep];
	}
	return ;
}
//莫队 ↑ 

void print(){
	for(int i=1;i<=q;i++)
		printf("%lld\n",ANS[i]); 
    return ;
}
signed main(){
	read(),solve(),print();return 0;
}
```


---

## 作者：Albedo (赞：3)

## $ \texttt{Introduction} $

树上 $ \text{dsu} $ 例题。

## $ \texttt{Solution} $ 

首先将森林的问题解决好，就是把 $ 0 $ 也当做一个点，那么就解决了。

首先树上 $ \text{dsu} $ 的前提是要做出 $ O(n^2) $ 的暴力，而且这个暴力只与子树的答案有关。

如何暴力的最关键的一点就是对于一个点 $ x $ ，他的 $ \text{K-son} $ 有多少的不同的值，而且没有任何区间，就是一整个 $ \text{K-son} $，而我们平时碰到的东西什么东西不满足可重性。那就是集合，所以我们可以使用 $ \text{set} $ 去维护这样子的一个东西。

我们假设 $ val[x] $ 表示当前子树下深度为 $ x $ 的节点有多少个不同的数，那么每次加入一个点，我们就判断他有没有在集合中，如果他在，那么不加入，否则直接加入，到现在，我们的暴力已经完成，现在的问题就是如何把这个暴力转换成树上 $ \text{dsu} $。

这个就十分套路了，我们发现以其他儿子为根的子树的贡献是不要的，所以直接 $ \text{set} $ 清空就好了，加点还是暴力的加点。

## $ \texttt{Code} $

```c++
#include<bits/stdc++.h>
using namespace std;
//build1:find depth,father,size,height_son 
//build2:find height_son's top and height_son's id
struct node{
	int col,top,fa,siz,hson,dep;
} E[510100];
set<int> Set[201010];
int col[1001010],up[1001010],Answer[1001010],opt,H[1010100],dfn[1010100],e[1010100],a[1010100],b[1010100],d[1010100],ans;
int len,u,v,cnt,n,m,i,T,x,y,id;
bool exist[1010100];
string lsh[1001010],Strin[100100];
int Testing;
vector<pair<int,int>> Asking[101000];
void add(int x,int y)
{
	cnt++;a[cnt]=y;b[cnt]=d[x];d[x]=cnt;
}
void build1(int x,int fa)
{
	id++;dfn[x]=id;
	E[x].siz=1;int mx=0;E[x].hson=0;
	for (int i=d[x];i;i=b[i])
	   if (a[i]!=fa)
	     {
	     	E[a[i]].dep=E[x].dep+1;
            E[a[i]].fa=x;build1(a[i],x);E[x].siz+=E[a[i]].siz; 
			if (E[a[i]].siz>mx) mx=E[a[i]].siz,E[x].hson=a[i];    	
		 }
	if (E[x].hson!=0) exist[E[x].hson]=true;
}
void delet(int x)
{
	//cout<<"-----"<<x<<"-----\n";
	for (int i=dfn[x];i<=dfn[x]+E[x].siz-1;i++)
	      Set[E[H[i]].dep].clear();
}
void insert(int x,int fa)
{
	for (int i=dfn[x];i<=dfn[x]+E[x].siz-1;i++)
	      Set[E[H[i]].dep].insert(E[H[i]].col);
}
void sc(int x,int fa)
{
	int i;
	for (i=d[x];i;i=b[i])
	     if (a[i]!=fa)
	         if (a[i]!=E[x].hson)
	            {
	            sc(a[i],x);
	            delet(a[i]);
	            }
	if (E[x].hson!=0)
	    {
	     sc(E[x].hson,x);
	     //cout<<"---"<<x<<"---:"<<Answer[x]<<endl;
    	for (i=d[x];i;i=b[i])
	     if (a[i]!=fa)
	         if (a[i]!=E[x].hson)
	            insert(a[i],x);
	   }
	Set[E[x].dep].insert(E[x].col);
	for (i=0;i<Asking[x].size();i++)
	    Answer[Asking[x][i].second]=Set[E[x].dep+Asking[x][i].first].size();
}
int main()
{
	ios::sync_with_stdio(0);cin.tie();cout.tie();
	char s[1010];
	cin>>n;
	for (i=1;i<=n;i++) 
	    {
	    	cin>>Strin[i]>>x;
	    	lsh[i]=Strin[i];
	    	if (x==0) x=n+1;
	    	add(x,i);
		 } 
	sort(lsh+1,lsh+n+1);len=unique(lsh+1,lsh+n+1)-lsh-1;
	for (i=1;i<=n;i++) E[i].col=lower_bound(lsh+1,lsh+len+1,Strin[i])-lsh;
	E[n+1].dep=1;build1(n+1,0);
	for (i=1;i<=n+1;i++) H[dfn[i]]=i;
	cin>>Testing; 
	for (i=1;i<=Testing;i++)
	   { 
	     cin>>x>>y;
	      Asking[x].push_back(make_pair(y,i));
	   }
	sc(n+1,0);
	for (i=1;i<=Testing;i++) cout<<Answer[i]<<endl;
 return 0;
}
```



---

## 作者：legendgod (赞：3)

毕竟是刚学线段树合并，可能会讲得稍微细一点。

### [CF246E Blood Cousins Return](https://www.luogu.com.cn/problem/CF246E)

翻译

> 给定一片森林，询问每个节点 $v$，其深度为 $k$ 的儿子中不同的名字个数。

输入格式
> n 个节点，每个节点的名字和父亲, 之后是 $q$ 个询问，每行输入 v 和 k。

~~话说因为英语差，看了翻译好久。~~


首先我们考虑假设没有相同名字，我们可以直接使用线段树合并，通过权值线段树记录每一个深度，因为 $depmax \le n$ 显然可行。

> 之前想的时候总有一个问题，就是线段树具体维护深度是全局的深度还是相对深度，其实仔细想过之后就可以发现，肯定是维护全局深度，因为这样合并的时候就可以做到 $O(1)$ 的复杂度。

之后我们考虑对于每一个名字，我们可以先判重，再赋予一个新的编号，这样做线段树合并的时候貌似会简单一点，关键看是怎么判重的。

之后我们考虑对于每一个节点运用 set 进行维护和判重。可以发现合并的时候是两个 set 暴力合并的，所以我们可以将小的合并到大的里面去来减小复杂度。

之后还有一个细节，开大 tree 数组的时候，别忘记将判重的数组也开大。

----
$Code$

```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c);c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}

const int maxn = 1e5 + 5;
const int maxm = maxn << 1;

typedef int room[maxn];

int n, m;
map<string, int> vis;
int num(0), v[maxn];
int dep[maxn];
struct Node {
	int l, r, id;
}t[maxn * 21];
int stlen(0);
set<int> st[maxn * 21];
struct Seg {
	int tot;
	Seg() : tot(0) {}
	#define mid ((l + r) >> 1)
	void Insert(int &p,int l,int r,int pos,int v) {
		if(!p) p = ++ tot;
		if(l == r) return !t[p].id ? t[p].id = ++ stlen : 0, st[t[p].id].insert(v), void();
		if(pos <= mid) Insert(t[p].l, l, mid, pos, v);
		else Insert(t[p].r, mid + 1, r, pos, v);
	}
	void merge(int &p,int v,int l,int r) {
		if(!p || !v) return p = p + v, void();
		if(l == r) {
			if(!t[p].id) t[p].id = ++ stlen;
			else {
				if(st[t[p].id].size() < st[t[v].id].size()) swap(st[t[p].id], st[t[v].id]);
				for(set<int> :: iterator it = st[t[v].id].begin(); it != st[t[v].id].end(); ++ it)
					st[t[p].id].insert(*it);
				st[t[v].id].clear();
			}
			return ;
		}
		merge(t[p].l, t[v].l, l, mid), merge(t[p].r, t[v].r, mid +1 , r);
 	}
 	int ask(int p,int l,int r,int pos) {
 		if(!p) return 0;
 		if(l == r) return st[t[p].id].size();
 		if(pos <= mid) return ask(t[p].l, l, mid, pos);
 		else return ask(t[p].r, mid + 1, r, pos);
	 }
}T;
struct Edge {
	int to, next;
}edg[maxn << 1];
int head[maxn], cnt;
void add(int u, int v) {
	edg[++ cnt] = (Edge) {v, head[u]}, head[u] = cnt;
}
struct Query {
	int dep, id;
	Query(int a,int b) : dep(a), id(b) {}
};
vector<Query> vc[maxn];
int ans[maxn];
int rt[maxn];
void dfs(int p,int f) {
//	dep[p] = dep[f] + 1;
	T.Insert(rt[p], 1, n, dep[p], v[p]);
	for(int i = head[p];i;i = edg[i].next) {
		int to = edg[i].to;
		if(to == f) continue;
		dfs(to, p);
		T.merge(rt[p], rt[to], 1, n);
	}
	for(vector<Query> :: iterator it = vc[p].begin(); it != vc[p].end(); ++ it)
		ans[it->id] = T.ask(rt[p], 1, n, it->dep);
}

void dfs1(int p,int dep1,int f) {
    dep[p] = dep1;
    for(int i = head[p];i;i = edg[i].next) {
        int to = edg[i].to;
        if(to == f) continue;
        dfs1(to, dep1 + 1, p);
    }
}


signed main() {
	int i, j;
	r1(n);
	for(i = 1;i <= n; ++ i) {
		int x;
		string s;
		cin >> s;
		r1(x);
		if(vis[s]) v[i] = vis[s];
		else vis[s] = v[i] = ++ num;
		add(x, i);
	}
	r1(m);
	dfs1(0, 0, 0);
	for(i = 1;i <= m; ++ i) {
		int x, k;
		r1(x), r1(k);
		if(dep[x] + k <= n)
		vc[x].push_back(Query(dep[x] + k, i));
	}
	dfs(0, 0);
	for(i = 1; i <= m; ++ i) printf("%d\n", ans[i]);
	return 0;
}


```


---

## 作者：p_b_p_b (赞：3)

广告：我的[树上启发式合并总结](https://blog.csdn.net/pb122401/article/details/84648993)

又是一道$DSU\; on\; Tree$模板题，但存储方式由数组升级为map（其实也没有升级多少）

开一个`map<string,int>cnt[sz]`记录当前每个深度里每个字符串出现的次数，再用`sum[sz]`记录每个深度当前答案即可

复杂度应该是$O(nlog^2n)$吧……胡乱分析$ing$

代码：

```cpp
#include<bits/stdc++.h>
#define sz 1000020
#define mod 998244353
using namespace std;
typedef long long ll;
int n;
struct hh{int t,nxt;}edge[sz<<1];
int head[sz],ecnt;
void make_edge(int f,int t)
{
	edge[++ecnt]=(hh){t,head[f]};
	head[f]=ecnt;
	edge[++ecnt]=(hh){f,head[t]};
	head[t]=ecnt;
}
#define go(x) for (int i=head[x];i;i=edge[i].nxt)
#define v edge[i].t
int dep[sz],size[sz],son[sz],fa[sz];
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;size[x]=1;
	go(x) if (v!=fa)
	{
		dfs1(v,x);
		size[x]+=size[v];
		if (size[v]>size[son[x]]) son[x]=v;
	}
}
map<string,int>S[sz];
int sum[sz];
string a[sz];
bool s[sz];
void add(string s,int d,int t)
{
	if (!S[d][s]) ++sum[d];
	S[d][s]+=t;
	if (!S[d][s]) --sum[d];
}
void add(int x,int fa,int t)
{
	add(a[x],dep[x],t);
	go(x) if (v!=fa&&!s[v]) add(v,x,t);
}
#define pii pair<int,int>
#define MP make_pair
#define fir first
#define sec second
vector<pii>q[sz];
int ans[sz];
void dfs2(int x,int fa,bool keep)
{
	go(x) if (v!=fa&&v!=son[x]) dfs2(v,x,0);
	s[son[x]]=1;
	if (son[x]) dfs2(son[x],x,1);
	add(x,fa,1);
	for (int i=0;i<(int)q[x].size();i++) ans[q[x][i].fir]=sum[q[x][i].sec];
	s[son[x]]=0;
	if (!keep) add(x,fa,-1); 
}
int main()
{
	ios::sync_with_stdio(false);
	int i,x,y,m;
	cin>>n;
	for (i=1;i<=n;i++) { cin>>a[i]>>fa[i]; if (fa[i]) make_edge(fa[i],i); }
	for (i=1;i<=n;i++) if (!fa[i]) dfs1(i,0);
	cin>>m;
	for (i=1;i<=m;i++)
	{
		cin>>x>>y;
		q[x].push_back(MP(i,dep[x]+y));
	}
	for (i=1;i<=n;i++) if (!fa[i]) dfs2(i,0,0);
	for (i=1;i<=m;i++) printf("%d\n",ans[i]);
}
```

---

## 作者：Farkas_W (赞：2)

$$\text{CF246E Blood Cousins Return}$$

$\quad$题目链接：[CF246E Blood Cousins Return](https://www.luogu.com.cn/problem/CF246E)(洛谷的链接)

$\quad$一道 $Dcu$ 模板题(下面会讲)，只需要用一个 $map$ 数组来维护这个名字(字符串)是否出现过，用 $set$ 也可以，貌似会慢一些，用 $cnt$ 数组来维护每一层的不同名字的数量即可，因为是一个森林，所以记得要清空数组。

### 一个大坑点：
$\quad$ $WA$第 $50$ 个点的注意了，在储存询问时一定要判断询问这个第 $k$ 级儿子的深度是否超过了 $10^5$ ，因为最多只有 $10^5$ 个点，如果超过就不用存储，答案一定是 $0$ ，存储的话会溢出数组，遇到一些毒瘤数据就会WA。

$\quad$下面就简单讲讲树上启发式合并 ($DSU$ $on$ $Tree$)算法，如果有不懂的可以提出来。

$$\text{关于树上启发式合并(Lsu)前置知识}$$

$\quad$学这个之前需要对树上操作、 $dfs$ 序和轻重链剖分等知识有一定了解，最好已经掌握了树链剖分。

$$\text{算法思想}$$

$\quad$树上启发式合并 ($DSU$ $on$ $Tree$)，是一个在 $O(nlogn)$ 时间内解决许多树上问题的有力算法，对于某些树上离线问题可以速度大于等于大部分算法且更易于理解和实现。

$\quad$先想一下暴力算法，对于每一次询问都遍历整棵子树，然后统计答案，最后再清空cnt数组，最坏情况是时间复杂度为 $O(n^2)$ ，对于 $10^5$ 的数据肯定是过不去的。

$\quad$现在考虑优化算法，暴力算法跑得慢的原因就是多次遍历，多次清空数组，一个显然的优化就是将询问同一个子树的询问放在一起处理，但这样还是没有处理到关键，最坏情况时间复杂度还是 $O(n^2)$ ，考虑到询问 $x$ 节点时， $x$ 的子树对答案有贡献，所以可以不用清空数组，先统计 $x$ 的子树中的答案，再统计 $x$ 的答案，这样就需要提前处理好 $dfs$ 序。

$\quad$然后我们可以考虑一个优化，遍历到最后一个子树时是不用清空的，因为它不会产生对其他节点影响了，根据贪心的思想我们当然要把节点数最多的子树（即重儿子形成的子树）放在最后，之后我们就有了一个看似比较快的算法，先遍历所有的轻儿子节点形成的子树，统计答案但是不保留数据，然后遍历重儿子，统计答案并且保留数据，最后再遍历轻儿子以及父节点，合并重儿子统计过的答案。

$\quad$其实树上启发式合并的基本思路就是这样，可以看一下代码理解。

```
il int check(int x)//统计答案
{
  int num=0,ret=0;
  for(re i=1;i<=n;i++)
    {
      if(cnt[i]==num){ret+=i;}
      else if(cnt[i]>num){num=cnt[i],ret=i;}
    }
  return ret;
}
il void add(int x){cnt[col[x]]++;}//单点增加
il void del(int x){cnt[col[x]]--;}//单点减少
il void raise(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)add(rev[i]);}//增加x子树的贡献
il void clear(int x){for(re i=seg[x];i<=seg[x]+size[x]-1;i++)del(rev[i]);}//清空x子树的贡献
il void dfs1(int x,int fa)
{
  dep[x]=dep[fa]+1;father[x]=fa;//处理深度，父亲
  seg[x]=++seg[0];rev[seg[x]]=x;size[x]=1;//子树大小，dfs序
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==fa)continue;dfs1(y,x);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;//重儿子
    }
}
il void dfs2(int x,int flag)//flag表示是否为重儿子，1表示重儿子，0表示轻儿子
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x]||y==father[x])continue;
      dfs2(y,0);//先遍历轻儿子
    }
  if(son[x])dfs2(son[x],1);//再遍历重儿子
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x]||y==father[x])continue;
      raise(y);//更新轻儿子的贡献
    }add(x);//加上x结点本身的贡献
  ans[x]=check(x);//更新答案
  if(!flag)clear(x);//如果是轻儿子，就清空
}
```
$\quad$上面的只是模板的代码，此题的完整代码在下面。(附带注释)

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
#define re register int
#define int long long
#define LL long long
#define il inline
#define next nee
#define inf 1e18
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=1e5+5;
int n,m,next[N],go[N],head[N],tot,father[N],ans[N];
int dep[N],son[N],seg[N],rev[N],size[N],cnt[N];
struct node{int k,id;};
string s[N]; 
vector<node>q[N];
map<string,bool>c[N];

il void Add(int x,int y)
{
  next[++tot]=head[x];
  head[x]=tot;go[tot]=y;
}
il void add(int x)//单点增加
{
  if(!c[dep[x]][s[x]])c[dep[x]][s[x]]=1,cnt[dep[x]]++;
}
il void raise(int x)//算上x子树的贡献
{
  for(re i=seg[x];i<=seg[x]+size[x]-1;i++)add(rev[i]);
}
il void del(int x)//单点减少
{
  c[dep[x]].clear();
  cnt[dep[x]]=0;
}
il void clear(int x)//清空x子树
{
  for(re i=seg[x];i<=seg[x]+size[x]-1;i++)
    del(rev[i]);
}
il void dfs1(int x,int fa)
{
  dep[x]=dep[fa]+1;size[x]=1;seg[x]=++seg[0];rev[seg[x]]=x;
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      dfs1(y,x);size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;
    }
}
il void dfs2(int x,int flag)
{
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==son[x])continue;
      dfs2(y,0);//先遍历轻儿子
    }
  if(son[x])dfs2(son[x],1);//再遍历重儿子
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {if(y==son[x])continue;raise(y);}//更新轻儿子的贡献
  add(x);//加上x结点本身的贡献
  for(re i=0;i<q[x].size();i++)
    ans[q[x][i].id]=cnt[dep[x]+q[x][i].k];//更新答案
  if(!flag)clear(x);//如果是轻儿子，就清空
}
signed main()
{
  n=read();
  for(re i=1,x;i<=n;i++)cin>>s[i],x=read(),father[i]=x,Add(x,i);
  for(re i=1;i<=n;i++)if(!father[i])dfs1(i,0);//预处理，倍增数组、dfs序等树上信息,记得要用循环，从每棵树的根节点出发
  m=read();
  for(re i=1,x,y;i<=m;i++)
    {
      x=read(),y=read();
      if(dep[x]+y>=N)continue;//注意，如果询问的第K级儿子超过限制，不能存储，原因上面有
      q[x].push_back((node){y,i});
    }
  for(re i=1;i<=n;i++)if(!father[i])dfs2(i,0);//找每棵树的根节点，0表示轻儿子，这样不用手动清空数组
  for(re i=1;i<=m;i++)print(ans[i]),putchar('\n');
  return 0;
}
```

---

## 作者：Azazеl (赞：2)

### CF246E Blood Cousins Return

#### 题意

（我觉得翻译挺简洁的就不自己概括了）

> $~~~~$ 给定一片森林，每次询问一个节点的K-Son共有个多少不同的名字。一个节点的K-Son即为深度是该节点深度加K的节点。

---

#### 题解  

$~~~~$ 可以想到一道~~名字和~~内容和它很相似的题[CF246E](https://www.luogu.com.cn/problem/CF246E "求k级祖先的k级儿子个数") ，那道题分成两个部分，其中一部分就是求 $k$ 级儿子的个数，直接用 Dsu on tree 即可，具体来说，每次维护每个节点子树内不同深度的点的个数即可。  

$~~~~$ 这题不大一样，需要计算的是种类数而不是个数，但换个角度思考，我们可以把种类数看作去重过后的个数，那我们的 `cnt` 就要能够去重并且计算元素个数。  

$~~~~$ ~~直接一个 STL `set` 甩上去当`cnt`就行了.~~

$~~~~$ 现在的需求类似于 [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)，只是这是区间问题，那我们是不是可以尝试把这个树上的问题搞下来，变成区间的问题呢？  

$~~~~$ 当然可以！我们考虑到每个询问的对应区间深度一致，那就可以变成记录每个询问的区间深度，在 dfs序上两个端点的值，按深度排序后一次按深度对形成的区间求解即可。  

$~~~~$ 至于这个求解，理论上是要用 BIT 的，不会的话可以去看一下原题。但不知道 莫队 能不能卡过去awa.

---

## 作者：yukimianyan (赞：1)

## 题目描述

给定一片森林，每个点有一个名字（字符串）。每次查询一个节点的子树中离他距离为 $k$ 的点中有多少种不同的名字。$n, m\leq 10^5$。

## solution

将所有名字离散化。考虑在算答案的时候，我们钦定同一种颜色只有 bfs 序最小的才能被计算。对于每个点，找出与它深度相同的，bfs 序在他前面的，颜色也与它相同的点。求出这两个点的 LCA，然后在这个点本身的这个深度上打一个 $+1$ 标记，在 LCA 处的这个深度上打一个 $-1$ 标记，表示在 LCA 处颜色出现了重复，减去自己，用前面与它颜色相同的点为这个颜色的代表进行计算。然后做长链剖分即可。

如果用线性的 LCA 算法，并忽略离散化部分，那么时间复杂度为 $O(n)$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
#define debug(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define endl "\n"
#define debug(...) void(0)
#endif
using LL = long long;
constexpr int N = 1e5 + 10;
int n, col[N], fa[N], st[20][N], cnt, dfn[N], dep[N], hei[N], son[N], rnk[N];
map<string, int> mp;
basic_string<int> g[N];
bool cmp(int u, int v) { return dfn[u] < dfn[v]; }
void dfs0(int u) {
  son[u] = 0;
  for (int v : g[u]) dfs0(v), hei[v] > hei[son[u]] && (son[u] = v);
  hei[u] = hei[son[u]] + 1;
}
void dfs(int u) {
  dfn[u] = ++cnt, st[0][cnt] = fa[u], dep[u] = dep[fa[u]] + 1, rnk[cnt] = u;
  if (son[u]) dfs(son[u]);
  for (int v : g[u]) if (v != son[u]) dfs(v);
}
int lca(int u, int v) {
  if (u == v) return u;
  auto [l, r] = minmax(dfn[u], dfn[v]);
  int k = __lg(r - l);
  return min(st[k][l + 1], st[k][r - (1 << k) + 1], cmp);
}
basic_string<int> des[N];
int main() {
#ifndef LOCAL
  cin.tie(nullptr)->sync_with_stdio(false);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s >> fa[i];
    if (!mp.count(s)) mp.emplace(s, mp.size());
    col[i] = mp[s];
    g[fa[i]] += i;
  }
  dfs0(0);
  dfs(0);
  for (int j = 1; j < 20; j++) {
    for (int i = 1; i + (1 << j) - 1 <= cnt; i++) {
      st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
  }
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    static int lst[N];
    int p = exchange(lst[col[u]], u);
    if (p && dep[p] == dep[u]) des[lca(u, p)] += dep[u];
    for (int v : g[u]) q.push(v);
  }
  static int f[N], fans[N];
  static vector<pair<int, int>> qry[N];
  int m;
  cin >> m;
  for (int i = 1, u, k; i <= m; i++) cin >> u >> k, qry[u].emplace_back(k, i);
  for (int j = cnt; j >= 1; j--) {
    int u = rnk[j];
    for (int v : g[u]) if (v != son[u]) {
      for (int i = 0; i < hei[v]; i++) f[dfn[u] + i + 1] += f[dfn[v] + i];
    }
    f[dfn[u]] += 1;
    for (int d : des[u]) f[dfn[u] + d - dep[u]] -= 1;
    for (auto [k, id] : qry[u]) if (k < hei[u]) fans[id] = f[dfn[u] + k];
  }
  for (int i = 1; i <= m; i++) cout << fans[i] << endl;
  return 0;
}
```

---

## 作者：Alkaid_Star (赞：1)


Updated On 2021.10.20：修改了部分 $\LaTeX$。

### 题目大意

> 给你一片 $n$ 个点的森林，每个点有一个字符串作为名字。
>
> 有 $m$ 次询问，每次询问一个点 $v_i$ 有多少个不同的名字的 $k_i$ 级儿子。
>
> （一个节点的 $k$ 级儿子即为深度是该节点深度加 $k$ 的儿子节点。）
>
> $1 \le n,m \le 10^5, 1 \le v_i,k_i \le n$。

### 解题思路

啊这道题名字叫 `Blood Cousins Return`，而之前的 `CF208E` 叫 `Blood Cousins`，可以猜想这两题肯定是有关系的（确信）。

事实上还真的有关系，不过关系不大。不会 `CF208E` 的可以去看[我的博客](https://www.encounter.cool/index.php/2021/10/19/cf208e-solution/)。

跟深度有关的问题，线段树合并几乎是万能的。考虑线段树合并，我们只要在每个线段树节点上开个 `std::set` ，维护深度为当前线段树节点代表区间 $l \sim r$ 的点的名字放在一起，再去重后的结果。每次合并线段树节点的时候直接把 $size$ 小的 `set` 合并到 $size$ 大的 `set` 上，大概是叫做 `set` 的启发式合并？

考虑证明复杂度。

我们考虑类似于轻重链剖分的思想，每个点离开自己 `set` 被合并到其他 `set` 的次数一定不超过 $O(\log⁡n)$ 次，因为每次这么做，`set` 的 $siz$ 至少乘 $2$ 。而在 $siz$ 大的 `set` 里是直接继承的。加上 `set` 本身平衡树的复杂度，所以总复杂度是 $O(n \log^2⁡ n)$ 的。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005,LogN=20;

bool St;

struct Edge{
	int vet,nxt;
}e[N<<1];

struct Ques{
	int val,ord;
};

struct Node{
	int lson,rson;
	set <int> s;
}tree[N*LogN];

int n,m,edge=0,logN=0,head[N];
int fa[N],dep[N],name[N];
int ans[N],rt[N],cntNode=0,cntMap=0;
bool isrt[N];
vector <Ques> q[N];
map <string,int> Map;

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)){ if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

inline void addedge(int x,int y){
	e[++edge].vet=y;
	e[edge].nxt=head[x];
	head[x]=edge;
}

inline void dfs(int x,int fath){
	fa[x]=fath; dep[x]=dep[fath]+1;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].vet;
		if (v==fath) continue;
		dfs(v,x);
	}
}

#define lid (tree[id].lson)
#define rid (tree[id].rson)

void pushup(int id){
	if (tree[lid].s.size()>tree[rid].s.size()){
		tree[id].s=tree[lid].s;
		for (auto it : tree[rid].s)
			tree[id].s.insert(it);
	}
	else {
		tree[id].s=tree[rid].s;
		for (auto it : tree[lid].s)
			tree[id].s.insert(it);
	}
}

void Insert(int& id,int l,int r,int x,int val){
	if (!id) id=++cntNode;
	if (l==r){
		tree[id].s.insert(val);
		return void();
	}
	int mid=(l+r)>>1;
	if (x<=mid) Insert(lid,l,mid,x,val);
	else Insert(rid,mid+1,r,x,val);
	pushup(id);
}

int Mergeset(int x,int y){
	if (tree[x].s.size()>tree[y].s.size()){
		for (auto it : tree[y].s)
			tree[x].s.insert(it);
		return x;
	}
	else {
		for (auto it : tree[x].s)
			tree[y].s.insert(it);
		return y;
	}
}

int Merge(int x,int y,int l,int r){
	if (!x) return y;
	if (!y) return x;
	if (l==r) return Mergeset(x,y);
	int mid=(l+r)>>1;
	tree[x].lson=Merge(tree[x].lson,tree[y].lson,l,mid);
	tree[x].rson=Merge(tree[x].rson,tree[y].rson,mid+1,r);
	// pushup(x);
	return x;
}

int Query(int id,int l,int r,int val){
	if ((!id) || (l>r)) return 0;
	if (l==r) return tree[id].s.size();
	int mid=(l+r)>>1;
	if (val<=mid) return Query(lid,l,mid,val);
	else return Query(rid,mid+1,r,val);
}

inline void Dfs(int x,int fath){
	// printf("x=%d fath=%d dep[x]=%d\n",x,fath,dep[x]);
	rt[x]=++cntNode;
	Insert(rt[x],1,n+1,dep[x],name[x]);
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].vet;
		if (v==fath) continue;
		Dfs(v,x);
		rt[x]=Merge(rt[x],rt[v],1,n+1);
	}
	for (auto it : q[x])
		ans[it.ord]=Query(rt[x],1,n+1,it.val);
}

int main(){
	//freopen("CF246E.in","r",stdin);
	//freopen("CF246E.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n; logN=(int)(log2(n)+1);
	for (int i=1;i<=n;++i){
		int x; string str; cin>>str>>x;
		if (Map.find(str)==Map.end()) Map[str]=name[i]=++cntMap;
		else name[i]=Map[str];
		if (x==0){ isrt[i]=true; continue; }
		addedge(x,i);
		addedge(i,x);
	}
	cin>>m;
	for (int i=1;i<=n;++i)
		if (isrt[i]) dfs(i,0);
	for (int i=1;i<=m;++i){
		int x,y; cin>>x>>y;
		q[x].push_back((Ques){dep[x]+y,i});
	}
	for (int i=1;i<=n;++i)
		if (isrt[i]) Dfs(i,0);
	for (int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	bool Ed; cerr<<"MemoryUsed:"<<1.0*(&St-&Ed)/1024/1024<<endl;
	return 0;
}
```



---

## 作者：FutaRimeWoawaSete (赞：1)

我们考虑树上启发式合并，将所有名字都 Hash 处理一下，然后合并的时候用 map 存一下之前相同深度的点上出现过这个名字几次，即可知道当前加入的名字是否有贡献。               

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
const int K = 131;
long unsigned long Hash,Name[Len];
map<long unsigned long,int> mp[Len];
int n,m,head[Len],cnts,cnt[Len << 2],dep[Len],siz[Len],son[Len],dp[Len][30],Son,ans[Len];
bool vis[Len];
vector<int> root;
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnts].to = to;
	edge[cnts].next = head[from];
	head[from] = cnts;
}
struct Node
{
	int depth,idx;
};
vector<Node> G[Len];
void Add(int x,int val)
{
	if(val == 1) 
	{
		if(!mp[dep[x]][Name[x]]) cnt[dep[x]] ++;
		mp[dep[x]][Name[x]] ++;
	}
	else 
	{
		if(mp[dep[x]][Name[x]] == 1) cnt[dep[x]] --;
		mp[dep[x]][Name[x]] --;
	}
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == Son) continue;
		Add(to , val);
	}
}
void dfs1(int x,int f)
{
	dep[x] = dep[f] + 1;
	siz[x] = 1;
	dp[x][0] =  f;
	int maxson = -1;
	for(int i = 1 ; (1 << i) <= dep[x] ; i ++) dp[x][i] = dp[dp[x][i - 1]][i - 1];
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		dfs1(to , x);
		siz[x] += siz[to];
		if(maxson < siz[to]) maxson = siz[to] , son[x] = to;
	}
}
int Find(int x,int k)//爬树 
{
	for(int i = 20 ; i >= 0 ; i --) if((1 << i) <= k) k -= (1 << i) , x = dp[x][i];
	return x;
}
void dfs2(int x,int f,int opt)
{
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == son[x]) continue;
		dfs2(to , x , 0);
	}	
	if(son[x]) dfs2(son[x] , x , 1) , Son = son[x];
	Add(x , 1) , Son = 0;
	for(int e = 0 ; e < G[x].size() ; e ++) ans[G[x][e].idx] = cnt[G[x][e].depth];
	if(!opt) Add(x , -1);
}
char s[Len];
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)
	{
		int x;scanf("%s",s + 1);
		int lens = strlen(s + 1);Hash = 0;
		for(int j = 1 ; j <= lens ; j ++) Hash = Hash * K + s[j] - '0';
		Name[i] = Hash;
		scanf("%d",&x);
		if(x == 0) root.push_back(i);
		else add(x , i);
	}
	for(int i = 0 ; i < root.size() ; i ++) dfs1(root[i] , 0);
	scanf("%d",&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		if(dep[x] + y > n) ans[i] = 0;
		else
		{
			Node opt;
			opt.depth = dep[x] + y , opt.idx = i;
			G[x].push_back(opt);
		}
	}
	for(int i = 0 ; i < root.size() ; i ++) dfs2(root[i] , 0 , 0);
	for(int i = 1 ; i <= m ; i ++) printf("%d\n",ans[i]);
	return 0;
}
```

---

