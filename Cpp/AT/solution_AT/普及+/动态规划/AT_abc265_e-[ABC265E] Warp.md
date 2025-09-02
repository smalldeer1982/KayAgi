# [ABC265E] Warp

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc265/tasks/abc265_e

$ 2 $ 次元平面の原点に高橋君がいます。  
 高橋君はこれから、ワープを $ N $ 回繰り返します。各ワープでは、以下の $ 3 $ つのうちいずれか $ 1 $ つを行います。

- 現在いる座標 $ (x,y) $ から $ (x+A,y+B) $ に移動する
- 現在いる座標 $ (x,y) $ から $ (x+C,y+D) $ に移動する
- 現在いる座標 $ (x,y) $ から $ (x+E,y+F) $ に移動する

平面上の $ M $ 箇所 $ (X_1,Y_1),\ldots,(X_M,Y_M) $ には障害物があり、これらの座標に移動することはできません。

$ N $ 回のワープによる移動経路として考えられるものは何通りですか？ $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 300 $
- $ 0\ \leq\ M\ \leq\ 10^5 $
- $ -10^9\ \leq\ A,B,C,D,E,F\ \leq\ 10^9 $
- $ (A,B),(C,D),(E,F) $ は相異なる
- $ -10^9\ \leq\ X_i,Y_i\ \leq\ 10^9 $
- $ (X_i,Y_i)\neq(0,0) $
- $ (X_i,Y_i) $ は相異なる
- 入力に含まれる値は全て整数である

### Sample Explanation 1

以下の $ 5 $ 通りが考えられます。 - $ (0,0)\to(1,1)\to(2,3) $ - $ (0,0)\to(1,1)\to(2,4) $ - $ (0,0)\to(1,3)\to(2,4) $ - $ (0,0)\to(1,3)\to(2,5) $ - $ (0,0)\to(1,3)\to(2,6) $

## 样例 #1

### 输入

```
2 2
1 1 1 2 1 3
1 2
2 2```

### 输出

```
5```

## 样例 #2

### 输入

```
10 3
-1000000000 -1000000000 1000000000 1000000000 -1000000000 1000000000
-1000000000 -1000000000
1000000000 1000000000
-1000000000 1000000000```

### 输出

```
0```

## 样例 #3

### 输入

```
300 0
0 0 1 0 0 1```

### 输出

```
292172978```

# 题解

## 作者：flying_man (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc265_e)

题意：flying_man 有三种移动方式：

- $(X,Y)$ 移至 $(X+A,X+B)$
- $(X,Y)$ 移至 $(X+C,C+D)$
- $(X,Y)$ 移至 $(X+E,X+F)$

同时有 $M$ 个障碍 $(X_i,Y_i)$，他不能经过这些障碍。问你在进行 $N$ 次移动后，有多少种可能的路径？答案对 $998244353$ 取模。

------------
**题解部分：**

我们可以先考虑暴力 DP。

设 $dp_{i,j}$ 为当所处位置为 $(i,j)$ 时可能的路径数。

当然，转移方程很好想，~~所以说这题切了？~~

**NO NO NO NO NO NO NO**

我们看取值范围，坐标可能会到达 $10^{11}$ 量级。

所以我们可以转换思路：不记坐标，而是记录三次移动分别用了多少次。

设 $dp_{i,j,k}$ 为 第一种移动方式用 $i$ 次，第二种移动方式用 $j$ 次，第三种移动方式用 $k$ 次时可能的路径数。

此时我们能通过 $i,j,k$ 计算出当前坐标。至于障碍，我们考虑用 map，如果当前为障碍点，我们就直接跳过。

注：可能会被卡常，建议使用哈希表或 unordered_map 处理障碍。

------------
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 305;
const ll mod = 998244353;
ll dp[N][N][N],ans;
int n,m,A,B,C,D,E,F,x,y;
map<pair<int,int>,int> p;
void in(int &s){
    char c;s = 0;int p = 1;
    while(c < '0' || c > '9'){
        if(c == '-') p = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9')
        s=s*10+c-'0',c = getchar();
    s *= p;
}
int main(){
    in(n);in(m);in(A);in(B);in(C);in(D);in(E);in(F);
    for(int i = 1;i <= m;i++){
        in(x);in(y);
        p[{x,y}] = 1;
    }
    dp[0][0][0] = 1;
    for(int i = 0;i <= n;i++){
        for(int j = 0;j <= n-i;j++){
            for(int k = 0;k <= n-i-j;k++){
                if(i == 0 && j == 0 && k == 0) continue;
                ll nx = i*A+j*C+k*E;
                ll ny = i*B+j*D+k*F;
                if(p[{nx,ny}] == 1) continue;
                if(i) dp[i][j][k] += dp[i-1][j][k];
                if(j) dp[i][j][k] += dp[i][j-1][k];
                if(k) dp[i][j][k] += dp[i][j][k-1];
                dp[i][j][k] %= mod;
                if(i+j+k == n) ans = (ans+dp[i][j][k])%mod;
            }
        }
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：FFTotoro (赞：7)

本题可以使用记忆化搜索。

首先，我们要明白一个性质：

设题目中的三种操作从原点开始分别进行了 $t_1,t_2,t_3$ 次，那么高桥君现在所处的位置就是 $(t_1A+t_2C+t_3E,t_1B+t_2D+t_3F)$。

很显然，利用一个 `std::set` 就可以存储所有禁止走到的点的坐标，查找时利用 `find` 函数即可。

我们可以定义一个函数 `int dfs(int x,int y,int z)`，代表目前搜到了“三种操作分别进行了 $x,y,z$ 次的点”，并用一个三维数组 $g$ 保存答案。如果 $x+y+z=n$，那么就代表搜到了答案，返回 $1$。然后不断递归下去就可以求解。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
set<pair<int,int> > s;
int n,m,a,b,c,d,e,f,g[301][301][301];
int dfs(int x,int y,int z){
    int x0=a*x+c*y+e*z,y0=b*x+d*y+f*z; // 求坐标
    if(s.find(make_pair(x0,y0))!=s.end())return 0; // 不能走
    if(x+y+z==n)return 1; // 搜到了合法方案
    if(g[x][y][z])return g[x][y][z]; // 已经标记过
    return g[x][y][z]=(dfs(x+1,y,z)+dfs(x,y+1,z)+dfs(x,y,z+1))%998244353; // 三种走法分别 +1
}
main(){
    ios::sync_with_stdio(false);
    cin>>n>>m>>a>>b>>c>>d>>e>>f;
    for(int i=0;i<m;i++){int x,y; cin>>x>>y; s.emplace(x,y);}
    cout<<dfs(0,0,0)<<endl;
    return 0;
}
```

---

## 作者：xiaoPanda (赞：2)

## E - Warp
写爆搜肯定会爆，而记忆化又不如 dp 好理解，考虑 dp，设 $f[dep][x][y]$ 代表当前走了 $dep$ 步到了点 $(x,y)$，注意到每个点可以多次经过，所以还要记一下当前是第几步这个点。

然后暴力枚举每个操作使用了多少次，假设操作 AB 使用了 $i$ 次，操作 CD 使用了 $j$ 次，操作 EF 使用了 $k$ 次，那么现在点的坐标就是 $(x=i*A+j*C+k*E,y=i*B+j*D+k*F)$，如果这个点没有障碍，那么就有 $f[dep][x][y]=f[dep-1][x-A][y-B]+f[dep-1][x-C][y-D]+f[dep-1][x-E][y-F]$ 注意下操作次数非负。

如果 $f$ 用 map 来存，时间复杂度为 $O(n^3\log n^3)$ 难以通过，用 hash 来存容易冲突并且空间也开不下太大，用 hash 表可能可以通过，但下面介绍一种更简单的方法。

注意我们关心的是到什么位置和到这个位置走了多少步，所以我们可以记下每个操作用了多少次，那么依旧可以记录下上面的 dp 所记录的信息，具体的设 $f[i][j][k]$ 表示操作 AB 使用了 $i$ 次，操作 CD 使用了 $j$ 次，操作 EF 使用了 $k$ 次，那么就是走了 $i+j+k$ 步，位置同上，转移有 $f[i][j][k]=f[i-1][j][k]+f[i][j-1][k]+f[i][j][k-1]$，这样 $f$ 用普通的数组即可，至于记一下哪些点有障碍直接用 set 即可，时间复杂度为 $O(n^3\log m)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
const int N=307;
const int mod=998244353;
int f[N][N][N];
set<pair<int,int> >s;
main() 
{
   int n,m,A,B,C,D,E,F,ans=0;
	cin>>n>>m>>A>>B>>C>>D>>E>>F;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		s.insert(mp(x,y));
	} 
	f[0][0][0]=1;
	for(int i=0;i<=n;i++)
	    for(int j=0;i+j<=n;j++)
	        for(int k=0;i+j+k<=n;k++)
	        {
	        	 int x=i*A+j*C+k*E;
					int y=i*B+j*D+k*F;
					if(s.find(mp(x,y))!=s.end()||i+j+k==0)continue;
					if(i!=0)f[i][j][k]+=f[i-1][j][k];
					if(j!=0)f[i][j][k]+=f[i][j-1][k];
					if(k!=0)f[i][j][k]+=f[i][j][k-1];
					f[i][j][k]%=mod;
				}
	for(int i=0;i<=n;i++)
	    for(int j=0;i+j<=n;j++)
			ans+=f[i][j][n-i-j],ans%=mod;
	printf("%lld",ans);
   return 0;
}
```

---

## 作者：_shine_ (赞：1)

看到 $1\le n \le 300$，则不难猜到使用时间 $n^3$ 的算法。

定义 $f_{i,j,k}$ 表示操作了第一个操作 $i$ 次，第二个操作 $j$ 次，第三个操作 $k$ 次所能获得的方案数，则显然可以发现 $f_{i,j,k}$ 只能从 $f_{i-1,j,k},f_{i,j-1,k},f_{i,j,k-1}$ 转移过来，则思考处理无法经过的点，发现 $f_{i,j,k}$ 的点所在位置显然为 $\left(i\times a+j\times c+k \times e,i\times b+j\times d+k\times f\right)$，所以使用 ```map``` 维护当前点是否可以走即可。

建议不用 ```map``` 或者使用 ```scanf``` 或快读。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define x first
#define y second
#define pii pair<int,int>
const int maxn=3e2+10;
const int inf=998244353;
int n,m;
int a,B,c,d,e,F;
int f[maxn][maxn][maxn];
map<pii,int>p;
int b[maxn];
int ans;
signed main(){
	cin >> n >> m;
	cin >> a >> B >> c >> d >> e >> F;
	for(int i=1;i<=m;++i){int l,r;cin >> l >> r;p[{l,r}]=1;}
	f[0][0][0]=1;
	for(int i=0;i<=n;++i){
		for(int j=0;j<=n-i;++j){
			for(int k=0;k<=n-i-j;++k){
				int x=i*a+j*c+k*e,y=i*B+j*d+k*F;
				if(p[{x,y}]==1)continue;
				if(i)f[i][j][k]+=f[i-1][j][k];
				if(j)f[i][j][k]+=f[i][j-1][k];
				if(k)f[i][j][k]+=f[i][j][k-1];
				f[i][j][k]%=inf;
				if(i+k+j==n)ans=(ans+f[i][j][k])%inf;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```
题外话：
建议大家在考CSP时注意 ```define int long long``` 输入却用 ```%d``` 的问题，这个在 linux 系统下会无法通过。

---

## 作者：MYJ_aiie (赞：1)

### [题目](https://www.luogu.com.cn/problem/AT_abc265_e)


------------

读完题之后很容易设 $f(i,j)$  为到 $ i,j $ 的方案数……吗？  
可是发现并不是的,因为 $i,j$ 都是大于 $10^9$ 的数,数组没办法开那么大。  

这时候又看到 $n$ 为 $300$，$300^3$ 正好可以过，那怎么设三维的 DP ? 发现
题目的移动方法正好有 $3$ 种,那就设 $f[i][j][k]$ 中 
$i$ 为用第一种移动的次数,也就是 $A,B$ 的移动次数；$j$ 为用第二种移动的次数,也就是 $C,D$ 的移动次数；以此类推第三种。  
所以状态转移方程就是：

${f}_{i,j,k}={f}_{i-1,j,k}+{f}_{i,j-1,k}+{f}_{i,j,k-1}$

所以说当前的位置就是：

$x=i\times A +j\times C+k\times E$  
$y=i\times B+j\times D+k\times F$

还有一个地方需要处理,因为题目中 $M$ 的范围是     $10^5$ ,所以如果暴力判断是否经过,会超时。我们可以用 map 存 $X_i,Y_i$。

code
------------
```
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<map> 
using namespace std;
const int mod=998244353;
int n,m;
long long A,B,C,D,E,F;
int f[302][302][302];
map<long long,int> vi;
long long ans=0;
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%lld%lld%lld%lld%lld%lld",&A,&B,&C,&D,&E,&F);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		vi[x*1e9+y]=1;
	}
	f[0][0][0]=1;
	for(int i=0;i<=n;i++)//注意从0开始，因为可能一次都不用 
	{
		for(int j=0;j<=n;j++)
		{
			if(i+j<=n)//小优化 
			{
				for(int k=0;k<=n;k++)
				{	
					if(i+j+k<=n) 
					{
						if(vi[(i*A+j*C+k*E)*1e9+i*B+j*D+k*F]==1) continue;
						if(i-1>=0) f[i][j][k]=(f[i][j][k]+f[i-1][j][k])%mod;
						if(j-1>=0) f[i][j][k]=(f[i][j][k]+f[i][j-1][k])%mod;
						if(k-1>=0) f[i][j][k]=(f[i][j][k]+f[i][j][k-1])%mod; 
						if(i+j+k==n)
						ans=(ans+f[i][j][k])%mod;
					}
					
				}
			}
			
		
		}
	} 
	printf("%lld\n",ans);
	return 0;
}

```


------------


---

## 作者：Ginger_he (赞：1)

## 题目描述

给定平面直角坐标系上的 $M$ 个点。一开始你在原点，接下来执行 $N$ 次操作，每次操作你可以从 $(i,j)$ 走到 $(i+A,j+B)$ 或 $(i+C,j+D)$ 或 $(i+E,j+F)$，求不经过给定的 $M$ 个点的方案数，答案对 $998244353$ 取模。

## 题解

建议评绿。

这题和[乌龟棋](https://www.luogu.com.cn/problem/P1541)很像，考虑设计一个 dp，$dp_{i,j,k}$ 表示走 $i$ 次 $(A,B)$，$j$ 次 $(C,D)$，$k$ 次 $(E,F)$ 的方案数。我们可以简单的用一下哈希，把某个点 $(x,y)$ 用一个数 $2x\times10^9+y$ 来表示，放到 `map` 里表示可不可走，转移的时候判断当前点能否经过即可，时间复杂度 $O(n^3\log m)$，不过显然跑不满。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 305
const ll p=998244353;
ll n,m,a,b,c,d,e,f,x,y,dp[N][N][N],ans;
map<ll,bool> mp;
int main()
{
	scanf("%lld%lld%lld%lld%lld%lld%lld%lld",&n,&m,&a,&b,&c,&d,&e,&f);
	for(ll i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		mp[x*2e9+y]=1;
	}
	dp[0][0][0]=1;
	for(ll i=0;i<=n;i++)
	{
		for(ll j=0;i+j<=n;j++)
		{
			for(ll k=0;i+j+k<=n;k++)
			{
				x=i*a+j*c+k*e,y=i*b+j*d+k*f;
				if(!mp[x*2e9+y])
				{
					if(i) dp[i][j][k]=(dp[i][j][k]+dp[i-1][j][k])%p;
					if(j) dp[i][j][k]=(dp[i][j][k]+dp[i][j-1][k])%p;
					if(k) dp[i][j][k]=(dp[i][j][k]+dp[i][j][k-1])%p; 
				}
				if(i+j+k==n)
					ans=(ans+dp[i][j][k])%p;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

蛮经典的一道题。

## 思路

考虑 $n\leq 300$，我们改变定义，令 $dp_{i,j,k}$ 表示三种走法各走了 $i,j,k$ 步的方案。如果终点是不合法点直接为 $0$，$i+j+k=n$ 时统计入答案，否则转移到 $dp_{i+1,j,k},dp_{i,j+1,k},dp_{i,j,k+1}$ 即可。题目难度其实还行，$dp$ 的一个小套路。关于记录点可以用 map 或 unordered_map。复杂度 $\Theta(n^3\log m)$，由于 unordered_map 常数极小几乎 $\Theta(1)$ 所以没啥问题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
int dp[305][305][305];
unordered_map<int,int> mp;
signed main(){
	dp[0][0][0]=1;
	int n,m;
	cin>>n>>m;
	int a,b,c,d,e,f;
	cin>>a>>b>>c>>d>>e>>f;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		mp[(x+1000000007)*(2000000114)+(y+1000000007)]=1;
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		for(int j=0;j+i<=n;j++){
			for(int k=0;k+j+i<=n;k++){
				int px=a*i+c*j+e*k,py=b*i+d*j+f*k;
				if(mp[(px+1000000007)*(2000000114)+(py+1000000007)]) continue;
				if(i+j+k==n){
					ans=(ans+dp[i][j][k])%mod;
					continue;
				}
				dp[i+1][j][k]=(dp[i+1][j][k]+dp[i][j][k])%mod;
				dp[i][j+1][k]=(dp[i][j+1][k]+dp[i][j][k])%mod;
				dp[i][j][k+1]=(dp[i][j][k+1]+dp[i][j][k])%mod;
			}
		} 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_AyachiNene (赞：0)

# 思路：
看这种计数的题一看就是动态规划。很容易想到一种思路：设 $dp_{i,j}$ 表示在坐标为 $(i,j)$ 时的方案数。那么转移方程很容易推出，就不写了。但是这道题的坐标的数据范围很大，显然不能这么做，要换状态定义。可以发现，当三种操作中每种操作数量一一对应时，最后到达的点是一样的，也就是说，操作顺序不影响答案。那么可以设 $dp_{i,j,k}$ 为三种操作分别用了 $i,j,k$ 时的方案数容易得到转移方程：
$$dp_{i,j,k}=dp_{i-1,j,k}+dp_{i,j-1,k}+dp_{i,j,k-1}$$
转移的前提是当前的这个点可以到达，用 map 判一下就行了。
# Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int mod=998244353;
int n,m;
int x[114],y[114];
int dp[114<<2][114<<2][114<<2];
map<pair<int,int>,int>vis;
int ans;
inline int check(int i,int j,int k)
{
	return !vis[{i*x[1]+j*x[2]+k*x[3],i*y[1]+j*y[2]+k*y[3]}];
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=3;i++)
		x[i]=read(),y[i]=read();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read();
		vis[{x,y}]=1;
	}
	dp[0][0][0]=1;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n-i;j++)
			for(int k=0;k<=n-i-j;k++)
			{
				if(!check(i,j,k))
					continue;
				if(i)
					dp[i][j][k]=(dp[i][j][k]+dp[i-1][j][k])%mod;
				if(j)
					dp[i][j][k]=(dp[i][j][k]+dp[i][j-1][k])%mod;
				if(k)
					dp[i][j][k]=(dp[i][j][k]+dp[i][j][k-1])%mod;
			}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			if(check(i,j,n-i-j))
				ans=(ans+dp[i][j][n-i-j])%mod;
	write(ans);
}
```


---

## 作者：Mu_leaf (赞：0)

## [思路]

考虑如果 $x,y$ 的范围很小，那么可以钦定数组 $f_{i,j}$ 表示走到第 $i,j$ 格的方案数，方程很好列。

可惜 AT 不给我们这个机会，注意到最多只有三种传送方式且操作顺序并不会影响到最终位置，则可以钦定数组 $f_{i,j,k}$ 表示分别用了三种传送方式多少次。

初始状态则是 $f_{0,0,0}=1$ 表示一个方式都不选的方案有一个。

转移则是 
$$f_{i,j,k}=f_{i-1,j,k}(1 \leq i) + f_{i,j-1,k}(1 \leq j) +f_{i,j,k-1}(1 \leq k)$$

于是我们可以 $O(1)$ 算出现在走到了哪里，用 map 存一下障碍，遇到就跳过就好啦。

注意在 dp 循环时可以让 $i+j+k \leq n$ 优化一下常数。

Code:
------

```cpp

#include <bits/stdc++.h>
#define hsh 1000000000
#define int long long
using namespace std;
const int mod=998244353,p=10000000;
int n,m;
int fx[10][5];
int f[305][305][305],ans;
map<pair<int,int>,int> mp;
signed main(){
	cin >> n >> m;
	cin >> fx[1][1] >> fx[1][2] >> fx[2][1] >> fx[2][2] >> fx[3][1] >> fx[3][2];
	for(int i=1,x,y,v;i<=m;i++) cin >> x >> y,mp[{x,y}]=1;
	f[0][0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;i+j<=n;j++){
			for(int k=0;i+j+k<=n;k++){
				if(i==0 && j==0 && k==0) continue;
				int x=i*fx[1][1]+j*fx[2][1]+k*fx[3][1];
				int y=i*fx[1][2]+j*fx[2][2]+k*fx[3][2];
				if(mp[{x,y}]) continue;
				if(i)(f[i][j][k]+=f[i-1][j][k])%=mod;
				if(j)(f[i][j][k]+=f[i][j-1][k])%=mod;
				if(k)(f[i][j][k]+=f[i][j][k-1])%=mod;
				if(i+j+k==n)ans=(ans+f[i][j][k])%mod;
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

[博客园](https://www.cnblogs.com/gsczl71/p/17920149.html)。

首先，这一题很显然是一个 Dp。

考虑如何转移状态，因为一开始的坐标是 $(0,0)$。

发现最后的坐标是 $(A\times i + C \times j + E \times k,B\times i + D \times j + F \times k)$。如果是统计最后的种类的话，那么就比较简单，枚举 $i$，$j$ 和 $k$。但是题目要求的是方案数，所以我们可以用一个三维 Dp，转移一下 $i$，$j$ 和 $k$ 时的方案数，很容易想，可以从 $i-1$，$j-1$ 和 $k-1$ 分别转移。所以后面枚举 $i$，$j$ 和 $k$ 只需要累加其 Dp 状态即可。

不可行的方案用 map 存储特判掉即可。

上代码：[link](https://atcoder.jp/contests/abc265/submissions/48659015)。

---

## 作者：MMXIandCCXXII (赞：0)

## 题目大意
每次可以将点 $(x,y)$ 移动到 $(x+a,y+b)$ 或 $(x+c,y+d)$ 或 $(x+e,y+f)$，但有 $m$ 个点不能去，需要移动 $n$ 步，求有几条路径。

## 分析
这道题可以用动态规划，因为 $n$ 不超过 $300$，考虑 $O(N^3)$，每次枚举三种操作的次数，开三维数组，然后统计三种次数加起来是 $n$ 的情况的和即可。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 310;
const int mod = 998244353;
map <pair <int, int>, bool> mp;
int dp[N][N][N];
int n, m;
int a, b, c, d, e, f;

signed main()
{
    cin >> n >> m;
    cin >> a >> b >> c >> d >> e >> f;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        mp[make_pair(x,y)] = true;
    }
    dp[0][0][0] = 1;
    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n - i; j++)
        {
            for (int k = 0; k <= n - i - j; k++)
            {
            	if(i == 0 && j == 0 && k == 0) continue;
                int x = i * a + j * c + k * e;
                int y = i * b + j * d + k * f;     
                if (mp[make_pair(x,y)]) continue;
                if (i) dp[i][j][k] = (dp[i-1][j][k] + dp[i][j][k]) % mod;
                if (j) dp[i][j][k] = (dp[i][j-1][k] + dp[i][j][k]) % mod;
                if (k) dp[i][j][k] = (dp[i][j][k-1] + dp[i][j][k]) % mod;
            }
        }
    }
    for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n - i; j++)
		{
			ans = (ans + dp[i][j][n - i - j]) % mod;
		}
	}
    cout << ans << endl;
    return 0;
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目分析
### 思路：动态规划
第一眼看到这个题目，有人可能会想到设 $dp_{x,y}$ 为从 $(0,0)$ 走到 $(x,y)$ 的路径条数，但是 $A$，$B$，$C$，$D$，$E$ 和 $F$ 最大的取值范围都是 $10^9$，这是一个数组无法承受的数据范围。还有人会想到搜索：从 $(0,0)$ 开始搜，一直不停地向下搜索，知道搜索层数达到 $N$，或是遇到障碍再返回，在搜索时统计方案数。但是，就算对这个方法加上记忆化，也依然会消耗很多时间才能得到答案。既然把坐标设为状态不可行，那我们就要把握住题目的数据范围，抓软的柿子来捏。我们发现 $N$ 很小，想到可以从移动步数入手。设 $dp_{i,j,k}$ 为三种移动各执行 $i$、$j$、$k$ 次可以得到的路径条数。很明显，$dp_{0,0,0}=0$。如何转移 $dp_{i,j,k}$ 呢？由于每一次移动只能选择一种移动操作，所以我们可以得到下面这个状态转移方程：
$$dp_{i,j,k}=dp_{i-1,j,k}+dp_{i,j-1,k}+dp_{i,j,k-1}$$
那么，答案是什么呢？由于三种移动操作的执行次数不定，所以答案就是：
$$\sum_{i=0}^{N} \sum_{j=0}^{N-i} dp_{i,j,N-i-j}$$
到此，思路部分结束。
## 代码实现
由于本题还有障碍物，所以我们要好好考虑一下障碍物如何处理。用一个 map 来标记肯定不行，这么做的时间复杂度为 $O(N^3 \log N^3)$，无法通过本题。我们可以考虑用一个 set 来存障碍物，每次到达一个点时判断它是否在障碍物的集合里，如果该点不在集合中就转移 $dp_{i,j,k}$。

完结撒花！

**AC code:**
```cpp
#include<iostream>
#include<cstring>
#include<set>
using namespace std;
#define ll long long
const int mod=998244353;
int n,m,a,b,c,d,e,f,x,y;
ll dp[305][305][305],ans;
set<pair<int,int> >st;
int main(){
	cin>>n>>m>>a>>b>>c>>d>>e>>f;
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		st.insert(make_pair(x,y));
	}
	dp[0][0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				if(st.find(make_pair(i*a+j*c+k*e,i*b+j*d+k*f))==st.end()){
					if(i>0){
						dp[i][j][k]=(dp[i][j][k]+dp[i-1][j][k])%mod;
					}
					if(j>0){
						dp[i][j][k]=(dp[i][j][k]+dp[i][j-1][k])%mod;
					}
					if(k>0){
						dp[i][j][k]=(dp[i][j][k]+dp[i][j][k-1])%mod;
					}
				}
			}
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=0;i+j<=n;j++){
			int k=n-i-j;
			ans=(ans+dp[i][j][k])%mod;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lhc0707 (赞：0)


[题目传送门](https://www.luogu.com.cn/problem/AT_abc265_e)

#### 题意：

已知三种移动的方式：

- 从点 $(X,Y)$ 移动到点 $(X+A,Y+B)$ 

- 从点 $(X,Y)$ 移动到点 $(X+C,Y+D)$

- 从点 $(X,Y)$ 移动到点 $(X+E,Y+F)$

同时，有 $M$ 个点不可以被经过，问转移 $N$ 次后有多少种转移的路径，答案对 $998244353$ 取模。

#### 题解：

直接在坐标系中记忆化搜索显然是不行的，我们要开 $10^9 \times 10^9=10^{18} $ 的数组，空间爆炸，考虑 dp 优化。

考虑到在给定了三种走法后，我们每一步到达的点坐标都可以用三种走法的步数计算出来。

我们可以设 $f_{i,j,k}$ 表示方式 $1,2,3$ 分别走了 $i,j,k$ 步后到达该点的次数，设初始值 $f_{0,0,0}=1$。

我们可以很容易地列出转移方程：

$$
f_{i,j,k}=f_{i-1,j,k}+f_{i,j-1,k}+f_{i,j,k-1}
$$

此时的点坐标 $P(x,y)$ 可表示为：

$$
x=i \times A + j \times C + k \times E
$$

$$
y=i\times B + j \times D + k \times F
$$

$n$次传送，只需要保证 $i+j+k \le n$ 即可。

那么问题来了，如何判断条件中不能走的点呢？如果只是简单地在坐标系中标记下来，空间又爆了。

其实解决方案很简单：开 map，对于每一个不能走的点，用
map 标记上，转移过程中根据 $i,j,k$ 的值算出坐标值，进行查询即可。

下面放上代码:

```cpp
#include<map>
#include<cstdio>
#include<iostream>
#define int long long
#define mkpr make_pair
using namespace std;
const int MOD=998244353;
int n,m,A,B,C,D,E,F,f[305][305][305],ans;
map<pair<int,int>,bool> mp;
signed main(){
	cin>>n>>m>>A>>B>>C>>D>>E>>F;
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		mp[mkpr(x,y)]=true;
	}
	f[0][0][0]=1;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n-i;j++){
			for(int k=0;k<=n-i-j;k++){
				if(mp[mkpr(i*A+j*C+k*E,i*B+j*D+k*F)]==true)continue;
				if(i)f[i][j][k]+=f[i-1][j][k],f[i][j][k]%=MOD;
				if(j)f[i][j][k]+=f[i][j-1][k],f[i][j][k]%=MOD;
				if(k)f[i][j][k]+=f[i][j][k-1],f[i][j][k]%=MOD;	
				if(i+j+k==n)ans=(ans+f[i][j][k])%MOD;
			}
		}
	}
	cout<<ans%MOD;
	return 0;
}
```
本蒟蒻第一篇题解，望过审QWQ。

---

## 作者：chengning0909 (赞：0)

# abs 265 e

## 题意

Takahashi 在二维平面的原点处。有 $N$ 次传送，每次可以选择下面三种中的一种：

1. 从 $(x, y)$ 传送到 $(x + a, y + b)$。

2. 从 $(x, y)$ 传送到 $(x + c, y + d)$。

3. 从 $(x, y)$ 传送到 $(x + e, y + f)$。

平面上有 $M$ 个障碍点，不能传送到障碍点上。

请问有多少种可能的传送路径，答案对 $998244353$ 取模。

## 思路

首先，我们可以想到这样一个状态，$dp_{i, x, y}$ 表示在第 $i$ 次操作后走到 $(x, y)$ 的方案数，再在转移的时候判断是否为障碍点。

但是，很明显，这个是不行的，因为 $(x, y)$ 太大了，存不下来。

那么，我们可以考虑另外一种角度。假设当前做了 $i$ 次操作 $1$，$j$ 次操作 $2$，$k$ 次操作 $3$。

那么，当前所处的坐标就是 $(i \times a + j \times c + k \times e, i \times b + j \times d + k \times f)$。

所以，我们可以枚举 $i, j, k$，得到当前所处的坐标，再分别进行三种转移。（也可以枚举三种操作的总次数与 $i, j$）

总时间复杂度为 $O(N ^ 3)$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 310, mod = 998244353;

int n, m, a, b, c, d, e, f, cnt;
long long ans, dp[N][N][N];
map<pair<long long, long long>, bool> mp;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> a >> b >> c >> d >> e >> f;
  while (m--) {
    int x, y;
    cin >> x >> y, mp[{x, y}] = 1;
  }
  dp[0][0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int u = 0; u <= i; u++) {
      for (int v = 0; u + v <= i; v++) {
        int w = i - u - v;
        long long x = 1ll * u * a + 1ll * v * c + 1ll * w * e;
        long long y = 1ll * u * b + 1ll * v * d + 1ll * w * f;
        if (mp.find({x, y}) == mp.end()) {
          dp[i][u][v] = dp[i - 1][u][v];
          if (u) {
            dp[i][u][v] = (dp[i][u][v] + dp[i - 1][u - 1][v]) % mod;
          }
          if (v) {
            dp[i][u][v] = (dp[i][u][v] + dp[i - 1][u][v - 1]) % mod;
          }
          if (i == n) {
            ans = (ans + dp[i][u][v]) % mod;
          }
        }
      }
    }
  }
  cout << ans;
  return 0;
}
```

---

