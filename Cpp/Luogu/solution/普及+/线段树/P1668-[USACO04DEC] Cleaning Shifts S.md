# [USACO04DEC] Cleaning Shifts S

## 题目描述

一天有 $T(1\le T\le 10^6)$ 个时段。约翰正打算安排他的 $N(1\le N\le 2.5\times 10^4)$ 只奶牛来值班，打扫打扫牛棚卫生。每只奶牛都有自己的空闲时间段 $ [S_i,E_i](1\le S_i\le E_i\le T)$，只能把空闲的奶牛安排出来值班。而且，每个时间段必需有奶牛在值班。

那么，最少需要动用多少奶牛参与值班呢？如果没有办法安排出合理的方案，就输出 $-1$。

## 说明/提示

$1\le T\le 10^6$，$N\le 2.5\times 10^4$，$1\le S_i\le E_i\le T$。

$\text{Update On 2023/08/08}$：添加了一组hack数据，详情见[这里](https://www.luogu.com.cn/discuss/613052)。叉掉了时间复杂度为 $\mathcal O(nt)$ 的错解。

## 样例 #1

### 输入

```
3 10
1 7
3 6
6 10```

### 输出

```
2```

# 题解

## 作者：Greenzhe (赞：29)

看到题解区没有贪心解法，来交一发。蒟蒻第一次做证明，**如有勘误，敬请指教。**

该题的本质是从 $n$ 个区间里选择一些区间，在这些区间能覆盖 $[1,t]$ 内所有**整数点**的前提下，使得选择的区间个数**最小**。

### 算法流程：

1. 将所有区间按左端点从小到大排序。

2. 设 $st$ 为当前**最靠左的**没有被覆盖的点。枚举每个区间，在所有能覆盖 $st$ 的区间中，挑一个**右端点最大**的作为当前决策。然后更新 $st$。

3. 如果找不到能覆盖 $st$ 的区间，则原问题无解。

利用双指针实现算法。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct segment{
	int l,r;
	bool operator<(const segment &x) const{
		return l<x.l;
	} // 重载小于号，用于 sort()。也可以用 cmp() 函数实现同样功能。
}range[25005];

int main(){
	int n,ed;
	scanf("%d%d",&n,&ed);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&range[i].l,&range[i].r);
	sort(range+1,range+n+1);
	int st=1,ans=0;
	for(int i=1,j=1;i<=n;){
		int r=0;
		while(j<=n&&range[j].l<=st){ // 左端点要 <= st，即该区间能覆盖 st 
			r=max(r,range[j].r); // 找右端点最大的
			j++;
		}
		if(r<st) break; // 找不到能覆盖 st 的区间
		ans++;
		if(r>=ed){ // 有解，输出
			printf("%d\n",ans);
			return 0;
		}
		st=r+1;i=j;
	}
	printf("-1\n");
	return 0;
}
```

### 证明：

参考闫学灿《算法基础课》。

只考虑有解的情况。

- **正确性**：由于我们每次选择的左端点 $\le$ 上次选择的右端点，所以能保证任意两个区间都是连接的。所以每个整数点都一定会被覆盖到。

- **最优性**：假设最优解与该算法得出的解有部分区间选择不同。由于该算法中每次选择右端点最大的区间，所以一定能够覆盖更多的点。如果我们把最优解中选择的区间换成该算法选择的区间，显然答案不会更劣。

综上所述，以上贪心算法能得出最优解。

---

## 作者：MoonCake2011 (赞：17)

此题我的 dalao 朋友 @HDZmessi 用的贪心，而我只会用 dp。

我做此题有三个优化我的 dp 的阶段。

# Step 1

一看到此题，一看到它是区间问题，立马上 $\text O(n^3)$ 的区间 dp。

对于每个 $[l,r]$，$dp_{i,j}=1$，其中 $l \le i \le j \le r$。

只能通过 $t \le 500$ 的数据。

不用多讲，暴力转移即可。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int dp[510][510];
int main() {
	cin>>n>>t;
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=n;i++){
		int l,r;
		cin>>l>>r;
		for(int j=l;j<=r;j++)
			for(int k=j;k<=r;k++)
				dp[j][k]=1;
	}
	for(int k=1;k<=t;k++)
		for(int i=1;i+k-1<=t;i++){
			int j=i+k-1;
			for(int p=i;p<j;p++)
				dp[i][j]=min(dp[i][j],dp[i][p]+dp[p+1][j]);
		}
	if(dp[1][t]==0x3f3f3f3f) cout<<-1;
	else cout<<dp[1][t];
	return 0;
}
```
期望得分 10 分。

~~骗了 28 分。~~
# Step 2

尝试区间 dp 变成 线性 dp。

设 $dp_i$ 为 $[1,i]$ 区间需要用的线段的数量。

对于每条线段，如果它的 $l$ 为 $1$，那么 $dp_r=1$。

如果它的 $l$ 不为 $1$，它可以尝试用能与 $[l,r]$ 合并的组合来拼接。

于是推出状态转移方程。

$dp_r=\text{min}\{dp_j\}$，其中 $l-1 \le j<r$。

因为 dp 的状态转移有顺序性。

所以按 $r$ 从小到大排序。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int dp[int(1e6)+10];
struct node{
	int l,r;
}a[25010];
bool cmp(node x,node y){
	return x.r<y.r;
}
int main() {
	cin>>n>>t;
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
		if(a[i].l==1) dp[a[i].r]=1;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
		for(int j=a[i].l-1;j<a[i].r;j++)
			dp[a[i].r]=min(dp[a[i].r],dp[j]+1);
	if(dp[t]==0x3f3f3f3f) cout<<-1;
	else cout<<dp[t];
	return 0;
}
```
时间复杂度 $\text O(nt)$。

期望得分 60 分。

实际~~骗得~~ 100 分。

数据还是过于淼了。

# Step 3

既然要求区间最小，那么我们可以用线段树维护 dp 数组。

线段树只用区间最小与单点修改就行了。

这才是正确的时间复杂度 $\text O(n \log t)$。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int dp[int(4e6)+10];
void build(int root,int l,int r){
	if(l==r){
		dp[root]=1e9;
		return;
	}
	int mid=l+r>>1;
	build(root*2,l,mid);
	build(root*2+1,mid+1,r);
	dp[root]=min(dp[root*2],dp[root*2+1]);
}
void update(int x,int k,int root=1,int l=1,int r=t){
	if(l==r && l==x){
		dp[root]=k;
		return;
	}
	int mid=l+r>>1;
	if(x>=l && x<=mid) update(x,k,root*2,l,mid);
	else update(x,k,root*2+1,mid+1,r);
	dp[root]=min(dp[root*2],dp[root*2+1]);
}
int get_min(int l,int r,int root=1,int x=1,int y=t){
	if(x>=l && y<=r) return dp[root];
	int mid=x+y>>1;
	int tot=1e9;
	if(l<=mid) tot=min(get_min(l,r,root*2,x,mid),tot);
	if(r>mid) tot=min(get_min(l,r,root*2+1,mid+1,y),tot);
	return tot; 
}
struct node{
	int l,r;
}a[25010];
bool cmp(node x,node y){
	if(x.r!=y.r) return x.r<y.r;
	return x.l<y.l;
}
int main() {
	cin>>n>>t;
	build(1,0,t);
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
		if(a[i].l==1) update(a[i].r,1);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		int p=min(get_min(a[i].r,a[i].r),get_min(a[i].l-1,a[i].r-1)+1);
		update(a[i].r,p);
	}
	int p=get_min(t,t);
	if(p==1e9) cout<<-1;
	else cout<<p;
	return 0;
}
```

---

## 作者：Southern_Dynasty (赞：16)

两种做法。

# 一、最短路

题目要求区间数量最小。如果能建出图来，就可以转换为最短路问题。

具体地，我们从 $l-1\to r$ 连一条长度为 $1$ 的边，意味着要多经过 $(l-1,r]$ 这一个区间。这是左开右闭的形式。

现在还有一个问题：通过这种边我们只能到达区间的右端点，如果想向左到达区间内部的其他点或者到达另一个区间，该怎么办呢？

我们可以对于 $i\in[1,T]$，从 $i\to i-1$ 连一条长度为 $0$ 的边，这样既可以向左移动，又不会算错答案（显然点的移动不会增加新的区间）。

然后求 $0$ 到 $T$ 的最短路即可（因为左开右闭）。

注意到边权只有 $0,1$ 两种取值，所以可以使用 01BFS。时间复杂度 $O(T+n)$。

代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define gt getchar
#define pt putchar
typedef long long ll;
const int N=1e6+5;
using namespace std;
using namespace __gnu_pbds;
inline bool __(char ch){return ch>=48&&ch<=57;}
template<class T> inline void read(T &x){
	x=0;bool sgn=0;char ch=gt();
	while(!__(ch)&&ch!=EOF) sgn|=(ch=='-'),ch=gt();
	while(__(ch)) x=(x<<1)+(x<<3)+(ch&15),ch=gt();
	if(sgn) x=-x;
}
template<class T,class ...T1> inline void read(T &x, T1 &...x1){
	read(x);
	read(x1...);
}
template<class T> inline void print(T x){
	static char st[70];short top=0;
	if(x<0) pt('-');
 	do{st[++top]=x>=0?(x%10+48):(-(x%10)+48),x/=10;}while(x);
    while(top) pt(st[top--]);
}
template<class T> inline void printsp(T x){
	print(x);
	putchar(' ');
}
template<class T> inline void println(T x){
	print(x);
	putchar('\n');
}
inline void put_str(string s){
	int siz=s.size();
	for(int i=0;i<siz;++i) pt(s[i]);
	printf("\n");
}
struct edge{
	int to,nxt,w;
}e[N<<1];
int head[N],cnt,n,T,dis[N];
deque<int>dq;
inline void add_edge(int f,int t,int w){
	e[++cnt].to=t;
	e[cnt].w=w;
	e[cnt].nxt=head[f];
	head[f]=cnt;
}
inline void BFS_01(int s){
	memset(dis,0x3f3f3f3f,sizeof(dis));
	dis[s]=0;
	dq.push_back(s);
	while(dq.size()){
		int u=dq.front();
		dq.pop_front();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,w=e[i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(w) dq.push_back(v);
				else dq.push_front(v);
			}
		}
	}
}
signed main(){
	read(n,T);
	for(int i=1;i<=T;++i) add_edge(i,i-1,0);
	for(int u,v,i=1;i<=n;++i){
		read(u,v);
		add_edge(u-1,v,1);
	}
	BFS_01(0);
	println(dis[T]==0x3f3f3f3f?-1:dis[T]);
	return 0;
}
```

现在加强一下，$T$ 开到 $10^9$，怎么办？


注意到区间长度统一缩小后对答案没有影响，因此考虑离散化。

细节：注意我们是要从 $l-1\to r$ 连边，所以应将 $l-1$ 和 $r$ 离散化（而不是 $l$）！并且，起点 $S=0$ 和终点 $T$ 也需要离散化，然后跑最短路时直接使用离散化后的结果。

时间复杂度 $O(n\log n)$，瓶颈在于离散化。

代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define gt getchar
#define pt putchar
typedef long long ll;
const int N=1e6+5;
using namespace std;
using namespace __gnu_pbds;
inline bool __(char ch){return ch>=48&&ch<=57;}
template<class T> inline void read(T &x){
	x=0;bool sgn=0;char ch=gt();
	while(!__(ch)&&ch!=EOF) sgn|=(ch=='-'),ch=gt();
	while(__(ch)) x=(x<<1)+(x<<3)+(ch&15),ch=gt();
	if(sgn) x=-x;
}
template<class T,class ...T1> inline void read(T &x, T1 &...x1){
	read(x);
	read(x1...);
}
template<class T> inline void print(T x){
	static char st[70];short top=0;
	if(x<0) pt('-');
 	do{st[++top]=x>=0?(x%10+48):(-(x%10)+48),x/=10;}while(x);
    while(top) pt(st[top--]);
}
template<class T> inline void printsp(T x){
	print(x);
	putchar(' ');
}
template<class T> inline void println(T x){
	print(x);
	putchar('\n');
}
inline void put_str(string s){
	int siz=s.size();
	for(int i=0;i<siz;++i) pt(s[i]);
	printf("\n");
}
struct edge{
	int to,nxt,w;
}e[N<<1];
int head[N],cnt,n,T,dis[N],lsh[N<<1],tot,u[N],v[N];
deque<int>dq;
inline void add_edge(int f,int t,int w){
	e[++cnt].to=t;
	e[cnt].w=w;
	e[cnt].nxt=head[f];
	head[f]=cnt;
}
inline void BFS_01(int s){
	memset(dis,0x3f3f3f3f,sizeof(dis));
	dis[s]=0;
	dq.push_back(s);
	while(dq.size()){
		int u=dq.front();
		dq.pop_front();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,w=e[i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(w) dq.push_back(v);
				else dq.push_front(v);
			}
		}
	}
}
signed main(){
	read(n,T);
	int S=0;
	lsh[++tot]=S;
	for(int i=1;i<=n;++i){
		read(u[i],v[i]);
		lsh[++tot]=u[i]-1,lsh[++tot]=v[i];
	}
	lsh[++tot]=T;
	sort(lsh+1,lsh+tot+1);
	tot=unique(lsh+1,lsh+tot+1)-(lsh+1);
	for(int i=1;i<=n;++i){
		u[i]=lower_bound(lsh+1,lsh+tot+1,u[i]-1)-lsh;// u[i]-1
		v[i]=lower_bound(lsh+1,lsh+tot+1,v[i])-lsh; 
		add_edge(u[i],v[i],1);
	}
	S=lower_bound(lsh+1,lsh+tot+1,S)-lsh;
	T=lower_bound(lsh+1,lsh+tot+1,T)-lsh;
	for(int i=S+1;i<=T;++i) add_edge(i,i-1,0);
	BFS_01(S);
	println(dis[T]==0x3f3f3f3f?-1:dis[T]);
	return 0;
}
```


# 二、dp

考虑 DP。

设 $f_i$ 表示 $[1,i]$ 中所有数被覆盖所需要的最小区间数。初始有 $f_0=0$。

记 $mn_i$ 表示以 $i$ 为**右端点**的所有区间中**左端点最小值**（显然长度更长的区间更优），没有则为 $-1$，分类讨论：

- $mn_i=-1$：直接跳过。

- $mn_i\not=-1$：考虑在原有基础上添加 $i$ 所在的区间，有 $f_i=\min_{j=mn_i-1}^{i-1}f_j+1$

分析复杂度：最坏情况下就是区间为 $[1,...T-n+1],[1...T-n+2],....,[1,T]$。复杂度为 $O(\sum_{i=0}^{n-1}T-i)=O(Tn)$，过不了。

但是由于数据水，所以能过（但是 1.2s 巨慢）。

代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define gt getchar
#define pt putchar
typedef long long ll;
const int N=1e6+5;
using namespace std;
using namespace __gnu_pbds;
inline bool __(char ch){return ch>=48&&ch<=57;}
template<class T> inline void read(T &x){
	x=0;bool sgn=0;char ch=gt();
	while(!__(ch)&&ch!=EOF) sgn|=(ch=='-'),ch=gt();
	while(__(ch)) x=(x<<1)+(x<<3)+(ch&15),ch=gt();
	if(sgn) x=-x;
}
template<class T,class ...T1> inline void read(T &x, T1 &...x1){
	read(x);
	read(x1...);
}
template<class T> inline void print(T x){
	static char st[70];short top=0;
	if(x<0) pt('-');
 	do{st[++top]=x>=0?(x%10+48):(-(x%10)+48),x/=10;}while(x);
    while(top) pt(st[top--]);
}
template<class T> inline void printsp(T x){
	print(x);
	putchar(' ');
}
template<class T> inline void println(T x){
	print(x);
	putchar('\n');
}
inline void put_str(string s){
	int siz=s.size();
	for(int i=0;i<siz;++i) pt(s[i]);
	printf("\n");
}
int n,T,l[N],r[N],min_l[N],f[N];
signed main(){
	read(n,T);
	memset(min_l,0x3f,sizeof(min_l));
	for(int i=1;i<=n;++i) read(l[i],r[i]),min_l[r[i]]=min(min_l[r[i]],l[i]);
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int i=1;i<=T;++i){
		if(min_l[i]==0x3f3f3f3f) continue;
		for(int j=min_l[i]-1;j<i;++j) f[i]=min(f[i],f[j]+1);
	}
	println(f[T]==0x3f3f3f3f?-1:f[T]);
	return 0;
}
```

考虑优化，注意 DP 的转移方程，实际上就是一个 RMQ。再加上 $f_i$ 的更新，也就是说我们只需要支持区间求 $\min$，单点修改的操作即可。用一棵线段树维护即可。时间复杂度 $O(T\log T)$。

求出来区间 $\min$ 之后有一点小细节，具体见代码。

代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define gt getchar
#define pt putchar
typedef long long ll;
const int N=1e6+5;
using namespace std;
using namespace __gnu_pbds;
inline bool __(char ch){return ch>=48&&ch<=57;}
template<class T> inline void read(T &x){
	x=0;bool sgn=0;char ch=gt();
	while(!__(ch)&&ch!=EOF) sgn|=(ch=='-'),ch=gt();
	while(__(ch)) x=(x<<1)+(x<<3)+(ch&15),ch=gt();
	if(sgn) x=-x;
}
template<class T,class ...T1> inline void read(T &x, T1 &...x1){
	read(x);
	read(x1...);
}
template<class T> inline void print(T x){
	static char st[70];short top=0;
	if(x<0) pt('-');
 	do{st[++top]=x>=0?(x%10+48):(-(x%10)+48),x/=10;}while(x);
    while(top) pt(st[top--]);
}
template<class T> inline void printsp(T x){
	print(x);
	putchar(' ');
}
template<class T> inline void println(T x){
	print(x);
	putchar('\n');
}
inline void put_str(string s){
	int siz=s.size();
	for(int i=0;i<siz;++i) pt(s[i]);
	printf("\n");
}
int n,T,l[N],r[N],min_l[N],f[N];
struct Node{
	int l,r;
	int mn;
}node[N<<2];
inline int lson(int x){return x<<1;}
inline int rson(int x){return x<<1|1;}
inline void push_up(int p){
	node[p].mn=min(node[lson(p)].mn,node[rson(p)].mn);
}
void build(int p,int l,int r){
	node[p].l=l,node[p].r=r;
	if(l==r) return node[p].mn=0x3f3f3f3f,void();
	int mid=l+((r-l)>>1);
	build(lson(p),l,mid);
	build(rson(p),mid+1,r);
	push_up(p);
}
int query(int p,int l,int r){
	if(l<=node[p].l&&node[p].r<=r) return node[p].mn;
	int mid=node[p].l+((node[p].r-node[p].l)>>1);
	if(r<=mid) return query(lson(p),l,r);
	if(l>mid) return query(rson(p),l,r);
	return min(query(lson(p),l,r),query(rson(p),l,r));
}
void update(int p,int x,int k){
	if(node[p].l==node[p].r) return node[p].mn=k,void();
	int mid=node[p].l+((node[p].r-node[p].l)>>1);
	if(x<=mid) update(lson(p),x,k);
	else update(rson(p),x,k);
	push_up(p);
}
signed main(){
	read(n,T);
	memset(min_l,0x3f,sizeof(min_l));
	for(int i=1;i<=n;++i) read(l[i],r[i]),min_l[r[i]]=min(min_l[r[i]],l[i]);
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	build(1,0,T);
	update(1,0,0);
	for(int i=1;i<=T;++i){
		if(min_l[i]==0x3f3f3f3f) continue;
		f[i]=query(1,min_l[i]-1,i-1);
		if(f[i]!=0x3f3f3f3f) f[i]++;
		update(1,i,f[i]);
	}
	println(f[T]==0x3f3f3f3f?-1:f[T]);
	return 0;
}
```

应该也可以离散化。

---

## 作者：HDZmessi (赞：6)

一道很有趣的题目。

题意大致是说给定一个长线段的长度和一些短线段，要求用尽量少的短线段完全覆盖住长线段。

算法貌似需要一点贪心，首先建立一个结构体，然后按左端点进行排序，然后对长线段覆盖的位置不断更新和标记，更新标记时只需注意以下两点。

1. 线段左端点的位置一定要小于或等于标记。
1. 线段右端点尽可能的大。

找到最符合条件的线段后就把标记更新成那条线段右端点加一就行了。

至于判断无解的情形，我们只需要看有没有符合上述第一条的线段，如果没有就输出结果并结束程序。

AC Code：

```cpp
#include<bits/stdc++.h> //万能头，你值得拥有 
using namespace std;
int ans;
struct node{
	int a;
	int b;
}m[100005];  //结构体定义 
bool operator < (node a,node b){
	return a.a<b.a;  //按照左端点进行排序 
}
int main(){
	int n,t;cin>>n>>t;
	for(int i=0;i<n;i++){
		cin>>m[i].a>>m[i].b;
	}
	sort(m,m+n);
	int mark=1,sum=0;  //一个是更新判断，一个是标记 
	while(sum!=t){
		sum=0; //每次一定要归零 
		for(int i=0;i<n;i++){
			if(m[i].a<=mark){  //第一个条件 
				sum=max(sum,m[i].b);  //第二个条件 
			}
		}
	//	cout<<sum<<endl;  //调试过程 
		if(sum==0||sum<mark){  //如果初始值不变或者更新后右端点反而更小则输出-1 
			cout<<-1;
			return 0;
		}
		mark=sum+1;  //更新标记 
		ans++; //记录答案 
	}
	cout<<ans;
	return 0;  //华丽结束 
}
```
这段代码直接提交会 TLE 一个点，开个 O2 就行了！

---

## 作者：船酱魔王 (赞：5)

# P1668 [USACO04DEC] Cleaning Shifts S 题解

## 题意回顾

一条大线段被分为 $ t $ 个小段，$ n $ 个备选小线段，每个线段可以覆盖 $ [l_i,r_i] $ 的小段。你可以启用一些小线段使得每个小段至少被一个小线段覆盖，求最小启用数或报告无解。

$ t \le 10^6 $，$ n \le 2.5 \times 10^4 $，$ 1 \le l_i,r_i \le t $。

## 分析

我们定义 $ dp_i $ 表示 $ [1,i] $ 正好被覆盖时，最小的线段启用数。

我们把线段按照右端点第一关键字，左端点为第二关键字排序。对于线段 $ [l,r] $，考虑设计暴力转移：

$$ dp_{r}=\min\{dp_{i}\}(l-1 \le i \le r-1) $$

这个转移的主要时间瓶颈在于区间最小值。所以我们用线段树维护 $ dp $ 数组，只需要单点修改、区间查询最小值即可。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2.5 * 1e4 + 5;
const int T = 1e6 + 5;
int n, t;
struct node {
	int l, r; 
} a[N];
bool operator<(node p1, node p2) {
	if(p1.r != p2.r) {
		return p1.r < p2.r;
	}
	return p1.l < p2.l;
}

int d[T * 4];
void build(int s, int t, int p) {
	if(s == t) {
		d[p] = 1e9 + 5;
		return;
	}
	int mid = (s + t) >> 1;
	build(s, mid, p * 2);
	build(mid + 1, t, p * 2 + 1);
	d[p] = min(d[p * 2], d[p * 2 + 1]);
}
void update(int x, int v, int s, int t, int p) {
	if(s == t) {
		d[p] = min(d[p], v);
		return;
	}
	int mid = (s + t) >> 1;
	if(x <= mid) {
		update(x, v, s, mid, p * 2);
	} else {
		update(x, v, mid + 1, t, p * 2 + 1);
	}
	d[p] = min(d[p * 2], d[p * 2 + 1]);
}
int query(int l, int r, int s, int t, int p) {
	if(l <= s && t <= r) {
		return d[p];
	}
	int mid = (s + t) >> 1;
	int sum = 1e9 + 5;
	if(l <= mid) {
		sum = min(sum, query(l, r, s, mid, p * 2));
	}
	if(mid < r) {
		sum = min(sum, query(l, r, mid + 1, t, p * 2 + 1));
	}
	return sum;
}

int main() {
	scanf("%d%d", &n, &t);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &a[i].l, &a[i].r);
	}
	sort(a + 1, a + n + 1);
	build(1, t, 1);
	for(int i = 1; i <= n; i++) {
		if(a[i].l == 1) {
			update(a[i].r, 1, 1, t, 1);
			if(a[i].r == t) {
				printf("1\n");
				return 0;
			}
		}
	}
	int ans = 1e9 + 5;
	for(int i = 1; i <= n; i++) {
		if(a[i].l > 1) {
			int tmp = query(max(a[i].l - 1, 1), max(a[i].r - 1, 1), 1, t, 1) + 1;
			update(a[i].r, tmp, 1, t, 1);
			if(a[i].r == t) {
				ans = min(ans, tmp);
			}
		}
	}
	if(ans == 1e9 + 5) {
		printf("-1\n");
	} else {
		printf("%d\n", ans);
	}
	return 0;
}
```

## 总结与评价

线段树优化 DP 典题。

---

## 作者：wangzikang (赞：5)

来个最短路题解。

我们建立一条从 $t+1$ 到 $1$ 的长度为0的链，以样例为例，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rlfg828z.png)

对于每一个奶牛，我们新建一个点，然后从 $s_i$ 连到这个点，再从这个点连到 $e_i+1$，使这两条边的总边权为1，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/bfql3o0j.png)

显然，$1-t+1$ 的最短路就是答案。

我们可以感性理解：走到时间轴上的某个点时代表前面的时刻都有人值班，所以我们可以反着走：我们从 $s_i$ 到 $e_i+1$ 花一个边权的过程，就是让一个奶牛从 $s_i$ 值班到 $e_i$，由于走到时间轴上的某个点时代表前面的时刻都有人值班，所以我们应该直接走到 $e_i+1$。

注意常数因子带来的时间复杂度影响。

code：
```cpp
#include<bits/stdc++.h>
const int MAXN=2e6+10,MAXM=5e6+10;
using namespace std;
int s,t,k;
struct node{
	int nxt,to,dis;
}g[MAXM<<1];
int n,m,head[MAXN],cnt,dis[MAXN],vis[MAXN];
void add(int u,int v,int w){
	g[++cnt].nxt=head[u],head[u]=cnt,g[cnt].to=v,g[cnt].dis=w;
}
priority_queue<int,vector<pair<int,int> >,greater<pair<int,int> > >q;
void dij(int s){//乐 
	memset(dis,0x3f,sizeof dis);
	dis[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=g[i].nxt){
			int v=g[i].to;
			if(!vis[v]&&(dis[v]>dis[u]+g[i].dis)){
				dis[v]=min(dis[v],dis[u]+g[i].dis);
				q.push(make_pair(dis[v],v));
				vis[v]=1;
			}
			dis[v]=min(dis[v],dis[u]+g[i].dis);
		}
	}
}
signed main(){
	
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	int cnt=1;
	for(int i=1;i<m;++i){
		add(i+1,i,0);
	}
	for(int i=1;i<=n;++i){
		int l,r;
		cin>>l>>r;
		add(l,m+(++cnt),0);
		add(m+cnt,r+1,1);
	}
	dij(1);
	cout<<(dis[m+1]==0x3f3f3f3f?-1:dis[m+1]);
	return 0;
}
```


---

## 作者：Wangjunhao2011 (赞：4)

## 此题可用贪心算法

贪心的方法为首先从第 $x$ 个时段 ( $x$ 初始为 $1$ ) 开始判断。如果有一个奶牛的工作开始时间是小于当前的 $x$ 那么就先将这个数记录下来，以后再遇到小于 $x$ 的工作开始时间，就更新记录的数。使记录下来的数一直保持最小值。最后将 $x$ 替换成记录好的数。至于判断是否无解的情况，我们只需要在整体扫完后判断记录下来的数是否是初始值，即 $0$ 就说明有一段是无奶牛的，直接输出 $-1$ 。而如果记录出来的数小于我们的 $x$，也说明有一段是无奶牛的，也是直接输出 $-1$ 即可。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int aaa;
	int bas;
	int &operator [](int n){
		if(n==1)return aaa;
		else return bas;
	}//重载了中括号，于是可以用下标来访问aaa或bas 
}a[2500001];
int main(){
	int n,l;cin>>n>>l;
	for(int i=1;i<=n;i++){
		cin>>a[i][1]>>a[i][2];
	}
	int ans=0;
	int book=1,cd=1;//cd 长度的拼音首字母 
	while(cd!=l){
		cd=0;
		for(int i=1;i<=n;i++){
			if(a[i][1]<=book){
				cd=max(cd,a[i][2]);
			}
		}
		if(cd==0||cd<book){
			cout<<-1;
			exit(0);//华丽结束 
		}
		book=cd+1;
		ans++; 
	} 
	cout<<ans;
	return 0;
} 
```
因为在有解的情况下时间复杂度基本为 $O(N^2)$ 而 $N_{max}$ 为 $10^6$ 肯定 ``TLE`` ！

不过开 ``O2`` 还救就的回来。

不然就只能得 $90$ 分。

但有没有不用开 ``O2`` 优化也能过的方法呢？

答案是当然有，我们知道 ``C++`` 有一个内置函数叫做 ``sort``,因为我们以前是从 $1$ 开始枚举到 $n$，但如果我们排了序，上一个小于 $x$ 的工作开始时间到下一个 $x$ 就一定不会通过条件 ``a[i][1]<=book``。

优化AC代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int aaa;
	int bas;
	int &operator [](int n){
		if(n==1)return aaa;
		else return bas;
	}//重载了中括号，于是可以用下标来访问aaa或bas 
}a[25001];
bool operator < (const node aa,const node b){
	return aa.aaa<b.aaa;//重载运算符 
}
int main(){
	int n,l;cin>>n>>l;
	for(int i=1;i<=n;i++){
		cin>>a[i][1]>>a[i][2];
	}
	sort(a+1,a+n+1);
	int ans=0;
	int book=1,cd=1,bn=1;//cd 长度的拼音首字母 
	while(cd!=l){
		cd=0;
		for(int i=bn;i<=n;i++){
			if(a[i][1]<=book){
			    bn++;
				cd=max(cd,a[i][2]);
			}
		}
		if(cd==0||cd<book){
			cout<<-1;
			exit(0);//华丽结束 
		}
		book=cd+1;
		ans++; 
	} 
	cout<<ans;
	return 0;
} 
```

那我们再来分析一下优化后的时间复杂度。

$1$.``sort`` 的平均时间复杂度为 $O(n  \log n)$

$2$. 在 ``for(int i=bn;i<=n;i++)`` 在最坏且有解的情况下第一次运行为 $O(n)$ ,第二次是 $O(n-1)$，$\dots$ 第 $n$ 次为 $O(1)$。而``while(cd!=l)`` 在最坏且有解的情况是会运行 $n$ 次的，所以最坏时间复杂度为  $O(n+(n-1)+(n-2)+\dots+2+1)=O(\frac{n^2+n}{2})=O(n^2+n)=O(n^2)$

两个合并起来  $O(n \log n)+O(n^2)=O(n\log n+n^2)=O(n^2)$

你会惊奇的发现这好像和上一个一样，但上一个没有较小的常数忽略，而这个忽略了 $\frac{1}{2}$，所以这个比上一个快了足足将近一倍！

---

## 作者：hxuwna (赞：3)

## 题面大意
给你一个 $t$，一个 $n$，和 $n$ 个区间 $[s[i],e[i]]$。
让你求一个数 $ans$，使得在这 $n$ 个区间中取 $ans$ 个区间 $[ss[i],ee[i]]$，能够令 $\bigcup_{i=1}^{ans} [ss[i],ee[i]]=[1,t]$，且 $ans$ 要尽可能小。

## 分析
首先，因为因为它要令几个区间的并集为 $[1,t]$。  

所以，我们考虑贪心求覆盖当前区间 $[1,k]$ 的最小的区间数，并记录区间数最小时区间并的最大右端点。  

当 $k$ 增大时，如果最大右端点比 $k$ 小，那么求 $\max_{i=1}^{n} e[i] ,s[i]<=最大右端点$。

显然，当前区间并与该选定区间合并等价于令当前区间并的最大右端点与该选定区间右端点取最大值。

所以，我们直接把当前区间并的最大右端点赋值为该选定区间右端点取最大值。

而，若赋值后区间并的最大右端点仍小于 $k$ ，那么可得知求不出 $ans$，所以直接输出负一。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e6+5;
int n,t,la,ma[N],maa,ans;
struct node{
	int s,e;
}a[N];//给定区间
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>t;la=1;
	for(int i=1;i<=n;i++) cin>>a[i].s>>a[i].e,ma[a[i].s]=max(ma[a[i].s],a[i].e);//ma[i]:以i为左端点区间的最大右端点
	for(int i=1;i<=t;i++){
		if(la<i) cout<<-1,exit(0);//若无解，输出-1
		maa=max(maa,ma[i]);//求选定区间右端点
		if(la==i) la=maa+1,ans++;//提前一步赋值为选定区间右端点，la是最大右端点+1
	}
	if(la<=t) cout<<-1,exit(0);//同上
	cout<<ans;
	return 0;
}
```
该算法不用快排，所以不带 $\log$，时间复杂度 $O(n)$，但在该题中时间还是那些带 $\log$ 的快（可能时数据太水了）。

---

## 作者：ICU152_lowa_IS8 (赞：3)

介绍一种贪心的写法：

## 算法大致流程：

我们直接将数组按 $S_i$ 从小到大排序，$E_i$ 不用管。

设一个标记 $start$ 为当前**连续**覆盖到的最右的点，随后一个指针 $i$ 加一向右寻找 $S_i \leq start+1$ 的数字。

如果循环一次都进不去（这就是之前按 $S_i$ 从小到大排序的方便之处了），那么直接跳出循环即可。

进去循环之后，用一个变量 $maxright$ 记录 $S_i$ 可以覆盖 $start+1$ 的区间中最大的 $E_i$。

正确性：在所有能覆盖的区间中，选择 $E_i$ 更右的**一定不比选择 $E_i$ 更左的更劣**，因为 $E_i$ 更右的区间有更大的机会找到一个 $S_i$ 可以覆盖到 $E_i+1$ 的位置。

最后，更新 $start=maxright$，$ans$ 加一。

这里有一个小细节（如果没有这一行代码会只有 $86$ 分）：如果在过程中 $start \geq T$，那么要直接跳出循环输出答案。

给一组 Hack:

```
2 10
1 10
11 20
```
答案很明显是 $1$，实际输出 $2$。

最后跳出循环时，做一个判断：

如果 $start<T$，那么输出 $-1$；否则，输出 $ans$。


------------
代码如下：
```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r;
}a[25005];
bool cmp(node a,node b){
	return a.l<b.l;
}
int main(){
	int n,t;
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
	}
	sort(a+1,a+n+1,cmp);
	int start=0,cnt=0;
	for(int i=1;i<=n;i++){
		int maxright=0;
		while(a[i].l<=start+1&&i<=n){
			maxright=max(maxright,a[i].r);
			i++;
		}
		i--;
		if(start>=t)break;
		if(!maxright){
			break;
		}
		start=maxright;
		cnt++;
	}
	if(start<t){
		cout<<-1;
	}
	else{
		cout<<cnt;
	}
	return 0;
}
```

---

## 作者：TheCliffSwallow (赞：2)

### 题意
给定 $n$ 个区间，求最少区间数使得能覆盖 $[1,T]$。
### 思路
最短路。为了让区间连续，可以建成左开右闭的区间，区间整体覆盖后可看做每个给定区间的右端点向左移动数位。将给定的区间 $[i,j]$ 建为对于 $\forall k\in (i-1,j]$ 从 $i-1$ 到 $k$ 的边权为 $1$ 的边，但是这样会 MLE。所以可以只建从 $i-1$ 到 $j$ 的边，而对于每个 $k\in[1,T]$，建一条从 $k$ 到 $k-1$ 的边权为 $0$ 的边。

最后答案就是从 $0$ 到 $T$ 的最短路，dijsktra 即可。
### Code
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<queue>
#define int long long
using namespace std;
int n,t;
struct nodev{
	int to;
	int wei;
};
struct nodeq{
	int to;
	int dis;
	bool operator < (const nodeq&a)const{
		return dis>a.dis;
	}
};
vector<nodev>vec[1000005];
int dis[1000005];
bool vis[1000005];
void dijkstra(){
	priority_queue<nodeq>q;
	for(int i=1;i<=t;i++)dis[i]=1e18;
	q.push((nodeq){0,0});
	while(!q.empty()){
		int u=q.top().to;
		q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(int i=0;i<vec[u].size();i++){
			int v=vec[u][i].to,w=vec[u][i].wei;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push((nodeq){v,dis[v]});
			}
		}
	}
}
signed main(){
	scanf("%lld %lld",&n,&t);
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%lld %lld",&x,&y);
		vec[x-1].push_back((nodev){y,1});
	}
	for(int i=1;i<=t;i++){
		vec[i].push_back((nodev){i-1,0});
	}
	dijkstra();
	if(dis[t]==1e18){
		puts("-1");
		return 0;
	}
	printf("%lld\n",dis[t]);
	return 0;
}
```


---

## 作者：Eric_jx (赞：2)

这里介绍一种最短路解法。

## 思路详解

对于每一个空闲区间，由 $S_i-1$ 连一条边权为 $1$ 的有向边指向 $E_i$，表示动用第 $i$ 头奶牛，此时能管理到 $E_i$ 这个时间点，显然代价为 $1$ 头奶牛。

对于每个时间点 $i$，连一条边权为 $0$ 的有向边指向 $i-1$，为了能够向左到达空闲区间内部的其余点或者到达另一个区间的时间点。

答案就是 $0$ 到 $n$ 的最短路，用 dijkstra 求解即可。

注意：链式前向星数组要开大一点。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int h[2000005],w[2000005],e[2000005],ne[2000005],dis[2000005],vis[2000005],cnt;
void add(int a, int b, int c) {
	e[++cnt]=b;
	w[cnt]=c;
	ne[cnt]=h[a];
	h[a]=cnt;
}
int n,m,s,t;
#define PI pair<int,int>
void dijkstra() {
	for(int i=0; i<=t; i++) {
		dis[i]=INT_MAX;
	}
	dis[s]=0;
	priority_queue<pair<int,int>, vector<pair<int,int> >,greater<pair<int,int> > > q;
	q.push({0,s});
	while(!q.empty()) {
		PI t=q.top();
		q.pop();
		int x=t.first;
		int y=t.second;
		if(vis[y]) {
			continue;
		}
		vis[y]=1;
		for(int i=h[y]; i!=-1; i=ne[i]) {
			if(dis[y]+w[i]<dis[e[i]]) {
				dis[e[i]]=dis[y]+w[i];
				q.push({dis[e[i]],e[i]});
			}
		}
	}
}
int main() {
	memset(h,-1,sizeof(h));
	cin>>n>>t;
	for(int i=1;i<=t;i++){
		add(i,i-1,0);
	}
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		add(x-1,y,1);
	}
	s=0;
	dijkstra();
	if(dis[t]==INT_MAX){
		cout<<"-1";return 0;
	}
	cout<<dis[t];
	return 0;
}
```

---

## 作者：_k_e_v_i_n_ (赞：1)

## 1.贪心

记 $end$ 为当前已有奶牛值班时段的结束时间，将数组按 $S_i$ 从小到大排序，然后寻找满足 $S_j \le end$ 时 $E_j$ 的最大值，将 $E_j$ 的最大值赋给 $end$，进行下一轮循环。如果有哪次找不到 $j$ 满足 $S_j \le end$ 了，就说明没有办法安排出合理的方案。

正确性证明：选择 $E_j$ 靠左的不会比选择 $E_j$ 靠右的更优，因为 $E_j$ 靠右的比 $E_j$ 靠左的更有可能满足 $S_j \le end$。

代码就不放了。

## 2.最短路

**这里使用 dijkstra 算法。**

- 将 $S_i$ 与 $E_i$ 建一条边权为 $1$ 的有向边，则样例可以画出这个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/bdgk6ot9.png)

- 对于每个时间点 $i$，有一条边权为 $0$ 的有向边指向 $i - 1$，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/9sx5d63d.png)

现在我们只需要求 $1 \sim n$ 的最短路就可以了。

**But，这是错的！**

来看这一组数据：

```
3 10
1 7
3 6
8 10
```

显然选第一头和第三头奶牛。

然而，如果按照上述方法，$1 \sim n$ 的最短路的值为 $\infty$。

解决方法：将所有的 $E_i$ 加 $1$（将所有的 $S_i$ 减 $1$ 也可以），这组数据可以画出下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/crd12trk.png)

显然求 $1 \sim n + 1$ 的最短路即可。

### Code

```
#include <bits/stdc++.h>
using namespace std;
int t, n, m, dis[2000005], vis[2000005];
struct node {
	int v, d;
	friend bool operator < (node x, node y) {
		return x.d > y.d;
	}
};
vector <node> g[1000005];
priority_queue <node> q;
void dij() {		//dijkstra 模板
	dis[1] = 0;
	q.push((node) {
		1, 0
	});
	while (!q.empty()) {
		node n1 = q.top();
		q.pop();
		if (!vis[n1.v]) {
			vis[n1.v] = 1;
			for (int v = 0; v < g[n1.v].size(); v++) {
				if (dis[n1.v] + g[n1.v][v].d < dis[g[n1.v][v].v]) {
					dis[g[n1.v][v].v] = dis[n1.v] + g[n1.v][v].d;
					q.push((node) {
						g[n1.v][v].v, dis[g[n1.v][v].v]
					});
				}
			}
		}
	}
}
int main() {
	cin >> n >> t;
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= n; i++) {
		int s, e;
		cin >> s >> e;
		g[s].push_back((node) {
			e + 1, 1
		});
	}
	for (int i = 2; i <= t + 1; i++) {
		g[i].push_back((node) {
			i - 1, 0
		});
	}
	dij();
	if (dis[t + 1] != 0x3f3f3f3f)	cout << dis[t + 1];
	else	cout << "-1";
	return 0;
}
```

---

## 作者：bloodstalk (赞：1)

## Description
有一长度为 $T$ 的区间。$N(1\le N\le 2.5\times 10^4)$ 个人。每个人能覆盖的区间是 $[S_i,E_i](1\le S_i\le E_i\le T)$，问最少需要几个人能把这个区间覆盖。无解输出 $-1$。

$1\le T\le 10^6,N\le 2.5\times 10^4,1\le S_i\le E_i\le T$。

## Solution
线段树优化 DP。

这题是 [P4644 [USACO05DEC] Cleaning Shifts S](https://www.luogu.com.cn/problem/P4644) 的弱化版，那道题每个人还需要一定的聘请费用，求的是覆盖的最小聘请费用，而这个题相当于每个人的聘请费用固定为 $1$。

我们设 $f_i$ 表示覆盖 $[1,i]$ 这个区间所需要的最小人数。 

为了便于转移，我们将每个人按照右端点 $E_i$ 递增排序，那么有状态转移方程：

$$
f_{E_i} = \min_{S_i-1\leq x < E_i}\{f_x\} + 1
$$

其实就是枚举是否能接起来，覆盖区间必须有交或者刚好相邻。

那我们就可以进行 DP 了，初值 $f_0= 0$，其余为 $\inf$。最终答案就是 $f_T$。

朴素 DP 是 $\mathcal O(NT)$ 的，我们考虑怎么优化。

我们观察状态转移方程，发现这其实是一个查询区间最小值的操作，并且会有修改操作，因为 $f$ 是在不断更新的。我们很自然的就能想出用线段树来解决这个问题，这样我们就可以在 $\mathcal O(\log T)$ 的时间内完成这个问题。时间复杂度 $\mathcal O(N\log T)$。

需要注意的一点是，我们是在 $[0,T]$ 上建立的线段树而并非 $[1,T]$，因为状态转移方程中左端点是 $S_i-1$。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define next nxt
#define re register
#define il inline
const int N = 1e6 + 5;
const int INF = 1e11;
using namespace std;
int max(int x,int y){return x > y ? x : y;}
int min(int x,int y){return x < y ? x : y;}

int n,R;
int f[N];
struct node{
	int l,r;
	int cost;
}a[N];
int tree[N<<2];

il int read()
{
	int f=0,s=0;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f |= (ch=='-');
	for(; isdigit(ch);ch=getchar()) s = (s<<1) + (s<<3) + (ch^48);
	return f ? -s : s;
}

#define lc p<<1
#define rc p<<1|1

il void build(int p,int l,int r)
{
	if(l == r)
	{
		tree[p] = INF;
		return ;
	}
	int mid = (l+r) >> 1;
	build(lc,l,mid) , build(rc,mid+1,r);
	tree[p] = min(tree[lc],tree[rc]);
}

il void Modify(int pos,int l,int r,int p,int k)
{
	if(l == pos && r == pos)
	{
		tree[p] = k;
		return ;
	}
	int mid = (l+r) >> 1;
	if(pos <= mid) Modify(pos,l,mid,lc,k);
	if(pos > mid) Modify(pos,mid+1,r,rc,k);
	tree[p] = min(tree[lc],tree[rc]);
}

il int Query(int nl,int nr,int l,int r,int p)
{
	int ans = INF;
	if(nl <= l && r <= nr) return tree[p];
	int mid = (l+r) >> 1;
	if(nl <= mid) ans = min(ans,Query(nl,nr,l,mid,lc));
	if(nr > mid) ans = min(ans,Query(nl,nr,mid+1,r,rc));
	return ans;
}

il bool cmp(node a,node b) { return a.r < b.r; }

signed main()
{
	n = read() , R = read();
	for(re int i=1;i<=n;i++)
	{
		a[i].l = read() , a[i].r = read();
		a[i].cost = 1;
	}
	sort(a+1,a+n+1,cmp);
	build(1,0,R);
	Modify(0,0,R,1,0);
	for(re int i=1;i<=R;i++) f[i] = INF;
	f[0] = 0;
	for(re int i=1;i<=n;i++)
	{
		int Min = Query(a[i].l-1,a[i].r-1,0,R,1);
		f[a[i].r] = min(f[a[i].r],Min + a[i].cost);
		Modify(a[i].r,0,R,1,f[a[i].r]);
	}
	if(f[R] == INF) cout << -1; else cout << f[R];
	return 0;
}
```

---

## 作者：technopolis_2085 (赞：0)

此题跟 [P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280) 有异曲同工之妙。

建议通过此题后再去做一下这题。


------------

分析：

我们首先特判掉 $-1$ 的情况。

考虑差分，如果第 $i$ 只奶牛值班，则 $S_i$ 到 $E_i$ 都有人值班。

所以可以 $sum_{S_i}$ 加 $1$，然后 $sum_{E_i+1}$ 减 $1$。

然后遍历一遍每个时间点，如果 $sum_i$ 等于 $0$，则说明第 $i$ 时刻无人值班，无法满足题意。此时输出 $-1$，并结束程序。

特判掉 $-1$ 后，考虑如何求解。

我们发现，对于第 $i$ 时刻，最后的结果只会与 $i$ 时刻的结果相关，无后效性，所以可以考虑 dp。

设 $dp_i$ 表示截止到 $i$ 时刻最少需要多少奶牛值班。

对于 $i$ 而言：

如果 $i$ 属于某只奶牛 $x$ 的休息时间，则说明 $[S_x,E_x]$ 都有人值班。所以对于区间内的每一个 $i$，都可以从 $dp_{S_x}-1$ 转移过来。

然后答案为 $dp_t$。

观察数据范围，如果对于每一个时间点 $i$，我们都枚举一遍所有奶牛，这样的话会超时。我们发现只需要枚举以 $i$ 为开头的奶牛。可以用 vector 存储每一头奶牛的值班时间。

开 O2 就过了。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+10;
vector<int> G[maxn];
int sum[maxn];
int dp[maxn];

int main(){
	int n,t;
	scanf("%d%d",&n,&t);
	
	for (int i=1;i<=t;i++) dp[i]=1e9+7;
	
	for (int i=1;i<=n;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		G[l].push_back(r);
		sum[l]++, sum[r+1]--;
	}
	
	for (int i=1;i<=t;i++){
		sum[i]+=sum[i-1];
		if (sum[i]==0){
			printf("-1\n");
			return 0;
		}
	}
	
	for (int i=1;i<=t;i++){
		for (int j=0;j<(int)G[i].size();i++){
			int r=G[i][j];
			
			for (int k=i;k<=r;k++) dp[k]=min(dp[k],dp[i-1]+1);
		}
		
	}
	
	printf("%d",dp[t]);
	return 0;
}
```



---

