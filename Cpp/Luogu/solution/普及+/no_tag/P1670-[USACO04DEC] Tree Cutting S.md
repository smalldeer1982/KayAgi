# [USACO04DEC] Tree Cutting S

## 题目描述

约翰意识到贝茜建设网络花费了他巨额的经费，就把她解雇了。贝茜很愤怒，打算狠狠报复。她打算破坏刚建成的约翰的网络。约翰的网络是树形的，连接着 $N$ 个牛棚。她打算切断某一个牛棚的电源，使和这个牛棚相连的所有电缆全部中断。之后，就会存在若干子网络。为保证破坏够大，每一个子网的牛棚数不得超过总牛棚数的一半，那哪些牛棚值得破坏呢？

## 说明/提示

$1\le N\le 10^4$。

## 样例 #1

### 输入

```
10
1 2
2 3
3 4
4 5
6 7
7 8
8 9
9 10
3 8```

### 输出

```
3
8
```

# 题解

## 作者：MoonCake2011 (赞：8)

# 前置知识：[树的重心](https://blog.csdn.net/qiancm/article/details/118856915)

此题呢是可以 $n$ 次 `dfs`，以 $\text O(n^2)$ 的时间复杂度求解的。

但，这只是常规做法。

众所周知，树的重心可以以一次 `dfs` 以玄妙的方式求解**以一个节点为根的最大子树大小**。

这不是这道题需要去比较的吗？

我们把**以一个节点为根的最大子树大小**存在一个数组里面，再以一个循环比较输出就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int head[10010],to[20010],nxt[20010],tot;
void add(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
int dp[10010],siz[10010];
void dfs(int x,int fa){
	siz[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		if(to[i]==fa) continue;
		dfs(to[i],x);
		siz[x]+=siz[to[i]];
		dp[x]=max(dp[x],siz[to[i]]);
	}
	dp[x]=max(dp[x],n-siz[x]);
}
int main() {
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs(1,0);
	int mid=n>>1,cnt=0;
	for(int i=1;i<=n;i++)
		if(dp[i]<=mid)
			cnt++,cout<<i<<"\n";
	if(!cnt) cout<<"NONE";
	return 0;
} 
```

---

## 作者：2021changqing52 (赞：6)

### 思路
我们可以做一遍 DFS 来找出每个节点的儿子，然后算出以每个节点为根的子树的大小，再枚举牛棚检查是否可以。
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d[10005];
vector<int>e[10005],son[10005];
void dfs(int u,int fa){//DFS
	d[u]=1;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v==fa)continue;
		dfs(v,u);
		son[u].push_back(v);
		d[u]+=d[v];
	}
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,-1);
	int w=1;
	for(int i=1;i<=n;i++){
		bool f=1;//检查
		for(int j=0;j<son[i].size();j++){
			int u=son[i][j];
			if(d[u]>n/2){
				f=0;
				break;
			}
		}
		if(d[i]>=n/2&&f)cout<<i<<endl,w=0;
	}
	if(w)puts("NONE");
	return 0;
}
```


---

## 作者：Miku_QwQ (赞：4)

### 这是蒟蒻的第一篇题解，有错误请指出。

[题目传送门](https://www.luogu.com.cn/problem/P1670)

# 本题芝士：[树的重心](https://oi-wiki.org/graph/tree-centroid/)

## 题意简述：
给定一棵 $N$ 个节点的 __无根树__ 。现在要找到所有的节点，使得删除这个节点之后，剩余的所有连通块中 __最大__ 连通块的大小 $S \leq \frac{N}{2}$。

## 解题思路
观察题意，发现删去的节点性质与树的 __重心__ 一模一样。所以本题即为求解树的重心。

### $O(n^{2})$ 做法

枚举每个点，找到以它的邻接点为根的子树进行 dfs，最后进行一个判断就可以了。

代码蒟蒻就不贴了。~~虽然吸个氧好像是能过的，但这并不是蒟蒻想要介绍的正解。~~

### $O(n)$ 做法

我们发现，对于一棵 __有根树__ ，删去一个节点 $a$ 后所有的连通块有以下两种：

- $a$ 的所有子树

- $a$ 的父节点往上构成的连通块

其中 $a$ 的子树的大小可以一边 dfs 预处理求出，而 $a$ 的父节点往上构成的连通块的大小可以反向思考。

我们发现：向上连通块的大小即为总的节点个数减去以 $a$ 为根的子树节点数。

所以，对于无根树的处理，方法来了：

先任意指定一个节点作为 __无根树的根__ ，一遍 dfs 把这棵无根树处理成有根树。

接下来进行第二次 dfs，处理出以每个节点为根的子树大小。

最后枚举每个点，进行判断即可。注意特判无解情况，输出 ```NONE```。

## 代码实现

题目中并没有说电缆的两端一定是按父子关系给出的，所以蒟蒻就按无根树来处理了。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
vector<int> G[10010],Tree[10010];//G：无根树 Tree：有根树
int s[10010];//大小
bool vis[10010];//构建无根树的标记
void dfs(int u){//构建无根树
	vis[u]=true;
	for(int i=0;i<G[u].size();i++){
		if(!vis[G[u][i]]){
			Tree[u].push_back(G[u][i]);
			dfs(G[u][i]);
		}
	}
}
void DFS(int u){//预处理子树大小
	s[u]=1;
	for(int i=0;i<Tree[u].size();i++){
		DFS(Tree[u][i]);
		s[u]+=s[Tree[u][i]];
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	DFS(1);
	bool flag=false;
	for(int i=1;i<=n;i++){
		int maxn=0;
		for(int j=0;j<Tree[i].size();j++){//找下方连通块
			maxn=max(maxn,s[Tree[i][j]]);
		}
		maxn=max(maxn,n-s[i]);//找上方连通块
		if(maxn*2<=n){
			printf("%d\n",i);
			flag=true;//标记
		}
	}
	if(flag==false){//特判
		printf("NONE");
	}
	return 0;
}
```

然后：

![](https://www.luogu.com.cn/images/congratulation.png)

---

## 作者：Chengqijun2012 (赞：3)

# 题解：P1670 [USACO04DEC] Tree Cutting S

一道水绿，废话不多说直接开始讲解。

## 解题步骤：
首先开始思考解题方法，题目中说这是一颗树，于是直接锁定关于树的算法。然后再观察题目，“为保证破坏够大，每一个子网的牛棚数不得超过总牛棚数的一半”这句话直接告诉了我们这题所需的算法——**树的重心**，因为树的重心的定义正是：**如果在树中选择某个节点并删除，这棵树将分为若干棵子树，统计子树节点数并记录最大值。取遍树上所有节点，使此最大值取到最小的节点被称为整个树的重心。（摘自 [OI-Wiki 树的重心](https://oi-wiki.org/graph/tree-centroid/)）**

众所周知，在求树的重心时我们通常会用一个数组，比如：$ms_{i}$ 来记录第 $i$ 个节点被删除后每棵子树节点数的最大值（也可以理解为：对于第 $i$ 个节点，以 $i$ 为根求 $i$ 的所有子树的节点数的最大值）。而这道题与树的重心模板唯一的不同在于它多了一个要求：只要破坏该节点后**每一个子网的牛棚数不得超过总牛棚数的一半**即可输出。因此我们只需在跑完求树的重心的 DFS 后把所有 $ms \le \frac{n}{2}$ 的节点输出即可。

## 时间复杂度：
由于主体代码只跑了一遍 DFS 求树的重心，所以时间复杂度为 $O(n+m)$。

AC Code：
```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <map>
#include <bitset>
#include <cstdio>
#define ll long long
#define P pair<int, int>
#define MP make_pair
#define PU push_back
#define li(x) x << 1
#define ri(x) (x << 1) | 1
using namespace std;
const ll LLF = LLONG_MAX >> 2;
const int INF = INT_MAX >> 1;
const int N = 1e4 + 5;
int n, tot, head[N], son[N], ms[N];

struct Edge{
	int u, v, w, nex;
}e[N << 1];

inline ll read(){
	ll f = 1, x = 0;
	char c = getchar();
	while(c < '0' || c > '9'){if(c == '-') f = -1; c = getchar();}
	while('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (ll)(c - '0'), c = getchar();
	return x * f;
}

inline void write(ll x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

inline void add(int u, int v){
	e[++tot] = {u, v, 1, head[u]};
	head[u] = tot;
}

void DFS(int u, int fr){
	son[u] = 1;
	for(int i = head[u]; i; i = e[i].nex){
		int v = e[i].v;
		if(v == fr) continue;
		DFS(v, u);
		son[u] += son[v];
		ms[u] = max(ms[u], son[v]);
	}
	ms[u] = max(ms[u], n - son[u]);
}

int main(){
//	freopen("water.in.txt", "r", stdin);
//	freopen("water.out.txt", "w", stdout);
	
//	ios::sync_with_stdio(false);
//  cin.tie(0), cout.tie(0);
	
	n = read();
	for(int i = 1, u, v; i < n; ++i){
		u = read(), v = read();
		add(u, v), add(v, u);
	}
	DFS(1, 0);
	bool f = false;
	for(int i = 1; i <= n; ++i) if(ms[i] <= (n >> 1)) f = true, write(i), putchar('\n');
	if(!f) puts("NONE");
	return 0;
}
```
完结撒花！！！

---

## 作者：SegmentSplay (赞：1)

## $O(n^2)$ 思路

注意到 $n \leq 10^4$，所以可以枚举每个点把树掰开判断剩下的连通块里有没有大于 $\frac n2 $ 的。

时间复杂度 $O(n^2)$ 可以通过。 

~~好的绿题被我们变成了黄题。~~

 $O(n^2)$ 时间复杂度的代码请自己实现。~~绝对不是我懒得写第二个代码了~~

## $O(n)$ 思路

前置芝士：[树的重心](https://oi-wiki.org/graph/tree-centroid/) 。

你说的对，虽然 $O(n^2)$ 的时间复杂度能过，但还是太吃时间了，有没有更强势的算法？

有的兄弟，有的！

考虑一种算法，可以在一次搜索中求出所有点的最大子树大小。

你想到了什么？没错，就是树的重心！

大体思路：
任意以一个点作为树的根，进行一次 DFS，每次用搜到的点的最大子树大小更新当前点的最大子树大小。

- 由于这是一棵无根树，所以父节点的子树也算一棵合法的子树。计算方法：用总节点数减去当前节点其他所有子树的节点数。

- 还有一个细节：众所周知，树的重心一定满足其最大子树节点数小于总结点数一半的性质，而一棵无根树肯定存在一个重心。所以，**无解的情况其实根本不存在**！

## AC 代码

说明: $s_i$ 表示对于当前节点，以 $1$ 为根时，所有子树的节点数总和。$d_i$ 表示 节点 $i$ 最大子树的节点个数。

存图采用利用 `vector` 实现的邻接表方式。

吸上氧气以后跑的飞快。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool vis[10005];
int s[10005],n,d[10005]; 
vector<int>v[10005];
void dfs(int x)
{
	vis[x]=s[x]=1;
	int ans=0;
	for(int i=0;i<=v[x].size()-1;i++)
	{
		int t=v[x][i];
		if(vis[t])
		{
			continue;
		}
		dfs(t);
		s[x]+=s[t];
		ans=max(ans,s[t]); 
	}
	ans=max(ans,n-s[x]);
	d[x]=ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		int u,vv;
		cin>>u>>vv;
		v[u].push_back(vv);
		v[vv].push_back(u);
	}
	dfs(1);
	for(int i=1;i<=n;i++)
	{
		if(d[i]<=(n/2))
		{
			cout<<i<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：云雷心柠檬听 (赞：1)

[博客食用更加](https://www.cnblogs.com/lemon-cyy/p/18961456)

### 题意简述

给定一个有 $n$ 个节点的树，要求输出所有的节点 $u$ 使得当这棵树以 $u$ 为根的时候，其儿子为根的子树大小小于节点数 $n$ 的一半。如果没有这样的 $u$ 输出 `NONE`。

### 思维路径

首先考虑计算子树大小，使用 dfs 遍历一遍即可，时间复杂度为 $O(n)$，如果枚举每一个节点作为根则复杂度达到 $O(n^2)$，对于本题来说太大，因此我们需要更好的优化方案。

由此可见，我们大概率只会进行一次 dfs 遍历。我们将样例的图画出来，进行研究。
![](https://cdn.luogu.com.cn/upload/image_hosting/9vb6oq17.png)

考虑到 3 号点是一个答案，我们以它为例研究，在下图中我标出了需要与 $n/2$ 比较大小的子树。
![](https://cdn.luogu.com.cn/upload/image_hosting/nqtskwdm.png)

观察可见，橙框和绿框中的子树大小就是以 $1$ 为根时子树大小，不必另外计算，而红框中的节点数恰好为总节点数 $n$ 减去 $3$ 号点的子树大小。通过这种方法即可仅用一次 dfs 计算出所有需要的数值。

随后遍历每个点是否符合条件即可，这个步骤也可以与 dfs 本身合并。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10009;
int n,ok[N],ans,sz[N];
vector<int> es[N];

void input(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		es[u].push_back(v);
		es[v].push_back(u); 
	}
}

void dfs(int u,int fa){
	for(int i=0;i<es[u].size();i++){
		int v=es[u][i];
		if(v==fa) continue;
		dfs(v,u);
		sz[u]+=sz[v];
		if(sz[v]>n/2) ok[u]=0;
	} 
	sz[u]++;
	if(n-sz[u]>n/2) ok[u]=0;
}

void solve(){
	for(int i=1;i<=n;i++) ok[i]=1; 
	dfs(1,0);
	for(int i=1;i<=n;i++){
		if(ok[i]){
			cout<<i<<"\n";
			ans++;
		}
	}
	if(!ans) cout<<"NONE";
}

int main(){
	input();
	solve();
	return 0;
}
```

---

## 作者：xxxxxzy (赞：1)

#### P1670的题解

树的重心的模板题。

首先，树的重心的定义：删除后使产生的最大部分最小的点。

而题目目标就是要求出删除所有点后的最大子树。

暴力一个点一个点枚举是 $O(n^{2})$ 的时间复杂度，不多赘述，下面介绍 $O(n)$ 的算法：

删除一个点后，剩余的部分必然分为两类：

- 一类是它的所有以子节点为根的子树

- 另一类是去掉以它为根的子树的树

对于第一类情况，只需要递归枚举即可；

对于第二类情况，只需要处理完第一类情况后，用总结点减去当前子树的节点总和就是剩余的大小。

所以所有点都只用遍历一遍，也就是 $O(n)$ 的时间复杂度。

回到问题，对于每一个点，记录删除该点之后的最大联通块的顶点数，再在最后一一判断就行了。

#### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
bool v[10005];
int size[10005],n,d[10005];
vector<int> ed[10005];
void dfs(int x){
	v[x]=size[x]=1;
	int maxn=0;
	for(int i=0;i<ed[x].size();i++){
		int y=ed[x][i];
		if(v[y]) continue;
		dfs(y);
		size[x]+=size[y];
		maxn=max(maxn,size[y]); 
	}
	maxn=max(maxn,n-size[x]);
	d[x]=maxn;
}
int main(){
	cin>>n;
	for(int i=0;i<n-1;i++){
		int x,y;
		cin>>x>>y;
		ed[x].push_back(y),ed[y].push_back(x);
	}
	dfs(1);
	bool flag=0;
	for(int i=1;i<=n;i++){
		if(d[i]<=n/2){
			flag=1;
			cout<<i<<endl;
		}
	}
	if(!flag) cout<<"NONE"; 
}
```



---

## 作者：Huangjy88 (赞：1)

# P1670题解
一道树的重心的题目。我们可以以每个节点为根做 dfs，求出最大子树大小，时间复杂度为 $O(n ^ {2})$，能过此题。考虑更优秀的做法，可以用类似找树的重心的思路，一遍 dfs 求出以每个节点为根的最大子树，最后进行判断最大子树大小是否小于等于 $ \frac{n}{2} $ 即可，时间复杂度为 $O(n)$。不会重心的建议先做[这道题](https://www.luogu.com.cn/problem/P1395)。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
int n;
vector<int> v[N];
int sz[N],mss[N];
int ans;
void dfs(int x,int fa){//dfs
    sz[x]=1;
    for(int i=0;i<v[x].size();i++){
	int y=v[x][i];
	if(y==fa) continue;
	dfs(y,x);
	sz[x]+=sz[y];
	mss[x]=max(mss[x],sz[y]);//子节点
    }
    mss[x]=max(mss[x],n-sz[x]);//父节点
}
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
	int x,y;cin>>x>>y;
	v[x].push_back(y);
	v[y].push_back(x);//存图
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
	if(mss[i]<=n>>1) cout<<i<<endl;//判断
    }
    return 0;
}
```

---

## 作者：Tjaweiof (赞：0)

# P1670 题解
[题目传送门](https://www.luogu.com.cn/problem/P1670)

随便以一个点为根然后 dfs，记录每个点的子树大小，然后每个点判断是否值得破坏。判断方法：遍历子节点，若子节点的子树大小大于 $n\div2$ 就不值得；若 $n$ 减该子树大小（即剪断后上面留下的子网络大小）大于 $n\div2$ 也不值得。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int n, sz[10001];
bool ans[10001], f;
vector <int> e[10001];
void dfs(int x, int fa){
	sz[x] = 1;
	for (auto u : e[x]){
		if (u == fa){
			continue;
		}
		dfs(u, x);
		sz[x] += sz[u];
		if (sz[u] > (n >> 1)){
			ans[x] = false;
		}
	}
	if (n - sz[x] > (n >> 1)){
		ans[x] = false;
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int u, v;
	cin >> n;
	for (int i = 1; i <= n; i++){
		ans[i] = true;
	}
	for (int i = 1; i < n; i++){
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++){
		if (ans[i]){
			cout << i << "\n";
			f = true;
		}
	}
	if (!f){
		cout << "NONE";
	}
	return 0;
}

```

---

