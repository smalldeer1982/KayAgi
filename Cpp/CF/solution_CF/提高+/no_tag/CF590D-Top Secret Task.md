# Top Secret Task

## 题目描述

A top-secret military base under the command of Colonel Zuev is expecting an inspection from the Ministry of Defence. According to the charter, each top-secret military base must include a top-secret troop that should... well, we cannot tell you exactly what it should do, it is a top secret troop at the end. The problem is that Zuev's base is missing this top-secret troop for some reasons.

The colonel decided to deal with the problem immediately and ordered to line up in a single line all $ n $ soldiers of the base entrusted to him. Zuev knows that the loquacity of the $ i $ -th soldier from the left is equal to $ q_{i} $ . Zuev wants to form the top-secret troop using $ k $ leftmost soldiers in the line, thus he wants their total loquacity to be as small as possible (as the troop should remain top-secret). To achieve this, he is going to choose a pair of consecutive soldiers and swap them. He intends to do so no more than $ s $ times. Note that any soldier can be a participant of such swaps for any number of times. The problem turned out to be unusual, and colonel Zuev asked you to help.

Determine, what is the minimum total loquacity of the first $ k $ soldiers in the line, that can be achieved by performing no more than $ s $ swaps of two consecutive soldiers.

## 说明/提示

In the first sample Colonel has to swap second and third soldiers, he doesn't really need the remaining swap. The resulting soldiers order is: ( $ 2 $ , $ 1 $ , $ 4 $ ). Minimum possible summary loquacity of the secret troop is $ 3 $ . In the second sample Colonel will perform swaps in the following order:

1. (10, 1, 6 — 2, 5)
2. (10, 1, 2, 6 — 5)

The resulting soldiers order is (10, 1, 2, 5, 6).

Minimum possible summary loquacity is equal to $ 18 $ .

## 样例 #1

### 输入

```
3 2 2
2 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 4 2
10 1 6 2 5
```

### 输出

```
18
```

## 样例 #3

### 输入

```
5 2 3
3 1 4 2 5
```

### 输出

```
3
```

# 题解

## 作者：Mistletoes (赞：5)

传送门：[Top Secret Task](https://www.luogu.org/problemnew/show/CF590D)

dp[i][j][k] 表示  考虑到第i个数  计算前j个数的和 进行了k次操作   

则有     

1. 若不把第i个数放入前j个数中  

         dp[i][j][k] = dp[i-1][j][k]          
1. 若把第i个数放入前j个数中

      	 至少需要把第i个移到第j个，即进行i-j次操作
         if(k >= i-j) 
        	dp[i][j][k] = dp[i-1][j-1][k-(i-j)]  
            
            
然而如果直接开数组，则要开dp[151][151][151*151]这么大  这显然是不可取的  

又因为 dp[i][ ][ ] 始终只和 dp[i-1][ ][ ] 有关，所以考虑滚动数组  

即用 dp[i%2][ ][ ] 表示 dp[i][ ][ ]  

话不多说，上代码：


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
int N,K,S;
ll dp[2][155][155*155];
ll a[155];
int main(){
	scanf("%d%d%d",&N,&K,&S);
	for(int i=1;i<=N;i++)
		scanf("%d",&a[i]);
	memset(dp,inf,sizeof(dp));
	dp[0][0][0]=0;
	for(int i=1;i<=N;i++){
		memset(dp[i%2][0],0,sizeof(dp[i%2][0]));
		for(int j=1;j<=i;j++){
			for(int k=0;k<=i*j;k++){
				dp[i%2][j][k]=dp[(i-1)%2][j][k];
				if(k>=i-j)
					dp[i%2][j][k]=min(dp[i%2][j][k],dp[(i-1)%2][j-1][k-(i-j)]+a[i]);
			}
		}
	}
	ll ans=inf;
	for(int k=0;k<=min(S,N*(N-1)/2);k++)
		ans=min(dp[N%2][K][k],ans);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：TernaryTree (赞：2)

感觉这个 dp 非常好想啊，完全没有我认知中的 *2300 dp 难度。

考虑我们最后挪过来的前 $k$ 个位置原来在的地方 $p_1< p_2< \cdots < p_k$，那么这些点显然让位置最小的移到第一个，第二小的移到第二个，以此类推，这样我们总需要交换的次数就是 $\sum p_i-i$。

然后我们设计一个 dp，令 $f_{i,j,z}$ 表示前 $i$ 个位置选了 $j$ 个，这 $j$ 个挪到前面需要 $z$ 次操作的最小总和。有

$$f_{i,j,z}=\min(f_{i-1,j,z},f_{i-1, j-1,z-i+j}+a_i)$$

但是 $z$ 是 $\Theta(s)$ 的，会达到 $10^9$。我们注意到当 $s$ 特别大的时候我们一定可以将前 $k$ 小的数挪到前面，具体是多大呢，考虑最小的几个值都在最后面的情况，这个时候你要全部挪到最前面操作次数是 $k(n-k)$，所以当 $s$ 大于这个数的时候我们直接排序将前 $k$ 项求和即可。

然后剩下的复杂度是 $\Theta(nk^2(n-k))$，当 $n=150$ 时这个看起来 $n^4$ 的东西最多只有 $7.5\times 10^7$，完全可以跑过。记得要滚动数组啊！

---

## 作者：qzmoot (赞：0)

# 题解：CF590D Top Secret Task
## 题目大意
有 $n$ 个数，有 $s$ 次操作，每次操作可以交换两个相邻的数，现在要求通过 $s$ 次操作，使前 $k$ 个数的和最小，输出这个最小的和。
## 分析
第一眼看到这个题目，我感觉可能是什么奇怪的贪心之类的，但是因为贪心不一定能保证最优。若你想吧一个最小的从后 $n-k$ 个数中移动到前面来的话，你可能还比不上移走在前 $k$ 个中一些最大的数。总的来说，我们还是考虑 dp。

看了看数据范围，$n\leq 150$ 这可能就是给 dp 暴力转移的，印证了我们之前的想法。而且这是 $n^3$ 转移可以通过的复杂度，且题目也在最前面给出了三个数，于是我们就可以考虑设置一个状态为如下的 dp：

$f_{i,j,k}$ 表示，目前考虑到第 $i$ 位，前 $j$ 个数的和，与操作了 $k$ 次。

考虑如何转移。

1. 我们不动第 $i$ 个，那么就是直接继承 $i-1$ 的状态。
2. 我们把 $i$ 移动进前 $j$ 个。于是我们算出移动的次数为 $i-j$ 次，说明上一次用了 $k-(i-j)$ 次。那么就可以很容易看出是从 $f_{i-1,j-1,k-(i-j)}+a_i$ 转移而来的。

### 第三维的大小问题
但是我们的 $s$ 是可以到达 $10^9$ 的大小的，如果不加思考就直接套式子的话我们的复杂度会直接炸掉。我们进行一下思考，如果 $s$ 很小的话，我们无需进行操作；若 $s$ 大于一定限制，我们就把他赋值成该限制的值，因为不能再大了。那么该限制是什么呢？

我们发现，如果 $s$ 十分充裕，我们是完全可以将前 $k$ 小个数全部移动到前面来的，我们假定 $k$ 和 $n$ 同阶，那么我们将限制定为 $n\times(n-1)/2$ 就很合理了这是假想每次 $k$ 都在最后面的情况。

### 空间复杂度更优
优化完我们的第三维后，我们的空间仍然会爆掉，为 $n^4$，不难发现每次的转移都只和上一次的有关，于是我们就进行滚动数组优化就行了。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=155;
int n,s,K;
int a[N];
int f[N][N*N],g[N][N*N];
int ans=1e18;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>K>>s;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	memset(f,0x3f,sizeof f);
	memset(g,0x3f,sizeof g);
	f[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		memset(g[0],0,sizeof g[0]);
		for(int j=1;j<=i;j++)
			for(int k=0;k<=i*j;k++)
			{
				g[j][k]=f[j][k];
				if(k>=i-j)
					g[j][k]=min(g[j][k],f[j-1][k-(i-j)]+a[i]);
			}
		for(int j=1;j<=i;j++)
			for(int k=0;k<=i*j;k++)
				f[j][k]=g[j][k];
	}
	int lim=min(s,n*(n-1)/2);
	for(int k=0;k<=lim;k++)
		ans=min(ans,f[K][k]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

数据范围极小，我们可以考虑非常非常暴力的做法。

我们每个状态需要记录三个量，目前在第 $i$ 个阶段，已经确定了前 $j$ 个数，已经使用了 $k$ 次操作。

即 $f(i,j,k)$ 表示前 $i$ 个数，使用 $k$ 次操作，前 $j$ 个数确定，的最大和。

+ 不移是一种：$f(i,j,k)=f(i-1,j,k)$。
+ 移动 $i$ 到 $j$ 的位置，因为 $j-1$ 是固定的，再移到前面没有意义。$f(i,j,k)=f(i-1,j-1,k-i+j)$，这里 $k>i-j$。

暴力转移即可。注意到 $s\le10^9$ 是假的，因为 $>n^2$ 次操作相当于直接排序了。

$n,k$ 同阶，复杂度 $O(n\times k\times n^2)=n^4$。数组开不下，可以把第一维滚掉。

```cpp 
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
using ll=long long;
static const int Buf_size=1<<25;
static char _c; static int _x;
static const signed int base_10=10, zero(48), nine(57), flag_signed(45);
static char buf[Buf_size], *p1=buf, *p2=buf;
#define digit() (zero<=_c&&_c<=nine)
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Buf_size,stdin),p1==p2)?EOF:*p1++)
inline int read(){_x=0;_c=getchar();while(!digit()){_c=getchar();}while(digit()){_x=_x*10+(_c^zero);_c=getchar();}return _x;}
const int N=200, inf=2e9;
const ll illf=1e18;
int a[N]; int f[2][N][N*N];
int qt, n, i, j, k, res, s, K;
int main()
{
	n=read(); K=read(); s=read(); rep(i, 1, n) a[i]=read();
	if(s>n*(n+1)/2)
	{
		sort(a+1, a+n+1);
		res=0; rep(i, 1, K) res+=a[i];
		printf("%d\n", res);
		return 0;
	}
	rep(i, 1, n) rep(j, 0, (n+1)*n/2) f[0][i][j]=f[1][i][j]=inf;
	f[0][0][0]=0; rep(i, 1, n) rep(j, 1, i)
	{
		int now=i&1, lst=(i-1)&1;
		rep(k, 0, n*(n+1)/2) f[now][j][k]=0;
		rep(k, 0, n*(n+1)/2) f[now][j][k]=min(f[lst][j][k], k>=i-j? f[lst][j-1][k-i+j]+a[i]: inf);
//		rep(k, 0, n*(n+1)/2) printf("f[%d][%d][%d]=%d\n", i, j, k, f[now][j][k]);
	}
	// puts("ok");
	res=inf;
	rep(i, 0, s) res=min(res, f[n&1][K][i]);
	printf("%d\n", res);
}
```

---

## 作者：翛醨 (赞：0)

 $n\leq150$ ,很明显这是一个 dp 的数据范围,显然咱们可以设状态 $dp[i][j][k]$ ,表示是否把 $i$ 点与 $j$ 点进行交换(可以交换,也可以不交换,只是要取其中最小的),一共所需的花费次数为 $k$ 时的最小前 $j$ 个数字的最小和
 
### 状态转移转移方程

如果 $i$ 与 $j$ 不进行交换,那么 $dp[i][j][k]=dp[i-1][j][k]$ 

如果交换,那么 $dp[i][j][k]=min(dp[i][j][k], dp[i-1][j-1][k-(i-j)]$ 
 
### 边界

首先,要保证 $i \leq j$ ,因为如果 $i>j$ ,就说明 $i$ 已经在 $j$ 的前面了,那么再把他们两交换就没有意义了,因为他们两都会对前 $j$ 个数造成贡献

然后,就是第三维的最大值,考虑极端的情况,就是我们把该序列直接用冒泡排序变成了一个有序的序列,那么肯定前 $k$ 个数字的和最小,而根据冒泡排序的排序方式我们可以知道,要将原序列排成一个有序序列所需的交换次数应该是原序列中的逆序对个数,也就是说,最多花费逆序对个数的次数,我们就能得到这一题的答案,而第三维的最大值也就是原序列逆序对个数.

这里插一句,求逆序对是可以用树状数组的,但是对于这道题来说,数据范围过小,没有必要.

### 优化
显然, $dp[150][150][150*150]$ 的 $int$ 数组会爆空间,注意到第一维转化时一直是从 $i-1$ 转化到 $i$ 的,那么我们就可以用滚动数组把这一维滚掉.

### 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define R register int 
#define min(a, b) a<b?a:b
using namespace std;
const int N=155;
LL a[N], dp[2][N][N*N];
int main (){
	LL n, k, s, rev=0, val=0;
	
	scanf ("%lld%lld%lld", &n, &k, &s);
	for (R i=1;i<=n;++i){
		scanf ("%lld", &a[i]);
		for (R j=1;j<i;++j)//求逆序对个数
			rev+=(a[j]>a[i])?1:0;
	}if(s>=rev){//特判,看是否能够直接将排序
		int ans=0;
		sort(a+1, a+1+n);
		for (R i=1;i<=k;++i) ans+=a[i];
		return printf("%d\n", ans)&0;
	}rev=s;
	memset(dp, 0x7f, sizeof(dp));
	dp[0][0][0]=0;//初始化
	for (R i=1;i<=n;++i){
		val^=1;
		memset(dp[val][0], 0, sizeof(dp[val][0]));//一定一定要清空
		for (R j=1;j<=i;++j){
			for (R p=0;p<=rev;++p){
				//状态转移
				dp[val][j][p]=dp[val^1][j][p];
				if(p>=i-j) dp[val][j][p]=min(dp[val][j][p], dp[val^1][j-1][p-(i-j)]+a[i]);
			}
		}
	}LL minn=1000000000;
	for(R i=0;i<=rev;++i) minn=min(minn, dp[val][k][i]);//统计答案
	printf("%lld\n", minn);
	
	return 0;
}
```


---

