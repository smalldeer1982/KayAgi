# [ARC159A] Copy and Paste Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc159/tasks/arc159_a

$ N $ 行 $ N $ 列の行列 $ A=(a_{i,j}) $ が与えられます。ここで、$ a_{i,j}\ \in\ \{0,1\} $ が成り立ちます。

また、以下のような有向グラフがあります。

- 頂点数は $ NK $ で、各頂点には $ 1,2,\ldots,NK $ と番号が付けられている。
- 辺は $ A $ を縦 $ K $ 行横 $ K $ 列に並べて得られる $ NK $ 行 $ NK $ 列の行列 $ X=(x_{i,j}) $ によって表される(入出力例1にて $ A,\ K $ に対応する $ X $ が示されている)。具体的には、$ x_{i,j}=1 $ ならば頂点 $ i $ から頂点 $ j $ への有向辺が存在し、$ x_{i,j}=0 $ ならば存在しない。
 
$ i=1,2,\ldots,Q $ に対し、次の問題に答えてください。

- 頂点 $ s_i $ から頂点 $ t_i $ への経路の長さ(辺の本数)の最小値を求めよ。ただし、そのような経路が存在しない場合は代わりに `-1` と出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ K\ \leq\ 10^9 $
- $ a_{i,j}\ \in\ \{0,1\} $
- $ 1\ \leq\ Q\ \leq\ 100 $
- $ 1\ \leq\ s_i,t_i\ \leq\ NK $
- $ s_i\ \neq\ t_i $
- 入力はすべて整数
 
### Sample Explanation 1

この例において、辺を表す行列 $ X $ は以下のようになります。 ``` 1 1 1 1 1 1 1 1 0 1 1 0 0 1 0 0 1 0 1 1 1 1 1 1 1 1 0 1 1 0 0 1 0 0 1 0 ```

### Sample Explanation 2

辺が $ 1 $ 本も存在しません。

## 样例 #1

### 输入

```
3 2
1 1 1
1 1 0
0 1 0
4
1 2
1 4
1 6
6 3```

### 输出

```
1
1
1
3```

## 样例 #2

### 输入

```
4 1000000000
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
1
1 4000000000```

### 输出

```
-1```

# 题解

## 作者：Xy_top (赞：3)

### 题意

给一个 $n\cdot n$ 的邻接矩阵（$0$ 表示没边，$1$ 表示有）。再给一个 $k$，表示最终的邻接矩阵是由 $k\cdot k$ 个小矩阵拼成的，询问两点间的最短距离，没有输出 $-1$。

### 思路

读完题就可以发现，$x$ 到 $y$ 有没有路径等于问我 $x-k$ 到 $y-k$ 两点有没有路径。所以我们跑个 Floyd，每次询问先把 $x$ 和 $y$ 减到 $\leq n$ 然后 $O(1)$ 回答就行了。

代码：
```cpp
#include <iostream>
#define int long long
using namespace std;
int n, k, x;
int q, f[105][105];
signed main () {
	int x, y;
	cin >> n >> k;
	for (int i = 1; i <= 100; i ++) {
		for (int j = 1; j <= 100; j ++) f[i][j] = 1000000000;
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			cin >> x;
			if (x == 1) f[i][j] = 1;
		}
	}
	for (int l = 1; l <= n; l ++) {
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				f[i][j] = min (f[i][j], f[i][l] + f[l][j]);
			}
		}
	}
	cin >> q;
	while (q --) {
		cin >> x >> y;
		x %= n;
		y %= n;
		if (x == 0) x += n;
		if (y == 0) y += n;
		if (f[x][y]) {
			if (f[x][y] >= 100000000) cout << -1;
			else cout << f[x][y];
		}
		cout << "\n";
	}
	return 0;
}
```


---

## 作者：KidzzZip (赞：1)

### 题目描述
给出一个 $N×N$ 大小的 ${0-1}$ 矩阵，并且将 ${K^2}$ 个矩阵拼接成一个大矩阵，求出两点间的最短路。

### 题目思路
首先看数据范围 ${1≤N≤100}$ 这点数据范围用 **Floyd** 算法非常合适。首先先求出一张图的最短路，然后我们使用模运算取 ${s_i,t_i}$ 的模，输出这个模的坐标便是答案，具体细节看代码。

### Code
```
#include<bits/stdc++.h>
#define N 101
using namespace std;
long long a[N][N],n,f,dis[N][N],q,x,y;
int main() {
	scanf("%lld%lld",&n,&f);
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			scanf("%lld",&a[i][j]); //初始化图
			if(a[i][j]) dis[i][j]=1;
			else dis[i][j]=1e9; 
		}
	}
   //Floyd启动！
	for(int f=1;f<=n;f++) {
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=n;j++) {
				dis[i][j]=min(dis[i][j],dis[i][f]+dis[f][j]);
			}
		}
	}
	scanf("%lld",&q);
	for(int i=1;i<=q;i++) {
		scanf("%lld%lld",&x,&y);
		printf("%lld\n",dis[(x%n==0)?n:x%n][(y%n==0)?n:y%n]!=1e9?dis[(x%n==0)?n:x%n][(y%n==0)?n:y%n]:-1); 
      //这一句的意思是x%n是不是0，是0就取n，不是0就取x%n，又判断这个坐标的值是不是1e9，是就输出-1，不是输出坐标值。
	}
	return 0;
}
```

---

## 作者：良心WA题人 (赞：1)

## 前言

有意思的 A。赛时没证明直接凭感觉上，突然就过了。赛后来浅补一下题解。不过这个 $Q$ 的数据范围挺误导人的，让我想了一段时间。

## 题意

给你一个 $n\times n$ 的邻接矩阵，将其复制 $k^2$ 份组成一个 $nk\times nk$ 的邻接矩阵，询问你 $Q$ 次，每次给定 $s_i,t_i$，问你从 $s_i$ 到 $t_i$ 的最短路。

## 思路

因为是由 $n\times n$ 的邻接矩阵复制 $k^2$ 次得到的，所以若 $a$ 能够在邻接矩阵上到达 $b$，那么 $a+xk$ 也能到达 $b+yk$。

看到这个性质考场上可以直接开写了。具体做法就是先预处理 任意的 $a$ 到 $b$ 的最短路，这个直接 `floyd` 处理。令 $g(x)=((x-1)\bmod n)+1$，那么每次的答案就是 $f_{g(s_i),g(t_i)}$。注意到因为 $s_i$ 不等于 $t_i$，所以用到 $f_{i,i}$ 一定是两个不同的点，至少需要一步，因此不要将 $f_{i,i}$ 赋值为 $0$。

现在考虑这样为什么是对的。审查 $s_i$ 到 $t_i$ 的路径上的每一条边 $u,v$，显然可以映射到一条边 $g(u),g(v)$，那么就变成了 $g(s_i)$ 到 $g(t_i)$ 的一个路径。所以直接用 $g(s_i)$ 到 $g(t_i)$ 的最短路径作为答案一定最优。不妨考虑反证法，若 $s_i$ 到 $t_i$ 的最短路径长度小于 $g(s_i)$ 到 $g(t_i)$ 的最短路径长度，那么将每条边 $u,v$ 映射到 $g(u),g(v)$ ，我们就得到了一条更短的从 $g(s_i)$ 到 $g(t_i)$ 的路径，矛盾，所以原命题得证。

时间复杂度 $O(n^3)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=104;
int f[NN][NN];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			int x;
			scanf("%d",&x);
			if(x==1)
				f[i][j]=1;
		}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	int q;
	scanf("%d",&q);
	while(q--)
	{
		long long u,v;
		scanf("%lld%lld",&u,&v);
		u=(u-1)%n+1,v=(v-1)%n+1;
		printf("%d\n",f[u][v]==0x3f3f3f3f?-1:f[u][v]);
	}
	return 0;
}
```

---

## 作者：_Gabriel_ (赞：0)

### 思路

经典最短路径题。

数据范围 $1 \le n \le 100$，用 Floyd 算法比较合适。

首先把图的最短路求出来。因为每次询问 $u$ 到 $v$ 有没有路径就是询问 $u-k$ 到 $v-k$ 有没有路径，所以把 $u,v$ 降到 $\le n$，然后判断从 $u$ 到 $v$ 有没有路径就可以了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const int N = 1e2 + 10;
int g[N][N];
int n, k, q;

void floyd() {
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);	
			}
		}
	}
}

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int t;
			cin >> t;
			if (t == 1) {
				g[i][j] = 1;
			} else {
				g[i][j] = INF;
			}
		}
	}	
	floyd();
	cin >> q;
	while (q--) {
		ll u, v;
		cin >> u >> v;
		u %= n;
		v %= n;
		if (u == 0) {
			u += n;
		} 
		if (v == 0) {
			v += n;
		}
		if (g[u][v] == INF) {
			cout << -1 << "\n";
		} else {
			cout << g[u][v] << "\n";
		}
	}
	return 0;
}
```


---

## 作者：FyFive (赞：0)

#### 思路

注意到多出来的那么多 $k$ 实际上是没有用的，本质上还是在 $n*n$ 的邻接矩阵里跑最短路，不过需要注意的是当 $s=t$ 的时候，答案为 0。

考虑 Floyd 实现最短路，复杂度 $O(n^3+Q)$。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mo 998244353998244353ll
int a[105][105];
int q,s,t,n,k;
signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) cin>>a[i][j];
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) if(a[i][j]==0) a[i][j]=mo;
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) for(int l=1;l<=n;++l) a[i][j]=min(a[i][j],a[i][l]+a[l][j]);
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) for(int l=1;l<=n;++l) a[i][j]=min(a[i][j],a[i][l]+a[l][j]);
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) for(int l=1;l<=n;++l) a[i][j]=min(a[i][j],a[i][l]+a[l][j]);
    cin>>q;
    while(q--)
    {
        cin>>s>>t;
        bool noti=(s==t);
        s=(s-1ll)%n+1ll; t=(t-1ll)%n+1ll;
        if(noti) cout<<0<<endl;
        else cout<<(a[s][t]>=mo?-1ll:a[s][t])<<endl;
    }
    return 0;
}
```

---

## 作者：lzqy_ (赞：0)

观察到若 $a \to b\;(1\le a,b \le n)$，那么 $kn+a\to kn+b$，也就是说所有的 $(kn+b)$ **基本**是等价的。所以题目直接转化为求 $a \to b\;(1\le a,b \le n)$ 的最短路。

注意一个细节，之所以说是 `基本` 相等，是因为不能默认 $kn+b\to kn+b$。因此对于每组询问求最短路的时候，要找到能直接到达 $t$ 的点 $t'$，然后求 $dis(s,t')+1$。

时间复杂度 $O(n^3+qn)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
const int maxn=110;
const int inf=1<<30;
il ll read(){
	ll x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
vector<int>v[maxn];
int a[maxn][maxn];
int f[maxn][maxn];
int n,k;
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=inf;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]=read())
				f[i][j]=1,v[j].push_back(i);
	for(int i=1;i<=n;i++) f[i][i]=0;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				f[i][j]=min((ll)f[i][j],(ll)f[i][k]+f[k][j]);
	int Q=read(),ans;
	while(Q--){
		ll s=read(),t=read(); ans=inf;
		if(s==t){printf("0\n");continue;}
		s=(s-1)%n+1,t=(t-1)%n+1;
		for(int i=0;i<v[t].size();i++)
			ans=min(ans,f[s][v[t][i]]+1);
		if(ans==inf) printf("-1\n");
		else printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)

由于图是复制的，复制时会保留原来所有的边。比如 $x,y$ 之间有连边，那么 $(x,y+n)$ 之间也有，因此一个点 $x$ 可以被映射到 $1\sim n$ 内，与其它点的距离并不会发生改变。 

直接跑多源最短路。注意如果两个点映射后被映射到同一个点，但它们原本不是同一个点，那么需要走一条边的。也就是说，相同点的距离是根据题目给定的，在此基础上判掉本来就相同的点即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64; 
const int INF = 1e9; 

int n, k; 
int a[105][105]; 

int main(void) {
    scanf("%d%d", &n, &k); 
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        scanf("%d", &a[i][j]); 
        a[i][j] = (a[i][j] ? 1 : INF); 
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                a[i][j] = min(a[i][j], a[i][k] + a[k][j]); 
    int q; scanf("%d", &q); 
    while (q--) {
        i64 s, t; scanf("%lld%lld", &s, &t); 
        if (s == t) { puts("0"); continue; }
        s = (s - 1) % n + 1, t = (t - 1) % n + 1; 
        printf("%d\n", (a[s][t] == INF ? -1 : a[s][t])); 
    }
    return 0;
}
```

---

## 作者：Federico2903 (赞：0)

## 思路

~~很有意思的一道思维题？~~  
通过观察不难发现，如果 $a$ 能到达 $b$，那么 $a$ 一定能到达 所有的 $kn+b(0\le k)$，同理可得，所有的 $kn+a(0\le k)$ 一定都能到达 $b$。  
所以就转换成了一个 Floyd，输出时对 $n$ 取模即可。  

## AC 代码

```cpp
ll a[105][105];
ll n,k,Q,dp[105][105];

signed main() {
	read(n);read(k);
	memset(dp,0x3f,sizeof dp);
	rep(i,1,n)
		rep(j,1,n){
			read(a[i][j]);
			if(a[i][j])dp[i][j]=1;
			//dp[i][i]=0;
		}
	rep(k,1,n)
		rep(i,1,n)
			rep(j,1,n){
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
			}
	ll q;
	read(q);
	while(q--){
		ll s,t;read(s);read(t);
		if(s==t){
			cout << 0 << endl;
			continue;
		}
		if(dp[s%n==0?n:s%n][t%n==0?n:t%n]>=1e11){
			cout << -1 << endl;
		}
		else{
			cout << dp[s%n==0?n:s%n][t%n==0?n:t%n] << endl;
		}
	}
	return 0;
}
```

---

