# [ABC133E] Virus Tree 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc133/tasks/abc133_e

$ N $ 頂点、$ N-1 $ 辺を持つ木が与えられます。 頂点には番号 $ 1,2,...,N $ がつけられており、$ i $ 番目の辺は頂点 $ a_i,b_i $ をつないでいます。

あなたは $ K $ 色の絵の具を持っています。 木の頂点それぞれに対して、以下の条件を満たすように、$ K $ 色の中から $ 1 $ 色を選んで塗ることにしました。

- 二つの異なる頂点 $ x,y $ 間の距離が $ 2 $ 以下ならば、頂点 $ x $ の色と頂点 $ y $ の色は異なる。

木を塗り分ける方法は何通りあるでしょうか。 総数を $ 1,000,000,007 $ で割った余りを求めてください。

木とは

木とはグラフの一種です。詳しくはこちらをご覧ください: [Wikipedia「木 (数学)」](https://ja.wikipedia.org/wiki/%E6%9C%A8_(%E6%95%B0%E5%AD%A6))

距離とは

二つの頂点 $ x,y $ 間の距離とは、$ x $ から $ y $ に到達する際にたどる必要のある最小の辺数です。

## 说明/提示

### 制約

- $ 1\ \leqq\ N,K\ \leqq\ 10^5 $
- $ 1\ \leqq\ a_i,b_i\ \leqq\ N $
- 与えられるグラフは木である。

### Sample Explanation 1

!\[zu\](https://img.atcoder.jp/ghi/491cd56a53e99ba7677ee4827b8f767a.png) 塗り分け方は $ 6 $ 通りです。

## 样例 #1

### 输入

```
4 3
1 2
2 3
3 4```

### 输出

```
6```

## 样例 #2

### 输入

```
5 4
1 2
1 3
1 4
4 5```

### 输出

```
48```

## 样例 #3

### 输入

```
16 22
12 1
3 1
4 16
7 12
6 2
2 15
5 16
14 16
10 11
3 10
3 13
8 6
16 8
9 12
4 3```

### 输出

```
271414432```

# 题解

## 作者：Zhangikun (赞：8)

## ~~很明显是~~树形 dp
## 思路：
不难发现，前面有 $num$ 个点给你抢颜色，所以每个节点可以染颜色的数量就是 $k-num$，其中 $num$ 为前面距离不超过 $2$ 的邻接点（其实就是父节点、爷爷节点、以及在此点之前进入 dfs 的兄弟节点）。
## 初始状态：
$dp_{cur}=k-num$
## 状态转移：
（$nxt$ 为 $cur$ 的子节点）。

$dp_{cur}=dp_{cur}\times dp_{nxt}$
## 坑点：
如果构不成合法方案，就输出 $0$，所以我们要特判一下。
## 完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long//一定要开long long!!!
using namespace std;
const int cxk=1e5+5,mod=1e9+7;
int n,k,dp[cxk];
vector<int>nbr[cxk];
bool f=0;
void dfs(int cur,int fa,int grand,int id)//当前点、父节点、爷节点、前面的兄弟节点个数
{
  if(f)return;//如果颜色不够已经被标记了，那么紧急终止递归
  int num=0;
  if(fa)num++;//有父节点
  if(grand)num++;//有爷节点
  num+=id;//加上之前来过的兄弟
  if(k-num<=0)//颜色不够了
  {
    f=1;
    return;
  }
  dp[cur]=(k-num)%mod;
  int ii=-1;
  for(int i=0;i<nbr[cur].size();i++)
  {
    int nxt=nbr[cur][i];
    if(nxt==fa)continue;
    dfs(nxt,cur,fa,++ii);
    dp[cur]=(dp[cur]%mod*(dp[nxt]%mod))%mod;//状态转移
  }
  return;
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0),cout.tie(0);
  cin>>n>>k;
  for(int i=2,x,y;i<=n;i++)
  {
    cin>>x>>y;
    nbr[x].push_back(y);//连边
    nbr[y].push_back(x);
  }
  dfs(1,0,0,0);
  if(f)goto a;//如果不够，执行书签a后面的输出0，直接return
  cout<<dp[1]%mod<<"\n";
  return 0;
  a:
  cout<<0<<"\n";
  return 0;
}
```



---

## 作者：b6e0_ (赞：5)

[题](https://www.luogu.com.cn/problem/AT4289)

数学中的染色问题，有些题目中需要分讨，比如对一个正方形染色，在确定一个点的颜色后，需要分讨与它相邻的两个点的颜色是否相同。但是，可以发现，这种情况只出现在有环的情况下。所以在树上，我们不用担心这点。

下面考虑**按照 dfs 序（即不管 dfs 序大于它的节点，dfs 序比它小的节点颜色确定后它能涂的颜色种数）**，算出每个点能涂的颜色个数，设第 $i$ 个点能涂的颜色个数为 $w_i$，根据乘法原理，最终答案就是 $\prod_{i=1}^nw_i$。考虑对于一个节点 $u$，哪些节点 $v$ 与它的距离为 $2$。
1. $v$ 是 $u$ 的儿子或者孙子节点。它们的 dfs 序明显大于 $u$，所以不考虑；
2. $v$ 是 $u$ 的父亲或爷爷。这种情况判断一下 $u$ 的深度，看它有没有爷爷，有没有爸爸即可；
3. $v$ 是 $u$ 同父亲的兄弟节点。这种情况的贡献为先进去并已经回溯上来的兄弟节点个数，即 $u$“前面”的兄弟个数。

按照上面的情况，统计即可。时间复杂度 $\mathcal O(n)$。代码：
```cpp
#include<bits/stdc++.h>
using namepace std;
const int mod=1000000007;
vector<int>g[100010];
int k;
long long a[100010];
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return x;
}
void dfs(int x,int f,int d)//d为深度
{
	int p=0,i;
	for(i=0;i<g[x].size();i++)
		if(g[x][i]!=f)
		{
			if(p)//不是第一个进去的子节点
				a[g[x][i]]=p-1;
			else
				if(!d)//判断是否有爷爷
					a[g[x][i]]=k-1;
				else
					a[g[x][i]]=k-2;
			p=a[g[x][i]];
		}
	for(i=0;i<g[x].size();i++)
		if(g[x][i]!=f)
			dfs(g[x][i],x,d+1);
}
int main()
{
	int n=read(),x,y,i;
	long long ans=1;
	k=read();
	for(i=1;i<n;i++)
	{
		x=read();
		y=read();
		g[x].push_back(y);
		g[y].push_back(x);
	}
	a[1]=k;
	dfs(1,0,0);
	for(i=1;i<=n;i++)
		if(a[i]<=0)//有颜色不够的节点直接输出0
			break;
	if(i<=n)
		puts("0");
	else
	{
		for(i=1;i<=n;i++)
			ans=ans*a[i]%mod;
		printf("%lld",ans);
	}
	return 0;
}
```

---

## 作者：LCat90 (赞：3)

我们用 $a_i$ 来表示第 $i$ 个结点它能被染的颜色数量。最终的答案就为所有 $a_i$ 的乘积。

问题就变为了：如何去求得所有的 $a_i$

对于一些拥有父子关系的结点而言，同一个父亲结点的所有儿子之间，它们的距离都为 $2$。因此，假如我们在第一个儿子 $s1$ 结点中染了 $a_{s1}$ 种颜色，那么，第二个儿子 $s2$ 结点能染得颜色 $a_{s2} = a_{s1}-1$,如果儿子越多，后面能染的颜色越少，即 $a_{sm}=a_{sm-1}-1$。问题就转变成如何求每一个父亲结点的第一个儿子节点能染的颜色，即 $a_
{s1}$ 。

而在祖先层面会对 $a_{s1}$ 产生影响的，就只有它的父亲和爷爷($s1$ 结点的子孙是会被它影响，不会影响 $a_{s1}$ 的值)。因此，就需要去查询 $s1$ 在整棵树上的深度。

- $depth_{s1}=1$，它就是根节点 $a_{s1}=k$

- $depth_{s1}=2$，它就没有爷爷  $a_{s1}=k-1$

- $depth_{s1}>=3$，它既有父亲，又有爷爷 $a_{s1}=k-2$

这样就能得到整棵树上每一个结点能染的颜色数量，全部相乘，即是答案。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int Mod = 1e9 + 7, Maxn = 1e5 + 5;
ll n, k, cnt, ans = 1;
ll head[2 * Maxn], depth[Maxn], a[Maxn];
struct node {
	ll u, v;
} temp[Maxn];
struct edge {
	ll next, to;
} e[2 * Maxn];
void dfs1(ll now, ll father) {
	depth[now] = depth[father] + 1;
	for(ll i = head[now];i != 0;i = e[i].next)
		if(e[i].to != father) dfs1(e[i].to, now);
}
void dfs2(ll now, ll father) {
	if(depth[now] == 2) a[now]--;
	else if(depth[now] >= 3) a[now] -= 2;
	ll flag = 0, last;
	for(ll i = head[now];i;i = e[i].next) {
		if(e[i].to != father) {
			if(!flag) {
				last = a[e[i].to];
				flag = 1;
				continue;
			}
			a[e[i].to] = last - 1;
			last = a[e[i].to];
		}
	}
	for(ll i = head[now];i;i = e[i].next)
		if(e[i].to != father) dfs2(e[i].to, now);
}
void add_edge(ll u, ll v) { e[++cnt].to = v, e[cnt].next = head[u], head[u] = cnt; }
int main() {
	scanf("%d %d", &n, &k);
	for(ll i = 1;i < n; ++i) scanf("%d %d", &temp[i].u, &temp[i].v), a[i] = k;
	a[n] = k;
	for(ll i = n;i >= 1; --i) {
		add_edge(temp[i].u, temp[i].v);
		add_edge(temp[i].v, temp[i].u);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	for(ll i = 1;i <= n; ++i) ans = (ans * max(a[i], 0ll)) % Mod;
	printf("%d", ans);
	return 0;
}
```

---

## 作者：洛璟 (赞：2)

## Solution:
这道题目，是一道可以用组合数做的搜索题。

至于组合数……可以去看看[我以前写的一篇题目的题解](https://www.luogu.com.cn/blog/Soviet-Molotov/solution-at5270),里面有写到如何使用费马小定理求组合数，但是这里经过优化，所以建议去学习如何求组合数再来做这道题。

我们可以先把小样例 $1$、$2$ 画出来（个人习惯以1号节点为根），然后经过一定的推理，我们发现，一个数可以选的数字的个数，只与他的父亲和爷爷节点有关而与兄弟无关。

那么一定有人要问了，兄弟节点与当前节点距离一定是二，怎么就无关了？

我们来想想，比如样例二，节点$2$、$3$、$4$均为兄弟节点，但是你会发现，无论 $2$ 号节点选什么，$3$、$4$号节点都可以随意选除去1号节点已经选了的的数字。也就是说，兄弟节点之间不是相互制约的关系，他们之间没有任何影响，无论你的兄弟选什么，你总有另外一个数字给你选，不会造成冲突。

好，那么明白了这个,我们可以再去观察一下样例二。

在1号节点选完之后，来到了 $2$、$3$、$4$ 号节点，他们三个可以选三个数，也就是  $C_{3}^{3}$ 那么结果很明显，是 $1$，显然错误。

经过观察，我们发现，这三个节点的数字可以随意互换，今天 $123$、明天$132$、后天 $213$……眼尖的同志可能已经发现了，这就是一个全排列啊。

好，那么规律也就差不多找到了，每一堆兄弟节点对答案的贡献，显然是 $C^{m}_{n} * m!$ 其中 $m$ 为所有兄弟节点个数， $n$ 为可以选的数字的个数。而 $n$ 只需要减去他的父亲节点和爷爷节点即可，也就是减去 $2$。

接下来上代码，如果对前面的内容似懂非懂，可以结合代码来理解：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p = 1000000007;
int n, k, ans = 1;
int a[1000010], son[1000010];
int nxt[1000010], ver[1000010], h[1000010], tot;
bool fg[1000010];
queue<int> q;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
inline int Pow(int base, int b)
{
    int ans = 1;
    while (b > 0)
    {
        if (b & 1 == 1)
        {
            ans = ans * base % p;
        }
        base = base * base % p;
        b = b >> 1;
    }
    return ans % p;
}
inline int qaq(int m, int n)
{
    return n < m ? 0 : ((a[n] * Pow(a[n - m], p - 2) % p) % p * Pow(a[m], p - 2) % p) % p;
}
void add(int x, int y)
{
    tot++;
    nxt[tot] = h[x];
    h[x] = tot;
    ver[tot] = y;
}
void bfs()//经典广搜遍历一整棵树
{
    while (!q.empty())
    {
        int tmp = q.front();
        q.pop();
        for (int i = h[tmp];i != 0;i = nxt[i])
        {
            int y = ver[i];
            if (fg[y] == 1) continue;
            fg[y] = 1;
            son[tmp]++;
            //记录当前正在遍历的节点的所有儿子节点
            q.push(y);
        }
        if (son[tmp] != 0)
            ans = ans * (qaq(son[tmp], k - (tmp == 1 ? 1 : 2)) % p * a[son[tmp]] % p) % p;//我们上面推出来的公式
            //对于这个三目是一个特判，显然根节点是没有父亲的，
            //所以如果在遍历根节点的儿子节点时，我们不需要减去爷爷节点
            //因此减去1就够了
    }
}
signed main()
{
    n = read();
    k = read();
    for (int i = 1;i < n;++i)
    {
        int x = read(), y = read();//加边加边加边（
        add(x, y);
        add(y, x);
    }
    a[0] = 1;
    for (int i = 1;i <= k;++i)//求组合数需要预处理阶乘
    {
        a[i] = a[i - 1] % p * i;
        a[i] = a[i] % p;
    }
    ans = k;
    q.push(1);
    fg[1] = 1;
    bfs();
    printf("%lld", ans % p);
    return 0;
}

```

---

## 作者：Sirkey (赞：0)

题目本身是一个树。

我们考虑一个点的染色的所有方案，是与他距离为 $2$ 的点的的个数，减去 $k$。

具体的是，把节点 $1$ 的方案数设为 $k$。

![图](https://cdn.luogu.com.cn/upload/image_hosting/d898r4nf.png)

由于考虑先后问题，先放入的不考虑他的弟弟和儿子。

节点一什么都没有，所以有 $k$ 种方案。

所以 $2$ 的方案数就是他的哥哥，父亲，爷爷。

显然他没有哥哥和爷爷他的方案数就有 $k-1$ 个。

关于 $3$，他有一个哥哥，同样没有爷爷，所以方案有 $k-2$ 个。

关于 $4$，他有俩个哥哥，同样没有爷爷，所以方案 $k-3$ 个。

关于 $5$，他没有哥哥，但是有爷爷和父亲，所以方案数有 $k-2$ 个。

这样就很清晰了。

父亲除了节点一都有，爷爷除了节点一的儿子都有，所以判断深度就可以做，至于哥哥，搜索的时候记一下就好。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define tell(ans) out(ans),printf("\n");
#define say(ans) out(ans),printf(" ");
#define pb push_back
//
//
//
using namespace std;
inline ll read() {
	ll f=0,t=0;
	char c=getchar();
	while(!isdigit(c)) t|=(c=='-'),c=getchar();
	while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
	return t?-f:f;
}
inline void out(ll x) {
	if(x<0) putchar('-');
	if(x>9) out(x/10);
	putchar('0'+x%10);
}
const int MX=1e6+10,mod=1e9+7;
int head[MX],to[MX],nxt[MX],top,n,k;
void LINK_(int x,int y) {
	to[++top]=y;
	nxt[top]=head[x];
	head[x]=top;
}
ll ans;
void dp(int x,int fa,int dep) {
	int s=0;
	for(int i=head[x]; i; i=nxt[i]) {
		if(to[i]!=fa) {
			s++;
			if(dep>0) ans=(ans*max(k-s-1,0))%mod;
			else ans=(ans*max(k-s,0))%mod;
			dp(to[i],x,dep+1);
		}
	}
}
int main() {
	n=read(),k=read();
	ans=k;
	FOR(i,1,n-1) {
		int a=read(),b=read();
		LINK_(a,b);
		LINK_(b,a);
	}
	dp(1,0,0);
	cout<<ans%mod;
	return 0;
}
```

订：代码中没有取模的问题。

---

## 作者：Zhao_daodao (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc133_e)

# 题目解释
给定两个数 $n$，$k$，分别代表节点的个数和颜色的个数。求合法的染色方案，使得任何两个距离不大于 $2$ 的不同节点所被染的颜色不同。$ans$ 需要对 $10^{9}+7$ 取模。

# 题目分析
### 写在前面  
本题通过 `dfs` 做，所以每一次对于节点 $k$，只考虑 $k$ 上面的节点对于 $k$ 的染色方案的影响。
在下面的分析中会出现数组：$fa_{k}$ 表示 $k$ 节点的父亲。
## 简化分析
#### 一条链
显然，第一个节点的方案数为 $k$，第二个节点的方案数为 $(k-1)$，后面的节点的染色方案为 $(k-2)$。这个链的染色方案数为：$ans=k\times (k-1)\times (k-2)^{n-2}$
#### 节点 $fa_{k}$ 第一个计算的节点
这个节点 $k$ 不用考虑 $fa_{k}$ 的其他儿子，所以方案数还是 $(k-2)$，当然，如果 $fa_{k}$ 是树的根节点，方案数即为 $(k-1)$。
#### 节点 $fa_{k}$ 然后计算的节点
~~显然，~~  $k$ 的方案数为 $(k-2-x)$，$x$ 代表在 $k$ 前面计算过的 $fa_{k}$ 的子节点。（因为与 $k$ 节点距离不大于2的节点除了 $fa_{k}$ 和 $fa_{fa_{k}}$，只有 $fa_{k}$ 的其他子节点。）
## 所以
这棵树和它的子树都可以通过类似的方法用 `dfs` 递归下去，所以本题是一道~~简简单单的~~递归题。

# 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
const int mod=1e9+7;
int n,k;
int ans=1;
int head[MAXN],tot;
struct edge{
	int to,nxt;
}e[MAXN<<1];
void edgeadd(int u,int v){
	e[++tot].nxt=head[u];
	e[tot].to=v;
	head[u]=tot;
}
int cnt[MAXN];
void dfs(int u,int fa,int sum){
	ans=(ans*max(0ll,k-sum)%mod)%mod;
	cnt[u]++;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			cnt[v]++;
			dfs(v,u,cnt[u]);
			cnt[u]++;
		}
	}
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		edgeadd(u,v);
		edgeadd(v,u);
	}
	dfs(1,0,0);
	cout<<ans;
}
```

---

## 作者：_Flame_ (赞：0)


## 思路

先想两种情况：

- 一条长为 $n$ 的链的情况，染色方案数显然为 $k\times (k-1)\times (k-2)^{n-2}$。

- 深度为 $2$ 的树且不为链的情况，对于一个根节点 $u$，设其有 $cnt$ 个儿子，则从当前根节点向下一层所带来的贡献为 $\prod\limits_{i=1}^{cnt } (k-i)$。

然后玩一下样例，发现每个图都可以拆分成这两种情况，对于一个节点 $u$，记录其儿子数量 $cnt$，若 $cnt$ 为 $1$，按链的方法处理，若不为 $1$，按第二种方法处理即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=301000;
const int maxm=110;
const int mod=1e9+7;
const int inf=1e18;

int n,k;

int ans=1;

int head[maxn],tot;
struct edge{
	int to,nxt;
}e[maxn<<1];

void add(int u,int v){
	e[++tot].nxt=head[u];
	e[tot].to=v;
	head[u]=tot;
}

int cnt[maxn];
void dfs(int u,int fa,int sum){
	ans=(ans*max(0ll,k-sum)%mod)%mod;
	cnt[u]++;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			cnt[v]++;
			dfs(v,u,cnt[u]);
			cnt[u]++;
		}
	}
}

void solve(){
	n=read(),k=read();
	for(int i=1;i<=n-1;i++){
		int u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	dfs(1,0,0);
	write(ans);
	puts("");
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}



```


---

## 作者：WRuperD (赞：0)

乱搞。

考虑对于每个点，它能染的颜色色的数量的限制是任何两个距离不大于 $2$ 的不同节点。考虑直接按 $\operatorname{dfs}$ 序顺序染色。不用考虑每个点到底染了什么颜色，显然答案至与和它距离不大于 $2$ 的不同节点已有多少个被染了色有关。直接任意钦定一种顺序跑一遍即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 1e5+10;
const int mod = 1e9 + 7;
vector <int> g[MAX];
int n, k;
bool f[MAX];
int hh[MAX];
int ans = 1;

void dfs(int u, int fa){
	int cnt = 0;
	for(int v:g[u]){
		if(f[v])	cnt += hh[v], hh[u]++;
		else{
			continue ;
		} 
	}
	f[u] = 1;
	hh[u] ++;
	ans *= k - cnt;
	ans %= mod;
	for(int v:g[u]){
		if(v == fa)	continue;
		dfs(v, u);
		hh[u]++;
	}
}

void solve(){
	n = read(), k = read();
	for(int i = 1; i < n; i++){
		int u = read(), v = read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 1);
	write(ans), endl;
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```


---

## 作者：Supor__Shoep (赞：0)

首先，我们会想到小学的数学问题。

在样例一中，构成的树其实就是一条线。对于一条线，从头部开始，每个节点可以填入的颜色方案数是 $k(k-1)(k-2)(k-2)$。

因此我们可以想到，对于一棵树，一个节点相距 $2$ 的节点其实就是相邻节点的相邻节点（除本身之外）。对于样例二，方案数就是 $k(k-1)(k-2)^2(k-3)$。如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ra4hie71.png)

根据一条线的填色方式，我们不难想到从根节点开始涂色。由于每个节点的颜色方案会受到相距 $1$ 或 $2$ 的节点的影响，在遍历一个节点的子节点时，我们可以用变量储存已经遍历子节点的个数，然后放在搜索框架中调整出方案数的值即可。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=1e9+7;
int n,m;
vector<int> v[100005],V[100005];
int ans=1;
void dfs(int x,int sum,int lx)
{
	if(!v[x].size())	return;
	ans*=(m-v[lx].size()+sum);
	ans%=MOD;
	int t=0;
	for(int i=0;i<v[x].size();i++)
	{
		if(v[x][i]!=lx)	dfs(v[x][i],t++,x);
	}
}
signed main()
{
	cin>>n>>m;
	if(n==1)
	{
		cout<<m;
		return 0;
	}
	if(n==2)
	{
		if(m==1)	cout<<"0";
		else	cout<<(m*(m-1))%MOD;
		return 0;
	}
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：dd_d (赞：0)

## Sol  
首先我们假设对于 $x$ 这个点已经染了色，我们考虑对以他为根的子树染色对答案产生的贡献。  
假设 $x$ 有 $y$ 个与他距离为 $1$ 的儿子，那么显然，这些点对答案的贡献就是 $P_{y}^{k-1}$。  
然后就是考虑对之后每一层的点算贡献。  
依旧假设这一层结点有 $y$ 个，  
那么，这一层结点对答案的贡献就是 $P_{y}^{k-2}$。    
算 $P$ 的时候可以用连乘的方式来计算，降低代码难度。  
最后一层一层往下递归就行了。  
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int mod=1e9+7;
vector<int> G[100001];
int ans,n,k;
void dfs(int x,int fa)
{
	int cnt=k-G[x].size();//cnt记录的是当前这一层能取多少种颜色
	if (cnt<=0) 
	{
		ans=0;
		return;
	}
	for (auto u:G[x])
	{
		if (u==fa) continue;
		dfs(u,x);
		(ans*=cnt)%=mod; //算P
		cnt++;
	}
}
signed main()
{
	n=read(); k=read();
	for (int i=1;i<n;i++)
	{
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	ans=k; //小细节注意
	dfs(1,0);
	writeln(ans);
}

```


---

