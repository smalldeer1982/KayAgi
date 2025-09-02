# Penchick and Chloe's Trees

## 题目描述

离 Penchick 和 Chloe 前往新加坡的时间只剩下几个小时了，他们迫不及待地想去看看新加坡植物园的参天大树！为了抑制激动的心情，Penchick 制作了一棵有根树，让 Chloe 和他自己忙个不停。

Penchick 有一棵**有根树**，由 $n$ 个节点组成，编号从 $1$ 到 $n$，节点 $1$ 是根，Chloe 可以选择一个非负整数 $d$ 来创建一棵深度为 $d$ 的**满二叉树**。

由于 Penchick 和 Chloe 是好朋友，Chloe 希望自己的树与 Penchick 的树**同构**。为了满足这个条件，Chloe 可以在自己的树上执行以下操作，次数不限：

+ 选择边 $(u,v)$，其中 $u$ 是 $v$ 的父亲。
+ 删除顶点 $v$ 和所有连接到 $v$ 的边，然后将 $v$ 之前的所有子节点直接连接到 $u$。

具体来说，在 $v$ 为叶子的边 $(u,v)$ 上进行操作，可以删除顶点 $v$，而不会添加任何新的边。

由于构建满二叉树非常耗时，Chloe 希望选择最小值 $d$，这样深度为 $d$ 的满二叉树就可以通过上述操作与 Penchick 的树同构。注意，她不能改变树的根。

**有根树**：树是没有环的连通图。有根树是指有一个节点是特殊的，叫做根。节点 $v$ 的父节点是从 $v$ 到根的简单路径上的第一个节点。根没有父节点。节点  $v$ 的子节点是以 $v$ 为父节点的任意节点 $u$。叶是任何没有子节点的节点。

**满二叉树**：一棵 Full Binary Tree 是有根树，其中每个节点都有 $0$ 或 $2$ 个子节点。满二叉树是指每个叶子与根的距离都相同的 Full Binary Tree。树的深度就是树根到树叶的距离。

**同构**：如果存在顶点的排列 $p$，使得当且仅当边  $(p_u,p_v)$ 存在于第二棵树中时，边 $(u,v)$ 存在于第一棵树中，并且 $p_{r_1}=r_2$。则两棵根分别为 $r_1,r_2$ 的树被认为是同构的。

## 样例 #1

### 输入

```
5
6
1 2 2 1 1
15
1 1 2 2 3 3 4 4 5 5 6 6 7 7
5
1 2 2 2
7
1 1 2 1 1 2
10
1 1 1 2 2 2 4 3 3```

### 输出

```
2
3
3
3
3```

# 题解

## 作者：Xuan_qwq (赞：8)

upd：修正了文中的一处错误。

---

动规妙妙题，代码完成于赛后一分钟内，诶诶。

### 题面大意
给你一颗有根树，现要生成一颗满二叉树，使得对该二叉树经过若干次删点操作后可以使两棵树同构。

删点操作定义为：选择一个非根节点 $u$，删去点 $u$，并把 $u$ 的所有儿子与 $u$ 的父亲连边。

求所需满二叉树高度的最小值，高度定义为根节点到叶子节点路径上的边数。

### 思路

设 $dp_u$ 表示：可以通过删点操作与以 $u$ 为根的子树同构的满二叉树高度最小值。

考虑转移，对于任意节点 $u$，现已知其所有儿子 $v\in son_u$ 对应的 $dp_v$，则 $dp_u$ 可以贪心求得。

每次选取所有儿子中二叉树高度最小的两个，设为 $v_1$ 和 $v_2$，将这两颗二叉树合并，合并后的二叉树大小为 $\max(dp_{v_1},dp_{v_2})+1$，不断进行合并操作直到只剩一棵树即可，过程可使用优先队列实现。



注意转移时要特判 $u$ 只有一个儿子的情况。因为出题人开大了时限，所以我们可以用深搜来转移它。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
int T,n,dp[1000005];
vector<int>G[1000005];
void dfs(int u){
	if(G[u].size()==0)return;//叶子节点 
	for(int i=0;i<G[u].size();i++)dfs(G[u][i]);
	if(G[u].size()==1){//特判只有一个儿子
		dp[u]=dp[G[u][0]]+1;
		return;
	}
	priority_queue<int>q;
	for(int i=0;i<G[u].size();i++)q.push(-dp[G[u][i]]);//因为priority_queue默认大根堆，所以我们存负值以达到小根堆的效果
	while(q.size()>1){
		int x=q.top();q.pop();
		int y=q.top();q.pop();
		q.push(min(x,y)-1);//合并 
	}
	dp[u]=-q.top();//记得符号要变回来
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)G[i].clear(),dp[i]=0;//多测要清空 
		int u;
		for(int i=2;i<=n;i++){
			cin>>u;
			G[u].push_back(i);
		}
		dfs(1);
		cout<<dp[1]<<endl;//输出根节点对应的值 
	}
	return 0;
}
```

---

## 作者：2huk (赞：7)

> 求最小的 $d$，使得可以在深度为 $d$ 的满二叉树上删除若干点后，与给定的树同构。
>
> 这里删掉点 $u$ 后，$u$ 的所有儿子都会连到 $u$ 的父亲上。
>
> $n \le 10^6$。

显然树形 DP 是必要的。$f(u)$ 表示 $u$ 子树的答案，即最小的合法满二叉树的深度。

如果 $u$ 是叶子（没有儿子）：$f(u)=1$；

如果 $u$ 只有一个儿子：$f(u)=f(v)+1$；

否则，考虑一个类似合并的过程。我们举几个例子。如果 $u$ 的儿子的 DP 值是：
- $[3, 3]$：$f(u)=4$；
- $[3, 3, 3, 3]$：$f(u)=5$；
- $[3, 3, 3]$：$f(u)=5$；
- $[1,3,3]$：$f(u)=5$；

![](https://cdn.luogu.com.cn/upload/image_hosting/oz0jml3d.png)

---

着重分析一下 $[1,3,3]$。首先我想把 $1$ 跟别的对齐，就需要造一个深度为 $3$ 的满二叉树。

![](https://cdn.luogu.com.cn/upload/image_hosting/xa7254x9.png)

（实际上这里省了一步，应该先造深度为 $2$ 的，发现还不够，再造了 $3$。）

然后变成了 $[3, 3, 3]$ 的问题。直接连肯定不行，因为需要是二叉树。所以再造一个深度为 $3$ 的。

![](https://cdn.luogu.com.cn/upload/image_hosting/1tqcalwu.png)

然后变成了 $[3, 3, 3, 3]$ 的问题。把前两个和后两个分别合成深度为 $4$ 的。 

![](https://cdn.luogu.com.cn/upload/image_hosting/4o17ifak.png)

然后是 $[4, 4]$ 的问题。显然能合并成一个 $5$。结束了。

---

形式化的，这个过程是 $[1, 3, 3] \to [2, 3, 3] \to [3, 3, 3] \to [4, 4] \to [5]$。也就是每次把所有最小的数删掉（令最小的数是 $x$，有 $y$ 个），然后添加 $\lceil \frac y2 \rceil$ 个 $x+1$。重复这个过程直到只剩一个数。最后这个数就是 $f(u)$。

暴力代码是这样的：

```cpp
void dfs(int u) {
	f[u] = 0;
	
	if (g[u].empty()) {
		f[u] = 1;
		return;
	}
	
	if (g[u].size() == 1) {
		dfs(g[u][0]);
		f[u] = f[g[u][0]] + 1;
		return;
	}
	
	map<int, int> cnt;
	for (int v : g[u]) {
		dfs(v);
		cnt[f[v]] ++ ;
	}
	
	while (cnt.size() != 1 || (*cnt.begin()).second != 1) {
		int x = (*cnt.begin()).first;
		int y = (*cnt.begin()).second;
		cnt[x + 1] += (y + 1) / 2;
		cnt.erase(x);
	}
	
	f[u] = (*cnt.begin()).first;
}
```

直接这样交会 [TLE on test #62](https://codeforces.com/contest/2031/submission/292119672)。其实这样复杂度是错误的，因为求一个 DP 值的复杂度是 $f(v)$ 的值域，也就是 $\mathcal O(n)$。总复杂度是平方的。[hack generator](https://www.luogu.com.cn/paste/4wqoib1w)。

---

怎么优化？

仍然考虑这个例子 $[1, 3, 3]$。在最上面模拟时，我们跳过了 $[2, 3, 3]$ 这一步，而是直接到了 $[3, 3, 3]$。考虑实现这一点。

也就是我们考虑这一个 $1$ 最终会变成几个 $3$。更一般的，我们考虑 $x$ 个 $y$ 最终会变成几个 $y+k$（$k > 0$），且 $y,y+k$ 是原数组排好序后的相邻的两个数。

不难发现这个答案是从 $x$ 开始，执行 $k$ 次除以二上取整的答案。注意到当过程中 $x$ 变为 $1$ 后，最终结果一定是 $1$，此时可以直接退出。不难证明这样做最多只有 $\mathcal O(\log n)$ 次。

总复杂度 $\mathcal O(n \log n)$。常数挺大。

```cpp
#define tests
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n, fa[N];
vector<int> g[N];
int f[N];		// i 的子树，需要几层满二叉树

int work(int x, int y) {
	if (!x) return 0;
	if (y > 60) return 1;
	while (y -- ) x = (x + 1) / 2;
	return x;
}

void dfs(int u) {
	f[u] = 0;
	
	if (g[u].empty()) {
		f[u] = 1;
		return;
	}
	
	if (g[u].size() == 1) {
		dfs(g[u][0]);
		f[u] = f[g[u][0]] + 1;
		return;
	}
	
	map<int, int> cnt;
	for (int v : g[u]) {
		dfs(v);
		cnt[f[v]] ++ ;
	}
	
	vector<pair<int, int>> vec;
	for (auto e : cnt) vec.push_back(e);
	
	for (int i = 0; i + 1 < vec.size(); ++ i ) {
		vec[i + 1].second += work(vec[i].second, vec[i + 1].first - vec[i].first);
	}
	
	while (vec.back().second != 1) {
		vec.back().first ++ ;
		vec.back().second = (vec.back().second + 1) / 2;
	}
	
	f[u] = vec.back().first;
}

void solve() {
	cin >> n;
	
	for (int i = 1; i <= n; ++ i ) {
		g[i].clear();
	}
	
	for (int i = 2; i <= n; ++ i ) {
		cin >> fa[i];
		g[fa[i]].push_back(i);
	}
	
	dfs(1);
	
	cout << f[1] - 1 << '\n';
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
#ifdef tests
	cin >> T;
#endif
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：Eddie08012025 (赞：6)

## 思路
本题会用到一些贪心与 dp。

本题题面上是一个删边的操作，但其实实现起来是一个增边的操作。

令 $mxdep_i$ 为以 $i$ 号节点为根节点，让其子树变成一个二叉树的最小深度。

对于 $i$ 号节点，处理 $mxdep_i$，需要先得到所有 $i$ 的子节点 $j$ 的 $mxdep_j$。每次合并每个深度最小的子节点的子树，得到的深度是两个子树中更大深度加一，最后将所有子节点的子树合并成一个一棵树，$mxdep_i$ 即为最后剩下的树的深度。可以用小根堆实现。

举个例子，假如 $1$ 节点的子节点有 $2,3,4,5$，$mxdep_2=3,mxdep_3=4,mxdep_4=7,mxdep_5=8$。此时将所有深度塞入小根堆，此时为：$[3,4,7,8]$。

合并深度为 $3,4$ 的子树，得到深度为 $5$ 的子树，再塞入小根堆，此时为：$[5,7,8]$。

合并深度为 $5,7$ 的子树，得到深度为 $8$ 的子树，再塞入小根堆，此时为：$[8,8]$。

合并深度为 $8,8$ 的子树，得到深度为 $9$ 的子树，再塞入小根堆，此时为：$[9]$，得 $mxdep_1=9$。

答案为 $mxdep_1$。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,mxdep[1000005];
vector<int>z[1000005];
void dfs(int x){
	priority_queue<int,vector<int>,greater<int> >q;
	for(auto v:z[x]){
		dfs(v);
		q.push(mxdep[v]);
	}if(q.empty())return ;
	if(q.size()==1){
		mxdep[x]=q.top()+1;
		return ;
	}while(q.size()>1){
		int x=q.top();
		q.pop();
		int y=q.top();
		q.pop();
		q.push(max(x,y)+1);
	}mxdep[x]=q.top();
	return ;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=2;i<=n;i++){
			mxdep[i]=0;
			int a;
			cin>>a;
			z[a].push_back(i);
		}dfs(1);
		cout<<mxdep[1]<<"\n";
		for(int i=1;i<=n;i++){
			z[i].clear();
		}
	}
	return 0;
}
 
```

---

## 作者：zhengjinyi (赞：4)

## Problem
将一棵满二叉树删为一棵指定的树，每次删除节点会将其所有儿子连到父亲节点上，求初始二叉树的最小高度。
## Solution
### $O(n^2)$
记 $f_i$ 表示节点 $i$ 子树内操作完成的最小高度，考虑转移。\
显然我们应该将高度低的子节点和高度低的子节点优先合并。设当前节点为 $x$，每个高度与 $x$ 相差 $k$ 的节点可以放 $2^k$ 个，可以看作“占据”了节点 $x$ 的 $\frac{1}{2^k}$ 的空间。因为每个子节点的大小都是 $2$ 的整数次幂，所以不必担心某个节点因空间不连续而放不下。\
充分发扬人类智慧，发现这个过程与高精加非常相似。\
具体地，将每个子节点 $y$ 看作一个二进制数 $2^{f_y}$，每个节点跑一遍高精加，有以下转移（注意 $f_x$ 应大于 $\max f_y$）：
$$f_x=\max(\max f_y+1,\lceil\log_2\sum 2^{f_y}\rceil)$$
用 bitset 可以做到 $O(\frac{n^2}{\omega})$，~~虽然没什么用~~。
### $O(n\log n)$
考虑优化高精加的过程。\
因为我们只关心 $\lceil\log_2\sum 2^{f_y}\rceil$ 的值，所以较低位可以舍去。\
将所有儿子的 $f$ 值存起来排序，从低到高位考虑，同时记录进位。\
高精加的每个数都是 $2$ 的整数次幂，所以进位数量仅有 $O(n)$ 个，可以存下。\
从一位 $p$ 进到另一位 $p+d$ 时，将进位数量 $w$ 更新为 $\lceil\frac{w}{2^d}\rceil$。\
最后将剩余的进位加上 $\max f_y$，即为 $\lceil\log_2\sum 2^{f_y}\rceil$ 的值。
## Code
（场上没发现进位 $w$ 的贡献是 $\lceil\log_2w\rceil$，代码里面 $O(\log n)$ 求了。预处理即可。
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb emplace_back
#define R read()
using namespace std;
inline int read(){
	int x=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}
const int inf=0x3f3f3f3f,N=1000005;
const ll INF=0x3f3f3f3f3f3f3f3f;
int T,n,f[N],p2[25];
vector<int> v[N];
void dfs(int x){
	if(!v[x].size()){ f[x]=0; return; }
	int mx=0;
	vector<int> s;
	for(int y:v[x]){
		dfs(y);
		s.pb(f[y]);
		mx=max(mx,f[y]);
	}
	sort(s.begin(),s.end());
	int w=0,lst=0,cnt=0;
	for(int y:s){
		if(y-lst>22&&w) w=1;
		else w=ceil(1.0*w/p2[y-lst]);
		w++;
		lst=y;
	}
	while(w>1) w=ceil(w/2.0),cnt++;
	f[x]=max(mx+1,s.back()+cnt);
}
int main(){
	T=R;
	p2[0]=1;
	for(int i=1;i<25;i++) p2[i]=p2[i-1]<<1;
	while(T--){
		n=R;
		for(int i=1;i<=n;i++) v[i].clear();
		for(int i=2;i<=n;i++) v[R].pb(i);
		dfs(1);
		printf("%d\n",f[1]);
	}
	return 0;
}
```

---

## 作者：TonviaSzt (赞：2)

[Problem Link](https://codeforces.com/contest/2031/problem/E)

**题目大意**

> 定义树上一次操作为删除 $u$ 节点，并连接 $u$ 的父亲和 $u$ 的儿子。给定一棵树，求一棵满二叉树能操作成该树的最小满二叉树深度。

**思路分析**

树形 dp。设 $f_u$ 为以 $u$ 子树还原成满二叉树的最小满二叉树深度。

可以发现合法性只和 $u$ 子树的叶子结点个数有关，具体地，单对 $u$ 来说，设其子树的叶子结点数为 $k$，则 $f_u=\lceil\log_2k\rceil$，结论显然。

因为所有儿子 $v$ 都需要满足该式，且 $u$ 只能有两个子树，因此 $f_u$ 的大小由 $f_v$ 直接决定。考虑从下向上转移 $f$，每次贪心合并最小的两个 $f_v$， $f_{new}=\max(f_{v_1},f_{v_2})+1$，直到合并剩下不超过两个子树，$f_u=\max (f_{lson},f_{rson})+1$。

[Submission](https://codeforces.com/contest/2031/submission/292183316)

---

## 作者：__Floze3__ (赞：2)

## 思路

我们设 $f_u$ 表示以 $u$ 为根的子树，需要深度为几的完全二叉树才能构成，那么最终的答案即为 $f_1$。既然题目给的是一颗有根树，我们自然想到通过儿子节点的 $f$ 来求出当前节点的 $f$。我们考虑如果有两个儿子节点的 $f$ 值为 $0$，那么我们可以把它们合并成一个需要深度为 $1$ 的完全二叉树的节点；同样的，如果两个儿子节点的 $f$ 值为 $0$ 和 $1$，那么可以把它合并成一个需要深度为 $2$ 的完全二叉树的节点。但我们考虑儿子节点 $f$ 值为四个 $0$ 的情况，如果我们按顺序一个一个合并的话深度为 $3$，但我们完全可以把四个 $0$ 两两合并，最后再把两个 $1$ 合并得到 $2$，这样显然更优。我们不难想到这样的贪心：每次选择两个最小的 $f$ 值合并，直到只剩下一个 $f$ 值，那么当前节点的答案即为这个 $f$。每个节点开一个优先队列即可做到 $O(n \log n)$。注意要特判只有一个儿子节点的情况，此时的 $f$ 值为儿子节点的 $f$ 值加 $1$。

## 代码

[赛时代码](https://codeforces.com/contest/2031/submission/291647528)

---

## 作者：_segmenttree (赞：1)

题意：每次操作可将一个点删除，并将它的父亲向所有儿子连边。求深度至少为多少的满二叉树经过操作后成为指定的树。

解法：$dp_u$ 表示以 $u$ 为根的子树需要几层满二叉树操作过来。容易看出没有儿子时 $dp_u=0$，在儿子数量在两个以内时 $dp_u=\max(dp_v+1),v\in son_u$。在儿子数量大于二时我们考虑会将哪些儿子合并，如果我们选择 $v1,v2$ 合并，合并的新点的贡献为 $\max(dp_{v1},dp_{v2})+1$。容易看出，如果想让 $dp_u$ 的值尽可能小的话我们一定选择最小的两个点合并，用优先队列维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,dp[N];
vector<int>a[N];
void dfs(int x) {
    priority_queue<int,vector<int>,greater<int> >q;
    dp[x]=0;
	if(a[x].size()==0) return ;
	for(auto v:a[x]) {
		dfs(v);
		q.push(dp[v]);
	}
	while(q.size()>2) {
		int fi=q.top();
		q.pop();
		int se=q.top();
		q.pop();
		q.push(max(fi,se)+1);
	}
	while(!q.empty()) { 
	    dp[x]=max(dp[x],q.top()+1);
	    q.pop();
    }
}
void solve() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) a[i].clear();
	for(int i=2;i<=n;i++) {
		int f;
		scanf("%d",&f);
		a[f].push_back(i);
	}
	dfs(1);
	printf("%d\n",dp[1]);
}
signed main(){
	int t;
	cin>>t;
	while(t--) solve(); 
	return 0;
}
```

---

## 作者：tai_chi (赞：1)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18549167) 中阅读。

#### 题意

假设初始有一棵根为 $1$ 的满二叉树，定义一次删除操作为：

- 选择一条树边 $(u,v)$，不妨令 $u$ 为父亲；
- 将所有 $v$ 的儿子与 $u$ 相连；
- 删除节点 $v$。

现在给定一棵已经被进行了一系列删除操作的树，问最少需要高度为多少的满二叉树才能通过若干次删除操作将满二叉树变为给定的树。

#### 分析

从满二叉树开始考虑较为困难，我们可以从给定的数开始考虑如何还原回满二叉树。

注意到一个节点的儿子数量不大于 $2$ 是容易处理的，因为删除一个叶子不影响其他节点。

现在我们考虑儿子数量为 $3$ 的情况，发现可以选取其中两个儿子新建一个父亲，另一个节点直接连接到父亲。贪心地，我们会选择两个**高度**较小的儿子。

数量为 $4$ 呢？一种自然的思路是两两分组合并，但稍加思考就会发现这并不一定最优，因为可能有一个儿子非常高，这时把这个儿子直接连接父亲，剩余三个按照上面的方法合并即可。

这表明儿子的合并不能简单贪心，我们转而在每个节点上开一个优先队列，每次将两个高度最小的节点合并，当剩余的节点只有两个时直接与父亲相连。

```cpp
void solve()
{
	int n; cin>>n;
	vector<int> p(n+5);
	vector<vector<int>> gr(n+5);
	for(int i=2;i<=n;i++)
	{
		cin>>p[i];
		gr[p[i]].push_back(i);
	}
	vector<int> f(n+5);
	function<void(int)> dfs=[&](int u)
	{
		priority_queue<int,vector<int>,greater<int>> q;
		for(int v:gr[u])
		{
			dfs(v);
			q.push(f[v]);
		}
		while(q.size()>2)
		{
			int x=q.top(); q.pop();
			int y=q.top(); q.pop();
			q.push(max(x,y)+1);
		}
		if(q.empty()) return;
		if(q.size()==1) f[u]=q.top()+1;
		if(q.size()==2)
		{
			int x=q.top(); q.pop();
			int y=q.top(); q.pop();
			f[u]=max(x,y)+1;
		}
	};
	dfs(1);
	cout<<f[1]<<"\n";
}
```

---

## 作者：Exp10re (赞：1)

感谢此题送我上 M。我喜欢你。

## 解题思路

正难则反。

考虑原操作的逆操作：选中一个节点以及其若干儿子，创造一个新节点，将这些儿子的父亲设为该节点，然后将该节点的父亲设为该节点。

容易发现，存在一种方案对原树使用若干次这种操作之后将其变为一棵二叉树，并且在所有由其生成的二叉树中深度最小的一颗的深度即为使用正向操作能生成原树的满二叉树的最小深度，并且可以证明在这种意义下逆操作仅选择两个点一定最优。

考虑如何得到这个深度：注意到其具有局部最优性，考虑树形 DP。

具体的，记 $f_x$ 表示仅对 $x$ 子树内的节点操作将其变为一颗二叉树时的最小深度。

转移时，将 $x$ 的所有儿子的 $f$ 值列为一个数列，转移形如每次从该数列中选择两个数 $x,y$ 删去并将 $\max(x,y)+1$ 加入该数列（即模拟计算使用逆操作合并这两个子树产生一个新的子树）直到只剩一个数，这个数即为 $f_x$。

要使得这个数最小考虑贪心：将数列中的数加入小根堆中，每次取其最小的两个进行合并，考虑到小的数要尽可能被多合并，可以发现这么做一定最优。

$f_1$ 即为答案，时间复杂度 $O(n\log n)$。

---

## 作者：__Louis__ (赞：1)

### 题解：CF2031E Penchick and Chloe's Trees

### 思路

树形 dp 好题，难点在于处理转移。

首先，设状态 $dp_x$ 表示在 $x$ 节点至少需要多深的完全二叉树。

然后考虑转移，根据样例，发现两颗深度为 $1$ 的子树可以合成一个深度为 $2$ 的树（即至少需要一个深度为 $2$ 的子树才能使得这两个深度为 $1$ 的子树都成为儿子节点）。

那么现在问题就变成如何合并这些子树，使得最后剩下小于两个子树，其最大深度最小。最终 dp 值就是两个子树深度最大值多一。

显然，合并子树可以用堆来维护，每次使得最小的两个子树合并即可。

复杂度 $O(n\log n)$。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
vector<int> v[maxn];
int dp[maxn];
bool vis[maxn];
void dfs(int x){
	vis[x]=true;
	priority_queue<int,vector<int>,greater<int> > q;
	for(int i=0;i<v[x].size();i++){
		int k=v[x][i];
		if(!vis[k]){
			dfs(k);
			q.push(dp[k]);
		}
	} 
	while(q.size()>2){
		int k1=q.top();
		q.pop();
		int k2=q.top();
		q.pop();
		q.push(max(k1,k2)+1);
	}
	if(q.empty()) dp[x]=0;
	else if(q.size()==1) dp[x]=q.top()+1;
	else{
		int k1=q.top();
		q.pop();
		int k2=q.top();
		dp[x]=max(k1,k2)+1;
	}
	vis[x]=false;
}
signed main(){

	int T;
	scanf("%lld",&T);
	while(T--){
		int n;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			v[i].clear();
			dp[i]=0;
		}
		int a=0;
		for(int i=2;i<=n;i++){
			scanf("%lld",&a);
			v[a].push_back(i);
			v[i].push_back(a);
		}
		dfs(1);
		printf("%lld\n",dp[1]);
	}
}
```

---

## 作者：qnqfff (赞：0)

### 思路

容易发现题目相当于可以每次把两个点和父亲的边断掉并连上一个新的点，再把新的点和这两个点原先的父亲连边，求将一棵树变成一棵二叉树的最小操作次数。

考虑设 $dp_u$ 表示 $u$ 子树内的答案，考虑如何转移，容易发现相当于有很多个 $dp_v$，每次可以将两个点 $x,y$ 删掉并加上 $\max(x,y)+1$，最后剩下来的那个数最小，直接贪心每次删最小的两个即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int T,n,dp[1000010];vector<int>e[1000010]; 
void solve(){
	n=read();for(int i=1;i<=n;i++) e[i].clear();for(int i=2;i<=n;i++) e[read()].push_back(i);
	function<void(int)>dfs=[&](int u){
		for(auto v:e[u]) dfs(v);priority_queue<int,vector<int>,greater<int>>q;for(auto v:e[u]) q.push(dp[v]);
		if(q.empty()){dp[u]=1;return ;}if(q.size()==1){dp[u]=dp[e[u].front()]+1;return ;}
		while(q.size()>1){int u=q.top();q.pop();int v=q.top();q.pop();q.push(max(u,v)+1);}dp[u]=q.top();
	};dfs(1);cout<<dp[1]-1<<'\n';
}
signed main(){
	T=read();while(T--) solve();
	return 0;
}
```

---

## 作者：RayAstRa_ (赞：0)

## Description

给一棵有根树，问深度最小的在删除若干点后与该树同构的完全二叉树的深度。**该完全二叉树的根节点需与原树的根节点一致。**

## Solution

考虑树形 dp，对每个点计算以该点为根的子树的答案 $\log_2 d_i$。

对于叶子，显然 $d_i=0$。

对于只有一个儿子的节点，$d_i=2d_{son}$。

对于有多个儿子的节点，设 $x=\sum d_{son}$，则 $d_i=2^{\lceil \log_2x\rceil}$。

明显，直接这么 dp，$d_i$ 的最大值可到 $2^n$，正常变量都存不下。

发现 $d_i$ 均为 $2$ 的幂次，则对于每个点记录 $\log_2 d_i$，然后用一个 bool 数组模拟加法。清空时用栈记录 bool 数组里被访问过的值。时空复杂度 $O(n)$。

## Code


```cpp
const int N=1000005;
int n,fa[N],stk[N<<1],lev;
ll d[N];
vec g[N];
bool now[N<<1];
void add(int x){
    while(now[x]){
        now[x]=0;
        x++;
    }
    stk[++lev]=x;
    now[x]=1;
}
int calc(){
    int maxa=0,cnt=0;
    For(i,1,lev)
        if(now[stk[i]])
            maxa=max(maxa,stk[i]),cnt++;
    if(cnt>1)maxa++;
    return maxa;
}
void clear(){
    For(i,1,lev)
        now[stk[i]]=0;
    lev=0;
}
void dfs(int x){
    if(!g[x].size())
        d[x]=0;
    else if(g[x].size()==1)
        for(auto to:g[x]){
            dfs(to);
            d[x]=d[to]+1;
    }else{
        d[x]=0;
        for(auto to:g[x])
            dfs(to);
        for(auto to:g[x])
            add(d[to]);
        d[x]=calc();
        clear();
    }
}
void solve(){
    read(n);
    For(i,1,n)
        g[i].clear();
    For(i,2,n){
        read(fa[i]);
        g[fa[i]].pb(i);
    }
    dfs(1);
    print(d[1],'\n');
}
```

---

