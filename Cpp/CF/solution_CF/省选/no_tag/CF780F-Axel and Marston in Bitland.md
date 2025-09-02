# Axel and Marston in Bitland

## 题目描述

A couple of friends, Axel and Marston are travelling across the country of Bitland. There are $ n $ towns in Bitland, with some pairs of towns connected by one-directional roads. Each road in Bitland is either a pedestrian road or a bike road. There can be multiple roads between any pair of towns, and may even be a road from a town to itself. However, no pair of roads shares the starting and the destination towns along with their types simultaneously.

The friends are now located in the town 1 and are planning the travel route. Axel enjoys walking, while Marston prefers biking. In order to choose a route diverse and equally interesting for both friends, they have agreed upon the following procedure for choosing the road types during the travel:

- The route starts with a pedestrian route.
- Suppose that a beginning of the route is written in a string $ s $ of letters P (pedestrain road) and B (biking road). Then, the string ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF780F/cef16389b26df3f7c3105894b69565df69e4485d.png) is appended to $ s $ , where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF780F/cef16389b26df3f7c3105894b69565df69e4485d.png) stands for the string $ s $ with each character changed to opposite (that is, all pedestrian roads changed to bike roads, and vice versa).

In the first few steps the route will look as follows: P, PB, PBBP, PBBPBPPB, PBBPBPPBBPPBPBBP, and so on.

After that the friends start travelling from the town 1 via Bitlandian roads, choosing the next road according to the next character of their route type each time. If it is impossible to choose the next road, the friends terminate their travel and fly home instead.

Help the friends to find the longest possible route that can be travelled along roads of Bitland according to the road types choosing procedure described above. If there is such a route with more than $ 10^{18} $ roads in it, print -1 instead.

## 说明/提示

In the first sample we can obtain a route of length 3 by travelling along the road 1 from town 1 to town 2, and then following the road 2 twice from town 2 to itself.

In the second sample we can obtain an arbitrarily long route by travelling the road 1 first, and then choosing road 2 or 3 depending on the necessary type.

## 样例 #1

### 输入

```
2 2
1 2 0
2 2 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 3
1 2 0
2 2 1
2 2 0
```

### 输出

```
-1
```

# 题解

## 作者：是个汉子 (赞：12)

本蒟蒻觉得题解中二位大佬讲的过快，所以将一些地方写的详细一点。

### Solution

首先，能够比较明显的看出来，它的路径类型都是形如 $2^i$ ，所以我们能够想到倍增。

然后我们观察数据范围，发现 $n\leq 500$ 。~~我去，那我乱搞不就行了~~

考虑**倍增的DP**，设状态 $dp[0/1][s][u][v]$ 为从 $u$ 到 $v$ 存在一条以 $0/1$ 开头，长度为 $2^s$ 的路径，那么状态转移方程为 $dp[0/1][s][u][v]=dp[0/1][s-1][u][k]\vee dp[1/0][s-1][k][v]$ ，其中 $k$ 为中间转移点。

然后考虑如何计算答案，因为二进制的某个性质，当前位有 $1$ 要比后面都是 $1$ 还大，所以从高位向低位贪心，并用一个 $tmp$ 来表示状态，及时更新。

细节：因为大于 $10^{18}$ 就输出 $-1$ ，所以开 $long~long$ ，并在统计答案的时候及时判断。

### 代码

```c++
#include<cmath>
#include<bitset>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long

using namespace std;
const int N=510;
const ll INF=1e18;
int n,m,now;
ll ans,pow2[100];
bitset<N> f[2][70][N],g,tmp;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int main(){
    n=read();m=read();
    for(int i=1,u,v,w;i<=m;i++){
        u=read();v=read();w=read();
        f[w][0][u][v]=1;
    }
    for(int i=1;i<=60;i++)
        for(int u=1;u<=n;u++)
            for(int v=1;v<=n;v++){
                if(f[0][i-1][u][v]!=0) f[0][i][u]|=f[1][i-1][v];
                if(f[1][i-1][u][v]!=0) f[1][i][u]|=f[0][i-1][v];
            }
    if(f[0][60][1].count()){
        puts("-1");
        return 0;
    }
    now=0;tmp[1]=1;pow2[0]=1;
    for(int i=1;i<=60;i++) pow2[i]=pow2[i-1]*2;
    for(int i=60;i>=0;i--){
        g.reset();
        for(int j=1;j<=n;j++)
            if(tmp[j]) g|=f[now][i][j];
        if(g.count()!=0){
            now^=1;tmp=g;
            ans+=pow2[i];
        }
    }
    if(ans>INF) puts("-1");
    else printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：Enzyme125 (赞：3)

题目这个构造方式----
倍增模型。

考虑dp。
$dp[s][0/1][u][v]$ 表示是否存在长度$2^s$的从$u$到$v$的路。

转移方程

$dp[s][0/1][u][v] = dp[s - 1][0/1][u][k] \vee dp[s - 1][1/0][k][v] $


中间bitset压位。

AC代码(327ms)

```C++
#include<cstdio>
#include<bitset>
#include<cctype>
using namespace std;
#define debug(...) fprintf(stderr,__VA_ARGS__)
typedef long long ll;

inline char nc(){ static char buf[100000] , *p1,*p2; return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,100000,stdin),p1 == p2) ? EOF: *p1++;}
template<class T>inline void rd(T & x) { x = 0;char ch = nc();for(;!isdigit(ch);ch = nc()); for(;isdigit(ch);ch = nc()) x = x * 10 - 48 + ch;}


const int lev = 63;
const int maxn = 500 + 10;
const ll inf = (ll)(1e18);
int n,m;

bitset<maxn> dp[lev][2][maxn] , pre,g;
ll ans;

int main(){
	int n,m; rd(n); rd(m);
	for(int i = 0,u,v,t;i < m;i++){
		rd(u); rd(v); rd(t);
		dp[0][t][u][v] = 1;
	}
	for(int s = 1;s <= 60;s++)
		for(int j = 0;j < 2;j++)
			for(int u = 1;u <= n;u++)
				for(int v = 1;v <= n;v++)
					if(dp[s - 1][j][u][v]) dp[s][j][u] |= dp[s - 1][j ^ 1][v];
	for(int i = 1;i <= n;i++) if(dp[60][0][1][i]) return !printf("-1");
	int t = 0; pre[1] = 1; 
	for(int i = 59;i >= 0;i--){
		g = 0;
		for(int j = 1;j <= n;j++) if(pre[j]) g |= dp[i][t][j];
		if(g.count()) {
			pre = g; t ^= 1; ans += (1ll << i);
			if(ans > inf) return !printf("-1");
		}
	}
	if(ans > inf) return !printf("-1");
	return !printf("%I64d\n",ans);
}
```

---

## 作者：Provicy (赞：2)

$\text{Problem}:$[Axel and Marston in Bitland](https://codeforces.com/problemset/problem/780/F)

$\text{Solution}:$

记一条路径是好的，即：它的长度为 $2^{k}$，且这段路径可以通过翻转（即将 $P$ 变成 $B$，$B$ 变成 $P$）如果是答案，它是合法的，即这段路径形如 $PBBP$，$BPPB$。我们发现，好的路径当长度固定时，它的形式只和第一个字符是 $P$ 或是 $Q$ 有关。那么答案路径就可以表示成若干个好的路径按顺序拼接在一起，具体的，设答案路径长度为 $len$，则有：

$len=2^{k_{1}}(st.P)+2^{k_{2}}(st.B)+2^{k_{3}}(st.P)...,k_{1}>k_{2}>k_{3}...$

设 $F_{i,j,k,s}$ 表示从 $i$ 到 $j$，是否存在长度为 $2^{k}$，以 $s$ 为第一条边的好路径，容易得到转移：

$F_{i,j,k,s}|=(F_{i,x,k-1,s}\&F_{x,j,k-1,!s}),(1\leq x \leq n)$

求答案时，我们从大到小枚举 $k$，从满足当前条件的点，转移到满足 $k$ 条件的点。如果点集不空，则更新点集，并且将 $2^k$ 计入答案。

但是 $F$ 转移的时间复杂度我们无法接受。考虑对于 $F$ 的转移，都是位运算，故可以用 $bitset$ 优化转移。

$\text{Code}:$

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define int long long
#define ri register
#define mk make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define is insert
#define es erase
using namespace std; const int N=505, M=60;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
int n,m,Ans;
bitset<N> F[N][M+2][2],res,vis;
signed main()
{
	n=read(), m=read();
	for(ri int i=1;i<=m;i++)
	{
		int u,v,t;
		u=read(), v=read(), t=read();
		u--, v--;
		F[u][0][t].set(v);
	}
	for(ri int p=1;p<=61;p++)
	for(ri int i=0;i<n;i++)
	for(ri int j=0;j<n;j++)
	for(ri int k=0;k<2;k++)
	if(F[i][p-1][k][j])
	F[i][p][k]|=F[j][p-1][k^1];
	vis.set(0);
	int sta=0;
	for(ri int i=61;~i;i--)
	{
		res.reset();
		for(ri int j=0;j<n;j++) if(vis[j]) res|=F[j][i][sta];
		if(!(int)(res.count())) continue;
		vis=res;
		sta^=1, Ans+=(1ll<<i);
	}
	printf("%lld\n",(Ans>1e18)?(-1):(Ans));
	return 0;
}
```


---

## 作者：lsj2009 (赞：1)

### Solution

容易发现的是，每次连续走的一段路径长度比如是 $2^k$ 的形式，且如果我们知道了最开始走的边权，就能确定这条路径的形状，则我们考虑设 $f_{0/1,k,u,v}$ 表示是否存在一条从 $u$ 到 $v$ 且路径长度为 $2^k$ 然后第一条走的边权是 $0/1$ 的路径。

易得转移方程：

$$f_{0/1,k,u,v}=\bigvee\limits_{w=1}^{n} f_{0/1,k-1,u,w}\wedge f_{1/0,k-1,w,v}$$

直接暴力转移复杂度是 $\Theta(n^3\log{V})$ 的，显然吃不消，但是我们发现 $f$ 的取值只有可能是 $0/1$，所以考虑 ``bitset`` 优化，我们枚举点 $u,w$，如果 $f_{0/1,k,u,w}=1$，那么直接把 $f_{1/0,k,w}$ 整体或到 $f_{0/1,k+1,u}$ 上即可，复杂度变为 $\Theta(\frac{n^3\log{V}}{\omega})$，可以接受。

然后考虑怎么计算答案，我们贪心地从大到小走路径，由于如果存在长度为 $2^k$ 的路径则必然存在长度为 $2^{k-1}$ 地路径，所以这样必然不劣；我们保存一个集合 $S$ 表示我们当前走的路径长度为 $x$ 时可能的终点集合，假设我们现在要走长度为 $2^k$ 的路径，算一下 $T=\bigvee\limits_{u\in S} f_{p,k,u}$ 即可（其中 $p$ 为第一步要走的边权），看一下 $T$ 是否不为空集，如果不为空集，直接转移，令 $S\gets T,p\gets p\oplus 1$ 即可。

最终复杂度 $\Theta(\frac{n^3\log{V}}{\omega})$。

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
const int N=5e2+5,M=61;
bitset<N> f[2][M][N],last,g;
void solve() {
	int n,m;
	scanf("%lld%lld",&n,&m);
	while(m--) {
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		f[w][0][u][v]=1;
	}
	rep(k,1,60) {
		rep(d,0,1) {
			rep(u,1,n) {
				rep(v,1,n) {
					if(f[d][k-1][u][v])
						f[d][k][u]|=f[d^1][k-1][v];
				}
			}			
		}
	}
	int res=0,p=0;
	last[1]=1;
	per(i,60,0) {
		g.reset();
		rep(u,1,n) {
			if(last[u])
				g|=f[p][i][u];
		}
		if(g.count()) {
			last=g; 
			p^=1;
			res+=1ll<<i;
		}
	}
	if(res>1e18)
		puts("-1");
	else
		printf("%lld\n",res);
}
signed main() {
    int testcase=1;
    while(testcase--)
        solve();
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

由于路径是通过类似倍增的过程生成的，所以我们在求解最长路径时就不去二分了，而是直接倍增。

最初，走一个长度为 $2^{i}$ 的路径是要走第 $i$ 个路径，但是走了长度为 $2^i$ 的路径后再走一个长度为 $2^{i-1}$ 的路径就是要走第 $i-1$ 个路径取反后的结果，不妨维护一个状态表示下一步要走的路径是否要取反，每成功走了一个路径就将状态取反，同时倍增的过程中维护点集合 $S$ 表示当前能走到的点，然后用 $S$ 中的点去尝试走下一步，如果已经处理出了 $dp_{0/1,i,x,y}$ 表示在第 $i$ 个路径或者其取反的路径中，能否从 $x$ 走到 $y$ 就可以在 $O(n^2 \log V)$ 的时间内倍增出答案，现在问题转变为求解 dp 数组。

考虑 $dp_{0/1,i}$ 是由 $dp_{0/1,i-1}$ 做一个传递闭包得到，用 bitset 加速后可以做到 $O(\frac{n^3 \log V}{w})$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 504;
vector< vector<int> > dp[2][65];
//0 - 1
int n,m;
vector< vector<int> > merge(vector< vector<int> > A,vector< vector<int> > B){
    //A[i][k] B[k][j] -> f[i][j]
    bitset<maxn> a[maxn];
    bitset<maxn> b[maxn];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) a[i][j]=A[i][j],b[i][j]=B[j][i];
    } 
    vector< vector<int> > res;
    for(int i=1;i<=n+1;i++){
        vector<int> vec;
        vec.resize(n+1);
        res.push_back(vec);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            res[i][j]=((a[i]&b[j]).count()>0);
        }
    }
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n+1;i++){
        vector<int> vec;
        vec.resize(n+1);
        dp[0][0].push_back(vec);
        dp[1][0].push_back(vec);
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        dp[w][0][u][v]=1;
    }
    for(int i=1;i<=61;i++){
        dp[0][i]=merge(dp[0][i-1],dp[1][i-1]);
        dp[1][i]=merge(dp[1][i-1],dp[0][i-1]);
    }
    long long ans=0;
    int flag=0;
    vector<int> vec;
    for(int i=1;i<=n;i++) vec.push_back(i);
    for(int i=61;i>=0;i--){
        vector<int> New;
        vector<int> mp;
        mp.resize(n+1);
        for(int x:vec){
            for(int y=1;y<=n;y++){
                if(dp[flag][i][x][y]==1) mp[y]=1;
            }
        }
        for(int y=1;y<=n;y++){
            if(mp[y]==1) New.push_back(y);
        }
        if(New.size()>0){
            vec=New;
            flag^=1;
            ans+=(1ll<<i);
        }
    }
    if(ans>1e18) cout<<-1<<"\n";
    else cout<<ans<<'\n';
    return 0;
}
```

---

