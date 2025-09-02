# [ABC231D] Neighbors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc231/tasks/abc231_d

$ 1 $ から $ N $ の番号がついた $ N $ 人を横一列に並べる方法のうち、以下の形式の $ M $ 個の条件全てを満たすものが存在するか判定してください。

- 条件：人 $ A_i $ と人 $ B_i $ は隣り合っている

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 10^5 $
- $ 1\leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,B_i) $ は相異なる

### Sample Explanation 1

例えば $ 4,1,3,2 $ の順に並べることで全ての条件を満たすことができます。

### Sample Explanation 2

どのように並べても全ての条件を満たすことはできません。

## 样例 #1

### 输入

```
4 2
1 3
2 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4 3
1 4
2 4
3 4```

### 输出

```
No```

# 题解

## 作者：zzy_zzy (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc231_d)
### 题意
对于每组 $(A_i,B_i)$，表示在一条链上点 $A_i$ 与点 $B_i$ 相邻，问是否能满足使其构成一条链（链上每一个点互不相同）。
### 思路
如果想使其构成一条链，则必须满足：
- 每个点最多出现两次。
- 如果前面已经有 $x$ 和 $y$ 这两个点之间已经有 $i$ 个点了 $(0<i)$。再说点 $x$ 与点 $y$ 相邻就不对了。

这道题可以用~~数组~~并查集来解决。为什么呢？因为每几个相邻关系都可以合并成一个集合。虽然这个相邻并不具有传递性，但只需要看两个点是否在同一链中就行了。

另外，我们还要再开一个数组表示与这个点相邻的点的个数。

**AC code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[100010],vis[100010];
int find(int x){	//查找
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);	//路径压缩
}
void build(int x,int y){	//合并
	int fx=find(x),fy=find(y);
	if(fx==fy){
		return;
	}
	fa[fx]=fy;
	return;
}
bool same_set(int x,int y){	//判断同一集合
	int fx=find(x),fy=find(y);
	if(fx==fy){
		return 1;
	}
	return 0;
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){	//初始化
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		vis[x]++,vis[y]++;
		if(vis[x]>2||vis[y]>2||same_set(x,y)){
			cout<<"No";
			return 0;
		}
		build(x,y);	//把相邻的点归到同一集合
	}
	cout<<"Yes";
	return 0;
}
```


---

## 作者：allenchoi (赞：2)

### 科技：  
图论基础知识  
### 思路：  
首先考虑什么情况有解。  
第一，每个数只能与两个数相邻；  
第二，整个排列是一条链。  
换句话说，我们对于每一组 $a_i,b_i$ 都建一条双向边，那么这张图中每个点的度最多为 $2$ ，且这张图中不能有环。度在建边时处理，判环在建好图后爆搜即可。  
### 代码：  
```cpp
#include <cstdio>
#include <vector>
using namespace std;
int n,m,a,b,vis[200010],cnt[200010];
bool flag = true;
vector <int> v[200010];
void dfs(int x,int fa)
{
	if(vis[x])
	{
		flag = false;
		return ;
	}
	vis[x]++;
	int siz = v[x].size();
	for(int i = 0;i < siz;i++) if(v[x][i] != fa) dfs(v[x][i],x);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++)
	{
		scanf("%d%d",&a,&b);
		if(a != b) v[a].push_back(b),v[b].push_back(a);
		cnt[a]++,cnt[b]++;
	}
	for(int i = 1;i <= n;i++)
	{
		if(cnt[i] > 2)
		{
			flag = false;
			break;
		}
		if(!vis[i]) dfs(i,-1);
		if(!flag) break;
	}
	if(flag) printf("Yes\n");
	else printf("No\n");
	return 0;
}
```

---

## 作者：Lizj (赞：2)

## 题意分析

题意：输入 $m$ 组 $(A_i,B_i)$，表示点 $A_i$ 与点 $B_i$ 在相邻，问这 $m$ 组数据是否能构成一条每一个点都互不相同的链。

想使其构成一条链，必须满足以下条件：

- 每个点最多只能描述两次它的关系（如果多于两次就不是一条链了）。

- 如果在前面的描述中已经描述了 $x$ 点的左右关系，再描述 $x$ 与 $y$ 相邻。就会发生重复。

然后我们就可以使用并查集来模拟这道题的操作，因为并查集可以为一条链，只需不断存入关系即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[100010],c[100010];
bool flag=1;
int find(int x){	//寻找元素所在集合的代表元
	if(fa[x]==x) 
		return x;
	return find(fa[x]);
}
void hebing(int x,int y){	//合并两点之间的关系
	int fx=find(x),fy=find(y);
	if(fx==fy){
		return;
	}else{
		fa[fx]=fy;
	}
}
bool same(int x,int y){	//寻找两点是否在同一集合
	int fx=find(x),fy=find(y);
	if(fx==fy){
		return true;
	}else{
		return false;
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){	//别忘了初始化
		fa[i]=i;
	}for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		c[a]++;c[b]++;
		if(c[a]>2||c[b]>2){
			flag=0;
		}if(same(a,b)){
			flag=0;
		}hebing(a,b);
	}if(flag){
		cout<<"Yes";
	}else{
		cout<<"No";
	}
    return 0;
}
```
但这样会导致超时，为什么呢？因为当集合为一条链时，递归算法会做许多重复的事。所以，我们需要考虑路径优化，那么路径优化是什么呢？就是在递归答案时将每个元素的祖先指向答案（这样可以降低时间复杂度）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[100010],c[100010];
bool flag=1;
int find(int x){
	if(fa[x]==x) 
		return x;
	return fa[x]=find(fa[x]);	//路径优化
}
void hebing(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy){
		return;
	}else{
		fa[fx]=fy;
	}
}
bool same(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy){
		return true;
	}else{
		return false;
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		c[a]++;c[b]++;
		if(c[a]>2||c[b]>2){
			flag=0;
		}if(same(a,b)){
			flag=0;
		}hebing(a,b);
	}if(flag){
		cout<<"Yes";
	}else{
		cout<<"No";
	}
    return 0;
}
```

---

## 作者：PikachuQAQ (赞：0)

## Description

[Link](https://www.luogu.com.cn/problem/AT_abc231_d)

## Solution

拓扑排序模板题。

可以将链看成一张图，然后分析一下不满足的情况：

一个节点的度如果超过了 $2$，就是不满足一条链的情况，因为在链上的节点最多只会连接左右两个节点。

随后使用拓扑排序，用拓扑排序检测图上是否有环。

如果以上两点都不满足，说明排列存在，否则则不存在。

## Code

```cpp
// 2023/5/15 Accept__

#include <queue> 
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int kMaxN = 2e5 + 7;

vector<int> G[kMaxN], l;
queue<int> q;
int n, m, t[kMaxN];

bool toposort() {
	int cnt = 0;
	int degree[kMaxN];
	memset(degree, sizeof degree, 0);
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		degree[i] = G[i].size();
		if (degree[i] <= 1) 
			q.push(i);
	}
	while (!q.empty()) {
		cnt++;
		int root = q.front();
		q.pop();
		for (auto child : G[root]) {
			degree[child]--;
			if (degree[child] == 1) 
				q.push(child);
	
		}
	}
	return (cnt != n);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 0, u, v; i < m; i++) {
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
		t[u]++, t[v]++;
		if (t[u] > 2 || t[v] > 2) {
			cout << "No";
			return 0;
		}
	}
	
	for (int i = 1; i <= n; i++) {
		if (t[i] > 2)  {
			cout << "No";
			return 0;
		}
	}
	if (!toposort()) cout << "Yes";
	else cout << "No";
	
	return 0;
} 
```


---

## 作者：rui_er (赞：0)

首先，每个数不能有超过两个相邻元素，不然无法构成一条链。可以通过记录每个数出现次数（度数）来判断。

其次，给的信息不能成环，不然也无法构成一条链。可以通过并查集来判断。

在以上两个判断之后，剩余的情况一定有解，可以通过不断找度数小于 $2$ 的点作为起点，依次通过若干度数等于 $2$ 的点，最终停留在度数小于 $2$ 的点作为终点，重复若干次得到。

时间复杂度 $\Theta(n\alpha(n))$。

```cpp
// Problem: D - Neighbors
// Contest: AtCoder - Panasonic Programming Contest 2021(AtCoder Beginner Contest 231)
// URL: https://atcoder.jp/contests/abc231/tasks/abc231_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 1e5+5;

int n, m, deg[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
struct Dsu {
	int fa[N], rk[N];
	void init(int x) {rep(i, 1, x) fa[i] = i, rk[i] = 0;}
	int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
	bool merge(int x, int y) {
		int u = find(x), v = find(y);
		if(u == v) return 0;
		if(rk[u] < rk[v]) swap(u, v);
		chkmax(rk[u], rk[v] + 1);
		fa[v] = u;
		return 1;
	}
}dsu;

int main() {
	scanf("%d%d", &n, &m);
	dsu.init(n);
	rep(i, 1, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		++deg[u]; ++deg[v];
		if(!dsu.merge(u, v)) return puts("No")&0;
	}
	if(*max_element(deg+1, deg+1+n) > 2) puts("No");
	else puts("Yes");
	return 0;
}
```

---

## 作者：charleshe (赞：0)

注：以下设 $m$ 为图的边数，$n$ 为图的点数。

显然不应该把此题当成一道数组类的题目来想。考虑转化。

把数组的每一个位置抽象成每一个点，问题就会被转化成：在一张图里有一些边，问能不能再连一些边使得全图变成一条链。

显然链是树的一种，而树的边数即为顶点数减一（即，$m = n - 1$），于是当数据中出现 $m \geq n$ 的情况时，直接输出 `No`，这是一个小优化。

接下来分析链的性质：

- 一条链的任何一个点的度数最多为 $2$。

因此，在建完图后，我们可以顺序遍历一遍每个点，判断其度数；如果度数大于等于 $3$，直接输出 `No` 结束。

- 链是无环的。

原因显然。树是无环的，作为树的一种的链自然也应该无环。

判断图上是否有环的方法很多，常规的做法是并查集，或者深搜。本篇题解使用深搜。**注意不能使用拓扑排序，因为拓扑排序是针对有向图的，而读完条件后易知本题的图是无向图。**

还有几个细节：

> $1 \leq A_i < B_i \leq N$。

说明每一组 $A_i$ 和 $B_i$ 都是不同的，从而排除自环。

> 保证所有的 $( A_i , B_i )$ 都是不同的。

显然这意味着图上没有重边。

另外，注意到可能会出现 $m < n - 1$ 的情况，即该图不连通。因此，判环的深搜应该在每个点上都进行一次。

综上，此题做完了。

```cpp
#include <iostream>
#include <vector>
using namespace std;
vector<int> v[100001];//这里使用了边表来存图。
int n,m,u0,v0;
bool vis[100001];
void dfs(int u,int f){
	if(vis[u]){
		cout<<"No\n";
		exit(0);
	}
	vis[u]=1;
	for(auto v1:v[u]){
		if(v1!=f) dfs(v1,u);
	}
}//注意到这个深搜没有将vis数组重新归零。
int main(){
	cin>>n>>m;
	if(m>=n){//提前特判。
    //其实没有这个特判也行，这只是一个小优化。
		cout<<"No\n";
		return 0;
	}
	for(int i=1;i<=m;i++){
		cin>>u0>>v0;
		v[u0].push_back(v0);
		v[v0].push_back(u0);//注意是无向图。
	}
	for(int i=1;i<=n;i++){
		if(v[i].size()>2){//判断点的度数。
			cout<<"No\n";
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]) dfs(i,0);//由于深搜没有将vis数组重新归零，所以已经被遍历过的点不能再遍历一次，否则答案会出错。
        //当然，如果深搜有将vis数组重新归零的话，已遍历的点就可以重新遍历。
	}
	cout<<"Yes\n";
	return 0;
}
```


---

## 作者：CQ_Bab (赞：0)

# 思路
~~这道题其实很水~~。首先我们只需要去建边，然后判断每个点的出现次数是否超过 $2$ 或是两个数已经在同一个集合内即可（因为它不是一个环形数组），出现次数不能大于 $2$ 因为一个数只能与它的左右相邻，两个数不能在同一个集合内是因为若在同一个集合内说明他们一定为一个数的左右，而一个数的左右一定不会相邻。若这两种情况都判断过了就将 $A_i$ 与 $B_i$ 所在的集合合并。

例如：
```
4 3
1 2
2 3
3 1
```
应输出否。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010;
int fa[N], d[N];
void init(int n) { for (int i = 0; i <= n; i++) fa[i] = i; } //初始化
int find(int x) { return fa[x] == x ? x : find(fa[x]); } //查询
void merge(int x, int y) { //合并
	x = find(x), y = find(y);
	if (x == y)return;
	fa[x]=y;
}
int a[N];
signed main(){
	int n, m;
	cin >> n >> m;
	init(n);
	int ok = 1;
	while (m--){
		int u, v;
		cin >> u >> v;
		a[u]++;
        a[v]++;
		if (a[u] > 2 || a[v] > 2)ok = 0;
		if (find(u) == find(v))ok = 0;
		merge(u, v);
	}
	if (ok) cout << "Yes\n"; //输出
	else cout << "No\n";
    return false; // AC了
}
```


---

