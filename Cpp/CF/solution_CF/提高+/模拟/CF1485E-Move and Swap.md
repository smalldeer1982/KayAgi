# Move and Swap

## 题目描述

You are given $ n - 1 $ integers $ a_2, \dots, a_n $ and a tree with $ n $ vertices rooted at vertex $ 1 $ . The leaves are all at the same distance $ d $ from the root.

Recall that a tree is a connected undirected graph without cycles. The distance between two vertices is the number of edges on the simple path between them. All non-root vertices with degree $ 1 $ are leaves. If vertices $ s $ and $ f $ are connected by an edge and the distance of $ f $ from the root is greater than the distance of $ s $ from the root, then $ f $ is called a child of $ s $ .

Initially, there are a red coin and a blue coin on the vertex $ 1 $ . Let $ r $ be the vertex where the red coin is and let $ b $ be the vertex where the blue coin is. You should make $ d $ moves. A move consists of three steps:

- Move the red coin to any child of $ r $ .
- Move the blue coin to any vertex $ b' $ such that $ dist(1, b') = dist(1, b) + 1 $ . Here $ dist(x, y) $ indicates the length of the simple path between $ x $ and $ y $ . Note that $ b $ and $ b' $ are not necessarily connected by an edge.
- You can optionally swap the two coins (or skip this step).

Note that $ r $ and $ b $ can be equal at any time, and there is no number written on the root.

After each move, you gain $ |a_r - a_b| $ points. What's the maximum number of points you can gain after $ d $ moves?

## 说明/提示

In the first test case, an optimal solution is to:

- move $ 1 $ : $ r = 4 $ , $ b = 2 $ ; no swap;
- move $ 2 $ : $ r = 7 $ , $ b = 6 $ ; swap (after it $ r = 6 $ , $ b = 7 $ );
- move $ 3 $ : $ r = 11 $ , $ b = 9 $ ; no swap.

The total number of points is $ |7 - 2| + |6 - 9| + |3 - 9| = 14 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1485E/4458e6880f21f3108c1f541006f191c7d2396ea3.png)In the second test case, an optimal solution is to:

- move $ 1 $ : $ r = 2 $ , $ b = 2 $ ; no swap;
- move $ 2 $ : $ r = 3 $ , $ b = 4 $ ; no swap;
- move $ 3 $ : $ r = 5 $ , $ b = 6 $ ; no swap.

The total number of points is $ |32 - 32| + |78 - 69| + |5 - 41| = 45 $ .

## 样例 #1

### 输入

```
4
14
1 1 1 2 3 4 4 5 5 6 7 8 8
2 3 7 7 6 9 5 9 7 3 6 6 5
6
1 2 2 3 4
32 78 69 5 41
15
1 15 1 10 4 9 11 2 4 1 8 6 10 11
62 13 12 43 39 65 42 86 25 38 19 19 43 62
15
11 2 7 6 9 8 10 1 1 1 5 3 15 2
50 19 30 35 9 45 13 24 8 44 16 26 10 40```

### 输出

```
14
45
163
123```

# 题解

## 作者：lsj2009 (赞：6)

### Solution

很高明的 dp 题，感觉不止 2500，其实完全可以评紫啊。

首先最直观的想法是 $f_{x,y}$ 表示红点在 $x$，蓝点在 $y$ 的最大得分，但是发现红点和蓝点必然在同一层上，而且蓝点的位置是任意的，所以设 $f_u$ 表示红点在点 $u$ 时的最大得分。

接下来考虑交换/不交换红蓝点的位置。

- 不交换：贪心的考虑，此时蓝点必然在这一层的最大/最小值时最优，维护一下当前层的最大/最小值即可。

得转移方程：

$$f_u\gets\begin{cases}
 f_{fa_u}+\max_{d_u}-a_u\\
 f_{fa_u}+a_u-\min_{d_u}\\
\end{cases}$$

其中 $\max_x$ 和 $\min_x$ 表示第 $x$ 的最大/最小值。

- 交换：设当前红子在 $u$ 且蓝子在 $v$，然后交换，得：

$$f_v\gets f_{fa_u}+|a_u-a_v|$$

然后是经典 trick，考虑到 $|a-b|=\max(a-b,b-a)$，所以我们将绝对值拆开来，得：

$$f_v\gets\begin{cases}
 a_v+\max(f_{fa_u}-a_u)\\
 -a_v+\max(f_{fa_u}+a_u)\\
\end{cases}$$

维护一下这一层的 $\max(f_{fa_u}-a_u)$ 和 $\max(f_{fa_u}+a_u)$ 即可。

最终复杂度 $\Theta(n)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e5+5;
int head[N],len;
struct node {
    int to,nxt;
}; node edge[N<<1];
void add_edge(int u,int v) {
	edge[++len]={v,head[u]}; head[u]=len;
}
vector<int> vec[N];
int d[N],f[N],mx[N],pa[N],mn[N],a[N],n,T;
void dfs(int u,int fa) {
    d[u]=d[fa]+1;
    pa[u]=fa;
    chkmax(mx[d[u]],a[u]);
    chkmin(mn[d[u]],a[u]);
    vec[d[u]].push_back(u);
    for(int i=head[u];i;i=edge[i].nxt) {
        int v=edge[i].to;
        if(v!=fa)
            dfs(v,u);
    }
}
void init() {
    len=0;
    rep(i,1,n) {
        head[i]=0;
        d[i]=f[i]=pa[i]=mx[i]=0;
        mn[i]=INF;
        vec[i].clear();
    }
}
signed main() {
    scanf("%lld",&T);
    while(T--) {
        scanf("%lld",&n);
        init();
        rep(i,2,n) {
            int u;
            scanf("%lld",&u);
            add_edge(u,i);
            add_edge(i,u);
        }
        rep(i,2,n)
            scanf("%lld",&a[i]);
        dfs(1,0);
        int ans=0;
        rep(i,2,n) {
            int val1=-INF,val2=-INF;
            for(auto u:vec[i]) {
                chkmax(val1,f[pa[u]]+a[u]);
                chkmax(val2,f[pa[u]]-a[u]);
            }
            for(auto u:vec[i]) {
                chkmax(f[u],f[pa[u]]+max(mx[i]-a[u],a[u]-mn[i]));
                chkmax(f[u],max(val1-a[u],val2+a[u]));
                chkmax(ans,f[u]);
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：FiraCode (赞：3)

## 题解思路：
设 $dp_{i,j}$ 代表：$i \to $ 蓝，$j \to $ 红，能到达状态最大值。

我们再枚举一个 $dp_{x , y}$，然后转移，时间复杂度就是 $\mathcal O(n ^ 4)$。 

我们可以加入一些优化：

$dp_{x , y}$：
要么从 $dp_{i , fa_{y}}$ 转移来。

要么从 $dp_{i , fa_{x}}$ 转移来。

这样的话就不用枚举 $j$ 了，时间复杂度变成了 $\mathcal O(n ^ 3)$。

我们发现直接一维就可以了，因为蓝色这个点可以在任意位置，所以我们只要知道层数就可以了，而红色点和蓝色点在同一层，所以只保留红色点那一维就可以了。

装态转移方程：
> $1$ 操作
>> $dp_{y} = \max (dp_{y}, dp_{fa_{y}} + \operatorname{abs} (a_{y} - mi))$ 其中 $mi$ 表示这一层的最小值。

>> $dp_{y} = \max (dp_{y}, dp_{fa_{y}} + \operatorname{abs} (a_{y} - ma))$ 其中 $ma$ 表示这一层的最大值。

> $2$ 操作
>> $dp_{y} = \max (dp_{y} + dp_{fa_{x}} + \operatorname{abs} (a_{x} - a_{y}))$。

优化完之后时间复杂度就变成了 $\mathcal O(n ^ 2)$。

我们在做一个优化，这个优化只能优化二式：
> 先把绝对值去掉：
>> 要么是：$dp_{y} = \max (dp_{y}, dp_{fa_{x}} + a_{y} - a_{x})$。

>> 要么是：$dp_{y} = \max (dp_{y}, dp_{fa_{x}} + a_{x} - a_{y})$。

> 再把 $dp_{fa_{x}}$ 给提出来，那么我们只需要关心两个值就可以了，我们定义两个值：
>> $f(x) = dp_{fa_{x}} - a_{x}$

>> $g(x) = dp_{fa_{x}} + a_{x}$

> 那么我们就只需要记录 $f(x),g(x)$ 的最大值就可以了，我们就在转移时直接用就可以了。

> 状态转移变为：
>> $dp_{y} = \max (dp_{y}, a_{y} + \max{f(x)})$。

>> $dp_{y} = \max (dp_{y}, - a_{y} + \max{g(x)})$。

时间复杂度就变成了：$\mathcal{O(n)}$。

## AC CODE:
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 200010;
int n;
ll dp[N];
vector <int> e[N] , d[N];
int fa[N] , deep[N] , ma[N] , mi[N] , a[N];
void dfs (int u , int pre) {
	deep[u] = deep[pre] + 1;//深度，他的深度为他的父节点的深度加一
	d[deep[u]].push_back (u);//每一层有那些值
	ma[deep[u]] = max (ma[deep[u]] , a[u]);//每一层的最大值
	mi[deep[u]] = min (mi[deep[u]] , a[u]);//每一层的最小值
	for (auto v : e[u]) {
		if (v == pre) continue;
		fa[v] = u;//预处理fa数组
		dfs (v , u);//递归他的儿子节点
	}
}
void init () {//初始化
	for (int i = 1; i <= n; ++ i) {
		e[i].clear ();
		d[i].clear ();
		dp[i] = fa[i] = deep[i] = ma[i] = 0;
		mi[i] = 2e9;
	}
}
int main() {
	memset (mi , 0x3f , sizeof (mi));
	int T;
	scanf ("%d" , &T);
	while (T --) {
		init ();
		scanf ("%d" , &n);
		for (int i = 2; i <= n; ++ i) {
			int x;
			scanf ("%d" , &x);
			e[x].push_back (i);//连边
			e[i].push_back (x);
		}
		for (int i = 2; i <= n; ++ i) scanf ("%d" , &a[i]);
		dfs (1 , 1);//预处理
		ll ans = 0;
		for (int i = 2; i <= n; ++ i) {
			ll val1 = 0 , val2 = -2e9;//初始化
			for (auto x : d[i]) {//就是预处理f,g
				val1 = max (val1 , dp[fa[x]] + a[x]);
				val2 = max (val2 , dp[fa[x]] - a[x]);
			}
			for (auto x : d[i]) {
				dp[x] = max (dp[x] , dp[fa[x]] + max (ma[i] - a[x] , a[x] - mi[i]));//第一个转移方程 
				dp[x] = max (dp[x] , max (val1 - a[x] , val2 + a[x]));//第二个 
				ans = max (ans , dp[x]);//求个最大值 
			}
		}
		printf ("%lld\n" , ans);//输出
	}
	return 0;
}
```
码字不易，求赞！

---

## 作者：jun头吉吉 (赞：3)

## 题意
有一棵树，以$1$为根，叶子结点深度相同,结点 $i$ 有权值 $a_i$。现在有红蓝两颗棋子，每一步可以进行如下操作：
- 把红色棋子移动到它的子节点
- 把蓝色棋子移动到它下一层的任何一个结点
- 选择交换或不交换红子与蓝子的位置
- 计算得分为 $|a_{red}-a_{blue}|$

问最大的得分和
## 题解
$\rm dp$是不难想到的，但状态如何设计？记录两颗棋子各自的状态肯定是不行的。

但想一想，蓝子现在的位置并不会约束它下一行走到哪里，因此我们只需要记录 红子 的状态即可。

我们先预处理出 每层的最大权值与最小权值 $Max_i$ 与 $Min_i$

设 $dp_i$ 表示红子走到 $i$ 最大的得分和，那么转移：
### 红子从父节点走下来。
那么此时蓝子无任何约束，选择走最大的或最小的可以取得最大的得分，即为 $\max(|a_i-Max_{dep_i}|,|a_i-Min_{dep_i}|)$
### 红子与蓝子交换得到
设蓝子的位置为 $j$ ,那么红子的父亲为 $fa_j$ ,此时的得分和为 $dp_{fa_j}+|a_i-a_j|$。

优化这个 $\rm dp$。一个 $fa_j$ 有贡献的肯定只有最大值与最小值。把上一层的 $(\max\{a_j\}_{j\in son},dp_{i})$ 与 $(\min\{a_j\}_{j\in son},dp_i)$ 两个二元组放进数组，可以把问题转化得更简单：求 $|a_i-first|+second$ 的最大值

按 $first$ 排序，二分找到 $a_i$ 的位置，之前的取 $\max\{second-first\}+a_i$ ，之后的取 $\max\{second+first\}-a_i$，两个 $\max$ 可以事先预处理。

于是得到了一个时间复杂度为 $\mathcal{O}(n\log n)$ 的做法。

把排序换成好吃的鸡排，二分换成均摊可以做到 $\mathcal{O}(n)$ 只不过没什么意义
## 代码
```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	template <typename T>inline void read(T& t){
		t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
	    while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
}
namespace out{
	char buffer[1<<21];int p1=-1;const int p2 = (1<<21)-1;
	inline void flush(){fwrite(buffer,1,p1+1,stdout),p1=-1;}
	inline void putc(const char &x) {if(p1==p2)flush();buffer[++p1]=x;}
	template <typename T>void write(T x) {
		static char buf[15];static int len=-1;if(x>=0){do{buf[++len]=x%10+48,x/=10;}while (x);}else{putc('-');do {buf[++len]=-(x%10)+48,x/=10;}while(x);}
		while (len>=0)putc(buf[len]),--len;
	}
}
using namespace std;
const int N=2e5+10;
#define int long long
int t,n,a[N];vector<vector<int>>e,node;
vector<int>dep,fa,mx,mn,dp;
#define chkmx(a,b) (a)=max((a),(b))
#define chkmn(a,b) (a)=min((a),(b))
void dfs1(int u){
	dep[u]=dep[fa[u]]+1;
	chkmx(mx[dep[u]],a[u]);
	chkmn(mn[dep[u]],a[u]);
	node[dep[u]].push_back(u);
	for(auto v:e[u])if(v!=fa[u])
		fa[v]=u,dfs1(v);
}
void work(){
	in::read(n);
//	多测不清空，抱凌两行* 
	e=vector<vector<int>>(n+1,vector<int>(0));
	node=vector<vector<int>>(n+1,vector<int>(0));
	dep=vector<int>(n+1);
	fa=vector<int>(n+1);
	dp=vector<int>(n+1,0);
	mx=vector<int>(n+1,-0x3f3f3f3f3f3f3f3f);
	mn=vector<int>(n+1,0x3f3f3f3f3f3f3f3f);
	for(int v,i=2;i<=n;i++)in::read(v),e[v].push_back(i),e[i].push_back(v);
	for(int i=2;i<=n;i++)in::read(a[i]);
	dfs1(1);
//	处理父子、深度、每层最大值
//	然后就是简单的dp
	vector<pair<int,int>>tmp;vector<int>pre,suf;
	for(int i=1;i<=n;i++){
		if(!node[i].size())break; 
		if(i!=1)
//			从 上一行转移
			for(auto u:node[i]){
				chkmx(dp[u],dp[fa[u]]+max(abs(a[u]-mx[i]),abs(a[u]-mn[i])));
//				从上一行直接移下来
				int pos=lower_bound(tmp.begin(),tmp.end(),make_pair(a[u]+1,0ll))-tmp.begin();
//				tmp[pos]之前取  second+a[u]-first
//				tmp[pos]及之后  second+first-a[u]
//				前后缀维护一下就ok了
				if(pos!=0)chkmx(dp[u],pre[pos-1]+a[u]);
				if(pos!=tmp.size())chkmx(dp[u],suf[pos]-a[u]); 
				//printf("%d %d\n",u,dp[u]);
			}
		tmp.clear();int Mx,Mn;
		for(auto u:node[i]){
//			保存信息给下一行
			Mx=-0x3f3f3f3f3f3f3f3f;
			Mn=0x3f3f3f3f3f3f3f3f;
			for(auto v:e[u])if(v!=fa[u])
				chkmx(Mx,a[v]),chkmn(Mn,a[v]);
			tmp.push_back({Mx,dp[u]});
			if(Mn!=Mx)
			tmp.push_back({Mn,dp[u]});
		}
		if(!tmp.size())break;
		sort(tmp.begin(),tmp.end());pre.resize(tmp.size());suf.resize(tmp.size());
		pre[0]=tmp[0].second-tmp[0].first;for(int i=1;i<tmp.size();i++)pre[i]=max(pre[i-1],tmp[i].second-tmp[i].first);
		suf[tmp.size()-1]=tmp[tmp.size()-1].second+tmp[tmp.size()-1].first;for(int i=(int)(tmp.size())-2;i>=0;i--)suf[i]=max(suf[i+1],tmp[i].second+tmp[i].first);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		chkmx(ans,dp[i]);
	out::write(ans);
	out::putc('\n');
}
signed main(){
	in::read(t);
	while(t--)work();
	out::flush();
	return 0;
}
```

---

## 作者：LS_Z_66066 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1485E)

显然可以设 $dp_{i,j}$ 表示红点在 $i$，蓝点在 $j$，的最大得分，复杂度明显超了。

先不考虑交换，模拟样例发现红点和蓝点每次都会向下移动一层，所以两点始终在同一层，蓝点可以在该层的任意点，只有最小值或最大值才会使得分最大，蓝点约束较少，不方便转移，故定义 $f_u$ 为红点在 $u$ 号点的最大得分，可得 $f_u = f_{fa_u}+\max(ma-a_u,a_u-mi)$，其中 $ma$ 为该层最大值，$mi$为该层最小值。

接着考虑交换，可得 $f_u=f_{fa_u}+\max\{\vert a_u-a_v\vert\}$。拆开得 $f_u=\max(f_{fa_u}+a_u-a_v,f_{fa_u}-a_u+a_v)$，分别维护 $f_{fa_u}+a_u$ 和 $f_{fa_u}-a_u$ 的最大值即可。

[AC记录](https://codeforces.com/problemset/submission/1485/322021347)

---

## 作者：gesong (赞：2)

题目传送门：[CF1485E Move and Swap](https://www.luogu.com.cn/problem/CF1485E)。
# 思路

考虑 dp，我们发现蓝子的移动的影响不是很大，设 $f_x$ 表示红子在 $x$ 位置的最大得分。

转移要分两种情况：
1. 不交换，那么肯定蓝子的位置选择这一层的最大或最小位置。

   $$f_u=\max(f_{fa_u}+a_u-\min_{dep_v=dep_u} a_v,f_{fa_u}-a_u+\max_{dep_v=dep_u} a_v)$$
2. 交换。
   $$\begin{aligned}
      f_u&=\max_{dep_v=dep_u}(f_{fa_v}+|a_u-a_v|)\\
      &=\max_{dep_v=dep_u} \max(f_{fa_v}+a_u-a_v,f_{fa_v}-a_u+a_v)\\
      &=\max (\max_{dep_v=dep_u} (f_{fa_v}-a_v)+a_u,\max_{dep_v=dep_u} (f_{fa_v}+a_v)-a_v)
   \end{aligned}$$

其中有一步用到了 $|a-b|=\max(a-b,-a+b)$。
   
# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int N=2e5+10;
int n,a[N],fa[N],dep[N],f[N];
vector<int>b[N],c[N];
void dfs(int u,int fa){
	c[dep[u]].push_back(u);
	::fa[u]=fa;
	for (auto v:b[u]) if (v^fa) dep[v]=dep[u]+1,dfs(v,u);
}
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
inline void solve(){
	n=read();
	for (int i=1;i<=n;i++) b[i].clear(),c[i].clear(),f[i]=-1e18;
	for (int i=2;i<=n;i++){
		int x=read();
		b[i].push_back(x);
		b[x].push_back(i);
	}
	for (int i=2;i<=n;i++) a[i]=read();
	dep[1]=1;
	dfs(1,0);
	int xx=0;
	for (int i=1;i<=n;i++) xx=max(xx,dep[i]);
	f[1]=0;
	for (int i=2;i<=xx;i++){
		int mx=0,mn=1e9;
		for (auto j:c[i]) mn=min(mn,a[j]),mx=max(mx,a[j]);
		for (auto j:c[i]) f[j]=max(f[fa[j]]+a[j]-mn,f[fa[j]]+mx-a[j]);
		int mx1=-1e18,mx2=-1e18;
		for (auto j:c[i]) mx1=max(mx1,f[fa[j]]-a[j]),mx2=max(mx2,f[fa[j]]+a[j]);
		for (auto j:c[i]) f[j]=max(f[j],max(a[j]+mx1,-a[j]+mx2));
	}
	int ans=0;
	for (int i=1;i<=n;i++) ans=max(ans,f[i]);
	printf("%lld\n",ans);
}
main(){
	int T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：_ZSR_ (赞：2)

### [CF1485E Move and Swap](https://www.luogu.com.cn/problem/CF1485E)

显然有一个很暴力的做法，令 $dp_{i,j}$ 表示红色棋子在 $i$，蓝色棋子在 $j$ 的最大得分。每次枚举上一层的两个点，转移是 $O(n^4)$ 的。

考虑优化。因为红色棋子每次只能从它的父亲走过来，所以我们可以少枚举一层，转移变成 $O(n^3)$。

又因为蓝色棋子可以在一层的任意位置，所以我们只要记一维就可以了。令 $dp_{i}$ 表示红色棋子在 $i$ 的最大得分。如果没有交换，那么 $dp_{i}=\max(dp_{i},dp_{fa_{i}}+\max(\mid a_{i}-maxx \mid,\mid a_i-minx \mid)$，其中 $maxx,minx$ 分别表示当前这一层的最大值和最小值。如果有交换，那么 $dp_{i}=\max(dp_{i},dp_{fa_{j}}+\mid a_{i}-a_{j} \mid)$。这样就变成 $O(n^2)$ 的了。

我们发现，第一类转移是 $O(n)$ 的，瓶颈在第二类转移，于是继续优化第二类转移。先分类讨论一下，$dp_{i}=\max(dp_{i},dp_{fa_{j}}+a_{i}-a_{j},dp_{fa_{j}}+a_{j}-a{i})$。然后把跟 $j$ 有关的合并，记 $f=\max dp_{fa_{j}}+a_{j},g=\max dp_{fa_{j}}-a_{j}$。那么转移方程就可以写为 $dp_{i}=\max(dp_{i},g+a_{i},f-a_{i})$。对于每一层，我们可以先把 $f,g$ 求出来，这样第二类转移就是 $O(n)$ 的了。

code
```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
int T,n;
int h[N],to[N<<1],nxt[N<<1],idx;
int dep[N],maxa[N],mina[N],a[N],fa[N];
ll dp[N];
vector<int> d[N];
inline void clear()
{
    idx=0;
    for (int i=1;i<=n;++i) h[i]=0;
    for (int i=1;i<=n;++i) dp[i]=0;
    for (int i=1;i<=n;++i) maxa[i]=0;
    for (int i=1;i<=n;++i) mina[i]=0x3f3f3f3f;
    for (int i=1;i<=n;++i) d[i].clear();
}
inline void add(int a,int b)
{
    to[++idx]=b;
    nxt[idx]=h[a];
    h[a]=idx;
}
void dfs(int u,int fath)
{
    dep[u]=dep[fath]+1;
    d[dep[u]].push_back(u);
    maxa[dep[u]]=max(maxa[dep[u]],a[u]);
    mina[dep[u]]=min(mina[dep[u]],a[u]);
    for (int i=h[u];i;i=nxt[i])
    {
        int v=to[i];
        if (v==fath) continue;
        fa[v]=u;
        dfs(v,u);
    }
}
int main()
{
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d",&n);
        clear();
        for (int i=2;i<=n;++i)
        {
            int j;
            scanf("%d",&j);
            add(i,j),add(j,i);
        }
        for (int i=2;i<=n;++i) scanf("%d",&a[i]);
        dfs(1,0);
        ll ans=0;
        for (int i=2;i<=n;++i)
        {
            if (d[i].empty()) break;
            ll f=0,g=-0x3f3f3f3f;
            for (int j:d[i])
            {
                f=max(f,dp[fa[j]]+a[j]);
                g=max(g,dp[fa[j]]-a[j]);
            }
            for (int j:d[i])
            {
                dp[j]=max(dp[j],dp[fa[j]]+max(maxa[i]-a[j],a[j]-mina[i]));
                dp[j]=max(dp[j],max(f-a[j],g+a[j]));
                ans=max(ans,dp[j]);
            }
        }
        printf("%lld\n",ans);
    }
    return 0;   
}
```


---

## 作者：hater (赞：2)

这场的E大概比F难一点 

我们把$r$的路径画出来 

大概是几条从上而下的链 

链中每一个深度只会有一个点 链的端点每一个深度有两个点 （属于两条不同的链 而且显然根节点和叶子节点是不满足的 ） 

那么这种选择的贡献就是 ： 

链中的点与最值匹配 链端的节点同深度匹配 

这个显然可以$dp$ 因为只与$r$当前节点有关 

设 $f_{x}$ 是 匹配到以$x$为下端点的最大答案 （$x$暂未匹配） 

我们枚举这条链的上端点 $y$ 就是  

$f_{x}=f_{k}+\sum_{z\in path_{x,y}}maxp_{z}+abs(a_{k}-a_{y})$ 

（ $maxp$指的是最大匹配 其中$k$与$y$同深度 $z$在其路径上） 

很显然 $sigma$前缀和拆掉 $abs$用拆成两个$max$ $maxp$也显然好求 就是同深度的$min max$点权与其匹配 （易证） 

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
#define ls ch[k][0] 
#define rs ch[k][1] 
#define int long long 
using namespace std ; 
const int N = 2e5+10 , inf = 1e16+7 ; 
vector <int> v[N] , pd[N] ; 
int d[N] , mnd[N] , mxd[N] , t[N][2] , m , n , a[N] , pre[N] , mx[N] , sum[N] , f[N] ;       
void dfs1( int x , int fa ) { 
  int l = v[x].size() , y ; 
  pd[d[x]].push_back(x) ; 
  mxd[d[x]] = max( mxd[d[x]] , a[x] ) ; 
  mnd[d[x]] = min( mnd[d[x]] , a[x] ) ; 
  m = max( m , d[x] ) ; 
  fp( i , 0 , l-1 ) { 
    y = v[x][i] ; 
    if( y == fa ) continue ; 
    d[y] = d[x] + 1 ; 
    dfs1( y , x ) ; 
  } 
} 
void dfs2( int x , int fa ) { 
  pre[x] = fa ; 
  int l = v[x].size() , y ; 
  if( x != 1 ) 
    sum[x] = sum[fa] + max( abs(a[x]-mxd[d[x]]) , abs(a[x]-mnd[d[x]]) ) ; 
  fp( i , 0 , l-1 ) { 
    y = v[x][i] ; 
    if( y == fa ) continue ; 
    dfs2( y , x ) ; 
  } 
} 
signed main( ) {   
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  int T , x , nw ; cin >> T ; 
  while( T -- ) { 
    int ans = 0 ;  
    cin >> n ; m = 0 ; 
	fp( i , 1 , n ) 
	  mnd[i] = inf , mxd[i] = 0 , v[i].clear( ) , pd[i].clear( ) , t[i][0] = t[i][1] = -inf , f[i] = sum[i] = mx[i] = pre[i] = 0 ;    
    fp( i , 2 , n ) { 
      cin >> x ; 
      v[x].push_back(i) ; v[i].push_back(x) ; 
	} 
	fp( i , 2 , n ) cin >> a[i] ; 
	dfs1( 1 , 0 ) ; 
	dfs2( 1 , 0 ) ; 
	fp( i , 1 , m ) { 
	  int l = pd[i].size() ; 
	  fp( j , 0 , l-1 ) {  
	    nw = pd[i][j] ; 
	    f[nw] = sum[pre[nw]] + mx[pre[nw]] ; 
	    t[i][0] = max( t[i][0] , f[nw] - a[nw] ) ; 
		t[i][1] = max( t[i][1] , f[nw] + a[nw] ) ;  
	  } 
	  fp( j  , 0 , l-1 ) { 
	    nw = pd[i][j] ; 
	    mx[nw] = max( mx[pre[nw]] , max( a[nw] + t[i][0] , t[i][1] - a[nw] ) - sum[nw] ) ; 
	    if( i == m ) 
	      ans = max( ans , f[nw] + sum[nw] - sum[pre[nw]] ) ; 
	  } 
	} 
	cout << ans << '\n' ;  
  } 
  return 0 ; 
} 
/*
1
14
1 1 1 2 3 4 4 5 5 6 7 8 8
2 3 7 7 6 9 5 9 7 3 6 6 5

*/
```


实现的丑 凑合着看 /yun ~~反正水题解~~ 

---

## 作者：JiaY19 (赞：1)

不要什么脑子的带 $\log$ 做法。

### 思路

考虑 $dp_{i,j}$ 表示红点到 $i$，蓝点到 $j$ 的最大权值。

那么有：

$$dp_{i,j}=\max(dp_{fa_i,pre},dp_{fa_j,pre})+|a_i-a_j|$$

其中 $pre$ 是任意一个上一层节点。

发现第二维没有用。

可以优化：

$$dp_i=\max(dp_{fa_i}+\max(|a_i-a_{pre}|),dp_{pre}+|a_i-a_{pre}|)$$

这样我们只需要维护 $\max(|a_i-a_{pre}|)$ 与 $\max(dp_{pre}+|a_i-a_{pre}|)$ 两个值即可。

直接树状数组维护。

### Code

```cpp
/**
 * @file 1485E.cpp
 * @author mfeitveer
 * @date 2023-11-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define mp(x, y) make_pair(x, y)
#define fro(i, x, y) for(int i = (x);i <= (y);i++)
#define pre(i, x, y) for(int i = (x);i >= (y);i--)
#define dbg cerr << "Line " << __LINE__ << ": "
#define EVAL(x) #x " = " << (x)

typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef pair<int, int> PII;

bool ed;

const int N = 1000010;
const int mod = 998244353;

int n, m, q, cnt, fa[N], dep[N], head[N];
i64 a[N], b[N], dp[N];
vector<int> to[N];
struct edge { int to, nxt; } e[N * 2];
class Tree
{
	int op, top{}, vis[N]{}, del[N]{}; i64 t[N];
	inline int lb(int x)
		{ return x & (-x); }
	inline void Add(int x, i64 y)
	{
		if(!vis[x]) vis[x] = 1, del[++top] = x;
		t[x] = max(t[x], y);
	}
	public:
	inline Tree(int o) { op = o, memset(t, -0x3f, sizeof t); }
	inline void add(int x, i64 y)
		{ for(;(op==1 ? x <= m : x);x += lb(x) * op) Add(x, y); }
	inline i64 ask(int x)
	{
		i64 r = -1e17;
		for(;(op==1 ? x : x <= m);x += lb(x) * op * -1)
			r = max(r, t[x]);
		return r;
	}
	inline void clear()
		{ while(top) vis[del[top]] = 0, t[del[top]] = -1e17, top--; }
} t1(-1), t2(1), t3(-1), t4(1);

inline void add(int x, int y)
{
	e[++cnt] = {y, head[x]}, head[x] = cnt;
	e[++cnt] = {x, head[y]}, head[y] = cnt;
}
inline void dfs(int now)
{
	to[dep[now]].push_back(now), q = max(q, dep[now]);
	for(int i = head[now];i;i = e[i].nxt)
	{
		if(e[i].to == fa[now]) continue;
		dep[e[i].to] = dep[now] + 1, dfs(e[i].to);
	}
}
inline void cmax(i64 &x, i64 y)
	{ x = (y > x ? y : x); }
inline void solve()
{
	cin >> n;
	fro(i, 2, n) cin >> fa[i], add(i, fa[i]);
	fro(i, 2, n) cin >> a[i], b[i - 1] = a[i];
	sort(b + 1, b + n);
	m = unique(b + 1, b + n) - b - 1;
	fro(i, 2, n) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
	dfs(1);
	fro(i, 1, q)
	{
		for(auto j : to[i])
			t1.add(a[j], b[a[j]]),
			t2.add(a[j], -b[a[j]]);
		for(auto j : to[i])
			t3.add(a[j], dp[fa[j]] + b[a[j]]),
			t4.add(a[j], dp[fa[j]] - b[a[j]]);
		for(auto j : to[i])
		{
			cmax(dp[j], dp[fa[j]] - b[a[j]] + t1.ask(a[j]));
			cmax(dp[j], dp[fa[j]] + b[a[j]] + t2.ask(a[j]));
			cmax(dp[j], t3.ask(a[j]) - b[a[j]]);
			cmax(dp[j], t4.ask(a[j]) + b[a[j]]);
		}
		t1.clear(), t2.clear(), t3.clear(), t4.clear();
	}
	i64 ans = 0;
	for(auto i : to[q]) ans = max(ans, dp[i]);
	cout << ans << "\n", cnt = q = 0;
	fro(i, 1, n) dp[i] = head[i] = 0, to[i].clear();
}

bool st;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	double Mib = fabs((&ed-&st)/1048576.), Lim = 1024;
	assert(Mib<=Lim), cerr << " Memory: " << Mib << "\n";
	int t; cin >> t;
	while(t--) solve();
	return 0;
}

```

---

## 作者：nanjolno (赞：1)

dp。

注意到在每一层中，蓝币的位置是任意的，而红币的位置是有限制的，仅能由父节点转移到儿子节点。

考虑从上到下一层一层地转移，令$dp[i]$表示红币位于i号节点的最大答案，j表示i号节点的父亲，当我们不考虑换位时，显然:

$$dp[i]=dp[j]+max(|a_i-a_b|)$$

其中($a_b$表示与i位于同一层的蓝币所处位置的值)。我们确定红币位置后，直接贪心取最大的\|$a_i-a_b$\|即可

现考虑换位，则i可以是本层中任意一个位置（因为蓝币在本层中位置是任意的，你可以放好蓝币后与红币交换）。设换位前红币位于k，s是k的父亲，则:

$$dp[i]=max(dp[i],dp[s]+|a_i-a_k|)$$

这样，对于每一个i，我们在这一层中枚举所有的位置取最优即可

然而这样在每层中，每次更新是$O(n^2)$的，全局复杂度也是$O(n^2)$。现考虑如何优化：

当$a_i$>$a_k$时，去掉绝对值，得:

$$dp[s]+|a_i-a_k|=dp[s]+a_i-a_k$$

我们注意到，处理完上一层后，对于位置k，$dp[s]-a_k$的值可以预处理。同理，当$a_i$<$a_k$时,$dp[s]+a_k$的值也可以预处理。

在每一层中，我们把当前层的点用一个vector来维护。我们对当前层的元素以$a_i$为关键字升序排序，这样，处理第i个元素时，对于其前面的元素，我们取最大的$dp[s]-a_k$，对于其后面的元素，我们取最大的$dp[s]+a_k$。为了实现这点，我们考虑构造一个前缀数组$pmax$和后缀数组$bmax$来维护其最值，$pmax[i]$表示i前面所有元素中最大的$dp[s]-a_k$，$bmax[i]$表示i后面所有元素中最大的$dp[s]+a_k$
这样，状态转移方程为：

$$dp[i]=max(dp[i],pamx[i]+a_i,bmax[i]-a_i)$$

最后，我们考虑如何实现一层一层地枚举点。我是把所有点以深度为关键字排序，这样相同深度的点的下标就是一个连续的子段了，令$L[i]$表示深度为i的段的首端，$R[i]$为末端，在dp前处理出$L[i]$，$R[i]$即可


------------
#### 代码

注意我这里使用bmax维护的前缀，pmax维护的后缀
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
struct front_star{
	int to,next;
}e[400005];
struct poi{
	int id,fa,d;
	long long val;
}node[200005];
int T,n,cnt=0,mxd=0;
long long ans=0;
int head[200005],L[200005],R[200005];
long long dp[200005],tpf[200005],tps[200005],pmx[200005],bmx[200005];
vector<poi>f;
inline int read()
{
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline long long maxn(long long a,long long b)
{
	return a>b?a:b;
}
inline void addedge(int u,int v)
{
	cnt++;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
inline bool wcnmp(poi a,poi b)
{
	if(a.d<b.d)
	   return true;
	return false;      
}
inline void dfs(int u,int deep)
{
	mxd=maxn(deep,mxd);
	node[u].d=deep;
	for(register int i=head[u];~i;i=e[i].next)
	{
		int v=e[i].to;
		if(v!=node[u].fa)
		{
			node[v].fa=node[u].id;
			dfs(v,deep+1);
		}
	}
}
inline bool cmp(poi a,poi b)
{
	if(a.val<b.val)
	   return true;
	return false;    
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		cnt=0;
		ans=0;
		mxd=0;
		memset(head,-1,sizeof(head));
		scanf("%d",&n);
		for(register int i=2;i<=n;i++)
		{
			int s;
			s=read();
			addedge(i,s);
			addedge(s,i);
		}
		node[1].id=1;
		node[1].val=0;
		for(register int i=2;i<=n;i++)
		{
			node[i].id=i;
			node[i].val=read();
		}
		node[1].fa=0;
		dfs(1,1);
		sort(node+1,node+1+n,wcnmp);
		L[1]=1,R[mxd]=n;
		int now=1;
		for(register int i=1;i<=n;i++)
		{
			if(now!=node[i].d)
			{
				R[now]=i-1;
				now++;
				L[now]=i;
			}
		}
		memset(dp,0,sizeof(dp));
		for(register int i=2;i<=mxd;i++)
		{
			f.clear();
			for(register int j=L[i];j<=R[i];j++)
			    f.push_back(node[j]);
			int upp=f.size();
			sort(f.begin(),f.end(),cmp);
			for(register int j=0;j<upp;j++)
			{
				bmx[j]=0;
				pmx[j]=0;
				tpf[j]=dp[f[j].fa]+f[j].val;
				tps[j]=dp[f[j].fa]-f[j].val;
			}
			bmx[0]=tps[0];
			pmx[upp-1]=tpf[upp-1];
			for(register int j=1;j<upp;j++)
				bmx[j]=maxn(bmx[j-1],tps[j]);
			for(register int j=upp-2;j>=0;j--)
			    pmx[j]=maxn(pmx[j+1],tpf[j]);	
			for(register int j=0;j<upp;j++)
			{
				poi tp=f[j];
				dp[tp.id]=maxn(dp[tp.id],dp[tp.fa]+f[upp-1].val-tp.val);
				dp[tp.id]=maxn(dp[tp.id],dp[tp.fa]-f[0].val+tp.val);
				dp[tp.id]=maxn(dp[tp.id],bmx[j]+tp.val);
				dp[tp.id]=maxn(dp[tp.id],pmx[j]-tp.val);
			}
		}
	    for(register int i=L[mxd];i<=R[mxd];i++)
	        ans=maxn(dp[node[i].id],ans);
		printf("%lld\n",ans);    
	}
	return 0;
} 
/*
1
17
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 
141742934 542155364 408860514 496518420 268022205 252909000 521914080 315254896 636214743 875364320 404786741 620328680 510764873 126572193 547542158 951490057
*/
```


---

## 作者：Cutest_Junior (赞：1)

## 题解 CF1485E 【Move and Swap】

### 题意

+ 有一棵树，根为 $1$，每个点有权值 $a$，所有叶子深度相同；
+ 有红蓝各一颗棋，每一步红棋可到它的任意一个儿子，蓝棋可到下一层任意点，选择是否交换红蓝棋位置，得分加上两点 $a$ 的绝对差；
+ 求最大得分；
+ 多组数据，$n\le2\times10^5$。

### 做法

每一步的答案都只和上一步有关，考虑 dp。

设 $dp_{x,y}$ 为红蓝棋分别位于点 $x,y$ 时的最大已有得分。

然后发现空间已经爆了，$n\le2\times10^5$。

考虑优化。

发现蓝棋可以随便跳，和下一层无关，消掉这一维。

现在，设 $dp_{x}$ 为红棋位于点 $x$ 时的最大已有得分。

记 $y$ 为蓝棋所在的位置，$f_x$ 为点 $x$ 父亲的编号。

发现分两种情况，
1. 由上一层直接转移下来；
2. 由上一层交换后转移下来。

先考虑第一种。

发现还是有两种情况，
1. 红点的 $a$ 比蓝点的大，$dp_x=\max(a_x-a_y+dp_{f_x})=a_x-\min({a_y})+dp_{f_x}$；
2. 红点的 $a$ 比蓝点的小，$dp_x=\max(a_y-a_x+dp_{f_x})=\max({a_y})-a_x+dp_{f_x}$。

然后是第二种。

同样是两种情况，
1. 红点的 $a$ 比蓝点的大，$dp_x=\max(a_x-a_y+dp_{f_y})=\max({dp_{f_y}-a_y})+a_x$；
2. 红点的 $a$ 比蓝点的小，$dp_x=\max(a_y-a_x+dp_{f_y})=\max({dp_{f_y}+a_y})-a_x$。

然后对于每一层，只要预处理出 $\min({a_y})$、$\max({a_y})$、$\max({dp_{f_y}-a_y})$、$\max({dp_{f_y}+a_y})$ 四个值，然后直接线性转移即可。

### 代码

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

const ll inf = (1ll << 60) - 1;

const int N = 2e5 + 5;

vector<int> edge[N];

void add(int u, int v) {
	edge[u].push_back(v);
}

void erase(vector<int> *v, int n) {
	for (int i = 1; i <= n; ++i) {
		vector<int>().swap(v[i]);
	}
}

ll a[N];

int dep[N];
int father[N];

void dfs(int x) {
	for (int i = 0; i < (int)edge[x].size(); ++i) {
		int to = edge[x][i];
		if (to == father[x]) {
			continue;
		}
		father[to] = x;
		dep[to] = dep[x] + 1;
		dfs(to);
	}
}

vector<int> node[N];

ll dp[N];

void solve() {
	int n;
	scanf("%d", &n);
	erase(edge, n);
	erase(node, n);
	memset(dp, 0, sizeof dp);
	for (int i = 2; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		add(x, i);
		add(i, x);
	}
	for (int i = 2; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	dfs(1);
	for (int i = 1; i <= n; ++i) {
		node[dep[i]].push_back(i);
	}
	ll ans = 0;
	for (int i = 1; !node[i].empty(); ++i) {
		ll m[4] = {inf, -inf, -inf, -inf};
		for (int j = 0; j < (int)node[i].size(); ++j) {
			int x = node[i][j];
			m[0] = min(m[0], a[x]);
			m[1] = max(m[1], a[x]);
			m[2] = max(m[2], dp[father[x]] - a[x]);
			m[3] = max(m[3], dp[father[x]] + a[x]);
		}
		for (int j = 0; j < (int)node[i].size(); ++j) {
			int x = node[i][j];
			dp[x] = max(max(a[x] - m[0] + dp[father[x]], m[1] - a[x] + dp[father[x]]), 
			max(m[2] + a[x], m[3] - a[x]));
			ans = max(ans, dp[x]);
//			printf("%d %d\n", x, dp[x]);
		}
	}
	printf("%lld\n", ans);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}
```

---

## 作者：冷却心 (赞：0)

阿姆罗烤羊第一人。夏亚，我正在干着贪得无厌的事情。

这不是唐诗题吗，个人感觉 2300*。

朴素 dp 状态 $f_{u,v}$ 表示红点在 $u$ 蓝点在 $v$ 的答案，状态数 $O(n^2)$，显然做不了。注意到蓝点的位置和上一层的状态无关，所以只记录红点，记 $f_u$ 表示红点在 $u$，蓝点在同一层的某个位置，并且**未计算**本层贡献的答案。显然逐层转移。记 $s_i$ 表示深度为 $i$ 的点集。设当前转移到深度为 $d$ 的点。有两种转移，设当前考虑点 $u \in s_d$，其父亲为 $p\in s_{d-1}$：

- 红点和蓝点在上一层未交换，上层红点为本层红点的父亲，若上层蓝点取在 $q$，那么 $f_u \gets f_p + |a_p - a_q|$，显然 $q$ 取上一层 $a_q$ 极值位置最优，转移 $O(1)$。
- 上一场红蓝交换，上层蓝点是本层红点的父亲，那么枚举上一层红点位置 $q$，转移 $f_u \gets f_q + |a_q-a_p|$，直接实现转移 $O(|s_d|^2)$，可以对 $s_d$ 按照 $a$ 值排序之后拆绝对值，前后扫一遍做到 $O(|s_d|\log |s_d|)$。

注意最后一层的贡献未计算，统计全局答案需要加上第一种转移的贡献。时间复杂度 $O(n\log n)$。

[https://codeforces.com/problemset/submission/1485/327162366](https://codeforces.com/problemset/submission/1485/327162366)

---

## 作者：ax_by_c (赞：0)

仔细分析操作，其实就是每次把两个棋子移到下一层，只要有某个棋子是原来某个棋子的儿子就合法。

显然考虑 DP，设 $f_x$ 表示某个棋子在 $x$ 时的最大得分。

转移即为 $f_{fa_x}+\lvert a_x-a_y\rvert\rightarrow f_x,f_y$。

显然把绝对值拆了，然后随便做。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll llinf=3e18;
const int N=2e5+5;
int n,fa[N],de[N];
vector<int>g[N],nds[N];
ll a[N],f[N];
void dfs(int u){
	nds[de[u]].pb(u);
	for(auto v:g[u]){
		de[v]=de[u]+1;
		dfs(v);
	}
}
void slv(){
	scanf("%d",&n);
	rep(i,0,n)g[i].clr(),nds[i].clr(),f[i]=0;
	rep(i,2,n)scanf("%d",&fa[i]),g[fa[i]].pb(i);
	rep(i,2,n)scanf("%lld",&a[i]);
	dfs(1);
	rep(i,1,n){
		ll mx1=-llinf,mx2=-llinf,mx3=-llinf,mx4=-llinf;
		for(auto x:nds[i])mx1=max(mx1,f[fa[x]]+a[x]),mx2=max(mx2,f[fa[x]]-a[x]),mx3=max(mx3,a[x]),mx4=max(mx4,-a[x]);
		for(auto x:nds[i])f[x]=max({mx1-a[x],mx2+a[x],f[fa[x]]-a[x]+mx3,f[fa[x]]+a[x]+mx4});
	}
	ll ans=-llinf;
	rep(i,1,n)ans=max(ans,f[i]);
	printf("%lld\n",ans);
}
void main(){
	int T=1;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：hegm (赞：0)

有点意思的题，感觉不应该是蓝色。

我们不妨抛下颜色把一个合法的方案选择的所有点提溜出来，容易发现，对于相邻层来说，只需要满足上层的两个点中的一个和下层的两个点中的一个是父子关系即可。

我们把过程倒过来，对于一个初始状态，我们任选两个叶子作为初始状态，每次选择两个点其中一个点的父亲，和上一层中的任意一个节点。

考虑设状态 $f_i$ 表示当前状态的两个点中其中有一个在 $i$ 。另一个节点具体在哪里不重要，因为我们的限制只有一个：存在一对父子关系。

因为对于一个选择状态 $(i,j)$，我们可以达到的状态为 $(fa_i,x)$ 或者 $(fa_j,x)$。其中 $x$ 为下一层，随便一个节点。

对于这个状态，我们一层一层的去更新。

考虑转移 $f_i$ 一定可以达到的状态为 $(fa_i,x)$。

对于 $(fa_i,x)$ 这个状态，我们需要更新 $f_{fa_i}$ 和 $f_x$。

对于更新 $f_{fa_i}$，我们的选择非常简单，选择下一层最大和最小的点权值（$mx,mn$）更新即可。 

$f_{fa_i}=f_i+\max(mx-w_{fa_i},w_{fa_i}-mn)$。

对于 $x$ 比较麻烦，因为 $x$ 是下一层全体节点，因此我们不妨将 $\text{abs}$ 拆开考虑。

将 $f_{x}=f_i+\begin{cases}w_x-w_{fa_i}\ (w_x>w_{fa_i})
\\
w_{fa_i}-w_x\ (w_{fa_i}<w_x)
\end{cases}$

因此我们按照 $w$，然后容易发现，每次更新拆成前缀更新后缀更新和单点更新三种，然后线性扫一遍就好。

复杂度 $O(n\log n)$。

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define int long long
#define make make_pair
#define N 200005
#define l(x) *s[x].begin()
#define r(x) *s[x].rbegin() 
#define inf 10000000000000000
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,t,a[N],f[N],fa[N],dep[N],mx,g[N];
vector<int> v[N],s[N];
void dfs(int now,int f)
{
	fa[now]=f;
	dep[now]=dep[f]+1;mx=max(mx,dep[now]);
	for(int x:v[now])if(x!=f)dfs(x,now);
}
bool cmp(int x,int y)
{
	return a[x]<a[y];
}
signed main()
{
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;i++)
		{
			v[i].clear();
			s[i].clear();
			f[i]=g[i]=0;
		}
		for(int i=2,x;i<=n;i++)
		{
			x=read();
			v[x].push_back(i);
			v[i].push_back(x);
		}
		for(int i=2;i<=n;i++)a[i]=read();
		dfs(1,0);
		for(int i=1;i<=n;i++)s[dep[i]].push_back(i);
		for(int i=1;i<=mx;i++)sort(s[i].begin(),s[i].end(),cmp);
		for(int x:s[mx])f[x]=max(a[x]-a[l(mx)],a[r(mx)]-a[x]);
		for(int i=mx;i>1;i--)
		{
			for(int x:s[i])g[fa[x]]=max(g[fa[x]],f[x]);
			int pos=-inf;
			for(int x:s[i-1])
			{
				f[x]=g[x]+max(a[r(i-1)]-a[x],a[x]-a[l(i-1)]);
				f[x]=max(f[x],pos+a[x]);
				pos=max(pos,g[x]-a[x]);
			}
			pos=-inf;
			for(int j=s[i-1].size()-1;j>=0;j--)
			{
				int x=s[i-1][j];
				f[x]=max(f[x],pos-a[x]);
				pos=max(pos,g[x]+a[x]);
			}
		}
		cout<<f[1]<<"\n";
	}
	return 0;
}

```

---

## 作者：SmileMask (赞：0)

对于固定红点 $u$，则蓝点只会是同层结点，不妨记 $f_u$ 为 $u$ 为红点的最大得分和。

枚举上次是否交换，转移方程有：

$f_{u}=\max(f_{fa_u}+|a_u-a_v|,\max_{dep_u=dep_v} f_{fa_v}+|a_u-a_v|)$

前者可以维护同层 $a$ 的最大值与最小值转移，而后者可以拆绝对值得到：
$$
f_{u}=\max(f_{fa_v}+a_u-a_v,f_{fa_v}+a_v-a_u)
$$
维护同层的 $f_{fa_v}-a_v,f_{fa_v}+a_v$ 的最大值直接转移即可。

总复杂度 $O(n)$。

---

## 作者：liujiaxi123456 (赞：0)

## 关键词：DP，rank1 代码
### 思路：
首先选择算法大致方向，由于操作较为复杂，先往 DP 方面想。

先设出最基本状态：第 $i$ 步，红色节点的位置 $u$，蓝色节点的位置 $v$。转移时从 $i-1$，$fa_u$，枚举蓝色上一层位置转移。

一步步优化，第 $i$ 步显然先去掉。

由于蓝色点现在或上一层的位置**都没有限制**，并且**答案与之无关**，它唯一的作用是**判断是否交换**，而这其实可以由红色点是否在它父亲的子树内来判断，因此不用记录蓝色点位置。

此时，设 $f_u$ 表示红色点在 $u$ 上时最大得分，$v$ 表示蓝色点。

不交换的情况：

- $ f_u = \max \left \{ f_{fa_u}+|a_u-a_v| \right \}$

- 只用维护与 $u$ 同层的点的最大值、最小值即可去掉绝对值。

交换的情况：

- $ f_u = \max \left \{ f_{fa_v}+|a_u-a_v| \right \}$

- 因为 $|a_u-a_v| = \max(a_u-a_v, -a_u+a_v)$。

- 所以 $f_u = \begin{cases}
  & a_u + \max(f_{fa_v}-a_v)\\
  & -a_u + \max(f_{fa_v}+a_v)
  \end{cases}$
  
- 维护一下与 $u$ 同层的 $\max(f_{fa_v}-a_v)$ 与 $\max(f_{fa_v}+a_v)$ 即可。

### 实现：
因为转移与深度有关，考虑用 bfs 的方式把最后两层存下来，一层一层的更新即可。
### 复杂度：
时间：$O(n)$。

空间：$O(n)$。
### Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 2e5+5;

namespace EDGE {
	int sz, head[Maxn];
	struct Edge { int next, to; } edge[Maxn*2];
	inline void Add_edge(int u, int v) {
		edge[++sz] = {head[u], v};
		head[u] = sz;
	}
	inline void edge_memset(int N) { memset(head+1, 0, N*4), sz = 0; }
} using namespace EDGE;

namespace Josh_zmf {
	
	int N, a[Maxn], stk[2][Maxn], fa[Maxn];
	ll f[Maxn];

	inline void bfs(int u) {
		int top[2] = {0, 0}, maxx, minn; ll max1, max2; 
		stk[0][++top[0]] = u;
		for(bool now=1; top[now^1]; now^=1) {
			maxx = -INT_MAX, minn = INT_MAX, max1 = max2 = -INT64_MAX;
			for(int asdf=1; asdf<=top[now^1]; asdf++) {
				u = stk[now^1][asdf];
				for(int i=head[u], v; i; i=edge[i].next) {
					v = edge[i].to;
					if(v == fa[u])	continue;
					fa[v] = u, stk[now][++top[now]] = v;
				}
				maxx = max(maxx, a[u]), minn = min(minn, a[u]);
				max1 = max(max1, f[fa[u]]-a[u]), max2 = max(max2, f[fa[u]]+a[u]);
			}
			for(; top[now^1]; top[now^1]--) {
				u = stk[now^1][top[now^1]];
				f[u] = max({f[fa[u]]+maxx-a[u], f[fa[u]]+a[u]-minn, a[u]+max1, max2-a[u]});
			}
		}
	}

	inline int main() {
		cin>> N, edge_memset(N), a[1] = 1;
		for(int i=2, u; i<=N; i++)	cin>> u, Add_edge(u, i), Add_edge(i, u);
		for(int i=2; i<=N; i++)	cin>> a[i];
		bfs(1); ll ans = 0;
		for(int i=1; i<=N; i++)	ans = max(ans, f[i]);
		cout<< ans<< '\n';
		return 0;
	}

}

int main() {
	int T; cin>> T;
	while(T--)	Josh_zmf::main();
	return 0;
}
```
### 结语：
都看到这里了，点个赞再走吧。：）

---

## 作者：A_Sunny_Day (赞：0)

前置知识：dp，CDQ 分治

显然是树形 dp 。

注意到我们顺着题目进行 dp，那么交换操作将会非常的烦人。所以我们考虑倒着进行 dp。

正着做的流程应该是：移动，计算贡献，交换。

那么倒着做的流程就应该是：交换，计算贡献，移动。

注意到倒着做的时候蓝色点在哪里并不重要，因为蓝色点可以出现在任意想要的位置，所以我们设 $f_i$  表示**红色**在 $i$ 这个节点时最大的贡献。由于我们是倒着做的，所以答案就是 $f_i$。

此外，我们是从下往上爬，所以移动一定是往父亲节点移动。

那么暴力转移可以这么转移：设 $fa(x)$ 表示 $x$ 的父亲，假设我们要将 $f_u$ 转移到 $f_{fa(u)}$，枚举 $v$ 为同一层的两个点（可以相同，表示蓝红走到一个点了）。设 $V=\max(f_u,f_v)+|
a_u-a_v|$ 。那么我们就可以用 $V$ 来更新 $f_{fa(u)}$，即 $f_{fa(u)}=\max(V,f_{fa(u)})$。

取 $\max(f_u,f_v)$ 是因为我们倒着做的流程是先交换再计算贡献最后移动的，所以 $u,v$ 都可能是红色的点。而 $|a_u-a_v|$ 就是贡献。

注意到我们这么转移最坏是 $O(n^2)$ 的。考虑优化。

要想优化，就得快速处理出最大的 $V$。也就是针对每一个 $u$，我们需要快速找到一个同层节点 $v$ 使得 $\max(f_u,f_v)+|a_u-a_v|$ 最大。这条式子中的 $\max(f_u,f_v)$ 与 $|a_u-a_v |$ 显得很棘手。

如果我们一开始按照 $f$ 值大小对一层的节点排序，那么 $\max$ 就可以去掉了，线性分左右两部分转移即可。但是 $|a_u-a_v|$ 依然无法很好解决。如果一开始按照 $a$ 值大小排序，那么 $|a_u,a_v|$ 就可以去掉了，同样线性枚举分左右两部分转移，同样的 $\max(f_u,f_v)$ 无法很好解决。

而实际上这个式子有点像二维偏序，如果我们能同时保证 $f,a$ 的有序，那么这个式子就很好维护了。所以我们可以使用 cdq 分治来维护这个式子。

我们将同层编号存储在 $A$ 中，并且在外层以按 $f$ 值进行排序， 在内层按 $a$ 值排序。也就是分治前按 $f$ 排序。在分治时，将 $[l,mid],[mid+1,r]$ 这两个区间按 $a$ 值排序。

由于 $[mid+1,r]$ 中任意的一个点的 $f$ 值都是大于 $[l,mid]$ 中任意一个点的 $f$ 值， 我们设 $u\in[mid+1,r]$ 为当前要用以更新其父亲的点， $V=\max(|a_u-a_{A(l)}|,|a_u-a_{A(mid)}|)$。那么 $f_{fa(u)}=\max(f_{fa(u)},f_u+V)$。

我们设 $u\in[l,mid]$ 为当前要用以更新其父亲的点，设 $pos\in[mid+1,r]$ 表示 $pos $ 为 $[mid+1,r] $ 中最后一个满足 $a_{i}\le a_u$ 的点的下标。这个可以用二分在 $O(\log n)$ 求出。然后我们求出前缀最大值 $L_{pos}=\max_{i=mid+1}^{pos}(f_i-a_i)$，以及后缀最大值 $R_{pos+1}=\max_{i=pos+1}^{r}(f_i+a_i)$。这两个可以$O(n)$ 预处理且 $O(1)$ 查询。那么 $f_{fa(u)}=\max(L_{pos}+a_u,R_{pos+1}-a_u)$。

总时间复杂度就是 $O(n\log^2 n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 2e5+5;
ll dp[MAXN],W[MAXN],L[MAXN],R[MAXN];
int n,f[MAXN],dep[MAXN],mxdep,A[MAXN];
vector <int> e[MAXN],node[MAXN];
void dfs(int p,int fa)
{
	dep[p]=dep[fa]+1;f[p]=fa;
	mxdep=max(mxdep,dep[p]);
	for(int i=0;i<e[p].size();++i)
	{
		int to=e[p][i];
		if(to==fa) continue;
		dfs(to,p);
	}
	node[dep[p]].push_back(p);
}
bool cmp1(int x,int y)
{
	return dp[x]<dp[y];
}
bool cmp2(int x,int y)
{
	return W[x]<W[y];
}
void cdq_solve(int l,int r)
{
	if(l==r)
	{
		dp[f[A[l]]]=max(dp[f[A[l]]],dp[A[l]]);
		return ;
	}
	int mid=l+r>>1;
	cdq_solve(l,mid);cdq_solve(mid+1,r);
	sort(A+l,A+mid+1,cmp2);sort(A+mid+1,A+r+1,cmp2);
	for(int i=mid+1;i<=r;++i)
	{
		L[i]=dp[A[i]]-W[A[i]];
		R[i]=dp[A[i]]+W[A[i]];
		if(i>mid+1) L[i]=max(L[i],L[i-1]);
		ll V=dp[A[i]]+max(abs(W[A[i]]-W[A[mid]]),abs(W[A[i]]-W[A[l]]));
		dp[f[A[i]]]=max(dp[f[A[i]]],V);
	}
	for(int i=r-1;i>=mid+1;--i)
		R[i]=max(R[i],R[i+1]);
	for(int i=l;i<=mid;++i)
	{
		int pos=upper_bound(A+mid+1,A+r+1,A[i],cmp2)-A-1;
		if(pos>r) pos=r;
		ll V=0;
		if(pos>=mid+1) V=max(V,L[pos]+W[A[i]]);
		if(pos+1<=r) V=max(V,R[pos+1]-W[A[i]]);
		dp[f[A[i]]]=max(dp[f[A[i]]],V);
	}
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(dp,-0x3f,sizeof dp);
		for(int i=1;i<=n;++i) e[i].clear();
		for(int i=1;i<=n;++i) node[i].clear();
		scanf("%d",&n);
		for(int i=2;i<=n;++i)
		{
			int v;scanf("%d",&v);
			e[i].push_back(v);
			e[v].push_back(i);
		}
		for(int i=2;i<=n;++i) scanf("%lld",&W[i]);
		mxdep=0;
		dfs(1,0);
		for(int i=0;i<node[mxdep].size();++i)
			dp[node[mxdep][i]]=0;
		for(int d=mxdep;d>1;--d)
		{
			int tot=0;
			for(int i=0;i<node[d].size();++i)
				A[++tot]=node[d][i];
			sort(A+1,A+1+tot,cmp1);
			cdq_solve(1,tot);
		}
		printf("%lld\n",dp[1]);
	}

	return 0;
}
```





---

