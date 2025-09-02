# Bear and Friendship Condition

## 题目描述

Bear Limak examines a social network. Its main functionality is that two members can become friends (then they can talk with each other and share funny pictures).

There are $ n $ members, numbered $ 1 $ through $ n $ . $ m $ pairs of members are friends. Of course, a member can't be a friend with themselves.

Let A-B denote that members A and B are friends. Limak thinks that a network is reasonable if and only if the following condition is satisfied: For every three distinct members (X, Y, Z), if X-Y and Y-Z then also X-Z.

For example: if Alan and Bob are friends, and Bob and Ciri are friends, then Alan and Ciri should be friends as well.

Can you help Limak and check if the network is reasonable? Print "YES" or "NO" accordingly, without the quotes.

## 说明/提示

The drawings below show the situation in the first sample (on the left) and in the second sample (on the right). Each edge represents two members that are friends. The answer is "NO" in the second sample because members $ (2,3) $ are friends and members $ (3,4) $ are friends, while members $ (2,4) $ are not.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF771A/452e04bb457330535035b94604ffb28f5fa05d56.png)

## 样例 #1

### 输入

```
4 3
1 3
3 4
1 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 4
3 1
2 3
3 4
1 2
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
10 4
4 3
5 10
8 9
1 2
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
3 2
1 2
2 3
```

### 输出

```
NO
```

# 题解

## 作者：xxzjbd (赞：6)

## 题目分析
给出 $n$ 个点及 $m$ 条边，判断有关系的点间是否都是两两相连。

既然要保证两两相连，那么每个连通块必须为完全图，若连通块有 $i$ 个点，则对边数的贡献为 $i * ( i - 1 )$ $/$ $2$ 。又因为总共只有 $m$ 条边，所以把连通块总边数相加与 $m$ 比较，判断是否符合即可得出答案。

各位大佬的思路差不多，代码实现略有不同。本人以并查集实现，稍微通俗易懂些。
## 代码如下
```cpp
#include<cstdio>
#define int long long
using namespace std;
int fa[150010],num[150010];
int sum;
int fi(int x){
	if(fa[x]==x)return x;
	else return fa[x]=fi(fa[x]);
}
void add(int x,int y){
	int xx=fi(x),yy=fi(y);
	if(xx==yy)return;
	fa[yy]=xx;
	num[xx]+=num[yy];
	num[yy]=0;
}
signed main(){
	int n,m;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		fa[i]=i;
		num[i]=1;
	}
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y);
	}
	for(int i=1;i<=n;i++)
		if(num[i]>1)sum+=num[i]*(num[i]-1)/2;		
	if(sum==m)printf("YES");
	else printf("NO");
	return 0;
}
```
记得开 $long long$
## 谢谢观赏

---

## 作者：Priori_Incantatem (赞：3)

### 题目大意

给出一张无向图，对于每一个点三元组 $x,y,z$ ，若 $(x,y)$ $(y,z)$ 之间分别都有连边，那么$(x,z)$ 之间也必须有连边

对于给出的无向图，求出该图是否满足要求

观察上面规则的性质，我们发现对于 由一个点三元组组成的连通块，要满足上面要求，必须每两个点之间都有一条连边，也就是满足该连通块是一个完全图  
完全图的其中一个判定方法，就是判断一下方程是否成立：$\frac{n(n-1)}{2}=m$ （$n$为点数，$m$为变数）

由此，题目就被我们转换成了：对于给出的无向图，求出该图所有连通块是否满足完全图性质

**代码：**
```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const long long Maxn=150000+20,inf=0x3f3f3f3f;
vector <long long> e[Maxn];
bool vis[Maxn];
long long n,m;
inline long long read()
{
	long long s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
bool bfs(long long s)
{
	queue <long long> q;
	vis[s]=1,q.push(s);
	long long cnt=0,tot=0;
	while(q.size())
	{
		long long x=q.front();
		q.pop();
		++cnt;
		for(long long i=0;i<e[x].size();++i)
		{
			long long y=e[x][i];
			++tot;
			if(vis[y])continue;
			vis[y]=1,q.push(y);
		}
	}
	if(cnt==1)return 1;
	tot>>=1;
	
	return ((cnt*(cnt-1))>>1) == tot;
}
int main()
{
	//freopen("in.txt","r",stdin);
	n=read(),m=read();
	for(long long i=1;i<=m;++i)
	{
		long long x=read(),y=read();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	bool flag=1;
	for(long long i=1;i<=n;++i)
	{
		if(vis[i])continue;
		flag=(flag & bfs(i));
		if(!flag)break;
	}
	
	if(flag)puts("YES");
	else puts("NO");
	
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：2)

upd：刚交上去，发现手残写错数组名了，在此致歉。

## 思路

题目要求，若 $i,j$ 和 $j,k$ 之间有边，那么 $i,k$ 之间必须有边。看上去似曾相识，我们不妨大胆猜测。

那么我们假设一个连通的符合要求的图不是完全图。那么也就是说存在这么一些点 $(i,k)$ 他们之间没有边。

又因为这个图是连通的，它们之间一定最少通过若干个点相连。假设这若干个点有 $k$ 个，记为 $d_1...d_k$。

- 如果 $k = 1$，那么显然 $(i,d_1)$ 有边，$(d_1,k)$ 有边，但是 $(i,k)$ 没有边，是不符合要求的；

- 如果 $k>1$，显然在 $(i,d_1)$ 有边，$(d_1,d_2)$ 有边。又因为 $i$ 所经过的这条是最短路径，所以 $(i,d_2)$ 间不可能有路径。

因此 $(i,k)$ 连通但是之间没有边的情况是不成立的，证毕。所以一个连通的符合条件的图必须是完全图。

又因为题目没有要求图必须连通，所以这个图可以有许多个互不相连的子图组成。我们只需要判断这个图的每一个连通块是不是完全图即可。实际上，我们不需要算出每个连通块的边数，只需要假设这些连通块都是完全图，算出来比较即可。之所以能这样做，是因为完全图的边数最大，最后算出来的理论边数 $M$ 只会大于等于实际边数。

最后记得开 long long qwq

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int fa[150005];
long long tot[150005]; // tot[i] 表示以 i 为“爸爸”的连通块有多少个点。
int find(int k)
{
	if(fa[k]==k) return k;
	return fa[k]=find(fa[k]);
	// 等价于 return (fa[k]==k)?k:fa[k]=find(fa[k]);
}
int main()
{
	int n,m; scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i,tot[i]=1; // 并查集预处理
	for(int i=1;i<=m;i++)
	{
		int x,y; scanf("%d%d",&x,&y);
		int fx=find(x),fy=find(y);
		if(fx!=fy) fa[fx]=fy,tot[fy]+=tot[fx]; // 并查集合并连通块 基本操作。
	}
	long long ans=0; // 记得开 long long。
	for(int i=1;i<=n;i++)
		if(find(i)==i) // 如果 i 的“爸爸”是 i 说明是一个全新的连通块
			ans+=tot[i]*(tot[i]-1)/2; // 加上完全图的边数 n(n-1)/2
	if(ans==m) puts("YES");
	else puts("NO");
	return 0;
}
```

---

## 作者：一个简单名字 (赞：2)

# CF771A

## 知识点

并查集的[**按秩合并** ]([](https://oi-wiki.org/ds/dsu/))

## solution

题目转换，判断整张图是否是张完全图，根据完全图的性质
$$
\frac{n(n-1)}{2}=m
$$
$n$ 为点数，$m$ 为边数。考虑用并查集维护两点的连通关系，这里要维护这个连通块里的点的数量，即 $num$ 数组。最后遍历每个点，统计下整张图的理论上的边数 $ans$ ，等于 $m$ 输出 $YES$ ,反之输出 $NO$ 。  

## code

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std ;
const int maxn = 2e5+7 ;
int num[maxn] , fa[maxn] ;
int n , m , ans , tot ; 
int find(int x)
{
	if(x == fa[x])	return x ;
	return fa[x] = find(fa[x]) ;	
}
void merg(int x,int y)
{
	int a = find(x) , b = find(y) ;
	if(a == b)	return ;
	fa[a] = b ;	num[b] += num[a] ;//按秩合并操作
	num[a] = 0 ;//合并完成，该点清零 
}
signed main()
{
	cin>>n>>m ;	tot = m ;
	for(int i = 1 ; i <= n ; i++)//并查集初始化 
		fa[i] = i , num[i] = 1 ;
	while(m--)
	{
		int x , y ;
		cin>>x>>y ;
		merg(x,y) ;
	}
	for(int i = 1 ;i <= n ; i++)
		if(num[i])	ans += num[i] * (num[i]-1) >> 1 ;
	if(ans == tot)	cout<<"YES"<<endl ;
	else cout<<"NO"<<endl ;
	return 0 ;
} 
```

work by simon

---

## 作者：Ginger_he (赞：1)

本文同步更新于[博客园](https://www.cnblogs.com/Gingerhe/p/16315980.html)
# 题目描述
给定一张无向图，要求如果 $A$ 与 $B$ 之间有边，$B$ 与 $C$ 之间有边，那么 $A$ 与 $C$ 之间也需要有边，问这张图是否满足要求。
# 题解
不难发现，如果一个连通块满足上述条件，那它一定是一个完全图。而一个完全图又需要满足 $\mathrm{C}_n^2=m$，其中 $n$ 为点数，$m$ 为边数，所以我们在并查集的 $\texttt{merge}$ 中顺便记录下点数和边数即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 150005
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int n,m,u,v,f[N];
ll g[N],e[N];
bool flag;
set<int> s;
int find(int x)
{
	if(x==f[x])
		return x;
	return f[x]=find(f[x]);
}
void merge(int x,int y)
{
	x=find(x),y=find(y);
	e[y]++; 
	if(x==y)
		return;
	f[x]=y;
	g[y]+=g[x];
	e[y]+=e[x];
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		g[i]=1;
	}
	for(int i=1;i<=m;i++)
	{
		u=read(),v=read();
		merge(u,v);
	}
	for(int i=1;i<=n;i++)
		s.insert(find(i));
	for(auto i:s)
		flag|=(g[i]*(g[i]-1)/2!=e[i]);
	printf("%s\n",flag?"NO":"YES");
	return 0;
}
```

---

## 作者：墨舞灵纯 (赞：1)

现存的神仙题解只有一句话：“按照题意，所求的图需要是一个完全图。此时输出yes,否则输出no”。所以我补充一点吧。

一个朴素的想法是把所有连通的点缩起来，然后判断每个连通块内的点数和边数是否存在dot*(dot-1)/2==edge的关系。然后我们会自然地想到用并查集把所有点并起来，不需要缩点。那么每次我们合并的时候记录一下点和边，进行启发式合并就行了。主要的代码可以参见现存的神仙题解，这里给出核心部分。


$\mathcal\textcolor{Gold}{Code:}$
```
for(int i=1,u,v;i<=m;++i)
{
	cin>>u>>v,u=find(u),v=find(v);
	if(u==v)
	{
		++edge[u];continue;//在同一个连通块之内，多一条边
	}
    if(cnt[u]>cnt[v])
    {
    	cnt[u]+=cnt[v];
        edge[u]+=edge[v]+1;
        fa[v]=u;
    }
    else
    {
    	cnt[v]+=cnt[u];
        edge[v]+=edge[u]+1;
        fa[u]=v;
    }//启发式合并，累加边和点的贡献
} 

```

---

## 作者：TPJX (赞：0)

### 题目分析

题目大意就是说判断无向图中的每个连通分量是否为一个完全图。完全图的特性是：任意两个顶点之间都存在边。因此，对于图中的每个连通分量，可以通过计算其顶点数和边数来判断是否为完全图。

众所周知，对于一个包含 $k$ 个顶点的完全图，应有 $\frac{k\times (k-1)}{2}$ 条边。这里可以通过并查集找出所有的连通分量，然后检查每个分量是否符合完全图的边数要求。

### C++ 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 150010;
using ll = long long;
int n, m, pa[N], sz[N];
ll ec[N]; 

int find(int x) {
    if (pa[x] != x) pa[x] = find(pa[x]);
    return pa[x];
}

void unite(int x, int y) {
    int rx = find(x);
    int ry = find(y);
    if (rx != ry) {
        pa[ry] = rx;
        sz[rx] += sz[ry];
        ec[rx] += ec[ry];
    }
    ec[rx]++;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        pa[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        unite(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        if (pa[i] == i) { 
            ll k = sz[i];
			ll exp = k * (k - 1) / 2;
            if (ec[i] != exp) {
                printf("NO");
                return 0;
            }
        }
    }
    printf("YES");
    return 0;
}
```

---

## 作者：Ryan_Adam (赞：0)

## CF771A Bear and Friendship Condition 题解
### 算法
并查集，图的基本性质
### 分析
题目意思是，一旦有一些点联通，那么这些点必须两两直接相连。换句话讲，就是图中的每个联通块都是**完全图**。

所谓完全图，就是图中的每个点都两两相连，假设一个完全图有 $n$ 个点，那么我们可以通过乘法原理算出这个完全图的边数为 $\frac{n\times(n-1)}{2}$。那么我们现在只需要用并查集统计一下联通块个数，顺便统计一下每个联通块的点数，算出来所有完全图的边数之和与 $m$ 比较即可。

注意要开 `long long`。
### 示例代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace Ryan
{
    const int N=150005;
    int n,m;
    int fa[N],sum[N],vis[N];
    int find(int x)
    {
        return (x==fa[x]?x:fa[x]=find(fa[x]));
    }
    void merge(int x,int y)
    {
        int ff=find(x);
        int fy=find(y);
        fa[ff]=fy;
        sum[fy]+=sum[ff];
        return;
    }
    signed work()
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            fa[i]=i,sum[i]=1;
        for(int i=1;i<=m;i++)
        {
            int x,y;
            cin>>x>>y;
            if(find(x)!=find(y))
                merge(x,y);
        }
        int k=0,ans=0;
        for(int i=1;i<=n;i++)
        {
            int x=find(i);
            if(vis[x])continue;
            vis[x]=1;
            k+=sum[x]*(sum[x]-1)/2;
            ans++;
        }
        if(k==m)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Ryan::work();
}
```

---

## 作者：Peaky (赞：0)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF771A)。
### 题目大意
简化一下问题。  
判断每一个连通块是否每两个点之间都有一条边相连。

### 思路
简化完问题就很容易做了。  
假设一个连通块有 $n$ 个点，每一个点都要和另外 $n-1$ 个点相连接，那么从这个点会引出 $n-1$ 条边，把每一个点都类比一下，就会发现一个连通块有 $n\times(n-1)$ 条边。  
考虑到每两个点之间只有一条边，所以每一次算边都会重复计算一次，所以边数还要再 $\div2$，算得每一个连通块总边数为 $\frac{n\times(n-1)}{2}$。

### 实现
本篇题解用 dfs 实现判断连通块点和边的个数，链式前向星存图。
### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=3e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int head[N],edge[N],last[N],idx,n,m;
int vis[N],ans,cnt;
void add(int u,int v){
	edge[++idx]=v;
	last[idx]=head[u];
	head[u]=idx;
}
void dfs(int x){
	cnt++;
	vis[x]=1;
	for(int i=head[x];i;i=last[i]){
		ans++;
		if(vis[edge[i]]) continue;
		dfs(edge[i]);
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]) cnt=0,ans=0,dfs(i);
		if(cnt&&cnt*(cnt-1)!=ans) return cout<<"NO",0;
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：YFF1 (赞：0)

## 题目分析：
通过题意，我们可以给出的图要满足一个人的朋友的朋友也得是自己的直接朋友。注意到题目范围并不大，因此直接暴力搜索即可，甚至不需要递归。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,x,y;
bool vis[200005],use[200005];
vector<int>g[200005];
bool find(int x){
	if(g[x].size()==0)return 1;
	memset(vis,0,sizeof(vis));
	for(int i:g[x])vis[i]=1;//标记自己的直接好友 
	for(int i:g[x]){
		for(int j:g[i]){//遍历自己好友的好友，即自己的间接好友 
			if(j==x)continue;//不要遍历到自己 
			if(vis[j]!=1)return 0;//不满足条件就 return 0 
		}
	}
	return 1;
}
signed main () {
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		if(find(i)==0){
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：liluhexuan (赞：0)

首先，简单画一下图就会发现：只有这个图的所有子图都是完全图时这个图才符合要求。那我们只需要找到所有子图，记下他的边数 $a$ 和点数 $b$。如果 $a=b\times (b-1) \div 2$（$b\times (b-1) \div 2$ 是这个子图应有的边数）那么说明这个子图符合条件；如果不符合条件，就输出 `NO`。

```cpp
#include<iostream>
#include<vector>
using namespace std;
#define int long long
const int N=2e5+10;
vector<int>g[N];
int a[N],sum,cnt=0;
int color[N],point[N];
bool vis[N];
void dfs(int u){
	vis[u]=1,sum++;
	for(int i=0;i<g[u].size();i++){
		cnt++;
		int v=g[u][i];
		if(vis[v]) continue;
		dfs(v);
	}
}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		sum=0,cnt=0;
		dfs(i);
		cnt/=2;
		if(sum*(sum-1)/2!=cnt){
			cout<<"NO\n";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}

```

---

## 作者：1234567890sjx (赞：0)

用并查集求出所有的连通块，然后判断每一个连通块是否都是完全图即可。

如果某一个连通块不是完全图，那么必然不满足条件。

时间复杂度 $O(\alpha n)$。

核心代码：

```cpp
   for (int i = 1; i <= m; i++) {
		int &u = ed[i].u, &v = ed[i].v;
		sz[find(u)]++;
	}
	for (int i = 1; i <= n; i++) {
		nd[find(i)]++;
	}
	bool ok = true;
	for (int i = 1; i <= n; i++) {
		if (!vis[find(i)]) {
			vis[find(i)] = true;
			int f1 = sz[find(i)], f2 = nd[find(i)] * (nd[find(i)] - 1) / 2;
			if (f1 != f2) {
				ok = false;
				break;
			}
		}
	}
```

其中 `ed[i]` 表示第 $i$ 条边，`find(i)` 表示并查集中 $i$ 点的祖先。

---

## 作者：SuperCowHorse (赞：0)

给一种 **暴力** 但能通过的方法。

先建图，输入 $u,v$ 时用并查集把它俩 $\operatorname {merge}$ 起来，然后，枚举每个集合里所有的元素，一旦有没有连边的直接结束程序即可。

如何判断有没有连边呢？这里使用了`map`。也是在输入时维护信息。

详见代码。
``` cpp
#include<bits/stdc++.h>
#define ll long long
#define do double
using namespace std;
const int maxn=1.5e5+5;
int n,m;
map<pair<int,int>,bool>p;//判断边是否存在
vector<int>k[maxn];int cnt;//记录集合元素
map<int,int>t;//记录集合编号
struct dsu{//并查集模板，按秩合并+路径压缩
	int f[maxn],g[maxn];
	inline void init(){
		for(int i=1;i<=n;++i)
			f[i]=i,g[i]=1;
	}
	int find(int x){return f[x]==x?f[x]:f[x]=find(f[x]);}
	inline bool merge(int x,int y){
		int u=find(x);
		int v=find(y);
		if(u==v) return 0;
		if(g[u]>g[v]) swap(u,v);
		f[u]=f[v];g[v]+=g[u];
		return 1;
	}
	inline bool check(int x,int y){return find(x)==find(y);}
}d;
inline bool o(){//枚举集合元素并判断
	for(int i=1;i<=n;++i){//先把每个集合的元素都归类
		if(!t[find(i)]){//没有就新建集合
			k[++cnt].push_back(0);
			k[cnt].push_back(i);
			t[find(i)]=cnt;
		}
		else k[t[find(i)]].push_back(i);//有了就压入
	}
	for(int i=1;i<=cnt;++i){//枚举有没有连边
		int siz=k[i].size()-1;
		for(int j=1;j<=siz;++j)
			for(int l=j+1;l<=siz;++l){
			int u=k[i][j];
			int v=k[i][l];
			if(!p[make_pair(u,v)])
				return 0;//没有连边，不符题意，return 0
		}
	}
	return 1;//符合题意
}
signed main(){
	scanf("%d%d",&n,&m);
	d.init();
	for(int i=1,u,v;i<=m;++i){
		scanf("%d%d",&u,&v);
		d.merge(u,v);//合并集合
		p[make_pair(u,v)]=p[make_pair(v,u)]=1;//记录连边
	}
	printf(o()?"YES":"NO");//判断
	return 0;
}
```

---

## 作者：hanzhang666 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF771A)
# 前置知识
完全图性质：设 $n$ 为完全图点数，$m$ 为完全图边数，有   $m=n\times(n-1)/2$。
# 分析
题目要求 $A$ 与 $B$ 之间有边，$B$ 与 $C$ 之间有边，那么 $A$ 与 $C$ 之间也需要有边，由此我们可以想到完全图。


注意：图可以不连通，所以判断每个**连通块**是否为完全图即可。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200000
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int nedge,Next[N*2],head[N],to[N*2];
void add(int a,int b){//加边 
	Next[++nedge]=head[a];
	head[a]=nedge;
	to[nedge]=b;
}
int vis[N];
int cnt,cnt1;//cnt表示每个连通块中点的个数，cnt1表示 每个连通块中边的个数
void bfs(int now){
	cnt1++;//点++ 
	vis[now]=1;//记忆化搜索 
	for(int i=head[now];i;i=Next[i]){
		cnt++;//边++ 
		if(!vis[to[i]]) bfs(to[i]);
	}
	return;
}
signed main(){
	int n=read(),m=read();
	for(int z=1;z<=m;z++){
		int u=read(),v=read();
		add(u,v);
		add(v,u);//无向图 
	}
	for(int z=1;z<=n;z++){
		cnt=0;
		cnt1=0;
		if(!vis[z]) bfs(z);
		cnt/=2;//无向图，每边存两次，所以要除以2 
		if(cnt!=cnt1*(cnt1-1)/2){//不是完全图 
			puts("NO");
			return 0;
		}
	}
	puts("YES");
}
```


---

## 作者：wangml (赞：0)

### 思路
> 按照题意，所求的图需要是一个完全图。此时输出yes,否则输出no

### AC代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=15e4+5;
int n,m,fa[maxn];
long long size_v[maxn];
long long size_e[maxn];
int u[maxn],v[maxn];

bool is_digit(char c){return '0'<=c && c<='9';}
int scan()
{
    int x=0;
    char c=0;    //快速读入
    bool flag=false;
    while(!is_digit(c)) {flag|=c=='-',c=getchar();};
    while(is_digit(c)) {x=(x<<3)+(x<<1)+(c^48),c=getchar();};
    return flag?-x:x;
}

int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
void unionset(int x,int y)
{
    int fx=find(x),fy=find(y);
    if(fx!=fy) fa[fx]=fy;
}

int main()
{
    n=scan(); m=scan();
    for(int i=1;i<=n;i++) fa[i]=i;
    memset(size_v,0,sizeof(size_v));  //初始化
    memset(size_e,0,sizeof(size_e));
    for(int i=1;i<=m;i++)
    {
        u[i]=scan();
        v[i]=scan();      //输入
        unionset(u[i],v[i]);
    }
    
    for(int i=1;i<=m;i++) size_e[find(u[i])]++;		//记录图中边数
    for(int i=1;i<=n;i++) size_v[find(i)]++;   		//记录图中点数
    for(int i=1;i<=n;i++)
    if(find(i)==i)  //如果i为根节点
    {
        long long sv=size_v[i];
        long long se=size_e[i];
        if((long long)sv*(sv-1)>>1!=se) 
        {         						//验证点与边的关系是否符合要求
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}
```

---

