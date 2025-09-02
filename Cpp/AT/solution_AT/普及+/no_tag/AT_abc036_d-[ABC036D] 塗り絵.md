# [ABC036D] 塗り絵

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc036/tasks/abc036_d



# 题解

## 作者：MinimumSpanningTree (赞：6)

[题目链接](https://www.luogu.com.cn/problem/AT_abc036_d)

由于是树上问题，又是方案数，可以想到树形 dp。

设 $dp_{1,i}$ 表示对结点 $i$ 为根的子树染色，$i$ 为黑色的方案数，$dp_{2,i}$ 则表示 $i$ 为白色的方案数。

题目中的染色限制是相邻点，所以 dp 转移方程是子推父。白色没有限制，黑色的限制是相邻点不能都是黑。所以父节点是白色时，子节点可以是黑色也可以是白色。父节点是黑色时，子节点只能是白色，再根据加乘原理，可以推出转移方程：

$$
dp_{1,u}=\prod dp_{2,v}
$$

$$
dp_{2,u}=\prod dp_{1,v}+dp_{2,v}
$$

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll MOD=1000000007;
const int N=1e5+100;
int n,u,v,t[N],k;
ll dp[5][N],ans;
struct node
{
	int id,last;
}a[N*2];
void add(int a1,int a2)
{
	a[++k].id=a2;
	a[k].last=t[a1];
	t[a1]=k;
}
void dfs(int x,int fa)
{
	dp[1][x]=dp[2][x]=1;
	for(int i=t[x];i;i=a[i].last)
	{
		if(a[i].id==fa) continue;
		dfs(a[i].id,x);
		dp[1][x]=(dp[1][x]*dp[2][a[i].id])%MOD;
		dp[2][x]=(dp[2][x]*((dp[1][a[i].id]+dp[2][a[i].id])%MOD))%MOD;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	dfs(1,0);
	ans=(dp[1][1]+dp[2][1])%MOD;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Dreamer_xbt910 (赞：4)

# 题意

有一棵由 $N$ 个点 $N-1$ 条边构成的树，求出树上每个点染成白色或黑色，但相邻两个点不能同时染成黑色的染色方案数量，并取模 $10^9+7$。

# 思路

对于这种求合法方案数的题目，一般可以考虑 $dp$ 。设 $dp_{i,1}$ 表示第 $i$ 个节点为染成黑色的方案数。设 $dp_{i,0}$ 表示第 $i$ 个节点为染成白色的方案数。

再利用乘法原理，可得出动态转移方程。
$$dp_{i,1} \gets dp_{i,1} \times dp_{j,0},$$
$$dp_{i,0} \gets dp_{i,0} \times (dp_{j,0}+dp_{j,1}).$$
然后输出 $dp_{1,1}+dp_{1,0}$ 即可。

记得取模！！！
# code

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=100005;
int n,u,v,dp[N][5],tot=1,head[N];
struct op
{
	int to,next;
}arr[N<<1];
void edge(int x,int y){
	arr[tot].to=y;
	arr[tot].next=head[x];
	head[x]=tot++;
}
void dfs(int x,int fa){
	dp[x][0]=1,dp[x][1]=1;//初始化
	for(int i=head[x];i;i=arr[i].next){
		int y=arr[i].to;
		if(fa==y)continue;
		dfs(y,x);
		dp[x][0]*=dp[y][0]+dp[y][1];//动态转移方程
		dp[x][1]*=dp[y][0];//动态转移方程
		dp[x][1]%=mod;
		dp[x][0]%=mod;
	}
}
signed main(){
    scanf("%lld",&n);
	for(int i=1;i<n;i++){
        scanf("%lld%lld",&u,&v);
		edge(u,v),edge(v,u);//建边
	}//输入
	dfs(1,0);
    printf("%lld\n",(dp[1][0]+dp[1][1])%mod);//输出
	return 0;
} 
```

---

## 作者：Rannio (赞：3)

### 题意
题面讲挺清楚的就不简化了。

### 思路
树上求方案数，很明显是树上 `dp`。

设 $dp_{i,0/1}$ 表示第 $i$ 个点涂成白/黑色的方案数。 

当前结点如果为白色，那么它的子节点涂成什么颜色都没关系，根据分步乘法原理，将它子结点涂成白/黑色的方案数之和乘起来即可；当前结点如果为黑色，那么它的子节点只能涂成白色，根据分步乘法原理，将它子结点涂成白色的方案数乘起来即可。如果 $i$ 是叶子结点，那么 $dp_{i,0}=dp_{i,1}=1$。

形式化的讲：
- $dp_{i,0}=\prod dp_{j,0}+dp_{j,1}$
- $dp_{i,1}=\prod dp_{j,0}$  

其中 $j$ 表示 $i$ 的一个子结点。  
记得取模。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m;
int head[200005],cnt=1;
int dp[100005][2];
int ans;
struct node{
    int to,next;
}edge[200005];
void add(int x,int y){
    edge[cnt].to=y;
    edge[cnt].next=head[x];
    head[x]=cnt++;
}
void dfs(int x,int fa){
    int num=0;
    dp[x][0]=1;
    dp[x][1]=1;
    for(int i=head[x];i;i=edge[i].next){
        int u=edge[i].to;
        if(u==fa) continue;
        num++;
        dfs(u,x);
        dp[x][0]*=(dp[u][0]+dp[u][1])%mod;
        dp[x][0]%=mod;
        dp[x][1]*=dp[u][0];
        dp[x][1]%=mod;
    }
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%lld%lld",&x,&y);
        add(x,y);
        add(y,x);
    }
    dfs(1,0);
    printf("%lld",(dp[1][0]+dp[1][1])%mod);
    return 0;
}
```

---

## 作者：湖南省队御用绫厨TM_Sharweek (赞：2)

~~到底是谁在做这些题的翻译怎么输入输出格式都不给一下。~~

## 题意简述

给出一棵无根树，你可以对一个点选择染或者不染，不能有两个相邻节点都染色。求总的方案数。

### 输入格式：
先输入一个数 $n$，表示这棵树上所有点的总个数。

第 $2$ 至 $n$ 行，一行两个整数 $u$ 和 $v$，表示这两个点之间有连边。

### 输出格式：
输出一行一个整数，表示总方案数对 $10^9+7$ 取模后得到的答案。

## 思路分析
这种奇奇怪怪数数题大概率是计数 DP 了，所以往树形计数 DP 的方向思考。

我们先构造一个十分无脑的状态：$f_u$ 表示以 $u$ 为根的子树的方案数。但是这个状态的转移也太难想了（或者说根本就不存在），所以我们考虑加一点状态。我们需要增加一个状态便于我们利用不能有相邻两个节点都染色这个性质转移。我们发现如果知道了一个节点 $u$ 的所有儿子的子树的答案，我们只需要知道这些儿子的染色情况和 $u$ 的染色情况就能非常方便的转移了。因为一个儿子的子树中所有节点到另一个儿子的子树中任意节点的路径都一定会经过 $u$，所以根本不可能相邻。因此我们再添加一个状态 $j$，$f_{u,j}$ 表示 $u$ 的子树中 $u$ 染色（$j=1$）/不染色（$j=0$）的合法方案数即可。

给出这个状态后，推出转移方程是十分简单的。因为每棵子树都是相对独立的，可以看作是把 $u$ 的子树染色的几个步骤（先染某一个儿子的子树，有多少种方案；再染另一个儿子的子树，有多少种方案；……），所以根据乘法原理，就有 $f_{u,1}=\prod_{v\in son_u}f_{v,0},f_{u,0}=\prod_{v\in son_u}(f_{v,1}+f_{v,0})$（$son_u$ 表示 $u$ 的儿子集合）。为什么后面那个式子中是 $f_{v,1}+f_{v,0}$ 呢？因为这是将这棵子树染色的两类方式（你总不能先把它染成一个颜色再把它染成另一个颜色吧！），所以要使用加法原理。边界条件是 $f_{u,1}=f_{u,0}$，其中 $u$ 是叶子结点。因为乘法的单位元是 $1$，所以初始时把所有 $f_{u,1}$ 和 $f_{u,0}$ 都赋值为 $1$ 即可。答案就是 $f_{root,1}+f_{root,0}$（$root$ 是根节点）。

## 代码

以下是我的 C++ 代码

```cpp
/*********************************************************************
    程序名:
    版权:
    作者:
    日期: 2024-11-20 21:43
    说明:
*********************************************************************/
#include <bits/stdc++.h>

#define m_p make_pair
#define p_b push_back
#define fst first
#define sec second

#define p_q priority_queue
#define u_map unordered_map

using namespace std;

using ll = long long;
using ull = unsigned long long;
using i128 = __int128;

const int N = 1e5 + 50;
const ll P = 1e9 + 7;

vector<int> g[N];
ll f[N][2];

void dfs(int u, int fa) {
	f[u][1] = f[u][0] = 1;
	for (int v : g[u]) {
		if (v == fa) {
			continue;
		}
		dfs(v, u);
		f[u][1] = (f[u][1] * f[v][0]) % P;
		f[u][0] = (f[u][0] * (f[v][1] + f[v][0])) % P;
	}
}

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].p_b(v);
		g[v].p_b(u);
	}
	dfs(1, 0);
	cout << (f[1][1] + f[1][0]) % P << endl;

	return 1007120412;
}

``````

---

## 作者：iamajcer (赞：2)

# 思路

这题一看就是树形 dp。

考虑记 $f_{i,0/1}$，表示以 $i$ 节点为子树时，$i$ 节点染（$0$ 黑 $1$ 白）时染色方案总数。

转移就很好搞了。根据题意即可，假设 $v$ 是 $u$ 的孩子，$u$ 染黑，由于不能染相邻的黑色，所以 $v$ 只能染白。反之，$u$ 染白，$v$ 可黑可白。

$f_{u,0} = f_{u,0} \times f_{v,1}$

$f_{u,1} = f_{u,1} \times (f_{v,1}+f_{v,0})$

注意一下，因为这里是求方案总数，肯定是乘法原理。

也就是两棵子树的选择方法不单单相加，他俩有一处染色不同即可，也就是乘法原理。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5, Mod=1000000007;

int n, u1, v1, root=0, rd[N];
vector<int> a[N];
long long f[N][5];
void dfs(int u, int fa)
{
	f[u][0]=f[u][1]=1;
	for (int i=0; i<a[u].size(); i++)
	{
		int v=a[u][i];
		if (v==fa) continue;
		
		dfs(v, u);
		f[u][0]=(f[u][0]*f[v][1])%Mod;
		f[u][1]=(f[u][1]*(f[v][1]+f[v][0]))%Mod;
	}
}
int main()
{
	scanf("%d", &n);
	for (int i=1; i<n; i++)
	{
		scanf("%d%d", &u1, &v1);
		a[u1].push_back(v1);
		a[v1].push_back(u1);
		
		rd[v1]++;
	}
	for (int i=1; i<=n; i++)
		if (!rd[i])
		{
			root=i;
			break;
		}
	dfs(root, -1);
	
	printf("%lld", (f[root][0]+f[root][1])%Mod);
	return 0; 
} 
```

---

## 作者：AlanFong (赞：2)

## 写在前面

模拟赛上的一道裸树形 DP 题，直接切了。

## 思路

首先定义状态。\
$dp_{x}$ 表示当根结点为 $x$ 时的状态。\
要分成两种：\
$dp_{x,0}$ 表示染成白色；\
$dp_{x,1}$ 表示染成黑色。\
设 $x$ 的子节点为 $y$。\
据乘法原理可知：

$$dp_{x,0}=\prod dp_{y,0}+dp_{y,1}$$

当 $x$ 染成白色时，$y$ 可以染成任意颜色。


$$dp_{x,1}=\prod dp_{y,0}$$

当 $x$ 染成黑色时，$y$ 仅能染成白色。

## 注意事项

- 开 `long long`。

- 记得要模。

## 代码

```
#include<bits/stdc++.h>
#define int long long // int 宏定义为 long long
using namespace std;
int dp[100005][3],n,head[100005],nxt[200005],to[200005],cnt; // 0 表示白， 1 表示黑
const int mod=1e9+7; //模数
void add(int u,int v) //链式前向星加边
{
    cnt++;
    to[cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void dfs(int x,int fa) //树状 dp
{
    dp[x][0]=1;
    dp[x][1]=1;
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if(y==fa)
        {
            continue;
        }
        dfs(y,x);
        dp[x][0]=dp[x][0]*(dp[y][1]+dp[y][0])%mod;
        dp[x][1]=dp[x][1]*dp[y][0]%mod;
    }
}
signed main() //定义了 int，需要用 signed main
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);//加双向边
    }
    dfs(1,0);
    cout<<(dp[1][1]+dp[1][0])%mod<<endl; //两种颜色方案数之和
    return 0;
}
```

---

## 作者：iamjcer (赞：1)

# 思路
我们考虑用树形 dp。

我们可以令 $f_{i,1/0}$ 表示以 $i$ 为根的子树中，$i$ 结点染色或不染色时的方案总数。

根据题意，相邻两个点不能都涂成黑色，所以如果 $i$ 结点染成黑色，那么 $i$ 的子节点只能染成白色。反之，$i$ 结点染成白色，那么 $i$ 结点的子节点可以染白色也可以染黑色。所以，我们令 $j$ 是 $i$ 的子节点，那么转移方程如下：

$f_{i,0}=f_{i,0} \times f_{j,1}$
  
$f_{i,1}=f_{i,1} \times (f_{j,1}+f_{j,0})$

需要注意，因为需要算方案总数，所以我们要通过乘法原理把每个子节点的贡献乘起来。

# Code

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
#define N 100005
using namespace std;
int dp[N][8],n,in[N],root=0;
vector<int> v[N];
void dfs(int x,int father){
	dp[x][0]=dp[x][1]=1;
	for(int i=0;i<v[x].size();i++){
		int son=v[x][i];
        if(son==father) continue;
		dfs(son,x);
        
		dp[x][1]=(dp[x][1]*(dp[son][1]+dp[son][0]))%mod;
		dp[x][0]=(dp[x][0]*dp[son][1])%mod;
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%lld %lld",&x,&y);
		v[x].push_back(y);
        v[y].push_back(x);
		in[y]++;
	}
	for(int i=1;i<=n;i++){
		if(!in[i]){
			root=i;
			break; 
		}
	}
	dfs(root,-1);
	printf("%lld",(dp[root][1]+dp[root][0])%mod);
	return 0;
}
```

---

## 作者：Swirl (赞：1)

此题解是本人第一篇题解，若有不对请海涵。

# 思路简述
**本题是一道基础树形 ``Dp``。**

定义 $Dp_{i,0}$ 代表第 $i$ 个节点涂白色的方案数；

同理  $Dp_{i,1}$ 代表第 $i$ 个节点涂黑色的方案数。

接着是状态转移方程。

首先我们所采用的遍历树的方法是后序遍历，这很好理解；

接着根据题意可以知道 $Dp_{i,0}$ 由 $Dp_{j,0}$ 和 $Dp_{j,1}$ 转移而来，其中 $j$ 是 $i$ 的子节点；

进一步推出 $Dp_{i,1}$ 仅由 $Dp_{j,0}$ 转移而来。

更进一步的，用乘法原理可以得到状态转移方程为：
$$
Dp_{i,0}=\prod_{j\in Edge_i}Dp_{j,1}+Dp_{j,0}
$$
$$
Dp_{i,1}=\prod_{j\in Edge_i}Dp_{j,0}
$$

其中 $Edge_i$ 表示 $i$ 的子节点。

思路部分结束。

# 代码与易错点

先放代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define Mod 1000000007
using namespace std;

ll a[100005];
ll Dp[100005][2];
ll n;
vector<ll> Edge[100005];

void dfs(ll fa, ll step) { //树形Dp
	Dp[step][1] = Dp[step][0] = 1;
	for (auto x : Edge[step]) {
		if (x == fa) continue; //切记不可删
		dfs (step, x);
		Dp[step][0] = (Dp[step][0] * (Dp[x][1] + Dp[x][0]) % Mod) % Mod; //状态转移
		Dp[step][1] = (Dp[step][1] * Dp[x][0]) % Mod;
	}
}

int main() {
	cin >> n;
	for (ll i = 1; i < n; i++) {
		ll fa, son;
		cin >> fa >> son;
		Edge[fa].push_back(son); //双向建树
		Edge[son].push_back(fa);
	}
	dfs(0, 1);
	cout << (Dp[1][1] + Dp[1][0]) % Mod; //一定要模
	return 0;
}
```
## 易错点
1. 忘开 $long~long$。
2. 忘取模。
3. 输出成 `(Dp[n][1] + Dp[n][0]) % Mod` (本人在这里卡了好久...)。
4. 忘记双向建树。

---

## 作者：hjqhs (赞：1)

### 一道简单的树形 dp。
不会树形 dp 的出门左转[没有上司的舞会](https://www.luogu.com.cn/problem/P1352)。  

设 $dp_{i,0}$ 为第 $i$ 个结点染成白色的方案数。  
设 $dp_{i,1}$ 为第 $i$ 个结点染成黑色的方案数。  
答案为 $dp_{i,0}+dp_{i,1}$。  
考虑如何转移。  
对于结点 $u$，当 $u$ 染成白色时，子节点可以染成白色或黑色，用乘法原理乘起来，即 $dp_{u,0}=\prod{(dp_{v,0}+dp_{v,1})}$($v$ 是 $u$ 的子结点)。当 $u$ 染成黑色时，子节点只能染成白色，用乘法原理乘起来，即 $dp_{u,1}=\prod{(dp_{v,0})}$($v$ 是 $u$ 的子结点)。   
注意要开 ```long long```，中间要取模。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=100005;
const int mod=1000000007;
vector<int>tree[MAXN];
int n,ans,dp[MAXN][2];
void dfs(int u,int fa){
	dp[u][0]=dp[u][1]=1;
	for(int i=0;i<tree[u].size();++i){
		int v=tree[u][i];
		if(v!=fa){
			dfs(v,u);
			dp[u][0]*=(dp[v][0]+dp[v][1]);
			dp[u][0]%=mod;
			dp[u][1]*=dp[v][0];
			dp[u][1]%=mod;
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;++i){
		int a,b;
		cin>>a>>b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	dfs(1,0);
	ans=(dp[1][0]+=dp[1][1])%mod;
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：csh0908 (赞：0)

## 题意
很清晰了不多加解释。


## 思路
这里是树上操作，并且求的是方案数，很容易就让人想到了树形 dp ，我们可以遍历整一棵树，由叶子节点开始返回时，以子推父的方式记录方案数。当现在的节点为黑色时，那么子节点只能是白色，当前节点是白色时，子节点可以是黑色或白色。由于是求方案数，一步一步这样乘上来，所以用的是乘法原理。我们用 $1$ 表示黑色，$0$ 表示白色，不难推出状态转移方程为：

$$dp(u,0)=\prod dp(v,0) +dp(v,1)$$

$$dp(u,1)=\prod dp(v,0)$$

## 注意事项
记得开 longlong 以及取模。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int mod=1000000007;
int n,x,y;
long long dp[N][2];
vector<int>a[N];
void dfs(int u,int fa)
{
	for(int i=0;i<a[u].size();i++)
	{
		int v=a[u][i];
		if(v==fa)continue;
		dfs(v,u);
		dp[u][0]=dp[u][0]%mod*((dp[v][0]+dp[v][1])%mod)%mod;//当前节点为白色
		dp[u][1]=dp[u][1]%mod*dp[v][0]%mod;//当前节点为黑色
//		cout<<dp[u][0]<<" "<<dp[u][1]<<"\n";
	}
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
    	scanf("%d%d",&x,&y);
    	a[x].push_back(y);
    	a[y].push_back(x);
    }
    for(int i=1;i<=n;i++)
    	dp[i][0]=dp[i][1]=1;
    dfs(1,1);
    cout<<(dp[1][0]%mod+dp[1][1]%mod)%mod;
    return 0;
}
```

---

## 作者：Antiluna (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc036_d)

快掉绿了，水一发题解。

刚开始把树看成图了，导致浪费了 10 min。

但是是树，所以就是一个很简单的树形 dp 了。

类似[没有上司的舞会](https://www.luogu.com.cn/problem/P1352)，考虑 $f_{i,0}$ 表示以 $i$ 为根的子树 $i$ 染成黑色时的合法染色方案数，$f_{i,1}$ 则表示白色。

根据乘法原理有 ：

$f_{u,0}=\prod f_{v,1}$

$f_{u,1}=\prod f_{v,0}+f_{v,1}$

初始化 $f_{i,0}=f_{i,1}=1$。

注意取模。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,first[100010],ct,mod=1000000007;
long long f[100010][2];
struct node
{
	int to,next;
}tr[200010];
void add(int x,int y)
{
	tr[++ct].to=y;
	tr[ct].next=first[x];
	first[x]=ct;
}
void dfs(int u,int fa)
{
	f[u][0]=f[u][1]=1;
	for(int i=first[u];i;i=tr[i].next)
	{
		int v=tr[i].to;
		if(v==fa)continue;
		dfs(v,u);
		f[u][0]=(f[u][0]*f[v][1])%mod;
		f[u][1]=f[u][1]*((f[v][1]+f[v][0])%mod)%mod;
	}
}
signed main()
{
	scanf("%d",bitand n);
	for(int i=1;i<n;i++)scanf("%d %d",bitand x,bitand y),add(x,y),add(y,x);
	dfs(1,0);
	printf("%lld",(f[1][1]+f[1][0])%mod);
	return 0;
}
```

---

## 作者：Gapple (赞：0)

比较板子的树形 DP。

我们设 $f_{u, 0}$ 为节点 $u$ 染上白色的方案数，$f_{u, 1}$ 为节点 $u$ 染上黑色的方案数，$S(u)$ 为节点 $u$ 的子树。

容易发现：

$$
\begin{aligned}
  f_{u, 0} &\equiv \prod_{v \in S(u)} (f_{v, 0} + f_{v, 1}) \pmod{10^9 + 7} \\
  f_{u, 1} &\equiv \prod_{v \in S(u)} f_{v, 0} \pmod{10^9 + 7}
\end{aligned}
$$

设根为 $u$，则答案为 $f_{u, 0} + f_{u, 1}$。

---

## 作者：YuYuanPQ (赞：0)

Update on 2024.6.20:

- 语言更简练。
- 修改了状态转移方程中的笔误。
- 删除了 `align`，解决了部分 LaTeX 公式仅能在详情页显示的问题。

------------

Update on 2024.7.24:

- 修改了状态转移方程中的又一处笔误。

感谢 [InversionShadow](https://www.luogu.com.cn/user/672281) 的反馈。

------------

我没场切纯属唐氏。（乘法打成了加法）

简单树形 DP。

设 $dp_{x,0}$ 表示把编号为 $x$ 的点染成黑色和白色的方案数。

从题目中容易得出：

- 黑点：由与它相连的白点转移过来。

- 白点：由与它相连的黑点和白点转移过来。

状态转移方程：

$$
dp_{x,0}=\prod_{y\in edge[x]}dp_{y,1}\\
dp_{x,1}=\prod_{y\in edge[x]}dp_{y,0}+dp_{y,1}
$$

[双倍经验](https://www.luogu.com.cn/problem/AT_dp_p)

## Code

[Link](https://atcoder.jp/contests/abc036/submissions/53477396)

---

## 作者：InversionShadow (赞：0)

令 $dp_{i,0/1}$ 表示第 $i$ 个结点染黑色或者白色。

令当前搜索的结点为 $u$，它的子节点为 $v$。显然有：

$$f_{u,0}=\prod f_{v,1}\\f_{u,1}=\prod (f_{v,0}+f_{u,1})$$

什么意思呢？因为不能让两个结点同时染黑，所以 $f_{u,0}$ 只能从 $f_{v,1}$ 转移过来。反之就是一黑一白或者两白，转移即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std; 

const int N = 1e5 + 100;
const int mod = 1e9 + 7;

int n, head[N], tot, f[N][2];

struct Node {
	int to, nxt;
} e[N << 1];

void add(int u, int v) {
	e[++tot] = {v, head[u]};
	head[u] = tot;
}

void dfs(int u, int fa) {
	f[u][0] = f[u][1] = 1;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fa) continue;
		dfs(v, u);
		(f[u][0] *= f[v][1]) %= mod;
		(f[u][1] *= (f[v][0] + f[v][1])) %= mod;
	}
}

signed main() {
	cin >> n;
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	cout << (f[1][0] + f[1][1]) % mod << '\n';
	return 0;
}

```

---

## 作者：Floating_Trees (赞：0)

### 题意
有一个 $n$ 个点 $n-1$ 条边的树，第 $a_i$ 和 $b_i$ 之间有一条无向边，每个点都可以染成黑色或者白色，但如果有相邻的一个点是黑色的，那就不能染成黑色了，问最终有多少种染色的方法，并把答案模 $10^9+7$。

### 思路
很显然是一道树形 DP。状态转移方程也很明显，如果染成白色，那么儿子们就可以染成黑色或者白色，如果染成黑色，那儿子们就只能染成白色了，那么当前这个点的子树的染色方案数就只需按上面所说的相乘即可。

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 100010, mod = 1000000007;
int n,dp[2][N]; // dp[0][i]表示节点i染成白色的方案数，dp[1][i]表示节点i染成黑色的方案数 
vector<int> v[N];

void dfs(int k, int fa)
{
	dp[0][k] = 1, dp[1][k] = 1; // 初始化每个点的方案数 
	for (auto i : v[k])
	{
		if (i == fa)
			continue; // 不访问这个点的父亲节点 
		dfs(i,k); // 先把儿子的方案数算出来 
		dp[0][k] = (1ll * dp[0][k] * (dp[0][i] + dp[1][i])) % mod;
		dp[1][k] = (1ll * dp[1][k] * dp[0][i]) % mod;
	}
}

int main()
{
	scanf ("%d",&n);
	int a,b;
	for (int i = 1;i < n;i++)
		scanf ("%d%d",&a,&b), v[a].push_back(b), v[b].push_back(a);
	dfs(1,0); // 1没有父亲节点，那么就传入一个不在图里面的点 
	printf ("%d",(dp[0][1] + dp[1][1]) % mod); // 节点1既可以染白色也可以染黑色 
	
	return 0;
}
```

---

## 作者：Bulyly (赞：0)

### 解析
- 非常经典的一道树形 DP 模板，和主题库的一些题很像。思路很简单，用 $dp[i][0/1]$ 表示节点 $u$ 被涂成白色或黑色的方案数。

- 状态转移思路，这个也很好想，运用乘法原理，如果该点染黑色就去累乘所有子节点染白色的方案数，如果该点染白色那就累成所有子节点为白色或黑色的方案数总和。

注意：累乘时会爆 int 所以应该用 long long。

下附代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
#include <vector>
using namespace std;
const int N=1105222,Mod=1e9+7;
int n,u,v;
vector<int> e[N];
int f[N][2];

void dfs(int u,int fa)
{
	f[u][0]=1,f[u][1]=1;
	for(int i=0;i<e[u].size();i++)
	{
		int j=e[u][i];
		if(j==fa)  continue;
		dfs(j,u);
		f[u][1]=(f[u][1]*f[j][0])%Mod;
		f[u][0]*=f[u][0]*(f[j][0]+f[j][1])%Mod;
	}
}

signed main()
{
	
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	int ans=(f[1][0]+f[1][1])%Mod;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Buried_Dream (赞：0)

树形 dp。


设 $dp_{u,0/1}$ 表示 $u$ 这个节点涂成白色/黑色的方案数。

因为相邻的两个点不能同时是黑色。

所以有转移式：

$$dp_{u,1}=dp_{u,1} \times dp_{v,0}$$

$$dp_{u,0}=dp_{u,0}\times (dp_{v,0}+ dp_{v,1})$$

注意开 long long。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;
#define int ll
typedef long long ll;
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const int Mod = 1e9 + 7;

inline int read() {
    int res = 0, f = 0; char ch = getchar();
    for(; !isdigit(ch); ch = getchar()) f |= (ch == '-');
    for(; isdigit(ch); ch = getchar()) res = (res << 1) + (res << 3) + (ch - '0');
    return f ? - res : res;
}

int n, dp[N][3];
std::vector <int> E[N];

void dfs(int u, int fa) {
	dp[u][0] = dp[u][1] = 1;
	for(int v : E[u]) {
		if(v == fa) continue;
		dfs(v, u);
		dp[u][1] = (dp[u][1] * dp[v][0]) % Mod;
		dp[u][0] = dp[u][0] * (dp[v][1] + dp[v][0]) % Mod;
	}	
}

signed main() {
	n = read();
	for(int i = 1; i <= n - 1; i++) {
		int u = read(), v = read();
		E[u].pb(v), E[v].pb(u);
	}
	dfs(1, 0);
	cout << (dp[1][1] + dp[1][0]) % Mod;
	return 0;
}


---

## 作者：technopolis_2085 (赞：0)

### [ABC036D] 塗り絵 题解

分析：

### 很明显是树形的 dp。

设计状态：

令 $dp_{i,0}$ 表示第 $i$ 个节点染成白色的方案数，

令 $dp_{i,1}$ 表示第 $i$ 个节点染成黑色的方案数。

答案：$dp_{1,0}$ 与 $dp_{1,1}$ 的和。

转移过程：

对于每一个节点 $u$，我们先考虑用 dfs 计算出它所有子节点的方案数，再计算 $u$ 节点的方案数。

当 $u$ 节点染成白色时，子节点可以染成白色或者黑色，用乘法原理逐个乘起来。

当 $u$ 节点染成黑色时，子节点只能染成白色，用乘法原理逐个乘起来。

中间过程记得取余。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=1e5+10;
vector<int> G[maxn];
int dp[maxn][2];

const int mod=1e9+7;

void dfs(int u,int fa){
	dp[u][0]=dp[u][1]=1;
	
	for (int i=0;i<(int)G[u].size();i++){
		int v=G[u][i];
		if (v==fa) continue;
		
		dfs(v,u);
		dp[u][0]=dp[u][0]*(dp[v][0]+dp[v][1])%mod;
		dp[u][1]=dp[u][1]*dp[v][0]%mod; 
	}
}

signed main(){
	int n;
	scanf("%lld",&n);
	for (int i=1;i<n;i++){
		int u,v;
		scanf("%lld%lld",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	
	dfs(1,0);
	printf("%lld",(dp[1][0]+dp[1][1])%mod);
	return 0;
}
```


---

