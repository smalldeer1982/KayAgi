# Graph Cost

## 题目描述

You are given an initially empty undirected graph with $ n $ nodes, numbered from $ 1 $ to $ n $ (i. e. $ n $ nodes and $ 0 $ edges). You want to add $ m $ edges to the graph, so the graph won't contain any self-loop or multiple edges.

If an edge connecting two nodes $ u $ and $ v $ is added, its weight must be equal to the greatest common divisor of $ u $ and $ v $ , i. e. $ \gcd(u, v) $ .

In order to add edges to the graph, you can repeat the following process any number of times (possibly zero):

- choose an integer $ k \ge 1 $ ;
- add exactly $ k $ edges to the graph, each having a weight equal to $ k + 1 $ . Adding these $ k $ edges costs $ k + 1 $ in total.

 Note that you can't create self-loops or multiple edges. Also, if you can't add $ k $ edges of weight $ k + 1 $ , you can't choose such $ k $ .For example, if you can add $ 5 $ more edges to the graph of weight $ 6 $ , you may add them, and it will cost $ 6 $ for the whole pack of $ 5 $ edges. But if you can only add $ 4 $ edges of weight $ 6 $ to the graph, you can't perform this operation for $ k = 5 $ .

Given two integers $ n $ and $ m $ , find the minimum total cost to form a graph of $ n $ vertices and exactly $ m $ edges using the operation above. If such a graph can't be constructed, output $ -1 $ .

Note that the final graph may consist of several connected components.

## 说明/提示

In the first test case, we can add an edge between the vertices $ 2 $ and $ 4 $ with $ \gcd = 2 $ . This is the only possible way to add $ 1 $ edge that will cost $ 2 $ .

In the second test case, there is no way to add $ 10 $ edges, so the answer is $ -1 $ .

In the third test case, we can add the following edges:

- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 2 $ and $ 4 $ ( $ \gcd(2, 4) = 2 $ ). Cost: $ 2 $ ;
- $ k = 1 $ : edge of weight $ 2 $ between vertices $ 4 $ and $ 6 $ ( $ \gcd(4, 6) = 2 $ ). Cost: $ 2 $ ;
- $ k = 2 $ : edges of weight $ 3 $ : $ (3, 6) $ and $ (3, 9) $ ( $ \gcd(3, 6) = \gcd(3, 9) = 3 $ ). Cost: $ 3 $ .

 As a result, we added $ 1 + 1 + 2 = 4 $ edges with total cost $ 2 + 2 + 3 = 7 $ , which is the minimal possible cost.

## 样例 #1

### 输入

```
4
4 1
6 10
9 4
10 11```

### 输出

```
2
-1
7
21```

# 题解

## 作者：Inui_Sana (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1731E)

今天刚爬就评级了，还是蓝，所以写个题解。

既然每次操作要连 $k$ 条边，要求 $\gcd(u,v)=k+1$，那么我们就要知道满足 $\gcd(a,b)=k+1$ 的二元组有多少个。因为 $\gcd(a,b)=k+1$，那么 $\gcd(\frac a{k+1},\frac b{k+1})=1$。这样问题就转换成了 $a,b\le \frac n{k+1}$，$a$ 与 $b$ 互质的二元组有多少个。提到互质，自然会想到欧拉函数。所以可以得出，二元组个数 $=\sum_{i=1}^{\frac n{k+1}}\varphi(i)$。

所以，我们可以用线性筛筛出 $1$ 至 $n$ 的欧拉函数值并记录前缀和。根据贪心，最优策略肯定是优先取更大的 $k$ 值。所以再从大到小枚举 $k$，能连就连。具体细节可以看代码。

注意前缀和数组要开 `long long`。

code：

```cpp
int n,k,pm[N],ph[N];ll m,sum[N];
bool vis[N];
void solve(){
	scanf("%d%lld",&n,&m);
	ll ans=0;
	for(int i=n-1;i&&m;i--){
		if(i>m)continue;
		ll x=sum[n/(i+1)]/i;//能操作多少次
		if(i*x>=m)ans+=(ll)(i+1)*(m/i),m%=i;//如果能连边数大于需要连的边数，操作直到需要数小于k为止
		else ans+=(ll)(i+1)*x,m-=(ll)i*x;//否则全连
	}
	if(m)puts("-1");
	else printf("%lld\n",ans);
}
signed main(){
	const int mx=1e6;
	for(int i=2;i<=mx;i++){
		if(!vis[i])pm[++k]=i,ph[i]=i-1;
		sum[i]=sum[i-1]+(ll)ph[i];
		for(int j=1;j<=k&&pm[j]<=mx/i;j++){
			vis[i*pm[j]]=true;
			if(i%pm[j]==0){
				ph[i*pm[j]]=ph[i]*pm[j];
				break;
			}
			ph[i*pm[j]]=ph[i]*(pm[j]-1);
		}
	}
	int t=1;
	scanf("%d",&t);
	while(t--)solve();
}

---

## 作者：MortisM (赞：2)

[题目链接](https://codeforces.com/problemset/problem/1731/E)

主要讲一下证明。

考虑选 $k$ 条边能选几个，这个问题也就是说选多少对 $1\le x<y\le n$ 满足 $\gcd(x,y)=k+1$。可以把它们都除以 $k+1$，得到的就是有多少对 $1\le x<y\le\lfloor\frac{n}{k+1}\rfloor$ 满足 $\gcd(x,y)=1$，这个显然是 $\displaystyle\sum_{i=2}^{\lfloor\frac{n}{k+1}\rfloor}\varphi(i)$。

考虑到均摊到 $k$ 个点上每个点的代价都是 $\frac{k+1}{k}$，所以要代价小则必然要 $k$ 先选大的。这里给一个证明：

假设存在某个 $x>y>z$ 使得选 $x,z$ 比选 $y$ 劣。设 $y$ 选了 $c$ 个，则最坏情况下 $z$ 选 $c-1$ 个，$x$ 选 $1$ 个。此时 $(c-1)z+x=cy$，即代价相等。所以得到结论。

线性筛欧拉函数，做个前缀和，每次暴力的到着扫即可。时间复杂度 $\mathcal{O}(n)$，比官方题解的 $\mathcal{O}(n\log n)$ 的优。[代码](https://codeforces.com/contest/1731/submission/188571676)。

---

## 作者：Priestess_SLG (赞：1)

~~呃呃呃，大水题~~

首先有一个简单的贪心策略：先加边权大的边，然后再加边权小的边。容易证明她是正确的。

然后问题变为对于每一个 $k\in[1,n]\cap\mathbb{N_+}$ 计算有多少个整数对 $(i,j)$ 满足 $1\le i<j\le n$ 且 $\gcd(i,j)=k$ 了。考虑 dp。设 $f_i$ 表示 $k=i$ 时上式的答案，则显然有 $f_i=\lfloor\frac{n}{i}\rfloor^2$。但是这显然是错的，因为 $2i$ 有可能被错误的统计在 $i$ 内。考虑容斥。将所有 $i$ 的倍数且不为 $i$ 的数的贡献在 $f_i$ 中减去。因此有：

$$f_i=\lfloor\frac{n}{i}\rfloor^2-\sum\limits_{k=2}^{+\infin}f_{ki}$$

直接暴力计算 $f$ 的值是调和级数的，因此这样就能在单组数据 $O(n\log n)$ 的时间复杂度内通过该题目。

代码：

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define int long long
using namespace std;
const int N = 1000100;
int f[N];
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        for (int i = n; i; --i) {
            f[i] = (n / i) * (n / i);
            for (int j = 2; j * i <= n; ++j) {
                f[i] -= f[j * i];
            }
        }
        int sum = 0, cnt = 0;
        for (int i = n; i > 1; --i) {
            int k = min(m, f[i] / 2) / (i - 1) * (i - 1);
            m -= k;
            sum += k / (i - 1) * i;
        }
        if (m) {
            sum = -1;
        }
        cout << sum << '\n';
    }
    return 0;
}

```

---

## 作者：yingkeqian9217 (赞：0)

## 前置芝士

欧拉函数 $\varphi(x)$：表示小于等于 $x$ 的正整数中与 $x$ 互质的数的个数。可以使用欧拉筛求解。

## 题目描述

给定 $n$ 个点无边的无向图，连接点 $u$ 和  $v$ 需要满足边权为 $\gcd(u,v)$，每次操作可以连接 $k$ 条边权为 $k+1$ 的边，代价为 $k+1$ ，问恰好连接到 $m$ 条边的最小代价。

## 分析

因为对于每个 $k$，每次一定要连 $k$ 条才合法，所以我们不妨考虑一下对于当前的 $n,k$，最多能连几条边。也就是求 $1$ 到 $n$ 内有多少对数的最大公因数为 $k+1$。

首先，这对数显然一定是 $k+1$ 的倍数，我们先把这些数拿出来看一看：$k',2 k',3k'......\lfloor\dfrac{n}{k'}\rfloor\times k'$，为了方便，我们使 $k'=k+1$。那么最终答案肯定要从这里选。对于两个数 $xk',yk'$，考虑到要求 $\gcd(xk',yk')=k'$，即要求 $\gcd(x,y)=1$，也就是要求两数互质。

然后我们的问题就变成了求 $1$ 到 $\lfloor\dfrac{n}{k'}\rfloor$ 内互质的数对的个数。看到互质的数对的个数，不难想到欧拉函数 $\varphi$。但是这里 $\varphi$ 只能求与当前数互质的小于等于它的数的个数。于是我们就可以预处理。

我们记 $1$ 到 $p$ 内互质的数对的个数为 $f_x$，那么显然可以得到 $f_x=f_{x-1}+\varphi(x),x\ge 3$。也就是求前缀，这个我们只要在处理欧拉函数之后顺便求一下即可。但是此处当 $x\le 2$ 时还需注意，我们可以特别处理一下，即 $f_1=0,f_2=1=\varphi(2)$。

于是我们知道了求 $1$ 到 $n$ 内有 $\min(f_{\lfloor\frac{n}{k+1}\rfloor},m)$ 对数的最大公因数为 $k+1$。但是我们一次性要操作 $k$ 条边，所以要对这个数除以 $k$ 才得到对于当前 $k$，我们能操作的次数，由此得知对总边数与总代价的贡献。

问题是求解最小代价，观察代价公式，我们发现，代价其实就是本次操作处理的边数 $+1$。但我们的总边数不变，唯一的变数在于后面的 $1$。所以我们要使操作次数最少，也就是说，我们要使每次的 $k$ 尽量大，枚举时从大至小即可。

## AC CODE
```
#include<bits/stdc++.h>
#define maxn 2900001
#define int long long
using namespace std;
int T,n,m;
int cnt,phi[maxn],p[maxn],fl[maxn];
void solve(){
	int ans=0;
	scanf("%lld%lld",&n,&m);
	for(int i=n;i>=2;i--){//为了方便，此处枚举的是k+1
		int num=min(phi[n/i],m)/(i-1);
		ans+=num*i;
		m-=num*(i-1);
	}
	if(m) ans=-1;//注意特判
	printf("%lld\n",ans);
}
signed main(){
	scanf("%lld",&T);
	phi[1]=1;
	for(int i=2;i<=2e6;i++){
		if(fl[i]==0){
			p[++cnt]=i;
			phi[i]=i-1;
		}
		for(int j=1;j<=cnt&&i*p[j]<=2e6;j++){
			fl[p[j]*i]=1;
			if(i%p[j]==0){
				phi[p[j]*i]=phi[i]*p[j];
				break;
			}
			else phi[p[j]*i]=phi[i]*phi[p[j]];
		}
	}
	phi[1]=0;
	for(int i=3;i<=2e6;i++)
	 phi[i]=phi[i-1]+phi[i];//此处采用的是直接覆盖原来的phi数组
	while(T--){
		solve();
	}
	return 0;
}
```

---

