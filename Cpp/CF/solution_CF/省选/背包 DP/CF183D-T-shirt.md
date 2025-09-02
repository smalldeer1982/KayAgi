# T-shirt

## 题目描述

你将在 CodeForces 的一个 $n$ 人团队实习，$n$ 个工程师由 $1$ 到 $n$ 编号。你决定给每个工程师一个纪念品：一件来自你的国家的 T 恤（T 恤在 CodeForces 很受欢迎）。不幸的是，你不知道 $n$ 个工程师各自衣服的尺寸。一共有 $1$ 到 $m$ 共 $m$ 种不同的尺寸，并且每个工程师只适合一个尺寸。

你不知道每个工程师的尺寸，所以你询问你的朋友 Gerald。很遗憾，他也不知道每个工程师的尺寸，但他知道对于第 $i$ 个工程师，适合第 $j$ 种 T 恤的概率。

最后你带来了 $n$ 件 T 恤（这 $n$ 件 T 恤可以是任意组合，你也可以带多件同样尺寸的衣服），在你准备 T 恤的时候并不知道每个工程师的尺寸，所以你只能根据 Gerald 提供的概率决定你所带的T恤。

当你到达办公室后，你会询问每个工程师他适合的T恤的尺寸，如果你有那个尺寸的衣服，你就会给他一件，否则就不给他 T 恤。你会从 $1$ 号问起，一直问到 $n$ 号。

你的任务是最大化收到适合自己的衣服的工程师数量的期望值。

## 样例 #1

### 输入

```
2 2
500 500
500 500
```

### 输出

```
1.500000000000
```

## 样例 #2

### 输入

```
3 3
1000 0 0
1000 0 0
0 1000 0
```

### 输出

```
3.000000000000
```

## 样例 #3

### 输入

```
1 4
100 200 300 400
```

### 输出

```
0.400000000000
```

# 题解

## 作者：C20203030 (赞：10)

## 一、题目
![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3Uub3JnL3VwbG9hZC9waWMvNzQ0NzcucG5n?x-oss-process=image/format,png)

## 二、解法
网上的题解貌似学得不是很清楚（反正蒟蒻作者是很难看懂的），我就来补一发详细题解吧。

**0x01 暴力dp**

~~期望的题好像暴力都很难写~~ 。

设$f[i][j][k]$表示前$i$个人，有$j$个人喜欢第$k$件衣服的概率，则有转移：

$f[i][j][k]=f[i-1][j-1][k]*p[i][k]+f[i-1][j][k]*(1-p[i][k])$

$p[i][k]$表示第$i$个人喜欢第$k$件衣服的概率。

设$g[i][k]$表示准备了$i$件第$k$种衣服，送出衣服的期望，那么：

$g[i][k]=\sum_{j=0}^{i} j*f[n][j][k]+i*\sum_{j=i+1}^{n} f[n][j][k]$
然后对$g$数组进行背包即可，时间复杂度$O(n^{2}m)$。

**0x02 优化**

首先有一个式子：

$\sum_{i=0}^{n} f[n][i][k]=1$（似乎很显然，但后面的变化要用到）

观察$g$数组，对它做差：

$g[i+1][k]-g[i][k]=\sum_{j=i+1}^{n} f[n][j][k]=1-\sum_{j=1}^{i}f[n][j][k]$

发现$g$数组是单调递增的，且随着$i$的增大，他们的差单调变小。

这就给了我们贪心的依据，我们只需要选差最大的$g$，把它加入答案即可。

但是我们仍需对$f$数组进行优化，由于期望的线性性，不同的物品是互不相关的（看$dp$式也看得出来），有一些不优的物品就不需要把它的$dp$全部处理出来（用多少算多少）。

于是我们重新定义$dp$，设$f[i][j]$为对于第$i$件衣服，前$j$人有$cnt[i]$个人喜欢的概率（转移用滚动数组），$g[i]$为准备了$cnt[i]$件第$i$种衣服，送出的期望，转移是注意用前缀和优化一下。

时间复杂度$O(n^{2}+nm)$

```cpp
#include <cstdio>
#include <cstring>
const int MAXN = 3005;
int read()
{
    int num=0,flag=1;char c;
    while((c=getchar())<'0'||c>'9')if(c=='-')flag=-1;
    while(c>='0'&&c<='9')num=(num<<3)+(num<<1)+(c^48),c=getchar();
    return num*flag;
}
int n,m,cnt[MAXN];
double ans,p[MAXN][305],dp[305][MAXN];
double delt[MAXN],sv[MAXN],siv[MAXN],val[MAXN];
void updata(int c)
{
	double g[MAXN]={};
	memcpy(g,dp[c],sizeof g);
	dp[c][0]=0;
	for(int i=1;i<=n;i++)
		dp[c][i]=dp[c][i-1]*(1-p[i][c])+g[i-1]*p[i][c];
	cnt[c]++;
	siv[c]+=cnt[c]*dp[c][n];sv[c]+=dp[c][n];
	double e=siv[c]+cnt[c]*(1-sv[c]);
	delt[c]=e-val[c];
	val[c]=e;
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%lf",&p[i][j]);
			p[i][j]/=1000.0;
		}
	for(int i=1;i<=m;i++)
	{
		dp[i][0]=1.0;
		for(int j=1;j<=n;j++)
			dp[i][j]=dp[i][j-1]*(1-p[j][i]);
		sv[i]=dp[i][n];
		updata(i);
	}
	for(int i=1;i<=n;i++)
	{
		int Max=0;
		for(int j=1;j<=m;j++)
			if(delt[Max]<delt[j])
				Max=j;
		if(!Max) break;
		ans+=delt[Max];
		updata(Max);
	}
	printf("%.12lf",ans);
}
```



---

## 作者：LJZ_C (赞：8)

## dp

### 直接dp

易知不同T恤之间互相独立则
定义dp[i][j][h]为第i种T恤前j个人里送出h个的概率
状态转移方程为:
$$dp[i][j][h] = dp[i][j - 1][h - 1] * p[j][i] + dp[i][j - 1][h] * (1 - p[j][i])$$
定义E[i][j]为第i种T恤带j种对答案贡献的期望
则由全期望公式得：
$$E[i][j] = \sum_{h = 1}^j(h * dp[i][n][h]) + \sum_{h = j + 1}^n(j * dp[i][n][h])$$
然后问题转化为分组背包求解
时间复杂度O($n^2m$)

### 优化
观察E数组，发现其满足上凹函数性质且：
$$E[i][j + 1] - E[i][j] = \sum_{h = j + 1}^ndp[i][n][h] = 1 - \sum_{h = 1}^jdp[i][n][h]$$
则定义delt[i]为当前状态下多带一件i种T恤对答案的贡献
省略dp数组第3维初始化为一件不带的情况并更新delt数组
然后依次贪心选取当前所带T恤x并更新delt[x]与dp[x]数组即可
时间复杂度O($nm + n^2$)

## 代码

```language_cpp
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
using namespace std;
typedef long double ld;
const int MAXN = 3000, MAXM = 300;
int n, m;
ld last[MAXN + 5], delt[MAXM + 5], dp[MAXM + 5][MAXN + 5], p[MAXN + 5][MAXM + 5];

inline void DynamicProgramming(void) {
	register int i, j;
	
	memset(delt, 0, sizeof(delt));
	memset(dp, 0, sizeof(dp));
	for(i = 1; i <= m; ++i) {
		dp[i][0] = 1.;
		for(j = 1; j <= n; ++j) {
			dp[i][j] = dp[i][j - 1] * (1. - p[j][i]);
		}
		delt[i] = 1. - dp[i][n];
	}
}

inline void updata(int x) {
	register int i;
	
	for(i = 0; i <= n; ++i) {
		last[i] = dp[x][i];
	} 
	dp[x][0] = 0.;
	for(i = 1; i <= n; ++i) {
		dp[x][i] = dp[x][i - 1] * (1. - p[i][x]) + last[i - 1] * p[i][x];  
	}
	delt[x] -= dp[x][n];
}

int main(int argc, char *argv[]) {
	register int i, j;
	double ans;
	
	while( ~scanf("%d%d", &n, &m) ) {
		ans = 0;
		for(i = 1; i <= n; ++i) {
			for(j = 1; j <= m; ++j) {
				int tmp;
				
				scanf("%d", &tmp);
				
				p[i][j] = (ld)tmp / 1000.;
			}
		}
		DynamicProgramming();
		for(i = 1; i <= n; ++i) {
			int tmp = 0;
			
			for(j = 1; j <= m; ++j) {
				if(delt[j] > delt[tmp]) {
					tmp = j;
				} 
			}
			ans += delt[tmp];
			updata(tmp);
		}
		
		cout << fixed << setprecision(12) << ans << endl; 
	}
	
	return 0;
}
```

---

## 作者：i207M (赞：6)

唔...好题...就是我有点蠢：因为每个人只能选一种大小，所以我以为颜色之间的贡献不是独立的（毕竟选了一种就不能选另一种了），后来发现这个想法是多余的，直接死扣期望的线性性就行。

然后考虑第i种衣服带j件的贡献。我们可以DP算出第i种衣服需要j件的概率，从而计算出带j件的贡献，然后跑分组背包即可。

DP状态是3维的：$f[w][i][j]$表示第w种，考虑前i个人，需要j个的概率。

$$f[i][j]=f[i-1][j-1]p+f[i-1][j](1-p)$$

直接DP是$O(mn^2)$的，但是我们不需要把所有的都DP出来。我们衣服是一件件选的，每次选权值最大的，选完了之后我们把j往上推一维即可，复杂度$O(n(n+m))$

正确性是因为这个DP是凸的

```cpp
const int N=3005,M=305;
int n,m;
double p[N][M];
double f[M][N];
double sv[M],siv[M],val[M],dt[M];
int cnt[M];
void upd(int c)
{
	static double g[N];
	memcpy(g,f[c],sizeof(g));
	f[c][0]=0;
	for(ri i=1;i<=n;++i)
		f[c][i]=f[c][i-1]*(1-p[i][c])+g[i-1]*p[i][c];
	++cnt[c];
	sv[c]+=f[c][n],siv[c]+=cnt[c]*f[c][n];
	double nv=siv[c]+cnt[c]*(1-sv[c]);
	dt[c]=nv-val[c];
	val[c]=nv;
}
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
#endif
	in(n),in(m);
	for(ri i=1,t;i<=n;++i)
		for(ri j=1;j<=m;++j)
		{
			in(t);
			p[i][j]=t/1000.0;
		}
	for(ri i=1;i<=m;++i) 
	{
		f[i][0]=1;
		for(ri j=1;j<=n;++j) f[i][j]=f[i][j-1]*(1-p[j][i]);
		sv[i]=f[i][n];
		upd(i);
	}
	double ans=0;
	for(ri o=1;o<=n;++o)
	{
		double mx=-1; int mxk=0;
		for(ri i=1;i<=m;++i)
			if(mx<dt[i]) mx=dt[i],mxk=i;
		if(!mxk) break;
		ans+=dt[mxk];
		upd(mxk);
	}
	printf("%.10f\n",ans);
	return 0;
}
```

---

## 作者：cqbzlzm (赞：4)

### Description

$n\leq 3000$ 个人和 $m\leq 300$ 种衣服，已知 $p_{i,j}$ 表示第 $i$ 个人适合第 $j$ 中衣服的概率，求一个最优的 $n$ 件衣服的种类选取方案，使有合适衣服穿的人数期望最大。

你会询问每个人他适合穿的衣服到底是哪一件，如果你有，你就给他，否则就不给。

### Solution

#### 暴力

首先发现不同的衣服互不影响。

对每一种衣服分开考虑。

设 $f_{i,j,k}$ 表示**第 $i$ 件**衣服，对于前 $j$ 个人有 $k$ 个人适合当前衣服的概率。

$f_{i,j,k}=f_{i,j-1,k-1}\times p_{j,i}+f_{i,j-1,k}\times (1-p_{j,i})$。

设 $E_{i,j}$ 表示 **第 $i$ 件**衣服，选 $j$ 件，期望分出去的衣服件数。

$E_{i,j}=\sum_{k=0}^j{f_{i,n,k}\times k}+\sum_{k=j+1}^{n}{f_{i,n,k}\times j}$。

最后打一个分组背包，总时间复杂度 $O(n^2\times m)$。

#### 优化

考虑一件一件地选衣服，设 $delt_i$ 表示现在情况下，选一件 $i$ 衣服可以对答案造成的贡献。

注意到同一种衣服，关于选的衣服件数，$E_{i,j}$ 是凸的，于是可以每次选择最大的 $delt_i$，然后动态更新 $f$ 和 $delt$ 数组。

具体的，对第 $i$ 件衣服，设当前已经选了 $k$ 件，那么 $delt_i=E_{i,k+1}-E_{i,k}=\sum_{h=k+1}^{n}{f_{i,n,h}}=1-\sum_{h=1}^{k}f_{i,n,h}$。

### Code

#### 暴力

```cpp
for (int i = 1; i <= m; i ++) { // 第 i 种
    f[i][0][0] = 1;
    for (int j = 1; j <= n; j ++) { // 前 j 人
        for (int k = 0; k <= j; k ++) {
            if (k >= 1) f[i][j][k] += f[i][j - 1][k - 1] * p[j][i];
            f[i][j][k] += f[i][j - 1][k] * (1 - p[j][i]);
        }
    }
}
for (int i = 1; i <= m; i ++) {
    for (int j = 0; j <= n; j ++) {
        for (int h = 0; h <= j; h ++)
            E[i][j] += f[i][n][h] * h;
        for (int h = j + 1; h <= n; h ++)
            E[i][j] += f[i][n][h] * j;
    }
}

for (int i = 1; i <= m; i ++) {
    for (int j = 0; j <= n; j ++) {
        for (int k = 0; k <= j; k ++)
            dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + E[i][k]);
    }
}
printf("%.9lf", dp[m][n]);
```



#### 优化

```cpp
for (int i = 1; i <= m; i ++) { // 第 i 种
    f[i][0] = 1;
    for (int j = 1; j <= n; j ++) { // 前 j 人
        f[i][j] = f[i][j - 1] * (1 - p[j][i]);
    }
    delt[i] = 1 - f[i][n];
}
double ans = 0;
for (int i = 1; i <= n; i ++) { // 选出第 i 件衣服
    int cur = 0;
    for (int j = 1; j <= m; j ++) {
        if (!cur || delt[j] > delt[cur]) cur = j;
    }
    cnt[cur] ++;
    ans += delt[cur];
    for (int j = 0; j <= n; j ++) ff[j] = f[cur][j];
    f[cur][0] = 0;
    for (int j = 1; j <= n; j ++) // 前 j 人
        f[cur][j] = f[cur][j - 1] * (1 - p[j][cur]) + ff[j - 1] * p[j][cur];
    delt[cur] -= f[cur][n];
}
```

---

## 作者：CarroT1212 (赞：3)

先设 $f_{i,j,k}$ 表示前 $i$ 个人中是第 $j$ 种衣服的人有 $k$ 个的概率。有 $f_{i,j,k}=p_{i,j}f_{i-1,j,k-1}+(1-p_{i,j})f_{i-1,j,k}$。

那设 $g_{i,j}$ 表示准备了 $i$ 件第 $j$ 种衣服然后卖出的期望件数，有 $g_{i,j}=\sum\limits_{k=0}^i k\cdot f_{i,j,k}+\sum\limits_{k=i+1}^{n}i\cdot f_{i,j,k}$，后一项表示衣服不够了。

根据期望无敌的可加性，可以直接用这个 $g$ 跑背包。然而这是 $O(n^2m)$ 的，需要优化。

观察一下性质。发现随着同种衣服携带的件数越来越多，那么就需要多几个人来买这种衣服，那多出来的人的衣服尺寸成功对上的概率应该也会越来越低，那每多带一件衣服增加的期望应该会越来越少吧？

不太严谨，但实际上它确实是。作一下差可得 $g_{i,j}-g_{i-1,j}=\sum\limits_{k=i+1}^{n}f_{n,j,k}$。显然这玩意会随着 $k$ 增大而单调不增。

所以我们可以一件一件决定选哪种衣服，每次选那种会使答案增加最多的衣服，每次拿一件，直到选了 $n$ 件为止。由于贪心结论的力量，这样取一定不会漏掉类似取两件同样的比取两件不同的要优的情况。

于是我们就并不需要求那么多 $f$……了吗？上面的 $g_{i,j}-g_{i-1,j}=\sum\limits_{k=i}^{n}f_{n,j,k}$ 也是要用到 $i$ 之后的元素的，需要所有的 $f$，这咋办。

考虑 $f$ 的定义，发现有 $\sum\limits_{k=0}^{i} f_{i,j,k}=1$。所以可以把式子换成 $g_{i,j}-g_{i-1,j}=1-\sum\limits_{k=0}^{i-1}f_{n,j,k}$。这样需要的 $f$ 的量也就差不多是 $O(n^2)$ 级别的了，可求。

具体的，先把每一个 $f_{i,j,1}$ 找出来。设第 $i$ 件衣服目前取了 $c_i$ 件，初始时都为 $0$。反复重复以下过程：找到 $g_{c_p+1,p}-g_{c_p,p}$ 最大的 $p$，也就是使答案增加最多的。选定这件衣服，然后求出 $f_{i,p,c_p+2}$，再去找现在最大的 $p$……直到选了 $n$ 件。每次更新是 $O(n)$ 的。总复杂度 $O(nm+n^2)$。

实际实现需要一些滚动数组神秘技巧。

```cpp
ll n,m;
ld a[N][W],dp[N][W],now[W],tmp[N],ans;
void mian() {
	scanf("%lld%lld",&n,&m);
	for (ll i=1;i<=n;i++) for (ll j=1;j<=m;j++)
		scanf("%Lf",&a[i][j]),a[i][j]/=1000.;
	for (ll i=1;i<=m;i++) dp[0][i]=1;
	for (ll i=1;i<=n;i++) for (ll j=1;j<=m;j++)
		dp[i][j]=dp[i-1][j]*(1-a[i][j]);
	for (ll i=1;i<=m;i++) now[i]=1-dp[n][i];
	for (ll i=1;i<=n;i++) {
		ll p=0;
		for (ll j=1;j<=m;j++) if (now[j]>now[p]) p=j;
		ans+=now[p];
		for (ll j=0;j<=n;j++) tmp[j]=dp[j][p];
		dp[0][p]=0;
		for (ll j=1;j<=n;j++) dp[j][p]=tmp[j-1]*a[j][p]+dp[j-1][p]*(1-a[j][p]);
		now[p]-=dp[n][p];
	}
	printf("%.15Lf",ans);
}
```

---

## 作者：crashed (赞：2)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF183D)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;一看就不知道如何入手......  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;好吧~~看了题解就知道了~~，这是道$DP$题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先我们有一个暴力做法，设$f(k,i,j)$为前$i$个人中喜欢第$k$件衬衫的有$j$个人的概率。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;则$f$的转移为$f(k,i,j)=p_if(k,i-1,j-1)+(1-p_i)f(k,i-1,j)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;再设$g(k,i)$表示准备$i$件第$k$种衬衫的期望送出数量。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;则$g(k,i)=\sum_{j=0}^ij\times f(k,n,j)+i\times\sum_{j=i+1}^nf(k,n,j)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这个方程的意义是，如果送出的数量少于准备的数量，则每种送出的数量的贡献均为其送出数量；否则，如果衣服被送完了，则贡献仅为准备的数量。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;此时，我们已经可以用$g$函数来跑背包骗分了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不过，如果你追求满分的话，可以继续看下去：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们尝试对$g$的相邻两项做差：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$g(k,i+1)-g(k,i)=\sum_{j=i+1}^nf(k,n,j)=1-\sum_{j=0}^if(k,n,j)$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后我们发现$\lim_{i\rightarrow n}\Delta g=0$，所以函数$g$的增长是递减的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后，我们就可以贪心地解决这个问题：每次选择一种会使答案增长最多的衣服，放入答案集合中，同时我们可以推出这种衣服的$i+1$的增长率。重复直到凑完$n$件衣服。而$f$和$g$也不需要全部预处理了，边贪边打表。  
# 代码
```cpp
#include <cstdio>

const int MAXN = 3005, MAXM = 305;

template<typename _T>
void read( _T &x )
{
    x = 0;char s = getchar();int f = 1;
    while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
    while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
    x *= f;
}

template<typename _T>
void write( _T x )
{
    if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
    if( 9 < x ){ write( x / 10 ); }
    putchar( x % 10 + '0' );
}

double p[MAXN][MAXM];
double f[MAXM][MAXN], delta[MAXM], tmp[MAXN];
int times[MAXM] = {};
int N, M;

void prepare()
{
	for( int i = 1 ; i <= M ; i ++ ) f[i][0] = 1.0;
	for( int i = 1 ; i <= M ; i ++ )
	{
		for( int j = 1 ; j <= N ; j ++ ) f[i][j] = f[i][j - 1] * ( 1.0 - p[j][i] );
		delta[i] = 1.0 - f[i][N];
	}
}

void upt( const int indx )
{
	times[indx] ++;
	if( times[indx] >= N )
	{
		delta[indx] = 0;
		return;
	}
	for( int i = 0 ; i <= N ; i ++ ) tmp[i] = f[indx][i];
	f[indx][0] = 0.0;
	for( int i = 1 ; i <= N ; i ++ )
		f[indx][i] = f[indx][i - 1] * ( 1.0 - p[i][indx] ) + tmp[i - 1] * p[i][indx];
	delta[indx] -= f[indx][N];
}

int main()
{
	read( N ), read( M );
	for( int i = 1 ; i <= N ; i ++ )
	{
		for( int j = 1 ; j <= M ; j ++ )
		{
			scanf( "%lf", &p[i][j] );
			p[i][j] /= 1000.0;
		}
	}
	prepare();
	double maxVal, res = 0;
	int maxIndx;
	for( int i = 1 ; i <= N ; i ++ )
	{
		maxVal = 0, maxIndx = -1;
		for( int j = 1 ; j <= M ; j ++ )
		{
			if( maxVal < delta[j] )
			{
				maxVal = delta[j];
				maxIndx = j;
			}
		}
		res += maxVal;
		if( maxIndx == -1 ) return 0;
		upt( maxIndx );
	}
	printf( "%.12lf\n", res );
	return 0;
}
```

---

## 作者：SegTree (赞：0)

下提供一个时间复杂度为 $O(n(n+m))$ 的做法，但是依赖于精度限制。

首先对于每件衣服依次考虑，求出 $f_i$ 表示恰 $i$ 个人穿这种衣服的概率，然后就可以随便算出选 $i$ 件衣服的收益 $g_i$。这样就有转移式 $dp'_{i+j}\gets dp_i+g_j$，其中 $dp$ 表示的是考虑前面的这些衣服选 $i$ 件衣服的最大期望收益。

遗憾的是这个做法时间复杂度高达 $O(n^2m)$，无法通过。

我们设置一个 $eps$，在 $f$ 转移的时候只考虑值 $>eps$ 的位置。由于每次转移概率 $x$ 和 $1-x$ 都有一个 $\le 0.5$，因此 $O(\log \dfrac{1}{eps})$ 轮就会减半到 $eps$ 以下。算答案的时候只需要特殊关心 $f_j>eps$ 的位置，剩下的位置是可以通过这种近似方式 $O(1)$ 计算得出的。

因为本题要求精度误差不超过 $10^{-9}$，$eps$ 大概取 $10^{-12}$ 即可通过。

---

## 作者：mRXxy0o0 (赞：0)

# 分析

按每种尺寸考虑，设准备了 $x$ 件，合适的人有 $y$ 个，那么会带来 $\min(x,y)$ 的贡献。

再套一层期望，设 $f_{i,j}$ 表示第 $i$ 种尺寸买 $j$ 件带来的期望贡献，先求出 $f$。

## 法一

分治 FFT，由于 $f$ 是一个类似背包的东西，对于每个人，一次项系数表示选，零次项为不选，$n$ 个人乘起来就好。

求出 $f$ 后再考虑一个 DP，设 $g_{i,j}$ 表示前 $i$ 种尺寸用了 $j$ 个人的最大期望。明显，这个转移是 $O(n^2m)$ 的。考虑优化，直接猜决策单调性，或打表验证一下。

## 法二

先忽略一下很难搞的 $f$，直接进入求 $g$ 的环节。你会惊奇的发现，对于同种尺寸，多买一件的贡献增量是递减的且始终不小于 $0$。证明可以考虑其意义以及最开始贡献取 $\min$ 的形式，这也是法一中决策单调性的原因。

因此，我们可以直接贪心。维护所有颜色下一个增量的最大值，直接取就好。对于 $f$ 和 $g$，可以只更新到需要的位置。更新一次是 $O(n)$ 的，所以总时间复杂度是 $O(n^2)$ 的。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<double,int> pii;
const int N=3010,M=310;
int n,m,b[M];
double a[M][N],f0[M][N],f1[M][N],g[M][N],s1[M],s0[M],ans;
priority_queue<pii>q;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		for(int j=1,x;j<=m;++j){
			scanf("%d",&x);
			a[j][i]=x/1000.0;
		}
	}
	for(int i=1;i<=m;++i){
		double s=1;
		for(int j=1;j<=n;++j){
			f0[i][j]=f0[i][j-1]*(1-a[i][j])+s*a[i][j];
			s*=(1-a[i][j]);
		}
		s0[i]=s+f0[i][n];
		s1[i]=f0[i][n];
		g[i][1]=1-s;
		b[i]=1;
		q.push({1-s,i});
	}
	for(int i=1;i<=n;++i){
		ans+=q.top().first;
		int x=q.top().second;
		q.pop();
		++b[x];
		for(int j=1;j<=n;++j) f1[x][j]=f0[x][j-1]*a[x][j]+f1[x][j-1]*(1-a[x][j]);
		for(int j=1;j<=n;++j) f0[x][j]=f1[x][j],f1[x][j]=0;
		g[x][b[x]]=s1[x]+b[x]*(1-s0[x]);
		q.push({g[x][b[x]]-g[x][b[x]-1],x});
		s0[x]+=f0[x][n],s1[x]+=b[x]*f0[x][n];
	}
	printf("%.9lf",ans);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

UPD 2025.4.22：修了一个唐爆了的锅。

[Prob. link](https://codeforces.com/problemset/problem/183/D)

首先考虑一个暴力 dp：

令 $f_{i,j,k}$ 表示前 $j$ 个选了 $k$ 个颜色为 $i$ 的，显然有转移 $f_{i,j,k}=f_{i,j-1,k}(1-p_{j,i})+f_{i,j-1,k-1}p_{j,i}$。

令 $g_{i,j}$ 表示带了 $j$ 件颜色为 $i$ 的衣服的期望人数，容易想到 $g_{i,j}=\sum\limits_{k=0}^{j} kf_{i,n,k}+i\sum\limits_{k=j+1}^n f_{i,n,k}$。

时间复杂度 $O(n^2m)$。

***

考察 $g$ 的变化量：

$g_{i,j+1}-g_{i,j}=\sum\limits_{k=j+1}^n f_{i,n,k}=1-\sum\limits_{k=0}^j f_{i,n,k}$

容易想到 $\Delta g$ 是单调不增的。

根据期望的线性性，我们把它拆成每件衣服的贡献和后，贪心地取最大的 $\Delta g$ 一定是最优的，因为它一定不会因为取的数目的增加而导致有其它的贡献比它更大。

容易想到这样以后显然可以增加在一个颜色取的数量之后计算 $f_{i,\_,j+1}$ 然后更新 $\Delta g$，这样单次更新是 $O(n)$ 的，一共取 $n$ 次，所以时间复杂度是 $O(n^2)$ 的。

总时间复杂度 $O(n(n+m))$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define endl '\n'
using namespace std;
const int N=3005,M=305;
int n,m;
double p[3005][305],f[2][M][N],delta[M],ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) for(int j=1,P;j<=m;++j) cin>>P,p[i][j]=P/1000.0;
	for(int i=1;i<=m;++i){
		f[0][i][0]=1;
		for(int j=1;j<=n;++j) f[0][i][j]=f[0][i][j-1]*(1-p[j][i]);
		delta[i]=1-f[0][i][n];
	}
	for(int i=1;i<=n;++i){
		int pos=1;
		for(int j=1;j<=m;++j) if(delta[j]>delta[pos]) pos=j;
		ans+=delta[pos];
		for(int j=1;j<=n;++j) f[1][pos][j]=f[1][pos][j-1]*(1-p[j][pos])+f[0][pos][j-1]*(p[j][pos]);
		delta[pos]-=f[1][pos][n];
		memcpy(f[0][pos],f[1][pos],sizeof(f[0][pos]));
	}
	cout<<fixed<<setprecision(10)<<ans<<endl;
	return 0;
}
```

---

