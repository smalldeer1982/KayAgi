# Jumping Around

## 题目描述

There is an infinite pond that can be represented with a number line. There are $ n $ rocks in the pond, numbered from $ 1 $ to $ n $ . The $ i $ -th rock is located at an integer coordinate $ a_i $ . The coordinates of the rocks are pairwise distinct. The rocks are numbered in the increasing order of the coordinate, so $ a_1 < a_2 < \dots < a_n $ .

A robot frog sits on the rock number $ s $ . The frog is programmable. It has a base jumping distance parameter $ d $ . There also is a setting for the jumping distance range. If the jumping distance range is set to some integer $ k $ , then the frog can jump from some rock to any rock at a distance from $ d - k $ to $ d + k $ inclusive in any direction. The distance between two rocks is an absolute difference between their coordinates.

You are assigned a task to implement a feature for the frog. Given two integers $ i $ and $ k $ determine if the frog can reach a rock number $ i $ from a rock number $ s $ performing a sequence of jumps with the jumping distance range set to $ k $ . The sequence can be arbitrarily long or empty.

You will be given $ q $ testcases for that feature, the $ j $ -th testcase consists of two integers $ i $ and $ k $ . Print "Yes" if the $ i $ -th rock is reachable and "No" otherwise.

You can output "YES" and "NO" in any case (for example, strings "yEs", "yes", "Yes" and 'YES"' will be recognized as a positive answer).

## 说明/提示

Explanation of the first example:

In the first testcase the destination rock is the same as the starting rock, thus no jumps are required to reach it.

In the second testcase the frog can jump any distance in the range $ [5 - 2; 5 + 2] $ . Thus, it can reach rock number $ 5 $ (by jumping $ 7 $ to the right) and rock number $ 3 $ (by jumping $ 3 $ to the left). From rock number $ 3 $ it can reach rock number $ 2 $ (by jumping $ 5 $ to the left). From rock number $ 2 $ it can reach rock number $ 1 $ (by jumping $ 4 $ to the left). However, there is no way to reach rock number $ 7 $ .

In the third testcase the frog can jump any distance in the range $ [5 - 3; 5 + 3] $ . Thus, it can reach rock number $ 7 $ by jumping to rock $ 5 $ first and to $ 7 $ afterwards.

The fourth testcase is shown in the explanation for the second testcase.

## 样例 #1

### 输入

```
7 4 4 5
1 5 10 13 20 22 28
4 1
7 2
7 3
3 2```

### 输出

```
Yes
No
Yes
Yes```

## 样例 #2

### 输入

```
10 8 6 11
1 2 4 7 8 9 11 13 19 20
2 13
5 8
8 1
6 15
1 15
2 7
7 6
8 9```

### 输出

```
Yes
Yes
No
Yes
Yes
Yes
Yes
Yes```

## 样例 #3

### 输入

```
6 9 6 6
1 2 4 9 18 19
2 17
1 18
5 4
2 11
5 17
6 8
4 3
3 3
6 6```

### 输出

```
Yes
Yes
Yes
Yes
Yes
Yes
No
No
Yes```

## 样例 #4

### 输入

```
4 1 1 10
1 8 10 19
2 1```

### 输出

```
Yes```

# 题解

## 作者：Cry_For_theMoon (赞：13)

[传送门](https://codeforces.ml/contest/1550/problem/F)

D，E，F的 difficulty 是不是乱打的啊

应该是比较水的 2700* 了。

##### 题意：

给定若干个点的坐标 $a_1<a_2<...<a_n$ 还有常数 $d$. 如果参数为 $k$，则一次可以跳跃 $t-k \sim t+k$ 的距离.

$q$ 次询问，每次给定终点 $ed$ 和参数 $k$，询问能否从起点 $st$（固定点，一开始给出）跳到 $ed$ 点。

$n \le 2\,\times 10^5,q,a_i \le 10^6.$

##### 分析：

容易发现一个基本性质：

若 $st \rightarrow ed$ 在 $k$ 为参数时可行，则在 $k+1$ 为参数时一定也行。换言之跳跃范围满足**单调性**。

但是由于本来就是若干判定性问题所以不太可能利用单调性二分。考虑跳跃，可达性，容易让人想到图论连边。

由于满足单调性，我们对所有 $(i,j)$ 连边，边权是 $i$ 直接跳到 $j$ 所需要的最小的参数值 $w$. 根据单调性，只要 $st \rightarrow ed$ 有一条路径，满足路径最大权值小于等于给定的 $k$ 就有解；反之无解。

~~$n^2$ 级别边数（不可做）+ 有特点的边权 = 可做题(暴论)~~

容易发现边权 $w$ 应该设为 $||a_i-a_j|-d|$.  再有进一步的做法之前我们先不动这个式子。

”路径最大权值“小于等于给定的 $k$. 就是 2013 提高组那道经典的货车运输，即最小瓶颈生成树。已经烂大街的一个 trick 就是，最小生成树上，任意两点之间唯一路径上边权最大值，一定是整张图上，这两点之间任意路径上边权最大值的最小值。如果还不会，可以去先看看货车运输，或者[这题](https://www.luogu.com.cn/problem/P2245) .

那么我们就是要求一个 $O(n^2)$ 级别的，每两点的边权都是一个关于这两个点的一次的式子的，一张图的生成树（莫名想到去年B卷的丁香之路）。这个时候就可以拆式子分析了：
$$
w=\begin{cases}|a_i-a_j-d|,i>j \\
|a_j-a_i-d|=|a_i+d-a_j|,i\le j
\end{cases}
$$
仅差在了 $d$ 的正负（更近一步的化简就比较麻烦了所以先不拆完，直接考虑此时的做法）。

点数边数都是 $O(n^2)$ 所以直接 kruskal / prim 是不行的。考虑 boruvka 算法：

每轮对于每个连通块找到其最短的连向其它连通块的边，全部找完以后把这些边两端的连通块全部合并。

这个算法只会执行 $O(\log n)$ 次，重点是每次找到每个连通块连向其它连通块的边。

显然我们把每个连通块放在一起考虑，对于上面 $w$ 的式子，容易发现 $j$ 是非该连通块中的点中，$a_j$ 距离 $a_i+d$ 或者 $a_i-d$ 最近的，容易想到二分，但是这样无法处理 $j$ 与 $i$ 不在同一连通块的限制，考虑 lower_bound 还可以放在 set 上，同时它也支持快速的插入删除。所以每次处理连通块的时候先把该连通块的点从 set 中删去，处理完再加入即可。至于二分的时候，要考虑 $a_j$ 是小于还是大于它要“最近”的那个值。所以我们维护两个 set，一个从小到大一个反之，这样就比较方便。

最烦的找边完成了，剩下的合并就都是平凡的了。总复杂度为 $O(n \log^2 n)$. 由于出题人良心所以不需要进一步优化（不会）是可以直接过去的。

最优解倒数第一位，唯一的总时间超过 $1$min，比倒数第二慢了一倍的 code：

```c++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=2e5+10;
ll n,q,st,d,ed,k;
ll a[(int)1e6+10],fa[MAXN],num[(int)1e6+10];
ll nxt[MAXN];
pi gnxt[MAXN];
vector<ll>group[MAXN];
vector<pair<ll,ll>>e[MAXN];
set<ll>s1;
set<ll,greater<ll>>s2;
ll maxw[MAXN];
ll getdis(int x,int y){return abs(d-abs(a[x]-a[y]));}
int Find(int x){
	if(fa[x]==x)return x;
	return fa[x]=Find(fa[x]);
}
void Merge(int x,int y){
	if(Find(x)==Find(y))return;
	fa[Find(y)]=Find(x);
	e[x].pb(mp(y,getdis(x,y)));
	e[y].pb(mp(x,getdis(x,y)));
}
int check(){
	rep(i,2,n)if(Find(1)!=Find(i))return 1;
	return 0;
}
void check(int x,int y){
	if(!nxt[x])nxt[x]=y;
	else if(getdis(x,y) < getdis(x,nxt[x]))nxt[x]=y;
}
void dfs(int u,int fa){
	for(vector<pair<ll,ll>>::iterator it=e[u].begin();it!=e[u].end();it++){
		pair<ll,ll>nxt=*it;
		if(fa==nxt.fr)continue;
		maxw[nxt.fr]=max(maxw[u],nxt.se);
		dfs(nxt.fr,u);
	}
}
int main(){
	cin>>n>>q>>st>>d;
	rep(i,1,n){
		cin>>a[i];
		num[a[i]]=i;
		fa[i]=i;
		s1.is(a[i]);
		s2.is(a[i]);
	}
	while(check()){
		rep(i,1,n){nxt[i]=0;gnxt[i]=mp(0,0);group[i].clear();}
		rep(i,1,n){group[Find(i)].pb(i);}
		rep(i,1,n){
			int sz=group[i].size();
			rep(j,0,sz-1){
				s1.erase(a[group[i][j]]);
				s2.erase(a[group[i][j]]);
			}
			rep(j,0,sz-1){
				//u<v
				if(s1.lower_bound(a[group[i][j]]+d)!=s1.end()){
					ll v=*s1.lower_bound(a[group[i][j]]+d);
					v=num[v];
					if(group[i][j]<v)check(group[i][j],v);
				}
				if(s2.lower_bound(a[group[i][j]]+d)!=s2.end()){
					ll v=*s2.lower_bound(a[group[i][j]]+d);
					v=num[v];
					if(group[i][j]<v)check(group[i][j],v);
				}
				//u>v 
				if(s1.lower_bound(a[group[i][j]]-d)!=s1.end()){
					ll v=*s1.lower_bound(a[group[i][j]]-d);
					v=num[v];
					if(group[i][j]>v)check(group[i][j],v);
				}
				if(s2.lower_bound(a[group[i][j]]-d)!=s2.end()){
					ll v=*s2.lower_bound(a[group[i][j]]-d);
					v=num[v];
					if(group[i][j]>v)check(group[i][j],v);
				}
				//更新
				if(gnxt[i].se==0 || getdis(gnxt[i].fr,gnxt[i].se)>getdis(group[i][j],nxt[group[i][j]]))gnxt[i]=
				mp(group[i][j],nxt[group[i][j]]); 
			}
			rep(j,0,sz-1){
				s1.is(a[group[i][j]]);
				s2.is(a[group[i][j]]);
			}
		}
		rep(i,1,n){
			if(gnxt[i].se==0)continue;
			int u=gnxt[i].fr,v=gnxt[i].se;
			Merge(u,v);
		}
	}
	dfs(st,0);
	rep(i,1,q){
		cin>>ed>>k;
		if(maxw[ed]<=k)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```





 

---

## 作者：Saliеri (赞：6)

写在前面：本篇题解的重点是第三种做法。前面的两种做法如果有漏洞烦请指出。（因为伞兵作者自己并没有去实现/lengh）

感谢 @滑奆稽 对这个即将退役的菜鸡作者的指导。

___

做法一：纯线段树，$O(n\log n)$。（作者未实现）

很容易想到的一个思路如下：按照 $k$ 升序处理所有询问，维护当前与 $s$ 相连的连通块信息。

可以发现，我们只要能保证我们的（数据结构）操作次数**只与扩展连通块的次数**有关，我们的复杂度就是正确的。

- 换言之，每次扫一遍连通块试图扩展到新点是错的，扫新点同理。

那么我们换一种想法维护——对于每一个不在连通块中的点，**维护最小的能使得其连入连通块的 $k$**。 

考虑加点的影响。设点 $p$ 刚被加入了连通块，此时的操作应当是——两个中心点分别为 $a_p-d$,$a_p+d$ 的 **“谷”状的对一次函数取 $\min$**。

注意到一次函数的斜率只有 $\pm1$，于是我们开两颗线段树后维护最小的 $b$ 也可以达到相同的效果。（$b$ 指 $kx+b$ 中的 $b$）

考虑回答询问。对于每一个询问重复以下过程：取出线段树中最小值，如果其 $\le k$，那就将这个位置删除（赋值为 $+\text{inf}$），在并查集中加入连通块，进行更新操作。显然线段树操作只有 $O(n)$ 次，于是总复杂度 $O(n\log n)$。


~~但是有点难写，常数也有点大~~。同时也不好处理 $s$ 不固定的情况。

___

做法二：Boruvka 求 MST。$O(n\log^2 n)$。

考虑使得 $s\to t$ 的边存在的最小 $k$（$\min(|a_s+d-a_t|,|a_s-d-a_t|$），我们不妨将这个值设为 $s,t$ 间的**边权**。

那么这就变成了一个图上问题。我们从上面的扩展连通块的思路抽出身来，考虑另外一种等价的问题问法：

- $k$ 至少要多大才能使得 $s,t$ 连通？或者换言之，$s,t$ **所有路径上的最大边权的最小值是多少？**

~~完了 dna 动了~~。于是这是简单的**瓶颈路问题**，广为人知的结论是答案就是 MST 上两点路径上最大边权。

- 回答询问还是需要离线使得 $k\uparrow$，求出 MST 过后对 MST 上边也排序，双指针即可。

问题变成求**完全图 MST**，广为人知的套路是考虑 Boruvka。

问题变成对于每一个点，求终点与它不在同一个连通块中的最小边。

处理 “不在同一连通块” 考虑正反扫连通块序列，分别计算前缀贡献。用 set 维护值域即可支持最小值查询。

Boruvka 1log，set 1log，于是复杂度 $O(n\log ^2 n)$。

这个做法非常可！但是 Boruvka 太难写了！还有没有更劲爆的啊？（迫真）

___

做法三：奇技淫巧求完全图 MST，$O(n\log^2 n)$。

（听说是）常见的 trick：完全图的 MST 可以考虑**分治**，求每次分治得到的完全二分图的 MST，然后将边集并起来跑 Kruskal，$O(n\log^2 n)$。

- 正确性口胡：考虑一条不是任意一个完全二分图的 MST 中的边。考虑 Kruskal 的过程，它绝无可能被加入原图 MST。

完全二分图 MST 怎么做？~~Boruvka！~~ 不 Boruvka 没法做。

考虑，我们可以不求出 MST。我们可以考虑求出一个**与点数同阶的 MST 的超集**。

- 具体地，对于每一个左部点 $p$，连向右边 $a_p+d$ 的前驱后继；右边同理连向左边 $a_p-d$ 的前驱后继。

我们需要证明这是 MST 的超集。

- 连通性：
	- 考虑将左部点的 $a_p+d$，右部点的 $a_p$ 升序放一个序列中。（当然左部 $a_p$，右部 $a_p-d$ 也是这个序列）
    - 考虑极长的左部右部连续段，内部必然连通，因为都连向同一个前驱或者后继。
    - 每一个连续段间必然在边界处连通。证毕。

- 包含 MST：类似于上面，考虑 Kruskal 的过程。 

好写，好调，好理解，不毒瘤，跑得快。大家快来写！

upd：
考虑将维克曲儿二分换成双指针，排序用鸡排就可以让这个做法也达到 $O(n\log n)$。

upd2：

- 首先，鸡排是不需要的，因为值域够小桶排就行。

- 其次，我们其实后面那一边 Kruskal 是不需要跑的。因为用 MST 的超集双指针并不影响正确性。
___

做法三的代码：

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
const int maxn = 2e5+5;
int n,m,S,D,a[maxn],ans[maxn],ecnt;
struct E{int x,y,z;}e[maxn*25],mst[maxn];
std :: vector <int> V;
void lnk(int p,int s,int l){
	auto it = std::lower_bound(V.begin(),V.end(),p);int P = it-V.begin();
	if(it != V.end())e[++ecnt] = (E){s,l+P,*it-p};
	if(it != V.begin())--it,e[++ecnt] = (E){s,l+P-1,p-*it};
}
void Div(int l,int r){
	if(l != r){
		int mid = l+r>>1;
		Div(l,mid);for(int i=mid+1;i<=r;++i)lnk(a[i]-D,i,l);
		Div(mid+1,r);for(int i=l;i<=mid;++i)lnk(a[i]+D,i,mid+1);
	}
	V.clear();for(int i=l;i<=r;++i)V.push_back(a[i]);
}
struct DSU{
	int fa[maxn];
	void init(){for(int i=1;i<=n;++i)fa[i] = i;}
	int getfa(int x){return fa[x] == x ? x : fa[x] = getfa(fa[x]);}
	void merge(int x,int y){x = getfa(x),y = getfa(y),fa[x] = y;}
}dsu;
void Kruskal(){
	auto cmp = [](E a,E b){return a.z<b.z;};
	std :: sort(e+1,e+ecnt+1,cmp);
	int cnt = 0;dsu.init();
	for(int i=1;cnt<n-1;++i){
		int fx = dsu.getfa(e[i].x),fy = dsu.getfa(e[i].y);
		if(fx != fy)dsu.fa[fx] = fy,mst[++cnt] = e[i];
	}
	std :: sort(mst+1,mst+cnt+1,cmp);
}
struct Q{int k,t,id;}q[maxn];
int main(){
	scanf("%d %d %d %d",&n,&m,&S,&D);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	Div(1,n),Kruskal();
	for(int i=1;i<=m;++i)scanf("%d %d",&q[i].t,&q[i].k),q[i].id = i;
	std :: sort(q+1,q+m+1,[](Q a,Q b){return a.k<b.k;}),dsu.init();
	for(int i=1,j=1;i<=m;++i){
		while(j<n&&mst[j].z<=q[i].k)dsu.merge(mst[j].x,mst[j].y),++j;
		ans[q[i].id] = (dsu.getfa(S) == dsu.getfa(q[i].t));
	}
	for(int i=1;i<=m;++i)puts(ans[i]?"Yes":"No");
	return 0;
}
```


---

## 作者：Purslane (赞：5)

# Solution

考虑两个点（我们直接用位置表示点）的边权为 $||u-v|-k|$，求出最小生成树，然后预处理某个节点到其他所有点简单路径边权的最大值。

所以关键在于如何求最小生成树。

考虑使用 Boruvka 求最小生成树。Boruvka 的好处就是我们可以每次操作的时候把所有点扫一遍。

于是我们可以在每次合并的过程中维护每个数向左和向右第一个不在联通块的位置，然后用双指针扫一遍做到线性。

复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,q,s,d,cnt,dep[MAXN],a[MAXN],fa[MAXN],l[MAXN],r[MAXN],pos[MAXN],len[MAXN],nw[MAXN],ori[MAXN],val[MAXN];
vector<pair<int,int>> G[MAXN];
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
void init(void) {
	ffor(i,1,n) if(find(i-1)!=find(i)) l[i]=i-1; else l[i]=l[i-1];
	roff(i,n,1) if(find(i+1)!=find(i)) r[i]=i+1; else r[i]=r[i+1];
	return ;	
}
void update(int id,int Id) {
	if(id==Id||Id==0||Id>n) return ;
	assert(find(id)!=find(Id));
	if(pos[id]==-1) return pos[id]=Id,len[id]=abs(abs(a[id]-a[Id])-d),void();
	if(abs(abs(a[id]-a[pos[id]])-d)>abs(abs(a[id]-a[Id])-d)) pos[id]=Id;
	len[id]=min(len[id],abs(abs(a[id]-a[Id])-d));
	return ;	
}
void dfs(int u,int f) {
	for(auto pr:G[u]) {
		int v=pr.first,w=pr.second;
		if(v==f) continue;
		dep[v]=max(dep[u],w);
		dfs(v,u);	
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q>>s>>d,cnt=n;
	ffor(i,1,n) fa[i]=i,cin>>a[i];
	while(cnt>1) {
		init();
		memset(pos,-1,sizeof(pos)),memset(len,0x3f,sizeof(len));
		int id=1;
		ffor(i,1,n) {
			while(id<n&&a[id]<=a[i]+d) id++;
			if(find(id)!=find(i)) update(i,id);	
			else update(i,l[id]),update(i,r[id]);
			if(find(id+1)!=find(i)) update(i,id+1);	
			else update(i,l[id+1]),update(i,r[id+1]);
			if(find(id-1)!=find(i)) update(i,id-1);	
			else update(i,l[id-1]),update(i,r[id-1]);
		}
		id=n;
		roff(i,n,1) {
			while(id>1&&a[id]>=a[i]-d) id--;
			if(find(id)!=find(i)) update(i,id);	
			else update(i,l[id]),update(i,r[id]);
			if(find(id+1)!=find(i)) update(i,id+1);	
			else update(i,l[id+1]),update(i,r[id+1]);
			if(find(id-1)!=find(i)) update(i,id-1);	
			else update(i,l[id-1]),update(i,r[id-1]);
		}
		memset(val,0x3f,sizeof(val));
		ffor(i,1,n) if(len[i]<val[find(i)]) val[find(i)]=len[i],nw[find(i)]=pos[i],ori[find(i)]=i;	
		ffor(i,1,n) if(val[i]!=val[0]) {
			if(find(ori[i])!=find(nw[i])) cnt--,G[ori[i]].push_back({nw[i],val[i]}),G[nw[i]].push_back({ori[i],val[i]});
			fa[find(ori[i])]=find(nw[i]);
		}
	}
	dfs(s,0);
	ffor(i,1,q) {
		int id,k; cin>>id>>k;	
		if(dep[id]<=k) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：wind_whisper (赞：5)

## $\text{Foreword}$
"Boruvka 算法有什么用啊？"

“这题你看看呢？”

“呃 prim 好像过了...呃怎么 Boruvka 还是两个 $\log$ 的...”

洛谷和 CF 题解都说 prim 不行，这里介绍一个好想好写的单 $\log$ prim 做法。

感觉不是什么高妙做法，肯定有人想到过了，但没有写题解吧（

（upd：Boruvka 不用 `set` 改成扫一遍也可以是单 $\log$，但感觉还是没有 prim 好写）

## $\text{Solution}$
首先把询问离线，按灵活程度排序，做最小生成树的过程中处理询问。

维护当前尚未与起点连通的集合 $lft$，每次从 $lft$ 选出 $dis$ 最小的点 $x$，如何更新其它 $dis$？

一个朴素的思想：用 $x-d,x+d$ 在 $lft$ 里找找前驱后继，更新其 $dis$。（为了方便，称 $x-d,x+d$ 这样的点为“落脚点”，已经合并的点产生的所有落脚点集合为 $s$）

但显然直接这么做有问题，比如某个落脚点 $y$ 找到的前驱为 $pre$，那么当 $pre$ 从 $lft$ 删除时，$y$ 需要重新在 $lft$ 集合里找前驱。

解决方法也很简单，每次从 $lft$ 里取出 $dis$ 最小的点 $x$ 的时候，让 $x$ 在 $s$ 集合找找前驱后继，让它们重新在 $lft$ 里面找一下前驱后继并更新 $dis$ 就好了。

实现可以直接维护两个 `std::set`，每次 `set` 中的操作次数都是 $O(1)$ 的，总复杂度也就是 $O(n\log n)$。

## $\text{Code}$
~~退役人懒得分讨了直接暴力处理常数死大~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("ok\n")
inline ll read(){
	ll x(0),f(1);char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return f*x;
}

const int N=2e5+100;
const int inf=1e9;

int n,m,ss,d;
struct query{	
	int k,i,id;
	bool operator < (const query &oth)const{return k<oth.k;}
}qq[N];
int a[N];
int ans[N];
#define It set<int>::iterator
set<int>lft,s;
#define pr pair<int,int>
#define mkp make_pair 
priority_queue<pr,vector<pr>,greater<pr> >q;
inline int Pre(const set<int>&s,int x){
	It it=s.lower_bound(x);
	--it;
	return *it;
}
inline int Suf(const set<int>&s,int x){
	It it=s.lower_bound(x);
	return *it;
}
inline void ins(int x){
	s.insert(x);
	int pre=Pre(lft,x);
	int suf=Suf(lft,x);
	//printf("ins: %d pre=%d suf=%d\n",x,pre,suf);
	if(pre>=-2e6){
		q.push(mkp(x-pre,pre));
	}
	if(suf<=2e6){
		q.push(mkp(suf-x,suf));
	}
}
inline void link(int x){
	lft.erase(x);
	int pre=Pre(s,x);
	int suf=Suf(s,x);
	if(pre>=-2e6) ins(pre);		
	if(suf<=2e6) ins(suf);
	ins(x-d);
	ins(x+d);
}
bool vis[N*10];

int main() {
    s.insert(inf);
   	s.insert(-inf);
   	lft.insert(inf);
   	lft.insert(-inf);
   	n=read();m=read();ss=read();d=read();
   	for(int i=1;i<=n;i++){
   		a[i]=read();
   		lft.insert(a[i]);
	}   
   	ss=a[ss];
   	for(int i=1;i<=m;i++){
   		qq[i].i=a[read()];qq[i].k=read();
   		qq[i].id=i;
	}
	int st=1;
	sort(qq+1,qq+1+m);
	q.push(mkp(0,ss));
	int ttt=0;
	for(int qwq=1;qwq<=n;qwq++){
		pr o=q.top();q.pop();
		//printf("x=%d w=%d\n",o.second,o.first);
		if(vis[o.second]){
			//return 0;
			++ttt;
			//if(ttt==1000) return 0;
			qwq--;continue;
		}
		while(st<=m&&qq[st].k<o.first){
			ans[qq[st].id]=vis[qq[st].i];
			st++;
		}
		vis[o.second]=1;
		link(o.second);
	}
	while(st<=m){
		ans[qq[st].id]=vis[qq[st].i];
		st++;
	}
	for(int i=1;i<=m;i++){
		if(ans[i]) puts("Yes");
		else puts("No");
	}
    return 0;
}
```


---

## 作者：2huk (赞：2)

第一次做出 *2700 的题，而且没用半小时。

如果想从第 $i$ 个石头跳到第 $j$ 个石头，$k$ 应该至少是 $||a_j-a_i|-d|$。

于是我们建一张完全图，$i,j$ 间的边权为 $||a_j-a_i|-d|$，那么一次 $(i, k)$ 的询问，等价于存在某条 $s \rightsquigarrow i$ 的路径，使得每条边的边权都 $\le k$。这等价于找一条 $s \rightsquigarrow i$ 的路径使得最大边权最小。

[经典结论](https://www.luogu.com.cn/problem/P1967)，求出原图的最小生成树，那么这个东西等于树上 $s,i$ 的唯一路径上的边权最大值。

最小生成树用 B 开头那个算法就行了。

---

## 作者：WrongAnswer_90 (赞：2)

[更好的阅读体验](https://www.cnblogs.com/WrongAnswer90-home/p/17956940)

[CF1550F Jumping Around](https://www.luogu.com.cn/problem/CF1550F)

提供一个不用动脑子的方法。

首先题目可以看成是求一个点到 $s$ 的最小瓶颈路，设这个值为 $v_i$，自然想到最小生成树，但是边数是 $\mathcal O(n^2)$ 的，不可接受。

考虑使用 prim，一开始联通块力只有一个点 $s$，每次新加入距离联通快距离最小的一个点，问题在于如何找到全局最小值。

直接求肯定没有前途，考虑加入一个点对其他点 $v_i$ 的贡献：

$$
v_j=\min(v_j,\max(v_i,\min(|a_j-(a_i-d)|,|a_j-(a_i+d)|)))
$$

然后可以把 $\max$ 和绝对值暴力拆开，可以变成区间 $v_i=\min(v_i,x-a_i)$ 和 $v_i=\min(v_i,x+a_i)$ 和 $v_i=\min(v_i,x)$。图大概就是这样的：

![捕获.PNG](https://s2.loli.net/2024/01/10/UGbzQWiH7xhElCk.png)

线段树维护区间 $a_i$ 最大值最小值，当前 $v_i$ 最小值及其位置即可，每次找到最小值的位置更新真实的 $v_i$ 然后删掉这个位置，复杂度 $\mathcal O(n\log n+m)$。常数也不算大。

```cpp
	int n,m,S,d,v[200010],a[200010];
	namespace Segment
	{
		struct{int l,r,tg1,tg2,tg3;pii mina,maxa,minn;}t[800010];
		inline pii chkmin(pii p1,pii p2){if(!~p2.se)return p1;if(!~p1.se)return p2;return p1.fi<p2.fi?p1:p2;}
		inline pii chkmax(pii p1,pii p2){if(!~p2.se)return p1;if(!~p1.se)return p2;return p1.fi>p2.fi?p1:p2;}
		inline void update(int p)
		{
			t[p].mina=chkmin(t[p*2].mina,t[p*2+1].mina);
			t[p].maxa=chkmax(t[p*2].maxa,t[p*2+1].maxa);
			t[p].minn=chkmin(t[p*2].minn,t[p*2+1].minn);
		}
		inline void down1(int p,int x)
		{
			Mmin(t[p].tg1,x);
			if(x+t[p].mina.fi<t[p].minn.fi)t[p].minn=mp(x+t[p].mina.fi,t[p].mina.se);
		}
		inline void down2(int p,int x)
		{
			Mmin(t[p].tg2,x);
			if(x-t[p].maxa.fi<t[p].minn.fi)t[p].minn=mp(x-t[p].maxa.fi,t[p].maxa.se);
		}
		inline void down3(int p,int x){Mmin(t[p].tg3,x),Mmin(t[p].minn.fi,x);}
		inline void spread(int p)
		{
			if(t[p].tg1!=inf)down1(p*2,t[p].tg1),down1(p*2+1,t[p].tg1);
			if(t[p].tg2!=inf)down2(p*2,t[p].tg2),down2(p*2+1,t[p].tg2);
			if(t[p].tg3!=inf)down3(p*2,t[p].tg3),down3(p*2+1,t[p].tg3);
			t[p].tg1=t[p].tg2=t[p].tg3=inf;
		}
		void build(int p,int l,int r)
		{
			t[p].l=l,t[p].r=r,t[p].tg1=t[p].tg2=t[p].tg3=inf;
			if(l==r)return t[p].mina=t[p].maxa=mp(a[l],l),t[p].minn=mp(inf,l),void();
			int mid=l+((r-l)>>1);
			build(p*2,l,mid),build(p*2+1,mid+1,r),update(p);
		}
		void change(int p,int x)
		{
			if(t[p].l==t[p].r)
			return t[p].mina=mp(inf,-1),t[p].maxa=mp(-inf,-1),t[p].minn=mp(inf,-1),void();
			spread(p);
			if(x<=t[p*2].r)change(p*2,x);else change(p*2+1,x);
			update(p);
		}
		void modify1(int p,int l,int x)
		{
			if(l<=t[p].l)return down1(p,x);
			spread(p),modify1(p*2+1,l,x);
			if(l<=t[p*2].r)modify1(p*2,l,x);
			update(p);
		}
		void modify2(int p,int r,int x)
		{
			if(r>=t[p].r)return down2(p,x);
			spread(p),modify2(p*2,r,x);
			if(r>t[p*2].r)modify2(p*2+1,r,x);
			update(p);
		}
		void modify3(int p,int l,int r,int x)
		{
			if(l<=t[p].l&&r>=t[p].r)return down3(p,x);
			spread(p);
			if(l<=t[p*2].r)modify3(p*2,l,r,x);
			if(r>t[p*2].r)modify3(p*2+1,l,r,x);
			update(p);
		}
		void print(int p)
		{
			if(t[p].l==t[p].r)return write(t[p].minn.fi,' ');
			spread(p),print(p*2),print(p*2+1);
		}
	}
	using namespace Segment;
	inline void mian()
	{
		read(n,m,S,d);int x,y;
		for(int i=1;i<=n;++i)read(a[i]);
		build(1,1,n),memset(v,127,sizeof(v)),change(1,S),v[S]=0;
		for(int i=1;i<=n;++i)
		{
			int pos1=lower_bound(a+1,a+1+n,a[S]-d-v[S])-a;
			int pos2=upper_bound(a+1,a+1+n,a[S]-d+v[S])-a-1;
			if(pos1<=pos2&&pos1>=1&&pos2<=n)
			modify3(1,pos1,pos2,v[S]);
			if(pos1-1)modify2(1,pos1-1,a[S]-d);
			if(pos2<n)modify1(1,pos2+1,d-a[S]);
			pos1=lower_bound(a+1,a+1+n,a[S]+d-v[S])-a;
			pos2=upper_bound(a+1,a+1+n,a[S]+d+v[S])-a-1;
			if(pos1<=pos2&&pos1>=1&&pos2<=n)
			modify3(1,pos1,pos2,v[S]);
			if(pos1-1)modify2(1,pos1-1,d+a[S]);
			if(pos2<n)modify1(1,pos2+1,-d-a[S]);
			v[S=t[1].minn.se]=t[1].minn.fi,change(1,S);
		}
		while(m--)read(x,y),puts(y<v[x]?"No":"Yes");
	}
```

---

## 作者：jr_linys (赞：2)

[CF1550F Jumping Around](https://www.luogu.com.cn/problem/CF1550F)

来一个  $O(n\log n)$ 的 Boruvka。

从 $i$ 到 $j$ 需要的灵活程度为 $||a_i-a_j|-d|$，自然建一个最小生成树就行。

对于点 $i$，$dis(i,j)$ 最小且 $i,j$ 不在一个连通块。  
则 $a_j$ 为不与 $i$ 在同一连通块的点集中离 $a_i-d$ 或 $a_i+d$ 最近的。

预处理对每个点左/右边第一个不同连通块的点，双指针分讨一下即可。

最后一遍 Dfs。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
template<typename T=int>
T read(){
	char c;bool f=1;
	while(!isdigit(c=getchar())) if(c=='-') f=0;
	T x=c^'0';
	while(isdigit(c=getchar())) x=x*10+(c^'0');
	return f?x:-x;
}
template<class T>int Min(T &a,T b){return b<a? a=b:a;}
template<class T>int Max(T &a,T b){return b>a? a=b:a;}
template<class T>void readi(T *s){
	char c;
	while(!isdigit(c=getchar()));
	for(*s=c-'0';isdigit(c=getchar());) *(++s)=c-'0';
}
const int N=2e5,iINF=1<<30;
int n,q,s,d,a[N+5];
int dis(pii x){
	return abs(abs(a[x.first]-a[x.second])-d);
}
int fa[N+5];
int find(int x){
	return fa[x]?fa[x]=find(fa[x]):x;
}
pii ml[N+5];
vector<pii> e[N+5];
void boruvka(){
	int resl=n-1;//剩余边数
	while(resl){
		fill(ml+1,ml+1+n,pii{0,1});//重置连通块的最小边
		static int le[N+5],ri[N+5];
		for(int i=1;i<=n;++i)
			if(find(i)==find(i-1)) le[i]=le[i-1];//左边第一个不同连通块
		else le[i]=i-1;
		for(int i=n;i;--i)
			if(find(i)==find(i+1)) ri[i]=ri[i+1];//右边边第一个不同连通块
		else ri[i]=i+1;
		for(int i=1,l=1,r=1;i<=n;++i){
			while(a[l]<a[i]-d) ++l;
			while(a[r]<a[i]+d) ++r;
			pii &L=ml[find(i)];
			auto upd=[&](int p){
				if(p==0||n<p) return;
				pii x={i,p};
				if(dis(x)<dis(L)) L=x;
				return;
			};
			if(find(i)==find(l)) upd(le[l]),upd(ri[l]);
			else upd(find(i)==find(l-1)?le[l-1]:l-1),upd(l);
			if(find(i)==find(r)) upd(le[r]),upd(ri[r]);
			else upd(find(i)==find(r-1)?le[r-1]:r-1),upd(r);
		}
		for(int i=1;i<=n;++i) if(!fa[i]){
			const int u=ml[i].first,v=ml[i].second,w=dis(ml[i]);
			if(find(u)!=find(v)){
				fa[find(u)]=find(v);
				e[u].push_back({v,w});
				e[v].push_back({u,w});
				--resl;
			}
		}
	}
}
int ans[N+5];
void dfs(int u,int fa){
	for(pii E:e[u]) if(E.first!=fa){
		Max(ans[E.first],max(ans[u],E.second));
		dfs(E.first,u);
	}
}

int main(){
	n=read(),q=read(),s=read(),d=read();
	a[0]=-iINF,a[n+1]=iINF;//垃圾桶（
	for(int i=1;i<=n;++i) a[i]=read();
	boruvka();
	dfs(s,0);
	while(q--){
		int u=read(),k=read();
		puts(ans[u]<=k?"yEs":"nO");
	}
}
```

---

## 作者：pigstd (赞：2)

#### [CF1550F](https://codeforces.ml/contest/1550/problem/F)

考虑对于每个结点 $i$ 算出最小的满足条件的 $k$，记为 $d_i$。

对于两个结点 $u,v$，如果 $u$ 可以直接到 $v$，那么 $k=|d-|a_u-a_v||$。对于所有的 $(u,v)$ 连一条 $|d-|a_u-a_v||$ 的边，那么 $s \to i$ 的最小满足条件的 $k$ 就是最小的 $k$ 满足存在 $s \to i$ 的路径且每条边的边权不大于 $k$。

根据最小生成树的性质，实际上建出最小生成树后，$d_i$ 就是 $s \to i$ 的路径中最大的权值，这意味着我们需要找到这个最小生成树。

边数为 $n^2$ 级别的，直接使用 kruskal 和 prim 显然会超时，可以使用另外一种最小生成树算法：boruvka 。

这个东西就是维护每个联通块，然后对于每次迭代，对于每个联通块找到他连出去的最小的边，然后全部找完之后合并。因为每次联通块的次数会至少减半，所以迭代的次数是 $\log n$ 级别的。

虽然边数仍然是 $n^2$ 级别，但是对于联通块的每一个点 $u$，只要快速找到联通块以外最小的边，即 $|d-|a_u-a_v|||$ 最小。

- $a_u < a_v$，即 $|d+a_u-a_v|$ 最小，即 $a_v$ 最接近于 $a_u+d$。
- $a_u \ge a_v$，即 $|d-a_u+a_v|=|a_u-d-a_v|$ 最小，即 $a_v$ 最接近于 $a_u-d$。

那么利用一个 `set` 维护所有的点，对于每个联通块，先删去这个联通块中的所有点，然后再遍历所有点，用 `lower_bound` 快速找到最接近于上面两个数的点，然后在遍历完成后连上最小的边就可以，然后就可以在 $\mathcal{O}(n \log^2 n)$ 的时间复杂度内找到最小生成树。

然后再按照上面所说的在这个树上 `dfs` 一次即可。

[AC link](https://codeforces.ml/contest/1550/submission/122587603)。

---

## 作者：luogubot (赞：1)

- 数轴上顺次有 $n$ 个点 $a_1 < a_2 < \cdots < a_n$。
- 有一只小青蛙，初始时在 $a_s$ 处。小青蛙有两个参数：步长 $d$ 和灵活程度 $k$。其中，步长 $d$ 是确定的，而灵活程度 $k$ 是可以调整的。
- 小青蛙可以从某个点跳到另一个点。但这是有要求的：小青蛙能从 $a_i$ 跳到 $a_j$，当且仅当 $d-k\leq |a_i-a_j|\leq d+k$。
- 给定 $a_1,...,a_n$ 和 $d$。你需要回答 $q$ 次询问，每次询问给定一个灵活程度 $k$ 和一个下标 $i$，你需要回答：此时的小青蛙能否跳到 $a_i$？
- 保证 $1\leq n,q\leq 2\times 10^5$，$1\leq s,i\leq n$，$1\leq a_i,d,k\leq 10^6$，$a_1 < a_2 < \cdots < a_n$。

初步分析，认为模型是最短路，即求出到每个 $a_i$ 所需的 $k_{\min}$，但是发现转移实际上需要的 $k$ 是 **路径上每条边对应 $k$ 的最大值**，所以其实是一个 Kruskal 重构树模型。

现在面临的问题实际上是一个 **完全图 MST**，常见的做法有 Boruvka 算法，先考虑这个怎么做。其实就是要求每个点（不方便对于连通块整体考虑）连出去的最短非同色边，也就是在 $a_i+d,a_i-d$ 找到前驱后继中第一个和自己不同色的，那么第一个辅助工具是 **并查集启发式合并+线段树维护区间内颜色的 $\min,\max$ 并支持线段树二分**，这样就能做到 2log，但是瓶颈有一个启发式合并+线段树单点修改，还有一个 Boruvka+线段树二分，常数较大；另一个易于实现得多的做法就是，每轮把每个点所属连通块编号写成序列，只需要找某个位置向前向后第一个不同色的，那么维护一个全局可用点的 `std::set`，对于每个颜色先删掉其中所有这个颜色的点，再对每个该色点进去找对应位置的前驱后继，完事再重新塞回去，这样的复杂度也是 2log，复杂度瓶颈只有 Boruvka+set 一处，但是  set 的常数也比较大。

另外，完全图 MST 还有一个分治求法：求 $G=(V,E)$ 的 MST，把 $V$ 划分为 $S,T$，只保留 $S,T$ 之间的 MST 需要的边（丢掉 Kruskal 过程中一定不会被使用的边），然后再保留 $S,T$ 内部的 MST，这些边一定包含原图的 MST。注意这个过程是可以递归处理的，除非能方便地求出 $S,T$ 内部的 MST。同时，求出之间 MST 的超集也是可以的。在本题中，可以证明，对于每个 $i\in S$，找到 $a_i+d$ 前后第一个和自己不同点集的点之间的边并保留，对每个 $j$ 找 $a_j-d$ 的前驱后继，这 $2n$ 条边一定是 MST 的超集。用这种方法找到的边足够小，因为根据 Kruskal 的过程，如果证明了连通性，那么更远的边权值更大一定会被丢掉。连通性的证明考虑把 $i\in S$ 的 $a_i+d$ 和 $j\in T$ 的 $a_j$ 放在一起排序，那么对于相同类型的一段 $i$，其找到的 $j$ 是同一个；$a_i$ 和 $a_j-d$ 也是同一个序列，那么同一段 $j$ 找到的 $i$ 也是同一个，所以内部联通，相邻段连通，整图联通。依然是 2log，但是常数比较小。复杂度瓶颈之一在于把找到的 $O(n\log n)$ 条边排序并建立 Kruskal 重构树/最小生成树，可以桶排+离线双指针维护连通性，可以拓展到 $s$ 不固定的情况；另一个瓶颈是如何快速对每个 $i$ 找到对应的 $j$，发现按照上面的流程归并就好了，这样比 2log 难写一些，但是做到了 1log。[Submission](https://codeforces.com/contest/1550/submission/204185717)

---

## 作者：囧仙 (赞：1)

只要对于每个 $i$，求出一个到达它的最小灵活程度 $t_i$ 就可以 $O(1)$ 回答所有询问
   
考虑进行整体二分，现在有一些点，我们知道它们的 $t_i$ 在 $[L,R]$ 之间，我们希望知道每个点的 $t_i$ 与 $m = \dfrac{L+R}{2}$ 的大小关系
   
考虑哪些点的 $t_i \le m$，可以发现有两类情况
   
- 1. 在 $k = m$ 的情况下，这个点直接可以跳到某个 $t_i < L$  的点
   
- 2. 在 $k = m$ 的情况下，这个点可以到达某个点集内已经被确认可行的点
   
事实上由于整体二分的过程，我们在处理 $[L,R]$ 时已经确定了哪些点 $t_i < L$，所以 1. 是简单的。我们直接用一个 `set`，称为 $P$，里面存储所有 $t_i < L$ 的点的位置，然后二分一下即可

我们把由于 1. 可行的点存储在一个 `vector` 里面，把当前还不可行的点存储在一个 `set` 里面

然后我们每次从 `vector` 取出一个元素，用它去尝试更新 `set` 内的点，如果这样使得一些点可行了，就把这些点从 `set` 里面删掉，然后放入 `vector`

最终 `vector` 被清空了，那么我们就知道了哪些点的 $t_i$ 在 $[L,m]$ 间，哪些点的 $t_i$ 在 $[m+1,R]$ 间，递归处理即可

注意：在处理完 $[L,m]$ 后，我们要把 $t_i$ 在 $[L,m]$ 的点加入 $P$，然后再处理 $[m+1,R]$

```cpp
#include <cstdio>
#include <set>
#include <vector>
using namespace std;
int n,q,s,d;
int a[200005],t[200005];

struct node{
	int id,val;
};

set <int> P;
set <int>::iterator it;
set <node> Q;
set <node>::iterator iter;

bool operator <(node a,node b){
	return a.val < b.val;
}

void solve(vector <int> S,int L,int R){
	vector <int> t1,t2;
	t1.clear();
	t2.clear();
	if(L == R){
		for(int i = 0;i < S.size();i++){
			t[S[i]] = L;
			P.insert(a[S[i]]);
		}
		return;
	}
    int m = (L + R) / 2;
    for(int i = 0;i < S.size();i++) Q.insert({S[i],a[S[i]]});
    for(int i = 0;i < S.size();i++){
        int id = S[i];
        it = P.lower_bound(a[id] - (d + m));
        if(it != P.end() && (*it) <= a[id] - d + m){
            t1.push_back(id);
            Q.erase({id,a[id]});
            continue;
        }
        it = P.lower_bound(a[id] + d - m);
        if(it != P.end() && (*it) <= a[id] + d + m){
        	t1.push_back(id);
        	Q.erase({id,a[id]});
        }
    }
    while(!t1.empty()){
    	int id = t1.back();
    	t1.pop_back();
    	iter = Q.lower_bound({0,a[id] - (d + m)});
    	while(iter != Q.end() && (iter->val) <= a[id] - d + m){
    		t1.push_back(iter->id);
    		iter = Q.erase(iter);
    	}
    	iter = Q.lower_bound({0,a[id] + d - m});
    	while(iter != Q.end() && (iter->val) <= a[id] + d + m){
    		t1.push_back(iter->id);
    		iter = Q.erase(iter);
    	}
    }
    for(int i = 0;i < S.size();i++){
    	if(Q.count({S[i],a[S[i]]})){
    		t2.push_back(S[i]);
    	}else{
    		t1.push_back(S[i]);
    	}
    }
    solve(t1,L,m);
    solve(t2,m+1,R);
}

int main(){
    scanf("%d%d%d%d",&n,&q,&s,&d);
    for(int i = 1;i <= n;i++) scanf("%d",&a[i]);
    t[s] = 0;
    P.insert(a[s]);
    vector <int> tmp;
    tmp.clear();
    for(int i = 1;i <= n;i++) if(i != s) tmp.push_back(i);
    solve(tmp,0,1000000);
    //for(int i = 1;i <= n;i++) printf("%d ",t[i]);
    //printf("\n");
    for(int i = 1;i <= q;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
    	if(y >= t[x]) printf("Yes\n");
    	else printf("No\n");
    }
	return 0;
}
```


---

## 作者：Mashu77 (赞：0)

所有答案在 
$[
l
,
r
]$
 的点。我们只需要将这些点分为 $[l,
m
i
d
]$
 与 
$(
m
i
d
,
r
]$
 的两部分，递归解决即可。并由单调性，等价于根据 
$k=
m
i
d$
 时的可达与否分组。

此时答案在 
$[0,l)$ 的点已经存在，利用他们更新 $k=
m
i
d$
 时能跳到的点。

待考虑的点有两种方式更新：

1. 由 
$[
0
,
l
)$
 的一步跳到
 
 2. 由第一种点跳到。第一种用 set 即可；第二种可以用队列和 set（类似广搜）。这样的方式可以保证 
$O
(
n
\log^
2
n
)$
 的复杂度。
 
 ```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a),i##END=(b);i<=i##END;i++)
#define Rof(i,b,a) for(int i=(b),i##END=(a);i>=i##END;i--)
#define go(u) for(int i=head[u];i;i=nxt[i])
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
bool ST;
const int N=2e5+10,M=1e6+10,LG=18;
int n,q,s,d,a[N],fa[N],ans[N];
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
void merge(int x,int y){fa[get(x)]=get(y);}
#define pi pair<int,int>
#define fi first
#define se second
int head[M],nxt[N*LG*3],cnt;pi to[N*LG*3];
void add(int u,pi v){to[++cnt]=v,nxt[cnt]=head[u],head[u]=cnt;}
pi tmp[N],t[N];int tp;
void solve(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	solve(l,mid),solve(mid+1,r);
	For(i,l,mid)t[i]=pi(a[i]+d,-i);For(j,mid+1,r)t[j]=pi(a[j],j);
	merge(t+l,t+mid+1,t+mid+1,t+r+1,tmp+1);int tp=r-l+1;
	For(i,1,tp)t[i]=tmp[i];
	For(T,1,2){
		int lstS=0,lstT=0;
		for(int i=1,j;i<=tp;i=j+1){
			j=i;while(j<tp&&(t[j+1].se>0)==(t[i].se>0))j++;
			if(t[i].se>0){
				if(lstT)For(k,i,j)add(abs(t[k].fi-t[lstT].fi),pi(t[k].se,-t[lstT].se));
				lstS=j;
			}else{
				if(lstS)For(k,i,j)add(abs(t[k].fi-t[lstS].fi),pi(-t[k].se,t[lstS].se));
				lstT=j;
			}
		}reverse(t+1,t+tp+1);
	}
}
bool ED;
signed main(){
	fprintf(stderr,"%.2lf MB\n",abs(&ED-&ST)/1024.0/1024.0);
	n=read(),q=read(),s=read(),d=read();
	For(i,1,n)a[i]=read(),fa[i]=i;
	For(i,1,q){int u=read(),k=read();add(k,pi(-i,u));}
	solve(1,n);
	For(t,0,M-10){
		go(t){
			auto x=to[i];
			if(x.fi>0)merge(x.fi,x.se);
			else ans[-x.fi]=get(s)==get(x.se);
		}
	}For(i,1,q)puts(ans[i]?"Yes":"No");
	return 0;
}
```

---

## 作者：cirnovsky (赞：0)

题不错，但是花了很久啊，完全比不过贺题怪。

答案有单调性，转化求每个点被跳到所需的最小 $k_i$，容易想到用整体二分维护一个有 $s$ 的连通块，每次拓展的时候就考虑在值域范围内的点能不能在 $k$ 取 $(l+r)/2$ 的时候跳出去。具体而言，就是看能不能以 $k=(l+r)/2$ 跳到 $k_i<l$ 的点上（1）。

但是这样会少点，因为值域范围内的点能够跳出去，而值域范围内有些不能跳出去的点可以藉由这些点间接跳出去（2）。

现在的问题就是如何维护（1）类点。我们在执行整体二分的时候先递归左子树，这样跑到叶子的时候把叶子加入一个数据结构（`std::set` is enough），这样我们递归到后面的结点时数据结构中存放的就是所有的（1）类点，跑完（1）类点再把值域范围内剩下的点依次判断能否间接跳出去即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;
int n, Q, st, d, a[200100], ans[200100], q[200100];
int q1[200100], q2[200100];
set<int> s;
void solve(int l, int r, int lq, int rq) {
    if (l == r) {
        for (int i=lq; i<=rq; ++i) {
            ans[q[i]] = l;
            s.insert(a[q[i]]);
        }
        return;
    }
    set<P> now;
    for (int i=lq; i<=rq; ++i) {
        now.emplace(a[q[i]], q[i]);
    }
    int mid = (l+r)/2, tl = 0, tr = 0;
    for (int i=lq; i<=rq; ++i) {
        auto it = s.lower_bound(a[q[i]]-d-mid);
        if (it != s.end() && (*it) <= a[q[i]]-d+mid) {
            q1[++tl] = q[i];
            now.erase(P(a[q[i]], q[i]));
        }
        else {
            it = s.lower_bound(a[q[i]]+d-mid);
            if (it != s.end() && (*it) <= a[q[i]]+d+mid) {
                q1[++tl] = q[i];
                now.erase(P(a[q[i]], q[i]));
            }
        }
    }
    for (int i; tl;) {
        i = q1[tl--];
        auto it = now.lower_bound(P(a[i]-d-mid, 0));
        while (it != now.end() && it->first <= a[i]-d+mid) {
            q1[++tl] = it->second;
            it = now.erase(it);
        }
        it = now.lower_bound(P(a[i]+d-mid, 0));
        while (it != now.end() && it->first <= a[i]+d+mid) {
            q1[++tl] = it->second;
            it = now.erase(it);
        }
    }
    tl = 0;
    for (int i=lq; i<=rq; ++i) {
        if (now.count(P(a[q[i]], q[i]))) {
            q2[++tr] = q[i];
        }
        else {
            q1[++tl] = q[i];
        }
    }
    for (int i=1; i<=tl; ++i) q[lq+i-1] = q1[i];
    for (int i=1; i<=tr; ++i) q[lq+tl+i-1] = q2[i];
    solve(l, mid, lq, lq+tl-1);
    solve(mid+1, r, lq+tl, rq);
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> Q >> st >> d;
    int cnt = 0;
    for (int i=1; i<=n; ++i) {
        cin >> a[i];
        if (i != st) {
            q[++cnt] = i;
        }
    }
    s.insert(a[st]);
    solve(0, 1e6, 1, cnt);
    for (int i, k; Q--;) {
        cin >> i >> k;
        if (ans[i] <= k) {
            cout << "yEs\n";
        }
        else {
            cout << "nO\n";
        }
    }
    return 0;
}
```

---

## 作者：Mihari (赞：0)

# 题目描述

[传送门 to Luogu](https://www.luogu.com.cn/problem/CF1550F).

# [题解](https://www.cnblogs.com/Arextre/p/15032161.html)

首先明白，如果你想从 $i$ 跳到 $j$，那么你需要的修正值为
$$
w_{ij}=|d-|a_i-a_j||
$$
如果我们想从 $s$ 走到 $t$，假设我们经过的路径为 $\{p_0,p_1,p_2,...,p_x|p_0=s,p_x=t\}$，那么我们需要的修正值即为
$$
req_t=\max_{i=1}^n w_{p_{i-1}p_i}
$$
然后比较 $req_t$ 与它给的 $k$ 即可，如果 $k<req_t$，那么答案为 $\tt nO$，否则为 $\tt yEs$.

现在问题变成，如何求 $req_t$？

我们可以将 $w_{ij}$ 看成一条边，那么，现在我们面临的就是一张有 $n$ 个点，$n(n-1)\over 2$ 条边的图，现在，我们想要从给定起点 $s$ 到某个点的经过的最大边最小，这不难让我们想到了二分答案。

不过，这又是另一个问题 —— 二分答案之后，如何检查？一个比较普遍的想法就是，将所有权小于等于 $mid$ 的边连接的两个点暴力合并到一个并查集中，最后看 $s,t$ 是否在同一个并查集中即可。

但是这样做，似乎二分答案有点多于，我们可以直接贪心地将当前权最小的边连接的俩点加入同一个并查集中，某个时刻 $s,t$ 位于同一个并查集时，最后加入的这条边就是答案。

但是这样做有两个问题：

- 边最多达到 $n^2$ 级别；
- 每个询问都反复加边实在太重复；

我们重新思考上面的过程，发现它似乎和最小生成树比较相似，我们从生成树方向考虑。

我们将第一次连接两个并查集的边保留，不难发现它最后就会是一个最小生成树，而从 $s$ 到某个 $t$ 所需的修正值就是树上从 $s$ 到 $t$ 的路径中经过的最大边的权。

于是，我们现在的目的是 —— 如何快速地求出原图的 “最小生成树”；

如果是使用普遍的 $\rm Prim$ 或者 $\rm Kruskal$ 似乎都比较困难，前者因为复杂度为 $\mathcal O((|V|+|E|)\log |V|)$，而 $m$ 较大，后者也是因为需要对 $|E|={n(n-1)\over 2}$ 条边进行排序，复杂度也不那么好看，我们得找一种更先进的，可以将边的数量降下来的方法。

此处，我们需要一种名为 $\rm Boruvka$ 的最小生成树算法，它的复杂度为 $\mathcal O(|E|\log |V|)$，但是它的好处在于 —— 在已知什么边最优的情况，我们可以不用将所有的边都求出来。更强地，它甚至可以解决一些二进制生成树问题，而广大 $\rm OIer$ 都深感其优势。

![img](https://z3.ax1x.com/2021/07/19/WJjUAA.png)

~~（不知道如何打码，就手动上一个了）~~

其具体过程可以这样描述：（以下内容摘自 [**OI Wiki**](https://oi-wiki.org/)）

>为了描述该算法，我们需要引入一些定义：
>
>1. 定义 $E'$ 为我们当前找到的最小生成森林的边。在算法执行过程中，我们逐步向 $E'$ 加边，定义 **连通块** 表示一个点集 $V'\subseteq V$，且这个点集中的任意两个点 $u,v$， 在 $E'$ 中的边构成的子图上是连通的（互相可达）。
>2. 定义一个连通块的 **最小边** 为它连向其它连通块的边中权值最小的那一条。
>
>初始时，$E'=\emptyset$，每个点各自是一个连通块：
>
>1. 计算每个点分别属于哪个连通块。将每个连通块都设为“没有最小边”。
>2. 遍历每条边 $(u,v)$，如果 $u$ 和 $v$ 不在同一个连通块，就用这条边的边权分别更新 $u$ 和 $v$ **所在连通块**的最小边。
>3. 如果所有连通块都没有最小边，退出程序，此时的 $E'$ 就是原图最小生成森林的边集。否则，将每个有最小边的连通块的最小边加入 $E'$，返回第一步。
>
>下面是伪代码：
>$$
>\begin{array}{ll} 1 & \textbf{Input. } \text{A graph }G\text{ whose edges have distinct weights. } \\ 2 & \textbf{Output. } \text{The minimum spanning forest of }G . \\ 3 & \textbf{Method. } \\ 4 & \text{Initialize a forest }F\text{ to be a set of one-vertex trees} \\ 5 & \textbf{while } \text{True} \\ 6 & \qquad \text{Find the components of }F\text{ and label each vertex of }G\text{ by its component } \\ 7 & \qquad \text{Initialize the cheapest edge for each component to "None"} \\ 8 & \qquad \textbf{for } \text{each edge }(u, v)\text{ of }G \\ 9 & \qquad\qquad \textbf{if } u\text{ and }v\text{ have different component labels} \\ 10 & \qquad\qquad\qquad \textbf{if } (u, v)\text{ is cheaper than the cheapest edge for the component of }u \\ 11 & \qquad\qquad\qquad\qquad\text{ Set }(u, v)\text{ as the cheapest edge for the component of }u \\ 12 & \qquad\qquad\qquad \textbf{if } (u, v)\text{ is cheaper than the cheapest edge for the component of }v \\ 13 & \qquad\qquad\qquad\qquad\text{ Set }(u, v)\text{ as the cheapest edge for the component of }v \\ 14 & \qquad \textbf{if }\text{ all components'cheapest edges are "None"} \\ 15 & \qquad\qquad \textbf{return } F \\ 16 & \qquad \textbf{for }\text{ each component whose cheapest edge is not "None"} \\ 17 & \qquad\qquad\text{ Add its cheapest edge to }F \\ \end{array}
>$$

十分佩服 $\text{OI Wiki}$ 的同志直接使用 $\LaTeX$ 而不用任何宏包书写伪代码，这让我有了[共产主义](https://www.cnblogs.com/Arextre/p/15005336.html)的空间。

值得注意的是，在伪代码中，有两句判断是
$$
\begin{aligned}
\textbf{if } (u, v)\text{ is cheaper than the cheapest edge for the component of }u \\
\textbf{if } (u, v)\text{ is cheaper than the cheapest edge for the component of }v
\end{aligned}
$$
如果我们可以直接找到这样的边，那是最好不过。

显然，对于一个点 $u$，如果它连接的另一个集合的点与 $a_u\pm d$ 差最小，那么所需的修正值也越小，那么我们可以直接使用 $\tt lower\_bound()$ 在一个储存了坐标的 $\tt set$ 中解决问题，这样我们就不需要枚举一个点连出去的所有边了。

然后，我们就可以实现代码了，代码中有一些细节，自己康康罢。

该算法的复杂度应该是 $\mathcal O(|V|\log^2|V|)$ 的罢。当然，如果你可以不使用 $\tt set$，应该是可以降低至 $\mathcal O(|V|\log|V|)$ 的。注意，启发式合并的 $\mathcal O(|V|\log|V|)$ 是独立的，不和 $\rm Boruvka$ 算法的主体部分相乘。至于你问哪里用到了启发式合并，看看代码罢。

# 参考代码


```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;

// #define NDEBUG
#include<cassert>

namespace Elaina{
    #define rep(i, l, r) for(int i=(l), i##_end_=(r); i<=i##_end_; ++i)
    #define drep(i, l, r) for(int i=(l), i##_end_=(r); i>=i##_end_; --i)
    #define fi first
    #define se second
    #define mp(a, b) make_pair(a, b)
    #define Endl putchar('\n')
    #define mmset(a, b) memset(a, b, sizeof a)
    // #define int long long
    typedef long long ll;
    typedef unsigned long long ull;
    typedef pair<int, int> pii;
    typedef pair<ll, ll> pll;
    template<class T>inline T fab(T x){ return x<0? -x: x; }
    template<class T>inline void getmin(T& x, const T rhs){ x=min(x, rhs); }
    template<class T>inline void getmax(T& x, const T rhs){ x=max(x, rhs); }
    template<class T>inline T readin(T x){
        x=0; int f=0; char c;
        while((c=getchar())<'0' || '9'<c) if(c=='-') f=1;
        for(x=(c^48); '0'<=(c=getchar()) && c<='9'; x=(x<<1)+(x<<3)+(c^48));
        return f? -x: x;
    }
    template<class T>inline void writc(T x, char s='\n'){
        static int fwri_sta[1005], fwri_ed=0;
        if(x<0) putchar('-'), x=-x;
        do fwri_sta[++fwri_ed]=x%10, x/=10; while(x);
        while(putchar(fwri_sta[fwri_ed--]^48), fwri_ed);
        putchar(s);
    }
}
using namespace Elaina;

const int maxn=2e5;
const int inf=0x3f3f3f3f;

struct edge{
    int u, v, w;
    inline bool operator <(const edge rhs) const{
        return w<rhs.w;
    }
};

set<int>plane;
vector< vector<int> >compo;
vector<int>a, fa, refl;

inline int findrt(int u){
    return fa[u]==u? u: fa[u]=findrt(fa[u]);
}
inline bool merge(int u, int v){
    u=findrt(u), v=findrt(v);
    if(u==v) return 0;
    if(compo[u]<compo[v]) swap(u, v);
    for(int x: compo[v]){
        compo[u].push_back(x);
        fa[refl[x]]=u;
    }
    compo[v].clear();
    return 1;
}

int n, q, s, d;

inline void input(){
    n=readin(1), q=readin(1), s=readin(1)-1, d=readin(1);
    fa.resize(n), a.resize(n);
    for(int i=0; i<n; ++i){
        fa[i]=i, a[i]=readin(1);
        plane.insert(a[i]);
    }
}

vector<pii>g[maxn+5]; int req[maxn+5];
inline void add_edge(int u, int v, int w){
    g[u].push_back({v, w}); g[v].push_back({u, w});
}
void dfs(int u, int par, int mx){
    req[u]=mx;
    for(pii e: g[u]) if(e.fi!=par)
        dfs(e.fi, u, max(mx, e.se));
}

signed main(){
    input();
    compo.resize(n), refl=vector<int>(a[n-1]+1);
    for(int i=0; i<n; ++i){
        compo[i]=vector<int>(1, a[i]);
        refl[a[i]]=i;
    }
    int cnt=n;
    while(cnt>1){
        vector<edge>Es; edge mn;
        for(auto cur: compo) if(!cur.empty()){
            mn={-1, -1, inf};
            for(int x: cur) plane.erase(x);
            for(int x: cur){
                for(int dir: {-d, d}){
                    auto it=plane.lower_bound(x+dir);
                    if(it!=plane.end()) mn=min(mn, {refl[x], refl[*it], fab(d-fab(x-(*it)))});
                    if(it!=plane.begin()){
                        --it;
                        mn=min(mn, {refl[x], refl[*it], fab(d-fab(x-(*it)))});
                    }
                }
            }
            for(int x: cur) plane.insert(x);
            Es.push_back(mn);
        }
        for(auto e: Es) if(merge(e.u, e.v))
            --cnt, add_edge(e.u, e.v, e.w);
    }
    dfs(s, -1, -1);
    while(q--){
        int i=readin(1)-1, k=readin(1);
        if(req[i]<=k) printf("yEs\n");
        else printf("nO\n");
    }
    return 0;
}
```
                     

# 扩展

还记得上文提到的 *更强地，它甚至可以解决一些二进制生成树问题* 吗？这里有一道题，就是这样的问题（当然被一些妹妹用子集切掉了）。

[传送门 to *新年的繁荣*](https://www.cnblogs.com/Arextre/p/15032259.html).


---

