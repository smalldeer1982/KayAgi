# [PA 2021] Drzewo czerwono-czarne

## 题目描述

你熟悉红黑树这种数据结构吗？在本题我们将考虑一种节点颜色为红色或黑色的树，但请放心，如果你听说过刚才提到的数据结构的话，最好迅速忘掉它。

给定一棵树（即，一个无环的无向连通图），每个节点被涂成红或黑两种颜色之一。你可以选择被一条边相连的两个节点 $v$ 和 $u$，并把 $v$ 重新涂成和 $u$ 一样的颜色。

你的任务是确定经过一系列操作（**有可能不进行任何操作**）之后，一种最初的涂色情况能否变为最终给定的涂色情况。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq T, n \leq 10^5$，$1 \leq \sum n \leq 10^6$，$1 \leq a_i, b_i \leq n$。

## 样例 #1

### 输入

```
3
4
1011
1100
1 2
2 3
2 4
2
10
10
1 2
2
10
01
1 2```

### 输出

```
TAK
TAK
NIE```

# 题解

## 作者：iyaang (赞：4)

[神秘的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17110546.html)

[题目链接](https://www.luogu.com.cn/problem/P9039)

首先有三种情况是平凡的：

1. 起始和终止相同，显然有解
2. 起始中只有一种颜色并且终止和起始并不相同，显然无解
3. 考虑最后一步，一定是将某一条边上的一个点改成另一个点的颜色，所以终止的颜色序列中必定有一条边上的两个点颜色相同，即必有 $(x,y) \in G$ 且 $col_x=col_y$，否则无解。

增大限制，如果放在链上这个东西怎么判断。链上的颜色一定形如 $\text{BRBRBR}$ 或者 $\text{RBRBRB}$。所以如果起始的连续颜色段数**不少于**终止的连续颜色段数，注意到终止状态中的一个颜色段至少可以对应上起始状态中的一个颜色段，那么就可以不断挪动来得到解。特别的，如果在链的开头起始和终止颜色不同，那么起始就要少算一个连续段，原因是我们的颜色段只能伸展，不能交换顺序或者分裂开在中间插入新的颜色。

做完了链剩下的一定是一棵多叉树。

![graph.png](https://s2.loli.net/2023/02/12/X6noKhQAetLNSGr.png)

显然，样例中的情况是先用 $2$ 把 $3,4$ 染红，然后用 $1$ 把 $2$ 染白。

也不难发现，对于四个点来说，只要有一个点度数为 $3$ 就必定有解，证明如下：

1. 设有这么一个四点三边的结构 $(x,a)$，$(x,b)$，$(x,c)$，其中 $col_x=0$ 我们要使得终止状态为 $col_a=0,col_b=col_c=1$
2. 如果初始终止状态相同，自然有解
3. 如果 $col_a=col_b=col_c=1$，操作 $x \to a$ 即可
4. 如果 $col_a=col_b=0,col_c=1$，操作 $c \to x$，$x \to b$，$a \to x$ 即可
5. 如果 $col_a=col_b=col_c=0$，因为我们保证了要先满足树上必定有两种颜色，否则一定无解，所以先随便在外头找一个 $col_i=1$ 的点 $i$，然后一路染过来使得 $col_x=1$，如果这期间使得状态变成了 $col_x=col_a=1$，那么操作 $x \to b$，$c \to x$，$x \to a$，$b \to x$ $x \to c$ $a \to x$。如果 $col_a=0$ 那么就先把 $col_x$ 变成 $1$，染完 $b,c$ 后再用 $a$ 把 $x$ 染回来
6. 对于 $col_x=1$ 也是一样的分讨操作

从上面我们可以知道只要我们最后能把树转化成上面的结构，那么通过调整颜色就一定能够得到解。大胆猜想，只要树中有点度数为 $3$ 就必定有解，证明如下：

1. 从三叉树开始考虑，不妨将度数为 $3$ 的 $x$ 记为根。我们首先处理 $a$ 下面的链。在 $b$ 节点上存一个红，在 $c$ 节点上存一个黑，那么此时 $x$ 就可以看作一个可以变色的链头，用类似于处理链的方式将 $a$ 的链染合法。
2. 此时再将 $a$ 作为储存点，用相同的道理继续处理 $b$ 的链和 $c$ 的链。
3. 可以发现当每条链都合法后，我们成功转化出了上面的结构，剩下的就是四个点之间的转化，这个是好做的。
4. 对于多叉的推广情况是相同的。

于是这道题就做完了，我们只需要判断是否符合上面几个情况。时间复杂度为 $O(n)$，瓶颈在于找链的连续颜色段数量的遍历，注意判断答案的顺序。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
	while(isdigit(c)) s=(s<<1)+(s<<3)+(c^48),c=getchar();
	return s*w;
}
inline void READ(char *s)
{
	int num=0;
	char c=getchar();
	while(c!='0'&&c!='1') c=getchar();
	while(c=='0'||c=='1') s[++num]=c,c=getchar();
	return;
}

namespace LgxTpre
{
	static const int MAX=200010;
	static const int INF=4557430888798830399;
	static const int mod=998244353;
	
	int T,n;
	int x,y;
	char s1[MAX],s2[MAX];

	struct edge
	{
		int nex,to;
	}e[MAX<<1];
	int head[MAX],cnt;
	inline void add(int x,int y)
	{
		e[++cnt].nex=head[x];
		head[x]=cnt;
		e[cnt].to=y;
		return;
	}

	int deg[MAX];
	int num1,num2;
	void dfs(int now,int father)
	{
		if(s1[now]!=s1[father]) ++num1;
		if(s2[now]!=s2[father]) ++num2;
		for(int i=head[now];i;i=e[i].nex)
		{
			int to=e[i].to;
			if(to!=father) dfs(to,now);
		}
		return;
	}
	inline void init()
	{
		for(int i=1;i<=n;++i)
			head[i]=deg[i]=0;
		cnt=num1=num2=1;
		return;
	}
		
	inline void lmy_forever()
	{
		T=read(); 
		while(T--)
		{
			init();
			n=read(),READ(s1),READ(s2);
			int flag1=1,flag2=0,flag3=1,flag4=1,s;
			for(int i=1;i<n;++i)
			{
				x=read(),y=read(),
				++deg[x],++deg[y],
				add(x,y),add(y,x);
				if(s2[x]==s2[y]) flag3=0;
			}
			for(int i=1;i<=n;++i)
			{
				if(s1[i]!=s1[i-1]&&i!=1) flag1=0;
				if(deg[i]>=3) flag2=1;
				if(s1[i]!=s2[i]) flag4=0;
				if(deg[i]==1) s=i;
			}
			if(flag4)        {printf("TAK\n"); continue;}
			if(flag1||flag3) {printf("NIE\n"); continue;}
			if(flag2) {printf("TAK\n"); continue;}
			dfs(s,s);
			if(s1[s]!=s2[s]) --num1;
			if(num1<num2) printf("NIE\n");
			else printf("TAK\n");
		}
		return;
	}
}

signed main()
{
	LgxTpre::lmy_forever();
	return (0-0);	
}
```

---

## 作者：KellyFrog (赞：2)

首先一条链的问题是简单的，每个颜色会扩展成连续一段，判断颜色段数即可。

接下来判掉颜色全部相等的情况。

剩下的情况中显然存在度数 $\ge 3$ 的点，不妨假设其为 $u$，不难发现，我们总可以让其中一些儿子为黑，一些为白。不难发现，借助 $u$ 可以任意交换、染色所有儿子，只要不全变成一个颜色。

那么直接以这个点为根，儿子可以向子树不断发出 黑/白 的脉冲，显然可以满足所有子树内的限制。最后 $u$ 及其儿子不能够达到的情况就是 $u$ 和所有儿子颜色都不同。

不妨假设 $u$ 是白的，假如说能够在子树 $v$ 的儿子上“存储”一个黑色，那么只需要最后 $u,v$ 染白，用 $v$ 的儿子把 $v$ 染黑即可。不难发现，如果子树内两个颜色不是二分图的两边，那么必然存在一条边两边相同，把其到 $v$ 的路径都往下移一个就可以存储一个黑的。

剩下可能不合法的情况就是整个树黑白是二分图的两边，判掉即可。

复杂度 $O(n)$。


```cpp
// Problem: P9039 [PA2021] Drzewo czerwono-czarne
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9039
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Create Time: 2023-06-08 22:10:31
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 1e5 + 5;

int n;
int a[N], b[N];
vector<int> adj[N];
int d[N];

inline void dfs(int u, int fa) {
	d[u] = d[fa] ^ 1;
	for(int v : adj[u]) if(v != fa) dfs(v, u);
}

void solve() {
	cin >> n;
	rep(i, 1, n) adj[i].clear();
	rep(i, 1, n) {
		char ch; cin >> ch; a[i] = ch - '0';
	}
	rep(i, 1, n) {
		char ch; cin >> ch; b[i] = ch - '0';
	}
	rep(i, 2, n) {
		int u, v; cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}
	bool f = 1;
	rep(i, 2, n) f &= a[i] == a[i-1];
	if(f) {
		bool ok = 1;
		rep(i, 1, n) ok &= b[i] == a[1];
		cout << (ok ? "TAK" : "NIE") << "\n";
		return;
	}
	int mx = 0;
	rep(i, 1, n) mx = max(mx, (int)adj[i].size());
	if(mx <= 2) {
		int p = -1;
		rep(i, 1, n) if(adj[i].size() == 1) p = i;
		int las = p;
		p = adj[p][0];
		int c1 = (a[las] != a[p]) - (a[las] != b[las]), c2 = (b[las] != b[p]);
		while(adj[p].size() > 1) {
			int v = adj[p][0] ^ adj[p][1] ^ las;
			c1 += a[p] != a[v];
			c2 += b[p] != b[v];
			las = p;
			p = v;
		}
		cout << (c1 >= c2 ? "TAK" : "NIE") << "\n";
		return;
	}
	f = 1;
	rep(i, 1, n) f &= a[i] == b[i];
	if(f == 1) {
		cout << "TAK" << "\n";
		return;
	}
	dfs(1, 0);
	f = 1;
	rep(i, 2, n) f &= (b[i] ^ d[i]) == (b[i-1] ^ d[i-1]);
	cout << (f ? "NIE" : "TAK") << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}



```

---

## 作者：Reunite (赞：1)

省选前多写点题解攒 rp。

先判掉一些简单情况：初始全相同一定有解，初始颜色数量不够一定无解。那么剩下的就一定是至少要调整一步的情况了，我们发现，最后一步操作一定会产生两个同色相邻点，因此如果结束状态不存在同色相邻点也一定无解。

考虑链的情况，显然颜色段只能移动和伸缩，因此我们必须强制舍去开头异色的一段，剩下来初始和最终状态的颜色段开始一一对位匹配，如果初始颜色段不够了，那显然无解，否则容易调整有解。思考一下发现有无解只与初始和结束的颜色段数，以及首尾颜色段是否对位相同有关，扫一遍即可。

剩下来的情况，我们知道，一定有异色点，一定有度数 $\ge 3$ 的点，显然的，我们一定可以让这个多叉结构有异色点对，如果本来就异色不用管，否则强制让另一种颜色染色过来即可。

现在我们以这个度数 $\ge 3$ 的点 $u$ 为根，接下来说明此结构可以任意调整它每个儿子的颜色：要反转一个儿子颜色时，如果反转后仍然能满足该结构异色限制，显然不管，否则的话我们要把这个颜色保存起来，可以借用该点为跳板保存在另一个儿子上即可。这样我们就可以任意调整儿子的颜色了。

然后我们要说明，这样的情况时一定有解的，考虑直接推平构造每个点的颜色，利用上面的结论，从下往上一层一层的染色，每次调整就下放这一层需要的颜色，暴力染下去即可。这样就知道了，判完那些特殊情况之后，只要非链，只要有异色点，就一定有解了。复杂度 $O(n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int T,n;
char c[100005];
char s[100005];
bool vis[100005];
vector <int> g[100005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int main(){
	in(T);
	int tid=0;
	while(T--){
		in(n);
		tid++;
		scanf("%s",c+1);
		scanf("%s",s+1);
		for(int i=1;i<=n;i++) g[i].clear(),vis[i]=0;
		bool okk=1;
		for(int i=1;i<n;i++){
			int u,v;
			in(u),in(v);
			okk&=(s[u]!=s[v]);
			g[u].emplace_back(v);
			g[v].emplace_back(u);
		}
		bool ok=1;
		for(int i=1;i<=n;i++) ok&=(c[i]==s[i]);
		if(ok){puts("TAK");continue;}
		if(n==1){puts("NIE");continue;}
		if(okk){puts("NIE");continue;}
		int ss1=0,ss2=0;
		for(int i=1;i<=n;i++) ss1|=(1<<(c[i]-'0')),ss2|=(1<<(s[i]-'0'));
		if(__builtin_popcount(ss1)<__builtin_popcount(ss2)){puts("NIE");continue;}
		if(max(__builtin_popcount(ss1),__builtin_popcount(ss2))==1&&ss1!=ss2){puts("NIE");continue;}
		int mx=0,mn=1e9,u=0;
		for(int i=1;i<=n;i++){
			mx=max(mx,(int)g[i].size());
			if(mn>g[i].size()) mn=g[i].size(),u=i;
		}
		if(mx<=2){
			int s1=1,s2=1,l1=c[u],l2=s[u];
			vis[u]=1;
			if(c[u]!=s[u]) s1--;
			for(int i=1;i<n;i++){
				int vv;
				for(int v:g[u]) if(!vis[v]) vv=v;
				vis[u]=1;
				if(l1!=c[vv]) s1++;
				if(l2!=s[vv]) s2++;
				l1=c[vv],l2=s[vv];
				u=vv;
			}
			if(c[u]!=s[u]) s1--;
			if(s1>=s2) puts("TAK");
			else puts("NIE");
		}
		else puts("TAK");
	}

	return 0;
}
```

---

