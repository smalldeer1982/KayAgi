# Game of Sum

## 题目描述

有一个长度为 $n$ 的整数序列，两个游戏者 $A$ 和 $B$ 轮流取数，$A$ 先取。每次玩家只能从左端或者右端取任意数量的数，但不能两边都取。所有数都被取走视为游戏结束，然后统计每个人取走的数之和，作为各自的得分。两个人采取的策略都是让自己得分尽可能高，并且两个人都很机智，求 $A$ 得分 - $B$ 得分后的结果。

## 样例 #1

### 输入

```
4
4 -10 -20 7
4
1 2 3 4
0```

### 输出

```
7
10```

# 题解

## 作者：云浅知处 (赞：4)

我们考虑 dp。

定义 $F(l,r)$ 为：剩下的区间为 $[l,r]$ 时先手可以获得的最大得分。

初始状态显然 $F(i,i)=A_i$，而答案就是 $F(1,n)-(\sum_{i=1}^nA_i-F(1,n))=2F(1,n)-\sum_{i=1}^nA_i$

先只考虑从左边选的情况。

设先手选到的位置为 $k$，那么选完之后就还剩下 $[k+1,r]$ 这个区间。

由于两者都采用最优策略，所以后手一定会选择出 $F(k+1,r)$ 这么多分。

而这段区间的总分一共只有 $\sum_{i=k+1}^rA_i$ ，其中 $A$ 是原序列。

因此，这段区间中剩给先手的分数是 $\sum_{i=k+1}^rA_i-F(k+1,r)$。

于是，我们有：
$$
F(l,r)=\sum_{i=l}^kA_i+\sum_{i=k+1}^rA_i-F(k+1,r)=\sum_{i=l}^rA_i-F(k+1,r)
$$
直接转移是 $O(n^3)$ 的，稳 TLE

不过这个转移是可以优化的：前一部分直接前缀和，后面一部分只需要对每个 $r$ 维护一下 $F$ 的后缀最小值就行了。

代码实现的时候，由于要考虑右边，所以我们还需要对每个 $l$ 维护一下前缀最小值。并且，由于可以一个数都不取，所以我们需要将前/后缀最小值对 $0$ 取 $\text{min}$。

这样就做到了 $O(n^2)$。

上代码=w=

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>

#define int long long
const int MN=1005; 

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

int T,n;
int a[MN],f[MN][MN],sum[MN],sufmin[MN],premin[MN];

signed main(void){

	n=114514;
	while(n!=0){
		memset(f,0,sizeof(f));
		memset(a,0,sizeof(a));
		memset(sum,0,sizeof(sum));
		memset(sufmin,0,sizeof(sufmin));
		memset(premin,0,sizeof(premin));
		
		n=read();
        if(n==0)exit(0);
		for(int i=1;i<=n;i++)a[i]=read(),f[i][i]=a[i],premin[i]=sufmin[i]=min(f[i][i],0ll),sum[i]=sum[i-1]+a[i];
		
		for(int len=2;len<=n;len++){
			for(int l=1,r=len;r<=n;l++,r++){
				f[l][r]=max(sum[r]-sum[l-1]-sufmin[r],sum[r]-sum[l-1]-premin[l]);
				sufmin[r]=min(sufmin[r],f[l][r]);
				premin[l]=min(premin[l],f[l][r]);
			}
		}
		
		cout<<2*f[1][n]-sum[n]<<'\n';
	}

    return 0;
}
```

---

## 作者：斗神_君莫笑 (赞：4)

本题是明显的区间dp  
主要是体会问题迭代的思想  
按照一般的写法，n^3的循环不错  
但其实记忆化搜索也是可以的  

定义f[i][j]为i到j的先手最大  
这里引入一个绝妙的迭代思想：  
我们先从一边取掉任意个，那么问题就像踢皮球一样踢给了对面   
而对面在此情况下一定取最优  
那么f[i][j]由f[i~j-1][j]和f[i][i+1~j]转移而来   

取一下min，当对手获取最少时就是我们获取最多   
注意代码中的m初值是0，代表如果对手取的始终是正数我们就把区间取完  
（不能坑别人就全自己吃掉）   
还要注意循环的顺序，由小到大，才能正常的更新状态  
```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[110][110],f[110][110],a[110],s[110];
int dfs(int i,int j){
	if(vis[i][j])return f[i][j];
	vis[i][j]=1;
	int m=0;
	for(int k=i;k<j;++k)
		m=min(m,dfs(i,k));
	for(int k=i+1;k<=j;++k)
		m=min(m,dfs(k,j));
	f[i][j]=s[j]-s[i-1]-m;
	return f[i][j];
}
inline void clear(){
	memset(a,0,sizeof(a));
	memset(s,0,sizeof(s));
	memset(f,0,sizeof(f));
	memset(vis,0,sizeof(vis));
}
int main(){
	int n;
	while(1){
		scanf("%d",&n);
		if(n==0)break;
		clear();
		for(int i=1;i<=n;++i)scanf("%d",&a[i]);
		for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i];
		int k=dfs(1,n);
		printf("%d\n",k-(s[n]-k));
	}
	return 0;
} 
```


---

## 作者：_WMD (赞：2)

看这道题还没有题解，本蒟蒻就来一发吧。
这是一道比较简单的DP，d[i][j]代表序列i~j先手取的最大值。f和g数组是一个优化。
下面上代码。
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int t,n,d[1010][1010],a[1010],f[1010][1010],g[1010][1010];
inline int min(int a,int b)
{
	if(a<b)return a;return b;
}
void dp()
{
	for(int i=1;i<=n;i++)d[i][i]=f[i][i]=g[i][i]=a[i]-a[i-1];
	for(int l=1;l<n;l++)
	{
		for(int i=1;i+l<=n;i++)
		{
			int j=i+l,m=0;
			m=min(m,f[i+1][j]);m=min(m,g[i][j-1]);
			d[i][j]=a[j]-a[i-1]-m;
			f[i][j]=min(d[i][j],f[i+1][j]);g[i][j]=min(g[i][j-1],d[i][j]);
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	//scanf("%d",&t);
	while(1)
	{
		scanf("%d",&n);
		if(n==0)break;a[0]=0;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]+=a[i-1];
		dp();
		printf("%d\n",d[1][n]*2-a[n]);
	}
	return 0;
} 
```

---

## 作者：翼德天尊 (赞：1)

很容易可以看出这是一道区间 DP 的题目。

考虑设 $dp_{i,j}$ 为序列剩余 $i$ 到 $j$ 时先手的最优解，则显然可以得到 $dp_{i,j}$ 的状态转移方程为：

$$dp_{i,j}=sum(i,j)-\min(dp_{i,j-1},dp_{i,j-2},\dots,dp_{i,i},dp_{i+1,j},dp_{i+2,j},\dots,dp_{j,j})$$

然后很容易想到用前缀和+差分的方式预处理出 $sum(i,j)$，然后先枚举区间长度，再枚举左端点右端点，最后枚举所有区间内 $dp$ 数组的最小值。

复杂度 $O(n^3)$，虽然可以过，但显然不够优。

考虑区间内 $dp$ 数组的最小值完全可以通过递推 $O(1)$ 得到。设 $z_{i,j}=\min(dp_{i,j},dp_{i,j-1},dp_{i,j-2},\dots,dp_{i,i})$，$y_{i,j}=\min(dp_{i,j},dp_{i+1,j},dp_{i+2,j},dp_{j,j})$。

则每次处理完 $dp_{i,j}$ 时，我们都可以顺便维护 $z_{i,j}$ 和 $y_{i,j}$。

则新的状态转移方程式为

$$dp_{i,j}=sum_j-sum_{i-1}-\min(0,z_{i,j-1},y_{i+1,j})$$

其中可以取 $0$ 是因为可以将这段数全部取走。

复杂度 $O(n^2)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 105
int n,a,z[N][N],y[N][N],dp[N][N],sum[N];
int read(){
	int w=0,f=1;
	char ch=getchar();
	while (ch>'9'||ch<'0') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
} 
int main(){
	while (1){
		if ((n=read())==0) break;
		for (int i=1;i<=n;i++) dp[i][i]=z[i][i]=y[i][i]=a=read(),sum[i]=sum[i-1]+a;
		for (int i=2;i<=n;i++){
			for (int l=1;l<=n-i+1;l++){
				int r=l+i-1;
				int x=min(0,min(z[l][r-1],y[l+1][r]));
				dp[l][r]=sum[r]-sum[l-1]-x;
				z[l][r]=min(z[l][r-1],dp[l][r]);
				y[l][r]=min(y[l+1][r],dp[l][r]);
			}
		}
		printf("%d\n",2*dp[1][n]-sum[n]);
	}
	return 0;
}
```


---

## 作者：MyukiyoMekya (赞：1)

区间dp，$f_{l,r}$ 表示 $[l,r]$ 区间先手能取到的最大值

显而易见先手取完以后后手只能取 $[l,r-1],[l,r-2] , \cdots ,[l+1,r],[l+2,r],\cdots$

$a_i$ 是给的整数序列，所以就有
$$
f_{l,r}=\sum_{i=l}^r a_i-\min\{0,f_{l,r-1},f_{l,r-2},\cdots ,f_{l+1,r},f_{l+2,r},\cdots\}
$$
显然我们可以搞一个 $L_{i,j}=\min\{f_{i,j},f_{i+1,j},\cdots ,f_{j,j}\}$，$R_{i,j}=\min\{f_{i,j},f_{i,j-1},\cdots,f_{i,i}\}$ 

然后弄个前缀和 $s_i=\sum_{j=1}^i a_j$

那么就变成了 $f_{l,r}=s_r-s_{l-1}-\min\{0,L_{l+1,r},R_{l,r-1}\}$

LR也很好维护，$L_{l,r}=\min\{L_{l+1,r},f_{l,r}\}$ , $R_{l,r}=\min\{R_{l,r-1},f_{l,r}\}$

答案就是 $f_{1,n}-(s_n-f_{1,n})$

时间复杂度 $\mathcal O(n^2)$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
int n;
int a[MaxN],s[MaxN];
int f[MaxN][MaxN],L[MaxN][MaxN],R[MaxN][MaxN];
// L[i][j] = min(f[i][j],f[i+1][j],...,f[j][j])
// R[i][j] = min(f[i][j],f[i][j-1],...,f[i][i])
inline void work()
{
	mem(f,0xc0);
	for(int i=1;i<=n;++i)
		read(a[i]),f[i][i]=L[i][i]=R[i][i]=a[i],s[i]=s[i-1]+a[i];
	for(int len=2;len<=n;++len)
		for(int i=1;i<=n-len+1;++i)
		{
			reg int j=i+len-1;
			checkmax(f[i][j],s[j]-s[i-1]-min(0ll,min(L[i+1][j],R[i][j-1])));
			L[i][j]=min(L[i+1][j],f[i][j]);
			R[i][j]=min(R[i][j-1],f[i][j]);
		}
	write(f[1][n]-(s[n]-f[1][n])),ln;
	return;
}
signed main(void)
{
	while(scanf("%lld",&n)==1&&n)
		work();
	return 0;
}
```

---

## 作者：弹星者 (赞：1)

显然本题是一道动规(~~因为窝想不出怎么贪心~~)   
定义f[i][j]表示第i到j张牌，先手能取得的最大分数
于是推出f[i][j]为i到j张牌之和减去后手能取得的分数最大值（因为两个人都很机智）  
即f[i][j]=sum[j]-sum[i-1]-min( f[i+1][j], f[i+2][j] ...f[j][j] , f[i][j-1] , f[i][j-2] ... f[i][j] )      
附上本蒟蒻的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[110],sum[110],f[110][110],vis[110][110];
int dp(int i,int j){
    if(vis[i][j]) return f[i][j];
    vis[i][j]=1;
    int m=0;
    for(int k=i;k<j;k++) 
		m=min(m,dp(i,k));
	for(int k=i+1;k<=j;k++) 
		m=min(m,dp(k,j));
    f[i][j]=sum[j]-sum[i-1]-m;
    return f[i][j];
}
int main(){
    while(scanf("%d",&n)){
    	if(n==0) break;
        for(int i=1;i<=n;i++){
        	scanf("%d",&a[i]);
			sum[i]=sum[i-1]+a[i];
		}
        memset(vis,0,sizeof(vis));
        printf("%d\n",2*dp(1,n)-sum[n]);
    }
	return 0;
}
```


---

## 作者：AllanPan (赞：1)

## 一、题意概要
>有一个长度为 $n$ 的整数序列，两个游戏者 $A$ 和 $B$ 轮流取数，且均采用**贪心算法**，求最终双方取出的数的总和之差。

## 二、算法及分析

事实上，通过题目中的描述，我们很容易就能看出，在**贪心算法**这一制约条件下，这题的结果就变成了唯一的（注意：贪心算法 $\neq$ 最小差距！），因此可以看作是一道“模拟”题。

在做法上，注意到双方都用**贪心算法**，因此代码实现可以用动态规划实现：开一个动态规划二维数组 $dp[105][105]$，其中 $dp[i][j]$ 表示其中一段 $[i, j]$ 区间的取法。那么不难发现，我们只要枚举每一种情况，再求出最值：

$$dp[i][j] = \sum_{k=i}^ja[k] - \min\{d[i+1][j], d[i+2][j], \ldots,d[j][j], d[i][j-1], d[i][j-2], \ldots ,d[i][i], 0\}.$$

## 三、代码
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
#include <cstring>
#include <istream>
#include <complex>

using namespace std;

int dp[105][105]; // 动规数组
int a[105]; // 数组
int s[105]; // 前几个数之和
bool hasBeenVisited[105][105] = { false }; // 是否已经算过，节省时间复杂度

int ddpp(int i, int j)
{
	if (hasBeenVisited[i][j])
		return dp[i][j];
	else
	{
		hasBeenVisited[i][j] = true;
		int ans = 0;
		for (int k = i + 1; k <= j; k++)
			ans = min(ans, ddpp(k, j));
		for (int k = i; k < j; k++)
			ans = min(ans, ddpp(i, k));
		dp[i][j] = s[j] - s[i - 1] - ans;
		return dp[i][j];
	}
} // 动规

int main()
{
	int n;
	while (scanf("%d", &n) && n)
	{
		s[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
			s[i] = s[i - 1] + a[i];
		}
		memset(hasBeenVisited, 0, sizeof(hasBeenVisited));
		cout << (2 * ddpp(1, n) - s[n]) << endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 广告
个人博客[食用更佳]( http://www.cinema000.xyz/1278.ruby)
## 分析
本题的数学模型就是：把$n$个集合$P_1,P_2,...,P_n$分成尽量多组，使得每组中所有集合的并集等于全集，这里的集合$P_i$就是计算机$i$及其相邻计算机的集合，每组对应题目中的一项服务，因为$n$比较小，所以可以用二进制表示，用$cover[S]$表示若干个$P_i$的集合$S$中所有$P_i$的并集即这些$P_i$在数值上的“按位与”。
然后用$f(S)$表示子集$S$最多可以分成多少组，则有
$$f(S)=\max (f(S-S_0)|S_0\subset S,cover[S_0]=U)+1$$
## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
const int MAXN = 100 + 6;
int S[MAXN],A[MAXN],d[MAXN][MAXN];
bool hash[MAXN][MAXN];

int dp(int i,int j){
	if(hash[i][j]) return d[i][j];
	hash[i][j] = true;
	int m = 0;
	for(int k = i + 1;k <= j;k++) m = min(m,dp(k,j));
	for(int k = i;k < j;k++) m = min(m,dp(i,k));
	d[i][j] = S[j] - S[i - 1] - m;
	return d[i][j];
}

int main(){
	int n;
	while(scanf("%d",&n) == 1 && n){
		S[0] = 0;
		for(int i = 1;i <= n;i++) scanf("%d",&A[i]),S[i] = S[i - 1] + A[i];
		memset(hash,0,sizeof(hash));
		printf("%d\n",2 * dp(1,n) - S[n]);
	}
	
	return 0;
}
```

---

