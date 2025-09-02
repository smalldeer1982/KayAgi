# Counter Attack

## 题目描述

Berland has managed to repel the flatlanders' attack and is now starting the counter attack.

Flatland has $ n $ cities, numbered from $ 1 $ to $ n $ , and some pairs of them are connected by bidirectional roads. The Flatlandian maps show roads between cities if and only if there is in fact no road between this pair of cities (we do not know whether is it a clever spy-proof strategy or just saving ink). In other words, if two cities are connected by a road on a flatland map, then there is in fact no road between them. The opposite situation is also true: if two cities are not connected by a road on a flatland map, then in fact, there is a road between them.

The berlanders got hold of a flatland map. Now Vasya the Corporal is commissioned by General Touristov to find all such groups of flatland cities, that in each group of cities you can get from any city to any other one, moving along the actual roads. Also the cities from different groups are unreachable from each other, moving along the actual roads. Indeed, destroying such groups one by one is much easier than surrounding all Flatland at once!

Help the corporal complete this task and finally become a sergeant! Don't forget that a flatland map shows a road between cities if and only if there is in fact no road between them.

## 说明/提示

In the first sample there are roads only between pairs of cities 1-4 and 2-3.

In the second sample there is no road between cities 1 and 2, but still you can get from one city to the other one through city number 3.

## 样例 #1

### 输入

```
4 4
1 2
1 3
4 2
4 3
```

### 输出

```
2
2 1 4 
2 2 3 
```

## 样例 #2

### 输入

```
3 1
1 2
```

### 输出

```
1
3 1 2 3 
```

# 题解

## 作者：xuanxuan001 (赞：2)

虽然这题我做得比较复杂，但还是写一篇吧。

这题我看完后想了很久，最后突然想到了生成树，虽然还没完全想出来，但觉得应该可以做。逻辑问题很多，肝了应该不下两小时，交了 11 发。

正文
-
最后的大致思路是顺序枚举每个点 $i$，然后枚举所有的 $j > i$ 且 $i$ 与 $j$ 还没有联通。如果它们之间有边连接，那么就将这条边加上，并将 $i$ 和 $j$ 所在联通块联通。这样可以保证每对给出没有连边的点都会被访问至多一次。

然后就是在判断两个点是否有边时不能直接将给出点集加入一个 set 然后查询，这样复杂度多一个 $\log$，虽然算起来也不会 T，但我的常数比较大。需要在枚举 $i$ 时处理出一个布尔数组，其中的第 $j$ 个表示 $i$ 与 $j$ 有没有连边，这样就能 $O(1)$ 查询了。

还有就是逻辑问题，必须将每种情况的点对不重不漏地遍历到，否则要么就会 T 要么就会 WA。我是把所有的联通块用一个并查集维护的同时也维护了一个不路径压缩的树，编号最大的作为根，所有边都是编号较大的作为父亲。然后将所有根节点放到一个 set 里，这样每次枚举 $j$ 的时候只要将除 $i$ 所在树以外的所有树都 dfs 一遍即可，然后只要遍历到 $j \le i$ 的情况就直接退出 dfs，因为它的所有儿子的编号都是小于它的。

代码
-
```
#include<cstdio>
#include<vector>
#include<set>
#define Ty int
#define MAXN 500002
#define FOR(i,a,b) for(Ty i=a;i<=b;++i)
#define fOR(i,a,b) for(Ty i=a;i<b;++i)
#define ROF(i,a,b) for(Ty i=a;i>=b;--i)
#define rOF(i,a,b) for(Ty i=a;i>b;--i)
using namespace std;
typedef long long ll;
const Ty M=998244353;
typedef unsigned long long ull;
Ty _abs(Ty a){return a<0?-a:a;}
Ty maxn(Ty a,Ty b){return a>b?a:b;}
Ty minn(Ty a,Ty b){return a<b?a:b;}
Ty gcd(Ty a,Ty b){return b?gcd(b,a%b):a;}
Ty qp(Ty a,Ty b){Ty ans=1;for(;b;b>>=1){if(b&1)ans=ans*a%M;a=a*a%M;}return ans;}
Ty qr(){
	char ch=getchar();Ty s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';
	return x*s;
}Ty n,m,u,v,fa[MAXN],head[MAXN],nxt[MAXN],sz[MAXN],ans;
void addedge(Ty u,Ty v){nxt[v]=head[u];head[u]=v;}
set<Ty>lft;set<Ty>::iterator it;
vector<Ty>sd[MAXN];bool hv[MAXN];
Ty getfa(Ty u){return fa[u]^u?fa[u]=getfa(fa[u]):u;}
bool dfs(Ty now,Ty x){
	if(!hv[now])return true;
	for(Ty i=head[now];i;i=nxt[i])
		if(i>x&&dfs(i,x))return true;
	return false;
}
int main(){
	ans=n=qr();m=qr();FOR(i,1,n)lft.insert(fa[i]=i);//一开始所有点都是根 
	FOR(i,1,m){
		u=qr();v=qr();if(u>v)u^=v^=u^=v;sd[u].push_back(v);
	}FOR(i,1,n){
		v=getfa(i);it=lft.end();
		fOR(j,0,sd[i].size())hv[sd[i][j]]=true;//对每个点记录与 i 有没有连边 
		for(--it;;--it){
			if(*it<=i)break;
			if((*it^v)&&dfs(*it,i)){//如果有连边
				if((u=*it)<v){
					++it;--ans;lft.erase(u);//注意删除 set 中的元素时指向它的 iterator 会失效，需要先移开 
					addedge(fa[u]=v,u);
				}else{
					--ans;lft.erase(v);
					addedge(fa[v]=u,v);v=u;
				}
			}if(it==lft.begin())break;
		}fOR(j,0,sd[i].size())hv[sd[i][j]]=false;
	}printf("%d",ans);FOR(i,1,n)head[i]=0;
	FOR(i,1,n)if(fa[i]^i){addedge(getfa(i),i);++sz[fa[i]];}
	FOR(i,1,n)if(fa[i]==i){
		printf("\n%d %d",sz[i]+1,i);
		for(Ty j=head[i];j;j=nxt[j])printf(" %d",j);
	}return 0;
}
```

---

## 作者：灵茶山艾府 (赞：2)

考察这 $m$ 对点中，出现次数最少的点 $v$，由于「**最小值不会超过平均值**」，$v$ 的出现次数 $\leq \frac{2m}{n}$，即与点 $v$ 相连的边至多被删除了 $\frac{2m}{n}$ 条。

举例来说，当 $n=1000,\ m=10000$ 时，与点 $v$ 相连的点有 $999$ 个，由于至多被删除了 $20$ 条边，即至少还剩 $979$ 个点与点 $v$ 相连。这意味着仅仅考察点 $v$，我们就找到了一个大小至少为 $980$ 的连通分量。

对于剩余的 $20$ 个点，暴力遍历求取该点所属的联通分量即可。

综上所述，若使用路径压缩和按秩合并的并查集（复杂度视作常数），总的复杂度为构造点 $v$ 的联通分量的开销 $O(n)$，加上遍历剩余点的开销 $O(\frac{2m}{n}*n)$，即 $O(n+m)$。

AC 代码（Golang）：

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	_i, buf := 1<<12, make([]byte, 1<<12)
	rc := func() byte {
		if _i == 1<<12 {
			os.Stdin.Read(buf)
			_i = 0
		}
		b := buf[_i]
		_i++
		return b
	}
	r := func() (x int) {
		b := rc()
		for ; '0' > b; b = rc() {
		}
		for ; '0' <= b; b = rc() {
			x = x*10 + int(b&15)
		}
		return
	}

	n, m := r(), r()
	g := make([][]int, n)
	for ; m > 0; m-- {
		v, w := r()-1, r()-1
		g[v] = append(g[v], w)
		g[w] = append(g[w], v)
	}

	maxDeg, maxDegV := 0, 0
	for v, edges := range g {
		if deg := n - 1 - len(edges); deg > maxDeg {
			maxDeg, maxDegV = deg, v
		}
	}
	if maxDeg == 0 {
		Fprintln(out, n)
		for i := 1; i <= n; i++ {
			Fprintln(out, 1, i)
		}
		return
	}

	fa := make([]int, n)
	for i := range fa {
		fa[i] = i
	}
	var find func(int) int
	find = func(x int) int {
		if fa[x] != x {
			fa[x] = find(fa[x])
		}
		return fa[x]
	}
	mergeV := func(v int, edges []int) {
		has := map[int]bool{v: true}
		for _, w := range edges {
			has[w] = true
		}
		for i := 0; i < n; i++ {
			if !has[i] {
				fa[find(i)] = find(v)
			}
		}
	}
	mergeV(maxDegV, g[maxDegV])
	for v, edges := range g {
		if find(v) != find(maxDegV) {
			mergeV(v, edges)
		}
	}

	cnt := map[int][]interface{}{}
	for i := range fa {
		v := find(i)
		cnt[v] = append(cnt[v], i+1)
	}
	Fprintln(out, len(cnt))
	for _, vs := range cnt {
		Fprint(out, len(vs), " ")
		Fprintln(out, vs...)
	}
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

设 $d_i$ 为 $i$ 在这 $m$ 条不存在边中作为端点的数量。找到 $d$ 最小的点 $p$，那么有 $d_p\le\dfrac{2m}{n}$（最小值不超过平均值），于是不与 $p$ 在同一连通块至多 $\dfrac{2m}{n}$ 个，所以对这些点直接进行爆搜找出它们所在的连通块即可。

用的并查集记录连通块，`std::vector` 加指针判断是否为不存在的边（因为用 `std::unordered_set` 和自定义哈希类超时了）。

本题输入输出量极大，记得用快读快写。个人感觉还挺卡常，注意优化代码。

# Code

```cpp
#include<bits/stdc++.h>
std::vector<int>v[500005];
int dsu[500005];
int fs(int x){
	if(dsu[x]!=x)dsu[x]=fs(dsu[x]);
	return dsu[x];
}
bool vis[500005];
int deg[500005];
int n,m;
void dfs(int p){
	if(vis[p])return;
	vis[p]=true;
	for(int i=1,j=0;i<=n;++i){
		while(j!=v[p].size()&&v[p][j]<i)++j;
		if(j==v[p].size()||v[p][j]!=i)dsu[fs(i)]=fs(p),dfs(i);
	}
}
std::vector<std::vector<int> >ans;
std::vector<int>g[500005];
int main(){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);std::cout.tie(0);
	std::cin>>n>>m;
	for(int x,y;m--;)
		std::cin>>x>>y,++deg[x],++deg[y],
		v[x].push_back(y),v[y].push_back(x);
	for(int i=1;i<=n;++i)
		std::stable_sort(v[i].begin(),v[i].end()),dsu[i]=i;
	for(int i=1,p=std::min_element(deg+1,deg+n+1)-deg,j=0;i<=n;++i){
		while(j!=v[p].size()&&v[p][j]<i)++j;
		if(j==v[p].size()||v[p][j]!=i)dsu[i]=p,vis[i]=true;
	}
	for(int i=1;i<=n;++i)dfs(i);
	for(int i=1;i<=n;++i)
		g[fs(i)].push_back(i);
	for(int i=1;i<=n;++i)
		if(!g[i].empty())ans.push_back(g[i]);
	std::cout<<ans.size();
	for(const auto&i:ans){
		std::cout<<'\n'<<i.size();
		for(const int&j:i)
			std::cout<<' '<<j;
	}
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

一位外国小哥问我的题。

有一种非常自然的思路是线段树优化建图。显然我们可以拆分为 $O(n+m)$ 种边：节点 $u$ 和区间 $[l,r]$ 内的点在同一个连通块内。这时候就可以把 $[l,r]$ 的所有底层节点想办法和完全被这个区间包含的非叶子节点连边（可以打个标记每次遍历的时候下传），然后用 $O((n+m) \log n)$ 的复杂度合并并查集。

但是很容易想到线性做法。考虑选取输入的图中，度数最小的节点，我们记度数为 $\deg u$。考虑必有 $\deg u \le \dfrac{2m}{n}$。于是，我们发现，最多有 $\deg u+1$ 个区间 $[l,r]$ 使得 $[l,r]$ 中所有节点都与 $u$ 有连边。那么他们显然在同一个连通块内，相当于你进行了缩点。

那么我们只需要统计缩点之后的两两之间的边。由于 $\deg u \le \min\{n,\dfrac{2m}{n}\}$，所以算法复杂度为 $O(\deg u^2) = O(m)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=500000+10;
int n,m,fa[MAXN],sze[MAXN],flg[MAXN];
vector<int> G[MAXN],T[MAXN],res[MAXN];
map<pair<int,int>,int> cnt;
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) fa[i]=i;
	ffor(i,1,m) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v),G[v].push_back(u);	
	}
	int dg=n+1,pos=-1;
	ffor(i,1,n) if(G[i].size()<dg) dg=G[i].size(),pos=i;
	for(auto v:G[pos]) flg[v]=1; flg[pos]=1;
	ffor(i,2,n) if(!flg[i]&&!flg[i-1]) fa[find(i)]=find(i-1);
	ffor(u,1,n) for(auto v:G[u]) if(u<v&&find(u)!=find(v)) cnt[{min(find(u),find(v)),max(find(u),find(v))}]++;
	ffor(i,1,n) sze[find(i)]++;
	vector<int> _0;
	ffor(i,1,n) if(find(i)==i) _0.push_back(i);
	for(auto u:_0) for(auto v:_0) {
		if(u>=v) continue ;
		if(1ll*sze[u]*sze[v]!=cnt[{u,v}]) fa[find(u)]=find(v);
	}
	ffor(i,1,n) res[find(i)].push_back(i);
	int cnt=0;
	ffor(i,1,n) cnt+=!!res[i].size();
	cout<<cnt<<'\n';
	ffor(i,1,n) if(res[i].size()) {
		cout<<res[i].size()<<' ';
		for(auto v:res[i]) cout<<v<<' ';
		cout<<'\n';	
	}
	return 0;
}
```


---

## 作者：LiuIR (赞：1)

### 题目大意

[题目传送门](https://www.luogu.com.cn/problem/CF190E)

给出一个有 $n$ 个点的无向图，该图比完全图少了 $m$ 条边。现在要求出该图的连通分量。

$n\le 5\times10^5$，$m\le10^6$。

### 题目分析

首先可以观察到 $m$ 条边对于完全图是非常小的，所以可能有一个较大的连通分量。

倘若我们选择一个点 $u$，满足它缺少的边的数量是最少的。根据最小值小于等于平均值，可得点 $u$ 缺少的边是小于等于 $\dfrac{2m}n$ 条的，所以点 $u$ 所在的连通分量至少有 $n-\dfrac{2m}n$ 个点。

至于剩下的 $\dfrac{2m}n$ 个点，可以直接暴力搜索出经过他们的连通分量。

而对于连通分量的维护，可以使用并查集。

### 代码

```c++
#include <bits/stdc++.h>

namespace IO//快读快输 
{
	static int sta[205];
	char Is[(1 << 21) + 10], Os[(1 << 21) + 10];
	int Ipt, Opt;
	char Gc()
	{
		if(Ipt == 1 << 21)
			Ipt = 0;
		if(!Ipt)
			Is[fread(Is, 1, 1 << 21, stdin)] = 0;
		return Is[Ipt++];
	}
	void Flush(){fwrite(Os, 1, Opt, stdout); Opt = 0;}
	void Pc(char x)
	{
		if(Opt == 1 << 21)
			Flush();
		Os[Opt++] = x;
	}
	int Read()
	{
		int x = 0;
		char ch = Gc();
		while(ch < '0' || ch > '9')
			ch = Gc();
		while(ch >= '0' && ch <= '9')
			x = (x << 1) + (x << 3) + (ch ^ 48), ch = Gc();
		return x;
	}
	void Write(int x)
	{
		int top = 0;
		do
		{
			sta[top++] = x % 10;
			x /= 10;
		}while (x);
		while (top)
			Pc(sta[--top] + '0');
	}
	void Write(int x, char ch)
	{
		Write(x);
		Pc(ch);
	}
}

using namespace IO;

const int N = 5e5 + 5;

int n, m, pos, tot, id[N], fa[N], num[N];
bool bj[N];
std::vector<int> ans[N], edge[N];

void Dfs(int);
int Find(int);

signed main()
{
	n = Read();
	m = Read();
	if (!m)//特判 m=0 的情况 
	{
		Write(1, '\n');
		Write(n, ' ');
		for (int i = 1; i <= n; i++)
			Write(i, ' ');
		Flush();
		return 0;
	}
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1, u, v; i <= m; i++)
	{
		u = Read();
		v = Read();
		edge[u].push_back(v);
		edge[v].push_back(u);
		num[u]++;
		num[v]++;
	}
	for (int i = 1; i <= n; i++)if (!pos || num[i] < num[pos])//寻找缺少的边的最少的点 pos
		pos = i;
	for (int i = 1; i <= n; i++)
		std::sort(edge[i].begin(), edge[i].end());
	fa[pos] = pos;
	bj[pos] = true;
	for (int i = 1, j = 0; i <= n; i++)//寻找 pos 所在的连通分量 
	{
		if (!edge[pos].empty() && j < edge[pos].size() && i == edge[pos][j])
		{
			j++;
			continue;
		}
		fa[i] = pos;
		bj[i] = true;
	}
	for (int i = 1; i <= n; i++)if (!bj[i])//寻找其他点的连通分量 
	{
		fa[i] = i;
		Dfs(i);
	}
	for (int i = 1; i <= n; i++)if (fa[i] == i)
		id[i] = ++tot;
	for (int i = 1; i <= n; i++)
	{
		int fi = id[Find(i)];
		ans[fi].push_back(i);
	}
	Write(tot, '\n');
	for (int i = 1; i <= tot; i++)
	{
		Write(ans[i].size(), ' ');
		for (int j : ans[i])
			Write(j, ' ');
		Pc('\n');
	}
	Flush();
	return 0;
}

void Dfs(int u)
{
	bj[u] = true;
	for (int v = 1, i = 0; v <= n; v++)
	{
		if (!edge[u].empty() && i < edge[u].size() && v == edge[u][i])
		{
			i++;
			continue;
		}
		fa[Find(v)] = fa[Find(u)];
		if (bj[v])
			continue;
		Dfs(v);
	}
}
int Find(int x){return fa[x] == x ? x : fa[x] = Find(fa[x]);}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficutlty : 2100}$
---
### 解题思路：

剩下的边其实很多，考虑对于删去边最少的一个点先进行一个处理，将所有与之连边的点划分出来，得到一个很大的联通块。

然后将不与这个块联通的点暴力处理一下就好了。

---
然后分析一下复杂度，若希望卡到这个算法的复杂度上限，暴力处理的点希望尽量多，而最少连边的边的数量一定不会多于 $\dfrac{2m}{n}$，也就是最多只有这么多个点被暴力处理。然后暴力处理的复杂度是 $O(\dfrac{2m}{n}\times n)$ 的，最后的总复杂度为 $O(n+m)$ 可以接受。

### 代码：

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
int n,m,d[500005],x,y,col[500005],col_num=1,cnt,fa[500005];
vector <int> v[500005],ans[500005];
int find(int now){
	if(fa[now]==now)return now;
	return fa[now]=find(fa[now]);
}
void deal(int x){
	int l=0;
	for(int i=1;i<=n;i++){
		if(v[x].size()>=1)
		if(v[x][l]==i){
			l++;
			continue;
		}
		fa[find(i)]=find(x);
		col[i]=1;
	}
}
void dfs(int now){
	int l=0;col[now]=col_num;
	for(int i=1;i<=n;i++){
		if(v[now][l]==i){
			l++;
			continue;
		}
		fa[find(i)]=find(now);
		if(col[i]==0)dfs(i);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		d[x]++;d[y]++;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for(int i=1;i<=n;i++)sort(v[i].begin(),v[i].end());
	deal(min_element(d+1,d+n+1)-d);
	for(int i=1;i<=n;i++){
		if(col[i]==0){
			col_num++;
			dfs(i);
		}
	}
	for(int i=1;i<=n;i++){
		ans[find(i)].push_back(i);
		if(ans[find(i)].size()==1)cnt++;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++){
		if(ans[i].size()==0)continue;
		printf("%d ",ans[i].size());
		for(int j=0;j<ans[i].size();j++)
		printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}
```


---

