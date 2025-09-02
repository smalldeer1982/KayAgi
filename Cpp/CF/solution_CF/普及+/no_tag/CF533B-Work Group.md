# Work Group

## 题目描述

One Big Software Company has $ n $ employees numbered from $ 1 $ to $ n $ . The director is assigned number $ 1 $ . Every employee of the company except the director has exactly one immediate superior. The director, of course, doesn't have a superior.

We will call person $ a $ a subordinates of another person $ b $ , if either $ b $ is an immediate supervisor of $ a $ , or the immediate supervisor of $ a $ is a subordinate to person $ b $ . In particular, subordinates of the head are all other employees of the company.

To solve achieve an Important Goal we need to form a workgroup. Every person has some efficiency, expressed by a positive integer $ a_{i} $ , where $ i $ is the person's number. The efficiency of the workgroup is defined as the total efficiency of all the people included in it.

The employees of the big software company are obsessed with modern ways of work process organization. Today pair programming is at the peak of popularity, so the workgroup should be formed with the following condition. Each person entering the workgroup should be able to sort all of his subordinates who are also in the workgroup into pairs. In other words, for each of the members of the workgroup the number of his subordinates within the workgroup should be even.

Your task is to determine the maximum possible efficiency of the workgroup formed at observing the given condition. Any person including the director of company can enter the workgroup.

## 说明/提示

In the sample test the most effective way is to make a workgroup from employees number $ 1,2,4,5,6 $ .

## 样例 #1

### 输入

```
7
-1 3
1 2
1 1
1 4
4 5
4 3
5 2
```

### 输出

```
17
```

# 题解

## 作者：bunH2O (赞：5)

[题目链接](https://www.luogu.com.cn/problem/CF533B)

还算朴素的树形dp题(?)

一句话题意：给定一棵树，要求选定一些点加入点集，使得这些点的权值和最大，且对于点集中的任意一个点，其子树中恰有奇数个点被选中。

-----------------------

我们可以令 $f[x][0/1]$ 表示在子树 $x$ 中有偶数/奇数个在点集中的点时最大的权值和。

显然，对于一个偶数，仅可能由两个偶数或两个奇数组成；

同理，对于一个奇数，仅可能由一个奇数和一个偶数组成。

所以可以有：

$\begin{cases}f[u][0]=max(f[v][0]+f[u][0],f[v][1]+f[u][1])\\f[u][1]=max(f[v][0]+f[u][1],f[v][1]+f[u][0])\end{cases}$

为什么呢？

根据定义，$f[u][0]$ 表示子树 $u$ 中有偶数个节点，所以只能由两个偶数或两个奇数组成。

同理可得，$f[u][1]$ 表示子树 $u$ 中有奇数个节点，所以只能由一个奇数和一个偶数组成。

------------------------

同时，根据题意，一个结点可以被选入点集当且仅当这个节点的子树在点集的点为奇数。

因此，我们可以得到：

$f[u][1]=max(f[u][1],f[u][0]+a[u])$

------------------------

奉上丑陋的代码：

```cpp
#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
vector<vector<ll> >tree(250001);
ll a[250001],f[250001][2];
void dfs(ll u)
{
	f[u][1]=-1145141919810;
	for(int i=0;i<tree[u].size();i++)
	{
		ll v=tree[u][i];
		dfs(v);
		ll x=f[u][0],y=f[u][1];
		f[u][0]=max(f[v][0]+x,f[v][1]+y);
		f[u][1]=max(f[v][1]+x,f[v][0]+y);
	}
	f[u][1]=max(f[u][1],f[u][0]+a[u]);
}
int main()
{
	ll n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		ll x,y;
		cin>>x>>y;
		if(x!=-1)
		{
			tree[x].push_back(i);
		}
		a[i]=y;
	}
	dfs(1);
	cout<<max(f[1][0],f[1][1])<<endl;
	return 0;
}
```


---

## 作者：Hello，yearning (赞：3)

#### 最近在复习树形DP，然后就发现了这样一道题。。。
#### solution：
   我们可以比较容易的发现，对于up[u][1/0]表示以点u为根节点的子树中选取的点的个数是奇数或偶数且合法的最大的权值和。
   
   转移方程如下：
   
dp[u][0]=∑max(dp[v][1]+dp[u][1],dp[v][0]+dp[u][0]) //奇加奇 偶加偶
   
dp[u][1]=max{dp[u][0]+v[u],∑max(dp[v][1]+dp[u][0],dp[v][0]+dp[u][1])}//子树和奇+自己 奇加偶 偶加奇 
  
  查看code自行~~感性理解~~
 ```cpp
#include<cstdio>
#include<algorithm>
#define ll long long 
using namespace std;
const int N=1e5+10;
int h[N<<1],cnt,n,root,p;
ll dp[N<<1][2],v[N<<1];
struct edge{
	int v,nxt;
}e[N<<2];
inline void add(int a,int b)
{
	e[++cnt].v=b;
	e[cnt].nxt=h[a];
	h[a]=cnt;
} 
template <typename e> inline void read(e &x)
{
	x=0;int f=1;char ch=getchar();
	while(ch<'0' || ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x*=f;
}
void dfs(int u,int fa)
{
	dp[u][1]=-1ll<<62;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs(v,u);
		ll x1=dp[u][1],x0=dp[u][0];
		dp[u][0]=max(dp[v][1]+x1,dp[v][0]+x0);
		dp[u][1]=max(dp[v][1]+x0,dp[v][0]+x1);
	}
	dp[u][1]=max(dp[u][1],dp[u][0]+v[u]);
}
int main()
{
	read(n);register int i;
	for(i=1;i<=n;++i)
	{
		read(p);read(v[i]); 
		if(p==-1) root=i;
		add(i,p);add(p,i);
	}
	dfs(root,-1);
	printf("%lld",max(dp[root][0],dp[root][1]));
	return 0;
}
```



---

## 作者：hzoi_liuchang (赞：2)

### 分析
树形$DP$

我们设$f[x][0][0]$为以$x$为根的子树选择了偶数个节点，其中编号为$x$的节点不选所得到的最大权值

我们设$f[x][1][0]$为以$x$为根的子树选择了偶数个节点，其中编号为$x$的节点选择所得到的最大权值

我们设$f[x][0][1]$为以$x$为根的子树选择了奇数个节点，其中编号为$x$的节点不选所得到的最大权值

我们设$f[x][1][1]$为以$x$为根的子树选择了奇数个节点，其中编号为$x$的节点选择所得到的最大权值

每次转移时，我们记录在$x$的儿子节点中选择奇数个节点的最大值$maxj$，选择偶数个节点的最大值$maxo$,最后更新$x$的$f$值即可
### 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
typedef long long ll;
ll f[maxn][2][2],a[maxn];
vector<ll> g[maxn];
void dfs(ll now){
    if(g[now].size()==0){
        f[now][0][0]=0;
        f[now][1][0]=a[now];
        f[now][0][1]=f[now][1][1]=-0x3f3f3f3f;
        return;
    }
    ll maxj=0,maxo=0;
    for(ll i=0;i<g[now].size();i++){
        ll u=g[now][i];
        dfs(u);
        ll aa=maxj,bb=maxo;
        if(aa!=0) maxj=max(aa+max(f[u][0][0],f[u][1][1]),bb+max(f[u][0][1],f[u][1][0]));
        else maxj+=(bb+max(f[u][0][1],f[u][1][0]));
        if(aa!=0) maxo=max(aa+max(f[u][0][1],f[u][1][0]),bb+max(f[u][0][0],f[u][1][1]));
        else maxo+=max(f[u][0][0],f[u][1][1]);
    }
    f[now][0][0]=maxo;
    f[now][1][0]=maxo+a[now];
    f[now][0][1]=maxj;
}
int main(){
    ll n;
    scanf("%lld",&n);
    ll rt;
    for(ll i=1;i<=n;i++){
        ll aa,bb;
        scanf("%lld%lld",&aa,&bb);
        if(aa==-1) rt=i;
        else g[aa].push_back(i);
        a[i]=bb;
    }                                                                               
    dfs(rt);
    printf("%lld\n",max(max(f[rt][0][1],f[rt][0][0]),f[rt][1][0]));
    return 0;
}
```

---

## 作者：apiad (赞：1)

因为奇偶性，所以我们可以开一个二维的 DP 来计算。首先处理状态转移方程：$dp_{i,j}$ 中代表 $i$ 这个子树里奇偶情况为 $j$ 的最大权值和。如何转移？偶数可以由两个偶数加两个奇数组成。奇数只能奇数加偶数。于是我们可以得到转移方程。$dp_{i,0} = \max(dp_{i,0}+dp_{j,0},dp_{i,1}+dp_{j,1})$ 和 $dp_{i,1} = \max(dp_{i,0}+dp_{j,1},dp_{i,1}+dp_{j,0})$。其中，$j$ 是 $i$ 的一个子节点。然后又有 $dp_{i,1} = \max(dp_{i,1},dp_{i,0} + num_i)$。于是树形 Dp 直接转移即可。

```cpp
const int N = 2e5 + 5, M = 2e5 + 5;
vector<int> mp[N];
int num[N];
int n;
int dp[N][3];
void dfs(int x, int fa) {
	dp[x][1] = -inf;
	for (auto it : mp[x]) {
		if (it == fa) continue;
		dfs(it,x);
		int tmp1 = dp[x][0],tmp2 = dp[x][1];
		dp[x][0] = max(tmp1+dp[it][0],tmp2+dp[it][1]);
		dp[x][1] = max(tmp1+dp[it][1],tmp2+dp[it][0]);
	}dp[x][1]=max(dp[x][1],dp[x][0] + num[x]);
	return;
}
void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x, y;
		cin >> x >> y;
		if (x != -1) {
			mp[x].push_back(i);
		}
		num[i] = y;
	}

	dfs(1, 0);
	
	cout<<max(dp[1][0],dp[1][1]);
}


```

---

## 作者：heshuxi (赞：0)

## 做题思路

见到题目需要我们求一个有限制最大集合，我们应本能地感觉到这题应该是动态规划。于是用动归考虑这道题目。

我们发现这道题目的限制有两个：最大和每个人有偶数个下属。最大不特别，但看每个人有偶数个下属，我们想：偶数可以由什么数相加得到。显然的，偶数可以是奇数和奇数的和或者偶数和偶数的和。但是需要下属数为偶数，所以只能由偶数和偶数得到。其中还需要用到奇数，我们还要同理去考虑奇数。

于是我们得到思路，分有奇数个下属和偶数个下属讨论。从而便于我们转移状态。

## 状态设计

 $ f[u][0/1] $ 表示以第 $ u $ 个节点为根，下属数为奇数（偶数）时最大的权值。
 
## 状态转移方程

```cpp
int x=f[u][0],y=f[u][1];
f[u][0]=max(f[v][0]+x,f[v][1]+y);      
f[u][1]=max(f[v][1]+x,f[v][0]+y);
```

就是分奇数和偶数考虑转移。

注意，到最后还需要考虑加上该节点后的状态。就是如下的语句。

```cpp
f[u][1]=max(f[u][1],f[u][0]+p[u]);
```
详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,cnt,head[N],p[N],ro,f[N][2];
struct Edge{int from,next,to;}edge[N];
void add(int from,int to){edge[++cnt].next=head[from];edge[cnt].to=to;edge[cnt].from=from;head[from]=cnt;}
void dfs(int u){
	f[u][1]=LONG_LONG_MIN;
	for(int e=head[u];e;e=edge[e].next){
		int v=edge[e].to;dfs(v);
		int x=f[u][0],y=f[u][1];
		f[u][0]=max(f[v][0]+x,f[v][1]+y);      
		f[u][1]=max(f[v][1]+x,f[v][0]+y);
	}
	f[u][1]=max(f[u][1],f[u][0]+p[u]);
}
signed main(){
	scanf("%lld",&n);
	for(int i=1,x;i<=n;i++){
		scanf("%lld%lld",&x,&p[i]);
		if(x!=-1) add(x,i); else ro=i;
	}
	dfs(ro);
	cout<<max(f[ro][0],f[ro][1]);
	return 0;
}
```

完结撒花。

---

## 作者：carp_oier (赞：0)

## advertisement

这位靓仔，你都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/17770621.html)看看呢。

## analysis

我们很明显能够发现这个题目的性质：

1. 奇数是由孩子的奇数和我的偶数，或者是孩子的偶数我的奇数取一个最大值进行更新。
2. 偶数就是我的偶数和孩子的偶数，或者是孩子奇数和我的奇数取一个最大值进行更新。


我们不妨用 $0$ 表示已经选择了偶数个节点，用 $1$ 表示已经选择了奇数个节点。

易得我们这个题目的转移方程为：

$$f_{u, 0} \gets \max(f_{v, 0} + f_{u, 0}, f_{v, 1} + f_{u, 1})$$
$$f_{u, 1} \gets \max(f_{v, 1} + f_{u, 0}, f_{v, 0} + f_{u, 1})$$

## code time

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rl register ll
#define foa(i, a, b) for(rl i=a; i < b; ++ i)
#define fos(i, a, b) for(rl i=a; i <= b; ++ i)
#define fop(i, a, b) for(rl i=a; i >= b; -- i)
#define ws putchar(' ')
#define wl putchar('\n')

template <class T> inline void waw(T x)
{
    if(x > 9) waw(x / 10);
    putchar(x % 10 ^ 48);
}

template <class T> inline void ww(T x)
{
    if(x < 0) x = ~x + 1, putchar('-');
    waw(x);
}

template <class T> inline void read(T &res)
{
    char ch = getchar(); bool f = 0; res = 0;
    for(; !isdigit(ch); ch = getchar()) f |= ch == '-';
    for(; isdigit(ch); ch = getchar()) res = (res << 1) + (res << 3) + (ch ^ 48);
    res = f ? ~res + 1 : res;
}

const ll N = 2e5 + 10, M = N << 1;

ll n, m, w[N], f[N][2];

ll tot, h[N];

struct edge { ll v, ne; } e[M];

inline void add(ll a, ll b) { e[ ++ tot] = {b, h[a]}, h[a] = tot; } 

inline void dfs(ll u, ll fa)
{
    f[u][1] = -1e18;

    for(rl i=h[u]; ~i; i = e[i].ne)
    {
        ll v = e[i].v;
        if(v == fa) continue;
        dfs(v, u);
        ll x = f[u][1], y = f[u][0];
        f[u][0] = max(f[v][1] + x, f[v][0] + y);
        f[u][1] = max(f[v][1] + y, f[v][0] + x);
    }
    f[u][1] = max(f[u][1], f[u][0] + w[u]);
}

int main()
{
    read(n);

    tot = -1, memset(h, -1, sizeof h);

    fos(i, 1, n)
    {
        ll a, b; read(a), read(b);
        if(a != -1) add(a, i), add(i, a); w[i] = b;
    }

    dfs(1, -1);

    cout << max(f[1][0], f[1][1]) << endl;
    return 0;
}
```

---

## 作者：Lib_Zhang (赞：0)

#### 题意简述:
给出一棵节点数为 $n$ 的树，选出点权最大的一个点集，满足每个点的后代有偶数个也在集合中（即所有一共奇数个）。

#### 分析:

考虑树形 dp,从奇偶个数下手，设 $dp_{root}{1}$ 表示以 $root$ 为根的子树选奇数个节点，$dp_{root}{2}$ 表示以 $root$ 为根的子树选偶数个节点。

因为奇数 $+$ 奇数 $=$ 偶数 $+$ 偶数 $=$ 偶数，所以对于选偶数个的情况需要考虑奇数和奇数，偶数和偶数。

因为奇数 $+$ 偶数 $=$ 偶数 $+$ 奇数 $=$ 奇数，所以对于选奇数个的情况需要考虑奇数和偶数，偶数和奇数。

最后为了保证所有的节点数为奇数，比较时也要加上原节点。

具体的状态转移方程见 treedp 部分。


### 代码:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<set>
#include<stack>
#include<map>
#include<queue>
#include<cstdlib>
#include<iomanip>
#include<utility>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pai;
const double eps = 1e-10;
const int base = 13331;
const ll mod = 998242353;
ll maxn = -2147483647-1,minn = 0x7f7f7f7f;
ll n,a[200005],op,root = 1,dp[200005][2];
vector<ll> edge[200005];
void treedp(ll root){
	dp[root][0] = 0,dp[root][1] = maxn;
	for(ll y:edge[root]){
		ll vj = dp[root][0],vo = dp[root][1];
		treedp(y);
		dp[root][0] = max(dp[y][0]+vj,dp[y][1]+vo);
		dp[root][1] = max(dp[y][1]+vj,dp[y][0]+vo);
	}	
	dp[root][1] = max(dp[root][1],dp[root][0]+a[root]);
}
int main(){
	//freopen("filename.in","r",stdin);
	//freopen("filename.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>op>>a[i];
		if(op==-1){
			continue;
		}
		edge[op].push_back(i);
	}
	treedp(root);
	cout<<dp[root][1]<<endl;
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}

```

#### 总结:
显然的树形 dp，感觉评蓝过高了。


---

