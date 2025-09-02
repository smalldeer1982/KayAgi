# Sum of Paths

## 题目描述

There are $ n $ cells, numbered $ 1,2,\dots, n $ from left to right. You have to place a robot at any cell initially. The robot must make exactly $ k $ moves.

In one move, the robot must move one cell to the left or right, provided that it doesn't move out of bounds. In other words, if the robot was in the cell $ i $ , it must move to either the cell $ i-1 $ or the cell $ i+1 $ , as long as it lies between $ 1 $ and $ n $ (endpoints inclusive). The cells, in the order they are visited (including the cell the robot is placed), together make a good path.

Each cell $ i $ has a value $ a_i $ associated with it. Let $ c_0, c_1, \dots, c_k $ be the sequence of cells in a good path in the order they are visited ( $ c_0 $ is the cell robot is initially placed, $ c_1 $ is the cell where the robot is after its first move, and so on; more formally, $ c_i $ is the cell that the robot is at after $ i $ moves). Then the value of the path is calculated as $ a_{c_0} + a_{c_1} + \dots + a_{c_k} $ .

Your task is to calculate the sum of values over all possible good paths. Since this number can be very large, output it modulo $ 10^9 + 7 $ . Two good paths are considered different if the starting cell differs or there exists an integer $ i \in [1, k] $ such that the current cell of the robot after exactly $ i $ moves is different in those paths.

You must process $ q $ updates to $ a $ and print the updated sum each time. Each update changes the value of exactly one cell. See the input format and the sample input-output for more details.

## 说明/提示

In the first example, the good paths are $ (1, 2), (2, 1), (2, 3), (3, 2), (3, 4), (4, 3), (4, 5), (5, 4) $ .

Initially the values of $ a $ are $ [3, 5, 1, 4, 2] $ . After the first update, they become $ [9, 5, 1, 4, 2] $ . After the second update, they become $ [9, 4, 1, 4, 2] $ , and so on.

## 样例 #1

### 输入

```
5 1 5
3 5 1 4 2
1 9
2 4
3 6
4 6
5 2```

### 输出

```
62
58
78
86
86```

## 样例 #2

### 输入

```
5 2 5
3 5 1 4 2
1 9
2 4
3 6
4 6
5 2```

### 输出

```
157
147
207
227
227```

## 样例 #3

### 输入

```
4 40 6
92 21 82 46
3 56
1 72
4 28
1 97
2 49
2 88```

### 输出

```
239185261
666314041
50729936
516818968
766409450
756910476```

# 题解

## 作者：zzr8178541919 (赞：8)

#### DP好题

首先观察数据范围：$ 2≤n≤5000,1≤k≤5000, 1\leq q\leq2*10^{5} $ ，于是想用一个$O(nk)$的复杂度来解决这道题。

发现直接计算很难，一条路径经过了哪些点很难表示出来。

换个思路：我想考虑每一个数对答案产生的贡献是多少？最终答案就是贡献之和。

贡献怎么计算呢？

发现一个性质：不管数字的值怎么变，对于所有长度为$k$的路径情况，第$i$位的数字总共经过了几次是不变的。也就是说，我们可以先处理出来每个数字总共经过$tot[i]$,那这一位数产生的贡献就是$a[i]*tot[i]$。

由于每次$tot[i]$是不变的，每次又只改动一个$a[i]$，我们完全可以预处理答案，每次把第$i$为的$x$改成$y$，我们只需要让
$ans=ans-tot[i]*x+tot[i]*y,a[i]=y $ 即可，查询的复杂度是$O(q)$的。

现在的问题是：怎么计算$tot[i]$呢？

设$dp[i][j]$表示走$j$步到达$i$的方案数。初始有$dp[i][0]=1$。转移方程很好想：$dp[i][j]=dp[i-1][j-1]+dp[i+1][j-1]$(注意边界特判)。

设$f[i][j]$表示走从$i$出发走$j$步的方案数。注意到从$i$出发走$j$步，把路径倒过来，不就是走$j$步到达$i$吗？它们是一一对应的，也就是说,$f[i][j]=dp[i][j]$，我们可以省掉$f[i][j]$。

那$tot[i]$不就等于$\sum\limits_{j=0}^{k}dp[i][j]*f[i][k-j]$吗，因为一条长度为$j$的以$i$为终点的路径和一条长度为$(k-j)$以$i$为起点的路径拼起来，就是一条长度为$k$的路径。我们枚举每个$j$，然后到$dp[i][j]$中任找一条路径，$f[i][k-j]$中任找一条路径，它们拼起来都是长度为$k$的路径，根据乘法原理，对$i$的$tot$产生的贡献就是$dp[i][j]*f[i][k-j]$了。

$code:$
```cpp
#include<bits/stdc++.h>

#define int long long

#define reg register
using namespace std;
const int maxn=1e6+5;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int n,k,Q;
int a[maxn];
int dp[5005][5005];
int f[5005][5005];
int ans=0;
int wns[5005];
signed main()
{
	n=read(),k=read(),Q=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		dp[i][0]=1;
	}
	for(int j=1;j<=k;j++)
	{
		for(int i=1;i<=n;i++)
		{
			if(i!=1)
			dp[i][j]=(dp[i][j]+dp[i-1][j-1])%mod;
			if(i!=n)
			dp[i][j]=(dp[i][j]+dp[i+1][j-1])%mod;
		}
	}
	int ans=0;
	for(int j=0;j<=k;j++)
	{
		for(int i=1;i<=n;i++)
		{
			f[i][j]=dp[i][j]*dp[i][k-j]%mod;
			wns[i]=(wns[i]%mod+f[i][j])%mod;
			ans=(ans+f[i][j]%mod*a[i])%mod;
		}
	}
	while(Q--)
	{
		//ans=0;
		int x,v;
		x=read(),v=read();
		//a[x]=v;
		ans=((ans-wns[x]%mod*a[x])%mod+mod)%mod;
		ans=(ans%mod+wns[x]%mod*v%mod)%mod;
		a[x]=v%mod;
		printf("%lld\n",ans%mod);
	}
	return 0;
}
/*
1 0 10
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
*/
```






---

## 作者：Refined_heart (赞：3)

简单 DP.

蒟蒻 VP 的时候读错了题……本来可以很快过掉的/kk

考虑设$g[i][j]$表示走$j$步以$i$结尾的路径条数。

有显然的转移：$g[i][j]=g[i+1][j-1]+g[i-1][j-1]$.

考虑计算一个点在所有路径中的出现次数：它应该等于:

$$\sum_j g[i][j]*g[i][k-j].$$

注意到一点，$g[i][j]$也可以阐释为从$i$出发走到其他点的路径条数。

于是我们枚举$i$点出现的步数$j$并从这一步继续往其他点走$k-j$步即满足题意。

于是这题做完了。单点修改什么的应该不用详细说了，直接把上次的减掉，加上这次的即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
inline int add(int x,int y){return (x+y)%mod;}
inline int mul(int x,int y){return 1ll*x*y%mod;}
int n,k,q,a[5002];
int dp[5002][5002];
int g[5002][5002];
int c[5001],cnt[5002];
int main(){
	scanf("%d%d%d",&n,&k,&q);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)dp[i][0]=1,g[i][0]=1;
	for(int i=1;i<=n;++i){
		if(i==1||i==n)dp[i][1]=2,g[i][1]=1;
		else dp[i][1]=4,g[i][1]=2;
	}
	for(int i=2;i<=k;++i){
		for(int j=1;j<=n;++j){
			dp[j][i]=add(dp[j][i],dp[j][i-1]);
			dp[j][i]=add(dp[j][i],g[j-1][i-1]);
			dp[j][i]=add(dp[j][i],g[j+1][i-1]);
			g[j][i]=add(g[j][i],g[j-1][i-1]);
			g[j][i]=add(g[j][i],g[j+1][i-1]);
			dp[j][i]=add(dp[j][i],g[j][i]);
		}
	}
	
//	for(int i=1;i<=n;++i)printf("%d %d %d %d\n",dp[i][1],dp[i][2],g[i][1],g[i][2]);
	for(int i=1;i<=n;++i){
		for(int j=0;j<=k;++j)
			cnt[i]=add(cnt[i],mul(g[i][j],g[i][k-j]));
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		c[i]=mul(cnt[i],a[i]);
		ans=add(ans,c[i]);
	}
	while(q--){
		int x,v;
		scanf("%d%d",&x,&v);
		ans-=c[x];ans+=mod;ans%=mod;
		c[x]=mul(cnt[x],v);
		ans=add(ans,c[x]);
		cout<<ans<<endl;
	}
	return 0;
} 
```
(代码里面的dp数组没有用)

---

## 作者：Imitators (赞：3)

考虑每个点的权重的贡献，记作 $cnt_i$。

$cnt_i$ 不会改变，所以现在我们要求 $cnt_i$ 即这个点能被经历多少次。

首先考虑走走走，最后停到了 $x$ 的方案数。

这个 $dp$ 十分简单，设 $f[i][j]$ 表示走 $j$ 步最后停到 $i$。

转移 $f[i][j]=f[i-1][j-1]+f[i+1][j-1]$ （到 $i$ 可能从 $i-1$ , $i+1$）。

由于路径可逆，$f[i][j]$ 被赋予了新的含义，从 $i$ 开始，走 $j$ 步的方案数。

$cnt_i$ 真心不好直接求，我们把他分解成 $cnt_i=\sum_{j=0}^{k} a[i][j]$ 。

$a[i][j]$ 表示第 $j$ 步经历 $i$ 的总方案数。

拿这个算肯定是不重不漏的。

$a[i][j]=f[i][j]\times f[i][k-j]$。

表示有 $f[i][j]$ 种情况 $j$ 步后到 $i$, 然后有 $f[i][k-j]$ 种情况，从 $i$ 出发直到结束。

这道题到这里也就做完了

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,q;
const int N=5100;
int dp[N][N],a[N][N];
int cnt[N],v[N];
const int mod=1e9+7;
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n>>k>>q;
    for(int i=1;i<=n;i++) cin>>v[i];
    for(int i=1;i<=n;i++) dp[i][0]=1;
    for(int j=1;j<=k;j++)
        for(int i=1;i<=n;i++)
            dp[i][j]=(dp[i-1][j-1]+dp[i+1][j-1])%mod;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=k;j++)
            a[i][j]=dp[i][j]*dp[i][k-j]%mod;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=k;j++)
        {
            cnt[i]+=a[i][j];
            cnt[i]%=mod;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans+=cnt[i]*v[i];
        ans%=mod;
    }
    while(q--)
    {
        int x,y;
        cin>>x>>y;
        ans+=(y-v[x])*cnt[x];
        v[x]=y;
        ans%=mod;ans+=mod;ans%=mod;
        cout<<ans<<endl;
    }
}
```

---

## 作者：ZCETHAN (赞：2)

[传送门](http://codeforces.com/problemset/problem/1467/D)
## 题目大意
数轴上有 $n$ 个点，一个机器人从任意位置出发，每个时刻任意向左或者向右，到达一个位置就加上这个位置的分数，求最后走 $k$ 步所有可能的分数之和。

并且有 $q$ 次询问，每次修改一个点权。
## Solution
显然不能直接做。所以考虑拆开算贡献。

对于一个点，我们考虑会在路径中出现多少次。考虑用 $dp$ 算。

设 $cnt_{i,j}$ 为第 $i$ 步的时候走到 $j$ 号点的路径数，那么有：

$$cnt_{i,j}=cnt_{i-1,j-1}+cnt_{i-1,j+1}$$

但是我们不知道到达第 $i$ 号点的时候是路径的第几部，所以考虑再设一个 $cnt'_{i,j}$ 表示从 $j$ 号节点出发，走 $i$ 步的路径总数，结果发现递推式和 $cnt$ 一模一样，那就直接用 $cnt$ 了。这样递推是 $O(n^2)$ 的可以接受。

然后考虑用 $cnt$ 来求出一个点在所有路径中出现的次数。

枚举点 $i$ 在路径中是第 $j$ 个点，那么有（$mul$ 就表示出现次数）：

$$mul=\sum_{j=0}^kcnt_{j,i}\times cnt_{k-j,i}$$

于是我们成功求出每个点出现的次数，然后乘上点的权值就是最后对答案的贡献了。

至于修改，用树状数组或者线段树维护一下就可以了。

复杂度是 $O(n^2+q\log n)$，可以过。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf (1<<30)
#define INF (1ll<<60)
using namespace std;
const int MAXN=5010;
const ll MOD=1e9+7;
ll cnt[MAXN][MAXN],a[MAXN],mul[MAXN];
ll tr[MAXN];
int n;
int lbt(int x){return x&(-x);}
void upd(int x,ll v){
	for(int i=x;i<=n;i+=lbt(i))
		tr[i]=(tr[i]+v)%MOD;
}
ll ask(int x){
	ll ret=0;
	for(int i=x;i;i-=lbt(i))
		ret=(ret+tr[i])%MOD;
	return ret;
}
void solve(){
	int k,Q;
	scanf("%d%d%d",&n,&k,&Q);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),cnt[0][i]=1;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++)
			cnt[i][j]=(cnt[i-1][j-1]+cnt[i-1][j+1])%MOD;
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<=k;j++)
			mul[i]=(mul[i]+cnt[j][i]*cnt[k-j][i]%MOD)%MOD;
	for(int i=1;i<=n;i++)
		upd(i,mul[i]*a[i]%MOD);
	int p;ll x;
	while(Q--){
		scanf("%d%lld",&p,&x);
		upd(p,(MOD-a[p]*mul[p]%MOD)%MOD);
		a[p]=x;
		upd(p,a[p]*mul[p]%MOD);
		printf("%lld\n",ask(n)%MOD);
	}
}
int main()
{
//	int T;
//	for(scanf("%d",&T);T--;)
		solve();
	return 0;
}
```

---

## 作者：RyexAwl (赞：2)

考虑计算每个位置对答案的贡献，我们发现每个位置的贡献即被所有路径经过的次数乘上点权。

（下文所有描述下标均为$0\sim k$）
那么我们当前的问题即：

按如下方式构造长度为$k+1$的序列$a[]$:

$1.\forall0\le i \le k,a[i]\in [1,n]$

$2.\forall1\le i < k,a[i+1]=a[i]+1/a[i]-1,a[i-1]=a[i]+1/a[i]-1$ 

考虑数出$x$在所有满足要求的序列$a[]$中出现的次数。

我们将其所有的序列构造成一个矩阵，其中$m[i][j]=[a[i][j]=x]$。

那么$x$在其出现的次数即矩阵元素和，行求和比较困难，考虑列求和。

令$f[i][j]$为长度为所有满足条件的序列$a[]$中位置$i$为$j$的序列数，那么我们发现这就转化为了一个数序列的问题。

我们发现其序列可以分成两部分：

$1.$位置$0\sim i$：长度为$i+1$且位置$i$为$j$的序列$a[]$

$2.$位置$i\sim k$：第$1$位是$i$且长度为$k-i+1$的序列$a[]$

且这两部分满足乘法原理。

令$g[i][j]$为长度为$i+1$且位置$i$为$j$的序列$a[]$的数量，有：
$$
g[i][j]=g[i-1][j+1]+g[i-1][j-1]
$$
且$g[0][j]=1$
我们发现，其$g[i][j]$所代表的组合意义又包括长度为$i+1$且位置$0$为$j$的序列$a[]$的数量。
因此
$$
f[i][j]=g[i][j]\times g[k-i][j]
$$
位置$j$的贡献即
$$
w[j]\sum_{0\le i\le k}g[i][j]\times g[k-i][j]
$$
修改操作简单维护即可。

总结：考虑将一些直接求解比较困难的问题拆成贡献转化为数数解决通常会简化问题，在数所有满足某个条件的序列某个元素出现的次数时通常可以转化为$01$矩阵列求和以此转化为数序列的问题，以及在数满足第$k$位是$j$的序列个数时，可以考虑将其按第$k$位前后分成两段数最后乘法原理乘出个数。

代码：
```cpp
#include <iostream>

namespace wxy{
	const int N = 5050,mod = 1e9 + 7;
	#define int unsigned long long
	int a[N],f[N][N],g[N][N],times[N],n,k,q;
	void main(){
		std::cin >> n >> k >> q;
		for (int i = 1; i <= n; i++) g[0][i] = 1;
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= n; j++){
				if (j == 1) g[i][j] = g[i - 1][j + 1];
				else if (j == n) g[i][j] = g[i - 1][j - 1];
				else g[i][j] = (g[i - 1][j + 1] + g[i - 1][j - 1]) % mod;
				if (i >= k - i) f[i][j] = f[k - i][j] = (g[i][j] * g[k - i][j]) % mod;
			}
		for (int i = 1; i <= n; i++)
			for (int j = 0; j <= k; j++) times[i] = (times[i] + f[j][i]) % mod;
		int ans = 0;
		for (int i = 1; i <= n; i++) std::cin >> a[i];
		for (int i = 1; i <= n; i++) ans = (ans + times[i] * a[i]) % mod;
		while (q--){
			int x,val;
			std::cin >> x >> val;
			ans = (ans - (times[x] * a[x]) % mod + mod) % mod;
			a[x] = val;ans = (ans + times[x] * a[x]) % mod;
			std::cout << ans << std::endl;
		}
	}
}signed main(){wxy::main();return 0;}
```




---

## 作者：wmy_goes_to_thu (赞：2)

$n,k$ 都是固定的，所以我们只需要考虑第 $i$ 个位置经过了多少次即可。

我们需要枚举是第几步经过的这个位置，需要一共有多少种走法在第 $i$ 步经过它。往后需要 $k-i$ 步，由于路线是可逆的，所以往前走 $i$ 步就行。如果设 $f_{i,j}$ 代表现在在 $i$ 点，走 $j$ 步有多少条路径，这个用 dp 很容易求出。那么枚举第 $i$ 步经过 $j$ 的总方案数就是 $f_{j,i} \times f_{j,k-i}$。

每次询问只需要把求好的答案修改一个点就行，很容易。

---

## 作者：kimi0705 (赞：0)

考虑 $dp$。

显然的，要计算出每一个点的贡献，记为 $c_i$。

那么答案为 $ans=\sum_{i=1}^{n}c_i\times a_i$。

对于每次询问，更新 $ans$ 时间复杂度显然为 $O(1)$。

所以只要求 $c_i$ 问题就迎刃而解了。

计 $f_{i,j}$ 为起点是 $i$ 走 $j$ 步的方案数。

因为可以把路径反过来，所以 $f_{i,j}$ 也为终点是 $i$ 走 $j$ 步的方案数。

所以显然 $f_{i,j}=f_{i-1,j-1}+f_{i+1,j-1}$。

所以 $c_i=\sum_{j = 0}^{k} f_{i,j}f_{i,k-j}$。其中 $f_{i,j}$ 表示终点为 $i$ 的路径种数，$f_{i, k- j}$ 为起点为 $i$ 的路径种数。

所以 $ans=\sum_{i=1}^{n}(\sum_{j = 0}^{k} f_{i,j}f_{i,k-j})\times a_i$。

---

## 作者：mango2011 (赞：0)

令 $f_{i,j}$ 为走 $i$ 步到 $j$ 的方案数，$g_{i,j}$ 为从 $i$ 开始走 $j$ 步的方案数。

初始值：$f_{0,i}=1(1\le i\le n)$，$g_{i,0}=1(1\le i\le n)$。

转移：$f_{i,j}=f_{i-1,j-1}+f_{i-1,j+1}$，$g_{i,j}=g_{i-1,j-1}+g_{i+1,j-1}$。

然后考虑每个点经过的次数：

第 $i$ 个点总共走 $k$ 次经过被经过的次数为 $\displaystyle\sum_{j=0}^{k}f_{j,i}\times g_{i,k-j}$。

显然，每个点被经过的次数是固定的，所以询问与修改的操作都可以 $O(1)$ 进行，代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5005;
const int mod=1e9+7;
int f[maxn][maxn],g[maxn][maxn],a[maxn];
signed main(){
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
	int n,k,q,ans=0;
	cin>>n>>k>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[0][i]=1;
		g[i][0]=1;
	}
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			g[j][i]+=g[j-1][i-1]+g[j+1][i-1];
			g[j][i]%=mod;
		}
	}
//	cout<<g[n][1]<<endl;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			f[i][j]+=f[i-1][j-1]+f[i-1][j+1];
			f[i][j]%=mod;
		}
	}
	for(int i=0;i<k;i++){
		for(int j=1;j<=n;j++){
			f[k][j]+=f[i][j]*g[j][k-i];
			f[k][j]%=mod;
		}
	} 
	for(int i=1;i<=n;i++){
		ans+=f[k][i]*a[i];
		ans%=mod;
	}
	while(q--){
		int i,t;
		cin>>i>>t;
		ans+=(t-a[i])*f[k][i];
		ans%=mod;
		if(ans<0){
			ans+=mod;
		}
		a[i]=t;
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：james1BadCreeper (赞：0)

不难发现权值就是纸老虎，因为权值的改变不会影响行走时的方案数，只需要 $O(1)$ 计算答案的增量即可。

现在的问题是如何求经过每个点的次数。因此设 $f_{i,j}$ 代表从 $i$ 开始，走了 $j$ 步的方案数，$g_i$ 代表经过 $i$ 的总次数。$g$ 在计算时只要用到达它的方案数乘上离开它的方案数即可，有：

$$
\begin{aligned}
f_{i,j}&=f_{i-1,j-1}+f_{i+1,j-1},\\
g_i&=\sum f_{i,j}\times f_{i,k-j}.
\end{aligned}
$$

然后就可以直接计算了，时间复杂度 $O(nk+q)$。

```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 1000000007; 

int n, k, q; 
int a[5005], f[5005][5005], g[5005]; 

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> k >> q; 
    for (int i = 1; i <= n; ++i) cin >> a[i], f[i][0] = 1; 
    for (int j = 1; j <= k; ++j) for (int i = 1; i <= n; ++i) f[i][j] = (f[i - 1][j - 1] + f[i + 1][j - 1]) % P; 
    for (int i = 1; i <= n; ++i) for (int j = 0; j <= k; ++j) g[i] = (g[i] + 1ll * f[i][j] * f[i][k - j]) % P; 

    int ans = 0; 
    for (int i = 1; i <= n; ++i) ans = (ans + 1ll * g[i] * a[i]) % P; 
    while (q--) {
        int x, v; cin >> x >> v; 
        ans = (ans - 1ll * g[x] * a[x]) % P; 
        a[x] = v; 
        ans = (ans + 1ll * g[x] * a[x]) % P; 
        cout << (ans + P) % P << "\n"; 
    }
    return 0; 
}
```

---

