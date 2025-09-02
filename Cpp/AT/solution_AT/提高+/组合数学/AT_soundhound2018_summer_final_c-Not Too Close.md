# Not Too Close

## 题目描述

[problemUrl]: https://atcoder.jp/contests/soundhound2018-summer-final/tasks/soundhound2018_summer_final_c

$ N $ 頂点の無向グラフであって、以下の条件をすべて満たすものの個数を $ 10^9\ +\ 7 $ で割った余りを求めてください。

- $ N $ 個の頂点には $ 1 $ から $ N $ までの番号が振られている。
- グラフは自己辺や多重辺を持たない（連結である必要はない）。
- すべての辺の長さを $ 1 $ とすると、頂点 $ 1,\ 2 $ 間の最短距離は $ D $ である。

## 说明/提示

### 注記

二つのグラフ $ G_1,\ G_2 $ は、以下が満たされる場合に異なるとみなされ、満たされない場合に同一とみなされます。

- ある整数の組 $ (i,\ j) $ $ (1\ <\ =\ i\ <\ j\ <\ =\ N) $ が存在し、頂点 $ i,\ j $ を直接結ぶ辺が $ G_1,\ G_2 $ のうち一方のみに存在する。

### 制約

- $ 1\ <\ =\ D\ <\ N\ <\ =\ 30 $
- $ N,\ D $ は整数である。

### Sample Explanation 1

条件を満たすグラフは下図の $ 2 $ 通りです。 !\[\](https://img.atcoder.jp/soundhound2018-summer-final/4b0c83895d12c1a9c90cb3e8060db969.png)

### Sample Explanation 2

条件を満たすグラフは下図の $ 14 $ 通りです。 !\[\](https://img.atcoder.jp/soundhound2018-summer-final/df4dffb7f2140b22a6c7ccc86f6c9cf9.png)

### Sample Explanation 3

mod $ (10^9\ +\ 7) $ にご注意ください。

## 样例 #1

### 输入

```
4 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4 2```

### 输出

```
14```

## 样例 #3

### 输入

```
30 15```

### 输出

```
313862829```

# 题解

## 作者：Zhao_daodao (赞：0)

## [Not Too Close](https://www.luogu.com.cn/problem/AT_soundhound2018_summer_final_c)

简单 dp。发现可以一层一层 dp。

把距离 1 最短路长度相同的点分为一层。则一层只会内部连边，或者向上一层和下一层连边。

定义状态 $f_{i,j,k}$ 表示当前共 $i$ 层，一共使用了 $j$ 个点，第 $i$ 层 $k$ 个点的总方案数。

枚举 $i+1$ 层的大小 $l$。

- 选点。

  因为点 2 只能在第 $d$ 层，所以要分类讨论。

  - 若 $i=d-1$，则一共有 $\binom{n-j-1}{l-1}$ 种方案。
  - 若 $i\ne d-1$，则一共有 $\binom{n-j-1}{l}$ 种方案。

- 第 $i+1$ 层可以互相连边。贡献 $2^{\binom{l}{2}}$。

- 第 $i$ 层与 $i+1$ 层的连边，每一个 $i+1$ 层的点至少连接一个第 $i$ 层的点。一共 $(2^k-1)^l$。

考虑答案计算。最后的状态为 $dp_{d,j,k}$。

因为一些点可以在 $d$ 层之后，这些点就没有必要计算了。

他们可以随便连：$2^{\binom{n-j}{2}}$。

还可以任意向第 $d$ 层连边：$2^{(n-j)k}$。

直接就算完了啊。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,d,fc[1005],c[105][105];
int dp[35][35][35];//共 i 层,总共 j 个,当前节点 k 个
inline int ksm(int a,int b){int cnt=1;while(b){if(b&1)cnt=cnt*a%mod;a=a*a%mod;b>>=1;}return cnt;}
inline int C(int x,int y){
    if(x<0||y<0||x<y)return 0;
    return c[x][y];
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>d;
    fc[0]=1;for(int i=1;i<=1000;i++)fc[i]=fc[i-1]*2%mod;
    for(int i=0;i<=100;i++){
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++)c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    }
    dp[0][1][1]=1;
    for(int i=0;i<d;i++)for(int j=i;j<=n;j++)for(int k=1;k<=j;k++){
        for(int l=1;l<=n-j;l++){
            #define old dp[i][j][k]
            #define now dp[i+1][j+l][l]
            (now+=old*C(n-j-1,l-(i==d-1))%mod*fc[C(l,2)]%mod*ksm(fc[k]+mod-1,l)%mod)%=mod;
        }
    }
    int ans=0;
    for(int j=d;j<=n;j++)for(int k=1;k<=j;k++){
        (ans+=dp[d][j][k]*fc[C(n-j,2)]%mod*fc[(n-j)*k]%mod)%=mod;
    }
    cout<<ans<<"\n";
}
```

---

## 作者：AC_love (赞：0)

注意到所有点可以根据最短路分层。

设 $f(i, j, k)$ 表示当前在第 $i$ 层，已经用了 $j$ 个点，其中第 $i$ 层有 $k$ 个点的方案数。

发现 $f(i, j, k)$ 一定是从某个 $f(i - 1, j - k, l)$ 转移过来的。具体乘的系数分为三部分：

- 从剩余点中选 $k$ 个的方案数，这部分系数是 ${n - j + k - 1 \choose k - [i = d]}$。
- 从第 $i - 1$ 层向第 $i$ 层连边的方案数，这部分系数是 $(2 ^ l - 1) ^ k$。
- 第 $i$ 层内部互相连边的方案数，这部分系数是 $2 ^ \frac{k(k - 1)}{2}$。

分别计算即可。

最后统计答案，其他没选的点可以和第 $d$ 层的点随便连，这些点内部也可以随便连，用同上的方式分别计算系数即可。

[code](https://atcoder.jp/contests/soundhound2018-summer-final/submissions/59085941)

---

## 作者：Hadtsti (赞：0)

~~题号太长就不放在题目里了，给个[链接](https://www.luogu.com.cn/problem/AT_soundhound2018_summer_final_c)。~~
### 题意简述

一张无向图有 $n(2\le n\le30)$ 个点，已知它的所有边权都是 $1$。求满足点 $1$ 和点 $2$ 之间的最短路为给定的 $D(1\le D<n)$ 的无向图的数量。

### 题目分析

考虑在每个图上将到点 $1$ 的距离相同的点看作同一层。那么我们得到每一层的点只会与上一层、下一层及同层的点有连边（连边的两个点跨度不会超过 $1$ 层，否则距离点 $1$ 更远的那个点到 $1$ 的最短路可以更短，矛盾）。由于边是无向边，不妨只在距离点 $1$ 更近的那个点统计跨层的边。

设 $f_{i,j,k}$ 为共 $j$ 个与点 $1$ 距离不超过 $i$ 的点，且共 $k$ 个点与点 $1$ 的距离正好为 $i$ 的方案数（多记 $k$ 一维是为了方便扩展状态）。对于每个状态的扩展，枚举下一层点的个数 $l$。则方案数可分为三部分：

- 下一层的点具体是哪些：$\binom{n-j-1}{l-[i+1=D]}$
- 下一层内点互相之间的连边情况：$2^{\binom l2}$
- 该层与下一层之间连边情况：$(2^k-1)^l$

回到原问题，我们只计算前 $D$ 层的 $f$。而对于每一个 $f_{D,j,k}$，未确定的点互相之间可以任意连，但都只能连第 $D$ 层确定的点，因此方案数为 $2^{k(n-j)+\binom{n-j}2}$。

总时间复杂度为 $O(n^4)$，$n\le30$ 绰绰有余。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,mod,pow2[45010],f[160][160][160],C[160][160],ans;
int main()
{
	scanf("%d%d%d",&n,&d,&mod);
	pow2[0]=1;
	for(int i=1;i<=n*n;i++)
		pow2[i]=(pow2[i-1]<<1)%mod;//预处理 2 的幂
	for(int i=0;i<=n;i++)
		C[i][0]=C[i][i]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;//组合数
	f[0][1][1]=1;
	for(int i=0;i<d;i++)
		for(int j=i;j<=n;j++)
			for(int k=1;k<=j-i+1;k++)
				if(f[i][j][k])
					for(int tmp=f[i][j][k],l=1;l<=n-j-d+i+1;l++)
						tmp=1ll*tmp*(pow2[k]-1)%mod,f[i+1][j+l][l]=(f[i+1][j+l][l]+1ll*tmp*pow2[l*(l-1)/2]%mod*C[n-j-1][l-(i+1==d)]%mod)%mod;//上文提到的三种情况乘法原理乘在一起就行了
	for(int i=d;i<=n;i++)
		for(int k=1;k<=n;k++)
			ans=(ans+1ll*f[d][i][k]*pow2[(n-i)*(n-i-1)/2+(n-i)*k]%mod)%mod;//第 D 层统计答案
	printf("%d",ans);
	return 0;
}
```

---

## 作者：VainSylphid (赞：0)

## 题意简述

构造一张有 $n$ 个点的无向连通图，满足 $1$ 号节点到 $2$ 号节点的最短距离为 $d$，求方案数，对 $10^9+7$ 取模。

## 思路

回忆单源最短路的算法流程，不难发现如果按照到源点的距离，整张图会被分成若干层，满足只有同一层之间和最短路相差 $1$ 的两层之间会有连边。

考虑设 $f_{i,j,k}$ 表示考虑到第 $i$ 层，前 $i$ 层一共有 $j$ 个节点，且第 $i$ 层有 $k$ 个节点的方案数，然后主动转移 dp 计算。

枚举第 $i+1$ 层的节点数 $w$，则容易得出转移方程：

$$\displaystyle f_{i+1,j+w,w}=f_{i,j,k}\times (2^k-1)^w\times 2^\tbinom{w}{2}\times \tbinom{n-j-1}{w}$$

其中 $(2^k-1)^w$ 是第 $i$ 层和第 $i+1$ 层之间连边的方案数，$2^\tbinom{w}{2}$ 是第 $i+1$ 层内部连边的方案数。$\tbinom{n-j-1}{w}$ 则是选取第 $i+1$ 层的节点的方案数。注意当 $i+1=d$ 时需要留一个位置给 $2$ 号节点，因此当 $i+1=d$ 时转移方程为：

$$\displaystyle f_{d,j+w,w}=f_{d-1,j,k}\times(2^k-1)^w\times 2^\tbinom{w}{2}\times \tbinom{n-j-1}{w-1}$$

然后考虑 $f_{d,j,k}$ 对答案的贡献，此时还剩下 $n-j$ 个点没有使用，它们内部之间可以任意连边，但是对于已经使用过的点，只能和第 $d$ 层的点连边，所以答案就出来了：

$$\displaystyle ans=\sum_{j=d}^{n}{\sum_{k=1}^{n}{f_{d,j,k}\times 2^{k\times (n-j)+\tbinom{n-j}{2}}}}$$

其中 $2^{k\times (n-j)}$ 表示未使用的点和和第 $d$ 层的点连边的方案数，$2^{\tbinom{n-j}{2}}$ 表示未使用的点内部的连边方案数。

$O(n^2)$ 预处理组合数和 $2$ 的幂次，即可做到时间复杂度 $O(n^4)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,d,mod = 1e9 + 7,pw[23005],dp[205][205][205],C[205][205];
int main()
{
	scanf("%lld%lld",&n,&d);
	pw[0] = 1;
	for(ll i = 1;i <= 23001;i++)
	    pw[i] = pw[i - 1] * 2 % mod;
	for(ll i = 0;i <= n;i++)
	    C[i][0] = C[i][i] = 1;
	for(ll i = 2;i <= n;i++)
		for(ll j = 1;j < i;j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	dp[0][1][1] = 1;
	for(ll i = 1;i <= d;i++)
	    for(ll j = i;j <= n;j++)
	        for(ll k = 1;k <= j - i + 1;k++)
	            if(dp[i - 1][j][k])
	            {
	            	ll tmp = dp[i - 1][j][k];
	                for(ll w = 1;w <= n - j - max(d - i,0LL);w++)
	                {
	                	tmp = tmp * (pw[k] - 1 + mod) % mod;
						dp[i][j + w][w] = (dp[i][j + w][w] + tmp * pw[w * (w - 1) / 2] % mod * C[n - j - 1][w - (i == d)] % mod) % mod;
					}
				}
	ll ans = 0;
	for(ll i = d;i <= n;i++)
	    for(ll j = 1;j <= n;j++)
		    ans = (ans + dp[d][i][j] * pw[j * (n - i) + (n - i) * (n - i - 1) / 2] % mod) % mod;
	printf("%lld\n",ans);
    return 0;
}
```

---

