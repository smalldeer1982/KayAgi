# Serval and Rooted Tree

## 题目描述

现在 Serval 是 Japari 中学的一名初中生，他依然像以前一样热爱数学。

作为一个有天赋的数学少年，他喜欢玩数字游戏。这一次，他想在一棵有根树上玩数字游戏。

一棵树是一个无环连通图。有根树有一个特殊的顶点称为根节点。节点 $v$ 的父节点是从根到 $v$ 的路径上，最后一个不同于 $v$ 的顶点。节点 $v$ 的所有以 $v$ 为父节点的节点称为 $v$ 的子节点。如果一个节点没有子节点，则称其为叶子节点。

Serval 拥有的这棵有根树有 $n$ 个节点，节点 $1$ 是根节点。Serval 会在树的所有节点上写上一些数字。不过，有一些限制。每个非叶子节点上都写有一个操作 $\max$ 或 $\min$，表示该节点上的数字应等于其所有子节点上的数字的最大值或最小值。

假设树上有 $k$ 个叶子节点。Serval 想将整数 $1, 2, \ldots, k$ 分别填入这 $k$ 个叶子节点（每个数字只能用一次）。他喜欢大的数字，所以他希望根节点上的数字尽可能大。作为他最好的朋友，你能帮帮他吗？

## 说明/提示

下图解释了样例。节点中间的数字是节点编号，节点上方的数字是节点中的数字。

在第一个样例中，无论如何安排数字，答案都是 $1$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153D/6708db6b93ae87595a2a5e6a14824b45296d26be.png)

在第二个样例中，无论如何安排数字，答案都是 $4$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153D/55298e44ca1267165e9d58705a4fc29c70e74b01.png)

在第三个样例中，为了得到 $4$，一种最优方案是将 $4$ 和 $5$ 分别放在节点 $4$ 和 $5$ 上。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153D/13208157ec6652f71e197305f666d97c9ee17111.png)

在第四个样例中，最优方案是将 $5$ 放在节点 $5$ 上。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153D/7e271f8f21b87048c8998b0ecd2a589e99082246.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
1 0 1 1 0 1
1 2 2 2 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 0 1 0 1
1 1 1 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
8
1 0 0 1 0 1 1 0
1 1 2 2 3 3 3
```

### 输出

```
4
```

## 样例 #4

### 输入

```
9
1 1 0 0 1 0 1 0 1
1 1 2 2 3 3 4 4
```

### 输出

```
5
```

# 题解

## 作者：hsfzLZH1 (赞：18)

## 题目大意

给定一个有 $n$ 个结点的以 $1$ 为根的树，每个结点上有一个操作类型 $0$ 或 $1$ 。

操作类型 $0$ 代表该节点的权值为其所有儿子的权值的最小值，操作类型 $1$ 代表该节点的权值为其所有儿子的权值的最大值。叶子结点的权值没有意义，可以忽略。

假设这棵树有 $k$ 个叶子，你需要在每个叶子上填入数字 $1-k$ ，使得按如上计算结点权值后，结点 $1$ 的权值最大，输出这个最大值。

$2\le n\le 3\times 10^5$

## 解题思路

假设答案为 $x$ ，如果一个结点上的操作为 $\min$ ，则其要求其每个儿子结点的值都大于 $x$ ，如果一个结点上的操作为 $\max$ ，其要求其中一个儿子结点的值大于 $x$ 。

按照上面的操作，如果我们到达了一个叶子结点，那么我们就需要一个大于等于 $x$ 的数来填入这个格子中，由于 $x$ 在遍历全树时不会改变，我们只需要找到一种方式，使得最后到达的叶子结点数最少。

我们发现在这个过程中唯一能控制到达叶子结点数的是操作类型 $\max$ ，在计算该节点信息的过程中，我们只需选择一个叶子结点数最小的子树，即对其所有儿子能选择的最小叶子节点数取 $\min$ 。

在操作 $\min$ 时，由于其要求每个儿子结点的值都大于 $x$ ，我们要对其儿子能选择的最小叶子结点数求和，作为该节点能选择的最小叶子结点数。

最后，我们发现根节点能选择的最小叶子结点数 $ans$ 是和 $x$ 无关的，而这个结点数的意义是至少需要选择 $ans$ 个值大于等于 $x$ 的数，那么我们的 $x$ 最大为 $k+1-ans$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=600010;
int n,op[maxn],x,k;
int cur,h[maxn],nxt[maxn],p[maxn];
int f[maxn];
void add_edge(int x,int y)
{
	cur++;
	nxt[cur]=h[x];
	h[x]=cur;
	p[cur]=y;
}
void dfs(int x,int fa)
{
	int ch=0;
	if(op[x]==1)f[x]=2e9;
	for(int j=h[x];j;j=nxt[j])if(p[j]!=fa)
	{
		ch++;
		dfs(p[j],x);
		if(op[x]==0)f[x]+=f[p[j]];
		else f[x]=min(f[x],f[p[j]]);
	}
	if(!ch)k++,f[x]=1;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",op+i);
	for(int i=2;i<=n;i++)scanf("%d",&x),add_edge(i,x),add_edge(x,i);
	dfs(1,-1);
	printf("%d\n",k+1-f[1]);
	return 0;
}
```

---

## 作者：2018ljw (赞：12)

一种不用动脑子的做法。

感性理解，假如我们能让根节点的数为 $x$，那么将值为 $x$ 的叶节点换成更小的值一定能凑出更小的数。考虑二分根节点的值能否 $\ge mid$，把 $\ge mid$ 的数看成 $1$，剩下的数看成 $0$，目标是让根节点值为 $1$。

关注到 $1$ 的数量减小答案只会变劣，$1$ 的个数越小答案越大。那么扔掉二分的外壳，问题转化为最少用几个 $1$ 可以让根节点为 $1$。

设 $dp_{x}$ 表示让 $val_x=1$，子树内最少填几个 $1$。

当前节点取 $\min$，$dp_{x}=\sum dp_{y}$；当前节点取 $\max$，$dp_{x}=\min\{dp_y\}$。

答案即为 $k-dp_1+1$。

```cpp
#include<cstdio>
#define min(x,y) (x<y?x:y)
int op[300001],fa[300001],dp[300001];
bool nlv[300001];
int main(){
	int i,n,cnt=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&op[i]);
		if(op[i])dp[i]=n+1;
	}
	for(i=2;i<=n;i++)scanf("%d",&fa[i]),nlv[fa[i]]=1;;
	for(i=n;i>1;i--){
		if(!nlv[i])dp[i]=1,cnt++;
		int x=fa[i];
		if(op[x])dp[x]=min(dp[x],dp[i]);
		else dp[x]+=dp[i];
	}
	printf("%d",cnt-dp[1]+1);
}
```

---

## 作者：SSerxhs (赞：11)

神仙dp题。

考虑设$g[x]$表示x在其子树叶子节点的权值排名最高值，则显然要使排名最大化，即$g[x]$最大化。分两种情况讨论

1：x对子节点v取min。在这种情况下，**至少有$\sum_{v}g[v]$个数字大于等于x的权值**（为什么？因为原来比v要大的肯定也比取min后的x要大），**且存在一种方案使得x排名为$\sum_{v(x->v)}g[v]$**（方法：设$S(x)$为比x大的叶子节点集合，则将$\bigcup_{v}^{}S(v)$均设为最大的权值就好了）**因此$g[x]=\sum_{v}g[v]$**

2：x对子节点取max。这个很好算，因为取了max，所以使g最小那个子节点所在子树的权值取最大的即可，其他子树一定小于x的权值，所以$g[x]=min(g[v])$

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N=3e5+2;
int lj[N],nxt[N],fir[N],f[N],g[N],t[N];
int n,m,i,bs,x,c;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
inline void add(register int x,register int y){lj[++bs]=y;nxt[bs]=fir[x];fir[x]=bs;}
void dfs(int x)
{
	if (!fir[x]) {++m;g[x]=1;return;}
	int i;
	if (t[x])
	{
		g[x]=n;
		for (i=fir[x];i;i=nxt[i]) {dfs(lj[i]);g[x]=min(g[x],g[lj[i]]);}
	} else for (i=fir[x];i;i=nxt[i]) {dfs(lj[i]);g[x]+=g[lj[i]];}
}
int main()
{
	read(n);
	for (i=1;i<=n;i++) read(t[i]);
	for (i=2;i<=n;i++) {read(x);add(x,i);}
	dfs(1);printf("%d",m-g[1]+1);
}
```


---

## 作者：xht (赞：11)

题目地址：[CF1153D Serval and Rooted Tree](https://www.luogu.org/problemnew/show/CF1153D)

挺好玩儿也挺考思维的一道题

思路：树形DP+贪心

数组 $d$ 维护这样一个值：

对于一个节点 $x$ ，它的值最大可以为**以 $x$ 为根的子树中叶子节点的数值中排名第 $d_x$ 大的数值**。

感性的理解就是，假如这个节点下有 $n$ 个叶子节点，儿这个节点的 $d$ 值为 $k$ ，那么这个节点最大可以是 $n+1-k$ 。

假设现在在节点 $x$ ：

如果 $x$ 是叶子节点，那么 $d_x = 1$ ；

如果 $x$ 是 $min$ 节点，那么 $d_x = \sum_{y \in son_x}\ d_y$ ；

如果 $x$ 是 $max$ 节点，那么 $d_x = min_{y \in son_x}\ d_y$ 。

那么显然 $ans = cnt + 1 - d_1$ ，其中 $cnt$ 为叶子节点个数。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 6;
int n, a[N], d[N], cnt;
vector<int> e[N];

void dfs(int x) {
	if (!e[x].size()) {
		d[x] = 1;
		++cnt;
		return;
	}
	d[x] = a[x] ? n : 0;
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		dfs(y);
		if (a[x]) d[x] = min(d[x], d[y]);
		else d[x] += d[y];
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 2, f; i <= n; i++) {
		scanf("%d", &f);
		e[f].push_back(i);
	}
	dfs(1);
	cout << cnt + 1 - d[1] << endl;
	return 0;
}
```

---

## 作者：VinstaG173 (赞：4)

本校高中毕业的大一dalao @[bzh](https://codeforces.com/profile/bzh)出的题orz

一个有趣的树形dp好题。

这个dp嘛，首先想直接按min-max的规则dp（边界的dp值都不确定怎么dp？边儿去！）。。。

然后呢，想到取最大值，于是就看看min节点和max节点取最大值要满足什么条件。

显然，min节点要使得其所有子节点值的最小值尽可能大，max节点要使得其所有子节点值的最大值尽可能大（其实就是任意一个子节点的值）。

所以，我们可以说min的所有子节点影响其值，而max节点可以让我们任意选一个子节点影响其值。

因此我们得出一个贪心策略：对于叶子节点，只有一个节点影响该节点值；对于非叶子节点，若是min节点，影响该节点值的叶子结点个数为该节点所有子节点值的叶子结点个数之和；若是max节点，影响该节点值的叶子结点个数为该节点所有子节点值的叶子结点个数中最小值。这样，影响根节点值的叶子节点数就确定了，只需在这些节点上依次填入最大的一些数，就能最大化根节点的值。所以设有$k$个叶子节点影响根节点的值，则根节点值为第$k$大值即$N-k+1$。

Code:
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int N,M,a[300003];
int f,head[300003],cnt;
struct edge
{
	int nxt,to;
}e[300003];
inline void add(int x,int y)
{
	e[++cnt].nxt=head[x];
	e[cnt].to=y;
	head[x]=cnt;
}
inline int dfs(int u)
{
	int ans;
	if(!head[u])++M,ans=1;
	else if(a[u])
	{
		ans=N+1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			ans=min(ans,dfs(v));
		}
	}
	else
	{
		ans=0;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			ans+=dfs(v);
		}
	}
	return ans;
}
int main()
{
	scanf(" %d",&N);
	for(int i=1;i<=N;++i)
	{
		scanf(" %d",&a[i]);
	}
	for(int i=2;i<=N;++i)
	{
		scanf(" %d",&f);
		add(f,i);
	}
	int K=dfs(1);
	printf("%d\n",M-K+1);
	return 0;
}
```

---

## 作者：Trimsteanima (赞：4)

### Description
给一棵树，每个点是子节点的最大值或最小值，将叶子节点填上整数，使这棵树的根最大。
### Solution
明显的$dp$题，代码很短。
分类讨论如下：

1、如果是叶子节点，$d_x = 1$

2、如果是$min$节点，$d_x =\sum_{y \in son_x} d_y$

3、如果是$max$节点，$d_x = min_{y \in son_x} d_y$


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 300005;
int n, a[N], b[N], x, k, ans[N], c[N];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        ans[i] = a[i] ? n + 1 : 0, c[i] = -1;
    }
    for (int i = 2; i <= n; i++) {
        scanf("%d", &x);
        b[i] = x, c[x] = i;
    }
    for (int i = n; i > 1; i--) {
        if (c[i] == -1)
            ans[i] = 1, k++;
        x = b[i];
        ans[x] = a[x] ? std::min(ans[x], ans[i]) : ans[x] + ans[i];
    }
    printf("%d\n", k + 1 - ans[1]);
    return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：3)

### 前言

这里是蒟蒻 Wind_Leaves_ShaDow 尝试狂刷 CF 的第 $1$ 天。

### 正文

第一眼看到题其实没想到是树形 dp。那好，先贪心做呗。在树上就用递归，先找一遍叶子节点，然后填数。然后在每一次递归的时候传一个值域，代表这棵树只能用这个值域的数填。

如果这个是要找最大值，那么把当前能够填的数中最大的一个传下去。此时我们要传子树中最优的一个，也就是找的是最大值、子树大小最小的一棵。

如果是最小值呢？这种时候就不好办了。我们无法分配传下去的值域，因为我们无法推出来什么样的分配才是最优。

那么就这么卡住了，然后放弃吗？

错误的。树上问题，很常见的一种解决方法就是，**正着推行不通的时候，尝试倒着推**，也就是先递归子树，再汇总答案于自身，也就是我们常说的 **树形 dp**。

但是如何 dp 又成了问题。如何设状态？

这个时候我们回头看我们的贪心。**我们发现，填的大数尽可能少，就能让根节点的数尽可能大**。那么我们的状态这么设：$dp_i$ 表示以 $i$ 为根的子树最少填多少个大数。

- 如果是最大值操作，那么 **只用在所有子树中选一个最小的得到最优解**，因为是最大值，所以 **只要有一棵树里面放大数** 就好，所以转移方程就是 $dp_i=\min(\sum{(\text{i,e 是父子节点})}dp(e))$；

- 如果是最小值操作，那么需要的是 **所有子树的总和**，因为是最小值，所以 **要在所有子树中放大数不然不会得到更优的根**，所以转移方程就是 $dp_i=\sum({\text{i,e 是父子节点})dp_e}$。

~~话说 latex 是不是这么打的……~~

~~详见代码，写的不好，轻喷：~~

```cpp
#include <bits/stdc++.h>
#define int long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;
typedef double db;
const int N=3e5+10,INF=1e14;

int n,fa[N],dp[N],K=0;
bool op[N];
vector<int>v[N];

inline void Dp(int p){
	if(op[p])dp[p]=INF;//要求最小值（这里指代码中）所以初始化无限大
	if(v[p].empty()){
		K++;//求叶子节点个数
		dp[p]=1;//叶子节点初始化为 1
		return;
	}
	for(auto e:v[p]){
		Dp(e);//先处理子树
		if(op[p])dp[p]=min(dp[p],dp[e]);
		else dp[p]+=dp[e];
	}//显然的转移
	return;
}

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>op[i];
	for(int i=2;i<=n;i++){
		cin>>fa[i];
		v[fa[i]].push_back(i);
	}
	Dp(1);
	cout<<K-dp[1]+1;//叶子节点个数-最少的大数数量+1
	return 0;
} 
```

最后求答案的时候加了 $1$，原因是我们的答案应该是填的大数中最小的那一个。

### 后记/总结

一道比较考思维的 dp，树形 dp 的码量一般都不高，如何想到 dp 才是这类问题的关键。这里 **没有把具体的数值进行考虑，而是单纯对数的大小进行考虑，也不妨是一种解题技巧吧**。

---

## 作者：djh123 (赞：3)

树形dp

设$f[x]$表示$x$所在子树答案最大是第几大，$siz[x]$表示$x$所在子树内叶子节点的个数。

那么$siz[now]-f[now]$这一段数字不可能再被使用了。

转移时，若当前节点是求$max$，那么$f[x]=siz[x]-min(siz[to]-f[to])$，相当于找一棵子树，把最大的都给这棵子树。

若当前节点是$min$，那么要先把子节点不能使用的数字填满，设总共有$sum$个，然后每个子节点填一个数，取最小值，那么$f[now]=siz[now]-sum-\text{孩子个数}+1$

边界条件：$f[\text{叶子节点}]=1$

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int uint;
typedef double db;
typedef pair <int, int> pii;
typedef vector <int> vi;

#ifndef ONLINE_JUDGE
#define DEBUG
#endif

#define Fi first
#define Se second
#define pb push_back
#define mp make_pair
#define rep(x, a, b) for(int x = (a); x <= (b); ++ x)
#define per(x, a, b) for(int x = (a); x >= (b); -- x)
#define rop(x, a, b) for(int x = (a); x < (b); ++ x)
#define por(x, a, b) for(int x = (a); x > (b); -- x)
#define forE(x, a) for(int x = head[a]; x; x = nxt[x])

#ifdef DEBUG
#define debug(x) cerr << #x << ": " << x << '\n'
#else
#define debug(x)
#endif

void open(const char *s){
	#ifdef DEBUG
    char str[100];
	sprintf(str,"%s.in",s);
	freopen(str,"r",stdin);
	sprintf(str,"%s.my",s);
	freopen(str,"w",stdout);
	#endif
}

const db eps = 1e-8;
const int inf = 0x3f3f3f3f;
const int Minf = 0x7f7f7f7f;
const LL INF = 0x3f3f3f3f3f3f3f3fll;
const LL MINF = 0x7f7f7f7f7f7f7f7fll;

const int N = 5e5 + 50;

int opt[N], fa[N]; 
vi q[N];
int f[N];
int siz[N];

void dfs(int now) {
	int y = 0;
	int Min = inf, sum = 0;
	rop(i, 0, (int)q[now].size()) {
		++ y;
		dfs(q[now][i]);
		siz[now] += siz[q[now][i]];
		Min = min(Min, siz[q[now][i]] - f[q[now][i]]);
		sum += siz[q[now][i]] - f[q[now][i]];
	}
	siz[now] += (y == 0);
	if(opt[now] == 1) f[now] = siz[now] - Min;
	else f[now] = siz[now] - sum - y + 1;
	if(y == 0) f[now] = 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 
	
	int n; cin >> n;
	rep(i, 1, n) cin >> opt[i];
	rep(i, 2, n) cin >> fa[i], q[fa[i]].pb(i);
	
	dfs(1);
	
	printf("%d\n", f[1]);
	
}
```


---

## 作者：花里心爱 (赞：3)

表示当时这场CF我没打。然后第二天看这题看了2h才看出来做法（我太弱了）。

然后这种在树上取$\ \min\ \max\ $之类的应该就是树形dp。

我们会发现题目要求我们向叶子填一个排列，最后经过向上合并后使根节点的值最大。

此处我们先设以点$u$为根的子树中的叶子节点个数为$size[u]$。~~显然~~总的叶子节点数为$size[1]$。

然后如果根节点有很多子树，我们就要将$1\sim s$的排列分配给它的子树。如果一个子树还有很多子树，那么我们就要将分配给它的数分配下去……

然后我们就可以递归分治了……

吗？

我们发现我们递归的时候并不知道我们当前分配给这个子树的是哪些数。

但是我们知道分配下去的数一定互不相同（~~显然，因为一开始是一个排列~~）。

然后我们发现我们只需要知道分配下去的数分别是第几大就可以。

然后我们还发现实际上我们连分配下去的数分别是第几大都不需要知道，我们只需要知道如果当前子树$u$填一个$1\sim size[u]$的排列的话，最终根节点的最大值是多少。

于是我们设$f[i]$表示在以$i$为根的子树，叶子节点填入$1\sim size[i]$的排列，$i$子树的答案（也就是$i$可以填的最大值）。

~~还是很显然~~如果$i$是叶子，那么$f[i] = 1$（你只能填$1$）

然后看$i$不是叶子的情况。假设我们已经递归求出了$i$所有子树的$f$和$size$。

如果$i$上面的操作是对子节点取$\max$，那么我们只需要关心其中一个节点的最大值，不需要关心其他点。假设我们已经找到了这个子树$v$，然后我们把最靠近最大值的点都填进这个子树里，那么答案即为$size[i]-(size[v]-f[v])$

（因为你填了$size[v]$个点在这个子树里，就有$size[i]-size[v]$个填小的数的点对答案没有影响，然后本来$v$最大能取$f[v]$，现在就可以取$size[i]-size[v]+f[v]$）。

然后关于怎么找$v$，只需要对所有子树的$size[v]-f[v]$取$\min$即可。

然后考虑$i$上面的操作是对子节点取$\min$，这个时候我们就要考虑把比较大的树均衡地放进每个子树里。然后我们发现每个子树要占掉$size[v]-f[v]$个比较大的数。于是答案即为$size[i]-\sum{(size[v]-f[v]+1)}+1$

（可以参考着上面的解释理解）

然后上代码：
```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define maxn 300005
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

int n, op[maxn];
int sz[maxn], f[maxn];
int nlf[maxn];
int head[maxn], ver[maxn], nxt[maxn], tot;

inline void add(int u, int v) {
	ver[++tot] = v, nxt[tot] = head[u], head[u] = tot;
}

void dfs(int u) {
	if(!nlf[u]) {sz[u] = f[u] = 1; return;} // 是叶子，到达了分治边界
	if(op[u]) {
		f[u] = 0x3f3f3f3f; // 为了取min而初始化的极大值……
		for(int p = head[u]; p; p = nxt[p]) {
			int v = ver[p]; dfs(v);
			sz[u] += sz[v];
			f[u] = std::min(f[u], sz[v]-f[v]);
		}
		f[u] = sz[u]-f[u];
	}
	else {
		for(int p = head[u]; p; p = nxt[p]) {
			int v = ver[p]; dfs(v);
			sz[u] += sz[v];
			f[u] += sz[v]-f[v]+1;
		}
		f[u] = sz[u]-f[u]+1;
	}
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i) op[i] = read();
	for(int i = 2; i <= n; ++i) {
		int fa = read();
		add(fa, i), nlf[fa] = 1;
	}
	dfs(1);
	printf("%d", f[1]);
	return 0;
}
```
然后转移方程看上去特别的复杂，于是我们发现每个点都用$size$减了一遍又减了回去，~~没意思~~，我们设$g[i] = size[i]-f[i]+1$

上面$g[i]$的实际含义就是以$i$为根的子树，叶子节点填入$1\sim size[i]$的排列，$i$子树能取到第几大的数。

然后我们把$g[i] = size[i]-f[i]+1$代入上面的转移方程，我们~~惊奇地~~发现，方程变为了：

$$g[i] = \min{g[v]}, op[i] = \max$$

$$g[i] = \sum{g[v]}, op[i] = \min$$

方程简单了很多。上面方程的含义可以类比$f[i]$的含义解释出来。

下面上代码：
```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define maxn 300005
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

int n, op[maxn];
int sz[maxn], g[maxn];
int nlf[maxn];
int head[maxn], ver[maxn], nxt[maxn], tot;

inline void add(int u, int v) {
	ver[++tot] = v, nxt[tot] = head[u], head[u] = tot;
}

void dfs(int u) {
	if(!nlf[u]) {sz[u] = g[u] = 1; return;}
	if(op[u]) g[u] = 0x3f3f3f3f; // 为了取min而初始化的极大值……
	for(int p = head[u]; p; p = nxt[p]) {
		int v = ver[p]; dfs(v);
		sz[u] += sz[v];
		if(op[u]) g[u] = std::min(g[u], g[v]);
		else g[u] += g[v];
	}
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i) op[i] = read();
	for(int i = 2; i <= n; ++i) {
		int fa = read();
		add(fa, i), nlf[fa] = 1;
	}
	dfs(1);
    // 注意题目要求的是f[1]，而f[1] = sz[1]-g[1]+1，所以我们要输出sz[1]-g[1]+1
    // 也就是在1~sz[1]中，第g[1]大的数
	printf("%d", sz[1]-g[1]+1);
	return 0;
}
```

---

## 作者：lenaalyth (赞：2)

题目大意：给你一棵树，这颗树的每个点是他的子节点的最大值或者最小值，要求你将这棵树的叶子节点填上整数（1到叶子节点个数）这棵树的根最大。（差不多就是这个意思吧？）

首先很明显符合树状dp的结构（每个节点状态由他的子节点状态推出），所以我们按照树状dp的想法来想，题意可知根节点必定为叶子节点中的一个且叶子节点必定为1到叶子节点个数（废话），我们可以将状态为该节点最大能为他所包含的叶子节点里的第几大的数（因为我们要最大的所以求第几大的数）。
如此可以推出状态转移方程。

1.如果该点为需要最大值则这个点的值为他所有的子节点（注意是子节点）的最小值，（要最小值是因为这里存的是第几大（第一大肯定要比第二大大的））。


2.如果该点为需要最小值则这个点的值为他所有子节点（注意是子节点）的和。（他肯定比这些子节点大的数小，所以是和）

最后用叶子节点-dp【1】+1就可以了。
然后写就是了，代码如下：
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
vector<int> tr[310000];
int bj[310000];
int b[310000];
int dp[510000];
int m,n,q,h,gudan;
int dpp(int x1)
{
	int minn=1e9+7,sum=0;
	if(tr[x1].size()==0)
	{
		dp[x1]=1;
		return 0;
	}
	for(int x=0;x<tr[x1].size();x++)
	{
		if(dp[tr[x1][x]]==-1)
		{
			dpp(tr[x1][x]);
			minn=min(dp[tr[x1][x]],minn);
			sum+=dp[tr[x1][x]];
		}
	}
	if(b[x1]==1)
	{
		dp[x1]=minn;
	}
	else
	{
		
		dp[x1]=sum;
	}
}
int main()
{
	memset(dp,-1,sizeof(dp));
	cin>>m;
	for(int x=1;x<=m;x++)
	{
		cin>>b[x];
	}
	for(int x=2;x<=m;x++)
	{
		cin>>h;
		tr[h].push_back(x);
		bj[h]++; 
	}
	for(int x=1;x<=m;x++)
	{
		if(bj[x]==0)
		{
			gudan++;
		}
	}
	dpp(1);
	cout<<gudan-dp[1]+1<<endl;
}
```





---

## 作者：cmrhhh (赞：1)

题解：[Serval and Rooted Tree](https://www.luogu.com.cn/problem/CF1153D)

很有意思的题目，~~看了题解后~~想来分析一下思路来源。注意到如果直接枚举 $k$ 个叶结点的值复杂度将爆炸。所以有趣的思路就是拿排名代替真实的数值，这样可以在子树合并的时候进行优雅 `dp`。具体地，定义 $f[i]$ 为在 $i$ 节点时，该节点的值在其子树内最高排 $f[i]$ 名，进行树上转移状态。

1.当某个节点 $u$ 的操作为 $0$（取 $\min$ 操作时）

$$
f[u]=\sum_{v\in son[u]}{f[v]}
$$

2.当某个节点 $u$ 的操作为 $1$（取 $\max$ 操作时） 
$$
f[u]=\min_{v\in son[u]}{f[v]}
$$

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
int n,op[maxn],k;
vector<int>g[maxn];
int f[maxn];//i子树中，i点权为叶子排名第f[i] 大的值 。贪心考虑最大化 
void dfs(int u){
	int mn=maxn,sum=0;
	if(!g[u].size()){
		f[u]=1;
		k++;
		return;
	}
	for(int v:g[u]){
		dfs(v);
		mn=min(mn,f[v]);
		sum+=f[v];
	}
	f[u]=(op[u]==1?mn:sum);
}
int main(){
//	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>op[i];
	for(int i=2;i<=n;++i){
		int f;
		cin>>f;
		g[f].emplace_back(i);
	}
	dfs(1);
	cout<<k+1-f[1];
	return 0;
}

```

----------------------------------------------------------------------------------CF的轻工业思维题

---

## 作者：Vitamin_B (赞：0)

# 思路
对于每个 $\min$ 合并，肯定会有一些较大数受到浪费，例如把 $4,5$ 进行 $\min$ 合并，得数是 $4$，这里就浪费了 $5-4=1$。我们设 $dp_x$ 表示以 $x$ 为根的子树里最少得浪费，然后从 $n\sim1$ 的顺序枚举 $^\dag$ 每个 $x$，依次更新 $dp_{f_i}$。若这是叶子结点，$dp_x=1$（$dp_x$ 是指 $\text{能选的颜色数}-\text{最大答案}+1$）。若 $num_{x}=1$，因为是取所有子树的最大值，这个最大值肯定要是所有子树中浪费最小的那个，$dp_x=\min dp_{son_x}$；否则就是取最小值，就是取所有子树中值最小的那个，但因为在它之前还有别的所有子树，所以 $dp_x=\sum dp_{son_x}$。另外注意这是浪费的值，所以答案是 $k-dp_x+1$。

$^\dag$ 因为 $f_i<i$，所以倒着枚举即可。
# 代码
```cpp
# include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int inf = 1e9;
int n, f[300005], dp[300005], k;
bool a[300005];
bitset <300005> leaf;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
		leaf[i] = 1;
		if (a[i])
			dp[i] = inf;
	}
	for (int i = 2; i <= n; ++ i)
		cin >> f[i], leaf[f[i]] = 0;
	for (int i = n; i; -- i) {
		if (leaf[i])
			++ k, dp[i] = 1;
		if (a[f[i]])
			dp[f[i]] = min (dp[f[i]], dp[i]);
		else
			dp[f[i]] += dp[i];
	}
	cout << k - dp[1] + 1;
	return 0;
}
```

---

## 作者：konyakest (赞：0)

**从变化中找不变**



------------


初看这道题，感觉十分不可做，一堆不知道的数，让你求 $\min/\max$ 后最大是多少？

如果只是盯住这些数本身，想着怎么去填，那就没办法做了

其实，我们只需要**从变化中找不变**，想想：一堆数取 $\min/\max$，哪些信息是已知的？

**排名！**

所以，我们只要 DP 排名即可

设 $dp_u$ 表示节点 $u$ 在以 $u$ 为根的子树中**最小**排名多少（注：我们从大到小排，即认为最大的那个为第一名）

则：

- 如果这个节点是 $\max$ ，则它的排名**最小**为它**所有儿子**的排名的**最小值**，最小值当我们给**排名最小的儿子的子树**分配最大的数据时得到

- 如果这个节点是 $\min$ ，则它的排名**最小**为它**所有儿子**的排名**之和**，最小值当这样分配时得到：

  - 若它的儿子 $i$ 的排名为 $k$ ，则**先**给它分配 $k$ 个**还没有被分配的**最优的数据
  
  - 剩下的数据随便分

所以，上述分析的最小值一定可以被取到

最后，我们算出根节点的排名，用叶子节点个数减去，再+1即可

```cpp
#include <bits/stdc++.h>
using namespace std;
#define F(i,j,k) for (signed i=signed(j);i<=signed(k);i++)
#define endl '\n'
const int maxn=3e5+5;
int n,x,leaf;
vector<int> v[maxn];
bool a[maxn];
int dfs(int u,int fa){
	// cerr<<u<<" "<<fa<<endl;
	if(v[u].size()==1) return leaf++,1;
	if(a[u]){
		int ans=INT_MAX;
		for(auto i:v[u]){
			if(i==fa) continue;
			ans=min(ans,dfs(i,u));
		}
		return ans;
	}
	else{
		int ans=0;
		for(auto i:v[u]){
			if(i==fa) continue;
			ans+=dfs(i,u);
		}
		return ans;
	}
}
signed main() { 
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	F(i,1,n) cin>>a[i];
	F(i,2,n) cin>>x,v[x].push_back(i),v[i].push_back(x);
	dfs(1,1);//先算一下叶子节点的个数
	cout<<leaf-dfs(1,1)+1<<endl;
	return 0; 
}
```



---

## 作者：cqbzhyf (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1153D)

题目大意为：

$n$ 个节点以 $1$ 为根的一棵树，每个非叶子节点都有一个操作 `max` 或 `min`（$0$ 表示 `min`，$1$ 表示 `max`），表示这个节点中的值应该分别等于其子节点中所有值的最大值或最小值。假设树上有 $k$ 个叶节点，你可以将每个叶节点填上 $[1,k]$ 的数字，且每个数字只使用一次，求根节点的最大值。

---
首先这是一道简单的 `树形DP`，如果是进行 `min` 操作，就要求每个子节点大于父节点，反之也成立。

选择一个**叶子结点数最小**的子树，对其所有儿子能选择的最小叶子节点数取 `min`。对其子节点能选择的最小叶子结点数**求和**，作为该节点**能选择的最小叶子结点数**。


## code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int ch=0,num=0;
	char c=getchar();
	while(!isdigit(c))ch|=(c=='-'),c=getchar();
	while(isdigit(c))num=(num<<1)+(num<<3)+(c^48),c=getchar();
	return ch?-num:num;
}
inline void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
int n,a[300005],dp[300005],tot;
bool flag[300005];
vector<int>G[300005];
inline void dfs(int x){
	for(int i=0;i<G[x].size();++i){
		dfs(G[x][i]);
		if(a[x]==1){
			if(!dp[x])dp[x]=dp[G[x][i]];
			dp[x]=min(dp[x],dp[G[x][i]]);
		}else dp[x]+=dp[G[x][i]];
	}
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=2;i<=n;++i){
		int x=read();
		G[x].push_back(i),flag[x]=1;
	}
	for(int i=1;i<=n;++i){
		if(!flag[i])dp[i]=1,++tot;
	}
	dfs(1);
	write(tot-dp[1]+1);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

## Update
2022.4.3 更新了一个错别字

显然可以发现本题是树形 `dp`。

现在，我们有一个非常容易想到的转移：

设 $dp_i$ 表示 $i$ 的最优解。

$dp_u\gets\min\limits_{v=1}^ndp_v(v\in u)(a_u=0)$

$dp_u\gets\max\limits_{v=1}^ndp_v(v\in u)(a_u=1)$

现在，有一个最关键的问题是：$dp_v$ 是要变化的！！！

我们可以想到一个方式，因为每个数的排名不会变化，我们可以设 $dp_i$ 表示的是 $i$ 的最优排名，排名越小值域越大。那么，我们可以得到每个叶子节点的 $dp$ 为 $1$。我们可以很容易地得到：

$dp_u\gets\min\limits_{v=1}^ndp_v(v\in u)(a_u=1)$

那么，我们继续，如果 $a_u=0$，一个子节点 $v$ 可以显然得到 $dp_u\gets dp_v$。那么我们可以发现，设 $v_1$、$v_2$ 分别为 $u$ 的子节点，假设选择 $v_2$，那么 $v_1$ 中的值，$v_2$ 就不能有，那么最后的答案就是 $dp_{v_1}+dp_{v_2}$。以此类推，可得：

$dp_u\gets\sum\limits_{v=1}^ndp_v(v\in u)(a_u=0)$

时间复杂度 $O(n)$。
```cpp
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int n,k,dp[maxn],f[maxn];
vector<int> G[maxn];
void dfs(int u){
	if(!G[u].size()){
		++k;
		dp[u]=1;
		return; 
	}
	if(f[u])
		dp[u]=0x3f3f3f3f;
	for(int i=0,len=G[u].size();i<len;++i){
		int v=G[u][i];
		dfs(v);
		if(f[u])
			dp[u]=min(dp[u],dp[v]);
		else
			dp[u]+=dp[v];
	}
}
inline char gc(){
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int res=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return res;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i)
		f[i]=read();
	for(int i=2,a;i<=n;++i){
		a=read();
		G[a].push_back(i);
	}	
	dfs(1);
	printf("%d\n",k-dp[1]+1);
	return 0;
}
```

---

## 作者：Harry_Hedwig (赞：0)

# 0x00 思路
先看题。
>$n$ 个节点**以 $1$ 为根的一棵树**，每个非叶子节点都有一个操作 $\max$ 或 $\min$（$0$ 表示 $\min$，$1$ 表示 $\max$），表示这个节点中的值应该分别等于**其子节点中所有值的最大值或最小值**。假设树上有 $k$ 个叶节点，你可以将每个叶节点填上 $[1,k]$ 的数字，且每个数字只使用一次，求**根节点的最大值**。

他要求每个数字只用一次……？

或者说……一个叶节点可以填任意一个数？

根节点的……最大值？

想到什么了吗？

我们可以假设在某个节点下的所有叶子节点占据了在所有数中最大的数，那么在这样的情况下，我们就可以根据 $\min$ 和 $\max$ 找到这个节点可以得到的最大值在 $[1,n]$ 从大到小的排列中所处的位置。

接着有了思路，我们再具体情况具体分析。
# 0x01 $\min$ & $\max$
1. $\max$

	我们只需要去找它的所有子节点中最大的那一个即可。
2. $\min$

	由于其要求每个儿子结点的值都大于等于它自身的值 ，我们要看它所有可以到达的叶子节点的个数，因为我们假设的是每一个节点可以成为最大的值是多少，而最直观的就是看它的儿子节点，因此我们可以将其儿子能选择的最小叶子结点数之和，作为该节点能选择的最小叶子结点数。
## code
```c++
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
using namespace std;
int oper[300005],d[300005],leave;
bool book[300005];
vector<int>V[300005];
void Go(int now)
{
        int i;
        if(oper[now])//初始值
            d[now]=1e9;
        for(i=0;i<V[now].size();i++)
        {
            Go(V[now][i]);
            if(!oper[now])//min
                d[now]+=d[V[now][i]];
            else//max
                d[now]=min(d[now],d[V[now][i]]);
        }
        if(V[now].size()==0)//叶子节点值均为1
        {
            d[now]=1;
            leave++;
        }
}
int main()
{
      int n,i,x;
      scanf("%d",&n);
      for(i=1;i<=n;i++)
          scanf("%d",&oper[i]);
      for(i=1;i<n;i++)
      {
          scanf("%d",&x);
          V[x].push_back(i+1);
      }
      Go(1);
      printf("%d",leave+1-d[1]);
      //d数组记录的是从大到小取得的最大值的排名，又由于叶子节点取值为[1,叶子节点数（leave)]，所以用leave来减
      return 0;
}
```

---

## 作者：issue_is_fw (赞：0)

## 想出来后才发现不是什么难题哈哈


刚开始看真是无从下手,想$dp$却又确定不了最大值。

但是突然发现答案具有单调性,那二分呀!!

**那我们直接去check这个二分的mid就好了**

设$dp[u]$表示$u$为了达到$mid$这个值,子树的最小花费(需要使用几个大于$mid$的值)

若$u$是叶子节点,$dp[u]=1$,因为只需要$u$选一个大于等于$mid$的填上

**当u不是叶子节点时**

显然当$u$节点取$max$时,在所有儿子中选一个最小的$dp[son]$即可

当$u$节点取$min$时,每个儿子都要达到$mid$,所以$dp[u]=\sum{dp[son]}$

那么1节点到达mid需要的最小花费是$dp[1]$

而一共有$k-mid+1$个数大于等于$mid$($k$表示叶子节点个数)

所以当$k>=dp[1]$时二分成功,继续缩小范围

[二分dp代码](https://paste.ubuntu.com/p/XYyphQrmsC/)

但是我竟然的发现树型dp的过程中完全没有用到二分的$mid!$

这说明每次$dfs$得到的$dp$数组相同,不需要每次二分都去$dfs$

**实际上连二分都不需要了**

回想一下设计的状态$dp[i]$

实际上就表示$i$节点要达到$x$,需要有$dp[i]$个比x大的数字!!

也就是$k-x+1>=dp[1]$

$x<=k+1-dp[1]$

$x$最大取$k+1-dp[1]$

$至于代码和那个二分的一摸一样,就是去掉了二分而已.$



---

