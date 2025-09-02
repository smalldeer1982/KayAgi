# [ARC103F] Distance Sums

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc103/tasks/arc103_d

長さ $ N $ の数列 $ D_1,\ D_2,\ ...,\ D_N $ が与えられます。 **$ D_i $ の値はすべて異なります**。 以下の条件を満たす $ N $ 頂点の木は存在するでしょうか？

- 各頂点には $ 1,2,...,\ N $ の番号が付けられている
- 各辺には $ 1,2,...,\ N-1 $ の番号が付けられていて、$ i $ 番目の辺は頂点 $ u_i $ と $ v_i $ をつないでいる
- 各頂点 $ i $ に対して、$ i $ から他の頂点までの距離の和は $ D_i $ である。ただし、各辺の長さは $ 1 $ であるものとする。

条件を満たす木が存在する場合、$ 1 $ つ構築してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100000 $
- $ 1\ \leq\ D_i\ \leq\ 10^{12} $
- $ D_i $ はすべて異なる

### Sample Explanation 1

次のような木が条件を満たします。 !\[\](https://img.atcoder.jp/arc103/92920696862ead4cacf3755c3c8135e0.png)

## 样例 #1

### 输入

```
7
10
15
13
18
11
14
19```

### 输出

```
1 2
1 3
1 5
3 4
5 6
6 7```

## 样例 #2

### 输入

```
2
1
2```

### 输出

```
-1```

## 样例 #3

### 输入

```
15
57
62
47
45
42
74
90
75
54
50
66
63
77
87
51```

### 输出

```
1 10
1 11
2 8
2 15
3 5
3 9
4 5
4 10
5 15
6 12
6 14
7 13
9 12
11 13```

# 题解

## 作者：chen_zhe (赞：15)

# [ARC103D] Distance Sums

月考之余做做构造题玩玩。

之前的翻译是不准确的，我顺便改了改。题目中要求 $D_i$ 与节点 $i$ 是一一对应的。

首先我们很自然地考虑对于一棵树上相邻的两个节点 $u,v$，其 $D_u$ 和 $D_v$ 的变化规律。我们可以把一棵树抽象成这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/9smcjkiw.png)

这样我们可以发现，如果从 $u$ 变化到 $v$，那么相当于 $u$ 左边的点（在图中为 $1,2,3,4,u$）对 $D_v$ 的贡献比 $D_u$ 多 $1$，也就是做出了一个等于 $size[u]$ 的贡献。而在 $v$ 右边的点（在图中为 $5,6,7,8,v$）对 $D_v$ 的贡献比 $D_u$ 少 $1$，也就是做出了一个等于 $-size[v]$ 的贡献。

因此，我们可以发现，$\Delta D=size[u]-size[v]=size[u]-(n-size[u])=2\times size[u]-n$，即 $D_v=2\times size[u]-n+D_u$。

一下子感觉卵用没有。我们会发现，$D_i$ 最小的值，应当是树的重心，而最大的值必定是某个叶子节点。证明略。

那么我们显然就可以从树的叶子节点开始构造。首先把 $D_i$ 排序，找到必定是叶子节点的那个节点，根据上面的 $\Delta D$ 的计算式，找到属于父节点的 $D_i$，然后连接过去即可。在这个期间，如果我们找不到符合的 $D_i$，那么就说明无解了。

但是我们发现一点，就是我们算出的是 $\Delta D$，不一定是真正的距离。我的想法比较粗暴，就是直接根据重心跑一遍 $D_i$ 看看是否相等。时间复杂度其实是 $O(n \log n)$ 的。注意几个 `long long` 的问题。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

pair <long long,int> D[100050];

pair <int,int> edge[100050];

vector <int> G[100050];

int n,size[100050],tot;

long long dis[100050];

inline void dfs(int u,int fa)
{
	for (int i=0;i<G[u].size();i++)
	{
		int v=G[u][i];
		if (v!=fa)
		{
			dis[v]=dis[u]+1;
			dfs(v,u);
		}
	}
}

int main()
{
	n=read();
	for (int i=1;i<=n;i++)
	{
		long long d=read();
		D[i]={d,i};
		size[i]=1;
	}
	sort(D+1,D+n+1);
	reverse(D+1,D+n+1);
	for (int i=1;i<n;i++)
	{
		long long delta=D[i].first-n+2*size[i];
		int l=1,r=n+1,pos=0; 
		while (l<=r)
		{
			int mid=(l+r)>>1;
			if (D[mid].first<=delta)
			{
				r=mid-1;
				pos=mid;
			}
			else
				l=mid+1;
		}
		//cout << D[pos].first << " " << delta << endl;
		if (D[pos].first!=delta)
		{
			puts("-1");
			return 0;
		}
		int u=D[i].second,v=D[pos].second;
		G[u].push_back(v);
		G[v].push_back(u);
		edge[++tot]={u,v};
		size[pos]+=size[i];
	}	
	dfs(D[n].second,0);
	long long sum=0;
	for (int i=1;i<=n;i++)
		sum+=dis[i];
	if (sum==D[n].first)
	{
		for (int i=1;i<=tot;i++)
			cout << edge[i].first << " " << edge[i].second << endl;
	}
	else
		puts("-1");
	return 0;
}

```

---

## 作者：CYJian (赞：10)

~~md 这题 p 事真多~~

一开始 WA 的一发，是因为我标号瞎给了，没注意这题还强制要你标号也对上 $D_i$。

---

这题一看上去没啥思路的话，就先找些特殊的东西吧：

$D_i$ 最大是啥？肯定是个叶子节点嘛。

$D_i$ 最小是啥？肯定是这棵树的重心嘛。

然后，我们再联想一些东西，~~比如，这题如果不定标号， SPJ 怎么写？（当时不知道定了标号还真是从这方面想想出来的）~~ 比如，怎么算一棵树的每个点到其他所有点的距离和？

$N^2$ 的东西太没技术含量了，而且对这个题的启发意义不大。有没有 $O(N)$ 的做法呢？

我们假设以某个节点为根，先求出根的 $D_x$ 以及每个点的子树大小 $sz_x$。

然后考虑，如果知道一个点的 $D_x$，要计算它相连的一个节点的 $D_u$。不难发现有这样一个式子成立：

$$D_u = D_x - sz_{u} + (N-sz_u) $$

大概的意思是，你考虑「集合点」从 $x$ 放到了 $u$ 上之后，对于 $u$ 子树里头的点，都会少走一步；而对于不是 $u$ 子树里面的点，都会多走一步。

然后考虑这个东西和这个题的关联：

我们假设以重心为根节点，不难发现，在同一条链上的点，离重心越远，$D_i$ 就越大。

我们现在知道一个叶子节点的 $D_x$，也知道了它的子树大小为 $1$。这样我们就能反推其父节点的 $D_f$。

知道了 $x$ 的父亲节点 $f$。然后我们再找 $D_i$ 次大的点，这时候它的子树大小也一定知道了，也就能反推出它的父节点是啥。

这样一直反推上去就能建出一棵树。当然，如果中间的某一次反推中，找不到 $D_i$ 了，那么就说明这样的树不存在。

但是，这样反推出来的树，可能也不一定对。因为我们考虑我们反推的本质：用 $n-1$ 条边建立关于 $n$ 个变量的方程。我们固然能确定每对变量之间的关系，但是并不能确切的解出每个变量是不是等于这个值。

换句话说，我们只求出来 $D_i-D_j$ 都是满足于这棵树的，但是不知道 $D_i$ 是不是真的就是距离和。

要检查是不是满足也很简单，只需要确定一个 $D_i$ 是满足的，剩下的 $D_i$ 也就都满足了。

建出树后，要求一个 $D_x$ 很简单，DFS 一遍之后随便就求出来了。当然，我们用反推的时候求出来的 $sz_x$，将这些 $sz_x$ 加起来，求出重心的 $D_x$ 也是可行的。

$\rm Code$：

```cpp
const int MAXN = 100010;

struct Node {
	ll d; int id;
	
	Node() {}
	Node(ll d, int x):d(d), id(x) {}

	friend bool operator < (Node a, Node b) { return a.d < b.d; }
}d[MAXN];

int sz[MAXN];
int u[MAXN];
int v[MAXN];

int main() {
	int n = ri;
	for(int i = 1; i <= n; i++) d[i] = Node(rl, i), sz[i] = 1;
	sort(d + 1, d + 1 + n);
	ll dis = 0, N = 0;
	for(int i = n; i > 1; i--) {
		ll D = d[i].d - n + (sz[i] << 1);
		int p = lower_bound(d + 1, d + 1 + n, Node(D, 0)) - d;
		if(d[p].d != D) return puts("-1"), 0;
		++N;
		u[N] = d[i].id;
		v[N] = d[p].id;
		sz[p] += sz[i];
		dis += sz[i];
	}
	if(dis != d[1].d) puts("-1");
	else
		for(int i = 1; i <= N; i++)
			printf("%d %d\n", u[i], v[i]);
	return 0;
}
```

---

## 作者：Kubic (赞：5)

这个题好像并没有其他几位神仙说的那么难吧。。。

首先考虑这道题的 SPJ 怎么写：

先求出根节点的 $D$ 值与每个点子树的大小 $size_u$，然后对于每一对 $u$ 和 $f$（$f$ 为 $u$ 的父亲）做如下转移：

$$D_u=D_f-2size_u+n$$

解释：当这个点从 $f$ 走到 $u$ 时，$u$ 子树内的每一个点的贡献会减少 $1$，$u$ 子树外的每一个点的贡献会增加 $1$，所以总的贡献先减少 $size_u$ 再增加 $n-size_u$。

改变一下这个柿子：

$$D_f=D_u+2size_u-n$$

那么很容易发现每一条从叶子到根的链上 $D$ 值是一个下凸函数。所以我们用 $D$ 值最小的点作为根，这样每一条从叶子到根的链上 $D$ 值单调递减。

~~做到这里，我没看到 $D$ 值互不相等，卡了我一年~~

如果您是会存在 $D$ 值相等的做法的神仙，并且愿意的话，请在评论或者私信里教一下这位蒟蒻/kel。

回到正题：$D$ 值互不相等。

首先，$D$ 值最大的节点一定是叶子。

其次，对于每一个 $size_u$ 确定的 $u$，我们就可以直接得到它的父亲的编号。

那么我们按 $D$ 值从大到小遍历这些点。显然在 $u$ 之后遍历到的 $v$ 一定不会是 $u$ 的儿子。所以在遍历到 $u$ 时它所有的儿子都已经计算完毕了，$size_u$ 已经确定下来。于是就能直接得到 $u$ 的父亲 $f$，并把 $size_u$ 加入 $size_f$。

此时我们只需要检验根节点的 $D$ 值是否正确即可，随便怎么做都行。

上代码（自认为十分简洁）：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define ll long long
int n,sz[N],fa[N],dep[N];ll dst,a[N];map<ll,int> rv;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i]),rv[a[i]]=i,sz[i]=1;sort(a+1,a+n+1);
	for(int i=n,u,f;i>1;--i)
	{
		u=rv[a[i]];f=rv[a[i]+sz[u]*2-n];fa[u]=f;sz[f]+=sz[u];
		if(!f || fa[f]) {puts("-1");return 0;}
	}for(int i=2,u;i<=n;++i) u=rv[a[i]],dep[u]=dep[fa[u]]+1,dst+=dep[u]; 
	if(dst!=a[1]) {puts("-1");return 0;}
	for(int i=2,u;i<=n;++i) u=rv[a[i]],printf("%d %d\n",u,fa[u]);
	return 0;
}
```

---

## 作者：SpeMars (赞：2)

这道题要求我们构造一棵树，定义 $D_i$ 为所有点到 $i$ 的距离之和，

树上所有边权为 $1$ ，给出所有 $D_i$ 然后构造出符合条件的树，或判断无解。

既然是构造题，我们不妨找一下性质，如果我们令这棵树是无根树会发现，

$D_i$ 最大的 $i$ 一定是某个叶子结点显然可以证明(也可以~~性感~~感性理解一下)。

那么我们考虑一下两个相邻节点的贡献

![](https://cdn.luogu.com.cn/upload/image_hosting/co2vvujj.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

$D_v$ 如何转移到 $D_u$ 呢？

我们不妨定义 $sz_i$ 为 $i$ 子树的大小，那么从 $D_v$ 更新到 $D_u$ 时

所有 $v$ 的子树中的点都会多走一条边，那么贡献就是 $sz_v$ ，

有得必有失，所有原来 $v$ 子树外的点都得少走一条边，所以贡献为 $-(n-sz_v)$

综合得： $ D_u=D_v+ 2 \times sz_v -n $ ,也就是说两个相邻的节点满足此性质。

那么我们考虑从叶子节点构造，每次找有没有符合条件的 $D_u$ ，如果找不到了，直接无解。

转移的时候记得更新一下子树 $sz$ 即可，

由于我们用的是两个点 $D$ 的值的变化量构造的，所以最后我们再跑一个树形DP check 一下答案是否可行。

tips: 这题要求编号也要对应……

# code:

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=1e6+10;
int n,dis[N],f[N],d[N],sz[N],tmp,p,tot;
vector<int> g[N];
struct laq{
	int v,id;
	bool operator >(laq tmp) const{
		return v>tmp.v;
	}
	bool operator ==(laq tmp) const{
		return v==tmp.v;
	}
	bool operator <(laq tmp) const{
		return v<tmp.v;
	}
}s[N],e[N];
void dfs_d(int u,int fa){
	sz[u]=1;
	for(int i=0;i<g[u].size();++i){
		int v=g[u][i];
		if(v==fa)continue;
		dfs_d(v,u);
		sz[u]+=sz[v];
		d[u]+=(d[v]+sz[v]);
	}
	return;
}
void dfs_f(int u,int fa){
	for(int i=0;i<g[u].size();++i){
		int v=g[u][i];
		if(v==fa)continue;
		f[v]=(f[u]+d[u]-(d[v]+sz[v])+(n-sz[v]));
		dfs_f(v,u);
	}
	return;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld",dis+i);
		s[i]=(laq){dis[i],i};
		sz[i]=1;
	}
	sort(s+1,s+n+1);
	for(int i=n;i>1;--i){
		tmp=(s[i].v+sz[s[i].id]+sz[s[i].id]-n);
		p=lower_bound(s+1,s+n+1,(laq){tmp,756})-s;
		if(s[p].v!=tmp){
			puts("-1");
			return (0^0);
		}
		e[++tot]=(laq){s[i].id,s[p].id};
		g[s[i].id].push_back(s[p].id);
		g[s[p].id].push_back(s[i].id);
		sz[s[p].id]+=sz[s[i].id];
	}
	memset(sz,0,sizeof(sz));
	dfs_d(1,0),dfs_f(1,0);
	for(int i=1;i<=n;++i){
		if(f[i]+d[i]!=dis[i]){
			puts("-1");
			return (0^0);
		}
	}
	for(int i=1;i<=tot;++i)printf("%lld %lld\n",e[i].id,e[i].v);
	return (0^0);
}
```

---

## 作者：1234567s (赞：1)

给定每个点到其他点的距离和，构造一棵树。  
对于距离，最基础的求法应该是换根DP，可以写出基本递推式。  
$$  
f_u=f_{fa}+(n-sz_u)-sz_u
$$  
这样就可以通过与父亲值的关系推导出 $sz$。  
此时不妨考虑一条链， $sz_u=\frac{n-f_u+f_{fa}}{2}$，那么此时从上到下由于 $sz$ 递减，所以 $f_u-f_{fa}$ 是递增的，但其实此时并没啥用，因为根节点并不满足这个性质。  
为了得到诸如链上权值递增的结论，我们可以钦定 $f$ 值最小的点（重心）为根，那么 $f$ 就是递增的了。  
如此子树内点的权值都较大，排序后从低向上构造，当构造到点 $i$ 时，他的子树被唯一确定，且由于 $f$ 互不相等，他唯一对应一个父亲，即可构造。   
最后要判一下无解，如果上述构造成立，链上关系确定，要么合法要么都不合法，所以判断根 $f$ 值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
#define int long long
namespace lzz
{
	int n,fa[N],dis[N],size[N];
	struct kkk{int u,v;}t[N];
	struct node
	{
		int val,id;
		bool operator<(const node &b)const
		{
			return val<b.val;
		}
	}a[N];
	int main()
	{
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i].val),a[i].id=i; sort(a+1,a+n+1);
		for(int i=n;i>=2;i--)
		{
			size[a[i].id]++;
			int to=a[i].val+2*size[a[i].id]-n,x=lower_bound(a+1,a+n+1,node({to,0}))-a;
			if(a[x].val!=to||x>=i)return printf("-1\n"),0; size[a[x].id]+=size[a[i].id],t[i]={a[x].id,a[i].id};
		}int all=0; for(int i=2;i<=n;i++)dis[t[i].v]=dis[t[i].u]+1,all+=dis[t[i].v];
		if(all!=a[1].val||size[a[1].id]!=n-1)return printf("-1\n"),0; for(int i=2;i<=n;i++)cout<<t[i].u<<" "<<t[i].v<<'\n';
		return 0;
	}
}
signed main()
{
	return lzz::main();
} 
```

---

## 作者：Cx114514 (赞：1)

### 题目链接：[[ARC103F] Distance Sums](https://www.luogu.com.cn/problem/AT_arc103_d)
#### 闲话
看到这道题的时候发现 $d$ 值最小的一定是树的重心，就一直想着给已知点加儿子，结果发现限制条件越搞越多。

唉，构造题就是这样，脑电波对不上就完了。

#### 正文
接上文，一个点的儿子会有很多个，但一个点的父亲只会有一个。考虑给已知点找父亲。


设 $u$ 是 $v$ 的父亲，$sz_{v}$ 表示 $v$ 的子树大小。

先引入一个结论：$d_{u}=d_{v}-\left(n-2\times sz_{v}\right)$。

证明：当目标点从 $u$ 移到 $v$ 时，会有 $sz_v$ 个节点距离 $-1$，有 $n-sz_v$ 个节点距离 $+1$。

首先，不难发现，$d$ 值最小的一定是树的一个叶子，其 $sz=1$。那么，根据上面给出的结论，能唯一确定其父亲的 $d$ 值，继而唯一确定其父亲。

那么，只要在找到 $d$ 最小的节点后，将其删去，再在剩余的树上找到 $d$ 最小的节点。这样重复进行 $n-1$ 次即可确定树的形态。

但上述过程均依赖于 $d$ 值的差，无法保证 $d$ 值的和满足条件。计算所有节点到重心的总距离判断一下即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, ans, sz[100005], fa[100005];

struct node
{
	int d, num;
} a[100005];

bool cmp(node q, node p)
{
	return q.d > p.d;
}

vector < int > G[100005];

void dfs(int u, int dis)
{
	ans += dis;
	for (int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		dfs(v, dis + 1);
	}
}

signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].d;
		a[i].num = i;
	}
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i < n; i++)
	{
		sz[a[i].num]++;
		int D = a[i].d - (n - 2 * sz[a[i].num]);
		int L = i + 1, R = n, mid, ans = -1;
		while (L <= R)
		{
			mid = (L + R) / 2;
			if (a[mid].d >= D)
			{
				ans = mid;
				L = mid + 1;
			}
			else R = mid - 1;
		}
		if (ans == -1 || a[ans].d != D)
		{
			cout << -1 << endl;
			exit(0);
		}
		fa[a[i].num] = a[ans].num;
		G[a[ans].num].push_back(a[i].num);
		sz[a[ans].num] += sz[a[i].num];
	}
	dfs(a[n].num, 0);
	if (ans != a[n].d)
	{
		cout << -1 << endl;
		exit(0);
	}
	for (int i = 1; i < n; i++)
		cout << a[i].num << " " << fa[a[i].num] << endl;
}
```

---

## 作者：ZigZagKmp (赞：1)

本文同步于我的
[cnblog](https://www.cnblogs.com/ZigZagKmp/p/14374450.html)

## 题意简述
给定 $n$ 个互不相同的整数 $D_i$，表示一棵树每一个节点到其他所有节点的简单路径距离和。

构造出原树，或判断这是不可能的。

$n\le 10^5$。

## 算法分析
乍看上去没有任何思路，考虑先~~瞎~~找一些性质。

首先我们考虑两个相邻的节点 $x,y$，并假设 $y$ 是 $x$ 的父节点，那么不难发现 $D(x)=D(y)-siz(x)+\left(n-siz(x)\right)$，即 $D(x)=D(y)-2siz(x)+n$ 。

由这个性质，我们不难发现，所有 $D_i$ 中最大的一定是一个叶子节点的 $D_i$ 。

因此我们考虑将这棵树自底向上构造出来。首先先对 $D_i$ 从大到小排序，然后维护一个森林，存储每一棵树的根节点，树大小，树根的 $D_i$ ，这样我们可以求出每一棵树**要连接的父节点**的 $D_i$。对于一个新加的节点，我们找到所有可以作为其儿子的树，连边即可。最后连 $n-1$ 条边即可。

下面我们考虑证明这个构造的正确性。首先我们要证明对于任意一棵树，都能找到一个节点，使得从这个节点所有叶子的 $D_i$ 递增。

$D_i$的递推式与 $siz$ 有关，因此我们直接取树的重心，由树的重心性质不难发现，其除了其本身以外所有节点的 $2\times siz<n$，因此 $D(x)>D(y)$。

接着我们要证明，如果有解，上面的构造一定能得到一个可行解。

由于 $D_i$ 互不相同，所以如果对于当前枚举的节点 $i$ ，有一棵树的根 $x$ 满足连边条件却不连边，**以后一定没有连边的机会**，因此一定要连边才可能有解。这样的构造从根到叶子 $D_i$ 递增，由上证单调性可知对于任意有解的树，这样的构造一定能将其构造出来。

但由于一些边界问题，上述构造得到的解不一定满足题意，我们需要再检验一次。

找连边的节点可以用 `set` 维护，每一个元素会进入离开set一次，均摊下来复杂度为 $O(n\log n)$。

## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define int long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
struct node{
	int id,vl;
	bool operator <(node y)const{
		return vl>y.vl;
	}
}a[maxn];
int edf[maxn],edt[maxn],ett;
struct nds{
	int rt,siz,vl;
	bool operator <(nds y)const{//按照应该的父节点di排序
		return ((vl+2*siz-n)==(y.vl+2*y.siz-n))?(rt<y.rt):((vl+2*siz-n)<(y.vl+2*y.siz-n));
	}
};
set<nds>st;
namespace CHK{//二次检验
	vector<int>G[maxn];
	int d[maxn],siz[maxn];
	void dfs1(int x,int pa){
		siz[x]=1;
		for(auto y:G[x]){
			if(y==pa)continue;
			dfs1(y,x);
			siz[x]+=siz[y];
			d[x]+=d[y]+siz[y];
		}
	}
	void dfs2(int x,int pa){
		for(auto y:G[x]){
			if(y==pa)continue;
			d[y]=d[x]-2*siz[y]+n;
			dfs2(y,x);
		}
	}
	void chk(){
		for(int i=1;i<=ett;++i){
			G[edf[i]].push_back(edt[i]);
			G[edt[i]].push_back(edf[i]);
		}
		dfs1(1,0);dfs2(1,0);
		for(int i=1;i<=n;++i){
			int x=a[i].id,dd=a[i].vl;
			if(d[x]!=dd){
				puts("-1");
				exit(0);
			}
		}
	}
}
signed main(){
	read(n);
	for(int i=1;i<=n;++i){
		read(a[i].vl);a[i].id=i;
	}
	sort(a+1,a+n+1);
	set<nds>::iterator itl,itr,it,it0;
	for(int i=1;i<=n;++i){
		if(!st.size()){
			st.insert((nds){a[i].id,1,a[i].vl});
			continue;
		}
		int tvl=a[i].vl,tn=(n>>1);
		if(n&1)++tvl;//这里是用set写不太方便的一个地方，这里强行构造出一个siz,vl使得vl+2*siz-n=di
		itl=st.lower_bound((nds){0,tn,tvl});
		itr=st.upper_bound((nds){n+1,tn,tvl});
		if(itl==itr){
			st.insert((nds){a[i].id,1,a[i].vl});
			continue;
		}
		int sm=1;
		for(it=itl;it!=itr;++it){
			++ett;
			edf[ett]=a[i].id;
			edt[ett]=(*it).rt;
			sm+=(*it).siz;
		}
		st.insert((nds){a[i].id,sm,a[i].vl});
		for(it=itl;it!=itr;){
			it0=it;++it;
			st.erase(it0);
		}
	}
	if(st.size()>1){
		puts("-1");
	}
	else{
		CHK::chk(); 
		for(int i=1;i<=ett;++i)printf("%lld %lld\n",edf[i],edt[i]);
	}
	return 0;
}

```

---

## 作者：xukehg (赞：0)

考虑定根后一条从 $u$ 到 $u$ 的父亲 $v$ 的边，由经典的换根 dp 可以得出 $d_v = d_u - 2 \times siz_u + n$，其中 $siz_u$ 是 $u$ 的子树大小。

你注意到叶子的父亲的值一定比叶子的值小，那显然 $d$ 最大的必然是某个叶子。因为 $d$ 值互不相同，按照这个性质模拟即可确定唯一可能的树。演算 $d_1$ 是否一致即可。

[记录。](https://atcoder.jp/contests/arc103/submissions/65996918)

---

## 作者：Corzica (赞：0)

根据一些结论，可以得到 $d_p=d_q+n-2siz_p$（q 是 p 的父亲）。

而如果把重心当作这一刻数的根，那么对于满足 $p$ 是 $q$ 的祖先的两点来说，一定有 $d_p<d_q$。

我们按 $d$ 排序，从大到小枚举。

显然，所有节点中 $d$ 值最大的一个点一定是叶子节点，也就说明它的 $siz$ 唯一确定，那么他父亲的 $d$ 也唯一确定了。

当枚举到一个非叶子时，因为它子树内的节点的 $d$ 均大于它，所以它的 $siz$ 一样唯一确定，那么一整棵树这样子就能确定下来了。

最后检查一下总和是否和重心的 $d$ 对得上就行。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, fa[100005], sum, siz[100005], cnt;
pair<int, int> a[100005];
map<int, vector<int>> ma;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a + 1, a + n + 1);
	sum = a[1].first;
	cnt = n - 1;
	for (int i = n; i >= 1; i--) {
		if (ma.find(a[i].first) != ma.end()) {
			siz[a[i].second] = 1;
			for (int j : ma[a[i].first]) {
				siz[a[i].second] += siz[j];
				fa[j] = a[i].second;
				cnt--;
			}
		} else {
			siz[a[i].second] = 1;
		}
		if (i != 1) sum -= siz[a[i].second];
		ma[a[i].first + 2 * siz[a[i].second] - n].push_back(a[i].second);
	}
	if (!sum && !cnt) {
		for (int i = 2; i <= n; i++) {
			cout << a[i].second << " " << fa[a[i].second] << "\n";
		}
	} else {
		cout << -1;
	}
}
```

---

## 作者：legenc6y (赞：0)

首先我们要知道一个事实：满足 $D_x$ 值最小的 $x$ 一定是重心。证明并不困难。我们以 $x$ 为根建树，和 $x$ 相连的 $y$ 满足 $D_y=D_x+n-2sz_y$，由于 $x$ 为重心所以 $sz_y\le \lfloor \frac{n}{2} \rfloor$，于是 $D_y\ge D_x$。$y$ 子树内同理。

一个比较直接的思路是，确定重心 $x$ 为根，把 $D_y$ 值大于 $D_x$ 的 $y$ 往根上连，这样会给 $y$ 一个 $sz$ 的限制，但是这样你会发现限制越来越多，而我们没有很好的处理方法。

事实上，上述推导可以引出另一个结论：$D$ 值最大的点一定是叶子节点。理解方法同上。

因为我们知道叶子节点的 $sz$ 一定是 $1$，那么我们可以轻松确定其父亲，以此类推，我们发现，按 $D$ 降序遍历节点，每个节点的 $sz$ 值一定可以根据之前的节点推出，并推得其父亲。于是我们找到了一种建树方法。最后只需要判断 $D$ 值是否合乎真实情况即可。时间复杂度 $\mathcal O(n\log n)$。

代码实现中，我使用了 `gp_hash_table` 存储每个 $D$ 值对应的节点，理论是 $\mathcal O(n)$ 但实际应该跑不过二分或者 `map`。并且我没有注意到只需要判断根节点的 $D$ 值是否合法，而是换根 dp 直接求出了所有点的实际 $D$ 值进行比较。很愚蠢，不要学 qwq。

upd: 那个 `dfs2` 里面的递归应该改成 `dfs2(v)`，我写的是 `dfs(v)`，但是由于上述原因，它仍然能通过，非常的神奇（

``` cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define pb emplace_back
#define fir first
#define sec second
using namespace __gnu_pbds;

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int maxn = 1e5 + 5;
int n, ord[maxn], siz[maxn], sz[maxn], fa[maxn];
i64 d[maxn], f[maxn];
std::vector<int> G[maxn];
bool flg = true;
gp_hash_table<i64, int> mp;

void dfs(int u) {
	siz[u] = 1; f[u] = 0;
	for (auto& v : G[u]) {
		dfs(v); siz[u] += siz[v];
		f[u] += f[v] + siz[v];
	}
	return ;
}
void dfs2(int u) {
	flg &= d[u] == f[u];
	for (auto& v : G[u]) {
		f[u] -= f[v] + siz[v]; siz[u] -= siz[v]; 
		f[v] += f[u] + siz[u]; siz[v] += siz[u];
		dfs(v);
		f[v] -= f[u] + siz[u]; siz[v] -= siz[u];
		f[u] += f[v] + siz[v]; siz[u] += siz[v];
	}
	return ;
}

int main() {
	scanf("%d", &n);
	std::iota(ord + 1, ord + 1 + n, 1);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", &d[i]), mp[d[i]] = i;
	std::sort(ord + 1, ord + 1 + n, [&](const int& lhs, const int& rhs) {
		return d[lhs] > d[rhs];
	});
	std::fill(sz + 1, sz + 1 + n, 1);
	for (int i = 1; i < n; ++i) {
		i64 lst = d[ord[i]] - n + 2ll * sz[ord[i]];
		if (!mp[lst]) return puts("-1"), 0;
		sz[fa[ord[i]] = mp[lst]] += sz[ord[i]];
	}
	for (int i = 1; i <= n; ++i)
		if (fa[i]) G[fa[i]].pb(i);
	dfs(ord[n]); dfs2(ord[n]);
	if (!flg) return puts("-1"), 0;
	for (int i = 1; i <= n; ++i)
		if (fa[i]) printf("%d %d\n", fa[i], i);
	return 0;
}
```

---

## 作者：xht (赞：0)

> [ARC103F Distance Sums](https://atcoder.jp/contests/arc103/tasks/arc103_d)

## 题意

- 有一棵 $n$ 个点的树。
- 对于每个点 $i$，已知 $d_i$，表示 $\sum_{j=1}^n \operatorname{dist}(i,j)$。
- 所有 $d_i$ 两两互不相同。
- 构造出一棵符合要求的树，或者判断无解。
- $n \le 10^5$。

## 题解

首先这棵树只有一个重心，否则这两个重心的 $d$ 值相同，且这个重心一定是 $d$ 值最小的点。

以重心为根，有每个非根节点 $x$ 满足 $d_x > d_{f_x}$，其中 $f_x$ 表示 $x$ 的父亲。

按照 $d$ 值从大到小考虑每个点 $u$，则相当于每次剥去一个叶子，且与 $u$ 相连的一定是 $d$ 值为 $d_u - n + 2s_u$ 的点 $v$，其中 $s_u$ 表示 $u$ 的子树内点的个数，需要动态维护。

重复 $n-1$ 次这个过程后即可确定这棵树的形态，最后检查一下重心的 $d$ 值是不是对的就可以了。

时间复杂度 $\mathcal O(n \log n)$。

## 代码

```cpp
#define Fail print(-1), exit(0);
const int N = 1e5 + 7;
int n, p[N], s[N], f[N];
ll d[N], ans;
vi e[N];
map<ll, int> c;

void dfs(int x, int o) {
	ans += o;
	for (int y : e[x]) dfs(y, o + 1);
}

int main() {
	rd(n), rda(d, n);
	for (int i = 1; i <= n; i++) p[i] = i;
	sort(p + 1, p + n + 1, [&](int i, int j) { return d[i] < d[j]; });
	for (int i = 1; i <= n; i++) c[d[i]] = i, s[i] = 1;
	for (int i = n; i > 1; i--) {
		int u = p[i], fa;
		c.erase(d[u]);
		if (!(fa = c[d[u]-n+2*s[u]])) Fail;
		f[u] = fa, e[fa].pb(u), s[fa] += s[u];
	}
	dfs(p[1], 0);
	if (ans != d[p[1]]) Fail;
	for (int i = 1; i <= n; i++)
		if (f[i]) print(i, f[i]);
	return 0;
}
```

---

## 作者：chihik (赞：0)

由题显然有：

$$\begin{cases}

siz_u=1+\sum_{v\in son_u} siz_v \\

d_v=d_u+n-2\times siz_v

\end{cases}$$

顺带一提，$d$ 是 换根dp 的基操。

因为我们知道 $d$ , 所以考虑将 $siz$ 消掉，从而确定父子关系。

化简可得：

$$\frac{d_{fa}+n-d_u}{2}=1+\sum_{v\in son_u} \frac{d_u+n-d_v}{2}$$

$$d_{fa}+n-d_u=2+\sum_{v\in son_u} d_u+n-d_v$$

$$d_{fa}=d_u+2-n+\sum_{v\in son_u} d_u+n-d_v$$

可以发现，$d$ 最大的节点一定是叶子，并且对于叶子 $u$ 的父亲的 $d$，满足

$$d_{fa}=d_u+2-n$$

那么可以把 $d$ 从大到小排序，维护对父亲的贡献即可。

注意我们构造出的这棵树只满足父子 $d$ 的差值，所以还要遍历这棵树判断根的 $d$ 是否与题目相同。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define LL long long

const int MAXN = 1e6;
int n , fa[ MAXN + 5 ];
vector< int > Graph[ MAXN + 5 ];
struct node {
    int id; LL d , f;
    bool operator < ( const node &x ) const { return d > x.d; }
    bool operator > ( const node &x ) const { return d < x.d; }
    bool operator > ( const LL &x  ) const { return d < x; }
    bool operator < ( const LL &x  ) const { return d > x; }
}p[ MAXN + 5 ];

int rt; LL disrt;
void dfs( int u , int dep ) {
	disrt += dep;
	for( int i = 0 ; i < Graph[ u ].size() ; i ++ ) dfs( Graph[ u ][ i ] , dep + 1 );
}

int main( ) {
    scanf("%d",&n);
    for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&p[ i ].d) , p[ i ].id = i;
	sort( p + 1 , p + n + 1 );
    for( int i = 1 ; i < n ; i ++ ) {
        fa[ i ] = lower_bound( p + 1 , p + n + 1 , p[ i ].d + 2 - n + p[ i ].f ) - p;
        if( fa[ i ] == n + 1 ) return printf("-1\n") & 0;
        Graph[ fa[ i ] ].push_back( i );
        p[ fa[ i ] ].f += p[ fa[ i ] ].d + n - p[ i ].d;
    }
    for( int i = 1 ; i <= n ; i ++ ) if( !fa[ i ] ) rt = i;
    dfs( rt , 0 ); if( disrt != p[ rt ].d ) return printf("-1\n") & 0;
    for( int i = 1 ; i < n ; i ++ ) if( fa[ i ] ) printf("%d %d\n", p[ fa[ i ] ].id , p[ i ].id );
    return 0;
}
```

---

## 作者：jockbutt (赞：0)

好像没人诶，~~来㵘一发题解。~~

感谢大神nodgd供题+毒瘤数据，这道题的数据真的不好造，很多树都不能达到要求。


------------
### 思路
题目大意：一棵边权都是$1$的树，定义$D_i$是所有节点到节点$i$的距离之和。已知 $D_1D_2D_3D_4....D_n$数组且保证两两不同，求这棵树的形态。

一道很不错的构造题，不需要掌握什么高深的算法，只需要dfs+二分就行了。
不过确实很难想。

### 简单结论：
1. 重心的$D_i$一定最小（由定义知道）

2. $D_i$最大的节点一定是叶子（不信自己逝世）

3. 如果以重心为根，则每个节点的$D_i$严格大于父亲（因为$D_i$互不相同,不可能出现双重心的情况）

### 解题方法：

1.以重心为根将$D_1D_2D_3...D_n$递减排序得到 ，则每个节点的父亲一定在自己右边。（正常操作，谁都会做）。

2.在已知$Di$的情况下，可以算出$D_father=D_i+2size_i-n$，可以直接确定父亲是谁，其中$size_i$指$i$下面（包括它自己）结点的个数。如果某个节点找不到父亲，则无解。

why?

![](https://cdn.luogu.com.cn/upload/image_hosting/8kx4lkze.png)

这样一棵树，研究A和B，A右边有$size_A$5个节点，B左边有$size_B$4个节点。A的节点比B的节点多：$5*1-4*1=1$ 个，与$5和4$相乘的那个$1$，就是他们中间那个距离。易得：$size_A+size_B=n$，所以$size_B=n-size_A$然后代入得出那个式子。

3.所有节点都找到父亲后，还要验证一遍。只需要验证根节点即可。
因为这个算法确保了$D_father-D_i$的差分都正确，但是假如$D_1'D_2'....D_n'$是从某棵树的$D_1D_2....D_n$集体
常 数 得到，则也可以利用上述算法算出原本树的形状。

时间复杂度$O(nlogn)$

## Ohhhhhhhh

这就做出来了

Code：
```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll maxn=1e5+10;
ll n;
inline ll read()
{
	ll x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll dis[maxn];
ll s[maxn],tot;
struct node{
	ll v,pos;
}a[maxn];
struct Edge{
	ll from,to;
}edge[maxn];
vector <ll> G[maxn];
inline bool cmp(node x,node y)
{
	return x.v>y.v;
}
inline void dfs(ll u,ll fa)
{
	ll size=G[u].size();
	for(ll i=0;i<size;i++)
	{
		if(G[u][i]!=fa)
		{
			dis[G[u][i]]=dis[u]+1;
			dfs(G[u][i],u);
		}
	}
}
int main(){
	n=read();
	for(ll i=1;i<=n;i++)	{s[i]=1;a[i].v=read();a[i].pos=i;}
	sort(a+1,a+1+n,cmp);//第一步
	for(ll i=1;i<n;i++)//第二步
	{
		ll l=1,r=n+1,del=2*s[i]+a[i].v-n,mid;//二分得出
		ll poss=0;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(a[mid].v<=del)
			{
				poss=mid;
				r=mid-1;
			}
			else	l=mid+1;
		}
		if(a[poss].v!=del)
		{
			printf("-1\n");//感谢绿鸟的题解，让我改出了一个神♂奇的bug
			return 0;
		}
		edge[++tot]={a[i].pos,a[poss].pos};
		G[a[i].pos].push_back(a[poss].pos);
		G[a[poss].pos].push_back(a[i].pos);
		s[poss]+=s[i];
	}
	dfs(a[n].pos,0);//第三步
	int sum=0;
	for(int i=1;i<=n;i++)	sum+=dis[i];
	if(sum!=a[n].v)//验证
	{
		printf("-1\n");
		return 0;
	}
	for(ll i=tot;i>=1;i--)
	{
		printf("%lld %lld\n",edge[i].from,edge[i].to);
	}
	return 0;
   cout<<"I AK IOI"<<endl;
}
```


---

