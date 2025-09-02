# Tree Cutting (Easy Version)

## 题目描述

You are given an undirected tree of $ n $ vertices.

Some vertices are colored blue, some are colored red and some are uncolored. It is guaranteed that the tree contains at least one red vertex and at least one blue vertex.

You choose an edge and remove it from the tree. Tree falls apart into two connected components. Let's call an edge nice if neither of the resulting components contain vertices of both red and blue colors.

How many nice edges are there in the given tree?

## 说明/提示

Here is the tree from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/ab0319e6d1b3fdf0a12318f77b159c6dc359f231.png)The only nice edge is edge $ (2, 4) $ . Removing it makes the tree fall apart into components $ \{4\} $ and $ \{1, 2, 3, 5\} $ . The first component only includes a red vertex and the second component includes blue vertices and uncolored vertices.

Here is the tree from the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/7f13f482fb950c8fef37bc2658aa383ebfb7bf5b.png)Every edge is nice in it.

Here is the tree from the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F1/f3485c6c57decb8200c34309a45ff67d9c4b5fd0.png)Edge $ (1, 3) $ splits the into components $ \{1\} $ and $ \{3, 2\} $ , the latter one includes both red and blue vertex, thus the edge isn't nice. Edge $ (2, 3) $ splits the into components $ \{1, 3\} $ and $ \{2\} $ , the former one includes both red and blue vertex, thus the edge also isn't nice. So the answer is 0.

## 样例 #1

### 输入

```
5
2 0 0 1 2
1 2
2 3
2 4
2 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 0 0 0 2
1 2
2 3
3 4
4 5
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3
1 1 2
2 3
1 3
```

### 输出

```
0
```

# 题解

## 作者：Edmundino (赞：2)

# 题意

给定一棵树，树上的点有$0,1,2$三种情况，$0$代表该点无色。

现在需要你将这棵树割掉一些边，使得割掉每条边分割成的两部分均最多只含有一种颜色的点，

即分割后的两部分不能同时拥有$1,2$点($0$的点数可以任意)

求这样的边有多少个。

# 分析

其实是道树上搜索题，

我们在搜索过程中要记录每个子树的$1$和$2$节点的个数，

我们把$u$的子树有$1$节点的个数记为$s[u][1]$，$2$节点的个数记为$s[u][2]$，

那么：$s[u][1]+= s[v][1]$,$s[u][2]+= s[v][2]$，

我们把这些节点记录下来后，

就是一个判断的过程

一个子树如果满足其中的一种节点等于这种节点的全部个数，且另一种节点的个数为$0$,

那么它就是合法的。

# 代码

**$dfs$树上搜索部分**

```cpp
void dfs(int u,int fa)
{
  if(a[u]==1) s[u][1]++;
  if(a[u]==2) s[u][2]++;
  int lon=vec[u].size();
  for(int i=0;i<lon;i++)
  {
    int v=vec[u][i];
    if(v!=fa)
    {
       dfs(v,u);
       s[u][1]+=s[v][1];
       s[u][2]+=s[v][2];
    }
  }
  if(s[u][1]==0&&s[u][2]==sumb||s[u][2]==0&&s[u][1]==suma)
  {
     zs++;
  }
}

```

**$AC$代码**

```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<vector>

using namespace std;

const int N=3e5+50;

int n,a[N],suma,sumb,s[N][3],x,y,zs;

vector<int>vec[N];

void dfs(int u,int fa)
{
  if(a[u]==1) s[u][1]++;
  if(a[u]==2) s[u][2]++;
  int lon=vec[u].size();
  for(int i=0;i<lon;i++)
  {
    int v=vec[u][i];
    if(v!=fa)
    {
       dfs(v,u);
       s[u][1]+=s[v][1];
       s[u][2]+=s[v][2];
    }
  }
  if(s[u][1]==0&&s[u][2]==sumb||s[u][2]==0&&s[u][1]==suma)
  {
     zs++;
  }
}

int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
     cin>>a[i];
     if(a[i]==1)suma++;
     if(a[i]==2)sumb++;
  }
  for(int i=2;i<=n;i++)
  {
    cin>>x>>y;
    vec[x].push_back(y);
    vec[y].push_back(x);
  }
  dfs(1,0);
  cout<<zs<<endl;
  return 0;
}
```


---

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1118F1)

[CF传送门](https://codeforces.com/problemset/problem/1118/F1)

[AC记录](https://codeforces.com/contest/1118/submission/288509938)
# 题意简述
一棵树上有 $n$ 个节点，有 $0$，$1$ 和 $2$ 三种状态，问有几条边，满足这条边被删除后的左右两棵子树一个只包含 $0$ 和 $1$，一个只包含 $0$ 和 $2$。
# 题解
**总体思路：统计好以每个点为根的子树中有几个 $1$ 和几个 $2$。**  
显然，以点 $u$ 为根的的子树所含的 $1$ 和 $2$ 的个数由它的子节点 $v$ 转移过来。  
写出来长这样（`sum[x][u]` 指以 $u$ 为根的子树中有几个 $x$）：
```cpp
sum[a[u]][u]++;

sum[1][u]+=sum[1][v];
sum[2][u]+=sum[2][v];
```
大体就是说（以求 `sum[1][u]` 为例），先将所有以 $u$ 的子节点为根的的子树中 $1$ 的个数加起来，在看看点 $u$ 是不是 $1$，是就再加 $1$。

怎么判断这条边可不可以删呢？  
其实很简单。  
既然我们已经统计好以每个点为根的子树中有几个 $1$ 和几个 $2$，我们就可以看删掉边后的两棵树**是否含有所有的 $1$ 或 $2$，并不含任何 $2$ 或 $1$** 即可。  
判断条件是这样的：`sum[1][x]==s[1]&&sum[2][x]==0||sum[1][x]==0&&sum[2][x]==s[2]`  
若满足条件，给答案加 $1$。

dfs 什么的应该不用我说吧。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=6e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
int ver[M],w[M],Next[M],head[M],tot,n,x,y,a[M],sum[3][M],s[3],ans;
void add(int x,int y){
    Next[++tot]=head[x];
    ver[tot]=y;
    head[x]=tot;
}
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void print(ll x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
    return;
}
void dfs(int x,int fa){
    sum[a[x]][x]++;
    for(int i=head[x];~i;i=Next[i]){
        int v=ver[i];
        if(v==fa) continue;
        dfs(v,x);
        sum[1][x]+=sum[1][v];
        sum[2][x]+=sum[2][v];
    }
    if(sum[1][x]==s[1]&&sum[2][x]==0||sum[1][x]==0&&sum[2][x]==s[2]) ans++;
}
int main(){
    mem(head,-1);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],s[1]+=(a[i]==1),s[2]+=(a[i]==2);
    for(int i=1;i<n;i++){
        cin>>x>>y;
        add(x,y);
        add(y,x);
    }
    dfs(1,-1);
    cout<<ans;
    return 0;
}
```

---

## 作者：gyh2024 (赞：1)

题意
======
一棵树，有多个结点，每一个节点中都有颜色，只有红色， 蓝色或无色。在里面删除一条边。使树中没有同时有红色和蓝色。求最多有多少条边能删除！

思路
------
我们可以定义一个数组来存储每一个节点下面和他本身的红色数量和蓝色的数量。最后再一个个判断删除每一条边是否可行。 最后再统计即可。

AC代码
------
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int col[N];
vector<int> arr[N];
int cnt;
int ans[N][3],sum1,sum2;
void dfs(int x,int fa) {
	if(col[x]==1) {
		ans[x][1]++;
	} else if(col[x]==2) {
		ans[x][2]++;
	}
	for(int i=0; i<arr[x].size(); i++) {
		int tx=arr[x][i];

		if(tx!=fa) {
			dfs(tx,x);
			ans[x][1]+=ans[tx][1];
			ans[x][2]+=ans[tx][2];
		}
	}
	if(ans[x][1]==sum1&&ans[x][2]==0||ans[x][2]==sum2&&ans[x][1]==0) {
		cnt++;
	}
}
int main() {
	int n;
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>col[i];
		if(col[i]==1) {
			sum1++;
		}
		if(col[i]==2) {
			sum2++;
		}
	}
	for(int i=1; i<n; i++) {
		int u,v;
		cin>>u>>v;
		arr[u].push_back(v);
		arr[v].push_back(u);
	}
	dfs(1,116);
	cout<<cnt;

	return 0;
}
```

---

## 作者：Allanljx (赞：1)

# CF1118F1 题解
[洛谷传送门](https://www.luogu.com.cn/problem/CF1118F1)
[CF传送门](https://codeforces.com/problemset/problem/1118/F1)
## 思路
当这其中一棵树有多余一种颜色时，显然是不合法的。当其中一棵树有一种颜色，但这种颜色的总共的数量大于这棵树中这种颜色的数量，也是不行的。所以我们就可以统计其中一棵树的每种颜色的数量。

如何统计呢？我们可以树形 $dp$ 一下。$sum_{i,1}$ 表示以第 $i$ 个节点为根的子树，有多少个节点的颜色是红色；$sum_{i,2}$ 表示以第 $i$ 个节点为根的子树，有多少个节点的颜色是蓝色。转移：设当前这个节点为 $u$，它的子结点为 $v$，$a_i$ 表示第 $i$ 个节点的颜色。
```
sum[u][a[u]]++,sum[u][1]+=sum[v][1];
sum[u][2]+=sum[v][2];
```
这时候就相当于删掉节点 $u$ 与它的的父节点的边。

$sum1,sum2$ 分别表示红色和蓝色节点的总个数。枚举每一个节点，当 
```
0==sum[i][2]&&sum[i][1]==sum1||0==sum[i][1]&&sum[i][2]==sum2
```
时这条边就可以删。有一种颜色只在这颗子树中出现并且这颗子树中没有另一种颜色。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[300005],sum[300005][3],sum1,sum2,ans;
vector<int> tr[300005];
void dfs(int u,int f)
{
	sum[u][a[u]]++;//当前节点的颜色
	for(int i=0;i<tr[u].size();i++)
	{
		int v=tr[u][i];
		if(v==f) continue;
		dfs(v,u);
		sum[u][1]+=sum[v][1];//转移
		sum[u][2]+=sum[v][2];//转移
	}
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==1) sum1++;//统计红色的个数
		if(a[i]==2) sum2++;//统计蓝色的个数
	}
	for(int i=1;i<n;i++)
	{
		int uu,vv;
		cin>>uu>>vv;
		tr[uu].push_back(vv);//建边
		tr[vv].push_back(uu);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		if(0==sum[i][2]&&sum[i][1]==sum1||0==sum[i][1]&&sum[i][2]==sum2) ans++;//统计答案
	}
	cout<<ans<<endl;
}
```

---

## 作者：封禁用户 (赞：1)

萌新写题解，欢迎 HACK！

树形结构题。

我们可以使用深度优先搜索遍历树，并在遍历的过程中记录每个子树中红色和蓝色节点的数量。

具体思路&步骤
1. 初始化一个数组（或者两个变量）来记录遍历到当前节点时，红色节点和蓝色节点的数量。
2. 从任意一个节点开始 DFS 遍历整棵树。
3. 对于每个节点，我们检查与其相连的边，如果删除这条边后，与当前节点相连的子树中的红色节点和蓝色节点数量满足题目条件（即不同时含有红色和蓝色节点），则这条边是合法的。
4. 在 DFS 的过程中，我们需要更新当前节点及其子树中红色和蓝色节点的数量。

给出核心（DFS）code：

```cpp
void dfs(int u,int f)
{
	sum[u][a[u]]++;
	for(int i=0;i<tr[u].size();i++)
	{
		int v=tr[u][i];
		if(v==f) continue;
		dfs(v,u);
		sum[u][1]+=sum[v][1];
		sum[u][2]+=sum[v][2];
	}
}
```

完结撒花！！！

---

## 作者：endswitch (赞：1)

## 题意简述：

给定一棵树，每一个节点都是红色，蓝色或者无色。一条边是合法的当且仅当删除这一条边之后，树被分成两部分，这两部分不同时含有红色和蓝色。问有多少条合法的边。

## 思路：

先跑一遍树形 dp 求出每一棵子树包含的红色和蓝色节点的数量，然后对于每一条边被删除的两个部分中一定会有一棵子树。所以我们可以去用整个树整体红蓝节点的数量减去另一个子树红蓝节点的数量后可以得到另一个部分的红蓝节点的数量。最后对于两个部分判断即可。

时间复杂度 $O(n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N=3e5+5;
int n,u,v,ans,sum1,sum2,a[N],col[N][3];
vector<int> g[N];
inline void dfs(int x,int last) {
	if(a[x]==1) col[x][1]++;
	if(a[x]==2) col[x][2]++;
	for(auto u:g[x])
		if(u!=last) {
       		dfs(u,x);
       		col[x][1]+=col[u][1];
       		col[x][2]+=col[u][2];
    	}
  	if(col[x][1]==0&&col[x][2]==sum2||col[x][2]==0&&col[x][1]==sum1) ans++;
}
signed main() {
  	cin>>n;
  	for(int i=1;i<=n;i++) {
    	cin>>a[i];
    	if(a[i]==1) sum1++;
    	if(a[i]==2) sum2++;
	}
	for(int i=2;i<=n;i++)
		cin>>u>>v,g[u].pb(v),g[v].pb(u);
  	dfs(1,0);
  	cout<<ans;
  	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

## 前置

因为我比较搞笑，所以我写了一个树剖，而且本题甚至连修改都没有，可是我还是写了线段树。

## 正文

不会写树剖的出门左转：[【模板】重链剖分/树链剖分](https://www.luogu.com.cn/problem/P3384)

本题只需要维护两个东西，红色节点的数量和蓝色节点的数量。

如果把这一条边删除，就会分裂成两棵树。

第一棵树是那个深度较大的节点的子树，第二棵树就是原来的那棵树的剩余部分。

对于第二棵树的统计，用容斥原理即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 3e5 + 10;
int T,n,vist;
int col[N],x[N],y[N];
int fa[N],sz[N],wc[N],dep[N];
int dfn[N],rdfn[N];
int sum1[N << 2],sum2[N << 2];
vector <int> g[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void dfs1 (int u,int f){
	dep[u] = dep[f] + 1;
	sz[u] = 1;
	fa[u] = f;
	for (auto v : g[u]){
		if (v == f) continue;
		dfs1(v,u);
		sz[u] += sz[v];
		if (sz[wc[u]] < sz[v]) wc[u] = v;
	}
}
void dfs2 (int u){
	dfn[u] = ++vist;
	rdfn[vist] = u;
	if (wc[u]){
		dfs2(wc[u]);
		for (auto v : g[u]){
			if (v == fa[u] || v == wc[u]) continue;
			dfs2(v);
		}
	}
}
// 树剖
void pushup (int o){
	sum1[o] = sum1[o << 1] + sum1[o << 1 | 1];
	sum2[o] = sum2[o << 1] + sum2[o << 1 | 1];
}
void build (int o,int l,int r){
	if (l == r){
		if (col[rdfn[l]] == 1) sum1[o] = 1;
		if (col[rdfn[l]] == 2) sum2[o] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(o << 1,l,mid);
	build(o << 1 | 1,mid + 1,r);
	pushup(o);
}
int query1 (int o,int l,int r,int ql,int qr){
	if (ql <= l && r <= qr)
		return sum1[o];
	int mid = (l + r) >> 1;
	int ret = 0;
	if (ql <= mid) ret += query1(o << 1,l,mid,ql,qr);
	if (qr > mid) ret += query1(o << 1 | 1,mid + 1,r,ql,qr);
	return ret;
}
int query2 (int o,int l,int r,int ql,int qr){
	if (ql <= l && r <= qr)
		return sum2[o];
	int mid = (l + r) >> 1;
	int ret = 0;
	if (ql <= mid) ret += query2(o << 1,l,mid,ql,qr);
	if (qr > mid) ret += query2(o << 1 | 1,mid + 1,r,ql,qr);
	return ret;
}
// 线段树
void solve(){
	cin >> n;
	for (int i = 1 ; i <= n ; i++)
		cin >> col[i];
	for (int i = 1 ; i < n ; i++){
		cin >> x[i] >> y[i];
		g[x[i]].push_back(y[i]);
		g[y[i]].push_back(x[i]);
	}
	dfs1(1,0);
    dfs2(1);
    build(1,1,n);
    int ans = 0;
    for (int i = 1 ; i < n ; i++){
    	int u = x[i];
    	int v = y[i];
    	if (dep[u] > dep[v]) swap(u,v);
		/*
    	cout << "dot:" << v << ' ';
    	cout << query1(1,1,n,dfn[v],dfn[v] + sz[v] - 1) << ' '; // 第一棵树的红色节点数量
    	cout << query2(1,1,n,dfn[v],dfn[v] + sz[v] - 1) << ' '; // 第一棵树的蓝色节点数量
    	cout << query1(1,1,n,1,n) - query1(1,1,n,dfn[v],dfn[v] + sz[v] - 1) << ' '; // 第二棵树的红色节点数量
    	cout << query2(1,1,n,1,n) - query2(1,1,n,dfn[v],dfn[v] + sz[v] - 1) << endl; // 第二棵树的蓝色节点数量
    	*/
		if (query1(1,1,n,dfn[v],dfn[v] + sz[v] - 1) > 0 && query2(1,1,n,dfn[v],dfn[v] + sz[v] - 1) > 0) continue;
		if (query1(1,1,n,1,n) - query1(1,1,n,dfn[v],dfn[v] + sz[v] - 1) > 0 && query2(1,1,n,1,n) - query2(1,1,n,dfn[v],dfn[v] + sz[v] - 1) > 0) continue;
		ans++;
	}
	cout << ans << endl;
}
signed main(){
	close();
	T = 1;
	while (T--) solve();
	return 0;
}
```

---

## 作者：RioFutaba (赞：0)

## 题意
给定一棵树和每个节点的颜色，颜色只有红、蓝、不染色三种。问有多少条边，满足这条边被删除后树分成的两部分不同时含有红色和蓝色。
## 做法
枚举删除的边。

如下图，删除一条边，就是把树分成两部分，第一部分是边连接的两个节点中，深度较大的那棵节点的子树。其余则是其他节点。


那么我们自底向上，统计每个节点的子树里颜色为红的节点和蓝的节点的个数，再进行判断即可。
![样例](https://cdn.luogu.com.cn/upload/image_hosting/jckqwfbx.png)
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=6e5+5;
int n,a[maxn],head[maxn],ne[maxn],to[maxn],tot;
int rc,bc,ans;
int r[maxn],b[maxn];
void add(int u,int v){
	to[++tot]=v;
	ne[tot]=head[u];
	head[u]=tot;
}//链式前向星
void dfs(int u,int fa){
	if(a[u]==1) r[u]=1;
	else if(a[u]==2) b[u]=1;
	for(int i=head[u];i;i=ne[i]){
		int v=to[i];
		if(v==fa) continue;
		dfs(v,u);
		if((rc-r[v]==0 || bc-b[v]==0) && (r[v]==0 || b[v]==0))//判断子树和其余节点中是否只有一种颜色
			ans++;
		r[u]+=r[v];b[u]+=b[v];
	}
	
}
int main(){
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		if(a[i]==1) rc++;
		else if(a[i]==2) bc++;//记录整棵树里蓝色节点和红色节点有多少个
	}
	for(int i=1,u,v;i<n;i++){
		cin >> u >> v;
		add(u,v);
		add(v,u);//双向边
	}
	dfs(1,0);//以1为根
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

给一棵树，每一个节点都是红色，蓝色或者无色。

一条边是合法的当且仅当删除这一条边之后，树被分成两部分，这两部分不同时含有红色和蓝色。

问有多少条合法的边。

## 题目分析

考虑先搜索一遍这棵树，并处理出以 $x$ 节点为根的子树中红点和蓝点的数量，记为 $red_x$ 和 $blue_x$。树中所有的蓝点和红点的数量记为 $\texttt{BLUE}$ 和 $\texttt{RED}$。

如果 $u \rightarrow v$ 这条边是合法的，那么以 $v$ 为根的子树中仅有一种有颜色的点，即以下两种情况：

- $red_v=\texttt{RED}$ 并且 $blue_v=0$。
- $blue_v=\texttt{BLUE}$ 并且 $red_v=0$。

在搜索的时候判断即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define random(a,b) (rand()%(b-a+1)+a)
const int N=3e5+10;
vector<int> G[N];
int n,a[N],Blue,Red,ans;
pair<int,int> dfs(int u,int father)
{
	int blue=(a[u]==2),red=(a[u]==1);
	for(int v:G[u])
	{
		if(v!=father)
		{
			auto temp=dfs(v,u);
			int A=temp.first,B=temp.second;
			if((A==Blue&&B==0)||(A==0&&B==Red)) ans++;
			blue+=A,red+=B;
		}
	}
	return {blue,red};
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
    	if(a[i]==2) Blue++;
    	if(a[i]==1) Red++;
	}
	for(int u=0,v=0,i=1;i<n;i++)
	{
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：EDqwq (赞：0)

我们经过简易的观察发现，当一个点的子树拥有所有的蓝点，并且没有红点，或者，拥有所有的红点，并且没有蓝点的话，就会出现对应的一条边，是一个答案。

为什么呢？因为我们剪掉了这条边之后，那些所有的蓝/红点就会和剩下的点分开。

所以我们做简单的树形dp求出子树蓝/红点，然后判断一下即可。

这里有一个可能出现的小坑，如果你是记录 $fa$ 的 dfs ，请把初始 $fa$ 设为 $0$ 而不是 $-1$。

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

struct node{
	int to;
	int nxt;
}e[1000010];

int cnt,head[1000010];
int n;
int a[1000010];
int num1[1000010],num2[1000010];
int cnt1,cnt2;
int ans;

void add(int x,int y){
	cnt ++;
	e[cnt].to = y;
	e[cnt].nxt = head[x];
	head[x] = cnt;
}

void dfs(int x,int fa){
	for(int i = head[x];i;i = e[i].nxt){
		int v = e[i].to;
		if(v != fa){
			dfs(v,x);
			num1[x] += num1[v];
			num2[x] += num2[v];
		}
	}
	if((num1[x] == cnt1 && num2[x] == 0) || (num2[x] == cnt2 && num1[x] == 0))ans ++;
}

signed main(){
	cin>>n;
	for(int i = 1;i <= n;i ++){
		a[i] = read();
		if(a[i] == 1)cnt1 ++,num1[i] ++;
		if(a[i] == 2)cnt2 ++,num2[i] ++;
	}
	for(int i = 1;i <= n - 1;i ++){
		int x,y;
		x = read(),y = read();
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：Erusel (赞：0)

我们先随便钦定一个根，然后统计每个子树内部的红色节点数和蓝色节点数

然后考虑每一个点与父亲相连的那条边

有两个要求：

$1.$子树内部的红色和蓝色节点数至少有一个为 $0$

$2.$考虑断去这条边后的另外一棵树，满足的条件为它的红蓝节点数至少有一个为 $0$

我们用 $s[u][1]$ 表示以 $u$ 为根节点的子树内部红色节点数

用 $s[u][2]$ 表示以 $u$ 为根节点的子树内部蓝色节点数

那么 $s[root][1]-s[u][1]$ 和 $s[root][2]-s[u][2]$ 中至少有一个为 $0$

统计一下即可，时间复杂度 $O(n)$

**Code:**

```cpp
#include<bits/stdc++.h>
 
#define rd(x) x=read()
 
#define N 300005 
 
using namespace std;
 
int n; 
int a[N],s[N][2];
vector<int>e[N];
 
inline void addEdge(int u,int v){e[u].push_back(v);}
 
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
 
inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}
 
void dfs(int u,int fa)
{
	if(a[u])s[u][a[u]]=1;
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i];
		if(v==fa)continue;
		dfs(v,u),s[u][1]+=s[v][1],s[u][2]+=s[v][2];
	}
}
 
int ans;
 
int main()
{
	rd(n);
	for(int i=1;i<=n;i++)rd(a[i]);
	for(int i=1,u,v;i<n;i++)rd(u),rd(v),addEdge(u,v),addEdge(v,u);
	dfs(1,0);for(int i=2;i<=n;i++)
	{
		if(s[i][1]&&s[i][2])continue;
		if((s[1][1]^s[i][1])&&(s[1][2]^s[i][2]))continue;
		ans++;
	}
	cout<<ans<<endl;
 
 
    return 0;
}
```

---

