# [ABC144F] Fork in the Road

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc144/tasks/abc144_f

$ N $ 個の部屋と、$ M $ 本の一方向にのみ通れる通路から成る洞窟があります。部屋には $ 1 $ から $ N $ までの番号がついています。

高橋君はいま部屋 $ 1 $ におり、部屋 $ N $ が出口へと繋がっています。$ i $ 番目の通路は部屋 $ s_i $ と部屋 $ t_i $ ( $ s_i $ &lt; $ t_i $ ) を繋いでおり、部屋 $ s_i $ から部屋 $ t_i $ の方向にのみ通ることが出来ます。部屋 $ N $ 以外の各部屋について、その部屋から出る通路が少なくとも $ 1 $ つ存在することが分かっています。

高橋君はこの洞窟から脱出を試みます。部屋に到達するたびに (脱出開始時は部屋 $ 1 $ に到達したとみなします)、高橋君はその部屋から出る通路のうち等確率でランダムに $ 1 $ つを選んで進みます。

高橋君の友達の青木君は、高橋君が部屋 $ 1 $ から移動する前に $ 1 $ つだけ通路を塞ぐ (または何もしない) ことが出来ます。ただし、高橋君が部屋 $ N $ に到達できなくなる可能性が生じるような通路の塞ぎ方は出来ません。

高橋君が部屋 $ N $ に到達するまでに通る通路の数の期待値を $ E $ とします。青木君が $ E $ を最小化するような選択をしたときの $ E $ の値を求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =\ N\ <\ =\ 600 $
- $ N-1\ <\ =\ M\ <\ =\ \frac{N(N-1)}{2} $
- $ s_i\ <\ t_i $
- $ i\ \neq\ j $ のとき、$ (s_i,\ t_i)\ \neq\ (s_j,\ t_j) $ (21:23 追記)
- 任意の $ v\ =\ 1,\ 2,\ ...,\ N-1 $ に対し、ある $ i $ が存在して $ v\ =\ s_i $

### Sample Explanation 1

青木君が部屋 $ 1 $ から部屋 $ 2 $ への通路を塞ぐと、高橋君は $ \frac{1}{2} $ の確率で `1` → `3` → `4` という経路を辿り、 $ \frac{1}{2} $ の確率で `1` → `4` という経路を辿ります。このとき $ E\ =\ 1.5 $ であり、これが $ E $ がとりうる最小の値です。

### Sample Explanation 2

どの通路を塞いでも部屋 $ N $ に到達出来なくなるため、青木君は通路を塞ぐことは出来ません。

## 样例 #1

### 输入

```
4 6
1 4
2 3
1 3
1 2
3 4
2 4```

### 输出

```
1.5000000000```

## 样例 #2

### 输入

```
3 2
1 2
2 3```

### 输出

```
2.0000000000```

## 样例 #3

### 输入

```
10 33
3 7
5 10
8 9
1 10
4 6
2 5
1 7
6 10
1 4
1 3
8 10
1 5
2 6
6 9
5 6
5 8
3 6
4 8
2 7
2 9
6 7
1 2
5 9
6 8
9 10
3 9
7 8
4 5
2 10
5 7
3 5
4 7
4 9```

### 输出

```
3.0133333333```

# 题解

## 作者：CYZZ (赞：5)

# [Fork in the Road](https://www.luogu.com.cn/problem/AT_abc144_f)
update in 2024.5.14：感觉一年前的自己太 naive 了，过来补充一下。
## 思路
首先，题目中 “$s_i<t_i$” 告诉我们图是一个 DAG。

考虑不删边的情况，设 $f_u$ 表示从 $u$ 走到 $n$ 的期望步数，就是 DAG 上随机游走。显然有： 
$$f_u= \frac{\sum f_{to}}{out_u}+1$$
如果暴力枚举删除哪一条边，复杂度 $\mathcal{O}(M^2)$ ，考虑优化。

结论：对于一个点，应该把它连接**期望值最大**的点对应的边删掉。

口胡证明：考虑删除一条边 $(u,v)$ 对 $f$ 的影响。显然 $f$ 值会产生变化的的点集为 $u$ 和 $u$ 的前驱，即**能到达 $u$ 的点集**。分类讨论：

- 对于 $u$，$f_u$ 的变化为 $\frac{\sum f_{to}}{out_u}+1\rightarrow\frac{\sum\limits_{to\neq v}f_{to}}{out_u-1}+1$。分母是固定的，$f_v$ 越大，$\sum\limits_{to\neq v}f_{to}$ 越小，$f_u$ 越小。

- 对于 $u$ 的前驱 $pre$，$f_{pre}$ 的转移和转移系数完全不变，所以 $f_u$ 越小，$f_{pre}$ 越小。

综上，对于一个点 $u$，$f_v$ 越大，$f_1$ 也就是答案越小。

那么解法就出来了：先跑一遍 dp，枚举每个点 $u$，找到 $u$ 的 $f$ 值最大的后继 $v$，删除 $(u,v)$ 后再跑一遍 dp。 

注意：不能删除一条边使 $1$ 无法到达 $n$，也就是每个点出发都能到达 $n$，所以不考虑出度为 $1$ 的点即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,tot,head[605],out[605],maxx;
double f[605],dp[605],ans;
struct Edge
{
    int next,to;
}e[200005];
void add_edge(int u,int v)
{
    e[++tot].next=head[u];
    e[tot].to=v;
    head[u]=tot;
}
void solve(int nod)
{
    maxx=0;
    out[nod]--;//删边
    for(int i=head[nod];i;i=e[i].next)
    {
        int v=e[i].to;
        if(f[v]>f[maxx])
            maxx=v;//寻找期望值最大的边
    }
    memset(dp,0,sizeof dp);
    for(int u=n;u;u--)
    {
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].to;
            if(u==nod&&v==maxx)//被删除的边跳过
                continue;
            dp[u]+=(dp[v]+1)/out[u];
        }
    }
    out[nod]++;//边加回来
    if(dp[1])
        ans=min(ans,dp[1]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        out[x]++;
    }
    for(int u=n-1;u;u--)
    {
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].to;
            f[u]+=(f[v]+1)/out[u];//初始的期望值
        }
    }
    ans=f[1];
    for(int i=1;i<n;i++)
    {
		if(out[i]==1)//无法到达的情况
			continue;
        solve(i);
    }
    printf("%.10lf",ans);
}
```

---

## 作者：zhaoyp (赞：5)

### upd on 23.08.11 修改笔误

[ABC144F](https://atcoder.jp/contests/abc144/tasks/abc144_f)
$\text{Difficulty : 2189}$ ：$n$ 个点，$m$ 条单向路径，由编号小的点指向编号大的点，每次会从当前点的通道中等概率随机选择一个通道行走。可以至多删去一条边，求 $1$ 到 $n$ 的期望步数最小值。

------------


记 $f_u$ 为 $u$ 到 $n$ 的期望步数。

有 $f_u = \sum\limits_{v}\dfrac{f_v+1}{d_u}$，其中 $d_u$ 为 $u$ 的出度。

暴力是枚举删去的边然后做期望 dp，时间复杂度 $O(m^2)$。

考虑优化。

为了使期望步数最小，观察柿子可以发现最小值取时，必然是删去 $f_v$ 最大的边。

枚举删去哪一个点的出边。

然后做期望 dp，时间复杂度 $O(mn)$。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 606; 
int n,m,u,v,de[maxn];
double g[maxn],f[maxn],ans;
vector <int> G[maxn];
inline int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while(ch < '0'||ch > '9'){if(ch == '-'){f = -1;}ch = getchar();}
	while(ch <= '9'&&ch >= '0'){x = (x << 1) + (x << 3) + ch - '0',ch = getchar();}
	return f * x;
}
void input()
{
	n = read(),m = read();
	for(int i = 1;i <= m;i++)
		u = read(),v = read(),G[u].push_back(v),de[u]++;
}
void prefix()
{
	for(int i = n - 1;i;i--)
		for(int j = 0;j < (int) G[i].size();j++)
			g[i] += 1.0 * (g[G[i][j]] + 1) / de[i];
	ans = g[1];
}
void solve(int u)
{
	if(G[u].size() == 0)
		return ;
	v = G[u][0];
	for(int j = 1;j < (int) G[u].size();j++)
		if(g[G[u][j]] > g[v])
			v = G[u][j];
	de[u]--;
	for(int i = 1;i <= n;i++)
		f[i] = -1;
	f[n] = 0;
	for(int i = n - 1;i;i--)
		for(int j = 0;j < (int) G[i].size();j++)
			if(i != u||G[i][j] != v)
			{
				if(f[G[i][j]] == -1)
				{
					f[i] = -1;break;
				}
				if(f[i] == -1)
					f[i] = 0;
				f[i] += 1.0 * (f[G[i][j]] + 1) / de[i];
			}
	if(f[1] != -1)
		ans = min(ans,f[1]);
	de[u]++;
}
int main()
{
	input();
	prefix();
	for(int i = 1;i <= n;i++)
		solve(i);
	printf("%.11lf",ans);
	return 0 ;
}
/*
CSP-S2022 RP++
*/
```

---

## 作者：f_hxr_ (赞：2)

[**洛谷传送门**](https://www.luogu.com.cn/problem/AT_abc144_f) [**AT 传送门**](https://atcoder.jp/contests/abc144/tasks/abc144_f)

其实这道题挺水的，我们只要把[ P4316 ](https://www.luogu.com.cn/problem/P4316)的代码稍微改动即可 AC 本题。

强烈建议先切~~双倍经验~~ P4316。

切完了吗？好，现在正文开始。

我们定义 $out_u$ 为结点 $u$ 的出度，$f_u$ 为高桥从结点 $u$ 走到结点 $n$ 花费的距离的期望。根据期望的性质，有：

$$f_u=\sum_{u \to v \text{存在}}\dfrac{f_v+1}{out_u}$$

暴力枚举每一条边然后删掉进行期望 DP，时间复杂度 $O(M^2)$。

考虑优化。我们发现要删去一条边 $u \to v$ 使得 $f_u$ 最小，那么其对应的 $f_v$ 要最大。

因此，我们可以预先跑一遍期望 DP。然后对于每一个结点 $u$，找出一个与其连接的 $f_v$ 最大的结点 $v$，删去边 $u \to v$，跑一遍期望 DP，最后更新答案即可。

注意到不能堵住一条边使得高桥**有可能**到不了终点，所以我们要保证每一个点的出度大于等于 1 。将出度为 1 的点跳过即可。

特别的，如果每一个结点的出度都是 1，那么我们只需要在第一次期望 DP 时直接输出答案即可。

时间复杂度 $O(NM)$。

code：

（注意，虽然一下代码可以 [AC](https://atcoder.jp/contests/abc144/submissions/44652608) 但由于评测机波动，同一份代码，有时会 [TLE](https://atcoder.jp/contests/abc144/submissions/44654519) 2~3 个点。）

![](https://cdn.luogu.com.cn/upload/image_hosting/inghvyri.png)

```
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL maxn=200005;
LL N,M;
LL head[maxn],nxt[maxn],to[maxn],cnt;
LL head2[maxn],nxt2[maxn],to2[maxn],cnt2;
LL deg[maxn];
double f[maxn],G[maxn],ans=1e9+7;
void edge(LL U,LL V){
	nxt[++cnt]=head[U];//正边 
	to[cnt]=V;head[U]=cnt;
	nxt2[++cnt2]=head2[V];//反边
	to2[cnt2]=U;head2[V]=cnt2;
	return;
}
LL f_hxr_(LL v){
	LL ret=0;
	for(int i=head[v];i;i=nxt[i])
		if(G[to[i]]>G[to[ret]])ret=i;
	return ret;
}
void Topsort(LL v){
	memset(f,0,sizeof(f));
	LL T[maxn];queue<LL>q;
	LL e=f_hxr_(v);
	deg[v]--;
	for(LL i=1;i<=N;i++)T[i]=deg[i];
	q.push(N);
	while(!q.empty()){
		LL x=q.front();q.pop();
		for(int i=head2[x];i;i=nxt2[i]){
			if(i==e)continue;
			LL p=to2[i];
			f[p]+=(f[x]+1.0)/deg[p];
			if(--T[p]==0)q.push(p);
		}
	}
	deg[v]++;
	return;
}
int main(){
	scanf("%lld%lld",&N,&M);
	for(int i=1;i<=M;i++){
		LL a,b;scanf("%lld%lld",&a,&b);
		edge(a,b);deg[a]++;
	}
	Topsort(0);
	LL T=0;
	for(int i=1;i<=N;i++){
		G[i]=f[i];
		if(deg[i]==0)T++; 
	}
	if(T==N){printf("%.6f",f[1]);return 0;}
	for(int i=1;i<=N;i++){
		if(deg[i]==1)continue;
		Topsort(i);
		ans=min(ans,f[1]);
	}
	printf("%.6f",ans);
	return 0;
}
```

---

## 作者：lzqy_ (赞：1)

爆一下标，$n,m$ 可以开到 $10^6$。

不带修改是好做的，设 $f_x$ 表示 $1\rightarrow x$ 的概率，$g_x$ 表示 $1\rightarrow x$ 的期望，拓扑排序转移即可。考虑分析删去一条边 $(u,v)$ 的影响。

先 $f,g$ 肯定正反分别跑一遍，即 $f_x,g_x$ 表示 $1\rightarrow x$，$F_x,G_x$ 表示 $x\rightarrow n$。

首先经过边 $(u,v)$ 的贡献会被减去。即 $\frac{g_u}{sz_u}+\frac{G_v+1}{f_usz_u}$。

其次，经过点 $u$ 但是不经过 $(u,v)$ 的边的占比会增大。考虑对于一条路径 $x_1,x_2,\dots,x_k$，其权重为 $\prod sz_{x_i}$。发现这些路径的权重变化是一致的，即乘上 $\frac{sz_x}{sz_x-1}$。因此相当于加上 $\frac 1 {sz_u-1}(g_u+f_uG_u-S)$。其中 $S$ 是是经过边 $(u,v)$ 的步数期望。

时间复杂度 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
#define db double
#define il inline
using namespace std;
const int maxn=610;
const db eps=1e-10;
il int read(){
    int x=0;
    char c=getchar();
    for(;!(c>='0'&&c<='9');c=getchar());
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+c-'0';
    return x;
}
db f1[maxn],g1[maxn];
db f2[maxn],g2[maxn];
int d1[maxn],d2[maxn];
int len1[maxn],len2[maxn];
vector<int>v1[maxn],v2[maxn];
int n,m;
queue<int>q;
void tp1(){
    f1[1]=1,g1[1]=0;
    for(int i=1;i<=n;i++)
    	for(int j=0;j<v1[i].size();j++){
    		f1[v1[i][j]]+=f1[i]/len1[i];
    		g1[v1[i][j]]+=(f1[i]+g1[i])/len1[i];
		}
}
void tp2(){
    f2[n]=1,g2[n]=0;
    for(int i=n;i;i--)
    	for(int j=0;j<v2[i].size();j++){
    		f2[v2[i][j]]+=f2[i]/len1[v2[i][j]];
    		g2[v2[i][j]]+=(f2[i]+g2[i])/len1[v2[i][j]];
		}
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        v1[x].push_back(y),d1[y]++;
        v2[y].push_back(x),d2[x]++;
    }
    for(int i=1;i<=n;i++){
        len1[i]=v1[i].size();
        len2[i]=v2[i].size();
    }tp1(),tp2();
    db E=g1[n],mE=g1[n];);
    for(int i=1;i<=n;i++){
        if(len1[i]<=1) continue;
        for(int j=0;j<v1[i].size();j++){
        	db p1=1.0/len1[i],p2=(len1[i]-1.0)/len1[i];
            db t1=(g1[i]*p1+(g2[v1[i][j]]+1)*f1[i]*p1); 
            db t2=(g1[i]+g2[i]*f1[i]); t2-=t1;
			E=min(E,mE-t1-t2+t2*len1[i]/(len1[i]-1.0));
        }
    }
    printf("%.10lf\n",E);
    return 0;
}
```

---

## 作者：Composite_Function (赞：0)

注意到一眼 DAG 上期望 dp。关键在于删哪一条边。

注意到删的那条边 $u \rightarrow v$ 在走过 $u$ 以后便没有后效性了，同时这条边不会影响 $u$ 之前的转移。于是我们立刻得到一个贪心：对于每个 $u$，选择 $u \rightarrow v$ 中期望边数最大的 $v$。

然后就做完了。

---

```cpp
#include <bits/stdc++.h>
using namespace std;

struct FastIO {
	inline FastIO& operator >> (short& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (int& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (long long& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (double& x) {
		x = 0;
		char f = 0, ch = getchar();
		double d = 0.1;
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = x * 10 + (ch ^ 48), ch = getchar();
		if (ch == '.') {
			ch = getchar();
			while (ch <= '9' && ch >= '0') x += d * (ch ^ 48), d *= 0.1, ch = getchar();
		}
		return x = (f ? -x : x), *this;
	}
} rin;

#define ll long long
#define uint unsigned int
#define reg register
#define ld long double
#define uint unsigned int
#define ull unsigned long long
#define qint const int&
#define qll const ll&
#define quint cosnt uint&
#define qull const ull&
#define endl "\n"

inline void qmod(int& x, const int& mod) {
	x = x >= mod? x - mod : x;
}

const int N = 605;
int n, m, mx[N];
vector<int> to[N];
double f[N];

signed main() {
	rin >> n >> m;
	for (int i = 1, u, v; i <= m; ++i) {
		rin >> u >> v;
		to[u].push_back(v);
	}
	f[n] = 0;
	for (int i = n - 1; i >= 1; --i) {
		for (int v : to[i]) {
			f[i] += f[v] + 1;
			if (f[v] > f[mx[i]]) mx[i] = v;
		}
		f[i] /= to[i].size();
	}
	double ans = f[1];
	for (int i = 1; i < n; ++i) {
		if (to[i].size() == 1) continue;
		f[n] = 0;
		for (int j = n - 1; j >= 1; --j) {
			f[j] = 0;
			for (int v : to[j]) {
				if (j == i && v == mx[i]) continue;
				f[j] += f[v] + 1;
			}
			f[j] /= to[j].size() - (j == i);
		}
		ans = min(ans, f[1]);
	}
	cout << setprecision(10) << fixed << ans << endl;
	return 0;
}
```

---

