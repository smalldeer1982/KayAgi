# [USACO20OPEN] Sprinklers 2: Return of the Alfalfa P

## 题目描述

Farmer John 有一块小的田地，形状为一个 $N$ 行 $N$ 列的一个方阵，对于所有的 $1 \le i,j \le N$，从上往下的第 $i$ 行的从左往右第 $j$ 个方格记为 $(i,j)$。他有兴趣在他的田地里种植甜玉米和苜蓿。为此，他需要安装一些特殊的洒水器。  
在方格 $(I,J)$ 中的甜玉米洒水器可以喷洒到所有左下方的方格：即满足 $I \le i$ 以及 $j \le J$ 的 $(i,j)$。

在方格 $(I,J)$ 中的苜蓿洒水器可以喷洒到所有右上方的方格：即满足 $i \le I$ 以及 $J \le j$ 的 $(i,j)$。

被一个或多个甜玉米洒水器喷洒到的方格可以长出甜玉米；被一个或多个苜蓿洒水器喷洒到的方格可以长出苜蓿。但是被两种洒水器均喷洒到（或均喷洒不到）的方格什么也长不出来。

帮助 Farmer John 求出在他的田地里安装洒水器的方案数（ $\bmod \ 10^9 + 7$），每个方格至多安装一个洒水器，使得每个方格均能生长作物（即被恰好一种洒水器喷洒到）。

某些方格正被长毛奶牛占据；这不会阻止这些方格生长作物，但是这些方格里不能安装洒水器。

## 说明/提示

#### 样例 $1$ 解释：
以下是所有十四种可以使得 $(1,1)$ 生长甜玉米的方式。（译注：`C` 表示 sweet corn，即甜玉米；`A` 表示 alfalfa，即苜蓿）

```plain
CC  .C  CA  CC  .C  CA  CA  C.  CA  C.  CC  .C  CC  .C
CC, CC, CC, .C, .C, .C, CA, CA, .A, .A, C., C., .., ..
```

#### 样例 $2$ 提示：

这个样例满足第一个子任务的限制。

-----

对于 $100\%$ 的数据，满足 $1 \le N \le 2000$。

共 $16$ 个测试点，其中 $1\sim 2$ 为样例，其余性质如下：

对于测试点 $3 \sim 4$，满足 $N \le 10$ 且最多有 $10$ 个未被占据的格子。  
对于测试点 $5 \sim 9$，满足 $N \le 200$。  
对于测试点 $10 \sim 16$，无特殊限制。

---

出题人：Benjamin Qi

## 样例 #1

### 输入

```
2
..
..```

### 输出

```
28```

## 样例 #2

### 输入

```
4
..W.
..WW
WW..
...W```

### 输出

```
2304```

# 题解

## 作者：ez_lcw (赞：43)

先讲一下等会要用到的定义：

1. 红格代表被甜玉米洒水器喷洒到的方格，蓝格代表被苜蓿洒水器喷洒到的方格。橙格代表有甜玉米洒水器的方格，紫格代表有苜蓿洒水器。

1. $(a,b)$ 指网格线的交点，$[a,b]$ 指网格。
  
   比如下面这个图中，黄**点**代表的是 $(4,3)$，黄**格**代表的是 $[2,3]$。
    
   ![](https://cdn.luogu.com.cn/upload/image_hosting/edr2jjqh.png)
   
1. $sum_i$ 表示网格图的第 $i$ 行中有多少个没被占据的网格。

~~然后说说考试时的心路历程。~~（其实是用来帮助你如何由暴力思考到正解的）

### $25\ pts$

第一眼看到这道题是不会的……~~甚至连部分分都不知道怎么写~~

但是仔细想了一想，发现红蓝两方阵营肯定是被一条由 $(0,0)$ 到 $(n,n)$ 的分割线分开的。

比如说这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/pkic868g.png)

这种情况是被如图的黄色的分割线分开的。

然后考虑哪些地方需要洒水器：

![](https://cdn.luogu.com.cn/upload/image_hosting/r3a6m13j.png)

显然，我们发现，在分割线的拐角处都需要洒水器（即图中的橙格和紫格），其他地方可填可不填，但是只能填一种洒水器。

我们假设某一种分割线有 $k$ 个拐角（也就是有 $k$ 个洒水器是一定要放的），方阵总面积为 $S$（面积指没有被占据的网格的总数）。

那么对于这种分割线，一共有 $2^{S-k}$ 种方案。（记住这条公式）

那么暴力的方法就显而易见了：每次枚举一条分割线，并记录分割线的拐角数，最后统计答案。

时间复杂度貌似是 $O(2^n+n^2)$，只有 $25pts$。

代码：

```cpp
#include<bits/stdc++.h>
 
#define N 2010
#define mod 1000000007
 
using namespace std;
 
int n,ans,poww[N*N],sum;
char ch[N][N];
 
//n=4
// 0 1 2 3 4 
//0#########
// #.#.#W#.#
//1#########
// #.#.#W#W#
//2#########
// #W#W#.#.#
//3#########
// #.#.#.#W#
//4#########
 
//last=0向下，last=1向上 

void dfs(const int x,const int y,const int a,const int b,const int last)
{
    if(x==n&&y==n)
    {
        ans=(0ll+ans+1ll*poww[sum-a-b])%mod;
        return;
    }
    if(!last)
    {
        if(x+1<=n) dfs(x+1,y,a,b,0);
        if(y+1<=n&&ch[x][y+1]!='W') dfs(x,y+1,a,b+1,1);
    }
    else
    {
        if(x+1<=n&&ch[x+1][y]!='W') dfs(x+1,y,a+1,b,0);
        if(y+1<=n) dfs(x,y+1,a,b,1);
    } 
}
 
inline int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^'0');
        ch=getchar();
    }
    return x;
}
 
int main()
{
    n=read();
    poww[0]=1;
    for(register int i=1;i<=n*n;i++) poww[i]=(2ll*poww[i-1])%mod;
    for(register int i=1;i<=n;i++) scanf("%s",ch[i]+1);
    for(register int i=1;i<=n;i++)
        for(register int j=1;j<=n;j++)
            sum+=(ch[i][j]=='.');
    dfs(1,0,0,0,0);
    dfs(0,1,0,0,1);
    printf("%d\n",ans);
    return 0;
}
```

### $100\ pts$

考虑 $dp$，设 $dp(i,j,0/1)$ 指已经把前 $i$ 行灌溉满了，分割线的终止在 $(i,j)$，分割线最后的方向是向右/向下的。

那么答案显然就是 $dp(n,n,0)+dp(n,n,1)$。

考虑状态转移方程。

1. 先考虑 $dp(i,j,0)$ 怎么转移：

	![](https://cdn.luogu.com.cn/upload/image_hosting/7p8umiki.png)

	如图，我们现在要求出 $dp(3,3,0)$（黄点），那么只能从 $dp(3,2,0/1)$（绿点）转移，因为分割线最后的方向是向右的。

	第一种情况：从 $dp(3,2,0)$ 转移，如图：

	![](https://cdn.luogu.com.cn/upload/image_hosting/kpr316a1.png)

	那么显然有 $dp(3,3,0)=dp(3,2,0)$，因为 $S$ 没变，$k$ 也没变。

	第二种情况：从 $dp(3,2,1)$ 转移，如图：

	![](https://cdn.luogu.com.cn/upload/image_hosting/huhauzy7.png)

	我们发现，原来的分割线终止在 $(3,2)$ 时，$k=1$，就是只有 $[1,2]$ 一个灌溉器，但是现在分割线种植在 $(3,3)$ 时，$k=2$，也就是新增了一个灌溉器 $[3,3]$。那么原来的方案数 $dp(3,2,1)=2^{S-k}$，现在 $k\gets k+1$，所以 $dp(3,3,0)=\frac{dp(3,2,1)}{2}$。

	整合一下，就有 $dp(3,3,0)=dp(3,2,0)+\frac{dp(3,2,1)}{2}$。
    
   即 $dp(i,j,0)=dp(i,j-1,0)+\frac{dp(i,j-1,1)}{2}$

2. 考虑 $dp(i,j,1)$ 怎么转移：

	同理，这次需要从绿点转移：
    
   ![](https://cdn.luogu.com.cn/upload/image_hosting/lce7f5l3.png)
   
   第一种情况：从 $dp(2,3,0)$ 转移，如图：
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/v0o7ack2.png)
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/y9mll9qm.png)
   
   第一幅图是 $dp(2,3,0)$ 的情况，第二幅图是 $dp(3,3,1)$ 的情况。
   
   显然从第一幅图变成第二幅图时 $S$ 增加了 $sum_3$，$k$ 增加了 $1$，那么 $dp$ 值从 $2^{S-k}$ 变成了 $2^{S+sum_3-k-1}$，也就是说 $dp(3,3,1)=dp(2,3,0)\times 2^{sum_3-1}$。
   
   第二种情况：从 $dp(2,3,1)$ 转移，如图：
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/5udnovg3.png)
   
   然后我们发现，$S\gets S+sum_3$，$k$ 没变，则 $dp(3,3,1)=dp(2,3,1)\times 2^{sum_3}$
   
   整合一下，$dp(3,3,1)=dp(2,3,0)\times 2^{sum_3-1}+dp(2,3,1)\times 2^{sum_3}$。
   
   即 $dp(i,j,1)=dp(i-1,j,0)\times 2^{sum_i-1}+dp(i-1,j,1)\times 2^{sum_i}$。
   
到这里，整道题就做完了，已经可以 AC 了。

时间复杂度 $O(n^2)$。

但是还有一些可以优化的地方，这里就大致讲一下，就是把求面积的部分直接提出来，放到最后输出的时候乘上一个 $2^{\sum_{i=1}^n sum_i}$（也就是全局的面积）就好了。

代码（未加优化）：

```cpp
#include<bits/stdc++.h>
 
#define N 2010
#define mod 1000000007
#define half 500000004
 
using namespace std;
 
void add(int &a,int b){a=(0ll+a+b)%mod;}
int mul(int a,int b){return (1ll*a*b)%mod;}
 
int n,dp[N][N][2],sum[N],poww[N*N];
char ch[N][N];
 
int main()
{
    scanf("%d",&n);
    poww[0]=1;
    for(int i=1;i<=n*n;i++)
        poww[i]=mul(2,poww[i-1]);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch[i]+1);
        for(int j=1;j<=n;j++) 
            sum[i]+=(ch[i][j]=='.');
    } 
    dp[0][0][0]=dp[0][0][1]=1;
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(!i&&!j) continue;
            if(j>0)
            {
                add(dp[i][j][0],dp[i][j-1][0]);
                if(ch[i][j]=='.') add(dp[i][j][0],mul(dp[i][j-1][1],half));
            }
            if(i>0)
            {
                add(dp[i][j][1],mul(dp[i-1][j][1],poww[sum[i]]));
                if(ch[i][j]=='.') add(dp[i][j][1],mul(dp[i-1][j][0],poww[sum[i]-1]));
            }
        }
    }
    printf("%d\n",(0ll+dp[n][n][0]+dp[n][n][1])%mod);
    return 0;
}
```

代码（加优化）：

```cpp
#include<bits/stdc++.h>
 
#define N 2010
#define mod 1000000007
#define half 500000004
 
using namespace std;
 
void add(int &a,int b){a=(0ll+a+b)%mod;}
int mul(int a,int b){return (1ll*a*b)%mod;}
 
int n,dp[N][N][2],sum;
char ch[N][N];
 
int poww(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1) ans=(1ll*ans*a)%mod;
        a=(1ll*a*a)%mod;
        b>>=1;
    }
    return ans;
}
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch[i]+1);
        for(int j=1;j<=n;j++) 
            sum+=(ch[i][j]=='.');
    } 
    dp[0][0][0]=dp[0][0][1]=1;
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(!i&&!j) continue;
            if(j>0)
            {
                add(dp[i][j][0],dp[i][j-1][0]);
                if(ch[i][j]=='.') add(dp[i][j][0],mul(dp[i][j-1][1],half));
            }
            if(i>0)
            {
                add(dp[i][j][1],dp[i-1][j][1]);
                if(ch[i][j]=='.') add(dp[i][j][1],mul(dp[i-1][j][0],half));
            }
        }
    }
    printf("%d\n",1ll*(dp[n][n][0]+dp[n][n][1])%mod*poww(2,sum)%mod);
    return 0;
}
```

~~其实就是常数上的优化。~~

~~写码不易，留赞再走。~~

---

## 作者：lahlah (赞：9)

我丢 : https://www.luogu.com.cn/problem/P6275

显然DP,发现最后放出来肯定是长这个亚子

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200516084525970.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM4OTQ0MTYz,size_16,color_FFFFFF,t_70)

深色的一定要放，浅色的可放可不放，答案就是 $\large 2^{\text{浅色块数}}$

把中间那条轮廓线抽出来

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200516084903430.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM4OTQ0MTYz,size_16,color_FFFFFF,t_70)

发现轮廓线折的地方一定要放，所以可以考虑DP轮廓线

$f[i][j][0/1]$表示当前轮廓线在第$i$行，第$j$列格子的右下角那个点，是横/竖的

考虑轮廓线长什么样，每次轮廓线只能向右或向下走一格，这就是个入门DP

因为每次转折的时候都有一个点是一定要放的，相当于随便放的减少了一个，就先把DP值除以$2$在转移出去，最后乘上$\large 2^{size}$即可

code :

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define inv 500000004
#define int long long
#define N 2005
using namespace std;
int n, a[N][N], s[N][N], ss[N][N], f[N][N][2];
signed main() {
	scanf("%lld", &n);
	int cnt = 1;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++) {
			char ch;
			scanf(" %c", &ch);
			if(ch == '.') a[i][j] = 1, cnt = cnt * 2 % mod;
		}
	f[0][1][0] = f[1][0][1] = cnt;
	for(int i = 0; i <= n; i ++)
		for(int j = 0; j <= n; j ++) {
			if(f[i][j][0]) {
				f[i][j + 1][0] += f[i][j][0], f[i][j + 1][0] %= mod;
				if(a[i + 1][j]) f[i + 1][j][1] += f[i][j][0] * inv % mod, f[i + 1][j][1] %= mod;
			}
			if(f[i][j][1]) {
				f[i + 1][j][1] += f[i][j][1], f[i + 1][j][1] %= mod;
				if(a[i][j + 1]) f[i][j + 1][0] += f[i][j][1] * inv % mod, f[i][j + 1][0] %= mod;
			}
		}
	printf("%lld", (f[n][n][0] + f[n][n][1]) % mod);
	return 0;
}
```

~~感觉是题解当中最容易理解的~~

---

## 作者：cff_0102 (赞：8)

首先，可以发现最终两种作物的生长范围一定能够被一条从左上到右下的每次只能向下或向右的线分割：

![](https://cdn.luogu.com.cn/upload/image_hosting/79s3pe55.png)

可以注意到，在内拐角处是必须安装对应洒水器的：

![](https://cdn.luogu.com.cn/upload/image_hosting/emao8zhx.png)

而其它空格则可以选择是否要安装当前所处位置对应的洒水器：

![](https://cdn.luogu.com.cn/upload/image_hosting/kx6araz4.png)

因此，如果中间的这条线确定了，不难求出其对应的方案数。

接着，给方格和格点这样进行编号：

![](https://cdn.luogu.com.cn/upload/image_hosting/20t36o2u.png)

最左上角的格点是 $(0,0)$，与一个格点坐标表示相同的方格在这个格点的左上角。

考虑 dp。设 $dp_{i,j,0/1}$ 表示中间这条线走到了格点 $(i,j)$（~~好像跳舞的线~~），且最后一次走的方向是向右/下时，考虑 $(i,j)$ 及其左上角所有方格，总共可能的方案数。

那么就可以这么转移：

首先考虑 $dp_{i,j,0}$。它的上一步可以是向下的，也可以是向右的。

如果是向右的：

![](https://cdn.luogu.com.cn/upload/image_hosting/e3ly7l6k.png)

计算方案的范围从 $(i,j-1)$ 的左上角变成了 $(i,j)$ 的左上角，多了在第 $j$ 列前 $i$ 行安 A 型洒水器的方案数。设从方格 $(i,j)$ 到方格 $(1,j)$ 的范围内共有 $x$ 个格子是空的，那么这样的方案数就是 $dp_{i,j-1,0}\times2^x$。$x$ 可以前缀和算出。

如果是向下的：

![](https://cdn.luogu.com.cn/upload/image_hosting/8aow52xh.png)

计算方案的范围同样是从 $(i,j-1)$ 的左上角变成了 $(i,j)$ 的左上角，多了在第 $j$ 列前 $i$ 行安 A 型洒水器的方案数。那么这个和上一种情况有什么区别呢？区别在于这种情况会产生一个拐角，而拐角内侧的格子必须放一个 A 型洒水器。因此，如果内侧的格子 $(i,j)$ 被 W 占据，则这种情况的方案数应为 $0$；如果没有，方案数也应该是 $dp_{i,j-1,1}\times2^{x-1}$（而不是 $\times2^x$）。

最终 $dp_{i,j,0}$ 应该是上面两种情况的方案数之和。

$dp_{i,j,1}$ 同理：

![](https://cdn.luogu.com.cn/upload/image_hosting/fembrp9x.png)

在这种情况下，方案数为 $dp_{i-1,j,1}\times2^{x}$，其中 $x$ 是 $(i,j)$ 左侧空格的数量。

![](https://cdn.luogu.com.cn/upload/image_hosting/whfm078x.png)

在这种情况下，若 $(i,j)$ 不是空地，则方案数为 $0$；否则为 $dp_{i-1,j,0}\times2^{x-1}$。

$dp_{i,j,1}$ 即为上面两种情况的方案数之和。

最后输出 $dp_{n,n,0}+dp_{n,n,1}$ 即可。

记得随时取模。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2147,mod=1e9+7;
bool a[N][N];
#define int long long
int sl[N][N],su[N][N];
int dp[N][N][2];
int ksm(int a,int b){
	if(b<0)return 0;
	int s=1;
	while(b){
		if(b&1)(s*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		char c;cin>>c;
		a[i][j]=(c=='W');
		sl[i][j]=sl[i][j-1]+1-a[i][j];
		su[i][j]=su[i-1][j]+1-a[i][j];
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			if(i*j==0){
				if(i==0)dp[i][j][0]=1;
				if(j==0)dp[i][j][1]=1;
				continue;
			}
			dp[i][j][0]=(dp[i][j-1][0]*ksm(2,su[i][j])%mod+(a[i][j]==0)*dp[i][j-1][1]*ksm(2,su[i][j]-1)%mod)%mod;
			dp[i][j][1]=(dp[i-1][j][1]*ksm(2,sl[i][j])%mod+(a[i][j]==0)*dp[i-1][j][0]*ksm(2,sl[i][j]-1)%mod)%mod;
			//cout<<dp[i][j][0]<<"|"<<dp[i][j][1]<<" ";
		}//cout<<endl; 
	}
	cout<<(dp[n][n][0]+dp[n][n][1])%mod;
	return 0;
}
```

BTW 上面代码由于底数是固定的所以其实可以把快速幂改成预处理来着，不过快速幂多一个 $\log$ 也能过这题。

---

## 作者：伟大的王夫子 (赞：6)

发现这道题蛮有意思的，那么我也来发表一下我对这道题的见解吧。

首先，我们可以先找一下规律，发现这个田地肯定会被轮廓线分成两部分，一部分种玉米，另一部分种苜蓿。

然后这些轮廓线的拐弯处是必须放置洒水器的，并且还会从最左上角到达右下角。

我们可以用轮廓线 DP 来进行维护。**具体的说，一条轮廓线对应着许多不同的方案，我们维护轮廓线对应的方案个数。**

不妨设 $dp_{i, j, 0}$ 表示轮廓线最后一个点是 $(i,j)$ 这个方格的右下角，并且最后一条线是横着的**所有的轮廓线**方案数。而 $dp_{i, j, 1}$ 的定义也差不多，就是最后一条线不是横着而是竖着。

而转移方程我们就拿横着的来举例。考虑 $dp_{i-1,j, 0}$ 对其的贡献。因为拐角的数量不变，所以只用简单相加。

但如果从 $dp_{i-1,j,1}$ 转移过来，那么就会多一个拐角，此时就要把方案数给除以 2。

当然，第二种转移需要 $a_{i, j}$ 是个空地。

而 $dp_{i, j, 1}$ 的转移同理。

初值 $dp_{0, 0, 0} = dp_{0, 0, 1} = 2^S$。因为这时每个方格可以自由选择放或不放，轮廓线也只有一条，所以方案数为 $2^S$。

注：$S$ 的定义：所有 $n^2$ 个格子中空地的个数。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n;
LL dp[2005][2005][2];
char a[2005][2005];
const LL P = 1e9 + 7;
LL power(LL a, LL b) {
	LL c = 1;
	for (; b; b >>= 1) {
		if (b & 1) c = c * a % P;
		a = a * a % P;
	}
	return c;
}
LL mul(LL a, LL b) {
	return a * b % P;
}
inline void Add(LL &x, LL y) {
	x = (x + y) % P;
}
int main() {
	scanf("%d", &n);
	int S = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%s", a[i] + 1);
		for (int j = 1; j <= n; ++j) S += a[i][j] == '.';
	}
	dp[0][0][0] = dp[0][0][1] = power(2, S);
	LL half = power(2, P - 2);
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n; ++j) {
			if (i) {
				Add(dp[i][j][0], dp[i - 1][j][0]);
				if (a[i][j] == '.') Add(dp[i][j][0], mul(dp[i - 1][j][1], half));
			}
			if (j) {
				Add(dp[i][j][1], dp[i][j - 1][1]);
				if (a[i][j] == '.') Add(dp[i][j][1], mul(dp[i][j - 1][0], half));
			}
		}
	printf("%lld", (dp[n][n][0] + dp[n][n][1]) % P);
}
```

---

## 作者：hhhyyyfff (赞：3)

注：原来一篇公式挂了。

- 题意简述：  
  有一块 $N \times N$ 的网格田，有两种灌溉器。设一个灌溉器安装在 $(I,J)$，甜玉米灌溉器能灌溉 $(i,j)\ (I \le i\text{且}j \le J)$，苜蓿灌溉器能灌溉 $(i,j)\ (i \le I\text{且}J \le j)$。每个网格最多只能安装一种灌溉器，每个网格必须刚好被一**种**灌溉器灌溉。有一部分网格不能安装灌溉器，求安装方案数。

- 前置知识：前缀和，DP

- 算法分析 $O(n^2)$：  
  根据两种灌溉器的特点，安装后的灌溉情况应该是这样的。  
  ![4-1-1 灌溉情况](https://cdn.luogu.com.cn/upload/image_hosting/91ef4urs.png)  
  两种灌溉区域呈阶梯状分布，灌溉器安装在折角处（红色为甜玉米，蓝色为苜蓿）。  
  设 $f_{i,j}$ 表示在 $(i,j)$ 处安装甜玉米灌溉器时，只考虑 $(x,y)\ (x<i\text{或}y \le j)$ 这部分的方案数。  
  ![4-1-2 状态转移](https://cdn.luogu.com.cn/upload/image_hosting/w5slsojc.png)  
  如上图所示，当深红色方格转移到红色方格时，必须安装蓝色方格，浅灰色方格装不装皆可（但安装的灌溉器种类是确定的）。  
  因此，$f_{i,j}=\sum f_{k,l} \times 2^{s_{k,l+1}-s_{i,j+1}} \times [map_{i,j}=1] \times [map_{i-1,l+1}=1]$  
  其中 $map_{i,j}$ 表示 $(i,j)$ 能否安装灌溉器，$s_{i,j}=\sum_{k=i}^N \sum_{l=j}^{N} [map_{k,l}=1]=s_{i+1,j}+s_{i,j+1}-s_{i+1,j+1}+[map_{i,j}=1]$  
  然后，我们会发现这个DP的复杂度是 $O(n^4)$ 的，需要进行优化。  
  首先，整理$f_{i,j}=\sum_{k<i,l<j} (f_{k,l} \times 2^{s_{k,l+1}}) \times [map_{i-1,l+1}=1] \times (2^{-s_{i,j+1}} \times [map_{i,j}=1])$  
  令$g_{i,j}=\sum_{k<i} f_{k,j} \times 2^{s_{k,j+1}}=g_{i-1,j}+f_{i-1,j} \times 2^{i-1,j+1}$  
  则$f_{i,j}=(2^{-s_{i,j+1}} \times [map_{i,j}=1]) \times (\sum_{k<j} g_{i,k} \times [map_{i-1,k}=1])$  
  后一部分可以前缀和优化，复杂度就降到 $O(n^2)$ 了。总而言之，对原 DP 方程在行和列的方向进行前缀和优化即可，方法有很多。

- 代码：

``` cpp
#include <cstdio>

using namespace std;
#define MOD 1000000007

char mp[2010][2010];
int N, ans, s[2010][2010], f[2010][2010], g[2010];
long long p[4000010], ip[4000010];

int main() {
  freopen("sprinklers2.in", "r", stdin);
  freopen("sprinklers2.out", "w", stdout);
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) scanf("%s", mp[i] + 1);
  for (int i = N; i >= 0; --i)
    for (int j = N; j >= 0; --j)
      s[i][j] = s[i + 1][j] + s[i][j + 1] - s[i + 1][j + 1] + (mp[i][j] == '.');
  p[0] = ip[0] = 1;
  for (int i = 1; i <= N * N; ++i) {
    p[i] = p[i - 1] * 2 % MOD;
    ip[i] = ip[i - 1] * (MOD / 2 + 1) % MOD;
  }
  f[0][0] = 1;
  g[0] = p[s[0][1]];
  for (int i = 1; i <= N; ++i) {
    int sum = 0;
    for (int j = 1; j <= N; ++j) {
      sum = (sum + g[j - 1] * (mp[i - 1][j] != 'W')) % MOD;
      f[i][j] = ip[s[i][j + 1] + 1 + (i > 1)] * (mp[i][j] == '.') * sum % MOD;
    }
    for (int j = 1; j <= N; ++j) g[j] = (g[j] + f[i][j] * p[s[i][j + 1]]) % MOD;
  }
  for (int i = 1; i <= N; ++i)
    ans = (ans + g[i - 1] * (mp[N][i] == '.') * ip[1]) % MOD;
  ans = (ans + g[N]) % MOD;
  printf("%d\n", ans);
  return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

观察到：

* 对于每一列，一定是上面一些 `A`，下面一些 `C`；
* 对于每一行，一定是左边一些 `C`，右边一些 `A`。

结论容易由反证证明。

该性质等价于右上方一块连通的 `A`，左下方一块连通的 `C`，也就是说分割线是一条由 $(0,0)$ 到 $(n,n)$ 的折线。

容易发现在折角的位置必须放置洒水器，其他位置可放可不放，于是折角处必须为 `.`。也就是总方案数等于每条折线的 $2^{tot-k}$ 之和，其中 $tot$ 为总共的 `.` 数，$k$ 为折角数。

考虑 $dp_{i,j,0/1}$ 表示看到 $(i,j)$，目前向右/下。转移分两类：

* 继续延这个方向；
* 转角，要求 $(i+1,j+1)$ 是 `.`，且有一个位置强制放置，系数为 $\frac{1}{2}$。

最后答案就是 $2^{tot}(dp_{i,j,0}+dp_{i,j,1})$。总复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long 
#define add(i,j) ((i+j>=mod)?(i+j-mod):(i+j))
using namespace std;
const int mod=1e9+7,inv2=(mod+1)/2;
char c[2005][2005];
int dp[2005][2005][2];
int pre[2005][2005],suf[2005][2005],pw2[2005];
signed main(){
	int n,cnt=0; cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%s",c[i]+1);
		for(int j=1;j<=n;j++){
			cnt+=(c[i][j]=='.');
		}
	}
	int tmp=1;
	for(int i=1;i<=cnt;i++) (tmp*=2)%=mod;
	dp[0][0][0]=dp[0][0][1]=tmp;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			(dp[i+1][j][0]+=dp[i][j][0])%=mod;
			if(c[i+1][j+1]=='.') (dp[i+1][j][1]+=dp[i][j][0]*inv2%mod)%=mod;
			(dp[i][j+1][1]+=dp[i][j][1])%=mod;
			if(c[i+1][j+1]=='.') (dp[i][j+1][0]+=dp[i][j][1]*inv2%mod)%=mod;
		}
	}
	cout<<(dp[n][n][0]+dp[n][n][1])%mod;
	return 0;
}
```

---

## 作者：EndSaH (赞：2)

[欢迎光临个人博客，这里的可能不会更新](https://endsah.tk/blog/USACO-2020-US-Open-Solution/)

建议到上面的链接或者洛谷博客里阅读，题解界面的公式渲染有些问题

# Solution

观察题目性质可以发现，如果只看那些覆盖左下角的点，他们的并形成了一个递减轮廓线，并且覆盖右上角的那些点一定位于轮廓线的折处的右上角。

所以相当于是要 DP 出有多少个合法的轮廓线。

实际上还有一个问题，就是除了轮廓线上的点以外，其他的可以种洒水器的点都会有两种选择。这些点带来的方案数在 DP 中乘出来是不太现实的，转移方程会因此变得极其复杂，所以一个比较好的解决方案是把所有状态的值全部除掉一个 2^折点数量，最后再乘上 2^可以种洒水器的点的总数量 即可。

设 $f(i, j)$ 表示已经考虑好了前 $j$ 列的轮廓线，第 $j$ 列的覆盖左下角的那个点在第 $i$ 行。（注意这里的 $i$ 可以到 $n + 1$）

转移时枚举 $k$ 表示 $[k, j]$ 这一块被当前轮廓线覆盖，可以得到转移方程：

$$
f(i, j) = \frac {\sum _{k = 1} ^j \sum _{l = 1} ^{i - 1} [(i - 1, k) \text{ is coverable}] f(l, k - 1)} 4
$$

因为这里增加了两个折点，所以除个 $4$。注意第一行和第 $n + 1$ 行考虑时只用除 $2$。

前缀优化一下就是 $O(n ^2)$ 的了。

## Code

```cpp
#include <cstdio>
#include <iostream>

#define Dec(x) (x >= mod ? x -= mod : 0)

using namespace std;

typedef long long LL;

const int maxN = 2e3 + 5;
const int mod = 1e9 + 7;
const int inv4 = 250000002;

int n;
char g[maxN][maxN];
int sum[maxN];
int f[maxN][maxN];

int FPM(int bas, int ind)
{
    int res = 1;
    while (ind)
    {
        if (ind & 1)
            res = (LL)res * bas % mod;
        bas = (LL)bas * bas % mod;
        ind >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    int s = 0;
    for (int i = 1; i <= n; ++i)
        cin >> (g[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            s += g[i][j] == '.';
    f[1][0] = sum[0] = 1;
    for (int j = 1; j <= n; ++j) if (g[1][j] == '.')
        f[1][j] = sum[j] = (mod + 1) >> 1;
    for (int i = 1; i <= n; ++i)
    {
        if (i != 1)
        {
            for (int j = 1; j <= n; ++j)
                f[i][j] += f[i][j - 1], Dec(f[i][j]);
            f[i][0] = 1;
            for (int j = 1; j <= n; ++j)
            {
                if (g[i][j] == 'W')
                    f[i][j] = 0;
                f[i][j] = (LL)f[i][j] * inv4 % mod;
                sum[j] += f[i][j], Dec(sum[j]);
            }
        }
        for (int j = 1; j <= n; ++j)
            if (g[i][j] == '.')
                f[i + 1][j] += sum[j - 1], Dec(f[i + 1][j]);
    }
    for (int j = 1; j <= n; ++j)
        f[n + 1][j] += f[n + 1][j - 1], Dec(f[n + 1][j]);
    f[n + 1][0] = 1;
    for (int j = 1; j <= n; ++j)
        f[n + 1][j] = f[n + 1][j] * LL(mod / 2 + 1) % mod;
    sum[n] += f[n + 1][n], Dec(sum[n]);
    cout << (LL)sum[n] * FPM(2, s) % mod << endl;

    return 0;
}
```


---

## 作者：MoyunAllgorithm (赞：1)

### 分析

一个重要的性质是，存在一条折线：

- 只会向下、向右拐弯。

- 从 $(0,0)$ 到 $(N,N)$。

- 这个折线左侧是作物 $\text{A}$，另一侧是作物 $\text{B}$。

- 每一个拐弯处，若是向下拐，则拐角的左下方必须有洒水器；若是向右拐，则拐角的右上方必须有洒水器。

根据这一性质，我们可以以此得到

$\text{dp}(i,j)$ 表示折线在纵坐标 $i$ 时，最右侧的横坐标是 $j$ 时，满足该条件的洒水器分配情况数量。本质上，就是网格的第 $i$ 行的前 $j$ 格是洒水器 $\text{A}$ 的势力范围，后面是 $\text{B}$ 的势力范围的方案数。

考虑用“填表法”转移，即从状态的前驱推出当前状态。

设 $\text{tot}(i)$ 表示第 $i$ 行的可种植方格个数。

$\text{dp}$ 的初始化为:

- $\text{dp}(1,0)= 2^{\text{tot}(1)}$；

- $\text{dp}(1,i)= 2^{\text{tot}(1)-1}(i \in [1,N],\text{c}(i,j) \neq \texttt{W})$（因为 $(1,i)$ 必须放置洒水器）；

- $\text{dp}(1,0)=0 (\text{otherwise})$。

转移：考虑折线是否向右转。

- 不向右转，继续向下，没有任何约束。

$\text{dp}(i,j)=\text{dp}(i-1,j) \times 2^{\text{tot}(i)}$。

- 向右转。枚举右转前它在哪，有

$\text{dp}(i,j)=\sum_{k=0}^{j-1} \dfrac{\text{dp}(i-1,k)}{2} \times [\text{c}(i-1,k+1) \neq \texttt{W}]$。

有点抽象，因为我们看这条折线的第四条性质：

>  每一个拐弯处，若是向右拐，则拐角的右上方必须有洒水器。

$\text{c}(i-1,k+1)$ 就是拐角的右上方，是必须放置洒水器的，否则不合法。那既然这一个强制放置洒水器，那也就是说 $\text{dp}(i-1,k)$ 只有一半的方案是合法的（也就是在那里放置了洒水器的方案），需要除以 $2$。实现时乘以其逆元即可。

你可能要问：那我们是如何保证 

>  每一个拐弯处，若是向下拐，则拐角的左下方必须有洒水器。

的呢？很简单：当 $\text{c}(i,j)=\texttt{W}$ 时，只执行第一种转移，也就是让折线向下延伸，而不是从右往下拐。

可以在 $O(N^3)$ 的时间内完成该问题。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MOD=1e9+7;
char c[205][205];
LL dp[205][205];
int yes[205][205];
LL po[205];
int N,inv;
int QPow(LL base,int po)
{
    LL res=1;
    while(po)
    {
        if(po&1) res=res*base%MOD;
        base=base*base%MOD;
        po>>=1;
    }
    return res;
}
int main()
{
    freopen("rural.in","r",stdin);
    freopen("rural.out","w",stdout);
    scanf("%d",&N);
    po[0]=1;
    inv=QPow(2,MOD-2);
    for(int i=1;i<=N;i++) po[i]=(po[i-1]<<1)%MOD;
    for(int i=1;i<=N;i++)
    {
        scanf("%s",c[i]+1);
        yes[i][0]=0;
        for(int j=1;j<=N;j++)
        {
            yes[i][j]=yes[i][j-1];
            if(c[i][j]!='W') yes[i][j]++;
        }
       // printf("%d\n",yes[i][N]);
    }
    dp[1][0]=po[yes[1][N]];
    for(int i=1;i<=N;i++)
    {
        if(c[1][i]=='W') dp[1][i]=0;
        else dp[1][i]=po[yes[1][N]-1];
    }
    for(int i=2;i<=N;i++)
    {
        for(int j=0;j<=N;j++)
        {
            if(c[i][j]=='W')
            {
                dp[i][j]=dp[i-1][j];
                dp[i][j]*=po[yes[i][N]];
                dp[i][j]%=MOD;
                continue;
            }
            for(int k=0;k<j;k++)
            {
                if(c[i-1][k+1]=='W') continue;
                dp[i][j]+=dp[i-1][k]*inv%MOD;
            }
            dp[i][j]%=MOD;
            dp[i][j]*=po[yes[i][N]-(j!=0)];
            dp[i][j]%=MOD;
            dp[i][j]+=dp[i-1][j]*po[yes[i][N]]%MOD;
            dp[i][j]%=MOD;
        }
    }
  /*  for(int i=1;i<=N;i++)
    {
        for(int j=0;j<=N;j++) printf("%lld ",dp[i][j]);
        puts("");
    }*/
    LL ans=0;
    for(int i=0;i<=N;i++) 
    {
        if(i!=N) dp[N][i]=dp[N][i]*inv%MOD;
        if(i!=N&&c[N][i+1]=='W') dp[N][i]=0;
        ans+=dp[N][i];
    }
    printf("%d\n",ans%MOD);
	return 0;
}
```

然而会超时。你会发现第二种转移会带来额外的 $O(N)$ 复杂度。然而可以前缀和优化掉。那个带 $\sum$ 的式子是可以在 $j$ 增加的同时顺便递推的。看代码：

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MOD=1e9+7;
char c[2005][2005];
LL dp[2005][2005];
int yes[2005][2005];
LL po[2005];
int N,inv;
int QPow(LL base,int po)
{
    LL res=1;
    while(po)
    {
        if(po&1) res=res*base%MOD;
        base=base*base%MOD;
        po>>=1;
    }
    return res;
}
int main()
{
    //freopen("rural.in","r",stdin);
   //freopen("rural.out","w",stdout);
    scanf("%d",&N);
    po[0]=1;
    inv=QPow(2,MOD-2);
    for(int i=1;i<=N;i++) po[i]=(po[i-1]<<1)%MOD;
    for(int i=1;i<=N;i++)
    {
        scanf("%s",c[i]+1);
        yes[i][0]=0;
        for(int j=1;j<=N;j++)
        {
            yes[i][j]=yes[i][j-1];
            if(c[i][j]!='W') yes[i][j]++;
        }
       // printf("%d\n",yes[i][N]);
    }
    dp[1][0]=po[yes[1][N]];
    for(int i=1;i<=N;i++)
    {
        if(c[1][i]=='W') dp[1][i]=0;
        else dp[1][i]=po[yes[1][N]-1];
    }
    for(int i=2;i<=N;i++)
    {
        LL sum=0;//这就是之前那个sigma
        for(int j=0;j<=N;j++)
        {
            if(c[i][j]=='W')
            {
                dp[i][j]=dp[i-1][j];
                dp[i][j]*=po[yes[i][N]];
                dp[i][j]%=MOD;
            }
            else 
            {
                dp[i][j]+=sum;
                dp[i][j]%=MOD;
                dp[i][j]*=po[yes[i][N]-(j!=0)];
                dp[i][j]%=MOD;
                dp[i][j]+=dp[i-1][j]*po[yes[i][N]]%MOD;
                dp[i][j]%=MOD;
            }
            if(c[i-1][j+1]!='W') sum=(sum+dp[i-1][j]*inv)%MOD;
        }
    }
  /*  for(int i=1;i<=N;i++)
    {
        for(int j=0;j<=N;j++) printf("%lld ",dp[i][j]);
        puts("");
    }*/
    LL ans=0;
    for(int i=0;i<=N;i++) 
    {
        if(i!=N) dp[N][i]=dp[N][i]*inv%MOD;
        if(i!=N&&c[N][i+1]=='W') dp[N][i]=0;
        ans+=dp[N][i];
    }
    printf("%lld\n",ans%MOD);
	return 0;
}
```

$O(N^2)$。

---

## 作者：Plozia (赞：1)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/121358932)

一道很妙的 DP 题，一眼过去感觉这好像是个轮廓线 DP，然后这道题确实是轮廓线 DP 但不是 $2^n$ 那种的。

本篇题解参照了其他题解的思路 ~~（我从来没写过这种套路的题）~~，在此表示感谢。

直接进入正解。

首先规定一下本文中的 $(i,j)$ 不是指第 $i$ 行第 $j$ 列，而是指网格线的第 $i$ 行第 $j$ 列这个点，如下图所示：

![在这里插入图片描述](https://img-blog.csdnimg.cn/2fe380d15a614421a80e96dd1d1977f1.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUGxvemlh,size_18,color_FFFFFF,t_70,g_se,x_16)
红色点就是 $(4,5)$。

这道题的轮廓线就是从 $(0,0)$ 到 $(n,n)$ 的一条往右下线。

设 $f_{i,j,0/1}$ 表示前面 $i$ 行都全部覆盖，当前轮廓线终止在 $(i,j)$，轮廓线的最后一根方向是往右还是往下时的方案数。

---------

首先看几个结论：

1. 轮廓线的拐点数就是必须要放的洒水器数。

比如说下图，有 5 个拐点，那么就要放 5 个洒水器。

![在这里插入图片描述](https://img-blog.csdnimg.cn/e7eae457bebe41cc8a86db3e848edec2.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUGxvemlh,size_18,color_FFFFFF,t_70,g_se,x_16)

2. 假设上图必须要放 $k$ 个洒水器，整张图能放洒水器的面积为 $S$，那么对于当前轮廓线的总方案数为 $2^{S-k}$。
	这个结论还是很明显的吧，就是因为剩下的点可放可不放，而且每个点能放的洒水器数量只有一种。

---------

好的又设 $sum_{i}$ 表示这一行的能放洒水器的数量（空地数），可以开始推方程了。

对于 $f_{i,j,0}$：

我们发现其需要从 $f_{i,j-1,0/1}$ 转移。

1. 从 $f_{i,j-1,0}$ 转移。

此时是这样的：

![在这里插入图片描述](https://img-blog.csdnimg.cn/9928fce0a1cc4a5780d225f180d121d2.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUGxvemlh,size_12,color_FFFFFF,t_70,g_se,x_16)

发现拐点数没变，覆盖总面积也没变，因此 $f_{i,j-1,0}$ 的贡献是 $f_{i,j-1,0}$。

2. 从 $f_{i,j-1,1}$ 转移。

![在这里插入图片描述](https://img-blog.csdnimg.cn/236fe3dbaa31403888876e16d570a6bd.png)

发现新增了一个红色的洒水器，总面积没变，对应的 $2^{S-k}$ 变为 $2^{S-k-1}$，因此 $f_{i,j-1,1}$ 的贡献是 $\dfrac{f_{i,j-1,1}}{2}$。

综上，$f_{i,j,0}=f_{i,j-1,0}+\dfrac{f_{i,j-1,1}}{2}$。

对于 $f_{i,j,1}$：

注意 $f_{i,j,1}$ 需要从 $f_{i-1,j,0/1}$ 转移过来，因此面积数和拐点数都有变动。

$f_{i-1,j,0}$ 的贡献：面积数增加 $sum_i$，拐点数增加 1，方案数变化为 $2^{S-k} \to 2^{S-k+sum_i-1}$，因此贡献是 $f_{i-1,j,0} \times 2^{sum_i-1}$。

$f_{i-1,j,1}$ 的贡献：面积数增加 $sum_i$，拐点数不变，方案数变化为 $2^{S-k} \to 2^{S-k+sum_i}$，因此贡献是 $f_{i-1,j,1} \times 2^{sum_i}$。

所以 $f_{i,j,1}=f_{i-1,j,0} \times 2^{sum_i-1}+f_{i-1,j,1} \times 2^{sum_i}$。

这一组转移可以参考下面两幅图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/a3175b33f72e4e83a01335b3123cf596.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUGxvemlh,size_12,color_FFFFFF,t_70,g_se,x_16)
![在这里插入图片描述](https://img-blog.csdnimg.cn/9620915bab174eb0a95e1419d4033718.png?x-oss-process=image/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBAUGxvemlh,size_12,color_FFFFFF,t_70,g_se,x_16)

注意 DP 的时候 $i : \text\red{0} \to n,j : \text\red{0} \to n$，整体代码还是很好写的。

Code：[GitHub CodeBase-of-Plozia P6275 [USACO20OPEN]Sprinklers 2 Return of the Alfalfa P.cpp](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/%E8%BD%AE%E5%BB%93%E7%BA%BF%20DP/P6275%20%5BUSACO20OPEN%5DSprinklers%202%20Return%20of%20the%20Alfalfa%20P.cpp)

```cpp
/*
========= Plozia =========
    Author:Plozia
    Problem:P6275 [USACO20OPEN]Sprinklers 2: Return of the Alfalfa P
    Date:2021/11/16
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2e3 + 5;
const LL P = 1e9 + 7;
int n, a[MAXN][MAXN], sum[MAXN], Pow[MAXN], f[MAXN][MAXN][2];

int Read()
{
    int sum = 0, fh = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
    return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }
int Add(int fir, int sec) { return (fir + sec >= P) ? (fir + sec - P) : (fir + sec); }
LL ksm(LL a, LL b = P - 2, LL p = P)
{
    LL s = 1 % p;
    for (; b; b >>= 1, a = a * a % p)
        if (b & 1) s = s * a % p;
    return s;
}
const LL inv2 = ksm(2);

int main()
{
    n = Read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            char ch = getchar();
            while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
            if (ch == '.') a[i][j] = 1;
            sum[i] += a[i][j];
        }
    Pow[0] = 1;
    for (int i = 1; i <= n; ++i) Pow[i] = Pow[i - 1] * 2 % P;
    f[0][0][0] = f[0][0][1] = 1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
        {
            if (!i && !j) continue;
            if (j > 0)
            {
                f[i][j][0] = f[i][j - 1][0];
                if (a[i][j] == 1) f[i][j][0] = Add(f[i][j][0], 1ll * f[i][j - 1][1] * inv2 % P);
            }
            if (i > 0)
            {
                f[i][j][1] = 1ll * f[i - 1][j][1] * Pow[sum[i]] % P;
                if (a[i][j] == 1) f[i][j][1] = Add(f[i][j][1], 1ll * f[i - 1][j][0] * Pow[sum[i] - 1] % P);
            }
        }
    printf("%lld\n", (1ll * f[n][n][0] + 1ll * f[n][n][1]) % P); return 0;
}
```

---

## 作者：Anonymely (赞：0)

由于不能重叠，所以轮廓线呈阶梯状，且每个拐角处必须放，剩下的随便放，对答案贡献是 $2^{c-\text{拐角数量}}$。

故直接对轮廓线做 dp，$f_{i,j,0/1}$ 表示当前在 $(i,j)$ 右下角且最后一段是向右/向下，转移是平凡的。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, const T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, const T y) {x = min(x, y);}

const int mod = 1e9 + 7;
const int inv = (mod + 1) / 2;
const int N = 2005;
void add(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}
int n;
string s[N];
int f[N][N][2];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i] = " " + s[i];
    int pw = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i][j] == '.') pw = 1ll * pw * 2 % mod;
        }
    }
    f[0][0][1] = f[0][0][0] = pw;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (j) {
                f[i][j][0] = f[i][j - 1][0];
                if (s[i][j] == '.') add(f[i][j][0], 1ll * f[i][j - 1][1] * inv % mod);
            }
            if (i) {
                f[i][j][1] = f[i - 1][j][1];
                if (s[i][j] == '.') add(f[i][j][1], 1ll * f[i - 1][j][0] * inv % mod);
            }
        }
    }
    cout << (f[n][n][0] + f[n][n][1]) % mod << '\n';
    QwQ01AwA;
}
```

---

## 作者：arrow_king (赞：0)

# $O(n^3)$ 做法

我们发现最后染色的图中会存在一条折线分界线，在折线的左下方都是玉米，右上方都是苜蓿。因此我们考虑设状态 $dp_{i,j,0/1}$ 表示考虑子矩阵 $(1,1)\sim(i,j)$ 且 $(i,j)$ 被染色为 $0/1$ 的方案数（注意被染色不代表建立洒水站）。以下以种植玉米来举例。

![](https://cdn.luogu.com.cn/upload/image_hosting/csmv2ltp.png)

考虑 $dp_{i,j,0}$ 的值，显然可以发现存在一个最高的点 $(k,j)$ 被放置了洒水站，而可以注意到 $(k-1,j)$ 被种上了苜蓿，因此可以写出 dp 方程
$$
dp_{i,j,0}=\sum_{k=1}^{i}[c_{k-1,j}\neq\mathtt W]dp_{k-1,j,1}\times\operatorname{VAL}(1,k,i,j)
$$
其中 $\operatorname{VAL}(x_1,y_1,x_2,y_2)$ 是在子矩阵 $(x_1,y_1)\sim(x_2,y_2)$ 中任意放置洒水站的方案数，等于 $2^{\text{不是牛的格子数}-1}$。（为什么要减一呢？因为 $(k,j)$ 一定要放洒水站）。

这样动态规划就是 $O(n^3)$，最后答案是 $dp_{n,n,1}+dp_{n,n,0}$。

# $O(n^2)$

我们发现求和过程中有前缀和，因此用前缀和优化上述 dp，就可以做到 $O(n^2)$ 求答案。

前缀和 $s_{i,j,0/1}$ 的定义是当前一列/行**往下/右一格不是牛**的 $dp_{x,y}\times[2\operatorname{VAL}(1,1,x,y)]^{-1}$，这样才能在求答案的时候直接用 $\operatorname{VAL}(1,1,i,j)$ 一次性求出来。

```cpp
for(int i=1;i<=n;i++) dp[0][i][0]=dp[0][i][1]=dp[i][0][0]=dp[i][0][1]=1;
dp_sum[0][0][0]=dp_sum[0][0][1]=1;
for(int i=1;i<=n;i++) {
	if(c[i][1]!='W') dp_sum[i][0][0]=dp_sum[i][0][1]=1;
	if(c[1][i]!='W') dp_sum[0][i][0]=dp_sum[0][i][1]=1;
}
for(int i=1;i<=n;i++) {
	for(int j=1;j<=n;j++) {
		if(c[i][j]=='W') {
			if(i!=1) dp[i][j][0]=(dp_sum[i-2][j][1])%mod*Val(1,1,i,j)%mod;
			if(j!=1) dp[i][j][1]=(dp_sum[i][j-2][0])%mod*Val(1,1,i,j)%mod;
		}
		else {
			dp[i][j][0]=dp_sum[i-1][j][1]*Val(1,1,i,j)%mod;
			dp[i][j][1]=dp_sum[i][j-1][0]*Val(1,1,i,j)%mod;
		}
		dp_sum[i][j][0]=dp_sum[i][j-1][0];
		dp_sum[i][j][1]=dp_sum[i-1][j][1];
		if(c[i][j+1]!='W') dp_sum[i][j][0]=(dp_sum[i][j][0]+dp[i][j][0]*Val_inv(1,1,i,j)%mod)%mod;
		if(c[i+1][j]!='W') dp_sum[i][j][1]=(dp_sum[i][j][1]+dp[i][j][1]*Val_inv(1,1,i,j)%mod)%mod;
	}
}
printf("%lld\n",(dp[n][n][0]+dp[n][n][1])%mod);
```

---

