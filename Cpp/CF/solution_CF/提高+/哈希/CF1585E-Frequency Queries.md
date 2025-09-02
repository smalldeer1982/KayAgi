# Frequency Queries

## 题目描述

Petya has a rooted tree with an integer written on each vertex. The vertex $ 1 $ is the root. You are to answer some questions about the tree.

A tree is a connected graph without cycles. A rooted tree has a special vertex called the root. The parent of a node $ v $ is the next vertex on the shortest path from $ v $ to the root.

Each question is defined by three integers $ v $ , $ l $ , and $ k $ . To get the answer to the question, you need to perform the following steps:

- First, write down the sequence of all integers written on the shortest path from the vertex $ v $ to the root (including those written in the $ v $ and the root).
- Count the number of times each integer occurs. Remove all integers with less than $ l $ occurrences.
- Replace the sequence, removing all duplicates and ordering the elements by the number of occurrences in the original list in increasing order. In case of a tie, you can choose the order of these elements arbitrary.
- The answer to the question is the $ k $ -th number in the remaining sequence. Note that the answer is not always uniquely determined, because there could be several orderings. Also, it is possible that the length of the sequence on this step is less than $ k $ , in this case the answer is $ -1 $ .

For example, if the sequence of integers on the path from $ v $ to the root is $ [2, 2, 1, 7, 1, 1, 4, 4, 4, 4] $ , $ l = 2 $ and $ k = 2 $ , then the answer is $ 1 $ .

Please answer all questions about the tree.

## 样例 #1

### 输入

```
2
3 3
1 1 1
1 2
3 1 1
3 1 2
3 2 1
5 5
1 2 1 1 2
1 1 2 2
3 1 1
2 1 2
4 1 1
4 2 1
4 2 2```

### 输出

```
1 -1 1 
1 1 2 1 -1```

# 题解

## 作者：Luzhuoyuan (赞：2)

Links: [[Codeforces]](http://codeforces.com/problemset/problem/1585/E) [[Luogu]](https://www.luogu.com.cn/problem/CF1585E)

### 题意简述

给定一棵 $n$ 个点的根为 $1$ 的树，第 $i$ 个节点有权值 $a_i$。有 $q$ 个询问，每次询问给出三个整数 $v,l,k$，表示将从根到节点 $v$ 的简单路径中经过的每个点的权值加入一个序列中，问其中出现次数大于等于 $l$ 的值中出现次数第 $k$ 小的值，若有多解输出任意合法解，若无解输出 `-1`。每个测试点 $t$ 组测试用例。

$$1\le n,q,\sum n,\sum q\le 10^6;1\le a_i\le n;1\le v,l,k\le n$$

### 思路

来自官方题解的妙妙线性做法。

首先考虑朴素做法。对于每个询问，把每个值的出现次数 $cnt_i$ 处理出来并升序排序，然后找到其中最小的大于等于 $l$ 的位置 $lb$（lower_bound），最后，位置在 $lb+k-1$ 的值肯定是一种合法解。（$lb+k-1>n$ 则无解。）

考虑怎么优化这种做法。我们思考这样一个问题：如何将一个有序整数序列的某个值加 $1$ 并维护其单调性。设要调整的位置为 $p1$，该位置原来的值为 $val$，维护一个序列 $lb_i$ 表示最小且值大于等于 $i$ 的位置，则我们可以找到 $p2=lb_{val+1}-1$，也就是值为 $val$ 的最靠右的位置，将 $p1,p2$ 交换，然后令 $lb_{val+1}$ 自减就能维护了。同样的，把某个值减 $1$ 反过来做一遍就行了。

这对解决这个问题有什么用呢？我们可以将询问离线，把每个询问挂在对应的点 $v$ 上，然后对这棵树进行 DFS，每进入一个点就把该点对应权值的 $cnt$ 增加 $1$ 并维护 $cnt$ 单调性，然后处理询问，离开这个点之前再减掉就行了。

具体实现中，我们维护一个排列 $d$ 表示 $cnt$ 排序后的位置对应的值，即 $\forall 1\le i<n,cnt_{d_i}\le cnt_{d_{i+1}}$。然后我们再维护 $dd=d^{-1}$，即 $dd_{d_i}=i$，$dd_i$ 就表示值 $i$ 在排序后出现的位置。然后对于进入的点 $u$，令 $p1=dd_{a_u},p2=lb_{cnt_{a_u}+1}-1$，然后像上面那样维护，维护时不交换 $cnt$，只要交换 $d,dd$ 就行了。复杂度 $O(n+q)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=1e6+5;
int T,n,m,a[N],x,y,z,cnt[N],d[N],dd[N],lb[N],ans[N];
vector<int> ve[N];
struct node{int id,l,k;};
vector<node> q[N];
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
void dfs(int u){
	int p1=dd[a[u]],p2=--lb[++cnt[a[u]]];
	swap(d[p1],d[p2]),swap(dd[d[p1]],dd[d[p2]]);
	for(node p:q[u])ans[p.id]=(lb[p.l]+p.k-1>n?-1:d[lb[p.l]+p.k-1]);
	for(int v:ve[u])dfs(v);
	swap(d[p1],d[p2]),swap(dd[d[p1]],dd[d[p2]]);
	lb[cnt[a[u]]--]++;
}
signed main(){
	T=read();
	while(T--){
		n=read(),m=read();
		for(int i=1;i<=n;i++)a[i]=read(),d[i]=dd[i]=i,lb[i]=n+1;
		for(int i=2;i<=n;i++)ve[read()].pb(i);
		for(int i=1;i<=m;i++)x=read(),y=read(),z=read(),q[x].pb({i,y,z});
		dfs(1);for(int i=1;i<=m;i++)printf("%d ",ans[i]);
		puts("");
		for(int i=1;i<=n;i++)ve[i].clear(),q[i].clear();
	}
	return 0;
}
```
（逃

---

## 作者：dd_d (赞：2)

思路 by @houzhiyuan  
[更好的阅读体验](https://www.cnblogs.com/dd-d/p/16656875.html)
### Sol
感觉在线不怎么可做，考虑离线。  
那么问题变成了维护路径上第 $k$ 大出现次数的数。  
考虑线段树，以出现次数为节点的下标，那么查询相当于是求第 $k$ 大。  
线段树二分即可。  
存方案的话开个 set 维护一下每个值即可。  
时间复杂度 $O(Q \log n)$。  
具体实现看代码。  
###  Code
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=1e6+10;
struct node
{
	int l,k,id;
};
set<int> s[N];
vector<int> G[N];
vector<node> q[N];
int siz[N<<2],n,m,a[N],cnt[N],ans[N];
void update(int k,int l,int r,int pos,int x1,int x2)
{
	siz[k]+=x2;
	if (l==r)
	{
		if (x2==1) s[l].insert(x1);
		else s[l].erase(x1);
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) update(k<<1,l,mid,pos,x1,x2);
	else update(k<<1|1,mid+1,r,pos,x1,x2);
}
int querysum(int k,int l,int r,int L,int R)
{
	if (L>R) return 0;
	if (L<=l&&r<=R) return siz[k];
	int mid=(l+r)>>1,res=0;
	if (L<=mid) res+=querysum(k<<1,l,mid,L,R);
	if (mid<R) res+=querysum(k<<1|1,mid+1,r,L,R);
	return res;
}
int query(int k,int l,int r,int val)
{
	if (siz[k]<val) return -1;
	if (l==r) return *s[l].begin();
	int mid=(l+r)>>1;
	if (siz[k<<1]>=val) return query(k<<1,l,mid,val);
	else return query(k<<1|1,mid+1,r,val-siz[k<<1]);
}
void dfs(int x,int fa)
{
	if (cnt[a[x]]) update(1,1,n,cnt[a[x]],a[x],-1);
	cnt[a[x]]++;
	update(1,1,n,cnt[a[x]],a[x],1);
	for (auto now:q[x])
		ans[now.id]=query(1,1,n,now.k+(now.l>1)*(querysum(1,1,n,1,now.l-1)));
	for (auto v:G[x])
	{
		if (v==fa) continue;
		dfs(v,x);
	}
	update(1,1,n,cnt[a[x]],a[x],-1);
	cnt[a[x]]--;
	if (cnt[a[x]]) update(1,1,n,cnt[a[x]],a[x],1);
}
void solve()
{
	n=read(); m=read();
	for (int i=1;i<=n;i++)
		a[i]=read(),G[i].clear(),q[i].clear();
	for (int i=2;i<=n;i++)
	{
		int x=read();
		G[x].emplace_back(i); G[i].emplace_back(x);
	}
	for (int i=1;i<=m;i++)
	{
		int x=read(),l=read(),k=read();
		q[x].push_back({l,k,i});
	}
	dfs(1,0);
	for (int i=1;i<=m;i++)
		writesp(ans[i]);
	putchar('\n');
}
signed main()
{
	int T=read();
	while (T--) solve();
}





```

---

## 作者：ifffer_2137 (赞：0)

在被 \*2100 军训过以后成功秒了这道 \*2400，十分牛。
### 题意
给定大小为 $n$ 的一棵以 $1$ 为根的有根树，点有点权。有 $q$ 次询问，每次询问给定 $u$，$l$，$k$，把 $u$ 到根路径上所有点的点权写下来，将出现次数小于 $l$ 的数全删去，对剩余序列去重，并按每种数在原序列中的出现次数升序排序，出现次数相等则任意排，求第 $k$ 个（如有多种可能随意输出一种，不存在输出 $-1$）。
### 分析
因为不带修，每次查询到根链，所以离线把询问挂在点上，直接 dfs，动态维护当前到根链上的信息。

然后你显然要弄一个`cnt[]`维护每个值出现次数，又因为要求第 $k$ 小，朴素二分出现次数，同时用个值域 BIT 维护一下出现次数小于等于 $x$ 的数有几种，就可以 check 了。最后要输出的是数值，所以再对每种出现次数维护一个`set`，直接从里面拿一个输出即可。这三个要维护的东西单点加和单点删都没啥好说的。

时间复杂度的话因为二分套 BIT 所以 $O(n\log^2 n)$，常数还十分大。但非常抱歉它跑 $10^6$ 过了，并且获得了`3936ms`的好成绩。具体解决办法可以弄个 sgt 上二分，就单 log 了喵。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e6+5;
int T;
int n,q;
int a[maxn],ans[maxn];
vector<int> tr[maxn];
struct node{int id,x,k;};
vector<node> ask[maxn];
int cnt[maxn];
set<int> val[maxn];
struct Fenwick_Tree{
	int c[maxn];
	void init(){for(int i=1;i<=n;i++) c[i]=0;}
	int lowbit(int x){return x&(-x);}
	void update(int x,int k){
		while(x<=n){
			c[x]+=k;
			x+=lowbit(x);
		}
	}
	int query(int x){
		int res=0;
		while(x){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
}BIT;
void init(){
	BIT.init();
	for(int i=1;i<=n;i++){
		cnt[i]=0;
		tr[i].clear(),ask[i].clear();
		val[i].clear();
	}
}
void add(int x){
	if(cnt[x]) BIT.update(cnt[x],-1),val[cnt[x]].erase(x);
	cnt[x]++;
	BIT.update(cnt[x],1),val[cnt[x]].insert(x);
}
void del(int x){
	BIT.update(cnt[x],-1),val[cnt[x]].erase(x);
	cnt[x]--;
	if(cnt[x]) BIT.update(cnt[x],1),val[cnt[x]].insert(x);
}
void dfs(int u,int f){
	add(a[u]);
	for(node p:ask[u]){
		int id=p.id,x=p.x,k=p.k;
		int l=1,r=n,res=-1;
		while(l<=r){
			int m=(l+r)>>1;
			if(BIT.query(m)-BIT.query(x-1)>=k){
				res=m;
				r=m-1;
			}else{
				l=m+1;
			}
		}
		if(res!=-1) ans[id]=(*val[res].begin());
		else ans[id]=-1;
	}
	for(int v:tr[u]){
		if(v==f) continue;
		dfs(v,u);
	}
	del(a[u]);
}
signed main(){
	cin.tie(0),cout.tie(0);
	T=read();
	while(T--){
		n=read(),q=read();init();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=2;i<=n;i++){
			int fa=read();
			tr[fa].eb(i),tr[i].eb(fa);
		}
		for(int i=1;i<=q;i++){
			int u=read(),x=read(),k=read();
			ask[u].eb((node){i,x,k});
		}
		dfs(1,0);
		for(int i=1;i<=q;i++) cout<<ans[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

