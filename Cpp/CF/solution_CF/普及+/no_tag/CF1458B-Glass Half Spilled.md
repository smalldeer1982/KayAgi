# Glass Half Spilled

## 题目描述

There are $ n $ glasses on the table numbered $ 1, \ldots, n $ . The glass $ i $ can hold up to $ a_i $ units of water, and currently contains $ b_i $ units of water.

You would like to choose $ k $ glasses and collect as much water in them as possible. To that effect you can pour water from one glass to another as many times as you like. However, because of the glasses' awkward shape (and totally unrelated to your natural clumsiness), each time you try to transfer any amount of water, half of the amount is spilled on the floor.

Formally, suppose a glass $ i $ currently contains $ c_i $ units of water, and a glass $ j $ contains $ c_j $ units of water. Suppose you try to transfer $ x $ units from glass $ i $ to glass $ j $ (naturally, $ x $ can not exceed $ c_i $ ). Then, $ x / 2 $ units is spilled on the floor. After the transfer is done, the glass $ i $ will contain $ c_i - x $ units, and the glass $ j $ will contain $ \min(a_j, c_j + x / 2) $ units (excess water that doesn't fit in the glass is also spilled).

Each time you transfer water, you can arbitrarlly choose from which glass $ i $ to which glass $ j $ to pour, and also the amount $ x $ transferred can be any positive real number.

For each $ k = 1, \ldots, n $ , determine the largest possible total amount of water that can be collected in arbitrarily chosen $ k $ glasses after transferring water between glasses zero or more times.

## 说明/提示

In the sample case, you can act as follows:


2. for $ k = 1 $ , transfer water from the first two glasses to the third one, spilling $ (5 + 5) / 2 = 5 $ units and securing $ 2 + (5 + 5) / 2 = 7 $ units;
3. for $ k = 2 $ , transfer water from the third glass to any of the first two, spilling $ 2 / 2 = 1 $ unit and securing $ 5 + 5 + 2 / 2 = 11 $ units;
4. for $ k = 3 $ , do nothing. All $ 5 + 5 + 2 = 12 $ units are secured.

## 样例 #1

### 输入

```
3
6 5
6 5
10 2```

### 输出

```
7.0000000000 11.0000000000 12.0000000000```

# 题解

## 作者：dead_X (赞：5)

## 思路
虽然这玩意看起来很像网络流，但是看到这个很小的**值域**，我们尝试 dp。

如果**选定最终产生贡献**的盆子之后，我们显然会把别的盆子的水都尝试往选中的盆子倒，直到填满或者没水了为止。或者说，假设我们选的盆子的已有水量是 $x$，剩余的可用空间为 $y$，还剩下 $z$ 升水，最终的答案就是 $x+\min(y,\frac{z}{2})$。这里的 $z$ 即总水量减去 $x$，可以消去。

注意到 $x$ 和 $y$ 的值域都很小，我们考虑使用背包来求解。接下来我们稍微找一找单调性，发现 $y$ 一定的时候，$x$ 越大显然是越优秀的，再加上题目中选的盆子数量是 $k$ 这一状态即可 dp。

想到这一步就不难列出 dp 柿子了。假设我们选了 $i$ 个盆子，这些盆子的 $a$ 之和为 $j$，$b$ 之和最大值即为 $dp_{i,j}$。而对于一个新的盆子，不难发现 $dp_{i,j}=\max\{dp_{i,j},dp_{i-1,j-(a-b)}+b\}$。

时间复杂度 $O(n^3\times a_i)$，常数大概 $\frac{1}{4}$ 的样子（循环可以只跑能到达的部分）。
## 代码
```
#include<bits/stdc++.h>
#define mp make_pair
#define pi pair<int,int>
#define pb push_back
//#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[103],b[103],tot,dp[103][10003];//空间，空余量 
double ans[103];
signed main()
{
	int n=read();
	for(int i=1; i<=n; i++) b[i]=read(),a[i]=read(),tot+=a[i];
	memset(dp,0xc0,sizeof(dp));
	for(int i=0; i<=n; i++) dp[i][0]=0;
	for(int i=1; i<=n; i++) for(int j=i; j>=1; j--) for(int k=100*j; k>=b[i]-a[i]; k--)
	dp[j][k]=max(dp[j][k],dp[j-1][k-b[i]+a[i]]+a[i]);
	for(int i=1; i<=n; i++) for(int j=0; j<=100*i; j++) ans[i]=max(ans[i],min((tot-dp[i][j])/2.0,(double)j)+dp[i][j]);
	for(int i=1; i<=n; i++) printf("%.10lf ",ans[i]);
	return 0;
}
 
```

---

## 作者：Timmylyx (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1458B)

一道 $01$ 背包的~~水~~题。
# 思路
   第 $i$ 瓶水如果被取，它可以贡献 $b_{i}$ 单位水，但如果它没被取，它只能贡献 $\frac{b_{i}}{2}$ 单位水，还要考虑最大容量，我们可以设一个二维 $dp$，求最大。
 ```cpp
 double dp[110][10010]; //dp[i][j] 表示选 i 个数，最大容量为 j 所选的水量的最大值
```
可得以下转移方程
 ```cpp
 dp[i][j]=max(dp[i][j],min(double(j),dp[i-1][j-c[x]]+v[x]));//x 为当前算到的数据的下标（阶段）
 ```
 最后的第 $i$ 个答案是所有的 $ \mathit{dp}_{i,j}$ 在不溢出的情况下加入剩余的水 $sum-\mathit{dp}_{i,j}$ 的一半中最大的一个，求答案代码见下（求第 $i$ 个答案）：
 ```cpp
 double ans=0;
for (int j=0; j<=10000; j++){
	ans=max(ans,dp[i][j]+min(double(i-dp[i][j]),(sum-dp[i][j])/2));
}
printf("%.1f000000000 ",ans);
 ```
 # 代码
 ```cpp
 #include <bits/stdc++.h>
using namespace std;
double dp[110][10010]; 
int c[110],v[110];
int main(){
	int n;
	double sum=0;
	scanf("%d",&n);
	for (int i=1; i<=n; i++){
		scanf("%d%d",&c[i],&v[i]);
		sum+=v[i];
	}
	for (int i=0; i<=n; i++){
		for (int j=1; j<=10000; j++){
			dp[i][j]=-1000000000.000000000;//求最大，设成无穷小
		}
	}
	for (int i=1; i<=n; i++){
		for (int j=i; j>=1; j--){
			
			for (int k=10000; k>=c[i]; k--){
				dp[j][k]=max(dp[j][k],min(double(k),dp[j-1][k-c[i]]+v[i]));
			}
		}
	}
	for (int j=1; j<=n; j++){
		
		double ans=0;
		for (int i=0; i<=10000; i++){
			ans=max(ans,dp[j][i]+min(double(i-dp[j][i]),(sum-dp[j][i])/2));
		}
		printf("%.1f000000000 ",ans);//最多一位小数，偷懒一下
	}

	return 0;
} 
 ```
 [提交结果](https://www.luogu.com.cn/record/110745460)
 
 这是~~本蒟蒻~~写的第一篇题解，有错误请多多谅解。

---

## 作者：tzc_wk (赞：3)

首先要明确的一点是，我们不会出现回倒的情况，就是从杯子 $x$ 倒到一个杯子 $y$，再倒到一个杯子 $z$，因为这样还不如 $x$ 直接倒到 $z$，$y$ 直接倒到 $z$。

于是本题变为选择 $k$ 个杯子 $i_1,i_2,\dots,i_k$，将所有其它杯子里的水倒到这 $k$ 个杯子里，这样总共能容纳 $\min(a_{i_1}+a_{i_2}+\dots+a_{i_k},b_{i_1}+b_{i_2}+\dots+b_{i_k}+\sum\limits_{i \text{没被选择}}\frac{b_i}{2})$ 的水。

然后就可以 $dp$ 了，$dp_{i,j,k}$ 表示在前 $i$ 个杯子里选择了 $j$ 个杯子，这 $j$ 个杯子的 $a_i$ 的和为 $k$，最多能容纳多少水。时空复杂度均 $n^4$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
template<typename T>
void read(T &x){
	char c=getchar();T neg=1;
	while(!isdigit(c)){
		if(c=='-') neg=-1;
		c=getchar();
	}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=100;
int n,a[MAXN+5],b[MAXN+5],dp[MAXN+5][MAXN+5][MAXN*MAXN+5];
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);memset(dp,128,sizeof(dp));
	dp[0][0][0]=0;
	for(int i=0;i<n;i++) for(int j=0;j<=i;j++) for(int k=0;k<=10000;k++){
		if(k+a[i]<=10000) chkmax(dp[i+1][j+1][k+a[i+1]],dp[i][j][k]+b[i+1]*2);
		chkmax(dp[i+1][j][k],dp[i][j][k]+b[i+1]);
	}
	for(int i=1;i<=n;i++){
		double ans=0;
		for(int k=0;k<=10000;k++){
			ans=max(ans,min(1.0*k,dp[n][i][k]/2.0));
		}
		printf("%.10lf ",ans);
	}
	return 0;
}
```

---

## 作者：Warriors_Cat (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/CF1458B)。

> 题意：有 $n$ 杯水，现有 $a_i$ 单位水，容积为 $b_i$ 单位水。将现有 $c_i$ 单位水中 $x(x \le c_i)$ 单位水倒入现有 $c_j$ 单位水后，$c_i$ 会变成 $c_i - x$，$c_j$ 会变成 $\min\{b_j, c_j + \frac{x}{2}\}$。对于每个 $k \in [1, n]$，问经过若干次操作后取 $k$ 个杯子最多能有多少水。

---

### $Solution:$

现场被区分了，没想出来，赛后发现没有多难。

有一个很重要的性质：对于三个杯子 $x, y, z$，将 $x$ 倒进 $y$、再将 $y$ 倒进 $z$ 还不如将 $x$ 倒进 $z$、再将 $y$ 倒进 $z$。

因此问题就转化为：选取 $k$ 个杯子，将其他杯子里的水倒入这 $k$ 个杯子，最后最多能倒多少。

这样就只是一个背包问题了。定义 $f_{i, j, k}$ 表示前 $i$ 个杯子中选 $j$ 个，此时 $b_i$ 和为 $k$ 时 $a_i$ 和的最大值。至于状态转移，从 $f_{i - 1, j - 1, k - b_i} + a_i$ 即可。

over，时间复杂度为 $O(n^3V)$，其中 $V$ 为值域。

---

### $Code:$

非赛时代码，码风可能有些不一样。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = y; i >= x; --i)
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 100;
int n, a[N + 5], b[N + 5], sum, f[N + 5][N + 5][N * N + 5]; double ans[N];
inline void work(){
	n = read(); rep(i, 1, n) b[i] = read(), sum += (a[i] = read());
	memset(f, -0x3f, sizeof(f)); rep(i, 0, n) f[i][0][0] = 0;
	rep(i, 1, n) rep(j, 1, i) rep(k, 0, N * N){
		f[i][j][k] = f[i - 1][j][k];
		if(k >= b[i]) f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - b[i]] + a[i]);
	}
	rep(i, 1, n) rep(j, 0, N * N) ans[i] = max(ans[i], min(1.0 * j, 1.0 * (sum + f[n][i][j]) / 2));
	rep(i, 1, n) printf("%0.11lf ", ans[i]);
}
int main(){ int t = 1; while(t--) work(); return 0; }
```


---

## 作者：Imitators (赞：1)

考虑，每一次倒的时候会有一半的损失，所以只可能一次性从 $i$ 倒入 $j$。

那么可以枚举子集 $S$，表示这些杯子的水要被倒入别的杯子里。

于是答案变为 $\min({\sum_{x\not \in S}b_x},suma-\frac{\sum_{x\in S}a_x}{2})$。

也就是 $\min(sumb-{\sum_{x \in S}b_x},suma-\sum_{x\in S}\frac{a_x}{2})$。

由于 $\sum a$ 不是很大，考虑$dp$。

---

$dp[i][j][k]$ 表示前 $i$ 个数，选了 $j$ 个，当前 $a$ 之和为 $k$ 的最小 $b$ 之和。

类似背包，有 :

$$dp[i][j][k]=\min(dp[i-1][j][k],dp[i-1][j-1][k-a_i]+b_i)$$

要求选 $j$ 个时，枚举$k$ ,此时答案为$\min(sumb-dp[n][n-i][k],suma-\frac{k}{2})$。

空间太大，那就滚动数组。

时间复杂度$O(n^2\times \sum a)$,极限$O(n^4)$

$\mathcal{code}$
``` cpp
#include<bits/stdc++.h>
using namespace std; 
int dp[2][110][10001];
int n;
int a[1000],b[1000];
bool opt=0;
int main()
{
	memset(dp,63,sizeof(dp));
	cin>>n;
	int SUM=0,sum=0,all=0;
	for(int i=1;i<=n;i++) cin>>b[i]>>a[i],SUM+=b[i],all+=a[i];
	dp[0][0][0]=0;
	for(int i=1;i<=n;i++)
	{
		sum+=a[i];
		opt^=1;
		for(int j=0;j<=n;j++)
		{
			for(int k=0;k<a[i];k++)
				dp[opt][j][k]=dp[opt^1][j][k];
			if(j==0)
			{
				for(int k=a[i];k<=sum;k++)
					dp[opt][j][k]=dp[opt^1][j][k];
			}
			else
			{
				for(int k=a[i];k<=sum;k++)
					dp[opt][j][k]=min(dp[opt^1][j][k],dp[opt^1][j-1][k-a[i]]+b[i]);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		double ans=0;
		for(int j=0;j<=sum;j++)
		{
			ans=max(ans,min(1.0*SUM-1.0*dp[opt][n-i][j],1.0*all-1.0*j/2.0));
		}
		printf("%.3lf ",ans);
	}
}
```

---

## 作者：hzoi_liuchang (赞：0)

## 分析
我们会发现这道题有两个限制:容量和水量

带着两个限制是不好处理的

但是我们可以先确定某一个限制，然后再找另一个限制的最优解

具体地，我们设 $f[i][j]$ 为容量为 $i$ 并且选择了 $j$ 杯水时最大的水量

这东西可以用 $n^4$ 的复杂度预处理出来，但是常数比较小

这样对于每一个询问，我们就可以枚举选择的容量来得到最优的水量

同时我们记录一下总的水量

这样就可以得到剩下的水量

和当前剩余的容量取一个 $min$ 就可以得到结果

要注意把一开始的 $dp$ 数组赋成最小值，因为会有当前水量为 $0$ 的情况
## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#define rg register
inline int read(){
	rg int x=0,fh=1;
	rg char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=115;
int n,a[maxn],b[maxn],f[maxn*maxn][maxn],sum,maxv;
int main(){
	n=read();
	memset(f,0xcf,sizeof(f));
	for(rg int i=1;i<=n;i++){
		a[i]=read(),b[i]=read();
		sum+=b[i];
		maxv+=a[i];
	}
	f[0][0]=0;
	for(rg int i=1;i<=n;i++){
		for(rg int j=maxv;j>=a[i];j--){
			for(rg int k=0;k<i;k++){
				f[j][k+1]=std::max(f[j][k+1],f[j-a[i]][k]+b[i]);
			}
		}
	}
	rg double ans,now;
	for(rg int i=1;i<=n;i++){
		ans=0;
		for(rg int j=1;j<=maxv;j++){
			if(f[j][i]>=0){
				now=(double)(sum-f[j][i])/2;
				now+=f[j][i];
				now=std::min(now,(double)j);
				ans=std::max(ans,now);
			}
		}
		printf("%.5f ",ans);
	}
	printf("\n");
	return 0;
}
```

---

## 作者：Little09 (赞：0)

发现这题的 $n$ 和 $a_i$ 都很小，考虑一个高复杂度的 dp。

倒水的过程肯定不会回倒，那样肯定不优。设选出的 $k$ 个杯子的 $a$ 值和为 $A$，$b$ 值和为 $B$，所有杯子的 $b$ 值和为 $sumb$。可以得到答案就是：

$$\min\{A,sumb*0.5 +B*0.5\}$$

根据值域很小这个性质，我们可以进行背包预处理。处理出每个 $A$ 对应的 $B$ 再计算就很方便了。

至于背包就是个普通的 dp，转移方程：`dp[i][j][k]=max(dp[i-1][j][k],dp[i-1][j-1][k-a[i].a]+a[i].b)` 。

时间和空间复杂度是 $O(n^3*a_i)$，实际上跑不满，可以过得去。空间复杂度还可以用滚动数组缩掉一维，但是没必要了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct bottle
{
	int a,b;
	int id;
}a[101];
int s;
bool used[101];
int dp[101][101][10001];
int main()
{
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		cin >> a[i].a >> a[i].b;
		s+=a[i].b;
	}
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<=n;j++)
		{
			for (int k=0;k<=10000;k++)
			{
				if (j==0&&k==0) continue;
				dp[i][j][k]=-10000000;
			}
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=i;j++)
		{
			for (int k=0;k<=10000;k++)
			{
				if (k>=a[i].a) dp[i][j][k]=max(dp[i-1][j][k],dp[i-1][j-1][k-a[i].a]+a[i].b);
				else dp[i][j][k]=dp[i-1][j][k];
			}
		}
	}
	for (int k=1;k<=n;k++)
	{
		double ans=0;
		for (int i=0;i<=10000;i++)
		{
			ans=max(ans,1.0*min(1.0*i,0.5*s+0.5*dp[n][k][i]));
		}
		printf("%.10lf ",ans);
	}
	return 0;
}
```

顺带提一句，什么 $10^{-9}$ 的精度很显然是假的，只会出现整数和 $.5$ 的情况……

---

## 作者：Fairicle (赞：0)

不妨假定对于某个 $k$，我们选择了 $p_1,p_2,...,p_k$ 这些杯子，那么肯定是将其他未被选的杯子倒入这些杯子中，因为**多次倒显然不优**。

假设选择的所有杯子的 $b$ 值之和为 $b_1$，所有杯子中的 $b$ 之和为 $B$，那么最后能获得的水量就是 $b_1+\dfrac{B-b_1}{2}=\dfrac{b_1+B}{2}$。发现 $\dfrac{B}{2}$ 是常量，只需要最大化 $b_1$ 即可。

值域很小，于是考虑 DP。设 $f_{i,j}$ 表示遍历前 $i$ 个杯子，选择了 $j$ 个的最大 $b$ 值之和。容易得到 $f_{i,j}=max(f_{i-1,j},f_{i-1,j-1}+b_i)$，最后取 $f_{i,j}$ 的最大值就行了...？

这样做，无论从时间复杂度来感性猜想，或是实际验证，都能发现是行不通的，因为这题还有一个杯子容积限制。于是考虑在 dp 方程中加上一维，就是当前所选杯子的 $a$ 值之和，使用 $f_{i,j,k}$ 表示遍历前 $i$ 个杯子，选择了 $j$ 个杯子，$a$ 值之和为 $k$ 时的最大 $b$ 值之和。

则有 $f_{i,j,k}=max(f_{i-1,j,k},f_{i-1,j-1,k-a_i}+b_i)$。

最后对于一个 $k$ 查询时，只需要枚举 $a$ 之和 $V$，然后将其与 $\dfrac{f_{n,k,V}+B}{2}$ 取最小值后，取最大值即可。

（部分思路来源于 codeforces 官方题解）

code：
```cpp
#define ri register int
#define ll long long
#define N 102
int n,b[N],a[N],f[N][N][N*N];
int main(){
    cin>>n;
    for(ri i=1;i<=n;++i) cin>>a[i]>>b[i];
    int all=0;
    for(ri i=1;i<=n;++i) all+=b[i];
    memset(f,-0x3f,sizeof(f));
    f[0][0][0]=0;
    for(ri i=1;i<=n;++i)
    for(ri j=0;j<=i;++j)
    for(ri k=0;k<=10000;++k){
        f[i][j][k]=f[i-1][j][k];
        if(j>0&&k>=a[i]) f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k-a[i]]+b[i]);
    }
    for(ri k=1;k<=n;++k){
        int ans=0;
        for(ri p=0;p<=10000;++p) ans=max(ans,min(p*2,f[n][k][p]+all));
        printf("%d.%d ",ans/2,(ans%2)*5);
    }   
    return 0;
}
```


---

