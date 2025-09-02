# Chemistry in Berland

## 题目描述

Igor is a post-graduate student of chemistry faculty in Berland State University (BerSU). He needs to conduct a complicated experiment to write his thesis, but laboratory of BerSU doesn't contain all the materials required for this experiment.

Fortunately, chemical laws allow material transformations (yes, chemistry in Berland differs from ours). But the rules of transformation are a bit strange.

Berland chemists are aware of $ n $ materials, numbered in the order they were discovered. Each material can be transformed into some other material (or vice versa). Formally, for each $ i $ $ (2<=i<=n) $ there exist two numbers $ x_{i} $ and $ k_{i} $ that denote a possible transformation: $ k_{i} $ kilograms of material $ x_{i} $ can be transformed into $ 1 $ kilogram of material $ i $ , and $ 1 $ kilogram of material $ i $ can be transformed into $ 1 $ kilogram of material $ x_{i} $ . Chemical processing equipment in BerSU allows only such transformation that the amount of resulting material is always an integer number of kilograms.

For each $ i $ ( $ 1<=i<=n $ ) Igor knows that the experiment requires $ a_{i} $ kilograms of material $ i $ , and the laboratory contains $ b_{i} $ kilograms of this material. Is it possible to conduct an experiment after transforming some materials (or none)?

## 样例 #1

### 输入

```
3
1 2 3
3 2 1
1 1
1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
3 2 1
1 2 3
1 1
1 2
```

### 输出

```
NO
```

# 题解

## 作者：lukelin (赞：2)

这题乍一看是一道水树形DP(其实事实上它确实是树形DP)，然后设f[i]表示第i个点所多余/需要的材料，然后我们愉快的列出了式子：
```cpp
if(f[v]<0)
	f[u] += f[v] * edges[c_e].dis;
else
	f[u] += f[v];
```
然后放到CF上，直接WA，十分自闭，于是我试图define int long long，还是没过，仔细一想(~~偷瞄了一眼CF的数据~~)，发现f数组有可能会爆long long，怎么办？~~高精~~？ 显然这不太现实，于是想着如果它要爆了就把它置回边缘，实测不会WA

贴个代码  
```cpp
#include <cstdio>
#define ll long long

const ll INF = (1ll << 62);

using namespace std;

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

struct Edge{
    int to; ll dis; int next;
} edges[2000005];

int head[2000005], edge_num = 0;

inline void addEdge(int u, int v, ll dis){
    edges[++edge_num] = (Edge){v, dis, head[u]};
    head[u] = edge_num;
}

ll a[2000005], b[2000005];
ll f[2000005];

void DFS(int u){
    //置为所需 
    f[u] = b[u] - a[u];
    for(int c_e = head[u]; c_e; c_e = edges[c_e].next){
        int v = edges[c_e].to;
        DFS(v);
        if(f[v] < 0){
            //需要 u 去补 
            if (INF / edges[c_e].dis <= -f[v])
                f[u] = -INF;
            else{
                f[u] += f[v] * edges[c_e].dis;
                if (f[u] < -INF)
                    f[u] = -INF;
            }
        }
        else{
            //反向转换 
            f[u] += f[v];
        }
    }
}

int main(){
    int n = read();
    for (int i = 1; i <= n; ++i)
        b[i] = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 2; i <= n; ++i){
        int u = read(); ll dis = read();
        addEdge(u, i, dis);
    }
    DFS(1);
    if (f[1] >= 0)
        printf("YES");
    else
        printf("NO");
    return 0;
}
```

---

## 作者：Acc_Robin (赞：1)

## CF846E Chemistry in Berland 题解

[传送门](https://codeforces.com/contest/846/problem/E)

### 题意

有 $n$ 种材料，存在 $n-1$ 个转化关系，对于 $i\ge 2$，每 $k_i$ 个 $x_i$ 可以转化为一个 $i$，每一个 $i$ 可以转化为一个 $x_i$。现在告诉你每种材料的供给/需求，问是否存在一种转化方式能满足所有材料的需求。

$n\le 10^5$

### 题解

不难看出转化关系构成了一颗以 $1$ 为根的树。

那么我们令 $f_i$​ 表示以 $i$​ 为根的子树中，**除了 $i$​** 以外其它节点都满足需求时， $i$​​​ 这里最多能屯多少材料（如果值为负就表示还需要 $|f_v|$  的材料）。

那么答案就是 $f_1$ 是否大于等于 $0$。

如何转移？考虑贪心：

儿子 $v$ 多出来的材料给父亲 $u$ 一定不会更劣，那么

- 如果 $f_v>0$，就令 $f_u\leftarrow f_u+f_v$

否则，就要让父亲去给儿子填所缺的：

- 如果 $f_v<0$​，就令 $f_u\leftarrow f_u+k_v\cdot f_v$​（注意这里 $f_v$ 是负数，所以直接加就可以）

按照上述转移即可，注意节点 $i$ 的 $f_i$ 初始等于$\text{供给}-\text{需求}$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	const int N=1e5+9;
	struct T{int v,w;};
	basic_string<T>G[N];
	long long a[N],b[N];
	long double f[N];
	void dfs(int u){
		f[u]=b[u]-a[u];
		for(auto[v,w]:G[u])if(dfs(v),f[v]>=0)f[u]+=f[v];else f[u]+=w*f[v];
	}		
	void work(){
		int n,i,x,y;
		for(cin>>n,i=1;i<=n;++i)cin>>b[i];
		for(i=1;i<=n;++i)cin>>a[i];
		for(i=2;i<=n;++i)cin>>x>>y,G[x]+={i,y};
		dfs(1),puts(f[1]>=0?"YES":"NO");
	}
}
int main(){return Acc::work(),0;}
```

### 小细节

在运算过程中会炸出 `long long`，所以要么设置一个阈值，要么使用 `long double`。



---

## 作者：chenxia25 (赞：1)

这也是一个热身题（

显然建出来一棵树。我们考虑树形 DP，$dp_i$ 表示子树 $i$ 除了 $i$ 都合法的时候，$i$ 的最大储存量。转移就扫一遍儿子们，少了的就补，多了的就补上去，就这么简单。

但是这题难点不在这里，而在 DP 值可能很大很大。这时候我们要想各种解决措施。一是设一个无穷小值，超过这个值就直接判为不可能。另一个就是 `long double`，因为太大的时候不太需要精度。

---

## 作者：TG_Space_Station (赞：0)

# 思路
本题目容易看出是一个树形结构，再看一眼又很 dp。所以我们考虑树形 dp。

树形 dp 的基本状态是 $dp_u$，即以 $u$ 为根的子树中的某种信息。本体似乎并不需要多余的空间维度。  
接下来我们考虑里面存储什么信息。我们会想到存可行与否，但这根本无法转移。再加思考，我们似乎可以存一种更为详细的“可行与否”——除根以外的点都满足条件时根最多可以**留下**多少材料供祖先使用（正数表示有余可向祖先交税，负数表示不足需祖先补贴，$0$ 则表示刚好满足要求）。最终答案即为 $dp_1$ 的正负性。

转移就很简单了：$dp_u = \sum (dp_v \times w)[dp_v < 0] + (dp_v)[dp_v \ge 0]$。  
# Code
```
#include<bits/stdc++.h>
using namespace std;

const long long N = 1e5 + 5;
long double dp[N];
long long n, a[N], b[N];
vector < pair<long long, long long> > edge[N];

void dfs(long long u)
{
	long long i;
	dp[u] = b[u] - a[u];
	
	for(i = 0; i < edge[u].size(); i++)
	{
		long long v = edge[u][i].first;
		long long w = edge[u][i].second;
		dfs(v);
		
		if(dp[v] >= 0)
			dp[u] += dp[v];
		else
			dp[u] += w * dp[v];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	long long i, u, v;
	cin >> n;
	
	for(i = 1; i <= n; i++)
		cin >> b[i];
	for(i = 1; i <= n; i++)
		cin >> a[i];
	
	for(i = 2; i <= n; i++)
	{
		cin >> u >> v;
		edge[u].push_back(make_pair(i, v));
	}
	
	dfs(1);
	cout << (dp[1] >= 0 ? "YES" : "NO");
	return 0;
}
```

---

## 作者：Erusel (赞：0)

你会发现这是一道简单的树形 $\text{dp}$

自底向上 $\text{dfs}$ 即可

柿子也很简单:

```cpp
if(a[v]<0) a[u]+=a[v]*w
else a[u]+=a[v]
```

然后你会发现这会炸 $\text{long long}$，于是我们设定一个 $\text{inf}$

如果炸了就把它变成最小值，其他没有什么注意点了

**Code:**

```cpp
void dfs(int u)
{
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i].v,w=e[u][i].w;dfs(v);
		if(a[v]<0)
		{
            if(inf/w<=-a[v])a[u]=-inf;
            else a[u]+=a[v]*w,a[u]=max(a[u],-inf);
		}
		else a[u]+=a[v];
	}
}
```



---

## 作者：龙啸空 (赞：0)

这是一道树形DP

~~【但是不知道为什么老师说是树上差分】【小声BB】~~

做法很简单，维护一个dp[i]表示当前值与目标值差距

在对i结点dfs过后：

如果dp[i]是负的，并且绝对值在（1e7/转换率）以内，就向i的父亲借

如果dp[i]是负的，并且绝对值在（1e7/转换率）以外，直接将i的父亲设为负无穷

因为你再怎么借也借不过

（节点个数*节点最大值/转换率）= 1e7

这么多

如果经过上述操作dp[i]还大于0，就把他丢给i的父亲

因为i也用不上，i的父亲可能不够，要向自己的儿子结点借，还不如直接给父亲用

最后看一下dp[1]是否大于0就好了（自己被N-1个结点借过后自己还够不够）

上代码：





```cpp
#include<cstdio>
#include<cstring>
#define LIMIT 1e17
long long head[200005],v[200005*2],nxt[200005*2],tot=1,w[200005],sub[200005],c[200005],d[200005],fa[200005],dp[200005],N;
bool vis[200005],ok;
void addedge(long long U,long long V,long long W){
	v[++tot]=V;
	nxt[tot]=head[U];
	w[tot]=W;
	head[U]=tot;
}
void dfs(long long x)
{
	vis[x]=true;
    dp[x]=c[x]-d[x];
    for(int i=head[x];i;i=nxt[i])
    {
        dfs(v[i]);
        if(dp[v[i]]<0)
        {
            if(-dp[v[i]]<LIMIT/w[i])
                dp[x]+=dp[v[i]]*w[i];
            else dp[x]=-LIMIT;
            if(dp[x]<-LIMIT)
                dp[x]=-LIMIT;
        }
        else dp[x]+=dp[v[i]];
    }
}
int main(){
	fa[1]=0;
	tot=1;
	ok=true;
	scanf("%lld",&N);
	long long x,k;
	for(int i=1;i<=N;i++){
		scanf("%lld",&c[i]);
	}
	for(int i=1;i<=N;i++){
		scanf("%lld",&d[i]);
	}
	for(int i=2;i<=N;i++){
		scanf("%lld%lld",&x,&k);
 		addedge(x,i,k);
	}
	dfs(1);
	if(dp[1]>=0) printf("YES\n");
	else printf("NO\n");
}
```

完结撒小fafa~~~

---

## 作者：泠小毒 (赞：0)

# Chemistry in Berland
给定2个长度为n的序列a,b，表示当前的材料数量和目标材料数量

给出n-1组转换关系，Xi,Ki，表示Ki个Xi可以转换为1个i且1个i可以转换为1个Xi

求是否能满足需求
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190514/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190514.html)
## 解法
首先处理一下序列a,b，让a[i]-=b[i]，目标就是使a序列变成非负序列

把转换关系看成代价为k的从x到i的边，然后就可以跑dfs了QAQ

对于一个点，跑完了它的所有儿子之后，如果它已经满足，把多的给它爸

如果它不满足，就看它爸能不能转给他

优先转给它的一定是它儿子，因为它儿子转给它是1比1，它爸转给它是k比1

如果他爸不能转给它，就炸了QWQ

~~tips:乘起来会爆long long（大雾~~
## ac代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 23333333333333333
using namespace std;
struct node{ll to,next,w;}e[100010];
ll n,cnt=0,x,y,a[100010],head[100010];
double tmp;
void add(ll i){e[++cnt]={i,head[x],y},head[x]=cnt;}
void dfs(ll u,ll f,ll k)
{
	for(ll i=head[u];i;i=e[i].next)dfs(e[i].to,u,e[i].w);
	if(a[u]>=0)a[f]+=a[u];
	else
	{
		tmp=double(k)*double(a[u]);
		if(!f||tmp<-inf)puts("NO"),exit(0);
		a[f]+=k*a[u];
		if(a[f]<-inf)puts("NO"),exit(0);
	}
}
int main()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(ll i=1;i<=n;i++)scanf("%lld",&x),a[i]-=x;
	for(ll i=2;i<=n;i++)scanf("%lld%lld",&x,&y),add(i);
	dfs(1,0,0),puts("YES");
	return 0;
}
```

---

