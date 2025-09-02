# [ABC113D] Number of Amidakuji

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc113/tasks/abc113_d

あみだくじは, 日本に古くから伝わる伝統的なくじ引きである.

あみだくじを作るには, まず $ W $ 本の平行な縦線を引き, 次にそれらを繋ぐ横線を引いていく. それぞれの縦棒の長さは $ H+1 $ \[cm\] であり、横線の端点となれるのは上から $ 1,2,3,...,H $ \[cm\] の位置のみである.

ここで,「正しいあみだくじ」とは, 以下のような条件を満たすあみだくじのことである.

- どの $ 2 $ つの横棒も端点を共有しない.
- それぞれの横棒の $ 2 $ つの端点は同じ高さになければならない.
- 横棒は隣り合う縦線を繋がなければならない.

![ ](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc113_d/76ad4dbaf6281d141632ee1be437fcd6eb62cf06.png)

縦棒 $ 1 $ の上端から, 横線があれば必ずそれを通るというルールで下へたどったときに, 最終的にたどり着く縦棒の番号が $ K $ となるような「正しいあみだくじ」の本数を $ 1\ 000\ 000\ 007 $ で割った余りを求めなさい.

例として, 以下のあみだくじにおいて, 最終的にたどり着く縦棒の番号は $ 4 $ である.

![ ](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc113_d/798f2b4676c5cd94b2fff66ef18034da71e67ad6.png)

## 说明/提示

### 制約

- $ H $ は $ 1 $ 以上 $ 100 $ 以下の整数
- $ W $ は $ 1 $ 以上 $ 8 $ 以下の整数
- $ K $ は $ 1 $ 以上 $ W $ 以下の整数

### Sample Explanation 1

以下の $ 1 $ 個のあみだくじのみが条件を満たす. !\[ \](https://img.atcoder.jp/abc113/c68c6daccfc4cba8bc94af5f1a80ef2f.png)

### Sample Explanation 2

以下の $ 2 $ 個のあみだくじのみが条件を満たす. !\[ \](https://img.atcoder.jp/abc113/4be150946de8bef9b14d9bc17814d963.png)

### Sample Explanation 3

以下の $ 1 $ 個のあみだくじのみが条件を満たす. !\[ \](https://img.atcoder.jp/abc113/9b2e9f49832458c3488b1e04afd51ed4.png)

### Sample Explanation 4

以下の $ 5 $ 個のあみだくじのみが条件を満たす. !\[ \](https://img.atcoder.jp/abc113/bf6ec766f8923ac2f082f538a6c736b6.png)

### Sample Explanation 5

縦線が $ 1 $ 本しかないので, 横線をそもそも引くことができない. よって条件を満たすあみだくじは「一本も横線を引かない」の $ 1 $ 通りしかない.

### Sample Explanation 6

答えを $ 1\ 000\ 000\ 007 $ で割った余りを出力すること.

## 样例 #1

### 输入

```
1 3 2```

### 输出

```
1```

## 样例 #2

### 输入

```
1 3 1```

### 输出

```
2```

## 样例 #3

### 输入

```
2 3 3```

### 输出

```
1```

## 样例 #4

### 输入

```
2 3 1```

### 输出

```
5```

## 样例 #5

### 输入

```
7 1 1```

### 输出

```
1```

## 样例 #6

### 输入

```
15 8 5```

### 输出

```
437760187```

# 题解

## 作者：hyxgg (赞：5)

[题目](https://www.luogu.com.cn/problem/AT_abc113_d)

## 思路
考虑 dp。  
设状态 $dp_{k,i,j}$ 表示从第 $i$ 个竖线到第 $j$ 个竖线，中间长度为 $k$ 时的总方案数。

对于一个点，它可以从它上面、上面的左边一个、上面的右边一个下来。

则有

$$dp_{k,i,j}=dp_{k-1,i,j} \times dp_{1,j,j}+dp_{k-1,i,j-1} \times dp_{1,j-1,j}+dp_{k-1,i,j+1} \times dp_{1,j+1,j}$$

当然，得先把 $k=1$ 的值处理出来，这很简单，不再赘述。

答案则为 $dp_{H,1,K}$。

## 代码
没啥细节，就不写注释了，有问题评论区见。
```
#include<iostream>
#include<cstdio>
#define ll long long
#define mod 1000000007
using namespace std;
ll h,w,k,dp[105][15][15],f[15];
int main(){
    scanf("%lld%lld%lld",&h,&w,&k);
    f[1]=1;
    f[0]=1;
    for(ll i=2;i<=w;i++){
        f[i]=f[i-1]+f[i-2];
        f[i]%=mod;
    }
    for(ll i=1;i<=w;i++){
        dp[1][i][i]=f[i-1]*f[w-i]%mod;
        if(i>1)dp[1][i-1][i]=f[i-2]*f[w-i]%mod;
        if(i<w)dp[1][i+1][i]=f[i-1]*f[w-i-1]%mod;
    }
    for(ll i=2;i<=h;i++){
        for(ll j=1;j<=w;j++){
            for(ll kk=1;kk<=w;kk++){
                dp[i][j][kk]=dp[i-1][j][kk]*dp[1][kk][kk]%mod;
                dp[i][j][kk]+=dp[i-1][j][kk-1]*dp[1][kk-1][kk]%mod;
                dp[i][j][kk]%=mod;
                dp[i][j][kk]+=dp[i-1][j][kk+1]*dp[1][kk+1][kk]%mod;
                dp[i][j][kk]%=mod;
            }
        }
    }
    printf("%lld",dp[h][1][k]);
    return 0;
}
```

---

## 作者：fengenrong (赞：5)

### 题意

有 $m$ 条竖线，每条线上有 $n$ 个高度。从 $(1,1)$ 出发，每次遇到横线时都选择经过它，并且不存在两条端点重合的横线，一条横线的两端点必须在同一高度，一条横线连接的需要是相邻的两条竖线。求从 $(1,1)$ 到 $(h,k)$ 的图的方案数。

### 思路

考虑 $dp$，我们可以用 $dp_{i,j}$ 表示从 $(1,1)$ 到 $(i,j)$ 的方案数。

在此之前，我们需要先求一个东西，我们定义 $f_{i,0}$ 为放到第 $i$ 个位置不放边的方案数，定义 $f_{i,1}$ 为放到第 $i$ 个位置放边的方案数。不难想到：

$$f_{i,0} \gets f_{i-1,0}+f_{i-1,1}$$
$$f_{i,1} \gets f_{i-1,0}$$

不难看出，$(i,j)$ 可以由 $(i-1,j)$，$(i-1,j-1)$ 和 $(i-1,j+1)$ 到达，即一个点上面三个点。

首先，假如是要直接由上面的点移下来，就需要要求上面那个点左边和右边都没有边，所以可以推出：

$$dp_{i,j} \gets dp_{i-1,j} \times f_{j-1,0} \times f_{m-j,0}$$

接下来，如果是由左上的点推出，就需要要求上面那个点左边有边，而右边都没有边，所以可以推出：

$$dp_{i,j} \gets dp_{i-1,j-1} \times f_{j-1,1} \times f_{m-j,0}$$

从右上的点推出的也同理。

$$dp_{i,j} \gets dp_{i-1,j+1} \times f_{j-1,0} \times f_{m-j,1}$$

### Code
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int mod=1000000007;
int n,m,k;
int f[105][2],dp[105][105];
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		f[i][0]=(f[i-1][0]+f[i-1][1])%mod;
		f[i][1]=f[i-1][0];
	}
	dp[0][1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			dp[i][j]=(dp[i][j]+((dp[i-1][j]*((f[j-1][0]*f[m-j][0])%mod)%mod)%mod))%mod;
			dp[i][j]=(dp[i][j]+((dp[i-1][j-1]*((f[j-1][1]*f[m-j][0])%mod)%mod)%mod))%mod;
			dp[i][j]=(dp[i][j]+((dp[i-1][j+1]*((f[j-1][0]*f[m-j][1])%mod)%mod)%mod))%mod;
		}
	printf("%lld\n",dp[n][k]);
	return 0;
} 

```

---

## 作者：Mobius127 (赞：4)

[题传](https://www.luogu.com.cn/problem/AT4248)

发现 $W$ 很小，肯定要在上面做文章。

记 $dp_{i, S}$ 为到第 $i$ 行，状态集合为 $S$ 的方案数。

显然有：

$$dp_{i, S} = \sum_{T|T \text{合法}} dp_{i-1, T}$$

我们考虑怎样的一个状态是合法的：


显然对于 $T$ 与 $S$，它们都需要满足二进制下没有两位相邻的 1，考虑多进行一次 DP，记 $no_S$ 为状态 $S$ 是否 **不**合法，$no_S$ 为真的的时候会怎样呢？显然有两种可能：要么 $S$ 丢掉最后一位不合法（即 $no_{\frac{S}{2}}$ 为真），要么 $S$ 与 $S$ 右移一位的与值不为零（实际上两种情况珂以都合并成第二种）。 

这样做是 $O(H \times 2^{2W})$ 的，珂以通过此题。。。吗？

这绕了个大弯：我们并不能确定对于某个状态 $dp_{W, S}$，最后是否正好在 $k-1$ （因为二进制多压了一位）位置！！1

~~所以说写方程的时候一定要想好最后要求什么 a。~~

重新定义 $dp_{i, j}$ 为到第 $i$ 行第 $j$ 个位置的方案数。

对于位置 $(i, j)$ ，能转移到此位置的无非就 $(i-1, j-1), (i-1, j+1), (i-1, j)$ 三处，但是转移不止一次，所以我们枚举上次转移的状态 $S$：

1. 若 $S$ 在 $j-1$ 处为 1，则 $(i-1, j-1)$ 珂以转移；

1. 若$S$ 在 $j$ 处为 1，则 $(i-1, j+1)$ 珂以转移；

1. $S$ 在 $j, j-1$ 处均**不为** 1（有桥的话按照规则就必须走），则 $(i-1, j)$ 珂以转移。

复杂度 $O(HW \times 2^W)$，珂以通过；

### Code：

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
const int mo=1e9+7;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
inline int ksm(int a, int b){
	int ret=1;
	for(; b; b>>=1, a=1ll*a*a%mo)
		if(b&1) ret=1ll*ret*a%mo;
	return ret;
}
namespace Solution{
	int f[101][8], h, w, k, R;
	bool no[1<<18];int mx[1<<18];
    //数组开大了无伤大雅O(∩_∩)O
	signed work(){
		h=read(), w=read()-1, k=read(), R=1<<w;
		f[0][0]=1;
		for(int i=1; i<R; i++)
			mx[i]=mx[i>>1]+1;//乱写的，脑子进水了 OvO
		mx[0]=-1;
		for(int i=1; i<R; i++)
			no[i]=no[i>>1]||(i&(i>>1));
		for(int i=1; i<=h; i++)
			for(int S=0; S<R; S++)
				if(!no[S])
					for(int j=0; j<=w; j++){
						if(j&&(S&(1<<j-1)))
							f[i][j]=(f[i][j]+f[i-1][j-1])%mo;
						else if(j<w&&S&(1<<j))
							f[i][j]=(f[i][j]+f[i-1][j+1])%mo;
						else
							f[i][j]=(f[i][j]+f[i-1][j])%mo;
					}
		printf("%d ", f[h][k-1]);
		return 0;
	}
}
signed main(){
	Solution :: work();
	return 0;
}


```


---

## 作者：Nightingale_OI (赞：1)

### 大意

有 $ w $ 条竖线，每条线上有 $ h $ 个高度。

可以用横线进行任意次链接，具体为链接相邻竖线同一高度的位置，但是不可以一个位置被链接两次，即横线无交点。

有一个人沿着竖线从上往下走，当遇到横线就沿着横线走到链接的竖线上。

问有多少链接方案使得这个人从 $ 1 $ 号竖线开始最终走到 $ k $ 号竖线的方案数。

### 思路

考虑设 $ dp_{i,j} $ 为在 $ i $ 高度时在第 $ j $ 号竖线的方案数，枚举 $ i - 1 $ 高度时在哪里即可。

时间复杂度 $ O(nm) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
const int mo=1e9+7;
int f[10]={1,1,2,3,5,8,13,21,34,55};
int dp[101][10];
int main(){
    cin>>n>>m>>s;
    dp[0][1]=1;
    f(i,1,n)f(j,1,m){
        dp[i][j]=(dp[i][j]+1ll*f[j-1]*f[m-j]%mo*dp[i-1][j]%mo)%mo;
        if(j>1)dp[i][j]=(dp[i][j]+1ll*f[j-2]*f[m-j]%mo*dp[i-1][j-1]%mo)%mo;
        if(j<m)dp[i][j]=(dp[i][j]+1ll*f[j-1]*f[m-j-1]%mo*dp[i-1][j+1]%mo)%mo;
    }
    printf("%d\n",dp[n][s]);
    return 0;
}
```

---

