# Village (Maximum)

## 题目描述

### 题意

[最小值版本](https://www.luogu.com.cn/problem/CF1387B1)

村里 $n$ 个房子构成了一个 $n$ 点 $n-1$ 条边的**树**结构（下标从 $1$ 开始），每条边长度均为 $1$。一开始每个房子里分别有一个村民。

现在所有村民都需要搬家（改变自己所在的点），搬家后依然需要满足每个房子里**有且只有一个**村民。也就是说，如果原本位于点 $i$ 的村民搬到了点 $v_i$，那么应当满足：

- 对于任意点 $i$，有 $i \neq v_i$。

- 对于任意两个不同的点 $i$ 与 $j$，有 $v_i \neq v_j$。

村民 $i$ 搬家的花费是点 $i$ 到点 $v_i$ 的树上距离（即树上二点间相隔的边数），总花费为所有村民花费之和。求总花费的**最大值**及其方案。

## 说明/提示

- $2 \leq n \leq 10^5$

- $1 \leq a,b \leq n$

## 样例 #1

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
8
4 3 2 1```

## 样例 #2

### 输入

```
7
4 2
5 7
3 4
6 3
1 3
4 5```

### 输出

```
18
2 7 4 1 3 5 6```

# 题解

## 作者：duyi (赞：18)

## 题解 CF1387B2 Village (Maximum)

我们考虑每条边对答案的贡献，也就是它被经过了几次。设这条边两个端点分别为$a,b$，则它被经过的次数，最大为$2\cdot \min(\text{size}(a),\text{size}(b))$，其中$\text{size}$表示子树大小。把所有边的最大经过次数加起来，就是答案的理论最大值（上界）。

现在的问题是，如何构造一种方案，使答案达到这个理论最大值。

考虑找到一个节点，满足：它的所有子树，大小都不超过$\lfloor\frac{n}{2}\rfloor$。这样的节点我们称为重心，一棵树有且仅有不超过两个重心，我们只需要找到任意一个即可。找重心的过程，时间复杂度是$O(n)$的。

假设重心有若干个儿子，这样把树划分为了若干个子树。我们把每个节点按照它所在的“子树”分类。容易发现，只要我们匹配的任意两个节点都不在同一个子树内（也就是路径必须经过重心），答案就一定能取到理论最大值。因为每条边较小的那侧（当以重心为根时，就是它的下方那一侧），所有节点的路径都会经过它。

并且，由于每棵子树大小都不超过$\lfloor\frac{n}{2}\rfloor$，我们一定能找到一种两两匹配的方案，使得任意一对匹配点都不在同一个子树内。这是一个经典问题。我提供两种做法：

- 做法一。可以贪心。用一个大根堆，维护所有子树，以子树内还未被匹配的节点数量为关键字。每次弹出最大的两棵子树，从中各取一个节点，配成一对。
- 做法二。把所有节点排成一排，同一子树内的节点放在一起。然后把这个序列的第$i$项和第$i+\lfloor\frac{n}{2}\rfloor$ ($1\leq i\leq \lfloor\frac{n}{2}\rfloor$)项匹配即可。因为没有一棵子树大小大于$\lfloor\frac{n}{2}\rfloor$，所以每对匹配的节点一定来自不同的子树。

两种做法，时间复杂度分别为$O(n\log n)$和$O(n)$，均可以通过本题。

参考代码（做法二）：

```cpp
//problem:CF1387B2
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T& x,T y){x=(y<x?y:x);}

const int MAXN=1e5;
int n;
ll ans;
int dest[MAXN+5];

struct EDGE{int nxt,to;}edge[MAXN*2+5];
int head[MAXN+5],tot;
inline void add_edge(int u,int v){edge[++tot].nxt=head[u],edge[tot].to=v,head[u]=tot;}

int sz[MAXN+5],f[MAXN+5],root;
void dfs1(int u,int fa){
	sz[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa) continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		ckmax(f[u],sz[v]);
	}
	ckmax(f[u],n-sz[u]);
	if(!root || f[u]<f[root]){
		root=u;
	}
}
int arr[MAXN+5],cnt_arr;
int dep[MAXN+5];
void dfs2(int u,int fa){
	arr[++cnt_arr]=u;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa) continue;
		dep[v]=dep[u]+1;
		dfs2(v,u);
	}
}
int main() {
	cin>>n;
	for(int i=1;i<n;++i){
		int u,v; cin>>u>>v;
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(root,0);
	for(int i=1;i<=n/2;++i){
		int u=arr[i],v=arr[i+n/2];
		ans+=(dep[u]+dep[v])*2;
		dest[u]=v;
		dest[v]=u;
	}
	if(n%2==1){
		int u=arr[n];
		int v=arr[1];
		int w=arr[1+n/2];
		ans+=dep[u]*2;
		dest[u]=v;
		dest[v]=w;
		dest[w]=u;
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;++i)
		cout<<dest[i]<<" \n"[i==n];
	return 0;
}
```









---

## 作者：U____ (赞：10)

# CF1387B2 Village (Maximum) 题解

## 题目简述
有一棵 $n$ 个节点的树，记 $dis(a, b)$ 为节点 $a$ 到节点 $b$ 所经过的边数。要求我们求出一个序列   $a_{1},a_{2},a_{3}\ldots,a_{n}$，使得 $\sum _ {i = 1} ^ ndis(a_{i}, i)$ 最大。

## 讲解
![](https://cdn.luogu.com.cn/upload/image_hosting/jad4vlcm.png)

我们先想一下，上图节点 $1$ 到节点 $5$ 的这条边被村民经过的次数最多是多少？

显而易见，这条边上面的 $4$ 个节点的村民要去下面，然后下面便会有 $4$ 个节点的村民上来，所以这条边被经过最多次数为 $8$ 。

所以，一条端点为 $a$ 和 $b$ 的边被经过的最多次数为 $2 \times\min(s_{a},s_{b})$，$s_{a}$ 表示其子树的大小。

然后，我们再了解一下树的重心。

它的定义是在一棵树中，如果我们选择某个结点为根，可以使得它的所有子树中最大的子树最小，那么这个结点就被称作这棵树的重心。

重心的一个性质是以重心为树根时，所有子树的大小不超过全树大小的一半，求重心代码如下。

```cpp
void dfs(int x,int fa) {
	int mx = 0; 
	siz[x] = 1;
	for(int i : G[x]) {
		if (i == fa) continue;
		dfs(i, x);
		siz[x] += siz[i];
		mx = max(mx, siz[i]); 
	}
	mx = max(mx, n - siz[x]);
	if (mx <= n/2) rt = x;
}
```

考虑使所有边经过次数最多，我们可以找到这棵树的一个重心，再以这个重心为根，划分成不同的子树。根据重心的性质，每次在两个不同子树中匹配两个节点计算距离，累加便可以得到答案。

但是，我们会发现一个问题，当这颗树有奇数个节点时，所有节点都两两匹配后，会使最后一个节点的村民的无处可走。那么怎么办呢？

我们可以在匹配时，将剩下的最后三个节点进行匹配，即 $a$ 去 $b$，$b$ 去 $c$，$c$ 去 $a$，可以使答案最大。

## 代码

```cpp
//代码与 duyi 大佬写的基本一样，自己加了一些注释。 
#include<bits/stdc++.h>
using namespace std;
const int M = 1e5 + 5;
int n;
struct tree {
	int to, ext;
}edge[M*2];
int head[M], tot;
void add(int u, int v) {
	edge[++tot].to = v;
	edge[tot].ext = head[u];
	head[u] = tot;
}
int siz[M], f[M], root;//找重心模板 
void find(int rt, int fa) {
	siz[rt] = 1;
	for(int i = head[rt]; i; i = edge[i].ext) {
		int to = edge[i].to;
		if(to==fa) continue;
			find(to, rt);
			siz[rt] += siz[to];
			f[rt] = max(f[rt], siz[to]);
	}
	f[rt] = max(f[rt], n - siz[rt]);
	if(f[rt] < f[root] || root == 0) {
		root = rt;//找到一个重心即可 
	}
}
int dep[M], vis[M], cnt;
void dfs(int rt, int fa) {
	vis[++cnt] = rt;//用 vis记录经过的节点 
//因为是深度优先，所以同一子树的节点都是在一起的 
//然后根据重心的性质，vis[i] 和 vis[i+n/2] 一定是两个不同子树的节点 
	for(int i = head[rt]; i; i = edge[i].ext) {
		int to = edge[i].to;
		if(to == fa) continue;
		dep[to] = dep[rt] + 1;//向下遍历求深度 
		dfs(to, rt);
	}
}

int cage[M];
int main() {
	int u, v;
	cin>>n;
	for(int i = 1; i < n; i ++) {
		cin>>u>>v;
		add(u, v);
		add(v, u);
	}
	
	find(1, 0);//先找到重心root 
	dfs(root, 0);//再以重心为根，求所有节点的深度 
	
	long long ans = 0;
	for(int i = 1; i <= n/2; i ++) {
		int u = vis[i], v = vis[i + n/2];
		ans += (dep[u] + dep[v]) * 2;
		cage[u] = v;//v节点的村民去 u 
		cage[v] = u;//u节点的村民去 v 
	}
	if(n%2==1) {
		int u =vis[n], v = vis[1], w = vis[1 + n/2];
		ans += dep[u] * 2;
		//如果是奇数，让剩下的三个节点互换
		// 1 去 2， 2 去 3，3 去 1   
		cage[u] = v;
		cage[v] = w;
		cage[w] = u;
	}
	cout<<ans<<endl;
	for(int i = 1; i <= n; i ++) cout<<cage[i]<<" ";
	cout<<endl;
	return 0;
} 
```


---

## 作者：zhlzt (赞：0)

### 题解

来一波双倍经验：[[ABC362F] Perfect Matching on a Tree](https://www.luogu.com.cn/problem/AT_abc362_f)。

首先考虑答案何时取到上界。对于一条边，设其两个结点为 $u$ 和 $v$，易知 $u$ 和 $v$ 所在的两部分会有同样的村民经过这条边搬家至另一部分，即最多有 $2\times \min\left\{\text{size}(u),\text{size}(v)\right\}$ 个村民搬家时经过这条边。其中 $\text{size}(u)$ 表示结点 $u$ 所在部分的结点数量。

钦定树上的任意一个节点为根，遍历他的所有子树，尝试取到上述的答案上界。若对于每一棵子树，都有该子树内的村民均搬家到根节点或另一棵子树中，那么显然答案是取到上界的。因为对于该子树的每一条边，以及该子树的根节点连向给定树的根节点的那条边，其下边所有结点上的村民搬家时必定经过了这条边。此时我们只需保证每个子树的大小均 $\le \left\lfloor\dfrac{n}{2}\right\rfloor$ 即可使每棵子树内的村民均可搬家到根节点或另一棵子树中。

我们发现只有树的重心满足以其为根时每个子树的大小 $\le \left\lfloor\dfrac{n}{2}\right\rfloor$，因此我们从树的重心开始遍历给定树，将所有结点按 dfn 序排序后第 $i$ 个结点上的村民搬家至第 $\left(i+\left\lfloor\dfrac{n}{2}\right\rfloor-1\right)\bmod n +1$ 个结点即可保证所有村民均搬家到根节点或另一棵子树中。

找出树的重心并遍历给定树，时间复杂度为 $O(n)$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
int siz[maxn],son[maxn];
int ans[maxn],cnt=0;
int ver[maxn]; ll sum=0;
vector<int>edge[maxn];
void dfs(int u,int dad,int n){
	siz[u]=1; son[u]=0;
	for(int v:edge[u]){
		if(v==dad) continue;
		dfs(v,u,n); siz[u]+=siz[v];
		son[u]=max(son[u],siz[v]);
		sum+=2*min(siz[v],n-siz[v]);
	}
}
void solve(int u,int dad){
	ans[++cnt]=u;
	for(int v:edge[u]){
		if(v==dad) continue;
		solve(v,u);
	}
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0,n); int pos=0;
	for(int i=1;i<=n;i++){
		if(max(son[i],n-siz[i])<=n/2) pos=i;
	}
	solve(pos,0);
	printf("%lld\n",sum);
	for(int i=1;i<=n;i++){
		ver[ans[i]]=ans[(i+n/2-1)%n+1];
	}
	for(int i=1;i<=n;i++) printf("%d ",ver[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：roger_yrj (赞：0)

我们可以把移动理解为交换。问题转化为选 $\lfloor \frac{n}{2}\rfloor$ 对点进行交换。

我们希望每一对点的路径尽可能的经过根节点，我们考虑构造。

我们发现树的重心有个很好的性质：每个子树大小不会超过 $\lfloor \frac{n}{2}\rfloor$。通过这个性质，考虑以下构造：

以重心为根，求出每个点的 dfn，每次将 dfn 为 $i$ 的点与 dfn 为 $i+\lfloor \frac{n}{2}\rfloor$ 的点配对。容易证明这一对点不会在同一个子树内。

如果 $n$ 为奇数，那么将 dfn 为 $1,2,2+\lfloor \frac{n}{2}\rfloor$ 的三个点特殊处理一下就行。

答案为 $2\sum\limits_{i=1}^ndep_i$。

```cpp
void getrt(int u,int fa){
	siz[u]=1;
	for(int i=fst[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
		getrt(v,u);
		siz[u]+=siz[v];
		maxx[u]=max(maxx[u],siz[v]);
	}
	maxx[u]=max(maxx[u],n-siz[u]);
	if(!rt||maxx[u]<maxx[rt])rt=u;
}
void dfs(int u,int fa){
	vis[++tcnt]=u;
	for(int i=fst[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa)continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
}
void solve(){
	maxx[0]=1145141919;
	cin>>n; 
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		adde(u,v);
		adde(v,u);
	}
	getrt(1,0);
	dfs(rt,0);
	ll ans=0;
	for(int i=1;i<=n;i++)ans+=dep[i]*2;
	cout<<ans<<"\n";
	if(n&1){
		b[vis[1]]=vis[2],b[vis[2]]=vis[2+n/2],b[vis[2+n/2]]=vis[1];
		for(int i=3;i-1<=n/2;i++){
			b[vis[i]]=vis[i+n/2];
			b[vis[i+n/2]]=vis[i];
		}
	}else{
		for(int i=1;i<=n/2;i++){
			b[vis[i]]=vis[i+n/2];
			b[vis[i+n/2]]=vis[i];
		}
	}
	for(int i=1;i<=n;i++)cout<<b[i]<<" ";
}
```

三倍经验：
AT_abc362_f、CF700B。

---

